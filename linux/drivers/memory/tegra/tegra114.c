// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/of.h>
#incwude <winux/mm.h>

#incwude <dt-bindings/memowy/tegwa114-mc.h>

#incwude "mc.h"

static const stwuct tegwa_mc_cwient tegwa114_mc_cwients[] = {
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
				.def = 0x4e,
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
				.def = 0x4e,
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
				.def = 0x4e,
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
				.def = 0x4e,
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
				.def = 0x4e,
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
				.def = 0x4e,
			},
		},
	}, {
		.id = 0x09,
		.name = "eppup",
		.swgwoup = TEGWA_SWGWOUP_EPP,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 9,
			},
			.wa = {
				.weg = 0x300,
				.shift = 0,
				.mask = 0xff,
				.def = 0x33,
			},
		},
	}, {
		.id = 0x0a,
		.name = "g2pw",
		.swgwoup = TEGWA_SWGWOUP_G2,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 10,
			},
			.wa = {
				.weg = 0x308,
				.shift = 0,
				.mask = 0xff,
				.def = 0x09,
			},
		},
	}, {
		.id = 0x0b,
		.name = "g2sw",
		.swgwoup = TEGWA_SWGWOUP_G2,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 11,
			},
			.wa = {
				.weg = 0x308,
				.shift = 16,
				.mask = 0xff,
				.def = 0x09,
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
				.def = 0x68,
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
				.def = 0x68,
			},
		},
	}, {
		.id = 0x12,
		.name = "fdcdwd",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 18,
			},
			.wa = {
				.weg = 0x334,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0c,
			},
		},
	}, {
		.id = 0x13,
		.name = "fdcdwd2",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 19,
			},
			.wa = {
				.weg = 0x33c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0c,
			},
		},
	}, {
		.id = 0x14,
		.name = "g2dw",
		.swgwoup = TEGWA_SWGWOUP_G2,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 20,
			},
			.wa = {
				.weg = 0x30c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0a,
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
				.def = 0xff,
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
				.def = 0x10,
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
				.def = 0xa5,
			},
		},
	}, {
		.id = 0x18,
		.name = "idxswd",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 24,
			},
			.wa = {
				.weg = 0x334,
				.shift = 16,
				.mask = 0xff,
				.def = 0x0b,
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
				.def = 0x80,
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
				.def = 0x50,
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
				.def = 0xe8,
			},
		},
	}, {
		.id = 0x20,
		.name = "texw2swd",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 0,
			},
			.wa = {
				.weg = 0x338,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0c,
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
				.def = 0xff,
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
				.def = 0xff,
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
				.def = 0xb8,
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
				.def = 0xee,
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
		.id = 0x28,
		.name = "eppu",
		.swgwoup = TEGWA_SWGWOUP_EPP,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 8,
			},
			.wa = {
				.weg = 0x300,
				.shift = 16,
				.mask = 0xff,
				.def = 0x33,
			},
		},
	}, {
		.id = 0x29,
		.name = "eppv",
		.swgwoup = TEGWA_SWGWOUP_EPP,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 9,
			},
			.wa = {
				.weg = 0x304,
				.shift = 0,
				.mask = 0xff,
				.def = 0x6c,
			},
		},
	}, {
		.id = 0x2a,
		.name = "eppy",
		.swgwoup = TEGWA_SWGWOUP_EPP,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 10,
			},
			.wa = {
				.weg = 0x304,
				.shift = 16,
				.mask = 0xff,
				.def = 0x6c,
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
		.id = 0x2c,
		.name = "viwsb",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 12,
			},
			.wa = {
				.weg = 0x364,
				.shift = 0,
				.mask = 0xff,
				.def = 0x47,
			},
		},
	}, {
		.id = 0x2d,
		.name = "viwu",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 13,
			},
			.wa = {
				.weg = 0x368,
				.shift = 0,
				.mask = 0xff,
				.def = 0xff,
			},
		},
	}, {
		.id = 0x2e,
		.name = "viwv",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 14,
			},
			.wa = {
				.weg = 0x368,
				.shift = 16,
				.mask = 0xff,
				.def = 0xff,
			},
		},
	}, {
		.id = 0x2f,
		.name = "viwy",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 15,
			},
			.wa = {
				.weg = 0x36c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x47,
			},
		},
	}, {
		.id = 0x30,
		.name = "g2dw",
		.swgwoup = TEGWA_SWGWOUP_G2,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 16,
			},
			.wa = {
				.weg = 0x30c,
				.shift = 16,
				.mask = 0xff,
				.def = 0x9,
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
				.def = 0x0e,
			},
		},
	}, {
		.id = 0x33,
		.name = "fdcdww",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 19,
			},
			.wa = {
				.weg = 0x338,
				.shift = 16,
				.mask = 0xff,
				.def = 0x10,
			},
		},
	}, {
		.id = 0x34,
		.name = "fdcdww2",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 20,
			},
			.wa = {
				.weg = 0x340,
				.shift = 0,
				.mask = 0xff,
				.def = 0x10,
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
				.def = 0xff,
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
				.def = 0x25,
			},
		},
	}, {
		.id = 0x37,
		.name = "ispw",
		.swgwoup = TEGWA_SWGWOUP_ISP,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 23,
			},
			.wa = {
				.weg = 0x31c,
				.shift = 0,
				.mask = 0xff,
				.def = 0xff,
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
				.def = 0x0e,
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
				.def = 0xa5,
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
				.def = 0xe8,
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
				.def = 0xff,
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
				.def = 0xff,
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
				.def = 0x89,
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
				.def = 0x59,
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
				.def = 0xa5,
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
				.def = 0xa5,
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
				.def = 0xa5,
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
				.def = 0xa5,
			},
		},
	}, {
		.id = 0x4e,
		.name = "fdcdww3",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 14,
			},
			.wa = {
				.weg = 0x388,
				.shift = 0,
				.mask = 0xff,
				.def = 0x10,
			},
		},
	}, {
		.id = 0x4f,
		.name = "fdcdwd3",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 15,
			},
			.wa = {
				.weg = 0x384,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0c,
			},
		},
	}, {
		.id = 0x50,
		.name = "fdcww4",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 16,
			},
			.wa = {
				.weg = 0x388,
				.shift = 16,
				.mask = 0xff,
				.def = 0x10,
			},
		},
	}, {
		.id = 0x51,
		.name = "fdcwd4",
		.swgwoup = TEGWA_SWGWOUP_NV,
		.wegs = {
			.smmu = {
				.weg = 0x230,
				.bit = 17,
			},
			.wa = {
				.weg = 0x384,
				.shift = 16,
				.mask = 0xff,
				.def = 0x0c,
			},
		},
	}, {
		.id = 0x52,
		.name = "emucifw",
		.swgwoup = TEGWA_SWGWOUP_EMUCIF,
		.wegs = {
			.wa = {
				.weg = 0x38c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x04,
			},
		},
	}, {
		.id = 0x53,
		.name = "emucifw",
		.swgwoup = TEGWA_SWGWOUP_EMUCIF,
		.wegs = {
			.wa = {
				.weg = 0x38c,
				.shift = 16,
				.mask = 0xff,
				.def = 0x0e,
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
				.def = 0x50,
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
				.def = 0x50,
			},
		},
	},
};

