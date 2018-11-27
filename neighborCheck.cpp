// Megan Yu & Andrew Dieken
// ID# Megan: 2263079 
// ID# Andrew: 1968999 
// yu204@mail.chapman.edu 
// dieke102@mail.chapman.edu
// CPSC 350-01
// Assignment 02

#include "neighborCheck.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale>
#include <fstream>

using namespace std;


neighborCheck::neighborCheck(int mode, int pauseInput) 
{
    this->mode = mode;
    this->pauseInput = pauseInput; 
}

neighborCheck::~neighborCheck()
{
    /* Deallocates memory from the grid before the program exits. */
    
    for (int i = 0; i < height; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

/* returns height from first line of specified fileName. Takes in user's file as parameter 
and returns height to be inputted to neighbors funciton*/ 
int neighborCheck::get_height(string fileName) {
    ifstream openFile;
    openFile.open (fileName);
    int lineCount = 1;
    for (string line; getline (openFile, line); ) {
        if (lineCount == 1) {
                height = atoi(line.c_str()); //converts file input 
                lineCount++;
        }
    }
    openFile.close();
    return height;
}
/* returns width from second line of specified fileName. Takes in user's file as parameter 
and returns width to be inputted to neighbors funciton*/ 
int neighborCheck::get_width(string fileName){
    ifstream openFile;
    openFile.open (fileName);
    int lineCount = 2;
    for (string line; getline (openFile, line); ) {
        if (lineCount == 2) {
                width = atoi(line.c_str());
                lineCount++;
        }
    }
    openFile.close();
    return width; 
}

/* not currently in use of program. Originally designed to count X's from grid provided in file, and calculates
density of given grid*/ 
double neighborCheck::get_density(string fileName){
    ifstream openFile;
    openFile.open (fileName);
    int lineCount = 3;
    for (string line; getline (openFile, line); ) {
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == 'X') {
                numOfX++;
            }
            else{
                    //default
            }
        }
    }
    area = height * width *1.0; //fix placement
    density = numOfX/area;
    openFile.close();
    return density;
}

/*parses through grid starting at line 3 of file provided by user, and copies each coordinate into
grid*/ 
void neighborCheck::fileToGrid(string fileName){
    ifstream openFile;
    openFile.open (fileName);
    int lineCount = 0;
    int row = 0;
    for (string line; getline (openFile, line); ) {
        if (lineCount < 2) {
            lineCount++;
            continue;
        }
        for (int i = 0; i < line.length(); ++i) {
            // row should start from 0
            grid[row][i] = line[i];
        }
        row++;
    }
    print_grid();
    openFile.close();
}

/*
*if user decides not to read in a map from their own file. Asks user for height, width and density
    then generates a grid with those coordinates by calling makeGrid and fillGrid functions
*height, width, & density are all defined as ints/double. cin.fail allows program to check if user 
    enters anything other than an int or a double (in case of density) 
*/ 
    
void neighborCheck::ranGrid() {
    cout << "What would you like the the dimensions of the world to be? " << endl;

    cout << "Height: ";
    cin >> height;
    while (cin.fail()){ //if user inputs any non
        cout << "Please enter only integers: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin>>height; 
    }

    cout << "Width: " ;
    cin >> width ;
    while (cin.fail()){
        cout << "Please enter only integers: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin>>width; 
    }

    cout << "What population density would you like? (Enter a decimal between 0.0 and 1.0): " ;
    cin >> density;
    while (cin.fail()){
        cout << "Please enter only integers: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin>>density; 
    }

    grid = new char*[height];
    for (int heightIndex = 0; heightIndex<height; ++heightIndex)
        grid[heightIndex] = new char[width];

    /*
    * fill the newly generated world with '-'
    */
    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            grid[i][j] = '-';
        }
    }

    area = height * width;
    numOfX = ceil (area * density);      
    cout << (density) << endl;    
    makeGrid();
    fillGrid();
    print_grid();
}

/*takes in user inputted height, width and creates an empty grid of those dimensions */
void neighborCheck::makeGrid(){
    grid = new char*[height];
    for (int heightIndex = 0; heightIndex<height; ++heightIndex)
        grid[heightIndex] = new char [width];
    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            grid[i][j] = '-';
        }
    }
}

/*randomly distributes X's in the empty grid created from makeGrid function*/ 
void neighborCheck::fillGrid(){
    for (int i = 0; i < numOfX; i++){
       int rand_row = rand() % height;
       int rand_col = rand() % width;
       while (grid[rand_row][rand_col] == '-'){
            if (grid[rand_row][rand_col]=='-')
                grid[rand_row][rand_col]='X';
            else{
                rand_row = rand() % height;
                rand_col = rand() % width;
            }
        
       }
    }
}

/*outputs grid to terminal or specified location */ 
void neighborCheck::print_grid() 
{
    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            cout<< grid[i][j];
        }
        cout<<endl;
    }  
}

