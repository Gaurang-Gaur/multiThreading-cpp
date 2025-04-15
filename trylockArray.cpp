#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
using namespace std::chrono;

std::mutex m1, m2;
int X = 0, Y = 0;

void doSomething(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void incrementXY(int& XorY, mutex& m, const char* ch) {
    for (int i = 0; i < 5; i++) {
        m.lock();
        ++XorY;
        cout << ch<<" " << XorY <<" " <<endl;
        m.unlock();
        doSomething(1);
    }
}

void consumeXY() {
    int useCount = 5;
    int XplusY = 0;
    while (1) {
        int lockResult = try_lock(m1, m2);
        if (lockResult == -1) {
            if (X != 0 && Y != 0) {
                --useCount;
                XplusY += (X + Y);
                X = 0;
                Y = 0;
                cout << "X Plus Y =" << XplusY << endl;
            }
            m1.unlock();
            m2.unlock();
            if (useCount == 0) break;
        }
    }
}

int main() {
    thread t1(incrementXY, std::ref(X), std::ref(m1), "X");
    thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y");
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
