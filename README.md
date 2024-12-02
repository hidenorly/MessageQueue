# MessageQueue

This is thread-safe message queue based on recent C++ (C++20 is specified in CMakeList.txt).

```
int main() {
    MessageQueue mq;

    auto sender = [&mq]() {
        for (int i = 0; i < 100; ++i) {
            mq.enqueue("hello" + std::to_string(i));
        }
    };

    auto receiver = [&mq]() {
        for (int i = 0; i < 100; ++i) {
            std::string msg = mq.dequeue();
            std::cout << msg << std::endl;
        }
    };

    std::thread senderThread(sender);
    std::thread receiverThread(receiver);

    senderThread.join();
    receiverThread.join();
}
```

You can use like MailBox.
