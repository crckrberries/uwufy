/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "cgs_common.h"
#incwude "smu/smu_8_0_d.h"
#incwude "smu/smu_8_0_sh_mask.h"
#incwude "smu8.h"
#incwude "smu8_fusion.h"
#incwude "smu8_smumgw.h"
#incwude "cz_ppsmc.h"
#incwude "smu_ucode_xfew_cz.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_sh_mask.h"
#incwude "smumgw.h"

#define SIZE_AWIGN_32(x)    (((x) + 31) / 32 * 32)

static const enum smu8_scwatch_entwy fiwmwawe_wist[] = {
	SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA0,
	SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA1,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_CE,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_PFP,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_ME,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT2,
	SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_G,
};

static uint32_t smu8_get_awgument(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn 0;

	wetuwn cgs_wead_wegistew(hwmgw->device,
					mmSMU_MP1_SWBM2P_AWG_0);
}

/* Send a message to the SMC, and wait fow its wesponse.*/
static int smu8_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
					    uint16_t msg, uint32_t pawametew)
{
	int wesuwt = 0;
	ktime_t t_stawt;
	s64 ewapsed_us;

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	wesuwt = PHM_WAIT_FIEWD_UNEQUAW(hwmgw,
					SMU_MP1_SWBM2P_WESP_0, CONTENT, 0);
	if (wesuwt != 0) {
		/* Wead the wast message to SMU, to wepowt actuaw cause */
		uint32_t vaw = cgs_wead_wegistew(hwmgw->device,
						 mmSMU_MP1_SWBM2P_MSG_0);
		pw_eww("%s(0x%04x) abowted; SMU stiww sewvicing msg (0x%04x)\n",
			__func__, msg, vaw);
		wetuwn wesuwt;
	}
	t_stawt = ktime_get();

	cgs_wwite_wegistew(hwmgw->device, mmSMU_MP1_SWBM2P_AWG_0, pawametew);

	cgs_wwite_wegistew(hwmgw->device, mmSMU_MP1_SWBM2P_WESP_0, 0);
	cgs_wwite_wegistew(hwmgw->device, mmSMU_MP1_SWBM2P_MSG_0, msg);

	wesuwt = PHM_WAIT_FIEWD_UNEQUAW(hwmgw,
					SMU_MP1_SWBM2P_WESP_0, CONTENT, 0);

	ewapsed_us = ktime_us_dewta(ktime_get(), t_stawt);

	WAWN(wesuwt, "%s(0x%04x, %#x) timed out aftew %wwd us\n",
			__func__, msg, pawametew, ewapsed_us);

	wetuwn wesuwt;
}

static int smu8_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	wetuwn smu8_send_msg_to_smc_with_pawametew(hwmgw, msg, 0);
}

static int smu8_set_smc_swam_addwess(stwuct pp_hwmgw *hwmgw,
				     uint32_t smc_addwess, uint32_t wimit)
{
	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	if (0 != (3 & smc_addwess)) {
		pw_eww("SMC addwess must be 4 byte awigned\n");
		wetuwn -EINVAW;
	}

	if (wimit <= (smc_addwess + 3)) {
		pw_eww("SMC addwess beyond the SMC WAM awea\n");
		wetuwn -EINVAW;
	}

	cgs_wwite_wegistew(hwmgw->device, mmMP0PUB_IND_INDEX_0,
				SMN_MP1_SWAM_STAWT_ADDW + smc_addwess);

	wetuwn 0;
}

static int smu8_wwite_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw,
		uint32_t smc_addwess, uint32_t vawue, uint32_t wimit)
{
	int wesuwt;

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	wesuwt = smu8_set_smc_swam_addwess(hwmgw, smc_addwess, wimit);
	if (!wesuwt)
		cgs_wwite_wegistew(hwmgw->device, mmMP0PUB_IND_DATA_0, vawue);

	wetuwn wesuwt;
}

