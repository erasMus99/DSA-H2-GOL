#pragma once
// The pseudo code for this faster implementation
// of Cgol is from Michael Abrash's Graphic programming book

/*
* In Michael Abrash's book, the cells are stored inside 8-bit chars.
* The 0th bit represent the cell state: Dead or Alive (we love those Wanted Posters ;) )
* Then we use the remaining bits to represent the number of neighbours.
*/

#define CELL_SIZE 30                                        // Used for the rendering
#include <SDL2/SDL.h>

class Cell
{
public:
	Cell(unsigned int w, unsigned int h);					// Basic constructor
	~Cell();												// I'm scared of destructors	
	void SettingCell(unsigned int x, unsigned int y);		// As it said here we sett the cells
	void ClearingCell(unsigned int x, unsigned int y);		// And here we Clear them
	int CellState(int x, int y);							// With this we can go and fetch the state of a Cell
	void MoveToNextGen(SDL_Surface* surface, unsigned int cell_size, unsigned int surface_width);				// Allow the Game to move to it's new generation, while checking and putting in place all the correct rules
	void InitTheGame();					                    // Used to Init the Game based on a predifine pattern
private:
	unsigned char* cells;									// As said, we use a unsigned char to store our cells
	unsigned char* temp_cells;
	unsigned int width;
	unsigned int height;
	unsigned int len;										// We also need a len to be able to know the total len of the map
    unsigned int map_width;                                 // This will be used for the cell map size
    unsigned int map_height;
    unsigned int cell_size;                                                                           
    unsigned int surface_width;                             // And here even if it doesn't change anything yet 
    unsigned int surface_height;
};
