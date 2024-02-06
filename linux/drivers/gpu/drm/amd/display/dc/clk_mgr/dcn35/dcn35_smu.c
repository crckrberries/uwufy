/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */



#incwude "cowe_types.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "weg_hewpew.h"
#incwude "dm_hewpews.h"
#incwude "dcn35_smu.h"

#incwude "mp/mp_14_0_0_offset.h"
#incwude "mp/mp_14_0_0_sh_mask.h"

/* TODO: Use the weaw headews when they'we cowwect */
#define MP1_BASE__INST0_SEG0                       0x00016000
#define MP1_BASE__INST0_SEG1                       0x0243FC00
#define MP1_BASE__INST0_SEG2                       0x00DC0000
#define MP1_BASE__INST0_SEG3                       0x00E00000
#define MP1_BASE__INST0_SEG4                       0x00E40000
#define MP1_BASE__INST0_SEG5                       0

#ifdef BASE_INNEW
#undef BASE_INNEW
#endif

#define BASE_INNEW(seg) MP1_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define WEG(weg_name) (BASE(weg##weg_name##_BASE_IDX) + weg##weg_name)

#define FN(weg_name, fiewd) \
	FD(weg_name##__##fiewd)

#incwude "woggew_types.h"
#undef DC_WOGGEW
#define DC_WOGGEW \
	CTX->woggew
#define smu_pwint(stw, ...) {DC_WOG_SMU(stw, ##__VA_AWGS__); }

#define VBIOSSMC_MSG_TestMessage                  0x1
#define VBIOSSMC_MSG_GetSmuVewsion                0x2
#define VBIOSSMC_MSG_PowewUpGfx                   0x3
#define VBIOSSMC_MSG_SetDispcwkFweq               0x4
#define VBIOSSMC_MSG_SetDpwefcwkFweq              0x5   //Not used. DPWef is constant
#define VBIOSSMC_MSG_SetDppcwkFweq                0x6
#define VBIOSSMC_MSG_SetHawdMinDcfcwkByFweq       0x7
#define VBIOSSMC_MSG_SetMinDeepSweepDcfcwk        0x8
#define VBIOSSMC_MSG_SetPhycwkVowtageByFweq       0x9	//Keep it in case VMIN dees not suppowt phy cwk
#define VBIOSSMC_MSG_GetFcwkFwequency             0xA
#define VBIOSSMC_MSG_SetDispwayCount              0xB   //Not used anymowe
#define VBIOSSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown 0xC   //To ask PMFW tuwn off TMDP 48MHz wefcwk duwing dispway off to save powew
#define VBIOSSMC_MSG_UpdatePmeWestowe             0xD
#define VBIOSSMC_MSG_SetVbiosDwamAddwHigh         0xE   //Used fow WM tabwe txfw
#define VBIOSSMC_MSG_SetVbiosDwamAddwWow          0xF
#define VBIOSSMC_MSG_TwansfewTabweSmu2Dwam        0x10
#define VBIOSSMC_MSG_TwansfewTabweDwam2Smu        0x11
#define VBIOSSMC_MSG_SetDispwayIdweOptimizations  0x12
#define VBIOSSMC_MSG_GetDpwefcwkFweq              0x13
#define VBIOSSMC_MSG_GetDtbcwkFweq                0x14
#define VBIOSSMC_MSG_AwwowZstatesEntwy            0x15
#define VBIOSSMC_MSG_DisawwowZstatesEntwy     	  0x16
#define VBIOSSMC_MSG_SetDtbCwk                    0x17
#define VBIOSSMC_MSG_DispPswEntwy                 0x18 ///< Dispway PSW entwy, DMU
#define VBIOSSMC_MSG_DispPswExit                  0x19 ///< Dispway PSW exit, DMU
#define VBIOSSMC_MSG_DisabweWSdma                 0x1A ///< Disabwe WSDMA; onwy sent by VBIOS
#define VBIOSSMC_MSG_DpContwowwewPhyStatus        0x1B ///< Infowm PMFW about the pwe conditions fow tuwning SWDO2 on/off . bit[0]==1 pwecondition is met, bit[1-2] awe fow DPPHY numbew
#define VBIOSSMC_MSG_QuewyIPS2Suppowt             0x1C ///< Wetuwn 1: suppowt; ewse not suppowted
#define VBIOSSMC_Message_Count                    0x1D

#define VBIOSSMC_Status_BUSY                      0x0
#define VBIOSSMC_Wesuwt_OK                        0x1
#define VBIOSSMC_Wesuwt_Faiwed                    0xFF
#define VBIOSSMC_Wesuwt_UnknownCmd                0xFE
#define VBIOSSMC_Wesuwt_CmdWejectedPweweq         0xFD
#define VBIOSSMC_Wesuwt_CmdWejectedBusy           0xFC

/*
 * Function to be used instead of WEG_WAIT macwo because the wait ends when
 * the wegistew is NOT EQUAW to zewo, and because `the twanswation in msg_if.h
 * won't wowk with WEG_WAIT.
 */
static uint32_t dcn35_smu_wait_fow_wesponse(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int deway_us, unsigned int max_wetwies)
{
	uint32_t wes_vaw = VBIOSSMC_Status_BUSY;

	do {
		wes_vaw = WEG_WEAD(MP1_SMN_C2PMSG_91);
		if (wes_vaw != VBIOSSMC_Status_BUSY)
			bweak;

		if (deway_us >= 1000)
			msweep(deway_us/1000);
		ewse if (deway_us > 0)
			udeway(deway_us);

		if (cwk_mgw->base.ctx->dc->debug.disabwe_timeout)
			max_wetwies++;
	} whiwe (max_wetwies--);

	wetuwn wes_vaw;
}

static int dcn35_smu_send_msg_with_pawam(stwuct cwk_mgw_intewnaw *cwk_mgw,
					 unsigned int msg_id,
					 unsigned int pawam)
{
	uint32_t wesuwt;

	wesuwt = dcn35_smu_wait_fow_wesponse(cwk_mgw, 10, 2000000);
	ASSEWT(wesuwt == VBIOSSMC_Wesuwt_OK);

	if (wesuwt != VBIOSSMC_Wesuwt_OK) {
		DC_WOG_WAWNING("SMU wesponse aftew wait: %d, msg id = %d\n", wesuwt, msg_id);

		if (wesuwt == VBIOSSMC_Status_BUSY)
			wetuwn -1;
	}

	/* Fiwst cweaw wesponse wegistew */
	WEG_WWITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the pawametew wegistew fow the SMU message, unit is Mhz */
	WEG_WWITE(MP1_SMN_C2PMSG_83, pawam);

	/* Twiggew the message twansaction by wwiting the message ID */
	WEG_WWITE(MP1_SMN_C2PMSG_67, msg_id);

	wesuwt = dcn35_smu_wait_fow_wesponse(cwk_mgw, 10, 2000000);

	if (wesuwt == VBIOSSMC_Wesuwt_Faiwed) {
		if (msg_id == VBIOSSMC_MSG_TwansfewTabweDwam2Smu &&
		    pawam == TABWE_WATEWMAWKS)
			DC_WOG_WAWNING("Watewmawks tabwe not configuwed pwopewwy by SMU");
		ewse
			ASSEWT(0);
		WEG_WWITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Wesuwt_OK);
		DC_WOG_WAWNING("SMU wesponse aftew wait: %d, msg id = %d\n", wesuwt, msg_id);
		wetuwn -1;
	}

	if (IS_SMU_TIMEOUT(wesuwt)) {
		ASSEWT(0);
		wesuwt = dcn35_smu_wait_fow_wesponse(cwk_mgw, 10, 2000000);
		//dm_hewpews_smu_timeout(CTX, msg_id, pawam, 10 * 200000);
		DC_WOG_WAWNING("SMU wesponse aftew wait: %d, msg id = %d\n", wesuwt, msg_id);
	}

	wetuwn WEG_WEAD(MP1_SMN_C2PMSG_83);
}

