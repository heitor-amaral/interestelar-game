#include "texturas.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void CodigoCarregamento()
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void carregaTextura()
{

//INICIO DAS TEXTURAS NORMAL GAME


	  //TEXTURA NAVE
    texturaNave = SOIL_load_OGL_texture(
         "./texturas/nave2.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

    CodigoCarregamento();    

    if (texturaNave == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 1: '%s'\n", SOIL_last_result());
    }
    //TEXTURA NAVE


    //TEXTURA PAUSE
    texturaPause = SOIL_load_OGL_texture(
         "./texturas/Pause.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

    CodigoCarregamento();

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

    CodigoCarregamento();

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

    CodigoCarregamento();

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

    CodigoCarregamento();

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

   CodigoCarregamento();

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

   CodigoCarregamento();

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

   CodigoCarregamento();

   if (texturaFundoJogo01 == 0) //verifica se a textura carregou corretamente
   {
      printf("Erro do SOIL 8: '%s'\n", SOIL_last_result());
   }

     texturaFundoJogo02 = SOIL_load_OGL_texture(
         "./texturas/fundo02.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

    CodigoCarregamento();

    if (texturaFundoJogo02 == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 9: '%s'\n", SOIL_last_result());
    }
    //TEXTURA FUNDO JOGO


    //TEXTURA BASE POUSO
    texturaBasePouso = SOIL_load_OGL_texture(
       "./texturas/Base-Pouso.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaBasePouso == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 10: '%s'\n", SOIL_last_result());
    }
    //TEXTURA BASE POUSO


    //TEXTURA MENU
    menu_sem_escrita = SOIL_load_OGL_texture(
      "./texturas/Menu_sem_escrita.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (menu_sem_escrita == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 11: '%s'\n", SOIL_last_result());
    }
    //TEXTURA MENU


    //TEXTURA CONTROLES
    texturaControles = SOIL_load_OGL_texture(
      "./texturas/Controle.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaControles == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 12: '%s'\n", SOIL_last_result());
    }
    //TEXTURA CONTROLES


    //TEXTURA SPACEBAR
    texturaPressSpacebarToContinue = SOIL_load_OGL_texture(
      "./texturas/PressSpacebarToContinue.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaPressSpacebarToContinue == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 13: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SPACEBAR


    //TEXTURA CREDITOS
    texturaCreditos = SOIL_load_OGL_texture(
      "./texturas/creditos.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaCreditos == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 14: '%s'\n", SOIL_last_result());
    }
    //TEXTURA CREDITOS


    //TEXTURA SCORE
    texturaScore = SOIL_load_OGL_texture(
      "./texturas/Score.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaScore == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 15: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SCORE


    //TEXTURA SPRITESHEET MENU
    SpriteSheet_Menu = SOIL_load_OGL_texture(
      "./texturas/SpriteSheet_Menu.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (SpriteSheet_Menu == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 16: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SPRITESHEET MENU


//===========================================================================================


//INICIO DAS TEXTURAS ONE SWITCH

    //TEXTURA SCORE
    texturaScoreOneSwitch = SOIL_load_OGL_texture(
      "./texturas/TOPSCOREOneSwitch.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaScoreOneSwitch == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 17: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SCORE


    //TEXTURA CREDITOS
    texturaCreditosOneSwitch = SOIL_load_OGL_texture(
      "./texturas/creditoOneSwitch.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaCreditosOneSwitch == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 18: '%s'\n", SOIL_last_result());
    }
    //TEXTURA CREDITOS


    //TEXTURA CONTROLES
    texturaControlesOneSwitch = SOIL_load_OGL_texture(
      "./texturas/ControleOneSwitch.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaControlesOneSwitch == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 19: '%s'\n", SOIL_last_result());
    }
    //TEXTURA CONTROLES


    //TEXTURA MENU
    texturaMenuOneSwitch = SOIL_load_OGL_texture(
      "./texturas/MenuOneSwitch.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaMenuOneSwitch == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 20: '%s'\n", SOIL_last_result());
    }
    //TEXTURA MENU


    //TEXTURA DERROTA
    texturaDerrotaOneSwitch = SOIL_load_OGL_texture(
       "./texturas/DerrotaOneSwitch.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (texturaDerrotaOneSwitch == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 21: '%s'\n", SOIL_last_result());
    }
    //TEXTURA DERROTA


    //TEXTURA SPRITE DERROTA
    SpriteDerrota = SOIL_load_OGL_texture(
      "./texturas/Sprite_derrota.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (SpriteDerrota == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 22: '%s'\n", SOIL_last_result());
    }
    //TEXTURA SPRITE DERROTA


    //TEXTURA SPRITE VITORIA
    SpriteVitoria = SOIL_load_OGL_texture(
      "./texturas/Sprite_vitoria.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
    );

    CodigoCarregamento();

    if (SpriteVitoria == 0) //verifica se a textura carregou corretamente
    {
      printf("Erro do SOIL 23: '%s'\n", SOIL_last_result());
    }

    //TEXTURA SPRITE VITORIA


    //TEXTURA VITORIA
    texturaVitoriaOneSwitch = SOIL_load_OGL_texture(
         "./texturas/VitoriaOneSwitch.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

      CodigoCarregamento();

      if (texturaVitoriaOneSwitch == 0) //verifica se a textura carregou corretamente
      {
         printf("Erro do SOIL 24: '%s'\n", SOIL_last_result());
      }
      //TEXTURA VITORIA


    //PRE JOGO
    texturaPreJogo = SOIL_load_OGL_texture(
         "./texturas/PreJogo.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

      CodigoCarregamento();

      if (texturaPreJogo == 0) //verifica se a textura carregou corretamente
      {
         printf("Erro do SOIL 25: '%s'\n", SOIL_last_result());
      }
    //PRE JOGO


    //SPRITE PRE JOGO
    SpritePreJogo = SOIL_load_OGL_texture(
         "./texturas/SpritePre.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
     );

    CodigoCarregamento();

    if (SpritePreJogo == 0) //verifica se a textura carregou corretamente
    {
       printf("Erro do SOIL 26: '%s'\n", SOIL_last_result());
    }
    //SPRITE PRE JOGO


// FIM DAS TEXTURAS ONE SWITCH
//====================================================================================

}
