#include <iostream>
#include "SDL2/SDL.h"

//#include "GLES/gl.h"
//#include "gles/gl.h"
//#include "GLFW/glfw3.h"
//#include "GL/gl.h"

#include "GL/glew.h"

#include <string>

#include "mainGame.h"

#include "errors.h"

using namespace std;

mainGame::mainGame() {
  _window = NULL;
  _screenWidth = 1024;
  _screenHeight = 768;
  _gameState = GameState::PLAY;
}

mainGame:: ~mainGame() {

}
void mainGame::run() {
  //cout << "hi world!" << endl;
  initSystems();

  //initalize the sprite (temp)
  _sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

  //starts game loop, returns when game ends
  gameLoop();
}

void mainGame::initSystems() {
  //Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  _window = SDL_CreateWindow("Game Engine",
			     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			     _screenWidth, _screenHeight,
			     SDL_WINDOW_OPENGL);
  if (_window == NULL) {
    fatalError("SDL Window could not be created");
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (glContext == NULL) {
    fatalError("SDL_GL context could not be created");
  }

  GLenum error = glewInit();
  
  if (error != GLEW_OK) {
    fatalError("Could not initalize glew");
  }
  //*/
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //set background color
  glClearColor(0.0f, 0.0f, 1.0f, 1.0);

  initShaders();
}

void mainGame::initShaders() {
  //string one = "shaders/colorShading.vert";
  //string two = "shaders/colorShading.frag";
  _colorProgram.compileShaders("shaders/colorShading.vert",
			       "shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.linkShaders();
}

void mainGame::gameLoop() {
  while (_gameState != GameState::EXIT) {
    processInput();
    drawGame();
  }
}

void mainGame::processInput() {
  SDL_Event evnt;
  
  //this will set evnt if it returns as true
  while (SDL_PollEvent(&evnt)) {
    switch (evnt.type) {
    case SDL_QUIT:
      _gameState = GameState::EXIT;
      break;
    /*/
    case SDL_MOUSEMOTION:
      cout << evnt.motion.x << " " << evnt.motion.y << endl;
      
    //*/
    }
  }
}

void mainGame::drawGame() {
  glClearDepth(1.0);
  //does this twice with different inputs with one line of code
  //FYI this code clears depth + color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _colorProgram.use();
  
  //draw sprite!
  _sprite.draw();

  _colorProgram.unuse();
  
  //Swap or buffer to draw stuff to the screen
  SDL_GL_SwapWindow(_window);
  
  //stupid way of drawing (that does not even work with my version)
  /*
  glEnableClientState(GL_COLOR_ARRAY);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(0, 0);
  glVertex2f(0, 1);
  glVertex2f(1, 1);
  glColor3f(0.0f, 0.0f, 1.0f);
  glEnd;
  //*/
}

