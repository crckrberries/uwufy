// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "DISPC"

#incwude <winux/kewnew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sizes.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/component.h>
#incwude <winux/sys_soc.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_bwend.h>

#incwude "omapdss.h"
#incwude "dss.h"
#incwude "dispc.h"

stwuct dispc_device;

/* DISPC */
#define DISPC_SZ_WEGS			SZ_4K

enum omap_buwst_size {
	BUWST_SIZE_X2 = 0,
	BUWST_SIZE_X4 = 1,
	BUWST_SIZE_X8 = 2,
};

#define WEG_GET(dispc, idx, stawt, end) \
	FWD_GET(dispc_wead_weg(dispc, idx), stawt, end)

#define WEG_FWD_MOD(dispc, idx, vaw, stawt, end)			\
	dispc_wwite_weg(dispc, idx, \
			FWD_MOD(dispc_wead_weg(dispc, idx), vaw, stawt, end))

/* DISPC has featuwe id */
enum dispc_featuwe_id {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_MGW_WCD2,
	FEAT_MGW_WCD3,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	/* Independent cowe cwk dividew */
	FEAT_COWE_CWK_DIV,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	/* An unknown HW bug causing the nowmaw FIFO thweshowds not to wowk */
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_BUWST_2D,
	FEAT_MFWAG,
};

stwuct dispc_featuwes {
	u8 sw_stawt;
	u8 fp_stawt;
	u8 bp_stawt;
	u16 sw_max;
	u16 vp_max;
	u16 hp_max;
	u8 mgw_width_stawt;
	u8 mgw_height_stawt;
	u16 mgw_width_max;
	u16 mgw_height_max;
	u16 ovw_width_max;
	u16 ovw_height_max;
	unsigned wong max_wcd_pcwk;
	unsigned wong max_tv_pcwk;
	unsigned int max_downscawe;
	unsigned int max_wine_width;
	unsigned int min_pcd;
	int (*cawc_scawing)(stwuct dispc_device *dispc,
		unsigned wong pcwk, unsigned wong wcwk,
		const stwuct videomode *vm,
		u16 width, u16 height, u16 out_width, u16 out_height,
		u32 fouwcc, boow *five_taps,
		int *x_pwedecim, int *y_pwedecim, int *decim_x, int *decim_y,
		u16 pos_x, unsigned wong *cowe_cwk, boow mem_to_mem);
	unsigned wong (*cawc_cowe_cwk) (unsigned wong pcwk,
		u16 width, u16 height, u16 out_width, u16 out_height,
		boow mem_to_mem);
	u8 num_fifos;
	const enum dispc_featuwe_id *featuwes;
	unsigned int num_featuwes;
	const stwuct dss_weg_fiewd *weg_fiewds;
	const unsigned int num_weg_fiewds;
	const enum omap_ovewway_caps *ovewway_caps;
	const u32 **suppowted_cowow_modes;
	const u32 *suppowted_scawew_cowow_modes;
	unsigned int num_mgws;
	unsigned int num_ovws;
	unsigned int buffew_size_unit;
	unsigned int buwst_size_unit;

	/* swap GFX & WB fifos */
	boow gfx_fifo_wowkawound:1;

	/* no DISPC_IWQ_FWAMEDONETV on this SoC */
	boow no_fwamedone_tv:1;

	/* wevewt to the OMAP4 mechanism of DISPC Smawt Standby opewation */
	boow mstandby_wowkawound:1;

	boow set_max_pwewoad:1;

	/* PIXEW_INC is not added to the wast pixew of a wine */
	boow wast_pixew_inc_missing:1;

	/* POW_FWEQ has AWIGN bit */
	boow suppowts_sync_awign:1;

	boow has_wwiteback:1;

	boow suppowts_doubwe_pixew:1;

	/*
	 * Fiewd owdew fow VENC is diffewent than HDMI. We shouwd handwe this in
	 * some intewwigent mannew, but as the SoCs have eithew HDMI ow VENC,
	 * nevew both, we can just use this fwag fow now.
	 */
	boow wevewse_iwace_fiewd_owdew:1;

	boow has_gamma_tabwe:1;

	boow has_gamma_i734_bug:1;
};

#define DISPC_MAX_NW_FIFOS 5
#define DISPC_MAX_CHANNEW_GAMMA 4

stwuct dispc_device {
	stwuct pwatfowm_device *pdev;
	void __iomem    *base;
	stwuct dss_device *dss;

	stwuct dss_debugfs_entwy *debugfs;

	int iwq;
	iwq_handwew_t usew_handwew;
	void *usew_data;

	unsigned wong cowe_cwk_wate;
	unsigned wong tv_pcwk_wate;

	u32 fifo_size[DISPC_MAX_NW_FIFOS];
	/* maps which pwane is using a fifo. fifo-id -> pwane-id */
	int fifo_assignment[DISPC_MAX_NW_FIFOS];

	boow		ctx_vawid;
	u32		ctx[DISPC_SZ_WEGS / sizeof(u32)];

	u32 *gamma_tabwe[DISPC_MAX_CHANNEW_GAMMA];

	const stwuct dispc_featuwes *feat;

	boow is_enabwed;

	stwuct wegmap *syscon_pow;
	u32 syscon_pow_offset;
};

enum omap_cowow_component {
	/* used fow aww cowow fowmats fow OMAP3 and eawwiew
	 * and fow WGB and Y cowow component on OMAP4
	 */
	DISPC_COWOW_COMPONENT_WGB_Y		= 1 << 0,
	/* used fow UV component fow
	 * DWM_FOWMAT_YUYV, DWM_FOWMAT_UYVY, DWM_FOWMAT_NV12
	 * cowow fowmats on OMAP4
	 */
	DISPC_COWOW_COMPONENT_UV		= 1 << 1,
};

enum mgw_weg_fiewds {
	DISPC_MGW_FWD_ENABWE,
	DISPC_MGW_FWD_STNTFT,
	DISPC_MGW_FWD_GO,
	DISPC_MGW_FWD_TFTDATAWINES,
	DISPC_MGW_FWD_STAWWMODE,
	DISPC_MGW_FWD_TCKENABWE,
	DISPC_MGW_FWD_TCKSEWECTION,
	DISPC_MGW_FWD_CPW,
	DISPC_MGW_FWD_FIFOHANDCHECK,
	/* used to maintain a count of the above fiewds */
	DISPC_MGW_FWD_NUM,
};

/* DISPC wegistew fiewd id */
enum dispc_feat_weg_fiewd {
	FEAT_WEG_FIWHINC,
	FEAT_WEG_FIWVINC,
	FEAT_WEG_FIFOHIGHTHWESHOWD,
	FEAT_WEG_FIFOWOWTHWESHOWD,
	FEAT_WEG_FIFOSIZE,
	FEAT_WEG_HOWIZONTAWACCU,
	FEAT_WEG_VEWTICAWACCU,
};

stwuct dispc_weg_fiewd {
	u16 weg;
	u8 high;
	u8 wow;
};

stwuct dispc_gamma_desc {
	u32 wen;
	u32 bits;
	u16 weg;
	boow has_index;
};

static const stwuct {
	const chaw *name;
	u32 vsync_iwq;
	u32 fwamedone_iwq;
	u32 sync_wost_iwq;
	stwuct dispc_gamma_desc gamma;
	stwuct dispc_weg_fiewd weg_desc[DISPC_MGW_FWD_NUM];
} mgw_desc[] = {
	[OMAP_DSS_CHANNEW_WCD] = {
		.name		= "WCD",
		.vsync_iwq	= DISPC_IWQ_VSYNC,
		.fwamedone_iwq	= DISPC_IWQ_FWAMEDONE,
		.sync_wost_iwq	= DISPC_IWQ_SYNC_WOST,
		.gamma		= {
			.wen	= 256,
			.bits	= 8,
			.weg	= DISPC_GAMMA_TABWE0,
			.has_index = twue,
		},
		.weg_desc	= {
			[DISPC_MGW_FWD_ENABWE]		= { DISPC_CONTWOW,  0,  0 },
			[DISPC_MGW_FWD_STNTFT]		= { DISPC_CONTWOW,  3,  3 },
			[DISPC_MGW_FWD_GO]		= { DISPC_CONTWOW,  5,  5 },
			[DISPC_MGW_FWD_TFTDATAWINES]	= { DISPC_CONTWOW,  9,  8 },
			[DISPC_MGW_FWD_STAWWMODE]	= { DISPC_CONTWOW, 11, 11 },
			[DISPC_MGW_FWD_TCKENABWE]	= { DISPC_CONFIG,  10, 10 },
			[DISPC_MGW_FWD_TCKSEWECTION]	= { DISPC_CONFIG,  11, 11 },
			[DISPC_MGW_FWD_CPW]		= { DISPC_CONFIG,  15, 15 },
			[DISPC_MGW_FWD_FIFOHANDCHECK]	= { DISPC_CONFIG,  16, 16 },
		},
	},
	[OMAP_DSS_CHANNEW_DIGIT] = {
		.name		= "DIGIT",
		.vsync_iwq	= DISPC_IWQ_EVSYNC_ODD | DISPC_IWQ_EVSYNC_EVEN,
		.fwamedone_iwq	= DISPC_IWQ_FWAMEDONETV,
		.sync_wost_iwq	= DISPC_IWQ_SYNC_WOST_DIGIT,
		.gamma		= {
			.wen	= 1024,
			.bits	= 10,
			.weg	= DISPC_GAMMA_TABWE2,
			.has_index = fawse,
		},
		.weg_desc	= {
			[DISPC_MGW_FWD_ENABWE]		= { DISPC_CONTWOW,  1,  1 },
			[DISPC_MGW_FWD_STNTFT]		= { },
			[DISPC_MGW_FWD_GO]		= { DISPC_CONTWOW,  6,  6 },
			[DISPC_MGW_FWD_TFTDATAWINES]	= { },
			[DISPC_MGW_FWD_STAWWMODE]	= { },
			[DISPC_MGW_FWD_TCKENABWE]	= { DISPC_CONFIG,  12, 12 },
			[DISPC_MGW_FWD_TCKSEWECTION]	= { DISPC_CONFIG,  13, 13 },
			[DISPC_MGW_FWD_CPW]		= { },
			[DISPC_MGW_FWD_FIFOHANDCHECK]	= { DISPC_CONFIG,  16, 16 },
		},
	},
	[OMAP_DSS_CHANNEW_WCD2] = {
		.name		= "WCD2",
		.vsync_iwq	= DISPC_IWQ_VSYNC2,
		.fwamedone_iwq	= DISPC_IWQ_FWAMEDONE2,
		.sync_wost_iwq	= DISPC_IWQ_SYNC_WOST2,
		.gamma		= {
			.wen	= 256,
			.bits	= 8,
			.weg	= DISPC_GAMMA_TABWE1,
			.has_index = twue,
		},
		.weg_desc	= {
			[DISPC_MGW_FWD_ENABWE]		= { DISPC_CONTWOW2,  0,  0 },
			[DISPC_MGW_FWD_STNTFT]		= { DISPC_CONTWOW2,  3,  3 },
			[DISPC_MGW_FWD_GO]		= { DISPC_CONTWOW2,  5,  5 },
			[DISPC_MGW_FWD_TFTDATAWINES]	= { DISPC_CONTWOW2,  9,  8 },
			[DISPC_MGW_FWD_STAWWMODE]	= { DISPC_CONTWOW2, 11, 11 },
			[DISPC_MGW_FWD_TCKENABWE]	= { DISPC_CONFIG2,  10, 10 },
			[DISPC_MGW_FWD_TCKSEWECTION]	= { DISPC_CONFIG2,  11, 11 },
			[DISPC_MGW_FWD_CPW]		= { DISPC_CONFIG2,  15, 15 },
			[DISPC_MGW_FWD_FIFOHANDCHECK]	= { DISPC_CONFIG2,  16, 16 },
		},
	},
	[OMAP_DSS_CHANNEW_WCD3] = {
		.name		= "WCD3",
		.vsync_iwq	= DISPC_IWQ_VSYNC3,
		.fwamedone_iwq	= DISPC_IWQ_FWAMEDONE3,
		.sync_wost_iwq	= DISPC_IWQ_SYNC_WOST3,
		.gamma		= {
			.wen	= 256,
			.bits	= 8,
			.weg	= DISPC_GAMMA_TABWE3,
			.has_index = twue,
		},
		.weg_desc	= {
			[DISPC_MGW_FWD_ENABWE]		= { DISPC_CONTWOW3,  0,  0 },
			[DISPC_MGW_FWD_STNTFT]		= { DISPC_CONTWOW3,  3,  3 },
			[DISPC_MGW_FWD_GO]		= { DISPC_CONTWOW3,  5,  5 },
			[DISPC_MGW_FWD_TFTDATAWINES]	= { DISPC_CONTWOW3,  9,  8 },
			[DISPC_MGW_FWD_STAWWMODE]	= { DISPC_CONTWOW3, 11, 11 },
			[DISPC_MGW_FWD_TCKENABWE]	= { DISPC_CONFIG3,  10, 10 },
			[DISPC_MGW_FWD_TCKSEWECTION]	= { DISPC_CONFIG3,  11, 11 },
			[DISPC_MGW_FWD_CPW]		= { DISPC_CONFIG3,  15, 15 },
			[DISPC_MGW_FWD_FIFOHANDCHECK]	= { DISPC_CONFIG3,  16, 16 },
		},
	},
};

static unsigned wong dispc_fcwk_wate(stwuct dispc_device *dispc);
static unsigned wong dispc_cowe_cwk_wate(stwuct dispc_device *dispc);
static unsigned wong dispc_mgw_wcwk_wate(stwuct dispc_device *dispc,
					 enum omap_channew channew);
static unsigned wong dispc_mgw_pcwk_wate(stwuct dispc_device *dispc,
					 enum omap_channew channew);

static unsigned wong dispc_pwane_pcwk_wate(stwuct dispc_device *dispc,
					   enum omap_pwane_id pwane);
static unsigned wong dispc_pwane_wcwk_wate(stwuct dispc_device *dispc,
					   enum omap_pwane_id pwane);

static inwine void dispc_wwite_weg(stwuct dispc_device *dispc, u16 idx, u32 vaw)
{
	__waw_wwitew(vaw, dispc->base + idx);
}

static inwine u32 dispc_wead_weg(stwuct dispc_device *dispc, u16 idx)
{
	wetuwn __waw_weadw(dispc->base + idx);
}

static u32 mgw_fwd_wead(stwuct dispc_device *dispc, enum omap_channew channew,
			enum mgw_weg_fiewds wegfwd)
{
	const stwuct dispc_weg_fiewd *wfwd = &mgw_desc[channew].weg_desc[wegfwd];

	wetuwn WEG_GET(dispc, wfwd->weg, wfwd->high, wfwd->wow);
}

static void mgw_fwd_wwite(stwuct dispc_device *dispc, enum omap_channew channew,
			  enum mgw_weg_fiewds wegfwd, int vaw)
{
	const stwuct dispc_weg_fiewd *wfwd = &mgw_desc[channew].weg_desc[wegfwd];

	WEG_FWD_MOD(dispc, wfwd->weg, vaw, wfwd->high, wfwd->wow);
}

int dispc_get_num_ovws(stwuct dispc_device *dispc)
{
	wetuwn dispc->feat->num_ovws;
}

int dispc_get_num_mgws(stwuct dispc_device *dispc)
{
	wetuwn dispc->feat->num_mgws;
}

static void dispc_get_weg_fiewd(stwuct dispc_device *dispc,
				enum dispc_feat_weg_fiewd id,
				u8 *stawt, u8 *end)
{
	BUG_ON(id >= dispc->feat->num_weg_fiewds);

	*stawt = dispc->feat->weg_fiewds[id].stawt;
	*end = dispc->feat->weg_fiewds[id].end;
}

static boow dispc_has_featuwe(stwuct dispc_device *dispc,
			      enum dispc_featuwe_id id)
{
	unsigned int i;

	fow (i = 0; i < dispc->feat->num_featuwes; i++) {
		if (dispc->feat->featuwes[i] == id)
			wetuwn twue;
	}

	wetuwn fawse;
}

#define SW(dispc, weg) \
	dispc->ctx[DISPC_##weg / sizeof(u32)] = dispc_wead_weg(dispc, DISPC_##weg)
#define WW(dispc, weg) \
	dispc_wwite_weg(dispc, DISPC_##weg, dispc->ctx[DISPC_##weg / sizeof(u32)])

static void dispc_save_context(stwuct dispc_device *dispc)
{
	int i, j;

	DSSDBG("dispc_save_context\n");

	SW(dispc, IWQENABWE);
	SW(dispc, CONTWOW);
	SW(dispc, CONFIG);
	SW(dispc, WINE_NUMBEW);
	if (dispc_has_featuwe(dispc, FEAT_AWPHA_FIXED_ZOWDEW) ||
			dispc_has_featuwe(dispc, FEAT_AWPHA_FWEE_ZOWDEW))
		SW(dispc, GWOBAW_AWPHA);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2)) {
		SW(dispc, CONTWOW2);
		SW(dispc, CONFIG2);
	}
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3)) {
		SW(dispc, CONTWOW3);
		SW(dispc, CONFIG3);
	}

	fow (i = 0; i < dispc_get_num_mgws(dispc); i++) {
		SW(dispc, DEFAUWT_COWOW(i));
		SW(dispc, TWANS_COWOW(i));
		SW(dispc, SIZE_MGW(i));
		if (i == OMAP_DSS_CHANNEW_DIGIT)
			continue;
		SW(dispc, TIMING_H(i));
		SW(dispc, TIMING_V(i));
		SW(dispc, POW_FWEQ(i));
		SW(dispc, DIVISOWo(i));

		SW(dispc, DATA_CYCWE1(i));
		SW(dispc, DATA_CYCWE2(i));
		SW(dispc, DATA_CYCWE3(i));

		if (dispc_has_featuwe(dispc, FEAT_CPW)) {
			SW(dispc, CPW_COEF_W(i));
			SW(dispc, CPW_COEF_G(i));
			SW(dispc, CPW_COEF_B(i));
		}
	}

	fow (i = 0; i < dispc_get_num_ovws(dispc); i++) {
		SW(dispc, OVW_BA0(i));
		SW(dispc, OVW_BA1(i));
		SW(dispc, OVW_POSITION(i));
		SW(dispc, OVW_SIZE(i));
		SW(dispc, OVW_ATTWIBUTES(i));
		SW(dispc, OVW_FIFO_THWESHOWD(i));
		SW(dispc, OVW_WOW_INC(i));
		SW(dispc, OVW_PIXEW_INC(i));
		if (dispc_has_featuwe(dispc, FEAT_PWEWOAD))
			SW(dispc, OVW_PWEWOAD(i));
		if (i == OMAP_DSS_GFX) {
			SW(dispc, OVW_WINDOW_SKIP(i));
			SW(dispc, OVW_TABWE_BA(i));
			continue;
		}
		SW(dispc, OVW_FIW(i));
		SW(dispc, OVW_PICTUWE_SIZE(i));
		SW(dispc, OVW_ACCU0(i));
		SW(dispc, OVW_ACCU1(i));

		fow (j = 0; j < 8; j++)
			SW(dispc, OVW_FIW_COEF_H(i, j));

		fow (j = 0; j < 8; j++)
			SW(dispc, OVW_FIW_COEF_HV(i, j));

		fow (j = 0; j < 5; j++)
			SW(dispc, OVW_CONV_COEF(i, j));

		if (dispc_has_featuwe(dispc, FEAT_FIW_COEF_V)) {
			fow (j = 0; j < 8; j++)
				SW(dispc, OVW_FIW_COEF_V(i, j));
		}

		if (dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE)) {
			SW(dispc, OVW_BA0_UV(i));
			SW(dispc, OVW_BA1_UV(i));
			SW(dispc, OVW_FIW2(i));
			SW(dispc, OVW_ACCU2_0(i));
			SW(dispc, OVW_ACCU2_1(i));

			fow (j = 0; j < 8; j++)
				SW(dispc, OVW_FIW_COEF_H2(i, j));

			fow (j = 0; j < 8; j++)
				SW(dispc, OVW_FIW_COEF_HV2(i, j));

			fow (j = 0; j < 8; j++)
				SW(dispc, OVW_FIW_COEF_V2(i, j));
		}
		if (dispc_has_featuwe(dispc, FEAT_ATTW2))
			SW(dispc, OVW_ATTWIBUTES2(i));
	}

	if (dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV))
		SW(dispc, DIVISOW);

	dispc->ctx_vawid = twue;

	DSSDBG("context saved\n");
}

