/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * applies                         *
 * * * * * * * * * * * * * * * * * */

#ifndef APPLY_H
#define APPLY_H

#include "hash.h"
#include "memorymap.h"
#include "analyze.h"

/* Os cógidos das diretivas e das intruções estão definidas em analyze.h */


void applyDirectiveOnMemory(int directive, char* arg1, char* arg2, mMap memoryMap, Base p, bool pre);
/* Função que dada uma diretiva (directive) e seus argumentos, verifica se ela é uma diretiva válida, e a coloca no mapa
   de memoria. As diretivas podem ser:
  - ALIGN_CODE: Recebe apenas um parametro e dada um número procura a posicao de memoria próxima multipla desse numero
  - WORD_CODE: Recebe apenas um parametro e escreve na posicao do endereco do mapa de memoria esse parametro
  - ORG_CODE: Faz um salto para a posicao desejada. Não pode já ter sido usada
  - WFILL_CODE: Recebe dois parametros e cria um vetor de tam arg1 e valor arg2
  - SET_CODE: Recebe dois parametros e cria um código para determinado valor. É usado na mesma hash que o rotulo */

void applyInstructionOnMemory(int instruction,char* arg1, mMap memoryMap, Base p, bool pre);
/* Função que dada uma instrucao e seu argumento verifica a validade do argumento e escreve a diretiva no mapa de
   memoria. Lembrando que apenas LSH E RSH não recebem parametro e as funcoes que possuem direita e esquerda só podem ser
   acessadas com rotulos */

#endif
