#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "player.hpp"
using namespace std;

namespace ariel
{
    // Constructor that initializes p1 and p2 with the addresses of the two Player objects passed as arguments
    // and generate a stack to each of the players
    // By using references, the constructor can access the original Player objects passed as arguments rather than creating copies.
    Game::Game(Player &p_1, Player &p_2)
    {
        this->p1 = &p_1;
        this->p2 = &p_2;
        this->generateCardStack();
    }

    // This function generate a stack randomly according to the enoms that defined in the "card" class
    // and divide the stack to eack player
    void Game::generateCardStack()
    {
        srand(time(NULL));                    // Seed the random number generator
        while (this->cards_stack.size() < 52) // generate cards stack
        {
            Number num = static_cast<Number>(rand() % 13 + 2); // generate a number between 2-14
            Sign sign = static_cast<Sign>(rand() % 4);
            Color color = (sign == Heart || sign == Diamond) ? Red : Black;
            // generate the spesific card
            Card card(num, sign, color);
            // check if the card is already in the deck
            auto it = std::find(cards_stack.begin(), cards_stack.end(), card);
            // if such card not exist, push it to the end of the vector
            if (it == cards_stack.end())
            {
                cards_stack.push_back(card);
            }
        }
        // divide the stack to two different stacks and assign them to the each player
        vector<Card> first_half(cards_stack.begin(), cards_stack.begin() + 26);
        vector<Card> second_half(cards_stack.begin() + 26, cards_stack.end());
        this->p1->setPersonalStack(&first_half);
        this->p2->setPersonalStack(&second_half);
    }