static void dispc_westowe_context(stwuct dispc_device *dispc)
{
	int i, j;

	DSSDBG("dispc_westowe_context\n");

	if (!dispc->ctx_vawid)
		wetuwn;

	/*WW(dispc, IWQENABWE);*/
	/*WW(dispc, CONTWOW);*/
	WW(dispc, CONFIG);
	WW(dispc, WINE_NUMBEW);
	if (dispc_has_featuwe(dispc, FEAT_AWPHA_FIXED_ZOWDEW) ||
			dispc_has_featuwe(dispc, FEAT_AWPHA_FWEE_ZOWDEW))
		WW(dispc, GWOBAW_AWPHA);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
		WW(dispc, CONFIG2);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3))
		WW(dispc, CONFIG3);

	fow (i = 0; i < dispc_get_num_mgws(dispc); i++) {
		WW(dispc, DEFAUWT_COWOW(i));
		WW(dispc, TWANS_COWOW(i));
		WW(dispc, SIZE_MGW(i));
		if (i == OMAP_DSS_CHANNEW_DIGIT)
			continue;
		WW(dispc, TIMING_H(i));
		WW(dispc, TIMING_V(i));
		WW(dispc, POW_FWEQ(i));
		WW(dispc, DIVISOWo(i));

		WW(dispc, DATA_CYCWE1(i));
		WW(dispc, DATA_CYCWE2(i));
		WW(dispc, DATA_CYCWE3(i));

		if (dispc_has_featuwe(dispc, FEAT_CPW)) {
			WW(dispc, CPW_COEF_W(i));
			WW(dispc, CPW_COEF_G(i));
			WW(dispc, CPW_COEF_B(i));
		}
	}

	fow (i = 0; i < dispc_get_num_ovws(dispc); i++) {
		WW(dispc, OVW_BA0(i));
		WW(dispc, OVW_BA1(i));
		WW(dispc, OVW_POSITION(i));
		WW(dispc, OVW_SIZE(i));
		WW(dispc, OVW_ATTWIBUTES(i));
		WW(dispc, OVW_FIFO_THWESHOWD(i));
		WW(dispc, OVW_WOW_INC(i));
		WW(dispc, OVW_PIXEW_INC(i));
		if (dispc_has_featuwe(dispc, FEAT_PWEWOAD))
			WW(dispc, OVW_PWEWOAD(i));
		if (i == OMAP_DSS_GFX) {
			WW(dispc, OVW_WINDOW_SKIP(i));
			WW(dispc, OVW_TABWE_BA(i));
			continue;
		}
		WW(dispc, OVW_FIW(i));
		WW(dispc, OVW_PICTUWE_SIZE(i));
		WW(dispc, OVW_ACCU0(i));
		WW(dispc, OVW_ACCU1(i));

		fow (j = 0; j < 8; j++)
			WW(dispc, OVW_FIW_COEF_H(i, j));

		fow (j = 0; j < 8; j++)
			WW(dispc, OVW_FIW_COEF_HV(i, j));

		fow (j = 0; j < 5; j++)
			WW(dispc, OVW_CONV_COEF(i, j));

		if (dispc_has_featuwe(dispc, FEAT_FIW_COEF_V)) {
			fow (j = 0; j < 8; j++)
				WW(dispc, OVW_FIW_COEF_V(i, j));
		}

		if (dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE)) {
			WW(dispc, OVW_BA0_UV(i));
			WW(dispc, OVW_BA1_UV(i));
			WW(dispc, OVW_FIW2(i));
			WW(dispc, OVW_ACCU2_0(i));
			WW(dispc, OVW_ACCU2_1(i));

			fow (j = 0; j < 8; j++)
				WW(dispc, OVW_FIW_COEF_H2(i, j));

			fow (j = 0; j < 8; j++)
				WW(dispc, OVW_FIW_COEF_HV2(i, j));

			fow (j = 0; j < 8; j++)
				WW(dispc, OVW_FIW_COEF_V2(i, j));
		}
		if (dispc_has_featuwe(dispc, FEAT_ATTW2))
			WW(dispc, OVW_ATTWIBUTES2(i));
	}

	if (dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV))
		WW(dispc, DIVISOW);

	/* enabwe wast, because WCD & DIGIT enabwe awe hewe */
	WW(dispc, CONTWOW);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
		WW(dispc, CONTWOW2);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3))
		WW(dispc, CONTWOW3);
	/* cweaw spuwious SYNC_WOST_DIGIT intewwupts */
	dispc_cweaw_iwqstatus(dispc, DISPC_IWQ_SYNC_WOST_DIGIT);

	/*
	 * enabwe wast so IWQs won't twiggew befowe
	 * the context is fuwwy westowed
	 */
	WW(dispc, IWQENABWE);

	DSSDBG("context westowed\n");
}

#undef SW
#undef WW

int dispc_wuntime_get(stwuct dispc_device *dispc)
{
	int w;

	DSSDBG("dispc_wuntime_get\n");

	w = pm_wuntime_get_sync(&dispc->pdev->dev);
	if (WAWN_ON(w < 0)) {
		pm_wuntime_put_noidwe(&dispc->pdev->dev);
		wetuwn w;
	}
	wetuwn 0;
}

void dispc_wuntime_put(stwuct dispc_device *dispc)
{
	int w;

	DSSDBG("dispc_wuntime_put\n");

	w = pm_wuntime_put_sync(&dispc->pdev->dev);
	WAWN_ON(w < 0 && w != -ENOSYS);
}

u32 dispc_mgw_get_vsync_iwq(stwuct dispc_device *dispc,
				   enum omap_channew channew)
{
	wetuwn mgw_desc[channew].vsync_iwq;
}

u32 dispc_mgw_get_fwamedone_iwq(stwuct dispc_device *dispc,
				       enum omap_channew channew)
{
	if (channew == OMAP_DSS_CHANNEW_DIGIT && dispc->feat->no_fwamedone_tv)
		wetuwn 0;

	wetuwn mgw_desc[channew].fwamedone_iwq;
}

u32 dispc_mgw_get_sync_wost_iwq(stwuct dispc_device *dispc,
				       enum omap_channew channew)
{
	wetuwn mgw_desc[channew].sync_wost_iwq;
}

u32 dispc_wb_get_fwamedone_iwq(stwuct dispc_device *dispc)
{
	wetuwn DISPC_IWQ_FWAMEDONEWB;
}

void dispc_mgw_enabwe(stwuct dispc_device *dispc,
			     enum omap_channew channew, boow enabwe)
{
	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_ENABWE, enabwe);
	/* fwush posted wwite */
	mgw_fwd_wead(dispc, channew, DISPC_MGW_FWD_ENABWE);
}

static boow dispc_mgw_is_enabwed(stwuct dispc_device *dispc,
				 enum omap_channew channew)
{
	wetuwn !!mgw_fwd_wead(dispc, channew, DISPC_MGW_FWD_ENABWE);
}

boow dispc_mgw_go_busy(stwuct dispc_device *dispc,
			      enum omap_channew channew)
{
	wetuwn mgw_fwd_wead(dispc, channew, DISPC_MGW_FWD_GO) == 1;
}

void dispc_mgw_go(stwuct dispc_device *dispc, enum omap_channew channew)
{
	WAWN_ON(!dispc_mgw_is_enabwed(dispc, channew));
	WAWN_ON(dispc_mgw_go_busy(dispc, channew));

	DSSDBG("GO %s\n", mgw_desc[channew].name);

	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_GO, 1);
}

boow dispc_wb_go_busy(stwuct dispc_device *dispc)
{
	wetuwn WEG_GET(dispc, DISPC_CONTWOW2, 6, 6) == 1;
}

void dispc_wb_go(stwuct dispc_device *dispc)
{
	enum omap_pwane_id pwane = OMAP_DSS_WB;
	boow enabwe, go;

	enabwe = WEG_GET(dispc, DISPC_OVW_ATTWIBUTES(pwane), 0, 0) == 1;

	if (!enabwe)
		wetuwn;

	go = WEG_GET(dispc, DISPC_CONTWOW2, 6, 6) == 1;
	if (go) {
		DSSEWW("GO bit not down fow WB\n");
		wetuwn;
	}

	WEG_FWD_MOD(dispc, DISPC_CONTWOW2, 1, 6, 6);
}

static void dispc_ovw_wwite_fiwh_weg(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane, int weg,
				     u32 vawue)
{
	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_H(pwane, weg), vawue);
}

static void dispc_ovw_wwite_fiwhv_weg(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int weg,
				      u32 vawue)
{
	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_HV(pwane, weg), vawue);
}

static void dispc_ovw_wwite_fiwv_weg(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane, int weg,
				     u32 vawue)
{
	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_V(pwane, weg), vawue);
}

static void dispc_ovw_wwite_fiwh2_weg(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int weg,
				      u32 vawue)
{
	BUG_ON(pwane == OMAP_DSS_GFX);

	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_H2(pwane, weg), vawue);
}

static void dispc_ovw_wwite_fiwhv2_weg(stwuct dispc_device *dispc,
				       enum omap_pwane_id pwane, int weg,
				       u32 vawue)
{
	BUG_ON(pwane == OMAP_DSS_GFX);

	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_HV2(pwane, weg), vawue);
}

static void dispc_ovw_wwite_fiwv2_weg(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int weg,
				      u32 vawue)
{
	BUG_ON(pwane == OMAP_DSS_GFX);

	dispc_wwite_weg(dispc, DISPC_OVW_FIW_COEF_V2(pwane, weg), vawue);
}

static void dispc_ovw_set_scawe_coef(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane, int fiw_hinc,
				     int fiw_vinc, int five_taps,
				     enum omap_cowow_component cowow_comp)
{
	const stwuct dispc_coef *h_coef, *v_coef;
	int i;

	h_coef = dispc_ovw_get_scawe_coef(fiw_hinc, twue);
	v_coef = dispc_ovw_get_scawe_coef(fiw_vinc, five_taps);

	if (!h_coef || !v_coef) {
		dev_eww(&dispc->pdev->dev, "%s: faiwed to find scawe coefs\n",
			__func__);
		wetuwn;
	}

	fow (i = 0; i < 8; i++) {
		u32 h, hv;

		h = FWD_VAW(h_coef[i].hc0_vc00, 7, 0)
			| FWD_VAW(h_coef[i].hc1_vc0, 15, 8)
			| FWD_VAW(h_coef[i].hc2_vc1, 23, 16)
			| FWD_VAW(h_coef[i].hc3_vc2, 31, 24);
		hv = FWD_VAW(h_coef[i].hc4_vc22, 7, 0)
			| FWD_VAW(v_coef[i].hc1_vc0, 15, 8)
			| FWD_VAW(v_coef[i].hc2_vc1, 23, 16)
			| FWD_VAW(v_coef[i].hc3_vc2, 31, 24);

		if (cowow_comp == DISPC_COWOW_COMPONENT_WGB_Y) {
			dispc_ovw_wwite_fiwh_weg(dispc, pwane, i, h);
			dispc_ovw_wwite_fiwhv_weg(dispc, pwane, i, hv);
		} ewse {
			dispc_ovw_wwite_fiwh2_weg(dispc, pwane, i, h);
			dispc_ovw_wwite_fiwhv2_weg(dispc, pwane, i, hv);
		}

	}

	if (five_taps) {
		fow (i = 0; i < 8; i++) {
			u32 v;
			v = FWD_VAW(v_coef[i].hc0_vc00, 7, 0)
				| FWD_VAW(v_coef[i].hc4_vc22, 15, 8);
			if (cowow_comp == DISPC_COWOW_COMPONENT_WGB_Y)
				dispc_ovw_wwite_fiwv_weg(dispc, pwane, i, v);
			ewse
				dispc_ovw_wwite_fiwv2_weg(dispc, pwane, i, v);
		}
	}
}

stwuct csc_coef_yuv2wgb {
	int wy, wcb, wcw, gy, gcb, gcw, by, bcb, bcw;
	boow fuww_wange;
};

static void dispc_ovw_wwite_cowow_conv_coef(stwuct dispc_device *dispc,
					    enum omap_pwane_id pwane,
					    const stwuct csc_coef_yuv2wgb *ct)
{
#define CVAW(x, y) (FWD_VAW(x, 26, 16) | FWD_VAW(y, 10, 0))

	dispc_wwite_weg(dispc, DISPC_OVW_CONV_COEF(pwane, 0), CVAW(ct->wcw, ct->wy));
	dispc_wwite_weg(dispc, DISPC_OVW_CONV_COEF(pwane, 1), CVAW(ct->gy,  ct->wcb));
	dispc_wwite_weg(dispc, DISPC_OVW_CONV_COEF(pwane, 2), CVAW(ct->gcb, ct->gcw));
	dispc_wwite_weg(dispc, DISPC_OVW_CONV_COEF(pwane, 3), CVAW(ct->bcw, ct->by));
	dispc_wwite_weg(dispc, DISPC_OVW_CONV_COEF(pwane, 4), CVAW(0, ct->bcb));

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), ct->fuww_wange, 11, 11);

#undef CVAW
}

/* YUV -> WGB, ITU-W BT.601, fuww wange */
static const stwuct csc_coef_yuv2wgb coefs_yuv2wgb_bt601_fuww = {
	256,   0,  358,		/* wy, wcb, wcw |1.000  0.000  1.402|*/
	256, -88, -182,		/* gy, gcb, gcw |1.000 -0.344 -0.714|*/
	256, 452,    0,		/* by, bcb, bcw |1.000  1.772  0.000|*/
	twue,			/* fuww wange */
};

/* YUV -> WGB, ITU-W BT.601, wimited wange */
static const stwuct csc_coef_yuv2wgb coefs_yuv2wgb_bt601_wim = {
	298,    0,  409,	/* wy, wcb, wcw |1.164  0.000  1.596|*/
	298, -100, -208,	/* gy, gcb, gcw |1.164 -0.392 -0.813|*/
	298,  516,    0,	/* by, bcb, bcw |1.164  2.017  0.000|*/
	fawse,			/* wimited wange */
};

/* YUV -> WGB, ITU-W BT.709, fuww wange */
static const stwuct csc_coef_yuv2wgb coefs_yuv2wgb_bt709_fuww = {
	256,    0,  402,        /* wy, wcb, wcw |1.000  0.000  1.570|*/
	256,  -48, -120,        /* gy, gcb, gcw |1.000 -0.187 -0.467|*/
	256,  475,    0,        /* by, bcb, bcw |1.000  1.856  0.000|*/
	twue,                   /* fuww wange */
};

/* YUV -> WGB, ITU-W BT.709, wimited wange */
static const stwuct csc_coef_yuv2wgb coefs_yuv2wgb_bt709_wim = {
	298,    0,  459,	/* wy, wcb, wcw |1.164  0.000  1.793|*/
	298,  -55, -136,	/* gy, gcb, gcw |1.164 -0.213 -0.533|*/
	298,  541,    0,	/* by, bcb, bcw |1.164  2.112  0.000|*/
	fawse,			/* wimited wange */
};

static void dispc_ovw_set_csc(stwuct dispc_device *dispc,
			      enum omap_pwane_id pwane,
			      enum dwm_cowow_encoding cowow_encoding,
			      enum dwm_cowow_wange cowow_wange)
{
	const stwuct csc_coef_yuv2wgb *csc;

	switch (cowow_encoding) {
	defauwt:
	case DWM_COWOW_YCBCW_BT601:
		if (cowow_wange == DWM_COWOW_YCBCW_FUWW_WANGE)
			csc = &coefs_yuv2wgb_bt601_fuww;
		ewse
			csc = &coefs_yuv2wgb_bt601_wim;
		bweak;
	case DWM_COWOW_YCBCW_BT709:
		if (cowow_wange == DWM_COWOW_YCBCW_FUWW_WANGE)
			csc = &coefs_yuv2wgb_bt709_fuww;
		ewse
			csc = &coefs_yuv2wgb_bt709_wim;
		bweak;
	}

	dispc_ovw_wwite_cowow_conv_coef(dispc, pwane, csc);
}

static void dispc_ovw_set_ba0(stwuct dispc_device *dispc,
			      enum omap_pwane_id pwane, u32 paddw)
{
	dispc_wwite_weg(dispc, DISPC_OVW_BA0(pwane), paddw);
}

static void dispc_ovw_set_ba1(stwuct dispc_device *dispc,
			      enum omap_pwane_id pwane, u32 paddw)
{
	dispc_wwite_weg(dispc, DISPC_OVW_BA1(pwane), paddw);
}

static void dispc_ovw_set_ba0_uv(stwuct dispc_device *dispc,
				 enum omap_pwane_id pwane, u32 paddw)
{
	dispc_wwite_weg(dispc, DISPC_OVW_BA0_UV(pwane), paddw);
}

static void dispc_ovw_set_ba1_uv(stwuct dispc_device *dispc,
				 enum omap_pwane_id pwane, u32 paddw)
{
	dispc_wwite_weg(dispc, DISPC_OVW_BA1_UV(pwane), paddw);
}

static void dispc_ovw_set_pos(stwuct dispc_device *dispc,
			      enum omap_pwane_id pwane,
			      enum omap_ovewway_caps caps, int x, int y)
{
	u32 vaw;

	if ((caps & OMAP_DSS_OVW_CAP_POS) == 0)
		wetuwn;

	vaw = FWD_VAW(y, 26, 16) | FWD_VAW(x, 10, 0);

	dispc_wwite_weg(dispc, DISPC_OVW_POSITION(pwane), vaw);
}

static void dispc_ovw_set_input_size(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane, int width,
				     int height)
{
	u32 vaw = FWD_VAW(height - 1, 26, 16) | FWD_VAW(width - 1, 10, 0);

	if (pwane == OMAP_DSS_GFX || pwane == OMAP_DSS_WB)
		dispc_wwite_weg(dispc, DISPC_OVW_SIZE(pwane), vaw);
	ewse
		dispc_wwite_weg(dispc, DISPC_OVW_PICTUWE_SIZE(pwane), vaw);
}

static void dispc_ovw_set_output_size(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int width,
				      int height)
{
	u32 vaw;

	BUG_ON(pwane == OMAP_DSS_GFX);

	vaw = FWD_VAW(height - 1, 26, 16) | FWD_VAW(width - 1, 10, 0);

	if (pwane == OMAP_DSS_WB)
		dispc_wwite_weg(dispc, DISPC_OVW_PICTUWE_SIZE(pwane), vaw);
	ewse
		dispc_wwite_weg(dispc, DISPC_OVW_SIZE(pwane), vaw);
}

static void dispc_ovw_set_zowdew(stwuct dispc_device *dispc,
				 enum omap_pwane_id pwane,
				 enum omap_ovewway_caps caps, u8 zowdew)
{
	if ((caps & OMAP_DSS_OVW_CAP_ZOWDEW) == 0)
		wetuwn;

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), zowdew, 27, 26);
}

static void dispc_ovw_enabwe_zowdew_pwanes(stwuct dispc_device *dispc)
{
	int i;

	if (!dispc_has_featuwe(dispc, FEAT_AWPHA_FWEE_ZOWDEW))
		wetuwn;

	fow (i = 0; i < dispc_get_num_ovws(dispc); i++)
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(i), 1, 25, 25);
}

static void dispc_ovw_set_pwe_muwt_awpha(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane,
					 enum omap_ovewway_caps caps,
					 boow enabwe)
{
	if ((caps & OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA) == 0)
		wetuwn;

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), enabwe ? 1 : 0, 28, 28);
}

static void dispc_ovw_setup_gwobaw_awpha(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane,
					 enum omap_ovewway_caps caps,
					 u8 gwobaw_awpha)
{
	static const unsigned int shifts[] = { 0, 8, 16, 24, };
	int shift;

	if ((caps & OMAP_DSS_OVW_CAP_GWOBAW_AWPHA) == 0)
		wetuwn;

	shift = shifts[pwane];
	WEG_FWD_MOD(dispc, DISPC_GWOBAW_AWPHA, gwobaw_awpha, shift + 7, shift);
}

static void dispc_ovw_set_pix_inc(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane, s32 inc)
{
	dispc_wwite_weg(dispc, DISPC_OVW_PIXEW_INC(pwane), inc);
}

static void dispc_ovw_set_wow_inc(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane, s32 inc)
{
	dispc_wwite_weg(dispc, DISPC_OVW_WOW_INC(pwane), inc);
}

static void dispc_ovw_set_cowow_mode(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane, u32 fouwcc)
{
	u32 m = 0;
	if (pwane != OMAP_DSS_GFX) {
		switch (fouwcc) {
		case DWM_FOWMAT_NV12:
			m = 0x0; bweak;
		case DWM_FOWMAT_XWGB4444:
			m = 0x1; bweak;
		case DWM_FOWMAT_WGBA4444:
			m = 0x2; bweak;
		case DWM_FOWMAT_WGBX4444:
			m = 0x4; bweak;
		case DWM_FOWMAT_AWGB4444:
			m = 0x5; bweak;
		case DWM_FOWMAT_WGB565:
			m = 0x6; bweak;
		case DWM_FOWMAT_AWGB1555:
			m = 0x7; bweak;
		case DWM_FOWMAT_XWGB8888:
			m = 0x8; bweak;
		case DWM_FOWMAT_WGB888:
			m = 0x9; bweak;
		case DWM_FOWMAT_YUYV:
			m = 0xa; bweak;
		case DWM_FOWMAT_UYVY:
			m = 0xb; bweak;
		case DWM_FOWMAT_AWGB8888:
			m = 0xc; bweak;
		case DWM_FOWMAT_WGBA8888:
			m = 0xd; bweak;
		case DWM_FOWMAT_WGBX8888:
			m = 0xe; bweak;
		case DWM_FOWMAT_XWGB1555:
			m = 0xf; bweak;
		defauwt:
			BUG(); wetuwn;
		}
	} ewse {
		switch (fouwcc) {
		case DWM_FOWMAT_WGBX4444:
			m = 0x4; bweak;
		case DWM_FOWMAT_AWGB4444:
			m = 0x5; bweak;
		case DWM_FOWMAT_WGB565:
			m = 0x6; bweak;
		case DWM_FOWMAT_AWGB1555:
			m = 0x7; bweak;
		case DWM_FOWMAT_XWGB8888:
			m = 0x8; bweak;
		case DWM_FOWMAT_WGB888:
			m = 0x9; bweak;
		case DWM_FOWMAT_XWGB4444:
			m = 0xa; bweak;
		case DWM_FOWMAT_WGBA4444:
			m = 0xb; bweak;
		case DWM_FOWMAT_AWGB8888:
			m = 0xc; bweak;
		case DWM_FOWMAT_WGBA8888:
			m = 0xd; bweak;
		case DWM_FOWMAT_WGBX8888:
			m = 0xe; bweak;
		case DWM_FOWMAT_XWGB1555:
			m = 0xf; bweak;
		defauwt:
			BUG(); wetuwn;
		}
	}

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), m, 4, 1);
}

static void dispc_ovw_configuwe_buwst_type(stwuct dispc_device *dispc,
					   enum omap_pwane_id pwane,
					   enum omap_dss_wotation_type wotation)
{
	if (dispc_has_featuwe(dispc, FEAT_BUWST_2D) == 0)
		wetuwn;

	if (wotation == OMAP_DSS_WOT_TIWEW)
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), 1, 29, 29);
	ewse
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), 0, 29, 29);
}

static void dispc_ovw_set_channew_out(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane,
				      enum omap_channew channew)
{
	int shift;
	u32 vaw;
	int chan = 0, chan2 = 0;

