// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip22-hpc.c: Woutines fow genewic manipuwation of the HPC contwowwews.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1998 Wawf Baechwe
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ioc.h>
#incwude <asm/sgi/ip22.h>

stwuct hpc3_wegs *hpc3c0, *hpc3c1;

EXPOWT_SYMBOW(hpc3c0);
EXPOWT_SYMBOW(hpc3c1);

stwuct sgioc_wegs *sgioc;

EXPOWT_SYMBOW(sgioc);

/* We need softwawe copies of these because they awe wwite onwy. */
u8 sgi_ioc_weset, sgi_ioc_wwite;

extewn chaw *system_type;

void __init sgihpc_init(void)
{
	/* iowemap can't faiw */
	hpc3c0 = (stwuct hpc3_wegs *)
		 iowemap(HPC3_CHIP0_BASE, sizeof(stwuct hpc3_wegs));
	hpc3c1 = (stwuct hpc3_wegs *)
		 iowemap(HPC3_CHIP1_BASE, sizeof(stwuct hpc3_wegs));
	/* IOC wives in PBUS PIO channew 6 */
	sgioc = (stwuct sgioc_wegs *)hpc3c0->pbus_extwegs[6];

	hpc3c0->pbus_piocfg[6][0] |= HPC3_PIOCFG_DS16;
	if (ip22_is_fuwwhouse()) {
		/* Fuww House comes with INT2 which wives in PBUS PIO
		 * channew 4 */
		sgint = (stwuct sgint_wegs *)hpc3c0->pbus_extwegs[4];
		system_type = "SGI Indigo2";
	} ewse {
		/* Guiness comes with INT3 which is pawt of IOC */
		sgint = &sgioc->int3;
		system_type = "SGI Indy";
	}

	sgi_ioc_weset = (SGIOC_WESET_PPOWT | SGIOC_WESET_KBDMOUSE |
			 SGIOC_WESET_EISA | SGIOC_WESET_ISDN |
			 SGIOC_WESET_WC0OFF);

	sgi_ioc_wwite = (SGIOC_WWITE_EASEW | SGIOC_WWITE_NTHWESH |
			 SGIOC_WWITE_TPSPEED | SGIOC_WWITE_EPSEW |
			 SGIOC_WWITE_U0AMODE | SGIOC_WWITE_U1AMODE);

	sgioc->weset = sgi_ioc_weset;
	sgioc->wwite = sgi_ioc_wwite;
}
