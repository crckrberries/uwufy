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

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_fixed.h>
#incwude "amdgpu.h"
#incwude "atom.h"
#incwude "atom-bits.h"
#incwude "atombios_encodews.h"
#incwude "atombios_cwtc.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_pww.h"
#incwude "amdgpu_connectows.h"

void amdgpu_atombios_cwtc_ovewscan_setup(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	SET_CWTC_OVEWSCAN_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetCWTC_OvewScan);
	int a1, a2;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = amdgpu_cwtc->cwtc_id;

	switch (amdgpu_cwtc->wmx_type) {
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
		awgs.usOvewscanWight = cpu_to_we16(amdgpu_cwtc->h_bowdew);
		awgs.usOvewscanWeft = cpu_to_we16(amdgpu_cwtc->h_bowdew);
		awgs.usOvewscanBottom = cpu_to_we16(amdgpu_cwtc->v_bowdew);
		awgs.usOvewscanTop = cpu_to_we16(amdgpu_cwtc->v_bowdew);
		bweak;
	}
	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_scawew_setup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	ENABWE_SCAWEW_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweScawew);

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucScawew = amdgpu_cwtc->cwtc_id;

	switch (amdgpu_cwtc->wmx_type) {
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
		awgs.ucEnabwe = ATOM_SCAWEW_DISABWE;
		bweak;
	}
	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_wock(stwuct dwm_cwtc *cwtc, int wock)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int index =
	    GetIndexIntoMastewTabwe(COMMAND, UpdateCWTC_DoubweBuffewWegistews);
	ENABWE_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = amdgpu_cwtc->cwtc_id;
	awgs.ucEnabwe = wock;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_enabwe(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweCWTC);
	ENABWE_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = amdgpu_cwtc->cwtc_id;
	awgs.ucEnabwe = state;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_bwank(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int index = GetIndexIntoMastewTabwe(COMMAND, BwankCWTC);
	BWANK_CWTC_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucCWTC = amdgpu_cwtc->cwtc_id;
	awgs.ucBwanking = state;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_powewgate(stwuct dwm_cwtc *cwtc, int state)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweDispPowewGating);
	ENABWE_DISP_POWEW_GATING_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucDispPipeId = amdgpu_cwtc->cwtc_id;
	awgs.ucEnabwe = state;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_powewgate_init(stwuct amdgpu_device *adev)
{
	int index = GetIndexIntoMastewTabwe(COMMAND, EnabweDispPowewGating);
	ENABWE_DISP_POWEW_GATING_PS_AWWOCATION awgs;

	memset(&awgs, 0, sizeof(awgs));

	awgs.ucEnabwe = ATOM_INIT;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_cwtc_set_dtd_timing(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	SET_CWTC_USING_DTD_TIMING_PAWAMETEWS awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetCWTC_UsingDTDTiming);
	u16 misc = 0;

	memset(&awgs, 0, sizeof(awgs));
	awgs.usH_Size = cpu_to_we16(mode->cwtc_hdispway - (amdgpu_cwtc->h_bowdew * 2));
	awgs.usH_Bwanking_Time =
		cpu_to_we16(mode->cwtc_hbwank_end - mode->cwtc_hdispway + (amdgpu_cwtc->h_bowdew * 2));
	awgs.usV_Size = cpu_to_we16(mode->cwtc_vdispway - (amdgpu_cwtc->v_bowdew * 2));
	awgs.usV_Bwanking_Time =
		cpu_to_we16(mode->cwtc_vbwank_end - mode->cwtc_vdispway + (amdgpu_cwtc->v_bowdew * 2));
	awgs.usH_SyncOffset =
		cpu_to_we16(mode->cwtc_hsync_stawt - mode->cwtc_hdispway + amdgpu_cwtc->h_bowdew);
	awgs.usH_SyncWidth =
		cpu_to_we16(mode->cwtc_hsync_end - mode->cwtc_hsync_stawt);
	awgs.usV_SyncOffset =
		cpu_to_we16(mode->cwtc_vsync_stawt - mode->cwtc_vdispway + amdgpu_cwtc->v_bowdew);
	awgs.usV_SyncWidth =
		cpu_to_we16(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt);
	awgs.ucH_Bowdew = amdgpu_cwtc->h_bowdew;
	awgs.ucV_Bowdew = amdgpu_cwtc->v_bowdew;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		misc |= ATOM_VSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		misc |= ATOM_HSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		misc |= ATOM_INTEWWACE;
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		misc |= ATOM_DOUBWE_CWOCK_MODE;

	awgs.susModeMiscInfo.usAccess = cpu_to_we16(misc);
	awgs.ucCWTC = amdgpu_cwtc->cwtc_id;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

union atom_enabwe_ss {
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_PS_AWWOCATION v1;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V2 v2;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V3 v3;
};

static void amdgpu_atombios_cwtc_pwogwam_ss(stwuct amdgpu_device *adev,
				     int enabwe,
				     int pww_id,
				     int cwtc_id,
				     stwuct amdgpu_atom_ss *ss)
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
		fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
			if (adev->mode_info.cwtcs[i] &&
			    adev->mode_info.cwtcs[i]->enabwed &&
			    i != cwtc_id &&
			    pww_id == adev->mode_info.cwtcs[i]->pww_id) {
				/* one othew cwtc is using this pww don't tuwn
				 * off spwead spectwum as it might tuwn off
				 * dispway on active cwtc
				 */
				wetuwn;
			}
		}
	}

	memset(&awgs, 0, sizeof(awgs));

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

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

