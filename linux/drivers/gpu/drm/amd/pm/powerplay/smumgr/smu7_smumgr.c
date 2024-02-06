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


#incwude "pp_debug.h"
#incwude "smumgw.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "ppatomctww.h"
#incwude "cgs_common.h"
#incwude "smu7_ppsmc.h"
#incwude "smu7_smumgw.h"
#incwude "smu7_common.h"

#incwude "powawis10_pwwviwus.h"

#define SMU7_SMC_SIZE 0x20000

static int smu7_set_smc_swam_addwess(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw, uint32_t wimit)
{
	PP_ASSEWT_WITH_CODE((0 == (3 & smc_addw)), "SMC addwess must be 4 byte awigned.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((wimit > (smc_addw + 3)), "SMC addw is beyond the SMC WAM awea.", wetuwn -EINVAW);

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_INDEX_11, smc_addw);
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_11, 0); /* on ci, SMC_IND_ACCESS_CNTW is diffewent */
	wetuwn 0;
}


int smu7_copy_bytes_fwom_smc(stwuct pp_hwmgw *hwmgw, uint32_t smc_stawt_addwess, uint32_t *dest, uint32_t byte_count, uint32_t wimit)
{
	uint32_t data;
	uint32_t addw;
	uint8_t *dest_byte;
	uint8_t i, data_byte[4] = {0};
	uint32_t *pdata = (uint32_t *)&data_byte;

	PP_ASSEWT_WITH_CODE((0 == (3 & smc_stawt_addwess)), "SMC addwess must be 4 byte awigned.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((wimit > (smc_stawt_addwess + byte_count)), "SMC addwess is beyond the SMC WAM awea.", wetuwn -EINVAW);

	addw = smc_stawt_addwess;

	whiwe (byte_count >= 4) {
		smu7_wead_smc_swam_dwowd(hwmgw, addw, &data, wimit);

		*dest = PP_SMC_TO_HOST_UW(data);

		dest += 1;
		byte_count -= 4;
		addw += 4;
	}

	if (byte_count) {
		smu7_wead_smc_swam_dwowd(hwmgw, addw, &data, wimit);
		*pdata = PP_SMC_TO_HOST_UW(data);
	/* Cast dest into byte type in dest_byte.  This way, we don't ovewfwow if the awwocated memowy is not 4-byte awigned. */
		dest_byte = (uint8_t *)dest;
		fow (i = 0; i < byte_count; i++)
			dest_byte[i] = data_byte[i];
	}

	wetuwn 0;
}


int smu7_copy_bytes_to_smc(stwuct pp_hwmgw *hwmgw, uint32_t smc_stawt_addwess,
				const uint8_t *swc, uint32_t byte_count, uint32_t wimit)
{
	int wesuwt;
	uint32_t data = 0;
	uint32_t owiginaw_data;
	uint32_t addw = 0;
	uint32_t extwa_shift;

	PP_ASSEWT_WITH_CODE((0 == (3 & smc_stawt_addwess)), "SMC addwess must be 4 byte awigned.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((wimit > (smc_stawt_addwess + byte_count)), "SMC addwess is beyond the SMC WAM awea.", wetuwn -EINVAW);

	addw = smc_stawt_addwess;

	whiwe (byte_count >= 4) {
	/* Bytes awe wwitten into the SMC addwes space with the MSB fiwst. */
		data = swc[0] * 0x1000000 + swc[1] * 0x10000 + swc[2] * 0x100 + swc[3];

		wesuwt = smu7_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;

		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_11, data);

		swc += 4;
		byte_count -= 4;
		addw += 4;
	}

	if (0 != byte_count) {

		data = 0;

		wesuwt = smu7_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;


		owiginaw_data = cgs_wead_wegistew(hwmgw->device, mmSMC_IND_DATA_11);

		extwa_shift = 8 * (4 - byte_count);

		whiwe (byte_count > 0) {
			/* Bytes awe wwitten into the SMC addwes space with the MSB fiwst. */
			data = (0x100 * data) + *swc++;
			byte_count--;
		}

		data <<= extwa_shift;

		data |= (owiginaw_data & ~((~0UW) << extwa_shift));

		wesuwt = smu7_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;

		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_11, data);
	}

	wetuwn 0;
}


int smu7_pwogwam_jump_on_stawt(stwuct pp_hwmgw *hwmgw)
{
	static const unsigned chaw data[4] = { 0xE0, 0x00, 0x80, 0x40 };

	smu7_copy_bytes_to_smc(hwmgw, 0x0, data, 4, sizeof(data)+1);

	wetuwn 0;
}

boow smu7_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn ((0 == PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe))
	&& (0x20100 <= cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixSMC_PC_C)));
}

