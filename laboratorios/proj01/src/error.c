/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * error                           *
 * * * * * * * * * * * * * * * * * */

#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void callExit(int error_type,char* word){
    fprintf(stderr, "ERROR on line %d\n", line_counter);

    if(error_type == INVALID_DIRECTIVE_ARGUMENT)
        fprintf(stderr, "%s is not a valid argument on directive.\n", word);
    else if(error_type == INVALID_INSTRUCTION_ARGUMENT)
        fprintf(stderr,"%s is not a valid argument on instruction.\n", word);
    else if(error_type == NO_ARGUMENT_DIRECTIVE)
        fprintf(stderr, "One or more arguments is missing on directive %s.\n", word);
    else if(error_type == NO_ARGUMENT_INSTRUCTION)
        fprintf(stderr,"One argument is mission on instruction %s.\n", word);
    else if(error_type == MAP_LIMIT)
        fprintf(stderr, "Trying to acess an adress out of reach.\n");
    else if(error_type == RIGHT_WRITE)
        fprintf(stderr, "Invalid writing on memory due alignment.\n");
    else if(error_type == DUPLICATE_MEMORY)
        fprintf(stderr, "Trying to overwrite memory %s.\n", word);
    else if(error_type == LIMIT_NUMBER)
        fprintf(stderr, "%s is out of the limits.\n", word);
    else if(error_type == INVALID_ROTULE)
        fprintf(stderr, "%s has a not valid character on label.\n", word);
    else if(error_type == INVALID_SET)
        fprintf(stderr,"%s has a not valid character on set.\n", word);
    else if(error_type == EXCESS_ARGUMENT)
        fprintf(stderr, "%s is invalid on the line.\n", word);
    else if(error_type == INVALID_HEX_NUMBER)
        printf("%s is a not valid hexnumber.\n", word);

    exit(-1);
}
