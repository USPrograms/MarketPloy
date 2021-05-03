// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Vonreich
// Recitation: 323 – Isha Karki and Christopher Gavin
// Project 3 - Class Player Header
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Company.h"

using namespace std;
/* this file defines what the Player class will look like what datamembers and member functions are in it
more may be added depending on need*/

class Player
{
    // defines public member functions some of which are getters and setters as well as constructors
    public:
        //CONSTRUCTORS
        Player();
        Player(int stocks[],int starting_cash, int Total_stocks, string nameIn);

        //GETTERS AND SETTERS
        string getName();
        void setName(string name);
        int getStocksat(int index);
        void setStocksat(int number_of_shares,int index);
        double getCash();
        void setCash(double Cash);
        double getEarnedCash();
        void setEarnedCash(double Cash_Earned_Total);
        double getLostCash();
        void setLostCash(double Cash_Lost_Total);
        int getTotalStocks();
        void setTotalstocks(int stocks_total);
        int getStartingCash();
        void setStartingCash(int cash_starting);
        double getProfileValue();
        void setProfileValue(double profileValue);
        double getStartingCashWithInterest();
        void setStartingCashWithInterest(double startingInterest);


        //GENERAL USE FUNCTIONS
        /*
            *This function prints all data members of a player in a formatted and labeled way
        */
        void printPlayer();

    // defines Private data members    
    private:
        string Name;
        int stocks[5];  // this array holds the number of shares owned for each company
        double cash;
        int starting_cash;
        int Total_Stocks;  // this is the total number of stocks/shares
        double totalProfileValue;
        double startingCashWithInterest;
        double Total_Cash_Earned;
        double Total_Cash_Lost;
};
#endif