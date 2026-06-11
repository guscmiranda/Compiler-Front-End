#include "lexer.h"
#include "tabela_transicao.h"
#include <stdio.h>
#include <string.h>

int linha_atual = 1;
int coluna_atual = 1;
FILE *arquivo = NULL;

void inicializa_lexer(FILE *codigo_fonte) {
    arquivo = codigo_fonte;
    inicializa_tabela_transicao();
    linha_atual = 1;
    coluna_atual = 1;
}

//falta get next token no lexer.c, tem que ler o arquivo e usar a tabela de transicao pra gerar os tokens e usar a funcao verifica_palavra_reservada pra diferenciar id de palavra reservada

static TokenType verifica_palavra_reservada(const char* lexema) {
    //tipo
    if (strcmp(lexema, "void") == 0) return TK_TIPO;
    if (strcmp(lexema, "int") == 0) return TK_TIPO;
    if (strcmp(lexema, "char") == 0) return TK_TIPO;
    if (strcmp(lexema, "float") == 0) return TK_TIPO;
    
    //estrutura
    if (strcmp(lexema, "programa") == 0) return TK_PROGRAMA;
    if (strcmp(lexema, "inicio") == 0) return TK_INICIO;
    if (strcmp(lexema, "fim") == 0) return TK_FIM;

    //selecao
    if (strcmp(lexema, "se") == 0) return TK_SE;
    if (strcmp(lexema, "entao") == 0) return TK_ENTAO;
    if (strcmp(lexema, "e_se") == 0) return TK_E_SE;
    if (strcmp(lexema, "senao") == 0) return TK_SENAO;

    //repeticao
    if (strcmp(lexema, "enquanto") == 0) return TK_ENQUANTO;
    if (strcmp(lexema, "faca") == 0) return TK_FACA;
    if (strcmp(lexema, "repita") == 0) return TK_REPITA;
    if (strcmp(lexema, "ate") == 0) return TK_ATE;
    if (strcmp(lexema, "para") == 0) return TK_PARA;
    if (strcmp(lexema, "passo") == 0) return TK_PASSO;

    //se passa eh id
    return TK_ID;
}