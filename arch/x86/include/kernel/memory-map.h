/*
 * Memory map describing the contents of the computer's physical memory at the
 * moment that the BIOS jumps to bootloader code.
 */

#ifndef _MEMORY_MAP
#define _MEMORY_MAP

#include <macros.h>

/*
 * Low memory region
 */

/* Real Mode IVT (Interrupt Vector Table) - 1 KiB RAM */
#define REAL_MODE_IVT_MEMORY		0x00000000
#define REAL_MODE_IVT_MEMORY_END	0x000003FF
#define REAL_MODE_IVT_MEMORY_SIZE		\
	(REAL_MODE_IVT_END - REAL_MODE_IVT)
#define is_real_mode_ivt_memory_region(addr)	\
	__is_in_region(addr,			\
		       REAL_MODE_IVT_MEMORY,	\
		       REAL_MODE_IVT_MEMORY_END)

/* BDA (BIOS data area) - 256 bytes RAM */
#define BDA_MEMORY			0x00000400
#define BDA_MEMORY_END			0x000004FF
#define BDA_MEMORY_SIZE				\
	(BDA_END - BDA)
#define is_in_bda_memory_region(addr)		\
	__is_in_region(addr,			\
		       BDA_MEMORY,		\
		       BDA_MEMORY_END)

/*
 * ROM area
 */

/* VGA display memory - 128 KiB video RAM */
#define GRAPHICAL_MODE_MEMORY  		0x000A0000
#define GRAPHICAL_MODE_MEMORY_END	0x000B7FFF
#define GRAPHICAL_MODE_MEMORY_SIZE		\
	(GRAPHICAL_MODE_MEMORY_END - GRAPHICAL_MODE_MEMORY)
#define is_in_graphical_mode_memory_region(addr) \
	__is_in_region(addr,			\
		       GRAPHICAL_MODE_MEMORY,	\
		       GRAPHICAL_MODE_MEMORY_END)

#define COLOR_TEXT_MODE_MEMORY 		0x000B8000
#define COLOR_TEXT_MODE_MEMORY_END	0x000AFFFF
#define COLOR_TEXT_MODE_MEMORY_SIZE		\
	(COLOR_TEXT_MODE_MEMORY_END - COLOR_TEXT_MODE_MEMORY)
#define is_in_color_text_mode_memory_region(addr) \
	__is_in_region(addr,			\
		       COLOR_TEXT_MODE_MEMORY,	\
		       COLOR_TEXT_MODE_MEMORY_END)

#define MONO_TEXT_MODE_MEMORY  		0x000B0000
#define MONO_TEXT_MODE_MEMORY_END  	0x000BFFFF
#define MONO_TEXT_MODE_MEMORY_SIZE		\
	(MONO_TEXT_MODE_MEMORY_END - MONO_TEXT_MODE_MEMORY)
#define is_in_mono_text_mode_memory_region(addr) \
	__is_in_region(addr,			\
		       MONO_TEXT_MODE_MEMORY,	\
		       MONO_TEXT_MODE_MEMORY_END)

#define VGA_DISPLAY_MEMORY		GRAPHICAL_MODE_MEMORY
#define VGA_DISPLAY_MEMORY_END		MONO_TEXT_MODE_MEMORY_END
#define VGA_DISPLAY_MEMORY_SIZE			\
	(VGA_DISPLAY_MEMORY_END - VGA_DISPLAY_MEMORY)
#define is_in_vga_display_memory_region(addr)	\
	__is_in_region(addr)			\
		       VGA_DISPLAY_MEMORY,	\
		       VGA_DISPLAY_MEMORY_END)

/* Video BIOS - 32 KiB ROM */
#define VIDEO_BIOS_MEMORY		0x000C0000
#define VIDEO_BIOS_MEMORY_END		0x000C7FFF
#define VIDEO_BIOS_MEMORY_SIZE			\
	(VIDEO_BIOS_END - VIDEO_BIOS)
#define is_in_video_biods_memory_region(addr)	\
	__is_in_region(addr,			\
		       VIDEO_BIOS_MEMORY,	\
		       VIDEO_BIOS_MEMORY_END)

/* Mapped hardware & misc 160 KiB - ROMs */
#define MAPPED_HW_MEMORY		0x000C8000
#define MAPPED_HW_MEMORY_END		0x000EFFFF
#define MAPPED_HW_MEMORY_SIZE			\
	(MAPPED_HW_END - MAPPED_HW )
#define is_in_mapped_hw_memory_region(addr)	\
	__is_in_region(addr)			\
		       MAPPED_HW_MEMORY,	\
		       MAPPED_HW_MEMORY_END)

/* Motherboard BIOS - 64 KiB ROM */
#define MOTHERBOARD_BIOS_MEMORY		0x000F0000
#define MOTHERBOARD_BIOS_MEMORY_END	0x000FFFFF
#define MOTHERBOARD_BIOS_MEMORY_SIZE		\
	(MOTHERBOARD_BIOS_END - MOTHERBOARD_BIOS)
#define is_in_motherboard_bios_memory_region(addr) \
	__is_in_region(addr,			\
		       MOTHERBOARD_BIOS_MEMORY, \
		       MOTHERBOARD_BIOS_MEMORY_END)

/*
 * High memory region
 */
#define HIGH_MEMORY_START		0x00100000
#define is_in_high_memory_region(x)		\
	((u32)(x) >= HIGH_MEMORY_START)

#endif /* _MEMORY_MAP */
