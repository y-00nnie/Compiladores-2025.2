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

int estado = BEGIN;
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
  while (cont_sim_lido < strlen(code) && code[cont_sim_lido] != '\0') {
    switch (estado) {
        
      case BEGIN:
            c = code[cont_sim_lido];
            if ((c == ' ') || (c == '\n')) {
            estado = BEGIN;
            cont_sim_lido++;
            }
            else if (c == 'i') {
                estado = 0;
                cont_sim_lido++;
                printf("DEBUG: encontrou 'i', foi para estado 0\n");
            }
            break;

        case 0:
            c = code[cont_sim_lido];
            if (c == 'n'){
              estado = 1;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'n', foi para estado 1\n");
            }
            break;

        case 1:
            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 2;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 2\n");
            }
            break;

        case 2:
            c = code[cont_sim_lido];
            if (c == 'c'){
              estado = 3;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'c', foi para estado 3\n");
            }
            break;
  
        case 3:
            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 4;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 4\n");
            }
            break;
        
        case 4:
            c = code[cont_sim_lido];
            if (c == 'o'){
              estado = 5;
              printf("DEBUG: encontrou 'o', foi para estado 5\n");
            }
            break;

        case 5:
            cont_sim_lido++;
            printf("<inicio, >\n");
            token.nome_token = BEGIN;
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