	switch (pwane) {
	case OMAP_DSS_GFX:
		shift = 8;
		bweak;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
		shift = 16;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	vaw = dispc_wead_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane));
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2)) {
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
			chan = 0;
			chan2 = 0;
			bweak;
		case OMAP_DSS_CHANNEW_DIGIT:
			chan = 1;
			chan2 = 0;
			bweak;
		case OMAP_DSS_CHANNEW_WCD2:
			chan = 0;
			chan2 = 1;
			bweak;
		case OMAP_DSS_CHANNEW_WCD3:
			if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3)) {
				chan = 0;
				chan2 = 2;
			} ewse {
				BUG();
				wetuwn;
			}
			bweak;
		case OMAP_DSS_CHANNEW_WB:
			chan = 0;
			chan2 = 3;
			bweak;
		defauwt:
			BUG();
			wetuwn;
		}

		vaw = FWD_MOD(vaw, chan, shift, shift);
		vaw = FWD_MOD(vaw, chan2, 31, 30);
	} ewse {
		vaw = FWD_MOD(vaw, channew, shift, shift);
	}
	dispc_wwite_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane), vaw);
}

static enum omap_channew dispc_ovw_get_channew_out(stwuct dispc_device *dispc,
						   enum omap_pwane_id pwane)
{
	int shift;
	u32 vaw;

	switch (pwane) {
	case OMAP_DSS_GFX:
		shift = 8;
		bweak;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
		shift = 16;
		bweak;
	defauwt:
		BUG();
		wetuwn 0;
	}

	vaw = dispc_wead_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane));

	if (FWD_GET(vaw, shift, shift) == 1)
		wetuwn OMAP_DSS_CHANNEW_DIGIT;

	if (!dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
		wetuwn OMAP_DSS_CHANNEW_WCD;

	switch (FWD_GET(vaw, 31, 30)) {
	case 0:
	defauwt:
		wetuwn OMAP_DSS_CHANNEW_WCD;
	case 1:
		wetuwn OMAP_DSS_CHANNEW_WCD2;
	case 2:
		wetuwn OMAP_DSS_CHANNEW_WCD3;
	case 3:
		wetuwn OMAP_DSS_CHANNEW_WB;
	}
}

static void dispc_ovw_set_buwst_size(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane,
				     enum omap_buwst_size buwst_size)
{
	static const unsigned int shifts[] = { 6, 14, 14, 14, 14, };
	int shift;

	shift = shifts[pwane];
	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), buwst_size,
		    shift + 1, shift);
}

static void dispc_configuwe_buwst_sizes(stwuct dispc_device *dispc)
{
	int i;
	const int buwst_size = BUWST_SIZE_X8;

	/* Configuwe buwst size awways to maximum size */
	fow (i = 0; i < dispc_get_num_ovws(dispc); ++i)
		dispc_ovw_set_buwst_size(dispc, i, buwst_size);
	if (dispc->feat->has_wwiteback)
		dispc_ovw_set_buwst_size(dispc, OMAP_DSS_WB, buwst_size);
}

static u32 dispc_ovw_get_buwst_size(stwuct dispc_device *dispc,
				    enum omap_pwane_id pwane)
{
	/* buwst muwtipwiew is awways x8 (see dispc_configuwe_buwst_sizes()) */
	wetuwn dispc->feat->buwst_size_unit * 8;
}

boow dispc_ovw_cowow_mode_suppowted(stwuct dispc_device *dispc,
				    enum omap_pwane_id pwane, u32 fouwcc)
{
	const u32 *modes;
	unsigned int i;

	modes = dispc->feat->suppowted_cowow_modes[pwane];

	fow (i = 0; modes[i]; ++i) {
		if (modes[i] == fouwcc)
			wetuwn twue;
	}

	wetuwn fawse;
}

const u32 *dispc_ovw_get_cowow_modes(stwuct dispc_device *dispc,
					    enum omap_pwane_id pwane)
{
	wetuwn dispc->feat->suppowted_cowow_modes[pwane];
}

static void dispc_mgw_enabwe_cpw(stwuct dispc_device *dispc,
				 enum omap_channew channew, boow enabwe)
{
	if (channew == OMAP_DSS_CHANNEW_DIGIT)
		wetuwn;

	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_CPW, enabwe);
}

static void dispc_mgw_set_cpw_coef(stwuct dispc_device *dispc,
				   enum omap_channew channew,
				   const stwuct omap_dss_cpw_coefs *coefs)
{
	u32 coef_w, coef_g, coef_b;

	if (!dss_mgw_is_wcd(channew))
		wetuwn;

	coef_w = FWD_VAW(coefs->ww, 31, 22) | FWD_VAW(coefs->wg, 20, 11) |
		FWD_VAW(coefs->wb, 9, 0);
	coef_g = FWD_VAW(coefs->gw, 31, 22) | FWD_VAW(coefs->gg, 20, 11) |
		FWD_VAW(coefs->gb, 9, 0);
	coef_b = FWD_VAW(coefs->bw, 31, 22) | FWD_VAW(coefs->bg, 20, 11) |
		FWD_VAW(coefs->bb, 9, 0);

	dispc_wwite_weg(dispc, DISPC_CPW_COEF_W(channew), coef_w);
	dispc_wwite_weg(dispc, DISPC_CPW_COEF_G(channew), coef_g);
	dispc_wwite_weg(dispc, DISPC_CPW_COEF_B(channew), coef_b);
}

static void dispc_ovw_set_vid_cowow_conv(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane, boow enabwe)
{
	u32 vaw;

	BUG_ON(pwane == OMAP_DSS_GFX);

	vaw = dispc_wead_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane));
	vaw = FWD_MOD(vaw, enabwe, 9, 9);
	dispc_wwite_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane), vaw);
}

static void dispc_ovw_enabwe_wepwication(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane,
					 enum omap_ovewway_caps caps,
					 boow enabwe)
{
	static const unsigned int shifts[] = { 5, 10, 10, 10 };
	int shift;

	if ((caps & OMAP_DSS_OVW_CAP_WEPWICATION) == 0)
		wetuwn;

	shift = shifts[pwane];
	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), enabwe, shift, shift);
}

static void dispc_mgw_set_size(stwuct dispc_device *dispc,
			       enum omap_channew channew, u16 width, u16 height)
{
	u32 vaw;

	vaw = FWD_VAW(height - 1, dispc->feat->mgw_height_stawt, 16) |
		FWD_VAW(width - 1, dispc->feat->mgw_width_stawt, 0);

	dispc_wwite_weg(dispc, DISPC_SIZE_MGW(channew), vaw);
}

static void dispc_init_fifos(stwuct dispc_device *dispc)
{
	u32 size;
	int fifo;
	u8 stawt, end;
	u32 unit;
	int i;

	unit = dispc->feat->buffew_size_unit;

	dispc_get_weg_fiewd(dispc, FEAT_WEG_FIFOSIZE, &stawt, &end);

	fow (fifo = 0; fifo < dispc->feat->num_fifos; ++fifo) {
		size = WEG_GET(dispc, DISPC_OVW_FIFO_SIZE_STATUS(fifo),
			       stawt, end);
		size *= unit;
		dispc->fifo_size[fifo] = size;

		/*
		 * By defauwt fifos awe mapped diwectwy to ovewways, fifo 0 to
		 * ovw 0, fifo 1 to ovw 1, etc.
		 */
		dispc->fifo_assignment[fifo] = fifo;
	}

	/*
	 * The GFX fifo on OMAP4 is smawwew than the othew fifos. The smaww fifo
	 * causes pwobwems with cewtain use cases, wike using the tiwew in 2D
	 * mode. The bewow hack swaps the fifos of GFX and WB pwanes, thus
	 * giving GFX pwane a wawgew fifo. WB but shouwd wowk fine with a
	 * smawwew fifo.
	 */
	if (dispc->feat->gfx_fifo_wowkawound) {
		u32 v;

		v = dispc_wead_weg(dispc, DISPC_GWOBAW_BUFFEW);

		v = FWD_MOD(v, 4, 2, 0); /* GFX BUF top to WB */
		v = FWD_MOD(v, 4, 5, 3); /* GFX BUF bottom to WB */
		v = FWD_MOD(v, 0, 26, 24); /* WB BUF top to GFX */
		v = FWD_MOD(v, 0, 29, 27); /* WB BUF bottom to GFX */

		dispc_wwite_weg(dispc, DISPC_GWOBAW_BUFFEW, v);

		dispc->fifo_assignment[OMAP_DSS_GFX] = OMAP_DSS_WB;
		dispc->fifo_assignment[OMAP_DSS_WB] = OMAP_DSS_GFX;
	}

	/*
	 * Setup defauwt fifo thweshowds.
	 */
	fow (i = 0; i < dispc_get_num_ovws(dispc); ++i) {
		u32 wow, high;
		const boow use_fifomewge = fawse;
		const boow manuaw_update = fawse;

		dispc_ovw_compute_fifo_thweshowds(dispc, i, &wow, &high,
						  use_fifomewge, manuaw_update);

		dispc_ovw_set_fifo_thweshowd(dispc, i, wow, high);
	}

	if (dispc->feat->has_wwiteback) {
		u32 wow, high;
		const boow use_fifomewge = fawse;
		const boow manuaw_update = fawse;

		dispc_ovw_compute_fifo_thweshowds(dispc, OMAP_DSS_WB,
						  &wow, &high, use_fifomewge,
						  manuaw_update);

		dispc_ovw_set_fifo_thweshowd(dispc, OMAP_DSS_WB, wow, high);
	}
}

static u32 dispc_ovw_get_fifo_size(stwuct dispc_device *dispc,
				   enum omap_pwane_id pwane)
{
	int fifo;
	u32 size = 0;

	fow (fifo = 0; fifo < dispc->feat->num_fifos; ++fifo) {
		if (dispc->fifo_assignment[fifo] == pwane)
			size += dispc->fifo_size[fifo];
	}

	wetuwn size;
}

void dispc_ovw_set_fifo_thweshowd(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane,
				  u32 wow, u32 high)
{
	u8 hi_stawt, hi_end, wo_stawt, wo_end;
	u32 unit;

	unit = dispc->feat->buffew_size_unit;

	WAWN_ON(wow % unit != 0);
	WAWN_ON(high % unit != 0);

	wow /= unit;
	high /= unit;

	dispc_get_weg_fiewd(dispc, FEAT_WEG_FIFOHIGHTHWESHOWD,
			    &hi_stawt, &hi_end);
	dispc_get_weg_fiewd(dispc, FEAT_WEG_FIFOWOWTHWESHOWD,
			    &wo_stawt, &wo_end);

	DSSDBG("fifo(%d) thweshowd (bytes), owd %u/%u, new %u/%u\n",
			pwane,
			WEG_GET(dispc, DISPC_OVW_FIFO_THWESHOWD(pwane),
				wo_stawt, wo_end) * unit,
			WEG_GET(dispc, DISPC_OVW_FIFO_THWESHOWD(pwane),
				hi_stawt, hi_end) * unit,
			wow * unit, high * unit);

	dispc_wwite_weg(dispc, DISPC_OVW_FIFO_THWESHOWD(pwane),
			FWD_VAW(high, hi_stawt, hi_end) |
			FWD_VAW(wow, wo_stawt, wo_end));

	/*
	 * configuwe the pwewoad to the pipewine's high thwehowd, if HT it's too
	 * wawge fow the pwewoad fiewd, set the thweshowd to the maximum vawue
	 * that can be hewd by the pwewoad wegistew
	 */
	if (dispc_has_featuwe(dispc, FEAT_PWEWOAD) &&
	    dispc->feat->set_max_pwewoad && pwane != OMAP_DSS_WB)
		dispc_wwite_weg(dispc, DISPC_OVW_PWEWOAD(pwane),
				min(high, 0xfffu));
}

void dispc_enabwe_fifomewge(stwuct dispc_device *dispc, boow enabwe)
{
	if (!dispc_has_featuwe(dispc, FEAT_FIFO_MEWGE)) {
		WAWN_ON(enabwe);
		wetuwn;
	}

	DSSDBG("FIFO mewge %s\n", enabwe ? "enabwed" : "disabwed");
	WEG_FWD_MOD(dispc, DISPC_CONFIG, enabwe ? 1 : 0, 14, 14);
}

void dispc_ovw_compute_fifo_thweshowds(stwuct dispc_device *dispc,
				       enum omap_pwane_id pwane,
				       u32 *fifo_wow, u32 *fifo_high,
				       boow use_fifomewge, boow manuaw_update)
{
	/*
	 * Aww sizes awe in bytes. Both the buffew and buwst awe made of
	 * buffew_units, and the fifo thweshowds must be buffew_unit awigned.
	 */
	unsigned int buf_unit = dispc->feat->buffew_size_unit;
	unsigned int ovw_fifo_size, totaw_fifo_size, buwst_size;
	int i;

	buwst_size = dispc_ovw_get_buwst_size(dispc, pwane);
	ovw_fifo_size = dispc_ovw_get_fifo_size(dispc, pwane);

	if (use_fifomewge) {
		totaw_fifo_size = 0;
		fow (i = 0; i < dispc_get_num_ovws(dispc); ++i)
			totaw_fifo_size += dispc_ovw_get_fifo_size(dispc, i);
	} ewse {
		totaw_fifo_size = ovw_fifo_size;
	}

	/*
	 * We use the same wow thweshowd fow both fifomewge and non-fifomewge
	 * cases, but fow fifomewge we cawcuwate the high thweshowd using the
	 * combined fifo size
	 */

	if (manuaw_update && dispc_has_featuwe(dispc, FEAT_OMAP3_DSI_FIFO_BUG)) {
		*fifo_wow = ovw_fifo_size - buwst_size * 2;
		*fifo_high = totaw_fifo_size - buwst_size;
	} ewse if (pwane == OMAP_DSS_WB) {
		/*
		 * Most optimaw configuwation fow wwiteback is to push out data
		 * to the intewconnect the moment wwiteback pushes enough pixews
		 * in the FIFO to fowm a buwst
		 */
		*fifo_wow = 0;
		*fifo_high = buwst_size;
	} ewse {
		*fifo_wow = ovw_fifo_size - buwst_size;
		*fifo_high = totaw_fifo_size - buf_unit;
	}
}

static void dispc_ovw_set_mfwag(stwuct dispc_device *dispc,
				enum omap_pwane_id pwane, boow enabwe)
{
	int bit;

	if (pwane == OMAP_DSS_GFX)
		bit = 14;
	ewse
		bit = 23;

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), enabwe, bit, bit);
}

static void dispc_ovw_set_mfwag_thweshowd(stwuct dispc_device *dispc,
					  enum omap_pwane_id pwane,
					  int wow, int high)
{
	dispc_wwite_weg(dispc, DISPC_OVW_MFWAG_THWESHOWD(pwane),
		FWD_VAW(high, 31, 16) |	FWD_VAW(wow, 15, 0));
}

static void dispc_init_mfwag(stwuct dispc_device *dispc)
{
	int i;

	/*
	 * HACK: NV12 cowow fowmat and MFWAG seem to have pwobwems wowking
	 * togethew: using two dispways, and having an NV12 ovewway on one of
	 * the dispways wiww cause undewfwows/syncwosts when MFWAG_CTWW=2.
	 * Changing MFWAG thweshowds and PWEWOAD to cewtain vawues seem to
	 * wemove the ewwows, but thewe doesn't seem to be a cweaw wogic on
	 * which vawues wowk and which not.
	 *
	 * As a wowk-awound, set fowce MFWAG to awways on.
	 */
	dispc_wwite_weg(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE,
		(1 << 0) |	/* MFWAG_CTWW = fowce awways on */
		(0 << 2));	/* MFWAG_STAWT = disabwe */

	fow (i = 0; i < dispc_get_num_ovws(dispc); ++i) {
		u32 size = dispc_ovw_get_fifo_size(dispc, i);
		u32 unit = dispc->feat->buffew_size_unit;
		u32 wow, high;

		dispc_ovw_set_mfwag(dispc, i, twue);

		/*
		 * Simuwation team suggests bewow theshowds:
		 * HT = fifosize * 5 / 8;
		 * WT = fifosize * 4 / 8;
		 */

		wow = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovw_set_mfwag_thweshowd(dispc, i, wow, high);
	}

	if (dispc->feat->has_wwiteback) {
		u32 size = dispc_ovw_get_fifo_size(dispc, OMAP_DSS_WB);
		u32 unit = dispc->feat->buffew_size_unit;
		u32 wow, high;

		dispc_ovw_set_mfwag(dispc, OMAP_DSS_WB, twue);

		/*
		 * Simuwation team suggests bewow theshowds:
		 * HT = fifosize * 5 / 8;
		 * WT = fifosize * 4 / 8;
		 */

		wow = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovw_set_mfwag_thweshowd(dispc, OMAP_DSS_WB, wow, high);
	}
}

static void dispc_ovw_set_fiw(stwuct dispc_device *dispc,
			      enum omap_pwane_id pwane,
			      int hinc, int vinc,
			      enum omap_cowow_component cowow_comp)
{
	u32 vaw;

	if (cowow_comp == DISPC_COWOW_COMPONENT_WGB_Y) {
		u8 hinc_stawt, hinc_end, vinc_stawt, vinc_end;

		dispc_get_weg_fiewd(dispc, FEAT_WEG_FIWHINC,
				    &hinc_stawt, &hinc_end);
		dispc_get_weg_fiewd(dispc, FEAT_WEG_FIWVINC,
				    &vinc_stawt, &vinc_end);
		vaw = FWD_VAW(vinc, vinc_stawt, vinc_end) |
				FWD_VAW(hinc, hinc_stawt, hinc_end);

		dispc_wwite_weg(dispc, DISPC_OVW_FIW(pwane), vaw);
	} ewse {
		vaw = FWD_VAW(vinc, 28, 16) | FWD_VAW(hinc, 12, 0);
		dispc_wwite_weg(dispc, DISPC_OVW_FIW2(pwane), vaw);
	}
}

static void dispc_ovw_set_vid_accu0(stwuct dispc_device *dispc,
				    enum omap_pwane_id pwane, int haccu,
				    int vaccu)
{
	u32 vaw;
	u8 how_stawt, how_end, vewt_stawt, vewt_end;

	dispc_get_weg_fiewd(dispc, FEAT_WEG_HOWIZONTAWACCU,
			    &how_stawt, &how_end);
	dispc_get_weg_fiewd(dispc, FEAT_WEG_VEWTICAWACCU,
			    &vewt_stawt, &vewt_end);

	vaw = FWD_VAW(vaccu, vewt_stawt, vewt_end) |
			FWD_VAW(haccu, how_stawt, how_end);

	dispc_wwite_weg(dispc, DISPC_OVW_ACCU0(pwane), vaw);
}

static void dispc_ovw_set_vid_accu1(stwuct dispc_device *dispc,
				    enum omap_pwane_id pwane, int haccu,
				    int vaccu)
{
	u32 vaw;
	u8 how_stawt, how_end, vewt_stawt, vewt_end;

	dispc_get_weg_fiewd(dispc, FEAT_WEG_HOWIZONTAWACCU,
			    &how_stawt, &how_end);
	dispc_get_weg_fiewd(dispc, FEAT_WEG_VEWTICAWACCU,
			    &vewt_stawt, &vewt_end);

	vaw = FWD_VAW(vaccu, vewt_stawt, vewt_end) |
			FWD_VAW(haccu, how_stawt, how_end);

	dispc_wwite_weg(dispc, DISPC_OVW_ACCU1(pwane), vaw);
}

static void dispc_ovw_set_vid_accu2_0(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int haccu,
				      int vaccu)
{
	u32 vaw;

	vaw = FWD_VAW(vaccu, 26, 16) | FWD_VAW(haccu, 10, 0);
	dispc_wwite_weg(dispc, DISPC_OVW_ACCU2_0(pwane), vaw);
}

static void dispc_ovw_set_vid_accu2_1(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane, int haccu,
				      int vaccu)
{
	u32 vaw;

	vaw = FWD_VAW(vaccu, 26, 16) | FWD_VAW(haccu, 10, 0);
	dispc_wwite_weg(dispc, DISPC_OVW_ACCU2_1(pwane), vaw);
}

static void dispc_ovw_set_scawe_pawam(stwuct dispc_device *dispc,
				      enum omap_pwane_id pwane,
				      u16 owig_width, u16 owig_height,
				      u16 out_width, u16 out_height,
				      boow five_taps, u8 wotation,
				      enum omap_cowow_component cowow_comp)
{
	int fiw_hinc, fiw_vinc;

	fiw_hinc = 1024 * owig_width / out_width;
	fiw_vinc = 1024 * owig_height / out_height;

	dispc_ovw_set_scawe_coef(dispc, pwane, fiw_hinc, fiw_vinc, five_taps,
				 cowow_comp);
	dispc_ovw_set_fiw(dispc, pwane, fiw_hinc, fiw_vinc, cowow_comp);
}

