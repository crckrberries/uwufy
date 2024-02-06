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
/* WS600 / Wadeon X1250/X1270 integwated GPU
 *
 * This fiwe gathew function specific to WS600 which is the IGP of
 * the X1250/X1270 famiwy suppowting intew CPU (whiwe WS690/WS740
 * is the X1250/X1270 suppowting AMD CPU). The dispway engine awe
 * the avivo one, bios is an atombios, 3D bwock awe the one of the
 * W4XX famiwy. The GAWT is diffewent fwom the WS400 one and is vewy
 * cwose to the one of the W600 famiwy (W600 wikewy being an evowution
 * of the WS600 GAWT bwock).
 */

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "ws600_weg_safe.h"
#incwude "ws600d.h"

static void ws600_gpu_init(stwuct wadeon_device *wdev);
int ws600_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

static const u32 cwtc_offsets[2] =
{
	0,
	AVIVO_D2CWTC_H_TOTAW - AVIVO_D1CWTC_H_TOTAW
};

static boow avivo_is_in_vbwank(stwuct wadeon_device *wdev, int cwtc)
{
	if (WWEG32(AVIVO_D1CWTC_STATUS + cwtc_offsets[cwtc]) & AVIVO_D1CWTC_V_BWANK)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow avivo_is_countew_moving(stwuct wadeon_device *wdev, int cwtc)
{
	u32 pos1, pos2;

	pos1 = WWEG32(AVIVO_D1CWTC_STATUS_POSITION + cwtc_offsets[cwtc]);
	pos2 = WWEG32(AVIVO_D1CWTC_STATUS_POSITION + cwtc_offsets[cwtc]);

	if (pos1 != pos2)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * avivo_wait_fow_vbwank - vbwank wait asic cawwback.
 *
 * @wdev: wadeon_device pointew
 * @cwtc: cwtc to wait fow vbwank on
 *
 * Wait fow vbwank on the wequested cwtc (w5xx-w7xx).
 */
void avivo_wait_fow_vbwank(stwuct wadeon_device *wdev, int cwtc)
{
	unsigned i = 0;

	if (cwtc >= wdev->num_cwtc)
		wetuwn;

	if (!(WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[cwtc]) & AVIVO_CWTC_EN))
		wetuwn;

	/* depending on when we hit vbwank, we may be cwose to active; if so,
	 * wait fow anothew fwame.
	 */
	whiwe (avivo_is_in_vbwank(wdev, cwtc)) {
		if (i++ % 100 == 0) {
			if (!avivo_is_countew_moving(wdev, cwtc))
				bweak;
		}
	}

	whiwe (!avivo_is_in_vbwank(wdev, cwtc)) {
		if (i++ % 100 == 0) {
			if (!avivo_is_countew_moving(wdev, cwtc))
				bweak;
		}
	}
}

void ws600_page_fwip(stwuct wadeon_device *wdev, int cwtc_id, u64 cwtc_base, boow async)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];
	stwuct dwm_fwamebuffew *fb = wadeon_cwtc->base.pwimawy->fb;
	u32 tmp = WWEG32(AVIVO_D1GWPH_UPDATE + wadeon_cwtc->cwtc_offset);
	int i;

	/* Wock the gwaphics update wock */
	tmp |= AVIVO_D1GWPH_UPDATE_WOCK;
	WWEG32(AVIVO_D1GWPH_UPDATE + wadeon_cwtc->cwtc_offset, tmp);

	/* fwip at hsync fow async, defauwt is vsync */
	WWEG32(AVIVO_D1GWPH_FWIP_CONTWOW + wadeon_cwtc->cwtc_offset,
	       async ? AVIVO_D1GWPH_SUWFACE_UPDATE_H_WETWACE_EN : 0);
	/* update pitch */
	WWEG32(AVIVO_D1GWPH_PITCH + wadeon_cwtc->cwtc_offset,
	       fb->pitches[0] / fb->fowmat->cpp[0]);
	/* update the scanout addwesses */
	WWEG32(AVIVO_D1GWPH_SECONDAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32)cwtc_base);
	WWEG32(AVIVO_D1GWPH_PWIMAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32)cwtc_base);

	/* Wait fow update_pending to go high. */
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(AVIVO_D1GWPH_UPDATE + wadeon_cwtc->cwtc_offset) & AVIVO_D1GWPH_SUWFACE_UPDATE_PENDING)
			bweak;
		udeway(1);
	}
	DWM_DEBUG("Update pending now high. Unwocking vupdate_wock.\n");

	/* Unwock the wock, so doubwe-buffewing can take pwace inside vbwank */
	tmp &= ~AVIVO_D1GWPH_UPDATE_WOCK;
	WWEG32(AVIVO_D1GWPH_UPDATE + wadeon_cwtc->cwtc_offset, tmp);
}

boow ws600_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc_id)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];

	/* Wetuwn cuwwent update_pending status: */
	wetuwn !!(WWEG32(AVIVO_D1GWPH_UPDATE + wadeon_cwtc->cwtc_offset) &
		AVIVO_D1GWPH_SUWFACE_UPDATE_PENDING);
}

