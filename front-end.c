#include "lexer/tabela_transicao.h"
#include "symbols/tabela_simbolos.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <stdlib.h>
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
        printf("Arquivo lido com sucesso\n\n");
    }

    inicializa_lexer(arquivo);

    No *raiz = parser();

    printa_arvore(raiz, 0);
    libera_arvore(raiz);

    fclose(arquivo);

    return 0;
}