#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm> // std::find
#include <chrono>
#include <functional> // std::mem_fn
#include <future>     // std::condition_variable
#include <mutex>      // std::mutex
#include <thread>     // std::thread

constexpr static int SCREEN_WIDTH = 1440;
constexpr static int SCREEN_HEIGHT = 870;

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;
TTF_Font *font = NULL;

std::mutex mtx_main;
std::condition_variable cond_main;

// control how many rectangles will have functionaly
constexpr static int total_buttons = 5;

// bar distance must be greater than bar width, otherwise there will be overlap
static int bar_distance = 5, bar_width = 3;

// control sorting inicialization
bool sortingFlag = false;

namespace WindowOrientation {
constexpr static int x_center = SCREEN_WIDTH / 2;
constexpr static int bottom_h = SCREEN_HEIGHT - 20;
int width = 150;
int height = 40;

constexpr static int mergeSort = 450;
constexpr static int quickSort = 640;
constexpr static int bubbleSort = 840;
constexpr static int startSort = 1035;
constexpr static int newArray = 1250;
} // namespace WindowOrientation

bool init();
void close();
