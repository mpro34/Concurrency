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
#include <map>
#include <chrono>

struct Email
{
    std::string subject;
    std::string body;
    std::string recipient;

    Email() {};
    Email(std::string _s, std::string _b, std::string _r) : subject(_s), body(_s), recipient(_r) {};
};

class EmailServer
{
private:
    std::vector<Email> EmailList;

public:
    EmailServer() {};

    // Helper function to break a string into a list of substrings based on a denotation
    std::vector<std::string> BreakIntoSubstrings(std::string s, char mark)
    {
        std::vector<std::string> result;
        for (int i = 0; i < (int)s.size(); i++)
        {
            if (s[i] == mark)
            {
                result.push_back(s.substr(0, i));
                s.erase(0, i+1);
            }
        }
        result.push_back(s);
        return result;
    }

    // Populate database with emails based on the input - Single thread
    void AddEmails(std::vector<std::string> newemails)
    {
        for (std::string emailstring : newemails)
        {
            AddEmailSingle(emailstring);
        }
    }

    // Create numThreads to handle emails list for adding to data store
    void AddEmailsMultipleThreads(int numThreads, std::vector<std::string> emails)
    {
        AddEmails(emails);
        // TODO: How to launch numThreads to handle X emails in list?
    }

    int GetEmailListSize()
    {
        return EmailList.size();
    }

    void ResetServer()
    {
        EmailList.clear();
    }

    // Creates a new thread of execution - readonly - that performs the requires steps in the input arg, each arg is seperated by a comma
    /*
        input format = "USERNAME,DATE" (i.e. "Chris,2020") -> Should print out all emails with username chris and date = 2020
    */
    void FetchEmails(std::vector<std::string> inputargs)
    {

    }

private:
	// Used when attempting to add emails with multiple threads
	void AddEmailSingle(std::string data)
	{
		// Parse emailstring recipient, subject and date
		std::vector<std::string> brokenup = BreakIntoSubstrings(data, ',');
		if (brokenup.size() == 3)
		{
			std::string recipient = brokenup[0];
			std::string subject = brokenup[1];
			int date = (int)stoi(brokenup[2]);

			EmailList.push_back(Email(subject, "body", recipient));
		}
	}
};


int main()
{
    std::cout << "EmailServer Started" << std::endl;

    // -- Adding work
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

    // Add emails with a single thread
    auto starta = std::chrono::high_resolution_clock::now();
    MyServer.AddEmails(SampleInput);
    auto enda = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(enda - starta);
    std::cout << "Single Threaded email add took = " << duration.count() << " ms" <<std::endl;
    MyServer.ResetServer(); // clear all added emails

    // Add emails with multiple threads
    auto startb = std::chrono::high_resolution_clock::now();
    int numThreads = 2;
    MyServer.AddEmailsMultipleThreads(numThreads, SampleInput);
    auto endb = std::chrono::high_resolution_clock::now();
    auto durationb = std::chrono::duration_cast<std::chrono::microseconds>(enda - starta);
    std::cout << numThreads << " Threaded email add func took = " << durationb.count() << " ms" << std::endl;
    
    // -- Fetching work

    std::vector<std::string> SampleFetch = 
    {
        "Chris,2020",
        "Bill,2020",
        "Mike,2021"
    };
    MyServer.FetchEmails(SampleFetch);

    // Should print out all emails for Chris in 2020, Bill in 2020, and Mike in 2021!
}
