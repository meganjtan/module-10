// Megan Tan
// CIS 1202 801
// Aug 9, 2026
// Module 10 - Final Project
// Class Specification - Basic Calculator

#ifndef BASIC_CALCULATOR_H
#define BASIC_CALCULATOR_H

#define _USE_MATH_DEFINES //to get M_PI pi
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

class BasicCalculator{
    private: 
        double operand1;
        double operand2;
        double result;
        char expression[50];
        int id;

    public: 
        //constructors
        BasicCalculator();
        BasicCalculator(double operand1, double operand2, double result, const char* expression);

        //setters
        void setOperand1(double operand1);
        void setOperand2(double operand2);
        void setResult(double result);
        void setExpression(const char* expression);
        void setID(int id);

        //getters
        double getOperand1() const;
        double getOperand2() const;
        double getResult() const;
        const char* getExpression() const;
        int getID() const;

        //other methods
        void compute(double op1, double op2, char operation);
        void compute(double op1, int function);
        virtual void displayInfo();
};

#endif 
