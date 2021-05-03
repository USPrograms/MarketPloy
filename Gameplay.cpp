// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 323 – Isha Karki and Christopher Gavin 
// Project 3 - Gameplay Source File
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <time.h>
#include "Government.h"
#include "Player.h"
#include "Company.h"
#include "Event.h"
#include "Gameplay.h" //include the header for Gameplay Class
#include <iostream>    // needed to use cout and cin
#include <fstream>     // needed to read and write files
#include <string>      // needed for getline() and stoi()
#include <vector>
#include <fstream>
#include <cmath>
#include <stdio.h>
//#include <unistd.h>

using namespace std;

//Source File for Gameplay class, with data:
/*
    int turns;
    int GamePhase; // Start Middle or End
    Company companies[5];
    Government governments[5];
    Event events[10];
    Government chosenGovernment;
    Player main_Player;
    int numCompanies;
    int eventIndex;
*/


//-----------------------------------------------------CONSTRUCTORS-----------------------------------------------------------------------------------------------------------

//default constuctor for Gameplay object
Gameplay::Gameplay()
{
    turns = 0;
    gamePhase = 1;
    numCompanies = 5;
    eventIndex = 0;
    //objects and arrays will initalize to empty on their own
}

//parameterized construtor for a Gameplay object
Gameplay::Gameplay(int turnsIn, int gamePhaseIn, Company companiesIn[], Government governmentsIn[], Government chosenGovernmentIn, Event eventsIn[], Player main_PlayerIn, int numCompaniesIn)
{
    //fill normal data types
    turns = turnsIn;
    gamePhase = gamePhase;
    numCompanies = numCompaniesIn;
    eventIndex = 0;

    //fill the arrays
    for (int i = 0; i < 5; i++)
    {
        //only the events array is greater than size 5
        if (i > 4)
        {
            events[i] = eventsIn[i];
        }
        else 
        {
            companies[i] = companiesIn[i];
            governments[i] = governmentsIn[i];
            events[i] = eventsIn[i];
        }
    }

    //fill the objects
    main_Player = main_PlayerIn;
    chosenGovernment = chosenGovernmentIn;
}


//-------------------------------------------SETTERS AND GETTERS (PRIMARILY FOR DEBUGGING)------------------------------------------------------------------------------------------------------
int Gameplay::getTurns() const
{
    return turns;
}

void Gameplay::setTurns(int turnsIn)
{
    turns = turnsIn;
}

int Gameplay::getGamePhase() const
{
    return gamePhase;
}

void Gameplay::setGamePhase(int phase)
{
    gamePhase = phase;
}

int Gameplay::getNumCompanies() const
{
    return numCompanies;
}

void Gameplay::setNumCompanies(int companies)
{
    numCompanies = companies;
}

int Gameplay::getEventIndex() const
{
    return eventIndex;
}

void Gameplay::setEventIndex(int index)
{
    eventIndex = index;
}

//------------------------------------BASIC BUILDING BLOCK FUNCTIONS---------------------------------------------------------------------------------

//split function to parse txt files
int Gameplay::split(string toSplit, char separator, string pieces[], int size)
{
    //intialize holder variables
    int numPieces = 0; // number of pieces the string is split into
    int startIndex = 0; // the starting index for the current piece being found

    //step through toSplit to find pieces
    for (int i = 0; i < toSplit.length(); i++)
    {
        //Check for edge cases and then see if there is a separator at i
        if (numPieces > size - 1)  //more pieces than the size of the array case
        {
            return -1;
        }
        else if (i == toSplit.length() - 1)  //last piece case (since there is no delimiter at the end of the string)
        {
           pieces[numPieces] = toSplit.substr(startIndex, i - startIndex + 1);
           numPieces ++;
        }
        else if(toSplit[i] == separator)  //general case, look to see if i is the delimiter
        {
           pieces[numPieces] = toSplit.substr(startIndex, i - startIndex);
           startIndex = i + 1; //set the starting index for the next piece one index after the delimiter
           numPieces ++;
        }
    }

    //return the number of pieces
    if (toSplit == "" || numPieces != 0) // general case
    {
        return numPieces;
    }
    else  // delimiter is not found cases
    {
        pieces[0] = toSplit;
        return 1;
    } 
}

/*
    This Function Steps Through Companies[] and prints out the list of companies for use throughout the game
*/
void Gameplay::printNumberedCompanyList()
{
    //sort the companies in descending order
    sortCompanies();

    //step through companies and print them
    for (int i = 0; i < numCompanies; i++)
    {
        //print company
        cout << (i+1) << ". ";
        companies[companySorted[i]].printCompany();

        //print user info
        cout << "   Shares Owned: " << main_Player.getStocksat(companySorted[i]) << endl;
    }
}

/*
    *This Function Steps Through governments[] and prints out the list of governments with all relavent data
*/
void Gameplay::printNumberedGovernmentList()
{
    //step through governments to print it
    for (int i = 0; i < 5; i++)
    {
        //print government
        cout << (i+1) << ". ";
        governments[i].printGovernment();
    }
}