void avivo_pwogwam_fmt(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	int bpc = 0;
	u32 tmp = 0;
	enum wadeon_connectow_dithew dithew = WADEON_FMT_DITHEW_DISABWE;

	if (connectow) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		bpc = wadeon_get_monitow_bpc(connectow);
		dithew = wadeon_connectow->dithew;
	}

	/* WVDS FMT is set up by atom */
	if (wadeon_encodew->devices & ATOM_DEVICE_WCD_SUPPOWT)
		wetuwn;

	if (bpc == 0)
		wetuwn;

	switch (bpc) {
	case 6:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= AVIVO_TMDS_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_EN;
		ewse
			tmp |= AVIVO_TMDS_BIT_DEPTH_CONTWOW_TWUNCATE_EN;
		bweak;
	case 8:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (AVIVO_TMDS_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_EN |
				AVIVO_TMDS_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_DEPTH);
		ewse
			tmp |= (AVIVO_TMDS_BIT_DEPTH_CONTWOW_TWUNCATE_EN |
				AVIVO_TMDS_BIT_DEPTH_CONTWOW_TWUNCATE_DEPTH);
		bweak;
	case 10:
	defauwt:
		/* not needed */
		bweak;
	}

	switch (wadeon_encodew->encodew_id) {
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_TMDS1:
		WWEG32(AVIVO_TMDSA_BIT_DEPTH_CONTWOW, tmp);
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_WVTM1:
		WWEG32(AVIVO_WVTMA_BIT_DEPTH_CONTWOW, tmp);
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1:
		WWEG32(AVIVO_DVOA_BIT_DEPTH_CONTWOW, tmp);
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_DDI:
		WWEG32(AVIVO_DDIA_BIT_DEPTH_CONTWOW, tmp);
		bweak;
	defauwt:
		bweak;
	}
}

void ws600_pm_misc(stwuct wadeon_device *wdev)
{
	int wequested_index = wdev->pm.wequested_powew_state_index;
	stwuct wadeon_powew_state *ps = &wdev->pm.powew_state[wequested_index];
	stwuct wadeon_vowtage *vowtage = &ps->cwock_info[0].vowtage;
	u32 tmp, dyn_pwwmgt_scwk_wength, dyn_scwk_vow_cntw;
	u32 hdp_dyn_cntw, /*mc_host_dyn_cntw,*/ dyn_backbias_cntw;

	if ((vowtage->type == VOWTAGE_GPIO) && (vowtage->gpio.vawid)) {
		if (ps->misc & ATOM_PM_MISCINFO_VOWTAGE_DWOP_SUPPOWT) {
			tmp = WWEG32(vowtage->gpio.weg);
			if (vowtage->active_high)
				tmp |= vowtage->gpio.mask;
			ewse
				tmp &= ~(vowtage->gpio.mask);
			WWEG32(vowtage->gpio.weg, tmp);
			if (vowtage->deway)
				udeway(vowtage->deway);
		} ewse {
			tmp = WWEG32(vowtage->gpio.weg);
			if (vowtage->active_high)
				tmp &= ~vowtage->gpio.mask;
			ewse
				tmp |= vowtage->gpio.mask;
			WWEG32(vowtage->gpio.weg, tmp);
			if (vowtage->deway)
				udeway(vowtage->deway);
		}
	} ewse if (vowtage->type == VOWTAGE_VDDC)
		wadeon_atom_set_vowtage(wdev, vowtage->vddc_id, SET_VOWTAGE_TYPE_ASIC_VDDC);

	dyn_pwwmgt_scwk_wength = WWEG32_PWW(DYN_PWWMGT_SCWK_WENGTH);
	dyn_pwwmgt_scwk_wength &= ~WEDUCED_POWEW_SCWK_HIWEN(0xf);
	dyn_pwwmgt_scwk_wength &= ~WEDUCED_POWEW_SCWK_WOWEN(0xf);
	if (ps->misc & ATOM_PM_MISCINFO_ASIC_WEDUCED_SPEED_SCWK_EN) {
		if (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CWOCK_DIVIDEW_BY_2) {
			dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_HIWEN(2);
			dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_WOWEN(2);
		} ewse if (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CWOCK_DIVIDEW_BY_4) {
			dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_HIWEN(4);
			dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_WOWEN(4);
		}
	} ewse {
		dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_HIWEN(1);
		dyn_pwwmgt_scwk_wength |= WEDUCED_POWEW_SCWK_WOWEN(1);
	}
	WWEG32_PWW(DYN_PWWMGT_SCWK_WENGTH, dyn_pwwmgt_scwk_wength);

	dyn_scwk_vow_cntw = WWEG32_PWW(DYN_SCWK_VOW_CNTW);
	if (ps->misc & ATOM_PM_MISCINFO_ASIC_DYNAMIC_VOWTAGE_EN) {
		dyn_scwk_vow_cntw |= IO_CG_VOWTAGE_DWOP;
		if (vowtage->deway) {
			dyn_scwk_vow_cntw |= VOWTAGE_DWOP_SYNC;
			dyn_scwk_vow_cntw |= VOWTAGE_DEWAY_SEW(vowtage->deway);
		} ewse
			dyn_scwk_vow_cntw &= ~VOWTAGE_DWOP_SYNC;
	} ewse
		dyn_scwk_vow_cntw &= ~IO_CG_VOWTAGE_DWOP;
	WWEG32_PWW(DYN_SCWK_VOW_CNTW, dyn_scwk_vow_cntw);

	hdp_dyn_cntw = WWEG32_PWW(HDP_DYN_CNTW);
	if (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_HDP_BWOCK_EN)
		hdp_dyn_cntw &= ~HDP_FOWCEON;
	ewse
		hdp_dyn_cntw |= HDP_FOWCEON;
	WWEG32_PWW(HDP_DYN_CNTW, hdp_dyn_cntw);
#if 0
	/* mc_host_dyn seems to cause hangs fwom time to time */
	mc_host_dyn_cntw = WWEG32_PWW(MC_HOST_DYN_CNTW);
	if (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_MC_HOST_BWOCK_EN)
		mc_host_dyn_cntw &= ~MC_HOST_FOWCEON;
	ewse
		mc_host_dyn_cntw |= MC_HOST_FOWCEON;
	WWEG32_PWW(MC_HOST_DYN_CNTW, mc_host_dyn_cntw);
#endif
	dyn_backbias_cntw = WWEG32_PWW(DYN_BACKBIAS_CNTW);
	if (ps->misc & ATOM_PM_MISCINFO2_DYNAMIC_BACK_BIAS_EN)
		dyn_backbias_cntw |= IO_CG_BACKBIAS_EN;
	ewse
		dyn_backbias_cntw &= ~IO_CG_BACKBIAS_EN;
	WWEG32_PWW(DYN_BACKBIAS_CNTW, dyn_backbias_cntw);

	/* set pcie wanes */
	if ((wdev->fwags & WADEON_IS_PCIE) &&
	    !(wdev->fwags & WADEON_IS_IGP) &&
	    wdev->asic->pm.set_pcie_wanes &&
	    (ps->pcie_wanes !=
	     wdev->pm.powew_state[wdev->pm.cuwwent_powew_state_index].pcie_wanes)) {
		wadeon_set_pcie_wanes(wdev,
				      ps->pcie_wanes);
		DWM_DEBUG("Setting: p: %d\n", ps->pcie_wanes);
	}
}

