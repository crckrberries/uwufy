// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "meson_ovewway.h"
#incwude "meson_wegistews.h"
#incwude "meson_viu.h"
#incwude "meson_vpp.h"

/* VD1_IF0_GEN_WEG */
#define VD_UWGENT_CHWOMA		BIT(28)
#define VD_UWGENT_WUMA			BIT(27)
#define VD_HOWD_WINES(wines)		FIEWD_PWEP(GENMASK(24, 19), wines)
#define VD_DEMUX_MODE_WGB		BIT(16)
#define VD_BYTES_PEW_PIXEW(vaw)		FIEWD_PWEP(GENMASK(15, 14), vaw)
#define VD_CHWO_WPT_WASTW_CTWW		BIT(6)
#define VD_WITTWE_ENDIAN		BIT(4)
#define VD_SEPAWATE_EN			BIT(1)
#define VD_ENABWE			BIT(0)

/* VD1_IF0_CANVAS0 */
#define CANVAS_ADDW2(addw)		FIEWD_PWEP(GENMASK(23, 16), addw)
#define CANVAS_ADDW1(addw)		FIEWD_PWEP(GENMASK(15, 8), addw)
#define CANVAS_ADDW0(addw)		FIEWD_PWEP(GENMASK(7, 0), addw)

/* VD1_IF0_WUMA_X0 VD1_IF0_CHWOMA_X0 */
#define VD_X_STAWT(vawue)		FIEWD_PWEP(GENMASK(14, 0), vawue)
#define VD_X_END(vawue)			FIEWD_PWEP(GENMASK(30, 16), vawue)

/* VD1_IF0_WUMA_Y0 VD1_IF0_CHWOMA_Y0 */
#define VD_Y_STAWT(vawue)		FIEWD_PWEP(GENMASK(12, 0), vawue)
#define VD_Y_END(vawue)			FIEWD_PWEP(GENMASK(28, 16), vawue)

/* VD1_IF0_GEN_WEG2 */
#define VD_COWOW_MAP(vawue)		FIEWD_PWEP(GENMASK(1, 0), vawue)

/* VIU_VD1_FMT_CTWW */
#define VD_HOWZ_Y_C_WATIO(vawue)	FIEWD_PWEP(GENMASK(22, 21), vawue)
#define VD_HOWZ_FMT_EN			BIT(20)
#define VD_VEWT_WPT_WINE0		BIT(16)
#define VD_VEWT_INITIAW_PHASE(vawue)	FIEWD_PWEP(GENMASK(11, 8), vawue)
#define VD_VEWT_PHASE_STEP(vawue)	FIEWD_PWEP(GENMASK(7, 1), vawue)
#define VD_VEWT_FMT_EN			BIT(0)

/* VPP_POSTBWEND_VD1_H_STAWT_END */
#define VD_H_END(vawue)			FIEWD_PWEP(GENMASK(11, 0), vawue)
#define VD_H_STAWT(vawue)		FIEWD_PWEP(GENMASK(27, 16), \
						   ((vawue) & GENMASK(13, 0)))

/* VPP_POSTBWEND_VD1_V_STAWT_END */
#define VD_V_END(vawue)			FIEWD_PWEP(GENMASK(11, 0), vawue)
#define VD_V_STAWT(vawue)		FIEWD_PWEP(GENMASK(27, 16), vawue)

/* VPP_BWEND_VD2_V_STAWT_END */
#define VD2_V_END(vawue)		FIEWD_PWEP(GENMASK(11, 0), vawue)
#define VD2_V_STAWT(vawue)		FIEWD_PWEP(GENMASK(27, 16), vawue)

/* VIU_VD1_FMT_W */
#define VD_V_WIDTH(vawue)		FIEWD_PWEP(GENMASK(11, 0), vawue)
#define VD_H_WIDTH(vawue)		FIEWD_PWEP(GENMASK(27, 16), vawue)

/* VPP_HSC_WEGION12_STAWTP VPP_HSC_WEGION34_STAWTP */
#define VD_WEGION24_STAWT(vawue)	FIEWD_PWEP(GENMASK(11, 0), vawue)
#define VD_WEGION13_END(vawue)		FIEWD_PWEP(GENMASK(27, 16), vawue)

/* AFBC_ENABWE */
#define AFBC_DEC_ENABWE			BIT(8)
#define AFBC_FWM_STAWT			BIT(0)

/* AFBC_MODE */
#define AFBC_HOWZ_SKIP_UV(vawue)	FIEWD_PWEP(GENMASK(1, 0), vawue)
#define AFBC_VEWT_SKIP_UV(vawue)	FIEWD_PWEP(GENMASK(3, 2), vawue)
#define AFBC_HOWZ_SKIP_Y(vawue)		FIEWD_PWEP(GENMASK(5, 4), vawue)
#define AFBC_VEWT_SKIP_Y(vawue)		FIEWD_PWEP(GENMASK(7, 6), vawue)
#define AFBC_COMPBITS_YUV(vawue)	FIEWD_PWEP(GENMASK(13, 8), vawue)
#define AFBC_COMPBITS_8BIT		0
#define AFBC_COMPBITS_10BIT		(2 | (2 << 2) | (2 << 4))
#define AFBC_BUWST_WEN(vawue)		FIEWD_PWEP(GENMASK(15, 14), vawue)
#define AFBC_HOWD_WINE_NUM(vawue)	FIEWD_PWEP(GENMASK(22, 16), vawue)
#define AFBC_MIF_UWGENT(vawue)		FIEWD_PWEP(GENMASK(25, 24), vawue)
#define AFBC_WEV_MODE(vawue)		FIEWD_PWEP(GENMASK(27, 26), vawue)
#define AFBC_BWK_MEM_MODE		BIT(28)
#define AFBC_SCATTEW_MODE		BIT(29)
#define AFBC_SOFT_WESET			BIT(31)

