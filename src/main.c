
//LINK DO ENUNCIADO: https://github.com/fegemo/cefet-cg/blob/master/assignments/tp1-lander/README.md#trabalho-pr%C3%A1tico-1---lander
//CEU TEMPORARIO https://extraterrestresmyblog.wordpress.com/ceu-noite-jpg/

//COISAS A FAZER:
//1.  Derrota quando pousar inclinado
//2.  Tirar numeros magicos
//3.  VITORIA/DERROTA NO ONE SWITCH
//4. COMENTAR O CODIGO

//EM ANDAMENTO:
//1.  Arrumar razão aspecto de escrita na tela

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
//13. foguinho sai da turbina quando o motor principal é ligado
//14. Menu
//15. HUD
//16. Pontuação salva em arquivo

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
#include <pontuacao.h>

//COLOCAR NO LUGAR CERTO
float transparencia = 1; // inicio
float acrescimo = 0.01; //inicio
float spritesheet = 0.2; // menu
float min = 0;
int estadoMenu = 10;
// 10 = jogar
/// 11 = score
// 12 = controles
//13 creditos

// 14 = sair

navinha nave;
Mouse posicaoMouse;

unsigned int tecla[256];
unsigned int teclaEspec[256];

int melhoresPontuacoes[5];

float controleAngulo = -22.5;
int controleMenu = 0;
int oneSwitch = 1;
float ang = 0.25;

float spriteReiniciar = 0.5;
float minReiniciar = 0;
int controleReiniciar = 0;
int estadoReiniciar = 0;
// 0 = reiniciar
// 1 = voltar ao menu

void resetaJogo() //Usa o preset da atualiza
{
  if(oneSwitch == 0)
  {
    estado = jogo;
    xAleatorioBasePouso = rand()%1000;
    nave.posicaoX = 200;
    nave.posicaoY = 1000;
    nave.gravidade = -0.01;
    nave.velocidadeEmY = 0;
    nave.velocidadeEmX = 2;
    nave.aceleracaoX = 0;
    nave.aceleracaoY = 0;
    nave.angulo = 0;
    nave.motor = 0;
    nave.combustivel = 1000;
  }

  if(oneSwitch == 1)
  {
    estado = jogo;
    xAleatorioBasePouso = rand()%1000;
    nave.posicaoX = 200;
    nave.posicaoY = 1000;
    nave.gravidade = -0.005;
    nave.velocidadeEmY = 0;
    nave.velocidadeEmX = 0.1;
    nave.aceleracaoX = 0;
    nave.aceleracaoY = 0;
    nave.angulo = 0;
    nave.motor = 0;
    nave.combustivel = 1000;
  }
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

void quadradoDoTamanhoDaTelaComOpacidade()
{
    glColor4f(1, 1, 1, transparencia);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);	glVertex2f(0,0);
        glTexCoord2f(1, 0);	glVertex2f(LARGURA_DO_MUNDO, 0);
        glTexCoord2f(1, 1);	glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
        glTexCoord2f(0, 1);	glVertex2f(0, ALTURA_DO_MUNDO);

    glEnd();
}

void desenhaInicio()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaInicio);

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);

    // Habilita o uso de texturas
      glEnable(GL_TEXTURE_2D);

      // Começa a usar a textura que criamos
      glBindTexture(GL_TEXTURE_2D, texturaPressSpacebarToContinue);

      glColor4f(1, 1, 1, 0);

      quadradoDoTamanhoDaTelaComOpacidade();

      glDisable(GL_TEXTURE_2D);
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

    if(oneSwitch == 0)
    {
	    	// Começa a usar a textura que criamos
	    glBindTexture(GL_TEXTURE_2D, texturaDerrota);

	    quadradoDoTamanhoDaTela();

	    glDisable(GL_TEXTURE_2D);
    }

    if(oneSwitch == 1)
    {
    	// Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaDerrotaOneSwitch);

    quadradoDoTamanhoDaTela();

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, SpriteDerrota);

    glColor3f(1, 1, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, minReiniciar);	glVertex2f(0,0);
        glTexCoord2f(1, minReiniciar);	glVertex2f(LARGURA_DO_MUNDO, 0);
        glTexCoord2f(1, spriteReiniciar);	glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
        glTexCoord2f(0, spriteReiniciar);	glVertex2f(0, ALTURA_DO_MUNDO);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    
    }    
}

