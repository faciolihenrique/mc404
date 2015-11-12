/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * error                           *
 * * * * * * * * * * * * * * * * * */

#ifndef ERROR_H
#define ERROR_H

#define INVALID_INSTRUCTION_ARGUMENT         0
#define INVALID_DIRECTIVE_ARGUMENT           1
#define NO_ARGUMENT_DIRECTIVE                2
#define NO_ARGUMENT_INSTRUCTION              3
#define MAP_LIMIT                            4
#define RIGHT_WRITE                          5
#define DUPLICATE_MEMORY                     6
#define LIMIT_NUMBER                         7
#define INVALID_ROTULE                       8
#define INVALID_SET                          9
#define EXCESS_ARGUMENT                      10
#define INVALID_HEX_NUMBER                   11

/* :( - Variavel global que controla a linha do arquivo*/
unsigned int line_counter;


void callExit(int error_type, char* word);
/* Chamada de funcao que apresenta o erro */

#endif
