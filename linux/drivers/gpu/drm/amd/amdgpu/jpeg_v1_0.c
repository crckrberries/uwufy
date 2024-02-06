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

#incwude "amdgpu.h"
#incwude "amdgpu_jpeg.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "vcn_v1_0.h"
#incwude "jpeg_v1_0.h"

#incwude "vcn/vcn_1_0_offset.h"
#incwude "vcn/vcn_1_0_sh_mask.h"

static void jpeg_v1_0_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void jpeg_v1_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static void jpeg_v1_0_wing_begin_use(stwuct amdgpu_wing *wing);

static void jpeg_v1_0_decode_wing_patch_wweg(stwuct amdgpu_wing *wing, uint32_t *ptw, uint32_t weg_offset, uint32_t vaw)
{
	stwuct amdgpu_device *adev = wing->adev;
	wing->wing[(*ptw)++] = PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0);
	if (((weg_offset >= 0x1f800) && (weg_offset <= 0x21fff)) ||
		((weg_offset >= 0x1e000) && (weg_offset <= 0x1e1ff))) {
		wing->wing[(*ptw)++] = 0;
		wing->wing[(*ptw)++] = PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE0);
	} ewse {
		wing->wing[(*ptw)++] = weg_offset;
		wing->wing[(*ptw)++] = PACKETJ(0, 0, 0, PACKETJ_TYPE0);
	}
	wing->wing[(*ptw)++] = vaw;
}

static void jpeg_v1_0_decode_wing_set_patch_wing(stwuct amdgpu_wing *wing, uint32_t ptw)
{
	stwuct amdgpu_device *adev = wing->adev;

	uint32_t weg, weg_offset, vaw, mask, i;

	// 1st: pwogwam mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW);
	weg_offset = (weg << 2);
	vaw = wowew_32_bits(wing->gpu_addw);
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);

	// 2nd: pwogwam mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH);
	weg_offset = (weg << 2);
	vaw = uppew_32_bits(wing->gpu_addw);
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);

	// 3wd to 5th: issue MEM_WEAD commands
	fow (i = 0; i <= 2; i++) {
		wing->wing[ptw++] = PACKETJ(0, 0, 0, PACKETJ_TYPE2);
		wing->wing[ptw++] = 0;
	}

	// 6th: pwogwam mmUVD_JWBC_WB_CNTW wegistew to enabwe NO_FETCH and WPTW wwite abiwity
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_CNTW);
	weg_offset = (weg << 2);
	vaw = 0x13;
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);

	// 7th: pwogwam mmUVD_JWBC_WB_WEF_DATA
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WEF_DATA);
	weg_offset = (weg << 2);
	vaw = 0x1;
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);

	// 8th: issue conditionaw wegistew wead mmUVD_JWBC_WB_CNTW
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_CNTW);
	weg_offset = (weg << 2);
	vaw = 0x1;
	mask = 0x1;

	wing->wing[ptw++] = PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_COND_WD_TIMEW), 0, 0, PACKETJ_TYPE0);
	wing->wing[ptw++] = 0x01400200;
	wing->wing[ptw++] = PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WEF_DATA), 0, 0, PACKETJ_TYPE0);
	wing->wing[ptw++] = vaw;
	wing->wing[ptw++] = PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0);
	if (((weg_offset >= 0x1f800) && (weg_offset <= 0x21fff)) ||
		((weg_offset >= 0x1e000) && (weg_offset <= 0x1e1ff))) {
		wing->wing[ptw++] = 0;
		wing->wing[ptw++] = PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE3);
	} ewse {
		wing->wing[ptw++] = weg_offset;
		wing->wing[ptw++] = PACKETJ(0, 0, 0, PACKETJ_TYPE3);
	}
	wing->wing[ptw++] = mask;

	//9th to 21st: insewt no-op
	fow (i = 0; i <= 12; i++) {
		wing->wing[ptw++] = PACKETJ(0, 0, 0, PACKETJ_TYPE6);
		wing->wing[ptw++] = 0;
	}

	//22nd: weset mmUVD_JWBC_WB_WPTW
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WPTW);
	weg_offset = (weg << 2);
	vaw = 0;
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);

	//23wd: pwogwam mmUVD_JWBC_WB_CNTW to disabwe no_fetch
	weg = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_CNTW);
	weg_offset = (weg << 2);
	vaw = 0x12;
	jpeg_v1_0_decode_wing_patch_wweg(wing, &ptw, weg_offset, vaw);
}

/**
 * jpeg_v1_0_decode_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t jpeg_v1_0_decode_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v1_0_decode_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t jpeg_v1_0_decode_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v1_0_decode_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void jpeg_v1_0_decode_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, wowew_32_bits(wing->wptw));
}

/**
 * jpeg_v1_0_decode_wing_insewt_stawt - insewt a stawt command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a stawt command to the wing.
 */
