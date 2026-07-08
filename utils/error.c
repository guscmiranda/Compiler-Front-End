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