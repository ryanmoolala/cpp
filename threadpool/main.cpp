#include <atomic>
#include <thread>
#include <cassert>
#include <iostream>
#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    mutex mtx;
    condition_variable cv;
    queue<function<void()>> tasks;
    void worker(); //fucntion each thread runs
    bool stop;

public:
    ThreadPool(std::size_t nr_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> future<decltype(f(args...))>;

    //make pool non movable and non copyable
    ThreadPool(ThreadPool&) = delete; //cant touch ref
    ThreadPool(const ThreadPool&) = delete; 
    ThreadPool(ThreadPool&&) = delete; //delete the move constructor
    ThreadPool& operator=(ThreadPool&&) = delete; //no moving allowed
    ThreadPool& operator=(const ThreadPool&) = delete;
};

ThreadPool::ThreadPool(std::size_t nr_workers) {
    stop = false;
    for (auto i{ 0u }; i < nr_workers; i++) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

void ThreadPool::worker() {
    for (;;) {
        function<void()> curr_task;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() {
                return stop || !tasks.empty();
            });
            if (stop && tasks.empty()) {
                break;
            }
            curr_task = tasks.front();
            tasks.pop();
        }
        curr_task();
    }
}


//&&: Rvalue reference / Forwarding reference (the one in your thread pool) no unnecessary copies

template<typename F, typename... Args> //generic code for multiple types, works for any fn signature
auto ThreadPool::enqueue(F&& f, Args&&... args) -> future<decltype(f(args...))> {
    using ReturnType = decltype(f(args...)); 

    auto func = bind(forward<F>(f), forward<Args>(args)...);
    auto encapsulated_ptr = make_shared<packaged_task<ReturnType()>>(func);
    //makes tasks copyable, use shared ptr (only bumps ref count and doesnt copy underlying object)
    future<ReturnType> future_object = encapsulated_ptr->get_future();
    {
        unique_lock<mutex> lock(mtx);
        tasks.emplace([encapsulated_ptr]() {
            (*encapsulated_ptr)();
        });
    }
    cv.notify_one();
    return future_object;
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (auto& worker : workers) {
        worker.join();
    }
}

int main() {
    ThreadPool pool(4);
    vector<future<int>> results;
    for (int i = 0; i < 8; i++) {
        auto future = pool.enqueue([i] {
            return i + 1;
        });
        results.emplace_back(move(future));
    }

    for (auto& result : results) {
        cout << result.get() << ' ';
    }
    cout << endl;
    cout << "hard ware concurrency " << std::thread::hardware_concurrency() << endl;
}