    // This function represent the actuall game - the war between the cards of the players
    void Game::war()
    {
        // counting the number of rounds for statistics
        this->rounds = this->rounds + 1;
        // each player takes one card from his stack
        Card p1_card = p1->liftCard();
        Card p2_card = p2->liftCard();

        //                           *** Ace VS 2 ***

        // 2 beat Ace but lose to all other cards so in this case p2 wins
        if (p1_card.getNumber() == 14 && p2_card.getNumber() == 2)
        {
            // adding a point for the wining in this turn - The points represents the number of wining rounds
            p2->setPoints(1);
            // updating the log
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + ".\n*** " + p2->getName() + " win ***\n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p2->setCardsTaken(6 + (num_of_draw - 1) * 4); // for 1 draw the player needs to take 6 cards, for two in a raw it's 10 and goes on...
                p2->setDrawsNumberForPlayer(1);
                this->setDrawsGame(num_of_draw);
                this->num_of_draw = 0;
            }
            else
            {
                // regular turn (p2 takes his card and p1's card)
                p2->setCardsTaken(2);
            }
            return;
        }
        // 2 beat Ace but lose to all other cards so in this case p1 wins
        if (p2_card.getNumber() == 14 && p1_card.getNumber() == 2)
        {
            // adding a point for the wining in this turn - The points represents the number of wining rounds
            p1->setPoints(1);
            // updating the log
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + ".\n*** " + p1->getName() + " win ***\n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p1->setCardsTaken(6 + (num_of_draw - 1) * 4);
                p1->setDrawsNumberForPlayer(1);
                this->setDrawsGame(num_of_draw);
                this->num_of_draw = 0;
            }
            else
            {
                // regular turn (p1 takes his card and p2's card)
                p1->setCardsTaken(2);
            }
            return;
        }

        //                    ***  All other cards wars (not Ace vs 2) - the bigger wins ***
        if (p1_card.getNumber() > p2_card.getNumber())
        {
            p1->setPoints(1);
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + ".\n*** " + p1->getName() + " win ***\n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p1->setCardsTaken(6 + (num_of_draw - 1) * 4);
                p1->setDrawsNumberForPlayer(1);
                this->setDrawsGame(num_of_draw);
                this->num_of_draw = 0;
            }
            else
            {
                // regular turn (p2 takes his card and p1's card)

                p1->setCardsTaken(2);
            }
        }
        else if (p2_card.getNumber() > p1_card.getNumber())
        {
            p2->setPoints(1);
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + ".\n*** " + p2->getName() + " win ***\n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p2->setCardsTaken(6 + (num_of_draw - 1) * 4);
                p2->setDrawsNumberForPlayer(1);
                this->setDrawsGame(num_of_draw);
                this->num_of_draw = 0;
            }
            else
            {
                // regular turn (p1 takes his card and p2's card)
                p2->setCardsTaken(2);
            }
        }
        else
        {
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + " \n");
            this->setLog(this->last_turn);

            // if the numbers of the cards are equal - it's a draw
            this->draw();
        }
    }

    void Game::draw()
    {
        //                              *** Checking breaking points ***

        //  no more cards to play
        if (p1->stacksize() == 0 || p2->stacksize() == 0)
        {
            // it's not the first draw in a row but there aren't more cards
            if (this->num_of_draw > 0)
            {
                // each player gets half of the cards
                p1->setCardsTaken(num_of_draw * 2 - 1);
                p2->setCardsTaken(num_of_draw * 2 - 1);
                this->setDrawsGame(num_of_draw);
                this->num_of_draw = 0;
            }
            else
            {
                // it's the first draw, there no more cards so taking the equal card
                p1->setCardsTaken(1);
                p2->setCardsTaken(1);
            }
        }
        // only one more card left to play
        else if (p1->stacksize() == 1 && p2->stacksize() == 1)
        {
            p1->takeAcard();
            p2->takeAcard();
            // now there are no more cards and the rest like the condition above
            if (this->num_of_draw > 0)
            {
                // each player gets half of the cards
                p1->setCardsTaken(num_of_draw * 2);
                p2->setCardsTaken(num_of_draw * 2);
                this->num_of_draw = 0;
            }
            else
            {
                p1->setCardsTaken(2);
                p2->setCardsTaken(2);
            }
        }
        p1->takeAcard();
        p2->takeAcard();
        this->setLastTurn("It's a draw! each player put one card upside down, let's continue---> \n");
        this->setLog(this->last_turn);
        this->num_of_draw += 1;
        this->war();
    }

    void Game::setDrawsGame(int num)
    {
        this->draws = this->draws + num;
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
        if (stack_b < stack_a)
        {
            size = stack_b;
        }
        // play until all the cards in the stack ends
        for (size_t i = 0; i < size; i++)
        {
            if (p1->cardesTaken() + p2->cardesTaken() == 52) // we are in the end so get out
            {
                return;
            }
            if (i == 23) // we are in the turn before end
            {
                //this->flag = true;
                this->war();
            }
            else
            {
                playTurn();
            }
        }
        return;
    }
    // This function prints the winner name of the game
    void Game::printWiner()
    {

        if (p1->cardesTaken() > p2->cardesTaken())
        {
            cout << "The winner is " + p1->getName() << endl;
        }
        else
        {
            cout << "The winner is " + p2->getName() << endl;
        }
    }

    void Game::printLog()
    {
        cout << this->getLog();
    }

    void Game::printStats()
    {
        float draw_rate = static_cast<float>(this->draws) / this->rounds;
        cout << "Number of rounds: " + std::to_string(this->rounds) << endl;
        cout << "draw rate : " + std::to_string(draw_rate) << endl;
        cout << p1->getName() + " status: " + p1->getStatus() + p2->getName() + " status: " + p2->getStatus();
        this->printWiner();
        this->p1->getPersonalStack().clear();
        this->p2->getPersonalStack().clear();
    }

    void Game::playTurn()
    {

        if ((p1->stacksize() == 0) || (p2->stacksize() == 0))
        {
            throw std::runtime_error("The game cannot be played as one of the players has an empty stack.");
        }
        if (p1 == p2)
        {
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

    Player &Game::getWinner()
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
