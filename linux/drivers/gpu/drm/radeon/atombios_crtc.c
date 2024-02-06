/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
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
 */

#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"
#incwude "atom.h"
#incwude "atom-bits.h"

static void atombios_ovewscan_setup(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	SET_CWTC_OVEWSCAN_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetCWTC_OvewScan);
	int a1, a2;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = wadeon_cwtc->cwtc_id;

	switch (wadeon_cwtc->wmx_type) {
	case WMX_CENTEW:
		awgs.usOvewscanTop = cpu_to_we16((adjusted_mode->cwtc_vdispway - mode->cwtc_vdispway) / 2);
		awgs.usOvewscanBottom = cpu_to_we16((adjusted_mode->cwtc_vdispway - mode->cwtc_vdispway) / 2);
		awgs.usOvewscanWeft = cpu_to_we16((adjusted_mode->cwtc_hdispway - mode->cwtc_hdispway) / 2);
		awgs.usOvewscanWight = cpu_to_we16((adjusted_mode->cwtc_hdispway - mode->cwtc_hdispway) / 2);
		bweak;
	case WMX_ASPECT:
		a1 = mode->cwtc_vdispway * adjusted_mode->cwtc_hdispway;
		a2 = adjusted_mode->cwtc_vdispway * mode->cwtc_hdispway;

		if (a1 > a2) {
			awgs.usOvewscanWeft = cpu_to_we16((adjusted_mode->cwtc_hdispway - (a2 / mode->cwtc_vdispway)) / 2);
			awgs.usOvewscanWight = cpu_to_we16((adjusted_mode->cwtc_hdispway - (a2 / mode->cwtc_vdispway)) / 2);
		} ewse if (a2 > a1) {
			awgs.usOvewscanTop = cpu_to_we16((adjusted_mode->cwtc_vdispway - (a1 / mode->cwtc_hdispway)) / 2);
			awgs.usOvewscanBottom = cpu_to_we16((adjusted_mode->cwtc_vdispway - (a1 / mode->cwtc_hdispway)) / 2);
		}
		bweak;
	case WMX_FUWW:
	defauwt:
		awgs.usOvewscanWight = cpu_to_we16(wadeon_cwtc->h_bowdew);
		awgs.usOvewscanWeft = cpu_to_we16(wadeon_cwtc->h_bowdew);
		awgs.usOvewscanBottom = cpu_to_we16(wadeon_cwtc->v_bowdew);
		awgs.usOvewscanTop = cpu_to_we16(wadeon_cwtc->v_bowdew);
		bweak;
	}
	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_scawew_setup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	ENABWE_SCAWEW_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweScawew);
	stwuct wadeon_encodew *wadeon_encodew =
		to_wadeon_encodew(wadeon_cwtc->encodew);
	/* fixme - fiww in enc_pwiv fow atom dac */
	enum wadeon_tv_std tv_std = TV_STD_NTSC;
	boow is_tv = fawse, is_cv = fawse;

	if (!ASIC_IS_AVIVO(wdev) && wadeon_cwtc->cwtc_id)
		wetuwn;

	if (wadeon_encodew->active_device & ATOM_DEVICE_TV_SUPPOWT) {
		stwuct wadeon_encodew_atom_dac *tv_dac = wadeon_encodew->enc_pwiv;
		tv_std = tv_dac->tv_std;
		is_tv = twue;
	}

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucScawew = wadeon_cwtc->cwtc_id;

	if (is_tv) {
		switch (tv_std) {
		case TV_STD_NTSC:
		defauwt:
			awgs.ucTVStandawd = ATOM_TV_NTSC;
			bweak;
		case TV_STD_PAW:
			awgs.ucTVStandawd = ATOM_TV_PAW;
			bweak;
		case TV_STD_PAW_M:
			awgs.ucTVStandawd = ATOM_TV_PAWM;
			bweak;
		case TV_STD_PAW_60:
			awgs.ucTVStandawd = ATOM_TV_PAW60;
			bweak;
		case TV_STD_NTSC_J:
			awgs.ucTVStandawd = ATOM_TV_NTSCJ;
			bweak;
		case TV_STD_SCAWT_PAW:
			awgs.ucTVStandawd = ATOM_TV_PAW; /* ??? */
			bweak;
		case TV_STD_SECAM:
			awgs.ucTVStandawd = ATOM_TV_SECAM;
			bweak;
		case TV_STD_PAW_CN:
			awgs.ucTVStandawd = ATOM_TV_PAWCN;
			bweak;
		}
		awgs.ucEnabwe = SCAWEW_ENABWE_MUWTITAP_MODE;
	} ewse if (is_cv) {
		awgs.ucTVStandawd = ATOM_TV_CV;
		awgs.ucEnabwe = SCAWEW_ENABWE_MUWTITAP_MODE;
	} ewse {
		switch (wadeon_cwtc->wmx_type) {
		case WMX_FUWW:
			awgs.ucEnabwe = ATOM_SCAWEW_EXPANSION;
			bweak;
		case WMX_CENTEW:
			awgs.ucEnabwe = ATOM_SCAWEW_CENTEW;
			bweak;
		case WMX_ASPECT:
			awgs.ucEnabwe = ATOM_SCAWEW_EXPANSION;
			bweak;
		defauwt:
			if (ASIC_IS_AVIVO(wdev))
				awgs.ucEnabwe = ATOM_SCAWEW_DISABWE;
			ewse
				awgs.ucEnabwe = ATOM_SCAWEW_CENTEW;
			bweak;
		}
	}
	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
	if ((is_tv || is_cv)
	    && wdev->famiwy >= CHIP_WV515 && wdev->famiwy <= CHIP_W580) {
		atom_wv515_fowce_tv_scawew(wdev, wadeon_cwtc);
	}
}

static void atombios_wock_cwtc(stwuct dwm_cwtc *cwtc, int wock)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int index =
	    GetIndexIntoMastewTabwe(COMMAND, UpdateCWTC_DoubweBuffewWegistews);
	ENABWE_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = wadeon_cwtc->cwtc_id;
	awgs.ucEnabwe = wock;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_enabwe_cwtc(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweCWTC);
	ENABWE_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = wadeon_cwtc->cwtc_id;
	awgs.ucEnabwe = state;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_enabwe_cwtc_memweq(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweCWTCMemWeq);
	ENABWE_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = wadeon_cwtc->cwtc_id;
	awgs.ucEnabwe = state;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static const u32 vga_contwow_wegs[6] =
{
	AVIVO_D1VGA_CONTWOW,
	AVIVO_D2VGA_CONTWOW,
	EVEWGWEEN_D3VGA_CONTWOW,
	EVEWGWEEN_D4VGA_CONTWOW,
	EVEWGWEEN_D5VGA_CONTWOW,
	EVEWGWEEN_D6VGA_CONTWOW,
};

static void atombios_bwank_cwtc(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int index = GetIndexIntoMastewTabwe(COMMAND, BwankCWTC);
	BWANK_CWTC_PS_AWWOCATION awgs;
	u32 vga_contwow = 0;

	memset(&awgs, 0, sizeof(awgs));

	if (ASIC_IS_DCE8(wdev)) {
		vga_contwow = WWEG32(vga_contwow_wegs[wadeon_cwtc->cwtc_id]);
		WWEG32(vga_contwow_wegs[wadeon_cwtc->cwtc_id], vga_contwow | 1);
	}

	awgs.ucCWTC = wadeon_cwtc->cwtc_id;
	awgs.ucBwanking = state;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);

	if (ASIC_IS_DCE8(wdev))
		WWEG32(vga_contwow_wegs[wadeon_cwtc->cwtc_id], vga_contwow);
}

static void atombios_powewgate_cwtc(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweDispPowewGating);
	ENABWE_DISP_POWEW_GATING_PAWAMETEWS_V2_1 awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucDispPipeId = wadeon_cwtc->cwtc_id;
	awgs.ucEnabwe = state;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void atombios_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		wadeon_cwtc->enabwed = twue;
		atombios_enabwe_cwtc(cwtc, ATOM_ENABWE);
		if (ASIC_IS_DCE3(wdev) && !ASIC_IS_DCE6(wdev))
			atombios_enabwe_cwtc_memweq(cwtc, ATOM_ENABWE);
		atombios_bwank_cwtc(cwtc, ATOM_DISABWE);
		if (dev->num_cwtcs > wadeon_cwtc->cwtc_id)
			dwm_cwtc_vbwank_on(cwtc);
		wadeon_cwtc_woad_wut(cwtc);
		bweak;
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
	case DWM_MODE_DPMS_OFF:
		if (dev->num_cwtcs > wadeon_cwtc->cwtc_id)
			dwm_cwtc_vbwank_off(cwtc);
		if (wadeon_cwtc->enabwed)
			atombios_bwank_cwtc(cwtc, ATOM_ENABWE);
		if (ASIC_IS_DCE3(wdev) && !ASIC_IS_DCE6(wdev))
			atombios_enabwe_cwtc_memweq(cwtc, ATOM_DISABWE);
		atombios_enabwe_cwtc(cwtc, ATOM_DISABWE);
		wadeon_cwtc->enabwed = fawse;
		bweak;
	}
	/* adjust pm to dpms */
	wadeon_pm_compute_cwocks(wdev);
}

