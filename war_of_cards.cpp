#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
#include "./Gambling_Underground_Classes.h" 
#include "./Gambling_Underground_Functions.h"

using namespace std;

//Will be called each time a card is drawn to display the table containing the player's and dealer's cards and totals
void display_table(vector<card> dealer, double dealer_total, vector<card> player, double player_total, int current_column)
{
    cout << endl << "Column: " << current_column << endl;
    cout << "Dealer Total: " << dealer_total << endl;
    //Prints dealer's cards
    cout << "[";
    for (long unsigned int index = 0; index < dealer.size(); index++)
    {
        dealer.at(index).Print();
        cout << ", ";
    }
    cout << "]" << endl << endl;
    //Prints the player's cards
    cout << "[";
    for (long unsigned int index = 0; index < player.size(); index++)
    {
        player.at(index).Print();
        cout << ", ";
    }
    cout << "]" << endl;
    cout << "Player Total: " << player_total << endl << endl;
}

//Checks to see if a string contains only digits (used for input validation)
bool check_all_digits(string betting_amount)
{
    for (long unsigned index = 0; index < size(betting_amount); index++)
    {
        //Will convert the currently analyzed character to ASCII number
        int character = betting_amount.at(index);
        if (character < 48 || character > 57)
        {
            return false;
        }
    }
    return true;
}

//Adds a new randomized card not already drawn from the deck, adds it to the specified deck, and removes it from the drawable deck
//If test is true, then it allows the user to specify a card to be added and properly alerts if a card has already been added
void add_card(vector<card>& person, map<int, card>& deck, bool test)
{
    //Loops till a card that is still in the deck can be served
    if (test)
    {
        while (true)
        {
            //Asks which key the user wants to manually input
            int key = 0;
            cout << "Please enter the key of the deck map you would like to put in: ";
            cin >> key;
            //Checks the card has not already been in play
            if (deck.count(key) == 1)
            {
                card card_to_add = deck.at(key);
                person.push_back(card_to_add);
                deck.erase(key);
                return;
            }
            //Executes when the key does not exist
            else
            {
                cout << "Card has already been used or key is out of range or simply invalid, please input a different key." << endl;
                continue;
            } 
        }
        
    }
    //Same thing but when playing the game normally
    else
    {
        while (true)
        {
            //Ensure that each game will be truely random
            srand(time(0));
            int key = rand() % 76;
            //Checks to ensure that the card is still in the deck
            if (deck.count(key) == 1)
            {
                card card_to_add = deck.at(key);
                person.push_back(card_to_add);
                deck.erase(key);
                return;
            }
            //Continues till a card not in play will be drawn
            else
            {
                continue;
            }
        }        
    }
}

//Calculates either the dealer or player's total
double calculate_total(vector<card> person)
{
    double person_total = 0.0;
    double person_multipliers = 1;
    for (long unsigned index = 0; index < person.size(); index++)
        {
            card current_card = person.at(index);
            //Check to see if it's a normal suit, or if it's a multiplier
            //Multipliers will be applied when all normal values are added
            if (current_card.suit == "M")
            {
                person_multipliers *= current_card.value;
            }
            else
            {
                person_total += current_card.value;
            }
        }
    person_total *= person_multipliers;
    return person_total;   
}

//Checks if either the player or dealer has a deck of 5 cards that are of the same suit
bool check_for_same_suit(vector<card> person)
{
    //Ensures deck is 5
    if (person.size() < 5)
    {
        return false;
    }
    //If any card has a different suit, then the function outputs false
    string suit = (person.at(0)).suit;
    for (long unsigned index = 1; index < person.size(); index++)
    {
        string current_card_suit = (person.at(index)).suit;
        if (current_card_suit != suit)
        {
            return false;
        }
    }
    return true;
}

//Checks if either the player or the dealer has 5 cards that are in numeric order, multipliers not allowed
bool check_for_ascending_order(vector<card> person)
{
    //Ensure the size is 5
    if (person.size() < 5)
    {
        return false;
    }
    double previous_value = (person.at(0)).value;
    if (person.at(0).suit == "M")
    {
        return false;
    }
    //If any value is less than or equal, or is a multiplier, will output false, otherwise will be true
    for (long unsigned index = 1; index < person.size(); index++)
    {
        double current_value = (person.at(index)).value;
        //Signifies a multiplier is present and thus acending order is not present either
        if (person.at(index).suit == "M")
        {
            return false;
        }
        if (current_value <= previous_value)
        {
            return false;
        }
        //Reassigns previous value to current value as the next iteration will have current value be the next value and thus a 
        //Reassignment is needed
        previous_value = current_value;
    }
    return true;
}

