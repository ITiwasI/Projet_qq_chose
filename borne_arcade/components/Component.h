#ifndef COMPONENT_H_
#define COMPONENT_H_

virtual class Component
{
  public :
    Component();
    ~Component();    
    
	virtual void init(void);
};

#endif