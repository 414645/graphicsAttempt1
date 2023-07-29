#ifndef MAINGAME_H
#define MAINGAME_H

#include <iostream>
#include "SDL2/SDL.h"

#include "sprite.h"

#include "GLSLProgram.h"

enum class GameState {PLAY, EXIT};

class mainGame {
 public:
  mainGame();
  ~mainGame();
  
  void run();

 private:
  void initSystems();
  void initShaders();
  void gameLoop();
  void processInput();
  void drawGame();
  
  SDL_Window* _window;
  int _screenWidth;
  int _screenHeight;
  GameState _gameState;

  sprite _sprite;

  GLSLProgram _colorProgram;
};

#endif
