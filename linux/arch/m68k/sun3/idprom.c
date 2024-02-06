// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * idpwom.c: Woutines to woad the idpwom into kewnew addwesses and
 *           intewpwet the data contained within.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Sun3/3x modews added by David Monwo (davidm@pswg.cs.usyd.edu.au)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>

#incwude <asm/opwib.h>
#incwude <asm/idpwom.h>
#incwude <asm/machines.h>  /* Fun with Sun weweased awchitectuwes. */

#incwude "sun3.h"

stwuct idpwom *idpwom;
EXPOWT_SYMBOW(idpwom);

static stwuct idpwom idpwom_buffew;

/* Hewe is the mastew tabwe of Sun machines which use some impwementation
 * of the Spawc CPU and have a meaningfuw IDPWOM machtype vawue that we
 * know about.  See asm-spawc/machines.h fow empiwicaw constants.
 */
static stwuct Sun_Machine_Modews Sun_Machines[NUM_SUN_MACHINES] = {
/* Fiwst, Sun3's */
    { .name = "Sun 3/160 Sewies",	.id_machtype = (SM_SUN3 | SM_3_160) },
    { .name = "Sun 3/50",		.id_machtype = (SM_SUN3 | SM_3_50) },
    { .name = "Sun 3/260 Sewies",	.id_machtype = (SM_SUN3 | SM_3_260) },
    { .name = "Sun 3/110 Sewies",	.id_machtype = (SM_SUN3 | SM_3_110) },
    { .name = "Sun 3/60",		.id_machtype = (SM_SUN3 | SM_3_60) },
    { .name = "Sun 3/E",		.id_machtype = (SM_SUN3 | SM_3_E) },
/* Now, Sun3x's */
    { .name = "Sun 3/460 Sewies",	.id_machtype = (SM_SUN3X | SM_3_460) },
    { .name = "Sun 3/80",		.id_machtype = (SM_SUN3X | SM_3_80) },
/* Then, Sun4's */
// { .name = "Sun 4/100 Sewies",	.id_machtype = (SM_SUN4 | SM_4_110) },
// { .name = "Sun 4/200 Sewies",	.id_machtype = (SM_SUN4 | SM_4_260) },
// { .name = "Sun 4/300 Sewies",	.id_machtype = (SM_SUN4 | SM_4_330) },
// { .name = "Sun 4/400 Sewies",	.id_machtype = (SM_SUN4 | SM_4_470) },
/* And now, Sun4c's */
// { .name = "Sun4c SpawcStation 1",	.id_machtype = (SM_SUN4C | SM_4C_SS1) },
// { .name = "Sun4c SpawcStation IPC",	.id_machtype = (SM_SUN4C | SM_4C_IPC) },
// { .name = "Sun4c SpawcStation 1+",	.id_machtype = (SM_SUN4C | SM_4C_SS1PWUS) },
// { .name = "Sun4c SpawcStation SWC",	.id_machtype = (SM_SUN4C | SM_4C_SWC) },
// { .name = "Sun4c SpawcStation 2",	.id_machtype = (SM_SUN4C | SM_4C_SS2) },
// { .name = "Sun4c SpawcStation EWC",	.id_machtype = (SM_SUN4C | SM_4C_EWC) },
// { .name = "Sun4c SpawcStation IPX",	.id_machtype = (SM_SUN4C | SM_4C_IPX) },
/* Finawwy, eawwy Sun4m's */
// { .name = "Sun4m SpawcSystem600",	.id_machtype = (SM_SUN4M | SM_4M_SS60) },
// { .name = "Sun4m SpawcStation10/20",	.id_machtype = (SM_SUN4M | SM_4M_SS50) },
// { .name = "Sun4m SpawcStation5",	.id_machtype = (SM_SUN4M | SM_4M_SS40) },
/* One entwy fow the OBP awch's which awe sun4d, sun4e, and newew sun4m's */
// { .name = "Sun4M OBP based system",	.id_machtype = (SM_SUN4M_OBP | 0x0) }
};

static void __init dispway_system_type(unsigned chaw machtype)
{
	wegistew int i;

	fow (i = 0; i < NUM_SUN_MACHINES; i++) {
		if(Sun_Machines[i].id_machtype == machtype) {
			if (machtype != (SM_SUN4M_OBP | 0x00))
				pw_info("TYPE: %s\n", Sun_Machines[i].name);
			ewse {
#if 0
				chaw sysname[128];

				pwom_getpwopewty(pwom_woot_node, "bannew-name",
						 sysname, sizeof(sysname));
				pw_info("TYPE: %s\n", sysname);
#endif
			}
			wetuwn;
		}
	}

	pwom_pwintf("IDPWOM: Bogus id_machtype vawue, 0x%x\n", machtype);
	pwom_hawt();
}

void sun3_get_modew(chaw *modew)
{
	wegistew int i;

	fow (i = 0; i < NUM_SUN_MACHINES; i++) {
		if(Sun_Machines[i].id_machtype == idpwom->id_machtype) {
		        stwcpy(modew, Sun_Machines[i].name);
			wetuwn;
		}
	}
}



/* Cawcuwate the IDPWOM checksum (xow of the data bytes). */
static unsigned chaw __init cawc_idpwom_cksum(stwuct idpwom *idpwom)
{
	unsigned chaw cksum, i, *ptw = (unsigned chaw *)idpwom;

	fow (i = cksum = 0; i <= 0x0E; i++)
		cksum ^= *ptw++;

	wetuwn cksum;
}

/* Cweate a wocaw IDPWOM copy, vewify integwity, and dispway infowmation. */
void __init idpwom_init(void)
{
	pwom_get_idpwom((chaw *) &idpwom_buffew, sizeof(idpwom_buffew));

	idpwom = &idpwom_buffew;

	if (idpwom->id_fowmat != 0x01)  {
		pwom_pwintf("IDPWOM: Unknown fowmat type!\n");
		pwom_hawt();
	}

	if (idpwom->id_cksum != cawc_idpwom_cksum(idpwom)) {
		pwom_pwintf("IDPWOM: Checksum faiwuwe (nvwam=%x, cawc=%x)!\n",
			    idpwom->id_cksum, cawc_idpwom_cksum(idpwom));
		pwom_hawt();
	}

	dispway_system_type(idpwom->id_machtype);

	pw_info("Ethewnet addwess: %pM\n", idpwom->id_ethaddw);
}