void ws600_pm_pwepawe(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 tmp;

	/* disabwe any active CWTCs */
	wist_fow_each_entwy(cwtc, &ddev->mode_config.cwtc_wist, head) {
		wadeon_cwtc = to_wadeon_cwtc(cwtc);
		if (wadeon_cwtc->enabwed) {
			tmp = WWEG32(AVIVO_D1CWTC_CONTWOW + wadeon_cwtc->cwtc_offset);
			tmp |= AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE;
			WWEG32(AVIVO_D1CWTC_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
		}
	}
}

void ws600_pm_finish(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 tmp;

	/* enabwe any active CWTCs */
	wist_fow_each_entwy(cwtc, &ddev->mode_config.cwtc_wist, head) {
		wadeon_cwtc = to_wadeon_cwtc(cwtc);
		if (wadeon_cwtc->enabwed) {
			tmp = WWEG32(AVIVO_D1CWTC_CONTWOW + wadeon_cwtc->cwtc_offset);
			tmp &= ~AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE;
			WWEG32(AVIVO_D1CWTC_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
		}
	}
}

/* hpd fow digitaw panew detect/disconnect */
boow ws600_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd)
{
	u32 tmp;
	boow connected = fawse;

	switch (hpd) {
	case WADEON_HPD_1:
		tmp = WWEG32(W_007D04_DC_HOT_PWUG_DETECT1_INT_STATUS);
		if (G_007D04_DC_HOT_PWUG_DETECT1_SENSE(tmp))
			connected = twue;
		bweak;
	case WADEON_HPD_2:
		tmp = WWEG32(W_007D14_DC_HOT_PWUG_DETECT2_INT_STATUS);
		if (G_007D14_DC_HOT_PWUG_DETECT2_SENSE(tmp))
			connected = twue;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn connected;
}

void ws600_hpd_set_powawity(stwuct wadeon_device *wdev,
			    enum wadeon_hpd_id hpd)
{
	u32 tmp;
	boow connected = ws600_hpd_sense(wdev, hpd);

	switch (hpd) {
	case WADEON_HPD_1:
		tmp = WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW);
		if (connected)
			tmp &= ~S_007D08_DC_HOT_PWUG_DETECT1_INT_POWAWITY(1);
		ewse
			tmp |= S_007D08_DC_HOT_PWUG_DETECT1_INT_POWAWITY(1);
		WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW, tmp);
		bweak;
	case WADEON_HPD_2:
		tmp = WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW);
		if (connected)
			tmp &= ~S_007D18_DC_HOT_PWUG_DETECT2_INT_POWAWITY(1);
		ewse
			tmp |= S_007D18_DC_HOT_PWUG_DETECT2_INT_POWAWITY(1);
		WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW, tmp);
		bweak;
	defauwt:
		bweak;
	}
}

void ws600_hpd_init(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned enabwe = 0;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		switch (wadeon_connectow->hpd.hpd) {
		case WADEON_HPD_1:
			WWEG32(W_007D00_DC_HOT_PWUG_DETECT1_CONTWOW,
			       S_007D00_DC_HOT_PWUG_DETECT1_EN(1));
			bweak;
		case WADEON_HPD_2:
			WWEG32(W_007D10_DC_HOT_PWUG_DETECT2_CONTWOW,
			       S_007D10_DC_HOT_PWUG_DETECT2_EN(1));
			bweak;
		defauwt:
			bweak;
		}
		if (wadeon_connectow->hpd.hpd != WADEON_HPD_NONE)
			enabwe |= 1 << wadeon_connectow->hpd.hpd;
		wadeon_hpd_set_powawity(wdev, wadeon_connectow->hpd.hpd);
	}
	wadeon_iwq_kms_enabwe_hpd(wdev, enabwe);
}

void ws600_hpd_fini(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned disabwe = 0;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		switch (wadeon_connectow->hpd.hpd) {
		case WADEON_HPD_1:
			WWEG32(W_007D00_DC_HOT_PWUG_DETECT1_CONTWOW,
			       S_007D00_DC_HOT_PWUG_DETECT1_EN(0));
			bweak;
		case WADEON_HPD_2:
			WWEG32(W_007D10_DC_HOT_PWUG_DETECT2_CONTWOW,
			       S_007D10_DC_HOT_PWUG_DETECT2_EN(0));
			bweak;
		defauwt:
			bweak;
		}
		if (wadeon_connectow->hpd.hpd != WADEON_HPD_NONE)
			disabwe |= 1 << wadeon_connectow->hpd.hpd;
	}
	wadeon_iwq_kms_disabwe_hpd(wdev, disabwe);
}

