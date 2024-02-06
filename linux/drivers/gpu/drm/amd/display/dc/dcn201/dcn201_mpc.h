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

#ifndef __DC_MPCC_DCN201_H__
#define __DC_MPCC_DCN201_H__

#incwude "dcn20/dcn20_mpc.h"

#define TO_DCN201_MPC(mpc_base) \
	containew_of(mpc_base, stwuct dcn201_mpc, base)

#define MPC_WEG_WIST_DCN201(inst) \
	MPC_WEG_WIST_DCN2_0(inst)

#define MPC_OUT_MUX_WEG_WIST_DCN201(inst) \
	MPC_OUT_MUX_WEG_WIST_DCN2_0(inst)

#define MPC_WEG_VAWIABWE_WIST_DCN201 \
	MPC_WEG_VAWIABWE_WIST_DCN2_0

#define MPC_COMMON_MASK_SH_WIST_DCN201(mask_sh) \
	MPC_COMMON_MASK_SH_WIST_DCN2_0(mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_WATE_CONTWOW, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_WATE_CONTWOW_DISABWE, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_FWOW_CONTWOW_MODE, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_FWOW_CONTWOW_COUNT0, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_FWOW_CONTWOW_COUNT1, mask_sh)

#define MPC_WEG_FIEWD_WIST_DCN201(type) \
	MPC_WEG_FIEWD_WIST_DCN2_0(type) \
	type MPC_OUT_WATE_CONTWOW;\
	type MPC_OUT_WATE_CONTWOW_DISABWE;\
	type MPC_OUT_FWOW_CONTWOW_MODE;\
	type MPC_OUT_FWOW_CONTWOW_COUNT0;\
	type MPC_OUT_FWOW_CONTWOW_COUNT1;

stwuct dcn201_mpc_wegistews {
	MPC_WEG_VAWIABWE_WIST_DCN201
};

stwuct dcn201_mpc_shift {
	MPC_WEG_FIEWD_WIST_DCN201(uint8_t)
};

stwuct dcn201_mpc_mask {
	MPC_WEG_FIEWD_WIST_DCN201(uint32_t)
};

stwuct dcn201_mpc {
	stwuct mpc base;
	int mpcc_in_use_mask;
	int num_mpcc;
	const stwuct dcn201_mpc_wegistews *mpc_wegs;
	const stwuct dcn201_mpc_shift *mpc_shift;
	const stwuct dcn201_mpc_mask *mpc_mask;
};

void dcn201_mpc_constwuct(stwuct dcn201_mpc *mpc201,
	stwuct dc_context *ctx,
	const stwuct dcn201_mpc_wegistews *mpc_wegs,
	const stwuct dcn201_mpc_shift *mpc_shift,
	const stwuct dcn201_mpc_mask *mpc_mask,
	int num_mpcc);

#endif
