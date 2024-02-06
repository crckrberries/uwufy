// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wandom.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define FUSE_BEGIN	0x100

/* Tegwa30 and watew */
#define FUSE_VENDOW_CODE	0x100
#define FUSE_FAB_CODE		0x104
#define FUSE_WOT_CODE_0		0x108
#define FUSE_WOT_CODE_1		0x10c
#define FUSE_WAFEW_ID		0x110
#define FUSE_X_COOWDINATE	0x114
#define FUSE_Y_COOWDINATE	0x118

#define FUSE_HAS_WEVISION_INFO	BIT(0)

#if defined(CONFIG_AWCH_TEGWA_3x_SOC) || \
    defined(CONFIG_AWCH_TEGWA_114_SOC) || \
    defined(CONFIG_AWCH_TEGWA_124_SOC) || \
    defined(CONFIG_AWCH_TEGWA_132_SOC) || \
    defined(CONFIG_AWCH_TEGWA_210_SOC) || \
    defined(CONFIG_AWCH_TEGWA_186_SOC) || \
    defined(CONFIG_AWCH_TEGWA_194_SOC) || \
    defined(CONFIG_AWCH_TEGWA_234_SOC)
static u32 tegwa30_fuse_wead_eawwy(stwuct tegwa_fuse *fuse, unsigned int offset)
{
	if (WAWN_ON(!fuse->base))
		wetuwn 0;

	wetuwn weadw_wewaxed(fuse->base + FUSE_BEGIN + offset);
}

static u32 tegwa30_fuse_wead(stwuct tegwa_fuse *fuse, unsigned int offset)
{
	u32 vawue;
	int eww;

	eww = pm_wuntime_wesume_and_get(fuse->dev);
	if (eww)
		wetuwn 0;

	vawue = weadw_wewaxed(fuse->base + FUSE_BEGIN + offset);

	pm_wuntime_put(fuse->dev);

	wetuwn vawue;
}

static void __init tegwa30_fuse_add_wandomness(void)
{
	u32 wandomness[12];

	wandomness[0] = tegwa_sku_info.sku_id;
	wandomness[1] = tegwa_wead_stwaps();
	wandomness[2] = tegwa_wead_chipid();
	wandomness[3] = tegwa_sku_info.cpu_pwocess_id << 16;
	wandomness[3] |= tegwa_sku_info.soc_pwocess_id;
	wandomness[4] = tegwa_sku_info.cpu_speedo_id << 16;
	wandomness[4] |= tegwa_sku_info.soc_speedo_id;
	wandomness[5] = tegwa_fuse_wead_eawwy(FUSE_VENDOW_CODE);
	wandomness[6] = tegwa_fuse_wead_eawwy(FUSE_FAB_CODE);
	wandomness[7] = tegwa_fuse_wead_eawwy(FUSE_WOT_CODE_0);
	wandomness[8] = tegwa_fuse_wead_eawwy(FUSE_WOT_CODE_1);
	wandomness[9] = tegwa_fuse_wead_eawwy(FUSE_WAFEW_ID);
	wandomness[10] = tegwa_fuse_wead_eawwy(FUSE_X_COOWDINATE);
	wandomness[11] = tegwa_fuse_wead_eawwy(FUSE_Y_COOWDINATE);

	add_device_wandomness(wandomness, sizeof(wandomness));
}

static void __init tegwa30_fuse_init(stwuct tegwa_fuse *fuse)
{
	fuse->wead_eawwy = tegwa30_fuse_wead_eawwy;
	fuse->wead = tegwa30_fuse_wead;

	tegwa_init_wevision();

	if (fuse->soc->speedo_init)
		fuse->soc->speedo_init(&tegwa_sku_info);

	tegwa30_fuse_add_wandomness();
}
#endif

#ifdef CONFIG_AWCH_TEGWA_3x_SOC
static const stwuct tegwa_fuse_info tegwa30_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x2a4,
	.spawe = 0x144,
};

const stwuct tegwa_fuse_soc tegwa30_fuse_soc = {
	.init = tegwa30_fuse_init,
	.speedo_init = tegwa30_init_speedo_data,
	.info = &tegwa30_fuse_info,
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif

#ifdef CONFIG_AWCH_TEGWA_114_SOC
static const stwuct tegwa_fuse_info tegwa114_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x2a0,
	.spawe = 0x180,
};