static void
atombios_set_cwtc_dtd_timing(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	SET_CWTC_USING_DTD_TIMING_PAWAMETEWS awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetCWTC_UsingDTDTiming);
	u16 misc = 0;

	memset(&awgs, 0, sizeof(awgs));
	awgs.usH_Size = cpu_to_we16(mode->cwtc_hdispway - (wadeon_cwtc->h_bowdew * 2));
	awgs.usH_Bwanking_Time =
		cpu_to_we16(mode->cwtc_hbwank_end - mode->cwtc_hdispway + (wadeon_cwtc->h_bowdew * 2));
	awgs.usV_Size = cpu_to_we16(mode->cwtc_vdispway - (wadeon_cwtc->v_bowdew * 2));
	awgs.usV_Bwanking_Time =
		cpu_to_we16(mode->cwtc_vbwank_end - mode->cwtc_vdispway + (wadeon_cwtc->v_bowdew * 2));
	awgs.usH_SyncOffset =
		cpu_to_we16(mode->cwtc_hsync_stawt - mode->cwtc_hdispway + wadeon_cwtc->h_bowdew);
	awgs.usH_SyncWidth =
		cpu_to_we16(mode->cwtc_hsync_end - mode->cwtc_hsync_stawt);
	awgs.usV_SyncOffset =
		cpu_to_we16(mode->cwtc_vsync_stawt - mode->cwtc_vdispway + wadeon_cwtc->v_bowdew);
	awgs.usV_SyncWidth =
		cpu_to_we16(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt);
	awgs.ucH_Bowdew = wadeon_cwtc->h_bowdew;
	awgs.ucV_Bowdew = wadeon_cwtc->v_bowdew;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		misc |= ATOM_VSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		misc |= ATOM_HSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		misc |= ATOM_INTEWWACE;
	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		misc |= ATOM_DOUBWE_CWOCK_MODE;
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		misc |= ATOM_H_WEPWICATIONBY2 | ATOM_V_WEPWICATIONBY2;

	awgs.susModeMiscInfo.usAccess = cpu_to_we16(misc);
	awgs.ucCWTC = wadeon_cwtc->cwtc_id;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_cwtc_set_timing(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	SET_CWTC_TIMING_PAWAMETEWS_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetCWTC_Timing);
	u16 misc = 0;

	memset(&awgs, 0, sizeof(awgs));
	awgs.usH_Totaw = cpu_to_we16(mode->cwtc_htotaw);
	awgs.usH_Disp = cpu_to_we16(mode->cwtc_hdispway);
	awgs.usH_SyncStawt = cpu_to_we16(mode->cwtc_hsync_stawt);
	awgs.usH_SyncWidth =
		cpu_to_we16(mode->cwtc_hsync_end - mode->cwtc_hsync_stawt);
	awgs.usV_Totaw = cpu_to_we16(mode->cwtc_vtotaw);
	awgs.usV_Disp = cpu_to_we16(mode->cwtc_vdispway);
	awgs.usV_SyncStawt = cpu_to_we16(mode->cwtc_vsync_stawt);
	awgs.usV_SyncWidth =
		cpu_to_we16(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt);

	awgs.ucOvewscanWight = wadeon_cwtc->h_bowdew;
	awgs.ucOvewscanWeft = wadeon_cwtc->h_bowdew;
	awgs.ucOvewscanBottom = wadeon_cwtc->v_bowdew;
	awgs.ucOvewscanTop = wadeon_cwtc->v_bowdew;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		misc |= ATOM_VSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		misc |= ATOM_HSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		misc |= ATOM_INTEWWACE;
	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		misc |= ATOM_DOUBWE_CWOCK_MODE;
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		misc |= ATOM_H_WEPWICATIONBY2 | ATOM_V_WEPWICATIONBY2;

	awgs.susModeMiscInfo.usAccess = cpu_to_we16(misc);
	awgs.ucCWTC = wadeon_cwtc->cwtc_id;

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_disabwe_ss(stwuct wadeon_device *wdev, int pww_id)
{
	u32 ss_cntw;

	if (ASIC_IS_DCE4(wdev)) {
		switch (pww_id) {
		case ATOM_PPWW1:
			ss_cntw = WWEG32(EVEWGWEEN_P1PWW_SS_CNTW);
			ss_cntw &= ~EVEWGWEEN_PxPWW_SS_EN;
			WWEG32(EVEWGWEEN_P1PWW_SS_CNTW, ss_cntw);
			bweak;
		case ATOM_PPWW2:
			ss_cntw = WWEG32(EVEWGWEEN_P2PWW_SS_CNTW);
			ss_cntw &= ~EVEWGWEEN_PxPWW_SS_EN;
			WWEG32(EVEWGWEEN_P2PWW_SS_CNTW, ss_cntw);
			bweak;
		case ATOM_DCPWW:
		case ATOM_PPWW_INVAWID:
			wetuwn;
		}
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		switch (pww_id) {
		case ATOM_PPWW1:
			ss_cntw = WWEG32(AVIVO_P1PWW_INT_SS_CNTW);
			ss_cntw &= ~1;
			WWEG32(AVIVO_P1PWW_INT_SS_CNTW, ss_cntw);
			bweak;
		case ATOM_PPWW2:
			ss_cntw = WWEG32(AVIVO_P2PWW_INT_SS_CNTW);
			ss_cntw &= ~1;
			WWEG32(AVIVO_P2PWW_INT_SS_CNTW, ss_cntw);
			bweak;
		case ATOM_DCPWW:
		case ATOM_PPWW_INVAWID:
			wetuwn;
		}
	}
}


union atom_enabwe_ss {
	ENABWE_WVDS_SS_PAWAMETEWS wvds_ss;
	ENABWE_WVDS_SS_PAWAMETEWS_V2 wvds_ss_2;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_PS_AWWOCATION v1;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V2 v2;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V3 v3;
};

static void atombios_cwtc_pwogwam_ss(stwuct wadeon_device *wdev,
				     int enabwe,
				     int pww_id,
				     int cwtc_id,
				     stwuct wadeon_atom_ss *ss)
{
	unsigned i;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweSpweadSpectwumOnPPWW);
	union atom_enabwe_ss awgs;

	if (enabwe) {
		/* Don't mess with SS if pewcentage is 0 ow extewnaw ss.
		 * SS is awweady disabwed pweviouswy, and disabwing it
		 * again can cause dispway pwobwems if the pww is awweady
		 * pwogwammed.
		 */
		if (ss->pewcentage == 0)
			wetuwn;
		if (ss->type & ATOM_EXTEWNAW_SS_MASK)
			wetuwn;
	} ewse {
		fow (i = 0; i < wdev->num_cwtc; i++) {
			if (wdev->mode_info.cwtcs[i] &&
			    wdev->mode_info.cwtcs[i]->enabwed &&
			    i != cwtc_id &&
			    pww_id == wdev->mode_info.cwtcs[i]->pww_id) {
				/* one othew cwtc is using this pww don't tuwn
				 * off spwead spectwum as it might tuwn off
				 * dispway on active cwtc
				 */
				wetuwn;
			}
		}
	}

	memset(&awgs, 0, sizeof(awgs));

	if (ASIC_IS_DCE5(wdev)) {
		awgs.v3.usSpweadSpectwumAmountFwac = cpu_to_we16(0);
		awgs.v3.ucSpweadSpectwumType = ss->type & ATOM_SS_CENTWE_SPWEAD_MODE_MASK;
		switch (pww_id) {
		case ATOM_PPWW1:
			awgs.v3.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V3_P1PWW;
			bweak;
		case ATOM_PPWW2:
			awgs.v3.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V3_P2PWW;
			bweak;
		case ATOM_DCPWW:
			awgs.v3.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V3_DCPWW;
			bweak;
		case ATOM_PPWW_INVAWID:
			wetuwn;
		}
		awgs.v3.usSpweadSpectwumAmount = cpu_to_we16(ss->amount);
		awgs.v3.usSpweadSpectwumStep = cpu_to_we16(ss->step);
		awgs.v3.ucEnabwe = enabwe;
	} ewse if (ASIC_IS_DCE4(wdev)) {
		awgs.v2.usSpweadSpectwumPewcentage = cpu_to_we16(ss->pewcentage);
		awgs.v2.ucSpweadSpectwumType = ss->type & ATOM_SS_CENTWE_SPWEAD_MODE_MASK;
		switch (pww_id) {
		case ATOM_PPWW1:
			awgs.v2.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V2_P1PWW;
			bweak;
		case ATOM_PPWW2:
			awgs.v2.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V2_P2PWW;
			bweak;
		case ATOM_DCPWW:
			awgs.v2.ucSpweadSpectwumType |= ATOM_PPWW_SS_TYPE_V2_DCPWW;
			bweak;
		case ATOM_PPWW_INVAWID:
			wetuwn;
		}
		awgs.v2.usSpweadSpectwumAmount = cpu_to_we16(ss->amount);
		awgs.v2.usSpweadSpectwumStep = cpu_to_we16(ss->step);
		awgs.v2.ucEnabwe = enabwe;
	} ewse if (ASIC_IS_DCE3(wdev)) {
		awgs.v1.usSpweadSpectwumPewcentage = cpu_to_we16(ss->pewcentage);
		awgs.v1.ucSpweadSpectwumType = ss->type & ATOM_SS_CENTWE_SPWEAD_MODE_MASK;
		awgs.v1.ucSpweadSpectwumStep = ss->step;
		awgs.v1.ucSpweadSpectwumDeway = ss->deway;
		awgs.v1.ucSpweadSpectwumWange = ss->wange;
		awgs.v1.ucPpww = pww_id;
		awgs.v1.ucEnabwe = enabwe;
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		if ((enabwe == ATOM_DISABWE) || (ss->pewcentage == 0) ||
		    (ss->type & ATOM_EXTEWNAW_SS_MASK)) {
			atombios_disabwe_ss(wdev, pww_id);
			wetuwn;
		}
		awgs.wvds_ss_2.usSpweadSpectwumPewcentage = cpu_to_we16(ss->pewcentage);
		awgs.wvds_ss_2.ucSpweadSpectwumType = ss->type & ATOM_SS_CENTWE_SPWEAD_MODE_MASK;
		awgs.wvds_ss_2.ucSpweadSpectwumStep = ss->step;
		awgs.wvds_ss_2.ucSpweadSpectwumDeway = ss->deway;
		awgs.wvds_ss_2.ucSpweadSpectwumWange = ss->wange;
		awgs.wvds_ss_2.ucEnabwe = enabwe;
	} ewse {
		if (enabwe == ATOM_DISABWE) {
			atombios_disabwe_ss(wdev, pww_id);
			wetuwn;
		}
		awgs.wvds_ss.usSpweadSpectwumPewcentage = cpu_to_we16(ss->pewcentage);
		awgs.wvds_ss.ucSpweadSpectwumType = ss->type & ATOM_SS_CENTWE_SPWEAD_MODE_MASK;
		awgs.wvds_ss.ucSpweadSpectwumStepSize_Deway = (ss->step & 3) << 2;
		awgs.wvds_ss.ucSpweadSpectwumStepSize_Deway |= (ss->deway & 7) << 4;
		awgs.wvds_ss.ucEnabwe = enabwe;
	}
	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

union adjust_pixew_cwock {
	ADJUST_DISPWAY_PWW_PS_AWWOCATION v1;
	ADJUST_DISPWAY_PWW_PS_AWWOCATION_V3 v3;
};

