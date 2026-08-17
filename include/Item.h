#ifndef ITEM_H
#define ITEM_H
#include "iostream"

using namespace std;

class Item
{
    // Public methods and member for the class
    public:
        Item();
        Item(string, string, string, string, int, int, int, int);
        virtual ~Item();

        string get_name();
        string get_name_description();
        string get_name_description_price();
        string get_symbol();
        int get_r_color();
        int get_g_color();
        int get_b_color();
        int get_price();

        void set_name(string);
        void set_name_description(string);
        void set_name_description_price(string);
        void set_symbol(string);
        void set_color(int, int, int);
        void set_price(int);

        void display();

        virtual void use_item();
        virtual void regenerate_item();

    // Protected methods and members for the class
    protected:
        string m_name;
        string m_name_description;
        string m_name_description_price;
        string m_item_symbol;
        int m_r_color;
        int m_g_color;
        int m_b_color;
        int m_price;

};

#endif // ITEM_H
