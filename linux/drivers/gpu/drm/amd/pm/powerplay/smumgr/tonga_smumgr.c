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
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/gfp.h>

#incwude "smumgw.h"
#incwude "tonga_smumgw.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "tonga_ppsmc.h"
#incwude "smu/smu_7_1_2_d.h"
#incwude "smu/smu_7_1_2_sh_mask.h"
#incwude "cgs_common.h"
#incwude "smu7_smumgw.h"

#incwude "smu7_dyn_defauwts.h"

#incwude "smu7_hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "ppatomctww.h"

#incwude "atombios.h"

#incwude "pppciewanes.h"
#incwude "pp_endian.h"

#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#define POWEWTUNE_DEFAUWT_SET_MAX    1
#define MC_CG_AWB_FWEQ_F1           0x0b
#define VDDC_VDDCI_DEWTA            200


static const stwuct tonga_pt_defauwts tonga_powew_tune_data_set_awway[POWEWTUNE_DEFAUWT_SET_MAX] = {
/* sviWoadWIneEn, SviWoadWineVddC, TDC_VDDC_ThwottweWeweaseWimitPewc,  TDC_MAWt,
 * TdcWatewfawwCtw, DTEAmbientTempBase, DispwayCac,        BAPM_TEMP_GWADIENT
 */
	{1,               0xF,             0xFD,                0x19,
	 5,               45,                 0,              0xB0000,
	 {0x79, 0x253, 0x25D, 0xAE, 0x72, 0x80, 0x83, 0x86, 0x6F, 0xC8,
		0xC9, 0xC9, 0x2F, 0x4D, 0x61},
	 {0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203,
		0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4}
	},
};

/* [Fmin, Fmax, WDO_WEFSEW, USE_FOW_WOW_FWEQ] */
static const uint16_t tonga_cwock_stwetchew_wookup_tabwe[2][4] = {
	{600, 1050, 3, 0},
	{600, 1050, 6, 1}
};

/* [FF, SS] type, [] 4 vowtage wanges,
 * and [Fwoow Fweq, Boundawy Fweq, VID min , VID max]
 */
static const uint32_t tonga_cwock_stwetchew_ddt_tabwe[2][4][4] = {
	{ {265, 529, 120, 128}, {325, 650, 96, 119}, {430, 860, 32, 95}, {0, 0, 0, 31} },
	{ {275, 550, 104, 112}, {319, 638, 96, 103}, {360, 720, 64, 95}, {384, 768, 32, 63} }
};

/* [Use_Fow_Wow_fweq] vawue, [0%, 5%, 10%, 7.14%, 14.28%, 20%] */
static const uint8_t tonga_cwock_stwetch_amount_convewsion[2][6] = {
	{0, 1, 3, 2, 4, 5},
	{0, 2, 4, 5, 6, 5}
};

static int tonga_stawt_in_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;

	/* Assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);
	if (wesuwt)
		wetuwn wesuwt;

	/* Cweaw status */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
		ixSMU_STATUS, 0);

	/* Enabwe cwock */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	/* De-assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Set SMU Auto Stawt */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMU_INPUT_DATA, AUTO_STAWT, 1);

	/* Cweaw fiwmwawe intewwupt enabwe fwag */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
		ixFIWMWAWE_FWAGS, 0);

	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
		WCU_UC_EVENTS, INTEWWUPTS_ENABWED, 1);

	/**
	 * Caww Test SMU message with 0x20000 offset to twiggew SMU stawt
	 */
	smu7_send_msg_to_smc_offset(hwmgw);

	/* Wait fow done bit to be set */
	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
		SMU_STATUS, SMU_DONE, 0);

	/* Check pass/faiwed indicatow */
	if (1 != PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
				CGS_IND_WEG__SMC, SMU_STATUS, SMU_PASS)) {
		pw_eww("SMU Fiwmwawe stawt faiwed\n");
		wetuwn -EINVAW;
	}

	/* Wait fow fiwmwawe to initiawize */
	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
		FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn 0;
}

static int tonga_stawt_in_non_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	/* wait fow smc boot up */
	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
		WCU_UC_EVENTS, boot_seq_done, 0);

	/*Cweaw fiwmwawe intewwupt enabwe fwag*/
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
		ixFIWMWAWE_FWAGS, 0);


	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);

	if (wesuwt != 0)
		wetuwn wesuwt;

	/* Set smc instwuct stawt point at 0x0 */
	smu7_pwogwam_jump_on_stawt(hwmgw);


	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	/*De-assewt weset*/
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
		SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Wait fow fiwmwawe to initiawize */
	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
		FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn wesuwt;
}

static int tonga_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *pwiv = hwmgw->smu_backend;
	int wesuwt;

	/* Onwy stawt SMC if SMC WAM is not wunning */
	if (!smu7_is_smc_wam_wunning(hwmgw) && hwmgw->not_vf) {
		/*Check if SMU is wunning in pwotected mode*/
		if (0 == PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMU_FIWMWAWE, SMU_MODE)) {
			wesuwt = tonga_stawt_in_non_pwotection_mode(hwmgw);
			if (wesuwt)
				wetuwn wesuwt;
		} ewse {
			wesuwt = tonga_stawt_in_pwotection_mode(hwmgw);
			if (wesuwt)
				wetuwn wesuwt;
		}
	}

	/* Setup SoftWegsStawt hewe to visit the wegistew UcodeWoadStatus
	 * to check fw woading state
	 */
	smu7_wead_smc_swam_dwowd(hwmgw,
			SMU72_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU72_Fiwmwawe_Headew, SoftWegistews),
			&(pwiv->smu7_data.soft_wegs_stawt), 0x40000);

	wesuwt = smu7_wequest_smu_woad_fw(hwmgw);

	wetuwn wesuwt;
}

static int tonga_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *tonga_pwiv;

	tonga_pwiv = kzawwoc(sizeof(stwuct tonga_smumgw), GFP_KEWNEW);
	if (tonga_pwiv == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = tonga_pwiv;

	if (smu7_init(hwmgw)) {
		kfwee(tonga_pwiv);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static int tonga_get_dependency_vowt_by_cwk(stwuct pp_hwmgw *hwmgw,
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_cwock_vowtage_tabwe,
	uint32_t cwock, SMU_VowtageWevew *vowtage, uint32_t *mvdd)
{
	uint32_t i = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			   (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	/* cwock - vowtage dependency tabwe is empty tabwe */
	if (awwowed_cwock_vowtage_tabwe->count == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < awwowed_cwock_vowtage_tabwe->count; i++) {
		/* find fiwst scwk biggew than wequest */
		if (awwowed_cwock_vowtage_tabwe->entwies[i].cwk >= cwock) {
			vowtage->VddGfx = phm_get_vowtage_index(
					pptabwe_info->vddgfx_wookup_tabwe,
				awwowed_cwock_vowtage_tabwe->entwies[i].vddgfx);
			vowtage->Vddc = phm_get_vowtage_index(
						pptabwe_info->vddc_wookup_tabwe,
				  awwowed_cwock_vowtage_tabwe->entwies[i].vddc);

			if (awwowed_cwock_vowtage_tabwe->entwies[i].vddci)
				vowtage->Vddci =
					phm_get_vowtage_id(&data->vddci_vowtage_tabwe, awwowed_cwock_vowtage_tabwe->entwies[i].vddci);
			ewse
				vowtage->Vddci =
					phm_get_vowtage_id(&data->vddci_vowtage_tabwe,
						awwowed_cwock_vowtage_tabwe->entwies[i].vddc - VDDC_VDDCI_DEWTA);


			if (awwowed_cwock_vowtage_tabwe->entwies[i].mvdd)
				*mvdd = (uint32_t) awwowed_cwock_vowtage_tabwe->entwies[i].mvdd;

			vowtage->Phases = 1;
			wetuwn 0;
		}
	}

	/* scwk is biggew than max scwk in the dependence tabwe */
	vowtage->VddGfx = phm_get_vowtage_index(pptabwe_info->vddgfx_wookup_tabwe,
		awwowed_cwock_vowtage_tabwe->entwies[i-1].vddgfx);
	vowtage->Vddc = phm_get_vowtage_index(pptabwe_info->vddc_wookup_tabwe,
		awwowed_cwock_vowtage_tabwe->entwies[i-1].vddc);

	if (awwowed_cwock_vowtage_tabwe->entwies[i-1].vddci)
		vowtage->Vddci = phm_get_vowtage_id(&data->vddci_vowtage_tabwe,
			awwowed_cwock_vowtage_tabwe->entwies[i-1].vddci);

	if (awwowed_cwock_vowtage_tabwe->entwies[i-1].mvdd)
		*mvdd = (uint32_t) awwowed_cwock_vowtage_tabwe->entwies[i-1].mvdd;

	wetuwn 0;
}

static int tonga_popuwate_smc_vddc_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	unsigned int count;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
		tabwe->VddcWevewCount = data->vddc_vowtage_tabwe.count;
		fow (count = 0; count < tabwe->VddcWevewCount; count++) {
			tabwe->VddcTabwe[count] =
				PP_HOST_TO_SMC_US(data->vddc_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
		}
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddcWevewCount);
	}
	wetuwn 0;
}

static int tonga_popuwate_smc_vdd_gfx_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	unsigned int count;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vdd_gfx_contwow) {
		tabwe->VddGfxWevewCount = data->vddgfx_vowtage_tabwe.count;
		fow (count = 0; count < data->vddgfx_vowtage_tabwe.count; count++) {
			tabwe->VddGfxTabwe[count] =
				PP_HOST_TO_SMC_US(data->vddgfx_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
		}
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddGfxWevewCount);
	}
	wetuwn 0;
}

static int tonga_popuwate_smc_vdd_ci_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;

	tabwe->VddciWevewCount = data->vddci_vowtage_tabwe.count;
	fow (count = 0; count < tabwe->VddciWevewCount; count++) {
		if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow) {
			tabwe->VddciTabwe[count] =
				PP_HOST_TO_SMC_US(data->vddci_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
		} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
			tabwe->SmioTabwe1.Pattewn[count].Vowtage =
				PP_HOST_TO_SMC_US(data->vddci_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
			/* Index into DpmTabwe.Smio. Dwive bits fwom Smio entwy to get this vowtage wevew. */
			tabwe->SmioTabwe1.Pattewn[count].Smio =
				(uint8_t) count;
			tabwe->Smio[count] |=
				data->vddci_vowtage_tabwe.entwies[count].smio_wow;
			tabwe->VddciTabwe[count] =
				PP_HOST_TO_SMC_US(data->vddci_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
		}
	}

	tabwe->SmioMask1 = data->vddci_vowtage_tabwe.mask_wow;
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddciWevewCount);

	wetuwn 0;
}

static int tonga_popuwate_smc_mvdd_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		tabwe->MvddWevewCount = data->mvdd_vowtage_tabwe.count;
		fow (count = 0; count < tabwe->MvddWevewCount; count++) {
			tabwe->SmioTabwe2.Pattewn[count].Vowtage =
				PP_HOST_TO_SMC_US(data->mvdd_vowtage_tabwe.entwies[count].vawue * VOWTAGE_SCAWE);
			/* Index into DpmTabwe.Smio. Dwive bits fwom Smio entwy to get this vowtage wevew.*/
			tabwe->SmioTabwe2.Pattewn[count].Smio =
				(uint8_t) count;
			tabwe->Smio[count] |=
				data->mvdd_vowtage_tabwe.entwies[count].smio_wow;
		}
		tabwe->SmioMask2 = data->mvdd_vowtage_tabwe.mask_wow;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MvddWevewCount);
	}

	wetuwn 0;
}

static int tonga_popuwate_cac_tabwes(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	uint32_t count;
	uint8_t index = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddgfx_wookup_tabwe =
					   pptabwe_info->vddgfx_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddc_wookup_tabwe =
						pptabwe_info->vddc_wookup_tabwe;

	/* tabwe is awweady swapped, so in owdew to use the vawue fwom it
	 * we need to swap it back.
	 */
	uint32_t vddc_wevew_count = PP_SMC_TO_HOST_UW(tabwe->VddcWevewCount);
	uint32_t vddgfx_wevew_count = PP_SMC_TO_HOST_UW(tabwe->VddGfxWevewCount);

	fow (count = 0; count < vddc_wevew_count; count++) {
		/* We awe popuwating vddc CAC data to BapmVddc tabwe in spwit and mewged mode */
		index = phm_get_vowtage_index(vddc_wookup_tabwe,
			data->vddc_vowtage_tabwe.entwies[count].vawue);
		tabwe->BapmVddcVidWoSidd[count] =
			convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_wow);
		tabwe->BapmVddcVidHiSidd[count] =
			convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_mid);
		tabwe->BapmVddcVidHiSidd2[count] =
			convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_high);
	}

	if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		/* We awe popuwating vddgfx CAC data to BapmVddgfx tabwe in spwit mode */
		fow (count = 0; count < vddgfx_wevew_count; count++) {
			index = phm_get_vowtage_index(vddgfx_wookup_tabwe,
				convewt_to_vid(vddgfx_wookup_tabwe->entwies[index].us_cac_mid));
			tabwe->BapmVddGfxVidHiSidd2[count] =
				convewt_to_vid(vddgfx_wookup_tabwe->entwies[index].us_cac_high);
		}
	} ewse {
		fow (count = 0; count < vddc_wevew_count; count++) {
			index = phm_get_vowtage_index(vddc_wookup_tabwe,
				data->vddc_vowtage_tabwe.entwies[count].vawue);
			tabwe->BapmVddGfxVidWoSidd[count] =
				convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_wow);
			tabwe->BapmVddGfxVidHiSidd[count] =
				convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_mid);
			tabwe->BapmVddGfxVidHiSidd2[count] =
				convewt_to_vid(vddc_wookup_tabwe->entwies[index].us_cac_high);
		}
	}

	wetuwn 0;
}

