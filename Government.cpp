// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Vonreich
// Recitation: 323 – Isha Karki and Christopher Gavin
// Project 3 - Class Government Source File
  #include <iostream>
  #include <string>
  #include "Government.h"
  using namespace std;

  /* 
  This is the government source file
  Data:
  string governmentName;
  double interest_rate;  //this is the general interst rate of the government, effects the range of the share price 
  double inflation;      
  double subsidies[5];  //this array holds the value of the subsidy for each company in the corresponding index
  double volitality;    //effects the range of share price and revenue, little spice in the market
  */

 //--------------------------------------------------CONTSTRUCTORS---------------------------------------------------------

// default constructor sets everything to zero or null
Government::Government()
{
    governmentName = "";
    interest_rate = 0;
    inflation = 0;
    for(int i=0; i<5; i++)
    {
        subsidies[i]= 0;
    }
    volatility = 0;
}

//parameterized constructor it sets all of the data menbers to the input values of the function
Government::Government(string GovernmentName, double Interest_Rate, double Inflation, double Subsidies[], double Volitality, int size)
{
    governmentName = GovernmentName;
    interest_rate = Interest_Rate;
    inflation = Inflation;

    // for the array if the size is less then 5 then it sets the values to the inputs untill it reaches the size then sets the remaining to zero
    // if size is bigger than 5 then it sets the subsidies array to the first 5 of the other array
    if(size < 5)
    {
        for(int i=0; i<size; i++)
        {
            subsidies[i]= Subsidies[i];
        }
        for(int i=size; i<5; i++)
        {
            subsidies[i]=0;
        }
    }
    else
    {
        for(int i=0; i<5; i++)
        {
        subsidies[i]= Subsidies[i];
        } 
    }

    volatility = Volitality;
}

//---------------------------------------------------------------GETTERS AND SETTERS-----------------------------------------------------

string Government::getGovernmentName()
{
return governmentName;
}
void Government::setGovernmentName(string name)
{
governmentName = name;
}
double Government::getInterestRate()
{
return interest_rate;
}
void Government::setInterestRate(double Interest_Rate)
{
interest_rate = Interest_Rate;
}
double Government::getSubsidiesAt(int index)
{
return subsidies[index];
}
void Government::setSubsidiesAt(int index, double subsidy)
{
subsidies[index] = subsidy;
}
double Government::getVolatility()
{
return volatility;
}
void Government::setVolatility(double Volitality)
{
volatility = Volitality;
}
double Government::getInflation()
{
return inflation;
}
void Government::setInflation(double Inflation)
{
inflation = Inflation;
}

//-------------------------------------GENERAL FUNCTIONS------------------------------------------------------------------

//This function will print every datamember of Government for player viewings
void Government::printGovernment()
{
   bool anySubsidy = false;
   cout << governmentName << " -- ";
   cout << " Interest Rate: " << interest_rate;
   cout << " Inflation: " << inflation;
   cout << " Volatility: " << volatility << endl;
   cout << "-Subsidies Include: " << endl;

    //step through subsidies and print out the value and company type that the subsidy effects
   if(subsidies[0] != 0)
   {
       cout << "    $ " << subsidies[0] << " Farming subsidy" << endl;
       anySubsidy = true;
   }
    if(subsidies[1] != 0)
   {
       cout << "    $ " << subsidies[1] << " Defence subsidy" << endl;
       anySubsidy = true;
   }
    if(subsidies[2] != 0)
   {
       cout << "    $ " << subsidies[2] << " Technology subsidy" << endl;
       anySubsidy = true;
   }
    if(subsidies[3] != 0)
   {
       cout << "    $ " << subsidies[3] << " Oil subsidy" << endl;
       anySubsidy = true;
   }
    if(subsidies[4] != 0)
   {
       cout << "    $ " << subsidies[4] << " Hospital subsidy" << endl;
       anySubsidy = true;
   }
   cout << endl;
   if(anySubsidy == false) //there was no subsidy
   {
       cout << "This government does not have any subsidies" << endl;
   }
}