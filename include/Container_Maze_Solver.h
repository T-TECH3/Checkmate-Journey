#ifndef CONTAINER_MAZE_SOLVER_H
#define CONTAINER_MAZE_SOLVER_H

class Container_Maze_Solver
{
    // Public methods and member for the class
    public:
        Container_Maze_Solver();
        Container_Maze_Solver(char, bool, Container_Maze_Solver*);
        virtual ~Container_Maze_Solver();

        Container_Maze_Solver* get_next();
        char get_contents();
        bool get_back_track();

        void set_next(Container_Maze_Solver*);
        void set_all(char, bool);
        void set_contents(char);
        void set_back_track(bool);

    // Private methods and members for the class
    private:
        Container_Maze_Solver* m_next;
        char m_contents;
        bool m_back_track;
};

#endif // CONTAINER_MAZE_SOLVER_H