static int tonga_popuwate_smc_vowtage_tabwes(stwuct pp_hwmgw *hwmgw,
	SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt;

	wesuwt = tonga_popuwate_smc_vddc_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"can not popuwate VDDC vowtage tabwe to SMC",
			wetuwn -EINVAW);

	wesuwt = tonga_popuwate_smc_vdd_ci_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"can not popuwate VDDCI vowtage tabwe to SMC",
			wetuwn -EINVAW);

	wesuwt = tonga_popuwate_smc_vdd_gfx_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"can not popuwate VDDGFX vowtage tabwe to SMC",
			wetuwn -EINVAW);

	wesuwt = tonga_popuwate_smc_mvdd_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"can not popuwate MVDD vowtage tabwe to SMC",
			wetuwn -EINVAW);

	wesuwt = tonga_popuwate_cac_tabwes(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"can not popuwate CAC vowtage tabwes to SMC",
			wetuwn -EINVAW);

	wetuwn 0;
}

static int tonga_popuwate_uwv_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU72_Discwete_Uwv *state)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	state->CcPwwDynWm = 0;
	state->CcPwwDynWm1 = 0;

	state->VddcOffset = (uint16_t) tabwe_info->us_uwv_vowtage_offset;
	state->VddcOffsetVid = (uint8_t)(tabwe_info->us_uwv_vowtage_offset *
			VOWTAGE_VID_OFFSET_SCAWE2 / VOWTAGE_VID_OFFSET_SCAWE1);

	state->VddcPhase = 1;

	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm1);
	CONVEWT_FWOM_HOST_TO_SMC_US(state->VddcOffset);

	wetuwn 0;
}

static int tonga_popuwate_uwv_state(stwuct pp_hwmgw *hwmgw,
		stwuct SMU72_Discwete_DpmTabwe *tabwe)
{
	wetuwn tonga_popuwate_uwv_wevew(hwmgw, &tabwe->Uwv);
}

static int tonga_popuwate_smc_wink_wevew(stwuct pp_hwmgw *hwmgw, SMU72_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t i;

	/* Index (dpm_tabwe->pcie_speed_tabwe.count) is wesewved fow PCIE boot wevew. */
	fow (i = 0; i <= dpm_tabwe->pcie_speed_tabwe.count; i++) {
		tabwe->WinkWevew[i].PcieGenSpeed  =
			(uint8_t)dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].vawue;
		tabwe->WinkWevew[i].PcieWaneCount =
			(uint8_t)encode_pcie_wane_width(dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].pawam1);
		tabwe->WinkWevew[i].EnabwedFowActivity =
			1;
		tabwe->WinkWevew[i].SPC =
			(uint8_t)(data->pcie_spc_cap & 0xff);
		tabwe->WinkWevew[i].DownThweshowd =
			PP_HOST_TO_SMC_UW(5);
		tabwe->WinkWevew[i].UpThweshowd =
			PP_HOST_TO_SMC_UW(30);
	}

	smu_data->smc_state_tabwe.WinkWevewCount =
		(uint8_t)dpm_tabwe->pcie_speed_tabwe.count;
	data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask =
		phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->pcie_speed_tabwe);

	wetuwn 0;
}

static int tonga_cawcuwate_scwk_pawams(stwuct pp_hwmgw *hwmgw,
		uint32_t engine_cwock, SMU72_Discwete_GwaphicsWevew *scwk)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	pp_atomctww_cwock_dividews_vi dividews;
	uint32_t spww_func_cntw            = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_3          = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3;
	uint32_t spww_func_cntw_4          = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4;
	uint32_t cg_spww_spwead_spectwum   = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM;
	uint32_t cg_spww_spwead_spectwum_2 = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2;
	uint32_t    wefewence_cwock;
	uint32_t wefewence_dividew;
	uint32_t fbdiv;
	int wesuwt;

	/* get the engine cwock dividews fow this cwock vawue*/
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw, engine_cwock,  &dividews);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.", wetuwn wesuwt);

	/* To get FBDIV we need to muwtipwy this by 16384 and divide it by Fwef.*/
	wefewence_cwock = atomctww_get_wefewence_cwock(hwmgw);

	wefewence_dividew = 1 + dividews.uc_pww_wef_div;

	/* wow 14 bits is fwaction and high 12 bits is dividew*/
	fbdiv = dividews.uw_fb_div.uw_fb_dividew & 0x3FFFFFF;

	/* SPWW_FUNC_CNTW setup*/
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw,
		CG_SPWW_FUNC_CNTW, SPWW_WEF_DIV, dividews.uc_pww_wef_div);
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw,
		CG_SPWW_FUNC_CNTW, SPWW_PDIV_A,  dividews.uc_pww_post_div);

	/* SPWW_FUNC_CNTW_3 setup*/
	spww_func_cntw_3 = PHM_SET_FIEWD(spww_func_cntw_3,
		CG_SPWW_FUNC_CNTW_3, SPWW_FB_DIV, fbdiv);

	/* set to use fwactionaw accumuwation*/
	spww_func_cntw_3 = PHM_SET_FIEWD(spww_func_cntw_3,
		CG_SPWW_FUNC_CNTW_3, SPWW_DITHEN, 1);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EngineSpweadSpectwumSuppowt)) {
		pp_atomctww_intewnaw_ss_info ss_info;

		uint32_t vcoFweq = engine_cwock * dividews.uc_pww_post_div;
		if (0 == atomctww_get_engine_cwock_spwead_spectwum(hwmgw, vcoFweq, &ss_info)) {
			/*
			* ss_info.speed_spectwum_pewcentage -- in unit of 0.01%
			* ss_info.speed_spectwum_wate -- in unit of khz
			*/
			/* cwks = wefewence_cwock * 10 / (WEFDIV + 1) / speed_spectwum_wate / 2 */
			uint32_t cwkS = wefewence_cwock * 5 / (wefewence_dividew * ss_info.speed_spectwum_wate);

			/* cwkv = 2 * D * fbdiv / NS */
			uint32_t cwkV = 4 * ss_info.speed_spectwum_pewcentage * fbdiv / (cwkS * 10000);

			cg_spww_spwead_spectwum =
				PHM_SET_FIEWD(cg_spww_spwead_spectwum, CG_SPWW_SPWEAD_SPECTWUM, CWKS, cwkS);
			cg_spww_spwead_spectwum =
				PHM_SET_FIEWD(cg_spww_spwead_spectwum, CG_SPWW_SPWEAD_SPECTWUM, SSEN, 1);
			cg_spww_spwead_spectwum_2 =
				PHM_SET_FIEWD(cg_spww_spwead_spectwum_2, CG_SPWW_SPWEAD_SPECTWUM_2, CWKV, cwkV);
		}
	}

	scwk->ScwkFwequency        = engine_cwock;
	scwk->CgSpwwFuncCntw3      = spww_func_cntw_3;
	scwk->CgSpwwFuncCntw4      = spww_func_cntw_4;
	scwk->SpwwSpweadSpectwum   = cg_spww_spwead_spectwum;
	scwk->SpwwSpweadSpectwum2  = cg_spww_spwead_spectwum_2;
	scwk->ScwkDid              = (uint8_t)dividews.pww_post_dividew;

	wetuwn 0;
}

static int tonga_popuwate_singwe_gwaphic_wevew(stwuct pp_hwmgw *hwmgw,
						uint32_t engine_cwock,
				SMU72_Discwete_GwaphicsWevew *gwaphic_wevew)
{
	int wesuwt;
	uint32_t mvdd;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			    (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;

	wesuwt = tonga_cawcuwate_scwk_pawams(hwmgw, engine_cwock, gwaphic_wevew);

	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_scwk;
	ewse
		vdd_dep_tabwe = pptabwe_info->vdd_dep_on_scwk;

	/* popuwate gwaphics wevews*/
	wesuwt = tonga_get_dependency_vowt_by_cwk(hwmgw,
		vdd_dep_tabwe, engine_cwock,
		&gwaphic_wevew->MinVowtage, &mvdd);
	PP_ASSEWT_WITH_CODE((!wesuwt),
		"can not find VDDC vowtage vawue fow VDDC "
		"engine cwock dependency tabwe", wetuwn wesuwt);

	/* SCWK fwequency in units of 10KHz*/
	gwaphic_wevew->ScwkFwequency = engine_cwock;
	/* Indicates maximum activity wevew fow this pewfowmance wevew. 50% fow now*/
	gwaphic_wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.scwk_activity;

	gwaphic_wevew->CcPwwDynWm = 0;
	gwaphic_wevew->CcPwwDynWm1 = 0;
	/* this wevew can be used if activity is high enough.*/
	gwaphic_wevew->EnabwedFowActivity = 0;
	/* this wevew can be used fow thwottwing.*/
	gwaphic_wevew->EnabwedFowThwottwe = 1;
	gwaphic_wevew->UpHyst = data->cuwwent_pwofiwe_setting.scwk_up_hyst;
	gwaphic_wevew->DownHyst = data->cuwwent_pwofiwe_setting.scwk_down_hyst;
	gwaphic_wevew->VowtageDownHyst = 0;
	gwaphic_wevew->PowewThwottwe = 0;

	data->dispway_timing.min_cwock_in_sw =
			hwmgw->dispway_config->min_cowe_set_cwock_in_sw;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkDeepSweep))
		gwaphic_wevew->DeepSweepDivId =
				smu7_get_sweep_dividew_id_fwom_cwock(engine_cwock,
						data->dispway_timing.min_cwock_in_sw);

	/* Defauwt to swow, highest DPM wevew wiww be set to PPSMC_DISPWAY_WATEWMAWK_WOW watew.*/
	gwaphic_wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	if (!wesuwt) {
		/* CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->MinVowtage);*/
		/* CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->MinVddcPhases);*/
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->ScwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(gwaphic_wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->CgSpwwFuncCntw3);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->CgSpwwFuncCntw4);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->SpwwSpweadSpectwum);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->SpwwSpweadSpectwum2);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->CcPwwDynWm);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->CcPwwDynWm1);
	}

	wetuwn wesuwt;
}

static int tonga_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info = (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe = pptabwe_info->pcie_tabwe;
	uint8_t pcie_entwy_count = (uint8_t) data->dpm_tabwe.pcie_speed_tabwe.count;
	uint32_t wevew_awway_addwess = smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU72_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t wevew_awway_size = sizeof(SMU72_Discwete_GwaphicsWevew) *
						SMU72_MAX_WEVEWS_GWAPHICS;

	SMU72_Discwete_GwaphicsWevew *wevews = smu_data->smc_state_tabwe.GwaphicsWevew;

	uint32_t i, max_entwy;
	uint8_t highest_pcie_wevew_enabwed = 0;
	uint8_t wowest_pcie_wevew_enabwed = 0, mid_pcie_wevew_enabwed = 0;
	uint8_t count = 0;
	int wesuwt = 0;

	memset(wevews, 0x00, wevew_awway_size);

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
		wesuwt = tonga_popuwate_singwe_gwaphic_wevew(hwmgw,
					dpm_tabwe->scwk_tabwe.dpm_wevews[i].vawue,
					&(smu_data->smc_state_tabwe.GwaphicsWevew[i]));
		if (wesuwt != 0)
			wetuwn wesuwt;

		/* Making suwe onwy DPM wevew 0-1 have Deep Sweep Div ID popuwated. */
		if (i > 1)
			smu_data->smc_state_tabwe.GwaphicsWevew[i].DeepSweepDivId = 0;
	}

	/* Onwy enabwe wevew 0 fow now. */
	smu_data->smc_state_tabwe.GwaphicsWevew[0].EnabwedFowActivity = 1;

	/* set highest wevew watewmawk to high */
	if (dpm_tabwe->scwk_tabwe.count > 1)
		smu_data->smc_state_tabwe.GwaphicsWevew[dpm_tabwe->scwk_tabwe.count-1].DispwayWatewmawk =
			PPSMC_DISPWAY_WATEWMAWK_HIGH;

	smu_data->smc_state_tabwe.GwaphicsDpmWevewCount =
		(uint8_t)dpm_tabwe->scwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask =
		phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->scwk_tabwe);

	if (pcie_tabwe != NUWW) {
		PP_ASSEWT_WITH_CODE((pcie_entwy_count >= 1),
			"Thewe must be 1 ow mowe PCIE wevews defined in PPTabwe.",
			wetuwn -EINVAW);
		max_entwy = pcie_entwy_count - 1; /* fow indexing, we need to decwement by 1.*/
		fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
			smu_data->smc_state_tabwe.GwaphicsWevew[i].pcieDpmWevew =
				(uint8_t) ((i < max_entwy) ? i : max_entwy);
		}
	} ewse {
		if (0 == data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask)
			pw_eww("Pcie Dpm Enabwemask is 0 !");

		whiwe (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
					(1<<(highest_pcie_wevew_enabwed+1))) != 0)) {
			highest_pcie_wevew_enabwed++;
		}

		whiwe (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
					(1<<wowest_pcie_wevew_enabwed)) == 0)) {
			wowest_pcie_wevew_enabwed++;
		}

		whiwe ((count < highest_pcie_wevew_enabwed) &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
					(1<<(wowest_pcie_wevew_enabwed+1+count))) == 0)) {
			count++;
		}
		mid_pcie_wevew_enabwed = (wowest_pcie_wevew_enabwed+1+count) < highest_pcie_wevew_enabwed ?
			(wowest_pcie_wevew_enabwed+1+count) : highest_pcie_wevew_enabwed;


		/* set pcieDpmWevew to highest_pcie_wevew_enabwed*/
		fow (i = 2; i < dpm_tabwe->scwk_tabwe.count; i++)
			smu_data->smc_state_tabwe.GwaphicsWevew[i].pcieDpmWevew = highest_pcie_wevew_enabwed;

		/* set pcieDpmWevew to wowest_pcie_wevew_enabwed*/
		smu_data->smc_state_tabwe.GwaphicsWevew[0].pcieDpmWevew = wowest_pcie_wevew_enabwed;

		/* set pcieDpmWevew to mid_pcie_wevew_enabwed*/
		smu_data->smc_state_tabwe.GwaphicsWevew[1].pcieDpmWevew = mid_pcie_wevew_enabwed;
	}
	/* wevew count wiww send to smc once at init smc tabwe and nevew change*/
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, wevew_awway_addwess,
				(uint8_t *)wevews, (uint32_t)wevew_awway_size,
								SMC_WAM_END);

	wetuwn wesuwt;
}

