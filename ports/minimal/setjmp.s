
	.global	_setjmp
	.global	_longjmp

/*
	setjmp()

	This function is implemented using a trick that changes the value of
	pr (so that it points just after the call to setjmp()) within the
	longjmp() function, which lets the rts function perform the actual
	jump. This value is obtained from the save buffer.

	setjmp() returns 0 when called to set up the jump point and a non-zero
	value when invoked through a long jump. If 0 is provided as argument to
	longjmp(), 1 is returned instead.
*/
_setjmp:
	/* Getting some free space. */
	add	#64, r4

	/* Saving general-purpose registers. */
	mov.l	r15, @-r4
	mov.l	r14, @-r4
	mov.l	r13, @-r4
	mov.l	r12, @-r4
	mov.l	r11, @-r4
	mov.l	r10, @-r4
	mov.l	r9, @-r4
	mov.l	r8, @-r4

	/* Saving control and system registers. */
	stc.l	sr, @-r4
	stc.l	ssr, @-r4
	stc.l	spc, @-r4
	stc.l	gbr, @-r4
	stc.l	vbr, @-r4
	sts.l	mach, @-r4
	sts.l	macl, @-r4
	sts.l	pr, @-r4

	/* This function always return 0. The cases where setjmp() seems to
	return non-zero values, when a long jump has just been performed, are
	those when the longjmp() function returns. */
	rts
	mov	#0, r0



_longjmp:
	/* Restoring the system and control registers. Restoring pr is actually
	what performs the jump -- and makes the user program think that
	setjmp() has just returned. */
	lds.l	@r4+, pr
	lds.l	@r4+, macl
	lds.l	@r4+, mach
	ldc.l	@r4+, vbr
	ldc.l	@r4+, gbr
	ldc.l	@r4+, spc
	ldc.l	@r4+, ssr
	ldc.l	@r4+, sr

	/* Restoring the general-purpose registers. */
	mov.l	@r4+, r8
	mov.l	@r4+, r9
	mov.l	@r4+, r10
	mov.l	@r4+, r11
	mov.l	@r4+, r12
	mov.l	@r4+, r13
	mov.l	@r4+, r14
	mov.l	@r4+, r15

	/* Preventing return value from being 0 (must be at least 1). */
	tst	r5, r5
	movt	r0
	rts
	add	r5, r0