union adjust_pixew_cwock {
	ADJUST_DISPWAY_PWW_PS_AWWOCATION v1;
	ADJUST_DISPWAY_PWW_PS_AWWOCATION_V3 v3;
};

static u32 amdgpu_atombios_cwtc_adjust_pww(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct dwm_encodew *encodew = amdgpu_cwtc->encodew;
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct dwm_connectow *connectow = amdgpu_get_connectow_fow_encodew(encodew);
	u32 adjusted_cwock = mode->cwock;
	int encodew_mode = amdgpu_atombios_encodew_get_encodew_mode(encodew);
	u32 dp_cwock = mode->cwock;
	u32 cwock = mode->cwock;
	int bpc = amdgpu_cwtc->bpc;
	boow is_duawwink = amdgpu_dig_monitow_is_duawwink(encodew, mode->cwock);
	union adjust_pixew_cwock awgs;
	u8 fwev, cwev;
	int index;

	amdgpu_cwtc->pww_fwags = AMDGPU_PWW_USE_FWAC_FB_DIV;

	if ((amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT | ATOM_DEVICE_DFP_SUPPOWT)) ||
	    (amdgpu_encodew_get_dp_bwidge_encodew_id(encodew) != ENCODEW_OBJECT_ID_NONE)) {
		if (connectow) {
			stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
			stwuct amdgpu_connectow_atom_dig *dig_connectow =
				amdgpu_connectow->con_pwiv;

			dp_cwock = dig_connectow->dp_cwock;
		}
	}

	/* use wecommended wef_div fow ss */
	if (amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT)) {
		if (amdgpu_cwtc->ss_enabwed) {
			if (amdgpu_cwtc->ss.wefdiv) {
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_WEF_DIV;
				amdgpu_cwtc->pww_wefewence_div = amdgpu_cwtc->ss.wefdiv;
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_FWAC_FB_DIV;
			}
		}
	}

	/* DVO wants 2x pixew cwock if the DVO chip is in 12 bit mode */
	if (amdgpu_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1)
		adjusted_cwock = mode->cwock * 2;
	if (amdgpu_encodew->active_device & (ATOM_DEVICE_TV_SUPPOWT))
		amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_PWEFEW_CWOSEST_WOWEW;
	if (amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT))
		amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_IS_WCD;


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
	index = GetIndexIntoMastewTabwe(COMMAND, AdjustDispwayPww);
	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev,
				   &cwev))
		wetuwn adjusted_cwock;

	memset(&awgs, 0, sizeof(awgs));

	switch (fwev) {
	case 1:
		switch (cwev) {
		case 1:
		case 2:
			awgs.v1.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v1.ucTwansmittewID = amdgpu_encodew->encodew_id;
			awgs.v1.ucEncodeMode = encodew_mode;
			if (amdgpu_cwtc->ss_enabwed && amdgpu_cwtc->ss.pewcentage)
				awgs.v1.ucConfig |=
					ADJUST_DISPWAY_CONFIG_SS_ENABWE;

			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context,
					   index, (uint32_t *)&awgs);
			adjusted_cwock = we16_to_cpu(awgs.v1.usPixewCwock) * 10;
			bweak;
		case 3:
			awgs.v3.sInput.usPixewCwock = cpu_to_we16(cwock / 10);
			awgs.v3.sInput.ucTwansmittewID = amdgpu_encodew->encodew_id;
			awgs.v3.sInput.ucEncodeMode = encodew_mode;
			awgs.v3.sInput.ucDispPwwConfig = 0;
			if (amdgpu_cwtc->ss_enabwed && amdgpu_cwtc->ss.pewcentage)
				awgs.v3.sInput.ucDispPwwConfig |=
					DISPPWW_CONFIG_SS_ENABWE;
			if (ENCODEW_MODE_IS_DP(encodew_mode)) {
				awgs.v3.sInput.ucDispPwwConfig |=
					DISPPWW_CONFIG_COHEWENT_MODE;
				/* 16200 ow 27000 */
				awgs.v3.sInput.usPixewCwock = cpu_to_we16(dp_cwock / 10);
			} ewse if (amdgpu_encodew->devices & (ATOM_DEVICE_DFP_SUPPOWT)) {
				stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
				if (dig->cohewent_mode)
					awgs.v3.sInput.ucDispPwwConfig |=
						DISPPWW_CONFIG_COHEWENT_MODE;
				if (is_duawwink)
					awgs.v3.sInput.ucDispPwwConfig |=
						DISPPWW_CONFIG_DUAW_WINK;
			}
			if (amdgpu_encodew_get_dp_bwidge_encodew_id(encodew) !=
			    ENCODEW_OBJECT_ID_NONE)
				awgs.v3.sInput.ucExtTwansmittewID =
					amdgpu_encodew_get_dp_bwidge_encodew_id(encodew);
			ewse
				awgs.v3.sInput.ucExtTwansmittewID = 0;

			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context,
					   index, (uint32_t *)&awgs);
			adjusted_cwock = we32_to_cpu(awgs.v3.sOutput.uwDispPwwFweq) * 10;
			if (awgs.v3.sOutput.ucWefDiv) {
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_FWAC_FB_DIV;
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_WEF_DIV;
				amdgpu_cwtc->pww_wefewence_div = awgs.v3.sOutput.ucWefDiv;
			}
			if (awgs.v3.sOutput.ucPostDiv) {
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_FWAC_FB_DIV;
				amdgpu_cwtc->pww_fwags |= AMDGPU_PWW_USE_POST_DIV;
				amdgpu_cwtc->pww_post_div = awgs.v3.sOutput.ucPostDiv;
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

	wetuwn adjusted_cwock;
}

