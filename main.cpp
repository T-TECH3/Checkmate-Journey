// Author: Thomas Corkery
// Project Description: This is a dungon crawler video game controller by a x box controller use STUFF learnt in ICS4U
// Date Created: 21/12/2024
// Date modified: 18/1/2025

// Author: T TECH
// Project: Checkmate Journey
// Lisence: MIT License
// Date Created: 21/12/2024
// Date Modified: 18/1/2025
/*
 _______              _______      _______      _______      __   __
/\__  __\            /\__  __\    /\    __\    /\   ___\    /\ \ /\ \
\/_/\ \_/            \/_/\ \_/    \ \   \_/_   \ \  \__/    \ \ \\_\ \
   \ \ \                \ \ \      \ \    __\   \ \  \       \ \  ___ \
    \ \ \                \ \ \      \ \   \_/_   \ \  \____   \ \ \_/\ \
     \ \_\                \ \_\      \ \______\   \ \______\   \ \_\\ \_\
      \/_/                 \/_/       \/______/    \/______/    \/_/ \/_/
*/

#include <iostream>
#include <windows.h>
#include <cwchar>
#include <cstdlib>
#include "Utility_Function.h"
#include "Screen.h"
#include "Player.h"
#include "Game.h"
#include "SDL.h"

using namespace std;

// SDL2 needs there in main to run
int main(int argc, char *argv[])
{
    int main_menu_option = -1;
    bool quit = false;

    // Set up the for using unicode characers
    system("chcp 65001");

    // Clear the screen
    void (system("CLS"));

    // Remove the cursor from the console
    show_cursor(false);

    // Create arrays of options for the two different menus
    string options [9] = {"New Game", "AI Game", "How To Play", "Quit", "", "", "", "", ""};
    string options_resume [9] = {"New Game", "Resume Game", "AI Game", "How To Play", "Quit", "", "", "", ""};

    // Create a game
    Game* game_1 = nullptr;

    // Change the console color to white
    console_color(255, 255, 255);

    // Output a warning and a game intro
    cout << "<-------------------------------Warning: Console must be 120+ characters Wide (This Size)------------------------------>" << endl << endl;
    cout << "Welcome to Checkmate Journey!" << endl << endl << "You, the White King will embark on wild journey to save your kingdom." << endl;
    cout << "The Dark King has " << "captured your army and queen. Through out the maze," << endl <<  "you will have to bravely fight";
    cout << " the dark king's army. Your army is" << endl << "stuck in the maze, they can help you gear up and prepare for the epic" << endl << "battle. ";
    cout << "Defeat the Dark King and save your queen." << endl << endl << "Good luck!" << endl << endl;

    // Wait until the A button is pressed to continue
    cout << "Press A to continue..." << endl;
    Game::game_controller.wait_until_button_a_input();

    // Run the main menu until the quit option is picked
    do
    {
        // Display the main menu depending on if there is a game in progress
        if (game_1 == nullptr)
        {
            main_menu_option = display_menu("<---Checkmate Journey - Start Menu:--->", 4, options, true);

            // Ajust the option so the options choice maches with the second menu choices
            if (main_menu_option != 0)
            {
                main_menu_option++;
            }

        }
        else
        {
            main_menu_option = display_menu("<---Checkmate Journey - Start Menu:--->", 5, options_resume, true);
        }

        // If the option is 0 create a game
        if (main_menu_option == 0)
        {
            delete game_1;

            game_1 = new Game();
            game_1->load_screens(false);

            // Delete the game if the player has died
            if (game_1->run_game() == true)
            {
                delete game_1;
                game_1 = nullptr;
            }

        }
        // If the option is 1 resume the current game
        else if (main_menu_option == 1)
        {
            if (game_1->run_game() == true)
            {
                delete game_1;
                game_1 = nullptr;
            }
        }
        // If the option is 2 run the auto maze solver
        else if (main_menu_option == 2)
        {
            Game* game_2 = new Game();
            game_2->load_screens(true);
            game_2->run_maze_solver();
            delete game_2;
        }
        // If the option is 3 display how to play
        else if (main_menu_option == 3)
        {
            void (system("CLS"));

            cout << "<-------------CONTROLS:------------->" << endl;
            cout << "Left Joy: Movement/Menu Selection" << endl;
            cout << "Button Pad: Interact - Door, NPC, Item (with direction pressed)" << endl;
            cout << "Y Button: Fast Movement (Hold)" << endl;
            cout << "B Button: Start Menu" << endl;
            cout << "A Button: Select" << endl;
            cout << "X Button: Player Stats/Inventory/Other" << endl << endl;

            cout << "Press A to continue..." << endl;

            Game::game_controller.wait_until_button_a_input();
        }
        // If the option is 4 quit the game
        else if (main_menu_option == 4)
        {
            quit = true;
        }

        main_menu_option = -1;

    } while (quit == false);

    return 0;
}
