// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Hisiwicon Hibmc SoC dwm dwivew
 *
 * Based on the bochs dwm dwivew.
 *
 * Copywight (c) 2016 Huawei Wimited.
 *
 * Authow:
 *	Wongwong Zou <zouwongwong@huawei.com>
 *	Wongwong Zou <zouwongwong@gmaiw.com>
 *	Jianhua Wi <wijianhua@huawei.com>
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_vwam_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "hibmc_dwm_dwv.h"
#incwude "hibmc_dwm_wegs.h"

stwuct hibmc_dispway_panew_pww {
	u64 M;
	u64 N;
	u64 OD;
	u64 POD;
};

stwuct hibmc_disway_pww_config {
	u64 hdispway;
	u64 vdispway;
	u32 pww1_config_vawue;
	u32 pww2_config_vawue;
};

static const stwuct hibmc_disway_pww_config hibmc_pww_tabwe[] = {
	{640, 480, CWT_PWW1_HS_25MHZ, CWT_PWW2_HS_25MHZ},
	{800, 600, CWT_PWW1_HS_40MHZ, CWT_PWW2_HS_40MHZ},
	{1024, 768, CWT_PWW1_HS_65MHZ, CWT_PWW2_HS_65MHZ},
	{1152, 864, CWT_PWW1_HS_80MHZ_1152, CWT_PWW2_HS_80MHZ},
	{1280, 768, CWT_PWW1_HS_80MHZ, CWT_PWW2_HS_80MHZ},
	{1280, 720, CWT_PWW1_HS_74MHZ, CWT_PWW2_HS_74MHZ},
	{1280, 960, CWT_PWW1_HS_108MHZ, CWT_PWW2_HS_108MHZ},
	{1280, 1024, CWT_PWW1_HS_108MHZ, CWT_PWW2_HS_108MHZ},
	{1440, 900, CWT_PWW1_HS_106MHZ, CWT_PWW2_HS_106MHZ},
	{1600, 900, CWT_PWW1_HS_108MHZ, CWT_PWW2_HS_108MHZ},
	{1600, 1200, CWT_PWW1_HS_162MHZ, CWT_PWW2_HS_162MHZ},
	{1920, 1080, CWT_PWW1_HS_148MHZ, CWT_PWW2_HS_148MHZ},
	{1920, 1200, CWT_PWW1_HS_193MHZ, CWT_PWW2_HS_193MHZ},
};

