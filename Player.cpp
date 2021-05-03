// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Vonreich
// Recitation: 323 – Isha Karki and Christopher Gavin
// Project 3 - Class Player Source File
  #include <iostream>
  #include <string>
  #include "Player.h"
  #include "Company.h"
  using namespace std;

/* 
this is the Player implimentation file 
Data:
string Name; int stocks[5]; double cash; int starting_cash; int Total_Stocks; double Total_Cash_Earned; double Total_Cash_Lost;
*/

//default Constuctor
Player::Player()
{
    //set shares owned to 0
    for (int i = 0; i< 5; i++)
    {
        stocks[i] = 0;
    }
    starting_cash = 100000;
    cash = starting_cash;
    Total_Stocks = 5; 
    Total_Cash_Earned = 0;
    Total_Cash_Lost = 0;
    startingCashWithInterest = starting_cash;
    totalProfileValue = starting_cash;
}

//parameterized constructor it sets all of the data menbers to the input values of the function
// for the array if the Total Stocks is less then 5 then it sets the values to the inputs untill it reaches the Total Stocks then sets the remaining to zero
// if Total Stocks is bigger than 5 then it sets the subsidies array to the first 5 of the other array
Player::Player(int Stocks[],int Starting_Cash, int Total_stocks, string nameIn)
{
    //for the array if the Total Stocks is less then 5 then it sets the values to the inputs untill it reaches the Total Stocks then sets the remaining to zero
    if (Total_stocks < 5)
    {
        for (int i = 0; i<Total_stocks; i++ )
        {
            stocks[i] = Stocks[i];
        }
        for(int j = Total_stocks; j<5; j++)
        {
            stocks[j] = 0;
        }
    }
    else
    {
        for (int i = 0; i<5; i++ )
        {
            stocks[i] = Stocks[i];
        }
    }

    //set other values
    starting_cash = Starting_Cash;
    cash = starting_cash;
    Name = nameIn;
    Total_Cash_Earned = 0;
    Total_Cash_Lost = 0;
    startingCashWithInterest = starting_cash;
}

//------------------------------------------------- GETTERS AND SETTERS--------------------------------------------------------------------
string Player::getName()
{
    return Name;
}
void Player::setName(string name)
{
    Name = name;
}
int Player::getStocksat(int index)
{
    return stocks[index];
}
void Player::setStocksat(int numberOfShares,int index)
{
    stocks[index] = numberOfShares;
}
double Player::getCash()
{
    return cash;
}
void Player::setCash(double Cash)
{
    cash = Cash;
}
double Player::getEarnedCash()
{
    return Total_Cash_Earned;
}
void Player::setEarnedCash(double Cash_Earned_Total)
{
    Total_Cash_Earned = Cash_Earned_Total;
}
double Player::getLostCash()
{
    return Total_Cash_Lost;
}
void Player::setLostCash(double Cash_Lost_Total)
{
    Total_Cash_Lost = Cash_Lost_Total;
}
int Player::getTotalStocks()
{
    return Total_Stocks;
}
void Player::setTotalstocks(int stocks_total)
{
    Total_Stocks = stocks_total;
}
int Player::getStartingCash()
{
    return starting_cash;
}
void Player::setStartingCash(int cash_starting)
{
    starting_cash = cash_starting;
    startingCashWithInterest = starting_cash;
}
double Player::getProfileValue()
{
    return totalProfileValue;
}
void Player::setProfileValue(double profileValue)
{
    totalProfileValue = profileValue;
}
double Player::getStartingCashWithInterest()
{
    return startingCashWithInterest;
}
void Player::setStartingCashWithInterest(double startingInterest)
{
    startingCashWithInterest = startingInterest;
}

//------------------------------------------------------------General Functions-----------------------------------------------------

/*
    *This function prints all data members of a player in a formatted and labeled way
*/
void Player::printPlayer()
{
    cout << "Current cash Balance: $" << cash << " Starting Cash (Interest Applied): $" << startingCashWithInterest;
    cout << " Total Cash Earned: $" << Total_Cash_Earned << " Total Cash Spent: $" << Total_Cash_Lost << endl;
    cout << "              Total Portfolio Value: $" << totalProfileValue << endl << endl;
}