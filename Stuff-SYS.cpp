// Team Members:-
/*
    N A M E				      ID
- - - - - - - - - - - - - - - - - - - +
Abdulrahman M.Alshehri    2190005832  |
Saleh A.Rammah            2210001932  |
Muhannad A.Almahmoud      2210002240  |
Sami S.AlIrhain           2220000109  |
Abdulaziz H.Hamdi         2220002901  |
- - - - - - - - - - - - - - - - - - - +
*/



/*
---------------+
Libraries Area |
---------------+
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>
#include <sys/stat.h>
using namespace std;



/*
---------------+
Files Area     |
---------------+
*/
const string PROGRAM_NAME = "Stuff-SYS.exe";
const string DB_NAME = "Staff-DB.txt";
const string REPORT_NAME = "Stuff-REPORT.txt";
const string BACKUP_NAME = "Staff-BACKUP.txt";



/*
---------------+
Structure Area |
---------------+
*/
struct Staff {
    string name;
    int id;
    int age;
    string job;
    double salary;
};



/*
---------------+
ProtoTypes Area|
---------------+
*/
void displayMenu();
int getFileInfo(string DB_NAME, string type);
void Struct_Update(vector<Staff> &staff, int size, int capcity);
bool Validation_INT_Check(int& input);
bool Validation_DOUBLE_Check(int& input);
bool Validation_STRING_Check(string& input, bool isMultiLine, int maxValue);
void back();
void clearScreen();
void addEmployee(vector<Staff> &staff, int& size, int& capacity);
int getIntInput(const string& prompt, int minValue, int maxValue);
double getDoubleInput(const string& prompt, double minValue, double maxValue);
string getStringInput(const string& prompt, bool isMultiLine, int maxValue);
bool checkUniqueID(int id, vector<Staff> &staff, int size);
bool DBCheck(int size, bool isAdding, int capacity);
void searchEmployee(vector<Staff> &staff, int size, int capacity);
void updateEmployee(vector<Staff> &staff, int size, int capacity);
void deleteEmployee(vector<Staff> &staff, int& size, int capacity);
void sortEmployees(vector<Staff> &staff, int size, int capacity);
void displayAllEmployees(vector<Staff> &staff, int size, int capacity);
void generateReport(vector<Staff> &staff, int size, int capacity);
void createBackupFile(string originalFile, string backupFile);
time_t get_last_activity_time(const string& PROGRAM_NAME);
void updateFile(vector<Staff> &staff, int size, int capacity);
void settings(int size, int *capacity);
void Read_Mode();
void Append_Mode(string text);
void OverWrite_Mode(string text);
void Clear_Mode(string FILE);
void Change_CAPACITY(int size, int *capacity);
void getSTATUS(int size, int capacity, time_t last_activity_time);



