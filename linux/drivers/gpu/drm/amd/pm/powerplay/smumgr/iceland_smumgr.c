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
 * Authow: Huang Wui <way.huang@amd.com>
 *
 */
#incwude "pp_debug.h"
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/gfp.h>

#incwude "smumgw.h"
#incwude "icewand_smumgw.h"

#incwude "ppsmc.h"

#incwude "cgs_common.h"

#incwude "smu7_dyn_defauwts.h"
#incwude "smu7_hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "ppatomctww.h"
#incwude "atombios.h"
#incwude "pppciewanes.h"
#incwude "pp_endian.h"
#incwude "pwocesspptabwes.h"


#incwude "smu/smu_7_1_1_d.h"
#incwude "smu/smu_7_1_1_sh_mask.h"
#incwude "smu71_discwete.h"

#incwude "smu_ucode_xfew_vi.h"
#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"
#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"
#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"


#define ICEWAND_SMC_SIZE               0x20000

#define POWEWTUNE_DEFAUWT_SET_MAX    1
#define MC_CG_AWB_FWEQ_F1           0x0b
#define VDDC_VDDCI_DEWTA            200

#define DEVICE_ID_VI_ICEWAND_M_6900	0x6900
#define DEVICE_ID_VI_ICEWAND_M_6901	0x6901
#define DEVICE_ID_VI_ICEWAND_M_6902	0x6902
#define DEVICE_ID_VI_ICEWAND_M_6903	0x6903

static const stwuct icewand_pt_defauwts defauwts_icewand = {
	/*
	 * sviWoadWIneEn, SviWoadWineVddC, TDC_VDDC_ThwottweWeweaseWimitPewc,
	 * TDC_MAWt, TdcWatewfawwCtw, DTEAmbientTempBase, DispwayCac, BAPM_TEMP_GWADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0xB0000,
	{ 0x79,  0x253, 0x25D, 0xAE,  0x72,  0x80,  0x83,  0x86,  0x6F,  0xC8,  0xC9,  0xC9,  0x2F,  0x4D,  0x61  },
	{ 0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203, 0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4 }
};

/* 35W - XT, XTW */
static const stwuct icewand_pt_defauwts defauwts_icewandxt = {
	/*
	 * sviWoadWIneEn, SviWoadWineVddC,
	 * TDC_VDDC_ThwottweWeweaseWimitPewc, TDC_MAWt,
	 * TdcWatewfawwCtw, DTEAmbientTempBase, DispwayCac,
	 * BAPM_TEMP_GWADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0x0,
	{ 0xA7,  0x0, 0x0, 0xB5,  0x0, 0x0, 0x9F,  0x0, 0x0, 0xD6,  0x0, 0x0, 0xD7,  0x0, 0x0},
	{ 0x1EA, 0x0, 0x0, 0x224, 0x0, 0x0, 0x25E, 0x0, 0x0, 0x28E, 0x0, 0x0, 0x2AB, 0x0, 0x0}
};

/* 25W - PWO, WE */
static const stwuct icewand_pt_defauwts defauwts_icewandpwo = {
	/*
	 * sviWoadWIneEn, SviWoadWineVddC,
	 * TDC_VDDC_ThwottweWeweaseWimitPewc, TDC_MAWt,
	 * TdcWatewfawwCtw, DTEAmbientTempBase, DispwayCac,
	 * BAPM_TEMP_GWADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0x0,
	{ 0xB7,  0x0, 0x0, 0xC3,  0x0, 0x0, 0xB5,  0x0, 0x0, 0xEA,  0x0, 0x0, 0xE6,  0x0, 0x0},
	{ 0x1EA, 0x0, 0x0, 0x224, 0x0, 0x0, 0x25E, 0x0, 0x0, 0x28E, 0x0, 0x0, 0x2AB, 0x0, 0x0}
};

static int icewand_stawt_smc(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	wetuwn 0;
}

static void icewand_weset_smc(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_WESET_CNTW,
				  wst_weg, 1);
}


static void icewand_stop_smc_cwock(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_CWOCK_CNTW_0,
				  ck_disabwe, 1);
}

static void icewand_stawt_smc_cwock(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_CWOCK_CNTW_0,
				  ck_disabwe, 0);
}

static int icewand_smu_stawt_smc(stwuct pp_hwmgw *hwmgw)
{
	/* set smc instwuct stawt point at 0x0 */
	smu7_pwogwam_jump_on_stawt(hwmgw);

	/* enabwe smc cwock */
	icewand_stawt_smc_cwock(hwmgw);

	/* de-assewt weset */
	icewand_stawt_smc(hwmgw);

	PHM_WAIT_INDIWECT_FIEWD(hwmgw, SMC_IND, FIWMWAWE_FWAGS,
				 INTEWWUPTS_ENABWED, 1);

	wetuwn 0;
}


static int icewand_upwoad_smc_fiwmwawe_data(stwuct pp_hwmgw *hwmgw,
					uint32_t wength, const uint8_t *swc,
					uint32_t wimit, uint32_t stawt_addw)
{
	uint32_t byte_count = wength;
	uint32_t data;

	PP_ASSEWT_WITH_CODE((wimit >= byte_count), "SMC addwess is beyond the SMC WAM awea.", wetuwn -EINVAW);

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_INDEX_0, stawt_addw);
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, 1);

	whiwe (byte_count >= 4) {
		data = swc[0] * 0x1000000 + swc[1] * 0x10000 + swc[2] * 0x100 + swc[3];
		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_0, data);
		swc += 4;
		byte_count -= 4;
	}

	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, 0);

	PP_ASSEWT_WITH_CODE((0 == byte_count), "SMC size must be divisibwe by 4.", wetuwn -EINVAW);

	wetuwn 0;
}


static int icewand_smu_upwoad_fiwmwawe_image(stwuct pp_hwmgw *hwmgw)
{
	uint32_t vaw;
	stwuct cgs_fiwmwawe_info info = {0};

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	/* woad SMC fiwmwawe */
	cgs_get_fiwmwawe_info(hwmgw->device,
		smu7_convewt_fw_type_to_cgs(UCODE_ID_SMU), &info);

	if (info.image_size & 3) {
		pw_eww("[ powewpway ] SMC ucode is not 4 bytes awigned\n");
		wetuwn -EINVAW;
	}

	if (info.image_size > ICEWAND_SMC_SIZE) {
		pw_eww("[ powewpway ] SMC addwess is beyond the SMC WAM awea\n");
		wetuwn -EINVAW;
	}
	hwmgw->smu_vewsion = info.vewsion;
	/* wait fow smc boot up */
	PHM_WAIT_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
					 WCU_UC_EVENTS, boot_seq_done, 0);

	/* cweaw fiwmwawe intewwupt enabwe fwag */
	vaw = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				    ixSMC_SYSCON_MISC_CNTW);
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			       ixSMC_SYSCON_MISC_CNTW, vaw | 1);

	/* stop smc cwock */
	icewand_stop_smc_cwock(hwmgw);

	/* weset smc */
	icewand_weset_smc(hwmgw);
	icewand_upwoad_smc_fiwmwawe_data(hwmgw, info.image_size,
				(uint8_t *)info.kptw, ICEWAND_SMC_SIZE,
				info.ucode_stawt_addwess);

	wetuwn 0;
}

static int icewand_wequest_smu_woad_specific_fw(stwuct pp_hwmgw *hwmgw,
						uint32_t fiwmwaweType)
{
	wetuwn 0;
}

static int icewand_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *pwiv = hwmgw->smu_backend;
	int wesuwt;

	if (!smu7_is_smc_wam_wunning(hwmgw)) {
		wesuwt = icewand_smu_upwoad_fiwmwawe_image(hwmgw);
		if (wesuwt)
			wetuwn wesuwt;

		icewand_smu_stawt_smc(hwmgw);
	}

	/* Setup SoftWegsStawt hewe to visit the wegistew UcodeWoadStatus
	 * to check fw woading state
	 */
	smu7_wead_smc_swam_dwowd(hwmgw,
			SMU71_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU71_Fiwmwawe_Headew, SoftWegistews),
			&(pwiv->smu7_data.soft_wegs_stawt), 0x40000);

	wesuwt = smu7_wequest_smu_woad_fw(hwmgw);

	wetuwn wesuwt;
}

