// Megan Yu & Andrew Dieken
// ID# Megan: 2263079 
// ID# Andrew: 1968999 
// yu204@mail.chapman.edu 
// dieke102@mail.chapman.edu
// CPSC 350-01
// Assignment 02

/*The purpose of this assignment is to simulate bacteria spawning in a given environment. Each cell's status is 
determined by the amount of neighbors that are alive */ 

#include "neighborCheck.h"
#include "global.h"



int main() {

    int mode;
    int pauseInput;
    string gridInput;
    string fileName;
    
    cout << "Welcome to Game of Life!"<<endl;
    
    cout << "Please select the mode you would like to play in (1, 2 or 3):" << endl;
    cout << "1)Classic Mode" << endl;
    cout << "2)Doughnut Mode" << endl;
    cout << "3)Mirror Mode" << endl;
    cin >> mode; 
    
    cout << "Please choose an option (1, 2, 3)" << endl;
    cout << "1) Pause breifly between generations" << endl;
    cout << "2) Press enter between generations" << endl;
    cout << "3) Write the results to a text file" << endl;
    cin >> pauseInput;

    neighborCheck game(mode, pauseInput);  
    
    cout << "Do you wish to provide your own map file (yes/no)" << endl;
      cin >> gridInput ;
      if (gridInput == "yes") {
        //call in file reader function
        cout<< "Enter the file name: ";
        cin >> fileName;
        height = game.get_height(fileName);
        width = game.get_width(fileName);
        game.makeGrid();
        density = game.get_density(fileName);

        game.fileToGrid(fileName);        
      }
      else if (gridInput == "no") {
          game.ranGrid() ;
      }
        game.run(pauseInput);
    
    return 0;
}