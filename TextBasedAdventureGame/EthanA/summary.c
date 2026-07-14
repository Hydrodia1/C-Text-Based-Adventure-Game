#include <stdio.h>
#include "../SanchezG/SanchezG.h"


//prototype for displaySummary, which is defined in summary.c and called from main.c (GS)
void displaySummary(struct Player *player);

// This function displays the player's current stats and progress in the game, including health, defense, attack, rooms cleared, damage dealt, damage taken, and items used. It also includes a fun easter egg for certain "nice" numbers.
void displaySummary(struct Player *player) {
    printf("\n--=[%s's Progress]=--\n", player->name);
    if (player->health==69 || player->health==67 || player->health==420) {
        printf("♡ Health: %d Ha, nice\n", player->health); 
    }
    else if (player->health < 10) {
        printf("♡ Health: %d Yikes! A little low\n", player->health);
    }
    else {
        printf("♡ Health: %d\n", player->health);
    }

    /* if (player->defense==69 || player->defense==67 || player->defense==420) {
        printf("🛡 Defense: %d Ha, nice\n", player->defense); 
    }
    else if (player->defense < 10) {
        printf("🛡 Defense: %d Yikes! A little low\n", player->defense);
    }
    else {
        printf("🛡 Defense: %d\n", player->defense);
    } */
    
    if (player->attack==69 || player->attack==67 || player->attack==420) {
        printf("⚔ Attack: %d Ha, nice\n", player->attack); 
    }
    else if (player->attack < 10) {
        printf("⚔ Attack: %d Yikes! A little low\n", player->attack);
    }
    else {
        printf("⚔ Attack: %d\n", player->attack);
    }
    
    printf("𖠿 Rooms Cleared: %d\n", player->roomClearedCounter);
    
    if (player->damageDealtCounter==69 || player->damageDealtCounter==67 || player->damageDealtCounter==420) {
        printf("✦ Damage Dealt: %d Ha, nice\n", player->damageDealtCounter); 
    }
    else {
        printf("✦ Damage Dealt: %d\n", player->damageDealtCounter);
    }

    if (player->damageTakenCounter==69 || player->damageTakenCounter==67 || player->damageTakenCounter==420) {
        printf("☠︎︎ Damage Taken: %.2f Ha, nice\n", player->damageTakenCounter); 
    }
    else {
        printf("☠︎︎ Damage Taken: %.2f\n", player->damageTakenCounter);
    }

    if (player->itemUsedCounter==69 || player->itemUsedCounter==67 || player->itemUsedCounter==420) {
        printf("⚱𐃯 Items Used: %d Ha, nice\n", player->itemUsedCounter); 
    }
    else {
        printf("⚱𐃯 Items Used: %d\n", player->itemUsedCounter);
    }

    printf("--=[   End Summary   ]=--\n");
}