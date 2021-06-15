#ifndef Window_h
	#define Window_h
	#define WINDOW_WIDTH 800
	#define WINDOW_HEIGHT 500

	struct Dimension {
		unsigned long windowWidth;
		unsigned long windowHeight;
	};

	typedef struct {
		char* title;
		int winX, winY;
		unsigned int windowWidth, windowHeight;
		SDL_Window* window;
	} Window;

	struct Dimension setScreenDimensions() {
		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		struct Dimension screenDimensions = {displayMode.w, displayMode.h};
		return screenDimensions;
	}
	
	void getWindowPos(int* x, int* y, unsigned long screenWidth, unsigned long screenHeight) {
		*x = screenWidth / 2 - WINDOW_WIDTH / 2,
		*y = screenHeight / 2 - WINDOW_HEIGHT / 2;
	}

	Window windowSetup() {
		Window window = {
			.title = "Conway's Game of Life implementation in C/SDL2",
			.windowWidth = WINDOW_WIDTH,
			.windowHeight = WINDOW_HEIGHT
		};
		struct Dimension screenDimensions = setScreenDimensions();
		getWindowPos(&window.winX, &window.winY, screenDimensions.windowWidth, screenDimensions.windowHeight);
		window.window = SDL_CreateWindow(window.title, window.winX, window.winY, window.windowWidth, window.windowHeight, SDL_WINDOW_OPENGL);
		return window;
	}

#endif
