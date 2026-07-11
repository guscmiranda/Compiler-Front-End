// Implementação manual de um analisador sintático preditivo:
// - Utilizar a abordagem baseada em descida recursiva

// A parte da descida recursiva vai ser resolvida por causa da implementação da árvore sintática

// O QUE FAZER AQUI:
// - Implementar as funções correspondentes às produções da gramática ✅
// - Função que recebe o token atual e chama a função correspondente à produção da gramática  --> parser() ✅
// - Função que verifique o casamento do token atual com o token esperado e avance para o próximo token --> match(TokenType tk_esperado) ✅
// - Função que verifica se o token atual é um token de erro e trata o erro de forma adequada  --> existe error.c para isso né ✅

#include "parser.h"
#include "arvore.h"
#include "../utils/error.h"
#include "../token/token.h"
#include <stdio.h>
#include <stdlib.h>

Token tk_atual;

No *parser()
{
    tk_atual = lexer();

    No *raiz = call();

    match(TK_EOF);

    return raiz;
}

void match(TokenType tk_esperado)
{
    if (tk_atual.tipo == tk_esperado)
    {
        tk_atual = lexer();
    }
    else
    {
        syn_error(tk_atual, tk_esperado);
    }
}

No *call()
{
    // <call> ::= tipo programa () <bloco>
    // FIRST(<call>) = {tipo}
    No *n = cria_no("call");

    adiciona_filho(n, cria_no("tipo"));
    match(TK_TIPO);

    adiciona_filho(n, cria_no("programa"));
    match(TK_PROGRAMA);

    adiciona_filho(n, cria_no("("));
    match(TK_PARENTESE_ABRE);

    adiciona_filho(n, cria_no(")"));
    match(TK_PARENTESE_FECHA);

    adiciona_filho(n, bloco());

    return n;
}

No *bloco()
{
    // <bloco> ::= inicio <declaracao_das_variaveis> <sequencia_de_comandos> fim
    // FIRST(<bloco>) = {inicio}
    No *n = cria_no("bloco");

    adiciona_filho(n, cria_no("inicio"));
    match(TK_INICIO);

    adiciona_filho(n, declaracao_das_variaveis());
    adiciona_filho(n, sequencia_de_comandos());

    adiciona_filho(n, cria_no("fim"));
    match(TK_FIM);

    return n;
}

No *declaracao_das_variaveis()
{
    // <declaracao_das_variaveis> ::= tipo: <lista_ids>; <declaracao_das_variaveis> | ϵ
    No *n = cria_no("declaracao_das_variaveis");

    if (tk_atual.tipo == TK_TIPO)
    {
        adiciona_filho(n, cria_no("tipo"));
        match(TK_TIPO);
        adiciona_filho(n, cria_no(":"));
        match(TK_DOIS_PONTOS);
        adiciona_filho(n, lista_ids());
        adiciona_filho(n, cria_no(";"));
        match(TK_PONTO_VIRGULA);
        adiciona_filho(n, declaracao_das_variaveis());
    }

    return n;
}

No *lista_ids()
{
    // <lista_ids> ::= ID <lista_ids_linha>
    No *n = cria_no("lista_ids");

    adiciona_filho(n, cria_no("ID"));
    match(TK_ID);
    adiciona_filho(n, lista_ids_linha());

    return n;
}

No *lista_ids_linha()
{
    // <lista_ids_linha> ::= , ID <lista_ids_linha> | ϵ
    No *n = cria_no("lista_ids_linha");

    if (tk_atual.tipo == TK_VIRGULA)
    {
        adiciona_filho(n, cria_no(","));
        match(TK_VIRGULA);
        adiciona_filho(n, cria_no("ID"));
        match(TK_ID);
        adiciona_filho(n, lista_ids_linha());
    }

    return n;
}

No *sequencia_de_comandos()
{
    // <sequencia_de_comandos> ::= <comando> <sequencia_de_comandos> | ϵ
    // FIRST(<sequencia_de_comandos>) = { ID, ENQUANTO, SE, PARA, REPITA, ϵ}
    No *n = cria_no("sequencia_de_comandos");

    if (tk_atual.tipo == TK_ID || tk_atual.tipo == TK_ENQUANTO || tk_atual.tipo == TK_SE || tk_atual.tipo == TK_PARA || tk_atual.tipo == TK_REPITA)
    {
        adiciona_filho(n, comando());
        adiciona_filho(n, sequencia_de_comandos());
    }

    return n;
}

