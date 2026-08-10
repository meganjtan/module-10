// Megan Tan
// CIS 1202 801
// Aug 9, 2026
// Module 10 - Final Project
// Main - Basic Calculator

/* INSTRUCTIONS

To run in terminal:
    clang++ main.cpp BasicCalculator.cpp -o filename
    ./filename

What it does:
    The main (driver) displays a menu of options to choose from to test the capabilities of the BasicCalculator object. 
    The calculation info is written and read from the binary file "calculator_hisory.dat".
    The menu allows users to:
        1. Perform basic calculations (+, -, *, /, ^)
        2. Perform single operand calculations (sqrt, sin, cos, tan, log)
        3. Display all calculated history
        4. Search for a calculation
        5. Exit the program
*/

//0. LIBRARIES AND PROTOTYPES
#include <iomanip>
#include <iostream>
#include <fstream>
#include "BasicCalculator.h"
using namespace std;

int menu();
void calculations1(int& idCounter, fstream&);
void calculations2(int& idCounter, fstream&); 
void displayHistory(int& idCounter, fstream& file);
void searchHistory(int& idCounter, fstream&);
void saveRecord(const BasicCalculator& calc, fstream&);
template <typename T> T validation (T num);

//1. MAIN
int main(){
    fstream file("calculator_history.dat", ios::in | ios::out | ios::binary | ios::trunc); //read, write, binary, clear old data 
    int idCounter = 0; //id, and keeps count of how many calculations done
    int choice; //menu choice
    cout << fixed << setprecision(2); //go ahead and set console display #no. precision

    if(!file){ //if file can't be opened for some reason
        cout << "[Error opening file]" << endl;
        return 1;
    }

    do{ //do menu
        choice = menu(); //get choice, does validation
        cout << endl;
        switch(choice){
            case 1: //perform double operand calculations (+, -, *, /, ^)
                calculations1(idCounter, file);
                cout << endl;
                break;
            case 2: //perform single operand calculations (sqrt, sin, cos, tan, log)
                calculations2(idCounter, file);
                cout << endl;
                break;
            case 3: //display all history
                displayHistory(idCounter, file);
                cout << endl;
                break;
            case 4: //search history by id
                searchHistory(idCounter, file);
                cout << endl;
                break;
            case 5: //exit
                break;
            default: //oops why are you here
                cout << "[Invalid selection]" << endl;
                break;
        }
    } while(choice != 5); //user choice = 5 = exit
    file.close(); 
    cout << "Goodbye!" << endl;
    cout << endl;
    return 0;
}

//2. FUNCTIONS
/** 2.1
 *  @brief Display menu and return user choice
 *  @return int user choice
 */
int menu(){
    int choice;
    bool validInput;

    cout << "-------- CALCULATOR MENU --------" << endl;
    cout << "1. Perform Calculation (+, -, *, /, ^)" << endl;
    cout << "2. Perform Calculation (sqrt, sin, cos, tan, log)" << endl;
    cout << "3. View History" << endl;
    cout << "4. Search History by ID" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter Selection: ";

    do{ //input validation
        if (!(cin >> choice) || cin.fail() || choice < 1 || choice > 5){ //valid: btw 1-5 and an integer
            cout << "[Input error.] Try again (1-5): ";
            cin.clear(); //clears entry failure flag
            cin.ignore(10, '\n'); //ignores 10 digits from keyboard buffer
            validInput = false;
        } else{
            validInput = true;
        }
    } while(!validInput); //loops until a valid entry
    
    cin.ignore();
    return choice; //returns the user's menu choice
}

/** 2.2
 *  @brief Perform double operand calculations (+, -, *, /, ^)
 *  @param idCounter keeps track of records, fstream writes calculation to file to save it
 */
void calculations1(int& idCounter, fstream& file){
    char opChar; //operation choice
    double op1, op2 = 0.0; //two operands
    bool validOp; //validation for opChar

    do{ //input validation for opChar
        cout << "Enter operator (+, -, *, /, ^): ";
        if(cin>>opChar && (opChar == '+' || opChar == '-' || opChar == '*' || opChar == '/' || opChar == '^')){
            validOp = true; 
            cout << endl;
        } else {
            cout << "[Input error.] Try again. ";
            cin.clear(); //clears entry failure flag
            cin.ignore(10, '\n'); //ignores 10 digits from keyboard buffer
            validOp = false;
        }
    } while(!validOp);

    //input validation for op1, op2
    cout << "Enter first operand: ";
    op1 = validation(op1);
    if(opChar == '/'){ //division by 0 is undefined
        cout << "Enter second operand (/= 0): ";
        op2 = validation(op2);
        while(op2==0.0){
            cout << "[error.] Division by 0 is undefined. Try again: ";
            op2 = validation(op2);
        }
    } else {
        cout << "Enter second operand: ";
        op2 = validation(op2);
    }
   
    //calculator computes
    BasicCalculator calc;
    calc.setID(++idCounter);
    calc.compute(op1, op2, opChar);

    //display to console
    cout << "Result: " << calc.getResult() << endl;

    //save to binary file
    saveRecord(calc, file); 
}

