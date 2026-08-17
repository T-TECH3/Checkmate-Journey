#ifndef STACK_MAZE_SOLVER_H
#define STACK_MAZE_SOLVER_H

class Container_Maze_Solver;

class Stack_Maze_Solver
{
    // Public methods and member for the class
    public:
        Stack_Maze_Solver();
        Stack_Maze_Solver(Container_Maze_Solver*);
        virtual ~Stack_Maze_Solver();

        Container_Maze_Solver* get_top();
        void set_top(Container_Maze_Solver *);

        char pop();
        char peek_content();
        bool peek_back_track();
        void push(char, bool);
        void free();

        bool is_stack_false();

        void display();

    // Private methods and members for the class
    private:
        Container_Maze_Solver* m_top;
};

#endif // STACK_MAZE_SOLVER_H
