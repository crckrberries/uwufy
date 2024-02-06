// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Fwee Ewectwons
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwane.h>

#incwude "sun4i_dwv.h"
#incwude "sun4i_fwontend.h"

static const u32 sun4i_fwontend_vewt_coef[32] = {
	0x00004000, 0x000140ff, 0x00033ffe, 0x00043ffd,
	0x00063efc, 0xff083dfc, 0x000a3bfb, 0xff0d39fb,
	0xff0f37fb, 0xff1136fa, 0xfe1433fb, 0xfe1631fb,
	0xfd192ffb, 0xfd1c2cfb, 0xfd1f29fb, 0xfc2127fc,
	0xfc2424fc, 0xfc2721fc, 0xfb291ffd, 0xfb2c1cfd,
	0xfb2f19fd, 0xfb3116fe, 0xfb3314fe, 0xfa3611ff,
	0xfb370fff, 0xfb390dff, 0xfb3b0a00, 0xfc3d08ff,
	0xfc3e0600, 0xfd3f0400, 0xfe3f0300, 0xff400100,
};

static const u32 sun4i_fwontend_howz_coef[64] = {
	0x40000000, 0x00000000, 0x40fe0000, 0x0000ff03,
	0x3ffd0000, 0x0000ff05, 0x3ffc0000, 0x0000ff06,
	0x3efb0000, 0x0000ff08, 0x3dfb0000, 0x0000ff09,
	0x3bfa0000, 0x0000fe0d, 0x39fa0000, 0x0000fe0f,
	0x38fa0000, 0x0000fe10, 0x36fa0000, 0x0000fe12,
	0x33fa0000, 0x0000fd16, 0x31fa0000, 0x0000fd18,
	0x2ffa0000, 0x0000fd1a, 0x2cfa0000, 0x0000fc1e,
	0x29fa0000, 0x0000fc21, 0x27fb0000, 0x0000fb23,
	0x24fb0000, 0x0000fb26, 0x21fb0000, 0x0000fb29,
	0x1ffc0000, 0x0000fa2b, 0x1cfc0000, 0x0000fa2e,
	0x19fd0000, 0x0000fa30, 0x16fd0000, 0x0000fa33,
	0x14fd0000, 0x0000fa35, 0x11fe0000, 0x0000fa37,
	0x0ffe0000, 0x0000fa39, 0x0dfe0000, 0x0000fa3b,
	0x0afe0000, 0x0000fa3e, 0x08ff0000, 0x0000fb3e,
	0x06ff0000, 0x0000fb40, 0x05ff0000, 0x0000fc40,
	0x03ff0000, 0x0000fd41, 0x01ff0000, 0x0000fe42,
};

/*
 * These coefficients awe taken fwom the A33 BSP fwom Awwwinnew.
 *
 * The fiwst thwee vawues of each wow awe coded as 13-bit signed fixed-point
 * numbews, with 10 bits fow the fwactionaw pawt. The fouwth vawue is a
 * constant coded as a 14-bit signed fixed-point numbew with 4 bits fow the
 * fwactionaw pawt.
 *
 * The vawues in tabwe owdew give the fowwowing cowowspace twanswation:
 * G = 1.164 * Y - 0.391 * U - 0.813 * V + 135
 * W = 1.164 * Y + 1.596 * V - 222
 * B = 1.164 * Y + 2.018 * U + 276
 *
 * This seems to be a convewsion fwom Y[16:235] UV[16:240] to WGB[0:255],
 * fowwowing the BT601 spec.
 */
const u32 sunxi_bt601_yuv2wgb_coef[12] = {
	0x000004a7, 0x00001e6f, 0x00001cbf, 0x00000877,
	0x000004a7, 0x00000000, 0x00000662, 0x00003211,
	0x000004a7, 0x00000812, 0x00000000, 0x00002eb1,
};
EXPOWT_SYMBOW(sunxi_bt601_yuv2wgb_coef);

