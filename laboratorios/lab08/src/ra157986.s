@ Henrique Noronha Facioli - MC404

@ Beginnig
.org 0x0
.section .iv,"a"

_start:

interrupt_vector:

    b RESET_HANDLER
.org 0x18
    b IRQ_HANDLER


.data 
CONTADOR: .word 0x0 

@ Vetor de interrupções
.org 0x100
.text


RESET_HANDLER:
    @ GPT definitions
    .set GPT_BASE,              0x53FA0000
    .set GPT_CR,                0x00
    .set GPT_PR,                0x04
    .set GPT_SR,                0x08
    .set GPT_IR,                0x0C
    .set GPT_OCR1,              0x10
    .set GPT_CR_VALUE,          0x00000041

    @ Zera o contador
    ldr r2, =CONTADOR  @lembre-se de declarar esse contador em uma secao de dados!
    mov r0,#0
    str r0,[r2]

    @Set interrupt table base address on coprocessor 15.
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

    @Send data do GPT hardware
    @ Load the first adress of GPT on r1
    ldr	r1, =GPT_BASE

    ldr r0, =GPT_CR_VALUE
    str	r0, [r1, #GPT_CR]

    @ Set zero the prescaler
    ldr r0, =0
    str r0, [r1, #GPT_PR]

    @ Value to compare
    ldr r0, =100
    str r0, [r1, #GPT_OCR1]

    @Enabling Output Compare Channel 1 interrupt
    ldr r0, =1
    str r0, [r1, #GPT_IR]


@ Código TZIC
SET_TZIC:
    @ Constantes para os enderecos do TZIC
    .set TZIC_BASE,             0x0FFFC000
    .set TZIC_INTCTRL,          0x0
    .set TZIC_INTSEC1,          0x84
    .set TZIC_ENSET1,           0x104
    .set TZIC_PRIOMASK,         0xC
    .set TZIC_PRIORITY9,        0x424

    @ Liga o controlador de interrupcoes
    @ R1 <= TZIC_BASE
    ldr	r1, =TZIC_BASE

    @ Configura interrupcao 39 do GPT como nao segura
    mov	r0, #(1 << 7)
    str	r0, [r1, #TZIC_INTSEC1]

    @ Habilita interrupcao 39 (GPT)
    @ reg1 bit 7 (gpt)
    mov	r0, #(1 << 7)
    str	r0, [r1, #TZIC_ENSET1]

    @ Configure interrupt39 priority as 1
    @ reg9, byte 3
    ldr r0, [r1, #TZIC_PRIORITY9]
    bic r0, r0, #0xFF000000
    mov r2, #1
    orr r0, r0, r2, lsl #24
    str r0, [r1, #TZIC_PRIORITY9]

    @ Configure PRIOMASK as 0
    eor r0, r0, r0
    str r0, [r1, #TZIC_PRIOMASK]

    @ Habilita o controlador de interrupcoes
    mov	r0, #1
    str	r0, [r1, #TZIC_INTCTRL]

    @instrucao msr - habilita interrupcoes
    msr  CPSR_c, #0x13       @ SUPERVISOR mode, IRQ/FIQ enabled

laco:
    b laco

IRQ_HANDLER:
    stmfd sp!, {r4-r11, lr}

    @ Increment the counter
    ldr r2, =CONTADOR
    ldr r0, [r2]
    add r0, r0, #0x1
    str r0, [r2]

    ldmfd sp!, {r4, r11, lr}

    @ Subtract 4 of lr
    sub lr, lr, #4
    movs pc, lr
