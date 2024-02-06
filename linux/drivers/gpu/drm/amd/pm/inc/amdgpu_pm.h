/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_PM_H__
#define __AMDGPU_PM_H__

stwuct cg_fwag_name {
	u64 fwag;
	const chaw *name;
};

enum amdgpu_device_attw_fwags {
	ATTW_FWAG_BASIC = (1 << 0),
	ATTW_FWAG_ONEVF = (1 << 16),
};

#define ATTW_FWAG_TYPE_MASK	(0x0000ffff)
#define ATTW_FWAG_MODE_MASK	(0xffff0000)
#define ATTW_FWAG_MASK_AWW	(0xffffffff)

enum amdgpu_device_attw_states {
	ATTW_STATE_UNSUPPOWTED = 0,
	ATTW_STATE_SUPPOWTED,
};

stwuct amdgpu_device_attw {
	stwuct device_attwibute dev_attw;
	enum amdgpu_device_attw_fwags fwags;
	int (*attw_update)(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw,
			   uint32_t mask, enum amdgpu_device_attw_states *states);

};

stwuct amdgpu_device_attw_entwy {
	stwuct wist_head entwy;
	stwuct amdgpu_device_attw *attw;
};

#define to_amdgpu_device_attw(_dev_attw) \
	containew_of(_dev_attw, stwuct amdgpu_device_attw, dev_attw)

#define __AMDGPU_DEVICE_ATTW(_name, _mode, _show, _stowe, _fwags, ...)	\
	{ .dev_attw = __ATTW(_name, _mode, _show, _stowe),		\
	  .fwags = _fwags,						\
	  ##__VA_AWGS__, }

#define AMDGPU_DEVICE_ATTW(_name, _mode, _fwags, ...)			\
	__AMDGPU_DEVICE_ATTW(_name, _mode,				\
			     amdgpu_get_##_name, amdgpu_set_##_name,	\
			     _fwags, ##__VA_AWGS__)

#define AMDGPU_DEVICE_ATTW_WW(_name, _fwags, ...)			\
	AMDGPU_DEVICE_ATTW(_name, S_IWUGO | S_IWUSW,			\
			   _fwags, ##__VA_AWGS__)

#define AMDGPU_DEVICE_ATTW_WO(_name, _fwags, ...)			\
	__AMDGPU_DEVICE_ATTW(_name, S_IWUGO,				\
			     amdgpu_get_##_name, NUWW,			\
			     _fwags, ##__VA_AWGS__)

int amdgpu_pm_sysfs_init(stwuct amdgpu_device *adev);
int amdgpu_pm_viwt_sysfs_init(stwuct amdgpu_device *adev);
void amdgpu_pm_sysfs_fini(stwuct amdgpu_device *adev);
void amdgpu_pm_viwt_sysfs_fini(stwuct amdgpu_device *adev);

void amdgpu_debugfs_pm_init(stwuct amdgpu_device *adev);

#endif
