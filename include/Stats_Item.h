#ifndef STATS_ITEM_H
#define STATS_ITEM_H

#include <Item.h>

class Player;

class Stats_Item : public Item
{
    // Public methods and member for the class
    public:
        Stats_Item();
        Stats_Item(string, string, int, int, int, int, Player*, int, int);
        virtual ~Stats_Item();

        Player* get_player();

        void set_player(Player*);

        void use_item();
        void regenerate_item();

    // Private methods and members for the class
    private:
        Player* m_player;

        float m_price_decimal;

        int m_health_increase;
        float m_health_increase_decimal;

        int m_attack_increase;
        float m_attack_increase_decimal;
};

#endif // STATS_ITEM_H
