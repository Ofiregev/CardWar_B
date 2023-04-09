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
        return std::to_string(this->number) + " " + std::to_string(this->sign) + " " + std::to_string(this->color);
        ;
    }
    bool Card::operator==(const Card &other) const
    {
        return sign == other.sign && number == other.number && color == other.color;
    }

}
