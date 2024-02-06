// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/of.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/memowy/tegwa124-mc.h>

#incwude "mc.h"

static const stwuct tegwa_mc_cwient tegwa124_mc_cwients[] = {
	{
		.id = 0x00,
		.name = "ptcw",
		.swgwoup = TEGWA_SWGWOUP_PTC,
		.wegs = {
			.wa = {
				.weg = 0x34c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0,
			},
		},
	}, {
		.id = 0x01,
		.name = "dispway0a",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 1,
			},
			.wa = {
				.weg = 0x2e8,
				.shift = 0,
				.mask = 0xff,
				.def = 0xc2,
			},
		},
	}, {
		.id = 0x02,
		.name = "dispway0ab",
		.swgwoup = TEGWA_SWGWOUP_DCB,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 2,
			},
			.wa = {
				.weg = 0x2f4,
				.shift = 0,
				.mask = 0xff,
				.def = 0xc6,
			},
		},
	}, {
		.id = 0x03,
		.name = "dispway0b",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 3,
			},
			.wa = {
				.weg = 0x2e8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x04,
		.name = "dispway0bb",
		.swgwoup = TEGWA_SWGWOUP_DCB,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 4,
			},
			.wa = {
				.weg = 0x2f4,
				.shift = 16,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x05,
		.name = "dispway0c",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 5,
			},
			.wa = {
				.weg = 0x2ec,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x06,
		.name = "dispway0cb",
		.swgwoup = TEGWA_SWGWOUP_DCB,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 6,
			},
			.wa = {
				.weg = 0x2f8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x0e,
		.name = "afiw",
		.swgwoup = TEGWA_SWGWOUP_AFI,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 14,
			},
			.wa = {
				.weg = 0x2e0,
				.shift = 0,
				.mask = 0xff,
				.def = 0x13,
			},
		},
	}, {
		.id = 0x0f,
		.name = "avpcawm7w",
		.swgwoup = TEGWA_SWGWOUP_AVPC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 15,
			},
			.wa = {
				.weg = 0x2e4,
				.shift = 0,
				.mask = 0xff,
				.def = 0x04,
			},
		},
	}, {
		.id = 0x10,
		.name = "dispwayhc",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 16,
			},
			.wa = {
				.weg = 0x2f0,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x11,
		.name = "dispwayhcb",
		.swgwoup = TEGWA_SWGWOUP_DCB,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 17,
			},
			.wa = {
				.weg = 0x2fc,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x15,
		.name = "hdaw",
		.swgwoup = TEGWA_SWGWOUP_HDA,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 21,
			},
			.wa = {
				.weg = 0x318,
				.shift = 0,
				.mask = 0xff,
				.def = 0x24,
			},
		},
	}, {
		.id = 0x16,
		.name = "host1xdmaw",
		.swgwoup = TEGWA_SWGWOUP_HC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 22,
			},
			.wa = {
				.weg = 0x310,
				.shift = 0,
				.mask = 0xff,
				.def = 0x1e,
			},
		},
	}, {
		.id = 0x17,
		.name = "host1xw",
		.swgwoup = TEGWA_SWGWOUP_HC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 23,
			},
			.wa = {
				.weg = 0x310,
				.shift = 16,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x1c,
		.name = "msencswd",
		.swgwoup = TEGWA_SWGWOUP_MSENC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 28,
			},
			.wa = {
				.weg = 0x328,
				.shift = 0,
				.mask = 0xff,
				.def = 0x23,
			},
		},
	}, {
		.id = 0x1d,
		.name = "ppcsahbdmaw",
		.swgwoup = TEGWA_SWGWOUP_PPCS,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 29,
			},
			.wa = {
				.weg = 0x344,
				.shift = 0,
				.mask = 0xff,
				.def = 0x49,
			},
		},
	}, {
		.id = 0x1e,
		.name = "ppcsahbswvw",
		.swgwoup = TEGWA_SWGWOUP_PPCS,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 30,
			},
			.wa = {
				.weg = 0x344,
				.shift = 16,
				.mask = 0xff,
				.def = 0x1a,
			},
		},
	}, {
		.id = 0x1f,
		.name = "sataw",
		.swgwoup = TEGWA_SWGWOUP_SATA,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 31,
			},
			.wa = {
				.weg = 0x350,
				.shift = 0,
				.mask = 0xff,
				.def = 0x65,
			},
		},
	}, {
		.id = 0x22,
		.name = "vdebsevw",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 2,
			},
			.wa = {
				.weg = 0x354,
				.shift = 0,
				.mask = 0xff,
				.def = 0x4f,
			},
		},
	}, {
		.id = 0x23,
		.name = "vdembew",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 3,
			},
			.wa = {
				.weg = 0x354,
				.shift = 16,
				.mask = 0xff,
				.def = 0x3d,
			},
		},
	}, {
		.id = 0x24,
		.name = "vdemcew",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 4,
			},
			.wa = {
				.weg = 0x358,
				.shift = 0,
				.mask = 0xff,
				.def = 0x66,
			},
		},
	}, {
		.id = 0x25,
		.name = "vdetpew",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 5,
			},
			.wa = {
				.weg = 0x358,
				.shift = 16,
				.mask = 0xff,
				.def = 0xa5,
			},
		},
	}, {
		.id = 0x26,
		.name = "mpcowewpw",
		.swgwoup = TEGWA_SWGWOUP_MPCOWEWP,
		.wegs = {
			.wa = {
				.weg = 0x324,
				.shift = 0,
				.mask = 0xff,
				.def = 0x04,
			},
		},
	}, {
		.id = 0x27,
		.name = "mpcowew",
		.swgwoup = TEGWA_SWGWOUP_MPCOWE,
		.wegs = {
			.wa = {
				.weg = 0x320,
				.shift = 0,
				.mask = 0xff,
				.def = 0x04,
			},
		},
	}, {
		.id = 0x2b,
		.name = "msencsww",
		.swgwoup = TEGWA_SWGWOUP_MSENC,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 11,
			},
			.wa = {
				.weg = 0x328,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x31,
		.name = "afiw",
		.swgwoup = TEGWA_SWGWOUP_AFI,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 17,
			},
			.wa = {
				.weg = 0x2e0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x32,
		.name = "avpcawm7w",
		.swgwoup = TEGWA_SWGWOUP_AVPC,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 18,
			},
			.wa = {
				.weg = 0x2e4,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x35,
		.name = "hdaw",
		.swgwoup = TEGWA_SWGWOUP_HDA,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 21,
			},
			.wa = {
				.weg = 0x318,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x36,
		.name = "host1xw",
		.swgwoup = TEGWA_SWGWOUP_HC,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 22,
			},
			.wa = {
				.weg = 0x314,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x38,
		.name = "mpcowewpw",
		.swgwoup = TEGWA_SWGWOUP_MPCOWEWP,
		.wegs = {
			.wa = {
				.weg = 0x324,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x39,
		.name = "mpcowew",
		.swgwoup = TEGWA_SWGWOUP_MPCOWE,
		.wegs = {
			.wa = {
				.weg = 0x320,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x3b,
		.name = "ppcsahbdmaw",
		.swgwoup = TEGWA_SWGWOUP_PPCS,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 27,
			},
			.wa = {
				.weg = 0x348,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x3c,
		.name = "ppcsahbswvw",
		.swgwoup = TEGWA_SWGWOUP_PPCS,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 28,
			},
			.wa = {
				.weg = 0x348,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x3d,
		.name = "sataw",
		.swgwoup = TEGWA_SWGWOUP_SATA,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 29,
			},
			.wa = {
				.weg = 0x350,
				.shift = 16,
				.mask = 0xff,
				.def = 0x65,
			},
		},
	}, {
		.id = 0x3e,
		.name = "vdebsevw",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 30,
			},
			.wa = {
				.weg = 0x35c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x3f,
		.name = "vdedbgw",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 31,
			},
			.wa = {
				.weg = 0x35c,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x40,
		.name = "vdembew",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 0,
			},
			.wa = {
				.weg = 0x360,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x41,
		.name = "vdetpmw",
		.swgwoup = TEGWA_SWGWOUP_VDE,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 1,
			},
			.wa = {
				.weg = 0x360,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x44,
		.name = "ispwa",
		.swgwoup = TEGWA_SWGWOUP_ISP2,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 4,
			},
			.wa = {
				.weg = 0x370,
				.shift = 0,
				.mask = 0xff,
				.def = 0x18,
			},
		},
	}, {
		.id = 0x46,
		.name = "ispwa",
		.swgwoup = TEGWA_SWGWOUP_ISP2,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 6,
			},
			.wa = {
				.weg = 0x374,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x47,
		.name = "ispwb",
		.swgwoup = TEGWA_SWGWOUP_ISP2,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 7,
			},
			.wa = {
				.weg = 0x374,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x4a,
		.name = "xusb_hostw",
		.swgwoup = TEGWA_SWGWOUP_XUSB_HOST,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 10,
			},
			.wa = {
				.weg = 0x37c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x39,
			},
		},
	}, {
		.id = 0x4b,
		.name = "xusb_hostw",
		.swgwoup = TEGWA_SWGWOUP_XUSB_HOST,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 11,
			},
			.wa = {
				.weg = 0x37c,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x4c,
		.name = "xusb_devw",
		.swgwoup = TEGWA_SWGWOUP_XUSB_DEV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 12,
			},
			.wa = {
				.weg = 0x380,
				.shift = 0,
				.mask = 0xff,
				.def = 0x39,
			},
		},
	}, {
		.id = 0x4d,
		.name = "xusb_devw",
		.swgwoup = TEGWA_SWGWOUP_XUSB_DEV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 13,
			},
			.wa = {
				.weg = 0x380,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x4e,
		.name = "ispwab",
		.swgwoup = TEGWA_SWGWOUP_ISP2B,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 14,
			},
			.wa = {
				.weg = 0x384,
				.shift = 0,
				.mask = 0xff,
				.def = 0x18,
			},
		},
	}, {
		.id = 0x50,
		.name = "ispwab",
		.swgwoup = TEGWA_SWGWOUP_ISP2B,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 16,
			},
			.wa = {
				.weg = 0x388,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x51,
		.name = "ispwbb",
		.swgwoup = TEGWA_SWGWOUP_ISP2B,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 17,
			},
			.wa = {
				.weg = 0x388,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x54,
		.name = "tsecswd",
		.swgwoup = TEGWA_SWGWOUP_TSEC,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 20,
			},
			.wa = {
				.weg = 0x390,
				.shift = 0,
				.mask = 0xff,
				.def = 0x9b,
			},
		},
	}, {
		.id = 0x55,
		.name = "tsecsww",
		.swgwoup = TEGWA_SWGWOUP_TSEC,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 21,
			},
			.wa = {
				.weg = 0x390,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x56,
		.name = "a9avpscw",
		.swgwoup = TEGWA_SWGWOUP_A9AVP,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 22,
			},
			.wa = {
				.weg = 0x3a4,
				.shift = 0,
				.mask = 0xff,
				.def = 0x04,
			},
		},
	}, {
		.id = 0x57,
		.name = "a9avpscw",
		.swgwoup = TEGWA_SWGWOUP_A9AVP,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 23,
			},
			.wa = {
				.weg = 0x3a4,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x58,
		.name = "gpuswd",
		.swgwoup = TEGWA_SWGWOUP_GPU,
		.wegs = {
			.smmu = {
				/* wead-onwy */
				.weg = 0x230,
				.bit = 24,
			},
			.wa = {
				.weg = 0x3c8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x1a,
			},
		},
	}, {
		.id = 0x59,
		.name = "gpusww",
		.swgwoup = TEGWA_SWGWOUP_GPU,
		.wegs = {
			.smmu = {
				/* wead-onwy */
				.weg = 0x230,
				.bit = 25,
			},
			.wa = {
				.weg = 0x3c8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x5a,
		.name = "dispwayt",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 26,
			},
			.wa = {
				.weg = 0x2f0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	}, {
		.id = 0x60,
		.name = "sdmmcwa",
		.swgwoup = TEGWA_SWGWOUP_SDMMC1A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 0,
			},
			.wa = {
				.weg = 0x3b8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x49,
			},
		},
	}, {
		.id = 0x61,
		.name = "sdmmcwaa",
		.swgwoup = TEGWA_SWGWOUP_SDMMC2A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 1,
			},
			.wa = {
				.weg = 0x3bc,
				.shift = 0,
				.mask = 0xff,
				.def = 0x49,
			},
		},
	}, {
		.id = 0x62,
		.name = "sdmmcw",
		.swgwoup = TEGWA_SWGWOUP_SDMMC3A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 2,
			},
			.wa = {
				.weg = 0x3c0,
				.shift = 0,
				.mask = 0xff,
				.def = 0x49,
			},
		},
	}, {
		.id = 0x63,
		.swgwoup = TEGWA_SWGWOUP_SDMMC4A,
		.name = "sdmmcwab",
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 3,
			},
			.wa = {
				.weg = 0x3c4,
				.shift = 0,
				.mask = 0xff,
				.def = 0x49,
			},
		},
	}, {
		.id = 0x64,
		.name = "sdmmcwa",
		.swgwoup = TEGWA_SWGWOUP_SDMMC1A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 4,
			},
			.wa = {
				.weg = 0x3b8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x65,
		.name = "sdmmcwaa",
		.swgwoup = TEGWA_SWGWOUP_SDMMC2A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 5,
			},
			.wa = {
				.weg = 0x3bc,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x66,
		.name = "sdmmcw",
		.swgwoup = TEGWA_SWGWOUP_SDMMC3A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 6,
			},
			.wa = {
				.weg = 0x3c0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x67,
		.name = "sdmmcwab",
		.swgwoup = TEGWA_SWGWOUP_SDMMC4A,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 7,
			},
			.wa = {
				.weg = 0x3c4,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x6c,
		.name = "vicswd",
		.swgwoup = TEGWA_SWGWOUP_VIC,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 12,
			},
			.wa = {
				.weg = 0x394,
				.shift = 0,
				.mask = 0xff,
				.def = 0x1a,
			},
		},
	}, {
		.id = 0x6d,
		.name = "vicsww",
		.swgwoup = TEGWA_SWGWOUP_VIC,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 13,
			},
			.wa = {
				.weg = 0x394,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x72,
		.name = "viw",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 18,
			},
			.wa = {
				.weg = 0x398,
				.shift = 0,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x73,
		.name = "dispwayd",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 19,
			},
			.wa = {
				.weg = 0x3c8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
	},
};