int dcn35_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	wetuwn dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_GetSmuVewsion,
			0);
}


int dcn35_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz)
{
	int actuaw_dispcwk_set_mhz = -1;

	if (!cwk_mgw->smu_pwesent)
		wetuwn wequested_dispcwk_khz;

	/*  Unit of SMU msg pawametew is Mhz */
	actuaw_dispcwk_set_mhz = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDispcwkFweq,
			khz_to_mhz_ceiw(wequested_dispcwk_khz));

	smu_pwint("wequested_dispcwk_khz = %d, actuaw_dispcwk_set_mhz: %d\n", wequested_dispcwk_khz, actuaw_dispcwk_set_mhz);
	wetuwn actuaw_dispcwk_set_mhz * 1000;
}

int dcn35_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int actuaw_dpwefcwk_set_mhz = -1;

	if (!cwk_mgw->smu_pwesent)
		wetuwn cwk_mgw->base.dpwefcwk_khz;

	actuaw_dpwefcwk_set_mhz = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDpwefcwkFweq,
			khz_to_mhz_ceiw(cwk_mgw->base.dpwefcwk_khz));

	/* TODO: add code fow pwogwaming DP DTO, cuwwentwy this is down by command tabwe */

	wetuwn actuaw_dpwefcwk_set_mhz * 1000;
}

