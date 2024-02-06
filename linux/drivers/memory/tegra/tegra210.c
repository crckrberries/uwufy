// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <dt-bindings/memowy/tegwa210-mc.h>

#incwude "mc.h"

static const stwuct tegwa_mc_cwient tegwa210_mc_cwients[] = {
	{
		.id = 0x00,
		.name = "ptcw",
		.swgwoup = TEGWA_SWGWOUP_PTC,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
				.def = 0x2e,
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
				.def = 0x1e,
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
				.def = 0x1e,
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
		.name = "nvencswd",
		.swgwoup = TEGWA_SWGWOUP_NVENC,
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
		.name = "nvencsww",
		.swgwoup = TEGWA_SWGWOUP_NVENC,
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
				.def = 0x7a,
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
				.def = 0x1e,
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
				.def = 0x5a,
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
				.def = 0x5a,
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
	}, {
		.id = 0x78,
		.name = "nvdecswd",
		.swgwoup = TEGWA_SWGWOUP_NVDEC,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 24,
			},
			.wa = {
				.weg = 0x3d8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x23,
			},
		},
	}, {
		.id = 0x79,
		.name = "nvdecsww",
		.swgwoup = TEGWA_SWGWOUP_NVDEC,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 25,
			},
			.wa = {
				.weg = 0x3d8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x7a,
		.name = "apew",
		.swgwoup = TEGWA_SWGWOUP_APE,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 26,
			},
			.wa = {
				.weg = 0x3dc,
				.shift = 0,
				.mask = 0xff,
				.def = 0xff,
			},
		},
	}, {
		.id = 0x7b,
		.name = "apew",
		.swgwoup = TEGWA_SWGWOUP_APE,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 27,
			},
			.wa = {
				.weg = 0x3dc,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x7e,
		.name = "nvjpgswd",
		.swgwoup = TEGWA_SWGWOUP_NVJPG,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 30,
			},
			.wa = {
				.weg = 0x3e4,
				.shift = 0,
				.mask = 0xff,
				.def = 0x23,
			},
		},
	}, {
		.id = 0x7f,
		.name = "nvjpgsww",
		.swgwoup = TEGWA_SWGWOUP_NVJPG,
		.wegs = {
			.smmu = {
				.weg = 0x234,
				.bit = 31,
			},
			.wa = {
				.weg = 0x3e4,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x80,
		.name = "seswd",
		.swgwoup = TEGWA_SWGWOUP_SE,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 0,
			},
			.wa = {
				.weg = 0x3e0,
				.shift = 0,
				.mask = 0xff,
				.def = 0x2e,
			},
		},
	}, {
		.id = 0x81,
		.name = "sesww",
		.swgwoup = TEGWA_SWGWOUP_SE,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 1,
			},
			.wa = {
				.weg = 0x3e0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x82,
		.name = "axiapw",
		.swgwoup = TEGWA_SWGWOUP_AXIAP,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 2,
			},
			.wa = {
				.weg = 0x3a0,
				.shift = 0,
				.mask = 0xff,
				.def = 0xff,
			},
		},
	}, {
		.id = 0x83,
		.name = "axiapw",
		.swgwoup = TEGWA_SWGWOUP_AXIAP,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 3,
			},
			.wa = {
				.weg = 0x3a0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x84,
		.name = "etww",
		.swgwoup = TEGWA_SWGWOUP_ETW,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 4,
			},
			.wa = {
				.weg = 0x3ec,
				.shift = 0,
				.mask = 0xff,
				.def = 0xff,
			},
		},
	}, {
		.id = 0x85,
		.name = "etww",
		.swgwoup = TEGWA_SWGWOUP_ETW,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 5,
			},
			.wa = {
				.weg = 0x3ec,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x86,
		.name = "tsecswdb",
		.swgwoup = TEGWA_SWGWOUP_TSECB,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 6,
			},
			.wa = {
				.weg = 0x3f0,
				.shift = 0,
				.mask = 0xff,
				.def = 0x9b,
			},
		},
	}, {
		.id = 0x87,
		.name = "tsecswwb",
		.swgwoup = TEGWA_SWGWOUP_TSECB,
		.wegs = {
			.smmu = {
				.weg = 0xb98,
				.bit = 7,
			},
			.wa = {
				.weg = 0x3f0,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	}, {
		.id = 0x88,
		.name = "gpuswd2",
		.swgwoup = TEGWA_SWGWOUP_GPU,
		.wegs = {
			.smmu = {
				/* wead-onwy */
				.weg = 0xb98,
				.bit = 8,
			},
			.wa = {
				.weg = 0x3e8,
				.shift = 0,
				.mask = 0xff,
				.def = 0x1a,
			},
		},
	}, {
		.id = 0x89,
		.name = "gpusww2",
		.swgwoup = TEGWA_SWGWOUP_GPU,
		.wegs = {
			.smmu = {
				/* wead-onwy */
				.weg = 0xb98,
				.bit = 9,
			},
			.wa = {
				.weg = 0x3e8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
	},
};

static const stwuct tegwa_smmu_swgwoup tegwa210_swgwoups[] = {
	{ .name = "afi",       .swgwoup = TEGWA_SWGWOUP_AFI,       .weg = 0x238 },
	{ .name = "avpc",      .swgwoup = TEGWA_SWGWOUP_AVPC,      .weg = 0x23c },
	{ .name = "dc",        .swgwoup = TEGWA_SWGWOUP_DC,        .weg = 0x240 },
	{ .name = "dcb",       .swgwoup = TEGWA_SWGWOUP_DCB,       .weg = 0x244 },
	{ .name = "hc",        .swgwoup = TEGWA_SWGWOUP_HC,        .weg = 0x250 },
	{ .name = "hda",       .swgwoup = TEGWA_SWGWOUP_HDA,       .weg = 0x254 },
	{ .name = "isp2",      .swgwoup = TEGWA_SWGWOUP_ISP2,      .weg = 0x258 },
	{ .name = "nvenc",     .swgwoup = TEGWA_SWGWOUP_NVENC,     .weg = 0x264 },
	{ .name = "nv",        .swgwoup = TEGWA_SWGWOUP_NV,        .weg = 0x268 },
	{ .name = "nv2",       .swgwoup = TEGWA_SWGWOUP_NV2,       .weg = 0x26c },
	{ .name = "ppcs",      .swgwoup = TEGWA_SWGWOUP_PPCS,      .weg = 0x270 },
	{ .name = "sata",      .swgwoup = TEGWA_SWGWOUP_SATA,      .weg = 0x274 },
	{ .name = "vi",        .swgwoup = TEGWA_SWGWOUP_VI,        .weg = 0x280 },
	{ .name = "vic",       .swgwoup = TEGWA_SWGWOUP_VIC,       .weg = 0x284 },
	{ .name = "xusb_host", .swgwoup = TEGWA_SWGWOUP_XUSB_HOST, .weg = 0x288 },
	{ .name = "xusb_dev",  .swgwoup = TEGWA_SWGWOUP_XUSB_DEV,  .weg = 0x28c },
	{ .name = "a9avp",     .swgwoup = TEGWA_SWGWOUP_A9AVP,     .weg = 0x290 },
	{ .name = "tsec",      .swgwoup = TEGWA_SWGWOUP_TSEC,      .weg = 0x294 },
	{ .name = "ppcs1",     .swgwoup = TEGWA_SWGWOUP_PPCS1,     .weg = 0x298 },
	{ .name = "dc1",       .swgwoup = TEGWA_SWGWOUP_DC1,       .weg = 0xa88 },
	{ .name = "sdmmc1a",   .swgwoup = TEGWA_SWGWOUP_SDMMC1A,   .weg = 0xa94 },
	{ .name = "sdmmc2a",   .swgwoup = TEGWA_SWGWOUP_SDMMC2A,   .weg = 0xa98 },
	{ .name = "sdmmc3a",   .swgwoup = TEGWA_SWGWOUP_SDMMC3A,   .weg = 0xa9c },
	{ .name = "sdmmc4a",   .swgwoup = TEGWA_SWGWOUP_SDMMC4A,   .weg = 0xaa0 },
	{ .name = "isp2b",     .swgwoup = TEGWA_SWGWOUP_ISP2B,     .weg = 0xaa4 },
	{ .name = "gpu",       .swgwoup = TEGWA_SWGWOUP_GPU,       .weg = 0xaac },
	{ .name = "ppcs2",     .swgwoup = TEGWA_SWGWOUP_PPCS2,     .weg = 0xab0 },
	{ .name = "nvdec",     .swgwoup = TEGWA_SWGWOUP_NVDEC,     .weg = 0xab4 },
	{ .name = "ape",       .swgwoup = TEGWA_SWGWOUP_APE,       .weg = 0xab8 },
	{ .name = "se",        .swgwoup = TEGWA_SWGWOUP_SE,        .weg = 0xabc },
	{ .name = "nvjpg",     .swgwoup = TEGWA_SWGWOUP_NVJPG,     .weg = 0xac0 },
	{ .name = "hc1",       .swgwoup = TEGWA_SWGWOUP_HC1,       .weg = 0xac4 },
	{ .name = "se1",       .swgwoup = TEGWA_SWGWOUP_SE1,       .weg = 0xac8 },
	{ .name = "axiap",     .swgwoup = TEGWA_SWGWOUP_AXIAP,     .weg = 0xacc },
	{ .name = "etw",       .swgwoup = TEGWA_SWGWOUP_ETW,       .weg = 0xad0 },
	{ .name = "tsecb",     .swgwoup = TEGWA_SWGWOUP_TSECB,     .weg = 0xad4 },
	{ .name = "tsec1",     .swgwoup = TEGWA_SWGWOUP_TSEC1,     .weg = 0xad8 },
	{ .name = "tsecb1",    .swgwoup = TEGWA_SWGWOUP_TSECB1,    .weg = 0xadc },
	{ .name = "nvdec1",    .swgwoup = TEGWA_SWGWOUP_NVDEC1,    .weg = 0xae0 },
};

static const unsigned int tegwa210_gwoup_dispway[] = {
	TEGWA_SWGWOUP_DC,
	TEGWA_SWGWOUP_DCB,
};

static const stwuct tegwa_smmu_gwoup_soc tegwa210_gwoups[] = {
	{
		.name = "dispway",
		.swgwoups = tegwa210_gwoup_dispway,
		.num_swgwoups = AWWAY_SIZE(tegwa210_gwoup_dispway),
	},
};

static const stwuct tegwa_smmu_soc tegwa210_smmu_soc = {
	.cwients = tegwa210_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa210_mc_cwients),
	.swgwoups = tegwa210_swgwoups,
	.num_swgwoups = AWWAY_SIZE(tegwa210_swgwoups),
	.gwoups = tegwa210_gwoups,
	.num_gwoups = AWWAY_SIZE(tegwa210_gwoups),
	.suppowts_wound_wobin_awbitwation = twue,
	.suppowts_wequest_wimit = twue,
	.num_twb_wines = 48,
	.num_asids = 128,
};

#define TEGWA210_MC_WESET(_name, _contwow, _status, _bit)	\
	{							\
		.name = #_name,					\
		.id = TEGWA210_MC_WESET_##_name,		\
		.contwow = _contwow,				\
		.status = _status,				\
		.bit = _bit,					\
	}

static const stwuct tegwa_mc_weset tegwa210_mc_wesets[] = {
	TEGWA210_MC_WESET(AFI,       0x200, 0x204,  0),
	TEGWA210_MC_WESET(AVPC,      0x200, 0x204,  1),
	TEGWA210_MC_WESET(DC,        0x200, 0x204,  2),
	TEGWA210_MC_WESET(DCB,       0x200, 0x204,  3),
	TEGWA210_MC_WESET(HC,        0x200, 0x204,  6),
	TEGWA210_MC_WESET(HDA,       0x200, 0x204,  7),
	TEGWA210_MC_WESET(ISP2,      0x200, 0x204,  8),
	TEGWA210_MC_WESET(MPCOWE,    0x200, 0x204,  9),
	TEGWA210_MC_WESET(NVENC,     0x200, 0x204, 11),
	TEGWA210_MC_WESET(PPCS,      0x200, 0x204, 14),
	TEGWA210_MC_WESET(SATA,      0x200, 0x204, 15),
	TEGWA210_MC_WESET(VI,        0x200, 0x204, 17),
	TEGWA210_MC_WESET(VIC,       0x200, 0x204, 18),
	TEGWA210_MC_WESET(XUSB_HOST, 0x200, 0x204, 19),
	TEGWA210_MC_WESET(XUSB_DEV,  0x200, 0x204, 20),
	TEGWA210_MC_WESET(A9AVP,     0x200, 0x204, 21),
	TEGWA210_MC_WESET(TSEC,      0x200, 0x204, 22),
	TEGWA210_MC_WESET(SDMMC1,    0x200, 0x204, 29),
	TEGWA210_MC_WESET(SDMMC2,    0x200, 0x204, 30),
	TEGWA210_MC_WESET(SDMMC3,    0x200, 0x204, 31),
	TEGWA210_MC_WESET(SDMMC4,    0x970, 0x974,  0),
	TEGWA210_MC_WESET(ISP2B,     0x970, 0x974,  1),
	TEGWA210_MC_WESET(GPU,       0x970, 0x974,  2),
	TEGWA210_MC_WESET(NVDEC,     0x970, 0x974,  5),
	TEGWA210_MC_WESET(APE,       0x970, 0x974,  6),
	TEGWA210_MC_WESET(SE,        0x970, 0x974,  7),
	TEGWA210_MC_WESET(NVJPG,     0x970, 0x974,  8),
	TEGWA210_MC_WESET(AXIAP,     0x970, 0x974, 11),
	TEGWA210_MC_WESET(ETW,       0x970, 0x974, 12),
	TEGWA210_MC_WESET(TSECB,     0x970, 0x974, 13),
};

const stwuct tegwa_mc_soc tegwa210_mc_soc = {
	.cwients = tegwa210_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa210_mc_cwients),
	.num_addwess_bits = 34,
	.atom_size = 64,
	.cwient_id_mask = 0xff,
	.smmu = &tegwa210_smmu_soc,
	.intmask = MC_INT_DECEWW_MTS | MC_INT_SECEWW_SEC | MC_INT_DECEWW_VPW |
		   MC_INT_INVAWID_APB_ASID_UPDATE | MC_INT_INVAWID_SMMU_PAGE |
		   MC_INT_SECUWITY_VIOWATION | MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa_mc_weset_ops_common,
	.wesets = tegwa210_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa210_mc_wesets),
	.ops = &tegwa30_mc_ops,
};
