/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * hash                            *
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <ctype.h>



/* DECLARAÇÕES DE TIPOS */
/* -------------------- */

typedef struct RegLista *Lista;
typedef struct RegLista {
    Rotulo rotulo;
    Lista prox;
} RegLista;

typedef struct RegBase *ImplBase;
typedef struct RegBase {
    int numregs;
    Lista tabela[MaxHash];
} RegBase;

/* FUNÇÃO DE ESPALHAMENTO */
/* ---------------------- */

int CalculaNumero(char* nome){
    int i, size, number = 0;
    size = strlen(nome);
    for(i = 0; i < size; i++){
        if(nome[i] != ':')
            //nome[i] = toupper(nome[i]); REMOVE THIS COMMENT LINE TO CASE INSENSITVE
            number =  (nome[i]*i) + number;
    }
    return number;
}

int Espalha(int k) {
  return (k%MaxHash);
} /* Espalha */

/* FUNÇÕES AUXILIARES */
/* ------------------ */

/*Algoritimo para liberar uma lista ligada*/
void libera_lista(Lista a){
    Lista aux1 = a->prox, aux2;
    /*Caminha com duas variaveis uma seguida da outra, liberando a segunda
      e avançando, até que se chegue ao nó cabeça*/
    /*Como o nome é alocado dinamicamente, precisa libera-lo*/
    while(aux1->rotulo.number != -1){
        aux2 = aux1->prox;
        free(aux1->rotulo.nome);
        free(aux1);
        aux1 = aux2;
    }

    free(a);
}


/* FUNÇÕES DA INTERFACE */
/* -------------------- */
Base CriaBase(){
    /*Funcao que cria uma base, inicializando o vetor de lista circular com nós
    cabeças com o valor -1 nelas*/
    ImplBase aux = malloc(sizeof(RegBase));
    aux->numregs = 0;

    /*Inicializa o vetor de lista circular com o no cabeça*/
    for(int i = 0; i < MaxHash; i++){
        aux->tabela[i] = malloc(sizeof(RegLista));
        aux->tabela[i]->rotulo.number = -1;
        aux->tabela[i]->prox = aux->tabela[i];
    }

    return (Base) aux;
}

bool InsereBase(Base p, Rotulo *a){
    /*Funcao que insere o rotulo a na base p*/

    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o rotulo*/

    a->number = CalculaNumero( a->nome );
    int posicao = Espalha(a->number);
    Lista no, previous, novo_no;
    /*Faz com que previous comece no nó cabeça e nó no seguinte a ele*/
    no = z->tabela[posicao]->prox;
    previous = z->tabela[posicao];

    /*Procunumber o lugar do rotulo dentro da lista, avançando com duas variaveis,
      uma seguida da outra*/
    while( (a->number > no->rotulo.number) && (no->rotulo.number != -1)){
        previous = no;
        no = no->prox;
    }

    /*Caso ja exista o rotulo*/
    if(a->number == no->rotulo.number){
        return false;
    }

    /*Caso seja uma insercao no meio da lista*/
    novo_no = malloc(sizeof(RegLista));
    novo_no->rotulo = *a;
    novo_no->prox = previous->prox;
    previous->prox = novo_no;

    /*Aumenta o numero de registros dentro da base*/
    z->numregs++;
    return true;
}


bool RemoveBase(Base p, int number){
    /*Funcao que remove o rotulo com o ra da lista*/

    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o rotulo*/
    int posicao = Espalha(number);
    Lista no , previous;
    /*Assim como no insere*/
    no = z->tabela[posicao]->prox;
    previous = z->tabela[posicao];

    /*Procura o nó com o usuario desejado*/
    while((no->rotulo.number != -1) && (number > no->rotulo.number)){
        previous = no;
        no = no->prox;
    }

    /*Se encontrou o rotulo, o anterior dele aponta para o posterior dele e ele é
    liberado*/
    if(no->rotulo.number != -1 && number == no->rotulo.number){
        previous->prox = no->prox;
        free(no->rotulo.nome);
        free(no);

        z->numregs--;
        return true;
    }

    /*Se nao encontrou, o rotulo nao existe, e retorna false*/
    return false;
}

bool ConsultaBase(Base p, char* stringdorotulo, Rotulo *a){
    /*Casting*/
    ImplBase z = (ImplBase) p;
    Lista auxiliar;

    int number = CalculaNumero( stringdorotulo );

    /* Posicao do vetor de lista que deve ser colocado o rotulo */
    int posicao = Espalha(number);
    auxiliar = z->tabela[posicao]->prox;

    while( auxiliar->rotulo.number != -1 ){
        if( auxiliar->rotulo.number == number ){
            *a = auxiliar->rotulo;
            return true;
        }
        auxiliar = auxiliar->prox;
    }

    return false;
}

int NumeroRegsBase(Base p){
    /*Casting*/
    ImplBase z = (ImplBase) p;

    return z->numregs;
}

void ImprimeBase(Base p){
    /*Funcao que imprime todos os registros da base*/
    /*Casting*/
    ImplBase z = (ImplBase) p;
    Lista no;

    printf("\nImprime base: %d registro(s):\n", NumeroRegsBase(p) );
    /*Percorre o vetor de lista, imprimindo a lista*/
    for(int i = 0; i < MaxHash; i++){
        no = (z->tabela[i])->prox;
        while(no->rotulo.number != -1){
            printf("(%3d) %06d %s %03x %c\n",i, no->rotulo.number, no->rotulo.nome, no->rotulo.value, no->rotulo.type);
            no = no->prox;
        }
    }
    printf("\n");

}

void LiberaBase(Base p){
    /*Casting*/
    ImplBase z = (ImplBase) p;

    for(int i = 0; i < MaxHash; i++){
        libera_lista(z->tabela[i]);
    }

    free(p);
}