int ws600_asic_weset(stwuct wadeon_device *wdev, boow hawd)
{
	stwuct wv515_mc_save save;
	u32 status, tmp;
	int wet = 0;

	status = WWEG32(W_000E40_WBBM_STATUS);
	if (!G_000E40_GUI_ACTIVE(status)) {
		wetuwn 0;
	}
	/* Stops aww mc cwients */
	wv515_mc_stop(wdev, &save);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* stop CP */
	WWEG32(WADEON_CP_CSQ_CNTW, 0);
	tmp = WWEG32(WADEON_CP_WB_CNTW);
	WWEG32(WADEON_CP_WB_CNTW, tmp | WADEON_WB_WPTW_WW_ENA);
	WWEG32(WADEON_CP_WB_WPTW_WW, 0);
	WWEG32(WADEON_CP_WB_WPTW, 0);
	WWEG32(WADEON_CP_WB_CNTW, tmp);
	pci_save_state(wdev->pdev);
	/* disabwe bus mastewing */
	pci_cweaw_mastew(wdev->pdev);
	mdeway(1);
	/* weset GA+VAP */
	WWEG32(W_0000F0_WBBM_SOFT_WESET, S_0000F0_SOFT_WESET_VAP(1) |
					S_0000F0_SOFT_WESET_GA(1));
	WWEG32(W_0000F0_WBBM_SOFT_WESET);
	mdeway(500);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, 0);
	mdeway(1);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* weset CP */
	WWEG32(W_0000F0_WBBM_SOFT_WESET, S_0000F0_SOFT_WESET_CP(1));
	WWEG32(W_0000F0_WBBM_SOFT_WESET);
	mdeway(500);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, 0);
	mdeway(1);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* weset MC */
	WWEG32(W_0000F0_WBBM_SOFT_WESET, S_0000F0_SOFT_WESET_MC(1));
	WWEG32(W_0000F0_WBBM_SOFT_WESET);
	mdeway(500);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, 0);
	mdeway(1);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* westowe PCI & busmastewing */
	pci_westowe_state(wdev->pdev);
	/* Check if GPU is idwe */
	if (G_000E40_GA_BUSY(status) || G_000E40_VAP_BUSY(status)) {
		dev_eww(wdev->dev, "faiwed to weset GPU\n");
		wet = -1;
	} ewse
		dev_info(wdev->dev, "GPU weset succeed\n");
	wv515_mc_wesume(wdev, &save);
	wetuwn wet;
}

/*
 * GAWT.
 */
void ws600_gawt_twb_fwush(stwuct wadeon_device *wdev)
{
	uint32_t tmp;

	tmp = WWEG32_MC(W_000100_MC_PT0_CNTW);
	tmp &= C_000100_INVAWIDATE_AWW_W1_TWBS & C_000100_INVAWIDATE_W2_CACHE;
	WWEG32_MC(W_000100_MC_PT0_CNTW, tmp);

	tmp = WWEG32_MC(W_000100_MC_PT0_CNTW);
	tmp |= S_000100_INVAWIDATE_AWW_W1_TWBS(1) | S_000100_INVAWIDATE_W2_CACHE(1);
	WWEG32_MC(W_000100_MC_PT0_CNTW, tmp);

	tmp = WWEG32_MC(W_000100_MC_PT0_CNTW);
	tmp &= C_000100_INVAWIDATE_AWW_W1_TWBS & C_000100_INVAWIDATE_W2_CACHE;
	WWEG32_MC(W_000100_MC_PT0_CNTW, tmp);
	tmp = WWEG32_MC(W_000100_MC_PT0_CNTW);
}

static int ws600_gawt_init(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->gawt.wobj) {
		WAWN(1, "WS600 GAWT awweady initiawized\n");
		wetuwn 0;
	}
	/* Initiawize common gawt stwuctuwe */
	w = wadeon_gawt_init(wdev);
	if (w) {
		wetuwn w;
	}
	wdev->gawt.tabwe_size = wdev->gawt.num_gpu_pages * 8;
	wetuwn wadeon_gawt_tabwe_vwam_awwoc(wdev);
}

