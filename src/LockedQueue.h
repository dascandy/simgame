#pragma once

#include <mutex>
#include <vector>

template <typename T>
class LockedQueue {
public:
  void push(T&& value) {
    std::lock_guard<std::mutex> l(m);
    queue.push_back(std::move(value));
  }
  void pop_all(std::vector<T>& otherQueue) {
    std::lock_guard<std::mutex> l(m);
    swap(queue, otherQueue);
  }
private:
  std::mutex m;
  std::vector<T> queue;
};

