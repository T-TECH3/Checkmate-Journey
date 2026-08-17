#ifndef QUEUE_NPC_H
#define QUEUE_NPC_H

class Container_NPC;
class NPC;

class Queue_NPC
{
    // Private variables for Queue_NPC
    private:
        Container_NPC* m_ptr_front;
        Container_NPC* m_ptr_back;

    // Public methods for Queue_NPC
    public:
        Queue_NPC();
        Queue_NPC(Container_NPC*);
        virtual ~Queue_NPC();

        Container_NPC* get_front();
        Container_NPC* get_back();
        void set_front(Container_NPC*);
        void set_back(Container_NPC*);

        NPC* pop();
        NPC* peek();
        void push(NPC*);

        int get_size();

        void display();
};

#endif // QUEUE_NPC_H
