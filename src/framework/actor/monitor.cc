#include "monitor.h"

void MonitorMgr::init(size_t ThreadCount) {
    for (size_t i = 0; i < ThreadCount; i++) {
		vMonitorMgr.emplace_back(std::make_unique<monitor>());
    }
}

void MonitorMgr::MonitorMgr_trigger(unique_ptr<monitor> &sm, uint32_t source, uint32_t destination) {
    sm->source = source;
    sm->destination = destination;
    atomic_fetch_add(&sm->version, 1);
}

void MonitorMgr::MonitorMgr_check(unique_ptr<monitor> &sm) {
    if (sm->version == sm->check_version) {
        if (sm->destination) {
            // skynet_context_endless(sm->destination);
            // skynet_error(NULL, "A message from [ :%08x ] to [ :%08x ] maybe in an endless loop (version = %d)", sm->source , sm->destination, sm->version);
        }
    } else {
        sm->check_version = sm->version;
    }
}

unique_ptr<void> MonitorMgr::thread_monitor() {
    int i;
    int n = count;
    // skynet_initthread(THREAD_MONITOR);
    for (;;) {
        // CHECK_ABORT
        for (i = 0; i < n; i++) {
            MonitorMgr_check(vMonitorMgr[i]);
        }
        for (i = 0; i < 5; i++) {
            // CHECK_ABORT
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    return NULL;
}