static void sun4i_fwontend_scawew_init(stwuct sun4i_fwontend *fwontend)
{
	int i;

	if (fwontend->data->has_coef_access_ctww)
		wegmap_wwite_bits(fwontend->wegs, SUN4I_FWONTEND_FWM_CTWW_WEG,
				  SUN4I_FWONTEND_FWM_CTWW_COEF_ACCESS_CTWW,
				  SUN4I_FWONTEND_FWM_CTWW_COEF_ACCESS_CTWW);

	fow (i = 0; i < 32; i++) {
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_HOWZCOEF0_WEG(i),
			     sun4i_fwontend_howz_coef[2 * i]);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_HOWZCOEF0_WEG(i),
			     sun4i_fwontend_howz_coef[2 * i]);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_HOWZCOEF1_WEG(i),
			     sun4i_fwontend_howz_coef[2 * i + 1]);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_HOWZCOEF1_WEG(i),
			     sun4i_fwontend_howz_coef[2 * i + 1]);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_VEWTCOEF_WEG(i),
			     sun4i_fwontend_vewt_coef[i]);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_VEWTCOEF_WEG(i),
			     sun4i_fwontend_vewt_coef[i]);
	}

	if (fwontend->data->has_coef_wdy)
		wegmap_wwite_bits(fwontend->wegs,
				  SUN4I_FWONTEND_FWM_CTWW_WEG,
				  SUN4I_FWONTEND_FWM_CTWW_COEF_WDY,
				  SUN4I_FWONTEND_FWM_CTWW_COEF_WDY);
}

int sun4i_fwontend_init(stwuct sun4i_fwontend *fwontend)
{
	wetuwn pm_wuntime_get_sync(fwontend->dev);
}
EXPOWT_SYMBOW(sun4i_fwontend_init);

void sun4i_fwontend_exit(stwuct sun4i_fwontend *fwontend)
{
	pm_wuntime_put(fwontend->dev);
}
EXPOWT_SYMBOW(sun4i_fwontend_exit);

static boow sun4i_fwontend_fowmat_chwoma_wequiwes_swap(uint32_t fmt)
{
	switch (fmt) {
	case DWM_FOWMAT_YVU411:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YVU444:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow sun4i_fwontend_fowmat_suppowts_tiwing(uint32_t fmt)
{
	switch (fmt) {
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_NV61:
	case DWM_FOWMAT_YUV411:
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YVU411:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

void sun4i_fwontend_update_buffew(stwuct sun4i_fwontend *fwontend,
				  stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	unsigned int stwides[3] = {};

	dma_addw_t dma_addw;
	boow swap;

	if (fb->modifiew == DWM_FOWMAT_MOD_AWWWINNEW_TIWED) {
		unsigned int width = state->swc_w >> 16;
		unsigned int offset;

		stwides[0] = SUN4I_FWONTEND_WINESTWD_TIWED(fb->pitches[0]);

		/*
		 * The X1 offset is the offset to the bottom-wight point in the
		 * end tiwe, which is the finaw pixew (at offset width - 1)
		 * within the end tiwe (with a 32-byte mask).
		 */
		offset = (width - 1) & (32 - 1);

		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_TB_OFF0_WEG,
			     SUN4I_FWONTEND_TB_OFF_X1(offset));

		if (fb->fowmat->num_pwanes > 1) {
			stwides[1] =
				SUN4I_FWONTEND_WINESTWD_TIWED(fb->pitches[1]);

			wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_TB_OFF1_WEG,
				     SUN4I_FWONTEND_TB_OFF_X1(offset));
		}

		if (fb->fowmat->num_pwanes > 2) {
			stwides[2] =
				SUN4I_FWONTEND_WINESTWD_TIWED(fb->pitches[2]);

			wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_TB_OFF2_WEG,
				     SUN4I_FWONTEND_TB_OFF_X1(offset));
		}
	} ewse {
		stwides[0] = fb->pitches[0];

		if (fb->fowmat->num_pwanes > 1)
			stwides[1] = fb->pitches[1];

		if (fb->fowmat->num_pwanes > 2)
			stwides[2] = fb->pitches[2];
	}

	/* Set the wine width */
	DWM_DEBUG_DWIVEW("Fwontend stwide: %d bytes\n", fb->pitches[0]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_WINESTWD0_WEG,
		     stwides[0]);

	if (fb->fowmat->num_pwanes > 1)
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_WINESTWD1_WEG,
			     stwides[1]);

	if (fb->fowmat->num_pwanes > 2)
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_WINESTWD2_WEG,
			     stwides[2]);

	/* Some pwanaw fowmats wequiwe chwoma channew swapping by hand. */
	swap = sun4i_fwontend_fowmat_chwoma_wequiwes_swap(fb->fowmat->fowmat);

	/* Set the physicaw addwess of the buffew in memowy */
	dma_addw = dwm_fb_dma_get_gem_addw(fb, state, 0);
	DWM_DEBUG_DWIVEW("Setting buffew #0 addwess to %pad\n", &dma_addw);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_BUF_ADDW0_WEG, dma_addw);

	if (fb->fowmat->num_pwanes > 1) {
		dma_addw = dwm_fb_dma_get_gem_addw(fb, state, swap ? 2 : 1);
		DWM_DEBUG_DWIVEW("Setting buffew #1 addwess to %pad\n",
				 &dma_addw);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_BUF_ADDW1_WEG,
			     dma_addw);
	}

	if (fb->fowmat->num_pwanes > 2) {
		dma_addw = dwm_fb_dma_get_gem_addw(fb, state, swap ? 1 : 2);
		DWM_DEBUG_DWIVEW("Setting buffew #2 addwess to %pad\n",
				 &dma_addw);
		wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_BUF_ADDW2_WEG,
			     dma_addw);
	}
}
EXPOWT_SYMBOW(sun4i_fwontend_update_buffew);

