// Aqui vamos fazer a implementação do lexer, que é responsável por ler o código fonte
// e gerar os tokens.

#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include <stdio.h>
// Token get_next_token();

void inicializa_lexer(FILE *codigo_fonte);
Token get_next_token();

#endif // LEXER_H