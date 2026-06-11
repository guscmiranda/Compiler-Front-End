// Aqui vamos fazer a implementação do lexer, que é responsável por ler o código fonte
// e gerar os tokens.

#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include "tabela_transicao.h"
#include <stdio.h>
// Token get_next_token();

void inicializa_lexer(FILE *codigo_fonte);
int get_next_token();
Token acoes(Estado s, char *lexema, int *tamanho_lexema, int token_linha, int token_coluna);
// Token acao(char *lexema, int );


#endif // LEXER_H