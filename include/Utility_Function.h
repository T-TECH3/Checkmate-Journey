#pragma once

#ifndef UTILITY_FUNCTION_H
#define UTILITY_FUNCTION_H
#include <iostream>
#include "Controller.h"

using namespace std;

// Definitions for functions
void show_cursor(bool);
void move_cursor(int, int);
void console_color(int, int, int);
int display_menu(string, int, string [], bool);


#endif // UTILITY_FUNCTION_H
