#include <iostream>
#include <stdlib.h>
#include "Producer.h"
#include "Bread.h"

using namespace std;

Producer::Producer(BreadContainer* breadContainer) : Thread() {
    this->breadContainer = breadContainer;
}

void Producer::run() {
    while(true) {
        Bread* bread = new Bread();
        struct timespec currentTime;
        clock_gettime(CLOCK_REALTIME, &currentTime);
        bread->madeTime = currentTime.tv_sec * 1000 + currentTime.tv_nsec * 1000 * 1000;
        breadContainer->putBread(bread);
        cout << this->threadId << "make bread, index: " << bread->index << endl;
        usleep(rand() / double(RAND_MAX) * 1000 * 1000);
    }
}

Producer::~Producer() {
    if(breadContainer != NULL) {
        delete breadContainer;
        breadContainer = NULL;
    }
}