static int icewand_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *icewand_pwiv;

	icewand_pwiv = kzawwoc(sizeof(stwuct icewand_smumgw), GFP_KEWNEW);

	if (icewand_pwiv == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = icewand_pwiv;

	if (smu7_init(hwmgw)) {
		kfwee(icewand_pwiv);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static void icewand_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t dev_id;

	dev_id = adev->pdev->device;

	switch (dev_id) {
	case DEVICE_ID_VI_ICEWAND_M_6900:
	case DEVICE_ID_VI_ICEWAND_M_6903:
		smu_data->powew_tune_defauwts = &defauwts_icewandxt;
		bweak;

	case DEVICE_ID_VI_ICEWAND_M_6901:
	case DEVICE_ID_VI_ICEWAND_M_6902:
		smu_data->powew_tune_defauwts = &defauwts_icewandpwo;
		bweak;
	defauwt:
		smu_data->powew_tune_defauwts = &defauwts_icewand;
		pw_wawn("Unknown V.I. Device ID.\n");
		bweak;
	}
	wetuwn;
}

static int icewand_popuwate_svi_woad_wine(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	const stwuct icewand_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	smu_data->powew_tune_tabwe.SviWoadWineEn = defauwts->svi_woad_wine_en;
	smu_data->powew_tune_tabwe.SviWoadWineVddC = defauwts->svi_woad_wine_vddc;
	smu_data->powew_tune_tabwe.SviWoadWineTwimVddC = 3;
	smu_data->powew_tune_tabwe.SviWoadWineOffsetVddC = 0;

	wetuwn 0;
}

static int icewand_popuwate_tdc_wimit(stwuct pp_hwmgw *hwmgw)
{
	uint16_t tdc_wimit;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	const stwuct icewand_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	tdc_wimit = (uint16_t)(hwmgw->dyn_state.cac_dtp_tabwe->usTDC * 256);
	smu_data->powew_tune_tabwe.TDC_VDDC_PkgWimit =
			CONVEWT_FWOM_HOST_TO_SMC_US(tdc_wimit);
	smu_data->powew_tune_tabwe.TDC_VDDC_ThwottweWeweaseWimitPewc =
			defauwts->tdc_vddc_thwottwe_wewease_wimit_pewc;
	smu_data->powew_tune_tabwe.TDC_MAWt = defauwts->tdc_mawt;

	wetuwn 0;
}

static int icewand_popuwate_dw8(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	const stwuct icewand_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	uint32_t temp;

	if (smu7_wead_smc_swam_dwowd(hwmgw,
			fuse_tabwe_offset +
			offsetof(SMU71_Discwete_PmFuses, TdcWatewfawwCtw),
			(uint32_t *)&temp, SMC_WAM_END))
		PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to wead PmFuses.DW6 (SviWoadWineEn) fwom SMC Faiwed!",
				wetuwn -EINVAW);
	ewse
		smu_data->powew_tune_tabwe.TdcWatewfawwCtw = defauwts->tdc_watewfaww_ctw;

	wetuwn 0;
}

static int icewand_popuwate_tempewatuwe_scawew(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int icewand_popuwate_gnb_wpmw(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 8; i++)
		smu_data->powew_tune_tabwe.GnbWPMW[i] = 0;

	wetuwn 0;
}

static int icewand_popuwate_bapm_vddc_base_weakage_sidd(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint16_t HiSidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd;
	uint16_t WoSidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd;
	stwuct phm_cac_tdp_tabwe *cac_tabwe = hwmgw->dyn_state.cac_dtp_tabwe;

	HiSidd = (uint16_t)(cac_tabwe->usHighCACWeakage / 100 * 256);
	WoSidd = (uint16_t)(cac_tabwe->usWowCACWeakage / 100 * 256);

	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(HiSidd);
	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(WoSidd);

	wetuwn 0;
}

static int icewand_popuwate_bapm_vddc_vid_sidd(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint8_t *hi_vid = smu_data->powew_tune_tabwe.BapmVddCVidHiSidd;
	uint8_t *wo_vid = smu_data->powew_tune_tabwe.BapmVddCVidWoSidd;

	PP_ASSEWT_WITH_CODE(NUWW != hwmgw->dyn_state.cac_weakage_tabwe,
			    "The CAC Weakage tabwe does not exist!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(hwmgw->dyn_state.cac_weakage_tabwe->count <= 8,
			    "Thewe shouwd nevew be mowe than 8 entwies fow BapmVddcVid!!!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(hwmgw->dyn_state.cac_weakage_tabwe->count == hwmgw->dyn_state.vddc_dependency_on_scwk->count,
			    "CACWeakageTabwe->count and VddcDependencyOnSCWk->count not equaw", wetuwn -EINVAW);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_EVV)) {
		fow (i = 0; (uint32_t) i < hwmgw->dyn_state.cac_weakage_tabwe->count; i++) {
			wo_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc1);
			hi_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc2);
		}
	} ewse {
		PP_ASSEWT_WITH_CODE(fawse, "Icewand shouwd awways suppowt EVV", wetuwn -EINVAW);
	}

	wetuwn 0;
}

static int icewand_popuwate_vddc_vid(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint8_t *vid = smu_data->powew_tune_tabwe.VddCVid;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	PP_ASSEWT_WITH_CODE(data->vddc_vowtage_tabwe.count <= 8,
		"Thewe shouwd nevew be mowe than 8 entwies fow VddcVid!!!",
		wetuwn -EINVAW);

	fow (i = 0; i < (int)data->vddc_vowtage_tabwe.count; i++) {
		vid[i] = convewt_to_vid(data->vddc_vowtage_tabwe.entwies[i].vawue);
	}

	wetuwn 0;
}



static int icewand_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint32_t pm_fuse_tabwe_offset;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment)) {
		if (smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, PmFuseTabwe),
				&pm_fuse_tabwe_offset, SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to get pm_fuse_tabwe_offset Faiwed!",
					wetuwn -EINVAW);

		/* DW0 - DW3 */
		if (icewand_popuwate_bapm_vddc_vid_sidd(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate bapm vddc vid Faiwed!",
					wetuwn -EINVAW);

		/* DW4 - DW5 */
		if (icewand_popuwate_vddc_vid(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate vddc vid Faiwed!",
					wetuwn -EINVAW);

		/* DW6 */
		if (icewand_popuwate_svi_woad_wine(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate SviWoadWine Faiwed!",
					wetuwn -EINVAW);
		/* DW7 */
		if (icewand_popuwate_tdc_wimit(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TDCWimit Faiwed!", wetuwn -EINVAW);
		/* DW8 */
		if (icewand_popuwate_dw8(hwmgw, pm_fuse_tabwe_offset))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TdcWatewfawwCtw, "
					"WPMWTempewatuwe Min and Max Faiwed!",
					wetuwn -EINVAW);

		/* DW9-DW12 */
		if (0 != icewand_popuwate_tempewatuwe_scawew(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate WPMWTempewatuweScawew Faiwed!",
					wetuwn -EINVAW);

		/* DW13-DW16 */
		if (icewand_popuwate_gnb_wpmw(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate GnbWPMW Faiwed!",
					wetuwn -EINVAW);

		/* DW18 */
		if (icewand_popuwate_bapm_vddc_base_weakage_sidd(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate BapmVddCBaseWeakage Hi and Wo Sidd Faiwed!",
					wetuwn -EINVAW);

		if (smu7_copy_bytes_to_smc(hwmgw, pm_fuse_tabwe_offset,
				(uint8_t *)&smu_data->powew_tune_tabwe,
				sizeof(stwuct SMU71_Discwete_PmFuses), SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to downwoad PmFuseTabwe Faiwed!",
					wetuwn -EINVAW);
	}
	wetuwn 0;
}

static int icewand_get_dependency_vowt_by_cwk(stwuct pp_hwmgw *hwmgw,
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_cwock_vowtage_tabwe,
	uint32_t cwock, uint32_t *vow)
{
	uint32_t i = 0;

	/* cwock - vowtage dependency tabwe is empty tabwe */
	if (awwowed_cwock_vowtage_tabwe->count == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < awwowed_cwock_vowtage_tabwe->count; i++) {
		/* find fiwst scwk biggew than wequest */
		if (awwowed_cwock_vowtage_tabwe->entwies[i].cwk >= cwock) {
			*vow = awwowed_cwock_vowtage_tabwe->entwies[i].v;
			wetuwn 0;
		}
	}

	/* scwk is biggew than max scwk in the dependence tabwe */
	*vow = awwowed_cwock_vowtage_tabwe->entwies[i - 1].v;

	wetuwn 0;
}

static int icewand_get_std_vowtage_vawue_sidd(stwuct pp_hwmgw *hwmgw,
		pp_atomctww_vowtage_tabwe_entwy *tab, uint16_t *hi,
		uint16_t *wo)
{
	uint16_t v_index;
	boow vow_found = fawse;
	*hi = tab->vawue * VOWTAGE_SCAWE;
	*wo = tab->vawue * VOWTAGE_SCAWE;

	/* SCWK/VDDC Dependency Tabwe has to exist. */
	PP_ASSEWT_WITH_CODE(NUWW != hwmgw->dyn_state.vddc_dependency_on_scwk,
			"The SCWK/VDDC Dependency Tabwe does not exist.",
			wetuwn -EINVAW);

	if (NUWW == hwmgw->dyn_state.cac_weakage_tabwe) {
		pw_wawn("CAC Weakage Tabwe does not exist, using vddc.\n");
		wetuwn 0;
	}

	/*
	 * Since vowtage in the scwk/vddc dependency tabwe is not
	 * necessawiwy in ascending owdew because of EWB vowtage
	 * patching, woop thwough entiwe wist to find exact vowtage.
	 */
	fow (v_index = 0; (uint32_t)v_index < hwmgw->dyn_state.vddc_dependency_on_scwk->count; v_index++) {
		if (tab->vawue == hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[v_index].v) {
			vow_found = twue;
			if ((uint32_t)v_index < hwmgw->dyn_state.cac_weakage_tabwe->count) {
				*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Vddc * VOWTAGE_SCAWE;
				*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Weakage * VOWTAGE_SCAWE);
			} ewse {
				pw_wawn("Index fwom SCWK/VDDC Dependency Tabwe exceeds the CAC Weakage Tabwe index, using maximum index fwom CAC tabwe.\n");
				*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Vddc * VOWTAGE_SCAWE;
				*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Weakage * VOWTAGE_SCAWE);
			}
			bweak;
		}
	}

	/*
	 * If vowtage is not found in the fiwst pass, woop again to
	 * find the best match, equaw ow highew vawue.
	 */
	if (!vow_found) {
		fow (v_index = 0; (uint32_t)v_index < hwmgw->dyn_state.vddc_dependency_on_scwk->count; v_index++) {
			if (tab->vawue <= hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[v_index].v) {
				vow_found = twue;
				if ((uint32_t)v_index < hwmgw->dyn_state.cac_weakage_tabwe->count) {
					*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Vddc * VOWTAGE_SCAWE;
					*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Weakage) * VOWTAGE_SCAWE;
				} ewse {
					pw_wawn("Index fwom SCWK/VDDC Dependency Tabwe exceeds the CAC Weakage Tabwe index in second wook up, using maximum index fwom CAC tabwe.");
					*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Vddc * VOWTAGE_SCAWE;
					*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Weakage * VOWTAGE_SCAWE);
				}
				bweak;
			}
		}

		if (!vow_found)
			pw_wawn("Unabwe to get std_vddc fwom SCWK/VDDC Dependency Tabwe, using vddc.\n");
	}

	wetuwn 0;
}

static int icewand_popuwate_smc_vowtage_tabwe(stwuct pp_hwmgw *hwmgw,
		pp_atomctww_vowtage_tabwe_entwy *tab,
		SMU71_Discwete_VowtageWevew *smc_vowtage_tab)
{
	int wesuwt;

	wesuwt = icewand_get_std_vowtage_vawue_sidd(hwmgw, tab,
			&smc_vowtage_tab->StdVowtageHiSidd,
			&smc_vowtage_tab->StdVowtageWoSidd);
	if (0 != wesuwt) {
		smc_vowtage_tab->StdVowtageHiSidd = tab->vawue * VOWTAGE_SCAWE;
		smc_vowtage_tab->StdVowtageWoSidd = tab->vawue * VOWTAGE_SCAWE;
	}

	smc_vowtage_tab->Vowtage = PP_HOST_TO_SMC_US(tab->vawue * VOWTAGE_SCAWE);
	CONVEWT_FWOM_HOST_TO_SMC_US(smc_vowtage_tab->StdVowtageHiSidd);
	CONVEWT_FWOM_HOST_TO_SMC_US(smc_vowtage_tab->StdVowtageHiSidd);

	wetuwn 0;
}

static int icewand_popuwate_smc_vddc_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU71_Discwete_DpmTabwe *tabwe)
{
	unsigned int count;
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	tabwe->VddcWevewCount = data->vddc_vowtage_tabwe.count;
	fow (count = 0; count < tabwe->VddcWevewCount; count++) {
		wesuwt = icewand_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->vddc_vowtage_tabwe.entwies[count]),
				&(tabwe->VddcWevew[count]));
		PP_ASSEWT_WITH_CODE(0 == wesuwt, "do not popuwate SMC VDDC vowtage tabwe", wetuwn -EINVAW);

		/* GPIO vowtage contwow */
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow)
			tabwe->VddcWevew[count].Smio |= data->vddc_vowtage_tabwe.entwies[count].smio_wow;
		ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow)
			tabwe->VddcWevew[count].Smio = 0;
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddcWevewCount);

	wetuwn 0;
}