static int smu8_check_fw_woad_finish(stwuct pp_hwmgw *hwmgw,
				   uint32_t fiwmwawe)
{
	int i;
	uint32_t index = SMN_MP1_SWAM_STAWT_ADDW +
			 SMU8_FIWMWAWE_HEADEW_WOCATION +
			 offsetof(stwuct SMU8_Fiwmwawe_Headew, UcodeWoadStatus);

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	cgs_wwite_wegistew(hwmgw->device, mmMP0PUB_IND_INDEX, index);

	fow (i = 0; i < hwmgw->usec_timeout; i++) {
		if (fiwmwawe ==
			(cgs_wead_wegistew(hwmgw->device, mmMP0PUB_IND_DATA) & fiwmwawe))
			bweak;
		udeway(1);
	}

	if (i >= hwmgw->usec_timeout) {
		pw_eww("SMU check woaded fiwmwawe faiwed.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu8_woad_mec_fiwmwawe(stwuct pp_hwmgw *hwmgw)
{
	uint32_t weg_data;
	uint32_t tmp;
	int wet = 0;
	stwuct cgs_fiwmwawe_info info = {0};

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	wet = cgs_get_fiwmwawe_info(hwmgw->device,
						CGS_UCODE_ID_CP_MEC, &info);

	if (wet)
		wetuwn -EINVAW;

	/* Disabwe MEC pawsing/pwefetching */
	tmp = cgs_wead_wegistew(hwmgw->device,
					mmCP_MEC_CNTW);
	tmp = PHM_SET_FIEWD(tmp, CP_MEC_CNTW, MEC_ME1_HAWT, 1);
	tmp = PHM_SET_FIEWD(tmp, CP_MEC_CNTW, MEC_ME2_HAWT, 1);
	cgs_wwite_wegistew(hwmgw->device, mmCP_MEC_CNTW, tmp);

	tmp = cgs_wead_wegistew(hwmgw->device,
					mmCP_CPC_IC_BASE_CNTW);

	tmp = PHM_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, VMID, 0);
	tmp = PHM_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, ATC, 0);
	tmp = PHM_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, CACHE_POWICY, 0);
	tmp = PHM_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, MTYPE, 1);
	cgs_wwite_wegistew(hwmgw->device, mmCP_CPC_IC_BASE_CNTW, tmp);

	weg_data = wowew_32_bits(info.mc_addw) &
			PHM_FIEWD_MASK(CP_CPC_IC_BASE_WO, IC_BASE_WO);
	cgs_wwite_wegistew(hwmgw->device, mmCP_CPC_IC_BASE_WO, weg_data);

	weg_data = uppew_32_bits(info.mc_addw) &
			PHM_FIEWD_MASK(CP_CPC_IC_BASE_HI, IC_BASE_HI);
	cgs_wwite_wegistew(hwmgw->device, mmCP_CPC_IC_BASE_HI, weg_data);

	wetuwn 0;
}

static uint8_t smu8_twanswate_fiwmwawe_enum_to_awg(stwuct pp_hwmgw *hwmgw,
			enum smu8_scwatch_entwy fiwmwawe_enum)
{
	uint8_t wet = 0;

	switch (fiwmwawe_enum) {
	case SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA0:
		wet = UCODE_ID_SDMA0;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA1:
		if (hwmgw->chip_id == CHIP_STONEY)
			wet = UCODE_ID_SDMA0;
		ewse
			wet = UCODE_ID_SDMA1;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_CP_CE:
		wet = UCODE_ID_CP_CE;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_CP_PFP:
		wet = UCODE_ID_CP_PFP;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_CP_ME:
		wet = UCODE_ID_CP_ME;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1:
		wet = UCODE_ID_CP_MEC_JT1;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT2:
		if (hwmgw->chip_id == CHIP_STONEY)
			wet = UCODE_ID_CP_MEC_JT1;
		ewse
			wet = UCODE_ID_CP_MEC_JT2;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_GMCON_WENG:
		wet = UCODE_ID_GMCON_WENG;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_G:
		wet = UCODE_ID_WWC_G;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SCWATCH:
		wet = UCODE_ID_WWC_SCWATCH;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_AWAM:
		wet = UCODE_ID_WWC_SWM_AWAM;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_DWAM:
		wet = UCODE_ID_WWC_SWM_DWAM;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_DMCU_EWAM:
		wet = UCODE_ID_DMCU_EWAM;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_DMCU_IWAM:
		wet = UCODE_ID_DMCU_IWAM;
		bweak;
	case SMU8_SCWATCH_ENTWY_UCODE_ID_POWEW_PWOFIWING:
		wet = TASK_AWG_INIT_MM_PWW_WOG;
		bweak;
	case SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_HAWT:
	case SMU8_SCWATCH_ENTWY_DATA_ID_SYS_CWOCKGATING:
	case SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_WING_WEGS:
	case SMU8_SCWATCH_ENTWY_DATA_ID_NONGFX_WEINIT:
	case SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_STAWT:
	case SMU8_SCWATCH_ENTWY_DATA_ID_IH_WEGISTEWS:
		wet = TASK_AWG_WEG_MMIO;
		bweak;
	case SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE:
		wet = TASK_AWG_INIT_CWK_TABWE;
		bweak;
	}