/*
---------------+
Root Area      |
---------------+
*/
int main() {
    /*makes an inFile database object to read from DB_NAME, creates a size and Bu variables of type int and string respectively as well as a Staff array created from a structure*/
    ifstream inFile;
    int size, capacity;
    string LINE;
    capacity = getFileInfo(DB_NAME, "capacity");
    size = getFileInfo(DB_NAME, "size");
    vector<Staff> staff(size);
    Struct_Update(staff, size, capacity);
    inFile.open(DB_NAME);
    time_t last_activity_time;

    
    /* checks if the inFile object is open, if not creates a file and names it DB_NAME and writes to it and filling it with - with width 50. also checks with an else condition for errors like a compiler error or not finding the file*/
    if (inFile.fail()) {
        if (!inFile.is_open()) {
            cout << "File does not exist. Creating a new file..." << endl << "File_Name:" << DB_NAME << endl;
            ofstream outFile(DB_NAME);
            outFile.close();
            updateFile(staff, size, capacity);
            cout << setfill('-') << setw(50) << "" << endl;
            cout << endl << "\n!!Press Double ENTER!!";
            back();
        }
        else {
            cout << "[x]Somthing Wrong!! (Check $PATH Permission)" << endl;
            exit(0);
        }
    }
    
    /*this is the menu switch case. basically calls upon the displaymenu() function to print the statements to use this correctly and within the while loop it a function that checks for int values entered.*/
    /*the user inputs the right integer that corresponds to a function from the menu function. if the user selects 0 the code quits*/
    int option;
    do {
        do {
            displayMenu();
            cout << "\nEnter your option: ";
        } while (!Validation_INT_Check(option));
        switch (option) {
        case 1:
            clearScreen();
            addEmployee(staff, size, capacity);
            updateFile(staff, size, capacity);
            break;
        case 2:
            clearScreen();
            searchEmployee(staff, size, capacity);
            break;
        case 3:
            clearScreen();
            updateEmployee(staff, size, capacity);
            updateFile(staff, size, capacity);
            break;
        case 4:
            clearScreen();
            deleteEmployee(staff, size, capacity);
            updateFile(staff, size, capacity);
            break;
        case 5:
            clearScreen();
            sortEmployees(staff, size, capacity);
            updateFile(staff, size, capacity);
            break;
        case 6:
            clearScreen();
            displayAllEmployees(staff, size, capacity);
            break;
        case 7:
            clearScreen();
            generateReport(staff, size, capacity);
            break;
        case 8:
            clearScreen();
            createBackupFile(DB_NAME, BACKUP_NAME);
            break;
        case 9:
            clearScreen();
            getSTATUS(size, capacity, last_activity_time);
            break;
        case 10:
            clearScreen();
            settings(size, &capacity);
            updateFile(staff, size, capacity);
            break;
        case 0:
            clearScreen();
            cout << "Thank you for using " << PROGRAM_NAME << "." << endl;
            break;
        default:
            clearScreen();
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    } while (option != 0);

    cout << "Exiting program..." << endl;

    return 0;
}



/*
---------------+
Functions Area |
---------------+
*/

/* the menu function printing all the numbers with the corresponding function names to choose from*/
void displayMenu() {
    clearScreen();
    cout << "\n>>>>>>>>>>> STAFF MANAGEMENT SYSTEM <<<<<<<<<<<" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
    cout << "ENTER--1----->  To Add an Employee" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--2----->  To Search for an Employee" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--3----->  To Update an Employee" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--4----->  To Delete an Employee" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--5----->  To Sort Employees by Name" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--6----->  To Display all Employees" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--7----->  To Generate Report File" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--8----->  To Generate BackUp File" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--9----->  To see STATUS" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--10---->  To Settings" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -|" << endl;
    cout << "ENTER--0----->  To Exit" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
}

int getFileInfo(string DB_NAME, string type) {
    int size = -2, capacity = 100/*Default Maximum Size*/;
    string LINE;
    ifstream inFile;
    inFile.open(DB_NAME);
    if (inFile.is_open()) {
    	// Get the file size
        inFile.seekg(0, inFile.end);
        streampos inFileSize = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        
    	if(inFileSize  == 0){
    		if(type == "capacity"){
    			return capacity;
			}
			if(type == "size"){
        		return size+=2;
			}
		}else{
			if(type == "capacity"){
        		getline(inFile, LINE);
        		istringstream iss(LINE);
        		iss >> capacity;
        		inFile >> capacity; // Read the maximum size
        		inFile.close();
    			return capacity;
			}
			if(type == "size"){
				inFile >> size; // Read the current size
				inFile.close();
        		return size;
			}
		}
    }else{
    	if(type == "capacity"){
    		return capacity;
		}
		if(type == "size"){
        	return size+=2;
		}
	}
}


void Struct_Update(vector<Staff> &staff, int size, int capacity){
	ifstream inFile;
	string LINE;
	inFile.open(DB_NAME);
	getline(inFile, LINE);
    getline(inFile, LINE);
	for (int i = 0; i < size; i++) {
        inFile >> staff[i].name >> staff[i].id >> staff[i].age >> staff[i].job >> staff[i].salary;
    }
    inFile.close();
    return;
}

/*a bool function to check whether the number selected is an int or not with true or false using a referenced variable*/
bool Validation_INT_Check(int& input) {
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();
        cout << "[!]Input Numeric Value." << endl
            << "[x]OverFlow Input." << endl
            << setfill('-') << setw(50) << "" << endl;
        return false;
    }
    return true;
}

/*a bool function to check whether the number selected is an double or not with true or false using a referenced variable*/
bool Validation_DOUBLE_Check(double& input) {
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();
        cout << "[!]Input Numeric Value." << endl
            << "[x]OverFlow Input." << endl
            << setfill('-') << setw(50) << "" << endl;
        return false;
    }
    return true;
}

