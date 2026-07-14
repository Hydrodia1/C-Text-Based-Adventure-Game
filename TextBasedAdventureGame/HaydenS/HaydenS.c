#include <stdio.h>
#include <string.h>
#include "HaydenS.h"


//This function compares the item name to determine its effects on the player, such as increasing health or attack power.
void ItemUsageCmpString(struct Player *player, int itemIndex) {
    // Note: itemIndex is 1-based from the user, so we use [itemIndex - 1]
    char *itemName = player->inventory[itemIndex - 1].name;

    if (strcmp(itemName, "Big Oxygen Tank") == 0) {
        player->health = player->health * 2; 
        printf("Your health has been doubled!\n");
    } else if (strcmp(itemName, "Small Oxygen Tank") == 0) {
        player->health = (int)(player->health * 1.5); // Cast to int for health
        printf("Your health has been increased by 50%%!\n");
    } else if (strcmp(itemName, "Apple") == 0) {
        player->health += 5;
        printf("Your health has been increased by 5!\n");
    } else if (strcmp(itemName, "Bread") == 0) {
        player->health += 10;
        printf("Your health has been increased by 10!\n");
    } else if (strcmp(itemName, "Meat") == 0) {
        player->health += 20;
        printf("Your health has been increased by 20!\n");
    } else if (strcmp(itemName, "CAKE!!!!") == 0) {
        player->health += 50;
        printf("Your health has been increased by 50!\n");
    } else if (strcmp(itemName, "Sword") == 0) {
        player->attackMultiplier = 2; 
        printf("Your attack power has been doubled until the end of combat!\n");
    } else if (strcmp(itemName, "Armor") == 0){
        player->defense = 2;
        printf("You take half as much damage until the end of combat!\n");
    } else {
        printf("This item has no usable effect.\n");
    }
}

void ItemUsage(struct Player *player) {
    int itemIndex;
    printf("Enter the item number to use (1-20, or 0 to cancel): ");
    
    // Check if scanf succeeds and flush the buffer
    if (scanf("%d", &itemIndex) != 1) {
        while (getchar() != '\n'); // Clear bad input
        printf("Invalid input. Returning to combat.\n");
        return;
    }
    while (getchar() != '\n'); // Clear the newline

    if (itemIndex == 0) return;

    
    if (itemIndex >= 1 && itemIndex <= 20) {
        if (strlen(player->inventory[itemIndex - 1].name) > 0) {
            printf("You used: %s\n", player->inventory[itemIndex - 1].name);
            ItemUsageCmpString(player, itemIndex);
            
            // Clear the item after use
            player->inventory[itemIndex - 1].name[0] = '\0';
            player->inventory[itemIndex - 1].description[0] = '\0';                        
            player->inventory[itemIndex - 1].value = 0;
            player->itemUsedCounter += 1; 
        } else {
            printf("That inventory slot is empty!\n");
        }
    } else {
        printf("Invalid inventory index.\n");
    }
}

void newGame(struct Player *player) {
    printf("Starting a new game...\n");
    printf("Enter your name, adventurer: ");
    
    if (fgets(player->name, sizeof(player->name), stdin) != NULL) {
        // Strip the newline
        player->name[strcspn(player->name, "\n")] = 0;
    }

    // If the name ended up empty because of a leftover newline, try one more time
    if (strlen(player->name) == 0) {
        fgets(player->name, sizeof(player->name), stdin);
        player->name[strcspn(player->name, "\n")] = 0;
    }

    // --- Reset Player Stats ---
    player->health = 100;
    player->attack = 20;
    player->defense = 1;
    player->attackMultiplier = 1;
    player->roomClearedCounter = 0;
    player->damageDealtCounter = 0;
    player->damageTakenCounter = 0.0;
    player->itemUsedCounter = 0;
    player->currentRoomIndex = 0; // Ensure they start at Room 0

    // Clear inventory strings
    for (int i = 0; i < 20; i++) {
        player->inventory[i].name[0] = '\0';
        player->inventory[i].description[0] = '\0';
        player->inventory[i].value = 0;
    }

    printf("Welcome to your Space Traveling adventure, %s!\n", player->name);
}