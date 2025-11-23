#include <SDL3/SDL.h>
#include <string>

class Texture {
public:
  Texture(std::string path);
  ~Texture();
  void render(float x, float y);

private:
  SDL_Texture *texture;
  int width;
  int height;
};
