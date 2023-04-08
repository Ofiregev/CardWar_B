#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "player.hpp"
using namespace std;

namespace ariel
{

    Game::Game(Player &p_1, Player& p_2) 
    {
        this->p1 = &p_1;
        this->p2 = &p_2;
        this->last_turn = "starting game";
        this->generateCardStack();

        cout << "after generating2 : " + std::to_string(p_1.stacksize()) << endl;

    }

    void Game::generateCardStack()
    {
            while (this->cards_stack.size() < 52) {
            Number num = static_cast<Number>(rand() % 13 + 1);
            Sign sign = static_cast<Sign>(rand() % 4);
            Color color = (sign == Heart || sign == Diamond) ? Red : Black;
            
            // check if the card is already in the deck
            Card card(num, sign, color);
            auto it = std::find(cards_stack.begin(), cards_stack.end(), card);
            if (it == cards_stack.end()) {
                cards_stack.push_back(card);
            }
        }
    vector<Card> first_half(cards_stack.begin(), cards_stack.begin() + 26);
    vector<Card> second_half(cards_stack.begin() + 26, cards_stack.end());
    this->p1->setPersonalStack(&first_half);
    this->p2->setPersonalStack(&second_half);
    }

    void Game::war()
    {
        Card p1_card = p1->liftCard();
        Card p2_card = p2->liftCard();
        

        if (p1_card.getNumber() > p2_card.getNumber())
        {
            p1->setPoints(1);
            this->setLastTurn(p1->getName() + "played-"+ p1_card.toString() +"\n"+ p2->getName() + "played-"+ p2_card.toString() +"."+ p1->getName()+"win");
            p2->setCardsTaken(2);
        }
        else if(p2_card.getNumber() > p1_card.getNumber()){
            p2->setPoints(1);
            this->setLastTurn(p1->getName() + "played-"+ p1_card.toString() +"\n"+ p2->getName() + "played-"+ p2_card.toString() +"."+ p2->getName()+"win");
            p1->setCardsTaken(2);
        }else{
            this->draw();
        }
    }

    void Game::draw()
    {
    }
    
    void Game::printLastTurn()
    {
        cout << this->last_turn;
    }

    void Game::playAll()
    {
        int stack_a = p1->stacksize();
        int stack_b = p2->stacksize();
        int size = stack_a;
        if(stack_b < stack_a){
            size = stack_b;
        }
        for (size_t i = 0; i < size; i++)
        {
            playTurn();
        }
        return;
    }

    void Game::printWiner()
    {
        cout << "The winner is ";
    }

    void Game::printLog()
    {
        cout << this->getLog();
    }

    void Game::printStats()
    {
        cout << p1->getStatus() + p2->getStatus();
    }
    
    void Game::playTurn()
    {
        if ((p1->stacksize() == 0) || (p2->stacksize() == 0)) {
            throw std::runtime_error("The game cannot be played as one of the players has an empty stack.");
            
        }
        if (p1 == p2) {
            throw std::runtime_error("The game cannot be played with one player");
            
        }
        this->war();
        return;
    }

    string Game::getLastTurn()
    {
        return this->last_turn;
    }

    void Game::setLastTurn(string last_turn)
    {
        this->last_turn = last_turn;
    }

    Player& Game::getWinner()
    {
    return winner;
    }

    void Game::setWinner(Player name)
    {
        this->winner = name;
    }

     string Game::getLog()
    {
        return this->log;
    }

    void Game::setLog(string log)
    {
        this->log = this->log + log;
    }
}


