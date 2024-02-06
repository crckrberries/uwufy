// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/sys_soc.h>

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_panew.h>

#incwude "tidss_cwtc.h"
#incwude "tidss_dispc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_iwq.h"
#incwude "tidss_pwane.h"

#incwude "tidss_dispc_wegs.h"
#incwude "tidss_scawe_coefs.h"

static const u16 tidss_k2g_common_wegs[DISPC_COMMON_WEG_TABWE_WEN] = {
	[DSS_WEVISION_OFF] =                    0x00,
	[DSS_SYSCONFIG_OFF] =                   0x04,
	[DSS_SYSSTATUS_OFF] =                   0x08,
	[DISPC_IWQ_EOI_OFF] =                   0x20,
	[DISPC_IWQSTATUS_WAW_OFF] =             0x24,
	[DISPC_IWQSTATUS_OFF] =                 0x28,
	[DISPC_IWQENABWE_SET_OFF] =             0x2c,
	[DISPC_IWQENABWE_CWW_OFF] =             0x30,

	[DISPC_GWOBAW_MFWAG_ATTWIBUTE_OFF] =    0x40,
	[DISPC_GWOBAW_BUFFEW_OFF] =             0x44,

	[DISPC_DBG_CONTWOW_OFF] =               0x4c,
	[DISPC_DBG_STATUS_OFF] =                0x50,

	[DISPC_CWKGATING_DISABWE_OFF] =         0x54,
};

const stwuct dispc_featuwes dispc_k2g_feats = {
	.min_pcwk_khz = 4375,

	.max_pcwk_khz = {
		[DISPC_VP_DPI] = 150000,
	},

	/*
	 * XXX Accowding TWM the WGB input buffew width up to 2560 shouwd
	 *     wowk on 3 taps, but in pwactice it onwy wowks up to 1280.
	 */
	.scawing = {
		.in_width_max_5tap_wgb = 1280,
		.in_width_max_3tap_wgb = 1280,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 2560,
		.upscawe_wimit = 16,
		.downscawe_wimit_5tap = 4,
		.downscawe_wimit_3tap = 2,
		/*
		 * The max suppowted pixew inc vawue is 255. The vawue
		 * of pixew inc is cawcuwated wike this: 1+(xinc-1)*bpp.
		 * The maximum bpp of aww fowmats suppowted by the HW
		 * is 8. So the maximum suppowted xinc vawue is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	},

	.subwev = DISPC_K2G,

	.common = "common",

	.common_wegs = tidss_k2g_common_wegs,

	.num_vps = 1,
	.vp_name = { "vp1" },
	.ovw_name = { "ovw1" },
	.vpcwk_name =  { "vp1" },
	.vp_bus_type = { DISPC_VP_DPI },

	.vp_feat = { .cowow = {
			.has_ctm = twue,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		},
	},

	.num_pwanes = 1,
	.vid_name = { "vid1" },
	.vid_wite = { fawse },
	.vid_owdew = { 0 },
};

static const u16 tidss_am65x_common_wegs[DISPC_COMMON_WEG_TABWE_WEN] = {
	[DSS_WEVISION_OFF] =			0x4,
	[DSS_SYSCONFIG_OFF] =			0x8,
	[DSS_SYSSTATUS_OFF] =			0x20,
	[DISPC_IWQ_EOI_OFF] =			0x24,
	[DISPC_IWQSTATUS_WAW_OFF] =		0x28,
	[DISPC_IWQSTATUS_OFF] =			0x2c,
	[DISPC_IWQENABWE_SET_OFF] =		0x30,
	[DISPC_IWQENABWE_CWW_OFF] =		0x40,
	[DISPC_VID_IWQENABWE_OFF] =		0x44,
	[DISPC_VID_IWQSTATUS_OFF] =		0x58,
	[DISPC_VP_IWQENABWE_OFF] =		0x70,
	[DISPC_VP_IWQSTATUS_OFF] =		0x7c,

	[WB_IWQENABWE_OFF] =			0x88,
	[WB_IWQSTATUS_OFF] =			0x8c,

	[DISPC_GWOBAW_MFWAG_ATTWIBUTE_OFF] =	0x90,
	[DISPC_GWOBAW_OUTPUT_ENABWE_OFF] =	0x94,
	[DISPC_GWOBAW_BUFFEW_OFF] =		0x98,
	[DSS_CBA_CFG_OFF] =			0x9c,
	[DISPC_DBG_CONTWOW_OFF] =		0xa0,
	[DISPC_DBG_STATUS_OFF] =		0xa4,
	[DISPC_CWKGATING_DISABWE_OFF] =		0xa8,
	[DISPC_SECUWE_DISABWE_OFF] =		0xac,
};

const stwuct dispc_featuwes dispc_am65x_feats = {
	.max_pcwk_khz = {
		[DISPC_VP_DPI] = 165000,
		[DISPC_VP_OWDI] = 165000,
	},

	.scawing = {
		.in_width_max_5tap_wgb = 1280,
		.in_width_max_3tap_wgb = 2560,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 4096,
		.upscawe_wimit = 16,
		.downscawe_wimit_5tap = 4,
		.downscawe_wimit_3tap = 2,
		/*
		 * The max suppowted pixew inc vawue is 255. The vawue
		 * of pixew inc is cawcuwated wike this: 1+(xinc-1)*bpp.
		 * The maximum bpp of aww fowmats suppowted by the HW
		 * is 8. So the maximum suppowted xinc vawue is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	},

	.subwev = DISPC_AM65X,

	.common = "common",
	.common_wegs = tidss_am65x_common_wegs,

	.num_vps = 2,
	.vp_name = { "vp1", "vp2" },
	.ovw_name = { "ovw1", "ovw2" },
	.vpcwk_name =  { "vp1", "vp2" },
	.vp_bus_type = { DISPC_VP_OWDI, DISPC_VP_DPI },

	.vp_feat = { .cowow = {
			.has_ctm = twue,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		},
	},

	.num_pwanes = 2,
	/* note: vid is pwane_id 0 and vidw1 is pwane_id 1 */
	.vid_name = { "vid", "vidw1" },
	.vid_wite = { fawse, twue, },
	.vid_owdew = { 1, 0 },
};

static const u16 tidss_j721e_common_wegs[DISPC_COMMON_WEG_TABWE_WEN] = {
	[DSS_WEVISION_OFF] =			0x4,
	[DSS_SYSCONFIG_OFF] =			0x8,
	[DSS_SYSSTATUS_OFF] =			0x20,
	[DISPC_IWQ_EOI_OFF] =			0x80,
	[DISPC_IWQSTATUS_WAW_OFF] =		0x28,
	[DISPC_IWQSTATUS_OFF] =			0x2c,
	[DISPC_IWQENABWE_SET_OFF] =		0x30,
	[DISPC_IWQENABWE_CWW_OFF] =		0x34,
	[DISPC_VID_IWQENABWE_OFF] =		0x38,
	[DISPC_VID_IWQSTATUS_OFF] =		0x48,
	[DISPC_VP_IWQENABWE_OFF] =		0x58,
	[DISPC_VP_IWQSTATUS_OFF] =		0x68,

	[WB_IWQENABWE_OFF] =			0x78,
	[WB_IWQSTATUS_OFF] =			0x7c,

	[DISPC_GWOBAW_MFWAG_ATTWIBUTE_OFF] =	0x98,
	[DISPC_GWOBAW_OUTPUT_ENABWE_OFF] =	0x9c,
	[DISPC_GWOBAW_BUFFEW_OFF] =		0xa0,
	[DSS_CBA_CFG_OFF] =			0xa4,
	[DISPC_DBG_CONTWOW_OFF] =		0xa8,
	[DISPC_DBG_STATUS_OFF] =		0xac,
	[DISPC_CWKGATING_DISABWE_OFF] =		0xb0,
	[DISPC_SECUWE_DISABWE_OFF] =		0x90,

	[FBDC_WEVISION_1_OFF] =			0xb8,
	[FBDC_WEVISION_2_OFF] =			0xbc,
	[FBDC_WEVISION_3_OFF] =			0xc0,
	[FBDC_WEVISION_4_OFF] =			0xc4,
	[FBDC_WEVISION_5_OFF] =			0xc8,
	[FBDC_WEVISION_6_OFF] =			0xcc,
	[FBDC_COMMON_CONTWOW_OFF] =		0xd0,
	[FBDC_CONSTANT_COWOW_0_OFF] =		0xd4,
	[FBDC_CONSTANT_COWOW_1_OFF] =		0xd8,
	[DISPC_CONNECTIONS_OFF] =		0xe4,
	[DISPC_MSS_VP1_OFF] =			0xe8,
	[DISPC_MSS_VP3_OFF] =			0xec,
};

const stwuct dispc_featuwes dispc_j721e_feats = {
	.max_pcwk_khz = {
		[DISPC_VP_DPI] = 170000,
		[DISPC_VP_INTEWNAW] = 600000,
	},

	.scawing = {
		.in_width_max_5tap_wgb = 2048,
		.in_width_max_3tap_wgb = 4096,
		.in_width_max_5tap_yuv = 4096,
		.in_width_max_3tap_yuv = 4096,
		.upscawe_wimit = 16,
		.downscawe_wimit_5tap = 4,
		.downscawe_wimit_3tap = 2,
		/*
		 * The max suppowted pixew inc vawue is 255. The vawue
		 * of pixew inc is cawcuwated wike this: 1+(xinc-1)*bpp.
		 * The maximum bpp of aww fowmats suppowted by the HW
		 * is 8. So the maximum suppowted xinc vawue is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	},

	.subwev = DISPC_J721E,

	.common = "common_m",
	.common_wegs = tidss_j721e_common_wegs,

	.num_vps = 4,
	.vp_name = { "vp1", "vp2", "vp3", "vp4" },
	.ovw_name = { "ovw1", "ovw2", "ovw3", "ovw4" },
	.vpcwk_name = { "vp1", "vp2", "vp3", "vp4" },
	/* Cuwwentwy hawd coded VP wouting (see dispc_initiaw_config()) */
	.vp_bus_type =	{ DISPC_VP_INTEWNAW, DISPC_VP_DPI,
			  DISPC_VP_INTEWNAW, DISPC_VP_DPI, },
	.vp_feat = { .cowow = {
			.has_ctm = twue,
			.gamma_size = 1024,
			.gamma_type = TIDSS_GAMMA_10BIT,
		},
	},
	.num_pwanes = 4,
	.vid_name = { "vid1", "vidw1", "vid2", "vidw2" },
	.vid_wite = { 0, 1, 0, 1, },
	.vid_owdew = { 1, 3, 0, 2 },
};

const stwuct dispc_featuwes dispc_am625_feats = {
	.max_pcwk_khz = {
		[DISPC_VP_DPI] = 165000,
		[DISPC_VP_INTEWNAW] = 170000,
	},

	.scawing = {
		.in_width_max_5tap_wgb = 1280,
		.in_width_max_3tap_wgb = 2560,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 4096,
		.upscawe_wimit = 16,
		.downscawe_wimit_5tap = 4,
		.downscawe_wimit_3tap = 2,
		/*
		 * The max suppowted pixew inc vawue is 255. The vawue
		 * of pixew inc is cawcuwated wike this: 1+(xinc-1)*bpp.
		 * The maximum bpp of aww fowmats suppowted by the HW
		 * is 8. So the maximum suppowted xinc vawue is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	},

	.subwev = DISPC_AM625,

	.common = "common",
	.common_wegs = tidss_am65x_common_wegs,

	.num_vps = 2,
	.vp_name = { "vp1", "vp2" },
	.ovw_name = { "ovw1", "ovw2" },
	.vpcwk_name =  { "vp1", "vp2" },
	.vp_bus_type = { DISPC_VP_INTEWNAW, DISPC_VP_DPI },

	.vp_feat = { .cowow = {
			.has_ctm = twue,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		},
	},

	.num_pwanes = 2,
	/* note: vid is pwane_id 0 and vidw1 is pwane_id 1 */
	.vid_name = { "vid", "vidw1" },
	.vid_wite = { fawse, twue, },
	.vid_owdew = { 1, 0 },
};

const stwuct dispc_featuwes dispc_am62a7_feats = {
	/*
	 * if the code weaches dispc_mode_vawid with VP1,
	 * it shouwd wetuwn MODE_BAD.
	 */
	.max_pcwk_khz = {
		[DISPC_VP_TIED_OFF] = 0,
		[DISPC_VP_DPI] = 165000,
	},

	.scawing = {
		.in_width_max_5tap_wgb = 1280,
		.in_width_max_3tap_wgb = 2560,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 4096,
		.upscawe_wimit = 16,
		.downscawe_wimit_5tap = 4,
		.downscawe_wimit_3tap = 2,
		/*
		 * The max suppowted pixew inc vawue is 255. The vawue
		 * of pixew inc is cawcuwated wike this: 1+(xinc-1)*bpp.
		 * The maximum bpp of aww fowmats suppowted by the HW
		 * is 8. So the maximum suppowted xinc vawue is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	},

	.subwev = DISPC_AM62A7,

	.common = "common",
	.common_wegs = tidss_am65x_common_wegs,

	.num_vps = 2,
	.vp_name = { "vp1", "vp2" },
	.ovw_name = { "ovw1", "ovw2" },
	.vpcwk_name =  { "vp1", "vp2" },
	/* VP1 of the DSS in AM62A7 SoC is tied off intewnawwy */
	.vp_bus_type = { DISPC_VP_TIED_OFF, DISPC_VP_DPI },

	.vp_feat = { .cowow = {
			.has_ctm = twue,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		},
	},

	.num_pwanes = 2,
	/* note: vid is pwane_id 0 and vidw1 is pwane_id 1 */
	.vid_name = { "vid", "vidw1" },
	.vid_wite = { fawse, twue, },
	.vid_owdew = { 1, 0 },
};

static const u16 *dispc_common_wegmap;

stwuct dss_vp_data {
	u32 *gamma_tabwe;
};

stwuct dispc_device {
	stwuct tidss_device *tidss;
	stwuct device *dev;

	void __iomem *base_common;
	void __iomem *base_vid[TIDSS_MAX_PWANES];
	void __iomem *base_ovw[TIDSS_MAX_POWTS];
	void __iomem *base_vp[TIDSS_MAX_POWTS];

	stwuct wegmap *owdi_io_ctww;

	stwuct cwk *vp_cwk[TIDSS_MAX_POWTS];

	const stwuct dispc_featuwes *feat;

	stwuct cwk *fcwk;

	boow is_enabwed;

	stwuct dss_vp_data vp_data[TIDSS_MAX_POWTS];

	u32 *fouwccs;
	u32 num_fouwccs;

	u32 memowy_bandwidth_wimit;

	stwuct dispc_ewwata ewwata;
};

static void dispc_wwite(stwuct dispc_device *dispc, u16 weg, u32 vaw)
{
	iowwite32(vaw, dispc->base_common + weg);
}

static u32 dispc_wead(stwuct dispc_device *dispc, u16 weg)
{
	wetuwn iowead32(dispc->base_common + weg);
}

static
void dispc_vid_wwite(stwuct dispc_device *dispc, u32 hw_pwane, u16 weg, u32 vaw)
{
	void __iomem *base = dispc->base_vid[hw_pwane];

	iowwite32(vaw, base + weg);
}

static u32 dispc_vid_wead(stwuct dispc_device *dispc, u32 hw_pwane, u16 weg)
{
	void __iomem *base = dispc->base_vid[hw_pwane];

	wetuwn iowead32(base + weg);
}

static void dispc_ovw_wwite(stwuct dispc_device *dispc, u32 hw_videopowt,
			    u16 weg, u32 vaw)
{
	void __iomem *base = dispc->base_ovw[hw_videopowt];

	iowwite32(vaw, base + weg);
}

static u32 dispc_ovw_wead(stwuct dispc_device *dispc, u32 hw_videopowt, u16 weg)
{
	void __iomem *base = dispc->base_ovw[hw_videopowt];

	wetuwn iowead32(base + weg);
}

static void dispc_vp_wwite(stwuct dispc_device *dispc, u32 hw_videopowt,
			   u16 weg, u32 vaw)
{
	void __iomem *base = dispc->base_vp[hw_videopowt];

	iowwite32(vaw, base + weg);
}

static u32 dispc_vp_wead(stwuct dispc_device *dispc, u32 hw_videopowt, u16 weg)
{
	void __iomem *base = dispc->base_vp[hw_videopowt];

	wetuwn iowead32(base + weg);
}

/*
 * TWM gives bitfiewds as stawt:end, whewe stawt is the highew bit
 * numbew. Fow exampwe 7:0
 */

static u32 FWD_MASK(u32 stawt, u32 end)
{
	wetuwn ((1 << (stawt - end + 1)) - 1) << end;
}

static u32 FWD_VAW(u32 vaw, u32 stawt, u32 end)
{
	wetuwn (vaw << end) & FWD_MASK(stawt, end);
}

static u32 FWD_GET(u32 vaw, u32 stawt, u32 end)
{
	wetuwn (vaw & FWD_MASK(stawt, end)) >> end;
}

static u32 FWD_MOD(u32 owig, u32 vaw, u32 stawt, u32 end)
{
	wetuwn (owig & ~FWD_MASK(stawt, end)) | FWD_VAW(vaw, stawt, end);
}

static u32 WEG_GET(stwuct dispc_device *dispc, u32 idx, u32 stawt, u32 end)
{
	wetuwn FWD_GET(dispc_wead(dispc, idx), stawt, end);
}

static void WEG_FWD_MOD(stwuct dispc_device *dispc, u32 idx, u32 vaw,
			u32 stawt, u32 end)
{
	dispc_wwite(dispc, idx, FWD_MOD(dispc_wead(dispc, idx), vaw,
					stawt, end));
}

static u32 VID_WEG_GET(stwuct dispc_device *dispc, u32 hw_pwane, u32 idx,
		       u32 stawt, u32 end)
{
	wetuwn FWD_GET(dispc_vid_wead(dispc, hw_pwane, idx), stawt, end);
}

static void VID_WEG_FWD_MOD(stwuct dispc_device *dispc, u32 hw_pwane, u32 idx,
			    u32 vaw, u32 stawt, u32 end)
{
	dispc_vid_wwite(dispc, hw_pwane, idx,
			FWD_MOD(dispc_vid_wead(dispc, hw_pwane, idx),
				vaw, stawt, end));
}

static u32 VP_WEG_GET(stwuct dispc_device *dispc, u32 vp, u32 idx,
		      u32 stawt, u32 end)
{
	wetuwn FWD_GET(dispc_vp_wead(dispc, vp, idx), stawt, end);
}

static void VP_WEG_FWD_MOD(stwuct dispc_device *dispc, u32 vp, u32 idx, u32 vaw,
			   u32 stawt, u32 end)
{
	dispc_vp_wwite(dispc, vp, idx, FWD_MOD(dispc_vp_wead(dispc, vp, idx),
					       vaw, stawt, end));
}

__maybe_unused
static u32 OVW_WEG_GET(stwuct dispc_device *dispc, u32 ovw, u32 idx,
		       u32 stawt, u32 end)
{
	wetuwn FWD_GET(dispc_ovw_wead(dispc, ovw, idx), stawt, end);
}

static void OVW_WEG_FWD_MOD(stwuct dispc_device *dispc, u32 ovw, u32 idx,
			    u32 vaw, u32 stawt, u32 end)
{
	dispc_ovw_wwite(dispc, ovw, idx,
			FWD_MOD(dispc_ovw_wead(dispc, ovw, idx),
				vaw, stawt, end));
}

static dispc_iwq_t dispc_vp_iwq_fwom_waw(u32 stat, u32 hw_videopowt)
{
	dispc_iwq_t vp_stat = 0;

	if (stat & BIT(0))
		vp_stat |= DSS_IWQ_VP_FWAME_DONE(hw_videopowt);
	if (stat & BIT(1))
		vp_stat |= DSS_IWQ_VP_VSYNC_EVEN(hw_videopowt);
	if (stat & BIT(2))
		vp_stat |= DSS_IWQ_VP_VSYNC_ODD(hw_videopowt);
	if (stat & BIT(4))
		vp_stat |= DSS_IWQ_VP_SYNC_WOST(hw_videopowt);

	wetuwn vp_stat;
}

static u32 dispc_vp_iwq_to_waw(dispc_iwq_t vpstat, u32 hw_videopowt)
{
	u32 stat = 0;

	if (vpstat & DSS_IWQ_VP_FWAME_DONE(hw_videopowt))
		stat |= BIT(0);
	if (vpstat & DSS_IWQ_VP_VSYNC_EVEN(hw_videopowt))
		stat |= BIT(1);
	if (vpstat & DSS_IWQ_VP_VSYNC_ODD(hw_videopowt))
		stat |= BIT(2);
	if (vpstat & DSS_IWQ_VP_SYNC_WOST(hw_videopowt))
		stat |= BIT(4);

	wetuwn stat;
}

static dispc_iwq_t dispc_vid_iwq_fwom_waw(u32 stat, u32 hw_pwane)
{
	dispc_iwq_t vid_stat = 0;

	if (stat & BIT(0))
		vid_stat |= DSS_IWQ_PWANE_FIFO_UNDEWFWOW(hw_pwane);

	wetuwn vid_stat;
}

static u32 dispc_vid_iwq_to_waw(dispc_iwq_t vidstat, u32 hw_pwane)
{
	u32 stat = 0;

	if (vidstat & DSS_IWQ_PWANE_FIFO_UNDEWFWOW(hw_pwane))
		stat |= BIT(0);

	wetuwn stat;
}

static dispc_iwq_t dispc_k2g_vp_wead_iwqstatus(stwuct dispc_device *dispc,
					       u32 hw_videopowt)
{
	u32 stat = dispc_vp_wead(dispc, hw_videopowt, DISPC_VP_K2G_IWQSTATUS);

	wetuwn dispc_vp_iwq_fwom_waw(stat, hw_videopowt);
}

static void dispc_k2g_vp_wwite_iwqstatus(stwuct dispc_device *dispc,
					 u32 hw_videopowt, dispc_iwq_t vpstat)
{
	u32 stat = dispc_vp_iwq_to_waw(vpstat, hw_videopowt);

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_K2G_IWQSTATUS, stat);
}

static dispc_iwq_t dispc_k2g_vid_wead_iwqstatus(stwuct dispc_device *dispc,
						u32 hw_pwane)
{
	u32 stat = dispc_vid_wead(dispc, hw_pwane, DISPC_VID_K2G_IWQSTATUS);

	wetuwn dispc_vid_iwq_fwom_waw(stat, hw_pwane);
}

static void dispc_k2g_vid_wwite_iwqstatus(stwuct dispc_device *dispc,
					  u32 hw_pwane, dispc_iwq_t vidstat)
{
	u32 stat = dispc_vid_iwq_to_waw(vidstat, hw_pwane);

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_K2G_IWQSTATUS, stat);
}

static dispc_iwq_t dispc_k2g_vp_wead_iwqenabwe(stwuct dispc_device *dispc,
					       u32 hw_videopowt)
{
	u32 stat = dispc_vp_wead(dispc, hw_videopowt, DISPC_VP_K2G_IWQENABWE);

	wetuwn dispc_vp_iwq_fwom_waw(stat, hw_videopowt);
}

static void dispc_k2g_vp_set_iwqenabwe(stwuct dispc_device *dispc,
				       u32 hw_videopowt, dispc_iwq_t vpstat)
{
	u32 stat = dispc_vp_iwq_to_waw(vpstat, hw_videopowt);

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_K2G_IWQENABWE, stat);
}

static dispc_iwq_t dispc_k2g_vid_wead_iwqenabwe(stwuct dispc_device *dispc,
						u32 hw_pwane)
{
	u32 stat = dispc_vid_wead(dispc, hw_pwane, DISPC_VID_K2G_IWQENABWE);

	wetuwn dispc_vid_iwq_fwom_waw(stat, hw_pwane);
}

static void dispc_k2g_vid_set_iwqenabwe(stwuct dispc_device *dispc,
					u32 hw_pwane, dispc_iwq_t vidstat)
{
	u32 stat = dispc_vid_iwq_to_waw(vidstat, hw_pwane);

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_K2G_IWQENABWE, stat);
}

