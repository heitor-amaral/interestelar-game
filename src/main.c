
//LINK DO ENUNCIADO: https://github.com/fegemo/cefet-cg/blob/master/assignments/tp1-lander/README.md#trabalho-pr%C3%A1tico-1---lander
//LINK DA NAVE (Provisório) http://pixelartmaker.com/art/2af857ae05c0f00.png

//COISAS A FAZER:
//1.  'R' para reiniciar
//2.  local de pouso
//3.  foguinho sai da turbina quando o motor principal é ligado
//4.  Nave quebra quando o impacto for muito forte ou pousar inclinado
//5.  Movimentação da nave via setinhas

//EM ANDAMENTO:
//1.  HUD
//2.  Arrumar BUG na nave quando acelerada para baixo
//3.  Arrumar razão aspecto de escrita na tela
//4.  Vitoria/Derrota

//OBJETIVOS CONCLUIDOS:
//1.  Movimentação da Nave atraves de teclas WAD
//2.  Textura temporáriada nave
//3.  Tecla 'P' pausa o jogo
//4.  Rotação da nave
//5.  Tecla 'esc' para sair pede confirmação antes
//6.  Fisica da nave
//7.  Manter razão de aspecto


#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <texto.h>


#define LARGURA_DO_MUNDO 1200
#define ALTURA_DO_MUNDO 1200

#define LARGURA 50
#define ALTURA 50

float apertar = 0; // Apertar 'W'

//VARIAVEIS DE TEXTURA
int texturaNave;
int texturaPause;
int texturaInicio;
int texturaSair;
int texturaDerrota;
//VARIAVEIS DE TEXTURA

//VARIAVEIS DE ESTADO
const int jogo = 1;
const int pause = 2;
const int inicio = 3;
const int sair = 4;
const int Derrota = 5;
int estado = 3;
//VARIAVEIS DE ESTADO

typedef struct navinha // Estrutura da nave
{
  float velocidadeEmY;
	float velocidadeEmX;
	float posicaoX;
	float posicaoY;
	float gravidade;
	float aceleracaoX;
	float aceleracaoY;
	float angulo;
  bool motor;
} navinha;

navinha nave;

void carregaTextura()
{
	//TEXTURA NAVE
  texturaNave = SOIL_load_OGL_texture(
       "./texturas/nave.png",
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
}

void desenhaHUD()
{
	glColor3f(0.0, 0.0, 0.0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "VELOCIDADE EM X", 700, 1000); //velocidade em X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.velocidadeEmX, 1000, 1000);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "VELOCIDADE EM Y", 700, 950); // velocidade em Y
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.velocidadeEmY, 1000, 950);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ALTURA", 700, 900); // Altura
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.posicaoY, 1000, 900);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ACELERACAO EM X", 700, 850); //ACELERACAO EM X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.aceleracaoX, 1000, 850);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ACELERACAO EM Y", 700, 800); //ACELERACAO EM X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.aceleracaoY, 1000, 800);

		escreveTexto(GLUT_BITMAP_HELVETICA_18, "ANGULO", 700, 750); //ANGULO DA NAVE
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.angulo, 1000, 750);
}

void quadradoDoTamanhoDaTela()
{
    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);	glVertex2f(0,0);
        glTexCoord2f(1, 0);	glVertex2f(LARGURA_DO_MUNDO, 0);
        glTexCoord2f(1, 1);	glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
        glTexCoord2f(0, 1);	glVertex2f(0, ALTURA_DO_MUNDO);

    glEnd();
}

void desenhaPause()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaPause);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaInicio()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaInicio);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaSair()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaSair);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaDerrota()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaDerrota);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}