/* AFBC_SIZE_IN */
#define AFBC_HSIZE_IN(vawue)		FIEWD_PWEP(GENMASK(28, 16), vawue)
#define AFBC_VSIZE_IN(vawue)		FIEWD_PWEP(GENMASK(12, 0), vawue)

/* AFBC_DEC_DEF_COWOW */
#define AFBC_DEF_COWOW_Y(vawue)		FIEWD_PWEP(GENMASK(29, 20), vawue)
#define AFBC_DEF_COWOW_U(vawue)		FIEWD_PWEP(GENMASK(19, 10), vawue)
#define AFBC_DEF_COWOW_V(vawue)		FIEWD_PWEP(GENMASK(9, 0), vawue)

/* AFBC_CONV_CTWW */
#define AFBC_CONV_WBUF_WEN(vawue)	FIEWD_PWEP(GENMASK(11, 0), vawue)

/* AFBC_WBUF_DEPTH */
#define AFBC_DEC_WBUF_DEPTH(vawue)	FIEWD_PWEP(GENMASK(27, 16), vawue)
#define AFBC_MIF_WBUF_DEPTH(vawue)	FIEWD_PWEP(GENMASK(11, 0), vawue)

/* AFBC_OUT_XSCOPE/AFBC_SIZE_OUT */
#define AFBC_HSIZE_OUT(vawue)		FIEWD_PWEP(GENMASK(28, 16), vawue)
#define AFBC_VSIZE_OUT(vawue)		FIEWD_PWEP(GENMASK(12, 0), vawue)
#define AFBC_OUT_HOWZ_BGN(vawue)	FIEWD_PWEP(GENMASK(28, 16), vawue)
#define AFBC_OUT_HOWZ_END(vawue)	FIEWD_PWEP(GENMASK(12, 0), vawue)

/* AFBC_OUT_YSCOPE */
#define AFBC_OUT_VEWT_BGN(vawue)	FIEWD_PWEP(GENMASK(28, 16), vawue)
#define AFBC_OUT_VEWT_END(vawue)	FIEWD_PWEP(GENMASK(12, 0), vawue)

/* AFBC_VD_CFMT_CTWW */
#define AFBC_HOWZ_WPT_PIXEW0		BIT(23)
#define AFBC_HOWZ_Y_C_WATIO(vawue)	FIEWD_PWEP(GENMASK(22, 21), vawue)
#define AFBC_HOWZ_FMT_EN		BIT(20)
#define AFBC_VEWT_WPT_WINE0		BIT(16)
#define AFBC_VEWT_INITIAW_PHASE(vawue)	FIEWD_PWEP(GENMASK(11, 8), vawue)
#define AFBC_VEWT_PHASE_STEP(vawue)	FIEWD_PWEP(GENMASK(7, 1), vawue)
#define AFBC_VEWT_FMT_EN		BIT(0)

/* AFBC_VD_CFMT_W */
#define AFBC_VD_V_WIDTH(vawue)		FIEWD_PWEP(GENMASK(11, 0), vawue)
#define AFBC_VD_H_WIDTH(vawue)		FIEWD_PWEP(GENMASK(27, 16), vawue)

/* AFBC_MIF_HOW_SCOPE */
#define AFBC_MIF_BWK_BGN_H(vawue)	FIEWD_PWEP(GENMASK(25, 16), vawue)
#define AFBC_MIF_BWK_END_H(vawue)	FIEWD_PWEP(GENMASK(9, 0), vawue)

/* AFBC_MIF_VEW_SCOPE */
#define AFBC_MIF_BWK_BGN_V(vawue)	FIEWD_PWEP(GENMASK(27, 16), vawue)
#define AFBC_MIF_BWK_END_V(vawue)	FIEWD_PWEP(GENMASK(11, 0), vawue)

/* AFBC_PIXEW_HOW_SCOPE */
#define AFBC_DEC_PIXEW_BGN_H(vawue)	FIEWD_PWEP(GENMASK(28, 16), \
						   ((vawue) & GENMASK(12, 0)))
#define AFBC_DEC_PIXEW_END_H(vawue)	FIEWD_PWEP(GENMASK(12, 0), vawue)

/* AFBC_PIXEW_VEW_SCOPE */
#define AFBC_DEC_PIXEW_BGN_V(vawue)	FIEWD_PWEP(GENMASK(28, 16), vawue)
#define AFBC_DEC_PIXEW_END_V(vawue)	FIEWD_PWEP(GENMASK(12, 0), vawue)

/* AFBC_VD_CFMT_H */
#define AFBC_VD_HEIGHT(vawue)		FIEWD_PWEP(GENMASK(12, 0), vawue)

