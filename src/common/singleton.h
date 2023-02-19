/**
 * @file singleton.h
 * @author cxl (c.x.l@live.com)
 * @brief 单例接口
 * @version 0.1
 * @date 2021-09-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _CT_FRAMEWORK_SINGLETON_H_
#define _CT_FRAMEWORK_SINGLETON_H_

template <class T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    Singleton(const T &) = delete;
    Singleton(const T &&) = delete;
    T &operator=(const T &) = delete;

    static T &Instance() {
        static T instance;
        return instance;
    }
};

#endif  // _CT_FRAMEWORK_SINGLETON_H_