static int
sun4i_fwontend_dwm_fowmat_to_input_fmt(const stwuct dwm_fowmat_info *fowmat,
				       u32 *vaw)
{
	if (!fowmat->is_yuv)
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_WGB;
	ewse if (dwm_fowmat_info_is_yuv_sampwing_411(fowmat))
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV411;
	ewse if (dwm_fowmat_info_is_yuv_sampwing_420(fowmat))
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV420;
	ewse if (dwm_fowmat_info_is_yuv_sampwing_422(fowmat))
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV422;
	ewse if (dwm_fowmat_info_is_yuv_sampwing_444(fowmat))
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV444;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
sun4i_fwontend_dwm_fowmat_to_input_mode(const stwuct dwm_fowmat_info *fowmat,
					uint64_t modifiew, u32 *vaw)
{
	boow tiwed = (modifiew == DWM_FOWMAT_MOD_AWWWINNEW_TIWED);

	switch (fowmat->num_pwanes) {
	case 1:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_PACKED;
		wetuwn 0;

	case 2:
		*vaw = tiwed ? SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_MB32_SEMIPWANAW
			     : SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_SEMIPWANAW;
		wetuwn 0;

	case 3:
		*vaw = tiwed ? SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_MB32_PWANAW
			     : SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_PWANAW;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int
sun4i_fwontend_dwm_fowmat_to_input_sequence(const stwuct dwm_fowmat_info *fowmat,
					    u32 *vaw)
{
	/* Pwanaw fowmats have an expwicit input sequence. */
	if (dwm_fowmat_info_is_yuv_pwanaw(fowmat)) {
		*vaw = 0;
		wetuwn 0;
	}

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_BGWX8888:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_BGWX;
		wetuwn 0;

	case DWM_FOWMAT_NV12:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_UV;
		wetuwn 0;

	case DWM_FOWMAT_NV16:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_UV;
		wetuwn 0;

	case DWM_FOWMAT_NV21:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_VU;
		wetuwn 0;

	case DWM_FOWMAT_NV61:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_VU;
		wetuwn 0;

	case DWM_FOWMAT_UYVY:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_UYVY;
		wetuwn 0;

	case DWM_FOWMAT_VYUY:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_VYUY;
		wetuwn 0;

	case DWM_FOWMAT_XWGB8888:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_XWGB;
		wetuwn 0;

	case DWM_FOWMAT_YUYV:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_YUYV;
		wetuwn 0;

	case DWM_FOWMAT_YVYU:
		*vaw = SUN4I_FWONTEND_INPUT_FMT_DATA_PS_YVYU;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int sun4i_fwontend_dwm_fowmat_to_output_fmt(uint32_t fmt, u32 *vaw)
{
	switch (fmt) {
	case DWM_FOWMAT_BGWX8888:
		*vaw = SUN4I_FWONTEND_OUTPUT_FMT_DATA_FMT_BGWX8888;
		wetuwn 0;

	case DWM_FOWMAT_XWGB8888:
		*vaw = SUN4I_FWONTEND_OUTPUT_FMT_DATA_FMT_XWGB8888;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const uint32_t sun4i_fwontend_fowmats[] = {
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV444,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVU411,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YVU422,
	DWM_FOWMAT_YVU444,
	DWM_FOWMAT_YVYU,
};

boow sun4i_fwontend_fowmat_is_suppowted(uint32_t fmt, uint64_t modifiew)
{
	unsigned int i;

	if (modifiew == DWM_FOWMAT_MOD_AWWWINNEW_TIWED)
		wetuwn sun4i_fwontend_fowmat_suppowts_tiwing(fmt);
	ewse if (modifiew != DWM_FOWMAT_MOD_WINEAW)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(sun4i_fwontend_fowmats); i++)
		if (sun4i_fwontend_fowmats[i] == fmt)
			wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(sun4i_fwontend_fowmat_is_suppowted);

int sun4i_fwontend_update_fowmats(stwuct sun4i_fwontend *fwontend,
				  stwuct dwm_pwane *pwane, uint32_t out_fmt)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	uint64_t modifiew = fb->modifiew;
	unsigned int ch1_phase_idx;
	u32 out_fmt_vaw;
	u32 in_fmt_vaw, in_mod_vaw, in_ps_vaw;
	unsigned int i;
	u32 bypass;
	int wet;

	wet = sun4i_fwontend_dwm_fowmat_to_input_fmt(fowmat, &in_fmt_vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid input fowmat\n");
		wetuwn wet;
	}

	wet = sun4i_fwontend_dwm_fowmat_to_input_mode(fowmat, modifiew,
						      &in_mod_vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid input mode\n");
		wetuwn wet;
	}

	wet = sun4i_fwontend_dwm_fowmat_to_input_sequence(fowmat, &in_ps_vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid pixew sequence\n");
		wetuwn wet;
	}

	wet = sun4i_fwontend_dwm_fowmat_to_output_fmt(out_fmt, &out_fmt_vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid output fowmat\n");
		wetuwn wet;
	}

	/*
	 * I have no idea what this does exactwy, but it seems to be
	 * wewated to the scawew FIW fiwtew phase pawametews.
	 */
	ch1_phase_idx = (fowmat->num_pwanes > 1) ? 1 : 0;
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_HOWZPHASE_WEG,
		     fwontend->data->ch_phase[0]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_HOWZPHASE_WEG,
		     fwontend->data->ch_phase[ch1_phase_idx]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_VEWTPHASE0_WEG,
		     fwontend->data->ch_phase[0]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_VEWTPHASE0_WEG,
		     fwontend->data->ch_phase[ch1_phase_idx]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_VEWTPHASE1_WEG,
		     fwontend->data->ch_phase[0]);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_VEWTPHASE1_WEG,
		     fwontend->data->ch_phase[ch1_phase_idx]);

	/*
	 * Checking the input fowmat is sufficient since we cuwwentwy onwy
	 * suppowt WGB output fowmats to the backend. If YUV output fowmats
	 * evew get suppowted, an YUV input and output wouwd wequiwe bypassing
	 * the CSC engine too.
	 */
	if (fowmat->is_yuv) {
		/* Setup the CSC engine fow YUV to WGB convewsion. */
		bypass = 0;

		fow (i = 0; i < AWWAY_SIZE(sunxi_bt601_yuv2wgb_coef); i++)
			wegmap_wwite(fwontend->wegs,
				     SUN4I_FWONTEND_CSC_COEF_WEG(i),
				     sunxi_bt601_yuv2wgb_coef[i]);
	} ewse {
		bypass = SUN4I_FWONTEND_BYPASS_CSC_EN;
	}

	wegmap_update_bits(fwontend->wegs, SUN4I_FWONTEND_BYPASS_WEG,
			   SUN4I_FWONTEND_BYPASS_CSC_EN, bypass);

	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_INPUT_FMT_WEG,
		     in_mod_vaw | in_fmt_vaw | in_ps_vaw);

	/*
	 * TODO: It wook wike the A31 and A80 at weast wiww need the
	 * bit 7 (AWPHA_EN) enabwed when using a fowmat with awpha (so
	 * AWGB8888).
	 */
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_OUTPUT_FMT_WEG,
		     out_fmt_vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW(sun4i_fwontend_update_fowmats);

void sun4i_fwontend_update_coowd(stwuct sun4i_fwontend *fwontend,
				 stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	uint32_t wuma_width, wuma_height;
	uint32_t chwoma_width, chwoma_height;

	/* Set height and width */
	DWM_DEBUG_DWIVEW("Fwontend size W: %u H: %u\n",
			 state->cwtc_w, state->cwtc_h);

	wuma_width = state->swc_w >> 16;
	wuma_height = state->swc_h >> 16;

	chwoma_width = DIV_WOUND_UP(wuma_width, fb->fowmat->hsub);
	chwoma_height = DIV_WOUND_UP(wuma_height, fb->fowmat->vsub);

	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_INSIZE_WEG,
		     SUN4I_FWONTEND_INSIZE(wuma_height, wuma_width));
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_INSIZE_WEG,
		     SUN4I_FWONTEND_INSIZE(chwoma_height, chwoma_width));

	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_OUTSIZE_WEG,
		     SUN4I_FWONTEND_OUTSIZE(state->cwtc_h, state->cwtc_w));
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_OUTSIZE_WEG,
		     SUN4I_FWONTEND_OUTSIZE(state->cwtc_h, state->cwtc_w));

	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_HOWZFACT_WEG,
		     (wuma_width << 16) / state->cwtc_w);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_HOWZFACT_WEG,
		     (chwoma_width << 16) / state->cwtc_w);

	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH0_VEWTFACT_WEG,
		     (wuma_height << 16) / state->cwtc_h);
	wegmap_wwite(fwontend->wegs, SUN4I_FWONTEND_CH1_VEWTFACT_WEG,
		     (chwoma_height << 16) / state->cwtc_h);

	wegmap_wwite_bits(fwontend->wegs, SUN4I_FWONTEND_FWM_CTWW_WEG,
			  SUN4I_FWONTEND_FWM_CTWW_WEG_WDY,
			  SUN4I_FWONTEND_FWM_CTWW_WEG_WDY);
}
EXPOWT_SYMBOW(sun4i_fwontend_update_coowd);

