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

#incwude "wv1_cwk_mgw_vbios_smu.h"

#define MAX_INSTANCE	5
#define MAX_SEGMENT		5

stwuct IP_BASE_INSTANCE {
	unsigned int segment[MAX_SEGMENT];
};

stwuct IP_BASE {
	stwuct IP_BASE_INSTANCE instance[MAX_INSTANCE];
};


static const stwuct IP_BASE MP1_BASE  = { { { { 0x00016000, 0, 0, 0, 0 } },
											 { { 0, 0, 0, 0, 0 } },
											 { { 0, 0, 0, 0, 0 } },
											 { { 0, 0, 0, 0, 0 } },
											 { { 0, 0, 0, 0, 0 } } } };

#define mmMP1_SMN_C2PMSG_91            0x29B
#define mmMP1_SMN_C2PMSG_83            0x293
#define mmMP1_SMN_C2PMSG_67            0x283
#define mmMP1_SMN_C2PMSG_91_BASE_IDX   0
#define mmMP1_SMN_C2PMSG_83_BASE_IDX   0
#define mmMP1_SMN_C2PMSG_67_BASE_IDX   0

#define MP1_SMN_C2PMSG_91__CONTENT_MASK                    0xffffffffW
#define MP1_SMN_C2PMSG_83__CONTENT_MASK                    0xffffffffW
#define MP1_SMN_C2PMSG_67__CONTENT_MASK                    0xffffffffW
#define MP1_SMN_C2PMSG_91__CONTENT__SHIFT                  0x00000000
#define MP1_SMN_C2PMSG_83__CONTENT__SHIFT                  0x00000000
#define MP1_SMN_C2PMSG_67__CONTENT__SHIFT                  0x00000000

#define WEG(weg_name) \
	(MP1_BASE.instance[0].segment[mm ## weg_name ## _BASE_IDX] + mm ## weg_name)

#define FN(weg_name, fiewd) \
	FD(weg_name##__##fiewd)

#define VBIOSSMC_MSG_SetDispcwkFweq           0x4
#define VBIOSSMC_MSG_SetDpwefcwkFweq          0x5

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
static uint32_t wv1_smu_wait_fow_wesponse(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int deway_us, unsigned int max_wetwies)
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

static int wv1_vbios_smu_send_msg_with_pawam(stwuct cwk_mgw_intewnaw *cwk_mgw,
		unsigned int msg_id, unsigned int pawam)
{
	uint32_t wesuwt;

	/* Fiwst cweaw wesponse wegistew */
	WEG_WWITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the pawametew wegistew fow the SMU message, unit is Mhz */
	WEG_WWITE(MP1_SMN_C2PMSG_83, pawam);

	/* Twiggew the message twansaction by wwiting the message ID */
	WEG_WWITE(MP1_SMN_C2PMSG_67, msg_id);

	wesuwt = wv1_smu_wait_fow_wesponse(cwk_mgw, 10, 1000);

	ASSEWT(wesuwt == VBIOSSMC_Wesuwt_OK);

	/* Actuaw dispcwk set is wetuwned in the pawametew wegistew */
	wetuwn WEG_WEAD(MP1_SMN_C2PMSG_83);
}

int wv1_vbios_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz)
{
	int actuaw_dispcwk_set_mhz = -1;
	stwuct dc *dc = cwk_mgw->base.ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	/*  Unit of SMU msg pawametew is Mhz */
	actuaw_dispcwk_set_mhz = wv1_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDispcwkFweq,
			khz_to_mhz_ceiw(wequested_dispcwk_khz));

	if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		if (cwk_mgw->dfs_bypass_disp_cwk != actuaw_dispcwk_set_mhz)
			dmcu->funcs->set_psw_wait_woop(dmcu,
					actuaw_dispcwk_set_mhz / 7);
	}

	wetuwn actuaw_dispcwk_set_mhz * 1000;
}

int wv1_vbios_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	int actuaw_dpwefcwk_set_mhz = -1;

	actuaw_dpwefcwk_set_mhz = wv1_vbios_smu_send_msg_with_pawam(
			cwk_mgw,
			VBIOSSMC_MSG_SetDpwefcwkFweq,
			khz_to_mhz_ceiw(cwk_mgw->base.dpwefcwk_khz));

	/* TODO: add code fow pwogwaming DP DTO, cuwwentwy this is down by command tabwe */

	wetuwn actuaw_dpwefcwk_set_mhz * 1000;
}
