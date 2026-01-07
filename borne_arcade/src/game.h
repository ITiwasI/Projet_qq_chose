#ifndef GAME_H_
#define GAME_H_
    
class game
{
  public :
    game();
    ~game();    
    
    virtual void init(&leftButton, &rightButton);
    virtual void run(void);
    
  protected :
    bool _quit;
};
#endif