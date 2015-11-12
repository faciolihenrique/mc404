/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * memorymap                       *
 * * * * * * * * * * * * * * * * * */

#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <stdbool.h>
#include <stdio.h>

#define SIDES_SIZE 8

/* Tipo que armazena uma palavra de memoria do IAS*/
typedef struct line *Memoria;
typedef struct line{
    bool lside;
    bool rside;
    char left[SIDES_SIZE];
    char right[SIDES_SIZE];
} line;

/* Tipo que armazena 1024 palavras, ou seja, a memoria do IAS */
typedef struct memoryMap *mMap;
typedef struct memoryMap{
    int position;
    Memoria map[1024];
}memoryMap;



mMap Initialize();
/* Inicializa um mapa de memoria:
   - position = 0;
   - todas a Memorias apontam para NULL*/

void printMemoryMap(mMap memorymap, FILE* fileOut);
/* Faz a impressão do mapa de memoria na saida padrão ou no arquivo filOut*/

void freeMemoryMap(mMap p);
/* Desaloca o mapa de memoria */

#endif
