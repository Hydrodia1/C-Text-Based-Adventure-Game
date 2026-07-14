#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SanchezG.h"
#include "../HaydenS/HaydenS.h"




// Hardcoded array of room data to act as the default "New Game" state
struct Room testRooms[10] = {
    // ROOM 1: Aetherion
    {"Aetherion", "\"The Pale Dawning World\". A small, pearly-white world wrapped in sparkling clouds that drift from East to West. The surface of this planet glows like a dim candle, giving the planet a sense of pleasant warmth of an early morning.", 
        {{"Apple", "A juicy red apple.", 5}, {"Bread", "A loaf of bread.", 10}, {"\0", "", 0}}, 
        {{"Luminthos", "A slender humanoid with translucent skin and veins of gold that pulsate like the wick of a candle in the dead of night. It carries a dawnlight staff with a neon green egg held with 4 prongs of gold. It is less for combat and more for ceremonial purposes.", 15, 5, 1.0}}},

    // ROOM 2: Pelagora
    {"Pelagora", "\"The Aura of the Sea\". A world of beautiful turquoise oceans that seem to hum harmonies of celestial songs. Below the water are vast coral forests of every color imaginable.", 
        {{"Small Oxygen Tank", "A small oxygen tank.", 25}, {"Apple", "A juicy red apple.", 5}, {"Bread", "A loaf of bread.", 10}}, 
        {{"Okeanidron", "A serpentine titan with magenta, teal, and purple scales and a crest in the center of its chest in the shape of a wave. It moves with fluidity in the water but becomes sluggish and floppy on land, almost like a fish not remembering how its legs work.", 20, 8, 1.5}}},

    // ROOM 3: Verdantis
    {"Verdantis", "\"The Living Grove\". A lush, emerald-colored world with trees of great magnitude that sway to create winds that yell into the night. Bioluminescent spores float in the air, lighting the planet as embers of a campfire would for humans on Earth.", 
        {{"Meat", "A piece of meat.", 20}, {"Apple", "A juicy red apple.", 5}, {"Bread", "A loaf of bread.", 10}}, 
        {{"Gaiaxyl", "A colossal, wooden titan with tree bark armor and pine-colored, glowing eyes that seem to wait with intensity and vast-patience. The titan has the ability to command the roots and vines of the forests, creating cracking and slow movements.", 35, 12, 3.0}}},

    // ROOM 4: Pyrokratos
    {"Pyrokratos", "\"The Ember Forge\". A volcanic and iron-rich world with molten rivers that stream in hues of burgundy and ember. Overhead, lightning storms crackle to illuminate the surface in fiery flashes.", 
        {{"Sword", "A sharp steel sword.", 30}, {"Armor", "Sturdy leather armor.", 40}, {"Small Oxygen Tank", "A small oxygen tank.", 25}}, 
        {{"Kronfyr", "A molten-skinned monster with armor plates of pure obsidian and a heart, burning like the furnace in a house. It wields a blazing scythe and can distort time briefly, giving the effect of the flicker in an unstable flame.", 55, 15, 4.5}}},

    // ROOM 5: Thalasson
    {"Thalasson", "\"The Sea of Islands\". A deep blue, oceanic globe dotted with varying singular, deserted islands. Almost like a big chocolate chip cookie with 5 mini chocolate chips.", 
        {{"Meat", "A piece of meat.", 20}, {"Small Oxygen Tank", "A small oxygen tank.", 25}, {"Bread", "A loaf of bread.", 10}}, 
        {{"Cyclops", "A large, single-eyed giant with a muscular, rugged build. His forehead pierced with a silver ring and grimacing facial expression.", 70, 20, 5.5}}},

