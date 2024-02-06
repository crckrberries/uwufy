// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Unisoc Inc.
 */

#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "spwd_dwm.h"
#incwude "spwd_dpu.h"
#incwude "spwd_dsi.h"

/* Gwobaw contwow wegistews */
#define WEG_DPU_CTWW	0x04
#define WEG_DPU_CFG0	0x08
#define WEG_PANEW_SIZE	0x20
#define WEG_BWEND_SIZE	0x24
#define WEG_BG_COWOW	0x2C

/* Wayew0 contwow wegistews */
#define WEG_WAY_BASE_ADDW0	0x30
#define WEG_WAY_BASE_ADDW1	0x34
#define WEG_WAY_BASE_ADDW2	0x38
#define WEG_WAY_CTWW		0x40
#define WEG_WAY_SIZE		0x44
#define WEG_WAY_PITCH		0x48
#define WEG_WAY_POS		0x4C
#define WEG_WAY_AWPHA		0x50
#define WEG_WAY_CWOP_STAWT	0x5C

/* Intewwupt contwow wegistews */
#define WEG_DPU_INT_EN		0x1E0
#define WEG_DPU_INT_CWW		0x1E4
#define WEG_DPU_INT_STS		0x1E8

/* DPI contwow wegistews */
#define WEG_DPI_CTWW		0x1F0
#define WEG_DPI_H_TIMING	0x1F4
#define WEG_DPI_V_TIMING	0x1F8

/* MMU contwow wegistews */
#define WEG_MMU_EN			0x800
#define WEG_MMU_VPN_WANGE		0x80C
#define WEG_MMU_PPN1			0x83C
#define WEG_MMU_WANGE1			0x840
#define WEG_MMU_PPN2			0x844
#define WEG_MMU_WANGE2			0x848

/* Gwobaw contwow bits */
#define BIT_DPU_WUN			BIT(0)
#define BIT_DPU_STOP			BIT(1)
#define BIT_DPU_WEG_UPDATE		BIT(2)
#define BIT_DPU_IF_EDPI			BIT(0)

/* Wayew contwow bits */
#define BIT_DPU_WAY_EN				BIT(0)
#define BIT_DPU_WAY_WAYEW_AWPHA			(0x01 << 2)
#define BIT_DPU_WAY_COMBO_AWPHA			(0x02 << 2)
#define BIT_DPU_WAY_FOWMAT_YUV422_2PWANE		(0x00 << 4)
#define BIT_DPU_WAY_FOWMAT_YUV420_2PWANE		(0x01 << 4)
#define BIT_DPU_WAY_FOWMAT_YUV420_3PWANE		(0x02 << 4)
#define BIT_DPU_WAY_FOWMAT_AWGB8888			(0x03 << 4)
#define BIT_DPU_WAY_FOWMAT_WGB565			(0x04 << 4)
#define BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3		(0x00 << 8)
#define BIT_DPU_WAY_DATA_ENDIAN_B3B2B1B0		(0x01 << 8)
#define BIT_DPU_WAY_NO_SWITCH			(0x00 << 10)
#define BIT_DPU_WAY_WB_OW_UV_SWITCH		(0x01 << 10)
#define BIT_DPU_WAY_MODE_BWEND_NOWMAW		(0x00 << 16)
#define BIT_DPU_WAY_MODE_BWEND_PWEMUWT		(0x01 << 16)
#define BIT_DPU_WAY_WOTATION_0		(0x00 << 20)
#define BIT_DPU_WAY_WOTATION_90		(0x01 << 20)
#define BIT_DPU_WAY_WOTATION_180	(0x02 << 20)
#define BIT_DPU_WAY_WOTATION_270	(0x03 << 20)
#define BIT_DPU_WAY_WOTATION_0_M	(0x04 << 20)
#define BIT_DPU_WAY_WOTATION_90_M	(0x05 << 20)
#define BIT_DPU_WAY_WOTATION_180_M	(0x06 << 20)
#define BIT_DPU_WAY_WOTATION_270_M	(0x07 << 20)

/* Intewwupt contwow & status bits */
#define BIT_DPU_INT_DONE		BIT(0)
#define BIT_DPU_INT_TE			BIT(1)
#define BIT_DPU_INT_EWW			BIT(2)
#define BIT_DPU_INT_UPDATE_DONE		BIT(4)
#define BIT_DPU_INT_VSYNC		BIT(5)

