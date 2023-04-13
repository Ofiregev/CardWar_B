#include <iostream>
#include <string>
#include "card.hpp"
using namespace std;

namespace ariel
{
    Card::Card()
    {
    }
    Card::Card(Number num, Sign sign, Color color)
    {
        this->sign = sign;
        this->number = num;
        this->color = color;
    }
    Number Card::getNumber()
    {
        return this->number;
    }
    Sign Card::getSign()
    {
        return this->sign;
    }
    Color Card::getColor()
    {
        return this->color;
    }
    string Card::toString()
    {
        return this->to_string(this->number) + " " + this->to_string(this->sign) + " " + this->to_string(this->color);
        ;
    }
    bool Card::operator==(const Card &other) const
    {
        return sign == other.sign && number == other.number && color == other.color;
    }
    string Card::to_string(const Color& color)
{
    switch (color)
    {
        case Color::Red:
            return "Red";
        case Color::Black:
            return "Black";
        default:
            return "Unknown";
    }
}

string Card::to_string(const Sign& sign)
{
    switch (sign)
    {
        case Sign::Heart:
            return "Heart";
        case Sign::Diamond:
            return "Diamond";
        case Sign::Club:
            return "Club";
        case Sign::Spade:
            return "Spade";
        default:
            return "Unknown";
    }
}

string Card::to_string(const Number& number)
{
    switch (number)
    {
        case Number::Two:
            return "Two";
        case Number::Three:
            return "Three";
        case Number::Four:
            return "Four";
        case Number::Five:
            return "Five";
        case Number::Six:
            return "Six";
        case Number::Seven:
            return "Seven";
        case Number::Eight:
            return "Eight";
        case Number::Nine:
            return "Nine";
        case Number::Ten:
            return "Ten";
        case Number::Jack:
            return "Jack";
        case Number::Queen:
            return "Queen";
        case Number::King:
            return "King";
        case Number::Ace:
            return "Ace";
        default:
            return "Unknown";
    }
}
}