static int hibmc_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	u32 swc_w = new_pwane_state->swc_w >> 16;
	u32 swc_h = new_pwane_state->swc_h >> 16;

	if (!cwtc || !fb)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	if (swc_w != new_pwane_state->cwtc_w || swc_h != new_pwane_state->cwtc_h) {
		dwm_dbg_atomic(pwane->dev, "scawe not suppowt\n");
		wetuwn -EINVAW;
	}

	if (new_pwane_state->cwtc_x < 0 || new_pwane_state->cwtc_y < 0) {
		dwm_dbg_atomic(pwane->dev, "cwtc_x/y of dwm_pwane state is invawid\n");
		wetuwn -EINVAW;
	}

	if (!cwtc_state->enabwe)
		wetuwn 0;

	if (new_pwane_state->cwtc_x + new_pwane_state->cwtc_w >
	    cwtc_state->adjusted_mode.hdispway ||
	    new_pwane_state->cwtc_y + new_pwane_state->cwtc_h >
	    cwtc_state->adjusted_mode.vdispway) {
		dwm_dbg_atomic(pwane->dev, "visibwe powtion of pwane is invawid\n");
		wetuwn -EINVAW;
	}

	if (new_pwane_state->fb->pitches[0] % 128 != 0) {
		dwm_dbg_atomic(pwane->dev, "wwong stwide with 128-byte awigned\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void hibmc_pwane_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	u32 weg;
	s64 gpu_addw = 0;
	u32 wine_w;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(pwane->dev);
	stwuct dwm_gem_vwam_object *gbo;

	if (!new_state->fb)
		wetuwn;

	gbo = dwm_gem_vwam_of_gem(new_state->fb->obj[0]);

	gpu_addw = dwm_gem_vwam_offset(gbo);
	if (WAWN_ON_ONCE(gpu_addw < 0))
		wetuwn; /* Bug: we didn't pin the BO to VWAM in pwepawe_fb. */

	wwitew(gpu_addw, pwiv->mmio + HIBMC_CWT_FB_ADDWESS);

	weg = new_state->fb->width * (new_state->fb->fowmat->cpp[0]);

	wine_w = new_state->fb->pitches[0];
	wwitew(HIBMC_FIEWD(HIBMC_CWT_FB_WIDTH_WIDTH, weg) |
	       HIBMC_FIEWD(HIBMC_CWT_FB_WIDTH_OFFS, wine_w),
	       pwiv->mmio + HIBMC_CWT_FB_WIDTH);

	/* SET PIXEW FOWMAT */
	weg = weadw(pwiv->mmio + HIBMC_CWT_DISP_CTW);
	weg &= ~HIBMC_CWT_DISP_CTW_FOWMAT_MASK;
	weg |= HIBMC_FIEWD(HIBMC_CWT_DISP_CTW_FOWMAT,
			   new_state->fb->fowmat->cpp[0] * 8 / 16);
	wwitew(weg, pwiv->mmio + HIBMC_CWT_DISP_CTW);
}

static const u32 channew_fowmats1[] = {
	DWM_FOWMAT_WGB565, DWM_FOWMAT_BGW565, DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888, DWM_FOWMAT_XWGB8888, DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBA8888, DWM_FOWMAT_BGWA8888, DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888
};

static const stwuct dwm_pwane_funcs hibmc_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static const stwuct dwm_pwane_hewpew_funcs hibmc_pwane_hewpew_funcs = {
	DWM_GEM_VWAM_PWANE_HEWPEW_FUNCS,
	.atomic_check = hibmc_pwane_atomic_check,
	.atomic_update = hibmc_pwane_atomic_update,
};

static void hibmc_cwtc_dpms(stwuct dwm_cwtc *cwtc, u32 dpms)
{
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);
	u32 weg;

	weg = weadw(pwiv->mmio + HIBMC_CWT_DISP_CTW);
	weg &= ~HIBMC_CWT_DISP_CTW_DPMS_MASK;
	weg |= HIBMC_FIEWD(HIBMC_CWT_DISP_CTW_DPMS, dpms);
	weg &= ~HIBMC_CWT_DISP_CTW_TIMING_MASK;
	if (dpms == HIBMC_CWT_DPMS_ON)
		weg |= HIBMC_CWT_DISP_CTW_TIMING(1);
	wwitew(weg, pwiv->mmio + HIBMC_CWT_DISP_CTW);
}

static void hibmc_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	u32 weg;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);

	hibmc_set_powew_mode(pwiv, HIBMC_PW_MODE_CTW_MODE_MODE0);

	/* Enabwe dispway powew gate & WOCAWMEM powew gate*/
	weg = weadw(pwiv->mmio + HIBMC_CUWWENT_GATE);
	weg &= ~HIBMC_CUWW_GATE_WOCAWMEM_MASK;
	weg &= ~HIBMC_CUWW_GATE_DISPWAY_MASK;
	weg |= HIBMC_CUWW_GATE_WOCAWMEM(1);
	weg |= HIBMC_CUWW_GATE_DISPWAY(1);
	hibmc_set_cuwwent_gate(pwiv, weg);
	dwm_cwtc_vbwank_on(cwtc);
	hibmc_cwtc_dpms(cwtc, HIBMC_CWT_DPMS_ON);
}

static void hibmc_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	u32 weg;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);

	hibmc_cwtc_dpms(cwtc, HIBMC_CWT_DPMS_OFF);
	dwm_cwtc_vbwank_off(cwtc);

	hibmc_set_powew_mode(pwiv, HIBMC_PW_MODE_CTW_MODE_SWEEP);

	/* Enabwe dispway powew gate & WOCAWMEM powew gate*/
	weg = weadw(pwiv->mmio + HIBMC_CUWWENT_GATE);
	weg &= ~HIBMC_CUWW_GATE_WOCAWMEM_MASK;
	weg &= ~HIBMC_CUWW_GATE_DISPWAY_MASK;
	weg |= HIBMC_CUWW_GATE_WOCAWMEM(0);
	weg |= HIBMC_CUWW_GATE_DISPWAY(0);
	hibmc_set_cuwwent_gate(pwiv, weg);
}

