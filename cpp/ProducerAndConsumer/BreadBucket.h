#ifndef BREABUCKET_H
#define	BREABUCKET_H
#include <queue>
#include <pthread.h>
#include "BreadContainer.h"
#include "Bread.h"

using namespace std;

class BreadBucket : public BreadContainer {
    
private:
    pthread_mutex_t mutex;
    pthread_cond_t getCondition;
    pthread_cond_t putCondition;
    
    queue<Bread*>* breads;
    int capacity;
    
public:
    BreadBucket(int capacity);
    
    bool init();
    
    void putBread(Bread* bread);
    
    Bread* getBread();
    
    ~BreadBucket();
    
};

#endif

