#ifndef THREAD_H
#define	THREAD_H

#include <pthread.h>


class Thread {
    
protected:
    pthread_t threadId;
    
private:
    static void* startRoutine(void* args);
    
public:
    Thread();
    
    virtual void run() = 0;
    
    void start();
    
    virtual ~Thread();
};

#endif

