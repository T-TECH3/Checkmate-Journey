#include <iostream>
#include "Linked_List_Item.h"
#include "Node_Item.h"
#include "Item.h"
#include "windows.h"
#include "Game.h"
#include "Utility_Function.h"

using namespace std;

// Default constructor
Linked_List_Item::Linked_List_Item()
{
    m_node_amount = 0;
    m_ptr_front = nullptr;
    m_ptr_back = nullptr;
    return;
}

// Custom constructor
Linked_List_Item::Linked_List_Item(Node_Item* ptr_node)
{
    if (ptr_node == nullptr)
    {
        m_node_amount = 0;
    }
    else
    {
        m_node_amount = 1;
    }

    m_ptr_front = ptr_node;
    m_ptr_back = ptr_node;
    return;
}

// Destructor
Linked_List_Item::~Linked_List_Item()
{
    return;
}

// Return the ptr front
Node_Item* Linked_List_Item::get_front()
{
    return m_ptr_front;
}

// Return the ptr back
Node_Item* Linked_List_Item::get_back()
{
    return m_ptr_back;
}

// Return the node amount
int Linked_List_Item::get_node_amount()
{
    return m_node_amount;
}

// Set ptr_front with value
void Linked_List_Item::set_front(Node_Item* ptr_front)
{
    m_ptr_front = ptr_front;
    return;
}

// Set ptr back with value
void Linked_List_Item::set_back(Node_Item* ptr_back)
{
    m_ptr_back = ptr_back;
    return;
}

// Set node amount with value
void Linked_List_Item::set_node_amount(int node_amount)
{
    m_node_amount = node_amount;
    return;
}

// Search for a node; return node if found, otherwise nullptr
Node_Item* Linked_List_Item::search_for_node(Node_Item* current_node)
{
    Node_Item* iterator = m_ptr_front;
    bool end_loop = false;

    while (iterator != nullptr && !end_loop)
    {
        if (iterator == current_node)
        {
            end_loop = true;
        }
        else
        {
            iterator = iterator->get_next();
        }
    }

    return iterator;
}

// Display the linked list
void Linked_List_Item::display(bool display_empty)
{
    Node_Item* iterator = m_ptr_front;

    if (iterator == nullptr)
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        while (iterator != nullptr)
        {
            cout << iterator->get_contents()->get_name() << endl;
            iterator = iterator->get_next();
        }
    }

    return;
}

// Return whether a value is in the list
bool Linked_List_Item::search_for_value(Item* value)
{
    Node_Item* node = find_node_with_value(value);
    return node != nullptr;
}

// Find the value at an index
Item* Linked_List_Item::find_index_value(int index)
{
    Node_Item* node_with_value = nullptr;

    try
    {
        node_with_value = search_for_node_index(index);
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }

    if (node_with_value == nullptr)
    {
        throw ("Error: find_index_value was sent nullptr by search_for_node_index");
    }

    return node_with_value->get_contents();
}

// Return the node at a given index
Node_Item* Linked_List_Item::search_for_node_index(int index)
{
    if (index < 0 || index >= m_node_amount)
    {
        throw ("Error: search_for_node_index was sent an index out of range");
    }

    Node_Item* iterator = m_ptr_front;

    for (int i = 0; i < index; i++)
    {
        if (iterator == nullptr)
        {
            throw ("Error: search_for_node_index hit nullptr before out of range");
        }
        iterator = iterator->get_next();
    }

    return iterator;
}

// Return a node with a value
Node_Item* Linked_List_Item::find_node_with_value(Item* value)
{
    Node_Item* iterator = m_ptr_front;

    while (iterator != nullptr)
    {
        if (iterator->get_contents() == value)
        {
            return iterator;
        }
        iterator = iterator->get_next();
    }

    return nullptr;
}

// Insert node after another node
void Linked_List_Item::insert_node_after(Node_Item* ptr_new, Node_Item* ptr_previous)
{
    if (ptr_new != nullptr)
    {
        Node_Item* ptr_new_in_list = search_for_node(ptr_new);
        Node_Item* ptr_previous_in_list = search_for_node(ptr_previous);

        if (ptr_new_in_list == nullptr && ptr_previous_in_list != nullptr)
        {
            Node_Item* ptr_next = ptr_previous->get_next();

            if (ptr_next == nullptr)
            {
                m_ptr_back = ptr_new;
            }
            else
            {
                ptr_next->set_previous(ptr_new);
            }

            ptr_new->set_next(ptr_next);
            ptr_previous->set_next(ptr_new);
            ptr_new->set_previous(ptr_previous);

            m_node_amount++;
        }
        else if (ptr_new_in_list == nullptr && ptr_previous == nullptr)
        {
            if (m_ptr_front == nullptr)
            {
                ptr_new->set_next(nullptr);
                ptr_new->set_previous(nullptr);
                m_ptr_front = ptr_new;
                m_ptr_back = ptr_new;
            }
            else
            {
                m_ptr_front->set_previous(ptr_new);
                ptr_new->set_next(m_ptr_front);
                ptr_new->set_previous(nullptr);
                m_ptr_front = ptr_new;
            }
            m_node_amount++;
        }
        else
        {
            throw ("Error: insert_node_after was sent a new_node that was already in the list");
        }
    }
    else
    {
        throw ("Error: insert_node_after was sent nullptr as the new node");
    }

    return;
}

// Insert value after another value
void Linked_List_Item::insert_value_after(Item* new_value, Item* previous_value)
{
    Node_Item* ptr_previous_node = find_node_with_value(previous_value);

    if (ptr_previous_node != nullptr)
    {
        Node_Item* new_node = new Node_Item(new_value, nullptr, nullptr);
        try
        {
            insert_node_after(new_node, ptr_previous_node);
        }
        catch (const char* error_message)
        {
            cout << error_message << endl;
        }
    }
    else
    {
        throw ("Error: insert_value_after was sent a previous_value that was not in the list");
    }

    return;
}

