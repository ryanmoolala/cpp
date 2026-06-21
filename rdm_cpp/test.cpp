#include <atomic>
#include <thread>
#include <cassert>
#include <iostream>

using namespace std;

atomic<bool> x, y;
atomic<int> z;

void write_x() {
    cout << "write_x: storing x=true" << endl;
    x.store(true, memory_order_seq_cst);
}

void write_y() {
    cout << "write_y: storing y=true" << endl;
    y.store(true, memory_order_seq_cst);
}

void read_x_then_y() {
    cout << "read_x_then_y: waiting for x" << endl;

    while (!x.load(memory_order_seq_cst));

    cout << "read_x_then_y: saw x=true" << endl;

    if (y.load(memory_order_seq_cst)) {
        cout << "read_x_then_y: saw y=true, incrementing z" << endl;
        ++z;
    } else {
        cout << "read_x_then_y: saw y=false" << endl;
    }
}

void read_y_then_x() {
    cout << "read_y_then_x: waiting for y" << endl;

    while (!y.load(memory_order_seq_cst));

    cout << "read_y_then_x: saw y=true" << endl;

    if (x.load(memory_order_seq_cst)) {
        cout << "read_y_then_x: saw x=true, incrementing z" << endl;
        ++z;
    } else {
        cout << "read_y_then_x: saw x=false" << endl;
    }
}

int main() {
    x = false;
    y = false;
    z = 0;

    cout << "Starting threads..." << endl;

    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);

    a.join();
    b.join();
    c.join();
    d.join();

    cout << "Final values:" << endl;
    cout << "x = " << x.load() << endl;
    cout << "y = " << y.load() << endl;
    cout << "z = " << z.load() << endl;

    assert(z.load() != 0);

    cout << "Assertion passed: z != 0" << endl;

    return 0;
}