#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"
#include "AI.h"

using namespace std;

static int SQUARE_SIZE = 100;
static int PIECE_SIZE = 90;

static int GRID_WIDTH = 7;
static int GRID_HEIGHT = 6;
static int WIDTH = (GRID_WIDTH) * SQUARE_SIZE;
static int HEIGHT = (GRID_HEIGHT + 1) * SQUARE_SIZE;

static SDL_Color redPlayerC = { 255, 0, 0, 255 };
static SDL_Color bluePlayerC = { 0, 0, 255, 255 };

SDL_Texture* RedWonText;
SDL_Texture* BlueWonText;
SDL_Rect textRect = {WIDTH/2 - WIDTH/5/2,HEIGHT/2 - HEIGHT/5/2,WIDTH/5,HEIGHT/5};

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Event event;

SDL_Point mousePos;

State<7, 6> mainBoard;



static int roundUpToMultipleOfEight(int v)
{
    return (v + (8 - 1)) & -8;
}
static void DrawCircle(SDL_Renderer* renderer, SDL_Point center, int radius)
{
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
    SDL_Point* points = new SDL_Point[arrSize];
    int drawCount = 0;

    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        points[drawCount + 0] = { center.x + x, center.y - y };
        points[drawCount + 1] = { center.x + x, center.y + y };
        points[drawCount + 2] = { center.x - x, center.y - y };
        points[drawCount + 3] = { center.x - x, center.y + y };
        points[drawCount + 4] = { center.x + y, center.y - x };
        points[drawCount + 5] = { center.x + y, center.y + x };
        points[drawCount + 6] = { center.x - y, center.y - x };
        points[drawCount + 7] = { center.x - y, center.y + x };

        drawCount += 8;

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_RenderDrawPoints(renderer, points, drawCount);
    delete[] points;
}
static void DrawFilledCircle(SDL_Renderer* renderer, SDL_Point center, int radius)
{
    const int arrSize = static_cast<int>(M_PI * radius * radius);
    SDL_Point* points = new SDL_Point[arrSize];

    int radiusSquared = radius * radius;

    int count = 0;

    for (int y = -radius; y <= radius; y++)
    {
        int ySquared = y * y;
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + ySquared <= radiusSquared) {
                points[count] = { center.x + x, center.y + y };
                count++;
            }
        }
    }


    SDL_RenderDrawPoints(renderer, points, arrSize);

    delete[] points;
}
static void DrawBackground(SDL_Color bgColor, int width, int height) {

    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);

    for (size_t i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            SDL_Point p = { i * SQUARE_SIZE + SQUARE_SIZE / 2, (6 - j) * SQUARE_SIZE + SQUARE_SIZE / 2 };
            DrawFilledCircle(renderer, p, PIECE_SIZE / 2);
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

    SDL_Surface* redWonSurface = IMG_Load("Assets/Red Won Text.png");
    if (redWonSurface) {
        RedWonText = SDL_CreateTextureFromSurface(renderer, redWonSurface);
        SDL_FreeSurface(redWonSurface);
    }
    
    SDL_Surface* blueWonSurface = IMG_Load("Assets/Blue Won Text.png");
    if (blueWonSurface) {
        BlueWonText = SDL_CreateTextureFromSurface(renderer, blueWonSurface);
        SDL_FreeSurface(blueWonSurface);
    }


    bool running = true;

    SDL_Rect backgroundRect = { 0, SQUARE_SIZE, WIDTH, HEIGHT - SQUARE_SIZE};

    Board* b = new Board();


    while (running) {
        // Input
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        vector<Move> moves = Board::GetMoves(mainBoard);

        while (SDL_PollEvent(&event)) {

            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_SetWindowSize(window, WIDTH, HEIGHT);
            }

            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN) {
                
                for (size_t i = 0; i < moves.size(); i++)
                {
                    if (moves[i].x == static_cast<int>(mousePos.x / SQUARE_SIZE)) {
                        Board::MakeMove(mainBoard, moves[i]);
                        MinimaxResult result = AI::CalculateBestMove(mainBoard, 5);
                        cout << result.move.x << endl;
                        Board::MakeMove(mainBoard, result.move);
                    }
                }
            }
        }

        SDL_Point piece = { 0, 0};



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        DrawBackground(SDL_Color{ 100, 100, 100, 255 }, 7, 6);


        SDL_SetRenderDrawColor(renderer, redPlayerC.r, redPlayerC.g, redPlayerC.b, 255);

        for (int rank = 0; rank < 6; ++rank) {
            for (int file = 0; file < 7; ++file) {

                int bitPosition = rank * 7 + file;
                if (!mainBoard.red.test(bitPosition))
                    continue;

                piece.x = file * SQUARE_SIZE + SQUARE_SIZE / 2;
                piece.y = (5 - rank) * SQUARE_SIZE + SQUARE_SIZE / 2 + SQUARE_SIZE;

                DrawFilledCircle(renderer, piece, PIECE_SIZE / 2);
            }
        }
        
        SDL_SetRenderDrawColor(renderer, bluePlayerC.r, bluePlayerC.g, bluePlayerC.b, 255);

        for (int rank = 0; rank <= 5; ++rank) {
            for (int file = 0; file <= 6; ++file) {

                int bitPosition = rank * 7 + file;
                if (!mainBoard.blue.test(bitPosition))
                    continue;

                piece.x = file * SQUARE_SIZE + SQUARE_SIZE / 2;
                piece.y = (5 - rank) * SQUARE_SIZE + SQUARE_SIZE / 2 + SQUARE_SIZE;

                DrawFilledCircle(renderer, piece, PIECE_SIZE / 2);
                
            }
        }
        

        if (Board::WhoWins(mainBoard) == Red) {
            SDL_RenderCopy(renderer, RedWonText, nullptr, &textRect);
        }
        if (Board::WhoWins(mainBoard) == Blue) {
            SDL_RenderCopy(renderer, BlueWonText, nullptr, &textRect);
        }        
        
        if (mainBoard.isRedTurn) {
            SDL_SetRenderDrawColor(renderer, redPlayerC.r, redPlayerC.g, redPlayerC.b, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, bluePlayerC.r, bluePlayerC.g, bluePlayerC.b, 255);
        }


        piece = { static_cast<int>(mousePos.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE / 2, SQUARE_SIZE / 2 };
        DrawFilledCircle(renderer, piece, PIECE_SIZE / 2);


        // Rendering
        SDL_RenderPresent(renderer);
    }


	return 0;
}