#include "Stats_Item.h"
#include "Player.h"
#include "Game.h"
#include <string>
#include "Linked_List_Item.h"

// Default constuctor
Stats_Item::Stats_Item() : Item()
{
    m_player = nullptr;
    m_health_increase = 0;
    m_attack_increase = 0;

    m_price_decimal = 0.0;
    m_health_increase_decimal = 0.0;
    m_attack_increase_decimal = 0.0;

    return;
}

// Custom constuctor
Stats_Item::Stats_Item(string name, string item_symbol, int r, int g, int b, int price, Player* player, int health_increase, int attack_increase) : Item(name, "", "", item_symbol, r, g, b, price)
{
    m_player = player;
    m_health_increase = health_increase;
    m_attack_increase = attack_increase;

    if (m_health_increase > 0 and m_attack_increase > 0)
    {
        m_name_description = m_name + " (HP: +" + to_string(m_health_increase) + ", ATK: +" + to_string(m_attack_increase) + ")";
    }
    else if (m_health_increase > 0)
    {
        m_name_description = m_name + " (HP: +" + to_string(m_health_increase) + ")";
    }
    else if (m_attack_increase > 0)
    {
        m_name_description = m_name + " (ATK: +" + to_string(m_attack_increase) + ")";
    }

    m_name_description_price = m_name_description + " - " + to_string(price) + " coins";

    m_price_decimal = price;
    m_health_increase_decimal = health_increase;
    m_attack_increase_decimal = attack_increase;

    return;
}

// Deconstuctor
Stats_Item::~Stats_Item()
{
    return;
}

// Get methods for all members
Player* Stats_Item::get_player()
{
    return m_player;
}

// Set methods for all members
void Stats_Item::set_player(Player* player)
{
    m_player = player;
    return;
}

// Use the item
void Stats_Item::use_item()
{
    // Use the item on the play and display the players new stats and remove from the player inventory
    void (system("CLS"));

    cout << "<--" << m_name << "-->" << endl;

    if (m_health_increase != 0)
    {
        cout << "HP: " << m_player->get_health() << " + " << m_health_increase << endl;
    }
    if (m_attack_increase != 0)
    {
        cout << "ATK: " << m_player->get_attack() << " + " << m_attack_increase << endl;
    }

    cout << endl << "Press A to continue...";
    Game::game_controller.wait_until_button_a_input();

    m_player->set_health(m_player->get_health() + m_health_increase);
    m_player->set_attack(m_player->get_attack() + m_attack_increase);

    m_player->get_inventory()->remove_value(this);

    void (system("CLS"));

    return;
}

// Regenerate item
void Stats_Item::regenerate_item()
{
    // REgenerate the item with new stats and prices
    float temp = m_price_decimal * 1.4;

    m_price_decimal = temp;

    temp = temp + 0.5;
    m_price = temp;

    if (m_health_increase != 0)
    {
        temp = m_health_increase_decimal * 1.5;

        m_health_increase_decimal = temp;

        temp = temp + 0.5;
        m_health_increase = temp;
    }

    if (m_attack_increase != 0)
    {
        temp = m_attack_increase_decimal * 1.3;

        m_attack_increase_decimal = temp;

        temp = temp + 0.5;

        m_attack_increase = temp;
    }

    if (m_health_increase > 0 and m_attack_increase > 0)
    {
        m_name_description = m_name + " (HP: +" + to_string(m_health_increase) + ", ATK: +" + to_string(m_attack_increase) + ")";
    }
    else if (m_health_increase > 0)
    {
        m_name_description = m_name + " (HP: +" + to_string(m_health_increase) + ")";
    }
    else if (m_attack_increase > 0)
    {
        m_name_description = m_name + " (ATK: +" + to_string(m_attack_increase) + ")";
    }

    m_name_description_price = m_name_description + " - " + to_string(m_price) + " coins";

    return;
}