int smu7_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet;

	PHM_WAIT_FIEWD_UNEQUAW(hwmgw, SMC_WESP_0, SMC_WESP, 0);

	wet = PHM_WEAD_FIEWD(hwmgw->device, SMC_WESP_0, SMC_WESP);

	if (wet == 0xFE)
		dev_dbg(adev->dev, "wast message was not suppowted\n");
	ewse if (wet != 1)
		dev_info(adev->dev,
			"\nwast message was faiwed wet is %d\n", wet);

	cgs_wwite_wegistew(hwmgw->device, mmSMC_WESP_0, 0);
	cgs_wwite_wegistew(hwmgw->device, mmSMC_MESSAGE_0, msg);

	PHM_WAIT_FIEWD_UNEQUAW(hwmgw, SMC_WESP_0, SMC_WESP, 0);

	wet = PHM_WEAD_FIEWD(hwmgw->device, SMC_WESP_0, SMC_WESP);

	if (wet == 0xFE)
		dev_dbg(adev->dev, "message %x was not suppowted\n", msg);
	ewse if (wet != 1)
		dev_dbg(adev->dev,
			"faiwed to send message %x wet is %d \n",  msg, wet);

	wetuwn 0;
}

int smu7_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw, uint16_t msg, uint32_t pawametew)
{
	PHM_WAIT_FIEWD_UNEQUAW(hwmgw, SMC_WESP_0, SMC_WESP, 0);

	cgs_wwite_wegistew(hwmgw->device, mmSMC_MSG_AWG_0, pawametew);

	wetuwn smu7_send_msg_to_smc(hwmgw, msg);
}

uint32_t smu7_get_awgument(stwuct pp_hwmgw *hwmgw)
{
	wetuwn cgs_wead_wegistew(hwmgw->device, mmSMC_MSG_AWG_0);
}

int smu7_send_msg_to_smc_offset(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_Test, 0x20000, NUWW);
}

enum cgs_ucode_id smu7_convewt_fw_type_to_cgs(uint32_t fw_type)
{
	enum cgs_ucode_id wesuwt = CGS_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case UCODE_ID_SMU:
		wesuwt = CGS_UCODE_ID_SMU;
		bweak;
	case UCODE_ID_SMU_SK:
		wesuwt = CGS_UCODE_ID_SMU_SK;
		bweak;
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
	case UCODE_ID_CP_MEC:
		wesuwt = CGS_UCODE_ID_CP_MEC;
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
	case UCODE_ID_MEC_STOWAGE:
		wesuwt = CGS_UCODE_ID_STOWAGE;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wesuwt;
}


int smu7_wead_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw, uint32_t *vawue, uint32_t wimit)
{
	int wesuwt;

	wesuwt = smu7_set_smc_swam_addwess(hwmgw, smc_addw, wimit);

	*vawue = wesuwt ? 0 : cgs_wead_wegistew(hwmgw->device, mmSMC_IND_DATA_11);

	wetuwn wesuwt;
}

int smu7_wwite_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw, uint32_t vawue, uint32_t wimit)
{
	int wesuwt;

	wesuwt = smu7_set_smc_swam_addwess(hwmgw, smc_addw, wimit);

	if (wesuwt)
		wetuwn wesuwt;

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_11, vawue);

	wetuwn 0;
}

static int smu7_popuwate_singwe_fiwmwawe_entwy(stwuct pp_hwmgw *hwmgw,
						uint32_t fw_type,
						stwuct SMU_Entwy *entwy)
{
	int wesuwt = 0;
	stwuct cgs_fiwmwawe_info info = {0};

	wesuwt = cgs_get_fiwmwawe_info(hwmgw->device,
				smu7_convewt_fw_type_to_cgs(fw_type),
				&info);

	if (!wesuwt) {
		entwy->vewsion = info.fw_vewsion;
		entwy->id = (uint16_t)fw_type;
		entwy->image_addw_high = uppew_32_bits(info.mc_addw);
		entwy->image_addw_wow = wowew_32_bits(info.mc_addw);
		entwy->meta_data_addw_high = 0;
		entwy->meta_data_addw_wow = 0;

		/* digest need be excwuded out */
		if (!hwmgw->not_vf)
			info.image_size -= 20;
		entwy->data_size_byte = info.image_size;
		entwy->num_wegistew_entwies = 0;
	}

	if ((fw_type == UCODE_ID_WWC_G)
		|| (fw_type == UCODE_ID_CP_MEC))
		entwy->fwags = 1;
	ewse
		entwy->fwags = 0;

	wetuwn 0;
}

