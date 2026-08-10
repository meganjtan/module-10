// Megan Tan
// CIS 1202 801
// Aug 9, 2026
// Module 10 - Final Project
// Class Implementation - Basic Calculator

#include "BasicCalculator.h"
using namespace std;

//Constructors
BasicCalculator::BasicCalculator(){
    this->operand1 = 0.0;
    this->operand2 = 0.0;
    this->result = 0.0;
    strncpy(this->expression, "Null", 50);
}

BasicCalculator::BasicCalculator(double operand1, double operand2, double result, const char* expression){
    this->operand1 = operand1;
    this->operand2 = operand2;
    this->result = result;
    strncpy(this->expression, expression, 50);
}

//Setters
void BasicCalculator::setOperand1(double operand1) { this->operand1 = operand1; }
void BasicCalculator::setOperand2(double operand2){ this->operand2 = operand2; }
void BasicCalculator::setResult(double result) { this->result = result; }
void BasicCalculator::setID(int id) { this->id = id; }
void BasicCalculator::setExpression(const char* expression){
    strncpy(this->expression, expression, 49);
    this->expression[49]='\0';
}

//Getters
double BasicCalculator::getOperand1() const{ return operand1; }
double BasicCalculator::getOperand2() const{ return operand2; }
double BasicCalculator::getResult() const { return result; }
int BasicCalculator::getID() const { return id; }
const char* BasicCalculator::getExpression() const { return expression; }

//Other Methods
void BasicCalculator::compute(double op1, double op2, char operation){
    this->operand1=op1;
    this->operand2=op2;
    
    switch(operation){
        case '+':
            result = op1+op2;
            snprintf(expression, sizeof(expression), "%.2f + %.2f", op1, op2); //snprintf - saves contents to cstring expression
            break;
        case '-':
            result = op1-op2;
            snprintf(expression, sizeof(expression), "%.2f - %.2f", op1, op2);
            break;
        case '*':
            result = op1*op2;
            snprintf(expression, sizeof(expression), "%.2f * %.2f", op1, op2);
            break;
        case '/':
            result = op1/op2;
            snprintf(expression, sizeof(expression), "%.2f / %.2f", op1, op2);
            break;
        case '^':
            result = pow(op1, op2);
            snprintf(expression, sizeof(expression), "%.2f ^ %.2f", op1, op2);
            break;
        default: //oops
            result = 0.0;
            snprintf(expression, sizeof(expression), "Invalid operation.");
            break;
    }
}

void BasicCalculator::compute(double op1, int function){ //overloaded compute
    this->operand1=op1;
    this->operand2=0.0;

    switch(function){
        case 1: //sqr root
            result = (op1>=0) ? sqrt(op1) : 0.0;
            snprintf(expression, sizeof(expression), "sqrt(%.2f)", op1);
            break;
        case 2: //sin - input degrees, convert to radians
            result = sin(op1*M_PI / 180.0);
            snprintf(expression, sizeof(expression), "sin(%.2f)", op1);
            break;
        case 3: //cos - ^^
            result = cos(op1*M_PI / 180.0);
            snprintf(expression, sizeof(expression), "cos(%.2f)", op1);
            break;
        case 4: //tan - ^^
            result = tan(op1*M_PI / 180.0);
            snprintf(expression, sizeof(expression), "tan(%.2f)", op1);
            break;
        case 5: //log base 10
            result = (op1>0) ? log10(op1) : 0.0;
            snprintf(expression, sizeof(expression), "log10(%.2f)", op1);
            break;
        case 6: //ln (natural logarithm)
            result = (op1>0) ? log(op1) : 0.0;
            snprintf(expression, sizeof(expression), "ln(%.2f)", op1);
            break;
        default: //oops
            result = 0.0;
            snprintf(expression, sizeof(expression), "Invalid operation.");
            break;
    }
}

void BasicCalculator::displayInfo(){
    cout << left << setw(20) << "Calculation ID: " << id << endl;
    cout << left << setw(20) << "Expression: " << expression << endl;
    cout << left << setw(20) << "Result: " << fixed << setprecision(2) << result << endl;
}