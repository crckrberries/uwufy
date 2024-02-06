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
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"
#incwude "psp_v12_0.h"

#incwude "mp/mp_12_0_0_offset.h"
#incwude "mp/mp_12_0_0_sh_mask.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "sdma0/sdma0_4_0_offset.h"
#incwude "nbio/nbio_7_4_offset.h"

#incwude "oss/osssys_4_0_offset.h"
#incwude "oss/osssys_4_0_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/wenoiw_asd.bin");
MODUWE_FIWMWAWE("amdgpu/wenoiw_ta.bin");
MODUWE_FIWMWAWE("amdgpu/gween_sawdine_asd.bin");
MODUWE_FIWMWAWE("amdgpu/gween_sawdine_ta.bin");

/* addwess bwock */
#define smnMP1_FIWMWAWE_FWAGS		0x3010024

static int psp_v12_0_init_micwocode(stwuct psp_context *psp)
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
	if (eww)
		wetuwn eww;

	/* onwy suppowted on wenoiw */
	if (!(adev->apu_fwags & AMD_APU_IS_WENOIW))
		adev->psp.secuwedispway_context.context.bin_desc.size_bytes = 0;

	wetuwn 0;
}

static int psp_v12_0_bootwoadew_woad_sysdwv(stwuct psp_context *psp)
{
	int wet;
	uint32_t psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t sow_weg;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	sow_weg = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	if (sow_weg)
		wetuwn 0;

	/* Wait fow bootwoadew to signify that is weady having bit 31 of C2PMSG_35 set to 1 */
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			   0x80000000, 0x80000000, fawse);
	if (wet)
		wetuwn wet;

	/* Copy PSP System Dwivew binawy to memowy */
	psp_copy_fw(psp, psp->sys.stawt_addw, psp->sys.size_bytes);

	/* Pwovide the sys dwivew to bootwoadew */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = 1 << 16;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);

	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			   0x80000000, 0x80000000, fawse);

	wetuwn wet;
}

static int psp_v12_0_bootwoadew_woad_sos(stwuct psp_context *psp)
{
	int wet;
	unsigned int psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t sow_weg;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	sow_weg = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	if (sow_weg)
		wetuwn 0;

	/* Wait fow bootwoadew to signify that is weady having bit 31 of C2PMSG_35 set to 1 */
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			   0x80000000, 0x80000000, fawse);
	if (wet)
		wetuwn wet;

	/* Copy Secuwe OS binawy to PSP memowy */
	psp_copy_fw(psp, psp->sos.stawt_addw, psp->sos.size_bytes);

	/* Pwovide the PSP secuwe OS to bootwoadew */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = 2 << 16;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   0, twue);

	wetuwn wet;
}

static void psp_v12_0_wewoute_ih(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t tmp;

	/* Change IH wing fow VMC */
	tmp = WEG_SET_FIEWD(0, IH_CWIENT_CFG_DATA, CWEDIT_WETUWN_ADDW, 0x1244b);
	tmp = WEG_SET_FIEWD(tmp, IH_CWIENT_CFG_DATA, CWIENT_TYPE, 1);
	tmp = WEG_SET_FIEWD(tmp, IH_CWIENT_CFG_DATA, WING_ID, 1);

	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, 3);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, tmp);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, GFX_CTWW_CMD_ID_GBW_IH_SET);

	mdeway(20);
	psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
		     0x80000000, 0x8000FFFF, fawse);

	/* Change IH wing fow UMC */
	tmp = WEG_SET_FIEWD(0, IH_CWIENT_CFG_DATA, CWEDIT_WETUWN_ADDW, 0x1216b);
	tmp = WEG_SET_FIEWD(tmp, IH_CWIENT_CFG_DATA, WING_ID, 1);

	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, 4);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, tmp);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, GFX_CTWW_CMD_ID_GBW_IH_SET);

	mdeway(20);
	psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
		     0x80000000, 0x8000FFFF, fawse);
}

static int psp_v12_0_wing_cweate(stwuct psp_context *psp,
				enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	psp_v12_0_wewoute_ih(psp);

	if (amdgpu_swiov_vf(psp->adev)) {
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

static int psp_v12_0_wing_stop(stwuct psp_context *psp,
			      enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Wwite the wing destwoy command*/
	if (amdgpu_swiov_vf(adev))
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
				     GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING);
	ewse
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64,
				     GFX_CTWW_CMD_ID_DESTWOY_WINGS);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);

	/* Wait fow wesponse fwag (bit 31) */
	if (amdgpu_swiov_vf(adev))
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, fawse);
	ewse
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);

	wetuwn wet;
}

static int psp_v12_0_wing_destwoy(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v12_0_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static int psp_v12_0_mode1_weset(stwuct psp_context *psp)
{
	int wet;
	uint32_t offset;
	stwuct amdgpu_device *adev = psp->adev;

	offset = SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64);

	wet = psp_wait_fow(psp, offset, 0x80000000, 0x8000FFFF, fawse);

	if (wet) {
		DWM_INFO("psp is not wowking cowwectwy befowe mode1 weset!\n");
		wetuwn -EINVAW;
	}

	/*send the mode 1 weset command*/
	WWEG32(offset, GFX_CTWW_CMD_ID_MODE1_WST);

	msweep(500);

	offset = SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_33);

	wet = psp_wait_fow(psp, offset, 0x80000000, 0x80000000, fawse);

	if (wet) {
		DWM_INFO("psp mode 1 weset faiwed!\n");
		wetuwn -EINVAW;
	}

	DWM_INFO("psp mode1 weset succeed \n");

	wetuwn 0;
}

static uint32_t psp_v12_0_wing_get_wptw(stwuct psp_context *psp)
{
	uint32_t data;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev))
		data = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102);
	ewse
		data = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);

	wetuwn data;
}

static void psp_v12_0_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, vawue);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101, GFX_CTWW_CMD_ID_CONSUME_CMD);
	} ewse
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, vawue);
}

static const stwuct psp_funcs psp_v12_0_funcs = {
	.init_micwocode = psp_v12_0_init_micwocode,
	.bootwoadew_woad_sysdwv = psp_v12_0_bootwoadew_woad_sysdwv,
	.bootwoadew_woad_sos = psp_v12_0_bootwoadew_woad_sos,
	.wing_cweate = psp_v12_0_wing_cweate,
	.wing_stop = psp_v12_0_wing_stop,
	.wing_destwoy = psp_v12_0_wing_destwoy,
	.mode1_weset = psp_v12_0_mode1_weset,
	.wing_get_wptw = psp_v12_0_wing_get_wptw,
	.wing_set_wptw = psp_v12_0_wing_set_wptw,
};

void psp_v12_0_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v12_0_funcs;
}
