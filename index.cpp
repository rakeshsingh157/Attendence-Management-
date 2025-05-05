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
#include <vector>


using namespace std;
//all the function name is here
int mainpage();
int choice1();
int choice2();
string montostr(int mon);
string autocreatefile(string filename);
int studentname(string filename , string class_name);
int monthdays();
int checkstudent(string path);
string choice3();
string choice4();
string choice5();
string addname();
string removeName();
int removestd(string path);
int checkstudent(string path);

string global_file_path; // i am storing some path while code running
string path; // declare to use multiple time

// Check if folder exists
// this create for check if any of folder is exist or not  
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
       cout<<"\nMaybe you forget to create Class";
        mainpage();
        
    }

    cout<<endl<<endl<< "Select Class :  ";
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
        cout <<endl <<"Something went wrong" << endl<<endl;
        mainpage();
    }

    fstream file_check(path, ios::in | ios::out | ios::app);
    if (file_check.good()) {
        file_check.close();
    } else {
        cout <<endl<< "Something went wrong" <<endl<< endl;
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
    cout<<"\n\nAttendance updated successfully!\n"<<endl;
    mainpage();
    return 0;
}



int choice2() {
    string class_name;
    cout << "\n\nEnter Class Name: ";
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
        cout << "\n\nClass already exists!" << endl;
        autocreatefile(class_name);
        choice2();

       }

    return 0;
}
string choice3()
{
    string path;
    int select;
    cout<<"\n\n";

    // Step 1: List all folders inside ./classes
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
        cout << "\n\nUnable to open './classes' directory." << endl;
        mainpage();
        return "";
    }

    file.close();

    // Step 2: User selects a class folder
    cout << "\n\n\nSelect Class :  ";
    cin >> select;

    string storef;
    ifstream File2("temp.txt", ios::in);
    string line;
    int lineNumber = 0;

    if (File2.is_open()) {
        while (getline(File2, line)) {
            lineNumber++;
            if (lineNumber == select) {
                storef = line;
                break;
            }
        }
        File2.close();
    } else {
        cout << "\n\nError opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Step 3: List files inside ./classes/storef
    string folderPath = "./classes/" + storef;
    DIR* subDir = opendir(folderPath.c_str());

    if (subDir == NULL) {
        cout << "\n\nUnable to open folder: " << folderPath << endl;
        mainpage();
        return "";
    }

    ofstream fileList("temp.txt", ios::out);  // Overwrite again with files
    i = 1;

    cout << "\nSelect month & year" << ":\n\n\n";

    while ((ent = readdir(subDir)) != NULL) {
        if (ent->d_type == DT_REG) { // Only list files
            cout << i << ". " << ent->d_name << endl;
            fileList << ent->d_name << endl;
            i++;
        }
    }

    fileList.close();
    closedir(subDir);

    // Step 4: User selects a file
    cout << "\n\nSelect Month : ";
    cin >> select;

    string filename;
    ifstream File3("temp.txt", ios::in);
    lineNumber = 0;

    if (File3.is_open()) {
        while (getline(File3, line)) {
            lineNumber++;
            if (lineNumber == select) {
                filename = line;
                break;
            }
        }
        File3.close();
    } else {
        cout << "\n\nError opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Final path to selected file
    path = folderPath + "/" + filename;
   


// Print file content to terminal
ifstream selectedFile(path);
if (selectedFile.is_open()) {
    string fileLine;
    cout << "\n--- ATTENDENCE ---\n";
    while (getline(selectedFile, fileLine)) {
        cout << fileLine << endl;
    }
    selectedFile.close();
    mainpage();
} else {
    cout << "\n\nError opening the selected file." << endl;
}



    

    return path;
}




string choice4()
{
    string path;
    int select;
    cout<<endl;

    // Step 1: List all folders inside ./classes
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
        cout << "\n\nUnable to open './classes' directory." << endl;
        mainpage();
        return "";
    }

    file.close();

    // Step 2: User selects a class folder
    cout << "\nSelect Class :  ";
    cin >> select;

    string storef;
    ifstream File2("temp.txt", ios::in);
    string line;
    int lineNumber = 0;

    if (File2.is_open()) {
        while (getline(File2, line)) {
            lineNumber++;
            if (lineNumber == select) {
                storef = line;
                break;
            }
        }
        File2.close();
    } else {
        cout << "\n\nError opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Step 3: List files inside ./classes/storef
    string folderPath = "./classes/" + storef;
    DIR* subDir = opendir(folderPath.c_str());

    if (subDir == NULL) {
        cout << "\n\nUnable to open folder: " << folderPath << endl;
        mainpage();
        return "";
    }

    ofstream fileList("temp.txt", ios::out);  // Overwrite again with files
    i = 1;

    cout << "\n\nMonths & Years: \n\n ";

    while ((ent = readdir(subDir)) != NULL) {
        if (ent->d_type == DT_REG) { // Only list files
            cout << i << ". " << ent->d_name << endl;
            fileList << ent->d_name << endl;
            i++;
        }
    }

    fileList.close();
    closedir(subDir);

    // Step 4: User selects a file
    cout << "\n\nSelect Month : ";
    cin >> select;

    string filename;
    ifstream File3("temp.txt", ios::in);
    lineNumber = 0;

    if (File3.is_open()) {
        while (getline(File3, line)) {
            lineNumber++;
            if (lineNumber == select) {
                filename = line;
                break;
            }
        }
        File3.close();
    } else {
        cout << "\n\nError opening temp.txt" << endl;
        mainpage();
        
    }

    // Final path to selected file
    path = folderPath + "/" + filename;
    
    int check = checkstudent(path); 

    
    
    
}



int checkstudent(string path){
    ifstream showName(path);
    string tempLine;
    int current = 0;
    cout << "\n\nStudents:\n";
    while (getline(showName, tempLine))
    {
        current++;
        if (current >= 2) {
            cout  << tempLine.substr(0, 30) << endl;
        }
    }
    showName.close();
    cout << endl;

    // Ask for student selection
    cout << "\n\nSelect student : ";
    int select1;
    cin >> select1;
    select1 -= 1; // Adjust for header line
    // Ask for date
    int date;
    cout << "Enter Date : ";
    cin >> date;

    // Calculate index
    int dateIndex;
    if (date == 1) {
        dateIndex = 30;
    } else {
        dateIndex = (date * 6) + 30 - 6;
    }

    // Read that specific line and show character at date index
    ifstream file_show(path);
    string lineRead;
    int currentLine = 0;

    while (getline(file_show, lineRead)) {
        if (currentLine == select1 + 1) {
            if (lineRead.length() > dateIndex) {
                cout << "Attendance on Date " << date << ": " << lineRead[dateIndex] << endl;
                
            } else {
                cout << "\n\n\nData not available for that date." << endl;
            }
            break;
        }
        currentLine++;
    }

    file_show.close();
    cout << "\n\nPress Y for go to Main Screen / Press another button to check again" << endl;
    string choice;
    cin >> choice;

    if (choice == "Y" || choice == "y") {
        mainpage();
    } else {
        checkstudent(path);
    }
    cout << "\n\nPress Y for go to Main Screen / Press another button to check again" << endl;
    return 1;

}

string choice5()
{

    cout << "\n\n1. Add Student" << endl;
    cout << "2. Remove Student" << endl;
    cout << "3. Go to Main Screen" << endl;
    cout << "Select your choice: ";
    int choice;
    cin >> choice;
    
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "\n\n\nInvalid input! Please enter a number.\n" << endl;
        return choice5();
    }

    switch (choice) {
        case 1:
            addname();
            break;
        case 2:
            removeName();
            break;
        case 3:
            mainpage();
            break;
        default:
            cout << "\n\nInvalid choice!" << endl;
            choice5();
            break;
    }
    return 0;

}


