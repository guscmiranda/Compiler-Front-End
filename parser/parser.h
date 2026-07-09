#ifndef PARSER_H
#define PARSER_H

#include "arvore.h"
#include "../lexer/lexer.h"

//alguem confirma se ta tudo aqui tenho medo de pular
enum TipoToken {
    TK_TIPO, TK_PROGRAMA, TK_PARENTESE_ABRE, TK_PARENTESE_FECHA,
    TK_INICIO, TK_FIM, TK_ID, TK_NUM, TK_CHAR_CONTEUDO,
    TK_OP_ADI, TK_OP_SUB, TK_OP_MUL, TK_OP_DIV, TK_OP_POT,
    TK_ATRIBUICAO, TK_DOIS_PONTOS, TK_PONTO_VIRGULA, TK_VIRGULA,
    TK_SE, TK_ENTAO, TK_E_SE, TK_SENAO, TK_ENQUANTO, TK_FACA,
    TK_REPITA, TK_ATE, TK_PARA, TK_PASSO, TK_RELOP, TK_EOF
};

extern Token tk_atual;

Token get_next_token(); 
void match(int token_esperado);
void erro_sintatico(char *mensagem_esperada);

// producoes da LL1
No *call();
No *bloco();
No *termo();
No *declaracao_das_variaveis();
No *sequencia_de_comandos();
No *expressao3();
No *expressao3_linha();
//...
#endif 