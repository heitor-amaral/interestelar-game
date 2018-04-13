
//LINK DO ENUNCIADO: https://github.com/fegemo/cefet-cg/blob/master/assignments/tp1-lander/README.md#trabalho-pr%C3%A1tico-1---lander
//LINK DA NAVE (Provisório) http://pixelartmaker.com/art/2af857ae05c0f00.png
//CEU TEMPORARIO https://extraterrestresmyblog.wordpress.com/ceu-noite-jpg/

//COISAS A FAZER:
//1.  foguinho sai da turbina quando o motor principal é ligado
//2.  Nave quebra quando o impacto for muito forte ou pousar inclinado

//EM ANDAMENTO:
//1.  HUD
//2.  Arrumar razão aspecto de escrita na tela

//OBJETIVOS CONCLUIDOS:
//1.  Movimentação da Nave atraves de teclas WAD
//2.  Textura temporáriada nave
//3.  Tecla 'P' pausa o jogo
//4.  Rotação da nave
//5.  Tecla 'esc' para sair pede confirmação antes
//6.  Fisica da nave
//7.  Manter razão de aspecto
//8.  'R' para reiniciar
//9.  Vitoria/Derrota
//10. local de pouso
//11. Movimentação da nave via setinhas
//12. Combustivel do motor

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <config.h>
#include <texto.h>
#include <texturas.h>

navinha nave;

unsigned int tecla[256];

void resetaJogo() //Usa o preset da atualiza
{
  estado = inicio;
  xAleatorioBasePouso = rand()%1000;
  nave.posicaoX = 500;
  nave.posicaoY = 500;
  nave.gravidade = -0.01;
  nave.velocidadeEmY = 0;
  nave.velocidadeEmX = 0;
  nave.aceleracaoX = 0;
  nave.aceleracaoY = 0;
  nave.angulo = 0;
  nave.motor = 0.0;
  nave.combustivel = 1000;
}

void desenhaHUD()
{
	glColor3f(1, 1, 1);
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "VELOCIDADE EM X", 700, 1000); //velocidade em X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.velocidadeEmX, 1000, 1000);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "VELOCIDADE EM Y", 700, 950); // velocidade em Y
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.velocidadeEmY, 1000, 950);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ALTURA", 700, 900); // Altura
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.posicaoY, 1000, 900);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ACELERACAO EM X", 700, 850); //ACELERACAO EM X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.aceleracaoX * sin((-nave.angulo * M_PI) / 180) , 1000, 850);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "ACELERACAO EM Y", 700, 800); //ACELERACAO EM X
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.aceleracaoY * cos((nave.angulo * M_PI) / 180) + nave.gravidade, 1000, 800);

  	escreveTexto(GLUT_BITMAP_HELVETICA_18, "ANGULO", 700, 750); //ANGULO DA NAVE
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.angulo, 1000, 750);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "FUEL", 700, 700); //COMBUSTIVEL
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.combustivel, 1000, 700);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "MOTOR", 700, 650); //COMBUSTIVEL
    escreveNumero(GLUT_BITMAP_HELVETICA_18, nave.motor, 1000, 650);
}

void quadradoDoTamanhoDaTela()
{
    // Começa a usar a cor verde
    glColor3f(1, 1, 1);

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

void desenhaReset()
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaReset);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaVitoria()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaVitoria);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaFundoJogo()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaFundoJogo);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaBasePouso()
{
  int altura = 30;
  int largura = 100;


	glColor3f(0, 1, 0);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(xAleatorioBasePouso, 0);
        glVertex2f(xAleatorioBasePouso + largura, 0);
        glVertex2f(xAleatorioBasePouso + largura, altura);
        glVertex2f(xAleatorioBasePouso, altura);
    glEnd();
}

