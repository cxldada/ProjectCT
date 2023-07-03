/**
 * @file actor.h
 * @author trk
 * @brief actor模型的实现
 * @version 0.1
 * @date 2021-09-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "MsgQueueMgr.h"

#include "monitor.h"
#include "../common/singleton.h"

#include <cstdio>
#include <assert.h>
#include <thread>

#define STOP 1               //分发者告诉组装着已完成
#define NO_MORE_NUMBER 2     //分发着告诉加工者没有原材料了
#define I_AM_DONE 3          //加工者告诉分发者我干完了
#define GIVE_ME_A_NEW_ONE 4  //加工者告诉分发者再来一个

// TODO 最好改成可配置项
#define THREADCOUNT 8

class Actor : public Singleton<Actor> {
public:
    Actor(/* args */){};
    ~Actor(){};
};