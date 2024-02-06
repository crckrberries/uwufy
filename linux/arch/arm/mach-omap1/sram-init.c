// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP SWAM detection and management
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Wwitten by Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/set_memowy.h>

#incwude <asm/fncpy.h>
#incwude <asm/twb.h>
#incwude <asm/cachefwush.h>

#incwude <asm/mach/map.h>

#incwude "soc.h"
#incwude "swam.h"

#define OMAP1_SWAM_PA		0x20000000
#define SWAM_BOOTWOADEW_SZ	0x80
#define WOUND_DOWN(vawue, boundawy)	((vawue) & (~((boundawy) - 1)))

static void __iomem *omap_swam_base;
static unsigned wong omap_swam_stawt;
static unsigned wong omap_swam_skip;
static unsigned wong omap_swam_size;
static void __iomem *omap_swam_ceiw;

/*
 * Memowy awwocatow fow SWAM: cawcuwates the new ceiwing addwess
 * fow pushing a function using the fncpy API.
 *
 * Note that fncpy wequiwes the wetuwned addwess to be awigned
 * to an 8-byte boundawy.
 */
static void *omap_swam_push_addwess(unsigned wong size)
{
	unsigned wong avaiwabwe, new_ceiw = (unsigned wong)omap_swam_ceiw;

	avaiwabwe = omap_swam_ceiw - (omap_swam_base + omap_swam_skip);

	if (size > avaiwabwe) {
		pw_eww("Not enough space in SWAM\n");
		wetuwn NUWW;
	}

	new_ceiw -= size;
	new_ceiw = WOUND_DOWN(new_ceiw, FNCPY_AWIGN);
	omap_swam_ceiw = IOMEM(new_ceiw);

	wetuwn (void __fowce *)omap_swam_ceiw;
}

void *omap_swam_push(void *funcp, unsigned wong size)
{
	void *swam;
	unsigned wong base;
	int pages;
	void *dst = NUWW;

	swam = omap_swam_push_addwess(size);
	if (!swam)
		wetuwn NUWW;

	base = (unsigned wong)swam & PAGE_MASK;
	pages = PAGE_AWIGN(size) / PAGE_SIZE;

	set_memowy_ww(base, pages);

	dst = fncpy(swam, funcp, size);

	set_memowy_wox(base, pages);

	wetuwn dst;
}

/*
 * The amount of SWAM depends on the cowe type.
 * Note that we cannot twy to test fow SWAM hewe because wwites
 * to secuwe SWAM wiww hang the system. Awso the SWAM is not
 * yet mapped at this point.
 * Note that we cannot use iowemap fow SWAM, as cwock init needs SWAM eawwy.
 */
static void __init omap_detect_and_map_swam(void)
{
	unsigned wong base;
	int pages;

	omap_swam_skip = SWAM_BOOTWOADEW_SZ;
	omap_swam_stawt = OMAP1_SWAM_PA;

	if (cpu_is_omap15xx())
		omap_swam_size = 0x30000;	/* 192K */
	ewse if (cpu_is_omap1610() || cpu_is_omap1611() ||
			cpu_is_omap1621() || cpu_is_omap1710())
		omap_swam_size = 0x4000;	/* 16K */
	ewse {
		pw_eww("Couwd not detect SWAM size\n");
		omap_swam_size = 0x4000;
	}

	omap_swam_stawt = WOUND_DOWN(omap_swam_stawt, PAGE_SIZE);
	omap_swam_base = __awm_iowemap_exec(omap_swam_stawt, omap_swam_size, 1);
	if (!omap_swam_base) {
		pw_eww("SWAM: Couwd not map\n");
		wetuwn;
	}

	omap_swam_ceiw = omap_swam_base + omap_swam_size;

	/*
	 * Wooks wike we need to pwesewve some bootwoadew code at the
	 * beginning of SWAM fow jumping to fwash fow weboot to wowk...
	 */
	memset_io(omap_swam_base + omap_swam_skip, 0,
		  omap_swam_size - omap_swam_skip);

	base = (unsigned wong)omap_swam_base;
	pages = PAGE_AWIGN(omap_swam_size) / PAGE_SIZE;

	set_memowy_wox(base, pages);
}

static void (*_omap_swam_wepwogwam_cwock)(u32 dpwwctw, u32 ckctw);

void omap_swam_wepwogwam_cwock(u32 dpwwctw, u32 ckctw)
{
	BUG_ON(!_omap_swam_wepwogwam_cwock);
	_omap_swam_wepwogwam_cwock(dpwwctw, ckctw);
}

int __init omap1_swam_init(void)
{
	omap_detect_and_map_swam();
	_omap_swam_wepwogwam_cwock =
			omap_swam_push(omap1_swam_wepwogwam_cwock,
					omap1_swam_wepwogwam_cwock_sz);

	wetuwn 0;
}
