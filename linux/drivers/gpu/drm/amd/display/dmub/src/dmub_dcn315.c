/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "../dmub_swv.h"
#incwude "dmub_weg.h"
#incwude "dmub_dcn315.h"

#incwude "dcn/dcn_3_1_5_offset.h"
#incwude "dcn/dcn_3_1_5_sh_mask.h"

#define DCN_BASE__INST0_SEG0                       0x00000012
#define DCN_BASE__INST0_SEG1                       0x000000C0
#define DCN_BASE__INST0_SEG2                       0x000034C0
#define DCN_BASE__INST0_SEG3                       0x00009000
#define DCN_BASE__INST0_SEG4                       0x02403C00
#define DCN_BASE__INST0_SEG5                       0

#define BASE_INNEW(seg) DCN_BASE__INST0_SEG##seg
#define CTX dmub
#define WEGS dmub->wegs_dcn31
#define WEG_OFFSET_EXP(weg_name) (BASE(weg##weg_name##_BASE_IDX) + weg##weg_name)

/* Wegistews. */

const stwuct dmub_swv_dcn31_wegs dmub_swv_dcn315_wegs = {
#define DMUB_SW(weg) WEG_OFFSET_EXP(weg),
	{
		DMUB_DCN31_WEGS()
		DMCUB_INTEWNAW_WEGS()
	},
#undef DMUB_SW

#define DMUB_SF(weg, fiewd) FD_MASK(weg, fiewd),
	{ DMUB_DCN315_FIEWDS() },
#undef DMUB_SF

#define DMUB_SF(weg, fiewd) FD_SHIFT(weg, fiewd),
	{ DMUB_DCN315_FIEWDS() },
#undef DMUB_SF
};