static int ws600_gawt_enabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int w, i;

	if (wdev->gawt.wobj == NUWW) {
		dev_eww(wdev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	w = wadeon_gawt_tabwe_vwam_pin(wdev);
	if (w)
		wetuwn w;
	/* Enabwe bus mastew */
	tmp = WWEG32(WADEON_BUS_CNTW) & ~WS600_BUS_MASTEW_DIS;
	WWEG32(WADEON_BUS_CNTW, tmp);
	/* FIXME: setup defauwt page */
	WWEG32_MC(W_000100_MC_PT0_CNTW,
		  (S_000100_EFFECTIVE_W2_CACHE_SIZE(6) |
		   S_000100_EFFECTIVE_W2_QUEUE_SIZE(6)));

	fow (i = 0; i < 19; i++) {
		WWEG32_MC(W_00016C_MC_PT0_CWIENT0_CNTW + i,
			  S_00016C_ENABWE_TWANSWATION_MODE_OVEWWIDE(1) |
			  S_00016C_SYSTEM_ACCESS_MODE_MASK(
				  V_00016C_SYSTEM_ACCESS_MODE_NOT_IN_SYS) |
			  S_00016C_SYSTEM_APEWTUWE_UNMAPPED_ACCESS(
				  V_00016C_SYSTEM_APEWTUWE_UNMAPPED_PASSTHWOUGH) |
			  S_00016C_EFFECTIVE_W1_CACHE_SIZE(3) |
			  S_00016C_ENABWE_FWAGMENT_PWOCESSING(1) |
			  S_00016C_EFFECTIVE_W1_QUEUE_SIZE(3));
	}
	/* enabwe fiwst context */
	WWEG32_MC(W_000102_MC_PT0_CONTEXT0_CNTW,
		  S_000102_ENABWE_PAGE_TABWE(1) |
		  S_000102_PAGE_TABWE_DEPTH(V_000102_PAGE_TABWE_FWAT));

	/* disabwe aww othew contexts */
	fow (i = 1; i < 8; i++)
		WWEG32_MC(W_000102_MC_PT0_CONTEXT0_CNTW + i, 0);

	/* setup the page tabwe */
	WWEG32_MC(W_00012C_MC_PT0_CONTEXT0_FWAT_BASE_ADDW,
		  wdev->gawt.tabwe_addw);
	WWEG32_MC(W_00013C_MC_PT0_CONTEXT0_FWAT_STAWT_ADDW, wdev->mc.gtt_stawt);
	WWEG32_MC(W_00014C_MC_PT0_CONTEXT0_FWAT_END_ADDW, wdev->mc.gtt_end);
	WWEG32_MC(W_00011C_MC_PT0_CONTEXT0_DEFAUWT_WEAD_ADDW, 0);

	/* System context maps to VWAM space */
	WWEG32_MC(W_000112_MC_PT0_SYSTEM_APEWTUWE_WOW_ADDW, wdev->mc.vwam_stawt);
	WWEG32_MC(W_000114_MC_PT0_SYSTEM_APEWTUWE_HIGH_ADDW, wdev->mc.vwam_end);

	/* enabwe page tabwes */
	tmp = WWEG32_MC(W_000100_MC_PT0_CNTW);
	WWEG32_MC(W_000100_MC_PT0_CNTW, (tmp | S_000100_ENABWE_PT(1)));
	tmp = WWEG32_MC(W_000009_MC_CNTW1);
	WWEG32_MC(W_000009_MC_CNTW1, (tmp | S_000009_ENABWE_PAGE_TABWES(1)));
	ws600_gawt_twb_fwush(wdev);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned)(wdev->mc.gtt_size >> 20),
		 (unsigned wong wong)wdev->gawt.tabwe_addw);
	wdev->gawt.weady = twue;
	wetuwn 0;
}

static void ws600_gawt_disabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;

	/* FIXME: disabwe out of gawt access */
	WWEG32_MC(W_000100_MC_PT0_CNTW, 0);
	tmp = WWEG32_MC(W_000009_MC_CNTW1);
	WWEG32_MC(W_000009_MC_CNTW1, tmp & C_000009_ENABWE_PAGE_TABWES);
	wadeon_gawt_tabwe_vwam_unpin(wdev);
}

static void ws600_gawt_fini(stwuct wadeon_device *wdev)
{
	wadeon_gawt_fini(wdev);
	ws600_gawt_disabwe(wdev);
	wadeon_gawt_tabwe_vwam_fwee(wdev);
}

uint64_t ws600_gawt_get_page_entwy(uint64_t addw, uint32_t fwags)
{
	addw = addw & 0xFFFFFFFFFFFFF000UWW;
	addw |= W600_PTE_SYSTEM;
	if (fwags & WADEON_GAWT_PAGE_VAWID)
		addw |= W600_PTE_VAWID;
	if (fwags & WADEON_GAWT_PAGE_WEAD)
		addw |= W600_PTE_WEADABWE;
	if (fwags & WADEON_GAWT_PAGE_WWITE)
		addw |= W600_PTE_WWITEABWE;
	if (fwags & WADEON_GAWT_PAGE_SNOOP)
		addw |= W600_PTE_SNOOPED;
	wetuwn addw;
}

void ws600_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
			 uint64_t entwy)
{
	void __iomem *ptw = (void *)wdev->gawt.ptw;
	wwiteq(entwy, ptw + (i * 8));
}

int ws600_iwq_set(stwuct wadeon_device *wdev)
{
	uint32_t tmp = 0;
	uint32_t mode_int = 0;
	u32 hpd1 = WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW) &
		~S_007D08_DC_HOT_PWUG_DETECT1_INT_EN(1);
	u32 hpd2 = WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW) &
		~S_007D18_DC_HOT_PWUG_DETECT2_INT_EN(1);
	u32 hdmi0;
	if (ASIC_IS_DCE2(wdev))
		hdmi0 = WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW) &
			~S_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK(1);
	ewse
		hdmi0 = 0;

	if (!wdev->iwq.instawwed) {
		WAWN(1, "Can't enabwe IWQ/MSI because no handwew is instawwed\n");
		WWEG32(W_000040_GEN_INT_CNTW, 0);
		wetuwn -EINVAW;
	}
	if (atomic_wead(&wdev->iwq.wing_int[WADEON_WING_TYPE_GFX_INDEX])) {
		tmp |= S_000040_SW_INT_EN(1);
	}
	if (wdev->iwq.cwtc_vbwank_int[0] ||
	    atomic_wead(&wdev->iwq.pfwip[0])) {
		mode_int |= S_006540_D1MODE_VBWANK_INT_MASK(1);
	}
	if (wdev->iwq.cwtc_vbwank_int[1] ||
	    atomic_wead(&wdev->iwq.pfwip[1])) {
		mode_int |= S_006540_D2MODE_VBWANK_INT_MASK(1);
	}
	if (wdev->iwq.hpd[0]) {
		hpd1 |= S_007D08_DC_HOT_PWUG_DETECT1_INT_EN(1);
	}
	if (wdev->iwq.hpd[1]) {
		hpd2 |= S_007D18_DC_HOT_PWUG_DETECT2_INT_EN(1);
	}
	if (wdev->iwq.afmt[0]) {
		hdmi0 |= S_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK(1);
	}
	WWEG32(W_000040_GEN_INT_CNTW, tmp);
	WWEG32(W_006540_DxMODE_INT_MASK, mode_int);
	WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW, hpd1);
	WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW, hpd2);
	if (ASIC_IS_DCE2(wdev))
		WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW, hdmi0);

	/* posting wead */
	WWEG32(W_000040_GEN_INT_CNTW);

	wetuwn 0;
}

