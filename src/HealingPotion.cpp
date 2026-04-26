#include "player.h"

void drickHealingPotion(Player* owner) {
    owner->removeItem(HealingPotion, 1);
    owner->HP = std::min(owner->HP + 10, 10);
}