#pragma once

#include <vector>
#include <functional>

template <typename T>
using myVector = std::vector<T>;

template <typename T, template <typename> typename Container = myVector>
struct filter_view {
  struct iterator {
    typename Container<T>::iterator it, end;
    std::function<bool(const T&)> functor;
    iterator& operator++() {
      ++it;
      while (it != end && !functor(*it)) { ++it; }
      return *this;
    }
    T &operator*() { 
      return *it; 
    }
    bool operator!=(const iterator& oi) {
      return oi.it != it;
    }
    bool operator==(const iterator& oi) {
      return oi.it == it;
    }
  };
  iterator begin() { return iterator{container.begin(), container.end(), functor}; }
  iterator end() { return iterator{container.end(), container.end(), functor}; }
  Container<T>& container;
  std::function<bool(const T&)> functor;
};

