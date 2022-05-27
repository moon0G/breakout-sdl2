#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>

int main(int argv, char** args) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("error, %s", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL Initialised!");

	const int windowW = 800;
	const int windowH = 600;
	SDL_Window* window = SDL_CreateWindow("Breakout",
					      SDL_WINDOWPOS_UNDEFINED,
					      SDL_WINDOWPOS_UNDEFINED,
					      windowW, windowH,
					      SDL_WINDOW_SHOWN);
	if(!window) {
		SDL_Log("Window could not be created\nSDL_Error: %s", SDL_GetError());
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		SDL_Log("Renderer could not be created\nSDL_Error: %s", SDL_GetError());
	}
	
	/*
	  * After the SDl is setup we start the main code
	*/
	bool quit = false;
	const int fps = 60;
	const int rectSize = 15;
	const float deltaTime = 1.0/(float)fps;
	const float speed = 200.0;
	int barW = 75;
	int barX = (windowW / 2)-(barW/2);
	const int barY = 400;
	float x = (rand() % (windowW-100)) + 1, y = (rand() % (windowH-100)) + 1;
	float x1 = 1, y1 = 1;
	while(!quit) {
		SDL_Event e; //all events tied to e
		while(SDL_PollEvent(&e) != 0) {
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case 'a':
							barX -= 10;
							break;
						case 'd':
							barX += 10;
							break;
					}
			}
		}
		
		float barX1 = 0;
		if(SDL_GetKeyboardState[SDL_SCANCODE_A] != 0) {
			barX1 *= 1.3;
		}
		if(SDL_GetKeyboardState[SDL_SCANCODE_D] != 0) {
			barX1 *= -1.3;
		}
		barX += barX1*speed*deltaTime;
	 	
		if(barX+barW > windowW) {
			barX = windowW-barW;
		}else if(barX < 0) {
			barX = 0;
		}

		float x2 = x + x1*speed*deltaTime; // x2 placeholder
		if(x2 < 0 || x2 + rectSize > windowW) { 
			x1 *= -1;
			x2 = x + x1*speed*deltaTime;
		}
		float y2 = y + y1*speed*deltaTime; //y2 placehold
		if(y2 < 0 || y2 + rectSize > windowH) {
			y1 *= -1;
			y2 = y + y1*speed*deltaTime;
		}

		x = x2;
		y = y2;
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set backgorund colour to black
		SDL_RenderClear(renderer); // clear the render

		//proj block
		SDL_Rect proj;
		proj.x = (int)x;
		proj.y = (int)y;
		proj.w = rectSize;
		proj.h = rectSize;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // white colour
		SDL_RenderFillRect(renderer, &proj); // load the proj's address in memory into the renderer
		//bar block
		SDL_Rect bar;
		bar.x = barX;
		bar.y = barY;
		bar.w = barW;
		bar.h = 10;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // white colour
		SDL_RenderFillRect(renderer, &bar); // load the bar's address in memory into the renderer

		//Present renderer
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/fps); // capped at 1000ms/60 or 60FPS
	}
	
	SDL_DestroyRenderer(renderer); // destroy the renderer 
	SDL_Quit(); // quit SDL
	
	return 0;
}
