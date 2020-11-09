//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
//Commented by Dean Pektas CS313
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; 

void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    //keeps track of if given expression is valid
    bool expressionOk;

    char ch;
    stackType<double> stack(100);
    //allows for reading from a file.
    ifstream infile;
    //used to create file and to write information to file.
    ofstream outfile;
 
    //opens file so input operations can be performed on file.
    infile.open("RpnData.txt");

    //if infile cannot open the file, will exit and not continue the program.
    if (!infile)
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }

    //opens file so output operations can be performed on file. 
    outfile.open("RpnOutput.txt");

    //Sets output of float numbers in a fixed decimal format.
    outfile << fixed << showpoint;
    //outputs the amount of decimal places to be displayed, in this case its 2.
    outfile << setprecision(2); 
    //reads file and stores in ch.
    infile >> ch;
    //While loop used to read through entire input file.
    while (infile)
    {
        //initialize stack so each character can be placed in stack and used for output
        stack.initializeStack();
        expressionOk = true;
        outfile << ch;

        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 

    //stop reading from and writing to files, closes files.
    infile.close();
    outfile.close();

    return 0;

} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    //while loop scans through each char in expression
    while (ch != '=')
    {
    //while given char does not equal to '=',
    //if char contains '#', read from file and store into num, output num with a 
    //space onto output file.
        switch (ch)
        {
        case '#': 
            inpF >> num;
            outF << num << " ";
            //if stack isnt full, add num to the stack.
            if (!stack.isFullStack())
                stack.push(num);
            else
            {
            //if stack IS full, do not overflow and terminate.
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default: 
        //passes current stack and output into further evaluation
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if no error with expression, write into ch and output it.
        {
            inpF >> ch;
            outF << ch;

            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression.

//verify stack can perform operations on and then perform them.
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    //checks if stack is empty, fails evaluation.
    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
    //set op2 to the top of the stack and remove that value from the stack.
        op2 = stack.top();
        stack.pop();
    //checks if stack is empty once the top element of the stack is removed.
        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
        //set op1 to the current top of stack, remove that value from stack.
            op1 = stack.top();
            stack.pop();
        //perform specific operation on top two values in the stack based on
        //what ch is when it was passed into this function.
            switch (ch)
            {
            case '+': 
                stack.push(op1 + op2);
                break;
            case '-': 
                stack.push(op1 - op2);
                break;
            case '*': 
                stack.push(op1 * op2);
                break;
            case '/': 
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            //any operator that is not listed above is considered illegal.
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())//if stack is not empty, store top of stack
                               //into result and remove that value from the stack. 
        {
            result = stack.top();
            stack.pop();

            if (stack.isEmptyStack())//if stack is empty, print results.
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult
