#include <errno.h>
#include <iostream>
#include <queue>
#include "BreadBasket.h"

BreadBasket::BreadBasket(int capacity) {
    this->breads = new queue<Bread*>();
    this->capacity = capacity;
}

bool BreadBasket::init() {
    if(sem_init(&state, 0, 0) != 0) {
        cout << "semaphore initialize failed" << endl;
        return false;
    }
    return true;
}

void BreadBasket::putBread(Bread* bread) {
    if(breads->size() < capacity) {
        bread->index = breads->size();
        breads->push(bread);
        sem_post(&state);
    }
}

Bread* BreadBasket::getBread() {
    while(sem_wait(&state)== -1 && errno == EINTR);
    Bread* bread = breads->front();
    breads->pop();
    return bread;
}

BreadBasket::~BreadBasket() {
    if(this->breads != NULL) {
        while(!breads->empty()) {
            Bread* bread = breads->front();
            breads->pop();
            delete bread;
        }
        delete[] breads;
        breads = NULL;
    }
    sem_destroy(&state);
}
