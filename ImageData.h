#pragma once
#include <iostream>
#include <SDL.h> // Using SDL
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include "SDL_image.h"  // Using SDL2 image extension library 
#include "SDL_open_Windows.h"

struct ImageData {
	SDL_Texture* texture;
	int width;
	int height;
	int num;
	int wn;
	int hn;
	Super_point IMG_p; 
};

// ImageData loadTexture(char *path, bool ckEnable, Uint8 r, Uint8 g, Uint8 b)
void LoadImgTexture(Window_data& win_in, ImageData& IMG_in, char* path, int num, int hn, int wn, bool ckEnable, Uint8 r, Uint8 g, Uint8 b, Super_point point = Super_point{0 , 0}) {
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		printf("IMG_Load failed: %s\n", IMG_GetError());
		IMG_in = { NULL }; 
	}
	else {
		//ImageData img;

		// Set the color key (transparent pixel) in a surface.		
		SDL_SetColorKey(loadedSurface, ckEnable, SDL_MapRGB(loadedSurface->format, r, g, b));

		// Create texture from surface pixels
		IMG_in.texture = SDL_CreateTextureFromSurface(win_in.renderer, loadedSurface);
		if (IMG_in.texture == NULL) {
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		//Get image dimensions and information
		IMG_in.width = loadedSurface->w;
		IMG_in.height = loadedSurface->h;
		IMG_in.num = num;
		IMG_in.wn = wn;
		IMG_in.hn = hn;

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		//return newTexture;
		return; 
	}
}


int ImgRender(Window_data& win_in, ImageData img, Super_point pos , int frame, Super_point c, double angle, SDL_RendererFlip flip, int alpha) {
	int wc = frame % img.wn;
	int hc = frame / img.wn;

	SDL_Rect src, dst;
	src.x = img.width / img.wn * wc;
	src.y = img.height / img.hn * hc;
	src.w = img.width / img.wn;
	src.h = img.height / img.hn;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = src.w;
	dst.h = src.h;


	// Set and enable standard alpha blending mode for a texture
	// https://wiki.libsdl.org/SDL_SetTextureBlendMode
	// https://wiki.libsdl.org/SDL_BlendMode
	if (SDL_SetTextureBlendMode(img.texture, SDL_BLENDMODE_BLEND) == -1) {
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return -1;
	}

	// Modulate texture alpha
	// https://wiki.libsdl.org/SDL_SetTextureAlphaMod
	if (SDL_SetTextureAlphaMod(img.texture, alpha) == -1) {
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return -1;
	}

	//SDL_RenderCopy(renderer, img.texture, &src, &dst);

	// SDL_Point
	// A structure that defines a two dimensional point.
	// https://wiki.libsdl.org/SDL_Point
	SDL_Point center = { c.x, c.y };

	// Copy a portion of the texture to the current rendering target, 
	// optionally rotating it by angle around the given center and also flipping it top-bottom and/or left-right.
	// if center is NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2
	// https://wiki.libsdl.org/SDL_RenderCopyEx
	SDL_RenderCopyEx(win_in.renderer, img.texture, &src, &dst, angle, &center, flip);

	return 1;
}