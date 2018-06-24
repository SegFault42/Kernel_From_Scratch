;; entry point to kernel load

bits 32						; compile in 32 bits

section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			; magic number (for multiboot)
	dd 0x00					; flags
	dd - (0x1BADB002 + 0x0) ; checksum magic + flag + checksum = should be 0x00

global start
extern kmain				; kmain defined in kernel_main.c

start:
	cli						; interupt flag
	mov esp, stack_space	; set stack pointer
	call kmain
	hlt						; halt CPU

section .bss
	resb 8192					;8KB for stack

stack_space:
