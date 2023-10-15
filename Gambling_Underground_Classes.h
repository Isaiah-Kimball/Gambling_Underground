#ifndef GAMBLING_UNDERGROUND_CLASSES
#define GAMBLING_UNDERGROUND_CLASSES
#include <string>

using namespace std;

class card
{
    public:
        //Will hold the value of the card object from 1-10
        double value;
        //Holds the actual rank from 2-10,J,Q,K,A,JO, and multipliers
        string rank;
        //Will be used to differ the string suits
        string suit;
        //Constructors
        //Default
        card(): value(0), rank("Undefined"), suit("Undefined") {};
        //Specified parameters
        card(double new_value, string new_rank, string new_suit): value(new_value), rank(new_rank), suit(new_suit) {};
        //Print function for formatting how a card is printed
        void Print();
};

#endif