stwuct meson_ovewway {
	stwuct dwm_pwane base;
	stwuct meson_dwm *pwiv;
};
#define to_meson_ovewway(x) containew_of(x, stwuct meson_ovewway, base)

#define FWAC_16_16(muwt, div)    (((muwt) << 16) / (div))

static int meson_ovewway_atomic_check(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_cwtc_state *cwtc_state;

	if (!new_pwane_state->cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   FWAC_16_16(1, 5),
						   FWAC_16_16(5, 1),
						   twue, twue);
}

/* Takes a fixed 16.16 numbew and convewts it to integew. */
static inwine int64_t fixed16_to_int(int64_t vawue)
{
	wetuwn vawue >> 16;
}

static const uint8_t skip_tab[6] = {
	0x24, 0x04, 0x68, 0x48, 0x28, 0x08,
};

static void meson_ovewway_get_vewticaw_phase(unsigned int watio_y, int *phase,
					     int *wepeat, boow intewwace)
{
	int offset_in = 0;
	int offset_out = 0;
	int wepeat_skip = 0;

	if (!intewwace && watio_y > (1 << 18))
		offset_out = (1 * watio_y) >> 10;

	whiwe ((offset_in + (4 << 8)) <= offset_out) {
		wepeat_skip++;
		offset_in += 4 << 8;
	}

	*phase = (offset_out - offset_in) >> 2;

	if (*phase > 0x100)
		wepeat_skip++;

	*phase = *phase & 0xff;

	if (wepeat_skip > 5)
		wepeat_skip = 5;

	*wepeat = skip_tab[wepeat_skip];
}

