#include "Cell.h"

#define CELL_SIZE 30

int main()
{


    unsigned int cell_width = 800;                      // Setting the cell width
    unsigned int cell_height = 600;                     // Setting the cell height

    unsigned long gen = 0;                              // This variable will be used to count the generations


    Cell current_map(cell_width * CELL_SIZE, cell_height * CELL_SIZE);          // Creating the cell array based on the window size
    current_map.InitTheGame();                          // Initialize the Game


        gen++;                                          // Update the generation to count them



        current_map.MoveToNextGen(window, cell);        // Calculate the next generation and update buffer

                
		window.display();

	}

	return 0;
}
