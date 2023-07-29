#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <iostream>
#include "GL/glew.h"

using namespace std;

class GLSLProgram {
 public:
  GLSLProgram();
  ~GLSLProgram();

  void compileShaders(const string& vertexShaderFilePath,
		      const string& fragmentShaderFilePath);
  void linkShaders();
  void addAttribute(const string& attributeName);

  void use();
  void unuse();
 private:
  void compileShader(const string& filepath, GLuint id);

  int _numAttributes;
  GLuint _programID;

  GLuint _vertexShaderID;
  GLuint _fragmentShaderID;
};

#endif
