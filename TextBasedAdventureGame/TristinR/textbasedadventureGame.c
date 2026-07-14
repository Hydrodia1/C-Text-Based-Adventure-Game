#include <stdio.h>
#include <string.h>
#include <strings.h> 
#include <stdlib.h>
#include <time.h> 

#include "../HaydenS/HaydenS.h"
#include "../SanchezG/SanchezG.h"
#include "TristinR.h"

void Combat(struct Player *player, struct Room *room, int enemyIndex) {
    struct Enemy *enemy = &room->enemies[enemyIndex];

    printf("\n--- Combat Started: %s vs %s ---\n", player->name, enemy->name);

    if (enemy->health <= 0) {
        printf("The %s is already defeated.\n", enemy->name);
        return;
    }

    while (player->health > 0 && enemy->health > 0) {
        printf("\n[ %s: %d HP | %s: %d HP ]\n", player->name, player->health, enemy->name, enemy->health);
        
        // --- CHECK IF INVENTORY IS EMPTY ---
        int hasItems = 0;
        for (int i = 0; i < 20; i++) {
            if (strlen(player->inventory[i].name) > 0) {
                hasItems = 1; // Found an item!
                break;        // No need to keep checking
            }
        }

        // Only ask to use an item if the player actually has items
        if (hasItems) {
            printf("Use an item before attacking? (yes/no): ");
            char useItemInput[10];
            
            // Using fgets instead of scanf to avoid input issues, and strcasecmp for case-insensitive comparison
            fgets(useItemInput, sizeof(useItemInput), stdin);
            useItemInput[strcspn(useItemInput, "\n")] = 0; 

            // accepts "YES", "Yes", "yes", etc.
            if (strcasecmp(useItemInput, "yes") == 0) {
                displayInventory(player);
                ItemUsage(player);        
            }
        }

        // --- PLAYER'S TURN ---
        int basePlayerAttack = player->attack * player->attackMultiplier;
        
        // Calculate random range (80% to 120%)
        int minPlayerAttack = (int)(basePlayerAttack * 0.8);
        int maxPlayerAttack = (int)(basePlayerAttack * 1.2);
        
        // Safety checks to prevent math errors
        if (minPlayerAttack < 1) minPlayerAttack = 1;
        if (maxPlayerAttack < minPlayerAttack) maxPlayerAttack = minPlayerAttack;
        
        // Generate actual random attack
        int actualPlayerAttack = (rand() % (maxPlayerAttack - minPlayerAttack + 1)) + minPlayerAttack;

        // Apply defense to the randomized attack
        int damageToEnemy = actualPlayerAttack - (int)enemy->defense;
        if (damageToEnemy < 1) damageToEnemy = 1; // Always deal at least 1 damage

        enemy->health -= damageToEnemy;
        if (enemy->health < 0) enemy->health = 0;

        player->damageDealtCounter += damageToEnemy; 

        printf("> You strike the %s for %d damage!\n", enemy->name, damageToEnemy);

        if (enemy->health <= 0) {
            printf("Victory! You have defeated the %s.\n", enemy->name);
            player->roomClearedCounter++; 
            break; 
        }

        // --- ENEMY'S TURN ---
        int baseEnemyAttack = enemy->attack;
        
        // Calculate random range (80% to 120%)
        int minEnemyAttack = (int)(baseEnemyAttack * 0.8);
        int maxEnemyAttack = (int)(baseEnemyAttack * 1.2);
        
        // Safety checks to prevent math errors
        if (minEnemyAttack < 1) minEnemyAttack = 1;
        if (maxEnemyAttack < minEnemyAttack) maxEnemyAttack = minEnemyAttack;
        
        // Generate actual random attack
        int actualEnemyAttack = (rand() % (maxEnemyAttack - minEnemyAttack + 1)) + minEnemyAttack;

        // Apply defense to the randomized attack
        int damageToPlayer = actualEnemyAttack / player->defense;
        if (damageToPlayer < 1) damageToPlayer = 1;

        player->health -= damageToPlayer;
        if (player->health < 0) player->health = 0;

        player->damageTakenCounter += (float)damageToPlayer; 

        printf("> The %s hits you for %d damage!\n", enemy->name, damageToPlayer);

        if (player->health <= 0) {
            printf("GAME OVER: You have been defeated by the %s...\n", enemy->name);
            break;
        }
    }
    
    // Stats Reset Section
    player->attackMultiplier = 1;
    player->defense = 1; 
    
    printf("--- Combat Ended ---\n\n");
}