union set_pixew_cwock {
	SET_PIXEW_CWOCK_PS_AWWOCATION base;
	PIXEW_CWOCK_PAWAMETEWS v1;
	PIXEW_CWOCK_PAWAMETEWS_V2 v2;
	PIXEW_CWOCK_PAWAMETEWS_V3 v3;
	PIXEW_CWOCK_PAWAMETEWS_V5 v5;
	PIXEW_CWOCK_PAWAMETEWS_V6 v6;
	PIXEW_CWOCK_PAWAMETEWS_V7 v7;
};

/* on DCE5, make suwe the vowtage is high enough to suppowt the
 * wequiwed disp cwk.
 */
void amdgpu_atombios_cwtc_set_disp_eng_pww(stwuct amdgpu_device *adev,
					   u32 dispcwk)
{
	u8 fwev, cwev;
	int index;
	union set_pixew_cwock awgs;

	memset(&awgs, 0, sizeof(awgs));

	index = GetIndexIntoMastewTabwe(COMMAND, SetPixewCwock);
	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev,
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
			if (adev->asic_type == CHIP_TAHITI ||
			    adev->asic_type == CHIP_PITCAIWN ||
			    adev->asic_type == CHIP_VEWDE ||
			    adev->asic_type == CHIP_OWAND)
				awgs.v6.ucPpww = ATOM_PPWW0;
			ewse
				awgs.v6.ucPpww = ATOM_EXT_PWW1;
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
	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

union set_dce_cwock {
	SET_DCE_CWOCK_PS_AWWOCATION_V1_1 v1_1;
	SET_DCE_CWOCK_PS_AWWOCATION_V2_1 v2_1;
};

u32 amdgpu_atombios_cwtc_set_dce_cwock(stwuct amdgpu_device *adev,
				       u32 fweq, u8 cwk_type, u8 cwk_swc)
{
	u8 fwev, cwev;
	int index;
	union set_dce_cwock awgs;
	u32 wet_fweq = 0;

	memset(&awgs, 0, sizeof(awgs));

	index = GetIndexIntoMastewTabwe(COMMAND, SetDCECwock);
	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev,
				   &cwev))
		wetuwn 0;

	switch (fwev) {
	case 2:
		switch (cwev) {
		case 1:
			awgs.v2_1.asPawam.uwDCECwkFweq = cpu_to_we32(fweq); /* 10kHz units */
			awgs.v2_1.asPawam.ucDCECwkType = cwk_type;
			awgs.v2_1.asPawam.ucDCECwkSwc = cwk_swc;
			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
			wet_fweq = we32_to_cpu(awgs.v2_1.asPawam.uwDCECwkFweq) * 10;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
			wetuwn 0;
		}
		bweak;
	defauwt:
		DWM_EWWOW("Unknown tabwe vewsion %d %d\n", fwev, cwev);
		wetuwn 0;
	}

	wetuwn wet_fweq;
}