/*takes current grid as parameter and copies it to a temporary grid*/ 
char ** neighborCheck::copy_grid(char ** grid) 
{
    /* Returns a pointer to a dynamically allocated 2D array with its 
    elements copied from another 2D array. */

    char ** new_grid = new char* [height];
    for (int r = 0; r < height; r++) {
        new_grid[r] = new char [width];
        for (int c = 0; c < width; c++) {
            new_grid[r][c] = grid[r][c];
        }
    }
    return new_grid;
}

/* Deallocates memory from a dynamic array*/
void neighborCheck::cleanup(char ** grid)
{
    for (int r = 0; r < height; r++) {
        delete[] grid[r];
    }
    delete[] grid;
}

/* Returns true if the (row, col) is in bounds, false otherwise. */
bool neighborCheck::bounds(int r, int c) //mostly for classic mode. checks to see if its within the grid. 
{
    return r >= 0 && r < height && c >= 0 && c < width;
}

/* Returns true if the (row, col) is a corner, false otherwise. */
bool neighborCheck::corner(int r, int c) // checks to see if its a corner. this is used for all 3 modes. 
{
    return (r == 0 && c == 0) || (r == 0 && c == width - 1) || 
    (r == height - 1 && width == 0) || (r == height - 1 && c == width - 1);
}

/* Returns the number of neighbors at the specified (row, col) according
    to the given mode CLASSIC, DOUGHNUT, or MIRROR. */