    // ROOM 6: Borealune
    {"Borealune", "\"The Frosted Twilight\". A dim, icy world stuck in a perpetual dusk. Storms of ice crystals sweep profusely across the plans, scattering light like glass caught in a sharp breeze.", 
        {{"Big Oxygen Tank", "A large oxygen tank.", 50}, {"Armor", "Reinforced armor.", 60}, {"Meat", "A piece of meat.", 20}}, 
        {{"Hyperboreon", "Massive frost giant with glacier-cracked skin and a long mane of drifting snow. It channels the cold and freezes the ground beneath its feet with each step it takes.", 90, 28, 6.5}}},

    // ROOM 7: Tempestrix
    {"Tempestrix", "\"The Shattered Sky\". A storm-ridden world where islands float in the air like tufts of dandelion float after blowing it out. Here, cyclones twist across the horizon, sculpting the sky into shifting shapes.", 
        {{"Big Oxygen Tank", "A large oxygen tank.", 50}, {"Sword", "A balanced longsword.", 70}, {"Meat", "A piece of meat.", 20}}, 
        {{"Koios", "A four-armed titan with storm-cloud skin and lightning-veined muscles. Koios can command the thunder and pressure with an arm gesture. Each strike cracking the air like a drummer would to snare.", 120, 32, 8.0}}},

    // ROOM 8: Obscuron
    {"Obscuron", "\"The Void Mire\". A shadow-drenched world full of black marshes and hovering gray, obsidian monoliths. The sky resembles a cracked mirror, only reflecting the darkness and glimmers of the Ereboros’s victims.", 
        {{"Big Oxygen Tank", "A large oxygen tank.", 50}, {"Armor", "Full plate mail.", 100}, {"CAKE!!!!", "A delicious cake.", 50}}, 
        {{"Ereboros", "A shifting, shadow titan with no fixed form. Its silhouette ripples like a cloud of smoke trying to take shape. Has the ability to manipulate darkness and can create illusions of false forms to trick its victims.", 160, 38, 10.0}}},

    // ROOM 9: Tartarion
    {"Tartarion", "\"The Abyssal Core\". A colossal, unstable planet with cracked crust which exposed oceans of magma that churn under the surface like a palpitating heartbeat. Gravity fluctuates, which tugs at everything in an uneven manner.", 
        {{"CAKE!!!!", "A delicious cake.", 50}, {"Big Oxygen Tank", "A large oxygen tank.", 50}, {"Big Oxygen Tank", "A large oxygen tank.", 50}}, 
        {{"Tytanomachus", "A gargantuan titan of pure magma and stone, radiating pressure like a mountain learning to breathe deeply. Has the ability to regenerate rapidly and can yield seismic power, capable of reshaping continents in seconds.", 210, 45, 12.0}}},

    // ROOM 10: Vantacrus
    {"Vantacrus", "\"The Crossroad of Darkness\". A blackhole. An invisible region of space where gravity is so powerful, only the almighty can escape Kronos’s wrath.", 
        {{"The Overlord's Cape", "A trophy of your victory.", 0}, {"Broken Scepter", "It no longer holds any power.", 0}, {"CAKE!!!!", "The legendary reward.", 0}}, 
        {{"Kronos", "The Final Boss. A destroyer, darker than shadows with eyes of pure fury and fire. A void of evil that even the black hole glows to expose his silhouette.", 400, 65, 18.0}}}
};

// Global pointer for the active room list
struct Room *rooms = NULL;

/**
 * Dynamically allocates memory for the rooms array and populates it with default data.
 * Uses calloc to ensure all fields are zero-initialized before copying testRooms.
 */
void initializeRooms(void) {
    // 1. Allocate memory for the 10 rooms
    rooms = (struct Room *)calloc(10, sizeof(struct Room));
    if (rooms == NULL) {
        printf("Error: Could not allocate memory for rooms.\n");
        return;
    }

    // 2. Check if the "rooms.txt" file exists by trying to open it
    FILE *file = fopen("rooms.txt", "r");
    
    if (file != NULL) {
        // --- FILE EXISTS ---
        fclose(file); // Close it here so load function can open it normally
        
        // Call your existing load function to populate the 'rooms' array
        loadRoomsFromFile(); 
        // printf("Rooms successfully loaded from rooms.txt!\n"); // Optional debug message
    } else {
        // --- FILE DOES NOT EXIST ---
        // Load the hardcoded defaults
        for( int i = 0; i < 10; i++) {
            rooms[i] = testRooms[i];
        }
        
       
    }
}