//Checks strings to make sure they are only digits (for usin stoi)
bool Gameplay::validateInputDigits(string toCheck)
{
    //step through the string to check for wrong characters
    for (int i = 0; i < toCheck.length(); i++)
    {
        //check if it is not a digit
        if (!isdigit(toCheck[i]))
        {
            return false;
        }
    }

    //check if string is empty
    if (toCheck == "")
    {
        return false;
    }

    //only digits
    return true;
}

/*
    *This function prints out the stats of the game
*/
void Gameplay::printGameStats()
{
    //print turns and player stats
    cout << endl << "Game Stats- Turns Left: " << turns << endl;
    cout << "Player Stats: "; 
    main_Player.printPlayer();
}

/*
    *This function prints the goodbye message
*/
void Gameplay::quit()
{
    cout << "Thanks for Playing!" << endl;
}

/*
    *This Function sorts an array of indexes which represents the companies in descending array in terms of share price
*/
int Gameplay::sortCompanies()
{
    //holder variables
    int numSwaps = 0;
    bool first = true;
    bool unsorted = false;
    int save;

    do
    {
        //set unsorted
        unsorted = false;

        //this is the first run
        if(first)
        {
            //fill the array with the indexes 1-5 for the companies
            for (int j=0; j< numCompanies; j++)
            {
                companySorted[j] = j;
            }
            first = false;
        }

        //go through and swap the stocks
        for(int i = 0; i< numCompanies-1; i++)
        {
            double oneStock = companies[companySorted[i]].getStockPrice();
            double twoStock = companies[companySorted[i+1]].getStockPrice();
            //cout << "One: " << oneStock << endl;
            //cout << "Two: " << twoStock << endl;
            if(oneStock < twoStock ) // if the share price is in wrong number
            {   
                //swap the elements
                save =companySorted[i];
                companySorted[i] = companySorted[i+1];
                companySorted[i+1] = save;
                unsorted = true; // since a swap was needed, set unsorted to true
            }
        }
    } 
    while (unsorted == true);
    
    //return the number of swaps done (for debugging mostly)
    return numSwaps;
}
//---------------------------------------------Invisible Functions to make Coding Easier ------------------------------------
/*
    *This function generates a random number in a given range
    *Parameters: min- min number, max- max number
    *Returns the random number (double)
*/
double Gameplay::randomNumber(double min, double max)
{
    double randomNumber = 0; 

    //create range as told to us by a ta
    int range = ((max - min) + 1);
    randomNumber = double (min + (rand() % range));  //generate random number
    return randomNumber;
}

/*
    *This function generates either 1 or 0 (which is used in this to signidy growth or decay for a stock price)
    *Returns 1 or 0 (int)
*/
int Gameplay::binaryGenerator()
{
     int randomNumber = 0;
    //srand(time(NULL)); 
   // int range = ((max - min) + 1);
    randomNumber = int (rand() % 2);
    //rand() % (max - min + 1);
    //cout << RAND_MAX << endl;
    return randomNumber;
}

//----------------------------------------------INITIAL GAME SETUP FUNCTIONS----------------------------------------------------------------------

/*
    *This functions looks into a txt file and fills the array governments
    *Returns 1 if succesfull, -1 if not
*/
int Gameplay::readGovernments()
{
    //defines variables
    int checkVal = -1;
    vector <string> Lines; //temproary storage for entire file 
    string input_line; // termporary storage for lines
    string pieces[10]; // resuts of split function made bigger on purpose
    int size = 9;  // size of the number of items in the 
    ifstream input; // open file var
    int counter = 0; // counter
    string Name; //temp name of government 
    double interestRate = 0; // temp interest 
    double inflation = 0; // temp inflation
    double volatility = 0; // temp volatility
    double subsidies[5];   // subsidies array
    
    //opens file  if it fails it send the folowing error message
    input.open("Governments.txt");
    if(input.fail())
    {
        cout << "Sorry the input file required to start the game is not here please re-install the game" << endl;
        return checkVal;
    }
    else
    {
        checkVal = 1;
    }
    //writes file into a vector this is to prevent bugs. I got bugs on past homework assignments and this fixed them so 
    //this was just a premature bug 
    
    while(getline(input,input_line))
    {
        //skips line if empty
        if (input_line.length()== 0)
        {
 
        }
        //write line to vector
        else if(counter < 5)
        {
            Lines.push_back(input_line);
            counter++;
        }
    }

    //runs a loop for each line
    for(int i = 0; i<5; i++)
    {
        //sets the temp line to the current line
        input_line = Lines[i];
 
        // splits the line into peieces
        split(input_line, ',',pieces,size);
        //cout << "moment after split function" << endl;
        //sets the name to the first piece
        Name = pieces[0];
 
        // sets interest rate to 2nd piece
        interestRate = stod(pieces[1]);
        //sets inflation to 3rd piece
        inflation = stod(pieces[2]);
        //sets volitality to 4th piece
        volatility = stod(pieces[3]);
        //sets the subsidies from the last 5 sections
        subsidies[0] = stod(pieces[4]);
        subsidies[1] = stod(pieces[5]);
        subsidies[2] = stod(pieces[6]);
        subsidies[3] = stod(pieces[7]);
        subsidies[4] = stod(pieces[8]);
        //applies the temp varialbles to there actual permanent location in the government class
        governments[i].setGovernmentName(Name);
        governments[i].setInterestRate(interestRate);
        governments[i].setInflation(inflation);
        // applies the temp subsidies to their actual permanent location in the government class
        for(int k=0; k<5; k++)
        {
            governments[i].setSubsidiesAt(k,subsidies[k]);
        }
        //applies the temp volitality to its actual locaiton in the government class 
        governments[i].setVolatility(volatility);
    }
 
    //close file return checker
    input.close();
    return checkVal;
}

