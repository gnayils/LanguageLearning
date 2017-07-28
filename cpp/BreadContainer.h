#ifndef BREADCONTAINER_H
#define	BREADCONTAINER_H

#include "Bread.h"

class BreadContainer {
    
public:
    virtual bool init() = 0;
    
    virtual void putBread(Bread* bread) = 0;
    
    virtual Bread* getBread() = 0;
    
};

#endif

