#ifndef LOCK_H
#define LOCK_H

#include "pch.h"
#include <pthread.h>

class Sem {
public:
    Sem() {
        if (sem_init(&sem_, 0, 0) != 0) {
            STDERR_FUNC_LINE();
            exit(EXIT_FAILURE);
        }
    }

    explicit Sem(uint32_t num) {
        if (sem_init(&sem_, 0, num) != 0)  {
            STDERR_FUNC_LINE();
            exit(EXIT_FAILURE);
        }
    }

    ~Sem() {
        sem_destroy(&sem_);
    }

    bool wait() {
        return sem_wait(&sem_) == 0;
    }

    bool post() {
        return sem_post(&sem_) == 0;
    }

private:
    sem_t sem_;
};

class Mutex {
public:
    Mutex() {
        if (pthread_mutex_init(&mutex_, NULL) != 0) {
            STDERR_FUNC_LINE();
            exit(EXIT_FAILURE);
        }
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    bool lock() {
        return pthread_mutex_lock(&mutex_) == 0;
    }

    bool unlock() {
        return pthread_mutex_unlock(&mutex_) == 0;
    }

    pthread_mutex_t* get() {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};

class Cond {
public:
    Cond() {
        if (pthread_cond_init(&cond_, NULL) != 0) {
            STDERR_FUNC_LINE();
            exit(EXIT_FAILURE);
        }
    }

    ~Cond() {
        pthread_cond_destroy(&cond_);
    }

    bool wait(pthread_mutex_t* pm_mutex) {
        return pthread_cond_wait(&cond_, pm_mutex) == 0;
    }

    bool timewait(pthread_mutex_t* pm_mutex, struct timespec t) {
        return pthread_cond_timedwait(&cond_, pm_mutex, &t) == 0;
    }

    bool signal() {
        return pthread_cond_signal(&cond_) == 0;
    }
    
    bool broadcast() {
        return pthread_cond_broadcast(&cond_) == 0;
    }

private:
    pthread_cond_t cond_;
};

class RwLock {
public:
    RwLock() {
        if (pthread_rwlock_init(&rwlock_, NULL) != 0) {
            STDERR_FUNC_LINE();
            exit(EXIT_FAILURE);
        }
    }

    ~RwLock() {
        pthread_rwlock_destroy(&rwlock_);
    }

    bool rdlock() {
        return pthread_rwlock_rdlock(&rwlock_) == 0;
    }

    bool wrlock() {
        return pthread_rwlock_wrlock(&rwlock_) == 0;
    }

    bool unlock() {
        return pthread_rwlock_unlock(&rwlock_) == 0;
    }

    pthread_rwlock_t* get() {
        return &rwlock_;
    }

private:
    pthread_rwlock_t rwlock_;
};

#endif