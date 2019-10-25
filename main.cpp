#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Date
{
    unsigned short int Year;
    unsigned short int Month;
    unsigned short int Day;
};

struct Student
{
    string Firstname;
    string Lastname;
    unsigned long long int ID;
    Date Birthday;
    float Grade;
};

struct Class
{
    string ClassName;
    float Awerage;
    unsigned short int Capacity;
    vector <Student> Data;
};

void SelectClass(string);
void AddClass(string);
void RemoveClass(string);
void AddStudent(string, Date, unsigned long long int, float);
void RemoveStudent(unsigned long long int);
void Search(unsigned long long int);
void Search(string, string);
void ShowClass(string);
void ShowAll();
void SortByName();
void SortByName(string);
void SortByID(string);
void SortByID();
void Save();
void Save(string);

vector <Class> Database;

void start (void);

string CurrentClass = "";


int main() {
    start();
    return 0;
}

void start (void)
{
    string input;
    while (true)
    {
        vector <string> command;
        cout << "Database>>";
        getline(cin, input);
        string temp = "";
        for (char ch : input)
        {
            if (ch != ' ')
            temp += ch;
            else
            {
                command.push_back(temp);
                temp = "";
            }
        }
        command.push_back(temp);
        if ( command[0] == "basu" && command[1] == "select" && command[2] == "class")
        SelectClass(command[3]);

        else if ( command[0] == "basu" && command[1] == "select" && command[2] == "none")
        CurrentClass = "";

        else if (command[0] == "basu" && command[1] == "add" && command[2] == "student")
        {
            string firstname, lastname, date;
            float grade;
            unsigned long long int id;
            cout << "enter firstname, lastname, birthday (yyyy/mm/dd), grade, id: " << endl;
            cin >> firstname >> lastname >> date >> grade >> id;
            vector <string> Datee;
            string temp = "";
            for (char ch : date)
            {
               if (ch != '/')
               temp += ch;
               else
               {
                Datee.push_back(temp);
                temp = "";
               }
            }
            Datee.push_back(temp);

            Date dateObj;
            dateObj.Year = stoi(Datee[0]);
            dateObj.Month = stoi(Datee[1]);
            dateObj.Day = stoi(Datee[2]);
            AddStudent(firstname + ' ' + lastname, dateObj, id, grade);
        }

        else if (command[0] == "basu" && command[1] == "remove" && command[2] == "student")
        RemoveStudent(stoll(command[3]));

        else if (command[0] == "basu" && command[1] == "add" && command[2] == "class")
        AddClass(command[3]);

        else if (command.size() == 3 && command[0] == "basu" && command[1] == "search")
        Search(stoll(command[2]));

        else if (command[0] == "basu" && command[1] == "search")
        {
           string firstname, lastname;
           Search(firstname , lastname);
        }
        else if (command[0] == "basu" && command[1] == "show" && command.size() == 2 )
        {
            if ( CurrentClass == "" )
            ShowAll();
            else
            {
                ShowClass( CurrentClass );
            }

        }

        else if (command[0] == "basu" && command[1] == "show")
        ShowClass(command[2]);

        else if (command[0] == "basu" && command[1] == "sort" && command[2] == "name")
        {
            if ( CurrentClass == "")
                for ( Class &i : Database)
                {
                    SortByName( i.ClassName);
                }
            else
                SortByName();
        }

        else if (command[0] == "basu" && command[1] == "sort" && command[2] == "id")
        {
            if ( CurrentClass == "")
                for ( Class &i : Database)
                {
                    SortByID( i.ClassName);
                }
            else
                SortByID();
        }

        else if (command[0] == "basu" && command[1] == "save")
        {
            if ( CurrentClass == "")
                for( Class &i : Database)
                {
                    Save( i.ClassName);
                }
            else
                Save();
        }

        else if (command[0] == "exit")
        exit(0);
    }
}