#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <random>
#include <string>
#include <vector>

static int array_size = 150;
const static int min_array_value = 20, max_array_value = 700;

// https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c/13446015
int randomGenerator(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> d(start, end);

  return d(gen);
}

void newArray(std::vector<int> &array) {
  array.clear();
  for (int i = 0; i < array_size; i++) {
    array.emplace_back(
        std::move(randomGenerator(min_array_value, max_array_value)));
  }
}

class Button {
public:
  Button();
  Button(int x, SDL_Renderer *renderer);
  ~Button();

  void setPosition(int x, int y);
  void setName(std::string name);
  void handleEvent(SDL_Event *event, std::vector<int> &array,
                   std::string &value, bool &sortingFlag);

private:
  SDL_Point _position;
  SDL_Renderer *_renderer = NULL;
  std::string _name;
  const int _width = 200, _height = 60;
};
