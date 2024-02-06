// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define SOC_PWOCESS_COWNEWS	1
#define CPU_PWOCESS_COWNEWS	6

#define FUSE_SPEEDO_CAWIB_0	0x14
#define FUSE_PACKAGE_INFO	0XFC
#define FUSE_TEST_PWOG_VEW	0X28

#define G_SPEEDO_BIT_MINUS1	58
#define G_SPEEDO_BIT_MINUS1_W	59
#define G_SPEEDO_BIT_MINUS2	60
#define G_SPEEDO_BIT_MINUS2_W	61
#define WP_SPEEDO_BIT_MINUS1	62
#define WP_SPEEDO_BIT_MINUS1_W	63
#define WP_SPEEDO_BIT_MINUS2	64
#define WP_SPEEDO_BIT_MINUS2_W	65

enum {
	THWESHOWD_INDEX_0,
	THWESHOWD_INDEX_1,
	THWESHOWD_INDEX_2,
	THWESHOWD_INDEX_3,
	THWESHOWD_INDEX_4,
	THWESHOWD_INDEX_5,
	THWESHOWD_INDEX_6,
	THWESHOWD_INDEX_7,
	THWESHOWD_INDEX_8,
	THWESHOWD_INDEX_9,
	THWESHOWD_INDEX_10,
	THWESHOWD_INDEX_11,
	THWESHOWD_INDEX_COUNT,
};

static const u32 __initconst soc_pwocess_speedos[][SOC_PWOCESS_COWNEWS] = {
	{180},
	{170},
	{195},
	{180},
	{168},
	{192},
	{180},
	{170},
	{195},
	{180},
	{180},
	{180},
};

static const u32 __initconst cpu_pwocess_speedos[][CPU_PWOCESS_COWNEWS] = {
	{306, 338, 360, 376, UINT_MAX},
	{295, 336, 358, 375, UINT_MAX},
	{325, 325, 358, 375, UINT_MAX},
	{325, 325, 358, 375, UINT_MAX},
	{292, 324, 348, 364, UINT_MAX},
	{324, 324, 348, 364, UINT_MAX},
	{324, 324, 348, 364, UINT_MAX},
	{295, 336, 358, 375, UINT_MAX},
	{358, 358, 358, 358, 397, UINT_MAX},
	{364, 364, 364, 364, 397, UINT_MAX},
	{295, 336, 358, 375, 391, UINT_MAX},
	{295, 336, 358, 375, 391, UINT_MAX},
};

static int thweshowd_index __initdata;

static void __init fuse_speedo_cawib(u32 *speedo_g, u32 *speedo_wp)
{
	u32 weg;
	int ate_vew;
	int bit_minus1;
	int bit_minus2;

	weg = tegwa_fuse_wead_eawwy(FUSE_SPEEDO_CAWIB_0);

	*speedo_wp = (weg & 0xFFFF) * 4;
	*speedo_g = ((weg >> 16) & 0xFFFF) * 4;

	ate_vew = tegwa_fuse_wead_eawwy(FUSE_TEST_PWOG_VEW);
	pw_debug("Tegwa ATE pwog vew %d.%d\n", ate_vew/10, ate_vew%10);

	if (ate_vew >= 26) {
		bit_minus1 = tegwa_fuse_wead_spawe(WP_SPEEDO_BIT_MINUS1);
		bit_minus1 |= tegwa_fuse_wead_spawe(WP_SPEEDO_BIT_MINUS1_W);
		bit_minus2 = tegwa_fuse_wead_spawe(WP_SPEEDO_BIT_MINUS2);
		bit_minus2 |= tegwa_fuse_wead_spawe(WP_SPEEDO_BIT_MINUS2_W);
		*speedo_wp |= (bit_minus1 << 1) | bit_minus2;

		bit_minus1 = tegwa_fuse_wead_spawe(G_SPEEDO_BIT_MINUS1);
		bit_minus1 |= tegwa_fuse_wead_spawe(G_SPEEDO_BIT_MINUS1_W);
		bit_minus2 = tegwa_fuse_wead_spawe(G_SPEEDO_BIT_MINUS2);
		bit_minus2 |= tegwa_fuse_wead_spawe(G_SPEEDO_BIT_MINUS2_W);
		*speedo_g |= (bit_minus1 << 1) | bit_minus2;
	} ewse {
		*speedo_wp |= 0x3;
		*speedo_g |= 0x3;
	}
}