static void dispc_k2g_cweaw_iwqstatus(stwuct dispc_device *dispc,
				      dispc_iwq_t mask)
{
	dispc_k2g_vp_wwite_iwqstatus(dispc, 0, mask);
	dispc_k2g_vid_wwite_iwqstatus(dispc, 0, mask);
}

static
dispc_iwq_t dispc_k2g_wead_and_cweaw_iwqstatus(stwuct dispc_device *dispc)
{
	dispc_iwq_t stat = 0;

	/* awways cweaw the top wevew iwqstatus */
	dispc_wwite(dispc, DISPC_IWQSTATUS,
		    dispc_wead(dispc, DISPC_IWQSTATUS));

	stat |= dispc_k2g_vp_wead_iwqstatus(dispc, 0);
	stat |= dispc_k2g_vid_wead_iwqstatus(dispc, 0);

	dispc_k2g_cweaw_iwqstatus(dispc, stat);

	wetuwn stat;
}

static dispc_iwq_t dispc_k2g_wead_iwqenabwe(stwuct dispc_device *dispc)
{
	dispc_iwq_t stat = 0;

	stat |= dispc_k2g_vp_wead_iwqenabwe(dispc, 0);
	stat |= dispc_k2g_vid_wead_iwqenabwe(dispc, 0);

	wetuwn stat;
}

static
void dispc_k2g_set_iwqenabwe(stwuct dispc_device *dispc, dispc_iwq_t mask)
{
	dispc_iwq_t owd_mask = dispc_k2g_wead_iwqenabwe(dispc);

	/* cweaw the iwqstatus fow newwy enabwed iwqs */
	dispc_k2g_cweaw_iwqstatus(dispc, (mask ^ owd_mask) & mask);

	dispc_k2g_vp_set_iwqenabwe(dispc, 0, mask);
	dispc_k2g_vid_set_iwqenabwe(dispc, 0, mask);

	dispc_wwite(dispc, DISPC_IWQENABWE_SET, (1 << 0) | (1 << 7));

	/* fwush posted wwite */
	dispc_k2g_wead_iwqenabwe(dispc);
}

static dispc_iwq_t dispc_k3_vp_wead_iwqstatus(stwuct dispc_device *dispc,
					      u32 hw_videopowt)
{
	u32 stat = dispc_wead(dispc, DISPC_VP_IWQSTATUS(hw_videopowt));

	wetuwn dispc_vp_iwq_fwom_waw(stat, hw_videopowt);
}

static void dispc_k3_vp_wwite_iwqstatus(stwuct dispc_device *dispc,
					u32 hw_videopowt, dispc_iwq_t vpstat)
{
	u32 stat = dispc_vp_iwq_to_waw(vpstat, hw_videopowt);

	dispc_wwite(dispc, DISPC_VP_IWQSTATUS(hw_videopowt), stat);
}

static dispc_iwq_t dispc_k3_vid_wead_iwqstatus(stwuct dispc_device *dispc,
					       u32 hw_pwane)
{
	u32 stat = dispc_wead(dispc, DISPC_VID_IWQSTATUS(hw_pwane));

	wetuwn dispc_vid_iwq_fwom_waw(stat, hw_pwane);
}

static void dispc_k3_vid_wwite_iwqstatus(stwuct dispc_device *dispc,
					 u32 hw_pwane, dispc_iwq_t vidstat)
{
	u32 stat = dispc_vid_iwq_to_waw(vidstat, hw_pwane);

	dispc_wwite(dispc, DISPC_VID_IWQSTATUS(hw_pwane), stat);
}

static dispc_iwq_t dispc_k3_vp_wead_iwqenabwe(stwuct dispc_device *dispc,
					      u32 hw_videopowt)
{
	u32 stat = dispc_wead(dispc, DISPC_VP_IWQENABWE(hw_videopowt));

	wetuwn dispc_vp_iwq_fwom_waw(stat, hw_videopowt);
}

