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
            std::vector<Card> personal_stack;
            string status;
            int cards_taken = 0;
            int draws_number = 0;
            int points = 0;
            int personal_stack_size = 0;
            
        public:
            Player();
            Player(std::vector<Card>& ps) : personal_stack(ps) {}
            Player(string name);
            void setStackSize(vector<Card>& size);
            void generateStack();
            void generateStack(vector<Card>& ps);
            vector<Card> getPersonalStack();
            void setCardsTaken(int cards);
            string getName();
            int stacksize();
            int cardesTaken();
            int getPoints();
            void setPoints(int point);
            Card liftCard();
            string getStatus();
            void setDrawsNumber(int num);
            void setPersonalStack(vector<Card>* ps);

    };
}

#endif
