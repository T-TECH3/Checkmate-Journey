#include "Tile.h"
#include "Utility_Function.h"
#include "NPC.h"
#include "Screen.h"
#include "Game.h"
#include "Unlock_Item.h"
#include "Player.h"
#include "Linked_List_Item.h"

// Defult constucotr
Tile::Tile()
{
    m_current_screen = nullptr;
    m_row_coord = 0;
    m_column_coord = 0;
    m_tile_type = '.';
    m_tile_symbol = " ";
    m_tile_symbol_2 = " ";
    m_r_color = 255;
    m_g_color = 255;
    m_b_color = 255;
    m_is_passable = false;
    m_bread_crumbs = false;
    m_teleport = nullptr;
    m_npc = nullptr;
    m_unlock_item = nullptr;
    m_droped_item = nullptr;

    return;
}

// Custom constuctor
Tile::Tile(Screen* current_screen, int row_coord, int column_coord, char tile_type, string tile_symbol, string tile_symbol_2, int r_color, int g_color, int b_color, bool is_passable, bool bread_crumbs, Tile* teleport, NPC* npc, Unlock_Item* unlock_item, Item* droped_item)
{
    m_current_screen = current_screen;
    m_row_coord = row_coord;
    m_column_coord = column_coord;

    m_tile_type = tile_type;
    m_tile_symbol = tile_type;
    m_tile_symbol_2 = tile_symbol_2;
    m_r_color = r_color;
    m_g_color = g_color;
    m_b_color = b_color;
    m_is_passable = is_passable;
    m_bread_crumbs = bread_crumbs;
    m_teleport = teleport;
    m_npc = npc;
    m_unlock_item = unlock_item;
    m_droped_item = droped_item;

    return;
}

// Deconstuctor
Tile::~Tile()
{
    return;
}

// Get methods for all members
Screen* Tile::get_current_screen()
{
    return m_current_screen;
}

int Tile::get_row_coord()
{
    return m_row_coord;
}

int Tile::get_column_coord()
{
    return m_column_coord;
}

char Tile::get_tile_type()
{
    return m_tile_type;
}

string Tile::get_tile_symbol()
{
    return m_tile_symbol;
}

string Tile::get_tile_symbol_2()
{
    return m_tile_symbol_2;
}

int Tile::get_r_color()
{
    return m_r_color;
}

int Tile::get_g_color()
{
    return m_g_color;
}

int Tile::get_b_color()
{
    return m_b_color;
}

bool Tile::get_is_passable()
{
   return m_is_passable;
}

bool Tile::get_bread_crumbs()
{
   return m_bread_crumbs;
}

Tile* Tile::get_teleport()
{
    return m_teleport;
}

NPC* Tile::get_npc()
{
    return m_npc;
}

Unlock_Item* Tile::get_unlock_item()
{
    return m_unlock_item;
}

Item* Tile::get_droped_item()
{
    return m_droped_item;
}

// Set methods for all mebers
void Tile::set_current_screen(Screen* current_screen)
{
    m_current_screen = current_screen;
    return;
}

void Tile::set_row_coord(int row_coord)
{
    m_row_coord = row_coord;
    return;
}

void Tile::set_column_coord(int column_coord)
{
    m_column_coord = column_coord;
    return;
}

void Tile::set_tile_type(char tile_type)
{
    m_tile_type = tile_type;
    return;
}

void Tile::set_tile_symbol(string tile_symbol)
{
    m_tile_symbol = tile_symbol;
    return;
}

void Tile::set_tile_symbol_2(string tile_symbol_2)
{
    m_tile_symbol_2 = tile_symbol_2;
    return;
}

void Tile::set_color(int r_color, int g_color, int b_color)
{
    m_r_color = r_color;
    m_g_color = g_color;
    m_b_color = b_color;
    return;
}

void Tile::set_is_passable(bool is_passable)
{
   m_is_passable = is_passable;
    return;
}

void Tile::set_bread_crumbs(bool bread_crumbs)
{
    m_bread_crumbs = bread_crumbs;
    return;
}

void Tile::set_teleport(Tile* teleport)
{
    m_teleport = teleport;
    return;
}