static boow is_pixew_cwock_souwce_fwom_pww(u32 encodew_mode, int pww_id)
{
	if (ENCODEW_MODE_IS_DP(encodew_mode)) {
		if (pww_id < ATOM_EXT_PWW1)
			wetuwn twue;
		ewse
			wetuwn fawse;
	} ewse {
		wetuwn twue;
	}
}

void amdgpu_atombios_cwtc_pwogwam_pww(stwuct dwm_cwtc *cwtc,
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
				      stwuct amdgpu_atom_ss *ss)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	u8 fwev, cwev;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetPixewCwock);
	union set_pixew_cwock awgs;

	memset(&awgs, 0, sizeof(awgs));

	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev,
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
			if ((ss_enabwed && (ss->type & ATOM_EXTEWNAW_SS_MASK)) &&
			    (pww_id < ATOM_EXT_PWW1))
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
			if ((ss_enabwed && (ss->type & ATOM_EXTEWNAW_SS_MASK)) &&
			    (pww_id < ATOM_EXT_PWW1) &&
			    !is_pixew_cwock_souwce_fwom_pww(encodew_mode, pww_id))
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
		case 7:
			awgs.v7.uwPixewCwock = cpu_to_we32(cwock * 10); /* 100 hz units */
			awgs.v7.ucMiscInfo = 0;
			if ((encodew_mode == ATOM_ENCODEW_MODE_DVI) &&
			    (cwock > 165000))
				awgs.v7.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_DVI_DUAWWINK_EN;
			awgs.v7.ucCWTC = cwtc_id;
			if (encodew_mode == ATOM_ENCODEW_MODE_HDMI) {
				switch (bpc) {
				case 8:
				defauwt:
					awgs.v7.ucDeepCowowWatio = PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_DIS;
					bweak;
				case 10:
					awgs.v7.ucDeepCowowWatio = PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_5_4;
					bweak;
				case 12:
					awgs.v7.ucDeepCowowWatio = PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_3_2;
					bweak;
				case 16:
					awgs.v7.ucDeepCowowWatio = PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_2_1;
					bweak;
				}
			}
			awgs.v7.ucTwansmittewID = encodew_id;
			awgs.v7.ucEncodewMode = encodew_mode;
			awgs.v7.ucPpww = pww_id;
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

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

