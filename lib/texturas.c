#include "texturas.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void carregaTextura()
{
	//TEXTURA NAVE
  texturaNave = SOIL_load_OGL_texture(
       "./texturas/nave2.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if (texturaNave == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
    //TEXTURA NAVE

    //TEXTURA PAUSE
  texturaPause = SOIL_load_OGL_texture(
       "./texturas/Pause.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if (texturaPause == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 2: '%s'\n", SOIL_last_result());
    }
    //TEXTURA PAUSE

    //TEXTURA INICIO
  texturaInicio = SOIL_load_OGL_texture(
       "./texturas/Inicio.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if (texturaInicio == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 3: '%s'\n", SOIL_last_result());
    }
    //TEXTURA INICIO

      //TEXTURA SAIR
  texturaSair = SOIL_load_OGL_texture(
       "./texturas/Sair.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if (texturaSair == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 4: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SAIR

     //TEXTURA DERROTA
  texturaDerrota = SOIL_load_OGL_texture(
       "./texturas/Derrota.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if (texturaDerrota == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 5: '%s'\n", SOIL_last_result());
    }
    //TEXTURA DERROTA

    //TEXTURA RESET
 texturaReset = SOIL_load_OGL_texture(
      "./texturas/Reset.jpg",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
  );

   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   if (texturaReset == 0) //verifica se a textura carregou corretamente
   {
      printf("Erro do SOIL 6: '%s'\n", SOIL_last_result());
   }
   //TEXTURA RESET

   //TEXTURA VITORIA
texturaVitoria = SOIL_load_OGL_texture(
     "./texturas/Vitoria.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
 );

  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  if (texturaVitoria == 0) //verifica se a textura carregou corretamente
  {
     printf("Erro do SOIL 7: '%s'\n", SOIL_last_result());
  }
  //TEXTURA VITORIA

  //TEXTURA FUNDO JOGO
texturaFundoJogo = SOIL_load_OGL_texture(
    "./texturas/FundoJogo.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
   SOIL_FLAG_INVERT_Y
);

 glEnable( GL_BLEND );
 glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

 if (texturaFundoJogo == 0) //verifica se a textura carregou corretamente
 {
    printf("Erro do SOIL 7: '%s'\n", SOIL_last_result());
 }
 //TEXTURA FUNDO JOGO
}