#ifndef GAME_H
#define GAME_H
#include "Controller.h"

class Queue_NPC;
class Controller;
class Screen;
class Tile;
class Player;
class Enemy;

class Game
{
    // Public methods and member for the class
    public:
        static Controller game_controller;

        Game();
        Game(Screen* [50], int, bool);
        virtual ~Game();

        Screen* get_screens(int);
        int get_screen_number();
        bool get_game_over();
        bool get_player_die();
        Queue_NPC* get_npc_queue();

        void set_screens(Screen* [50]);
        void set_screen_number(int);
        void set_game_over(bool);
        void set_player_die(bool);
        void set_npc_queue(Queue_NPC*);

        void load_screens(bool);

        bool run_game();
        void run_maze_solver();
        void teleport();

        void switch_screens(Screen*, Screen*, Tile*);

        void interact();

    // Private methods and members for the class
    private:
        Screen* m_screens[50];
        int m_screen_number;
        bool m_game_over;
        bool m_player_die;
        Queue_NPC* m_npc_queue;
};

#endif // GAME_H
