// Megan Tan
// CIS 1202 801
// Aug 9, 2026
// Module 10 - Final Project
// Class Specification - Basic Calculator

#ifndef BASIC_CALCULATOR_H
#define BASIC_CALCULATOR_H

#include <cstring>
using namespace std;

class BasicCalculator{
    private: 
        double operand1;
        double operand2;
        double result;
        char expression[50];

    public: 
        BasicCalculator();
        BasicCalculator(double operand1, double operand2, double result, const char* expression);

        void setOperand1(double operand1);
        void setOperand2(double operand2);
        void setResult(double result);
        void setExpression(const char* expression);

        double getOperand1() const;
        double getOperand2() const;
        double getResult() const;
        const char* getExpression() const;

        virtual void displayInfo();
};

#endif 
