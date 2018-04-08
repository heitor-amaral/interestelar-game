
//Link do enunciado: https://github.com/fegemo/cefet-cg/blob/master/assignments/tp1-lander/README.md#trabalho-pr%C3%A1tico-1---lander
//Link da nave (Provisório) http://pixelartmaker.com/art/2af857ae05c0f00.png

//      Coisas para fazer (Obrigatório):

//1.  'R' para reiniciar (em andamento)
//2.  Colisão com a superfície (em andamento)
//3.  HUD com altura, velocidade e aceleração (em andamento)
//4.  Física da nave (em andamento - eixo X concluido)
//5.  local de pouso
//6.  Vitoria/Derrota
//7.  foguinho sai da turbina quando o motor principal é ligado
//8.  Nave quebra quando o impacto for muito forte ou pousar inclinado

//    Extras:

//1.  Highscore salvo em Arquivo
//2.  Jogo modularizado (separar em vários arquivos)

//    O que ja foi feito:

//1.  Movimentação do Nave
//2.  Movimentação atraves de teclas WAD
//3.  Uso da gravidade
//4.  Testura temporáriada nave
//5.  Nascimento da nave no eixo X aleatório
//6.  Renascimento ao chegar no limite do mundo
//7.  HUD com altura
//8.  Tecla 'P' pausa o jogo
//9.  Rotação da nave
//10. Tecla 'esc' para sair pede confirmação antes
//11. Manter razão de aspecto

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <texto.h>

#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100

#define PI 3.14159265


GLuint texturaNave; //Variável de textura

GLuint valor;
GLfloat gravidade = 0.1;
const float aceleracao = 0.8;
GLdouble angulo = 2; //Varicao do angulo


//VARIAVEIS DE ESTADO
int estado = 1;
const int menu = 1;
const int pause = 2;
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


//Funcao que desenha a HUD
void desenhaHUD()
{
  glColor3f (1.0, 0, 0);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "ALTURA:", 85, 90);
  escreveNumero(GLUT_BITMAP_TIMES_ROMAN_10, navePrincipal.posicao.y , 95, 90);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "ANGULO:", 85, 88);
  escreveNumero(GLUT_BITMAP_TIMES_ROMAN_10, navePrincipal.angulo , 95, 88);
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "ACELERACAO:", 85, 86);
  escreveNumeroFloat(GLUT_BITMAP_TIMES_ROMAN_10, aceleracaoNave , 85, 84);

}


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

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void desenhaChao(){

  glColor3f(1,0,0);

  double i;
  glBegin(GL_LINES);
    for(i=0; i<LARGURA_DO_MUNDO; i+=0.001){
      glVertex2d(i, sin(0.3*i)+5);
    }
  glEnd();

/*   glBegin(GL_POLYGON);
    glVertex2f(0,5); // Vertice 1
    glVertex2f(100,5);
    glVertex2f(100,10);
    glVertex2f(0,10);
  glEnd(); */

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

void telaReiniciar()
{
   glClear(GL_COLOR_BUFFER_BIT);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 20, 0);
        glVertex3f(80, 20, 0);
        glVertex3f(80, 80, 0);
        glVertex3f(20, 80, 0);
    glEnd();
    glFlush();

    glColor3f(0.3f,0.3f,0.3f);
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "VOCE MORREU, APERTE R PARA REINICIAR", 45, 50);
}

void telaMenu()
{

  glClear(GL_COLOR_BUFFER_BIT);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 20, 0);
        glVertex3f(80, 20, 0);
        glVertex3f(80, 80, 0);
        glVertex3f(20, 80, 0);
    glEnd();
    glFlush();

    glColor3f(0.3f,0.3f,0.3f);
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "APERTE ENTER PARA INICIAR O JOGO", 40, 50);
}

void telaSair()
{

  glClear(GL_COLOR_BUFFER_BIT);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 20, 0);
        glVertex3f(80, 20, 0);
        glVertex3f(80, 80, 0);
        glVertex3f(20, 80, 0);
    glEnd();
    glFlush();

    glColor3f(0.3f,0.3f,0.3f);
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "TEM CERTEZA QUE DESEJA SAIR?", 40, 50);
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_10, "APERTE 'S' PARA SAIR OU ENTER PARA VOLTAR AO JOGO", 30, 45);
}


