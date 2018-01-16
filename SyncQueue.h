/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SyncQueue.h
 * Author: paf
 *
 * Created on January 16, 2018, 8:00 AM
 */

#ifndef SYNCQUEUE_H
#define SYNCQUEUE_H

#include <queue>

#include <unistd.h>
#include <mutex>
#include <condition_variable>

template <typename T>
class SyncQueue
{
 public:
 
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    mlock.unlock();
    return item;
  }
  
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_all();
  }
   
  bool empty(){
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

