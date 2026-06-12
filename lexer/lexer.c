#include <stdio.h>
#include <string.h>

#include "../symbols/symbol_table.h"
#include "tabela_transicao.h"
#include "../utils/error.h"
#include "lexer.h"

int linha_atual = 1;
int coluna_atual = 1;
int coluna_anterior = 1;
FILE *arquivo = NULL;

extern Estado tabela_transicao[N_ESTADOS][NUM_CLASSES];
extern TokenType estado_final[N_ESTADOS];
extern int estado_lookahead[N_ESTADOS];

void inicializa_lexer(FILE *codigo_fonte)
{
    arquivo = codigo_fonte;
    inicializa_tabela_transicao();
}

// falta get next token no lexer.c, tem que ler o arquivo e usar a tabela de transicao pra gerar os
// tokens e usar a funcao verifica_palavra_reservada pra diferenciar id de palavra reservada

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
        // if (!is_eof && c != '\r')
        lexema[i++] = c;

        if (is_eof /*&& s == estado_inicial()*/)
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
        // se o eof é lookahead temos q tratar num else ??

        ClasseEntrada classe = classifica_caractere(c);
        s = move(s, classe);
    }

    // return acoes(s, lexema, token_linha, token_coluna);
    Token token_atual = acoes(s, lexema, token_linha, token_coluna);

    if (token_atual.tipo == TK_SEPARADOR || token_atual.tipo == TK_COMENTARIO)
    {
        // repetir, talvez devesemos colocar tudo dentro de outro while
        // aí colocava um continue;
    }

    return token_atual;
}

// Considera que EOF é tratado no while
// Acho que não trata RELOP de acordo...
Token acoes(Estado s, char *lexema, int token_linha, int token_coluna)
{

    Token token;

    int tamanho_lexema = strlen(lexema);

    if (s == ST_ERRO)
    { // Conferir
        lexema[tamanho_lexema] = '\0';
        // chama função de erro
        token.tipo = TK_NULO;
        token.linha = token_linha;
        token.coluna = token_coluna;
        return token;
    }

    trata_lookahead(s, lexema, &tamanho_lexema);
    lexema[tamanho_lexema] = '\0';

    TokenType tipo = estado_final[s];

    if (tipo == TK_ID)
    {
        tipo = verifica_palavra_reservada(lexema);
        if (tipo == TK_ID)
        { // se for id, tem que verificar se o lexema pertence à tabela de símbolos
            token.atributo[0] = 48 + indice_simbolo(lexema);
            token.atributo[1] = '\0';
        }
    }
    else if (tipo == TK_RELOP)
    {
        // Para relop, o atributo é o próprio lexema (==, !=, <, >, <=, >=)
        strcpy(token.atributo, lexema);
    }
    else
    {
        // Para outros tokens, o atributo é o próprio lexema (ex: número, char)
        strcpy(token.atributo, "\0");
    }

    // strcpy(token.atributo, lexema);

    token.tipo = tipo;
    token.linha = token_linha;
    token.coluna = token_coluna;

    return token;
}
