#ifndef BREADBASKET_H
#define	BREADBASKET_H

#include <queue>
#include <semaphore.h>
#include "BreadContainer.h"
#include "Bread.h"

using namespace std;

class BreadBasket : public BreadContainer {
    
private:
    queue<Bread*>* breads;
    int capacity;
    sem_t state;
    
public:
    BreadBasket(int capacity);
    
    bool init();
    
    void putBread(Bread* bread);
    
    Bread* getBread();
    
    ~BreadBasket();
};

#endif

