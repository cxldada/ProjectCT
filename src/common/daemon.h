/**
 * @file daemon.h
 * @author cxl (c.x.l@live.com)
 * @brief 守护进程实现
 * @version 0.1
 * @date 2021-09-25 11:38:50
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _CT_FRAMEWORK_DAEMON_H_
#define _CT_FRAMEWORK_DAEMON_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <signal.h>
#include <fcntl.h>

namespace CT {
    /**
     * @brief 使调用进程进入守护模式
     *
     * @param nochdir 是否改变工作目录
     * @return int 0成功，<0 失败
     */
    int daemon(bool nochdir) {
        int i, fd0, fd1, fd2;
        pid_t pid;
        struct rlimit rl;
        struct sigaction sa;

        // 修改文件模式屏蔽字
        umask(0);

        if (getrlimit(RLIMIT_NOFILE, &rl)) {
            return -1;
        }

        // fork并关闭父进程
        if ((pid = fork()) < 0) {
            return -1;
        } else if (pid != 0) {  // 父进程
            exit(0);
        }
        setsid();  // 关闭控制终端，成为会话首进程

        // 确保将来打开文件时不会分配控制终端
        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGHUP, &sa, NULL) < 0) {
            return -1;
        }

        // 再次fork
        if ((pid = fork() < 0)) {
            return -1;
        } else if (pid != 0) {  // 父进程
            exit(0);
        }

        // 修改工作目录
        if (!nochdir) {
            if (chdir("/") < 0) {
                return -1;
            }
        }

        // 关闭所有文件描述符
        if (rl.rlim_max == RLIM_INFINITY)
            rl.rlim_max = 1024;
        for (i = 0; i < rl.rlim_max; ++i)
            close(i);

        // 重定向标准输入输出
        fd0 = open("/dev/null", O_RDWR);
        fd1 = dup(0);
        fd2 = dup(0);

        return 0;
    }
}

#endif  // _CT_FRAMEWORK_DAEMON_H_