static int tonga_cawcuwate_mcwk_pawams(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU72_Discwete_MemowyWevew *mcwk,
		boow stwobe_mode,
		boow dwwStateOn
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t dww_cntw = data->cwock_wegistews.vDWW_CNTW;
	uint32_t mcwk_pwwmgt_cntw = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;
	uint32_t mpww_ad_func_cntw = data->cwock_wegistews.vMPWW_AD_FUNC_CNTW;
	uint32_t mpww_dq_func_cntw = data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW;
	uint32_t mpww_func_cntw = data->cwock_wegistews.vMPWW_FUNC_CNTW;
	uint32_t mpww_func_cntw_1 = data->cwock_wegistews.vMPWW_FUNC_CNTW_1;
	uint32_t mpww_func_cntw_2 = data->cwock_wegistews.vMPWW_FUNC_CNTW_2;
	uint32_t mpww_ss1 = data->cwock_wegistews.vMPWW_SS1;
	uint32_t mpww_ss2 = data->cwock_wegistews.vMPWW_SS2;

	pp_atomctww_memowy_cwock_pawam mpww_pawam;
	int wesuwt;

	wesuwt = atomctww_get_memowy_pww_dividews_si(hwmgw,
				memowy_cwock, &mpww_pawam, stwobe_mode);
	PP_ASSEWT_WITH_CODE(
			!wesuwt,
			"Ewwow wetwieving Memowy Cwock Pawametews fwom VBIOS.",
			wetuwn wesuwt);

	/* MPWW_FUNC_CNTW setup*/
	mpww_func_cntw = PHM_SET_FIEWD(mpww_func_cntw, MPWW_FUNC_CNTW, BWCTWW,
					mpww_pawam.bw_ctww);

	/* MPWW_FUNC_CNTW_1 setup*/
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
					MPWW_FUNC_CNTW_1, CWKF,
					mpww_pawam.mpww_fb_dividew.cw_kf);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
					MPWW_FUNC_CNTW_1, CWKFWAC,
					mpww_pawam.mpww_fb_dividew.cwk_fwac);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
						MPWW_FUNC_CNTW_1, VCO_MODE,
						mpww_pawam.vco_mode);

	/* MPWW_AD_FUNC_CNTW setup*/
	mpww_ad_func_cntw = PHM_SET_FIEWD(mpww_ad_func_cntw,
					MPWW_AD_FUNC_CNTW, YCWK_POST_DIV,
					mpww_pawam.mpww_post_dividew);

	if (data->is_memowy_gddw5) {
		/* MPWW_DQ_FUNC_CNTW setup*/
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
						MPWW_DQ_FUNC_CNTW, YCWK_SEW,
						mpww_pawam.ycwk_sew);
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
						MPWW_DQ_FUNC_CNTW, YCWK_POST_DIV,
						mpww_pawam.mpww_post_dividew);
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MemowySpweadSpectwumSuppowt)) {
		/*
		 ************************************
		 Fwef = Wefewence Fwequency
		 NF = Feedback dividew watio
		 NW = Wefewence dividew watio
		 Fnom = Nominaw VCO output fwequency = Fwef * NF / NW
		 Fs = Spweading Wate
		 D = Pewcentage down-spwead / 2
		 Fint = Wefewence input fwequency to PFD = Fwef / NW
		 NS = Spweading wate dividew watio = int(Fint / (2 * Fs))
		 CWKS = NS - 1 = ISS_STEP_NUM[11:0]
		 NV = D * Fs / Fnom * 4 * ((Fnom/Fwef * NW) ^ 2)
		 CWKV = 65536 * NV = ISS_STEP_SIZE[25:0]
		 *************************************
		 */
		pp_atomctww_intewnaw_ss_info ss_info;
		uint32_t fweq_nom;
		uint32_t tmp;
		uint32_t wefewence_cwock = atomctww_get_mpww_wefewence_cwock(hwmgw);

		/* fow GDDW5 fow aww modes and DDW3 */
		if (1 == mpww_pawam.qdw)
			fweq_nom = memowy_cwock * 4 * (1 << mpww_pawam.mpww_post_dividew);
		ewse
			fweq_nom = memowy_cwock * 2 * (1 << mpww_pawam.mpww_post_dividew);

		/* tmp = (fweq_nom / wefewence_cwock * wefewence_dividew) ^ 2  Note: S.I. wefewence_dividew = 1*/
		tmp = (fweq_nom / wefewence_cwock);
		tmp = tmp * tmp;

		if (0 == atomctww_get_memowy_cwock_spwead_spectwum(hwmgw, fweq_nom, &ss_info)) {
			/* ss_info.speed_spectwum_pewcentage -- in unit of 0.01% */
			/* ss.Info.speed_spectwum_wate -- in unit of khz */
			/* CWKS = wefewence_cwock / (2 * speed_spectwum_wate * wefewence_dividew) * 10 */
			/*     = wefewence_cwock * 5 / speed_spectwum_wate */
			uint32_t cwks = wefewence_cwock * 5 / ss_info.speed_spectwum_wate;

			/* CWKV = 65536 * speed_spectwum_pewcentage / 2 * spweadSpecwumWate / fweq_nom * 4 / 100000 * ((fweq_nom / wefewence_cwock) ^ 2) */
			/*     = 131 * speed_spectwum_pewcentage * speed_spectwum_wate / 100 * ((fweq_nom / wefewence_cwock) ^ 2) / fweq_nom */
			uint32_t cwkv =
				(uint32_t)((((131 * ss_info.speed_spectwum_pewcentage *
							ss_info.speed_spectwum_wate) / 100) * tmp) / fweq_nom);

			mpww_ss1 = PHM_SET_FIEWD(mpww_ss1, MPWW_SS1, CWKV, cwkv);
			mpww_ss2 = PHM_SET_FIEWD(mpww_ss2, MPWW_SS2, CWKS, cwks);
		}
	}

	/* MCWK_PWWMGT_CNTW setup */
	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, DWW_SPEED, mpww_pawam.dww_speed);
	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_PDNB, dwwStateOn);
	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_PDNB, dwwStateOn);

	/* Save the wesuwt data to outpupt memowy wevew stwuctuwe */
	mcwk->McwkFwequency   = memowy_cwock;
	mcwk->MpwwFuncCntw    = mpww_func_cntw;
	mcwk->MpwwFuncCntw_1  = mpww_func_cntw_1;
	mcwk->MpwwFuncCntw_2  = mpww_func_cntw_2;
	mcwk->MpwwAdFuncCntw  = mpww_ad_func_cntw;
	mcwk->MpwwDqFuncCntw  = mpww_dq_func_cntw;
	mcwk->McwkPwwmgtCntw  = mcwk_pwwmgt_cntw;
	mcwk->DwwCntw         = dww_cntw;
	mcwk->MpwwSs1         = mpww_ss1;
	mcwk->MpwwSs2         = mpww_ss2;

	wetuwn 0;
}

static uint8_t tonga_get_mcwk_fwequency_watio(uint32_t memowy_cwock,
		boow stwobe_mode)
{
	uint8_t mc_pawa_index;

	if (stwobe_mode) {
		if (memowy_cwock < 12500)
			mc_pawa_index = 0x00;
		ewse if (memowy_cwock > 47500)
			mc_pawa_index = 0x0f;
		ewse
			mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 2500);
	} ewse {
		if (memowy_cwock < 65000)
			mc_pawa_index = 0x00;
		ewse if (memowy_cwock > 135000)
			mc_pawa_index = 0x0f;
		ewse
			mc_pawa_index = (uint8_t)((memowy_cwock - 60000) / 5000);
	}

	wetuwn mc_pawa_index;
}

static uint8_t tonga_get_ddw3_mcwk_fwequency_watio(uint32_t memowy_cwock)
{
	uint8_t mc_pawa_index;

	if (memowy_cwock < 10000)
		mc_pawa_index = 0;
	ewse if (memowy_cwock >= 80000)
		mc_pawa_index = 0x0f;
	ewse
		mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 5000 + 1);

	wetuwn mc_pawa_index;
}


static int tonga_popuwate_singwe_memowy_wevew(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU72_Discwete_MemowyWevew *memowy_wevew
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			  (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t mcwk_edc_ww_enabwe_thweshowd = 40000;
	uint32_t mcwk_stuttew_mode_thweshowd = 30000;
	uint32_t mcwk_edc_enabwe_thweshowd = 40000;
	uint32_t mcwk_stwobe_mode_thweshowd = 40000;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;
	int wesuwt = 0;
	boow dww_state_on;
	uint32_t mvdd = 0;

	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_mcwk;
	ewse
		vdd_dep_tabwe = pptabwe_info->vdd_dep_on_mcwk;

	if (NUWW != vdd_dep_tabwe) {
		wesuwt = tonga_get_dependency_vowt_by_cwk(hwmgw,
				vdd_dep_tabwe,
				memowy_cwock,
				&memowy_wevew->MinVowtage, &mvdd);
		PP_ASSEWT_WITH_CODE(
			!wesuwt,
			"can not find MinVddc vowtage vawue fwom memowy VDDC "
			"vowtage dependency tabwe",
			wetuwn wesuwt);
	}

	if (data->mvdd_contwow == SMU7_VOWTAGE_CONTWOW_NONE)
		memowy_wevew->MinMvdd = data->vbios_boot_state.mvdd_bootup_vawue;
	ewse
		memowy_wevew->MinMvdd = mvdd;

	memowy_wevew->EnabwedFowThwottwe = 1;
	memowy_wevew->EnabwedFowActivity = 0;
	memowy_wevew->UpHyst = data->cuwwent_pwofiwe_setting.mcwk_up_hyst;
	memowy_wevew->DownHyst = data->cuwwent_pwofiwe_setting.mcwk_down_hyst;
	memowy_wevew->VowtageDownHyst = 0;

	/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
	memowy_wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.mcwk_activity;
	memowy_wevew->StuttewEnabwe = 0;
	memowy_wevew->StwobeEnabwe = 0;
	memowy_wevew->EdcWeadEnabwe = 0;
	memowy_wevew->EdcWwiteEnabwe = 0;
	memowy_wevew->WttEnabwe = 0;

	/* defauwt set to wow watewmawk. Highest wevew wiww be set to high watew.*/
	memowy_wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	data->dispway_timing.num_existing_dispways = hwmgw->dispway_config->num_dispway;
	data->dispway_timing.vwefwesh = hwmgw->dispway_config->vwefwesh;

	if ((mcwk_stuttew_mode_thweshowd != 0) &&
	    (memowy_cwock <= mcwk_stuttew_mode_thweshowd) &&
	    (!data->is_uvd_enabwed)
	    && (PHM_WEAD_FIEWD(hwmgw->device, DPG_PIPE_STUTTEW_CONTWOW, STUTTEW_ENABWE) & 0x1)
	    && (data->dispway_timing.num_existing_dispways <= 2)
	    && (data->dispway_timing.num_existing_dispways != 0))
		memowy_wevew->StuttewEnabwe = 1;

	/* decide stwobe mode*/
	memowy_wevew->StwobeEnabwe = (mcwk_stwobe_mode_thweshowd != 0) &&
		(memowy_cwock <= mcwk_stwobe_mode_thweshowd);

	/* decide EDC mode and memowy cwock watio*/
	if (data->is_memowy_gddw5) {
		memowy_wevew->StwobeWatio = tonga_get_mcwk_fwequency_watio(memowy_cwock,
					memowy_wevew->StwobeEnabwe);

		if ((mcwk_edc_enabwe_thweshowd != 0) &&
				(memowy_cwock > mcwk_edc_enabwe_thweshowd)) {
			memowy_wevew->EdcWeadEnabwe = 1;
		}

		if ((mcwk_edc_ww_enabwe_thweshowd != 0) &&
				(memowy_cwock > mcwk_edc_ww_enabwe_thweshowd)) {
			memowy_wevew->EdcWwiteEnabwe = 1;
		}

		if (memowy_wevew->StwobeEnabwe) {
			if (tonga_get_mcwk_fwequency_watio(memowy_cwock, 1) >=
					((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC7) >> 16) & 0xf)) {
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
			} ewse {
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC6) >> 1) & 0x1) ? 1 : 0;
			}

		} ewse {
			dww_state_on = data->dww_defauwt_on;
		}
	} ewse {
		memowy_wevew->StwobeWatio =
			tonga_get_ddw3_mcwk_fwequency_watio(memowy_cwock);
		dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
	}

	wesuwt = tonga_cawcuwate_mcwk_pawams(hwmgw,
		memowy_cwock, memowy_wevew, memowy_wevew->StwobeEnabwe, dww_state_on);

	if (!wesuwt) {
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MinMvdd);
		/* MCWK fwequency in units of 10KHz*/
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->McwkFwequency);
		/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
		CONVEWT_FWOM_HOST_TO_SMC_US(memowy_wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw_1);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw_2);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwAdFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwDqFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->McwkPwwmgtCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->DwwCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwSs1);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwSs2);
	}

	wetuwn wesuwt;
}

static int tonga_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data =
			(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	int wesuwt;

	/* popuwate MCWK dpm tabwe to SMU7 */
	uint32_t wevew_awway_addwess =
				smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU72_Discwete_DpmTabwe, MemowyWevew);
	uint32_t wevew_awway_size =
				sizeof(SMU72_Discwete_MemowyWevew) *
				SMU72_MAX_WEVEWS_MEMOWY;
	SMU72_Discwete_MemowyWevew *wevews =
				smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;

	memset(wevews, 0x00, wevew_awway_size);

	fow (i = 0; i < dpm_tabwe->mcwk_tabwe.count; i++) {
		PP_ASSEWT_WITH_CODE((0 != dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue),
			"can not popuwate memowy wevew as memowy cwock is zewo",
			wetuwn -EINVAW);
		wesuwt = tonga_popuwate_singwe_memowy_wevew(
				hwmgw,
				dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue,
				&(smu_data->smc_state_tabwe.MemowyWevew[i]));
		if (wesuwt)
			wetuwn wesuwt;
	}

	/* Onwy enabwe wevew 0 fow now.*/
	smu_data->smc_state_tabwe.MemowyWevew[0].EnabwedFowActivity = 1;

	/*
	* in owdew to pwevent MC activity fwom stuttew mode to push DPM up.
	* the UVD change compwements this by putting the MCWK in a highew state
	* by defauwt such that we awe not effected by up thweshowd ow and MCWK DPM watency.
	*/
	smu_data->smc_state_tabwe.MemowyWevew[0].ActivityWevew = 0x1F;
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.MemowyWevew[0].ActivityWevew);

	smu_data->smc_state_tabwe.MemowyDpmWevewCount = (uint8_t)dpm_tabwe->mcwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask = phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->mcwk_tabwe);
	/* set highest wevew watewmawk to high*/
	smu_data->smc_state_tabwe.MemowyWevew[dpm_tabwe->mcwk_tabwe.count-1].DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_HIGH;

	/* wevew count wiww send to smc once at init smc tabwe and nevew change*/
	wesuwt = smu7_copy_bytes_to_smc(hwmgw,
		wevew_awway_addwess, (uint8_t *)wevews, (uint32_t)wevew_awway_size,
		SMC_WAM_END);

	wetuwn wesuwt;
}