No *comando_atribuicao()
{
    // <comando_atribuicao> ::= ID = <expressao>;
    // FIRST(<comando_atribuicao>) = { ID }
    No *n = cria_no("comando_atribuicao");

    adiciona_filho(n, cria_no("ID"));
    match(TK_ID);
    adiciona_filho(n, cria_no("="));
    match(TK_ATRIBUICAO);
    adiciona_filho(n, expressao());
    adiciona_filho(n, cria_no(";"));
    match(TK_PONTO_VIRGULA);

    return n;
}

No *expressao()
{
    // <expressao> ::= <expressao2> <expressao_linha>
    No *n = cria_no("expressao");

    adiciona_filho(n, expressao2());
    adiciona_filho(n, expressao_linha());

    return n;
}

No *expressao_linha()
{
    // <expressao’> ::= <op_adi_ou_sub> <expressao2> <expressao’> | ϵ
    // FIRST(<expressao_linha>) = {OP_ADI, OP_SUB, ε}
    No *n = cria_no("expressao_linha");

    if (tk_atual.tipo == TK_OP_ADI || tk_atual.tipo == TK_OP_SUB)
    {
        adiciona_filho(n, op_adi_ou_sub());
        adiciona_filho(n, expressao2());
        adiciona_filho(n, expressao_linha());
    }

    return n;
}

No *expressao2()
{
    // <expressao2> ::= <expressao3> <expressao2’>
    No *n = cria_no("expressao2");

    adiciona_filho(n, expressao3());
    adiciona_filho(n, expressao2_linha());

    return n;
}

No *expressao2_linha()
{
    // <expressao2’> ::= <op_mul_ou_div> <expressao3> <expressao2’> | ϵ
    No *n = cria_no("expressao2_linha");

    if (tk_atual.tipo == TK_OP_MUL || tk_atual.tipo == TK_OP_DIV)
    {
        adiciona_filho(n, op_mul_ou_div());
        adiciona_filho(n, expressao3());
        adiciona_filho(n, expressao2_linha());
    }

    return n;
}

No *expressao3()
/*<expressao3> ::= <termo> <expressao3’>*/
// FIRST(<expressao3>) = {ID, NUM, OP_SUB, CONTEUDO_CHAR, ( }
{
    No *n = cria_no("expressao3");

    adiciona_filho(n, termo());
    adiciona_filho(n, expressao3_linha());

    return n;
}

No *expressao3_linha()
{
    // <expressao3'> ::= OP_POT <expressao3> | ϵ
    // FIRST(<expressao3'>) = {OP_POT, ε}
    No *n = cria_no("expressao3_linha");

    if (tk_atual.tipo == TK_OP_POT)
    {
        adiciona_filho(n, cria_no("OP_POT"));
        match(TK_OP_POT);
        adiciona_filho(n, expressao3());
    }

    return n;
}

No *termo()
{
    // <termo> ::= ID | NUM | OP_SUB <num_ou_id> | CONTEUDO_CHAR | (<expressao>)
    No *n = cria_no("termo");

    if (tk_atual.tipo == TK_ID)
    {
        adiciona_filho(n, cria_no("ID"));
        match(TK_ID);
    }
    else if (tk_atual.tipo == TK_NUM)
    {
        adiciona_filho(n, cria_no("NUM"));
        match(TK_NUM);
    }
    else if (tk_atual.tipo == TK_OP_SUB)
    {
        adiciona_filho(n, cria_no("OP_SUB"));
        match(TK_OP_SUB);
        // adiciona_filho(n, num_ou_id());
    }
    else if (tk_atual.tipo == TK_CHAR_CONTEUDO)
    {
        adiciona_filho(n, cria_no("CONTEUDO_CHAR"));
        match(TK_CHAR_CONTEUDO);
    }
    else if (tk_atual.tipo == TK_PARENTESE_ABRE)
    {
        adiciona_filho(n, cria_no("("));
        match(TK_PARENTESE_ABRE);
        // adiciona_filho(n, expressao());
        adiciona_filho(n, cria_no(")"));
        match(TK_PARENTESE_FECHA);
    }
    else
    {
        TokenType first_set[] = {TK_ID, TK_NUM, TK_OP_SUB, TK_CHAR_CONTEUDO, TK_PARENTESE_ABRE};
        syn_error_first(tk_atual, first_set, 5);
    }

    return n;
}