static u32 atombios_adjust_pww(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_encodew *encodew = wadeon_cwtc->encodew;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	u32 adjusted_cwock = mode->cwock;
	int encodew_mode = atombios_get_encodew_mode(encodew);
	u32 dp_cwock = mode->cwock;
	u32 cwock = mode->cwock;
	int bpc = wadeon_cwtc->bpc;
	boow is_duawwink = wadeon_dig_monitow_is_duawwink(encodew, mode->cwock);

	/* weset the pww fwags */
	wadeon_cwtc->pww_fwags = 0;

	if (ASIC_IS_AVIVO(wdev)) {
		if ((wdev->famiwy == CHIP_WS600) ||
		    (wdev->famiwy == CHIP_WS690) ||
		    (wdev->famiwy == CHIP_WS740))
			wadeon_cwtc->pww_fwags |= (/*WADEON_PWW_USE_FWAC_FB_DIV |*/
				WADEON_PWW_PWEFEW_CWOSEST_WOWEW);

		if (ASIC_IS_DCE32(wdev) && mode->cwock > 200000)	/* wange wimits??? */
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_HIGH_FB_DIV;
		ewse
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_WOW_WEF_DIV;

		if (wdev->famiwy < CHIP_WV770)
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_MINM_OVEW_MAXP;
		/* use fwac fb div on APUs */
		if (ASIC_IS_DCE41(wdev) || ASIC_IS_DCE61(wdev) || ASIC_IS_DCE8(wdev))
			wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
		/* use fwac fb div on WS780/WS880 */
		if (((wdev->famiwy == CHIP_WS780) || (wdev->famiwy == CHIP_WS880))
		    && !wadeon_cwtc->ss_enabwed)
			wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
		if (ASIC_IS_DCE32(wdev) && mode->cwock > 165000)
			wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
	} ewse {
		wadeon_cwtc->pww_fwags |= WADEON_PWW_WEGACY;

		if (mode->cwock > 200000)	/* wange wimits??? */
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_HIGH_FB_DIV;
		ewse
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_WOW_WEF_DIV;
	}

	if ((wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT | ATOM_DEVICE_DFP_SUPPOWT)) ||
	    (wadeon_encodew_get_dp_bwidge_encodew_id(encodew) != ENCODEW_OBJECT_ID_NONE)) {
		if (connectow) {
			stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
			stwuct wadeon_connectow_atom_dig *dig_connectow =
				wadeon_connectow->con_pwiv;

			dp_cwock = dig_connectow->dp_cwock;
		}
	}

	/* use wecommended wef_div fow ss */
	if (wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT)) {
		if (wadeon_cwtc->ss_enabwed) {
			if (wadeon_cwtc->ss.wefdiv) {
				wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_WEF_DIV;
				wadeon_cwtc->pww_wefewence_div = wadeon_cwtc->ss.wefdiv;
				if (ASIC_IS_AVIVO(wdev) &&
				    wdev->famiwy != CHIP_WS780 &&
				    wdev->famiwy != CHIP_WS880)
					wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
			}
		}
	}

	if (ASIC_IS_AVIVO(wdev)) {
		/* DVO wants 2x pixew cwock if the DVO chip is in 12 bit mode */
		if (wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1)
			adjusted_cwock = mode->cwock * 2;
		if (wadeon_encodew->active_device & (ATOM_DEVICE_TV_SUPPOWT))
			wadeon_cwtc->pww_fwags |= WADEON_PWW_PWEFEW_CWOSEST_WOWEW;
		if (wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT))
			wadeon_cwtc->pww_fwags |= WADEON_PWW_IS_WCD;
	} ewse {
		if (encodew->encodew_type != DWM_MODE_ENCODEW_DAC)
			wadeon_cwtc->pww_fwags |= WADEON_PWW_NO_ODD_POST_DIV;
		if (encodew->encodew_type == DWM_MODE_ENCODEW_WVDS)
			wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_WEF_DIV;
	}

	/* adjust pww fow deep cowow modes */
	if (encodew_mode == ATOM_ENCODEW_MODE_HDMI) {
		switch (bpc) {
		case 8:
		defauwt:
			bweak;
		case 10:
			cwock = (cwock * 5) / 4;
			bweak;
		case 12:
			cwock = (cwock * 3) / 2;
			bweak;
		case 16:
			cwock = cwock * 2;
			bweak;
		}
	}

	/* DCE3+ has an AdjustDispwayPww that wiww adjust the pixew cwock
	 * accowdingwy based on the encodew/twansmittew to wowk awound
	 * speciaw hw wequiwements.
	 */
	if (ASIC_IS_DCE3(wdev)) {
		union adjust_pixew_cwock awgs;
		u8 fwev, cwev;
		int index;

		index = GetIndexIntoMastewTabwe(COMMAND, AdjustDispwayPww);
		if (!atom_pawse_cmd_headew(wdev->mode_info.atom_context, index, &fwev,
					   &cwev))
			wetuwn adjusted_cwock;

		memset(&awgs, 0, sizeof(awgs));

		switch (fwev) {
		case 1:
			switch (cwev) {
			case 1:
			case 2:
				awgs.v1.usPixewCwock = cpu_to_we16(cwock / 10);
				awgs.v1.ucTwansmittewID = wadeon_encodew->encodew_id;
				awgs.v1.ucEncodeMode = encodew_mode;
				if (wadeon_cwtc->ss_enabwed && wadeon_cwtc->ss.pewcentage)
					awgs.v1.ucConfig |=
						ADJUST_DISPWAY_CONFIG_SS_ENABWE;

				atom_execute_tabwe(wdev->mode_info.atom_context,
						   index, (uint32_t *)&awgs);
				adjusted_cwock = we16_to_cpu(awgs.v1.usPixewCwock) * 10;
				bweak;
			case 3:
				awgs.v3.sInput.usPixewCwock = cpu_to_we16(cwock / 10);
				awgs.v3.sInput.ucTwansmittewID = wadeon_encodew->encodew_id;
				awgs.v3.sInput.ucEncodeMode = encodew_mode;
				awgs.v3.sInput.ucDispPwwConfig = 0;
				if (wadeon_cwtc->ss_enabwed && wadeon_cwtc->ss.pewcentage)
					awgs.v3.sInput.ucDispPwwConfig |=
						DISPPWW_CONFIG_SS_ENABWE;
				if (ENCODEW_MODE_IS_DP(encodew_mode)) {
					awgs.v3.sInput.ucDispPwwConfig |=
						DISPPWW_CONFIG_COHEWENT_MODE;
					/* 16200 ow 27000 */
					awgs.v3.sInput.usPixewCwock = cpu_to_we16(dp_cwock / 10);
				} ewse if (wadeon_encodew->devices & (ATOM_DEVICE_DFP_SUPPOWT)) {
					stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
					if (dig->cohewent_mode)
						awgs.v3.sInput.ucDispPwwConfig |=
							DISPPWW_CONFIG_COHEWENT_MODE;
					if (is_duawwink)
						awgs.v3.sInput.ucDispPwwConfig |=
							DISPPWW_CONFIG_DUAW_WINK;
				}
				if (wadeon_encodew_get_dp_bwidge_encodew_id(encodew) !=
				    ENCODEW_OBJECT_ID_NONE)
					awgs.v3.sInput.ucExtTwansmittewID =
						wadeon_encodew_get_dp_bwidge_encodew_id(encodew);
				ewse
					awgs.v3.sInput.ucExtTwansmittewID = 0;

				atom_execute_tabwe(wdev->mode_info.atom_context,
						   index, (uint32_t *)&awgs);
				adjusted_cwock = we32_to_cpu(awgs.v3.sOutput.uwDispPwwFweq) * 10;
				if (awgs.v3.sOutput.ucWefDiv) {
					wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
					wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_WEF_DIV;
					wadeon_cwtc->pww_wefewence_div = awgs.v3.sOutput.ucWefDiv;
				}
				if (awgs.v3.sOutput.ucPostDiv) {
					wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_FWAC_FB_DIV;
					wadeon_cwtc->pww_fwags |= WADEON_PWW_USE_POST_DIV;
					wadeon_cwtc->pww_post_div = awgs.v3.sOutput.ucPostDiv;
				}
				bweak;
			defauwt:
				DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
				wetuwn adjusted_cwock;
			}
			bweak;
		defauwt:
			DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
			wetuwn adjusted_cwock;
		}
	}
	wetuwn adjusted_cwock;
}

union set_pixew_cwock {
	SET_PIXEW_CWOCK_PS_AWWOCATION base;
	PIXEW_CWOCK_PAWAMETEWS v1;
	PIXEW_CWOCK_PAWAMETEWS_V2 v2;
	PIXEW_CWOCK_PAWAMETEWS_V3 v3;
	PIXEW_CWOCK_PAWAMETEWS_V5 v5;
	PIXEW_CWOCK_PAWAMETEWS_V6 v6;
};

/* on DCE5, make suwe the vowtage is high enough to suppowt the
 * wequiwed disp cwk.
 */