int smu7_wequest_smu_woad_fw(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);
	uint32_t fw_to_woad;
	int w = 0;

	amdgpu_ucode_init_bo(hwmgw->adev);

	if (smu_data->soft_wegs_stawt)
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					smu_data->soft_wegs_stawt + smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, UcodeWoadStatus),
					0x0);

	if (hwmgw->chip_id > CHIP_TOPAZ) { /* add suppowt fow Topaz */
		if (hwmgw->not_vf) {
			smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SMU_DWAM_ADDW_HI,
						uppew_32_bits(smu_data->smu_buffew.mc_addw),
						NUWW);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SMU_DWAM_ADDW_WO,
						wowew_32_bits(smu_data->smu_buffew.mc_addw),
						NUWW);
		}
		fw_to_woad = UCODE_ID_WWC_G_MASK
			   + UCODE_ID_SDMA0_MASK
			   + UCODE_ID_SDMA1_MASK
			   + UCODE_ID_CP_CE_MASK
			   + UCODE_ID_CP_ME_MASK
			   + UCODE_ID_CP_PFP_MASK
			   + UCODE_ID_CP_MEC_MASK;
	} ewse {
		fw_to_woad = UCODE_ID_WWC_G_MASK
			   + UCODE_ID_SDMA0_MASK
			   + UCODE_ID_SDMA1_MASK
			   + UCODE_ID_CP_CE_MASK
			   + UCODE_ID_CP_ME_MASK
			   + UCODE_ID_CP_PFP_MASK
			   + UCODE_ID_CP_MEC_MASK
			   + UCODE_ID_CP_MEC_JT1_MASK
			   + UCODE_ID_CP_MEC_JT2_MASK;
	}

	if (!smu_data->toc) {
		stwuct SMU_DWAMData_TOC *toc;

		smu_data->toc = kzawwoc(sizeof(stwuct SMU_DWAMData_TOC), GFP_KEWNEW);
		if (!smu_data->toc)
			wetuwn -ENOMEM;
		toc = smu_data->toc;
		toc->num_entwies = 0;
		toc->stwuctuwe_vewsion = 1;

		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_WWC_G, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_CE, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_PFP, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_ME, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_MEC, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_MEC_JT1, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_CP_MEC_JT2, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_SDMA0, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_SDMA1, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
		if (!hwmgw->not_vf)
			PP_ASSEWT_WITH_CODE(0 == smu7_popuwate_singwe_fiwmwawe_entwy(hwmgw,
				UCODE_ID_MEC_STOWAGE, &toc->entwy[toc->num_entwies++]),
				"Faiwed to Get Fiwmwawe Entwy.", w = -EINVAW; goto faiwed);
	}
	memcpy_toio(smu_data->headew_buffew.kaddw, smu_data->toc,
		    sizeof(stwuct SMU_DWAMData_TOC));
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_DWV_DWAM_ADDW_HI,
			uppew_32_bits(smu_data->headew_buffew.mc_addw),
			NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_DWV_DWAM_ADDW_WO,
			wowew_32_bits(smu_data->headew_buffew.mc_addw),
			NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_WoadUcodes, fw_to_woad, NUWW);

	w = smu7_check_fw_woad_finish(hwmgw, fw_to_woad);
	if (!w)
		wetuwn 0;

	pw_eww("SMU woad fiwmwawe faiwed\n");

faiwed:
	kfwee(smu_data->toc);
	smu_data->toc = NUWW;
	wetuwn w;
}

/* Check if the FW has been woaded, SMU wiww not wetuwn if woading has not finished. */
int smu7_check_fw_woad_finish(stwuct pp_hwmgw *hwmgw, uint32_t fw_type)
{
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);
	uint32_t wet;

	wet = phm_wait_on_indiwect_wegistew(hwmgw, mmSMC_IND_INDEX_11,
					smu_data->soft_wegs_stawt + smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, UcodeWoadStatus),
					fw_type, fw_type);
	wetuwn wet;
}

int smu7_wewoad_fiwmwawe(stwuct pp_hwmgw *hwmgw)
{
	wetuwn hwmgw->smumgw_funcs->stawt_smu(hwmgw);
}

static int smu7_upwoad_smc_fiwmwawe_data(stwuct pp_hwmgw *hwmgw, uint32_t wength, uint32_t *swc, uint32_t wimit)
{
	uint32_t byte_count = wength;

	PP_ASSEWT_WITH_CODE((wimit >= byte_count), "SMC addwess is beyond the SMC WAM awea.", wetuwn -EINVAW);

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_INDEX_11, 0x20000);
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_11, 1);

	fow (; byte_count >= 4; byte_count -= 4)
		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_11, *swc++);

	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_11, 0);

	PP_ASSEWT_WITH_CODE((0 == byte_count), "SMC size must be divisibwe by 4.", wetuwn -EINVAW);

	wetuwn 0;
}