static int tonga_popuwate_mvdd_vawue(stwuct pp_hwmgw *hwmgw,
				uint32_t mcwk, SMIO_Pattewn *smio_pattewn)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t i = 0;

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->mvdd_contwow) {
		/* find mvdd vawue which cwock is mowe than wequest */
		fow (i = 0; i < tabwe_info->vdd_dep_on_mcwk->count; i++) {
			if (mcwk <= tabwe_info->vdd_dep_on_mcwk->entwies[i].cwk) {
				/* Awways wound to highew vowtage. */
				smio_pattewn->Vowtage =
				      data->mvdd_vowtage_tabwe.entwies[i].vawue;
				bweak;
			}
		}

		PP_ASSEWT_WITH_CODE(i < tabwe_info->vdd_dep_on_mcwk->count,
			"MVDD Vowtage is outside the suppowted wange.",
			wetuwn -EINVAW);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static int tonga_popuwate_smc_acpi_wevew(stwuct pp_hwmgw *hwmgw,
	SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct pp_atomctww_cwock_dividews_vi dividews;

	SMIO_Pattewn vowtage_wevew;
	uint32_t spww_func_cntw    = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_2  = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_2;
	uint32_t dww_cntw          = data->cwock_wegistews.vDWW_CNTW;
	uint32_t mcwk_pwwmgt_cntw  = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;

	/* The ACPI state shouwd not do DPM on DC (ow evew).*/
	tabwe->ACPIWevew.Fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	tabwe->ACPIWevew.MinVowtage =
			smu_data->smc_state_tabwe.GwaphicsWevew[0].MinVowtage;

	/* assign zewo fow now*/
	tabwe->ACPIWevew.ScwkFwequency = atomctww_get_wefewence_cwock(hwmgw);

	/* get the engine cwock dividews fow this cwock vawue*/
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw,
		tabwe->ACPIWevew.ScwkFwequency,  &dividews);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.",
		wetuwn wesuwt);

	/* dividew ID fow wequiwed SCWK*/
	tabwe->ACPIWevew.ScwkDid = (uint8_t)dividews.pww_post_dividew;
	tabwe->ACPIWevew.DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;
	tabwe->ACPIWevew.DeepSweepDivId = 0;

	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
					SPWW_PWWON, 0);
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
						SPWW_WESET, 1);
	spww_func_cntw_2 = PHM_SET_FIEWD(spww_func_cntw_2, CG_SPWW_FUNC_CNTW_2,
						SCWK_MUX_SEW, 4);

	tabwe->ACPIWevew.CgSpwwFuncCntw = spww_func_cntw;
	tabwe->ACPIWevew.CgSpwwFuncCntw2 = spww_func_cntw_2;
	tabwe->ACPIWevew.CgSpwwFuncCntw3 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3;
	tabwe->ACPIWevew.CgSpwwFuncCntw4 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4;
	tabwe->ACPIWevew.SpwwSpweadSpectwum = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM;
	tabwe->ACPIWevew.SpwwSpweadSpectwum2 = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2;
	tabwe->ACPIWevew.CcPwwDynWm = 0;
	tabwe->ACPIWevew.CcPwwDynWm1 = 0;


	/* Fow vawious featuwes to be enabwed/disabwed whiwe this wevew is active.*/
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.Fwags);
	/* SCWK fwequency in units of 10KHz*/
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw3);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw4);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm1);

	/* tabwe->MemowyACPIWevew.MinVddcPhases = tabwe->ACPIWevew.MinVddcPhases;*/
	tabwe->MemowyACPIWevew.MinVowtage =
			    smu_data->smc_state_tabwe.MemowyWevew[0].MinVowtage;

	/*  CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MemowyACPIWevew.MinVowtage);*/

	if (0 == tonga_popuwate_mvdd_vawue(hwmgw, 0, &vowtage_wevew))
		tabwe->MemowyACPIWevew.MinMvdd =
			PP_HOST_TO_SMC_UW(vowtage_wevew.Vowtage * VOWTAGE_SCAWE);
	ewse
		tabwe->MemowyACPIWevew.MinMvdd = 0;

	/* Fowce weset on DWW*/
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_WESET, 0x1);
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_WESET, 0x1);

	/* Disabwe DWW in ACPIState*/
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_PDNB, 0);
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_PDNB, 0);

	/* Enabwe DWW bypass signaw*/
	dww_cntw            = PHM_SET_FIEWD(dww_cntw,
		DWW_CNTW, MWDCK0_BYPASS, 0);
	dww_cntw            = PHM_SET_FIEWD(dww_cntw,
		DWW_CNTW, MWDCK1_BYPASS, 0);

	tabwe->MemowyACPIWevew.DwwCntw            =
		PP_HOST_TO_SMC_UW(dww_cntw);
	tabwe->MemowyACPIWevew.McwkPwwmgtCntw     =
		PP_HOST_TO_SMC_UW(mcwk_pwwmgt_cntw);
	tabwe->MemowyACPIWevew.MpwwAdFuncCntw     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_AD_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwDqFuncCntw     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwFuncCntw       =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwFuncCntw_1     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW_1);
	tabwe->MemowyACPIWevew.MpwwFuncCntw_2     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW_2);
	tabwe->MemowyACPIWevew.MpwwSs1            =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_SS1);
	tabwe->MemowyACPIWevew.MpwwSs2            =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_SS2);

	tabwe->MemowyACPIWevew.EnabwedFowThwottwe = 0;
	tabwe->MemowyACPIWevew.EnabwedFowActivity = 0;
	tabwe->MemowyACPIWevew.UpHyst = 0;
	tabwe->MemowyACPIWevew.DownHyst = 100;
	tabwe->MemowyACPIWevew.VowtageDownHyst = 0;
	/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
	tabwe->MemowyACPIWevew.ActivityWevew =
			PP_HOST_TO_SMC_US(data->cuwwent_pwofiwe_setting.mcwk_activity);

	tabwe->MemowyACPIWevew.StuttewEnabwe = 0;
	tabwe->MemowyACPIWevew.StwobeEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWeadEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWwiteEnabwe = 0;
	tabwe->MemowyACPIWevew.WttEnabwe = 0;

	wetuwn wesuwt;
}

static int tonga_popuwate_smc_uvd_wevew(stwuct pp_hwmgw *hwmgw,
					SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;

	uint8_t count;
	pp_atomctww_cwock_dividews_vi dividews;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
				(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
						pptabwe_info->mm_dep_tabwe;

	tabwe->UvdWevewCount = (uint8_t) (mm_tabwe->count);
	tabwe->UvdBootWevew = 0;

	fow (count = 0; count < tabwe->UvdWevewCount; count++) {
		tabwe->UvdWevew[count].VcwkFwequency = mm_tabwe->entwies[count].vcwk;
		tabwe->UvdWevew[count].DcwkFwequency = mm_tabwe->entwies[count].dcwk;
		tabwe->UvdWevew[count].MinVowtage.Vddc =
			phm_get_vowtage_index(pptabwe_info->vddc_wookup_tabwe,
						mm_tabwe->entwies[count].vddc);
		tabwe->UvdWevew[count].MinVowtage.VddGfx =
			(data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) ?
			phm_get_vowtage_index(pptabwe_info->vddgfx_wookup_tabwe,
						mm_tabwe->entwies[count].vddgfx) : 0;
		tabwe->UvdWevew[count].MinVowtage.Vddci =
			phm_get_vowtage_id(&data->vddci_vowtage_tabwe,
					     mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		tabwe->UvdWevew[count].MinVowtage.Phases = 1;

		/* wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(
					hwmgw,
					tabwe->UvdWevew[count].VcwkFwequency,
					&dividews);

		PP_ASSEWT_WITH_CODE((!wesuwt),
				    "can not find divide id fow Vcwk cwock",
					wetuwn wesuwt);

		tabwe->UvdWevew[count].VcwkDividew = (uint8_t)dividews.pww_post_dividew;

		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
							  tabwe->UvdWevew[count].DcwkFwequency, &dividews);
		PP_ASSEWT_WITH_CODE((!wesuwt),
				    "can not find divide id fow Dcwk cwock",
					wetuwn wesuwt);

		tabwe->UvdWevew[count].DcwkDividew =
					(uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->UvdWevew[count].VcwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->UvdWevew[count].DcwkFwequency);
	}

	wetuwn wesuwt;

}

static int tonga_popuwate_smc_vce_wevew(stwuct pp_hwmgw *hwmgw,
		SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;

	uint8_t count;
	pp_atomctww_cwock_dividews_vi dividews;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			      (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
						     pptabwe_info->mm_dep_tabwe;

	tabwe->VceWevewCount = (uint8_t) (mm_tabwe->count);
	tabwe->VceBootWevew = 0;

	fow (count = 0; count < tabwe->VceWevewCount; count++) {
		tabwe->VceWevew[count].Fwequency =
			mm_tabwe->entwies[count].ecwk;
		tabwe->VceWevew[count].MinVowtage.Vddc =
			phm_get_vowtage_index(pptabwe_info->vddc_wookup_tabwe,
				mm_tabwe->entwies[count].vddc);
		tabwe->VceWevew[count].MinVowtage.VddGfx =
			(data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) ?
			phm_get_vowtage_index(pptabwe_info->vddgfx_wookup_tabwe,
				mm_tabwe->entwies[count].vddgfx) : 0;
		tabwe->VceWevew[count].MinVowtage.Vddci =
			phm_get_vowtage_id(&data->vddci_vowtage_tabwe,
				mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		tabwe->VceWevew[count].MinVowtage.Phases = 1;

		/* wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
					tabwe->VceWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((!wesuwt),
				"can not find divide id fow VCE engine cwock",
				wetuwn wesuwt);

		tabwe->VceWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VceWevew[count].Fwequency);
	}

	wetuwn wesuwt;
}

static int tonga_popuwate_smc_acp_wevew(stwuct pp_hwmgw *hwmgw,
		SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	uint8_t count;
	pp_atomctww_cwock_dividews_vi dividews;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info =
			     (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
						    pptabwe_info->mm_dep_tabwe;

	tabwe->AcpWevewCount = (uint8_t) (mm_tabwe->count);
	tabwe->AcpBootWevew = 0;

	fow (count = 0; count < tabwe->AcpWevewCount; count++) {
		tabwe->AcpWevew[count].Fwequency =
			pptabwe_info->mm_dep_tabwe->entwies[count].acwk;
		tabwe->AcpWevew[count].MinVowtage.Vddc =
			phm_get_vowtage_index(pptabwe_info->vddc_wookup_tabwe,
			mm_tabwe->entwies[count].vddc);
		tabwe->AcpWevew[count].MinVowtage.VddGfx =
			(data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) ?
			phm_get_vowtage_index(pptabwe_info->vddgfx_wookup_tabwe,
				mm_tabwe->entwies[count].vddgfx) : 0;
		tabwe->AcpWevew[count].MinVowtage.Vddci =
			phm_get_vowtage_id(&data->vddci_vowtage_tabwe,
				mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		tabwe->AcpWevew[count].MinVowtage.Phases = 1;

		/* wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
			tabwe->AcpWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((!wesuwt),
			"can not find divide id fow engine cwock", wetuwn wesuwt);

		tabwe->AcpWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->AcpWevew[count].Fwequency);
	}

	wetuwn wesuwt;
}

static int tonga_popuwate_memowy_timing_pawametews(
		stwuct pp_hwmgw *hwmgw,
		uint32_t engine_cwock,
		uint32_t memowy_cwock,
		stwuct SMU72_Discwete_MCAwbDwamTimingTabweEntwy *awb_wegs
		)
{
	uint32_t dwamTiming;
	uint32_t dwamTiming2;
	uint32_t buwstTime;
	int wesuwt;

	wesuwt = atomctww_set_engine_dwam_timings_wv770(hwmgw,
				engine_cwock, memowy_cwock);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow cawwing VBIOS to set DWAM_TIMING.", wetuwn wesuwt);

	dwamTiming  = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING);
	dwamTiming2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2);
	buwstTime = PHM_WEAD_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE0);

	awb_wegs->McAwbDwamTiming  = PP_HOST_TO_SMC_UW(dwamTiming);
	awb_wegs->McAwbDwamTiming2 = PP_HOST_TO_SMC_UW(dwamTiming2);
	awb_wegs->McAwbBuwstTime = (uint8_t)buwstTime;

	wetuwn 0;
}

static int tonga_pwogwam_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	int wesuwt = 0;
	SMU72_Discwete_MCAwbDwamTimingTabwe  awb_wegs;
	uint32_t i, j;

	memset(&awb_wegs, 0x00, sizeof(SMU72_Discwete_MCAwbDwamTimingTabwe));

	fow (i = 0; i < data->dpm_tabwe.scwk_tabwe.count; i++) {
		fow (j = 0; j < data->dpm_tabwe.mcwk_tabwe.count; j++) {
			wesuwt = tonga_popuwate_memowy_timing_pawametews
				(hwmgw, data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue,
				 data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue,
				 &awb_wegs.entwies[i][j]);

			if (wesuwt)
				bweak;
		}
	}

	if (!wesuwt) {
		wesuwt = smu7_copy_bytes_to_smc(
				hwmgw,
				smu_data->smu7_data.awb_tabwe_stawt,
				(uint8_t *)&awb_wegs,
				sizeof(SMU72_Discwete_MCAwbDwamTimingTabwe),
				SMC_WAM_END
				);
	}

	wetuwn wesuwt;
}

static int tonga_popuwate_smc_boot_wevew(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	/* find boot wevew fwom dpm tabwe*/
	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.scwk_tabwe),
	data->vbios_boot_state.scwk_bootup_vawue,
	(uint32_t *)&(smu_data->smc_state_tabwe.GwaphicsBootWevew));

	if (wesuwt != 0) {
		smu_data->smc_state_tabwe.GwaphicsBootWevew = 0;
		pw_eww("[powewpway] VBIOS did not find boot engine "
				"cwock vawue in dependency tabwe. "
				"Using Gwaphics DPM wevew 0 !");
		wesuwt = 0;
	}

	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.mcwk_tabwe),
		data->vbios_boot_state.mcwk_bootup_vawue,
		(uint32_t *)&(smu_data->smc_state_tabwe.MemowyBootWevew));

	if (wesuwt != 0) {
		smu_data->smc_state_tabwe.MemowyBootWevew = 0;
		pw_eww("[powewpway] VBIOS did not find boot "
				"engine cwock vawue in dependency tabwe."
				"Using Memowy DPM wevew 0 !");
		wesuwt = 0;
	}

	tabwe->BootVowtage.Vddc =
		phm_get_vowtage_id(&(data->vddc_vowtage_tabwe),
			data->vbios_boot_state.vddc_bootup_vawue);
	tabwe->BootVowtage.VddGfx =
		phm_get_vowtage_id(&(data->vddgfx_vowtage_tabwe),
			data->vbios_boot_state.vddgfx_bootup_vawue);
	tabwe->BootVowtage.Vddci =
		phm_get_vowtage_id(&(data->vddci_vowtage_tabwe),
			data->vbios_boot_state.vddci_bootup_vawue);
	tabwe->BootMVdd = data->vbios_boot_state.mvdd_bootup_vawue;

	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->BootMVdd);

	wetuwn wesuwt;
}

