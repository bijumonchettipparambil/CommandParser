#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cctype>

//Namespace definition
using namespace std;

/**
 * 
 * This program implements a command-based calculator in C++.
 * 
 * Users can input a complete operation command in a single line, such as:
 * 
 *      add 10 5
 *      divide 42 6
 *      mod 9 4
 * 
 * The input is parsed into three parts:
 * 
 *  - A command keyword (add, subtract, multiply, divide, mod)
 *  - First operand
 *  - Second operand
 * 
 * The program validates the command and the numeric inputs, performs the
 * appropriate operation, and prints the result.
 * 
 * Invalid commands, non-numeric input, or incorrect number of arguments are
 * all handled gracefully with informative error messages.
 * 
 * The program continues running until the user enters the "quit" command.
 * 
 */

// Constant definitions
const short MAX_COMMANDS = 5;
const short MAX_RETRIES = 3;
const string ADD = "ADD";
const string SUBTRACT = "SUBTRACT";
const string MULTIPLY = "MULTIPLY";
const string DIVIDE = "DIVIDE";
const string QUIT = "QUIT";
const vector<string> VALID_COMMANDS = {ADD, SUBTRACT, MULTIPLY, DIVIDE, QUIT};

// Error message constants
const string INVALID_INPUT = "Invalid/Unrecognised input ";
const string EXTRANEOUS_INPUT = "Extraneous input ";
const string RETRY_ATTEMPTS_EXHAUSTED = "Retry attempts exhausted!";

// Prototype definitions
string promptAndGetInputFromUser(void);
void showCommandFormatAndExample(void);
map<string, string> parseUserInput(string);
void showErrorMessage(string, string);
string validateAndReturnParsedInput(string, short);
string getResult(map<string, string>);
double performOperation(string, double, double);
string stringToUpperCase(string);
bool isAValidCommand(string);
bool isAValidNumber(string);
bool isAFloatingPointNumber(string);
double addNumbers(double, double);
double subtractNumbers(double, double);
double multiplyNumbers(double, double);
double divideNumbers(double, double);

/**
 * 
 * Main function
 * 
 */
int main(void){
    short retryCount = 0;
    bool commandFinished = false;
    map<string, string> command;
    while(retryCount < MAX_RETRIES && !commandFinished){
        string input = promptAndGetInputFromUser();
         command = parseUserInput(input);
         if (!command.empty()){
            if (stringToUpperCase(command["0"]) == QUIT){
                return 0;
            } else {
                cout << endl;
                cout << "===================================================================================" << endl;
                cout << "The result of the \"" << command["0"] << "\" operation is: " << getResult(command) << endl;
                cout << "===================================================================================" << endl;
                cout << endl;
                retryCount = 0;
            }
         } else {
            retryCount++;
         }
    }
    if (retryCount > MAX_RETRIES){
        showErrorMessage("", RETRY_ATTEMPTS_EXHAUSTED);
    }
    return 0;
}

/**
 * Prompt user for input
 */
string promptAndGetInputFromUser(void){
    string input;
    showCommandFormatAndExample();
    cout << "Enter the command : ";
    getline(cin, input);
    return input;
}

/**
 * Show the command format and example to user
 */
void showCommandFormatAndExample(void){
    cout << "<--------------------------------------------------------------------------------->" << endl;
    cout << "Format of input is <command> <operand1> <operand2>" << endl;
    cout << "Example: add 100 50" << endl;
    cout << "<--------------------------------------------------------------------------------->" << endl;
    cout << "Enter \"Quit\", to exit!" << endl;
    cout << "<--------------------------------------------------------------------------------->" << endl;
    cout << endl;
}

/**
 * Edit check and parse user input
 */
map<string, string> parseUserInput(string input){
    istringstream streamOfUserInput(input);
    map<string, string> parsedUserInput;
    short inputCount = 0;
    string wordFromInput;
    string editedInputWord;
    while (true){
        wordFromInput = "";
        getline(streamOfUserInput, wordFromInput, ' ');
        if (inputCount > 3){
            showErrorMessage(wordFromInput, EXTRANEOUS_INPUT);
            break;
        }
        editedInputWord = validateAndReturnParsedInput(wordFromInput, inputCount);
        if (editedInputWord != ""){
            parsedUserInput.emplace(to_string(inputCount), editedInputWord);
        } else {
            showErrorMessage(wordFromInput, INVALID_INPUT);
            parsedUserInput.clear();    
            break;
        }
        // Handle end of stream and exit to prevent 
        // extraneous input error from being triggerred
        if (streamOfUserInput.eof()){
            break;
        }
        // Increment parameter count
        inputCount++;
    }
    return parsedUserInput;
}

