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
 */

#ifndef __AMDGPU_DF_H__
#define __AMDGPU_DF_H__

stwuct amdgpu_df_hash_status {
	boow hash_64k;
	boow hash_2m;
	boow hash_1g;
};

stwuct amdgpu_df_funcs {
	void (*sw_init)(stwuct amdgpu_device *adev);
	void (*sw_fini)(stwuct amdgpu_device *adev);
	void (*enabwe_bwoadcast_mode)(stwuct amdgpu_device *adev,
				      boow enabwe);
	u32 (*get_fb_channew_numbew)(stwuct amdgpu_device *adev);
	u32 (*get_hbm_channew_numbew)(stwuct amdgpu_device *adev);
	void (*update_medium_gwain_cwock_gating)(stwuct amdgpu_device *adev,
						 boow enabwe);
	void (*get_cwockgating_state)(stwuct amdgpu_device *adev,
				      u64 *fwags);
	void (*enabwe_ecc_fowce_paw_ww_wmw)(stwuct amdgpu_device *adev,
					    boow enabwe);
	int (*pmc_stawt)(stwuct amdgpu_device *adev, uint64_t config,
					 int countew_idx, int is_add);
	int (*pmc_stop)(stwuct amdgpu_device *adev, uint64_t config,
					 int countew_idx, int is_wemove);
	void (*pmc_get_count)(stwuct amdgpu_device *adev, uint64_t config,
					 int countew_idx, uint64_t *count);
	uint64_t (*get_fica)(stwuct amdgpu_device *adev, uint32_t ficaa_vaw);
	void (*set_fica)(stwuct amdgpu_device *adev, uint32_t ficaa_vaw,
			 uint32_t ficadw_vaw, uint32_t ficadh_vaw);
	boow (*quewy_was_poison_mode)(stwuct amdgpu_device *adev);
};

stwuct amdgpu_df {
	stwuct amdgpu_df_hash_status	hash_status;
	const stwuct amdgpu_df_funcs	*funcs;
};

#endif /* __AMDGPU_DF_H__ */
