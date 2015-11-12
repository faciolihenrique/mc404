/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * applies                         *
 * * * * * * * * * * * * * * * * * */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "applicators.h"
#include "error.h"

void applyDirectiveOnMemory(int directive, char* arg1, char* arg2, mMap memoryMap, Base p, bool pre){
    Rotulo a;                           // Rotulo usado para buscar rotulos e set
    long int argg1 = -1, argg2 = -1;    // Variaveis para converter o argumento em inteiro

    /* VERIFICAÇÃO DE ARGUMENTOS */
    /* ----------- -- ---------- */
    if(arg1 != NULL){
        if( (argg1 = isValidNumber(arg1)) != -1 ){

        }else if(pre){
            argg1 = 0;
        }else if( isValidRotulo(arg1) && ConsultaBase(p, arg1, &a) ){
            argg1 = a.value;
        }else if(directive != SET_CODE){
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg1);
        }
    }else{
        callExit(NO_ARGUMENT_DIRECTIVE, "");
    }

    if(arg2 != NULL){
        if( (argg2 = isValidNumber(arg2)) != -1 ){

        }else if(pre){
            argg2 = 0;
        }
        else if( isValidRotulo(arg2) && ConsultaBase(p, arg2, &a) ){
            argg2 = a.value;
        }
        else if(directive != SET_CODE){
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg2);
        }
    }

    /* APLICAÇÃO DAS DIRETIVAS */
    /* --------- --- --------- */

    /* ---- ALIGN ---- */
    if(directive == ALIGN_CODE){
        /*Verifica se possui dois argumento */
        if(arg2 != NULL)
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg2);
        if(argg1 > 1024 || argg1 < 1){
            callExit(LIMIT_NUMBER, arg1);
        }

        /* Recupera o ultimo local da memoria que foi utilizado para qualquer coisa completar com 0 o resto da linha */
        Memoria lastMemory = memoryMap->map[ memoryMap->position ];
        if(lastMemory != NULL){
            lastMemory->rside = false;
            (memoryMap->position)++;
        }
        while( (memoryMap->position % argg1) != 0 ){
            (memoryMap->position)++;
        }
        return;

    }

    /* ---- WORD ---- */
    else if(directive == WORD_CODE){
        char line[11], left[6], right[6];

        /*Verifica se possui dois argumento */
        if(arg2 != NULL)
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg2);
        /* Verifica se na proxima inserção terá problema do limite de memoria do IAS */
        if((memoryMap->position) > 1023)
            callExit(MAP_LIMIT, "");
        /* Verifica se quando a diretiva foi chamada o mapa de memoria não estava na direita */
        if(memoryMap->map[memoryMap->position] != NULL && !memoryMap->map[memoryMap->position]->rside){
            callExit(RIGHT_WRITE, "");
        }
        /* Verifica se o argumento respeita os limites */
        if(argg1 < 0 || (unsigned long long) argg1 > (unsigned long long) NUMBER_LIMIT){
            callExit(LIMIT_NUMBER, arg1);
        }

        /* Escreve a a palavra em uma string maior e depois divide ela em duas */
        sprintf(line, "%010X", (int)argg1);
        sscanf(line, "%5s%5s", left, right);
        /* Aloca uma linha no mapa de memoria */
        Memoria lastMemory = malloc( sizeof(line) );
        /* Copia as informações da esquerda e direita para o mapa de memoria */
        strcpy(lastMemory->left , left);
        lastMemory->lside = true;
        strcpy(lastMemory->right , right);
        lastMemory->rside = true;
        /* Faz a ultima posicao do vetor apontar para essa linha da memoria e incrementa o contador */
        memoryMap->map[memoryMap->position] = lastMemory;
        (memoryMap->position)++;
        return;
    }

    /* ---- ORG ---- */
    else if(directive == ORG_CODE){
        /*Verifica se possui dois argumento */
        if(arg2 != NULL)
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg2);
        /*Verifica se o argumento está dentro do limite */
        if(argg1 > 1024 || argg1 < 0){
            callExit(LIMIT_NUMBER, arg1);
        }
        /* Verifica se a posicao desejada pelo .org ja foi usada, se não muda o contador */
        if(memoryMap->map[argg1] == NULL)
            memoryMap->position = argg1;
        else{
            callExit(DUPLICATE_MEMORY, arg1);
        }
        return;
    }

    /* ---- WFILL ---- */
    else if(directive == WFILL_CODE){
        /* Lembrando que o argg1 é o numero de repetições e o argg2 é o valor */
        char line[11], left[6], right[6];

        /*Verifica se possui dois argumento */
        if(arg2 == NULL)
            callExit(NO_ARGUMENT_DIRECTIVE, arg2);
        /*Verifica a validade dos argumentos */
        if(argg1 > 1024 || argg1 < 1){
            callExit(LIMIT_NUMBER, arg1);
        }
        if((long long)argg2 > (unsigned long long) NUMBER_LIMIT){
            callExit(LIMIT_NUMBER, arg2);
        }
        /* Verifica se há o estouro de memória */
        if(memoryMap->position + argg1 > 1024)
            callExit(MAP_LIMIT, "");
        /* Verifica se quando a diretiva foi chamada o mapa de memoria não estava na direita */
        if(memoryMap->map[memoryMap->position] != NULL && !memoryMap->map[memoryMap->position]->rside){
            callExit(RIGHT_WRITE, "");
        }


        for(int i = 0; i < argg1; i++){
            /* Escreve a a palavra em uma string maior e depois divide ela em duas */
            sprintf(line, "%010X",(int) argg2);
            sscanf(line, "%5s%5s", left, right);

            /* Aloca uma linha no mapa de memoria */
            Memoria line = malloc(sizeof(line) );
            /* Copia as informações da esquerda e direita para o mapa de memoria */
            strcpy(line->left, left);
            line->lside = true;
            strcpy(line->right, right);
            line->rside = true;
            /* Faz a ultima posicao do vetor apontar para essa linha da memoria e incrementa o contador */
            memoryMap->map[memoryMap->position] = line;
            (memoryMap->position)++;
        }
        return;
    }

    /* ---- SET ---- */
    else if(directive == SET_CODE && !pre){
        /*Verifica se possui dois argumento */
        if(arg2 == NULL)
            callExit(NO_ARGUMENT_DIRECTIVE, arg2);
        /*Verifica a validade do argumento */
        if(argg2 < 0 || (unsigned long long) argg2 > (unsigned long long) NUMBER_LIMIT){
            callExit(LIMIT_NUMBER, arg2);
        }
        /* Verifica a validade do nome */
        if( isValidSet(arg1) ){
            /*Cria um novo rotulo na hash*/
            Rotulo a;
            a.nome = malloc( strlen(arg1) + 1);
            strcpy(a.nome, arg1);
            a.type = 's';
            a.value = argg2;

            InsereBase(p , &a);
        }
        else{
            callExit(INVALID_DIRECTIVE_ARGUMENT, arg1);
        }
        return;
    }

    return;
}


