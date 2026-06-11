// Aqui faremos a implementação das transições do autômato para o lexer.

/* A tabela de transição é uma estrutura que define como o autômato deve se comportar ao ler cada
caractere de entrada, dependendo do estado atual. */

/* Acho que dá para enumerar as entradas da tabela de transição, daí a tabela
seria uma matriz de estados x entradas, onde cada célula indica o próximo estado do autômato. */

// a matriz seria basicamente a planilha que o daniel fez

#include "../token/token.h"

#ifndef TABELA_TRANSICAO_H
#define TABELA_TRANSICAO_H

typedef enum
{
    CLS_LETRA, // excluindo Ee
    CLS_UNDERLINE,
    CLS_ABRE_PAR,
    CLS_FECHA_PAR,
    CLS_DOIS_PONTOS,
    CLS_VIRGULA,
    CLS_MAIS,
    CLS_ASTERISCO,
    CLS_APOSTROFO,
    CLS_DIGITO,
    CLS_PONTO_VIRGULA,
    CLS_IGUAL,
    CLS_MENOS,
    CLS_BARRA,
    CLS_MENOR,
    CLS_MAIOR,
    CLS_PONTO,
    CLS_Ee,
    CLS_SEPARADOR,
    CLS_OUTROS,

    NUM_CLASSES,

} ClasseEntrada;

typedef enum
{
    ST_A,
    ST_B,
    ST_C,
    ST_D,
    ST_E,
    ST_F,
    ST_G,
    ST_H,
    ST_I,
    ST_J,
    ST_K,
    ST_L,
    ST_M,
    ST_N,
    ST_O,
    ST_P,
    ST_Q,
    ST_R,
    ST_S,
    ST_T,
    ST_U,
    ST_V,
    ST_W,
    ST_X,
    ST_Y,
    ST_Z,
    ST_AA,
    ST_AB,
    ST_AC,
    ST_AD,
    ST_AE,
    ST_AF,
    ST_AG,
    ST_AH,
    ST_AI,
    ST_AJ,
    ST_AK,
    ST_AL,
    ST_q0,
    ST_q1,
    ST_q2,
    NUM_ESTADOS,

    ST_ERRO = -1,

} Estado;

#define N_ESTADOS NUM_ESTADOS + 1

void inicializa_tabela_transicao();
Estado estado_inicial();
Estado move(int estado, int classe);
int is_estado_final(int estado);
int needs_lookahead(int estado);
int token_final(Estado estado);

ClasseEntrada classifica_caractere(char entrada);

#endif // TABELA_TRANSICAO_