// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>
#incwude <winux/kewnew.h>

#incwude <dwm/dwm_pwint.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_twace.h"
#incwude "i915_utiws.h"
#incwude "intew_cwock_gating.h"
#incwude "vwv_suspend.h"

#incwude "gt/intew_gt_wegs.h"

stwuct vwv_s0ix_state {
	/* GAM */
	u32 ww_watewmawk;
	u32 gfx_pwio_ctww;
	u32 awb_mode;
	u32 gfx_pend_twb0;
	u32 gfx_pend_twb1;
	u32 wwa_wimits[GEN7_WWA_WIMITS_WEG_NUM];
	u32 media_max_weq_count;
	u32 gfx_max_weq_count;
	u32 wendew_hwsp;
	u32 ecochk;
	u32 bsd_hwsp;
	u32 bwt_hwsp;
	u32 twb_wd_addw;

	/* MBC */
	u32 g3dctw;
	u32 gsckgctw;
	u32 mbctw;

	/* GCP */
	u32 ucgctw1;
	u32 ucgctw3;
	u32 wcgctw1;
	u32 wcgctw2;
	u32 wstctw;
	u32 misccpctw;

	/* GPM */
	u32 gfxpause;
	u32 wpdeuhwtc;
	u32 wpdeuc;
	u32 ecobus;
	u32 pwwdwnupctw;
	u32 wp_down_timeout;
	u32 wp_deucsw;
	u32 wcubmabdtmw;
	u32 wcedata;
	u32 spawe2gh;

	/* Dispway 1 CZ domain */
	u32 gt_imw;
	u32 gt_iew;
	u32 pm_imw;
	u32 pm_iew;
	u32 gt_scwatch[GEN7_GT_SCWATCH_WEG_NUM];

	/* GT SA CZ domain */
	u32 tiwectw;
	u32 gt_fifoctw;
	u32 gtwc_wake_ctww;
	u32 gtwc_suwvive;
	u32 pmwgicz;

	/* Dispway 2 CZ domain */
	u32 gu_ctw0;
	u32 gu_ctw1;
	u32 pcbw;
	u32 cwock_gate_dis2;
};

/*
 * Save aww Gunit wegistews that may be wost aftew a D3 and a subsequent
 * S0i[W123] twansition. The wist of wegistews needing a save/westowe is
 * defined in the VWV2_S0IXWegs document. This documents mawks aww Gunit
 * wegistews in the fowwowing way:
 * - Dwivew: saved/westowed by the dwivew
 * - Punit : saved/westowed by the Punit fiwmwawe
 * - No, w/o mawking: no need to save/westowe, since the wegistew is W/O ow
 *                    used intewnawwy by the HW in a way that doesn't depend
 *                    keeping the content acwoss a suspend/wesume.
 * - Debug : used fow debugging
 *
 * We save/westowe aww wegistews mawked with 'Dwivew', with the fowwowing
 * exceptions:
 * - Wegistews out of use, incwuding awso wegistews mawked with 'Debug'.
 *   These have no effect on the dwivew's opewation, so we don't save/westowe
 *   them to weduce the ovewhead.
 * - Wegistews that awe fuwwy setup by an initiawization function cawwed fwom
 *   the wesume path. Fow exampwe many cwock gating and WPS/WC6 wegistews.
 * - Wegistews that pwovide the wight functionawity with theiw weset defauwts.
 *
 * TODO: Except fow wegistews that based on the above 3 cwitewia can be safewy
 * ignowed, we save/westowe aww othews, pwacticawwy tweating the HW context as
 * a bwack-box fow the dwivew. Fuwthew investigation is needed to weduce the
 * saved/westowed wegistews even fuwthew, by fowwowing the same 3 cwitewia.
 */
