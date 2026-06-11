#include "tabela_transicao.h"
#include <stdio.h>

Estado tabela_transicao[N_ESTADOS][NUM_CLASSES];
TokenType estado_final[N_ESTADOS];
int estado_lookahead[N_ESTADOS] = {0};

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

    for (int i = 0; i < N_ESTADOS; i++)
        for (int j = 0; j < NUM_CLASSES; j++)
            tabela_transicao[i][j] = ST_ERRO;

    /* Estado A */
    tabela_transicao[ST_A][CLS_LETRA] = ST_B;
    tabela_transicao[ST_A][CLS_UNDERLINE] = ST_B;
    tabela_transicao[ST_A][CLS_ABRE_PAR] = ST_C;
    tabela_transicao[ST_A][CLS_FECHA_PAR] = ST_D;
    tabela_transicao[ST_A][CLS_DOIS_PONTOS] = ST_E;
    tabela_transicao[ST_A][CLS_VIRGULA] = ST_F;
    tabela_transicao[ST_A][CLS_MAIS] = ST_G;
    tabela_transicao[ST_A][CLS_ASTERISCO] = ST_q0;
    tabela_transicao[ST_A][CLS_APOSTROFO] = ST_I;
    tabela_transicao[ST_A][CLS_DIGITO] = ST_J;
    tabela_transicao[ST_A][CLS_PONTO_VIRGULA] = ST_K;
    tabela_transicao[ST_A][CLS_IGUAL] = ST_q1;
    tabela_transicao[ST_A][CLS_MENOS] = ST_M;
    tabela_transicao[ST_A][CLS_BARRA] = ST_q2;
    tabela_transicao[ST_A][CLS_MENOR] = ST_O;
    tabela_transicao[ST_A][CLS_MAIOR] = ST_P;
    tabela_transicao[ST_A][CLS_Ee] = ST_B;
    tabela_transicao[ST_A][CLS_SEPARADOR] = ST_AI;

    /* Estado B */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_B][c] = ST_Q;

    tabela_transicao[ST_B][CLS_LETRA] = ST_B;
    tabela_transicao[ST_B][CLS_UNDERLINE] = ST_B;
    tabela_transicao[ST_B][CLS_DIGITO] = ST_B;
    tabela_transicao[ST_B][CLS_Ee] = ST_B;

    /* Estados C D E F G são de aceitação*/

    /* Estado q0 */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_q0][c] = ST_H;

    tabela_transicao[ST_q0][CLS_ASTERISCO] = ST_R;

    /* Estado H é de aceitação */

    /* Estado I */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_I][c] = ST_AJ;

    tabela_transicao[ST_I][CLS_APOSTROFO] = ST_ERRO;

    /* Estado J */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_J][c] = ST_T;

    tabela_transicao[ST_J][CLS_DIGITO] = ST_J;
    tabela_transicao[ST_J][CLS_Ee] = ST_AB;
    tabela_transicao[ST_J][CLS_PONTO] = ST_S;

    /* Estado K é de aceitação */

    /* Estado q1 */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_q1][c] = ST_L;

    tabela_transicao[ST_q1][CLS_IGUAL] = ST_U;

    /* Estados L M são de aceitação */

    /* Estado q2 */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_q2][c] = ST_N;

    tabela_transicao[ST_q2][CLS_ASTERISCO] = ST_AF;

    /* Estado N é de aceitação */

    /* Estado O */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_O][c] = ST_X;

    tabela_transicao[ST_O][CLS_IGUAL] = ST_V;
    tabela_transicao[ST_O][CLS_MAIOR] = ST_W;

    /* Estado P */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_P][c] = ST_Z;

    tabela_transicao[ST_P][CLS_IGUAL] = ST_Y;

    /* Estados Q R são de aceitação  */

    /* Estado S */
    tabela_transicao[ST_S][CLS_DIGITO] = ST_AA;

    /* Estados T U V W X Y Z são de aceitação */

    /* Estado AA */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_AA][c] = ST_AC;

    tabela_transicao[ST_AA][CLS_DIGITO] = ST_AA;
    tabela_transicao[ST_AA][CLS_Ee] = ST_AB;

    /* Estado AB */
    tabela_transicao[ST_AB][CLS_DIGITO] = ST_AE;
    tabela_transicao[ST_AB][CLS_MAIS] = ST_AD;
    tabela_transicao[ST_AB][CLS_MENOS] = ST_AD;

    /* Estado AC de aceitação */

    /* Estado AD */
    tabela_transicao[ST_AD][CLS_DIGITO] = ST_AE;

    /* Estado AE */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_AE][c] = ST_AC;

    tabela_transicao[ST_AE][CLS_DIGITO] = ST_AE;

    /* Estado AF */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_AF][c] = ST_AF;

    tabela_transicao[ST_AF][CLS_ASTERISCO] = ST_AG;

    /* Estado AG */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_AG][c] = ST_AF;

    tabela_transicao[ST_AG][CLS_BARRA] = ST_AH; // Aqui estava AF[ST_AG][CLS_BARRA]

    /* Estado H é de aceitação */

    /* Estado AI */
    for (int c = 0; c < NUM_CLASSES; c++)
        tabela_transicao[ST_AI][c] = ST_AL;

    tabela_transicao[ST_AI][CLS_SEPARADOR] = ST_AI;

    /* Estado AJ */
    tabela_transicao[ST_AJ][CLS_APOSTROFO] = ST_AK;

    /* Estados AK AL são de aceitação */
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
    return estado_final[estado] != TK_NULO;
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

    if (is_digit(entrada))
        return CLS_DIGITO;

    if (entrada == ';')
        return CLS_PONTO_VIRGULA;

    if (entrada == '=')
        return CLS_IGUAL;

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