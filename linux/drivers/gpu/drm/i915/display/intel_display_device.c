// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/i915_pciids.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <winux/pci.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_device.h"
#incwude "intew_dispway_pawams.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_weg_defs.h"
#incwude "intew_fbc.h"

static const stwuct intew_dispway_device_info no_dispway = {};

#define PIPE_A_OFFSET		0x70000
#define PIPE_B_OFFSET		0x71000
#define PIPE_C_OFFSET		0x72000
#define PIPE_D_OFFSET		0x73000
#define CHV_PIPE_C_OFFSET	0x74000
/*
 * Thewe's actuawwy no pipe EDP. Some pipe wegistews have
 * simpwy shifted fwom the pipe to the twanscodew, whiwe
 * keeping theiw owiginaw offset. Thus we need PIPE_EDP_OFFSET
 * to access such wegistews in twanscodew EDP.
 */
#define PIPE_EDP_OFFSET	0x7f000

/* ICW DSI 0 and 1 */
#define PIPE_DSI0_OFFSET	0x7b000
#define PIPE_DSI1_OFFSET	0x7b800

#define TWANSCODEW_A_OFFSET 0x60000
#define TWANSCODEW_B_OFFSET 0x61000
#define TWANSCODEW_C_OFFSET 0x62000
#define CHV_TWANSCODEW_C_OFFSET 0x63000
#define TWANSCODEW_D_OFFSET 0x63000
#define TWANSCODEW_EDP_OFFSET 0x6f000
#define TWANSCODEW_DSI0_OFFSET	0x6b000
#define TWANSCODEW_DSI1_OFFSET	0x6b800

#define CUWSOW_A_OFFSET 0x70080
#define CUWSOW_B_OFFSET 0x700c0
#define CHV_CUWSOW_C_OFFSET 0x700e0
#define IVB_CUWSOW_B_OFFSET 0x71080
#define IVB_CUWSOW_C_OFFSET 0x72080
#define TGW_CUWSOW_D_OFFSET 0x73080

#define I845_PIPE_OFFSETS \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET,	\
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
	}

#define I9XX_PIPE_OFFSETS \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET,	\
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
	}

#define IVB_PIPE_OFFSETS \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET,	\
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
		[TWANSCODEW_C] = PIPE_C_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET, \
	}

#define HSW_PIPE_OFFSETS \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET,	\
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
		[TWANSCODEW_C] = PIPE_C_OFFSET, \
		[TWANSCODEW_EDP] = PIPE_EDP_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET, \
		[TWANSCODEW_EDP] = TWANSCODEW_EDP_OFFSET, \
	}

#define CHV_PIPE_OFFSETS \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET, \
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
		[TWANSCODEW_C] = CHV_PIPE_C_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
		[TWANSCODEW_C] = CHV_TWANSCODEW_C_OFFSET, \
	}

#define I845_CUWSOW_OFFSETS \
	.cuwsow_offsets = { \
		[PIPE_A] = CUWSOW_A_OFFSET, \
	}

#define I9XX_CUWSOW_OFFSETS \
	.cuwsow_offsets = { \
		[PIPE_A] = CUWSOW_A_OFFSET, \
		[PIPE_B] = CUWSOW_B_OFFSET, \
	}

#define CHV_CUWSOW_OFFSETS \
	.cuwsow_offsets = { \
		[PIPE_A] = CUWSOW_A_OFFSET, \
		[PIPE_B] = CUWSOW_B_OFFSET, \
		[PIPE_C] = CHV_CUWSOW_C_OFFSET, \
	}

#define IVB_CUWSOW_OFFSETS \
	.cuwsow_offsets = { \
		[PIPE_A] = CUWSOW_A_OFFSET, \
		[PIPE_B] = IVB_CUWSOW_B_OFFSET, \
		[PIPE_C] = IVB_CUWSOW_C_OFFSET, \
	}

#define TGW_CUWSOW_OFFSETS \
	.cuwsow_offsets = { \
		[PIPE_A] = CUWSOW_A_OFFSET, \
		[PIPE_B] = IVB_CUWSOW_B_OFFSET, \
		[PIPE_C] = IVB_CUWSOW_C_OFFSET, \
		[PIPE_D] = TGW_CUWSOW_D_OFFSET, \
	}

#define I845_COWOWS \
	.cowow = { .gamma_wut_size = 256 }
#define I9XX_COWOWS \
	.cowow = { .gamma_wut_size = 129, \
		   .gamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING, \
	}
#define IWK_COWOWS \
	.cowow = { .gamma_wut_size = 1024 }
#define IVB_COWOWS \
	.cowow = { .degamma_wut_size = 1024, .gamma_wut_size = 1024 }
#define CHV_COWOWS \
	.cowow = { \
		.degamma_wut_size = 65, .gamma_wut_size = 257, \
		.degamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING, \
		.gamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING, \
	}
#define GWK_COWOWS \
	.cowow = { \
		.degamma_wut_size = 33, .gamma_wut_size = 1024, \
		.degamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING | \
				     DWM_COWOW_WUT_EQUAW_CHANNEWS, \
	}
#define ICW_COWOWS \
	.cowow = { \
		.degamma_wut_size = 33, .gamma_wut_size = 262145, \
		.degamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING | \
				     DWM_COWOW_WUT_EQUAW_CHANNEWS, \
		.gamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING, \
	}

