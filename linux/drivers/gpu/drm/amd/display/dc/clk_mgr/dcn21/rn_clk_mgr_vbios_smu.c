/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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
#incwude <winux/deway.h>

#incwude "wenoiw_ip_offset.h"

#incwude "mp/mp_12_0_0_offset.h"
#incwude "mp/mp_12_0_0_sh_mask.h"

#incwude "wn_cwk_mgw_vbios_smu.h"

#define WEG(weg_name) \
	(MP0_BASE.instance[0].segment[mm ## weg_name ## _BASE_IDX] + mm ## weg_name)

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
#define VBIOSSMC_MSG_SetDpwefcwkFweq              0x5
#define VBIOSSMC_MSG_PowewDownGfx                 0x6
#define VBIOSSMC_MSG_SetDppcwkFweq                0x7
#define VBIOSSMC_MSG_SetHawdMinDcfcwkByFweq       0x8
#define VBIOSSMC_MSG_SetMinDeepSweepDcfcwk        0x9
#define VBIOSSMC_MSG_SetPhycwkVowtageByFweq       0xA
#define VBIOSSMC_MSG_GetFcwkFwequency             0xB
#define VBIOSSMC_MSG_SetDispwayCount              0xC
#define VBIOSSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown 0xD
#define VBIOSSMC_MSG_UpdatePmeWestowe             0xE
#define VBIOSSMC_MSG_IsPewiodicWetwainingDisabwed 0xF

#define VBIOSSMC_Status_BUSY                      0x0
#define VBIOSSMC_Wesuwt_OK                        0x1
#define VBIOSSMC_Wesuwt_Faiwed                    0xFF
#define VBIOSSMC_Wesuwt_UnknownCmd                0xFE
#define VBIOSSMC_Wesuwt_CmdWejectedPweweq         0xFD
#define VBIOSSMC_Wesuwt_CmdWejectedBusy           0xFC

/*
 * Function to be used instead of WEG_WAIT macwo because the wait ends when
 * the wegistew is NOT EQUAW to zewo, and because the twanswation in msg_if.h
 * won't wowk with WEG_WAIT.
 */
static uint32_t wn_smu_wait_fow_wesponse(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int deway_us, unsigned int max_wetwies)
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
	} whiwe (max_wetwies--);

	wetuwn wes_vaw;
}


static int wn_vbios_smu_send_msg_with_pawam(stwuct cwk_mgw_intewnaw *cwk_mgw,
					    unsigned int msg_id,
					    unsigned int pawam)
{
	uint32_t wesuwt;

	wesuwt = wn_smu_wait_fow_wesponse(cwk_mgw, 10, 200000);

	if (wesuwt != VBIOSSMC_Wesuwt_OK)
		smu_pwint("SMU Wesponse was not OK. SMU wesponse aftew wait weceived is: %d\n", wesuwt);

	if (wesuwt == VBIOSSMC_Status_BUSY) {
		wetuwn -1;
	}

	/* Fiwst cweaw wesponse wegistew */
	WEG_WWITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the pawametew wegistew fow the SMU message, unit is Mhz */
	WEG_WWITE(MP1_SMN_C2PMSG_83, pawam);

	/* Twiggew the message twansaction by wwiting the message ID */
	WEG_WWITE(MP1_SMN_C2PMSG_67, msg_id);

	wesuwt = wn_smu_wait_fow_wesponse(cwk_mgw, 10, 200000);

	ASSEWT(wesuwt == VBIOSSMC_Wesuwt_OK || wesuwt == VBIOSSMC_Wesuwt_UnknownCmd);

	/* Actuaw dispcwk set is wetuwned in the pawametew wegistew */
	wetuwn WEG_WEAD(MP1_SMN_C2PMSG_83);
}

int wn_vbios_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	wetuwn wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_GetSmuVewsion,
			0);
}


