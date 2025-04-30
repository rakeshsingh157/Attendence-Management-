#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <sys/stat.h> 
#include <direct.h>
#include <ctime>
#include <dirent.h>
#include <cstring>  
#include <sstream>  


using namespace std;

int mainpage();
int choice1();
int choice2();
string montostr(int mon);
string autocreatefile(string filename);
int studentname(string filename , string class_name);
int monthdays();

string global_file_path;
string path ;

// Check if folder exists
bool folderExists(const string& folderName) {
    struct stat info;
    if (stat(folderName.c_str(), &info) != 0) {
        return false;
    } else if (info.st_mode & S_IFDIR) {
        return true;
    } else {
        return false;
    }
}





int choice1()
 {
    string path;
    int select;
    cout << "Select Class :" << endl;
    DIR* dir;
    struct dirent* ent;
    dir = opendir("./classes");
    int i = 1;
    ofstream file("temp.txt", ios::out);
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                cout << i << ". " << ent->d_name << endl;
                file << ent->d_name << endl;
                i++;
            }
        }
        closedir(dir);
    } else {
        cout << "Maybe you forget to Create Classes" << endl;
        return 0;
    }
    cin >> select;
    string storef;
    file.close();
    ifstream File2("temp.txt", ios::in);
    string line;
    int lineNumber = 0;
    if (File2.is_open()) {
        while (getline(File2, line)) {
            lineNumber++;
            if (lineNumber == select) {
                storef = line;
                path = autocreatefile(storef);
                break;
            }
        }
        File2.close();
    } else {
        cout << "Something went wrong" << endl;
        return 0;
    }

    fstream file_check(path, ios::in | ios::out | ios::app);
    if (file_check.good()) {
        file_check.close();
    } else {
        cout << "Something went wrong" << endl;
        return 0;
    }

    time_t now = time(0);
    tm* t = localtime(&now);
    int days = t->tm_mday;
    int day = days - 1;
    int count = (day == 1) ? 30 : (day * 6) + 30;

    int totalLines = 0;
    ifstream fileread(path);
    if (fileread.is_open()) {
        while (getline(fileread, line)) {
            totalLines++;
        }
        fileread.close();
    }

    for (int i = 2; i <= totalLines; i++) {
        int lineToModify = i;
        int indexToInsert = count;
        ifstream file_check2(path);
        char newDat;

        // Show first 30 characters of the line
        ifstream showName(path);
        string tempLine;
        int current = 0;
        while (getline(showName, tempLine)) {
            current++;
            if (current == lineToModify) {
                cout << tempLine.substr(0, 30) << " : ";
                break;
            }
        }
        showName.close();

        // Get new data input from user
        cin >> newDat;
        char newData = toupper(newDat);
        int lineNumber = 0;

        if (file_check2.is_open()) {
            ofstream file_check3("temp.txt", ios::out);
            if (file_check3.is_open()) {
                while (getline(file_check2, line)) {
                    lineNumber++;
                    if (lineNumber == lineToModify) {
                        if (line.length() > indexToInsert) {
                            line[indexToInsert] = newData;  
                        } else {
                            line += string(indexToInsert - line.length(), ' ') + newData;  
                        }
                    }
                    file_check3 << line << endl;
                }
                file_check3.close();
            }
            file_check2.close();
            

        }
        remove(path.c_str());
        rename("temp.txt", path.c_str());
        
    }
    cout<<"Attendance updated successfully!"<<endl;
    mainpage();
    return 0;
}



