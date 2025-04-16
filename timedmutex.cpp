#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;
using namespace std::chrono;
int myCount=0;
std::timed_mutex m;
void increament(int x){
    
  if(m.try_lock_for(chrono::seconds(1))){
      
      ++myCount;
      
      this_thread::sleep_for(chrono::seconds(2));
      cout<<"Thread "<<x<<" Entered"<<endl;
      m.unlock();
  }
  else{
      cout<<"Thead "<<x<<" Could not Entered"<<endl;
  }
  
}


int main(){
    
    thread t1(increament,1);
    thread t2(increament,2);
    
    t1.join();
    t2.join();
    
    return 0;
}




