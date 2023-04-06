#include <iostream>
#include <string>
#include "card.hpp"
using namespace std;

namespace ariel
{
    Card::Card(){
        
    }
    Card::Card(Number num, Sign sign, Color color){
        this->sign=sign;
        this->number=num;
        this->color=color;
    }
    Card Card::getCard()
    {
        return this->generateCard();
    }
    Number Card::getNumber()
    {
        return this->number;
    }
    string Card::toString(){
        return "card";
    }
    Card Card::generateCard(){
        Number num = static_cast<Number>(rand() % 13 + 1); // generate a random number between 1-13
        Sign sign = static_cast<Sign>(rand() % 4); // generate a random sign between 0-3
        Color color = (sign == Heart || sign == Diamond) ? Red : Black; // determine the color based on the sign
        Card c = Card(num, sign,color);
        return c;
        
    }


}
