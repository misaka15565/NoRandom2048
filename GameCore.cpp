#define MAP_SIZE 4
#define MAX_TIMES 2000000000



class Gamemap
{
public:
    Gamemap();
    int map[MAP_SIZE][MAP_SIZE];
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    bool SetBlock(int x,int y,int n);
};

Gamemap::Gamemap(/* args */)
{
}
