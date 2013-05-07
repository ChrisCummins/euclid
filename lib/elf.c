#include <elf.h>

#include <kernel/panic.h>

#include <stddef.h>
#include <stdio.h>

const char *symbol_from_elf(struct elf *elf, u32 address) {
	unsigned int i;

	for (i = 0; i < (elf->symtabsz / sizeof(struct elf_symbol)); i++) {
		if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2)
			continue;

		if ((address >= elf->symtab[i].value) &&
		    (address < (elf->symtab[i].value + elf->symtab[i].size))) {
			return (const char *)((u32)elf->strtab
					      + elf->symtab[i].name);
		}
	}

	printf("Unable to find address %x in elf\n");
	return NULL;
}
