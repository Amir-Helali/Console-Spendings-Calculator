/*
Simple spendings calculator in C++ to excercise using all datatypes,
 operators, loops, conditional statements, arrays and functions with parameters
*/

/*
   1. Main menu with a switch case menu in which you can choose which day of the week
   you are going to be loading in spendings for
   2. The spendings have to be saved after the program is closed. This will be done by on choosing a day of the week
   from the menu, the program will check if there is a CSV file with the name of the day in the folder. If there is
   it will print the existing data to the console, if not it will create a CSV file and prompt you to write your savings in
   
*/
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <limits>

using namespace std;

//Function Declarations
void PrintMenu();
void GetUserInput();
bool doesDayCSVFileExist(const string& filename);
void CreateCSVFile(const string& filename);
bool isCSVFileEmpty(const string& filename);
void menuForCSVFileActions(string filename);
void editCSVFile(string& filename);
void printContetsOfCSVFile(string filename);

//<summery> Reshih da izpolzvam maisv za da moje pri printirane na menuto na consolata
//da moje da se iterira prez nego vmesto da se copy i pasteva edno i sushto
//</summery>
const int lengthOfDaysOfTheWeek = 6;

const string CSVFilesdirectory = "E:\\Programming\\C++\\Console-Spendings-Calculator\\csv\\";
string daysOfTheWeek[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
};

int main()
{
   PrintMenu();
}

//<summery> Prints the main menu on the console
//</summery>
void PrintMenu()
{
    int counter = 1;
    cout << "Welcome to spendings calculator!" << endl;
    
    for(int i = 0; i <= lengthOfDaysOfTheWeek; i++)
    {
        cout << counter << ". " << daysOfTheWeek[i];
        counter++;
        cout << endl;
    }
    GetUserInput();
    
}
void GetUserInput()
{
    int input;
 
    while(input < 1 || input > 7)
    {
        cout << "Choose a day with its number: ";
        cin >> input;
    }
    

    switch(input)
    {
        case 1:
        doesDayCSVFileExist("Monday");

        //TODO Take this logic out in a seperate function
        // This ef else statement underneath in a "IsFileEmpty()" function
        if(isCSVFileEmpty(daysOfTheWeek[0]))
        {
           menuForCSVFileActions(daysOfTheWeek[0]);
        }
        else
        {
            printContetsOfCSVFile(daysOfTheWeek[0]);
        }
        break;
        case 2:
        cout << "Tuesday\n";
        doesDayCSVFileExist("Tuesday");
        break;
        case 3:
        cout << "Wednesday";
        doesDayCSVFileExist("Wednesday");
        break;
        case 4:
        cout << "Thursday";
        doesDayCSVFileExist("Thursday");
        break;
        case 5:
        cout << "Friday";
        doesDayCSVFileExist("Friday");      
        break;
        case 6:
        cout << "Saturday";
        doesDayCSVFileExist("Saturday");
        break;
        case 7:
        cout << "Sunday";
        doesDayCSVFileExist("Sunday");
        break;
        default:
        cout << "No such day of the week!" << endl;
        break;
    }
}

void menuForCSVFileActions(string filename)
{
    system("cls");
    cout         << "No spendings for this day.\n";
    cout         << "Press E to start editing the file\n"
                 << "Press B to go back to the menu\n"
                 << "Press Q to quit the program\n" ;

        char ch = _getch();

        if (ch == 'e' || ch == 'E') 
        {
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            editCSVFile(filename);
        } 
        else if (ch == 'b' || ch == 'B') 
        {
            //TODO Figure out a way to clear the console before printing the menu again
            system("cls");
            PrintMenu();       
        }
        else if(ch == 'q' || ch == 'Q')
        {
            return;
        }
}
void editCSVFile(string& filename)
{  
    ofstream outputFile(CSVFilesdirectory + filename + ".csv");

     if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    cout << "Enter your spending data for the day. To save and quit, type ':wq'. To quit without saving, type ':q'." << endl;

    while (true) {
        string input;
        cout << "Enter spending (name, price): ";
        getline(cin, input);

        if (input == ":wq") {
            cout << "Saving and quitting." << endl;
            break;
        } else if (input == ":q") {
            cout << "Quitting without saving." << endl;
            break;
        } else {
            outputFile << input << endl;
        }
    }

    outputFile.close();
}

void printContetsOfCSVFile(string filename)
{
    ifstream inputFile(CSVFilesdirectory + filename + ".csv");

    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            std::cout << line << std::endl;
        }

        inputFile.close();
    } else {
        std::cerr << "Unable to open the file." << endl;
    }
}
//<summery> Proverqva dali sushtestvuva s fail s ime koeto sme dali
//Kato argument i ako ne go suzdava
//</summery>
bool doesDayCSVFileExist(const string& filename) {
   
    ifstream file(CSVFilesdirectory + filename + ".csv");

    if (file.good()) {
        
        file.close();
        return true;
    }
    else
    {
        CreateCSVFile(filename);
        file.close();
        return false;
    }
}

//<summery> Suzdava CSVov file s ime 
//passnato kato argument na funkciqta s nqkakav primeren input v CSVoviq file
//</summery>
void CreateCSVFile(const string& filename)
{
    ofstream newFile(CSVFilesdirectory + filename + ".csv");
    if (!newFile.is_open()) {
        cerr << "Error: Failed to create the file " << CSVFilesdirectory + filename + ".csv" << endl;
    }
    newFile.close();
    cout << filename <<" was created";
    cin.get();
    system("cls");
    PrintMenu();
}

bool isCSVFileEmpty(const string& filename)
{
    ifstream file(CSVFilesdirectory + filename + ".csv");

    if(file.is_open())
    {
        char character;

        if(file.get(character))
        {
             file.close();
             return false;
        }
        file.close();
        return true;
    }
    else
    {
        cout << "The file doesn't exist";
        CreateCSVFile(filename);
        return true;
    }
}



