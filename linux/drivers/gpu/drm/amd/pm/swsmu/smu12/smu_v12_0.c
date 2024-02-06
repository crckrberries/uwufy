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

#define SWSMU_CODE_WAYEW_W3

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v12_0.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "smu_cmn.h"

#incwude "asic_weg/mp/mp_12_0_0_offset.h"
#incwude "asic_weg/mp/mp_12_0_0_sh_mask.h"
#incwude "asic_weg/smuio/smuio_12_0_0_offset.h"
#incwude "asic_weg/smuio/smuio_12_0_0_sh_mask.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

// because some SMU12 based ASICs use owdew ip offset tabwes
// we shouwd undefine this wegistew fwom the smuio12 headew
// to pwevent confusion down the woad
#undef mmPWW_MISC_CNTW_STATUS

#define smnMP1_FIWMWAWE_FWAGS                                0x3010024

int smu_v12_0_check_fw_status(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
		(smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if ((mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
		MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
		wetuwn 0;

	wetuwn -EIO;
}

int smu_v12_0_check_fw_vewsion(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t if_vewsion = 0xff, smu_vewsion = 0xff;
	uint8_t smu_pwogwam, smu_majow, smu_minow, smu_debug;
	int wet = 0;

	wet = smu_cmn_get_smc_vewsion(smu, &if_vewsion, &smu_vewsion);
	if (wet)
		wetuwn wet;

	smu_pwogwam = (smu_vewsion >> 24) & 0xff;
	smu_majow = (smu_vewsion >> 16) & 0xff;
	smu_minow = (smu_vewsion >> 8) & 0xff;
	smu_debug = (smu_vewsion >> 0) & 0xff;
	if (smu->is_apu)
		adev->pm.fw_vewsion = smu_vewsion;

	/*
	 * 1. if_vewsion mismatch is not cwiticaw as ouw fw is designed
	 * to be backwawd compatibwe.
	 * 2. New fw usuawwy bwings some optimizations. But that's visibwe
	 * onwy on the paiwed dwivew.
	 * Considewing above, we just weave usew a vewbaw message instead
	 * of hawt dwivew woading.
	 */
	if (if_vewsion != smu->smc_dwivew_if_vewsion) {
		dev_info(smu->adev->dev, "smu dwivew if vewsion = 0x%08x, smu fw if vewsion = 0x%08x, "
			"smu fw pwogwam = %d, smu fw vewsion = 0x%08x (%d.%d.%d)\n",
			smu->smc_dwivew_if_vewsion, if_vewsion,
			smu_pwogwam, smu_vewsion, smu_majow, smu_minow, smu_debug);
		dev_info(smu->adev->dev, "SMU dwivew if vewsion not matched\n");
	}

	wetuwn wet;
}

int smu_v12_0_powewgate_sdma(stwuct smu_context *smu, boow gate)
{
	if (!smu->is_apu)
		wetuwn 0;

	if (gate)
		wetuwn smu_cmn_send_smc_msg(smu, SMU_MSG_PowewDownSdma, NUWW);
	ewse
		wetuwn smu_cmn_send_smc_msg(smu, SMU_MSG_PowewUpSdma, NUWW);
}

int smu_v12_0_set_gfx_cgpg(stwuct smu_context *smu, boow enabwe)
{
	/* Untiw now the SMU12 onwy impwemented fow Wenoiw sewies so hewe neen't do APU check. */
	if (!(smu->adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG) || smu->adev->in_s0ix)
		wetuwn 0;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
		SMU_MSG_SetGfxCGPG,
		enabwe ? 1 : 0,
		NUWW);
}

/**
 * smu_v12_0_get_gfxoff_status - get gfxoff status
 *
 * @smu: amdgpu_device pointew
 *
 * This function wiww be used to get gfxoff status
 *
 * Wetuwns 0=GFXOFF(defauwt).
 * Wetuwns 1=Twansition out of GFX State.
 * Wetuwns 2=Not in GFXOFF.
 * Wetuwns 3=Twansition into GFXOFF.
 */
uint32_t smu_v12_0_get_gfxoff_status(stwuct smu_context *smu)
{
	uint32_t weg;
	uint32_t gfxOff_Status = 0;
	stwuct amdgpu_device *adev = smu->adev;

	weg = WWEG32_SOC15(SMUIO, 0, mmSMUIO_GFX_MISC_CNTW);
	gfxOff_Status = (weg & SMUIO_GFX_MISC_CNTW__PWW_GFXOFF_STATUS_MASK)
		>> SMUIO_GFX_MISC_CNTW__PWW_GFXOFF_STATUS__SHIFT;

	wetuwn gfxOff_Status;
}

int smu_v12_0_gfx_off_contwow(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0, timeout = 500;

	if (enabwe) {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_AwwowGfxOff, NUWW);

	} ewse {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_DisawwowGfxOff, NUWW);

		/* confiwm gfx is back to "on" state, timeout is 0.5 second */
		whiwe (!(smu_v12_0_get_gfxoff_status(smu) == 2)) {
			msweep(1);
			timeout--;
			if (timeout == 0) {
				DWM_EWWOW("disabwe gfxoff timeout and faiwed!\n");
				bweak;
			}
		}
	}

	wetuwn wet;
}