/*
    *This functions looks into a txt file and fills the array companies
    *Returns 1 if succesfull, -1 if not
*/
int Gameplay::readCompanies()
{
    //define variables
    int checkVal = -1;
    // temp variables for storage
    vector <string> Lines; // vector for storage
    string input_line; // string to store the currently worked on line
    string pieces[10]; // an array to store the pieces
    int size = 7; // size
    ifstream input; // open file variable  
    int counter = 0; // counter
    string Name;    // temp name of company
    int numberOfEmployees = 0; // temp number of employees variable 
    double revenue = 0; // temp revenue variable 
    double pricePerShare = 0; //price per share temp variable 
    double previousePrice = 0; // previous price 
    double levelOfRisk = 0; //level of risk temp
    string type;
 
    // opens companies file 
    input.open("Companies.txt");
    if(input.fail()) // fail to open case
    {
        cout << "Sorry the input file required to start the game is not here please re-install the game" << endl;
        return checkVal;
    }
    else //opened case
    {
        checkVal = 1;
    }

    // writes file into a vector
    while(getline(input,input_line))
    {
        if (input_line.length()== 0)
        {
 
        }
        else if(counter < numCompanies)
        {
            Lines.push_back(input_line);
            counter++;
        }
    }

    // processes the vector line by line
    for(int i = 0; i<numCompanies; i++)
    {
        //sets the temp line to the current line 
        input_line = Lines[i];
 
        //splits the line
        split(input_line, ',',pieces,size);
        //writes the pieces that arent numbers to there temp variables
        Name = pieces[0];
        type = pieces[6];
        //writes the peices to their variables 
        numberOfEmployees = stoi(pieces[1]);
        revenue = stod(pieces[2]);
        pricePerShare = stod(pieces[3]);
        previousePrice = stod(pieces[4]);
        levelOfRisk = stod(pieces[5]);

        //writes the varialbles to a company in their respective locations
        companies[i].setName(Name);
        companies[i].setNumberEmployees(numberOfEmployees);
        companies[i].setRevenue(revenue);
        companies[i].setStockPrice(pricePerShare);
        companies[i].setPreviousPrice(previousePrice);
        companies[i].setLevelofRisk(levelOfRisk);
        companies[i].setType(type);
    }
 
    input.close();
    return checkVal;
}


/*
    *This functions looks into a txt file and fills the array events
    *Returns 1 if succesfull, -1 if not
*/
int Gameplay::readEvents()
{
    //holder vars
    int checkVal = -1;
    string input_line;
    string pieces[10];
    int eventCounter = 0; //holds the index of the current event being filled
    int size = 10;
    ifstream input;
    int counter = 0;  //counts the number of lines that have passed
    string name;
    string type;
    int duration = 0;
    double effectValue = 0;
    int eventTurn;

    input.open("Events.txt"); //open the file
    if(input.fail()) //input fail case
    {
        cout << "Sorry the input file required to start the game is not here please re-install the game" << endl;
        return checkVal;
    }
    else //file opened
    {
        checkVal = 1;
    }

    //go through the file and fill the array of events
    while(getline(input,input_line)) 
    {
        if (input_line.length() == 0) //line is empty case
        {
            //do nothing
        }
        else if(counter % 2 == 0) // Line 0, 2, 4, etc- These lines hold the name, type, duration, and effect Value
        {
            //split and get the temp vars
            split(input_line, ',', pieces, 4);
            name = pieces[0];
            type = pieces[1];
            duration = stoi(pieces[2]);
            effectValue = stod(pieces[3]);

            //fill events[]
            events[eventCounter].setName(name);
            events[eventCounter].setCompanyTypeAffected(type);
            events[eventCounter].setEventDuration(duration);
            events[eventCounter].setEffectValue(effectValue);
            
            //increment counter
            counter++;
        }
        else //this line holds the description for the event
        {
            //place the description and increment counters
            events[eventCounter].setDescription(input_line);
            counter++;
            eventCounter++;
        }
    }

    //close counter
    input.close();

    //debug
    // for (int i = 0; i<10; i++)
    // {
    //     events[i].printEvent();
    // }
    
    return checkVal;
}

