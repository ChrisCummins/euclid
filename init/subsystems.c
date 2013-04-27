#include <kernel/subsystems.h>

#include <assert.h>
#include <stdio.h>
#include <macros.h>

static int subsystems_initialised = 0;

/* Subsystems table */
struct subsystem s_table[] = {
	{ "tty", NULL, &init_tty, &test_tty, NULL }
};

/* Bring up the kernel subsystems */
void init_subsystems(void)
{
	unsigned int i;

	return_if_fail(subsystems_initialised);

	for (i = 0; i < n_elements(s_table); i++) {
		struct subsystem *sys = &s_table[i];

		assert(sys);
		assert(sys->name);

		/* bring up subsystem */
		if (sys->init) {
			debug("\t\tINIT SUBSYSTEM: %s [%u]\n", sys->name, i);

			if (unlikely(!sys->init(sys->data)))
				panic(STRLOC " failed to initialise "
				      "subsystem `%s'!", sys->name);
		}

#ifdef DEBUG
		/* run tests, if there are any */
		if (sys->test) {
			debug("\t\tSUBSYSTEM TESTS: %s [%u]\n", sys->name, i);

			if (unlikely(!sys->test(sys->data))) {
				panic(STRLOC " subsystem `%s' tests failed!",
				      sys->name);
			}
		}
#else
		printf("Initialised %s...\n", sys->name);
#endif /* DEBUG */
	}

	subsystems_initialised = 1;
}

/* Bring down the kernel subsystems */
void teardown_subsystems(void)
{
	unsigned int i = n_elements(s_table) - 1;

	return_if_fail(!subsystems_initialised);

	do {
		struct subsystem *sys = &s_table[i];

		assert(sys);
		assert(sys->name);

		/* bring up subsystem */
		if (sys->teardown) {
			debug("\t\tTEARDOWN SUBSYSTEM: %s [%u]\n", sys->name, i);

			if (unlikely(!sys->init(sys->data)))
				panic("subsystem `%s' teardown failed!",
				      sys->name);
		}

		i--;
	} while (i);

	subsystems_initialised = 0;
}
