#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
mutex m;
int addmoney=0;

void addMoney(){
    // m.lock();
    
    for(int i=0;i<10000;i++){
    if(m.try_lock()){
        
    ++addmoney;
    m.unlock();
    }
    }
   
}


int main(){
    thread t1(addMoney);
    thread t2(addMoney);
    t1.join();
    t2.join();
    
    cout<<addmoney;
    
    return 0;
    
}