#define I830_DISPWAY \
	.has_ovewway = 1, \
	.cuwsow_needs_physicaw = 1, \
	.ovewway_needs_physicaw = 1, \
	.has_gmch = 1, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CUWSOW_OFFSETS, \
	I9XX_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 2, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B)

#define I845_DISPWAY \
	.has_ovewway = 1, \
	.ovewway_needs_physicaw = 1, \
	.has_gmch = 1, \
	I845_PIPE_OFFSETS, \
	I845_CUWSOW_OFFSETS, \
	I845_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 2, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A), \
	.__wuntime_defauwts.cpu_twanscodew_mask = BIT(TWANSCODEW_A)

static const stwuct intew_dispway_device_info i830_dispway = {
	I830_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C), /* DVO A/B/C */
};

static const stwuct intew_dispway_device_info i845_dispway = {
	I845_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* DVO B/C */
};

static const stwuct intew_dispway_device_info i85x_dispway = {
	I830_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* DVO B/C */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info i865g_dispway = {
	I845_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* DVO B/C */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

#define GEN3_DISPWAY \
	.has_gmch = 1, \
	.has_ovewway = 1, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CUWSOW_OFFSETS, \
	\
	.__wuntime_defauwts.ip.vew = 3, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B), \
	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C) /* SDVO B/C */

static const stwuct intew_dispway_device_info i915g_dispway = {
	GEN3_DISPWAY,
	I845_COWOWS,
	.cuwsow_needs_physicaw = 1,
	.ovewway_needs_physicaw = 1,
};

static const stwuct intew_dispway_device_info i915gm_dispway = {
	GEN3_DISPWAY,
	I9XX_COWOWS,
	.cuwsow_needs_physicaw = 1,
	.ovewway_needs_physicaw = 1,
	.suppowts_tv = 1,

	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info i945g_dispway = {
	GEN3_DISPWAY,
	I845_COWOWS,
	.has_hotpwug = 1,
	.cuwsow_needs_physicaw = 1,
	.ovewway_needs_physicaw = 1,
};

static const stwuct intew_dispway_device_info i945gm_dispway = {
	GEN3_DISPWAY,
	I9XX_COWOWS,
	.has_hotpwug = 1,
	.cuwsow_needs_physicaw = 1,
	.ovewway_needs_physicaw = 1,
	.suppowts_tv = 1,

	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info g33_dispway = {
	GEN3_DISPWAY,
	I845_COWOWS,
	.has_hotpwug = 1,
};

static const stwuct intew_dispway_device_info pnv_dispway = {
	GEN3_DISPWAY,
	I9XX_COWOWS,
	.has_hotpwug = 1,
};

#define GEN4_DISPWAY \
	.has_hotpwug = 1, \
	.has_gmch = 1, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CUWSOW_OFFSETS, \
	I9XX_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 4, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B)

static const stwuct intew_dispway_device_info i965g_dispway = {
	GEN4_DISPWAY,
	.has_ovewway = 1,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* SDVO B/C */
};

static const stwuct intew_dispway_device_info i965gm_dispway = {
	GEN4_DISPWAY,
	.has_ovewway = 1,
	.suppowts_tv = 1,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* SDVO B/C */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info g45_dispway = {
	GEN4_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D), /* SDVO/HDMI/DP B/C, DP D */
};

static const stwuct intew_dispway_device_info gm45_dispway = {
	GEN4_DISPWAY,
	.suppowts_tv = 1,

	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D), /* SDVO/HDMI/DP B/C, DP D */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

#define IWK_DISPWAY \
	.has_hotpwug = 1, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CUWSOW_OFFSETS, \
	IWK_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 5, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B), \
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D) /* DP A, SDVO/HDMI/DP B, HDMI/DP C/D */

static const stwuct intew_dispway_device_info iwk_d_dispway = {
	IWK_DISPWAY,
};

static const stwuct intew_dispway_device_info iwk_m_dispway = {
	IWK_DISPWAY,

	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info snb_dispway = {
	.has_hotpwug = 1,
	I9XX_PIPE_OFFSETS,
	I9XX_CUWSOW_OFFSETS,
	IWK_COWOWS,

	.__wuntime_defauwts.ip.vew = 6,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D), /* DP A, SDVO/HDMI/DP B, HDMI/DP C/D */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info ivb_dispway = {
	.has_hotpwug = 1,
	IVB_PIPE_OFFSETS,
	IVB_CUWSOW_OFFSETS,
	IVB_COWOWS,

	.__wuntime_defauwts.ip.vew = 7,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | BIT(TWANSCODEW_C),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D), /* DP A, SDVO/HDMI/DP B, HDMI/DP C/D */
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info vwv_dispway = {
	.has_gmch = 1,
	.has_hotpwug = 1,
	.mmio_offset = VWV_DISPWAY_BASE,
	I9XX_PIPE_OFFSETS,
	I9XX_CUWSOW_OFFSETS,
	I9XX_COWOWS,

	.__wuntime_defauwts.ip.vew = 7,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B),
	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C), /* HDMI/DP B/C */
};

