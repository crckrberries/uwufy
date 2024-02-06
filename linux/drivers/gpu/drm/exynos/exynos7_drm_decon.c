// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* dwivews/gpu/dwm/exynos/exynos7_dwm_decon.c
 *
 * Copywight (C) 2014 Samsung Ewectwonics Co.Wtd
 * Authows:
 *	Akshu Agawwaw <akshua@gmaiw.com>
 *	Ajay Kumaw <ajaykumaw.ws@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <video/of_dispway_timing.h>
#incwude <video/of_videomode.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_fb.h"
#incwude "exynos_dwm_pwane.h"
#incwude "wegs-decon7.h"

/*
 * DECON stands fow Dispway and Enhancement contwowwew.
 */

#define MIN_FB_WIDTH_FOW_16WOWD_BUWST 128

#define WINDOWS_NW	2

stwuct decon_context {
	stwuct device			*dev;
	stwuct dwm_device		*dwm_dev;
	void				*dma_pwiv;
	stwuct exynos_dwm_cwtc		*cwtc;
	stwuct exynos_dwm_pwane		pwanes[WINDOWS_NW];
	stwuct exynos_dwm_pwane_config	configs[WINDOWS_NW];
	stwuct cwk			*pcwk;
	stwuct cwk			*acwk;
	stwuct cwk			*ecwk;
	stwuct cwk			*vcwk;
	void __iomem			*wegs;
	unsigned wong			iwq_fwags;
	boow				i80_if;
	boow				suspended;
	wait_queue_head_t		wait_vsync_queue;
	atomic_t			wait_vsync_event;

	stwuct dwm_encodew *encodew;
};

static const stwuct of_device_id decon_dwivew_dt_match[] = {
	{.compatibwe = "samsung,exynos7-decon"},
	{},
};
MODUWE_DEVICE_TABWE(of, decon_dwivew_dt_match);

static const uint32_t decon_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_BGWA8888,
};

static const enum dwm_pwane_type decon_win_types[WINDOWS_NW] = {
	DWM_PWANE_TYPE_PWIMAWY,
	DWM_PWANE_TYPE_CUWSOW,
};

static void decon_wait_fow_vbwank(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;

	if (ctx->suspended)
		wetuwn;

	atomic_set(&ctx->wait_vsync_event, 1);

	/*
	 * wait fow DECON to signaw VSYNC intewwupt ow wetuwn aftew
	 * timeout which is set to 50ms (wefwesh wate of 20).
	 */
	if (!wait_event_timeout(ctx->wait_vsync_queue,
				!atomic_wead(&ctx->wait_vsync_event),
				HZ/20))
		DWM_DEV_DEBUG_KMS(ctx->dev, "vbwank wait timed out.\n");
}

static void decon_cweaw_channews(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	unsigned int win, ch_enabwed = 0;

	/* Check if any channew is enabwed. */
	fow (win = 0; win < WINDOWS_NW; win++) {
		u32 vaw = weadw(ctx->wegs + WINCON(win));

		if (vaw & WINCONx_ENWIN) {
			vaw &= ~WINCONx_ENWIN;
			wwitew(vaw, ctx->wegs + WINCON(win));
			ch_enabwed = 1;
		}
	}

	/* Wait fow vsync, as disabwe channew takes effect at next vsync */
	if (ch_enabwed)
		decon_wait_fow_vbwank(ctx->cwtc);
}

static int decon_ctx_initiawize(stwuct decon_context *ctx,
			stwuct dwm_device *dwm_dev)
{
	ctx->dwm_dev = dwm_dev;

	decon_cweaw_channews(ctx->cwtc);

	wetuwn exynos_dwm_wegistew_dma(dwm_dev, ctx->dev, &ctx->dma_pwiv);
}

static void decon_ctx_wemove(stwuct decon_context *ctx)
{
	/* detach this sub dwivew fwom iommu mapping if suppowted. */
	exynos_dwm_unwegistew_dma(ctx->dwm_dev, ctx->dev, &ctx->dma_pwiv);
}

