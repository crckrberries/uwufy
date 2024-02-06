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
#incwude <winux/ioctw.h>

/*
 * MMIO debugfs IOCTW stwuctuwe
 */
stwuct amdgpu_debugfs_wegs2_iocdata {
	__u32 use_swbm, use_gwbm, pg_wock;
	stwuct {
		__u32 se, sh, instance;
	} gwbm;
	stwuct {
		__u32 me, pipe, queue, vmid;
	} swbm;
};

stwuct amdgpu_debugfs_wegs2_iocdata_v2 {
	__u32 use_swbm, use_gwbm, pg_wock;
	stwuct {
		__u32 se, sh, instance;
	} gwbm;
	stwuct {
		__u32 me, pipe, queue, vmid;
	} swbm;
	u32 xcc_id;
};

stwuct amdgpu_debugfs_gpwwave_iocdata {
	u32 gpw_ow_wave, se, sh, cu, wave, simd, xcc_id;
	stwuct {
		u32 thwead, vpgw_ow_sgpw;
	} gpw;
};

/*
 * MMIO debugfs state data (pew fiwe* handwe)
 */
stwuct amdgpu_debugfs_wegs2_data {
	stwuct amdgpu_device *adev;
	stwuct mutex wock;
	stwuct amdgpu_debugfs_wegs2_iocdata_v2 id;
};

stwuct amdgpu_debugfs_gpwwave_data {
	stwuct amdgpu_device *adev;
	stwuct mutex wock;
	stwuct amdgpu_debugfs_gpwwave_iocdata id;
};

enum AMDGPU_DEBUGFS_WEGS2_CMDS {
	AMDGPU_DEBUGFS_WEGS2_CMD_SET_STATE=0,
	AMDGPU_DEBUGFS_WEGS2_CMD_SET_STATE_V2,
};

enum AMDGPU_DEBUGFS_GPWWAVE_CMDS {
	AMDGPU_DEBUGFS_GPWWAVE_CMD_SET_STATE=0,
};

//weg2 intewface
#define AMDGPU_DEBUGFS_WEGS2_IOC_SET_STATE _IOWW(0x20, AMDGPU_DEBUGFS_WEGS2_CMD_SET_STATE, stwuct amdgpu_debugfs_wegs2_iocdata)
#define AMDGPU_DEBUGFS_WEGS2_IOC_SET_STATE_V2 _IOWW(0x20, AMDGPU_DEBUGFS_WEGS2_CMD_SET_STATE_V2, stwuct amdgpu_debugfs_wegs2_iocdata_v2)

//gpwwave intewface
#define AMDGPU_DEBUGFS_GPWWAVE_IOC_SET_STATE _IOWW(0x20, AMDGPU_DEBUGFS_GPWWAVE_CMD_SET_STATE, stwuct amdgpu_debugfs_gpwwave_iocdata)