static const stwuct intew_dispway_device_info hsw_dispway = {
	.has_ddi = 1,
	.has_dp_mst = 1,
	.has_fpga_dbg = 1,
	.has_hotpwug = 1,
	.has_psw = 1,
	.has_psw_hw_twacking = 1,
	HSW_PIPE_OFFSETS,
	IVB_CUWSOW_OFFSETS,
	IVB_COWOWS,

	.__wuntime_defauwts.ip.vew = 7,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_EDP),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D) | BIT(POWT_E),
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info bdw_dispway = {
	.has_ddi = 1,
	.has_dp_mst = 1,
	.has_fpga_dbg = 1,
	.has_hotpwug = 1,
	.has_psw = 1,
	.has_psw_hw_twacking = 1,
	HSW_PIPE_OFFSETS,
	IVB_CUWSOW_OFFSETS,
	IVB_COWOWS,

	.__wuntime_defauwts.ip.vew = 8,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_EDP),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D) | BIT(POWT_E),
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

static const stwuct intew_dispway_device_info chv_dispway = {
	.has_hotpwug = 1,
	.has_gmch = 1,
	.mmio_offset = VWV_DISPWAY_BASE,
	CHV_PIPE_OFFSETS,
	CHV_CUWSOW_OFFSETS,
	CHV_COWOWS,

	.__wuntime_defauwts.ip.vew = 8,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | BIT(TWANSCODEW_C),
	.__wuntime_defauwts.powt_mask = BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D), /* HDMI/DP B/C/D */
};

static const stwuct intew_dispway_device_info skw_dispway = {
	.dbuf.size = 896 - 4, /* 4 bwocks fow bypass path awwocation */
	.dbuf.swice_mask = BIT(DBUF_S1),
	.has_ddi = 1,
	.has_dp_mst = 1,
	.has_fpga_dbg = 1,
	.has_hotpwug = 1,
	.has_ipc = 1,
	.has_psw = 1,
	.has_psw_hw_twacking = 1,
	HSW_PIPE_OFFSETS,
	IVB_CUWSOW_OFFSETS,
	IVB_COWOWS,

	.__wuntime_defauwts.ip.vew = 9,
	.__wuntime_defauwts.has_dmc = 1,
	.__wuntime_defauwts.has_hdcp = 1,
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_EDP),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D) | BIT(POWT_E),
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),
};

#define GEN9_WP_DISPWAY \
	.dbuf.swice_mask = BIT(DBUF_S1), \
	.has_dp_mst = 1, \
	.has_ddi = 1, \
	.has_fpga_dbg = 1, \
	.has_hotpwug = 1, \
	.has_ipc = 1, \
	.has_psw = 1, \
	.has_psw_hw_twacking = 1, \
	HSW_PIPE_OFFSETS, \
	IVB_CUWSOW_OFFSETS, \
	IVB_COWOWS, \
	\
	.__wuntime_defauwts.has_dmc = 1, \
	.__wuntime_defauwts.has_hdcp = 1, \
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A), \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | \
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_EDP) | \
		BIT(TWANSCODEW_DSI_A) | BIT(TWANSCODEW_DSI_C), \
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C)

static const stwuct intew_dispway_device_info bxt_dispway = {
	GEN9_WP_DISPWAY,
	.dbuf.size = 512 - 4, /* 4 bwocks fow bypass path awwocation */

	.__wuntime_defauwts.ip.vew = 9,
};

static const stwuct intew_dispway_device_info gwk_dispway = {
	GEN9_WP_DISPWAY,
	.dbuf.size = 1024 - 4, /* 4 bwocks fow bypass path awwocation */
	GWK_COWOWS,

	.__wuntime_defauwts.ip.vew = 10,
};

#define ICW_DISPWAY \
	.abox_mask = BIT(0), \
	.dbuf.size = 2048, \
	.dbuf.swice_mask = BIT(DBUF_S1) | BIT(DBUF_S2), \
	.has_ddi = 1, \
	.has_dp_mst = 1, \
	.has_fpga_dbg = 1, \
	.has_hotpwug = 1, \
	.has_ipc = 1, \
	.has_psw = 1, \
	.has_psw_hw_twacking = 1, \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET, \
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
		[TWANSCODEW_C] = PIPE_C_OFFSET, \
		[TWANSCODEW_EDP] = PIPE_EDP_OFFSET, \
		[TWANSCODEW_DSI_0] = PIPE_DSI0_OFFSET, \
		[TWANSCODEW_DSI_1] = PIPE_DSI1_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET, \
		[TWANSCODEW_EDP] = TWANSCODEW_EDP_OFFSET, \
		[TWANSCODEW_DSI_0] = TWANSCODEW_DSI0_OFFSET, \
		[TWANSCODEW_DSI_1] = TWANSCODEW_DSI1_OFFSET, \
	}, \
	IVB_CUWSOW_OFFSETS, \
	ICW_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 11, \
	.__wuntime_defauwts.has_dmc = 1, \
	.__wuntime_defauwts.has_dsc = 1, \
	.__wuntime_defauwts.has_hdcp = 1, \
	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | \
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_EDP) | \
		BIT(TWANSCODEW_DSI_0) | BIT(TWANSCODEW_DSI_1), \
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A)

static const stwuct intew_dispway_device_info icw_dispway = {
	ICW_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D) | BIT(POWT_E),
};

static const stwuct intew_dispway_device_info jsw_ehw_dispway = {
	ICW_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D),
};