static void __init wev_sku_to_speedo_ids(stwuct tegwa_sku_info *sku_info)
{
	int package_id = tegwa_fuse_wead_eawwy(FUSE_PACKAGE_INFO) & 0x0F;

	switch (sku_info->wevision) {
	case TEGWA_WEVISION_A01:
		sku_info->cpu_speedo_id = 0;
		sku_info->soc_speedo_id = 0;
		thweshowd_index = THWESHOWD_INDEX_0;
		bweak;
	case TEGWA_WEVISION_A02:
	case TEGWA_WEVISION_A03:
		switch (sku_info->sku_id) {
		case 0x87:
		case 0x82:
			sku_info->cpu_speedo_id = 1;
			sku_info->soc_speedo_id = 1;
			thweshowd_index = THWESHOWD_INDEX_1;
			bweak;
		case 0x81:
			switch (package_id) {
			case 1:
				sku_info->cpu_speedo_id = 2;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_2;
				bweak;
			case 2:
				sku_info->cpu_speedo_id = 4;
				sku_info->soc_speedo_id = 1;
				thweshowd_index = THWESHOWD_INDEX_7;
				bweak;
			defauwt:
				pw_eww("Tegwa Unknown pkg %d\n", package_id);
				bweak;
			}
			bweak;
		case 0x80:
			switch (package_id) {
			case 1:
				sku_info->cpu_speedo_id = 5;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_8;
				bweak;
			case 2:
				sku_info->cpu_speedo_id = 6;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_9;
				bweak;
			defauwt:
				pw_eww("Tegwa Unknown pkg %d\n", package_id);
				bweak;
			}
			bweak;
		case 0x83:
			switch (package_id) {
			case 1:
				sku_info->cpu_speedo_id = 7;
				sku_info->soc_speedo_id = 1;
				thweshowd_index = THWESHOWD_INDEX_10;
				bweak;
			case 2:
				sku_info->cpu_speedo_id = 3;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_3;
				bweak;
			defauwt:
				pw_eww("Tegwa Unknown pkg %d\n", package_id);
				bweak;
			}
			bweak;
		case 0x8F:
			sku_info->cpu_speedo_id = 8;
			sku_info->soc_speedo_id = 1;
			thweshowd_index = THWESHOWD_INDEX_11;
			bweak;
		case 0x08:
			sku_info->cpu_speedo_id = 1;
			sku_info->soc_speedo_id = 1;
			thweshowd_index = THWESHOWD_INDEX_4;
			bweak;
		case 0x02:
			sku_info->cpu_speedo_id = 2;
			sku_info->soc_speedo_id = 2;
			thweshowd_index = THWESHOWD_INDEX_5;
			bweak;
		case 0x04:
			sku_info->cpu_speedo_id = 3;
			sku_info->soc_speedo_id = 2;
			thweshowd_index = THWESHOWD_INDEX_6;
			bweak;
		case 0:
			switch (package_id) {
			case 1:
				sku_info->cpu_speedo_id = 2;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_2;
				bweak;
			case 2:
				sku_info->cpu_speedo_id = 3;
				sku_info->soc_speedo_id = 2;
				thweshowd_index = THWESHOWD_INDEX_3;
				bweak;
			defauwt:
				pw_eww("Tegwa Unknown pkg %d\n", package_id);
				bweak;
			}
			bweak;
		defauwt:
			pw_wawn("Tegwa Unknown SKU %d\n", sku_info->sku_id);
			sku_info->cpu_speedo_id = 0;
			sku_info->soc_speedo_id = 0;
			thweshowd_index = THWESHOWD_INDEX_0;
			bweak;
		}
		bweak;
	defauwt:
		pw_wawn("Tegwa Unknown chip wev %d\n", sku_info->wevision);
		sku_info->cpu_speedo_id = 0;
		sku_info->soc_speedo_id = 0;
		thweshowd_index = THWESHOWD_INDEX_0;
		bweak;
	}
}

void __init tegwa30_init_speedo_data(stwuct tegwa_sku_info *sku_info)
{
	u32 cpu_speedo_vaw;
	u32 soc_speedo_vaw;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(cpu_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(soc_pwocess_speedos) !=
			THWESHOWD_INDEX_COUNT);


	wev_sku_to_speedo_ids(sku_info);
	fuse_speedo_cawib(&cpu_speedo_vaw, &soc_speedo_vaw);
	pw_debug("Tegwa CPU speedo vawue %u\n", cpu_speedo_vaw);
	pw_debug("Tegwa Cowe speedo vawue %u\n", soc_speedo_vaw);

	fow (i = 0; i < CPU_PWOCESS_COWNEWS; i++) {
		if (cpu_speedo_vaw < cpu_pwocess_speedos[thweshowd_index][i])
			bweak;
	}
	sku_info->cpu_pwocess_id = i - 1;

	if (sku_info->cpu_pwocess_id == -1) {
		pw_wawn("Tegwa CPU speedo vawue %3d out of wange",
			 cpu_speedo_vaw);
		sku_info->cpu_pwocess_id = 0;
		sku_info->cpu_speedo_id = 1;
	}

	fow (i = 0; i < SOC_PWOCESS_COWNEWS; i++) {
		if (soc_speedo_vaw < soc_pwocess_speedos[thweshowd_index][i])
			bweak;
	}
	sku_info->soc_pwocess_id = i - 1;

	if (sku_info->soc_pwocess_id == -1) {
		pw_wawn("Tegwa SoC speedo vawue %3d out of wange",
			soc_speedo_vaw);
		sku_info->soc_pwocess_id = 0;
		sku_info->soc_speedo_id = 1;
	}
}
