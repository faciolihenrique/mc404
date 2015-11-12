@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@ Codigo de exemplo para controle basico de um robo.
@ Este codigo le os valores de 2 sonares frontais para decidir se o
@ robo deve parar ou seguir em frente.
@ 2 syscalls serao utilizadas para controlar o robo:
@   write_motors  (syscall de numero 124)
@                 Parametros:
@                       r0 : velocidade para o motor 0  (valor de 6 bits)
@                       r1 : velocidade para o motor 1  (valor de 6 bits)
@
@  read_sonar (syscall de numero 125)
@                 Parametros:
@                       r0 : identificador do sonar   (valor de 4 bits)
@                 Retorno:
@                       r0 : distancia capturada pelo sonar consultado (valor de 12 bits)
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


.text
.align 4
.globl _start

_start:                     @ main

    mov r0, #0              @ Carrega em r0 a velocidade do motor 0.
                            @ Lembre-se: apenas os 6 bits menos significativos
                            @ serao utilizados.
    mov r1, #0              @ Carrega em r1 a velocidade do motor 1.
    mov r7, #124            @ Identifica a syscall 124 (write_motors).
    svc 0x0                 @ Faz a chamada da syscall.

    ldr r6, =1700           @ r6 <- 1200 (Limiar para parar o robo)

loop:
    mov r0, #3              @ Define em r0 o identificador do sonar a ser consultado.
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    mov r5, r0              @ Armazena o retorno da syscall.

    mov r0, #4              @ Define em r0 o sonar.
    mov r7, #125
    svc 0x0

    cmp r0, r5              @ Compara o retorno do 3 com 4
    movls r2, r5            @ Se r5(3) <= r0(4), move r5 para r2
    movgt r2, r0            @ Se r0(4) <  r5(3), move r0 para r2

    cmp r2, r6              @ Compara com o limiar o valor do menor sensor
    bgt front               @ Se for maior que o limiar, move para frente
                            @ Se nao:
    cmp r5, r0              @ Compara o retorno do 4 (em r0) com 3 (em r5)
    bgt left                @ Se r5 > r0: Salta pra direita
    bls right               @ Se r5 < r0: vira para a esquerda

front:
    mov r0, #30             @ define uma velocidade para os 2 motores para andar para frente
    mov r1, #30
    mov r7, #124
    svc 0x0

    b loop                  @ Refaz toda a logica

left:                       @ Funcao que verifica o quanto deve continuar virando para esquerda
    mov r0, #4              @ Define em r0 o identificador do sonar a ser consultado.
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0

    cmp r0, #600              @ Faz uma verificacao com o limiar 18% menor que o original
    bls move_left           @ Se ainda estive perto o suficiente, vira para esquerda
    b loop

right:        @ Funcao que verifica o quanto deve continuar virando para direita
    mov r0, #3              @ Define em r0 o identificador do sonar a ser consultado.
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0

    cmp r0, #600           @ Faz uma verificacao do limiar 18% menor que o original
    bls move_right          @ Se ainda estive perto o suficiente, vira para direita
    b loop

move_left:
    mov r0, #30             @ define uma velocidade para os 2 motores para andar para frente
    mov r1, #0
    mov r7, #124
    svc 0x0

    b left

move_right:
    mov r0, #0             @ define uma velocidade para os 2 motores para andar para frente
    mov r1, #30
    mov r7, #124
    svc 0x0

    b right

end:                        @ Parar o robo
    mov r0, #0
    mov r1, #0
    mov r7, #124
    svc 0x0

    mov r7, #1              @ syscall exit
    svc 0x0
