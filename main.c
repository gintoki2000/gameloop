#include <SDL2/SDL.h>

#define GAME_WIDTH 400
#define GAME_HEIGHT 300

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_bool g_is_game_running = SDL_TRUE;
//init sdl
SDL_bool init();

//game loop
void loop();

//clean up and shutdown sdl system
void quit();

int main()
{
    if(init())
    {
	    loop();
    }
    quit();
    return 0;
}

SDL_bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not init sdl: %s", SDL_GetError());
        return SDL_FALSE;
    }

    g_window =  SDL_CreateWindow("game loop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);

    if(!g_window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s", SDL_GetError());
        return SDL_FALSE;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1 , SDL_RENDERER_ACCELERATED);

    if(!g_renderer)
    {
	 SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s", SDL_GetError());
        return SDL_FALSE;

    }

    return SDL_TRUE;
}

void quit()
{
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

void loop()
{
	Uint32 start_ticks;
	Uint32 used_ticks;
	Uint32 ticks_per_frame = 1000 / 60;
	SDL_Event event;

	SDL_Rect rect;
	rect.w = 50;
	rect.h = 50;
	rect.x = 0;
	rect.y = GAME_HEIGHT / 2;
	while(g_is_game_running)
	{
		start_ticks = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				g_is_game_running = SDL_FALSE;
			}
		}


		rect.x++;
			
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(g_renderer);


		SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);

		SDL_RenderFillRect(g_renderer, &rect);

		SDL_RenderPresent(g_renderer);

		used_ticks = SDL_GetTicks() - start_ticks;

		if(used_ticks < ticks_per_frame)
		{
			SDL_Delay(ticks_per_frame - used_ticks);
		}
	}
}
