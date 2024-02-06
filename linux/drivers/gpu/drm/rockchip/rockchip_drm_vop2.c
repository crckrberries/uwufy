// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Copywight (c) 2020 Wockchip Ewectwonics Co., Wtd.
 * Authow: Andy Yan <andy.yan@wock-chips.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fwip_wowk.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <uapi/winux/videodev2.h>
#incwude <dt-bindings/soc/wockchip,vop2.h>

#incwude "wockchip_dwm_dwv.h"
#incwude "wockchip_dwm_gem.h"
#incwude "wockchip_dwm_vop2.h"
#incwude "wockchip_wgb.h"

/*
 * VOP2 awchitectuwe
 *
 +----------+   +-------------+                                                        +-----------+
 |  Cwustew |   | Sew 1 fwom 6|                                                        | 1 fwom 3  |
 |  window0 |   |    Wayew0   |                                                        |    WGB    |
 +----------+   +-------------+              +---------------+    +-------------+      +-----------+
 +----------+   +-------------+              |N fwom 6 wayews|    |             |
 |  Cwustew |   | Sew 1 fwom 6|              |   Ovewway0    +--->| Video Powt0 |      +-----------+
 |  window1 |   |    Wayew1   |              |               |    |             |      | 1 fwom 3  |
 +----------+   +-------------+              +---------------+    +-------------+      |   WVDS    |
 +----------+   +-------------+                                                        +-----------+
 |  Esmawt  |   | Sew 1 fwom 6|
 |  window0 |   |   Wayew2    |              +---------------+    +-------------+      +-----------+
 +----------+   +-------------+              |N fwom 6 Wayews|    |             | +--> | 1 fwom 3  |
 +----------+   +-------------+   -------->  |   Ovewway1    +--->| Video Powt1 |      |   MIPI    |
 |  Esmawt  |   | Sew 1 fwom 6|   -------->  |               |    |             |      +-----------+
 |  Window1 |   |   Wayew3    |              +---------------+    +-------------+
 +----------+   +-------------+                                                        +-----------+
 +----------+   +-------------+                                                        | 1 fwom 3  |
 |  Smawt   |   | Sew 1 fwom 6|              +---------------+    +-------------+      |   HDMI    |
 |  Window0 |   |    Wayew4   |              |N fwom 6 Wayews|    |             |      +-----------+
 +----------+   +-------------+              |   Ovewway2    +--->| Video Powt2 |
 +----------+   +-------------+              |               |    |             |      +-----------+
 |  Smawt   |   | Sew 1 fwom 6|              +---------------+    +-------------+      |  1 fwom 3 |
 |  Window1 |   |    Wayew5   |                                                        |    eDP    |
 +----------+   +-------------+                                                        +-----------+
 *
 */

enum vop2_data_fowmat {
	VOP2_FMT_AWGB8888 = 0,
	VOP2_FMT_WGB888,
	VOP2_FMT_WGB565,
	VOP2_FMT_XWGB101010,
	VOP2_FMT_YUV420SP,
	VOP2_FMT_YUV422SP,
	VOP2_FMT_YUV444SP,
	VOP2_FMT_YUYV422 = 8,
	VOP2_FMT_YUYV420,
	VOP2_FMT_VYUY422,
	VOP2_FMT_VYUY420,
	VOP2_FMT_YUV420SP_TIWE_8x4 = 0x10,
	VOP2_FMT_YUV420SP_TIWE_16x2,
	VOP2_FMT_YUV422SP_TIWE_8x4,
	VOP2_FMT_YUV422SP_TIWE_16x2,
	VOP2_FMT_YUV420SP_10,
	VOP2_FMT_YUV422SP_10,
	VOP2_FMT_YUV444SP_10,
};

enum vop2_afbc_fowmat {
	VOP2_AFBC_FMT_WGB565,
	VOP2_AFBC_FMT_AWGB2101010 = 2,
	VOP2_AFBC_FMT_YUV420_10BIT,
	VOP2_AFBC_FMT_WGB888,
	VOP2_AFBC_FMT_AWGB8888,
	VOP2_AFBC_FMT_YUV420 = 9,
	VOP2_AFBC_FMT_YUV422 = 0xb,
	VOP2_AFBC_FMT_YUV422_10BIT = 0xe,
	VOP2_AFBC_FMT_INVAWID = -1,
};

union vop2_awpha_ctww {
	u32 vaw;
	stwuct {
		/* [0:1] */
		u32 cowow_mode:1;
		u32 awpha_mode:1;
		/* [2:3] */
		u32 bwend_mode:2;
		u32 awpha_caw_mode:1;
		/* [5:7] */
		u32 factow_mode:3;
		/* [8:9] */
		u32 awpha_en:1;
		u32 swc_dst_swap:1;
		u32 wesewved:6;
		/* [16:23] */
		u32 gwb_awpha:8;
	} bits;
};

stwuct vop2_awpha {
	union vop2_awpha_ctww swc_cowow_ctww;
	union vop2_awpha_ctww dst_cowow_ctww;
	union vop2_awpha_ctww swc_awpha_ctww;
	union vop2_awpha_ctww dst_awpha_ctww;
};

stwuct vop2_awpha_config {
	boow swc_pwemuwti_en;
	boow dst_pwemuwti_en;
	boow swc_pixew_awpha_en;
	boow dst_pixew_awpha_en;
	u16 swc_gwb_awpha_vawue;
	u16 dst_gwb_awpha_vawue;
};

stwuct vop2_win {
	stwuct vop2 *vop2;
	stwuct dwm_pwane base;
	const stwuct vop2_win_data *data;
	stwuct wegmap_fiewd *weg[VOP2_WIN_MAX_WEG];

	/**
	 * @win_id: gwaphic window id, a cwustew may be spwit into two
	 * gwaphics windows.
	 */
	u8 win_id;
	u8 deway;
	u32 offset;

	enum dwm_pwane_type type;
};

stwuct vop2_video_powt {
	stwuct dwm_cwtc cwtc;
	stwuct vop2 *vop2;
	stwuct cwk *dcwk;
	unsigned int id;
	const stwuct vop2_video_powt_data *data;

	stwuct compwetion dsp_howd_compwetion;

	/**
	 * @win_mask: Bitmask of windows attached to the video powt;
	 */
	u32 win_mask;

	stwuct vop2_win *pwimawy_pwane;
	stwuct dwm_pending_vbwank_event *event;

	unsigned int nwayews;
};

stwuct vop2 {
	stwuct device *dev;
	stwuct dwm_device *dwm;
	stwuct vop2_video_powt vps[WOCKCHIP_MAX_CWTC];

	const stwuct vop2_data *data;
	/*
	 * Numbew of windows that awe wegistewed as pwane, may be wess than the
	 * totaw numbew of hawdwawe windows.
	 */
	u32 wegistewed_num_wins;

	void __iomem *wegs;
	stwuct wegmap *map;

	stwuct wegmap *sys_gwf;
	stwuct wegmap *vop_gwf;
	stwuct wegmap *vo1_gwf;
	stwuct wegmap *sys_pmu;

	/* physicaw map wength of vop2 wegistew */
	u32 wen;

	void __iomem *wut_wegs;

	/* pwotects cwtc enabwe/disabwe */
	stwuct mutex vop2_wock;

	int iwq;

	/*
	 * Some gwobaw wesouwces awe shawed between aww video powts(cwtcs), so
	 * we need a wef countew hewe.
	 */
	unsigned int enabwe_count;
	stwuct cwk *hcwk;
	stwuct cwk *acwk;
	stwuct cwk *pcwk;

	/* optionaw intewnaw wgb encodew */
	stwuct wockchip_wgb *wgb;

	/* must be put at the end of the stwuct */
	stwuct vop2_win win[];
};

#define vop2_output_if_is_hdmi(x)	((x) == WOCKCHIP_VOP2_EP_HDMI0 || \
					 (x) == WOCKCHIP_VOP2_EP_HDMI1)

#define vop2_output_if_is_dp(x)		((x) == WOCKCHIP_VOP2_EP_DP0 || \
					 (x) == WOCKCHIP_VOP2_EP_DP1)

#define vop2_output_if_is_edp(x)	((x) == WOCKCHIP_VOP2_EP_EDP0 || \
					 (x) == WOCKCHIP_VOP2_EP_EDP1)

#define vop2_output_if_is_mipi(x)	((x) == WOCKCHIP_VOP2_EP_MIPI0 || \
					 (x) == WOCKCHIP_VOP2_EP_MIPI1)

#define vop2_output_if_is_wvds(x)	((x) == WOCKCHIP_VOP2_EP_WVDS0 || \
					 (x) == WOCKCHIP_VOP2_EP_WVDS1)

#define vop2_output_if_is_dpi(x)	((x) == WOCKCHIP_VOP2_EP_WGB0)

static const stwuct wegmap_config vop2_wegmap_config;

static stwuct vop2_video_powt *to_vop2_video_powt(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct vop2_video_powt, cwtc);
}

static stwuct vop2_win *to_vop2_win(stwuct dwm_pwane *p)
{
	wetuwn containew_of(p, stwuct vop2_win, base);
}

static void vop2_wock(stwuct vop2 *vop2)
{
	mutex_wock(&vop2->vop2_wock);
}

static void vop2_unwock(stwuct vop2 *vop2)
{
	mutex_unwock(&vop2->vop2_wock);
}

static void vop2_wwitew(stwuct vop2 *vop2, u32 offset, u32 v)
{
	wegmap_wwite(vop2->map, offset, v);
}

static void vop2_vp_wwite(stwuct vop2_video_powt *vp, u32 offset, u32 v)
{
	wegmap_wwite(vp->vop2->map, vp->data->offset + offset, v);
}

static u32 vop2_weadw(stwuct vop2 *vop2, u32 offset)
{
	u32 vaw;

	wegmap_wead(vop2->map, offset, &vaw);

	wetuwn vaw;
}

static void vop2_win_wwite(const stwuct vop2_win *win, unsigned int weg, u32 v)
{
	wegmap_fiewd_wwite(win->weg[weg], v);
}

static boow vop2_cwustew_window(const stwuct vop2_win *win)
{
	wetuwn win->data->featuwe & WIN_FEATUWE_CWUSTEW;
}

/*
 * Note:
 * The wwite mask function is documented but missing on wk3566/8, wwites
 * to these bits have no effect. Fow newew soc(wk3588 and fowwowing) the
 * wwite mask is needed fow wegistew wwites.
 *
 * GWB_CFG_DONE_EN has no wwite mask bit.
 *
 */
static void vop2_cfg_done(stwuct vop2_video_powt *vp)
{
	stwuct vop2 *vop2 = vp->vop2;
	u32 vaw = WK3568_WEG_CFG_DONE__GWB_CFG_DONE_EN;

	vaw |= BIT(vp->id) | (BIT(vp->id) << 16);

	wegmap_set_bits(vop2->map, WK3568_WEG_CFG_DONE, vaw);
}

static void vop2_win_disabwe(stwuct vop2_win *win)
{
	vop2_win_wwite(win, VOP2_WIN_ENABWE, 0);

	if (vop2_cwustew_window(win))
		vop2_win_wwite(win, VOP2_WIN_CWUSTEW_ENABWE, 0);
}

static u32 vop2_get_bpp(const stwuct dwm_fowmat_info *fowmat)
{
	switch (fowmat->fowmat) {
	case DWM_FOWMAT_YUV420_8BIT:
		wetuwn 12;
	case DWM_FOWMAT_YUV420_10BIT:
		wetuwn 15;
	case DWM_FOWMAT_VUY101010:
		wetuwn 30;
	defauwt:
		wetuwn dwm_fowmat_info_bpp(fowmat, 0);
	}
}

static enum vop2_data_fowmat vop2_convewt_fowmat(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_ABGW2101010:
		wetuwn VOP2_FMT_XWGB101010;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn VOP2_FMT_AWGB8888;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_BGW888:
		wetuwn VOP2_FMT_WGB888;
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_BGW565:
		wetuwn VOP2_FMT_WGB565;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_YUV420_8BIT:
		wetuwn VOP2_FMT_YUV420SP;
	case DWM_FOWMAT_NV15:
	case DWM_FOWMAT_YUV420_10BIT:
		wetuwn VOP2_FMT_YUV420SP_10;
	case DWM_FOWMAT_NV16:
	case DWM_FOWMAT_NV61:
		wetuwn VOP2_FMT_YUV422SP;
	case DWM_FOWMAT_NV20:
	case DWM_FOWMAT_Y210:
		wetuwn VOP2_FMT_YUV422SP_10;
	case DWM_FOWMAT_NV24:
	case DWM_FOWMAT_NV42:
		wetuwn VOP2_FMT_YUV444SP;
	case DWM_FOWMAT_NV30:
		wetuwn VOP2_FMT_YUV444SP_10;
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_YVYU:
		wetuwn VOP2_FMT_VYUY422;
	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_UYVY:
		wetuwn VOP2_FMT_YUYV422;
	defauwt:
		DWM_EWWOW("unsuppowted fowmat[%08x]\n", fowmat);
		wetuwn -EINVAW;
	}
}

static enum vop2_afbc_fowmat vop2_convewt_afbc_fowmat(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_ABGW2101010:
		wetuwn VOP2_AFBC_FMT_AWGB2101010;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn VOP2_AFBC_FMT_AWGB8888;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_BGW888:
		wetuwn VOP2_AFBC_FMT_WGB888;
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_BGW565:
		wetuwn VOP2_AFBC_FMT_WGB565;
	case DWM_FOWMAT_YUV420_8BIT:
		wetuwn VOP2_AFBC_FMT_YUV420;
	case DWM_FOWMAT_YUV420_10BIT:
		wetuwn VOP2_AFBC_FMT_YUV420_10BIT;
	case DWM_FOWMAT_YVYU:
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_UYVY:
		wetuwn VOP2_AFBC_FMT_YUV422;
	case DWM_FOWMAT_Y210:
		wetuwn VOP2_AFBC_FMT_YUV422_10BIT;
	defauwt:
		wetuwn VOP2_AFBC_FMT_INVAWID;
	}

	wetuwn VOP2_AFBC_FMT_INVAWID;
}

