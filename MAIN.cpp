#include "SDL.h"
#include "ray.h"
#include "camera.h"
#include "canvas.h"
#include "image.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Material.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

double rand_dbl()
{
	return (double)rand() / (double)RAND_MAX;
}

int main(int, char**)
{
	//srand((unsigned int)time(nullptr));

	//lower paramaters = lower quality but faster rendering
	const int width = 800;
	const int height = 600;
	const int samples = 1;
	const int depth = 5;
	const int objects = 10;


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl; return 1;
	}
	SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) 
	{ 
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1; 
	}

	Canvas canvas(renderer,width,height);
	Image image(width,height);
	// eye, lookat, up, fov, image
	Camera camera{ glm::vec3{0, 30, 0}, glm::vec3{0, 0, 0}, glm::vec3{1, 1, 0}, 80.0f, &image };
	//Camera camera{ glm::vec3{0, 5, 5}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0}, 90.0f, &image };
	Tracer tracer(samples, depth);
	Scene scene;

	Sphere* s;
	for (size_t i = 0; i < objects; i++)
	{
		glm::vec3 color = glm::rgbColor(glm::vec3{ rand()%360, 1, 1 });
		glm::vec3 center = glm::vec3({10-(rand_dbl()*5), 10 - (rand_dbl() * 5) , 10 - (rand_dbl() * 5) });
		float radius = rand_dbl() * 100;
		Material* m = nullptr;
		switch (rand()%3)
		{
		case 0:
			m = new Lambertian{color};
			break;	
	
		case 1:
			m = new Metal{color, 0.0f};
			break;
		case 2:
			m = new Dieletric{ color, 1.33f };
			break;
		}
		s = new Sphere(center, radius, m);
		scene.Add(s);
	}


	//scene.Add(new Sphere{	{ 2, 2, -2 },	1,			new Lambertian	{ { 1, 1, 0 } } });
	//scene.Add(new Sphere{	{ 1, 0, 2 },	0.75,		new Metal		{ { .8, .9, .7 }, 0.0f } });
	//scene.Add(new Sphere{	{0,-1.1,-2 },	0.5,		new Dieletric	{ { 1, 1, 0 }, 1.33f } });
	scene.Add(new Plane{	{0, -2, 0},		{0, 1, 0},	new Metal		{ { .6, .6, .6 }, 0.0f } });

	image.Clear({ 0,0,0 });

	auto start = std::chrono::high_resolution_clock::now();
	tracer.Trace(image, scene, camera);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "\nDuration (microseconds): " << duration.count() << '\n';
	std::cout << "Samples: ............... " << samples << '\n';
	std::cout << "Depth: ................. " << depth << '\n';

	bool quit = false; while (!quit) 
	{
		SDL_Event event; SDL_PollEvent(&event);
		switch (event.type) 
		{
			case SDL_QUIT:quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{ 
					case SDLK_ESCAPE:quit = true; break; 
				}
			break;
		}
		canvas.Clear({1,1,1});
		canvas.DrawImage(image);
		canvas.Update();

		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit(); 
	return 0;
}