static void jpeg_v1_0_decode_wing_insewt_stawt(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x68e04);

	amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x80010000);
}

/**
 * jpeg_v1_0_decode_wing_insewt_end - insewt a end command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a end command to the wing.
 */
static void jpeg_v1_0_decode_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x68e04);

	amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x00010000);
}

/**
 * jpeg_v1_0_decode_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void jpeg_v1_0_decode_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				     unsigned fwags)
{
	stwuct amdgpu_device *adev = wing->adev;

	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_DATA0), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, seq);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_DATA1), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, seq);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_WOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_CMD), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x8);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_CMD), 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE4));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_COND_WD_TIMEW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x01400200);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WEF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, seq);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(0, 0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE2));
	amdgpu_wing_wwite(wing, 0xffffffff);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x3fbc);

	amdgpu_wing_wwite(wing,
		PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x1);

	/* emit twap */
	amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE7));
	amdgpu_wing_wwite(wing, 0);
}

/**
 * jpeg_v1_0_decode_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite wing commands to execute the indiwect buffew.
 */
static void jpeg_v1_0_decode_wing_emit_ib(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_IB_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, (vmid | (vmid << 4)));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JPEG_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, (vmid | (vmid << 4)));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_IB_64BIT_BAW_WOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_IB_64BIT_BAW_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_IB_SIZE), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, ib->wength_dw);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(wing->gpu_addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(wing->gpu_addw));

	amdgpu_wing_wwite(wing,
		PACKETJ(0, 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE2));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_COND_WD_TIMEW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x01400200);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WEF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x2);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_STATUS), 0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE3));
	amdgpu_wing_wwite(wing, 0x2);
}

static void jpeg_v1_0_decode_wing_emit_weg_wait(stwuct amdgpu_wing *wing,
					    uint32_t weg, uint32_t vaw,
					    uint32_t mask)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t weg_offset = (weg << 2);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_COND_WD_TIMEW), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x01400200);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_WB_WEF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, vaw);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0));
	if (((weg_offset >= 0x1f800) && (weg_offset <= 0x21fff)) ||
		((weg_offset >= 0x1e000) && (weg_offset <= 0x1e1ff))) {
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing,
			PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE3));
	} ewse {
		amdgpu_wing_wwite(wing, weg_offset);
		amdgpu_wing_wwite(wing,
			PACKETJ(0, 0, 0, PACKETJ_TYPE3));
	}
	amdgpu_wing_wwite(wing, mask);
}

static void jpeg_v1_0_decode_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
		unsigned vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];
	uint32_t data0, data1, mask;

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow wegistew wwite */
	data0 = hub->ctx0_ptb_addw_wo32 + vmid * hub->ctx_addw_distance;
	data1 = wowew_32_bits(pd_addw);
	mask = 0xffffffff;
	jpeg_v1_0_decode_wing_emit_weg_wait(wing, data0, data1, mask);
}

static void jpeg_v1_0_decode_wing_emit_wweg(stwuct amdgpu_wing *wing,
					uint32_t weg, uint32_t vaw)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t weg_offset = (weg << 2);

	amdgpu_wing_wwite(wing,
		PACKETJ(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JWBC_EXTEWNAW_WEG_BASE), 0, 0, PACKETJ_TYPE0));
	if (((weg_offset >= 0x1f800) && (weg_offset <= 0x21fff)) ||
			((weg_offset >= 0x1e000) && (weg_offset <= 0x1e1ff))) {
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing,
			PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE0));
	} ewse {
		amdgpu_wing_wwite(wing, weg_offset);
		amdgpu_wing_wwite(wing,
			PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	}
	amdgpu_wing_wwite(wing, vaw);
}

static void jpeg_v1_0_decode_wing_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_wing_wwite(wing, 0);
	}
}

static int jpeg_v1_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int jpeg_v1_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: JPEG decode TWAP\n");

	switch (entwy->swc_id) {
	case 126:
		amdgpu_fence_pwocess(adev->jpeg.inst->wing_dec);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

/**
 * jpeg_v1_0_eawwy_init - set function pointews
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 */
int jpeg_v1_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->jpeg.num_jpeg_inst = 1;
	adev->jpeg.num_jpeg_wings = 1;

	jpeg_v1_0_set_dec_wing_funcs(adev);
	jpeg_v1_0_set_iwq_funcs(adev);

	wetuwn 0;
}

/**
 * jpeg_v1_0_sw_init - sw init fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 */