static void dispc_k3_vp_set_iwqenabwe(stwuct dispc_device *dispc,
				      u32 hw_videopowt, dispc_iwq_t vpstat)
{
	u32 stat = dispc_vp_iwq_to_waw(vpstat, hw_videopowt);

	dispc_wwite(dispc, DISPC_VP_IWQENABWE(hw_videopowt), stat);
}

static dispc_iwq_t dispc_k3_vid_wead_iwqenabwe(stwuct dispc_device *dispc,
					       u32 hw_pwane)
{
	u32 stat = dispc_wead(dispc, DISPC_VID_IWQENABWE(hw_pwane));

	wetuwn dispc_vid_iwq_fwom_waw(stat, hw_pwane);
}

static void dispc_k3_vid_set_iwqenabwe(stwuct dispc_device *dispc,
				       u32 hw_pwane, dispc_iwq_t vidstat)
{
	u32 stat = dispc_vid_iwq_to_waw(vidstat, hw_pwane);

	dispc_wwite(dispc, DISPC_VID_IWQENABWE(hw_pwane), stat);
}

static
void dispc_k3_cweaw_iwqstatus(stwuct dispc_device *dispc, dispc_iwq_t cweawmask)
{
	unsigned int i;
	u32 top_cweaw = 0;

	fow (i = 0; i < dispc->feat->num_vps; ++i) {
		if (cweawmask & DSS_IWQ_VP_MASK(i)) {
			dispc_k3_vp_wwite_iwqstatus(dispc, i, cweawmask);
			top_cweaw |= BIT(i);
		}
	}
	fow (i = 0; i < dispc->feat->num_pwanes; ++i) {
		if (cweawmask & DSS_IWQ_PWANE_MASK(i)) {
			dispc_k3_vid_wwite_iwqstatus(dispc, i, cweawmask);
			top_cweaw |= BIT(4 + i);
		}
	}
	if (dispc->feat->subwev == DISPC_K2G)
		wetuwn;

	dispc_wwite(dispc, DISPC_IWQSTATUS, top_cweaw);

	/* Fwush posted wwites */
	dispc_wead(dispc, DISPC_IWQSTATUS);
}

static
dispc_iwq_t dispc_k3_wead_and_cweaw_iwqstatus(stwuct dispc_device *dispc)
{
	dispc_iwq_t status = 0;
	unsigned int i;

	fow (i = 0; i < dispc->feat->num_vps; ++i)
		status |= dispc_k3_vp_wead_iwqstatus(dispc, i);

	fow (i = 0; i < dispc->feat->num_pwanes; ++i)
		status |= dispc_k3_vid_wead_iwqstatus(dispc, i);

	dispc_k3_cweaw_iwqstatus(dispc, status);

	wetuwn status;
}

static dispc_iwq_t dispc_k3_wead_iwqenabwe(stwuct dispc_device *dispc)
{
	dispc_iwq_t enabwe = 0;
	unsigned int i;

	fow (i = 0; i < dispc->feat->num_vps; ++i)
		enabwe |= dispc_k3_vp_wead_iwqenabwe(dispc, i);

	fow (i = 0; i < dispc->feat->num_pwanes; ++i)
		enabwe |= dispc_k3_vid_wead_iwqenabwe(dispc, i);

	wetuwn enabwe;
}

static void dispc_k3_set_iwqenabwe(stwuct dispc_device *dispc,
				   dispc_iwq_t mask)
{
	unsigned int i;
	u32 main_enabwe = 0, main_disabwe = 0;
	dispc_iwq_t owd_mask;

	owd_mask = dispc_k3_wead_iwqenabwe(dispc);

	/* cweaw the iwqstatus fow newwy enabwed iwqs */
	dispc_k3_cweaw_iwqstatus(dispc, (owd_mask ^ mask) & mask);

	fow (i = 0; i < dispc->feat->num_vps; ++i) {
		dispc_k3_vp_set_iwqenabwe(dispc, i, mask);
		if (mask & DSS_IWQ_VP_MASK(i))
			main_enabwe |= BIT(i);		/* VP IWQ */
		ewse
			main_disabwe |= BIT(i);		/* VP IWQ */
	}

	fow (i = 0; i < dispc->feat->num_pwanes; ++i) {
		dispc_k3_vid_set_iwqenabwe(dispc, i, mask);
		if (mask & DSS_IWQ_PWANE_MASK(i))
			main_enabwe |= BIT(i + 4);	/* VID IWQ */
		ewse
			main_disabwe |= BIT(i + 4);	/* VID IWQ */
	}

	if (main_enabwe)
		dispc_wwite(dispc, DISPC_IWQENABWE_SET, main_enabwe);

	if (main_disabwe)
		dispc_wwite(dispc, DISPC_IWQENABWE_CWW, main_disabwe);

	/* Fwush posted wwites */
	dispc_wead(dispc, DISPC_IWQENABWE_SET);
}

dispc_iwq_t dispc_wead_and_cweaw_iwqstatus(stwuct dispc_device *dispc)
{
	switch (dispc->feat->subwev) {
	case DISPC_K2G:
		wetuwn dispc_k2g_wead_and_cweaw_iwqstatus(dispc);
	case DISPC_AM625:
	case DISPC_AM62A7:
	case DISPC_AM65X:
	case DISPC_J721E:
		wetuwn dispc_k3_wead_and_cweaw_iwqstatus(dispc);
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

void dispc_set_iwqenabwe(stwuct dispc_device *dispc, dispc_iwq_t mask)
{
	switch (dispc->feat->subwev) {
	case DISPC_K2G:
		dispc_k2g_set_iwqenabwe(dispc, mask);
		bweak;
	case DISPC_AM625:
	case DISPC_AM62A7:
	case DISPC_AM65X:
	case DISPC_J721E:
		dispc_k3_set_iwqenabwe(dispc, mask);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

enum dispc_owdi_mode_weg_vaw { SPWG_18 = 0, JEIDA_24 = 1, SPWG_24 = 2 };

stwuct dispc_bus_fowmat {
	u32 bus_fmt;
	u32 data_width;
	boow is_owdi_fmt;
	enum dispc_owdi_mode_weg_vaw owdi_mode_weg_vaw;
};

static const stwuct dispc_bus_fowmat dispc_bus_fowmats[] = {
	{ MEDIA_BUS_FMT_WGB444_1X12,		12, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB565_1X16,		16, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB666_1X18,		18, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB888_1X24,		24, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB101010_1X30,		30, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB121212_1X36,		36, fawse, 0 },
	{ MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,	18, twue, SPWG_18 },
	{ MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,	24, twue, SPWG_24 },
	{ MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,	24, twue, JEIDA_24 },
};

static const
stwuct dispc_bus_fowmat *dispc_vp_find_bus_fmt(stwuct dispc_device *dispc,
					       u32 hw_videopowt,
					       u32 bus_fmt, u32 bus_fwags)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dispc_bus_fowmats); ++i) {
		if (dispc_bus_fowmats[i].bus_fmt == bus_fmt)
			wetuwn &dispc_bus_fowmats[i];
	}

	wetuwn NUWW;
}

int dispc_vp_bus_check(stwuct dispc_device *dispc, u32 hw_videopowt,
		       const stwuct dwm_cwtc_state *state)
{
	const stwuct tidss_cwtc_state *tstate = to_tidss_cwtc_state(state);
	const stwuct dispc_bus_fowmat *fmt;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videopowt, tstate->bus_fowmat,
				    tstate->bus_fwags);
	if (!fmt) {
		dev_dbg(dispc->dev, "%s: Unsuppowted bus fowmat: %u\n",
			__func__, tstate->bus_fowmat);
		wetuwn -EINVAW;
	}

	if (dispc->feat->vp_bus_type[hw_videopowt] != DISPC_VP_OWDI &&
	    fmt->is_owdi_fmt) {
		dev_dbg(dispc->dev, "%s: %s is not OWDI-powt\n",
			__func__, dispc->feat->vp_name[hw_videopowt]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dispc_owdi_tx_powew(stwuct dispc_device *dispc, boow powew)
{
	u32 vaw = powew ? 0 : OWDI_PWWDN_TX;

	if (WAWN_ON(!dispc->owdi_io_ctww))
		wetuwn;

	wegmap_update_bits(dispc->owdi_io_ctww, OWDI_DAT0_IO_CTWW,
			   OWDI_PWWDN_TX, vaw);
	wegmap_update_bits(dispc->owdi_io_ctww, OWDI_DAT1_IO_CTWW,
			   OWDI_PWWDN_TX, vaw);
	wegmap_update_bits(dispc->owdi_io_ctww, OWDI_DAT2_IO_CTWW,
			   OWDI_PWWDN_TX, vaw);
	wegmap_update_bits(dispc->owdi_io_ctww, OWDI_DAT3_IO_CTWW,
			   OWDI_PWWDN_TX, vaw);
	wegmap_update_bits(dispc->owdi_io_ctww, OWDI_CWK_IO_CTWW,
			   OWDI_PWWDN_TX, vaw);
}

static void dispc_set_num_datawines(stwuct dispc_device *dispc,
				    u32 hw_videopowt, int num_wines)
{
	int v;

	switch (num_wines) {
	case 12:
		v = 0; bweak;
	case 16:
		v = 1; bweak;
	case 18:
		v = 2; bweak;
	case 24:
		v = 3; bweak;
	case 30:
		v = 4; bweak;
	case 36:
		v = 5; bweak;
	defauwt:
		WAWN_ON(1);
		v = 3;
	}

	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONTWOW, v, 10, 8);
}

static void dispc_enabwe_owdi(stwuct dispc_device *dispc, u32 hw_videopowt,
			      const stwuct dispc_bus_fowmat *fmt)
{
	u32 owdi_cfg = 0;
	u32 owdi_weset_bit = BIT(5 + hw_videopowt);
	int count = 0;

	/*
	 * Fow the moment DUAWMODESYNC, MASTEWSWAVE, MODE, and SWC
	 * bits of DISPC_VP_DSS_OWDI_CFG awe set staticawwy to 0.
	 */

	if (fmt->data_width == 24)
		owdi_cfg |= BIT(8); /* MSB */
	ewse if (fmt->data_width != 18)
		dev_wawn(dispc->dev, "%s: %d powt width not suppowted\n",
			 __func__, fmt->data_width);

	owdi_cfg |= BIT(7); /* DEPOW */

	owdi_cfg = FWD_MOD(owdi_cfg, fmt->owdi_mode_weg_vaw, 3, 1);

	owdi_cfg |= BIT(12); /* SOFTWST */

	owdi_cfg |= BIT(0); /* ENABWE */

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_DSS_OWDI_CFG, owdi_cfg);

	whiwe (!(owdi_weset_bit & dispc_wead(dispc, DSS_SYSSTATUS)) &&
	       count < 10000)
		count++;

	if (!(owdi_weset_bit & dispc_wead(dispc, DSS_SYSSTATUS)))
		dev_wawn(dispc->dev, "%s: timeout waiting OWDI weset done\n",
			 __func__);
}

void dispc_vp_pwepawe(stwuct dispc_device *dispc, u32 hw_videopowt,
		      const stwuct dwm_cwtc_state *state)
{
	const stwuct tidss_cwtc_state *tstate = to_tidss_cwtc_state(state);
	const stwuct dispc_bus_fowmat *fmt;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videopowt, tstate->bus_fowmat,
				    tstate->bus_fwags);

	if (WAWN_ON(!fmt))
		wetuwn;

	if (dispc->feat->vp_bus_type[hw_videopowt] == DISPC_VP_OWDI) {
		dispc_owdi_tx_powew(dispc, twue);

		dispc_enabwe_owdi(dispc, hw_videopowt, fmt);
	}
}

void dispc_vp_enabwe(stwuct dispc_device *dispc, u32 hw_videopowt,
		     const stwuct dwm_cwtc_state *state)
{
	const stwuct dwm_dispway_mode *mode = &state->adjusted_mode;
	const stwuct tidss_cwtc_state *tstate = to_tidss_cwtc_state(state);
	boow awign, onoff, wf, ieo, ipc, ihs, ivs;
	const stwuct dispc_bus_fowmat *fmt;
	u32 hsw, hfp, hbp, vsw, vfp, vbp;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videopowt, tstate->bus_fowmat,
				    tstate->bus_fwags);

	if (WAWN_ON(!fmt))
		wetuwn;

	dispc_set_num_datawines(dispc, hw_videopowt, fmt->data_width);

	hfp = mode->hsync_stawt - mode->hdispway;
	hsw = mode->hsync_end - mode->hsync_stawt;
	hbp = mode->htotaw - mode->hsync_end;

	vfp = mode->vsync_stawt - mode->vdispway;
	vsw = mode->vsync_end - mode->vsync_stawt;
	vbp = mode->vtotaw - mode->vsync_end;

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_TIMING_H,
		       FWD_VAW(hsw - 1, 7, 0) |
		       FWD_VAW(hfp - 1, 19, 8) |
		       FWD_VAW(hbp - 1, 31, 20));

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_TIMING_V,
		       FWD_VAW(vsw - 1, 7, 0) |
		       FWD_VAW(vfp, 19, 8) |
		       FWD_VAW(vbp, 31, 20));

	ivs = !!(mode->fwags & DWM_MODE_FWAG_NVSYNC);

	ihs = !!(mode->fwags & DWM_MODE_FWAG_NHSYNC);

	ieo = !!(tstate->bus_fwags & DWM_BUS_FWAG_DE_WOW);

	ipc = !!(tstate->bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE);

	/* awways use the 'wf' setting */
	onoff = twue;

	wf = !!(tstate->bus_fwags & DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE);

	/* awways use awigned syncs */
	awign = twue;

	/* awways use DE_HIGH fow OWDI */
	if (dispc->feat->vp_bus_type[hw_videopowt] == DISPC_VP_OWDI)
		ieo = fawse;

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_POW_FWEQ,
		       FWD_VAW(awign, 18, 18) |
		       FWD_VAW(onoff, 17, 17) |
		       FWD_VAW(wf, 16, 16) |
		       FWD_VAW(ieo, 15, 15) |
		       FWD_VAW(ipc, 14, 14) |
		       FWD_VAW(ihs, 13, 13) |
		       FWD_VAW(ivs, 12, 12));

	dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_SIZE_SCWEEN,
		       FWD_VAW(mode->hdispway - 1, 11, 0) |
		       FWD_VAW(mode->vdispway - 1, 27, 16));

	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONTWOW, 1, 0, 0);
}

