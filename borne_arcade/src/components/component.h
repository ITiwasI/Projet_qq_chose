#ifndef COMPONENT_H_
#define COMPONENT_H_

class component
{
  public :
    component();
    ~component();    
	  virtual void init(void)=0;
};

#endif // COMPONENT_H_