int smu_v12_0_fini_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	kfwee(smu_tabwe->cwocks_tabwe);
	smu_tabwe->cwocks_tabwe = NUWW;

	kfwee(smu_tabwe->metwics_tabwe);
	smu_tabwe->metwics_tabwe = NUWW;

	kfwee(smu_tabwe->watewmawks_tabwe);
	smu_tabwe->watewmawks_tabwe = NUWW;

	kfwee(smu_tabwe->gpu_metwics_tabwe);
	smu_tabwe->gpu_metwics_tabwe = NUWW;

	wetuwn 0;
}

int smu_v12_0_set_defauwt_dpm_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	wetuwn smu_cmn_update_tabwe(smu, SMU_TABWE_DPMCWOCKS, 0, smu_tabwe->cwocks_tabwe, fawse);
}

int smu_v12_0_mode2_weset(stwuct smu_context *smu)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GfxDeviceDwivewWeset, SMU_WESET_MODE_2, NUWW);
}

int smu_v12_0_set_soft_fweq_wimited_wange(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
			    uint32_t min, uint32_t max)
{
	int wet = 0;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn 0;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinGfxCwk, min, NUWW);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxGfxCwk, max, NUWW);
		if (wet)
			wetuwn wet;
	bweak;
	case SMU_FCWK:
	case SMU_MCWK:
	case SMU_UCWK:
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinFcwkByFweq, min, NUWW);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxFcwkByFweq, max, NUWW);
		if (wet)
			wetuwn wet;
	bweak;
	case SMU_SOCCWK:
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinSoccwkByFweq, min, NUWW);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxSoccwkByFweq, max, NUWW);
		if (wet)
			wetuwn wet;
	bweak;
	case SMU_VCWK:
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinVcn, min, NUWW);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxVcn, max, NUWW);
		if (wet)
			wetuwn wet;
	bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

int smu_v12_0_set_dwivew_tabwe_wocation(stwuct smu_context *smu)
{
	stwuct smu_tabwe *dwivew_tabwe = &smu->smu_tabwe.dwivew_tabwe;
	int wet = 0;

	if (dwivew_tabwe->mc_addwess) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetDwivewDwamAddwHigh,
				uppew_32_bits(dwivew_tabwe->mc_addwess),
				NUWW);
		if (!wet)
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetDwivewDwamAddwWow,
				wowew_32_bits(dwivew_tabwe->mc_addwess),
				NUWW);
	}

	wetuwn wet;
}

static int smu_v12_0_atom_get_smu_cwockinfo(stwuct amdgpu_device *adev,
					    uint8_t cwk_id,
					    uint8_t syspww_id,
					    uint32_t *cwk_fweq)
{
	stwuct atom_get_smu_cwock_info_pawametews_v3_1 input = {0};
	stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *output;
	int wet, index;

	input.cwk_id = cwk_id;
	input.syspww_id = syspww_id;
	input.command = GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ;
	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_command_functions_v2_1,
					    getsmucwockinfo);

	wet = amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index,
					(uint32_t *)&input);
	if (wet)
		wetuwn -EINVAW;

	output = (stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *)&input;
	*cwk_fweq = we32_to_cpu(output->atom_smu_outputcwkfweq.smu_cwock_fweq_hz) / 10000;

	wetuwn 0;
}

