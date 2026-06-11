#include "lexer/lexer.h"
#include "lexer/tabela_transicao.h"
#include <stdio.h>

int main()
{
    FILE *arquivo = fopen("testes/teste01.txt", "r");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }
    else
    {
        printf("Arquivo lido com sucesso\n");
    }

    // inicializa_tabela_transicao();
    inicializa_lexer(arquivo);
    int i = 0;
    while(i < 20){
        get_next_token();
        i++;
    }

    // se for ID, tem que verificar se o lexema pertence à tabela de palvras reservadas

    fclose(arquivo);

    return 0;
}