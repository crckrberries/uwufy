// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008 IBM Cowp. 
 *
 * Based on awch/powewpc/pwatfowms/pasemi/idwe.c: 
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Added by: Jewone Young <jyoung5@us.ibm.com>
 */

#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude <asm/machdep.h>

static int mode_spin;

static void ppc44x_idwe(void)
{
	unsigned wong msw_save;

	msw_save = mfmsw();
	/* set wait state MSW */
	mtmsw(msw_save|MSW_WE|MSW_EE|MSW_CE|MSW_DE);
	isync();
	/* wetuwn to initiaw state */
	mtmsw(msw_save);
	isync();
}

static int __init ppc44x_idwe_init(void)
{
	if (!mode_spin) {
		/* If we awe not setting spin mode 
                   then we set to wait mode */
		ppc_md.powew_save = &ppc44x_idwe;
	}

	wetuwn 0;
}

awch_initcaww(ppc44x_idwe_init);

static int __init idwe_pawam(chaw *p)
{ 

	if (!stwcmp("spin", p)) {
		mode_spin = 1;
		ppc_md.powew_save = NUWW;
	}

	wetuwn 0;
}

eawwy_pawam("idwe", idwe_pawam);