No *num_ou_id()
{
    //<num_ou_id> ::= NUM | ID
    // FIRST(<num_ou_id>) = { NUM, ID }
    No *n = cria_no("num_ou_id");
    if (tk_atual.tipo == TK_NUM)
    {
        adiciona_filho(n, cria_no("NUM"));
        match(TK_NUM);
    }
    else if (tk_atual.tipo == TK_ID)
    {
        adiciona_filho(n, cria_no("ID"));
        match(TK_ID);
    }
    else
    {
        TokenType first_set[] = {TK_ID, TK_NUM};
        syn_error_first(tk_atual, first_set, 2);
    }
    return n;
}

No *comando()
{
    //<comando> ::= <comando_atribuicao> | <comando_enquanto> | <comando_condicional> |<comando_para> | <comando_repita>
    // FIRST(<comando>) = { ID, ENQUANTO, SE, PARA, REPITA }
    No *n = cria_no("comando");
    if (tk_atual.tipo == TK_ID)
    {
        adiciona_filho(n, comando_atribuicao());
    }
    else if (tk_atual.tipo == TK_ENQUANTO)
    {
        adiciona_filho(n, comando_enquanto());
    }
    else if (tk_atual.tipo == TK_SE)
    {
        adiciona_filho(n, comando_condicional());
    }
    else if (tk_atual.tipo == TK_PARA)
    {
        adiciona_filho(n, comando_para());
    }
    else if (tk_atual.tipo == TK_REPITA)
    {
        adiciona_filho(n, comando_repita());
    }
    else
    {
        TokenType first_set[] = {TK_ID, TK_ENQUANTO, TK_SE, TK_PARA, TK_REPITA};
        syn_error_first(tk_atual, first_set, 5);
    }

    return n;
}

No *comando_ou_bloco()
{
    //<comando_ou_bloco> ::= <comando> | <bloco>
    // FIRST(<comando_ou_bloco> ) = FIRST(<comando>) ∪ FIRST(<bloco>) = { ID, ENQUANTO,SE, PARA, REPITA, inicio }
    No *n = cria_no("comando_ou_bloco");
    if (tk_atual.tipo == TK_INICIO)
    {
        adiciona_filho(n, bloco());
    }
    else if (tk_atual.tipo == TK_ID || tk_atual.tipo == TK_ENQUANTO || tk_atual.tipo == TK_SE || tk_atual.tipo == TK_PARA || tk_atual.tipo == TK_REPITA)
    {
        adiciona_filho(n, comando());
    }
    else
    {
        TokenType first_set[] = {TK_ID, TK_ENQUANTO, TK_SE, TK_PARA, TK_REPITA, TK_INICIO};
        syn_error_first(tk_atual, first_set, 6);
    }
    return n;
}

No *comando_condicional()
{
    // <comando_condicional> ::= SE (<condicao>) ENTAO <comando_ou_bloco> <parte_e_se> <parte_senao>
    No *n = cria_no("comando_condicional");

    adiciona_filho(n, cria_no("SE"));
    match(TK_SE);

    adiciona_filho(n, cria_no("("));
    match(TK_PARENTESE_ABRE);

    adiciona_filho(n, condicao());

    adiciona_filho(n, cria_no(")"));
    match(TK_PARENTESE_FECHA);

    adiciona_filho(n, cria_no("ENTAO"));
    match(TK_ENTAO);

    adiciona_filho(n, comando_ou_bloco());

    adiciona_filho(n, parte_e_se());

    adiciona_filho(n, parte_senao());

    return n;
}

No *condicao()
{
    // <condicao> ::= <expressao> RELOP <expressao>
    No *n = cria_no("condicao");

    adiciona_filho(n, expressao());
    adiciona_filho(n, cria_no("RELOP"));
    match(TK_RELOP);
    adiciona_filho(n, expressao());

    return n;
}

No *parte_e_se()
{
    //<parte_e_se> ::= E_SE (<condicao>) ENTAO <comando_ou_bloco> <parte_e_se> | ϵ
    // FIRST(<parte_e_se> ) = { E_SE, ϵ}
    No *n = cria_no("parte_e_se");
    if (tk_atual.tipo == TK_E_SE)
    {
        adiciona_filho(n, cria_no("E_SE"));
        match(TK_E_SE);

        adiciona_filho(n, cria_no("("));
        match(TK_PARENTESE_ABRE);

        adiciona_filho(n, condicao());

        adiciona_filho(n, cria_no(")"));
        match(TK_PARENTESE_FECHA);

        adiciona_filho(n, cria_no("ENTAO"));
        match(TK_ENTAO);

        adiciona_filho(n, comando_ou_bloco());

        adiciona_filho(n, parte_e_se());
    }
    return n;
}

