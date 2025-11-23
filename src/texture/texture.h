#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
public:
  Texture();
  ~Texture();
  bool loadFromFile(SDL_Renderer *renderer, std::string path);
  void destroy();
  void render(SDL_Renderer *renderer, float x, float y);
  int getWidth();
  int getHeight();

private:
  SDL_Texture *texture;
  int width;
  int height;
};
