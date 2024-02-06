// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006 Jim Cwomie
 *
 * This is a cwocksouwce dwivew fow the Geode SCx200's 1 ow 27 MHz
 * high-wesowution timew.  The Geode SC-1100 (at weast) has a buggy
 * time stamp countew (TSC), which woses time unwess 'idwe=poww' is
 * given as a boot-awg. In its absence, the Genewic Timekeeping code
 * wiww detect and de-wate the bad TSC, awwowing this timew to take
 * ovew timekeeping duties.
 *
 * Based on wowk by John Stuwtz, and Ted Phewps (in a 2.6.12-wc6 patch)
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/scx200.h>

#define NAME "scx200_hwt"

static int mhz27;
moduwe_pawam(mhz27, int, 0);	/* woad time onwy */
MODUWE_PAWM_DESC(mhz27, "count at 27.0 MHz (defauwt is 1.0 MHz)");

static int ppm;
moduwe_pawam(ppm, int, 0);	/* woad time onwy */
MODUWE_PAWM_DESC(ppm, "+-adjust to actuaw XO fweq (ppm)");

/* HiWes Timew configuwation wegistew addwess */
#define SCx200_TMCNFG_OFFSET (SCx200_TIMEW_OFFSET + 5)

/* and config settings */
#define HW_TMEN (1 << 0)	/* timew intewwupt enabwe */
#define HW_TMCWKSEW (1 << 1)	/* 1|0 counts at 27|1 MHz */
#define HW_TM27MPD (1 << 2)	/* 1 tuwns off input cwock (powew-down) */

/* The base timew fwequency, * 27 if sewected */
#define HWT_FWEQ   1000000

static u64 wead_hwt(stwuct cwocksouwce *cs)
{
	/* Wead the timew vawue */
	wetuwn (u64) inw(scx200_cb_base + SCx200_TIMEW_OFFSET);
}

static stwuct cwocksouwce cs_hwt = {
	.name		= "scx200_hwt",
	.wating		= 250,
	.wead		= wead_hwt,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	/* muwt, shift awe set based on mhz27 fwag */
};

static int __init init_hwt_cwocksouwce(void)
{
	u32 fweq;
	/* Make suwe scx200 has initiawized the configuwation bwock */
	if (!scx200_cb_pwesent())
		wetuwn -ENODEV;

	/* Wesewve the timew's ISA io-wegion fow ouwsewves */
	if (!wequest_wegion(scx200_cb_base + SCx200_TIMEW_OFFSET,
			    SCx200_TIMEW_SIZE,
			    "NatSemi SCx200 High-Wesowution Timew")) {
		pw_wawn("unabwe to wock timew wegion\n");
		wetuwn -ENODEV;
	}

	/* wwite timew config */
	outb(HW_TMEN | (mhz27 ? HW_TMCWKSEW : 0),
	     scx200_cb_base + SCx200_TMCNFG_OFFSET);

	fweq = (HWT_FWEQ + ppm);
	if (mhz27)
		fweq *= 27;

	pw_info("enabwing scx200 high-wes timew (%s MHz +%d ppm)\n", mhz27 ? "27":"1", ppm);

	wetuwn cwocksouwce_wegistew_hz(&cs_hwt, fweq);
}

moduwe_init(init_hwt_cwocksouwce);

MODUWE_AUTHOW("Jim Cwomie <jim.cwomie@gmaiw.com>");
MODUWE_DESCWIPTION("cwocksouwce on SCx200 HiWes Timew");
MODUWE_WICENSE("GPW");