No *parte_senao()
{
    //<parte_senao> ::= SENAO <comando_ou_bloco> | ϵ
    // FIRST(<parte_senao> ) = { SENAO, ϵ }
    No *n = cria_no("parte_senao");
    if (tk_atual.tipo == TK_SENAO)
    {
        adiciona_filho(n, cria_no("SENAO"));
        match(TK_SENAO);
        adiciona_filho(n, comando_ou_bloco());
    }
    return n;
}

No *comando_enquanto()
{
    //<comando_enquanto> ::= ENQUANTO (<condicao>) FACA <comando_ou_bloco>
    // FIRST(<comando_enquanto> ) = { ENQUANTO }
    No *n = cria_no("comando_enquanto");

    adiciona_filho(n, cria_no("ENQUANTO"));
    match(TK_ENQUANTO);
    adiciona_filho(n, cria_no("("));
    match(TK_PARENTESE_ABRE);
    adiciona_filho(n, condicao());
    adiciona_filho(n, cria_no(")"));
    match(TK_PARENTESE_FECHA);
    adiciona_filho(n, cria_no("FACA"));
    match(TK_FACA);
    adiciona_filho(n, comando_ou_bloco());

    return n;
}

No *comando_repita()
{
    //<comando_repita> ::= REPITA <comando_ou_bloco> ATE (<condicao>);
    // FIRST(<comando_repita>) = { REPITA }
    No *n = cria_no("comando_repita");

    adiciona_filho(n, cria_no("REPITA"));
    match(TK_REPITA);
    adiciona_filho(n, comando_ou_bloco());
    adiciona_filho(n, cria_no("ATE"));
    match(TK_ATE);
    adiciona_filho(n, cria_no("("));
    match(TK_PARENTESE_ABRE);
    adiciona_filho(n, condicao());
    adiciona_filho(n, cria_no(")"));
    match(TK_PARENTESE_FECHA);
    adiciona_filho(n, cria_no(";"));
    match(TK_PONTO_VIRGULA);

    return n;
}

No *comando_para()
{
    // <comando_para> ::= PARA ID = NUM ATE NUM PASSO <op_adi_ou_sub> NUM <comando_ou_bloco>
    // FIRST(<comando_para>) = { PARA }

    No *n = cria_no("comando_para");

    adiciona_filho(n, cria_no("PARA"));
    match(TK_PARA);

    adiciona_filho(n, cria_no("ID"));
    match(TK_ID);

    adiciona_filho(n, cria_no("="));
    match(TK_ATRIBUICAO);

    adiciona_filho(n, cria_no("NUM"));
    match(TK_NUM);

    adiciona_filho(n, cria_no("ATE"));
    match(TK_ATE);

    adiciona_filho(n, cria_no("NUM"));
    match(TK_NUM);

    adiciona_filho(n, cria_no("PASSO"));
    match(TK_PASSO);

    adiciona_filho(n, op_adi_ou_sub());

    adiciona_filho(n, cria_no("NUM"));
    match(TK_NUM);

    adiciona_filho(n, comando_ou_bloco());

    return n;
}

No *op_adi_ou_sub()
{
    // <op_adi_ou_sub> ::= OP_ADI | OP_SUB
    // FIRST(<op_adi_ou_sub>) = { OP_ADI, OP_SUB }
    No *n = cria_no("op_adi_ou_sub");

    if (tk_atual.tipo == TK_OP_ADI)
    {
        adiciona_filho(n, cria_no("OP_ADI"));
        match(TK_OP_ADI);
    }
    else if (tk_atual.tipo == TK_OP_SUB)
    {
        adiciona_filho(n, cria_no("OP_SUB"));
        match(TK_OP_SUB);
    }
    else
    {
        TokenType first_set[] = {TK_OP_ADI, TK_OP_SUB};
        syn_error_first(tk_atual, first_set, 2);
    }

    return n;
}

No *op_mul_ou_div()
{
    // <op_mul_ou_div> ::= OP_MUL | OP_DIV
    // FIRST(<op_mul_ou_div>) = {OP_MUL, OP_DIV}
    No *n = cria_no("op_mul_ou_div");

    if (tk_atual.tipo == TK_OP_MUL)
    {
        adiciona_filho(n, cria_no("OP_MUL"));
        match(TK_OP_MUL);
    }
    else if (tk_atual.tipo == TK_OP_DIV)
    {
        adiciona_filho(n, cria_no("OP_DIV"));
        match(TK_OP_DIV);
    }
    else
    {
        TokenType first_set[] = {TK_OP_MUL, TK_OP_DIV};
        syn_error_first(tk_atual, first_set, 2);
    }

    return n;
}