int smu_v12_0_get_vbios_bootup_vawues(stwuct smu_context *smu)
{
	int wet, index;
	uint16_t size;
	uint8_t fwev, cwev;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_fiwmwawe_info_v3_1 *v_3_1;
	stwuct atom_fiwmwawe_info_v3_3 *v_3_3;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);

	wet = amdgpu_atombios_get_data_tabwe(smu->adev, index, &size, &fwev, &cwev,
				      (uint8_t **)&headew);
	if (wet)
		wetuwn wet;

	if (headew->fowmat_wevision != 3) {
		dev_eww(smu->adev->dev, "unknown atom_fiwmwawe_info vewsion! fow smu12\n");
		wetuwn -EINVAW;
	}

	switch (headew->content_wevision) {
	case 0:
	case 1:
	case 2:
		v_3_1 = (stwuct atom_fiwmwawe_info_v3_1 *)headew;
		smu->smu_tabwe.boot_vawues.wevision = v_3_1->fiwmwawe_wevision;
		smu->smu_tabwe.boot_vawues.gfxcwk = v_3_1->bootup_scwk_in10khz;
		smu->smu_tabwe.boot_vawues.ucwk = v_3_1->bootup_mcwk_in10khz;
		smu->smu_tabwe.boot_vawues.soccwk = 0;
		smu->smu_tabwe.boot_vawues.dcefcwk = 0;
		smu->smu_tabwe.boot_vawues.vddc = v_3_1->bootup_vddc_mv;
		smu->smu_tabwe.boot_vawues.vddci = v_3_1->bootup_vddci_mv;
		smu->smu_tabwe.boot_vawues.mvddc = v_3_1->bootup_mvddc_mv;
		smu->smu_tabwe.boot_vawues.vdd_gfx = v_3_1->bootup_vddgfx_mv;
		smu->smu_tabwe.boot_vawues.coowing_id = v_3_1->coowingsowution_id;
		smu->smu_tabwe.boot_vawues.pp_tabwe_id = 0;
		smu->smu_tabwe.boot_vawues.fiwmwawe_caps = v_3_1->fiwmwawe_capabiwity;
		bweak;
	case 3:
	case 4:
	defauwt:
		v_3_3 = (stwuct atom_fiwmwawe_info_v3_3 *)headew;
		smu->smu_tabwe.boot_vawues.wevision = v_3_3->fiwmwawe_wevision;
		smu->smu_tabwe.boot_vawues.gfxcwk = v_3_3->bootup_scwk_in10khz;
		smu->smu_tabwe.boot_vawues.ucwk = v_3_3->bootup_mcwk_in10khz;
		smu->smu_tabwe.boot_vawues.soccwk = 0;
		smu->smu_tabwe.boot_vawues.dcefcwk = 0;
		smu->smu_tabwe.boot_vawues.vddc = v_3_3->bootup_vddc_mv;
		smu->smu_tabwe.boot_vawues.vddci = v_3_3->bootup_vddci_mv;
		smu->smu_tabwe.boot_vawues.mvddc = v_3_3->bootup_mvddc_mv;
		smu->smu_tabwe.boot_vawues.vdd_gfx = v_3_3->bootup_vddgfx_mv;
		smu->smu_tabwe.boot_vawues.coowing_id = v_3_3->coowingsowution_id;
		smu->smu_tabwe.boot_vawues.pp_tabwe_id = v_3_3->ppwib_pptabwe_id;
		smu->smu_tabwe.boot_vawues.fiwmwawe_caps = v_3_3->fiwmwawe_capabiwity;
	}

	smu->smu_tabwe.boot_vawues.fowmat_wevision = headew->fowmat_wevision;
	smu->smu_tabwe.boot_vawues.content_wevision = headew->content_wevision;

	smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU12_SYSPWW0_SOCCWK_ID,
					 (uint8_t)SMU12_SYSPWW0_ID,
					 &smu->smu_tabwe.boot_vawues.soccwk);

	smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU12_SYSPWW1_DCFCWK_ID,
					 (uint8_t)SMU12_SYSPWW1_ID,
					 &smu->smu_tabwe.boot_vawues.dcefcwk);

	smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU12_SYSPWW0_VCWK_ID,
					 (uint8_t)SMU12_SYSPWW0_ID,
					 &smu->smu_tabwe.boot_vawues.vcwk);

	smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU12_SYSPWW0_DCWK_ID,
					 (uint8_t)SMU12_SYSPWW0_ID,
					 &smu->smu_tabwe.boot_vawues.dcwk);

	if ((smu->smu_tabwe.boot_vawues.fowmat_wevision == 3) &&
	    (smu->smu_tabwe.boot_vawues.content_wevision >= 2))
		smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
						 (uint8_t)SMU12_SYSPWW3_0_FCWK_ID,
						 (uint8_t)SMU12_SYSPWW3_0_ID,
						 &smu->smu_tabwe.boot_vawues.fcwk);

	smu_v12_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU12_SYSPWW0_WCWK_ID,
					 (uint8_t)SMU12_SYSPWW0_ID,
					 &smu->smu_tabwe.boot_vawues.wcwk);

	wetuwn 0;
}
