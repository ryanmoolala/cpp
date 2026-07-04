#include <atomic>     
#include <iostream>    
#include <thread>      
#include <vector>      
#include <chrono>      
using namespace std::chrono;
using namespace std;
struct spinlock {
    atomic<bool> booleanlock = {0};
    void lock() {
        for (;;) { //Test and Test-Swap implementation
            if (!booleanlock.exchange(true, memory_order_acquire)) {
                break;
            }
            while (booleanlock.load(memory_order_relaxed)) {
               // __builtin_ia32_pause();  -> x86 only
               this_thread::yield();
            }
        }
    }
    void unlock() {
        booleanlock.store(false, memory_order_release);
    } 
};

int main() {
    const long long iterations = 100000000;
    const int num_threads = 8;

    spinlock lock;
    long long counter = 0;
    long long iters_per_thread = iterations / num_threads;

    auto work = [&] {
        for (long long i = 0; i < iters_per_thread; ++i) {
            lock.lock();
            ++counter;
            lock.unlock();
        }
    };

    vector<thread> threads;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) threads.emplace_back(work);
    for (auto& t : threads) t.join();

    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<duration<double, milli>>(end - start).count();

    cout << "Final counter: " << counter << endl;
    cout << "Threads: " << num_threads << endl;
    cout << "Total iterations: " << iters_per_thread * num_threads << endl;
    cout << "Elapsed time: " << elapsed_ms << " ms" << endl;
    cout << "Throughput: " << (iters_per_thread * num_threads) / (elapsed_ms / 1000.0)
         << " ops/sec" << endl;

    return 0;
}

// int main() {
//     spinlock lock;
//     int counter = 0;

//     auto work = [&] {
//         for (int i = 0; i < 100000; ++i) {
//             lock.lock();
//             ++counter; // unprotected non-atomic increment — this is the point
//             lock.unlock();
//         }
//     };

//     vector<thread> threads;
//     for (int i = 0; i < 4; ++i) threads.emplace_back(work);
//     for (auto& t : threads) t.join();

//     cout << counter << endl; // should be exactly 400000 if the lock works
//     return 0;
// }


/*
hardware-level atomic instructions (such as Compare-And-Swap or Test-And-Set) 
to ensure that checking the lock and acquiring it is an indivisible action

threads should spin on a standard relaxed read. 
Once the lock appears free, the thread attempts 
to acquire it via an atomic operation.

Acquire Semantics: When locking, you must use std::memory_order_acquire
(or an acquire fence) to ensure all subsequent memory operations wait until the lock is obtained
No read or write that comes after the acquire operation (in program order, on this thread) 
can be reordered to happen before it. 

Release Semantics: When unlocking, you must use std::memory_order_release to ensure all previous 
modifications to the protected data are visible to other threads before the lock is released.

All writes to memory that happened before this store (in program order, on this thread) become visible to 
any other thread that subsequently does an acquire load on this same atomic and sees the new value.
*/