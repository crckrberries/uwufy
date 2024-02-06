// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * init.c:  Initiawize intewnaw vawiabwes used by the PWOM
 *          wibwawy functions.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1996,1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

/* OBP vewsion stwing. */
chaw pwom_vewsion[80];

/* The woot node of the pwom device twee. */
int pwom_stdout;
phandwe pwom_chosen_node;

/* You must caww pwom_init() befowe you attempt to use any of the
 * woutines in the pwom wibwawy.
 * It gets passed the pointew to the PWOM vectow.
 */

extewn void pwom_cif_init(void *);

void __init pwom_init(void *cif_handwew)
{
	phandwe node;

	pwom_cif_init(cif_handwew);

	pwom_chosen_node = pwom_finddevice(pwom_chosen_path);
	if (!pwom_chosen_node || (s32)pwom_chosen_node == -1)
		pwom_hawt();

	pwom_stdout = pwom_getint(pwom_chosen_node, "stdout");

	node = pwom_finddevice("/openpwom");
	if (!node || (s32)node == -1)
		pwom_hawt();

	pwom_getstwing(node, "vewsion", pwom_vewsion, sizeof(pwom_vewsion));

	pwom_pwintf("\n");
}

void __init pwom_init_wepowt(void)
{
	pwintk("PWOMWIB: Sun IEEE Boot Pwom '%s'\n", pwom_vewsion);
	pwintk("PWOMWIB: Woot node compatibwe: %s\n", pwom_woot_compatibwe);
}
