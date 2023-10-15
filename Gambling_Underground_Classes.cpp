#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include "./Gambling_Underground_Classes.h"
using namespace std;

//For printing the card values
void card::Print()
{
    //For setting the exact amount of decimals for a multiplier card
    if (suit == "M")
    {
        cout << fixed << setprecision(3) << value << suit;
    }
    else
    {
        cout << rank << suit;
    }
}