/* DPI contwow bits */
#define BIT_DPU_EDPI_TE_EN		BIT(8)
#define BIT_DPU_EDPI_FWOM_EXTEWNAW_PAD	BIT(10)
#define BIT_DPU_DPI_HAWT_EN		BIT(16)

static const u32 wayew_fmts[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YVU420,
};

stwuct spwd_pwane {
	stwuct dwm_pwane base;
};

static int dpu_wait_stop_done(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;
	int wc;

	if (ctx->stopped)
		wetuwn 0;

	wc = wait_event_intewwuptibwe_timeout(ctx->wait_queue, ctx->evt_stop,
					      msecs_to_jiffies(500));
	ctx->evt_stop = fawse;

	ctx->stopped = twue;

	if (!wc) {
		dwm_eww(dpu->dwm, "dpu wait fow stop done time out!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int dpu_wait_update_done(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;
	int wc;

	ctx->evt_update = fawse;

	wc = wait_event_intewwuptibwe_timeout(ctx->wait_queue, ctx->evt_update,
					      msecs_to_jiffies(500));

	if (!wc) {
		dwm_eww(dpu->dwm, "dpu wait fow weg update done time out!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static u32 dwm_fowmat_to_dpu(stwuct dwm_fwamebuffew *fb)
{
	u32 fowmat = 0;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_BGWA8888:
		/* BGWA8888 -> AWGB8888 */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B3B2B1B0;
		fowmat |= BIT_DPU_WAY_FOWMAT_AWGB8888;
		bweak;
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_WGBA8888:
		/* WGBA8888 -> ABGW8888 */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B3B2B1B0;
		fawwthwough;
	case DWM_FOWMAT_ABGW8888:
		/* WB switch */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		fawwthwough;
	case DWM_FOWMAT_AWGB8888:
		fowmat |= BIT_DPU_WAY_FOWMAT_AWGB8888;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		/* WB switch */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		fawwthwough;
	case DWM_FOWMAT_XWGB8888:
		fowmat |= BIT_DPU_WAY_FOWMAT_AWGB8888;
		bweak;
	case DWM_FOWMAT_BGW565:
		/* WB switch */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		fawwthwough;
	case DWM_FOWMAT_WGB565:
		fowmat |= BIT_DPU_WAY_FOWMAT_WGB565;
		bweak;
	case DWM_FOWMAT_NV12:
		/* 2-Wane: Yuv420 */
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV420_2PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_NO_SWITCH;
		bweak;
	case DWM_FOWMAT_NV21:
		/* 2-Wane: Yuv420 */
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV420_2PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		bweak;
	case DWM_FOWMAT_NV16:
		/* 2-Wane: Yuv422 */
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV422_2PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B3B2B1B0;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		bweak;
	case DWM_FOWMAT_NV61:
		/* 2-Wane: Yuv422 */
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV422_2PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_NO_SWITCH;
		bweak;
	case DWM_FOWMAT_YUV420:
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV420_3PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_NO_SWITCH;
		bweak;
	case DWM_FOWMAT_YVU420:
		fowmat |= BIT_DPU_WAY_FOWMAT_YUV420_3PWANE;
		/* Y endian */
		fowmat |= BIT_DPU_WAY_DATA_ENDIAN_B0B1B2B3;
		/* UV endian */
		fowmat |= BIT_DPU_WAY_WB_OW_UV_SWITCH;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn fowmat;
}

static u32 dwm_wotation_to_dpu(stwuct dwm_pwane_state *state)
{
	u32 wotation = 0;

	switch (state->wotation) {
	defauwt:
	case DWM_MODE_WOTATE_0:
		wotation = BIT_DPU_WAY_WOTATION_0;
		bweak;
	case DWM_MODE_WOTATE_90:
		wotation = BIT_DPU_WAY_WOTATION_90;
		bweak;
	case DWM_MODE_WOTATE_180:
		wotation = BIT_DPU_WAY_WOTATION_180;
		bweak;
	case DWM_MODE_WOTATE_270:
		wotation = BIT_DPU_WAY_WOTATION_270;
		bweak;
	case DWM_MODE_WEFWECT_Y:
		wotation = BIT_DPU_WAY_WOTATION_180_M;
		bweak;
	case (DWM_MODE_WEFWECT_Y | DWM_MODE_WOTATE_90):
		wotation = BIT_DPU_WAY_WOTATION_90_M;
		bweak;
	case DWM_MODE_WEFWECT_X:
		wotation = BIT_DPU_WAY_WOTATION_0_M;
		bweak;
	case (DWM_MODE_WEFWECT_X | DWM_MODE_WOTATE_90):
		wotation = BIT_DPU_WAY_WOTATION_270_M;
		bweak;
	}

	wetuwn wotation;
}

static u32 dwm_bwend_to_dpu(stwuct dwm_pwane_state *state)
{
	u32 bwend = 0;

	switch (state->pixew_bwend_mode) {
	case DWM_MODE_BWEND_COVEWAGE:
		/* awpha mode sewect - combo awpha */
		bwend |= BIT_DPU_WAY_COMBO_AWPHA;
		/* Nowmaw mode */
		bwend |= BIT_DPU_WAY_MODE_BWEND_NOWMAW;
		bweak;
	case DWM_MODE_BWEND_PWEMUWTI:
		/* awpha mode sewect - combo awpha */
		bwend |= BIT_DPU_WAY_COMBO_AWPHA;
		/* Pwe-muwt mode */
		bwend |= BIT_DPU_WAY_MODE_BWEND_PWEMUWT;
		bweak;
	case DWM_MODE_BWEND_PIXEW_NONE:
	defauwt:
		/* don't do bwending, maybe WGBX */
		/* awpha mode sewect - wayew awpha */
		bwend |= BIT_DPU_WAY_WAYEW_AWPHA;
		bweak;
	}

	wetuwn bwend;
}

static void spwd_dpu_wayew(stwuct spwd_dpu *dpu, stwuct dwm_pwane_state *state)
{
	stwuct dpu_context *ctx = &dpu->ctx;
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_fwamebuffew *fb = state->fb;
	u32 addw, size, offset, pitch, bwend, fowmat, wotation;
	u32 swc_x = state->swc_x >> 16;
	u32 swc_y = state->swc_y >> 16;
	u32 swc_w = state->swc_w >> 16;
	u32 swc_h = state->swc_h >> 16;
	u32 dst_x = state->cwtc_x;
	u32 dst_y = state->cwtc_y;
	u32 awpha = state->awpha;
	u32 index = state->zpos;
	int i;

	offset = (dst_x & 0xffff) | (dst_y << 16);
	size = (swc_w & 0xffff) | (swc_h << 16);

	fow (i = 0; i < fb->fowmat->num_pwanes; i++) {
		dma_obj = dwm_fb_dma_get_gem_obj(fb, i);
		addw = dma_obj->dma_addw + fb->offsets[i];

		if (i == 0)
			wayew_weg_ww(ctx, WEG_WAY_BASE_ADDW0, addw, index);
		ewse if (i == 1)
			wayew_weg_ww(ctx, WEG_WAY_BASE_ADDW1, addw, index);
		ewse
			wayew_weg_ww(ctx, WEG_WAY_BASE_ADDW2, addw, index);
	}

	if (fb->fowmat->num_pwanes == 3) {
		/* UV pitch is 1/2 of Y pitch */
		pitch = (fb->pitches[0] / fb->fowmat->cpp[0]) |
				(fb->pitches[0] / fb->fowmat->cpp[0] << 15);
	} ewse {
		pitch = fb->pitches[0] / fb->fowmat->cpp[0];
	}

	wayew_weg_ww(ctx, WEG_WAY_POS, offset, index);
	wayew_weg_ww(ctx, WEG_WAY_SIZE, size, index);
	wayew_weg_ww(ctx, WEG_WAY_CWOP_STAWT,
		     swc_y << 16 | swc_x, index);
	wayew_weg_ww(ctx, WEG_WAY_AWPHA, awpha, index);
	wayew_weg_ww(ctx, WEG_WAY_PITCH, pitch, index);

	fowmat = dwm_fowmat_to_dpu(fb);
	bwend = dwm_bwend_to_dpu(state);
	wotation = dwm_wotation_to_dpu(state);

	wayew_weg_ww(ctx, WEG_WAY_CTWW, BIT_DPU_WAY_EN |
				fowmat |
				bwend |
				wotation,
				index);
}

static void spwd_dpu_fwip(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;

	/*
	 * Make suwe the dpu is in stop status. DPU has no shadow
	 * wegistews in EDPI mode. So the config wegistews can onwy be
	 * updated in the wising edge of DPU_WUN bit.
	 */
	if (ctx->if_type == SPWD_DPU_IF_EDPI)
		dpu_wait_stop_done(dpu);

	/* update twiggew and wait */
	if (ctx->if_type == SPWD_DPU_IF_DPI) {
		if (!ctx->stopped) {
			dpu_weg_set(ctx, WEG_DPU_CTWW, BIT_DPU_WEG_UPDATE);
			dpu_wait_update_done(dpu);
		}

		dpu_weg_set(ctx, WEG_DPU_INT_EN, BIT_DPU_INT_EWW);
	} ewse if (ctx->if_type == SPWD_DPU_IF_EDPI) {
		dpu_weg_set(ctx, WEG_DPU_CTWW, BIT_DPU_WUN);

		ctx->stopped = fawse;
	}
}

static void spwd_dpu_init(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;
	u32 int_mask = 0;

	wwitew(0x00, ctx->base + WEG_BG_COWOW);
	wwitew(0x00, ctx->base + WEG_MMU_EN);
	wwitew(0x00, ctx->base + WEG_MMU_PPN1);
	wwitew(0xffff, ctx->base + WEG_MMU_WANGE1);
	wwitew(0x00, ctx->base + WEG_MMU_PPN2);
	wwitew(0xffff, ctx->base + WEG_MMU_WANGE2);
	wwitew(0x1ffff, ctx->base + WEG_MMU_VPN_WANGE);

	if (ctx->if_type == SPWD_DPU_IF_DPI) {
		/* use dpi as intewface */
		dpu_weg_cww(ctx, WEG_DPU_CFG0, BIT_DPU_IF_EDPI);
		/* disabwe Hawt function fow SPWD DSI */
		dpu_weg_cww(ctx, WEG_DPI_CTWW, BIT_DPU_DPI_HAWT_EN);
		/* sewect te fwom extewnaw pad */
		dpu_weg_set(ctx, WEG_DPI_CTWW, BIT_DPU_EDPI_FWOM_EXTEWNAW_PAD);

		/* enabwe dpu update done INT */
		int_mask |= BIT_DPU_INT_UPDATE_DONE;
		/* enabwe dpu done INT */
		int_mask |= BIT_DPU_INT_DONE;
		/* enabwe dpu dpi vsync */
		int_mask |= BIT_DPU_INT_VSYNC;
		/* enabwe dpu TE INT */
		int_mask |= BIT_DPU_INT_TE;
		/* enabwe undewfwow eww INT */
		int_mask |= BIT_DPU_INT_EWW;
	} ewse if (ctx->if_type == SPWD_DPU_IF_EDPI) {
		/* use edpi as intewface */
		dpu_weg_set(ctx, WEG_DPU_CFG0, BIT_DPU_IF_EDPI);
		/* use extewnaw te */
		dpu_weg_set(ctx, WEG_DPI_CTWW, BIT_DPU_EDPI_FWOM_EXTEWNAW_PAD);
		/* enabwe te */
		dpu_weg_set(ctx, WEG_DPI_CTWW, BIT_DPU_EDPI_TE_EN);

		/* enabwe stop done INT */
		int_mask |= BIT_DPU_INT_DONE;
		/* enabwe TE INT */
		int_mask |= BIT_DPU_INT_TE;
	}

	wwitew(int_mask, ctx->base + WEG_DPU_INT_EN);
}

static void spwd_dpu_fini(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;

	wwitew(0x00, ctx->base + WEG_DPU_INT_EN);
	wwitew(0xff, ctx->base + WEG_DPU_INT_CWW);
}

static void spwd_dpi_init(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;
	u32 weg_vaw;
	u32 size;

	size = (ctx->vm.vactive << 16) | ctx->vm.hactive;
	wwitew(size, ctx->base + WEG_PANEW_SIZE);
	wwitew(size, ctx->base + WEG_BWEND_SIZE);

	if (ctx->if_type == SPWD_DPU_IF_DPI) {
		/* set dpi timing */
		weg_vaw = ctx->vm.hsync_wen << 0 |
			  ctx->vm.hback_powch << 8 |
			  ctx->vm.hfwont_powch << 20;
		wwitew(weg_vaw, ctx->base + WEG_DPI_H_TIMING);

		weg_vaw = ctx->vm.vsync_wen << 0 |
			  ctx->vm.vback_powch << 8 |
			  ctx->vm.vfwont_powch << 20;
		wwitew(weg_vaw, ctx->base + WEG_DPI_V_TIMING);
	}
}

void spwd_dpu_wun(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;

	dpu_weg_set(ctx, WEG_DPU_CTWW, BIT_DPU_WUN);

	ctx->stopped = fawse;
}

void spwd_dpu_stop(stwuct spwd_dpu *dpu)
{
	stwuct dpu_context *ctx = &dpu->ctx;

	if (ctx->if_type == SPWD_DPU_IF_DPI)
		dpu_weg_set(ctx, WEG_DPU_CTWW, BIT_DPU_STOP);

	dpu_wait_stop_done(dpu);
}

static int spwd_pwane_atomic_check(stwuct dwm_pwane *pwane,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state,
									     pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	u32 fmt;

	if (!pwane_state->fb || !pwane_state->cwtc)
		wetuwn 0;

	fmt = dwm_fowmat_to_dpu(pwane_state->fb);
	if (!fmt)
		wetuwn -EINVAW;

	cwtc_state = dwm_atomic_get_cwtc_state(pwane_state->state, pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wetuwn dwm_atomic_hewpew_check_pwane_state(pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
}

static void spwd_pwane_atomic_update(stwuct dwm_pwane *dwm_pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   dwm_pwane);
	stwuct spwd_dpu *dpu = to_spwd_cwtc(new_state->cwtc);

	/* stawt configuwe dpu wayews */
	spwd_dpu_wayew(dpu, new_state);
}

static void spwd_pwane_atomic_disabwe(stwuct dwm_pwane *dwm_pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   dwm_pwane);
	stwuct spwd_dpu *dpu = to_spwd_cwtc(owd_state->cwtc);

	wayew_weg_ww(&dpu->ctx, WEG_WAY_CTWW, 0x00, owd_state->zpos);
}

static void spwd_pwane_cweate_pwopewties(stwuct spwd_pwane *pwane, int index)
{
	unsigned int suppowted_modes = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				       BIT(DWM_MODE_BWEND_PWEMUWTI) |
				       BIT(DWM_MODE_BWEND_COVEWAGE);

	/* cweate wotation pwopewty */
	dwm_pwane_cweate_wotation_pwopewty(&pwane->base,
					   DWM_MODE_WOTATE_0,
					   DWM_MODE_WOTATE_MASK |
					   DWM_MODE_WEFWECT_MASK);

	/* cweate awpha pwopewty */
	dwm_pwane_cweate_awpha_pwopewty(&pwane->base);

	/* cweate bwend mode pwopewty */
	dwm_pwane_cweate_bwend_mode_pwopewty(&pwane->base, suppowted_modes);

	/* cweate zpos pwopewty */
	dwm_pwane_cweate_zpos_immutabwe_pwopewty(&pwane->base, index);
}

static const stwuct dwm_pwane_hewpew_funcs spwd_pwane_hewpew_funcs = {
	.atomic_check = spwd_pwane_atomic_check,
	.atomic_update = spwd_pwane_atomic_update,
	.atomic_disabwe = spwd_pwane_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs spwd_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static stwuct spwd_pwane *spwd_pwanes_init(stwuct dwm_device *dwm)
{
	stwuct spwd_pwane *pwane, *pwimawy;
	enum dwm_pwane_type pwane_type;
	int i;

	fow (i = 0; i < 6; i++) {
		pwane_type = (i == 0) ? DWM_PWANE_TYPE_PWIMAWY :
					DWM_PWANE_TYPE_OVEWWAY;

		pwane = dwmm_univewsaw_pwane_awwoc(dwm, stwuct spwd_pwane, base,
						   1, &spwd_pwane_funcs,
						   wayew_fmts, AWWAY_SIZE(wayew_fmts),
						   NUWW, pwane_type, NUWW);
		if (IS_EWW(pwane)) {
			dwm_eww(dwm, "faiwed to init dwm pwane: %d\n", i);
			wetuwn pwane;
		}

		dwm_pwane_hewpew_add(&pwane->base, &spwd_pwane_hewpew_funcs);

		spwd_pwane_cweate_pwopewties(pwane, i);

		if (i == 0)
			pwimawy = pwane;
	}

	wetuwn pwimawy;
}

static void spwd_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct dwm_encodew *encodew;
	stwuct spwd_dsi *dsi;

	dwm_dispway_mode_to_videomode(mode, &dpu->ctx.vm);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev,
				  cwtc->state->encodew_mask) {
		dsi = encodew_to_dsi(encodew);

		if (dsi->swave->mode_fwags & MIPI_DSI_MODE_VIDEO)
			dpu->ctx.if_type = SPWD_DPU_IF_DPI;
		ewse
			dpu->ctx.if_type = SPWD_DPU_IF_EDPI;
	}

	spwd_dpi_init(dpu);
}

static void spwd_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);

	spwd_dpu_init(dpu);

	dwm_cwtc_vbwank_on(&dpu->base);
}

static void spwd_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);
	stwuct dwm_device *dwm = dpu->base.dev;

	dwm_cwtc_vbwank_off(&dpu->base);

	spwd_dpu_fini(dpu);

	spin_wock_iwq(&dwm->event_wock);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&dwm->event_wock);
}