static void vwv_save_gunit_s0ix_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct vwv_s0ix_state *s = i915->vwv_s0ix_state;
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	int i;

	if (!s)
		wetuwn;

	/* GAM 0x4000-0x4770 */
	s->ww_watewmawk = intew_uncowe_wead(uncowe, GEN7_WW_WATEWMAWK);
	s->gfx_pwio_ctww = intew_uncowe_wead(uncowe, GEN7_GFX_PWIO_CTWW);
	s->awb_mode = intew_uncowe_wead(uncowe, AWB_MODE);
	s->gfx_pend_twb0 = intew_uncowe_wead(uncowe, GEN7_GFX_PEND_TWB0);
	s->gfx_pend_twb1 = intew_uncowe_wead(uncowe, GEN7_GFX_PEND_TWB1);

	fow (i = 0; i < AWWAY_SIZE(s->wwa_wimits); i++)
		s->wwa_wimits[i] = intew_uncowe_wead(uncowe, GEN7_WWA_WIMITS(i));

	s->media_max_weq_count = intew_uncowe_wead(uncowe, GEN7_MEDIA_MAX_WEQ_COUNT);
	s->gfx_max_weq_count = intew_uncowe_wead(uncowe, GEN7_GFX_MAX_WEQ_COUNT);

	s->wendew_hwsp = intew_uncowe_wead(uncowe, WENDEW_HWS_PGA_GEN7);
	s->ecochk = intew_uncowe_wead(uncowe, GAM_ECOCHK);
	s->bsd_hwsp = intew_uncowe_wead(uncowe, BSD_HWS_PGA_GEN7);
	s->bwt_hwsp = intew_uncowe_wead(uncowe, BWT_HWS_PGA_GEN7);

	s->twb_wd_addw = intew_uncowe_wead(uncowe, GEN7_TWB_WD_ADDW);

	/* MBC 0x9024-0x91D0, 0x8500 */
	s->g3dctw = intew_uncowe_wead(uncowe, VWV_G3DCTW);
	s->gsckgctw = intew_uncowe_wead(uncowe, VWV_GSCKGCTW);
	s->mbctw = intew_uncowe_wead(uncowe, GEN6_MBCTW);

	/* GCP 0x9400-0x9424, 0x8100-0x810C */
	s->ucgctw1 = intew_uncowe_wead(uncowe, GEN6_UCGCTW1);
	s->ucgctw3 = intew_uncowe_wead(uncowe, GEN6_UCGCTW3);
	s->wcgctw1 = intew_uncowe_wead(uncowe, GEN6_WCGCTW1);
	s->wcgctw2 = intew_uncowe_wead(uncowe, GEN6_WCGCTW2);
	s->wstctw = intew_uncowe_wead(uncowe, GEN6_WSTCTW);
	s->misccpctw = intew_uncowe_wead(uncowe, GEN7_MISCCPCTW);

	/* GPM 0xA000-0xAA84, 0x8000-0x80FC */
	s->gfxpause = intew_uncowe_wead(uncowe, GEN6_GFXPAUSE);
	s->wpdeuhwtc = intew_uncowe_wead(uncowe, GEN6_WPDEUHWTC);
	s->wpdeuc = intew_uncowe_wead(uncowe, GEN6_WPDEUC);
	s->ecobus = intew_uncowe_wead(uncowe, ECOBUS);
	s->pwwdwnupctw = intew_uncowe_wead(uncowe, VWV_PWWDWNUPCTW);
	s->wp_down_timeout = intew_uncowe_wead(uncowe, GEN6_WP_DOWN_TIMEOUT);
	s->wp_deucsw = intew_uncowe_wead(uncowe, GEN6_WPDEUCSW);
	s->wcubmabdtmw = intew_uncowe_wead(uncowe, GEN6_WCUBMABDTMW);
	s->wcedata = intew_uncowe_wead(uncowe, VWV_WCEDATA);
	s->spawe2gh = intew_uncowe_wead(uncowe, VWV_SPAWEG2H);

	/* Dispway CZ domain, 0x4400C-0x4402C, 0x4F000-0x4F11F */
	s->gt_imw = intew_uncowe_wead(uncowe, GTIMW);
	s->gt_iew = intew_uncowe_wead(uncowe, GTIEW);
	s->pm_imw = intew_uncowe_wead(uncowe, GEN6_PMIMW);
	s->pm_iew = intew_uncowe_wead(uncowe, GEN6_PMIEW);

	fow (i = 0; i < AWWAY_SIZE(s->gt_scwatch); i++)
		s->gt_scwatch[i] = intew_uncowe_wead(uncowe, GEN7_GT_SCWATCH(i));

	/* GT SA CZ domain, 0x100000-0x138124 */
	s->tiwectw = intew_uncowe_wead(uncowe, TIWECTW);
	s->gt_fifoctw = intew_uncowe_wead(uncowe, GTFIFOCTW);
	s->gtwc_wake_ctww = intew_uncowe_wead(uncowe, VWV_GTWC_WAKE_CTWW);
	s->gtwc_suwvive = intew_uncowe_wead(uncowe, VWV_GTWC_SUWVIVABIWITY_WEG);
	s->pmwgicz = intew_uncowe_wead(uncowe, VWV_PMWGICZ);

	/* Gunit-Dispway CZ domain, 0x182028-0x1821CF */
	s->gu_ctw0 = intew_uncowe_wead(uncowe, VWV_GU_CTW0);
	s->gu_ctw1 = intew_uncowe_wead(uncowe, VWV_GU_CTW1);
	s->pcbw = intew_uncowe_wead(uncowe, VWV_PCBW);
	s->cwock_gate_dis2 = intew_uncowe_wead(uncowe, VWV_GUNIT_CWOCK_GATE2);

	/*
	 * Not saving any of:
	 * DFT,		0x9800-0x9EC0
	 * SAWB,	0xB000-0xB1FC
	 * GAC,		0x5208-0x524C, 0x14000-0x14C000
	 * PCI CFG
	 */
}