string addname()
{
    string path;
    int select;

    // Step 1: List all folders inside ./classes
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
        cout << "\n\n\nnUnable to open './classes' directory." << endl;
        mainpage();
        
    }

    file.close();

    // Step 2: User selects a class folder
    cout << "\n\n\nSelect Class :  ";
    cin >> select;

    string storef;
    ifstream File2("temp.txt", ios::in);
    string line;
    int lineNumber = 0;

    if (File2.is_open()) {
        while (getline(File2, line)) {
            lineNumber++;
            if (lineNumber == select) {
                storef = line;
                break;
            }
        }
        File2.close();
    } else {
        cout << "\n\nSomething went Wrong" << endl;
        mainpage();
       
    }

    // Step 3: List files inside ./classes/storef
    time_t now = time(0);
    tm* t = localtime(&now);
    int month = t->tm_mon + 1;
    int year = t->tm_year + 1900;
    string month_str = montostr(month);
    string year_str = to_string(year);
    string folderPath = "./classes/" + storef;
    string filename = month_str + year_str + ".txt";

    // Final path to selected file
    path = folderPath + "/" + filename;

    ifstream file_show(path);
    string lineRead;
    int currentLine = 1;

    while (getline(file_show, lineRead))
     {
            
        currentLine++;
    }

    file_show.close();

    cout << "Enter Student Name: ";
    string student_name;
    cin.ignore();
    getline(cin, student_name);
    
    ofstream file1(path, ios::app);
    if (!file1) {
        cout << "Error opening file!" << endl;
       
    }
    file1<<currentLine - 1 << ". " << student_name << endl;
    file1.close();
    cout << "\n\nStudent added successfully!" << endl;
    cout << "\n\nPress Y for go to Main Screen / Press another button to add again" << endl;
    string choice;
    cin >> choice;
    if (choice == "Y" || choice == "y") {
        mainpage();
    } else {
        addname();
    }
    return 0;
    
    

}
string removeName()
{
    string path;
    int select;

    // Step 1: List all folders inside ./classes
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
        cout << "\n\nUnable to open './classes' directory." << endl;
        mainpage();
        return "";
    }

    file.close();

    // Step 2: User selects a class folder
    cout << "\n\nSelect Class :  ";
    cin >> select;

    string storef;
    ifstream File2("temp.txt", ios::in);
    string line;
    int lineNumber = 0;

    if (File2.is_open()) {
        while (getline(File2, line)) {
            lineNumber++;
            if (lineNumber == select) {
                storef = line;
                break;
            }
        }
        File2.close();
    } else {
        cout << "\n\nError opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Step 3: Build file path for current month and year
    time_t now = time(0);
    tm* t = localtime(&now);
    int month = t->tm_mon + 1;
    int year = t->tm_year + 1900;
    string month_str = montostr(month);
    string year_str = to_string(year);
    string folderPath = "./classes/" + storef;
    string filename = month_str + year_str + ".txt";

    path = folderPath + "/" + filename;

    // Step 4: Display student names
    int repeat = removestd(path);
    if (repeat == 1) {
        
    
    cout << "\n\nPress Y for remove again / Press another button to main menu : " << endl;
    string choice;
    cin >> choice;
    if (choice == "Y" || choice == "y") {
       removeName();
    } else {
        mainpage();
    }}
    cout << "File updated successfully!" << endl;

    return path;
}
int removestd(string path){
    ifstream showName(path);
    string tempLine;
    int current = 0;
    vector<string> allLines;

    cout << "\n\nStudents:\n";
    while (getline(showName, tempLine)) {
        allLines.push_back(tempLine);
        current++;
        if (current >= 2) {
            cout  << tempLine.substr(0, 30) << endl;
        }
    }
    showName.close();
    cout << endl;

    // Step 5: Ask for student selection
    cout << "\n\nSelect student to remove: ";
    int select1;
    cin >> select1;
    

    int lineToRemove = select1; // first line is metadata
    
    // Step 6: Rewrite file without selected line
    ofstream outFile(path, ios::out | ios::trunc);
    for (int j = 0; j < allLines.size(); j++) {
        if (j != lineToRemove) {
            outFile << allLines[j] << endl;
        }
    }
    outFile.close();
    cout << "\n\nStudent removed successfully!\n";
    return 1;

}




