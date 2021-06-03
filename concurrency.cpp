#include <iostream>
#include <string.h>
#include <thread>
#include <vector>

using namespace std;

void print(int n, const std::string &str)
{
    cout << "Printing interger: " << n << endl;
    cout << "Printing string: " << str << endl;
}


int main()
{
    cout << "Starting execution..." << endl;

    vector<string> s = {
        "Example1",
        "Example2",
        "Threadripper"
    };
    vector<thread> threads;

    for (string val : s)
    {
        threads.push_back(thread(print, 1, val));
    }

    for (auto &th : threads)
    {
        th.join();
    }

    // Single Thread of execution
    thread t1(print, 10, "SingleThreaded"); // initialize thread t1 with print function, then add print arguments at the end
    t1.join();                              // stop main thread to execute t1 thread, then continue with main thread

    return 0;
}