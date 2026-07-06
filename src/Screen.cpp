#include <iostream>
#include "Screen.h"
#include "Tile.h"
#include "Player.h"
#include "Utility_Function.h"
#include "NPC.h"
#include "windows.h"

using namespace std;

//  Default constor
Screen::Screen()
{
    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            m_map [row][column] = new Tile(this, row, column, '.', " ", " ", 255, 255, 255, true, false, nullptr, nullptr, nullptr, nullptr);
        }
    }

    m_player_1 = nullptr;

    return;
}

// Custom constutor for an array of tiles
Screen::Screen(Tile* map [17][60], Player* player_1)
{
    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            m_map [row][column] = map[row][column];
        }
    }

    m_player_1 = player_1;

    return;
}

// Custom constuctor for an array of char
Screen::Screen(char char_map [17][60], Player* player_1)
{
    bool is_passable = true;
    string temp_string = " ";

    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            if (char_map [row][column] == 'W')
            {
                is_passable = false;
            }
            else
            {
                is_passable = true;
            }

            temp_string[0] = char_map [row][column];

            m_map [row][column] = new Tile(this, row, column, char_map [row][column], temp_string, temp_string, 255, 255, 255, is_passable, false, nullptr, nullptr, nullptr, nullptr);
        }
    }

    m_player_1 = player_1;

    return;
}

// Deconstuctor
Screen::~Screen()
{
    return;
}

// Get methods for all members
Tile* Screen::get_map(int row , int column)
{
   return m_map[row][column];
}

Player* Screen::get_player_1 ()
{
    return m_player_1;
}

// Set methods for all members
void Screen::set_map(Tile* map [17][60])
{
    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            m_map [row][column] = map[row][column];
        }
    }
    return;
}

void Screen::set_map(char char_map [17][60])
{
    bool is_passable = true;
    string temp_string = "";

    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            if (char_map [17][60] == 'W')
            {
                is_passable = false;
            }
            else
            {
                is_passable = true;
            }

            temp_string[0] = char_map [row][column];

            m_map [row][column] = new Tile(this, row, column, char_map [row][column], temp_string, temp_string, 255, 255, 255, is_passable, false, nullptr, nullptr, nullptr, nullptr);
        }
    }
}

void Screen::set_player_1 (Player* player_1)
{
    m_player_1 = player_1;
    return;
}

