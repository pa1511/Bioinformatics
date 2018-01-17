/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File: SyncQueue.h
 * Author: paf
 *
 * Created on January 16, 2018, 8:00 AM
 */

#ifndef SYNCQUEUE_H
#define SYNCQUEUE_H

#include <unistd.h>
#include <queue>

#include <mutex>
#include <condition_variable>

/**
 * Sync queue is a thread safe implementation of a simple queue structure.
 *
 */
template <typename T>
class SyncQueue {
public:
  /**
   * Returns and removes the first element from the queue if it exists,
   * otherwise blocks until an element is present.
   * @return first queue element
   */
  T pop() {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    mlock.unlock();
    return item;
  }

  /**
   * Pushes the given element into the queue.
   * If someone is waiting for an element in the queue they will be notified.
   * @param item - element to add to the queue
   */
  void push(const T& item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_all();
  }

  /**
   * Checks is the queue empty. If it is then true is returned otherwise false.
   * @return true if empty, false if not
   */
  bool empty() {
    std::unique_lock<std::mutex> mlock(mutex_);
    bool result = queue_.empty();
    mlock.unlock();
    return result;
  }

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};


#endif /* SYNCQUEUE_H */

