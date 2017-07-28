#ifndef CONSUMER_H
#define	CONSUMER_H

#include "Thread.h"
#include "BreadContainer.h"

class Consumer : public Thread {
    
private:
    BreadContainer* breadContainer;
    
public:
    Consumer(BreadContainer* breadContainer);
    
    void run();

    ~Consumer();
};


#endif

