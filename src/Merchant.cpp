#include "Merchant.h"
#include "Utility_Function.h"
#include "Game.h"
#include "Linked_List_Item.h"
#include "Player.h"
#include "Item.h"
#include "Stats_Item.h"
#include "Item.h"

// Default constuctor
Merchant::Merchant() : NPC()
{
    m_menu_options[0] = "View Shop";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 3;

    m_regenerate_item = false;

    return;
}

// Custom constuctor
Merchant::Merchant(string piece_symbol, int row_coord, int column_coord, int r_color, int g_color, int b_color, string name, bool regenerate_item) : NPC(piece_symbol, row_coord, column_coord, r_color, g_color, b_color, 1, 1, 0, name)
{
    m_menu_options[0] = "View Shop";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 3;

    m_regenerate_item = regenerate_item;

    return;
}

// Deconstuctor
Merchant::~Merchant()
{
    return;
}

// Interact menu
bool Merchant::interact_menu(Player* player, Queue_NPC* npc_queue)
{
    string question =  "<--" + m_name + " - Please Choose an Option:" + "-->";
    bool player_die = false;
    int menu_answer;

    do
    {
        // Ask the user for a choice
        menu_answer = display_menu(question, m_number_of_options, m_menu_options, true);

        // Based on the choice run the correct option
        if (menu_answer == 0)
        {
            sell_item(player);
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
void Merchant::display_stats()
{
    // Display class stats and then character stats
    cout << "<----------" << m_name << " - Stats:---------->" << endl;
    cout << "Type: Merchant" << endl;
    Character::display_stats(false);
    return;
}

// Sell item from merchants inventory
void Merchant::sell_item(Player* player)
{
    int item_choice = -1;

    void (system("CLS"));

    cout << "<--" << m_name << " - Shop:-->" << endl;

    cout << "Player Coins: " << player->get_money() << endl << endl;

    // Display the merchants items
    item_choice = m_inventory->display_menu("Items:", 3, false, true);

    // If user chose a item buy it
    if (item_choice != -1)
    {
        void (system("CLS"));

        cout << "<-" << m_inventory->find_index_value(item_choice)->get_name() << ":->" << endl;

        // If the user buys an item remove some of its coins and put the item in its inventory
        if (m_inventory->find_index_value(item_choice)->get_price() <= player->get_money())
        {
            player->set_money(player->get_money() -  m_inventory->find_index_value(item_choice)->get_price());
            cout << "Player bought: " << m_inventory->find_index_value(item_choice)->get_name_description() << endl;
            cout << "Player Coins: " << player->get_money() << endl << endl;

            player->get_inventory()->insert_value_start(m_inventory->find_index_value(item_choice));

            if (m_regenerate_item != true)
            {
                m_inventory->remove_index_value(item_choice);
            }
        }
        // If the user can't buy the item display how mnay coins the user needs
        else
        {
            cout << "Player needs " << m_inventory->find_index_value(item_choice)->get_price() - player->get_money() << " coins to buy this item" << endl << endl;
        }

        cout << "Press A to continue...";

        Game::game_controller.wait_until_button_a_input();

    }

    return;
}