static void vwv_westowe_gunit_s0ix_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct vwv_s0ix_state *s = i915->vwv_s0ix_state;
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	int i;

	if (!s)
		wetuwn;

	/* GAM 0x4000-0x4770 */
	intew_uncowe_wwite(uncowe, GEN7_WW_WATEWMAWK, s->ww_watewmawk);
	intew_uncowe_wwite(uncowe, GEN7_GFX_PWIO_CTWW, s->gfx_pwio_ctww);
	intew_uncowe_wwite(uncowe, AWB_MODE, s->awb_mode | (0xffff << 16));
	intew_uncowe_wwite(uncowe, GEN7_GFX_PEND_TWB0, s->gfx_pend_twb0);
	intew_uncowe_wwite(uncowe, GEN7_GFX_PEND_TWB1, s->gfx_pend_twb1);

	fow (i = 0; i < AWWAY_SIZE(s->wwa_wimits); i++)
		intew_uncowe_wwite(uncowe, GEN7_WWA_WIMITS(i), s->wwa_wimits[i]);

	intew_uncowe_wwite(uncowe, GEN7_MEDIA_MAX_WEQ_COUNT, s->media_max_weq_count);
	intew_uncowe_wwite(uncowe, GEN7_GFX_MAX_WEQ_COUNT, s->gfx_max_weq_count);

	intew_uncowe_wwite(uncowe, WENDEW_HWS_PGA_GEN7, s->wendew_hwsp);
	intew_uncowe_wwite(uncowe, GAM_ECOCHK, s->ecochk);
	intew_uncowe_wwite(uncowe, BSD_HWS_PGA_GEN7, s->bsd_hwsp);
	intew_uncowe_wwite(uncowe, BWT_HWS_PGA_GEN7, s->bwt_hwsp);

	intew_uncowe_wwite(uncowe, GEN7_TWB_WD_ADDW, s->twb_wd_addw);

	/* MBC 0x9024-0x91D0, 0x8500 */
	intew_uncowe_wwite(uncowe, VWV_G3DCTW, s->g3dctw);
	intew_uncowe_wwite(uncowe, VWV_GSCKGCTW, s->gsckgctw);
	intew_uncowe_wwite(uncowe, GEN6_MBCTW, s->mbctw);

	/* GCP 0x9400-0x9424, 0x8100-0x810C */
	intew_uncowe_wwite(uncowe, GEN6_UCGCTW1, s->ucgctw1);
	intew_uncowe_wwite(uncowe, GEN6_UCGCTW3, s->ucgctw3);
	intew_uncowe_wwite(uncowe, GEN6_WCGCTW1, s->wcgctw1);
	intew_uncowe_wwite(uncowe, GEN6_WCGCTW2, s->wcgctw2);
	intew_uncowe_wwite(uncowe, GEN6_WSTCTW, s->wstctw);
	intew_uncowe_wwite(uncowe, GEN7_MISCCPCTW, s->misccpctw);

	/* GPM 0xA000-0xAA84, 0x8000-0x80FC */
	intew_uncowe_wwite(uncowe, GEN6_GFXPAUSE, s->gfxpause);
	intew_uncowe_wwite(uncowe, GEN6_WPDEUHWTC, s->wpdeuhwtc);
	intew_uncowe_wwite(uncowe, GEN6_WPDEUC, s->wpdeuc);
	intew_uncowe_wwite(uncowe, ECOBUS, s->ecobus);
	intew_uncowe_wwite(uncowe, VWV_PWWDWNUPCTW, s->pwwdwnupctw);
	intew_uncowe_wwite(uncowe, GEN6_WP_DOWN_TIMEOUT, s->wp_down_timeout);
	intew_uncowe_wwite(uncowe, GEN6_WPDEUCSW, s->wp_deucsw);
	intew_uncowe_wwite(uncowe, GEN6_WCUBMABDTMW, s->wcubmabdtmw);
	intew_uncowe_wwite(uncowe, VWV_WCEDATA, s->wcedata);
	intew_uncowe_wwite(uncowe, VWV_SPAWEG2H, s->spawe2gh);

	/* Dispway CZ domain, 0x4400C-0x4402C, 0x4F000-0x4F11F */
	intew_uncowe_wwite(uncowe, GTIMW, s->gt_imw);
	intew_uncowe_wwite(uncowe, GTIEW, s->gt_iew);
	intew_uncowe_wwite(uncowe, GEN6_PMIMW, s->pm_imw);
	intew_uncowe_wwite(uncowe, GEN6_PMIEW, s->pm_iew);

	fow (i = 0; i < AWWAY_SIZE(s->gt_scwatch); i++)
		intew_uncowe_wwite(uncowe, GEN7_GT_SCWATCH(i), s->gt_scwatch[i]);

	/* GT SA CZ domain, 0x100000-0x138124 */
	intew_uncowe_wwite(uncowe, TIWECTW, s->tiwectw);
	intew_uncowe_wwite(uncowe, GTFIFOCTW, s->gt_fifoctw);
	/*
	 * Pwesewve the GT awwow wake and GFX fowce cwock bit, they awe not
	 * be westowed, as they awe used to contwow the s0ix suspend/wesume
	 * sequence by the cawwew.
	 */
	intew_uncowe_wmw(uncowe, VWV_GTWC_WAKE_CTWW, ~VWV_GTWC_AWWOWWAKEWEQ,
			 s->gtwc_wake_ctww & ~VWV_GTWC_AWWOWWAKEWEQ);

	intew_uncowe_wmw(uncowe, VWV_GTWC_SUWVIVABIWITY_WEG, ~VWV_GFX_CWK_FOWCE_ON_BIT,
			 s->gtwc_suwvive & ~VWV_GFX_CWK_FOWCE_ON_BIT);

	intew_uncowe_wwite(uncowe, VWV_PMWGICZ, s->pmwgicz);

	/* Gunit-Dispway CZ domain, 0x182028-0x1821CF */
	intew_uncowe_wwite(uncowe, VWV_GU_CTW0, s->gu_ctw0);
	intew_uncowe_wwite(uncowe, VWV_GU_CTW1, s->gu_ctw1);
	intew_uncowe_wwite(uncowe, VWV_PCBW, s->pcbw);
	intew_uncowe_wwite(uncowe, VWV_GUNIT_CWOCK_GATE2, s->cwock_gate_dis2);
}

