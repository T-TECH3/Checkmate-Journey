#include <iostream>
#include <ctime>
#include <windows.h>
#include "Utility_Function.h"
#include "Game.h"
#include "Screen.h"
#include "Player.h"
#include "Tile.h"
#include "Controller.h"
#include "Stack_Maze_Solver.h"
#include "NPC.h"
#include "Enemy.h"
#include "Merchant.h"
#include "Item.h"
#include "Stats_Item.h"
#include "Unlock_Item.h"
#include "Linked_List_Item.h"
#include "Informant.h"
#include "Queue_NPC.h"

using namespace std;

Controller Game:: game_controller = Controller();

// Default constuctor
Game::Game()
{
    for (int i = 0; i < 50; i++)
    {
        m_screens[i] = nullptr;
    }

    m_screen_number = 0;
    m_game_over = false;
    m_npc_queue = new Queue_NPC();
}

// Custom constuctor
Game::Game(Screen* screens [50], int screen_number, bool game_over)
{
    for (int i = 0; i < 50; i++)
    {
        m_screens[i] = screens[i];
    }

    m_screen_number = screen_number;
    m_game_over = game_over;
    m_npc_queue = new Queue_NPC();
}

// Deconstuctor
Game::~Game()
{
    //dtor
}

// Get methods for all members
Screen* Game::get_screens(int screen_number)
{
    return m_screens[screen_number];
}

int Game::get_screen_number()
{
    return m_screen_number;
}

bool Game::get_game_over()
{
    return m_game_over;
}

bool Game::get_player_die()
{
    return m_player_die;
}

Queue_NPC* Game::get_npc_queue()
{
    return m_npc_queue;
}

// Set methods for all members
void Game::set_screens(Screen* screens [50])
{
    for (int i = 0; i < 50; i++)
    {
        m_screens[i] = screens[i];
    }

    return;
}

void Game::set_screen_number(int screen_number)
{
    m_screen_number = screen_number;
    return;
}

void Game::set_game_over(bool game_over)
{
    m_game_over = game_over;
    return;
}

void Game::set_player_die(bool player_die)
{
    m_player_die = player_die;
    return;
}

void Game::set_npc_queue(Queue_NPC* queue_npc)
{
    m_npc_queue = queue_npc;
    return;
}

