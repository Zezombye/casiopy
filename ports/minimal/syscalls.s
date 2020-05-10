	.global _putKey
	.global _getOsVersion
	.global _ML_vram_adress
	

_putKey:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0x910
	
_ML_vram_adress:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0x135
	
_malloc_syscall:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0xACD
	
_free_syscall:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0xACC
	
_realloc_syscall:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0xE6D
	
_calloc_syscall:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0xE6B
	
_getOsVersion:
    mov.l    syscall_table, r2
    mov.l    1f, r0
    jmp      @r2
    nop
1:
    .long    0x2EE

syscall_table:
    .long    0x80010070
    