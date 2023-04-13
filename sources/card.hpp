#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <string>
using namespace std;

namespace ariel
{
    enum Sign
    {
        Heart,
        Diamond,
        Club,
        Spade
    };

    enum Number
    {
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13,
        Ace = 14
        
    };

    enum Color
    {
        Red,
        Black
    };

    class Card
    {
    private:
        Sign sign;
        Number number;
        Color color;

    public:
        Card();
        Card(Number num, Sign sign, Color color);
        Number getNumber();
        Sign getSign();
        Color getColor();
        Card getCard();
        string toString();
        bool operator==(const Card &other) const;
        string to_string(const Color& color);
        string to_string(const Sign& sign);
        string to_string(const Number& number);
    };
}

#endif