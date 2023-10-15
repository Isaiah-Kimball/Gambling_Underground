#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "./Gambling_Underground_Classes.h"
#include "./war_of_cards.h" 
#include <map>
using namespace std;


//Makes a map for the card deck
map <int, card> create_deck()
{
    //Will hold a map for all values that the games can access
    map<int, card> deck;
    int value_of_card = 1;
    //Creates the clubs, spades, hearts, diamonds, then multipliers in order, Jokers created outside of their respective loop
    deck.emplace(0, card(1, "A", "C"));
    for (int key = 1; key < 10; key++)
    {
        value_of_card++;
        deck.emplace(key, card(value_of_card, to_string(key + 1), "C"));
    }
    deck.emplace(10, card(10, "J", "C"));
    deck.emplace(11, card(10, "Q", "C"));
    deck.emplace(12, card(10, "K", "C"));
    deck.emplace(13, card(1, "JO", "C"));
    //Creates spades
        deck.emplace(14, card(1, "A", "S"));
        value_of_card = 1;
    for (int key = 15; key < 24; key++)
    {
        value_of_card++;
        deck.emplace(key, card(value_of_card, to_string(value_of_card), "S"));
    }
    deck.emplace(24, card(10, "J", "S"));
    deck.emplace(25, card(10, "Q", "S"));
    deck.emplace(26, card(10, "K", "S"));
    deck.emplace(27, card(1, "JO", "S"));
    //Creates Hearts
        deck.emplace(28, card(1, "A", "H"));
        value_of_card = 1;
    for (int key = 29; key < 38; key++)
    {
        value_of_card++;
        deck.emplace(key, card(value_of_card, to_string(value_of_card), "H"));
    }
    deck.emplace(38, card(10, "J", "H"));
    deck.emplace(39, card(10, "Q", "H"));
    deck.emplace(40, card(10, "K", "H"));
    deck.emplace(41, card(1, "JO", "H"));
    //Creates the diamonds
        deck.emplace(42, card(1, "A", "D"));
        value_of_card = 1;
    for (int key = 43; key < 52; key++)
    {
        value_of_card++;
        deck.emplace(key, card(value_of_card, to_string(value_of_card), "D"));
    }
    deck.emplace(52, card(10, "J", "D"));
    deck.emplace(53, card(10, "Q", "D"));
    deck.emplace(54, card(10, "K", "D"));
    deck.emplace(55, card(1, "JO", "D"));
    //Will create the multipliers
    double multiplier = 0.1;
    for (int key = 56; key < 76; key++)
    {
        deck.emplace(key,card(multiplier, to_string(multiplier), "M"));
        multiplier+=0.1;
    }
    return deck;
}

//Prints the game options
void print_games()
{
    cout << "----------" << endl;
    cout << "1) War of Cards" << endl;
    cout << "----------" << endl;
}

//Will print the menu to pick which game the user wants to play
//Will always appear when the program begins or when the user exits a game
void print_starter_menu(long long wallet)
{
    //Make more prettier and complex later down the road    
    cout << "Welcome to the Underground Gambling Center!" << endl << endl;
    cout << "Here at the center we offer our own unique gambling games that you won't find at any normal casinos." << endl;
    cout << "Here are the following available games right now:" << endl;
    print_games();
    cout << "Enter the number corresponding to the game to play it." << endl; 
    cout << "Enter the number and then the letter 'r' next to it see the rules and betting information for the game (Ex: 1r)." << endl;
    cout << "To exit the center, input 'q' or 'quit'." << endl;
    cout << "You currently have: $" << wallet << endl;
}

//Prints the betting returns for War of Cards
void war_of_cards_betting_info()
{
    cout << endl << "Player can only bet money that they have" << endl;
    cout << "Rates for first column:" << endl;
    cout << "Player number higher than dealer: [2:1]" << endl;
    cout << "Player number is exactly 30 and does not tie with dealer: [4:1]" << endl;
    cout << "Player only drew multiplier cards: [5:1]" << endl;
    cout << "Player drew 5 cards of the same suit (no multipliers) and won the column: [6:1]" << endl;
    cout << "Player drew 5 cards in ascending order (EX: A,2,3,4,5) and won the column: [8:1]" << endl;
    cout << "Player drew 5 cards in ascending order AND of the same suit, and won the column: [10:1]" << endl;
    cout << endl << "Return rates are doubled for the second column, and tripled for the third column." << endl;
    cout << "In the event that the dealer and player tie and both have a special hand (same suit, ascending order, or both)" << endl;
    cout << "The tie will be broken based off of who has the highest ranked suit." << endl;
    cout << "Suit rankings are as such: Clubs, Spades, Hearts, Diamonds. Where Clubs are the lowest and Diamonds the highest." << endl;
    cout << "A tie is only possible if no special hands are present, and the user and player have the exact same total." << endl;
}

//Prints the ruleset of war of cards
void print_war_of_cards_ruleset()
{
    cout << "War of cards will pit the player vs the dealer" << endl;
    cout << "War of cards will utilize a standard 52 card deck of clubs, spades, hearts, and diamonds." << endl;
    cout << "But also 4 jokers, and a unique 20 card multiplier deck (multiplies all numbers currently drawn and also with other multipliers)." << endl;
    cout << "The multiplier deck contains the following values: 2.0, 1.9, 1.8, 1.7, 1.6, ... down to 0.1" << endl;
    cout << "The player will have 3 total columns for a round, in which they can play on" << endl;
    cout << "Each will first have the user start with 2 cards and draw up to 3 more cards while trying to get the total number as close to 30." << endl;
    cout << "The player does not have to draw cards at any point, if the user goes over 30, they bust and automatically lose the entire round." << endl;
    cout << "The player will start with the first column in which the bet rates are normal (see betting list at the bottom)." << endl; 
    cout << "If they win, the user will be able to do war in the second column where the betting is doubled." << endl; 
    cout << "If the they win the second column, they can go again and play in the third column in which the bettings are tripled." << endl;
    cout << "Once the player has either stopped drawing at a number, the dealer will start to draw." << endl;
    cout << "The dealer will stop till they either beat the player, bust, or do not beat the player with a total of 5 cards." << endl;
    cout << "Player total will be represented with a decimal due to multipliers." << endl;
    cout << "Numbered cards count the same as their number, jack, queen, and king count as 10, aces and jokers is always 1." << endl;
    //cout << "A joker will be a ten if it gurantees that you will bust when it is a 10, and will be a one if you will not bust";
    war_of_cards_betting_info();
}

//Will allow the user to access the finished card games and their specific rule sets
void user_direct(string& user_choice, long long& wallet)
{
    //Will keep looping till the user wants to quit or return to the main menu
    while (true)
    {
        //Play War of Cards
        if (user_choice == "1")
        {
            user_choice = play_war_of_cards(wallet);
        }
        //See the rules for War of Cards
        else if (user_choice == "1r")
        {
            print_war_of_cards_ruleset();
        }
        //Quit the program
        else if (user_choice == "q")
        {
            return;
        }
        //Tells the user that what they inputted was invalid
        else
        {
            cout << "Invalid input, please try again" << endl;
        }
        //Re-checks in the event that a game is played and the user quit out of it, it will return them to the main menu
        if (user_choice == "q")
        {
            return;
        }
        //Will print if an invalid input occurred, or the user wanted to print a ruleset such that they will still be in the
        //User directory
        cout << "Please enter which option you would like to select: ";
        cin >> user_choice;
        cout << endl;
        if (user_choice == "quit" || user_choice == "q")
        {
            user_choice = "q";
            return;
        }
    }
}