#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

int main(int argc, char **argv) {
    
  image = readBMP(argv[1]);
  if (!image) return 1;

  // Inicializar GLUT
  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
