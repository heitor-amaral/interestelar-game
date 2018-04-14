#include "pontuacao.h"
#include <stdio.h>
#include <stdlib.h>


void carregaPontuacao(int *melhoresPontucoes)
{

    FILE *filePontuacao = fopen("./pontuacao.txt", "r");

    if(filePontuacao == NULL)
    {
        printf("Erro na abertura do arquivo!");
        exit(0);
    }

    int i;

    for(i=0; i<10; i++)
    {
        fscanf(filePontuacao, "%d\n", melhoresPontucoes[i]);
    }

    fclose(filePontuacao);

}

void salvaPontuacao(int pontuacao)
{

    FILE *filePontuacao = fopen("./pontuacao.txt", "w");
    if(filePontuacao == NULL)
    {
        printf("Erro na abertura do arquivo!");
        exit(0);
    }

    fprintf(filePontuacao, "%d", pontuacao);

    fclose(filePontuacao);
}