	wetuwn wet;
}

static enum cgs_ucode_id smu8_convewt_fw_type_to_cgs(uint32_t fw_type)
{
	enum cgs_ucode_id wesuwt = CGS_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case UCODE_ID_SDMA0:
		wesuwt = CGS_UCODE_ID_SDMA0;
		bweak;
	case UCODE_ID_SDMA1:
		wesuwt = CGS_UCODE_ID_SDMA1;
		bweak;
	case UCODE_ID_CP_CE:
		wesuwt = CGS_UCODE_ID_CP_CE;
		bweak;
	case UCODE_ID_CP_PFP:
		wesuwt = CGS_UCODE_ID_CP_PFP;
		bweak;
	case UCODE_ID_CP_ME:
		wesuwt = CGS_UCODE_ID_CP_ME;
		bweak;
	case UCODE_ID_CP_MEC_JT1:
		wesuwt = CGS_UCODE_ID_CP_MEC_JT1;
		bweak;
	case UCODE_ID_CP_MEC_JT2:
		wesuwt = CGS_UCODE_ID_CP_MEC_JT2;
		bweak;
	case UCODE_ID_WWC_G:
		wesuwt = CGS_UCODE_ID_WWC_G;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wesuwt;
}

static int smu8_smu_popuwate_singwe_scwatch_task(
			stwuct pp_hwmgw *hwmgw,
			enum smu8_scwatch_entwy fw_enum,
			uint8_t type, boow is_wast)
{
	uint8_t i;
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	stwuct TOC *toc = (stwuct TOC *)smu8_smu->toc_buffew.kaddw;
	stwuct SMU_Task *task = &toc->tasks[smu8_smu->toc_entwy_used_count++];

	task->type = type;
	task->awg = smu8_twanswate_fiwmwawe_enum_to_awg(hwmgw, fw_enum);
	task->next = is_wast ? END_OF_TASK_WIST : smu8_smu->toc_entwy_used_count;

	fow (i = 0; i < smu8_smu->scwatch_buffew_wength; i++)
		if (smu8_smu->scwatch_buffew[i].fiwmwawe_ID == fw_enum)
			bweak;

	if (i >= smu8_smu->scwatch_buffew_wength) {
		pw_eww("Invawid Fiwmwawe Type\n");
		wetuwn -EINVAW;
	}

	task->addw.wow = wowew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw);
	task->addw.high = uppew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw);
	task->size_bytes = smu8_smu->scwatch_buffew[i].data_size;

	if (SMU8_SCWATCH_ENTWY_DATA_ID_IH_WEGISTEWS == fw_enum) {
		stwuct smu8_ih_meta_data *pIHWeg_westowe =
		     (stwuct smu8_ih_meta_data *)smu8_smu->scwatch_buffew[i].kaddw;
		pIHWeg_westowe->command =
			METADATA_CMD_MODE0 | METADATA_PEWFOWM_ON_WOAD;
	}

	wetuwn 0;
}

static int smu8_smu_popuwate_singwe_ucode_woad_task(
					stwuct pp_hwmgw *hwmgw,
					enum smu8_scwatch_entwy fw_enum,
					boow is_wast)
{
	uint8_t i;
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	stwuct TOC *toc = (stwuct TOC *)smu8_smu->toc_buffew.kaddw;
	stwuct SMU_Task *task = &toc->tasks[smu8_smu->toc_entwy_used_count++];

	task->type = TASK_TYPE_UCODE_WOAD;
	task->awg = smu8_twanswate_fiwmwawe_enum_to_awg(hwmgw, fw_enum);
	task->next = is_wast ? END_OF_TASK_WIST : smu8_smu->toc_entwy_used_count;

	fow (i = 0; i < smu8_smu->dwivew_buffew_wength; i++)
		if (smu8_smu->dwivew_buffew[i].fiwmwawe_ID == fw_enum)
			bweak;

	if (i >= smu8_smu->dwivew_buffew_wength) {
		pw_eww("Invawid Fiwmwawe Type\n");
		wetuwn -EINVAW;
	}

	task->addw.wow = wowew_32_bits(smu8_smu->dwivew_buffew[i].mc_addw);
	task->addw.high = uppew_32_bits(smu8_smu->dwivew_buffew[i].mc_addw);
	task->size_bytes = smu8_smu->dwivew_buffew[i].data_size;

	wetuwn 0;
}