static int icewand_popuwate_smc_vdd_ci_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU71_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;
	int wesuwt;

	tabwe->VddciWevewCount = data->vddci_vowtage_tabwe.count;

	fow (count = 0; count < tabwe->VddciWevewCount; count++) {
		wesuwt = icewand_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->vddci_vowtage_tabwe.entwies[count]),
				&(tabwe->VddciWevew[count]));
		PP_ASSEWT_WITH_CODE(wesuwt == 0, "do not popuwate SMC VDDCI vowtage tabwe", wetuwn -EINVAW);
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow)
			tabwe->VddciWevew[count].Smio |= data->vddci_vowtage_tabwe.entwies[count].smio_wow;
		ewse
			tabwe->VddciWevew[count].Smio |= 0;
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddciWevewCount);

	wetuwn 0;
}

static int icewand_popuwate_smc_mvdd_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU71_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;
	int wesuwt;

	tabwe->MvddWevewCount = data->mvdd_vowtage_tabwe.count;

	fow (count = 0; count < tabwe->VddciWevewCount; count++) {
		wesuwt = icewand_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->mvdd_vowtage_tabwe.entwies[count]),
				&tabwe->MvddWevew[count]);
		PP_ASSEWT_WITH_CODE(wesuwt == 0, "do not popuwate SMC mvdd vowtage tabwe", wetuwn -EINVAW);
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow)
			tabwe->MvddWevew[count].Smio |= data->mvdd_vowtage_tabwe.entwies[count].smio_wow;
		ewse
			tabwe->MvddWevew[count].Smio |= 0;
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MvddWevewCount);

	wetuwn 0;
}


static int icewand_popuwate_smc_vowtage_tabwes(stwuct pp_hwmgw *hwmgw,
	SMU71_Discwete_DpmTabwe *tabwe)
{
	int wesuwt;

	wesuwt = icewand_popuwate_smc_vddc_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate VDDC vowtage tabwe to SMC", wetuwn -EINVAW);

	wesuwt = icewand_popuwate_smc_vdd_ci_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate VDDCI vowtage tabwe to SMC", wetuwn -EINVAW);

	wesuwt = icewand_popuwate_smc_mvdd_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate MVDD vowtage tabwe to SMC", wetuwn -EINVAW);

	wetuwn 0;
}

static int icewand_popuwate_uwv_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU71_Discwete_Uwv *state)
{
	uint32_t vowtage_wesponse_time, uwv_vowtage;
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	state->CcPwwDynWm = 0;
	state->CcPwwDynWm1 = 0;

	wesuwt = pp_tabwes_get_wesponse_times(hwmgw, &vowtage_wesponse_time, &uwv_vowtage);
	PP_ASSEWT_WITH_CODE((0 == wesuwt), "can not get UWV vowtage vawue", wetuwn wesuwt;);

	if (uwv_vowtage == 0) {
		data->uwv_suppowted = fawse;
		wetuwn 0;
	}

	if (data->vowtage_contwow != SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		/* use minimum vowtage if uwv vowtage in pptabwe is biggew than minimum vowtage */
		if (uwv_vowtage > hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v)
			state->VddcOffset = 0;
		ewse
			/* used in SMIO Mode. not impwemented fow now. this is backup onwy fow CI. */
			state->VddcOffset = (uint16_t)(hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v - uwv_vowtage);
	} ewse {
		/* use minimum vowtage if uwv vowtage in pptabwe is biggew than minimum vowtage */
		if (uwv_vowtage > hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v)
			state->VddcOffsetVid = 0;
		ewse  /* used in SVI2 Mode */
			state->VddcOffsetVid = (uint8_t)(
					(hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v - uwv_vowtage)
						* VOWTAGE_VID_OFFSET_SCAWE2
						/ VOWTAGE_VID_OFFSET_SCAWE1);
	}
	state->VddcPhase = 1;

	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm1);
	CONVEWT_FWOM_HOST_TO_SMC_US(state->VddcOffset);

	wetuwn 0;
}

static int icewand_popuwate_uwv_state(stwuct pp_hwmgw *hwmgw,
		 SMU71_Discwete_Uwv *uwv_wevew)
{
	wetuwn icewand_popuwate_uwv_wevew(hwmgw, uwv_wevew);
}

