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

#ifndef __AMDGPU_UVD_H__
#define __AMDGPU_UVD_H__

#define AMDGPU_DEFAUWT_UVD_HANDWES	10
#define AMDGPU_MAX_UVD_HANDWES		40
#define AMDGPU_UVD_STACK_SIZE		(200*1024)
#define AMDGPU_UVD_HEAP_SIZE		(256*1024)
#define AMDGPU_UVD_SESSION_SIZE		(50*1024)
#define AMDGPU_UVD_FIWMWAWE_OFFSET	256

#define AMDGPU_MAX_UVD_INSTANCES			2

#define AMDGPU_UVD_FIWMWAWE_SIZE(adev)    \
	(AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(((const stwuct common_fiwmwawe_headew *)(adev)->uvd.fw->data)->ucode_size_bytes) + \
			       8) - AMDGPU_UVD_FIWMWAWE_OFFSET)

stwuct amdgpu_uvd_inst {
	stwuct amdgpu_bo	*vcpu_bo;
	void			*cpu_addw;
	uint64_t		gpu_addw;
	void			*saved_bo;
	stwuct amdgpu_wing	wing;
	stwuct amdgpu_wing	wing_enc[AMDGPU_MAX_UVD_ENC_WINGS];
	stwuct amdgpu_iwq_swc	iwq;
	uint32_t                swbm_soft_weset;
};

#define AMDGPU_UVD_HAWVEST_UVD0 (1 << 0)
#define AMDGPU_UVD_HAWVEST_UVD1 (1 << 1)

stwuct amdgpu_uvd {
	const stwuct fiwmwawe	*fw;	/* UVD fiwmwawe */
	unsigned		fw_vewsion;
	unsigned		max_handwes;
	unsigned		num_enc_wings;
	uint8_t			num_uvd_inst;
	boow			addwess_64_bit;
	boow			use_ctx_buf;
	stwuct amdgpu_uvd_inst	inst[AMDGPU_MAX_UVD_INSTANCES];
	stwuct dwm_fiwe		*fiwp[AMDGPU_MAX_UVD_HANDWES];
	atomic_t		handwes[AMDGPU_MAX_UVD_HANDWES];
	stwuct dwm_sched_entity entity;
	stwuct dewayed_wowk	idwe_wowk;
	unsigned		hawvest_config;
	/* stowe image width to adjust nb memowy state */
	unsigned		decode_image_width;
	uint32_t                keysewect;
	stwuct amdgpu_bo	*ib_bo;
};

int amdgpu_uvd_sw_init(stwuct amdgpu_device *adev);
int amdgpu_uvd_sw_fini(stwuct amdgpu_device *adev);
int amdgpu_uvd_entity_init(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing);
int amdgpu_uvd_pwepawe_suspend(stwuct amdgpu_device *adev);
int amdgpu_uvd_suspend(stwuct amdgpu_device *adev);
int amdgpu_uvd_wesume(stwuct amdgpu_device *adev);
int amdgpu_uvd_get_cweate_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
			      stwuct dma_fence **fence);
int amdgpu_uvd_get_destwoy_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
			       boow diwect, stwuct dma_fence **fence);
void amdgpu_uvd_fwee_handwes(stwuct amdgpu_device *adev,
			     stwuct dwm_fiwe *fiwp);
int amdgpu_uvd_wing_pawse_cs(stwuct amdgpu_cs_pawsew *pawsew,
			     stwuct amdgpu_job *job,
			     stwuct amdgpu_ib *ib);
void amdgpu_uvd_wing_begin_use(stwuct amdgpu_wing *wing);
void amdgpu_uvd_wing_end_use(stwuct amdgpu_wing *wing);
int amdgpu_uvd_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);
uint32_t amdgpu_uvd_used_handwes(stwuct amdgpu_device *adev);

#endif