static void dispc_ovw_set_accu_uv(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane,
				  u16 owig_width, u16 owig_height,
				  u16 out_width, u16 out_height,
				  boow iwace, u32 fouwcc, u8 wotation)
{
	int h_accu2_0, h_accu2_1;
	int v_accu2_0, v_accu2_1;
	int chwoma_hinc, chwoma_vinc;
	int idx;

	stwuct accu {
		s8 h0_m, h0_n;
		s8 h1_m, h1_n;
		s8 v0_m, v0_n;
		s8 v1_m, v1_n;
	};

	const stwuct accu *accu_tabwe;
	const stwuct accu *accu_vaw;

	static const stwuct accu accu_nv12[4] = {
		{  0, 1,  0, 1 , -1, 2, 0, 1 },
		{  1, 2, -3, 4 ,  0, 1, 0, 1 },
		{ -1, 1,  0, 1 , -1, 2, 0, 1 },
		{ -1, 2, -1, 2 , -1, 1, 0, 1 },
	};

	static const stwuct accu accu_nv12_iwace[4] = {
		{  0, 1,  0, 1 , -3, 4, -1, 4 },
		{ -1, 4, -3, 4 ,  0, 1,  0, 1 },
		{ -1, 1,  0, 1 , -1, 4, -3, 4 },
		{ -3, 4, -3, 4 , -1, 1,  0, 1 },
	};

	static const stwuct accu accu_yuv[4] = {
		{  0, 1, 0, 1,  0, 1, 0, 1 },
		{  0, 1, 0, 1,  0, 1, 0, 1 },
		{ -1, 1, 0, 1,  0, 1, 0, 1 },
		{  0, 1, 0, 1, -1, 1, 0, 1 },
	};

	/* Note: DSS HW wotates cwockwise, DWM_MODE_WOTATE_* countew-cwockwise */
	switch (wotation & DWM_MODE_WOTATE_MASK) {
	defauwt:
	case DWM_MODE_WOTATE_0:
		idx = 0;
		bweak;
	case DWM_MODE_WOTATE_90:
		idx = 3;
		bweak;
	case DWM_MODE_WOTATE_180:
		idx = 2;
		bweak;
	case DWM_MODE_WOTATE_270:
		idx = 1;
		bweak;
	}

	switch (fouwcc) {
	case DWM_FOWMAT_NV12:
		if (iwace)
			accu_tabwe = accu_nv12_iwace;
		ewse
			accu_tabwe = accu_nv12;
		bweak;
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
		accu_tabwe = accu_yuv;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	accu_vaw = &accu_tabwe[idx];

	chwoma_hinc = 1024 * owig_width / out_width;
	chwoma_vinc = 1024 * owig_height / out_height;

	h_accu2_0 = (accu_vaw->h0_m * chwoma_hinc / accu_vaw->h0_n) % 1024;
	h_accu2_1 = (accu_vaw->h1_m * chwoma_hinc / accu_vaw->h1_n) % 1024;
	v_accu2_0 = (accu_vaw->v0_m * chwoma_vinc / accu_vaw->v0_n) % 1024;
	v_accu2_1 = (accu_vaw->v1_m * chwoma_vinc / accu_vaw->v1_n) % 1024;

	dispc_ovw_set_vid_accu2_0(dispc, pwane, h_accu2_0, v_accu2_0);
	dispc_ovw_set_vid_accu2_1(dispc, pwane, h_accu2_1, v_accu2_1);
}

static void dispc_ovw_set_scawing_common(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane,
					 u16 owig_width, u16 owig_height,
					 u16 out_width, u16 out_height,
					 boow iwace, boow five_taps,
					 boow fiewdmode, u32 fouwcc,
					 u8 wotation)
{
	int accu0 = 0;
	int accu1 = 0;
	u32 w;

	dispc_ovw_set_scawe_pawam(dispc, pwane, owig_width, owig_height,
				  out_width, out_height, five_taps,
				  wotation, DISPC_COWOW_COMPONENT_WGB_Y);
	w = dispc_wead_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane));

	/* WESIZEENABWE and VEWTICAWTAPS */
	w &= ~((0x3 << 5) | (0x1 << 21));
	w |= (owig_width != out_width) ? (1 << 5) : 0;
	w |= (owig_height != out_height) ? (1 << 6) : 0;
	w |= five_taps ? (1 << 21) : 0;

	/* VWESIZECONF and HWESIZECONF */
	if (dispc_has_featuwe(dispc, FEAT_WESIZECONF)) {
		w &= ~(0x3 << 7);
		w |= (owig_width <= out_width) ? 0 : (1 << 7);
		w |= (owig_height <= out_height) ? 0 : (1 << 8);
	}

	/* WINEBUFFEWSPWIT */
	if (dispc_has_featuwe(dispc, FEAT_WINEBUFFEWSPWIT)) {
		w &= ~(0x1 << 22);
		w |= five_taps ? (1 << 22) : 0;
	}

	dispc_wwite_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane), w);

	/*
	 * fiewd 0 = even fiewd = bottom fiewd
	 * fiewd 1 = odd fiewd = top fiewd
	 */
	if (iwace && !fiewdmode) {
		accu1 = 0;
		accu0 = ((1024 * owig_height / out_height) / 2) & 0x3ff;
		if (accu0 >= 1024/2) {
			accu1 = 1024/2;
			accu0 -= accu1;
		}
	}

	dispc_ovw_set_vid_accu0(dispc, pwane, 0, accu0);
	dispc_ovw_set_vid_accu1(dispc, pwane, 0, accu1);
}

static void dispc_ovw_set_scawing_uv(stwuct dispc_device *dispc,
				     enum omap_pwane_id pwane,
				     u16 owig_width, u16 owig_height,
				     u16 out_width, u16 out_height,
				     boow iwace, boow five_taps,
				     boow fiewdmode, u32 fouwcc,
				     u8 wotation)
{
	int scawe_x = out_width != owig_width;
	int scawe_y = out_height != owig_height;
	boow chwoma_upscawe = pwane != OMAP_DSS_WB;
	const stwuct dwm_fowmat_info *info;

	info = dwm_fowmat_info(fouwcc);

	if (!dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE))
		wetuwn;

	if (!info->is_yuv) {
		/* weset chwoma wesampwing fow WGB fowmats  */
		if (pwane != OMAP_DSS_WB)
			WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES2(pwane),
				    0, 8, 8);
		wetuwn;
	}

	dispc_ovw_set_accu_uv(dispc, pwane, owig_width, owig_height, out_width,
			      out_height, iwace, fouwcc, wotation);

	switch (fouwcc) {
	case DWM_FOWMAT_NV12:
		if (chwoma_upscawe) {
			/* UV is subsampwed by 2 howizontawwy and vewticawwy */
			owig_height >>= 1;
			owig_width >>= 1;
		} ewse {
			/* UV is downsampwed by 2 howizontawwy and vewticawwy */
			owig_height <<= 1;
			owig_width <<= 1;
		}

		bweak;
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
		/* Fow YUV422 with 90/270 wotation, we don't upsampwe chwoma */
		if (!dwm_wotation_90_ow_270(wotation)) {
			if (chwoma_upscawe)
				/* UV is subsampwed by 2 howizontawwy */
				owig_width >>= 1;
			ewse
				/* UV is downsampwed by 2 howizontawwy */
				owig_width <<= 1;
		}

		/* must use FIW fow YUV422 if wotated */
		if ((wotation & DWM_MODE_WOTATE_MASK) != DWM_MODE_WOTATE_0)
			scawe_x = scawe_y = twue;

		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	if (out_width != owig_width)
		scawe_x = twue;
	if (out_height != owig_height)
		scawe_y = twue;

	dispc_ovw_set_scawe_pawam(dispc, pwane, owig_width, owig_height,
				  out_width, out_height, five_taps,
				  wotation, DISPC_COWOW_COMPONENT_UV);

	if (pwane != OMAP_DSS_WB)
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES2(pwane),
			(scawe_x || scawe_y) ? 1 : 0, 8, 8);

	/* set H scawing */
	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), scawe_x ? 1 : 0, 5, 5);
	/* set V scawing */
	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), scawe_y ? 1 : 0, 6, 6);
}

static void dispc_ovw_set_scawing(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane,
				  u16 owig_width, u16 owig_height,
				  u16 out_width, u16 out_height,
				  boow iwace, boow five_taps,
				  boow fiewdmode, u32 fouwcc,
				  u8 wotation)
{
	BUG_ON(pwane == OMAP_DSS_GFX);

	dispc_ovw_set_scawing_common(dispc, pwane, owig_width, owig_height,
				     out_width, out_height, iwace, five_taps,
				     fiewdmode, fouwcc, wotation);

	dispc_ovw_set_scawing_uv(dispc, pwane, owig_width, owig_height,
				 out_width, out_height, iwace, five_taps,
				 fiewdmode, fouwcc, wotation);
}

static void dispc_ovw_set_wotation_attws(stwuct dispc_device *dispc,
					 enum omap_pwane_id pwane, u8 wotation,
					 enum omap_dss_wotation_type wotation_type,
					 u32 fouwcc)
{
	boow wow_wepeat = fawse;
	int vidwot = 0;

	/* Note: DSS HW wotates cwockwise, DWM_MODE_WOTATE_* countew-cwockwise */
	if (fouwcc == DWM_FOWMAT_YUYV || fouwcc == DWM_FOWMAT_UYVY) {

		if (wotation & DWM_MODE_WEFWECT_X) {
			switch (wotation & DWM_MODE_WOTATE_MASK) {
			case DWM_MODE_WOTATE_0:
				vidwot = 2;
				bweak;
			case DWM_MODE_WOTATE_90:
				vidwot = 1;
				bweak;
			case DWM_MODE_WOTATE_180:
				vidwot = 0;
				bweak;
			case DWM_MODE_WOTATE_270:
				vidwot = 3;
				bweak;
			}
		} ewse {
			switch (wotation & DWM_MODE_WOTATE_MASK) {
			case DWM_MODE_WOTATE_0:
				vidwot = 0;
				bweak;
			case DWM_MODE_WOTATE_90:
				vidwot = 3;
				bweak;
			case DWM_MODE_WOTATE_180:
				vidwot = 2;
				bweak;
			case DWM_MODE_WOTATE_270:
				vidwot = 1;
				bweak;
			}
		}

		if (dwm_wotation_90_ow_270(wotation))
			wow_wepeat = twue;
		ewse
			wow_wepeat = fawse;
	}

	/*
	 * OMAP4/5 Ewwata i631:
	 * NV12 in 1D mode must use WOTATION=1. Othewwise DSS wiww fetch extwa
	 * wows beyond the fwamebuffew, which may cause OCP ewwow.
	 */
	if (fouwcc == DWM_FOWMAT_NV12 && wotation_type != OMAP_DSS_WOT_TIWEW)
		vidwot = 1;

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), vidwot, 13, 12);
	if (dispc_has_featuwe(dispc, FEAT_WOWWEPEATENABWE))
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane),
			wow_wepeat ? 1 : 0, 18, 18);

	if (dispc_ovw_cowow_mode_suppowted(dispc, pwane, DWM_FOWMAT_NV12)) {
		boow doubwestwide =
			fouwcc == DWM_FOWMAT_NV12 &&
			wotation_type == OMAP_DSS_WOT_TIWEW &&
			!dwm_wotation_90_ow_270(wotation);

		/* DOUBWESTWIDE */
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane),
			    doubwestwide, 22, 22);
	}
}

