#include "GLSLProgram.h"
#include "errors.h"

#include <fstream>

#include <iostream>
#include <string>

#include <vector>

using namespace std;

GLSLProgram::GLSLProgram() : _numAttributes(0),
			     _programID(0),
			     _vertexShaderID(0),
			     _fragmentShaderID(0) {

}

GLSLProgram::~GLSLProgram() {

}

//compiles shaders into something GPU understands
void GLSLProgram::compileShaders(const string& vertexShaderFilePath,
				 const string& fragmentShaderFilePath) {
  //vertexShaderFilePath=<error reading variable: Cannot acces memory at addres 0x8>) at GLSLProgram.cpp:24
  //this is trying to dereference a null pointer error
  
  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  _programID = glCreateProgram();
  

  //create the vertex shader object and store its id
  _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (_vertexShaderID == 0) {
    fatalError("Vertex shader failed to be created");
  }

  //create the fragment shader object and store its ID
  _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (_fragmentShaderID == 0) {
    fatalError("Fragment shader failed to be created");
  }

  //call compile on shaders
  compileShader(vertexShaderFilePath, _vertexShaderID);
  compileShader(fragmentShaderFilePath, _fragmentShaderID);
  
}


void GLSLProgram::linkShaders() {
  //code adapted from (once you have a sucessful shader)
  //also everything is from a coding wiht ben turorial since graphics
  //https://www.khronos.org/opengl/wiki/Shader_Compilation#Shader_object_compulation
  
  // Attach our shaders to our program
  glAttachShader(_programID, _vertexShaderID);
  glAttachShader(_programID, _fragmentShaderID);
  
  // Link our program
  glLinkProgram(_programID);

  //"rest of this ugly code here is just error checking"
  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
    
    // The maxLength includes the NULL character
    vector<char> errorLog(maxLength);
    glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
    
    // We don't need the program anymore.
    glDeleteProgram(_programID);
    // Don't leak shaders either.
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
    
    // Use the infoLog as you see fit.
    printf("%s\n", &(errorLog[0]));
    fatalError("Shaders failed to link");
    
  }
  
  //Always detach shaders after a successful link.
  glDetachShader(_programID, _vertexShaderID);
  glDetachShader(_programID, _fragmentShaderID);
  
  glDeleteShader(_vertexShaderID);
  glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string& attributeName) {
  glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
  //_numAttributes++; //moved to the upperline for concise
}

//enable shader + its attributes
void GLSLProgram::use() {
  glUseProgram(_programID);
  for (int i = 0; i < _numAttributes; i++) {
    glEnableVertexAttribArray(i);
  }
}

//disable the shader
void GLSLProgram::unuse() {
  glUseProgram(0);
  for (int i = 0; i < _numAttributes; i++) {
    glDisableVertexAttribArray(i);
  }
}

//compile a singe shader file
void GLSLProgram::compileShader(const string& filepath, GLuint id) {
  //cout << "hello" << endl;
  
  ifstream vertexFile(filepath);
  if (vertexFile.fail()) {
    perror(filepath.c_str());
    fatalError("Failed to open " + filepath);
  }

  string fileContents = "";
  string line;

  while (getline(vertexFile, line)) {
    fileContents += line + "\n";
  }

  vertexFile.close();

  const char* contentsPtr = fileContents.c_str();
  glShaderSource(id, 1, &contentsPtr, NULL);
  
  glCompileShader(id);

  //testing if it compiled correctly
  GLint sucess = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
  
  if (sucess == false) {
    GLint maxLength = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &maxLength);
    vector<char> errorLog(maxLength);
    glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
    glDeleteShader(id);

    //how tf does this print cause a seg fault
    //I know that &errorlog is null somehow but wtf
    //printf("%s\n", &(errorLog[0]));
    fatalError("Shader "+ filepath + " failed to compile");
  }
}
