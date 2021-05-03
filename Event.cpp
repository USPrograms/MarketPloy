// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 323 – Isha Karki and Christopher Gavin 
// Project 3 - Event Source File

#include "Event.h" //include the header for Event Class
//Source File for Event class, with data:
//string eventName; string eventDescription; string companyTypeAffected; int eventDuration; double effectValue; int eventExecuteTurn; bool isExecuting; 

//---------------------------------------CONSTRUCTORS----------------------------------------------------------------------------------------

//default constuctor for Event object
Event::Event()
{
    // all strings intialized to empty strings
    eventDuration = 0;
    effectValue = 0;
    eventExecuteTurn = 0; //arbitary generated in game
    isExecuting = false;
}

//parameterized construtor for a Event object
Event::Event(string name, string eventInfo, string companyTypeAffectedIn, int eventTurns, double effectVal)
{
    eventName = name;
    eventDescription = eventInfo;
    companyTypeAffected = companyTypeAffectedIn;
    eventDuration = eventTurns;
    effectValue = effectVal;
    eventExecuteTurn = 0; 
    isExecuting = false;
}

//--------------------------------------------------------------SETTERS------------------------------------------------------------

//name setter
void Event::setName(string name)
{
    eventName = name;
}

//description setter
void Event::setDescription(string description)
{
    eventDescription = description;
}

//company type affected setter
void Event::setCompanyTypeAffected(string companyType)
{
    companyTypeAffected = companyType;
}

//event duration setter
void Event::setEventDuration(int duration)
{
    eventDuration = duration;
}

//effect value setter
void Event::setEffectValue(double effect)
{
    effectValue = effect;
}

//execute event turn setter
void Event::setEventExecuteTurn(int turnNum)
{
    eventExecuteTurn = turnNum;
}


//isExecuting setter
void Event::setIsExecuting(bool input)
{
    isExecuting = input;
}

//----------------------------------------------------------Getters------------------------------------------------------------------------------

//name getter
string Event::getName() const
{
    return eventName;
}

//description getter
string Event::getDescription() const
{
    return eventDescription;
}

//company type affected getter
string Event::getCompanyTypeAffected() const
{
    return companyTypeAffected;
}

//event duration getter
int Event::getEventDuration() const
{
    return eventDuration;
}

//effect value getter
double Event::getEffectValue() const
{
    return effectValue;
}

//event execute turn getter
int Event::getEventExecuteTurn() const
{
    return eventExecuteTurn;
}

//is executing getter
bool Event::getIsExecuting() const
{
    return isExecuting;
}

//-------------------------------------------GENERAL USE FUNCTIONS----------------------------------------------------------------

//prints data members of an event, properly formatted, with clear labels
void Event::printEvent()
{
    cout << "Event Name: " << eventName << endl;
    cout << eventDescription << endl;
    cout << "Affects: " << companyTypeAffected << ", Duration: " << eventDuration << " turn(s), Effect Value: " << effectValue << endl; 
}

        
        




   