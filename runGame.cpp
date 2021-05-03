 // CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 323 – Isha Karki and Christopher Gavin 
// Project 3 - Game Main File

/*
    This is the cpp file which actually runs all the code from the Gameplay class to create a terminal based game
    -this is a sort of stock market simulator game
    -each turn, the player is preseted with a list of companies and their attributes
    -they can choose to buy or sell shares in those companies, keeping in mind that their profit is determined by probability
    -sometimes, strange events will happen that completetely change how certain companies make money, watch out for those
    -at the end of the game, you win by having more money than you started with
*/

//include all files that could be needed (will reduce later, right now this is good for testing)
#include "Government.h"
#include "Player.h"
#include "Company.h"
#include "Event.h"
#include "Gameplay.h"
#include <time.h>
#include <iostream>    // needed to use cout and cin
#include <fstream>     // needed to read and write files
#include <string>      // needed for getline() and stoi()
#include <iomanip>     // needed for setprecision()
using namespace std;


int main()
{
    //intialize gameplay object, which will set all data to null or empty
    Gameplay game;

    cout << fixed << setprecision(2);
    srand(time(NULL));

    //set up game
    game.readGovernments();  // read the government txt file
    game.readCompanies();   // read the companies txt file
    game.readEvents();      // read the events txt file
    game.printGameInstructions();  //print game instructions
    game.getPlayerInfo();   //get the player info
    game.chooseGovernment();  //show the player the governments and choose one
    game.setUpEvents(); //choose which event will happen, when it will happen, and the durations

    //play game 
    game.runGeneralGame();

    //end program
    return 0;
}
