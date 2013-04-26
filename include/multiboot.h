/*
 * Multiboot specification definitions. See GNU Multiboot Specification v0.6.96
 * for more information, available at:
 *
 * 	http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <macros.h>
#include <types.h>

/*
 * The boot information structure, as defined in Section 3.3 (Boot information
 * format) of the Multiboot Specification version 0.6.96. To quote the original
 * text:
 *
 *   Upon entry to the operating system, the EBX register contains the physical
 *   address of a Multiboot information data structure, through which the boot
 *   loader communicates vital information to the operating system. The
 *   operating system can use or ignore any parts of the structure as it
 *   chooses; all information passed by the boot loader is advisory only.
 *
 *   The Multiboot information structure and its related substructures may be
 *   placed anywhere in memory by the boot loader (with the exception of the
 *   memory reserved for the kernel and boot modules, of course). It is the
 *   operating system's responsibility to avoid overwriting this memory until it
 *   is done using it.
 *
 *              +-------------------+
 *      0       | flags             |    (required)
 *              +-------------------+
 *      4       | mem_lower         |    (present if flags[0] is set)
 *      8       | mem_upper         |    (present if flags[0] is set)
 *              +-------------------+
 *      12      | boot_device       |    (present if flags[1] is set)
 *              +-------------------+
 *      16      | cmdline           |    (present if flags[2] is set)
 *              +-------------------+
 *      20      | mods_count        |    (present if flags[3] is set)
 *      24      | mods_addr         |    (present if flags[3] is set)
 *              +-------------------+
 *      28 - 40 | syms              |    (present if flags[4] or
 *              |                   |                flags[5] is set)
 *              +-------------------+
 *      44      | mmap_length       |    (present if flags[6] is set)
 *      48      | mmap_addr         |    (present if flags[6] is set)
 *              +-------------------+
 *      52      | drives_length     |    (present if flags[7] is set)
 *      56      | drives_addr       |    (present if flags[7] is set)
 *              +-------------------+
 *      60      | config_table      |    (present if flags[8] is set)
 *              +-------------------+
 *      64      | boot_loader_name  |    (present if flags[9] is set)
 *              +-------------------+
 *      68      | apm_table         |    (present if flags[10] is set)
 *              +-------------------+
 *      72      | vbe_control_info  |    (present if flags[11] is set)
 *      76      | vbe_mode_info     |
 *      80      | vbe_mode          |
 *      82      | vbe_interface_seg |
 *      84      | vbe_interface_off |
 *      86      | vbe_interface_len |
 *              +-------------------+
 */

__diagnostic_disable(packed)

struct multiboot {
	u32 flags;
	u32 mem_lower;
	u32 mem_upper;
	u32 boot_device;
	u32 cmdline;
	u32 mods_count;
	u32 mods_addr;
	u32 num;
	u32 size;
	u32 addr;
	u32 shndx;
	u32 mmap_length;
	u32 mmap_addr;
	u32 drives_length;
	u32 drives_addr;
	u32 config_table;
	u32 boot_loader_name;
	u32 apm_table;
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u32 vbe_mode;
	u32 vbe_interface_seg;
	u32 vbe_interface_off;
	u32 vbe_interface_len;
}  __attribute__((packed));

__diagnostic_enable(packed)

/*
 * Flags for struct multiboot->flags.
 */
#define MULTIBOOT_FLAG_MEM       (1<<0)
#define MULTIBOOT_FLAG_DEVICE    (1<<1)
#define MULTIBOOT_FLAG_CMDLINE   (1<<2)
#define MULTIBOOT_FLAG_MODS      (1<<3)
#define MULTIBOOT_FLAG_AOUT      (1<<4)
#define MULTIBOOT_FLAG_ELF       (1<<5)
#define MULTIBOOT_FLAG_MMAP      (1<<6)
#define MULTIBOOT_FLAG_CONFIG    (1<<7)
#define MULTIBOOT_FLAG_LOADER    (1<<8)
#define MULTIBOOT_FLAG_APM       (1<<9)
#define MULTIBOOT_FLAG_VBE       (1<<10)

#endif /* _MULTIBOOT_H */
