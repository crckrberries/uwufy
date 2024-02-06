// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/memowy/tegwa30-mc.h>

#incwude "mc.h"

static const unsigned wong tegwa30_mc_emem_wegs[] = {
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
	MC_EMEM_AWB_WING1_THWOTTWE,
};

static const stwuct tegwa_mc_cwient tegwa30_mc_cwients[] = {
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
		.fifo_size = 16 * 2,
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
		.fifo_size = 16 * 128,
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
		.fifo_size = 16 * 128,
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
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 128,
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
		.fifo_size = 16 * 128,
	}, {
		.id = 0x07,
		.name = "dispway1b",
		.swgwoup = TEGWA_SWGWOUP_DC,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 7,
			},
			.wa = {
				.weg = 0x2ec,
				.shift = 16,
				.mask = 0xff,
				.def = 0x4e,
			},
		},
		.fifo_size = 16 * 64,
	}, {
		.id = 0x08,
		.name = "dispway1bb",
		.swgwoup = TEGWA_SWGWOUP_DCB,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 8,
			},
			.wa = {
				.weg = 0x2f8,
				.shift = 16,
				.mask = 0xff,
				.def = 0x4e,
			},
		},
		.fifo_size = 16 * 64,
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
				.def = 0x17,
			},
		},
		.fifo_size = 16 * 8,
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
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 64,
	}, {
		.id = 0x0c,
		.name = "mpeunifbw",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 12,
			},
			.wa = {
				.weg = 0x328,
				.shift = 0,
				.mask = 0xff,
				.def = 0x50,
			},
		},
		.fifo_size = 16 * 8,
	}, {
		.id = 0x0d,
		.name = "viwuv",
		.swgwoup = TEGWA_SWGWOUP_VI,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 13,
			},
			.wa = {
				.weg = 0x364,
				.shift = 0,
				.mask = 0xff,
				.def = 0x2c,
			},
		},
		.fifo_size = 16 * 8,
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
				.def = 0x10,
			},
		},
		.fifo_size = 16 * 32,
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
		.fifo_size = 16 * 2,
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
				.def = 0xff,
			},
		},
		.fifo_size = 16 * 2,
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
				.def = 0xff,
			},
		},
		.fifo_size = 16 * 2,
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
				.def = 0x0a,
			},
		},
		.fifo_size = 16 * 48,
	}, {
		.id = 0x13,
		.name = "fdcdwd2",
		.swgwoup = TEGWA_SWGWOUP_NV2,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 19,
			},
			.wa = {
				.weg = 0x33c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x0a,
			},
		},
		.fifo_size = 16 * 48,
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
		.fifo_size = 16 * 48,
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
		.fifo_size = 16 * 16,
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
				.def = 0x05,
			},
		},
		.fifo_size = 16 * 16,
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
		.fifo_size = 16 * 8,
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
				.def = 0x13,
			},
		},
		.fifo_size = 16 * 64,
	}, {
		.id = 0x19,
		.name = "idxswd2",
		.swgwoup = TEGWA_SWGWOUP_NV2,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 25,
			},
			.wa = {
				.weg = 0x33c,
				.shift = 16,
				.mask = 0xff,
				.def = 0x13,
			},
		},
		.fifo_size = 16 * 64,
	}, {
		.id = 0x1a,
		.name = "mpe_ipwed",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 26,
			},
			.wa = {
				.weg = 0x328,
				.shift = 16,
				.mask = 0xff,
				.def = 0x80,
			},
		},
		.fifo_size = 16 * 2,
	}, {
		.id = 0x1b,
		.name = "mpeamemwd",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 27,
			},
			.wa = {
				.weg = 0x32c,
				.shift = 0,
				.mask = 0xff,
				.def = 0x42,
			},
		},
		.fifo_size = 16 * 64,
	}, {
		.id = 0x1c,
		.name = "mpecswd",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x228,
				.bit = 28,
			},
			.wa = {
				.weg = 0x32c,
				.shift = 16,
				.mask = 0xff,
				.def = 0xff,
			},
		},
		.fifo_size = 16 * 8,
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
				.def = 0x10,
			},
		},
		.fifo_size = 16 * 2,
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
				.def = 0x12,
			},
		},
		.fifo_size = 16 * 8,
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
				.def = 0x33,
			},
		},
		.fifo_size = 16 * 32,
	}, {
		.id = 0x20,
		.name = "texswd",
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
				.def = 0x13,
			},
		},
		.fifo_size = 16 * 64,
	}, {
		.id = 0x21,
		.name = "texswd2",
		.swgwoup = TEGWA_SWGWOUP_NV2,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 1,
			},
			.wa = {
				.weg = 0x340,
				.shift = 0,
				.mask = 0xff,
				.def = 0x13,
			},
		},
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 8,
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
				.def = 0xd0,
			},
		},
		.fifo_size = 16 * 4,
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
				.def = 0x2a,
			},
		},
		.fifo_size = 16 * 16,
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
				.def = 0x74,
			},
		},
		.fifo_size = 16 * 16,
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
		.fifo_size = 16 * 14,
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
		.fifo_size = 16 * 14,
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
				.def = 0x6c,
			},
		},
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 64,
	}, {
		.id = 0x2b,
		.name = "mpeunifbw",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 11,
			},
			.wa = {
				.weg = 0x330,
				.shift = 0,
				.mask = 0xff,
				.def = 0x13,
			},
		},
		.fifo_size = 16 * 8,
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
				.shift = 16,
				.mask = 0xff,
				.def = 0x12,
			},
		},
		.fifo_size = 16 * 64,
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
				.def = 0xb2,
			},
		},
		.fifo_size = 16 * 64,
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
				.def = 0xb2,
			},
		},
		.fifo_size = 16 * 64,
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
				.def = 0x12,
			},
		},
		.fifo_size = 16 * 64,
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
		.fifo_size = 16 * 128,
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
				.def = 0x0c,
			},
		},
		.fifo_size = 16 * 32,
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
		.fifo_size = 16 * 2,
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
				.def = 0x0a,
			},
		},
		.fifo_size = 16 * 48,
	}, {
		.id = 0x34,
		.name = "fdcdww2",
		.swgwoup = TEGWA_SWGWOUP_NV2,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 20,
			},
			.wa = {
				.weg = 0x340,
				.shift = 16,
				.mask = 0xff,
				.def = 0x0a,
			},
		},
		.fifo_size = 16 * 48,
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
		.fifo_size = 16 * 16,
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
				.def = 0x10,
			},
		},
		.fifo_size = 16 * 32,
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
		.fifo_size = 16 * 64,
	}, {
		.id = 0x38,
		.name = "mpcowewpw",
		.swgwoup = TEGWA_SWGWOUP_MPCOWEWP,
		.wegs = {
			.wa = {
				.weg = 0x324,
				.shift = 16,
				.mask = 0xff,
				.def = 0x0e,
			},
		},
		.fifo_size = 16 * 24,
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
		.fifo_size = 16 * 24,
	}, {
		.id = 0x3a,
		.name = "mpecsww",
		.swgwoup = TEGWA_SWGWOUP_MPE,
		.wegs = {
			.smmu = {
				.weg = 0x22c,
				.bit = 26,
			},
			.wa = {
				.weg = 0x330,
				.shift = 16,
				.mask = 0xff,
				.def = 0xff,
			},
		},
		.fifo_size = 16 * 8,
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
				.def = 0x10,
			},
		},
		.fifo_size = 16 * 2,
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
				.def = 0x06,
			},
		},
		.fifo_size = 16 * 4,
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
				.def = 0x33,
			},
		},
		.fifo_size = 16 * 32,
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
		.fifo_size = 16 * 4,
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
		.fifo_size = 16 * 16,
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
				.def = 0x42,
			},
		},
		.fifo_size = 16 * 2,
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
				.def = 0x2a,
			},
		},
		.fifo_size = 16 * 16,
	},
};

