#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "SDL.h"

class Controller
{
    // Public methods and member for the class
    public:
        Controller();
        virtual ~Controller();

        bool connect_controller();
        void close_controller();

        char get_joy_1_direction();
        char get_button_pad_direction();
        bool get_button_b_input();
        bool get_button_y_input();
        bool get_button_a_input();
        bool get_button_x_input();

        void wait_until_button_a_input();
        void wait_until_button_x_input();

    // Private methods and members for the class
    private:
        SDL_GameController* m_game_controller;

};

#endif // CONTROLLER_H
