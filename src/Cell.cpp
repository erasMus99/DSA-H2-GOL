#include "Cell.h"
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <iostream>

// Let's define our cell class here


using namespace std;

Cell::Cell(unsigned int w, unsigned int h)
{
	width = w;
	height = h;
	len = w * h;

	cells = new unsigned char[len];			// Creating the cells 'array', that's why we needed len
	temp_cells = new unsigned char[len];	// Same for the temporary cells

	memset(cells, 0, len);					// Making sure that the unsigned char array is really at 0. We don't really like those random memories values
}

Cell::~Cell()
{
	delete[] cells;							// I'm still scared of you
	delete[] temp_cells;
}

void Cell::SettingCell(unsigned int x, unsigned int y)
{
	int w = width;
	int h = height;

	int xLeft, xRight, yAbove, yBelow;							// Let's create our variables needed to move around and calculate offset
	unsigned char* pointer_for_cell = cells + (y * w) + x;		// And our pointer

	xLeft = (x == 0) ? w - 1 : -1;								// Using ternary operators to check the conditions. The borders of the map is also taken into account
	xRight = (x == (w - 1)) ? -(w - 1) : 1;
	yAbove = (y == 0) ? len - w : -w;
	yBelow = (y == (h - 1)) ? -(int)(len - w) : w;

	*(pointer_for_cell) |= 0x01;								// Set the first bit to 1, using XOR in case there is already a value at the memory emplacement

	*(pointer_for_cell + yAbove + xLeft) += 0x02;				// Changing the bits for the sucessive count of neighbours
	*(pointer_for_cell + yAbove) += 0x02;
	*(pointer_for_cell + yAbove + xRight) += 0x02;
	*(pointer_for_cell + xLeft) += 0x02;
	*(pointer_for_cell + xRight) += 0x02;
	*(pointer_for_cell + yBelow + xLeft) += 0x02;
	*(pointer_for_cell + yBelow) += 0x02;
	*(pointer_for_cell + yBelow + xRight) += 0x02;

}

void Cell::ClearingCell(unsigned int x, unsigned int y)
{
	int w = width;
	int h = height;

	int xLeft, xRight, yAbove, yBelow;							// Let's create our variables needed to move around and calculate offset
	unsigned char* pointer_for_cell = cells + (y * w) + x;		// And our pointer

	xLeft = (x == 0) ? w - 1 : -1;								// Using ternary operators to check the conditions. The borders of the map is also taken into account
	xRight = (x == (w - 1)) ? -(w - 1) : 1;
	yAbove = (y == 0) ? len - w : -w;
	yBelow = (y == (h - 1)) ? -(int)(len - w) : w;

	*(pointer_for_cell) &= ~0x01;								// Set the first bit to 0, using bitwise and operation

	*(pointer_for_cell + yAbove + xLeft) -= 0x02;				// Changing the bits for the sucessive count of neighbours
	*(pointer_for_cell + yAbove) -= 0x02;
	*(pointer_for_cell + yAbove + xRight) -= 0x02;
	*(pointer_for_cell + xLeft) -= 0x02;
	*(pointer_for_cell + xRight) -= 0x02;
	*(pointer_for_cell + yBelow + xLeft) -= 0x02;
	*(pointer_for_cell + yBelow) -= 0x02;
	*(pointer_for_cell + yBelow + xRight) -= 0x02;
}

int Cell::CellState(int x, int y)
{
	unsigned char* pointer_for_cell = cells + (y * width) + x;	// Get our pointer to the correct location
	return *pointer_for_cell & 0x01;							// Return the first bit, the least significant one, where the state is stored
}

void Cell::MoveToNextGen()
{
	unsigned int x;												// Declaring the necessary variables
	unsigned int y;
	unsigned int count;											// Used to count the number of neighbors
	unsigned int h = height;
	unsigned int w = width;
	unsigned char* pointer_for_cell;
    const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);       // Added to fix the errors of rendering

	memcpy(temp_cells, cells, len);								// Copying to the temp cell to keep an unaltered version in case we need to rollback to it

	pointer_for_cell = temp_cells;								// Let's process the cells 

	for (y = 0; y < h; y++)
	{
		x = 0;
		do
		{
			while (*pointer_for_cell == 0)						// The cell is dead and their is no neighbours so skip them
			{
				pointer_for_cell++;								// Let's advance to the next cell
				if (++x >= w) goto RowDone;						// If all the cells in the row are dead with no neighbours move to the next row
			}

			count = *pointer_for_cell >> 1;						// Now we're left we cells that are alive or have neighbours, so let's count the number of neighbours
			if (*pointer_for_cell & 0x01)
			{
				if ((count != 2) && (count != 3))				// If the cell is alive but don't have the necessary neighbours we need to clear it
				{
					ClearingCell(x, y);
				}
			}
			else
			{
				if (count == 3)									// If the cell is dead but have three neighbours we need to Set it alive
				{
					SettingCell(x, y);

				}
			}

			pointer_for_cell++;									// And now we go to the next cell byte

		} while (++x < w);
	RowDone:;													// When the row is done we go to the next
	}
}

bool check_25()
{
    int i = (rand() % 4) + 1;                                   // Generate random number between 1 and 4
    return (i == 1);                                            // If i == 1 then it's a 25% chance that the cell need to be alive 
}

void Cell::InitTheGame()
{
	unsigned int x;
	unsigned int y;
	unsigned int init_len;

	cout << "Started Initialization" << endl;
	srand(time(nullptr));
	init_len = (width * height) / 2;								// Get ~50% of the map where their will be random cell
	do
	{
		x = rand() % (width - 1);									// We do this to be sure that the value we get is inside the map
		y = rand() % (height - 1);
		if (CellState(x, y) == 0 && check_25())                     // If the cell is dead and is in the ~25% chance Set it alive
			SettingCell(x, y);

	} while (--init_len);
}