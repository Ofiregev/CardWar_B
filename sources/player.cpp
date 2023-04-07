#include "player.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "card.hpp"

using namespace std;

namespace ariel
{


Player::Player(string name) : name(name), points(0), cards_taken(0), personal_stack(*(new std::vector<Card>())) {}

ariel::Player::Player(std::vector<ariel::Card>& cards, std::string name, int points, int cards_taken)
    : name(name), points(points), cards_taken(cards_taken), personal_stack(cards)
{
    this->name = name;
    this->points = points;
    this->cards_taken = cards_taken;

    for (Card& card : cards)
    {
        this->personal_stack.push_back(card);
    }
}


    // void Player::startingGame(vector <Card> &ps){
    //     cout << "before generating: " + std::to_string(ps.size());
    //     this->personal_stack = ps;
    //     this->generateStack(this->personal_stack);
    //     cout << " after generating:  "+ std::to_string(personal_stack.size());
    // }
    
// void Player::generateStack() {
//     while (personal_stack.size() < 26) {
//         Number num = static_cast<Number>(rand() % 13 + 1);
//         Sign sign = static_cast<Sign>(rand() % 4);
//         Color color = (sign == Heart || sign == Diamond) ? Red : Black;
        
//         // check if the card is already in the deck
//         Card card(num, sign, color);
//         auto it = std::find(personal_stack.begin(), personal_stack.end(), card);
        
//         if (it == personal_stack.end()) {
//             personal_stack.push_back(card);
//         }
//     }
//     personal_stack_size = personal_stack.size();
// }



    void Player::generateStack(vector<Card> &ps)
{
    while (ps.size() < 26) {
        Number num = static_cast<Number>(rand() % 13 + 1);
        Sign sign = static_cast<Sign>(rand() % 4);
        Color color = (sign == Heart || sign == Diamond) ? Red : Black;
        
        // check if the card is already in the deck
        Card card(num,sign, color);
        auto it = std::find(ps.begin(), ps.end(), card);
        
        if (it == ps.end()) {
            ps.push_back(card);
        }
    }
}

    
    
    void Player::setStackSize(vector<Card>& size) {
    personal_stack = size;
    personal_stack_size = personal_stack.size(); // update the size variable
    cout << "pss: " + std::to_string(personal_stack_size) << endl;
}

void Player::setPersonalStack(vector<Card>* stack) {
    // Check that the input vector has exactly 26 cards
    if (stack->size() != 26) {
        throw std::invalid_argument("Input vector size is not 26");
    }
    this->personal_stack = *stack;
    cout << "set ps: " + std::to_string(this->stacksize()) << endl;
}




   int Player::stacksize()
{
    //cout << "original generated stack loc (from ss fun):" << &personal_stack << endl;

    int size = personal_stack.size();
    //cout << "personal_stack size: " << size << endl;
    return this->getPersonalStack().size();
}

vector<Card> Player::getPersonalStack() {
    return personal_stack;
}
    // Player& Player::operator=(const Player& other) {
    //     if (this != &other) {
    //         name = other.name;
    //         personal_stack = other.personal_stack;
    //     }
    //     return *this;
    // }
int Player::getCardsTaken(){
    return this->cards_taken;
}


























    int Player::cardesTaken()
    {
        return this->cards_taken;
    }
    string Player::getName(){
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