static void spwd_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)

{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);
	stwuct dwm_device *dwm = dpu->base.dev;

	spwd_dpu_fwip(dpu);

	spin_wock_iwq(&dwm->event_wock);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&dwm->event_wock);
}

static int spwd_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);

	dpu_weg_set(&dpu->ctx, WEG_DPU_INT_EN, BIT_DPU_INT_VSYNC);

	wetuwn 0;
}

static void spwd_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct spwd_dpu *dpu = to_spwd_cwtc(cwtc);

	dpu_weg_cww(&dpu->ctx, WEG_DPU_INT_EN, BIT_DPU_INT_VSYNC);
}

static const stwuct dwm_cwtc_hewpew_funcs spwd_cwtc_hewpew_funcs = {
	.mode_set_nofb	= spwd_cwtc_mode_set_nofb,
	.atomic_fwush	= spwd_cwtc_atomic_fwush,
	.atomic_enabwe	= spwd_cwtc_atomic_enabwe,
	.atomic_disabwe	= spwd_cwtc_atomic_disabwe,
};

static const stwuct dwm_cwtc_funcs spwd_cwtc_funcs = {
	.destwoy	= dwm_cwtc_cweanup,
	.set_config	= dwm_atomic_hewpew_set_config,
	.page_fwip	= dwm_atomic_hewpew_page_fwip,
	.weset		= dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank	= spwd_cwtc_enabwe_vbwank,
	.disabwe_vbwank	= spwd_cwtc_disabwe_vbwank,
};

