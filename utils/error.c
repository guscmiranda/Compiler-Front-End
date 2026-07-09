#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void lex_error(int linha, int coluna, const char *lexema)
{
    fprintf(stderr, "\n[ERRO LEXICO] Padrao nao reconhecido\n");
    fprintf(stderr, "Nao era esperado encontrar \"%s\" na linha %d e coluna %d\n", lexema, linha, coluna);

    exit(EXIT_FAILURE);
}

void exe_error(int linha, int coluna, const char *lexema)
{
    fprintf(stderr, "\n[ERRO DE EXECUCAO] Acao invalida.\n");
    fprintf(stderr, "O procedimento acao() foi chamado sobre estado não final");
    fprintf(stderr, " na linha %d e coluna %d ao ler o lexema %s\n", linha, coluna, lexema);
}

void syn_error(Token tk, TokenType tk_esperado)
{
    fprintf(stderr, "\n[ERRO SINTATICO]\n");
    fprintf(stderr, "Linha %d, coluna %d\n", tk.linha, tk.coluna);
    fprintf(stderr, "Esperado: %s\n", token_type_to_string(tk_esperado));
    fprintf(stderr, "Encontrado: %s \n", token_type_to_string(tk.tipo));

    exit(EXIT_FAILURE);
}

void syn_error_first(Token tk, TokenType *esperados, int n)
{
    fprintf(stderr, "\n[ERRO SINTATICO]\n");
    fprintf(stderr, "Linha %d, coluna %d\n", tk.linha, tk.coluna);

    fprintf(stderr, "Esperado: ");

    for (int i = 0; i < n; i++)
    {
        fprintf(stderr, "%s", token_type_to_string(esperados[i]));

        if (i < n - 1)
            fprintf(stderr, ", ");
    }

    fprintf(stderr, "\n");

    fprintf(stderr,
            "Encontrado: %s \n",
            token_type_to_string(tk.tipo));

    exit(EXIT_FAILURE);
}