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
#pragma once

#include "../common/singleton.h"

#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <chrono>
#include <condition_variable>

using namespace std;

class MonitorMgr : public Singleton<MonitorMgr> {
public:
    MonitorMgr(){};
    ~MonitorMgr(){};

    void init();
};