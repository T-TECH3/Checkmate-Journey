#include <iostream>
#ifndef TILE_H
#define TILE_H

using namespace std;

class Screen;
class Player;
class NPC;
class Unlock_Item;
class Item;
class Queue_NPC;

class Tile
{
    // Public methods and member for the class
    public:
        Tile();
        Tile(Screen*, int, int, char, string, string, int, int, int, bool, bool, Tile*, NPC*, Unlock_Item*, Item*);
        virtual ~Tile();

        Screen* get_current_screen();
        int get_row_coord();
        int get_column_coord();
        char get_tile_type();
        string get_tile_symbol();
        string get_tile_symbol_2();
        int get_r_color();
        int get_g_color();
        int get_b_color();
        bool get_is_passable();
        bool get_bread_crumbs();
        Tile* get_teleport();
        NPC* get_npc();
        Unlock_Item* get_unlock_item();
        Item* get_droped_item();

        void set_current_screen(Screen*);
        void set_row_coord(int);
        void set_column_coord(int);
        void set_tile_type(char);
        void set_tile_symbol(string);
        void set_tile_symbol_2(string);
        void set_color(int, int, int);
        void set_is_passable(bool);
        void set_bread_crumbs(bool);
        void set_teleport(Tile*);
        void set_npc(NPC*);
        void set_unlock_item(Unlock_Item*);
        void set_droped_item(Item*);

        void display_tile();

        int interact(bool, Queue_NPC*);

    // Private methods and members for the class
    private:
        Screen* m_current_screen;
        int m_row_coord;
        int m_column_coord;
        char m_tile_type;
        string m_tile_symbol;
        string m_tile_symbol_2;
        int m_r_color;
        int m_g_color;
        int m_b_color;
        bool m_is_passable;
        bool m_bread_crumbs;
        Tile* m_teleport;
        NPC* m_npc;
        Unlock_Item* m_unlock_item;
        Item* m_droped_item;
};

#endif // TILE_H