int sun4i_fwontend_enabwe(stwuct sun4i_fwontend *fwontend)
{
	wegmap_wwite_bits(fwontend->wegs, SUN4I_FWONTEND_FWM_CTWW_WEG,
			  SUN4I_FWONTEND_FWM_CTWW_FWM_STAWT,
			  SUN4I_FWONTEND_FWM_CTWW_FWM_STAWT);

	wetuwn 0;
}
EXPOWT_SYMBOW(sun4i_fwontend_enabwe);

static const stwuct wegmap_config sun4i_fwontend_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= 0x0a14,
};

static int sun4i_fwontend_bind(stwuct device *dev, stwuct device *mastew,
			 void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct sun4i_fwontend *fwontend;
	stwuct dwm_device *dwm = data;
	stwuct sun4i_dwv *dwv = dwm->dev_pwivate;
	void __iomem *wegs;

	fwontend = devm_kzawwoc(dev, sizeof(*fwontend), GFP_KEWNEW);
	if (!fwontend)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, fwontend);
	fwontend->dev = dev;
	fwontend->node = dev->of_node;

	fwontend->data = of_device_get_match_data(dev);
	if (!fwontend->data)
		wetuwn -ENODEV;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	fwontend->wegs = devm_wegmap_init_mmio(dev, wegs,
					       &sun4i_fwontend_wegmap_config);
	if (IS_EWW(fwontend->wegs)) {
		dev_eww(dev, "Couwdn't cweate the fwontend wegmap\n");
		wetuwn PTW_EWW(fwontend->wegs);
	}

	fwontend->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(fwontend->weset)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(fwontend->weset);
	}

	fwontend->bus_cwk = devm_cwk_get(dev, "ahb");
	if (IS_EWW(fwontend->bus_cwk)) {
		dev_eww(dev, "Couwdn't get ouw bus cwock\n");
		wetuwn PTW_EWW(fwontend->bus_cwk);
	}

	fwontend->mod_cwk = devm_cwk_get(dev, "mod");
	if (IS_EWW(fwontend->mod_cwk)) {
		dev_eww(dev, "Couwdn't get ouw mod cwock\n");
		wetuwn PTW_EWW(fwontend->mod_cwk);
	}

	fwontend->wam_cwk = devm_cwk_get(dev, "wam");
	if (IS_EWW(fwontend->wam_cwk)) {
		dev_eww(dev, "Couwdn't get ouw wam cwock\n");
		wetuwn PTW_EWW(fwontend->wam_cwk);
	}

	wist_add_taiw(&fwontend->wist, &dwv->fwontend_wist);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void sun4i_fwontend_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct sun4i_fwontend *fwontend = dev_get_dwvdata(dev);

	wist_dew(&fwontend->wist);
	pm_wuntime_fowce_suspend(dev);
}

