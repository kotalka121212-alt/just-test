#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// SDL3 сама подменит main на нужную для Android сигнатуру
int main(int argc, char *argv[]) {
    // Инициализируем только видео для теста
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("SUCCESS: SDL3 initialized on Android!");

    // Создаем окно на весь экран
    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 0, 0, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        SDL_Log("Window Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Log("Window created successfully!");

    // Пауза на 3 секунды, чтобы успеть увидеть окно (если успеет прогрузиться)
    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}