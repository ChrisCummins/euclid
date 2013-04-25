;
; Kernel entry location for euclid on x86 architecture.
;

	MBOOT_PAGE_ALIGN	equ 1<<0
	MBOOT_MEM_INFO		equ 1<<1

	MBOOT_HEADER_MAGIC	equ 0x1BADB002

	MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

	MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

bits 32				; All instructions should be 32 bits

global mboot			; Make 'mboot' globally accessible

extern code			; Start of the '.text' section
extern bss			; Start of the .bss section
extern end			; End of the last loadable section

mboot:
dd	MBOOT_HEADER_MAGIC	; GRUB will search for this value on each 4-byte
				; boundary in the first 8kb of the kernel file
dd	MBOOT_HEADER_FLAGS	; How GRUB should load your file/settings
dd	MBOOT_CHECKSUM		; To ensure that the above values are correct
dd	mboot			; Location of the mboot descriptor
dd	code			; Start of kernel .text section
dd	bss			; Start of kernel .bss section
dd	end			; End of kernel
dd	start			; Kernel entry point (initial EIP)

global start:function start.end-start ; Kernel entry point

extern k_main			; Defined in init/main.c

start:
	cli
	mov     esp,	stack	; Grab our SBP
	push	ebx		; Load multiboot header file
	mov     ebp, 	0
	call	k_main		; Kernel entry point
	jmp	$		; Enter an infinite loop
.end:

section .bss

resb 32768

stack:
