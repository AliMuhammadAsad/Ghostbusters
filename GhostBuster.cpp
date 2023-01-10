#include "GhostBuster.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Currently rows and columns are set to 8, however your game implementation should work for any other number
const int rows = 8 , cols = 8;

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
char* grid = NULL;

// Ghost will be placed over this location
int ghostRow, ghostCol;

// *****************************************************************************************************
// No change zone: Don't change anything until the next stars line
// *****************************************************************************************************

// Don't Change it: Screen width and height values
const int width = 1000, height = 600;

// Don't Change: This function is dealing with SDL and currently it's complete. Don't change anything here
void drawOneBlock(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col, char sym){
    int xbox = width/cols;
    int ybox = height/rows;
    SDL_Rect src;
    switch(sym){
        case 'L': src = {141, 7, 104, 113}; break;
        case 'S': src = {427, 12, 129, 103}; break;
        case 'T': src = {268, 10, 130, 111}; break;
        case 'B': src = {0, 3, 114, 111}; break;
        case 'G': src = {571, 0, 123, 121}; break;
        case 'Z': src = {571, 0, 25, 25}; break;
        case 'F': src = {707, 16, 90, 86}; break;
    }
    SDL_Rect mov = { xbox*col, ybox*row, xbox - 10, ybox - 10};
    SDL_RenderCopy(renderer, texture, &src, &mov);
}

void drawBlocks(SDL_Renderer* renderer, SDL_Texture* texture){
    // Call drawOneBlock for all of the blocks of grid
    // for example to draw a snake over block (3, 5) you call it this way:
    // drawOneBlock(renderer, texture, 3, 5, 'S');
    if(grid == NULL) return;
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            drawOneBlock(renderer, texture, i, j, grid[i*cols+j]);
        }   
    }
}

// *****************************************************************************************************
// No change zone ends here
// *****************************************************************************************************



// To Do zone: 

bool ended = false;

void initialize(){
    // Create memory for grid here, it should be one dimensional array.
    // The memory should be rows*cols size.
    grid = new char[rows * cols];
    // Initialize entire grid with 'L' so that locks are displayed all over
    for(int i = 0; i < rows*cols; i++)
        grid[i] = 'L';
    // generate two random numbers and store in ghostRow and ghostCol variables
    int r1 = rand() % rows; int r2 = rand() % cols;
    ghostRow = r1; ghostCol = r2;

}

void huntGhost(int x, int y){
    // this function is called every time you click on the screen
    // x, y are screen coordinates, you need to identify the block from these coordinates and using screen width and height values
    // each block size is width/cols x height/rows
    // according to game rules you need to put appropriate character in the grid for that block
    if(ended == true)
        return;

    // Place 'S' to draw a snake
    // place 'T' to draw a turtle
    // place 'B' to draw a bunny

    int x_box = width / cols; int y_box = height / rows; //Screen Coordinates with size width/cols and height/rows
    int col_block = x / x_box; int row_block = y / y_box; //position of block on the grid

    //Distance from clicked block to the ghost block - calculated using distance formula
    int dist_to_ghost = sqrt((ghostCol - col_block)*(ghostCol - col_block) + (ghostRow - row_block)*(ghostRow - row_block));
    cout << "The ghost is " << dist_to_ghost << " block(s) away from your clicked position" << endl;

    //Distance can be of varying blocks, thus different cases for displaying different figures on the clicked location
    if(dist_to_ghost == 0 || dist_to_ghost == 1)
        grid[(row_block * cols) + col_block] = 'S'; 
    /*Our index for grid is taken like this as the array is one dimensional, then if we visualize it as a n x n grid,
    then whatever our row block will be, we can multiply it by the total columns to get to the desired row we want, then 
    we can just add the column block we have to move that many spaces in that particular row to get to our desired column block too
    and thus our desired position on the grid */
    else if(dist_to_ghost == 2 || dist_to_ghost == 3)
        grid[(row_block * cols) + col_block] = 'T';
    else if(dist_to_ghost == 4)
        grid[(row_block * cols) + col_block] = 'B';
    else if(dist_to_ghost > 4){
        int random_fig = rand() % 3;
        if(random_fig == 2){
            grid[(row_block * cols) + col_block] = 'B';
        }
        else if(random_fig == 1){
            grid[(row_block * cols) + col_block] = 'T';
        }
        else if(random_fig == 0){
            grid[(row_block * cols) + col_block] = 'S';
        }
    }
}

void bustGhost(int x, int y){
    // this function is called when you right-click
    // it should work only one time, and you decide whether game is won or failed
    // once the game is won/failed, nothing in game should change anymore.
    // according to game rules you need to put appropriate character in the grid for that block
    // place 'S' to draw snake, when the game is won //Place 'G' to draw ghost when the game is won***
    // place 'F' to draw failed symbol, when the game is failed
    if(ended == true)
        return;

    int x_box = width / cols; int y_box = height / rows; //Screen Coordinates with size width/cols and height/rows
    int col_block = x / x_box; int row_block = y / y_box; //position of block on the grid
    //This is done again to compare against the value of the ghost blocks,

    if (col_block == ghostCol && row_block == ghostRow)
        grid[(row_block * cols) + col_block] = 'G';
    else
        grid[(row_block * cols) + col_block] = 'F';

    ended = true; 
    //ended = true indicates that the game has ended - either you lost or you won - thus no other task should be done now
    //Since bustGhost can only be called one time, ended must be set here to stop the game and return win or lose.
    /* Ohkay so I was wrong apparently, the game freezes with either the picture of the Ghost or Fail, it doesn't show
    win or lose, so if the game freezes at Fail, you lose. If game freezes with ghost, you win. */
    /*Can we display win or lose thought? */
}

void quitGhostBuster(){
    // delete the grid here
    delete [] grid;
}