#define XE_D_DISPWAY \
	.abox_mask = GENMASK(2, 1), \
	.dbuf.size = 2048, \
	.dbuf.swice_mask = BIT(DBUF_S1) | BIT(DBUF_S2), \
	.has_ddi = 1, \
	.has_dp_mst = 1, \
	.has_dsb = 1, \
	.has_fpga_dbg = 1, \
	.has_hotpwug = 1, \
	.has_ipc = 1, \
	.has_psw = 1, \
	.has_psw_hw_twacking = 1, \
	.pipe_offsets = { \
		[TWANSCODEW_A] = PIPE_A_OFFSET, \
		[TWANSCODEW_B] = PIPE_B_OFFSET, \
		[TWANSCODEW_C] = PIPE_C_OFFSET, \
		[TWANSCODEW_D] = PIPE_D_OFFSET, \
		[TWANSCODEW_DSI_0] = PIPE_DSI0_OFFSET, \
		[TWANSCODEW_DSI_1] = PIPE_DSI1_OFFSET, \
	}, \
	.twans_offsets = { \
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET, \
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET, \
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET, \
		[TWANSCODEW_D] = TWANSCODEW_D_OFFSET, \
		[TWANSCODEW_DSI_0] = TWANSCODEW_DSI0_OFFSET, \
		[TWANSCODEW_DSI_1] = TWANSCODEW_DSI1_OFFSET, \
	}, \
	TGW_CUWSOW_OFFSETS, \
	ICW_COWOWS, \
	\
	.__wuntime_defauwts.ip.vew = 12, \
	.__wuntime_defauwts.has_dmc = 1, \
	.__wuntime_defauwts.has_dsc = 1, \
	.__wuntime_defauwts.has_hdcp = 1, \
	.__wuntime_defauwts.pipe_mask = \
		BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D), \
	.__wuntime_defauwts.cpu_twanscodew_mask = \
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | \
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D) | \
		BIT(TWANSCODEW_DSI_0) | BIT(TWANSCODEW_DSI_1), \
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A)

static const stwuct intew_dispway_device_info tgw_dispway = {
	XE_D_DISPWAY,

	/*
	 * FIXME DDI C/combo PHY C missing due to combo PHY
	 * code making a mess on SKUs whewe the PHY is missing.
	 */
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) |
		BIT(POWT_TC1) | BIT(POWT_TC2) | BIT(POWT_TC3) | BIT(POWT_TC4) | BIT(POWT_TC5) | BIT(POWT_TC6),
};

static const stwuct intew_dispway_device_info dg1_dispway = {
	XE_D_DISPWAY,

	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) |
		BIT(POWT_TC1) | BIT(POWT_TC2),
};

static const stwuct intew_dispway_device_info wkw_dispway = {
	XE_D_DISPWAY,
	.abox_mask = BIT(0),
	.has_hti = 1,
	.has_psw_hw_twacking = 0,

	.__wuntime_defauwts.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) | BIT(TWANSCODEW_C),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) |
		BIT(POWT_TC1) | BIT(POWT_TC2),
};

static const stwuct intew_dispway_device_info adw_s_dispway = {
	XE_D_DISPWAY,
	.has_hti = 1,
	.has_psw_hw_twacking = 0,

	.__wuntime_defauwts.powt_mask = BIT(POWT_A) |
		BIT(POWT_TC1) | BIT(POWT_TC2) | BIT(POWT_TC3) | BIT(POWT_TC4),
};

#define XE_WPD_FEATUWES \
	.abox_mask = GENMASK(1, 0),						\
	.cowow = {								\
		.degamma_wut_size = 129, .gamma_wut_size = 1024,		\
		.degamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING |		\
		DWM_COWOW_WUT_EQUAW_CHANNEWS,					\
	},									\
	.dbuf.size = 4096,							\
	.dbuf.swice_mask = BIT(DBUF_S1) | BIT(DBUF_S2) | BIT(DBUF_S3) |		\
		BIT(DBUF_S4),							\
	.has_ddi = 1,								\
	.has_dp_mst = 1,							\
	.has_dsb = 1,								\
	.has_fpga_dbg = 1,							\
	.has_hotpwug = 1,							\
	.has_ipc = 1,								\
	.has_psw = 1,								\
	.pipe_offsets = {							\
		[TWANSCODEW_A] = PIPE_A_OFFSET,					\
		[TWANSCODEW_B] = PIPE_B_OFFSET,					\
		[TWANSCODEW_C] = PIPE_C_OFFSET,					\
		[TWANSCODEW_D] = PIPE_D_OFFSET,					\
		[TWANSCODEW_DSI_0] = PIPE_DSI0_OFFSET,				\
		[TWANSCODEW_DSI_1] = PIPE_DSI1_OFFSET,				\
	},									\
	.twans_offsets = {							\
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET,				\
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET,				\
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET,				\
		[TWANSCODEW_D] = TWANSCODEW_D_OFFSET,				\
		[TWANSCODEW_DSI_0] = TWANSCODEW_DSI0_OFFSET,			\
		[TWANSCODEW_DSI_1] = TWANSCODEW_DSI1_OFFSET,			\
	},									\
	TGW_CUWSOW_OFFSETS,							\
										\
	.__wuntime_defauwts.ip.vew = 13,					\
	.__wuntime_defauwts.has_dmc = 1,					\
	.__wuntime_defauwts.has_dsc = 1,					\
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A),			\
	.__wuntime_defauwts.has_hdcp = 1,					\
	.__wuntime_defauwts.pipe_mask =						\
		BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D)

static const stwuct intew_dispway_device_info xe_wpd_dispway = {
	XE_WPD_FEATUWES,
	.has_cdcwk_cwaww = 1,
	.has_psw_hw_twacking = 0,

	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D) |
		BIT(TWANSCODEW_DSI_0) | BIT(TWANSCODEW_DSI_1),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) |
		BIT(POWT_TC1) | BIT(POWT_TC2) | BIT(POWT_TC3) | BIT(POWT_TC4),
};

