//Dean Pektas CS313 Q6 11/8/20

#include <iostream>  
#include <iomanip>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std; 

//Creating empty stack to store string
stack<string> Stack;

//Creating empty string var to store expression TEMPORARILY.
string plate = "";

void emptyTemp()
{
        //place variable into stack.
        Stack.push(plate);
        //empty out variable once its been pushed into stack.
        plate = "";

}

void writeToPlate(char exp)
{
        //if not empty, concatenate expression into temporary var.
        plate = plate + exp;
}

void evaluateExpression(string expression) 
{
    //Go through each char in the string and store in stack.
    for(int x = 0; x < expression.length(); x++) 
    {
        //check for empty space in index of string expression.
        if(expression[x] == ' ')
        {
            emptyTemp();
        }
        else
        {
            writeToPlate(expression[x]);
        }
        
    }

    Stack.push(plate);

    //once finished pushing expression into stack, make sure stack not empty,
    //the end of the expression starts at the top of the stack,
    //insert end of expression into temporary var and print it.
    while(!Stack.empty())
        plate = Stack.top();
        cout << plate << " ";
        Stack.pop();
    }
    cout << endl;

}

int main(){
    string s = "This is a test";
    evaluateExpression(s); 
    return 0;

}