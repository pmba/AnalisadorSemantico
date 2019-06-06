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
} Category;

typedef struct token {
    Category category;
    String lexeme;
    int row, col;
    struct token* next;
} Token;

Token* current_token;

void error(String msg, Token* token);
Token* newToken(Category cat, String lex, int row, int col);
void nextToken();
void funPgm();
void funListSent();

int main(int argc, char const *argv[])
{
    current_token = newToken(Point, "if", 0, 0);

    error("'Debug' expected", current_token);

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
    printf("Error: %s at %d, %d.\n", msg, token->row, token->col);
}

void funListSentRight()
{
    if (current_token->category == Semicolon) {
        nextToken();
        funListSent();
        funListSentRight();
    }
}

void funListSent()
{
    funListSent();
    funListSentRight();
}

void funBoolExpr()
{

}

void funAritExpr()
{

}

void funAtr() 
{

}

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