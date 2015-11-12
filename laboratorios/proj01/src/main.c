/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * main                            *
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "assembler.h"

#define SIZE_FILE 4096

int main(int argc, char *argv[]){
    Base rotulador;
    FILE* fileIn , *fileOut;
    mMap MemoryMap;

    /* LEITURA PARAMETROS ENTRADA */
    if(argc < 1){
        printf("Sem arquivo para abertura\n");
        return -1;
    }
    if(argc > 2){
        fileOut = fopen(argv[2], "w");

    }else{
        fileOut = NULL;
    }
    /* LEITURA DO ARQUIVO */
    fileIn = fopen( argv[1], "r");
    if(fileIn == NULL){
        printf("Erro ao tentar abrir o arquivo %s.\n", argv[1]);
        return 0;
    }

    /* ---- INÏCIO DO PROCESSAMENTO ---- */
    rotulador = CriaBase();

    /* Pré-processamento para organizacao de rotulos */
    MemoryMap = Initialize();
    Assembler(fileIn, rotulador, MemoryMap, true);
    freeMemoryMap(MemoryMap);

    rewind(fileIn);

    /* Montagem da mapa de memoria usando os rotulos */
    MemoryMap = Initialize();
    //RealAssembler(fileIn, rotulador, MemoryMap);
    Assembler(fileIn, rotulador, MemoryMap, false);
    printMemoryMap(MemoryMap, fileOut);
    freeMemoryMap(MemoryMap);

    LiberaBase(rotulador);

    fclose(fileIn);
    if(fileOut != NULL)
        fclose(fileOut);

    return 0;
}