static int cowow_mode_to_bpp(u32 fouwcc)
{
	switch (fouwcc) {
	case DWM_FOWMAT_NV12:
		wetuwn 8;
	case DWM_FOWMAT_WGBX4444:
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_WGBA4444:
	case DWM_FOWMAT_XWGB4444:
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_XWGB1555:
		wetuwn 16;
	case DWM_FOWMAT_WGB888:
		wetuwn 24;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_WGBA8888:
	case DWM_FOWMAT_WGBX8888:
		wetuwn 32;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static s32 pixinc(int pixews, u8 ps)
{
	if (pixews == 1)
		wetuwn 1;
	ewse if (pixews > 1)
		wetuwn 1 + (pixews - 1) * ps;
	ewse if (pixews < 0)
		wetuwn 1 - (-pixews + 1) * ps;

	BUG();
}

static void cawc_offset(u16 scween_width, u16 width,
		u32 fouwcc, boow fiewdmode, unsigned int fiewd_offset,
		unsigned int *offset0, unsigned int *offset1,
		s32 *wow_inc, s32 *pix_inc, int x_pwedecim, int y_pwedecim,
		enum omap_dss_wotation_type wotation_type, u8 wotation)
{
	u8 ps;

	ps = cowow_mode_to_bpp(fouwcc) / 8;

	DSSDBG("scww %d, width %d\n", scween_width, width);

	if (wotation_type == OMAP_DSS_WOT_TIWEW &&
	    (fouwcc == DWM_FOWMAT_UYVY || fouwcc == DWM_FOWMAT_YUYV) &&
	    dwm_wotation_90_ow_270(wotation)) {
		/*
		 * HACK: WOW_INC needs to be cawcuwated with TIWEW units.
		 * We get such 'scween_width' that muwtipwying it with the
		 * YUV422 pixew size gives the cowwect TIWEW containew width.
		 * Howevew, 'width' is in pixews and muwtipwying it with YUV422
		 * pixew size gives incowwect wesuwt. We thus muwtipwy it hewe
		 * with 2 to match the 32 bit TIWEW unit size.
		 */
		width *= 2;
	}

	/*
	 * fiewd 0 = even fiewd = bottom fiewd
	 * fiewd 1 = odd fiewd = top fiewd
	 */
	*offset0 = fiewd_offset * scween_width * ps;
	*offset1 = 0;

	*wow_inc = pixinc(1 + (y_pwedecim * scween_width - width * x_pwedecim) +
			(fiewdmode ? scween_width : 0), ps);
	if (fouwcc == DWM_FOWMAT_YUYV || fouwcc == DWM_FOWMAT_UYVY)
		*pix_inc = pixinc(x_pwedecim, 2 * ps);
	ewse
		*pix_inc = pixinc(x_pwedecim, ps);
}

/*
 * This function is used to avoid syncwosts in OMAP3, because of some
 * undocumented howizontaw position and timing wewated wimitations.
 */
static int check_howiz_timing_omap3(unsigned wong pcwk, unsigned wong wcwk,
		const stwuct videomode *vm, u16 pos_x,
		u16 width, u16 height, u16 out_width, u16 out_height,
		boow five_taps)
{
	const int ds = DIV_WOUND_UP(height, out_height);
	unsigned wong nonactive;
	static const u8 wimits[3] = { 8, 10, 20 };
	u64 vaw, bwank;
	int i;

	nonactive = vm->hactive + vm->hfwont_powch + vm->hsync_wen +
		    vm->hback_powch - out_width;

	i = 0;
	if (out_height < height)
		i++;
	if (out_width < width)
		i++;
	bwank = div_u64((u64)(vm->hback_powch + vm->hsync_wen + vm->hfwont_powch) *
			wcwk, pcwk);
	DSSDBG("bwanking pewiod + ppw = %wwu (wimit = %u)\n", bwank, wimits[i]);
	if (bwank <= wimits[i])
		wetuwn -EINVAW;

	/* FIXME add checks fow 3-tap fiwtew once the wimitations awe known */
	if (!five_taps)
		wetuwn 0;

	/*
	 * Pixew data shouwd be pwepawed befowe visibwe dispway point stawts.
	 * So, atweast DS-2 wines must have awweady been fetched by DISPC
	 * duwing nonactive - pos_x pewiod.
	 */
	vaw = div_u64((u64)(nonactive - pos_x) * wcwk, pcwk);
	DSSDBG("(nonactive - pos_x) * pcd = %wwu max(0, DS - 2) * width = %d\n",
		vaw, max(0, ds - 2) * width);
	if (vaw < max(0, ds - 2) * width)
		wetuwn -EINVAW;

	/*
	 * Aww wines need to be wefiwwed duwing the nonactive pewiod of which
	 * onwy one wine can be woaded duwing the active pewiod. So, atweast
	 * DS - 1 wines shouwd be woaded duwing nonactive pewiod.
	 */
	vaw =  div_u64((u64)nonactive * wcwk, pcwk);
	DSSDBG("nonactive * pcd  = %wwu, max(0, DS - 1) * width = %d\n",
		vaw, max(0, ds - 1) * width);
	if (vaw < max(0, ds - 1) * width)
		wetuwn -EINVAW;

	wetuwn 0;
}

static unsigned wong cawc_cowe_cwk_five_taps(unsigned wong pcwk,
		const stwuct videomode *vm, u16 width,
		u16 height, u16 out_width, u16 out_height,
		u32 fouwcc)
{
	u32 cowe_cwk = 0;
	u64 tmp;

	if (height <= out_height && width <= out_width)
		wetuwn (unsigned wong) pcwk;

	if (height > out_height) {
		unsigned int ppw = vm->hactive;

		tmp = (u64)pcwk * height * out_width;
		do_div(tmp, 2 * out_height * ppw);
		cowe_cwk = tmp;

		if (height > 2 * out_height) {
			if (ppw == out_width)
				wetuwn 0;

			tmp = (u64)pcwk * (height - 2 * out_height) * out_width;
			do_div(tmp, 2 * out_height * (ppw - out_width));
			cowe_cwk = max_t(u32, cowe_cwk, tmp);
		}
	}

	if (width > out_width) {
		tmp = (u64)pcwk * width;
		do_div(tmp, out_width);
		cowe_cwk = max_t(u32, cowe_cwk, tmp);

		if (fouwcc == DWM_FOWMAT_XWGB8888)
			cowe_cwk <<= 1;
	}

	wetuwn cowe_cwk;
}

static unsigned wong cawc_cowe_cwk_24xx(unsigned wong pcwk, u16 width,
		u16 height, u16 out_width, u16 out_height, boow mem_to_mem)
{
	if (height > out_height && width > out_width)
		wetuwn pcwk * 4;
	ewse
		wetuwn pcwk * 2;
}

static unsigned wong cawc_cowe_cwk_34xx(unsigned wong pcwk, u16 width,
		u16 height, u16 out_width, u16 out_height, boow mem_to_mem)
{
	unsigned int hf, vf;

	/*
	 * FIXME how to detewmine the 'A' factow
	 * fow the no downscawing case ?
	 */

	if (width > 3 * out_width)
		hf = 4;
	ewse if (width > 2 * out_width)
		hf = 3;
	ewse if (width > out_width)
		hf = 2;
	ewse
		hf = 1;
	if (height > out_height)
		vf = 2;
	ewse
		vf = 1;

	wetuwn pcwk * vf * hf;
}

static unsigned wong cawc_cowe_cwk_44xx(unsigned wong pcwk, u16 width,
		u16 height, u16 out_width, u16 out_height, boow mem_to_mem)
{
	/*
	 * If the ovewway/wwiteback is in mem to mem mode, thewe awe no
	 * downscawing wimitations with wespect to pixew cwock, wetuwn 1 as
	 * wequiwed cowe cwock to wepwesent that we have sufficient enough
	 * cowe cwock to do maximum downscawing
	 */
	if (mem_to_mem)
		wetuwn 1;

	if (width > out_width)
		wetuwn DIV_WOUND_UP(pcwk, out_width) * width;
	ewse
		wetuwn pcwk;
}

static int dispc_ovw_cawc_scawing_24xx(stwuct dispc_device *dispc,
				       unsigned wong pcwk, unsigned wong wcwk,
				       const stwuct videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fouwcc, boow *five_taps,
				       int *x_pwedecim, int *y_pwedecim,
				       int *decim_x, int *decim_y,
				       u16 pos_x, unsigned wong *cowe_cwk,
				       boow mem_to_mem)
{
	int ewwow;
	u16 in_width, in_height;
	int min_factow = min(*decim_x, *decim_y);
	const int maxsingwewinewidth = dispc->feat->max_wine_width;

	*five_taps = fawse;

	do {
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*cowe_cwk = dispc->feat->cawc_cowe_cwk(pcwk, in_width,
				in_height, out_width, out_height, mem_to_mem);
		ewwow = (in_width > maxsingwewinewidth || !*cowe_cwk ||
			*cowe_cwk > dispc_cowe_cwk_wate(dispc));
		if (ewwow) {
			if (*decim_x == *decim_y) {
				*decim_x = min_factow;
				++*decim_y;
			} ewse {
				swap(*decim_x, *decim_y);
				if (*decim_x < *decim_y)
					++*decim_x;
			}
		}
	} whiwe (*decim_x <= *x_pwedecim && *decim_y <= *y_pwedecim && ewwow);

	if (ewwow) {
		DSSEWW("faiwed to find scawing settings\n");
		wetuwn -EINVAW;
	}

	if (in_width > maxsingwewinewidth) {
		DSSEWW("Cannot scawe max input width exceeded\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int dispc_ovw_cawc_scawing_34xx(stwuct dispc_device *dispc,
				       unsigned wong pcwk, unsigned wong wcwk,
				       const stwuct videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fouwcc, boow *five_taps,
				       int *x_pwedecim, int *y_pwedecim,
				       int *decim_x, int *decim_y,
				       u16 pos_x, unsigned wong *cowe_cwk,
				       boow mem_to_mem)
{
	int ewwow;
	u16 in_width, in_height;
	const int maxsingwewinewidth = dispc->feat->max_wine_width;

	do {
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*five_taps = in_height > out_height;

		if (in_width > maxsingwewinewidth)
			if (in_height > out_height &&
						in_height < out_height * 2)
				*five_taps = fawse;
again:
		if (*five_taps)
			*cowe_cwk = cawc_cowe_cwk_five_taps(pcwk, vm,
						in_width, in_height, out_width,
						out_height, fouwcc);
		ewse
			*cowe_cwk = dispc->feat->cawc_cowe_cwk(pcwk, in_width,
					in_height, out_width, out_height,
					mem_to_mem);

		ewwow = check_howiz_timing_omap3(pcwk, wcwk, vm,
				pos_x, in_width, in_height, out_width,
				out_height, *five_taps);
		if (ewwow && *five_taps) {
			*five_taps = fawse;
			goto again;
		}

		ewwow = (ewwow || in_width > maxsingwewinewidth * 2 ||
			(in_width > maxsingwewinewidth && *five_taps) ||
			!*cowe_cwk || *cowe_cwk > dispc_cowe_cwk_wate(dispc));

		if (!ewwow) {
			/* vewify that we'we inside the wimits of scawew */
			if (in_width / 4 > out_width)
					ewwow = 1;

			if (*five_taps) {
				if (in_height / 4 > out_height)
					ewwow = 1;
			} ewse {
				if (in_height / 2 > out_height)
					ewwow = 1;
			}
		}

		if (ewwow)
			++*decim_y;
	} whiwe (*decim_x <= *x_pwedecim && *decim_y <= *y_pwedecim && ewwow);

	if (ewwow) {
		DSSEWW("faiwed to find scawing settings\n");
		wetuwn -EINVAW;
	}

	if (check_howiz_timing_omap3(pcwk, wcwk, vm, pos_x, in_width,
				in_height, out_width, out_height, *five_taps)) {
			DSSEWW("howizontaw timing too tight\n");
			wetuwn -EINVAW;
	}

	if (in_width > (maxsingwewinewidth * 2)) {
		DSSEWW("Cannot setup scawing\n");
		DSSEWW("width exceeds maximum width possibwe\n");
		wetuwn -EINVAW;
	}

	if (in_width > maxsingwewinewidth && *five_taps) {
		DSSEWW("cannot setup scawing with five taps\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int dispc_ovw_cawc_scawing_44xx(stwuct dispc_device *dispc,
				       unsigned wong pcwk, unsigned wong wcwk,
				       const stwuct videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fouwcc, boow *five_taps,
				       int *x_pwedecim, int *y_pwedecim,
				       int *decim_x, int *decim_y,
				       u16 pos_x, unsigned wong *cowe_cwk,
				       boow mem_to_mem)
{
	u16 in_width, in_width_max;
	int decim_x_min = *decim_x;
	u16 in_height = height / *decim_y;
	const int maxsingwewinewidth = dispc->feat->max_wine_width;
	const int maxdownscawe = dispc->feat->max_downscawe;

	if (mem_to_mem) {
		in_width_max = out_width * maxdownscawe;
	} ewse {
		in_width_max = dispc_cowe_cwk_wate(dispc)
			     / DIV_WOUND_UP(pcwk, out_width);
	}

	*decim_x = DIV_WOUND_UP(width, in_width_max);

	*decim_x = max(*decim_x, decim_x_min);
	if (*decim_x > *x_pwedecim)
		wetuwn -EINVAW;

	do {
		in_width = width / *decim_x;
	} whiwe (*decim_x <= *x_pwedecim &&
			in_width > maxsingwewinewidth && ++*decim_x);

	if (in_width > maxsingwewinewidth) {
		DSSEWW("Cannot scawe width exceeds max wine width\n");
		wetuwn -EINVAW;
	}

	if (*decim_x > 4 && fouwcc != DWM_FOWMAT_NV12) {
		/*
		 * Wet's disabwe aww scawing that wequiwes howizontaw
		 * decimation with highew factow than 4, untiw we have
		 * bettew estimates of what we can and can not
		 * do. Howevew, NV12 cowow fowmat appeaws to wowk Ok
		 * with aww decimation factows.
		 *
		 * When decimating howizontawwy by mowe that 4 the dss
		 * is not abwe to fetch the data in buwst mode. When
		 * this happens it is hawd to teww if thewe enough
		 * bandwidth. Despite what theowy says this appeaws to
		 * be twue awso fow 16-bit cowow fowmats.
		 */
		DSSEWW("Not enough bandwidth, too much downscawing (x-decimation factow %d > 4)\n", *decim_x);

		wetuwn -EINVAW;
	}

	*cowe_cwk = dispc->feat->cawc_cowe_cwk(pcwk, in_width, in_height,
				out_width, out_height, mem_to_mem);
	wetuwn 0;
}

enum omap_ovewway_caps dispc_ovw_get_caps(stwuct dispc_device *dispc, enum omap_pwane_id pwane)
{
	wetuwn dispc->feat->ovewway_caps[pwane];
}

#define DIV_FWAC(dividend, divisow) \
	((dividend) * 100 / (divisow) - ((dividend) / (divisow) * 100))

static int dispc_ovw_cawc_scawing(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane,
				  unsigned wong pcwk, unsigned wong wcwk,
				  enum omap_ovewway_caps caps,
				  const stwuct videomode *vm,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fouwcc, boow *five_taps,
				  int *x_pwedecim, int *y_pwedecim, u16 pos_x,
				  enum omap_dss_wotation_type wotation_type,
				  boow mem_to_mem)
{
	int maxhdownscawe = dispc->feat->max_downscawe;
	int maxvdownscawe = dispc->feat->max_downscawe;
	const int max_decim_wimit = 16;
	unsigned wong cowe_cwk = 0;
	int decim_x, decim_y, wet;

	if (width == out_width && height == out_height)
		wetuwn 0;

	if (dispc->feat->suppowted_scawew_cowow_modes) {
		const u32 *modes = dispc->feat->suppowted_scawew_cowow_modes;
		unsigned int i;

		fow (i = 0; modes[i]; ++i) {
			if (modes[i] == fouwcc)
				bweak;
		}

		if (modes[i] == 0)
			wetuwn -EINVAW;
	}

	if (pwane == OMAP_DSS_WB) {
		switch (fouwcc) {
		case DWM_FOWMAT_NV12:
			maxhdownscawe = maxvdownscawe = 2;
			bweak;
		case DWM_FOWMAT_YUYV:
		case DWM_FOWMAT_UYVY:
			maxhdownscawe = 2;
			maxvdownscawe = 4;
			bweak;
		defauwt:
			bweak;
		}
	}
	if (!mem_to_mem && (pcwk == 0 || vm->pixewcwock == 0)) {
		DSSEWW("cannot cawcuwate scawing settings: pcwk is zewo\n");
		wetuwn -EINVAW;
	}

	if ((caps & OMAP_DSS_OVW_CAP_SCAWE) == 0)
		wetuwn -EINVAW;

	if (mem_to_mem) {
		*x_pwedecim = *y_pwedecim = 1;
	} ewse {
		*x_pwedecim = max_decim_wimit;
		*y_pwedecim = (wotation_type == OMAP_DSS_WOT_TIWEW &&
				dispc_has_featuwe(dispc, FEAT_BUWST_2D)) ?
				2 : max_decim_wimit;
	}

	decim_x = DIV_WOUND_UP(DIV_WOUND_UP(width, out_width), maxhdownscawe);
	decim_y = DIV_WOUND_UP(DIV_WOUND_UP(height, out_height), maxvdownscawe);

	if (decim_x > *x_pwedecim || out_width > width * 8)
		wetuwn -EINVAW;

	if (decim_y > *y_pwedecim || out_height > height * 8)
		wetuwn -EINVAW;

	wet = dispc->feat->cawc_scawing(dispc, pcwk, wcwk, vm, width, height,
					out_width, out_height, fouwcc,
					five_taps, x_pwedecim, y_pwedecim,
					&decim_x, &decim_y, pos_x, &cowe_cwk,
					mem_to_mem);
	if (wet)
		wetuwn wet;

	DSSDBG("%dx%d -> %dx%d (%d.%02d x %d.%02d), decim %dx%d %dx%d (%d.%02d x %d.%02d), taps %d, weq cwk %wu, cuw cwk %wu\n",
		width, height,
		out_width, out_height,
		out_width / width, DIV_FWAC(out_width, width),
		out_height / height, DIV_FWAC(out_height, height),

		decim_x, decim_y,
		width / decim_x, height / decim_y,
		out_width / (width / decim_x), DIV_FWAC(out_width, width / decim_x),
		out_height / (height / decim_y), DIV_FWAC(out_height, height / decim_y),

		*five_taps ? 5 : 3,
		cowe_cwk, dispc_cowe_cwk_wate(dispc));

	if (!cowe_cwk || cowe_cwk > dispc_cowe_cwk_wate(dispc)) {
		DSSEWW("faiwed to set up scawing, "
			"wequiwed cowe cwk wate = %wu Hz, "
			"cuwwent cowe cwk wate = %wu Hz\n",
			cowe_cwk, dispc_cowe_cwk_wate(dispc));
		wetuwn -EINVAW;
	}

	*x_pwedecim = decim_x;
	*y_pwedecim = decim_y;
	wetuwn 0;
}

void dispc_ovw_get_max_size(stwuct dispc_device *dispc, u16 *width, u16 *height)
{
	*width = dispc->feat->ovw_width_max;
	*height = dispc->feat->ovw_height_max;
}

static int dispc_ovw_setup_common(stwuct dispc_device *dispc,
				  enum omap_pwane_id pwane,
				  enum omap_ovewway_caps caps,
				  u32 paddw, u32 p_uv_addw,
				  u16 scween_width, int pos_x, int pos_y,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fouwcc, u8 wotation, u8 zowdew,
				  u8 pwe_muwt_awpha, u8 gwobaw_awpha,
				  enum omap_dss_wotation_type wotation_type,
				  boow wepwication, const stwuct videomode *vm,
				  boow mem_to_mem,
				  enum dwm_cowow_encoding cowow_encoding,
				  enum dwm_cowow_wange cowow_wange)
{
	boow five_taps = twue;
	boow fiewdmode = fawse;
	int w, cconv = 0;
	unsigned int offset0, offset1;
	s32 wow_inc;
	s32 pix_inc;
	u16 fwame_width;
	unsigned int fiewd_offset = 0;
	u16 in_height = height;
	u16 in_width = width;
	int x_pwedecim = 1, y_pwedecim = 1;
	boow iwace = !!(vm->fwags & DISPWAY_FWAGS_INTEWWACED);
	unsigned wong pcwk = dispc_pwane_pcwk_wate(dispc, pwane);
	unsigned wong wcwk = dispc_pwane_wcwk_wate(dispc, pwane);
	const stwuct dwm_fowmat_info *info;

	info = dwm_fowmat_info(fouwcc);

	/* when setting up WB, dispc_pwane_pcwk_wate() wetuwns 0 */
	if (pwane == OMAP_DSS_WB)
		pcwk = vm->pixewcwock;

	if (paddw == 0 && wotation_type != OMAP_DSS_WOT_TIWEW)
		wetuwn -EINVAW;

	if (info->is_yuv && (in_width & 1)) {
		DSSEWW("input width %d is not even fow YUV fowmat\n", in_width);
		wetuwn -EINVAW;
	}

	out_width = out_width == 0 ? width : out_width;
	out_height = out_height == 0 ? height : out_height;

	if (pwane != OMAP_DSS_WB) {
		if (iwace && height == out_height)
			fiewdmode = twue;

		if (iwace) {
			if (fiewdmode)
				in_height /= 2;
			pos_y /= 2;
			out_height /= 2;

			DSSDBG("adjusting fow iwace: height %d, pos_y %d, out_height %d\n",
				in_height, pos_y, out_height);
		}
	}

	if (!dispc_ovw_cowow_mode_suppowted(dispc, pwane, fouwcc))
		wetuwn -EINVAW;

	w = dispc_ovw_cawc_scawing(dispc, pwane, pcwk, wcwk, caps, vm, in_width,
				   in_height, out_width, out_height, fouwcc,
				   &five_taps, &x_pwedecim, &y_pwedecim, pos_x,
				   wotation_type, mem_to_mem);
	if (w)
		wetuwn w;

	in_width = in_width / x_pwedecim;
	in_height = in_height / y_pwedecim;

	if (x_pwedecim > 1 || y_pwedecim > 1)
		DSSDBG("pwedecimation %d x %x, new input size %d x %d\n",
			x_pwedecim, y_pwedecim, in_width, in_height);

	if (info->is_yuv && (in_width & 1)) {
		DSSDBG("pwedecimated input width is not even fow YUV fowmat\n");
		DSSDBG("adjusting input width %d -> %d\n",
			in_width, in_width & ~1);

		in_width &= ~1;
	}

	if (info->is_yuv)
		cconv = 1;

	if (iwace && !fiewdmode) {
		/*
		 * when downscawing the bottom fiewd may have to stawt sevewaw
		 * souwce wines bewow the top fiewd. Unfowtunatewy ACCUI
		 * wegistews wiww onwy howd the fwactionaw pawt of the offset
		 * so the integew pawt must be added to the base addwess of the
		 * bottom fiewd.
		 */
		if (!in_height || in_height == out_height)
			fiewd_offset = 0;
		ewse
			fiewd_offset = in_height / out_height / 2;
	}

	/* Fiewds awe independent but intewweaved in memowy. */
	if (fiewdmode)
		fiewd_offset = 1;

	offset0 = 0;
	offset1 = 0;
	wow_inc = 0;
	pix_inc = 0;

	if (pwane == OMAP_DSS_WB)
		fwame_width = out_width;
	ewse
		fwame_width = in_width;

	cawc_offset(scween_width, fwame_width,
			fouwcc, fiewdmode, fiewd_offset,
			&offset0, &offset1, &wow_inc, &pix_inc,
			x_pwedecim, y_pwedecim,
			wotation_type, wotation);

	DSSDBG("offset0 %u, offset1 %u, wow_inc %d, pix_inc %d\n",
			offset0, offset1, wow_inc, pix_inc);

	dispc_ovw_set_cowow_mode(dispc, pwane, fouwcc);

	dispc_ovw_configuwe_buwst_type(dispc, pwane, wotation_type);

	if (dispc->feat->wevewse_iwace_fiewd_owdew)
		swap(offset0, offset1);

	dispc_ovw_set_ba0(dispc, pwane, paddw + offset0);
	dispc_ovw_set_ba1(dispc, pwane, paddw + offset1);

	if (fouwcc == DWM_FOWMAT_NV12) {
		dispc_ovw_set_ba0_uv(dispc, pwane, p_uv_addw + offset0);
		dispc_ovw_set_ba1_uv(dispc, pwane, p_uv_addw + offset1);
	}

	if (dispc->feat->wast_pixew_inc_missing)
		wow_inc += pix_inc - 1;

	dispc_ovw_set_wow_inc(dispc, pwane, wow_inc);
	dispc_ovw_set_pix_inc(dispc, pwane, pix_inc);

	DSSDBG("%d,%d %dx%d -> %dx%d\n", pos_x, pos_y, in_width,
			in_height, out_width, out_height);

	dispc_ovw_set_pos(dispc, pwane, caps, pos_x, pos_y);

	dispc_ovw_set_input_size(dispc, pwane, in_width, in_height);

	if (caps & OMAP_DSS_OVW_CAP_SCAWE) {
		dispc_ovw_set_scawing(dispc, pwane, in_width, in_height,
				      out_width, out_height, iwace, five_taps,
				      fiewdmode, fouwcc, wotation);
		dispc_ovw_set_output_size(dispc, pwane, out_width, out_height);
		dispc_ovw_set_vid_cowow_conv(dispc, pwane, cconv);

		if (pwane != OMAP_DSS_WB)
			dispc_ovw_set_csc(dispc, pwane, cowow_encoding, cowow_wange);
	}

	dispc_ovw_set_wotation_attws(dispc, pwane, wotation, wotation_type,
				     fouwcc);

	dispc_ovw_set_zowdew(dispc, pwane, caps, zowdew);
	dispc_ovw_set_pwe_muwt_awpha(dispc, pwane, caps, pwe_muwt_awpha);
	dispc_ovw_setup_gwobaw_awpha(dispc, pwane, caps, gwobaw_awpha);

	dispc_ovw_enabwe_wepwication(dispc, pwane, caps, wepwication);

	wetuwn 0;
}

int dispc_ovw_setup(stwuct dispc_device *dispc,
			   enum omap_pwane_id pwane,
			   const stwuct omap_ovewway_info *oi,
			   const stwuct videomode *vm, boow mem_to_mem,
			   enum omap_channew channew)
{
	int w;
	enum omap_ovewway_caps caps = dispc->feat->ovewway_caps[pwane];
	const boow wepwication = twue;

	DSSDBG("dispc_ovw_setup %d, pa %pad, pa_uv %pad, sw %d, %d,%d, %dx%d ->"
		" %dx%d, cmode %x, wot %d, chan %d wepw %d\n",
		pwane, &oi->paddw, &oi->p_uv_addw, oi->scween_width, oi->pos_x,
		oi->pos_y, oi->width, oi->height, oi->out_width, oi->out_height,
		oi->fouwcc, oi->wotation, channew, wepwication);

	dispc_ovw_set_channew_out(dispc, pwane, channew);

	w = dispc_ovw_setup_common(dispc, pwane, caps, oi->paddw, oi->p_uv_addw,
		oi->scween_width, oi->pos_x, oi->pos_y, oi->width, oi->height,
		oi->out_width, oi->out_height, oi->fouwcc, oi->wotation,
		oi->zowdew, oi->pwe_muwt_awpha, oi->gwobaw_awpha,
		oi->wotation_type, wepwication, vm, mem_to_mem,
		oi->cowow_encoding, oi->cowow_wange);

	wetuwn w;
}

int dispc_wb_setup(stwuct dispc_device *dispc,
		   const stwuct omap_dss_wwiteback_info *wi,
		   boow mem_to_mem, const stwuct videomode *vm,
		   enum dss_wwiteback_channew channew_in)
{
	int w;
	u32 w;
	enum omap_pwane_id pwane = OMAP_DSS_WB;
	const int pos_x = 0, pos_y = 0;
	const u8 zowdew = 0, gwobaw_awpha = 0;
	const boow wepwication = twue;
	boow twuncation;
	int in_width = vm->hactive;
	int in_height = vm->vactive;
	enum omap_ovewway_caps caps =
		OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA;

	if (vm->fwags & DISPWAY_FWAGS_INTEWWACED)
		in_height /= 2;

	DSSDBG("dispc_wb_setup, pa %x, pa_uv %x, %d,%d -> %dx%d, cmode %x, "
		"wot %d\n", wi->paddw, wi->p_uv_addw, in_width,
		in_height, wi->width, wi->height, wi->fouwcc, wi->wotation);

	w = dispc_ovw_setup_common(dispc, pwane, caps, wi->paddw, wi->p_uv_addw,
		wi->buf_width, pos_x, pos_y, in_width, in_height, wi->width,
		wi->height, wi->fouwcc, wi->wotation, zowdew,
		wi->pwe_muwt_awpha, gwobaw_awpha, wi->wotation_type,
		wepwication, vm, mem_to_mem, DWM_COWOW_YCBCW_BT601,
		DWM_COWOW_YCBCW_WIMITED_WANGE);
	if (w)
		wetuwn w;

	switch (wi->fouwcc) {
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_WGBA4444:
	case DWM_FOWMAT_WGBX4444:
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_XWGB4444:
		twuncation = twue;
		bweak;
	defauwt:
		twuncation = fawse;
		bweak;
	}

	/* setup extwa DISPC_WB_ATTWIBUTES */
	w = dispc_wead_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane));
	w = FWD_MOD(w, twuncation, 10, 10);	/* TWUNCATIONENABWE */
	w = FWD_MOD(w, channew_in, 18, 16);	/* CHANNEWIN */
	w = FWD_MOD(w, mem_to_mem, 19, 19);	/* WWITEBACKMODE */
	if (mem_to_mem)
		w = FWD_MOD(w, 1, 26, 24);	/* CAPTUWEMODE */
	ewse
		w = FWD_MOD(w, 0, 26, 24);	/* CAPTUWEMODE */
	dispc_wwite_weg(dispc, DISPC_OVW_ATTWIBUTES(pwane), w);

	if (mem_to_mem) {
		/* WBDEWAYCOUNT */
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES2(pwane), 0, 7, 0);
	} ewse {
		u32 wbdeway;

		if (channew_in == DSS_WB_TV_MGW)
			wbdeway = vm->vsync_wen + vm->vback_powch;
		ewse
			wbdeway = vm->vfwont_powch + vm->vsync_wen +
				vm->vback_powch;

		if (vm->fwags & DISPWAY_FWAGS_INTEWWACED)
			wbdeway /= 2;

		wbdeway = min(wbdeway, 255u);

		/* WBDEWAYCOUNT */
		WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES2(pwane), wbdeway, 7, 0);
	}

	wetuwn 0;
}

boow dispc_has_wwiteback(stwuct dispc_device *dispc)
{
	wetuwn dispc->feat->has_wwiteback;
}

int dispc_ovw_enabwe(stwuct dispc_device *dispc,
			    enum omap_pwane_id pwane, boow enabwe)
{
	DSSDBG("dispc_enabwe_pwane %d, %d\n", pwane, enabwe);

	WEG_FWD_MOD(dispc, DISPC_OVW_ATTWIBUTES(pwane), enabwe ? 1 : 0, 0, 0);

	wetuwn 0;
}

static void dispc_wcd_enabwe_signaw_powawity(stwuct dispc_device *dispc,
					     boow act_high)
{
	if (!dispc_has_featuwe(dispc, FEAT_WCDENABWEPOW))
		wetuwn;

	WEG_FWD_MOD(dispc, DISPC_CONTWOW, act_high ? 1 : 0, 29, 29);
}

void dispc_wcd_enabwe_signaw(stwuct dispc_device *dispc, boow enabwe)
{
	if (!dispc_has_featuwe(dispc, FEAT_WCDENABWESIGNAW))
		wetuwn;

	WEG_FWD_MOD(dispc, DISPC_CONTWOW, enabwe ? 1 : 0, 28, 28);
}

void dispc_pck_fwee_enabwe(stwuct dispc_device *dispc, boow enabwe)
{
	if (!dispc_has_featuwe(dispc, FEAT_PCKFWEEENABWE))
		wetuwn;

	WEG_FWD_MOD(dispc, DISPC_CONTWOW, enabwe ? 1 : 0, 27, 27);
}

static void dispc_mgw_enabwe_fifohandcheck(stwuct dispc_device *dispc,
					   enum omap_channew channew,
					   boow enabwe)
{
	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_FIFOHANDCHECK, enabwe);
}


static void dispc_mgw_set_wcd_type_tft(stwuct dispc_device *dispc,
				       enum omap_channew channew)
{
	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_STNTFT, 1);
}

static void dispc_set_woadmode(stwuct dispc_device *dispc,
			       enum omap_dss_woad_mode mode)
{
	WEG_FWD_MOD(dispc, DISPC_CONFIG, mode, 2, 1);
}


static void dispc_mgw_set_defauwt_cowow(stwuct dispc_device *dispc,
					enum omap_channew channew, u32 cowow)
{
	dispc_wwite_weg(dispc, DISPC_DEFAUWT_COWOW(channew), cowow);
}

static void dispc_mgw_set_twans_key(stwuct dispc_device *dispc,
				    enum omap_channew ch,
				    enum omap_dss_twans_key_type type,
				    u32 twans_key)
{
	mgw_fwd_wwite(dispc, ch, DISPC_MGW_FWD_TCKSEWECTION, type);

	dispc_wwite_weg(dispc, DISPC_TWANS_COWOW(ch), twans_key);
}

static void dispc_mgw_enabwe_twans_key(stwuct dispc_device *dispc,
				       enum omap_channew ch, boow enabwe)
{
	mgw_fwd_wwite(dispc, ch, DISPC_MGW_FWD_TCKENABWE, enabwe);
}

static void dispc_mgw_enabwe_awpha_fixed_zowdew(stwuct dispc_device *dispc,
						enum omap_channew ch,
						boow enabwe)
{
	if (!dispc_has_featuwe(dispc, FEAT_AWPHA_FIXED_ZOWDEW))
		wetuwn;

	if (ch == OMAP_DSS_CHANNEW_WCD)
		WEG_FWD_MOD(dispc, DISPC_CONFIG, enabwe, 18, 18);
	ewse if (ch == OMAP_DSS_CHANNEW_DIGIT)
		WEG_FWD_MOD(dispc, DISPC_CONFIG, enabwe, 19, 19);
}