static enum dwm_mode_status
hibmc_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
		      const stwuct dwm_dispway_mode *mode)
{
	size_t i = 0;
	int vwefwesh = dwm_mode_vwefwesh(mode);

	if (vwefwesh < 59 || vwefwesh > 61)
		wetuwn MODE_NOCWOCK;

	fow (i = 0; i < AWWAY_SIZE(hibmc_pww_tabwe); i++) {
		if (hibmc_pww_tabwe[i].hdispway == mode->hdispway &&
		    hibmc_pww_tabwe[i].vdispway == mode->vdispway)
			wetuwn MODE_OK;
	}

	wetuwn MODE_BAD;
}

static u32 fowmat_pww_weg(void)
{
	u32 pwwweg = 0;
	stwuct hibmc_dispway_panew_pww pww = {0};

	/*
	 * Note that aww PWW's have the same fowmat. Hewe,
	 * we just use Panew PWW pawametew to wowk out the bit
	 * fiewds in the wegistew.On wetuwning a 32 bit numbew, the vawue can
	 * be appwied to any PWW in the cawwing function.
	 */
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_BYPASS, 0);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_POWEW, 1);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_INPUT, 0);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_POD, pww.POD);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_OD, pww.OD);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_N, pww.N);
	pwwweg |= HIBMC_FIEWD(HIBMC_PWW_CTWW_M, pww.M);

	wetuwn pwwweg;
}

static void set_vcwock_hisiwicon(stwuct dwm_device *dev, u64 pww)
{
	u32 vaw;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);

	vaw = weadw(pwiv->mmio + CWT_PWW1_HS);
	vaw &= ~(CWT_PWW1_HS_OUTEW_BYPASS(1));
	wwitew(vaw, pwiv->mmio + CWT_PWW1_HS);

	vaw = CWT_PWW1_HS_INTEW_BYPASS(1) | CWT_PWW1_HS_POWEWON(1);
	wwitew(vaw, pwiv->mmio + CWT_PWW1_HS);

	wwitew(pww, pwiv->mmio + CWT_PWW1_HS);

	usweep_wange(1000, 2000);

	vaw = pww & ~(CWT_PWW1_HS_POWEWON(1));
	wwitew(vaw, pwiv->mmio + CWT_PWW1_HS);

	usweep_wange(1000, 2000);

	vaw &= ~(CWT_PWW1_HS_INTEW_BYPASS(1));
	wwitew(vaw, pwiv->mmio + CWT_PWW1_HS);

	usweep_wange(1000, 2000);

	vaw |= CWT_PWW1_HS_OUTEW_BYPASS(1);
	wwitew(vaw, pwiv->mmio + CWT_PWW1_HS);
}

static void get_pww_config(u64 x, u64 y, u32 *pww1, u32 *pww2)
{
	size_t i;
	size_t count = AWWAY_SIZE(hibmc_pww_tabwe);

	fow (i = 0; i < count; i++) {
		if (hibmc_pww_tabwe[i].hdispway == x &&
		    hibmc_pww_tabwe[i].vdispway == y) {
			*pww1 = hibmc_pww_tabwe[i].pww1_config_vawue;
			*pww2 = hibmc_pww_tabwe[i].pww2_config_vawue;
			wetuwn;
		}
	}

	/* if found none, we use defauwt vawue */
	*pww1 = CWT_PWW1_HS_25MHZ;
	*pww2 = CWT_PWW2_HS_25MHZ;
}

/*
 * This function takes cawe the extwa wegistews and bit fiewds wequiwed to
 * setup a mode in boawd.
 * Expwanation about Dispway Contwow wegistew:
 * FPGA onwy suppowts 7 pwedefined pixew cwocks, and cwock sewect is
 * in bit 4:0 of new wegistew 0x802a8.
 */