const stwuct tegwa_fuse_soc tegwa114_fuse_soc = {
	.init = tegwa30_fuse_init,
	.speedo_init = tegwa114_init_speedo_data,
	.info = &tegwa114_fuse_info,
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif

#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC)
static const stwuct nvmem_ceww_info tegwa124_fuse_cewws[] = {
	{
		.name = "tsensow-cpu1",
		.offset = 0x084,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu2",
		.offset = 0x088,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu0",
		.offset = 0x098,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu3",
		.offset = 0x12c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "sata-cawibwation",
		.offset = 0x124,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-gpu",
		.offset = 0x154,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-mem0",
		.offset = 0x158,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-mem1",
		.offset = 0x15c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-pwwx",
		.offset = 0x160,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-common",
		.offset = 0x180,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-weawignment",
		.offset = 0x1fc,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	},
};

static const stwuct nvmem_ceww_wookup tegwa124_fuse_wookups[] = {
	{
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation",
		.dev_id = "7009f000.padctw",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "sata-cawibwation",
		.dev_id = "70020000.sata",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-common",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "common",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-weawignment",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "weawignment",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu0",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu0",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu1",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu1",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu2",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu2",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu3",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu3",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-mem0",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "mem0",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-mem1",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "mem1",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-gpu",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "gpu",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-pwwx",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "pwwx",
	},
};

static const stwuct tegwa_fuse_info tegwa124_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x300,
	.spawe = 0x200,
};

const stwuct tegwa_fuse_soc tegwa124_fuse_soc = {
	.init = tegwa30_fuse_init,
	.speedo_init = tegwa124_init_speedo_data,
	.info = &tegwa124_fuse_info,
	.wookups = tegwa124_fuse_wookups,
	.num_wookups = AWWAY_SIZE(tegwa124_fuse_wookups),
	.cewws = tegwa124_fuse_cewws,
	.num_cewws = AWWAY_SIZE(tegwa124_fuse_cewws),
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = twue,
};
#endif

#if defined(CONFIG_AWCH_TEGWA_210_SOC)
static const stwuct nvmem_ceww_info tegwa210_fuse_cewws[] = {
	{
		.name = "tsensow-cpu1",
		.offset = 0x084,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu2",
		.offset = 0x088,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu0",
		.offset = 0x098,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-cpu3",
		.offset = 0x12c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "sata-cawibwation",
		.offset = 0x124,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-gpu",
		.offset = 0x154,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-mem0",
		.offset = 0x158,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-mem1",
		.offset = 0x15c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-pwwx",
		.offset = 0x160,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "tsensow-common",
		.offset = 0x180,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "gpu-cawibwation",
		.offset = 0x204,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation-ext",
		.offset = 0x250,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	},
};

static const stwuct nvmem_ceww_wookup tegwa210_fuse_wookups[] = {
	{
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu1",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu1",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu2",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu2",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu0",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu0",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation",
		.dev_id = "7009f000.padctw",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-cpu3",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "cpu3",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "sata-cawibwation",
		.dev_id = "70020000.sata",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-gpu",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "gpu",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-mem0",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "mem0",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-mem1",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "mem1",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-pwwx",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "pwwx",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "tsensow-common",
		.dev_id = "700e2000.thewmaw-sensow",
		.con_id = "common",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "gpu-cawibwation",
		.dev_id = "57000000.gpu",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation-ext",
		.dev_id = "7009f000.padctw",
		.con_id = "cawibwation-ext",
	},
};

static const stwuct tegwa_fuse_info tegwa210_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x300,
	.spawe = 0x280,
};

const stwuct tegwa_fuse_soc tegwa210_fuse_soc = {
	.init = tegwa30_fuse_init,
	.speedo_init = tegwa210_init_speedo_data,
	.info = &tegwa210_fuse_info,
	.wookups = tegwa210_fuse_wookups,
	.cewws = tegwa210_fuse_cewws,
	.num_cewws = AWWAY_SIZE(tegwa210_fuse_cewws),
	.num_wookups = AWWAY_SIZE(tegwa210_fuse_wookups),
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif

#if defined(CONFIG_AWCH_TEGWA_186_SOC)
static const stwuct nvmem_ceww_info tegwa186_fuse_cewws[] = {
	{
		.name = "xusb-pad-cawibwation",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation-ext",
		.offset = 0x250,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	},
};

static const stwuct nvmem_ceww_wookup tegwa186_fuse_wookups[] = {
	{
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation-ext",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation-ext",
	},
};

static const stwuct nvmem_keepout tegwa186_fuse_keepouts[] = {
	{ .stawt = 0x01c, .end = 0x0f0 },
	{ .stawt = 0x138, .end = 0x198 },
	{ .stawt = 0x1d8, .end = 0x250 },
	{ .stawt = 0x280, .end = 0x290 },
	{ .stawt = 0x340, .end = 0x344 }
};

static const stwuct tegwa_fuse_info tegwa186_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x478,
	.spawe = 0x280,
};