int neighborCheck::neighbors(char ** grid, int mode, int r, int c)
{
    int count = 0; 
    
    // corner case for MIRROR mode
    if (mode == MIRROR && corner(r, c)) { //if its mirror mode and its a corner, it automatically has 3 neighbors because it reflects there
        if (grid[r][c] == 'X'){
            count += 3;
        }
            
        /* the following MIRROR corner functions check the rest of the neighbors besides the 3 it already has*/
        
        // upper left MIRROR corner
        if (r == 0 && c == 0) { 
            if (grid[r + 1][c] == 'X') 
                count++;    // lower left reflection
            if (grid[r][c + 1] == 'X')
                count++;    // upper right reflection
        }
        // upper right MIRROR corner
        else if (r == 0 && c == width - 1) { 
            if (grid[r][c - 1] == 'X')
                count++;    // upper left reflection
            if (grid[r + 1][c] == 'X')
                count++;    // lower right reflection
        }
        // lower left MIRROR corner
        else if (r == height - 1 && c == 0) { 
            if (grid[r - 1][c] == 'X')
                count++;    // upper left reflection
            if (grid[r][c + 1] == 'X')
                count++;    // lower right reflection
        }
        // lower right MIRROR corner
        else if (r == height - 1 && c == width - 1) { 
            if (grid[r - 1][c] == 'X')
                count++;    // upper right reflection
            if (grid[r][c - 1] == 'X')
                count++;    // lower left reflection
        }
    }
    
    // up: 
    if (bounds(r - 1, c) && grid[r - 1][c] == 'X')
        count++;    
    else if (mode == DOUGHNUT && !bounds(r - 1, c) && grid[height - 1][c] == 'X')
        count++;
    else if (mode == MIRROR && !bounds(r - 1, c) && !corner(r, c)) {
        if (grid[r][c] == 'X')
            count++;    // top reflection
        if (bounds(r, c - 1) && grid[r][c - 1] == 'X')
            count++;    // upper left reflection
        if (bounds(r, c + 1) && grid[r][c + 1] == 'X')
            count++;    // upper right reflection
    }
    
    // down
    if (bounds(r + 1, c) && grid[r + 1][c] == 'X')
        count++;
    else if (mode == DOUGHNUT && !bounds(r + 1, c) && grid[0][c] == 'X')
        count++;
    else if (mode == MIRROR && !bounds(r + 1, c) && !corner(r, c)) {
        if (grid[r][c] == 'X')
            count++;    // bottom reflection
        if (bounds(r, c - 1) && grid[r][c - 1] == 'X')
            count++;    // bottom left reflection
        if (bounds(r, c + 1) && grid[r][c + 1] == 'X')
            count++;    // bottom right reflection
    }
    
    // left
    if (bounds(r, c - 1) && grid[r][c - 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && !bounds(r, c - 1) && grid[r][width - 1] == 'X')
        count++;
    else if (mode == MIRROR && !bounds(r, c - 1) && !corner(r, c)) {
        if (grid[r][c] == 'X')
            count++;    // left reflection
        if (bounds(r + 1, c) && grid[r + 1][c] == 'X')
            count++;    // bottom left reflection
        if (bounds(r - 1, c) && grid[r - 1][c] == 'X')
            count++;    // top left reflection
    }
        
    // right
    if (bounds(r, c + 1) && grid[r][c + 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && !bounds(r, c + 1) && grid[r][0] == 'X')
        count++;
    else if (mode == MIRROR && !bounds(r, c + 1) && !corner(r, c)) {
        if (grid[r][c] == 'X')
            count++;    // right reflection
        if (bounds(r + 1, c) && grid[r + 1][c] == 'X')
            count++;    // bottom right reflection
        if (bounds(r - 1, c) && grid[r - 1][c] == 'X')
            count++;    // top right reflection
    }
        
    // upper left
    if (bounds(r - 1, c - 1) && grid[r - 1][c - 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && r == 0 && c == 0 && grid[height - 1][width - 1] == 'X')
        count++;    // upper left corner wrap around lower right corner
    else if (mode == DOUGHNUT && !bounds(r - 1, c - 1) && grid[height - 1][c - 1] == 'X')
        count++;    // upper left wrap around to bottom left
        
    // upper right
    if (bounds(r - 1, c + 1) && grid[r - 1][c + 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && r == 0 && c == width - 1 && grid[height - 1][0] == 'X')
        count++;    // upper right corner wrap around lower left corner
    else if (mode == DOUGHNUT && !bounds(r - 1, c + 1) && grid[height - 1][c + 1] == 'X')
        count++;    // upper right wrap around to bottom right
        
    // lower left
    if (bounds(r + 1, c - 1) && grid[r + 1][c - 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && r == height - 1 && c == 0 && grid[0][width - 1] == 'X')
        count++;    // lower left corner wrap around upper right corner
    else if (mode == DOUGHNUT && !bounds(r + 1, c - 1) && grid[0][c - 1] == 'X')
        count++;    // lower left wrap around to upper left
        
    // lower right
    if (bounds(r + 1, c + 1) && grid[r + 1][c + 1] == 'X')
        count++;
    else if (mode == DOUGHNUT && r == height - 1 && c == width - 1 && grid[0][0] == 'X')
        count++;    // lower right corner wrap around upper left corner
    else if (mode == DOUGHNUT && !bounds(r + 1, c + 1) && grid[0][c + 1] == 'X')
        count++;    // lower right wrap around to upper right
    return count;
}

/*takes in the mode of operation and neighbors counted from previous neighbors function and determines
whether or not the cell lives or dies in the next generation*/ 
int neighborCheck::bounds_condition(int mode)
{
    /* Returns the number of cells changed. */
    int cells = 0;
    char ** new_grid = copy_grid(grid);
    
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            
            if ((mode == CLASSIC && neighbors(grid, CLASSIC, r, c) <= 1) || 
                (mode == DOUGHNUT && neighbors(grid, DOUGHNUT, r, c) <= 1) || 
                (mode == MIRROR && neighbors(grid, MIRROR, r, c) <= 1))
                new_grid[r][c] = '-';
 
            else if ((mode == CLASSIC && neighbors(grid, CLASSIC, r, c) == 2) || 
                (mode == DOUGHNUT && neighbors(grid, DOUGHNUT, r, c) == 2) || 
                (mode == MIRROR && neighbors(grid, MIRROR, r, c) == 2))
                continue;
                
            else if ((mode == CLASSIC && neighbors(grid, CLASSIC, r, c) == 3) || 
                (mode == DOUGHNUT && neighbors(grid, DOUGHNUT, r, c) == 3) || 
                (mode == MIRROR && neighbors(grid, MIRROR, r, c) == 3))
                new_grid[r][c] = 'X';
                
            else if ((mode == CLASSIC && neighbors(grid, CLASSIC, r, c) >= 4) || 
                (mode == DOUGHNUT && neighbors(grid, DOUGHNUT, r, c) >= 4) || 
                (mode == MIRROR && neighbors(grid, MIRROR, r, c) >= 4))
                new_grid[r][c] = '-';
                
            if ((grid[r][c] == '-' && new_grid[r][c] == 'X')||
                (grid[r][c] == 'X' && new_grid[r][c] == '-'))
                cells++;    // new cell born
        }
    }
    cleanup(grid);     // delete old grid
    grid = new_grid;
    return cells;
}

/*if user selects option 3 for pauseInput. Does not pause between generations and writes all output
to a filename specified by the user*/ 
void neighborCheck::writeToFile(int cycle)
{
    ofstream outFile;
    outFile.open(file, fstream::app);
    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            outFile << "Cycle: "<< cycle << endl;
            outFile<< grid[i][j];
        }
        outFile<<endl;
    }
    outFile.close();
}

/*initiates the simulation*/
void neighborCheck::run(int answer) 
{

    int cells = -1;
    int cycle = 0;

    if (answer == 3) {
            cout << "What is the name of the file you would like to write to? " ;
            cin >> file ; 

    }
    while (cells != 0) {
        cells = bounds_condition(mode);
        if (answer == 1) {
            sleep(3); 
            cout << "Cycle: "<< cycle << endl;
            print_grid();
        }
        else if (answer == 2) { 
            cout << "Press enter" << endl; 
            cin.ignore() ;
            cout << "Cycle: "<< cycle << endl;
            print_grid();
        }
        else if (answer == 3){
            writeToFile(cycle);
        }
        cycle++;
        //print out the grid and the generation number
    }
    
    cout<< "The program has stabilized."<<endl;
    cout << "Total Cycles: " << cycle << endl;
    cout << ' ' << endl;
    
}