/**
 * Saves the current state of the dungeon (items remaining, enemy health) to rooms.txt.
 * Uses a pipe-delimited format (|) to make parsing easier for loadRoomsFromFile.
 */void writeRoomsToFile(void) {
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save game.\n");
        return;
    }

    for (int i = 0; i < 10; i++) {
        fprintf(file, "Room: %s\n", rooms[i].name);
        fprintf(file, "Desc: %s\n", rooms[i].description);
            
        // Loop through the 3 item slots per room

        for (int j = 0; j < 3; j++) {
            fprintf(file, "I:%s|%s|%d\n", 
                    rooms[i].items[j].name, 
                    rooms[i].items[j].description, 
                    rooms[i].items[j].value);
        }

        // Save enemy stats: Name, Desc, HP, ATK, DEF

        fprintf(file, "E:%s|%s|%d|%d|%.2f\n", 
                rooms[i].enemies[0].name, 
                rooms[i].enemies[0].description, 
                rooms[i].enemies[0].health, 
                rooms[i].enemies[0].attack, 
                rooms[i].enemies[0].defense);
        fprintf(file, "---\n");
    }
    fclose(file);
    printf("Dungeon state saved successfully to rooms.txt\n");
}

// Reads the file from rooms.txt and populates the rooms struct instance
void loadRoomsFromFile(void) {
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) {
        printf("No save file found. Initializing default dungeon.\n");
        return;
    }

    char buffer[256];
    for (int i = 0; i < 10; i++) {
   
        fscanf(file, "Room: %[^\n]\n", rooms[i].name);
        fscanf(file, "Desc: %399[^\n]\n", rooms[i].description);
        
        for (int j = 0; j < 3; j++) {
            // Parses pipe-delimited item data
            fscanf(file, "I:%49[^|]|%199[^|]|%d\n", 
                   rooms[i].items[j].name, 
                   rooms[i].items[j].description, 
                   &rooms[i].items[j].value);
        }
        
        // Parses pipe-delimited enemy data
  
        fscanf(file, "E:%49[^|]|%399[^|]|%d|%d|%f\n", 
               rooms[i].enemies[0].name, 
               rooms[i].enemies[0].description, 
               &rooms[i].enemies[0].health, 
               &rooms[i].enemies[0].attack, 
               &rooms[i].enemies[0].defense);
        
        fgets(buffer, sizeof(buffer), file); //Consume the "---" separator line
    }

    fclose(file);
   // printf("Dungeon state loaded!\n");
}

/**
 * Debug function to print all room data to the console to ensure loading worked correctly.
 */
void verifyRoomsLoaded(void) {
    printf("\n--- VERIFYING ROOM DATA LOADED ---\n");
    for (int i = 0; i < 10; i++) {
        printf("Room %d: %s\n", i + 1, rooms[i].name);
        printf("Description: %s\n", rooms[i].description);
        
        printf("  Items:\n");
        for (int j = 0; j < 3; j++) {
            if (strlen(rooms[i].items[j].name) > 0) {
                printf("    [%d] %s - %s (Value: %d)\n", 
                       j + 1, rooms[i].items[j].name, rooms[i].items[j].description, rooms[i].items[j].value);
            } else {
                printf("    [%d] [EMPTY SLOT]\n", j + 1);
            }
        }

        printf("  Enemy Info:\n");
        printf("    Name: %s\n", rooms[i].enemies[0].name);
        printf("    Name: %s\n", rooms[i].enemies[0].description);

        printf("    Stats: HP: %d | ATK: %d | DEF: %.2f\n", 
               rooms[i].enemies[0].health, 
               rooms[i].enemies[0].attack, 
               rooms[i].enemies[0].defense);
        printf("----------------------------------\n");
    }
}  

