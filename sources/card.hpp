#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <string>
using namespace std;



namespace ariel {
    enum Sign {
        Heart,
        Diamond,
        Club,
        Spade
    };

    enum Number {
        Ace = 1,
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
        King = 13
    };

    enum Color {
        Red,
        Black
    };

    class Card {
        private:
            Sign sign;
            Number number;
            Color color;

        public:
            Card();
            Card(Number num, Sign sign, Color color);
            Number getNumber();
            Card getCard();
            string toString();
            Card generateCard();

  };
}

#endif