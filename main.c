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
    EndOfFile, Point, 
} Category;

typedef struct token {
    Category category;
    String lexeme;
    int row, col;
    struct token* next;
} Token;

Token* current_token;

Token* newToken(Category cat, String lex, int row, int col);
void nextToken();
void funPgm();

int main(int argc, char const *argv[])
{
    current_token = newToken(Point, ".", 0, 0);

    free(current_token);
    return 0;
}

Token* newToken(Category cat, String lex, int row, int col)
{
    Token* new_token = malloc(sizeof(Token*));
    new_token->category = cat;
    new_token->lexeme = lex;
    new_token->row = row;
    new_token->col = col;
    return new_token;
}

void nextToken()
{
    
}

void funLSentRight()
{

}

void funLSent()
{

}

void funPgm()
{
    funLSent();

    if ( current_token->category == Point ) {
        
    }
}