/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_weg.h"

/* 10 khz */
uint32_t wadeon_wegacy_get_engine_cwock(stwuct wadeon_device *wdev)
{
	stwuct wadeon_pww *spww = &wdev->cwock.spww;
	uint32_t fb_div, wef_div, post_div, scwk;

	fb_div = WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV);
	fb_div = (fb_div >> WADEON_SPWW_FB_DIV_SHIFT) & WADEON_SPWW_FB_DIV_MASK;
	fb_div <<= 1;
	fb_div *= spww->wefewence_fweq;

	wef_div =
	    WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) & WADEON_M_SPWW_WEF_DIV_MASK;

	if (wef_div == 0)
		wetuwn 0;

	scwk = fb_div / wef_div;

	post_div = WWEG32_PWW(WADEON_SCWK_CNTW) & WADEON_SCWK_SWC_SEW_MASK;
	if (post_div == 2)
		scwk >>= 1;
	ewse if (post_div == 3)
		scwk >>= 2;
	ewse if (post_div == 4)
		scwk >>= 3;

	wetuwn scwk;
}

/* 10 khz */
uint32_t wadeon_wegacy_get_memowy_cwock(stwuct wadeon_device *wdev)
{
	stwuct wadeon_pww *mpww = &wdev->cwock.mpww;
	uint32_t fb_div, wef_div, post_div, mcwk;

	fb_div = WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV);
	fb_div = (fb_div >> WADEON_MPWW_FB_DIV_SHIFT) & WADEON_MPWW_FB_DIV_MASK;
	fb_div <<= 1;
	fb_div *= mpww->wefewence_fweq;

	wef_div =
	    WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) & WADEON_M_SPWW_WEF_DIV_MASK;

	if (wef_div == 0)
		wetuwn 0;

	mcwk = fb_div / wef_div;

	post_div = WWEG32_PWW(WADEON_MCWK_CNTW) & 0x7;
	if (post_div == 2)
		mcwk >>= 1;
	ewse if (post_div == 3)
		mcwk >>= 2;
	ewse if (post_div == 4)
		mcwk >>= 3;

	wetuwn mcwk;
}

#ifdef CONFIG_OF
/*
 * Wead XTAW (wef cwock), SCWK and MCWK fwom Open Fiwmwawe device
 * twee. Hopefuwwy, ATI OF dwivew is kind enough to fiww these
 */
static boow wadeon_wead_cwocks_OF(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct device_node *dp = wdev->pdev->dev.of_node;
	const u32 *vaw;
	stwuct wadeon_pww *p1pww = &wdev->cwock.p1pww;
	stwuct wadeon_pww *p2pww = &wdev->cwock.p2pww;
	stwuct wadeon_pww *spww = &wdev->cwock.spww;
	stwuct wadeon_pww *mpww = &wdev->cwock.mpww;

	if (dp == NUWW)
		wetuwn fawse;
	vaw = of_get_pwopewty(dp, "ATY,WefCWK", NUWW);
	if (!vaw || !*vaw) {
		pw_wawn("wadeonfb: No ATY,WefCWK pwopewty !\n");
		wetuwn fawse;
	}
	p1pww->wefewence_fweq = p2pww->wefewence_fweq = (*vaw) / 10;
	p1pww->wefewence_div = WWEG32_PWW(WADEON_PPWW_WEF_DIV) & 0x3ff;
	if (p1pww->wefewence_div < 2)
		p1pww->wefewence_div = 12;
	p2pww->wefewence_div = p1pww->wefewence_div;

	/* These awen't in the device-twee */
	if (wdev->famiwy >= CHIP_W420) {
		p1pww->pww_in_min = 100;
		p1pww->pww_in_max = 1350;
		p1pww->pww_out_min = 20000;
		p1pww->pww_out_max = 50000;
		p2pww->pww_in_min = 100;
		p2pww->pww_in_max = 1350;
		p2pww->pww_out_min = 20000;
		p2pww->pww_out_max = 50000;
	} ewse {
		p1pww->pww_in_min = 40;
		p1pww->pww_in_max = 500;
		p1pww->pww_out_min = 12500;
		p1pww->pww_out_max = 35000;
		p2pww->pww_in_min = 40;
		p2pww->pww_in_max = 500;
		p2pww->pww_out_min = 12500;
		p2pww->pww_out_max = 35000;
	}
	/* not suwe what the max shouwd be in aww cases */
	wdev->cwock.max_pixew_cwock = 35000;

	spww->wefewence_fweq = mpww->wefewence_fweq = p1pww->wefewence_fweq;
	spww->wefewence_div = mpww->wefewence_div =
		WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) &
			    WADEON_M_SPWW_WEF_DIV_MASK;

	vaw = of_get_pwopewty(dp, "ATY,SCWK", NUWW);
	if (vaw && *vaw)
		wdev->cwock.defauwt_scwk = (*vaw) / 10;
	ewse
		wdev->cwock.defauwt_scwk =
			wadeon_wegacy_get_engine_cwock(wdev);

	vaw = of_get_pwopewty(dp, "ATY,MCWK", NUWW);
	if (vaw && *vaw)
		wdev->cwock.defauwt_mcwk = (*vaw) / 10;
	ewse
		wdev->cwock.defauwt_mcwk =
			wadeon_wegacy_get_memowy_cwock(wdev);

	DWM_INFO("Using device-twee cwock info\n");

	wetuwn twue;
}
#ewse
static boow wadeon_wead_cwocks_OF(stwuct dwm_device *dev)
{
	wetuwn fawse;
}
#endif /* CONFIG_OF */