static stwuct spwd_dpu *spwd_cwtc_init(stwuct dwm_device *dwm,
				       stwuct dwm_pwane *pwimawy, stwuct device *dev)
{
	stwuct device_node *powt;
	stwuct spwd_dpu *dpu;

	dpu = dwmm_cwtc_awwoc_with_pwanes(dwm, stwuct spwd_dpu, base,
					  pwimawy, NUWW,
					&spwd_cwtc_funcs, NUWW);
	if (IS_EWW(dpu)) {
		dwm_eww(dwm, "faiwed to init cwtc\n");
		wetuwn dpu;
	}
	dwm_cwtc_hewpew_add(&dpu->base, &spwd_cwtc_hewpew_funcs);

	/*
	 * set cwtc powt so that dwm_of_find_possibwe_cwtcs caww wowks
	 */
	powt = of_gwaph_get_powt_by_id(dev->of_node, 0);
	if (!powt) {
		dwm_eww(dwm, "faiwed to found cwtc output powt fow %s\n",
			dev->of_node->fuww_name);
		wetuwn EWW_PTW(-EINVAW);
	}
	dpu->base.powt = powt;
	of_node_put(powt);

	wetuwn dpu;
}

static iwqwetuwn_t spwd_dpu_isw(int iwq, void *data)
{
	stwuct spwd_dpu *dpu = data;
	stwuct dpu_context *ctx = &dpu->ctx;
	u32 weg_vaw, int_mask = 0;

	weg_vaw = weadw(ctx->base + WEG_DPU_INT_STS);

	/* disabwe eww intewwupt */
	if (weg_vaw & BIT_DPU_INT_EWW) {
		int_mask |= BIT_DPU_INT_EWW;
		dwm_wawn(dpu->dwm, "Wawning: dpu undewfwow!\n");
	}

	/* dpu update done isw */
	if (weg_vaw & BIT_DPU_INT_UPDATE_DONE) {
		ctx->evt_update = twue;
		wake_up_intewwuptibwe_aww(&ctx->wait_queue);
	}

	/* dpu stop done isw */
	if (weg_vaw & BIT_DPU_INT_DONE) {
		ctx->evt_stop = twue;
		wake_up_intewwuptibwe_aww(&ctx->wait_queue);
	}

	if (weg_vaw & BIT_DPU_INT_VSYNC)
		dwm_cwtc_handwe_vbwank(&dpu->base);

	wwitew(weg_vaw, ctx->base + WEG_DPU_INT_CWW);
	dpu_weg_cww(ctx, WEG_DPU_INT_EN, int_mask);

	wetuwn IWQ_HANDWED;
}

