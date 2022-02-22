#include "thread_pool.h"

namespace CT {
namespace Thread {

ThreadPool::ThreadPool(pool_size_t num) {
    for (pool_size_t i = 0; i < num; ++i) {
        m_Threads.emplace_back(std::thread(&ThreadPool::Worker, this));
    }
}

ThreadPool::~ThreadPool() {
    if (!IsStop())
        Shutdown();
}

void ThreadPool::Worker() {
    while (true) {
        std::function<void()> task;

        // 加锁
        std::unique_lock<std::mutex> lock(m_QueMutex);
        m_ConditionLock.wait(lock, [this] {
            // 并且任务队列不为空
            return (IsStop() || !m_Tasks.empty());
        });

        if (IsStop()) {  // 停止工作线程
            return;
        } else if (m_Tasks.empty()) {  // 防止虚假唤醒
            std::this_thread::yield(); // 可以使用睡眠函数也可以是有yield函数
        } else {  // 执行任务
            task = std::move(m_Tasks.front());
            m_Tasks.pop();

            task();
        }
    }
}

void ThreadPool::Shutdown() {
    {
        std::unique_lock<std::mutex> lock(m_QueMutex);
        m_Stop = true;
    }
    m_ConditionLock.notify_all();

    if (!m_Threads.empty()) {
        for (auto &t : m_Threads) {
            t.join();
        }
    }
    m_Threads.clear();
}

}  // namespace Thread
}  // namespace CT
