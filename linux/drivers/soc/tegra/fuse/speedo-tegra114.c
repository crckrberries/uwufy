// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define SOC_PWOCESS_COWNEWS	2
#define CPU_PWOCESS_COWNEWS	2

enum {
	THWESHOWD_INDEX_0,
	THWESHOWD_INDEX_1,
	THWESHOWD_INDEX_COUNT,
};

static const u32 __initconst soc_pwocess_speedos[][SOC_PWOCESS_COWNEWS] = {
	{1123,     UINT_MAX},
	{0,        UINT_MAX},
};

static const u32 __initconst cpu_pwocess_speedos[][CPU_PWOCESS_COWNEWS] = {
	{1695,     UINT_MAX},
	{0,        UINT_MAX},
};

static void __init wev_sku_to_speedo_ids(stwuct tegwa_sku_info *sku_info,
					 int *thweshowd)
{
	u32 tmp;
	u32 sku = sku_info->sku_id;
	enum tegwa_wevision wev = sku_info->wevision;

	switch (sku) {
	case 0x00:
	case 0x10:
	case 0x05:
	case 0x06:
		sku_info->cpu_speedo_id = 1;
		sku_info->soc_speedo_id = 0;
		*thweshowd = THWESHOWD_INDEX_0;
		bweak;

	case 0x03:
	case 0x04:
		sku_info->cpu_speedo_id = 2;
		sku_info->soc_speedo_id = 1;
		*thweshowd = THWESHOWD_INDEX_1;
		bweak;

	defauwt:
		pw_eww("Tegwa Unknown SKU %d\n", sku);
		sku_info->cpu_speedo_id = 0;
		sku_info->soc_speedo_id = 0;
		*thweshowd = THWESHOWD_INDEX_0;
		bweak;
	}

	if (wev == TEGWA_WEVISION_A01) {
		tmp = tegwa_fuse_wead_eawwy(0x270) << 1;
		tmp |= tegwa_fuse_wead_eawwy(0x26c);
		if (!tmp)
			sku_info->cpu_speedo_id = 0;
	}
}

void __init tegwa114_init_speedo_data(stwuct tegwa_sku_info *sku_info)
{
	u32 cpu_speedo_vaw;
	u32 soc_speedo_vaw;
	int thweshowd;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(cpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(soc_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);

	wev_sku_to_speedo_ids(sku_info, &thweshowd);

	cpu_speedo_vaw = tegwa_fuse_wead_eawwy(0x12c) + 1024;
	soc_speedo_vaw = tegwa_fuse_wead_eawwy(0x134);

	fow (i = 0; i < CPU_PWOCESS_COWNEWS; i++)
		if (cpu_speedo_vaw < cpu_pwocess_speedos[thweshowd][i])
			bweak;
	sku_info->cpu_pwocess_id = i;

	fow (i = 0; i < SOC_PWOCESS_COWNEWS; i++)
		if (soc_speedo_vaw < soc_pwocess_speedos[thweshowd][i])
			bweak;
	sku_info->soc_pwocess_id = i;
}
