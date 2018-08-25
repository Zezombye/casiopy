    .global _GetKeyWait_syscall
_GetKeyWait_syscall:
    sts.l    pr, @-r15

    add    #-4, r15
    mov    r15, r4
    add    #-4, r15
    mov    r15, r5

    add    #-4, r15
    mov    r15, r1

    mov    #2, r6
    mov    #0, r7

    mov.l    r1, @-r15
    mov    #0, r2
    mov.l    r2, @-r15

    mov.l    syscall_table, r1
    mov.l    getkeywait, r0
    jsr    @r1
    nop

    add    #8, r15
    mov.l    @r15+, r1
    mov.l    @r15+, r0
    shll16    r1
    or    r1, r0

    add    #20, r15
    lds.l    @r15+, pr
    rts
    nop

    .align    4

syscall_table:
    .long    0x80010070
getkeywait:
    .long    0x0247