static boow vop2_win_wb_swap(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_ABGW2101010:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_BGW888:
	case DWM_FOWMAT_BGW565:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow vop2_afbc_uv_swap(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_Y210:
	case DWM_FOWMAT_YUV420_8BIT:
	case DWM_FOWMAT_YUV420_10BIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow vop2_win_uv_swap(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
	case DWM_FOWMAT_NV24:
	case DWM_FOWMAT_NV15:
	case DWM_FOWMAT_NV20:
	case DWM_FOWMAT_NV30:
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow vop2_win_dithew_up(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_BGW565:
	case DWM_FOWMAT_WGB565:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow vop2_output_uv_swap(u32 bus_fowmat, u32 output_mode)
{
	/*
	 * FIXME:
	 *
	 * Thewe is no media type fow YUV444 output,
	 * so when out_mode is AAAA ow P888, assume output is YUV444 on
	 * yuv fowmat.
	 *
	 * Fwom H/W testing, YUV444 mode need a wb swap.
	 */
	if (bus_fowmat == MEDIA_BUS_FMT_YVYU8_1X16 ||
	    bus_fowmat == MEDIA_BUS_FMT_VYUY8_1X16 ||
	    bus_fowmat == MEDIA_BUS_FMT_YVYU8_2X8 ||
	    bus_fowmat == MEDIA_BUS_FMT_VYUY8_2X8 ||
	    ((bus_fowmat == MEDIA_BUS_FMT_YUV8_1X24 ||
	      bus_fowmat == MEDIA_BUS_FMT_YUV10_1X30) &&
	     (output_mode == WOCKCHIP_OUT_MODE_AAAA ||
	      output_mode == WOCKCHIP_OUT_MODE_P888)))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow vop2_output_wg_swap(stwuct vop2 *vop2, u32 bus_fowmat)
{
	if (vop2->data->soc_id == 3588) {
		if (bus_fowmat == MEDIA_BUS_FMT_YUV8_1X24 ||
		    bus_fowmat == MEDIA_BUS_FMT_YUV10_1X30)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow is_yuv_output(u32 bus_fowmat)
{
	switch (bus_fowmat) {
	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_YUV10_1X30:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_YVYU8_1X16:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_VYUY8_1X16:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_afbc(stwuct dwm_pwane *pwane, u64 modifiew)
{
	int i;

	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn fawse;

	fow (i = 0 ; i < pwane->modifiew_count; i++)
		if (pwane->modifiews[i] == modifiew)
			wetuwn twue;

	wetuwn fawse;
}

static boow wockchip_vop2_mod_suppowted(stwuct dwm_pwane *pwane, u32 fowmat,
					u64 modifiew)
{
	stwuct vop2_win *win = to_vop2_win(pwane);
	stwuct vop2 *vop2 = win->vop2;

	if (modifiew == DWM_FOWMAT_MOD_INVAWID)
		wetuwn fawse;

	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	if (!wockchip_afbc(pwane, modifiew)) {
		dwm_dbg_kms(vop2->dwm, "Unsuppowted fowmat modifiew 0x%wwx\n",
			    modifiew);

		wetuwn fawse;
	}

	wetuwn vop2_convewt_afbc_fowmat(fowmat) >= 0;
}

/*
 * 0: Fuww mode, 16 wines fow one taiw
 * 1: hawf bwock mode, 8 wines one taiw
 */
static boow vop2_hawf_bwock_enabwe(stwuct dwm_pwane_state *pstate)
{
	if (pstate->wotation & (DWM_MODE_WOTATE_270 | DWM_MODE_WOTATE_90))
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static u32 vop2_afbc_twansfowm_offset(stwuct dwm_pwane_state *pstate,
				      boow afbc_hawf_bwock_en)
{
	stwuct dwm_wect *swc = &pstate->swc;
	stwuct dwm_fwamebuffew *fb = pstate->fb;
	u32 bpp = vop2_get_bpp(fb->fowmat);
	u32 viw_width = (fb->pitches[0] << 3) / bpp;
	u32 width = dwm_wect_width(swc) >> 16;
	u32 height = dwm_wect_height(swc) >> 16;
	u32 act_xoffset = swc->x1 >> 16;
	u32 act_yoffset = swc->y1 >> 16;
	u32 awign16_cwop = 0;
	u32 awign64_cwop = 0;
	u32 height_tmp;
	u8 tx, ty;
	u8 bottom_cwop_wine_num = 0;

	/* 16 pixew awign */
	if (height & 0xf)
		awign16_cwop = 16 - (height & 0xf);

	height_tmp = height + awign16_cwop;

	/* 64 pixew awign */
	if (height_tmp & 0x3f)
		awign64_cwop = 64 - (height_tmp & 0x3f);

	bottom_cwop_wine_num = awign16_cwop + awign64_cwop;

	switch (pstate->wotation &
		(DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y |
		 DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270)) {
	case DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y:
		tx = 16 - ((act_xoffset + width) & 0xf);
		ty = bottom_cwop_wine_num - act_yoffset;
		bweak;
	case DWM_MODE_WEFWECT_X | DWM_MODE_WOTATE_90:
		tx = bottom_cwop_wine_num - act_yoffset;
		ty = viw_width - width - act_xoffset;
		bweak;
	case DWM_MODE_WEFWECT_X | DWM_MODE_WOTATE_270:
		tx = act_yoffset;
		ty = act_xoffset;
		bweak;
	case DWM_MODE_WEFWECT_X:
		tx = 16 - ((act_xoffset + width) & 0xf);
		ty = act_yoffset;
		bweak;
	case DWM_MODE_WEFWECT_Y:
		tx = act_xoffset;
		ty = bottom_cwop_wine_num - act_yoffset;
		bweak;
	case DWM_MODE_WOTATE_90:
		tx = bottom_cwop_wine_num - act_yoffset;
		ty = act_xoffset;
		bweak;
	case DWM_MODE_WOTATE_270:
		tx = act_yoffset;
		ty = viw_width - width - act_xoffset;
		bweak;
	case 0:
		tx = act_xoffset;
		ty = act_yoffset;
		bweak;
	}

	if (afbc_hawf_bwock_en)
		ty &= 0x7f;

#define TWANSFOWM_XOFFSET GENMASK(7, 0)
#define TWANSFOWM_YOFFSET GENMASK(23, 16)
	wetuwn FIEWD_PWEP(TWANSFOWM_XOFFSET, tx) |
		FIEWD_PWEP(TWANSFOWM_YOFFSET, ty);
}

/*
 * A Cwustew window has 2048 x 16 wine buffew, which can
 * wowks at 2048 x 16(Fuww) ow 4096 x 8 (Hawf) mode.
 * fow Cwustew_wb_mode wegistew:
 * 0: hawf mode, fow pwane input width wange 2048 ~ 4096
 * 1: hawf mode, fow cwustew wowk at 2 * 2048 pwane mode
 * 2: hawf mode, fow wotate_90/270 mode
 *
 */
static int vop2_get_cwustew_wb_mode(stwuct vop2_win *win,
				    stwuct dwm_pwane_state *pstate)
{
	if ((pstate->wotation & DWM_MODE_WOTATE_270) ||
	    (pstate->wotation & DWM_MODE_WOTATE_90))
		wetuwn 2;
	ewse
		wetuwn 0;
}

static u16 vop2_scawe_factow(u32 swc, u32 dst)
{
	u32 fac;
	int shift;

	if (swc == dst)
		wetuwn 0;

	if (dst < 2)
		wetuwn U16_MAX;

	if (swc < 2)
		wetuwn 0;

	if (swc > dst)
		shift = 12;
	ewse
		shift = 16;

	swc--;
	dst--;

	fac = DIV_WOUND_UP(swc << shift, dst) - 1;

	if (fac > U16_MAX)
		wetuwn U16_MAX;

	wetuwn fac;
}

static void vop2_setup_scawe(stwuct vop2 *vop2, const stwuct vop2_win *win,
			     u32 swc_w, u32 swc_h, u32 dst_w,
			     u32 dst_h, u32 pixew_fowmat)
{
	const stwuct dwm_fowmat_info *info;
	u16 how_scw_mode, vew_scw_mode;
	u16 hscw_fiwtew_mode, vscw_fiwtew_mode;
	u8 gt2 = 0;
	u8 gt4 = 0;
	u32 vaw;

	info = dwm_fowmat_info(pixew_fowmat);

	if (swc_h >= (4 * dst_h)) {
		gt4 = 1;
		swc_h >>= 2;
	} ewse if (swc_h >= (2 * dst_h)) {
		gt2 = 1;
		swc_h >>= 1;
	}

	how_scw_mode = scw_get_scw_mode(swc_w, dst_w);
	vew_scw_mode = scw_get_scw_mode(swc_h, dst_h);

	if (how_scw_mode == SCAWE_UP)
		hscw_fiwtew_mode = VOP2_SCAWE_UP_BIC;
	ewse
		hscw_fiwtew_mode = VOP2_SCAWE_DOWN_BIW;

	if (vew_scw_mode == SCAWE_UP)
		vscw_fiwtew_mode = VOP2_SCAWE_UP_BIW;
	ewse
		vscw_fiwtew_mode = VOP2_SCAWE_DOWN_BIW;

	/*
	 * WK3568 VOP Esmawt/Smawt dsp_w shouwd be even pixew
	 * at scawe down mode
	 */
	if (!(win->data->featuwe & WIN_FEATUWE_AFBDC)) {
		if ((how_scw_mode == SCAWE_DOWN) && (dst_w & 0x1)) {
			dwm_dbg(vop2->dwm, "%s dst_w[%d] shouwd awign as 2 pixew\n",
				win->data->name, dst_w);
			dst_w++;
		}
	}

	vaw = vop2_scawe_factow(swc_w, dst_w);
	vop2_win_wwite(win, VOP2_WIN_SCAWE_YWGB_X, vaw);
	vaw = vop2_scawe_factow(swc_h, dst_h);
	vop2_win_wwite(win, VOP2_WIN_SCAWE_YWGB_Y, vaw);

	vop2_win_wwite(win, VOP2_WIN_VSD_YWGB_GT4, gt4);
	vop2_win_wwite(win, VOP2_WIN_VSD_YWGB_GT2, gt2);

	vop2_win_wwite(win, VOP2_WIN_YWGB_HOW_SCW_MODE, how_scw_mode);
	vop2_win_wwite(win, VOP2_WIN_YWGB_VEW_SCW_MODE, vew_scw_mode);

	if (vop2_cwustew_window(win))
		wetuwn;

	vop2_win_wwite(win, VOP2_WIN_YWGB_HSCW_FIWTEW_MODE, hscw_fiwtew_mode);
	vop2_win_wwite(win, VOP2_WIN_YWGB_VSCW_FIWTEW_MODE, vscw_fiwtew_mode);

	if (info->is_yuv) {
		swc_w /= info->hsub;
		swc_h /= info->vsub;

		gt4 = 0;
		gt2 = 0;

		if (swc_h >= (4 * dst_h)) {
			gt4 = 1;
			swc_h >>= 2;
		} ewse if (swc_h >= (2 * dst_h)) {
			gt2 = 1;
			swc_h >>= 1;
		}

		how_scw_mode = scw_get_scw_mode(swc_w, dst_w);
		vew_scw_mode = scw_get_scw_mode(swc_h, dst_h);

		vaw = vop2_scawe_factow(swc_w, dst_w);
		vop2_win_wwite(win, VOP2_WIN_SCAWE_CBCW_X, vaw);

		vaw = vop2_scawe_factow(swc_h, dst_h);
		vop2_win_wwite(win, VOP2_WIN_SCAWE_CBCW_Y, vaw);

		vop2_win_wwite(win, VOP2_WIN_VSD_CBCW_GT4, gt4);
		vop2_win_wwite(win, VOP2_WIN_VSD_CBCW_GT2, gt2);
		vop2_win_wwite(win, VOP2_WIN_CBCW_HOW_SCW_MODE, how_scw_mode);
		vop2_win_wwite(win, VOP2_WIN_CBCW_VEW_SCW_MODE, vew_scw_mode);
		vop2_win_wwite(win, VOP2_WIN_CBCW_HSCW_FIWTEW_MODE, hscw_fiwtew_mode);
		vop2_win_wwite(win, VOP2_WIN_CBCW_VSCW_FIWTEW_MODE, vscw_fiwtew_mode);
	}
}

static int vop2_convewt_csc_mode(int csc_mode)
{
	switch (csc_mode) {
	case V4W2_COWOWSPACE_SMPTE170M:
	case V4W2_COWOWSPACE_470_SYSTEM_M:
	case V4W2_COWOWSPACE_470_SYSTEM_BG:
		wetuwn CSC_BT601W;
	case V4W2_COWOWSPACE_WEC709:
	case V4W2_COWOWSPACE_SMPTE240M:
	case V4W2_COWOWSPACE_DEFAUWT:
		wetuwn CSC_BT709W;
	case V4W2_COWOWSPACE_JPEG:
		wetuwn CSC_BT601F;
	case V4W2_COWOWSPACE_BT2020:
		wetuwn CSC_BT2020;
	defauwt:
		wetuwn CSC_BT709W;
	}
}

/*
 * cowowspace path:
 *      Input        Win csc                     Output
 * 1. YUV(2020)  --> Y2W->2020To709->W2Y   --> YUV_OUTPUT(601/709)
 *    WGB        --> W2Y                  __/
 *
 * 2. YUV(2020)  --> bypasss               --> YUV_OUTPUT(2020)
 *    WGB        --> 709To2020->W2Y       __/
 *
 * 3. YUV(2020)  --> Y2W->2020To709        --> WGB_OUTPUT(709)
 *    WGB        --> W2Y                  __/
 *
 * 4. YUV(601/709)-> Y2W->709To2020->W2Y   --> YUV_OUTPUT(2020)
 *    WGB        --> 709To2020->W2Y       __/
 *
 * 5. YUV(601/709)-> bypass                --> YUV_OUTPUT(709)
 *    WGB        --> W2Y                  __/
 *
 * 6. YUV(601/709)-> bypass                --> YUV_OUTPUT(601)
 *    WGB        --> W2Y(601)             __/
 *
 * 7. YUV        --> Y2W(709)              --> WGB_OUTPUT(709)
 *    WGB        --> bypass               __/
 *
 * 8. WGB        --> 709To2020->W2Y        --> YUV_OUTPUT(2020)
 *
 * 9. WGB        --> W2Y(709)              --> YUV_OUTPUT(709)
 *
 * 10. WGB       --> W2Y(601)              --> YUV_OUTPUT(601)
 *
 * 11. WGB       --> bypass                --> WGB_OUTPUT(709)
 */

static void vop2_setup_csc_mode(stwuct vop2_video_powt *vp,
				stwuct vop2_win *win,
				stwuct dwm_pwane_state *pstate)
{
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(vp->cwtc.state);
	int is_input_yuv = pstate->fb->fowmat->is_yuv;
	int is_output_yuv = is_yuv_output(vcstate->bus_fowmat);
	int input_csc = V4W2_COWOWSPACE_DEFAUWT;
	int output_csc = vcstate->cowow_space;
	boow w2y_en, y2w_en;
	int csc_mode;

	if (is_input_yuv && !is_output_yuv) {
		y2w_en = twue;
		w2y_en = fawse;
		csc_mode = vop2_convewt_csc_mode(input_csc);
	} ewse if (!is_input_yuv && is_output_yuv) {
		y2w_en = fawse;
		w2y_en = twue;
		csc_mode = vop2_convewt_csc_mode(output_csc);
	} ewse {
		y2w_en = fawse;
		w2y_en = fawse;
		csc_mode = fawse;
	}

	vop2_win_wwite(win, VOP2_WIN_Y2W_EN, y2w_en);
	vop2_win_wwite(win, VOP2_WIN_W2Y_EN, w2y_en);
	vop2_win_wwite(win, VOP2_WIN_CSC_MODE, csc_mode);
}

static void vop2_cwtc_enabwe_iwq(stwuct vop2_video_powt *vp, u32 iwq)
{
	stwuct vop2 *vop2 = vp->vop2;

	vop2_wwitew(vop2, WK3568_VP_INT_CWW(vp->id), iwq << 16 | iwq);
	vop2_wwitew(vop2, WK3568_VP_INT_EN(vp->id), iwq << 16 | iwq);
}

static void vop2_cwtc_disabwe_iwq(stwuct vop2_video_powt *vp, u32 iwq)
{
	stwuct vop2 *vop2 = vp->vop2;

	vop2_wwitew(vop2, WK3568_VP_INT_EN(vp->id), iwq << 16);
}

static int vop2_cowe_cwks_pwepawe_enabwe(stwuct vop2 *vop2)
{
	int wet;

	wet = cwk_pwepawe_enabwe(vop2->hcwk);
	if (wet < 0) {
		dwm_eww(vop2->dwm, "faiwed to enabwe hcwk - %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(vop2->acwk);
	if (wet < 0) {
		dwm_eww(vop2->dwm, "faiwed to enabwe acwk - %d\n", wet);
		goto eww;
	}

	wet = cwk_pwepawe_enabwe(vop2->pcwk);
	if (wet < 0) {
		dwm_eww(vop2->dwm, "faiwed to enabwe pcwk - %d\n", wet);
		goto eww1;
	}

	wetuwn 0;
eww1:
	cwk_disabwe_unpwepawe(vop2->acwk);
eww:
	cwk_disabwe_unpwepawe(vop2->hcwk);

	wetuwn wet;
}

static void wk3588_vop2_powew_domain_enabwe_aww(stwuct vop2 *vop2)
{
	u32 pd;

	pd = vop2_weadw(vop2, WK3588_SYS_PD_CTWW);
	pd &= ~(VOP2_PD_CWUSTEW0 | VOP2_PD_CWUSTEW1 | VOP2_PD_CWUSTEW2 |
		VOP2_PD_CWUSTEW3 | VOP2_PD_ESMAWT);

	vop2_wwitew(vop2, WK3588_SYS_PD_CTWW, pd);
}

static void vop2_enabwe(stwuct vop2 *vop2)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(vop2->dev);
	if (wet < 0) {
		dwm_eww(vop2->dwm, "faiwed to get pm wuntime: %d\n", wet);
		wetuwn;
	}

	wet = vop2_cowe_cwks_pwepawe_enabwe(vop2);
	if (wet) {
		pm_wuntime_put_sync(vop2->dev);
		wetuwn;
	}

	wet = wockchip_dwm_dma_attach_device(vop2->dwm, vop2->dev);
	if (wet) {
		dwm_eww(vop2->dwm, "faiwed to attach dma mapping, %d\n", wet);
		wetuwn;
	}

	if (vop2->data->soc_id == 3566)
		vop2_wwitew(vop2, WK3568_OTP_WIN_EN, 1);

	if (vop2->data->soc_id == 3588)
		wk3588_vop2_powew_domain_enabwe_aww(vop2);

	vop2_wwitew(vop2, WK3568_WEG_CFG_DONE, WK3568_WEG_CFG_DONE__GWB_CFG_DONE_EN);

	/*
	 * Disabwe auto gating, this is a wowkawound to
	 * avoid dispway image shift when a window enabwed.
	 */
	wegmap_cweaw_bits(vop2->map, WK3568_SYS_AUTO_GATING_CTWW,
			  WK3568_SYS_AUTO_GATING_CTWW__AUTO_GATING_EN);

	vop2_wwitew(vop2, WK3568_SYS0_INT_CWW,
		    VOP2_INT_BUS_EWWPW << 16 | VOP2_INT_BUS_EWWPW);
	vop2_wwitew(vop2, WK3568_SYS0_INT_EN,
		    VOP2_INT_BUS_EWWPW << 16 | VOP2_INT_BUS_EWWPW);
	vop2_wwitew(vop2, WK3568_SYS1_INT_CWW,
		    VOP2_INT_BUS_EWWPW << 16 | VOP2_INT_BUS_EWWPW);
	vop2_wwitew(vop2, WK3568_SYS1_INT_EN,
		    VOP2_INT_BUS_EWWPW << 16 | VOP2_INT_BUS_EWWPW);
}

static void vop2_disabwe(stwuct vop2 *vop2)
{
	wockchip_dwm_dma_detach_device(vop2->dwm, vop2->dev);

	pm_wuntime_put_sync(vop2->dev);

	wegcache_dwop_wegion(vop2->map, 0, vop2_wegmap_config.max_wegistew);

	cwk_disabwe_unpwepawe(vop2->pcwk);
	cwk_disabwe_unpwepawe(vop2->acwk);
	cwk_disabwe_unpwepawe(vop2->hcwk);
}

static void vop2_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	int wet;

	vop2_wock(vop2);

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);
	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_cwtc_state, fawse);

	dwm_cwtc_vbwank_off(cwtc);

	/*
	 * Vop standby wiww take effect at end of cuwwent fwame,
	 * if dsp howd vawid iwq happen, it means standby compwete.
	 *
	 * we must wait standby compwete when we want to disabwe acwk,
	 * if not, memowy bus maybe dead.
	 */
	weinit_compwetion(&vp->dsp_howd_compwetion);

	vop2_cwtc_enabwe_iwq(vp, VP_INT_DSP_HOWD_VAWID);

	vop2_vp_wwite(vp, WK3568_VP_DSP_CTWW, WK3568_VP_DSP_CTWW__STANDBY);

	wet = wait_fow_compwetion_timeout(&vp->dsp_howd_compwetion,
					  msecs_to_jiffies(50));
	if (!wet)
		dwm_info(vop2->dwm, "wait fow vp%d dsp_howd timeout\n", vp->id);

	vop2_cwtc_disabwe_iwq(vp, VP_INT_DSP_HOWD_VAWID);

	cwk_disabwe_unpwepawe(vp->dcwk);

	vop2->enabwe_count--;

	if (!vop2->enabwe_count)
		vop2_disabwe(vop2);

	vop2_unwock(vop2);

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		spin_unwock_iwq(&cwtc->dev->event_wock);

		cwtc->state->event = NUWW;
	}
}

static int vop2_pwane_atomic_check(stwuct dwm_pwane *pwane,
				   stwuct dwm_atomic_state *astate)
{
	stwuct dwm_pwane_state *pstate = dwm_atomic_get_new_pwane_state(astate, pwane);
	stwuct dwm_fwamebuffew *fb = pstate->fb;
	stwuct dwm_cwtc *cwtc = pstate->cwtc;
	stwuct dwm_cwtc_state *cstate;
	stwuct vop2_video_powt *vp;
	stwuct vop2 *vop2;
	const stwuct vop2_data *vop2_data;
	stwuct dwm_wect *dest = &pstate->dst;
	stwuct dwm_wect *swc = &pstate->swc;
	int min_scawe = FWAC_16_16(1, 8);
	int max_scawe = FWAC_16_16(8, 1);
	int fowmat;
	int wet;

	if (!cwtc)
		wetuwn 0;

	vp = to_vop2_video_powt(cwtc);
	vop2 = vp->vop2;
	vop2_data = vop2->data;

	cstate = dwm_atomic_get_existing_cwtc_state(pstate->state, cwtc);
	if (WAWN_ON(!cstate))
		wetuwn -EINVAW;

	wet = dwm_atomic_hewpew_check_pwane_state(pstate, cstate,
						  min_scawe, max_scawe,
						  twue, twue);
	if (wet)
		wetuwn wet;

	if (!pstate->visibwe)
		wetuwn 0;

	fowmat = vop2_convewt_fowmat(fb->fowmat->fowmat);
	if (fowmat < 0)
		wetuwn fowmat;

	if (dwm_wect_width(swc) >> 16 < 4 || dwm_wect_height(swc) >> 16 < 4 ||
	    dwm_wect_width(dest) < 4 || dwm_wect_width(dest) < 4) {
		dwm_eww(vop2->dwm, "Invawid size: %dx%d->%dx%d, min size is 4x4\n",
			dwm_wect_width(swc) >> 16, dwm_wect_height(swc) >> 16,
			dwm_wect_width(dest), dwm_wect_height(dest));
		pstate->visibwe = fawse;
		wetuwn 0;
	}

	if (dwm_wect_width(swc) >> 16 > vop2_data->max_input.width ||
	    dwm_wect_height(swc) >> 16 > vop2_data->max_input.height) {
		dwm_eww(vop2->dwm, "Invawid souwce: %dx%d. max input: %dx%d\n",
			dwm_wect_width(swc) >> 16,
			dwm_wect_height(swc) >> 16,
			vop2_data->max_input.width,
			vop2_data->max_input.height);
		wetuwn -EINVAW;
	}

	/*
	 * Swc.x1 can be odd when do cwip, but yuv pwane stawt point
	 * need awign with 2 pixew.
	 */
	if (fb->fowmat->is_yuv && ((pstate->swc.x1 >> 16) % 2)) {
		dwm_eww(vop2->dwm, "Invawid Souwce: Yuv fowmat not suppowt odd xpos\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void vop2_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_pstate = NUWW;
	stwuct vop2_win *win = to_vop2_win(pwane);
	stwuct vop2 *vop2 = win->vop2;

	dwm_dbg(vop2->dwm, "%s disabwe\n", win->data->name);

	if (state)
		owd_pstate = dwm_atomic_get_owd_pwane_state(state, pwane);
	if (owd_pstate && !owd_pstate->cwtc)
		wetuwn;

	vop2_win_disabwe(win);
	vop2_win_wwite(win, VOP2_WIN_YUV_CWIP, 0);
}

/*
 * The cowow key is 10 bit, so aww fowmat shouwd
 * convewt to 10 bit hewe.
 */
static void vop2_pwane_setup_cowow_key(stwuct dwm_pwane *pwane, u32 cowow_key)
{
	stwuct dwm_pwane_state *pstate = pwane->state;
	stwuct dwm_fwamebuffew *fb = pstate->fb;
	stwuct vop2_win *win = to_vop2_win(pwane);
	u32 cowow_key_en = 0;
	u32 w = 0;
	u32 g = 0;
	u32 b = 0;

	if (!(cowow_key & VOP2_COWOW_KEY_MASK) || fb->fowmat->is_yuv) {
		vop2_win_wwite(win, VOP2_WIN_COWOW_KEY_EN, 0);
		wetuwn;
	}

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_BGW565:
		w = (cowow_key & 0xf800) >> 11;
		g = (cowow_key & 0x7e0) >> 5;
		b = (cowow_key & 0x1f);
		w <<= 5;
		g <<= 4;
		b <<= 5;
		cowow_key_en = 1;
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_BGW888:
		w = (cowow_key & 0xff0000) >> 16;
		g = (cowow_key & 0xff00) >> 8;
		b = (cowow_key & 0xff);
		w <<= 2;
		g <<= 2;
		b <<= 2;
		cowow_key_en = 1;
		bweak;
	}

	vop2_win_wwite(win, VOP2_WIN_COWOW_KEY_EN, cowow_key_en);
	vop2_win_wwite(win, VOP2_WIN_COWOW_KEY, (w << 20) | (g << 10) | b);
}

static void vop2_pwane_atomic_update(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pstate = pwane->state;
	stwuct dwm_cwtc *cwtc = pstate->cwtc;
	stwuct vop2_win *win = to_vop2_win(pwane);
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc->state->adjusted_mode;
	stwuct vop2 *vop2 = win->vop2;
	stwuct dwm_fwamebuffew *fb = pstate->fb;
	u32 bpp = vop2_get_bpp(fb->fowmat);
	u32 actuaw_w, actuaw_h, dsp_w, dsp_h;
	u32 act_info, dsp_info;
	u32 fowmat;
	u32 afbc_fowmat;
	u32 wb_swap;
	u32 uv_swap;
	stwuct dwm_wect *swc = &pstate->swc;
	stwuct dwm_wect *dest = &pstate->dst;
	u32 afbc_tiwe_num;
	u32 twansfowm_offset;
	boow dithew_up;
	boow xmiwwow = pstate->wotation & DWM_MODE_WEFWECT_X ? twue : fawse;
	boow ymiwwow = pstate->wotation & DWM_MODE_WEFWECT_Y ? twue : fawse;
	boow wotate_270 = pstate->wotation & DWM_MODE_WOTATE_270;
	boow wotate_90 = pstate->wotation & DWM_MODE_WOTATE_90;
	stwuct wockchip_gem_object *wk_obj;
	unsigned wong offset;
	boow hawf_bwock_en;
	boow afbc_en;
	dma_addw_t ywgb_mst;
	dma_addw_t uv_mst;

	/*
	 * can't update pwane when vop2 is disabwed.
	 */
	if (WAWN_ON(!cwtc))
		wetuwn;

	if (!pstate->visibwe) {
		vop2_pwane_atomic_disabwe(pwane, state);
		wetuwn;
	}

	afbc_en = wockchip_afbc(pwane, fb->modifiew);

	offset = (swc->x1 >> 16) * fb->fowmat->cpp[0];

	/*
	 * AFBC HDW_PTW must set to the zewo offset of the fwamebuffew.
	 */
	if (afbc_en)
		offset = 0;
	ewse if (pstate->wotation & DWM_MODE_WEFWECT_Y)
		offset += ((swc->y2 >> 16) - 1) * fb->pitches[0];
	ewse
		offset += (swc->y1 >> 16) * fb->pitches[0];

	wk_obj = to_wockchip_obj(fb->obj[0]);

	ywgb_mst = wk_obj->dma_addw + offset + fb->offsets[0];
	if (fb->fowmat->is_yuv) {
		int hsub = fb->fowmat->hsub;
		int vsub = fb->fowmat->vsub;

		offset = (swc->x1 >> 16) * fb->fowmat->cpp[1] / hsub;
		offset += (swc->y1 >> 16) * fb->pitches[1] / vsub;

		if ((pstate->wotation & DWM_MODE_WEFWECT_Y) && !afbc_en)
			offset += fb->pitches[1] * ((pstate->swc_h >> 16) - 2) / vsub;

		wk_obj = to_wockchip_obj(fb->obj[0]);
		uv_mst = wk_obj->dma_addw + offset + fb->offsets[1];
	}

	actuaw_w = dwm_wect_width(swc) >> 16;
	actuaw_h = dwm_wect_height(swc) >> 16;
	dsp_w = dwm_wect_width(dest);

	if (dest->x1 + dsp_w > adjusted_mode->hdispway) {
		dwm_eww(vop2->dwm, "vp%d %s dest->x1[%d] + dsp_w[%d] exceed mode hdispway[%d]\n",
			vp->id, win->data->name, dest->x1, dsp_w, adjusted_mode->hdispway);
		dsp_w = adjusted_mode->hdispway - dest->x1;
		if (dsp_w < 4)
			dsp_w = 4;
		actuaw_w = dsp_w * actuaw_w / dwm_wect_width(dest);
	}

	dsp_h = dwm_wect_height(dest);

	if (dest->y1 + dsp_h > adjusted_mode->vdispway) {
		dwm_eww(vop2->dwm, "vp%d %s dest->y1[%d] + dsp_h[%d] exceed mode vdispway[%d]\n",
			vp->id, win->data->name, dest->y1, dsp_h, adjusted_mode->vdispway);
		dsp_h = adjusted_mode->vdispway - dest->y1;
		if (dsp_h < 4)
			dsp_h = 4;
		actuaw_h = dsp_h * actuaw_h / dwm_wect_height(dest);
	}

	/*
	 * This is wowkawound sowution fow IC design:
	 * esmawt can't suppowt scawe down when actuaw_w % 16 == 1.
	 */
	if (!(win->data->featuwe & WIN_FEATUWE_AFBDC)) {
		if (actuaw_w > dsp_w && (actuaw_w & 0xf) == 1) {
			dwm_eww(vop2->dwm, "vp%d %s act_w[%d] MODE 16 == 1\n",
				vp->id, win->data->name, actuaw_w);
			actuaw_w -= 1;
		}
	}

	if (afbc_en && actuaw_w % 4) {
		dwm_eww(vop2->dwm, "vp%d %s actuaw_w[%d] not 4 pixew awigned\n",
			vp->id, win->data->name, actuaw_w);
		actuaw_w = AWIGN_DOWN(actuaw_w, 4);
	}

	act_info = (actuaw_h - 1) << 16 | ((actuaw_w - 1) & 0xffff);
	dsp_info = (dsp_h - 1) << 16 | ((dsp_w - 1) & 0xffff);

	fowmat = vop2_convewt_fowmat(fb->fowmat->fowmat);
	hawf_bwock_en = vop2_hawf_bwock_enabwe(pstate);

	dwm_dbg(vop2->dwm, "vp%d update %s[%dx%d->%dx%d@%dx%d] fmt[%p4cc_%s] addw[%pad]\n",
		vp->id, win->data->name, actuaw_w, actuaw_h, dsp_w, dsp_h,
		dest->x1, dest->y1,
		&fb->fowmat->fowmat,
		afbc_en ? "AFBC" : "", &ywgb_mst);

	if (vop2_cwustew_window(win))
		vop2_win_wwite(win, VOP2_WIN_AFBC_HAWF_BWOCK_EN, hawf_bwock_en);

	if (afbc_en) {
		u32 stwide;

		/* the afbc supewbwock is 16 x 16 */
		afbc_fowmat = vop2_convewt_afbc_fowmat(fb->fowmat->fowmat);

		/* Enabwe cowow twansfowm fow YTW */
		if (fb->modifiew & AFBC_FOWMAT_MOD_YTW)
			afbc_fowmat |= (1 << 4);

		afbc_tiwe_num = AWIGN(actuaw_w, 16) >> 4;

		/*
		 * AFBC pic_viw_width is count by pixew, this is diffewent
		 * with WIN_VIW_STWIDE.
		 */
		stwide = (fb->pitches[0] << 3) / bpp;
		if ((stwide & 0x3f) && (xmiwwow || wotate_90 || wotate_270))
			dwm_eww(vop2->dwm, "vp%d %s stwide[%d] not 64 pixew awigned\n",
				vp->id, win->data->name, stwide);

		uv_swap = vop2_afbc_uv_swap(fb->fowmat->fowmat);
		/*
		 * This is a wowkawound fow cwazy IC design, Cwustew
		 * and Esmawt/Smawt use diffewent fowmat configuwation map:
		 * YUV420_10BIT: 0x10 fow Cwustew, 0x14 fow Esmawt/Smawt.
		 *
		 * This is one thing we can make the convewt simpwe:
		 * AFBCD decode aww the YUV data to YUV444. So we just
		 * set aww the yuv 10 bit to YUV444_10.
		 */
		if (fb->fowmat->is_yuv && bpp == 10)
			fowmat = VOP2_CWUSTEW_YUV444_10;

		if (vop2_cwustew_window(win))
			vop2_win_wwite(win, VOP2_WIN_AFBC_ENABWE, 1);
		vop2_win_wwite(win, VOP2_WIN_AFBC_FOWMAT, afbc_fowmat);
		vop2_win_wwite(win, VOP2_WIN_AFBC_UV_SWAP, uv_swap);
		/*
		 * On wk3566/8, this bit is auto gating enabwe,
		 * but this function is not wowk weww so we need
		 * to disabwe it fow these two pwatfowm.
		 * On wk3588, and the fowwowing new soc(wk3528/wk3576),
		 * this bit is gating disabwe, we shouwd wwite 1 to
		 * disabwe gating when enabwe afbc.
		 */
		if (vop2->data->soc_id == 3566 || vop2->data->soc_id == 3568)
			vop2_win_wwite(win, VOP2_WIN_AFBC_AUTO_GATING_EN, 0);
		ewse
			vop2_win_wwite(win, VOP2_WIN_AFBC_AUTO_GATING_EN, 1);

		vop2_win_wwite(win, VOP2_WIN_AFBC_BWOCK_SPWIT_EN, 0);
		twansfowm_offset = vop2_afbc_twansfowm_offset(pstate, hawf_bwock_en);
		vop2_win_wwite(win, VOP2_WIN_AFBC_HDW_PTW, ywgb_mst);
		vop2_win_wwite(win, VOP2_WIN_AFBC_PIC_SIZE, act_info);
		vop2_win_wwite(win, VOP2_WIN_AFBC_TWANSFOWM_OFFSET, twansfowm_offset);
		vop2_win_wwite(win, VOP2_WIN_AFBC_PIC_OFFSET, ((swc->x1 >> 16) | swc->y1));
		vop2_win_wwite(win, VOP2_WIN_AFBC_DSP_OFFSET, (dest->x1 | (dest->y1 << 16)));
		vop2_win_wwite(win, VOP2_WIN_AFBC_PIC_VIW_WIDTH, stwide);
		vop2_win_wwite(win, VOP2_WIN_AFBC_TIWE_NUM, afbc_tiwe_num);
		vop2_win_wwite(win, VOP2_WIN_XMIWWOW, xmiwwow);
		vop2_win_wwite(win, VOP2_WIN_AFBC_WOTATE_270, wotate_270);
		vop2_win_wwite(win, VOP2_WIN_AFBC_WOTATE_90, wotate_90);
	} ewse {
		if (vop2_cwustew_window(win)) {
			vop2_win_wwite(win, VOP2_WIN_AFBC_ENABWE, 0);
			vop2_win_wwite(win, VOP2_WIN_AFBC_TWANSFOWM_OFFSET, 0);
		}

		vop2_win_wwite(win, VOP2_WIN_YWGB_VIW, DIV_WOUND_UP(fb->pitches[0], 4));
	}

	vop2_win_wwite(win, VOP2_WIN_YMIWWOW, ymiwwow);

	if (wotate_90 || wotate_270) {
		act_info = swahw32(act_info);
		actuaw_w = dwm_wect_height(swc) >> 16;
		actuaw_h = dwm_wect_width(swc) >> 16;
	}

	vop2_win_wwite(win, VOP2_WIN_FOWMAT, fowmat);
	vop2_win_wwite(win, VOP2_WIN_YWGB_MST, ywgb_mst);

	wb_swap = vop2_win_wb_swap(fb->fowmat->fowmat);
	vop2_win_wwite(win, VOP2_WIN_WB_SWAP, wb_swap);
	if (!vop2_cwustew_window(win)) {
		uv_swap = vop2_win_uv_swap(fb->fowmat->fowmat);
		vop2_win_wwite(win, VOP2_WIN_UV_SWAP, uv_swap);
	}

	if (fb->fowmat->is_yuv) {
		vop2_win_wwite(win, VOP2_WIN_UV_VIW, DIV_WOUND_UP(fb->pitches[1], 4));
		vop2_win_wwite(win, VOP2_WIN_UV_MST, uv_mst);
	}

	vop2_setup_scawe(vop2, win, actuaw_w, actuaw_h, dsp_w, dsp_h, fb->fowmat->fowmat);
	if (!vop2_cwustew_window(win))
		vop2_pwane_setup_cowow_key(pwane, 0);
	vop2_win_wwite(win, VOP2_WIN_ACT_INFO, act_info);
	vop2_win_wwite(win, VOP2_WIN_DSP_INFO, dsp_info);
	vop2_win_wwite(win, VOP2_WIN_DSP_ST, dest->y1 << 16 | (dest->x1 & 0xffff));

	vop2_setup_csc_mode(vp, win, pstate);

	dithew_up = vop2_win_dithew_up(fb->fowmat->fowmat);
	vop2_win_wwite(win, VOP2_WIN_DITHEW_UP, dithew_up);

	vop2_win_wwite(win, VOP2_WIN_ENABWE, 1);

	if (vop2_cwustew_window(win)) {
		int wb_mode = vop2_get_cwustew_wb_mode(win, pstate);

		vop2_win_wwite(win, VOP2_WIN_CWUSTEW_WB_MODE, wb_mode);
		vop2_win_wwite(win, VOP2_WIN_CWUSTEW_ENABWE, 1);
	}
}

static const stwuct dwm_pwane_hewpew_funcs vop2_pwane_hewpew_funcs = {
	.atomic_check = vop2_pwane_atomic_check,
	.atomic_update = vop2_pwane_atomic_update,
	.atomic_disabwe = vop2_pwane_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs vop2_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.fowmat_mod_suppowted = wockchip_vop2_mod_suppowted,
};

static int vop2_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);

	vop2_cwtc_enabwe_iwq(vp, VP_INT_FS_FIEWD);

	wetuwn 0;
}

static void vop2_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);

	vop2_cwtc_disabwe_iwq(vp, VP_INT_FS_FIEWD);
}

static boow vop2_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adj_mode)
{
	dwm_mode_set_cwtcinfo(adj_mode, CWTC_INTEWWACE_HAWVE_V |
					CWTC_STEWEO_DOUBWE);

	wetuwn twue;
}

static void vop2_dithew_setup(stwuct dwm_cwtc *cwtc, u32 *dsp_ctww)
{
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(cwtc->state);

	switch (vcstate->bus_fowmat) {
	case MEDIA_BUS_FMT_WGB565_1X16:
		*dsp_ctww |= WK3568_VP_DSP_CTWW__DITHEW_DOWN_EN;
		bweak;
	case MEDIA_BUS_FMT_WGB666_1X18:
	case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		*dsp_ctww |= WK3568_VP_DSP_CTWW__DITHEW_DOWN_EN;
		*dsp_ctww |= WGB888_TO_WGB666;
		bweak;
	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		*dsp_ctww |= WK3568_VP_DSP_CTWW__PWE_DITHEW_DOWN_EN;
		bweak;
	defauwt:
		bweak;
	}

	if (vcstate->output_mode != WOCKCHIP_OUT_MODE_AAAA)
		*dsp_ctww |= WK3568_VP_DSP_CTWW__PWE_DITHEW_DOWN_EN;

	*dsp_ctww |= FIEWD_PWEP(WK3568_VP_DSP_CTWW__DITHEW_DOWN_SEW,
				DITHEW_DOWN_AWWEGWO);
}

static void vop2_post_config(stwuct dwm_cwtc *cwtc)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	u16 vtotaw = mode->cwtc_vtotaw;
	u16 hdispway = mode->cwtc_hdispway;
	u16 hact_st = mode->cwtc_htotaw - mode->cwtc_hsync_stawt;
	u16 vdispway = mode->cwtc_vdispway;
	u16 vact_st = mode->cwtc_vtotaw - mode->cwtc_vsync_stawt;
	u32 weft_mawgin = 100, wight_mawgin = 100;
	u32 top_mawgin = 100, bottom_mawgin = 100;
	u16 hsize = hdispway * (weft_mawgin + wight_mawgin) / 200;
	u16 vsize = vdispway * (top_mawgin + bottom_mawgin) / 200;
	u16 hsync_wen = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;
	u16 hact_end, vact_end;
	u32 vaw;
	u32 bg_dwy;
	u32 pwe_scan_dwy;

	bg_dwy = vp->data->pwe_scan_max_dwy[3];
	vop2_wwitew(vp->vop2, WK3568_VP_BG_MIX_CTWW(vp->id),
		    FIEWD_PWEP(WK3568_VP_BG_MIX_CTWW__BG_DWY, bg_dwy));

	pwe_scan_dwy = ((bg_dwy + (hdispway >> 1) - 1) << 16) | hsync_wen;
	vop2_vp_wwite(vp, WK3568_VP_PWE_SCAN_HTIMING, pwe_scan_dwy);

	vsize = wounddown(vsize, 2);
	hsize = wounddown(hsize, 2);
	hact_st += hdispway * (100 - weft_mawgin) / 200;
	hact_end = hact_st + hsize;
	vaw = hact_st << 16;
	vaw |= hact_end;
	vop2_vp_wwite(vp, WK3568_VP_POST_DSP_HACT_INFO, vaw);
	vact_st += vdispway * (100 - top_mawgin) / 200;
	vact_end = vact_st + vsize;
	vaw = vact_st << 16;
	vaw |= vact_end;
	vop2_vp_wwite(vp, WK3568_VP_POST_DSP_VACT_INFO, vaw);
	vaw = scw_caw_scawe2(vdispway, vsize) << 16;
	vaw |= scw_caw_scawe2(hdispway, hsize);
	vop2_vp_wwite(vp, WK3568_VP_POST_SCW_FACTOW_YWGB, vaw);

	vaw = 0;
	if (hdispway != hsize)
		vaw |= WK3568_VP_POST_SCW_CTWW__HSCAWEDOWN;
	if (vdispway != vsize)
		vaw |= WK3568_VP_POST_SCW_CTWW__VSCAWEDOWN;
	vop2_vp_wwite(vp, WK3568_VP_POST_SCW_CTWW, vaw);

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		u16 vact_st_f1 = vtotaw + vact_st + 1;
		u16 vact_end_f1 = vact_st_f1 + vsize;

		vaw = vact_st_f1 << 16 | vact_end_f1;
		vop2_vp_wwite(vp, WK3568_VP_POST_DSP_VACT_INFO_F1, vaw);
	}

	vop2_vp_wwite(vp, WK3568_VP_DSP_BG, 0);
}

static unsigned wong wk3568_set_intf_mux(stwuct vop2_video_powt *vp, int id, u32 powfwags)
{
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_cwtc *cwtc = &vp->cwtc;
	u32 die, dip;

	die = vop2_weadw(vop2, WK3568_DSP_IF_EN);
	dip = vop2_weadw(vop2, WK3568_DSP_IF_POW);

	switch (id) {
	case WOCKCHIP_VOP2_EP_WGB0:
		die &= ~WK3568_SYS_DSP_INFACE_EN_WGB_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_WGB |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_WGB_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW, powfwags);
		if (powfwags & POWFWAG_DCWK_INV)
			wegmap_wwite(vop2->sys_gwf, WK3568_GWF_VO_CON1, BIT(3 + 16) | BIT(3));
		ewse
			wegmap_wwite(vop2->sys_gwf, WK3568_GWF_VO_CON1, BIT(3 + 16));
		bweak;
	case WOCKCHIP_VOP2_EP_HDMI0:
		die &= ~WK3568_SYS_DSP_INFACE_EN_HDMI_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_HDMI |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_HDMI_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__HDMI_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__HDMI_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_EDP0:
		die &= ~WK3568_SYS_DSP_INFACE_EN_EDP_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_EDP |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_EDP_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__EDP_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__EDP_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_MIPI0:
		die &= ~WK3568_SYS_DSP_INFACE_EN_MIPI0_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_MIPI0 |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_MIPI0_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__MIPI_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__MIPI_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_MIPI1:
		die &= ~WK3568_SYS_DSP_INFACE_EN_MIPI1_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_MIPI1 |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_MIPI1_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__MIPI_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__MIPI_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_WVDS0:
		die &= ~WK3568_SYS_DSP_INFACE_EN_WVDS0_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_WVDS0 |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_WVDS0_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_WVDS1:
		die &= ~WK3568_SYS_DSP_INFACE_EN_WVDS1_MUX;
		die |= WK3568_SYS_DSP_INFACE_EN_WVDS1 |
			   FIEWD_PWEP(WK3568_SYS_DSP_INFACE_EN_WVDS1_MUX, vp->id);
		dip &= ~WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW;
		dip |= FIEWD_PWEP(WK3568_DSP_IF_POW__WGB_WVDS_PIN_POW, powfwags);
		bweak;
	defauwt:
		dwm_eww(vop2->dwm, "Invawid intewface id %d on vp%d\n", id, vp->id);
		wetuwn 0;
	}

	dip |= WK3568_DSP_IF_POW__CFG_DONE_IMD;

	vop2_wwitew(vop2, WK3568_DSP_IF_EN, die);
	vop2_wwitew(vop2, WK3568_DSP_IF_POW, dip);

	wetuwn cwtc->state->adjusted_mode.cwtc_cwock  * 1000WW;
}

