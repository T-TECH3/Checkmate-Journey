#include "iostream"
#include "NPC.h"
#include "Utility_Function.h"
#include "Game.h"
#include "Linked_List_Item.h"

// Default constcotr
NPC::NPC() : Character()
{
    m_name = "Blank Name";

    m_menu_options [0] = "View Stats";
    m_menu_options [1] = "Back";

    for (int i = 2; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 2;

    return;
}


// Custom constuctor
NPC::NPC(string piece_symbol, int row_coord, int column_coord, int r_color, int g_color, int b_color, int health, int attack, int money, string name) : Character (piece_symbol, row_coord, column_coord, r_color, g_color, b_color, health, attack, money)
{
    m_name = name;

    m_menu_options [0] = "View Stats";
    m_menu_options [1] = "Back";

    for (int i = 2; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 2;

    return;
}

// Deconstuctor
NPC::~NPC()
{
    return;
}

// Get methods for all members
string NPC::get_name()
{
    return m_name;
}

string NPC::get_option(int i)
{
    return m_menu_options[i];
}

int NPC::get_number_of_options()
{
    return m_number_of_options;
}

Linked_List_Item* NPC::get_inventory()
{
    return m_inventory;
}

// Set methods for all members
void NPC::set_name(string name)
{
    m_name = name;
    return;
}

void NPC::set_option(string menu_options [9])
{
    for (int i = 0; i < 9; i++)
    {
        m_menu_options [i] = menu_options [i];
    }

    return;
}

void NPC::set_number_of_options(int number_of_options)
{
    m_number_of_options = number_of_options;
    return;
}

void NPC::set_inventory(Linked_List_Item* inventory)
{
    m_inventory = inventory;
    return;
}

// Interact menu
bool NPC::interact_menu(Player* player,  Queue_NPC* npc_queue)
{
    // Dispaly the options an return (this function = 0_
    string question = m_name + " - Please Choose an Option:";

    int menu_answer = display_menu(question, m_number_of_options, m_menu_options, true);

    if (menu_answer == 0)
    {
        void (system("CLS"));
        display_stats();
        cout << endl << "Press A to continue..." << endl;
        Game::game_controller.wait_until_button_a_input();
        void (system("CLS"));
    }

    return false;
}

// Display name and NPC stats
void NPC::display_stats()
{
    cout << "<----------" << m_name << " - Stats:---------->" << endl;
    Character::display_stats(false);
    return;
}
