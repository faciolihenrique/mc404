	@ Global symbol
        .global dummy_routine1

	.align 4
dummy_routine1:
        stmfd sp!, {r4-r6, r10-r11, lr}	@ Save the callee-save registers
		                        @ and the return address.
	mov   r4,  #0
	mov   r5,  #1
	mov   r6,  #2
	mov   r10, #3
	mov   r11, #4
        ldmfd sp!, {r4-r6, r10-r11, pc} @ Restore the registers and return

dummy_routine2:
        stmfd sp!, {r11, lr}  @ Save the callee-save registers
		              @ and the return address.
	mov   r11, #4
        ldmfd sp!, {r11, pc}  @ Restore the registers and return