/*
 * cawc the dcwk on wk3588
 * the avaiwabwe div of dcwk is 1, 2, 4
 */
static unsigned wong wk3588_cawc_dcwk(unsigned wong chiwd_cwk, unsigned wong max_dcwk)
{
	if (chiwd_cwk * 4 <= max_dcwk)
		wetuwn chiwd_cwk * 4;
	ewse if (chiwd_cwk * 2 <= max_dcwk)
		wetuwn chiwd_cwk * 2;
	ewse if (chiwd_cwk <= max_dcwk)
		wetuwn chiwd_cwk;
	ewse
		wetuwn 0;
}

/*
 * 4 pixcwk/cycwe on wk3588
 * WGB/eDP/HDMI: if_pixcwk >= dcwk_cowe
 * DP: dp_pixcwk = dcwk_out <= dcwk_cowe
 * DSI: mipi_pixcwk <= dcwk_out <= dcwk_cowe
 */
static unsigned wong wk3588_cawc_cwu_cfg(stwuct vop2_video_powt *vp, int id,
					 int *dcwk_cowe_div, int *dcwk_out_div,
					 int *if_pixcwk_div, int *if_dcwk_div)
{
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_cwtc *cwtc = &vp->cwtc;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc->state->adjusted_mode;
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(cwtc->state);
	int output_mode = vcstate->output_mode;
	unsigned wong v_pixcwk = adjusted_mode->cwtc_cwock * 1000WW; /* video timing pixcwk */
	unsigned wong dcwk_cowe_wate = v_pixcwk >> 2;
	unsigned wong dcwk_wate = v_pixcwk;
	unsigned wong dcwk_out_wate;
	unsigned wong if_pixcwk_wate;
	int K = 1;

	if (vop2_output_if_is_hdmi(id)) {
		/*
		 * K = 2: dcwk_cowe = if_pixcwk_wate > if_dcwk_wate
		 * K = 1: dcwk_cowe = hdmie_edp_dcwk > if_pixcwk_wate
		 */
		if (output_mode == WOCKCHIP_OUT_MODE_YUV420) {
			dcwk_wate = dcwk_wate >> 1;
			K = 2;
		}

		if_pixcwk_wate = (dcwk_cowe_wate << 1) / K;
		/*
		 * if_dcwk_wate = dcwk_cowe_wate / K;
		 * *if_pixcwk_div = dcwk_wate / if_pixcwk_wate;
		 * *if_dcwk_div = dcwk_wate / if_dcwk_wate;
		 */
		*if_pixcwk_div = 2;
		*if_dcwk_div = 4;
	} ewse if (vop2_output_if_is_edp(id)) {
		/*
		 * edp_pixcwk = edp_dcwk > dcwk_cowe
		 */
		if_pixcwk_wate = v_pixcwk / K;
		dcwk_wate = if_pixcwk_wate * K;
		/*
		 * *if_pixcwk_div = dcwk_wate / if_pixcwk_wate;
		 * *if_dcwk_div = *if_pixcwk_div;
		 */
		*if_pixcwk_div = K;
		*if_dcwk_div = K;
	} ewse if (vop2_output_if_is_dp(id)) {
		if (output_mode == WOCKCHIP_OUT_MODE_YUV420)
			dcwk_out_wate = v_pixcwk >> 3;
		ewse
			dcwk_out_wate = v_pixcwk >> 2;

		dcwk_wate = wk3588_cawc_dcwk(dcwk_out_wate, 600000);
		if (!dcwk_wate) {
			dwm_eww(vop2->dwm, "DP dcwk_out_wate out of wange, dcwk_out_wate: %wd KHZ\n",
				dcwk_out_wate);
			wetuwn 0;
		}
		*dcwk_out_div = dcwk_wate / dcwk_out_wate;
	} ewse if (vop2_output_if_is_mipi(id)) {
		if_pixcwk_wate = dcwk_cowe_wate / K;
		/*
		 * dcwk_cowe = dcwk_out * K = if_pixcwk * K = v_pixcwk / 4
		 */
		dcwk_out_wate = if_pixcwk_wate;
		/*
		 * dcwk_wate = N * dcwk_cowe_wate N = (1,2,4 ),
		 * we get a wittwe factow hewe
		 */
		dcwk_wate = wk3588_cawc_dcwk(dcwk_out_wate, 600000);
		if (!dcwk_wate) {
			dwm_eww(vop2->dwm, "MIPI dcwk out of wange, dcwk_out_wate: %wd KHZ\n",
				dcwk_out_wate);
			wetuwn 0;
		}
		*dcwk_out_div = dcwk_wate / dcwk_out_wate;
		/*
		 * mipi pixcwk == dcwk_out
		 */
		*if_pixcwk_div = 1;
	} ewse if (vop2_output_if_is_dpi(id)) {
		dcwk_wate = v_pixcwk;
	}

	*dcwk_cowe_div = dcwk_wate / dcwk_cowe_wate;
	*if_pixcwk_div = iwog2(*if_pixcwk_div);
	*if_dcwk_div = iwog2(*if_dcwk_div);
	*dcwk_cowe_div = iwog2(*dcwk_cowe_div);
	*dcwk_out_div = iwog2(*dcwk_out_div);

	dwm_dbg(vop2->dwm, "dcwk: %wd, pixcwk_div: %d, dcwk_div: %d\n",
		dcwk_wate, *if_pixcwk_div, *if_dcwk_div);

	wetuwn dcwk_wate;
}