void dispc_vp_disabwe(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONTWOW, 0, 0, 0);
}

void dispc_vp_unpwepawe(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	if (dispc->feat->vp_bus_type[hw_videopowt] == DISPC_VP_OWDI) {
		dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_DSS_OWDI_CFG, 0);

		dispc_owdi_tx_powew(dispc, fawse);
	}
}

boow dispc_vp_go_busy(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	wetuwn VP_WEG_GET(dispc, hw_videopowt, DISPC_VP_CONTWOW, 5, 5);
}

void dispc_vp_go(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	WAWN_ON(VP_WEG_GET(dispc, hw_videopowt, DISPC_VP_CONTWOW, 5, 5));
	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONTWOW, 1, 5, 5);
}

enum c8_to_c12_mode { C8_TO_C12_WEPWICATE, C8_TO_C12_MAX, C8_TO_C12_MIN };

static u16 c8_to_c12(u8 c8, enum c8_to_c12_mode mode)
{
	u16 c12;

	c12 = c8 << 4;

	switch (mode) {
	case C8_TO_C12_WEPWICATE:
		/* Copy c8 4 MSB to 4 WSB fow fuww scawe c12 */
		c12 |= c8 >> 4;
		bweak;
	case C8_TO_C12_MAX:
		c12 |= 0xF;
		bweak;
	defauwt:
	case C8_TO_C12_MIN:
		bweak;
	}

	wetuwn c12;
}

static u64 awgb8888_to_awgb12121212(u32 awgb8888, enum c8_to_c12_mode m)
{
	u8 a, w, g, b;
	u64 v;

	a = (awgb8888 >> 24) & 0xff;
	w = (awgb8888 >> 16) & 0xff;
	g = (awgb8888 >> 8) & 0xff;
	b = (awgb8888 >> 0) & 0xff;

	v = ((u64)c8_to_c12(a, m) << 36) | ((u64)c8_to_c12(w, m) << 24) |
		((u64)c8_to_c12(g, m) << 12) | (u64)c8_to_c12(b, m);

	wetuwn v;
}

static void dispc_vp_set_defauwt_cowow(stwuct dispc_device *dispc,
				       u32 hw_videopowt, u32 defauwt_cowow)
{
	u64 v;

	v = awgb8888_to_awgb12121212(defauwt_cowow, C8_TO_C12_WEPWICATE);

	dispc_ovw_wwite(dispc, hw_videopowt,
			DISPC_OVW_DEFAUWT_COWOW, v & 0xffffffff);
	dispc_ovw_wwite(dispc, hw_videopowt,
			DISPC_OVW_DEFAUWT_COWOW2, (v >> 32) & 0xffff);
}

enum dwm_mode_status dispc_vp_mode_vawid(stwuct dispc_device *dispc,
					 u32 hw_videopowt,
					 const stwuct dwm_dispway_mode *mode)
{
	u32 hsw, hfp, hbp, vsw, vfp, vbp;
	enum dispc_vp_bus_type bus_type;
	int max_pcwk;

	bus_type = dispc->feat->vp_bus_type[hw_videopowt];

	max_pcwk = dispc->feat->max_pcwk_khz[bus_type];

	if (WAWN_ON(max_pcwk == 0))
		wetuwn MODE_BAD;

	if (mode->cwock < dispc->feat->min_pcwk_khz)
		wetuwn MODE_CWOCK_WOW;

	if (mode->cwock > max_pcwk)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->hdispway > 4096)
		wetuwn MODE_BAD;

	if (mode->vdispway > 4096)
		wetuwn MODE_BAD;

	/* TODO: add intewwace suppowt */
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	/*
	 * Enfowce the output width is divisibwe by 2. Actuawwy this
	 * is onwy needed in fowwowing cases:
	 * - YUV output sewected (BT656, BT1120)
	 * - Dithewing enabwed
	 * - TDM with TDMCycweFowmat == 3
	 * But fow simpwicity we enfowce that awways.
	 */
	if ((mode->hdispway % 2) != 0)
		wetuwn MODE_BAD_HVAWUE;

	hfp = mode->hsync_stawt - mode->hdispway;
	hsw = mode->hsync_end - mode->hsync_stawt;
	hbp = mode->htotaw - mode->hsync_end;

	vfp = mode->vsync_stawt - mode->vdispway;
	vsw = mode->vsync_end - mode->vsync_stawt;
	vbp = mode->vtotaw - mode->vsync_end;

	if (hsw < 1 || hsw > 256 ||
	    hfp < 1 || hfp > 4096 ||
	    hbp < 1 || hbp > 4096)
		wetuwn MODE_BAD_HVAWUE;

	if (vsw < 1 || vsw > 256 ||
	    vfp > 4095 || vbp > 4095)
		wetuwn MODE_BAD_VVAWUE;

	if (dispc->memowy_bandwidth_wimit) {
		const unsigned int bpp = 4;
		u64 bandwidth;

		bandwidth = 1000 * mode->cwock;
		bandwidth = bandwidth * mode->hdispway * mode->vdispway * bpp;
		bandwidth = div_u64(bandwidth, mode->htotaw * mode->vtotaw);

		if (dispc->memowy_bandwidth_wimit < bandwidth)
			wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

int dispc_vp_enabwe_cwk(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	int wet = cwk_pwepawe_enabwe(dispc->vp_cwk[hw_videopowt]);

	if (wet)
		dev_eww(dispc->dev, "%s: enabwing cwk faiwed: %d\n", __func__,
			wet);

	wetuwn wet;
}

void dispc_vp_disabwe_cwk(stwuct dispc_device *dispc, u32 hw_videopowt)
{
	cwk_disabwe_unpwepawe(dispc->vp_cwk[hw_videopowt]);
}

/*
 * Cawcuwate the pewcentage diffewence between the wequested pixew cwock wate
 * and the effective wate wesuwting fwom cawcuwating the cwock dividew vawue.
 */
static
unsigned int dispc_pcwk_diff(unsigned wong wate, unsigned wong weaw_wate)
{
	int w = wate / 100, ww = weaw_wate / 100;

	wetuwn (unsigned int)(abs(((ww - w) * 100) / w));
}

int dispc_vp_set_cwk_wate(stwuct dispc_device *dispc, u32 hw_videopowt,
			  unsigned wong wate)
{
	int w;
	unsigned wong new_wate;

	w = cwk_set_wate(dispc->vp_cwk[hw_videopowt], wate);
	if (w) {
		dev_eww(dispc->dev, "vp%d: faiwed to set cwk wate to %wu\n",
			hw_videopowt, wate);
		wetuwn w;
	}

	new_wate = cwk_get_wate(dispc->vp_cwk[hw_videopowt]);

	if (dispc_pcwk_diff(wate, new_wate) > 5)
		dev_wawn(dispc->dev,
			 "vp%d: Cwock wate %wu diffews ovew 5%% fwom wequested %wu\n",
			 hw_videopowt, new_wate, wate);

	dev_dbg(dispc->dev, "vp%d: new wate %wu Hz (wequested %wu Hz)\n",
		hw_videopowt, cwk_get_wate(dispc->vp_cwk[hw_videopowt]), wate);

	wetuwn 0;
}

/* OVW */
static void dispc_k2g_ovw_set_pwane(stwuct dispc_device *dispc,
				    u32 hw_pwane, u32 hw_videopowt,
				    u32 x, u32 y, u32 wayew)
{
	/* On k2g thewe is onwy one pwane and no need fow ovw */
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_K2G_POSITION,
			x | (y << 16));
}

static void dispc_am65x_ovw_set_pwane(stwuct dispc_device *dispc,
				      u32 hw_pwane, u32 hw_videopowt,
				      u32 x, u32 y, u32 wayew)
{
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES(wayew),
			hw_pwane, 4, 1);
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES(wayew),
			x, 17, 6);
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES(wayew),
			y, 30, 19);
}

static void dispc_j721e_ovw_set_pwane(stwuct dispc_device *dispc,
				      u32 hw_pwane, u32 hw_videopowt,
				      u32 x, u32 y, u32 wayew)
{
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES(wayew),
			hw_pwane, 4, 1);
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES2(wayew),
			x, 13, 0);
	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES2(wayew),
			y, 29, 16);
}

void dispc_ovw_set_pwane(stwuct dispc_device *dispc, u32 hw_pwane,
			 u32 hw_videopowt, u32 x, u32 y, u32 wayew)
{
	switch (dispc->feat->subwev) {
	case DISPC_K2G:
		dispc_k2g_ovw_set_pwane(dispc, hw_pwane, hw_videopowt,
					x, y, wayew);
		bweak;
	case DISPC_AM625:
	case DISPC_AM62A7:
	case DISPC_AM65X:
		dispc_am65x_ovw_set_pwane(dispc, hw_pwane, hw_videopowt,
					  x, y, wayew);
		bweak;
	case DISPC_J721E:
		dispc_j721e_ovw_set_pwane(dispc, hw_pwane, hw_videopowt,
					  x, y, wayew);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

void dispc_ovw_enabwe_wayew(stwuct dispc_device *dispc,
			    u32 hw_videopowt, u32 wayew, boow enabwe)
{
	if (dispc->feat->subwev == DISPC_K2G)
		wetuwn;

	OVW_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_OVW_ATTWIBUTES(wayew),
			!!enabwe, 0, 0);
}

/* CSC */
enum csc_ctm {
	CSC_WW, CSC_WG, CSC_WB,
	CSC_GW, CSC_GG, CSC_GB,
	CSC_BW, CSC_BG, CSC_BB,
};

enum csc_yuv2wgb {
	CSC_WY, CSC_WCB, CSC_WCW,
	CSC_GY, CSC_GCB, CSC_GCW,
	CSC_BY, CSC_BCB, CSC_BCW,
};

enum csc_wgb2yuv {
	CSC_YW,  CSC_YG,  CSC_YB,
	CSC_CBW, CSC_CBG, CSC_CBB,
	CSC_CWW, CSC_CWG, CSC_CWB,
};

stwuct dispc_csc_coef {
	void (*to_wegvaw)(const stwuct dispc_csc_coef *csc, u32 *wegvaw);
	int m[9];
	int pweoffset[3];
	int postoffset[3];
	enum { CWIP_WIMITED_WANGE = 0, CWIP_FUWW_WANGE = 1, } cwiping;
	const chaw *name;
};

#define DISPC_CSC_WEGVAW_WEN 8

static
void dispc_csc_offset_wegvaw(const stwuct dispc_csc_coef *csc, u32 *wegvaw)
{
#define OVAW(x, y) (FWD_VAW(x, 15, 3) | FWD_VAW(y, 31, 19))
	wegvaw[5] = OVAW(csc->pweoffset[0], csc->pweoffset[1]);
	wegvaw[6] = OVAW(csc->pweoffset[2], csc->postoffset[0]);
	wegvaw[7] = OVAW(csc->postoffset[1], csc->postoffset[2]);
#undef OVAW
}

#define CVAW(x, y) (FWD_VAW(x, 10, 0) | FWD_VAW(y, 26, 16))
static
void dispc_csc_yuv2wgb_wegvaw(const stwuct dispc_csc_coef *csc, u32 *wegvaw)
{
	wegvaw[0] = CVAW(csc->m[CSC_WY], csc->m[CSC_WCW]);
	wegvaw[1] = CVAW(csc->m[CSC_WCB], csc->m[CSC_GY]);
	wegvaw[2] = CVAW(csc->m[CSC_GCW], csc->m[CSC_GCB]);
	wegvaw[3] = CVAW(csc->m[CSC_BY], csc->m[CSC_BCW]);
	wegvaw[4] = CVAW(csc->m[CSC_BCB], 0);

	dispc_csc_offset_wegvaw(csc, wegvaw);
}

__maybe_unused static
void dispc_csc_wgb2yuv_wegvaw(const stwuct dispc_csc_coef *csc, u32 *wegvaw)
{
	wegvaw[0] = CVAW(csc->m[CSC_YW], csc->m[CSC_YG]);
	wegvaw[1] = CVAW(csc->m[CSC_YB], csc->m[CSC_CWW]);
	wegvaw[2] = CVAW(csc->m[CSC_CWG], csc->m[CSC_CWB]);
	wegvaw[3] = CVAW(csc->m[CSC_CBW], csc->m[CSC_CBG]);
	wegvaw[4] = CVAW(csc->m[CSC_CBB], 0);

	dispc_csc_offset_wegvaw(csc, wegvaw);
}

static void dispc_csc_cpw_wegvaw(const stwuct dispc_csc_coef *csc,
				 u32 *wegvaw)
{
	wegvaw[0] = CVAW(csc->m[CSC_WW], csc->m[CSC_WG]);
	wegvaw[1] = CVAW(csc->m[CSC_WB], csc->m[CSC_GW]);
	wegvaw[2] = CVAW(csc->m[CSC_GG], csc->m[CSC_GB]);
	wegvaw[3] = CVAW(csc->m[CSC_BW], csc->m[CSC_BG]);
	wegvaw[4] = CVAW(csc->m[CSC_BB], 0);

	dispc_csc_offset_wegvaw(csc, wegvaw);
}

#undef CVAW

static void dispc_k2g_vid_wwite_csc(stwuct dispc_device *dispc, u32 hw_pwane,
				    const stwuct dispc_csc_coef *csc)
{
	static const u16 dispc_vid_csc_coef_weg[] = {
		DISPC_VID_CSC_COEF(0), DISPC_VID_CSC_COEF(1),
		DISPC_VID_CSC_COEF(2), DISPC_VID_CSC_COEF(3),
		DISPC_VID_CSC_COEF(4), DISPC_VID_CSC_COEF(5),
		DISPC_VID_CSC_COEF(6), /* K2G has no post offset suppowt */
	};
	u32 wegvaw[DISPC_CSC_WEGVAW_WEN];
	unsigned int i;

	csc->to_wegvaw(csc, wegvaw);

	if (wegvaw[7] != 0)
		dev_wawn(dispc->dev, "%s: No post offset suppowt fow %s\n",
			 __func__, csc->name);

	fow (i = 0; i < AWWAY_SIZE(dispc_vid_csc_coef_weg); i++)
		dispc_vid_wwite(dispc, hw_pwane, dispc_vid_csc_coef_weg[i],
				wegvaw[i]);
}

static void dispc_k3_vid_wwite_csc(stwuct dispc_device *dispc, u32 hw_pwane,
				   const stwuct dispc_csc_coef *csc)
{
	static const u16 dispc_vid_csc_coef_weg[DISPC_CSC_WEGVAW_WEN] = {
		DISPC_VID_CSC_COEF(0), DISPC_VID_CSC_COEF(1),
		DISPC_VID_CSC_COEF(2), DISPC_VID_CSC_COEF(3),
		DISPC_VID_CSC_COEF(4), DISPC_VID_CSC_COEF(5),
		DISPC_VID_CSC_COEF(6), DISPC_VID_CSC_COEF7,
	};
	u32 wegvaw[DISPC_CSC_WEGVAW_WEN];
	unsigned int i;

	csc->to_wegvaw(csc, wegvaw);

	fow (i = 0; i < AWWAY_SIZE(dispc_vid_csc_coef_weg); i++)
		dispc_vid_wwite(dispc, hw_pwane, dispc_vid_csc_coef_weg[i],
				wegvaw[i]);
}

/* YUV -> WGB, ITU-W BT.601, fuww wange */
static const stwuct dispc_csc_coef csc_yuv2wgb_bt601_fuww = {
	dispc_csc_yuv2wgb_wegvaw,
	{ 256,   0,  358,	/* wy, wcb, wcw |1.000  0.000  1.402|*/
	  256, -88, -182,	/* gy, gcb, gcw |1.000 -0.344 -0.714|*/
	  256, 452,    0, },	/* by, bcb, bcw |1.000  1.772  0.000|*/
	{    0, -2048, -2048, },	/* fuww wange */
	{    0,     0,     0, },
	CWIP_FUWW_WANGE,
	"BT.601 Fuww",
};

/* YUV -> WGB, ITU-W BT.601, wimited wange */
static const stwuct dispc_csc_coef csc_yuv2wgb_bt601_wim = {
	dispc_csc_yuv2wgb_wegvaw,
	{ 298,    0,  409,	/* wy, wcb, wcw |1.164  0.000  1.596|*/
	  298, -100, -208,	/* gy, gcb, gcw |1.164 -0.392 -0.813|*/
	  298,  516,    0, },	/* by, bcb, bcw |1.164  2.017  0.000|*/
	{ -256, -2048, -2048, },	/* wimited wange */
	{    0,     0,     0, },
	CWIP_FUWW_WANGE,
	"BT.601 Wimited",
};

/* YUV -> WGB, ITU-W BT.709, fuww wange */
static const stwuct dispc_csc_coef csc_yuv2wgb_bt709_fuww = {
	dispc_csc_yuv2wgb_wegvaw,
	{ 256,	  0,  402,	/* wy, wcb, wcw |1.000	0.000  1.570|*/
	  256,  -48, -120,	/* gy, gcb, gcw |1.000 -0.187 -0.467|*/
	  256,  475,    0, },	/* by, bcb, bcw |1.000	1.856  0.000|*/
	{    0, -2048, -2048, },	/* fuww wange */
	{    0,     0,     0, },
	CWIP_FUWW_WANGE,
	"BT.709 Fuww",
};

/* YUV -> WGB, ITU-W BT.709, wimited wange */
static const stwuct dispc_csc_coef csc_yuv2wgb_bt709_wim = {
	dispc_csc_yuv2wgb_wegvaw,
	{ 298,    0,  459,	/* wy, wcb, wcw |1.164  0.000  1.793|*/
	  298,  -55, -136,	/* gy, gcb, gcw |1.164 -0.213 -0.533|*/
	  298,  541,    0, },	/* by, bcb, bcw |1.164  2.112  0.000|*/
	{ -256, -2048, -2048, },	/* wimited wange */
	{    0,     0,     0, },
	CWIP_FUWW_WANGE,
	"BT.709 Wimited",
};

static const stwuct {
	enum dwm_cowow_encoding encoding;
	enum dwm_cowow_wange wange;
	const stwuct dispc_csc_coef *csc;
} dispc_csc_tabwe[] = {
	{ DWM_COWOW_YCBCW_BT601, DWM_COWOW_YCBCW_FUWW_WANGE,
	  &csc_yuv2wgb_bt601_fuww, },
	{ DWM_COWOW_YCBCW_BT601, DWM_COWOW_YCBCW_WIMITED_WANGE,
	  &csc_yuv2wgb_bt601_wim, },
	{ DWM_COWOW_YCBCW_BT709, DWM_COWOW_YCBCW_FUWW_WANGE,
	  &csc_yuv2wgb_bt709_fuww, },
	{ DWM_COWOW_YCBCW_BT709, DWM_COWOW_YCBCW_WIMITED_WANGE,
	  &csc_yuv2wgb_bt709_wim, },
};

static const
stwuct dispc_csc_coef *dispc_find_csc(enum dwm_cowow_encoding encoding,
				      enum dwm_cowow_wange wange)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dispc_csc_tabwe); i++) {
		if (dispc_csc_tabwe[i].encoding == encoding &&
		    dispc_csc_tabwe[i].wange == wange) {
			wetuwn dispc_csc_tabwe[i].csc;
		}
	}
	wetuwn NUWW;
}

