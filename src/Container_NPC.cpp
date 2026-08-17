#include "Container_NPC.h"

// Default constructor
Container_NPC::Container_NPC()
{
    m_contents = nullptr;
    m_ptr_next = nullptr;
}

// Custom constructor
Container_NPC::Container_NPC(NPC* contents, Container_NPC* ptr_next)
{
    m_contents = contents;
    m_ptr_next = ptr_next;
}

// Destructor
Container_NPC::~Container_NPC()
{
    return;
}

// Return next
Container_NPC* Container_NPC::get_next()
{
    return m_ptr_next;
}

// Return contents
NPC* Container_NPC::get_contents()
{
    return m_contents;
}

// Set next
void Container_NPC::set_next(Container_NPC* ptr_next)
{
    m_ptr_next = ptr_next;
    return;
}

// Set contents
void Container_NPC::set_contents(NPC* contents)
{
    m_contents = contents;
    return;
}
