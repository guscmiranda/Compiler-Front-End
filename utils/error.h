/*
Ainda não sei como vamos fazer o tratamento de erros, mas acho que é importante ter um
arquivo separado para isso, onde podemos definir as mensagens de erro e as funções para exibi-las.
*/

#ifndef ERROR_H
#define ERROR_H

#include "../token/token.h"

void lex_error(int linha, int coluna, const char *lexema);
void exe_error(int linha, int coluna, const char *lexema);
void syn_error(Token tk, TokenType tk_esperado);
void syn_error_first(Token tk, TokenType *esperados, int n);

#endif