//this function tells the player how the game works
void Gameplay::printGameInstructions()
{
    
    cout << endl;
    cout << "Welcome to the Stock Market Game, where you buy and sell shares in companies!" << endl;
    cout << "The object of the game is simple, you want to make a profit, any profit (accounting for inflation) by the end." << endl;
    cout << "How it works: Each turn, you will see a list of different companies, with different data about them." << endl << endl;
    cout << "The big things to look at will be the level of risk and the question of subsidization." << endl;
    cout << "Other data fields play a factor in the share price, but less so, so we will let you figure it out during play :)" << endl;
    cout << "Level of Risk is measure of the variability of the stock. The higher the number, the higher the risk and reward." << endl;
    cout << "Subsidies are applied each turn to the revenue, which then has an effect on the stock price over time." << endl << endl;
    cout << "Oh, and just so you know, randomly during the game, there will be an event which has a huge effect on the game, be prepared for that." << endl;
    cout << "We hope you see by the end that most day trading is just gambling, and maybe you get better at math too!" << endl << endl;
}

//this function gets the players name, how much money to start with, and the number of turns in the game      
void Gameplay::getPlayerInfo()
{
    //get and set name
    cout << "Now that you know how the game works, lets set it up. Please enter your name:" << endl;
    string name;
    getline(cin, name);
    main_Player.setName(name);

    //get and set the money starting
    string money;
    while (!validateInputDigits(money))  //ask for value while the user has not put in only digits
    {
      cout << "How much money do you want to start with? (we would say start with $7,500 and you will see if that is too easy or too hard)" << endl;
      getline(cin, money);
    }

    //get the number of turns (restricked between 10-30 because that makes the game more fun and can avoid int overflow errors)
    string turnsString;
    while(!validateInputDigits(turnsString) || stoi(turnsString) < 10 || stoi(turnsString) > 30) //ask for value while it is not a digit, and not in correct range
    {
        cout << "How many turns do you want to play to? (minimum is 10, maximum is 30, we recommend starting with 10)" << endl;
        getline(cin, turnsString);
    }
    cout << endl;

    //set the values
    main_Player.setCash(stod(money));
    main_Player.setStartingCash(stoi(money));
    calculateProfileValue();
    setTurns(stod(turnsString));
}

/*
    *This functions explains what each data member of governments means, and has the user select their governement
*/
void Gameplay::chooseGovernment()
{
    //explain what the governments are
    cout << "Now you have to pick what government you want to trade under." << endl;
    cout << "The inflation rate is what is going to make the game hard, the higher it is, the more you'll have to earn to profit, so pick carefully." << endl;
    cout << "The volatility is the variability of the market, the higher it is, the more the market will fluctuate between turns." << endl;
    cout << "The interest rate does not effect things in the current version of the game, it is there for future versions." << endl << endl;

    //print out the list of governments
    printNumberedGovernmentList();

    //get the choice
    string input;
    int inputInt;
    while(!validateInputDigits(input)) //do the following while the input is not a digit
    {   
        cout << "Please select a Government (index number)" << endl;
        getline(cin,input);

        //check if the input is a digit, but is not in the correct range
        if (validateInputDigits(input))
        {
            if (stoi(input) < 1 || stoi(input) > 5)
            {
                input = "";
            }
        }
    } 
    
    //allocate the chosen government and tell the user
    inputInt = stoi(input);
    chosenGovernment = governments[inputInt-1];
    cout << "Congratulations you have chosen " << chosenGovernment.getGovernmentName() << ", Let's Start the Game!" << endl << endl;
    
    //set the is subsidized field for each company, indexes correspond
    for (int i = 0; i < 5; i++)
    {   
        //check if there is a subsidy
        if (chosenGovernment.getSubsidiesAt(i) != 0)
        {
            companies[i].setSubsidized(true);
        }
    }
}

/*
    *Set which event will happen, and when it will happen
*/
void Gameplay::setUpEvents()
{
    //set which event will happen
    eventIndex = randomNumber(0, 9);

    //set the execute turn for the chosen event
    events[eventIndex].setEventExecuteTurn(randomNumber(2, (turns - 4)));

    //debug
    // cout << "event Index:" << eventIndex << endl;
    // cout << "execute turn:" << events[eventIndex].getEventExecuteTurn() << endl;
    // cout << "type affected:" << events[eventIndex].getCompanyTypeAffected() << endl;
}

//-------------------------------------------GENERAL GAMEPLAY-------------------------------------------------------------------