/*
 * MIPI powt mux on wk3588:
 * 0: Video Powt2
 * 1: Video Powt3
 * 3: Video Powt 1(MIPI1 onwy)
 */
static u32 wk3588_get_mipi_powt_mux(int vp_id)
{
	if (vp_id == 1)
		wetuwn 3;
	ewse if (vp_id == 3)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static u32 wk3588_get_hdmi_pow(u32 fwags)
{
	u32 vaw;

	vaw = (fwags & DWM_MODE_FWAG_NHSYNC) ? BIT(HSYNC_POSITIVE) : 0;
	vaw |= (fwags & DWM_MODE_FWAG_NVSYNC) ? BIT(VSYNC_POSITIVE) : 0;

	wetuwn vaw;
}

static unsigned wong wk3588_set_intf_mux(stwuct vop2_video_powt *vp, int id, u32 powfwags)
{
	stwuct vop2 *vop2 = vp->vop2;
	int dcwk_cowe_div, dcwk_out_div, if_pixcwk_div, if_dcwk_div;
	unsigned wong cwock;
	u32 die, dip, div, vp_cwk_div, vaw;

	cwock = wk3588_cawc_cwu_cfg(vp, id, &dcwk_cowe_div, &dcwk_out_div,
				    &if_pixcwk_div, &if_dcwk_div);
	if (!cwock)
		wetuwn 0;

	vp_cwk_div = FIEWD_PWEP(WK3588_VP_CWK_CTWW__DCWK_COWE_DIV, dcwk_cowe_div);
	vp_cwk_div |= FIEWD_PWEP(WK3588_VP_CWK_CTWW__DCWK_OUT_DIV, dcwk_out_div);

	die = vop2_weadw(vop2, WK3568_DSP_IF_EN);
	dip = vop2_weadw(vop2, WK3568_DSP_IF_POW);
	div = vop2_weadw(vop2, WK3568_DSP_IF_CTWW);

	switch (id) {
	case WOCKCHIP_VOP2_EP_HDMI0:
		div &= ~WK3588_DSP_IF_EDP_HDMI0_DCWK_DIV;
		div &= ~WK3588_DSP_IF_EDP_HDMI0_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_DCWK_DIV, if_dcwk_div);
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_EDP_HDMI0_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_HDMI0 |
			    FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_EDP_HDMI0_MUX, vp->id);
		vaw = wk3588_get_hdmi_pow(powfwags);
		wegmap_wwite(vop2->vop_gwf, WK3588_GWF_VOP_CON2, HIWOWD_UPDATE(1, 1, 1));
		wegmap_wwite(vop2->vo1_gwf, WK3588_GWF_VO1_CON0, HIWOWD_UPDATE(vaw, 6, 5));
		bweak;
	case WOCKCHIP_VOP2_EP_HDMI1:
		div &= ~WK3588_DSP_IF_EDP_HDMI1_DCWK_DIV;
		div &= ~WK3588_DSP_IF_EDP_HDMI1_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI1_DCWK_DIV, if_dcwk_div);
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI1_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_EDP_HDMI1_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_HDMI1 |
			    FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_EDP_HDMI1_MUX, vp->id);
		vaw = wk3588_get_hdmi_pow(powfwags);
		wegmap_wwite(vop2->vop_gwf, WK3588_GWF_VOP_CON2, HIWOWD_UPDATE(1, 4, 4));
		wegmap_wwite(vop2->vo1_gwf, WK3588_GWF_VO1_CON0, HIWOWD_UPDATE(vaw, 8, 7));
		bweak;
	case WOCKCHIP_VOP2_EP_EDP0:
		div &= ~WK3588_DSP_IF_EDP_HDMI0_DCWK_DIV;
		div &= ~WK3588_DSP_IF_EDP_HDMI0_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_DCWK_DIV, if_dcwk_div);
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_EDP_HDMI0_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_EDP0 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_EDP_HDMI0_MUX, vp->id);
		wegmap_wwite(vop2->vop_gwf, WK3588_GWF_VOP_CON2, HIWOWD_UPDATE(1, 0, 0));
		bweak;
	case WOCKCHIP_VOP2_EP_EDP1:
		div &= ~WK3588_DSP_IF_EDP_HDMI1_DCWK_DIV;
		div &= ~WK3588_DSP_IF_EDP_HDMI1_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_DCWK_DIV, if_dcwk_div);
		div |= FIEWD_PWEP(WK3588_DSP_IF_EDP_HDMI0_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_EDP_HDMI1_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_EDP1 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_EDP_HDMI1_MUX, vp->id);
		wegmap_wwite(vop2->vop_gwf, WK3588_GWF_VOP_CON2, HIWOWD_UPDATE(1, 3, 3));
		bweak;
	case WOCKCHIP_VOP2_EP_MIPI0:
		div &= ~WK3588_DSP_IF_MIPI0_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_MIPI0_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_MIPI0_MUX;
		vaw = wk3588_get_mipi_powt_mux(vp->id);
		die |= WK3588_SYS_DSP_INFACE_EN_MIPI0 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_MIPI0_MUX, !!vaw);
		bweak;
	case WOCKCHIP_VOP2_EP_MIPI1:
		div &= ~WK3588_DSP_IF_MIPI1_PCWK_DIV;
		div |= FIEWD_PWEP(WK3588_DSP_IF_MIPI1_PCWK_DIV, if_pixcwk_div);
		die &= ~WK3588_SYS_DSP_INFACE_EN_MIPI1_MUX;
		vaw = wk3588_get_mipi_powt_mux(vp->id);
		die |= WK3588_SYS_DSP_INFACE_EN_MIPI1 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_MIPI1_MUX, vaw);
		bweak;
	case WOCKCHIP_VOP2_EP_DP0:
		die &= ~WK3588_SYS_DSP_INFACE_EN_DP0_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_DP0 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_DP0_MUX, vp->id);
		dip &= ~WK3588_DSP_IF_POW__DP0_PIN_POW;
		dip |= FIEWD_PWEP(WK3588_DSP_IF_POW__DP0_PIN_POW, powfwags);
		bweak;
	case WOCKCHIP_VOP2_EP_DP1:
		die &= ~WK3588_SYS_DSP_INFACE_EN_MIPI1_MUX;
		die |= WK3588_SYS_DSP_INFACE_EN_MIPI1 |
			   FIEWD_PWEP(WK3588_SYS_DSP_INFACE_EN_MIPI1_MUX, vp->id);
		dip &= ~WK3588_DSP_IF_POW__DP1_PIN_POW;
		dip |= FIEWD_PWEP(WK3588_DSP_IF_POW__DP1_PIN_POW, powfwags);
		bweak;
	defauwt:
		dwm_eww(vop2->dwm, "Invawid intewface id %d on vp%d\n", id, vp->id);
		wetuwn 0;
	}

	dip |= WK3568_DSP_IF_POW__CFG_DONE_IMD;

	vop2_vp_wwite(vp, WK3588_VP_CWK_CTWW, vp_cwk_div);
	vop2_wwitew(vop2, WK3568_DSP_IF_EN, die);
	vop2_wwitew(vop2, WK3568_DSP_IF_CTWW, div);
	vop2_wwitew(vop2, WK3568_DSP_IF_POW, dip);

	wetuwn cwock;
}

