/**
 * @file multiboot.h
 *
 * Multiboot specification definitions. See the <a
 * href="http://www.gnu.org/software/grub/manual/multiboot/multiboot.html"
 * target="_blank">GNU Multiboot Specification</a> for more information.
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <elf.h>
#include <macros.h>
#include <types.h>

/**
 * The multiboot information structure.
 *
 * This defines the boot information structure, as specified in Section 3.3
 * (Boot information format) of the <a
 * href="http://www.gnu.org/software/grub/manual/multiboot/multiboot.html"
 * target="_blank">Multiboot Specification version 0.6.96</a>. To quote the
 * source material:
 *
 * > Upon entry to the operating system, the EBX register contains the physical
 * > address of a Multiboot information data structure, through which the boot
 * > loader communicates vital information to the operating system. The
 * > operating system can use or ignore any parts of the structure as it
 * > chooses; all information passed by the boot loader is advisory only.
 * >
 * > The Multiboot information structure and its related substructures may be
 * > placed anywhere in memory by the boot loader (with the exception of the
 * > memory reserved for the kernel and boot modules, of course). It is the
 * > operating system's responsibility to avoid overwriting this memory until it
 * > is done using it.
 *
 * The layout for the multiboot header is as follows:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
struct multiboot {
	/**
	 * Indicates the presence and validity of other fields in the Multiboot
	 * information structure. All as-yet-undefined bits must be set to zero
	 * by the boot loader. Any set bits that the operating system does not
	 * understand should be ignored. Thus, the ‘flags’ field also functions
	 * as a version indicator, allowing the Multiboot information structure
	 * to be expanded in the future without breaking anything.
	 */
	u32 flags;

	/**
	 * Indicates the amount of lower memory. Lower memory starts at address
	 * 0. The maximum possible value is 640 KiB. Only valid if bit 0 of @ref
	 * flags is set.
	 */
	u32 mem_lower;

	/**
	 * Indicates the amount of upper memory. Upper memory starts at address
	 * 1 MB. Only valid if bit 0 of @ref flags is set.
	 */
	u32 mem_upper;

	/**
	 * Indicates which BIOS disk device the boot loader loaded the OS image
	 * from. If the OS image was not loaded from a bios disk, then this
	 * field must not be present (bit 3 must be clear). Only valid if bit 1
	 * of @ref flags is set.
	 */
	u32 boot_device;

	/**
	 * Contains the physical address of the command line to be passed to the
	 * kernel. Only valid if bit 2 of @ref flags is set.
	 */
	u32 cmdline;

	/**
	 * Indicates to the kernel what boot modules were loaded along with the
	 * kernel image, and where they can be found. May be zero, indicating no
	 * boot modules were loaded, even if bit 1 of @ref flags is set. Only
	 * valid if bit 3 of @ref flags is set.
	 */
	u32 mods_count;

	/**
	 * Contains the physical address of the first module structure. Only
	 * valid if bit 3 of @ref flags is set.
	 */
	u32 mods_addr;

	/**
	 * Indicates the number of entries in the section header table for an
	 * ELF kernel. Only valid if bit 5 of @ref flags is set.
	 */
	u32 num;

	/**
	 * Indicates the size of each entry in the section header table for an
	 * ELF kernel. Only valid if bit 5 of @ref flags is set.
	 */
	u32 size;

	/**
	 * Indicates where the section header table for an ELF kernel can be
	 * found. Only valid if bit 5 of @ref flags is set.
	 */
	u32 addr;

	/**
	 * Contains the string table used as the index of names in the section
	 * header table for an ELF kernel. Only valid if bit 5 of @ref flags is
	 * set.
	 */
	u32 shndx;

	/**
	 * The total size of the buffer containing a memory map of the machine
	 * provided by the BIOS. Only valid if bit 6 of @ref flags is set.
	 */
	u32 mmap_length;

	/**
	 * The address of of the buffer containing a memory map of the machine
	 * provided by the BIOS. Only valid if bit 6 of @ref flags is set.
	 */
	u32 mmap_addr;

	/**
	 * The size of the drive strutures. Only valid if bit 7 of @ref flags is
	 * set.
	 */
	u32 drives_length;

	/**
	 * The address of the physical address of the first drive struture. Only
	 * valid if bit 7 of @ref flags is set.
	 */
	u32 drives_addr;

	/**
	 * Indicates the address of the ROM configuration table returned by the
	 * `GET CONFIGURATION` BIOS call. If the BIOS call fails, then the size
	 * of the table must be zero. Only valid if bit 8 of @ref flags is set.
	 */
	u32 config_table;

	/**
	 * The physical address of the name of a boot loader booting the
	 * kernel. The name is a normal C-style zero-terminated string. Only
	 * valid if bit 9 of @ref flags is set.
	 */
	u32 boot_loader_name;

	/**
	 * Contains the physical address of APM table.
	 *
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *             +----------------------+
	 *     0       | version              |
	 *     2       | cseg                 |
	 *     4       | offset               |
	 *     8       | cseg_16              |
	 *     10      | dseg                 |
	 *     12      | flags                |
	 *     14      | cseg_len             |
	 *     16      | cseg_16_len          |
	 *     18      | dseg_len             |
	 *             +----------------------+
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * Only valid if bit 10 of @ref flags is set.
	 */
	u32 apm_table;

	/**
	 * The physical address of VBE control information returned by the VBE
	 * Function `00h`. Only valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_control_info;

	/**
	 * The physical address of VBE mode information returned by the VBE
	 * Function `01h`. Only valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_mode_info;

	/**
	 * Indicates current video mode in the format specified in VBE 3.0. Only
	 * valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_mode;

	/**
	 * Contains the table of a protected mode interface defined in VBE
	 * 2.0+. If this information is not available, this contains zero. Only
	 * valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_interface_seg;

	/**
	 * Contains the table of a protected mode interface defined in VBE
	 * 2.0+. If this information is not available, this contains zero. Only
	 * valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_interface_off;

	/**
	 * Contains the table of a protected mode interface defined in VBE
	 * 2.0+. If this information is not available, this contains zero. Only
	 * valid if bit 11 of @ref flags is set.
	 */
	u32 vbe_interface_len;
}  __attribute__((packed));

/**
 * Return the elf structure containing the symbol information from a @ref
 * multiboot header.
 */
void elf_from_mb(struct multiboot *mb, struct elf *elf);

#endif /* _MULTIBOOT_H */