// Load screens
void Game::load_screens(bool maze_solver)
{
    string white_king = "\u2654";
    string white_queen = "\u2655";
    string white_rook = "\u2656";
    string white_horse = "\u2658";
    string white_bishop = "\u2657";
    string white_pawn = "\u2659";

    string key = "\u26B7";
    string sword = "\U0001F511";

    int enemy_r_color = 255;
    int enemy_g_color = 35;
    int enemy_b_color = 35;

    // Create Screens
    /*
    char screen_0_char_map [17] [60] =
    {
            {'W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W'},
            {'W','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','W'},
            {'W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','W'},
            {'W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','W','W','W','W'},
            {'.','.','W','.','.','W','W','W','.','W','W','.','W','W','.','W','W','W','.','W','W','W','.','W','W','.','W','W','.','W','W','.','.','W','W','.','W','W','W','W','W','.','W','W','W','W','.','W','W','W','.','W','W','W','.','.','W','.','.','W'},
            {'W','W','W','.','.','W','W','W','.','W','W','.','W','W','.','W','W','W','.','W','W','W','.','W','W','.','W','W','.','W','W','W','W','W','W','.','W','W','W','W','W','.','W','W','W','W','.','W','W','W','.','W','W','W','.','.','W','W','D','W'},
            {'W','.','.','.','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','W','W','W','.','W','W','W','W','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','.','.','W','W','W','.','.','.','W','.','W'},
            {'W','W','W','.','.','W','W','.','.','W','W','W','W','W','.','W','W','W','.','W','W','.','.','W','W','W','W','.','.','W','W','.','.','W','W','.','W','W','W','W','W','.','.','W','W','.','.','W','W','W','.','W','W','W','.','.','.','D','.','T'},
            {'.','.','W','.','.','W','W','.','.','W','W','W','W','W','.','W','W','W','.','W','W','.','.','W','W','.','.','.','.','W','W','.','.','W','W','.','W','W','W','W','W','.','.','W','W','.','.','W','W','W','.','W','W','W','.','.','.','D','.','T'},
            {'W','W','W','.','.','W','W','.','.','W','W','W','W','W','.','W','W','W','.','W','W','.','.','W','W','W','W','.','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','W','.','.','.','.','.','.','.','D','.','T'},
            {'W','.','.','.','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','W','W','W','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','.','.','W','W','W','.','.','.','W','.','W'},
            {'W','W','W','.','.','W','W','W','.','W','W','.','W','W','.','W','W','W','.','W','W','W','.','W','W','.','W','W','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','W','.','W','W','W','.','.','W','W','D','W'},
            {'.','.','W','.','.','W','W','W','.','W','W','.','W','W','.','W','W','W','.','W','W','W','.','W','W','.','W','W','.','W','W','.','.','W','W','.','W','W','.','W','W','.','.','W','W','.','.','W','W','W','.','W','W','W','.','.','W','.','.','W'},
            {'W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','W','W','W','W'},
            {'W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','W'},
            {'W','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','W'},
            {'W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W'}
    };
    */

    char screen_0_char_map [17] [60] =
    {
            {'W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W'},
            {'W','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','W'},
            {'W','.','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','W','.','W','W','.','.','.','.','D','.','.','.','.','D','.','.','.','.','.','.','W'},
            {'W','W','W','.','W','W','W','W','W','W','W','W','W','W','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','W','W','W','W','W','W','W','.','W','.','.','.','.','.','.','W','W','W','W','W','W','W','D','D','W','W','D','D','W'},
            {'.','W','.','.','W','.','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','.','.','.','.','W','.','.','.','W','.','.','.','.','.','.','.','.','.','W','W','D','D','D','W','W','W','W','.','.','.','.','.','.','.','W','.','.','.','W'},
            {'.','W','D','D','W','.','.','W','W','W','W','W','.','.','.','W','W','W','W','W','W','W','.','W','.','W','.','W','.','W','W','W','W','W','W','W','W','W','.','W','.','.','.','.','W','.','.','.','.','W','W','W','W','W','W','W','W','.','.','W'},
            {'W','W','.','.','W','W','W','W','.','.','.','W','W','W','.','W','.','.','.','D','.','W','.','W','.','W','.','W','.','.','.','.','.','.','.','.','.','.','.','W','.','.','W','.','W','W','W','W','.','.','.','W','.','.','.','.','W','W','W','W'},
            {'W','.','.','.','D','.','.','D','.','W','.','W','.','W','.','W','.','.','.','W','.','W','.','W','W','W','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','W','.','W','.','.','W','.','W','.','.','.','W','W','.','W','.','.','T'},
            {'W','.','.','.','D','.','.','D','.','W','W','W','.','W','.','W','W','W','W','W','.','W','.','W','.','.','.','.','.','.','D','.','.','.','.','.','.','.','W','.','.','.','W','.','W','.','.','W','.','W','W','W','W','W','W','.','D','.','.','T'},
            {'W','.','.','.','D','.','.','D','.','.','.','.','.','W','.','.','.','.','.','.','.','W','.','W','W','W','W','W','W','W','W','.','W','W','W','.','W','W','W','W','W','.','W','W','W','W','.','W','.','.','.','W','.','.','.','.','W','.','.','T'},
            {'W','W','.','.','W','.','.','W','W','W','W','W','.','W','W','W','W','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','W','.','.','.','.','W','.','W','W','W','W','W','.','W','W','W','W','D','D','W'},
            {'.','W','W','W','W','.','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','W','W','W','W','W','W','W','W','W','W','.','W','.','W','W','W','.','W','W','W','W','.','W','.','.','.','.','.','W','W','W','.','W','W','.','.','W'},
            {'.','W','.','.','.','.','W','W','W','W','D','W','W','W','W','W','W','W','W','W','W','.','.','W','.','.','.','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','.','.','.','W','.','W','.','W','.','.','.','.','.','.','.','.','.','W'},
            {'W','W','W','W','W','W','W','W','.','W','.','.','D','.','.','.','.','W','.','.','W','W','W','W','W','W','W','.','W','W','W','W','W','W','W','D','W','W','W','W','W','W','W','W','W','W','.','W','.','W','W','W','W','W','W','W','W','W','.','W'},
            {'W','.','W','.','.','.','.','.','.','W','W','D','W','.','.','W','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','D','.','.','.','.','D','.','.','.','.','W','W','.','.','.','.','W','.','.','.','.','W','.','.','.','.','W','.','W'},
            {'W','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','W','W','.','W','W','W','W','.','.','.','W'},
            {'W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W'}
    };

    Screen* screen_0 = new Screen(screen_0_char_map, nullptr);
    screen_0->load_map();
    m_screens[0] = screen_0;

    char screen_1_char_map [17] [60] =
    {
            {'W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','W','W','.','D','.','D','.','D','.','D','.','D','.','D','.','D','.','W','.','.','.','.','D','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','W','D','W','W','.','D','.','D','.','D','.','D','.','D','.','D','.','D','.','W','.','.','.','.','W','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','.','W','W','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'T','.','.','D','.','.','W','.','W','.','W','.','W','.','W','.','.','.','.','.','W','.','.','W','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'T','.','.','D','.','.','D','.','D','.','D','.','D','.','D','.','.','.','.','.','D','.','.','W','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'T','.','.','D','.','.','W','.','W','.','W','.','W','.','W','.','.','.','.','.','W','.','.','W','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','.','W','.','.','.','.','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','W','D','W','W','.','D','.','D','.','D','.','D','.','D','.','D','.','D','.','W','.','.','D','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','W','W','.','D','.','D','.','D','.','D','.','D','.','D','.','D','.','W','.','.','D','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','.','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','W','.','.','.','.','.','.','W','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','.','.','.','W','W','W','W','.','W','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
            {'W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','W','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'}
    };

    Screen* screen_1 = new Screen(screen_1_char_map, nullptr);
    screen_1->load_map();
    m_screens[1] = screen_1;

    m_screen_number = 0;

    // Set up teleport tiles
    m_screens[0]->get_map(7, 59)->set_teleport(m_screens[1]->get_map(7, 0));
    m_screens[0]->get_map(8, 59)->set_teleport(m_screens[1]->get_map(8, 0));
    m_screens[0]->get_map(9, 59)->set_teleport(m_screens[1]->get_map(9, 0));

    m_screens[1]->get_map(7, 0)->set_teleport(m_screens[0]->get_map(7, 59));
    m_screens[1]->get_map(8, 0)->set_teleport(m_screens[0]->get_map(8, 59));
    m_screens[1]->get_map(9, 0)->set_teleport(m_screens[0]->get_map(9, 59));

    // Set up player
    Stack_Maze_Solver* player_1_stack_char = new Stack_Maze_Solver();
    Player* player_1 = new Player(white_king, screen_0, 8, 1, 255, 255, 255, 3, 2, 0, player_1_stack_char);
    //Player* player_1 = new Player(white_king, screen_0, 8, 1, 255, 255, 255, 99, 99, 99, player_1_stack_char);
    screen_0->set_player_1(player_1);

    if (maze_solver == false)
    {
        // Merchants
        NPC* npc_M1 = new Merchant(white_pawn, 10, 3, 255, 255, 255, "White Pawn (TESTING ONLY)", false);
        m_screens[0]->get_map(10, 3)->set_npc(npc_M1);

        NPC* npc_M2 = new Merchant(white_bishop, 7, 10, 255, 255, 255, "White Bishop", true);
        m_screens[0]->get_map(7, 10)->set_npc(npc_M2);

        NPC* npc_M3 = new Merchant(white_horse, 6, 24, 255, 255, 255, "White Horse", true);
        m_screens[0]->get_map(6, 24)->set_npc(npc_M3);

        NPC* npc_M4 = new Merchant(white_rook, 5, 57, 255, 255, 255, "White Rook", false);
        m_screens[0]->get_map(5, 57)->set_npc(npc_M4);

        NPC* npc_M5 = new Merchant(white_rook, 14, 53, 255, 255, 255, "White Rook", false);
        m_screens[0]->get_map(14, 53)->set_npc(npc_M5);

        NPC* npc_M6 = new Informant(white_queen, 5, 27, 255, 255, 255, "White Queen");
        m_screens[1]->get_map(5, 27)->set_npc(npc_M6);

        // Enemey
        NPC* npc_1 = new Enemy(white_pawn, 5, 6, enemy_r_color, enemy_g_color, enemy_b_color, 3, 1, "Dark Pawn", true);
        m_screens[0]->get_map(5, 6)->set_npc(npc_1);

        NPC* npc_2 = new Enemy(white_pawn, 11, 7, enemy_r_color, enemy_g_color, enemy_b_color, 2, 2, "Dark Pawn", true);
        m_screens[0]->get_map(11, 7)->set_npc(npc_2);

        NPC* npc_3 = new Enemy(white_pawn, 11, 19, enemy_r_color, enemy_g_color, enemy_b_color, 5, 2, "Dark Pawn", true);
        m_screens[0]->get_map(11, 19)->set_npc(npc_3);

        NPC* npc_4 = new Enemy(white_bishop, 13, 10, enemy_r_color, enemy_g_color, enemy_b_color, 5, 3, "Dark Bishop", true);
        m_screens[0]->get_map(13, 10)->set_npc(npc_4);

        NPC* npc_5 = new Enemy(white_bishop, 7, 14, enemy_r_color, enemy_g_color, enemy_b_color, 5, 2, "Dark Bishop", true);
        m_screens[0]->get_map(7, 14)->set_npc(npc_5);

        NPC* npc_6 = new Enemy(white_bishop, 2, 28, enemy_r_color, enemy_g_color, enemy_b_color, 6, 2, "Dark Bishop", true);
        m_screens[0]->get_map(2, 28)->set_npc(npc_6);

        NPC* npc_7 = new Enemy(white_horse, 14, 30, enemy_r_color, enemy_g_color, enemy_b_color, 6, 3, "Dark Horse", true);
        m_screens[0]->get_map(14, 30)->set_npc(npc_7);

        NPC* npc_8 = new Enemy(white_horse, 10, 31, enemy_r_color, enemy_g_color, enemy_b_color, 7, 2, "Dark Horse", true);
        m_screens[0]->get_map(10, 31)->set_npc(npc_8);

        NPC* npc_9 = new Enemy(white_horse, 8, 24, enemy_r_color, enemy_g_color, enemy_b_color, 6, 3, "Dark Horse", true);
        m_screens[0]->get_map(8, 24)->set_npc(npc_9);

        NPC* npc_10 = new Enemy(white_horse, 3, 3, enemy_r_color, enemy_g_color, enemy_b_color, 6, 3, "Dark Horse", true);
        m_screens[0]->get_map(3, 3)->set_npc(npc_10);

        NPC* npc_11 = new Enemy(white_rook, 12, 39, enemy_r_color, enemy_g_color, enemy_b_color, 8, 4, "Dark Rook", true);
        m_screens[0]->get_map(12, 39)->set_npc(npc_11);

        NPC* npc_12 = new Enemy(white_rook, 2, 46, enemy_r_color, enemy_g_color, enemy_b_color, 8, 4, "Dark Rook", true);
        m_screens[0]->get_map(2, 46)->set_npc(npc_12);

        NPC* npc_13 = new Enemy(white_rook, 2, 53, enemy_r_color, enemy_g_color, enemy_b_color, 8, 4, "Dark Rook", true);
        m_screens[0]->get_map(2, 53)->set_npc(npc_13);

        NPC* npc_14 = new Enemy(white_rook, 6, 48, enemy_r_color, enemy_g_color, enemy_b_color, 7, 4, "Dark Rook", true);
        m_screens[0]->get_map(6, 48)->set_npc(npc_14);

        NPC* npc_15 = new Enemy(white_rook, 11, 47, enemy_r_color, enemy_g_color, enemy_b_color, 7, 4, "Dark Rook", true);
        m_screens[0]->get_map(11, 47)->set_npc(npc_15);

        NPC* npc_16 = new Enemy(white_rook, 11, 57, enemy_r_color, enemy_g_color, enemy_b_color, 10, 5, "Dark Rook", true);
        m_screens[0]->get_map(11, 57)->set_npc(npc_16);

        NPC* npc_17 = new Enemy(white_rook, 11, 58, enemy_r_color, enemy_g_color, enemy_b_color, 10, 5, "Dark Rook", true);
        m_screens[0]->get_map(11, 58)->set_npc(npc_17);

        NPC* npc_18 = new Enemy(white_king, 8, 25, enemy_r_color, enemy_g_color, enemy_b_color, 20, 5, "Dark King", false);
        m_screens[1]->get_map(8, 25)->set_npc(npc_18);

        NPC* npc_19 = new Enemy(white_queen, 8, 26, enemy_r_color, enemy_g_color, enemy_b_color, 15, 5, "Dark Queen", false);
        m_screens[1]->get_map(8, 26)->set_npc(npc_19);

        NPC* npc_20 = new Enemy(white_pawn, 12, 2, enemy_r_color, enemy_g_color, enemy_b_color, 2, 1, "Dark Pawn", true);
        m_screens[0]->get_map(12, 2)->set_npc(npc_20);

        NPC* npc_21 = new Enemy(white_bishop, 6, 2, enemy_r_color, enemy_g_color, enemy_b_color, 6, 3, "Dark Bishop", false);
        m_screens[1]->get_map(6, 2)->set_npc(npc_21);

        NPC* npc_22 = new Enemy(white_bishop, 10, 2, enemy_r_color, enemy_g_color, enemy_b_color, 6, 3, "Dark Bishop", false);
        m_screens[1]->get_map(10, 2)->set_npc(npc_22);

        NPC* npc_23 = new Enemy(white_horse, 8, 19, enemy_r_color, enemy_g_color, enemy_b_color, 10, 5, "Dark Horse", false);
        m_screens[1]->get_map(8, 19)->set_npc(npc_23);

        NPC* npc_24 = new Enemy(white_rook, 10, 21, enemy_r_color, enemy_g_color, enemy_b_color, 12, 5, "Dark Rook", false);
        m_screens[1]->get_map(10, 21)->set_npc(npc_24);

        NPC* npc_25 = new Enemy(white_rook, 10, 22, enemy_r_color, enemy_g_color, enemy_b_color, 12, 5, "Dark Rook", false);
        m_screens[1]->get_map(10, 22)->set_npc(npc_25);


        // Items
        // Create GOD item for testing purpose

        Item* item_1 = new Stats_Item("SUPER WEAPON", sword, 255, 255, 255, 0, player_1, 0, 999);
        npc_M1->get_inventory()->insert_value_start(item_1);

        Item* item_2 = new Stats_Item("IMMORTALITY BOOST", "?", 255, 255, 255, 0, player_1, 999, 0);
        npc_M1->get_inventory()->insert_value_start(item_2);

        Item* item_3_2 = new Stats_Item("Large Healing Potion", "?", 255, 255, 255, 9, player_1, 8, 0);
        npc_M2->get_inventory()->insert_value_start(item_3_2);

        Item* item_3_1 = new Stats_Item("Medium Healing Potion", "?", 255, 255, 255, 6, player_1, 5, 0);
        npc_M2->get_inventory()->insert_value_start(item_3_1);

        Item* item_3 = new Stats_Item("Tiny Healing Potion", "?", 255, 255, 255, 3, player_1, 2, 0);
        npc_M2->get_inventory()->insert_value_start(item_3);

        Item* item_4_2 = new Stats_Item("Large Battle Boost", sword, 255, 255, 255, 8, player_1, 0, 4);
        npc_M3->get_inventory()->insert_value_start(item_4_2);

        Item* item_4_1 = new Stats_Item("Medium Battle Boost", sword, 255, 255, 255, 5, player_1, 0, 2);
        npc_M3->get_inventory()->insert_value_start(item_4_1);

        Item* item_4 = new Stats_Item("Tiny Battle Boost", sword, 255, 255, 255, 3, player_1, 0, 1);
        npc_M3->get_inventory()->insert_value_start(item_4);

        Unlock_Item* item_5 = new Unlock_Item("Blue Key", key, 51, 153, 255, 10);
        npc_M4->get_inventory()->insert_value_start(item_5);
        m_screens[1]->get_map(8, 6)->set_unlock_item(item_5);

        Unlock_Item* item_6 = new Unlock_Item("Red Key", key, 255, 51, 51, 5);
        npc_M5->get_inventory()->insert_value_start(item_6);
        m_screens[1]->get_map(8, 8)->set_unlock_item(item_6);

        Unlock_Item* item_7 = new Unlock_Item("Purple Key", key, 153, 51, 255, 0);
        npc_9->get_inventory()->insert_value_start(item_7);
        m_screens[1]->get_map(8, 10)->set_unlock_item(item_7);
        m_screens[0]->get_map(6, 19)->set_unlock_item(item_7);

        Unlock_Item* item_8 = new Unlock_Item("Yellow Key", key, 255, 255, 102, 0);
        npc_14->get_inventory()->insert_value_start(item_8);
        m_screens[0]->get_map(14, 36)->set_unlock_item(item_8);
        m_screens[1]->get_map(8, 12)->set_unlock_item(item_8);

        Unlock_Item* item_9 = new Unlock_Item("Orange Key", key, 255, 153, 51, 0);
        m_screens[0]->get_map(7, 17)->set_droped_item(item_9);
        m_screens[1]->get_map(8, 14)->set_unlock_item(item_9);

        Unlock_Item* item_10 = new Unlock_Item("Jail Cell Key", key, 192, 192, 192, 0);
        npc_18->get_inventory()->insert_value_start(item_10);

        m_screens[1]->get_map(4, 25)->set_unlock_item(item_10);

        // Locked Doors
        m_screens[0]->get_map(12, 10)->set_is_passable(false);
        m_screens[0]->get_map(8, 30)->set_is_passable(false);
        m_screens[0]->get_map(8, 56)->set_is_passable(false);
    }

    return;
}

// Run game
bool Game::run_game()
{
    void (system("CLS"));

    // Check if there is a player
    if (m_screens[m_screen_number]->get_player_1() == nullptr)
    {
        cout << "Error: No Player on current screen";
        m_game_over = true;
    }
    else
    {
        m_screens[m_screen_number]->display_map();
    }

    // Run the game while game over is not true
    while (m_game_over == false)
    {
        // Move the player
        if (m_screens[m_screen_number]->get_player_1()->joy_1_move() == true)
        {
            teleport();
        }
        // Return to main menu if b button is pressed
        else if (game_controller.get_button_b_input() == true)
        {
            m_game_over = true;
        }
        // Open player stats if x button is pressed
        else if (game_controller.get_button_x_input() == true)
        {
            m_screens[m_screen_number]->get_player_1()->display_stats();
            void (system("CLS"));
            m_screens[m_screen_number]->display_map();
        }
        // call the interact function if the button pad is pressed
        else if(game_controller.get_button_pad_direction() != 'N')
        {
            interact();

            // If the player has died return true
            if (m_player_die == true)
            {
                return true;
            }
        }

        // If the y button is pressed lower the sleep time for faster movement
        if (game_controller.get_button_y_input())
        {
            Sleep(25);
        }
        else
        {
            Sleep(150);
        }
    }

    console_color(255, 255, 255);

    m_game_over = false;

    return false;
}

// Run maze solver
void Game::run_maze_solver()
{
    string white_queen = "\u2655";
    string key = "\u26B7";

    // Create the key required for the auto solver
    NPC* npc_M6 = new Informant(white_queen, 5, 27, 255, 255, 255, "White Queen");
    m_screens[1]->get_map(5, 27)->set_npc(npc_M6);

    Unlock_Item* item_1 = new Unlock_Item("Blue Key", key, 51, 153, 255, 0);
    m_screens[0]->get_map(7, 17)->set_droped_item(item_1);
    m_screens[1]->get_map(8, 6)->set_unlock_item(item_1);
    m_screens[1]->get_map(8, 6)->set_color(255, 35, 35);

    Unlock_Item* item_2 = new Unlock_Item("Red Key", key, 255, 51, 51, 0);
    m_screens[0]->get_map(14, 53)->set_droped_item(item_2);
    m_screens[1]->get_map(8, 8)->set_unlock_item(item_2);
    m_screens[1]->get_map(8, 8)->set_color(255, 35, 35);

    Unlock_Item* item_3 = new Unlock_Item("Purple Key", key, 153, 51, 255, 0);
    m_screens[0]->get_map(10, 52)->set_droped_item(item_3);
    m_screens[1]->get_map(8, 10)->set_unlock_item(item_3);
    m_screens[1]->get_map(8, 10)->set_color(255, 35, 35);

    Unlock_Item* item_4 = new Unlock_Item("Yellow Key", key, 255, 255, 102, 0);
    m_screens[0]->get_map(8, 24)->set_droped_item(item_4);
    m_screens[1]->get_map(8, 12)->set_unlock_item(item_4);
    m_screens[1]->get_map(8, 12)->set_color(255, 35, 35);

    Unlock_Item* item_5 = new Unlock_Item("Orange Key", key, 255, 153, 51, 0);
    m_screens[0]->get_map(14, 1)->set_droped_item(item_5);
    m_screens[1]->get_map(8, 14)->set_unlock_item(item_5);
    m_screens[1]->get_map(8, 14)->set_color(255, 35, 35);

    // Display the map and wait for a to start the auto solver
    void (system("CLS"));

    m_screens[m_screen_number]->display_map();

    move_cursor(0, 17);

    cout << "Maze Solver:" << " Press A to start..." << endl << "Note: For the purpose of the maze solver algorihm the doors which are locked are red and will turn green when unlocked";

    game_controller.wait_until_button_a_input();

    move_cursor(0, 17);
    cout << "                                                 " << endl << "                                                                                                                                                            ";

    // Search for all the key until they are all collected
    if (m_screens[m_screen_number]->get_player_1()->get_inventory()->search_for_value(item_1) == false)
    {
        m_screens[m_screen_number]->get_player_1()->solve_maze(7, 17, true);
    }

    if (m_screens[m_screen_number]->get_player_1()->get_inventory()->search_for_value(item_2) == false)
    {
        m_screens[m_screen_number]->get_player_1()->solve_maze(14, 53, true);
    }

    if (m_screens[m_screen_number]->get_player_1()->get_inventory()->search_for_value(item_3) == false)
    {
        m_screens[m_screen_number]->get_player_1()->solve_maze(10, 52, true);
    }

    if (m_screens[m_screen_number]->get_player_1()->get_inventory()->search_for_value(item_4) == false)
    {
        m_screens[m_screen_number]->get_player_1()->solve_maze(8, 24, true);
    }

    if (m_screens[m_screen_number]->get_player_1()->get_inventory()->search_for_value(item_5) == false)
    {
        m_screens[m_screen_number]->get_player_1()->solve_maze(14, 1, true);
    }

    // Search for the exit of screen 0
    m_screens[m_screen_number]->get_player_1()->solve_maze(8, 59, false);

    teleport();

    // Search for the exit of screen 1
    m_screens[m_screen_number]->get_player_1()->solve_maze(4, 27, true);

    move_cursor(0, 17);

    // Wait for a button to quit
    cout << "Maze Solver:" << " Press A to quit...";

    game_controller.wait_until_button_a_input();

    return;
}

// Teleport player from screen to screen
void Game::teleport()
{
    // If the player is on a teleport tile teleport the player to the corisponding tile on the text screen
    Tile* teleport_from_tile = m_screens[m_screen_number]->get_map(m_screens[m_screen_number]->get_player_1()->get_row_coord(), m_screens[m_screen_number]->get_player_1()->get_column_coord());

    if (teleport_from_tile->get_teleport() != nullptr)
    {
        switch_screens(teleport_from_tile->get_teleport()->get_current_screen(), teleport_from_tile->get_current_screen(), teleport_from_tile->get_teleport());
        return;
    }

    return;
}

// Intereact with tile function
void Game::interact()
{
    char direction = game_controller.get_button_pad_direction();
    int interaction = 1;

    // Based on the button pressed, all the interact funtion for the corisponding tile
    if (direction == 'U')
    {
        interaction = m_screens[m_screen_number]->get_map(m_screens[m_screen_number]->get_player_1()->get_row_coord() - 1, m_screens[m_screen_number]->get_player_1()->get_column_coord())->interact(false, m_npc_queue);
    }
    else if (direction == 'D')
    {
        interaction = m_screens[m_screen_number]->get_map(m_screens[m_screen_number]->get_player_1()->get_row_coord() + 1, m_screens[m_screen_number]->get_player_1()->get_column_coord())->interact(false, m_npc_queue);
    }
    else if (direction == 'L')
    {
        interaction = m_screens[m_screen_number]->get_map(m_screens[m_screen_number]->get_player_1()->get_row_coord(), m_screens[m_screen_number]->get_player_1()->get_column_coord() - 1)->interact(false, m_npc_queue);
    }
    else if (direction == 'R')
    {
        interaction = m_screens[m_screen_number]->get_map(m_screens[m_screen_number]->get_player_1()->get_row_coord(), m_screens[m_screen_number]->get_player_1()->get_column_coord() + 1)->interact(false, m_npc_queue);
    }

    // If the interaction is -1 the player has died
    if (interaction == -1)
    {
        m_player_die = true;
    }
    else
    {
        m_player_die = false;
    }

    // If the respond queue is 3 and the player is not dead respond an NPC
    if (m_npc_queue->get_size() == 3 and interaction == 0 and m_player_die == false)
    {
        NPC* the_npc = m_npc_queue->pop();

        m_screens[m_screen_number]->get_map(the_npc->get_row_coord(), the_npc->get_column_coord())->set_is_passable(false);
        m_screens[m_screen_number]->get_map(the_npc->get_row_coord(), the_npc->get_column_coord())->set_npc(the_npc);
    }

    // If the player is not dead return but the player did interact display the map
    if (interaction == 0 and m_player_die == false)
    {
        void (system("CLS"));
        m_screens[m_screen_number]->display_map();
    }

    return;
}

// Switch screens
void Game::switch_screens(Screen* new_screen, Screen* old_screen, Tile* teleport_tile)
{
    // Teleport the player to a new screen on the corsbonding tile
    new_screen->set_player_1(old_screen->get_player_1());
    old_screen->set_player_1(nullptr);

    new_screen->get_player_1()->set_current_screen(new_screen);

    new_screen->get_player_1()->set_column_coord(teleport_tile->get_column_coord());
    new_screen->get_player_1()->set_row_coord(teleport_tile->get_row_coord());

    for (int i = 0; i < 50; i++)
    {
        if (m_screens[i] == new_screen)
        {
            m_screen_number = i;
        }

    }

    move_cursor(0,0);

    // Display new screen
    new_screen->display_map();

    return;
}