void desenhaQuadrado()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaNave);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(nave.posicaoX,nave.posicaoY, 0);
    glRotated(nave.angulo, 0, 0, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);	glVertex2f(-LARGURA/2, -ALTURA/2);
        glTexCoord2f(1, 0);	glVertex2f(LARGURA/2, -ALTURA/2);
        glTexCoord2f(1, 1);	glVertex2f(LARGURA/2, ALTURA/2);
        glTexCoord2f(0, 1);	glVertex2f(-LARGURA/2, ALTURA/2);

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DesenhaChao()
{
	int altura = 20;

	glColor3f(0, 1, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        glVertex2f(LARGURA_DO_MUNDO, 0);
        glVertex2f(LARGURA_DO_MUNDO, altura);
        glVertex2f(0, altura);
    glEnd();
}

void desenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    // Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar

    if(estado == jogo)
    {
    	desenhaHUD();
    	DesenhaChao();
    	desenhaQuadrado();
    }

    else if(estado == pause)
    {
    	desenhaPause();
    }

    else if(estado == inicio)
    {
    	desenhaInicio();
    }

    else if(estado == sair)
    {
    	desenhaSair();
    }

    else if(estado == Derrota)
    {
    	desenhaDerrota();
    }

    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void chao()
{
	if(nave.posicaoY < 45)
		{
			if(nave.velocidadeEmY < -1)
			{
				estado = Derrota;
			}

			else
			{
				nave.posicaoY = 45;
				nave.velocidadeEmY = 0;
				nave.velocidadeEmX = 0;
				nave.aceleracaoY = 0;
				nave.aceleracaoX = 0;
			}

		}
}

void atualiza()
{
	if(estado == jogo)
	{
		if(nave.motor)
		{
			nave.posicaoY += nave.velocidadeEmY;
      // * cos((nave.angulo * M_PI) / 180);

			// if(nave.angulo>= 0 && nave.angulo <= 180)
			// {
				nave.posicaoX += nave.velocidadeEmX;
        // * sin(-(nave.angulo * M_PI) / 180);
			// }

			// else nave.posicaoX += nave.aceleracaoX * sin(-(nave.angulo * M_PI) / 180);
		}

		else
		{
			nave.posicaoY += nave.velocidadeEmY;
			nave.posicaoX += nave.velocidadeEmX;
		}

		nave.motor = false;

		nave.velocidadeEmY += nave.gravidade;

		chao();

		if(nave.angulo == 360 || nave.angulo == -360) //Reseta o angulo
		{
			nave.angulo = 0;
		}
	}

		glutPostRedisplay();
		glutTimerFunc(17, atualiza, 0);
}

// Inicia algumas variáveis de estado
void inicializa(void)
{
	carregaTextura();

    // cor para limpar a tela
  glClearColor(1, 1, 1, 0);      // branco
	int estado = inicio;
  nave.posicaoX = 500;
  nave.posicaoY = 500;
  nave.gravidade = -0.01;
  nave.velocidadeEmY = 0;
  nave.velocidadeEmX = 0;
  nave.aceleracaoX = 0.05;
  nave.aceleracaoY = 0.05;
  nave.angulo = 0;
  nave.motor = false;
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

      	 if(estado == Derrota)
      	 {
      	 	exit(0);
      	 }

      	 if(estado == jogo)
      	 {
         estado = sair;
      	 }
         break;

      case 'w':
      case 'W':
      	if(estado == jogo)
      	{
      		nave.motor = true;
      		nave.velocidadeEmY += nave.aceleracaoY * cos((nave.angulo * M_PI) / 180);
      		nave.velocidadeEmX += nave.aceleracaoX * sin(-(nave.angulo * M_PI) / 180);
      		//nave.velocidadeEmY += 0.05;
      	}
      break;

      case 'd':
      case 'D':
      if(estado == jogo)
      {
      	nave.angulo-=2;
      }
      break;

      case 'a':
      case 'A':
      if(estado == jogo)
      {
      	nave.angulo+=2;
      }
      break;

      case 'p':
      case 'P':
      	if(estado == jogo)
      	{
      		estado = pause;
      	}

      	else estado = jogo;
      break;

      case 13: //ENTER
      	estado = jogo;
      break;

      case 's':
      case 'S':
      {
      	if(estado == sair)
      	{
      		exit(0);
      	}
      }
      break;

      case 'n':
      case 'N':
      {
      	if(estado == sair)
      	{
      		estado = jogo;
      	}
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
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Navinha v0.5");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    inicializa();

    glutTimerFunc(0, atualiza, 0);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