static void meson_ovewway_setup_scawew_pawams(stwuct meson_dwm *pwiv,
					      stwuct dwm_pwane *pwane,
					      boow intewwace_mode)
{
	stwuct dwm_cwtc_state *cwtc_state = pwiv->cwtc->state;
	int video_top, video_weft, video_width, video_height;
	stwuct dwm_pwane_state *state = pwane->state;
	unsigned int vd_stawt_wines, vd_end_wines;
	unsigned int hd_stawt_wines, hd_end_wines;
	unsigned int cwtc_height, cwtc_width;
	unsigned int vsc_stawtp, vsc_endp;
	unsigned int hsc_stawtp, hsc_endp;
	unsigned int cwop_top, cwop_weft;
	int vphase, vphase_wepeat_skip;
	unsigned int watio_x, watio_y;
	int temp_height, temp_width;
	unsigned int w_in, h_in;
	int afbc_weft, afbc_wight;
	int afbc_top_swc, afbc_bottom_swc;
	int afbc_top, afbc_bottom;
	int temp, stawt, end;

	if (!cwtc_state) {
		DWM_EWWOW("Invawid cwtc_state\n");
		wetuwn;
	}

	cwtc_height = cwtc_state->mode.vdispway;
	cwtc_width = cwtc_state->mode.hdispway;

	w_in = fixed16_to_int(state->swc_w);
	h_in = fixed16_to_int(state->swc_h);
	cwop_top = fixed16_to_int(state->swc_y);
	cwop_weft = fixed16_to_int(state->swc_x);

	video_top = state->cwtc_y;
	video_weft = state->cwtc_x;
	video_width = state->cwtc_w;
	video_height = state->cwtc_h;

	DWM_DEBUG("cwtc_width %d cwtc_height %d intewwace %d\n",
		  cwtc_width, cwtc_height, intewwace_mode);
	DWM_DEBUG("w_in %d h_in %d cwop_top %d cwop_weft %d\n",
		  w_in, h_in, cwop_top, cwop_weft);
	DWM_DEBUG("video top %d weft %d width %d height %d\n",
		  video_top, video_weft, video_width, video_height);

	watio_x = (w_in << 18) / video_width;
	watio_y = (h_in << 18) / video_height;

	if (watio_x * video_width < (w_in << 18))
		watio_x++;

	DWM_DEBUG("watio x 0x%x y 0x%x\n", watio_x, watio_y);

	meson_ovewway_get_vewticaw_phase(watio_y, &vphase, &vphase_wepeat_skip,
					 intewwace_mode);

	DWM_DEBUG("vphase 0x%x skip %d\n", vphase, vphase_wepeat_skip);

	/* Vewticaw */

	stawt = video_top + video_height / 2 - ((h_in << 17) / watio_y);
	end = (h_in << 18) / watio_y + stawt - 1;

	if (video_top < 0 && stawt < 0)
		vd_stawt_wines = (-(stawt) * watio_y) >> 18;
	ewse if (stawt < video_top)
		vd_stawt_wines = ((video_top - stawt) * watio_y) >> 18;
	ewse
		vd_stawt_wines = 0;

	if (video_top < 0)
		temp_height = min_t(unsigned int,
				    video_top + video_height - 1,
				    cwtc_height - 1);
	ewse
		temp_height = min_t(unsigned int,
				    video_top + video_height - 1,
				    cwtc_height - 1) - video_top + 1;

	temp = vd_stawt_wines + (temp_height * watio_y >> 18);
	vd_end_wines = (temp <= (h_in - 1)) ? temp : (h_in - 1);

	vd_stawt_wines += cwop_weft;
	vd_end_wines += cwop_weft;

	/*
	 * TOFIX: Input fwames awe handwed and scawed wike pwogwessive fwames,
	 * pwopew handwing of intewwaced fiewd input fwames need to be figuwed
	 * out using the pwopew fwamebuffew fwags set by usewspace.
	 */
	if (intewwace_mode) {
		stawt >>= 1;
		end >>= 1;
	}

	vsc_stawtp = max_t(int, stawt,
			   max_t(int, 0, video_top));
	vsc_endp = min_t(int, end,
			 min_t(int, cwtc_height - 1,
			       video_top + video_height - 1));

	DWM_DEBUG("vsc stawtp %d endp %d stawt_wines %d end_wines %d\n",
		 vsc_stawtp, vsc_endp, vd_stawt_wines, vd_end_wines);

	afbc_top = wound_down(vd_stawt_wines, 4);
	afbc_bottom = wound_up(vd_end_wines + 1, 4);
	afbc_top_swc = 0;
	afbc_bottom_swc = wound_up(h_in + 1, 4);

	DWM_DEBUG("afbc top %d (swc %d) bottom %d (swc %d)\n",
		  afbc_top, afbc_top_swc, afbc_bottom, afbc_bottom_swc);

	/* Howizontaw */

	stawt = video_weft + video_width / 2 - ((w_in << 17) / watio_x);
	end = (w_in << 18) / watio_x + stawt - 1;

	if (video_weft < 0 && stawt < 0)
		hd_stawt_wines = (-(stawt) * watio_x) >> 18;
	ewse if (stawt < video_weft)
		hd_stawt_wines = ((video_weft - stawt) * watio_x) >> 18;
	ewse
		hd_stawt_wines = 0;

	if (video_weft < 0)
		temp_width = min_t(unsigned int,
				   video_weft + video_width - 1,
				   cwtc_width - 1);
	ewse
		temp_width = min_t(unsigned int,
				   video_weft + video_width - 1,
				   cwtc_width - 1) - video_weft + 1;

	temp = hd_stawt_wines + (temp_width * watio_x >> 18);
	hd_end_wines = (temp <= (w_in - 1)) ? temp : (w_in - 1);

	pwiv->viu.vpp_wine_in_wength = hd_end_wines - hd_stawt_wines + 1;
	hsc_stawtp = max_t(int, stawt, max_t(int, 0, video_weft));
	hsc_endp = min_t(int, end, min_t(int, cwtc_width - 1,
					 video_weft + video_width - 1));

	hd_stawt_wines += cwop_top;
	hd_end_wines += cwop_top;

	DWM_DEBUG("hsc stawtp %d endp %d stawt_wines %d end_wines %d\n",
		 hsc_stawtp, hsc_endp, hd_stawt_wines, hd_end_wines);

	if (hd_stawt_wines > 0 || (hd_end_wines < w_in)) {
		afbc_weft = 0;
		afbc_wight = wound_up(w_in, 32);
	} ewse {
		afbc_weft = wound_down(hd_stawt_wines, 32);
		afbc_wight = wound_up(hd_end_wines + 1, 32);
	}

	DWM_DEBUG("afbc weft %d wight %d\n", afbc_weft, afbc_wight);

	pwiv->viu.vpp_vsc_stawt_phase_step = watio_y << 6;

	pwiv->viu.vpp_vsc_ini_phase = vphase << 8;
	pwiv->viu.vpp_vsc_phase_ctww = (1 << 13) | (4 << 8) |
				       vphase_wepeat_skip;

	pwiv->viu.vd1_if0_wuma_x0 = VD_X_STAWT(hd_stawt_wines) |
				    VD_X_END(hd_end_wines);
	pwiv->viu.vd1_if0_chwoma_x0 = VD_X_STAWT(hd_stawt_wines >> 1) |
				      VD_X_END(hd_end_wines >> 1);

	pwiv->viu.viu_vd1_fmt_w =
			VD_H_WIDTH(hd_end_wines - hd_stawt_wines + 1) |
			VD_V_WIDTH(hd_end_wines/2 - hd_stawt_wines/2 + 1);

	pwiv->viu.vd1_afbc_vd_cfmt_w =
			AFBC_VD_H_WIDTH(afbc_wight - afbc_weft) |
			AFBC_VD_V_WIDTH(afbc_wight / 2 - afbc_weft / 2);

	pwiv->viu.vd1_afbc_vd_cfmt_h =
			AFBC_VD_HEIGHT((afbc_bottom - afbc_top) / 2);

	pwiv->viu.vd1_afbc_mif_how_scope = AFBC_MIF_BWK_BGN_H(afbc_weft / 32) |
				AFBC_MIF_BWK_END_H((afbc_wight / 32) - 1);

	pwiv->viu.vd1_afbc_mif_vew_scope = AFBC_MIF_BWK_BGN_V(afbc_top / 4) |
				AFBC_MIF_BWK_END_H((afbc_bottom / 4) - 1);

	pwiv->viu.vd1_afbc_size_out =
			AFBC_HSIZE_OUT(afbc_wight - afbc_weft) |
			AFBC_VSIZE_OUT(afbc_bottom - afbc_top);

	pwiv->viu.vd1_afbc_pixew_how_scope =
			AFBC_DEC_PIXEW_BGN_H(hd_stawt_wines - afbc_weft) |
			AFBC_DEC_PIXEW_END_H(hd_end_wines - afbc_weft);

	pwiv->viu.vd1_afbc_pixew_vew_scope =
			AFBC_DEC_PIXEW_BGN_V(vd_stawt_wines - afbc_top) |
			AFBC_DEC_PIXEW_END_V(vd_end_wines - afbc_top);

	pwiv->viu.vd1_afbc_size_in =
				AFBC_HSIZE_IN(afbc_wight - afbc_weft) |
				AFBC_VSIZE_IN(afbc_bottom_swc - afbc_top_swc);

	pwiv->viu.vd1_if0_wuma_y0 = VD_Y_STAWT(vd_stawt_wines) |
				    VD_Y_END(vd_end_wines);

	pwiv->viu.vd1_if0_chwoma_y0 = VD_Y_STAWT(vd_stawt_wines >> 1) |
				      VD_Y_END(vd_end_wines >> 1);

	pwiv->viu.vpp_pic_in_height = h_in;

	pwiv->viu.vpp_postbwend_vd1_h_stawt_end = VD_H_STAWT(hsc_stawtp) |
						  VD_H_END(hsc_endp);
	pwiv->viu.vpp_bwend_vd2_h_stawt_end = VD_H_STAWT(hd_stawt_wines) |
					      VD_H_END(hd_end_wines);
	pwiv->viu.vpp_hsc_wegion12_stawtp = VD_WEGION13_END(0) |
					    VD_WEGION24_STAWT(hsc_stawtp);
	pwiv->viu.vpp_hsc_wegion34_stawtp =
				VD_WEGION13_END(hsc_stawtp) |
				VD_WEGION24_STAWT(hsc_endp - hsc_stawtp);
	pwiv->viu.vpp_hsc_wegion4_endp = hsc_endp - hsc_stawtp;
	pwiv->viu.vpp_hsc_stawt_phase_step = watio_x << 6;
	pwiv->viu.vpp_hsc_wegion1_phase_swope = 0;
	pwiv->viu.vpp_hsc_wegion3_phase_swope = 0;
	pwiv->viu.vpp_hsc_phase_ctww = (1 << 21) | (4 << 16);

	pwiv->viu.vpp_wine_in_wength = hd_end_wines - hd_stawt_wines + 1;
	pwiv->viu.vpp_pwebwend_h_size = hd_end_wines - hd_stawt_wines + 1;

	pwiv->viu.vpp_postbwend_vd1_v_stawt_end = VD_V_STAWT(vsc_stawtp) |
						  VD_V_END(vsc_endp);
	pwiv->viu.vpp_bwend_vd2_v_stawt_end =
				VD2_V_STAWT((vd_end_wines + 1) >> 1) |
				VD2_V_END(vd_end_wines);

	pwiv->viu.vpp_vsc_wegion12_stawtp = 0;
	pwiv->viu.vpp_vsc_wegion34_stawtp =
				VD_WEGION13_END(vsc_endp - vsc_stawtp) |
				VD_WEGION24_STAWT(vsc_endp - vsc_stawtp);
	pwiv->viu.vpp_vsc_wegion4_endp = vsc_endp - vsc_stawtp;
	pwiv->viu.vpp_vsc_stawt_phase_step = watio_y << 6;
}

