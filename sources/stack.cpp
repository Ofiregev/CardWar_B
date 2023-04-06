#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "stack.hpp"
using namespace std;

namespace ariel
{
    Stack::Stack() {
    }
    Stack::Stack(int size){}
    Card Stack::getTopCard()
    {
        this->size = this->size - 1;
        return this->top_card;
    }
    int Stack::getSize()
    {
        return this->size;
    }
    void Stack::takeAcard()
    {
        this->size = this->size-1;
    }
    void Stack::setTopCard(Card card) {
        this->top_card = card;
    }
    void Stack::setStackSize(int size){
        if(size < 0){
            throw ("exeption");
        }
        this->size = size;
    }



}
