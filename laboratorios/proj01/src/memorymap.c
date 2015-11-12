/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * memorymap                       *
 * * * * * * * * * * * * * * * * * */

#include "memorymap.h"
#include <stdlib.h>
#include <string.h>


mMap Initialize(){
    mMap MemoryMap = malloc(sizeof(memoryMap));

    MemoryMap->position = 0;
    for(int i = 0; i < 1024; i++){
        MemoryMap->map[i] = NULL;
    }
    return MemoryMap;
}

void printMemoryMap(mMap memorymap, FILE* fileOut){
    char* j, *linha;
    char l1[4], l2[5], l3[4], l4[5];

    linha = malloc(15*sizeof(char));
    for(int i = 0; i < 1024; i++){
        if( memorymap->map[i] != NULL ){
            if(memorymap->map[i]->rside){
                j = (memorymap->map[i])->right;
            }else{
                j = "00000\0";
            }
            sprintf(linha, "%5s%5s",(memorymap->map[i])->left, j);
            linha[ strlen(linha)+1] = '\0';
            sscanf(linha,"%2s%3s%2s%3s",l1,l2,l3,l4);

            if(fileOut == NULL){
                printf("%03X %s %s %s %s\n", i,l1,l2,l3,l4 );
            }else{
                fprintf(fileOut , "%03X %s %s %s %s\n", i,l1,l2,l3,l4);
            }
        }
    }
    free(linha);
}

void freeMemoryMap(mMap p){
    for(int i = 0; i < 1024; i++){
        if(p->map[i] != NULL){
            free(p->map[i]);
        }
    }

    free(p);
    return;
}