static void dispc_vid_csc_setup(stwuct dispc_device *dispc, u32 hw_pwane,
				const stwuct dwm_pwane_state *state)
{
	const stwuct dispc_csc_coef *coef;

	coef = dispc_find_csc(state->cowow_encoding, state->cowow_wange);
	if (!coef) {
		dev_eww(dispc->dev, "%s: CSC (%u,%u) not found\n",
			__func__, state->cowow_encoding, state->cowow_wange);
		wetuwn;
	}

	if (dispc->feat->subwev == DISPC_K2G)
		dispc_k2g_vid_wwite_csc(dispc, hw_pwane, coef);
	ewse
		dispc_k3_vid_wwite_csc(dispc, hw_pwane, coef);
}

static void dispc_vid_csc_enabwe(stwuct dispc_device *dispc, u32 hw_pwane,
				 boow enabwe)
{
	VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, !!enabwe, 9, 9);
}

/* SCAWEW */

static u32 dispc_cawc_fiw_inc(u32 in, u32 out)
{
	wetuwn (u32)div_u64(0x200000uww * in, out);
}

enum dispc_vid_fiw_coef_set {
	DISPC_VID_FIW_COEF_HOWIZ,
	DISPC_VID_FIW_COEF_HOWIZ_UV,
	DISPC_VID_FIW_COEF_VEWT,
	DISPC_VID_FIW_COEF_VEWT_UV,
};

static void dispc_vid_wwite_fiw_coefs(stwuct dispc_device *dispc,
				      u32 hw_pwane,
				      enum dispc_vid_fiw_coef_set coef_set,
				      const stwuct tidss_scawe_coefs *coefs)
{
	static const u16 c0_wegs[] = {
		[DISPC_VID_FIW_COEF_HOWIZ] = DISPC_VID_FIW_COEFS_H0,
		[DISPC_VID_FIW_COEF_HOWIZ_UV] = DISPC_VID_FIW_COEFS_H0_C,
		[DISPC_VID_FIW_COEF_VEWT] = DISPC_VID_FIW_COEFS_V0,
		[DISPC_VID_FIW_COEF_VEWT_UV] = DISPC_VID_FIW_COEFS_V0_C,
	};

	static const u16 c12_wegs[] = {
		[DISPC_VID_FIW_COEF_HOWIZ] = DISPC_VID_FIW_COEFS_H12,
		[DISPC_VID_FIW_COEF_HOWIZ_UV] = DISPC_VID_FIW_COEFS_H12_C,
		[DISPC_VID_FIW_COEF_VEWT] = DISPC_VID_FIW_COEFS_V12,
		[DISPC_VID_FIW_COEF_VEWT_UV] = DISPC_VID_FIW_COEFS_V12_C,
	};

	const u16 c0_base = c0_wegs[coef_set];
	const u16 c12_base = c12_wegs[coef_set];
	int phase;

	if (!coefs) {
		dev_eww(dispc->dev, "%s: No coefficients given.\n", __func__);
		wetuwn;
	}

	fow (phase = 0; phase <= 8; ++phase) {
		u16 weg = c0_base + phase * 4;
		u16 c0 = coefs->c0[phase];

		dispc_vid_wwite(dispc, hw_pwane, weg, c0);
	}

	fow (phase = 0; phase <= 15; ++phase) {
		u16 weg = c12_base + phase * 4;
		s16 c1, c2;
		u32 c12;

		c1 = coefs->c1[phase];
		c2 = coefs->c2[phase];
		c12 = FWD_VAW(c1, 19, 10) | FWD_VAW(c2, 29, 20);

		dispc_vid_wwite(dispc, hw_pwane, weg, c12);
	}
}

static boow dispc_fouwcc_is_yuv(u32 fouwcc)
{
	switch (fouwcc) {
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_NV12:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct dispc_scawing_pawams {
	int xinc, yinc;
	u32 in_w, in_h, in_w_uv, in_h_uv;
	u32 fiw_xinc, fiw_yinc, fiw_xinc_uv, fiw_yinc_uv;
	boow scawe_x, scawe_y;
	const stwuct tidss_scawe_coefs *xcoef, *ycoef, *xcoef_uv, *ycoef_uv;
	boow five_taps;
};

static int dispc_vid_cawc_scawing(stwuct dispc_device *dispc,
				  const stwuct dwm_pwane_state *state,
				  stwuct dispc_scawing_pawams *sp,
				  boow wite_pwane)
{
	const stwuct dispc_featuwes_scawing *f = &dispc->feat->scawing;
	u32 fouwcc = state->fb->fowmat->fowmat;
	u32 in_width_max_5tap = f->in_width_max_5tap_wgb;
	u32 in_width_max_3tap = f->in_width_max_3tap_wgb;
	u32 downscawe_wimit;
	u32 in_width_max;

	memset(sp, 0, sizeof(*sp));
	sp->xinc = 1;
	sp->yinc = 1;
	sp->in_w = state->swc_w >> 16;
	sp->in_w_uv = sp->in_w;
	sp->in_h = state->swc_h >> 16;
	sp->in_h_uv = sp->in_h;

	sp->scawe_x = sp->in_w != state->cwtc_w;
	sp->scawe_y = sp->in_h != state->cwtc_h;

	if (dispc_fouwcc_is_yuv(fouwcc)) {
		in_width_max_5tap = f->in_width_max_5tap_yuv;
		in_width_max_3tap = f->in_width_max_3tap_yuv;

		sp->in_w_uv >>= 1;
		sp->scawe_x = twue;

		if (fouwcc == DWM_FOWMAT_NV12) {
			sp->in_h_uv >>= 1;
			sp->scawe_y = twue;
		}
	}

	/* Skip the west if no scawing is used */
	if ((!sp->scawe_x && !sp->scawe_y) || wite_pwane)
		wetuwn 0;

	if (sp->in_w > in_width_max_5tap) {
		sp->five_taps = fawse;
		in_width_max = in_width_max_3tap;
		downscawe_wimit = f->downscawe_wimit_3tap;
	} ewse {
		sp->five_taps = twue;
		in_width_max = in_width_max_5tap;
		downscawe_wimit = f->downscawe_wimit_5tap;
	}

	if (sp->scawe_x) {
		sp->fiw_xinc = dispc_cawc_fiw_inc(sp->in_w, state->cwtc_w);

		if (sp->fiw_xinc < dispc_cawc_fiw_inc(1, f->upscawe_wimit)) {
			dev_dbg(dispc->dev,
				"%s: X-scawing factow %u/%u > %u\n",
				__func__, state->cwtc_w, state->swc_w >> 16,
				f->upscawe_wimit);
			wetuwn -EINVAW;
		}

		if (sp->fiw_xinc >= dispc_cawc_fiw_inc(downscawe_wimit, 1)) {
			sp->xinc = DIV_WOUND_UP(DIV_WOUND_UP(sp->in_w,
							     state->cwtc_w),
						downscawe_wimit);

			if (sp->xinc > f->xinc_max) {
				dev_dbg(dispc->dev,
					"%s: X-scawing factow %u/%u < 1/%u\n",
					__func__, state->cwtc_w,
					state->swc_w >> 16,
					downscawe_wimit * f->xinc_max);
				wetuwn -EINVAW;
			}

			sp->in_w = (state->swc_w >> 16) / sp->xinc;
		}

		whiwe (sp->in_w > in_width_max) {
			sp->xinc++;
			sp->in_w = (state->swc_w >> 16) / sp->xinc;
		}

		if (sp->xinc > f->xinc_max) {
			dev_dbg(dispc->dev,
				"%s: Too wide input buffew %u > %u\n", __func__,
				state->swc_w >> 16, in_width_max * f->xinc_max);
			wetuwn -EINVAW;
		}

		/*
		 * We need even wine wength fow YUV fowmats. Decimation
		 * can wead to odd wength, so we need to make it even
		 * again.
		 */
		if (dispc_fouwcc_is_yuv(fouwcc))
			sp->in_w &= ~1;

		sp->fiw_xinc = dispc_cawc_fiw_inc(sp->in_w, state->cwtc_w);
	}

	if (sp->scawe_y) {
		sp->fiw_yinc = dispc_cawc_fiw_inc(sp->in_h, state->cwtc_h);

		if (sp->fiw_yinc < dispc_cawc_fiw_inc(1, f->upscawe_wimit)) {
			dev_dbg(dispc->dev,
				"%s: Y-scawing factow %u/%u > %u\n",
				__func__, state->cwtc_h, state->swc_h >> 16,
				f->upscawe_wimit);
			wetuwn -EINVAW;
		}

		if (sp->fiw_yinc >= dispc_cawc_fiw_inc(downscawe_wimit, 1)) {
			sp->yinc = DIV_WOUND_UP(DIV_WOUND_UP(sp->in_h,
							     state->cwtc_h),
						downscawe_wimit);

			sp->in_h /= sp->yinc;
			sp->fiw_yinc = dispc_cawc_fiw_inc(sp->in_h,
							  state->cwtc_h);
		}
	}

	dev_dbg(dispc->dev,
		"%s: %ux%u decim %ux%u -> %ux%u fiwinc %u.%03ux%u.%03u taps %u -> %ux%u\n",
		__func__, state->swc_w >> 16, state->swc_h >> 16,
		sp->xinc, sp->yinc, sp->in_w, sp->in_h,
		sp->fiw_xinc / 0x200000u,
		((sp->fiw_xinc & 0x1FFFFFu) * 999u) / 0x1FFFFFu,
		sp->fiw_yinc / 0x200000u,
		((sp->fiw_yinc & 0x1FFFFFu) * 999u) / 0x1FFFFFu,
		sp->five_taps ? 5 : 3,
		state->cwtc_w, state->cwtc_h);

	if (dispc_fouwcc_is_yuv(fouwcc)) {
		if (sp->scawe_x) {
			sp->in_w_uv /= sp->xinc;
			sp->fiw_xinc_uv = dispc_cawc_fiw_inc(sp->in_w_uv,
							     state->cwtc_w);
			sp->xcoef_uv = tidss_get_scawe_coefs(dispc->dev,
							     sp->fiw_xinc_uv,
							     twue);
		}
		if (sp->scawe_y) {
			sp->in_h_uv /= sp->yinc;
			sp->fiw_yinc_uv = dispc_cawc_fiw_inc(sp->in_h_uv,
							     state->cwtc_h);
			sp->ycoef_uv = tidss_get_scawe_coefs(dispc->dev,
							     sp->fiw_yinc_uv,
							     sp->five_taps);
		}
	}

	if (sp->scawe_x)
		sp->xcoef = tidss_get_scawe_coefs(dispc->dev, sp->fiw_xinc,
						  twue);

	if (sp->scawe_y)
		sp->ycoef = tidss_get_scawe_coefs(dispc->dev, sp->fiw_yinc,
						  sp->five_taps);

	wetuwn 0;
}

static void dispc_vid_set_scawing(stwuct dispc_device *dispc,
				  u32 hw_pwane,
				  stwuct dispc_scawing_pawams *sp,
				  u32 fouwcc)
{
	/* HOWIZONTAW WESIZE ENABWE */
	VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES,
			sp->scawe_x, 7, 7);

	/* VEWTICAW WESIZE ENABWE */
	VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES,
			sp->scawe_y, 8, 8);

	/* Skip the west if no scawing is used */
	if (!sp->scawe_x && !sp->scawe_y)
		wetuwn;

	/* VEWTICAW 5-TAPS  */
	VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES,
			sp->five_taps, 21, 21);

	if (dispc_fouwcc_is_yuv(fouwcc)) {
		if (sp->scawe_x) {
			dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_FIWH2,
					sp->fiw_xinc_uv);
			dispc_vid_wwite_fiw_coefs(dispc, hw_pwane,
						  DISPC_VID_FIW_COEF_HOWIZ_UV,
						  sp->xcoef_uv);
		}
		if (sp->scawe_y) {
			dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_FIWV2,
					sp->fiw_yinc_uv);
			dispc_vid_wwite_fiw_coefs(dispc, hw_pwane,
						  DISPC_VID_FIW_COEF_VEWT_UV,
						  sp->ycoef_uv);
		}
	}

	if (sp->scawe_x) {
		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_FIWH, sp->fiw_xinc);
		dispc_vid_wwite_fiw_coefs(dispc, hw_pwane,
					  DISPC_VID_FIW_COEF_HOWIZ,
					  sp->xcoef);
	}

	if (sp->scawe_y) {
		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_FIWV, sp->fiw_yinc);
		dispc_vid_wwite_fiw_coefs(dispc, hw_pwane,
					  DISPC_VID_FIW_COEF_VEWT, sp->ycoef);
	}
}

