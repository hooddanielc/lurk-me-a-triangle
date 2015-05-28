#define GL_GLEXT_PROTOTYPES

#include <cassert>
#include <iostream>
#include <GL/glut.h>
#include <glm/glm.hpp>

const char VERTEX_SHADER[] =
"  attribute vec3 vertexPosition;"
"  attribute vec4 vertexColor;"
"  uniform mat4 modelViewMatrix;"
"  uniform mat4 projectionMatrix;"
"  varying vec4 vColor;"

"  void main(void) {"
"    gl_Position = projectionMatrix * modelViewMatrix *"
"      vec4(vertexPosition, 1.0);"
"    vColor = vertexColor;"
"  }";

const char FRAGMENT_SHADER[] =
"  precision mediump float;"
"  varying vec4 vColor;"

"  void main(void) {"
"    gl_FragColor = vColor;"
"  }";

GLuint loadShader(GLenum type, const char *src) {
  const GLuint id = glCreateShader(type);
  assert(id);
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  GLint compiled = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
  assert(compiled);
  return id;
}

void resize(int width, int height) {
  std::cout << "resize x: " << width << std::endl;
  std::cout << "resize y: " << height << std::endl;
}

void draw() {
  /* do nothing */
}

void update() {
  /* do nothing */
}

void init() {
  /* compile some shaders into program */
  auto vertexShaderID = loadShader(GL_VERTEX_SHADER, VERTEX_SHADER);
  auto fragmentShaderID = loadShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);
  auto program = glCreateProgram();
  assert(program);
  glAttachShader(program, vertexShaderID);
  glAttachShader(program, fragmentShaderID);
  glLinkProgram(program);
  GLint linked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  assert(linked);

  // get uniform and attribute locations
  auto modelViewMatrix = glGetUniformLocation(program, "modelViewMatrix");
  auto projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
  auto vertexPosition = glGetAttribLocation(program, "vertexPosition");
  auto vertexColor = glGetAttribLocation(program, "vertexColor");

  assert(modelViewMatrix);
  assert(projectionMatrix);

  std::cout << "Got some fragment shader " << fragmentShaderID << std::endl;
  std::cout << "Got some vertex shader " << vertexShaderID << std::endl;
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("Hello Triangle");
  glutReshapeFunc(resize);
  glutDisplayFunc(draw);
  glutIdleFunc(update);
  init();
  glutMainLoop();
  std::cout << "vertex shader=" << VERTEX_SHADER << std::endl;
  std::cout << "fragment shader=" << FRAGMENT_SHADER << std::endl;
  return 0;
}
