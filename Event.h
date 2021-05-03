// CS1300 Fall 2020
// Author: Uri Soltz and Ferin Von Reich
// Recitation: 322 – Isha Karki and Christopher Gavin 
// Project 3 - Gameplay Source File

#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <iostream>

using namespace std;

//Header file for Class Event

class Event
{
    public:
        //CONSTRUCTORS
        Event();
        Event(string name, string eventInfo, string companyTypeAffectedIn, int eventTurns, double effectVal);

        //GETTERS AND SETTERS
        string getName() const;
        void setName(string name);
        string getDescription() const;
        void setDescription(string description);
        string getCompanyTypeAffected() const;
        void setCompanyTypeAffected(string companyType);
        int getEventDuration() const;
        void setEventDuration(int duration);
        double getEffectValue() const;
        void setEffectValue(double effect);
        int getEventExecuteTurn() const;
        void setEventExecuteTurn(int turnNum);
        bool getIsExecuting() const;
        void setIsExecuting(bool input);

        //GENERAL PURPOSE FUNCTIONS
        //prints data members of an event, properly formatted, with clear labels
        void printEvent();

    private:
        string eventName;
        string eventDescription;
        string companyTypeAffected;
        int eventDuration;     // the number of turns an event has an effect
        double effectValue;
        int eventExecuteTurn; // holds the turn in which the game will execute the event
        bool isExecuting;     //holds whether or not the event is executing and has an effect
};
#endif