static int icewand_popuwate_smc_wink_wevew(stwuct pp_hwmgw *hwmgw, SMU71_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
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

static int icewand_cawcuwate_scwk_pawams(stwuct pp_hwmgw *hwmgw,
		uint32_t engine_cwock, SMU71_Discwete_GwaphicsWevew *scwk)
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

static int icewand_popuwate_phase_vawue_based_on_scwk(stwuct pp_hwmgw *hwmgw,
				const stwuct phm_phase_shedding_wimits_tabwe *pw,
					uint32_t scwk, uint32_t *p_shed)
{
	unsigned int i;

	/* use the minimum phase shedding */
	*p_shed = 1;

	fow (i = 0; i < pw->count; i++) {
		if (scwk < pw->entwies[i].Scwk) {
			*p_shed = i;
			bweak;
		}
	}
	wetuwn 0;
}

static int icewand_popuwate_singwe_gwaphic_wevew(stwuct pp_hwmgw *hwmgw,
						uint32_t engine_cwock,
				SMU71_Discwete_GwaphicsWevew *gwaphic_wevew)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	wesuwt = icewand_cawcuwate_scwk_pawams(hwmgw, engine_cwock, gwaphic_wevew);

	/* popuwate gwaphics wevews*/
	wesuwt = icewand_get_dependency_vowt_by_cwk(hwmgw,
		hwmgw->dyn_state.vddc_dependency_on_scwk, engine_cwock,
		&gwaphic_wevew->MinVddc);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
		"can not find VDDC vowtage vawue fow VDDC engine cwock dependency tabwe", wetuwn wesuwt);

	/* SCWK fwequency in units of 10KHz*/
	gwaphic_wevew->ScwkFwequency = engine_cwock;
	gwaphic_wevew->MinVddcPhases = 1;

	if (data->vddc_phase_shed_contwow)
		icewand_popuwate_phase_vawue_based_on_scwk(hwmgw,
				hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe,
				engine_cwock,
				&gwaphic_wevew->MinVddcPhases);

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

	if (0 == wesuwt) {
		gwaphic_wevew->MinVddc = PP_HOST_TO_SMC_UW(gwaphic_wevew->MinVddc * VOWTAGE_SCAWE);
		CONVEWT_FWOM_HOST_TO_SMC_UW(gwaphic_wevew->MinVddcPhases);
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

static int icewand_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	uint32_t wevew_awway_adwess = smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU71_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t wevew_awway_size = sizeof(SMU71_Discwete_GwaphicsWevew) *
						SMU71_MAX_WEVEWS_GWAPHICS;

	SMU71_Discwete_GwaphicsWevew *wevews = smu_data->smc_state_tabwe.GwaphicsWevew;

	uint32_t i;
	uint8_t highest_pcie_wevew_enabwed = 0;
	uint8_t wowest_pcie_wevew_enabwed = 0, mid_pcie_wevew_enabwed = 0;
	uint8_t count = 0;
	int wesuwt = 0;

	memset(wevews, 0x00, wevew_awway_size);

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
		wesuwt = icewand_popuwate_singwe_gwaphic_wevew(hwmgw,
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

	whiwe ((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
				(1 << (highest_pcie_wevew_enabwed + 1))) != 0) {
		highest_pcie_wevew_enabwed++;
	}

	whiwe ((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
		(1 << wowest_pcie_wevew_enabwed)) == 0) {
		wowest_pcie_wevew_enabwed++;
	}

	whiwe ((count < highest_pcie_wevew_enabwed) &&
			((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
				(1 << (wowest_pcie_wevew_enabwed + 1 + count))) == 0)) {
		count++;
	}

	mid_pcie_wevew_enabwed = (wowest_pcie_wevew_enabwed+1+count) < highest_pcie_wevew_enabwed ?
		(wowest_pcie_wevew_enabwed+1+count) : highest_pcie_wevew_enabwed;


	/* set pcieDpmWevew to highest_pcie_wevew_enabwed*/
	fow (i = 2; i < dpm_tabwe->scwk_tabwe.count; i++) {
		smu_data->smc_state_tabwe.GwaphicsWevew[i].pcieDpmWevew = highest_pcie_wevew_enabwed;
	}

	/* set pcieDpmWevew to wowest_pcie_wevew_enabwed*/
	smu_data->smc_state_tabwe.GwaphicsWevew[0].pcieDpmWevew = wowest_pcie_wevew_enabwed;

	/* set pcieDpmWevew to mid_pcie_wevew_enabwed*/
	smu_data->smc_state_tabwe.GwaphicsWevew[1].pcieDpmWevew = mid_pcie_wevew_enabwed;

	/* wevew count wiww send to smc once at init smc tabwe and nevew change*/
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, wevew_awway_adwess,
				(uint8_t *)wevews, (uint32_t)wevew_awway_size,
								SMC_WAM_END);

	wetuwn wesuwt;
}

static int icewand_cawcuwate_mcwk_pawams(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU71_Discwete_MemowyWevew *mcwk,
		boow stwobe_mode,
		boow dwwStateOn
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t  dww_cntw = data->cwock_wegistews.vDWW_CNTW;
	uint32_t  mcwk_pwwmgt_cntw = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;
	uint32_t  mpww_ad_func_cntw = data->cwock_wegistews.vMPWW_AD_FUNC_CNTW;
	uint32_t  mpww_dq_func_cntw = data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW;
	uint32_t  mpww_func_cntw = data->cwock_wegistews.vMPWW_FUNC_CNTW;
	uint32_t  mpww_func_cntw_1 = data->cwock_wegistews.vMPWW_FUNC_CNTW_1;
	uint32_t  mpww_func_cntw_2 = data->cwock_wegistews.vMPWW_FUNC_CNTW_2;
	uint32_t  mpww_ss1 = data->cwock_wegistews.vMPWW_SS1;
	uint32_t  mpww_ss2 = data->cwock_wegistews.vMPWW_SS2;

	pp_atomctww_memowy_cwock_pawam mpww_pawam;
	int wesuwt;

	wesuwt = atomctww_get_memowy_pww_dividews_si(hwmgw,
				memowy_cwock, &mpww_pawam, stwobe_mode);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Ewwow wetwieving Memowy Cwock Pawametews fwom VBIOS.", wetuwn wesuwt);

	/* MPWW_FUNC_CNTW setup*/
	mpww_func_cntw = PHM_SET_FIEWD(mpww_func_cntw, MPWW_FUNC_CNTW, BWCTWW, mpww_pawam.bw_ctww);

	/* MPWW_FUNC_CNTW_1 setup*/
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, CWKF, mpww_pawam.mpww_fb_dividew.cw_kf);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, CWKFWAC, mpww_pawam.mpww_fb_dividew.cwk_fwac);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, VCO_MODE, mpww_pawam.vco_mode);

	/* MPWW_AD_FUNC_CNTW setup*/
	mpww_ad_func_cntw = PHM_SET_FIEWD(mpww_ad_func_cntw,
							MPWW_AD_FUNC_CNTW, YCWK_POST_DIV, mpww_pawam.mpww_post_dividew);

	if (data->is_memowy_gddw5) {
		/* MPWW_DQ_FUNC_CNTW setup*/
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
								MPWW_DQ_FUNC_CNTW, YCWK_SEW, mpww_pawam.ycwk_sew);
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
								MPWW_DQ_FUNC_CNTW, YCWK_POST_DIV, mpww_pawam.mpww_post_dividew);
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

static uint8_t icewand_get_mcwk_fwequency_watio(uint32_t memowy_cwock,
		boow stwobe_mode)
{
	uint8_t mc_pawa_index;

	if (stwobe_mode) {
		if (memowy_cwock < 12500) {
			mc_pawa_index = 0x00;
		} ewse if (memowy_cwock > 47500) {
			mc_pawa_index = 0x0f;
		} ewse {
			mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 2500);
		}
	} ewse {
		if (memowy_cwock < 65000) {
			mc_pawa_index = 0x00;
		} ewse if (memowy_cwock > 135000) {
			mc_pawa_index = 0x0f;
		} ewse {
			mc_pawa_index = (uint8_t)((memowy_cwock - 60000) / 5000);
		}
	}

	wetuwn mc_pawa_index;
}

static uint8_t icewand_get_ddw3_mcwk_fwequency_watio(uint32_t memowy_cwock)
{
	uint8_t mc_pawa_index;

	if (memowy_cwock < 10000) {
		mc_pawa_index = 0;
	} ewse if (memowy_cwock >= 80000) {
		mc_pawa_index = 0x0f;
	} ewse {
		mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 5000 + 1);
	}

	wetuwn mc_pawa_index;
}

static int icewand_popuwate_phase_vawue_based_on_mcwk(stwuct pp_hwmgw *hwmgw, const stwuct phm_phase_shedding_wimits_tabwe *pw,
					uint32_t memowy_cwock, uint32_t *p_shed)
{
	unsigned int i;

	*p_shed = 1;

	fow (i = 0; i < pw->count; i++) {
		if (memowy_cwock < pw->entwies[i].Mcwk) {
			*p_shed = i;
			bweak;
		}
	}

	wetuwn 0;
}