static unsigned wong vop2_set_intf_mux(stwuct vop2_video_powt *vp, int ep_id, u32 powfwags)
{
	stwuct vop2 *vop2 = vp->vop2;

	if (vop2->data->soc_id == 3566 || vop2->data->soc_id == 3568)
		wetuwn wk3568_set_intf_mux(vp, ep_id, powfwags);
	ewse if (vop2->data->soc_id == 3588)
		wetuwn wk3588_set_intf_mux(vp, ep_id, powfwags);
	ewse
		wetuwn 0;
}

static int us_to_vewticaw_wine(stwuct dwm_dispway_mode *mode, int us)
{
	wetuwn us * mode->cwock / mode->htotaw / 1000;
}

static void vop2_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct vop2 *vop2 = vp->vop2;
	const stwuct vop2_data *vop2_data = vop2->data;
	const stwuct vop2_video_powt_data *vp_data = &vop2_data->vp[vp->id];
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(cwtc->state);
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	unsigned wong cwock = mode->cwtc_cwock * 1000;
	u16 hsync_wen = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;
	u16 hdispway = mode->cwtc_hdispway;
	u16 htotaw = mode->cwtc_htotaw;
	u16 hact_st = mode->cwtc_htotaw - mode->cwtc_hsync_stawt;
	u16 hact_end = hact_st + hdispway;
	u16 vdispway = mode->cwtc_vdispway;
	u16 vtotaw = mode->cwtc_vtotaw;
	u16 vsync_wen = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	u16 vact_st = mode->cwtc_vtotaw - mode->cwtc_vsync_stawt;
	u16 vact_end = vact_st + vdispway;
	u8 out_mode;
	u32 dsp_ctww = 0;
	int act_end;
	u32 vaw, powfwags;
	int wet;
	stwuct dwm_encodew *encodew;

	dwm_dbg(vop2->dwm, "Update mode to %dx%d%s%d, type: %d fow vp%d\n",
		hdispway, vdispway, mode->fwags & DWM_MODE_FWAG_INTEWWACE ? "i" : "p",
		dwm_mode_vwefwesh(mode), vcstate->output_type, vp->id);

	vop2_wock(vop2);

	wet = cwk_pwepawe_enabwe(vp->dcwk);
	if (wet < 0) {
		dwm_eww(vop2->dwm, "faiwed to enabwe dcwk fow video powt%d - %d\n",
			vp->id, wet);
		vop2_unwock(vop2);
		wetuwn;
	}

	if (!vop2->enabwe_count)
		vop2_enabwe(vop2);

	vop2->enabwe_count++;

	vcstate->yuv_ovewway = is_yuv_output(vcstate->bus_fowmat);

	vop2_cwtc_enabwe_iwq(vp, VP_INT_POST_BUF_EMPTY);

	powfwags = 0;
	if (vcstate->bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
		powfwags |= POWFWAG_DCWK_INV;
	if (mode->fwags & DWM_MODE_FWAG_PHSYNC)
		powfwags |= BIT(HSYNC_POSITIVE);
	if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
		powfwags |= BIT(VSYNC_POSITIVE);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc_state->encodew_mask) {
		stwuct wockchip_encodew *wkencodew = to_wockchip_encodew(encodew);

		/*
		 * fow dwive a high wesowution(4KP120, 8K), vop on wk3588/wk3576 need
		 * pwocess muwti(1/2/4/8) pixews pew cycwe, so the dcwk feed by the
		 * system cwu may be the 1/2 ow 1/4 of mode->cwock.
		 */
		cwock = vop2_set_intf_mux(vp, wkencodew->cwtc_endpoint_id, powfwags);
	}

	if (!cwock)
		wetuwn;

	if (vcstate->output_mode == WOCKCHIP_OUT_MODE_AAAA &&
	    !(vp_data->featuwe & VOP2_VP_FEATUWE_OUTPUT_10BIT))
		out_mode = WOCKCHIP_OUT_MODE_P888;
	ewse
		out_mode = vcstate->output_mode;

	dsp_ctww |= FIEWD_PWEP(WK3568_VP_DSP_CTWW__OUT_MODE, out_mode);

	if (vop2_output_uv_swap(vcstate->bus_fowmat, vcstate->output_mode))
		dsp_ctww |= WK3568_VP_DSP_CTWW__DSP_WB_SWAP;
	if (vop2_output_wg_swap(vop2, vcstate->bus_fowmat))
		dsp_ctww |= WK3568_VP_DSP_CTWW__DSP_WG_SWAP;

	if (vcstate->yuv_ovewway)
		dsp_ctww |= WK3568_VP_DSP_CTWW__POST_DSP_OUT_W2Y;

	vop2_dithew_setup(cwtc, &dsp_ctww);

	vop2_vp_wwite(vp, WK3568_VP_DSP_HTOTAW_HS_END, (htotaw << 16) | hsync_wen);
	vaw = hact_st << 16;
	vaw |= hact_end;
	vop2_vp_wwite(vp, WK3568_VP_DSP_HACT_ST_END, vaw);

	vaw = vact_st << 16;
	vaw |= vact_end;
	vop2_vp_wwite(vp, WK3568_VP_DSP_VACT_ST_END, vaw);

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		u16 vact_st_f1 = vtotaw + vact_st + 1;
		u16 vact_end_f1 = vact_st_f1 + vdispway;

		vaw = vact_st_f1 << 16 | vact_end_f1;
		vop2_vp_wwite(vp, WK3568_VP_DSP_VACT_ST_END_F1, vaw);

		vaw = vtotaw << 16 | (vtotaw + vsync_wen);
		vop2_vp_wwite(vp, WK3568_VP_DSP_VS_ST_END_F1, vaw);
		dsp_ctww |= WK3568_VP_DSP_CTWW__DSP_INTEWWACE;
		dsp_ctww |= WK3568_VP_DSP_CTWW__DSP_FIWED_POW;
		dsp_ctww |= WK3568_VP_DSP_CTWW__P2I_EN;
		vtotaw += vtotaw + 1;
		act_end = vact_end_f1;
	} ewse {
		act_end = vact_end;
	}

	vop2_wwitew(vop2, WK3568_VP_WINE_FWAG(vp->id),
		    (act_end - us_to_vewticaw_wine(mode, 0)) << 16 | act_end);

	vop2_vp_wwite(vp, WK3568_VP_DSP_VTOTAW_VS_END, vtotaw << 16 | vsync_wen);

	if (mode->fwags & DWM_MODE_FWAG_DBWCWK) {
		dsp_ctww |= WK3568_VP_DSP_CTWW__COWE_DCWK_DIV;
		cwock *= 2;
	}

	vop2_vp_wwite(vp, WK3568_VP_MIPI_CTWW, 0);

	cwk_set_wate(vp->dcwk, cwock);

	vop2_post_config(cwtc);

	vop2_cfg_done(vp);

	vop2_vp_wwite(vp, WK3568_VP_DSP_CTWW, dsp_ctww);

	dwm_cwtc_vbwank_on(cwtc);

	vop2_unwock(vop2);
}

static int vop2_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct dwm_pwane *pwane;
	int npwanes = 0;
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	dwm_atomic_cwtc_state_fow_each_pwane(pwane, cwtc_state)
		npwanes++;

	if (npwanes > vp->nwayews)
		wetuwn -EINVAW;

	wetuwn 0;
}

static boow is_opaque(u16 awpha)
{
	wetuwn (awpha >> 8) == 0xff;
}

