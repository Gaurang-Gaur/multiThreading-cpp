#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; i++) {
        if ((i & 1) == 0) {
            evenSum += i;
        }
    }
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; i++) {
        if ((i & 1) == 1) {
            oddSum += i;
        }
    }
}

int main() {
    ull start = 0;
    ull end = 100000000;  // Reduced to a realistic range

    auto startTime = high_resolution_clock::now();
    thread t1(findOdd,start,end);
    thread t2(findEven,start,end);
    // findOdd(start, end);
    // findEven(start, end);
    t1.join();
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    // CPU core detection
    unsigned int cores = thread::hardware_concurrency();
    cout << "Detected CPU Cores: " << (cores == 0 ? "Unknown" : to_string(cores)) << endl;
    cout << "oddSum: " << oddSum << endl;
    cout << "evenSum: " << evenSum << endl;
    cout << "Duration (seconds): " << duration.count() / 1000000.0 << endl;

    return 0;
}
