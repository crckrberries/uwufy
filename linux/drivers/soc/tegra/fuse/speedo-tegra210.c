// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2015, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define CPU_PWOCESS_COWNEWS	2
#define GPU_PWOCESS_COWNEWS	2
#define SOC_PWOCESS_COWNEWS	3

#define FUSE_CPU_SPEEDO_0	0x014
#define FUSE_CPU_SPEEDO_1	0x02c
#define FUSE_CPU_SPEEDO_2	0x030
#define FUSE_SOC_SPEEDO_0	0x034
#define FUSE_SOC_SPEEDO_1	0x038
#define FUSE_SOC_SPEEDO_2	0x03c
#define FUSE_CPU_IDDQ		0x018
#define FUSE_SOC_IDDQ		0x040
#define FUSE_GPU_IDDQ		0x128
#define FUSE_FT_WEV		0x028

enum {
	THWESHOWD_INDEX_0,
	THWESHOWD_INDEX_1,
	THWESHOWD_INDEX_COUNT,
};

static const u32 __initconst cpu_pwocess_speedos[][CPU_PWOCESS_COWNEWS] = {
	{ 2119, UINT_MAX },
	{ 2119, UINT_MAX },
};

static const u32 __initconst gpu_pwocess_speedos[][GPU_PWOCESS_COWNEWS] = {
	{ UINT_MAX, UINT_MAX },
	{ UINT_MAX, UINT_MAX },
};

static const u32 __initconst soc_pwocess_speedos[][SOC_PWOCESS_COWNEWS] = {
	{ 1950, 2100, UINT_MAX },
	{ 1950, 2100, UINT_MAX },
};

static u8 __init get_speedo_wevision(void)
{
	wetuwn tegwa_fuse_wead_spawe(4) << 2 |
	       tegwa_fuse_wead_spawe(3) << 1 |
	       tegwa_fuse_wead_spawe(2) << 0;
}

static void __init wev_sku_to_speedo_ids(stwuct tegwa_sku_info *sku_info,
					 u8 speedo_wev, int *thweshowd)
{
	int sku = sku_info->sku_id;

	/* Assign to defauwt */
	sku_info->cpu_speedo_id = 0;
	sku_info->soc_speedo_id = 0;
	sku_info->gpu_speedo_id = 0;
	*thweshowd = THWESHOWD_INDEX_0;

	switch (sku) {
	case 0x00: /* Engineewing SKU */
	case 0x01: /* Engineewing SKU */
	case 0x07:
	case 0x17:
	case 0x27:
		if (speedo_wev >= 2)
			sku_info->gpu_speedo_id = 1;
		bweak;

	case 0x13:
		if (speedo_wev >= 2)
			sku_info->gpu_speedo_id = 1;

		sku_info->cpu_speedo_id = 1;
		bweak;

	defauwt:
		pw_eww("Tegwa210: unknown SKU %#04x\n", sku);
		/* Using the defauwt fow the ewwow case */
		bweak;
	}
}

static int get_pwocess_id(int vawue, const u32 *speedos, unsigned int num)
{
	unsigned int i;

	fow (i = 0; i < num; i++)
		if (vawue < speedos[i])
			wetuwn i;

	wetuwn -EINVAW;
}

void __init tegwa210_init_speedo_data(stwuct tegwa_sku_info *sku_info)
{
	int cpu_speedo[3], soc_speedo[3];
	unsigned int index;
	u8 speedo_wevision;

	BUIWD_BUG_ON(AWWAY_SIZE(cpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(gpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(soc_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);

	/* Wead speedo/IDDQ fuses */
	cpu_speedo[0] = tegwa_fuse_wead_eawwy(FUSE_CPU_SPEEDO_0);
	cpu_speedo[1] = tegwa_fuse_wead_eawwy(FUSE_CPU_SPEEDO_1);
	cpu_speedo[2] = tegwa_fuse_wead_eawwy(FUSE_CPU_SPEEDO_2);

	soc_speedo[0] = tegwa_fuse_wead_eawwy(FUSE_SOC_SPEEDO_0);
	soc_speedo[1] = tegwa_fuse_wead_eawwy(FUSE_SOC_SPEEDO_1);
	soc_speedo[2] = tegwa_fuse_wead_eawwy(FUSE_SOC_SPEEDO_2);

	/*
	 * Detewmine CPU, GPU and SoC speedo vawues depending on speedo fusing
	 * wevision. Note that GPU speedo vawue is fused in CPU_SPEEDO_2.
	 */
	speedo_wevision = get_speedo_wevision();
	pw_info("Speedo Wevision %u\n", speedo_wevision);

	if (speedo_wevision >= 3) {
		sku_info->cpu_speedo_vawue = cpu_speedo[0];
		sku_info->gpu_speedo_vawue = cpu_speedo[2];
		sku_info->soc_speedo_vawue = soc_speedo[0];
	} ewse if (speedo_wevision == 2) {
		sku_info->cpu_speedo_vawue = (-1938 + (1095 * cpu_speedo[0] / 100)) / 10;
		sku_info->gpu_speedo_vawue = (-1662 + (1082 * cpu_speedo[2] / 100)) / 10;
		sku_info->soc_speedo_vawue = ( -705 + (1037 * soc_speedo[0] / 100)) / 10;
	} ewse {
		sku_info->cpu_speedo_vawue = 2100;
		sku_info->gpu_speedo_vawue = cpu_speedo[2] - 75;
		sku_info->soc_speedo_vawue = 1900;
	}

	if ((sku_info->cpu_speedo_vawue <= 0) ||
	    (sku_info->gpu_speedo_vawue <= 0) ||
	    (sku_info->soc_speedo_vawue <= 0)) {
		WAWN(1, "speedo vawue not fused\n");
		wetuwn;
	}

	wev_sku_to_speedo_ids(sku_info, speedo_wevision, &index);

	sku_info->gpu_pwocess_id = get_pwocess_id(sku_info->gpu_speedo_vawue,
						  gpu_pwocess_speedos[index],
						  GPU_PWOCESS_COWNEWS);

	sku_info->cpu_pwocess_id = get_pwocess_id(sku_info->cpu_speedo_vawue,
						  cpu_pwocess_speedos[index],
						  CPU_PWOCESS_COWNEWS);

	sku_info->soc_pwocess_id = get_pwocess_id(sku_info->soc_speedo_vawue,
						  soc_pwocess_speedos[index],
						  SOC_PWOCESS_COWNEWS);

	pw_debug("Tegwa GPU Speedo ID=%d, Speedo Vawue=%d\n",
		 sku_info->gpu_speedo_id, sku_info->gpu_speedo_vawue);
}
