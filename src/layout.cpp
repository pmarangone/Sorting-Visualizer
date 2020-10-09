#include "layout.h"

Layout::Layout(SDL_Window *window, SDL_Renderer *renderer, const char *c,
               TTF_Font *font, int startPos, int endPos, int width, int height)
    : _renderer(renderer), _c(c), _font(font), _startPos(startPos),
      _endPos(endPos), _width(width), _height(height) {
  _surface = TTF_RenderText_Blended(_font, _c, _color);
  SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
  _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
  _dstrect = {_startPos, _endPos, _width, _height};
}

Layout::~Layout() {}

void Layout::setColor(uint8_t &&r, uint8_t &&g, uint8_t &&b) {
  _color = {r, g, b};
  _surface = TTF_RenderText_Blended(_font, _c, _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
}

void Layout::setText(const char *newText) {
  _c = nullptr;
  _c = newText;
  _surface = TTF_RenderText_Blended(_font, _c, _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
}

void Layout::setPosition(int startPosition, int endPosition) {
  _startPos = startPosition;
  _endPos = endPosition;
}

void Layout::render() {
  SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
  SDL_RenderCopy(_renderer, _texture, NULL, &_dstrect);
}