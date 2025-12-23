#ifndef GAME_H_
#define GAME_H_
    
class Game
{
  public :
    Game();
    ~Game();    
    
    virtual void init(void);
    virtual void run(void);
};
#endif