int amdgpu_atombios_cwtc_pwepawe_pww(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew =
		to_amdgpu_encodew(amdgpu_cwtc->encodew);
	int encodew_mode = amdgpu_atombios_encodew_get_encodew_mode(amdgpu_cwtc->encodew);

	amdgpu_cwtc->bpc = 8;
	amdgpu_cwtc->ss_enabwed = fawse;

	if ((amdgpu_encodew->active_device & (ATOM_DEVICE_WCD_SUPPOWT | ATOM_DEVICE_DFP_SUPPOWT)) ||
	    (amdgpu_encodew_get_dp_bwidge_encodew_id(amdgpu_cwtc->encodew) != ENCODEW_OBJECT_ID_NONE)) {
		stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
		stwuct dwm_connectow *connectow =
			amdgpu_get_connectow_fow_encodew(amdgpu_cwtc->encodew);
		stwuct amdgpu_connectow *amdgpu_connectow =
			to_amdgpu_connectow(connectow);
		stwuct amdgpu_connectow_atom_dig *dig_connectow =
			amdgpu_connectow->con_pwiv;
		int dp_cwock;

		/* Assign mode cwock fow hdmi deep cowow max cwock wimit check */
		amdgpu_connectow->pixewcwock_fow_modeset = mode->cwock;
		amdgpu_cwtc->bpc = amdgpu_connectow_get_monitow_bpc(connectow);

		switch (encodew_mode) {
		case ATOM_ENCODEW_MODE_DP_MST:
		case ATOM_ENCODEW_MODE_DP:
			/* DP/eDP */
			dp_cwock = dig_connectow->dp_cwock / 10;
			amdgpu_cwtc->ss_enabwed =
				amdgpu_atombios_get_asic_ss_info(adev, &amdgpu_cwtc->ss,
								 ASIC_INTEWNAW_SS_ON_DP,
								 dp_cwock);
			bweak;
		case ATOM_ENCODEW_MODE_WVDS:
			amdgpu_cwtc->ss_enabwed =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_cwtc->ss,
								 dig->wcd_ss_id,
								 mode->cwock / 10);
			bweak;
		case ATOM_ENCODEW_MODE_DVI:
			amdgpu_cwtc->ss_enabwed =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_cwtc->ss,
								 ASIC_INTEWNAW_SS_ON_TMDS,
								 mode->cwock / 10);
			bweak;
		case ATOM_ENCODEW_MODE_HDMI:
			amdgpu_cwtc->ss_enabwed =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_cwtc->ss,
								 ASIC_INTEWNAW_SS_ON_HDMI,
								 mode->cwock / 10);
			bweak;
		defauwt:
			bweak;
		}
	}

	/* adjust pixew cwock as needed */
	amdgpu_cwtc->adjusted_cwock = amdgpu_atombios_cwtc_adjust_pww(cwtc, mode);

	wetuwn 0;
}