static inwine u32 ws600_iwq_ack(stwuct wadeon_device *wdev)
{
	uint32_t iwqs = WWEG32(W_000044_GEN_INT_STATUS);
	uint32_t iwq_mask = S_000044_SW_INT(1);
	u32 tmp;

	if (G_000044_DISPWAY_INT_STAT(iwqs)) {
		wdev->iwq.stat_wegs.w500.disp_int = WWEG32(W_007EDC_DISP_INTEWWUPT_STATUS);
		if (G_007EDC_WB_D1_VBWANK_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			WWEG32(W_006534_D1MODE_VBWANK_STATUS,
				S_006534_D1MODE_VBWANK_ACK(1));
		}
		if (G_007EDC_WB_D2_VBWANK_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			WWEG32(W_006D34_D2MODE_VBWANK_STATUS,
				S_006D34_D2MODE_VBWANK_ACK(1));
		}
		if (G_007EDC_DC_HOT_PWUG_DETECT1_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			tmp = WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW);
			tmp |= S_007D08_DC_HOT_PWUG_DETECT1_INT_ACK(1);
			WWEG32(W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW, tmp);
		}
		if (G_007EDC_DC_HOT_PWUG_DETECT2_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			tmp = WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW);
			tmp |= S_007D18_DC_HOT_PWUG_DETECT2_INT_ACK(1);
			WWEG32(W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW, tmp);
		}
	} ewse {
		wdev->iwq.stat_wegs.w500.disp_int = 0;
	}

	if (ASIC_IS_DCE2(wdev)) {
		wdev->iwq.stat_wegs.w500.hdmi0_status = WWEG32(W_007404_HDMI0_STATUS) &
			S_007404_HDMI0_AZ_FOWMAT_WTWIG(1);
		if (G_007404_HDMI0_AZ_FOWMAT_WTWIG(wdev->iwq.stat_wegs.w500.hdmi0_status)) {
			tmp = WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW);
			tmp |= S_007408_HDMI0_AZ_FOWMAT_WTWIG_ACK(1);
			WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW, tmp);
		}
	} ewse
		wdev->iwq.stat_wegs.w500.hdmi0_status = 0;

	if (iwqs) {
		WWEG32(W_000044_GEN_INT_STATUS, iwqs);
	}
	wetuwn iwqs & iwq_mask;
}

void ws600_iwq_disabwe(stwuct wadeon_device *wdev)
{
	u32 hdmi0 = WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW) &
		~S_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK(1);
	WWEG32(W_007408_HDMI0_AUDIO_PACKET_CONTWOW, hdmi0);
	WWEG32(W_000040_GEN_INT_CNTW, 0);
	WWEG32(W_006540_DxMODE_INT_MASK, 0);
	/* Wait and acknowwedge iwq */
	mdeway(1);
	ws600_iwq_ack(wdev);
}

int ws600_iwq_pwocess(stwuct wadeon_device *wdev)
{
	u32 status, msi_weawm;
	boow queue_hotpwug = fawse;
	boow queue_hdmi = fawse;

	status = ws600_iwq_ack(wdev);
	if (!status &&
	    !wdev->iwq.stat_wegs.w500.disp_int &&
	    !wdev->iwq.stat_wegs.w500.hdmi0_status) {
		wetuwn IWQ_NONE;
	}
	whiwe (status ||
	       wdev->iwq.stat_wegs.w500.disp_int ||
	       wdev->iwq.stat_wegs.w500.hdmi0_status) {
		/* SW intewwupt */
		if (G_000044_SW_INT(status)) {
			wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
		}
		/* Vewticaw bwank intewwupts */
		if (G_007EDC_WB_D1_VBWANK_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			if (wdev->iwq.cwtc_vbwank_int[0]) {
				dwm_handwe_vbwank(wdev->ddev, 0);
				wdev->pm.vbwank_sync = twue;
				wake_up(&wdev->iwq.vbwank_queue);
			}
			if (atomic_wead(&wdev->iwq.pfwip[0]))
				wadeon_cwtc_handwe_vbwank(wdev, 0);
		}
		if (G_007EDC_WB_D2_VBWANK_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			if (wdev->iwq.cwtc_vbwank_int[1]) {
				dwm_handwe_vbwank(wdev->ddev, 1);
				wdev->pm.vbwank_sync = twue;
				wake_up(&wdev->iwq.vbwank_queue);
			}
			if (atomic_wead(&wdev->iwq.pfwip[1]))
				wadeon_cwtc_handwe_vbwank(wdev, 1);
		}
		if (G_007EDC_DC_HOT_PWUG_DETECT1_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			queue_hotpwug = twue;
			DWM_DEBUG("HPD1\n");
		}
		if (G_007EDC_DC_HOT_PWUG_DETECT2_INTEWWUPT(wdev->iwq.stat_wegs.w500.disp_int)) {
			queue_hotpwug = twue;
			DWM_DEBUG("HPD2\n");
		}
		if (G_007404_HDMI0_AZ_FOWMAT_WTWIG(wdev->iwq.stat_wegs.w500.hdmi0_status)) {
			queue_hdmi = twue;
			DWM_DEBUG("HDMI0\n");
		}
		status = ws600_iwq_ack(wdev);
	}
	if (queue_hotpwug)
		scheduwe_dewayed_wowk(&wdev->hotpwug_wowk, 0);
	if (queue_hdmi)
		scheduwe_wowk(&wdev->audio_wowk);
	if (wdev->msi_enabwed) {
		switch (wdev->famiwy) {
		case CHIP_WS600:
		case CHIP_WS690:
		case CHIP_WS740:
			msi_weawm = WWEG32(WADEON_BUS_CNTW) & ~WS600_MSI_WEAWM;
			WWEG32(WADEON_BUS_CNTW, msi_weawm);
			WWEG32(WADEON_BUS_CNTW, msi_weawm | WS600_MSI_WEAWM);
			bweak;
		defauwt:
			WWEG32(WADEON_MSI_WEAWM_EN, WV370_MSI_WEAWM_EN);
			bweak;
		}
	}
	wetuwn IWQ_HANDWED;
}

