#include "lexer/tabela_transicao.h"
#include "symbols/tabela_simbolos.h"
#include "lexer/lexer.h"
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

    Token tokens[500]; // Array para armazenar os tokens gerados

    inicializa_lexer(arquivo);
    int i = 0;
    do
    {
        tokens[i] = get_next_token();
        if (tokens[i].tipo == TK_NULO)
        {
            printf("Token de erro encontrado em linha %d, coluna %d.\n", tokens[i].linha, tokens[i].coluna);
            break;
        }
        else
        {
            // printf("leu com i = %d", i);
            // printf("Token: %-5d| Atributo: %-5s| Linha: %-3d| Coluna: %-3d\n", tokens[i].tipo, tokens[i].atributo, tokens[i].linha, tokens[i].coluna);
        }
        i++;
    } while (tokens[i - 1].tipo != TK_EOF);

    for (int j = 0; j < i; j++)
    {
        printf("Token: %-5d | Atributo: %-5s | Linha: %-3d | Coluna: %-3d\n", tokens[j].tipo, tokens[j].atributo, tokens[j].linha, tokens[j].coluna);
    }

    print_symbol_table();

    fclose(arquivo);

    return 0;
}