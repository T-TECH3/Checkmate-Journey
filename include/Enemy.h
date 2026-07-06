#ifndef ENEMY_H
#define ENEMY_H

#include <NPC.h>

class Player;
class Item;
class Queue_NPC;

class Enemy : public NPC
{
    // Public methods and member for the class
    public:
        Enemy();
        Enemy(string, int, int, int, int, int, int, int, string, bool);
        virtual ~Enemy();

        bool get_respawn();

        void set_respawn(bool);

        bool interact_menu(Player*, Queue_NPC*);
        void display_stats();

        bool battle(Player*, Queue_NPC*);

    private:
        bool m_respawn;
};

#endif // ENEMY_H
