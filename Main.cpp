#include<SDL.h>
#include<gfx/SDL2_gfxPrimitives.h>

#include <iostream>
#include<stdio.h>
#include<vector>
#include <time.h>
#include <random>

#define PI 3.14159265359

const int WIDTH = 640, HEIGHT = 480;


struct Pos { int x; int y; };
struct RGB { Uint8 r; Uint8 g; Uint8 b; };

std::vector<Pos> TreeGenerator();


int main(int arg,char* args[])
{
	srand(time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
		std::cout << "SDL Couldn't started." << SDL_GetError() << std::endl;
		system("pause");
		return 0;
    }
    
	SDL_Window* window = SDL_CreateWindow("Fractal_Tree", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,SDL_WINDOW_SHOWN);
    if(!window) {
		std::cout << "Window Couldn't Created." << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event* event = new SDL_Event;


	std::vector<Pos> poses = TreeGenerator();
	RGB bodycolor = { 139,69,19 }, leafcolor = { 34,139,34 };

	bool running = true;
    while(running)
    {     
        while(SDL_PollEvent(event))
        {
			if (event->type == SDL_QUIT)
				running = false;

			if (event->type == SDL_KEYDOWN) {
				if (event->key.keysym.sym == SDLK_ESCAPE)
					running = false;

				if (event->key.keysym.sym == SDLK_SPACE)
					poses = TreeGenerator();
			}
        }



		SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
		SDL_RenderClear(renderer);


		int i = 0,thickness=10;
		RGB color = bodycolor;

		while ( i < poses.size()) {
			if (thickness > 2)
				thickness -= 1;
			if (i > 16)
				color = leafcolor;

		    thickLineRGBA(renderer, poses[i].x, poses[i].y, poses[i+1].x, poses[i+1].y, thickness, color.r, color.g, color.b, 255);
			i += 2;
		}


		SDL_RenderPresent(renderer);
    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    return 0;
}

std::vector<Pos> TreeGenerator()
{
	std::vector<Pos> poses;
    

	double d = HEIGHT/4;
	double angle=0;

	poses.push_back(Pos{ WIDTH / 2, HEIGHT });

	angle = rand() %(150-30) +30 ;
    poses.push_back(Pos{ poses[0].x - (int)(d * std::cos(angle*PI / 180.0)) , poses[0].y - (int)(d * abs(std::sin(angle*PI / 180.0))) });
	d -=4;


	for (int i = 1; d > 1; i+=2) {
		for (int i2 = 0; i2 < 4; i2++) {

			poses.push_back(poses[i]);
			
			if (i2 == 0)
				angle = rand() % (150 - 90) + 90;
			else
				angle = rand() % (90 - 30) + 30;

			poses.push_back(Pos{ poses[i].x - (int)(d *std::cos(angle*PI/180.0))  , poses[i].y - (int)(d * std::sin(angle*PI / 180.0)) });

		}

        if(i%4==1||i==3)
		    d -=4;

	}
	
    return poses;
}
