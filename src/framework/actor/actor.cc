#include "actor.h"

bool actor::start() {
    //初始化
    MonitorMgr::GetInstance().init(THREADCOUNT);

    thread threads[THREADCOUNT];
    threads[0] = thread(MonitorMgr::GetInstance().thread_monitor());
    // threads[1] = thread(thread_timer) ;
    // threads[2] = thread(thread_socket) ;

    for (size_t i = 0; i < THREADCOUNT; i++) {
        threads[i] = thread(thread_worker);
    }
    for (size_t i = 0; i < THREADCOUNT; i++) {
        threads[i].join();
    }
}

//读取消息 进行分发
unique_ptr<void> actor::thread_worker() {
    /*MsgQueueMgr*  q = NULL;
    while (!m->quit)
    {
        q =
    }*/
}