#ifndef PLAYER_H
#define PLAYER_H
#include "Controller.h"
#include <iostream>
#include <bits/stdc++.h>
#include <Character.h>

using namespace std;

class Screen;
class Stack_Maze_Solver;
class Tile;

class Player : public Character
{
    // Public methods and member for the class
    public:
        Player();
        Player(string, Screen*, int, int, int, int, int, int, int, int, Stack_Maze_Solver*);
        virtual ~Player();

        Screen* get_current_screen();
        Stack_Maze_Solver* get_maze_solver();

        void set_current_screen(Screen*);
        void set_maze_solver(Stack_Maze_Solver*);

        bool joy_1_move();
        bool player_move(char);
        bool can_player_move(char, bool);
        bool button_b_quit();
        bool button_y_quit();

        bool solve_maze(int, int, bool);

        void display_stats();

    // Private methods and members for the class
    private:
        Screen* m_current_screen;
        Stack_Maze_Solver* m_maze_solver;
};

#endif // PLAYER_H
