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

  //Bucle para cambiar todas las matrices de color a b y n
  for (int y = 0; y < (int)image->height; y++) {
    for (int x = 0; x < (int)image->width; x++) {
      unsigned char *pixel = &image->data[(y * image->width + x) * 3];
      unsigned char gray = (unsigned char)(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
      pixel[0] = gray;
      pixel[1] = gray;
      pixel[2] = gray;
    }
  }
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