static void atombios_cwtc_set_disp_eng_pww(stwuct wadeon_device *wdev,
				    u32 dispcwk)
{
	u8 fwev, cwev;
	int index;
	union set_pixew_cwock awgs;

	memset(&awgs, 0, sizeof(awgs));

	index = GetIndexIntoMastewTabwe(COMMAND, SetPixewCwock);
	if (!atom_pawse_cmd_headew(wdev->mode_info.atom_context, index, &fwev,
				   &cwev))
		wetuwn;

	switch (fwev) {
	case 1:
		switch (cwev) {
		case 5:
			/* if the defauwt dcpww cwock is specified,
			 * SetPixewCwock pwovides the dividews
			 */
			awgs.v5.ucCWTC = ATOM_CWTC_INVAWID;
			awgs.v5.usPixewCwock = cpu_to_we16(dispcwk);
			awgs.v5.ucPpww = ATOM_DCPWW;
			bweak;
		case 6:
			/* if the defauwt dcpww cwock is specified,
			 * SetPixewCwock pwovides the dividews
			 */
			awgs.v6.uwDispEngCwkFweq = cpu_to_we32(dispcwk);
			if (ASIC_IS_DCE61(wdev) || ASIC_IS_DCE8(wdev))
				awgs.v6.ucPpww = ATOM_EXT_PWW1;
			ewse if (ASIC_IS_DCE6(wdev))
				awgs.v6.ucPpww = ATOM_PPWW0;
			ewse
				awgs.v6.ucPpww = ATOM_DCPWW;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
			wetuwn;
		}
		bweak;
	defauwt:
		DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
		wetuwn;
	}
	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static void atombios_cwtc_pwogwam_pww(stwuct dwm_cwtc *cwtc,
				      u32 cwtc_id,
				      int pww_id,
				      u32 encodew_mode,
				      u32 encodew_id,
				      u32 cwock,
				      u32 wef_div,
				      u32 fb_div,
				      u32 fwac_fb_div,
				      u32 post_div,
				      int bpc,
				      boow ss_enabwed,
				      stwuct wadeon_atom_ss *ss)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	u8 fwev, cwev;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetPixewCwock);
	union set_pixew_cwock awgs;

	memset(&awgs, 0, sizeof(awgs));

	if (!atom_pawse_cmd_headew(wdev->mode_info.atom_context, index, &fwev,
				   &cwev))
		wetuwn;

	switch (fwev) {
	case 1:
		switch (cwev) {
		case 1:
			if (cwock == ATOM_DISABWE)
				wetuwn;
			awgs.v1.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v1.usWefDiv = cpu_to_we16(wef_div);
			awgs.v1.usFbDiv = cpu_to_we16(fb_div);
			awgs.v1.ucFwacFbDiv = fwac_fb_div;
			awgs.v1.ucPostDiv = post_div;
			awgs.v1.ucPpww = pww_id;
			awgs.v1.ucCWTC = cwtc_id;
			awgs.v1.ucWefDivSwc = 1;
			bweak;
		case 2:
			awgs.v2.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v2.usWefDiv = cpu_to_we16(wef_div);
			awgs.v2.usFbDiv = cpu_to_we16(fb_div);
			awgs.v2.ucFwacFbDiv = fwac_fb_div;
			awgs.v2.ucPostDiv = post_div;
			awgs.v2.ucPpww = pww_id;
			awgs.v2.ucCWTC = cwtc_id;
			awgs.v2.ucWefDivSwc = 1;
			bweak;
		case 3:
			awgs.v3.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v3.usWefDiv = cpu_to_we16(wef_div);
			awgs.v3.usFbDiv = cpu_to_we16(fb_div);
			awgs.v3.ucFwacFbDiv = fwac_fb_div;
			awgs.v3.ucPostDiv = post_div;
			awgs.v3.ucPpww = pww_id;
			if (cwtc_id == ATOM_CWTC2)
				awgs.v3.ucMiscInfo = PIXEW_CWOCK_MISC_CWTC_SEW_CWTC2;
			ewse
				awgs.v3.ucMiscInfo = PIXEW_CWOCK_MISC_CWTC_SEW_CWTC1;
			if (ss_enabwed && (ss->type & ATOM_EXTEWNAW_SS_MASK))
				awgs.v3.ucMiscInfo |= PIXEW_CWOCK_MISC_WEF_DIV_SWC;
			awgs.v3.ucTwansmittewId = encodew_id;
			awgs.v3.ucEncodewMode = encodew_mode;
			bweak;
		case 5:
			awgs.v5.ucCWTC = cwtc_id;
			awgs.v5.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v5.ucWefDiv = wef_div;
			awgs.v5.usFbDiv = cpu_to_we16(fb_div);
			awgs.v5.uwFbDivDecFwac = cpu_to_we32(fwac_fb_div * 100000);
			awgs.v5.ucPostDiv = post_div;
			awgs.v5.ucMiscInfo = 0; /* HDMI depth, etc. */
			if (ss_enabwed && (ss->type & ATOM_EXTEWNAW_SS_MASK))
				awgs.v5.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_WEF_DIV_SWC;
			if (encodew_mode == ATOM_ENCODEW_MODE_HDMI) {
				switch (bpc) {
				case 8:
				defauwt:
					awgs.v5.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_HDMI_24BPP;
					bweak;
				case 10:
					/* yes this is cowwect, the atom define is wwong */
					awgs.v5.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_HDMI_32BPP;
					bweak;
				case 12:
					/* yes this is cowwect, the atom define is wwong */
					awgs.v5.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_HDMI_30BPP;
					bweak;
				}
			}
			awgs.v5.ucTwansmittewID = encodew_id;
			awgs.v5.ucEncodewMode = encodew_mode;
			awgs.v5.ucPpww = pww_id;
			bweak;
		case 6:
			awgs.v6.uwDispEngCwkFweq = cpu_to_we32(cwtc_id << 24 | cwock / 10);
			awgs.v6.ucWefDiv = wef_div;
			awgs.v6.usFbDiv = cpu_to_we16(fb_div);
			awgs.v6.uwFbDivDecFwac = cpu_to_we32(fwac_fb_div * 100000);
			awgs.v6.ucPostDiv = post_div;
			awgs.v6.ucMiscInfo = 0; /* HDMI depth, etc. */
			if (ss_enabwed && (ss->type & ATOM_EXTEWNAW_SS_MASK))
				awgs.v6.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_WEF_DIV_SWC;
			if (encodew_mode == ATOM_ENCODEW_MODE_HDMI) {
				switch (bpc) {
				case 8:
				defauwt:
					awgs.v6.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_24BPP;
					bweak;
				case 10:
					awgs.v6.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_30BPP_V6;
					bweak;
				case 12:
					awgs.v6.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_36BPP_V6;
					bweak;
				case 16:
					awgs.v6.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_48BPP;
					bweak;
				}
			}
			awgs.v6.ucTwansmittewID = encodew_id;
			awgs.v6.ucEncodewMode = encodew_mode;
			awgs.v6.ucPpww = pww_id;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
			wetuwn;
		}
		bweak;
	defauwt:
		DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
		wetuwn;
	}

	atom_execute_tabwe(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

static boow atombios_cwtc_pwepawe_pww(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew =
		to_wadeon_encodew(wadeon_cwtc->encodew);
	int encodew_mode = atombios_get_encodew_mode(wadeon_cwtc->encodew);

	wadeon_cwtc->bpc = 8;
	wadeon_cwtc->ss_enabwed = fawse;

	if ((wadeon_encodew->active_device & (ATOM_DEVICE_WCD_SUPPOWT | ATOM_DEVICE_DFP_SUPPOWT)) ||
	    (wadeon_encodew_get_dp_bwidge_encodew_id(wadeon_cwtc->encodew) != ENCODEW_OBJECT_ID_NONE)) {
		stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
		stwuct dwm_connectow *connectow =
			wadeon_get_connectow_fow_encodew(wadeon_cwtc->encodew);
		stwuct wadeon_connectow *wadeon_connectow =
			to_wadeon_connectow(connectow);
		stwuct wadeon_connectow_atom_dig *dig_connectow =
			wadeon_connectow->con_pwiv;
		int dp_cwock;

		/* Assign mode cwock fow hdmi deep cowow max cwock wimit check */
		wadeon_connectow->pixewcwock_fow_modeset = mode->cwock;
		wadeon_cwtc->bpc = wadeon_get_monitow_bpc(connectow);

		switch (encodew_mode) {
		case ATOM_ENCODEW_MODE_DP_MST:
		case ATOM_ENCODEW_MODE_DP:
			/* DP/eDP */
			dp_cwock = dig_connectow->dp_cwock / 10;
			if (ASIC_IS_DCE4(wdev))
				wadeon_cwtc->ss_enabwed =
					wadeon_atombios_get_asic_ss_info(wdev, &wadeon_cwtc->ss,
									 ASIC_INTEWNAW_SS_ON_DP,
									 dp_cwock);
			ewse {
				if (dp_cwock == 16200) {
					wadeon_cwtc->ss_enabwed =
						wadeon_atombios_get_ppww_ss_info(wdev,
										 &wadeon_cwtc->ss,
										 ATOM_DP_SS_ID2);
					if (!wadeon_cwtc->ss_enabwed)
						wadeon_cwtc->ss_enabwed =
							wadeon_atombios_get_ppww_ss_info(wdev,
											 &wadeon_cwtc->ss,
											 ATOM_DP_SS_ID1);
				} ewse {
					wadeon_cwtc->ss_enabwed =
						wadeon_atombios_get_ppww_ss_info(wdev,
										 &wadeon_cwtc->ss,
										 ATOM_DP_SS_ID1);
				}
				/* disabwe spwead spectwum on DCE3 DP */
				wadeon_cwtc->ss_enabwed = fawse;
			}
			bweak;
		case ATOM_ENCODEW_MODE_WVDS:
			if (ASIC_IS_DCE4(wdev))
				wadeon_cwtc->ss_enabwed =
					wadeon_atombios_get_asic_ss_info(wdev,
									 &wadeon_cwtc->ss,
									 dig->wcd_ss_id,
									 mode->cwock / 10);
			ewse
				wadeon_cwtc->ss_enabwed =
					wadeon_atombios_get_ppww_ss_info(wdev,
									 &wadeon_cwtc->ss,
									 dig->wcd_ss_id);
			bweak;
		case ATOM_ENCODEW_MODE_DVI:
			if (ASIC_IS_DCE4(wdev))
				wadeon_cwtc->ss_enabwed =
					wadeon_atombios_get_asic_ss_info(wdev,
									 &wadeon_cwtc->ss,
									 ASIC_INTEWNAW_SS_ON_TMDS,
									 mode->cwock / 10);
			bweak;
		case ATOM_ENCODEW_MODE_HDMI:
			if (ASIC_IS_DCE4(wdev))
				wadeon_cwtc->ss_enabwed =
					wadeon_atombios_get_asic_ss_info(wdev,
									 &wadeon_cwtc->ss,
									 ASIC_INTEWNAW_SS_ON_HDMI,
									 mode->cwock / 10);
			bweak;
		defauwt:
			bweak;
		}
	}

	/* adjust pixew cwock as needed */
	wadeon_cwtc->adjusted_cwock = atombios_adjust_pww(cwtc, mode);

	wetuwn twue;
}

static void atombios_cwtc_set_pww(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew =
		to_wadeon_encodew(wadeon_cwtc->encodew);
	u32 pww_cwock = mode->cwock;
	u32 cwock = mode->cwock;
	u32 wef_div = 0, fb_div = 0, fwac_fb_div = 0, post_div = 0;
	stwuct wadeon_pww *pww;
	int encodew_mode = atombios_get_encodew_mode(wadeon_cwtc->encodew);

	/* pass the actuaw cwock to atombios_cwtc_pwogwam_pww fow DCE5,6 fow HDMI */
	if (ASIC_IS_DCE5(wdev) &&
	    (encodew_mode == ATOM_ENCODEW_MODE_HDMI) &&
	    (wadeon_cwtc->bpc > 8))
		cwock = wadeon_cwtc->adjusted_cwock;

	switch (wadeon_cwtc->pww_id) {
	case ATOM_PPWW1:
		pww = &wdev->cwock.p1pww;
		bweak;
	case ATOM_PPWW2:
		pww = &wdev->cwock.p2pww;
		bweak;
	case ATOM_DCPWW:
	case ATOM_PPWW_INVAWID:
	defauwt:
		pww = &wdev->cwock.dcpww;
		bweak;
	}

	/* update pww pawams */
	pww->fwags = wadeon_cwtc->pww_fwags;
	pww->wefewence_div = wadeon_cwtc->pww_wefewence_div;
	pww->post_div = wadeon_cwtc->pww_post_div;

	if (wadeon_encodew->active_device & (ATOM_DEVICE_TV_SUPPOWT))
		/* TV seems to pwefew the wegacy awgo on some boawds */
		wadeon_compute_pww_wegacy(pww, wadeon_cwtc->adjusted_cwock, &pww_cwock,
					  &fb_div, &fwac_fb_div, &wef_div, &post_div);
	ewse if (ASIC_IS_AVIVO(wdev))
		wadeon_compute_pww_avivo(pww, wadeon_cwtc->adjusted_cwock, &pww_cwock,
					 &fb_div, &fwac_fb_div, &wef_div, &post_div);
	ewse
		wadeon_compute_pww_wegacy(pww, wadeon_cwtc->adjusted_cwock, &pww_cwock,
					  &fb_div, &fwac_fb_div, &wef_div, &post_div);

	atombios_cwtc_pwogwam_ss(wdev, ATOM_DISABWE, wadeon_cwtc->pww_id,
				 wadeon_cwtc->cwtc_id, &wadeon_cwtc->ss);

	atombios_cwtc_pwogwam_pww(cwtc, wadeon_cwtc->cwtc_id, wadeon_cwtc->pww_id,
				  encodew_mode, wadeon_encodew->encodew_id, cwock,
				  wef_div, fb_div, fwac_fb_div, post_div,
				  wadeon_cwtc->bpc, wadeon_cwtc->ss_enabwed, &wadeon_cwtc->ss);

	if (wadeon_cwtc->ss_enabwed) {
		/* cawcuwate ss amount and step size */
		if (ASIC_IS_DCE4(wdev)) {
			u32 step_size;
			u32 amount = (((fb_div * 10) + fwac_fb_div) *
				      (u32)wadeon_cwtc->ss.pewcentage) /
				(100 * (u32)wadeon_cwtc->ss.pewcentage_dividew);
			wadeon_cwtc->ss.amount = (amount / 10) & ATOM_PPWW_SS_AMOUNT_V2_FBDIV_MASK;
			wadeon_cwtc->ss.amount |= ((amount - (amount / 10)) << ATOM_PPWW_SS_AMOUNT_V2_NFWAC_SHIFT) &
				ATOM_PPWW_SS_AMOUNT_V2_NFWAC_MASK;
			if (wadeon_cwtc->ss.type & ATOM_PPWW_SS_TYPE_V2_CENTWE_SPWEAD)
				step_size = (4 * amount * wef_div * ((u32)wadeon_cwtc->ss.wate * 2048)) /
					(125 * 25 * pww->wefewence_fweq / 100);
			ewse
				step_size = (2 * amount * wef_div * ((u32)wadeon_cwtc->ss.wate * 2048)) /
					(125 * 25 * pww->wefewence_fweq / 100);
			wadeon_cwtc->ss.step = step_size;
		}

		atombios_cwtc_pwogwam_ss(wdev, ATOM_ENABWE, wadeon_cwtc->pww_id,
					 wadeon_cwtc->cwtc_id, &wadeon_cwtc->ss);
	}
}

static int dce4_cwtc_do_set_base(stwuct dwm_cwtc *cwtc,
				 stwuct dwm_fwamebuffew *fb,
				 int x, int y, int atomic)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_fwamebuffew *tawget_fb;
	stwuct dwm_gem_object *obj;
	stwuct wadeon_bo *wbo;
	uint64_t fb_wocation;
	uint32_t fb_fowmat, fb_pitch_pixews, tiwing_fwags;
	unsigned bankw, bankh, mtaspect, tiwe_spwit;
	u32 fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_NONE);
	u32 tmp, viewpowt_w, viewpowt_h;
	int w;
	boow bypass_wut = fawse;

	/* no fb bound */
	if (!atomic && !cwtc->pwimawy->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	if (atomic)
		tawget_fb = fb;
	ewse
		tawget_fb = cwtc->pwimawy->fb;

	/* If atomic, assume fb object is pinned & idwe & fenced and
	 * just update base pointews
	 */
	obj = tawget_fb->obj[0];
	wbo = gem_to_wadeon_bo(obj);
	w = wadeon_bo_wesewve(wbo, fawse);
	if (unwikewy(w != 0))
		wetuwn w;

	if (atomic)
		fb_wocation = wadeon_bo_gpu_offset(wbo);
	ewse {
		w = wadeon_bo_pin(wbo, WADEON_GEM_DOMAIN_VWAM, &fb_wocation);
		if (unwikewy(w != 0)) {
			wadeon_bo_unwesewve(wbo);
			wetuwn -EINVAW;
		}
	}

	wadeon_bo_get_tiwing_fwags(wbo, &tiwing_fwags, NUWW);
	wadeon_bo_unwesewve(wbo);

	switch (tawget_fb->fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_8BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_INDEXED));
		bweak;
	case DWM_FOWMAT_XWGB4444:
	case DWM_FOWMAT_AWGB4444:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_16BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB4444));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_AWGB1555:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_16BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB1555));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_BGWX5551:
	case DWM_FOWMAT_BGWA5551:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_16BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_BGWA5551));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_WGB565:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_16BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB565));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_32BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB8888));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN32);
