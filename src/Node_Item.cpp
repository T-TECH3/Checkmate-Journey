#include<iostream>
#include "Node_Item.h"

using namespace std;

// Default constructor
Node_Item::Node_Item()
{
    m_contents = nullptr;
    m_ptr_next = nullptr;
    m_ptr_previous = nullptr;
    return;
}

// Custom constructor
Node_Item::Node_Item(Item* contents, Node_Item* ptr_next, Node_Item* ptr_previous)
{
    m_contents = contents;
    m_ptr_next = ptr_next;
    m_ptr_previous = ptr_previous;

    return;
}

// Destructor
Node_Item::~Node_Item()
{
    return;
}

// Return the ptr to next
Node_Item* Node_Item::get_next()
{
    return m_ptr_next;
}

// Return the ptr to previous
Node_Item* Node_Item::get_previous()
{
    return m_ptr_previous;
}

// Return the contents
Item* Node_Item::get_contents()
{
    return m_contents;
}

// Set ptr next with a value
void Node_Item::set_next(Node_Item* ptr_next)
{
    m_ptr_next = ptr_next;
    return;
}

// Set ptr previous with a value
void Node_Item::set_previous(Node_Item* ptr_previous)
{
    m_ptr_previous = ptr_previous;
    return;
}

// Set contents with a value
void Node_Item::set_contents(Item* contents)
{
    m_contents = contents;
    return;
}