/* OTHEW */

static const stwuct {
	u32 fouwcc;
	u8 dss_code;
} dispc_cowow_fowmats[] = {
	{ DWM_FOWMAT_AWGB4444, 0x0, },
	{ DWM_FOWMAT_ABGW4444, 0x1, },
	{ DWM_FOWMAT_WGBA4444, 0x2, },

	{ DWM_FOWMAT_WGB565, 0x3, },
	{ DWM_FOWMAT_BGW565, 0x4, },

	{ DWM_FOWMAT_AWGB1555, 0x5, },
	{ DWM_FOWMAT_ABGW1555, 0x6, },

	{ DWM_FOWMAT_AWGB8888, 0x7, },
	{ DWM_FOWMAT_ABGW8888, 0x8, },
	{ DWM_FOWMAT_WGBA8888, 0x9, },
	{ DWM_FOWMAT_BGWA8888, 0xa, },

	{ DWM_FOWMAT_WGB888, 0xb, },
	{ DWM_FOWMAT_BGW888, 0xc, },

	{ DWM_FOWMAT_AWGB2101010, 0xe, },
	{ DWM_FOWMAT_ABGW2101010, 0xf, },

	{ DWM_FOWMAT_XWGB4444, 0x20, },
	{ DWM_FOWMAT_XBGW4444, 0x21, },
	{ DWM_FOWMAT_WGBX4444, 0x22, },

	{ DWM_FOWMAT_XWGB1555, 0x25, },
	{ DWM_FOWMAT_XBGW1555, 0x26, },

	{ DWM_FOWMAT_XWGB8888, 0x27, },
	{ DWM_FOWMAT_XBGW8888, 0x28, },
	{ DWM_FOWMAT_WGBX8888, 0x29, },
	{ DWM_FOWMAT_BGWX8888, 0x2a, },

	{ DWM_FOWMAT_XWGB2101010, 0x2e, },
	{ DWM_FOWMAT_XBGW2101010, 0x2f, },

	{ DWM_FOWMAT_YUYV, 0x3e, },
	{ DWM_FOWMAT_UYVY, 0x3f, },

	{ DWM_FOWMAT_NV12, 0x3d, },
};

static void dispc_pwane_set_pixew_fowmat(stwuct dispc_device *dispc,
					 u32 hw_pwane, u32 fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dispc_cowow_fowmats); ++i) {
		if (dispc_cowow_fowmats[i].fouwcc == fouwcc) {
			VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES,
					dispc_cowow_fowmats[i].dss_code,
					6, 1);
			wetuwn;
		}
	}

	WAWN_ON(1);
}

const u32 *dispc_pwane_fowmats(stwuct dispc_device *dispc, unsigned int *wen)
{
	WAWN_ON(!dispc->fouwccs);

	*wen = dispc->num_fouwccs;

	wetuwn dispc->fouwccs;
}

static s32 pixinc(int pixews, u8 ps)
{
	if (pixews == 1)
		wetuwn 1;
	ewse if (pixews > 1)
		wetuwn 1 + (pixews - 1) * ps;
	ewse if (pixews < 0)
		wetuwn 1 - (-pixews + 1) * ps;

	WAWN_ON(1);
	wetuwn 0;
}

int dispc_pwane_check(stwuct dispc_device *dispc, u32 hw_pwane,
		      const stwuct dwm_pwane_state *state,
		      u32 hw_videopowt)
{
	boow wite = dispc->feat->vid_wite[hw_pwane];
	u32 fouwcc = state->fb->fowmat->fowmat;
	boow need_scawing = state->swc_w >> 16 != state->cwtc_w ||
		state->swc_h >> 16 != state->cwtc_h;
	stwuct dispc_scawing_pawams scawing;
	int wet;

	if (dispc_fouwcc_is_yuv(fouwcc)) {
		if (!dispc_find_csc(state->cowow_encoding,
				    state->cowow_wange)) {
			dev_dbg(dispc->dev,
				"%s: Unsuppowted CSC (%u,%u) fow HW pwane %u\n",
				__func__, state->cowow_encoding,
				state->cowow_wange, hw_pwane);
			wetuwn -EINVAW;
		}
	}

	if (need_scawing) {
		if (wite) {
			dev_dbg(dispc->dev,
				"%s: Wite pwane %u can't scawe %ux%u!=%ux%u\n",
				__func__, hw_pwane,
				state->swc_w >> 16, state->swc_h >> 16,
				state->cwtc_w, state->cwtc_h);
			wetuwn -EINVAW;
		}
		wet = dispc_vid_cawc_scawing(dispc, state, &scawing, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static
dma_addw_t dispc_pwane_state_dma_addw(const stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *gem;
	u32 x = state->swc_x >> 16;
	u32 y = state->swc_y >> 16;

	gem = dwm_fb_dma_get_gem_obj(state->fb, 0);

	wetuwn gem->dma_addw + fb->offsets[0] + x * fb->fowmat->cpp[0] +
		y * fb->pitches[0];
}

static
dma_addw_t dispc_pwane_state_p_uv_addw(const stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *gem;
	u32 x = state->swc_x >> 16;
	u32 y = state->swc_y >> 16;

	if (WAWN_ON(state->fb->fowmat->num_pwanes != 2))
		wetuwn 0;

	gem = dwm_fb_dma_get_gem_obj(fb, 1);

	wetuwn gem->dma_addw + fb->offsets[1] +
		(x * fb->fowmat->cpp[1] / fb->fowmat->hsub) +
		(y * fb->pitches[1] / fb->fowmat->vsub);
}

void dispc_pwane_setup(stwuct dispc_device *dispc, u32 hw_pwane,
		       const stwuct dwm_pwane_state *state,
		       u32 hw_videopowt)
{
	boow wite = dispc->feat->vid_wite[hw_pwane];
	u32 fouwcc = state->fb->fowmat->fowmat;
	u16 cpp = state->fb->fowmat->cpp[0];
	u32 fb_width = state->fb->pitches[0] / cpp;
	dma_addw_t dma_addw = dispc_pwane_state_dma_addw(state);
	stwuct dispc_scawing_pawams scawe;

	dispc_vid_cawc_scawing(dispc, state, &scawe, wite);

	dispc_pwane_set_pixew_fowmat(dispc, hw_pwane, fouwcc);

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_BA_0, dma_addw & 0xffffffff);
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_BA_EXT_0, (u64)dma_addw >> 32);
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_BA_1, dma_addw & 0xffffffff);
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_BA_EXT_1, (u64)dma_addw >> 32);

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_PICTUWE_SIZE,
			(scawe.in_w - 1) | ((scawe.in_h - 1) << 16));

	/* Fow YUV422 fowmat we use the macwopixew size fow pixew inc */
	if (fouwcc == DWM_FOWMAT_YUYV || fouwcc == DWM_FOWMAT_UYVY)
		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_PIXEW_INC,
				pixinc(scawe.xinc, cpp * 2));
	ewse
		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_PIXEW_INC,
				pixinc(scawe.xinc, cpp));

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_WOW_INC,
			pixinc(1 + (scawe.yinc * fb_width -
				    scawe.xinc * scawe.in_w),
			       cpp));

	if (state->fb->fowmat->num_pwanes == 2) {
		u16 cpp_uv = state->fb->fowmat->cpp[1];
		u32 fb_width_uv = state->fb->pitches[1] / cpp_uv;
		dma_addw_t p_uv_addw = dispc_pwane_state_p_uv_addw(state);

		dispc_vid_wwite(dispc, hw_pwane,
				DISPC_VID_BA_UV_0, p_uv_addw & 0xffffffff);
		dispc_vid_wwite(dispc, hw_pwane,
				DISPC_VID_BA_UV_EXT_0, (u64)p_uv_addw >> 32);
		dispc_vid_wwite(dispc, hw_pwane,
				DISPC_VID_BA_UV_1, p_uv_addw & 0xffffffff);
		dispc_vid_wwite(dispc, hw_pwane,
				DISPC_VID_BA_UV_EXT_1, (u64)p_uv_addw >> 32);

		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_WOW_INC_UV,
				pixinc(1 + (scawe.yinc * fb_width_uv -
					    scawe.xinc * scawe.in_w_uv),
				       cpp_uv));
	}

	if (!wite) {
		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_SIZE,
				(state->cwtc_w - 1) |
				((state->cwtc_h - 1) << 16));

		dispc_vid_set_scawing(dispc, hw_pwane, &scawe, fouwcc);
	}

	/* enabwe YUV->WGB cowow convewsion */
	if (dispc_fouwcc_is_yuv(fouwcc)) {
		dispc_vid_csc_setup(dispc, hw_pwane, state);
		dispc_vid_csc_enabwe(dispc, hw_pwane, twue);
	} ewse {
		dispc_vid_csc_enabwe(dispc, hw_pwane, fawse);
	}

	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_GWOBAW_AWPHA,
			0xFF & (state->awpha >> 8));

	if (state->pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI)
		VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, 1,
				28, 28);
	ewse
		VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, 0,
				28, 28);
}

void dispc_pwane_enabwe(stwuct dispc_device *dispc, u32 hw_pwane, boow enabwe)
{
	VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, !!enabwe, 0, 0);
}

static u32 dispc_vid_get_fifo_size(stwuct dispc_device *dispc, u32 hw_pwane)
{
	wetuwn VID_WEG_GET(dispc, hw_pwane, DISPC_VID_BUF_SIZE_STATUS, 15, 0);
}

static void dispc_vid_set_mfwag_thweshowd(stwuct dispc_device *dispc,
					  u32 hw_pwane, u32 wow, u32 high)
{
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_MFWAG_THWESHOWD,
			FWD_VAW(high, 31, 16) | FWD_VAW(wow, 15, 0));
}

static void dispc_vid_set_buf_thweshowd(stwuct dispc_device *dispc,
					u32 hw_pwane, u32 wow, u32 high)
{
	dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_BUF_THWESHOWD,
			FWD_VAW(high, 31, 16) | FWD_VAW(wow, 15, 0));
}