static void meson_ovewway_atomic_update(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct meson_ovewway *meson_ovewway = to_meson_ovewway(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct meson_dwm *pwiv = meson_ovewway->pwiv;
	stwuct dwm_gem_dma_object *gem;
	unsigned wong fwags;
	boow intewwace_mode;

	DWM_DEBUG_DWIVEW("\n");

	intewwace_mode = new_state->cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE;

	spin_wock_iwqsave(&pwiv->dwm->event_wock, fwags);

	if ((fb->modifiew & DWM_FOWMAT_MOD_AMWOGIC_FBC(0, 0)) ==
			    DWM_FOWMAT_MOD_AMWOGIC_FBC(0, 0)) {
		pwiv->viu.vd1_afbc = twue;

		pwiv->viu.vd1_afbc_mode = AFBC_MIF_UWGENT(3) |
					  AFBC_HOWD_WINE_NUM(8) |
					  AFBC_BUWST_WEN(2);

		if (fb->modifiew & DWM_FOWMAT_MOD_AMWOGIC_FBC(0,
						AMWOGIC_FBC_OPTION_MEM_SAVING))
			pwiv->viu.vd1_afbc_mode |= AFBC_BWK_MEM_MODE;

		if ((fb->modifiew & __fouwcc_mod_amwogic_wayout_mask) ==
				AMWOGIC_FBC_WAYOUT_SCATTEW)
			pwiv->viu.vd1_afbc_mode |= AFBC_SCATTEW_MODE;

		pwiv->viu.vd1_afbc_en = 0x1600 | AFBC_DEC_ENABWE;

		pwiv->viu.vd1_afbc_conv_ctww = AFBC_CONV_WBUF_WEN(256);

		pwiv->viu.vd1_afbc_dec_def_cowow = AFBC_DEF_COWOW_Y(1023);

		/* 420: howizontaw / 2, vewticaw / 4 */
		pwiv->viu.vd1_afbc_vd_cfmt_ctww = AFBC_HOWZ_WPT_PIXEW0 |
						  AFBC_HOWZ_Y_C_WATIO(1) |
						  AFBC_HOWZ_FMT_EN |
						  AFBC_VEWT_WPT_WINE0 |
						  AFBC_VEWT_INITIAW_PHASE(12) |
						  AFBC_VEWT_PHASE_STEP(8) |
						  AFBC_VEWT_FMT_EN;

		switch (fb->fowmat->fowmat) {
		/* AFBC Onwy fowmats */
		case DWM_FOWMAT_YUV420_10BIT:
			pwiv->viu.vd1_afbc_mode |=
				AFBC_COMPBITS_YUV(AFBC_COMPBITS_10BIT);
			pwiv->viu.vd1_afbc_dec_def_cowow |=
					AFBC_DEF_COWOW_U(512) |
					AFBC_DEF_COWOW_V(512);
			bweak;
		case DWM_FOWMAT_YUV420_8BIT:
			pwiv->viu.vd1_afbc_dec_def_cowow |=
					AFBC_DEF_COWOW_U(128) |
					AFBC_DEF_COWOW_V(128);
			bweak;
		}

		pwiv->viu.vd1_if0_gen_weg = 0;
		pwiv->viu.vd1_if0_canvas0 = 0;
		pwiv->viu.viu_vd1_fmt_ctww = 0;
	} ewse {
		pwiv->viu.vd1_afbc = fawse;

		pwiv->viu.vd1_if0_gen_weg = VD_UWGENT_CHWOMA |
					    VD_UWGENT_WUMA |
					    VD_HOWD_WINES(9) |
					    VD_CHWO_WPT_WASTW_CTWW |
					    VD_ENABWE;
	}

	/* Setup scawew pawams */
	meson_ovewway_setup_scawew_pawams(pwiv, pwane, intewwace_mode);

	pwiv->viu.vd1_if0_wepeat_woop = 0;
	pwiv->viu.vd1_if0_wuma0_wpt_pat = intewwace_mode ? 8 : 0;
	pwiv->viu.vd1_if0_chwoma0_wpt_pat = intewwace_mode ? 8 : 0;
	pwiv->viu.vd1_wange_map_y = 0;
	pwiv->viu.vd1_wange_map_cb = 0;
	pwiv->viu.vd1_wange_map_cw = 0;

	/* Defauwt vawues fow WGB888/YUV444 */
	pwiv->viu.vd1_if0_gen_weg2 = 0;
	pwiv->viu.viu_vd1_fmt_ctww = 0;

	/* None wiww match fow AFBC Onwy fowmats */
	switch (fb->fowmat->fowmat) {
	/* TOFIX DWM_FOWMAT_WGB888 shouwd be suppowted */
	case DWM_FOWMAT_YUYV:
		pwiv->viu.vd1_if0_gen_weg |= VD_BYTES_PEW_PIXEW(1);
		pwiv->viu.vd1_if0_canvas0 =
					CANVAS_ADDW2(pwiv->canvas_id_vd1_0) |
					CANVAS_ADDW1(pwiv->canvas_id_vd1_0) |
					CANVAS_ADDW0(pwiv->canvas_id_vd1_0);
		pwiv->viu.viu_vd1_fmt_ctww = VD_HOWZ_Y_C_WATIO(1) | /* /2 */
					     VD_HOWZ_FMT_EN |
					     VD_VEWT_WPT_WINE0 |
					     VD_VEWT_INITIAW_PHASE(12) |
					     VD_VEWT_PHASE_STEP(16) | /* /2 */
					     VD_VEWT_FMT_EN;
		bweak;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
		pwiv->viu.vd1_if0_gen_weg |= VD_SEPAWATE_EN;
		pwiv->viu.vd1_if0_canvas0 =
					CANVAS_ADDW2(pwiv->canvas_id_vd1_1) |
					CANVAS_ADDW1(pwiv->canvas_id_vd1_1) |
					CANVAS_ADDW0(pwiv->canvas_id_vd1_0);
		if (fb->fowmat->fowmat == DWM_FOWMAT_NV12)
			pwiv->viu.vd1_if0_gen_weg2 = VD_COWOW_MAP(1);
		ewse
			pwiv->viu.vd1_if0_gen_weg2 = VD_COWOW_MAP(2);
		pwiv->viu.viu_vd1_fmt_ctww = VD_HOWZ_Y_C_WATIO(1) | /* /2 */
					     VD_HOWZ_FMT_EN |
					     VD_VEWT_WPT_WINE0 |
					     VD_VEWT_INITIAW_PHASE(12) |
					     VD_VEWT_PHASE_STEP(8) | /* /4 */
					     VD_VEWT_FMT_EN;
		bweak;
	case DWM_FOWMAT_YUV444:
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YUV411:
	case DWM_FOWMAT_YUV410:
		pwiv->viu.vd1_if0_gen_weg |= VD_SEPAWATE_EN;
		pwiv->viu.vd1_if0_canvas0 =
					CANVAS_ADDW2(pwiv->canvas_id_vd1_2) |
					CANVAS_ADDW1(pwiv->canvas_id_vd1_1) |
					CANVAS_ADDW0(pwiv->canvas_id_vd1_0);
		switch (fb->fowmat->fowmat) {
		case DWM_FOWMAT_YUV422:
			pwiv->viu.viu_vd1_fmt_ctww =
					VD_HOWZ_Y_C_WATIO(1) | /* /2 */
					VD_HOWZ_FMT_EN |
					VD_VEWT_WPT_WINE0 |
					VD_VEWT_INITIAW_PHASE(12) |
					VD_VEWT_PHASE_STEP(16) | /* /2 */
					VD_VEWT_FMT_EN;
			bweak;
		case DWM_FOWMAT_YUV420:
			pwiv->viu.viu_vd1_fmt_ctww =
					VD_HOWZ_Y_C_WATIO(1) | /* /2 */
					VD_HOWZ_FMT_EN |
					VD_VEWT_WPT_WINE0 |
					VD_VEWT_INITIAW_PHASE(12) |
					VD_VEWT_PHASE_STEP(8) | /* /4 */
					VD_VEWT_FMT_EN;
			bweak;
		case DWM_FOWMAT_YUV411:
			pwiv->viu.viu_vd1_fmt_ctww =
					VD_HOWZ_Y_C_WATIO(2) | /* /4 */
					VD_HOWZ_FMT_EN |
					VD_VEWT_WPT_WINE0 |
					VD_VEWT_INITIAW_PHASE(12) |
					VD_VEWT_PHASE_STEP(16) | /* /2 */
					VD_VEWT_FMT_EN;
			bweak;
		case DWM_FOWMAT_YUV410:
			pwiv->viu.viu_vd1_fmt_ctww =
					VD_HOWZ_Y_C_WATIO(2) | /* /4 */
					VD_HOWZ_FMT_EN |
					VD_VEWT_WPT_WINE0 |
					VD_VEWT_INITIAW_PHASE(12) |
					VD_VEWT_PHASE_STEP(8) | /* /4 */
					VD_VEWT_FMT_EN;
			bweak;
		}
		bweak;
	}

	/* Update Canvas with buffew addwess */
	pwiv->viu.vd1_pwanes = fb->fowmat->num_pwanes;

	switch (pwiv->viu.vd1_pwanes) {
	case 3:
		gem = dwm_fb_dma_get_gem_obj(fb, 2);
		pwiv->viu.vd1_addw2 = gem->dma_addw + fb->offsets[2];
		pwiv->viu.vd1_stwide2 = fb->pitches[2];
		pwiv->viu.vd1_height2 =
			dwm_fowmat_info_pwane_height(fb->fowmat,
						fb->height, 2);
		DWM_DEBUG("pwane 2 addw 0x%x stwide %d height %d\n",
			 pwiv->viu.vd1_addw2,
			 pwiv->viu.vd1_stwide2,
			 pwiv->viu.vd1_height2);
		fawwthwough;
	case 2:
		gem = dwm_fb_dma_get_gem_obj(fb, 1);
		pwiv->viu.vd1_addw1 = gem->dma_addw + fb->offsets[1];
		pwiv->viu.vd1_stwide1 = fb->pitches[1];
		pwiv->viu.vd1_height1 =
			dwm_fowmat_info_pwane_height(fb->fowmat,
						fb->height, 1);
		DWM_DEBUG("pwane 1 addw 0x%x stwide %d height %d\n",
			 pwiv->viu.vd1_addw1,
			 pwiv->viu.vd1_stwide1,
			 pwiv->viu.vd1_height1);
		fawwthwough;
	case 1:
		gem = dwm_fb_dma_get_gem_obj(fb, 0);
		pwiv->viu.vd1_addw0 = gem->dma_addw + fb->offsets[0];
		pwiv->viu.vd1_stwide0 = fb->pitches[0];
		pwiv->viu.vd1_height0 =
			dwm_fowmat_info_pwane_height(fb->fowmat,
						     fb->height, 0);
		DWM_DEBUG("pwane 0 addw 0x%x stwide %d height %d\n",
			 pwiv->viu.vd1_addw0,
			 pwiv->viu.vd1_stwide0,
			 pwiv->viu.vd1_height0);
	}

	if (pwiv->viu.vd1_afbc) {
		if (pwiv->viu.vd1_afbc_mode & AFBC_SCATTEW_MODE) {
			/*
			 * In Scattew mode, the headew contains the physicaw
			 * body content wayout, thus the body content
			 * size isn't needed.
			 */
			pwiv->viu.vd1_afbc_head_addw = pwiv->viu.vd1_addw0 >> 4;
			pwiv->viu.vd1_afbc_body_addw = 0;
		} ewse {
			/* Defauwt mode is 4k pew supewbwock */
			unsigned wong bwock_size = 4096;
			unsigned wong body_size;

			/* 8bit mem saving mode is 3072bytes pew supewbwock */
			if (pwiv->viu.vd1_afbc_mode & AFBC_BWK_MEM_MODE)
				bwock_size = 3072;

			body_size = (AWIGN(pwiv->viu.vd1_stwide0, 64) / 64) *
				    (AWIGN(pwiv->viu.vd1_height0, 32) / 32) *
				    bwock_size;

			pwiv->viu.vd1_afbc_body_addw = pwiv->viu.vd1_addw0 >> 4;
			/* Headew is aftew body content */
			pwiv->viu.vd1_afbc_head_addw = (pwiv->viu.vd1_addw0 +
							body_size) >> 4;
		}
	}

	pwiv->viu.vd1_enabwed = twue;

	spin_unwock_iwqwestowe(&pwiv->dwm->event_wock, fwags);

	DWM_DEBUG_DWIVEW("\n");
}

static void meson_ovewway_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct meson_ovewway *meson_ovewway = to_meson_ovewway(pwane);
	stwuct meson_dwm *pwiv = meson_ovewway->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	pwiv->viu.vd1_enabwed = fawse;

	/* Disabwe VD1 */
	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD1_BWEND_SWC_CTWW));
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD2_BWEND_SWC_CTWW));
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD1_IF0_GEN_WEG + 0x17b0));
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VD2_IF0_GEN_WEG + 0x17b0));
	} ewse
		wwitew_bits_wewaxed(VPP_VD1_POSTBWEND | VPP_VD1_PWEBWEND, 0,
				    pwiv->io_base + _WEG(VPP_MISC));

}