int choice2() {
    string class_name;
    cout << "Enter Class Name: ";
    cin.ignore(); 
    getline(cin, class_name);
    
    if(class_name == "Y" || class_name == "y")
    {
        mainpage();
        
    }

    string folderName = "Classes";

    if (!folderExists(folderName)) {
        if (_mkdir(folderName.c_str()) == 0) {
            cout<<"Class created successfully!"<<endl;
          

        } else {
            cout << "Failed to create Class" << endl;
            mainpage();

           
        }
    } 

    folderName = "Classes/" + class_name;

    if (!folderExists(folderName)) {
        if (_mkdir(folderName.c_str()) == 0) {
            autocreatefile(class_name);
            studentname(folderName,class_name);
        } else {
            cout << "Failed to create Class" << endl;
            mainpage();
        }
    } 
    else{
        cout << "Class already exists!" << endl;
        autocreatefile(class_name);
        cout<<"Press Y for go to Main Screen"<<endl;
        choice2();

       }

    return 0;
}
string autocreatefile(string filename)
{ 
    time_t now = time(0);
    tm* t = localtime(&now);
    int month = t->tm_mon + 1;
    int year = t->tm_year + 1900;

    string year_str = to_string(year);
    int day = monthdays();  // You already have this

    string month_str = montostr(month);
    string file_path = "Classes/" + filename + "/" + month_str + year_str + ".txt";
    global_file_path = file_path;

    ifstream check_exist(file_path);
    if (!check_exist.good()) {
        ofstream file_check(file_path);

        // First Line: Day numbers with spacing
        for (int i = 1; i <= day; i++) { 
            if (i == 1)
                file_check << string(30, ' ') << i;
            else if (i >= 10)
                file_check << string(4, ' ') << i;
            else
                file_check << string(5, ' ') << i;
        }
        file_check << "\n";

        // Construct previous month file path
        string prev_month_str;
        string prev_year_str = year_str;

        if (month == 1) {
            prev_month_str = "Dec ";
            prev_year_str = to_string(year - 1);
        } else {
            prev_month_str = montostr(month - 1);
        }

        string prev_file = "Classes/" + filename + "/" + prev_month_str + prev_year_str + ".txt";

        // Try to open previous month file
        ifstream file_copy(prev_file);
        if (!file_copy.is_open()) {
            cout << "Maybe you forget to create class" << endl;
        } else {
            string line;
            int currentLine = 0;
            while (getline(file_copy, line)) {
                currentLine++;
                if (currentLine >= 2) {
                    if (line.length() > 30)
                        line = line.substr(0, 30);
                    file_check << line << endl;
                }
            }
            file_copy.close();
        }

        file_check.close();
        cout << "File created because it did not exist." << endl;
    }

    return file_path;
}



string montostr(int mon)
{
    string month_str;
    switch (mon) {
        case 1: month_str = "Jan "; break;
        case 2: month_str = "Feb "; break;
        case 3: month_str = "Mar "; break;
        case 4: month_str = "Apr "; break;
        case 5: month_str = "May "; break;
        case 6: month_str = "Jun "; break;
        case 7: month_str = "Jul "; break;
        case 8: month_str = "Aug "; break;
        case 9: month_str = "Sep "; break;
        case 10: month_str = "Oct "; break;
        case 11: month_str = "Nov "; break;
        case 12: month_str = "Dec "; break;
        default: break; 
    }
    return month_str;
}


int monthdays(){
    time_t now = time(0);
    tm* t = localtime(&now);
    int month=  t->tm_mon + 1;
    int year =  t->tm_year + 1900 ;
    int days = 0;
    switch (month) {
        case 1: days = 31; break;
        case 2: days = (year % 4 == 0) ? 29 : 28; break; 
        case 3: days = 31; break;
        case 4: days = 30; break;
        case 5: days = 31; break;
        case 6: days = 30; break;
        case 7: days = 31; break;
        case 8: days = 31; break;
        case 9: days = 30; break;
        case 10: days = 31; break;
        case 11: days = 30; break;
        case 12: days = 31; break;
        default: break; 
    }
    return days;
}


int studentname(string filename , string class_name)
{
    string student_name;
    string ch;
    int day = monthdays();
    
    ofstream file1(global_file_path, ios::app);
    if (!file1) {
        cout << "Error opening file!" << endl;
        return 1;
    }
   
    int i = 1;
    for(int i = 1; i <= day; i++)
    { 
        if(i == 1){
            ch = string(30, ' ') + to_string(i);
        }
        else if(i>=10){
            ch = string(4, ' ') + to_string(i);
        }
        else{
            ch = string(5, ' ') + to_string(i);
        }
        file1<<ch;
    }
    file1<<"\n";
    cout<<"\nEnter Student Name (or type 'exit' to finish): \n";

    cout<<"\n";
    while(true)
    {
        cout<<"Enter Student "<<i<<": ";
        getline(cin, student_name);

        if (student_name == "exit") 
        {
            mainpage();
            break;
        }

        file1<<i<<". "<<student_name<<endl;
        i++;
    }
    
}




int mainpage(){
    cout << "Welcome to Attendance Management System" << endl;
    cout << "Please Enter Choice :" << endl;
    cout << "1. Take Attendance" << endl;
    cout << "2. Add Class" << endl;
    cout << "3. Exit" << endl;

    
    int choice = 0;
    cin >> choice;

    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Invalid input! Please enter a number.\n" << endl;
        return mainpage(); 
    }
    switch (choice) 
    {
        case 1:
            choice1();
            break;
        case 2:
            choice2();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
    }



int main() 
{
    
    mainpage();


    return 0;
}