string autocreatefile(string filename)
{ 
    time_t now = time(0);
    tm* t = localtime(&now);
    int month = t->tm_mon + 1;
    int year = t->tm_year + 1900;

    string year_str = to_string(year);
    int day = monthdays(); 

    string month_str = montostr(month);
    string file_path = "Classes/" + filename + "/" + month_str + year_str + ".txt";
    global_file_path = file_path;

    ifstream check_exist(file_path);
    if (!check_exist.good()) 
    {
        ofstream file_check(file_path);

        
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
            cout << "" << endl;
        } else {
            string line;
            int currentLine = 0;
            while (getline(file_copy, line)) {
                currentLine++;
                if( currentLine == 1) {
                    continue; // Skip the first line (day numbers)
                }
                if (currentLine >= 2) {
                    if (line.length() > 30)
                        line = line.substr(0, 30);
                    file_check << line << endl;
                }
            }
            file_copy.close();
        }

        file_check.close();
        cout << "" << endl;
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


int studentname(string filename, string class_name) {
    string student_name;
    string ch;
    int day = monthdays();
    ofstream file1(global_file_path, ios::app);
    if (!file1) {
        cout << "\n\nError opening file!" << endl;
        return 1;
    }
    int i = 1;
    cout << "\nEnter Student Name (or type 'exit' to finish): \n\n";
    cout << "\n";
    while (true) {
        cout << "Enter Student " << i << ": ";
        getline(cin, student_name);
        if (student_name == "exit") {
            mainpage();
            break;
        }
        if (student_name.find_first_not_of(' ') == string::npos || student_name.empty()) {
            cout << "Please enter a valid name." << endl;
            continue;
        }
        file1 << i << ". " << student_name << endl;
        i++;
    }
    file1.close();
}





int mainpage(){
    cout << "\n\n\nWelcome to Attendance Management System" << endl;
    cout << "Please Enter Choice :" << endl;
    cout << "1. Take Attendance" << endl;
    cout << "2. Add Class" << endl;
    cout << "3. Veiw full Attendence" << endl;
    cout << "4. Select student Attendence" << endl;
    cout << "5. Add or Remove Student" << endl;
    cout << "6. Exit" << endl;

    
    int choice = 0;
    cout << "\nSelect your choice: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "\n\nInvalid input! Please enter a number.\n" << endl;
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
            choice3();
            break;
        case 4:
            choice4();
            break;
        case 5:
            choice5();
            break;
        case 6:
            cout <<endl<<endl<< "\n\nExiting..." << endl<<endl;
            return 0;
         break;
        default:
            cout << "\n\nInvalid choice!" << endl;
            break;
    }

    return 0;
    }



int main() 
{
    mainpage();
    return 0;
}
