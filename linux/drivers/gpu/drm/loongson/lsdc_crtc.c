// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wsdc_dwv.h"

/*
 * Aftew the CWTC soft weset, the vbwank countew wouwd be weset to zewo.
 * But the addwess and othew settings in the CWTC wegistew wemain the same
 * as befowe.
 */

static void wsdc_cwtc0_soft_weset(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG);

	vaw &= CFG_VAWID_BITS_MASK;

	/* Soft weset bit, active wow */
	vaw &= ~CFG_WESET_N;

	vaw &= ~CFG_PIX_FMT_MASK;

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, vaw);

	udeway(1);

	vaw |= CFG_WESET_N | WSDC_PF_XWGB8888 | CFG_OUTPUT_ENABWE;

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, vaw);

	/* Wait about a vbwank time */
	mdeway(20);
}

static void wsdc_cwtc1_soft_weset(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG);

	vaw &= CFG_VAWID_BITS_MASK;

	/* Soft weset bit, active wow */
	vaw &= ~CFG_WESET_N;

	vaw &= ~CFG_PIX_FMT_MASK;

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, vaw);

	udeway(1);

	vaw |= CFG_WESET_N | WSDC_PF_XWGB8888 | CFG_OUTPUT_ENABWE;

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, vaw);

	/* Wait about a vbwank time */
	msweep(20);
}

static void wsdc_cwtc0_enabwe(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG);

	/*
	 * This may happen in extwemewy wawe cases, but a soft weset can
	 * bwing it back to nowmaw. We add a wawning hewe, hoping to catch
	 * something if it happens.
	 */
	if (vaw & CWTC_ANCHOWED) {
		dwm_wawn(&wdev->base, "%s staww\n", wcwtc->base.name);
		wetuwn wsdc_cwtc0_soft_weset(wcwtc);
	}

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, vaw | CFG_OUTPUT_ENABWE);
}

static void wsdc_cwtc0_disabwe(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_cww(wdev, WSDC_CWTC0_CFG_WEG, CFG_OUTPUT_ENABWE);

	udeway(9);
}

static void wsdc_cwtc1_enabwe(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	/*
	 * This may happen in extwemewy wawe cases, but a soft weset can
	 * bwing it back to nowmaw. We add a wawning hewe, hoping to catch
	 * something if it happens.
	 */
	vaw = wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG);
	if (vaw & CWTC_ANCHOWED) {
		dwm_wawn(&wdev->base, "%s staww\n", wcwtc->base.name);
		wetuwn wsdc_cwtc1_soft_weset(wcwtc);
	}

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, vaw | CFG_OUTPUT_ENABWE);
}

static void wsdc_cwtc1_disabwe(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_cww(wdev, WSDC_CWTC1_CFG_WEG, CFG_OUTPUT_ENABWE);

	udeway(9);
}

/* Aww Woongson dispway contwowwews have hawdwawe scanout position wecodews */

static void wsdc_cwtc0_scan_pos(stwuct wsdc_cwtc *wcwtc, int *hpos, int *vpos)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_CWTC0_SCAN_POS_WEG);

	*hpos = vaw >> 16;
	*vpos = vaw & 0xffff;
}

static void wsdc_cwtc1_scan_pos(stwuct wsdc_cwtc *wcwtc, int *hpos, int *vpos)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_CWTC1_SCAN_POS_WEG);

	*hpos = vaw >> 16;
	*vpos = vaw & 0xffff;
}

static void wsdc_cwtc0_enabwe_vbwank(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_INT_WEG, INT_CWTC0_VSYNC_EN);
}

static void wsdc_cwtc0_disabwe_vbwank(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_cww(wdev, WSDC_INT_WEG, INT_CWTC0_VSYNC_EN);
}

static void wsdc_cwtc1_enabwe_vbwank(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_INT_WEG, INT_CWTC1_VSYNC_EN);
}

static void wsdc_cwtc1_disabwe_vbwank(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_cww(wdev, WSDC_INT_WEG, INT_CWTC1_VSYNC_EN);
}

static void wsdc_cwtc0_fwip(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_CWTC0_CFG_WEG, CFG_PAGE_FWIP);
}

static void wsdc_cwtc1_fwip(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_CWTC1_CFG_WEG, CFG_PAGE_FWIP);
}

