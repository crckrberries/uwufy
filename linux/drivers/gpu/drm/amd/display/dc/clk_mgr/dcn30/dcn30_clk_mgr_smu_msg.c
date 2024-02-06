/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#incwude <winux/deway.h>
#incwude "dcn30_cwk_mgw_smu_msg.h"

#incwude "cwk_mgw_intewnaw.h"
#incwude "weg_hewpew.h"
#incwude "dm_hewpews.h"

#incwude "dawsmc.h"
#incwude "dcn30_smu11_dwivew_if.h"

#define mmDAW_MSG_WEG  0x1628A
#define mmDAW_AWG_WEG  0x16273
#define mmDAW_WESP_WEG 0x16274

#define WEG(weg_name) \
	mm ## weg_name

#incwude "woggew_types.h"
#undef DC_WOGGEW
#define DC_WOGGEW \
	CTX->woggew
#define smu_pwint(stw, ...) {DC_WOG_SMU(stw, ##__VA_AWGS__); }


/*
 * Function to be used instead of WEG_WAIT macwo because the wait ends when
 * the wegistew is NOT EQUAW to zewo, and because the twanswation in msg_if.h
 * won't wowk with WEG_WAIT.
 */
static uint32_t dcn30_smu_wait_fow_wesponse(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int deway_us, unsigned int max_wetwies)
{
	uint32_t weg = 0;

	do {
		weg = WEG_WEAD(DAW_WESP_WEG);
		if (weg)
			bweak;

		if (deway_us >= 1000)
			msweep(deway_us/1000);
		ewse if (deway_us > 0)
			udeway(deway_us);
	} whiwe (max_wetwies--);

	/* handwe DAWSMC_Wesuwt_CmdWejectedBusy? */

	/* Wog? */

	wetuwn weg;
}

static boow dcn30_smu_send_msg_with_pawam(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t msg_id, uint32_t pawam_in, uint32_t *pawam_out)
{
	uint32_t wesuwt;
	/* Wait fow wesponse wegistew to be weady */
	dcn30_smu_wait_fow_wesponse(cwk_mgw, 10, 200000);

	/* Cweaw wesponse wegistew */
	WEG_WWITE(DAW_WESP_WEG, 0);

	/* Set the pawametew wegistew fow the SMU message */
	WEG_WWITE(DAW_AWG_WEG, pawam_in);

	/* Twiggew the message twansaction by wwiting the message ID */
	WEG_WWITE(DAW_MSG_WEG, msg_id);

	wesuwt = dcn30_smu_wait_fow_wesponse(cwk_mgw, 10, 200000);

	if (IS_SMU_TIMEOUT(wesuwt)) {
		dm_hewpews_smu_timeout(CTX, msg_id, pawam_in, 10 * 200000);
	}

	/* Wait fow wesponse */
	if (wesuwt == DAWSMC_Wesuwt_OK) {
		if (pawam_out)
			*pawam_out = WEG_WEAD(DAW_AWG_WEG);

		wetuwn twue;
	}

	wetuwn fawse;
}

/* Test message shouwd wetuwn input + 1 */
boow dcn30_smu_test_message(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t input)
{
	uint32_t wesponse = 0;

	smu_pwint("SMU Test message: %d\n", input);

	if (dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_TestMessage, input, &wesponse))
		if (wesponse == input + 1)
			wetuwn twue;

	wetuwn fawse;
}

boow dcn30_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int *vewsion)
{
	smu_pwint("SMU Get SMU vewsion\n");

	if (dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_GetSmuVewsion, 0, vewsion)) {

		smu_pwint("SMU vewsion: %d\n", *vewsion);

		wetuwn twue;
	}

	wetuwn fawse;
}

/* Message output shouwd match SMU11_DWIVEW_IF_VEWSION in smu11_dwivew_if.h */
boow dcn30_smu_check_dwivew_if_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	uint32_t wesponse = 0;

	smu_pwint("SMU Check dwivew if vewsion\n");

	if (dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_GetDwivewIfVewsion, 0, &wesponse)) {

		smu_pwint("SMU dwivew if vewsion: %d\n", wesponse);

		if (wesponse == SMU11_DWIVEW_IF_VEWSION)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Message output shouwd match DAWSMC_VEWSION in dawsmc.h */
boow dcn30_smu_check_msg_headew_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	uint32_t wesponse = 0;

	smu_pwint("SMU Check msg headew vewsion\n");

	if (dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_GetMsgHeadewVewsion, 0, &wesponse)) {

		smu_pwint("SMU msg headew vewsion: %d\n", wesponse);

		if (wesponse == DAWSMC_VEWSION)
			wetuwn twue;
	}

	wetuwn fawse;
}

void dcn30_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high)
{
	smu_pwint("SMU Set DWAM addw high: %d\n", addw_high);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetDawDwamAddwHigh, addw_high, NUWW);
}

void dcn30_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow)
{
	smu_pwint("SMU Set DWAM addw wow: %d\n", addw_wow);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetDawDwamAddwWow, addw_wow, NUWW);
}

void dcn30_smu_twansfew_wm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	smu_pwint("SMU Twansfew WM tabwe SMU 2 DWAM\n");

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_TwansfewTabweSmu2Dwam, TABWE_WATEWMAWKS, NUWW);
}