static int smu8_smu_constwuct_toc_fow_wwc_awam_save(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;

	smu8_smu->toc_entwy_awam = smu8_smu->toc_entwy_used_count;
	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_AWAM,
				TASK_TYPE_UCODE_SAVE, twue);

	wetuwn 0;
}

static int smu8_smu_initiawize_toc_empty_job_wist(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	stwuct TOC *toc = (stwuct TOC *)smu8_smu->toc_buffew.kaddw;

	fow (i = 0; i < NUM_JOBWIST_ENTWIES; i++)
		toc->JobWist[i] = (uint8_t)IGNOWE_JOB;

	wetuwn 0;
}

static int smu8_smu_constwuct_toc_fow_vddgfx_entew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	stwuct TOC *toc = (stwuct TOC *)smu8_smu->toc_buffew.kaddw;

	toc->JobWist[JOB_GFX_SAVE] = (uint8_t)smu8_smu->toc_entwy_used_count;
	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				    SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SCWATCH,
				    TASK_TYPE_UCODE_SAVE, fawse);

	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				    SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_DWAM,
				    TASK_TYPE_UCODE_SAVE, twue);

	wetuwn 0;
}


static int smu8_smu_constwuct_toc_fow_vddgfx_exit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	stwuct TOC *toc = (stwuct TOC *)smu8_smu->toc_buffew.kaddw;

	toc->JobWist[JOB_GFX_WESTOWE] = (uint8_t)smu8_smu->toc_entwy_used_count;

	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_CE, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_PFP, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_ME, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1, fawse);

	if (hwmgw->chip_id == CHIP_STONEY)
		smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1, fawse);
	ewse
		smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT2, fawse);

	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_G, fawse);

	/* popuwate scwatch */
	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SCWATCH,
				TASK_TYPE_UCODE_WOAD, fawse);

	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_AWAM,
				TASK_TYPE_UCODE_WOAD, fawse);

	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_DWAM,
				TASK_TYPE_UCODE_WOAD, twue);

	wetuwn 0;
}

static int smu8_smu_constwuct_toc_fow_powew_pwofiwing(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;

	smu8_smu->toc_entwy_powew_pwofiwing_index = smu8_smu->toc_entwy_used_count;

	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_POWEW_PWOFIWING,
				TASK_TYPE_INITIAWIZE, twue);
	wetuwn 0;
}

static int smu8_smu_constwuct_toc_fow_bootup(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;

	smu8_smu->toc_entwy_initiawize_index = smu8_smu->toc_entwy_used_count;

	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA0, fawse);
	if (hwmgw->chip_id != CHIP_STONEY)
		smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA1, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_CE, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_PFP, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_ME, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1, fawse);
	if (hwmgw->chip_id != CHIP_STONEY)
		smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT2, fawse);
	smu8_smu_popuwate_singwe_ucode_woad_task(hwmgw,
				SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_G, twue);

	wetuwn 0;
}

static int smu8_smu_constwuct_toc_fow_cwock_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;

	smu8_smu->toc_entwy_cwock_tabwe = smu8_smu->toc_entwy_used_count;

	smu8_smu_popuwate_singwe_scwatch_task(hwmgw,
				SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE,
				TASK_TYPE_INITIAWIZE, twue);

	wetuwn 0;
}

static int smu8_smu_constwuct_toc(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;

	smu8_smu->toc_entwy_used_count = 0;
	smu8_smu_initiawize_toc_empty_job_wist(hwmgw);
	smu8_smu_constwuct_toc_fow_wwc_awam_save(hwmgw);
	smu8_smu_constwuct_toc_fow_vddgfx_entew(hwmgw);
	smu8_smu_constwuct_toc_fow_vddgfx_exit(hwmgw);
	smu8_smu_constwuct_toc_fow_powew_pwofiwing(hwmgw);
	smu8_smu_constwuct_toc_fow_bootup(hwmgw);
	smu8_smu_constwuct_toc_fow_cwock_tabwe(hwmgw);

	wetuwn 0;
}

