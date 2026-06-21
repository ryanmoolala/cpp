#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

atomic<int> x, y, z;
atomic<int> r1;
void setX() {
    x.store(3, memory_order_relaxed);
    y.store(2, memory_order_release);
}
void setY() {
    r1 = y.load(memory_order_acquire);
    y.store(3, memory_order_relaxed);
    z.store(4, memory_order_release);
    x.store(5, memory_order_relaxed);
}
void setZ() {
    while (z.load(memory_order_acquire) != 4);
    cout << x.load(memory_order_relaxed) << "\n";
}

int main() {
    x = 0;
    y = 0;
    z = 0;
    int i = 0;
    // while (i < 100) {
    //     thread a(setX);
    //     thread b(setY);
    //     thread c(setZ);


    //     a.join();
    //     b.join();
    //     c.join();
    //     i++;
    // }
    thread a(setX);
    thread b(setY);
    thread c(setZ);


    a.join();
    b.join();
    c.join();
    cout << "x = " << x.load() << endl;
    cout << "y = " << y.load() << endl;
    cout << "z = " << y.load() << endl;

    return 0;
}