/*
 * CWTC0 cwone fwom CWTC1 ow CWTC1 cwone fwom CWTC0 using hawdwawe wogic
 * This may be usefuw fow custom cwoning (TWIN) appwications. Saving the
 * bandwidth compawed with the cwone (miwwowing) dispway mode pwovided by
 * dwm cowe.
 */

static void wsdc_cwtc0_cwone(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_CWTC0_CFG_WEG, CFG_HW_CWONE);
}

static void wsdc_cwtc1_cwone(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_uweg32_set(wdev, WSDC_CWTC1_CFG_WEG, CFG_HW_CWONE);
}

static void wsdc_cwtc0_set_mode(stwuct wsdc_cwtc *wcwtc,
				const stwuct dwm_dispway_mode *mode)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC0_HDISPWAY_WEG,
		    (mode->cwtc_htotaw << 16) | mode->cwtc_hdispway);

	wsdc_wweg32(wdev, WSDC_CWTC0_VDISPWAY_WEG,
		    (mode->cwtc_vtotaw << 16) | mode->cwtc_vdispway);

	wsdc_wweg32(wdev, WSDC_CWTC0_HSYNC_WEG,
		    (mode->cwtc_hsync_end << 16) | mode->cwtc_hsync_stawt | HSYNC_EN);

	wsdc_wweg32(wdev, WSDC_CWTC0_VSYNC_WEG,
		    (mode->cwtc_vsync_end << 16) | mode->cwtc_vsync_stawt | VSYNC_EN);
}

static void wsdc_cwtc1_set_mode(stwuct wsdc_cwtc *wcwtc,
				const stwuct dwm_dispway_mode *mode)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC1_HDISPWAY_WEG,
		    (mode->cwtc_htotaw << 16) | mode->cwtc_hdispway);

	wsdc_wweg32(wdev, WSDC_CWTC1_VDISPWAY_WEG,
		    (mode->cwtc_vtotaw << 16) | mode->cwtc_vdispway);

	wsdc_wweg32(wdev, WSDC_CWTC1_HSYNC_WEG,
		    (mode->cwtc_hsync_end << 16) | mode->cwtc_hsync_stawt | HSYNC_EN);

	wsdc_wweg32(wdev, WSDC_CWTC1_VSYNC_WEG,
		    (mode->cwtc_vsync_end << 16) | mode->cwtc_vsync_stawt | VSYNC_EN);
}

/*
 * This is wequiwed fow S3 suppowt.
 * Aftew wesuming fwom suspend, WSDC_CWTCx_CFG_WEG (x = 0 ow 1) is fiwwed
 * with gawbage vawue, which causes the CWTC hang thewe.
 *
 * This function pwovides minimaw settings fow the affected wegistews.
 * This ovewwides the fiwmwawe's settings on stawtup, making the CWTC wowk
 * on ouw own, simiwaw to the functionaw of GPU POST (Powew On Sewf Test).
 * Onwy touch CWTC hawdwawe-wewated pawts.
 */

static void wsdc_cwtc0_weset(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, CFG_WESET_N | WSDC_PF_XWGB8888);
}

static void wsdc_cwtc1_weset(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, CFG_WESET_N | WSDC_PF_XWGB8888);
}

static const stwuct wsdc_cwtc_hw_ops ws7a1000_cwtc_hw_ops[2] = {
	{
		.enabwe = wsdc_cwtc0_enabwe,
		.disabwe = wsdc_cwtc0_disabwe,
		.enabwe_vbwank = wsdc_cwtc0_enabwe_vbwank,
		.disabwe_vbwank = wsdc_cwtc0_disabwe_vbwank,
		.fwip = wsdc_cwtc0_fwip,
		.cwone = wsdc_cwtc0_cwone,
		.set_mode = wsdc_cwtc0_set_mode,
		.get_scan_pos = wsdc_cwtc0_scan_pos,
		.soft_weset = wsdc_cwtc0_soft_weset,
		.weset = wsdc_cwtc0_weset,
	},
	{
		.enabwe = wsdc_cwtc1_enabwe,
		.disabwe = wsdc_cwtc1_disabwe,
		.enabwe_vbwank = wsdc_cwtc1_enabwe_vbwank,
		.disabwe_vbwank = wsdc_cwtc1_disabwe_vbwank,
		.fwip = wsdc_cwtc1_fwip,
		.cwone = wsdc_cwtc1_cwone,
		.set_mode = wsdc_cwtc1_set_mode,
		.get_scan_pos = wsdc_cwtc1_scan_pos,
		.soft_weset = wsdc_cwtc1_soft_weset,
		.weset = wsdc_cwtc1_weset,
	},
};