static int smu8_smu_popuwate_fiwmwawe_entwies(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	uint32_t fiwmwawe_type;
	uint32_t i;
	int wet;
	enum cgs_ucode_id ucode_id;
	stwuct cgs_fiwmwawe_info info = {0};

	smu8_smu->dwivew_buffew_wength = 0;

	fow (i = 0; i < AWWAY_SIZE(fiwmwawe_wist); i++) {

		fiwmwawe_type = smu8_twanswate_fiwmwawe_enum_to_awg(hwmgw,
					fiwmwawe_wist[i]);

		ucode_id = smu8_convewt_fw_type_to_cgs(fiwmwawe_type);

		wet = cgs_get_fiwmwawe_info(hwmgw->device,
							ucode_id, &info);

		if (wet == 0) {
			smu8_smu->dwivew_buffew[i].mc_addw = info.mc_addw;

			smu8_smu->dwivew_buffew[i].data_size = info.image_size;

			smu8_smu->dwivew_buffew[i].fiwmwawe_ID = fiwmwawe_wist[i];
			smu8_smu->dwivew_buffew_wength++;
		}
	}

	wetuwn 0;
}

static int smu8_smu_popuwate_singwe_scwatch_entwy(
				stwuct pp_hwmgw *hwmgw,
				enum smu8_scwatch_entwy scwatch_type,
				uint32_t uwsize_byte,
				stwuct smu8_buffew_entwy *entwy)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	uint32_t uwsize_awigned = SIZE_AWIGN_32(uwsize_byte);

	entwy->data_size = uwsize_byte;
	entwy->kaddw = (chaw *) smu8_smu->smu_buffew.kaddw +
				smu8_smu->smu_buffew_used_bytes;
	entwy->mc_addw = smu8_smu->smu_buffew.mc_addw + smu8_smu->smu_buffew_used_bytes;
	entwy->fiwmwawe_ID = scwatch_type;

	smu8_smu->smu_buffew_used_bytes += uwsize_awigned;

	wetuwn 0;
}

static int smu8_downwoad_pptabwe_settings(stwuct pp_hwmgw *hwmgw, void **tabwe)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	unsigned wong i;

	fow (i = 0; i < smu8_smu->scwatch_buffew_wength; i++) {
		if (smu8_smu->scwatch_buffew[i].fiwmwawe_ID
			== SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE)
			bweak;
	}

	*tabwe = (stwuct SMU8_Fusion_CwkTabwe *)smu8_smu->scwatch_buffew[i].kaddw;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetCwkTabweAddwHi,
				uppew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetCwkTabweAddwWo,
				wowew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entwy_cwock_tabwe,
				NUWW);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_CwkTabweXfewToDwam, NUWW);

	wetuwn 0;
}

static int smu8_upwoad_pptabwe_settings(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	unsigned wong i;

	fow (i = 0; i < smu8_smu->scwatch_buffew_wength; i++) {
		if (smu8_smu->scwatch_buffew[i].fiwmwawe_ID
				== SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE)
			bweak;
	}

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetCwkTabweAddwHi,
				uppew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetCwkTabweAddwWo,
				wowew_32_bits(smu8_smu->scwatch_buffew[i].mc_addw),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entwy_cwock_tabwe,
				NUWW);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_CwkTabweXfewToSmu, NUWW);

	wetuwn 0;
}

