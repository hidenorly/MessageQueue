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

#include "MessageQueue.hpp"

MessageQueue::MessageQueue() {}

MessageQueue::~MessageQueue() {
    mIsShuttingDown = true;
    mEvent.notify_all();
}

void MessageQueue::enqueue(std::string word) {
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mQueue.push(word);
    }
    mEvent.notify_one();
}

std::string MessageQueue::dequeue(void) {
    std::string result;
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mEvent.wait(lock, [&] { return mIsShuttingDown || !mQueue.empty(); });
        if (!mIsShuttingDown) {
            result = mQueue.front();
            mQueue.pop();
        }
    }
    return result;
}