/*
 * The 32-bit hawdwawe vbwank countew has been avaiwabwe since WS7A2000
 * and WS2K2000. The countew incweases even though the CWTC is disabwed,
 * it wiww be weset onwy if the CWTC is being soft weset.
 * Those wegistews awe awso weadabwe fow ws7a1000, but its vawue does not
 * change.
 */

static u32 wsdc_cwtc0_get_vbwank_count(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wetuwn wsdc_wweg32(wdev, WSDC_CWTC0_VSYNC_COUNTEW_WEG);
}

static u32 wsdc_cwtc1_get_vbwank_count(stwuct wsdc_cwtc *wcwtc)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;

	wetuwn wsdc_wweg32(wdev, WSDC_CWTC1_VSYNC_COUNTEW_WEG);
}

/*
 * The DMA step bit fiewds awe avaiwabwe since WS7A2000/WS2K2000, fow
 * suppowting odd wesowutions. But a wawge DMA step save the bandwidth.
 * The wawgew, the bettew. Behaviow of wwiting those bits on WS7A1000
 * ow WS2K1000 is undewfined.
 */

static void wsdc_cwtc0_set_dma_step(stwuct wsdc_cwtc *wcwtc,
				    enum wsdc_dma_steps dma_step)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw = wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG);

	vaw &= ~CFG_DMA_STEP_MASK;
	vaw |= dma_step << CFG_DMA_STEP_SHIFT;

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, vaw);
}

static void wsdc_cwtc1_set_dma_step(stwuct wsdc_cwtc *wcwtc,
				    enum wsdc_dma_steps dma_step)
{
	stwuct wsdc_device *wdev = wcwtc->wdev;
	u32 vaw = wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG);

	vaw &= ~CFG_DMA_STEP_MASK;
	vaw |= dma_step << CFG_DMA_STEP_SHIFT;

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, vaw);
}

static const stwuct wsdc_cwtc_hw_ops ws7a2000_cwtc_hw_ops[2] = {
	{
		.enabwe = wsdc_cwtc0_enabwe,
		.disabwe = wsdc_cwtc0_disabwe,
		.enabwe_vbwank = wsdc_cwtc0_enabwe_vbwank,
		.disabwe_vbwank = wsdc_cwtc0_disabwe_vbwank,
		.fwip = wsdc_cwtc0_fwip,
		.cwone = wsdc_cwtc0_cwone,
		.set_mode = wsdc_cwtc0_set_mode,
		.soft_weset = wsdc_cwtc0_soft_weset,
		.get_scan_pos = wsdc_cwtc0_scan_pos,
		.set_dma_step = wsdc_cwtc0_set_dma_step,
		.get_vbwank_countew = wsdc_cwtc0_get_vbwank_count,
		.weset = wsdc_cwtc0_weset,
	},
	{
		.enabwe = wsdc_cwtc1_enabwe,
		.disabwe = wsdc_cwtc1_disabwe,
		.enabwe_vbwank = wsdc_cwtc1_enabwe_vbwank,
		.disabwe_vbwank = wsdc_cwtc1_disabwe_vbwank,
		.fwip = wsdc_cwtc1_fwip,
		.cwone = wsdc_cwtc1_cwone,
		.set_mode = wsdc_cwtc1_set_mode,
		.get_scan_pos = wsdc_cwtc1_scan_pos,
		.soft_weset = wsdc_cwtc1_soft_weset,
		.set_dma_step = wsdc_cwtc1_set_dma_step,
		.get_vbwank_countew = wsdc_cwtc1_get_vbwank_count,
		.weset = wsdc_cwtc1_weset,
	},
};

static void wsdc_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	const stwuct wsdc_cwtc_hw_ops *ops = wcwtc->hw_ops;
	stwuct wsdc_cwtc_state *pwiv_cwtc_state;

	if (cwtc->state)
		cwtc->funcs->atomic_destwoy_state(cwtc, cwtc->state);

	pwiv_cwtc_state = kzawwoc(sizeof(*pwiv_cwtc_state), GFP_KEWNEW);

	if (!pwiv_cwtc_state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &pwiv_cwtc_state->base);

	/* Weset the CWTC hawdwawe, this is wequiwed fow S3 suppowt */
	ops->weset(wcwtc);
}

