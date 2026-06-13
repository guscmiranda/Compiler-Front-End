#include "tabela_simbolos.h"
#include <stdio.h>

SymbolTable symbol_table[MAX_SYMBOLS]; // Tabela de símbolos
int num_simbolos = 0;                  // Número de símbolos na tabela

int indice_simbolo(TokenType tipo, char *lexema, char *tipo_dado) // temos que inserir o tipo em NUM e ChAR_CONTEUDO
{
    // Verificar se o símbolo já existe na tabela
    int indice = busca_simbolo(lexema);
    if (indice == -1)
    {
        // Se não existir, insere e retorna o novo índice
        return insere_simbolo(tipo, lexema, tipo_dado);
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

int insere_simbolo(TokenType tipo, char *lexema, char *tipo_dado)
{
    if (num_simbolos < MAX_SYMBOLS)
    {
        symbol_table[num_simbolos].tipo_token = tipo;
        strcpy(symbol_table[num_simbolos].lexema, lexema);
        strcpy(symbol_table[num_simbolos].tipo_dado, tipo_dado);

        // Inicialmente, o tipo de dado não é especificado
        // symbol_table[num_simbolos].tipo_dado[0] = '\0';
        return num_simbolos++;
    }
    return -1; // Tabela de símbolos cheia
}

void print_symbol_table()
{
    printf("\n== TABELA DE SIMBOLOS ==\n");
    for (int i = 0; i < num_simbolos; i++)
    {
        printf("Pos: %-2d | Token: %-2d | Tipo de dado: %-5s |Lexema: %s\n", i, symbol_table[i].tipo_token, symbol_table[i].tipo_dado, symbol_table[i].lexema);
    }
}
