#ifndef TOKEN_H
#define TOKEN_H

typedef enum // enum já atribui valores de 0 em diante automaticamente
{
    TK_TIPO,
    TK_PROGRAMA,
    TK_ID,
    TK_PARENTESE_ABRE,
    TK_PARENTESE_FECHA,
    TK_INICIO,
    TK_FIM,
    TK_2PTS,
    TK_PVIRG,
    TK_VIRG,
    TK_ATRIBUICAO,
    TK_OP_ADI,
    TK_OP_SUB,
    TK_OP_MUL,
    TK_OP_DIV,
    TK_OP_POT,
    TK_CHAR_CONTEUDO,
    TK_NUM,
    TK_SE,
    TK_ENTAO,
    TK_E_SE,
    TK_SENAO,
    TK_ENQUANTO,
    TK_FACA,
    TK_REPITA,
    TK_ATE,
    TK_RELOP,
    TK_PARA,
    TK_PASSO,
    // TK_COMENTARIO,
    // TK_SEPARADOR, comentário e separador são ignorados
    NUM_TOKENS
} TokenType;

typedef struct
{
    TokenType tipo;
    char lexema[100]; // valor do atributo
    int indice;       // indice na tabela de símbolos, se aplicável
    int linha;
    int coluna;

} Token;

#endif