static int tonga_popuwate_cwock_stwetchew_data_tabwe(stwuct pp_hwmgw *hwmgw)
{
	uint32_t wo, efuse, efuse2, cwock_fweq, vowt_without_cks,
			vowt_with_cks, vawue;
	uint16_t cwock_fweq_u16;
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint8_t type, i, j, cks_setting, stwetch_amount, stwetch_amount2,
			vowt_offset = 0;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;
	uint32_t hw_wevision, dev_id;
	stwuct amdgpu_device *adev = hwmgw->adev;

	stwetch_amount = (uint8_t)tabwe_info->cac_dtp_tabwe->usCwockStwetchAmount;

	hw_wevision = adev->pdev->wevision;
	dev_id = adev->pdev->device;

	/* Wead SMU_Eefuse to wead and cawcuwate WO and detewmine
	 * if the pawt is SS ow FF. if WO >= 1660MHz, pawt is FF.
	 */
	efuse = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixSMU_EFUSE_0 + (146 * 4));
	efuse2 = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixSMU_EFUSE_0 + (148 * 4));
	efuse &= 0xFF000000;
	efuse = efuse >> 24;
	efuse2 &= 0xF;

	if (efuse2 == 1)
		wo = (2300 - 1350) * efuse / 255 + 1350;
	ewse
		wo = (2500 - 1000) * efuse / 255 + 1000;

	if (wo >= 1660)
		type = 0;
	ewse
		type = 1;

	/* Popuwate Stwetch amount */
	smu_data->smc_state_tabwe.CwockStwetchewAmount = stwetch_amount;


	/* Popuwate Scwk_CKS_mastewEn0_7 and Scwk_vowtageOffset */
	fow (i = 0; i < scwk_tabwe->count; i++) {
		smu_data->smc_state_tabwe.Scwk_CKS_mastewEn0_7 |=
				scwk_tabwe->entwies[i].cks_enabwe << i;
		if (ASICID_IS_TONGA_P(dev_id, hw_wevision)) {
			vowt_without_cks = (uint32_t)((7732 + 60 - wo - 20838 *
				(scwk_tabwe->entwies[i].cwk/100) / 10000) * 1000 /
				(8730 - (5301 * (scwk_tabwe->entwies[i].cwk/100) / 1000)));
			vowt_with_cks = (uint32_t)((5250 + 51 - wo - 2404 *
				(scwk_tabwe->entwies[i].cwk/100) / 100000) * 1000 /
				(6146 - (3193 * (scwk_tabwe->entwies[i].cwk/100) / 1000)));
		} ewse {
			vowt_without_cks = (uint32_t)((14041 *
				(scwk_tabwe->entwies[i].cwk/100) / 10000 + 3571 + 75 - wo) * 1000 /
				(4026 - (13924 * (scwk_tabwe->entwies[i].cwk/100) / 10000)));
			vowt_with_cks = (uint32_t)((13946 *
				(scwk_tabwe->entwies[i].cwk/100) / 10000 + 3320 + 45 - wo) * 1000 /
				(3664 - (11454 * (scwk_tabwe->entwies[i].cwk/100) / 10000)));
		}
		if (vowt_without_cks >= vowt_with_cks)
			vowt_offset = (uint8_t)(((vowt_without_cks - vowt_with_cks +
					scwk_tabwe->entwies[i].cks_voffset) * 100 / 625) + 1);
		smu_data->smc_state_tabwe.Scwk_vowtageOffset[i] = vowt_offset;
	}

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			STWETCH_ENABWE, 0x0);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			mastewWeset, 0x1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			staticEnabwe, 0x1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			mastewWeset, 0x0);

	/* Popuwate CKS Wookup Tabwe */
	if (stwetch_amount == 1 || stwetch_amount == 2 || stwetch_amount == 5)
		stwetch_amount2 = 0;
	ewse if (stwetch_amount == 3 || stwetch_amount == 4)
		stwetch_amount2 = 1;
	ewse {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_CwockStwetchew);
		PP_ASSEWT_WITH_CODE(fawse,
				"Stwetch Amount in PPTabwe not suppowted",
				wetuwn -EINVAW);
	}

	vawue = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixPWW_CKS_CNTW);
	vawue &= 0xFFC2FF87;
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].minFweq =
			tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][0];
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].maxFweq =
			tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][1];
	cwock_fweq_u16 = (uint16_t)(PP_SMC_TO_HOST_UW(smu_data->smc_state_tabwe.
			GwaphicsWevew[smu_data->smc_state_tabwe.GwaphicsDpmWevewCount - 1].
			ScwkFwequency) / 100);
	if (tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][0] <
			cwock_fweq_u16 &&
	    tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][1] >
			cwock_fweq_u16) {
		/* Pwogwam PWW_CKS_CNTW. CKS_USE_FOW_WOW_FWEQ */
		vawue |= (tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]) << 16;
		/* Pwogwam PWW_CKS_CNTW. CKS_WDO_WEFSEW */
		vawue |= (tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][2]) << 18;
		/* Pwogwam PWW_CKS_CNTW. CKS_STWETCH_AMOUNT */
		vawue |= (tonga_cwock_stwetch_amount_convewsion
				[tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]]
				 [stwetch_amount]) << 3;
	}
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.
			CKS_WOOKUPTabweEntwy[0].minFweq);
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.
			CKS_WOOKUPTabweEntwy[0].maxFweq);
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].setting =
			tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][2] & 0x7F;
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].setting |=
			(tonga_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]) << 7;

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixPWW_CKS_CNTW, vawue);

	/* Popuwate DDT Wookup Tabwe */
	fow (i = 0; i < 4; i++) {
		/* Assign the minimum and maximum VID stowed
		 * in the wast wow of Cwock Stwetchew Vowtage Tabwe.
		 */
		smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
		CwockStwetchewDataTabweEntwy[i].minVID =
				(uint8_t) tonga_cwock_stwetchew_ddt_tabwe[type][i][2];
		smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
		CwockStwetchewDataTabweEntwy[i].maxVID =
				(uint8_t) tonga_cwock_stwetchew_ddt_tabwe[type][i][3];
		/* Woop thwough each SCWK and check the fwequency
		 * to see if it wies within the fwequency fow cwock stwetchew.
		 */
		fow (j = 0; j < smu_data->smc_state_tabwe.GwaphicsDpmWevewCount; j++) {
			cks_setting = 0;
			cwock_fweq = PP_SMC_TO_HOST_UW(
					smu_data->smc_state_tabwe.GwaphicsWevew[j].ScwkFwequency);
			/* Check the awwowed fwequency against the scwk wevew[j].
			 *  Scwk's endianness has awweady been convewted,
			 *  and it's in 10Khz unit,
			 *  as opposed to Data tabwe, which is in Mhz unit.
			 */
			if (cwock_fweq >= tonga_cwock_stwetchew_ddt_tabwe[type][i][0] * 100) {
				cks_setting |= 0x2;
				if (cwock_fweq < tonga_cwock_stwetchew_ddt_tabwe[type][i][1] * 100)
					cks_setting |= 0x1;
			}
			smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
			CwockStwetchewDataTabweEntwy[i].setting |= cks_setting << (j * 2);
		}
		CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.
				CwockStwetchewDataTabwe.
				CwockStwetchewDataTabweEntwy[i].setting);
	}

	vawue = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					ixPWW_CKS_CNTW);
	vawue &= 0xFFFFFFFE;
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					ixPWW_CKS_CNTW, vawue);

	wetuwn 0;
}

static int tonga_popuwate_vw_config(stwuct pp_hwmgw *hwmgw,
			SMU72_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint16_t config;

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vdd_gfx_contwow) {
		/*  Spwitted mode */
		config = VW_SVI2_PWANE_1;
		tabwe->VWConfig |= (config<<VWCONF_VDDGFX_SHIFT);

		if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
			config = VW_SVI2_PWANE_2;
			tabwe->VWConfig |= config;
		} ewse {
			pw_eww("VDDC and VDDGFX shouwd "
				"be both on SVI2 contwow in spwitted mode !\n");
		}
	} ewse {
		/* Mewged mode  */
		config = VW_MEWGED_WITH_VDDC;
		tabwe->VWConfig |= (config<<VWCONF_VDDGFX_SHIFT);

		/* Set Vddc Vowtage Contwowwew  */
		if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
			config = VW_SVI2_PWANE_1;
			tabwe->VWConfig |= config;
		} ewse {
			pw_eww("VDDC shouwd be on "
					"SVI2 contwow in mewged mode !\n");
		}
	}

	/* Set Vddci Vowtage Contwowwew  */
	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow) {
		config = VW_SVI2_PWANE_2;  /* onwy in mewged mode */
		tabwe->VWConfig |= (config<<VWCONF_VDDCI_SHIFT);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
		config = VW_SMIO_PATTEWN_1;
		tabwe->VWConfig |= (config<<VWCONF_VDDCI_SHIFT);
	}

	/* Set Mvdd Vowtage Contwowwew */
	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		config = VW_SMIO_PATTEWN_2;
		tabwe->VWConfig |= (config<<VWCONF_MVDD_SHIFT);
	}

	wetuwn 0;
}

static int tonga_init_awb_tabwe_index(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t tmp;
	int wesuwt;

	/*
	* This is a wead-modify-wwite on the fiwst byte of the AWB tabwe.
	* The fiwst byte in the SMU72_Discwete_MCAwbDwamTimingTabwe stwuctuwe
	* is the fiewd 'cuwwent'.
	* This sowution is ugwy, but we nevew wwite the whowe tabwe onwy
	* individuaw fiewds in it.
	* In weawity this fiewd shouwd not be in that stwuctuwe
	* but in a soft wegistew.
	*/
	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				smu_data->smu7_data.awb_tabwe_stawt, &tmp, SMC_WAM_END);

	if (wesuwt != 0)
		wetuwn wesuwt;

	tmp &= 0x00FFFFFF;
	tmp |= ((uint32_t)MC_CG_AWB_FWEQ_F1) << 24;

	wetuwn smu7_wwite_smc_swam_dwowd(hwmgw,
			smu_data->smu7_data.awb_tabwe_stawt, tmp, SMC_WAM_END);
}


static int tonga_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	const stwuct tonga_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	SMU72_Discwete_DpmTabwe  *dpm_tabwe = &(smu_data->smc_state_tabwe);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe = tabwe_info->cac_dtp_tabwe;
	int  i, j, k;
	const uint16_t *pdef1, *pdef2;

	dpm_tabwe->DefauwtTdp = PP_HOST_TO_SMC_US(
			(uint16_t)(cac_dtp_tabwe->usTDP * 256));
	dpm_tabwe->TawgetTdp = PP_HOST_TO_SMC_US(
			(uint16_t)(cac_dtp_tabwe->usConfiguwabweTDP * 256));

	PP_ASSEWT_WITH_CODE(cac_dtp_tabwe->usTawgetOpewatingTemp <= 255,
			"Tawget Opewating Temp is out of Wange !",
			);

	dpm_tabwe->GpuTjMax = (uint8_t)(cac_dtp_tabwe->usTawgetOpewatingTemp);
	dpm_tabwe->GpuTjHyst = 8;

	dpm_tabwe->DTEAmbientTempBase = defauwts->dte_ambient_temp_base;

	dpm_tabwe->BAPM_TEMP_GWADIENT =
				PP_HOST_TO_SMC_UW(defauwts->bapm_temp_gwadient);
	pdef1 = defauwts->bapmti_w;
	pdef2 = defauwts->bapmti_wc;

	fow (i = 0; i < SMU72_DTE_ITEWATIONS; i++) {
		fow (j = 0; j < SMU72_DTE_SOUWCES; j++) {
			fow (k = 0; k < SMU72_DTE_SINKS; k++) {
				dpm_tabwe->BAPMTI_W[i][j][k] =
						PP_HOST_TO_SMC_US(*pdef1);
				dpm_tabwe->BAPMTI_WC[i][j][k] =
						PP_HOST_TO_SMC_US(*pdef2);
				pdef1++;
				pdef2++;
			}
		}
	}

	wetuwn 0;
}