/*a bool function to check whether the number selected is an string or not with true or false using a referenced variable*/
bool Validation_STRING_Check(string& input, bool isMultiLine, int maxValue) {
    if (isMultiLine) {
        cin.ignore();
        getline(cin, input);
    }
    else {
        cin >> input;
    }
    if (input.length() >= maxValue) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();
        cout << "[!]Input <= " << maxValue << " characters." << endl
            << setfill('-') << setw(50) << "" << endl;
        return false;
    }
    return true;
}

/*a function to backtrack within the menu*/
void back() {
    cout << endl << "\n[*]Press [ENTER] to go Back . .";
    cin.ignore();
    cin.get();
    clearScreen();
}

/*a function used to clear the screen from any previous commands*/
void clearScreen() {
    system("cls");
}

/*a function that takes the id, name, age, job and salary of an employee and checks if it already exits or not then adds it within our staff arrays file while also checking wheather the inputs are integers or not.*/
/*after taking all the info, it moves on to the next array slot to add another staff if desired. after all of that it clears the screen, confirms if the opreation was successful*/
void addEmployee(vector<Staff> &staff, int& size, int& capacity) {
	Staff Employee;
	
	if (DBCheck(size, true, capacity)) {
        return;
    }
    
    int id = getIntInput("Enter the ID of the new employee: ", 0, 999999);
    if (checkUniqueID(id, staff, size)) {
        Employee.id = id;
        Employee.name = getStringInput("Enter the name of the new employee: ", false, 15);
        Employee.age = getIntInput("Enter the age of the new employee: ", 0, 100);
        Employee.job = getStringInput("Enter the job title of the new employee: ", false, 20);
        Employee.salary = getDoubleInput("Enter the salary of the new employee: $", 0, 999999);
        staff.push_back(Employee);
        size++;
        clearScreen();
        cout << endl << "Employee added successfully." << endl
            << setfill('-') << setw(50) << "" << endl;
    }
    else {
        clearScreen();
        cout << endl << "ID already exists. Employee not added." << endl
            << setfill('-') << setw(50) << "" << endl;
    }
    back();
}

/*a function that checks if the input is an integer or not and have some limitation in input*/
int getIntInput(const string& prompt, int minValue, int maxValue) {
    int input;
    do {
        do {
            cout << prompt;
        } while (!Validation_INT_Check(input));
        if (input < minValue || input > maxValue) {
            clearScreen();
            cout << "Invalid input. Please enter a value between " << minValue << " and " << maxValue << "." << endl
                << setfill('-') << setw(50) << "" << endl;
            // return 0x00;
        }
    } while (input < minValue || input > maxValue);
    return input;
}

/*a function that checks if the input is an double or not and have some limitation in input*/
double getDoubleInput(const string& prompt, double minValue, double maxValue) {
    double input;
    do {
        do {
            cout << prompt;
        } while (!Validation_DOUBLE_Check(input));
        if (input < minValue || input > maxValue) {
            clearScreen();
            cout << "Invalid input. Please enter a value between " << minValue << " and " << maxValue << endl
                << setfill('-') << setw(50) << "" << endl;
        }
    } while (input < minValue || input > maxValue);
    return input;
}

/*a function that checks if the input is an string or not*/
string getStringInput(const string& prompt, bool isMultiLine, int maxValue) {
    string input;
    do {
        cout << prompt;
    } while (!Validation_STRING_Check(input, isMultiLine, maxValue));
    return input;
}

/*a function that checks if the id already exits in the staff array made earlier*/
bool checkUniqueID(int id, vector<Staff> &staff, int size) {
    for (int i = 0; i < size; i++) {
        if (staff[i].id == id) {
            return false;
        }
    }
    return true;
}

/*a function that checks wheather the the DB slot if max or empty*/
bool DBCheck(int size, bool isAdding, int capacity) {
	
	if(size >= capacity && isAdding){
		cout << "[!]The DB is Full." << endl;
		back();
		return true;
	}
	
    if (size <= 0 && !isAdding) {
        cout << "[!]Empty Staff." << endl
            << setfill('-') << setw(50) << "" << endl;
        back();
        return true;
    }
    return false;
}