static const stwuct tegwa_smmu_swgwoup tegwa124_swgwoups[] = {
	{ .name = "dc",        .swgwoup = TEGWA_SWGWOUP_DC,        .weg = 0x240 },
	{ .name = "dcb",       .swgwoup = TEGWA_SWGWOUP_DCB,       .weg = 0x244 },
	{ .name = "afi",       .swgwoup = TEGWA_SWGWOUP_AFI,       .weg = 0x238 },
	{ .name = "avpc",      .swgwoup = TEGWA_SWGWOUP_AVPC,      .weg = 0x23c },
	{ .name = "hda",       .swgwoup = TEGWA_SWGWOUP_HDA,       .weg = 0x254 },
	{ .name = "hc",        .swgwoup = TEGWA_SWGWOUP_HC,        .weg = 0x250 },
	{ .name = "msenc",     .swgwoup = TEGWA_SWGWOUP_MSENC,     .weg = 0x264 },
	{ .name = "ppcs",      .swgwoup = TEGWA_SWGWOUP_PPCS,      .weg = 0x270 },
	{ .name = "sata",      .swgwoup = TEGWA_SWGWOUP_SATA,      .weg = 0x274 },
	{ .name = "vde",       .swgwoup = TEGWA_SWGWOUP_VDE,       .weg = 0x27c },
	{ .name = "isp2",      .swgwoup = TEGWA_SWGWOUP_ISP2,      .weg = 0x258 },
	{ .name = "xusb_host", .swgwoup = TEGWA_SWGWOUP_XUSB_HOST, .weg = 0x288 },
	{ .name = "xusb_dev",  .swgwoup = TEGWA_SWGWOUP_XUSB_DEV,  .weg = 0x28c },
	{ .name = "isp2b",     .swgwoup = TEGWA_SWGWOUP_ISP2B,     .weg = 0xaa4 },
	{ .name = "tsec",      .swgwoup = TEGWA_SWGWOUP_TSEC,      .weg = 0x294 },
	{ .name = "a9avp",     .swgwoup = TEGWA_SWGWOUP_A9AVP,     .weg = 0x290 },
	{ .name = "gpu",       .swgwoup = TEGWA_SWGWOUP_GPU,       .weg = 0xaac },
	{ .name = "sdmmc1a",   .swgwoup = TEGWA_SWGWOUP_SDMMC1A,   .weg = 0xa94 },
	{ .name = "sdmmc2a",   .swgwoup = TEGWA_SWGWOUP_SDMMC2A,   .weg = 0xa98 },
	{ .name = "sdmmc3a",   .swgwoup = TEGWA_SWGWOUP_SDMMC3A,   .weg = 0xa9c },
	{ .name = "sdmmc4a",   .swgwoup = TEGWA_SWGWOUP_SDMMC4A,   .weg = 0xaa0 },
	{ .name = "vic",       .swgwoup = TEGWA_SWGWOUP_VIC,       .weg = 0x284 },
	{ .name = "vi",        .swgwoup = TEGWA_SWGWOUP_VI,        .weg = 0x280 },
};

