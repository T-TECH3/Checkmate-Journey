#include "Informant.h"
#include "Game.h"
#include "Utility_Function.h"

// Default constctor
Informant::Informant() : NPC()
{
    m_menu_options[0] = "End Game";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 3;

    return;
}

// Custom constuctor
Informant::Informant(string piece_symbol, int row_coord, int column_coord, int r_color, int g_color, int b_color, string name) : NPC(piece_symbol, row_coord, column_coord, r_color, g_color, b_color, 1, 1, 0, name)
{
    m_menu_options[0] = "End Game";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 3;

    return;
}

// Deconstuctor
Informant::~Informant()
{
    return;
}

// Interact menu
bool Informant::interact_menu(Player* player, Queue_NPC* npc_queue)
{
    string question =  "<--" + m_name + " - Please Choose an Option:" + "-->";
    bool player_die = false;
    int menu_answer;

    do
    {
        // Call the option chooser
        menu_answer = display_menu(question, m_number_of_options, m_menu_options, true);

        // Based on the choice all the correct function
        if (menu_answer == 0)
        {
            void (system("CLS"));
            cout << "<---Game Over:--->" << endl << "You win!" << endl << "Thank you for playing Checkmate Journey" << endl << endl;

            cout << "Press A to end game..." << endl;
            Game::game_controller.wait_until_button_a_input();
            void (system("CLS"));

            return true;
        }
        else if (menu_answer == 1)
        {
            void (system("CLS"));
            display_stats();
            cout << endl << "Press A to continue..." << endl;
            Game::game_controller.wait_until_button_a_input();
            void (system("CLS"));
        }

    } while (menu_answer != 2);

    return player_die;
}

// Display stats
void Informant::display_stats()
{
    // Display calls stats and character stats
    cout << "<----------" << m_name << " - Stats:---------->" << endl;
    cout << "Type: Informant" << endl;
    Character::display_stats(false);
    return;
}

