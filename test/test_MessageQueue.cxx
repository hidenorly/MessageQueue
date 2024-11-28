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

#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include "MessageQueue.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Test cases for MessageQueue
TEST(MessageQueueTest, BasicEnqueueDequeue) {
    MessageQueue pipe;
    std::string testWord = "hello";

    pipe.enqueue(testWord);
    std::string result = pipe.dequeue();

    EXPECT_EQ(result, testWord);
}

TEST(MessageQueueTest, EnqueueDequeueOrder) {
    MessageQueue pipe;
    std::vector<std::string> inputWords = {"first", "second", "third"};
    for (const auto& word : inputWords) {
        pipe.enqueue(word);
    }

    for (const auto& expectedWord : inputWords) {
        std::string result = pipe.dequeue();
        EXPECT_EQ(result, expectedWord);
    }
}

TEST(MessageQueueTest, ThreadSafety) {
    MessageQueue pipe;

    auto sender = [&pipe]() {
        for (int i = 0; i < 100; ++i) {
            pipe.enqueue("word" + std::to_string(i));
        }
    };

    auto receiver = [&pipe]() {
        for (int i = 0; i < 100; ++i) {
            std::string word = pipe.dequeue();
            EXPECT_TRUE(word == "word" + std::to_string(i));
            EXPECT_FALSE(word.empty());
        }
    };

    std::thread senderThread(sender);
    std::thread receiverThread(receiver);

    senderThread.join();
    receiverThread.join();
}

