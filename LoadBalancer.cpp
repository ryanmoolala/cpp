#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;
// Weighted Round Robin Load Balancing Algorithm, Linked List for student requests
struct MathOperation {
    int (*operation)(int, int);
    atomic(MathOperation*) next;
    MathOperation(int (*op)(int, int)): operation(op), next(nullptr) {}
};

//Worker

//Requester
class Student {
    private:
    public:
};

class LoadBalancer {
    private:
        atomic(MathOperation*) head;
        atomic(MathOperation*) tail;
    public:
        void enqueue(MathOperation& question) {
            MathOperation* newNode = &question;
            newNode->next.store(nullptr, memory_order_relaxed); //plain store, not published yet
            while (true) {
                MathOperation* tailPtr = tail.load(memory_order_acquire); //get current tail
                MathOperation* nextPtr = tailPtr->next.load(memory_order_acquire);   //get its nextPtr
                if (tailPtr == tail.load(memory_order_acquire)) {
                    if (nextPtr == null) {
                        if (tailPtr->next.compare_exchange_weak(
                            nextPtr, newNode, memory_order_release, memory_order_relaxed
                        )) {
                            tail.compare_exchange_weak(
                                tailPtr, newNode, memory_order_release, memory_order_relaxed 
                            );
                            return;
                        }
                        continue; //some other thread beat you to it, retry again
                    } else { 
                        //bookkeeping
                        //The else branch helps advance a lagging tail pointer to the actual last node, since another thread already linked one in but hasn't finished swinging tail forward yet.
                        tail.compare_exchange_weak(tailPtr, nextPtr, memory_order_release, memory_order_relaxed); 
                    }
                } 
            }
            return;
        }
        void dequeue(MathOperation& question) {
            return;
        }
}

//Balancer
int main() {
    MathOperation test([](int x, int y){return x + y;});
    int result = test.operation(2, 2);
    cout << result << endl;
    return 0;
}
