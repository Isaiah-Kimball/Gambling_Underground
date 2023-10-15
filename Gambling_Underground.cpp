#include <iostream>
#include <string>
#include <vector> 
#include "./Gambling_Underground_Classes.h"
#include "./Gambling_Underground_Functions.h"

using namespace std;

//The program is intended to eventually house 5 unique gambling-card-game inspired games for a user to play
//There is currently one game implemented right now, but more will be created in the future

int main()
{
    //Starting amount that you can bet
    long long wallet = 1000;
    //Controls when the program will end
    while (true)
    {
        //Ends program when the user has no more money left
        if (wallet == 0)
        {
            cout << "You have no more money, come back when you have more money." << endl;
            return 0;
        }
        //Will hold the user's input as a string to determine which option was selected
        string user_choice;
        print_starter_menu(wallet);
        cout << endl << "Please enter choice here: ";
        cin >> user_choice;
        //leaves the program for when the user wants to quit
        if (user_choice == "q" || user_choice == "Q" || user_choice == "quit" || user_choice == "Quit")
        {
            break;
        }
        //Will direct the user either to a specific game or ruleset
        user_direct(user_choice, wallet);
    }
    return 0;
}