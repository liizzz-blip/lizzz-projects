#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
using namespace std;

class Bank 
{
private:
    string username;
	int password;
    string username1;
	int password1;
    int total;
    struct person 
    {
        string name, email, ID;
        int contact, cash;
    } person[100];
    const string dataFileName = "data.txt";

public:
    Bank() 
    {
        total = 0;
    }
    void start();
    void signUp();
    void login();
    void choice();
    void Data();
    void show();
    void update();
    void search();
    void transactions();
    void del();
    void readDataFromFile();
    void writeDataToFile();
};

int main() 
{
    Bank b;
    b.start();
    b.signUp();
    b.login();
    return 0;
}

void Bank::start() 
{
    system("color 5E");
    char arr[] = {'~', '~', '~', ' ', 'B', 'A', 'N', 'K', ' ', 'M', 'A', 'N', 'A', 'G', 'E', 'M', 'E',
                'N', 'T', ' ', 'S', 'Y', 'S', 'T', 'E', 'M', ' ', '~', '~', '~'};
    cout << "\n\n\n\n\n\t\t\t";
    for(int i = 0 ; i < 30 ; i++)
    {
        cout << arr[i];
        Sleep(30);
    }
    Sleep(2000);
    system("CLS");

    readDataFromFile();
}

void Bank::signUp() 
{ 
    cout << "\n\n\t\t~~~ Bank Management System ~~~" << endl;
    cout << "\n\t\t SIGN UP" << endl;
    cout << "\t\t1.Enter Username: ";
    cin >> username;
    cout << "\t\t2.Enter Password: ";
    cin >> password;
    cout << "\t\tYour new id is creating please wait";
    for(int i = 0; i < 5; i++) 
    {
        cout << ".";
        Sleep(100);
    }
}

void Bank::login() 
{
    system("CLS");
    int attempts = 0;
    const int maxAttempts = 3; 

    while (attempts <= maxAttempts) 
    {
        cout << "\n\n\t\t\t\t^^^^^ WELCOME TO YOUR NEW ACCOUNT ^^^^^";
        cout << "\n\n\t\t LOGIN" << endl;
        cout << "\t\t1.Enter Username: ";
        cin >> username1;
        cout << "\t\t2.Enter Password: ";
        cin >> password1;

        if(username == username1 && password == password1)
        {
            system("CLS");
            while (true)
            {
                choice();
            }
        }
        else 
        {
            attempts++;
            if(username != username1 && password == password1) 
            {
                cout << "\t\t\aInvalid username. Access Denied !!!! " << endl ;
            }
            else if(username == username1 && password != password1) 
            {
                cout << "\t\t\aInvalid password. Access Denied !!!! " << endl ;
            }
            else 
            {
                cout << "\t\t\aInvalid username and password. Access Denied !!!!" << endl;
            }
            
            if (attempts <= maxAttempts)
            {
                cout << "\t\t\aPLEASE TRY AGAIN..... " << endl;
            }
            else 
            {
                cout << "\t\t\aToo many failed attempts. Access Denied permanently !!!!" << endl;
                break;
            }
            Sleep(3000); 
            system("CLS");
        }
    }
}

void Bank::choice() 
{
    char ch;
    cout << "\n\nPRESS..!!" << endl;
    cout << "1. Create new account" << endl;
    cout << "2. View customers list" << endl;
    cout << "3. Update information of existing account" << endl;
    cout << "4. Check the details of an existing account" << endl;
    cout << "5. For transactions" << endl;
    cout << "6. Remove existing account" << endl;
    cout << "7. Exit" << endl;
    ch = getch();
    system("CLS");
    switch(ch) 
    {
        case '1':
            Data();
            break;
        case '2':
            show();
            break;
        case '3':
            update();
            break;
        case '4':
            search();
            break;
        case '5':
            transactions();
            break;
        case '6':
            del();
            break;
        case '7':
            writeDataToFile();
            cout << "\n\tNICE TO MEET YOU " ;
            cout << "\n\t```GOOD BYE``` " ;
            cout << "\n\t\t___________________________________";
            cout << "\n\t\t|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|";
            cout << "\n\t\t| ~~~ Bank Management System ~~~  |" ;
            cout << "\n\t\t|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|";
            cout << "\n\t\t|_________________________________|";
            cout << "\n\t\t                                   ";
            cout << "\n\tExiting !!!! Please wait" << endl;
            for(int i = 0; i < 7; i++) {
                cout << ". " ;
                Sleep(200) ;
            }
            exit(0);
            break;
        default:
            cout << "\aInvalid input" << endl;
            break;
    }
}

void Bank::Data() 
{
    cout << "\nEnter data of person" << endl << endl;
    cout << "Enter Name: ";
    cin >> person[total].name;
    cout << "Enter ID: ";
    cin >> person[total].ID;
    cout << "Enter Contact: ";
    cin >> person[total].contact;
    cout << "Enter Email: ";
    cin >> person[total].email;
    cout << "Enter Cash in $ : ";
    cin >> person[total].cash;
    total++;
}

void Bank::show() 
{
    for(int i = 0; i < total; i++) 
    {
        cout << "\nData of person " << i + 1 << endl;
        cout << "Name: " << person[i].name << endl;
        cout << "ID: " << person[i].ID << endl;
        cout << "Contact: " << person[i].contact << endl;
        cout << "Email: " << person[i].email << endl;
        cout << "Cash: " << person[i].cash << endl;
    }
}

