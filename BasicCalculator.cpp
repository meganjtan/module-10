// Megan Tan
// CIS 1202 801
// Aug 9, 2026
// Module 10 - Final Project
// Class Implementation - Basic Calculator

#include "BasicCalculator.h"
using namespace std;

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

void BasicCalculator::setOperand1(double operand1) { this->operand1 = operand1; }
void BasicCalculator::setOperand2(double operand2){ this->operand2 = operand2; }
void BasicCalculator::setResult(double result) { this->result = result; }
void BasicCalculator::setExpression(const char* expression){
    strncpy(this->expression, expression, 49);
    this->expression[49]='\0';
}

double BasicCalculator::getOperand1() const{ return operand1; }
double BasicCalculator::getOperand2() const{ return operand2; }
double BasicCalculator::getResult() const { return result; }
const char* BasicCalculator::getExpression() const { return expression; }

void BasicCalculator::displayInfo(){
    
}