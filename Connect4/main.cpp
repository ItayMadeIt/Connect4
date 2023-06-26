#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

static int SQUARE_SIZE = 100;
static int PIECE_SIZE = 90;

static int WIDTH = 7 * SQUARE_SIZE;
static int HEIGHT = 7 * SQUARE_SIZE;

static SDL_Color redPlayerC = { 255, 0, 0, 255 };
static SDL_Color bluePlayerC = { 0, 0, 255, 255 };

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Event event;

SDL_Point mousePos;

void RenderFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a window
    window = SDL_CreateWindow("Connect 4 Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    // Error Checking
    if (!window)
    {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Error Checking
    if (!renderer)
    {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool running = true;

    while (running) {
        // Input
        while (SDL_PollEvent(&event)) {

            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_SetWindowSize(window, WIDTH, HEIGHT);
            }

            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        for (size_t i = 0; i < 7; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                RenderFilledCircle(renderer, i * SQUARE_SIZE + SQUARE_SIZE/2, (6-j) * SQUARE_SIZE + SQUARE_SIZE/2, PIECE_SIZE / 2, 100, 100, 100, 255);
            }
        }

        RenderFilledCircle(renderer, mousePos.x+100, mousePos.y, PIECE_SIZE / 2, redPlayerC.r, redPlayerC.g, redPlayerC.b, 255);
        RenderFilledCircle(renderer, mousePos.x-100, mousePos.y, PIECE_SIZE / 2, bluePlayerC.r, bluePlayerC.g, bluePlayerC.b, 255);

        // Rendering
        SDL_RenderPresent(renderer);
    }


	return 0;
}