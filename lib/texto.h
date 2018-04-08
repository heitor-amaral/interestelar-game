#include "texto.h"
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void escreveTexto(void* font, char* s, float x, float y) {
  unsigned int i;
  glRasterPos2f(x, y);

  for (i = 0; i < strlen (s); i++) {// menor que
     glutBitmapCharacter(font, s[i]);
  }
}

void escreveNumero(void* font, int numero, float x, float y) {
  unsigned int i;
  glRasterPos2f(x, y);
  char buffer[50];
  sprintf( buffer, "%d", numero );
  for (i = 0; i < strlen (buffer); i++) {// menor que
     glutBitmapCharacter(font, buffer[i]);
  }
}

void escreveNumeroFloat(void* font, float numero, float x, float y) {
  unsigned int i;
  glRasterPos2f(x, y);
  char buffer[50];
  sprintf( buffer, "%f", numero );
  for (i = 0; i < strlen (buffer); i++) {// menor que
     glutBitmapCharacter(font, buffer[i]);
  }
}