void applyInstructionOnMemory(int instruction, char* arg1, mMap memoryMap, Base p, bool pre){
    char side[6];
    unsigned int arg;

    /* Verificação do argumento passado */
    if(arg1 == NULL){
        if( instruction != LSH_CODE && instruction != RSH_CODE ){
            arg = 0;
            callExit(NO_ARGUMENT_INSTRUCTION, "");
        }
        else{
            arg = 0;
        }
    }
    else{
        /* Pode ser um rotulo ou um .set, e dai tera que verificar se é direita ou esquerda */
        /* Se estiver no pre processamento, não importa checar no hash... */
        /* Agora, se não for pre, deve procurar no hash o termo e verificar seu valor caso ache*/
        if( (arg = isValidNumber(arg1)) == -1){
            Rotulo a;

            if(pre){
                arg = 0;
            }else if( ConsultaBase(p, arg1, &a) ){
                if(a.type == 's'){
                    callExit(INVALID_INSTRUCTION_ARGUMENT, arg1);
                }
                arg = a.value;
                if(a.type == 'r'){
                    if( instruction == JUMP_L_CODE ){
                        instruction = JUMP_R_CODE;
                    }
                    else if( instruction ==  JUMPP_L_CODE ){
                        instruction = JUMPP_R_CODE;
                    }
                    else if( instruction == STOR_M_L_CODE ){
                        instruction = STOR_M_R_CODE;
                    }
                }
            }
            /* Se nao era um numero valido e nem estava no hash, o argumento é invalido*/
            else{
                callExit(INVALID_INSTRUCTION_ARGUMENT, arg1);
            }

        }
        /* Verifica se o argumento está dentro do limite */
        if(arg > 1024 || (int) arg < 0){
            callExit(LIMIT_NUMBER, arg1);
        }
    }


    /* Monta a linha no estilo XXYYY sendo XX o codigo da intrucao e YYY o endereco */
    sprintf(side, "%02X%03X", instruction, arg);

    /* Faz a copia da metade da linha para direita */
    if(memoryMap->map[memoryMap->position] != NULL && memoryMap->map[memoryMap->position]->lside){
        strcpy(memoryMap->map[memoryMap->position]->right, side);
        memoryMap->map[memoryMap->position]->rside = true;
        memoryMap->position++;
    }
    /* Faz a copia da metade da linha para esquerda */
    else{
        Memoria line = malloc(sizeof(line));
        strcpy(line->left, side);
        line->lside = true;
        line->rside = false;

        memoryMap->map[memoryMap->position] = line;
    }
}
