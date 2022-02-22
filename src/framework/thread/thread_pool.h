/**
 * @file thread_pool.h
 * @author cxl (c.x.l@live.com)
 * @brief 线程池
 * @version 0.1
 * @date 2021-10-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _CT_FRAMEWORK_THREAD_POOL_H_
#define _CT_FRAMEWORK_THREAD_POOL_H_

#include <thread>
#include <vector>
#include <future>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace CT {
namespace Thread {

/**
 * @brief 线城池对象
 * 
 * 使用方式
 * ThreadPool pool{4}; // 创建四个线程
 * 
 * pool.Submit(std::move(func), Args...); // 提交任务
 * 
 * pool.Shutdown();  // 提前终止所有工作线程
 *
 */
class ThreadPool {
public:
    typedef uint32_t pool_size_t;

public:
    explicit ThreadPool(pool_size_t num = std::thread::hardware_concurrency());
    ~ThreadPool();

    /**
     * @brief 关闭所有线程
     * 
     */
    void Shutdown(); 

    bool IsStop() {
        return m_Stop;
    }

    /**
     * @brief 提交任务
     *
     * @tparam Func 函数对象
     * @tparam Args 函数参数
     * @param f
     * @param args
     */
    template <typename Func, typename... Args>
    auto Submit(Func &&f, Args &&...args);

private:
    void Worker();

private:
    bool m_Stop{false};
    std::vector<std::thread> m_Threads;
    std::queue<std::function<void()>> m_Tasks;
    std::mutex m_QueMutex;
    std::condition_variable m_ConditionLock;
};

template <typename Func, typename... Args>
auto ThreadPool::Submit(Func &&f, Args &&...args) {
    // 定义函数返回值类型
    using return_type = typename std::result_of<Func(Args...)>::type;

    // packaged_task不允许拷贝，所以使用智能指针
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();

    // 加入任务队列
    {
        std::unique_lock<std::mutex> lock(m_QueMutex);

        if (IsStop())
            throw std::runtime_error("enqueue on stopped ThreadPool");

        m_Tasks.push([task]() {
            (*task)();
        });
    }

    m_ConditionLock.notify_all();
    return res;
}

}  // namespace thread
}  // namespace CT

#endif  //_CT_FRAMEWORK_THREAD_POOL_H_