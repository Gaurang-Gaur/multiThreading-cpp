#include<iostream>
#include<mutex>
#include<chrono>
#include<vector>
#include<thread>
#include<condition_variable>
using namespace std;
 std::condition_variable cond;
 std:: mutex m;
 
 vector<int> buffer;
 
 void producer(int val){
     
     
     while(val){
         std::unique_lock<mutex> lock(m);
         cond.wait(lock,[]{return (buffer.size()<50);});
         
         buffer.push_back(val);
         cout<<"producer is producing"<<val<<endl;
         val--;
         
         lock.unlock();
         cond.notify_one();
     }
 }
 
 void consumer(){
     
     while(true){
         
         std::unique_lock<mutex> lock(m);
         cond.wait(lock,[]{return (buffer.size()>0);});
         int val=buffer.back();
         buffer.pop_back();
         cout<<"consumer is consuming: "<<val<<endl;
         lock.unlock();
         cond.notify_one();
     }
 }
 
 
 
 
 
 
 
 
 
 
 
 int main(){
     
     thread t1(producer,100);
     thread t2(consumer);
     t1.join();
     t2.join();
     return  0;
 }