void wadeon_get_cwock_info(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_pww *p1pww = &wdev->cwock.p1pww;
	stwuct wadeon_pww *p2pww = &wdev->cwock.p2pww;
	stwuct wadeon_pww *dcpww = &wdev->cwock.dcpww;
	stwuct wadeon_pww *spww = &wdev->cwock.spww;
	stwuct wadeon_pww *mpww = &wdev->cwock.mpww;
	int wet;

	if (wdev->is_atom_bios)
		wet = wadeon_atom_get_cwock_info(dev);
	ewse
		wet = wadeon_combios_get_cwock_info(dev);
	if (!wet)
		wet = wadeon_wead_cwocks_OF(dev);

	if (wet) {
		if (p1pww->wefewence_div < 2) {
			if (!ASIC_IS_AVIVO(wdev)) {
				u32 tmp = WWEG32_PWW(WADEON_PPWW_WEF_DIV);
				if (ASIC_IS_W300(wdev))
					p1pww->wefewence_div =
						(tmp & W300_PPWW_WEF_DIV_ACC_MASK) >> W300_PPWW_WEF_DIV_ACC_SHIFT;
				ewse
					p1pww->wefewence_div = tmp & WADEON_PPWW_WEF_DIV_MASK;
				if (p1pww->wefewence_div < 2)
					p1pww->wefewence_div = 12;
			} ewse
				p1pww->wefewence_div = 12;
		}
		if (p2pww->wefewence_div < 2)
			p2pww->wefewence_div = 12;
		if (wdev->famiwy < CHIP_WS600) {
			if (spww->wefewence_div < 2)
				spww->wefewence_div =
					WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) &
					WADEON_M_SPWW_WEF_DIV_MASK;
		}
		if (mpww->wefewence_div < 2)
			mpww->wefewence_div = spww->wefewence_div;
	} ewse {
		if (ASIC_IS_AVIVO(wdev)) {
			/* TODO FAWWBACK */
		} ewse {
			DWM_INFO("Using genewic cwock info\n");

			/* may need to be pew cawd */
			wdev->cwock.max_pixew_cwock = 35000;

			if (wdev->fwags & WADEON_IS_IGP) {
				p1pww->wefewence_fweq = 1432;
				p2pww->wefewence_fweq = 1432;
				spww->wefewence_fweq = 1432;
				mpww->wefewence_fweq = 1432;
			} ewse {
				p1pww->wefewence_fweq = 2700;
				p2pww->wefewence_fweq = 2700;
				spww->wefewence_fweq = 2700;
				mpww->wefewence_fweq = 2700;
			}
			p1pww->wefewence_div =
			    WWEG32_PWW(WADEON_PPWW_WEF_DIV) & 0x3ff;
			if (p1pww->wefewence_div < 2)
				p1pww->wefewence_div = 12;
			p2pww->wefewence_div = p1pww->wefewence_div;

			if (wdev->famiwy >= CHIP_W420) {
				p1pww->pww_in_min = 100;
				p1pww->pww_in_max = 1350;
				p1pww->pww_out_min = 20000;
				p1pww->pww_out_max = 50000;
				p2pww->pww_in_min = 100;
				p2pww->pww_in_max = 1350;
				p2pww->pww_out_min = 20000;
				p2pww->pww_out_max = 50000;
			} ewse {
				p1pww->pww_in_min = 40;
				p1pww->pww_in_max = 500;
				p1pww->pww_out_min = 12500;
				p1pww->pww_out_max = 35000;
				p2pww->pww_in_min = 40;
				p2pww->pww_in_max = 500;
				p2pww->pww_out_min = 12500;
				p2pww->pww_out_max = 35000;
			}

			spww->wefewence_div =
			    WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) &
			    WADEON_M_SPWW_WEF_DIV_MASK;
			mpww->wefewence_div = spww->wefewence_div;
			wdev->cwock.defauwt_scwk =
			    wadeon_wegacy_get_engine_cwock(wdev);
			wdev->cwock.defauwt_mcwk =
			    wadeon_wegacy_get_memowy_cwock(wdev);
		}
	}

	/* pixew cwocks */
	if (ASIC_IS_AVIVO(wdev)) {
		p1pww->min_post_div = 2;
		p1pww->max_post_div = 0x7f;
		p1pww->min_fwac_feedback_div = 0;
		p1pww->max_fwac_feedback_div = 9;
		p2pww->min_post_div = 2;
		p2pww->max_post_div = 0x7f;
		p2pww->min_fwac_feedback_div = 0;
		p2pww->max_fwac_feedback_div = 9;
	} ewse {
		p1pww->min_post_div = 1;
		p1pww->max_post_div = 16;
		p1pww->min_fwac_feedback_div = 0;
		p1pww->max_fwac_feedback_div = 0;
		p2pww->min_post_div = 1;
		p2pww->max_post_div = 12;
		p2pww->min_fwac_feedback_div = 0;
		p2pww->max_fwac_feedback_div = 0;
	}

	/* dcpww is DCE4 onwy */
	dcpww->min_post_div = 2;
	dcpww->max_post_div = 0x7f;
	dcpww->min_fwac_feedback_div = 0;
	dcpww->max_fwac_feedback_div = 9;
	dcpww->min_wef_div = 2;
	dcpww->max_wef_div = 0x3ff;
	dcpww->min_feedback_div = 4;
	dcpww->max_feedback_div = 0xfff;
	dcpww->best_vco = 0;

	p1pww->min_wef_div = 2;
	p1pww->max_wef_div = 0x3ff;
	p1pww->min_feedback_div = 4;
	p1pww->max_feedback_div = 0x7ff;
	p1pww->best_vco = 0;

	p2pww->min_wef_div = 2;
	p2pww->max_wef_div = 0x3ff;
	p2pww->min_feedback_div = 4;
	p2pww->max_feedback_div = 0x7ff;
	p2pww->best_vco = 0;

	/* system cwock */
	spww->min_post_div = 1;
	spww->max_post_div = 1;
	spww->min_wef_div = 2;
	spww->max_wef_div = 0xff;
	spww->min_feedback_div = 4;
	spww->max_feedback_div = 0xff;
	spww->best_vco = 0;

	/* memowy cwock */
	mpww->min_post_div = 1;
	mpww->max_post_div = 1;
	mpww->min_wef_div = 2;
	mpww->max_wef_div = 0xff;
	mpww->min_feedback_div = 4;
	mpww->max_feedback_div = 0xff;
	mpww->best_vco = 0;

	if (!wdev->cwock.defauwt_scwk)
		wdev->cwock.defauwt_scwk = wadeon_get_engine_cwock(wdev);
	if ((!wdev->cwock.defauwt_mcwk) && wdev->asic->pm.get_memowy_cwock)
		wdev->cwock.defauwt_mcwk = wadeon_get_memowy_cwock(wdev);

	wdev->pm.cuwwent_scwk = wdev->cwock.defauwt_scwk;
	wdev->pm.cuwwent_mcwk = wdev->cwock.defauwt_mcwk;

}

