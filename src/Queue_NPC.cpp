#include "iostream"
#include "Queue_NPC.h"
#include "Container_NPC.h"
#include "NPC.h"

using namespace std;

// Default constructor
Queue_NPC::Queue_NPC()
{
    m_ptr_front = nullptr;
    m_ptr_back = nullptr;
}

// Custom constructor
Queue_NPC::Queue_NPC(Container_NPC* ptr_container)
{
    m_ptr_front = ptr_container;
    m_ptr_back = ptr_container;
}

// Destructor
Queue_NPC::~Queue_NPC()
{
    return;
}

// Return front ptr
Container_NPC* Queue_NPC::get_front()
{
    return m_ptr_front;
}

// Return back ptr
Container_NPC* Queue_NPC::get_back()
{
    return m_ptr_back;
}

// Set front ptr
void Queue_NPC::set_front(Container_NPC* ptr_front)
{
    m_ptr_front = ptr_front;
    return;
}

// Set back ptr
void Queue_NPC::set_back(Container_NPC* ptr_back)
{
    m_ptr_back = ptr_back;
    return;
}

// Pop the first item in the queue
NPC* Queue_NPC::pop()
{
    // If front (and back) are nullptr throw an error message
    if (m_ptr_front == nullptr)
    {
        throw("Error: Popping from empty queue");
    }
    else
    {
        // Put contents into variable
        NPC* contents = m_ptr_front->get_contents();
        // Unlink the old front and set the old front's next container to the next/front
        Container_NPC* old_front = m_ptr_front;
        m_ptr_front = old_front->get_next();
        old_front->set_next(nullptr);

        // If front ptr becomes nullptr so must be the back
        if (m_ptr_front == nullptr)
        {
            m_ptr_back = nullptr;
        }

        // Delete the old front
        delete old_front;

        // Return the contents
        return contents;
    }
}

// Peek at the first item in a queue
NPC* Queue_NPC::peek()
{
    // If ptr front is nullptr throw an error message
    if (m_ptr_front == nullptr)
    {
        throw("Error: Peeking from empty queue");
    }
    else
    {
        // Return the value of the first container
        return m_ptr_front->get_contents();
    }
}

// Push an item into a queue
void Queue_NPC::push(NPC* new_container_contents)
{
    // Create a new container
    Container_NPC* ptr_new_container = new Container_NPC(new_container_contents, nullptr);

    // If the front and back are nullptr set both to new container
    if (m_ptr_front == nullptr && m_ptr_back == nullptr)
    {
        m_ptr_front = ptr_new_container;
        m_ptr_back = ptr_new_container;
    }
    // If there is already a container, change the old back to the new container and the new back ptr to the new container
    else
    {
        m_ptr_back->set_next(ptr_new_container);
        m_ptr_back = ptr_new_container;
    }

    return;
}

// Return the size of the queue
int Queue_NPC::get_size()
{
    int number = 0;
    Container_NPC* iterator = m_ptr_front;

    while (iterator != nullptr)
    {
        number++;
        iterator = iterator->get_next();
    }

    return number;
}

// Display the queue
void Queue_NPC::display()
{
    Container_NPC* iterator = m_ptr_front;

    cout << "[";

    // Go through the queue using an iterator and display each value
    while (iterator != nullptr)
    {
        cout << iterator->get_contents();

        // If last value do not display comma after displaying it
        if (iterator->get_next() != nullptr)
        {
            cout << ",";
        }

        iterator = iterator->get_next();
    }
    cout << "]";

    return;
}