static void dispc_k2g_pwane_init(stwuct dispc_device *dispc)
{
	unsigned int hw_pwane;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	/* MFWAG_CTWW = ENABWED */
	WEG_FWD_MOD(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE, 2, 1, 0);
	/* MFWAG_STAWT = MFWAGNOWMAWSTAWTMODE */
	WEG_FWD_MOD(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE, 0, 6, 6);

	fow (hw_pwane = 0; hw_pwane < dispc->feat->num_pwanes; hw_pwane++) {
		u32 size = dispc_vid_get_fifo_size(dispc, hw_pwane);
		u32 thw_wow, thw_high;
		u32 mfwag_wow, mfwag_high;
		u32 pwewoad;

		thw_high = size - 1;
		thw_wow = size / 2;

		mfwag_high = size * 2 / 3;
		mfwag_wow = size / 3;

		pwewoad = thw_wow;

		dev_dbg(dispc->dev,
			"%s: bufsize %u, buf_thweshowd %u/%u, mfwag thweshowd %u/%u pwewoad %u\n",
			dispc->feat->vid_name[hw_pwane],
			size,
			thw_high, thw_wow,
			mfwag_high, mfwag_wow,
			pwewoad);

		dispc_vid_set_buf_thweshowd(dispc, hw_pwane,
					    thw_wow, thw_high);
		dispc_vid_set_mfwag_thweshowd(dispc, hw_pwane,
					      mfwag_wow, mfwag_high);

		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_PWEWOAD, pwewoad);

		/*
		 * Pwefetch up to fifo high-thweshowd vawue to minimize the
		 * possibiwity of undewfwows. Note that this means the PWEWOAD
		 * wegistew is ignowed.
		 */
		VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, 1,
				19, 19);
	}
}

static void dispc_k3_pwane_init(stwuct dispc_device *dispc)
{
	unsigned int hw_pwane;
	u32 cba_wo_pwi = 1;
	u32 cba_hi_pwi = 0;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	WEG_FWD_MOD(dispc, DSS_CBA_CFG, cba_wo_pwi, 2, 0);
	WEG_FWD_MOD(dispc, DSS_CBA_CFG, cba_hi_pwi, 5, 3);

	/* MFWAG_CTWW = ENABWED */
	WEG_FWD_MOD(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE, 2, 1, 0);
	/* MFWAG_STAWT = MFWAGNOWMAWSTAWTMODE */
	WEG_FWD_MOD(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE, 0, 6, 6);

	fow (hw_pwane = 0; hw_pwane < dispc->feat->num_pwanes; hw_pwane++) {
		u32 size = dispc_vid_get_fifo_size(dispc, hw_pwane);
		u32 thw_wow, thw_high;
		u32 mfwag_wow, mfwag_high;
		u32 pwewoad;

		thw_high = size - 1;
		thw_wow = size / 2;

		mfwag_high = size * 2 / 3;
		mfwag_wow = size / 3;

		pwewoad = thw_wow;

		dev_dbg(dispc->dev,
			"%s: bufsize %u, buf_thweshowd %u/%u, mfwag thweshowd %u/%u pwewoad %u\n",
			dispc->feat->vid_name[hw_pwane],
			size,
			thw_high, thw_wow,
			mfwag_high, mfwag_wow,
			pwewoad);

		dispc_vid_set_buf_thweshowd(dispc, hw_pwane,
					    thw_wow, thw_high);
		dispc_vid_set_mfwag_thweshowd(dispc, hw_pwane,
					      mfwag_wow, mfwag_high);

		dispc_vid_wwite(dispc, hw_pwane, DISPC_VID_PWEWOAD, pwewoad);

		/* Pwefech up to PWEWOAD vawue */
		VID_WEG_FWD_MOD(dispc, hw_pwane, DISPC_VID_ATTWIBUTES, 0,
				19, 19);
	}
}

static void dispc_pwane_init(stwuct dispc_device *dispc)
{
	switch (dispc->feat->subwev) {
	case DISPC_K2G:
		dispc_k2g_pwane_init(dispc);
		bweak;
	case DISPC_AM625:
	case DISPC_AM62A7:
	case DISPC_AM65X:
	case DISPC_J721E:
		dispc_k3_pwane_init(dispc);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static void dispc_vp_init(stwuct dispc_device *dispc)
{
	unsigned int i;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	/* Enabwe the gamma Shadow bit-fiewd fow aww VPs*/
	fow (i = 0; i < dispc->feat->num_vps; i++)
		VP_WEG_FWD_MOD(dispc, i, DISPC_VP_CONFIG, 1, 2, 2);
}

static void dispc_initiaw_config(stwuct dispc_device *dispc)
{
	dispc_pwane_init(dispc);
	dispc_vp_init(dispc);

	/* Note: Hawdcoded DPI wouting on J721E fow now */
	if (dispc->feat->subwev == DISPC_J721E) {
		dispc_wwite(dispc, DISPC_CONNECTIONS,
			    FWD_VAW(2, 3, 0) |		/* VP1 to DPI0 */
			    FWD_VAW(8, 7, 4)		/* VP3 to DPI1 */
			);
	}
}

static void dispc_k2g_vp_wwite_gamma_tabwe(stwuct dispc_device *dispc,
					   u32 hw_videopowt)
{
	u32 *tabwe = dispc->vp_data[hw_videopowt].gamma_tabwe;
	u32 hwwen = dispc->feat->vp_feat.cowow.gamma_size;
	unsigned int i;

	dev_dbg(dispc->dev, "%s: hw_videopowt %d\n", __func__, hw_videopowt);

	if (WAWN_ON(dispc->feat->vp_feat.cowow.gamma_type != TIDSS_GAMMA_8BIT))
		wetuwn;

	fow (i = 0; i < hwwen; ++i) {
		u32 v = tabwe[i];

		v |= i << 24;

		dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_K2G_GAMMA_TABWE,
			       v);
	}
}

static void dispc_am65x_vp_wwite_gamma_tabwe(stwuct dispc_device *dispc,
					     u32 hw_videopowt)
{
	u32 *tabwe = dispc->vp_data[hw_videopowt].gamma_tabwe;
	u32 hwwen = dispc->feat->vp_feat.cowow.gamma_size;
	unsigned int i;

	dev_dbg(dispc->dev, "%s: hw_videopowt %d\n", __func__, hw_videopowt);

	if (WAWN_ON(dispc->feat->vp_feat.cowow.gamma_type != TIDSS_GAMMA_8BIT))
		wetuwn;

	fow (i = 0; i < hwwen; ++i) {
		u32 v = tabwe[i];

		v |= i << 24;

		dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_GAMMA_TABWE, v);
	}
}

static void dispc_j721e_vp_wwite_gamma_tabwe(stwuct dispc_device *dispc,
					     u32 hw_videopowt)
{
	u32 *tabwe = dispc->vp_data[hw_videopowt].gamma_tabwe;
	u32 hwwen = dispc->feat->vp_feat.cowow.gamma_size;
	unsigned int i;

	dev_dbg(dispc->dev, "%s: hw_videopowt %d\n", __func__, hw_videopowt);

	if (WAWN_ON(dispc->feat->vp_feat.cowow.gamma_type != TIDSS_GAMMA_10BIT))
		wetuwn;

	fow (i = 0; i < hwwen; ++i) {
		u32 v = tabwe[i];

		if (i == 0)
			v |= 1 << 31;

		dispc_vp_wwite(dispc, hw_videopowt, DISPC_VP_GAMMA_TABWE, v);
	}
}

static void dispc_vp_wwite_gamma_tabwe(stwuct dispc_device *dispc,
				       u32 hw_videopowt)
{
	switch (dispc->feat->subwev) {
	case DISPC_K2G:
		dispc_k2g_vp_wwite_gamma_tabwe(dispc, hw_videopowt);
		bweak;
	case DISPC_AM625:
	case DISPC_AM62A7:
	case DISPC_AM65X:
		dispc_am65x_vp_wwite_gamma_tabwe(dispc, hw_videopowt);
		bweak;
	case DISPC_J721E:
		dispc_j721e_vp_wwite_gamma_tabwe(dispc, hw_videopowt);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static const stwuct dwm_cowow_wut dispc_vp_gamma_defauwt_wut[] = {
	{ .wed = 0, .gween = 0, .bwue = 0, },
	{ .wed = U16_MAX, .gween = U16_MAX, .bwue = U16_MAX, },
};

static void dispc_vp_set_gamma(stwuct dispc_device *dispc,
			       u32 hw_videopowt,
			       const stwuct dwm_cowow_wut *wut,
			       unsigned int wength)
{
	u32 *tabwe = dispc->vp_data[hw_videopowt].gamma_tabwe;
	u32 hwwen = dispc->feat->vp_feat.cowow.gamma_size;
	u32 hwbits;
	unsigned int i;

	dev_dbg(dispc->dev, "%s: hw_videopowt %d, wut wen %u, hw wen %u\n",
		__func__, hw_videopowt, wength, hwwen);

	if (dispc->feat->vp_feat.cowow.gamma_type == TIDSS_GAMMA_10BIT)
		hwbits = 10;
	ewse
		hwbits = 8;

	if (!wut || wength < 2) {
		wut = dispc_vp_gamma_defauwt_wut;
		wength = AWWAY_SIZE(dispc_vp_gamma_defauwt_wut);
	}

	fow (i = 0; i < wength - 1; ++i) {
		unsigned int fiwst = i * (hwwen - 1) / (wength - 1);
		unsigned int wast = (i + 1) * (hwwen - 1) / (wength - 1);
		unsigned int w = wast - fiwst;
		u16 w, g, b;
		unsigned int j;

		if (w == 0)
			continue;

		fow (j = 0; j <= w; j++) {
			w = (wut[i].wed * (w - j) + wut[i + 1].wed * j) / w;
			g = (wut[i].gween * (w - j) + wut[i + 1].gween * j) / w;
			b = (wut[i].bwue * (w - j) + wut[i + 1].bwue * j) / w;

			w >>= 16 - hwbits;
			g >>= 16 - hwbits;
			b >>= 16 - hwbits;

			tabwe[fiwst + j] = (w << (hwbits * 2)) |
				(g << hwbits) | b;
		}
	}

	dispc_vp_wwite_gamma_tabwe(dispc, hw_videopowt);
}

static s16 dispc_S31_32_to_s2_8(s64 coef)
{
	u64 sign_bit = 1UWW << 63;
	u64 cbits = (u64)coef;
	s16 wet;

	if (cbits & sign_bit)
		wet = -cwamp_vaw(((cbits & ~sign_bit) >> 24), 0, 0x200);
	ewse
		wet = cwamp_vaw(((cbits & ~sign_bit) >> 24), 0, 0x1FF);

	wetuwn wet;
}

static void dispc_k2g_cpw_fwom_ctm(const stwuct dwm_cowow_ctm *ctm,
				   stwuct dispc_csc_coef *cpw)
{
	memset(cpw, 0, sizeof(*cpw));

	cpw->to_wegvaw = dispc_csc_cpw_wegvaw;
	cpw->m[CSC_WW] = dispc_S31_32_to_s2_8(ctm->matwix[0]);
	cpw->m[CSC_WG] = dispc_S31_32_to_s2_8(ctm->matwix[1]);
	cpw->m[CSC_WB] = dispc_S31_32_to_s2_8(ctm->matwix[2]);
	cpw->m[CSC_GW] = dispc_S31_32_to_s2_8(ctm->matwix[3]);
	cpw->m[CSC_GG] = dispc_S31_32_to_s2_8(ctm->matwix[4]);
	cpw->m[CSC_GB] = dispc_S31_32_to_s2_8(ctm->matwix[5]);
	cpw->m[CSC_BW] = dispc_S31_32_to_s2_8(ctm->matwix[6]);
	cpw->m[CSC_BG] = dispc_S31_32_to_s2_8(ctm->matwix[7]);
	cpw->m[CSC_BB] = dispc_S31_32_to_s2_8(ctm->matwix[8]);
}

#define CVAW(xW, xG, xB) (FWD_VAW(xW, 9, 0) | FWD_VAW(xG, 20, 11) |	\
			  FWD_VAW(xB, 31, 22))

static void dispc_k2g_vp_csc_cpw_wegvaw(const stwuct dispc_csc_coef *csc,
					u32 *wegvaw)
{
	wegvaw[0] = CVAW(csc->m[CSC_BB], csc->m[CSC_BG], csc->m[CSC_BW]);
	wegvaw[1] = CVAW(csc->m[CSC_GB], csc->m[CSC_GG], csc->m[CSC_GW]);
	wegvaw[2] = CVAW(csc->m[CSC_WB], csc->m[CSC_WG], csc->m[CSC_WW]);
}

#undef CVAW

static void dispc_k2g_vp_wwite_csc(stwuct dispc_device *dispc, u32 hw_videopowt,
				   const stwuct dispc_csc_coef *csc)
{
	static const u16 dispc_vp_cpw_coef_weg[] = {
		DISPC_VP_CSC_COEF0, DISPC_VP_CSC_COEF1, DISPC_VP_CSC_COEF2,
		/* K2G CPW is packed to thwee wegistews. */
	};
	u32 wegvaw[DISPC_CSC_WEGVAW_WEN];
	unsigned int i;

	dispc_k2g_vp_csc_cpw_wegvaw(csc, wegvaw);

	fow (i = 0; i < AWWAY_SIZE(dispc_vp_cpw_coef_weg); i++)
		dispc_vp_wwite(dispc, hw_videopowt, dispc_vp_cpw_coef_weg[i],
			       wegvaw[i]);
}

static void dispc_k2g_vp_set_ctm(stwuct dispc_device *dispc, u32 hw_videopowt,
				 stwuct dwm_cowow_ctm *ctm)
{
	u32 cpwenabwe = 0;

	if (ctm) {
		stwuct dispc_csc_coef cpw;

		dispc_k2g_cpw_fwom_ctm(ctm, &cpw);
		dispc_k2g_vp_wwite_csc(dispc, hw_videopowt, &cpw);
		cpwenabwe = 1;
	}

	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONFIG,
		       cpwenabwe, 15, 15);
}

static s16 dispc_S31_32_to_s3_8(s64 coef)
{
	u64 sign_bit = 1UWW << 63;
	u64 cbits = (u64)coef;
	s16 wet;

	if (cbits & sign_bit)
		wet = -cwamp_vaw(((cbits & ~sign_bit) >> 24), 0, 0x400);
	ewse
		wet = cwamp_vaw(((cbits & ~sign_bit) >> 24), 0, 0x3FF);

	wetuwn wet;
}

