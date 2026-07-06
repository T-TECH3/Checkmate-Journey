#include "iostream"
#include "Character.h"
#include "Screen.h"
#include "Tile.h"
#include "Utility_Function.h"
#include "Linked_List_Item.h"

using namespace std;

// Default Constuctor
Character::Character()
{
    m_piece_symbol = "C";
    m_row_coord = 0;
    m_column_coord = 0;
    m_r_color = 255;
    m_g_color = 255;
    m_b_color = 255;

    m_health = 0;
    m_attack = 0;

    m_money = 0;

    m_inventory = new Linked_List_Item();

    return;
}

// Custom constuctor
Character::Character(string piece_symbol, int row_coord, int column_coord, int r_color, int g_color, int b_color, int health, int attack, int money)
{
    m_piece_symbol = piece_symbol;
    m_row_coord = row_coord;
    m_column_coord = column_coord;
    m_r_color = r_color;
    m_g_color = g_color;
    m_b_color = b_color;

    m_health = health;
    m_attack = attack;

    m_money = money;

    m_inventory = new Linked_List_Item();

    return;
}

// Deconstuctor
Character::~Character()
{
    return;
}

// Get methods for all members
string Character::get_piece_symbol()
{
    return m_piece_symbol;
}

int Character::get_row_coord()
{
    return m_row_coord;
}

int Character::get_column_coord()
{
    return m_column_coord;
}

int Character::get_r_color()
{
    return m_r_color;
}

int Character::get_g_color()
{
    return m_g_color;
}

int Character::get_b_color()
{
    return m_b_color;
}

int Character::get_health()
{
    return m_health;
}

int Character::get_attack()
{
    return m_attack;
}

int Character::get_money()
{
    return m_money;
}

Linked_List_Item* Character::get_inventory()
{
    return m_inventory;
}

// Set methods for all members
void Character::set_piece_symbol(string piece_symbol)
{
    m_piece_symbol = piece_symbol;
    return;
}

void Character::set_row_coord(int row_coord)
{
    m_row_coord = row_coord;
    return;
}

void Character::set_column_coord(int column_coord)
{
    m_column_coord = column_coord;
    return;
}

void Character::set_color(int r_color, int g_color, int b_color)
{
    m_r_color = r_color;
    m_g_color = g_color;
    m_b_color = b_color;
    return;
}

void Character::set_health(int health)
{
    m_health = health;
    return;
}

void Character::set_attack(int attack)
{
    m_attack = attack;
    return;
}

void Character::set_money(int money)
{
    m_money = money;
    return;
}

void Character::set_inventory(Linked_List_Item* inventory)
{
    m_inventory = inventory;
    return;
}

// Display the character symbol with its color
void Character::display_character()
{
    console_color(m_r_color, m_g_color, m_b_color);
    cout << m_piece_symbol << " ";
    return;
}

// Display the characters stats
void Character::display_stats(bool display_inventory)
{
    cout << "Location: " << m_column_coord << ", " << m_row_coord << endl;
    cout << "HP: " << m_health << endl;
    cout << "ATK: " << m_attack << endl;

    if (display_inventory == true)
    {
        cout << "<-Inventory:->" << endl;
        m_inventory->display(true);
    }

    return;
}