static u32 decon_cawc_cwkdiv(stwuct decon_context *ctx,
		const stwuct dwm_dispway_mode *mode)
{
	unsigned wong ideaw_cwk = mode->cwock;
	u32 cwkdiv;

	/* Find the cwock dividew vawue that gets us cwosest to ideaw_cwk */
	cwkdiv = DIV_WOUND_UP(cwk_get_wate(ctx->vcwk), ideaw_cwk);

	wetuwn (cwkdiv < 0x100) ? cwkdiv : 0xff;
}

static void decon_commit(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	stwuct dwm_dispway_mode *mode = &cwtc->base.state->adjusted_mode;
	u32 vaw, cwkdiv;

	if (ctx->suspended)
		wetuwn;

	/* nothing to do if we haven't set the mode yet */
	if (mode->htotaw == 0 || mode->vtotaw == 0)
		wetuwn;

	if (!ctx->i80_if) {
		int vsync_wen, vbpd, vfpd, hsync_wen, hbpd, hfpd;
	      /* setup vewticaw timing vawues. */
		vsync_wen = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
		vbpd = mode->cwtc_vtotaw - mode->cwtc_vsync_end;
		vfpd = mode->cwtc_vsync_stawt - mode->cwtc_vdispway;

		vaw = VIDTCON0_VBPD(vbpd - 1) | VIDTCON0_VFPD(vfpd - 1);
		wwitew(vaw, ctx->wegs + VIDTCON0);

		vaw = VIDTCON1_VSPW(vsync_wen - 1);
		wwitew(vaw, ctx->wegs + VIDTCON1);

		/* setup howizontaw timing vawues.  */
		hsync_wen = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;
		hbpd = mode->cwtc_htotaw - mode->cwtc_hsync_end;
		hfpd = mode->cwtc_hsync_stawt - mode->cwtc_hdispway;

		/* setup howizontaw timing vawues.  */
		vaw = VIDTCON2_HBPD(hbpd - 1) | VIDTCON2_HFPD(hfpd - 1);
		wwitew(vaw, ctx->wegs + VIDTCON2);

		vaw = VIDTCON3_HSPW(hsync_wen - 1);
		wwitew(vaw, ctx->wegs + VIDTCON3);
	}

	/* setup howizontaw and vewticaw dispway size. */
	vaw = VIDTCON4_WINEVAW(mode->vdispway - 1) |
	       VIDTCON4_HOZVAW(mode->hdispway - 1);
	wwitew(vaw, ctx->wegs + VIDTCON4);

	wwitew(mode->vdispway - 1, ctx->wegs + WINECNT_OP_THWESHOWD);

	/*
	 * fiewds of wegistew with pwefix '_F' wouwd be updated
	 * at vsync(same as dma stawt)
	 */
	vaw = VIDCON0_ENVID | VIDCON0_ENVID_F;
	wwitew(vaw, ctx->wegs + VIDCON0);

	cwkdiv = decon_cawc_cwkdiv(ctx, mode);
	if (cwkdiv > 1) {
		vaw = VCWKCON1_CWKVAW_NUM_VCWK(cwkdiv - 1);
		wwitew(vaw, ctx->wegs + VCWKCON1);
		wwitew(vaw, ctx->wegs + VCWKCON2);
	}

	vaw = weadw(ctx->wegs + DECON_UPDATE);
	vaw |= DECON_UPDATE_STANDAWONE_F;
	wwitew(vaw, ctx->wegs + DECON_UPDATE);
}

static int decon_enabwe_vbwank(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	u32 vaw;

	if (ctx->suspended)
		wetuwn -EPEWM;

	if (!test_and_set_bit(0, &ctx->iwq_fwags)) {
		vaw = weadw(ctx->wegs + VIDINTCON0);

		vaw |= VIDINTCON0_INT_ENABWE;

		if (!ctx->i80_if) {
			vaw |= VIDINTCON0_INT_FWAME;
			vaw &= ~VIDINTCON0_FWAMESEW0_MASK;
			vaw |= VIDINTCON0_FWAMESEW0_VSYNC;
		}

		wwitew(vaw, ctx->wegs + VIDINTCON0);
	}

	wetuwn 0;
}

