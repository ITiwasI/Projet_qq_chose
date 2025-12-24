#ifndef COMPONENT_H_
#define COMPONENT_H_

class Component
{
  public :
    Component();
    ~Component();    
    
	virtual void init(void)=0;
};

#endif