void desenhaPreJogo() //IMPORTANTE
{
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);    

    
    	// Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaPreJogo);

    quadradoDoTamanhoDaTela();

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, SpritePreJogo);

    glColor3f(1, 1, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, minReiniciar);	glVertex2f(0,0);
        glTexCoord2f(1, minReiniciar);	glVertex2f(LARGURA_DO_MUNDO, 0);
        glTexCoord2f(1, spriteReiniciar);	glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
        glTexCoord2f(0, spriteReiniciar);	glVertex2f(0, ALTURA_DO_MUNDO);

    glEnd();

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
    if(oneSwitch == 0)
    {
    	glBindTexture(GL_TEXTURE_2D, texturaVitoria);

    	quadradoDoTamanhoDaTela();

    	glDisable(GL_TEXTURE_2D);	
    }    

    //ONE SWITCH

    if(oneSwitch == 1) //ARRUMAR AQUIII
    {
    	glBindTexture(GL_TEXTURE_2D, texturaVitoriaOneSwitch);

        quadradoDoTamanhoDaTela();

        // Começa a usar a textura que criamos
        glBindTexture(GL_TEXTURE_2D, SpriteVitoria);

        glColor3f(1, 1, 1);

        // Começa a desenhar um polígono com os vértices especificados
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, minReiniciar);  glVertex2f(0,0);
            glTexCoord2f(1, minReiniciar);  glVertex2f(LARGURA_DO_MUNDO, 0);
            glTexCoord2f(1, spriteReiniciar);   glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
            glTexCoord2f(0, spriteReiniciar);   glVertex2f(0, ALTURA_DO_MUNDO);

        glEnd();

        glDisable(GL_TEXTURE_2D);

    }



    //EXIBE PONTUAÇAO
    glColor4f(0,0,0,0.8);

    glBegin(GL_TRIANGLE_FAN);

      glVertex2f((LARGURA_DO_MUNDO/2)-180, (ALTURA_DO_MUNDO/2)-90);
      glVertex2f((LARGURA_DO_MUNDO/2)+170, (ALTURA_DO_MUNDO/2)-90);
      glVertex2f((LARGURA_DO_MUNDO/2)+170, (ALTURA_DO_MUNDO/2)+50);
      glVertex2f((LARGURA_DO_MUNDO/2)-180, (ALTURA_DO_MUNDO/2)+50);

    glEnd();

    glColor3f(1,0.1,0.1);
    //rgb(179, 57, 57)

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "PONTUACAO", (LARGURA_DO_MUNDO/2)-100, ALTURA_DO_MUNDO/2); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, nave.combustivel, (LARGURA_DO_MUNDO/2)-40, (ALTURA_DO_MUNDO/2)-70);

    glEnd();

    glColor4f(0,0,0,0.8);

    glBegin(GL_TRIANGLE_FAN);

      glVertex2f((LARGURA_DO_MUNDO/2)-350, (ALTURA_DO_MUNDO/2)-375);
      glVertex2f((LARGURA_DO_MUNDO/2)+350, (ALTURA_DO_MUNDO/2)-375);
      glVertex2f((LARGURA_DO_MUNDO/2)+350, (ALTURA_DO_MUNDO/2)-150);
      glVertex2f((LARGURA_DO_MUNDO/2)-350, (ALTURA_DO_MUNDO/2)-150);

    glEnd();

    glColor3f(1,0.1,0.1);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "1 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-190); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[0], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-190);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "2 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-240); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[1], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-240);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "3 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-290); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[2], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-290);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "4 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-340); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[3], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-340);
}

void desenhaScore()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos

    if(oneSwitch == 0)
    {
        glBindTexture(GL_TEXTURE_2D, texturaScore);
    }

    else glBindTexture(GL_TEXTURE_2D, texturaScoreOneSwitch);


    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);

    glColor4f(0,0,0,0.8);

    glBegin(GL_TRIANGLE_FAN);

      glVertex2f((LARGURA_DO_MUNDO/2)-350, (ALTURA_DO_MUNDO/2)-375);
      glVertex2f((LARGURA_DO_MUNDO/2)+350, (ALTURA_DO_MUNDO/2)-375);
      glVertex2f((LARGURA_DO_MUNDO/2)+350, (ALTURA_DO_MUNDO/2)-150);
      glVertex2f((LARGURA_DO_MUNDO/2)-350, (ALTURA_DO_MUNDO/2)-150);

    glEnd();

    glColor3f(1,0.1,0.1);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "1 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-190); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[0], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-190);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "2 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-240); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[1], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-240);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "3 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-290); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[2], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-290);

    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "4 -", (LARGURA_DO_MUNDO/2)-310, (ALTURA_DO_MUNDO/2)-340); // velocidade em Y
    escreveNumero(GLUT_BITMAP_TIMES_ROMAN_24, melhoresPontuacoes[3], (LARGURA_DO_MUNDO/2)-250, (ALTURA_DO_MUNDO/2)-340);

}

