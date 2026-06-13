#include "tabela_transicao.h"
#include <stdio.h>

Estado tabela_transicao[NUM_ESTADOS][NUM_CLASSES];
TokenType estado_final[NUM_ESTADOS];
int estado_lookahead[NUM_ESTADOS] = {0};

int is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int isSeparador(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

void inicializa_tabela()
{
    Estado tabela[42][20] = {
        {ST_B, ST_B, ST_C, ST_D, ST_E, ST_F, ST_G, ST_q0, ST_I, ST_J, ST_K, ST_q1, ST_M, ST_q2, ST_O, ST_P, ST_ERRO, ST_B, ST_AI, ST_ERRO},
        {ST_B, ST_B, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_B, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_Q, ST_B, ST_Q, ST_Q},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_R, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H, ST_H},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_ERRO, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ, ST_AJ},
        {ST_T, ST_T, ST_T, ST_T, ST_T, ST_T, ST_T, ST_T, ST_T, ST_J, ST_T, ST_T, ST_T, ST_T, ST_T, ST_T, ST_S, ST_AB, ST_T, ST_T},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_U, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L, ST_L},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_AF, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N, ST_N},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_X, ST_V, ST_X, ST_X, ST_X, ST_W, ST_X, ST_X, ST_X, ST_X},
        {ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Y, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z, ST_Z},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_AA, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AA, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AB, ST_AC, ST_AC},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_AD, ST_ERRO, ST_ERRO, ST_AE, ST_ERRO, ST_ERRO, ST_AD, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_AE, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AE, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC, ST_AC},
        {ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AG, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF},
        {ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AH, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF, ST_AF},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AL, ST_AI, ST_AL},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_AK, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO},
        {ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO, ST_ERRO}};

    for (int i = 0; i < NUM_ESTADOS; i++)
        for (int j = 0; j < NUM_CLASSES; j++)
            tabela_transicao[i][j] = tabela[i][j];
}

Estado move(int estado, int classe)
{
    return tabela_transicao[estado][classe];
}

void inicializa_finais()
{
    for (int i = 0; i < N_ESTADOS; i++)
        estado_final[i] = TK_NULO;

    estado_final[ST_C] = TK_PARENTESE_ABRE;
    estado_final[ST_D] = TK_PARENTESE_FECHA;
    estado_final[ST_E] = TK_DOIS_PONTOS;
    estado_final[ST_F] = TK_VIRGULA;
    estado_final[ST_G] = TK_OP_ADI;
    estado_final[ST_H] = TK_OP_MUL;
    estado_final[ST_K] = TK_PONTO_VIRGULA;
    estado_final[ST_L] = TK_ATRIBUICAO;
    estado_final[ST_M] = TK_OP_SUB;
    estado_final[ST_N] = TK_OP_DIV;

    estado_final[ST_Q] = TK_ID;
    estado_final[ST_R] = TK_OP_POT;
    estado_final[ST_T] = TK_NUM;   // ATRIBUTO INT
    estado_final[ST_U] = TK_RELOP; // ==
    estado_final[ST_V] = TK_RELOP; // <=
    estado_final[ST_W] = TK_RELOP; // <>
    estado_final[ST_X] = TK_RELOP; // <
    estado_final[ST_Y] = TK_RELOP; // >=
    estado_final[ST_Z] = TK_RELOP; // >

    estado_final[ST_AC] = TK_NUM; // FLOAT
    estado_final[ST_AH] = TK_COMENTARIO;
    estado_final[ST_AK] = TK_CHAR_CONTEUDO;
    estado_final[ST_AL] = TK_SEPARADOR;
}

int is_estado_final(int estado)
{
    return estado_final[estado] != TK_NULO || estado == ST_ERRO;
}

int token_final(Estado estado)
{
    return estado_final[estado];
}

void inicializa_lookahead()
{

    estado_lookahead[ST_Q] = 1;
    estado_lookahead[ST_H] = 1;
    estado_lookahead[ST_T] = 1;
    estado_lookahead[ST_AC] = 1;
    estado_lookahead[ST_L] = 1;
    estado_lookahead[ST_N] = 1;
    estado_lookahead[ST_X] = 1;
    estado_lookahead[ST_Z] = 1;
    estado_lookahead[ST_AL] = 1;
}

int needs_lookahead(int estado)
{
    return estado_lookahead[estado];
}

Estado estado_inicial()
{
    return ST_A;
}

void inicializa_tabela_transicao()
{
    inicializa_tabela();
    inicializa_finais();
    inicializa_lookahead();
}

ClasseEntrada classifica_caractere(char entrada)
{

    if (entrada == 'e' || entrada == 'E')
        return CLS_Ee;

    if (is_alpha(entrada))
        return CLS_LETRA;

    if (entrada == '_')
        return CLS_UNDERLINE;

    if (entrada == '(')
        return CLS_ABRE_PAR;

    if (entrada == ')')
        return CLS_FECHA_PAR;

    if (entrada == ':')
        return CLS_DOIS_PONTOS;

    if (entrada == ',')
        return CLS_VIRGULA;

    if (entrada == '+')
        return CLS_MAIS;

    if (entrada == '*')
        return CLS_ASTERISCO;

    if (entrada == '\'')
        return CLS_APOSTROFO;

    if (entrada == ';')
        return CLS_PONTO_VIRGULA;

    if (entrada == '=')
        return CLS_IGUAL;

    if (is_digit(entrada))
        return CLS_DIGITO;

    if (entrada == '-')
        return CLS_MENOS;

    if (entrada == '/')
        return CLS_BARRA;

    if (entrada == '<')
        return CLS_MENOR;

    if (entrada == '>')
        return CLS_MAIOR;

    if (entrada == '.')
        return CLS_PONTO;

    if (isSeparador(entrada))
        return CLS_SEPARADOR;

    return CLS_OUTROS;
}