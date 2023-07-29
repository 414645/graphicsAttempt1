#include <iostream>
#include "SDL2/SDL.h"
//#include "GLFW/glfw3.h"

#include "mainGame.h"
#include "sprite.h"

using namespace std;

int main(int argc, char** argv) {
  //SDL_Init(SDL_INIT_EVERYTHING);
  //SDL_Quit();
  //cout << "hello world" <<endl;

  mainGame MainGame;
  MainGame.run();
  
  return 0;
}

  
