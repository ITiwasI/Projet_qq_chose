#ifndef GAME_H_
#define GAME_H_
    
class game
{
  private :
    static int gameCount;
    char name[20];
    int id;
  public :
    game();
    ~game();
    virtual void init(void)=0;
    virtual void run(void)=0;
};
#endif // GAME_H_