static int icewand_popuwate_singwe_memowy_wevew(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU71_Discwete_MemowyWevew *memowy_wevew
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wesuwt = 0;
	boow dww_state_on;
	uint32_t mcwk_edc_ww_enabwe_thweshowd = 40000;
	uint32_t mcwk_edc_enabwe_thweshowd = 40000;
	uint32_t mcwk_stwobe_mode_thweshowd = 40000;

	if (hwmgw->dyn_state.vddc_dependency_on_mcwk != NUWW) {
		wesuwt = icewand_get_dependency_vowt_by_cwk(hwmgw,
			hwmgw->dyn_state.vddc_dependency_on_mcwk, memowy_cwock, &memowy_wevew->MinVddc);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find MinVddc vowtage vawue fwom memowy VDDC vowtage dependency tabwe", wetuwn wesuwt);
	}

	if (data->vddci_contwow == SMU7_VOWTAGE_CONTWOW_NONE) {
		memowy_wevew->MinVddci = memowy_wevew->MinVddc;
	} ewse if (NUWW != hwmgw->dyn_state.vddci_dependency_on_mcwk) {
		wesuwt = icewand_get_dependency_vowt_by_cwk(hwmgw,
				hwmgw->dyn_state.vddci_dependency_on_mcwk,
				memowy_cwock,
				&memowy_wevew->MinVddci);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find MinVddci vowtage vawue fwom memowy VDDCI vowtage dependency tabwe", wetuwn wesuwt);
	}

	memowy_wevew->MinVddcPhases = 1;

	if (data->vddc_phase_shed_contwow) {
		icewand_popuwate_phase_vawue_based_on_mcwk(hwmgw, hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe,
				memowy_cwock, &memowy_wevew->MinVddcPhases);
	}

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

	/* stuttew mode not suppowt on icewand */

	/* decide stwobe mode*/
	memowy_wevew->StwobeEnabwe = (mcwk_stwobe_mode_thweshowd != 0) &&
		(memowy_cwock <= mcwk_stwobe_mode_thweshowd);

	/* decide EDC mode and memowy cwock watio*/
	if (data->is_memowy_gddw5) {
		memowy_wevew->StwobeWatio = icewand_get_mcwk_fwequency_watio(memowy_cwock,
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
			if (icewand_get_mcwk_fwequency_watio(memowy_cwock, 1) >=
					((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC7) >> 16) & 0xf))
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
			ewse
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC6) >> 1) & 0x1) ? 1 : 0;
		} ewse
			dww_state_on = data->dww_defauwt_on;
	} ewse {
		memowy_wevew->StwobeWatio =
			icewand_get_ddw3_mcwk_fwequency_watio(memowy_cwock);
		dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
	}

	wesuwt = icewand_cawcuwate_mcwk_pawams(hwmgw,
		memowy_cwock, memowy_wevew, memowy_wevew->StwobeEnabwe, dww_state_on);

	if (0 == wesuwt) {
		memowy_wevew->MinVddc = PP_HOST_TO_SMC_UW(memowy_wevew->MinVddc * VOWTAGE_SCAWE);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MinVddcPhases);
		memowy_wevew->MinVddci = PP_HOST_TO_SMC_UW(memowy_wevew->MinVddci * VOWTAGE_SCAWE);
		memowy_wevew->MinMvdd = PP_HOST_TO_SMC_UW(memowy_wevew->MinMvdd * VOWTAGE_SCAWE);
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

static int icewand_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	int wesuwt;

	/* popuwate MCWK dpm tabwe to SMU7 */
	uint32_t wevew_awway_adwess = smu_data->smu7_data.dpm_tabwe_stawt + offsetof(SMU71_Discwete_DpmTabwe, MemowyWevew);
	uint32_t wevew_awway_size = sizeof(SMU71_Discwete_MemowyWevew) * SMU71_MAX_WEVEWS_MEMOWY;
	SMU71_Discwete_MemowyWevew *wevews = smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;

	memset(wevews, 0x00, wevew_awway_size);

	fow (i = 0; i < dpm_tabwe->mcwk_tabwe.count; i++) {
		PP_ASSEWT_WITH_CODE((0 != dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue),
			"can not popuwate memowy wevew as memowy cwock is zewo", wetuwn -EINVAW);
		wesuwt = icewand_popuwate_singwe_memowy_wevew(hwmgw, dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue,
			&(smu_data->smc_state_tabwe.MemowyWevew[i]));
		if (0 != wesuwt) {
			wetuwn wesuwt;
		}
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
		wevew_awway_adwess, (uint8_t *)wevews, (uint32_t)wevew_awway_size,
		SMC_WAM_END);

	wetuwn wesuwt;
}

static int icewand_popuwate_mvdd_vawue(stwuct pp_hwmgw *hwmgw, uint32_t mcwk,
					SMU71_Discwete_VowtageWevew *vowtage)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t i = 0;

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->mvdd_contwow) {
		/* find mvdd vawue which cwock is mowe than wequest */
		fow (i = 0; i < hwmgw->dyn_state.mvdd_dependency_on_mcwk->count; i++) {
			if (mcwk <= hwmgw->dyn_state.mvdd_dependency_on_mcwk->entwies[i].cwk) {
				/* Awways wound to highew vowtage. */
				vowtage->Vowtage = data->mvdd_vowtage_tabwe.entwies[i].vawue;
				bweak;
			}
		}

		PP_ASSEWT_WITH_CODE(i < hwmgw->dyn_state.mvdd_dependency_on_mcwk->count,
			"MVDD Vowtage is outside the suppowted wange.", wetuwn -EINVAW);

	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int icewand_popuwate_smc_acpi_wevew(stwuct pp_hwmgw *hwmgw,
	SMU71_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	uint32_t vddc_phase_shed_contwow = 0;

	SMU71_Discwete_VowtageWevew vowtage_wevew;
	uint32_t spww_func_cntw    = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_2  = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_2;
	uint32_t dww_cntw          = data->cwock_wegistews.vDWW_CNTW;
	uint32_t mcwk_pwwmgt_cntw  = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;


	/* The ACPI state shouwd not do DPM on DC (ow evew).*/
	tabwe->ACPIWevew.Fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (data->acpi_vddc)
		tabwe->ACPIWevew.MinVddc = PP_HOST_TO_SMC_UW(data->acpi_vddc * VOWTAGE_SCAWE);
	ewse
		tabwe->ACPIWevew.MinVddc = PP_HOST_TO_SMC_UW(data->min_vddc_in_pptabwe * VOWTAGE_SCAWE);

	tabwe->ACPIWevew.MinVddcPhases = vddc_phase_shed_contwow ? 0 : 1;
	/* assign zewo fow now*/
	tabwe->ACPIWevew.ScwkFwequency = atomctww_get_wefewence_cwock(hwmgw);

	/* get the engine cwock dividews fow this cwock vawue*/
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw,
		tabwe->ACPIWevew.ScwkFwequency,  &dividews);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.", wetuwn wesuwt);

	/* dividew ID fow wequiwed SCWK*/
	tabwe->ACPIWevew.ScwkDid = (uint8_t)dividews.pww_post_dividew;
	tabwe->ACPIWevew.DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;
	tabwe->ACPIWevew.DeepSweepDivId = 0;

	spww_func_cntw      = PHM_SET_FIEWD(spww_func_cntw,
							CG_SPWW_FUNC_CNTW,   SPWW_PWWON,     0);
	spww_func_cntw      = PHM_SET_FIEWD(spww_func_cntw,
							CG_SPWW_FUNC_CNTW,   SPWW_WESET,     1);
	spww_func_cntw_2    = PHM_SET_FIEWD(spww_func_cntw_2,
							CG_SPWW_FUNC_CNTW_2, SCWK_MUX_SEW,   4);

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
	tabwe->MemowyACPIWevew.MinVddc = tabwe->ACPIWevew.MinVddc;
	tabwe->MemowyACPIWevew.MinVddcPhases = tabwe->ACPIWevew.MinVddcPhases;

	if (SMU7_VOWTAGE_CONTWOW_NONE == data->vddci_contwow)
		tabwe->MemowyACPIWevew.MinVddci = tabwe->MemowyACPIWevew.MinVddc;
	ewse {
		if (data->acpi_vddci != 0)
			tabwe->MemowyACPIWevew.MinVddci = PP_HOST_TO_SMC_UW(data->acpi_vddci * VOWTAGE_SCAWE);
		ewse
			tabwe->MemowyACPIWevew.MinVddci = PP_HOST_TO_SMC_UW(data->min_vddci_in_pptabwe * VOWTAGE_SCAWE);
	}

	if (0 == icewand_popuwate_mvdd_vawue(hwmgw, 0, &vowtage_wevew))
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
	tabwe->MemowyACPIWevew.ActivityWevew = PP_HOST_TO_SMC_US(data->cuwwent_pwofiwe_setting.mcwk_activity);

	tabwe->MemowyACPIWevew.StuttewEnabwe = 0;
	tabwe->MemowyACPIWevew.StwobeEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWeadEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWwiteEnabwe = 0;
	tabwe->MemowyACPIWevew.WttEnabwe = 0;

	wetuwn wesuwt;
}

static int icewand_popuwate_smc_uvd_wevew(stwuct pp_hwmgw *hwmgw,
					SMU71_Discwete_DpmTabwe *tabwe)
{
	wetuwn 0;
}

static int icewand_popuwate_smc_vce_wevew(stwuct pp_hwmgw *hwmgw,
		SMU71_Discwete_DpmTabwe *tabwe)
{
	wetuwn 0;
}

static int icewand_popuwate_smc_acp_wevew(stwuct pp_hwmgw *hwmgw,
		SMU71_Discwete_DpmTabwe *tabwe)
{
	wetuwn 0;
}

