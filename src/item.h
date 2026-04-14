#include <vector>


void DrawItems();
enum Items {
    BombUpgrade,
};
struct ItemsOnGround  {
    Items item;
    int posx;
    int posy;
};
extern std::vector<ItemsOnGround> ItemsOngroundList;
void placeItem(Items item, int posx, int posy);