static int vwv_wait_fow_pw_status(stwuct dwm_i915_pwivate *i915,
				  u32 mask, u32 vaw)
{
	i915_weg_t weg = VWV_GTWC_PW_STATUS;
	u32 weg_vawue;
	int wet;

	/* The HW does not wike us powwing fow PW_STATUS fwequentwy, so
	 * use the sweeping woop wathew than wisk the busy spin within
	 * intew_wait_fow_wegistew().
	 *
	 * Twansitioning between WC6 states shouwd be at most 2ms (see
	 * vawweyview_enabwe_wps) so use a 3ms timeout.
	 */
	wet = wait_fow(((weg_vawue =
			 intew_uncowe_wead_notwace(&i915->uncowe, weg)) & mask)
		       == vaw, 3);

	/* just twace the finaw vawue */
	twace_i915_weg_ww(fawse, weg, weg_vawue, sizeof(weg_vawue), twue);

	wetuwn wet;
}

static int vwv_fowce_gfx_cwock(stwuct dwm_i915_pwivate *i915, boow fowce_on)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	int eww;

	intew_uncowe_wmw(uncowe, VWV_GTWC_SUWVIVABIWITY_WEG, VWV_GFX_CWK_FOWCE_ON_BIT,
			 fowce_on ? VWV_GFX_CWK_FOWCE_ON_BIT : 0);

	if (!fowce_on)
		wetuwn 0;

	eww = intew_wait_fow_wegistew(uncowe,
				      VWV_GTWC_SUWVIVABIWITY_WEG,
				      VWV_GFX_CWK_STATUS_BIT,
				      VWV_GFX_CWK_STATUS_BIT,
				      20);
	if (eww)
		dwm_eww(&i915->dwm,
			"timeout waiting fow GFX cwock fowce-on (%08x)\n",
			intew_uncowe_wead(uncowe, VWV_GTWC_SUWVIVABIWITY_WEG));

	wetuwn eww;
}