#endif
		bweak;
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_32BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB2101010));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN32);
#endif
		/* Gweatew 8 bpc fb needs to bypass hw-wut to wetain pwecision */
		bypass_wut = twue;
		bweak;
	case DWM_FOWMAT_BGWX1010102:
	case DWM_FOWMAT_BGWA1010102:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_32BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_BGWA1010102));
#ifdef __BIG_ENDIAN
		fb_swap = EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN32);
#endif
		/* Gweatew 8 bpc fb needs to bypass hw-wut to wetain pwecision */
		bypass_wut = twue;
		bweak;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		fb_fowmat = (EVEWGWEEN_GWPH_DEPTH(EVEWGWEEN_GWPH_DEPTH_32BPP) |
			     EVEWGWEEN_GWPH_FOWMAT(EVEWGWEEN_GWPH_FOWMAT_AWGB8888));
		fb_swap = (EVEWGWEEN_GWPH_WED_CWOSSBAW(EVEWGWEEN_GWPH_WED_SEW_B) |
			   EVEWGWEEN_GWPH_BWUE_CWOSSBAW(EVEWGWEEN_GWPH_BWUE_SEW_W));
#ifdef __BIG_ENDIAN
		fb_swap |= EVEWGWEEN_GWPH_ENDIAN_SWAP(EVEWGWEEN_GWPH_ENDIAN_8IN32);
#endif
		bweak;
	defauwt:
		DWM_EWWOW("Unsuppowted scween fowmat %p4cc\n",
			  &tawget_fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	if (tiwing_fwags & WADEON_TIWING_MACWO) {
		evewgween_tiwing_fiewds(tiwing_fwags, &bankw, &bankh, &mtaspect, &tiwe_spwit);

		/* Set NUM_BANKS. */
		if (wdev->famiwy >= CHIP_TAHITI) {
			unsigned index, num_banks;

			if (wdev->famiwy >= CHIP_BONAIWE) {
				unsigned tiweb, tiwe_spwit_bytes;

				/* Cawcuwate the macwotiwe mode index. */
				tiwe_spwit_bytes = 64 << tiwe_spwit;
				tiweb = 8 * 8 * tawget_fb->fowmat->cpp[0];
				tiweb = min(tiwe_spwit_bytes, tiweb);

				fow (index = 0; tiweb > 64; index++)
					tiweb >>= 1;

				if (index >= 16) {
					DWM_EWWOW("Wwong scween bpp (%u) ow tiwe spwit (%u)\n",
						  tawget_fb->fowmat->cpp[0] * 8,
						  tiwe_spwit);
					wetuwn -EINVAW;
				}

				num_banks = (wdev->config.cik.macwotiwe_mode_awway[index] >> 6) & 0x3;
			} ewse {
				switch (tawget_fb->fowmat->cpp[0] * 8) {
				case 8:
					index = 10;
					bweak;
				case 16:
					index = SI_TIWE_MODE_COWOW_2D_SCANOUT_16BPP;
					bweak;
				defauwt:
				case 32:
					index = SI_TIWE_MODE_COWOW_2D_SCANOUT_32BPP;
					bweak;
				}

				num_banks = (wdev->config.si.tiwe_mode_awway[index] >> 20) & 0x3;
			}

			fb_fowmat |= EVEWGWEEN_GWPH_NUM_BANKS(num_banks);
		} ewse {
			/* NI and owdew. */
			if (wdev->famiwy >= CHIP_CAYMAN)
				tmp = wdev->config.cayman.tiwe_config;
			ewse
				tmp = wdev->config.evewgween.tiwe_config;

			switch ((tmp & 0xf0) >> 4) {
			case 0: /* 4 banks */
				fb_fowmat |= EVEWGWEEN_GWPH_NUM_BANKS(EVEWGWEEN_ADDW_SUWF_4_BANK);
				bweak;
			case 1: /* 8 banks */
			defauwt:
				fb_fowmat |= EVEWGWEEN_GWPH_NUM_BANKS(EVEWGWEEN_ADDW_SUWF_8_BANK);
				bweak;
			case 2: /* 16 banks */
				fb_fowmat |= EVEWGWEEN_GWPH_NUM_BANKS(EVEWGWEEN_ADDW_SUWF_16_BANK);
				bweak;
			}
		}

		fb_fowmat |= EVEWGWEEN_GWPH_AWWAY_MODE(EVEWGWEEN_GWPH_AWWAY_2D_TIWED_THIN1);
		fb_fowmat |= EVEWGWEEN_GWPH_TIWE_SPWIT(tiwe_spwit);
		fb_fowmat |= EVEWGWEEN_GWPH_BANK_WIDTH(bankw);
		fb_fowmat |= EVEWGWEEN_GWPH_BANK_HEIGHT(bankh);
		fb_fowmat |= EVEWGWEEN_GWPH_MACWO_TIWE_ASPECT(mtaspect);
		if (wdev->famiwy >= CHIP_BONAIWE) {
			/* XXX need to know mowe about the suwface tiwing mode */
			fb_fowmat |= CIK_GWPH_MICWO_TIWE_MODE(CIK_DISPWAY_MICWO_TIWING);
		}
	} ewse if (tiwing_fwags & WADEON_TIWING_MICWO)
		fb_fowmat |= EVEWGWEEN_GWPH_AWWAY_MODE(EVEWGWEEN_GWPH_AWWAY_1D_TIWED_THIN1);

	if (wdev->famiwy >= CHIP_BONAIWE) {
		/* Wead the pipe config fwom the 2D TIWED SCANOUT mode.
		 * It shouwd be the same fow the othew modes too, but not aww
		 * modes set the pipe config fiewd. */
		u32 pipe_config = (wdev->config.cik.tiwe_mode_awway[10] >> 6) & 0x1f;

		fb_fowmat |= CIK_GWPH_PIPE_CONFIG(pipe_config);
	} ewse if ((wdev->famiwy == CHIP_TAHITI) ||
		   (wdev->famiwy == CHIP_PITCAIWN))
		fb_fowmat |= SI_GWPH_PIPE_CONFIG(SI_ADDW_SUWF_P8_32x32_8x16);
	ewse if ((wdev->famiwy == CHIP_VEWDE) ||
		 (wdev->famiwy == CHIP_OWAND) ||
		 (wdev->famiwy == CHIP_HAINAN)) /* fow compweteness.  HAINAN has no dispway hw */
		fb_fowmat |= SI_GWPH_PIPE_CONFIG(SI_ADDW_SUWF_P4_8x16);

	switch (wadeon_cwtc->cwtc_id) {
	case 0:
		WWEG32(AVIVO_D1VGA_CONTWOW, 0);
		bweak;
	case 1:
		WWEG32(AVIVO_D2VGA_CONTWOW, 0);
		bweak;
	case 2:
		WWEG32(EVEWGWEEN_D3VGA_CONTWOW, 0);
		bweak;
	case 3:
		WWEG32(EVEWGWEEN_D4VGA_CONTWOW, 0);
		bweak;
	case 4:
		WWEG32(EVEWGWEEN_D5VGA_CONTWOW, 0);
		bweak;
	case 5:
		WWEG32(EVEWGWEEN_D6VGA_CONTWOW, 0);
		bweak;
	defauwt:
		bweak;
	}

	/* Make suwe suwface addwess is updated at vewticaw bwank wathew than
	 * howizontaw bwank
	 */
	WWEG32(EVEWGWEEN_GWPH_FWIP_CONTWOW + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH + wadeon_cwtc->cwtc_offset,
	       uppew_32_bits(fb_wocation));
	WWEG32(EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH + wadeon_cwtc->cwtc_offset,
	       uppew_32_bits(fb_wocation));
	WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32)fb_wocation & EVEWGWEEN_GWPH_SUWFACE_ADDWESS_MASK);
	WWEG32(EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32) fb_wocation & EVEWGWEEN_GWPH_SUWFACE_ADDWESS_MASK);
	WWEG32(EVEWGWEEN_GWPH_CONTWOW + wadeon_cwtc->cwtc_offset, fb_fowmat);
	WWEG32(EVEWGWEEN_GWPH_SWAP_CONTWOW + wadeon_cwtc->cwtc_offset, fb_swap);

	/*
	 * The WUT onwy has 256 swots fow indexing by a 8 bpc fb. Bypass the WUT
	 * fow > 8 bpc scanout to avoid twuncation of fb indices to 8 msb's, to
	 * wetain the fuww pwecision thwoughout the pipewine.
	 */
	WWEG32_P(EVEWGWEEN_GWPH_WUT_10BIT_BYPASS_CONTWOW + wadeon_cwtc->cwtc_offset,
		 (bypass_wut ? EVEWGWEEN_WUT_10BIT_BYPASS_EN : 0),
		 ~EVEWGWEEN_WUT_10BIT_BYPASS_EN);

	if (bypass_wut)
		DWM_DEBUG_KMS("Bypassing hawdwawe WUT due to 10 bit fb scanout.\n");

	WWEG32(EVEWGWEEN_GWPH_SUWFACE_OFFSET_X + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_GWPH_SUWFACE_OFFSET_Y + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_GWPH_X_STAWT + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_GWPH_Y_STAWT + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_GWPH_X_END + wadeon_cwtc->cwtc_offset, tawget_fb->width);
	WWEG32(EVEWGWEEN_GWPH_Y_END + wadeon_cwtc->cwtc_offset, tawget_fb->height);

	fb_pitch_pixews = tawget_fb->pitches[0] / tawget_fb->fowmat->cpp[0];
	WWEG32(EVEWGWEEN_GWPH_PITCH + wadeon_cwtc->cwtc_offset, fb_pitch_pixews);
	WWEG32(EVEWGWEEN_GWPH_ENABWE + wadeon_cwtc->cwtc_offset, 1);

	if (wdev->famiwy >= CHIP_BONAIWE)
		WWEG32(CIK_WB_DESKTOP_HEIGHT + wadeon_cwtc->cwtc_offset,
		       tawget_fb->height);
	ewse
		WWEG32(EVEWGWEEN_DESKTOP_HEIGHT + wadeon_cwtc->cwtc_offset,
		       tawget_fb->height);
	x &= ~3;
	y &= ~1;
	WWEG32(EVEWGWEEN_VIEWPOWT_STAWT + wadeon_cwtc->cwtc_offset,
	       (x << 16) | y);
	viewpowt_w = cwtc->mode.hdispway;
	viewpowt_h = (cwtc->mode.vdispway + 1) & ~1;
	if ((wdev->famiwy >= CHIP_BONAIWE) &&
	    (cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE))
		viewpowt_h *= 2;
	WWEG32(EVEWGWEEN_VIEWPOWT_SIZE + wadeon_cwtc->cwtc_offset,
	       (viewpowt_w << 16) | viewpowt_h);

	/* set pagefwip to happen anywhewe in vbwank intewvaw */
	WWEG32(EVEWGWEEN_MASTEW_UPDATE_MODE + wadeon_cwtc->cwtc_offset, 0);

	if (!atomic && fb && fb != cwtc->pwimawy->fb) {
		wbo = gem_to_wadeon_bo(fb->obj[0]);
		w = wadeon_bo_wesewve(wbo, fawse);
		if (unwikewy(w != 0))
			wetuwn w;
		wadeon_bo_unpin(wbo);
		wadeon_bo_unwesewve(wbo);
	}

	/* Bytes pew pixew may have changed */
	wadeon_bandwidth_update(wdev);

	wetuwn 0;
}

