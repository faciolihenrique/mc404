/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * analyze                         *
 * * * * * * * * * * * * * * * * * */

#ifndef ANALYZE_H
#define ANALYZE_H

#include <stdbool.h>
#include "hash.h"

#define SIZE_FILE 4096
#define SIZE_LINE 150
#define NUMBER_LIMIT 2147483647

/* ---- DIRETIVAS ---- */
#define ALIGN_DIR               ".align"
#define ALIGN_CODE              1
#define WORD_DIR                ".word"
#define WORD_CODE               2
#define SET_DIR                 ".set"
#define SET_CODE                3
#define ORG_DIR                 ".org"
#define ORG_CODE                4
#define WFILL_DIR               ".wfill"
#define WFILL_CODE              5

/* ---- INTRUCOES ---- */
#define LOAD_MN                 "LD"
#define LOAD_CODE               1

#define LOAD_NEG_MN             "LD-"
#define LOAD_NEG_CODE           2

#define LOAD_MOD_MN             "LD|"
#define LOAD_MOD_CODE           3

#define ADD_MN                  "ADD"
#define ADD_CODE                5

#define SUB_MN                  "SUB"
#define SUB_CODE                6

#define ADD_MOD_MN              "ADD|"
#define ADD_MOD_CODE            7

#define SUB_MOD_MN              "SUB|"
#define SUB_MOD_CODE            8

#define LOAD_MQ_MX_MN           "LDmq_mx"
#define LOAD_MQ_MX_CODE         9

#define LOAD_MQ_MN              "LDmq"
#define LOAD_MQ_CODE            10

#define MUL_MN                  "MUL"
#define MUL_CODE                11

#define DIV_MN                  "DIV"
#define DIV_CODE                12

#define JUMP_MN                 "JMP"
#define JUMP_L_CODE             13
#define JUMP_R_CODE             14

#define JUMPP_MN                "JUMP+"
#define JUMPP_L_CODE            15
#define JUMPP_R_CODE            16

#define STOR_M_MN               "STaddr"
#define STOR_M_L_CODE           18
#define STOR_M_R_CODE           19

#define LSH_MN                  "LSH"
#define LSH_CODE                20

#define RSH_MN                  "RSH"
#define RSH_CODE                21

#define STOR_MN                 "ST"
#define STOR_CODE               33



void removeCommentary(char* line);
/* Funcao para remover os comentarios da linha
   Procura na linha o caractere # e termina a string la (\0) */

int isInstrucao(char* word);
/* Verifica se a palavra é Instrução
   Uma palavra é uma intruçao se ela esta descrita em ---- INTRUCOES ---- */

int isDiretiva(char* word);
/* Verifica se a palavra é uma diretiva
   Uma palavra é uma diretiva se ela está descrita em ---- DIRETIVAS ----
   retorna o código usado pela diretiva*/

bool isValidRotulo(char* word);
/* Verifica a validade de um rótulo:
   Um rotulo é valido se seus caracteres obedecem:
   - [a,z], [A,Z], [0,9], _ */

int isValidNumber(char* number);
/* Verifica se é um numero valido:
   Contem [0,9],[A,F],[a,f] ou caractere x(hexadecimal) */

bool isValidSet(char* word);
/* Verifica se é um set válido */

#endif
