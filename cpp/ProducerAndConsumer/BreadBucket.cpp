#include <iostream>
#include <stdlib.h>
#include "BreadBucket.h"

BreadBucket::BreadBucket(int capacity) {
    this->breads = new queue<Bread*>();
    this->capacity = capacity;
}

bool BreadBucket::init() {
    if(pthread_mutex_init(&mutex, NULL) != 0) {
        cout << "mutex initialize failed" << endl;
        return false;
    }
    if(pthread_cond_init(&getCondition, NULL) != 0) {
        cout << "getCondition initialize failed" << endl;
        return false;
    }
    if(pthread_cond_init(&putCondition, NULL) != 0 ) {
        cout << "putCondition initialize failed" << endl;
        return false;
    }
    return true;
}

void BreadBucket::putBread(Bread* bread) {
    if (pthread_mutex_lock(&mutex) != 0) {
        cout << "lock method putBread failed" << endl;
        return;
    }

    while(breads->size() >= capacity) {
        cout << "bread basket was full, notify consumer to eat bread, " << pthread_self() << " begin wait" << endl;
        pthread_cond_wait(&putCondition, &mutex);
        cout << pthread_self() << " being notified" << endl; 
    }

    bread->index = breads->size();
    breads->push(bread);

    pthread_cond_signal(&getCondition);

    if (pthread_mutex_unlock(&mutex) != 0) {
        cout << "unlock method putBread failed" << endl;
        return;
    }
}

Bread* BreadBucket::getBread() {
    if (pthread_mutex_lock(&mutex) != 0) {
        cout << "lock method getBread failed" << endl;
        return NULL;
    }

    while(breads->empty()) {
        cout << "bread basket was empty, notify producer to make bread, " << pthread_self() << " begin wait" << endl;
        pthread_cond_wait(&getCondition, &mutex);
        cout << pthread_self() << " being notified" << endl;
    }

    Bread* bread = breads->front();
    breads->pop();

    pthread_cond_signal(&putCondition);

    if (pthread_mutex_unlock(&mutex) != 0) {
        cout << "unlock method getBread failed" << endl;
        return NULL;
    }
    return bread;
}

BreadBucket::~BreadBucket() {
    if(this->breads != NULL) {
        while(!breads->empty()) {
            Bread* bread = breads->front();
            breads->pop();
            delete bread;
        }
        delete breads;
        breads = NULL;
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&getCondition);
    pthread_cond_destroy(&putCondition);
}