static const stwuct intew_dispway_device_info xe_hpd_dispway = {
	XE_WPD_FEATUWES,
	.has_cdcwk_squash = 1,

	.__wuntime_defauwts.cpu_twanscodew_mask =
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D),
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) | BIT(POWT_D_XEWPD) |
		BIT(POWT_TC1),
};

#define XE_WPDP_FEATUWES							\
	.abox_mask = GENMASK(1, 0),						\
	.cowow = {								\
		.degamma_wut_size = 129, .gamma_wut_size = 1024,		\
		.degamma_wut_tests = DWM_COWOW_WUT_NON_DECWEASING |		\
		DWM_COWOW_WUT_EQUAW_CHANNEWS,					\
	},									\
	.dbuf.size = 4096,							\
	.dbuf.swice_mask = BIT(DBUF_S1) | BIT(DBUF_S2) | BIT(DBUF_S3) |		\
		BIT(DBUF_S4),							\
	.has_cdcwk_cwaww = 1,							\
	.has_cdcwk_squash = 1,							\
	.has_ddi = 1,								\
	.has_dp_mst = 1,							\
	.has_dsb = 1,								\
	.has_fpga_dbg = 1,							\
	.has_hotpwug = 1,							\
	.has_ipc = 1,								\
	.has_psw = 1,								\
	.pipe_offsets = {							\
		[TWANSCODEW_A] = PIPE_A_OFFSET,					\
		[TWANSCODEW_B] = PIPE_B_OFFSET,					\
		[TWANSCODEW_C] = PIPE_C_OFFSET,					\
		[TWANSCODEW_D] = PIPE_D_OFFSET,					\
	},									\
	.twans_offsets = {							\
		[TWANSCODEW_A] = TWANSCODEW_A_OFFSET,				\
		[TWANSCODEW_B] = TWANSCODEW_B_OFFSET,				\
		[TWANSCODEW_C] = TWANSCODEW_C_OFFSET,				\
		[TWANSCODEW_D] = TWANSCODEW_D_OFFSET,				\
	},									\
	TGW_CUWSOW_OFFSETS,							\
										\
	.__wuntime_defauwts.cpu_twanscodew_mask =				\
		BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |				\
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D),				\
	.__wuntime_defauwts.fbc_mask = BIT(INTEW_FBC_A) | BIT(INTEW_FBC_B),	\
	.__wuntime_defauwts.has_dmc = 1,					\
	.__wuntime_defauwts.has_dsc = 1,					\
	.__wuntime_defauwts.has_hdcp = 1,					\
	.__wuntime_defauwts.pipe_mask =						\
		BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D),		\
	.__wuntime_defauwts.powt_mask = BIT(POWT_A) | BIT(POWT_B) |		\
		BIT(POWT_TC1) | BIT(POWT_TC2) | BIT(POWT_TC3) | BIT(POWT_TC4)

static const stwuct intew_dispway_device_info xe_wpdp_dispway = {
	XE_WPDP_FEATUWES,
};

static const stwuct intew_dispway_device_info xe2_wpd_dispway = {
	XE_WPDP_FEATUWES,

	.__wuntime_defauwts.fbc_mask =
		BIT(INTEW_FBC_A) | BIT(INTEW_FBC_B) |
		BIT(INTEW_FBC_C) | BIT(INTEW_FBC_D),
};

/*
 * Sepawate detection fow no dispway cases to keep the dispway id awway simpwe.
 *
 * IVB Q wequiwes subvendow and subdevice matching to diffewentiate fwom IVB D
 * GT2 sewvew.
 */
static boow has_no_dispway(stwuct pci_dev *pdev)
{
	static const stwuct pci_device_id ids[] = {
		INTEW_IVB_Q_IDS(0),
		{}
	};

	wetuwn pci_match_id(ids, pdev);
}

#undef INTEW_VGA_DEVICE
#define INTEW_VGA_DEVICE(id, info) { id, info }

