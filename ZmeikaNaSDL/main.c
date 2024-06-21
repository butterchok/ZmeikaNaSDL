#include "snakelogic.c"
#include <SDL.h>

const int TILE_SIZE = 20;

void draw(SDL_Renderer* renderer, const gamestate* state) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < state->snake.length; i++) {
        SDL_Rect rect = { state->snake.body[i].x * TILE_SIZE, state->snake.body[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { state->food.pos.x * TILE_SIZE, state->food.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    gamestate state;
    init_game(&state);

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_w: change_direction(&state, UP); break;
                case SDLK_s: change_direction(&state, DOWN); break;
                case SDLK_a: change_direction(&state, LEFT); break;
                case SDLK_d: change_direction(&state, RIGHT); break;
                case SDLK_r: init_game(&state); break;
                case SDLK_q: quit = 1; break;
                }
            }
        }

        update_game(&state);
        draw(renderer, &state);
        SDL_Delay(200);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}