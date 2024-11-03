#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 10;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

// Определения состояния клетки в следующем шаге роверяет состояние клетки на основе её соседей и возвращает новое состояние (живая или мёртвая).
bool isCellAlive(int x, int y, const std::vector<std::vector<int>>& grid) {
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;  // Пропускаем саму клетку
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                aliveNeighbors += grid[ny][nx];
            }
        }
    }
    if (grid[y][x] == 1) {
        return aliveNeighbors == 2 || aliveNeighbors == 3;
    } else {
        return aliveNeighbors == 3;
    }
}

// Обновление игрового поля:сетку на основе правил 
void updateGrid(std::vector<std::vector<int>>& grid) {
    std::vector<std::vector<int>> newGrid = grid;

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            newGrid[y][x] = isCellAlive(x, y, grid);
        }
    }

    grid = newGrid;
}

// Отрисовки сетки c sdl
void renderGrid(SDL_Renderer* renderer, const std::vector<std::vector<int>>& grid) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            SDL_Rect cell;
            cell.x = x * CELL_SIZE;
            cell.y = y * CELL_SIZE;
            cell.w = CELL_SIZE;
            cell.h = CELL_SIZE;

            if (grid[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Живая клетка (зелёная)
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);    // Мёртвая клетка (чёрная)
            }
            SDL_RenderFillRect(renderer, &cell);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Белые линии сетки
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

// Обработка кликов мыши; оживить или убить клетку
void handleMouseClick(int mouseX, int mouseY, std::vector<std::vector<int>>& grid) {
    int gridX = mouseX / CELL_SIZE;
    int gridY = mouseY / CELL_SIZE;

    if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
        grid[gridY][gridX] = !grid[gridY][gridX];  // Инвертируем состояние клетки
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Создаем сетку
    std::vector<std::vector<int>> grid(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));

    bool isRunning = true;
    bool isPaused = true;  // Игра начинается в режиме паузы
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p) {
                    isPaused = !isPaused;  // Переключение паузы
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    handleMouseClick(mouseX, mouseY, grid);
                }
            }
        }

        if (!isPaused) {
            updateGrid(grid);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Заливка фона
        SDL_RenderClear(renderer);

        renderGrid(renderer, grid);  // Отрисовка сетки

        SDL_RenderPresent(renderer);  // Отображение содержимого

        SDL_Delay(100);  // Замедление
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