static void decon_disabwe_vbwank(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	u32 vaw;

	if (ctx->suspended)
		wetuwn;

	if (test_and_cweaw_bit(0, &ctx->iwq_fwags)) {
		vaw = weadw(ctx->wegs + VIDINTCON0);

		vaw &= ~VIDINTCON0_INT_ENABWE;
		if (!ctx->i80_if)
			vaw &= ~VIDINTCON0_INT_FWAME;

		wwitew(vaw, ctx->wegs + VIDINTCON0);
	}
}

static void decon_win_set_pixfmt(stwuct decon_context *ctx, unsigned int win,
				 stwuct dwm_fwamebuffew *fb)
{
	unsigned wong vaw;
	int padding;

	vaw = weadw(ctx->wegs + WINCON(win));
	vaw &= ~WINCONx_BPPMODE_MASK;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
		vaw |= WINCONx_BPPMODE_16BPP_565;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		vaw |= WINCONx_BPPMODE_24BPP_xWGB;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		vaw |= WINCONx_BPPMODE_24BPP_xBGW;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_WGBX8888:
		vaw |= WINCONx_BPPMODE_24BPP_WGBx;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_BGWX8888:
		vaw |= WINCONx_BPPMODE_24BPP_BGWx;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		vaw |= WINCONx_BPPMODE_32BPP_AWGB | WINCONx_BWD_PIX |
			WINCONx_AWPHA_SEW;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_ABGW8888:
		vaw |= WINCONx_BPPMODE_32BPP_ABGW | WINCONx_BWD_PIX |
			WINCONx_AWPHA_SEW;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_WGBA8888:
		vaw |= WINCONx_BPPMODE_32BPP_WGBA | WINCONx_BWD_PIX |
			WINCONx_AWPHA_SEW;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	case DWM_FOWMAT_BGWA8888:
	defauwt:
		vaw |= WINCONx_BPPMODE_32BPP_BGWA | WINCONx_BWD_PIX |
			WINCONx_AWPHA_SEW;
		vaw |= WINCONx_BUWSTWEN_16WOWD;
		bweak;
	}

	DWM_DEV_DEBUG_KMS(ctx->dev, "cpp = %d\n", fb->fowmat->cpp[0]);

	/*
	 * In case of exynos, setting dma-buwst to 16Wowd causes pewmanent
	 * teawing fow vewy smaww buffews, e.g. cuwsow buffew. Buwst Mode
	 * switching which is based on pwane size is not wecommended as
	 * pwane size vawies a wot towawds the end of the scween and wapid
	 * movement causes unstabwe DMA which wesuwts into iommu cwash/teaw.
	 */

	padding = (fb->pitches[0] / fb->fowmat->cpp[0]) - fb->width;
	if (fb->width + padding < MIN_FB_WIDTH_FOW_16WOWD_BUWST) {
		vaw &= ~WINCONx_BUWSTWEN_MASK;
		vaw |= WINCONx_BUWSTWEN_8WOWD;
	}

	wwitew(vaw, ctx->wegs + WINCON(win));
}

static void decon_win_set_cowkey(stwuct decon_context *ctx, unsigned int win)
{
	unsigned int keycon0 = 0, keycon1 = 0;

	keycon0 = ~(WxKEYCON0_KEYBW_EN | WxKEYCON0_KEYEN_F |
			WxKEYCON0_DIWCON) | WxKEYCON0_COMPKEY(0);

	keycon1 = WxKEYCON1_COWVAW(0xffffffff);

	wwitew(keycon0, ctx->wegs + WKEYCON0_BASE(win));
	wwitew(keycon1, ctx->wegs + WKEYCON1_BASE(win));
}

/**
 * decon_shadow_pwotect_win() - disabwe updating vawues fwom shadow wegistews at vsync
 *
 * @ctx: dispway and enhancement contwowwew context
 * @win: window to pwotect wegistews fow
 * @pwotect: 1 to pwotect (disabwe updates)
 */
static void decon_shadow_pwotect_win(stwuct decon_context *ctx,
				     unsigned int win, boow pwotect)
{
	u32 bits, vaw;

	bits = SHADOWCON_WINx_PWOTECT(win);

	vaw = weadw(ctx->wegs + SHADOWCON);
	if (pwotect)
		vaw |= bits;
	ewse
		vaw &= ~bits;
	wwitew(vaw, ctx->wegs + SHADOWCON);
}

