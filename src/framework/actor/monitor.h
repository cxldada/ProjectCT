/**
 * @file monitor.h
 * @author trk
 * @brief  防止发生死循环或者比较耗时（超过5s）
 * @version 0.1
 * @date 2021-09-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef _CT_FRAMEWORK_MONITOR_H_
#define _CT_FRAMEWORK_MONITOR_H_

#include "../common/singleton.h"

#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <chrono>
#include <condition_variable>

using namespace std;

struct monitor {
    std::atomic_int version{0};
    int check_version{0};
    uint32_t source{0};
    uint32_t destination{0};
};

class MonitorMgr : public Singleton<MonitorMgr> {
    // friend class Singleton<actor>;
private:
    int count{0};                             //记录线程数
    vector<unique_ptr<monitor>> vMonitorMgr;  //监控器指针容器
    condition_variable cond;                  //多线程条件变量锁
    pthread_mutex_t mutex;                    //互斥锁
    int sleep{0};                             //等待时间
    int quit{0};                              //是否退出

public:
    MonitorMgr(){};
    ~MonitorMgr(){};

    void init(size_t ThreadCount);
    void MonitorMgr_trigger(unique_ptr<monitor> &sm, uint32_t source, uint32_t destination);
    void MonitorMgr_check(unique_ptr<monitor> &sm);

    unique_ptr<void> thread_monitor();
};

#endif  // _CT_FRAMEWORK_MONITOR_H_