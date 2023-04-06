#include "player.hpp"
#include <iostream>
#include <string>

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
    void Player::setStackSize(int size){}
    int Player::stacksize()
    {
        return this->getPersonalStack().getSize();
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
        return personal_stack.getTopCard();
    }
    Stack Player::getPersonalStack(){
        return this->personal_stack;
    }
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
