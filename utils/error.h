/*
Ainda não sei como vamos fazer o tratamento de erros, mas acho que é importante ter um
arquivo separado para isso, onde podemos definir as mensagens de erro e as funções para exibi-las.
*/

#ifndef LEXER_H
#define ERROR_H

void lex_error(int linha, int colun, const char *lexema_inavelido);

#endif 

