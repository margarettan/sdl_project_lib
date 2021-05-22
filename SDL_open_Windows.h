#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
//#include "Image_contro.h"
//#include"ImageData_control.h"

struct Super_point{
	int x;
	int y;
};

struct Window_data {
	int WIDTH, HEIGHT;
	SDL_Window* window; // = NULL; // The window we'll be rendering to
	SDL_Renderer* renderer; // = NULL; // The window renderer
	Window_data(int WIDTH_in, int HEIGHT_in) {
		WIDTH = WIDTH_in;
		HEIGHT = HEIGHT_in;
		window = NULL; // The window we'll be rendering to
		renderer = NULL; // The window renderer
	 }
	//int (*open_window)(Window_data Win_data) = &InitSDL; // ok 
	//void (*close_window)(Window_data Win_data) = &CloseSDL;
};


inline int open_window(Window_data &Win_data) // buile sdl
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		// Error Handling
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}

	// Create window
	// SDL_WINDOWPOS_UNDEFINED: Used to indicate that you don't care what the window position is.
	Win_data.window =SDL_CreateWindow("OOP SDL Tutorial", 50, 50, Win_data.WIDTH, Win_data.HEIGHT, SDL_WINDOW_SHOWN);
	if (Win_data.window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 2;
	}
	// Initialize PNG loading	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 3;
	}
	// Create renderer
	Win_data.renderer = SDL_CreateRenderer(Win_data.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Win_data.renderer == NULL)
	{
		SDL_DestroyWindow(Win_data.window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 5;
	}

	return 0;
}

inline void close_window(Window_data Win_data) // close sdl 
{
	// Destroy renderer	
	// Destroy window	
	// Quit Image subsystem
	// Quit SDL subsystems
	SDL_DestroyRenderer(Win_data.renderer);
	SDL_DestroyWindow(Win_data.window);
	IMG_Quit();
	// Shutdown and cleanup the truetype font API.	
	SDL_Quit();
}