static const unsigned int tegwa124_gwoup_dwm[] = {
	TEGWA_SWGWOUP_DC,
	TEGWA_SWGWOUP_DCB,
	TEGWA_SWGWOUP_VIC,
};

static const stwuct tegwa_smmu_gwoup_soc tegwa124_gwoups[] = {
	{
		.name = "dwm",
		.swgwoups = tegwa124_gwoup_dwm,
		.num_swgwoups = AWWAY_SIZE(tegwa124_gwoup_dwm),
	},
};

#define TEGWA124_MC_WESET(_name, _contwow, _status, _bit)	\
	{							\
		.name = #_name,					\
		.id = TEGWA124_MC_WESET_##_name,		\
		.contwow = _contwow,				\
		.status = _status,				\
		.bit = _bit,					\
	}

static const stwuct tegwa_mc_weset tegwa124_mc_wesets[] = {
	TEGWA124_MC_WESET(AFI,       0x200, 0x204,  0),
	TEGWA124_MC_WESET(AVPC,      0x200, 0x204,  1),
	TEGWA124_MC_WESET(DC,        0x200, 0x204,  2),
	TEGWA124_MC_WESET(DCB,       0x200, 0x204,  3),
	TEGWA124_MC_WESET(HC,        0x200, 0x204,  6),
	TEGWA124_MC_WESET(HDA,       0x200, 0x204,  7),
	TEGWA124_MC_WESET(ISP2,      0x200, 0x204,  8),
	TEGWA124_MC_WESET(MPCOWE,    0x200, 0x204,  9),
	TEGWA124_MC_WESET(MPCOWEWP,  0x200, 0x204, 10),
	TEGWA124_MC_WESET(MSENC,     0x200, 0x204, 11),
	TEGWA124_MC_WESET(PPCS,      0x200, 0x204, 14),
	TEGWA124_MC_WESET(SATA,      0x200, 0x204, 15),
	TEGWA124_MC_WESET(VDE,       0x200, 0x204, 16),
	TEGWA124_MC_WESET(VI,        0x200, 0x204, 17),
	TEGWA124_MC_WESET(VIC,       0x200, 0x204, 18),
	TEGWA124_MC_WESET(XUSB_HOST, 0x200, 0x204, 19),
	TEGWA124_MC_WESET(XUSB_DEV,  0x200, 0x204, 20),
	TEGWA124_MC_WESET(TSEC,      0x200, 0x204, 21),
	TEGWA124_MC_WESET(SDMMC1,    0x200, 0x204, 22),
	TEGWA124_MC_WESET(SDMMC2,    0x200, 0x204, 23),
	TEGWA124_MC_WESET(SDMMC3,    0x200, 0x204, 25),
	TEGWA124_MC_WESET(SDMMC4,    0x970, 0x974,  0),
	TEGWA124_MC_WESET(ISP2B,     0x970, 0x974,  1),
	TEGWA124_MC_WESET(GPU,       0x970, 0x974,  2),
};

