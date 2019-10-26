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



void AddClass(string fileName)
{
    const char* fName = fileName.c_str();
    ifstream input;
    input.open(fName, ios::in);
    Class newClass;
    getline(input, newClass.ClassName);
    input >> newClass.Capacity;
    for (size_t i = 0; i < newClass.Capacity; i++)
    {
        string date;
        Student newStudent;
        input >> newStudent.Firstname;
        input >> newStudent.Lastname;
        input >> date;
        string temp[3];
        size_t counter = 0;
        for(auto j : date)
        {
            if (j != '/')
                temp[counter] += j;
            else
                counter++;
        }
        newStudent.Birthday.Year = stoi(temp[0]);
        newStudent.Birthday.Month = stoi(temp[1]);
        newStudent.Birthday.Day = stoi(temp[2]);
        input >> newStudent.Grade;
        input >> newStudent.ID;
        newClass.Data.push_back(newStudent);
    }
    Database.push_back(newClass);
    input.close();
}
void RemoveStudent(unsigned long long int id)
{
    if ( CurrentClass == "")
    {
        cout << "slect nakardi" << endl;
        return;
    }
    for(Class &i : Database)
    {
        if (i.ClassName == CurrentClass)
        {
            for (size_t j = 0; j < i.Data.size(); j++)
            {
                if(i.Data.at(j).ID == id)
                {
                    i.Data.erase(i.Data.begin() + j);
                    i.Capacity--;
                }
            }
        }
    }
}
void Search (unsigned long long id)
{
     if ( CurrentClass == "")
    {
        cout << "slect nakardi" << endl;
        return;
    }
       for(Class &i : Database)
    {
        if (i.ClassName == CurrentClass)
        {
            for (size_t j = 0; j < i.Data.size(); j++)
            {
                if(i.Data.at(j).ID == id)
                {
                    cout << i.Data.at(j).ID << endl;
                    cout << i.Data.at(j).Firstname << endl;
                    cout << i.Data.at(j).Lastname << endl;
                    cout << i.Data.at(j).Grade << endl;
                    cout << i.Data.at(j).Birthday.Year << "/";
                    cout << i.Data.at(j).Birthday.Month << "/";
                    cout << i.Data.at(j).Birthday.Day << endl;
                }
            }
        }
    }
}
void SelectClass (string classname)
{
    bool classfound = false;
    for ( Class &i : Database)
    {
        if ( i.ClassName == classname)
        {
            CurrentClass = classname;
            classfound = true;
            break;
        }
    }
    if ( classfound == false)
    cout << "class not found" <<endl;
}
void AddStudent(string fullname , Date dataObj, unsigned long long int id, float grade)
{
        if ( CurrentClass == "")
        {
            cout << "slect nakardi" << endl;
            return;
        }
        Student newStudent;
        string temp[2];
        size_t counter = 0;
        for(auto j : fullname)
        {
            if (j != ' ')
                temp[counter] += j;
            else
                counter++;
        }
        newStudent.Firstname = temp[0];
        newStudent.Lastname = temp[1];
        newStudent.Grade = grade;
        newStudent.ID = id;
        newStudent.Birthday = dataObj;
        for (Class &i : Database)
        {
            if ( i.ClassName == CurrentClass)
            {
                i.Data.push_back(newStudent);
                i.Capacity++;
            }
        }
}
void RemoveClass(string CurrentClass)
{
     if ( CurrentClass == "")
    {
        cout << "slect nakardi" << endl;
        return;
    }
    for ( size_t i = 0 ; i < Database.size(); i++)
    {
        if ( Database.at(i).ClassName == CurrentClass)
        {
            Database.erase(Database.begin() + i);
        }
    }
}
void Search(string firstname, string lastname)
{
    if ( CurrentClass == "")
    {
        cout << "slect nakardi" << endl;
        return;
    }

    for(Class &i : Database)
    {
        if (i.ClassName == CurrentClass)
        {
            for (size_t j = 0; j < i.Data.size(); j++)
            {
                if(i.Data.at(j).Firstname == firstname && i.Data.at(j).Lastname == lastname)
                {
                    cout << i.Data.at(j).ID << endl;
                    cout << i.Data.at(j).Firstname << endl;
                    cout << i.Data.at(j).Lastname << endl;
                    cout << i.Data.at(j).Grade << endl;
                    cout << i.Data.at(j).Birthday.Year << "/";
                    cout << i.Data.at(j).Birthday.Month << "/";
                    cout << i.Data.at(j).Birthday.Day << endl;
                }
            }
        }
    }
}
void ShowClass( string CurrentClass )
{
    for ( Class &i : Database)
    {
        if ( i.ClassName == CurrentClass )
        {
            cout << i.ClassName <<endl;
            cout << i.Capacity << endl;
            for ( size_t j = 0 ; j < i.Data.size() ; j++)
            {
                cout << i.Data.at(j).ID << " " ;
                cout << i.Data.at(j).Firstname << " " ;
                cout << i.Data.at(j).Lastname << " " ;
                cout << i.Data.at(j).Grade << " " ;
                cout << i.Data.at(j).Birthday.Year << "/";
                cout << i.Data.at(j).Birthday.Month << "/";
                cout << i.Data.at(j).Birthday.Day << endl;
            }

        }
    }
}
void ShowAll()
{
    for ( Class &i : Database)
    {
        cout << i.ClassName << endl;
        cout << i.Capacity << endl;
        for ( size_t j =0; j < i.Data.size(); j++)
        {
            cout << i.Data.at(j).ID << " " ;
            cout << i.Data.at(j).Firstname << " " ;
            cout << i.Data.at(j).Lastname << " " ;
            cout << i.Data.at(j).Grade << " " ;
            cout << i.Data.at(j).Birthday.Year << "/";
            cout << i.Data.at(j).Birthday.Month << "/";
            cout << i.Data.at(j).Birthday.Day << endl;
        }
    }
}
void SortByID(string classname )
{
    for ( Class &i : Database)
    {
        if ( i.ClassName == classname)
        {
            for ( size_t j = i.Data.size() - 1; j > 0 ; j--)
            {
                for ( int k = 0 ; k < j ; k++)
                {
                    if ( i.Data.at(k).ID > i.Data.at(k+1).ID)
                    swap ( i.Data.at(k).ID , i.Data.at(k+1).ID);
                }
            }
        }
    }
}
void SortByID()
{
    SortByID(CurrentClass);
}
void SortByName(string classname)
{
    for ( Class &i : Database)
    {
        if ( i.ClassName == classname)
        {
            for ( size_t j = i.Data.size() - 1; j > 0; j--)
            {
                for ( int k = 0; k < j; k++)
                {
                    if ( strcmp(i.Data.at(k).Lastname.c_str(), i.Data.at(k+1).Lastname.c_str()) == 1)
                    swap ( i.Data.at(k).Lastname, i.Data.at(k+1).Lastname);
                }
            }

        }
    }



}
void SortByName()
{
    SortByName(CurrentClass);
}