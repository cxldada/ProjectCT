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

#ifndef _CT_FRAMEWORK_ACTOR_H_
#define _CT_FRAMEWORK_ACTOR_H_

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

using namespace std;

class actor : public Singleton<actor> {
    // friend class Singleton<actor>;
private:
public:
    actor(/* args */){};
    ~actor(){};

    bool start();
    unique_ptr<void> thread_worker();
    // MsgQueueMgr* actor_context_message_dispatch(skynet_monitor *sm, message_queue *q, int weight);
};

#endif  // _CT_FRAMEWORK_ACTOR_H_