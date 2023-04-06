#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "player.hpp"
using namespace std;

namespace ariel
{
    Game::Game(Player p1, Player p2)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->last_turn = "startig game";
        this->p1.generateStack();
        this->p2.generateStack();

        
        
    }
    void Game::war(){
        Card p1_card = p1.liftCard();
        Card p2_card = p2.liftCard();
        

        if (p1_card.getNumber() > p2_card.getNumber())
        {
            p1.setPoints(1);
            this->setLastTurn(p1.get_name() + "played-"+ p1_card.toString() +"\n"+ p2.get_name() + "played-"+ p2_card.toString() +"."+ p1.get_name()+"win");
            p2.setCardsTaken(2);
        }
        else if(p2_card.getNumber() > p1_card.getNumber()){
            p2.setPoints(1);
            this->setLastTurn(p1.get_name() + "played-"+ p1_card.toString() +"\n"+ p2.get_name() + "played-"+ p2_card.toString() +"."+ p2.get_name()+"win");
            p1.setCardsTaken(2);
        }else{
            this->draw();
        }
    }
    void Game::draw(){
        


    }
    void Game::generateCardStack(){
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
    }
    void Game::printLastTurn()
    {
        cout << this->last_turn;
    }
    void Game::playAll()
    {
        int stack_a = this->p1.stacksize();
        int stack_b = this->p2.stacksize();
        int size = stack_a;
        if(stack_b < stack_a){
            size = stack_b;
        }
        for (size_t i = 0; i < size; i++)
        {
            playTurn();
        }
        
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
        cout << p1.getStatus() + p2.getStatus();
    }
    
    void Game::playTurn(){
         if ((p1.stacksize() == 0) || (p2.stacksize() == 0)) {
            throw std::runtime_error("The game cannot be played as one of the players has an empty stack.");
            
        }
        this->war();
    }

    string Game::getLastTurn(){
        return this->last_turn;
    }
    void Game::setLastTurn(string last_turn){
        this->last_turn = last_turn;
    }
    Player Game::getWinner(){
        return this->winner;
    }
    void Game::setWinner(Player name){
        this->winner = name;
    }
     string Game::getLog(){
        return this->log;
    }
    void Game::setLog(string log){
        this->log = this->log + log;
    }



}
