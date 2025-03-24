#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> atomic_value(0);

void writer() {
    for (int i = 0; i < 10; ++i) {
        atomic_value.store(i, std::memory_order_seq_cst);  // 使用顺序一致性顺序存储
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void reader() {
    for (int i = 0; i < 10; ++i) {
        int value = atomic_value.load(std::memory_order_seq_cst);  // 使用顺序一致性顺序加载
        std::cout << "Read value: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::thread t1(writer);
    std::thread t2(reader);

    t1.join();
    t2.join();

    return 0;
}