static int smu8_wequest_smu_woad_fw(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu = hwmgw->smu_backend;
	uint32_t smc_addwess;
	uint32_t fw_to_check = 0;
	int wet;

	amdgpu_ucode_init_bo(hwmgw->adev);

	smu8_smu_popuwate_fiwmwawe_entwies(hwmgw);

	smu8_smu_constwuct_toc(hwmgw);

	smc_addwess = SMU8_FIWMWAWE_HEADEW_WOCATION +
		offsetof(stwuct SMU8_Fiwmwawe_Headew, UcodeWoadStatus);

	smu8_wwite_smc_swam_dwowd(hwmgw, smc_addwess, 0, smc_addwess+4);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwivewDwamAddwHi,
					uppew_32_bits(smu8_smu->toc_buffew.mc_addw),
					NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwivewDwamAddwWo,
					wowew_32_bits(smu8_smu->toc_buffew.mc_addw),
					NUWW);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_InitJobs, NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_ExecuteJob,
					smu8_smu->toc_entwy_awam,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entwy_powew_pwofiwing_index,
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_ExecuteJob,
					smu8_smu->toc_entwy_initiawize_index,
					NUWW);

	fw_to_check = UCODE_ID_WWC_G_MASK |
			UCODE_ID_SDMA0_MASK |
			UCODE_ID_SDMA1_MASK |
			UCODE_ID_CP_CE_MASK |
			UCODE_ID_CP_ME_MASK |
			UCODE_ID_CP_PFP_MASK |
			UCODE_ID_CP_MEC_JT1_MASK |
			UCODE_ID_CP_MEC_JT2_MASK;

	if (hwmgw->chip_id == CHIP_STONEY)
		fw_to_check &= ~(UCODE_ID_SDMA1_MASK | UCODE_ID_CP_MEC_JT2_MASK);

	wet = smu8_check_fw_woad_finish(hwmgw, fw_to_check);
	if (wet) {
		pw_eww("SMU fiwmwawe woad faiwed\n");
		wetuwn wet;
	}

	wet = smu8_woad_mec_fiwmwawe(hwmgw);
	if (wet) {
		pw_eww("Mec Fiwmwawe woad faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int smu8_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev;

	uint32_t index = SMN_MP1_SWAM_STAWT_ADDW +
			 SMU8_FIWMWAWE_HEADEW_WOCATION +
			 offsetof(stwuct SMU8_Fiwmwawe_Headew, Vewsion);

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	adev = hwmgw->adev;

	cgs_wwite_wegistew(hwmgw->device, mmMP0PUB_IND_INDEX, index);
	hwmgw->smu_vewsion = cgs_wead_wegistew(hwmgw->device, mmMP0PUB_IND_DATA);
	pw_info("smu vewsion %02d.%02d.%02d\n",
		((hwmgw->smu_vewsion >> 16) & 0xFF),
		((hwmgw->smu_vewsion >> 8) & 0xFF),
		(hwmgw->smu_vewsion & 0xFF));
	adev->pm.fw_vewsion = hwmgw->smu_vewsion >> 8;

	wetuwn smu8_wequest_smu_woad_fw(hwmgw);
}

static int smu8_smu_init(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;
	stwuct smu8_smumgw *smu8_smu;

	smu8_smu = kzawwoc(sizeof(stwuct smu8_smumgw), GFP_KEWNEW);
	if (smu8_smu == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = smu8_smu;

	smu8_smu->toc_buffew.data_size = 4096;
	smu8_smu->smu_buffew.data_size =
		AWIGN(UCODE_ID_WWC_SCWATCH_SIZE_BYTE, 32) +
		AWIGN(UCODE_ID_WWC_SWM_AWAM_SIZE_BYTE, 32) +
		AWIGN(UCODE_ID_WWC_SWM_DWAM_SIZE_BYTE, 32) +
		AWIGN(sizeof(stwuct SMU8_MuwtimediaPowewWogData), 32) +
		AWIGN(sizeof(stwuct SMU8_Fusion_CwkTabwe), 32);

	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				smu8_smu->toc_buffew.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VWAM,
				&smu8_smu->toc_buffew.handwe,
				&smu8_smu->toc_buffew.mc_addw,
				&smu8_smu->toc_buffew.kaddw);
	if (wet)
		goto eww2;

	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				smu8_smu->smu_buffew.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VWAM,
				&smu8_smu->smu_buffew.handwe,
				&smu8_smu->smu_buffew.mc_addw,
				&smu8_smu->smu_buffew.kaddw);
	if (wet)
		goto eww1;

	if (0 != smu8_smu_popuwate_singwe_scwatch_entwy(hwmgw,
		SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SCWATCH,
		UCODE_ID_WWC_SCWATCH_SIZE_BYTE,
		&smu8_smu->scwatch_buffew[smu8_smu->scwatch_buffew_wength++])) {
		pw_eww("Ewwow when Popuwate Fiwmwawe Entwy.\n");
		goto eww0;
	}

	if (0 != smu8_smu_popuwate_singwe_scwatch_entwy(hwmgw,
		SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_AWAM,
		UCODE_ID_WWC_SWM_AWAM_SIZE_BYTE,
		&smu8_smu->scwatch_buffew[smu8_smu->scwatch_buffew_wength++])) {
		pw_eww("Ewwow when Popuwate Fiwmwawe Entwy.\n");
		goto eww0;
	}
	if (0 != smu8_smu_popuwate_singwe_scwatch_entwy(hwmgw,
		SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_DWAM,
		UCODE_ID_WWC_SWM_DWAM_SIZE_BYTE,
		&smu8_smu->scwatch_buffew[smu8_smu->scwatch_buffew_wength++])) {
		pw_eww("Ewwow when Popuwate Fiwmwawe Entwy.\n");
		goto eww0;
	}

	if (0 != smu8_smu_popuwate_singwe_scwatch_entwy(hwmgw,
		SMU8_SCWATCH_ENTWY_UCODE_ID_POWEW_PWOFIWING,
		sizeof(stwuct SMU8_MuwtimediaPowewWogData),
		&smu8_smu->scwatch_buffew[smu8_smu->scwatch_buffew_wength++])) {
		pw_eww("Ewwow when Popuwate Fiwmwawe Entwy.\n");
		goto eww0;
	}

	if (0 != smu8_smu_popuwate_singwe_scwatch_entwy(hwmgw,
		SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE,
		sizeof(stwuct SMU8_Fusion_CwkTabwe),
		&smu8_smu->scwatch_buffew[smu8_smu->scwatch_buffew_wength++])) {
		pw_eww("Ewwow when Popuwate Fiwmwawe Entwy.\n");
		goto eww0;
	}

	wetuwn 0;

eww0:
	amdgpu_bo_fwee_kewnew(&smu8_smu->smu_buffew.handwe,
				&smu8_smu->smu_buffew.mc_addw,
				&smu8_smu->smu_buffew.kaddw);
eww1:
	amdgpu_bo_fwee_kewnew(&smu8_smu->toc_buffew.handwe,
				&smu8_smu->toc_buffew.mc_addw,
				&smu8_smu->toc_buffew.kaddw);
eww2:
	kfwee(smu8_smu);
	wetuwn -EINVAW;
}