void desenhaNave()
{
    glColor3f(1,1,1);
   // glClear(GL_COLOR_BUFFER_BIT);
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaNave);
    
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(nave.posicaoX,nave.posicaoY, 0);
    glRotated(nave.angulo, 0, 0, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2d((0.5*nave.motor), 0);	glVertex2f(-LARGURA/2, -ALTURA/2);
        glTexCoord2d((0.5+(0.5*nave.motor)), 0);	glVertex2f(LARGURA/2, -ALTURA/2);
        glTexCoord2d((0.5+(0.5*nave.motor)), 1);	glVertex2f(LARGURA/2, ALTURA/2);
        glTexCoord2d((0.5*nave.motor), 1);	glVertex2f(-LARGURA/2, ALTURA/2);

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
      desenhaFundoJogo();
    	desenhaHUD();
    	DesenhaChao();
    	desenhaNave();
      desenhaBasePouso();
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

    else if(estado == reset)
    {
      desenhaReset();
    }

    else if(estado == vitoria)
    {
      desenhaVitoria();
    }

    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void basePouso()
{
  if(nave.posicaoY < 55 && (nave.posicaoX >= xAleatorioBasePouso && nave.posicaoX<= xAleatorioBasePouso + 100)) //100 é a largura
	{
			if(nave.velocidadeEmY < -1)
			{
				estado = Derrota;
			}

			else
			{
				nave.posicaoY = 55;
				nave.velocidadeEmY = 0;
				nave.velocidadeEmX = 0;
				nave.aceleracaoY = 0;
				nave.aceleracaoX = 0;

        estado = vitoria;
			}
	}

}

void chao()
{
	if(nave.posicaoY < 45)
	{
		estado = Derrota;
	}
}

void atualiza()
{
  
  // if(estado == inicio)
  // {

  //   if(tecla[13]==1)
  //     estado = jogo;
      
  // }

  // if(estado == pause)
  // {
  //   if(tecla[13]==1)
  //     estado = jogo;
  // }

  // if(estado == vitoria)
  // {

  //   if(tecla['s']==1)
  //     resetaJogo();
    
  //   if(tecla['n']==1)
  //     exit(0);
  // }

  // if(estado == reset)
  // {

  //   if(tecla['s'])
  //     resetaJogo();

  //   if(tecla['n'])
  //     estado = jogo;
  // }

  // if(estado == sair)
  // {

  //   if(tecla['s']==1)
  //     exit(0);
    
  //   if(tecla['n']==1)
  //     estado = jogo;
  // }
  
  // if(estado == Derrota)
  // {

  //   if(tecla['r'])
  //     resetaJogo();
  //     estado = jogo;

  //   if(tecla[27])
  //     exit(0);
  // }

	if(estado == jogo)
	{
    
    if(tecla['a']==1)
      nave.angulo+=1;

    if(tecla['d']==1)
      nave.angulo-=1;

		if(tecla['w']==1)
		{
      if(nave.combustivel>0)
      {
        nave.motor = 1;
        nave.aceleracaoY = 0.03;
        nave.aceleracaoX = 0.03;
        nave.velocidadeEmY += nave.aceleracaoY * cos((nave.angulo * M_PI) / 180);
        nave.velocidadeEmX += nave.aceleracaoX * sin(-(nave.angulo * M_PI) / 180);
        nave.posicaoY += nave.velocidadeEmY;
        nave.posicaoX += nave.velocidadeEmX;
        nave.combustivel--; 
      }
    }

		if(tecla['w']==0)
		{
      nave.motor = 0;
      nave.aceleracaoY = 0;
      nave.aceleracaoX = 0;
			nave.posicaoY += nave.velocidadeEmY;
			nave.posicaoX += nave.velocidadeEmX;
		}


		nave.velocidadeEmY += nave.gravidade;

    basePouso();
	  chao();

		if(nave.angulo == 360 || nave.angulo == -360) //Reseta o angulo
		{
			nave.angulo = 0;
		}

    // if(tecla['p']==1)
    //   estado = pause;

    // if(tecla['r']==1)
    //   estado = reset;

    // if(tecla[27]) // ESC
    //   estado = sair;
	}

		glutPostRedisplay();
		glutTimerFunc(17, atualiza, 0);
}

// Inicia algumas variáveis de estado
void inicializa(void)
{
	carregaTextura();

  xAleatorioBasePouso = rand()%1000;

  srand(time(NULL));

    // cor para limpar a tela
  glClearColor(1, 1, 1, 0);      // branco
	estado = inicio;
  nave.posicaoX = 500;
  nave.posicaoY = 500;
  nave.gravidade = -0.01;
  nave.velocidadeEmY = 0;
  nave.velocidadeEmX = 0;
  nave.aceleracaoX = 0;
  nave.aceleracaoY = 0;
  nave.angulo = 0;
  nave.motor = 0;
  nave.combustivel = 1000;
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

  tecla[key] = 1;


  switch(key)
  {
    
    case 27: // Tecla ESC

      if(estado == Derrota)
      {
        exit(0);
      }

      if(estado == jogo)
      {
        estado = sair;
      }
    break;


    case 'p':
    case 'P':
      if(estado == jogo)
      {
        estado = pause;
      }

      else if(estado == pause)
      {
        estado = jogo;
      }
    break;
    
    case 13: //ENTER
      if(estado == inicio)
      {
          estado = jogo;
      }
      break;

    case 's':
    case 'S':
    
      if(estado == sair)
      {
        exit(0);
      }

      if(estado == reset)
      {
        resetaJogo();
        estado = jogo;
      }
    
      if(estado == vitoria)
      {
          resetaJogo();
          estado = jogo;
      }
    
    break;
      
    case 'n':
    case 'N':
      
        if(estado == sair)
        {
          estado = jogo;
        }

        if(estado == reset)
        {
            estado = jogo;
        }
    
        if(estado == vitoria)
        {
          exit(0);
        }
      
      break;
      
      case 'r':
      case 'R':
      
        if(estado == jogo)
        {
          estado = reset;
        }
      
        if(estado == Derrota)
        {
            resetaJogo();
            estado = jogo;
        }
      
      break;
        
      default:
          break;
    }
}
            
void tecladoUP(unsigned char key, int x, int y)
{
  tecla[key] = 0;
}

void teclasEspeciais(int key, int x, int y)
{
  switch (key)
  {
      case GLUT_KEY_UP: //CIMA
      {
        if(estado == jogo)
      	{
      		if(nave.combustivel>0)
      		{
	      		nave.motor = 1.0;
            nave.aceleracaoY = 0.1;
            nave.aceleracaoX = 0.1;
	      		nave.velocidadeEmY += nave.aceleracaoY * cos((nave.angulo * M_PI) / 180);
            nave.velocidadeEmX += nave.aceleracaoX * sin(-(nave.angulo * M_PI) / 180);
	      		nave.combustivel--; 
      		}
      	}
      }
      break;

      case GLUT_KEY_RIGHT: //DIREITA
      {
        if(estado == jogo)
        {
          nave.angulo-=1;
        }
      }
      break;

      case GLUT_KEY_LEFT: //ESQUERDA
      {
        if(estado == jogo)
        {
        	nave.angulo+=1;
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
    glutKeyboardUpFunc(tecladoUP);
    glutSpecialFunc(teclasEspeciais);
    inicializa();

    glutTimerFunc(0, atualiza, 0);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}