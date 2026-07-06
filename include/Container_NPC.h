#ifndef CONTAINER_NPC_H
#define CONTAINER_NPC_H

class NPC;

class Container_NPC
{
    // Private methods and members for the class
    private:
        Container_NPC* m_ptr_next;
        NPC* m_contents;

    // Public methods and member for the class
    public:
        Container_NPC();
        Container_NPC(NPC*, Container_NPC*);
        virtual ~Container_NPC();

        Container_NPC* get_next();
        NPC* get_contents();
        void set_next(Container_NPC*);
        void set_contents(NPC*);
};

#endif
