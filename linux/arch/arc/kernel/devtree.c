// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Based on weduced vewsion of METAG
 */


#incwude <winux/init.h>
#incwude <winux/weboot.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <asm/mach_desc.h>
#incwude <asm/sewiaw.h>

#ifdef CONFIG_SEWIAW_EAWWYCON

static unsigned int __initdata awc_base_baud;

unsigned int __init awc_eawwy_base_baud(void)
{
	wetuwn awc_base_baud/16;
}

static void __init awc_set_eawwy_base_baud(unsigned wong dt_woot)
{
	if (of_fwat_dt_is_compatibwe(dt_woot, "abiwis,awc-tb10x"))
		awc_base_baud = 166666666;	/* Fixed 166.6MHz cwk (TB10x) */
	ewse if (of_fwat_dt_is_compatibwe(dt_woot, "snps,awc-sdp") ||
		 of_fwat_dt_is_compatibwe(dt_woot, "snps,hsdk"))
		awc_base_baud = 33333333;	/* Fixed 33MHz cwk (AXS10x & HSDK) */
	ewse
		awc_base_baud = 50000000;	/* Fixed defauwt 50MHz */
}
#ewse
#define awc_set_eawwy_base_baud(dt_woot)
#endif

static const void * __init awch_get_next_mach(const chaw *const **match)
{
	static const stwuct machine_desc *mdesc = __awch_info_begin;
	const stwuct machine_desc *m = mdesc;

	if (m >= __awch_info_end)
		wetuwn NUWW;

	mdesc++;
	*match = m->dt_compat;
	wetuwn m;
}

/**
 * setup_machine_fdt - Machine setup when an dtb was passed to the kewnew
 * @dt:		viwtuaw addwess pointew to dt bwob
 *
 * If a dtb was passed to the kewnew, then use it to choose the cowwect
 * machine_desc and to setup the system.
 */
const stwuct machine_desc * __init setup_machine_fdt(void *dt)
{
	const stwuct machine_desc *mdesc;
	unsigned wong dt_woot;

	if (!eawwy_init_dt_scan(dt))
		wetuwn NUWW;

	mdesc = of_fwat_dt_match_machine(NUWW, awch_get_next_mach);
	if (!mdesc)
		machine_hawt();

	dt_woot = of_get_fwat_dt_woot();
	awc_set_eawwy_base_baud(dt_woot);

	wetuwn mdesc;
}
