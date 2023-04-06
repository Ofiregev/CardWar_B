#include "player.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "card.hpp"

using namespace std;

namespace ariel
{
    Player::Player() {}

    Player::Player(string name)
    {
        this->name = name;
        this->points =0;
        this->cards_taken=0;
    }
    int Player::stacksize()
    {
        cout << this->personal_stack.size();
        return this->personal_stack.size();
    }

    void Player::generateStack()
    {
        while (this->personal_stack.size() < 26) {
        Number num = static_cast<Number>(rand() % 13 + 1);
        Sign sign = static_cast<Sign>(rand() % 4);
        Color color = (sign == Heart || sign == Diamond) ? Red : Black;
        
        // check if the card is already in the deck
        Card card(num,sign, color);
        auto it = std::find(personal_stack.begin(), personal_stack.end(), card);
        if (it == personal_stack.end()) {
            personal_stack.push_back(card);
        }
    }
    }

    int Player::cardesTaken()
    {
        return this->cards_taken;
    }
    string Player::get_name(){
        return this->name;
    }
    int Player::getPoints(){
        return this->points;
    }
    void Player::setPoints(int point){
        this->points = this->points+point;
    }
    Card Player::liftCard(){
        if(!this->personal_stack.empty()){
            Card top_card = this->personal_stack.front();
            personal_stack.erase(personal_stack.begin());
            return top_card;
        }
        throw("The stack is empty!");
    }
    // Stack Player::getPersonalStack(){
    //     return this->personal_stack;
    // }

    void Player::setCardsTaken(int cards){
        if(cards > 52){
            throw "error";
        }
        this->cards_taken = this->cards_taken+cards;
    }
    string Player::getStatus(){
        return (std::to_string(this->draws_number) + std::to_string(this->points) + std::to_string(this->cardesTaken()));
    }
    void Player::setDrawsNumber(int num){
        this->draws_number = num;
    }
    

};