/*a function that searched for an employee by using their id to check within our staff array. after checking for the staff wheather he is found(will print his info) or not, clears the screen*/
void searchEmployee(vector<Staff> &staff, int size, int capacity) {

    if (DBCheck(size, false, capacity)) {
        return;
    }

    int id = getIntInput("Enter the ID of the staff member to search for: ", 0, 999999);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (staff[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        clearScreen();
        cout << "Staff member not found." << endl
            << setfill('-') << setw(20) << "" << endl;
    }
    else {
        clearScreen();
        cout << "[Employee INFO]" << endl
            << setfill('-') << setw(25) << "" << endl
            << "Name: " << staff[index].name << endl
            << "ID: " << staff[index].id << endl
            << "Age: " << staff[index].age << endl
            << "Job: " << staff[index].job << endl
            << "Salary: " << staff[index].salary
            << endl
            << setfill('-') << setw(25) << "" << endl;
    }
    back();
}

/*a function that updates a staff's info within the staff array by using their name */
void updateEmployee(vector<Staff> &staff, int size, int capacity) {

    if (DBCheck(size, false, capacity)) {
        return;
    }

    int id = getIntInput("Enter the ID of the staff member to update: ", 0, 999999);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (staff[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        clearScreen();
        cout << "Staff member not found." << endl
            << setfill('-') << setw(20) << "" << endl;
    }
    else {
        clearScreen();
        cout << "[#]Found." << endl
            << setfill('-') << setw(50) << "" << endl;
        staff[index].name = getStringInput("Enter the new name of the staff member: ", false, 15);
        staff[index].id = getIntInput("Enter the new ID of the staff member: ", 0, 999999);
        staff[index].age = getIntInput("Enter the new age of the staff member: ", 0, 100);
        staff[index].job = getStringInput("Enter the new job of the staff member: ", false, 20);
        staff[index].salary = getDoubleInput("Enter the new salary of the staff member: ", 0, 999999);
        clearScreen();
        cout << "Staff member updated successfully!" << endl
            << setfill('-') << setw(50) << "" << endl;
    }
    back();
    return;
}

/*a function that deletes an employee's info from the staff array using their name*/
void deleteEmployee(vector<Staff> &staff, int& size, int capacity) {

    if (DBCheck(size, false, capacity)) {
        return;
    }

    int id = getIntInput("Enter the ID of the staff member to delete: ", 0, 999999);
    
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (staff[i].id == id) {
        	index = i;
            staff.erase(staff.begin() + i);
            size--;
            break;
        }
    }
    
        
    if (index == -1) {
        clearScreen();
        cout << "Staff member not found." << endl
            << setfill('-') << setw(50) << "" << endl;
    }
    else {
        for (int i = index; i < size - 1; i++) {
            staff[i] = staff[i + 1];
        }
        clearScreen();
        cout << "Staff member deleted successfully!" << endl
            << setfill('-') << setw(50) << "" << endl;
    }
    back();
    return;
}

/*a function that uses bubble sort to sort the employees by their names in the staff array*/
void sortEmployees(vector<Staff> &staff, int size, int capacity) {

    if (DBCheck(size, false, capacity)) {
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (staff[j].name > staff[j + 1].name) {
                Staff temp = staff[j];
                staff[j] = staff[j + 1];
                staff[j + 1] = temp;
            }
        }
    }
    clearScreen();
    cout << "Staff members sorted by name successfully!" << endl
        << setfill('-') << setw(50) << "" << endl;
    back();
    return;
}

/* a function that displays all employee names, ids, ages, jobs ,salaries*/
void displayAllEmployees(vector<Staff> &staff, int size, int capacity) {

    if (DBCheck(size, false, capacity)) {
        return;
    }

    cout << "[Employees INFO]" << endl;
    cout << setfill('-') << setw(50) << "" << endl;
    for (int i = 0; i < size; i++) {
        cout << "[" << i + 1 << "]"
            << " name:" << staff[i].name << ", "
            << "id:" << staff[i].id << ", "
            << "age:" << staff[i].age << ", "
            << "job:" << staff[i].job << ", "
            << "salary:" << staff[i].salary << "."
            << endl;
    }
    cout << setfill('-') << setw(50) << "" << endl;
    back();
    return;
}

/*a function that updates the database file by writing new info*/
void updateFile(vector<Staff> &staff, int size, int capacity) {
	string LINE;
    ofstream outFile(DB_NAME);
    outFile << size << endl; // Write the current size
    outFile << capacity << endl; // Write the maximum size
    for (int i = 0; i < size; i++) {
        outFile << staff[i].name << " " << staff[i].id << " " << staff[i].age << " " << staff[i].job << " " << staff[i].salary << endl;
    }
    outFile.close();
}

