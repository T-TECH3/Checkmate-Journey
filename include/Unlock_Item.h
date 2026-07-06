#ifndef UNLOCK_ITEM_H
#define UNLOCK_ITEM_H

#include <Item.h>

class Tile;

class Unlock_Item : public Item
{
    // Public methods and member for the class
    public:
        Unlock_Item();
        Unlock_Item(string, string, int, int, int, int);
        virtual ~Unlock_Item();

        void use_item();
        void regenerate_item();
};

#endif // UNLOCK_ITEM_H