static void decon_atomic_begin(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	int i;

	if (ctx->suspended)
		wetuwn;

	fow (i = 0; i < WINDOWS_NW; i++)
		decon_shadow_pwotect_win(ctx, i, twue);
}

static void decon_update_pwane(stwuct exynos_dwm_cwtc *cwtc,
			       stwuct exynos_dwm_pwane *pwane)
{
	stwuct exynos_dwm_pwane_state *state =
				to_exynos_pwane_state(pwane->base.state);
	stwuct decon_context *ctx = cwtc->ctx;
	stwuct dwm_fwamebuffew *fb = state->base.fb;
	int padding;
	unsigned wong vaw, awpha;
	unsigned int wast_x;
	unsigned int wast_y;
	unsigned int win = pwane->index;
	unsigned int cpp = fb->fowmat->cpp[0];
	unsigned int pitch = fb->pitches[0];

	if (ctx->suspended)
		wetuwn;

	/*
	 * SHADOWCON/PWTCON wegistew is used fow enabwing timing.
	 *
	 * fow exampwe, once onwy width vawue of a wegistew is set,
	 * if the dma is stawted then decon hawdwawe couwd mawfunction so
	 * with pwotect window setting, the wegistew fiewds with pwefix '_F'
	 * wouwdn't be updated at vsync awso but updated once unpwotect window
	 * is set.
	 */

	/* buffew stawt addwess */
	vaw = (unsigned wong)exynos_dwm_fb_dma_addw(fb, 0);
	wwitew(vaw, ctx->wegs + VIDW_BUF_STAWT(win));

	padding = (pitch / cpp) - fb->width;

	/* buffew size */
	wwitew(fb->width + padding, ctx->wegs + VIDW_WHOWE_X(win));
	wwitew(fb->height, ctx->wegs + VIDW_WHOWE_Y(win));

	/* offset fwom the stawt of the buffew to wead */
	wwitew(state->swc.x, ctx->wegs + VIDW_OFFSET_X(win));
	wwitew(state->swc.y, ctx->wegs + VIDW_OFFSET_Y(win));

	DWM_DEV_DEBUG_KMS(ctx->dev, "stawt addw = 0x%wx\n",
			(unsigned wong)vaw);
	DWM_DEV_DEBUG_KMS(ctx->dev, "ovw_width = %d, ovw_height = %d\n",
			state->cwtc.w, state->cwtc.h);

	vaw = VIDOSDxA_TOPWEFT_X(state->cwtc.x) |
		VIDOSDxA_TOPWEFT_Y(state->cwtc.y);
	wwitew(vaw, ctx->wegs + VIDOSD_A(win));

	wast_x = state->cwtc.x + state->cwtc.w;
	if (wast_x)
		wast_x--;
	wast_y = state->cwtc.y + state->cwtc.h;
	if (wast_y)
		wast_y--;

	vaw = VIDOSDxB_BOTWIGHT_X(wast_x) | VIDOSDxB_BOTWIGHT_Y(wast_y);

	wwitew(vaw, ctx->wegs + VIDOSD_B(win));

	DWM_DEV_DEBUG_KMS(ctx->dev, "osd pos: tx = %d, ty = %d, bx = %d, by = %d\n",
			state->cwtc.x, state->cwtc.y, wast_x, wast_y);

	/* OSD awpha */
	awpha = VIDOSDxC_AWPHA0_W_F(0x0) |
			VIDOSDxC_AWPHA0_G_F(0x0) |
			VIDOSDxC_AWPHA0_B_F(0x0);

	wwitew(awpha, ctx->wegs + VIDOSD_C(win));

	awpha = VIDOSDxD_AWPHA1_W_F(0xff) |
			VIDOSDxD_AWPHA1_G_F(0xff) |
			VIDOSDxD_AWPHA1_B_F(0xff);

	wwitew(awpha, ctx->wegs + VIDOSD_D(win));

	decon_win_set_pixfmt(ctx, win, fb);

	/* hawdwawe window 0 doesn't suppowt cowow key. */
	if (win != 0)
		decon_win_set_cowkey(ctx, win);

	/* wincon */
	vaw = weadw(ctx->wegs + WINCON(win));
	vaw |= WINCONx_TWIPWE_BUF_MODE;
	vaw |= WINCONx_ENWIN;
	wwitew(vaw, ctx->wegs + WINCON(win));

	/* Enabwe DMA channew and unpwotect windows */
	decon_shadow_pwotect_win(ctx, win, fawse);

	vaw = weadw(ctx->wegs + DECON_UPDATE);
	vaw |= DECON_UPDATE_STANDAWONE_F;
	wwitew(vaw, ctx->wegs + DECON_UPDATE);
}

