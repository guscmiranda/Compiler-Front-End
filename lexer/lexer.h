// Aqui vamos fazer a implementação do lexer, que é responsável por ler o código fonte
// e gerar os tokens.

#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include "tabela_transicao.h"
#include <stdio.h>

void inicializa_lexer(FILE *codigo_fonte);
Token get_next_token();
Token acoes(Estado s, char *lexema, int token_linha, int token_coluna);

#endif 