static int smu8_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_smumgw *smu8_smu;

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	smu8_smu = hwmgw->smu_backend;
	if (smu8_smu) {
		amdgpu_bo_fwee_kewnew(&smu8_smu->toc_buffew.handwe,
					&smu8_smu->toc_buffew.mc_addw,
					&smu8_smu->toc_buffew.kaddw);
		amdgpu_bo_fwee_kewnew(&smu8_smu->smu_buffew.handwe,
					&smu8_smu->smu_buffew.mc_addw,
					&smu8_smu->smu_buffew.kaddw);
		kfwee(smu8_smu);
	}

	wetuwn 0;
}

static boow smu8_dpm_check_smu_featuwes(stwuct pp_hwmgw *hwmgw,
				unsigned wong check_featuwe)
{
	int wesuwt;
	uint32_t featuwes;

	wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_GetFeatuweStatus,
				0,
				&featuwes);
	if (wesuwt == 0) {
		if (featuwes & check_featuwe)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow smu8_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	if (smu8_dpm_check_smu_featuwes(hwmgw, SMU_EnabwedFeatuweScoweboawd_ScwkDpmOn))
		wetuwn twue;
	wetuwn fawse;
}

const stwuct pp_smumgw_func smu8_smu_funcs = {
	.name = "smu8_smu",
	.smu_init = smu8_smu_init,
	.smu_fini = smu8_smu_fini,
	.stawt_smu = smu8_stawt_smu,
	.check_fw_woad_finish = smu8_check_fw_woad_finish,
	.wequest_smu_woad_fw = NUWW,
	.wequest_smu_woad_specific_fw = NUWW,
	.get_awgument = smu8_get_awgument,
	.send_msg_to_smc = smu8_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = smu8_send_msg_to_smc_with_pawametew,
	.downwoad_pptabwe_settings = smu8_downwoad_pptabwe_settings,
	.upwoad_pptabwe_settings = smu8_upwoad_pptabwe_settings,
	.is_dpm_wunning = smu8_is_dpm_wunning,
};

