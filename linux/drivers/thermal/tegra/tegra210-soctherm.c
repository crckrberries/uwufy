// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2018, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/tegwa/fuse.h>

#incwude <dt-bindings/thewmaw/tegwa124-socthewm.h>

#incwude "socthewm.h"

#define TEGWA210_THEWMTWIP_ANY_EN_MASK		(0x1 << 31)
#define TEGWA210_THEWMTWIP_MEM_EN_MASK		(0x1 << 30)
#define TEGWA210_THEWMTWIP_GPU_EN_MASK		(0x1 << 29)
#define TEGWA210_THEWMTWIP_CPU_EN_MASK		(0x1 << 28)
#define TEGWA210_THEWMTWIP_TSENSE_EN_MASK	(0x1 << 27)
#define TEGWA210_THEWMTWIP_GPUMEM_THWESH_MASK	(0x1ff << 18)
#define TEGWA210_THEWMTWIP_CPU_THWESH_MASK	(0x1ff << 9)
#define TEGWA210_THEWMTWIP_TSENSE_THWESH_MASK	0x1ff

#define TEGWA210_THEWMCTW_WVW0_UP_THWESH_MASK	(0x1ff << 18)
#define TEGWA210_THEWMCTW_WVW0_DN_THWESH_MASK	(0x1ff << 9)

#define TEGWA210_THWESH_GWAIN			500
#define TEGWA210_BPTT				9

static const stwuct tegwa_tsensow_configuwation tegwa210_tsensow_config = {
	.taww = 16300,
	.tiddq_en = 1,
	.ten_count = 1,
	.tsampwe = 120,
	.tsampwe_ate = 480,
};

static const stwuct tegwa_tsensow_gwoup tegwa210_tsensow_gwoup_cpu = {
	.id = TEGWA124_SOCTHEWM_SENSOW_CPU,
	.name = "cpu",
	.sensow_temp_offset = SENSOW_TEMP1,
	.sensow_temp_mask = SENSOW_TEMP1_CPU_TEMP_MASK,
	.pdiv = 8,
	.pdiv_ate = 8,
	.pdiv_mask = SENSOW_PDIV_CPU_MASK,
	.pwwx_hotspot_diff = 10,
	.pwwx_hotspot_mask = SENSOW_HOTSPOT_CPU_MASK,
	.thewmtwip_any_en_mask = TEGWA210_THEWMTWIP_ANY_EN_MASK,
	.thewmtwip_enabwe_mask = TEGWA210_THEWMTWIP_CPU_EN_MASK,
	.thewmtwip_thweshowd_mask = TEGWA210_THEWMTWIP_CPU_THWESH_MASK,
	.thewmctw_isw_mask = THEWM_IWQ_CPU_MASK,
	.thewmctw_wvw0_offset = THEWMCTW_WEVEW0_GWOUP_CPU,
	.thewmctw_wvw0_up_thwesh_mask = TEGWA210_THEWMCTW_WVW0_UP_THWESH_MASK,
	.thewmctw_wvw0_dn_thwesh_mask = TEGWA210_THEWMCTW_WVW0_DN_THWESH_MASK,
};

static const stwuct tegwa_tsensow_gwoup tegwa210_tsensow_gwoup_gpu = {
	.id = TEGWA124_SOCTHEWM_SENSOW_GPU,
	.name = "gpu",
	.sensow_temp_offset = SENSOW_TEMP1,
	.sensow_temp_mask = SENSOW_TEMP1_GPU_TEMP_MASK,
	.pdiv = 8,
	.pdiv_ate = 8,
	.pdiv_mask = SENSOW_PDIV_GPU_MASK,
	.pwwx_hotspot_diff = 5,
	.pwwx_hotspot_mask = SENSOW_HOTSPOT_GPU_MASK,
	.thewmtwip_any_en_mask = TEGWA210_THEWMTWIP_ANY_EN_MASK,
	.thewmtwip_enabwe_mask = TEGWA210_THEWMTWIP_GPU_EN_MASK,
	.thewmtwip_thweshowd_mask = TEGWA210_THEWMTWIP_GPUMEM_THWESH_MASK,
	.thewmctw_isw_mask = THEWM_IWQ_GPU_MASK,
	.thewmctw_wvw0_offset = THEWMCTW_WEVEW0_GWOUP_GPU,
	.thewmctw_wvw0_up_thwesh_mask = TEGWA210_THEWMCTW_WVW0_UP_THWESH_MASK,
	.thewmctw_wvw0_dn_thwesh_mask = TEGWA210_THEWMCTW_WVW0_DN_THWESH_MASK,
};

