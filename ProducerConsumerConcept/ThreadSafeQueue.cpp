#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <random>
#include <future>

using namespace std;

template <typename T>
class TSQueue
{
private:
    queue<T> messageQueue;
    mutex mqMutex;
    condition_variable mqCondVariable;
public:
    void push(T item) 
    {
        unique_lock<mutex> lock(mqMutex);
        messageQueue.push(item);
        mqCondVariable.notify_one();
    }

    T pop() 
    {
        unique_lock<mutex> lock(mqMutex);
        mqCondVariable.wait(lock, [this](){
            return !messageQueue.empty();
        });
        T item = messageQueue.front();
        messageQueue.pop();
        return item;
    }
};

template <typename V>
class Producer
{
private:
    int sleep = 100;
    TSQueue<V>* registeredQueue = nullptr;
    bool isRunning=false;
public:
    void registerQueue(TSQueue<V>& q) {
        registeredQueue = &q;
    }
    void produce() {
        isRunning=true;
        if (registeredQueue == nullptr) {cout<<"Missing queue to push to"<<endl;}
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> dist(0, 1000);
        while (isRunning) {
            registeredQueue->push(dist(rng));
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    void cancel() {
        isRunning=false;
    }
};

template <typename S>
class Consumer
{
private:
    TSQueue<S>* subscribedQueue = nullptr;
    int id;
    bool isListening;
public:
    Consumer(int id) {
        this->id=id;
        this->isListening=true;
    }
    void subscribeQueue(TSQueue<S>& q) {
        subscribedQueue = &q;
    }
    void listen() {
        while (isListening && subscribedQueue != nullptr) {
            cout << ("ID: " + std::to_string(id) + " " + std::to_string(subscribedQueue->pop()) + "\n");
        }
    }
    void cancel() {
        isListening=false;
        subscribedQueue=nullptr;
    }
};

//Simulate a fan-out pattern, 1 producer, multiple consumers

int main() {
    TSQueue<int> q;
    Producer<int> p;
    vector<Consumer<int>> consumers;
    vector<thread> consumerThreads;

    for (int i = 1; i <= 5; i++) {
        consumers.emplace_back(i);
        consumers.back().subscribeQueue(q);
    }

    p.registerQueue(q);

    thread a ([&p](){
        p.produce();
    });

    a.detach();
    cout << "=== PRODUCING ===" << endl;
    
    //5 threads run consumer?
    for (size_t i = 0; i < consumers.size(); i++) {
        consumerThreads.emplace_back(
            thread(
                [&consumers, i]() {
                    consumers[i].listen();
                }
            )
        );
    }
    for (auto& c : consumerThreads) {c.join();}
    return 0;
}


