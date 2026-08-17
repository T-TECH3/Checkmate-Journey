#include <iostream>
#include <SDL.h>
#include "Controller.h"
#include <cmath>
#include "windows.h"

using namespace std;

// Default constuctor
Controller::Controller()
{
    bool connected = connect_controller();

    if (connected == false)
    {
        cout << "Error: Cannot Connect Game Controller";
    }
    return;
}

// Deconstuctor
Controller::~Controller()
{
    return;
}

// Connect the controller with SDL 2
bool Controller::connect_controller()
{
	bool success = true;

	SDL_SetHint(SDL_HINT_JOYSTICK_THREAD, "1");
	if( SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error:" << SDL_GetError();
		success = false;
	}
	else
	{
		if( SDL_NumJoysticks() < 1 )
		{
			cout << "Warning: No joysticks connected!";
		}
		else
		{
			m_game_controller = SDL_GameControllerOpen( 0 );
			if(m_game_controller == NULL )
			{
				cout << "Warning: Unable to open game controller! SDL Error:" << SDL_GetError();
			}
		}
    }

	return success;
}

// Close the controller with SDL 2
void Controller::close_controller()
{
   	SDL_GameControllerClose(m_game_controller);
	m_game_controller = nullptr;

	return;
}

// Return the direction of the left joy
char Controller::get_joy_1_direction()
{
    if (m_game_controller == nullptr)
    {
        return 'N';
    }

    Sint16 axis_x = SDL_GameControllerGetAxis(m_game_controller, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 axis_y = SDL_GameControllerGetAxis(m_game_controller, SDL_CONTROLLER_AXIS_LEFTY);

    const Sint16 dead_zone = 10000;

    if (abs(axis_x) < dead_zone && abs(axis_y) < dead_zone)
    {
        return 'N';
    }
    else if (axis_x > dead_zone and axis_y < dead_zone and axis_y > -dead_zone)
    {
        return 'R';
    }
    else if (axis_x < -dead_zone and axis_y < dead_zone and axis_y > -dead_zone)
    {
        return 'L';
    }
    else if (axis_y > dead_zone and axis_x < dead_zone and axis_x > -dead_zone)
    {
        return 'D';
    }
    else if (axis_y < -dead_zone and axis_x < dead_zone and axis_x > -dead_zone)
    {
        return 'U';
    }

    return 'N';
}

// Return the direction of the button pad
char Controller::get_button_pad_direction()
{
    Uint8 up = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
    Uint8 down = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    Uint8 left = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    Uint8 right = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    if (unsigned(up) == 1)
    {
        return 'U';
    }
    if (unsigned(down) == 1)
    {
        return 'D';
    }
    if (unsigned(left) == 1)
    {
        return 'L';
    }
    if (unsigned(right) == 1)
    {
        return 'R';
    }

    return 'N';
}

// Return if the b button is pressed
bool Controller::get_button_b_input()
{
    Uint8 t3 = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_B);

    if (unsigned(t3) == 1)
    {
        return true;
    }

    return false;
}

// Return if the y button is pressed
bool Controller::get_button_y_input()
{
    Uint8 t3 = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_Y);

    if (unsigned(t3) == 1)
    {
        return true;
    }

    return false;
}

// Return if the a button is pressed
bool Controller::get_button_a_input()
{
    Uint8 t3 = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_A);

    if (unsigned(t3) == 1)
    {
        return true;
    }

    return false;
}

// Return if the x button is pressed
bool Controller::get_button_x_input()
{
    Uint8 t3 = SDL_GameControllerGetButton(m_game_controller, SDL_CONTROLLER_BUTTON_X);

    if (unsigned(t3) == 1)
    {
        return true;
    }

    return false;
}

// Return when the a button is pressed
void Controller::wait_until_button_a_input()
{
    Sleep(500);

    bool quit = false;

    while (quit == false)
    {
        if (get_button_a_input() == true)
        {
            quit = true;
        }

        Sleep(50);
    }

    return;
}

// Return when the x button is pressed
void Controller::wait_until_button_x_input()
{
    Sleep(500);

    bool quit = false;

    while (quit == false)
    {
        if (get_button_x_input() == true)
        {
            quit = true;
        }

        Sleep(50);
    }

    return;
}
