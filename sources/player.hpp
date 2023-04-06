
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include "stack.hpp"

using namespace std;
namespace ariel {
    class Player {
        private:
            string name;
            Stack personal_stack;
            string status;
            int cards_taken = 0;
            int draws_number = 0;
            int points = 0;
            
            
        public:
            Player();

            Player(string name); // Constructor
            void setStackSize(int size);
            Stack getPersonalStack();
            void setCardsTaken(int cards);
            string get_name();
            int stacksize();
            int cardesTaken();
            int getPoints();
            void setPoints(int point);
            Card liftCard();
            string getStatus();
            void setDrawsNumber(int num);
            

    };
}

#endif

