#ifndef PARSER_H
#define PARSER_H

#include "arvore.h"
#include "../lexer/lexer.h"

No *parser();
void match(TokenType token_esperado);

// producoes da LL1
No *call();
No *bloco();
No *declaracao_das_variaveis();
No *lista_ids();
No *lista_ids_linha();
No *sequencia_de_comandos();
No *comando_atribuicao();
No *expressao();
No *expressao_linha();
No *expressao2();
No *expressao2_linha();
No *expressao3();
No *expressao3_linha();
No *termo();
No *num_ou_id();
No *comando();
No *comando_ou_bloco();
No *comando_condicional();
No *condicao();
No *parte_e_se();
No *parte_senao();
No *comando_enquanto();
No *comando_repita();
No *comando_para();
No *op_adi_ou_sub();
No *op_mul_ou_div();
//...
#endif