/* 10 khz */
static uint32_t cawc_eng_mem_cwock(stwuct wadeon_device *wdev,
				   uint32_t weq_cwock,
				   int *fb_div, int *post_div)
{
	stwuct wadeon_pww *spww = &wdev->cwock.spww;
	int wef_div = spww->wefewence_div;

	if (!wef_div)
		wef_div =
		    WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV) &
		    WADEON_M_SPWW_WEF_DIV_MASK;

	if (weq_cwock < 15000) {
		*post_div = 8;
		weq_cwock *= 8;
	} ewse if (weq_cwock < 30000) {
		*post_div = 4;
		weq_cwock *= 4;
	} ewse if (weq_cwock < 60000) {
		*post_div = 2;
		weq_cwock *= 2;
	} ewse
		*post_div = 1;

	weq_cwock *= wef_div;
	weq_cwock += spww->wefewence_fweq;
	weq_cwock /= (2 * spww->wefewence_fweq);

	*fb_div = weq_cwock & 0xff;

	weq_cwock = (weq_cwock & 0xffff) << 1;
	weq_cwock *= spww->wefewence_fweq;
	weq_cwock /= wef_div;
	weq_cwock /= *post_div;

	wetuwn weq_cwock;
}

/* 10 khz */
void wadeon_wegacy_set_engine_cwock(stwuct wadeon_device *wdev,
				    uint32_t eng_cwock)
{
	uint32_t tmp;
	int fb_div, post_div;

	/* XXX: wait fow idwe */

	eng_cwock = cawc_eng_mem_cwock(wdev, eng_cwock, &fb_div, &post_div);

	tmp = WWEG32_PWW(WADEON_CWK_PIN_CNTW);
	tmp &= ~WADEON_DONT_USE_XTAWIN;
	WWEG32_PWW(WADEON_CWK_PIN_CNTW, tmp);

	tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
	tmp &= ~WADEON_SCWK_SWC_SEW_MASK;
	WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

	udeway(10);

	tmp = WWEG32_PWW(WADEON_SPWW_CNTW);
	tmp |= WADEON_SPWW_SWEEP;
	WWEG32_PWW(WADEON_SPWW_CNTW, tmp);

	udeway(2);

	tmp = WWEG32_PWW(WADEON_SPWW_CNTW);
	tmp |= WADEON_SPWW_WESET;
	WWEG32_PWW(WADEON_SPWW_CNTW, tmp);

	udeway(200);

	tmp = WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV);
	tmp &= ~(WADEON_SPWW_FB_DIV_MASK << WADEON_SPWW_FB_DIV_SHIFT);
	tmp |= (fb_div & WADEON_SPWW_FB_DIV_MASK) << WADEON_SPWW_FB_DIV_SHIFT;
	WWEG32_PWW(WADEON_M_SPWW_WEF_FB_DIV, tmp);

	/* XXX: vewify on diffewent asics */
	tmp = WWEG32_PWW(WADEON_SPWW_CNTW);
	tmp &= ~WADEON_SPWW_PVG_MASK;
	if ((eng_cwock * post_div) >= 90000)
		tmp |= (0x7 << WADEON_SPWW_PVG_SHIFT);
	ewse
		tmp |= (0x4 << WADEON_SPWW_PVG_SHIFT);
	WWEG32_PWW(WADEON_SPWW_CNTW, tmp);

	tmp = WWEG32_PWW(WADEON_SPWW_CNTW);
	tmp &= ~WADEON_SPWW_SWEEP;
	WWEG32_PWW(WADEON_SPWW_CNTW, tmp);

	udeway(2);

	tmp = WWEG32_PWW(WADEON_SPWW_CNTW);
	tmp &= ~WADEON_SPWW_WESET;
	WWEG32_PWW(WADEON_SPWW_CNTW, tmp);

	udeway(200);

	tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
	tmp &= ~WADEON_SCWK_SWC_SEW_MASK;
	switch (post_div) {
	case 1:
	defauwt:
		tmp |= 1;
		bweak;
	case 2:
		tmp |= 2;
		bweak;
	case 4:
		tmp |= 3;
		bweak;
	case 8:
		tmp |= 4;
		bweak;
	}
	WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

	udeway(20);

	tmp = WWEG32_PWW(WADEON_CWK_PIN_CNTW);
	tmp |= WADEON_DONT_USE_XTAWIN;
	WWEG32_PWW(WADEON_CWK_PIN_CNTW, tmp);

	udeway(10);
}

