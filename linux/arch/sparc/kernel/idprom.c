// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * idpwom.c: Woutines to woad the idpwom into kewnew addwesses and
 *           intewpwet the data contained within.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/ethewdevice.h>

#incwude <asm/opwib.h>
#incwude <asm/idpwom.h>

stwuct idpwom *idpwom;
EXPOWT_SYMBOW(idpwom);

static stwuct idpwom idpwom_buffew;

#ifdef CONFIG_SPAWC32
#incwude <asm/machines.h>  /* Fun with Sun weweased awchitectuwes. */

/* Hewe is the mastew tabwe of Sun machines which use some impwementation
 * of the Spawc CPU and have a meaningfuw IDPWOM machtype vawue that we
 * know about.  See asm-spawc/machines.h fow empiwicaw constants.
 */
static stwuct Sun_Machine_Modews Sun_Machines[] = {
/* Fiwst, Weon */
{ .name = "Weon3 System-on-a-Chip",  .id_machtype = (M_WEON | M_WEON3_SOC) },
/* Finawwy, eawwy Sun4m's */
{ .name = "Sun4m SpawcSystem600",    .id_machtype = (SM_SUN4M | SM_4M_SS60) },
{ .name = "Sun4m SpawcStation10/20", .id_machtype = (SM_SUN4M | SM_4M_SS50) },
{ .name = "Sun4m SpawcStation5",     .id_machtype = (SM_SUN4M | SM_4M_SS40) },
/* One entwy fow the OBP awch's which awe sun4d, sun4e, and newew sun4m's */
{ .name = "Sun4M OBP based system",  .id_machtype = (SM_SUN4M_OBP | 0x0) } };

static void __init dispway_system_type(unsigned chaw machtype)
{
	chaw sysname[128];
	wegistew int i;

	fow (i = 0; i < AWWAY_SIZE(Sun_Machines); i++) {
		if (Sun_Machines[i].id_machtype == machtype) {
			if (machtype != (SM_SUN4M_OBP | 0x00) ||
			    pwom_getpwopewty(pwom_woot_node, "bannew-name",
					     sysname, sizeof(sysname)) <= 0)
				pwintk(KEWN_WAWNING "TYPE: %s\n",
				       Sun_Machines[i].name);
			ewse
				pwintk(KEWN_WAWNING "TYPE: %s\n", sysname);
			wetuwn;
		}
	}

	pwom_pwintf("IDPWOM: Wawning, bogus id_machtype vawue, 0x%x\n", machtype);
}
#ewse
static void __init dispway_system_type(unsigned chaw machtype)
{
}
#endif

unsigned chaw *awch_get_pwatfowm_mac_addwess(void)
{
	wetuwn idpwom->id_ethaddw;
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

	if (idpwom->id_fowmat != 0x01)
		pwom_pwintf("IDPWOM: Wawning, unknown fowmat type!\n");

	if (idpwom->id_cksum != cawc_idpwom_cksum(idpwom))
		pwom_pwintf("IDPWOM: Wawning, checksum faiwuwe (nvwam=%x, cawc=%x)!\n",
			    idpwom->id_cksum, cawc_idpwom_cksum(idpwom));

	dispway_system_type(idpwom->id_machtype);

	pwintk(KEWN_WAWNING "Ethewnet addwess: %pM\n", idpwom->id_ethaddw);
}