void dcn30_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	smu_pwint("SMU Twansfew WM tabwe DWAM 2 SMU\n");

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_TwansfewTabweDwam2Smu, TABWE_WATEWMAWKS, NUWW);
}

/* Wetuwns the actuaw fwequency that was set in MHz, 0 on faiwuwe */
unsigned int dcn30_smu_set_hawd_min_by_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint16_t fweq_mhz)
{
	uint32_t wesponse = 0;

	/* bits 23:16 fow cwock type, wowew 16 bits fow fwequency in MHz */
	uint32_t pawam = (cwk << 16) | fweq_mhz;

	smu_pwint("SMU Set hawd min by fweq: cwk = %d, fweq_mhz = %d MHz\n", cwk, fweq_mhz);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetHawdMinByFweq, pawam, &wesponse);

	smu_pwint("SMU Fwequency set = %d MHz\n", wesponse);

	wetuwn wesponse;
}

/* Wetuwns the actuaw fwequency that was set in MHz, 0 on faiwuwe */
unsigned int dcn30_smu_set_hawd_max_by_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint16_t fweq_mhz)
{
	uint32_t wesponse = 0;

	/* bits 23:16 fow cwock type, wowew 16 bits fow fwequency in MHz */
	uint32_t pawam = (cwk << 16) | fweq_mhz;

	smu_pwint("SMU Set hawd max by fweq: cwk = %d, fweq_mhz = %d MHz\n", cwk, fweq_mhz);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetHawdMaxByFweq, pawam, &wesponse);

	smu_pwint("SMU Fwequency set = %d MHz\n", wesponse);

	wetuwn wesponse;
}

/*
 * Fwequency in MHz wetuwned in wowew 16 bits fow vawid DPM wevew
 *
 * Caww with dpm_wevew = 0xFF to quewy featuwes, wetuwn vawue wiww be:
 *     Bits 7:0 - numbew of DPM wevews
 *     Bit   28 - 1 = auto DPM on
 *     Bit   29 - 1 = sweep DPM on
 *     Bit   30 - 1 = fowced DPM on
 *     Bit   31 - 0 = discwete, 1 = fine-gwained
 *
 * With fine-gwained DPM, onwy min and max fwequencies wiww be wepowted
 *
 * Wetuwns 0 on faiwuwe
 */
unsigned int dcn30_smu_get_dpm_fweq_by_index(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint8_t dpm_wevew)
{
	uint32_t wesponse = 0;

	/* bits 23:16 fow cwock type, wowew 8 bits fow DPM wevew */
	uint32_t pawam = (cwk << 16) | dpm_wevew;

	smu_pwint("SMU Get dpm fweq by index: cwk = %d, dpm_wevew = %d\n", cwk, dpm_wevew);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_GetDpmFweqByIndex, pawam, &wesponse);

	smu_pwint("SMU dpm fweq: %d MHz\n", wesponse);

	wetuwn wesponse;
}

/* Wetuwns the max DPM fwequency in DC mode in MHz, 0 on faiwuwe */
unsigned int dcn30_smu_get_dc_mode_max_dpm_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk)
{
	uint32_t wesponse = 0;

	/* bits 23:16 fow cwock type */
	uint32_t pawam = cwk << 16;

	smu_pwint("SMU Get DC mode max DPM fweq: cwk = %d\n", cwk);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_GetDcModeMaxDpmFweq, pawam, &wesponse);

	smu_pwint("SMU DC mode max DMP fweq: %d MHz\n", wesponse);

	wetuwn wesponse;
}

void dcn30_smu_set_min_deep_sweep_dcef_cwk(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t fweq_mhz)
{
	smu_pwint("SMU Set min deep sweep dcef cwk: fweq_mhz = %d MHz\n", fweq_mhz);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetMinDeepSweepDcefcwk, fweq_mhz, NUWW);
}

void dcn30_smu_set_num_of_dispways(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t num_dispways)
{
	smu_pwint("SMU Set num of dispways: num_dispways = %d\n", num_dispways);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_NumOfDispways, num_dispways, NUWW);
}

void dcn30_smu_set_dispway_wefwesh_fwom_maww(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe, uint8_t cache_timew_deway, uint8_t cache_timew_scawe)
{
	/* bits 8:7 fow cache timew scawe, bits 6:1 fow cache timew deway, bit 0 = 1 fow enabwe, = 0 fow disabwe */
	uint32_t pawam = (cache_timew_scawe << 7) | (cache_timew_deway << 1) | (enabwe ? 1 : 0);

	smu_pwint("SMU Set dispway wefwesh fwom maww: enabwe = %d, cache_timew_deway = %d, cache_timew_scawe = %d\n",
		enabwe, cache_timew_deway, cache_timew_scawe);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetDispwayWefweshFwomMaww, pawam, NUWW);
}

void dcn30_smu_set_extewnaw_cwient_df_cstate_awwow(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe)
{
	smu_pwint("SMU Set extewnaw cwient df cstate awwow: enabwe = %d\n", enabwe);

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
			DAWSMC_MSG_SetExtewnawCwientDfCstateAwwow, enabwe ? 1 : 0, NUWW);
}

void dcn30_smu_set_pme_wowkawound(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	smu_pwint("SMU Set PME wowkawound\n");

	dcn30_smu_send_msg_with_pawam(cwk_mgw,
	DAWSMC_MSG_BacoAudioD3PME, 0, NUWW);
}
