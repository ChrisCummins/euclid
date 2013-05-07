/*
 * ELF format data structures and procedures.
 */

#ifndef _ELF_H
#define _ELF_H

#include <macros.h>
#include <types.h>

#define ELF32_ST_TYPE(i) ((i)&0xf)

struct elf_section {
	u32 name;
	u32 type;
	u32 flags;
	u32 addr;
	u32 offset;
	u32 size;
	u32 link;
	u32 info;
	u32 addralign;
	u32 entsize;
} __attribute__((packed));

struct elf_symbol {
	u32 name;
	u32 value;
	u32 size;
	u8 info;
	u8 other;
	u16 shndx;
} __attribute__((packed));

struct elf {
	struct elf_symbol *symtab;
	u32 symtabsz;
	const char *strtab;
	u32 strtabsz;
};

/* Look up a symbol by address */
const char *symbol_from_elf(struct elf *elf, u32 addr);

#endif /* _ELF_H */