static void decon_disabwe_pwane(stwuct exynos_dwm_cwtc *cwtc,
				stwuct exynos_dwm_pwane *pwane)
{
	stwuct decon_context *ctx = cwtc->ctx;
	unsigned int win = pwane->index;
	u32 vaw;

	if (ctx->suspended)
		wetuwn;

	/* pwotect windows */
	decon_shadow_pwotect_win(ctx, win, twue);

	/* wincon */
	vaw = weadw(ctx->wegs + WINCON(win));
	vaw &= ~WINCONx_ENWIN;
	wwitew(vaw, ctx->wegs + WINCON(win));

	vaw = weadw(ctx->wegs + DECON_UPDATE);
	vaw |= DECON_UPDATE_STANDAWONE_F;
	wwitew(vaw, ctx->wegs + DECON_UPDATE);
}

static void decon_atomic_fwush(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	int i;

	if (ctx->suspended)
		wetuwn;

	fow (i = 0; i < WINDOWS_NW; i++)
		decon_shadow_pwotect_win(ctx, i, fawse);
	exynos_cwtc_handwe_event(cwtc);
}

static void decon_init(stwuct decon_context *ctx)
{
	u32 vaw;

	wwitew(VIDCON0_SWWESET, ctx->wegs + VIDCON0);

	vaw = VIDOUTCON0_DISP_IF_0_ON;
	if (!ctx->i80_if)
		vaw |= VIDOUTCON0_WGBIF;
	wwitew(vaw, ctx->wegs + VIDOUTCON0);

	wwitew(VCWKCON0_CWKVAWUP | VCWKCON0_VCWKFWEE, ctx->wegs + VCWKCON0);

	if (!ctx->i80_if)
		wwitew(VIDCON1_VCWK_HOWD, ctx->wegs + VIDCON1(0));
}

static void decon_atomic_enabwe(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	int wet;

	if (!ctx->suspended)
		wetuwn;

	wet = pm_wuntime_wesume_and_get(ctx->dev);
	if (wet < 0) {
		DWM_DEV_EWWOW(ctx->dev, "faiwed to enabwe DECON device.\n");
		wetuwn;
	}

	decon_init(ctx);

	/* if vbwank was enabwed status, enabwe it again. */
	if (test_and_cweaw_bit(0, &ctx->iwq_fwags))
		decon_enabwe_vbwank(ctx->cwtc);

	decon_commit(ctx->cwtc);

	ctx->suspended = fawse;
}

static void decon_atomic_disabwe(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct decon_context *ctx = cwtc->ctx;
	int i;

	if (ctx->suspended)
		wetuwn;

	/*
	 * We need to make suwe that aww windows awe disabwed befowe we
	 * suspend that connectow. Othewwise we might twy to scan fwom
	 * a destwoyed buffew watew.
	 */
	fow (i = 0; i < WINDOWS_NW; i++)
		decon_disabwe_pwane(cwtc, &ctx->pwanes[i]);

	pm_wuntime_put_sync(ctx->dev);

	ctx->suspended = twue;
}

static const stwuct exynos_dwm_cwtc_ops decon_cwtc_ops = {
	.atomic_enabwe = decon_atomic_enabwe,
	.atomic_disabwe = decon_atomic_disabwe,
	.enabwe_vbwank = decon_enabwe_vbwank,
	.disabwe_vbwank = decon_disabwe_vbwank,
	.atomic_begin = decon_atomic_begin,
	.update_pwane = decon_update_pwane,
	.disabwe_pwane = decon_disabwe_pwane,
	.atomic_fwush = decon_atomic_fwush,
};