void Bank::update() 
{
    string id;
    cout << "Enter ID of person for update" << endl;
    cin >> id;
    for(int i = 0; i < total; i++) 
    {
        if(id == person[i].ID) 
        {
            cout << "\nPrevious data of person " << i + 1 << endl;
            cout << "Name: " << person[i].name << endl;
            cout << "ID: " << person[i].ID << endl;
            cout << "Contact: " << person[i].contact << endl;
            cout << "Email: " << person[i].email << endl;
            cout << "Cash: " << person[i].cash << endl;
            cout << "\nEnter new data" << endl << endl;
            cout << "Enter Name: ";
            cin >> person[i].name;
            cout << "Enter ID: ";
            cin >> person[i].ID;
            cout << "Enter Contact: ";
            cin >> person[i].contact;
            cout << "Enter Email: ";
            cin >> person[i].email;
            cout << "Enter Cash: ";
            cin >> person[i].cash;
            cout << "Your required data is updated" << endl;
            break;
        }
        if(i == total - 1) 
        {
            cout << "No such record found" << endl;
        }
    }
}

void Bank::search() 
{
    string id;
    cout << "Enter ID of person for check" << endl;
    cin >> id;
    for(int i = 0; i < total; i++) 
    {
        if(id == person[i].ID) 
        {
            cout << "\nData of person " << i + 1 << endl;
            cout << "Name: " << person[i].name << endl;
            cout << "ID: " << person[i].ID << endl;
            cout << "Contact: " << person[i].contact << endl;
            cout << "Email: " << person[i].email << endl;
            cout << "Cash: " << person[i].cash << endl;
            break;
        }
        if(i == total - 1) 
        {
            cout << "No such record found" << endl;
        }
    }
}

void Bank::transactions() 
{
    string id;
    char ch;
    int cash;
    cout << "Enter id of person which you want to transaction" << endl;
    cin >> id;
    for(int i = 0; i < total; i++) 
    {
        if(id == person[i].ID) 
        {
            cout << "Name: " << person[i].name << endl;
            cout << "ID: " << person[i].ID << endl;
            cout << "Contact: " << person[i].contact << endl;
            cout << "Email: " << person[i].email << endl;
            cout << "\nExisting Cash " << person[i].cash << endl;
            cout << "\nPress 1 to deposit cash" << endl;
            cout << "Press 2 to withdraw cash" << endl;
            ch = getch();
            switch(ch) 
            {
                case '1':
                    cout << "Enter cash which you want to deposit" << endl;
                    cin >> cash;
                    person[i].cash += cash;
                    cout << "New amount is " << person[i].cash << endl;
                    break;
                case '2':
                    back:
                    cout << "Enter cash which you want to withdraw" << endl;
                    cin >> cash;
                    if(cash > person[i].cash) 
                    {
                        cout << "Your existing cash is just " << person[i].cash << endl;
                        Sleep(3000);
                        goto back;
                    }
                    person[i].cash -= cash;
                    cout << "New amount is " << person[i].cash << endl;
                    break;
                default:
                    cout << "\aInvalid input" << endl;
                    break;
            }
            break;
        }
        if(i == total - 1) 
        {
            cout << "No such record found" << endl;
        }
    }
}

void Bank::del() 
{
    char ch;
    cout << "Press 1 to remove specific record" << endl;
    cout << "Press 2 to remove full record" << endl;
    ch = getch();
    switch(ch) 
    {
        case '1': 
        {
            string id;
            cout << "Enter ID of person for remove" << endl;
            cin >> id;
            for(int i = 0; i < total; i++) 
            {
                if(id == person[i].ID) 
                {
                    for(int j = i; j < total; j++) 
                    {
                        person[j].name = person[j + 1].name;
                        person[j].ID = person[j + 1].ID;
                        person[j].contact = person[j + 1].contact;
                        person[j].email = person[j + 1].email;
                        person[j].cash = person[j + 1].cash;
                    }
                    total--;
                    cout << "Your required data is deleted" << endl;
                    break;
                }
                if(i == total - 1) 
                {
                    cout << "No such record found" << endl;
                }
            }
            break;
        }
        case '2':
            total = 0;
            cout << "All records have been deleted." << endl;
            cout << "Thank you for using our bank management system! Goodbye!" << endl;
            break;
        default:
            cout << "\aInvalid input" << endl;
            break;
    }
}

void Bank::readDataFromFile() 
{
    ifstream inFile(dataFileName);
    if (!inFile) 
    {
        cout << "File not found. Starting with empty data." << endl;
        return;
    }

    total = 0;
    while (inFile >> person[total].name >> person[total].ID >> person[total].contact >> person[total].email >> person[total].cash) 
    {
        cout << "Reading: " << person[total].name << " " << person[total].ID << " " << person[total].contact << " " << person[total].email << " " << person[total].cash << endl; // Debug print
        total++;
    }

    inFile.close();
    cout << "Data successfully read from file." << endl; 
}


void Bank::writeDataToFile() 
{
    ofstream outFile(dataFileName);
    if (!outFile) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (int i = 0; i < total; i++) 
    {
        outFile << person[i].name << " " << person[i].ID << " " << person[i].contact << " " << person[i].email << " " << person[i].cash << endl;
        cout << "Writing: " << person[i].name << " " << person[i].ID << " " << person[i].contact << " " << person[i].email << " " << person[i].cash << endl; // Debug print
    }

    outFile.close();
    cout << "Data successfully written to file." << endl; 
}


