// EmailServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Create an EmailServer
/*
    Should handle multiple emails per username
    Ability to handle multiple user requests at the same time (i.e. 10 users request their emails on a certain date)

    Just store emails locally in a map or other data structure.

*/

#include <iostream>
#include <thread>
#include <vector>
#include <string.h>

class EmailServer
{


public:
    EmailServer() {};

    // Populate database with emails based on the input
    void AddEmails(std::vector<std::string> newemails)
    {

    }

    // Creates a new thread of execution - readonly - that performs the requires steps in the input arg, each arg is seperated by a comma
    /*
        input format = "USERNAME,DATE" (i.e. "Chris,2020") -> Should print out all emails with username chris and date = 2020
    */
    void FetchEmails(std::vector<std::string> inputargs)
    {

    }
};


int main()
{
    std::cout << "EmailServer Started" << std::endl;

    // TODO: Add requests here to get emails
    std::vector<std::string> SampleInput =
    {
        "Chris,To whom is concerned,2020",
        "Chris,Hello email world!,2020",
        "Chris,new hire checklist,2021",
        "Bill,engineering meeting today,2020",
        "Bill,todays checklist,2021",
        "Mike,lunch at in-n-out,2020",
        "Mike,coffee break at 3pm,2020",
        "Mike,Friday bring your pet to work day,2021"
    };

    EmailServer MyServer = EmailServer();
    MyServer.AddEmails(SampleInput);

    std::vector<std::string> SampleFetch = 
    {
        "Chris,2020",
        "Bill,2020",
        "Mike,2021"
    };
    MyServer.FetchEmails(SampleFetch);

    // Should print out all emails for Chris in 2020, Bill in 2020, and Mike in 2021!
}
