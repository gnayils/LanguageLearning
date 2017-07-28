#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread() {
    this->threadId = pthread_t(0);
}

void* Thread::startRoutine(void* args) {
    Thread* thread =(Thread*) args;
    thread->run();
    return NULL;
}

void Thread::start() {
    if(pthread_create(&threadId, NULL, startRoutine, this) != 0) {
        cout << "start thread failed" << endl;
    }
}

Thread::~Thread() {
    
}
