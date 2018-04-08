
//Link do enunciado: https://github.com/fegemo/cefet-cg/blob/master/assignments/tp1-lander/README.md#trabalho-pr%C3%A1tico-1---lander
//Link da nave (Provisório) http://pixelartmaker.com/art/2af857ae05c0f00.png

//      Coisas para fazer (Obrigatório):

//1. redimensionamento
//2. Rotacionar o Quadrado
//3. 'R' para reiniciar
//4. Colisão com a superfície
//5. HUD com altura, velocidade e aceleração

//    O que ja foi feito:

//1. Movimentação do Quadrado
//2. Movimentação atraves de teclas WAD
//3. Uso da gravidade
//4. Testura temporáriada nave
//5. Nascimento da nave no eixo X aleatório
//6. Renascimento ao chegar no limite do mundo
//7. HUD com altura
//8. Tecla 'P' pausa o jogo

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <texto.h>


#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100

#define PI 3.14159265

GLuint texturaNave; //Variável de textura

bool pause = false;

GLuint valor;
GLfloat gravidade = 0.1;
const float aceleracao = 0.8;
GLdouble angulo = 2; //Varicao do angulo


//VARIAVEIS DE ESTADO
int estado = 1;
const int menu = 1;
const int reiniciar = 3;
const int jogo = 4;
const int sair = 9;
//VAIIAVEIS DE ESTADO

//VARIAVEIS DE FISICA
float forcaPropulsao = 0; //Aperte W para aumentar
float forcaGravitacional = 0.1;
float massaNave = 1;
float aceleracaoNave;
int apertarW = 0;

//lembre que Fp-Fg = m*a

//VARIAVEIS FISICAS

struct coordenadas //Estrutura de coordenadas
{
  GLfloat x,y;
};

struct Tamanho
{
  GLfloat largura, altura;
};

typedef struct coordenadas ponto; //Posição
typedef struct coordenadas vetor; // Vetor
typedef struct Tamanho tamanho; // Tamanho

typedef struct nave // Estrutura da nave
{
  ponto posicao;
  vetor velocidade;
  tamanho tamanhoNave;
  GLdouble angulo; //
} nave;

nave navePrincipal;

void desenhaNave()
{

    glClear(GL_COLOR_BUFFER_BIT);
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaNave);
    glColor3f(0, 1, 0);

    glPushMatrix();
      // carrega uma Matriz Identidade, só pra garantir
      glLoadIdentity();

      // translada o sistema de coordenadas para (x,y)
      glTranslatef(navePrincipal.posicao.x, navePrincipal.posicao.y, 0);
      // rotaciona o sistema de coordenadas no próprio lugar
      glRotated(navePrincipal.angulo, 0, 0, 1);

      glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0, 0); glVertex2f( - navePrincipal.tamanhoNave.largura/2, - navePrincipal.tamanhoNave.altura/2); // Vertice 1

          glTexCoord2f(1, 0); glVertex2f( + navePrincipal.tamanhoNave.largura/2, - navePrincipal.tamanhoNave.altura/2);

          glTexCoord2f(1, 1); glVertex2f( + navePrincipal.tamanhoNave.largura/2,  + navePrincipal.tamanhoNave.altura/2);

          glTexCoord2f(0, 1); glVertex2f( - navePrincipal.tamanhoNave.largura/2,  + navePrincipal.tamanhoNave.altura/2);
        glEnd();

        // glBegin(GL_TRIANGLE_FAN);
        //   glTexCoord2f(0, 0); glVertex2f(navePrincipal.posicao.x - navePrincipal.tamanhoNave.largura/2,
        //      navePrincipal.posicao.y - navePrincipal.tamanhoNave.altura/2); // Vertice 1
        //   glTexCoord2f(1, 0); glVertex2f(navePrincipal.posicao.x + navePrincipal.tamanhoNave.largura/2,
        //      navePrincipal.posicao.y - navePrincipal.tamanhoNave.altura/2);
        //   glTexCoord2f(1, 1); glVertex2f(navePrincipal.posicao.x + navePrincipal.tamanhoNave.largura/2,
        //      navePrincipal.posicao.y + navePrincipal.tamanhoNave.altura/2);
        //   glTexCoord2f(0, 1); glVertex2f(navePrincipal.posicao.x - navePrincipal.tamanhoNave.largura/2,
        //     navePrincipal.posicao.y + navePrincipal.tamanhoNave.altura/2);
        // glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void desenhaChao(){

  glColor3f(1,0,0);

  glBegin(GL_LINE_STRIP);
    glVertex2f(0,5); // Vertice 1
    glVertex2f(100,5);
  glEnd();
}

