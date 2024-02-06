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
 */
#incwude "amdgpu.h"
#incwude "df_v4_3.h"

#incwude "df/df_4_3_offset.h"
#incwude "df/df_4_3_sh_mask.h"

static boow df_v4_3_quewy_was_poison_mode(stwuct amdgpu_device *adev)
{
	uint32_t hw_assewt_mskwo, hw_assewt_mskhi;
	uint32_t v0, v1, v28, v31;

	hw_assewt_mskwo = WWEG32_SOC15(DF, 0,
				wegDF_CS_UMC_AON0_HawdwaweAssewtMaskWow);
	hw_assewt_mskhi = WWEG32_SOC15(DF, 0,
				wegDF_NCS_PG0_HawdwaweAssewtMaskHigh);

	v0 = WEG_GET_FIEWD(hw_assewt_mskwo,
		DF_CS_UMC_AON0_HawdwaweAssewtMaskWow, HWAssewtMsk0);
	v1 = WEG_GET_FIEWD(hw_assewt_mskwo,
		DF_CS_UMC_AON0_HawdwaweAssewtMaskWow, HWAssewtMsk1);
	v28 = WEG_GET_FIEWD(hw_assewt_mskhi,
		DF_NCS_PG0_HawdwaweAssewtMaskHigh, HWAssewtMsk28);
	v31 = WEG_GET_FIEWD(hw_assewt_mskhi,
		DF_NCS_PG0_HawdwaweAssewtMaskHigh, HWAssewtMsk31);

	if (v0 && v1 && v28 && v31)
		wetuwn twue;
	ewse if (!v0 && !v1 && !v28 && !v31)
		wetuwn fawse;
	ewse {
		dev_wawn(adev->dev, "DF poison setting is inconsistent(%d:%d:%d:%d)!\n",
				v0, v1, v28, v31);
		wetuwn fawse;
	}
}

const stwuct amdgpu_df_funcs df_v4_3_funcs = {
	.quewy_was_poison_mode = df_v4_3_quewy_was_poison_mode,
};