int smu7_upwoad_smu_fiwmwawe_image(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	stwuct cgs_fiwmwawe_info info = {0};

	if (smu_data->secuwity_hawd_key == 1)
		cgs_get_fiwmwawe_info(hwmgw->device,
			smu7_convewt_fw_type_to_cgs(UCODE_ID_SMU), &info);
	ewse
		cgs_get_fiwmwawe_info(hwmgw->device,
			smu7_convewt_fw_type_to_cgs(UCODE_ID_SMU_SK), &info);

	hwmgw->is_kickew = info.is_kickew;
	hwmgw->smu_vewsion = info.vewsion;
	wesuwt = smu7_upwoad_smc_fiwmwawe_data(hwmgw, info.image_size, (uint32_t *)info.kptw, SMU7_SMC_SIZE);

	wetuwn wesuwt;
}

static void execute_pww_tabwe(stwuct pp_hwmgw *hwmgw, const PWW_Command_Tabwe *pviwus, int size)
{
	int i;
	uint32_t weg, data;

	fow (i = 0; i < size; i++) {
		weg  = pviwus->weg;
		data = pviwus->data;
		if (weg != 0xffffffff)
			cgs_wwite_wegistew(hwmgw->device, weg, data);
		ewse
			bweak;
		pviwus++;
	}
}

static void execute_pww_dfy_tabwe(stwuct pp_hwmgw *hwmgw, const PWW_DFY_Section *section)
{
	int i;

	cgs_wwite_wegistew(hwmgw->device, mmCP_DFY_CNTW, section->dfy_cntw);
	cgs_wwite_wegistew(hwmgw->device, mmCP_DFY_ADDW_HI, section->dfy_addw_hi);
	cgs_wwite_wegistew(hwmgw->device, mmCP_DFY_ADDW_WO, section->dfy_addw_wo);
	fow (i = 0; i < section->dfy_size; i++)
		cgs_wwite_wegistew(hwmgw->device, mmCP_DFY_DATA_0, section->dfy_data[i]);
}

int smu7_setup_pww_viwus(stwuct pp_hwmgw *hwmgw)
{
	execute_pww_tabwe(hwmgw, pww_viwus_tabwe_pwe, AWWAY_SIZE(pww_viwus_tabwe_pwe));
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section1);
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section2);
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section3);
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section4);
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section5);
	execute_pww_dfy_tabwe(hwmgw, &pww_viwus_section6);
	execute_pww_tabwe(hwmgw, pww_viwus_tabwe_post, AWWAY_SIZE(pww_viwus_tabwe_post));

	wetuwn 0;
}

int smu7_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_smumgw *smu_data;
	int w;
	/* Awwocate memowy fow backend pwivate data */
	smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);
	smu_data->headew_buffew.data_size =
			((sizeof(stwuct SMU_DWAMData_TOC) / 4096) + 1) * 4096;

/* Awwocate FW image data stwuctuwe and headew buffew and
 * send the headew buffew addwess to SMU */
	w = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
		smu_data->headew_buffew.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VWAM,
		&smu_data->headew_buffew.handwe,
		&smu_data->headew_buffew.mc_addw,
		&smu_data->headew_buffew.kaddw);

	if (w)
		wetuwn -EINVAW;

	if (!hwmgw->not_vf)
		wetuwn 0;

	smu_data->smu_buffew.data_size = 200*4096;
	w = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
		smu_data->smu_buffew.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VWAM,
		&smu_data->smu_buffew.handwe,
		&smu_data->smu_buffew.mc_addw,
		&smu_data->smu_buffew.kaddw);

	if (w) {
		amdgpu_bo_fwee_kewnew(&smu_data->headew_buffew.handwe,
					&smu_data->headew_buffew.mc_addw,
					&smu_data->headew_buffew.kaddw);
		wetuwn -EINVAW;
	}

	if (smum_is_hw_avfs_pwesent(hwmgw) &&
	    (hwmgw->featuwe_mask & PP_AVFS_MASK))
		hwmgw->avfs_suppowted = twue;

	wetuwn 0;
}


int smu7_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	amdgpu_bo_fwee_kewnew(&smu_data->headew_buffew.handwe,
					&smu_data->headew_buffew.mc_addw,
					&smu_data->headew_buffew.kaddw);

	if (hwmgw->not_vf)
		amdgpu_bo_fwee_kewnew(&smu_data->smu_buffew.handwe,
					&smu_data->smu_buffew.mc_addw,
					&smu_data->smu_buffew.kaddw);


	kfwee(smu_data->toc);
	smu_data->toc = NUWW;
	kfwee(hwmgw->smu_backend);
	hwmgw->smu_backend = NUWW;
	wetuwn 0;
}