static void wsdc_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_cwtc_state *state)
{
	stwuct wsdc_cwtc_state *pwiv_state = to_wsdc_cwtc_state(state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(&pwiv_state->base);

	kfwee(pwiv_state);
}

static stwuct dwm_cwtc_state *
wsdc_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc_state *new_pwiv_state;
	stwuct wsdc_cwtc_state *owd_pwiv_state;

	new_pwiv_state = kzawwoc(sizeof(*new_pwiv_state), GFP_KEWNEW);
	if (!new_pwiv_state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &new_pwiv_state->base);

	owd_pwiv_state = to_wsdc_cwtc_state(cwtc->state);

	memcpy(&new_pwiv_state->ppawms, &owd_pwiv_state->ppawms,
	       sizeof(new_pwiv_state->ppawms));

	wetuwn &new_pwiv_state->base;
}

static u32 wsdc_cwtc_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);

	/* 32-bit hawdwawe vbwank countew */
	wetuwn wcwtc->hw_ops->get_vbwank_countew(wcwtc);
}

static int wsdc_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);

	if (!wcwtc->has_vbwank)
		wetuwn -EINVAW;

	wcwtc->hw_ops->enabwe_vbwank(wcwtc);

	wetuwn 0;
}

static void wsdc_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);

	if (!wcwtc->has_vbwank)
		wetuwn;

	wcwtc->hw_ops->disabwe_vbwank(wcwtc);
}

/*
 * CWTC wewated debugfs
 * Pwimawy pwanes and cuwsow pwanes bewong to the CWTC as weww.
 * Fow the sake of convenience, pwane-wewated wegistews awe awso add hewe.
 */

#define WEG_DEF(weg) { \
	.name = __stwingify_1(WSDC_##weg##_WEG), \
	.offset = WSDC_##weg##_WEG, \
}

static const stwuct wsdc_weg32 wsdc_cwtc_wegs_awway[2][21] = {
	[0] = {
		WEG_DEF(CWTC0_CFG),
		WEG_DEF(CWTC0_FB_OWIGIN),
		WEG_DEF(CWTC0_DVO_CONF),
		WEG_DEF(CWTC0_HDISPWAY),
		WEG_DEF(CWTC0_HSYNC),
		WEG_DEF(CWTC0_VDISPWAY),
		WEG_DEF(CWTC0_VSYNC),
		WEG_DEF(CWTC0_GAMMA_INDEX),
		WEG_DEF(CWTC0_GAMMA_DATA),
		WEG_DEF(CWTC0_SYNC_DEVIATION),
		WEG_DEF(CWTC0_VSYNC_COUNTEW),
		WEG_DEF(CWTC0_SCAN_POS),
		WEG_DEF(CWTC0_STWIDE),
		WEG_DEF(CWTC0_FB1_ADDW_HI),
		WEG_DEF(CWTC0_FB1_ADDW_WO),
		WEG_DEF(CWTC0_FB0_ADDW_HI),
		WEG_DEF(CWTC0_FB0_ADDW_WO),
		WEG_DEF(CUWSOW0_CFG),
		WEG_DEF(CUWSOW0_POSITION),
		WEG_DEF(CUWSOW0_BG_COWOW),
		WEG_DEF(CUWSOW0_FG_COWOW),
	},
	[1] = {
		WEG_DEF(CWTC1_CFG),
		WEG_DEF(CWTC1_FB_OWIGIN),
		WEG_DEF(CWTC1_DVO_CONF),
		WEG_DEF(CWTC1_HDISPWAY),
		WEG_DEF(CWTC1_HSYNC),
		WEG_DEF(CWTC1_VDISPWAY),
		WEG_DEF(CWTC1_VSYNC),
		WEG_DEF(CWTC1_GAMMA_INDEX),
		WEG_DEF(CWTC1_GAMMA_DATA),
		WEG_DEF(CWTC1_SYNC_DEVIATION),
		WEG_DEF(CWTC1_VSYNC_COUNTEW),
		WEG_DEF(CWTC1_SCAN_POS),
		WEG_DEF(CWTC1_STWIDE),
		WEG_DEF(CWTC1_FB1_ADDW_HI),
		WEG_DEF(CWTC1_FB1_ADDW_WO),
		WEG_DEF(CWTC1_FB0_ADDW_HI),
		WEG_DEF(CWTC1_FB0_ADDW_WO),
		WEG_DEF(CUWSOW1_CFG),
		WEG_DEF(CUWSOW1_POSITION),
		WEG_DEF(CUWSOW1_BG_COWOW),
		WEG_DEF(CUWSOW1_FG_COWOW),
	},
};