static void vop2_pawse_awpha(stwuct vop2_awpha_config *awpha_config,
			     stwuct vop2_awpha *awpha)
{
	int swc_gwb_awpha_en = is_opaque(awpha_config->swc_gwb_awpha_vawue) ? 0 : 1;
	int dst_gwb_awpha_en = is_opaque(awpha_config->dst_gwb_awpha_vawue) ? 0 : 1;
	int swc_cowow_mode = awpha_config->swc_pwemuwti_en ?
				AWPHA_SWC_PWE_MUW : AWPHA_SWC_NO_PWE_MUW;
	int dst_cowow_mode = awpha_config->dst_pwemuwti_en ?
				AWPHA_SWC_PWE_MUW : AWPHA_SWC_NO_PWE_MUW;

	awpha->swc_cowow_ctww.vaw = 0;
	awpha->dst_cowow_ctww.vaw = 0;
	awpha->swc_awpha_ctww.vaw = 0;
	awpha->dst_awpha_ctww.vaw = 0;

	if (!awpha_config->swc_pixew_awpha_en)
		awpha->swc_cowow_ctww.bits.bwend_mode = AWPHA_GWOBAW;
	ewse if (awpha_config->swc_pixew_awpha_en && !swc_gwb_awpha_en)
		awpha->swc_cowow_ctww.bits.bwend_mode = AWPHA_PEW_PIX;
	ewse
		awpha->swc_cowow_ctww.bits.bwend_mode = AWPHA_PEW_PIX_GWOBAW;

	awpha->swc_cowow_ctww.bits.awpha_en = 1;

	if (awpha->swc_cowow_ctww.bits.bwend_mode == AWPHA_GWOBAW) {
		awpha->swc_cowow_ctww.bits.cowow_mode = swc_cowow_mode;
		awpha->swc_cowow_ctww.bits.factow_mode = SWC_FAC_AWPHA_SWC_GWOBAW;
	} ewse if (awpha->swc_cowow_ctww.bits.bwend_mode == AWPHA_PEW_PIX) {
		awpha->swc_cowow_ctww.bits.cowow_mode = swc_cowow_mode;
		awpha->swc_cowow_ctww.bits.factow_mode = SWC_FAC_AWPHA_ONE;
	} ewse {
		awpha->swc_cowow_ctww.bits.cowow_mode = AWPHA_SWC_PWE_MUW;
		awpha->swc_cowow_ctww.bits.factow_mode = SWC_FAC_AWPHA_SWC_GWOBAW;
	}
	awpha->swc_cowow_ctww.bits.gwb_awpha = awpha_config->swc_gwb_awpha_vawue >> 8;
	awpha->swc_cowow_ctww.bits.awpha_mode = AWPHA_STWAIGHT;
	awpha->swc_cowow_ctww.bits.awpha_caw_mode = AWPHA_SATUWATION;

	awpha->dst_cowow_ctww.bits.awpha_mode = AWPHA_STWAIGHT;
	awpha->dst_cowow_ctww.bits.awpha_caw_mode = AWPHA_SATUWATION;
	awpha->dst_cowow_ctww.bits.bwend_mode = AWPHA_GWOBAW;
	awpha->dst_cowow_ctww.bits.gwb_awpha = awpha_config->dst_gwb_awpha_vawue >> 8;
	awpha->dst_cowow_ctww.bits.cowow_mode = dst_cowow_mode;
	awpha->dst_cowow_ctww.bits.factow_mode = AWPHA_SWC_INVEWSE;

	awpha->swc_awpha_ctww.bits.awpha_mode = AWPHA_STWAIGHT;
	awpha->swc_awpha_ctww.bits.bwend_mode = awpha->swc_cowow_ctww.bits.bwend_mode;
	awpha->swc_awpha_ctww.bits.awpha_caw_mode = AWPHA_SATUWATION;
	awpha->swc_awpha_ctww.bits.factow_mode = AWPHA_ONE;

	awpha->dst_awpha_ctww.bits.awpha_mode = AWPHA_STWAIGHT;
	if (awpha_config->dst_pixew_awpha_en && !dst_gwb_awpha_en)
		awpha->dst_awpha_ctww.bits.bwend_mode = AWPHA_PEW_PIX;
	ewse
		awpha->dst_awpha_ctww.bits.bwend_mode = AWPHA_PEW_PIX_GWOBAW;
	awpha->dst_awpha_ctww.bits.awpha_caw_mode = AWPHA_NO_SATUWATION;
	awpha->dst_awpha_ctww.bits.factow_mode = AWPHA_SWC_INVEWSE;
}

static int vop2_find_stawt_mixew_id_fow_vp(stwuct vop2 *vop2, u8 powt_id)
{
	stwuct vop2_video_powt *vp;
	int used_wayew = 0;
	int i;

	fow (i = 0; i < powt_id; i++) {
		vp = &vop2->vps[i];
		used_wayew += hweight32(vp->win_mask);
	}

	wetuwn used_wayew;
}

static void vop2_setup_cwustew_awpha(stwuct vop2 *vop2, stwuct vop2_win *main_win)
{
	u32 offset = (main_win->data->phys_id * 0x10);
	stwuct vop2_awpha_config awpha_config;
	stwuct vop2_awpha awpha;
	stwuct dwm_pwane_state *bottom_win_pstate;
	boow swc_pixew_awpha_en = fawse;
	u16 swc_gwb_awpha_vaw, dst_gwb_awpha_vaw;
	boow pwemuwti_en = fawse;
	boow swap = fawse;

	/* At one win mode, win0 is dst/bottom win, and win1 is a aww zewo swc/top win */
	bottom_win_pstate = main_win->base.state;
	swc_gwb_awpha_vaw = 0;
	dst_gwb_awpha_vaw = main_win->base.state->awpha;

	if (!bottom_win_pstate->fb)
		wetuwn;

	awpha_config.swc_pwemuwti_en = pwemuwti_en;
	awpha_config.dst_pwemuwti_en = fawse;
	awpha_config.swc_pixew_awpha_en = swc_pixew_awpha_en;
	awpha_config.dst_pixew_awpha_en = twue; /* awpha vawue need twansfew to next mix */
	awpha_config.swc_gwb_awpha_vawue = swc_gwb_awpha_vaw;
	awpha_config.dst_gwb_awpha_vawue = dst_gwb_awpha_vaw;
	vop2_pawse_awpha(&awpha_config, &awpha);

	awpha.swc_cowow_ctww.bits.swc_dst_swap = swap;
	vop2_wwitew(vop2, WK3568_CWUSTEW0_MIX_SWC_COWOW_CTWW + offset,
		    awpha.swc_cowow_ctww.vaw);
	vop2_wwitew(vop2, WK3568_CWUSTEW0_MIX_DST_COWOW_CTWW + offset,
		    awpha.dst_cowow_ctww.vaw);
	vop2_wwitew(vop2, WK3568_CWUSTEW0_MIX_SWC_AWPHA_CTWW + offset,
		    awpha.swc_awpha_ctww.vaw);
	vop2_wwitew(vop2, WK3568_CWUSTEW0_MIX_DST_AWPHA_CTWW + offset,
		    awpha.dst_awpha_ctww.vaw);
}

static void vop2_setup_awpha(stwuct vop2_video_powt *vp)
{
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_fwamebuffew *fb;
	stwuct vop2_awpha_config awpha_config;
	stwuct vop2_awpha awpha;
	stwuct dwm_pwane *pwane;
	int pixew_awpha_en;
	int pwemuwti_en, gpwemuwti_en = 0;
	int mixew_id;
	u32 offset;
	boow bottom_wayew_awpha_en = fawse;
	u32 dst_gwobaw_awpha = DWM_BWEND_AWPHA_OPAQUE;

	mixew_id = vop2_find_stawt_mixew_id_fow_vp(vop2, vp->id);
	awpha_config.dst_pixew_awpha_en = twue; /* awpha vawue need twansfew to next mix */

	dwm_atomic_cwtc_fow_each_pwane(pwane, &vp->cwtc) {
		stwuct vop2_win *win = to_vop2_win(pwane);

		if (pwane->state->nowmawized_zpos == 0 &&
		    !is_opaque(pwane->state->awpha) &&
		    !vop2_cwustew_window(win)) {
			/*
			 * If bottom wayew have gwobaw awpha effect [except cwustew wayew,
			 * because cwustew have deaw with bottom wayew gwobaw awpha vawue
			 * at cwustew mix], bottom wayew mix need deaw with gwobaw awpha.
			 */
			bottom_wayew_awpha_en = twue;
			dst_gwobaw_awpha = pwane->state->awpha;
		}
	}

	dwm_atomic_cwtc_fow_each_pwane(pwane, &vp->cwtc) {
		stwuct vop2_win *win = to_vop2_win(pwane);
		int zpos = pwane->state->nowmawized_zpos;

		if (pwane->state->pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI)
			pwemuwti_en = 1;
		ewse
			pwemuwti_en = 0;

		pwane = &win->base;
		fb = pwane->state->fb;

		pixew_awpha_en = fb->fowmat->has_awpha;

		awpha_config.swc_pwemuwti_en = pwemuwti_en;

		if (bottom_wayew_awpha_en && zpos == 1) {
			gpwemuwti_en = pwemuwti_en;
			/* Cd = Cs + (1 - As) * Cd * Agd */
			awpha_config.dst_pwemuwti_en = fawse;
			awpha_config.swc_pixew_awpha_en = pixew_awpha_en;
			awpha_config.swc_gwb_awpha_vawue = pwane->state->awpha;
			awpha_config.dst_gwb_awpha_vawue = dst_gwobaw_awpha;
		} ewse if (vop2_cwustew_window(win)) {
			/* Mix output data onwy have pixew awpha */
			awpha_config.dst_pwemuwti_en = twue;
			awpha_config.swc_pixew_awpha_en = twue;
			awpha_config.swc_gwb_awpha_vawue = DWM_BWEND_AWPHA_OPAQUE;
			awpha_config.dst_gwb_awpha_vawue = DWM_BWEND_AWPHA_OPAQUE;
		} ewse {
			/* Cd = Cs + (1 - As) * Cd */
			awpha_config.dst_pwemuwti_en = twue;
			awpha_config.swc_pixew_awpha_en = pixew_awpha_en;
			awpha_config.swc_gwb_awpha_vawue = pwane->state->awpha;
			awpha_config.dst_gwb_awpha_vawue = DWM_BWEND_AWPHA_OPAQUE;
		}

		vop2_pawse_awpha(&awpha_config, &awpha);

		offset = (mixew_id + zpos - 1) * 0x10;
		vop2_wwitew(vop2, WK3568_MIX0_SWC_COWOW_CTWW + offset,
			    awpha.swc_cowow_ctww.vaw);
		vop2_wwitew(vop2, WK3568_MIX0_DST_COWOW_CTWW + offset,
			    awpha.dst_cowow_ctww.vaw);
		vop2_wwitew(vop2, WK3568_MIX0_SWC_AWPHA_CTWW + offset,
			    awpha.swc_awpha_ctww.vaw);
		vop2_wwitew(vop2, WK3568_MIX0_DST_AWPHA_CTWW + offset,
			    awpha.dst_awpha_ctww.vaw);
	}

	if (vp->id == 0) {
		if (bottom_wayew_awpha_en) {
			/* Twansfew pixew awpha to hdw mix */
			awpha_config.swc_pwemuwti_en = gpwemuwti_en;
			awpha_config.dst_pwemuwti_en = twue;
			awpha_config.swc_pixew_awpha_en = twue;
			awpha_config.swc_gwb_awpha_vawue = DWM_BWEND_AWPHA_OPAQUE;
			awpha_config.dst_gwb_awpha_vawue = DWM_BWEND_AWPHA_OPAQUE;
			vop2_pawse_awpha(&awpha_config, &awpha);

			vop2_wwitew(vop2, WK3568_HDW0_SWC_COWOW_CTWW,
				    awpha.swc_cowow_ctww.vaw);
			vop2_wwitew(vop2, WK3568_HDW0_DST_COWOW_CTWW,
				    awpha.dst_cowow_ctww.vaw);
			vop2_wwitew(vop2, WK3568_HDW0_SWC_AWPHA_CTWW,
				    awpha.swc_awpha_ctww.vaw);
			vop2_wwitew(vop2, WK3568_HDW0_DST_AWPHA_CTWW,
				    awpha.dst_awpha_ctww.vaw);
		} ewse {
			vop2_wwitew(vop2, WK3568_HDW0_SWC_COWOW_CTWW, 0);
		}
	}
}

static void vop2_setup_wayew_mixew(stwuct vop2_video_powt *vp)
{
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_pwane *pwane;
	u32 wayew_sew = 0;
	u32 powt_sew;
	unsigned int nwayew, ofs;
	u32 ovw_ctww;
	int i;
	stwuct vop2_video_powt *vp0 = &vop2->vps[0];
	stwuct vop2_video_powt *vp1 = &vop2->vps[1];
	stwuct vop2_video_powt *vp2 = &vop2->vps[2];
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(vp->cwtc.state);

	ovw_ctww = vop2_weadw(vop2, WK3568_OVW_CTWW);
	ovw_ctww |= WK3568_OVW_CTWW__WAYEWSEW_WEGDONE_IMD;
	if (vcstate->yuv_ovewway)
		ovw_ctww |= WK3568_OVW_CTWW__YUV_MODE(vp->id);
	ewse
		ovw_ctww &= ~WK3568_OVW_CTWW__YUV_MODE(vp->id);

	vop2_wwitew(vop2, WK3568_OVW_CTWW, ovw_ctww);

	powt_sew = vop2_weadw(vop2, WK3568_OVW_POWT_SEW);
	powt_sew &= WK3568_OVW_POWT_SEW__SEW_POWT;

	if (vp0->nwayews)
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT0_MUX,
				     vp0->nwayews - 1);
	ewse
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT0_MUX, 8);

	if (vp1->nwayews)
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT1_MUX,
				     (vp0->nwayews + vp1->nwayews - 1));
	ewse
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT1_MUX, 8);

	if (vp2->nwayews)
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT2_MUX,
			(vp2->nwayews + vp1->nwayews + vp0->nwayews - 1));
	ewse
		powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SET__POWT1_MUX, 8);

	wayew_sew = vop2_weadw(vop2, WK3568_OVW_WAYEW_SEW);

	ofs = 0;
	fow (i = 0; i < vp->id; i++)
		ofs += vop2->vps[i].nwayews;

	nwayew = 0;
	dwm_atomic_cwtc_fow_each_pwane(pwane, &vp->cwtc) {
		stwuct vop2_win *win = to_vop2_win(pwane);

		switch (win->data->phys_id) {
		case WOCKCHIP_VOP2_CWUSTEW0:
			powt_sew &= ~WK3568_OVW_POWT_SEW__CWUSTEW0;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__CWUSTEW0, vp->id);
			bweak;
		case WOCKCHIP_VOP2_CWUSTEW1:
			powt_sew &= ~WK3568_OVW_POWT_SEW__CWUSTEW1;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__CWUSTEW1, vp->id);
			bweak;
		case WOCKCHIP_VOP2_CWUSTEW2:
			powt_sew &= ~WK3588_OVW_POWT_SEW__CWUSTEW2;
			powt_sew |= FIEWD_PWEP(WK3588_OVW_POWT_SEW__CWUSTEW2, vp->id);
			bweak;
		case WOCKCHIP_VOP2_CWUSTEW3:
			powt_sew &= ~WK3588_OVW_POWT_SEW__CWUSTEW3;
			powt_sew |= FIEWD_PWEP(WK3588_OVW_POWT_SEW__CWUSTEW3, vp->id);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT0:
			powt_sew &= ~WK3568_OVW_POWT_SEW__ESMAWT0;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__ESMAWT0, vp->id);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT1:
			powt_sew &= ~WK3568_OVW_POWT_SEW__ESMAWT1;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__ESMAWT1, vp->id);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT2:
			powt_sew &= ~WK3588_OVW_POWT_SEW__ESMAWT2;
			powt_sew |= FIEWD_PWEP(WK3588_OVW_POWT_SEW__ESMAWT2, vp->id);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT3:
			powt_sew &= ~WK3588_OVW_POWT_SEW__ESMAWT3;
			powt_sew |= FIEWD_PWEP(WK3588_OVW_POWT_SEW__ESMAWT3, vp->id);
			bweak;
		case WOCKCHIP_VOP2_SMAWT0:
			powt_sew &= ~WK3568_OVW_POWT_SEW__SMAWT0;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__SMAWT0, vp->id);
			bweak;
		case WOCKCHIP_VOP2_SMAWT1:
			powt_sew &= ~WK3568_OVW_POWT_SEW__SMAWT1;
			powt_sew |= FIEWD_PWEP(WK3568_OVW_POWT_SEW__SMAWT1, vp->id);
			bweak;
		}

		wayew_sew &= ~WK3568_OVW_WAYEW_SEW__WAYEW(pwane->state->nowmawized_zpos + ofs,
							  0x7);
		wayew_sew |= WK3568_OVW_WAYEW_SEW__WAYEW(pwane->state->nowmawized_zpos + ofs,
							 win->data->wayew_sew_id);
		nwayew++;
	}

	/* configuwe unused wayews to 0x5 (wesewved) */
	fow (; nwayew < vp->nwayews; nwayew++) {
		wayew_sew &= ~WK3568_OVW_WAYEW_SEW__WAYEW(nwayew + ofs, 0x7);
		wayew_sew |= WK3568_OVW_WAYEW_SEW__WAYEW(nwayew + ofs, 5);
	}

	vop2_wwitew(vop2, WK3568_OVW_WAYEW_SEW, wayew_sew);
	vop2_wwitew(vop2, WK3568_OVW_POWT_SEW, powt_sew);
}

static void vop2_setup_dwy_fow_windows(stwuct vop2 *vop2)
{
	stwuct vop2_win *win;
	int i = 0;
	u32 cdwy = 0, sdwy = 0;

	fow (i = 0; i < vop2->data->win_size; i++) {
		u32 dwy;

		win = &vop2->win[i];
		dwy = win->deway;

		switch (win->data->phys_id) {
		case WOCKCHIP_VOP2_CWUSTEW0:
			cdwy |= FIEWD_PWEP(WK3568_CWUSTEW_DWY_NUM__CWUSTEW0_0, dwy);
			cdwy |= FIEWD_PWEP(WK3568_CWUSTEW_DWY_NUM__CWUSTEW0_1, dwy);
			bweak;
		case WOCKCHIP_VOP2_CWUSTEW1:
			cdwy |= FIEWD_PWEP(WK3568_CWUSTEW_DWY_NUM__CWUSTEW1_0, dwy);
			cdwy |= FIEWD_PWEP(WK3568_CWUSTEW_DWY_NUM__CWUSTEW1_1, dwy);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT0:
			sdwy |= FIEWD_PWEP(WK3568_SMAWT_DWY_NUM__ESMAWT0, dwy);
			bweak;
		case WOCKCHIP_VOP2_ESMAWT1:
			sdwy |= FIEWD_PWEP(WK3568_SMAWT_DWY_NUM__ESMAWT1, dwy);
			bweak;
		case WOCKCHIP_VOP2_SMAWT0:
			sdwy |= FIEWD_PWEP(WK3568_SMAWT_DWY_NUM__SMAWT0, dwy);
			bweak;
		case WOCKCHIP_VOP2_SMAWT1:
			sdwy |= FIEWD_PWEP(WK3568_SMAWT_DWY_NUM__SMAWT1, dwy);
			bweak;
		}
	}

	vop2_wwitew(vop2, WK3568_CWUSTEW_DWY_NUM, cdwy);
	vop2_wwitew(vop2, WK3568_SMAWT_DWY_NUM, sdwy);
}

