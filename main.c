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
    EndOfFile, Point, Semicolon, 
} Category;

typedef struct token {
    Category category;
    String lexeme;
    int row, col;
    struct token* next;
} Token;

Token* current_token;

void error(Token* token);
Token* newToken(Category cat, String lex, int row, int col);
void nextToken();
void funPgm();
void funListSent();

int main(int argc, char const *argv[])
{
    current_token = newToken(Point, "if", 0, 0);

    error(current_token);

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

void error(Token* token)
{
    printf("Error: '%s' expected at %d, %d.\n", token->lexeme, token->row, token->col);
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

void funSent()
{
    
}

void funPgm()
{
    funListSent();

    if (current_token->category == Point) {

        nextToken();

        if (current_token->category == EndOfFile) {
            return;
        } else {
            return error(current_token);
        }
    } else {
        return error(current_token);
    }
}