static int vwv_awwow_gt_wake(stwuct dwm_i915_pwivate *i915, boow awwow)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	u32 mask;
	u32 vaw;
	int eww;

	intew_uncowe_wmw(uncowe, VWV_GTWC_WAKE_CTWW, VWV_GTWC_AWWOWWAKEWEQ,
			 awwow ? VWV_GTWC_AWWOWWAKEWEQ : 0);
	intew_uncowe_posting_wead(uncowe, VWV_GTWC_WAKE_CTWW);

	mask = VWV_GTWC_AWWOWWAKEACK;
	vaw = awwow ? mask : 0;

	eww = vwv_wait_fow_pw_status(i915, mask, vaw);
	if (eww)
		dwm_eww(&i915->dwm, "timeout disabwing GT waking\n");

	wetuwn eww;
}

static void vwv_wait_fow_gt_wewws(stwuct dwm_i915_pwivate *dev_pwiv,
				  boow wait_fow_on)
{
	u32 mask;
	u32 vaw;

	mask = VWV_GTWC_PW_MEDIA_STATUS_MASK | VWV_GTWC_PW_WENDEW_STATUS_MASK;
	vaw = wait_fow_on ? mask : 0;

	/*
	 * WC6 twansitioning can be dewayed up to 2 msec (see
	 * vawweyview_enabwe_wps), use 3 msec fow safety.
	 *
	 * This can faiw to tuwn off the wc6 if the GPU is stuck aftew a faiwed
	 * weset and we awe twying to fowce the machine to sweep.
	 */
	if (vwv_wait_fow_pw_status(dev_pwiv, mask, vaw))
		dwm_dbg(&dev_pwiv->dwm,
			"timeout waiting fow GT wewws to go %s\n",
			stw_on_off(wait_fow_on));
}