//Called when the player and dealer both have the same special hands to break the tie
//Breaks the tie based on which person has the higher ranking suit of order Clubs, Spades, Hearts, then Diamonds
char break_tie(vector<card> player, vector<card> dealer, long long& wallet, int betting_amount)
{
    //Holds the respective card
    card first_player_card = player.at(0);
    card first_dealer_card = dealer.at(0);
    if (first_dealer_card.value == first_player_card.value)
    {
        map<string, int> associate_values;
        associate_values.emplace("C", 1);
        associate_values.emplace("S", 2);
        associate_values.emplace("H", 3);
        associate_values.emplace("D", 4);
        int player_value = associate_values.at(first_player_card.suit);
        int dealer_value = associate_values.at(first_dealer_card.suit);
        if (dealer_value > player_value)
        {
            wallet -= betting_amount;
            return 'l';
        }
    }
    return 'w';
}

//Will play a round of war till the user wins or loses
char play_column(long long& wallet, int current_column)
{
    //Will hold the cards that are left in the deck
    map <int, card> deck = create_deck();
    //Holds the respective person's cards
    vector<card> player;
    vector<card> dealer;
    //Can be turned to true to manually add cards, but will be false by default to play the game normall
    bool test = false;
    //Holds the player's and dealer's totals respectively
    double dealer_total = 0.0;
    double player_total = 0.0;
    //Holds the player's betting amount
    string betting_amount_as_string;
    //Will loop till the player wins, loses, or ties
    add_card(player, deck, test);
    add_card(player, deck, test);
    player_total = calculate_total(player);
    display_table(dealer, dealer_total, player, player_total, current_column);
    //Will loop till the user inputs a valid number to bet
    while (true)
    {
        cout << "Please input your betting amount or type q to quit: ";
        cin >> betting_amount_as_string;
        cout << endl;
        if (betting_amount_as_string == "q")
        {
            return 'q';
        }
        //Ensures only digits were inputted
        if(!check_all_digits(betting_amount_as_string))
        {
            cout << "Invalid input, please input a positive non-zero value that does not exceed your wallet." << endl;
        }
        else if (stoll(betting_amount_as_string) <= 0 || stoll(betting_amount_as_string) > wallet)
        {
            cout << "Invalid input, please input a positive non-zero value that does not exceed your wallet." << endl;
        }
        else
        {
            break;
        }

    }
    //Converts string to actual integer
    long long betting_amount = stoll(betting_amount_as_string);
    //Holds how many cards have been drawn
    int cards_drawn = 2;
    //Loops till 5 cards are drawn, the user stands, or the user busts
    while (cards_drawn < 6)
    {
        //Will check the user's total each time they draw a new card
        player_total = calculate_total(player);
        //Automatically stops the player as they have reached the highest possible value, if they accidentally draw again, they would lose.
        //Sort of a way to protect them from themselves
        if (player_total == 30)
        {
            display_table(dealer, dealer_total, player, player_total, current_column);
            break;
        }
        //Work around for intial display table call to induce preferred formatting
        if (cards_drawn != 2)
        {
            display_table(dealer, dealer_total, player, player_total, current_column);
        }
        //Means that the user has busted
        if (player_total > 30.0)
        {
            wallet -= betting_amount;
            return 'l';
        }
        //Max cards have been drawn
        if (cards_drawn == 5)
        {
            break;
        }

        //Holds the user's choice
        cout << "Type s to stand, d to draw, or q to quit: ";
        string user_input;
        cin >> user_input;
        cout << endl;
        //Loops till valid input is given
        while (user_input != "s" && user_input != "d" && user_input != "q")
        {
            cout << "Invalid input, please input only s, d, or q to either stand, draw, or quit respectively: ";
            cin >> user_input; 
        }
        //Means the user doesn't want to draw anymore and will have the dealer start drawing next
        if (user_input == "s")
        {
            break;
        }
        //Draws a card
        else if (user_input == "d")
        {
            add_card(player, deck, test);
            cards_drawn++;
        }
        //Quits the game and the loser will automatically lose their betted money
        else if (user_input == "q")
        {
            wallet -= betting_amount;
            return 'q';
        } 

    }
    cards_drawn = 2;
    add_card(dealer, deck, test);
    add_card(dealer, deck, test);
    //Will draw till the dealer busts, wins, or ties with the player
    while (cards_drawn < 6)
    {
        //Will check the dealer's total each time they draw a new card
        dealer_total = calculate_total(dealer);
        display_table(dealer, dealer_total, player, player_total, current_column);
        //Highest total is reached, dealer will no longer need to draw
        if (dealer_total == 30)
        {
            break;
        }
        //Means the dealer has busted
        if (dealer_total > 30.0)
        {
            wallet += betting_amount * current_column;
            return 'w';
        }
        //Means the dealer has won and the player loses betted amount
        else if (dealer_total > player_total)
        {
            //If the statement that's in the parenthesis is true, then that means the player has all multipliers and will most likely win
            if (!(player_total == 0 and player.size() == 5))
            {
                wallet -= betting_amount;
                return 'l';  
            }
        }
        //Adds dealer's cards
        else
        {
            if (cards_drawn == 5)
            {
                break;
            }
            add_card(dealer, deck, test);
            cards_drawn++;
        }
    }
    //Will be true for the respective person if they contain only multiplier cards
    bool player_all_multiples;
    bool dealer_all_multiples;
    if (player_total == 0 && player.size() == 5)
    {
        player_all_multiples = true;
    }
    if (dealer_total == 0 && dealer.size() == 5)
    {
        dealer_all_multiples = true;
    }
    //If player_total or dealer_total equals zero, then that means they only drew multiplier cards
    if (player_all_multiples && !dealer_all_multiples)
    {
        wallet += (betting_amount * 4) * current_column;
        return 'w';
    }
    else if (!player_all_multiples && dealer_all_multiples)
    {
        wallet -= betting_amount;
        return 'l';
    }
    else if (player_all_multiples && dealer_all_multiples)
    {
        return 't';
    }
    //Determines if the player won, tied, or lost (can only lose from tie breakers)
    //Makes check to see if all cards are of the same suit (no multipliers present)
    bool player_same_suit = check_for_same_suit(player);
    bool dealer_same_suit = check_for_same_suit(dealer);
    //Makes check to see if all cards are in ascending order (no multipliers present)
    bool player_ascending_order = check_for_ascending_order(player);
    bool dealer_ascending_order = check_for_ascending_order(player);
    //Best possible outcome for player, same suit and ascending order
    if (player_same_suit && player_ascending_order)
    {
        //Checks to see if the dealer has the same boolean values, if it does, then the tie will be broken by first checking
        //The first value of the ascending order, if they are the same, then the tie is broken by the highest precedence card type
        //Clubs, Spades, Hearts, Diamonds
        if (dealer_ascending_order && dealer_same_suit && player_total == dealer_total)
        {
            if (break_tie(player, dealer, wallet, betting_amount) == 'l')
            {
                return 'l';
            }
        }
        //Adds specified betting outcome to wallet
        wallet += (betting_amount * 9) * current_column;
        return 'w';
    }
    //Player contains
    else if (player_same_suit)
    {
        //Same check as coded before but just for when it's only same suits for the player's deck
        if (dealer_same_suit && player_total == dealer_total)
        {
            if (break_tie(player, dealer, wallet, betting_amount) == 'l')
            {
                return 'l';
            }
        }
        else
        {
            wallet += (betting_amount * 5) * current_column;
            return 'w';    
        }
    }
    else if (player_ascending_order)
    {
        //Same thing and style but only when ascending order is present
        if (dealer_ascending_order && player_total == dealer_total)
        {
            if (break_tie(player, dealer, wallet, betting_amount) == 'l')
            {
                return 'l';
            }
        }
        else
        {
            wallet += (betting_amount * 7) * current_column;
            return 'w';
        }
    }
    //Checks if the player got exactly thirty and hands the respective betting ratio
    if (player_total == 30.0 && dealer_total < 30)
    {
        wallet += (betting_amount * 3) * current_column;
        return 'w';
    }
    //Means that the player and dealer genuiely tied and no tie breakers of the sort were needed
    if (player_total == dealer_total)
    {
        return 't';
    }
    //Happens when no special hands were made, and the player simply won for having a higher number than the dealer
    wallet += betting_amount * current_column;
    return 'w';
}

