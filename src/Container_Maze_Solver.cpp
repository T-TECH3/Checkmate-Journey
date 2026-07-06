#include "Container_Maze_Solver.h"

// Default constuctor
Container_Maze_Solver::Container_Maze_Solver()
{
    m_next = nullptr;
    m_contents = 0;
    m_back_track = false;
    return;
}

// Custom constuctor
Container_Maze_Solver::Container_Maze_Solver(char contents, bool back_track, Container_Maze_Solver* next)
{
    m_contents = contents;
    m_next = next;
    m_back_track = back_track;

    return;
}

// Deconstuctor
Container_Maze_Solver::~Container_Maze_Solver()
{
    return;
}

// Get methods for all members
Container_Maze_Solver* Container_Maze_Solver::get_next()
{
    return m_next;
}

char Container_Maze_Solver::get_contents()
{
    return m_contents;
}

bool Container_Maze_Solver::get_back_track()
{
    return m_back_track;
}

// Set methods for all members
void Container_Maze_Solver::set_next(Container_Maze_Solver* current_container)
{
    m_next = current_container;
    return;
}

void Container_Maze_Solver::set_all(char value, bool back_track)
{
    m_contents = value;
    m_back_track = back_track;
    return;
}

void Container_Maze_Solver::set_contents(char value)
{
    m_contents = value;
    return;
}

void Container_Maze_Solver::set_back_track(bool back_track)
{
    m_back_track = back_track;
    return;
}