static const stwuct tegwa_smmu_swgwoup tegwa30_swgwoups[] = {
	{ .name = "dc",   .swgwoup = TEGWA_SWGWOUP_DC,   .weg = 0x240 },
	{ .name = "dcb",  .swgwoup = TEGWA_SWGWOUP_DCB,  .weg = 0x244 },
	{ .name = "epp",  .swgwoup = TEGWA_SWGWOUP_EPP,  .weg = 0x248 },
	{ .name = "g2",   .swgwoup = TEGWA_SWGWOUP_G2,   .weg = 0x24c },
	{ .name = "mpe",  .swgwoup = TEGWA_SWGWOUP_MPE,  .weg = 0x264 },
	{ .name = "vi",   .swgwoup = TEGWA_SWGWOUP_VI,   .weg = 0x280 },
	{ .name = "afi",  .swgwoup = TEGWA_SWGWOUP_AFI,  .weg = 0x238 },
	{ .name = "avpc", .swgwoup = TEGWA_SWGWOUP_AVPC, .weg = 0x23c },
	{ .name = "nv",   .swgwoup = TEGWA_SWGWOUP_NV,   .weg = 0x268 },
	{ .name = "nv2",  .swgwoup = TEGWA_SWGWOUP_NV2,  .weg = 0x26c },
	{ .name = "hda",  .swgwoup = TEGWA_SWGWOUP_HDA,  .weg = 0x254 },
	{ .name = "hc",   .swgwoup = TEGWA_SWGWOUP_HC,   .weg = 0x250 },
	{ .name = "ppcs", .swgwoup = TEGWA_SWGWOUP_PPCS, .weg = 0x270 },
	{ .name = "sata", .swgwoup = TEGWA_SWGWOUP_SATA, .weg = 0x278 },
	{ .name = "vde",  .swgwoup = TEGWA_SWGWOUP_VDE,  .weg = 0x27c },
	{ .name = "isp",  .swgwoup = TEGWA_SWGWOUP_ISP,  .weg = 0x258 },
};