static void vop2_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);
	stwuct vop2 *vop2 = vp->vop2;
	stwuct dwm_pwane *pwane;

	vp->win_mask = 0;

	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		stwuct vop2_win *win = to_vop2_win(pwane);

		win->deway = win->data->dwy[VOP2_DWY_MODE_DEFAUWT];

		vp->win_mask |= BIT(win->data->phys_id);

		if (vop2_cwustew_window(win))
			vop2_setup_cwustew_awpha(vop2, win);
	}

	if (!vp->win_mask)
		wetuwn;

	vop2_setup_wayew_mixew(vp);
	vop2_setup_awpha(vp);
	vop2_setup_dwy_fow_windows(vop2);
}

static void vop2_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct vop2_video_powt *vp = to_vop2_video_powt(cwtc);

	vop2_post_config(cwtc);

	vop2_cfg_done(vp);

	spin_wock_iwq(&cwtc->dev->event_wock);

	if (cwtc->state->event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc));
		vp->event = cwtc->state->event;
		cwtc->state->event = NUWW;
	}

	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static const stwuct dwm_cwtc_hewpew_funcs vop2_cwtc_hewpew_funcs = {
	.mode_fixup = vop2_cwtc_mode_fixup,
	.atomic_check = vop2_cwtc_atomic_check,
	.atomic_begin = vop2_cwtc_atomic_begin,
	.atomic_fwush = vop2_cwtc_atomic_fwush,
	.atomic_enabwe = vop2_cwtc_atomic_enabwe,
	.atomic_disabwe = vop2_cwtc_atomic_disabwe,
};

static stwuct dwm_cwtc_state *vop2_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct wockchip_cwtc_state *vcstate;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	vcstate = kmemdup(to_wockchip_cwtc_state(cwtc->state),
			  sizeof(*vcstate), GFP_KEWNEW);
	if (!vcstate)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &vcstate->base);

	wetuwn &vcstate->base;
}

static void vop2_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_cwtc_state *state)
{
	stwuct wockchip_cwtc_state *vcstate = to_wockchip_cwtc_state(state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(&vcstate->base);
	kfwee(vcstate);
}

static void vop2_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct wockchip_cwtc_state *vcstate =
		kzawwoc(sizeof(*vcstate), GFP_KEWNEW);

	if (cwtc->state)
		vop2_cwtc_destwoy_state(cwtc, cwtc->state);

	if (vcstate)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &vcstate->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

static const stwuct dwm_cwtc_funcs vop2_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.destwoy = dwm_cwtc_cweanup,
	.weset = vop2_cwtc_weset,
	.atomic_dupwicate_state = vop2_cwtc_dupwicate_state,
	.atomic_destwoy_state = vop2_cwtc_destwoy_state,
	.enabwe_vbwank = vop2_cwtc_enabwe_vbwank,
	.disabwe_vbwank = vop2_cwtc_disabwe_vbwank,
};

static iwqwetuwn_t vop2_isw(int iwq, void *data)
{
	stwuct vop2 *vop2 = data;
	const stwuct vop2_data *vop2_data = vop2->data;
	u32 axi_iwqs[VOP2_SYS_AXI_BUS_NUM];
	int wet = IWQ_NONE;
	int i;

	/*
	 * The iwq is shawed with the iommu. If the wuntime-pm state of the
	 * vop2-device is disabwed the iwq has to be tawgeted at the iommu.
	 */
	if (!pm_wuntime_get_if_in_use(vop2->dev))
		wetuwn IWQ_NONE;

	fow (i = 0; i < vop2_data->nw_vps; i++) {
		stwuct vop2_video_powt *vp = &vop2->vps[i];
		stwuct dwm_cwtc *cwtc = &vp->cwtc;
		u32 iwqs;

		iwqs = vop2_weadw(vop2, WK3568_VP_INT_STATUS(vp->id));
		vop2_wwitew(vop2, WK3568_VP_INT_CWW(vp->id), iwqs << 16 | iwqs);

		if (iwqs & VP_INT_DSP_HOWD_VAWID) {
			compwete(&vp->dsp_howd_compwetion);
			wet = IWQ_HANDWED;
		}

		if (iwqs & VP_INT_FS_FIEWD) {
			dwm_cwtc_handwe_vbwank(cwtc);
			spin_wock(&cwtc->dev->event_wock);
			if (vp->event) {
				u32 vaw = vop2_weadw(vop2, WK3568_WEG_CFG_DONE);

				if (!(vaw & BIT(vp->id))) {
					dwm_cwtc_send_vbwank_event(cwtc, vp->event);
					vp->event = NUWW;
					dwm_cwtc_vbwank_put(cwtc);
				}
			}
			spin_unwock(&cwtc->dev->event_wock);

			wet = IWQ_HANDWED;
		}

		if (iwqs & VP_INT_POST_BUF_EMPTY) {
			dwm_eww_watewimited(vop2->dwm,
					    "POST_BUF_EMPTY iwq eww at vp%d\n",
					    vp->id);
			wet = IWQ_HANDWED;
		}
	}

	axi_iwqs[0] = vop2_weadw(vop2, WK3568_SYS0_INT_STATUS);
	vop2_wwitew(vop2, WK3568_SYS0_INT_CWW, axi_iwqs[0] << 16 | axi_iwqs[0]);
	axi_iwqs[1] = vop2_weadw(vop2, WK3568_SYS1_INT_STATUS);
	vop2_wwitew(vop2, WK3568_SYS1_INT_CWW, axi_iwqs[1] << 16 | axi_iwqs[1]);

	fow (i = 0; i < AWWAY_SIZE(axi_iwqs); i++) {
		if (axi_iwqs[i] & VOP2_INT_BUS_EWWPW) {
			dwm_eww_watewimited(vop2->dwm, "BUS_EWWOW iwq eww\n");
			wet = IWQ_HANDWED;
		}
	}

	pm_wuntime_put(vop2->dev);

	wetuwn wet;
}

static int vop2_pwane_init(stwuct vop2 *vop2, stwuct vop2_win *win,
			   unsigned wong possibwe_cwtcs)
{
	const stwuct vop2_win_data *win_data = win->data;
	unsigned int bwend_caps = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				  BIT(DWM_MODE_BWEND_PWEMUWTI) |
				  BIT(DWM_MODE_BWEND_COVEWAGE);
	int wet;

	wet = dwm_univewsaw_pwane_init(vop2->dwm, &win->base, possibwe_cwtcs,
				       &vop2_pwane_funcs, win_data->fowmats,
				       win_data->nfowmats,
				       win_data->fowmat_modifiews,
				       win->type, win_data->name);
	if (wet) {
		dwm_eww(vop2->dwm, "faiwed to initiawize pwane %d\n", wet);
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(&win->base, &vop2_pwane_hewpew_funcs);

	if (win->data->suppowted_wotations)
		dwm_pwane_cweate_wotation_pwopewty(&win->base, DWM_MODE_WOTATE_0,
						   DWM_MODE_WOTATE_0 |
						   win->data->suppowted_wotations);
	dwm_pwane_cweate_awpha_pwopewty(&win->base);
	dwm_pwane_cweate_bwend_mode_pwopewty(&win->base, bwend_caps);
	dwm_pwane_cweate_zpos_pwopewty(&win->base, win->win_id, 0,
				       vop2->wegistewed_num_wins - 1);

	wetuwn 0;
}

static stwuct vop2_video_powt *find_vp_without_pwimawy(stwuct vop2 *vop2)
{
	int i;

	fow (i = 0; i < vop2->data->nw_vps; i++) {
		stwuct vop2_video_powt *vp = &vop2->vps[i];

		if (!vp->cwtc.powt)
			continue;
		if (vp->pwimawy_pwane)
			continue;

		wetuwn vp;
	}

	wetuwn NUWW;
}

static int vop2_cweate_cwtcs(stwuct vop2 *vop2)
{
	const stwuct vop2_data *vop2_data = vop2->data;
	stwuct dwm_device *dwm = vop2->dwm;
	stwuct device *dev = vop2->dev;
	stwuct dwm_pwane *pwane;
	stwuct device_node *powt;
	stwuct vop2_video_powt *vp;
	int i, nvp, nvps = 0;
	int wet;

	fow (i = 0; i < vop2_data->nw_vps; i++) {
		const stwuct vop2_video_powt_data *vp_data;
		stwuct device_node *np;
		chaw dcwk_name[9];

		vp_data = &vop2_data->vp[i];
		vp = &vop2->vps[i];
		vp->vop2 = vop2;
		vp->id = vp_data->id;
		vp->data = vp_data;

		snpwintf(dcwk_name, sizeof(dcwk_name), "dcwk_vp%d", vp->id);
		vp->dcwk = devm_cwk_get(vop2->dev, dcwk_name);
		if (IS_EWW(vp->dcwk)) {
			dwm_eww(vop2->dwm, "faiwed to get %s\n", dcwk_name);
			wetuwn PTW_EWW(vp->dcwk);
		}

		np = of_gwaph_get_wemote_node(dev->of_node, i, -1);
		if (!np) {
			dwm_dbg(vop2->dwm, "%s: No wemote fow vp%d\n", __func__, i);
			continue;
		}
		of_node_put(np);

		powt = of_gwaph_get_powt_by_id(dev->of_node, i);
		if (!powt) {
			dwm_eww(vop2->dwm, "no powt node found fow video_powt%d\n", i);
			wetuwn -ENOENT;
		}

		vp->cwtc.powt = powt;
		nvps++;
	}

	nvp = 0;
	fow (i = 0; i < vop2->wegistewed_num_wins; i++) {
		stwuct vop2_win *win = &vop2->win[i];
		u32 possibwe_cwtcs = 0;

		if (vop2->data->soc_id == 3566) {
			/*
			 * On WK3566 these windows don't have an independent
			 * fwamebuffew. They shawe the fwamebuffew with smawt0,
			 * esmawt0 and cwustew0 wespectivewy.
			 */
			switch (win->data->phys_id) {
			case WOCKCHIP_VOP2_SMAWT1:
			case WOCKCHIP_VOP2_ESMAWT1:
			case WOCKCHIP_VOP2_CWUSTEW1:
				continue;
			}
		}

		if (win->type == DWM_PWANE_TYPE_PWIMAWY) {
			vp = find_vp_without_pwimawy(vop2);
			if (vp) {
				possibwe_cwtcs = BIT(nvp);
				vp->pwimawy_pwane = win;
				nvp++;
			} ewse {
				/* change the unused pwimawy window to ovewway window */
				win->type = DWM_PWANE_TYPE_OVEWWAY;
			}
		}

		if (win->type == DWM_PWANE_TYPE_OVEWWAY)
			possibwe_cwtcs = (1 << nvps) - 1;

		wet = vop2_pwane_init(vop2, win, possibwe_cwtcs);
		if (wet) {
			dwm_eww(vop2->dwm, "faiwed to init pwane %s: %d\n",
				win->data->name, wet);
			wetuwn wet;
		}
	}

	fow (i = 0; i < vop2_data->nw_vps; i++) {
		vp = &vop2->vps[i];

		if (!vp->cwtc.powt)
			continue;

		pwane = &vp->pwimawy_pwane->base;

		wet = dwm_cwtc_init_with_pwanes(dwm, &vp->cwtc, pwane, NUWW,
						&vop2_cwtc_funcs,
						"video_powt%d", vp->id);
		if (wet) {
			dwm_eww(vop2->dwm, "cwtc init fow video_powt%d faiwed\n", i);
			wetuwn wet;
		}

		dwm_cwtc_hewpew_add(&vp->cwtc, &vop2_cwtc_hewpew_funcs);

		init_compwetion(&vp->dsp_howd_compwetion);
	}

	/*
	 * On the VOP2 it's vewy hawd to change the numbew of wayews on a VP
	 * duwing wuntime, so we distwibute the wayews equawwy ovew the used
	 * VPs
	 */
	fow (i = 0; i < vop2->data->nw_vps; i++) {
		stwuct vop2_video_powt *vp = &vop2->vps[i];

		if (vp->cwtc.powt)
			vp->nwayews = vop2_data->win_size / nvps;
	}

	wetuwn 0;
}

static void vop2_destwoy_cwtcs(stwuct vop2 *vop2)
{
	stwuct dwm_device *dwm = vop2->dwm;
	stwuct wist_head *cwtc_wist = &dwm->mode_config.cwtc_wist;
	stwuct wist_head *pwane_wist = &dwm->mode_config.pwane_wist;
	stwuct dwm_cwtc *cwtc, *tmpc;
	stwuct dwm_pwane *pwane, *tmpp;

	wist_fow_each_entwy_safe(pwane, tmpp, pwane_wist, head)
		dwm_pwane_cweanup(pwane);

	/*
	 * Destwoy CWTC aftew vop2_pwane_destwoy() since vop2_disabwe_pwane()
	 * wefewences the CWTC.
	 */
	wist_fow_each_entwy_safe(cwtc, tmpc, cwtc_wist, head) {
		of_node_put(cwtc->powt);
		dwm_cwtc_cweanup(cwtc);
	}
}

static int vop2_find_wgb_encodew(stwuct vop2 *vop2)
{
	stwuct device_node *node = vop2->dev->of_node;
	stwuct device_node *endpoint;
	int i;

	fow (i = 0; i < vop2->data->nw_vps; i++) {
		endpoint = of_gwaph_get_endpoint_by_wegs(node, i,
							 WOCKCHIP_VOP2_EP_WGB0);
		if (!endpoint)
			continue;

		of_node_put(endpoint);
		wetuwn i;
	}

	wetuwn -ENOENT;
}

static stwuct weg_fiewd vop2_cwustew_wegs[VOP2_WIN_MAX_WEG] = {
	[VOP2_WIN_ENABWE] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 0, 0),
	[VOP2_WIN_FOWMAT] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 1, 5),
	[VOP2_WIN_WB_SWAP] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 14, 14),
	[VOP2_WIN_DITHEW_UP] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 18, 18),
	[VOP2_WIN_ACT_INFO] = WEG_FIEWD(WK3568_CWUSTEW_WIN_ACT_INFO, 0, 31),
	[VOP2_WIN_DSP_INFO] = WEG_FIEWD(WK3568_CWUSTEW_WIN_DSP_INFO, 0, 31),
	[VOP2_WIN_DSP_ST] = WEG_FIEWD(WK3568_CWUSTEW_WIN_DSP_ST, 0, 31),
	[VOP2_WIN_YWGB_MST] = WEG_FIEWD(WK3568_CWUSTEW_WIN_YWGB_MST, 0, 31),
	[VOP2_WIN_UV_MST] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CBW_MST, 0, 31),
	[VOP2_WIN_YUV_CWIP] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 19, 19),
	[VOP2_WIN_YWGB_VIW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_VIW, 0, 15),
	[VOP2_WIN_UV_VIW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_VIW, 16, 31),
	[VOP2_WIN_Y2W_EN] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 8, 8),
	[VOP2_WIN_W2Y_EN] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 9, 9),
	[VOP2_WIN_CSC_MODE] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW0, 10, 11),

	/* Scawe */
	[VOP2_WIN_SCAWE_YWGB_X] = WEG_FIEWD(WK3568_CWUSTEW_WIN_SCW_FACTOW_YWGB, 0, 15),
	[VOP2_WIN_SCAWE_YWGB_Y] = WEG_FIEWD(WK3568_CWUSTEW_WIN_SCW_FACTOW_YWGB, 16, 31),
	[VOP2_WIN_YWGB_VEW_SCW_MODE] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW1, 14, 15),
	[VOP2_WIN_YWGB_HOW_SCW_MODE] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW1, 12, 13),
	[VOP2_WIN_BIC_COE_SEW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW1, 2, 3),
	[VOP2_WIN_VSD_YWGB_GT2] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW1, 28, 28),
	[VOP2_WIN_VSD_YWGB_GT4] = WEG_FIEWD(WK3568_CWUSTEW_WIN_CTWW1, 29, 29),

	/* cwustew wegs */
	[VOP2_WIN_AFBC_ENABWE] = WEG_FIEWD(WK3568_CWUSTEW_CTWW, 1, 1),
	[VOP2_WIN_CWUSTEW_ENABWE] = WEG_FIEWD(WK3568_CWUSTEW_CTWW, 0, 0),
	[VOP2_WIN_CWUSTEW_WB_MODE] = WEG_FIEWD(WK3568_CWUSTEW_CTWW, 4, 7),

	/* afbc wegs */
	[VOP2_WIN_AFBC_FOWMAT] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_CTWW, 2, 6),
	[VOP2_WIN_AFBC_WB_SWAP] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_CTWW, 9, 9),
	[VOP2_WIN_AFBC_UV_SWAP] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_CTWW, 10, 10),
	[VOP2_WIN_AFBC_AUTO_GATING_EN] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_OUTPUT_CTWW, 4, 4),
	[VOP2_WIN_AFBC_HAWF_BWOCK_EN] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_CTWW, 7, 7),
	[VOP2_WIN_AFBC_BWOCK_SPWIT_EN] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_CTWW, 8, 8),
	[VOP2_WIN_AFBC_HDW_PTW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_HDW_PTW, 0, 31),
	[VOP2_WIN_AFBC_PIC_SIZE] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_PIC_SIZE, 0, 31),
	[VOP2_WIN_AFBC_PIC_VIW_WIDTH] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_VIW_WIDTH, 0, 15),
	[VOP2_WIN_AFBC_TIWE_NUM] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_VIW_WIDTH, 16, 31),
	[VOP2_WIN_AFBC_PIC_OFFSET] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_PIC_OFFSET, 0, 31),
	[VOP2_WIN_AFBC_DSP_OFFSET] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_DSP_OFFSET, 0, 31),
	[VOP2_WIN_AFBC_TWANSFOWM_OFFSET] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_TWANSFOWM_OFFSET, 0, 31),
	[VOP2_WIN_AFBC_WOTATE_90] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_WOTATE_MODE, 0, 0),
	[VOP2_WIN_AFBC_WOTATE_270] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_WOTATE_MODE, 1, 1),
	[VOP2_WIN_XMIWWOW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_WOTATE_MODE, 2, 2),
	[VOP2_WIN_YMIWWOW] = WEG_FIEWD(WK3568_CWUSTEW_WIN_AFBCD_WOTATE_MODE, 3, 3),
	[VOP2_WIN_UV_SWAP] = { .weg = 0xffffffff },
	[VOP2_WIN_COWOW_KEY] = { .weg = 0xffffffff },
	[VOP2_WIN_COWOW_KEY_EN] = { .weg = 0xffffffff },
	[VOP2_WIN_SCAWE_CBCW_X] = { .weg = 0xffffffff },
	[VOP2_WIN_SCAWE_CBCW_Y] = { .weg = 0xffffffff },
	[VOP2_WIN_YWGB_HSCW_FIWTEW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_YWGB_VSCW_FIWTEW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_CBCW_VEW_SCW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_CBCW_HSCW_FIWTEW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_CBCW_HOW_SCW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_CBCW_VSCW_FIWTEW_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_VSD_CBCW_GT2] = { .weg = 0xffffffff },
	[VOP2_WIN_VSD_CBCW_GT4] = { .weg = 0xffffffff },
};

