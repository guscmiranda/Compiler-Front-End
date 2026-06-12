#include <stdio.h>
#include <string.h>

#include "../symbols/symbol_table.h"
#include "tabela_transicao.h"
#include "../utils/error.h"
#include "lexer.h"

int linha_atual;
int coluna_atual;
int coluna_anterior = 1;
FILE *arquivo = NULL;

extern Estado tabela_transicao[N_ESTADOS][NUM_CLASSES];
extern TokenType estado_final[N_ESTADOS];
extern int estado_lookahead[N_ESTADOS];

void inicializa_lexer(FILE *codigo_fonte)
{
    arquivo = codigo_fonte;
    inicializa_tabela_transicao();
    linha_atual = 1;
    coluna_atual = 1;
}

static TokenType verifica_palavra_reservada(const char *lexema)
{
    // tipo
    if (strcmp(lexema, "void") == 0)
        return TK_TIPO;
    if (strcmp(lexema, "int") == 0)
        return TK_TIPO;
    if (strcmp(lexema, "char") == 0)
        return TK_TIPO;
    if (strcmp(lexema, "float") == 0)
        return TK_TIPO;

    // estrutura
    if (strcmp(lexema, "programa") == 0)
        return TK_PROGRAMA;
    if (strcmp(lexema, "inicio") == 0)
        return TK_INICIO;
    if (strcmp(lexema, "fim") == 0)
        return TK_FIM;

    // selecao
    if (strcmp(lexema, "se") == 0)
        return TK_SE;
    if (strcmp(lexema, "entao") == 0)
        return TK_ENTAO;
    if (strcmp(lexema, "e_se") == 0)
        return TK_E_SE;
    if (strcmp(lexema, "senao") == 0)
        return TK_SENAO;

    // repeticao
    if (strcmp(lexema, "enquanto") == 0)
        return TK_ENQUANTO;
    if (strcmp(lexema, "faca") == 0)
        return TK_FACA;
    if (strcmp(lexema, "repita") == 0)
        return TK_REPITA;
    if (strcmp(lexema, "ate") == 0)
        return TK_ATE;
    if (strcmp(lexema, "para") == 0)
        return TK_PARA;
    if (strcmp(lexema, "passo") == 0)
        return TK_PASSO;

    // se passa eh id
    return TK_ID;
}

void conta_linha_e_coluna(char c)
{
    const int is_eof = (c == EOF);

    if (c == '\n')
    {
        linha_atual++;
        coluna_anterior = coluna_atual;
        coluna_atual = 1;
    }
    else if (!is_eof)
    {
        coluna_atual++;
    }
}

void trata_lookahead(Estado s, char *lexema, int *tamanho_lexema)
{

    // Se alcançou s sem lookahead não precisa tratar
    if (estado_lookahead[s] != 1)
        return;

    (*tamanho_lexema)--;
    char lookahead_char = lexema[*tamanho_lexema];

    // Devolve caractere e volta o ponteiro (conferir!)
    ungetc(lookahead_char, arquivo);

    if (lookahead_char == '\n')
    {
        linha_atual--;
        coluna_atual = coluna_anterior;
    }
    else
        coluna_atual--;
}

Token get_next_token()
{
    Estado s = estado_inicial();
    char lexema[100] = {0}; // buffer para construir o lexema
    int i = 0;

    // Para reportar erro, informar onde o token está exatamente
    int token_linha = linha_atual;
    int token_coluna = coluna_atual;

    while (!is_estado_final(s))
    {
        char c = fgetc(arquivo); // fazer get_next_char() ?
        int is_eof = (c == EOF);

        conta_linha_e_coluna(c); // Atualizar linha e coluna
        lexema[i++] = c;

        if (is_eof)
        {
            if (s == estado_inicial())
            {
                return (Token){.tipo = TK_EOF, .atributo = "\0", .linha = linha_atual, .coluna = coluna_atual + 1};
            }
            else
            {
                c = ' ';
            }
        }

        ClasseEntrada classe = classifica_caractere(c);
        s = move(s, classe);
    }

    Token token_atual = acoes(s, lexema, token_linha, token_coluna);

    if (token_atual.tipo == TK_SEPARADOR || token_atual.tipo == TK_COMENTARIO)
    {
        token_atual = get_next_token();
    }

    return token_atual;
}

Token acoes(Estado s, char *lexema, int token_linha, int token_coluna)
{

    Token token;
    int tamanho_lexema = strlen(lexema);

    if (!is_estado_final(s))
    {
        lexema[tamanho_lexema] = '\0';
        exe_error(linha_atual, coluna_atual, lexema); // Criar outra função paar esse erro
    }

    if (s == ST_ERRO)
    {
        lexema[tamanho_lexema] = '\0';
        lex_error(linha_atual, coluna_atual, lexema);
    }

    trata_lookahead(s, lexema, &tamanho_lexema);
    lexema[tamanho_lexema] = '\0';

    TokenType tipo = estado_final[s];

    if (tipo == TK_ID)
    {
        tipo = verifica_palavra_reservada(lexema);

        if (tipo == TK_ID)
        {
            int idx = indice_simbolo(TK_ID, lexema, "\0");
            sprintf(token.atributo, "%d", idx);
        }
        else
        {
            strcpy(token.atributo, "\0");
        }
    }
    else if (tipo == TK_RELOP)
    { // Para relop, o atributo é o próprio lexema (==, !=, <, >, <=, >=)
        strcpy(token.atributo, lexema);
    }
    else if (tipo == TK_NUM)
    { // Adicionar NUM com o tipo na tabela de simbolos
        char tipo_dado[20] = "";

        if (s == ST_T)
            strcpy(tipo_dado, "int");
        else if (s == ST_AC)
            strcpy(tipo_dado, "float");

        int idx = indice_simbolo(TK_NUM, lexema, tipo_dado);
        sprintf(token.atributo, "%d", idx);
    }
    else if (tipo == TK_CHAR_CONTEUDO)
    {
        int idx = indice_simbolo(TK_CHAR_CONTEUDO, lexema, "char");
        sprintf(token.atributo, "%d", idx);
    }
    else
    {
        strcpy(token.atributo, "\0");
    }

    token.tipo = tipo;
    token.linha = token_linha;
    token.coluna = token_coluna;

    return token;
}