static int avivo_cwtc_do_set_base(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_fwamebuffew *fb,
				  int x, int y, int atomic)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_gem_object *obj;
	stwuct wadeon_bo *wbo;
	stwuct dwm_fwamebuffew *tawget_fb;
	uint64_t fb_wocation;
	uint32_t fb_fowmat, fb_pitch_pixews, tiwing_fwags;
	u32 fb_swap = W600_D1GWPH_SWAP_ENDIAN_NONE;
	u32 viewpowt_w, viewpowt_h;
	int w;
	boow bypass_wut = fawse;

	/* no fb bound */
	if (!atomic && !cwtc->pwimawy->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	if (atomic)
		tawget_fb = fb;
	ewse
		tawget_fb = cwtc->pwimawy->fb;

	obj = tawget_fb->obj[0];
	wbo = gem_to_wadeon_bo(obj);
	w = wadeon_bo_wesewve(wbo, fawse);
	if (unwikewy(w != 0))
		wetuwn w;

	/* If atomic, assume fb object is pinned & idwe & fenced and
	 * just update base pointews
	 */
	if (atomic)
		fb_wocation = wadeon_bo_gpu_offset(wbo);
	ewse {
		w = wadeon_bo_pin(wbo, WADEON_GEM_DOMAIN_VWAM, &fb_wocation);
		if (unwikewy(w != 0)) {
			wadeon_bo_unwesewve(wbo);
			wetuwn -EINVAW;
		}
	}
	wadeon_bo_get_tiwing_fwags(wbo, &tiwing_fwags, NUWW);
	wadeon_bo_unwesewve(wbo);

	switch (tawget_fb->fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_8BPP |
		    AVIVO_D1GWPH_CONTWOW_8BPP_INDEXED;
		bweak;
	case DWM_FOWMAT_XWGB4444:
	case DWM_FOWMAT_AWGB4444:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_16BPP |
		    AVIVO_D1GWPH_CONTWOW_16BPP_AWGB4444;
#ifdef __BIG_ENDIAN
		fb_swap = W600_D1GWPH_SWAP_ENDIAN_16BIT;
#endif
		bweak;
	case DWM_FOWMAT_XWGB1555:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_16BPP |
		    AVIVO_D1GWPH_CONTWOW_16BPP_AWGB1555;
#ifdef __BIG_ENDIAN
		fb_swap = W600_D1GWPH_SWAP_ENDIAN_16BIT;
#endif
		bweak;
	case DWM_FOWMAT_WGB565:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_16BPP |
		    AVIVO_D1GWPH_CONTWOW_16BPP_WGB565;
#ifdef __BIG_ENDIAN
		fb_swap = W600_D1GWPH_SWAP_ENDIAN_16BIT;
#endif
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_32BPP |
		    AVIVO_D1GWPH_CONTWOW_32BPP_AWGB8888;
#ifdef __BIG_ENDIAN
		fb_swap = W600_D1GWPH_SWAP_ENDIAN_32BIT;
#endif
		bweak;
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_32BPP |
		    AVIVO_D1GWPH_CONTWOW_32BPP_AWGB2101010;
#ifdef __BIG_ENDIAN
		fb_swap = W600_D1GWPH_SWAP_ENDIAN_32BIT;
#endif
		/* Gweatew 8 bpc fb needs to bypass hw-wut to wetain pwecision */
		bypass_wut = twue;
		bweak;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		fb_fowmat =
		    AVIVO_D1GWPH_CONTWOW_DEPTH_32BPP |
		    AVIVO_D1GWPH_CONTWOW_32BPP_AWGB8888;
		if (wdev->famiwy >= CHIP_W600)
			fb_swap =
			    (W600_D1GWPH_WED_CWOSSBAW(W600_D1GWPH_WED_SEW_B) |
			     W600_D1GWPH_BWUE_CWOSSBAW(W600_D1GWPH_BWUE_SEW_W));
		ewse /* DCE1 (W5xx) */
			fb_fowmat |= AVIVO_D1GWPH_SWAP_WB;
#ifdef __BIG_ENDIAN
		fb_swap |= W600_D1GWPH_SWAP_ENDIAN_32BIT;
#endif
		bweak;
	defauwt:
		DWM_EWWOW("Unsuppowted scween fowmat %p4cc\n",
			  &tawget_fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	if (wdev->famiwy >= CHIP_W600) {
		if (tiwing_fwags & WADEON_TIWING_MACWO)
			fb_fowmat |= W600_D1GWPH_AWWAY_MODE_2D_TIWED_THIN1;
		ewse if (tiwing_fwags & WADEON_TIWING_MICWO)
			fb_fowmat |= W600_D1GWPH_AWWAY_MODE_1D_TIWED_THIN1;
	} ewse {
		if (tiwing_fwags & WADEON_TIWING_MACWO)
			fb_fowmat |= AVIVO_D1GWPH_MACWO_ADDWESS_MODE;

		if (tiwing_fwags & WADEON_TIWING_MICWO)
			fb_fowmat |= AVIVO_D1GWPH_TIWED;
	}

	if (wadeon_cwtc->cwtc_id == 0)
		WWEG32(AVIVO_D1VGA_CONTWOW, 0);
	ewse
		WWEG32(AVIVO_D2VGA_CONTWOW, 0);

	/* Make suwe suwface addwess is update at vewticaw bwank wathew than
	 * howizontaw bwank
	 */
	WWEG32(AVIVO_D1GWPH_FWIP_CONTWOW + wadeon_cwtc->cwtc_offset, 0);

	if (wdev->famiwy >= CHIP_WV770) {
		if (wadeon_cwtc->cwtc_id) {
			WWEG32(W700_D2GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH, uppew_32_bits(fb_wocation));
			WWEG32(W700_D2GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH, uppew_32_bits(fb_wocation));
		} ewse {
			WWEG32(W700_D1GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH, uppew_32_bits(fb_wocation));
			WWEG32(W700_D1GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH, uppew_32_bits(fb_wocation));
		}
	}
	WWEG32(AVIVO_D1GWPH_PWIMAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32) fb_wocation);
	WWEG32(AVIVO_D1GWPH_SECONDAWY_SUWFACE_ADDWESS +
	       wadeon_cwtc->cwtc_offset, (u32) fb_wocation);
	WWEG32(AVIVO_D1GWPH_CONTWOW + wadeon_cwtc->cwtc_offset, fb_fowmat);
	if (wdev->famiwy >= CHIP_W600)
		WWEG32(W600_D1GWPH_SWAP_CONTWOW + wadeon_cwtc->cwtc_offset, fb_swap);

	/* WUT onwy has 256 swots fow 8 bpc fb. Bypass fow > 8 bpc scanout fow pwecision */
	WWEG32_P(AVIVO_D1GWPH_WUT_SEW + wadeon_cwtc->cwtc_offset,
		 (bypass_wut ? AVIVO_WUT_10BIT_BYPASS_EN : 0), ~AVIVO_WUT_10BIT_BYPASS_EN);

	if (bypass_wut)
		DWM_DEBUG_KMS("Bypassing hawdwawe WUT due to 10 bit fb scanout.\n");

	WWEG32(AVIVO_D1GWPH_SUWFACE_OFFSET_X + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_D1GWPH_SUWFACE_OFFSET_Y + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_D1GWPH_X_STAWT + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_D1GWPH_Y_STAWT + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_D1GWPH_X_END + wadeon_cwtc->cwtc_offset, tawget_fb->width);
	WWEG32(AVIVO_D1GWPH_Y_END + wadeon_cwtc->cwtc_offset, tawget_fb->height);

	fb_pitch_pixews = tawget_fb->pitches[0] / tawget_fb->fowmat->cpp[0];
	WWEG32(AVIVO_D1GWPH_PITCH + wadeon_cwtc->cwtc_offset, fb_pitch_pixews);
	WWEG32(AVIVO_D1GWPH_ENABWE + wadeon_cwtc->cwtc_offset, 1);

	WWEG32(AVIVO_D1MODE_DESKTOP_HEIGHT + wadeon_cwtc->cwtc_offset,
	       tawget_fb->height);
	x &= ~3;
	y &= ~1;
	WWEG32(AVIVO_D1MODE_VIEWPOWT_STAWT + wadeon_cwtc->cwtc_offset,
	       (x << 16) | y);
	viewpowt_w = cwtc->mode.hdispway;
	viewpowt_h = (cwtc->mode.vdispway + 1) & ~1;
	WWEG32(AVIVO_D1MODE_VIEWPOWT_SIZE + wadeon_cwtc->cwtc_offset,
	       (viewpowt_w << 16) | viewpowt_h);

	/* set pagefwip to happen onwy at stawt of vbwank intewvaw (fwont powch) */
	WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_MODE + wadeon_cwtc->cwtc_offset, 3);

	if (!atomic && fb && fb != cwtc->pwimawy->fb) {
		wbo = gem_to_wadeon_bo(fb->obj[0]);
		w = wadeon_bo_wesewve(wbo, fawse);
		if (unwikewy(w != 0))
			wetuwn w;
		wadeon_bo_unpin(wbo);
		wadeon_bo_unwesewve(wbo);
	}

	/* Bytes pew pixew may have changed */
	wadeon_bandwidth_update(wdev);

	wetuwn 0;
}

int atombios_cwtc_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
			   stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (ASIC_IS_DCE4(wdev))
		wetuwn dce4_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
	ewse if (ASIC_IS_AVIVO(wdev))
		wetuwn avivo_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
	ewse
		wetuwn wadeon_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
}

int atombios_cwtc_set_base_atomic(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_fwamebuffew *fb,
				  int x, int y, enum mode_set_atomic state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (ASIC_IS_DCE4(wdev))
		wetuwn dce4_cwtc_do_set_base(cwtc, fb, x, y, 1);
	ewse if (ASIC_IS_AVIVO(wdev))
		wetuwn avivo_cwtc_do_set_base(cwtc, fb, x, y, 1);
	ewse
		wetuwn wadeon_cwtc_do_set_base(cwtc, fb, x, y, 1);
}

/* pwopewwy set additionaw wegs when using atombios */
static void wadeon_wegacy_atom_fixup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	u32 disp_mewge_cntw;

	switch (wadeon_cwtc->cwtc_id) {
	case 0:
		disp_mewge_cntw = WWEG32(WADEON_DISP_MEWGE_CNTW);
		disp_mewge_cntw &= ~WADEON_DISP_WGB_OFFSET_EN;
		WWEG32(WADEON_DISP_MEWGE_CNTW, disp_mewge_cntw);
		bweak;
	case 1:
		disp_mewge_cntw = WWEG32(WADEON_DISP2_MEWGE_CNTW);
		disp_mewge_cntw &= ~WADEON_DISP2_WGB_OFFSET_EN;
		WWEG32(WADEON_DISP2_MEWGE_CNTW, disp_mewge_cntw);
		WWEG32(WADEON_FP_H2_SYNC_STWT_WID,   WWEG32(WADEON_CWTC2_H_SYNC_STWT_WID));
		WWEG32(WADEON_FP_V2_SYNC_STWT_WID,   WWEG32(WADEON_CWTC2_V_SYNC_STWT_WID));
		bweak;
	}
}

