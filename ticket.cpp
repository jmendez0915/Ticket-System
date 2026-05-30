#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Ticket {
    public:
        int id;
        string name;
        string issue;
        string category;
        string status;
        string priority;
};

void createTicket(vector<Ticket>& tickets);
void viewTickets(const vector<Ticket>& tickets);
void searchTickets(const vector<Ticket>& tickets);
void updateTicketStatus(vector<Ticket>& tickets);
void saveTicket(const vector<Ticket>& tickets);
void loadTickets(vector<Ticket>& tickets);
void deleteTicket(vector<Ticket>& tickets);
int getNextTicketID(const vector<Ticket>& tickets);

int main()  {
    vector<Ticket> tickets;
    int choice;

    do
    {
        cout << "\n===== Help Desk Ticket System =====\n";
        cout << "1. Create New Ticket\n";
        cout << "2. View All Tickets\n";
        cout << "3. Search Ticket by ID\n";
        cout << "4. Update Ticket Status\n";
        cout << "5. Save Tickets\n";
        cout << "6. Load Tickets\n";
        cout << "7. Delete Ticket\n";
        cout << "8. Exit\n";
        cout << endl << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice)  {
            case 1:
                createTicket(tickets);
                break;
            case 2:
                viewTickets(tickets);
                break;
            case 3:
                searchTickets(tickets);
                break;
            case 4:
                updateTicketStatus(tickets);
                break;
            case 5:
                saveTicket(tickets);
                break;
            case 6:
                loadTickets(tickets);
                break;
            case 7:
                deleteTicket(tickets);
                break;
            case 8:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while(choice != 8);    
    
    return 0;
}


void createTicket(vector<Ticket>& tickets)  {
    Ticket newTicket;

    newTicket.id = getNextTicketID(tickets);
    
    cout << "Enter customer/user name: ";
    getline(cin, newTicket.name);

    cout << "Enter issue description: ";
    getline(cin, newTicket.issue);

    cout << "Enter category: ";
    getline(cin, newTicket.category);

    cout << "Enter priority: ";
    getline(cin, newTicket.priority);

    newTicket.status = "Open";
    tickets.push_back(newTicket);

    cout << "Ticket created successfully!\n";
}


void viewTickets(const vector<Ticket>& tickets) {
    if(tickets.empty()) {
        cout << "No tickets found.\n";
        return;
    }

    for(int i = 0; i < tickets.size(); i++) {
        cout << "\nTicket ID: " << tickets.at(i).id << endl;
        cout << "Name: " << tickets.at(i).name << endl;
        cout << "Issue: " << tickets.at(i).issue << endl;
        cout << "Category: " << tickets.at(i).category << endl;
        cout << "Status: " << tickets.at(i).status << endl;
        cout << "Priority: " << tickets.at(i).priority << endl;
    }
}


void searchTickets(const vector<Ticket>& tickets)   {
    bool found = false;
    int idSearch;
    cout << "Enter Ticket ID to search: ";
    cin >> idSearch;

    for(int i = 0; i < tickets.size(); i++) {
        if(idSearch == tickets.at(i).id)    {
            found = true;

            cout << "\nTicket Found!" << endl;
            cout << "Ticket ID: " << tickets.at(i).id << endl;
            cout << "Name: " << tickets.at(i).name << endl;
            cout << "Issue: " << tickets.at(i).issue << endl;
            cout << "Category: " << tickets.at(i).category << endl;
            cout << "Status: " << tickets.at(i).status << endl;
            cout << "Priority: " << tickets.at(i).priority << endl;

            break;
        }
    }
    if(!found)  {
        cout << "Ticket not found." << endl;
    }
}


void updateTicketStatus(vector<Ticket>& tickets)    {
    int idSearch;
    bool found = false;
    cout << "Enter Ticket ID to update: ";
    cin >> idSearch;

    for(int i = 0; i < tickets.size(); i++) {
        
        if(idSearch == tickets.at(i).id)    {
            cout << "Ticket found! Current Status: " << tickets.at(i).status << endl;
            found = true;
            cout << "Change Status: " << endl;
            int statusChange;
            cout << "1. Open" << endl;
            cout << "2. In Progress" << endl;
            cout << "3. Resolved" << endl;
            cout << "4. Closed" << endl;
            
            cout << "Enter choice: ";
            cin >> statusChange;
            
            switch (statusChange)   {
                case 1:
                    tickets.at(i).status = "Open";
                    cout << "Ticket status updated!" << endl;
                    break;
                case 2:
                    tickets.at(i).status = "In Progress";
                    cout << "Ticket status updated!" << endl;
                    break;
                case 3:
                    tickets.at(i).status = "Resolved";
                    cout << "Ticket status updated!" << endl;
                    break;
                case 4:
                    tickets.at(i).status = "Closed";
                    cout << "Ticket status updated!" << endl;
                    break;
                default:
                    cout << "Invalid option." << endl;
            }
            break;
        }
    }

    if(!found)  {
        cout << "Ticket not found." << endl;
    }
}


void saveTicket(const vector<Ticket>& tickets)  {
    ofstream myFile("tickets.txt");
    
    if(myFile.is_open())    {
        for(int i = 0; i < tickets.size(); i++) {
            myFile << tickets.at(i).id;
            myFile << '|';
            myFile << tickets.at(i).name;
            myFile << '|';
            myFile << tickets.at(i).issue;
            myFile << '|';
            myFile << tickets.at(i).category;
            myFile << '|';
            myFile << tickets.at(i).status;
            myFile << '|';
            myFile << tickets.at(i).priority << endl;
        }
        myFile.close();
        cout << "Tickets saved successfully!" << endl;
    }   else cout << "File not created!";
}


void loadTickets(vector<Ticket>& tickets) {
    ifstream myFile("tickets.txt");

    if (myFile.is_open()) {
        tickets.clear();

        string line;

        while (getline(myFile, line)) {
            Ticket tempTicket;
            string idText;

            stringstream ss(line);

            getline(ss, idText, '|');
            tempTicket.id = stoi(idText);

            getline(ss, tempTicket.name, '|');
            getline(ss, tempTicket.issue, '|');
            getline(ss, tempTicket.category, '|');
            getline(ss, tempTicket.status, '|');
            getline(ss, tempTicket.priority);

            tickets.push_back(tempTicket);
        }

        myFile.close();
        cout << "Tickets loaded successfully!" << endl;
    }
    else {
        cout << "File not found." << endl;
    }
}


void deleteTicket(vector<Ticket>& tickets)  {
    bool found = false;
    int deleteID;
    cout << "Enter Ticket ID of Ticket you want to delete: ";
    cin >> deleteID;

    for(int i = 0; i < tickets.size(); i++) {
        if(tickets.at(i).id == deleteID)    {
            tickets.erase(tickets.begin() + i);
            cout << "Ticket deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    if(!found) {
        cout << "Ticket not found." << endl;
    } 
}


int getNextTicketID(const vector<Ticket> & tickets) {
    int maxID = 0;

    for(int i = 0; i < tickets.size(); i++) {
        if(tickets.at(i).id > maxID)    {
            maxID = tickets.at(i).id;
        }
    }
    return maxID + 1;
}