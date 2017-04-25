//
//  SYLock.hpp
//  xBlog
//
//  Created by Cocoa on 4/10/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYLock_hpp
#define SYLock_hpp

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

class SYLock {
private:
    pthread_mutex_t     mMutex;
    
public:
    inline SYLock(){
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        int ret = pthread_mutex_init(&mMutex, &attr);
        if(ret != 0 ){
            printf("pthread_mutex_init error %d \n\r",ret);
        }
    }
    
    inline ~SYLock(){
        pthread_mutex_destroy(&mMutex);
    }
    
    inline void  Enter(){
        pthread_mutex_lock(&mMutex);
    }
    
    inline void Leave(){
        pthread_mutex_unlock(&mMutex);
    };
    
};

class SYLockUser
{
public:
    inline  SYLockUser(SYLock & lock):mlock(lock){
        mlock.Enter();
    }
    
    inline  ~SYLockUser(){
        mlock.Leave();
    }
    
private:
    SYLock & mlock;
};


#define SYLOCK(T) SYLockUser lock(T)

#endif /* SYLock_hpp */
