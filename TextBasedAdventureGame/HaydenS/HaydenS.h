#ifndef HAYDENS_H
#define HAYDENS_H

#include "../SanchezG/SanchezG.h"

// Prototypes for functions defined in HaydenS.c
void ItemUsageCmpString(struct Player *player, int itemIndex);
void ItemUsage(struct Player *player);

// was missing this prototype for newGame, which is defined in HaydenS.c and called from main.c (GS)
void newGame(struct Player *player);

#endif