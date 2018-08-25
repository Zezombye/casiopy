
	.export	_getkey
	.export	_system_menu

_getkey:
	sts.l	pr, @-r15
	mov.l	r12, @-r15
	mov.l	r13, @-r15

	; Getting some free space and storing stack addresses for later.
	add	#-4, r15
	mov	r15, r12	; column
	add	#-4, r15
	mov	r15, r13	; row
	add	#-4, r15
	mov	r15, r1		; keycode

	mov	r12, r4		; column
	mov	r13, r5		; row
	mov	#0, r6		; type_of_waiting
	mov	#0, r7		; timeout_period

	; Pushing the following arguments to the stack. (in order !)
	mov.l	r1, @-r15	; keycode
	mov	#1, r2
	mov.l	r2, @-r15	; menu

	; Calling subfunction.
	mov.l	syscall_table, r1
	mov.l	getkeywait, r0
	jsr	@r1
	nop

	; Retrieving keycode.
	mov.l	@r12, r0
	shll8	r0
	mov.l	@r13, r1
	or	r1, r0
	add	#20, r15

	; Returning.
	mov.l	@r15+, r13
	mov.l	@r15+, r12
	lds.l	@r15+, pr
	rts
	nop



_system_menu:
	sts.l	pr, @-r15
	add	#-4, r15

	; Putting the matrix code in the key buffer.

	mov	r15, r4
	mov.w	matrixcode_menu, r2
	mov.w	r2, @r4
	mov.l	syscall_table, r1
	mov.l	putmatrixcode, r0
	jsr	@r1
	nop

	; Calling getkeywait().

	mov	r15, r4
	add	#-4, r15
	mov	r15, r5
	add	#-4, r15
	mov	r15, r1

	mov	#2, r6
	mov	#0, r7
	mov.l	r1, @-r15
	mov	#0, r2
	mov.l	r2, @-r15

	mov.l	syscall_table, r1
	mov.l	getkeywait, r0
	jsr	@r1
	nop

	add	#20, r15
	lds.l	@r15+, pr
	rts
	nop


	.align	4

syscall_table:
	.data.l	h'80010070
getkeywait:
	.data.l	h'0247
getkey:
	.data.l	h'090f
putmatrixcode:
	.data.l	h'024f
putkeycode:
	.data.l	h'0910
keycode_menu:
	.data.l	d'30003
matrixcode_menu:
	.data.w	h'0308

	.end
