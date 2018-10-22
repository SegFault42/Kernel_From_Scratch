;; entry point to kernel load

bits 32						; compile in 32 bits

section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			; magic number (for multiboot)
	dd 0x00					; flags
	dd - (0x1BADB002 + 0x0) ; checksum magic + flag + checksum = should be 0x00

global start
global read_port
global write_port
global gdt_flush

extern kmain				; kmain defined in kernel_main.c

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

start:
	cli						; interupt flag
	mov esp, stack_space	; set stack pointer
	call kmain
	hlt						; halt CPU

gdt_flush:
	mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
	lgdt [eax]        ; Load the new GDT pointer

	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax        ; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!

.flush:
	ret

section .bss
	resb 8 * 1024				;8KB for stack

stack_space:
