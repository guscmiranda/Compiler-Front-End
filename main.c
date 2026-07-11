#include "lexer/tabela_transicao.h"
#include "symbols/tabela_simbolos.h"
#include "lexer/lexer.h"
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

    int capacidade = 100;
    int quantidade = 0;
    Token *tokens = malloc(capacidade * sizeof(Token));

    inicializa_lexer(arquivo);
    int i = 0;
    do
    {
        if (quantidade == capacidade)
        {
            capacidade += 100;
            Token *temp = realloc(tokens, capacidade * sizeof(Token));
            if (temp == NULL)
            {
                fprintf(stderr, "Erro de realocação de memoria.\n");
                free(tokens);
                fclose(arquivo);
                return 1;
            }
            tokens = temp;
        }

        tokens[quantidade] = lex();

        quantidade++;
    } while (tokens[quantidade - 1].tipo != TK_EOF);

    for (int j = 0; j < quantidade; j++)
    {
        printf("Token: %-5d | Atributo: %-5s | Linha: %-3d | Coluna: %-3d\n", tokens[j].tipo, tokens[j].atributo, tokens[j].linha, tokens[j].coluna);
    }

    print_symbol_table();

    free(tokens);
    fclose(arquivo);

    return 0;
}