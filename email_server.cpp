#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <map>

using namespace std;


class EmailServer
{
private:
    map<string, vector<string>> UserNameToListOfEmails;
    bool ServerOn = false;

public:
    EmailServer() {      
        ServerOn = true;
    };

    // returns a list of all emails for the specified username
    vector<string> GetEmailsForUser(string username)
    {
        vector<string> result;
        if (UserNameToListOfEmails.count(username) > 0)
        {
            result = UserNameToListOfEmails[username];
        }
        return result;
    }

    // adds the email and registers it for the username in the mapping
    void AddUserEmail(string username, string email)
    {
        if (UserNameToListOfEmails.count(username) > 0)
        {
            UserNameToListOfEmails[username].push_back(email);
        }
        else
        {
            vector<string> newemaillist;
            newemaillist.push_back(email);
            UserNameToListOfEmails[username] = newemaillist;
        }
    }

    // returns the number of emails for the specified username
    int GetMailCount(string username)
    {
        if (UserNameToListOfEmails.count(username) > 0)
        {
            return UserNameToListOfEmails[username].size();
        }
        return 0;
    }

    bool IsServerOn() 
    {
        return ServerOn;
    }

    // Create a thread for each Username to fetch the counts of their respective emails
    void FetchMailCountsAndPrint()
    {
        thread t_chris = thread(&EmailServer::GetMailCount, "Chris");
        thread t_bill = thread(&EmailServer::GetMailCount, "Bill");
        thread t_mike = thread(&EmailServer::GetMailCount, "Mike");

        t_chris.join();
        t_bill.join();
        t_mike.join();
    }


};


int main()
{
    cout << "Mail Server Starting..." << endl;
    EmailServer* server = new EmailServer();
    server->AddUserEmail("Chris", "All Hands Meeting Today at 4PM!");
    server->AddUserEmail("Chris", "engineering project 5, needs more work!");
    server->AddUserEmail("Bill", "hardware instructions are incomplete.");
    server->AddUserEmail("Mike", "threading is so cool, but not as much as robots");

    // Create a thread for each Username to fetch the counts of their respective emails
    server->FetchMailCountsAndPrint();


    return 0;
}