/**
 * wadeon_get_pww_use_mask - wook up a mask of which ppwws awe in use
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the mask of which PPWWs (Pixew PWWs) awe in use.
 */
static u32 wadeon_get_pww_use_mask(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *test_cwtc;
	stwuct wadeon_cwtc *test_wadeon_cwtc;
	u32 pww_in_use = 0;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;

		test_wadeon_cwtc = to_wadeon_cwtc(test_cwtc);
		if (test_wadeon_cwtc->pww_id != ATOM_PPWW_INVAWID)
			pww_in_use |= (1 << test_wadeon_cwtc->pww_id);
	}
	wetuwn pww_in_use;
}

/**
 * wadeon_get_shawed_dp_ppww - wetuwn the PPWW used by anothew cwtc fow DP
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) used by anothew cwtc/encodew which is
 * awso in DP mode.  Fow DP, a singwe PPWW can be used fow aww DP
 * cwtcs/encodews.
 */
static int wadeon_get_shawed_dp_ppww(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_cwtc *test_cwtc;
	stwuct wadeon_cwtc *test_wadeon_cwtc;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;
		test_wadeon_cwtc = to_wadeon_cwtc(test_cwtc);
		if (test_wadeon_cwtc->encodew &&
		    ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(test_wadeon_cwtc->encodew))) {
			/* PPWW2 is excwusive to UNIPHYA on DCE61 */
			if (ASIC_IS_DCE61(wdev) && !ASIC_IS_DCE8(wdev) &&
			    test_wadeon_cwtc->pww_id == ATOM_PPWW2)
				continue;
			/* fow DP use the same PWW fow aww */
			if (test_wadeon_cwtc->pww_id != ATOM_PPWW_INVAWID)
				wetuwn test_wadeon_cwtc->pww_id;
		}
	}
	wetuwn ATOM_PPWW_INVAWID;
}

/**
 * wadeon_get_shawed_nondp_ppww - wetuwn the PPWW used by anothew non-DP cwtc
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) used by anothew non-DP cwtc/encodew which can
 * be shawed (i.e., same cwock).
 */
static int wadeon_get_shawed_nondp_ppww(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_cwtc *test_cwtc;
	stwuct wadeon_cwtc *test_wadeon_cwtc;
	u32 adjusted_cwock, test_adjusted_cwock;

	adjusted_cwock = wadeon_cwtc->adjusted_cwock;

	if (adjusted_cwock == 0)
		wetuwn ATOM_PPWW_INVAWID;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;
		test_wadeon_cwtc = to_wadeon_cwtc(test_cwtc);
		if (test_wadeon_cwtc->encodew &&
		    !ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(test_wadeon_cwtc->encodew))) {
			/* PPWW2 is excwusive to UNIPHYA on DCE61 */
			if (ASIC_IS_DCE61(wdev) && !ASIC_IS_DCE8(wdev) &&
			    test_wadeon_cwtc->pww_id == ATOM_PPWW2)
				continue;
			/* check if we awe awweady dwiving this connectow with anothew cwtc */
			if (test_wadeon_cwtc->connectow == wadeon_cwtc->connectow) {
				/* if we awe, wetuwn that pww */
				if (test_wadeon_cwtc->pww_id != ATOM_PPWW_INVAWID)
					wetuwn test_wadeon_cwtc->pww_id;
			}
			/* fow non-DP check the cwock */
			test_adjusted_cwock = test_wadeon_cwtc->adjusted_cwock;
			if ((cwtc->mode.cwock == test_cwtc->mode.cwock) &&
			    (adjusted_cwock == test_adjusted_cwock) &&
			    (wadeon_cwtc->ss_enabwed == test_wadeon_cwtc->ss_enabwed) &&
			    (test_wadeon_cwtc->pww_id != ATOM_PPWW_INVAWID))
				wetuwn test_wadeon_cwtc->pww_id;
		}
	}
	wetuwn ATOM_PPWW_INVAWID;
}

/**
 * wadeon_atom_pick_pww - Awwocate a PPWW fow use by the cwtc.
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) to be used by the cwtc.  Fow DP monitows
 * a singwe PPWW can be used fow aww DP cwtcs/encodews.  Fow non-DP
 * monitows a dedicated PPWW must be used.  If a pawticuwaw boawd has
 * an extewnaw DP PWW, wetuwn ATOM_PPWW_INVAWID to skip PWW pwogwamming
 * as thewe is no need to pwogwam the PWW itsewf.  If we awe not abwe to
 * awwocate a PWW, wetuwn ATOM_PPWW_INVAWID to skip PWW pwogwamming to
 * avoid messing up an existing monitow.
 *
 * Asic specific PWW infowmation
 *
 * DCE 8.x
 * KB/KV
 * - PPWW1, PPWW2 awe avaiwabwe fow aww UNIPHY (both DP and non-DP)
 * CI
 * - PPWW0, PPWW1, PPWW2 awe avaiwabwe fow aww UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 6.1
 * - PPWW2 is onwy avaiwabwe to UNIPHYA (both DP and non-DP)
 * - PPWW0, PPWW1 awe avaiwabwe fow UNIPHYB/C/D/E/F (both DP and non-DP)
 *
 * DCE 6.0
 * - PPWW0 is avaiwabwe to aww UNIPHY (DP onwy)
 * - PPWW1, PPWW2 awe avaiwabwe fow aww UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 5.0
 * - DCPWW is avaiwabwe to aww UNIPHY (DP onwy)
 * - PPWW1, PPWW2 awe avaiwabwe fow aww UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 3.0/4.0/4.1
 * - PPWW1, PPWW2 awe avaiwabwe fow aww UNIPHY (both DP and non-DP) and DAC
 *
 */
static int wadeon_atom_pick_pww(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew =
		to_wadeon_encodew(wadeon_cwtc->encodew);
	u32 pww_in_use;
	int pww;

	if (ASIC_IS_DCE8(wdev)) {
		if (ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(wadeon_cwtc->encodew))) {
			if (wdev->cwock.dp_extcwk)
				/* skip PPWW pwogwamming if using ext cwock */
				wetuwn ATOM_PPWW_INVAWID;
			ewse {
				/* use the same PPWW fow aww DP monitows */
				pww = wadeon_get_shawed_dp_ppww(cwtc);
				if (pww != ATOM_PPWW_INVAWID)
					wetuwn pww;
			}
		} ewse {
			/* use the same PPWW fow aww monitows with the same cwock */
			pww = wadeon_get_shawed_nondp_ppww(cwtc);
			if (pww != ATOM_PPWW_INVAWID)
				wetuwn pww;
		}
		/* othewwise, pick one of the pwws */
		if ((wdev->famiwy == CHIP_KABINI) ||
		    (wdev->famiwy == CHIP_MUWWINS)) {
			/* KB/MW has PPWW1 and PPWW2 */
			pww_in_use = wadeon_get_pww_use_mask(cwtc);
			if (!(pww_in_use & (1 << ATOM_PPWW2)))
				wetuwn ATOM_PPWW2;
			if (!(pww_in_use & (1 << ATOM_PPWW1)))
				wetuwn ATOM_PPWW1;
			DWM_EWWOW("unabwe to awwocate a PPWW\n");
			wetuwn ATOM_PPWW_INVAWID;
		} ewse {
			/* CI/KV has PPWW0, PPWW1, and PPWW2 */
			pww_in_use = wadeon_get_pww_use_mask(cwtc);
			if (!(pww_in_use & (1 << ATOM_PPWW2)))
				wetuwn ATOM_PPWW2;
			if (!(pww_in_use & (1 << ATOM_PPWW1)))
				wetuwn ATOM_PPWW1;
			if (!(pww_in_use & (1 << ATOM_PPWW0)))
				wetuwn ATOM_PPWW0;
			DWM_EWWOW("unabwe to awwocate a PPWW\n");
			wetuwn ATOM_PPWW_INVAWID;
		}
	} ewse if (ASIC_IS_DCE61(wdev)) {
		stwuct wadeon_encodew_atom_dig *dig =
			wadeon_encodew->enc_pwiv;

		if ((wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY) &&
		    (dig->winkb == fawse))
			/* UNIPHY A uses PPWW2 */
			wetuwn ATOM_PPWW2;
		ewse if (ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(wadeon_cwtc->encodew))) {
			/* UNIPHY B/C/D/E/F */
			if (wdev->cwock.dp_extcwk)
				/* skip PPWW pwogwamming if using ext cwock */
				wetuwn ATOM_PPWW_INVAWID;
			ewse {
				/* use the same PPWW fow aww DP monitows */
				pww = wadeon_get_shawed_dp_ppww(cwtc);
				if (pww != ATOM_PPWW_INVAWID)
					wetuwn pww;
			}
		} ewse {
			/* use the same PPWW fow aww monitows with the same cwock */
			pww = wadeon_get_shawed_nondp_ppww(cwtc);
			if (pww != ATOM_PPWW_INVAWID)
				wetuwn pww;
		}
		/* UNIPHY B/C/D/E/F */
		pww_in_use = wadeon_get_pww_use_mask(cwtc);
		if (!(pww_in_use & (1 << ATOM_PPWW0)))
			wetuwn ATOM_PPWW0;
		if (!(pww_in_use & (1 << ATOM_PPWW1)))
			wetuwn ATOM_PPWW1;
		DWM_EWWOW("unabwe to awwocate a PPWW\n");
		wetuwn ATOM_PPWW_INVAWID;
	} ewse if (ASIC_IS_DCE41(wdev)) {
		/* Don't shawe PWWs on DCE4.1 chips */
		if (ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(wadeon_cwtc->encodew))) {
			if (wdev->cwock.dp_extcwk)
				/* skip PPWW pwogwamming if using ext cwock */
				wetuwn ATOM_PPWW_INVAWID;
		}
		pww_in_use = wadeon_get_pww_use_mask(cwtc);
		if (!(pww_in_use & (1 << ATOM_PPWW1)))
			wetuwn ATOM_PPWW1;
		if (!(pww_in_use & (1 << ATOM_PPWW2)))
			wetuwn ATOM_PPWW2;
		DWM_EWWOW("unabwe to awwocate a PPWW\n");
		wetuwn ATOM_PPWW_INVAWID;
	} ewse if (ASIC_IS_DCE4(wdev)) {
		/* in DP mode, the DP wef cwock can come fwom PPWW, DCPWW, ow ext cwock,
		 * depending on the asic:
		 * DCE4: PPWW ow ext cwock
		 * DCE5: PPWW, DCPWW, ow ext cwock
		 * DCE6: PPWW, PPWW0, ow ext cwock
		 *
		 * Setting ATOM_PPWW_INVAWID wiww cause SetPixewCwock to skip
		 * PPWW/DCPWW pwogwamming and onwy pwogwam the DP DTO fow the
		 * cwtc viwtuaw pixew cwock.
		 */
		if (ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(wadeon_cwtc->encodew))) {
			if (wdev->cwock.dp_extcwk)
				/* skip PPWW pwogwamming if using ext cwock */
				wetuwn ATOM_PPWW_INVAWID;
			ewse if (ASIC_IS_DCE6(wdev))
				/* use PPWW0 fow aww DP */
				wetuwn ATOM_PPWW0;
			ewse if (ASIC_IS_DCE5(wdev))
				/* use DCPWW fow aww DP */
				wetuwn ATOM_DCPWW;
			ewse {
				/* use the same PPWW fow aww DP monitows */
				pww = wadeon_get_shawed_dp_ppww(cwtc);
				if (pww != ATOM_PPWW_INVAWID)
					wetuwn pww;
			}
		} ewse {
			/* use the same PPWW fow aww monitows with the same cwock */
			pww = wadeon_get_shawed_nondp_ppww(cwtc);
			if (pww != ATOM_PPWW_INVAWID)
				wetuwn pww;
		}
		/* aww othew cases */
		pww_in_use = wadeon_get_pww_use_mask(cwtc);
		if (!(pww_in_use & (1 << ATOM_PPWW1)))
			wetuwn ATOM_PPWW1;
		if (!(pww_in_use & (1 << ATOM_PPWW2)))
			wetuwn ATOM_PPWW2;
		DWM_EWWOW("unabwe to awwocate a PPWW\n");
		wetuwn ATOM_PPWW_INVAWID;
	} ewse {
		/* on pwe-W5xx asics, the cwtc to pww mapping is hawdcoded */
		/* some atombios (obsewved in some DCE2/DCE3) code have a bug,
		 * the matching btw pww and cwtc is done thwough
		 * PCWK_CWTC[1|2]_CNTW (0x480/0x484) but atombios code use the
		 * pww (1 ow 2) to sewect which wegistew to wwite. ie if using
		 * pww1 it wiww use PCWK_CWTC1_CNTW (0x480) and if using pww2
		 * it wiww use PCWK_CWTC2_CNTW (0x484), it then use cwtc id to
		 * choose which vawue to wwite. Which is wevewse owdew fwom
		 * wegistew wogic. So onwy case that wowks is when pwwid is
		 * same as cwtcid ow when both pww and cwtc awe enabwed and
		 * both use same cwock.
		 *
		 * So just wetuwn cwtc id as if cwtc and pww wewe hawd winked
		 * togethew even if they awen't
		 */
		wetuwn wadeon_cwtc->cwtc_id;
	}
}

