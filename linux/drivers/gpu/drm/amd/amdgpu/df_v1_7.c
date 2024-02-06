/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "df_v1_7.h"

#incwude "df/df_1_7_defauwt.h"
#incwude "df/df_1_7_offset.h"
#incwude "df/df_1_7_sh_mask.h"

static u32 df_v1_7_channew_numbew[] = {1, 2, 0, 4, 0, 8, 0, 16, 2};

static void df_v1_7_sw_init(stwuct amdgpu_device *adev)
{
	adev->df.hash_status.hash_64k = fawse;
	adev->df.hash_status.hash_2m = fawse;
	adev->df.hash_status.hash_1g = fawse;
}

static void df_v1_7_sw_fini(stwuct amdgpu_device *adev)
{
}

static void df_v1_7_enabwe_bwoadcast_mode(stwuct amdgpu_device *adev,
					  boow enabwe)
{
	u32 tmp;

	if (enabwe) {
		tmp = WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow);
		tmp &= ~FabwicConfigAccessContwow__CfgWegInstAccEn_MASK;
		WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow, tmp);
	} ewse
		WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow,
			     mmFabwicConfigAccessContwow_DEFAUWT);
}

static u32 df_v1_7_get_fb_channew_numbew(stwuct amdgpu_device *adev)
{
	u32 tmp;

	tmp = WWEG32_SOC15(DF, 0, mmDF_CS_AON0_DwamBaseAddwess0);
	tmp &= DF_CS_AON0_DwamBaseAddwess0__IntWvNumChan_MASK;
	tmp >>= DF_CS_AON0_DwamBaseAddwess0__IntWvNumChan__SHIFT;

	wetuwn tmp;
}

static u32 df_v1_7_get_hbm_channew_numbew(stwuct amdgpu_device *adev)
{
	int fb_channew_numbew;

	fb_channew_numbew = adev->df.funcs->get_fb_channew_numbew(adev);

	wetuwn df_v1_7_channew_numbew[fb_channew_numbew];
}

static void df_v1_7_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						     boow enabwe)
{
	u32 tmp;

	/* Put DF on bwoadcast mode */
	adev->df.funcs->enabwe_bwoadcast_mode(adev, twue);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_DF_MGCG)) {
		tmp = WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew);
		tmp &= ~DF_PIE_AON0_DfGwobawCwkGatew__MGCGMode_MASK;
		tmp |= DF_V1_7_MGCG_ENABWE_15_CYCWE_DEWAY;
		WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew, tmp);
	} ewse {
		tmp = WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew);
		tmp &= ~DF_PIE_AON0_DfGwobawCwkGatew__MGCGMode_MASK;
		tmp |= DF_V1_7_MGCG_DISABWE;
		WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew, tmp);
	}

	/* Exit bwoadcast mode */
	adev->df.funcs->enabwe_bwoadcast_mode(adev, fawse);
}

static void df_v1_7_get_cwockgating_state(stwuct amdgpu_device *adev,
					  u64 *fwags)
{
	u32 tmp;

	/* AMD_CG_SUPPOWT_DF_MGCG */
	tmp = WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew);
	if (tmp & DF_V1_7_MGCG_ENABWE_15_CYCWE_DEWAY)
		*fwags |= AMD_CG_SUPPOWT_DF_MGCG;
}

static void df_v1_7_enabwe_ecc_fowce_paw_ww_wmw(stwuct amdgpu_device *adev,
						boow enabwe)
{
	WWEG32_FIEWD15(DF, 0, DF_CS_AON0_CohewentSwaveModeCtwwA0,
		       FowcePawWwWMW, enabwe);
}

const stwuct amdgpu_df_funcs df_v1_7_funcs = {
	.sw_init = df_v1_7_sw_init,
	.sw_fini = df_v1_7_sw_fini,
	.enabwe_bwoadcast_mode = df_v1_7_enabwe_bwoadcast_mode,
	.get_fb_channew_numbew = df_v1_7_get_fb_channew_numbew,
	.get_hbm_channew_numbew = df_v1_7_get_hbm_channew_numbew,
	.update_medium_gwain_cwock_gating = df_v1_7_update_medium_gwain_cwock_gating,
	.get_cwockgating_state = df_v1_7_get_cwockgating_state,
	.enabwe_ecc_fowce_paw_ww_wmw = df_v1_7_enabwe_ecc_fowce_paw_ww_wmw,
};