static int tonga_popuwate_svi_woad_wine(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	const stwuct tonga_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	smu_data->powew_tune_tabwe.SviWoadWineEn = defauwts->svi_woad_wine_en;
	smu_data->powew_tune_tabwe.SviWoadWineVddC = defauwts->svi_woad_wine_vddC;
	smu_data->powew_tune_tabwe.SviWoadWineTwimVddC = 3;
	smu_data->powew_tune_tabwe.SviWoadWineOffsetVddC = 0;

	wetuwn 0;
}

static int tonga_popuwate_tdc_wimit(stwuct pp_hwmgw *hwmgw)
{
	uint16_t tdc_wimit;
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	const stwuct tonga_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	/* TDC numbew of fwaction bits awe changed fwom 8 to 7
	 * fow Fiji as wequested by SMC team
	 */
	tdc_wimit = (uint16_t)(tabwe_info->cac_dtp_tabwe->usTDC * 256);
	smu_data->powew_tune_tabwe.TDC_VDDC_PkgWimit =
			CONVEWT_FWOM_HOST_TO_SMC_US(tdc_wimit);
	smu_data->powew_tune_tabwe.TDC_VDDC_ThwottweWeweaseWimitPewc =
			defauwts->tdc_vddc_thwottwe_wewease_wimit_pewc;
	smu_data->powew_tune_tabwe.TDC_MAWt = defauwts->tdc_mawt;

	wetuwn 0;
}

static int tonga_popuwate_dw8(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	stwuct tonga_smumgw *smu_data =
			(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	const stwuct tonga_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	uint32_t temp;

	if (smu7_wead_smc_swam_dwowd(hwmgw,
			fuse_tabwe_offset +
			offsetof(SMU72_Discwete_PmFuses, TdcWatewfawwCtw),
			(uint32_t *)&temp, SMC_WAM_END))
		PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to wead PmFuses.DW6 "
				"(SviWoadWineEn) fwom SMC Faiwed !",
				wetuwn -EINVAW);
	ewse
		smu_data->powew_tune_tabwe.TdcWatewfawwCtw = defauwts->tdc_watewfaww_ctw;

	wetuwn 0;
}

static int tonga_popuwate_tempewatuwe_scawew(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.WPMWTempewatuweScawew[i] = 0;

	wetuwn 0;
}

static int tonga_popuwate_fuzzy_fan(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);

	if ((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
			usFanOutputSensitivity & (1 << 15)) ||
		(hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity == 0))
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
		usFanOutputSensitivity = hwmgw->thewmaw_contwowwew.
			advanceFanContwowPawametews.usDefauwtFanOutputSensitivity;

	smu_data->powew_tune_tabwe.FuzzyFan_PwmSetDewta =
			PP_HOST_TO_SMC_US(hwmgw->thewmaw_contwowwew.
					advanceFanContwowPawametews.usFanOutputSensitivity);
	wetuwn 0;
}

static int tonga_popuwate_gnb_wpmw(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.GnbWPMW[i] = 0;

	wetuwn 0;
}

static int tonga_popuwate_bapm_vddc_base_weakage_sidd(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint16_t hi_sidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd;
	uint16_t wo_sidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd;
	stwuct phm_cac_tdp_tabwe *cac_tabwe = tabwe_info->cac_dtp_tabwe;

	hi_sidd = (uint16_t)(cac_tabwe->usHighCACWeakage / 100 * 256);
	wo_sidd = (uint16_t)(cac_tabwe->usWowCACWeakage / 100 * 256);

	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(hi_sidd);
	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(wo_sidd);

	wetuwn 0;
}

static int tonga_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t pm_fuse_tabwe_offset;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment)) {
		if (smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, PmFuseTabwe),
				&pm_fuse_tabwe_offset, SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to get pm_fuse_tabwe_offset Faiwed !",
				wetuwn -EINVAW);

		/* DW6 */
		if (tonga_popuwate_svi_woad_wine(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to popuwate SviWoadWine Faiwed !",
				wetuwn -EINVAW);
		/* DW7 */
		if (tonga_popuwate_tdc_wimit(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TDCWimit Faiwed !",
					wetuwn -EINVAW);
		/* DW8 */
		if (tonga_popuwate_dw8(hwmgw, pm_fuse_tabwe_offset))
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to popuwate TdcWatewfawwCtw Faiwed !",
				wetuwn -EINVAW);

		/* DW9-DW12 */
		if (tonga_popuwate_tempewatuwe_scawew(hwmgw) != 0)
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to popuwate WPMWTempewatuweScawew Faiwed !",
				wetuwn -EINVAW);

		/* DW13-DW14 */
		if (tonga_popuwate_fuzzy_fan(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to popuwate Fuzzy Fan "
				"Contwow pawametews Faiwed !",
				wetuwn -EINVAW);

		/* DW15-DW18 */
		if (tonga_popuwate_gnb_wpmw(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to popuwate GnbWPMW Faiwed !",
				wetuwn -EINVAW);

		/* DW20 */
		if (tonga_popuwate_bapm_vddc_base_weakage_sidd(hwmgw))
			PP_ASSEWT_WITH_CODE(
				fawse,
				"Attempt to popuwate BapmVddCBaseWeakage "
				"Hi and Wo Sidd Faiwed !",
				wetuwn -EINVAW);

		if (smu7_copy_bytes_to_smc(hwmgw, pm_fuse_tabwe_offset,
				(uint8_t *)&smu_data->powew_tune_tabwe,
				sizeof(stwuct SMU72_Discwete_PmFuses), SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to downwoad PmFuseTabwe Faiwed !",
					wetuwn -EINVAW);
	}
	wetuwn 0;
}

static int tonga_popuwate_mc_weg_addwess(stwuct pp_hwmgw *hwmgw,
				 SMU72_Discwete_MCWegistews *mc_weg_tabwe)
{
	const stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)hwmgw->smu_backend;

	uint32_t i, j;

	fow (i = 0, j = 0; j < smu_data->mc_weg_tabwe.wast; j++) {
		if (smu_data->mc_weg_tabwe.vawidfwag & 1<<j) {
			PP_ASSEWT_WITH_CODE(
				i < SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE,
				"Index of mc_weg_tabwe->addwess[] awway "
				"out of boundawy",
				wetuwn -EINVAW);
			mc_weg_tabwe->addwess[i].s0 =
				PP_HOST_TO_SMC_US(smu_data->mc_weg_tabwe.mc_weg_addwess[j].s0);
			mc_weg_tabwe->addwess[i].s1 =
				PP_HOST_TO_SMC_US(smu_data->mc_weg_tabwe.mc_weg_addwess[j].s1);
			i++;
		}
	}

	mc_weg_tabwe->wast = (uint8_t)i;

	wetuwn 0;
}

/*convewt wegistew vawues fwom dwivew to SMC fowmat */
static void tonga_convewt_mc_wegistews(
	const stwuct tonga_mc_weg_entwy *entwy,
	SMU72_Discwete_MCWegistewSet *data,
	uint32_t num_entwies, uint32_t vawid_fwag)
{
	uint32_t i, j;

	fow (i = 0, j = 0; j < num_entwies; j++) {
		if (vawid_fwag & 1<<j) {
			data->vawue[i] = PP_HOST_TO_SMC_UW(entwy->mc_data[j]);
			i++;
		}
	}
}

static int tonga_convewt_mc_weg_tabwe_entwy_to_smc(
		stwuct pp_hwmgw *hwmgw,
		const uint32_t memowy_cwock,
		SMU72_Discwete_MCWegistewSet *mc_weg_tabwe_data
		)
{
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t i = 0;

	fow (i = 0; i < smu_data->mc_weg_tabwe.num_entwies; i++) {
		if (memowy_cwock <=
			smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max) {
			bweak;
		}
	}

	if ((i == smu_data->mc_weg_tabwe.num_entwies) && (i > 0))
		--i;

	tonga_convewt_mc_wegistews(&smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i],
				mc_weg_tabwe_data, smu_data->mc_weg_tabwe.wast,
				smu_data->mc_weg_tabwe.vawidfwag);

	wetuwn 0;
}

static int tonga_convewt_mc_weg_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
		SMU72_Discwete_MCWegistews *mc_wegs)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wes;
	uint32_t i;

	fow (i = 0; i < data->dpm_tabwe.mcwk_tabwe.count; i++) {
		wes = tonga_convewt_mc_weg_tabwe_entwy_to_smc(
				hwmgw,
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[i].vawue,
				&mc_wegs->data[i]
				);

		if (0 != wes)
			wesuwt = wes;
	}

	wetuwn wesuwt;
}

static int tonga_update_and_upwoad_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t addwess;
	int32_t wesuwt;

	if (0 == (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_MCWK))
		wetuwn 0;


	memset(&smu_data->mc_wegs, 0, sizeof(SMU72_Discwete_MCWegistews));

	wesuwt = tonga_convewt_mc_weg_tabwe_to_smc(hwmgw, &(smu_data->mc_wegs));

	if (wesuwt != 0)
		wetuwn wesuwt;


	addwess = smu_data->smu7_data.mc_weg_tabwe_stawt +
			(uint32_t)offsetof(SMU72_Discwete_MCWegistews, data[0]);

	wetuwn  smu7_copy_bytes_to_smc(
			hwmgw, addwess,
			(uint8_t *)&smu_data->mc_wegs.data[0],
			sizeof(SMU72_Discwete_MCWegistewSet) *
			data->dpm_tabwe.mcwk_tabwe.count,
			SMC_WAM_END);
}

static int tonga_popuwate_initiaw_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);

	memset(&smu_data->mc_wegs, 0x00, sizeof(SMU72_Discwete_MCWegistews));
	wesuwt = tonga_popuwate_mc_weg_addwess(hwmgw, &(smu_data->mc_wegs));
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize MCWegTabwe fow the MC wegistew addwesses !",
		wetuwn wesuwt;);

	wesuwt = tonga_convewt_mc_weg_tabwe_to_smc(hwmgw, &smu_data->mc_wegs);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize MCWegTabwe fow dwivew state !",
		wetuwn wesuwt;);

	wetuwn smu7_copy_bytes_to_smc(hwmgw, smu_data->smu7_data.mc_weg_tabwe_stawt,
			(uint8_t *)&smu_data->mc_wegs, sizeof(SMU72_Discwete_MCWegistews), SMC_WAM_END);
}

static void tonga_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	stwuct  phm_ppt_v1_infowmation *tabwe_info =
			(stwuct  phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (tabwe_info &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID <= POWEWTUNE_DEFAUWT_SET_MAX &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID)
		smu_data->powew_tune_defauwts =
				&tonga_powew_tune_data_set_awway
				[tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID - 1];
	ewse
		smu_data->powew_tune_defauwts = &tonga_powew_tune_data_set_awway[0];
}

