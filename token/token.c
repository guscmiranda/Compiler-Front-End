#include "token.h"

char *token_type_to_string(TokenType tipo)
{
    switch (tipo)
    {
    case TK_NULO:
        return "NULO";
    case TK_TIPO:
        return "tipo";
    case TK_PROGRAMA:
        return "programa";
    case TK_ID:
        return "ID";
    case TK_PARENTESE_ABRE:
        return "(";
    case TK_PARENTESE_FECHA:
        return ")";
    case TK_INICIO:
        return "inicio";
    case TK_FIM:
        return "fim";
    case TK_DOIS_PONTOS:
        return ":";
    case TK_PONTO_VIRGULA:
        return ";";
    case TK_VIRGULA:
        return ",";
    case TK_ATRIBUICAO:
        return "=";
    case TK_OP_ADI:
        return "+";
    case TK_OP_SUB:
        return "-";
    case TK_OP_MUL:
        return "*";
    case TK_OP_DIV:
        return "/";
    case TK_OP_POT:
        return "**";
    case TK_CHAR_CONTEUDO:
        return "CHAR_CONTEUDO";
    case TK_NUM:
        return "numero"; //
    case TK_SE:
        return "se";
    case TK_ENTAO:
        return "entao";
    case TK_E_SE:
        return "e se";
    case TK_SENAO:
        return "senao";
    case TK_ENQUANTO:
        return "enquanto";
    case TK_FACA:
        return "faca";
    case TK_REPITA:
        return "repita";
    case TK_ATE:
        return "ate";
    case TK_RELOP:
        return ">, <, <>, ==, >=, =<";
    case TK_PARA:
        return "para";
    case TK_PASSO:
        return "passo";
    case TK_COMENTARIO:
        return "/* */"; // comentário e separador são ignorados
    case TK_EOF:
        return "$";
    }
}