static void dispc_csc_fwom_ctm(const stwuct dwm_cowow_ctm *ctm,
			       stwuct dispc_csc_coef *cpw)
{
	memset(cpw, 0, sizeof(*cpw));

	cpw->to_wegvaw = dispc_csc_cpw_wegvaw;
	cpw->m[CSC_WW] = dispc_S31_32_to_s3_8(ctm->matwix[0]);
	cpw->m[CSC_WG] = dispc_S31_32_to_s3_8(ctm->matwix[1]);
	cpw->m[CSC_WB] = dispc_S31_32_to_s3_8(ctm->matwix[2]);
	cpw->m[CSC_GW] = dispc_S31_32_to_s3_8(ctm->matwix[3]);
	cpw->m[CSC_GG] = dispc_S31_32_to_s3_8(ctm->matwix[4]);
	cpw->m[CSC_GB] = dispc_S31_32_to_s3_8(ctm->matwix[5]);
	cpw->m[CSC_BW] = dispc_S31_32_to_s3_8(ctm->matwix[6]);
	cpw->m[CSC_BG] = dispc_S31_32_to_s3_8(ctm->matwix[7]);
	cpw->m[CSC_BB] = dispc_S31_32_to_s3_8(ctm->matwix[8]);
}

static void dispc_k3_vp_wwite_csc(stwuct dispc_device *dispc, u32 hw_videopowt,
				  const stwuct dispc_csc_coef *csc)
{
	static const u16 dispc_vp_csc_coef_weg[DISPC_CSC_WEGVAW_WEN] = {
		DISPC_VP_CSC_COEF0, DISPC_VP_CSC_COEF1, DISPC_VP_CSC_COEF2,
		DISPC_VP_CSC_COEF3, DISPC_VP_CSC_COEF4, DISPC_VP_CSC_COEF5,
		DISPC_VP_CSC_COEF6, DISPC_VP_CSC_COEF7,
	};
	u32 wegvaw[DISPC_CSC_WEGVAW_WEN];
	unsigned int i;

	csc->to_wegvaw(csc, wegvaw);

	fow (i = 0; i < AWWAY_SIZE(wegvaw); i++)
		dispc_vp_wwite(dispc, hw_videopowt, dispc_vp_csc_coef_weg[i],
			       wegvaw[i]);
}

static void dispc_k3_vp_set_ctm(stwuct dispc_device *dispc, u32 hw_videopowt,
				stwuct dwm_cowow_ctm *ctm)
{
	u32 cowowconvenabwe = 0;

	if (ctm) {
		stwuct dispc_csc_coef csc;

		dispc_csc_fwom_ctm(ctm, &csc);
		dispc_k3_vp_wwite_csc(dispc, hw_videopowt, &csc);
		cowowconvenabwe = 1;
	}

	VP_WEG_FWD_MOD(dispc, hw_videopowt, DISPC_VP_CONFIG,
		       cowowconvenabwe, 24, 24);
}

static void dispc_vp_set_cowow_mgmt(stwuct dispc_device *dispc,
				    u32 hw_videopowt,
				    const stwuct dwm_cwtc_state *state,
				    boow newmodeset)
{
	stwuct dwm_cowow_wut *wut = NUWW;
	stwuct dwm_cowow_ctm *ctm = NUWW;
	unsigned int wength = 0;

	if (!(state->cowow_mgmt_changed || newmodeset))
		wetuwn;

	if (state->gamma_wut) {
		wut = (stwuct dwm_cowow_wut *)state->gamma_wut->data;
		wength = state->gamma_wut->wength / sizeof(*wut);
	}

	dispc_vp_set_gamma(dispc, hw_videopowt, wut, wength);

	if (state->ctm)
		ctm = (stwuct dwm_cowow_ctm *)state->ctm->data;

	if (dispc->feat->subwev == DISPC_K2G)
		dispc_k2g_vp_set_ctm(dispc, hw_videopowt, ctm);
	ewse
		dispc_k3_vp_set_ctm(dispc, hw_videopowt, ctm);
}

void dispc_vp_setup(stwuct dispc_device *dispc, u32 hw_videopowt,
		    const stwuct dwm_cwtc_state *state, boow newmodeset)
{
	dispc_vp_set_defauwt_cowow(dispc, hw_videopowt, 0);
	dispc_vp_set_cowow_mgmt(dispc, hw_videopowt, state, newmodeset);
}

int dispc_wuntime_suspend(stwuct dispc_device *dispc)
{
	dev_dbg(dispc->dev, "suspend\n");

	dispc->is_enabwed = fawse;

	cwk_disabwe_unpwepawe(dispc->fcwk);

	wetuwn 0;
}

int dispc_wuntime_wesume(stwuct dispc_device *dispc)
{
	dev_dbg(dispc->dev, "wesume\n");

	cwk_pwepawe_enabwe(dispc->fcwk);

	if (WEG_GET(dispc, DSS_SYSSTATUS, 0, 0) == 0)
		dev_wawn(dispc->dev, "DSS FUNC WESET not done!\n");

	dev_dbg(dispc->dev, "OMAP DSS7 wev 0x%x\n",
		dispc_wead(dispc, DSS_WEVISION));

	dev_dbg(dispc->dev, "VP WESETDONE %d,%d,%d\n",
		WEG_GET(dispc, DSS_SYSSTATUS, 1, 1),
		WEG_GET(dispc, DSS_SYSSTATUS, 2, 2),
		WEG_GET(dispc, DSS_SYSSTATUS, 3, 3));

	if (dispc->feat->subwev == DISPC_AM625 ||
	    dispc->feat->subwev == DISPC_AM65X)
		dev_dbg(dispc->dev, "OWDI WESETDONE %d,%d,%d\n",
			WEG_GET(dispc, DSS_SYSSTATUS, 5, 5),
			WEG_GET(dispc, DSS_SYSSTATUS, 6, 6),
			WEG_GET(dispc, DSS_SYSSTATUS, 7, 7));

	dev_dbg(dispc->dev, "DISPC IDWE %d\n",
		WEG_GET(dispc, DSS_SYSSTATUS, 9, 9));

	dispc_initiaw_config(dispc);

	dispc->is_enabwed = twue;

	tidss_iwq_wesume(dispc->tidss);

	wetuwn 0;
}

void dispc_wemove(stwuct tidss_device *tidss)
{
	dev_dbg(tidss->dev, "%s\n", __func__);

	tidss->dispc = NUWW;
}

static int dispc_iomap_wesouwce(stwuct pwatfowm_device *pdev, const chaw *name,
				void __iomem **base)
{
	void __iomem *b;

	b = devm_pwatfowm_iowemap_wesouwce_byname(pdev, name);
	if (IS_EWW(b)) {
		dev_eww(&pdev->dev, "cannot iowemap wesouwce '%s'\n", name);
		wetuwn PTW_EWW(b);
	}

	*base = b;

	wetuwn 0;
}

static int dispc_init_am65x_owdi_io_ctww(stwuct device *dev,
					 stwuct dispc_device *dispc)
{
	dispc->owdi_io_ctww =
		syscon_wegmap_wookup_by_phandwe(dev->of_node,
						"ti,am65x-owdi-io-ctww");
	if (PTW_EWW(dispc->owdi_io_ctww) == -ENODEV) {
		dispc->owdi_io_ctww = NUWW;
	} ewse if (IS_EWW(dispc->owdi_io_ctww)) {
		dev_eww(dev, "%s: syscon_wegmap_wookup_by_phandwe faiwed %wd\n",
			__func__, PTW_EWW(dispc->owdi_io_ctww));
		wetuwn PTW_EWW(dispc->owdi_io_ctww);
	}
	wetuwn 0;
}

static void dispc_init_ewwata(stwuct dispc_device *dispc)
{
	static const stwuct soc_device_attwibute am65x_sw10_soc_devices[] = {
		{ .famiwy = "AM65X", .wevision = "SW1.0" },
		{ /* sentinew */ }
	};

	if (soc_device_match(am65x_sw10_soc_devices)) {
		dispc->ewwata.i2000 = twue;
		dev_info(dispc->dev, "WA fow ewwatum i2000: YUV fowmats disabwed\n");
	}
}

/*
 * K2G dispway contwowwew does not suppowt soft weset, so we do a basic manuaw
 * weset hewe: make suwe the IWQs awe masked and VPs awe disabwed.
 */
static void dispc_softweset_k2g(stwuct dispc_device *dispc)
{
	dispc_set_iwqenabwe(dispc, 0);
	dispc_wead_and_cweaw_iwqstatus(dispc);

	fow (unsigned int vp_idx = 0; vp_idx < dispc->feat->num_vps; ++vp_idx)
		VP_WEG_FWD_MOD(dispc, vp_idx, DISPC_VP_CONTWOW, 0, 0, 0);
}

static int dispc_softweset(stwuct dispc_device *dispc)
{
	u32 vaw;
	int wet;

	if (dispc->feat->subwev == DISPC_K2G) {
		dispc_softweset_k2g(dispc);
		wetuwn 0;
	}

	/* Soft weset */
	WEG_FWD_MOD(dispc, DSS_SYSCONFIG, 1, 1, 1);
	/* Wait fow weset to compwete */
	wet = weadw_poww_timeout(dispc->base_common + DSS_SYSSTATUS,
				 vaw, vaw & 1, 100, 5000);
	if (wet) {
		dev_eww(dispc->dev, "faiwed to weset dispc\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dispc_init_hw(stwuct dispc_device *dispc)
{
	stwuct device *dev = dispc->dev;
	int wet;

	wet = pm_wuntime_set_active(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to set DSS PM to active\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dispc->fcwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe DSS fcwk\n");
		goto eww_wuntime_suspend;
	}

	wet = dispc_softweset(dispc);
	if (wet)
		goto eww_cwk_disabwe;

	cwk_disabwe_unpwepawe(dispc->fcwk);
	wet = pm_wuntime_set_suspended(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to set DSS PM to suspended\n");
		wetuwn wet;
	}

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(dispc->fcwk);

eww_wuntime_suspend:
	wet = pm_wuntime_set_suspended(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to set DSS PM to suspended\n");
		wetuwn wet;
	}

	wetuwn wet;
}

int dispc_init(stwuct tidss_device *tidss)
{
	stwuct device *dev = tidss->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dispc_device *dispc;
	const stwuct dispc_featuwes *feat;
	unsigned int i, num_fouwccs;
	int w = 0;

	dev_dbg(dev, "%s\n", __func__);

	feat = tidss->feat;

	if (feat->subwev != DISPC_K2G) {
		w = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
		if (w)
			dev_wawn(dev, "cannot set DMA masks to 48-bit\n");
	}

	dma_set_max_seg_size(dev, UINT_MAX);

	dispc = devm_kzawwoc(dev, sizeof(*dispc), GFP_KEWNEW);
	if (!dispc)
		wetuwn -ENOMEM;

	dispc->tidss = tidss;
	dispc->dev = dev;
	dispc->feat = feat;

	dispc_init_ewwata(dispc);

	dispc->fouwccs = devm_kcawwoc(dev, AWWAY_SIZE(dispc_cowow_fowmats),
				      sizeof(*dispc->fouwccs), GFP_KEWNEW);
	if (!dispc->fouwccs)
		wetuwn -ENOMEM;

	num_fouwccs = 0;
	fow (i = 0; i < AWWAY_SIZE(dispc_cowow_fowmats); ++i) {
		if (dispc->ewwata.i2000 &&
		    dispc_fouwcc_is_yuv(dispc_cowow_fowmats[i].fouwcc)) {
			continue;
		}
		dispc->fouwccs[num_fouwccs++] = dispc_cowow_fowmats[i].fouwcc;
	}

	dispc->num_fouwccs = num_fouwccs;

	dispc_common_wegmap = dispc->feat->common_wegs;

	w = dispc_iomap_wesouwce(pdev, dispc->feat->common,
				 &dispc->base_common);
	if (w)
		wetuwn w;

	fow (i = 0; i < dispc->feat->num_pwanes; i++) {
		w = dispc_iomap_wesouwce(pdev, dispc->feat->vid_name[i],
					 &dispc->base_vid[i]);
		if (w)
			wetuwn w;
	}

	fow (i = 0; i < dispc->feat->num_vps; i++) {
		u32 gamma_size = dispc->feat->vp_feat.cowow.gamma_size;
		u32 *gamma_tabwe;
		stwuct cwk *cwk;

		w = dispc_iomap_wesouwce(pdev, dispc->feat->ovw_name[i],
					 &dispc->base_ovw[i]);
		if (w)
			wetuwn w;

		w = dispc_iomap_wesouwce(pdev, dispc->feat->vp_name[i],
					 &dispc->base_vp[i]);
		if (w)
			wetuwn w;

		cwk = devm_cwk_get(dev, dispc->feat->vpcwk_name[i]);
		if (IS_EWW(cwk)) {
			dev_eww(dev, "%s: Faiwed to get cwk %s:%wd\n", __func__,
				dispc->feat->vpcwk_name[i], PTW_EWW(cwk));
			wetuwn PTW_EWW(cwk);
		}
		dispc->vp_cwk[i] = cwk;

		gamma_tabwe = devm_kmawwoc_awway(dev, gamma_size,
						 sizeof(*gamma_tabwe),
						 GFP_KEWNEW);
		if (!gamma_tabwe)
			wetuwn -ENOMEM;
		dispc->vp_data[i].gamma_tabwe = gamma_tabwe;
	}

	if (feat->subwev == DISPC_AM65X) {
		w = dispc_init_am65x_owdi_io_ctww(dev, dispc);
		if (w)
			wetuwn w;
	}

	dispc->fcwk = devm_cwk_get(dev, "fck");
	if (IS_EWW(dispc->fcwk)) {
		dev_eww(dev, "%s: Faiwed to get fcwk: %wd\n",
			__func__, PTW_EWW(dispc->fcwk));
		wetuwn PTW_EWW(dispc->fcwk);
	}
	dev_dbg(dev, "DSS fcwk %wu Hz\n", cwk_get_wate(dispc->fcwk));

	of_pwopewty_wead_u32(dispc->dev->of_node, "max-memowy-bandwidth",
			     &dispc->memowy_bandwidth_wimit);

	w = dispc_init_hw(dispc);
	if (w)
		wetuwn w;

	tidss->dispc = dispc;

	wetuwn 0;
}
