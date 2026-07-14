# 🌌 Project Overview

This project is a comprehensive terminal-based RPG developed in C. It blends technical software engineering with detailed astronomical world-building.
Players navigate through a series of ten unique celestial bodies, managing resources and battling powerful titans to survive the journey through the cosmos. The game highlights the importance of modular programming and collaborative development.

🛠 Features
• Narrative-Driven Exploration: Journey through 10 handcrafted worlds, from the glowing clouds of Aetherion to the gravity-warping void of Vantacrus.
• Modular Architecture: Organized into distinct student modules, showcasing clean header/source separation and team-based coding practices.
• Dynamic Combat System: Features turn-based encounters with randomized damage calculations (80% to 120% variance), defense mitigation, and strategic mid-battle item usage.
• Save/Load Persistence: Support for three distinct save slots using custom file I/O to track player stats and inventory.
• Smart Dungeon State: The game tracks the "Dungeon" state independently, remembering which items have been removed from rooms or which enemies have been defeated.
• Session Summary: A final performance breakdown that tracks damage dealt, total rooms cleared, and items used (including hidden Easter eggs for specific stat values).

🎮 How to Play
Commands
• Scan: Inspect the current planet for items and enemy descriptions.
• Combat: Engage the local Titan in turn-based combat.
• Pickup/Drop: Manage your 20-slot inventory.
• Move: Advance to the next room (available only after the enemy is defeated).
• Inventory: Check your current gear and HP.
• Save: Store your progress in one of three save slots.
• Quit: Exit the game and view your final adventure summary.

Survival Tips
• Oxygen Tanks: Vital for survival. Small Tanks boost health by 50%, while Big Tanks double your current HP.
• Combat Gear: Equip Swords to double your attack power or Armor to reduce incoming damage by half.

🏗 Technical Specifications
• Language: C
• Memory: Utilizes dynamic memory allocation (calloc) for room data and proper free() routines for cleanup.
• Data Parsing: Custom pipe-delimited (|) file parsing for reading/writing game states.
• UI: Automated text wrapping (60-character limit) for immersive terminal reading.
🚀 Compilation & Installation

 1. Clone the Repository:

 2. Compile:  gcc TextBasedAdventureGame.c -o TextBasedAdventureGame


 3. Run:  .\TextBasedAdventureGame
