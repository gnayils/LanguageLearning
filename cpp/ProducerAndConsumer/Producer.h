#ifndef PRODUCER_H
#define	PRODUCER_H

#include "Thread.h"
#include "BreadContainer.h"

class Producer : public Thread{
    
private:
    BreadContainer* breadContainer;
        
public:
    Producer(BreadContainer* breadContainer);
    
    void run();
    
    ~Producer();
};

#endif