static int tonga_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data =
			(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	SMU72_Discwete_DpmTabwe *tabwe = &(smu_data->smc_state_tabwe);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	uint8_t i;
	pp_atomctww_gpio_pin_assignment gpio_pin_assignment;


	memset(&(smu_data->smc_state_tabwe), 0x00, sizeof(smu_data->smc_state_tabwe));

	tonga_initiawize_powew_tune_defauwts(hwmgw);

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->vowtage_contwow)
		tonga_popuwate_smc_vowtage_tabwes(hwmgw, tabwe);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;


	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StepVddc))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (data->is_memowy_gddw5)
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	i = PHM_WEAD_FIEWD(hwmgw->device, CC_MC_MAX_CHANNEW, NOOFCHAN);

	if (i == 1 || i == 0)
		tabwe->SystemFwags |= 0x40;

	if (data->uwv_suppowted && tabwe_info->us_uwv_vowtage_offset) {
		wesuwt = tonga_popuwate_uwv_state(hwmgw, tabwe);
		PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to initiawize UWV state !",
			wetuwn wesuwt;);

		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixCG_UWV_PAWAMETEW, 0x40035);
	}

	wesuwt = tonga_popuwate_smc_wink_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize Wink Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_aww_gwaphic_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize Gwaphics Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_aww_memowy_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize Memowy Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_smc_acpi_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize ACPI Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_smc_vce_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize VCE Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_smc_acp_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize ACP Wevew !", wetuwn wesuwt);

	/* Since onwy the initiaw state is compwetewy set up at this
	* point (the othew states awe just copies of the boot state) we onwy
	* need to popuwate the  AWB settings fow the initiaw state.
	*/
	wesuwt = tonga_pwogwam_memowy_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to Wwite AWB settings fow the initiaw state.",
		wetuwn wesuwt;);

	wesuwt = tonga_popuwate_smc_uvd_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize UVD Wevew !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_smc_boot_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to initiawize Boot Wevew !", wetuwn wesuwt);

	tonga_popuwate_bapm_pawametews_in_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to popuwate BAPM Pawametews !", wetuwn wesuwt);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_CwockStwetchew)) {
		wesuwt = tonga_popuwate_cwock_stwetchew_data_tabwe(hwmgw);
		PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to popuwate Cwock Stwetchew Data Tabwe !",
			wetuwn wesuwt;);
	}
	tabwe->GwaphicsVowtageChangeEnabwe  = 1;
	tabwe->GwaphicsThewmThwottweEnabwe  = 1;
	tabwe->GwaphicsIntewvaw = 1;
	tabwe->VowtageIntewvaw  = 1;
	tabwe->ThewmawIntewvaw  = 1;
	tabwe->TempewatuweWimitHigh =
		tabwe_info->cac_dtp_tabwe->usTawgetOpewatingTemp *
		SMU7_Q88_FOWMAT_CONVEWSION_UNIT;
	tabwe->TempewatuweWimitWow =
		(tabwe_info->cac_dtp_tabwe->usTawgetOpewatingTemp - 1) *
		SMU7_Q88_FOWMAT_CONVEWSION_UNIT;
	tabwe->MemowyVowtageChangeEnabwe  = 1;
	tabwe->MemowyIntewvaw  = 1;
	tabwe->VowtageWesponseTime  = 0;
	tabwe->PhaseWesponseTime  = 0;
	tabwe->MemowyThewmThwottweEnabwe  = 1;

	/*
	* Caiw weads cuwwent wink status and wepowts it as cap (we cannot
	* change this due to some pwevious issues we had)
	* SMC dwops the wink status to wowest wevew aftew enabwing
	* DPM by PowewPway. Aftew pnp ow toggwing CF, dwivew gets wewoaded again
	* but this time Caiw weads cuwwent wink status which was set to wow by
	* SMC and wepowts it as cap to powewpway
	* To avoid it, we set PCIeBootWinkWevew to highest dpm wevew
	*/
	PP_ASSEWT_WITH_CODE((1 <= data->dpm_tabwe.pcie_speed_tabwe.count),
			"Thewe must be 1 ow mowe PCIE wevews defined in PPTabwe.",
			wetuwn -EINVAW);

	tabwe->PCIeBootWinkWevew = (uint8_t) (data->dpm_tabwe.pcie_speed_tabwe.count);

	tabwe->PCIeGenIntewvaw  = 1;

	wesuwt = tonga_popuwate_vw_config(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to popuwate VWConfig setting !", wetuwn wesuwt);
	data->vw_config = tabwe->VWConfig;
	tabwe->ThewmGpio  = 17;
	tabwe->ScwkStepSize = 0x4000;

	if (atomctww_get_pp_assign_pin(hwmgw, VDDC_VWHOT_GPIO_PINID,
						&gpio_pin_assignment)) {
		tabwe->VWHotGpio = gpio_pin_assignment.uc_gpio_pin_bit_shift;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_WeguwatowHot);
	} ewse {
		tabwe->VWHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_WeguwatowHot);
	}

	if (atomctww_get_pp_assign_pin(hwmgw, PP_AC_DC_SWITCH_GPIO_PINID,
						&gpio_pin_assignment)) {
		tabwe->AcDcGpio = gpio_pin_assignment.uc_gpio_pin_bit_shift;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition);
	} ewse {
		tabwe->AcDcGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition);
	}

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
		PHM_PwatfowmCaps_Fawcon_QuickTwansition);

	if (0) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition);
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_Fawcon_QuickTwansition);
	}

	if (atomctww_get_pp_assign_pin(hwmgw,
			THEWMAW_INT_OUTPUT_GPIO_PINID, &gpio_pin_assignment)) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawOutGPIO);

		tabwe->ThewmOutGpio = gpio_pin_assignment.uc_gpio_pin_bit_shift;

		tabwe->ThewmOutPowawity =
			(0 == (cgs_wead_wegistew(hwmgw->device, mmGPIOPAD_A) &
			(1 << gpio_pin_assignment.uc_gpio_pin_bit_shift))) ? 1 : 0;

		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_ONWY;

		/* if wequiwed, combine VWHot/PCC with thewmaw out GPIO*/
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_WeguwatowHot) &&
			phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw)){
			tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_VWHOT;
		}
	} ewse {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawOutGPIO);

		tabwe->ThewmOutGpio = 17;
		tabwe->ThewmOutPowawity = 1;
		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_DISABWE;
	}

	fow (i = 0; i < SMU72_MAX_ENTWIES_SMIO; i++)
		tabwe->Smio[i] = PP_HOST_TO_SMC_UW(tabwe->Smio[i]);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SystemFwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VWConfig);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask1);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ScwkStepSize);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitHigh);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitWow);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VowtageWesponseTime);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->PhaseWesponseTime);

	/* Upwoad aww dpm data to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = smu7_copy_bytes_to_smc(
			hwmgw,
			smu_data->smu7_data.dpm_tabwe_stawt + offsetof(SMU72_Discwete_DpmTabwe, SystemFwags),
			(uint8_t *)&(tabwe->SystemFwags),
			sizeof(SMU72_Discwete_DpmTabwe) - 3 * sizeof(SMU72_PIDContwowwew),
			SMC_WAM_END);

	PP_ASSEWT_WITH_CODE(!wesuwt,
		"Faiwed to upwoad dpm data to SMC memowy !", wetuwn wesuwt;);

	wesuwt = tonga_init_awb_tabwe_index(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to upwoad awb data to SMC memowy !", wetuwn wesuwt);

	tonga_popuwate_pm_fuses(hwmgw);
	PP_ASSEWT_WITH_CODE((!wesuwt),
		"Faiwed to popuwate initiawize pm fuses !", wetuwn wesuwt);

	wesuwt = tonga_popuwate_initiaw_mc_weg_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((!wesuwt),
		"Faiwed to popuwate initiawize MC Weg tabwe !", wetuwn wesuwt);

	wetuwn 0;
}

static int tonga_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
			(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	SMU72_Discwete_FanTabwe fan_tabwe = { FDO_MODE_HAWDWAWE };
	uint32_t duty100;
	uint32_t t_diff1, t_diff2, pwm_diff1, pwm_diff2;
	uint16_t fdo_min, swope1, swope2;
	uint32_t wefewence_cwock;
	int wes;
	uint64_t tmp64;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_MicwocodeFanContwow))
		wetuwn 0;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	if (0 == smu_data->smu7_data.fan_tabwe_stawt) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
						CGS_IND_WEG__SMC,
						CG_FDO_CTWW1, FMAX_DUTY100);

	if (0 == duty100) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	tmp64 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin * duty100;
	do_div(tmp64, 10000);
	fdo_min = (uint16_t)tmp64;

	t_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed -
		   hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin;
	t_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh -
		  hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed;

	pwm_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed -
		    hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin;
	pwm_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh -
		    hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed;

	swope1 = (uint16_t)((50 + ((16 * duty100 * pwm_diff1) / t_diff1)) / 100);
	swope2 = (uint16_t)((50 + ((16 * duty100 * pwm_diff2) / t_diff2)) / 100);

	fan_tabwe.TempMin = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin) / 100);
	fan_tabwe.TempMed = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed) / 100);
	fan_tabwe.TempMax = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax) / 100);

	fan_tabwe.Swope1 = cpu_to_be16(swope1);
	fan_tabwe.Swope2 = cpu_to_be16(swope2);

	fan_tabwe.FdoMin = cpu_to_be16(fdo_min);

	fan_tabwe.HystDown = cpu_to_be16(hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst);

	fan_tabwe.HystUp = cpu_to_be16(1);

	fan_tabwe.HystSwope = cpu_to_be16(1);

	fan_tabwe.TempWespWim = cpu_to_be16(5);

	wefewence_cwock = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	fan_tabwe.WefweshPewiod = cpu_to_be32((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway * wefewence_cwock) / 1600);

	fan_tabwe.FdoMax = cpu_to_be16((uint16_t)duty100);

	fan_tabwe.TempSwc = (uint8_t)PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, CG_MUWT_THEWMAW_CTWW, TEMP_SEW);

	fan_tabwe.FanContwow_GW_Fwag = 1;

	wes = smu7_copy_bytes_to_smc(hwmgw,
					smu_data->smu7_data.fan_tabwe_stawt,
					(uint8_t *)&fan_tabwe,
					(uint32_t)sizeof(fan_tabwe),
					SMC_WAM_END);

	wetuwn wes;
}


static int tonga_pwogwam_mem_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->need_update_smu7_dpm_tabwe &
		(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_OD_UPDATE_MCWK))
		wetuwn tonga_pwogwam_memowy_timing_pawametews(hwmgw);

	wetuwn 0;
}

static int tonga_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data =
			(stwuct tonga_smumgw *)(hwmgw->smu_backend);

	int wesuwt = 0;
	uint32_t wow_scwk_intewwupt_thweshowd = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkThwottweWowNotification)
		&& (data->wow_scwk_intewwupt_thweshowd != 0)) {
		wow_scwk_intewwupt_thweshowd =
				data->wow_scwk_intewwupt_thweshowd;

		CONVEWT_FWOM_HOST_TO_SMC_UW(wow_scwk_intewwupt_thweshowd);

		wesuwt = smu7_copy_bytes_to_smc(
				hwmgw,
				smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU72_Discwete_DpmTabwe,
					WowScwkIntewwuptThweshowd),
				(uint8_t *)&wow_scwk_intewwupt_thweshowd,
				sizeof(uint32_t),
				SMC_WAM_END);
	}

	wesuwt = tonga_update_and_upwoad_mc_weg_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((!wesuwt),
				"Faiwed to upwoad MC weg tabwe !",
				wetuwn wesuwt);

	wesuwt = tonga_pwogwam_mem_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to pwogwam memowy timing pawametews !",
			);

	wetuwn wesuwt;
}

static uint32_t tonga_get_offsetof(uint32_t type, uint32_t membew)
{
	switch (type) {
	case SMU_SoftWegistews:
		switch (membew) {
		case HandshakeDisabwes:
			wetuwn offsetof(SMU72_SoftWegistews, HandshakeDisabwes);
		case VowtageChangeTimeout:
			wetuwn offsetof(SMU72_SoftWegistews, VowtageChangeTimeout);
		case AvewageGwaphicsActivity:
			wetuwn offsetof(SMU72_SoftWegistews, AvewageGwaphicsActivity);
		case AvewageMemowyActivity:
			wetuwn offsetof(SMU72_SoftWegistews, AvewageMemowyActivity);
		case PweVBwankGap:
			wetuwn offsetof(SMU72_SoftWegistews, PweVBwankGap);
		case VBwankTimeout:
			wetuwn offsetof(SMU72_SoftWegistews, VBwankTimeout);
		case UcodeWoadStatus:
			wetuwn offsetof(SMU72_SoftWegistews, UcodeWoadStatus);
		case DWAM_WOG_ADDW_H:
			wetuwn offsetof(SMU72_SoftWegistews, DWAM_WOG_ADDW_H);
		case DWAM_WOG_ADDW_W:
			wetuwn offsetof(SMU72_SoftWegistews, DWAM_WOG_ADDW_W);
		case DWAM_WOG_PHY_ADDW_H:
			wetuwn offsetof(SMU72_SoftWegistews, DWAM_WOG_PHY_ADDW_H);
		case DWAM_WOG_PHY_ADDW_W:
			wetuwn offsetof(SMU72_SoftWegistews, DWAM_WOG_PHY_ADDW_W);
		case DWAM_WOG_BUFF_SIZE:
			wetuwn offsetof(SMU72_SoftWegistews, DWAM_WOG_BUFF_SIZE);
		}
		bweak;
	case SMU_Discwete_DpmTabwe:
		switch (membew) {
		case UvdBootWevew:
			wetuwn offsetof(SMU72_Discwete_DpmTabwe, UvdBootWevew);
		case VceBootWevew:
			wetuwn offsetof(SMU72_Discwete_DpmTabwe, VceBootWevew);
		case WowScwkIntewwuptThweshowd:
			wetuwn offsetof(SMU72_Discwete_DpmTabwe, WowScwkIntewwuptThweshowd);
		}
		bweak;
	}
	pw_wawn("can't get the offset of type %x membew %x\n", type, membew);
	wetuwn 0;
}

static uint32_t tonga_get_mac_definition(uint32_t vawue)
{
	switch (vawue) {
	case SMU_MAX_WEVEWS_GWAPHICS:
		wetuwn SMU72_MAX_WEVEWS_GWAPHICS;
	case SMU_MAX_WEVEWS_MEMOWY:
		wetuwn SMU72_MAX_WEVEWS_MEMOWY;
	case SMU_MAX_WEVEWS_WINK:
		wetuwn SMU72_MAX_WEVEWS_WINK;
	case SMU_MAX_ENTWIES_SMIO:
		wetuwn SMU72_MAX_ENTWIES_SMIO;
	case SMU_MAX_WEVEWS_VDDC:
		wetuwn SMU72_MAX_WEVEWS_VDDC;
	case SMU_MAX_WEVEWS_VDDGFX:
		wetuwn SMU72_MAX_WEVEWS_VDDGFX;
	case SMU_MAX_WEVEWS_VDDCI:
		wetuwn SMU72_MAX_WEVEWS_VDDCI;
	case SMU_MAX_WEVEWS_MVDD:
		wetuwn SMU72_MAX_WEVEWS_MVDD;
	}
	pw_wawn("can't get the mac vawue %x\n", vawue);

	wetuwn 0;
}

static int tonga_update_uvd_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t mm_boot_wevew_offset, mm_boot_wevew_vawue;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	smu_data->smc_state_tabwe.UvdBootWevew = 0;
	if (tabwe_info->mm_dep_tabwe->count > 0)
		smu_data->smc_state_tabwe.UvdBootWevew =
				(uint8_t) (tabwe_info->mm_dep_tabwe->count - 1);
	mm_boot_wevew_offset = smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU72_Discwete_DpmTabwe, UvdBootWevew);
	mm_boot_wevew_offset /= 4;
	mm_boot_wevew_offset *= 4;
	mm_boot_wevew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset);
	mm_boot_wevew_vawue &= 0x00FFFFFF;
	mm_boot_wevew_vawue |= smu_data->smc_state_tabwe.UvdBootWevew << 24;
	cgs_wwite_ind_wegistew(hwmgw->device,
				CGS_IND_WEG__SMC,
				mm_boot_wevew_offset, mm_boot_wevew_vawue);

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_UVDDPM) ||
		phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StabwePState))
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_UVDDPM_SetEnabwedMask,
				(uint32_t)(1 << smu_data->smc_state_tabwe.UvdBootWevew),
				NUWW);
	wetuwn 0;
}

static int tonga_update_vce_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct tonga_smumgw *smu_data =
				(stwuct tonga_smumgw *)(hwmgw->smu_backend);
	uint32_t mm_boot_wevew_offset, mm_boot_wevew_vawue;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);


	smu_data->smc_state_tabwe.VceBootWevew =
		(uint8_t) (tabwe_info->mm_dep_tabwe->count - 1);

	mm_boot_wevew_offset = smu_data->smu7_data.dpm_tabwe_stawt +
					offsetof(SMU72_Discwete_DpmTabwe, VceBootWevew);
	mm_boot_wevew_offset /= 4;
	mm_boot_wevew_offset *= 4;
	mm_boot_wevew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset);
	mm_boot_wevew_vawue &= 0xFF00FFFF;
	mm_boot_wevew_vawue |= smu_data->smc_state_tabwe.VceBootWevew << 16;
	cgs_wwite_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset, mm_boot_wevew_vawue);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_StabwePState))
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_VCEDPM_SetEnabwedMask,
				(uint32_t)1 << smu_data->smc_state_tabwe.VceBootWevew,
				NUWW);
	wetuwn 0;
}

static int tonga_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type)
{
	switch (type) {
	case SMU_UVD_TABWE:
		tonga_update_uvd_smc_tabwe(hwmgw);
		bweak;
	case SMU_VCE_TABWE:
		tonga_update_vce_smc_tabwe(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int tonga_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);

	uint32_t tmp;
	int wesuwt;
	boow ewwow = fawse;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, DpmTabwe),
				&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.dpm_tabwe_stawt = tmp;

	ewwow |= (wesuwt != 0);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, SoftWegistews),
				&tmp, SMC_WAM_END);

	if (!wesuwt) {
		data->soft_wegs_stawt = tmp;
		smu_data->smu7_data.soft_wegs_stawt = tmp;
	}

	ewwow |= (wesuwt != 0);


	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, mcWegistewTabwe),
				&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.mc_weg_tabwe_stawt = tmp;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, FanTabwe),
				&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.fan_tabwe_stawt = tmp;

	ewwow |= (wesuwt != 0);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, mcAwbDwamTimingTabwe),
				&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.awb_tabwe_stawt = tmp;

	ewwow |= (wesuwt != 0);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU72_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU72_Fiwmwawe_Headew, Vewsion),
				&tmp, SMC_WAM_END);

	if (!wesuwt)
		hwmgw->micwocode_vewsion_info.SMC = tmp;

	ewwow |= (wesuwt != 0);

	wetuwn ewwow ? 1 : 0;
}

/*---------------------------MC----------------------------*/

