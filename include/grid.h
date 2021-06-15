#ifndef Grid_h
	#define Grid_h
	#define GRID_COLS 100
	#define GRID_ROWS 50

	typedef struct {
		unsigned int gridRows;
		unsigned int gridCols;
		unsigned short grid[GRID_ROWS][GRID_COLS];
		unsigned short newGrid[GRID_ROWS][GRID_COLS];
		SDL_Rect renderingGrid[GRID_ROWS][GRID_COLS];
	} Grid;

	void initGrid(Grid* grid) {
		srand(time(NULL));
	
		grid->gridRows = GRID_ROWS;
		grid->gridCols = GRID_COLS;
		
		for (int i = 0; i < grid->gridRows; ++i) {
			for (int j = 0; j < grid->gridCols; ++j) {
				grid->grid[i][j] = rand() % 2;
			}
		}
	}

	void renderGrid(Grid* grid, SDL_Renderer* renderer) {
		for (int i = 0; i < grid->gridRows; ++i) {
			for (int j = 0; j < grid->gridCols; ++j) {
				grid->renderingGrid[i][j].x = j * (WINDOW_WIDTH / GRID_COLS), 
				grid->renderingGrid[i][j].y = i * (WINDOW_HEIGHT / GRID_ROWS), 
				grid->renderingGrid[i][j].w = WINDOW_WIDTH / GRID_COLS, 
				grid->renderingGrid[i][j].h = WINDOW_HEIGHT / GRID_ROWS;

				unsigned short color = grid->grid[i][j];		

				SDL_SetRenderDrawColor(renderer, (color == 0) ? 0 : 255, (color == 0) ? 0 : 255, (color == 0) ? 0 : 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &grid->renderingGrid[i][j]);
			}
		}
	}

	void initBlankGrid(Grid* grid) {
		grid->gridRows = GRID_ROWS;
		grid->gridCols = GRID_COLS;
		
		for (int i = 0; i < grid->gridRows; ++i) {
			for (int j = 0; j < grid->gridCols; ++j) {
				grid->grid[i][j] = 0;
			}	
		}	
	}

	void updateGrid(Grid* grid) {
		for (int i = 0; i < grid->gridRows; ++i) {
			for (int j = 0; j < grid->gridCols; ++j) {
				int liveNeighbors = 0;				

				if (grid->grid[i - 1][j - 1] == 1) liveNeighbors++;
				if (grid->grid[i - 1][j] == 1) liveNeighbors++;
				if (grid->grid[i - 1][j + 1] == 1) liveNeighbors++;
				if (grid->grid[i][j - 1] == 1) liveNeighbors++;
				if (grid->grid[i][j + 1] == 1) liveNeighbors++;
				if (grid->grid[i + 1][j - 1] == 1) liveNeighbors++;
				if (grid->grid[i + 1][j] == 1) liveNeighbors++;
				if (grid->grid[i + 1][j + 1] == 1) liveNeighbors++;
	
				if (grid->grid[i][j] == 1 && liveNeighbors < 2) grid->newGrid[i][j] = 0;
				else if (grid->grid[i][j] == 1 && liveNeighbors > 3) grid->newGrid[i][j] = 0;
				else if (grid->grid[i][j] == 0 && liveNeighbors == 3) grid->newGrid[i][j] = 1;
				else grid->newGrid[i][j] = grid->grid[i][j];
			}
		}
		for (int i = 0; i < grid->gridRows; ++i) {
			for (int j = 0; j < grid->gridCols; ++j) {
				grid->grid[i][j] = grid->newGrid[i][j];
			}
		}
	}

	void addCell(Grid* grid, int x, int y) {
		int xCol = x / (WINDOW_WIDTH / grid->gridCols);
		int yCol = y / (WINDOW_HEIGHT / grid->gridRows);
		if (grid->grid[yCol][xCol] == 0) grid->grid[yCol][xCol] = 1;
		else grid->grid[yCol][xCol] = 0;
	}

#endif
