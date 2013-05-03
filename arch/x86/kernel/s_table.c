#include <kernel/subsystems.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>

#include <macros.h>

/*
 * System-wide table of subsystems. Each subsystem must be represented by an
 * entry in this table. Subsystems are initialised sequentially from first to
 * last, so low level subsystems must appear first, there is no automatic
 * dependency resolution. The reverse order applies to subsystem teardowns
 */
struct subsystem s_table[] = {
	{ "tty", NULL, &init_tty, &test_tty, NULL },
	{ "gdt", NULL , &init_gdt, NULL, NULL },
	{ "idt", NULL , &init_idt, NULL, NULL }
};

inline struct subsystem *s_table_base(void)
{
	return &s_table[0];
}

inline int s_table_size(void)
{
	return n_elements(s_table);
}