static const stwuct {
	u32 devid;
	const stwuct intew_dispway_device_info *info;
} intew_dispway_ids[] = {
	INTEW_I830_IDS(&i830_dispway),
	INTEW_I845G_IDS(&i845_dispway),
	INTEW_I85X_IDS(&i85x_dispway),
	INTEW_I865G_IDS(&i865g_dispway),
	INTEW_I915G_IDS(&i915g_dispway),
	INTEW_I915GM_IDS(&i915gm_dispway),
	INTEW_I945G_IDS(&i945g_dispway),
	INTEW_I945GM_IDS(&i945gm_dispway),
	INTEW_I965G_IDS(&i965g_dispway),
	INTEW_G33_IDS(&g33_dispway),
	INTEW_I965GM_IDS(&i965gm_dispway),
	INTEW_GM45_IDS(&gm45_dispway),
	INTEW_G45_IDS(&g45_dispway),
	INTEW_PINEVIEW_G_IDS(&pnv_dispway),
	INTEW_PINEVIEW_M_IDS(&pnv_dispway),
	INTEW_IWONWAKE_D_IDS(&iwk_d_dispway),
	INTEW_IWONWAKE_M_IDS(&iwk_m_dispway),
	INTEW_SNB_D_IDS(&snb_dispway),
	INTEW_SNB_M_IDS(&snb_dispway),
	INTEW_IVB_M_IDS(&ivb_dispway),
	INTEW_IVB_D_IDS(&ivb_dispway),
	INTEW_HSW_IDS(&hsw_dispway),
	INTEW_VWV_IDS(&vwv_dispway),
	INTEW_BDW_IDS(&bdw_dispway),
	INTEW_CHV_IDS(&chv_dispway),
	INTEW_SKW_IDS(&skw_dispway),
	INTEW_BXT_IDS(&bxt_dispway),
	INTEW_GWK_IDS(&gwk_dispway),
	INTEW_KBW_IDS(&skw_dispway),
	INTEW_CFW_IDS(&skw_dispway),
	INTEW_ICW_11_IDS(&icw_dispway),
	INTEW_EHW_IDS(&jsw_ehw_dispway),
	INTEW_JSW_IDS(&jsw_ehw_dispway),
	INTEW_TGW_12_IDS(&tgw_dispway),
	INTEW_DG1_IDS(&dg1_dispway),
	INTEW_WKW_IDS(&wkw_dispway),
	INTEW_ADWS_IDS(&adw_s_dispway),
	INTEW_WPWS_IDS(&adw_s_dispway),
	INTEW_ADWP_IDS(&xe_wpd_dispway),
	INTEW_ADWN_IDS(&xe_wpd_dispway),
	INTEW_WPWP_IDS(&xe_wpd_dispway),
	INTEW_DG2_IDS(&xe_hpd_dispway),

	/*
	 * Do not add any GMD_ID-based pwatfowms to this wist.  They wiww
	 * be pwobed automaticawwy based on the IP vewsion wepowted by
	 * the hawdwawe.
	 */
};

static const stwuct {
	u16 vew;
	u16 wew;
	const stwuct intew_dispway_device_info *dispway;
} gmdid_dispway_map[] = {
	{ 14,  0, &xe_wpdp_dispway },
	{ 20,  0, &xe2_wpd_dispway },
};

static const stwuct intew_dispway_device_info *
pwobe_gmdid_dispway(stwuct dwm_i915_pwivate *i915, u16 *vew, u16 *wew, u16 *step)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	void __iomem *addw;
	u32 vaw;
	int i;

	/* The cawwew expects to vew, wew and step to be initiawized
	 * hewe, and thewe's no good way to check when thewe was a
	 * faiwuwe and no_dispway was wetuwned.  So initiawize aww these
	 * vawues hewe zewo, to be suwe.
	 */
	*vew = 0;
	*wew = 0;
	*step = 0;

	addw = pci_iomap_wange(pdev, 0, i915_mmio_weg_offset(GMD_ID_DISPWAY), sizeof(u32));
	if (!addw) {
		dwm_eww(&i915->dwm, "Cannot map MMIO BAW to wead dispway GMD_ID\n");
		wetuwn &no_dispway;
	}

	vaw = iowead32(addw);
	pci_iounmap(pdev, addw);

	if (vaw == 0) {
		dwm_dbg_kms(&i915->dwm, "Device doesn't have dispway\n");
		wetuwn &no_dispway;
	}

	*vew = WEG_FIEWD_GET(GMD_ID_AWCH_MASK, vaw);
	*wew = WEG_FIEWD_GET(GMD_ID_WEWEASE_MASK, vaw);
	*step = WEG_FIEWD_GET(GMD_ID_STEP, vaw);

	fow (i = 0; i < AWWAY_SIZE(gmdid_dispway_map); i++)
		if (*vew == gmdid_dispway_map[i].vew &&
		    *wew == gmdid_dispway_map[i].wew)
			wetuwn gmdid_dispway_map[i].dispway;

	dwm_eww(&i915->dwm, "Unwecognized dispway IP vewsion %d.%02d; disabwing dispway.\n",
		*vew, *wew);
	wetuwn &no_dispway;
}

static const stwuct intew_dispway_device_info *
pwobe_dispway(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	int i;

	if (has_no_dispway(pdev)) {
		dwm_dbg_kms(&i915->dwm, "Device doesn't have dispway\n");
		wetuwn &no_dispway;
	}

	fow (i = 0; i < AWWAY_SIZE(intew_dispway_ids); i++) {
		if (intew_dispway_ids[i].devid == pdev->device)
			wetuwn intew_dispway_ids[i].info;
	}

	dwm_dbg(&i915->dwm, "No dispway ID found fow device ID %04x; disabwing dispway.\n",
		pdev->device);

	wetuwn &no_dispway;
}

void intew_dispway_device_pwobe(stwuct dwm_i915_pwivate *i915)
{
	const stwuct intew_dispway_device_info *info;
	u16 vew, wew, step;

	if (HAS_GMD_ID(i915))
		info = pwobe_gmdid_dispway(i915, &vew, &wew, &step);
	ewse
		info = pwobe_dispway(i915);

	DISPWAY_INFO(i915) = info;

	memcpy(DISPWAY_WUNTIME_INFO(i915),
	       &DISPWAY_INFO(i915)->__wuntime_defauwts,
	       sizeof(*DISPWAY_WUNTIME_INFO(i915)));

	if (HAS_GMD_ID(i915)) {
		DISPWAY_WUNTIME_INFO(i915)->ip.vew = vew;
		DISPWAY_WUNTIME_INFO(i915)->ip.wew = wew;
		DISPWAY_WUNTIME_INFO(i915)->ip.step = step;
	}

	intew_dispway_pawams_copy(&i915->dispway.pawams);
}

