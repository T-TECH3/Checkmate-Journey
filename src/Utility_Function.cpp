#include "Utility_Function.h"
#include <iostream>
#include <windows.h>
#include "Controller.h"
#include "Game.h"

using namespace std;

// Display or not displpay the text cursor
void show_cursor(bool show_cursor)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show_cursor;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Move the cursor to a x and y position
void move_cursor(int column, int row)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT) column, (SHORT) row};
	SetConsoleCursorPosition(hOut, coord);
}

// Change the console color
void console_color(int r, int g, int b)
{
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";

    return;
}

// Display a menu that can be interacted wiht the constoller
int display_menu(string question, int number_of_options, string options [], bool clear_screen)
{
    Sleep(250);

    int current_option = 0;
    string triangle = "\u25C1";

    console_color(255,255,255);

    if (clear_screen == true)
    {
        void (system("CLS"));
    }


    cout << question << endl;

    for (int i = 0; i < number_of_options; i++)
    {
        cout << "[" << i << "] " << options[i];

        if (i == current_option)
        {
            console_color(0, 136, 255);

            cout << " " << triangle;

            console_color(255, 255, 255);
        }
        cout << endl;
    }


    while (Game::game_controller.get_button_a_input() != true)
    {
        if (Game::game_controller.get_joy_1_direction() == 'U')
        {
            move_cursor(options[current_option].size() + 4,current_option + 1);
            cout << "  ";

            current_option--;

            if (current_option == -1)
            {
                current_option = number_of_options - 1;
            }

            move_cursor(options[current_option].size() + 4,current_option + 1);

            console_color(0, 136, 255);

            cout << " " << triangle;

            console_color(255, 255, 255);

        }
        else if (Game::game_controller.get_joy_1_direction() == 'D')
        {
            move_cursor(options[current_option].size() + 4,current_option + 1);
            cout << "  ";

            current_option++;

            if (current_option == number_of_options )
            {
                current_option = 0;
            }

            move_cursor(options[current_option].size() + 4,current_option + 1);

            console_color(0, 136, 255);

            cout << " " << triangle;

            console_color(255, 255, 255);
        }

        Sleep(150);
    }

    return current_option;
}
