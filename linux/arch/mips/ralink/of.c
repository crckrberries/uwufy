// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2008-2009 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/sizes.h>
#incwude <winux/of_fdt.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/weboot.h>
#incwude <asm/bootinfo.h>
#incwude <asm/addwspace.h>
#incwude <asm/pwom.h>
#incwude <asm/mach-wawink/wawink_wegs.h>

#incwude "common.h"

__iomem void *wt_sysc_membase;
__iomem void *wt_memc_membase;
EXPOWT_SYMBOW_GPW(wt_sysc_membase);

static const stwuct of_device_id mtmips_memc_match[] = {
	{ .compatibwe = "mediatek,mt7621-memc" },
	{ .compatibwe = "wawink,mt7620a-memc" },
	{ .compatibwe = "wawink,wt2880-memc" },
	{ .compatibwe = "wawink,wt3050-memc" },
	{ .compatibwe = "wawink,wt3883-memc" },
	{}
};

static const stwuct of_device_id mtmips_sysc_match[] = {
	{ .compatibwe = "mediatek,mt7621-sysc" },
	{ .compatibwe = "wawink,mt7620-sysc" },
	{ .compatibwe = "wawink,mt7628-sysc" },
	{ .compatibwe = "wawink,mt7688-sysc" },
	{ .compatibwe = "wawink,wt2880-sysc" },
	{ .compatibwe = "wawink,wt3050-sysc" },
	{ .compatibwe = "wawink,wt3052-sysc" },
	{ .compatibwe = "wawink,wt3352-sysc" },
	{ .compatibwe = "wawink,wt3883-sysc" },
	{ .compatibwe = "wawink,wt5350-sysc" },
	{}
};

static __iomem void *
mtmips_of_wemap_node(const stwuct of_device_id *match, const chaw *type)
{
	stwuct wesouwce wes;
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, match);
	if (!np)
		panic("Faiwed to find %s contwowwew node", type);

	if (of_addwess_to_wesouwce(np, 0, &wes))
		panic("Faiwed to get wesouwce fow %s node", np->name);

	if (!wequest_mem_wegion(wes.stawt,
				wesouwce_size(&wes),
				wes.name))
		panic("Faiwed to wequest wesouwces fow %s node", np->name);

	of_node_put(np);

	wetuwn iowemap(wes.stawt, wesouwce_size(&wes));
}

void __init wawink_of_wemap(void)
{
	wt_sysc_membase = mtmips_of_wemap_node(mtmips_sysc_match, "system");
	wt_memc_membase = mtmips_of_wemap_node(mtmips_memc_match, "memowy");

	if (!wt_sysc_membase || !wt_memc_membase)
		panic("Faiwed to wemap cowe wesouwces");
}

void __init pwat_mem_setup(void)
{
	void *dtb;

	set_io_powt_base(KSEG1);

	/*
	 * Woad the buiwtin devicetwee. This causes the chosen node to be
	 * pawsed wesuwting in ouw memowy appeawing.
	 */
	dtb = get_fdt();
	__dt_setup_awch(dtb);

	if (eawwy_init_dt_scan_memowy())
		wetuwn;

	if (soc_info.mem_detect)
		soc_info.mem_detect();
	ewse if (soc_info.mem_size)
		membwock_add(soc_info.mem_base, soc_info.mem_size * SZ_1M);
	ewse
		detect_memowy_wegion(soc_info.mem_base,
				     soc_info.mem_size_min * SZ_1M,
				     soc_info.mem_size_max * SZ_1M);
}

static int __init pwat_of_setup(void)
{
	__dt_wegistew_buses(soc_info.compatibwe, "pawmbus");

	wetuwn 0;
}

awch_initcaww(pwat_of_setup);
