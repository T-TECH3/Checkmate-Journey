#ifndef MERCHANT_H
#define MERCHANT_H

#include <NPC.h>


class Merchant : public NPC
{
    // Public methods and member for the class
    public:
        Merchant();
        Merchant(string, int, int, int, int, int, string, bool);
        virtual ~Merchant();

        bool interact_menu(Player*, Queue_NPC*);
        void display_stats();

        void sell_item(Player*);

    // Private methods and members for the class
    private:
        bool m_regenerate_item;
};

#endif // MERCHANT_H