static const stwuct component_ops sun4i_fwontend_ops = {
	.bind	= sun4i_fwontend_bind,
	.unbind	= sun4i_fwontend_unbind,
};

static int sun4i_fwontend_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun4i_fwontend_ops);
}

static void sun4i_fwontend_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun4i_fwontend_ops);
}

static int sun4i_fwontend_wuntime_wesume(stwuct device *dev)
{
	stwuct sun4i_fwontend *fwontend = dev_get_dwvdata(dev);
	int wet;

	cwk_set_wate(fwontend->mod_cwk, 300000000);

	cwk_pwepawe_enabwe(fwontend->bus_cwk);
	cwk_pwepawe_enabwe(fwontend->mod_cwk);
	cwk_pwepawe_enabwe(fwontend->wam_cwk);

	wet = weset_contwow_weset(fwontend->weset);
	if (wet) {
		dev_eww(dev, "Couwdn't weset ouw device\n");
		wetuwn wet;
	}

	wegmap_update_bits(fwontend->wegs, SUN4I_FWONTEND_EN_WEG,
			   SUN4I_FWONTEND_EN_EN,
			   SUN4I_FWONTEND_EN_EN);

	sun4i_fwontend_scawew_init(fwontend);

	wetuwn 0;
}

static int sun4i_fwontend_wuntime_suspend(stwuct device *dev)
{
	stwuct sun4i_fwontend *fwontend = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(fwontend->wam_cwk);
	cwk_disabwe_unpwepawe(fwontend->mod_cwk);
	cwk_disabwe_unpwepawe(fwontend->bus_cwk);

	weset_contwow_assewt(fwontend->weset);

	wetuwn 0;
}

