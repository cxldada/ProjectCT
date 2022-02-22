/**
 * @file CT_mq.h
 * @author trk
 * @brief 主消息池
 * @version 0.1
 * @date 2021-09-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _CT_FRAMEWORK_MQ_H_
#define _CT_FRAMEWORK_MQ_H_
#include <thread>
#include <mutex>

//主数据结构
typedef struct CT_message {
    uint32_t source{0};
    int sessinon{0};
    void* data{nullptr};
    size_t sz{0};
} message;

//消息包结构
// 单例模式
class MsgQueueMgr {
private:
    std::mutex Mutex;
    uint32_t handle{0};
    int cap{0};
    int head{0};
    int tail{0};
    int release{0};
    int in_global{0};
    int overload{0};
    int overload_threshold{0};
    CT_message* queue{nullptr};
    MsgQueueMgr* next{nullptr};

public:
    MsgQueueMgr(/* args */){};
    ~MsgQueueMgr(){};

    // TODO 函数名 应该是 PushGlobalMQ 一下都是如此
    void CT_globalmq_push(MsgQueueMgr* queue);
    MsgQueueMgr* CT_globalmq_pop();
    MsgQueueMgr* CT_mq_create(uint32_t handle);
    void CT_mq_mark_release(MsgQueueMgr* q);
    // void CT_mq_release(MsgQueueMgr* q  )  这个用到了函数指针 暂时屏蔽
    unsigned int CT_mq_handle(MsgQueueMgr* q);
    int CT_mq_pop(MsgQueueMgr* q, CT_message* message);
    void CT_mq_push(MsgQueueMgr* q, CT_message* message);

    int CT_mq_length(MsgQueueMgr* q);
    int CT_mq_overload(MsgQueueMgr* q);

    void CT_mq_init();
};

//线程分发出来的消息全部存在这个总消息池里
typedef struct global_queue {
    MsgQueueMgr* head{nullptr};
    MsgQueueMgr* tail{nullptr};
    std::mutex Mutex;
};

#endif  // _CT_FRAMEWORK_MQ_H_