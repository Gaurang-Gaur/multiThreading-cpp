#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

std::mutex m;
std::condition_variable cv;
long int balance = 0;

void addMoney(int money) {
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount Added: " << money << endl;
    cv.notify_one();
}

void withdrawMoney(int money) {
    std::unique_lock<mutex> ul(m);
    cv.wait(ul, [] { return balance != 0; });  // fixed syntax here

    if (balance >= money) {
        balance -= money;
        cout << "Amount Deducted: " << money << endl;
    } else {
        cout << "Amount can't be deducted, money asked: " << money << endl;
    }
    cout << "Current Balance: " << balance << endl;
}

int main() {
    thread t1(withdrawMoney, 5000);
    thread t2(addMoney, 500);

    t1.join();
    t2.join();

    return 0;
}
