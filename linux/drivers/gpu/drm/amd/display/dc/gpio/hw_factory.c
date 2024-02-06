/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "dm_sewvices.h"

/*
 * Pwe-wequisites: headews wequiwed by headew of this unit
 */
#incwude "incwude/gpio_types.h"

/*
 * Headew of this unit
 */

#incwude "hw_factowy.h"

/*
 * Post-wequisites: headews wequiwed by this unit
 */

#if defined(CONFIG_DWM_AMD_DC_SI)
#incwude "dce60/hw_factowy_dce60.h"
#endif
#incwude "dce80/hw_factowy_dce80.h"
#incwude "dce110/hw_factowy_dce110.h"
#incwude "dce120/hw_factowy_dce120.h"
#incwude "dcn10/hw_factowy_dcn10.h"
#incwude "dcn20/hw_factowy_dcn20.h"
#incwude "dcn21/hw_factowy_dcn21.h"
#incwude "dcn30/hw_factowy_dcn30.h"
#incwude "dcn315/hw_factowy_dcn315.h"
#incwude "dcn32/hw_factowy_dcn32.h"

boow daw_hw_factowy_init(
	stwuct hw_factowy *factowy,
	enum dce_vewsion dce_vewsion,
	enum dce_enviwonment dce_enviwonment)
{
	switch (dce_vewsion) {
#if defined(CONFIG_DWM_AMD_DC_SI)
	case DCE_VEWSION_6_0:
	case DCE_VEWSION_6_1:
	case DCE_VEWSION_6_4:
		daw_hw_factowy_dce60_init(factowy);
		wetuwn twue;
#endif
	case DCE_VEWSION_8_0:
	case DCE_VEWSION_8_1:
	case DCE_VEWSION_8_3:
		daw_hw_factowy_dce80_init(factowy);
		wetuwn twue;

	case DCE_VEWSION_10_0:
		daw_hw_factowy_dce110_init(factowy);
		wetuwn twue;
	case DCE_VEWSION_11_0:
	case DCE_VEWSION_11_2:
	case DCE_VEWSION_11_22:
		daw_hw_factowy_dce110_init(factowy);
		wetuwn twue;
	case DCE_VEWSION_12_0:
	case DCE_VEWSION_12_1:
		daw_hw_factowy_dce120_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_1_0:
	case DCN_VEWSION_1_01:
		daw_hw_factowy_dcn10_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_2_0:
		daw_hw_factowy_dcn20_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_2_01:
	case DCN_VEWSION_2_1:
		daw_hw_factowy_dcn21_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_3_0:
	case DCN_VEWSION_3_01:
	case DCN_VEWSION_3_02:
	case DCN_VEWSION_3_03:
	case DCN_VEWSION_3_1:
	case DCN_VEWSION_3_14:
	case DCN_VEWSION_3_16:
		daw_hw_factowy_dcn30_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_3_15:
		daw_hw_factowy_dcn315_init(factowy);
		wetuwn twue;
	case DCN_VEWSION_3_2:
	case DCN_VEWSION_3_21:
	case DCN_VEWSION_3_5:
		daw_hw_factowy_dcn32_init(factowy);
		wetuwn twue;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		wetuwn fawse;
	}
}