/*
    *This function calculates the number of employees for the next turn
    *Returns: number of employees
*/
int Gameplay::calcNumberOfEmployees(int companyIndex)
{
    double newEmployees = 0;
    double Employees = companies[companyIndex].getNumberEmployees();
    
    //set up randomizer, the employee change deals with both a random growth, and the level of risk in the company (but does not factor in share price calc, red herring to make the game intersesting)
    bool growth = binaryGenerator();
    double min = companies[companyIndex].getLevelofRisk();
    double max = 5*companies[companyIndex].getLevelofRisk();

    //use a similiar alogrithm to share price which gives a better chance of growth for lower risk company 
    if(min < double (3) && growth == false)
    {
        growth = binaryGenerator();
    }
    if(min < double (1) && growth == false)
    {
        growth = binaryGenerator();
    }

    //calc the new employees
    if(growth)
    {
        newEmployees = Employees + randomNumber(min,max);
    }
    else
    {
        newEmployees = Employees - randomNumber(min,max);
    }

    //return
    return newEmployees;
}

/*
    *Calclate the new share price, which gives a better chance of growth for lower risk companies
    *Returns the new share price (double)
*/
double Gameplay::calcSharePrice(int companyIndex)
{
    //holder variables
    double newPrice = 0;
    double price = companies[companyIndex].getStockPrice();
    companies[companyIndex].setPreviousPrice(price); //set the previous price to the current price, since this is called during nextTurn()

    //set stuff for randomizing
    bool growth = binaryGenerator();
    double min = 1*companies[companyIndex].getLevelofRisk() * chosenGovernment.getVolatility(); 
    double max = 21*companies[companyIndex].getLevelofRisk() * chosenGovernment.getVolatility();
    double change = ((companies[companyIndex].getRevenue() + randomNumber(min,max))/(companies[companyIndex].getNumberEmployees())); //change takes into account the revenue since they are correlated

    //set change to be positive
    if (change < 0)
    {
        change = -change;
    }

    //check the growth value to bias low risk companies to have growth each turn (3 try for growth once, 1 try for growth twice)
    if(min < double (4) && growth == false)
    {
        growth = binaryGenerator();
    }
    if(min < double (1) && growth == false)
    {
        growth = binaryGenerator();
    }

    //set the new price
    if(growth)
    {
        newPrice = price + change;
    }
    else
    {
        newPrice = price - change;
    }

    //get the data to check if an event is in effect
    string companyType = companies[companyIndex].getType();
    string eventAffectsType = events[eventIndex].getCompanyTypeAffected();
    //debug
    // cout << companyType << endl;
    // cout << eventAffectsType << endl;
    // cout << events[eventIndex].getIsExecuting() << endl;
    
    
    //apply the effects of an event if needed
    if (events[eventIndex].getIsExecuting())
    {
        //if the first letter of the company type and the affected type are the same
        if (companyType[0] == eventAffectsType[0])
        {
            //debug
            //cout << "I APPLIED IT BOOSSSS _________________-----------------------" << endl << endl << endl << endl;

            //set the new price
            newPrice = newPrice * events[eventIndex].getEffectValue(); //this works as a percentage multiplier, so it has a drastic change
        }
    }
    
    //return it;
    return newPrice;
}

/*
    *Calculate the new revenue, which gives a better chance of growth for lower risk companies
    *Returns the new revenue (double)
*/
double Gameplay::calcRevenue(int companyIndex)
{
    //holder vars
    double newRevenue = 0;
    double revenue = companies[companyIndex].getRevenue();

    //set randomizing stuff
    bool growth = binaryGenerator();
    double min = 3 * companies[companyIndex].getLevelofRisk() * chosenGovernment.getVolatility();
    double max = 15*companies[companyIndex].getLevelofRisk() * chosenGovernment.getVolatility();
    double levelOfRisk = companies[companyIndex].getLevelofRisk() * chosenGovernment.getVolatility();

    //check the growth value to bias low risk companies to have growth each turn (4 try for growth once, 1 try for growth twice)
     if(levelOfRisk < double (4) && growth == false)
    {
        growth = binaryGenerator();
    }
    if(levelOfRisk < double (1) && growth == false)
    {
        growth = binaryGenerator();
    }

    //set the new revenue
    if(growth)
    {
        newRevenue = revenue + randomNumber(min,max);
    }
    else
    {
        newRevenue = revenue - randomNumber(min,max);
    }
    
    //apply the subsidy if applicible (share price is partially correlated to revenue so this will effect share price in the next turn)
    if (companies[companyIndex].getSubsidized())
    {
        newRevenue += chosenGovernment.getSubsidiesAt(companyIndex);
    }

    return newRevenue;
}

