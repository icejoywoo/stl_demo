
#ifndef _BASE_MUTEX_H_20140427
#define _BASE_MUTEX_H_20140427

#include <pthread.h>

namespace icejoywoo {
namespace base {

/// A simple pthread mutex wrapper
class MutexLock {
public:
    MutexLock() {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
        pthread_mutex_init(&m_mutex, &attr);
    }

    ~MutexLock() {
        pthread_mutex_destroy(&m_mutex);
    }

    void Lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void Unlock() {
        pthread_mutex_unlock(&m_mutex);
    }

    /// just for internal use
    pthread_mutex_t* GetMutex() {
        return &m_mutex;
    }
private:
    pthread_mutex_t m_mutex;

    // noncopyable
    MutexLock(const MutexLock&);
    const MutexLock& operator=(const MutexLock&);
};


/// MutexGuard RAII mutex guard
class MutexLockGuard {
public:
    explicit MutexLockGuard(MutexLock& mutex)
        : m_mutex(mutex) {
        m_mutex.Lock();
    }

    ~MutexLockGuard() {
        m_mutex.Unlock();
    }

private:
    MutexLock& m_mutex;

    // noncopyable
    MutexLockGuard(const MutexLockGuard&);
    const MutexLockGuard& operator=(const MutexLockGuard&);
};

/// pthread condition wrapper
class Condition {
public:
    explicit Condition(MutexLock& mutex)
        : m_mutex(mutex) {
        pthread_cond_init(&m_cond, NULL);
    }

    void Wait() {
        pthread_cond_wait(&m_cond, m_mutex.GetMutex());
    }

    void Notify() {
        pthread_cond_signal(&m_cond);
    }

    void NotifyAll() {
        pthread_cond_broadcast(&m_cond);
    }

private:
    pthread_cond_t m_cond;
    MutexLock& m_mutex;
    // noncopyable
    Condition(const Condition&);
    const Condition& operator=(const Condition&);
};

} // end base namespace
} // end icejoywoo namespace

# define MutexLockGuard(x) static_assert(false, "Missing mutex guard var name")

#endif // _BASE_MUTEX_H_20140427
