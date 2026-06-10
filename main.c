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

    inicializa_tabela_transicao();
    Estado s = estado_inicial();

    while (!is_estado_final(s))
    {
        char c = fgetc(arquivo);

        ClasseEntrada classe = classifica_caractere(c);
        // s = tabela_transicao[s][classe];
        s = move(s, classe);

        if (s == ST_ERRO)
        {
            fprintf(stderr, "Erro léxico: caractere '%c' não esperado.\n", c);
            fclose(arquivo);
            return 1;
        }
    }
    // Aqui devemos chamar as acoes de acordo com o estado final alcançado.

    fclose(arquivo);

    return 0;
}