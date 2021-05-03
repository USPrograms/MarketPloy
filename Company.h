 // CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 322 – Isha Karki and Christopher Gavin 
// Project 3 - Class Company Header
#ifndef COMPANY_H
#define COMPANY_H
#include <string>

/* this file defines what the company class will look like what datamembers and member functions are in it
more may be added depending on need*/
using namespace std;

class Company
{
    public:
        //CONSTRUCTORS
        Company();
        Company(string name, int Employee_Number, double revenue, double Price_Per_Share, double previousPriceIn, double Risk_level, bool Subsidized, string type);

        //GETTERS AND SETTERS
        string getName();
        void setName(string Name);
        int getNumberEmployees();
        void setNumberEmployees(int Employees);
        double getRevenue();
        void setRevenue(double revenue);
        double getStockPrice();
        void setStockPrice(double StockPrice);
        double getLevelofRisk();
        void setLevelofRisk(double RiskLevel);
        bool getSubsidized();
        void setSubsidized(bool subsidized);
        string getType();
        void setType(string CompanyType);
        double getPreviousPrice();
        void setPreviousPrice(double price);

        //GENERAL PURPOSE
        /*
            *this function prints all data from a Company Object, well formatted, with labels, so player can view
        */
        void printCompany();

    private:
        string companyName;
        int number_of_Employees;
        double Revenue;
        double Stock_Price_Per_Share;
        double previousPrice;  //the price per share in the last turn
        double level_of_risk;  //this holds the level of risk to reward for a stock, high number means large range of possible deviation, and the low number means low range
        bool is_subsidized; 
        string companyType;    //ie Industrial, Agricultural, Technologial, so on
};
#endif