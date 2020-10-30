//
//  Simpletron.hpp
//  Simpletron
//
//  Created by Ahmed Ramy on 4/28/20.
//  Copyright © 2020 Ahmed Ramy. All rights reserved.
//

#ifndef Simpletron_hpp
#define Simpletron_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

#endif /* Simpletron_hpp */
const int READ = 10;
const int WRITE = 11;
const int LOAD = 20;
const int STORE = 21;
const int ADD = 30;
const int SUBTRACT = 31;
const int DIVIDE = 32;
const int MULTIPLY = 33;
const int BRANCH = 40;
const int BRANCHEG = 41;
const int BRANCHZERO = 42;
const int HALT = 43;

class Simpletron
{
public:
    Simpletron();
    void enterSML();
    void execute();
    void SML();
    
private:
    
    void error(string);
    void printmem();
    int memory[100];
    int accumulator;
    int instructionCounter;
    int operationCode;
    int operand;
    int instructionRegister;
};
