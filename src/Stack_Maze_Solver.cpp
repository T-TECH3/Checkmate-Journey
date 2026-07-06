#include <iostream>
#include "Stack_Maze_Solver.h"
#include "Container_Maze_Solver.h"

using namespace std;

Stack_Maze_Solver::Stack_Maze_Solver()
{
    m_top = nullptr;
}

Stack_Maze_Solver::Stack_Maze_Solver(Container_Maze_Solver* current_container)
{
    m_top = current_container;
}

Stack_Maze_Solver::~Stack_Maze_Solver()
{
    return;
}

char Stack_Maze_Solver::pop()
{
    if (m_top != nullptr)
    {
        Container_Maze_Solver * top_container = m_top;
        m_top = m_top->get_next();
        top_container->set_next(nullptr);
        char return_value = top_container->get_contents();
        delete top_container;

        return return_value;
    }

    return '1';
}

char Stack_Maze_Solver::peek_content()
{
    if (m_top != nullptr)
    {
        return m_top->get_contents();
    }

    return '1';
}

bool Stack_Maze_Solver::peek_back_track()
{
    if (m_top != nullptr)
    {
        return m_top->get_back_track();
    }

    return false;
}

void Stack_Maze_Solver::push(char value, bool back_track)
{
    Container_Maze_Solver* new_container = new Container_Maze_Solver(value, back_track, m_top);
    m_top = new_container;

    return;
}

void Stack_Maze_Solver::free()
{
    while (m_top != nullptr)
    {
        Container_Maze_Solver* temp = m_top;
        m_top = m_top->get_next();
        delete temp;
    }

    m_top = nullptr;

    return;
}

bool Stack_Maze_Solver::is_stack_false()
{
    Container_Maze_Solver* iterator = m_top;

    while (iterator != nullptr)
    {
        if (iterator->get_back_track() == true)
        {
            return false;
        }

        iterator = iterator->get_next();
    }

    return true;
}

void Stack_Maze_Solver::display()
{
    Container_Maze_Solver* iterator = m_top;

    cout << "[";

    while (iterator != nullptr)
    {
        cout << iterator->get_contents();
        cout << iterator->get_back_track();

        if (iterator->get_next() != nullptr)
        {
            cout << ",";
        }

        iterator = iterator->get_next();
    }

    cout << "]                                                                                                                                                                                                          " << endl;

    return;
}