//Funcao de desenho da tela de pause
void telaDePause()
{

   glClear(GL_COLOR_BUFFER_BIT);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_POLYGON);
        glVertex3f(20, 20, 0);
        glVertex3f(80, 20, 0);
        glVertex3f(80, 80, 0);
        glVertex3f(20, 80, 0);
    glEnd();
    glFlush();

  glColor3f(0.3f,0.3f,0.3f);
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "PAUSE", 45, 50);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "APERTE 'P' PARA VOLTAR AO JOGO", 40, 45);
}

void desenhaHUD()
{
  glColor3f (1.0, 0, 0);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "ALTURA:", 85, 90);
  escreveNumero(GLUT_BITMAP_TIMES_ROMAN_10, navePrincipal.posicao.y , 95, 90);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "ANGULO:", 85, 85);
  escreveNumero(GLUT_BITMAP_TIMES_ROMAN_10, navePrincipal.angulo , 95, 85);
}

void desenhaCena(void)
{
    //Checa se o jogo esta pausado
    if(!pause){

      desenhaNave();

      desenhaHUD();

      desenhaChao();
    }

    else{
      telaDePause();
    }



    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void atualizaPosicao()
{


  if(!pause){
    srand(time(NULL));
    //LIMITE PROVISÓRIO DO MUNDO
    if(navePrincipal.posicao.x < 10)
    {
      valor = (-1)*(valor); // troca o sinal
      navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 90;
    }

    else if(navePrincipal.posicao.x > 90)
    {
      valor = (-1)*(valor); // troca o sinal
      navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 90;
    }

    if(navePrincipal.posicao.y < 10)
    {
      valor = (-1)*(valor); // troca o sinal
      navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 90;
    }

    else if(navePrincipal.posicao.y > 90)
    {
      valor = (-1)*(valor); // troca o sinal
      navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 90;
    }

    navePrincipal.posicao.y -= gravidade;
  }
  
  glutPostRedisplay();
  glutTimerFunc(17, atualizaPosicao, 0); //60FPS
}


//Funcao que desenha a HUD

// Inicia algumas variáveis de estado
void inicializa(void)
{

  // Sets de carregamento da SOIL
  texturaNave = SOIL_load_OGL_texture(
    "./src/nave.png",
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

    // cor para limpar a tela
    glClearColor(0, 0, 0, 0);      // Preto

      valor = 1;
      navePrincipal.tamanhoNave.largura = 10;
      navePrincipal.tamanhoNave.altura = 10;
      navePrincipal.posicao.x = 10 + rand() % 80; //Posição Aleatória de início da nave
      navePrincipal.posicao.y = 90;
      navePrincipal.angulo = 0.0;

      // imprime instruções
  printf("\nInstrucoes:\n");
  printf("\t\tWAD: Movimenta o Quadrado \n");

}

// Callback de redimensionamento
void redimensiona(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 100, 0, 100, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Callback de evento de teclado
void teclado(unsigned char key, int x, int y)
{
   switch(key)
   {
      // Tecla ESC
    case 27:
     exit(0);
     break;

     case 'w': //Movimenta para cima
     case 'W':
      navePrincipal.posicao.x += aceleracao*sin(-(navePrincipal.angulo * PI) / 180); //Velocidade no eixo x. OBS: O angulo da nave deve ser transformado em radianos
       navePrincipal.posicao.y += aceleracao*cos((navePrincipal.angulo * PI) / 180); //Velocidade no eixo y. OBS: O angulo da nave deve ser transformado em radianos
       // glutPostRedisplay();
       break;

     case 'a': //Rotaciona para a esquerda
     case 'A':
       navePrincipal.angulo += angulo;
       // glutPostRedisplay();
       break;

     case 'd': //Rotaciona para a direita
     case 'D':
       navePrincipal.angulo -= angulo;
       // glutPostRedisplay();
       break;

    case 'p': //Pausa o jogo
    case 'P':
      pause = !pause;
      break;

    default:
       break;
   }
}

// Rotina principal
int main(int argc, char **argv)
{
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);

    // Abre a janela
    glutCreateWindow("Navinha v0.3");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    inicializa();

    // Registra a função "atualizaPosicao" para executar daqui a 0 milissegundos
    glutTimerFunc(0, atualizaPosicao, 0);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
