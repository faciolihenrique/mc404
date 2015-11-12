	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	_start
	.type	_start, %function
_start:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #64
.L5:
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	mov	r2, r3
	ldr	r3, .L7
	cmp	r2, r3
	bhi	.L2
	mov	r0, #30
	mov	r1, #0
	bl	set_speed_motors
	b	.L5
.L2:
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	mov	r2, r3
	ldr	r3, .L7
	cmp	r2, r3
	bhi	.L4
	mov	r0, #0
	mov	r1, #30
	bl	set_speed_motors
	b	.L5
.L4:
	mov	r0, #30
	mov	r1, #30
	bl	set_speed_motors
	b	.L5
.L8:
	.align	2
.L7:
	.word	1199
	.size	_start, .-_start
	.align	2
	.global	delay
	.type	delay, %function
delay:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L10
.L11:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L10:
	ldr	r2, [fp, #-8]
	ldr	r3, .L13
	cmp	r2, r3
	ble	.L11
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L14:
	.align	2
.L13:
	.word	9999
	.size	delay, .-delay
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
