#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;
using namespace std::chrono;
int myCount=0;
std::recursive_mutex m;

void fun(char c, int count){
    
    if(count<=0) return ;
    
    m.lock();
    
    cout<<"I am "<<c<<" Count "<<count<<endl;
    
    fun(c,--count);
    m.unlock();
}

int main(){
    
    thread t1(fun,'0',10);
    thread t2(fun,'1',10);
    
    t1.join();
    t2.join();
    
    return 0;
}




