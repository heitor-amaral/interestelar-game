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
       "./texturas/Pause.png",
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
       "./texturas/Inicio.png",
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
       "./texturas/Sair.png",
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
       "./texturas/Derrota.png",
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
      "./texturas/Reset.png",
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
     "./texturas/Vitoria.png",
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
texturaFundoJogo01 = SOIL_load_OGL_texture(
    "./texturas/fundo01.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
   SOIL_FLAG_INVERT_Y
);

 glEnable( GL_BLEND );
 glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

 if (texturaFundoJogo01 == 0) //verifica se a textura carregou corretamente
 {
    printf("Erro do SOIL 7: '%s'\n", SOIL_last_result());
 }

 texturaFundoJogo02 = SOIL_load_OGL_texture(
     "./texturas/fundo02.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
 );

  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  if (texturaFundoJogo02 == 0) //verifica se a textura carregou corretamente
  {
     printf("Erro do SOIL 7: '%s'\n", SOIL_last_result());
  }
 //TEXTURA FUNDO JOGO

 //TEXTURA BASE POUSO
texturaBasePouso = SOIL_load_OGL_texture(
   "./texturas/Base-Pouso.png",
   SOIL_LOAD_AUTO,
   SOIL_CREATE_NEW_ID,
  SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (texturaBasePouso == 0) //verifica se a textura carregou corretamente
{
   printf("Erro do SOIL 20: '%s'\n", SOIL_last_result());
}
//TEXTURA BASE POUSO

//TEXTURA MENU
menu_sem_escrita = SOIL_load_OGL_texture(
  "./texturas/Menu_sem_escrita.png",
  SOIL_LOAD_AUTO,
  SOIL_CREATE_NEW_ID,
 SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (menu_sem_escrita == 0) //verifica se a textura carregou corretamente
{
  printf("Erro do SOIL 11: '%s'\n", SOIL_last_result());
}
//TEXTURA MENU

//TEXTURA SpriteSheet_Menu
SpriteSheet_Menu = SOIL_load_OGL_texture(
  "./texturas/SpriteSheet_Menu.png",
  SOIL_LOAD_AUTO,
  SOIL_CREATE_NEW_ID,
 SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (SpriteSheet_Menu == 0) //verifica se a textura carregou corretamente
{
  printf("Erro do SOIL 12: '%s'\n", SOIL_last_result());
}
//TEXTURA SpriteSheet_Menu

//TEXTURA CONTROLES
texturaControles = SOIL_load_OGL_texture(
  "./texturas/Controle.png",
  SOIL_LOAD_AUTO,
  SOIL_CREATE_NEW_ID,
 SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (texturaControles == 0) //verifica se a textura carregou corretamente
{
  printf("Erro do SOIL 13: '%s'\n", SOIL_last_result());
}
//TEXTURA CONTROLES

//TEXTURA SPACEBAR
texturaPressSpacebarToContinue = SOIL_load_OGL_texture(
  "./texturas/PressSpacebarToContinue.png",
  SOIL_LOAD_AUTO,
  SOIL_CREATE_NEW_ID,
 SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (texturaPressSpacebarToContinue == 0) //verifica se a textura carregou corretamente
{
  printf("Erro do SOIL 14: '%s'\n", SOIL_last_result());
}
//TEXTURA SPACEBAR

//TEXTURA CREDITOS
texturaCreditos = SOIL_load_OGL_texture(
  "./texturas/creditos.png",
  SOIL_LOAD_AUTO,
  SOIL_CREATE_NEW_ID,
 SOIL_FLAG_INVERT_Y
);

glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

if (texturaCreditos == 0) //verifica se a textura carregou corretamente
{
  printf("Erro do SOIL 15: '%s'\n", SOIL_last_result());
}
//TEXTURA CREDITOS

}
