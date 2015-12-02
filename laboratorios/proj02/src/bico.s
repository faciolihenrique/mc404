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

    mov r7, #18
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return


set_motors_speed:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #19
    svc 0x0

    ldmfd sp!, {r7, pc}     @ Restore the registers and return



read_sonar:
    stmfd sp!, {r7, r12, lr}    @ Save the callee-save registers
	
    mov r12, r1
    @ First parameter (r0) contain sonar_id and second (r1) the mem adress
    mov r7, #16            @ Identifica a syscall 16 (read_sonar).
    svc 0x0

    str r0 , [r12]

    ldmfd sp!, {r7, r12, pc}     @ Restore the registers and return


read_sonars:
    stmfd sp!, {r4-r11, lr}

    mov r5, r0                 
    ldr r0, =0x0
    ldr r6, =0x0
loop_read_sonars:
    mov r0, r6
    mov r7, #16            @ Identifica a syscall 16 (read_sonar).
    svc 0x0
    strh r0, [r5]
    add r5, r5, #0x04
    add r6, r6, #0x01
    cmp r6, #15
    blt loop_read_sonars

    ldmfd sp!, {r4-r11, pc}

register_proximity_callback:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #17
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return

add_alarm:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #22
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return

get_time:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #20
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return


set_time:
    stmfd sp!, {r7, lr}    @ Save the callee-save registers

    mov r7, #21
    svc 0x0

    ldmfd sp!, {r7, pc}      @ Restore the registers and return
