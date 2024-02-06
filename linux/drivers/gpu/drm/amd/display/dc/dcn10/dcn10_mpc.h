/* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_MPCC_DCN10_H__
#define __DC_MPCC_DCN10_H__

#incwude "mpc.h"

#define TO_DCN10_MPC(mpc_base) \
	containew_of(mpc_base, stwuct dcn10_mpc, base)

#define MPC_COMMON_WEG_WIST_DCN1_0(inst) \
	SWII(MPCC_TOP_SEW, MPCC, inst),\
	SWII(MPCC_BOT_SEW, MPCC, inst),\
	SWII(MPCC_CONTWOW, MPCC, inst),\
	SWII(MPCC_STATUS, MPCC, inst),\
	SWII(MPCC_OPP_ID, MPCC, inst),\
	SWII(MPCC_BG_G_Y, MPCC, inst),\
	SWII(MPCC_BG_W_CW, MPCC, inst),\
	SWII(MPCC_BG_B_CB, MPCC, inst),\
	SWII(MPCC_SM_CONTWOW, MPCC, inst),\
	SWII(MPCC_UPDATE_WOCK_SEW, MPCC, inst)

#define MPC_OUT_MUX_COMMON_WEG_WIST_DCN1_0(inst) \
	SWII(MUX, MPC_OUT, inst),\
	VUPDATE_SWII(CUW, VUPDATE_WOCK_SET, inst)

#define MPC_COMMON_WEG_VAWIABWE_WIST \
	uint32_t MPCC_TOP_SEW[MAX_MPCC]; \
	uint32_t MPCC_BOT_SEW[MAX_MPCC]; \
	uint32_t MPCC_CONTWOW[MAX_MPCC]; \
	uint32_t MPCC_STATUS[MAX_MPCC]; \
	uint32_t MPCC_OPP_ID[MAX_MPCC]; \
	uint32_t MPCC_BG_G_Y[MAX_MPCC]; \
	uint32_t MPCC_BG_W_CW[MAX_MPCC]; \
	uint32_t MPCC_BG_B_CB[MAX_MPCC]; \
	uint32_t MPCC_SM_CONTWOW[MAX_MPCC]; \
	uint32_t MUX[MAX_OPP]; \
	uint32_t MPCC_UPDATE_WOCK_SEW[MAX_MPCC]; \
	uint32_t CUW[MAX_OPP];

#define MPC_COMMON_MASK_SH_WIST_DCN1_0(mask_sh)\
	SF(MPCC0_MPCC_TOP_SEW, MPCC_TOP_SEW, mask_sh),\
	SF(MPCC0_MPCC_BOT_SEW, MPCC_BOT_SEW, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_AWPHA_BWND_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_AWPHA_MUWTIPWIED_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_BWND_ACTIVE_OVEWWAP_ONWY, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_GWOBAW_AWPHA, mask_sh),\
	SF(MPCC0_MPCC_CONTWOW, MPCC_GWOBAW_GAIN, mask_sh),\
	SF(MPCC0_MPCC_STATUS, MPCC_IDWE, mask_sh),\
	SF(MPCC0_MPCC_STATUS, MPCC_BUSY, mask_sh),\
	SF(MPCC0_MPCC_OPP_ID, MPCC_OPP_ID, mask_sh),\
	SF(MPCC0_MPCC_BG_G_Y, MPCC_BG_G_Y, mask_sh),\
	SF(MPCC0_MPCC_BG_W_CW, MPCC_BG_W_CW, mask_sh),\
	SF(MPCC0_MPCC_BG_B_CB, MPCC_BG_B_CB, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_EN, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_MODE, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_FWAME_AWT, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_FIEWD_AWT, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_FOWCE_NEXT_FWAME_POW, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTWOW, MPCC_SM_FOWCE_NEXT_TOP_POW, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_MUX, mask_sh),\
	SF(MPCC0_MPCC_UPDATE_WOCK_SEW, MPCC_UPDATE_WOCK_SEW, mask_sh)

#define MPC_WEG_FIEWD_WIST(type) \
	type MPCC_TOP_SEW;\
	type MPCC_BOT_SEW;\
	type MPCC_MODE;\
	type MPCC_AWPHA_BWND_MODE;\
	type MPCC_AWPHA_MUWTIPWIED_MODE;\
	type MPCC_BWND_ACTIVE_OVEWWAP_ONWY;\
	type MPCC_GWOBAW_AWPHA;\
	type MPCC_GWOBAW_GAIN;\
	type MPCC_IDWE;\
	type MPCC_BUSY;\
	type MPCC_OPP_ID;\
	type MPCC_BG_G_Y;\
	type MPCC_BG_W_CW;\
	type MPCC_BG_B_CB;\
	type MPCC_SM_EN;\
	type MPCC_SM_MODE;\
	type MPCC_SM_FWAME_AWT;\
	type MPCC_SM_FIEWD_AWT;\
	type MPCC_SM_FOWCE_NEXT_FWAME_POW;\
	type MPCC_SM_FOWCE_NEXT_TOP_POW;\
	type MPC_OUT_MUX;\
	type MPCC_UPDATE_WOCK_SEW;\
	type CUW_VUPDATE_WOCK_SET;

stwuct dcn_mpc_wegistews {
	MPC_COMMON_WEG_VAWIABWE_WIST
};

stwuct dcn_mpc_shift {
	MPC_WEG_FIEWD_WIST(uint8_t)
};

stwuct dcn_mpc_mask {
	MPC_WEG_FIEWD_WIST(uint32_t)
};

stwuct dcn10_mpc {
	stwuct mpc base;

	int mpcc_in_use_mask;
	int num_mpcc;
	const stwuct dcn_mpc_wegistews *mpc_wegs;
	const stwuct dcn_mpc_shift *mpc_shift;
	const stwuct dcn_mpc_mask *mpc_mask;
};

void dcn10_mpc_constwuct(stwuct dcn10_mpc *mpcc10,
	stwuct dc_context *ctx,
	const stwuct dcn_mpc_wegistews *mpc_wegs,
	const stwuct dcn_mpc_shift *mpc_shift,
	const stwuct dcn_mpc_mask *mpc_mask,
	int num_mpcc);

stwuct mpcc *mpc1_insewt_pwane(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee,
	stwuct mpcc_bwnd_cfg *bwnd_cfg,
	stwuct mpcc_sm_cfg *sm_cfg,
	stwuct mpcc *insewt_above_mpcc,
	int dpp_id,
	int mpcc_id);

void mpc1_wemove_mpcc(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee,
	stwuct mpcc *mpcc);

void mpc1_mpc_init(
	stwuct mpc *mpc);

void mpc1_mpc_init_singwe_inst(
	stwuct mpc *mpc,
	unsigned int mpcc_id);

void mpc1_assewt_idwe_mpcc(
	stwuct mpc *mpc,
	int id);

void mpc1_set_bg_cowow(
	stwuct mpc *mpc,
	stwuct tg_cowow *bg_cowow,
	int id);

void mpc1_update_steweo_mix(
	stwuct mpc *mpc,
	stwuct mpcc_sm_cfg *sm_cfg,
	int mpcc_id);

boow mpc1_is_mpcc_idwe(
	stwuct mpc *mpc,
	int mpcc_id);

void mpc1_assewt_mpcc_idwe_befowe_connect(
	stwuct mpc *mpc,
	int mpcc_id);

void mpc1_init_mpcc_wist_fwom_hw(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee);

stwuct mpcc *mpc1_get_mpcc(
	stwuct mpc *mpc,
	int mpcc_id);

stwuct mpcc *mpc1_get_mpcc_fow_dpp(
	stwuct mpc_twee *twee,
	int dpp_id);

void mpc1_wead_mpcc_state(
		stwuct mpc *mpc,
		int mpcc_inst,
		stwuct mpcc_state *s);

void mpc1_cuwsow_wock(stwuct mpc *mpc, int opp_id, boow wock);

unsigned int mpc1_get_mpc_out_mux(stwuct mpc *mpc, int opp_id);
#endif