/**
 * Show invalid input error message
 */
void showErrorMessage(string invalidInput, string message){
    cout << endl;
    if (invalidInput != ""){
        cout << message << invalidInput << " received!" << endl;
    } else {
        cout << message << endl;
    }
    if (message != RETRY_ATTEMPTS_EXHAUSTED){
        showCommandFormatAndExample();
    }
    cout << endl;
}

/**
 * Validate input and return, if invalid, returm empty string
 */
string validateAndReturnParsedInput(string input, short inputCount){
    if (inputCount == 0){
        return isAValidCommand(input) ? input : "";
    } 
    return isAValidNumber(input) ? input : "";
}

/**
 * Check if the command input by user is valid
 */
bool isAValidCommand(string commandToCheck){
    for(short i = 0; i < MAX_COMMANDS; i++){
        if (VALID_COMMANDS.at(i) == stringToUpperCase(commandToCheck)){
            return true;
        }
    }
    return false;
}

/**
 * Check if an input number is valid
 */
bool isAValidNumber(string valueToCheck){
    int dotCounter = 0;
    for(int i = 0; i < valueToCheck.length(); i++){
        if (valueToCheck.at(i) == '.'){
            // If number of '.' > 1, return invalid number
            if (dotCounter > 1){
                return false;
            }
            dotCounter++;
        } else if (!isnumber(valueToCheck.at(i))) {
            return false;
        }
    }
    return true;
}

/**
 * Get the result of requested operation
 */
string getResult(map<string, string> command){

    bool atLeastOneInputIsFloat = isAFloatingPointNumber(command["1"]) || isAFloatingPointNumber(command["2"]);
    double firstNumber = stod(command["1"]);
    double secondNumber = stod(command["2"]);
    double result = performOperation(command["0"], firstNumber, secondNumber);
    return atLeastOneInputIsFloat? to_string(result) : to_string((int) result);
}

/**
 * Perform requested and perform it
 */
double performOperation(string command, double firstNumber, double secondnNumber){
    string formattedCommand = stringToUpperCase(command);
    if (formattedCommand == ADD){
        return addNumbers(firstNumber, secondnNumber);
    }
    if (formattedCommand == SUBTRACT){
        return subtractNumbers(firstNumber, secondnNumber);
    }
    if (formattedCommand == MULTIPLY){
        return multiplyNumbers(firstNumber, secondnNumber);
    }
    // Safely assume it is Division, as invalid commands would have been rejected
    return divideNumbers(firstNumber, secondnNumber);
}

/**
 * Convert string to uppercase
 */
string stringToUpperCase(string inputString){
    string upperCaseString;
    for(int i = 0; i < inputString.length(); i++){
        upperCaseString += toupper(inputString.at(i));
    }
    return upperCaseString;
}

/**
 * Check if the number is a floating point number
 */
bool isAFloatingPointNumber(string valueToCheck){
    for(int i = 0; i < valueToCheck.length(); i++){
        if (valueToCheck.at(i) == '.'){
            return true;
        }
    }
    return false;
}

 /**
  * Add two numbers and returns the result.
  */
 double addNumbers(double firstNumber, double secondNumber){
    return firstNumber + secondNumber;
 }

 /**
  * Subtract two numbers and returns the result.
  */
 double subtractNumbers(double firstNumber, double secondNumber){
    return firstNumber - secondNumber;
 }

 /**
  * Multiply two numbers and returns the result.
  */
 double multiplyNumbers(double firstNumber, double secondNumber){
    return firstNumber * secondNumber;
}

 /**
  * Divide two numbers and returns the result.
  */
 double divideNumbers(double firstNumber, double secondNumber){
    return firstNumber / secondNumber;
}
