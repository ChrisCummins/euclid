#include <multiboot.h>

#include <string.h>
#include <macros.h>
#include <stdio.h>

void elf_from_mb(struct multiboot *mb, struct elf *elf)
{
	struct elf_section *section;
	u32 shstrtab;
	unsigned int i;

	return_if_fail(mb != NULL);
	return_if_fail(elf != NULL);

	section = (struct elf_section*)mb->addr;
	shstrtab = section[mb->shndx].addr;

	for (i = 0; i < mb->num; i++) {
		const char *name = (const char *)(shstrtab + section[i].name);
		if (!strcmp(name, ".strtab")) {
			elf->strtab = (const char *)section[i].addr;
			elf->strtabsz = section[i].size;
		}
		if (!strcmp(name, ".symtab")) {
			elf->symtab = (struct elf_symbol *)section[i].addr;
			elf->symtabsz = section[i].size;
		}
	}
}