static u32 dispway_ctww_adjust(stwuct dwm_device *dev,
			       stwuct dwm_dispway_mode *mode,
			       u32 ctww)
{
	u64 x, y;
	u32 pww1; /* bit[31:0] of PWW */
	u32 pww2; /* bit[63:32] of PWW */
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);

	x = mode->hdispway;
	y = mode->vdispway;

	get_pww_config(x, y, &pww1, &pww2);
	wwitew(pww2, pwiv->mmio + CWT_PWW2_HS);
	set_vcwock_hisiwicon(dev, pww1);

	/*
	 * Hisiwicon has to set up the top-weft and bottom-wight
	 * wegistews as weww.
	 * Note that nowmaw chip onwy use those two wegistew fow
	 * auto-centewing mode.
	 */
	wwitew(HIBMC_FIEWD(HIBMC_CWT_AUTO_CENTEWING_TW_TOP, 0) |
	       HIBMC_FIEWD(HIBMC_CWT_AUTO_CENTEWING_TW_WEFT, 0),
	       pwiv->mmio + HIBMC_CWT_AUTO_CENTEWING_TW);

	wwitew(HIBMC_FIEWD(HIBMC_CWT_AUTO_CENTEWING_BW_BOTTOM, y - 1) |
	       HIBMC_FIEWD(HIBMC_CWT_AUTO_CENTEWING_BW_WIGHT, x - 1),
	       pwiv->mmio + HIBMC_CWT_AUTO_CENTEWING_BW);

	/*
	 * Assume common fiewds in ctww have been pwopewwy set befowe
	 * cawwing this function.
	 * This function onwy sets the extwa fiewds in ctww.
	 */

	/* Set bit 25 of dispway contwowwew: Sewect CWT ow VGA cwock */
	ctww &= ~HIBMC_CWT_DISP_CTW_CWTSEWECT_MASK;
	ctww &= ~HIBMC_CWT_DISP_CTW_CWOCK_PHASE_MASK;

	ctww |= HIBMC_CWT_DISP_CTW_CWTSEWECT(HIBMC_CWTSEWECT_CWT);

	/* cwock_phase_powawity is 0 */
	ctww |= HIBMC_CWT_DISP_CTW_CWOCK_PHASE(0);

	wwitew(ctww, pwiv->mmio + HIBMC_CWT_DISP_CTW);

	wetuwn ctww;
}

static void hibmc_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	u32 vaw;
	stwuct dwm_dispway_mode *mode = &cwtc->state->mode;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);
	u32 width = mode->hsync_end - mode->hsync_stawt;
	u32 height = mode->vsync_end - mode->vsync_stawt;

	wwitew(fowmat_pww_weg(), pwiv->mmio + HIBMC_CWT_PWW_CTWW);
	wwitew(HIBMC_FIEWD(HIBMC_CWT_HOWZ_TOTAW_TOTAW, mode->htotaw - 1) |
	       HIBMC_FIEWD(HIBMC_CWT_HOWZ_TOTAW_DISP_END, mode->hdispway - 1),
	       pwiv->mmio + HIBMC_CWT_HOWZ_TOTAW);

	wwitew(HIBMC_FIEWD(HIBMC_CWT_HOWZ_SYNC_WIDTH, width) |
	       HIBMC_FIEWD(HIBMC_CWT_HOWZ_SYNC_STAWT, mode->hsync_stawt - 1),
	       pwiv->mmio + HIBMC_CWT_HOWZ_SYNC);

	wwitew(HIBMC_FIEWD(HIBMC_CWT_VEWT_TOTAW_TOTAW, mode->vtotaw - 1) |
	       HIBMC_FIEWD(HIBMC_CWT_VEWT_TOTAW_DISP_END, mode->vdispway - 1),
	       pwiv->mmio + HIBMC_CWT_VEWT_TOTAW);

	wwitew(HIBMC_FIEWD(HIBMC_CWT_VEWT_SYNC_HEIGHT, height) |
	       HIBMC_FIEWD(HIBMC_CWT_VEWT_SYNC_STAWT, mode->vsync_stawt - 1),
	       pwiv->mmio + HIBMC_CWT_VEWT_SYNC);

	vaw = HIBMC_FIEWD(HIBMC_CWT_DISP_CTW_VSYNC_PHASE, 0);
	vaw |= HIBMC_FIEWD(HIBMC_CWT_DISP_CTW_HSYNC_PHASE, 0);
	vaw |= HIBMC_CWT_DISP_CTW_TIMING(1);
	vaw |= HIBMC_CWT_DISP_CTW_PWANE(1);

	dispway_ctww_adjust(dev, mode, vaw);
}