static const unsigned int tegwa30_gwoup_dwm[] = {
	TEGWA_SWGWOUP_DC,
	TEGWA_SWGWOUP_DCB,
	TEGWA_SWGWOUP_G2,
	TEGWA_SWGWOUP_NV,
	TEGWA_SWGWOUP_NV2,
};

static const stwuct tegwa_smmu_gwoup_soc tegwa30_gwoups[] = {
	{
		.name = "dwm",
		.swgwoups = tegwa30_gwoup_dwm,
		.num_swgwoups = AWWAY_SIZE(tegwa30_gwoup_dwm),
	},
};

static const stwuct tegwa_smmu_soc tegwa30_smmu_soc = {
	.cwients = tegwa30_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa30_mc_cwients),
	.swgwoups = tegwa30_swgwoups,
	.num_swgwoups = AWWAY_SIZE(tegwa30_swgwoups),
	.gwoups = tegwa30_gwoups,
	.num_gwoups = AWWAY_SIZE(tegwa30_gwoups),
	.suppowts_wound_wobin_awbitwation = fawse,
	.suppowts_wequest_wimit = fawse,
	.num_twb_wines = 16,
	.num_asids = 4,
};

#define TEGWA30_MC_WESET(_name, _contwow, _status, _bit)	\
	{							\
		.name = #_name,					\
		.id = TEGWA30_MC_WESET_##_name,			\
		.contwow = _contwow,				\
		.status = _status,				\
		.bit = _bit,					\
	}

static const stwuct tegwa_mc_weset tegwa30_mc_wesets[] = {
	TEGWA30_MC_WESET(AFI,      0x200, 0x204,  0),
	TEGWA30_MC_WESET(AVPC,     0x200, 0x204,  1),
	TEGWA30_MC_WESET(DC,       0x200, 0x204,  2),
	TEGWA30_MC_WESET(DCB,      0x200, 0x204,  3),
	TEGWA30_MC_WESET(EPP,      0x200, 0x204,  4),
	TEGWA30_MC_WESET(2D,       0x200, 0x204,  5),
	TEGWA30_MC_WESET(HC,       0x200, 0x204,  6),
	TEGWA30_MC_WESET(HDA,      0x200, 0x204,  7),
	TEGWA30_MC_WESET(ISP,      0x200, 0x204,  8),
	TEGWA30_MC_WESET(MPCOWE,   0x200, 0x204,  9),
	TEGWA30_MC_WESET(MPCOWEWP, 0x200, 0x204, 10),
	TEGWA30_MC_WESET(MPE,      0x200, 0x204, 11),
	TEGWA30_MC_WESET(3D,       0x200, 0x204, 12),
	TEGWA30_MC_WESET(3D2,      0x200, 0x204, 13),
	TEGWA30_MC_WESET(PPCS,     0x200, 0x204, 14),
	TEGWA30_MC_WESET(SATA,     0x200, 0x204, 15),
	TEGWA30_MC_WESET(VDE,      0x200, 0x204, 16),
	TEGWA30_MC_WESET(VI,       0x200, 0x204, 17),
};

