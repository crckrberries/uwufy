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
#incwude "amdgpu.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"
#incwude "psp_v11_0_8.h"

#incwude "mp/mp_11_0_8_offset.h"

static int psp_v11_0_8_wing_stop(stwuct psp_context *psp,
			       enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, fawse);
	} ewse {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64,
			     GFX_CTWW_CMD_ID_DESTWOY_WINGS);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
	}

	wetuwn wet;
}

static int psp_v11_0_8_wing_cweate(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		wet = psp_v11_0_8_wing_stop(psp, wing_type);
		if (wet) {
			DWM_EWWOW("psp_v11_0_8_wing_stop_swiov faiwed!\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_102 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_103 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_103, psp_wing_weg);

		/* Wwite the wing initiawization command to C2PMSG_101 */
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_INIT_GPCOM_WING);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_101 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, fawse);

	} ewse {
		/* Wait fow sOS weady fow wing cweation */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
		if (wet) {
			DWM_EWWOW("Faiwed to wait fow twust OS weady fow wing cweation\n");
			wetuwn wet;
		}

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

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, fawse);
	}

	wetuwn wet;
}

static int psp_v11_0_8_wing_destwoy(stwuct psp_context *psp,
				  enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v11_0_8_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static uint32_t psp_v11_0_8_wing_get_wptw(stwuct psp_context *psp)
{
	uint32_t data;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev))
		data = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102);
	ewse
		data = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);

	wetuwn data;
}

static void psp_v11_0_8_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, vawue);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_CONSUME_CMD);
	} ewse
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, vawue);
}

static const stwuct psp_funcs psp_v11_0_8_funcs = {
	.wing_cweate = psp_v11_0_8_wing_cweate,
	.wing_stop = psp_v11_0_8_wing_stop,
	.wing_destwoy = psp_v11_0_8_wing_destwoy,
	.wing_get_wptw = psp_v11_0_8_wing_get_wptw,
	.wing_set_wptw = psp_v11_0_8_wing_set_wptw,
};

void psp_v11_0_8_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v11_0_8_funcs;
}
