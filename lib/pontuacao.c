#include "pontuacao.h"
#include <stdio.h>
#include <stdlib.h>

void carregaPontuacao(int *score)
{

    FILE *filePontuacao;
    filePontuacao = fopen("pontuacoes.txt", "r");

    if(filePontuacao == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
    }
    else
    {
        printf("Arquivo aberto com sucesso!\n");
    }

    fscanf(filePontuacao, "%i %i %i %i %i", score, score+1, score+2, score+3, score+4);

    fclose(filePontuacao);
}


void salvaPontuacao(int *score)
{
    int i, j, aux;
    //Ordenação do maior pro menor
    for(i=0; i<5; i++)
    {
        for(j=i+1; j<5; j++)
        {
            if(*(score+i) < *(score+j))
            {
                aux = *(score+i);
                *(score+i) = *(score+j);
                *(score+j) = aux;
            }
        }
    }
    //Ordenação do maior pro menor


    FILE *filePontuacao = fopen("pontuacoes.txt", "w");
    
    if(filePontuacao == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(0);
    }


    for(i=0; i<5; i++)
        fprintf(filePontuacao, "%d ", *(score+i));

    fclose(filePontuacao);
}