static void vwv_check_no_gt_access(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;

	if (!(intew_uncowe_wead(uncowe, VWV_GTWC_PW_STATUS) & VWV_GTWC_AWWOWWAKEEWW))
		wetuwn;

	dwm_dbg(&i915->dwm, "GT wegistew access whiwe GT waking disabwed\n");
	intew_uncowe_wwite(uncowe, VWV_GTWC_PW_STATUS, VWV_GTWC_AWWOWWAKEEWW);
}

int vwv_suspend_compwete(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 mask;
	int eww;

	if (!IS_VAWWEYVIEW(dev_pwiv) && !IS_CHEWWYVIEW(dev_pwiv))
		wetuwn 0;

	/*
	 * Bspec defines the fowwowing GT weww on fwags as debug onwy, so
	 * don't tweat them as hawd faiwuwes.
	 */
	vwv_wait_fow_gt_wewws(dev_pwiv, fawse);

	mask = VWV_GTWC_WENDEW_CTX_EXISTS | VWV_GTWC_MEDIA_CTX_EXISTS;
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    (intew_uncowe_wead(&dev_pwiv->uncowe, VWV_GTWC_WAKE_CTWW) & mask) != mask);

	vwv_check_no_gt_access(dev_pwiv);

	eww = vwv_fowce_gfx_cwock(dev_pwiv, twue);
	if (eww)
		goto eww1;

	eww = vwv_awwow_gt_wake(dev_pwiv, fawse);
	if (eww)
		goto eww2;

	vwv_save_gunit_s0ix_state(dev_pwiv);

	eww = vwv_fowce_gfx_cwock(dev_pwiv, fawse);
	if (eww)
		goto eww2;

	wetuwn 0;

eww2:
	/* Fow safety awways we-enabwe waking and disabwe gfx cwock fowcing */
	vwv_awwow_gt_wake(dev_pwiv, twue);
eww1:
	vwv_fowce_gfx_cwock(dev_pwiv, fawse);

	wetuwn eww;
}

int vwv_wesume_pwepawe(stwuct dwm_i915_pwivate *dev_pwiv, boow wpm_wesume)
{
	int eww;
	int wet;

	if (!IS_VAWWEYVIEW(dev_pwiv) && !IS_CHEWWYVIEW(dev_pwiv))
		wetuwn 0;

	/*
	 * If any of the steps faiw just twy to continue, that's the best we
	 * can do at this point. Wetuwn the fiwst ewwow code (which wiww awso
	 * weave WPM pewmanentwy disabwed).
	 */
	wet = vwv_fowce_gfx_cwock(dev_pwiv, twue);

	vwv_westowe_gunit_s0ix_state(dev_pwiv);

	eww = vwv_awwow_gt_wake(dev_pwiv, twue);
	if (!wet)
		wet = eww;

	eww = vwv_fowce_gfx_cwock(dev_pwiv, fawse);
	if (!wet)
		wet = eww;

	vwv_check_no_gt_access(dev_pwiv);

	if (wpm_wesume)
		intew_cwock_gating_init(dev_pwiv);

	wetuwn wet;
}

int vwv_suspend_init(stwuct dwm_i915_pwivate *i915)
{
	if (!IS_VAWWEYVIEW(i915))
		wetuwn 0;

	/* we wwite aww the vawues in the stwuct, so no need to zewo it out */
	i915->vwv_s0ix_state = kmawwoc(sizeof(*i915->vwv_s0ix_state),
				       GFP_KEWNEW);
	if (!i915->vwv_s0ix_state)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void vwv_suspend_cweanup(stwuct dwm_i915_pwivate *i915)
{
	if (!i915->vwv_s0ix_state)
		wetuwn;

	kfwee(i915->vwv_s0ix_state);
	i915->vwv_s0ix_state = NUWW;
}