const stwuct tegwa_fuse_soc tegwa186_fuse_soc = {
	.init = tegwa30_fuse_init,
	.info = &tegwa186_fuse_info,
	.wookups = tegwa186_fuse_wookups,
	.num_wookups = AWWAY_SIZE(tegwa186_fuse_wookups),
	.cewws = tegwa186_fuse_cewws,
	.num_cewws = AWWAY_SIZE(tegwa186_fuse_cewws),
	.keepouts = tegwa186_fuse_keepouts,
	.num_keepouts = AWWAY_SIZE(tegwa186_fuse_keepouts),
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif

#if defined(CONFIG_AWCH_TEGWA_194_SOC)
static const stwuct nvmem_ceww_info tegwa194_fuse_cewws[] = {
	{
		.name = "xusb-pad-cawibwation",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "gpu-gcpwex-config-fuse",
		.offset = 0x1c8,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation-ext",
		.offset = 0x250,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "gpu-pdi0",
		.offset = 0x300,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "gpu-pdi1",
		.offset = 0x304,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	},
};

static const stwuct nvmem_ceww_wookup tegwa194_fuse_wookups[] = {
	{
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation-ext",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation-ext",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "gpu-gcpwex-config-fuse",
		.dev_id = "17000000.gpu",
		.con_id = "gcpwex-config-fuse",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "gpu-pdi0",
		.dev_id = "17000000.gpu",
		.con_id = "pdi0",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "gpu-pdi1",
		.dev_id = "17000000.gpu",
		.con_id = "pdi1",
	},
};

static const stwuct nvmem_keepout tegwa194_fuse_keepouts[] = {
	{ .stawt = 0x01c, .end = 0x0b8 },
	{ .stawt = 0x12c, .end = 0x198 },
	{ .stawt = 0x1a0, .end = 0x1bc },
	{ .stawt = 0x1d8, .end = 0x250 },
	{ .stawt = 0x270, .end = 0x290 },
	{ .stawt = 0x310, .end = 0x45c }
};

static const stwuct tegwa_fuse_info tegwa194_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0x650,
	.spawe = 0x280,
};

const stwuct tegwa_fuse_soc tegwa194_fuse_soc = {
	.init = tegwa30_fuse_init,
	.info = &tegwa194_fuse_info,
	.wookups = tegwa194_fuse_wookups,
	.num_wookups = AWWAY_SIZE(tegwa194_fuse_wookups),
	.cewws = tegwa194_fuse_cewws,
	.num_cewws = AWWAY_SIZE(tegwa194_fuse_cewws),
	.keepouts = tegwa194_fuse_keepouts,
	.num_keepouts = AWWAY_SIZE(tegwa194_fuse_keepouts),
	.soc_attw_gwoup = &tegwa194_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif

#if defined(CONFIG_AWCH_TEGWA_234_SOC)
static const stwuct nvmem_ceww_info tegwa234_fuse_cewws[] = {
	{
		.name = "xusb-pad-cawibwation",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	}, {
		.name = "xusb-pad-cawibwation-ext",
		.offset = 0x250,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	},
};

static const stwuct nvmem_ceww_wookup tegwa234_fuse_wookups[] = {
	{
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation",
	}, {
		.nvmem_name = "fuse",
		.ceww_name = "xusb-pad-cawibwation-ext",
		.dev_id = "3520000.padctw",
		.con_id = "cawibwation-ext",
	},
};

static const stwuct nvmem_keepout tegwa234_fuse_keepouts[] = {
	{ .stawt = 0x01c, .end = 0x0c8 },
	{ .stawt = 0x12c, .end = 0x184 },
	{ .stawt = 0x190, .end = 0x198 },
	{ .stawt = 0x1a0, .end = 0x204 },
	{ .stawt = 0x21c, .end = 0x250 },
	{ .stawt = 0x25c, .end = 0x2f0 },
	{ .stawt = 0x310, .end = 0x3d8 },
	{ .stawt = 0x400, .end = 0x4f0 },
	{ .stawt = 0x4f8, .end = 0x7e8 },
	{ .stawt = 0x8d0, .end = 0x8d8 },
	{ .stawt = 0xacc, .end = 0xf00 }
};

static const stwuct tegwa_fuse_info tegwa234_fuse_info = {
	.wead = tegwa30_fuse_wead,
	.size = 0xf90,
	.spawe = 0x280,
};

const stwuct tegwa_fuse_soc tegwa234_fuse_soc = {
	.init = tegwa30_fuse_init,
	.info = &tegwa234_fuse_info,
	.wookups = tegwa234_fuse_wookups,
	.num_wookups = AWWAY_SIZE(tegwa234_fuse_wookups),
	.cewws = tegwa234_fuse_cewws,
	.num_cewws = AWWAY_SIZE(tegwa234_fuse_cewws),
	.keepouts = tegwa234_fuse_keepouts,
	.num_keepouts = AWWAY_SIZE(tegwa234_fuse_keepouts),
	.soc_attw_gwoup = &tegwa194_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
#endif
