#include "Item.h"
#include "Utility_Function.h"

// Default constuctor
Item::Item()
{
    m_name = "Blank Name";
    m_name_description  = "Blank Name Description";
    m_name_description_price = "Blank Name Description Price";
    m_item_symbol = "?";
    m_r_color = 255;
    m_g_color = 255;
    m_b_color = 255;

    m_price = 0;

    return;
}

// Custom constuctor
Item::Item(string name, string name_description, string name_description_price, string item_symbol, int r, int g, int b, int price)
{
    m_name = name;
    m_name_description = name_description;
    m_name_description_price = name_description_price;
    m_item_symbol = item_symbol;

    m_r_color = r;
    m_g_color = g;
    m_b_color = b;

    m_price = price;

    return;
}

// Deconstuctor
Item::~Item()
{
    return;
}

// Get methods for all members
string Item::get_name()
{
    return m_name;
}

string Item::get_name_description()
{
    return m_name_description;
}

string Item::get_name_description_price()
{
    return m_name_description_price;
}

string Item::get_symbol()
{
    return m_item_symbol;
}

int Item::get_r_color()
{
    return m_r_color;
}

int Item::get_g_color()
{
    return m_g_color;
}

int Item::get_b_color()
{
    return m_b_color;
}

int Item::get_price()
{
    return m_price;
}

// Set methods for all members
void Item::set_name(string name)
{
    m_name = name;
    return;
}

void Item::set_name_description(string name_description)
{
    m_name = name_description;
    return;
}

void Item::set_name_description_price(string name_description_price)
{
    m_name_description_price = name_description_price;
    return;
}

void Item::set_symbol(string symbol)
{
    m_item_symbol = symbol;
    return;
}

void Item::set_color(int r, int g, int b)
{
    m_r_color = r;
    m_g_color = g;
    m_b_color = b;

    return;
}

void Item::set_price(int price)
{
    m_price = price;
    return;
}

// Display the item with its color
void Item::display()
{
    console_color(m_r_color, m_b_color, m_g_color);

    cout << m_item_symbol << " ";

    return;
}

// Display you can use this item
void Item::use_item()
{
    cout << "Error: You can't use this Item" << endl;
    return;
}

// Regenrate item (does not regenerate)
void Item::regenerate_item()
{
    return;
}