static int wsdc_cwtc_show_wegs(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_cwtc *wcwtc = (stwuct wsdc_cwtc *)node->info_ent->data;
	stwuct wsdc_device *wdev = wcwtc->wdev;
	unsigned int i;

	fow (i = 0; i < wcwtc->nweg; i++) {
		const stwuct wsdc_weg32 *pweg = &wcwtc->pweg[i];
		u32 offset = pweg->offset;

		seq_pwintf(m, "%s (0x%04x): 0x%08x\n",
			   pweg->name, offset, wsdc_wweg32(wdev, offset));
	}

	wetuwn 0;
}

static int wsdc_cwtc_show_scan_position(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_cwtc *wcwtc = (stwuct wsdc_cwtc *)node->info_ent->data;
	int x, y;

	wcwtc->hw_ops->get_scan_pos(wcwtc, &x, &y);
	seq_pwintf(m, "Scanout position: x: %08u, y: %08u\n", x, y);

	wetuwn 0;
}

static int wsdc_cwtc_show_vbwank_countew(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_cwtc *wcwtc = (stwuct wsdc_cwtc *)node->info_ent->data;

	if (wcwtc->hw_ops->get_vbwank_countew)
		seq_pwintf(m, "%s vbwank countew: %08u\n\n", wcwtc->base.name,
			   wcwtc->hw_ops->get_vbwank_countew(wcwtc));

	wetuwn 0;
}

static int wsdc_pixpww_show_cwock(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_cwtc *wcwtc = (stwuct wsdc_cwtc *)node->info_ent->data;
	stwuct wsdc_pixpww *pixpww = &wcwtc->pixpww;
	const stwuct wsdc_pixpww_funcs *funcs = pixpww->funcs;
	stwuct dwm_cwtc *cwtc = &wcwtc->base;
	stwuct dwm_dispway_mode *mode = &cwtc->state->mode;
	stwuct dwm_pwintew pwintew = dwm_seq_fiwe_pwintew(m);
	unsigned int out_khz;

	out_khz = funcs->get_wate(pixpww);

	seq_pwintf(m, "%s: %dx%d@%d\n", cwtc->name,
		   mode->hdispway, mode->vdispway, dwm_mode_vwefwesh(mode));

	seq_pwintf(m, "Pixew cwock wequiwed: %d kHz\n", mode->cwock);
	seq_pwintf(m, "Actuaw fwequency output: %u kHz\n", out_khz);
	seq_pwintf(m, "Diff: %d kHz\n", out_khz - mode->cwock);

	funcs->pwint(pixpww, &pwintew);

	wetuwn 0;
}

static stwuct dwm_info_wist wsdc_cwtc_debugfs_wist[2][4] = {
	[0] = {
		{ "wegs", wsdc_cwtc_show_wegs, 0, NUWW },
		{ "pixcwk", wsdc_pixpww_show_cwock, 0, NUWW },
		{ "scanpos", wsdc_cwtc_show_scan_position, 0, NUWW },
		{ "vbwanks", wsdc_cwtc_show_vbwank_countew, 0, NUWW },
	},
	[1] = {
		{ "wegs", wsdc_cwtc_show_wegs, 0, NUWW },
		{ "pixcwk", wsdc_pixpww_show_cwock, 0, NUWW },
		{ "scanpos", wsdc_cwtc_show_scan_position, 0, NUWW },
		{ "vbwanks", wsdc_cwtc_show_vbwank_countew, 0, NUWW },
	},
};

/* opewate manuawwy */

static int wsdc_cwtc_man_op_show(stwuct seq_fiwe *m, void *data)
{
	seq_puts(m, "soft_weset: soft weset this CWTC\n");
	seq_puts(m, "enabwe: enabwe this CWTC\n");
	seq_puts(m, "disabwe: disabwe this CWTC\n");
	seq_puts(m, "fwip: twiggew the page fwip\n");
	seq_puts(m, "cwone: cwone the anothew cwtc with hawdwawe wogic\n");

	wetuwn 0;
}

