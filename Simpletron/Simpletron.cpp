//
//  Simpletron.cpp
//  Simpletron
//
//  Created by Ahmed Ramy on 4/28/20.
//  Copyright © 2020 Ahmed Ramy. All rights reserved.
//

#include "Simpletron.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

/*
    Constructor used to initialize all memory locations to 0 and all private variables to 0
 */
Simpletron::Simpletron() {
    for(int i = 0; i < 100; i++)
    {
        memory[i] = 0;
    }
    accumulator = 0; // represent the accumulator registor
    instructionCounter = 0; // keep track of the location in memory that contains the instruction being performed
    operationCode = 0; // indicate the operation currently being performed
    operand = 0; // indicate the memory location on which the current instruction operates
    instructionRegister = 0; // transfer the next instruction to be performed from memory to here
} // end constructor

void Simpletron::enterSML()
{
    int instructionNum = 0;
    int input = 0;
    
    cout << "*** Welcome to Simpletron! ***\n" << endl;
    cout << "*** Please enter your program one instruction ***" << endl;
    cout << "*** (or data word) at a time. I will type the ***" << endl;
    cout << "*** location number and a question mark (?).  ***" << endl;
    cout << "*** you then type the word for that location. ***" << endl;
    cout << "*** Type the sentinel -99999 to stop entering ***" << endl;
    cout << "*** your program. ***" << endl;
    
    while(instructionNum < 100)
    {
        if(instructionNum < 10)
        {
            cout << 0;
        }
        cout << instructionNum << " ? ";
        cin >> input;
        
        //Input is invalid. Prompt user again
        while((input < -9999 && input != -99999) || input > 9999)
        {
            cout << "User input invalid. Please try again." << endl;
            if(instructionNum < 10)
            {
                cout << 0;
            }
            cout << instructionNum << " ? ";
            cin >> input;
        }
        if(input == -99999)
        {
            break;
        }
        else{
            memory[ instructionNum ] = input;
            instructionNum++;
        }
    }
    
    cout << "*** Program loading completed ***" << endl;
    cout << "***  Program exection begins  ***" << endl;
}

void Simpletron::execute()
{
    while(instructionCounter < 100)
    {
        instructionRegister = memory[ instructionCounter ];
        SML();
    }
}

void Simpletron::SML()
{
    int tmp = 0;
    // Split the instruction into the opcode and operand
    operationCode = instructionRegister / 100;
    operand = instructionRegister % 100;
    ++instructionCounter;
    
    switch (operationCode) {
        case READ:
            cout << "Input number (-9999 to 9999): ";
            cin >> tmp;
            while(tmp < -9999 || tmp > 9999)
            {
                cout << "An error has occured please enter a number between -9999 and 9999: ";
                cin >> tmp;
            }
            memory[operand] = tmp;
            break;
        case WRITE:
            cout << memory[operand] << endl;
            break;
        case LOAD:
            accumulator = memory[ operand ];
            break;
        case STORE:
            memory[ operand ] = accumulator;
            break;
        case ADD:
            if(accumulator + memory[ operand] > 9999 || accumulator + memory[ operand ] < -9999)
            {
                error("overflow");
            } else{
                accumulator += memory[ operand];
            }
            break;
        case SUBTRACT:
            if( accumulator - memory[ operand ] > 9999 || accumulator - memory[ operand] < -9999)
            {
                error("overflow");
            } else {
                accumulator -= memory[ operand];
            }
            break;
        case DIVIDE:
            if(memory[ operand ] == 0){
                error("divide0");
            } else {
                accumulator /= memory[ operand];
            }
            break;
        case MULTIPLY:
            if (accumulator * memory[operand] > 9999 || accumulator * memory[ operand] < -9999){
                error("overflow");
            } else {
                accumulator *= memory[ operand];
            }
            break;
        case BRANCH:
            instructionCounter = operand;
            break;
        case BRANCHEG:
            if( accumulator > 0)
            {
                instructionCounter = operand;
            }
            break;
        case BRANCHZERO:
            if( accumulator == 0)
            {
                instructionCounter = operand;
            }
        case HALT:
            cout << "*** Simpletron execution terminated ***" << endl;
            printmem();
            instructionCounter = 100;
            break;
        default:
            cout << "Invalid input";
    }
}


void Simpletron::printmem(){
    cout << "REGISTERS:" << endl;
    cout << "accumulator:             " << showpos << setw(5) << setfill('0') << internal << accumulator << endl;
    cout << "instructionCounter:        " << showpos << setw(2) << setfill('0') << internal << instructionCounter << endl;
    cout << "instructionRegister:     " << showpos << setw(5) << setfill('0') << internal << instructionRegister << endl;
    cout << "operationCode:             " << showpos << setw(2) << setfill('0') << internal << operationCode << endl;
    cout << "operand:                   " << showpos << setw(2) << setfill('0') << internal << operand << endl;
    cout << "" << endl;
    cout << "MEMORY:" << endl;
    cout << "   0     1     2     3     4     5     6     7     8     9" << endl;
    // Print out the memory block.
    cout << "00 ";
    for (int i=0; i<10 ; i++){
        cout << showpos << setw(5) << setfill('0') << internal  << memory[i] << " ";
    }
    cout << endl;
    for (int s=10; s<100; s=s+10){
        cout << noshowpos << s << " ";
        for (int i=0; i<10; i++){
            cout << showpos << setw(5) << setfill('0') << internal  << memory[s+i] << " ";
        }
        cout << endl;
    }
}

void Simpletron::error(string s){
    if (s == "overflow"){
        cout << "An overflow error has occured. The program will now exit..." << endl;
        instructionCounter = 100;
        printmem();
    }
    if (s == "divide0" ){
        cout << "A divide by zero error has occured. The program will now exit..." << endl;
        instructionCounter = 100;
        printmem();
    }



}