/*
    *get the number of shares the users wants to buy, and place the order
*/
void Gameplay::buy(int companyIndex)
{
    //holders 
    string input;
    char inputChar;
    int numberOfShares = 0; //this will hold the number of shares the user wants to bu
    double cashLost = main_Player.getLostCash();
    int numberOfShares_old = main_Player.getStocksat(companyIndex);
    double amountDue = 0;
    double cash = main_Player.getCash();
    double sharePrice = companies[companyIndex].getStockPrice();
    
    //get the number of shares to be bought with error correction
    cout << "How many shares would you like to buy?" << endl;
    getline(cin,input);
   if(validateInputDigits(input))
   {
       numberOfShares = stoi(input);
   } 
   else //input invalid case
   {
       cout << "Sorry please enter a real value" << endl;
       return;
   }

    //if the input was valid and the user wants to buy shares do this
   if(numberOfShares > 0)
   {
       //find the number of shares and then see if the user can afford those shares
       amountDue = numberOfShares*sharePrice;

       if (amountDue > cash) //user wants to buy more than they can afford
       {
           if(cash < sharePrice) //user cannot afford any shares case
           {
               cout << "Sorry you are broke and the $" << cash << " isn't even enough to buy one share :(!" << endl;
               numberOfShares = 0;
           }
           else //user can affor some shares case
           {
               //tell user what they can afford
               cout << "Unfortunately the $" << cash << " isn't enough to buy you " << numberOfShares << " shares of ";
               cout << companies[companyIndex].getName() << " stock" << endl;
               numberOfShares = cash/sharePrice;  //calc the number of shares that could be bought
               cout << "However you can still afford to get " << numberOfShares << " shares." << endl;
               cout << "would you like to do that? (Y/N)" << endl; //ask if they want to do this
               getline(cin,input); //get input
               inputChar = input[0]; //get the first letter in case they said "yes" instead of y
               switch (inputChar) //look through options
               {    
                    //not buying case
                    case 'n':
                    case 'N':
                        cout << "Ok nothing has changed, and you still have $" << cash << "." << endl;
                        numberOfShares = 0;
                        break;
                    //buying case
                    case 'y':
                    case 'Y':
                            amountDue = numberOfShares*sharePrice;
                            cout << "Ok you have bought " << numberOfShares << " shares of " << companies[companyIndex].getName();
                            cout << "costing you $" << amountDue << " bringing your new balance of cash to $";
                            cash = cash - amountDue;
                            cout << cash << '.' << endl;
                            break;
                    //invalid inpput cae
                    default:
                        cout << "Ok nothing has changed, and you still have $" << cash << "." << endl; 
                        numberOfShares = 0;
                        break;
               }
           }
       }
       else //user can afford the number of shares they want
       {
            cout << "Ok you have bought " << numberOfShares << " shares of " << companies[companyIndex].getName();
            cout << " costing you $" << amountDue << " bringing your new balance of cash to $";
            cash = cash - amountDue;
            cout << cash << '.' << endl;
       }

       //set values
       main_Player.setCash(cash);
       numberOfShares = numberOfShares + numberOfShares_old;
       main_Player.setStocksat(numberOfShares, companyIndex);
       cashLost = cashLost + amountDue;
       main_Player.setLostCash(cashLost);
   }
   else //input was not valid or was 0
   {
    cout << "Ok nothing has changed, and you still have $" << cash << "." << endl;
    numberOfShares = 0;
   }
   
    //returns nothing
}

/*
    *get the number of shares the users wants to sell, and update needed variables
*/
void Gameplay::sell(int companyIndex)
{
    //holder variables
    string input;
    double cashEarned;
    char inputChar;
    int numberOfShares = 0;
    int numberOfShares_old = main_Player.getStocksat(companyIndex);
    double amountGained = 0;
    double cash = main_Player.getCash();
    double sharePrice = companies[companyIndex].getStockPrice();

    while(!validateInputDigits(input)) //get input while input is not digits
    {
        cout << "How many shares would you like to sell?" << endl;
        getline(cin,input);

        //check to make sure the input is within the number of shares available
        if (validateInputDigits(input))
        {
            if (stoi(input) < 0 || stoi(input) > numberOfShares_old)
            {
                cout <<"Sorry please enter valid number of shares." << endl;
                input = "";
            }
        }
    } 
   numberOfShares = stoi(input);

    
   if(numberOfShares >= 0)
   {
    //get the profit and tell the user
     amountGained = numberOfShares*sharePrice;
     cash = cash + amountGained;
     cout << "You have sold " << numberOfShares << " of " << companies[companyIndex].getName() << " stock for $";
     cout << amountGained << "." << endl;

     //set needed values
     numberOfShares = numberOfShares_old - numberOfShares;
     main_Player.setStocksat(numberOfShares, companyIndex);
     cashEarned = main_Player.getEarnedCash();
     cashEarned = cashEarned + amountGained;
     main_Player.setEarnedCash(cashEarned);
     main_Player.setCash(cash);
   }
   else //shreas to buy was 0
   {
       cout << "Please enter a number that is at or above zero" << endl;
       return;
   }
}

/*
    This function calculates the required profile values
*/
void Gameplay::calculateProfileValue()
{
    double sum = 0;
    double cash = main_Player.getCash();
    double additive = 0;
 
 
    //step through and get the money in each stock
    for(int i =0; i< numCompanies; i++)
    {
        additive = companies[i].getStockPrice() * double(main_Player.getStocksat(i));
        sum = sum + additive;
    }
 
    //find the total sum made and set it
    sum = sum + cash;
    main_Player.setProfileValue(sum);
}