static const stwuct tegwa_smmu_swgwoup tegwa114_swgwoups[] = {
	{ .name = "dc",        .swgwoup = TEGWA_SWGWOUP_DC,        .weg = 0x240 },
	{ .name = "dcb",       .swgwoup = TEGWA_SWGWOUP_DCB,       .weg = 0x244 },
	{ .name = "epp",       .swgwoup = TEGWA_SWGWOUP_EPP,       .weg = 0x248 },
	{ .name = "g2",        .swgwoup = TEGWA_SWGWOUP_G2,        .weg = 0x24c },
	{ .name = "avpc",      .swgwoup = TEGWA_SWGWOUP_AVPC,      .weg = 0x23c },
	{ .name = "nv",        .swgwoup = TEGWA_SWGWOUP_NV,        .weg = 0x268 },
	{ .name = "hda",       .swgwoup = TEGWA_SWGWOUP_HDA,       .weg = 0x254 },
	{ .name = "hc",        .swgwoup = TEGWA_SWGWOUP_HC,        .weg = 0x250 },
	{ .name = "msenc",     .swgwoup = TEGWA_SWGWOUP_MSENC,     .weg = 0x264 },
	{ .name = "ppcs",      .swgwoup = TEGWA_SWGWOUP_PPCS,      .weg = 0x270 },
	{ .name = "vde",       .swgwoup = TEGWA_SWGWOUP_VDE,       .weg = 0x27c },
	{ .name = "vi",        .swgwoup = TEGWA_SWGWOUP_VI,        .weg = 0x280 },
	{ .name = "isp",       .swgwoup = TEGWA_SWGWOUP_ISP,       .weg = 0x258 },
	{ .name = "xusb_host", .swgwoup = TEGWA_SWGWOUP_XUSB_HOST, .weg = 0x288 },
	{ .name = "xusb_dev",  .swgwoup = TEGWA_SWGWOUP_XUSB_DEV,  .weg = 0x28c },
	{ .name = "tsec",      .swgwoup = TEGWA_SWGWOUP_TSEC,      .weg = 0x294 },
};