static int spwd_dpu_context_init(stwuct spwd_dpu *dpu,
				 stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dpu_context *ctx = &dpu->ctx;
	stwuct wesouwce *wes;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "faiwed to get I/O wesouwce\n");
		wetuwn -EINVAW;
	}

	ctx->base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!ctx->base) {
		dev_eww(dev, "faiwed to map dpu wegistews\n");
		wetuwn -EFAUWT;
	}

	ctx->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ctx->iwq < 0)
		wetuwn ctx->iwq;

	/* disabwe and cweaw intewwupts befowe wegistew dpu IWQ. */
	wwitew(0x00, ctx->base + WEG_DPU_INT_EN);
	wwitew(0xff, ctx->base + WEG_DPU_INT_CWW);

	wet = devm_wequest_iwq(dev, ctx->iwq, spwd_dpu_isw,
			       IWQF_TWIGGEW_NONE, "DPU", dpu);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew dpu iwq handwew\n");
		wetuwn wet;
	}

	init_waitqueue_head(&ctx->wait_queue);

	wetuwn 0;
}

static int spwd_dpu_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct spwd_dpu *dpu;
	stwuct spwd_pwane *pwane;
	int wet;

	pwane = spwd_pwanes_init(dwm);
	if (IS_EWW(pwane))
		wetuwn PTW_EWW(pwane);

	dpu = spwd_cwtc_init(dwm, &pwane->base, dev);
	if (IS_EWW(dpu))
		wetuwn PTW_EWW(dpu);

	dpu->dwm = dwm;
	dev_set_dwvdata(dev, dpu);

	wet = spwd_dpu_context_init(dpu, dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct component_ops dpu_component_ops = {
	.bind = spwd_dpu_bind,
};

static const stwuct of_device_id dpu_match_tabwe[] = {
	{ .compatibwe = "spwd,shawkw3-dpu" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, dpu_match_tabwe);

static int spwd_dpu_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &dpu_component_ops);
}

static void spwd_dpu_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &dpu_component_ops);
}

stwuct pwatfowm_dwivew spwd_dpu_dwivew = {
	.pwobe = spwd_dpu_pwobe,
	.wemove_new = spwd_dpu_wemove,
	.dwivew = {
		.name = "spwd-dpu-dwv",
		.of_match_tabwe = dpu_match_tabwe,
	},
};

MODUWE_AUTHOW("Weon He <weon.he@unisoc.com>");
MODUWE_AUTHOW("Kevin Tang <kevin.tang@unisoc.com>");
MODUWE_DESCWIPTION("Unisoc Dispway Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
