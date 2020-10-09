#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Layout {
public:
  void setColor(uint8_t &&r, uint8_t &&g, uint8_t &&b);
  void setText(const char *c);
  void setPosition(int startPosition, int endPosition);

  Layout() {}
  Layout(SDL_Window *window, SDL_Renderer *renderer, const char *c,
         TTF_Font *font, int startPos, int endPos, int width, int height);
  ~Layout();
  void render();

private:
  SDL_Renderer *_renderer = NULL;
  SDL_Texture *_texture = NULL;
  SDL_Surface *_surface = NULL;
  SDL_Color _color = {0xE6, 0xE6, 0xE6};
  TTF_Font *_font = NULL;
  SDL_Rect _dstrect;

  const char *_c;
  int _startPos;
  int _endPos;
  int _width;
  int _height;
};