void desenhaFundoJogo()
{
  // Habilita o uso de texturas
  glEnable(GL_TEXTURE_2D);

  // Começa a usar a textura que criamos
  glBindTexture(GL_TEXTURE_2D, texturaFundoJogo01);

  quadradoDoTamanhoDaTela();

  glDisable(GL_TEXTURE_2D);

  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaFundoJogo02);

    glColor4f(1, 1, 1, 0);

    quadradoDoTamanhoDaTelaComOpacidade();

    glDisable(GL_TEXTURE_2D);
}

void desenhaBasePouso()
{
  int altura = 100;
  int largura = 100;


	glColor3f(1, 1, 1);

  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaBasePouso);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);  glVertex2f(xAleatorioBasePouso, 20);
        glTexCoord2f(1,0);  glVertex2f(xAleatorioBasePouso + largura, 20);
        glTexCoord2f(1,1);  glVertex2f(xAleatorioBasePouso + largura, altura);
        glTexCoord2f(0,1);  glVertex2f(xAleatorioBasePouso, altura);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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
        glTexCoord2f((0.5*nave.motor), 0);	glVertex2f(-LARGURA/2, -ALTURA/2);
        glTexCoord2f((0.5+(0.5*nave.motor)), 0);	glVertex2f(LARGURA/2, -ALTURA/2);
        glTexCoord2f((0.5+(0.5*nave.motor)), 1);	glVertex2f(LARGURA/2, ALTURA/2);
        glTexCoord2f((0.5*nave.motor), 1);	glVertex2f(-LARGURA/2, ALTURA/2);

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

void desenhaMenu()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    if(oneSwitch == 0)
    {
    	glBindTexture(GL_TEXTURE_2D, menu_sem_escrita);
    }

    else glBindTexture(GL_TEXTURE_2D, texturaMenuOneSwitch);
    

    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);

    //SPRITESHEET

    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, SpriteSheet_Menu);

    glColor3f(1, 1, 1);

    // Começa a desenhar um polígono com os vértices especificados
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, min);	glVertex2f(0,0);
        glTexCoord2f(1, min);	glVertex2f(LARGURA_DO_MUNDO, 0);
        glTexCoord2f(1, spritesheet);	glVertex2f(LARGURA_DO_MUNDO, ALTURA_DO_MUNDO);
        glTexCoord2f(0, spritesheet);	glVertex2f(0, ALTURA_DO_MUNDO);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void desenhaControles()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    if(oneSwitch == 0)
    {
        glBindTexture(GL_TEXTURE_2D, texturaControles);
    }

    else glBindTexture(GL_TEXTURE_2D, texturaControlesOneSwitch);


    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaCreditos()
{
  // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    if(oneSwitch == 0)
    {
        glBindTexture(GL_TEXTURE_2D, texturaCreditos);
    }

    else glBindTexture(GL_TEXTURE_2D, texturaCreditosOneSwitch);


    quadradoDoTamanhoDaTela();

    glDisable(GL_TEXTURE_2D);
}

void desenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    // Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar

    if(estado == pre)
    {
    	desenhaPreJogo();
    }

     if(estado == inicio)
    {
    	desenhaInicio();
    }

    else if(estado == menu)
    {
      desenhaMenu();
    }

    else if(estado == jogo)
    {
      desenhaFundoJogo();
    	desenhaHUD();
    	DesenhaChao();
      desenhaBasePouso();
      desenhaNave();
    }

    else if(estado == pause) //NAO TEM NO ONE SWITCH
    {
    	desenhaPause();
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

    else if(estado == Score)
    {
      desenhaScore();
    }

    else if(estado == controles)
    {
          desenhaControles();
    }

    else if(estado == creditos)
    {
          desenhaCreditos();
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

        melhoresPontuacoes[4] = nave.combustivel;

        salvaPontuacao(melhoresPontuacoes);
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
	if(estado == pre) //DECIDE SE ONE SWITCH OU NAO
	{
		controleReiniciar++;

    	if(controleReiniciar == 239)
      	{
        	controleReiniciar = 0;
      	}

      	if(controleReiniciar%80 == 0)
      	{      		
      		spriteReiniciar += 0.5;
      		minReiniciar += 0.5;
      		estadoReiniciar++;

      		if(spriteReiniciar > 1)
      		{
      			spriteReiniciar = 0.5;
      			minReiniciar = 0;
      			estadoReiniciar = 0;
      		}
      	}

	}

  if(oneSwitch == 1)
  {
    if(estado == menu)
    {
      controleMenu++;

      if(controleMenu == 479)
      {
        controleMenu = 0;
      }

      if(controleMenu%80==0)
      {
        spritesheet += 0.2; //CONTINUAR AQUI
        min += 0.2;
        estadoMenu ++;

        if(spritesheet > 1)
        {
          spritesheet = 0.2;
          min = 0;
          estadoMenu = 10;
        }
      }
    }

    if(estado == Derrota || estado == vitoria)
    {
    	controleReiniciar++;

    	if(controleReiniciar == 239)
      	{
        	controleReiniciar = 0;
      	}

      	if(controleReiniciar%80 == 0)
      	{      		
      		spriteReiniciar += 0.5;
      		minReiniciar += 0.5;
      		estadoReiniciar++;

      		if(spriteReiniciar > 1)
      		{
      			spriteReiniciar = 0.5;
      			minReiniciar = 0;
      			estadoReiniciar = 0;
      		}
      	}
    }
  }

  if(estado == inicio || estado == jogo)
  {
      transparencia -= acrescimo;

      if(transparencia <= 0)
      {
        acrescimo = -0.01;
      }

      if(transparencia > 1)
      {
        acrescimo = 0.01;
      }
  }

  if(oneSwitch == 1)
  {
    if(estado == jogo)
    {
      controleAngulo += ang;

      if(controleAngulo == 22.5 ||controleAngulo == -22.5)
      {
        ang = ang*(-1);
      }

      nave.angulo = controleAngulo;
    }
  }

    if(estado == jogo)
    {  
        if(oneSwitch == 0)
        {
	        if(tecla['w']==0 && tecla['W']==0)
	        {
	          nave.motor = 0;
	          nave.aceleracaoY = 0;
	          nave.aceleracaoX = 0;
	          nave.posicaoY += nave.velocidadeEmY;
	          nave.posicaoX += nave.velocidadeEmX;
	        }

	        if(tecla['a']==1 || tecla['A']==1)
          	nave.angulo+=1;

	        if(tecla['d']==1 || tecla['D']==1)
	          nave.angulo-=1;

	        if(tecla['w']==1 || tecla['W']==1)
	        {
	            if(nave.combustivel > 0)
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
	            else
	            {
	              nave.posicaoY += nave.velocidadeEmY;
	              nave.posicaoX += nave.velocidadeEmX;
	            }
        	}


        }

        if(oneSwitch == 1)
        {
        	if(tecla[32] == 1)
	        {
	            if(nave.combustivel > 0)
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
	            else
	            {
	              nave.posicaoY += nave.velocidadeEmY;
	              nave.posicaoX += nave.velocidadeEmX;
	            }
        	}

        	if(tecla[32]==0)
        	{
        		nave.motor = 0;
          		nave.aceleracaoY = 0;
          		nave.aceleracaoX = 0;
          		nave.posicaoY += nave.velocidadeEmY;
          		nave.posicaoX += nave.velocidadeEmX;
        	}
        }

        nave.velocidadeEmY += nave.gravidade;

        basePouso();
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
void inicializa(void) // OTIMIZAR 
{
	carregaTextura();

  srand(time(NULL));

  xAleatorioBasePouso = rand()%1000;

      // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
  	estado = pre;
    nave.posicaoX = 200;
    nave.posicaoY = 1000;
    nave.gravidade = -0.01;
    nave.velocidadeEmY = 0;
    nave.velocidadeEmX = 2;
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
        estado = menu;
      }

      if(estado == jogo)
      {
        estado = sair;
      }

      if(estado == controles)
      {
        estado = menu;
      }

      if(estado == creditos)
      {
        estado = menu;
      }

      if(estado == Score)
      {
        estado = menu;
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
    {
        if(estado == menu)
        {
          if(estadoMenu == 10)
          {
            resetaJogo();
            estado = jogo;
          }

          if(estadoMenu == 11)
          {
            estado = Score;
          }

          if(estadoMenu == 12)
          {
            estado = controles;
          }

          if(estadoMenu == 13)
          {
              estado = creditos;
          }

          if(estadoMenu == 14)
          {
            exit(0);
          }
        }
    }

      break;

      case 32: //ESPAÇO
      {
      	if(estado == pre)
      	{
      		if(estadoReiniciar == 0)
             	{             		
                  	oneSwitch = 1;
             	}

             	if(estadoReiniciar == 1)
             	{
             		oneSwitch = 0;
             	}

            estado = menu;
            break;

      	}
        if(estado == inicio)
        {
            estado = menu;
            break;
        }

        if(oneSwitch == 1)
        {
            if(estado == menu)
            {
               if(estadoMenu == 10)
               {
                  resetaJogo();
                  estado = jogo;
               }

               if(estadoMenu == 11)
               {
                 estado = Score;
                 break;
               }

               if(estadoMenu == 12)
               {
                  estado = controles;
                  break;
               }

               if(estadoMenu == 13)
               {
                    estado = creditos;
                    break;
               }

               if(estadoMenu == 14)
               {
                  exit(0);
               }
             }

             if(estado == Derrota || estado == vitoria)
             {             	
             	if(estadoReiniciar == 0)
             	{
             		resetaJogo();
                  	estado = jogo;
             	}

             	if(estadoReiniciar == 1)
             	{
             		estado = menu;
             	}
             }

             if(estado == creditos)
             {

               estado = menu;
             }

             if(estado == Score)
             {
               estado = menu;
             }

             if(estado == controles)
             {
               estado = menu;
             }
        }
      }
      break;

    case 's':
    case 'S':

      if(estado == sair)
      {
        estado = menu;
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
          estado = menu;
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
        if(estado == menu)
        {
            spritesheet -= 0.2; //CONTINUAR AQUI
            min -= 0.2;
            estadoMenu --;

            if(spritesheet < 0.2)
            {
              spritesheet = 1;
              min = 0.8;
              estadoMenu = 14;
            }
        }

      }
      break;

      case GLUT_KEY_DOWN: //abaixo
      {
        if(estado == menu)
        {
            spritesheet += 0.2; //CONTINUAR AQUI
            min += 0.2;
            estadoMenu ++;

            if(spritesheet > 1)
            {
              spritesheet = 0.2;
              min = 0;
              estadoMenu = 10;

            }
        }

      }
      break;

      default:
        break;
  }
}

void movimentoMouse(int x, int y)
{
    posicaoMouse.x = x;
    posicaoMouse.y = y;

    if(estado == menu)
    {
        if(posicaoMouse.x > 722 && posicaoMouse.x < 969) //SPRITESHEET MENU
        {
            if(posicaoMouse.y > 889 && posicaoMouse.y < 939) //Sair
            {
              spritesheet = 1;
              min = 0.8;
              estadoMenu = 14;
            }

            if(posicaoMouse.y > 830 && posicaoMouse.y < 880) //creditos
            {
              spritesheet = 0.8;
              min = 0.6;
              estadoMenu = 13;
            }

            if(posicaoMouse.y > 771 && posicaoMouse.y < 823) //controles
            {
              spritesheet = 0.6;
              min = 0.4;
              estadoMenu = 12;
            }

            if(posicaoMouse.y > 715 && posicaoMouse.y < 763) //score
            {
              spritesheet = 0.4;
              min = 0.2;
              estadoMenu = 11;
            }

            if(posicaoMouse.y > 653 && posicaoMouse.y < 705) //jogar
            {
              spritesheet = 0.2;
              min = 0;
              estadoMenu = 10;
            }
        }
    }
}

void ClicMouse(int button, int state, int x, int y)
{
  posicaoMouse.x = x;
  posicaoMouse.y = y;

  if(estado == menu)
  {
    if (button == GLUT_LEFT_BUTTON)
      {
          if (state == GLUT_DOWN) //OBS: TIRAR NUMEROS MAGICOS
          {
              if(posicaoMouse.x > 722 && posicaoMouse.x < 969) //SPRITESHEET MENU
              {
                  if(posicaoMouse.y > 889 && posicaoMouse.y < 939) //Sair nas coordenadas do mouse
                  {
                      exit(0);
                  }

                  if(posicaoMouse.y > 830 && posicaoMouse.y < 880) //creditos nas coordenadas do mouse
                  {
                    estado = creditos;
                  }

                  if(posicaoMouse.y > 771 && posicaoMouse.y < 823) //controles nas coordenadas do mouse
                  {
                    estado = controles;
                  }

                  if(posicaoMouse.y > 715 && posicaoMouse.y < 763) //USAR QUANDO SCORE FUNCIONAR nas coordenadas do mouse
                  {
                    estado = Score;
                  }

                  if(posicaoMouse.y > 653 && posicaoMouse.y < 705) //jogar nas coordenadas do mouse
                  {
                    estado = jogo;
                  }
              }
        }
    }
 }
}

int main(int argc, char **argv)
{
    carregaPontuacao(melhoresPontuacoes);

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
    glutCreateWindow("Interestelar v1.0");

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoUP);
    glutSpecialFunc(teclasEspeciais);
    glutMouseFunc(ClicMouse);
    glutPassiveMotionFunc(movimentoMouse);

    inicializa();

    glutTimerFunc(0, atualiza, 0);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
