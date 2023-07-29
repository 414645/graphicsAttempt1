#include "errors.h"

#include <cstdlib>

#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

//prints an error message and exits the game
void fatalError(string errorString) {
  cout << errorString << endl;
  cout << "Enter any key to quit..." << endl;
  int tmp;
  cin >> tmp;
  SDL_Quit();
  exit(1);
}

