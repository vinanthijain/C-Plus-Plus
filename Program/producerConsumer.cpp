#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;
bool done = false;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate data production delay
        std::unique_lock<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();}
 // Notify one waiting consumer
        {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
        cv.notify_all(); // Notify all waiting consumers that production is done
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !dataQueue.empty() || done; }); // Wait until there is data or done is true
        if (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            lock.unlock(); // Unlock the mutex before processing data
            std::cout << "Consumed: " << data << std::endl;
        } else if (done) {
            break; // Exit the loop if done and no more data
        }
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}

