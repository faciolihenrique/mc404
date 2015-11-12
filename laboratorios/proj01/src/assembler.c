/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * assembler                       *
 * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "error.h"

void Assembler(FILE* fileIn, Base p, mMap MemoryMap, bool first){
    char line[SIZE_LINE];       // Armazena toda a linha
    char* word,* arg1,* arg2;   // armazena os tokens das linhas, os argumentos e o codigo mneumonico intrucao
    int diretiva, mn_code;      // armazena a diretiva e o codigo mneumonico da instrucao
    bool alreadyLabel;          // Previne que coloque mais de um rotulo na mesma linha

    /* Inicializa o contador de linhas usado nas mensagens de erro*/
    line_counter = 1;

    /* Percorre linha por linha */
    while( fgets(line , (SIZE_LINE - 1) , fileIn) != NULL ){
        alreadyLabel = false;
        /* Remove qualquer comentario existente da linha*/
        removeCommentary(line);

        /* Separa as palavras da linha */
        word = strtok(line, " '\t''\n'");
        while(word != NULL){

            /* ---- ROTULO ---- */
            if( (word[strlen(word) - 1] == ':') && isValidRotulo(word) && alreadyLabel == false ){
                /* Criacao do elemento da hash */
                Rotulo a;
                a.nome = malloc(strlen(word) + 1);
                strcpy(a.nome, word);
                if(MemoryMap->map[MemoryMap->position] != NULL && MemoryMap->map[MemoryMap->position]->lside){
                    a.type = 'r';
                }else{
                    a.type = 'l';
                }
                a.value = MemoryMap->position;
                /* Adiciona o rotulo no hash */
                InsereBase(p , &a);
                alreadyLabel = true;


            }
            /* ---- DIRETIVA ---- */
            else if( (diretiva = isDiretiva(word)) ){
                /* Caso seja diretiva, pode ter um ou dois argumentos*/
                arg1 = strtok(NULL, " ''\t''\n'\"");
                arg2 = strtok(NULL, " ''\t''\n'\"");
                /* Verificacao se existe arugmento a mair */
                char* garbage = strtok(NULL, " ''\t''\n'\"");
                if(garbage != NULL){
                    //Palavra a mais na leitura
                    callExit(EXCESS_ARGUMENT, garbage);
                }
                applyDirectiveOnMemory(diretiva, arg1, arg2, MemoryMap, p, first);
            }
            /* ---- INTRUÇÃO ---- */
            else if( (mn_code = isInstrucao(word)) != 0 ){
                /* Separa o argumento */
                arg1 = strtok(NULL, " ''\t''\n'\"");

                /* Caso tenha mais um argumento, deve ser gerado um erro*/
                char* garbage = strtok(NULL, " ''\t''\n'\"");
                if(garbage != NULL){
                    callExit(EXCESS_ARGUMENT, garbage);
                }

                /* Chama a função para aplicar a intrucao em MemoryMap */
                applyInstructionOnMemory(mn_code, arg1, MemoryMap, p, first);
            }
            /* Caso não seja nem rotulo, diretiva ou intrução não reconheceu */
            else{
                callExit(EXCESS_ARGUMENT, word);
            }

            /* Busca a próxima palavra */
            word = strtok(NULL, " ''\t''\n'\"");
        }

        line_counter++;
    }
}
