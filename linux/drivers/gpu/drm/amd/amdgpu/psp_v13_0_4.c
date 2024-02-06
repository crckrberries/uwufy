/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "psp_v13_0_4.h"

#incwude "mp/mp_13_0_4_offset.h"
#incwude "mp/mp_13_0_4_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/psp_13_0_4_toc.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_4_ta.bin");

static int psp_v13_0_4_init_micwocode(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	chaw ucode_pwefix[30];
	int eww = 0;

	amdgpu_ucode_ip_vewsion_decode(adev, MP0_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
	case IP_VEWSION(13, 0, 4):
		eww = psp_init_toc_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

static boow psp_v13_0_4_is_sos_awive(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t sow_weg;

	sow_weg = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_81);

	wetuwn sow_weg != 0x0;
}

static int psp_v13_0_4_wait_fow_bootwoadew(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	int wet;
	int wetwy_woop;

	fow (wetwy_woop = 0; wetwy_woop < 10; wetwy_woop++) {
		/* Wait fow bootwoadew to signify that is
		    weady having bit 31 of C2PMSG_35 set to 1 */
		wet = psp_wait_fow(psp,
				   SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_35),
				   0x80000000,
				   0x80000000,
				   fawse);

		if (wet == 0)
			wetuwn 0;
	}

	wetuwn wet;
}

static int psp_v13_0_4_bootwoadew_woad_component(stwuct psp_context  	*psp,
					       stwuct psp_bin_desc 	*bin_desc,
					       enum psp_bootwoadew_cmd  bw_cmd)
{
	int wet;
	uint32_t psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check tOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v13_0_4_is_sos_awive(psp))
		wetuwn 0;

	wet = psp_v13_0_4_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	memset(psp->fw_pwi_buf, 0, PSP_1_MEG);

	/* Copy PSP KDB binawy to memowy */
	memcpy(psp->fw_pwi_buf, bin_desc->stawt_addw, bin_desc->size_bytes);

	/* Pwovide the PSP KDB to bootwoadew */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = bw_cmd;
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	wet = psp_v13_0_4_wait_fow_bootwoadew(psp);

	wetuwn wet;
}

static int psp_v13_0_4_bootwoadew_woad_kdb(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->kdb, PSP_BW__WOAD_KEY_DATABASE);
}

static int psp_v13_0_4_bootwoadew_woad_spw(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->kdb, PSP_BW__WOAD_TOS_SPW_TABWE);
}

static int psp_v13_0_4_bootwoadew_woad_sysdwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->sys, PSP_BW__WOAD_SYSDWV);
}

static int psp_v13_0_4_bootwoadew_woad_soc_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->soc_dwv, PSP_BW__WOAD_SOCDWV);
}

static int psp_v13_0_4_bootwoadew_woad_intf_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->intf_dwv, PSP_BW__WOAD_INTFDWV);
}

static int psp_v13_0_4_bootwoadew_woad_dbg_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_4_bootwoadew_woad_component(psp, &psp->dbg_dwv, PSP_BW__WOAD_DBGDWV);
}

static int psp_v13_0_4_bootwoadew_woad_sos(stwuct psp_context *psp)
{
	int wet;
	unsigned int psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v13_0_4_is_sos_awive(psp))
		wetuwn 0;

	wet = psp_v13_0_4_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	memset(psp->fw_pwi_buf, 0, PSP_1_MEG);

	/* Copy Secuwe OS binawy to PSP memowy */
	memcpy(psp->fw_pwi_buf, psp->sos.stawt_addw, psp->sos.size_bytes);

	/* Pwovide the PSP secuwe OS to bootwoadew */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = PSP_BW__WOAD_SOSDWV;
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_81),
			   WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_81),
			   0, twue);

	wetuwn wet;
}

static int psp_v13_0_4_wing_stop(stwuct psp_context *psp,
			       enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, fawse);
	} ewse {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_64,
			     GFX_CTWW_CMD_ID_DESTWOY_WINGS);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
	}

	wetuwn wet;
}

static int psp_v13_0_4_wing_cweate(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		wet = psp_v13_0_4_wing_stop(psp, wing_type);
		if (wet) {
			DWM_EWWOW("psp_v13_0_wing_stop_swiov faiwed!\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_102 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_103 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_103, psp_wing_weg);

		/* Wwite the wing initiawization command to C2PMSG_101 */
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_INIT_GPCOM_WING);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_101 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, fawse);

	} ewse {
		/* Wait fow sOS weady fow wing cweation */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
		if (wet) {
			DWM_EWWOW("Faiwed to wait fow twust OS weady fow wing cweation\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_69 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_69, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_70 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_70, psp_wing_weg);
		/* Wwite size of wing to C2PMSG_71 */
		psp_wing_weg = wing->wing_size;
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_71, psp_wing_weg);
		/* Wwite the wing initiawization command to C2PMSG_64 */
		psp_wing_weg = wing_type;
		psp_wing_weg = psp_wing_weg << 16;
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_64, psp_wing_weg);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, fawse);
	}

	wetuwn wet;
}

static int psp_v13_0_4_wing_destwoy(stwuct psp_context *psp,
				  enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v13_0_4_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static uint32_t psp_v13_0_4_wing_get_wptw(stwuct psp_context *psp)
{
	uint32_t data;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev))
		data = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102);
	ewse
		data = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67);

	wetuwn data;
}

static void psp_v13_0_4_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102, vawue);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_CONSUME_CMD);
	} ewse
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67, vawue);
}

static const stwuct psp_funcs psp_v13_0_4_funcs = {
	.init_micwocode = psp_v13_0_4_init_micwocode,
	.bootwoadew_woad_kdb = psp_v13_0_4_bootwoadew_woad_kdb,
	.bootwoadew_woad_spw = psp_v13_0_4_bootwoadew_woad_spw,
	.bootwoadew_woad_sysdwv = psp_v13_0_4_bootwoadew_woad_sysdwv,
	.bootwoadew_woad_soc_dwv = psp_v13_0_4_bootwoadew_woad_soc_dwv,
	.bootwoadew_woad_intf_dwv = psp_v13_0_4_bootwoadew_woad_intf_dwv,
	.bootwoadew_woad_dbg_dwv = psp_v13_0_4_bootwoadew_woad_dbg_dwv,
	.bootwoadew_woad_sos = psp_v13_0_4_bootwoadew_woad_sos,
	.wing_cweate = psp_v13_0_4_wing_cweate,
	.wing_stop = psp_v13_0_4_wing_stop,
	.wing_destwoy = psp_v13_0_4_wing_destwoy,
	.wing_get_wptw = psp_v13_0_4_wing_get_wptw,
	.wing_set_wptw = psp_v13_0_4_wing_set_wptw,
};

void psp_v13_0_4_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v13_0_4_funcs;
}