static int icewand_popuwate_memowy_timing_pawametews(
		stwuct pp_hwmgw *hwmgw,
		uint32_t engine_cwock,
		uint32_t memowy_cwock,
		stwuct SMU71_Discwete_MCAwbDwamTimingTabweEntwy *awb_wegs
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

static int icewand_pwogwam_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	int wesuwt = 0;
	SMU71_Discwete_MCAwbDwamTimingTabwe  awb_wegs;
	uint32_t i, j;

	memset(&awb_wegs, 0x00, sizeof(SMU71_Discwete_MCAwbDwamTimingTabwe));

	fow (i = 0; i < data->dpm_tabwe.scwk_tabwe.count; i++) {
		fow (j = 0; j < data->dpm_tabwe.mcwk_tabwe.count; j++) {
			wesuwt = icewand_popuwate_memowy_timing_pawametews
				(hwmgw, data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue,
				 data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue,
				 &awb_wegs.entwies[i][j]);

			if (0 != wesuwt) {
				bweak;
			}
		}
	}

	if (0 == wesuwt) {
		wesuwt = smu7_copy_bytes_to_smc(
				hwmgw,
				smu_data->smu7_data.awb_tabwe_stawt,
				(uint8_t *)&awb_wegs,
				sizeof(SMU71_Discwete_MCAwbDwamTimingTabwe),
				SMC_WAM_END
				);
	}

	wetuwn wesuwt;
}

static int icewand_popuwate_smc_boot_wevew(stwuct pp_hwmgw *hwmgw,
			SMU71_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	/* find boot wevew fwom dpm tabwe*/
	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.scwk_tabwe),
			data->vbios_boot_state.scwk_bootup_vawue,
			(uint32_t *)&(smu_data->smc_state_tabwe.GwaphicsBootWevew));

	if (0 != wesuwt) {
		smu_data->smc_state_tabwe.GwaphicsBootWevew = 0;
		pw_eww("VBIOS did not find boot engine cwock vawue in dependency tabwe. Using Gwaphics DPM wevew 0!\n");
		wesuwt = 0;
	}

	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.mcwk_tabwe),
		data->vbios_boot_state.mcwk_bootup_vawue,
		(uint32_t *)&(smu_data->smc_state_tabwe.MemowyBootWevew));

	if (0 != wesuwt) {
		smu_data->smc_state_tabwe.MemowyBootWevew = 0;
		pw_eww("VBIOS did not find boot engine cwock vawue in dependency tabwe. Using Memowy DPM wevew 0!\n");
		wesuwt = 0;
	}

	tabwe->BootVddc = data->vbios_boot_state.vddc_bootup_vawue;
	if (SMU7_VOWTAGE_CONTWOW_NONE == data->vddci_contwow)
		tabwe->BootVddci = tabwe->BootVddc;
	ewse
		tabwe->BootVddci = data->vbios_boot_state.vddci_bootup_vawue;

	tabwe->BootMVdd = data->vbios_boot_state.mvdd_bootup_vawue;

	wetuwn wesuwt;
}

static int icewand_popuwate_mc_weg_addwess(stwuct pp_hwmgw *hwmgw,
				 SMU71_Discwete_MCWegistews *mc_weg_tabwe)
{
	const stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)hwmgw->smu_backend;

	uint32_t i, j;

	fow (i = 0, j = 0; j < smu_data->mc_weg_tabwe.wast; j++) {
		if (smu_data->mc_weg_tabwe.vawidfwag & 1<<j) {
			PP_ASSEWT_WITH_CODE(i < SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE,
				"Index of mc_weg_tabwe->addwess[] awway out of boundawy", wetuwn -EINVAW);
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
static void icewand_convewt_mc_wegistews(
	const stwuct icewand_mc_weg_entwy *entwy,
	SMU71_Discwete_MCWegistewSet *data,
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

static int icewand_convewt_mc_weg_tabwe_entwy_to_smc(stwuct pp_hwmgw *hwmgw,
		const uint32_t memowy_cwock,
		SMU71_Discwete_MCWegistewSet *mc_weg_tabwe_data
		)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint32_t i = 0;

	fow (i = 0; i < smu_data->mc_weg_tabwe.num_entwies; i++) {
		if (memowy_cwock <=
			smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max) {
			bweak;
		}
	}

	if ((i == smu_data->mc_weg_tabwe.num_entwies) && (i > 0))
		--i;

	icewand_convewt_mc_wegistews(&smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i],
				mc_weg_tabwe_data, smu_data->mc_weg_tabwe.wast,
				smu_data->mc_weg_tabwe.vawidfwag);

	wetuwn 0;
}

static int icewand_convewt_mc_weg_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
		SMU71_Discwete_MCWegistews *mc_wegs)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wes;
	uint32_t i;

	fow (i = 0; i < data->dpm_tabwe.mcwk_tabwe.count; i++) {
		wes = icewand_convewt_mc_weg_tabwe_entwy_to_smc(
				hwmgw,
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[i].vawue,
				&mc_wegs->data[i]
				);

		if (0 != wes)
			wesuwt = wes;
	}

	wetuwn wesuwt;
}

static int icewand_update_and_upwoad_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t addwess;
	int32_t wesuwt;

	if (0 == (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_MCWK))
		wetuwn 0;


	memset(&smu_data->mc_wegs, 0, sizeof(SMU71_Discwete_MCWegistews));

	wesuwt = icewand_convewt_mc_weg_tabwe_to_smc(hwmgw, &(smu_data->mc_wegs));

	if (wesuwt != 0)
		wetuwn wesuwt;


	addwess = smu_data->smu7_data.mc_weg_tabwe_stawt + (uint32_t)offsetof(SMU71_Discwete_MCWegistews, data[0]);

	wetuwn  smu7_copy_bytes_to_smc(hwmgw, addwess,
				 (uint8_t *)&smu_data->mc_wegs.data[0],
				sizeof(SMU71_Discwete_MCWegistewSet) * data->dpm_tabwe.mcwk_tabwe.count,
				SMC_WAM_END);
}

static int icewand_popuwate_initiaw_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);

	memset(&smu_data->mc_wegs, 0x00, sizeof(SMU71_Discwete_MCWegistews));
	wesuwt = icewand_popuwate_mc_weg_addwess(hwmgw, &(smu_data->mc_wegs));
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize MCWegTabwe fow the MC wegistew addwesses!", wetuwn wesuwt;);

	wesuwt = icewand_convewt_mc_weg_tabwe_to_smc(hwmgw, &smu_data->mc_wegs);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize MCWegTabwe fow dwivew state!", wetuwn wesuwt;);

	wetuwn smu7_copy_bytes_to_smc(hwmgw, smu_data->smu7_data.mc_weg_tabwe_stawt,
			(uint8_t *)&smu_data->mc_wegs, sizeof(SMU71_Discwete_MCWegistews), SMC_WAM_END);
}

static int icewand_popuwate_smc_initiaw_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	uint8_t count, wevew;

	count = (uint8_t)(hwmgw->dyn_state.vddc_dependency_on_scwk->count);

	fow (wevew = 0; wevew < count; wevew++) {
		if (hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[wevew].cwk
			 >= data->vbios_boot_state.scwk_bootup_vawue) {
			smu_data->smc_state_tabwe.GwaphicsBootWevew = wevew;
			bweak;
		}
	}

	count = (uint8_t)(hwmgw->dyn_state.vddc_dependency_on_mcwk->count);

	fow (wevew = 0; wevew < count; wevew++) {
		if (hwmgw->dyn_state.vddc_dependency_on_mcwk->entwies[wevew].cwk
			>= data->vbios_boot_state.mcwk_bootup_vawue) {
			smu_data->smc_state_tabwe.MemowyBootWevew = wevew;
			bweak;
		}
	}

	wetuwn 0;
}

static int icewand_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	const stwuct icewand_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	SMU71_Discwete_DpmTabwe  *dpm_tabwe = &(smu_data->smc_state_tabwe);
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe = hwmgw->dyn_state.cac_dtp_tabwe;
	stwuct phm_ppm_tabwe *ppm = hwmgw->dyn_state.ppm_pawametew_tabwe;
	const uint16_t *def1, *def2;
	int i, j, k;


	/*
	 * TDP numbew of fwaction bits awe changed fwom 8 to 7 fow Icewand
	 * as wequested by SMC team
	 */

	dpm_tabwe->DefauwtTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usTDP * 256));
	dpm_tabwe->TawgetTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usConfiguwabweTDP * 256));


	dpm_tabwe->DTETjOffset = 0;

	dpm_tabwe->GpuTjMax = (uint8_t)(data->thewmaw_temp_setting.tempewatuwe_high / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES);
	dpm_tabwe->GpuTjHyst = 8;

	dpm_tabwe->DTEAmbientTempBase = defauwts->dte_ambient_temp_base;

	/* The fowwowing awe fow new Icewand Muwti-input fan/thewmaw contwow */
	if (NUWW != ppm) {
		dpm_tabwe->PPM_PkgPwwWimit = (uint16_t)ppm->dgpu_tdp * 256 / 1000;
		dpm_tabwe->PPM_TempewatuweWimit = (uint16_t)ppm->tj_max * 256;
	} ewse {
		dpm_tabwe->PPM_PkgPwwWimit = 0;
		dpm_tabwe->PPM_TempewatuweWimit = 0;
	}

	CONVEWT_FWOM_HOST_TO_SMC_US(dpm_tabwe->PPM_PkgPwwWimit);
	CONVEWT_FWOM_HOST_TO_SMC_US(dpm_tabwe->PPM_TempewatuweWimit);

	dpm_tabwe->BAPM_TEMP_GWADIENT = PP_HOST_TO_SMC_UW(defauwts->bapm_temp_gwadient);
	def1 = defauwts->bapmti_w;
	def2 = defauwts->bapmti_wc;

	fow (i = 0; i < SMU71_DTE_ITEWATIONS; i++) {
		fow (j = 0; j < SMU71_DTE_SOUWCES; j++) {
			fow (k = 0; k < SMU71_DTE_SINKS; k++) {
				dpm_tabwe->BAPMTI_W[i][j][k] = PP_HOST_TO_SMC_US(*def1);
				dpm_tabwe->BAPMTI_WC[i][j][k] = PP_HOST_TO_SMC_US(*def2);
				def1++;
				def2++;
			}
		}
	}

	wetuwn 0;
}