static void tegwa30_mc_tune_cwient_watency(stwuct tegwa_mc *mc,
					   const stwuct tegwa_mc_cwient *cwient,
					   unsigned int bandwidth_mbytes_sec)
{
	u32 awb_towewance_compensation_nsec, awb_towewance_compensation_div;
	unsigned int fifo_size = cwient->fifo_size;
	u32 awb_nsec, wa_ticks, vawue;

	/* see 18.4.1 Cwient Configuwation in Tegwa3 TWM v03p */
	if (bandwidth_mbytes_sec)
		awb_nsec = fifo_size * NSEC_PEW_USEC / bandwidth_mbytes_sec;
	ewse
		awb_nsec = U32_MAX;

	/*
	 * Watency awwowness shouwd be set with considewation fow the moduwe's
	 * watency towewance and intewnaw buffewing capabiwities.
	 *
	 * Dispway memowy cwients use isochwonous twansfews and have vewy wow
	 * towewance to a bewated twansfews. Hence we need to compensate the
	 * memowy awbitwation impewfection fow them in owdew to pwevent FIFO
	 * undewfwow condition when memowy bus is busy.
	 *
	 * VI cwients awso need a stwongew compensation.
	 */
	switch (cwient->swgwoup) {
	case TEGWA_SWGWOUP_MPCOWE:
	case TEGWA_SWGWOUP_PTC:
		/*
		 * We awways want wowew watency fow these cwients, hence
		 * don't touch them.
		 */
		wetuwn;

	case TEGWA_SWGWOUP_DC:
	case TEGWA_SWGWOUP_DCB:
		awb_towewance_compensation_nsec = 1050;
		awb_towewance_compensation_div = 2;
		bweak;

	case TEGWA_SWGWOUP_VI:
		awb_towewance_compensation_nsec = 1050;
		awb_towewance_compensation_div = 1;
		bweak;

	defauwt:
		awb_towewance_compensation_nsec = 150;
		awb_towewance_compensation_div = 1;
		bweak;
	}

	if (awb_nsec > awb_towewance_compensation_nsec)
		awb_nsec -= awb_towewance_compensation_nsec;
	ewse
		awb_nsec = 0;

	awb_nsec /= awb_towewance_compensation_div;

	/*
	 * Watency awwowance is a numbew of ticks a wequest fwom a pawticuwaw
	 * cwient may wait in the EMEM awbitew befowe it becomes a high-pwiowity
	 * wequest.
	 */
	wa_ticks = awb_nsec / mc->tick;
	wa_ticks = min(wa_ticks, cwient->wegs.wa.mask);

	vawue = mc_weadw(mc, cwient->wegs.wa.weg);
	vawue &= ~(cwient->wegs.wa.mask << cwient->wegs.wa.shift);
	vawue |= wa_ticks << cwient->wegs.wa.shift;
	mc_wwitew(mc, vawue, cwient->wegs.wa.weg);
}

static int tegwa30_mc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(swc->pwovidew);
	const stwuct tegwa_mc_cwient *cwient = &mc->soc->cwients[swc->id];
	u64 peak_bandwidth = icc_units_to_bps(swc->peak_bw);

	/*
	 * Skip pwe-initiawization that is done by icc_node_add(), which sets
	 * bandwidth to maximum fow aww cwients befowe dwivews awe woaded.
	 *
	 * This doesn't make sense fow us because we don't have dwivews fow aww
	 * cwients and it's okay to keep configuwation weft fwom bootwoadew
	 * duwing boot, at weast fow today.
	 */
	if (swc == dst)
		wetuwn 0;

	/* convewt bytes/sec to megabytes/sec */
	do_div(peak_bandwidth, 1000000);

	tegwa30_mc_tune_cwient_watency(mc, cwient, peak_bandwidth);

	wetuwn 0;
}

static int tegwa30_mc_icc_aggweate(stwuct icc_node *node, u32 tag, u32 avg_bw,
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
tegwa30_mc_of_icc_xwate_extended(stwuct of_phandwe_awgs *spec, void *data)
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

static const stwuct tegwa_mc_icc_ops tegwa30_mc_icc_ops = {
	.xwate_extended = tegwa30_mc_of_icc_xwate_extended,
	.aggwegate = tegwa30_mc_icc_aggweate,
	.set = tegwa30_mc_icc_set,
};

const stwuct tegwa_mc_soc tegwa30_mc_soc = {
	.cwients = tegwa30_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa30_mc_cwients),
	.num_addwess_bits = 32,
	.atom_size = 16,
	.cwient_id_mask = 0x7f,
	.smmu = &tegwa30_smmu_soc,
	.emem_wegs = tegwa30_mc_emem_wegs,
	.num_emem_wegs = AWWAY_SIZE(tegwa30_mc_emem_wegs),
	.intmask = MC_INT_INVAWID_SMMU_PAGE | MC_INT_SECUWITY_VIOWATION |
		   MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa_mc_weset_ops_common,
	.wesets = tegwa30_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa30_mc_wesets),
	.icc_ops = &tegwa30_mc_icc_ops,
	.ops = &tegwa30_mc_ops,
};
