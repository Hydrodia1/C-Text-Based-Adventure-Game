#ifndef SANCHEZG_H
#define SANCHEZG_H

// --- Struct Definitions ---

struct Item {
    char name[50];
    char description[200]; 
    int value;
};

struct Enemy {
    char name[50];
    char description[400]; 
    int health;
    int attack;
    float defense;
};

struct Room {
    char name[50];
    char description[400]; 
    struct Item items[3];
    struct Enemy enemies[1];
};

struct Player {
    char name[50];
    int health;
    int defense;
    int attack;
    struct Item inventory[20];
    int itemUsedCounter; 
    int damageDealtCounter;
    float damageTakenCounter; 
    int attackMultiplier;
    int roomClearedCounter;
    int currentRoomIndex;
};

// --- Function Prototypes ---

// File I/O
void writeRoomsToFile(void);
void loadRoomsFromFile(void);

// Save/Load Game State
void saveGame(struct Player *player);
void loadGame(struct Player *player);

// Setup & Testing
void initializeRooms(void); 
void verifyRoomsLoaded(void);

// Gameplay Functions
void scanRoomItems(int roomIndex);

// Inventory Management
void pickUpItem(int roomIndex, struct Player *player); 

void dropItem(int roomIndex, struct Player *player);
void displayInventory(struct Player *player);

// traversal through rooms
void moveToNextRoom(int *currentRoomIndexPtr);


void printWrapped(const char* desc);

void clearscreen();

#endif