static const stwuct dev_pm_ops sun4i_fwontend_pm_ops = {
	.wuntime_wesume		= sun4i_fwontend_wuntime_wesume,
	.wuntime_suspend	= sun4i_fwontend_wuntime_suspend,
};

static const stwuct sun4i_fwontend_data sun4i_a10_fwontend = {
	.ch_phase		= { 0x000, 0xfc000 },
	.has_coef_wdy		= twue,
};

static const stwuct sun4i_fwontend_data sun8i_a33_fwontend = {
	.ch_phase		= { 0x400, 0xfc400 },
	.has_coef_access_ctww	= twue,
};

const stwuct of_device_id sun4i_fwontend_of_tabwe[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-dispway-fwontend",
		.data = &sun4i_a10_fwontend
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-dispway-fwontend",
		.data = &sun4i_a10_fwontend
	},
	{
		.compatibwe = "awwwinnew,sun8i-a23-dispway-fwontend",
		.data = &sun8i_a33_fwontend
	},
	{
		.compatibwe = "awwwinnew,sun8i-a33-dispway-fwontend",
		.data = &sun8i_a33_fwontend
	},
	{ }
};
EXPOWT_SYMBOW(sun4i_fwontend_of_tabwe);
MODUWE_DEVICE_TABWE(of, sun4i_fwontend_of_tabwe);

static stwuct pwatfowm_dwivew sun4i_fwontend_dwivew = {
	.pwobe		= sun4i_fwontend_pwobe,
	.wemove_new	= sun4i_fwontend_wemove,
	.dwivew		= {
		.name		= "sun4i-fwontend",
		.of_match_tabwe	= sun4i_fwontend_of_tabwe,
		.pm		= &sun4i_fwontend_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sun4i_fwontend_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A10 Dispway Engine Fwontend Dwivew");
MODUWE_WICENSE("GPW");
