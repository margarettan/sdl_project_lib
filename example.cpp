/* Alphar: 2021.04.17 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include "SDL_image.h"  // Using SDL2 image extension library 
#include "SDL_open_Windows.h"
#include "ImageData.h"

//Screen dimension constants
/*const int WIDTH = 800;
const int HEIGHT = 600;*/
const int KFRAME = 28;
const int PFRAME = 10;
const int SFRAME = 12;

const int SOLID = 100;
const int SHADED = 101;
const int BLENDED = 102;


/*struct ImageData {	
	SDL_Texture* texture;
	int width;
	int height;
	int num;
	int wn;
	int hn;
};*/



/*int initSDL(); // Starts up SDL and creates window
void closeSDL(); // Frees media and shuts down SDL*/
//ImageData loadImgTexture(char* path, int num, int hn, int wn, bool ckEnable, Uint8 r, Uint8 g, Uint8 b);

// New and modified functions
//int imgRender(SDL_Renderer* renderer, ImageData img, int posX, int posY, int frame, int cx, int cy, double angle, SDL_RendererFlip flip, int alpha);
Uint32 aniAction(Uint32 interval, void* param); // Timer callback function


/*SDL_Window* window = NULL; // The window we'll be rendering to
SDL_Renderer* renderer = NULL; // The window renderer */



/*int initSDL()
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
	window = SDL_CreateWindow("OOP SDL Tutorial", 50, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 2;
	}

	// Initialize PNG loading	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 3;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 5;
	}

	return 0;
}*/


/*void closeSDL()
{
	// Destroy renderer	
	// Destroy window	
	// Quit Image subsystem
	// Quit SDL subsystems
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}*/


// ImageData loadTexture(char *path, bool ckEnable, Uint8 r, Uint8 g, Uint8 b)
/*ImageData loadImgTexture(char* path, int num, int hn, int wn, bool ckEnable, Uint8 r, Uint8 g, Uint8 b)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL)
	{
		printf("IMG_Load failed: %s\n", IMG_GetError());
		return { NULL };
	}
	else
	{
		ImageData img;

		// Set the color key (transparent pixel) in a surface.		
		SDL_SetColorKey(loadedSurface, ckEnable, SDL_MapRGB(loadedSurface->format, r, g, b));

		// Create texture from surface pixels
		img.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (img.texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		//Get image dimensions and information
		img.width = loadedSurface->w;
		img.height = loadedSurface->h;
		img.num = num;
		img.wn = wn;
		img.hn = hn;

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		//return newTexture;
		return img;
	}	
}*/


/*int imgRender(SDL_Renderer* renderer, ImageData img, int posX, int posY, int frame, int cx, int cy, double angle, SDL_RendererFlip flip, int alpha)
{
	int wc = frame % img.wn;
	int hc = frame / img.wn;

	SDL_Rect src, dst;
	src.x = img.width / img.wn * wc;
	src.y = img.height / img.hn * hc;
	src.w = img.width / img.wn;
	src.h = img.height / img.hn;
	dst.x = posX;
	dst.y = posY;
	dst.w = src.w;
	dst.h = src.h;
		

	// Set and enable standard alpha blending mode for a texture
	// https://wiki.libsdl.org/SDL_SetTextureBlendMode
	// https://wiki.libsdl.org/SDL_BlendMode
	if (SDL_SetTextureBlendMode(img.texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return -1;
	}

	// Modulate texture alpha
	// https://wiki.libsdl.org/SDL_SetTextureAlphaMod
	if (SDL_SetTextureAlphaMod(img.texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return -1;
	}

	//SDL_RenderCopy(renderer, img.texture, &src, &dst);

	// SDL_Point
	// A structure that defines a two dimensional point.
	// https://wiki.libsdl.org/SDL_Point
	SDL_Point center = { cx, cy };

	// Copy a portion of the texture to the current rendering target, 
	// optionally rotating it by angle around the given center and also flipping it top-bottom and/or left-right.
	// if center is NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2
	// https://wiki.libsdl.org/SDL_RenderCopyEx
	SDL_RenderCopyEx(renderer, img.texture, &src, &dst, angle, &center, flip);

	return 1;
}*/


