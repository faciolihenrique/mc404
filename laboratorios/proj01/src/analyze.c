/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * analyze                         *
 * * * * * * * * * * * * * * * * * */

#include "analyze.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

void removeCommentary(char* line){
    int i;
    int size = strlen(line);
    for(i = 0; i < size; i++){
        if(line[i] == '#'){
            line[i] = '\n';
            line[i+1] = '\0';
        }
    }
}

int isInstrucao(char* word){
    if(! strcmp( word, LOAD_MN))
        return LOAD_CODE;
    if(! strcmp( word, LOAD_NEG_MN))
        return LOAD_NEG_CODE;
    if(! strcmp( word, LOAD_MOD_MN))
        return LOAD_MOD_CODE;
    if(! strcmp( word, ADD_MN))
        return ADD_CODE;
    if(! strcmp( word, SUB_MN))
        return SUB_CODE;
    if(! strcmp( word, ADD_MOD_MN))
        return ADD_MOD_CODE;
    if(! strcmp( word, SUB_MOD_MN))
        return SUB_MOD_CODE;
    if(! strcmp( word, LOAD_MQ_MX_MN))
        return LOAD_MQ_MX_CODE;
    if(! strcmp( word, LOAD_MQ_MN))
        return LOAD_MQ_CODE;
    if(! strcmp( word, MUL_MN))
        return MUL_CODE;
    if(! strcmp( word, DIV_MN))
        return DIV_CODE;
    if(! strcmp( word, JUMP_MN))
        return JUMP_L_CODE;
    if(! strcmp( word, JUMPP_MN))
        return JUMPP_L_CODE;
    if(! strcmp( word, STOR_M_MN))
        return STOR_M_L_CODE;
    if(! strcmp( word, LSH_MN))
        return LSH_CODE;
    if(! strcmp( word, RSH_MN))
        return RSH_CODE;
    if(! strcmp( word, STOR_MN))
        return STOR_CODE;

    return 0;
}

int isDiretiva(char* word){
    if(! strcmp( word, ALIGN_DIR))
        return ALIGN_CODE;
    if(! strcmp( word, WORD_DIR))
        return WORD_CODE;
    if(! strcmp( word, SET_DIR))
        return SET_CODE;
    if(! strcmp( word, ORG_DIR))
        return ORG_CODE;
    if(! strcmp( word, WFILL_DIR))
        return WFILL_CODE;
    return 0;
}

bool isValidRotulo(char* word){
    int i, size;
    size = strlen(word);
    if(word[0] >= '0' && word[0] <= '9')
        return false;
    for(i =0; i < size-1; i++){
        if(word[i] )

        if(!( (word[i] >= 'A' && word[i] <= 'Z') ||
              (word[i] >= 'a' && word[i] <= 'z') ||
              (word[i] >= '0' && word[i] <= '9') ||
               word[i] == '_'
           )){
               callExit(INVALID_ROTULE, word);
               return false;
           }

    }
    if(word[i] == ':'){
        word[i] = '\0';
    }
    return true;
}

bool isValidSet(char* word){
    int i, size;
    size = strlen(word);
    for(i =0; i < size-1; i++){

        if(!( (word[i] >= 'A' && word[i] <= 'Z') ||
              (word[i] >= 'a' && word[i] <= 'z') ||
              (word[i] >= '0' && word[i] <= '9') ||
               word[i] == '_'
           )){
               callExit(INVALID_SET, word);
               return false;
           }
    }
    return true;
}

int isValidNumber(char* number){
    int size = strlen(number);

    if(number[0] == '0' && (number[1] == 'x' || number[1] == 'X')){
        if(size != 12){
           callExit(INVALID_HEX_NUMBER, number);
        }
    }

    for(int i = 0; i < size; i++){
        if( ( (number[i] >= '0' && number[i] <= '9')  ||
              (number[i] >= 'a' && number[i] <= 'f')  ||
              (number[i] >= 'A' && number[i] <= 'F')  ||
              (i == 1 && (number[i] == 'x') ))
        ){}
        else{
            return -1;
        }
    }

    return strtoll(number, NULL, 0);
}