/*a function that generates a report file by writing the employees info in the reports file as well as their number and the last updates done to it.*/
void generateReport(vector<Staff> &staff, int size, int capacity) {
    time_t now = time(0);
    ofstream outFile(REPORT_NAME);
    outFile << "{Staff Report}" << endl << endl;
	outFile << "CAPACITY: " << capacity << endl;
    outFile << "Number of staff members: " << size << endl;
    outFile << "Last update: " << ctime(&now) << endl << endl;
    for (int i = 0; i < size; i++) {
        outFile << "[" << i + 1 << "]"
            << " name:" << staff[i].name << ", "
            << "id:" << staff[i].id << ", "
            << "age:" << staff[i].age << ", "
            << "job:" << staff[i].job << ", "
            << "salary:" << staff[i].salary << "."
            << endl;
    }
    outFile.close();
    cout << "Report generated successfully!" << endl
        << setfill('-') << setw(50) << "" << endl;
    back();
    return;
}

/*a function that generates a backup file. it reads from the original file and writes it to another file(backup), as well as checking if the original and backup files exist*/
void createBackupFile(string originalFile, string backupFile = BACKUP_NAME) {
    ifstream inFile;
    ofstream outFile;

    inFile.open(originalFile);
    outFile.open(backupFile);

    if (inFile.fail()) {
        cout << "Error: original file does not exist." << endl
            << setfill('-') << setw(50) << "" << endl;
        back();
        return;
    }
    else if (outFile.fail()) {
        cout << "Error: cannot create backup file." << endl
            << setfill('-') << setw(50) << "" << endl;
        back();
        return;
    }

    string line;
    while (!inFile.eof()) {
        getline(inFile, line);
        outFile << line << endl;
    }

    cout << "Backup file successfully created." << endl
        << setfill('-') << setw(50) << "" << endl;
    inFile.close();
    outFile.close();
    back();
    return;
}

/*a function that checks the status of the edits made or running the main program exe*/
time_t get_last_activity_time(const string& PROGRAM_NAME) {
    struct stat file_stat;
    if (stat(PROGRAM_NAME.c_str(), &file_stat) != 0) {
        cout << "Failed to get file status" << endl
            << setfill('-') << setw(50) << "" << endl;
        return 0;
    }
    return file_stat.st_mtime;
}

/*a function that checks the REPORT File and changes any configurations for it. using several modes such as read(prints data), appened(adds to the end of the text), rewrite(edit or write the file again), clear(Delete the data)*/
/*it also has option to Delete Data in DB file, And another option to change the name of backup file with backup more than one file */
void settings(int size, int *capacity) {
    ifstream CHECK_FILE(REPORT_NAME);
    string text;
    int op, op1;

    do {
        op = getIntInput("1-Report_Config   2-Delete_Stuff_DB   3-Change_FILENAME_BackUp   4-Change_capacity   0-Back\n\n- - > ", 0, 4);
        switch (op) {
        case 1:
            clearScreen();
            if (!CHECK_FILE.is_open()) {
                cout << "[x]REPORT_FILE Does Not Exist!!" << endl
                    << setfill('-') << setw(50) << "" << endl;
                back();
                break;
            }
            do {
                cout << "[!]Found {REPORT_FILE.txt}" << endl
                    << setfill('-') << setw(50) << "" << endl;
                op1 = getIntInput("1-Read_Data  2-Append_Data  3-OverWrite_Data  4-Clear_Data  0-Back\n\n- - > ", 0, 4);
                switch (op1) {
                case 1:
                    clearScreen();
                    Read_Mode();
                    break;
                case 2:
                    clearScreen();
                    Append_Mode(getStringInput("Enter the text to be Appended: ", true, 999999));
                    break;
                case 3:
                    clearScreen();
                    OverWrite_Mode(getStringInput("Enter the text to be ReWritten: ", true, 999999));
                    break;
                case 4:
                    clearScreen();
                    Clear_Mode(REPORT_NAME);
                    break;
                case 0:
                    clearScreen();
                    break;
                default:
                    clearScreen();
                    cout << "[x]Error!!" << endl;
                    break;
                }
            } while (op1 != 0);
            break;
        case 2:
            clearScreen();
            cout << "[!]The Program Will Close[!]" << endl
                << "Write (\"Confirm\") To Continue." << endl
                << "- - > ", cin >> text;

            for (int i = 0; i < text.length(); i++) {
                text[i] = tolower(text[i]);
            }
            if (text == "confirm") {
                Clear_Mode(DB_NAME);
                exit(0);
            }
            clearScreen();
            break;
        case 3:
            clearScreen();
            createBackupFile(DB_NAME, getStringInput("{Create Your New File}\nFile Name: ", false, 10) + ".txt");
            break;
        case 4:
        	clearScreen();
        	Change_CAPACITY(size, *&capacity);
        	break;
        case 0:
            return;
        default:
            cout << "[x]Error!!" << endl;
            break;
        }
    } while (op != 3);
    return;
}

