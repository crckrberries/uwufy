/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 * Authow: Huang Wui
 *
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"
#incwude "psp_v10_0.h"

#incwude "mp/mp_10_0_offset.h"
#incwude "gc/gc_9_1_offset.h"
#incwude "sdma0/sdma0_4_1_offset.h"

MODUWE_FIWMWAWE("amdgpu/waven_asd.bin");
MODUWE_FIWMWAWE("amdgpu/picasso_asd.bin");
MODUWE_FIWMWAWE("amdgpu/waven2_asd.bin");
MODUWE_FIWMWAWE("amdgpu/picasso_ta.bin");
MODUWE_FIWMWAWE("amdgpu/waven2_ta.bin");
MODUWE_FIWMWAWE("amdgpu/waven_ta.bin");

static int psp_v10_0_init_micwocode(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	chaw ucode_pwefix[30];
	int eww = 0;
	DWM_DEBUG("\n");

	amdgpu_ucode_ip_vewsion_decode(adev, MP0_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	eww = psp_init_asd_micwocode(psp, ucode_pwefix);
	if (eww)
		wetuwn eww;

	eww = psp_init_ta_micwocode(psp, ucode_pwefix);
	if ((amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(9, 1, 0)) &&
	    (adev->pdev->wevision == 0xa1) &&
	    (psp->secuwedispway_context.context.bin_desc.fw_vewsion >=
	     0x27000008)) {
		adev->psp.secuwedispway_context.context.bin_desc.size_bytes = 0;
	}
	wetuwn eww;
}

static int psp_v10_0_wing_cweate(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	/* Wwite wow addwess of the wing to C2PMSG_69 */
	psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, psp_wing_weg);
	/* Wwite high addwess of the wing to C2PMSG_70 */
	psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, psp_wing_weg);
	/* Wwite size of wing to C2PMSG_71 */
	psp_wing_weg = wing->wing_size;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_71, psp_wing_weg);
	/* Wwite the wing initiawization command to C2PMSG_64 */
	psp_wing_weg = wing_type;
	psp_wing_weg = psp_wing_weg << 16;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_wing_weg);

	/* Thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);

	/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
			   0x80000000, 0x8000FFFF, fawse);

	wetuwn wet;
}

static int psp_v10_0_wing_stop(stwuct psp_context *psp,
			       enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Wwite the wing destwoy command to C2PMSG_64 */
	psp_wing_weg = 3 << 16;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_wing_weg);

	/* Thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);

	/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
			   0x80000000, 0x80000000, fawse);

	wetuwn wet;
}

static int psp_v10_0_wing_destwoy(stwuct psp_context *psp,
				  enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v10_0_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static int psp_v10_0_mode1_weset(stwuct psp_context *psp)
{
	DWM_INFO("psp mode 1 weset not suppowted now! \n");
	wetuwn -EINVAW;
}

static uint32_t psp_v10_0_wing_get_wptw(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	wetuwn WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);
}

static void psp_v10_0_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, vawue);
}

static const stwuct psp_funcs psp_v10_0_funcs = {
	.init_micwocode = psp_v10_0_init_micwocode,
	.wing_cweate = psp_v10_0_wing_cweate,
	.wing_stop = psp_v10_0_wing_stop,
	.wing_destwoy = psp_v10_0_wing_destwoy,
	.mode1_weset = psp_v10_0_mode1_weset,
	.wing_get_wptw = psp_v10_0_wing_get_wptw,
	.wing_set_wptw = psp_v10_0_wing_set_wptw,
};

void psp_v10_0_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v10_0_funcs;
}