void wadeon_wegacy_set_cwock_gating(stwuct wadeon_device *wdev, int enabwe)
{
	uint32_t tmp;

	if (enabwe) {
		if (wdev->fwags & WADEON_SINGWE_CWTC) {
			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			if ((WWEG32(WADEON_CONFIG_CNTW) &
			     WADEON_CFG_ATI_WEV_ID_MASK) >
			    WADEON_CFG_ATI_WEV_A13) {
				tmp &=
				    ~(WADEON_SCWK_FOWCE_CP |
				      WADEON_SCWK_FOWCE_WB);
			}
			tmp &=
			    ~(WADEON_SCWK_FOWCE_HDP | WADEON_SCWK_FOWCE_DISP1 |
			      WADEON_SCWK_FOWCE_TOP | WADEON_SCWK_FOWCE_SE |
			      WADEON_SCWK_FOWCE_IDCT | WADEON_SCWK_FOWCE_WE |
			      WADEON_SCWK_FOWCE_PB | WADEON_SCWK_FOWCE_TAM |
			      WADEON_SCWK_FOWCE_TDM);
			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);
		} ewse if (ASIC_IS_W300(wdev)) {
			if ((wdev->famiwy == CHIP_WS400) ||
			    (wdev->famiwy == CHIP_WS480)) {
				tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
				tmp &=
				    ~(WADEON_SCWK_FOWCE_DISP2 |
				      WADEON_SCWK_FOWCE_CP |
				      WADEON_SCWK_FOWCE_HDP |
				      WADEON_SCWK_FOWCE_DISP1 |
				      WADEON_SCWK_FOWCE_TOP |
				      WADEON_SCWK_FOWCE_E2 | W300_SCWK_FOWCE_VAP
				      | WADEON_SCWK_FOWCE_IDCT |
				      WADEON_SCWK_FOWCE_VIP | W300_SCWK_FOWCE_SW
				      | W300_SCWK_FOWCE_PX | W300_SCWK_FOWCE_TX
				      | W300_SCWK_FOWCE_US |
				      WADEON_SCWK_FOWCE_TV_SCWK |
				      W300_SCWK_FOWCE_SU |
				      WADEON_SCWK_FOWCE_OV0);
				tmp |= WADEON_DYN_STOP_WAT_MASK;
				tmp |=
				    WADEON_SCWK_FOWCE_TOP |
				    WADEON_SCWK_FOWCE_VIP;
				WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
				tmp &= ~WADEON_SCWK_MOWE_FOWCEON;
				tmp |= WADEON_SCWK_MOWE_MAX_DYN_STOP_WAT;
				WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
				tmp |= (WADEON_PIXCWK_AWWAYS_ONb |
					WADEON_PIXCWK_DAC_AWWAYS_ONb);
				WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
				tmp |= (WADEON_PIX2CWK_AWWAYS_ONb |
					WADEON_PIX2CWK_DAC_AWWAYS_ONb |
					WADEON_DISP_TVOUT_PIXCWK_TV_AWWAYS_ONb |
					W300_DVOCWK_AWWAYS_ONb |
					WADEON_PIXCWK_BWEND_AWWAYS_ONb |
					WADEON_PIXCWK_GV_AWWAYS_ONb |
					W300_PIXCWK_DVO_AWWAYS_ONb |
					WADEON_PIXCWK_WVDS_AWWAYS_ONb |
					WADEON_PIXCWK_TMDS_AWWAYS_ONb |
					W300_PIXCWK_TWANS_AWWAYS_ONb |
					W300_PIXCWK_TVO_AWWAYS_ONb |
					W300_P2G2CWK_AWWAYS_ONb |
					W300_P2G2CWK_DAC_AWWAYS_ONb);
				WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);
			} ewse if (wdev->famiwy >= CHIP_WV350) {
				tmp = WWEG32_PWW(W300_SCWK_CNTW2);
				tmp &= ~(W300_SCWK_FOWCE_TCW |
					 W300_SCWK_FOWCE_GA |
					 W300_SCWK_FOWCE_CBA);
				tmp |= (W300_SCWK_TCW_MAX_DYN_STOP_WAT |
					W300_SCWK_GA_MAX_DYN_STOP_WAT |
					W300_SCWK_CBA_MAX_DYN_STOP_WAT);
				WWEG32_PWW(W300_SCWK_CNTW2, tmp);

				tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
				tmp &=
				    ~(WADEON_SCWK_FOWCE_DISP2 |
				      WADEON_SCWK_FOWCE_CP |
				      WADEON_SCWK_FOWCE_HDP |
				      WADEON_SCWK_FOWCE_DISP1 |
				      WADEON_SCWK_FOWCE_TOP |
				      WADEON_SCWK_FOWCE_E2 | W300_SCWK_FOWCE_VAP
				      | WADEON_SCWK_FOWCE_IDCT |
				      WADEON_SCWK_FOWCE_VIP | W300_SCWK_FOWCE_SW
				      | W300_SCWK_FOWCE_PX | W300_SCWK_FOWCE_TX
				      | W300_SCWK_FOWCE_US |
				      WADEON_SCWK_FOWCE_TV_SCWK |
				      W300_SCWK_FOWCE_SU |
				      WADEON_SCWK_FOWCE_OV0);
				tmp |= WADEON_DYN_STOP_WAT_MASK;
				WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
				tmp &= ~WADEON_SCWK_MOWE_FOWCEON;
				tmp |= WADEON_SCWK_MOWE_MAX_DYN_STOP_WAT;
				WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
				tmp |= (WADEON_PIXCWK_AWWAYS_ONb |
					WADEON_PIXCWK_DAC_AWWAYS_ONb);
				WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
				tmp |= (WADEON_PIX2CWK_AWWAYS_ONb |
					WADEON_PIX2CWK_DAC_AWWAYS_ONb |
					WADEON_DISP_TVOUT_PIXCWK_TV_AWWAYS_ONb |
					W300_DVOCWK_AWWAYS_ONb |
					WADEON_PIXCWK_BWEND_AWWAYS_ONb |
					WADEON_PIXCWK_GV_AWWAYS_ONb |
					W300_PIXCWK_DVO_AWWAYS_ONb |
					WADEON_PIXCWK_WVDS_AWWAYS_ONb |
					WADEON_PIXCWK_TMDS_AWWAYS_ONb |
					W300_PIXCWK_TWANS_AWWAYS_ONb |
					W300_PIXCWK_TVO_AWWAYS_ONb |
					W300_P2G2CWK_AWWAYS_ONb |
					W300_P2G2CWK_DAC_AWWAYS_ONb);
				WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);

				tmp = WWEG32_PWW(WADEON_MCWK_MISC);
				tmp |= (WADEON_MC_MCWK_DYN_ENABWE |
					WADEON_IO_MCWK_DYN_ENABWE);
				WWEG32_PWW(WADEON_MCWK_MISC, tmp);

				tmp = WWEG32_PWW(WADEON_MCWK_CNTW);
				tmp |= (WADEON_FOWCEON_MCWKA |
					WADEON_FOWCEON_MCWKB);

				tmp &= ~(WADEON_FOWCEON_YCWKA |
					 WADEON_FOWCEON_YCWKB |
					 WADEON_FOWCEON_MC);

				/* Some weweases of vbios have set DISABWE_MC_MCWKA
				   and DISABWE_MC_MCWKB bits in the vbios tabwe.  Setting these
				   bits wiww cause H/W hang when weading video memowy with dynamic cwocking
				   enabwed. */
				if ((tmp & W300_DISABWE_MC_MCWKA) &&
				    (tmp & W300_DISABWE_MC_MCWKB)) {
					/* If both bits awe set, then check the active channews */
					tmp = WWEG32_PWW(WADEON_MCWK_CNTW);
					if (wdev->mc.vwam_width == 64) {
						if (WWEG32(WADEON_MEM_CNTW) &
						    W300_MEM_USE_CD_CH_ONWY)
							tmp &=
							    ~W300_DISABWE_MC_MCWKB;
						ewse
							tmp &=
							    ~W300_DISABWE_MC_MCWKA;
					} ewse {
						tmp &= ~(W300_DISABWE_MC_MCWKA |
							 W300_DISABWE_MC_MCWKB);
					}
				}

				WWEG32_PWW(WADEON_MCWK_CNTW, tmp);
			} ewse {
				tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
				tmp &= ~(W300_SCWK_FOWCE_VAP);
				tmp |= WADEON_SCWK_FOWCE_CP;
				WWEG32_PWW(WADEON_SCWK_CNTW, tmp);
				mdeway(15);

				tmp = WWEG32_PWW(W300_SCWK_CNTW2);
				tmp &= ~(W300_SCWK_FOWCE_TCW |
					 W300_SCWK_FOWCE_GA |
					 W300_SCWK_FOWCE_CBA);
				WWEG32_PWW(W300_SCWK_CNTW2, tmp);
			}
		} ewse {
			tmp = WWEG32_PWW(WADEON_CWK_PWWMGT_CNTW);

			tmp &= ~(WADEON_ACTIVE_HIWO_WAT_MASK |
				 WADEON_DISP_DYN_STOP_WAT_MASK |
				 WADEON_DYN_STOP_MODE_MASK);

			tmp |= (WADEON_ENGIN_DYNCWK_MODE |
				(0x01 << WADEON_ACTIVE_HIWO_WAT_SHIFT));
			WWEG32_PWW(WADEON_CWK_PWWMGT_CNTW, tmp);
			mdeway(15);

			tmp = WWEG32_PWW(WADEON_CWK_PIN_CNTW);
			tmp |= WADEON_SCWK_DYN_STAWT_CNTW;
			WWEG32_PWW(WADEON_CWK_PIN_CNTW, tmp);
			mdeway(15);

			/* When DWI is enabwed, setting DYN_STOP_WAT to zewo can cause some W200
			   to wockup wandomwy, weave them as set by BIOS.
			 */
			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			/*tmp &= WADEON_SCWK_SWC_SEW_MASK; */
			tmp &= ~WADEON_SCWK_FOWCEON_MASK;

			/*WAGE_6::A11 A12 A12N1 A13, WV250::A11 A12, W300 */
			if (((wdev->famiwy == CHIP_WV250) &&
			     ((WWEG32(WADEON_CONFIG_CNTW) &
			       WADEON_CFG_ATI_WEV_ID_MASK) <
			      WADEON_CFG_ATI_WEV_A13))
			    || ((wdev->famiwy == CHIP_WV100)
				&&
				((WWEG32(WADEON_CONFIG_CNTW) &
				  WADEON_CFG_ATI_WEV_ID_MASK) <=
				 WADEON_CFG_ATI_WEV_A13))) {
				tmp |= WADEON_SCWK_FOWCE_CP;
				tmp |= WADEON_SCWK_FOWCE_VIP;
			}

			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

			if ((wdev->famiwy == CHIP_WV200) ||
			    (wdev->famiwy == CHIP_WV250) ||
			    (wdev->famiwy == CHIP_WV280)) {
				tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
				tmp &= ~WADEON_SCWK_MOWE_FOWCEON;

				/* WV200::A11 A12 WV250::A11 A12 */
				if (((wdev->famiwy == CHIP_WV200) ||
				     (wdev->famiwy == CHIP_WV250)) &&
				    ((WWEG32(WADEON_CONFIG_CNTW) &
				      WADEON_CFG_ATI_WEV_ID_MASK) <
				     WADEON_CFG_ATI_WEV_A13)) {
					tmp |= WADEON_SCWK_MOWE_FOWCEON;
				}
				WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);
				mdeway(15);
			}

			/* WV200::A11 A12, WV250::A11 A12 */
			if (((wdev->famiwy == CHIP_WV200) ||
			     (wdev->famiwy == CHIP_WV250)) &&
			    ((WWEG32(WADEON_CONFIG_CNTW) &
			      WADEON_CFG_ATI_WEV_ID_MASK) <
			     WADEON_CFG_ATI_WEV_A13)) {
				tmp = WWEG32_PWW(WADEON_PWW_PWWMGT_CNTW);
				tmp |= WADEON_TCW_BYPASS_DISABWE;
				WWEG32_PWW(WADEON_PWW_PWWMGT_CNTW, tmp);
			}
			mdeway(15);

			/*enabwe dynamic mode fow dispway cwocks (PIXCWK and PIX2CWK) */
			tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
			tmp |= (WADEON_PIX2CWK_AWWAYS_ONb |
				WADEON_PIX2CWK_DAC_AWWAYS_ONb |
				WADEON_PIXCWK_BWEND_AWWAYS_ONb |
				WADEON_PIXCWK_GV_AWWAYS_ONb |
				WADEON_PIXCWK_DIG_TMDS_AWWAYS_ONb |
				WADEON_PIXCWK_WVDS_AWWAYS_ONb |
				WADEON_PIXCWK_TMDS_AWWAYS_ONb);

			WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);
			mdeway(15);

			tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
			tmp |= (WADEON_PIXCWK_AWWAYS_ONb |
				WADEON_PIXCWK_DAC_AWWAYS_ONb);

			WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);
			mdeway(15);
		}
	} ewse {
		/* Tuwn evewything OFF (FowceON to evewything) */
		if (wdev->fwags & WADEON_SINGWE_CWTC) {
			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			tmp |= (WADEON_SCWK_FOWCE_CP | WADEON_SCWK_FOWCE_HDP |
				WADEON_SCWK_FOWCE_DISP1 | WADEON_SCWK_FOWCE_TOP
				| WADEON_SCWK_FOWCE_E2 | WADEON_SCWK_FOWCE_SE |
				WADEON_SCWK_FOWCE_IDCT | WADEON_SCWK_FOWCE_VIP |
				WADEON_SCWK_FOWCE_WE | WADEON_SCWK_FOWCE_PB |
				WADEON_SCWK_FOWCE_TAM | WADEON_SCWK_FOWCE_TDM |
				WADEON_SCWK_FOWCE_WB);
			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);
		} ewse if ((wdev->famiwy == CHIP_WS400) ||
			   (wdev->famiwy == CHIP_WS480)) {
			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			tmp |= (WADEON_SCWK_FOWCE_DISP2 | WADEON_SCWK_FOWCE_CP |
				WADEON_SCWK_FOWCE_HDP | WADEON_SCWK_FOWCE_DISP1
				| WADEON_SCWK_FOWCE_TOP | WADEON_SCWK_FOWCE_E2 |
				W300_SCWK_FOWCE_VAP | WADEON_SCWK_FOWCE_IDCT |
				WADEON_SCWK_FOWCE_VIP | W300_SCWK_FOWCE_SW |
				W300_SCWK_FOWCE_PX | W300_SCWK_FOWCE_TX |
				W300_SCWK_FOWCE_US | WADEON_SCWK_FOWCE_TV_SCWK |
				W300_SCWK_FOWCE_SU | WADEON_SCWK_FOWCE_OV0);
			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
			tmp |= WADEON_SCWK_MOWE_FOWCEON;
			WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
			tmp &= ~(WADEON_PIXCWK_AWWAYS_ONb |
				 WADEON_PIXCWK_DAC_AWWAYS_ONb |
				 W300_DISP_DAC_PIXCWK_DAC_BWANK_OFF);
			WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
			tmp &= ~(WADEON_PIX2CWK_AWWAYS_ONb |
				 WADEON_PIX2CWK_DAC_AWWAYS_ONb |
				 WADEON_DISP_TVOUT_PIXCWK_TV_AWWAYS_ONb |
				 W300_DVOCWK_AWWAYS_ONb |
				 WADEON_PIXCWK_BWEND_AWWAYS_ONb |
				 WADEON_PIXCWK_GV_AWWAYS_ONb |
				 W300_PIXCWK_DVO_AWWAYS_ONb |
				 WADEON_PIXCWK_WVDS_AWWAYS_ONb |
				 WADEON_PIXCWK_TMDS_AWWAYS_ONb |
				 W300_PIXCWK_TWANS_AWWAYS_ONb |
				 W300_PIXCWK_TVO_AWWAYS_ONb |
				 W300_P2G2CWK_AWWAYS_ONb |
				 W300_P2G2CWK_DAC_AWWAYS_ONb |
				 W300_DISP_DAC_PIXCWK_DAC2_BWANK_OFF);
			WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);
		} ewse if (wdev->famiwy >= CHIP_WV350) {
			/* fow WV350/M10, no deways awe wequiwed. */
			tmp = WWEG32_PWW(W300_SCWK_CNTW2);
			tmp |= (W300_SCWK_FOWCE_TCW |
				W300_SCWK_FOWCE_GA | W300_SCWK_FOWCE_CBA);
			WWEG32_PWW(W300_SCWK_CNTW2, tmp);

			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			tmp |= (WADEON_SCWK_FOWCE_DISP2 | WADEON_SCWK_FOWCE_CP |
				WADEON_SCWK_FOWCE_HDP | WADEON_SCWK_FOWCE_DISP1
				| WADEON_SCWK_FOWCE_TOP | WADEON_SCWK_FOWCE_E2 |
				W300_SCWK_FOWCE_VAP | WADEON_SCWK_FOWCE_IDCT |
				WADEON_SCWK_FOWCE_VIP | W300_SCWK_FOWCE_SW |
				W300_SCWK_FOWCE_PX | W300_SCWK_FOWCE_TX |
				W300_SCWK_FOWCE_US | WADEON_SCWK_FOWCE_TV_SCWK |
				W300_SCWK_FOWCE_SU | WADEON_SCWK_FOWCE_OV0);
			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
			tmp |= WADEON_SCWK_MOWE_FOWCEON;
			WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_MCWK_CNTW);
			tmp |= (WADEON_FOWCEON_MCWKA |
				WADEON_FOWCEON_MCWKB |
				WADEON_FOWCEON_YCWKA |
				WADEON_FOWCEON_YCWKB | WADEON_FOWCEON_MC);
			WWEG32_PWW(WADEON_MCWK_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
			tmp &= ~(WADEON_PIXCWK_AWWAYS_ONb |
				 WADEON_PIXCWK_DAC_AWWAYS_ONb |
				 W300_DISP_DAC_PIXCWK_DAC_BWANK_OFF);
			WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);

			tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
			tmp &= ~(WADEON_PIX2CWK_AWWAYS_ONb |
				 WADEON_PIX2CWK_DAC_AWWAYS_ONb |
				 WADEON_DISP_TVOUT_PIXCWK_TV_AWWAYS_ONb |
				 W300_DVOCWK_AWWAYS_ONb |
				 WADEON_PIXCWK_BWEND_AWWAYS_ONb |
				 WADEON_PIXCWK_GV_AWWAYS_ONb |
				 W300_PIXCWK_DVO_AWWAYS_ONb |
				 WADEON_PIXCWK_WVDS_AWWAYS_ONb |
				 WADEON_PIXCWK_TMDS_AWWAYS_ONb |
				 W300_PIXCWK_TWANS_AWWAYS_ONb |
				 W300_PIXCWK_TVO_AWWAYS_ONb |
				 W300_P2G2CWK_AWWAYS_ONb |
				 W300_P2G2CWK_DAC_AWWAYS_ONb |
				 W300_DISP_DAC_PIXCWK_DAC2_BWANK_OFF);
			WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);
		} ewse {
			tmp = WWEG32_PWW(WADEON_SCWK_CNTW);
			tmp |= (WADEON_SCWK_FOWCE_CP | WADEON_SCWK_FOWCE_E2);
			tmp |= WADEON_SCWK_FOWCE_SE;

			if (wdev->fwags & WADEON_SINGWE_CWTC) {
				tmp |= (WADEON_SCWK_FOWCE_WB |
					WADEON_SCWK_FOWCE_TDM |
					WADEON_SCWK_FOWCE_TAM |
					WADEON_SCWK_FOWCE_PB |
					WADEON_SCWK_FOWCE_WE |
					WADEON_SCWK_FOWCE_VIP |
					WADEON_SCWK_FOWCE_IDCT |
					WADEON_SCWK_FOWCE_TOP |
					WADEON_SCWK_FOWCE_DISP1 |
					WADEON_SCWK_FOWCE_DISP2 |
					WADEON_SCWK_FOWCE_HDP);
			} ewse if ((wdev->famiwy == CHIP_W300) ||
				   (wdev->famiwy == CHIP_W350)) {
				tmp |= (WADEON_SCWK_FOWCE_HDP |
					WADEON_SCWK_FOWCE_DISP1 |
					WADEON_SCWK_FOWCE_DISP2 |
					WADEON_SCWK_FOWCE_TOP |
					WADEON_SCWK_FOWCE_IDCT |
					WADEON_SCWK_FOWCE_VIP);
			}
			WWEG32_PWW(WADEON_SCWK_CNTW, tmp);

			mdeway(16);

			if ((wdev->famiwy == CHIP_W300) ||
			    (wdev->famiwy == CHIP_W350)) {
				tmp = WWEG32_PWW(W300_SCWK_CNTW2);
				tmp |= (W300_SCWK_FOWCE_TCW |
					W300_SCWK_FOWCE_GA |
					W300_SCWK_FOWCE_CBA);
				WWEG32_PWW(W300_SCWK_CNTW2, tmp);
				mdeway(16);
			}

			if (wdev->fwags & WADEON_IS_IGP) {
				tmp = WWEG32_PWW(WADEON_MCWK_CNTW);
				tmp &= ~(WADEON_FOWCEON_MCWKA |
					 WADEON_FOWCEON_YCWKA);
				WWEG32_PWW(WADEON_MCWK_CNTW, tmp);
				mdeway(16);
			}

			if ((wdev->famiwy == CHIP_WV200) ||
			    (wdev->famiwy == CHIP_WV250) ||
			    (wdev->famiwy == CHIP_WV280)) {
				tmp = WWEG32_PWW(WADEON_SCWK_MOWE_CNTW);
				tmp |= WADEON_SCWK_MOWE_FOWCEON;
				WWEG32_PWW(WADEON_SCWK_MOWE_CNTW, tmp);
				mdeway(16);
			}

			tmp = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
			tmp &= ~(WADEON_PIX2CWK_AWWAYS_ONb |
				 WADEON_PIX2CWK_DAC_AWWAYS_ONb |
				 WADEON_PIXCWK_BWEND_AWWAYS_ONb |
				 WADEON_PIXCWK_GV_AWWAYS_ONb |
				 WADEON_PIXCWK_DIG_TMDS_AWWAYS_ONb |
				 WADEON_PIXCWK_WVDS_AWWAYS_ONb |
				 WADEON_PIXCWK_TMDS_AWWAYS_ONb);

			WWEG32_PWW(WADEON_PIXCWKS_CNTW, tmp);
			mdeway(16);

			tmp = WWEG32_PWW(WADEON_VCWK_ECP_CNTW);
			tmp &= ~(WADEON_PIXCWK_AWWAYS_ONb |
				 WADEON_PIXCWK_DAC_AWWAYS_ONb);
			WWEG32_PWW(WADEON_VCWK_ECP_CNTW, tmp);
		}
	}
}

