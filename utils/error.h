/*
Ainda não sei como vamos fazer o tratamento de erros, mas acho que é importante ter um
arquivo separado para isso, onde podemos definir as mensagens de erro e as funções para exibi-las.
*/

#ifndef ERROR_H
#define ERROR_H

void lex_error(int linha, int colun, const char *lexema);
void exe_error(int linha, int coluna, const char *lexema);

// TODO: Implementar função para tratar erros de sintaxe
void syn_error(int linha, int coluna, const char *lexema);
#endif
