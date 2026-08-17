#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>
#include "Player.h"
#include "Controller.h"
#include "Screen.h"
#include "Tile.h"
#include "Stack_Maze_Solver.h"
#include "Utility_Function.h"
#include "Game.h"
#include "Linked_List_Item.h"
#include "Item.h"

using namespace std;

// Default constuctor
Player::Player() : Character()
{
    m_current_screen = nullptr;
    m_maze_solver = nullptr;

    return;
}

// Custom constuctor
Player::Player(string piece_symbol, Screen* current_screen, int x_coord, int y_coord, int r_color, int g_color, int b_color, int health, int attack, int money, Stack_Maze_Solver* maze_solver) : Character(piece_symbol, x_coord, y_coord, r_color, g_color, b_color, health, attack, money)
{
    m_current_screen = current_screen;
    m_maze_solver = maze_solver;
    return;
}

// Default constutor
Player::~Player()
{
    return;
}

// Get methods for all members
Screen* Player::get_current_screen()
{
    return m_current_screen;
}

Stack_Maze_Solver* Player::get_maze_solver()
{
    return m_maze_solver;
}

// Set methods for all members
void Player::set_current_screen(Screen* current_screen)
{
    m_current_screen = current_screen;
    return;
}

void Player::set_maze_solver(Stack_Maze_Solver* maze_solver)
{
    m_maze_solver = maze_solver;
    return;
}

// Move the player based on the left joy
bool Player::joy_1_move()
{
    char joy_1_direction = 'N';

    joy_1_direction = Game::game_controller.get_joy_1_direction();

    if (joy_1_direction != 'N')
    {
        if (player_move(joy_1_direction) == true)
        {
            return true;
        }
    }

    return false;
}

// Move the player based on a direction
bool Player::player_move(char direction)
{
    int row_move_direction = 0;
    int column_move_direction = 0;
    bool can_move = false;

    if (direction == 'U')
    {
        row_move_direction --;
    }
    else if (direction == 'D')
    {
        row_move_direction ++;
    }
    else if (direction == 'L')
    {
        column_move_direction --;
    }
    else if (direction == 'R')
    {
        column_move_direction ++;
    }

    if (can_player_move(direction, false) == true)
    {
        int player_old_row = m_row_coord;
        int player_old_column = m_column_coord;

        m_row_coord = m_row_coord + row_move_direction;
        m_column_coord = m_column_coord + column_move_direction;

        can_move = true;

        move_cursor(player_old_column * 2, player_old_row);

        m_current_screen->get_map(player_old_row, player_old_column)->display_tile();

        move_cursor(m_column_coord * 2, m_row_coord);

        display_character();
    }



    return can_move;
}

// Return true if the player can move
bool Player::can_player_move(char direction, bool include_bread_crumbs)
{
    int row_move_direction = 0;
    int column_move_direction = 0;

    if (direction == 'U')
    {
        row_move_direction --;
    }
    else if (direction == 'D')
    {
        row_move_direction ++;
    }
    else if (direction == 'L')
    {
        column_move_direction --;
    }
    else if (direction == 'R')
    {
        column_move_direction ++;
    }

    if (m_current_screen->get_map(m_row_coord + row_move_direction, m_column_coord + column_move_direction)->get_is_passable() == true and include_bread_crumbs == false and m_row_coord + row_move_direction >= 0 and m_row_coord + row_move_direction <= 17 and m_column_coord + column_move_direction >= 0 and m_column_coord + column_move_direction <= 59)
    {
        return true;
    }
    else if (m_current_screen->get_map(m_row_coord + row_move_direction, m_column_coord + column_move_direction)->get_is_passable() == true and m_current_screen->get_map(m_row_coord + row_move_direction, m_column_coord + column_move_direction)->get_bread_crumbs() == false and include_bread_crumbs == true and m_row_coord + row_move_direction >= 0 and m_row_coord + row_move_direction <= 17 and m_column_coord + column_move_direction >= 0 and m_column_coord + column_move_direction <= 59)
    {
        return true;
    }

    return false;
}

// Return true if b button is pressed to quit
bool Player::button_b_quit()
{
    return Game::game_controller.get_button_b_input();
}

// Run the maze solver based on a x and y and interact with items if true
bool Player::solve_maze(int row, int column, bool interact)
{
    char direction_moved = ' ';

    // Load all directions
    m_maze_solver->free();
    m_maze_solver->push('R', false);
    m_maze_solver->push('L', false);
    m_maze_solver->push('D', false);
    m_maze_solver->push('U', false);

    while (m_row_coord != row or m_column_coord != column)
    {
        // If iteract is true interact with all tiles around the player
        if (interact == true)
        {
            m_current_screen->get_map(m_row_coord - 1, m_column_coord)->interact(true, nullptr);
            m_current_screen->get_map(m_row_coord + 1, m_column_coord)->interact(true, nullptr);
            m_current_screen->get_map(m_row_coord, m_column_coord - 1)->interact(true, nullptr);
            m_current_screen->get_map(m_row_coord, m_column_coord + 1)->interact(true, nullptr);
        }

        // Set the tile that the player is on to have bread crumbs
        m_current_screen->get_map(m_row_coord, m_column_coord)->set_bread_crumbs(true);

        // If the player can't move anywhere (or all the tile have bread crumbs) back track until there are no more backtraking moves
        if (can_player_move('U', true) == false and can_player_move('D', true) == false and can_player_move('L', true) == false and can_player_move('R', true) == false)
        {
            while (m_maze_solver->peek_back_track() == false)
            {
                m_maze_solver->pop();
            }

            player_move(m_maze_solver->pop());
        }
        // Check if the player can move in the next direction on the stack
        else if (player_move(m_maze_solver->peek_content()) == true)
        {
            // If the player can move pop the direction and push the new directions (push the first (oposite) value with back traking)
            direction_moved = m_maze_solver->pop();

            if (direction_moved == 'U')
            {
                m_maze_solver->push('D', true);
                m_maze_solver->push('R', false);
                m_maze_solver->push('L', false);
                m_maze_solver->push('U', false);
            }
            else if (direction_moved == 'D')
            {
                m_maze_solver->push('U', true);
                m_maze_solver->push('R', false);
                m_maze_solver->push('L', false);
                m_maze_solver->push('D', false);
            }
            else if (direction_moved == 'L')
            {
                m_maze_solver->push('R', true);
                m_maze_solver->push('L', false);
                m_maze_solver->push('D', false);
                m_maze_solver->push('U', false);
            }
            else if (direction_moved == 'R')
            {
                m_maze_solver->push('L', true);
                m_maze_solver->push('R', false);
                m_maze_solver->push('D', false);
                m_maze_solver->push('U', false);
            }
        }
        // If the player can't move in that direction pop the value
        else
        {
            m_maze_solver->pop();
        }

        Sleep (10);
    }

    m_current_screen->remove_breadcrumbs();

    return true;
}

// Dispaly player stats and character stats
void Player::display_stats()
{
    int item_choice = 0;

    while (item_choice != -1)
    {
        void (system("CLS"));

        cout << "<----------Player - Stats:---------->" << endl;
        cout << "Type: Player" << endl;
        Character::display_stats(false);

        cout << "Coins: " << m_money << endl;

        item_choice = m_inventory->display_menu("<-Inventory:->", 6, false, false);

        if (item_choice != -1)
        {
            m_inventory->find_index_value(item_choice)->use_item();
        }
    }

    return;
}
