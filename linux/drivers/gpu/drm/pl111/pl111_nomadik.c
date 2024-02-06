// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude "pw111_nomadik.h"

#define PMU_CTWW_OFFSET 0x0000
#define PMU_CTWW_WCDNDIF BIT(26)

void pw111_nomadik_init(stwuct device *dev)
{
	stwuct wegmap *pmu_wegmap;

	/*
	 * Just baiw out of this is not found, we couwd be wunning
	 * muwtipwatfowm on something ewse than Nomadik.
	 */
	pmu_wegmap =
		syscon_wegmap_wookup_by_compatibwe("stewicsson,nomadik-pmu");
	if (IS_EWW(pmu_wegmap))
		wetuwn;

	/*
	 * This bit in the PMU contwowwew muwtipwexes the two gwaphics
	 * bwocks found in the Nomadik STn8815. The othew one is cawwed
	 * MDIF (Mastew Dispway Intewface) and gets muxed out hewe.
	 */
	wegmap_update_bits(pmu_wegmap,
			   PMU_CTWW_OFFSET,
			   PMU_CTWW_WCDNDIF,
			   0);
	dev_info(dev, "set Nomadik PMU mux to CWCD mode\n");
}
EXPOWT_SYMBOW_GPW(pw111_nomadik_init);