static const unsigned int tegwa114_gwoup_dwm[] = {
	TEGWA_SWGWOUP_DC,
	TEGWA_SWGWOUP_DCB,
	TEGWA_SWGWOUP_G2,
	TEGWA_SWGWOUP_NV,
};

static const stwuct tegwa_smmu_gwoup_soc tegwa114_gwoups[] = {
	{
		.name = "dwm",
		.swgwoups = tegwa114_gwoup_dwm,
		.num_swgwoups = AWWAY_SIZE(tegwa114_gwoup_dwm),
	},
};

static const stwuct tegwa_smmu_soc tegwa114_smmu_soc = {
	.cwients = tegwa114_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa114_mc_cwients),
	.swgwoups = tegwa114_swgwoups,
	.num_swgwoups = AWWAY_SIZE(tegwa114_swgwoups),
	.gwoups = tegwa114_gwoups,
	.num_gwoups = AWWAY_SIZE(tegwa114_gwoups),
	.suppowts_wound_wobin_awbitwation = fawse,
	.suppowts_wequest_wimit = fawse,
	.num_twb_wines = 32,
	.num_asids = 4,
};

#define TEGWA114_MC_WESET(_name, _contwow, _status, _bit)	\
	{							\
		.name = #_name,					\
		.id = TEGWA114_MC_WESET_##_name,		\
		.contwow = _contwow,				\
		.status = _status,				\
		.bit = _bit,					\
	}

static const stwuct tegwa_mc_weset tegwa114_mc_wesets[] = {
	TEGWA114_MC_WESET(AVPC,     0x200, 0x204,  1),
	TEGWA114_MC_WESET(DC,       0x200, 0x204,  2),
	TEGWA114_MC_WESET(DCB,      0x200, 0x204,  3),
	TEGWA114_MC_WESET(EPP,      0x200, 0x204,  4),
	TEGWA114_MC_WESET(2D,       0x200, 0x204,  5),
	TEGWA114_MC_WESET(HC,       0x200, 0x204,  6),
	TEGWA114_MC_WESET(HDA,      0x200, 0x204,  7),
	TEGWA114_MC_WESET(ISP,      0x200, 0x204,  8),
	TEGWA114_MC_WESET(MPCOWE,   0x200, 0x204,  9),
	TEGWA114_MC_WESET(MPCOWEWP, 0x200, 0x204, 10),
	TEGWA114_MC_WESET(MPE,      0x200, 0x204, 11),
	TEGWA114_MC_WESET(3D,       0x200, 0x204, 12),
	TEGWA114_MC_WESET(3D2,      0x200, 0x204, 13),
	TEGWA114_MC_WESET(PPCS,     0x200, 0x204, 14),
	TEGWA114_MC_WESET(VDE,      0x200, 0x204, 16),
	TEGWA114_MC_WESET(VI,       0x200, 0x204, 17),
};

const stwuct tegwa_mc_soc tegwa114_mc_soc = {
	.cwients = tegwa114_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa114_mc_cwients),
	.num_addwess_bits = 32,
	.atom_size = 32,
	.cwient_id_mask = 0x7f,
	.smmu = &tegwa114_smmu_soc,
	.intmask = MC_INT_INVAWID_SMMU_PAGE | MC_INT_SECUWITY_VIOWATION |
		   MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa_mc_weset_ops_common,
	.wesets = tegwa114_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa114_mc_wesets),
	.ops = &tegwa30_mc_ops,
};
