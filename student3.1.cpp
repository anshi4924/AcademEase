#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <conio.h>
using namespace std;

void registr();
void login();
void forgot();
void signup();
void insert();
void search();
void update();
void del();
void show();
void main_menu();

int i = 0;

struct Student {
    int id;
    float marks, per;
    string name, grade;
    static int uniqueIds[25];
} 
s[25];
int Student::uniqueIds[25] = {0};

int main() {
    signup();
    login();
    main_menu();
    return 0;
}

void signup() {
    int choice;
    cout << "\n\n\t\t\t*** STUDENT MANAGEMENT SYSTEM ***" << endl;
    cout << "\n\n MENU: " << endl;
    cout << "\n\n 1. LOGIN" << endl;
    cout << "\n\n 2. REGISTER" << endl;
    cout << "\n\n 3. FORGOT PASSWORD" << endl;
    cout << "\n\n 4. EXIT" << endl;
    cout << "\n\n ENTER YOUR CHOICE -> ";
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            registr();
            break;
        case 3:
            forgot();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid choice, please try again." << endl;
            signup();
    }
}

void login() {
    int count = 0;
    string user, pass, u, p;
    system("cls");
    cout << "Please enter the following details: " << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    ifstream input("users.txt");
    while (input >> u >> p) {
        if (u == user && p == pass) {
            count = 1;
            break;
        }
    }
    input.close();
    if (count == 1) {
        cout << "Hello " << user << "\n <Login successful>\n";
        cin.get();
        system("pause");
        main_menu();
    } else {
        cout << "\nLOGIN ERROR\nPlease check your username and password." << endl;
        cin.get();
        system("pause");
        signup();
    }
}


void registr() {
    std::string reguser, regpass;
    system("cls");
    std::cout << "Please enter the following details: " << std::endl;
    bool validUsername = false;
    while (!validUsername) {
        std::cout << "Enter the username (only alphabets and numerics without spaces): ";
        std::cin.ignore();
        getline(cin,reguser);
        bool hasSpace = false;
        for (size_t i = 0; i < reguser.length(); i++) {
            if (!isalnum(reguser[i])) {
                std::cout << "Please use only alphabets and numerics without spaces for the username." << std::endl;
                hasSpace = true;
                break;
            }
        }
        if (!hasSpace) {
            validUsername = true;
        }
    }
    cout << "Enter the password: ";
    cin >> regpass;
    ofstream reg("users.txt", ios::app);
    reg << reguser << " " << regpass << endl;
    reg.close();
    cout << "Registration successful." << endl;
    system("pause");
    signup();
}

void forgot() {
    int ch;
    system("cls");
    cout << "1. Search your ID by username." << endl;
    cout << "2. Main menu." << endl;
    cin >> ch;
    switch (ch) {
        case 1:
        	{
            int count = 0;
            string searchuser, su, sp;
            cout << "\nEnter your username: ";
            cin >> searchuser;
            ifstream searchu("users.txt");
            while (searchu >> su >> sp) {
                if (su == searchuser) {
                    count = 1;
                }
            }
            searchu.close();
            if (count == 1) {
                cout << "\nAccount Found" << endl;
                cout << "\nYour password is: " << sp << endl;
                system("pause");
                signup();
            } else {
                cout << "\nUser ID not found." << endl;
                system("pause");
                signup();
            }
        }
            break;
        case 2:
            signup(); // No need for break
            break; // Break here
        default:
            cout << "Invalid choice." << endl;
            system("pause");
            signup();
    }
}




void insert() {
    system("cls");
    int newId;
    cout << "\n\n\t\t\t *** INSERT RECORD ***";
    bool isUnique = false;
    while (!isUnique) {
        isUnique = true;
        cout << "\n\n Enter Student Id: ";
        cin >> newId;
        for (int j = 0; j < i; j++) {
            if (s[j].id == newId || Student::uniqueIds[j] == newId) {
                isUnique = false;
                cout << "\n\n ***Cannot enter a duplicate Id. Please enter a Unique Id ***\n\n";
                break;
            }
        }
    }
    s[i].id = newId;
    Student::uniqueIds[i] = newId;
    cout << "\n\n Enter Student Name: ";
    cin.ignore();
    getline(cin, s[i].name);
    cout << "\n\n Enter Student Marks: ";
    cin >> s[i].marks;
    s[i].per = (s[i].marks / 100) * 100;
    if (s[i].per >= 85)
        s[i].grade = "A+";
    else if (s[i].per >= 75)
        s[i].grade = "A";
    else if (s[i].per >= 65)
        s[i].grade = "B+";
    else if (s[i].per >= 55)
        s[i].grade = "B";
    else if (s[i].per >= 45)
        s[i].grade = "C";
    else if (s[i].per >= 40)
        s[i].grade = "D";
    else if (s[i].per >= 33)
        s[i].grade = "E";
    else
        s[i].grade = "F";

    ofstream file("students.txt", ios::app);
    file << s[i].id << " " << s[i].name << " " << s[i].marks << " " << s[i].per << " " << s[i].grade << endl;
    file.close();
    i++;
    cout << "\n\n *** Record Inserted Successfully ***\n\n";
    system("pause");
}