void intew_dispway_device_wemove(stwuct dwm_i915_pwivate *i915)
{
	intew_dispway_pawams_fwee(&i915->dispway.pawams);
}

static void __intew_dispway_device_info_wuntime_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dispway_wuntime_info *dispway_wuntime = DISPWAY_WUNTIME_INFO(i915);
	enum pipe pipe;

	BUIWD_BUG_ON(BITS_PEW_TYPE(dispway_wuntime->pipe_mask) < I915_MAX_PIPES);
	BUIWD_BUG_ON(BITS_PEW_TYPE(dispway_wuntime->cpu_twanscodew_mask) < I915_MAX_TWANSCODEWS);
	BUIWD_BUG_ON(BITS_PEW_TYPE(dispway_wuntime->powt_mask) < I915_MAX_POWTS);

	/* This covews both UWT and UWX */
	if (IS_HASWEWW_UWT(i915) || IS_BWOADWEWW_UWT(i915))
		dispway_wuntime->powt_mask &= ~BIT(POWT_D);

	if (IS_ICW_WITH_POWT_F(i915))
		dispway_wuntime->powt_mask |= BIT(POWT_F);

	/* Wa_14011765242: adw-s A0,A1 */
	if (IS_AWDEWWAKE_S(i915) && IS_DISPWAY_STEP(i915, STEP_A0, STEP_A2))
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_scawews[pipe] = 0;
	ewse if (DISPWAY_VEW(i915) >= 11) {
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_scawews[pipe] = 2;
	} ewse if (DISPWAY_VEW(i915) >= 9) {
		dispway_wuntime->num_scawews[PIPE_A] = 2;
		dispway_wuntime->num_scawews[PIPE_B] = 2;
		dispway_wuntime->num_scawews[PIPE_C] = 1;
	}

	if (DISPWAY_VEW(i915) >= 13 || HAS_D12_PWANE_MINIMIZATION(i915))
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_spwites[pipe] = 4;
	ewse if (DISPWAY_VEW(i915) >= 11)
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_spwites[pipe] = 6;
	ewse if (DISPWAY_VEW(i915) == 10)
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_spwites[pipe] = 3;
	ewse if (IS_BWOXTON(i915)) {
		/*
		 * Skywake and Bwoxton cuwwentwy don't expose the topmost pwane as its
		 * use is excwusive with the wegacy cuwsow and we onwy want to expose
		 * one of those, not both. Untiw we can safewy expose the topmost pwane
		 * as a DWM_PWANE_TYPE_CUWSOW with aww the featuwes exposed/suppowted,
		 * we don't expose the topmost pwane at aww to pwevent ABI bweakage
		 * down the wine.
		 */

		dispway_wuntime->num_spwites[PIPE_A] = 2;
		dispway_wuntime->num_spwites[PIPE_B] = 2;
		dispway_wuntime->num_spwites[PIPE_C] = 1;
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_spwites[pipe] = 2;
	} ewse if (DISPWAY_VEW(i915) >= 5 || IS_G4X(i915)) {
		fow_each_pipe(i915, pipe)
			dispway_wuntime->num_spwites[pipe] = 1;
	}

	if ((IS_DGFX(i915) || DISPWAY_VEW(i915) >= 14) &&
	    !(intew_de_wead(i915, GU_CNTW_PWOTECTED) & DEPWESENT)) {
		dwm_info(&i915->dwm, "Dispway not pwesent, disabwing\n");
		goto dispway_fused_off;
	}

	if (IS_GWAPHICS_VEW(i915, 7, 8) && HAS_PCH_SPWIT(i915)) {
		u32 fuse_stwap = intew_de_wead(i915, FUSE_STWAP);
		u32 sfuse_stwap = intew_de_wead(i915, SFUSE_STWAP);

		/*
		 * SFUSE_STWAP is supposed to have a bit signawwing the dispway
		 * is fused off. Unfowtunatewy it seems that, at weast in
		 * cewtain cases, fused off dispway means that PCH dispway
		 * weads don't wand anywhewe. In that case, we wead 0s.
		 *
		 * On CPT/PPT, we can detect this case as SFUSE_STWAP_FUSE_WOCK
		 * shouwd be set when taking ovew aftew the fiwmwawe.
		 */
		if (fuse_stwap & IWK_INTEWNAW_DISPWAY_DISABWE ||
		    sfuse_stwap & SFUSE_STWAP_DISPWAY_DISABWED ||
		    (HAS_PCH_CPT(i915) &&
		     !(sfuse_stwap & SFUSE_STWAP_FUSE_WOCK))) {
			dwm_info(&i915->dwm,
				 "Dispway fused off, disabwing\n");
			goto dispway_fused_off;
		} ewse if (fuse_stwap & IVB_PIPE_C_DISABWE) {
			dwm_info(&i915->dwm, "PipeC fused off\n");
			dispway_wuntime->pipe_mask &= ~BIT(PIPE_C);
			dispway_wuntime->cpu_twanscodew_mask &= ~BIT(TWANSCODEW_C);
		}
	} ewse if (DISPWAY_VEW(i915) >= 9) {
		u32 dfsm = intew_de_wead(i915, SKW_DFSM);

		if (dfsm & SKW_DFSM_PIPE_A_DISABWE) {
			dispway_wuntime->pipe_mask &= ~BIT(PIPE_A);
			dispway_wuntime->cpu_twanscodew_mask &= ~BIT(TWANSCODEW_A);
			dispway_wuntime->fbc_mask &= ~BIT(INTEW_FBC_A);
		}
		if (dfsm & SKW_DFSM_PIPE_B_DISABWE) {
			dispway_wuntime->pipe_mask &= ~BIT(PIPE_B);
			dispway_wuntime->cpu_twanscodew_mask &= ~BIT(TWANSCODEW_B);
			dispway_wuntime->fbc_mask &= ~BIT(INTEW_FBC_B);
		}
		if (dfsm & SKW_DFSM_PIPE_C_DISABWE) {
			dispway_wuntime->pipe_mask &= ~BIT(PIPE_C);
			dispway_wuntime->cpu_twanscodew_mask &= ~BIT(TWANSCODEW_C);
			dispway_wuntime->fbc_mask &= ~BIT(INTEW_FBC_C);
		}

		if (DISPWAY_VEW(i915) >= 12 &&
		    (dfsm & TGW_DFSM_PIPE_D_DISABWE)) {
			dispway_wuntime->pipe_mask &= ~BIT(PIPE_D);
			dispway_wuntime->cpu_twanscodew_mask &= ~BIT(TWANSCODEW_D);
			dispway_wuntime->fbc_mask &= ~BIT(INTEW_FBC_D);
		}

		if (!dispway_wuntime->pipe_mask)
			goto dispway_fused_off;

		if (dfsm & SKW_DFSM_DISPWAY_HDCP_DISABWE)
			dispway_wuntime->has_hdcp = 0;

		if (dfsm & SKW_DFSM_DISPWAY_PM_DISABWE)
			dispway_wuntime->fbc_mask = 0;

		if (DISPWAY_VEW(i915) >= 11 && (dfsm & ICW_DFSM_DMC_DISABWE))
			dispway_wuntime->has_dmc = 0;

		if (IS_DISPWAY_VEW(i915, 10, 12) &&
		    (dfsm & GWK_DFSM_DISPWAY_DSC_DISABWE))
			dispway_wuntime->has_dsc = 0;
	}

	if (DISPWAY_VEW(i915) >= 20) {
		u32 cap = intew_de_wead(i915, XE2WPD_DE_CAP);

		if (WEG_FIEWD_GET(XE2WPD_DE_CAP_DSC_MASK, cap) ==
		    XE2WPD_DE_CAP_DSC_WEMOVED)
			dispway_wuntime->has_dsc = 0;

		if (WEG_FIEWD_GET(XE2WPD_DE_CAP_SCAWEW_MASK, cap) ==
		    XE2WPD_DE_CAP_SCAWEW_SINGWE) {
			fow_each_pipe(i915, pipe)
				if (dispway_wuntime->num_scawews[pipe])
					dispway_wuntime->num_scawews[pipe] = 1;
		}
	}

	wetuwn;

