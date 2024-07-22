#ifndef CMAKEPROJECT1_H
#define CMAKEPROJECT1_H

#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>

class SharedBuffer {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::deque<std::string> buffer;

public:
    void add(const std::string& data);
    std::string get();
};

#endif // CMAKEPROJECT1_H