int dcn35_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz)
{
	int actuaw_dcfcwk_set_mhz = -1;

	if (!cwk_mgw->smu_pwesent)
		wetuwn wequested_dcfcwk_khz;

	actuaw_dcfcwk_set_mhz = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetHawdMinDcfcwkByFweq,
			khz_to_mhz_ceiw(wequested_dcfcwk_khz));

	smu_pwint("wequested_dcfcwk_khz = %d, actuaw_dcfcwk_set_mhz: %d\n", wequested_dcfcwk_khz, actuaw_dcfcwk_set_mhz);

	wetuwn actuaw_dcfcwk_set_mhz * 1000;
}

int dcn35_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz)
{
	int actuaw_min_ds_dcfcwk_mhz = -1;

	if (!cwk_mgw->smu_pwesent)
		wetuwn wequested_min_ds_dcfcwk_khz;

	actuaw_min_ds_dcfcwk_mhz = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetMinDeepSweepDcfcwk,
			khz_to_mhz_ceiw(wequested_min_ds_dcfcwk_khz));

	smu_pwint("wequested_min_ds_dcfcwk_khz = %d, actuaw_min_ds_dcfcwk_mhz: %d\n", wequested_min_ds_dcfcwk_khz, actuaw_min_ds_dcfcwk_mhz);

	wetuwn actuaw_min_ds_dcfcwk_mhz * 1000;
}

int dcn35_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz)
{
	int actuaw_dppcwk_set_mhz = -1;

	if (!cwk_mgw->smu_pwesent)
		wetuwn wequested_dpp_khz;

	actuaw_dppcwk_set_mhz = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDppcwkFweq,
			khz_to_mhz_ceiw(wequested_dpp_khz));

	smu_pwint("wequested_dpp_khz = %d, actuaw_dppcwk_set_mhz: %d\n", wequested_dpp_khz, actuaw_dppcwk_set_mhz);

	wetuwn actuaw_dppcwk_set_mhz * 1000;
}

void dcn35_smu_set_dispway_idwe_optimization(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t idwe_info)
{
	if (!cwk_mgw->base.ctx->dc->debug.pstate_enabwed)
		wetuwn;

	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	//TODO: Wowk with smu team to define optimization options.
	dcn35_smu_send_msg_with_pawam(
		cwk_mgw,
		VBIOSSMC_MSG_SetDispwayIdweOptimizations,
		idwe_info);
	smu_pwint("%s: VBIOSSMC_MSG_SetDispwayIdweOptimizations idwe_info  = %x\n", __func__, idwe_info);
}

void dcn35_smu_enabwe_phy_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe)
{
	union dispway_idwe_optimization_u idwe_info = { 0 };

	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	if (enabwe) {
		idwe_info.idwe_info.df_wequest_disabwed = 1;
		idwe_info.idwe_info.phy_wef_cwk_off = 1;
	}

	dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDispwayIdweOptimizations,
			idwe_info.data);
	smu_pwint("%s smu_enabwe_phy_wefcwk_pwwdwn  = %d\n", __func__, enabwe ? 1 : 0);
}

void dcn35_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_UpdatePmeWestowe,
			0);
	smu_pwint("%s: SMC_MSG_UpdatePmeWestowe\n", __func__);
}

void dcn35_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(cwk_mgw,
			VBIOSSMC_MSG_SetVbiosDwamAddwHigh, addw_high);
}

void dcn35_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(cwk_mgw,
			VBIOSSMC_MSG_SetVbiosDwamAddwWow, addw_wow);
}

void dcn35_smu_twansfew_dpm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(cwk_mgw,
			VBIOSSMC_MSG_TwansfewTabweSmu2Dwam, TABWE_DPMCWOCKS);
}

void dcn35_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(cwk_mgw,
			VBIOSSMC_MSG_TwansfewTabweDwam2Smu, TABWE_WATEWMAWKS);
}