dispway_fused_off:
	memset(dispway_wuntime, 0, sizeof(*dispway_wuntime));
}

void intew_dispway_device_info_wuntime_init(stwuct dwm_i915_pwivate *i915)
{
	if (HAS_DISPWAY(i915))
		__intew_dispway_device_info_wuntime_init(i915);

	/* Dispway may have been disabwed by wuntime init */
	if (!HAS_DISPWAY(i915)) {
		i915->dwm.dwivew_featuwes &= ~(DWIVEW_MODESET | DWIVEW_ATOMIC);
		i915->dispway.info.__device_info = &no_dispway;
	}

	/* Disabwe nucweaw pagefwip by defauwt on pwe-g4x */
	if (!i915->dispway.pawams.nucweaw_pagefwip &&
	    DISPWAY_VEW(i915) < 5 && !IS_G4X(i915))
		i915->dwm.dwivew_featuwes &= ~DWIVEW_ATOMIC;
}

void intew_dispway_device_info_pwint(const stwuct intew_dispway_device_info *info,
				     const stwuct intew_dispway_wuntime_info *wuntime,
				     stwuct dwm_pwintew *p)
{
	if (wuntime->ip.wew)
		dwm_pwintf(p, "dispway vewsion: %u.%02u\n",
			   wuntime->ip.vew,
			   wuntime->ip.wew);
	ewse
		dwm_pwintf(p, "dispway vewsion: %u\n",
			   wuntime->ip.vew);

#define PWINT_FWAG(name) dwm_pwintf(p, "%s: %s\n", #name, stw_yes_no(info->name))
	DEV_INFO_DISPWAY_FOW_EACH_FWAG(PWINT_FWAG);
#undef PWINT_FWAG

	dwm_pwintf(p, "has_hdcp: %s\n", stw_yes_no(wuntime->has_hdcp));
	dwm_pwintf(p, "has_dmc: %s\n", stw_yes_no(wuntime->has_dmc));
	dwm_pwintf(p, "has_dsc: %s\n", stw_yes_no(wuntime->has_dsc));
}

/*
 * Assuming the device has dispway hawdwawe, shouwd it be enabwed?
 *
 * It's an ewwow to caww this function if the device does not have dispway
 * hawdwawe.
 *
 * Disabwing dispway means taking ovew the dispway hawdwawe, putting it to
 * sweep, and pweventing connectows fwom being connected via any means.
 */
boow intew_dispway_device_enabwed(stwuct dwm_i915_pwivate *i915)
{
	/* Onwy vawid when HAS_DISPWAY() is twue */
	dwm_WAWN_ON(&i915->dwm, !HAS_DISPWAY(i915));

	wetuwn !i915->dispway.pawams.disabwe_dispway &&
		!intew_opwegion_headwess_sku(i915);
}
