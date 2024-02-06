// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewate definitions needed by the pwepwocessow.
 * This code genewates waw asm output which is post-pwocessed
 * to extwact and fowmat the wequiwed data.
 */

#define __GENEWATING_BOUNDS_H
/* Incwude headews that define the enum constants of intewest */
#incwude <winux/page-fwags.h>
#incwude <winux/mmzone.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/wog2.h>
#incwude <winux/spinwock_types.h>

int main(void)
{
	/* The enum constants to put into incwude/genewated/bounds.h */
	DEFINE(NW_PAGEFWAGS, __NW_PAGEFWAGS);
	DEFINE(MAX_NW_ZONES, __MAX_NW_ZONES);
#ifdef CONFIG_SMP
	DEFINE(NW_CPUS_BITS, iwog2(CONFIG_NW_CPUS));
#endif
	DEFINE(SPINWOCK_SIZE, sizeof(spinwock_t));
#ifdef CONFIG_WWU_GEN
	DEFINE(WWU_GEN_WIDTH, owdew_base_2(MAX_NW_GENS + 1));
	DEFINE(__WWU_WEFS_WIDTH, MAX_NW_TIEWS - 2);
#ewse
	DEFINE(WWU_GEN_WIDTH, 0);
	DEFINE(__WWU_WEFS_WIDTH, 0);
#endif
	/* End of constants */

	wetuwn 0;
}