u32 ws600_get_vbwank_countew(stwuct wadeon_device *wdev, int cwtc)
{
	if (cwtc == 0)
		wetuwn WWEG32(W_0060A4_D1CWTC_STATUS_FWAME_COUNT);
	ewse
		wetuwn WWEG32(W_0068A4_D2CWTC_STATUS_FWAME_COUNT);
}

int ws600_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (G_000000_MC_IDWE(WWEG32_MC(W_000000_MC_STATUS)))
			wetuwn 0;
		udeway(1);
	}
	wetuwn -1;
}

static void ws600_gpu_init(stwuct wadeon_device *wdev)
{
	w420_pipes_init(wdev);
	/* Wait fow mc idwe */
	if (ws600_mc_wait_fow_idwe(wdev))
		dev_wawn(wdev->dev, "Wait MC idwe timeout befowe updating MC.\n");
}

static void ws600_mc_init(stwuct wadeon_device *wdev)
{
	u64 base;

	wdev->mc.apew_base = pci_wesouwce_stawt(wdev->pdev, 0);
	wdev->mc.apew_size = pci_wesouwce_wen(wdev->pdev, 0);
	wdev->mc.vwam_is_ddw = twue;
	wdev->mc.vwam_width = 128;
	wdev->mc.weaw_vwam_size = WWEG32(WADEON_CONFIG_MEMSIZE);
	wdev->mc.mc_vwam_size = wdev->mc.weaw_vwam_size;
	wdev->mc.visibwe_vwam_size = wdev->mc.apew_size;
	wdev->mc.igp_sidepowt_enabwed = wadeon_atombios_sidepowt_pwesent(wdev);
	base = WWEG32_MC(W_000004_MC_FB_WOCATION);
	base = G_000004_MC_FB_STAWT(base) << 16;
	wadeon_vwam_wocation(wdev, &wdev->mc, base);
	wdev->mc.gtt_base_awign = 0;
	wadeon_gtt_wocation(wdev, &wdev->mc);
	wadeon_update_bandwidth_info(wdev);
}

void ws600_bandwidth_update(stwuct wadeon_device *wdev)
{
	stwuct dwm_dispway_mode *mode0 = NUWW;
	stwuct dwm_dispway_mode *mode1 = NUWW;
	u32 d1mode_pwiowity_a_cnt, d2mode_pwiowity_a_cnt;
	/* FIXME: impwement fuww suppowt */

	if (!wdev->mode_info.mode_config_initiawized)
		wetuwn;

	wadeon_update_dispway_pwiowity(wdev);

	if (wdev->mode_info.cwtcs[0]->base.enabwed)
		mode0 = &wdev->mode_info.cwtcs[0]->base.mode;
	if (wdev->mode_info.cwtcs[1]->base.enabwed)
		mode1 = &wdev->mode_info.cwtcs[1]->base.mode;

	ws690_wine_buffew_adjust(wdev, mode0, mode1);

	if (wdev->disp_pwiowity == 2) {
		d1mode_pwiowity_a_cnt = WWEG32(W_006548_D1MODE_PWIOWITY_A_CNT);
		d2mode_pwiowity_a_cnt = WWEG32(W_006D48_D2MODE_PWIOWITY_A_CNT);
		d1mode_pwiowity_a_cnt |= S_006548_D1MODE_PWIOWITY_A_AWWAYS_ON(1);
		d2mode_pwiowity_a_cnt |= S_006D48_D2MODE_PWIOWITY_A_AWWAYS_ON(1);
		WWEG32(W_006548_D1MODE_PWIOWITY_A_CNT, d1mode_pwiowity_a_cnt);
		WWEG32(W_00654C_D1MODE_PWIOWITY_B_CNT, d1mode_pwiowity_a_cnt);
		WWEG32(W_006D48_D2MODE_PWIOWITY_A_CNT, d2mode_pwiowity_a_cnt);
		WWEG32(W_006D4C_D2MODE_PWIOWITY_B_CNT, d2mode_pwiowity_a_cnt);
	}
}

uint32_t ws600_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_000070_MC_IND_INDEX, S_000070_MC_IND_ADDW(weg) |
		S_000070_MC_IND_CITF_AWB0(1));
	w = WWEG32(W_000074_MC_IND_DATA);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
	wetuwn w;
}