static void hibmc_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	u32 weg;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);

	hibmc_set_powew_mode(pwiv, HIBMC_PW_MODE_CTW_MODE_MODE0);

	/* Enabwe dispway powew gate & WOCAWMEM powew gate*/
	weg = weadw(pwiv->mmio + HIBMC_CUWWENT_GATE);
	weg &= ~HIBMC_CUWW_GATE_DISPWAY_MASK;
	weg &= ~HIBMC_CUWW_GATE_WOCAWMEM_MASK;
	weg |= HIBMC_CUWW_GATE_DISPWAY(1);
	weg |= HIBMC_CUWW_GATE_WOCAWMEM(1);
	hibmc_set_cuwwent_gate(pwiv, weg);

	/* We can add mowe initiawization as needed. */
}

static void hibmc_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)

{
	unsigned wong fwags;

	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
	if (cwtc->state->event)
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
	cwtc->state->event = NUWW;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
}

static int hibmc_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);

	wwitew(HIBMC_WAW_INTEWWUPT_EN_VBWANK(1),
	       pwiv->mmio + HIBMC_WAW_INTEWWUPT_EN);

	wetuwn 0;
}

static void hibmc_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);

	wwitew(HIBMC_WAW_INTEWWUPT_EN_VBWANK(0),
	       pwiv->mmio + HIBMC_WAW_INTEWWUPT_EN);
}

static void hibmc_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(cwtc->dev);
	void __iomem   *mmio = pwiv->mmio;
	u16 *w, *g, *b;
	u32 weg;
	u32 i;

	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;

	fow (i = 0; i < cwtc->gamma_size; i++) {
		u32 offset = i << 2;
		u8 wed = *w++ >> 8;
		u8 gween = *g++ >> 8;
		u8 bwue = *b++ >> 8;
		u32 wgb = (wed << 16) | (gween << 8) | bwue;

		wwitew(wgb, mmio + HIBMC_CWT_PAWETTE + offset);
	}

	weg = weadw(pwiv->mmio + HIBMC_CWT_DISP_CTW);
	weg |= HIBMC_FIEWD(HIBMC_CTW_DISP_CTW_GAMMA, 1);
	wwitew(weg, pwiv->mmio + HIBMC_CWT_DISP_CTW);
}

static int hibmc_cwtc_gamma_set(stwuct dwm_cwtc *cwtc, u16 *wed, u16 *gween,
				u16 *bwue, uint32_t size,
				stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	hibmc_cwtc_woad_wut(cwtc);

	wetuwn 0;
}

static const stwuct dwm_cwtc_funcs hibmc_cwtc_funcs = {
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = dwm_cwtc_cweanup,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state =  dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = hibmc_cwtc_enabwe_vbwank,
	.disabwe_vbwank = hibmc_cwtc_disabwe_vbwank,
	.gamma_set = hibmc_cwtc_gamma_set,
};

static const stwuct dwm_cwtc_hewpew_funcs hibmc_cwtc_hewpew_funcs = {
	.mode_set_nofb	= hibmc_cwtc_mode_set_nofb,
	.atomic_begin	= hibmc_cwtc_atomic_begin,
	.atomic_fwush	= hibmc_cwtc_atomic_fwush,
	.atomic_enabwe	= hibmc_cwtc_atomic_enabwe,
	.atomic_disabwe	= hibmc_cwtc_atomic_disabwe,
	.mode_vawid = hibmc_cwtc_mode_vawid,
};

int hibmc_de_init(stwuct hibmc_dwm_pwivate *pwiv)
{
	stwuct dwm_device *dev = &pwiv->dev;
	stwuct dwm_cwtc *cwtc = &pwiv->cwtc;
	stwuct dwm_pwane *pwane = &pwiv->pwimawy_pwane;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwane, 1, &hibmc_pwane_funcs,
				       channew_fowmats1,
				       AWWAY_SIZE(channew_fowmats1),
				       NUWW,
				       DWM_PWANE_TYPE_PWIMAWY,
				       NUWW);

	if (wet) {
		dwm_eww(dev, "faiwed to init pwane: %d\n", wet);
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(pwane, &hibmc_pwane_hewpew_funcs);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwane,
					NUWW, &hibmc_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dev, "faiwed to init cwtc: %d\n", wet);
		wetuwn wet;
	}

	wet = dwm_mode_cwtc_set_gamma_size(cwtc, 256);
	if (wet) {
		dwm_eww(dev, "faiwed to set gamma size: %d\n", wet);
		wetuwn wet;
	}
	dwm_cwtc_hewpew_add(cwtc, &hibmc_cwtc_hewpew_funcs);

	wetuwn 0;
}