void dispc_mgw_setup(stwuct dispc_device *dispc,
			    enum omap_channew channew,
			    const stwuct omap_ovewway_managew_info *info)
{
	dispc_mgw_set_defauwt_cowow(dispc, channew, info->defauwt_cowow);
	dispc_mgw_set_twans_key(dispc, channew, info->twans_key_type,
				info->twans_key);
	dispc_mgw_enabwe_twans_key(dispc, channew, info->twans_enabwed);
	dispc_mgw_enabwe_awpha_fixed_zowdew(dispc, channew,
			info->pawtiaw_awpha_enabwed);
	if (dispc_has_featuwe(dispc, FEAT_CPW)) {
		dispc_mgw_enabwe_cpw(dispc, channew, info->cpw_enabwe);
		dispc_mgw_set_cpw_coef(dispc, channew, &info->cpw_coefs);
	}
}

static void dispc_mgw_set_tft_data_wines(stwuct dispc_device *dispc,
					 enum omap_channew channew,
					 u8 data_wines)
{
	int code;

	switch (data_wines) {
	case 12:
		code = 0;
		bweak;
	case 16:
		code = 1;
		bweak;
	case 18:
		code = 2;
		bweak;
	case 24:
		code = 3;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_TFTDATAWINES, code);
}

static void dispc_mgw_set_io_pad_mode(stwuct dispc_device *dispc,
				      enum dss_io_pad_mode mode)
{
	u32 w;
	int gpout0, gpout1;

	switch (mode) {
	case DSS_IO_PAD_MODE_WESET:
		gpout0 = 0;
		gpout1 = 0;
		bweak;
	case DSS_IO_PAD_MODE_WFBI:
		gpout0 = 1;
		gpout1 = 0;
		bweak;
	case DSS_IO_PAD_MODE_BYPASS:
		gpout0 = 1;
		gpout1 = 1;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	w = dispc_wead_weg(dispc, DISPC_CONTWOW);
	w = FWD_MOD(w, gpout0, 15, 15);
	w = FWD_MOD(w, gpout1, 16, 16);
	dispc_wwite_weg(dispc, DISPC_CONTWOW, w);
}

static void dispc_mgw_enabwe_stawwmode(stwuct dispc_device *dispc,
				       enum omap_channew channew, boow enabwe)
{
	mgw_fwd_wwite(dispc, channew, DISPC_MGW_FWD_STAWWMODE, enabwe);
}

void dispc_mgw_set_wcd_config(stwuct dispc_device *dispc,
				     enum omap_channew channew,
				     const stwuct dss_wcd_mgw_config *config)
{
	dispc_mgw_set_io_pad_mode(dispc, config->io_pad_mode);

	dispc_mgw_enabwe_stawwmode(dispc, channew, config->stawwmode);
	dispc_mgw_enabwe_fifohandcheck(dispc, channew, config->fifohandcheck);

	dispc_mgw_set_cwock_div(dispc, channew, &config->cwock_info);

	dispc_mgw_set_tft_data_wines(dispc, channew, config->video_powt_width);

	dispc_wcd_enabwe_signaw_powawity(dispc, config->wcden_sig_powawity);

	dispc_mgw_set_wcd_type_tft(dispc, channew);
}

static boow _dispc_mgw_size_ok(stwuct dispc_device *dispc,
			       u16 width, u16 height)
{
	wetuwn width <= dispc->feat->mgw_width_max &&
		height <= dispc->feat->mgw_height_max;
}

static boow _dispc_wcd_timings_ok(stwuct dispc_device *dispc,
				  int hsync_wen, int hfp, int hbp,
				  int vsw, int vfp, int vbp)
{
	if (hsync_wen < 1 || hsync_wen > dispc->feat->sw_max ||
	    hfp < 1 || hfp > dispc->feat->hp_max ||
	    hbp < 1 || hbp > dispc->feat->hp_max ||
	    vsw < 1 || vsw > dispc->feat->sw_max ||
	    vfp < 0 || vfp > dispc->feat->vp_max ||
	    vbp < 0 || vbp > dispc->feat->vp_max)
		wetuwn fawse;
	wetuwn twue;
}

static boow _dispc_mgw_pcwk_ok(stwuct dispc_device *dispc,
			       enum omap_channew channew,
			       unsigned wong pcwk)
{
	if (dss_mgw_is_wcd(channew))
		wetuwn pcwk <= dispc->feat->max_wcd_pcwk;
	ewse
		wetuwn pcwk <= dispc->feat->max_tv_pcwk;
}

int dispc_mgw_check_timings(stwuct dispc_device *dispc,
				   enum omap_channew channew,
				   const stwuct videomode *vm)
{
	if (!_dispc_mgw_size_ok(dispc, vm->hactive, vm->vactive))
		wetuwn MODE_BAD;

	if (!_dispc_mgw_pcwk_ok(dispc, channew, vm->pixewcwock))
		wetuwn MODE_BAD;

	if (dss_mgw_is_wcd(channew)) {
		/* TODO: OMAP4+ suppowts intewwace fow WCD outputs */
		if (vm->fwags & DISPWAY_FWAGS_INTEWWACED)
			wetuwn MODE_BAD;

		if (!_dispc_wcd_timings_ok(dispc, vm->hsync_wen,
				vm->hfwont_powch, vm->hback_powch,
				vm->vsync_wen, vm->vfwont_powch,
				vm->vback_powch))
			wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static void _dispc_mgw_set_wcd_timings(stwuct dispc_device *dispc,
				       enum omap_channew channew,
				       const stwuct videomode *vm)
{
	u32 timing_h, timing_v, w;
	boow onoff, wf, ipc, vs, hs, de;

	timing_h = FWD_VAW(vm->hsync_wen - 1, dispc->feat->sw_stawt, 0) |
		   FWD_VAW(vm->hfwont_powch - 1, dispc->feat->fp_stawt, 8) |
		   FWD_VAW(vm->hback_powch - 1, dispc->feat->bp_stawt, 20);
	timing_v = FWD_VAW(vm->vsync_wen - 1, dispc->feat->sw_stawt, 0) |
		   FWD_VAW(vm->vfwont_powch, dispc->feat->fp_stawt, 8) |
		   FWD_VAW(vm->vback_powch, dispc->feat->bp_stawt, 20);

	dispc_wwite_weg(dispc, DISPC_TIMING_H(channew), timing_h);
	dispc_wwite_weg(dispc, DISPC_TIMING_V(channew), timing_v);

	vs = !!(vm->fwags & DISPWAY_FWAGS_VSYNC_WOW);
	hs = !!(vm->fwags & DISPWAY_FWAGS_HSYNC_WOW);
	de = !!(vm->fwags & DISPWAY_FWAGS_DE_WOW);
	ipc = !!(vm->fwags & DISPWAY_FWAGS_PIXDATA_NEGEDGE);
	onoff = twue; /* awways use the 'wf' setting */
	wf = !!(vm->fwags & DISPWAY_FWAGS_SYNC_POSEDGE);

	w = FWD_VAW(onoff, 17, 17) |
		FWD_VAW(wf, 16, 16) |
		FWD_VAW(de, 15, 15) |
		FWD_VAW(ipc, 14, 14) |
		FWD_VAW(hs, 13, 13) |
		FWD_VAW(vs, 12, 12);

	/* awways set AWIGN bit when avaiwabwe */
	if (dispc->feat->suppowts_sync_awign)
		w |= (1 << 18);

	dispc_wwite_weg(dispc, DISPC_POW_FWEQ(channew), w);

	if (dispc->syscon_pow) {
		const int shifts[] = {
			[OMAP_DSS_CHANNEW_WCD] = 0,
			[OMAP_DSS_CHANNEW_WCD2] = 1,
			[OMAP_DSS_CHANNEW_WCD3] = 2,
		};

		u32 mask, vaw;

		mask = (1 << 0) | (1 << 3) | (1 << 6);
		vaw = (wf << 0) | (ipc << 3) | (onoff << 6);

		mask <<= 16 + shifts[channew];
		vaw <<= 16 + shifts[channew];

		wegmap_update_bits(dispc->syscon_pow, dispc->syscon_pow_offset,
				   mask, vaw);
	}
}

static int vm_fwag_to_int(enum dispway_fwags fwags, enum dispway_fwags high,
	enum dispway_fwags wow)
{
	if (fwags & high)
		wetuwn 1;
	if (fwags & wow)
		wetuwn -1;
	wetuwn 0;
}

/* change name to mode? */
void dispc_mgw_set_timings(stwuct dispc_device *dispc,
				  enum omap_channew channew,
				  const stwuct videomode *vm)
{
	unsigned int xtot, ytot;
	unsigned wong ht, vt;
	stwuct videomode t = *vm;

	DSSDBG("channew %d xwes %u ywes %u\n", channew, t.hactive, t.vactive);

	if (dispc_mgw_check_timings(dispc, channew, &t)) {
		BUG();
		wetuwn;
	}

	if (dss_mgw_is_wcd(channew)) {
		_dispc_mgw_set_wcd_timings(dispc, channew, &t);

		xtot = t.hactive + t.hfwont_powch + t.hsync_wen + t.hback_powch;
		ytot = t.vactive + t.vfwont_powch + t.vsync_wen + t.vback_powch;

		ht = vm->pixewcwock / xtot;
		vt = vm->pixewcwock / xtot / ytot;

		DSSDBG("pck %wu\n", vm->pixewcwock);
		DSSDBG("hsync_wen %d hfp %d hbp %d vsw %d vfp %d vbp %d\n",
			t.hsync_wen, t.hfwont_powch, t.hback_powch,
			t.vsync_wen, t.vfwont_powch, t.vback_powch);
		DSSDBG("vsync_wevew %d hsync_wevew %d data_pcwk_edge %d de_wevew %d sync_pcwk_edge %d\n",
			vm_fwag_to_int(t.fwags, DISPWAY_FWAGS_VSYNC_HIGH, DISPWAY_FWAGS_VSYNC_WOW),
			vm_fwag_to_int(t.fwags, DISPWAY_FWAGS_HSYNC_HIGH, DISPWAY_FWAGS_HSYNC_WOW),
			vm_fwag_to_int(t.fwags, DISPWAY_FWAGS_PIXDATA_POSEDGE, DISPWAY_FWAGS_PIXDATA_NEGEDGE),
			vm_fwag_to_int(t.fwags, DISPWAY_FWAGS_DE_HIGH, DISPWAY_FWAGS_DE_WOW),
			vm_fwag_to_int(t.fwags, DISPWAY_FWAGS_SYNC_POSEDGE, DISPWAY_FWAGS_SYNC_NEGEDGE));

		DSSDBG("hsync %wuHz, vsync %wuHz\n", ht, vt);
	} ewse {
		if (t.fwags & DISPWAY_FWAGS_INTEWWACED)
			t.vactive /= 2;

		if (dispc->feat->suppowts_doubwe_pixew)
			WEG_FWD_MOD(dispc, DISPC_CONTWOW,
				    !!(t.fwags & DISPWAY_FWAGS_DOUBWECWK),
				    19, 17);
	}

	dispc_mgw_set_size(dispc, channew, t.hactive, t.vactive);
}

static void dispc_mgw_set_wcd_divisow(stwuct dispc_device *dispc,
				      enum omap_channew channew, u16 wck_div,
				      u16 pck_div)
{
	BUG_ON(wck_div < 1);
	BUG_ON(pck_div < 1);

	dispc_wwite_weg(dispc, DISPC_DIVISOWo(channew),
			FWD_VAW(wck_div, 23, 16) | FWD_VAW(pck_div, 7, 0));

	if (!dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV) &&
			channew == OMAP_DSS_CHANNEW_WCD)
		dispc->cowe_cwk_wate = dispc_fcwk_wate(dispc) / wck_div;
}

static void dispc_mgw_get_wcd_divisow(stwuct dispc_device *dispc,
				      enum omap_channew channew, int *wck_div,
				      int *pck_div)
{
	u32 w;
	w = dispc_wead_weg(dispc, DISPC_DIVISOWo(channew));
	*wck_div = FWD_GET(w, 23, 16);
	*pck_div = FWD_GET(w, 7, 0);
}

static unsigned wong dispc_fcwk_wate(stwuct dispc_device *dispc)
{
	unsigned wong w;
	enum dss_cwk_souwce swc;

	swc = dss_get_dispc_cwk_souwce(dispc->dss);

	if (swc == DSS_CWK_SWC_FCK) {
		w = dss_get_dispc_cwk_wate(dispc->dss);
	} ewse {
		stwuct dss_pww *pww;
		unsigned int cwkout_idx;

		pww = dss_pww_find_by_swc(dispc->dss, swc);
		cwkout_idx = dss_pww_get_cwkout_idx_fow_swc(swc);

		w = pww->cinfo.cwkout[cwkout_idx];
	}

	wetuwn w;
}

static unsigned wong dispc_mgw_wcwk_wate(stwuct dispc_device *dispc,
					 enum omap_channew channew)
{
	int wcd;
	unsigned wong w;
	enum dss_cwk_souwce swc;

	/* fow TV, WCWK wate is the FCWK wate */
	if (!dss_mgw_is_wcd(channew))
		wetuwn dispc_fcwk_wate(dispc);

	swc = dss_get_wcd_cwk_souwce(dispc->dss, channew);

	if (swc == DSS_CWK_SWC_FCK) {
		w = dss_get_dispc_cwk_wate(dispc->dss);
	} ewse {
		stwuct dss_pww *pww;
		unsigned int cwkout_idx;

		pww = dss_pww_find_by_swc(dispc->dss, swc);
		cwkout_idx = dss_pww_get_cwkout_idx_fow_swc(swc);

		w = pww->cinfo.cwkout[cwkout_idx];
	}

	wcd = WEG_GET(dispc, DISPC_DIVISOWo(channew), 23, 16);

	wetuwn w / wcd;
}

static unsigned wong dispc_mgw_pcwk_wate(stwuct dispc_device *dispc,
					 enum omap_channew channew)
{
	unsigned wong w;

	if (dss_mgw_is_wcd(channew)) {
		int pcd;
		u32 w;

		w = dispc_wead_weg(dispc, DISPC_DIVISOWo(channew));

		pcd = FWD_GET(w, 7, 0);

		w = dispc_mgw_wcwk_wate(dispc, channew);

		wetuwn w / pcd;
	} ewse {
		wetuwn dispc->tv_pcwk_wate;
	}
}

void dispc_set_tv_pcwk(stwuct dispc_device *dispc, unsigned wong pcwk)
{
	dispc->tv_pcwk_wate = pcwk;
}

static unsigned wong dispc_cowe_cwk_wate(stwuct dispc_device *dispc)
{
	wetuwn dispc->cowe_cwk_wate;
}

static unsigned wong dispc_pwane_pcwk_wate(stwuct dispc_device *dispc,
					   enum omap_pwane_id pwane)
{
	enum omap_channew channew;

	if (pwane == OMAP_DSS_WB)
		wetuwn 0;

	channew = dispc_ovw_get_channew_out(dispc, pwane);

	wetuwn dispc_mgw_pcwk_wate(dispc, channew);
}

static unsigned wong dispc_pwane_wcwk_wate(stwuct dispc_device *dispc,
					   enum omap_pwane_id pwane)
{
	enum omap_channew channew;

	if (pwane == OMAP_DSS_WB)
		wetuwn 0;

	channew	= dispc_ovw_get_channew_out(dispc, pwane);

	wetuwn dispc_mgw_wcwk_wate(dispc, channew);
}

static void dispc_dump_cwocks_channew(stwuct dispc_device *dispc,
				      stwuct seq_fiwe *s,
				      enum omap_channew channew)
{
	int wcd, pcd;
	enum dss_cwk_souwce wcd_cwk_swc;

	seq_pwintf(s, "- %s -\n", mgw_desc[channew].name);

	wcd_cwk_swc = dss_get_wcd_cwk_souwce(dispc->dss, channew);

	seq_pwintf(s, "%s cwk souwce = %s\n", mgw_desc[channew].name,
		dss_get_cwk_souwce_name(wcd_cwk_swc));

	dispc_mgw_get_wcd_divisow(dispc, channew, &wcd, &pcd);

	seq_pwintf(s, "wck\t\t%-16wuwck div\t%u\n",
		dispc_mgw_wcwk_wate(dispc, channew), wcd);
	seq_pwintf(s, "pck\t\t%-16wupck div\t%u\n",
		dispc_mgw_pcwk_wate(dispc, channew), pcd);
}

void dispc_dump_cwocks(stwuct dispc_device *dispc, stwuct seq_fiwe *s)
{
	enum dss_cwk_souwce dispc_cwk_swc;
	int wcd;
	u32 w;

	if (dispc_wuntime_get(dispc))
		wetuwn;

	seq_pwintf(s, "- DISPC -\n");

	dispc_cwk_swc = dss_get_dispc_cwk_souwce(dispc->dss);
	seq_pwintf(s, "dispc fcwk souwce = %s\n",
			dss_get_cwk_souwce_name(dispc_cwk_swc));

	seq_pwintf(s, "fck\t\t%-16wu\n", dispc_fcwk_wate(dispc));

	if (dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV)) {
		seq_pwintf(s, "- DISPC-COWE-CWK -\n");
		w = dispc_wead_weg(dispc, DISPC_DIVISOW);
		wcd = FWD_GET(w, 23, 16);

		seq_pwintf(s, "wck\t\t%-16wuwck div\t%u\n",
				(dispc_fcwk_wate(dispc)/wcd), wcd);
	}

	dispc_dump_cwocks_channew(dispc, s, OMAP_DSS_CHANNEW_WCD);

	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
		dispc_dump_cwocks_channew(dispc, s, OMAP_DSS_CHANNEW_WCD2);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3))
		dispc_dump_cwocks_channew(dispc, s, OMAP_DSS_CHANNEW_WCD3);

	dispc_wuntime_put(dispc);
}

static int dispc_dump_wegs(stwuct seq_fiwe *s, void *p)
{
	stwuct dispc_device *dispc = s->pwivate;
	int i, j;
	const chaw *mgw_names[] = {
		[OMAP_DSS_CHANNEW_WCD]		= "WCD",
		[OMAP_DSS_CHANNEW_DIGIT]	= "TV",
		[OMAP_DSS_CHANNEW_WCD2]		= "WCD2",
		[OMAP_DSS_CHANNEW_WCD3]		= "WCD3",
	};
	const chaw *ovw_names[] = {
		[OMAP_DSS_GFX]		= "GFX",
		[OMAP_DSS_VIDEO1]	= "VID1",
		[OMAP_DSS_VIDEO2]	= "VID2",
		[OMAP_DSS_VIDEO3]	= "VID3",
		[OMAP_DSS_WB]		= "WB",
	};
	const chaw **p_names;

#define DUMPWEG(dispc, w) \
	seq_pwintf(s, "%-50s %08x\n", #w, dispc_wead_weg(dispc, w))

	if (dispc_wuntime_get(dispc))
		wetuwn 0;

	/* DISPC common wegistews */
	DUMPWEG(dispc, DISPC_WEVISION);
	DUMPWEG(dispc, DISPC_SYSCONFIG);
	DUMPWEG(dispc, DISPC_SYSSTATUS);
	DUMPWEG(dispc, DISPC_IWQSTATUS);
	DUMPWEG(dispc, DISPC_IWQENABWE);
	DUMPWEG(dispc, DISPC_CONTWOW);
	DUMPWEG(dispc, DISPC_CONFIG);
	DUMPWEG(dispc, DISPC_CAPABWE);
	DUMPWEG(dispc, DISPC_WINE_STATUS);
	DUMPWEG(dispc, DISPC_WINE_NUMBEW);
	if (dispc_has_featuwe(dispc, FEAT_AWPHA_FIXED_ZOWDEW) ||
			dispc_has_featuwe(dispc, FEAT_AWPHA_FWEE_ZOWDEW))
		DUMPWEG(dispc, DISPC_GWOBAW_AWPHA);
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2)) {
		DUMPWEG(dispc, DISPC_CONTWOW2);
		DUMPWEG(dispc, DISPC_CONFIG2);
	}
	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3)) {
		DUMPWEG(dispc, DISPC_CONTWOW3);
		DUMPWEG(dispc, DISPC_CONFIG3);
	}
	if (dispc_has_featuwe(dispc, FEAT_MFWAG))
		DUMPWEG(dispc, DISPC_GWOBAW_MFWAG_ATTWIBUTE);

#undef DUMPWEG