/*
    Reapply interest to the starting cash (there was a mistake so this term is stored as interest)
*/
void Gameplay::calculateStartingCashInflation()
{
    //get inflation and get the prevous starting cash
    double infationRate = chosenGovernment.getInflation()/100;
    double startingCash = double(main_Player.getStartingCashWithInterest());
 
    //calc the starting cash and set it
    startingCash = startingCash + startingCash*infationRate;
    main_Player.setStartingCashWithInterest(startingCash); //this term actually holds the cash with inflation, a type was had which just stayed
}

/*
    This function progresses the game to the next turn
*/
void Gameplay::nextTurn()
{   
    //decrement turns
    turns --;
    if (turns > 0)
    {
    cout << endl;
    cout << "------------------------------------------NEW TURN ----------------------------------------- " << endl;
    }

    //check for events and deal with them
    handleEvents();
 
    //step through each company and update required data
    for (int i = 0; i < numCompanies; i++)
    {
        companies[i].setRevenue(calcRevenue(i));
        companies[i].setNumberEmployees(calcNumberOfEmployees(i));
        companies[i].setStockPrice(calcSharePrice(i)); 
    }
 
    //calculate the profile, apply inflation, and sort companies
    calculateProfileValue();
    calculateStartingCashInflation();
    sortCompanies();
}


/*
    *This function handles alerting the user about events and dealing with their effects 
    *Returns: 1 if event stuff happened, 0 if event stuff did not happen
*/
int Gameplay::handleEvents()
{
    //check if event should be triggered
    if (turns == events[eventIndex].getEventExecuteTurn() && turns != 0)
    {
        //check if you need to print description of event effects
        cout << endl << "Looks Like There Was An Event Triggered!" << endl;
        events[eventIndex].printEvent(); //show the user the event
        events[eventIndex].setIsExecuting(true); //set is excuting to true
        events[eventIndex].setEventDuration(events[eventIndex].getEventDuration() - 1);  //decrement the number of turns left in the event by 1
        return 1;
    }
    else if (events[eventIndex].getIsExecuting() && events[eventIndex].getEventDuration() != 0 && turns != 0) //check if event is currently happening and is not at the end
    {
        cout << endl << "The event is still happening, keep this in mind!" << endl;
        //debug
        // for (int i = 0; i < 10; i ++)
        // {
        //     cout << "events " << i << endl;
        //     events[i].printEvent();
        // }
        events[eventIndex].printEvent(); //show the user the event
        events[eventIndex].setEventDuration(events[eventIndex].getEventDuration() - 1);  //decrement the number of turns left in the event by 1 
        return 1;
    }
    else if (events[eventIndex].getIsExecuting() && events[eventIndex].getEventDuration() == 0) //the event is over
    {
        events[eventIndex].setIsExecuting(false);
        return 1;
    }

    //nothing happened
    return 0;
}

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
void Gameplay::runGeneralGame()
{
    // defines variables
    string input = "";
    int choice = 0;

    //checks if the choice isn't 7 and you still have turns if so it runs the loop 
    while(choice != numCompanies + 2 && turns != 0)
    {
        // resets the input
        input = "";
        // prints the stats
        printGameStats();
        cout << "Please Input an Option!" << endl;

        //prints the menu 
        printNumberedCompanyList();
        cout <<  numCompanies + 1 <<". End Turn" << endl;
        cout << numCompanies + 2 << ". Quit" << endl;

        // takes in and validates input to make sure that it is a digit
        while(!validateInputDigits(input))
        {
            getline(cin,input);
        }
        //converts input to intiger
        choice = stoi(input);

        //checks input to see what to do
        if(choice > 0 && choice <= numCompanies) //input is within range for a company, show buy sell menu
        {
            printBuySellShortMenu(companySorted[choice-1]);
        }
        else if (choice < numCompanies + 2) //end turn case
        {
            nextTurn();
            
        }
        else if (choice == numCompanies + 2) //quit case
        {
            quit();
            break;
        }
    }

    // runs the end game functions
    if (turns <= 0)
    {
        printEndingStats();
        writeFinalStatsToFile();
    }
   //returns nothing
}

/*
    *This function handles buying and selling shares, as a submenu within the general menu
*/
void Gameplay::printBuySellShortMenu(int companyIndex)
{
    //defines variables
    string input;
    int choice;

    //prints the menu for buying stocks the menu displays the variables company name and player stocks
    cout << "You have selected " << companies[companyIndex].getName() << " you currently own " << main_Player.getStocksat(companyIndex);
    cout << " shares" << endl;
    cout << "Would you like to" << endl;
    cout << "1. Buy shares" << endl;
    cout << "2. Sell shares" << endl;
    cout << "3. Go back" << endl;

    //takes in input and validates it to make sure that it is a digit
    while(!validateInputDigits(input))
    {
        getline(cin,input);
    }
    // converts the string to a int
    choice = stoi(input);

    // does a switch which decides either buy or sell or does nothing
    switch(choice)
    {
        case 1:
            buy(companyIndex);
            break;
        case 2:
            sell(companyIndex);
            break;
        case 3:
            break;
        default:
            break;
    }
    // returns nothing
}