Uint32 aniAction(Uint32 interval, void* param)
{
	int* par = (int*)param;
	par[0] = (par[0] + 1) % KFRAME;
	par[1] = (par[1] + 1) % PFRAME;
	par[2] = (par[2] + 1) % SFRAME;
	
	// rotation degree
	par[3] = (par[3] + 10) % 360;

	return interval;
}


// When using SDL, you have to use "int main(int argc, char* args[])"
// int main() and void main() are not allowed
int main(int argc, char* args[])
{
	// The working directory is where the vcxproj file is located.
	char imgPath1[100] = "../images/sp.png";
	char imgPath2[100] = "../images/rob.png";

	char kissPath[100] = "../images/kiss.png";
	char piestarPath[100] = "../images/piestar.png";
	char spongePath[100] = "../images/spongebob.png";
	int animationPar[4] = { 0,0,0,0 }; // index, index, index, degree
	Window_data win_data(800, 600); 

	ImageData sp, rob;
	ImageData sponge, kiss, pie;	


	// Flip type
	// https://wiki.libsdl.org/SDL_RendererFlip
	SDL_RendererFlip no = SDL_FLIP_NONE;
	SDL_RendererFlip ho = SDL_FLIP_HORIZONTAL;
	SDL_RendererFlip ve = SDL_FLIP_VERTICAL;
	SDL_RendererFlip hove = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

	// Start up SDL and create window
	if (open_window(win_data)) {
		printf("Failed to initialize SDL!\n");
		return -1;
	}

	LoadImgTexture(win_data, sp, imgPath1, 1, 1, 1, true, 0xFF, 0xFF, 0xFF);
	LoadImgTexture(win_data, rob, imgPath2, 1, 1, 1, false, 0xFF, 0xFF, 0xFF);
	LoadImgTexture(win_data, kiss, kissPath, KFRAME, 5, 6, true, 0xFF, 0xFF, 0xFF);
	LoadImgTexture(win_data, pie, piestarPath, PFRAME, 3, 4, true, 0xFF, 0xFF, 0xFF);
	LoadImgTexture(win_data, sponge, spongePath, SFRAME, 3, 4, true, 0xFF, 0xFF, 0xFF);

	SDL_TimerID timerID_ku = SDL_AddTimer(70, aniAction, &animationPar);

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}


		// Clear screen
		SDL_SetRenderDrawColor(win_data.renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(win_data.renderer);

		ImgRender(win_data, rob, Super_point{ 0, 0 }, 0, Super_point{ NULL, NULL }, NULL, no, 255);
		ImgRender(win_data, sp, Super_point{ win_data.WIDTH / 2 - sp.width / 2, 100 }, 0, Super_point{ sp.width / 2, sp.height / 2 }, animationPar[3], no, 255);

		ImgRender(win_data, kiss, Super_point{ 0, 300 }, animationPar[0], Super_point{ NULL, NULL }, NULL, ve, 255);
		ImgRender(win_data, pie, Super_point{ 250, 300 }, animationPar[1], Super_point{ NULL, NULL }, NULL, ho, 255);

		
		//setTextureAlpha(sponge.texture, 150);		
		ImgRender(win_data, sponge, Super_point{ 550, 100 }, animationPar[2], Super_point{ sponge.width / 2, sponge.height / 2 }, -20, no, 150);
		

		// Update screen
		SDL_RenderPresent(win_data.renderer);
	}

	// Free loaded image
	SDL_DestroyTexture(sp.texture);
	SDL_DestroyTexture(rob.texture);
	SDL_DestroyTexture(kiss.texture);
	SDL_DestroyTexture(pie.texture);
	SDL_DestroyTexture(sponge.texture);

	//Free resources and close SDL
	close_window(win_data); 

	return 0;
}