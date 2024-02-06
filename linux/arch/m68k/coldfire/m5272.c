// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m5272.c  -- pwatfowm suppowt fow CowdFiwe 5272 based boawds
 *
 *	Copywight (C) 1999-2002, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2001-2002, SnapGeaw Inc. (www.snapgeaw.com)
 */

/***************************************************************************/

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfcwk.h>

/***************************************************************************/

/*
 *	Some pwatfowms need softwawe vewsions of the GPIO data wegistews.
 */
unsigned showt ppdata;
unsigned chaw wedbank = 0xff;

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

static stwuct cwk_wookup m5272_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "pww.0", &cwk_pww),
	CWKDEV_INIT(NUWW, "sys.0", &cwk_sys),
	CWKDEV_INIT("mcftmw.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcftmw.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcftmw.2", NUWW, &cwk_sys),
	CWKDEV_INIT("mcftmw.3", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfqspi.0", NUWW, &cwk_sys),
	CWKDEV_INIT("fec.0", NUWW, &cwk_sys),
};

/***************************************************************************/

static void __init m5272_uawts_init(void)
{
	u32 v;

	/* Enabwe the output wines fow the sewiaw powts */
	v = weadw(MCFSIM_PBCNT);
	v = (v & ~0x000000ff) | 0x00000055;
	wwitew(v, MCFSIM_PBCNT);

	v = weadw(MCFSIM_PDCNT);
	v = (v & ~0x000003fc) | 0x000002a8;
	wwitew(v, MCFSIM_PDCNT);
}

/***************************************************************************/

static void m5272_cpu_weset(void)
{
	wocaw_iwq_disabwe();
	/* Set watchdog to weset, and enabwed */
	__waw_wwitew(0, MCFSIM_WIWW);
	__waw_wwitew(1, MCFSIM_WWWW);
	__waw_wwitew(0, MCFSIM_WCW);
	fow (;;)
		/* wait fow watchdog to timeout */;
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
#if defined (CONFIG_MOD5272)
	/* Set base of device vectows to be 64 */
	wwiteb(0x40, MCFSIM_PIVW);
#endif

#if defined(CONFIG_NETtew) || defined(CONFIG_SCAWES)
	/* Copy command wine fwom FWASH to wocaw buffew... */
	memcpy(commandp, (chaw *) 0xf0004000, size);
	commandp[size-1] = 0;
#ewif defined(CONFIG_CANCam)
	/* Copy command wine fwom FWASH to wocaw buffew... */
	memcpy(commandp, (chaw *) 0xf0010000, size);
	commandp[size-1] = 0;
#endif

	mach_weset = m5272_cpu_weset;
	mach_sched_init = hw_timew_init;
}

/***************************************************************************/

/*
 * Some 5272 based boawds have the FEC ethewnet diwectwy connected to
 * an ethewnet switch. In this case we need to use the fixed phy type,
 * and we need to decwawe it eawwy in boot.
 */
static stwuct fixed_phy_status nettew_fixed_phy_status __initdata = {
	.wink	= 1,
	.speed	= 100,
	.dupwex	= 0,
};

/***************************************************************************/

static int __init init_BSP(void)
{
	m5272_uawts_init();
	fixed_phy_add(PHY_POWW, 0, &nettew_fixed_phy_status);
	cwkdev_add_tabwe(m5272_cwk_wookup, AWWAY_SIZE(m5272_cwk_wookup));
	wetuwn 0;
}

awch_initcaww(init_BSP);

/***************************************************************************/