void Tile::set_npc(NPC* npc)
{
    m_npc = npc;

    if (m_npc == nullptr)
    {
        m_is_passable = true;
    }
    else
    {
        m_is_passable = false;
    }

    return;
}

void Tile::set_unlock_item(Unlock_Item* item)
{
    m_unlock_item = item;

    if (m_unlock_item != nullptr)
    {
        m_is_passable = false;
    }
    else
    {
        m_is_passable = true;
    }

    return;
}

void Tile::set_droped_item(Item* droped_item)
{
    m_droped_item = droped_item;

    if (m_droped_item != nullptr)
    {
        m_is_passable = false;
    }
    else
    {
        m_is_passable = true;
    }

    return;
}

// Display the tile and the correct location with its symbol
void Tile::display_tile()
{
    move_cursor(m_column_coord * 2, m_row_coord);

    if (m_npc != nullptr)
    {
        m_npc->display_character();
    }
    else if (m_droped_item != nullptr)
    {
        console_color(0, 255, 0);
        console_color(m_droped_item->get_r_color(), m_droped_item->get_g_color(), m_droped_item->get_b_color());
        cout << m_droped_item->get_symbol() << " ";
    }
    else
    {
        console_color(m_r_color, m_g_color, m_b_color);
        cout << m_tile_symbol << m_tile_symbol_2;
    }

    return;
}

// interact with the NPC for dtreped
int Tile::interact(bool maze_solving, Queue_NPC* npc_queue)
{
    // If the maze solver is running inteact with the door or item without displaying text
    if (maze_solving == true)
    {
        if (m_droped_item != nullptr)
        {
            m_current_screen->get_player_1()->get_inventory()->insert_value_start(m_droped_item);
            m_droped_item = nullptr;

            m_is_passable = true;

            return 0;
        }
        else if (m_tile_type == 'D' and m_is_passable == false and m_current_screen->get_player_1()->get_inventory()->search_for_value(m_unlock_item) == true)
        {
            m_is_passable = true;
            m_r_color = 50;
            m_g_color = 205;
            m_b_color = 50;

            return 0;
        }
    }
    // If the maze solving is not runnint interact wiht the NPC, Door or item and display the text
    else
    {
        if (m_npc != nullptr)
        {
            bool player_die = m_npc->interact_menu(m_current_screen->get_player_1(), npc_queue);

            if (player_die == true)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
        else if (m_droped_item != nullptr)
        {
            void (system("CLS"));

            cout << "<---Item Found:--->" << endl;
            cout << "Player picked up a " << m_droped_item->get_name_description() << endl;

            m_current_screen->get_player_1()->get_inventory()->insert_value_start(m_droped_item);
            m_droped_item = nullptr;

            cout << endl << "Press A to continue...";
            Game::game_controller.wait_until_button_a_input();

            m_is_passable = true;

            return 0;
        }
        else if (m_tile_type == 'D' and m_is_passable == false and m_current_screen->get_player_1()->get_inventory()->search_for_value(m_unlock_item) == true)
        {
            void (system("CLS"));

            cout << "<---Unlocked Door:--->" << endl;
            cout << "This door is now unlocked by the " << m_unlock_item->get_name() << endl;

            cout << endl << "Press A to continue...";
            Game::game_controller.wait_until_button_a_input();

            m_is_passable = true;

            return 0;
        }
        else if (m_tile_type == 'D' and m_is_passable == false)
        {
            void (system("CLS"));

            cout << "<---Locked Door:--->" << endl;
            cout << "This door is locked";

            if (m_unlock_item != nullptr)
            {
                cout << ", find the " << m_unlock_item->get_name() << " to unlock the door";
            }

            cout << endl << endl << "Press A to continue...";
            Game::game_controller.wait_until_button_a_input();

            return 0;
        }
        else if (m_tile_type == 'D' and m_is_passable == true)
        {
            void (system("CLS"));

            cout << "<---Unlocked Door:--->" << endl;
            cout << "This door is unlocked" << endl << endl;

            cout << "Press A to continue...";
            Game::game_controller.wait_until_button_a_input();

            return 0;
        }
    }


    return 1;
}