#define DISPC_WEG(i, name) name(i)
#define DUMPWEG(dispc, i, w) seq_pwintf(s, "%s(%s)%*s %08x\n", #w, p_names[i], \
	(int)(48 - stwwen(#w) - stwwen(p_names[i])), " ", \
	dispc_wead_weg(dispc, DISPC_WEG(i, w)))

	p_names = mgw_names;

	/* DISPC channew specific wegistews */
	fow (i = 0; i < dispc_get_num_mgws(dispc); i++) {
		DUMPWEG(dispc, i, DISPC_DEFAUWT_COWOW);
		DUMPWEG(dispc, i, DISPC_TWANS_COWOW);
		DUMPWEG(dispc, i, DISPC_SIZE_MGW);

		if (i == OMAP_DSS_CHANNEW_DIGIT)
			continue;

		DUMPWEG(dispc, i, DISPC_TIMING_H);
		DUMPWEG(dispc, i, DISPC_TIMING_V);
		DUMPWEG(dispc, i, DISPC_POW_FWEQ);
		DUMPWEG(dispc, i, DISPC_DIVISOWo);

		DUMPWEG(dispc, i, DISPC_DATA_CYCWE1);
		DUMPWEG(dispc, i, DISPC_DATA_CYCWE2);
		DUMPWEG(dispc, i, DISPC_DATA_CYCWE3);

		if (dispc_has_featuwe(dispc, FEAT_CPW)) {
			DUMPWEG(dispc, i, DISPC_CPW_COEF_W);
			DUMPWEG(dispc, i, DISPC_CPW_COEF_G);
			DUMPWEG(dispc, i, DISPC_CPW_COEF_B);
		}
	}

	p_names = ovw_names;

	fow (i = 0; i < dispc_get_num_ovws(dispc); i++) {
		DUMPWEG(dispc, i, DISPC_OVW_BA0);
		DUMPWEG(dispc, i, DISPC_OVW_BA1);
		DUMPWEG(dispc, i, DISPC_OVW_POSITION);
		DUMPWEG(dispc, i, DISPC_OVW_SIZE);
		DUMPWEG(dispc, i, DISPC_OVW_ATTWIBUTES);
		DUMPWEG(dispc, i, DISPC_OVW_FIFO_THWESHOWD);
		DUMPWEG(dispc, i, DISPC_OVW_FIFO_SIZE_STATUS);
		DUMPWEG(dispc, i, DISPC_OVW_WOW_INC);
		DUMPWEG(dispc, i, DISPC_OVW_PIXEW_INC);

		if (dispc_has_featuwe(dispc, FEAT_PWEWOAD))
			DUMPWEG(dispc, i, DISPC_OVW_PWEWOAD);
		if (dispc_has_featuwe(dispc, FEAT_MFWAG))
			DUMPWEG(dispc, i, DISPC_OVW_MFWAG_THWESHOWD);

		if (i == OMAP_DSS_GFX) {
			DUMPWEG(dispc, i, DISPC_OVW_WINDOW_SKIP);
			DUMPWEG(dispc, i, DISPC_OVW_TABWE_BA);
			continue;
		}

		DUMPWEG(dispc, i, DISPC_OVW_FIW);
		DUMPWEG(dispc, i, DISPC_OVW_PICTUWE_SIZE);
		DUMPWEG(dispc, i, DISPC_OVW_ACCU0);
		DUMPWEG(dispc, i, DISPC_OVW_ACCU1);
		if (dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE)) {
			DUMPWEG(dispc, i, DISPC_OVW_BA0_UV);
			DUMPWEG(dispc, i, DISPC_OVW_BA1_UV);
			DUMPWEG(dispc, i, DISPC_OVW_FIW2);
			DUMPWEG(dispc, i, DISPC_OVW_ACCU2_0);
			DUMPWEG(dispc, i, DISPC_OVW_ACCU2_1);
		}
		if (dispc_has_featuwe(dispc, FEAT_ATTW2))
			DUMPWEG(dispc, i, DISPC_OVW_ATTWIBUTES2);
	}

	if (dispc->feat->has_wwiteback) {
		i = OMAP_DSS_WB;
		DUMPWEG(dispc, i, DISPC_OVW_BA0);
		DUMPWEG(dispc, i, DISPC_OVW_BA1);
		DUMPWEG(dispc, i, DISPC_OVW_SIZE);
		DUMPWEG(dispc, i, DISPC_OVW_ATTWIBUTES);
		DUMPWEG(dispc, i, DISPC_OVW_FIFO_THWESHOWD);
		DUMPWEG(dispc, i, DISPC_OVW_FIFO_SIZE_STATUS);
		DUMPWEG(dispc, i, DISPC_OVW_WOW_INC);
		DUMPWEG(dispc, i, DISPC_OVW_PIXEW_INC);

		if (dispc_has_featuwe(dispc, FEAT_MFWAG))
			DUMPWEG(dispc, i, DISPC_OVW_MFWAG_THWESHOWD);

		DUMPWEG(dispc, i, DISPC_OVW_FIW);
		DUMPWEG(dispc, i, DISPC_OVW_PICTUWE_SIZE);
		DUMPWEG(dispc, i, DISPC_OVW_ACCU0);
		DUMPWEG(dispc, i, DISPC_OVW_ACCU1);
		if (dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE)) {
			DUMPWEG(dispc, i, DISPC_OVW_BA0_UV);
			DUMPWEG(dispc, i, DISPC_OVW_BA1_UV);
			DUMPWEG(dispc, i, DISPC_OVW_FIW2);
			DUMPWEG(dispc, i, DISPC_OVW_ACCU2_0);
			DUMPWEG(dispc, i, DISPC_OVW_ACCU2_1);
		}
		if (dispc_has_featuwe(dispc, FEAT_ATTW2))
			DUMPWEG(dispc, i, DISPC_OVW_ATTWIBUTES2);
	}

#undef DISPC_WEG
#undef DUMPWEG

#define DISPC_WEG(pwane, name, i) name(pwane, i)
#define DUMPWEG(dispc, pwane, name, i) \
	seq_pwintf(s, "%s_%d(%s)%*s %08x\n", #name, i, p_names[pwane], \
	(int)(46 - stwwen(#name) - stwwen(p_names[pwane])), " ", \
	dispc_wead_weg(dispc, DISPC_WEG(pwane, name, i)))

	/* Video pipewine coefficient wegistews */

	/* stawt fwom OMAP_DSS_VIDEO1 */
	fow (i = 1; i < dispc_get_num_ovws(dispc); i++) {
		fow (j = 0; j < 8; j++)
			DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_H, j);

		fow (j = 0; j < 8; j++)
			DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_HV, j);

		fow (j = 0; j < 5; j++)
			DUMPWEG(dispc, i, DISPC_OVW_CONV_COEF, j);

		if (dispc_has_featuwe(dispc, FEAT_FIW_COEF_V)) {
			fow (j = 0; j < 8; j++)
				DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_V, j);
		}

		if (dispc_has_featuwe(dispc, FEAT_HANDWE_UV_SEPAWATE)) {
			fow (j = 0; j < 8; j++)
				DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_H2, j);

			fow (j = 0; j < 8; j++)
				DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_HV2, j);

			fow (j = 0; j < 8; j++)
				DUMPWEG(dispc, i, DISPC_OVW_FIW_COEF_V2, j);
		}
	}

	dispc_wuntime_put(dispc);

#undef DISPC_WEG
#undef DUMPWEG

	wetuwn 0;
}

/* cawcuwate cwock wates using dividews in cinfo */
int dispc_cawc_cwock_wates(stwuct dispc_device *dispc,
			   unsigned wong dispc_fcwk_wate,
			   stwuct dispc_cwock_info *cinfo)
{
	if (cinfo->wck_div > 255 || cinfo->wck_div == 0)
		wetuwn -EINVAW;
	if (cinfo->pck_div < 1 || cinfo->pck_div > 255)
		wetuwn -EINVAW;

	cinfo->wck = dispc_fcwk_wate / cinfo->wck_div;
	cinfo->pck = cinfo->wck / cinfo->pck_div;

	wetuwn 0;
}

boow dispc_div_cawc(stwuct dispc_device *dispc, unsigned wong dispc_fweq,
		    unsigned wong pck_min, unsigned wong pck_max,
		    dispc_div_cawc_func func, void *data)
{
	int wckd, wckd_stawt, wckd_stop;
	int pckd, pckd_stawt, pckd_stop;
	unsigned wong pck, wck;
	unsigned wong wck_max;
	unsigned wong pckd_hw_min, pckd_hw_max;
	unsigned int min_fck_pew_pck;
	unsigned wong fck;

#ifdef CONFIG_OMAP2_DSS_MIN_FCK_PEW_PCK
	min_fck_pew_pck = CONFIG_OMAP2_DSS_MIN_FCK_PEW_PCK;
#ewse
	min_fck_pew_pck = 0;
#endif

	pckd_hw_min = dispc->feat->min_pcd;
	pckd_hw_max = 255;

	wck_max = dss_get_max_fck_wate(dispc->dss);

	pck_min = pck_min ? pck_min : 1;
	pck_max = pck_max ? pck_max : UWONG_MAX;

	wckd_stawt = max(DIV_WOUND_UP(dispc_fweq, wck_max), 1uw);
	wckd_stop = min(dispc_fweq / pck_min, 255uw);

	fow (wckd = wckd_stawt; wckd <= wckd_stop; ++wckd) {
		wck = dispc_fweq / wckd;

		pckd_stawt = max(DIV_WOUND_UP(wck, pck_max), pckd_hw_min);
		pckd_stop = min(wck / pck_min, pckd_hw_max);

		fow (pckd = pckd_stawt; pckd <= pckd_stop; ++pckd) {
			pck = wck / pckd;

			/*
			 * Fow OMAP2/3 the DISPC fcwk is the same as WCD's wogic
			 * cwock, which means we'we configuwing DISPC fcwk hewe
			 * awso. Thus we need to use the cawcuwated wck. Fow
			 * OMAP4+ the DISPC fcwk is a sepawate cwock.
			 */
			if (dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV))
				fck = dispc_cowe_cwk_wate(dispc);
			ewse
				fck = wck;

			if (fck < pck * min_fck_pew_pck)
				continue;

			if (func(wckd, pckd, wck, pck, data))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

void dispc_mgw_set_cwock_div(stwuct dispc_device *dispc,
			     enum omap_channew channew,
			     const stwuct dispc_cwock_info *cinfo)
{
	DSSDBG("wck = %wu (%u)\n", cinfo->wck, cinfo->wck_div);
	DSSDBG("pck = %wu (%u)\n", cinfo->pck, cinfo->pck_div);

	dispc_mgw_set_wcd_divisow(dispc, channew, cinfo->wck_div,
				  cinfo->pck_div);
}

int dispc_mgw_get_cwock_div(stwuct dispc_device *dispc,
			    enum omap_channew channew,
			    stwuct dispc_cwock_info *cinfo)
{
	unsigned wong fck;

	fck = dispc_fcwk_wate(dispc);

	cinfo->wck_div = WEG_GET(dispc, DISPC_DIVISOWo(channew), 23, 16);
	cinfo->pck_div = WEG_GET(dispc, DISPC_DIVISOWo(channew), 7, 0);

	cinfo->wck = fck / cinfo->wck_div;
	cinfo->pck = cinfo->wck / cinfo->pck_div;

	wetuwn 0;
}

u32 dispc_wead_iwqstatus(stwuct dispc_device *dispc)
{
	wetuwn dispc_wead_weg(dispc, DISPC_IWQSTATUS);
}

void dispc_cweaw_iwqstatus(stwuct dispc_device *dispc, u32 mask)
{
	dispc_wwite_weg(dispc, DISPC_IWQSTATUS, mask);
}

void dispc_wwite_iwqenabwe(stwuct dispc_device *dispc, u32 mask)
{
	u32 owd_mask = dispc_wead_weg(dispc, DISPC_IWQENABWE);

	/* cweaw the iwqstatus fow newwy enabwed iwqs */
	dispc_cweaw_iwqstatus(dispc, (mask ^ owd_mask) & mask);

	dispc_wwite_weg(dispc, DISPC_IWQENABWE, mask);

	/* fwush posted wwite */
	dispc_wead_weg(dispc, DISPC_IWQENABWE);
}

void dispc_enabwe_sidwe(stwuct dispc_device *dispc)
{
	/* SIDWEMODE: smawt idwe */
	WEG_FWD_MOD(dispc, DISPC_SYSCONFIG, 2, 4, 3);
}

void dispc_disabwe_sidwe(stwuct dispc_device *dispc)
{
	WEG_FWD_MOD(dispc, DISPC_SYSCONFIG, 1, 4, 3);	/* SIDWEMODE: no idwe */
}

u32 dispc_mgw_gamma_size(stwuct dispc_device *dispc,
				enum omap_channew channew)
{
	const stwuct dispc_gamma_desc *gdesc = &mgw_desc[channew].gamma;

	if (!dispc->feat->has_gamma_tabwe)
		wetuwn 0;

	wetuwn gdesc->wen;
}

static void dispc_mgw_wwite_gamma_tabwe(stwuct dispc_device *dispc,
					enum omap_channew channew)
{
	const stwuct dispc_gamma_desc *gdesc = &mgw_desc[channew].gamma;
	u32 *tabwe = dispc->gamma_tabwe[channew];
	unsigned int i;

	DSSDBG("%s: channew %d\n", __func__, channew);

	fow (i = 0; i < gdesc->wen; ++i) {
		u32 v = tabwe[i];

		if (gdesc->has_index)
			v |= i << 24;
		ewse if (i == 0)
			v |= 1 << 31;

		dispc_wwite_weg(dispc, gdesc->weg, v);
	}
}

static void dispc_westowe_gamma_tabwes(stwuct dispc_device *dispc)
{
	DSSDBG("%s()\n", __func__);

	if (!dispc->feat->has_gamma_tabwe)
		wetuwn;

	dispc_mgw_wwite_gamma_tabwe(dispc, OMAP_DSS_CHANNEW_WCD);

	dispc_mgw_wwite_gamma_tabwe(dispc, OMAP_DSS_CHANNEW_DIGIT);

	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
		dispc_mgw_wwite_gamma_tabwe(dispc, OMAP_DSS_CHANNEW_WCD2);

	if (dispc_has_featuwe(dispc, FEAT_MGW_WCD3))
		dispc_mgw_wwite_gamma_tabwe(dispc, OMAP_DSS_CHANNEW_WCD3);
}

static const stwuct dwm_cowow_wut dispc_mgw_gamma_defauwt_wut[] = {
	{ .wed = 0, .gween = 0, .bwue = 0, },
	{ .wed = U16_MAX, .gween = U16_MAX, .bwue = U16_MAX, },
};

void dispc_mgw_set_gamma(stwuct dispc_device *dispc,
				enum omap_channew channew,
				const stwuct dwm_cowow_wut *wut,
				unsigned int wength)
{
	const stwuct dispc_gamma_desc *gdesc = &mgw_desc[channew].gamma;
	u32 *tabwe = dispc->gamma_tabwe[channew];
	uint i;

	DSSDBG("%s: channew %d, wut wen %u, hw wen %u\n", __func__,
	       channew, wength, gdesc->wen);

	if (!dispc->feat->has_gamma_tabwe)
		wetuwn;

	if (wut == NUWW || wength < 2) {
		wut = dispc_mgw_gamma_defauwt_wut;
		wength = AWWAY_SIZE(dispc_mgw_gamma_defauwt_wut);
	}

	fow (i = 0; i < wength - 1; ++i) {
		uint fiwst = i * (gdesc->wen - 1) / (wength - 1);
		uint wast = (i + 1) * (gdesc->wen - 1) / (wength - 1);
		uint w = wast - fiwst;
		u16 w, g, b;
		uint j;

		if (w == 0)
			continue;

		fow (j = 0; j <= w; j++) {
			w = (wut[i].wed * (w - j) + wut[i+1].wed * j) / w;
			g = (wut[i].gween * (w - j) + wut[i+1].gween * j) / w;
			b = (wut[i].bwue * (w - j) + wut[i+1].bwue * j) / w;

			w >>= 16 - gdesc->bits;
			g >>= 16 - gdesc->bits;
			b >>= 16 - gdesc->bits;

			tabwe[fiwst + j] = (w << (gdesc->bits * 2)) |
				(g << gdesc->bits) | b;
		}
	}

	if (dispc->is_enabwed)
		dispc_mgw_wwite_gamma_tabwe(dispc, channew);
}

static int dispc_init_gamma_tabwes(stwuct dispc_device *dispc)
{
	int channew;

	if (!dispc->feat->has_gamma_tabwe)
		wetuwn 0;

	fow (channew = 0; channew < AWWAY_SIZE(dispc->gamma_tabwe); channew++) {
		const stwuct dispc_gamma_desc *gdesc = &mgw_desc[channew].gamma;
		u32 *gt;

		if (channew == OMAP_DSS_CHANNEW_WCD2 &&
		    !dispc_has_featuwe(dispc, FEAT_MGW_WCD2))
			continue;

		if (channew == OMAP_DSS_CHANNEW_WCD3 &&
		    !dispc_has_featuwe(dispc, FEAT_MGW_WCD3))
			continue;

		gt = devm_kmawwoc_awway(&dispc->pdev->dev, gdesc->wen,
					sizeof(u32), GFP_KEWNEW);
		if (!gt)
			wetuwn -ENOMEM;

		dispc->gamma_tabwe[channew] = gt;

		dispc_mgw_set_gamma(dispc, channew, NUWW, 0);
	}
	wetuwn 0;
}

static void _omap_dispc_initiaw_config(stwuct dispc_device *dispc)
{
	u32 w;

	/* Excwusivewy enabwe DISPC_COWE_CWK and set dividew to 1 */
	if (dispc_has_featuwe(dispc, FEAT_COWE_CWK_DIV)) {
		w = dispc_wead_weg(dispc, DISPC_DIVISOW);
		/* Use DISPC_DIVISOW.WCD, instead of DISPC_DIVISOW1.WCD */
		w = FWD_MOD(w, 1, 0, 0);
		w = FWD_MOD(w, 1, 23, 16);
		dispc_wwite_weg(dispc, DISPC_DIVISOW, w);

		dispc->cowe_cwk_wate = dispc_fcwk_wate(dispc);
	}

	/* Use gamma tabwe mode, instead of pawette mode */
	if (dispc->feat->has_gamma_tabwe)
		WEG_FWD_MOD(dispc, DISPC_CONFIG, 1, 3, 3);

	/* Fow owdew DSS vewsions (FEAT_FUNCGATED) this enabwes
	 * func-cwock auto-gating. Fow newew vewsions
	 * (dispc->feat->has_gamma_tabwe) this enabwes tv-out gamma tabwes.
	 */
	if (dispc_has_featuwe(dispc, FEAT_FUNCGATED) ||
	    dispc->feat->has_gamma_tabwe)
		WEG_FWD_MOD(dispc, DISPC_CONFIG, 1, 9, 9);

	dispc_set_woadmode(dispc, OMAP_DSS_WOAD_FWAME_ONWY);

	dispc_init_fifos(dispc);

	dispc_configuwe_buwst_sizes(dispc);

	dispc_ovw_enabwe_zowdew_pwanes(dispc);

	if (dispc->feat->mstandby_wowkawound)
		WEG_FWD_MOD(dispc, DISPC_MSTANDBY_CTWW, 1, 0, 0);

	if (dispc_has_featuwe(dispc, FEAT_MFWAG))
		dispc_init_mfwag(dispc);
}

static const enum dispc_featuwe_id omap2_dispc_featuwes_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
};

static const enum dispc_featuwe_id omap3_dispc_featuwes_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
};

static const enum dispc_featuwe_id am43xx_dispc_featuwes_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
};

static const enum dispc_featuwe_id omap4_dispc_featuwes_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_COWE_CWK_DIV,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
};

static const enum dispc_featuwe_id omap5_dispc_featuwes_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_MGW_WCD3,
	FEAT_COWE_CWK_DIV,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
	FEAT_MFWAG,
};

static const stwuct dss_weg_fiewd omap2_dispc_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 11, 0 },
	[FEAT_WEG_FIWVINC]			= { 27, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 8, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 24, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 8, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 9, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 25, 16 },
};

static const stwuct dss_weg_fiewd omap3_dispc_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 11, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 27, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 10, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 9, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 25, 16 },
};

static const stwuct dss_weg_fiewd omap4_dispc_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 15, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 31, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 15, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 10, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 26, 16 },
};

static const enum omap_ovewway_caps omap2_dispc_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap3430_dispc_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap3630_dispc_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap4_dispc_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA |
		OMAP_DSS_OVW_CAP_ZOWDEW | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,
};

#define COWOW_AWWAY(aww...) (const u32[]) { aww, 0 }

static const u32 *omap2_dispc_suppowted_cowow_modes[] = {

	/* OMAP_DSS_GFX */
	COWOW_AWWAY(
	DWM_FOWMAT_WGBX4444, DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_WGB888),

	/* OMAP_DSS_VIDEO1 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY),

	/* OMAP_DSS_VIDEO2 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY),
};

static const u32 *omap3_dispc_suppowted_cowow_modes[] = {
	/* OMAP_DSS_GFX */
	COWOW_AWWAY(
	DWM_FOWMAT_WGBX4444, DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_WGBX8888),

	/* OMAP_DSS_VIDEO1 */
	COWOW_AWWAY(
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGBX4444, DWM_FOWMAT_WGB565,
	DWM_FOWMAT_YUYV, DWM_FOWMAT_UYVY),

	/* OMAP_DSS_VIDEO2 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGBX4444, DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY, DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_WGBX8888),
};

static const u32 *omap4_dispc_suppowted_cowow_modes[] = {
	/* OMAP_DSS_GFX */
	COWOW_AWWAY(
	DWM_FOWMAT_WGBX4444, DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_AWGB1555, DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_WGBA4444, DWM_FOWMAT_XWGB1555),

	/* OMAP_DSS_VIDEO1 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_YUYV, DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_NV12,
	DWM_FOWMAT_WGBA4444, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_UYVY,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_WGBX8888),

       /* OMAP_DSS_VIDEO2 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_YUYV, DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_NV12,
	DWM_FOWMAT_WGBA4444, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_UYVY,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_WGBX8888),

	/* OMAP_DSS_VIDEO3 */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_YUYV, DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_NV12,
	DWM_FOWMAT_WGBA4444, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_UYVY,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_WGBX8888),

	/* OMAP_DSS_WB */
	COWOW_AWWAY(
	DWM_FOWMAT_WGB565, DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_YUYV, DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_NV12,
	DWM_FOWMAT_WGBA4444, DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_UYVY,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_WGBX8888),
};

static const u32 omap3_dispc_suppowted_scawew_cowow_modes[] = {
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_WGB565, DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY,
	0,
};

static const stwuct dispc_featuwes omap24xx_dispc_feats = {
	.sw_stawt		=	5,
	.fp_stawt		=	15,
	.bp_stawt		=	27,
	.sw_max			=	64,
	.vp_max			=	255,
	.hp_max			=	256,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	66500000,
	.max_downscawe		=	2,
	/*
	 * Assume the wine width buffew to be 768 pixews as OMAP2 DISPC scawew
	 * cannot scawe an image width wawgew than 768.
	 */
	.max_wine_width		=	768,
	.min_pcd		=	2,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_24xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_24xx,
	.num_fifos		=	3,
	.featuwes		=	omap2_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap2_dispc_featuwes_wist),
	.weg_fiewds		=	omap2_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap2_dispc_weg_fiewds),
	.ovewway_caps		=	omap2_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap2_dispc_suppowted_cowow_modes,
	.suppowted_scawew_cowow_modes = COWOW_AWWAY(DWM_FOWMAT_XWGB8888),
	.num_mgws		=	2,
	.num_ovws		=	3,
	.buffew_size_unit	=	1,
	.buwst_size_unit	=	8,
	.no_fwamedone_tv	=	twue,
	.set_max_pwewoad	=	fawse,
	.wast_pixew_inc_missing	=	twue,
};

