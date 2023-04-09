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

    Game::Game(Player &p_1, Player &p_2)
    {
        this->p1 = &p_1;
        this->p2 = &p_2;
        this->last_turn = "starting game";
        this->generateCardStack();
    }

    void Game::generateCardStack()
    {
        srand(time(NULL));                    // Seed the random number generator
        while (this->cards_stack.size() < 52) // generate cards stack
        {
            Number num = static_cast<Number>(rand() % 13 + 1);
            Sign sign = static_cast<Sign>(rand() % 4);
            Color color = (sign == Heart || sign == Diamond) ? Red : Black;

            // check if the card is already in the deck
            Card card(num, sign, color);
            auto it = std::find(cards_stack.begin(), cards_stack.end(), card);
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

    void Game::war()
    {
        // each player takes one card from his stack
        Card p1_card = p1->liftCard();
        Card p2_card = p2->liftCard();

        //"A" VS 2

        // "A" beat 2 but lose to all other cards so in this case p2 wins
        if (p1_card.getNumber() == 2 && p2_card.getNumber() == 1)
        {
            // point for the wining in this turn
            p2->setPoints(1);
            // updating the log
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + "." + p2->getName() + " win \n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p2->setCardsTaken(2 * num_of_draw + 4);
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
        // "A" beat 2 but lose to all other cards so in this case p1 wins
        if (p2_card.getNumber() == 2 && p1_card.getNumber() == 1) // A beat 2 but lose to all other cards
        {
            // point for the wining in this turn
            p1->setPoints(1);
            // updating the log
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + "." + p1->getName() + "win \n");
            this->setLog(this->last_turn);

            // check how many cards need to be add to the player (according to the number of draws)
            if (this->num_of_draw > 0)
            {
                p1->setCardsTaken(2 * num_of_draw + 4);
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

        // All other cards war (not A vs 2) - the bigger wins
        if (p1_card.getNumber() > p2_card.getNumber())
        {
            p1->setPoints(1);
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + "." + p1->getName() + " win \n");
            this->setLog(this->last_turn);
            if (this->num_of_draw > 0)
            {
                p1->setCardsTaken(2 * num_of_draw + 4);
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
            this->setLastTurn(p1->getName() + " played- " + p1_card.toString() + "\n" + p2->getName() + " played- " + p2_card.toString() + "." + p2->getName() + " win \n");
            this->setLog(this->last_turn);
            if (this->num_of_draw > 0)
            {
                p2->setCardsTaken(2 * num_of_draw + 4);
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
            // if the numbers of the cards are equal - it's a draw
            this->draw();
        }
    }

    void Game::draw()
    {
        // Checking breaking points
        //  no more cards to play
        if (p1->stacksize() == 0 || p2->stacksize() == 0)
        {
            // it's not the first draw in a row but there aren't more cards
            if (this->num_of_draw > 0)
            {
                // each player gets half of the cards
                p1->setCardsTaken(num_of_draw * 2 + 1);
                p2->setCardsTaken(num_of_draw * 2 + 1);
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
        // only one more card to play
        else if (p1->stacksize() == 1 && p2->stacksize() == 1)
        {
            p1->takeAcard();
            p2->takeAcard();
            // now there are no more cards and the rest like the condition above
            if (this->num_of_draw > 0)
            {
                // each player gets half of the cards
                p1->setCardsTaken(num_of_draw * 2 + 2);
                p2->setCardsTaken(num_of_draw * 2 + 2);
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
        for (size_t i = 0; i < size; i++)
        {
            if (p1->cardesTaken() + p2->cardesTaken() == 52) // we are in the end so get out
            {
                return;
            }
            if (i == 23) // we are in the turn before end
            {
                this->flag = true;
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
        cout << "draw rate : " + std::to_string(this->draws) <<endl;
        cout << p1->getName() + " status: " + p1->getStatus() + p2->getName() + " status: " + p2->getStatus();
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