// Load the maps
void Screen::load_map()
{
    string temp_string = " ";

    string vertical_wall = "\u2551";
    string horizontal_wall = "\u2550";

    string horizontal_door = "\u2504";
    string vertical_door = "\u2506";

    string top_left_corner_wall = "\u2554";
    string top_right_corner_wall = "\u2557";
    string bottom_left_corner_wall = "\u255A";
    string bottom_right_corner_wall = "\u255D";

    string t_left_wall = "\u2563";
    string t_right_wall = "\u2560";
    string t_up_wall = "\u2569";
    string t_down_wall = "\u2566";

    string intersection_wall = "\u256C";

    string teleport = "\u26F6";

    // Gor tought every tile
    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            // Based on the tile type and the tiles around if set the tile symbole to the correct symbole and color

            if (m_map[row][column] != nullptr)
            {
                if (m_map [row][column]->get_tile_type() == '.')
                {
                    m_map[row][column]->set_tile_symbol(" ");
                    m_map[row][column]->set_tile_symbol_2(" ");
                }
                else if (m_map [row][column]->get_tile_type() == 'D')
                {
                    if ((m_map [row - 1][column]->get_tile_type() == 'W' or m_map [row - 1][column]->get_tile_type() == 'D') and (m_map [row + 1][column]->get_tile_type() == 'W' or m_map [row + 1][column]->get_tile_type() == 'D'))
                    {
                        m_map[row][column]->set_tile_symbol(vertical_door);
                        m_map[row][column]->set_tile_symbol_2(" ");
                    }
                    else if ((m_map [row][column - 1]->get_tile_type() == 'W' or m_map [row][column - 1]->get_tile_type() == 'D') and (m_map [row][column + 1]->get_tile_type() == 'W' or m_map [row][column + 1]->get_tile_type() == 'D'))
                    {
                        m_map[row][column]->set_tile_symbol(horizontal_door);
                        m_map[row][column]->set_tile_symbol_2(horizontal_door);
                    }
                    m_map[row][column]->set_color(153, 76, 0);
                }
                else if (m_map [row][column]->get_tile_type() == 'W')
                {
                    // Wall or Door
                    bool wall_up = false;
                    bool wall_down = false;
                    bool wall_left = false;
                    bool wall_right = false;

                    if (row > 0 and(m_map [row - 1][column]->get_tile_type() == 'W' or m_map [row - 1][column]->get_tile_type() == 'D'))
                    {
                        wall_up = true;
                    }
                    if (row < 16 and (m_map [row + 1][column]->get_tile_type() == 'W' or m_map [row + 1][column]->get_tile_type() == 'D'))
                    {
                        wall_down = true;
                    }
                    if (column > 0 and (m_map [row][column - 1]->get_tile_type() == 'W' or m_map [row][column - 1]->get_tile_type() == 'D'))
                    {
                        wall_left = true;
                    }
                    if (column < 59 and (m_map [row][column + 1]->get_tile_type() == 'W' or m_map [row ][column + 1]->get_tile_type() == 'D'))
                    {
                        wall_right = true;
                    }


                    if (wall_up == true and wall_down == true and wall_left == true and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(intersection_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);
                    }
                    else if (wall_up == true and wall_down == false and wall_left == true and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(t_up_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);
                    }
                    else if (wall_up == false and wall_down == true and wall_left == true and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(t_down_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);

                    }
                    else if (wall_up == true and wall_down == true and wall_left == true and wall_right == false)
                    {
                        m_map[row][column]->set_tile_symbol(t_left_wall);
                        m_map[row][column]->set_tile_symbol_2(" ");
                    }
                    else if (wall_up == true and wall_down == true and wall_left == false and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(t_right_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);
                    }
                    else if (wall_up == false and wall_down == true and wall_left == false and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(top_left_corner_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);
                    }
                    else if (wall_up == false and wall_down == true and wall_left == true and wall_right == false)
                    {
                        m_map[row][column]->set_tile_symbol(top_right_corner_wall);
                        m_map[row][column]->set_tile_symbol_2(" ");
                    }
                    else if (wall_up == true and wall_down == false and wall_left == false and wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(bottom_left_corner_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);
                    }
                    else if (wall_up == true and wall_down == false and wall_left == true and wall_right == false)
                    {
                        m_map[row][column]->set_tile_symbol(bottom_right_corner_wall);
                        m_map[row][column]->set_tile_symbol_2(" ");
                    }
                    else if (wall_left == true or wall_right == true)
                    {
                        m_map[row][column]->set_tile_symbol(horizontal_wall);
                        m_map[row][column]->set_tile_symbol_2(horizontal_wall);

                    }
                    else if (wall_up == true or wall_down == true)
                    {
                        m_map[row][column]->set_tile_symbol(vertical_wall);
                        m_map[row][column]->set_tile_symbol_2(" ");
                    }

                    m_map[row][column]->set_color(255, 255, 255);
                }
                else if (m_map [row][column]->get_tile_type() == 'T')
                {
                    m_map[row][column]->set_tile_symbol(teleport);
                    m_map[row][column]->set_tile_symbol_2(" ");
                    m_map[row][column]->set_color(102, 178, 255);
                }
                else
                {
                    temp_string[0] = m_map[row][column]->get_tile_type();
                    m_map[row][column]->set_tile_symbol(temp_string);
                }
            }

        }

    }
}

// Display the map of tiles
void Screen::display_map()
{
    // Go through every tiles and display it
    for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            // If the player is on this tile dislay it instead of the tile
            if (m_player_1 != nullptr && m_player_1->get_row_coord() == row && m_player_1->get_column_coord() == column)
            {
                m_player_1->display_character();
            }
            // Display the tile
            else if (m_map[row][column] != nullptr)
            {
                m_map[row][column]->display_tile();
            }
            // If there is no tile dipsly ?
            else
            {
                cout << "? ";
            }
        }
        cout << endl;
    }

    return;
}

// Remove breadcrumbs from all of the tiles
void Screen::remove_breadcrumbs()
{
        for (int row = 0; row < 17; row++)
    {
        for (int column = 0; column < 60; column++)
        {
            m_map[row][column]->set_bread_crumbs(false);
        }
    }

    return;
}


