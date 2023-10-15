#ifndef WAR_OF_CARDS
#define WAR_OF_CARDS
#include "./Gambling_Underground_Classes.h"
#include <vector>
#include <map>

//Will display how the current table looks like for the player's and dealer's decks
void display_table(vector<card> dealer, double dealer_total, vector<card> player, double player_total, int current_column);

//Checks to ensure the betting amount contains only numbers, loops till valid input
bool check_all_digits(string betting_amount);

//Adds a randomized card, or a custom one if test is true
void add_card(vector<card>& person, map<int, card>& deck, bool test);

//Calculate the player's and dealer's totals respectively each time a card is drawn
double calculate_total(vector<card> person);

//Checks the player's and dealer's decks to see if all cards are of the same suit
bool check_for_same_suit(vector<card> person);

//Checks the player's and dealer's decks to see if all cards in ascending order with no multipliers present
bool check_for_ascending_order(vector<card> person);

//Breaks a tie when the player and dealer have special hands, ties broken based off of suit of first card
char break_tie(vector<card> player, vector<card> dealer, long long& wallet, int betting_amount);

//Plays a round of war till player wins, loses, or ties with the dealer
char play_column(long long& wallet, int current_column);

//Checks for valid input in the play war of cards functions, like for asking for the rules, quitting to the main menu, or playing the game
string check_for_valid_input(string user_input);

//Asks the user if they want to see the rules, play, or quit, also shows them the general template of a War of Cards game
string play_war_of_cards(long long& wallet);

#endif