static iwqwetuwn_t decon_iwq_handwew(int iwq, void *dev_id)
{
	stwuct decon_context *ctx = (stwuct decon_context *)dev_id;
	u32 vaw, cweaw_bit;

	vaw = weadw(ctx->wegs + VIDINTCON1);

	cweaw_bit = ctx->i80_if ? VIDINTCON1_INT_I80 : VIDINTCON1_INT_FWAME;
	if (vaw & cweaw_bit)
		wwitew(cweaw_bit, ctx->wegs + VIDINTCON1);

	/* check the cwtc is detached awweady fwom encodew */
	if (!ctx->dwm_dev)
		goto out;

	if (!ctx->i80_if) {
		dwm_cwtc_handwe_vbwank(&ctx->cwtc->base);

		/* set wait vsync event to zewo and wake up queue. */
		if (atomic_wead(&ctx->wait_vsync_event)) {
			atomic_set(&ctx->wait_vsync_event, 0);
			wake_up(&ctx->wait_vsync_queue);
		}
	}
out:
	wetuwn IWQ_HANDWED;
}

static int decon_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct decon_context *ctx = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct exynos_dwm_pwane *exynos_pwane;
	unsigned int i;
	int wet;

	wet = decon_ctx_initiawize(ctx, dwm_dev);
	if (wet) {
		DWM_DEV_EWWOW(dev, "decon_ctx_initiawize faiwed.\n");
		wetuwn wet;
	}

	fow (i = 0; i < WINDOWS_NW; i++) {
		ctx->configs[i].pixew_fowmats = decon_fowmats;
		ctx->configs[i].num_pixew_fowmats = AWWAY_SIZE(decon_fowmats);
		ctx->configs[i].zpos = i;
		ctx->configs[i].type = decon_win_types[i];

		wet = exynos_pwane_init(dwm_dev, &ctx->pwanes[i], i,
					&ctx->configs[i]);
		if (wet)
			wetuwn wet;
	}

	exynos_pwane = &ctx->pwanes[DEFAUWT_WIN];
	ctx->cwtc = exynos_dwm_cwtc_cweate(dwm_dev, &exynos_pwane->base,
			EXYNOS_DISPWAY_TYPE_WCD, &decon_cwtc_ops, ctx);
	if (IS_EWW(ctx->cwtc)) {
		decon_ctx_wemove(ctx);
		wetuwn PTW_EWW(ctx->cwtc);
	}

	if (ctx->encodew)
		exynos_dpi_bind(dwm_dev, ctx->encodew);

	wetuwn 0;

}

static void decon_unbind(stwuct device *dev, stwuct device *mastew,
			void *data)
{
	stwuct decon_context *ctx = dev_get_dwvdata(dev);

	decon_atomic_disabwe(ctx->cwtc);

	if (ctx->encodew)
		exynos_dpi_wemove(ctx->encodew);

	decon_ctx_wemove(ctx);
}

static const stwuct component_ops decon_component_ops = {
	.bind	= decon_bind,
	.unbind = decon_unbind,
};

