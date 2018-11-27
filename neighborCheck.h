// Megan Yu & Andrew Dieken
// ID# Megan: 2263079 
// ID# Andrew: 1968999 
// yu204@mail.chapman.edu 
// dieke102@mail.chapman.edu
// CPSC 350-01
// Assignment 02

#ifndef NEIGHBORCHECK
#define NEIGHBORCHECK 

#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "global.h"

// Macros are global variables of renamed integers.
#define CLASSIC 1
#define DOUGHNUT 2
#define MIRROR 3
using namespace std;

class neighborCheck
{
    private:
        //string file_name;
        int mode;       // classic mirror or doughnut
        int pauseInput; // wait before next gen, press enter, or write to file
        char** grid;

    public:
        string file; //file if user decides to import a file map
        neighborCheck();
        neighborCheck(int mode, int pauseInput);
        ~neighborCheck();
        char ** copy_grid(char ** old_grid);
        void cleanup(char ** grid);
        bool bounds(int r, int c);
        bool corner(int r, int c);
        int neighbors(char ** grid, int mode, int r, int c);
        int bounds_condition(int mode);
        void run(int answer);
        void print_grid();
        int get_height(string fileName);
        int get_width(string fileName);
        double get_density(string fileName);
        void printFileGrid(string fileName);
        void ranGrid();
        void fillGrid();
        void makeGrid();
        void writeToFile(int cycle);
        void fileToGrid(string fileName);
        double area;
        int numOfX;
};
#endif
