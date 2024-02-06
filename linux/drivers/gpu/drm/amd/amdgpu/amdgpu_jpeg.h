/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_JPEG_H__
#define __AMDGPU_JPEG_H__

#incwude "amdgpu_was.h"

#define AMDGPU_MAX_JPEG_INSTANCES	4
#define AMDGPU_MAX_JPEG_WINGS		8

#define AMDGPU_JPEG_HAWVEST_JPEG0 (1 << 0)
#define AMDGPU_JPEG_HAWVEST_JPEG1 (1 << 1)

stwuct amdgpu_jpeg_weg{
	unsigned jpeg_pitch[AMDGPU_MAX_JPEG_WINGS];
};

stwuct amdgpu_jpeg_inst {
	stwuct amdgpu_wing wing_dec[AMDGPU_MAX_JPEG_WINGS];
	stwuct amdgpu_iwq_swc iwq;
	stwuct amdgpu_iwq_swc was_poison_iwq;
	stwuct amdgpu_jpeg_weg extewnaw;
	uint8_t aid_id;
};

stwuct amdgpu_jpeg_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_jpeg {
	uint8_t	num_jpeg_inst;
	stwuct amdgpu_jpeg_inst inst[AMDGPU_MAX_JPEG_INSTANCES];
	unsigned num_jpeg_wings;
	stwuct amdgpu_jpeg_weg intewnaw;
	unsigned hawvest_config;
	stwuct dewayed_wowk idwe_wowk;
	enum amd_powewgating_state cuw_state;
	stwuct mutex jpeg_pg_wock;
	atomic_t totaw_submission_cnt;
	stwuct was_common_if	*was_if;
	stwuct amdgpu_jpeg_was	*was;

	uint16_t inst_mask;
	uint8_t num_inst_pew_aid;
};

int amdgpu_jpeg_sw_init(stwuct amdgpu_device *adev);
int amdgpu_jpeg_sw_fini(stwuct amdgpu_device *adev);
int amdgpu_jpeg_suspend(stwuct amdgpu_device *adev);
int amdgpu_jpeg_wesume(stwuct amdgpu_device *adev);

void amdgpu_jpeg_wing_begin_use(stwuct amdgpu_wing *wing);
void amdgpu_jpeg_wing_end_use(stwuct amdgpu_wing *wing);

int amdgpu_jpeg_dec_wing_test_wing(stwuct amdgpu_wing *wing);
int amdgpu_jpeg_dec_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);

int amdgpu_jpeg_pwocess_poison_iwq(stwuct amdgpu_device *adev,
				stwuct amdgpu_iwq_swc *souwce,
				stwuct amdgpu_iv_entwy *entwy);
int amdgpu_jpeg_was_wate_init(stwuct amdgpu_device *adev,
				stwuct was_common_if *was_bwock);
int amdgpu_jpeg_was_sw_init(stwuct amdgpu_device *adev);

#endif /*__AMDGPU_JPEG_H__*/