void desenhaCena(void)
{
    if(estado == menu)
    {
      telaMenu();
    }

    else if (estado == pause)
    {
      telaDePause();
    }

    else if(estado == reiniciar)
    {
      telaReiniciar();
    }

    else if(estado == jogo)
    {

      desenhaNave();

      if(forcaPropulsao > forcaGravitacional)
         {
            forcaPropulsao -= 0.004;
         }

      desenhaHUD();

      desenhaChao();


    }

    if(estado == sair)
    {
      telaSair();
    }

    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void atualizaPosicao()
{


  if(estado == jogo)
  {
    //LIMITE PROVISÓRIO DO MUNDO
    if(navePrincipal.posicao.x < 10)
    {
      valor = (-1)*(valor); // troca o sinal
      //navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 10;
    }

    else if(navePrincipal.posicao.x > 90)
    {
      valor = (-1)*(valor); // troca o sinal
      //navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 10;
    }

    if(navePrincipal.posicao.y < 10)
    {
      valor = (-1)*(valor); // troca o sinal
      //navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 10;
    }

    else if(navePrincipal.posicao.y > 90)
    {
      valor = (-1)*(valor); // troca o sinal
      //navePrincipal.posicao.x = 10 + rand() % 80;
      navePrincipal.posicao.y = 10;
    }

    navePrincipal.posicao.y += -gravidade + aceleracaoNave;

    if(navePrincipal.angulo == 360 || navePrincipal.angulo == -360) //não deixa o angulo de rotação passar de 360 graus
    {
      navePrincipal.angulo = 0;
    }

    //ATUALIZA POSICAO DA NAVE
    aceleracaoNave = forcaPropulsao - forcaGravitacional;

       navePrincipal.posicao.x += aceleracaoNave*sin(-(navePrincipal.angulo * PI) / 180); //Velocidade no eixo x. OBS: O angulo da nave deve ser transformado em radianos
       navePrincipal.posicao.y += aceleracaoNave*cos((navePrincipal.angulo * PI) / 180); //Velocidade no eixo y. OBS: O angulo da nave deve ser transformado em radianos  */
    //ATULIZA POSICAO DA NAVE

       if(apertarW == 0)
       {
        forcaPropulsao-= 0.0009;
       }

  }
  glutPostRedisplay();
  glutTimerFunc(17, atualizaPosicao, 0); //60FPS

}

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
void redimensiona(int width, int height)
{
glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA_DO_MUNDO, 0, ALTURA_DO_MUNDO, -1, 1);

    float razaoAspectoJanela = ((float)width)/height;
    float razaoAspectoMundo = ((float) LARGURA_DO_MUNDO)/ ALTURA_DO_MUNDO;
    // se a janela está menos larga do que o mundo (16:9)...
    if (razaoAspectoJanela < razaoAspectoMundo) {
        // vamos colocar barras verticais (acima e abaixo)
        float hViewport = width / razaoAspectoMundo;
        float yViewport = (height - hViewport)/2;
        glViewport(0, yViewport, width, hViewport);
    }
    // se a janela está mais larga (achatada) do que o mundo (16:9)...
    else if (razaoAspectoJanela > razaoAspectoMundo) {
        // vamos colocar barras horizontais (esquerda e direita)
        float wViewport = ((float)height) * razaoAspectoMundo;
        float xViewport = (width - wViewport)/2;
        glViewport(xViewport, 0, wViewport, height);
    } else {
        glViewport(0, 0, width, height);
    }

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
      estado = sair;
     break;

     case 'w': //Movimenta para cima
     case 'W':
     apertarW = 1;
    forcaPropulsao += 0.015; //incrementa a forca propulsao
    printf("Fp = %f\n",forcaPropulsao);
       break;

     case 'a': //Rotaciona para a esquerda
     case 'A':
       navePrincipal.angulo += angulo;
       break;

     case 'd': //Rotaciona para a direita
     case 'D':
       navePrincipal.angulo -= angulo;
       break;

    case 'p': //Pausa o jogo
    case 'P':
      if(estado == pause)
      {
        estado = jogo;
      }

      else estado = pause;
      break;

      case 13:
      if(estado == menu)
      {
        estado = jogo;
      }

      if(estado == sair)
      {
        estado = jogo;
      }

      case 's':
      case 'S':
        if(estado == sair)
        {
          exit(0);
        }
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
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 400);

    // Abre a janela
    glutCreateWindow("Navinha v0.4");

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
