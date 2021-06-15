#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "include/window.h"
#include "include/grid.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	Window window = windowSetup();
	SDL_Window* gameWindow = window.window;
	SDL_Renderer* renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Grid grid;
	initGrid(&grid);
	
	unsigned int globalTime = 0;
	SDL_Event event;
	bool running = true;
	bool clicked = false;
	bool simulationRunning = false;
	char* simulationState = "DRAWING";
	while (running) {

		globalTime++;		

		if (globalTime % 10 == 0 && simulationRunning) updateGrid(&grid);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) clicked = true;
			else if (event.type == SDL_MOUSEBUTTONUP) clicked = false;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_p) {
					printf("Simulation running...\n");
					simulationState = "RUNNING";
					simulationRunning = true;
				} else if (event.key.keysym.sym == SDLK_c) {
					printf("Simulation cleared...\n");
					simulationRunning = false;
					simulationState = "DRAWING";
					for (int i = 0; i < grid.gridRows; ++i) {
						for (int j = 0; j < grid.gridCols; ++j) {
							grid.grid[i][j] = 0;
						}
					}
				} else if (event.key.keysym.sym == SDLK_SPACE) {
					printf("Simulation paused...\n");
					simulationState = "PAUSED";
					simulationRunning = false;
				} else if (event.key.keysym.sym == SDLK_e) {
					printf("Exiting simulation...\n");
					running = false;
					simulationState = "EXITING";
				}
			}

			if (clicked) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				addCell(&grid, x, y);
			} else if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}

		SDL_RenderClear(renderer);
	
		renderGrid(&grid, renderer);
	
		for (int i = 0; i < grid.gridRows; ++i) {
			for (int j = 0; j < grid.gridCols; ++j) {
				SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 0, i * WINDOW_HEIGHT / grid.gridRows, WINDOW_WIDTH, i * WINDOW_HEIGHT / grid.gridRows);
				SDL_RenderDrawLine(renderer, j * WINDOW_WIDTH / grid.gridCols, 0, j * WINDOW_WIDTH / grid.gridCols, WINDOW_HEIGHT);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
