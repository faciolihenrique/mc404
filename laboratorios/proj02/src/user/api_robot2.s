.global set_motor_speed
.global set_motors_speed
.global read_sonar
.global read_sonars
.global register_proximity_callback
.global add_alarm
.global get_time
.global set_time

.align 4
@ A id do motor é passada como primeiro parametro e o segundo é a velocidade
set_motor_speed:
    stmfd sp!, {r7,lr}    @ Save the callee-save registers

    movge r7, #18
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return


set_motors_speed:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #19
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return



read_sonar:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    @ First parameter (r0) contain sonar_id and second (r1) the mem adress
    mov r7, #16            @ Identifica a syscall 16 (read_sonar).
    svc 0x0

    str r0 , [r1]

    ldmfd sp!, {r7, pc}     @ Restore the registers and return


read_sonars:
    stmfd sp!, {r7, lr}

    mov r5, #0                @ Counter
loop_read_sonars:
    ldr r3, [r0]              @ First position
    ldr r0, [r5, #1]!
    b read_sonars
    str r0, [r0, #4]
    cmp r5, #16
    blt loop_read_sonars

    ldmfd sp!, {r7, pc}

register_proximity_callback:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #17
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return

.align 4
add_alarm:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    ldmfd sp!, {r7, pc}      @ Restore the registers and return

.align 4
get_time:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #20
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return


.align 4
set_time:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #21
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return
