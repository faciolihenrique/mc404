.global set_speed_motor
.global set_speed_motors
.global read_sonar
.global read_sonars

.align 4

read_sonar:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return


read_sonars:
    stmfd sp!, {r4-r11, lr}

    mov r5, #0
    mov r0, r4              @Change r0(first position of the vector) to r4

loop:
    ldr r3, [r4]              @ First position
    ldr r0, [r5, #1]!
    b read_sonar
    str ro, [r4, #4]!
    cmp r5, #18
    bge loop

    ldmfd sp!, {r4-r11, pc}



set_speed_motor:
    stmfd sp!, { r7, lr}    @ Save the callee-save registers

    cmp r1, #1              @compara para saber qual motor deve ser usado
    movge r7, #126
    movlt r7, #125

    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return

set_speed_motors:
    stmfd sp!, { r7, lr}    @ Save the callee-save registers

    mov r7, #124
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return
