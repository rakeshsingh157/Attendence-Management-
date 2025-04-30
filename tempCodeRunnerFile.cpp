string choice4()
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
        cout << "Unable to open './classes' directory." << endl;
        mainpage();
        return "";
    }

    file.close();

    // Step 2: User selects a class folder
    cout << "Select Class :  ";
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
        cout << "Error opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Step 3: List files inside ./classes/storef
    string folderPath = "./classes/" + storef;
    DIR* subDir = opendir(folderPath.c_str());

    if (subDir == NULL) {
        cout << "Unable to open folder: " << folderPath << endl;
        mainpage();
        return "";
    }

    ofstream fileList("temp.txt", ios::out);  // Overwrite again with files
    i = 1;

    cout << "\nFiles in " << storef << ":\n";

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
    cout << "Select Month : ";
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
        cout << "Error opening temp.txt" << endl;
        mainpage();
        return "";
    }

    // Final path to selected file
    path = folderPath + "/" + filename;


    cout<<endl<<endl;
   
   

        // Show first 30 characters of the line
        ifstream showName(path);
        string tempLine;
        int current = 0;
        while (getline(showName, tempLine)) {
            current++;
            if (current >= 2) {
                cout << tempLine.substr(0, 30) << endl;
                
            }
        }
        showName.close();
        cout<<endl<<endl;
   
        cout << "Select line : " << endl;
        int select1 , currentLine = 0;
        
        cin >> select1;
        select1 = select1 + 1;
        int date;
        cout << "Enter Date : ";
        cin >> date;
        
        int dateIndex;  // Declare the dateIndex outside the if/else block
        
        // Convert the date to 0-based indexing
        if (date == 1) {
            dateIndex = 30;  // For the first date, it’s the 31st character (index 30)
        } else {
            dateIndex = (date * 6) + 30 - 6;  // For other dates, calculate based on the pattern
        }
        
        ifstream file_show(path);
        string lines;
        while (getline(file_show, line)) 
        {
            if (currentLine == select1) {
        while (getline(file_show, lines)) {
            if (lines.length() > dateIndex) {
                cout << lines[dateIndex] << endl;  // Print the character at dateIndex
            } else {
                cout << " " << endl;  // Print blank space if line is shorter than dateIndex
            }
        }
        currentLine++;
    }}
        
        file_show.close();
    



}