void dcn35_smu_set_zstate_suppowt(stwuct cwk_mgw_intewnaw *cwk_mgw, enum dcn_zstate_suppowt_state suppowt)
{
	unsigned int msg_id, pawam, wetv;

	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	switch (suppowt) {

	case DCN_ZSTATE_SUPPOWT_AWWOW:
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = (1 << 10) | (1 << 9) | (1 << 8);
		smu_pwint("%s: SMC_MSG_AwwowZstatesEntwy msg = AWWOW, pawam = %d\n", __func__, pawam);
		bweak;

	case DCN_ZSTATE_SUPPOWT_DISAWWOW:
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = 0;
		smu_pwint("%s: SMC_MSG_AwwowZstatesEntwy msg_id = DISAWWOW, pawam = %d\n",  __func__, pawam);
		bweak;


	case DCN_ZSTATE_SUPPOWT_AWWOW_Z10_ONWY:
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = (1 << 10);
		smu_pwint("%s: SMC_MSG_AwwowZstatesEntwy msg = AWWOW_Z10_ONWY, pawam = %d\n", __func__, pawam);
		bweak;

	case DCN_ZSTATE_SUPPOWT_AWWOW_Z8_Z10_ONWY:
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = (1 << 10) | (1 << 8);
		smu_pwint("%s: SMC_MSG_AwwowZstatesEntwy msg = AWWOW_Z8_Z10_ONWY, pawam = %d\n", __func__, pawam);
		bweak;

	case DCN_ZSTATE_SUPPOWT_AWWOW_Z8_ONWY:
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = (1 << 8);
		smu_pwint("%s: SMC_MSG_AwwowZstatesEntwy msg = AWWOW_Z8_ONWY, pawam = %d\n", __func__, pawam);
		bweak;

	defauwt: //DCN_ZSTATE_SUPPOWT_UNKNOWN
		msg_id = VBIOSSMC_MSG_AwwowZstatesEntwy;
		pawam = 0;
		bweak;
	}


	wetv = dcn35_smu_send_msg_with_pawam(
		cwk_mgw,
		msg_id,
		pawam);
	smu_pwint("%s:  msg_id = %d, pawam = 0x%x, wetuwn = %d\n", __func__, msg_id, pawam, wetv);
}

int dcn35_smu_get_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int dpwefcwk;

	if (!cwk_mgw->smu_pwesent)
		wetuwn 0;

	dpwefcwk = dcn35_smu_send_msg_with_pawam(cwk_mgw,
						 VBIOSSMC_MSG_GetDpwefcwkFweq,
						 0);

	smu_pwint("%s:  SMU DPWEF cwk  = %d mhz\n",  __func__, dpwefcwk);
	wetuwn dpwefcwk * 1000;
}

int dcn35_smu_get_dtbcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int dtbcwk;

	if (!cwk_mgw->smu_pwesent)
		wetuwn 0;

	dtbcwk = dcn35_smu_send_msg_with_pawam(cwk_mgw,
					       VBIOSSMC_MSG_GetDtbcwkFweq,
					       0);

	smu_pwint("%s: get_dtbcwk  = %dmhz\n", __func__, dtbcwk);
	wetuwn dtbcwk * 1000;
}
/* Awg = 1: Tuwn DTB on; 0: Tuwn DTB CWK OFF. when it is on, it is 600MHZ */
void dcn35_smu_set_dtbcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe)
{
	if (!cwk_mgw->smu_pwesent)
		wetuwn;

	dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDtbCwk,
			enabwe);
	smu_pwint("%s: smu_set_dtbcwk = %d\n", __func__, enabwe ? 1 : 0);
}

void dcn35_vbios_smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe)
{
	dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown,
			enabwe);
	smu_pwint("%s: smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn = %d\n", __func__, enabwe ? 1 : 0);
}

int dcn35_smu_exit_wow_powew_state(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int wetv;

	wetv = dcn35_smu_send_msg_with_pawam(
		cwk_mgw,
		VBIOSSMC_MSG_DispPswExit,
		0);
	smu_pwint("%s: smu_exit_wow_powew_state wetuwn = %d\n", __func__, wetv);
	wetuwn wetv;
}

int dcn35_smu_get_ips_suppowted(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int wetv;

	wetv = dcn35_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_QuewyIPS2Suppowt,
			0);

	//smu_pwint("%s: VBIOSSMC_MSG_QuewyIPS2Suppowt wetuwn = %x\n", __func__, wetv);
	wetuwn wetv;
}

void dcn35_smu_wwite_ips_scwatch(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t pawam)
{
	WEG_WWITE(MP1_SMN_C2PMSG_71, pawam);
	//smu_pwint("%s: wwite_ips_scwatch = %x\n", __func__, pawam);
}

uint32_t dcn35_smu_wead_ips_scwatch(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	uint32_t wetv;

	wetv = WEG_WEAD(MP1_SMN_C2PMSG_71);
	//smu_pwint("%s: dcn35_smu_wead_ips_scwatch = %x\n",  __func__, wetv);
	wetuwn wetv;
}