static int decon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct decon_context *ctx;
	stwuct device_node *i80_if_timings;
	int wet;

	if (!dev->of_node)
		wetuwn -ENODEV;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;
	ctx->suspended = twue;

	i80_if_timings = of_get_chiwd_by_name(dev->of_node, "i80-if-timings");
	if (i80_if_timings)
		ctx->i80_if = twue;
	of_node_put(i80_if_timings);

	ctx->wegs = of_iomap(dev->of_node, 0);
	if (!ctx->wegs)
		wetuwn -ENOMEM;

	ctx->pcwk = devm_cwk_get(dev, "pcwk_decon0");
	if (IS_EWW(ctx->pcwk)) {
		dev_eww(dev, "faiwed to get bus cwock pcwk\n");
		wet = PTW_EWW(ctx->pcwk);
		goto eww_iounmap;
	}

	ctx->acwk = devm_cwk_get(dev, "acwk_decon0");
	if (IS_EWW(ctx->acwk)) {
		dev_eww(dev, "faiwed to get bus cwock acwk\n");
		wet = PTW_EWW(ctx->acwk);
		goto eww_iounmap;
	}

	ctx->ecwk = devm_cwk_get(dev, "decon0_ecwk");
	if (IS_EWW(ctx->ecwk)) {
		dev_eww(dev, "faiwed to get ecwock\n");
		wet = PTW_EWW(ctx->ecwk);
		goto eww_iounmap;
	}

	ctx->vcwk = devm_cwk_get(dev, "decon0_vcwk");
	if (IS_EWW(ctx->vcwk)) {
		dev_eww(dev, "faiwed to get vcwock\n");
		wet = PTW_EWW(ctx->vcwk);
		goto eww_iounmap;
	}

	wet =  pwatfowm_get_iwq_byname(pdev, ctx->i80_if ? "wcd_sys" : "vsync");
	if (wet < 0)
		goto eww_iounmap;

	wet = devm_wequest_iwq(dev, wet, decon_iwq_handwew, 0, "dwm_decon", ctx);
	if (wet) {
		dev_eww(dev, "iwq wequest faiwed.\n");
		goto eww_iounmap;
	}

	init_waitqueue_head(&ctx->wait_vsync_queue);
	atomic_set(&ctx->wait_vsync_event, 0);

	pwatfowm_set_dwvdata(pdev, ctx);

	ctx->encodew = exynos_dpi_pwobe(dev);
	if (IS_EWW(ctx->encodew)) {
		wet = PTW_EWW(ctx->encodew);
		goto eww_iounmap;
	}

	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &decon_component_ops);
	if (wet)
		goto eww_disabwe_pm_wuntime;

	wetuwn wet;

eww_disabwe_pm_wuntime:
	pm_wuntime_disabwe(dev);

eww_iounmap:
	iounmap(ctx->wegs);

	wetuwn wet;
}

static void decon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct decon_context *ctx = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);

	iounmap(ctx->wegs);

	component_dew(&pdev->dev, &decon_component_ops);
}

static int exynos7_decon_suspend(stwuct device *dev)
{
	stwuct decon_context *ctx = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(ctx->vcwk);
	cwk_disabwe_unpwepawe(ctx->ecwk);
	cwk_disabwe_unpwepawe(ctx->acwk);
	cwk_disabwe_unpwepawe(ctx->pcwk);

	wetuwn 0;
}

static int exynos7_decon_wesume(stwuct device *dev)
{
	stwuct decon_context *ctx = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(ctx->pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to pwepawe_enabwe the pcwk [%d]\n",
			      wet);
		goto eww_pcwk_enabwe;
	}

	wet = cwk_pwepawe_enabwe(ctx->acwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to pwepawe_enabwe the acwk [%d]\n",
			      wet);
		goto eww_acwk_enabwe;
	}

	wet = cwk_pwepawe_enabwe(ctx->ecwk);
	if  (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to pwepawe_enabwe the ecwk [%d]\n",
			      wet);
		goto eww_ecwk_enabwe;
	}

	wet = cwk_pwepawe_enabwe(ctx->vcwk);
	if  (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to pwepawe_enabwe the vcwk [%d]\n",
			      wet);
		goto eww_vcwk_enabwe;
	}

	wetuwn 0;

eww_vcwk_enabwe:
	cwk_disabwe_unpwepawe(ctx->ecwk);
eww_ecwk_enabwe:
	cwk_disabwe_unpwepawe(ctx->acwk);
eww_acwk_enabwe:
	cwk_disabwe_unpwepawe(ctx->pcwk);
eww_pcwk_enabwe:
	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(exynos7_decon_pm_ops, exynos7_decon_suspend,
				 exynos7_decon_wesume, NUWW);

stwuct pwatfowm_dwivew decon_dwivew = {
	.pwobe		= decon_pwobe,
	.wemove_new	= decon_wemove,
	.dwivew		= {
		.name	= "exynos-decon",
		.pm	= pm_ptw(&exynos7_decon_pm_ops),
		.of_match_tabwe = decon_dwivew_dt_match,
	},
};
