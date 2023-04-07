
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>
#include "card.hpp"

using namespace std;
namespace ariel {
    class Player {
        private:
            string name;
            //Stack personal_stack;
            std::vector<Card>& personal_stack;
            //vector<Card> personal_stack;
            string status;
            int cards_taken = 0;
            int draws_number = 0;
            int points = 0;
            int personal_stack_size = 0;
            
        public:
           Player();
           Player(std::vector<Card>& cards, std::string name, int points, int cardsTaken);
           Player(std::vector<Card>& cards) : personal_stack(cards) {}
            Player(string name); // Constructor
            void startingGame( vector<Card>& ps);
            void setStackSize(vector<Card>& size);
            void generateStack();

            void generateStack(vector<Card>& ps);
            vector<Card> getPersonalStack() ;
            void setCardsTaken(int cards);
            string getName();
            int getCardsTaken();
            int stacksize();
            int cardesTaken();
            int getPoints();
            void setPoints(int point);
            Card liftCard();
            string getStatus();
            void setDrawsNumber(int num);
            void setPersonalStack(vector<Card>* ps);
            Player& operator=(const Player& other) {
                if (this != &other) {
                    name = other.name;
                    points = other.points;
                    cards_taken = other.cards_taken;
                    personal_stack = other.personal_stack;
                }
                return *this;
            }

            // Destructor
            ~Player() {}


    };
}

#endif