/** 2.3
 *  @brief Perform single operand calculations (sqrt, sin, cos, tan, log)
 *  @param idCounter keeps track of records, fstream writes calculation to file to save it
 */
void calculations2(int& idCounter, fstream& file){
    cout << "--- Advanced Scientific Math Operation ---\n";
    cout << "1. Square Root (sqrt)" << endl;
    cout << "2. Sine (sin - in degrees)" << endl;
    cout << "3. Cosine (cos - in degrees)" << endl;
    cout << "4. Tangent (tan - in degrees)" << endl;
    cout << "5. Common Logarithm (log10)" << endl;
    cout << "6. Natural Logarithm (ln)" << endl;
    cout << "Enter selection (1-6): ";

    int functionChoice;
    bool validInput;
    do{ //input validation
        if (!(cin >> functionChoice) || cin.fail() || functionChoice < 1 || functionChoice > 6){ //valid: btw 1-6 and an integer
            cout << "[Input error.] Try again (1-6): ";
            cin.clear(); //clears entry failure flag
            cin.ignore(10, '\n'); //ignores 10 digits from keyboard buffer
            validInput = false;
        } else{
            validInput = true;
            cout << endl;
        }
    } while(!validInput); //loops until a valid entry
    cin.ignore();

    double op1;
    cout << "Enter value: ";
    op1 = validation(op1);
    if(functionChoice == 1){ //sqrt must be >= 0
        while(op1<0){
            cout << "[Input error.] Try again (>=0): ";
            op1 = validation(op1); 
        }
    } else if(functionChoice == 5 || functionChoice == 6){ //log must be > 0
        while(op1<=0){
            cout << "[Input error.] Try again (>0): ";
            op1 = validation(op1); 
        }
    }

    //calc computes
    BasicCalculator calc;
    calc.setID(++idCounter);
    calc.compute(op1, functionChoice);

    //display to console
    cout << "Result: " << calc.getResult() << endl;

    //save to binary file
    saveRecord(calc, file);
}

/** 2.4
 *  @brief Display all calculator history
 *  @param idCounter keeps track of records, fstream reads from file to display to console
 */
void displayHistory(int& idCounter, fstream& file){
    if(idCounter == 0){ //no calculations made yet
        cout << "[Not Available. No calculations added yet.]" << endl;
        return; //end
    }

    file.clear(); //clears error flags
    file.seekg(0, ios::beg); //start at beginning of file, no offset

    BasicCalculator calc;
    while(file.read(reinterpret_cast<char*>(&calc), sizeof(BasicCalculator))){ //read in each calculation and display to console
        calc.displayInfo(); 
        cout << endl;
    }
}

/** 2.5
 *  @brief Search and display a calculation
 *  @param idCounter keeps track of records, fstream reads from file to display to console
 */
void searchHistory(int& idCounter, fstream& file){
    file.clear(); //clears error flags
    
    int searchID;
    cout << "Enter an ID to search: ";
    searchID = validation(searchID); //input validation

    BasicCalculator calc;
    if(searchID <= idCounter && searchID > 0){ //if search is within the #no. of searches, continue
        file.seekg((searchID-1)*sizeof(BasicCalculator), ios::beg); //place iterator @ point of search ID (beginning + offset) - file is 0 indexed and my records start at 1, thus id-1 = file index
        file.read(reinterpret_cast<char*>(&calc), sizeof(BasicCalculator)); //read in the record
        cout << "[record found.]" << endl;
        calc.displayInfo();
        return;
    }
    cout << "[record not found.]" << endl;
}

/** 2.6
 *  @brief Save a calculation to file 
 *  @param calculator object & ccstring file name
 */
void saveRecord(const BasicCalculator& calc, fstream& file){ 
    file.clear(); //clear error flags
    file.seekp(0, ios::end); //seek end of file to append, no offset
    file.write(reinterpret_cast<const char*>(&calc), sizeof(BasicCalculator)); 
    cout << "[calculation saved]" << endl;
}

/** 2.8
 *  @brief Template for input validation for typename T data types
 *  @param T num
 *  @return T num
 */
template <typename T> 
T validation (T num){
    bool validInput;

    do{ //input validation
        if (!(cin >> num) || cin.fail()){ //valid: datatype T
            cout << "[Input error.] Try again: ";
            cin.clear(); //clears entry failure flag
            cin.ignore(10, '\n'); //ignores 10 digits from keyboard buffer
            validInput = false;
        } else{
            validInput = true;
        }
    } while(!validInput); //loops until a valid entry
    
    cin.ignore();
    return num; //returns the num
}