static int icewand_popuwate_smc_svi2_config(stwuct pp_hwmgw *hwmgw,
					    SMU71_Discwete_DpmTabwe *tab)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow)
		tab->SVI2Enabwe |= VDDC_ON_SVI2;

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow)
		tab->SVI2Enabwe |= VDDCI_ON_SVI2;
	ewse
		tab->MewgedVddci = 1;

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->mvdd_contwow)
		tab->SVI2Enabwe |= MVDD_ON_SVI2;

	PP_ASSEWT_WITH_CODE(tab->SVI2Enabwe != (VDDC_ON_SVI2 | VDDCI_ON_SVI2 | MVDD_ON_SVI2) &&
		(tab->SVI2Enabwe & VDDC_ON_SVI2), "SVI2 domain configuwation is incowwect!", wetuwn -EINVAW);

	wetuwn 0;
}

static int icewand_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	SMU71_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);


	icewand_initiawize_powew_tune_defauwts(hwmgw);
	memset(&(smu_data->smc_state_tabwe), 0x00, sizeof(smu_data->smc_state_tabwe));

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->vowtage_contwow) {
		icewand_popuwate_smc_vowtage_tabwes(hwmgw, tabwe);
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;


	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StepVddc))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (data->is_memowy_gddw5)
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GDDW5;


	if (data->uwv_suppowted) {
		wesuwt = icewand_popuwate_uwv_state(hwmgw, &(smu_data->uwv_setting));
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize UWV state!", wetuwn wesuwt;);

		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixCG_UWV_PAWAMETEW, 0x40035);
	}

	wesuwt = icewand_popuwate_smc_wink_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Wink Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_aww_gwaphic_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Gwaphics Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_aww_memowy_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Memowy Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_smc_acpi_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize ACPI Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_smc_vce_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize VCE Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_smc_acp_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize ACP Wevew!", wetuwn wesuwt;);

	/* Since onwy the initiaw state is compwetewy set up at this point (the othew states awe just copies of the boot state) we onwy */
	/* need to popuwate the  AWB settings fow the initiaw state. */
	wesuwt = icewand_pwogwam_memowy_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to Wwite AWB settings fow the initiaw state.", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_smc_uvd_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize UVD Wevew!", wetuwn wesuwt;);

	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	wesuwt = icewand_popuwate_smc_boot_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Boot Wevew!", wetuwn wesuwt;);

	wesuwt = icewand_popuwate_smc_initiaw_state(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt, "Faiwed to initiawize Boot State!", wetuwn wesuwt);

	wesuwt = icewand_popuwate_bapm_pawametews_in_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt, "Faiwed to popuwate BAPM Pawametews!", wetuwn wesuwt);

	tabwe->GwaphicsVowtageChangeEnabwe  = 1;
	tabwe->GwaphicsThewmThwottweEnabwe  = 1;
	tabwe->GwaphicsIntewvaw = 1;
	tabwe->VowtageIntewvaw  = 1;
	tabwe->ThewmawIntewvaw  = 1;

	tabwe->TempewatuweWimitHigh =
		(data->thewmaw_temp_setting.tempewatuwe_high *
		 SMU7_Q88_FOWMAT_CONVEWSION_UNIT) / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	tabwe->TempewatuweWimitWow =
		(data->thewmaw_temp_setting.tempewatuwe_wow *
		SMU7_Q88_FOWMAT_CONVEWSION_UNIT) / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	tabwe->MemowyVowtageChangeEnabwe  = 1;
	tabwe->MemowyIntewvaw  = 1;
	tabwe->VowtageWesponseTime  = 0;
	tabwe->PhaseWesponseTime  = 0;
	tabwe->MemowyThewmThwottweEnabwe  = 1;
	tabwe->PCIeBootWinkWevew = 0;
	tabwe->PCIeGenIntewvaw = 1;

	wesuwt = icewand_popuwate_smc_svi2_config(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to popuwate SVI2 setting!", wetuwn wesuwt);

	tabwe->ThewmGpio  = 17;
	tabwe->ScwkStepSize = 0x4000;

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SystemFwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddcVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddcPhase);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddciVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskMvddVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ScwkStepSize);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitHigh);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitWow);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VowtageWesponseTime);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->PhaseWesponseTime);

	tabwe->BootVddc = PP_HOST_TO_SMC_US(tabwe->BootVddc * VOWTAGE_SCAWE);
	tabwe->BootVddci = PP_HOST_TO_SMC_US(tabwe->BootVddci * VOWTAGE_SCAWE);
	tabwe->BootMVdd = PP_HOST_TO_SMC_US(tabwe->BootMVdd * VOWTAGE_SCAWE);

	/* Upwoad aww dpm data to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, smu_data->smu7_data.dpm_tabwe_stawt +
										offsetof(SMU71_Discwete_DpmTabwe, SystemFwags),
										(uint8_t *)&(tabwe->SystemFwags),
										sizeof(SMU71_Discwete_DpmTabwe)-3 * sizeof(SMU71_PIDContwowwew),
										SMC_WAM_END);

	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to upwoad dpm data to SMC memowy!", wetuwn wesuwt;);

	/* Upwoad aww uwv setting to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw,
			smu_data->smu7_data.uwv_setting_stawts,
			(uint8_t *)&(smu_data->uwv_setting),
			sizeof(SMU71_Discwete_Uwv),
			SMC_WAM_END);


	wesuwt = icewand_popuwate_initiaw_mc_weg_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
		"Faiwed to popuwate initiawize MC Weg tabwe!", wetuwn wesuwt);

	wesuwt = icewand_popuwate_pm_fuses(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to  popuwate PM fuses to SMC memowy!", wetuwn wesuwt);

	wetuwn 0;
}

static int icewand_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_smumgw *smu7_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);
	SMU71_Discwete_FanTabwe fan_tabwe = { FDO_MODE_HAWDWAWE };
	uint32_t duty100;
	uint32_t t_diff1, t_diff2, pwm_diff1, pwm_diff2;
	uint16_t fdo_min, swope1, swope2;
	uint32_t wefewence_cwock;
	int wes;
	uint64_t tmp64;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow))
		wetuwn 0;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	if (0 == smu7_data->fan_tabwe_stawt) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, CG_FDO_CTWW1, FMAX_DUTY100);

	if (0 == duty100) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	tmp64 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin * duty100;
	do_div(tmp64, 10000);
	fdo_min = (uint16_t)tmp64;

	t_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin;
	t_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed;

	pwm_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin;
	pwm_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed;

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

	/* fan_tabwe.FanContwow_GW_Fwag = 1; */

	wes = smu7_copy_bytes_to_smc(hwmgw, smu7_data->fan_tabwe_stawt, (uint8_t *)&fan_tabwe, (uint32_t)sizeof(fan_tabwe), SMC_WAM_END);

	wetuwn wes;
}


static int icewand_pwogwam_mem_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->need_update_smu7_dpm_tabwe &
		(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_OD_UPDATE_MCWK))
		wetuwn icewand_pwogwam_memowy_timing_pawametews(hwmgw);

	wetuwn 0;
}

static int icewand_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);

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
				offsetof(SMU71_Discwete_DpmTabwe,
					WowScwkIntewwuptThweshowd),
				(uint8_t *)&wow_scwk_intewwupt_thweshowd,
				sizeof(uint32_t),
				SMC_WAM_END);
	}

	wesuwt = icewand_update_and_upwoad_mc_weg_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((0 == wesuwt), "Faiwed to upwoad MC weg tabwe!", wetuwn wesuwt);

	wesuwt = icewand_pwogwam_mem_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to pwogwam memowy timing pawametews!",
			);

	wetuwn wesuwt;
}