// Insert value at start
void Linked_List_Item::insert_value_start (Item* value)
{
    Node_Item* node = new Node_Item(value, nullptr, nullptr);

    insert_node_after(node, nullptr);

    return;
}

// Remove a node
void Linked_List_Item::remove_node(Node_Item* current_node)
{
    current_node = search_for_node(current_node);

    if (current_node != nullptr)
    {
        if (current_node->get_next() == nullptr)
        {
            m_ptr_back = current_node->get_previous();

            if (current_node->get_previous() != nullptr)
            {
                current_node->get_previous()->set_next(nullptr);
            }
        }
        else
        {
            if (current_node->get_previous() != nullptr)
            {
                current_node->get_previous()->set_next(current_node->get_next());
            }
        }

        if (current_node->get_previous() == nullptr)
        {
            m_ptr_front = current_node->get_next();

            if (current_node->get_next() != nullptr)
            {
                current_node->get_next()->set_previous(nullptr);
            }
        }
        else
        {
            if (current_node->get_next() != nullptr)
            {
                current_node->get_next()->set_previous(current_node->get_previous());
            }
        }

        current_node->set_next(nullptr);
        current_node->set_previous(nullptr);

        m_node_amount--;

    }
    else
    {
        throw ("Error: remove_node was sent a node that was not in the list");
    }

    return;
}

// Remove a node at an index
void Linked_List_Item::remove_index_value(int index)
{
    Node_Item* removing_node = nullptr;

    try
    {
        removing_node = search_for_node_index(index);
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;

    }

    try
    {
        remove_node(removing_node);
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }

    return;
}

// Remove a node with a value
void Linked_List_Item::remove_value(Item* value)
{
    Node_Item* removing_node = find_node_with_value(value);

    if (removing_node != nullptr)
    {
        remove_node(removing_node);
    }
    else
    {
        throw ("Error: remove_value was sent nullptr by find_node_with_value");
    }

    return;
}

// Remove all items from the list
void Linked_List_Item::clear_list()
{
    Node_Item* iterator = m_ptr_front;
    Node_Item* current_node = nullptr;

    while (iterator != nullptr)
    {
        current_node = iterator;
        iterator = iterator->get_next();
        delete current_node ;
    }

    m_ptr_front = nullptr;
    m_ptr_back = nullptr;

    m_node_amount = 0;

    return;
}

// Display all the items as a menu
int Linked_List_Item::display_menu(string question, int offset, bool clear_screen, bool with_price)
{
    Sleep (250);

    int current_option = 0;
    string triangle = "\u25C1";

    console_color(255,255,255);

    if (clear_screen == true)
    {
        void (system("CLS"));
    }

    cout << question << endl;

    if (m_node_amount != 0)
    {
        int i = 0;

        Node_Item* iterator = m_ptr_front;

        while (iterator != nullptr)
        {
            if (with_price == false)
            {
                cout << "[" << i << "] " << iterator->get_contents()->get_name_description();
            }
            else
            {
                cout << "[" << i << "] " << iterator->get_contents()->get_name_description_price();
            }

            if (i == current_option)
            {
                console_color(0, 136, 255);

                cout << " " << triangle;

                console_color(255, 255, 255);
            }
            cout << endl;

            iterator = iterator->get_next();

            i++;
        }

        cout << endl << "Press A to select or X to continue...";

        while (Game::game_controller.get_button_a_input() != true and Game::game_controller.get_button_x_input() != true)
        {
            if (Game::game_controller.get_joy_1_direction() == 'U')
            {
                if (with_price == false)
                {
                    move_cursor(find_index_value(current_option)->get_name_description().size() + 4, current_option + 1 + offset);
                }
                else
                {
                    move_cursor(find_index_value(current_option)->get_name_description_price().size() + 4, current_option + 1 + offset);
                }

                cout << "  ";

                current_option--;

                if (current_option < 0)
                {
                    current_option = m_node_amount - 1;
                }

                if (with_price == false)
                {
                    move_cursor(find_index_value(current_option)->get_name_description().size() + 4, current_option + 1 + offset);
                }
                else
                {
                    move_cursor(find_index_value(current_option)->get_name_description_price().size() + 4, current_option + 1 + offset);
                }

                console_color(0, 136, 255);

                cout << " " << triangle;

                console_color(255, 255, 255);

            }
            else if (Game::game_controller.get_joy_1_direction() == 'D')
            {
                if (with_price == false)
                {
                    move_cursor(find_index_value(current_option)->get_name_description().size() + 4, current_option + 1 + offset);
                }
                else
                {
                    move_cursor(find_index_value(current_option)->get_name_description_price().size() + 4, current_option + 1 + offset);
                }

                cout << "  ";

                current_option++;

                if (current_option >= m_node_amount)
                {
                    current_option = 0;
                }

                if (with_price == false)
                {
                    move_cursor(find_index_value(current_option)->get_name_description().size() + 4, current_option + 1 + offset);
                }
                else
                {
                    move_cursor(find_index_value(current_option)->get_name_description_price().size() + 4, current_option + 1 + offset);
                }

                console_color(0, 136, 255);

                cout << " " << triangle;

                console_color(255, 255, 255);
            }

            Sleep(150);
        }

        if (Game::game_controller.get_button_x_input() == true)
        {
            current_option = -1;
        }
    }
    else
    {
        cout << "[Empty]" << endl;

        cout << endl << "Press X to continue...";

        Game::game_controller.wait_until_button_x_input();

        current_option = -1;
    }

    return current_option;
}