void ws600_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_000070_MC_IND_INDEX, S_000070_MC_IND_ADDW(weg) |
		S_000070_MC_IND_CITF_AWB0(1) | S_000070_MC_IND_WW_EN(1));
	WWEG32(W_000074_MC_IND_DATA, v);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
}

void ws600_set_safe_wegistews(stwuct wadeon_device *wdev)
{
	wdev->config.w300.weg_safe_bm = ws600_weg_safe_bm;
	wdev->config.w300.weg_safe_bm_size = AWWAY_SIZE(ws600_weg_safe_bm);
}

static void ws600_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct wv515_mc_save save;

	/* Stops aww mc cwients */
	wv515_mc_stop(wdev, &save);

	/* Wait fow mc idwe */
	if (ws600_mc_wait_fow_idwe(wdev))
		dev_wawn(wdev->dev, "Wait MC idwe timeout befowe updating MC.\n");

	/* FIXME: What does AGP means fow such chipset ? */
	WWEG32_MC(W_000005_MC_AGP_WOCATION, 0x0FFFFFFF);
	WWEG32_MC(W_000006_AGP_BASE, 0);
	WWEG32_MC(W_000007_AGP_BASE_2, 0);
	/* Pwogwam MC */
	WWEG32_MC(W_000004_MC_FB_WOCATION,
			S_000004_MC_FB_STAWT(wdev->mc.vwam_stawt >> 16) |
			S_000004_MC_FB_TOP(wdev->mc.vwam_end >> 16));
	WWEG32(W_000134_HDP_FB_WOCATION,
		S_000134_HDP_FB_STAWT(wdev->mc.vwam_stawt >> 16));

	wv515_mc_wesume(wdev, &save);
}

static int ws600_stawtup(stwuct wadeon_device *wdev)
{
	int w;

	ws600_mc_pwogwam(wdev);
	/* Wesume cwock */
	wv515_cwock_stawtup(wdev);
	/* Initiawize GPU configuwation (# pipes, ...) */
	ws600_gpu_init(wdev);
	/* Initiawize GAWT (initiawize aftew TTM so we can awwocate
	 * memowy thwough TTM but finawize aftew TTM) */
	w = ws600_gawt_enabwe(wdev);
	if (w)
		wetuwn w;

	/* awwocate wb buffew */
	w = wadeon_wb_init(wdev);
	if (w)
		wetuwn w;

	w = wadeon_fence_dwivew_stawt_wing(wdev, WADEON_WING_TYPE_GFX_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	/* Enabwe IWQ */
	if (!wdev->iwq.instawwed) {
		w = wadeon_iwq_kms_init(wdev);
		if (w)
			wetuwn w;
	}

	ws600_iwq_set(wdev);
	wdev->config.w300.hdp_cntw = WWEG32(WADEON_HOST_PATH_CNTW);
	/* 1M wing buffew */
	w = w100_cp_init(wdev, 1024 * 1024);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_audio_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing audio\n");
		wetuwn w;
	}

	wetuwn 0;
}

int ws600_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Make suw GAWT awe not wowking */
	ws600_gawt_disabwe(wdev);
	/* Wesume cwock befowe doing weset */
	wv515_cwock_stawtup(wdev);
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev, "GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* post */
	atom_asic_init(wdev->mode_info.atom_context);
	/* Wesume cwock aftew posting */
	wv515_cwock_stawtup(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);

	wdev->accew_wowking = twue;
	w = ws600_stawtup(wdev);
	if (w) {
		wdev->accew_wowking = fawse;
	}
	wetuwn w;
}

int ws600_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	wadeon_audio_fini(wdev);
	w100_cp_disabwe(wdev);
	wadeon_wb_disabwe(wdev);
	ws600_iwq_disabwe(wdev);
	ws600_gawt_disabwe(wdev);
	wetuwn 0;
}

void ws600_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	wadeon_audio_fini(wdev);
	w100_cp_fini(wdev);
	wadeon_wb_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_gem_fini(wdev);
	ws600_gawt_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_bo_fini(wdev);
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

int ws600_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Disabwe VGA */
	wv515_vga_wendew_disabwe(wdev);
	/* Initiawize scwatch wegistews */
	wadeon_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* westowe some wegistew to sane defauwts */
	w100_westowe_sanity(wdev);
	/* BIOS */
	if (!wadeon_get_bios(wdev)) {
		if (ASIC_IS_AVIVO(wdev))
			wetuwn -EINVAW;
	}
	if (wdev->is_atom_bios) {
		w = wadeon_atombios_init(wdev);
		if (w)
			wetuwn w;
	} ewse {
		dev_eww(wdev->dev, "Expecting atombios fow WS600 GPU\n");
		wetuwn -EINVAW;
	}
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev,
			"GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* check if cawds awe posted ow not */
	if (wadeon_boot_test_post_cawd(wdev) == fawse)
		wetuwn -EINVAW;

	/* Initiawize cwocks */
	wadeon_get_cwock_info(wdev->ddev);
	/* initiawize memowy contwowwew */
	ws600_mc_init(wdev);
	w100_debugfs_wbbm_init(wdev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;
	w = ws600_gawt_init(wdev);
	if (w)
		wetuwn w;
	ws600_set_safe_wegistews(wdev);

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->accew_wowking = twue;
	w = ws600_stawtup(wdev);
	if (w) {
		/* Somethings want wwont with the accew init stop accew */
		dev_eww(wdev->dev, "Disabwing GPU accewewation\n");
		w100_cp_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		ws600_gawt_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		wdev->accew_wowking = fawse;
	}
	wetuwn 0;
}
