#ifndef NODE_ITEM_H
#define NODE_ITEM_H

class Item;

class Node_Item
{
    // Public members of Node_Item
    public:
        Node_Item();
        Node_Item(Item*, Node_Item*, Node_Item*);
        virtual ~Node_Item();

        Node_Item* get_next();
        Node_Item* get_previous();
        Item* get_contents();

        void set_next(Node_Item*);
        void set_previous(Node_Item*);
        void set_contents(Item*);

    // Private members of Node_Item
    private:
        Node_Item* m_ptr_next;
        Node_Item* m_ptr_previous;
        Item* m_contents;
};

#endif // NODE_ITEM_H