//-------------------------------------------END GAME STUFF-------------------------------------------------------------

/*
    *This function prints out the final messages to the user once the game is over
*/
void Gameplay::printEndingStats()
{
    //get vars needed
    calculateProfileValue(); //calc current profile
    //defines variables used for comparing
    double profileValue = main_Player.getProfileValue();
    double startingCash = main_Player.getStartingCashWithInterest(); // interst is actually inflation I messed up
    bool first = true;
    //prints game over
    cout << "--------------------------------GAME OVER -----------------------------------------" << endl;
    //check if won or lost
    if (profileValue > startingCash) //won case
    {   
        //prints winning message with the variables name, profile value and starting cash 
        cout << "Congratulations " <<  main_Player.getName() << ", " << endl;
        cout << "YOU WON! your profile value of $" << profileValue << " exceeded the startingCash Value (Inflation Applied) of $";
        cout << startingCash << endl;
        //calculates amount gained
        cout << "You have made $" << profileValue - startingCash << " Investing." << endl;
    }
    else //lost case
    {
        //Prints losing message with the variables name, profile value , and starting cash
        cout << "Hi " <<  main_Player.getName() << ", " << endl;
        cout << "YOU LOST! your profile value of $" << profileValue << "  did not exceed the startingCash Value (Inflation Applied) of $";
        cout << startingCash << " :(" << endl; 
        cout << "You have lost $" <<  startingCash - profileValue << " Investing." << endl;
    }
    for(int i = 0; i<numCompanies; i++)
    {
       if(main_Player.getStocksat(i) != 0)
       {
            if(first ==true)
           {
               cout << endl;
               cout << "Your stocks include:" << endl;
               first = false;
           }
           cout << endl;//actually does the printing with the variables name, # of shares, stock price, and total value
           cout << companies[i].getName() << " shares owned: " << main_Player.getStocksat(i) << " valued at $" << companies[i].getStockPrice();
           cout << " Total Value of $" << main_Player.getStocksat(i)*companies[i].getStockPrice() << endl;
       }
    }
    cout << endl;
    //receipt message
    cout << "For future reference, your game stats were printed to gameStats.txt, thanks for playing!" << endl;
}

/*
    *This function stores a users game stats in a txt file
*/
void Gameplay::writeFinalStatsToFile()
{
    //Define Variable for opening and closing file
    ofstream outfile;
    remove("gameStats.txt"); // remove the file if it exists already
    bool first = true;
    // creates a new file called gameStats.txt
    outfile.open("gameStats.txt");
    // stops the file from being written in scientific notation
    outfile << fixed << setprecision(2);

    //Write message
    outfile << "--------------------------------GAME STATS -----------------------------------------" << endl;

    //calc needed vars
    calculateProfileValue();
    //defines variables used in comparison the first is the total profile value and the second is the cash with the inflation applied
    double profileValue = main_Player.getProfileValue();
    double startingCash = main_Player.getStartingCashWithInterest(); // interest is actually inflation I miss-Named it

    // check if they won or lost
    if (profileValue > startingCash) //won case
    {
        // writes winning message include variables name, Profile value,and starting cash
        outfile << "Congratulations " <<  main_Player.getName() << ", " << endl;
        outfile << "YOU WON! your profile value of $" << profileValue << " exceeded the startingCash Value (Inflation Applied) of $";
        outfile << startingCash << endl;
        // it also calculates how much you made
        outfile << "You have made $" << profileValue - startingCash << " Investing." << endl;
    }
    else //lost case
    {
        // writes losing message include variables name, Profile value,and starting cash
        outfile << "Hi " <<  main_Player.getName() << ", " << endl;
        outfile << "YOU LOST! your profile value of $" << profileValue << " did not exceed the startingCash Value (Inflation Applied) of $";
        outfile << startingCash << " :(" << endl; 
        // it also calculates how much you Lost
        outfile << "You have lost  $" <<  startingCash - profileValue << " Investing." << endl;
    }
    
     for(int i = 0; i<numCompanies; i++)
    {
       if(main_Player.getStocksat(i) != 0)
       {
           if(first ==true)
           {   outfile << endl;
               outfile << "Your stocks include:" << endl;
               first = false;
           }
           outfile << endl;//actually does the printing with the variables name, # of shares, stock price, and total value
           outfile << companies[i].getName() << " shares owned: " << main_Player.getStocksat(i) << " valued at $" << companies[i].getStockPrice();
           outfile << " Total Value of $" << main_Player.getStocksat(i)*companies[i].getStockPrice() << endl;
       }
    }

 
    //Closes the file;
    outfile.close();
}
