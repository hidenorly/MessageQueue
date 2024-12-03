/*
  Copyright (C) 2024 hidenorly

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

template <typename T>
class TMessageQueue {
    std::mutex mMutex;
    std::queue<std::string> mQueue;
    std::condition_variable mEvent;
    bool mIsShuttingDown = false;

   public:
    TMessageQueue() = default;

    virtual ~TMessageQueue(){
        mIsShuttingDown = true;
        mEvent.notify_all();
    };

    // Enqueue message (expect to use by sender thread, etc.)
    void enqueue(T message){
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(std::move(message));
        }
        mEvent.notify_one();
    }

    // Dequeue the stored message (expect to use by receiver thread, etc.)
    // Note that this blocks the caller thread when the queue is empty until
    // enqueuing 
    T dequeue(void){
        T result;
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mEvent.wait(lock, [&] { return mIsShuttingDown || !mQueue.empty(); });
            if (!mIsShuttingDown) {
                result = std::move(mQueue.front());
                mQueue.pop();
            }
        }
        return result;
    }

    // shutdown the queue
    void shutdown() {
        std::lock_guard<std::mutex> lock(mMutex);
        mIsShuttingDown = true;
        mEvent.notify_all();
    }
};

// for backward compatibility
using MessageQueue = TMessageQueue<std::string>;