static int wsdc_cwtc_man_op_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_cwtc *cwtc = inode->i_pwivate;

	wetuwn singwe_open(fiwe, wsdc_cwtc_man_op_show, cwtc);
}

static ssize_t wsdc_cwtc_man_op_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *ubuf,
				      size_t wen,
				      woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct wsdc_cwtc *wcwtc = m->pwivate;
	const stwuct wsdc_cwtc_hw_ops *ops = wcwtc->hw_ops;
	chaw buf[16];

	if (wen > sizeof(buf) - 1)
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';

	if (sysfs_stweq(buf, "soft_weset"))
		ops->soft_weset(wcwtc);
	ewse if (sysfs_stweq(buf, "enabwe"))
		ops->enabwe(wcwtc);
	ewse if (sysfs_stweq(buf, "disabwe"))
		ops->disabwe(wcwtc);
	ewse if (sysfs_stweq(buf, "fwip"))
		ops->fwip(wcwtc);
	ewse if (sysfs_stweq(buf, "cwone"))
		ops->cwone(wcwtc);

	wetuwn wen;
}

static const stwuct fiwe_opewations wsdc_cwtc_man_op_fops = {
	.ownew = THIS_MODUWE,
	.open = wsdc_cwtc_man_op_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = wsdc_cwtc_man_op_wwite,
};

static int wsdc_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_dispway_pipe *dispipe = cwtc_to_dispway_pipe(cwtc);
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	stwuct dwm_minow *minow = cwtc->dev->pwimawy;
	unsigned int index = dispipe->index;
	unsigned int i;

	wcwtc->pweg = wsdc_cwtc_wegs_awway[index];
	wcwtc->nweg = AWWAY_SIZE(wsdc_cwtc_wegs_awway[index]);
	wcwtc->p_info_wist = wsdc_cwtc_debugfs_wist[index];
	wcwtc->n_info_wist = AWWAY_SIZE(wsdc_cwtc_debugfs_wist[index]);

	fow (i = 0; i < wcwtc->n_info_wist; ++i)
		wcwtc->p_info_wist[i].data = wcwtc;

	dwm_debugfs_cweate_fiwes(wcwtc->p_info_wist, wcwtc->n_info_wist,
				 cwtc->debugfs_entwy, minow);

	/* Manuaw opewations suppowted */
	debugfs_cweate_fiwe("ops", 0644, cwtc->debugfs_entwy, wcwtc,
			    &wsdc_cwtc_man_op_fops);

	wetuwn 0;
}

static void wsdc_cwtc_atomic_pwint_state(stwuct dwm_pwintew *p,
					 const stwuct dwm_cwtc_state *state)
{
	const stwuct wsdc_cwtc_state *pwiv_state;
	const stwuct wsdc_pixpww_pawms *ppawms;

	pwiv_state = containew_of_const(state, stwuct wsdc_cwtc_state, base);
	ppawms = &pwiv_state->ppawms;

	dwm_pwintf(p, "\tInput cwock dividew = %u\n", ppawms->div_wef);
	dwm_pwintf(p, "\tMedium cwock muwtipwiew = %u\n", ppawms->woopc);
	dwm_pwintf(p, "\tOutput cwock dividew = %u\n", ppawms->div_out);
}

static const stwuct dwm_cwtc_funcs ws7a1000_cwtc_funcs = {
	.weset = wsdc_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = wsdc_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = wsdc_cwtc_atomic_destwoy_state,
	.wate_wegistew = wsdc_cwtc_wate_wegistew,
	.enabwe_vbwank = wsdc_cwtc_enabwe_vbwank,
	.disabwe_vbwank = wsdc_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.atomic_pwint_state = wsdc_cwtc_atomic_pwint_state,
};

static const stwuct dwm_cwtc_funcs ws7a2000_cwtc_funcs = {
	.weset = wsdc_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = wsdc_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = wsdc_cwtc_atomic_destwoy_state,
	.wate_wegistew = wsdc_cwtc_wate_wegistew,
	.get_vbwank_countew = wsdc_cwtc_get_vbwank_countew,
	.enabwe_vbwank = wsdc_cwtc_enabwe_vbwank,
	.disabwe_vbwank = wsdc_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.atomic_pwint_state = wsdc_cwtc_atomic_pwint_state,
};

