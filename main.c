#include <stdio.h>
#include <stdlib.h>

/****************************

Phyllipe Matheus Bezerra Alves
Universidade Federal de Alagoas
Ciencia da Computacao

*****************************/

#define DEBUG if(0)

typedef char* String;

typedef enum cat {
    EndOfFile, Point, Semicolon, If, Then, Else, For, To, Repeat, End,
    Id, Equals, BoolOp, AritOp, Not, True, False, OpenPar, ClosePar,
    CteInt, CteReal 
} Category;

typedef struct token {
    Category category;
    String lexeme;
    int row, col;
    struct token* next;
} Token;

Token* current_token;

Token* newToken(Category cat, String lex, int row, int col);
void error(String msg, Token* token);
void funPgm();
void funSent();
void funAritTerm();
void funAritFactor();

int main(int argc, char const *argv[])
{
    current_token = newToken(Point, "if", 0, 0);

    error("'Debug' Expected", current_token);

    free(current_token);
    return 0;
}

Token* newToken(Category cat, String lex, int row, int col)
{
    Token* new_token = malloc(sizeof(Token));
    new_token->category = cat;
    new_token->lexeme = lex;
    new_token->row = row;
    new_token->col = col;
    return new_token;
}

void nextToken()
{
    Token* aux = current_token;
    current_token = current_token->next;
    free(aux);
}

void error(String msg, Token* token)
{
    printf("%d:%d: Error: %s\n", token->row, token->col, msg);
}

/* 
    Lsentr = ';' sent Lsentr | E
*/

void funListSentRight()
{
    if (current_token->category == Semicolon) {
        nextToken();
        funSent();
        funListSentRight();
    }
}

/*
    Lsent = sent Lsentr
*/

void funListSent()
{
    funSent();
    funListSentRight();
}

/* 
    Tar = 'opa' Ta Tar | E
*/

void funAritTermRight()
{
    if (current_token->category == AritOp) {

        nextToken();
        funAritTerm();
        funAritTermRight();

    }
}

/* 
    Ta = Fa Tar
*/

void funAritTerm()
{
    funAritFactor();
    funAritTermRight();
}

/* 
    Ear = 'opa' Ta Ear | E
*/

void funAritExprRight()
{
    if (current_token->category == AritOp) {

        nextToken();
        funAritTerm();
        funAritExprRight();

    }
}

/* 
    Ea = Ta Ear
*/

void funAritExpr()
{
    funAritTerm();
    funAritExprRight();
}

/* 
    Fa = '(' Ea ')'
       | 'Id'
       | 'CteInt'
       | 'CteReal'
*/

void funAritFactor()
{
    if (current_token->category == OpenPar) {

        nextToken();
        funAritExpr();

        if (current_token->category == ClosePar) {

            nextToken();
            return;

        } else {
            return error("')' Expected", current_token);
        }
    } else if (current_token->category == Id) {

        nextToken();
        return;

    } else if (current_token->category == CteInt) {
        
        nextToken();
        return;

    } else if (current_token->category == CteReal) {
        
        nextToken();
        return;

    }
}

/* 
    Tb = 'Not' Tb
       | 'True'
       | 'False'
       | Ea
*/

void funBoolTerm()
{
    if (current_token->category == Not) {

        nextToken();
        funBoolTerm();

    } else if (current_token->category == True) {
        
        nextToken();
        return;

    } else if (current_token->category == False) {

        nextToken();
        return;

    } else {
        funAritExpr();
    }
}

/* 
    Ebr = 'opa' Tb Ebr | E
*/

void funBoolExprRight()
{
    if (current_token->category == BoolOp) {
        
        nextToken();
        funBoolTerm();
        funBoolExprRight();
    }
}

/* 
    Eb = Tb Ebr
*/

void funBoolExpr()
{
    funBoolTerm();
    funBoolExprRight();
}

/* 
    Atr = 'Id' 'Equals' Ea
*/

void funAtr() 
{
    if (current_token->category == Id) {
        
        nextToken();

        if (current_token->category == Equals) {

            nextToken();
            funAritExpr();

        } else {
            return error("'=' Expected", current_token);
        }
    } else {
        return error("'Id' Expected", current_token);
    }
}

/* 
    Sent = 'If' Eb 'Then' LSent 'End'
         | 'If' Eb 'Then' LSent 'Else' Lsent 'End'
         | 'For' Atr 'To' Ea 'Repeat' Lsent 'End'
         | Atr
*/

void funSent()
{
    if (current_token->category == If) {

        nextToken();
        funBoolExpr();

        if (current_token->category == Then) {

            nextToken();
            funListSent();

            if (current_token->category == Else) {

                nextToken();
                funListSent();

                if (current_token->category == End) {

                    nextToken();
                    return;
                } else {
                    return error("'End' Expected", current_token);
                }

            } else if (current_token->category == End) {

                nextToken();
                return;
            } else {
                return error("'End' Expected", current_token);
            }

        } else {
            return error("'Then' Expected", current_token);
        }

    } else if (current_token->category == For) {

        nextToken();
        funAtr();

        if (current_token->category == To) {

            nextToken();
            funAritExpr();

            if (current_token->category == Repeat) {

                nextToken();
                funListSent();

                if (current_token->category == End) {
                    
                    nextToken();
                    return;
                
                } else {
                    return error("'End' Expected", current_token);
                }
            } else {
                return error("'Repeat' Expected", current_token);
            }
        } else {
            return error("'To' Expected", current_token);
        }
    } else {

        funAtr();
        return;
    }
}

/* 
    Pgm = Lsent'.'
*/

void funPgm()
{
    funListSent();

    if (current_token->category == Point) {

        nextToken();

        if (current_token->category == EndOfFile) {
            return;
        } else {
            return error("'EOF' Expected", current_token);
        }
    } else {
        return error("'.' Expected", current_token);
    }
}