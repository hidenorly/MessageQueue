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

class MessageQueue {
    std::mutex mMutex;
    std::queue<std::string> mQueue;
    std::condition_variable mEvent;
    bool mIsShuttingDown = false;

   public:
    MessageQueue();
    virtual ~MessageQueue();
    // Enqueue word (expect to use by sender thread, etc.)
    void enqueue(std::string word);
    // Dequeue the stored word (expect to use by receiver thread, etc.)
    // Note that this blocks the caller thread when the queue is empty until
    // enqueuing
    std::string dequeue(void);
};
