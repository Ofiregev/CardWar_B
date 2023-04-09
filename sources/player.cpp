#include "player.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "card.hpp"

using namespace std;

namespace ariel
{
    Player::Player() : personal_stack(vector<Card>()) {}

    Player::Player(string name) : name(name), personal_stack(vector<Card>()) {}

        void Player::setPersonalStack(vector<Card> *stack)
    {
        // Check that the input vector has exactly 26 cards
        if (stack->size() != 26)
        {
            throw std::invalid_argument("Input vector size is not 26");
        }
        this->personal_stack = *stack;
    }

    int Player::stacksize()
    {
        return this->getPersonalStack().size();
    }

    vector<Card> Player::getPersonalStack()
    {
        return personal_stack;
    }

    int Player::cardesTaken()
    {
        return this->cards_taken;
    }

    string Player::getName()
    {
        return this->name;
    }

    int Player::getPoints()
    {
        return this->points;
    }

    void Player::setPoints(int point)
    {
        this->points = this->points + point;
    }

    Card Player::liftCard() // get a card from the stack
    {
        if (!this->personal_stack.empty())
        {
            Card top_card = this->personal_stack.front();
            personal_stack.erase(personal_stack.begin());
            return top_card;
        }
        throw("The stack is empty!");
    }

    void Player::setCardsTaken(int cards)
    {
        if (cards > 52)
        {
            throw "error";
        }
        this->cards_taken = this->cards_taken + cards;
    }
    void Player::setDrawsNumberForPlayer(int num)
    {
        this->draws_number = this->draws_number + num;
    }
    string Player::getStatus()
    {
        return "draws: " + (std::to_string(this->draws_number) + " win rounds: " + std::to_string(this->points) + " cards that taken: " + std::to_string(this->cardesTaken()) + '\n');
    }

    
    void Player::takeAcard() // pop a card from the stack without get it (only put it in the game)
    {
        this->personal_stack.erase(personal_stack.begin());
    }

};