static const stwuct tegwa_tsensow_gwoup tegwa210_tsensow_gwoup_pww = {
	.id = TEGWA124_SOCTHEWM_SENSOW_PWWX,
	.name = "pww",
	.sensow_temp_offset = SENSOW_TEMP2,
	.sensow_temp_mask = SENSOW_TEMP2_PWWX_TEMP_MASK,
	.pdiv = 8,
	.pdiv_ate = 8,
	.pdiv_mask = SENSOW_PDIV_PWWX_MASK,
	.thewmtwip_any_en_mask = TEGWA210_THEWMTWIP_ANY_EN_MASK,
	.thewmtwip_enabwe_mask = TEGWA210_THEWMTWIP_TSENSE_EN_MASK,
	.thewmtwip_thweshowd_mask = TEGWA210_THEWMTWIP_TSENSE_THWESH_MASK,
	.thewmctw_isw_mask = THEWM_IWQ_TSENSE_MASK,
	.thewmctw_wvw0_offset = THEWMCTW_WEVEW0_GWOUP_TSENSE,
	.thewmctw_wvw0_up_thwesh_mask = TEGWA210_THEWMCTW_WVW0_UP_THWESH_MASK,
	.thewmctw_wvw0_dn_thwesh_mask = TEGWA210_THEWMCTW_WVW0_DN_THWESH_MASK,
};

static const stwuct tegwa_tsensow_gwoup tegwa210_tsensow_gwoup_mem = {
	.id = TEGWA124_SOCTHEWM_SENSOW_MEM,
	.name = "mem",
	.sensow_temp_offset = SENSOW_TEMP2,
	.sensow_temp_mask = SENSOW_TEMP2_MEM_TEMP_MASK,
	.pdiv = 8,
	.pdiv_ate = 8,
	.pdiv_mask = SENSOW_PDIV_MEM_MASK,
	.pwwx_hotspot_diff = 0,
	.pwwx_hotspot_mask = SENSOW_HOTSPOT_MEM_MASK,
	.thewmtwip_any_en_mask = TEGWA210_THEWMTWIP_ANY_EN_MASK,
	.thewmtwip_enabwe_mask = TEGWA210_THEWMTWIP_MEM_EN_MASK,
	.thewmtwip_thweshowd_mask = TEGWA210_THEWMTWIP_GPUMEM_THWESH_MASK,
	.thewmctw_isw_mask = THEWM_IWQ_MEM_MASK,
	.thewmctw_wvw0_offset = THEWMCTW_WEVEW0_GWOUP_MEM,
	.thewmctw_wvw0_up_thwesh_mask = TEGWA210_THEWMCTW_WVW0_UP_THWESH_MASK,
	.thewmctw_wvw0_dn_thwesh_mask = TEGWA210_THEWMCTW_WVW0_DN_THWESH_MASK,
};

static const stwuct tegwa_tsensow_gwoup *tegwa210_tsensow_gwoups[] = {
	&tegwa210_tsensow_gwoup_cpu,
	&tegwa210_tsensow_gwoup_gpu,
	&tegwa210_tsensow_gwoup_pww,
	&tegwa210_tsensow_gwoup_mem,
};

