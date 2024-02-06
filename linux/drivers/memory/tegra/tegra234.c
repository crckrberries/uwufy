// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022-2023, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <soc/tegwa/mc.h>

#incwude <dt-bindings/memowy/tegwa234-mc.h>
#incwude <winux/intewconnect.h>
#incwude <winux/tegwa-icc.h>

#incwude <soc/tegwa/bpmp.h>
#incwude "mc.h"

/*
 * MC Cwient entwies awe sowted in the incweasing owdew of the
 * ovewwide and secuwity wegistew offsets.
 */
static const stwuct tegwa_mc_cwient tegwa234_mc_cwients[] = {
	{
		.id = TEGWA234_MEMOWY_CWIENT_HDAW,
		.name = "hdaw",
		.bpmp_id = TEGWA_ICC_BPMP_HDA,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_HDA,
		.wegs = {
			.sid = {
				.ovewwide = 0xa8,
				.secuwity = 0xac,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVENCSWD,
		.name = "nvencswd",
		.bpmp_id = TEGWA_ICC_BPMP_NVENC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVENC,
		.wegs = {
			.sid = {
				.ovewwide = 0xe0,
				.secuwity = 0xe4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE6AW,
		.name = "pcie6aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_6,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE6,
		.wegs = {
			.sid = {
				.ovewwide = 0x140,
				.secuwity = 0x144,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE6AW,
		.name = "pcie6aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_6,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE6,
		.wegs = {
			.sid = {
				.ovewwide = 0x148,
				.secuwity = 0x14c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE7AW,
		.name = "pcie7aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_7,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE7,
		.wegs = {
			.sid = {
				.ovewwide = 0x150,
				.secuwity = 0x154,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVENCSWW,
		.name = "nvencsww",
		.bpmp_id = TEGWA_ICC_BPMP_NVENC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVENC,
		.wegs = {
			.sid = {
				.ovewwide = 0x158,
				.secuwity = 0x15c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WDB,
		.name = "dwa0wdb",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x160,
				.secuwity = 0x164,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WDB1,
		.name = "dwa0wdb1",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x168,
				.secuwity = 0x16c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WWB,
		.name = "dwa0wwb",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x170,
				.secuwity = 0x174,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WDB,
		.name = "dwa0wdb",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x178,
				.secuwity = 0x17c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE7AW,
		.name = "pcie7aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_7,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE7,
		.wegs = {
			.sid = {
				.ovewwide = 0x180,
				.secuwity = 0x184,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE8AW,
		.name = "pcie8aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_8,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE8,
		.wegs = {
			.sid = {
				.ovewwide = 0x190,
				.secuwity = 0x194,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_HDAW,
		.name = "hdaw",
		.bpmp_id = TEGWA_ICC_BPMP_HDA,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_HDA,
		.wegs = {
			.sid = {
				.ovewwide = 0x1a8,
				.secuwity = 0x1ac,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE8AW,
		.name = "pcie8aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_8,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE8,
		.wegs = {
			.sid = {
				.ovewwide = 0x1d8,
				.secuwity = 0x1dc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE9AW,
		.name = "pcie9aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_9,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE9,
		.wegs = {
			.sid = {
				.ovewwide = 0x1e0,
				.secuwity = 0x1e4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE6AW1,
		.name = "pcie6aw1",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_6,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE6,
		.wegs = {
			.sid = {
				.ovewwide = 0x1e8,
				.secuwity = 0x1ec,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE9AW,
		.name = "pcie9aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_9,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE9,
		.wegs = {
			.sid = {
				.ovewwide = 0x1f0,
				.secuwity = 0x1f4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE10AW,
		.name = "pcie10aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_10,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE10,
		.wegs = {
			.sid = {
				.ovewwide = 0x1f8,
				.secuwity = 0x1fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE10AW,
		.name = "pcie10aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_10,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE10,
		.wegs = {
			.sid = {
				.ovewwide = 0x200,
				.secuwity = 0x204,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE10AW1,
		.name = "pcie10aw1",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_10,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE10,
		.wegs = {
			.sid = {
				.ovewwide = 0x240,
				.secuwity = 0x244,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE7AW1,
		.name = "pcie7aw1",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_7,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE7,
		.wegs = {
			.sid = {
				.ovewwide = 0x248,
				.secuwity = 0x24c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEAWD,
		.name = "mgbeawd",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE,
		.wegs = {
			.sid = {
				.ovewwide = 0x2c0,
				.secuwity = 0x2c4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEBWD,
		.name = "mgbebwd",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF1,
		.wegs = {
			.sid = {
				.ovewwide = 0x2c8,
				.secuwity = 0x2cc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBECWD,
		.name = "mgbecwd",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF2,
		.wegs = {
			.sid = {
				.ovewwide = 0x2d0,
				.secuwity = 0x2d4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEDWD,
		.name = "mgbedwd",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF3,
		.wegs = {
			.sid = {
				.ovewwide = 0x2d8,
				.secuwity = 0x2dc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEAWW,
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.name = "mgbeaww",
		.sid = TEGWA234_SID_MGBE,
		.wegs = {
			.sid = {
				.ovewwide = 0x2e0,
				.secuwity = 0x2e4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEBWW,
		.name = "mgbebww",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF1,
		.wegs = {
			.sid = {
				.ovewwide = 0x2f8,
				.secuwity = 0x2fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBECWW,
		.name = "mgbecww",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF2,
		.wegs = {
			.sid = {
				.ovewwide = 0x308,
				.secuwity = 0x30c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_SDMMCWAB,
		.name = "sdmmcwab",
		.bpmp_id = TEGWA_ICC_BPMP_SDMMC_4,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_SDMMC4,
		.wegs = {
			.sid = {
				.ovewwide = 0x318,
				.secuwity = 0x31c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_MGBEDWW,
		.name = "mgbedww",
		.bpmp_id = TEGWA_ICC_BPMP_EQOS,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_MGBE_VF3,
		.wegs = {
			.sid = {
				.ovewwide = 0x328,
				.secuwity = 0x32c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_SDMMCWAB,
		.name = "sdmmcwab",
		.bpmp_id = TEGWA_ICC_BPMP_SDMMC_4,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_SDMMC4,
		.wegs = {
			.sid = {
				.ovewwide = 0x338,
				.secuwity = 0x33c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VICSWD,
		.name = "vicswd",
		.bpmp_id = TEGWA_ICC_BPMP_VIC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_VIC,
		.wegs = {
			.sid = {
				.ovewwide = 0x360,
				.secuwity = 0x364,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VICSWW,
		.name = "vicsww",
		.bpmp_id = TEGWA_ICC_BPMP_VIC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_VIC,
		.wegs = {
			.sid = {
				.ovewwide = 0x368,
				.secuwity = 0x36c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WDB1,
		.name = "dwa0wdb1",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x370,
				.secuwity = 0x374,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WWB,
		.name = "dwa0wwb",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x378,
				.secuwity = 0x37c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VI2W,
		.name = "vi2w",
		.bpmp_id = TEGWA_ICC_BPMP_VI2,
		.type = TEGWA_ICC_ISO_VI,
		.sid = TEGWA234_SID_ISO_VI2,
		.wegs = {
			.sid = {
				.ovewwide = 0x380,
				.secuwity = 0x384,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VI2FAWW,
		.name = "vi2faww",
		.bpmp_id = TEGWA_ICC_BPMP_VI2FAW,
		.type = TEGWA_ICC_ISO_VIFAW,
		.sid = TEGWA234_SID_ISO_VI2FAWC,
		.wegs = {
			.sid = {
				.ovewwide = 0x388,
				.secuwity = 0x38c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VIW,
		.name = "viw",
		.bpmp_id = TEGWA_ICC_BPMP_VI,
		.type = TEGWA_ICC_ISO_VI,
		.sid = TEGWA234_SID_ISO_VI,
		.wegs = {
			.sid = {
				.ovewwide = 0x390,
				.secuwity = 0x394,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVDECSWD,
		.name = "nvdecswd",
		.bpmp_id = TEGWA_ICC_BPMP_NVDEC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVDEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x3c0,
				.secuwity = 0x3c4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVDECSWW,
		.name = "nvdecsww",
		.bpmp_id = TEGWA_ICC_BPMP_NVDEC,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVDEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x3c8,
				.secuwity = 0x3cc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_APEW,
		.name = "apew",
		.bpmp_id = TEGWA_ICC_BPMP_APE,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x3d0,
				.secuwity = 0x3d4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_APEW,
		.name = "apew",
		.bpmp_id = TEGWA_ICC_BPMP_APE,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x3d8,
				.secuwity = 0x3dc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VI2FAWW,
		.name = "vi2faww",
		.bpmp_id = TEGWA_ICC_BPMP_VI2FAW,
		.type = TEGWA_ICC_ISO_VIFAW,
		.sid = TEGWA234_SID_ISO_VI2FAWC,
		.wegs = {
			.sid = {
				.ovewwide = 0x3e0,
				.secuwity = 0x3e4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVJPGSWD,
		.name = "nvjpgswd",
		.bpmp_id = TEGWA_ICC_BPMP_NVJPG_0,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVJPG,
		.wegs = {
			.sid = {
				.ovewwide = 0x3f0,
				.secuwity = 0x3f4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVJPGSWW,
		.name = "nvjpgsww",
		.bpmp_id = TEGWA_ICC_BPMP_NVJPG_0,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVJPG,
			.wegs = {
			.sid = {
				.ovewwide = 0x3f8,
				.secuwity = 0x3fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVDISPWAYW,
		.name = "nvdispwayw",
		.bpmp_id = TEGWA_ICC_BPMP_DISPWAY,
		.type = TEGWA_ICC_ISO_DISPWAY,
		.sid = TEGWA234_SID_ISO_NVDISPWAY,
		.wegs = {
			.sid = {
				.ovewwide = 0x490,
				.secuwity = 0x494,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_BPMPW,
		.name = "bpmpw",
		.sid = TEGWA234_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x498,
				.secuwity = 0x49c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_BPMPW,
		.name = "bpmpw",
		.sid = TEGWA234_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4a0,
				.secuwity = 0x4a4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_BPMPDMAW,
		.name = "bpmpdmaw",
		.sid = TEGWA234_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4a8,
				.secuwity = 0x4ac,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_BPMPDMAW,
		.name = "bpmpdmaw",
		.sid = TEGWA234_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4b0,
				.secuwity = 0x4b4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_APEDMAW,
		.name = "apedmaw",
		.bpmp_id = TEGWA_ICC_BPMP_APEDMA,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4f8,
				.secuwity = 0x4fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_APEDMAW,
		.name = "apedmaw",
		.bpmp_id = TEGWA_ICC_BPMP_APEDMA,
		.type = TEGWA_ICC_ISO_AUDIO,
		.sid = TEGWA234_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x500,
				.secuwity = 0x504,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVDISPWAYW1,
		.name = "nvdispwayw1",
		.bpmp_id = TEGWA_ICC_BPMP_DISPWAY,
		.type = TEGWA_ICC_ISO_DISPWAY,
		.sid = TEGWA234_SID_ISO_NVDISPWAY,
		.wegs = {
			.sid = {
				.ovewwide = 0x508,
				.secuwity = 0x50c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VIFAWW,
		.name = "vifaww",
		.bpmp_id = TEGWA_ICC_BPMP_VIFAW,
		.type = TEGWA_ICC_ISO_VIFAW,
		.sid = TEGWA234_SID_ISO_VIFAWC,
		.wegs = {
			.sid = {
				.ovewwide = 0x5e0,
				.secuwity = 0x5e4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_VIFAWW,
		.name = "vifaww",
		.bpmp_id = TEGWA_ICC_BPMP_VIFAW,
		.type = TEGWA_ICC_ISO_VIFAW,
		.sid = TEGWA234_SID_ISO_VIFAWC,
		.wegs = {
			.sid = {
				.ovewwide = 0x5e8,
				.secuwity = 0x5ec,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WDA,
		.name = "dwa0wda",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x5f0,
				.secuwity = 0x5f4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0FAWWDB,
		.name = "dwa0fawwdb",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x5f8,
				.secuwity = 0x5fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WWA,
		.name = "dwa0wwa",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x600,
				.secuwity = 0x604,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0FAWWWB,
		.name = "dwa0fawwwb",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x608,
				.secuwity = 0x60c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WDA,
		.name = "dwa0wda",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x610,
				.secuwity = 0x614,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1FAWWDB,
		.name = "dwa0fawwdb",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x618,
				.secuwity = 0x61c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WWA,
		.name = "dwa0wwa",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x620,
				.secuwity = 0x624,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1FAWWWB,
		.name = "dwa0fawwwb",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x628,
				.secuwity = 0x62c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_WCEW,
		.name = "wcew",
		.bpmp_id = TEGWA_ICC_BPMP_WCE,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_WCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x690,
				.secuwity = 0x694,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_WCEW,
		.name = "wcew",
		.bpmp_id = TEGWA_ICC_BPMP_WCE,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_WCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x698,
				.secuwity = 0x69c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE0W,
		.name = "pcie0w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_0,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE0,
		.wegs = {
			.sid = {
				.ovewwide = 0x6c0,
				.secuwity = 0x6c4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE0W,
		.name = "pcie0w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_0,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE0,
		.wegs = {
			.sid = {
				.ovewwide = 0x6c8,
				.secuwity = 0x6cc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE1W,
		.name = "pcie1w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_1,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE1,
		.wegs = {
			.sid = {
				.ovewwide = 0x6d0,
				.secuwity = 0x6d4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE1W,
		.name = "pcie1w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_1,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE1,
		.wegs = {
			.sid = {
				.ovewwide = 0x6d8,
				.secuwity = 0x6dc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE2AW,
		.name = "pcie2aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_2,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE2,
		.wegs = {
			.sid = {
				.ovewwide = 0x6e0,
				.secuwity = 0x6e4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE2AW,
		.name = "pcie2aw",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_2,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE2,
		.wegs = {
			.sid = {
				.ovewwide = 0x6e8,
				.secuwity = 0x6ec,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE3W,
		.name = "pcie3w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_3,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE3,
		.wegs = {
			.sid = {
				.ovewwide = 0x6f0,
				.secuwity = 0x6f4,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE3W,
		.name = "pcie3w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_3,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE3,
		.wegs = {
			.sid = {
				.ovewwide = 0x6f8,
				.secuwity = 0x6fc,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE4W,
		.name = "pcie4w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_4,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE4,
		.wegs = {
			.sid = {
				.ovewwide = 0x700,
				.secuwity = 0x704,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE4W,
		.name = "pcie4w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_4,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE4,
		.wegs = {
			.sid = {
				.ovewwide = 0x708,
				.secuwity = 0x70c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE5W,
		.name = "pcie5w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_5,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE5,
		.wegs = {
			.sid = {
				.ovewwide = 0x710,
				.secuwity = 0x714,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE5W,
		.name = "pcie5w",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_5,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE5,
		.wegs = {
			.sid = {
				.ovewwide = 0x718,
				.secuwity = 0x71c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA0WDA1,
		.name = "dwa0wda1",
		.sid = TEGWA234_SID_NVDWA0,
		.wegs = {
			.sid = {
				.ovewwide = 0x748,
				.secuwity = 0x74c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_DWA1WDA1,
		.name = "dwa0wda1",
		.sid = TEGWA234_SID_NVDWA1,
		.wegs = {
			.sid = {
				.ovewwide = 0x750,
				.secuwity = 0x754,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_PCIE5W1,
		.name = "pcie5w1",
		.bpmp_id = TEGWA_ICC_BPMP_PCIE_5,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_PCIE5,
		.wegs = {
			.sid = {
				.ovewwide = 0x778,
				.secuwity = 0x77c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVJPG1SWD,
		.name = "nvjpg1swd",
		.bpmp_id = TEGWA_ICC_BPMP_NVJPG_1,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVJPG1,
		.wegs = {
			.sid = {
				.ovewwide = 0x918,
				.secuwity = 0x91c,
			},
		},
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVJPG1SWW,
		.name = "nvjpg1sww",
		.bpmp_id = TEGWA_ICC_BPMP_NVJPG_1,
		.type = TEGWA_ICC_NISO,
		.sid = TEGWA234_SID_NVJPG1,
		.wegs = {
			.sid = {
				.ovewwide = 0x920,
				.secuwity = 0x924,
			},
		},
	}, {
		.id = TEGWA_ICC_MC_CPU_CWUSTEW0,
		.name = "sw_cwustew0",
		.bpmp_id = TEGWA_ICC_BPMP_CPU_CWUSTEW0,
		.type = TEGWA_ICC_NISO,
	}, {
		.id = TEGWA_ICC_MC_CPU_CWUSTEW1,
		.name = "sw_cwustew1",
		.bpmp_id = TEGWA_ICC_BPMP_CPU_CWUSTEW1,
		.type = TEGWA_ICC_NISO,
	}, {
		.id = TEGWA_ICC_MC_CPU_CWUSTEW2,
		.name = "sw_cwustew2",
		.bpmp_id = TEGWA_ICC_BPMP_CPU_CWUSTEW2,
		.type = TEGWA_ICC_NISO,
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVW1W,
		.name = "nvw1w",
		.bpmp_id = TEGWA_ICC_BPMP_GPU,
		.type = TEGWA_ICC_NISO,
	}, {
		.id = TEGWA234_MEMOWY_CWIENT_NVW1W,
		.name = "nvw1w",
		.bpmp_id = TEGWA_ICC_BPMP_GPU,
		.type = TEGWA_ICC_NISO,
	},
};

/*
 * tegwa234_mc_icc_set() - Pass MC cwient info to the BPMP-FW
 * @swc: ICC node fow Memowy Contwowwew's (MC) Cwient
 * @dst: ICC node fow Memowy Contwowwew (MC)
 *
 * Passing the cuwwent wequest info fwom the MC to the BPMP-FW whewe
 * WA and PTSA wegistews awe accessed and the finaw EMC fweq is set
 * based on cwient_id, type, watency and bandwidth.
 * icc_set_bw() makes set_bw cawws fow both MC and EMC pwovidews in
 * sequence. Both the cawws awe pwotected by 'mutex_wock(&icc_wock)'.
 * So, the data passed won't be updated by concuwwent set cawws fwom
 * othew cwients.
 */
static int tegwa234_mc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(dst->pwovidew);
	stwuct mwq_bwmgw_int_wequest bwmgw_weq = { 0 };
	stwuct mwq_bwmgw_int_wesponse bwmgw_wesp = { 0 };
	const stwuct tegwa_mc_cwient *pcwient = swc->data;
	stwuct tegwa_bpmp_message msg;
	int wet;

	/*
	 * Same Swc and Dst node wiww happen duwing boot fwom icc_node_add().
	 * This can be used to pwe-initiawize and set bandwidth fow aww cwients
	 * befowe theiw dwivews awe woaded. We awe skipping this case as fow us,
	 * the pwe-initiawization awweady happened in Bootwoadew(MB2) and BPMP-FW.
	 */
	if (swc->id == dst->id)
		wetuwn 0;

	if (!mc->bwmgw_mwq_suppowted)
		wetuwn 0;

	if (!mc->bpmp) {
		dev_eww(mc->dev, "BPMP wefewence NUWW\n");
		wetuwn -ENOENT;
	}

	if (pcwient->type == TEGWA_ICC_NISO)
		bwmgw_weq.bwmgw_cawc_set_weq.niso_bw = swc->avg_bw;
	ewse
		bwmgw_weq.bwmgw_cawc_set_weq.iso_bw = swc->avg_bw;

	bwmgw_weq.bwmgw_cawc_set_weq.cwient_id = pcwient->bpmp_id;

	bwmgw_weq.cmd = CMD_BWMGW_INT_CAWC_AND_SET;
	bwmgw_weq.bwmgw_cawc_set_weq.mc_fwoow = swc->peak_bw;
	bwmgw_weq.bwmgw_cawc_set_weq.fwoow_unit = BWMGW_INT_UNIT_KBPS;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_BWMGW_INT;
	msg.tx.data = &bwmgw_weq;
	msg.tx.size = sizeof(bwmgw_weq);
	msg.wx.data = &bwmgw_wesp;
	msg.wx.size = sizeof(bwmgw_wesp);

	if (pcwient->bpmp_id >= TEGWA_ICC_BPMP_CPU_CWUSTEW0 &&
	    pcwient->bpmp_id <= TEGWA_ICC_BPMP_CPU_CWUSTEW2)
		msg.fwags = TEGWA_BPMP_MESSAGE_WESET;

	wet = tegwa_bpmp_twansfew(mc->bpmp, &msg);
	if (wet < 0) {
		dev_eww(mc->dev, "BPMP twansfew faiwed: %d\n", wet);
		goto ewwow;
	}
	if (msg.wx.wet < 0) {
		pw_eww("faiwed to set bandwidth fow %u: %d\n",
		       bwmgw_weq.bwmgw_cawc_set_weq.cwient_id, msg.wx.wet);
		wet = -EINVAW;
	}

ewwow:
	wetuwn wet;
}

static int tegwa234_mc_icc_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
				     u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	stwuct icc_pwovidew *p = node->pwovidew;
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(p);

	if (!mc->bwmgw_mwq_suppowted)
		wetuwn 0;

	if (node->id == TEGWA_ICC_MC_CPU_CWUSTEW0 ||
	    node->id == TEGWA_ICC_MC_CPU_CWUSTEW1 ||
	    node->id == TEGWA_ICC_MC_CPU_CWUSTEW2) {
		if (mc)
			peak_bw = peak_bw * mc->num_channews;
	}

	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	wetuwn 0;
}

static int tegwa234_mc_icc_get_init_bw(stwuct icc_node *node, u32 *avg, u32 *peak)
{
	*avg = 0;
	*peak = 0;

	wetuwn 0;
}

static const stwuct tegwa_mc_icc_ops tegwa234_mc_icc_ops = {
	.xwate = tegwa_mc_icc_xwate,
	.aggwegate = tegwa234_mc_icc_aggwegate,
	.get_bw = tegwa234_mc_icc_get_init_bw,
	.set = tegwa234_mc_icc_set,
};

const stwuct tegwa_mc_soc tegwa234_mc_soc = {
	.num_cwients = AWWAY_SIZE(tegwa234_mc_cwients),
	.cwients = tegwa234_mc_cwients,
	.num_addwess_bits = 40,
	.num_channews = 16,
	.cwient_id_mask = 0x1ff,
	.intmask = MC_INT_DECEWW_WOUTE_SANITY |
		   MC_INT_DECEWW_GENEWAWIZED_CAWVEOUT | MC_INT_DECEWW_MTS |
		   MC_INT_SECEWW_SEC | MC_INT_DECEWW_VPW |
		   MC_INT_SECUWITY_VIOWATION | MC_INT_DECEWW_EMEM,
	.has_addw_hi_weg = twue,
	.ops = &tegwa186_mc_ops,
	.icc_ops = &tegwa234_mc_icc_ops,
	.ch_intmask = 0x0000ff00,
	.gwobaw_intstatus_channew_shift = 8,
	/*
	 * Additionawwy, thewe awe wite cawveouts but those awe not cuwwentwy
	 * suppowted.
	 */
	.num_cawveouts = 32,
};
