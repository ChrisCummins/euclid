;
; Set up the Global Descriptor Table (GDT)
;

global flush_gdt:function flush_gdt.end-flush_gdt

; This takes the first parameter passed to it (in esp+4), loads the value it
; points to into the GDT, then loads the segment selectors for the data and code
; segments. Notice that each segment descriptor is 8 bytes, and the kernel code
; descriptor is the second segment, so it's offset is 0x08.
flush_gdt:
	mov	eax,	[esp+4]
	lgdt	[eax]
	mov	ax,	0x10
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	mov	ss,	ax
	jmp	0x08:.flush
.flush:
	ret
.end:
