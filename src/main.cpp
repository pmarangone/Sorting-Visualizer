#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"
#include "button.cpp"
#include "layout.cpp"
#include "mergeSort.h"
#include "quickSort.h"

// Layout
Layout layouts[total_buttons + 1];

// Buttons objects
Button buttons[total_buttons];

// good practice ( https://lazyfoo.net/tutorials/SDL/ )
bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    Window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (Window == NULL ||
        (SDL_SetWindowBrightness(Window, static_cast<float>(0.6) < 0))) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Create renderer
      Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);
      if (Renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      }
    }
  }
  if (TTF_Init() < 0) {
    printf("TTF could not be initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  return success;
}

// good practice ( https://lazyfoo.net/tutorials/SDL/ )
void close() {
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  TTF_CloseFont(font);
  Window = NULL;
  Renderer = NULL;
  font = NULL;

  SDL_Quit();
  TTF_Quit();

  exit(0);
}

struct Sorting {

  // if no Sorting was selected
  void default_(std::vector<int> *array) { cond_main.notify_one(); }

  void mergeSort(std::vector<int> *array) {
    std::vector<int> tmpArray(array->size());
    auxiliarArray = array;
    auxiliarSize = array->size();

    sort(*array, tmpArray, 0, array->size() - 1);
    cond_main.notify_one();
  }

  void quickSort(std::vector<int> *array) {
    quickSortRoutine(*array, 0, array->size() - 1);
    cond_main.notify_one();
  }
  void bubbleSort(std::vector<int> *array) {
    int size = array->size();
    int i, j;
    for (i = 0; i < size - 1; i++) {
      for (j = 0; j < size - i - 1; j++) {
        if (array->at(j) > array->at(j + 1)) {
          swapRoutine(*array, j, j + 1);
        }
      }
    }
    cond_main.notify_one();
  }
};

int main() {
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {

    bool quit = false;
    font = TTF_OpenFont("../Roboto-Medium.ttf", 64);

    std::vector<int> vi;
    newArray(vi);

    layouts[0] =
        Layout(Window, Renderer, "Sorting Visualizer", font, 100, 0,
               WindowOrientation::width + 150, WindowOrientation::height + 50);

    layouts[1] = Layout(Window, Renderer, "Merge Sort", font,
                        WindowOrientation::mergeSort, 30,
                        WindowOrientation::width, WindowOrientation::height);

    layouts[2] = Layout(Window, Renderer, "QuickSort", font,
                        WindowOrientation::quickSort, 30,
                        WindowOrientation::width, WindowOrientation::height);

    layouts[3] = Layout(Window, Renderer, "Bubble Sort", font,
                        WindowOrientation::bubbleSort, 30,
                        WindowOrientation::width, WindowOrientation::height);
    
    layouts[4] = Layout(
        Window, Renderer, "Start Sorting!", font, WindowOrientation::startSort,
        30, WindowOrientation::width + 30, WindowOrientation::height);

    layouts[5] =
        Layout(Window, Renderer, "New Array", font, WindowOrientation::newArray,
               30, WindowOrientation::width, WindowOrientation::height);

    buttons[0].setPosition(WindowOrientation::mergeSort, 30);
    buttons[0].setName("mergeSort");

    buttons[1].setPosition(WindowOrientation::quickSort, 30);
    buttons[1].setName("quickSort");

    buttons[2].setPosition(WindowOrientation::bubbleSort, 30);
    buttons[2].setName("bubbleSort");

    buttons[3].setPosition(WindowOrientation::startSort, 30);
    buttons[3].setName("startSorting");

    buttons[4].setPosition(WindowOrientation::newArray, 30);
    buttons[4].setName("newArray");

    Sorting sorting;
    auto sortingAlgo =
        std::mem_fn(&Sorting::default_); // alias to member function
    std::string opt = "";

    SDL_Event event;
    SDL_Event event_thread;

    while (!quit) {
      
      while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
          quit = true;
        }
        // User presses a key
        else if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
            case SDLK_LEFT:
              // decrease array size
              if (array_size > 100) {
                vi.erase(vi.begin() + randomGenerator(0, array_size - 1));
                array_size--;
              }
              break;

            case SDLK_RIGHT:
              // increase array size
              if (array_size < 250) {
                vi.emplace_back(
                    std::move(randomGenerator(min_array_value, max_array_value)));
                array_size++;
              }
              break;
             
            case SDLK_ESCAPE:
              close();
              break;

            default:
              break;
          }
          if (array_size >= 150)
            bar_distance = 5, bar_width = 3;
          else if (array_size < 150)
            bar_distance = 8, bar_width = 7;
        }
        // Handle button events
        for (int i = 0; i < total_buttons; i++) {
          buttons[i].handleEvent(&event, vi, opt, sortingFlag);
        }
      }
      
      // Clear screen
      SDL_SetRenderDrawColor(Renderer, 0x15, 0x31, 0x4B, 0xFF);
      SDL_RenderClear(Renderer);

      // render text
      for (auto layout : layouts) {
        layout.render();
      }

      // render array as bars
      SDL_SetRenderDrawColor(Renderer, 0x46, 0x82, 0xB4, 0xFF);
      SDL_Rect vec[array_size] = {};
      int pos = 0;

      for (int i = 0; i < array_size; i++) {

        SDL_Rect rect = {
            (WindowOrientation::x_center - ((bar_distance * array_size) / 2)) +
                pos,
            WindowOrientation::bottom_h - vi[i], bar_width, vi[i]};
        vec[i] = std::move(rect);
        pos += bar_distance;
      }
      SDL_RenderFillRects(Renderer, vec, array_size);

      // update screen
      SDL_RenderPresent(Renderer);

      if (opt == "mergesort")
        sortingAlgo = std::mem_fn(&Sorting::mergeSort);
      else if (opt == "quicksort")
        sortingAlgo = std::mem_fn(&Sorting::quickSort);
      else if (opt == "bubblesort")
        sortingAlgo = std::mem_fn(&Sorting::bubbleSort);

      if (sortingFlag) {
        sortingFlag = false;

        std::thread SORT(sortingAlgo, sorting, &vi);
        std::unique_lock<std::mutex> uLock(mtx_main);
        while (cond_main.wait_for(uLock, std::chrono::milliseconds(10)) ==
               std::cv_status::timeout) {
          if (SDL_PollEvent(&event_thread) != 0) {
            if (event_thread.type == SDL_QUIT ||
                (event_thread.type == SDL_KEYDOWN &&
                 event_thread.key.keysym.sym == SDLK_ESCAPE)) {
              cond_main.notify_one();
              quit = true;
              close();
            }
          }
        }
        SORT.join();
      }
    }
  }

  close();
  return 0;
}