void search() {
    system("cls");
    cout << "\n\n\t\t\t *** SEARCH RECORD ***";
    if (i == 0)
        cout << "\n\n *** No Record Found ***";
    else {
        int id, found = 0;
        cout << "\n\n Enter Student Id: ";
        cin >> id;
        for (int a = 0; a < i; a++) {
            if (id == s[a].id) {
                cout << "\n\n Name: " << s[a].name;
                cout << "\n\n Marks: " << s[a].marks;
                cout << "\n\n Percentage: " << s[a].per << "%";
                cout << "\n\n Grade: " << s[a].grade <<"\n\n";
                found++;
            }
        }
        if (found == 0)
            cout << "\n\n *** Student ID Not Found ***\n\n";
    }
    system("pause");
}

void update() {
    system("cls");
    cout << "\n\n\t\t\t *** UPDATE RECORD ***";
    if (i == 0)
        cout << "\n\n *** No Record Found ***\n\n";
    else {
        int id, found = 0;
        cout << "\n\n Enter Student Id: ";
        cin >> id;
        for (int a = 0; a < i; a++) {
            if (id == s[a].id) {
                cout << "\n\n Enter Student Name: ";
                cin.ignore();
                getline(cin,s[a].name);
                cout << "\n\n Enter Student Marks: ";
                cin >> s[a].marks;
                s[a].per = s[a].marks / 100 * 100;
                if (s[a].per >= 85)
                    s[a].grade = "A+";
                else if (s[a].per >= 75)
                    s[a].grade = "A";
                else if (s[a].per >= 65)
                    s[a].grade = "B+";
				else if (s[a].per >= 55)
                    s[a].grade = "B";
                else if (s[a].per >= 45)
                    s[a].grade = "C";
                else if (s[a].per >= 40)
                    s[a].grade = "D";
                else if (s[a].per >= 33)
                    s[a].grade = "E";
                else
                    s[a].grade = "F";
                cout << "\n\n *** RECORD UPDATED SUCCESSFULLY ***\n\n";
                found++;
            }
        }
        if (found == 0)
            cout << "\n\n *** Student ID Not Found ***\n\n";
    }
    system("pause");
}

void del() {
    system("cls");
    cout << "\n\n\t\t\t *** DELETE RECORD ***";
    if (i == 0)
        cout << "\n\n *** No Record Found ***\n\n";
    else {
        int id, found = 0;
        cout << "\n\n Enter Student Id: ";
        cin >> id;
        for (int a = 0; a < i; a++) {
            if (id == s[a].id) {
                for (int m = a; m < i - 1; m++) {
                    s[m].id = s[m + 1].id;
                    s[m].name = s[m + 1].name;
                    s[m].marks = s[m + 1].marks;
                    s[m].per = s[m + 1].per;
                    s[m].grade = s[m + 1].grade;
                }
                cout << "\n\n *** Record Deleted Successfully ***\n\n";
                found++;
                i--;
                break;
            }
        }
        if (found == 0)
            cout << "\n\n *** Student ID Not Found ***\n\n";
    }
    system("pause");
}

void show() {
    system("cls");
    cout << "\n\n\t\t\t *** SHOW RECORD ***";
    if (i == 0)
        cout << "\n\n *** No Record Found ***\n\n";
    else {
        for (int a = 0; a < i; a++) {
            cout << "\n\n Student Id: " << s[a].id;
            cout << "\n\n Name: " << s[a].name;
            cout << "\n\n Marks: " << s[a].marks;
            cout << "\n\n Percentage: " << s[a].per << "%";
            cout << "\n\n Grade: " << s[a].grade;
            cout << "\n\n *****************************\n\n";
        }
    }
    system("pause");
}
void main_menu() {
    p:
    system("cls");
    int choice;
    cout<<"\n\n\t\t\t*** STUDENT MANAGMENT SYSTEM ***"<<endl;
    cout<<"\n\n 1. INSERT RECORD"<<endl;
    cout<<"\n\n 2. SEARCH RECORD"<<endl;
    cout<<"\n\n 3. UPDATE RECORD"<<endl;
    cout<<"\n\n 4. DELETE RECORD"<<endl;
    cout<<"\n\n 5. SHOW RECORD"<<endl;
    cout<<"\n\n 6. EXIT"<<endl;
    cout<<"\n\n ENTER YOUR CHOICE -> "<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            insert();
            break;
        case 2:
            search();
            break;
        case 3:
            update();
            break;
        case 4:
            del();
            break;
        case 5:
            show();
            break;
        case 6:
            exit(0);
        default:
        cout<<"\n\n**** invalid choice****\n\n";
    }
    goto p;
    getch();
}


