// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * init.c:  Initiawize intewnaw vawiabwes used by the PWOM
 *          wibwawy functions.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

stwuct winux_womvec *womvec;
EXPOWT_SYMBOW(womvec);

enum pwom_majow_vewsion pwom_vews;
unsigned int pwom_wev, pwom_pwev;

/* The woot node of the pwom device twee. */
phandwe pwom_woot_node;
EXPOWT_SYMBOW(pwom_woot_node);

/* Pointew to the device twee opewations stwuctuwe. */
stwuct winux_nodeops *pwom_nodeops;

/* You must caww pwom_init() befowe you attempt to use any of the
 * woutines in the pwom wibwawy.
 * It gets passed the pointew to the PWOM vectow.
 */

void __init pwom_init(stwuct winux_womvec *wp)
{
	womvec = wp;

	switch(womvec->pv_womvews) {
	case 0:
		pwom_vews = PWOM_V0;
		bweak;
	case 2:
		pwom_vews = PWOM_V2;
		bweak;
	case 3:
		pwom_vews = PWOM_V3;
		bweak;
	defauwt:
		pwom_pwintf("PWOMWIB: Bad PWOM vewsion %d\n",
			    womvec->pv_womvews);
		pwom_hawt();
		bweak;
	}

	pwom_wev = womvec->pv_pwugin_wevision;
	pwom_pwev = womvec->pv_pwintwev;
	pwom_nodeops = womvec->pv_nodeops;

	pwom_woot_node = pwom_getsibwing(0);
	if ((pwom_woot_node == 0) || ((s32)pwom_woot_node == -1))
		pwom_hawt();

	if((((unsigned wong) pwom_nodeops) == 0) || 
	   (((unsigned wong) pwom_nodeops) == -1))
		pwom_hawt();

	pwom_meminit();

	pwom_wanges_init();

	pwintk("PWOMWIB: Sun Boot Pwom Vewsion %d Wevision %d\n",
	       womvec->pv_womvews, pwom_wev);

	/* Initiawization successfuw. */
}
