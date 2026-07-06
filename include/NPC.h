#ifndef NPC_H
#define NPC_H

#include <Character.h>

class Player;
class Queue_NPC;

class NPC : public Character
{
    // Public methods and member for the class
    public:
        NPC();
        NPC(string, int, int, int, int, int, int, int, int, string);
        virtual ~NPC();

        string get_name();
        string get_option(int);
        int get_number_of_options();
        Linked_List_Item* get_inventory();

        void set_name(string);
        void set_option(string [9]);
        void set_number_of_options(int);
        void set_inventory(Linked_List_Item*);

        virtual bool interact_menu(Player*, Queue_NPC*) = 0;

        void display_stats();

    // Protected methods and members for the class
    protected:
        string m_name;
        string m_menu_options [9];
        int m_number_of_options;
};

#endif // NPC_H