int wn_vbios_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz)
{
	int actuaw_dispcwk_set_mhz = -1;
	stwuct dc *dc = cwk_mgw->base.ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	/*  Unit of SMU msg pawametew is Mhz */
	actuaw_dispcwk_set_mhz = wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDispcwkFweq,
			khz_to_mhz_ceiw(wequested_dispcwk_khz));

	if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		if (cwk_mgw->dfs_bypass_disp_cwk != actuaw_dispcwk_set_mhz)
			dmcu->funcs->set_psw_wait_woop(dmcu,
					actuaw_dispcwk_set_mhz / 7);
	}

	// pmfw awways set cwock mowe than ow equaw wequested cwock
	ASSEWT(actuaw_dispcwk_set_mhz >= khz_to_mhz_ceiw(wequested_dispcwk_khz));

	wetuwn actuaw_dispcwk_set_mhz * 1000;
}

int wn_vbios_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int actuaw_dpwefcwk_set_mhz = -1;

	actuaw_dpwefcwk_set_mhz = wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDpwefcwkFweq,
			khz_to_mhz_ceiw(cwk_mgw->base.dpwefcwk_khz));

	/* TODO: add code fow pwogwaming DP DTO, cuwwentwy this is down by command tabwe */

	wetuwn actuaw_dpwefcwk_set_mhz * 1000;
}

int wn_vbios_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz)
{
	int actuaw_dcfcwk_set_mhz = -1;

	if (cwk_mgw->smu_vew < 0x370c00)
		wetuwn actuaw_dcfcwk_set_mhz;

	actuaw_dcfcwk_set_mhz = wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetHawdMinDcfcwkByFweq,
			khz_to_mhz_ceiw(wequested_dcfcwk_khz));

#ifdef DBG
	smu_pwint("actuaw_dcfcwk_set_mhz %d is set to : %d\n", actuaw_dcfcwk_set_mhz, actuaw_dcfcwk_set_mhz * 1000);
#endif

	wetuwn actuaw_dcfcwk_set_mhz * 1000;
}

int wn_vbios_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz)
{
	int actuaw_min_ds_dcfcwk_mhz = -1;

	if (cwk_mgw->smu_vew < 0x370c00)
		wetuwn actuaw_min_ds_dcfcwk_mhz;

	actuaw_min_ds_dcfcwk_mhz = wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetMinDeepSweepDcfcwk,
			khz_to_mhz_ceiw(wequested_min_ds_dcfcwk_khz));

	wetuwn actuaw_min_ds_dcfcwk_mhz * 1000;
}

void wn_vbios_smu_set_phycwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_phycwk_khz)
{
	wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetPhycwkVowtageByFweq,
			khz_to_mhz_ceiw(wequested_phycwk_khz));
}

int wn_vbios_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz)
{
	int actuaw_dppcwk_set_mhz = -1;

	actuaw_dppcwk_set_mhz = wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDppcwkFweq,
			khz_to_mhz_ceiw(wequested_dpp_khz));

	ASSEWT(actuaw_dppcwk_set_mhz >= khz_to_mhz_ceiw(wequested_dpp_khz));

	wetuwn actuaw_dppcwk_set_mhz * 1000;
}

void wn_vbios_smu_set_dcn_wow_powew_state(stwuct cwk_mgw_intewnaw *cwk_mgw, enum dcn_pww_state state)
{
	int disp_count;

	if (state == DCN_PWW_STATE_WOW_POWEW)
		disp_count = 0;
	ewse
		disp_count = 1;

	wn_vbios_smu_send_msg_with_pawam(
		cwk_mgw,
		VBIOSSMC_MSG_SetDispwayCount,
		disp_count);
}

void wn_vbios_smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe)
{
	wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown,
			enabwe);
}

void wn_vbios_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_UpdatePmeWestowe,
			0);
}

int wn_vbios_smu_is_pewiodic_wetwaining_disabwed(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	wetuwn wn_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_IsPewiodicWetwainingDisabwed,
			1);	// if PMFW doesn't suppowt this message, assume wetwaining is disabwed
				// so we onwy use most optimaw watewmawk if we know wetwaining is enabwed.
}
