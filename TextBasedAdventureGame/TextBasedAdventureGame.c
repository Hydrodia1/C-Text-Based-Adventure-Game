// Text Based Adventure Game
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // Added for random combat damage

/* --- Group Module Includes --- */
// Direct inclusion of .c files is used here to link the group's logic into one executable
#include "HaydenS/HaydenS.c"
#include "HaydenS/HaydenS.h"
#include "SanchezG/SanchezG.h"
#include "SanchezG/TextBasedAdventureGameGS.c"
#include "TristinR/textbasedadventureGame.c"
#include "TristinR/TristinR.h" 
#include "EthanA/summary.c"


/**
 * Main entry point for the Space Traveling Adventure.
 * Handles game initialization, the main command loop, and game termination.
 */
int main() {
    // Seed the random number generator so combat damage is different every time
    srand(time(NULL));

    // --- Variable Initialization ---
    char userInput[50];     // Buffer for the start menu
    char gameUserInput[50]; // Buffer for in-game commands
    int currentRoomIndex = 0;

    // Allocate memory and setup default room data (Items, Enemies, Descriptions)
    initializeRooms();

    // --- Player Initialization & Menu ---
    struct Player player;

    //Welcome Message
    printf("\nWelcome to Starlight Voyager.\n");

    //ask user if they want to continue with a previous game or start a new game or quit the game
    printf("Choose an option:\nNew Game\nContinue\nQuit\nEnter your choice: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0; // Strip newline immediately

    // Process menu selection
    if (strcasecmp(userInput, "New Game") == 0) {
        newGame(&player);
    }
    else if (strcasecmp(userInput, "Continue") == 0) {
        printf("Continuing from the previous game...\n");
        loadGame(&player);
        // Sync the local currentRoomIndex with the loaded player data
        currentRoomIndex = player.currentRoomIndex;
        printf("Welcome back to your Space Traveling adventure, %s!\n", player.name);
    } 
    else if (strcasecmp(userInput, "Quit") == 0) {
        printf("Quitting the game. Goodbye!\n");
        return 0;
    } else {
        printf("Invalid choice. Defaulting to New Game.\n");
        newGame(&player);
    }

    // Clear the screen right before the main game loop starts
    // so the transition from the main menu into the game is perfectly clean!
    clearscreen(); 

    // --- Main Game Loop ---
    // Loop continues as long as the player is alive and hasn't chosen to 'Quit'
    do {
        printf("\n============================================================"); 
        printf("\nLOCATION: %s", rooms[currentRoomIndex].name);
        
        printf("\nLOCATION Description: ");
        printWrapped(rooms[currentRoomIndex].description); 
        printf("\n============================================================"); 
        printf("\nWhat would you like to do?");
        printf("\n(Scan, Pickup, Drop, Move, Combat, Inventory, Save, Quit): ");

        fgets(gameUserInput, sizeof(gameUserInput), stdin);
        gameUserInput[strcspn(gameUserInput, "\n")] = 0; 

        // --- Command Logic ---
        if (strcasecmp(gameUserInput, "Scan") == 0) {
            scanRoomItems(currentRoomIndex);
        } 
        else if (strcasecmp(gameUserInput, "Pickup") == 0) {
            pickUpItem(currentRoomIndex, &player); 
        } 
        else if (strcasecmp(gameUserInput, "Drop") == 0) {
            dropItem(currentRoomIndex, &player);        
        }
        else if (strcasecmp(gameUserInput, "Move") == 0) {
            moveToNextRoom(&currentRoomIndex);
        } 
        else if (strcasecmp(gameUserInput, "Combat") == 0) {
            // Initiate turn-based combat with the enemy in the current room
            Combat(&player, &rooms[currentRoomIndex], 0);
        } 
        else if (strcasecmp(gameUserInput, "Inventory") == 0) {
            displayInventory(&player);
        } 
        else if (strcasecmp(gameUserInput, "Save") == 0) {
            // Update player index before saving to ensure they resume in the correct room
            player.currentRoomIndex = currentRoomIndex; 
            saveGame(&player);
        }   
        else if (strcasecmp(gameUserInput, "Quit") == 0) {
            printf("Thanks for playing, %s!\n", player.name);
            displaySummary(&player);// Show final stats
            break; 
        } 
        else {
            // This will only trigger if they actually type the wrong word
            printf("Invalid command. Use the options provided in parentheses.\n");
        }

    } while (player.health > 0);

    // --- Post-Game Cleanup ---
    if (player.health <= 0) {
        printf("\n--- YOU HAVE DIED --- \nBetter luck next time.\n");
        displaySummary(&player);
    }
    
    // Free the dynamically allocated rooms array from initializeRooms()
    free(rooms); 
    return 0;
}