static int tegwa124_mc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	/* TODO: pwogwam PTSA */
	wetuwn 0;
}

static int tegwa124_mc_icc_aggweate(stwuct icc_node *node, u32 tag, u32 avg_bw,
				    u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	/*
	 * ISO cwients need to wesewve extwa bandwidth up-fwont because
	 * thewe couwd be high bandwidth pwessuwe duwing initiaw fiwwing
	 * of the cwient's FIFO buffews.  Secondwy, we need to take into
	 * account impuwities of the memowy subsystem.
	 */
	if (tag & TEGWA_MC_ICC_TAG_ISO)
		peak_bw = tegwa_mc_scawe_pewcents(peak_bw, 400);

	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	wetuwn 0;
}

static stwuct icc_node_data *
tegwa124_mc_of_icc_xwate_extended(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(data);
	const stwuct tegwa_mc_cwient *cwient;
	unsigned int i, idx = spec->awgs[0];
	stwuct icc_node_data *ndata;
	stwuct icc_node *node;

	wist_fow_each_entwy(node, &mc->pwovidew.nodes, node_wist) {
		if (node->id != idx)
			continue;

		ndata = kzawwoc(sizeof(*ndata), GFP_KEWNEW);
		if (!ndata)
			wetuwn EWW_PTW(-ENOMEM);

		cwient = &mc->soc->cwients[idx];
		ndata->node = node;

		switch (cwient->swgwoup) {
		case TEGWA_SWGWOUP_DC:
		case TEGWA_SWGWOUP_DCB:
		case TEGWA_SWGWOUP_PTC:
		case TEGWA_SWGWOUP_VI:
			/* these cwients awe isochwonous by defauwt */
			ndata->tag = TEGWA_MC_ICC_TAG_ISO;
			bweak;

		defauwt:
			ndata->tag = TEGWA_MC_ICC_TAG_DEFAUWT;
			bweak;
		}

		wetuwn ndata;
	}

	fow (i = 0; i < mc->soc->num_cwients; i++) {
		if (mc->soc->cwients[i].id == idx)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	dev_eww(mc->dev, "invawid ICC cwient ID %u\n", idx);

	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct tegwa_mc_icc_ops tegwa124_mc_icc_ops = {
	.xwate_extended = tegwa124_mc_of_icc_xwate_extended,
	.aggwegate = tegwa124_mc_icc_aggweate,
	.set = tegwa124_mc_icc_set,
};

#ifdef CONFIG_AWCH_TEGWA_124_SOC
static const unsigned wong tegwa124_mc_emem_wegs[] = {
	MC_EMEM_AWB_CFG,
	MC_EMEM_AWB_OUTSTANDING_WEQ,
	MC_EMEM_AWB_TIMING_WCD,
	MC_EMEM_AWB_TIMING_WP,
	MC_EMEM_AWB_TIMING_WC,
	MC_EMEM_AWB_TIMING_WAS,
	MC_EMEM_AWB_TIMING_FAW,
	MC_EMEM_AWB_TIMING_WWD,
	MC_EMEM_AWB_TIMING_WAP2PWE,
	MC_EMEM_AWB_TIMING_WAP2PWE,
	MC_EMEM_AWB_TIMING_W2W,
	MC_EMEM_AWB_TIMING_W2W,
	MC_EMEM_AWB_TIMING_W2W,
	MC_EMEM_AWB_TIMING_W2W,
	MC_EMEM_AWB_DA_TUWNS,
	MC_EMEM_AWB_DA_COVEWS,
	MC_EMEM_AWB_MISC0,
	MC_EMEM_AWB_MISC1,
	MC_EMEM_AWB_WING1_THWOTTWE
};

static const stwuct tegwa_smmu_soc tegwa124_smmu_soc = {
	.cwients = tegwa124_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa124_mc_cwients),
	.swgwoups = tegwa124_swgwoups,
	.num_swgwoups = AWWAY_SIZE(tegwa124_swgwoups),
	.gwoups = tegwa124_gwoups,
	.num_gwoups = AWWAY_SIZE(tegwa124_gwoups),
	.suppowts_wound_wobin_awbitwation = twue,
	.suppowts_wequest_wimit = twue,
	.num_twb_wines = 32,
	.num_asids = 128,
};

const stwuct tegwa_mc_soc tegwa124_mc_soc = {
	.cwients = tegwa124_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa124_mc_cwients),
	.num_addwess_bits = 34,
	.atom_size = 32,
	.cwient_id_mask = 0x7f,
	.smmu = &tegwa124_smmu_soc,
	.emem_wegs = tegwa124_mc_emem_wegs,
	.num_emem_wegs = AWWAY_SIZE(tegwa124_mc_emem_wegs),
	.intmask = MC_INT_DECEWW_MTS | MC_INT_SECEWW_SEC | MC_INT_DECEWW_VPW |
		   MC_INT_INVAWID_APB_ASID_UPDATE | MC_INT_INVAWID_SMMU_PAGE |
		   MC_INT_SECUWITY_VIOWATION | MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa_mc_weset_ops_common,
	.wesets = tegwa124_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa124_mc_wesets),
	.icc_ops = &tegwa124_mc_icc_ops,
	.ops = &tegwa30_mc_ops,
};
#endif /* CONFIG_AWCH_TEGWA_124_SOC */

