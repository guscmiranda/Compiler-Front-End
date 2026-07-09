#ifndef TOKEN_H
#define TOKEN_H

typedef enum // enum já atribui valores de 0 em diante automaticamente
{
    TK_NULO, // 0
    TK_TIPO,
    TK_PROGRAMA,
    TK_ID,
    TK_PARENTESE_ABRE,
    TK_PARENTESE_FECHA, // 5
    TK_INICIO,
    TK_FIM,
    TK_DOIS_PONTOS,
    TK_PONTO_VIRGULA,
    TK_VIRGULA, // 10
    TK_ATRIBUICAO,
    TK_OP_ADI,
    TK_OP_SUB,
    TK_OP_MUL,
    TK_OP_DIV, // 15
    TK_OP_POT,
    TK_CHAR_CONTEUDO,
    TK_NUM,
    TK_SE,
    TK_ENTAO, // 20
    TK_E_SE,
    TK_SENAO,
    TK_ENQUANTO,
    TK_FACA,
    TK_REPITA, // 25
    TK_ATE,
    TK_RELOP,
    TK_PARA,
    TK_PASSO,
    TK_COMENTARIO, // 30
    TK_SEPARADOR,  // comentário e separador são ignorados
    TK_EOF,
    NUM_TOKENS
} TokenType;

typedef struct
{
    TokenType tipo;
    char atributo[100]; // valor do atributo
    // int indice;         // indice na tabela de símbolos, se aplicável
    int linha;
    int coluna;

} Token;

char *token_type_to_string(TokenType tipo);

#endif