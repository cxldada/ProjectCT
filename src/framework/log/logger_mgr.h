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

#ifndef _CT_LOG_LOGGER_MGR_H_
#define _CT_LOG_LOGGER_MGR_H_

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

#endif  // _CT_LOG_LOGGER_MGR_H_