#include "bico.h"

void ronda();
void vira_parede();
void segue_parede();
void vira_90();
void moveFrente();
void viraNoventa();
void para();

int tempo;

void _start(){
    
    segue_parede();

    while(1);

}

void ronda(){
    //register_proximity_callback(

}

void segue_parede(){
    int i;
    int speed;
    int dist_av;
    short unsigned int dist[16];;

    set_motors_speed(20,20);
   
    read_sonar(3, &dist[3]);
    read_sonar(4, &dist[4]);
    
    /* Anda reto até encontrar uma parede */
    while(dist[3] > 750 && dist[4] > 750){
        read_sonar(3, &dist[3]);
        read_sonar(4, &dist[4]);
    }
    
    // Vira para direita, deixando o lado esquerdo do mesmo virado para parede
    set_motors_speed(0, 63);
    do{
        read_sonar(15, &dist[14]);
        read_sonar(0, &dist[0]);
        dist_av = dist[15]-dist[0];
    }while(dist_av == 0);
    
    register_proximity_callback(3, 200, vira_parede);
    
    do{
        read_sonar(1, &dist[1]);
        speed = dist[1]/47;
        if(speed > 30 || speed < 0){
            speed = 10;
        }
        set_motors_speed(speed, 10);
    }while(1);
}



// Funções auxiliares
void vira_parede(){
    int dist_av;
    short unsigned int dist1, dist15;
    set_motors_speed(0, 10);
    do{
        read_sonar(15, &dist15);
        read_sonar(1, &dist1);
        dist_av = dist15-dist1;
    }while(dist_av == 0);
    set_motors_speed(0,0);

}

void moveFrente(){
    set_motors_speed(20,20);
}
void viraNoventa(){
    set_motors_speed(0,30);
}

void para(){
    set_motors_speed(0,0);
}
