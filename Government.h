// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Vonreich
// Recitation: 323 – Isha Karki and Christopher Gavin
// Project 3 - Class Government Header
#ifndef GOVERNMENT_H
#define GOVERNMENT_H
#include <string>
#include <vector>

/* this file defines what the government class will look like what datamembers and member functions are in it
more may be added depending on need*/

using namespace std;
class Government
{
  // defines public member functions some of which are getters and setters as well as constructors
  public:

  //CONSTRUCTORS
  Government();
  Government(string GovernmentName, double Interest_Rate, double Inflation, double Subsidies[], double Volitality, int size);

  //GETTERS AND SETTERS
  string getGovernmentName();
  void setGovernmentName(string name);
  double getInterestRate();
  void setInterestRate(double Interest_Rate);
  double getInflation();
  void setInflation(double Inflation);
  double getSubsidiesAt(int index);
  void setSubsidiesAt(int index, double subsidy);
  double getVolatility();
  void setVolatility(double Volitality);

  //GENERAL FUNCTIONS
  //this function prints all data of a government, properly formatted, with labels
  void printGovernment();

  // defines Private data members
  private:
  string governmentName;
  double interest_rate;  //this is the general interst rate of the government, effects the range of the share price 
  double inflation; 
  double subsidies[5];
  //vector <double> subsidies[5];  //this array holds the value of the subsidy for each company in the corresponding index
  double volatility;    //effects the range of share price and revenue, little spice in the market
};
#endif