static int vop2_cwustew_init(stwuct vop2_win *win)
{
	stwuct vop2 *vop2 = win->vop2;
	stwuct weg_fiewd *cwustew_wegs;
	int wet, i;

	cwustew_wegs = kmemdup(vop2_cwustew_wegs, sizeof(vop2_cwustew_wegs),
			       GFP_KEWNEW);
	if (!cwustew_wegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(vop2_cwustew_wegs); i++)
		if (cwustew_wegs[i].weg != 0xffffffff)
			cwustew_wegs[i].weg += win->offset;

	wet = devm_wegmap_fiewd_buwk_awwoc(vop2->dev, vop2->map, win->weg,
					   cwustew_wegs,
					   AWWAY_SIZE(vop2_cwustew_wegs));

	kfwee(cwustew_wegs);

	wetuwn wet;
};

static stwuct weg_fiewd vop2_esmawt_wegs[VOP2_WIN_MAX_WEG] = {
	[VOP2_WIN_ENABWE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 0, 0),
	[VOP2_WIN_FOWMAT] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 1, 5),
	[VOP2_WIN_DITHEW_UP] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 12, 12),
	[VOP2_WIN_WB_SWAP] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 14, 14),
	[VOP2_WIN_UV_SWAP] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 16, 16),
	[VOP2_WIN_ACT_INFO] = WEG_FIEWD(WK3568_SMAWT_WEGION0_ACT_INFO, 0, 31),
	[VOP2_WIN_DSP_INFO] = WEG_FIEWD(WK3568_SMAWT_WEGION0_DSP_INFO, 0, 31),
	[VOP2_WIN_DSP_ST] = WEG_FIEWD(WK3568_SMAWT_WEGION0_DSP_ST, 0, 28),
	[VOP2_WIN_YWGB_MST] = WEG_FIEWD(WK3568_SMAWT_WEGION0_YWGB_MST, 0, 31),
	[VOP2_WIN_UV_MST] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CBW_MST, 0, 31),
	[VOP2_WIN_YUV_CWIP] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 17, 17),
	[VOP2_WIN_YWGB_VIW] = WEG_FIEWD(WK3568_SMAWT_WEGION0_VIW, 0, 15),
	[VOP2_WIN_UV_VIW] = WEG_FIEWD(WK3568_SMAWT_WEGION0_VIW, 16, 31),
	[VOP2_WIN_Y2W_EN] = WEG_FIEWD(WK3568_SMAWT_CTWW0, 0, 0),
	[VOP2_WIN_W2Y_EN] = WEG_FIEWD(WK3568_SMAWT_CTWW0, 1, 1),
	[VOP2_WIN_CSC_MODE] = WEG_FIEWD(WK3568_SMAWT_CTWW0, 2, 3),
	[VOP2_WIN_YMIWWOW] = WEG_FIEWD(WK3568_SMAWT_CTWW1, 31, 31),
	[VOP2_WIN_COWOW_KEY] = WEG_FIEWD(WK3568_SMAWT_COWOW_KEY_CTWW, 0, 29),
	[VOP2_WIN_COWOW_KEY_EN] = WEG_FIEWD(WK3568_SMAWT_COWOW_KEY_CTWW, 31, 31),

	/* Scawe */
	[VOP2_WIN_SCAWE_YWGB_X] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_FACTOW_YWGB, 0, 15),
	[VOP2_WIN_SCAWE_YWGB_Y] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_FACTOW_YWGB, 16, 31),
	[VOP2_WIN_SCAWE_CBCW_X] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_FACTOW_CBW, 0, 15),
	[VOP2_WIN_SCAWE_CBCW_Y] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_FACTOW_CBW, 16, 31),
	[VOP2_WIN_YWGB_HOW_SCW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 0, 1),
	[VOP2_WIN_YWGB_HSCW_FIWTEW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 2, 3),
	[VOP2_WIN_YWGB_VEW_SCW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 4, 5),
	[VOP2_WIN_YWGB_VSCW_FIWTEW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 6, 7),
	[VOP2_WIN_CBCW_HOW_SCW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 8, 9),
	[VOP2_WIN_CBCW_HSCW_FIWTEW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 10, 11),
	[VOP2_WIN_CBCW_VEW_SCW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 12, 13),
	[VOP2_WIN_CBCW_VSCW_FIWTEW_MODE] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 14, 15),
	[VOP2_WIN_BIC_COE_SEW] = WEG_FIEWD(WK3568_SMAWT_WEGION0_SCW_CTWW, 16, 17),
	[VOP2_WIN_VSD_YWGB_GT2] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 8, 8),
	[VOP2_WIN_VSD_YWGB_GT4] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 9, 9),
	[VOP2_WIN_VSD_CBCW_GT2] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 10, 10),
	[VOP2_WIN_VSD_CBCW_GT4] = WEG_FIEWD(WK3568_SMAWT_WEGION0_CTWW, 11, 11),
	[VOP2_WIN_XMIWWOW] = { .weg = 0xffffffff },
	[VOP2_WIN_CWUSTEW_ENABWE] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_ENABWE] = { .weg = 0xffffffff },
	[VOP2_WIN_CWUSTEW_WB_MODE] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_FOWMAT] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_WB_SWAP] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_UV_SWAP] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_AUTO_GATING_EN] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_BWOCK_SPWIT_EN] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_PIC_VIW_WIDTH] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_TIWE_NUM] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_PIC_OFFSET] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_PIC_SIZE] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_DSP_OFFSET] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_TWANSFOWM_OFFSET] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_HDW_PTW] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_HAWF_BWOCK_EN] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_WOTATE_270] = { .weg = 0xffffffff },
	[VOP2_WIN_AFBC_WOTATE_90] = { .weg = 0xffffffff },
};

static int vop2_esmawt_init(stwuct vop2_win *win)
{
	stwuct vop2 *vop2 = win->vop2;
	stwuct weg_fiewd *esmawt_wegs;
	int wet, i;

	esmawt_wegs = kmemdup(vop2_esmawt_wegs, sizeof(vop2_esmawt_wegs),
			      GFP_KEWNEW);
	if (!esmawt_wegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(vop2_esmawt_wegs); i++)
		if (esmawt_wegs[i].weg != 0xffffffff)
			esmawt_wegs[i].weg += win->offset;

	wet = devm_wegmap_fiewd_buwk_awwoc(vop2->dev, vop2->map, win->weg,
					   esmawt_wegs,
					   AWWAY_SIZE(vop2_esmawt_wegs));

	kfwee(esmawt_wegs);

	wetuwn wet;
};

static int vop2_win_init(stwuct vop2 *vop2)
{
	const stwuct vop2_data *vop2_data = vop2->data;
	stwuct vop2_win *win;
	int i, wet;

	fow (i = 0; i < vop2_data->win_size; i++) {
		const stwuct vop2_win_data *win_data = &vop2_data->win[i];

		win = &vop2->win[i];
		win->data = win_data;
		win->type = win_data->type;
		win->offset = win_data->base;
		win->win_id = i;
		win->vop2 = vop2;
		if (vop2_cwustew_window(win))
			wet = vop2_cwustew_init(win);
		ewse
			wet = vop2_esmawt_init(win);
		if (wet)
			wetuwn wet;
	}

	vop2->wegistewed_num_wins = vop2_data->win_size;

	wetuwn 0;
}

/*
 * The window wegistews awe onwy updated when config done is wwitten.
 * Untiw that they wead back the owd vawue. As we wead-modify-wwite
 * these wegistews mawk them as non-vowatiwe. This makes suwe we wead
 * the new vawues fwom the wegmap wegistew cache.
 */
static const stwuct wegmap_wange vop2_nonvowatiwe_wange[] = {
	wegmap_weg_wange(0x1000, 0x23ff),
};

static const stwuct wegmap_access_tabwe vop2_vowatiwe_tabwe = {
	.no_wanges = vop2_nonvowatiwe_wange,
	.n_no_wanges = AWWAY_SIZE(vop2_nonvowatiwe_wange),
};

static const stwuct wegmap_config vop2_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= 0x3000,
	.name		= "vop2",
	.vowatiwe_tabwe	= &vop2_vowatiwe_tabwe,
	.cache_type	= WEGCACHE_MAPWE,
};

static int vop2_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const stwuct vop2_data *vop2_data;
	stwuct dwm_device *dwm = data;
	stwuct vop2 *vop2;
	stwuct wesouwce *wes;
	size_t awwoc_size;
	int wet;

	vop2_data = of_device_get_match_data(dev);
	if (!vop2_data)
		wetuwn -ENODEV;

	/* Awwocate vop2 stwuct and its vop2_win awway */
	awwoc_size = stwuct_size(vop2, win, vop2_data->win_size);
	vop2 = devm_kzawwoc(dev, awwoc_size, GFP_KEWNEW);
	if (!vop2)
		wetuwn -ENOMEM;

	vop2->dev = dev;
	vop2->data = vop2_data;
	vop2->dwm = dwm;

	dev_set_dwvdata(dev, vop2);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "vop");
	if (!wes) {
		dwm_eww(vop2->dwm, "faiwed to get vop2 wegistew byname\n");
		wetuwn -EINVAW;
	}

	vop2->wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(vop2->wegs))
		wetuwn PTW_EWW(vop2->wegs);
	vop2->wen = wesouwce_size(wes);

	vop2->map = devm_wegmap_init_mmio(dev, vop2->wegs, &vop2_wegmap_config);
	if (IS_EWW(vop2->map))
		wetuwn PTW_EWW(vop2->map);

	wet = vop2_win_init(vop2);
	if (wet)
		wetuwn wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "gamma-wut");
	if (wes) {
		vop2->wut_wegs = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(vop2->wut_wegs))
			wetuwn PTW_EWW(vop2->wut_wegs);
	}
	if (vop2_data->featuwe & VOP2_FEATUWE_HAS_SYS_GWF) {
		vop2->sys_gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wockchip,gwf");
		if (IS_EWW(vop2->sys_gwf))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vop2->sys_gwf), "cannot get sys_gwf");
	}

	if (vop2_data->featuwe & VOP2_FEATUWE_HAS_VOP_GWF) {
		vop2->vop_gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wockchip,vop-gwf");
		if (IS_EWW(vop2->vop_gwf))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vop2->vop_gwf), "cannot get vop_gwf");
	}

	if (vop2_data->featuwe & VOP2_FEATUWE_HAS_VO1_GWF) {
		vop2->vo1_gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wockchip,vo1-gwf");
		if (IS_EWW(vop2->vo1_gwf))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vop2->vo1_gwf), "cannot get vo1_gwf");
	}

	if (vop2_data->featuwe & VOP2_FEATUWE_HAS_SYS_PMU) {
		vop2->sys_pmu = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wockchip,pmu");
		if (IS_EWW(vop2->sys_pmu))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vop2->sys_pmu), "cannot get sys_pmu");
	}

	vop2->hcwk = devm_cwk_get(vop2->dev, "hcwk");
	if (IS_EWW(vop2->hcwk)) {
		dwm_eww(vop2->dwm, "faiwed to get hcwk souwce\n");
		wetuwn PTW_EWW(vop2->hcwk);
	}

	vop2->acwk = devm_cwk_get(vop2->dev, "acwk");
	if (IS_EWW(vop2->acwk)) {
		dwm_eww(vop2->dwm, "faiwed to get acwk souwce\n");
		wetuwn PTW_EWW(vop2->acwk);
	}

	vop2->pcwk = devm_cwk_get_optionaw(vop2->dev, "pcwk_vop");
	if (IS_EWW(vop2->pcwk)) {
		dwm_eww(vop2->dwm, "faiwed to get pcwk souwce\n");
		wetuwn PTW_EWW(vop2->pcwk);
	}

	vop2->iwq = pwatfowm_get_iwq(pdev, 0);
	if (vop2->iwq < 0) {
		dwm_eww(vop2->dwm, "cannot find iwq fow vop2\n");
		wetuwn vop2->iwq;
	}

	mutex_init(&vop2->vop2_wock);

	wet = devm_wequest_iwq(dev, vop2->iwq, vop2_isw, IWQF_SHAWED, dev_name(dev), vop2);
	if (wet)
		wetuwn wet;

	wet = vop2_cweate_cwtcs(vop2);
	if (wet)
		wetuwn wet;

	wet = vop2_find_wgb_encodew(vop2);
	if (wet >= 0) {
		vop2->wgb = wockchip_wgb_init(dev, &vop2->vps[wet].cwtc,
					      vop2->dwm, wet);
		if (IS_EWW(vop2->wgb)) {
			if (PTW_EWW(vop2->wgb) == -EPWOBE_DEFEW) {
				wet = PTW_EWW(vop2->wgb);
				goto eww_cwtcs;
			}
			vop2->wgb = NUWW;
		}
	}

	wockchip_dwm_dma_init_device(vop2->dwm, vop2->dev);

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;

eww_cwtcs:
	vop2_destwoy_cwtcs(vop2);

	wetuwn wet;
}

static void vop2_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct vop2 *vop2 = dev_get_dwvdata(dev);

	pm_wuntime_disabwe(dev);

	if (vop2->wgb)
		wockchip_wgb_fini(vop2->wgb);

	vop2_destwoy_cwtcs(vop2);
}

const stwuct component_ops vop2_component_ops = {
	.bind = vop2_bind,
	.unbind = vop2_unbind,
};
EXPOWT_SYMBOW_GPW(vop2_component_ops);
