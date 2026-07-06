#include "Unlock_Item.h"
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

// Default constuctor
Unlock_Item::Unlock_Item() : Item()
{
    return;
}

// Custom constuctor
Unlock_Item::Unlock_Item(string name, string item_symbol, int r, int g, int b, int price) : Item(name, name, name, item_symbol, r, g, b, price)
{
    string temp = name + " - " + to_string(price) + " coins";

    m_name_description = name + " (Unlocks a door)";

    m_name_description_price = temp;

    return;
}

// Deconstcuotr
Unlock_Item::~Unlock_Item()
{
    return;
}

// Use the item
void Unlock_Item::use_item()
{
    // Display this item can only be used when ineracting with a door
    void (system("CLS"));

    cout << "<--" << m_name << "-->" << endl;

    cout << "This item unlocks a door, interacted with the door to use this item" << endl;

    cout << endl << "Press A to continue...";
    Game::game_controller.wait_until_button_a_input();


    void (system("CLS"));

    return;
}

// This item can't regenerate (needed for polymorphism)
void Unlock_Item::regenerate_item()
{
    return;
}
