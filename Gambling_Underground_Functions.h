#ifndef GAMBLING_UNDERGROUND_FUNCTIONS
#define GAMBLING_UNDERGROUND_FUNCTIONS
#include <string>
#include <map>
#include "./Gambling_Underground_Classes.h" 

using namespace std;

//Will make a map that will be used to represent the 52 standard card deck with 4 jokers and 20 multiplier cards
//The key is simply an integer, and the value is the specific card with a value, rank, and suit
//Intended use will be that a map will be created in each game's play function which will have cards deleted from the map
//Created within the scope of the function to signify the card was already drawn
//Each iteration of the specific game's play function will recall this create function such that a fresh deck to refer to will be
//Recreated
map<int, card> create_deck();

//Simply prints all of the gambling game options (currently only 1, but planning to have 5 in the future)
void print_games();

//Will print the menu for when the user starts the program or exits from a game
void print_starter_menu(long long wallet);

//Outputs the betting returns and specific hands required to achieve them
void war_of_cards_betting_info();

//Outputs the rule set for how to play War of Cards
void print_war_of_cards_ruleset();

//Will direct the player to a specified game, a ruleset, or say that the input is invalid
//Will also directly change user_choice as it's passed by reference
void user_direct(string& user_choice, long long& wallet);

#endif