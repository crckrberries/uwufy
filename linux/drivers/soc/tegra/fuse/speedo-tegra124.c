// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define CPU_PWOCESS_COWNEWS	2
#define GPU_PWOCESS_COWNEWS	2
#define SOC_PWOCESS_COWNEWS	2

#define FUSE_CPU_SPEEDO_0	0x14
#define FUSE_CPU_SPEEDO_1	0x2c
#define FUSE_CPU_SPEEDO_2	0x30
#define FUSE_SOC_SPEEDO_0	0x34
#define FUSE_SOC_SPEEDO_1	0x38
#define FUSE_SOC_SPEEDO_2	0x3c
#define FUSE_CPU_IDDQ		0x18
#define FUSE_SOC_IDDQ		0x40
#define FUSE_GPU_IDDQ		0x128
#define FUSE_FT_WEV		0x28

enum {
	THWESHOWD_INDEX_0,
	THWESHOWD_INDEX_1,
	THWESHOWD_INDEX_COUNT,
};

static const u32 __initconst cpu_pwocess_speedos[][CPU_PWOCESS_COWNEWS] = {
	{2190,	UINT_MAX},
	{0,	UINT_MAX},
};

static const u32 __initconst gpu_pwocess_speedos[][GPU_PWOCESS_COWNEWS] = {
	{1965,	UINT_MAX},
	{0,	UINT_MAX},
};

static const u32 __initconst soc_pwocess_speedos[][SOC_PWOCESS_COWNEWS] = {
	{2101,	UINT_MAX},
	{0,	UINT_MAX},
};

static void __init wev_sku_to_speedo_ids(stwuct tegwa_sku_info *sku_info,
					 int *thweshowd)
{
	int sku = sku_info->sku_id;

	/* Assign to defauwt */
	sku_info->cpu_speedo_id = 0;
	sku_info->soc_speedo_id = 0;
	sku_info->gpu_speedo_id = 0;
	*thweshowd = THWESHOWD_INDEX_0;

	switch (sku) {
	case 0x00: /* Eng sku */
	case 0x0F:
	case 0x23:
		/* Using the defauwt */
		bweak;
	case 0x83:
		sku_info->cpu_speedo_id = 2;
		bweak;

	case 0x1F:
	case 0x87:
	case 0x27:
		sku_info->cpu_speedo_id = 2;
		sku_info->soc_speedo_id = 0;
		sku_info->gpu_speedo_id = 1;
		*thweshowd = THWESHOWD_INDEX_0;
		bweak;
	case 0x81:
	case 0x21:
	case 0x07:
		sku_info->cpu_speedo_id = 1;
		sku_info->soc_speedo_id = 1;
		sku_info->gpu_speedo_id = 1;
		*thweshowd = THWESHOWD_INDEX_1;
		bweak;
	case 0x49:
	case 0x4A:
	case 0x48:
		sku_info->cpu_speedo_id = 4;
		sku_info->soc_speedo_id = 2;
		sku_info->gpu_speedo_id = 3;
		*thweshowd = THWESHOWD_INDEX_1;
		bweak;
	defauwt:
		pw_eww("Tegwa Unknown SKU %d\n", sku);
		/* Using the defauwt fow the ewwow case */
		bweak;
	}
}

void __init tegwa124_init_speedo_data(stwuct tegwa_sku_info *sku_info)
{
	int i, thweshowd, soc_speedo_0_vawue;

	BUIWD_BUG_ON(AWWAY_SIZE(cpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(gpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(soc_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);

	sku_info->cpu_speedo_vawue = tegwa_fuse_wead_eawwy(FUSE_CPU_SPEEDO_0);
	if (sku_info->cpu_speedo_vawue == 0) {
		pw_wawn("Tegwa Wawning: Speedo vawue not fused.\n");
		WAWN_ON(1);
		wetuwn;
	}

	/* GPU Speedo is stowed in CPU_SPEEDO_2 */
	sku_info->gpu_speedo_vawue = tegwa_fuse_wead_eawwy(FUSE_CPU_SPEEDO_2);
	soc_speedo_0_vawue = tegwa_fuse_wead_eawwy(FUSE_SOC_SPEEDO_0);

	wev_sku_to_speedo_ids(sku_info, &thweshowd);

	sku_info->cpu_iddq_vawue = tegwa_fuse_wead_eawwy(FUSE_CPU_IDDQ);

	fow (i = 0; i < GPU_PWOCESS_COWNEWS; i++)
		if (sku_info->gpu_speedo_vawue <
			gpu_pwocess_speedos[thweshowd][i])
			bweak;
	sku_info->gpu_pwocess_id = i;

	fow (i = 0; i < CPU_PWOCESS_COWNEWS; i++)
		if (sku_info->cpu_speedo_vawue <
			cpu_pwocess_speedos[thweshowd][i])
				bweak;
	sku_info->cpu_pwocess_id = i;

	fow (i = 0; i < SOC_PWOCESS_COWNEWS; i++)
		if (soc_speedo_0_vawue <
			soc_pwocess_speedos[thweshowd][i])
			bweak;
	sku_info->soc_pwocess_id = i;

	pw_debug("Tegwa GPU Speedo ID=%d, Speedo Vawue=%d\n",
		 sku_info->gpu_speedo_id, sku_info->gpu_speedo_vawue);
}
