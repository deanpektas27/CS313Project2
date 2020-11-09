//Dean Pektas CS313 Q2 11/8/20

#include <iostream>  
#include <iomanip>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
 
using namespace std; 

//Creating empty stack to store the operands and operators where necessary.
stack<double> Stack;

//Checks if given char in expression is a number.
bool isOperand(char ch)
{
    return isdigit(ch);
}

void evaluateOpr(char c, double op1, double op2)
{
    //switch statement checks what operator is in the expression and applies it to both values.
        switch(c)
        {
            case '+':
                Stack.push(op1 + op2);
                break;
            case '-':
                Stack.push(op1 - op2);
                break;
            case '*':
                Stack.push(op1 * op2);
                break;
            case '/':
                Stack.push(op1 / op2);
                break;
            }    
}

//Used to scan through the given expression and perform operations.
double evaluateExpression(string expression) 
{

    //Scan through each char from the end of the expression to the beginning.
    for(int x = expression.size() - 1; x >= 0; x--) 
    {
        //If given char in expression is a number, convert from string to digit 
        //and store in stack.
       if(isOperand(expression[x]))
       {
           Stack.push(expression[x] - '0');
       }
       //If given char is not a number, its an operator
       else
       {
        //take the first available operands and remove them from stack
           double op1 = Stack.top();
           Stack.pop();
           double op2 = Stack.top();
           Stack.pop();
        //pass through operands to function to perform first operation thats in expression
           evaluateOpr(expression[x],op1,op2);
       }
       

    }

    return Stack.top();
}

//Allows for user to enter a prefix expression for evaluation
int main(){
    string exp;
    cout << "Enter expression" << endl;
    cin >> exp;
    cout << evaluateExpression(exp) << endl;
    return 0;
    
}