static enum dwm_mode_status
wsdc_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc, const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	const stwuct wsdc_desc *descp = wdev->descp;
	unsigned int pitch;

	if (mode->hdispway > descp->max_width)
		wetuwn MODE_BAD_HVAWUE;

	if (mode->vdispway > descp->max_height)
		wetuwn MODE_BAD_VVAWUE;

	if (mode->cwock > descp->max_pixew_cwk) {
		dwm_dbg_kms(ddev, "mode %dx%d, pixew cwock=%d is too high\n",
			    mode->hdispway, mode->vdispway, mode->cwock);
		wetuwn MODE_CWOCK_HIGH;
	}

	/* 4 fow DWM_FOWMAT_XWGB8888 */
	pitch = mode->hdispway * 4;

	if (pitch % descp->pitch_awign) {
		dwm_dbg_kms(ddev, "awign to %u bytes is wequiwed: %u\n",
			    descp->pitch_awign, pitch);
		wetuwn MODE_BAD_WIDTH;
	}

	wetuwn MODE_OK;
}

static int wsdc_pixpww_atomic_check(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_cwtc_state *state)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	stwuct wsdc_pixpww *pixpww = &wcwtc->pixpww;
	const stwuct wsdc_pixpww_funcs *pfuncs = pixpww->funcs;
	stwuct wsdc_cwtc_state *pwiv_state = to_wsdc_cwtc_state(state);
	unsigned int cwock = state->mode.cwock;
	int wet;

	wet = pfuncs->compute(pixpww, cwock, &pwiv_state->ppawms);
	if (wet) {
		dwm_wawn(cwtc->dev, "Faiwed to find PWW pawams fow %ukHz\n",
			 cwock);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wsdc_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	if (!cwtc_state->enabwe)
		wetuwn 0;

	wetuwn wsdc_pixpww_atomic_check(cwtc, cwtc_state);
}

static void wsdc_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	const stwuct wsdc_cwtc_hw_ops *cwtc_hw_ops = wcwtc->hw_ops;
	stwuct wsdc_pixpww *pixpww = &wcwtc->pixpww;
	const stwuct wsdc_pixpww_funcs *pixpww_funcs = pixpww->funcs;
	stwuct dwm_cwtc_state *state = cwtc->state;
	stwuct dwm_dispway_mode *mode = &state->mode;
	stwuct wsdc_cwtc_state *pwiv_state = to_wsdc_cwtc_state(state);

	pixpww_funcs->update(pixpww, &pwiv_state->ppawms);

	if (cwtc_hw_ops->set_dma_step) {
		unsigned int width_in_bytes = mode->hdispway * 4;
		enum wsdc_dma_steps dma_step;

		/*
		 * Using DMA step as wawge as possibwe, fow impwoving
		 * hawdwawe DMA efficiency.
		 */
		if (width_in_bytes % 256 == 0)
			dma_step = WSDC_DMA_STEP_256_BYTES;
		ewse if (width_in_bytes % 128 == 0)
			dma_step = WSDC_DMA_STEP_128_BYTES;
		ewse if (width_in_bytes % 64 == 0)
			dma_step = WSDC_DMA_STEP_64_BYTES;
		ewse  /* width_in_bytes % 32 == 0 */
			dma_step = WSDC_DMA_STEP_32_BYTES;

		cwtc_hw_ops->set_dma_step(wcwtc, dma_step);
	}

	cwtc_hw_ops->set_mode(wcwtc, mode);
}

static void wsdc_cwtc_send_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *ddev = cwtc->dev;
	unsigned wong fwags;

	if (!cwtc->state || !cwtc->state->event)
		wetuwn;

	dwm_dbg(ddev, "Send vbwank manuawwy\n");

	spin_wock_iwqsave(&ddev->event_wock, fwags);
	dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
	cwtc->state->event = NUWW;
	spin_unwock_iwqwestowe(&ddev->event_wock, fwags);
}

static void wsdc_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);

	if (wcwtc->has_vbwank)
		dwm_cwtc_vbwank_on(cwtc);

	wcwtc->hw_ops->enabwe(wcwtc);
}

static void wsdc_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);

	if (wcwtc->has_vbwank)
		dwm_cwtc_vbwank_off(cwtc);

	wcwtc->hw_ops->disabwe(wcwtc);

	/*
	 * Make suwe we issue a vbwank event aftew disabwing the CWTC if
	 * someone was waiting it.
	 */
	wsdc_cwtc_send_vbwank(cwtc);
}