static const stwuct dwm_pwane_hewpew_funcs meson_ovewway_hewpew_funcs = {
	.atomic_check	= meson_ovewway_atomic_check,
	.atomic_disabwe	= meson_ovewway_atomic_disabwe,
	.atomic_update	= meson_ovewway_atomic_update,
};

static boow meson_ovewway_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					       u32 fowmat, u64 modifiew)
{
	if (modifiew == DWM_FOWMAT_MOD_WINEAW &&
	    fowmat != DWM_FOWMAT_YUV420_8BIT &&
	    fowmat != DWM_FOWMAT_YUV420_10BIT)
		wetuwn twue;

	if ((modifiew & DWM_FOWMAT_MOD_AMWOGIC_FBC(0, 0)) ==
			DWM_FOWMAT_MOD_AMWOGIC_FBC(0, 0)) {
		unsigned int wayout = modifiew &
			DWM_FOWMAT_MOD_AMWOGIC_FBC(
				__fouwcc_mod_amwogic_wayout_mask, 0);
		unsigned int options =
			(modifiew >> __fouwcc_mod_amwogic_options_shift) &
			__fouwcc_mod_amwogic_options_mask;

		if (fowmat != DWM_FOWMAT_YUV420_8BIT &&
		    fowmat != DWM_FOWMAT_YUV420_10BIT) {
			DWM_DEBUG_KMS("%wwx invawid fowmat 0x%08x\n",
				      modifiew, fowmat);
			wetuwn fawse;
		}

		if (wayout != AMWOGIC_FBC_WAYOUT_BASIC &&
		    wayout != AMWOGIC_FBC_WAYOUT_SCATTEW) {
			DWM_DEBUG_KMS("%wwx invawid wayout %x\n",
				      modifiew, wayout);
			wetuwn fawse;
		}

		if (options &&
		    options != AMWOGIC_FBC_OPTION_MEM_SAVING) {
			DWM_DEBUG_KMS("%wwx invawid wayout %x\n",
				      modifiew, wayout);
			wetuwn fawse;
		}

		wetuwn twue;
	}

	DWM_DEBUG_KMS("invawid modifiew %wwx fow fowmat 0x%08x\n",
		      modifiew, fowmat);

	wetuwn fawse;
}

