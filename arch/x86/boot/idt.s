;
; Setup the Interrupt Descriptor Table (IDT).
;

global flush_idt:function flush_idt.end-flush_idt

flush_idt:
	mov	eax,	[esp+4]
	lidt	[eax]
	ret
.end:

; This macro creates a stub for an ISR which does NOT pass it's own error code
; (adds a dummy errcode byte).
%macro ISR_NOERRCODE 1
global isr%1
	isr%1:
	cli                         ; Disable interrupts firstly.
	push 0                      ; Push a dummy error code.
	push %1                     ; Push the interrupt number.
	jmp isr_common_stub         ; Go to our common handler code.
%endmacro

; This macro creates a stub for an ISR which DOES pass it's own error code.
%macro ISR_ERRCODE 1
global isr%1
	isr%1:
	cli                         ; Disable interrupts.
	push %1                     ; Push the interrupt number
	jmp isr_common_stub
%endmacro

; Generate our ISRs
	ISR_NOERRCODE 0
	ISR_NOERRCODE 1
	ISR_NOERRCODE 2
	ISR_NOERRCODE 3
	ISR_NOERRCODE 4
	ISR_NOERRCODE 5
	ISR_NOERRCODE 6
	ISR_NOERRCODE 7
	ISR_ERRCODE 8
	ISR_NOERRCODE 9
	ISR_ERRCODE 10
	ISR_ERRCODE 11
	ISR_ERRCODE 12
	ISR_ERRCODE 13
	ISR_ERRCODE 14
	ISR_NOERRCODE 15
	ISR_NOERRCODE 16
	ISR_NOERRCODE 17
	ISR_NOERRCODE 18
	ISR_NOERRCODE 19
	ISR_NOERRCODE 20
	ISR_NOERRCODE 21
	ISR_NOERRCODE 22
	ISR_NOERRCODE 23
	ISR_NOERRCODE 24
	ISR_NOERRCODE 25
	ISR_NOERRCODE 26
	ISR_NOERRCODE 27
	ISR_NOERRCODE 28
	ISR_NOERRCODE 29
	ISR_NOERRCODE 30
	ISR_NOERRCODE 31
	ISR_NOERRCODE 255

extern disaptch_idt_handler

global isr_common_stub:function isr_common_stub.end-isr_common_stub

; This is our common ISR stub. It saves the processor state, sets up for kernel
; mode segments, calls the C-level fault handler, and finally restores the stack
; frame.
isr_common_stub:
	pusha			; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov	ax,	ds	; Lower 16-bits of eax = ds.
	push 	eax		; Save the data segment descriptor

	mov	ax,	0x10	; Load the kernel data segment descriptor
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	mov	ss,	ax

	push	esp		; Push a pointer to the current top of stack
	call 	disaptch_idt_handler
	add	esp,	4	; Remove the r param

	pop	ebx		; Reload the original data segment descriptor
	mov	ds,	bx
	mov	es,	bx
	mov	fs,	bx
	mov	gs,	bx
	mov	ss,	bx

	popa			; Pops edi,esi,ebp...
	add	esp,	8	; Cleans up the pushed error code and pushed ISR number
	iret			; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
.end:

; This macro creates a stub for an IRQ - the first parameter is the IRQ number,
; the second is the ISR number it is remapped to.
%macro IRQ 2
global irq%1
	irq%1:
	cli
	push	byte	0
	push	byte	%2
	jmp irq_common_stub
%endmacro

	IRQ   0,    32
	IRQ   1,    33
	IRQ   2,    34
	IRQ   3,    35
	IRQ   4,    36
	IRQ   5,    37
	IRQ   6,    38
	IRQ   7,    39
	IRQ   8,    40
	IRQ   9,    41
	IRQ  10,    42
	IRQ  11,    43
	IRQ  12,    44
	IRQ  13,    45
	IRQ  14,    46
	IRQ  15,    47

extern disaptch_irq_handler

global irq_common_stub:function irq_common_stub.end-irq_common_stub

; This is our common IRQ stub. It saves the processor state, sets up for kernel
; mode segments, calls the C-level fault handler, and finally restores the stack
; frame.
irq_common_stub:
	pusha			; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov	ax,	ds	; Lower 16-bits of eax = ds.
	push	eax		; Save the data segment descriptor

	mov	ax,	0x10	; Load the kernel data segment descriptor
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	mov	ss,	ax

	push	esp		; Push a pointer to the current top of stack
	call disaptch_irq_handler
	add	esp,	4	; Remove the r parameter.

	pop	ebx		; Reload the original data segment descriptor
	mov	ds,	bx
	mov	es,	bx
	mov	fs,	bx
	mov	gs,	bx
	mov	ss,	bx

	popa			; Pops edi,esi,ebp...
	add	esp,	8	; Cleans up the pushed error code and pushed ISR number
	iret			; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
.end: