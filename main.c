#include <stdio.h>
#include <SDL2/SDL.h>

#ifdef main
# undef main
#endif

int SDL_main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window with a smaller size
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set render draw color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Initial position of the square
    int squareX = 160;
    int squareY = 120;
    int squareSize = 20;

    // Main event loop
    int quit = 0;
    SDL_Event event;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                // Handle key press events
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        // Move the square to the right
                        squareX += 5;
                        break;
                    case SDLK_LEFT:
                        // Move the square to the left
                        squareX -= 5;
                        break;
                    default:
                        break;
                }
            }
        }

        // Clear the renderer to a background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set render draw color to red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw the red square at the updated position
        SDL_Rect rect = {squareX - squareSize / 2, squareY - squareSize / 2, squareSize, squareSize}; // x, y, width, height
        SDL_RenderFillRect(renderer, &rect);

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Simulate a delay to avoid high CPU usage (replace with your actual rendering code)
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
