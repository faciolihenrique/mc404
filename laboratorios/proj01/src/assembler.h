/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * assembler                       *
 * * * * * * * * * * * * * * * * * */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include "hash.h"
#include "analyze.h"
#include "memorymap.h"
#include "applicators.h"



void Assembler(FILE* fileIn, Base p, mMap MemoryMap, bool first);
/* Função que faz a primeira leitura do arquivo, verificando se é uma diretiva, rotulo ou instrução e aplicando,gerenci-
   ando de modo que permita no final termos um mapa de <rotulo, <endereco, tipo> > */

#endif
