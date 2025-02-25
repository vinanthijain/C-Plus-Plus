#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

std::mutex m1;
std::mutex m2;
int globalVar1 = 0;
int globalVar2 = 0;


void thread1() {
    for(int i=0;i<100;i++) {
        m1.lock();
        globalVar1++; // Some processing ...

        m2.lock();
        globalVar2++; // Some processing ...

        m1.unlock();
        m2.unlock();
    }
}

void thread2() {
    for(int i=0;i<100;i++) {
        m2.lock();
        globalVar2++; // Some processing ...

        m1.lock();
        globalVar1++; // Some processing ...

        m1.unlock();
        m2.unlock();
    }
}

int main() {
    std::cout << "Starting threads ..." << std::endl;

    std::thread t1(thread1);
    std::thread t2(thread2);


    t1.join();
    t2.join();

    std::cout << "Result:\n";
    std::cout << "globalVar1: "<<globalVar1 <<"\n";
    std::cout << "globalVar2: "<<globalVar2 <<"\n";

    std::cout << "End" << std::endl;

    return 0;
}
