#include "button.h"

Button::Button() {
  _position.x = 0;
  _position.y = 0;
}
Button::~Button() {}

void Button::setPosition(int x, int y) {
  _position.x = x;
  _position.y = y;
}
void Button::setName(std::string name) { _name = name; }

void Button::handleEvent(SDL_Event *event, std::vector<int> &array,
                         std::string &value, bool &sortingFlag) {

  if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN ||
      event->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    bool inside = true;

    if (x < _position.x) {
      inside = false;
    } else if (x > _position.x + _width) {
      inside = false;
    } else if (y < _position.y) {
      inside = false;
    } else if (y > _position.y + _height) {
      inside = false;
    }

    if (inside) {
      switch (event->type) {
      case SDL_MOUSEBUTTONDOWN:
        if (this->_name == "startSorting")
          sortingFlag = true;
        else if (this->_name == "mergeSort")
          value = "mergesort";
        else if (this->_name == "quickSort")
          value = "quicksort";
        else if (this->_name == "bubbleSort")
          value = "bubblesort";
        else if (this->_name == "newArray")
          newArray(array);
        break;
      }
    }
  }
}