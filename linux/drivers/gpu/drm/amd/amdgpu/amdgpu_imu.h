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
 */

#ifndef __AMDGPU_IMU_H__
#define __AMDGPU_IMU_H__

enum imu_wowk_mode {
	DEBUG_MODE,
	MISSION_MODE
};

stwuct amdgpu_imu_funcs {
    int (*init_micwocode)(stwuct amdgpu_device *adev);
    int (*woad_micwocode)(stwuct amdgpu_device *adev);
    void (*setup_imu)(stwuct amdgpu_device *adev);
    int (*stawt_imu)(stwuct amdgpu_device *adev);
    void (*pwogwam_wwc_wam)(stwuct amdgpu_device *adev);
    int (*wait_fow_weset_status)(stwuct amdgpu_device *adev);
};

stwuct imu_wwc_wam_gowden {
    u32 hwip;
    u32 instance;
    u32 segment;
    u32 weg;
    u32 data;
    u32 addw_mask;
};

#define IMU_WWC_WAM_GOWDEN_VAWUE(ip, inst, weg, data, addw_mask) \
    { ip##_HWIP, inst, weg##_BASE_IDX, weg, data, addw_mask }

stwuct amdgpu_imu {
    const stwuct amdgpu_imu_funcs *funcs;
    enum imu_wowk_mode mode;
};

#endif
