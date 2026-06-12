#include "symbol_table.h"
#define MAX_SYMBOLS 100

SymbolTable symbol_table[MAX_SYMBOLS]; // Tabela de símbolos
int num_simbolos = 0;                  // Número de símbolos na tabela

int indice_simbolo(char *lexema)
{
    // Verificar se o símbolo já existe na tabela
    int indice = busca_simbolo(lexema);
    if (indice == -1)
    {
        // Se não existir, insere e retorna o novo índice
        return insere_simbolo(TK_ID, lexema);
    }
    else
    {
        // Se já existir, retorna o índice existente
        return indice;
    }
}

int busca_simbolo(char *lexema)
{
    for (int i = 0; i < num_simbolos; i++)
    {
        if (strcmp(symbol_table[i].lexema, lexema) == 0)
        {
            return i;
        }
    }
    return -1; // Símbolo não encontrado
}

int insere_simbolo(TokenType tipo, char *lexema)
{
    if (num_simbolos < MAX_SYMBOLS)
    {
        symbol_table[num_simbolos].tipo = tipo;
        strcpy(symbol_table[num_simbolos].lexema, lexema);
        // Inicialmente, o tipo de dado não é especificado
        symbol_table[num_simbolos].tipo_dado[0] = '\0';
        return num_simbolos++;
    }
    return -1; // Tabela de símbolos cheia
}