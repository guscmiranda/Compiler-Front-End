#include <stdio.h>
#include <stdlib.h>

#include "error.h"


void lex_error(int linha, int coluna, const char *lexema_invalido)
{
    fprintf(stderr, "\n[ERRO LEXICO] Padrao nao reconhecido\n");
    fprintf(stderr, "Nao era esperado encontrar \"%s\" na linha %d e coluna %d\n", lexema_invalido, linha, coluna);

    exit(EXIT_FAILURE);
    
}