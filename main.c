#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//nome_tokens

enum tipo_token {
    BEGIN = 256,
    ID, //id
    NUMBER,
    STRING,
    COMMENTARY,
    TYPE_INT, //int
    TYPE_FLOAT, //float
    TYPE_STRING, //string
    IF, //if
    ELSE, //else
    WHILE, //while
    READ, //read
    PRINT, //print
    SEMICOLON,//;
    ASSIGN, // =
    LEFT_PARENTHESIS, // (
    RIGHT_PARENTHESIS,// )
    LEFT_BRACKET, // {
    RIGHT_BRACKET, // }
    COMMA, // ,
    OP_SUM, // +
    OP_SUB, // -
    OP_MUL, // *
    OP_DIV, // /
    END // fim
};

typedef struct Token {
  enum tipo_token nome_token;
  int atributo;
} Token;

int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
int valor_lexico;
char *code;

unsigned char *readFile(char *fileName) {
  FILE *file = fopen(fileName, "r");
  char *code;
  int n = 0;
  int c;

  if (!file) {
    fprintf(stderr, "Erro ao ler o arquivo: %s.\n", fileName);
    exit(3);
  }

  fseek(file, 0, SEEK_END);
  long f_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  code = (unsigned char *)malloc((f_size + 1) * sizeof(char));

  while ((c = fgetc(file)) != EOF) {
    code[n++] = (unsigned char)c;
  }
  code[n] = '\0';
  return code;
}

Token proximo_token() {
  Token token;
  char c;
  while (code[cont_sim_lido] != EOF) {
    switch (estado) {
        case BEGIN:
            c = code[cont_sim_lido];
            if ((c == ' ') || (c == '\n')) {
            estado = BEGIN;
            cont_sim_lido++;
            }
            else if (c == 'i')
                estado = 0;
            break;
        
        case 0:
            cont_sim_lido++;
            printf("<inicio, >\n");
            token.nome_token = INICIO;
            token.atributo = -1;
            estado = BEGIN;
            return(token);
      }

    }
}


int main() {
  Token token;
  code = readFile("programa.txt");
  do {
    token = proximo_token();
  } while (token.nome_token != EOF);
  free(code);
}