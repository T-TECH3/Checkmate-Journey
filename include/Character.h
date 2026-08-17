#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Screen;
class Item;
class Linked_List_Item;

class Character
{
    // Public methods and member for the class
    public:
        Character();
        Character(string, int, int, int, int, int, int, int, int);
        virtual ~Character();

        string get_piece_symbol();
        int get_row_coord();
        int get_column_coord();
        int get_r_color();
        int get_g_color();
        int get_b_color();
        int get_health();
        int get_attack();
        int get_money();
        Linked_List_Item* get_inventory();

        void set_piece_symbol(string);
        void set_row_coord(int);
        void set_column_coord(int);
        void set_color(int, int, int);
        void set_health(int);
        void set_attack(int);
        void set_money(int);
        void set_inventory(Linked_List_Item*);

        void display_character();
        void display_stats(bool);

    // Protected methods and members for the class
    protected:
        string m_piece_symbol;
        int m_row_coord;
        int m_column_coord;
        int m_r_color;
        int m_g_color;
        int m_b_color;

        int m_health;
        int m_attack;

        int m_money;

        Linked_List_Item* m_inventory;
};

#endif // CHARACTER_H
