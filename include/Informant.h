#ifndef INFORMANT_H
#define INFORMANT_H

#include <NPC.h>


class Informant : public NPC
{
    // Public methods and member for the class
    public:
        Informant();
        Informant(string, int, int, int, int, int, string);
        virtual ~Informant();

        bool interact_menu(Player*, Queue_NPC*);
        void display_stats();
};

#endif // INFORMANT_H