/*a function to read and print the contents of the REPORT file. it checks if the file is at the end of the text, if not then it continues printing until it does.*/
void Read_Mode() {
    cout << setfill('-') << setw(50) << "" << endl;
    ifstream read;
    read.open(REPORT_NAME, ios::in);
    string line;
    while (!read.eof()) {
        getline(read, line);
        cout << line << endl;
    }
    read.close();
    cout << setfill('-') << setw(50) << "" << endl;
    back();
    return;
}

/*a function to appened or add to the text file of the REPORT*/
void Append_Mode(string text) {
    ofstream append;
    append.open(REPORT_NAME, ios::app);
    append << text << endl;
    append.close();
    clearScreen();
    cout << "[#]Done." << endl
        << setfill('-') << setw(50) << "" << endl
        << endl << "\n!!Press Double ENTER!!";
    back();
    return;
}

/*a function that opens the REPORT file to rewrite it */
void OverWrite_Mode(string text) {
    ofstream rewrite;
    rewrite.open(REPORT_NAME, ios::out);
    rewrite << text << endl;
    rewrite.close();
    clearScreen();
    cout << "[#]Done." << endl
        << setfill('-') << setw(50) << "" << endl
        << endl << "\n!!Press Double ENTER!!";
    back();
    return;
}

/*a function that delete the data from report_file*/
void Clear_Mode(string FILE) {
    ofstream clear(FILE);
    clear.clear();
    clear.close();
    clearScreen();
    cout << "[#]Done." << endl
        << setfill('-') << setw(50) << "" << endl;
    back();
    return;
}

/*a function that change the capacity from DB file*/
void Change_CAPACITY(int size, int *capacity){
	int Whew = *capacity;
	cout << "[!]Maximum Capacity <= 1000000" << endl
         << setfill('-') << setw(32) << "" << endl;
	*capacity = getIntInput("New capacity: ", 0, 1000000);
	clearScreen();
	if(*capacity < size){
		cout << "[x]Cannot change capacity to a value less than or equal the number of employees" << endl
			 << setfill('-') << setw(50) << "" << endl;
		*capacity = Whew;
		back();
        return;
	}
    cout << "[#]Done." << endl
        << setfill('-') << setw(50) << "" << endl;
	back();
	return;
}

void getSTATUS(int size, int capacity, time_t last_activity_time){
	ifstream CHECK_REPORT_FILE(REPORT_NAME);
	ifstream CHECK_BACKUP_FILE(BACKUP_NAME);
	string report_status, backup_status;
	last_activity_time = get_last_activity_time(PROGRAM_NAME);
	
	if(CHECK_REPORT_FILE.is_open()){
		report_status = "AVAILABLE!";
	}else{
		report_status = "Not AVAILABLE!";
	}
	
	if(CHECK_BACKUP_FILE.is_open()){
		backup_status = "AVAILABLE!";
	}else{
		backup_status = "Not AVAILABLE!";
	}
	
	cout << "[#]STATUS" << endl
        << setfill('-') << setw(50) << "" << endl;
    cout << "CAPACITY--> " << capacity << endl;
    cout << "NUMBER_OF_EMPLOYEES--> " << size << endl;
    cout << "REPORT_FILE--> " << report_status << endl;
    cout << "BACKUP_FILE--> " << backup_status << endl;
    cout << "LAST_ACTIVITY--> " << ctime(&last_activity_time)
    	 << setfill('-') << setw(50) << "" << endl;
    back();
    
    return;
}
