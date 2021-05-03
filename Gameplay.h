// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 323 – Isha Karki and Christopher Gavin 
// Project 3 - Gameplay Source File

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Government.h"
#include "Player.h"
#include "Company.h"
#include "Event.h"
#include <iostream>    // needed to use cout and cin
#include <fstream>     // needed to read and write files
#include <string>      // needed for getline() and stoi()
#include <iomanip>     // needed for setprecision()
using namespace std;


class Gameplay
{
    public:
        //Constructors----------------------------------------------------------------------------------------------------
        Gameplay();
        Gameplay(int turns, int gamePhase, Company companies[], Government governments[], Government chosenGovernment, Event events[], Player main_Player, int numCompanies);

        //setters and getters (primarily for debugging)-----------------------------------------------------------------------------
        int getTurns() const;
        void setTurns(int turnsIn);
        int getGamePhase() const;
        void setGamePhase(int phase);
        int getNumCompanies() const;
        void setNumCompanies(int companies);
        int getEventIndex() const;
        void setEventIndex(int index);


        //building block functions------------------------------------------------------------------------------------------------------
        /*
            *This function takes a string, splits it at every occurrence of a delimiter, and then populates an array of with the split pieces
            *Parameters: toSplit - string to be split
                        separator - delimeter which shows where string should be split
                        pieces - an array where the split apart string pieces will be stored
                        size - the size of pieces[]
            *Returns: the number of pieces the string was split into
        */
        int split(string toSplit, char separator, string pieces[], int size);
        /*
            *print a numbered list of all companies
        */
        void printNumberedCompanyList();
        /*
            *print a numbered list of all governments
        */
        void printNumberedGovernmentList();
        /*
            *This function checks if a string contains only digits
            *Parameters: toCheck
            *Returns: whether function contains only digits (true if it does)
        */
        bool validateInputDigits(string toCheck);
        /*
            *print stats on how the game is progressing (num turns left, current cash, etc.)
        */
        void printGameStats();
        /*
            *quit message function
        */
        void quit();
        /*
            *sort the array of companies in desceding order in terms of share price
        */
        int sortCompanies();
        //intial game set up
        /*
            *This functions looks into a txt file and fills the array governments
            *Returns 1 if succesfull, -1 if not
        */
        int readGovernments();
        /*
            *Fill companies[] with data from a txt file
            *return 1 if successfull, -1 if the file did not open
        */
        int readCompanies();
        /*
            *Fill events[] with data from a txt file
            *return 1 if successfull, -1 if the file did not open
        */
        int readEvents();
        /*
            *print an intro to the game and how it works
        */
        void printGameInstructions();
        /*
            *get the players name and how much cash they are starting with
        */
        void getPlayerInfo();
        /*
            *print the list of governements and have the user select one for the game
        */
        void chooseGovernment();
        /*
            *Set which event will happen, and when it will happen
        */
        void setUpEvents();

        //general gameplay---------------------------------------------------------------------------------------------------
        /*
            *calculate the new number of employees
            *Returns the number of employees
        */
        int calcNumberOfEmployees(int companyIndex);
        /*
            *Calclate the new share price, which gives a better chance of growth for lower risk companies
            *Returns the new share price (double)
        */
        double calcSharePrice(int companyIndex);
        /*
            *Calclate the new revenue, which gives a better chance of growth for lower risk companies
            *Returns the new revenue (double)
        */
        double calcRevenue(int companyIndex);
        /*
            *get the number of shares the users wants to buy, and place the order
        */
        void buy(int companyIndex);
        /*
            *get the number of shares the users wants to sell, and update needed variables
        */
        void sell(int companyIndex);
        /*
            *run and update variables for the next turn
        */
        void nextTurn();
        /*
            *This function handles alerting the user about events and dealing with their effects 
            *Returns: 1 if event stuff happened, 0 if event stuff did not happen
        */
        int handleEvents();
        /* (left the stub because this is pretty big function)
            This function gives the general main menu of companies that the user uses to play the game, it displays the list of companies, and each company has a submenu in which you can buy or sell shares
            1. sort the companies into correct order using sortCompanies()
            2. Check if there are no turns left in the game
                a) if there are no turns left, print the ending stats and recepit
                c) call quit() and end the program
            2. use handleEvents() to determine if any event related task must happen and inform user
            3. print the stats of game using printGameStats()
            4. print the numbered list of companies using printNumberedCompanyList() as well as an option for next turn, and an option for quit, and let user input selection
            5. make sure input is valid
            6. If user selects quit, call quit() and end program
            7. If user selects next turn, call nextTurn() and do this whole process again
            8. if the user selects a company, use printBuySellShortMenu to let them place orders, sell, or go back to this menu
        */
        void runGeneralGame();
        /*
            *This function handles buying and selling shares, as a submenu within the general menu
        */
        void printBuySellShortMenu(int companyIndex);
         /*
            *This function calculates the values in the players stock portfolio
        */
        void calculateProfileValue(); 
        /*
            Reapply interest to the starting cash (there was a mistake so this term is stored as interest)
        */
        void calculateStartingCashInflation();
        /*
            *This function generates a random number in a given range
            *Parameters: min- min number, max- max number
            *Returns the random number (double)
        */
        double randomNumber(double min, double max);
        /*
            *This function generates either 1 or 0 (which is used in this to signidy growth or decay for a stock price)
            *Returns 1 or 0 (int)
        */
        int binaryGenerator();

        //ending gameplay------------------------------------------------------------------------------------------------------------
        /*
            *This function prints out the final messages to the user once the game is over
        */
        void printEndingStats();
        /*
            *This function stores a users game stats in a txt file
        */
        void writeFinalStatsToFile();

    private:
        int turns;
        int gamePhase; // Start Middle or End
        Company companies[5];  
        Government governments[5];
        Event events[10];
        Government chosenGovernment;  
        Player main_Player;
        int numCompanies;
        int companySorted[5]; //indexes of companies to be sorted for printing them out 
        //vector <int> companySorted[5];
        Company companyTemp;
        int eventIndex;   // the event which will happen in this game index
};
#endif