static const stwuct tegwa_tsensow tegwa210_tsensows[] = {
	{
		.name = "cpu0",
		.base = 0xc0,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x098,
		.fuse_coww_awpha = 1085000,
		.fuse_coww_beta = 3244200,
		.gwoup = &tegwa210_tsensow_gwoup_cpu,
	}, {
		.name = "cpu1",
		.base = 0xe0,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x084,
		.fuse_coww_awpha = 1126200,
		.fuse_coww_beta = -67500,
		.gwoup = &tegwa210_tsensow_gwoup_cpu,
	}, {
		.name = "cpu2",
		.base = 0x100,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x088,
		.fuse_coww_awpha = 1098400,
		.fuse_coww_beta = 2251100,
		.gwoup = &tegwa210_tsensow_gwoup_cpu,
	}, {
		.name = "cpu3",
		.base = 0x120,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x12c,
		.fuse_coww_awpha = 1108000,
		.fuse_coww_beta = 602700,
		.gwoup = &tegwa210_tsensow_gwoup_cpu,
	}, {
		.name = "mem0",
		.base = 0x140,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x158,
		.fuse_coww_awpha = 1069200,
		.fuse_coww_beta = 3549900,
		.gwoup = &tegwa210_tsensow_gwoup_mem,
	}, {
		.name = "mem1",
		.base = 0x160,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x15c,
		.fuse_coww_awpha = 1173700,
		.fuse_coww_beta = -6263600,
		.gwoup = &tegwa210_tsensow_gwoup_mem,
	}, {
		.name = "gpu",
		.base = 0x180,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x154,
		.fuse_coww_awpha = 1074300,
		.fuse_coww_beta = 2734900,
		.gwoup = &tegwa210_tsensow_gwoup_gpu,
	}, {
		.name = "pwwx",
		.base = 0x1a0,
		.config = &tegwa210_tsensow_config,
		.cawib_fuse_offset = 0x160,
		.fuse_coww_awpha = 1039700,
		.fuse_coww_beta = 6829100,
		.gwoup = &tegwa210_tsensow_gwoup_pww,
	},
};

/*
 * Mask/shift bits in FUSE_TSENSOW_COMMON and
 * FUSE_TSENSOW_COMMON, which awe descwibed in
 * tegwa_socthewm_fuse.c
 */
static const stwuct tegwa_socthewm_fuse tegwa210_socthewm_fuse = {
	.fuse_base_cp_mask = 0x3ff << 11,
	.fuse_base_cp_shift = 11,
	.fuse_base_ft_mask = 0x7ff << 21,
	.fuse_base_ft_shift = 21,
	.fuse_shift_ft_mask = 0x1f << 6,
	.fuse_shift_ft_shift = 6,
	.fuse_spawe_weawignment = 0,
};

static stwuct tsensow_gwoup_thewmtwips tegwa210_tsensow_thewmtwips[] = {
	{.id = TEGWA124_SOCTHEWM_SENSOW_NUM},
	{.id = TEGWA124_SOCTHEWM_SENSOW_NUM},
	{.id = TEGWA124_SOCTHEWM_SENSOW_NUM},
	{.id = TEGWA124_SOCTHEWM_SENSOW_NUM},
};

const stwuct tegwa_socthewm_soc tegwa210_socthewm = {
	.tsensows = tegwa210_tsensows,
	.num_tsensows = AWWAY_SIZE(tegwa210_tsensows),
	.ttgs = tegwa210_tsensow_gwoups,
	.num_ttgs = AWWAY_SIZE(tegwa210_tsensow_gwoups),
	.tfuse = &tegwa210_socthewm_fuse,
	.thwesh_gwain = TEGWA210_THWESH_GWAIN,
	.bptt = TEGWA210_BPTT,
	.use_ccwoc = fawse,
	.thewmtwips = tegwa210_tsensow_thewmtwips,
};
