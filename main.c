/* enum tipo_token {
    ESTADO_INICIAL = 256,
    BEGIN, //inicio ✅
    ID, //id 
    NUMBER,
    STRING,
    COMMENTARY,
    TYPE_INT, //int ✅
    TYPE_FLOAT, //float
    TYPE_STRING, //string
    IF, //if ✅
    ELSE, //else ✅
    WHILE, //while ✅
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
};*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//nome_tokens

enum tipo_token {
    ESTADO_INICIAL = 256,
    BEGIN, //inicio 
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

int estado = ESTADO_INICIAL;
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

int falhar() {

  cont_sim_lido++;

  switch (estado) {

    case BEGIN:
      partida = END;
      break;

    case END:
      partida = ELSE;
      break;

    case ELSE:
      partida = BEGIN;
      break;

  }
  return partida;
}

Token proximo_token() {
  Token token;
  char c;
  while (cont_sim_lido < strlen(code) && code[cont_sim_lido] != '\0') {
    switch (estado) {
        
      case ESTADO_INICIAL:
            c = code[cont_sim_lido];
            if ((c == ' ') || (c == '\n')) {
              estado = ESTADO_INICIAL;
              cont_sim_lido++;
            }
            else if (c == 'i') {
                estado = BEGIN;
                cont_sim_lido++;
                printf("DEBUG: encontrou 'i', foi para estado BEGIN\n");
            }
            else if (c == 'f') {
                estado = END;
                cont_sim_lido++;
                printf("DEBUG: encontrou 'f', foi para estado END\n");
            }
            else if (c == 'e') {
                estado = ELSE;
                cont_sim_lido++;
                printf("DEBUG: encontrou 'e', foi para estado ELSE\n");
            }
            else if (c == 'w') {
              estado = WHILE;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'w', foi para estado WHILE\n");
            }
            else if (c == ';') {
              estado = SEMICOLON;
              cont_sim_lido++;
            }
            else if (c == '=') {
              estado = ASSIGN;
              cont_sim_lido++;
            }
            else if (c == '(') {
              estado = LEFT_PARENTHESIS;
              cont_sim_lido++;
            }
            else if (c == ')') {
              estado = RIGHT_PARENTHESIS;
              cont_sim_lido++;
            }
            else if (c == '{') {
              estado = LEFT_BRACKET;
              cont_sim_lido++;
            }
            else if (c == '}') {
              estado = RIGHT_BRACKET;
              cont_sim_lido++;
            }
            else if (c == ',') {
              estado = COMMA;
              cont_sim_lido++;
            }
            else if (c == '+') {
              estado = OP_SUM;
              cont_sim_lido++;
            }
            else if (c == '-') {
              estado = OP_SUB;
              cont_sim_lido++;
            }
            else if (c == '*') {
              estado = OP_MUL;
              cont_sim_lido++;
            }
            else if (c == '/') {
              estado = OP_DIV;
              cont_sim_lido++;
            }
            else 
              estado = falhar();
            break;

      case BEGIN:
            c = code[cont_sim_lido];
            if (c == 'n'){
              estado = 1;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'n', foi para estado 1\n");
            }
            else if (c == 'f'){
              estado = IF;
              printf("DEBUG: encontrou 'f', foi para estado IF\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 1:
            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 2;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 2\n");
            }
            else if (c == 't'){
              estado = TYPE_INT;
              printf("DEBUG: encontrou 't', foi para estado TYPE_INT\n");
            }
            else{
              estado = BEGIN;
            }
            break;

        case 2:
            c = code[cont_sim_lido];
            if (c == 'c'){
              estado = 3;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'c', foi para estado 3\n");
            }
            else{
              estado = BEGIN;
            }
            break;
  
        case 3:
            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 4;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 4\n");
            }
            else{
              estado = BEGIN;
            }
            break;
        
        case 4:
            c = code[cont_sim_lido];
            if (c == 'o'){
              estado = 5;
              printf("DEBUG: encontrou 'o', foi para estado 5\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 5:
            cont_sim_lido++;
            printf("<inicio, >\n");
            token.nome_token = BEGIN;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;
        
        case END: 

            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 7;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 7\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 7:
            c = code[cont_sim_lido];
            if (c == 'm'){
              estado = 8;
              printf("DEBUG: encontrou 'm', foi para estado 8\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;
        
        case 8:
            cont_sim_lido++;
            printf("<end, >\n");
            token.nome_token = END;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;

        case IF: 
            cont_sim_lido++;
            printf("<if, >\n");
            token.nome_token = IF;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;
        
        case TYPE_INT: 
            cont_sim_lido++;
            printf("<int, >\n");
            token.nome_token = TYPE_INT;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;

        case ELSE:
            c = code[cont_sim_lido];
            if (c == 'l'){
              estado = 9;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'l', foi para estado 9\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;
        
        case 9:
            c = code[cont_sim_lido];
            if (c == 's'){
              estado = 10;
              cont_sim_lido++;
              printf("DEBUG: encontrou 's', foi para estado 10\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 10:
            c = code[cont_sim_lido];
            if (c == 'e'){
              estado = 11;
              printf("DEBUG: encontrou 'e', foi para estado 11\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;
          
        case 11: 
            cont_sim_lido++;
            printf("<else, >\n");
            token.nome_token = ELSE;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;
        
        case WHILE:
            c = code[cont_sim_lido];
            if (c == 'h'){
              estado = 12;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'h', foi para estado 12\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 12:
            c = code[cont_sim_lido];
            if (c == 'i'){
              estado = 13;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'i', foi para estado 13\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 13:
            c = code[cont_sim_lido];
            if (c == 'l'){
              estado = 14;
              cont_sim_lido++;
              printf("DEBUG: encontrou 'l', foi para estado 14\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 14:
            c = code[cont_sim_lido];
            if (c == 'e'){
              estado = 15;
              printf("DEBUG: encontrou 'e', foi para estado 14\n");
            }
            else{
              estado = ESTADO_INICIAL;
            }
            break;

        case 15: 
            cont_sim_lido++;
            printf("<while, >\n");
            token.nome_token = ELSE;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;

        case SEMICOLON: 
            cont_sim_lido++;
            printf("<;, >\n");
            token.nome_token = SEMICOLON;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;

        case ASSIGN: 
            cont_sim_lido++;
            printf("<=, >\n");
            token.nome_token = ASSIGN;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;
        
        case LEFT_PARENTHESIS: 
            cont_sim_lido++;
            printf("<(, >\n");
            token.nome_token = LEFT_PARENTHESIS;
            token.atributo = -1;
            estado = ESTADO_INICIAL;
            return(token);
            break;
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