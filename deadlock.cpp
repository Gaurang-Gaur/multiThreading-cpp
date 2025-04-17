#include<iostream>
#include<mutex>
#include<thread>

#include<condition_variable>
#include<chrono>
using namespace std;
using namespace std::chrono;

std::mutex m1,m2;
std::condition_variable cv;


void thread1(){
    m1.lock();
    // this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    cout<<"I am thread1"<<endl;
    m1.unlock();
    m2.unlock();
}

void thread2(){
    m2.lock();
    // this_thread::sleep_for(chrono::seconds(1));
    // this will put threads in deadlock
    m1.lock();
    cout<<"I am thread2"<<endl;
    m2.unlock();
    m1.unlock();
}

int main(){
    
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();
    
    return 0;
}