#include <stdlib.h>
#include <iostream>
#include "Consumer.h"
#include "Bread.h"

using namespace std;

Consumer::Consumer(BreadContainer* breadContainer) : Thread() {
    this->breadContainer = breadContainer;
}

void Consumer::run() {
    while (true) {
        Bread* bread = breadContainer->getBread();
        if(bread == NULL) {
            cout << "get a empty bread from the basket" << endl;
            continue;
        }
        cout << this->threadId << " eat bread, index: " << bread->index << endl;
        usleep(rand() / double(RAND_MAX) * 1000 * 1000);
    }
}

Consumer::~Consumer() {
    if (breadContainer != NULL) {
        delete breadContainer;
        breadContainer = NULL;
    }
}