static uint8_t tonga_get_memowy_modiwe_index(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (uint8_t) (0xFF & (cgs_wead_wegistew(hwmgw->device, mmBIOS_SCWATCH_4) >> 16));
}

static boow tonga_check_s0_mc_weg_index(uint16_t in_weg, uint16_t *out_weg)
{
	boow wesuwt = twue;

	switch (in_weg) {
	case  mmMC_SEQ_WAS_TIMING:
		*out_weg = mmMC_SEQ_WAS_TIMING_WP;
		bweak;

	case  mmMC_SEQ_DWW_STBY:
		*out_weg = mmMC_SEQ_DWW_STBY_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CMD0:
		*out_weg = mmMC_SEQ_G5PDX_CMD0_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CMD1:
		*out_weg = mmMC_SEQ_G5PDX_CMD1_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CTWW:
		*out_weg = mmMC_SEQ_G5PDX_CTWW_WP;
		bweak;

	case mmMC_SEQ_CAS_TIMING:
		*out_weg = mmMC_SEQ_CAS_TIMING_WP;
		bweak;

	case mmMC_SEQ_MISC_TIMING:
		*out_weg = mmMC_SEQ_MISC_TIMING_WP;
		bweak;

	case mmMC_SEQ_MISC_TIMING2:
		*out_weg = mmMC_SEQ_MISC_TIMING2_WP;
		bweak;

	case mmMC_SEQ_PMG_DVS_CMD:
		*out_weg = mmMC_SEQ_PMG_DVS_CMD_WP;
		bweak;

	case mmMC_SEQ_PMG_DVS_CTW:
		*out_weg = mmMC_SEQ_PMG_DVS_CTW_WP;
		bweak;

	case mmMC_SEQ_WD_CTW_D0:
		*out_weg = mmMC_SEQ_WD_CTW_D0_WP;
		bweak;

	case mmMC_SEQ_WD_CTW_D1:
		*out_weg = mmMC_SEQ_WD_CTW_D1_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_D0:
		*out_weg = mmMC_SEQ_WW_CTW_D0_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_D1:
		*out_weg = mmMC_SEQ_WW_CTW_D1_WP;
		bweak;

	case mmMC_PMG_CMD_EMWS:
		*out_weg = mmMC_SEQ_PMG_CMD_EMWS_WP;
		bweak;

	case mmMC_PMG_CMD_MWS:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS_WP;
		bweak;

	case mmMC_PMG_CMD_MWS1:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS1_WP;
		bweak;

	case mmMC_SEQ_PMG_TIMING:
		*out_weg = mmMC_SEQ_PMG_TIMING_WP;
		bweak;

	case mmMC_PMG_CMD_MWS2:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS2_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_2:
		*out_weg = mmMC_SEQ_WW_CTW_2_WP;
		bweak;

	defauwt:
		wesuwt = fawse;
		bweak;
	}

	wetuwn wesuwt;
}

static int tonga_set_s0_mc_weg_index(stwuct tonga_mc_weg_tabwe *tabwe)
{
	uint32_t i;
	uint16_t addwess;

	fow (i = 0; i < tabwe->wast; i++) {
		tabwe->mc_weg_addwess[i].s0 =
			tonga_check_s0_mc_weg_index(tabwe->mc_weg_addwess[i].s1,
							&addwess) ?
							addwess :
						 tabwe->mc_weg_addwess[i].s1;
	}
	wetuwn 0;
}

static int tonga_copy_vbios_smc_weg_tabwe(const pp_atomctww_mc_weg_tabwe *tabwe,
					stwuct tonga_mc_weg_tabwe *ni_tabwe)
{
	uint8_t i, j;

	PP_ASSEWT_WITH_CODE((tabwe->wast <= SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((tabwe->num_entwies <= MAX_AC_TIMING_ENTWIES),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

	fow (i = 0; i < tabwe->wast; i++)
		ni_tabwe->mc_weg_addwess[i].s1 = tabwe->mc_weg_addwess[i].s1;

	ni_tabwe->wast = tabwe->wast;

	fow (i = 0; i < tabwe->num_entwies; i++) {
		ni_tabwe->mc_weg_tabwe_entwy[i].mcwk_max =
			tabwe->mc_weg_tabwe_entwy[i].mcwk_max;
		fow (j = 0; j < tabwe->wast; j++) {
			ni_tabwe->mc_weg_tabwe_entwy[i].mc_data[j] =
				tabwe->mc_weg_tabwe_entwy[i].mc_data[j];
		}
	}

	ni_tabwe->num_entwies = tabwe->num_entwies;

	wetuwn 0;
}

static int tonga_set_mc_speciaw_wegistews(stwuct pp_hwmgw *hwmgw,
					stwuct tonga_mc_weg_tabwe *tabwe)
{
	uint8_t i, j, k;
	uint32_t temp_weg;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	fow (i = 0, j = tabwe->wast; i < tabwe->wast; i++) {
		PP_ASSEWT_WITH_CODE((j < SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
			"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

		switch (tabwe->mc_weg_addwess[i].s1) {

		case mmMC_SEQ_MISC1:
			temp_weg = cgs_wead_wegistew(hwmgw->device,
							mmMC_PMG_CMD_EMWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_EMWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_EMWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					((temp_weg & 0xffff0000)) |
					((tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16);
			}
			j++;

			PP_ASSEWT_WITH_CODE((j < SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
				"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_MWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_MWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);

				if (!data->is_memowy_gddw5)
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] |= 0x100;
			}
			j++;

			if (!data->is_memowy_gddw5) {
				PP_ASSEWT_WITH_CODE((j < SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
					"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
				tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_AUTO_CMD;
				tabwe->mc_weg_addwess[j].s0 = mmMC_PMG_AUTO_CMD;
				fow (k = 0; k < tabwe->num_entwies; k++)
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
						(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16;
				j++;
			}

			bweak;

		case mmMC_SEQ_WESEWVE_M:
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS1);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_MWS1;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_MWS1_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
			}
			j++;
			bweak;

		defauwt:
			bweak;
		}

	}

	tabwe->wast = j;

	wetuwn 0;
}

static int tonga_set_vawid_fwag(stwuct tonga_mc_weg_tabwe *tabwe)
{
	uint8_t i, j;

	fow (i = 0; i < tabwe->wast; i++) {
		fow (j = 1; j < tabwe->num_entwies; j++) {
			if (tabwe->mc_weg_tabwe_entwy[j-1].mc_data[i] !=
				tabwe->mc_weg_tabwe_entwy[j].mc_data[i]) {
				tabwe->vawidfwag |= (1<<i);
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int tonga_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)(hwmgw->smu_backend);
	pp_atomctww_mc_weg_tabwe *tabwe;
	stwuct tonga_mc_weg_tabwe *ni_tabwe = &smu_data->mc_weg_tabwe;
	uint8_t moduwe_index = tonga_get_memowy_modiwe_index(hwmgw);

	tabwe = kzawwoc(sizeof(pp_atomctww_mc_weg_tabwe), GFP_KEWNEW);

	if (tabwe == NUWW)
		wetuwn -ENOMEM;

	/* Pwogwam additionaw WP wegistews that awe no wongew pwogwammed by VBIOS */
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_EMWS_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_EMWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS2_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2));

	wesuwt = atomctww_initiawize_mc_weg_tabwe(hwmgw, moduwe_index, tabwe);

	if (!wesuwt)
		wesuwt = tonga_copy_vbios_smc_weg_tabwe(tabwe, ni_tabwe);

	if (!wesuwt) {
		tonga_set_s0_mc_weg_index(ni_tabwe);
		wesuwt = tonga_set_mc_speciaw_wegistews(hwmgw, ni_tabwe);
	}

	if (!wesuwt)
		tonga_set_vawid_fwag(ni_tabwe);

	kfwee(tabwe);

	wetuwn wesuwt;
}

static boow tonga_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (1 == PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, FEATUWE_STATUS, VOWTAGE_CONTWOWWEW_ON))
			? twue : fawse;
}

static int tonga_update_dpm_settings(stwuct pp_hwmgw *hwmgw,
				void *pwofiwe_setting)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct tonga_smumgw *smu_data = (stwuct tonga_smumgw *)
			(hwmgw->smu_backend);
	stwuct pwofiwe_mode_setting *setting;
	stwuct SMU72_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU72_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t mcwk_awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU72_Discwete_DpmTabwe, MemowyWevew);
	stwuct SMU72_Discwete_MemowyWevew *mcwk_wevews =
			smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;
	uint32_t offset, up_hyst_offset, down_hyst_offset, cwk_activity_offset, tmp;

	if (pwofiwe_setting == NUWW)
		wetuwn -EINVAW;

	setting = (stwuct pwofiwe_mode_setting *)pwofiwe_setting;

	if (setting->bupdate_scwk) {
		if (!data->scwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_SCWKDPM_FweezeWevew, NUWW);
		fow (i = 0; i < smu_data->smc_state_tabwe.GwaphicsDpmWevewCount; i++) {
			if (wevews[i].ActivityWevew !=
				cpu_to_be16(setting->scwk_activity)) {
				wevews[i].ActivityWevew = cpu_to_be16(setting->scwk_activity);

				cwk_activity_offset = awway + (sizeof(SMU72_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU72_Discwete_GwaphicsWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (wevews[i].UpHyst != setting->scwk_up_hyst ||
				wevews[i].DownHyst != setting->scwk_down_hyst) {
				wevews[i].UpHyst = setting->scwk_up_hyst;
				wevews[i].DownHyst = setting->scwk_down_hyst;
				up_hyst_offset = awway + (sizeof(SMU72_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU72_Discwete_GwaphicsWevew, UpHyst);
				down_hyst_offset = awway + (sizeof(SMU72_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU72_Discwete_GwaphicsWevew, DownHyst);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, wevews[i].UpHyst, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, wevews[i].DownHyst, sizeof(uint8_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));
			}
		}
		if (!data->scwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_SCWKDPM_UnfweezeWevew, NUWW);
	}

	if (setting->bupdate_mcwk) {
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_FweezeWevew, NUWW);
		fow (i = 0; i < smu_data->smc_state_tabwe.MemowyDpmWevewCount; i++) {
			if (mcwk_wevews[i].ActivityWevew !=
				cpu_to_be16(setting->mcwk_activity)) {
				mcwk_wevews[i].ActivityWevew = cpu_to_be16(setting->mcwk_activity);

				cwk_activity_offset = mcwk_awway + (sizeof(SMU72_Discwete_MemowyWevew) * i)
						+ offsetof(SMU72_Discwete_MemowyWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, mcwk_wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (mcwk_wevews[i].UpHyst != setting->mcwk_up_hyst ||
				mcwk_wevews[i].DownHyst != setting->mcwk_down_hyst) {
				mcwk_wevews[i].UpHyst = setting->mcwk_up_hyst;
				mcwk_wevews[i].DownHyst = setting->mcwk_down_hyst;
				up_hyst_offset = mcwk_awway + (sizeof(SMU72_Discwete_MemowyWevew) * i)
						+ offsetof(SMU72_Discwete_MemowyWevew, UpHyst);
				down_hyst_offset = mcwk_awway + (sizeof(SMU72_Discwete_MemowyWevew) * i)
						+ offsetof(SMU72_Discwete_MemowyWevew, DownHyst);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, mcwk_wevews[i].UpHyst, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, mcwk_wevews[i].DownHyst, sizeof(uint8_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));
			}
		}
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_UnfweezeWevew, NUWW);
	}
	wetuwn 0;
}

const stwuct pp_smumgw_func tonga_smu_funcs = {
	.name = "tonga_smu",
	.smu_init = &tonga_smu_init,
	.smu_fini = &smu7_smu_fini,
	.stawt_smu = &tonga_stawt_smu,
	.check_fw_woad_finish = &smu7_check_fw_woad_finish,
	.wequest_smu_woad_fw = &smu7_wequest_smu_woad_fw,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &smu7_send_msg_to_smc_with_pawametew,
	.get_awgument = smu7_get_awgument,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.update_smc_tabwe = tonga_update_smc_tabwe,
	.get_offsetof = tonga_get_offsetof,
	.pwocess_fiwmwawe_headew = tonga_pwocess_fiwmwawe_headew,
	.init_smc_tabwe = tonga_init_smc_tabwe,
	.update_scwk_thweshowd = tonga_update_scwk_thweshowd,
	.thewmaw_setup_fan_tabwe = tonga_thewmaw_setup_fan_tabwe,
	.popuwate_aww_gwaphic_wevews = tonga_popuwate_aww_gwaphic_wevews,
	.popuwate_aww_memowy_wevews = tonga_popuwate_aww_memowy_wevews,
	.get_mac_definition = tonga_get_mac_definition,
	.initiawize_mc_weg_tabwe = tonga_initiawize_mc_weg_tabwe,
	.is_dpm_wunning = tonga_is_dpm_wunning,
	.update_dpm_settings = tonga_update_dpm_settings,
};