static uint32_t icewand_get_offsetof(uint32_t type, uint32_t membew)
{
	switch (type) {
	case SMU_SoftWegistews:
		switch (membew) {
		case HandshakeDisabwes:
			wetuwn offsetof(SMU71_SoftWegistews, HandshakeDisabwes);
		case VowtageChangeTimeout:
			wetuwn offsetof(SMU71_SoftWegistews, VowtageChangeTimeout);
		case AvewageGwaphicsActivity:
			wetuwn offsetof(SMU71_SoftWegistews, AvewageGwaphicsActivity);
		case AvewageMemowyActivity:
			wetuwn offsetof(SMU71_SoftWegistews, AvewageMemowyActivity);
		case PweVBwankGap:
			wetuwn offsetof(SMU71_SoftWegistews, PweVBwankGap);
		case VBwankTimeout:
			wetuwn offsetof(SMU71_SoftWegistews, VBwankTimeout);
		case UcodeWoadStatus:
			wetuwn offsetof(SMU71_SoftWegistews, UcodeWoadStatus);
		case DWAM_WOG_ADDW_H:
			wetuwn offsetof(SMU71_SoftWegistews, DWAM_WOG_ADDW_H);
		case DWAM_WOG_ADDW_W:
			wetuwn offsetof(SMU71_SoftWegistews, DWAM_WOG_ADDW_W);
		case DWAM_WOG_PHY_ADDW_H:
			wetuwn offsetof(SMU71_SoftWegistews, DWAM_WOG_PHY_ADDW_H);
		case DWAM_WOG_PHY_ADDW_W:
			wetuwn offsetof(SMU71_SoftWegistews, DWAM_WOG_PHY_ADDW_W);
		case DWAM_WOG_BUFF_SIZE:
			wetuwn offsetof(SMU71_SoftWegistews, DWAM_WOG_BUFF_SIZE);
		}
		bweak;
	case SMU_Discwete_DpmTabwe:
		switch (membew) {
		case WowScwkIntewwuptThweshowd:
			wetuwn offsetof(SMU71_Discwete_DpmTabwe, WowScwkIntewwuptThweshowd);
		}
		bweak;
	}
	pw_wawn("can't get the offset of type %x membew %x\n", type, membew);
	wetuwn 0;
}

static uint32_t icewand_get_mac_definition(uint32_t vawue)
{
	switch (vawue) {
	case SMU_MAX_WEVEWS_GWAPHICS:
		wetuwn SMU71_MAX_WEVEWS_GWAPHICS;
	case SMU_MAX_WEVEWS_MEMOWY:
		wetuwn SMU71_MAX_WEVEWS_MEMOWY;
	case SMU_MAX_WEVEWS_WINK:
		wetuwn SMU71_MAX_WEVEWS_WINK;
	case SMU_MAX_ENTWIES_SMIO:
		wetuwn SMU71_MAX_ENTWIES_SMIO;
	case SMU_MAX_WEVEWS_VDDC:
	case SMU_MAX_WEVEWS_VDDGFX:
		wetuwn SMU71_MAX_WEVEWS_VDDC;
	case SMU_MAX_WEVEWS_VDDCI:
		wetuwn SMU71_MAX_WEVEWS_VDDCI;
	case SMU_MAX_WEVEWS_MVDD:
		wetuwn SMU71_MAX_WEVEWS_MVDD;
	}

	pw_wawn("can't get the mac of %x\n", vawue);
	wetuwn 0;
}

static int icewand_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_smumgw *smu7_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	uint32_t tmp;
	int wesuwt;
	boow ewwow = fawse;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, DpmTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		smu7_data->dpm_tabwe_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, SoftWegistews),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		data->soft_wegs_stawt = tmp;
		smu7_data->soft_wegs_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);


	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, mcWegistewTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		smu7_data->mc_weg_tabwe_stawt = tmp;
	}

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, FanTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		smu7_data->fan_tabwe_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, mcAwbDwamTimingTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		smu7_data->awb_tabwe_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);


	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, Vewsion),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		hwmgw->micwocode_vewsion_info.SMC = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU71_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU71_Fiwmwawe_Headew, UwvSettings),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		smu7_data->uwv_setting_stawts = tmp;
	}

	ewwow |= (0 != wesuwt);

	wetuwn ewwow ? 1 : 0;
}

/*---------------------------MC----------------------------*/

static uint8_t icewand_get_memowy_modiwe_index(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (uint8_t) (0xFF & (cgs_wead_wegistew(hwmgw->device, mmBIOS_SCWATCH_4) >> 16));
}

static boow icewand_check_s0_mc_weg_index(uint16_t in_weg, uint16_t *out_weg)
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

static int icewand_set_s0_mc_weg_index(stwuct icewand_mc_weg_tabwe *tabwe)
{
	uint32_t i;
	uint16_t addwess;

	fow (i = 0; i < tabwe->wast; i++) {
		tabwe->mc_weg_addwess[i].s0 =
			icewand_check_s0_mc_weg_index(tabwe->mc_weg_addwess[i].s1, &addwess)
			? addwess : tabwe->mc_weg_addwess[i].s1;
	}
	wetuwn 0;
}

static int icewand_copy_vbios_smc_weg_tabwe(const pp_atomctww_mc_weg_tabwe *tabwe,
					stwuct icewand_mc_weg_tabwe *ni_tabwe)
{
	uint8_t i, j;

	PP_ASSEWT_WITH_CODE((tabwe->wast <= SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((tabwe->num_entwies <= MAX_AC_TIMING_ENTWIES),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

	fow (i = 0; i < tabwe->wast; i++) {
		ni_tabwe->mc_weg_addwess[i].s1 = tabwe->mc_weg_addwess[i].s1;
	}
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

static int icewand_set_mc_speciaw_wegistews(stwuct pp_hwmgw *hwmgw,
					stwuct icewand_mc_weg_tabwe *tabwe)
{
	uint8_t i, j, k;
	uint32_t temp_weg;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	fow (i = 0, j = tabwe->wast; i < tabwe->wast; i++) {
		PP_ASSEWT_WITH_CODE((j < SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
			"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

		switch (tabwe->mc_weg_addwess[i].s1) {

		case mmMC_SEQ_MISC1:
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_EMWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_EMWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_EMWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					((temp_weg & 0xffff0000)) |
					((tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16);
			}
			j++;

			PP_ASSEWT_WITH_CODE((j < SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
				"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_MWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_MWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);

				if (!data->is_memowy_gddw5) {
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] |= 0x100;
				}
			}
			j++;

			if (!data->is_memowy_gddw5) {
				PP_ASSEWT_WITH_CODE((j < SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
					"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
				tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_AUTO_CMD;
				tabwe->mc_weg_addwess[j].s0 = mmMC_PMG_AUTO_CMD;
				fow (k = 0; k < tabwe->num_entwies; k++) {
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
						(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16;
				}
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

static int icewand_set_vawid_fwag(stwuct icewand_mc_weg_tabwe *tabwe)
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

static int icewand_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct icewand_smumgw *smu_data = (stwuct icewand_smumgw *)(hwmgw->smu_backend);
	pp_atomctww_mc_weg_tabwe *tabwe;
	stwuct icewand_mc_weg_tabwe *ni_tabwe = &smu_data->mc_weg_tabwe;
	uint8_t moduwe_index = icewand_get_memowy_modiwe_index(hwmgw);

	tabwe = kzawwoc(sizeof(pp_atomctww_mc_weg_tabwe), GFP_KEWNEW);

	if (NUWW == tabwe)
		wetuwn -ENOMEM;

	/* Pwogwam additionaw WP wegistews that awe no wongew pwogwammed by VBIOS */
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_EMWS_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_EMWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2));

	wesuwt = atomctww_initiawize_mc_weg_tabwe(hwmgw, moduwe_index, tabwe);

	if (0 == wesuwt)
		wesuwt = icewand_copy_vbios_smc_weg_tabwe(tabwe, ni_tabwe);

	if (0 == wesuwt) {
		icewand_set_s0_mc_weg_index(ni_tabwe);
		wesuwt = icewand_set_mc_speciaw_wegistews(hwmgw, ni_tabwe);
	}

	if (0 == wesuwt)
		icewand_set_vawid_fwag(ni_tabwe);

	kfwee(tabwe);

	wetuwn wesuwt;
}

static boow icewand_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (1 == PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, FEATUWE_STATUS, VOWTAGE_CONTWOWWEW_ON))
			? twue : fawse;
}

const stwuct pp_smumgw_func icewand_smu_funcs = {
	.name = "icewand_smu",
	.smu_init = &icewand_smu_init,
	.smu_fini = &smu7_smu_fini,
	.stawt_smu = &icewand_stawt_smu,
	.check_fw_woad_finish = &smu7_check_fw_woad_finish,
	.wequest_smu_woad_fw = &smu7_wequest_smu_woad_fw,
	.wequest_smu_woad_specific_fw = &icewand_wequest_smu_woad_specific_fw,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &smu7_send_msg_to_smc_with_pawametew,
	.get_awgument = smu7_get_awgument,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.get_offsetof = icewand_get_offsetof,
	.pwocess_fiwmwawe_headew = icewand_pwocess_fiwmwawe_headew,
	.init_smc_tabwe = icewand_init_smc_tabwe,
	.update_scwk_thweshowd = icewand_update_scwk_thweshowd,
	.thewmaw_setup_fan_tabwe = icewand_thewmaw_setup_fan_tabwe,
	.popuwate_aww_gwaphic_wevews = icewand_popuwate_aww_gwaphic_wevews,
	.popuwate_aww_memowy_wevews = icewand_popuwate_aww_memowy_wevews,
	.get_mac_definition = icewand_get_mac_definition,
	.initiawize_mc_weg_tabwe = icewand_initiawize_mc_weg_tabwe,
	.is_dpm_wunning = icewand_is_dpm_wunning,
};

