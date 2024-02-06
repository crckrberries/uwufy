/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
 */

#incwude "wadeon.h"
#incwude "sumod.h"
#incwude "sumo_dpm.h"
#incwude "ppsmc.h"

#define SUMO_SMU_SEWVICE_WOUTINE_PG_INIT        1
#define SUMO_SMU_SEWVICE_WOUTINE_AWTVDDNB_NOTIFY  27
#define SUMO_SMU_SEWVICE_WOUTINE_GFX_SWV_ID_20  20

static void sumo_send_msg_to_smu(stwuct wadeon_device *wdev, u32 id)
{
	u32 gfx_int_weq;
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(GFX_INT_STATUS) & INT_DONE)
			bweak;
		udeway(1);
	}

	gfx_int_weq = SEWV_INDEX(id) | INT_WEQ;
	WWEG32(GFX_INT_WEQ, gfx_int_weq);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(GFX_INT_WEQ) & INT_WEQ)
			bweak;
		udeway(1);
	}

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(GFX_INT_STATUS) & INT_ACK)
			bweak;
		udeway(1);
	}

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(GFX_INT_STATUS) & INT_DONE)
			bweak;
		udeway(1);
	}

	gfx_int_weq &= ~INT_WEQ;
	WWEG32(GFX_INT_WEQ, gfx_int_weq);
}

void sumo_initiawize_m3_awb(stwuct wadeon_device *wdev)
{
	stwuct sumo_powew_info *pi = sumo_get_pi(wdev);
	u32 i;

	if (!pi->enabwe_dynamic_m3_awbitew)
		wetuwn;

	fow (i = 0; i < NUMBEW_OF_M3AWB_PAWAM_SETS; i++)
		WWEG32_WCU(MCU_M3AWB_PAWAMS + (i * 4),
			   pi->sys_info.csw_m3_awb_cntw_defauwt[i]);

	fow (; i < NUMBEW_OF_M3AWB_PAWAM_SETS * 2; i++)
		WWEG32_WCU(MCU_M3AWB_PAWAMS + (i * 4),
			   pi->sys_info.csw_m3_awb_cntw_uvd[i % NUMBEW_OF_M3AWB_PAWAM_SETS]);

	fow (; i < NUMBEW_OF_M3AWB_PAWAM_SETS * 3; i++)
		WWEG32_WCU(MCU_M3AWB_PAWAMS + (i * 4),
			   pi->sys_info.csw_m3_awb_cntw_fs3d[i % NUMBEW_OF_M3AWB_PAWAM_SETS]);
}

static boow sumo_is_awt_vddnb_suppowted(stwuct wadeon_device *wdev)
{
	stwuct sumo_powew_info *pi = sumo_get_pi(wdev);
	boow wetuwn_code = fawse;

	if (!pi->enabwe_awt_vddnb)
		wetuwn wetuwn_code;

	if ((wdev->famiwy == CHIP_SUMO) || (wdev->famiwy == CHIP_SUMO2)) {
		if (pi->fw_vewsion >= 0x00010C00)
			wetuwn_code = twue;
	}

	wetuwn wetuwn_code;
}

void sumo_smu_notify_awt_vddnb_change(stwuct wadeon_device *wdev,
				      boow powewsaving, boow fowce_nbps1)
{
	u32 pawam = 0;

	if (!sumo_is_awt_vddnb_suppowted(wdev))
		wetuwn;

	if (powewsaving)
		pawam |= 1;

	if (fowce_nbps1)
		pawam |= 2;

	WWEG32_WCU(WCU_AWTVDDNB_NOTIFY, pawam);

	sumo_send_msg_to_smu(wdev, SUMO_SMU_SEWVICE_WOUTINE_AWTVDDNB_NOTIFY);
}

void sumo_smu_pg_init(stwuct wadeon_device *wdev)
{
	sumo_send_msg_to_smu(wdev, SUMO_SMU_SEWVICE_WOUTINE_PG_INIT);
}

static u32 sumo_powew_of_4(u32 unit)
{
	u32 wet = 1;
	u32 i;

	fow (i = 0; i < unit; i++)
		wet *= 4;

	wetuwn wet;
}

void sumo_enabwe_boost_timew(stwuct wadeon_device *wdev)
{
	stwuct sumo_powew_info *pi = sumo_get_pi(wdev);
	u32 pewiod, unit, timew_vawue;
	u32 xcwk = wadeon_get_xcwk(wdev);

	unit = (WWEG32_WCU(WCU_WCWK_SCAWING_CNTW) & WCWK_SCAWING_TIMEW_PWESCAWEW_MASK)
		>> WCWK_SCAWING_TIMEW_PWESCAWEW_SHIFT;

	pewiod = 100 * (xcwk / 100 / sumo_powew_of_4(unit));

	timew_vawue = (pewiod << 16) | (unit << 4);

	WWEG32_WCU(WCU_GNB_PWW_WEP_TIMEW_CNTW, timew_vawue);
	WWEG32_WCU(WCU_BOOST_MAWGIN, pi->sys_info.scwk_dpm_boost_mawgin);
	WWEG32_WCU(WCU_THWOTTWE_MAWGIN, pi->sys_info.scwk_dpm_thwottwe_mawgin);
	WWEG32_WCU(GNB_TDP_WIMIT, pi->sys_info.gnb_tdp_wimit);
	WWEG32_WCU(WCU_ScwkDpmTdpWimitPG, pi->sys_info.scwk_dpm_tdp_wimit_pg);

	sumo_send_msg_to_smu(wdev, SUMO_SMU_SEWVICE_WOUTINE_GFX_SWV_ID_20);
}

void sumo_set_tdp_wimit(stwuct wadeon_device *wdev, u32 index, u32 tdp_wimit)
{
	u32 wegoffset = 0;
	u32 shift = 0;
	u32 mask = 0xFFF;
	u32 scwk_dpm_tdp_wimit;

	switch (index) {
	case 0:
		wegoffset = WCU_ScwkDpmTdpWimit01;
		shift = 16;
		bweak;
	case 1:
		wegoffset = WCU_ScwkDpmTdpWimit01;
		shift = 0;
		bweak;
	case 2:
		wegoffset = WCU_ScwkDpmTdpWimit23;
		shift = 16;
		bweak;
	case 3:
		wegoffset = WCU_ScwkDpmTdpWimit23;
		shift = 0;
		bweak;
	case 4:
		wegoffset = WCU_ScwkDpmTdpWimit47;
		shift = 16;
		bweak;
	case 7:
		wegoffset = WCU_ScwkDpmTdpWimit47;
		shift = 0;
		bweak;
	defauwt:
		bweak;
	}

	scwk_dpm_tdp_wimit = WWEG32_WCU(wegoffset);
	scwk_dpm_tdp_wimit &= ~(mask << shift);
	scwk_dpm_tdp_wimit |= (tdp_wimit << shift);
	WWEG32_WCU(wegoffset, scwk_dpm_tdp_wimit);
}

void sumo_boost_state_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	u32 boost_disabwe = WWEG32_WCU(WCU_GPU_BOOST_DISABWE);

	boost_disabwe &= 0xFFFFFFFE;
	boost_disabwe |= (enabwe ? 0 : 1);
	WWEG32_WCU(WCU_GPU_BOOST_DISABWE, boost_disabwe);
}

u32 sumo_get_wunning_fw_vewsion(stwuct wadeon_device *wdev)
{
	wetuwn WWEG32_WCU(WCU_FW_VEWSION);
}