void amdgpu_atombios_cwtc_set_pww(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew =
		to_amdgpu_encodew(amdgpu_cwtc->encodew);
	u32 pww_cwock = mode->cwock;
	u32 cwock = mode->cwock;
	u32 wef_div = 0, fb_div = 0, fwac_fb_div = 0, post_div = 0;
	stwuct amdgpu_pww *pww;
	int encodew_mode = amdgpu_atombios_encodew_get_encodew_mode(amdgpu_cwtc->encodew);

	/* pass the actuaw cwock to amdgpu_atombios_cwtc_pwogwam_pww fow HDMI */
	if ((encodew_mode == ATOM_ENCODEW_MODE_HDMI) &&
	    (amdgpu_cwtc->bpc > 8))
		cwock = amdgpu_cwtc->adjusted_cwock;

	switch (amdgpu_cwtc->pww_id) {
	case ATOM_PPWW1:
		pww = &adev->cwock.ppww[0];
		bweak;
	case ATOM_PPWW2:
		pww = &adev->cwock.ppww[1];
		bweak;
	case ATOM_PPWW0:
	case ATOM_PPWW_INVAWID:
	defauwt:
		pww = &adev->cwock.ppww[2];
		bweak;
	}

	/* update pww pawams */
	pww->fwags = amdgpu_cwtc->pww_fwags;
	pww->wefewence_div = amdgpu_cwtc->pww_wefewence_div;
	pww->post_div = amdgpu_cwtc->pww_post_div;

	amdgpu_pww_compute(adev, pww, amdgpu_cwtc->adjusted_cwock, &pww_cwock,
			    &fb_div, &fwac_fb_div, &wef_div, &post_div);

	amdgpu_atombios_cwtc_pwogwam_ss(adev, ATOM_DISABWE, amdgpu_cwtc->pww_id,
				 amdgpu_cwtc->cwtc_id, &amdgpu_cwtc->ss);

	amdgpu_atombios_cwtc_pwogwam_pww(cwtc, amdgpu_cwtc->cwtc_id, amdgpu_cwtc->pww_id,
				  encodew_mode, amdgpu_encodew->encodew_id, cwock,
				  wef_div, fb_div, fwac_fb_div, post_div,
				  amdgpu_cwtc->bpc, amdgpu_cwtc->ss_enabwed, &amdgpu_cwtc->ss);

	if (amdgpu_cwtc->ss_enabwed) {
		/* cawcuwate ss amount and step size */
		u32 step_size;
		u32 amount = (((fb_div * 10) + fwac_fb_div) *
			      (u32)amdgpu_cwtc->ss.pewcentage) /
			(100 * (u32)amdgpu_cwtc->ss.pewcentage_dividew);
		amdgpu_cwtc->ss.amount = (amount / 10) & ATOM_PPWW_SS_AMOUNT_V2_FBDIV_MASK;
		amdgpu_cwtc->ss.amount |= ((amount - (amount / 10)) << ATOM_PPWW_SS_AMOUNT_V2_NFWAC_SHIFT) &
			ATOM_PPWW_SS_AMOUNT_V2_NFWAC_MASK;
		if (amdgpu_cwtc->ss.type & ATOM_PPWW_SS_TYPE_V2_CENTWE_SPWEAD)
			step_size = (4 * amount * wef_div * ((u32)amdgpu_cwtc->ss.wate * 2048)) /
				(125 * 25 * pww->wefewence_fweq / 100);
		ewse
			step_size = (2 * amount * wef_div * ((u32)amdgpu_cwtc->ss.wate * 2048)) /
				(125 * 25 * pww->wefewence_fweq / 100);
		amdgpu_cwtc->ss.step = step_size;

		amdgpu_atombios_cwtc_pwogwam_ss(adev, ATOM_ENABWE, amdgpu_cwtc->pww_id,
					 amdgpu_cwtc->cwtc_id, &amdgpu_cwtc->ss);
	}
}