void wadeon_atom_disp_eng_pww_init(stwuct wadeon_device *wdev)
{
	/* awways set DCPWW */
	if (ASIC_IS_DCE6(wdev))
		atombios_cwtc_set_disp_eng_pww(wdev, wdev->cwock.defauwt_dispcwk);
	ewse if (ASIC_IS_DCE4(wdev)) {
		stwuct wadeon_atom_ss ss;
		boow ss_enabwed = wadeon_atombios_get_asic_ss_info(wdev, &ss,
								   ASIC_INTEWNAW_SS_ON_DCPWW,
								   wdev->cwock.defauwt_dispcwk);
		if (ss_enabwed)
			atombios_cwtc_pwogwam_ss(wdev, ATOM_DISABWE, ATOM_DCPWW, -1, &ss);
		/* XXX: DCE5, make suwe vowtage, dispcwk is high enough */
		atombios_cwtc_set_disp_eng_pww(wdev, wdev->cwock.defauwt_dispcwk);
		if (ss_enabwed)
			atombios_cwtc_pwogwam_ss(wdev, ATOM_ENABWE, ATOM_DCPWW, -1, &ss);
	}

}

int atombios_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
			   stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode,
			   int x, int y, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew =
		to_wadeon_encodew(wadeon_cwtc->encodew);
	boow is_tvcv = fawse;

	if (wadeon_encodew->active_device &
	    (ATOM_DEVICE_TV_SUPPOWT | ATOM_DEVICE_CV_SUPPOWT))
		is_tvcv = twue;

	if (!wadeon_cwtc->adjusted_cwock)
		wetuwn -EINVAW;

	atombios_cwtc_set_pww(cwtc, adjusted_mode);

	if (ASIC_IS_DCE4(wdev))
		atombios_set_cwtc_dtd_timing(cwtc, adjusted_mode);
	ewse if (ASIC_IS_AVIVO(wdev)) {
		if (is_tvcv)
			atombios_cwtc_set_timing(cwtc, adjusted_mode);
		ewse
			atombios_set_cwtc_dtd_timing(cwtc, adjusted_mode);
	} ewse {
		atombios_cwtc_set_timing(cwtc, adjusted_mode);
		if (wadeon_cwtc->cwtc_id == 0)
			atombios_set_cwtc_dtd_timing(cwtc, adjusted_mode);
		wadeon_wegacy_atom_fixup(cwtc);
	}
	atombios_cwtc_set_base(cwtc, x, y, owd_fb);
	atombios_ovewscan_setup(cwtc, mode, adjusted_mode);
	atombios_scawew_setup(cwtc);
	wadeon_cuwsow_weset(cwtc);
	/* update the hw vewsion fpw dpm */
	wadeon_cwtc->hw_mode = *adjusted_mode;

	wetuwn 0;
}

static boow atombios_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				     const stwuct dwm_dispway_mode *mode,
				     stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_encodew *encodew;

	/* assign the encodew to the wadeon cwtc to avoid wepeated wookups watew */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc == cwtc) {
			wadeon_cwtc->encodew = encodew;
			wadeon_cwtc->connectow = wadeon_get_connectow_fow_encodew(encodew);
			bweak;
		}
	}
	if ((wadeon_cwtc->encodew == NUWW) || (wadeon_cwtc->connectow == NUWW)) {
		wadeon_cwtc->encodew = NUWW;
		wadeon_cwtc->connectow = NUWW;
		wetuwn fawse;
	}
	if (wadeon_cwtc->encodew) {
		stwuct wadeon_encodew *wadeon_encodew =
			to_wadeon_encodew(wadeon_cwtc->encodew);

		wadeon_cwtc->output_csc = wadeon_encodew->output_csc;
	}
	if (!wadeon_cwtc_scawing_mode_fixup(cwtc, mode, adjusted_mode))
		wetuwn fawse;
	if (!atombios_cwtc_pwepawe_pww(cwtc, adjusted_mode))
		wetuwn fawse;
	/* pick pww */
	wadeon_cwtc->pww_id = wadeon_atom_pick_pww(cwtc);
	/* if we can't get a PPWW fow a non-DP encodew, faiw */
	if ((wadeon_cwtc->pww_id == ATOM_PPWW_INVAWID) &&
	    !ENCODEW_MODE_IS_DP(atombios_get_encodew_mode(wadeon_cwtc->encodew)))
		wetuwn fawse;

	wetuwn twue;
}

static void atombios_cwtc_pwepawe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	/* disabwe cwtc paiw powew gating befowe pwogwamming */
	if (ASIC_IS_DCE6(wdev))
		atombios_powewgate_cwtc(cwtc, ATOM_DISABWE);

	atombios_wock_cwtc(cwtc, ATOM_ENABWE);
	atombios_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);
}

static void atombios_cwtc_commit(stwuct dwm_cwtc *cwtc)
{
	atombios_cwtc_dpms(cwtc, DWM_MODE_DPMS_ON);
	atombios_wock_cwtc(cwtc, ATOM_DISABWE);
}

static void atombios_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_atom_ss ss;
	int i;

	atombios_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);
	if (cwtc->pwimawy->fb) {
		int w;
		stwuct wadeon_bo *wbo;

		wbo = gem_to_wadeon_bo(cwtc->pwimawy->fb->obj[0]);
		w = wadeon_bo_wesewve(wbo, fawse);
		if (unwikewy(w))
			DWM_EWWOW("faiwed to wesewve wbo befowe unpin\n");
		ewse {
			wadeon_bo_unpin(wbo);
			wadeon_bo_unwesewve(wbo);
		}
	}
	/* disabwe the GWPH */
	if (ASIC_IS_DCE4(wdev))
		WWEG32(EVEWGWEEN_GWPH_ENABWE + wadeon_cwtc->cwtc_offset, 0);
	ewse if (ASIC_IS_AVIVO(wdev))
		WWEG32(AVIVO_D1GWPH_ENABWE + wadeon_cwtc->cwtc_offset, 0);

	if (ASIC_IS_DCE6(wdev))
		atombios_powewgate_cwtc(cwtc, ATOM_ENABWE);

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (wdev->mode_info.cwtcs[i] &&
		    wdev->mode_info.cwtcs[i]->enabwed &&
		    i != wadeon_cwtc->cwtc_id &&
		    wadeon_cwtc->pww_id == wdev->mode_info.cwtcs[i]->pww_id) {
			/* one othew cwtc is using this pww don't tuwn
			 * off the pww
			 */
			goto done;
		}
	}

	switch (wadeon_cwtc->pww_id) {
	case ATOM_PPWW1:
	case ATOM_PPWW2:
		/* disabwe the ppww */
		atombios_cwtc_pwogwam_pww(cwtc, wadeon_cwtc->cwtc_id, wadeon_cwtc->pww_id,
					  0, 0, ATOM_DISABWE, 0, 0, 0, 0, 0, fawse, &ss);
		bweak;
	case ATOM_PPWW0:
		/* disabwe the ppww */
		if ((wdev->famiwy == CHIP_AWUBA) ||
		    (wdev->famiwy == CHIP_KAVEWI) ||
		    (wdev->famiwy == CHIP_BONAIWE) ||
		    (wdev->famiwy == CHIP_HAWAII))
			atombios_cwtc_pwogwam_pww(cwtc, wadeon_cwtc->cwtc_id, wadeon_cwtc->pww_id,
						  0, 0, ATOM_DISABWE, 0, 0, 0, 0, 0, fawse, &ss);
		bweak;
	defauwt:
		bweak;
	}
done:
	wadeon_cwtc->pww_id = ATOM_PPWW_INVAWID;
	wadeon_cwtc->adjusted_cwock = 0;
	wadeon_cwtc->encodew = NUWW;
	wadeon_cwtc->connectow = NUWW;
}

static const stwuct dwm_cwtc_hewpew_funcs atombios_hewpew_funcs = {
	.dpms = atombios_cwtc_dpms,
	.mode_fixup = atombios_cwtc_mode_fixup,
	.mode_set = atombios_cwtc_mode_set,
	.mode_set_base = atombios_cwtc_set_base,
	.mode_set_base_atomic = atombios_cwtc_set_base_atomic,
	.pwepawe = atombios_cwtc_pwepawe,
	.commit = atombios_cwtc_commit,
	.disabwe = atombios_cwtc_disabwe,
	.get_scanout_position = wadeon_get_cwtc_scanout_position,
};

void wadeon_atombios_init_cwtc(stwuct dwm_device *dev,
			       stwuct wadeon_cwtc *wadeon_cwtc)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (ASIC_IS_DCE4(wdev)) {
		switch (wadeon_cwtc->cwtc_id) {
		case 0:
		defauwt:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC0_WEGISTEW_OFFSET;
			bweak;
		case 1:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC1_WEGISTEW_OFFSET;
			bweak;
		case 2:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC2_WEGISTEW_OFFSET;
			bweak;
		case 3:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC3_WEGISTEW_OFFSET;
			bweak;
		case 4:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC4_WEGISTEW_OFFSET;
			bweak;
		case 5:
			wadeon_cwtc->cwtc_offset = EVEWGWEEN_CWTC5_WEGISTEW_OFFSET;
			bweak;
		}
	} ewse {
		if (wadeon_cwtc->cwtc_id == 1)
			wadeon_cwtc->cwtc_offset =
				AVIVO_D2CWTC_H_TOTAW - AVIVO_D1CWTC_H_TOTAW;
		ewse
			wadeon_cwtc->cwtc_offset = 0;
	}
	wadeon_cwtc->pww_id = ATOM_PPWW_INVAWID;
	wadeon_cwtc->adjusted_cwock = 0;
	wadeon_cwtc->encodew = NUWW;
	wadeon_cwtc->connectow = NUWW;
	dwm_cwtc_hewpew_add(&wadeon_cwtc->base, &atombios_hewpew_funcs);
}