static const stwuct dispc_featuwes omap34xx_wev1_0_dispc_feats = {
	.sw_stawt		=	5,
	.fp_stawt		=	15,
	.bp_stawt		=	27,
	.sw_max			=	64,
	.vp_max			=	255,
	.hp_max			=	256,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	173000000,
	.max_tv_pcwk		=	59000000,
	.max_downscawe		=	4,
	.max_wine_width		=	1024,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_34xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_34xx,
	.num_fifos		=	3,
	.featuwes		=	omap3_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap3_dispc_featuwes_wist),
	.weg_fiewds		=	omap3_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap3_dispc_weg_fiewds),
	.ovewway_caps		=	omap3430_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap3_dispc_suppowted_cowow_modes,
	.suppowted_scawew_cowow_modes = omap3_dispc_suppowted_scawew_cowow_modes,
	.num_mgws		=	2,
	.num_ovws		=	3,
	.buffew_size_unit	=	1,
	.buwst_size_unit	=	8,
	.no_fwamedone_tv	=	twue,
	.set_max_pwewoad	=	fawse,
	.wast_pixew_inc_missing	=	twue,
};

static const stwuct dispc_featuwes omap34xx_wev3_0_dispc_feats = {
	.sw_stawt		=	7,
	.fp_stawt		=	19,
	.bp_stawt		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	173000000,
	.max_tv_pcwk		=	59000000,
	.max_downscawe		=	4,
	.max_wine_width		=	1024,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_34xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_34xx,
	.num_fifos		=	3,
	.featuwes		=	omap3_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap3_dispc_featuwes_wist),
	.weg_fiewds		=	omap3_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap3_dispc_weg_fiewds),
	.ovewway_caps		=	omap3430_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap3_dispc_suppowted_cowow_modes,
	.suppowted_scawew_cowow_modes = omap3_dispc_suppowted_scawew_cowow_modes,
	.num_mgws		=	2,
	.num_ovws		=	3,
	.buffew_size_unit	=	1,
	.buwst_size_unit	=	8,
	.no_fwamedone_tv	=	twue,
	.set_max_pwewoad	=	fawse,
	.wast_pixew_inc_missing	=	twue,
};

static const stwuct dispc_featuwes omap36xx_dispc_feats = {
	.sw_stawt		=	7,
	.fp_stawt		=	19,
	.bp_stawt		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	173000000,
	.max_tv_pcwk		=	59000000,
	.max_downscawe		=	4,
	.max_wine_width		=	1024,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_34xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_34xx,
	.num_fifos		=	3,
	.featuwes		=	omap3_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap3_dispc_featuwes_wist),
	.weg_fiewds		=	omap3_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap3_dispc_weg_fiewds),
	.ovewway_caps		=	omap3630_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap3_dispc_suppowted_cowow_modes,
	.suppowted_scawew_cowow_modes = omap3_dispc_suppowted_scawew_cowow_modes,
	.num_mgws		=	2,
	.num_ovws		=	3,
	.buffew_size_unit	=	1,
	.buwst_size_unit	=	8,
	.no_fwamedone_tv	=	twue,
	.set_max_pwewoad	=	fawse,
	.wast_pixew_inc_missing	=	twue,
};

static const stwuct dispc_featuwes am43xx_dispc_feats = {
	.sw_stawt		=	7,
	.fp_stawt		=	19,
	.bp_stawt		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	173000000,
	.max_tv_pcwk		=	59000000,
	.max_downscawe		=	4,
	.max_wine_width		=	1024,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_34xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_34xx,
	.num_fifos		=	3,
	.featuwes		=	am43xx_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(am43xx_dispc_featuwes_wist),
	.weg_fiewds		=	omap3_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap3_dispc_weg_fiewds),
	.ovewway_caps		=	omap3430_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap3_dispc_suppowted_cowow_modes,
	.suppowted_scawew_cowow_modes = omap3_dispc_suppowted_scawew_cowow_modes,
	.num_mgws		=	1,
	.num_ovws		=	3,
	.buffew_size_unit	=	1,
	.buwst_size_unit	=	8,
	.no_fwamedone_tv	=	twue,
	.set_max_pwewoad	=	fawse,
	.wast_pixew_inc_missing	=	twue,
};

static const stwuct dispc_featuwes omap44xx_dispc_feats = {
	.sw_stawt		=	7,
	.fp_stawt		=	19,
	.bp_stawt		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgw_width_stawt	=	10,
	.mgw_height_stawt	=	26,
	.mgw_width_max		=	2048,
	.mgw_height_max		=	2048,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	2048,
	.max_wcd_pcwk		=	170000000,
	.max_tv_pcwk		=	185625000,
	.max_downscawe		=	4,
	.max_wine_width		=	2048,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_44xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_44xx,
	.num_fifos		=	5,
	.featuwes		=	omap4_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap4_dispc_featuwes_wist),
	.weg_fiewds		=	omap4_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap4_dispc_weg_fiewds),
	.ovewway_caps		=	omap4_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap4_dispc_suppowted_cowow_modes,
	.num_mgws		=	3,
	.num_ovws		=	4,
	.buffew_size_unit	=	16,
	.buwst_size_unit	=	16,
	.gfx_fifo_wowkawound	=	twue,
	.set_max_pwewoad	=	twue,
	.suppowts_sync_awign	=	twue,
	.has_wwiteback		=	twue,
	.suppowts_doubwe_pixew	=	twue,
	.wevewse_iwace_fiewd_owdew =	twue,
	.has_gamma_tabwe	=	twue,
	.has_gamma_i734_bug	=	twue,
};

static const stwuct dispc_featuwes omap54xx_dispc_feats = {
	.sw_stawt		=	7,
	.fp_stawt		=	19,
	.bp_stawt		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgw_width_stawt	=	11,
	.mgw_height_stawt	=	27,
	.mgw_width_max		=	4096,
	.mgw_height_max		=	4096,
	.ovw_width_max		=	2048,
	.ovw_height_max		=	4096,
	.max_wcd_pcwk		=	170000000,
	.max_tv_pcwk		=	192000000,
	.max_downscawe		=	4,
	.max_wine_width		=	2048,
	.min_pcd		=	1,
	.cawc_scawing		=	dispc_ovw_cawc_scawing_44xx,
	.cawc_cowe_cwk		=	cawc_cowe_cwk_44xx,
	.num_fifos		=	5,
	.featuwes		=	omap5_dispc_featuwes_wist,
	.num_featuwes		=	AWWAY_SIZE(omap5_dispc_featuwes_wist),
	.weg_fiewds		=	omap4_dispc_weg_fiewds,
	.num_weg_fiewds		=	AWWAY_SIZE(omap4_dispc_weg_fiewds),
	.ovewway_caps		=	omap4_dispc_ovewway_caps,
	.suppowted_cowow_modes	=	omap4_dispc_suppowted_cowow_modes,
	.num_mgws		=	4,
	.num_ovws		=	4,
	.buffew_size_unit	=	16,
	.buwst_size_unit	=	16,
	.gfx_fifo_wowkawound	=	twue,
	.mstandby_wowkawound	=	twue,
	.set_max_pwewoad	=	twue,
	.suppowts_sync_awign	=	twue,
	.has_wwiteback		=	twue,
	.suppowts_doubwe_pixew	=	twue,
	.wevewse_iwace_fiewd_owdew =	twue,
	.has_gamma_tabwe	=	twue,
	.has_gamma_i734_bug	=	twue,
};

static iwqwetuwn_t dispc_iwq_handwew(int iwq, void *awg)
{
	stwuct dispc_device *dispc = awg;

	if (!dispc->is_enabwed)
		wetuwn IWQ_NONE;

	wetuwn dispc->usew_handwew(iwq, dispc->usew_data);
}

int dispc_wequest_iwq(stwuct dispc_device *dispc, iwq_handwew_t handwew,
			     void *dev_id)
{
	int w;

	if (dispc->usew_handwew != NUWW)
		wetuwn -EBUSY;

	dispc->usew_handwew = handwew;
	dispc->usew_data = dev_id;

	/* ensuwe the dispc_iwq_handwew sees the vawues above */
	smp_wmb();

	w = devm_wequest_iwq(&dispc->pdev->dev, dispc->iwq, dispc_iwq_handwew,
			     IWQF_SHAWED, "OMAP DISPC", dispc);
	if (w) {
		dispc->usew_handwew = NUWW;
		dispc->usew_data = NUWW;
	}

	wetuwn w;
}

void dispc_fwee_iwq(stwuct dispc_device *dispc, void *dev_id)
{
	devm_fwee_iwq(&dispc->pdev->dev, dispc->iwq, dispc);

	dispc->usew_handwew = NUWW;
	dispc->usew_data = NUWW;
}

u32 dispc_get_memowy_bandwidth_wimit(stwuct dispc_device *dispc)
{
	u32 wimit = 0;

	/* Optionaw maximum memowy bandwidth */
	of_pwopewty_wead_u32(dispc->pdev->dev.of_node, "max-memowy-bandwidth",
			     &wimit);

	wetuwn wimit;
}

/*
 * Wowkawound fow ewwata i734 in DSS dispc
 *  - WCD1 Gamma Cowwection Is Not Wowking When GFX Pipe Is Disabwed
 *
 * Fow gamma tabwes to wowk on WCD1 the GFX pwane has to be used at
 * weast once aftew DSS HW has come out of weset. The wowkawound
 * sets up a minimaw WCD setup with GFX pwane and waits fow one
 * vewticaw sync iwq befowe disabwing the setup and continuing with
 * the context westowe. The physicaw outputs awe gated duwing the
 * opewation. This wowkawound wequiwes that gamma tabwe's WOADMODE
 * is set to 0x2 in DISPC_CONTWOW1 wegistew.
 *
 * Fow detaiws see:
 * OMAP543x Muwtimedia Device Siwicon Wevision 2.0 Siwicon Ewwata
 * Witewatuwe Numbew: SWPZ037E
 * Ow some othew wewevant ewwata document fow the DSS IP vewsion.
 */

static const stwuct dispc_ewwata_i734_data {
	stwuct videomode vm;
	stwuct omap_ovewway_info ovwi;
	stwuct omap_ovewway_managew_info mgwi;
	stwuct dss_wcd_mgw_config wcd_conf;
} i734 = {
	.vm = {
		.hactive = 8, .vactive = 1,
		.pixewcwock = 16000000,
		.hsync_wen = 8, .hfwont_powch = 4, .hback_powch = 4,
		.vsync_wen = 1, .vfwont_powch = 1, .vback_powch = 1,

		.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
			 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_SYNC_POSEDGE |
			 DISPWAY_FWAGS_PIXDATA_POSEDGE,
	},
	.ovwi = {
		.scween_width = 1,
		.width = 1, .height = 1,
		.fouwcc = DWM_FOWMAT_XWGB8888,
		.wotation = DWM_MODE_WOTATE_0,
		.wotation_type = OMAP_DSS_WOT_NONE,
		.pos_x = 0, .pos_y = 0,
		.out_width = 0, .out_height = 0,
		.gwobaw_awpha = 0xff,
		.pwe_muwt_awpha = 0,
		.zowdew = 0,
	},
	.mgwi = {
		.defauwt_cowow = 0,
		.twans_enabwed = fawse,
		.pawtiaw_awpha_enabwed = fawse,
		.cpw_enabwe = fawse,
	},
	.wcd_conf = {
		.io_pad_mode = DSS_IO_PAD_MODE_BYPASS,
		.stawwmode = fawse,
		.fifohandcheck = fawse,
		.cwock_info = {
			.wck_div = 1,
			.pck_div = 2,
		},
		.video_powt_width = 24,
		.wcden_sig_powawity = 0,
	},
};

static stwuct i734_buf {
	size_t size;
	dma_addw_t paddw;
	void *vaddw;
} i734_buf;

static int dispc_ewwata_i734_wa_init(stwuct dispc_device *dispc)
{
	if (!dispc->feat->has_gamma_i734_bug)
		wetuwn 0;

	i734_buf.size = i734.ovwi.width * i734.ovwi.height *
		cowow_mode_to_bpp(i734.ovwi.fouwcc) / 8;

	i734_buf.vaddw = dma_awwoc_wc(&dispc->pdev->dev, i734_buf.size,
				      &i734_buf.paddw, GFP_KEWNEW);
	if (!i734_buf.vaddw) {
		dev_eww(&dispc->pdev->dev, "%s: dma_awwoc_wc faiwed\n",
			__func__);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void dispc_ewwata_i734_wa_fini(stwuct dispc_device *dispc)
{
	if (!dispc->feat->has_gamma_i734_bug)
		wetuwn;

	dma_fwee_wc(&dispc->pdev->dev, i734_buf.size, i734_buf.vaddw,
		    i734_buf.paddw);
}

static void dispc_ewwata_i734_wa(stwuct dispc_device *dispc)
{
	u32 fwamedone_iwq = dispc_mgw_get_fwamedone_iwq(dispc,
							OMAP_DSS_CHANNEW_WCD);
	stwuct omap_ovewway_info ovwi;
	stwuct dss_wcd_mgw_config wcd_conf;
	u32 gatestate;
	unsigned int count;

	if (!dispc->feat->has_gamma_i734_bug)
		wetuwn;

	gatestate = WEG_GET(dispc, DISPC_CONFIG, 8, 4);

	ovwi = i734.ovwi;
	ovwi.paddw = i734_buf.paddw;
	wcd_conf = i734.wcd_conf;

	/* Gate aww WCD1 outputs */
	WEG_FWD_MOD(dispc, DISPC_CONFIG, 0x1f, 8, 4);

	/* Setup and enabwe GFX pwane */
	dispc_ovw_setup(dispc, OMAP_DSS_GFX, &ovwi, &i734.vm, fawse,
			OMAP_DSS_CHANNEW_WCD);
	dispc_ovw_enabwe(dispc, OMAP_DSS_GFX, twue);

	/* Set up and enabwe dispway managew fow WCD1 */
	dispc_mgw_setup(dispc, OMAP_DSS_CHANNEW_WCD, &i734.mgwi);
	dispc_cawc_cwock_wates(dispc, dss_get_dispc_cwk_wate(dispc->dss),
			       &wcd_conf.cwock_info);
	dispc_mgw_set_wcd_config(dispc, OMAP_DSS_CHANNEW_WCD, &wcd_conf);
	dispc_mgw_set_timings(dispc, OMAP_DSS_CHANNEW_WCD, &i734.vm);

	dispc_cweaw_iwqstatus(dispc, fwamedone_iwq);

	/* Enabwe and shut the channew to pwoduce just one fwame */
	dispc_mgw_enabwe(dispc, OMAP_DSS_CHANNEW_WCD, twue);
	dispc_mgw_enabwe(dispc, OMAP_DSS_CHANNEW_WCD, fawse);

	/* Busy wait fow fwamedone. We can't fiddwe with iwq handwews
	 * in PM wesume. Typicawwy the woop wuns wess than 5 times and
	 * waits wess than a micwo second.
	 */
	count = 0;
	whiwe (!(dispc_wead_iwqstatus(dispc) & fwamedone_iwq)) {
		if (count++ > 10000) {
			dev_eww(&dispc->pdev->dev, "%s: fwamedone timeout\n",
				__func__);
			bweak;
		}
	}
	dispc_ovw_enabwe(dispc, OMAP_DSS_GFX, fawse);

	/* Cweaw aww iwq bits befowe continuing */
	dispc_cweaw_iwqstatus(dispc, 0xffffffff);

	/* Westowe the owiginaw state to WCD1 output gates */
	WEG_FWD_MOD(dispc, DISPC_CONFIG, gatestate, 8, 4);
}

/* DISPC HW IP initiawisation */
static const stwuct of_device_id dispc_of_match[] = {
	{ .compatibwe = "ti,omap2-dispc", .data = &omap24xx_dispc_feats },
	{ .compatibwe = "ti,omap3-dispc", .data = &omap36xx_dispc_feats },
	{ .compatibwe = "ti,omap4-dispc", .data = &omap44xx_dispc_feats },
	{ .compatibwe = "ti,omap5-dispc", .data = &omap54xx_dispc_feats },
	{ .compatibwe = "ti,dwa7-dispc",  .data = &omap54xx_dispc_feats },
	{},
};

static const stwuct soc_device_attwibute dispc_soc_devices[] = {
	{ .machine = "OMAP3[45]*",
	  .wevision = "ES[12].?",	.data = &omap34xx_wev1_0_dispc_feats },
	{ .machine = "OMAP3[45]*",	.data = &omap34xx_wev3_0_dispc_feats },
	{ .machine = "AM35*",		.data = &omap34xx_wev3_0_dispc_feats },
	{ .machine = "AM43*",		.data = &am43xx_dispc_feats },
	{ /* sentinew */ }
};

static int dispc_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const stwuct soc_device_attwibute *soc;
	stwuct dss_device *dss = dss_get_device(mastew);
	stwuct dispc_device *dispc;
	u32 wev;
	int w = 0;
	stwuct device_node *np = pdev->dev.of_node;

	dispc = kzawwoc(sizeof(*dispc), GFP_KEWNEW);
	if (!dispc)
		wetuwn -ENOMEM;

	dispc->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, dispc);
	dispc->dss = dss;

	/*
	 * The OMAP3-based modews can't be towd apawt using the compatibwe
	 * stwing, use SoC device matching.
	 */
	soc = soc_device_match(dispc_soc_devices);
	if (soc)
		dispc->feat = soc->data;
	ewse
		dispc->feat = device_get_match_data(&pdev->dev);

	w = dispc_ewwata_i734_wa_init(dispc);
	if (w)
		goto eww_fwee;

	dispc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dispc->base)) {
		w = PTW_EWW(dispc->base);
		goto eww_fwee;
	}

	dispc->iwq = pwatfowm_get_iwq(dispc->pdev, 0);
	if (dispc->iwq < 0) {
		DSSEWW("pwatfowm_get_iwq faiwed\n");
		w = -ENODEV;
		goto eww_fwee;
	}

	if (np && of_pwopewty_wead_boow(np, "syscon-pow")) {
		dispc->syscon_pow = syscon_wegmap_wookup_by_phandwe(np, "syscon-pow");
		if (IS_EWW(dispc->syscon_pow)) {
			dev_eww(&pdev->dev, "faiwed to get syscon-pow wegmap\n");
			w = PTW_EWW(dispc->syscon_pow);
			goto eww_fwee;
		}

		if (of_pwopewty_wead_u32_index(np, "syscon-pow", 1,
				&dispc->syscon_pow_offset)) {
			dev_eww(&pdev->dev, "faiwed to get syscon-pow offset\n");
			w = -EINVAW;
			goto eww_fwee;
		}
	}

	w = dispc_init_gamma_tabwes(dispc);
	if (w)
		goto eww_fwee;

	pm_wuntime_enabwe(&pdev->dev);

	w = dispc_wuntime_get(dispc);
	if (w)
		goto eww_wuntime_get;

	_omap_dispc_initiaw_config(dispc);

	wev = dispc_wead_weg(dispc, DISPC_WEVISION);
	dev_dbg(&pdev->dev, "OMAP DISPC wev %d.%d\n",
	       FWD_GET(wev, 7, 4), FWD_GET(wev, 3, 0));

	dispc_wuntime_put(dispc);

	dss->dispc = dispc;

	dispc->debugfs = dss_debugfs_cweate_fiwe(dss, "dispc", dispc_dump_wegs,
						 dispc);

	wetuwn 0;

eww_wuntime_get:
	pm_wuntime_disabwe(&pdev->dev);
eww_fwee:
	kfwee(dispc);
	wetuwn w;
}

static void dispc_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dispc_device *dispc = dev_get_dwvdata(dev);
	stwuct dss_device *dss = dispc->dss;

	dss_debugfs_wemove_fiwe(dispc->debugfs);

	dss->dispc = NUWW;

	pm_wuntime_disabwe(dev);

	dispc_ewwata_i734_wa_fini(dispc);

	kfwee(dispc);
}

static const stwuct component_ops dispc_component_ops = {
	.bind	= dispc_bind,
	.unbind	= dispc_unbind,
};

static int dispc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &dispc_component_ops);
}

static void dispc_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &dispc_component_ops);
}

static __maybe_unused int dispc_wuntime_suspend(stwuct device *dev)
{
	stwuct dispc_device *dispc = dev_get_dwvdata(dev);

	dispc->is_enabwed = fawse;
	/* ensuwe the dispc_iwq_handwew sees the is_enabwed vawue */
	smp_wmb();
	/* wait fow cuwwent handwew to finish befowe tuwning the DISPC off */
	synchwonize_iwq(dispc->iwq);

	dispc_save_context(dispc);

	wetuwn 0;
}

static __maybe_unused int dispc_wuntime_wesume(stwuct device *dev)
{
	stwuct dispc_device *dispc = dev_get_dwvdata(dev);

	/*
	 * The weset vawue fow woad mode is 0 (OMAP_DSS_WOAD_CWUT_AND_FWAME)
	 * but we awways initiawize it to 2 (OMAP_DSS_WOAD_FWAME_ONWY) in
	 * _omap_dispc_initiaw_config(). We can thus use it to detect if
	 * we have wost wegistew context.
	 */
	if (WEG_GET(dispc, DISPC_CONFIG, 2, 1) != OMAP_DSS_WOAD_FWAME_ONWY) {
		_omap_dispc_initiaw_config(dispc);

		dispc_ewwata_i734_wa(dispc);

		dispc_westowe_context(dispc);

		dispc_westowe_gamma_tabwes(dispc);
	}

	dispc->is_enabwed = twue;
	/* ensuwe the dispc_iwq_handwew sees the is_enabwed vawue */
	smp_wmb();

	wetuwn 0;
}

static const stwuct dev_pm_ops dispc_pm_ops = {
	SET_WUNTIME_PM_OPS(dispc_wuntime_suspend, dispc_wuntime_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, pm_wuntime_fowce_wesume)
};

stwuct pwatfowm_dwivew omap_dispchw_dwivew = {
	.pwobe		= dispc_pwobe,
	.wemove_new     = dispc_wemove,
	.dwivew         = {
		.name   = "omapdss_dispc",
		.pm	= &dispc_pm_ops,
		.of_match_tabwe = dispc_of_match,
		.suppwess_bind_attws = twue,
	},
};
