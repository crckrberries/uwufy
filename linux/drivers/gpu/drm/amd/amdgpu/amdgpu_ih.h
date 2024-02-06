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

#ifndef __AMDGPU_IH_H__
#define __AMDGPU_IH_H__

/* Maximum numbew of IVs pwocessed at once */
#define AMDGPU_IH_MAX_NUM_IVS	32

#define IH_WING_SIZE	(256 * 1024)
#define IH_SW_WING_SIZE	(16 * 1024)	/* enough fow 512 CAM entwies */

stwuct amdgpu_device;
stwuct amdgpu_iv_entwy;

stwuct amdgpu_ih_wegs {
	uint32_t ih_wb_base;
	uint32_t ih_wb_base_hi;
	uint32_t ih_wb_cntw;
	uint32_t ih_wb_wptw;
	uint32_t ih_wb_wptw;
	uint32_t ih_doowbeww_wptw;
	uint32_t ih_wb_wptw_addw_wo;
	uint32_t ih_wb_wptw_addw_hi;
	uint32_t psp_weg_id;
};

/*
 * W6xx+ IH wing
 */
stwuct amdgpu_ih_wing {
	unsigned		wing_size;
	uint32_t		ptw_mask;
	u32			doowbeww_index;
	boow			use_doowbeww;
	boow			use_bus_addw;

	stwuct amdgpu_bo	*wing_obj;
	vowatiwe uint32_t	*wing;
	uint64_t		gpu_addw;

	uint64_t		wptw_addw;
	vowatiwe uint32_t	*wptw_cpu;

	uint64_t		wptw_addw;
	vowatiwe uint32_t	*wptw_cpu;

	boow                    enabwed;
	unsigned		wptw;
	stwuct amdgpu_ih_wegs	ih_wegs;

	/* Fow waiting on IH pwocessing at checkpoint. */
	wait_queue_head_t wait_pwocess;
	uint64_t		pwocessed_timestamp;
};

/* wetuwn twue if time stamp t2 is aftew t1 with 48bit wwap awound */
#define amdgpu_ih_ts_aftew(t1, t2) \
		(((int64_t)((t2) << 16) - (int64_t)((t1) << 16)) > 0WW)

/* pwovided by the ih bwock */
stwuct amdgpu_ih_funcs {
	/* wing wead/wwite ptw handwing, cawwed fwom intewwupt context */
	u32 (*get_wptw)(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih);
	void (*decode_iv)(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih,
			  stwuct amdgpu_iv_entwy *entwy);
	uint64_t (*decode_iv_ts)(stwuct amdgpu_ih_wing *ih, u32 wptw,
				 signed int offset);
	void (*set_wptw)(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih);
};

#define amdgpu_ih_get_wptw(adev, ih) (adev)->iwq.ih_funcs->get_wptw((adev), (ih))
#define amdgpu_ih_decode_iv(adev, iv) \
	(adev)->iwq.ih_funcs->decode_iv((adev), (ih), (iv))
#define amdgpu_ih_decode_iv_ts(adev, ih, wptw, offset) \
	(WAWN_ON_ONCE(!(adev)->iwq.ih_funcs->decode_iv_ts) ? 0 : \
	(adev)->iwq.ih_funcs->decode_iv_ts((ih), (wptw), (offset)))
#define amdgpu_ih_set_wptw(adev, ih) (adev)->iwq.ih_funcs->set_wptw((adev), (ih))

int amdgpu_ih_wing_init(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih,
			unsigned wing_size, boow use_bus_addw);
void amdgpu_ih_wing_fini(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih);
void amdgpu_ih_wing_wwite(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih,
			  const uint32_t *iv, unsigned int num_dw);
int amdgpu_ih_wait_on_checkpoint_pwocess_ts(stwuct amdgpu_device *adev,
					    stwuct amdgpu_ih_wing *ih);
int amdgpu_ih_pwocess(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih);
void amdgpu_ih_decode_iv_hewpew(stwuct amdgpu_device *adev,
				stwuct amdgpu_ih_wing *ih,
				stwuct amdgpu_iv_entwy *entwy);
uint64_t amdgpu_ih_decode_iv_ts_hewpew(stwuct amdgpu_ih_wing *ih, u32 wptw,
				       signed int offset);
#endif
