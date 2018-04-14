#ifndef CONFIG_H
#define CONFIG_H


    #define LARGURA_DO_MUNDO 1200
    #define ALTURA_DO_MUNDO 1200

    #define LARGURA 50
    #define ALTURA 50

    //VARIAVEIS DE ESTADO
    int estado;
    #define jogo 1
    #define pause 2
    #define inicio 3
    #define sair 4
    #define Derrota 5
    #define reset 6
    #define vitoria 7
    #define menu 8
    #define controles 9
    #define creditos 10
    int xAleatorioBasePouso; //Posição aleatoria da base de pouso
    //VARIAVEIS DE ESTADO


    //ESTRUTURA DA NAVE
    typedef struct navinha
    {
        float velocidadeEmY;
        float velocidadeEmX;
        float posicaoX;
        float posicaoY;
        float gravidade;
        float aceleracaoX;
        float aceleracaoY;
        float angulo;
        double motor;
        int combustivel;
    } navinha;
    //ESTRUTURA DA NAVE

    typedef struct Mouse
    {
      float x;
      float y;
    } Mouse;

#endif
