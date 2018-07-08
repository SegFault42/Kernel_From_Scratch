;; entry point to kernel load

bits 32						; compile in 32 bits

section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			; magic number (for multiboot)
	dd 0x00					; flags
	dd - (0x1BADB002 + 0x0) ; checksum magic + flag + checksum = should be 0x00

global start
global keyboard_handler
global read_port
global write_port
global load_idt

extern kmain				; kmain defined in kernel_main.c
extern keyboard_handler_main

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

;load_idt:
	;mov edx, [esp + 4]
	;lidt [edx]
	;sti
	;ret

;keyboard_handler:
	;call keyboard_handler_main
	;iretd

start:
	cli						; interupt flag
	mov esp, stack_space	; set stack pointer
	call kmain
	hlt						; halt CPU

section .bss
	resb 8192				;8KB for stack

stack_space:
