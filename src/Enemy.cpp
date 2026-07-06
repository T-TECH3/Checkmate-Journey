#include "Enemy.h"
#include "Utility_Function.h"
#include "Game.h"
#include <iostream>
#include "Player.h"
#include "Screen.h"
#include "Tile.h"
#include "Linked_List_Item.h"
#include "Item.h"
#include "Queue_NPC.h"
#include <windows.h>

using namespace std;

// Default constuctor
Enemy::Enemy() : NPC()
{
    m_money = (m_health + m_attack);

    if (m_money <= 0)
    {
        m_money = 1;
    }

    m_menu_options[0] = "Attack";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_number_of_options = 3;

    m_respawn = false;

    return;
}

// Defautl constuctor
Enemy::Enemy(string piece_symbol, int row_coord, int column_coord, int r_color, int g_color, int b_color, int health, int attack, string name, bool respawn) : NPC(piece_symbol, row_coord, column_coord, r_color, g_color, b_color, health, attack, 0, name)
{
    m_money = (m_health + m_attack);

    if (m_money <= 0)
    {
        m_money = 1;
    }

    m_menu_options[0] = "Attack";
    m_menu_options[1] = "View Stats";
    m_menu_options[2] = "Back";

    for (int i = 3; i < 9; i++)
    {
        m_menu_options [i] = "Blank Option";
    }

    m_respawn = respawn;

    m_number_of_options = 3;

    return;
}

// Deconstuctor
Enemy::~Enemy()
{
    return;
}

bool Enemy::get_respawn()
{
    return m_respawn;
}

void Enemy::set_respawn(bool respawn)
{
    m_respawn = respawn;
    return;
}

// Interact menu
bool Enemy::interact_menu(Player* player, Queue_NPC* npc_queue)
{
    string question =  "<--" + m_name + " - Please Choose an Option:" + "-->";
    bool player_die = false;
    int menu_answer;

    do
    {
        // Ask the user for an option
        menu_answer = display_menu(question, m_number_of_options, m_menu_options, true);

        // Based on the choice choose the correct option
        if (menu_answer == 0)
        {
            player_die = battle(player, npc_queue);
        }
        else if (menu_answer == 1)
        {
            void (system("CLS"));
            display_stats();
            cout << endl << "Press A to continue..." << endl;
            Game::game_controller.wait_until_button_a_input();
            void (system("CLS"));
        }

    } while (menu_answer != 0 and menu_answer != 2);

    return player_die;
}

// Display stats
void Enemy::display_stats()
{
    // Display ememy stats and character stats
    cout << "<----------" << m_name << " - Stats:---------->" << endl;
    cout << "Type: Enemy" << endl;
    Character::display_stats(false);
    return;
}

// Battle ememy and player
bool Enemy::battle(Player* player, Queue_NPC* npc_queue)
{
    bool player_turn = true;

    void (system("CLS"));

    // Display player and enemeys current stats
    cout << "<----Battle: Player VS " << m_name << "---->" << endl;

    cout << "Player: " << "HP: " << player->get_health() << " ATK: " << player->get_attack() << endl;
    cout << m_name << ": " << "HP: " << m_health << " ATK: " << m_attack << endl << endl;

    cout << "Press A to continue..." << endl;
    Game::game_controller.wait_until_button_a_input();
    void (system("CLS"));

    // Start with player and keep attacking until player or enemy has no health
    while (player->get_health() > 0 and m_health > 0)
    {
        // If its the players turn deal playrs attack to enemys health
        if (player_turn == true)
        {
            cout << "<--Players Turn:-->" << endl;
            cout << "Player Deals " << player->get_attack() << " damage to " << m_name << endl << endl;
            m_health = m_health - player->get_attack();

            if (m_health < 0)
            {
                m_health = 0;
            }

            player_turn = false;
        }
        // If its the enemys turn deal enemy attackt to player health
        else
        {
            cout << "<--" << m_name << "'s Turn:-->" << endl;
            cout << m_name << " Deals " << m_attack << " damage to " << "Player" << endl << endl;

            player->set_health(player->get_health() - m_attack);

            if (player->get_health() < 0)
            {
                player->set_health(0);
            }

            player_turn = true;
        }

        cout << "Player: " << "HP: " << player->get_health() << " ATK: " << player->get_attack() << endl;
        cout << m_name << ": " << "HP: " << m_health << " ATK: " << m_attack << endl << endl;

        cout << "Press A to continue..." << endl;
        Game::game_controller.wait_until_button_a_input();
        void (system("CLS"));
    }

    // When someone is a 0 health display who won
    if (m_health == 0)
    {
        cout << "<--Battle Over - Player Won-->" << endl;

        cout << "Loot:" << endl;

        // Give enemy money to player
        if (m_money != 0)
        {
            cout << m_money << " coins" << endl;
            player->set_money(player->get_money() + m_money);
        }

        // Drop the item that the enemy had
        Item* loot_item = nullptr;

        player->get_current_screen()->get_map(m_row_coord, m_column_coord)->set_npc(nullptr);

        if (m_inventory->get_node_amount() != 0)
        {
            loot_item = m_inventory->find_index_value(0);

            cout << loot_item->get_name_description() << endl;

            player->get_current_screen()->get_map(m_row_coord, m_column_coord)->set_droped_item(loot_item);
            m_inventory->remove_value(loot_item);

            player->get_current_screen()->get_map(m_row_coord, m_column_coord)->set_is_passable(false);
        }
        else
        {
            player->get_current_screen()->get_map(m_row_coord, m_column_coord)->set_is_passable(true);
        }

        cout << endl << "Press A to continue..." << endl;
        Game::game_controller.wait_until_button_a_input();
        void (system("CLS"));

        // Add the enemy to the respond queue
        if (m_respawn == true)
        {
            npc_queue->push(this);
        }

    }
    else
    {
        cout << "<--Battle Over - " << m_name << " Won-->" << endl;
        cout << "Player Died" << endl;

        cout << endl << "Press A to restart..." << endl;
        Game::game_controller.wait_until_button_a_input();
        void (system("CLS"));

        // Retrun true that the player died
        return true;
    }

    return false;
}
