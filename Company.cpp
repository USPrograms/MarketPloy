 // CS1300 Fall 2020
// Author: Uri Soltz and Ferin Vonreich
// Recitation: 323 – Isha Karki and Christopher Gavin
// Project 3 - Class Company Implimentation
  #include <iostream>
  #include <string>
  #include "Company.h"
  using namespace std;

 /* 
    Company Class Source File
    Data:
    string companyName;
        int number_of_Employees;
        double Revenue;
        double Stock_Price_Per_Share;
        double previousPrice;  //the price per share in the last turn
        double level_of_risk;  //this holds the level of risk to reward for a stock, high number means large range of possible deviation, and the low number means low range
        bool is_subsidized; 
        string companyType;    //ie Industrial, Agricultural, Technologial, so on
*/

//--------------------------------------------CONSTRUCTORS----------------------------------------------------------------------------

//default constructor, set all values to zero or null
Company::Company()
{
    companyName = "";
    number_of_Employees = 0;
    Revenue = 0;
    Stock_Price_Per_Share = 0;
    level_of_risk = 0;
    is_subsidized = false;
    previousPrice = 0;

}

// Paramaterized constructor: sets all the variables to their respective inputs from the parameters of the function 
Company::Company(string name, int Employee_Number, double revenue, double Price_Per_Share, double previousPriceIn, double Risk_level, bool Subsidized, string type)
{
    companyName = name;
    number_of_Employees = Employee_Number;
    Revenue = revenue;
    Stock_Price_Per_Share = Price_Per_Share;
    level_of_risk = Risk_level;
    is_subsidized = Subsidized;
    previousPrice = previousPriceIn;
    companyType = type;
}

//-------------------------------------------GETTERS AND SETTERS-----------------------------------------------------------------------
string Company::getName()
{
    return companyName;
}
void Company::setName(string Name)
{
    companyName = Name;
}
int Company::getNumberEmployees()
{
    return number_of_Employees;
}
void Company::setNumberEmployees(int Employees)
{
    number_of_Employees = Employees;
}
double Company::getRevenue()
{
    return Revenue;
}
void Company::setRevenue(double revenue)
{
    Revenue = revenue;
}
double Company::getStockPrice()
{
    return Stock_Price_Per_Share;
}
void Company::setStockPrice(double StockPrice)
{
    Stock_Price_Per_Share = StockPrice;
}
double Company::getLevelofRisk()
{
    return level_of_risk;
}
void Company::setLevelofRisk(double RiskLevel)
{
    level_of_risk=RiskLevel;
}
bool Company::getSubsidized()
{
    return is_subsidized;
}
void Company::setSubsidized(bool subsidized)
{
    is_subsidized = subsidized;
}
string Company::getType()
{
    return companyType;
}
void Company::setType(string CompanyType)
{
    companyType = CompanyType;
}
double Company::getPreviousPrice()
{
    return previousPrice;
}
void Company::setPreviousPrice(double price)
{
    previousPrice = price;
}

//-------------------------------------GENERAL USE FUNCTIONS-----------------------------------------

/*
    *this function prints all data from a Company Object, well formatted, with labels, so player can view
*/
void Company::printCompany()
{
    cout << companyName << ": " << endl;
    cout << "   Price Per Share: " << Stock_Price_Per_Share;
    cout << "   Previous Price: " << previousPrice;
    double difference = Stock_Price_Per_Share - previousPrice;
    cout << "   Amount Changed: " << difference;
    cout << "   Level Of Risk: " << level_of_risk;
    cout << "   Numbers of Employees: " << number_of_Employees;
    cout << "   Revenue: " << Revenue;
    cout << "   Subsidized? ";
    if (is_subsidized)
    {
        cout << "Y" << endl;
    }
    else 
    {
        cout << "N" << endl;
    }
    cout << "   Company Type: " << companyType << endl;
}