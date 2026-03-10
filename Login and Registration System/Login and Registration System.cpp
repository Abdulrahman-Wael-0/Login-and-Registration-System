#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Welcome {
public:
    void welecometext() {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "+-------------------------------------------+ " << endl;
        cout << "|     Welcome to the Login and Register     |" << endl;
        cout << "+-------------------------------------------+ " << endl;
    }
};

class Login {
public:

    string name_1, password_1;
    bool found = false;

    void login_Name() {
        system("cls");

        found = false; 

        SetConsoleTextAttribute(hConsole, 13);
        cout << "\n=========== LOGIN ===========\n\n";

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Enter your name: ";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> name_1;   

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Enter your password: ";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> password_1; 

        if (cin.fail() || password_1.length() < 8) {
            cin.clear();
            cin.ignore(1000, '\n');
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 250);
            cout << "\nInvalid input. Password must be at least 8 characters.\n";
            login_Name();
            return;
        }

        ifstream infile("users.txt");
        string user, pass;
        while (infile >> user >> pass) {
            if (user == name_1 && pass == password_1) {
                found = true;
                break;
            }
        }
        infile.close();

        if (found) {
            SetConsoleTextAttribute(hConsole, 10);
            Beep(1000, 200);
            cout << "\nLogin successful!\n";
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 500);
            cout << "\nLogin failed! Incorrect username or password.\n";
        }
    }

    void wronglog() const {
        SetConsoleTextAttribute(hConsole, 13);
        cout << "\n=========== LOGIN ===========\n\n";

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Your name is : " << name_1 << endl;

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Your password is : " << password_1 << endl;
    }
};



class Register {
public:

    string name, password;
    bool duplicate = false;

    void registername() {
        system("cls");

        SetConsoleTextAttribute(hConsole, 13);
        cout << "\n========== REGISTER ==========\n\n";

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Enter your name: ";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> name;

        ifstream infile("users.txt");
        string user, pass;
        while (infile >> user >> pass) {
            if (user == name) {
                duplicate = true;
                break;
            }
        }
        infile.close();

        if (duplicate) {
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 500);
            cout << "\nUsername already exists. Please choose another name.\n";
            registername();
            return;
        }

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Enter your password: ";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> password;

        if (cin.fail() || password.length() < 8) {
            cin.clear();
            cin.ignore(1000, '\n');
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 500); 
            cout << "\nPassword must be at least 8 characters.\n";
            registername();
            return;
        }

        ofstream outfile("users.txt", ios::app);
        outfile << name << " " << password << endl;
        outfile.close();

        SetConsoleTextAttribute(hConsole, 10);
        Beep(1000, 200); 
        cout << "\nRegistration successful!\n";
    }
    void wrongreg() {

        SetConsoleTextAttribute(hConsole, 13);
        cout << "\n========== REGISTER ==========\n\n";
        
        SetConsoleTextAttribute(hConsole, 14);
        cout << "Your name is : " << name << endl;

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Your password is : " << password << endl;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "\nRegistration successful!\n";
    }
};


class Aboutus : public  Welcome {
public:
    void ABOUTUS() {
        system("cls");
        SetConsoleTextAttribute(hConsole, 3);
        welecometext();

        SetConsoleTextAttribute(hConsole, 9);
        cout << "This GPA Calculator is developed by ";
        SetConsoleTextAttribute(hConsole, 10);
        cout << "[ABDELRAHMAN WAEL].\n";

        SetConsoleTextAttribute(hConsole, 9);
        cout << "This is a  Login and Register System.\n";
        cout << "This project represents the Second c++ program that ";
        SetConsoleTextAttribute(hConsole, 13);
        cout << "@Abdelrahman Wael";
        SetConsoleTextAttribute(hConsole, 9);
        cout << " made.\n";
    }
};


class Exit0 {
public:
    void Exit() {
        system("cls");
        SetConsoleTextAttribute(hConsole, 12);

        cout << R"(
      ******       ******
    **********   **********
   ************ ************
  ****************************
  ****************************
   **************************
    **********************
      ******************
        **************
          **********
            ******
              ***
               *
)" << endl;

        SetConsoleTextAttribute(hConsole, 10);
        Beep(1000, 400); 
        cout << "   Thank you for using my application\n";

        SetConsoleTextAttribute(hConsole, 0);
        exit(0);
    }
};


class Interface : public Login, public Register, public Aboutus, public Exit0  {
public:
        int choice = 0;
        int currentpage = 0;

    void askReturnOrExit() {
        int back;
        
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\n+-------------------------------------------+\n";
        cout << "[1] Return to main menu.\n";
        cout << "[2] Exit the application.\n";
        cout << "+-------------------------------------------+\n";
        cout << "Enter your choice: ";
        cin >> back;

        if (cin.fail() || (back != 1 && back != 2)) {
            cin.clear();
            cin.ignore(1000, '\n');
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 250);
            cout << "Invalid input. Try again.\n";
            Sleep(1500);
            if (currentpage == 1) {
                system("cls");
                wronglog();
                askReturnOrExit();
            }
            else if (currentpage == 2) {
                system("cls");
                wrongreg();
                cout << endl;
                askReturnOrExit();
            }
            else if (currentpage == 3) {
                system("cls");
                ABOUTUS();
                askReturnOrExit();
            }
            else { askReturnOrExit(); }   
        }
        else if (back == 1) {
            system("cls");
            interfacer();
        }
        else {
            Exit();
        }
    }

    void interfacer() {
        int choice = 0;
        
        system("cls");

        SetConsoleTextAttribute(hConsole, 3);
        cout << "+-------------------------------------------+\n";
        cout << "|     Welcome to the Login and Register     |\n";
        cout << "+-------------------------------------------+\n";


        
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\nMENU:\n";
        cout << "1-Login         \n";
        cout << "2-Register      \n";
        cout << "3-About us      \n";
        cout << "4-Exit          \n";
        cout << "+-------------------------------------------+\n";

        SetConsoleTextAttribute(hConsole, 7);
        cout << "Please Enter a number: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            SetConsoleTextAttribute(hConsole, 12);
            Beep(600, 250);
            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            system("pause");
            interfacer();
            return;
        }

        switch (choice) {
        case 1:
            currentpage = 1;
            login_Name();
            askReturnOrExit();

            break;
        case 2:
            currentpage = 2;
            registername();
            askReturnOrExit();
            break;
        case 3:
            currentpage = 3;
            ABOUTUS();
            askReturnOrExit();
            break;
        case 4:
            Exit();
            break;
        }
    }
};


int main() {
    Interface abc;
    abc.interfacer();
    return 0;
}
