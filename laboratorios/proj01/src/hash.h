/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * hash                            *
 * * * * * * * * * * * * * * * * * */

#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

#define MaxHash 256

/* tipo efetivo escondido */
typedef void * Base;

/* Tipo que armazena um rotulo ou um set */
typedef struct {
    char* nome;
    int value;
    char type;
    int number;
} Rotulo;

Base CriaBase();
/* Devolve apontador para uma base vazia com tabela inicializada */

bool InsereBase(Base p, Rotulo *a);
/* Insere o registro 'a' na base 'p' se não existe Rotulo
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */

bool RemoveBase(Base p, int number);
/* Remove da base 'p' o Rotulo com 'ra' dado; devolve 'true'
   se ele existiu e 'false' caso contrário. */

bool ConsultaBase(Base p, char* rotulo, Rotulo *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'.  'a' conterá
   os dados do Rotulo, se encontrado. */

int NumeroRegsBase(Base p);
/* Devolve o número de registros (Rotulos) na base 'p'. */

void ImprimeBase(Base p);
/* Imprime, os registros contidos na base 'p', um por linha.  A ordem
   de impressão segue a ordem das entradas da tabela, e para cada
   entrada, a ordem da lista ligada.  Cada linha começa com o índice
   correspondente na tabela de espalhamento. Deve ser usado o formato
   "(%3d) %06d %s\n". */

void LiberaBase(Base p);
/* Libera toda a memória utilizada pela base 'p', bem como
   todas as cadeias que guardam os nomes. */

#endif