//Loops respective section till user inputs something valid
string check_for_valid_input(string user_input)
{
    //Options are to see the rules, play, or quit to main menu
    while(user_input != "r" && user_input != "p" && user_input != "q")
            {
                cout << "Invalid input, please check for spelling and/or capitalization." << endl;
                cout << "Your only options are to see the rules or play." << endl;
                cout << "Please input r to see the rules of War of Cards, or input p to play War of Cards, or quit by inputting q: ";
                cin >> user_input;
                cout << endl;
            }
    //Will either ask the player to play or to quit after displaying the rules (no reason to duplicate the rules)
    if (user_input == "r")
    {
        print_war_of_cards_ruleset();
        cout << "Do you now want to play or quit (same inputs as before)?" << endl << "Please input here: ";
        cin >> user_input;
        while(user_input != "p" && user_input != "q")
            {
                cout << "Invalid input, please check for spelling and/or capitalization." << endl;
                cout << "Your only options are to play or quit." << endl;
                cout << "Please input p to play War of Cards, or quit by inputting q: ";
                cin >> user_input;
                cout << endl;
            }
    }
    return user_input;
}


string play_war_of_cards(long long& wallet)
{
    //Will hold the dealer's cards and players cards respectively for when they are empty to show the user the general structure
    //Of how the game will look like in play, will also give them the option to actually play or quit now that they know what the game will
    //Look like
    vector<card> dealer;
    vector<card> player;
    //Will hold what the current column being played is
    int current_column = 1;
    //Will hold the user's input
    string user_input;
    //If false, will display the beginning information as if the player has not ever played the game before
    //If true, will put the player right back into the game as it means they have already played the game before
    bool replay = false;
    //Will hold the result of playing a round of War of Cards
    char result;
    //When wallet is 0 or less, the program will end, and the user can replay with a starting value of $1000
    while (wallet > 0)
    {
        /*if (replay == true)
        {
            //Will reset the vectors for another round
            vector<card> dealer;
            vector<card> player;
        }*/
        //Display table function for beginning of play
        if (replay == false)
        {
            display_table(dealer, 0.0, player, 0.0, current_column);
        }
        cout << "You have: $" << wallet << endl << endl;
        //No need to repeat the display of the blank table as the user knows what it will look like by now
        if (replay == true)
        {
            result = play_column(wallet, current_column);
        }
        else 
        {
            //Initially ask to display rules or play a round of war, check for invalid input
            cout << "To see the rules of War of Cards, input r (you can see the rules at any time), to play, input p, to quit, input q: ";
            cin >> user_input;
            cout << endl;
            //Checks for valid input
            user_input = check_for_valid_input(user_input);
            //Will quit the game if the user desires
            if (user_input == "q")
            {
                return "q";
            }            
        }
        //Will play the first round after the beginning prompt is given and the user finally inputs something valid
        if (replay == false)
        {
            result = play_column(wallet, current_column); 
        }
        //Will ask player to continue w/ new round or quit if they lose, if they win, they will be prompted to continue
        //to the next column or to quit
        if (result == 'q')
        {
            return "q";
        }
         else if (result == 'l')
        {
            cout << "You have lost, you current amount left is: $" << wallet << endl;
            if (wallet == 0)
            {
                return "q";
            }
            cout << "Would you like to see the rules, play again, or quit (same inputs as before)?: ";
            cin >> user_input;
            user_input = check_for_valid_input(user_input);
            if (user_input == "q" || user_input == "Q" || user_input == "quit" || user_input == "Quit")
            {
                return "q";
            }
            if (user_input == "p" || user_input == "P" || user_input == "play" || user_input == "Play")
            {
                replay = true;
                current_column = 1;
                continue;
            }
        }
        else if (result == 'w')
        {
            cout << "You have won! Your current amount is: $" << wallet << endl;
            if (current_column == 3)
            {
                cout << "You have won all 3 columns, if you decide to continue, you will restart the game at column 1." << endl;
            }
            cout << "Would you like to see the rules, play again, or quit (same inputs as before)?: ";
            cin >> user_input;
            user_input = check_for_valid_input(user_input);
            if (user_input == "q" || user_input == "Q" || user_input == "quit" || user_input == "Quit")
            {
                return "q";
            }
            if (user_input == "p" || user_input == "P" || user_input == "play" || user_input == "Play")
            {
                if (current_column == 3)
                {
                    current_column = 1;
                }
                else 
                {
                    current_column++;
                }
                replay = true;
                continue;
            }
        }
        else if (result == 't')
        {
            cout << "You have tied. Your current amount is: $" << wallet << endl;
            if (current_column == 3)
            {
                cout << "You have tied at the third column, if you decide to continue, you will restart the game at column 1." << endl;
            }
            cout << "Would you like to see the rules, play again, or quit (same inputs as before)?: ";
            cin >> user_input;
            user_input = check_for_valid_input(user_input);
            if (user_input == "q" || user_input == "Q" || user_input == "quit" || user_input == "Quit")
            {
                return "q";
            }
            if (user_input == "p" || user_input == "P" || user_input == "play" || user_input == "Play")
            {
                if (current_column == 3)
                {
                    current_column = 1;
                }
                else 
                {
                    current_column++;
                }
                replay = true;
                continue;
            } 
        }
    }
    return "q";
}