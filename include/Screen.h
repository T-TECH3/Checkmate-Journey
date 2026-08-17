#include <iostream>
//#include <libxl.h>
#ifndef SCREEN_H
#define SCREEN_H

using namespace std;

class Tile;
class Player;

class Screen
{
    // Public methods and member for the class
    public:
        Screen();
        Screen(Tile* [17][60], Player*);
        Screen(char [17][60], Player*);
        virtual ~Screen();

        Tile* get_map(int, int);
        Player* get_player_1 ();

        void set_map(Tile* [17][60]);
        void set_map(char [17][60]);
        void set_player_1 (Player*);

        void load_map();

        void display_map();

        void remove_breadcrumbs();

    // Private methods and members for the class
    private:
        Tile* m_map [17][60];
        Player* m_player_1;
};

#endif // SCREEN_H