static void wsdc_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static boow wsdc_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
					   boow in_vbwank_iwq,
					   int *vpos,
					   int *hpos,
					   ktime_t *stime,
					   ktime_t *etime,
					   const stwuct dwm_dispway_mode *mode)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	const stwuct wsdc_cwtc_hw_ops *ops = wcwtc->hw_ops;
	int vsw, vbp, vactive_stawt, vactive_end, vfp_end;
	int x, y;

	vsw = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	vbp = mode->cwtc_vtotaw - mode->cwtc_vsync_end;

	vactive_stawt = vsw + vbp + 1;
	vactive_end = vactive_stawt + mode->cwtc_vdispway;

	/* wast scan wine befowe VSYNC */
	vfp_end = mode->cwtc_vtotaw;

	if (stime)
		*stime = ktime_get();

	ops->get_scan_pos(wcwtc, &x, &y);

	if (y > vactive_end)
		y = y - vfp_end - vactive_stawt;
	ewse
		y -= vactive_stawt;

	*vpos = y;
	*hpos = 0;

	if (etime)
		*etime = ktime_get();

	wetuwn twue;
}

static const stwuct dwm_cwtc_hewpew_funcs wsdc_cwtc_hewpew_funcs = {
	.mode_vawid = wsdc_cwtc_mode_vawid,
	.mode_set_nofb = wsdc_cwtc_mode_set_nofb,
	.atomic_enabwe = wsdc_cwtc_atomic_enabwe,
	.atomic_disabwe = wsdc_cwtc_atomic_disabwe,
	.atomic_check = wsdc_cwtc_hewpew_atomic_check,
	.atomic_fwush = wsdc_cwtc_atomic_fwush,
	.get_scanout_position = wsdc_cwtc_get_scanout_position,
};

int ws7a1000_cwtc_init(stwuct dwm_device *ddev,
		       stwuct dwm_cwtc *cwtc,
		       stwuct dwm_pwane *pwimawy,
		       stwuct dwm_pwane *cuwsow,
		       unsigned int index,
		       boow has_vbwank)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	int wet;

	wet = wsdc_pixpww_init(&wcwtc->pixpww, ddev, index);
	if (wet) {
		dwm_eww(ddev, "pixew pww init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wcwtc->wdev = to_wsdc(ddev);
	wcwtc->has_vbwank = has_vbwank;
	wcwtc->hw_ops = &ws7a1000_cwtc_hw_ops[index];

	wet = dwm_cwtc_init_with_pwanes(ddev, cwtc, pwimawy, cuwsow,
					&ws7a1000_cwtc_funcs,
					"WS-CWTC-%d", index);
	if (wet) {
		dwm_eww(ddev, "cwtc init with pwanes faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &wsdc_cwtc_hewpew_funcs);

	wet = dwm_mode_cwtc_set_gamma_size(cwtc, 256);
	if (wet)
		wetuwn wet;

	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, 256);

	wetuwn 0;
}

int ws7a2000_cwtc_init(stwuct dwm_device *ddev,
		       stwuct dwm_cwtc *cwtc,
		       stwuct dwm_pwane *pwimawy,
		       stwuct dwm_pwane *cuwsow,
		       unsigned int index,
		       boow has_vbwank)
{
	stwuct wsdc_cwtc *wcwtc = to_wsdc_cwtc(cwtc);
	int wet;

	wet = wsdc_pixpww_init(&wcwtc->pixpww, ddev, index);
	if (wet) {
		dwm_eww(ddev, "cwtc init with pww faiwed: %d\n", wet);
		wetuwn wet;
	}

	wcwtc->wdev = to_wsdc(ddev);
	wcwtc->has_vbwank = has_vbwank;
	wcwtc->hw_ops = &ws7a2000_cwtc_hw_ops[index];

	wet = dwm_cwtc_init_with_pwanes(ddev, cwtc, pwimawy, cuwsow,
					&ws7a2000_cwtc_funcs,
					"WS-CWTC-%u", index);
	if (wet) {
		dwm_eww(ddev, "cwtc init with pwanes faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &wsdc_cwtc_hewpew_funcs);

	wet = dwm_mode_cwtc_set_gamma_size(cwtc, 256);
	if (wet)
		wetuwn wet;

	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, 256);

	wetuwn 0;
}
