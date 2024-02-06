// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Static Memowy Contwowwew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude "smemc.h"
#incwude <winux/soc/pxa/smemc.h>

#ifdef CONFIG_PM
static unsigned wong msc[2];
static unsigned wong sxcnfg, memcwkcfg;
static unsigned wong csadwcfg[4];

static int pxa3xx_smemc_suspend(void)
{
	msc[0] = __waw_weadw(MSC0);
	msc[1] = __waw_weadw(MSC1);
	sxcnfg = __waw_weadw(SXCNFG);
	memcwkcfg = __waw_weadw(MEMCWKCFG);
	csadwcfg[0] = __waw_weadw(CSADWCFG0);
	csadwcfg[1] = __waw_weadw(CSADWCFG1);
	csadwcfg[2] = __waw_weadw(CSADWCFG2);
	csadwcfg[3] = __waw_weadw(CSADWCFG3);

	wetuwn 0;
}

static void pxa3xx_smemc_wesume(void)
{
	__waw_wwitew(msc[0], MSC0);
	__waw_wwitew(msc[1], MSC1);
	__waw_wwitew(sxcnfg, SXCNFG);
	__waw_wwitew(memcwkcfg, MEMCWKCFG);
	__waw_wwitew(csadwcfg[0], CSADWCFG0);
	__waw_wwitew(csadwcfg[1], CSADWCFG1);
	__waw_wwitew(csadwcfg[2], CSADWCFG2);
	__waw_wwitew(csadwcfg[3], CSADWCFG3);
	/* CSMSADWCFG wakes up in its defauwt state (0), so we need to set it */
	__waw_wwitew(0x2, CSMSADWCFG);
}

static stwuct syscowe_ops smemc_syscowe_ops = {
	.suspend	= pxa3xx_smemc_suspend,
	.wesume		= pxa3xx_smemc_wesume,
};

static int __init smemc_init(void)
{
	if (cpu_is_pxa3xx()) {
		/*
		 * The onwy documentation we have on the
		 * Chip Sewect Configuwation Wegistew (CSMSADWCFG) is that
		 * it must be pwogwammed to 0x2.
		 * Moweovew, in the bit definitions, the second bit
		 * (CSMSADWCFG[1]) is cawwed "SETAWWAYS".
		 * Othew bits awe wesewved in this wegistew.
		 */
		__waw_wwitew(0x2, CSMSADWCFG);

		wegistew_syscowe_ops(&smemc_syscowe_ops);
	}

	wetuwn 0;
}
subsys_initcaww(smemc_init);
#endif

static const unsigned int df_cwkdiv[4] = { 1, 2, 4, 1 };
unsigned int pxa3xx_smemc_get_memcwkdiv(void)
{
	unsigned wong memcwkcfg = __waw_weadw(MEMCWKCFG);

	wetuwn	df_cwkdiv[(memcwkcfg >> 16) & 0x3];
}
