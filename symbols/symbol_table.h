// aqui seria para guardar as informações dos símbolos, como variáveis, funções, etc.

/* Preencha tabela de símbolos com identificadores e constantes
   Campos: nome do token, lexema e tipo do dado
       − O último campo só será preenchido quando aplicável (constantes)
*/

/* Tenho minhas duvidas se isso merece um arquivo separado, ou se é só uma estrutura que fica dentro do lexer mesmo,
já que o lexer é o responsável por preencher a tabela de símbolos. */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../token/token.h"
#include <string.h>

typedef struct
{
    TokenType tipo;
    char lexema[100];
    char tipo_dado[20]; // int, float, ...
} SymbolTable;

int indice_simbolo(char *lexema);
int busca_simbolo(char *lexema);
int insere_simbolo(TokenType tipo, char *lexema);

#endif