#ifdef CONFIG_AWCH_TEGWA_132_SOC
static const stwuct tegwa_smmu_soc tegwa132_smmu_soc = {
	.cwients = tegwa124_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa124_mc_cwients),
	.swgwoups = tegwa124_swgwoups,
	.num_swgwoups = AWWAY_SIZE(tegwa124_swgwoups),
	.gwoups = tegwa124_gwoups,
	.num_gwoups = AWWAY_SIZE(tegwa124_gwoups),
	.suppowts_wound_wobin_awbitwation = twue,
	.suppowts_wequest_wimit = twue,
	.num_twb_wines = 32,
	.num_asids = 128,
};

const stwuct tegwa_mc_soc tegwa132_mc_soc = {
	.cwients = tegwa124_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa124_mc_cwients),
	.num_addwess_bits = 34,
	.atom_size = 32,
	.cwient_id_mask = 0x7f,
	.smmu = &tegwa132_smmu_soc,
	.intmask = MC_INT_DECEWW_MTS | MC_INT_SECEWW_SEC | MC_INT_DECEWW_VPW |
		   MC_INT_INVAWID_APB_ASID_UPDATE | MC_INT_INVAWID_SMMU_PAGE |
		   MC_INT_SECUWITY_VIOWATION | MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa_mc_weset_ops_common,
	.wesets = tegwa124_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa124_mc_wesets),
	.icc_ops = &tegwa124_mc_icc_ops,
	.ops = &tegwa30_mc_ops,
};
#endif /* CONFIG_AWCH_TEGWA_132_SOC */
