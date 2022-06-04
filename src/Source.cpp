#include "Cell.h"

// Define the time stop here for the display
#define RATE 1

// (If RATE == 1) then sleep for 2 seconds
#define SLEEP 2000


int main()
{

    
    SDL_Init(SDL_INIT_VIDEO);                           // Initializing the SDL window

    SDL_Window *window = NULL;                          // Create the pointer to the window and surface
    SDL_Surface *surface = NULL;
    unsigned int map_width = 500;                                 // This will be used for the cell map size
    unsigned int map_height = 500;
    unsigned int cell_size = 1;
    unsigned int surface_width = map_width * cell_size;           // And here even if it doesn't change anything yet 
    unsigned int surface_height = map_height * cell_size;

    // Create the window and SDL surface
    window = SDL_CreateWindow("Conway's Game of Life DSA H2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, surface_width, surface_height, SDL_WINDOW_SHOWN);
    surface = SDL_GETWindowSurface(window);


    unsigned long gen = 0;                              // This variable will be used to count the generations


    Cell current_map(map_width, map_height);            // Creating the cell array based on the window size
    current_map.InitTheGame();                          // Initialize the Game

    // SDL Event
    SDL_Event e;

    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT) quit = true;

        gen++;                                          // Update the generation to count them

        current_map.MoveToNextGen(surface);             // Calculate the next generation and update buffer

        SDL_UpdateWindowSurface(window);                // Update the window buffer with the new cells
#if RATE
        SDL_Delay(SLEEP);
#endif
	}

    SDL_DestroyWindow(window);                          // Destroy the window
    SDL_Quit();

    cout << "The number of generations: " << gen << endl;

	return 0;
}