/**
 * Displays all items and the enemy present in the current room to the player.
 */
void scanRoomItems(int roomIndex) {
    printf("Items in the room:\n");
    for (int i = 0; i < 3; i++) {
        if (strlen(rooms[roomIndex].items[i].name) > 0) {
            printf("  Item %d: %s\n", i + 1, rooms[roomIndex].items[i].name);
            printf("  Description: %s\n", rooms[roomIndex].items[i].description);
            printf("  Value: %d\n", rooms[roomIndex].items[i].value);
        }
    }
    printf("Monster in the room: %s\n", rooms[roomIndex].enemies[0].name);
    
    // --- MONSTER DESCRIPTION ---
    printf("Monster description: ");
    printWrapped(rooms[roomIndex].enemies[0].description);
    printf("\n"); 
    
    printf("Monster's health: %d\n", rooms[roomIndex].enemies[0].health);
}

/**
 * Transfers an item from the room's array to the player's inventory array.
 * Includes a "Pick Up All" option for efficiency.
 */
void pickUpItem(int roomIndex, struct Player *player) {
    if (rooms[roomIndex].enemies[0].health > 0) {
        printf("You cannot pick up items until you defeat the %s!\n", rooms[roomIndex].enemies[0].name);
        return;
    }

    printf("\nAvailable items to pick up:\n");
    int availableCount = 0;
    for (int i = 0; i < 3; i++) {
        if (strlen(rooms[roomIndex].items[i].name) > 0) {
            printf("%d. %s (%s)\n", i + 1, rooms[roomIndex].items[i].name, rooms[roomIndex].items[i].description);
            availableCount++;
        }
    }

    if (availableCount == 0) {
        printf("The room is empty.\n");
        return;
    }

    printf("9. PICK UP ALL ITEMS\n");
    printf("0. Cancel\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear buffer after scanf to avoid skipping fgets later

    if (choice == 0) return;

    if (choice == 9) {
        for (int i = 0; i < 3; i++) {
            if (strlen(rooms[roomIndex].items[i].name) > 0) {
                int emptySlot = -1;
                // Search player inventory for an empty slot (name length 0)
                for (int j = 0; j < 20; j++) {
                    if (strlen(player->inventory[j].name) == 0) {
                        emptySlot = j;
                        break;
                    }
                }

                if (emptySlot != -1) {
                    strcpy(player->inventory[emptySlot].name, rooms[roomIndex].items[i].name);
                    strcpy(player->inventory[emptySlot].description, rooms[roomIndex].items[i].description);
                    player->inventory[emptySlot].value = rooms[roomIndex].items[i].value;
                    printf("Picked up: %s\n", player->inventory[emptySlot].name);

                    rooms[roomIndex].items[i].name[0] = '\0';// Remove from room
                } else {
                    printf("Inventory full!\n");
                    break; 
                }
            }
        }
    } 
    // if user wants to pick up just one item
    else if (choice >= 1 && choice <= 3) {
        int itemIdx = choice - 1;
        if (strlen(rooms[roomIndex].items[itemIdx].name) == 0) {
            printf("Item no longer there.\n");
            return;
        }
        // find the empty slot
        int emptySlot = -1;
        for (int j = 0; j < 20; j++) {
            if (strlen(player->inventory[j].name) == 0) {
                emptySlot = j;
                break;
            }
        }
        // put the item in that empty slot
        if (emptySlot != -1) {
            strcpy(player->inventory[emptySlot].name, rooms[roomIndex].items[itemIdx].name);
            strcpy(player->inventory[emptySlot].description, rooms[roomIndex].items[itemIdx].description);
            player->inventory[emptySlot].value = rooms[roomIndex].items[itemIdx].value;
            printf("Added %s to inventory.\n", player->inventory[emptySlot].name);

            rooms[roomIndex].items[itemIdx].name[0] = '\0';// Remove from room
        } else {
            printf("Your inventory is full!\n");
        }
    }
}

/**
 * Transfers an item from the player's inventory back to one of the 3 room slots.
 */
void dropItem(int roomIndex, struct Player *player) {
    displayInventory(player);
    int hasItems = 0;
    for (int i = 0; i < 20; i++) {
        if (strlen(player->inventory[i].name) > 0) {
            hasItems = 1;
            break;
        }
    }
    if (!hasItems) return;

    int choice;
    printf("\nEnter item number to drop (1-20, or 0 to cancel): ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clears buffer after scanf

    if (choice < 1 || choice > 20) return;

    int invIdx = choice - 1; 
    if (strlen(player->inventory[invIdx].name) == 0) return;

    // Search for an empty slot in the room to place the dropped item
    int roomSlot = -1;
    for (int i = 0; i < 3; i++) {
        if (strlen(rooms[roomIndex].items[i].name) == 0) {
            roomSlot = i;
            break;
        }
    }
    // drop the item the user picked and put it into an emtpy slot in the room
    if (roomSlot != -1) {
        strcpy(rooms[roomIndex].items[roomSlot].name, player->inventory[invIdx].name);
        strcpy(rooms[roomIndex].items[roomSlot].description, player->inventory[invIdx].description);
        rooms[roomIndex].items[roomSlot].value = player->inventory[invIdx].value;

        printf("Dropped: %s\n", rooms[roomIndex].items[roomSlot].name);
        player->inventory[invIdx].name[0] = '\0';// Remove from player
    } else {
        printf("No room here to drop items.\n");
    }
} 

/**
 * Loops through the 20 inventory slots and prints any that contain a valid item name.
 */
void displayInventory(struct Player *player) {
    printf("Player Inventory:\n");
    for (int i = 0; i < 20; i++) {
        if (strlen(player->inventory[i].name) > 0) { 
            printf("Item %d: %s | Val: %d\n", i + 1, player->inventory[i].name, player->inventory[i].value);
        }
    }
}

/**
 * Increments the room index if the enemy has been defeated.
 * Bounds-checking ensures the player doesn't move past the final room.
 */
void moveToNextRoom(int *currentRoomIndexPtr) {
    if (rooms[*currentRoomIndexPtr].enemies[0].health <= 0) {
        if (*currentRoomIndexPtr < 9) {
            (*currentRoomIndexPtr)++;
            printf("You move to: %s\n", rooms[*currentRoomIndexPtr].name);
            clearscreen();
        } else {
            printf("You are at the end!\n");
        }
    } else {
        printf("Defeat the enemy first!\n");
    }
    
}


/**
 * Saves the player's individual stats and inventory to savegame.txt.
 * Uses "I:EMPTY" as a placeholder for unused inventory slots.
 */
void saveGame(struct Player *player) {
    int slot;
    
    // 1. Ask the user for the slot
    printf("Which slot would you like to save to? (1, 2, or 3): ");
    
    // 2. Read the input and check if it's a valid number
    if (scanf("%d", &slot) != 1) {
        printf("Invalid input. Save canceled.\n");
        // Clear the input buffer so the main loop doesn't break
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        return;
    }

    // Clear the input buffer of the newline character left by scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // 3. Validate the slot number
    if (slot < 1 || slot > 3) {
        printf("Invalid save slot! Save canceled.\n");
        return;
    }

    // 4. Generate the filename based on the slot (e.g., "savegame_1.txt")
    char filename[32];
    sprintf(filename, "savegame_%d.txt", slot);

    // 5. Open and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    fprintf(file, "PlayerName: %s\n", player->name);
    fprintf(file, "Health: %d\n", player->health);
    fprintf(file, "Defense: %d\n", player->defense);    
    fprintf(file, "Attack: %d\n", player->attack);

    for (int i = 0; i < 20; i++) {
        if (strlen(player->inventory[i].name) > 0) {
            fprintf(file, "I:%s|%s|%d\n", 
                    player->inventory[i].name, player->inventory[i].description, player->inventory[i].value);
        } else {
            fprintf(file, "I:EMPTY|EMPTY|0\n");
        }
    }   
    
    fprintf(file, "RoomsCleared: %d\n", player->roomClearedCounter);
    fprintf(file, "DamageDealt: %d\n", player->damageDealtCounter);
    fprintf(file, "DamageTaken: %.2f\n", player->damageTakenCounter);
    fprintf(file, "ItemsUsed: %d\n", player->itemUsedCounter);
    fprintf(file, "CurrentRoomIndex: %d\n", player->currentRoomIndex);
    
    fclose(file);
    printf("Game saved to slot %d!\n", slot);
} 

// loads the file based on the users input
void loadGame(struct Player *player) {
    int slot;

    // 1. Ask the user for the slot
    printf("Which slot would you like to load from? (1, 2, or 3): ");

    // 2. Read the input and check if it's a valid number
    if (scanf("%d", &slot) != 1) {
        printf("Invalid input. ");
        // Clear the input buffer so the main loop doesn't break
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        
        // Fallback to new game
        newGame(player);
        return;
    }

    // Clear the input buffer of the newline character left by scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // 3. Validate the slot number
    if (slot < 1 || slot > 3) {
        printf("\nInvalid load slot! \n");
        
        // Fallback to new game
        newGame(player);
        return;
    }

    // 4. Generate the filename based on the slot (e.g., "savegame_1.txt")
    char filename[32];
    sprintf(filename, "savegame_%d.txt", slot);

    // 5. Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Give the player a clear message if the file doesn't exist yet
        printf("No save data found in slot %d. ", slot);
        
        // Fallback to new game
        newGame(player);
        return;
    }

    // 6. Read the data
    fscanf(file, "PlayerName: %[^\n]\n", player->name);
    fscanf(file, "Health: %d\n", &player->health);
    fscanf(file, "Defense: %d\n", &player->defense);    
    fscanf(file, "Attack: %d\n", &player->attack);

    for (int i = 0; i < 20; i++) {
        char itemLine[256];
        if (fgets(itemLine, sizeof(itemLine), file) != NULL) {
            if (strncmp(itemLine, "I:EMPTY", 7) == 0) {
                player->inventory[i].name[0] = '\0';
            } else {
                sscanf(itemLine, "I:%[^|]|%[^|]|%d\n", 
                       player->inventory[i].name, 
                       player->inventory[i].description, 
                       &player->inventory[i].value);
            }
        }
    }

    fscanf(file, "RoomsCleared: %d\n", &player->roomClearedCounter);
    fscanf(file, "DamageDealt: %d\n", &player->damageDealtCounter);
    fscanf(file, "DamageTaken: %f\n", &player->damageTakenCounter); 
    fscanf(file, "ItemsUsed: %d\n", &player->itemUsedCounter);
    fscanf(file, "CurrentRoomIndex: %d\n", &player->currentRoomIndex);

    fclose(file);
    printf("Game loaded from slot %d!\n", slot);
}

// Automatically wraps text around 60 characters
void printWrapped(const char* desc) {
    if (desc == NULL) return;
    
    int line_length = 0;
    
    for (int i = 0; desc[i] != '\0'; i++) {
        // If we've printed 60 or more characters AND the current character is a space...
        if (line_length >= 60 && desc[i] == ' ') {
            printf("\n");    // ...print a new line instead of the space
            line_length = 0; // ...and reset our character counter
        } else {
            putchar(desc[i]); // Otherwise, just print the character normally
            line_length++;
        }
    }
}

void clearscreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
     