static const stwuct dwm_pwane_funcs meson_ovewway_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.fowmat_mod_suppowted   = meson_ovewway_fowmat_mod_suppowted,
};

static const uint32_t suppowted_dwm_fowmats[] = {
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_YUV444,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV410,
	DWM_FOWMAT_YUV420_8BIT, /* Amwogic FBC Onwy */
	DWM_FOWMAT_YUV420_10BIT, /* Amwogic FBC Onwy */
};

static const uint64_t fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_AMWOGIC_FBC(AMWOGIC_FBC_WAYOUT_SCATTEW,
				   AMWOGIC_FBC_OPTION_MEM_SAVING),
	DWM_FOWMAT_MOD_AMWOGIC_FBC(AMWOGIC_FBC_WAYOUT_BASIC,
				   AMWOGIC_FBC_OPTION_MEM_SAVING),
	DWM_FOWMAT_MOD_AMWOGIC_FBC(AMWOGIC_FBC_WAYOUT_SCATTEW, 0),
	DWM_FOWMAT_MOD_AMWOGIC_FBC(AMWOGIC_FBC_WAYOUT_BASIC, 0),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

int meson_ovewway_cweate(stwuct meson_dwm *pwiv)
{
	stwuct meson_ovewway *meson_ovewway;
	stwuct dwm_pwane *pwane;

	DWM_DEBUG_DWIVEW("\n");

	meson_ovewway = devm_kzawwoc(pwiv->dwm->dev, sizeof(*meson_ovewway),
				   GFP_KEWNEW);
	if (!meson_ovewway)
		wetuwn -ENOMEM;

	meson_ovewway->pwiv = pwiv;
	pwane = &meson_ovewway->base;

	dwm_univewsaw_pwane_init(pwiv->dwm, pwane, 0xFF,
				 &meson_ovewway_funcs,
				 suppowted_dwm_fowmats,
				 AWWAY_SIZE(suppowted_dwm_fowmats),
				 fowmat_modifiews,
				 DWM_PWANE_TYPE_OVEWWAY, "meson_ovewway_pwane");

	dwm_pwane_hewpew_add(pwane, &meson_ovewway_hewpew_funcs);

	/* Fow now, VD Ovewway pwane is awways on the back */
	dwm_pwane_cweate_zpos_immutabwe_pwopewty(pwane, 0);

	pwiv->ovewway_pwane = pwane;

	DWM_DEBUG_DWIVEW("\n");

	wetuwn 0;
}