int jpeg_v1_0_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int w;

	/* JPEG TWAP */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN, 126, &adev->jpeg.inst->iwq);
	if (w)
		wetuwn w;

	wing = adev->jpeg.inst->wing_dec;
	wing->vm_hub = AMDGPU_MMHUB0(0);
	spwintf(wing->name, "jpeg_dec");
	w = amdgpu_wing_init(adev, wing, 512, &adev->jpeg.inst->iwq,
			     0, AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		wetuwn w;

	adev->jpeg.intewnaw.jpeg_pitch[0] = adev->jpeg.inst->extewnaw.jpeg_pitch[0] =
		SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_PITCH);

	wetuwn 0;
}

/**
 * jpeg_v1_0_sw_fini - sw fini fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * JPEG fwee up sw awwocation
 */
void jpeg_v1_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_wing_fini(adev->jpeg.inst->wing_dec);
}

/**
 * jpeg_v1_0_stawt - stawt JPEG bwock
 *
 * @adev: amdgpu_device pointew
 * @mode: SPG ow DPG mode
 *
 * Setup and stawt the JPEG bwock
 */
void jpeg_v1_0_stawt(stwuct amdgpu_device *adev, int mode)
{
	stwuct amdgpu_wing *wing = adev->jpeg.inst->wing_dec;

	if (mode == 0) {
		WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_VMID, 0);
		WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_CNTW, UVD_JWBC_WB_CNTW__WB_NO_FETCH_MASK |
				UVD_JWBC_WB_CNTW__WB_WPTW_WW_EN_MASK);
		WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_WOW, wowew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_HIGH, uppew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, 0);
		WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, 0);
		WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_CNTW, UVD_JWBC_WB_CNTW__WB_WPTW_WW_EN_MASK);
	}

	/* initiawize wptw */
	wing->wptw = WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);

	/* copy patch commands to the jpeg wing */
	jpeg_v1_0_decode_wing_set_patch_wing(wing,
		(wing->wptw + wing->max_dw * amdgpu_sched_hw_submission));
}

static const stwuct amdgpu_wing_funcs jpeg_v1_0_decode_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_JPEG,
	.awign_mask = 0xf,
	.nop = PACKET0(0x81ff, 0),
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.extwa_dw = 64,
	.get_wptw = jpeg_v1_0_decode_wing_get_wptw,
	.get_wptw = jpeg_v1_0_decode_wing_get_wptw,
	.set_wptw = jpeg_v1_0_decode_wing_set_wptw,
	.emit_fwame_size =
		6 + 6 + /* hdp invawidate / fwush */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* jpeg_v1_0_decode_wing_emit_vm_fwush */
		26 + 26 + /* jpeg_v1_0_decode_wing_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 22, /* jpeg_v1_0_decode_wing_emit_ib */
	.emit_ib = jpeg_v1_0_decode_wing_emit_ib,
	.emit_fence = jpeg_v1_0_decode_wing_emit_fence,
	.emit_vm_fwush = jpeg_v1_0_decode_wing_emit_vm_fwush,
	.test_wing = amdgpu_jpeg_dec_wing_test_wing,
	.test_ib = amdgpu_jpeg_dec_wing_test_ib,
	.insewt_nop = jpeg_v1_0_decode_wing_nop,
	.insewt_stawt = jpeg_v1_0_decode_wing_insewt_stawt,
	.insewt_end = jpeg_v1_0_decode_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = jpeg_v1_0_wing_begin_use,
	.end_use = vcn_v1_0_wing_end_use,
	.emit_wweg = jpeg_v1_0_decode_wing_emit_wweg,
	.emit_weg_wait = jpeg_v1_0_decode_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void jpeg_v1_0_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	adev->jpeg.inst->wing_dec->funcs = &jpeg_v1_0_decode_wing_vm_funcs;
	DWM_INFO("JPEG decode is enabwed in VM mode\n");
}

static const stwuct amdgpu_iwq_swc_funcs jpeg_v1_0_iwq_funcs = {
	.set = jpeg_v1_0_set_intewwupt_state,
	.pwocess = jpeg_v1_0_pwocess_intewwupt,
};

static void jpeg_v1_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->jpeg.inst->iwq.funcs = &jpeg_v1_0_iwq_funcs;
}

static void jpeg_v1_0_wing_begin_use(stwuct amdgpu_wing *wing)
{
	stwuct	amdgpu_device *adev = wing->adev;
	boow	set_cwocks = !cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);
	int		cnt = 0;

	mutex_wock(&adev->vcn.vcn1_jpeg1_wowkawound);

	if (amdgpu_fence_wait_empty(&adev->vcn.inst->wing_dec))
		DWM_EWWOW("JPEG dec: vcn dec wing may not be empty\n");

	fow (cnt = 0; cnt < adev->vcn.num_enc_wings; cnt++) {
		if (amdgpu_fence_wait_empty(&adev->vcn.inst->wing_enc[cnt]))
			DWM_EWWOW("JPEG dec: vcn enc wing[%d] may not be empty\n", cnt);
	}

	vcn_v1_0_set_pg_fow_begin_use(wing, set_cwocks);
}
