/**
 * @file logger.h
 * @author cxl (c.x.l@live.com)
 * @brief 日志管理器
 * @version 0.1
 * @date 2021-09-26
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "common.h"
#include "singleton.h"

namespace CT {
namespace Log {

class CLoggerMgr : public Singleton<CLoggerMgr> {
public:
    CLoggerMgr() {}
    virtual ~CLoggerMgr() {}

private:
};  // class CLoggerMgr

}  // namespace Log
}  // namespace CT