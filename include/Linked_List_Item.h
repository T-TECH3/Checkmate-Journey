#ifndef LINKED_LIST_ITEM_H
#define LINKED_LIST_ITEM_H
#include "iostream"

using namespace std;

class Node_Item;
class Item;

class Linked_List_Item
{
    // Public members of Linked_List_Item
    public:
        Linked_List_Item();
        Linked_List_Item(Node_Item*);
        virtual ~Linked_List_Item();

        Node_Item* get_front();
        Node_Item* get_back();
        int get_node_amount();

        void set_front(Node_Item*);
        void set_back(Node_Item*);
        void set_node_amount(int);

        Node_Item* search_for_node (Node_Item*);

        // A display function that uses an iterator to display the contents of the list
        void display (bool);

        // A search function returns whether a given value is in the list
        bool search_for_value (Item*);

        // An index function that returns the nth value in the list.
        Item* find_index_value (int);

        // (NEW) An index function that returns the nth Link in the list. (NEW)
        Node_Item* search_for_node_index (int);

        // A findNodeWithValue function that returns the Node where the first occurrence of a specified value is stored.
        Node_Item* find_node_with_value (Item*);

        // An insert function that inserts a given Node after another specified Node in a list.
        void insert_node_after (Node_Item*, Node_Item*);

        // An insert function that inserts a value into this list after the first occurrence of another specified value in the list. (Look, it's encapsulation!)
        void insert_value_after (Item*, Item*);

        void insert_value_start (Item*);

        // A remove function that removes a Node from the list. This function will not return the value stored in that Node.
        void remove_node(Node_Item*);

        // A remove function that removes the nth Node from the list.
        void remove_index_value(int);

        // A remove function that removes the Node storing the first occurrence of a specified value from the list.
        void remove_value(Item*);

        void clear_list();

        int display_menu(string, int, bool, bool);

    // Private members of Linked_List_Item
    private:
        Node_Item* m_ptr_front;
        Node_Item* m_ptr_back;
        int m_node_amount;
};

#endif // LINKED_LIST_ITEM_H
