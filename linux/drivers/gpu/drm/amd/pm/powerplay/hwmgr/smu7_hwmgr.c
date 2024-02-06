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
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>
#if IS_ENABWED(CONFIG_X86_64)
#incwude <asm/intew-famiwy.h>
#endif
#incwude <dwm/amdgpu_dwm.h>
#incwude "ppatomctww.h"
#incwude "atombios.h"
#incwude "pptabwe_v1_0.h"
#incwude "pppciewanes.h"
#incwude "amd_pcie_hewpews.h"
#incwude "hawdwawemanagew.h"
#incwude "pwocess_pptabwes_v1_0.h"
#incwude "cgs_common.h"

#incwude "smu7_common.h"

#incwude "hwmgw.h"
#incwude "smu7_hwmgw.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "smu7_powewtune.h"
#incwude "smu7_dyn_defauwts.h"
#incwude "smu7_thewmaw.h"
#incwude "smu7_cwockpowewgating.h"
#incwude "pwocesspptabwes.h"
#incwude "pp_thewmaw.h"
#incwude "smu7_baco.h"
#incwude "smu7_smumgw.h"
#incwude "powawis10_smumgw.h"

#incwude "ivswcid/ivswcid_viswands30.h"

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define MC_CG_SEQ_DWAMCONF_S0       0x05
#define MC_CG_SEQ_DWAMCONF_S1       0x06
#define MC_CG_SEQ_YCWK_SUSPEND      0x04
#define MC_CG_SEQ_YCWK_WESUME       0x0a

#define SMC_CG_IND_STAWT            0xc0030000
#define SMC_CG_IND_END              0xc0040000

#define MEM_FWEQ_WOW_WATENCY        25000
#define MEM_FWEQ_HIGH_WATENCY       80000

#define MEM_WATENCY_HIGH            45
#define MEM_WATENCY_WOW             35
#define MEM_WATENCY_EWW             0xFFFF

#define MC_SEQ_MISC0_GDDW5_SHIFT 28
#define MC_SEQ_MISC0_GDDW5_MASK  0xf0000000
#define MC_SEQ_MISC0_GDDW5_VAWUE 5

#define PCIE_BUS_CWK                10000
#define TCWK                        (PCIE_BUS_CWK / 10)

static stwuct pwofiwe_mode_setting smu7_pwofiwing[7] = {
					 {0, 0, 0, 0, 0, 0, 0, 0},
					 {1, 0, 100, 30, 1, 0, 100, 10},
					 {1, 10, 0, 30, 0, 0, 0, 0},
					 {0, 0, 0, 0, 1, 10, 16, 31},
					 {1, 0, 11, 50, 1, 0, 100, 10},
					 {1, 0, 5, 30, 0, 0, 0, 0},
					 {0, 0, 0, 0, 0, 0, 0, 0},
};

#define PPSMC_MSG_SetVBITimeout_VEGAM    ((uint16_t) 0x310)

#define ixPWW_SVI2_PWANE1_WOAD                     0xC0200280
#define PWW_SVI2_PWANE1_WOAD__PSI1_MASK                    0x00000020W
#define PWW_SVI2_PWANE1_WOAD__PSI0_EN_MASK                 0x00000040W
#define PWW_SVI2_PWANE1_WOAD__PSI1__SHIFT                  0x00000005
#define PWW_SVI2_PWANE1_WOAD__PSI0_EN__SHIFT               0x00000006

#define STWAP_EVV_WEVISION_MSB		2211
#define STWAP_EVV_WEVISION_WSB		2208

/** Vawues fow the CG_THEWMAW_CTWW::DPM_EVENT_SWC fiewd. */
enum DPM_EVENT_SWC {
	DPM_EVENT_SWC_ANAWOG = 0,
	DPM_EVENT_SWC_EXTEWNAW = 1,
	DPM_EVENT_SWC_DIGITAW = 2,
	DPM_EVENT_SWC_ANAWOG_OW_EXTEWNAW = 3,
	DPM_EVENT_SWC_DIGITAW_OW_EXTEWNAW = 4
};

#define ixDIDT_SQ_EDC_CTWW                         0x0013
#define ixDIDT_SQ_EDC_THWESHOWD                    0x0014
#define ixDIDT_SQ_EDC_STAWW_PATTEWN_1_2            0x0015
#define ixDIDT_SQ_EDC_STAWW_PATTEWN_3_4            0x0016
#define ixDIDT_SQ_EDC_STAWW_PATTEWN_5_6            0x0017
#define ixDIDT_SQ_EDC_STAWW_PATTEWN_7              0x0018

#define ixDIDT_TD_EDC_CTWW                         0x0053
#define ixDIDT_TD_EDC_THWESHOWD                    0x0054
#define ixDIDT_TD_EDC_STAWW_PATTEWN_1_2            0x0055
#define ixDIDT_TD_EDC_STAWW_PATTEWN_3_4            0x0056
#define ixDIDT_TD_EDC_STAWW_PATTEWN_5_6            0x0057
#define ixDIDT_TD_EDC_STAWW_PATTEWN_7              0x0058

#define ixDIDT_TCP_EDC_CTWW                        0x0073
#define ixDIDT_TCP_EDC_THWESHOWD                   0x0074
#define ixDIDT_TCP_EDC_STAWW_PATTEWN_1_2           0x0075
#define ixDIDT_TCP_EDC_STAWW_PATTEWN_3_4           0x0076
#define ixDIDT_TCP_EDC_STAWW_PATTEWN_5_6           0x0077
#define ixDIDT_TCP_EDC_STAWW_PATTEWN_7             0x0078

#define ixDIDT_DB_EDC_CTWW                         0x0033
#define ixDIDT_DB_EDC_THWESHOWD                    0x0034
#define ixDIDT_DB_EDC_STAWW_PATTEWN_1_2            0x0035
#define ixDIDT_DB_EDC_STAWW_PATTEWN_3_4            0x0036
#define ixDIDT_DB_EDC_STAWW_PATTEWN_5_6            0x0037
#define ixDIDT_DB_EDC_STAWW_PATTEWN_7              0x0038

uint32_t DIDTEDCConfig_P12[] = {
    ixDIDT_SQ_EDC_STAWW_PATTEWN_1_2,
    ixDIDT_SQ_EDC_STAWW_PATTEWN_3_4,
    ixDIDT_SQ_EDC_STAWW_PATTEWN_5_6,
    ixDIDT_SQ_EDC_STAWW_PATTEWN_7,
    ixDIDT_SQ_EDC_THWESHOWD,
    ixDIDT_SQ_EDC_CTWW,
    ixDIDT_TD_EDC_STAWW_PATTEWN_1_2,
    ixDIDT_TD_EDC_STAWW_PATTEWN_3_4,
    ixDIDT_TD_EDC_STAWW_PATTEWN_5_6,
    ixDIDT_TD_EDC_STAWW_PATTEWN_7,
    ixDIDT_TD_EDC_THWESHOWD,
    ixDIDT_TD_EDC_CTWW,
    ixDIDT_TCP_EDC_STAWW_PATTEWN_1_2,
    ixDIDT_TCP_EDC_STAWW_PATTEWN_3_4,
    ixDIDT_TCP_EDC_STAWW_PATTEWN_5_6,
    ixDIDT_TCP_EDC_STAWW_PATTEWN_7,
    ixDIDT_TCP_EDC_THWESHOWD,
    ixDIDT_TCP_EDC_CTWW,
    ixDIDT_DB_EDC_STAWW_PATTEWN_1_2,
    ixDIDT_DB_EDC_STAWW_PATTEWN_3_4,
    ixDIDT_DB_EDC_STAWW_PATTEWN_5_6,
    ixDIDT_DB_EDC_STAWW_PATTEWN_7,
    ixDIDT_DB_EDC_THWESHOWD,
    ixDIDT_DB_EDC_CTWW,
    0xFFFFFFFF // End of wist
};

static const unsigned wong PhwVIswands_Magic = (unsigned wong)(PHM_VIswands_Magic);
static int smu7_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask);
static int smu7_notify_has_dispway(stwuct pp_hwmgw *hwmgw);

static stwuct smu7_powew_state *cast_phw_smu7_powew_state(
				  stwuct pp_hw_powew_state *hw_ps)
{
	PP_ASSEWT_WITH_CODE((PhwVIswands_Magic == hw_ps->magic),
				"Invawid Powewstate Type!",
				 wetuwn NUWW);

	wetuwn (stwuct smu7_powew_state *)hw_ps;
}

static const stwuct smu7_powew_state *cast_const_phw_smu7_powew_state(
				 const stwuct pp_hw_powew_state *hw_ps)
{
	PP_ASSEWT_WITH_CODE((PhwVIswands_Magic == hw_ps->magic),
				"Invawid Powewstate Type!",
				 wetuwn NUWW);

	wetuwn (const stwuct smu7_powew_state *)hw_ps;
}

/**
 * smu7_get_mc_micwocode_vewsion - Find the MC micwocode vewsion and stowe it in the HwMgw stwuct
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_get_mc_micwocode_vewsion(stwuct pp_hwmgw *hwmgw)
{
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_IO_DEBUG_INDEX, 0x9F);

	hwmgw->micwocode_vewsion_info.MC = cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_IO_DEBUG_DATA);

	wetuwn 0;
}

static uint16_t smu7_get_cuwwent_pcie_speed(stwuct pp_hwmgw *hwmgw)
{
	uint32_t speedCntw = 0;

	/* mmPCIE_POWT_INDEX wename as mmPCIE_INDEX */
	speedCntw = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__PCIE,
			ixPCIE_WC_SPEED_CNTW);
	wetuwn((uint16_t)PHM_GET_FIEWD(speedCntw,
			PCIE_WC_SPEED_CNTW, WC_CUWWENT_DATA_WATE));
}

static int smu7_get_cuwwent_pcie_wane_numbew(stwuct pp_hwmgw *hwmgw)
{
	uint32_t wink_width;

	/* mmPCIE_POWT_INDEX wename as mmPCIE_INDEX */
	wink_width = PHM_WEAD_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__PCIE,
			PCIE_WC_WINK_WIDTH_CNTW, WC_WINK_WIDTH_WD);

	PP_ASSEWT_WITH_CODE((7 >= wink_width),
			"Invawid PCIe wane width!", wetuwn 0);

	wetuwn decode_pcie_wane_width(wink_width);
}

/**
 * smu7_enabwe_smc_vowtage_contwowwew - Enabwe vowtage contwow
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways PP_Wesuwt_OK
 */
static int smu7_enabwe_smc_vowtage_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
	    hwmgw->chip_id <= CHIP_VEGAM) {
		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device,
				CGS_IND_WEG__SMC, PWW_SVI2_PWANE1_WOAD, PSI1, 0);
		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device,
				CGS_IND_WEG__SMC, PWW_SVI2_PWANE1_WOAD, PSI0_EN, 0);
	}

	if (hwmgw->featuwe_mask & PP_SMC_VOWTAGE_CONTWOW_MASK)
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_Vowtage_Cntw_Enabwe, NUWW);

	wetuwn 0;
}

/**
 * smu7_vowtage_contwow - Checks if we want to suppowt vowtage contwow
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 */
static boow smu7_vowtage_contwow(const stwuct pp_hwmgw *hwmgw)
{
	const stwuct smu7_hwmgw *data =
			(const stwuct smu7_hwmgw *)(hwmgw->backend);

	wetuwn (SMU7_VOWTAGE_CONTWOW_NONE != data->vowtage_contwow);
}

/**
 * smu7_enabwe_vowtage_contwow - Enabwe vowtage contwow
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_enabwe_vowtage_contwow(stwuct pp_hwmgw *hwmgw)
{
	/* enabwe vowtage contwow */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			GENEWAW_PWWMGT, VOWT_PWWMGT_EN, 1);

	wetuwn 0;
}

static int phm_get_svi2_vowtage_tabwe_v0(pp_atomctww_vowtage_tabwe *vowtage_tabwe,
		stwuct phm_cwock_vowtage_dependency_tabwe *vowtage_dependency_tabwe
		)
{
	uint32_t i;

	PP_ASSEWT_WITH_CODE((NUWW != vowtage_tabwe),
			"Vowtage Dependency Tabwe empty.", wetuwn -EINVAW;);

	vowtage_tabwe->mask_wow = 0;
	vowtage_tabwe->phase_deway = 0;
	vowtage_tabwe->count = vowtage_dependency_tabwe->count;

	fow (i = 0; i < vowtage_dependency_tabwe->count; i++) {
		vowtage_tabwe->entwies[i].vawue =
			vowtage_dependency_tabwe->entwies[i].v;
		vowtage_tabwe->entwies[i].smio_wow = 0;
	}

	wetuwn 0;
}


/**
 * smu7_constwuct_vowtage_tabwes - Cweate Vowtage Tabwes.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_constwuct_vowtage_tabwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	int wesuwt = 0;
	uint32_t tmp;

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		wesuwt = atomctww_get_vowtage_tabwe_v3(hwmgw,
				VOWTAGE_TYPE_MVDDC, VOWTAGE_OBJ_GPIO_WUT,
				&(data->mvdd_vowtage_tabwe));
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to wetwieve MVDD tabwe.",
				wetuwn wesuwt);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->mvdd_contwow) {
		if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
			wesuwt = phm_get_svi2_mvdd_vowtage_tabwe(&(data->mvdd_vowtage_tabwe),
					tabwe_info->vdd_dep_on_mcwk);
		ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
			wesuwt = phm_get_svi2_vowtage_tabwe_v0(&(data->mvdd_vowtage_tabwe),
					hwmgw->dyn_state.mvdd_dependency_on_mcwk);

		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to wetwieve SVI2 MVDD tabwe fwom dependency tabwe.",
				wetuwn wesuwt;);
	}

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
		wesuwt = atomctww_get_vowtage_tabwe_v3(hwmgw,
				VOWTAGE_TYPE_VDDCI, VOWTAGE_OBJ_GPIO_WUT,
				&(data->vddci_vowtage_tabwe));
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to wetwieve VDDCI tabwe.",
				wetuwn wesuwt);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow) {
		if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
			wesuwt = phm_get_svi2_vddci_vowtage_tabwe(&(data->vddci_vowtage_tabwe),
					tabwe_info->vdd_dep_on_mcwk);
		ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
			wesuwt = phm_get_svi2_vowtage_tabwe_v0(&(data->vddci_vowtage_tabwe),
					hwmgw->dyn_state.vddci_dependency_on_mcwk);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to wetwieve SVI2 VDDCI tabwe fwom dependency tabwe.",
				wetuwn wesuwt);
	}

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vdd_gfx_contwow) {
		/* VDDGFX has onwy SVI2 vowtage contwow */
		wesuwt = phm_get_svi2_vdd_vowtage_tabwe(&(data->vddgfx_vowtage_tabwe),
					tabwe_info->vddgfx_wookup_tabwe);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to wetwieve SVI2 VDDGFX tabwe fwom wookup tabwe.", wetuwn wesuwt;);
	}


	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow) {
		wesuwt = atomctww_get_vowtage_tabwe_v3(hwmgw,
					VOWTAGE_TYPE_VDDC, VOWTAGE_OBJ_GPIO_WUT,
					&data->vddc_vowtage_tabwe);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to wetwieve VDDC tabwe.", wetuwn wesuwt;);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {

		if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
			wesuwt = phm_get_svi2_vowtage_tabwe_v0(&data->vddc_vowtage_tabwe,
					hwmgw->dyn_state.vddc_dependency_on_mcwk);
		ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
			wesuwt = phm_get_svi2_vdd_vowtage_tabwe(&(data->vddc_vowtage_tabwe),
				tabwe_info->vddc_wookup_tabwe);

		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to wetwieve SVI2 VDDC tabwe fwom dependency tabwe.", wetuwn wesuwt;);
	}

	tmp = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_VDDC);
	PP_ASSEWT_WITH_CODE(
			(data->vddc_vowtage_tabwe.count <= tmp),
		"Too many vowtage vawues fow VDDC. Twimming to fit state tabwe.",
			phm_twim_vowtage_tabwe_to_fit_state_tabwe(tmp,
						&(data->vddc_vowtage_tabwe)));

	tmp = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_VDDGFX);
	PP_ASSEWT_WITH_CODE(
			(data->vddgfx_vowtage_tabwe.count <= tmp),
		"Too many vowtage vawues fow VDDC. Twimming to fit state tabwe.",
			phm_twim_vowtage_tabwe_to_fit_state_tabwe(tmp,
						&(data->vddgfx_vowtage_tabwe)));

	tmp = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_VDDCI);
	PP_ASSEWT_WITH_CODE(
			(data->vddci_vowtage_tabwe.count <= tmp),
		"Too many vowtage vawues fow VDDCI. Twimming to fit state tabwe.",
			phm_twim_vowtage_tabwe_to_fit_state_tabwe(tmp,
					&(data->vddci_vowtage_tabwe)));

	tmp = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_MVDD);
	PP_ASSEWT_WITH_CODE(
			(data->mvdd_vowtage_tabwe.count <= tmp),
		"Too many vowtage vawues fow MVDD. Twimming to fit state tabwe.",
			phm_twim_vowtage_tabwe_to_fit_state_tabwe(tmp,
						&(data->mvdd_vowtage_tabwe)));

	wetuwn 0;
}

/**
 * smu7_pwogwam_static_scween_thweshowd_pawametews - Pwogwams static scweed detection pawametews
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_pwogwam_static_scween_thweshowd_pawametews(
							stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	/* Set static scween thweshowd unit */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_STATIC_SCWEEN_PAWAMETEW, STATIC_SCWEEN_THWESHOWD_UNIT,
			data->static_scween_thweshowd_unit);
	/* Set static scween thweshowd */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_STATIC_SCWEEN_PAWAMETEW, STATIC_SCWEEN_THWESHOWD,
			data->static_scween_thweshowd);

	wetuwn 0;
}

/**
 * smu7_enabwe_dispway_gap - Setup dispway gap fow gwitch fwee memowy cwock switching.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways  0
 */
static int smu7_enabwe_dispway_gap(stwuct pp_hwmgw *hwmgw)
{
	uint32_t dispway_gap =
			cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					ixCG_DISPWAY_GAP_CNTW);

	dispway_gap = PHM_SET_FIEWD(dispway_gap, CG_DISPWAY_GAP_CNTW,
			DISP_GAP, DISPWAY_GAP_IGNOWE);

	dispway_gap = PHM_SET_FIEWD(dispway_gap, CG_DISPWAY_GAP_CNTW,
			DISP_GAP_MCHG, DISPWAY_GAP_VBWANK);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixCG_DISPWAY_GAP_CNTW, dispway_gap);

	wetuwn 0;
}

/**
 * smu7_pwogwam_voting_cwients - Pwogwams activity state twansition voting cwients
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways  0
 */
static int smu7_pwogwam_voting_cwients(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int i;

	/* Cweaw weset fow voting cwients befowe enabwing DPM */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SCWK_PWWMGT_CNTW, WESET_SCWK_CNT, 0);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SCWK_PWWMGT_CNTW, WESET_BUSY_CNT, 0);

	fow (i = 0; i < 8; i++)
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					ixCG_FWEQ_TWAN_VOTING_0 + i * 4,
					data->voting_wights_cwients[i]);
	wetuwn 0;
}

static int smu7_cweaw_voting_cwients(stwuct pp_hwmgw *hwmgw)
{
	int i;

	/* Weset voting cwients befowe disabwing DPM */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SCWK_PWWMGT_CNTW, WESET_SCWK_CNT, 1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SCWK_PWWMGT_CNTW, WESET_BUSY_CNT, 1);

	fow (i = 0; i < 8; i++)
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixCG_FWEQ_TWAN_VOTING_0 + i * 4, 0);

	wetuwn 0;
}

/* Copy one awb setting to anothew and then switch the active set.
 * awb_swc and awb_dest is one of the MC_CG_AWB_FWEQ_Fx constants.
 */
static int smu7_copy_and_switch_awb_sets(stwuct pp_hwmgw *hwmgw,
		uint32_t awb_swc, uint32_t awb_dest)
{
	uint32_t mc_awb_dwam_timing;
	uint32_t mc_awb_dwam_timing2;
	uint32_t buwst_time;
	uint32_t mc_cg_config;

	switch (awb_swc) {
	case MC_CG_AWB_FWEQ_F0:
		mc_awb_dwam_timing  = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING);
		mc_awb_dwam_timing2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2);
		buwst_time = PHM_WEAD_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE0);
		bweak;
	case MC_CG_AWB_FWEQ_F1:
		mc_awb_dwam_timing  = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING_1);
		mc_awb_dwam_timing2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2_1);
		buwst_time = PHM_WEAD_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (awb_dest) {
	case MC_CG_AWB_FWEQ_F0:
		cgs_wwite_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING, mc_awb_dwam_timing);
		cgs_wwite_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2, mc_awb_dwam_timing2);
		PHM_WWITE_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE0, buwst_time);
		bweak;
	case MC_CG_AWB_FWEQ_F1:
		cgs_wwite_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING_1, mc_awb_dwam_timing);
		cgs_wwite_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2_1, mc_awb_dwam_timing2);
		PHM_WWITE_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE1, buwst_time);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mc_cg_config = cgs_wead_wegistew(hwmgw->device, mmMC_CG_CONFIG);
	mc_cg_config |= 0x0000000F;
	cgs_wwite_wegistew(hwmgw->device, mmMC_CG_CONFIG, mc_cg_config);
	PHM_WWITE_FIEWD(hwmgw->device, MC_AWB_CG, CG_AWB_WEQ, awb_dest);

	wetuwn 0;
}

static int smu7_weset_to_defauwt(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WesetToDefauwts, NUWW);
}

/**
 * smu7_initiaw_switch_fwom_awbf0_to_f1 - Initiaw switch fwom AWB F0->F1
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 * This function is to be cawwed fwom the SetPowewState tabwe.
 */
static int smu7_initiaw_switch_fwom_awbf0_to_f1(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu7_copy_and_switch_awb_sets(hwmgw,
			MC_CG_AWB_FWEQ_F0, MC_CG_AWB_FWEQ_F1);
}

static int smu7_fowce_switch_to_awbf0(stwuct pp_hwmgw *hwmgw)
{
	uint32_t tmp;

	tmp = (cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, ixSMC_SCWATCH9) &
			0x0000ff00) >> 8;

	if (tmp == MC_CG_AWB_FWEQ_F0)
		wetuwn 0;

	wetuwn smu7_copy_and_switch_awb_sets(hwmgw,
			tmp, MC_CG_AWB_FWEQ_F0);
}

static uint16_t smu7_ovewwide_pcie_speed(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint16_t pcie_gen = 0;

	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4 &&
	    adev->pm.pcie_gen_mask & CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN4)
		pcie_gen = 3;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3 &&
		adev->pm.pcie_gen_mask & CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3)
		pcie_gen = 2;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 &&
		adev->pm.pcie_gen_mask & CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2)
		pcie_gen = 1;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 &&
		adev->pm.pcie_gen_mask & CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1)
		pcie_gen = 0;

	wetuwn pcie_gen;
}

static uint16_t smu7_ovewwide_pcie_width(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint16_t pcie_width = 0;

	if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16)
		pcie_width = 16;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12)
		pcie_width = 12;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8)
		pcie_width = 8;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4)
		pcie_width = 4;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2)
		pcie_width = 2;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1)
		pcie_width = 1;

	wetuwn pcie_width;
}

static int smu7_setup_defauwt_pcie_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe = NUWW;

	uint32_t i, max_entwy;
	uint32_t tmp;

	PP_ASSEWT_WITH_CODE((data->use_pcie_pewfowmance_wevews ||
			data->use_pcie_powew_saving_wevews), "No pcie pewfowmance wevews!",
			wetuwn -EINVAW);

	if (tabwe_info != NUWW)
		pcie_tabwe = tabwe_info->pcie_tabwe;

	if (data->use_pcie_pewfowmance_wevews &&
			!data->use_pcie_powew_saving_wevews) {
		data->pcie_gen_powew_saving = data->pcie_gen_pewfowmance;
		data->pcie_wane_powew_saving = data->pcie_wane_pewfowmance;
	} ewse if (!data->use_pcie_pewfowmance_wevews &&
			data->use_pcie_powew_saving_wevews) {
		data->pcie_gen_pewfowmance = data->pcie_gen_powew_saving;
		data->pcie_wane_pewfowmance = data->pcie_wane_powew_saving;
	}
	tmp = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_WINK);
	phm_weset_singwe_dpm_tabwe(&data->dpm_tabwe.pcie_speed_tabwe,
					tmp,
					MAX_WEGUWAW_DPM_NUMBEW);

	if (pcie_tabwe != NUWW) {
		/* max_entwy is used to make suwe we wesewve one PCIE wevew
		 * fow boot wevew (fix fow A+A PSPP issue).
		 * If PCIE tabwe fwom PPTabwe have UWV entwy + 8 entwies,
		 * then ignowe the wast entwy.*/
		max_entwy = (tmp < pcie_tabwe->count) ? tmp : pcie_tabwe->count;
		fow (i = 1; i < max_entwy; i++) {
			phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, i - 1,
					get_pcie_gen_suppowt(data->pcie_gen_cap,
							pcie_tabwe->entwies[i].gen_speed),
					get_pcie_wane_suppowt(data->pcie_wane_cap,
							pcie_tabwe->entwies[i].wane_width));
		}
		data->dpm_tabwe.pcie_speed_tabwe.count = max_entwy - 1;
		smum_update_smc_tabwe(hwmgw, SMU_BIF_TABWE);
	} ewse {
		/* Hawdcode Pcie Tabwe */
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 0,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Min_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 1,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Min_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 2,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 3,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 4,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, 5,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_wane_suppowt(data->pcie_wane_cap,
						PP_Max_PCIEWane));

		data->dpm_tabwe.pcie_speed_tabwe.count = 6;
	}
	/* Popuwate wast wevew fow boot PCIE wevew, but do not incwement count. */
	if (hwmgw->chip_famiwy == AMDGPU_FAMIWY_CI) {
		fow (i = 0; i <= data->dpm_tabwe.pcie_speed_tabwe.count; i++)
			phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe, i,
				get_pcie_gen_suppowt(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				data->vbios_boot_state.pcie_wane_bootup_vawue);
	} ewse {
		phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe,
			data->dpm_tabwe.pcie_speed_tabwe.count,
			get_pcie_gen_suppowt(data->pcie_gen_cap,
					PP_Min_PCIEGen),
			get_pcie_wane_suppowt(data->pcie_wane_cap,
					PP_Max_PCIEWane));

		if (data->pcie_dpm_key_disabwed)
			phm_setup_pcie_tabwe_entwy(&data->dpm_tabwe.pcie_speed_tabwe,
				data->dpm_tabwe.pcie_speed_tabwe.count,
				smu7_ovewwide_pcie_speed(hwmgw), smu7_ovewwide_pcie_width(hwmgw));
	}
	wetuwn 0;
}

static int smu7_weset_dpm_tabwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	memset(&(data->dpm_tabwe), 0x00, sizeof(data->dpm_tabwe));

	phm_weset_singwe_dpm_tabwe(
			&data->dpm_tabwe.scwk_tabwe,
				smum_get_mac_definition(hwmgw,
					SMU_MAX_WEVEWS_GWAPHICS),
					MAX_WEGUWAW_DPM_NUMBEW);
	phm_weset_singwe_dpm_tabwe(
			&data->dpm_tabwe.mcwk_tabwe,
			smum_get_mac_definition(hwmgw,
				SMU_MAX_WEVEWS_MEMOWY), MAX_WEGUWAW_DPM_NUMBEW);

	phm_weset_singwe_dpm_tabwe(
			&data->dpm_tabwe.vddc_tabwe,
				smum_get_mac_definition(hwmgw,
					SMU_MAX_WEVEWS_VDDC),
					MAX_WEGUWAW_DPM_NUMBEW);
	phm_weset_singwe_dpm_tabwe(
			&data->dpm_tabwe.vddci_tabwe,
			smum_get_mac_definition(hwmgw,
				SMU_MAX_WEVEWS_VDDCI), MAX_WEGUWAW_DPM_NUMBEW);

	phm_weset_singwe_dpm_tabwe(
			&data->dpm_tabwe.mvdd_tabwe,
				smum_get_mac_definition(hwmgw,
					SMU_MAX_WEVEWS_MVDD),
					MAX_WEGUWAW_DPM_NUMBEW);
	wetuwn 0;
}
/*
 * This function is to initiawize aww DPM state tabwes
 * fow SMU7 based on the dependency tabwe.
 * Dynamic state patching function wiww then twim these
 * state tabwes to the awwowed wange based
 * on the powew powicy ow extewnaw cwient wequests,
 * such as UVD wequest, etc.
 */

static int smu7_setup_dpm_tabwes_v0(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_vdd_scwk_tabwe =
		hwmgw->dyn_state.vddc_dependency_on_scwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_vdd_mcwk_tabwe =
		hwmgw->dyn_state.vddc_dependency_on_mcwk;
	stwuct phm_cac_weakage_tabwe *std_vowtage_tabwe =
		hwmgw->dyn_state.cac_weakage_tabwe;
	uint32_t i;

	PP_ASSEWT_WITH_CODE(awwowed_vdd_scwk_tabwe != NUWW,
		"SCWK dependency tabwe is missing. This tabwe is mandatowy", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_vdd_scwk_tabwe->count >= 1,
		"SCWK dependency tabwe has to have is missing. This tabwe is mandatowy", wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(awwowed_vdd_mcwk_tabwe != NUWW,
		"MCWK dependency tabwe is missing. This tabwe is mandatowy", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_vdd_mcwk_tabwe->count >= 1,
		"VMCWK dependency tabwe has to have is missing. This tabwe is mandatowy", wetuwn -EINVAW);


	/* Initiawize Scwk DPM tabwe based on awwow Scwk vawues*/
	data->dpm_tabwe.scwk_tabwe.count = 0;

	fow (i = 0; i < awwowed_vdd_scwk_tabwe->count; i++) {
		if (i == 0 || data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count-1].vawue !=
				awwowed_vdd_scwk_tabwe->entwies[i].cwk) {
			data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count].vawue =
				awwowed_vdd_scwk_tabwe->entwies[i].cwk;
			data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count].enabwed = (i == 0) ? 1 : 0;
			data->dpm_tabwe.scwk_tabwe.count++;
		}
	}

	PP_ASSEWT_WITH_CODE(awwowed_vdd_mcwk_tabwe != NUWW,
		"MCWK dependency tabwe is missing. This tabwe is mandatowy", wetuwn -EINVAW);
	/* Initiawize Mcwk DPM tabwe based on awwow Mcwk vawues */
	data->dpm_tabwe.mcwk_tabwe.count = 0;
	fow (i = 0; i < awwowed_vdd_mcwk_tabwe->count; i++) {
		if (i == 0 || data->dpm_tabwe.mcwk_tabwe.dpm_wevews[data->dpm_tabwe.mcwk_tabwe.count-1].vawue !=
			awwowed_vdd_mcwk_tabwe->entwies[i].cwk) {
			data->dpm_tabwe.mcwk_tabwe.dpm_wevews[data->dpm_tabwe.mcwk_tabwe.count].vawue =
				awwowed_vdd_mcwk_tabwe->entwies[i].cwk;
			data->dpm_tabwe.mcwk_tabwe.dpm_wevews[data->dpm_tabwe.mcwk_tabwe.count].enabwed = (i == 0) ? 1 : 0;
			data->dpm_tabwe.mcwk_tabwe.count++;
		}
	}

	/* Initiawize Vddc DPM tabwe based on awwow Vddc vawues.  And popuwate cowwesponding std vawues. */
	fow (i = 0; i < awwowed_vdd_scwk_tabwe->count; i++) {
		data->dpm_tabwe.vddc_tabwe.dpm_wevews[i].vawue = awwowed_vdd_mcwk_tabwe->entwies[i].v;
		data->dpm_tabwe.vddc_tabwe.dpm_wevews[i].pawam1 = std_vowtage_tabwe->entwies[i].Weakage;
		/* pawam1 is fow cowwesponding std vowtage */
		data->dpm_tabwe.vddc_tabwe.dpm_wevews[i].enabwed = twue;
	}

	data->dpm_tabwe.vddc_tabwe.count = awwowed_vdd_scwk_tabwe->count;
	awwowed_vdd_mcwk_tabwe = hwmgw->dyn_state.vddci_dependency_on_mcwk;

	if (NUWW != awwowed_vdd_mcwk_tabwe) {
		/* Initiawize Vddci DPM tabwe based on awwow Mcwk vawues */
		fow (i = 0; i < awwowed_vdd_mcwk_tabwe->count; i++) {
			data->dpm_tabwe.vddci_tabwe.dpm_wevews[i].vawue = awwowed_vdd_mcwk_tabwe->entwies[i].v;
			data->dpm_tabwe.vddci_tabwe.dpm_wevews[i].enabwed = twue;
		}
		data->dpm_tabwe.vddci_tabwe.count = awwowed_vdd_mcwk_tabwe->count;
	}

	awwowed_vdd_mcwk_tabwe = hwmgw->dyn_state.mvdd_dependency_on_mcwk;

	if (NUWW != awwowed_vdd_mcwk_tabwe) {
		/*
		 * Initiawize MVDD DPM tabwe based on awwow Mcwk
		 * vawues
		 */
		fow (i = 0; i < awwowed_vdd_mcwk_tabwe->count; i++) {
			data->dpm_tabwe.mvdd_tabwe.dpm_wevews[i].vawue = awwowed_vdd_mcwk_tabwe->entwies[i].v;
			data->dpm_tabwe.mvdd_tabwe.dpm_wevews[i].enabwed = twue;
		}
		data->dpm_tabwe.mvdd_tabwe.count = awwowed_vdd_mcwk_tabwe->count;
	}

	wetuwn 0;
}

static int smu7_setup_dpm_tabwes_v1(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t i;

	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe;

	if (tabwe_info == NUWW)
		wetuwn -EINVAW;

	dep_scwk_tabwe = tabwe_info->vdd_dep_on_scwk;
	dep_mcwk_tabwe = tabwe_info->vdd_dep_on_mcwk;

	PP_ASSEWT_WITH_CODE(dep_scwk_tabwe != NUWW,
			"SCWK dependency tabwe is missing.",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(dep_scwk_tabwe->count >= 1,
			"SCWK dependency tabwe count is 0.",
			wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(dep_mcwk_tabwe != NUWW,
			"MCWK dependency tabwe is missing.",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(dep_mcwk_tabwe->count >= 1,
			"MCWK dependency tabwe count is 0",
			wetuwn -EINVAW);

	/* Initiawize Scwk DPM tabwe based on awwow Scwk vawues */
	data->dpm_tabwe.scwk_tabwe.count = 0;
	fow (i = 0; i < dep_scwk_tabwe->count; i++) {
		if (i == 0 || data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count - 1].vawue !=
						dep_scwk_tabwe->entwies[i].cwk) {

			data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count].vawue =
					dep_scwk_tabwe->entwies[i].cwk;

			data->dpm_tabwe.scwk_tabwe.dpm_wevews[data->dpm_tabwe.scwk_tabwe.count].enabwed =
					i == 0;
			data->dpm_tabwe.scwk_tabwe.count++;
		}
	}
	if (hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock == 0)
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock = dep_scwk_tabwe->entwies[i-1].cwk;
	/* Initiawize Mcwk DPM tabwe based on awwow Mcwk vawues */
	data->dpm_tabwe.mcwk_tabwe.count = 0;
	fow (i = 0; i < dep_mcwk_tabwe->count; i++) {
		if (i == 0 || data->dpm_tabwe.mcwk_tabwe.dpm_wevews
				[data->dpm_tabwe.mcwk_tabwe.count - 1].vawue !=
						dep_mcwk_tabwe->entwies[i].cwk) {
			data->dpm_tabwe.mcwk_tabwe.dpm_wevews[data->dpm_tabwe.mcwk_tabwe.count].vawue =
							dep_mcwk_tabwe->entwies[i].cwk;
			data->dpm_tabwe.mcwk_tabwe.dpm_wevews[data->dpm_tabwe.mcwk_tabwe.count].enabwed =
							i == 0;
			data->dpm_tabwe.mcwk_tabwe.count++;
		}
	}

	if (hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock == 0)
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock = dep_mcwk_tabwe->entwies[i-1].cwk;
	wetuwn 0;
}

static int smu7_odn_initiaw_defauwt_setting(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_odn_dpm_tabwe *odn_tabwe = &(data->odn_dpm_tabwe);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t i;

	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe;
	stwuct phm_odn_pewfowmance_wevew *entwies;

	if (tabwe_info == NUWW)
		wetuwn -EINVAW;

	dep_scwk_tabwe = tabwe_info->vdd_dep_on_scwk;
	dep_mcwk_tabwe = tabwe_info->vdd_dep_on_mcwk;

	odn_tabwe->odn_cowe_cwock_dpm_wevews.num_of_pw =
						data->gowden_dpm_tabwe.scwk_tabwe.count;
	entwies = odn_tabwe->odn_cowe_cwock_dpm_wevews.entwies;
	fow (i = 0; i < data->gowden_dpm_tabwe.scwk_tabwe.count; i++) {
		entwies[i].cwock = data->gowden_dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue;
		entwies[i].enabwed = twue;
		entwies[i].vddc = dep_scwk_tabwe->entwies[i].vddc;
	}

	smu_get_vowtage_dependency_tabwe_ppt_v1(dep_scwk_tabwe,
		(stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&(odn_tabwe->vdd_dependency_on_scwk));

	odn_tabwe->odn_memowy_cwock_dpm_wevews.num_of_pw =
						data->gowden_dpm_tabwe.mcwk_tabwe.count;
	entwies = odn_tabwe->odn_memowy_cwock_dpm_wevews.entwies;
	fow (i = 0; i < data->gowden_dpm_tabwe.mcwk_tabwe.count; i++) {
		entwies[i].cwock = data->gowden_dpm_tabwe.mcwk_tabwe.dpm_wevews[i].vawue;
		entwies[i].enabwed = twue;
		entwies[i].vddc = dep_mcwk_tabwe->entwies[i].vddc;
	}

	smu_get_vowtage_dependency_tabwe_ppt_v1(dep_mcwk_tabwe,
		(stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&(odn_tabwe->vdd_dependency_on_mcwk));

	wetuwn 0;
}

static void smu7_setup_vowtage_wange_fwom_vbios(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t min_vddc = 0;
	uint32_t max_vddc = 0;

	if (!tabwe_info)
		wetuwn;

	dep_scwk_tabwe = tabwe_info->vdd_dep_on_scwk;

	atomctww_get_vowtage_wange(hwmgw, &max_vddc, &min_vddc);

	if (min_vddc == 0 || min_vddc > 2000
		|| min_vddc > dep_scwk_tabwe->entwies[0].vddc)
		min_vddc = dep_scwk_tabwe->entwies[0].vddc;

	if (max_vddc == 0 || max_vddc > 2000
		|| max_vddc < dep_scwk_tabwe->entwies[dep_scwk_tabwe->count-1].vddc)
		max_vddc = dep_scwk_tabwe->entwies[dep_scwk_tabwe->count-1].vddc;

	data->odn_dpm_tabwe.min_vddc = min_vddc;
	data->odn_dpm_tabwe.max_vddc = max_vddc;
}

static void smu7_check_dpm_tabwe_updated(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_odn_dpm_tabwe *odn_tabwe = &(data->odn_dpm_tabwe);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t i;

	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *odn_dep_tabwe;

	if (tabwe_info == NUWW)
		wetuwn;

	fow (i = 0; i < data->dpm_tabwe.scwk_tabwe.count; i++) {
		if (odn_tabwe->odn_cowe_cwock_dpm_wevews.entwies[i].cwock !=
					data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_SCWK;
			bweak;
		}
	}

	fow (i = 0; i < data->dpm_tabwe.mcwk_tabwe.count; i++) {
		if (odn_tabwe->odn_memowy_cwock_dpm_wevews.entwies[i].cwock !=
					data->dpm_tabwe.mcwk_tabwe.dpm_wevews[i].vawue) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_MCWK;
			bweak;
		}
	}

	dep_tabwe = tabwe_info->vdd_dep_on_mcwk;
	odn_dep_tabwe = (stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&(odn_tabwe->vdd_dependency_on_mcwk);

	fow (i = 0; i < dep_tabwe->count; i++) {
		if (dep_tabwe->entwies[i].vddc != odn_dep_tabwe->entwies[i].vddc) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_VDDC | DPMTABWE_OD_UPDATE_MCWK;
			wetuwn;
		}
	}

	dep_tabwe = tabwe_info->vdd_dep_on_scwk;
	odn_dep_tabwe = (stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&(odn_tabwe->vdd_dependency_on_scwk);
	fow (i = 0; i < dep_tabwe->count; i++) {
		if (dep_tabwe->entwies[i].vddc != odn_dep_tabwe->entwies[i].vddc) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_VDDC | DPMTABWE_OD_UPDATE_SCWK;
			wetuwn;
		}
	}
	if (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_VDDC) {
		data->need_update_smu7_dpm_tabwe &= ~DPMTABWE_OD_UPDATE_VDDC;
		data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_OD_UPDATE_MCWK;
	}
}

static int smu7_setup_defauwt_dpm_tabwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	smu7_weset_dpm_tabwes(hwmgw);

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
		smu7_setup_dpm_tabwes_v1(hwmgw);
	ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
		smu7_setup_dpm_tabwes_v0(hwmgw);

	smu7_setup_defauwt_pcie_tabwe(hwmgw);

	/* save a copy of the defauwt DPM tabwe */
	memcpy(&(data->gowden_dpm_tabwe), &(data->dpm_tabwe),
			sizeof(stwuct smu7_dpm_tabwe));

	/* initiawize ODN tabwe */
	if (hwmgw->od_enabwed) {
		if (data->odn_dpm_tabwe.max_vddc) {
			smu7_check_dpm_tabwe_updated(hwmgw);
		} ewse {
			smu7_setup_vowtage_wange_fwom_vbios(hwmgw);
			smu7_odn_initiaw_defauwt_setting(hwmgw);
		}
	}
	wetuwn 0;
}

static int smu7_enabwe_vwhot_gpio_intewwupt(stwuct pp_hwmgw *hwmgw)
{

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_WeguwatowHot))
		wetuwn smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_EnabweVWHotGPIOIntewwupt,
				NUWW);

	wetuwn 0;
}

static int smu7_enabwe_scwk_contwow(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SCWK_PWWMGT_CNTW,
			SCWK_PWWMGT_OFF, 0);
	wetuwn 0;
}

static int smu7_enabwe_uwv(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->uwv_suppowted)
		wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweUWV, NUWW);

	wetuwn 0;
}

static int smu7_disabwe_uwv(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->uwv_suppowted)
		wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DisabweUWV, NUWW);

	wetuwn 0;
}

static int smu7_enabwe_deep_sweep_mastew_switch(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkDeepSweep)) {
		if (smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MASTEW_DeepSweep_ON, NUWW))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to enabwe Mastew Deep Sweep switch faiwed!",
					wetuwn -EINVAW);
	} ewse {
		if (smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_MASTEW_DeepSweep_OFF,
				NUWW)) {
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to disabwe Mastew Deep Sweep switch faiwed!",
					wetuwn -EINVAW);
		}
	}

	wetuwn 0;
}

static int smu7_disabwe_deep_sweep_mastew_switch(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkDeepSweep)) {
		if (smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_MASTEW_DeepSweep_OFF,
				NUWW)) {
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to disabwe Mastew Deep Sweep switch faiwed!",
					wetuwn -EINVAW);
		}
	}

	wetuwn 0;
}

static int smu7_disabwe_scwk_vce_handshake(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t soft_wegistew_vawue = 0;
	uint32_t handshake_disabwes_offset = data->soft_wegs_stawt
				+ smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, HandshakeDisabwes);

	soft_wegistew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
				CGS_IND_WEG__SMC, handshake_disabwes_offset);
	soft_wegistew_vawue |= SMU7_VCE_SCWK_HANDSHAKE_DISABWE;
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			handshake_disabwes_offset, soft_wegistew_vawue);
	wetuwn 0;
}

static int smu7_disabwe_handshake_uvd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t soft_wegistew_vawue = 0;
	uint32_t handshake_disabwes_offset = data->soft_wegs_stawt
				+ smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, HandshakeDisabwes);

	soft_wegistew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
				CGS_IND_WEG__SMC, handshake_disabwes_offset);
	soft_wegistew_vawue |= smum_get_mac_definition(hwmgw,
					SMU_UVD_MCWK_HANDSHAKE_DISABWE);
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			handshake_disabwes_offset, soft_wegistew_vawue);
	wetuwn 0;
}

static int smu7_enabwe_scwk_mcwk_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	/* enabwe SCWK dpm */
	if (!data->scwk_dpm_key_disabwed) {
		if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
		    hwmgw->chip_id <= CHIP_VEGAM)
			smu7_disabwe_scwk_vce_handshake(hwmgw);

		PP_ASSEWT_WITH_CODE(
		(0 == smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DPM_Enabwe, NUWW)),
		"Faiwed to enabwe SCWK DPM duwing DPM Stawt Function!",
		wetuwn -EINVAW);
	}

	/* enabwe MCWK dpm */
	if (0 == data->mcwk_dpm_key_disabwed) {
		if (!(hwmgw->featuwe_mask & PP_UVD_HANDSHAKE_MASK))
			smu7_disabwe_handshake_uvd(hwmgw);

		PP_ASSEWT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgw,
						PPSMC_MSG_MCWKDPM_Enabwe,
						NUWW)),
				"Faiwed to enabwe MCWK DPM duwing DPM Stawt Function!",
				wetuwn -EINVAW);

		if ((hwmgw->chip_famiwy == AMDGPU_FAMIWY_CI) ||
		    (hwmgw->chip_id == CHIP_POWAWIS10) ||
		    (hwmgw->chip_id == CHIP_POWAWIS11) ||
		    (hwmgw->chip_id == CHIP_POWAWIS12) ||
		    (hwmgw->chip_id == CHIP_TONGA) ||
		    (hwmgw->chip_id == CHIP_TOPAZ))
			PHM_WWITE_FIEWD(hwmgw->device, MC_SEQ_CNTW_3, CAC_EN, 0x1);


		if (hwmgw->chip_famiwy == AMDGPU_FAMIWY_CI) {
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d30, 0x5);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d3c, 0x5);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d80, 0x100005);
			udeway(10);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d30, 0x400005);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d3c, 0x400005);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, 0xc0400d80, 0x500005);
		} ewse {
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC0_CNTW, 0x5);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC1_CNTW, 0x5);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_CPW_CNTW, 0x100005);
			udeway(10);
			if (hwmgw->chip_id == CHIP_VEGAM) {
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC0_CNTW, 0x400009);
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC1_CNTW, 0x400009);
			} ewse {
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC0_CNTW, 0x400005);
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_MC1_CNTW, 0x400005);
			}
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixWCAC_CPW_CNTW, 0x500005);
		}
	}

	wetuwn 0;
}

static int smu7_stawt_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	/*enabwe genewaw powew management */

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, GENEWAW_PWWMGT,
			GWOBAW_PWWMGT_EN, 1);

	/* enabwe scwk deep sweep */

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SCWK_PWWMGT_CNTW,
			DYNAMIC_PM_EN, 1);

	/* pwepawe fow PCIE DPM */

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			data->soft_wegs_stawt +
			smum_get_offsetof(hwmgw, SMU_SoftWegistews,
						VowtageChangeTimeout), 0x1000);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__PCIE,
			SWWST_COMMAND_1, WESETWC, 0x0);

	if (hwmgw->chip_famiwy == AMDGPU_FAMIWY_CI)
		cgs_wwite_wegistew(hwmgw->device, 0x1488,
			(cgs_wead_wegistew(hwmgw->device, 0x1488) & ~0x1));

	if (smu7_enabwe_scwk_mcwk_dpm(hwmgw)) {
		pw_eww("Faiwed to enabwe Scwk DPM and Mcwk DPM!");
		wetuwn -EINVAW;
	}

	/* enabwe PCIE dpm */
	if (0 == data->pcie_dpm_key_disabwed) {
		PP_ASSEWT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgw,
						PPSMC_MSG_PCIeDPM_Enabwe,
						NUWW)),
				"Faiwed to enabwe pcie DPM duwing DPM Stawt Function!",
				wetuwn -EINVAW);
	} ewse {
		PP_ASSEWT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgw,
						PPSMC_MSG_PCIeDPM_Disabwe,
						NUWW)),
				"Faiwed to disabwe pcie DPM duwing DPM Stawt Function!",
				wetuwn -EINVAW);
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_Fawcon_QuickTwansition)) {
		PP_ASSEWT_WITH_CODE((0 == smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_EnabweACDCGPIOIntewwupt,
				NUWW)),
				"Faiwed to enabwe AC DC GPIO Intewwupt!",
				);
	}

	wetuwn 0;
}

static int smu7_disabwe_scwk_mcwk_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	/* disabwe SCWK dpm */
	if (!data->scwk_dpm_key_disabwed) {
		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to disabwe SCWK DPM when DPM is disabwed",
				wetuwn 0);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DPM_Disabwe, NUWW);
	}

	/* disabwe MCWK dpm */
	if (!data->mcwk_dpm_key_disabwed) {
		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to disabwe MCWK DPM when DPM is disabwed",
				wetuwn 0);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_Disabwe, NUWW);
	}

	wetuwn 0;
}

static int smu7_stop_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	/* disabwe genewaw powew management */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, GENEWAW_PWWMGT,
			GWOBAW_PWWMGT_EN, 0);
	/* disabwe scwk deep sweep */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SCWK_PWWMGT_CNTW,
			DYNAMIC_PM_EN, 0);

	/* disabwe PCIE dpm */
	if (!data->pcie_dpm_key_disabwed) {
		PP_ASSEWT_WITH_CODE(
				(smum_send_msg_to_smc(hwmgw,
						PPSMC_MSG_PCIeDPM_Disabwe,
						NUWW) == 0),
				"Faiwed to disabwe pcie DPM duwing DPM Stop Function!",
				wetuwn -EINVAW);
	}

	smu7_disabwe_scwk_mcwk_dpm(hwmgw);

	PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
			"Twying to disabwe vowtage DPM when DPM is disabwed",
			wetuwn 0);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_Vowtage_Cntw_Disabwe, NUWW);

	wetuwn 0;
}

static void smu7_set_dpm_event_souwces(stwuct pp_hwmgw *hwmgw, uint32_t souwces)
{
	boow pwotection;
	enum DPM_EVENT_SWC swc;

	switch (souwces) {
	defauwt:
		pw_eww("Unknown thwottwing event souwces.");
		fawwthwough;
	case 0:
		pwotection = fawse;
		/* swc is unused */
		bweak;
	case (1 << PHM_AutoThwottweSouwce_Thewmaw):
		pwotection = twue;
		swc = DPM_EVENT_SWC_DIGITAW;
		bweak;
	case (1 << PHM_AutoThwottweSouwce_Extewnaw):
		pwotection = twue;
		swc = DPM_EVENT_SWC_EXTEWNAW;
		bweak;
	case (1 << PHM_AutoThwottweSouwce_Extewnaw) |
			(1 << PHM_AutoThwottweSouwce_Thewmaw):
		pwotection = twue;
		swc = DPM_EVENT_SWC_DIGITAW_OW_EXTEWNAW;
		bweak;
	}
	/* Owdew mattews - don't enabwe thewmaw pwotection fow the wwong souwce. */
	if (pwotection) {
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, CG_THEWMAW_CTWW,
				DPM_EVENT_SWC, swc);
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, GENEWAW_PWWMGT,
				THEWMAW_PWOTECTION_DIS,
				!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
						PHM_PwatfowmCaps_ThewmawContwowwew));
	} ewse
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, GENEWAW_PWWMGT,
				THEWMAW_PWOTECTION_DIS, 1);
}

static int smu7_enabwe_auto_thwottwe_souwce(stwuct pp_hwmgw *hwmgw,
		PHM_AutoThwottweSouwce souwce)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (!(data->active_auto_thwottwe_souwces & (1 << souwce))) {
		data->active_auto_thwottwe_souwces |= 1 << souwce;
		smu7_set_dpm_event_souwces(hwmgw, data->active_auto_thwottwe_souwces);
	}
	wetuwn 0;
}

static int smu7_enabwe_thewmaw_auto_thwottwe(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu7_enabwe_auto_thwottwe_souwce(hwmgw, PHM_AutoThwottweSouwce_Thewmaw);
}

static int smu7_disabwe_auto_thwottwe_souwce(stwuct pp_hwmgw *hwmgw,
		PHM_AutoThwottweSouwce souwce)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->active_auto_thwottwe_souwces & (1 << souwce)) {
		data->active_auto_thwottwe_souwces &= ~(1 << souwce);
		smu7_set_dpm_event_souwces(hwmgw, data->active_auto_thwottwe_souwces);
	}
	wetuwn 0;
}

static int smu7_disabwe_thewmaw_auto_thwottwe(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu7_disabwe_auto_thwottwe_souwce(hwmgw, PHM_AutoThwottweSouwce_Thewmaw);
}

static int smu7_pcie_pewfowmance_wequest(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	data->pcie_pewfowmance_wequest = twue;

	wetuwn 0;
}

static int smu7_pwogwam_edc_didt_wegistews(stwuct pp_hwmgw *hwmgw,
					   uint32_t *cac_config_wegs,
					   AtomCtww_EDCWeakgeTabwe *edc_weakage_tabwe)
{
	uint32_t data, i = 0;

	whiwe (cac_config_wegs[i] != 0xFFFFFFFF) {
		data = edc_weakage_tabwe->DIDT_WEG[i];
		cgs_wwite_ind_wegistew(hwmgw->device,
				       CGS_IND_WEG__DIDT,
				       cac_config_wegs[i],
				       data);
		i++;
	}

	wetuwn 0;
}

static int smu7_popuwate_edc_weakage_wegistews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (!data->disabwe_edc_weakage_contwowwew &&
	    data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtWoDpm7TabweOffset &&
	    data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtHiDpm7TabweOffset) {
		wet = smu7_pwogwam_edc_didt_wegistews(hwmgw,
						      DIDTEDCConfig_P12,
						      &data->edc_weakage_tabwe);
		if (wet)
			wetuwn wet;

		wet = smum_send_msg_to_smc(hwmgw,
					   (PPSMC_Msg)PPSMC_MSG_EnabweEDCContwowwew,
					   NUWW);
	} ewse {
		wet = smum_send_msg_to_smc(hwmgw,
					   (PPSMC_Msg)PPSMC_MSG_DisabweEDCContwowwew,
					   NUWW);
	}

	wetuwn wet;
}

static void smu7_popuwate_umdpstate_cwocks(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *gowden_dpm_tabwe = &data->gowden_dpm_tabwe;
	int32_t tmp_scwk, count, pewcentage;

	if (gowden_dpm_tabwe->mcwk_tabwe.count == 1) {
		pewcentage = 70;
		hwmgw->pstate_mcwk = gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[0].vawue;
	} ewse {
		pewcentage = 100 * gowden_dpm_tabwe->scwk_tabwe.dpm_wevews[gowden_dpm_tabwe->scwk_tabwe.count - 1].vawue /
				gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 1].vawue;
		hwmgw->pstate_mcwk = gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 2].vawue;
	}

	tmp_scwk = hwmgw->pstate_mcwk * pewcentage / 100;

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dependency_on_scwk =
			hwmgw->dyn_state.vddc_dependency_on_scwk;

		fow (count = vddc_dependency_on_scwk->count - 1; count >= 0; count--) {
			if (tmp_scwk >= vddc_dependency_on_scwk->entwies[count].cwk) {
				hwmgw->pstate_scwk = vddc_dependency_on_scwk->entwies[count].cwk;
				bweak;
			}
		}
		if (count < 0)
			hwmgw->pstate_scwk = vddc_dependency_on_scwk->entwies[0].cwk;

		hwmgw->pstate_scwk_peak =
			vddc_dependency_on_scwk->entwies[vddc_dependency_on_scwk->count - 1].cwk;
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_scwk =
			tabwe_info->vdd_dep_on_scwk;

		fow (count = vdd_dep_on_scwk->count - 1; count >= 0; count--) {
			if (tmp_scwk >= vdd_dep_on_scwk->entwies[count].cwk) {
				hwmgw->pstate_scwk = vdd_dep_on_scwk->entwies[count].cwk;
				bweak;
			}
		}
		if (count < 0)
			hwmgw->pstate_scwk = vdd_dep_on_scwk->entwies[0].cwk;

		hwmgw->pstate_scwk_peak =
			vdd_dep_on_scwk->entwies[vdd_dep_on_scwk->count - 1].cwk;
	}

	hwmgw->pstate_mcwk_peak =
		gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 1].vawue;

	/* make suwe the output is in Mhz */
	hwmgw->pstate_scwk /= 100;
	hwmgw->pstate_mcwk /= 100;
	hwmgw->pstate_scwk_peak /= 100;
	hwmgw->pstate_mcwk_peak /= 100;
}

static int smu7_enabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int tmp_wesuwt = 0;
	int wesuwt = 0;

	if (smu7_vowtage_contwow(hwmgw)) {
		tmp_wesuwt = smu7_enabwe_vowtage_contwow(hwmgw);
		PP_ASSEWT_WITH_CODE(tmp_wesuwt == 0,
				"Faiwed to enabwe vowtage contwow!",
				wesuwt = tmp_wesuwt);

		tmp_wesuwt = smu7_constwuct_vowtage_tabwes(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to constwuct vowtage tabwes!",
				wesuwt = tmp_wesuwt);
	}
	smum_initiawize_mc_weg_tabwe(hwmgw);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EngineSpweadSpectwumSuppowt))
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				GENEWAW_PWWMGT, DYN_SPWEAD_SPECTWUM_EN, 1);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawContwowwew))
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				GENEWAW_PWWMGT, THEWMAW_PWOTECTION_DIS, 0);

	tmp_wesuwt = smu7_pwogwam_static_scween_thweshowd_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to pwogwam static scween thweshowd pawametews!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_dispway_gap(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe dispway gap!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_pwogwam_voting_cwients(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to pwogwam voting cwients!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smum_pwocess_fiwmwawe_headew(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to pwocess fiwmwawe headew!", wesuwt = tmp_wesuwt);

	if (hwmgw->chip_id != CHIP_VEGAM) {
		tmp_wesuwt = smu7_initiaw_switch_fwom_awbf0_to_f1(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to initiawize switch fwom AwbF0 to F1!",
				wesuwt = tmp_wesuwt);
	}

	wesuwt = smu7_setup_defauwt_dpm_tabwes(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to setup defauwt DPM tabwes!", wetuwn wesuwt);

	tmp_wesuwt = smum_init_smc_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to initiawize SMC tabwe!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_vwhot_gpio_intewwupt(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe VW hot GPIO intewwupt!", wesuwt = tmp_wesuwt);

	if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
	    hwmgw->chip_id <= CHIP_VEGAM) {
		tmp_wesuwt = smu7_notify_has_dispway(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to enabwe dispway setting!", wesuwt = tmp_wesuwt);
	} ewse {
		smum_send_msg_to_smc(hwmgw, (PPSMC_Msg)PPSMC_NoDispway, NUWW);
	}

	if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
	    hwmgw->chip_id <= CHIP_VEGAM) {
		tmp_wesuwt = smu7_popuwate_edc_weakage_wegistews(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to popuwate edc weakage wegistews!", wesuwt = tmp_wesuwt);
	}

	tmp_wesuwt = smu7_enabwe_scwk_contwow(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe SCWK contwow!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_smc_vowtage_contwowwew(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe vowtage contwow!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_uwv(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe UWV!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_deep_sweep_mastew_switch(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe deep sweep mastew switch!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_didt_config(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to enabwe deep sweep mastew switch!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_stawt_dpm(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to stawt DPM!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_smc_cac(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe SMC CAC!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_powew_containment(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe powew containment!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_powew_contwow_set_wevew(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to powew contwow set wevew!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_thewmaw_auto_thwottwe(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe thewmaw auto thwottwe!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_pcie_pewfowmance_wequest(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"pcie pewfowmance wequest faiwed!", wesuwt = tmp_wesuwt);

	smu7_popuwate_umdpstate_cwocks(hwmgw);

	wetuwn 0;
}

static int smu7_avfs_contwow(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	if (enabwe) {
		if (!PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
				CGS_IND_WEG__SMC, FEATUWE_STATUS, AVS_ON)) {
			PP_ASSEWT_WITH_CODE(!smum_send_msg_to_smc(
					hwmgw, PPSMC_MSG_EnabweAvfs, NUWW),
					"Faiwed to enabwe AVFS!",
					wetuwn -EINVAW);
		}
	} ewse if (PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, FEATUWE_STATUS, AVS_ON)) {
		PP_ASSEWT_WITH_CODE(!smum_send_msg_to_smc(
				hwmgw, PPSMC_MSG_DisabweAvfs, NUWW),
				"Faiwed to disabwe AVFS!",
				wetuwn -EINVAW);
	}

	wetuwn 0;
}

static int smu7_update_avfs(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	if (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_VDDC) {
		smu7_avfs_contwow(hwmgw, fawse);
	} ewse if (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_SCWK) {
		smu7_avfs_contwow(hwmgw, fawse);
		smu7_avfs_contwow(hwmgw, twue);
	} ewse {
		smu7_avfs_contwow(hwmgw, twue);
	}

	wetuwn 0;
}

static int smu7_disabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int tmp_wesuwt, wesuwt = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawContwowwew))
		PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				GENEWAW_PWWMGT, THEWMAW_PWOTECTION_DIS, 1);

	tmp_wesuwt = smu7_disabwe_powew_containment(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe powew containment!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_disabwe_smc_cac(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe SMC CAC!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_disabwe_didt_config(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe DIDT!", wesuwt = tmp_wesuwt);

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_SPWW_SPWEAD_SPECTWUM, SSEN, 0);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			GENEWAW_PWWMGT, DYN_SPWEAD_SPECTWUM_EN, 0);

	tmp_wesuwt = smu7_disabwe_thewmaw_auto_thwottwe(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe thewmaw auto thwottwe!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_avfs_contwow(hwmgw, fawse);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe AVFS!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_stop_dpm(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to stop DPM!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_disabwe_deep_sweep_mastew_switch(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe deep sweep mastew switch!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_disabwe_uwv(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe UWV!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_cweaw_voting_cwients(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to cweaw voting cwients!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_weset_to_defauwt(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to weset to defauwt!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smum_stop_smc(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to stop smc!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_fowce_switch_to_awbf0(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to fowce to switch awbf0!", wesuwt = tmp_wesuwt);

	wetuwn wesuwt;
}

static void smu7_init_dpm_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint8_t tmp1, tmp2;
	uint16_t tmp3 = 0;

	data->dww_defauwt_on = fawse;
	data->mcwk_dpm0_activity_tawget = 0xa;
	data->vddc_vddgfx_dewta = 300;
	data->static_scween_thweshowd = SMU7_STATICSCWEENTHWESHOWD_DFWT;
	data->static_scween_thweshowd_unit = SMU7_STATICSCWEENTHWESHOWDUNIT_DFWT;
	data->voting_wights_cwients[0] = SMU7_VOTINGWIGHTSCWIENTS_DFWT0;
	data->voting_wights_cwients[1] = SMU7_VOTINGWIGHTSCWIENTS_DFWT1;
	data->voting_wights_cwients[2] = SMU7_VOTINGWIGHTSCWIENTS_DFWT2;
	data->voting_wights_cwients[3] = SMU7_VOTINGWIGHTSCWIENTS_DFWT3;
	data->voting_wights_cwients[4] = SMU7_VOTINGWIGHTSCWIENTS_DFWT4;
	data->voting_wights_cwients[5] = SMU7_VOTINGWIGHTSCWIENTS_DFWT5;
	data->voting_wights_cwients[6] = SMU7_VOTINGWIGHTSCWIENTS_DFWT6;
	data->voting_wights_cwients[7] = SMU7_VOTINGWIGHTSCWIENTS_DFWT7;

	data->mcwk_dpm_key_disabwed = hwmgw->featuwe_mask & PP_MCWK_DPM_MASK ? fawse : twue;
	data->scwk_dpm_key_disabwed = hwmgw->featuwe_mask & PP_SCWK_DPM_MASK ? fawse : twue;
	data->pcie_dpm_key_disabwed = !(hwmgw->featuwe_mask & PP_PCIE_DPM_MASK);
	/* need to set vowtage contwow types befowe EVV patching */
	data->vowtage_contwow = SMU7_VOWTAGE_CONTWOW_NONE;
	data->vddci_contwow = SMU7_VOWTAGE_CONTWOW_NONE;
	data->mvdd_contwow = SMU7_VOWTAGE_CONTWOW_NONE;
	data->enabwe_tdc_wimit_featuwe = twue;
	data->enabwe_pkg_pww_twacking_featuwe = twue;
	data->fowce_pcie_gen = PP_PCIEGenInvawid;
	data->uwv_suppowted = hwmgw->featuwe_mask & PP_UWV_MASK ? twue : fawse;
	data->cuwwent_pwofiwe_setting.bupdate_scwk = 1;
	data->cuwwent_pwofiwe_setting.scwk_up_hyst = 0;
	data->cuwwent_pwofiwe_setting.scwk_down_hyst = 100;
	data->cuwwent_pwofiwe_setting.scwk_activity = SMU7_SCWK_TAWGETACTIVITY_DFWT;
	data->cuwwent_pwofiwe_setting.bupdate_mcwk = 1;
	if (hwmgw->chip_id >= CHIP_POWAWIS10) {
		if (adev->gmc.vwam_width == 256) {
			data->cuwwent_pwofiwe_setting.mcwk_up_hyst = 10;
			data->cuwwent_pwofiwe_setting.mcwk_down_hyst = 60;
			data->cuwwent_pwofiwe_setting.mcwk_activity = 25;
		} ewse if (adev->gmc.vwam_width == 128) {
			data->cuwwent_pwofiwe_setting.mcwk_up_hyst = 5;
			data->cuwwent_pwofiwe_setting.mcwk_down_hyst = 16;
			data->cuwwent_pwofiwe_setting.mcwk_activity = 20;
		} ewse if (adev->gmc.vwam_width == 64) {
			data->cuwwent_pwofiwe_setting.mcwk_up_hyst = 3;
			data->cuwwent_pwofiwe_setting.mcwk_down_hyst = 16;
			data->cuwwent_pwofiwe_setting.mcwk_activity = 20;
		}
	} ewse {
		data->cuwwent_pwofiwe_setting.mcwk_up_hyst = 0;
		data->cuwwent_pwofiwe_setting.mcwk_down_hyst = 100;
		data->cuwwent_pwofiwe_setting.mcwk_activity = SMU7_MCWK_TAWGETACTIVITY_DFWT;
	}
	hwmgw->wowkwoad_mask = 1 << hwmgw->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D];
	hwmgw->powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D;
	hwmgw->defauwt_powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D;

	if (hwmgw->chip_id  == CHIP_HAWAII) {
		data->thewmaw_temp_setting.tempewatuwe_wow = 94500;
		data->thewmaw_temp_setting.tempewatuwe_high = 95000;
		data->thewmaw_temp_setting.tempewatuwe_shutdown = 104000;
	} ewse {
		data->thewmaw_temp_setting.tempewatuwe_wow = 99500;
		data->thewmaw_temp_setting.tempewatuwe_high = 100000;
		data->thewmaw_temp_setting.tempewatuwe_shutdown = 104000;
	}

	data->fast_watewmawk_thweshowd = 100;
	if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
			VOWTAGE_TYPE_VDDC, VOWTAGE_OBJ_SVID2))
		data->vowtage_contwow = SMU7_VOWTAGE_CONTWOW_BY_SVID2;
	ewse if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
			VOWTAGE_TYPE_VDDC, VOWTAGE_OBJ_GPIO_WUT))
		data->vowtage_contwow = SMU7_VOWTAGE_CONTWOW_BY_GPIO;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ContwowVDDGFX)) {
		if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
			VOWTAGE_TYPE_VDDGFX, VOWTAGE_OBJ_SVID2)) {
			data->vdd_gfx_contwow = SMU7_VOWTAGE_CONTWOW_BY_SVID2;
		}
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EnabweMVDDContwow)) {
		if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
				VOWTAGE_TYPE_MVDDC, VOWTAGE_OBJ_GPIO_WUT))
			data->mvdd_contwow = SMU7_VOWTAGE_CONTWOW_BY_GPIO;
		ewse if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
				VOWTAGE_TYPE_MVDDC, VOWTAGE_OBJ_SVID2))
			data->mvdd_contwow = SMU7_VOWTAGE_CONTWOW_BY_SVID2;
	}

	if (SMU7_VOWTAGE_CONTWOW_NONE == data->vdd_gfx_contwow)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ContwowVDDGFX);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ContwowVDDCI)) {
		if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
				VOWTAGE_TYPE_VDDCI, VOWTAGE_OBJ_GPIO_WUT))
			data->vddci_contwow = SMU7_VOWTAGE_CONTWOW_BY_GPIO;
		ewse if (atomctww_is_vowtage_contwowwed_by_gpio_v3(hwmgw,
				VOWTAGE_TYPE_VDDCI, VOWTAGE_OBJ_SVID2))
			data->vddci_contwow = SMU7_VOWTAGE_CONTWOW_BY_SVID2;
	}

	if (data->mvdd_contwow == SMU7_VOWTAGE_CONTWOW_NONE)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_EnabweMVDDContwow);

	if (data->vddci_contwow == SMU7_VOWTAGE_CONTWOW_NONE)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ContwowVDDCI);

	data->vddc_phase_shed_contwow = 1;
	if ((hwmgw->chip_id == CHIP_POWAWIS12) ||
	    ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P31(adev->pdev->device, adev->pdev->wevision)) {
		if (data->vowtage_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
			atomctww_get_svi2_info(hwmgw, VOWTAGE_TYPE_VDDC, &tmp1, &tmp2,
							&tmp3);
			tmp3 = (tmp3 >> 5) & 0x3;
			data->vddc_phase_shed_contwow = ((tmp3 << 1) | (tmp3 >> 1)) & 0x3;
		}
	} ewse if (hwmgw->chip_famiwy == AMDGPU_FAMIWY_CI) {
		data->vddc_phase_shed_contwow = 1;
	}

	if ((hwmgw->pp_tabwe_vewsion != PP_TABWE_V0) && (hwmgw->featuwe_mask & PP_CWOCK_STWETCH_MASK)
		&& (tabwe_info->cac_dtp_tabwe->usCwockStwetchAmount != 0))
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_CwockStwetchew);

	data->pcie_gen_pewfowmance.max = PP_PCIEGen1;
	data->pcie_gen_pewfowmance.min = PP_PCIEGen3;
	data->pcie_gen_powew_saving.max = PP_PCIEGen1;
	data->pcie_gen_powew_saving.min = PP_PCIEGen3;
	data->pcie_wane_pewfowmance.max = 0;
	data->pcie_wane_pewfowmance.min = 16;
	data->pcie_wane_powew_saving.max = 0;
	data->pcie_wane_powew_saving.min = 16;


	if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			      PHM_PwatfowmCaps_UVDPowewGating);
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCE)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			      PHM_PwatfowmCaps_VCEPowewGating);

	data->disabwe_edc_weakage_contwowwew = twue;
	if (((adev->asic_type == CHIP_POWAWIS10) && hwmgw->is_kickew) ||
	    ((adev->asic_type == CHIP_POWAWIS11) && hwmgw->is_kickew) ||
	    (adev->asic_type == CHIP_POWAWIS12) ||
	    (adev->asic_type == CHIP_VEGAM))
		data->disabwe_edc_weakage_contwowwew = fawse;

	if (!atomctww_is_asic_intewnaw_ss_suppowted(hwmgw)) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MemowySpweadSpectwumSuppowt);
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EngineSpweadSpectwumSuppowt);
	}

	if ((adev->pdev->device == 0x699F) &&
	    (adev->pdev->wevision == 0xCF)) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_PowewContainment);
		data->enabwe_tdc_wimit_featuwe = fawse;
		data->enabwe_pkg_pww_twacking_featuwe = fawse;
		data->disabwe_edc_weakage_contwowwew = twue;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_CwockStwetchew);
	}
}

static int smu7_cawcuwate_wo_wange(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t asicwev1, evv_wevision, max = 0, min = 0;

	atomctww_wead_efuse(hwmgw, STWAP_EVV_WEVISION_WSB, STWAP_EVV_WEVISION_MSB,
			&evv_wevision);

	atomctww_wead_efuse(hwmgw, 568, 579, &asicwev1);

	if (ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision)) {
		min = 1200;
		max = 2500;
	} ewse if (ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision) ||
		   ASICID_IS_P31(adev->pdev->device, adev->pdev->wevision)) {
		min = 900;
		max = 2100;
	} ewse if (hwmgw->chip_id == CHIP_POWAWIS10) {
		if (adev->pdev->subsystem_vendow == 0x106B) {
			min = 1000;
			max = 2300;
		} ewse {
			if (evv_wevision == 0) {
				min = 1000;
				max = 2300;
			} ewse if (evv_wevision == 1) {
				if (asicwev1 == 326) {
					min = 1200;
					max = 2500;
					/* TODO: PATCH WO in VBIOS */
				} ewse {
					min = 1200;
					max = 2000;
				}
			} ewse if (evv_wevision == 2) {
				min = 1200;
				max = 2500;
			}
		}
	} ewse {
		min = 1100;
		max = 2100;
	}

	data->wo_wange_minimum = min;
	data->wo_wange_maximum = max;

	/* TODO: PATCH WO in VBIOS hewe */

	wetuwn 0;
}

/**
 * smu7_get_evv_vowtages - Get Weakage VDDC based on weakage ID.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_get_evv_vowtages(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint16_t vv_id;
	uint16_t vddc = 0;
	uint16_t vddgfx = 0;
	uint16_t i, j;
	uint32_t scwk = 0;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe = NUWW;

	if (hwmgw->chip_id == CHIP_POWAWIS10 ||
	    hwmgw->chip_id == CHIP_POWAWIS11 ||
	    hwmgw->chip_id == CHIP_POWAWIS12)
		smu7_cawcuwate_wo_wange(hwmgw);

	fow (i = 0; i < SMU7_MAX_WEAKAGE_COUNT; i++) {
		vv_id = ATOM_VIWTUAW_VOWTAGE_ID0 + i;

		if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
			if ((hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
			    && !phm_get_scwk_fow_vowtage_evv(hwmgw,
						tabwe_info->vddgfx_wookup_tabwe, vv_id, &scwk)) {
				if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
							PHM_PwatfowmCaps_CwockStwetchew)) {
					scwk_tabwe = tabwe_info->vdd_dep_on_scwk;

					fow (j = 1; j < scwk_tabwe->count; j++) {
						if (scwk_tabwe->entwies[j].cwk == scwk &&
								scwk_tabwe->entwies[j].cks_enabwe == 0) {
							scwk += 5000;
							bweak;
						}
					}
				}
				if (0 == atomctww_get_vowtage_evv_on_scwk
				    (hwmgw, VOWTAGE_TYPE_VDDGFX, scwk,
				     vv_id, &vddgfx)) {
					/* need to make suwe vddgfx is wess than 2v ow ewse, it couwd buwn the ASIC. */
					PP_ASSEWT_WITH_CODE((vddgfx < 2000 && vddgfx != 0), "Invawid VDDGFX vawue!", wetuwn -EINVAW);

					/* the vowtage shouwd not be zewo now equaw to weakage ID */
					if (vddgfx != 0 && vddgfx != vv_id) {
						data->vddcgfx_weakage.actuaw_vowtage[data->vddcgfx_weakage.count] = vddgfx;
						data->vddcgfx_weakage.weakage_id[data->vddcgfx_weakage.count] = vv_id;
						data->vddcgfx_weakage.count++;
					}
				} ewse {
					pw_info("Ewwow wetwieving EVV vowtage vawue!\n");
				}
			}
		} ewse {
			if ((hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
				|| !phm_get_scwk_fow_vowtage_evv(hwmgw,
					tabwe_info->vddc_wookup_tabwe, vv_id, &scwk)) {
				if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
						PHM_PwatfowmCaps_CwockStwetchew)) {
					if (tabwe_info == NUWW)
						wetuwn -EINVAW;
					scwk_tabwe = tabwe_info->vdd_dep_on_scwk;

					fow (j = 1; j < scwk_tabwe->count; j++) {
						if (scwk_tabwe->entwies[j].cwk == scwk &&
								scwk_tabwe->entwies[j].cks_enabwe == 0) {
							scwk += 5000;
							bweak;
						}
					}
				}

				if (phm_get_vowtage_evv_on_scwk(hwmgw,
							VOWTAGE_TYPE_VDDC,
							scwk, vv_id, &vddc) == 0) {
					if (vddc >= 2000 || vddc == 0)
						wetuwn -EINVAW;
				} ewse {
					pw_debug("faiwed to wetwieving EVV vowtage!\n");
					continue;
				}

				/* the vowtage shouwd not be zewo now equaw to weakage ID */
				if (vddc != 0 && vddc != vv_id) {
					data->vddc_weakage.actuaw_vowtage[data->vddc_weakage.count] = (uint16_t)(vddc);
					data->vddc_weakage.weakage_id[data->vddc_weakage.count] = vv_id;
					data->vddc_weakage.count++;
				}
			}
		}
	}

	wetuwn 0;
}

/**
 * smu7_patch_ppt_v1_with_vdd_weakage - Change viwtuaw weakage vowtage to actuaw vawue.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @vowtage: pointew to changing vowtage
 * @weakage_tabwe: pointew to weakage tabwe
 */
static void smu7_patch_ppt_v1_with_vdd_weakage(stwuct pp_hwmgw *hwmgw,
		uint16_t *vowtage, stwuct smu7_weakage_vowtage *weakage_tabwe)
{
	uint32_t index;

	/* seawch fow weakage vowtage ID 0xff01 ~ 0xff08 */
	fow (index = 0; index < weakage_tabwe->count; index++) {
		/* if this vowtage matches a weakage vowtage ID */
		/* patch with actuaw weakage vowtage */
		if (weakage_tabwe->weakage_id[index] == *vowtage) {
			*vowtage = weakage_tabwe->actuaw_vowtage[index];
			bweak;
		}
	}

	if (*vowtage > ATOM_VIWTUAW_VOWTAGE_ID0)
		pw_info("Vowtage vawue wooks wike a Weakage ID but it's not patched\n");
}

/**
 * smu7_patch_wookup_tabwe_with_weakage - Patch vowtage wookup tabwe by EVV weakages.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @wookup_tabwe: pointew to vowtage wookup tabwe
 * @weakage_tabwe: pointew to weakage tabwe
 * Wetuwn:     awways 0
 */
static int smu7_patch_wookup_tabwe_with_weakage(stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe,
		stwuct smu7_weakage_vowtage *weakage_tabwe)
{
	uint32_t i;

	fow (i = 0; i < wookup_tabwe->count; i++)
		smu7_patch_ppt_v1_with_vdd_weakage(hwmgw,
				&wookup_tabwe->entwies[i].us_vdd, weakage_tabwe);

	wetuwn 0;
}

static int smu7_patch_cwock_vowtage_wimits_with_vddc_weakage(
		stwuct pp_hwmgw *hwmgw, stwuct smu7_weakage_vowtage *weakage_tabwe,
		uint16_t *vddc)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	smu7_patch_ppt_v1_with_vdd_weakage(hwmgw, (uint16_t *)vddc, weakage_tabwe);
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddc =
			tabwe_info->max_cwock_vowtage_on_dc.vddc;
	wetuwn 0;
}

static int smu7_patch_vowtage_dependency_tabwes_with_wookup_tabwe(
		stwuct pp_hwmgw *hwmgw)
{
	uint8_t entwy_id;
	uint8_t vowtage_id;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *mcwk_tabwe =
			tabwe_info->vdd_dep_on_mcwk;
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;

	if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		fow (entwy_id = 0; entwy_id < scwk_tabwe->count; ++entwy_id) {
			vowtage_id = scwk_tabwe->entwies[entwy_id].vddInd;
			scwk_tabwe->entwies[entwy_id].vddgfx =
				tabwe_info->vddgfx_wookup_tabwe->entwies[vowtage_id].us_vdd;
		}
	} ewse {
		fow (entwy_id = 0; entwy_id < scwk_tabwe->count; ++entwy_id) {
			vowtage_id = scwk_tabwe->entwies[entwy_id].vddInd;
			scwk_tabwe->entwies[entwy_id].vddc =
				tabwe_info->vddc_wookup_tabwe->entwies[vowtage_id].us_vdd;
		}
	}

	fow (entwy_id = 0; entwy_id < mcwk_tabwe->count; ++entwy_id) {
		vowtage_id = mcwk_tabwe->entwies[entwy_id].vddInd;
		mcwk_tabwe->entwies[entwy_id].vddc =
			tabwe_info->vddc_wookup_tabwe->entwies[vowtage_id].us_vdd;
	}

	fow (entwy_id = 0; entwy_id < mm_tabwe->count; ++entwy_id) {
		vowtage_id = mm_tabwe->entwies[entwy_id].vddcInd;
		mm_tabwe->entwies[entwy_id].vddc =
			tabwe_info->vddc_wookup_tabwe->entwies[vowtage_id].us_vdd;
	}

	wetuwn 0;

}

static int phm_add_vowtage(stwuct pp_hwmgw *hwmgw,
			phm_ppt_v1_vowtage_wookup_tabwe *wook_up_tabwe,
			phm_ppt_v1_vowtage_wookup_wecowd *wecowd)
{
	uint32_t i;

	PP_ASSEWT_WITH_CODE((NUWW != wook_up_tabwe),
		"Wookup Tabwe empty.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((0 != wook_up_tabwe->count),
		"Wookup Tabwe empty.", wetuwn -EINVAW);

	i = smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_VDDGFX);
	PP_ASSEWT_WITH_CODE((i >= wook_up_tabwe->count),
		"Wookup Tabwe is fuww.", wetuwn -EINVAW);

	/* This is to avoid entewing dupwicate cawcuwated wecowds. */
	fow (i = 0; i < wook_up_tabwe->count; i++) {
		if (wook_up_tabwe->entwies[i].us_vdd == wecowd->us_vdd) {
			if (wook_up_tabwe->entwies[i].us_cawcuwated == 1)
				wetuwn 0;
			bweak;
		}
	}

	wook_up_tabwe->entwies[i].us_cawcuwated = 1;
	wook_up_tabwe->entwies[i].us_vdd = wecowd->us_vdd;
	wook_up_tabwe->entwies[i].us_cac_wow = wecowd->us_cac_wow;
	wook_up_tabwe->entwies[i].us_cac_mid = wecowd->us_cac_mid;
	wook_up_tabwe->entwies[i].us_cac_high = wecowd->us_cac_high;
	/* Onwy incwement the count when we'we appending, not wepwacing dupwicate entwy. */
	if (i == wook_up_tabwe->count)
		wook_up_tabwe->count++;

	wetuwn 0;
}


static int smu7_cawc_vowtage_dependency_tabwes(stwuct pp_hwmgw *hwmgw)
{
	uint8_t entwy_id;
	stwuct phm_ppt_v1_vowtage_wookup_wecowd v_wecowd;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info = (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe = pptabwe_info->vdd_dep_on_scwk;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *mcwk_tabwe = pptabwe_info->vdd_dep_on_mcwk;

	if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		fow (entwy_id = 0; entwy_id < scwk_tabwe->count; ++entwy_id) {
			if (scwk_tabwe->entwies[entwy_id].vdd_offset & (1 << 15))
				v_wecowd.us_vdd = scwk_tabwe->entwies[entwy_id].vddgfx +
					scwk_tabwe->entwies[entwy_id].vdd_offset - 0xFFFF;
			ewse
				v_wecowd.us_vdd = scwk_tabwe->entwies[entwy_id].vddgfx +
					scwk_tabwe->entwies[entwy_id].vdd_offset;

			scwk_tabwe->entwies[entwy_id].vddc =
				v_wecowd.us_cac_wow = v_wecowd.us_cac_mid =
				v_wecowd.us_cac_high = v_wecowd.us_vdd;

			phm_add_vowtage(hwmgw, pptabwe_info->vddc_wookup_tabwe, &v_wecowd);
		}

		fow (entwy_id = 0; entwy_id < mcwk_tabwe->count; ++entwy_id) {
			if (mcwk_tabwe->entwies[entwy_id].vdd_offset & (1 << 15))
				v_wecowd.us_vdd = mcwk_tabwe->entwies[entwy_id].vddc +
					mcwk_tabwe->entwies[entwy_id].vdd_offset - 0xFFFF;
			ewse
				v_wecowd.us_vdd = mcwk_tabwe->entwies[entwy_id].vddc +
					mcwk_tabwe->entwies[entwy_id].vdd_offset;

			mcwk_tabwe->entwies[entwy_id].vddgfx = v_wecowd.us_cac_wow =
				v_wecowd.us_cac_mid = v_wecowd.us_cac_high = v_wecowd.us_vdd;
			phm_add_vowtage(hwmgw, pptabwe_info->vddgfx_wookup_tabwe, &v_wecowd);
		}
	}
	wetuwn 0;
}

static int smu7_cawc_mm_vowtage_dependency_tabwe(stwuct pp_hwmgw *hwmgw)
{
	uint8_t entwy_id;
	stwuct phm_ppt_v1_vowtage_wookup_wecowd v_wecowd;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *pptabwe_info = (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe = pptabwe_info->mm_dep_tabwe;

	if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		fow (entwy_id = 0; entwy_id < mm_tabwe->count; entwy_id++) {
			if (mm_tabwe->entwies[entwy_id].vddgfx_offset & (1 << 15))
				v_wecowd.us_vdd = mm_tabwe->entwies[entwy_id].vddc +
					mm_tabwe->entwies[entwy_id].vddgfx_offset - 0xFFFF;
			ewse
				v_wecowd.us_vdd = mm_tabwe->entwies[entwy_id].vddc +
					mm_tabwe->entwies[entwy_id].vddgfx_offset;

			/* Add the cawcuwated VDDGFX to the VDDGFX wookup tabwe */
			mm_tabwe->entwies[entwy_id].vddgfx = v_wecowd.us_cac_wow =
				v_wecowd.us_cac_mid = v_wecowd.us_cac_high = v_wecowd.us_vdd;
			phm_add_vowtage(hwmgw, pptabwe_info->vddgfx_wookup_tabwe, &v_wecowd);
		}
	}
	wetuwn 0;
}

static int smu7_sowt_wookup_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe)
{
	uint32_t tabwe_size, i, j;
	tabwe_size = wookup_tabwe->count;

	PP_ASSEWT_WITH_CODE(0 != wookup_tabwe->count,
		"Wookup tabwe is empty", wetuwn -EINVAW);

	/* Sowting vowtages */
	fow (i = 0; i < tabwe_size - 1; i++) {
		fow (j = i + 1; j > 0; j--) {
			if (wookup_tabwe->entwies[j].us_vdd <
					wookup_tabwe->entwies[j - 1].us_vdd) {
				swap(wookup_tabwe->entwies[j - 1],
				     wookup_tabwe->entwies[j]);
			}
		}
	}

	wetuwn 0;
}

static int smu7_compwete_dependency_tabwes(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	int tmp_wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (data->vdd_gfx_contwow == SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		tmp_wesuwt = smu7_patch_wookup_tabwe_with_weakage(hwmgw,
			tabwe_info->vddgfx_wookup_tabwe, &(data->vddcgfx_weakage));
		if (tmp_wesuwt != 0)
			wesuwt = tmp_wesuwt;

		smu7_patch_ppt_v1_with_vdd_weakage(hwmgw,
			&tabwe_info->max_cwock_vowtage_on_dc.vddgfx, &(data->vddcgfx_weakage));
	} ewse {

		tmp_wesuwt = smu7_patch_wookup_tabwe_with_weakage(hwmgw,
				tabwe_info->vddc_wookup_tabwe, &(data->vddc_weakage));
		if (tmp_wesuwt)
			wesuwt = tmp_wesuwt;

		tmp_wesuwt = smu7_patch_cwock_vowtage_wimits_with_vddc_weakage(hwmgw,
				&(data->vddc_weakage), &tabwe_info->max_cwock_vowtage_on_dc.vddc);
		if (tmp_wesuwt)
			wesuwt = tmp_wesuwt;
	}

	tmp_wesuwt = smu7_patch_vowtage_dependency_tabwes_with_wookup_tabwe(hwmgw);
	if (tmp_wesuwt)
		wesuwt = tmp_wesuwt;

	tmp_wesuwt = smu7_cawc_vowtage_dependency_tabwes(hwmgw);
	if (tmp_wesuwt)
		wesuwt = tmp_wesuwt;

	tmp_wesuwt = smu7_cawc_mm_vowtage_dependency_tabwe(hwmgw);
	if (tmp_wesuwt)
		wesuwt = tmp_wesuwt;

	tmp_wesuwt = smu7_sowt_wookup_tabwe(hwmgw, tabwe_info->vddgfx_wookup_tabwe);
	if (tmp_wesuwt)
		wesuwt = tmp_wesuwt;

	tmp_wesuwt = smu7_sowt_wookup_tabwe(hwmgw, tabwe_info->vddc_wookup_tabwe);
	if (tmp_wesuwt)
		wesuwt = tmp_wesuwt;

	wetuwn wesuwt;
}

static int smu7_find_highest_vddc(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_scwk_vdd_tabwe =
						tabwe_info->vdd_dep_on_scwk;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe =
						tabwe_info->vddc_wookup_tabwe;
	uint16_t highest_vowtage;
	uint32_t i;

	highest_vowtage = awwowed_scwk_vdd_tabwe->entwies[awwowed_scwk_vdd_tabwe->count - 1].vddc;

	fow (i = 0; i < wookup_tabwe->count; i++) {
		if (wookup_tabwe->entwies[i].us_vdd < ATOM_VIWTUAW_VOWTAGE_ID0 &&
		    wookup_tabwe->entwies[i].us_vdd > highest_vowtage)
			highest_vowtage = wookup_tabwe->entwies[i].us_vdd;
	}

	wetuwn highest_vowtage;
}

static int smu7_set_pwivate_data_based_on_pptabwe_v1(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_scwk_vdd_tabwe =
						tabwe_info->vdd_dep_on_scwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_mcwk_vdd_tabwe =
						tabwe_info->vdd_dep_on_mcwk;

	PP_ASSEWT_WITH_CODE(awwowed_scwk_vdd_tabwe != NUWW,
		"VDD dependency on SCWK tabwe is missing.",
		wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_scwk_vdd_tabwe->count >= 1,
		"VDD dependency on SCWK tabwe has to have is missing.",
		wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(awwowed_mcwk_vdd_tabwe != NUWW,
		"VDD dependency on MCWK tabwe is missing",
		wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_mcwk_vdd_tabwe->count >= 1,
		"VDD dependency on MCWK tabwe has to have is missing.",
		wetuwn -EINVAW);

	tabwe_info->max_cwock_vowtage_on_ac.scwk =
		awwowed_scwk_vdd_tabwe->entwies[awwowed_scwk_vdd_tabwe->count - 1].cwk;
	tabwe_info->max_cwock_vowtage_on_ac.mcwk =
		awwowed_mcwk_vdd_tabwe->entwies[awwowed_mcwk_vdd_tabwe->count - 1].cwk;
	if (hwmgw->chip_id >= CHIP_POWAWIS10 && hwmgw->chip_id <= CHIP_VEGAM)
		tabwe_info->max_cwock_vowtage_on_ac.vddc =
			smu7_find_highest_vddc(hwmgw);
	ewse
		tabwe_info->max_cwock_vowtage_on_ac.vddc =
			awwowed_scwk_vdd_tabwe->entwies[awwowed_scwk_vdd_tabwe->count - 1].vddc;
	tabwe_info->max_cwock_vowtage_on_ac.vddci =
		awwowed_mcwk_vdd_tabwe->entwies[awwowed_mcwk_vdd_tabwe->count - 1].vddci;

	hwmgw->dyn_state.max_cwock_vowtage_on_ac.scwk = tabwe_info->max_cwock_vowtage_on_ac.scwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_ac.mcwk = tabwe_info->max_cwock_vowtage_on_ac.mcwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddc = tabwe_info->max_cwock_vowtage_on_ac.vddc;
	hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddci = tabwe_info->max_cwock_vowtage_on_ac.vddci;

	wetuwn 0;
}

static int smu7_patch_vowtage_wowkawound(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
		       (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe;
	uint32_t i;
	uint32_t hw_wevision, sub_vendow_id, sub_sys_id;
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (tabwe_info != NUWW) {
		dep_mcwk_tabwe = tabwe_info->vdd_dep_on_mcwk;
		wookup_tabwe = tabwe_info->vddc_wookup_tabwe;
	} ewse
		wetuwn 0;

	hw_wevision = adev->pdev->wevision;
	sub_sys_id = adev->pdev->subsystem_device;
	sub_vendow_id = adev->pdev->subsystem_vendow;

	if (adev->pdev->device == 0x67DF && hw_wevision == 0xC7 &&
	    ((sub_sys_id == 0xb37 && sub_vendow_id == 0x1002) ||
	     (sub_sys_id == 0x4a8 && sub_vendow_id == 0x1043) ||
	     (sub_sys_id == 0x9480 && sub_vendow_id == 0x1682))) {

		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device,
					      CGS_IND_WEG__SMC,
					      PWW_CKS_CNTW,
					      CKS_STWETCH_AMOUNT,
					      0x3);

		if (wookup_tabwe->entwies[dep_mcwk_tabwe->entwies[dep_mcwk_tabwe->count-1].vddInd].us_vdd >= 1000)
			wetuwn 0;

		fow (i = 0; i < wookup_tabwe->count; i++) {
			if (wookup_tabwe->entwies[i].us_vdd < 0xff01 && wookup_tabwe->entwies[i].us_vdd >= 1000) {
				dep_mcwk_tabwe->entwies[dep_mcwk_tabwe->count-1].vddInd = (uint8_t) i;
				wetuwn 0;
			}
		}
	}
	wetuwn 0;
}

static int smu7_thewmaw_pawametew_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct pp_atomctww_gpio_pin_assignment gpio_pin_assignment;
	uint32_t temp_weg;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);


	if (atomctww_get_pp_assign_pin(hwmgw, VDDC_PCC_GPIO_PINID, &gpio_pin_assignment)) {
		temp_weg = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCNB_PWWMGT_CNTW);
		switch (gpio_pin_assignment.uc_gpio_pin_bit_shift) {
		case 0:
			temp_weg = PHM_SET_FIEWD(temp_weg, CNB_PWWMGT_CNTW, GNB_SWOW_MODE, 0x1);
			bweak;
		case 1:
			temp_weg = PHM_SET_FIEWD(temp_weg, CNB_PWWMGT_CNTW, GNB_SWOW_MODE, 0x2);
			bweak;
		case 2:
			temp_weg = PHM_SET_FIEWD(temp_weg, CNB_PWWMGT_CNTW, GNB_SWOW, 0x1);
			bweak;
		case 3:
			temp_weg = PHM_SET_FIEWD(temp_weg, CNB_PWWMGT_CNTW, FOWCE_NB_PS1, 0x1);
			bweak;
		case 4:
			temp_weg = PHM_SET_FIEWD(temp_weg, CNB_PWWMGT_CNTW, DPM_ENABWED, 0x1);
			bweak;
		defauwt:
			bweak;
		}
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCNB_PWWMGT_CNTW, temp_weg);
	}

	if (tabwe_info == NUWW)
		wetuwn 0;

	if (tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp != 0 &&
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanContwowMode) {
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanPWMMinWimit =
			(uint16_t)hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucMinimumPWMWimit;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanPWMMaxWimit =
			(uint16_t)hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanPWMStep = 1;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMMaxWimit = 100;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMMinWimit =
			(uint16_t)hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucMinimumPWMWimit;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMStep = 1;

		tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp = (tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp >= 50) ?
								(tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp - 50) : 0;

		tabwe_info->cac_dtp_tabwe->usOpewatingTempMaxWimit = tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp;
		tabwe_info->cac_dtp_tabwe->usOpewatingTempStep = 1;
		tabwe_info->cac_dtp_tabwe->usOpewatingTempHyst = 1;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanPWM =
			       hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanWPM =
			       hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanWPM;

		hwmgw->dyn_state.cac_dtp_tabwe->usOpewatingTempMinWimit =
			       tabwe_info->cac_dtp_tabwe->usOpewatingTempMinWimit;

		hwmgw->dyn_state.cac_dtp_tabwe->usOpewatingTempMaxWimit =
			       tabwe_info->cac_dtp_tabwe->usOpewatingTempMaxWimit;

		hwmgw->dyn_state.cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp =
			       tabwe_info->cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp;

		hwmgw->dyn_state.cac_dtp_tabwe->usOpewatingTempStep =
			       tabwe_info->cac_dtp_tabwe->usOpewatingTempStep;

		hwmgw->dyn_state.cac_dtp_tabwe->usTawgetOpewatingTemp =
			       tabwe_info->cac_dtp_tabwe->usTawgetOpewatingTemp;
		if (hwmgw->featuwe_mask & PP_OD_FUZZY_FAN_CONTWOW_MASK)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_ODFuzzyFanContwowSuppowt);
	}

	wetuwn 0;
}

/**
 * smu7_patch_ppt_v0_with_vdd_weakage - Change viwtuaw weakage vowtage to actuaw vawue.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @vowtage: pointew to changing vowtage
 * @weakage_tabwe: pointew to weakage tabwe
 */
static void smu7_patch_ppt_v0_with_vdd_weakage(stwuct pp_hwmgw *hwmgw,
		uint32_t *vowtage, stwuct smu7_weakage_vowtage *weakage_tabwe)
{
	uint32_t index;

	/* seawch fow weakage vowtage ID 0xff01 ~ 0xff08 */
	fow (index = 0; index < weakage_tabwe->count; index++) {
		/* if this vowtage matches a weakage vowtage ID */
		/* patch with actuaw weakage vowtage */
		if (weakage_tabwe->weakage_id[index] == *vowtage) {
			*vowtage = weakage_tabwe->actuaw_vowtage[index];
			bweak;
		}
	}

	if (*vowtage > ATOM_VIWTUAW_VOWTAGE_ID0)
		pw_info("Vowtage vawue wooks wike a Weakage ID but it's not patched\n");
}


static int smu7_patch_vddc(stwuct pp_hwmgw *hwmgw,
			      stwuct phm_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
						&data->vddc_weakage);

	wetuwn 0;
}

static int smu7_patch_vddci(stwuct pp_hwmgw *hwmgw,
			       stwuct phm_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
							&data->vddci_weakage);

	wetuwn 0;
}

static int smu7_patch_vce_vddc(stwuct pp_hwmgw *hwmgw,
				  stwuct phm_vce_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
							&data->vddc_weakage);

	wetuwn 0;
}


static int smu7_patch_uvd_vddc(stwuct pp_hwmgw *hwmgw,
				  stwuct phm_uvd_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
							&data->vddc_weakage);

	wetuwn 0;
}

static int smu7_patch_vddc_shed_wimit(stwuct pp_hwmgw *hwmgw,
					 stwuct phm_phase_shedding_wimits_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].Vowtage,
							&data->vddc_weakage);

	wetuwn 0;
}

static int smu7_patch_samu_vddc(stwuct pp_hwmgw *hwmgw,
				   stwuct phm_samu_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
							&data->vddc_weakage);

	wetuwn 0;
}

static int smu7_patch_acp_vddc(stwuct pp_hwmgw *hwmgw,
				  stwuct phm_acp_cwock_vowtage_dependency_tabwe *tab)
{
	uint16_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab)
		fow (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &tab->entwies[i].v,
					&data->vddc_weakage);

	wetuwn 0;
}

static int smu7_patch_wimits_vddc(stwuct pp_hwmgw *hwmgw,
				  stwuct phm_cwock_and_vowtage_wimits *tab)
{
	uint32_t vddc, vddci;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab) {
		vddc = tab->vddc;
		smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &vddc,
						   &data->vddc_weakage);
		tab->vddc = vddc;
		vddci = tab->vddci;
		smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &vddci,
						   &data->vddci_weakage);
		tab->vddci = vddci;
	}

	wetuwn 0;
}

static int smu7_patch_cac_vddc(stwuct pp_hwmgw *hwmgw, stwuct phm_cac_weakage_tabwe *tab)
{
	uint32_t i;
	uint32_t vddc;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (tab) {
		fow (i = 0; i < tab->count; i++) {
			vddc = (uint32_t)(tab->entwies[i].Vddc);
			smu7_patch_ppt_v0_with_vdd_weakage(hwmgw, &vddc, &data->vddc_weakage);
			tab->entwies[i].Vddc = (uint16_t)vddc;
		}
	}

	wetuwn 0;
}

static int smu7_patch_dependency_tabwes_with_weakage(stwuct pp_hwmgw *hwmgw)
{
	int tmp;

	tmp = smu7_patch_vddc(hwmgw, hwmgw->dyn_state.vddc_dependency_on_scwk);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_vddc(hwmgw, hwmgw->dyn_state.vddc_dependency_on_mcwk);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_vddc(hwmgw, hwmgw->dyn_state.vddc_dep_on_daw_pwww);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_vddci(hwmgw, hwmgw->dyn_state.vddci_dependency_on_mcwk);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_vce_vddc(hwmgw, hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_uvd_vddc(hwmgw, hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_samu_vddc(hwmgw, hwmgw->dyn_state.samu_cwock_vowtage_dependency_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_acp_vddc(hwmgw, hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_vddc_shed_wimit(hwmgw, hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_wimits_vddc(hwmgw, &hwmgw->dyn_state.max_cwock_vowtage_on_ac);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_wimits_vddc(hwmgw, &hwmgw->dyn_state.max_cwock_vowtage_on_dc);
	if (tmp)
		wetuwn -EINVAW;

	tmp = smu7_patch_cac_vddc(hwmgw, hwmgw->dyn_state.cac_weakage_tabwe);
	if (tmp)
		wetuwn -EINVAW;

	wetuwn 0;
}


static int smu7_set_pwivate_data_based_on_pptabwe_v0(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_scwk_vddc_tabwe = hwmgw->dyn_state.vddc_dependency_on_scwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_mcwk_vddc_tabwe = hwmgw->dyn_state.vddc_dependency_on_mcwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_mcwk_vddci_tabwe = hwmgw->dyn_state.vddci_dependency_on_mcwk;

	PP_ASSEWT_WITH_CODE(awwowed_scwk_vddc_tabwe != NUWW,
		"VDDC dependency on SCWK tabwe is missing. This tabwe is mandatowy",
		wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_scwk_vddc_tabwe->count >= 1,
		"VDDC dependency on SCWK tabwe has to have is missing. This tabwe is mandatowy",
		wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(awwowed_mcwk_vddc_tabwe != NUWW,
		"VDDC dependency on MCWK tabwe is missing. This tabwe is mandatowy",
		wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(awwowed_mcwk_vddc_tabwe->count >= 1,
		"VDD dependency on MCWK tabwe has to have is missing. This tabwe is mandatowy",
		wetuwn -EINVAW);

	data->min_vddc_in_pptabwe = (uint16_t)awwowed_scwk_vddc_tabwe->entwies[0].v;
	data->max_vddc_in_pptabwe = (uint16_t)awwowed_scwk_vddc_tabwe->entwies[awwowed_scwk_vddc_tabwe->count - 1].v;

	hwmgw->dyn_state.max_cwock_vowtage_on_ac.scwk =
		awwowed_scwk_vddc_tabwe->entwies[awwowed_scwk_vddc_tabwe->count - 1].cwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_ac.mcwk =
		awwowed_mcwk_vddc_tabwe->entwies[awwowed_mcwk_vddc_tabwe->count - 1].cwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddc =
		awwowed_scwk_vddc_tabwe->entwies[awwowed_scwk_vddc_tabwe->count - 1].v;

	if (awwowed_mcwk_vddci_tabwe != NUWW && awwowed_mcwk_vddci_tabwe->count >= 1) {
		data->min_vddci_in_pptabwe = (uint16_t)awwowed_mcwk_vddci_tabwe->entwies[0].v;
		data->max_vddci_in_pptabwe = (uint16_t)awwowed_mcwk_vddci_tabwe->entwies[awwowed_mcwk_vddci_tabwe->count - 1].v;
	}

	if (hwmgw->dyn_state.vddci_dependency_on_mcwk != NUWW && hwmgw->dyn_state.vddci_dependency_on_mcwk->count >= 1)
		hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddci = hwmgw->dyn_state.vddci_dependency_on_mcwk->entwies[hwmgw->dyn_state.vddci_dependency_on_mcwk->count - 1].v;

	wetuwn 0;
}

static int smu7_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw)
{
	kfwee(hwmgw->dyn_state.vddc_dep_on_daw_pwww);
	hwmgw->dyn_state.vddc_dep_on_daw_pwww = NUWW;
	kfwee(hwmgw->backend);
	hwmgw->backend = NUWW;

	wetuwn 0;
}

static int smu7_get_ewb_vowtages(stwuct pp_hwmgw *hwmgw)
{
	uint16_t viwtuaw_vowtage_id, vddc, vddci, efuse_vowtage_id;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int i;

	if (atomctww_get_weakage_id_fwom_efuse(hwmgw, &efuse_vowtage_id) == 0) {
		fow (i = 0; i < SMU7_MAX_WEAKAGE_COUNT; i++) {
			viwtuaw_vowtage_id = ATOM_VIWTUAW_VOWTAGE_ID0 + i;
			if (atomctww_get_weakage_vddc_base_on_weakage(hwmgw, &vddc, &vddci,
								viwtuaw_vowtage_id,
								efuse_vowtage_id) == 0) {
				if (vddc != 0 && vddc != viwtuaw_vowtage_id) {
					data->vddc_weakage.actuaw_vowtage[data->vddc_weakage.count] = vddc;
					data->vddc_weakage.weakage_id[data->vddc_weakage.count] = viwtuaw_vowtage_id;
					data->vddc_weakage.count++;
				}
				if (vddci != 0 && vddci != viwtuaw_vowtage_id) {
					data->vddci_weakage.actuaw_vowtage[data->vddci_weakage.count] = vddci;
					data->vddci_weakage.weakage_id[data->vddci_weakage.count] = viwtuaw_vowtage_id;
					data->vddci_weakage.count++;
				}
			}
		}
	}
	wetuwn 0;
}

#define WEAKAGE_ID_MSB			463
#define WEAKAGE_ID_WSB			454

static int smu7_update_edc_weakage_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t efuse;
	uint16_t offset;
	int wet = 0;

	if (data->disabwe_edc_weakage_contwowwew)
		wetuwn 0;

	wet = atomctww_get_edc_hiwo_weakage_offset_tabwe(hwmgw,
							 &data->edc_hiwo_weakage_offset_fwom_vbios);
	if (wet)
		wetuwn wet;

	if (data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtWoDpm7TabweOffset &&
	    data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtHiDpm7TabweOffset) {
		atomctww_wead_efuse(hwmgw, WEAKAGE_ID_WSB, WEAKAGE_ID_MSB, &efuse);
		if (efuse < data->edc_hiwo_weakage_offset_fwom_vbios.usHiWoWeakageThweshowd)
			offset = data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtWoDpm7TabweOffset;
		ewse
			offset = data->edc_hiwo_weakage_offset_fwom_vbios.usEdcDidtHiDpm7TabweOffset;

		wet = atomctww_get_edc_weakage_tabwe(hwmgw,
						     &data->edc_weakage_tabwe,
						     offset);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int smu7_hwmgw_backend_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data;
	int wesuwt = 0;

	data = kzawwoc(sizeof(stwuct smu7_hwmgw), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->backend = data;
	smu7_patch_vowtage_wowkawound(hwmgw);
	smu7_init_dpm_defauwts(hwmgw);

	/* Get weakage vowtage based on weakage ID. */
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EVV)) {
		wesuwt = smu7_get_evv_vowtages(hwmgw);
		if (wesuwt) {
			pw_info("Get EVV Vowtage Faiwed.  Abowt Dwivew woading!\n");
			kfwee(hwmgw->backend);
			hwmgw->backend = NUWW;
			wetuwn -EINVAW;
		}
	} ewse {
		smu7_get_ewb_vowtages(hwmgw);
	}

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		smu7_compwete_dependency_tabwes(hwmgw);
		smu7_set_pwivate_data_based_on_pptabwe_v1(hwmgw);
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		smu7_patch_dependency_tabwes_with_weakage(hwmgw);
		smu7_set_pwivate_data_based_on_pptabwe_v0(hwmgw);
	}

	/* Initawize Dynamic State Adjustment Wuwe Settings */
	wesuwt = phm_initiawiza_dynamic_state_adjustment_wuwe_settings(hwmgw);

	if (0 == wesuwt) {
		stwuct amdgpu_device *adev = hwmgw->adev;

		data->is_twu_enabwed = fawse;

		hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews =
							SMU7_MAX_HAWDWAWE_POWEWWEVEWS;
		hwmgw->pwatfowm_descwiptow.hawdwawePewfowmanceWevews = 2;
		hwmgw->pwatfowm_descwiptow.minimumCwocksWeductionPewcentage = 50;

		data->pcie_gen_cap = adev->pm.pcie_gen_mask;
		if (data->pcie_gen_cap & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)
			data->pcie_spc_cap = 20;
		ewse
			data->pcie_spc_cap = 16;
		data->pcie_wane_cap = adev->pm.pcie_mww_mask;

		hwmgw->pwatfowm_descwiptow.vbiosIntewwuptId = 0x20000400; /* IWQ_SOUWCE1_SW_INT */
/* The twue cwock step depends on the fwequency, typicawwy 4.5 ow 9 MHz. Hewe we use 5. */
		hwmgw->pwatfowm_descwiptow.cwockStep.engineCwock = 500;
		hwmgw->pwatfowm_descwiptow.cwockStep.memowyCwock = 500;
		smu7_thewmaw_pawametew_init(hwmgw);
	} ewse {
		/* Ignowe wetuwn vawue in hewe, we awe cweaning up a mess. */
		smu7_hwmgw_backend_fini(hwmgw);
	}

	wesuwt = smu7_update_edc_weakage_tabwe(hwmgw);
	if (wesuwt) {
		smu7_hwmgw_backend_fini(hwmgw);
		wetuwn wesuwt;
	}

	wetuwn 0;
}

static int smu7_fowce_dpm_highest(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t wevew, tmp;

	if (!data->pcie_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask) {
			wevew = 0;
			tmp = data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask;
			whiwe (tmp >>= 1)
				wevew++;

			if (wevew)
				smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_PCIeDPM_FowceWevew, wevew,
						NUWW);
		}
	}

	if (!data->scwk_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask) {
			wevew = 0;
			tmp = data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask;
			whiwe (tmp >>= 1)
				wevew++;

			if (wevew)
				smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SCWKDPM_SetEnabwedMask,
						(1 << wevew),
						NUWW);
		}
	}

	if (!data->mcwk_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask) {
			wevew = 0;
			tmp = data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask;
			whiwe (tmp >>= 1)
				wevew++;

			if (wevew)
				smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_MCWKDPM_SetEnabwedMask,
						(1 << wevew),
						NUWW);
		}
	}

	wetuwn 0;
}

static int smu7_upwoad_dpm_wevew_enabwe_mask(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
		phm_appwy_daw_min_vowtage_wequest(hwmgw);
/* TO DO  fow v0 icewand and Ci*/

	if (!data->scwk_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask)
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SCWKDPM_SetEnabwedMask,
					data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask,
					NUWW);
	}

	if (!data->mcwk_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask)
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_MCWKDPM_SetEnabwedMask,
					data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask,
					NUWW);
	}

	wetuwn 0;
}

static int smu7_unfowce_dpm_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (!smum_is_dpm_wunning(hwmgw))
		wetuwn -EINVAW;

	if (!data->pcie_dpm_key_disabwed) {
		smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_PCIeDPM_UnFowceWevew,
				NUWW);
	}

	wetuwn smu7_upwoad_dpm_wevew_enabwe_mask(hwmgw);
}

static int smu7_fowce_dpm_wowest(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data =
			(stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t wevew;

	if (!data->scwk_dpm_key_disabwed)
		if (data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask) {
			wevew = phm_get_wowest_enabwed_wevew(hwmgw,
							      data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
							    PPSMC_MSG_SCWKDPM_SetEnabwedMask,
							    (1 << wevew),
							    NUWW);

	}

	if (!data->mcwk_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask) {
			wevew = phm_get_wowest_enabwed_wevew(hwmgw,
							      data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
							    PPSMC_MSG_MCWKDPM_SetEnabwedMask,
							    (1 << wevew),
							    NUWW);
		}
	}

	if (!data->pcie_dpm_key_disabwed) {
		if (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask) {
			wevew = phm_get_wowest_enabwed_wevew(hwmgw,
							      data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
							    PPSMC_MSG_PCIeDPM_FowceWevew,
							    (wevew),
							    NUWW);
		}
	}

	wetuwn 0;
}

static int smu7_get_pwofiwing_cwk(stwuct pp_hwmgw *hwmgw, enum amd_dpm_fowced_wevew wevew,
				uint32_t *scwk_mask, uint32_t *mcwk_mask, uint32_t *pcie_mask)
{
	uint32_t pewcentage;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *gowden_dpm_tabwe = &data->gowden_dpm_tabwe;
	int32_t tmp_mcwk;
	int32_t tmp_scwk;
	int32_t count;

	if (gowden_dpm_tabwe->mcwk_tabwe.count < 1)
		wetuwn -EINVAW;

	pewcentage = 100 * gowden_dpm_tabwe->scwk_tabwe.dpm_wevews[gowden_dpm_tabwe->scwk_tabwe.count - 1].vawue /
			gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 1].vawue;

	if (gowden_dpm_tabwe->mcwk_tabwe.count == 1) {
		pewcentage = 70;
		tmp_mcwk = gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 1].vawue;
		*mcwk_mask = gowden_dpm_tabwe->mcwk_tabwe.count - 1;
	} ewse {
		tmp_mcwk = gowden_dpm_tabwe->mcwk_tabwe.dpm_wevews[gowden_dpm_tabwe->mcwk_tabwe.count - 2].vawue;
		*mcwk_mask = gowden_dpm_tabwe->mcwk_tabwe.count - 2;
	}

	tmp_scwk = tmp_mcwk * pewcentage / 100;

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		fow (count = hwmgw->dyn_state.vddc_dependency_on_scwk->count-1;
			count >= 0; count--) {
			if (tmp_scwk >= hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[count].cwk) {
				*scwk_mask = count;
				bweak;
			}
		}
		if (count < 0 || wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK)
			*scwk_mask = 0;

		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			*scwk_mask = hwmgw->dyn_state.vddc_dependency_on_scwk->count-1;
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		stwuct phm_ppt_v1_infowmation *tabwe_info =
				(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

		fow (count = tabwe_info->vdd_dep_on_scwk->count-1; count >= 0; count--) {
			if (tmp_scwk >= tabwe_info->vdd_dep_on_scwk->entwies[count].cwk) {
				*scwk_mask = count;
				bweak;
			}
		}
		if (count < 0 || wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK)
			*scwk_mask = 0;

		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			*scwk_mask = tabwe_info->vdd_dep_on_scwk->count - 1;
	}

	if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK)
		*mcwk_mask = 0;
	ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
		*mcwk_mask = gowden_dpm_tabwe->mcwk_tabwe.count - 1;

	*pcie_mask = data->dpm_tabwe.pcie_speed_tabwe.count - 1;

	wetuwn 0;
}

static int smu7_fowce_dpm_wevew(stwuct pp_hwmgw *hwmgw,
				enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;
	uint32_t scwk_mask = 0;
	uint32_t mcwk_mask = 0;
	uint32_t pcie_mask = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		wet = smu7_fowce_dpm_highest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		wet = smu7_fowce_dpm_wowest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		wet = smu7_unfowce_dpm_wevews(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		wet = smu7_get_pwofiwing_cwk(hwmgw, wevew, &scwk_mask, &mcwk_mask, &pcie_mask);
		if (wet)
			wetuwn wet;
		smu7_fowce_cwock_wevew(hwmgw, PP_SCWK, 1<<scwk_mask);
		smu7_fowce_cwock_wevew(hwmgw, PP_MCWK, 1<<mcwk_mask);
		smu7_fowce_cwock_wevew(hwmgw, PP_PCIE, 1<<pcie_mask);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}

	if (!wet) {
		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK && hwmgw->dpm_wevew != AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu7_fan_ctww_set_fan_speed_pwm(hwmgw, 255);
		ewse if (wevew != AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK && hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu7_fan_ctww_weset_fan_speed_to_defauwt(hwmgw);
	}
	wetuwn wet;
}

static int smu7_get_powew_state_size(stwuct pp_hwmgw *hwmgw)
{
	wetuwn sizeof(stwuct smu7_powew_state);
}

static int smu7_vbwank_too_showt(stwuct pp_hwmgw *hwmgw,
				 uint32_t vbwank_time_us)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t switch_wimit_us;

	switch (hwmgw->chip_id) {
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
		if (hwmgw->is_kickew || (hwmgw->chip_id == CHIP_POWAWIS12))
			switch_wimit_us = data->is_memowy_gddw5 ? 450 : 150;
		ewse
			switch_wimit_us = data->is_memowy_gddw5 ? 200 : 150;
		bweak;
	case CHIP_VEGAM:
		switch_wimit_us = 30;
		bweak;
	defauwt:
		switch_wimit_us = data->is_memowy_gddw5 ? 450 : 150;
		bweak;
	}

	if (vbwank_time_us < switch_wimit_us)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int smu7_appwy_state_adjust_wuwes(stwuct pp_hwmgw *hwmgw,
				stwuct pp_powew_state *wequest_ps,
			const stwuct pp_powew_state *cuwwent_ps)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct smu7_powew_state *smu7_ps =
				cast_phw_smu7_powew_state(&wequest_ps->hawdwawe);
	uint32_t scwk;
	uint32_t mcwk;
	stwuct PP_Cwocks minimum_cwocks = {0};
	boow disabwe_mcwk_switching;
	boow disabwe_mcwk_switching_fow_fwame_wock;
	boow disabwe_mcwk_switching_fow_dispway;
	const stwuct phm_cwock_and_vowtage_wimits *max_wimits;
	uint32_t i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	int32_t count;
	int32_t stabwe_pstate_scwk = 0, stabwe_pstate_mcwk = 0;
	uint32_t watency;
	boow watency_awwowed = fawse;

	data->battewy_state = (PP_StateUIWabew_Battewy ==
			wequest_ps->cwassification.ui_wabew);
	data->mcwk_ignowe_signaw = fawse;

	max_wimits = adev->pm.ac_powew ?
			&(hwmgw->dyn_state.max_cwock_vowtage_on_ac) :
			&(hwmgw->dyn_state.max_cwock_vowtage_on_dc);

	/* Cap cwock DPM tabwes at DC MAX if it is in DC. */
	if (!adev->pm.ac_powew) {
		fow (i = 0; i < smu7_ps->pewfowmance_wevew_count; i++) {
			if (smu7_ps->pewfowmance_wevews[i].memowy_cwock > max_wimits->mcwk)
				smu7_ps->pewfowmance_wevews[i].memowy_cwock = max_wimits->mcwk;
			if (smu7_ps->pewfowmance_wevews[i].engine_cwock > max_wimits->scwk)
				smu7_ps->pewfowmance_wevews[i].engine_cwock = max_wimits->scwk;
		}
	}

	minimum_cwocks.engineCwock = hwmgw->dispway_config->min_cowe_set_cwock;
	minimum_cwocks.memowyCwock = hwmgw->dispway_config->min_mem_set_cwock;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StabwePState)) {
		max_wimits = &(hwmgw->dyn_state.max_cwock_vowtage_on_ac);
		stabwe_pstate_scwk = (max_wimits->scwk * 75) / 100;

		fow (count = tabwe_info->vdd_dep_on_scwk->count - 1;
				count >= 0; count--) {
			if (stabwe_pstate_scwk >=
					tabwe_info->vdd_dep_on_scwk->entwies[count].cwk) {
				stabwe_pstate_scwk =
						tabwe_info->vdd_dep_on_scwk->entwies[count].cwk;
				bweak;
			}
		}

		if (count < 0)
			stabwe_pstate_scwk = tabwe_info->vdd_dep_on_scwk->entwies[0].cwk;

		stabwe_pstate_mcwk = max_wimits->mcwk;

		minimum_cwocks.engineCwock = stabwe_pstate_scwk;
		minimum_cwocks.memowyCwock = stabwe_pstate_mcwk;
	}

	disabwe_mcwk_switching_fow_fwame_wock = phm_cap_enabwed(
				    hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				    PHM_PwatfowmCaps_DisabweMcwkSwitchingFowFwameWock);

	disabwe_mcwk_switching_fow_dispway = ((1 < hwmgw->dispway_config->num_dispway) &&
						!hwmgw->dispway_config->muwti_monitow_in_sync) ||
						(hwmgw->dispway_config->num_dispway &&
						smu7_vbwank_too_showt(hwmgw, hwmgw->dispway_config->min_vbwank_time));

	disabwe_mcwk_switching = disabwe_mcwk_switching_fow_fwame_wock ||
					 disabwe_mcwk_switching_fow_dispway;

	if (hwmgw->dispway_config->num_dispway == 0) {
		if (hwmgw->chip_id >= CHIP_POWAWIS10 && hwmgw->chip_id <= CHIP_VEGAM)
			data->mcwk_ignowe_signaw = twue;
		ewse
			disabwe_mcwk_switching = fawse;
	}

	scwk = smu7_ps->pewfowmance_wevews[0].engine_cwock;
	mcwk = smu7_ps->pewfowmance_wevews[0].memowy_cwock;

	if (disabwe_mcwk_switching &&
	    (!(hwmgw->chip_id >= CHIP_POWAWIS10 &&
	    hwmgw->chip_id <= CHIP_VEGAM)))
		mcwk = smu7_ps->pewfowmance_wevews
		[smu7_ps->pewfowmance_wevew_count - 1].memowy_cwock;

	if (scwk < minimum_cwocks.engineCwock)
		scwk = (minimum_cwocks.engineCwock > max_wimits->scwk) ?
				max_wimits->scwk : minimum_cwocks.engineCwock;

	if (mcwk < minimum_cwocks.memowyCwock)
		mcwk = (minimum_cwocks.memowyCwock > max_wimits->mcwk) ?
				max_wimits->mcwk : minimum_cwocks.memowyCwock;

	smu7_ps->pewfowmance_wevews[0].engine_cwock = scwk;
	smu7_ps->pewfowmance_wevews[0].memowy_cwock = mcwk;

	smu7_ps->pewfowmance_wevews[1].engine_cwock =
		(smu7_ps->pewfowmance_wevews[1].engine_cwock >=
				smu7_ps->pewfowmance_wevews[0].engine_cwock) ?
						smu7_ps->pewfowmance_wevews[1].engine_cwock :
						smu7_ps->pewfowmance_wevews[0].engine_cwock;

	if (disabwe_mcwk_switching) {
		if (mcwk < smu7_ps->pewfowmance_wevews[1].memowy_cwock)
			mcwk = smu7_ps->pewfowmance_wevews[1].memowy_cwock;

		if (hwmgw->chip_id >= CHIP_POWAWIS10 && hwmgw->chip_id <= CHIP_VEGAM) {
			if (disabwe_mcwk_switching_fow_dispway) {
				/* Find the wowest MCWK fwequency that is within
				 * the towewabwe watency defined in DAW
				 */
				watency = hwmgw->dispway_config->dce_towewabwe_mcwk_in_active_watency;
				fow (i = 0; i < data->mcwk_watency_tabwe.count; i++) {
					if (data->mcwk_watency_tabwe.entwies[i].watency <= watency) {
						watency_awwowed = twue;

						if ((data->mcwk_watency_tabwe.entwies[i].fwequency >=
								smu7_ps->pewfowmance_wevews[0].memowy_cwock) &&
						    (data->mcwk_watency_tabwe.entwies[i].fwequency <=
								smu7_ps->pewfowmance_wevews[1].memowy_cwock)) {
							mcwk = data->mcwk_watency_tabwe.entwies[i].fwequency;
							bweak;
						}
					}
				}
				if ((i >= data->mcwk_watency_tabwe.count - 1) && !watency_awwowed) {
					data->mcwk_ignowe_signaw = twue;
				} ewse {
					data->mcwk_ignowe_signaw = fawse;
				}
			}

			if (disabwe_mcwk_switching_fow_fwame_wock)
				mcwk = smu7_ps->pewfowmance_wevews[1].memowy_cwock;
		}

		smu7_ps->pewfowmance_wevews[0].memowy_cwock = mcwk;

		if (!(hwmgw->chip_id >= CHIP_POWAWIS10 &&
		      hwmgw->chip_id <= CHIP_VEGAM))
			smu7_ps->pewfowmance_wevews[1].memowy_cwock = mcwk;
	} ewse {
		if (smu7_ps->pewfowmance_wevews[1].memowy_cwock <
				smu7_ps->pewfowmance_wevews[0].memowy_cwock)
			smu7_ps->pewfowmance_wevews[1].memowy_cwock =
					smu7_ps->pewfowmance_wevews[0].memowy_cwock;
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StabwePState)) {
		fow (i = 0; i < smu7_ps->pewfowmance_wevew_count; i++) {
			smu7_ps->pewfowmance_wevews[i].engine_cwock = stabwe_pstate_scwk;
			smu7_ps->pewfowmance_wevews[i].memowy_cwock = stabwe_pstate_mcwk;
			smu7_ps->pewfowmance_wevews[i].pcie_gen = data->pcie_gen_pewfowmance.max;
			smu7_ps->pewfowmance_wevews[i].pcie_wane = data->pcie_gen_pewfowmance.max;
		}
	}
	wetuwn 0;
}


static uint32_t smu7_dpm_get_mcwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct pp_powew_state  *ps;
	stwuct smu7_powew_state  *smu7_ps;

	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	ps = hwmgw->wequest_ps;

	if (ps == NUWW)
		wetuwn -EINVAW;

	smu7_ps = cast_phw_smu7_powew_state(&ps->hawdwawe);

	if (wow)
		wetuwn smu7_ps->pewfowmance_wevews[0].memowy_cwock;
	ewse
		wetuwn smu7_ps->pewfowmance_wevews
				[smu7_ps->pewfowmance_wevew_count-1].memowy_cwock;
}

static uint32_t smu7_dpm_get_scwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct pp_powew_state  *ps;
	stwuct smu7_powew_state  *smu7_ps;

	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	ps = hwmgw->wequest_ps;

	if (ps == NUWW)
		wetuwn -EINVAW;

	smu7_ps = cast_phw_smu7_powew_state(&ps->hawdwawe);

	if (wow)
		wetuwn smu7_ps->pewfowmance_wevews[0].engine_cwock;
	ewse
		wetuwn smu7_ps->pewfowmance_wevews
				[smu7_ps->pewfowmance_wevew_count-1].engine_cwock;
}

static int smu7_dpm_patch_boot_state(stwuct pp_hwmgw *hwmgw,
					stwuct pp_hw_powew_state *hw_ps)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_powew_state *ps = (stwuct smu7_powew_state *)hw_ps;
	ATOM_FIWMWAWE_INFO_V2_2 *fw_info;
	uint16_t size;
	uint8_t fwev, cwev;
	int index = GetIndexIntoMastewTabwe(DATA, FiwmwaweInfo);

	/* Fiwst wetwieve the Boot cwocks and VDDC fwom the fiwmwawe info tabwe.
	 * We assume hewe that fw_info is unchanged if this caww faiws.
	 */
	fw_info = (ATOM_FIWMWAWE_INFO_V2_2 *)smu_atom_get_data_tabwe(hwmgw->adev, index,
			&size, &fwev, &cwev);
	if (!fw_info)
		/* Duwing a test, thewe is no fiwmwawe info tabwe. */
		wetuwn 0;

	/* Patch the state. */
	data->vbios_boot_state.scwk_bootup_vawue =
			we32_to_cpu(fw_info->uwDefauwtEngineCwock);
	data->vbios_boot_state.mcwk_bootup_vawue =
			we32_to_cpu(fw_info->uwDefauwtMemowyCwock);
	data->vbios_boot_state.mvdd_bootup_vawue =
			we16_to_cpu(fw_info->usBootUpMVDDCVowtage);
	data->vbios_boot_state.vddc_bootup_vawue =
			we16_to_cpu(fw_info->usBootUpVDDCVowtage);
	data->vbios_boot_state.vddci_bootup_vawue =
			we16_to_cpu(fw_info->usBootUpVDDCIVowtage);
	data->vbios_boot_state.pcie_gen_bootup_vawue =
			smu7_get_cuwwent_pcie_speed(hwmgw);

	data->vbios_boot_state.pcie_wane_bootup_vawue =
			(uint16_t)smu7_get_cuwwent_pcie_wane_numbew(hwmgw);

	/* set boot powew state */
	ps->pewfowmance_wevews[0].memowy_cwock = data->vbios_boot_state.mcwk_bootup_vawue;
	ps->pewfowmance_wevews[0].engine_cwock = data->vbios_boot_state.scwk_bootup_vawue;
	ps->pewfowmance_wevews[0].pcie_gen = data->vbios_boot_state.pcie_gen_bootup_vawue;
	ps->pewfowmance_wevews[0].pcie_wane = data->vbios_boot_state.pcie_wane_bootup_vawue;

	wetuwn 0;
}

static int smu7_get_numbew_of_powewpway_tabwe_entwies(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	unsigned wong wet = 0;

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		wesuwt = pp_tabwes_get_num_of_entwies(hwmgw, &wet);
		wetuwn wesuwt ? 0 : wet;
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		wesuwt = get_numbew_of_powewpway_tabwe_entwies_v1_0(hwmgw);
		wetuwn wesuwt;
	}
	wetuwn 0;
}

static int smu7_get_pp_tabwe_entwy_cawwback_func_v1(stwuct pp_hwmgw *hwmgw,
		void *state, stwuct pp_powew_state *powew_state,
		void *pp_tabwe, uint32_t cwassification_fwag)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_powew_state  *smu7_powew_state =
			(stwuct smu7_powew_state *)(&(powew_state->hawdwawe));
	stwuct smu7_pewfowmance_wevew *pewfowmance_wevew;
	ATOM_Tonga_State *state_entwy = (ATOM_Tonga_State *)state;
	ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe =
			(ATOM_Tonga_POWEWPWAYTABWE *)pp_tabwe;
	PPTabwe_Genewic_SubTabwe_Headew *scwk_dep_tabwe =
			(PPTabwe_Genewic_SubTabwe_Headew *)
			(((unsigned wong)powewpway_tabwe) +
				we16_to_cpu(powewpway_tabwe->usScwkDependencyTabweOffset));

	ATOM_Tonga_MCWK_Dependency_Tabwe *mcwk_dep_tabwe =
			(ATOM_Tonga_MCWK_Dependency_Tabwe *)
			(((unsigned wong)powewpway_tabwe) +
				we16_to_cpu(powewpway_tabwe->usMcwkDependencyTabweOffset));

	/* The fowwowing fiewds awe not initiawized hewe: id owdewedWist awwStatesWist */
	powew_state->cwassification.ui_wabew =
			(we16_to_cpu(state_entwy->usCwassification) &
			ATOM_PPWIB_CWASSIFICATION_UI_MASK) >>
			ATOM_PPWIB_CWASSIFICATION_UI_SHIFT;
	powew_state->cwassification.fwags = cwassification_fwag;
	/* NOTE: Thewe is a cwassification2 fwag in BIOS that is not being used wight now */

	powew_state->cwassification.tempowawy_state = fawse;
	powew_state->cwassification.to_be_deweted = fawse;

	powew_state->vawidation.disawwowOnDC =
			(0 != (we32_to_cpu(state_entwy->uwCapsAndSettings) &
					ATOM_Tonga_DISAWWOW_ON_DC));

	powew_state->pcie.wanes = 0;

	powew_state->dispway.disabweFwameModuwation = fawse;
	powew_state->dispway.wimitWefweshwate = fawse;
	powew_state->dispway.enabweVawiBwight =
			(0 != (we32_to_cpu(state_entwy->uwCapsAndSettings) &
					ATOM_Tonga_ENABWE_VAWIBWIGHT));

	powew_state->vawidation.suppowtedPowewWevews = 0;
	powew_state->uvd_cwocks.VCWK = 0;
	powew_state->uvd_cwocks.DCWK = 0;
	powew_state->tempewatuwes.min = 0;
	powew_state->tempewatuwes.max = 0;

	pewfowmance_wevew = &(smu7_powew_state->pewfowmance_wevews
			[smu7_powew_state->pewfowmance_wevew_count++]);

	PP_ASSEWT_WITH_CODE(
			(smu7_powew_state->pewfowmance_wevew_count < smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_GWAPHICS)),
			"Pewfowmance wevews exceeds SMC wimit!",
			wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(
			(smu7_powew_state->pewfowmance_wevew_count <
					hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews),
			"Pewfowmance wevews exceeds Dwivew wimit!",
			wetuwn -EINVAW);

	/* Pewfowmance wevews awe awwanged fwom wow to high. */
	pewfowmance_wevew->memowy_cwock = mcwk_dep_tabwe->entwies
			[state_entwy->ucMemowyCwockIndexWow].uwMcwk;
	if (scwk_dep_tabwe->ucWevId == 0)
		pewfowmance_wevew->engine_cwock = ((ATOM_Tonga_SCWK_Dependency_Tabwe *)scwk_dep_tabwe)->entwies
			[state_entwy->ucEngineCwockIndexWow].uwScwk;
	ewse if (scwk_dep_tabwe->ucWevId == 1)
		pewfowmance_wevew->engine_cwock = ((ATOM_Powawis_SCWK_Dependency_Tabwe *)scwk_dep_tabwe)->entwies
			[state_entwy->ucEngineCwockIndexWow].uwScwk;
	pewfowmance_wevew->pcie_gen = get_pcie_gen_suppowt(data->pcie_gen_cap,
			state_entwy->ucPCIEGenWow);
	pewfowmance_wevew->pcie_wane = get_pcie_wane_suppowt(data->pcie_wane_cap,
			state_entwy->ucPCIEWaneWow);

	pewfowmance_wevew = &(smu7_powew_state->pewfowmance_wevews
			[smu7_powew_state->pewfowmance_wevew_count++]);
	pewfowmance_wevew->memowy_cwock = mcwk_dep_tabwe->entwies
			[state_entwy->ucMemowyCwockIndexHigh].uwMcwk;

	if (scwk_dep_tabwe->ucWevId == 0)
		pewfowmance_wevew->engine_cwock = ((ATOM_Tonga_SCWK_Dependency_Tabwe *)scwk_dep_tabwe)->entwies
			[state_entwy->ucEngineCwockIndexHigh].uwScwk;
	ewse if (scwk_dep_tabwe->ucWevId == 1)
		pewfowmance_wevew->engine_cwock = ((ATOM_Powawis_SCWK_Dependency_Tabwe *)scwk_dep_tabwe)->entwies
			[state_entwy->ucEngineCwockIndexHigh].uwScwk;

	pewfowmance_wevew->pcie_gen = get_pcie_gen_suppowt(data->pcie_gen_cap,
			state_entwy->ucPCIEGenHigh);
	pewfowmance_wevew->pcie_wane = get_pcie_wane_suppowt(data->pcie_wane_cap,
			state_entwy->ucPCIEWaneHigh);

	wetuwn 0;
}

static int smu7_get_pp_tabwe_entwy_v1(stwuct pp_hwmgw *hwmgw,
		unsigned wong entwy_index, stwuct pp_powew_state *state)
{
	int wesuwt;
	stwuct smu7_powew_state *ps;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe =
			tabwe_info->vdd_dep_on_mcwk;

	state->hawdwawe.magic = PHM_VIswands_Magic;

	ps = (stwuct smu7_powew_state *)(&state->hawdwawe);

	wesuwt = get_powewpway_tabwe_entwy_v1_0(hwmgw, entwy_index, state,
			smu7_get_pp_tabwe_entwy_cawwback_func_v1);

	/* This is the eawwiest time we have aww the dependency tabwe and the VBIOS boot state
	 * as PP_Tabwes_GetPowewPwayTabweEntwy wetwieves the VBIOS boot state
	 * if thewe is onwy one VDDCI/MCWK wevew, check if it's the same as VBIOS boot state
	 */
	if (dep_mcwk_tabwe != NUWW && dep_mcwk_tabwe->count == 1) {
		if (dep_mcwk_tabwe->entwies[0].cwk !=
				data->vbios_boot_state.mcwk_bootup_vawue)
			pw_debug("Singwe MCWK entwy VDDCI/MCWK dependency tabwe "
					"does not match VBIOS boot MCWK wevew");
		if (dep_mcwk_tabwe->entwies[0].vddci !=
				data->vbios_boot_state.vddci_bootup_vawue)
			pw_debug("Singwe VDDCI entwy VDDCI/MCWK dependency tabwe "
					"does not match VBIOS boot VDDCI wevew");
	}

	/* set DC compatibwe fwag if this state suppowts DC */
	if (!state->vawidation.disawwowOnDC)
		ps->dc_compatibwe = twue;

	if (state->cwassification.fwags & PP_StateCwassificationFwag_ACPI)
		data->acpi_pcie_gen = ps->pewfowmance_wevews[0].pcie_gen;

	ps->uvd_cwks.vcwk = state->uvd_cwocks.VCWK;
	ps->uvd_cwks.dcwk = state->uvd_cwocks.DCWK;

	if (!wesuwt) {
		uint32_t i;

		switch (state->cwassification.ui_wabew) {
		case PP_StateUIWabew_Pewfowmance:
			data->use_pcie_pewfowmance_wevews = twue;
			fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
				if (data->pcie_gen_pewfowmance.max <
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_pewfowmance.max =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_gen_pewfowmance.min >
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_pewfowmance.min =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_wane_pewfowmance.max <
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_pewfowmance.max =
							ps->pewfowmance_wevews[i].pcie_wane;
				if (data->pcie_wane_pewfowmance.min >
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_pewfowmance.min =
							ps->pewfowmance_wevews[i].pcie_wane;
			}
			bweak;
		case PP_StateUIWabew_Battewy:
			data->use_pcie_powew_saving_wevews = twue;

			fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
				if (data->pcie_gen_powew_saving.max <
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_powew_saving.max =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_gen_powew_saving.min >
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_powew_saving.min =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_wane_powew_saving.max <
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_powew_saving.max =
							ps->pewfowmance_wevews[i].pcie_wane;

				if (data->pcie_wane_powew_saving.min >
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_powew_saving.min =
							ps->pewfowmance_wevews[i].pcie_wane;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

static int smu7_get_pp_tabwe_entwy_cawwback_func_v0(stwuct pp_hwmgw *hwmgw,
					stwuct pp_hw_powew_state *powew_state,
					unsigned int index, const void *cwock_info)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_powew_state  *ps = cast_phw_smu7_powew_state(powew_state);
	const ATOM_PPWIB_CI_CWOCK_INFO *viswand_cwk_info = cwock_info;
	stwuct smu7_pewfowmance_wevew *pewfowmance_wevew;
	uint32_t engine_cwock, memowy_cwock;
	uint16_t pcie_gen_fwom_bios;

	engine_cwock = viswand_cwk_info->ucEngineCwockHigh << 16 | viswand_cwk_info->usEngineCwockWow;
	memowy_cwock = viswand_cwk_info->ucMemowyCwockHigh << 16 | viswand_cwk_info->usMemowyCwockWow;

	if (!(data->mc_micwo_code_featuwe & DISABWE_MC_WOADMICWOCODE) && memowy_cwock > data->highest_mcwk)
		data->highest_mcwk = memowy_cwock;

	PP_ASSEWT_WITH_CODE(
			(ps->pewfowmance_wevew_count < smum_get_mac_definition(hwmgw, SMU_MAX_WEVEWS_GWAPHICS)),
			"Pewfowmance wevews exceeds SMC wimit!",
			wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(
			(ps->pewfowmance_wevew_count <
					hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews),
			"Pewfowmance wevews exceeds Dwivew wimit, Skip!",
			wetuwn 0);

	pewfowmance_wevew = &(ps->pewfowmance_wevews
			[ps->pewfowmance_wevew_count++]);

	/* Pewfowmance wevews awe awwanged fwom wow to high. */
	pewfowmance_wevew->memowy_cwock = memowy_cwock;
	pewfowmance_wevew->engine_cwock = engine_cwock;

	pcie_gen_fwom_bios = viswand_cwk_info->ucPCIEGen;

	pewfowmance_wevew->pcie_gen = get_pcie_gen_suppowt(data->pcie_gen_cap, pcie_gen_fwom_bios);
	pewfowmance_wevew->pcie_wane = get_pcie_wane_suppowt(data->pcie_wane_cap, viswand_cwk_info->usPCIEWane);

	wetuwn 0;
}

static int smu7_get_pp_tabwe_entwy_v0(stwuct pp_hwmgw *hwmgw,
		unsigned wong entwy_index, stwuct pp_powew_state *state)
{
	int wesuwt;
	stwuct smu7_powew_state *ps;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe =
			hwmgw->dyn_state.vddci_dependency_on_mcwk;

	memset(&state->hawdwawe, 0x00, sizeof(stwuct pp_hw_powew_state));

	state->hawdwawe.magic = PHM_VIswands_Magic;

	ps = (stwuct smu7_powew_state *)(&state->hawdwawe);

	wesuwt = pp_tabwes_get_entwy(hwmgw, entwy_index, state,
			smu7_get_pp_tabwe_entwy_cawwback_func_v0);

	/*
	 * This is the eawwiest time we have aww the dependency tabwe
	 * and the VBIOS boot state as
	 * PP_Tabwes_GetPowewPwayTabweEntwy wetwieves the VBIOS boot
	 * state if thewe is onwy one VDDCI/MCWK wevew, check if it's
	 * the same as VBIOS boot state
	 */
	if (dep_mcwk_tabwe != NUWW && dep_mcwk_tabwe->count == 1) {
		if (dep_mcwk_tabwe->entwies[0].cwk !=
				data->vbios_boot_state.mcwk_bootup_vawue)
			pw_debug("Singwe MCWK entwy VDDCI/MCWK dependency tabwe "
					"does not match VBIOS boot MCWK wevew");
		if (dep_mcwk_tabwe->entwies[0].v !=
				data->vbios_boot_state.vddci_bootup_vawue)
			pw_debug("Singwe VDDCI entwy VDDCI/MCWK dependency tabwe "
					"does not match VBIOS boot VDDCI wevew");
	}

	/* set DC compatibwe fwag if this state suppowts DC */
	if (!state->vawidation.disawwowOnDC)
		ps->dc_compatibwe = twue;

	if (state->cwassification.fwags & PP_StateCwassificationFwag_ACPI)
		data->acpi_pcie_gen = ps->pewfowmance_wevews[0].pcie_gen;

	ps->uvd_cwks.vcwk = state->uvd_cwocks.VCWK;
	ps->uvd_cwks.dcwk = state->uvd_cwocks.DCWK;

	if (!wesuwt) {
		uint32_t i;

		switch (state->cwassification.ui_wabew) {
		case PP_StateUIWabew_Pewfowmance:
			data->use_pcie_pewfowmance_wevews = twue;

			fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
				if (data->pcie_gen_pewfowmance.max <
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_pewfowmance.max =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_gen_pewfowmance.min >
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_pewfowmance.min =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_wane_pewfowmance.max <
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_pewfowmance.max =
							ps->pewfowmance_wevews[i].pcie_wane;

				if (data->pcie_wane_pewfowmance.min >
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_pewfowmance.min =
							ps->pewfowmance_wevews[i].pcie_wane;
			}
			bweak;
		case PP_StateUIWabew_Battewy:
			data->use_pcie_powew_saving_wevews = twue;

			fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
				if (data->pcie_gen_powew_saving.max <
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_powew_saving.max =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_gen_powew_saving.min >
						ps->pewfowmance_wevews[i].pcie_gen)
					data->pcie_gen_powew_saving.min =
							ps->pewfowmance_wevews[i].pcie_gen;

				if (data->pcie_wane_powew_saving.max <
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_powew_saving.max =
							ps->pewfowmance_wevews[i].pcie_wane;

				if (data->pcie_wane_powew_saving.min >
						ps->pewfowmance_wevews[i].pcie_wane)
					data->pcie_wane_powew_saving.min =
							ps->pewfowmance_wevews[i].pcie_wane;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

static int smu7_get_pp_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
		unsigned wong entwy_index, stwuct pp_powew_state *state)
{
	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
		wetuwn smu7_get_pp_tabwe_entwy_v0(hwmgw, entwy_index, state);
	ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
		wetuwn smu7_get_pp_tabwe_entwy_v1(hwmgw, entwy_index, state);

	wetuwn 0;
}

static int smu7_get_gpu_powew(stwuct pp_hwmgw *hwmgw, u32 *quewy)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int i;
	u32 tmp = 0;

	if (!quewy)
		wetuwn -EINVAW;

	/*
	 * PPSMC_MSG_GetCuwwPkgPww is not suppowted on:
	 *  - Hawaii
	 *  - Bonaiwe
	 *  - Fiji
	 *  - Tonga
	 */
	if ((adev->asic_type != CHIP_HAWAII) &&
	    (adev->asic_type != CHIP_BONAIWE) &&
	    (adev->asic_type != CHIP_FIJI) &&
	    (adev->asic_type != CHIP_TONGA)) {
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetCuwwPkgPww, 0, &tmp);
		*quewy = tmp;

		if (tmp != 0)
			wetuwn 0;
	}

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PmStatusWogStawt, NUWW);
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
							ixSMU_PM_STATUS_95, 0);

	fow (i = 0; i < 10; i++) {
		msweep(500);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PmStatusWogSampwe, NUWW);
		tmp = cgs_wead_ind_wegistew(hwmgw->device,
						CGS_IND_WEG__SMC,
						ixSMU_PM_STATUS_95);
		if (tmp != 0)
			bweak;
	}
	*quewy = tmp;

	wetuwn 0;
}

static int smu7_wead_sensow(stwuct pp_hwmgw *hwmgw, int idx,
			    void *vawue, int *size)
{
	uint32_t scwk, mcwk, activity_pewcent;
	uint32_t offset, vaw_vid;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	/* size must be at weast 4 bytes fow aww sensows */
	if (*size < 4)
		wetuwn -EINVAW;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_API_GetScwkFwequency, &scwk);
		*((uint32_t *)vawue) = scwk;
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_API_GetMcwkFwequency, &mcwk);
		*((uint32_t *)vawue) = mcwk;
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		offset = data->soft_wegs_stawt + smum_get_offsetof(hwmgw,
								SMU_SoftWegistews,
								(idx == AMDGPU_PP_SENSOW_GPU_WOAD) ?
								AvewageGwaphicsActivity :
								AvewageMemowyActivity);

		activity_pewcent = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset);
		activity_pewcent += 0x80;
		activity_pewcent >>= 8;
		*((uint32_t *)vawue) = activity_pewcent > 100 ? 100 : activity_pewcent;
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GPU_TEMP:
		*((uint32_t *)vawue) = smu7_thewmaw_get_tempewatuwe(hwmgw);
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_UVD_POWEW:
		*((uint32_t *)vawue) = data->uvd_powew_gated ? 0 : 1;
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_VCE_POWEW:
		*((uint32_t *)vawue) = data->vce_powew_gated ? 0 : 1;
		*size = 4;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		if ((adev->asic_type != CHIP_HAWAII) &&
		    (adev->asic_type != CHIP_BONAIWE) &&
		    (adev->asic_type != CHIP_FIJI) &&
		    (adev->asic_type != CHIP_TONGA))
			wetuwn smu7_get_gpu_powew(hwmgw, (uint32_t *)vawue);
		ewse
			wetuwn -EOPNOTSUPP;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		if ((adev->asic_type != CHIP_HAWAII) &&
		    (adev->asic_type != CHIP_BONAIWE) &&
		    (adev->asic_type != CHIP_FIJI) &&
		    (adev->asic_type != CHIP_TONGA))
			wetuwn -EOPNOTSUPP;
		ewse
			wetuwn smu7_get_gpu_powew(hwmgw, (uint32_t *)vawue);
	case AMDGPU_PP_SENSOW_VDDGFX:
		if ((data->vw_config & VWCONF_VDDGFX_MASK) ==
		    (VW_SVI2_PWANE_2 << VWCONF_VDDGFX_SHIFT))
			vaw_vid = PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
					CGS_IND_WEG__SMC, PWW_SVI2_STATUS, PWANE2_VID);
		ewse
			vaw_vid = PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
					CGS_IND_WEG__SMC, PWW_SVI2_STATUS, PWANE1_VID);

		*((uint32_t *)vawue) = (uint32_t)convewt_to_vddc(vaw_vid);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smu7_find_dpm_states_cwocks_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw, const void *input)
{
	const stwuct phm_set_powew_state_input *states =
			(const stwuct phm_set_powew_state_input *)input;
	const stwuct smu7_powew_state *smu7_ps =
			cast_const_phw_smu7_powew_state(states->pnew_state);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *scwk_tabwe = &(data->dpm_tabwe.scwk_tabwe);
	uint32_t scwk = smu7_ps->pewfowmance_wevews
			[smu7_ps->pewfowmance_wevew_count - 1].engine_cwock;
	stwuct smu7_singwe_dpm_tabwe *mcwk_tabwe = &(data->dpm_tabwe.mcwk_tabwe);
	uint32_t mcwk = smu7_ps->pewfowmance_wevews
			[smu7_ps->pewfowmance_wevew_count - 1].memowy_cwock;
	stwuct PP_Cwocks min_cwocks = {0};
	uint32_t i;

	fow (i = 0; i < scwk_tabwe->count; i++) {
		if (scwk == scwk_tabwe->dpm_wevews[i].vawue)
			bweak;
	}

	if (i >= scwk_tabwe->count) {
		if (scwk > scwk_tabwe->dpm_wevews[i-1].vawue) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_SCWK;
			scwk_tabwe->dpm_wevews[i-1].vawue = scwk;
		}
	} ewse {
	/* TODO: Check SCWK in DAW's minimum cwocks
	 * in case DeepSweep dividew update is wequiwed.
	 */
		if (data->dispway_timing.min_cwock_in_sw != min_cwocks.engineCwockInSW &&
			(min_cwocks.engineCwockInSW >= SMU7_MINIMUM_ENGINE_CWOCK ||
				data->dispway_timing.min_cwock_in_sw >= SMU7_MINIMUM_ENGINE_CWOCK))
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_UPDATE_SCWK;
	}

	fow (i = 0; i < mcwk_tabwe->count; i++) {
		if (mcwk == mcwk_tabwe->dpm_wevews[i].vawue)
			bweak;
	}

	if (i >= mcwk_tabwe->count) {
		if (mcwk > mcwk_tabwe->dpm_wevews[i-1].vawue) {
			data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_MCWK;
			mcwk_tabwe->dpm_wevews[i-1].vawue = mcwk;
		}
	}

	if (data->dispway_timing.num_existing_dispways != hwmgw->dispway_config->num_dispway)
		data->need_update_smu7_dpm_tabwe |= DPMTABWE_UPDATE_MCWK;

	wetuwn 0;
}

static uint16_t smu7_get_maximum_wink_speed(stwuct pp_hwmgw *hwmgw,
		const stwuct smu7_powew_state *smu7_ps)
{
	uint32_t i;
	uint32_t scwk, max_scwk = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;

	fow (i = 0; i < smu7_ps->pewfowmance_wevew_count; i++) {
		scwk = smu7_ps->pewfowmance_wevews[i].engine_cwock;
		if (max_scwk < scwk)
			max_scwk = scwk;
	}

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
		if (dpm_tabwe->scwk_tabwe.dpm_wevews[i].vawue == max_scwk)
			wetuwn (uint16_t) ((i >= dpm_tabwe->pcie_speed_tabwe.count) ?
					dpm_tabwe->pcie_speed_tabwe.dpm_wevews
					[dpm_tabwe->pcie_speed_tabwe.count - 1].vawue :
					dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].vawue);
	}

	wetuwn 0;
}

static int smu7_wequest_wink_speed_change_befowe_state_change(
		stwuct pp_hwmgw *hwmgw, const void *input)
{
	const stwuct phm_set_powew_state_input *states =
			(const stwuct phm_set_powew_state_input *)input;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	const stwuct smu7_powew_state *smu7_nps =
			cast_const_phw_smu7_powew_state(states->pnew_state);
	const stwuct smu7_powew_state *powawis10_cps =
			cast_const_phw_smu7_powew_state(states->pcuwwent_state);

	uint16_t tawget_wink_speed = smu7_get_maximum_wink_speed(hwmgw, smu7_nps);
	uint16_t cuwwent_wink_speed;

	if (data->fowce_pcie_gen == PP_PCIEGenInvawid)
		cuwwent_wink_speed = smu7_get_maximum_wink_speed(hwmgw, powawis10_cps);
	ewse
		cuwwent_wink_speed = data->fowce_pcie_gen;

	data->fowce_pcie_gen = PP_PCIEGenInvawid;
	data->pspp_notify_wequiwed = fawse;

	if (tawget_wink_speed > cuwwent_wink_speed) {
		switch (tawget_wink_speed) {
#ifdef CONFIG_ACPI
		case PP_PCIEGen3:
			if (0 == amdgpu_acpi_pcie_pewfowmance_wequest(hwmgw->adev, PCIE_PEWF_WEQ_GEN3, fawse))
				bweak;
			data->fowce_pcie_gen = PP_PCIEGen2;
			if (cuwwent_wink_speed == PP_PCIEGen2)
				bweak;
			fawwthwough;
		case PP_PCIEGen2:
			if (0 == amdgpu_acpi_pcie_pewfowmance_wequest(hwmgw->adev, PCIE_PEWF_WEQ_GEN2, fawse))
				bweak;
			fawwthwough;
#endif
		defauwt:
			data->fowce_pcie_gen = smu7_get_cuwwent_pcie_speed(hwmgw);
			bweak;
		}
	} ewse {
		if (tawget_wink_speed < cuwwent_wink_speed)
			data->pspp_notify_wequiwed = twue;
	}

	wetuwn 0;
}

static int smu7_fweeze_scwk_mcwk_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (0 == data->need_update_smu7_dpm_tabwe)
		wetuwn 0;

	if ((0 == data->scwk_dpm_key_disabwed) &&
		(data->need_update_smu7_dpm_tabwe &
			(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_UPDATE_SCWK))) {
		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to fweeze SCWK DPM when DPM is disabwed",
				);
		PP_ASSEWT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_SCWKDPM_FweezeWevew,
				NUWW),
				"Faiwed to fweeze SCWK DPM duwing FweezeScwkMcwkDPM Function!",
				wetuwn -EINVAW);
	}

	if ((0 == data->mcwk_dpm_key_disabwed) &&
		!data->mcwk_ignowe_signaw &&
		(data->need_update_smu7_dpm_tabwe &
		 DPMTABWE_OD_UPDATE_MCWK)) {
		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to fweeze MCWK DPM when DPM is disabwed",
				);
		PP_ASSEWT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_MCWKDPM_FweezeWevew,
				NUWW),
				"Faiwed to fweeze MCWK DPM duwing FweezeScwkMcwkDPM Function!",
				wetuwn -EINVAW);
	}

	wetuwn 0;
}

static int smu7_popuwate_and_upwoad_scwk_mcwk_dpm_wevews(
		stwuct pp_hwmgw *hwmgw, const void *input)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	uint32_t count;
	stwuct smu7_odn_dpm_tabwe *odn_tabwe = &(data->odn_dpm_tabwe);
	stwuct phm_odn_cwock_wevews *odn_scwk_tabwe = &(odn_tabwe->odn_cowe_cwock_dpm_wevews);
	stwuct phm_odn_cwock_wevews *odn_mcwk_tabwe = &(odn_tabwe->odn_memowy_cwock_dpm_wevews);

	if (0 == data->need_update_smu7_dpm_tabwe)
		wetuwn 0;

	if (hwmgw->od_enabwed && data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_SCWK) {
		fow (count = 0; count < dpm_tabwe->scwk_tabwe.count; count++) {
			dpm_tabwe->scwk_tabwe.dpm_wevews[count].enabwed = odn_scwk_tabwe->entwies[count].enabwed;
			dpm_tabwe->scwk_tabwe.dpm_wevews[count].vawue = odn_scwk_tabwe->entwies[count].cwock;
		}
	}

	if (hwmgw->od_enabwed && data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_MCWK) {
		fow (count = 0; count < dpm_tabwe->mcwk_tabwe.count; count++) {
			dpm_tabwe->mcwk_tabwe.dpm_wevews[count].enabwed = odn_mcwk_tabwe->entwies[count].enabwed;
			dpm_tabwe->mcwk_tabwe.dpm_wevews[count].vawue = odn_mcwk_tabwe->entwies[count].cwock;
		}
	}

	if (data->need_update_smu7_dpm_tabwe &
			(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_UPDATE_SCWK)) {
		wesuwt = smum_popuwate_aww_gwaphic_wevews(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to popuwate SCWK duwing PopuwateNewDPMCwocksStates Function!",
				wetuwn wesuwt);
	}

	if (data->need_update_smu7_dpm_tabwe &
			(DPMTABWE_OD_UPDATE_MCWK | DPMTABWE_UPDATE_MCWK)) {
		/*popuwate MCWK dpm tabwe to SMU7 */
		wesuwt = smum_popuwate_aww_memowy_wevews(hwmgw);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Faiwed to popuwate MCWK duwing PopuwateNewDPMCwocksStates Function!",
				wetuwn wesuwt);
	}

	wetuwn wesuwt;
}

static int smu7_twim_singwe_dpm_states(stwuct pp_hwmgw *hwmgw,
			  stwuct smu7_singwe_dpm_tabwe *dpm_tabwe,
			uint32_t wow_wimit, uint32_t high_wimit)
{
	uint32_t i;

	/* fowce the twim if mcwk_switching is disabwed to pwevent fwickew */
	boow fowce_twim = (wow_wimit == high_wimit);
	fow (i = 0; i < dpm_tabwe->count; i++) {
	/*skip the twim if od is enabwed*/
		if ((!hwmgw->od_enabwed || fowce_twim)
			&& (dpm_tabwe->dpm_wevews[i].vawue < wow_wimit
			|| dpm_tabwe->dpm_wevews[i].vawue > high_wimit))
			dpm_tabwe->dpm_wevews[i].enabwed = fawse;
		ewse
			dpm_tabwe->dpm_wevews[i].enabwed = twue;
	}

	wetuwn 0;
}

static int smu7_twim_dpm_states(stwuct pp_hwmgw *hwmgw,
		const stwuct smu7_powew_state *smu7_ps)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t high_wimit_count;

	PP_ASSEWT_WITH_CODE((smu7_ps->pewfowmance_wevew_count >= 1),
			"powew state did not have any pewfowmance wevew",
			wetuwn -EINVAW);

	high_wimit_count = (1 == smu7_ps->pewfowmance_wevew_count) ? 0 : 1;

	smu7_twim_singwe_dpm_states(hwmgw,
			&(data->dpm_tabwe.scwk_tabwe),
			smu7_ps->pewfowmance_wevews[0].engine_cwock,
			smu7_ps->pewfowmance_wevews[high_wimit_count].engine_cwock);

	smu7_twim_singwe_dpm_states(hwmgw,
			&(data->dpm_tabwe.mcwk_tabwe),
			smu7_ps->pewfowmance_wevews[0].memowy_cwock,
			smu7_ps->pewfowmance_wevews[high_wimit_count].memowy_cwock);

	wetuwn 0;
}

static int smu7_genewate_dpm_wevew_enabwe_mask(
		stwuct pp_hwmgw *hwmgw, const void *input)
{
	int wesuwt = 0;
	const stwuct phm_set_powew_state_input *states =
			(const stwuct phm_set_powew_state_input *)input;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	const stwuct smu7_powew_state *smu7_ps =
			cast_const_phw_smu7_powew_state(states->pnew_state);


	wesuwt = smu7_twim_dpm_states(hwmgw, smu7_ps);
	if (wesuwt)
		wetuwn wesuwt;

	data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&data->dpm_tabwe.scwk_tabwe);
	data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&data->dpm_tabwe.mcwk_tabwe);
	data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&data->dpm_tabwe.pcie_speed_tabwe);

	wetuwn 0;
}

static int smu7_unfweeze_scwk_mcwk_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (0 == data->need_update_smu7_dpm_tabwe)
		wetuwn 0;

	if ((0 == data->scwk_dpm_key_disabwed) &&
		(data->need_update_smu7_dpm_tabwe &
		(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_UPDATE_SCWK))) {

		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to Unfweeze SCWK DPM when DPM is disabwed",
				);
		PP_ASSEWT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_SCWKDPM_UnfweezeWevew,
				NUWW),
			"Faiwed to unfweeze SCWK DPM duwing UnFweezeScwkMcwkDPM Function!",
			wetuwn -EINVAW);
	}

	if ((0 == data->mcwk_dpm_key_disabwed) &&
		!data->mcwk_ignowe_signaw &&
		(data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_MCWK)) {

		PP_ASSEWT_WITH_CODE(twue == smum_is_dpm_wunning(hwmgw),
				"Twying to Unfweeze MCWK DPM when DPM is disabwed",
				);
		PP_ASSEWT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_MCWKDPM_UnfweezeWevew,
				NUWW),
		    "Faiwed to unfweeze MCWK DPM duwing UnFweezeScwkMcwkDPM Function!",
		    wetuwn -EINVAW);
	}

	data->need_update_smu7_dpm_tabwe &= DPMTABWE_OD_UPDATE_VDDC;

	wetuwn 0;
}

static int smu7_notify_wink_speed_change_aftew_state_change(
		stwuct pp_hwmgw *hwmgw, const void *input)
{
	const stwuct phm_set_powew_state_input *states =
			(const stwuct phm_set_powew_state_input *)input;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	const stwuct smu7_powew_state *smu7_ps =
			cast_const_phw_smu7_powew_state(states->pnew_state);
	uint16_t tawget_wink_speed = smu7_get_maximum_wink_speed(hwmgw, smu7_ps);
	uint8_t  wequest;

	if (data->pspp_notify_wequiwed) {
		if (tawget_wink_speed == PP_PCIEGen3)
			wequest = PCIE_PEWF_WEQ_GEN3;
		ewse if (tawget_wink_speed == PP_PCIEGen2)
			wequest = PCIE_PEWF_WEQ_GEN2;
		ewse
			wequest = PCIE_PEWF_WEQ_GEN1;

		if (wequest == PCIE_PEWF_WEQ_GEN1 &&
				smu7_get_cuwwent_pcie_speed(hwmgw) > 0)
			wetuwn 0;

#ifdef CONFIG_ACPI
		if (amdgpu_acpi_pcie_pewfowmance_wequest(hwmgw->adev, wequest, fawse)) {
			if (PP_PCIEGen2 == tawget_wink_speed)
				pw_info("PSPP wequest to switch to Gen2 fwom Gen3 Faiwed!");
			ewse
				pw_info("PSPP wequest to switch to Gen1 fwom Gen2 Faiwed!");
		}
#endif
	}

	wetuwn 0;
}

static int smu7_notify_no_dispway(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (smum_send_msg_to_smc(hwmgw, (PPSMC_Msg)PPSMC_NoDispway, NUWW) == 0) ?  0 : -EINVAW;
}

static int smu7_notify_has_dispway(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (hwmgw->featuwe_mask & PP_VBI_TIME_SUPPOWT_MASK) {
		if (hwmgw->chip_id == CHIP_VEGAM)
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					(PPSMC_Msg)PPSMC_MSG_SetVBITimeout_VEGAM, data->fwame_time_x2,
					NUWW);
		ewse
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					(PPSMC_Msg)PPSMC_MSG_SetVBITimeout, data->fwame_time_x2,
					NUWW);
		data->wast_sent_vbi_timeout = data->fwame_time_x2;
	}

	wetuwn (smum_send_msg_to_smc(hwmgw, (PPSMC_Msg)PPSMC_HasDispway, NUWW) == 0) ?  0 : -EINVAW;
}

static int smu7_notify_smc_dispway(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wesuwt = 0;

	if (data->mcwk_ignowe_signaw)
		wesuwt = smu7_notify_no_dispway(hwmgw);
	ewse
		wesuwt = smu7_notify_has_dispway(hwmgw);

	wetuwn wesuwt;
}

static int smu7_set_powew_state_tasks(stwuct pp_hwmgw *hwmgw, const void *input)
{
	int tmp_wesuwt, wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	tmp_wesuwt = smu7_find_dpm_states_cwocks_in_dpm_tabwe(hwmgw, input);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to find DPM states cwocks in DPM tabwe!",
			wesuwt = tmp_wesuwt);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PCIEPewfowmanceWequest)) {
		tmp_wesuwt =
			smu7_wequest_wink_speed_change_befowe_state_change(hwmgw, input);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to wequest wink speed change befowe state change!",
				wesuwt = tmp_wesuwt);
	}

	tmp_wesuwt = smu7_fweeze_scwk_mcwk_dpm(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to fweeze SCWK MCWK DPM!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_popuwate_and_upwoad_scwk_mcwk_dpm_wevews(hwmgw, input);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to popuwate and upwoad SCWK MCWK DPM wevews!",
			wesuwt = tmp_wesuwt);

	/*
	 * If a custom pp tabwe is woaded, set DPMTABWE_OD_UPDATE_VDDC fwag.
	 * That effectivewy disabwes AVFS featuwe.
	 */
	if (hwmgw->hawdcode_pp_tabwe != NUWW)
		data->need_update_smu7_dpm_tabwe |= DPMTABWE_OD_UPDATE_VDDC;

	tmp_wesuwt = smu7_update_avfs(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to update avfs vowtages!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_genewate_dpm_wevew_enabwe_mask(hwmgw, input);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to genewate DPM wevew enabwed mask!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smum_update_scwk_thweshowd(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to update SCWK thweshowd!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_unfweeze_scwk_mcwk_dpm(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to unfweeze SCWK MCWK DPM!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_upwoad_dpm_wevew_enabwe_mask(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to upwoad DPM wevew enabwed mask!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_notify_smc_dispway(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to notify smc dispway settings!",
			wesuwt = tmp_wesuwt);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PCIEPewfowmanceWequest)) {
		tmp_wesuwt =
			smu7_notify_wink_speed_change_aftew_state_change(hwmgw, input);
		PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
				"Faiwed to notify wink speed change aftew state change!",
				wesuwt = tmp_wesuwt);
	}
	data->appwy_optimized_settings = fawse;
	wetuwn wesuwt;
}

static int smu7_set_max_fan_pwm_output(stwuct pp_hwmgw *hwmgw, uint16_t us_max_fan_pwm)
{
	hwmgw->thewmaw_contwowwew.
	advanceFanContwowPawametews.usMaxFanPWM = us_max_fan_pwm;

	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetFanPwmMax, us_max_fan_pwm,
			NUWW);
}

static int
smu7_notify_smc_dispway_config_aftew_ps_adjustment(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

/**
 * smu7_pwogwam_dispway_gap - Pwogwams the dispway gap
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways OK
 */
static int smu7_pwogwam_dispway_gap(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t dispway_gap = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_DISPWAY_GAP_CNTW);
	uint32_t dispway_gap2;
	uint32_t pwe_vbi_time_in_us;
	uint32_t fwame_time_in_us;
	uint32_t wef_cwock, wefwesh_wate;

	dispway_gap = PHM_SET_FIEWD(dispway_gap, CG_DISPWAY_GAP_CNTW, DISP_GAP, (hwmgw->dispway_config->num_dispway > 0) ? DISPWAY_GAP_VBWANK_OW_WM : DISPWAY_GAP_IGNOWE);
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_DISPWAY_GAP_CNTW, dispway_gap);

	wef_cwock =  amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);
	wefwesh_wate = hwmgw->dispway_config->vwefwesh;

	if (0 == wefwesh_wate)
		wefwesh_wate = 60;

	fwame_time_in_us = 1000000 / wefwesh_wate;

	pwe_vbi_time_in_us = fwame_time_in_us - 200 - hwmgw->dispway_config->min_vbwank_time;

	data->fwame_time_x2 = fwame_time_in_us * 2 / 100;

	if (data->fwame_time_x2 < 280) {
		pw_debug("%s: enfowce minimaw VBITimeout: %d -> 280\n", __func__, data->fwame_time_x2);
		data->fwame_time_x2 = 280;
	}

	dispway_gap2 = pwe_vbi_time_in_us * (wef_cwock / 100);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_DISPWAY_GAP_CNTW2, dispway_gap2);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			data->soft_wegs_stawt + smum_get_offsetof(hwmgw,
							SMU_SoftWegistews,
							PweVBwankGap), 0x64);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			data->soft_wegs_stawt + smum_get_offsetof(hwmgw,
							SMU_SoftWegistews,
							VBwankTimeout),
					(fwame_time_in_us - pwe_vbi_time_in_us));

	wetuwn 0;
}

static int smu7_dispway_configuwation_changed_task(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu7_pwogwam_dispway_gap(hwmgw);
}

/**
 * smu7_set_max_fan_wpm_output - Set maximum tawget opewating fan output WPM
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @us_max_fan_wpm:  max opewating fan WPM vawue.
 * Wetuwn:   The wesponse that came fwom the SMC.
 */
static int smu7_set_max_fan_wpm_output(stwuct pp_hwmgw *hwmgw, uint16_t us_max_fan_wpm)
{
	hwmgw->thewmaw_contwowwew.
	advanceFanContwowPawametews.usMaxFanWPM = us_max_fan_wpm;

	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetFanWpmMax, us_max_fan_wpm,
			NUWW);
}

static const stwuct amdgpu_iwq_swc_funcs smu7_iwq_funcs = {
	.pwocess = phm_iwq_pwocess,
};

static int smu7_wegistew_iwq_handwews(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_iwq_swc *souwce =
		kzawwoc(sizeof(stwuct amdgpu_iwq_swc), GFP_KEWNEW);

	if (!souwce)
		wetuwn -ENOMEM;

	souwce->funcs = &smu7_iwq_funcs;

	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			AMDGPU_IWQ_CWIENTID_WEGACY,
			VISWANDS30_IV_SWCID_CG_TSS_THEWMAW_WOW_TO_HIGH,
			souwce);
	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			AMDGPU_IWQ_CWIENTID_WEGACY,
			VISWANDS30_IV_SWCID_CG_TSS_THEWMAW_HIGH_TO_WOW,
			souwce);

	/* Wegistew CTF(GPIO_19) intewwupt */
	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			AMDGPU_IWQ_CWIENTID_WEGACY,
			VISWANDS30_IV_SWCID_GPIO_19,
			souwce);

	wetuwn 0;
}

static boow
smu7_check_smc_update_wequiwed_fow_dispway_configuwation(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	boow is_update_wequiwed = fawse;

	if (data->dispway_timing.num_existing_dispways != hwmgw->dispway_config->num_dispway)
		is_update_wequiwed = twue;

	if (data->dispway_timing.vwefwesh != hwmgw->dispway_config->vwefwesh)
		is_update_wequiwed = twue;

	if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
	    hwmgw->chip_id <= CHIP_VEGAM &&
	    data->wast_sent_vbi_timeout != data->fwame_time_x2)
		is_update_wequiwed = twue;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_ScwkDeepSweep)) {
		if (data->dispway_timing.min_cwock_in_sw != hwmgw->dispway_config->min_cowe_set_cwock_in_sw &&
			(data->dispway_timing.min_cwock_in_sw >= SMU7_MINIMUM_ENGINE_CWOCK ||
			hwmgw->dispway_config->min_cowe_set_cwock_in_sw >= SMU7_MINIMUM_ENGINE_CWOCK))
			is_update_wequiwed = twue;
	}
	wetuwn is_update_wequiwed;
}

static inwine boow smu7_awe_powew_wevews_equaw(const stwuct smu7_pewfowmance_wevew *pw1,
							   const stwuct smu7_pewfowmance_wevew *pw2)
{
	wetuwn ((pw1->memowy_cwock == pw2->memowy_cwock) &&
		  (pw1->engine_cwock == pw2->engine_cwock) &&
		  (pw1->pcie_gen == pw2->pcie_gen) &&
		  (pw1->pcie_wane == pw2->pcie_wane));
}

static int smu7_check_states_equaw(stwuct pp_hwmgw *hwmgw,
		const stwuct pp_hw_powew_state *pstate1,
		const stwuct pp_hw_powew_state *pstate2, boow *equaw)
{
	const stwuct smu7_powew_state *psa;
	const stwuct smu7_powew_state *psb;
	int i;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (pstate1 == NUWW || pstate2 == NUWW || equaw == NUWW)
		wetuwn -EINVAW;

	psa = cast_const_phw_smu7_powew_state(pstate1);
	psb = cast_const_phw_smu7_powew_state(pstate2);
	/* If the two states don't even have the same numbew of pewfowmance wevews they cannot be the same state. */
	if (psa->pewfowmance_wevew_count != psb->pewfowmance_wevew_count) {
		*equaw = fawse;
		wetuwn 0;
	}

	fow (i = 0; i < psa->pewfowmance_wevew_count; i++) {
		if (!smu7_awe_powew_wevews_equaw(&(psa->pewfowmance_wevews[i]), &(psb->pewfowmance_wevews[i]))) {
			/* If we have found even one pewfowmance wevew paiw that is diffewent the states awe diffewent. */
			*equaw = fawse;
			wetuwn 0;
		}
	}

	/* If aww pewfowmance wevews awe the same twy to use the UVD cwocks to bweak the tie.*/
	*equaw = ((psa->uvd_cwks.vcwk == psb->uvd_cwks.vcwk) && (psa->uvd_cwks.dcwk == psb->uvd_cwks.dcwk));
	*equaw &= ((psa->vce_cwks.evcwk == psb->vce_cwks.evcwk) && (psa->vce_cwks.eccwk == psb->vce_cwks.eccwk));
	*equaw &= (psa->scwk_thweshowd == psb->scwk_thweshowd);
	/* Fow OD caww, set vawue based on fwag */
	*equaw &= !(data->need_update_smu7_dpm_tabwe & (DPMTABWE_OD_UPDATE_SCWK |
							DPMTABWE_OD_UPDATE_MCWK |
							DPMTABWE_OD_UPDATE_VDDC));

	wetuwn 0;
}

static int smu7_check_mc_fiwmwawe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t tmp;

	/* Wead MC indiwect wegistew offset 0x9F bits [3:0] to see
	 * if VBIOS has awweady woaded a fuww vewsion of MC ucode
	 * ow not.
	 */

	smu7_get_mc_micwocode_vewsion(hwmgw);

	data->need_wong_memowy_twaining = fawse;

	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_IO_DEBUG_INDEX,
							ixMC_IO_DEBUG_UP_13);
	tmp = cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_IO_DEBUG_DATA);

	if (tmp & (1 << 23)) {
		data->mem_watency_high = MEM_WATENCY_HIGH;
		data->mem_watency_wow = MEM_WATENCY_WOW;
		if ((hwmgw->chip_id == CHIP_POWAWIS10) ||
		    (hwmgw->chip_id == CHIP_POWAWIS11) ||
		    (hwmgw->chip_id == CHIP_POWAWIS12))
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweFFC, NUWW);
	} ewse {
		data->mem_watency_high = 330;
		data->mem_watency_wow = 330;
		if ((hwmgw->chip_id == CHIP_POWAWIS10) ||
		    (hwmgw->chip_id == CHIP_POWAWIS11) ||
		    (hwmgw->chip_id == CHIP_POWAWIS12))
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DisabweFFC, NUWW);
	}

	wetuwn 0;
}

static int smu7_wead_cwock_wegistews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->cwock_wegistews.vCG_SPWW_FUNC_CNTW         =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_FUNC_CNTW);
	data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_2       =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_FUNC_CNTW_2);
	data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3       =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_FUNC_CNTW_3);
	data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4       =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_FUNC_CNTW_4);
	data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM   =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_SPWEAD_SPECTWUM);
	data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2 =
		cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixCG_SPWW_SPWEAD_SPECTWUM_2);
	data->cwock_wegistews.vDWW_CNTW                  =
		cgs_wead_wegistew(hwmgw->device, mmDWW_CNTW);
	data->cwock_wegistews.vMCWK_PWWMGT_CNTW          =
		cgs_wead_wegistew(hwmgw->device, mmMCWK_PWWMGT_CNTW);
	data->cwock_wegistews.vMPWW_AD_FUNC_CNTW         =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_AD_FUNC_CNTW);
	data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW         =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_DQ_FUNC_CNTW);
	data->cwock_wegistews.vMPWW_FUNC_CNTW            =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_FUNC_CNTW);
	data->cwock_wegistews.vMPWW_FUNC_CNTW_1          =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_FUNC_CNTW_1);
	data->cwock_wegistews.vMPWW_FUNC_CNTW_2          =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_FUNC_CNTW_2);
	data->cwock_wegistews.vMPWW_SS1                  =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_SS1);
	data->cwock_wegistews.vMPWW_SS2                  =
		cgs_wead_wegistew(hwmgw->device, mmMPWW_SS2);
	wetuwn 0;

}

/**
 * smu7_get_memowy_type - Find out if memowy is GDDW5.
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_get_memowy_type(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	data->is_memowy_gddw5 = (adev->gmc.vwam_type == AMDGPU_VWAM_TYPE_GDDW5);

	wetuwn 0;
}

/**
 * smu7_enabwe_acpi_powew_management - Enabwes Dynamic Powew Management by SMC
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_enabwe_acpi_powew_management(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			GENEWAW_PWWMGT, STATIC_PM_EN, 1);

	wetuwn 0;
}

/**
 * smu7_init_powew_gate_state - Initiawize PowewGating States fow diffewent engines
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   awways 0
 */
static int smu7_init_powew_gate_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->uvd_powew_gated = fawse;
	data->vce_powew_gated = fawse;

	wetuwn 0;
}

static int smu7_init_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->wow_scwk_intewwupt_thweshowd = 0;
	wetuwn 0;
}

static int smu7_setup_asic_task(stwuct pp_hwmgw *hwmgw)
{
	int tmp_wesuwt, wesuwt = 0;

	smu7_check_mc_fiwmwawe(hwmgw);

	tmp_wesuwt = smu7_wead_cwock_wegistews(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to wead cwock wegistews!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_get_memowy_type(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to get memowy type!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_enabwe_acpi_powew_management(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to enabwe ACPI powew management!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_init_powew_gate_state(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to init powew gate state!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_get_mc_micwocode_vewsion(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to get MC micwocode vewsion!", wesuwt = tmp_wesuwt);

	tmp_wesuwt = smu7_init_scwk_thweshowd(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == tmp_wesuwt),
			"Faiwed to init scwk thweshowd!", wesuwt = tmp_wesuwt);

	wetuwn wesuwt;
}

static int smu7_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (mask == 0)
		wetuwn -EINVAW;

	switch (type) {
	case PP_SCWK:
		if (!data->scwk_dpm_key_disabwed)
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SCWKDPM_SetEnabwedMask,
					data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask & mask,
					NUWW);
		bweak;
	case PP_MCWK:
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_MCWKDPM_SetEnabwedMask,
					data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask & mask,
					NUWW);
		bweak;
	case PP_PCIE:
	{
		uint32_t tmp = mask & data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask;

		if (!data->pcie_dpm_key_disabwed) {
			if (fws(tmp) != ffs(tmp))
				smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PCIeDPM_UnFowceWevew,
						NUWW);
			ewse
				smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_PCIeDPM_FowceWevew,
					fws(tmp) - 1,
					NUWW);
		}
		bweak;
	}
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int smu7_pwint_cwock_wevews(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, chaw *buf)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *scwk_tabwe = &(data->dpm_tabwe.scwk_tabwe);
	stwuct smu7_singwe_dpm_tabwe *mcwk_tabwe = &(data->dpm_tabwe.mcwk_tabwe);
	stwuct smu7_singwe_dpm_tabwe *pcie_tabwe = &(data->dpm_tabwe.pcie_speed_tabwe);
	stwuct smu7_odn_dpm_tabwe *odn_tabwe = &(data->odn_dpm_tabwe);
	stwuct phm_odn_cwock_wevews *odn_scwk_tabwe = &(odn_tabwe->odn_cowe_cwock_dpm_wevews);
	stwuct phm_odn_cwock_wevews *odn_mcwk_tabwe = &(odn_tabwe->odn_memowy_cwock_dpm_wevews);
	int size = 0;
	uint32_t i, now, cwock, pcie_speed;

	switch (type) {
	case PP_SCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_API_GetScwkFwequency, &cwock);

		fow (i = 0; i < scwk_tabwe->count; i++) {
			if (cwock > scwk_tabwe->dpm_wevews[i].vawue)
				continue;
			bweak;
		}
		now = i;

		fow (i = 0; i < scwk_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
					i, scwk_tabwe->dpm_wevews[i].vawue / 100,
					(i == now) ? "*" : "");
		bweak;
	case PP_MCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_API_GetMcwkFwequency, &cwock);

		fow (i = 0; i < mcwk_tabwe->count; i++) {
			if (cwock > mcwk_tabwe->dpm_wevews[i].vawue)
				continue;
			bweak;
		}
		now = i;

		fow (i = 0; i < mcwk_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
					i, mcwk_tabwe->dpm_wevews[i].vawue / 100,
					(i == now) ? "*" : "");
		bweak;
	case PP_PCIE:
		pcie_speed = smu7_get_cuwwent_pcie_speed(hwmgw);
		fow (i = 0; i < pcie_tabwe->count; i++) {
			if (pcie_speed != pcie_tabwe->dpm_wevews[i].vawue)
				continue;
			bweak;
		}
		now = i;

		fow (i = 0; i < pcie_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %s %s\n", i,
					(pcie_tabwe->dpm_wevews[i].vawue == 0) ? "2.5GT/s, x8" :
					(pcie_tabwe->dpm_wevews[i].vawue == 1) ? "5.0GT/s, x16" :
					(pcie_tabwe->dpm_wevews[i].vawue == 2) ? "8.0GT/s, x16" : "",
					(i == now) ? "*" : "");
		bweak;
	case OD_SCWK:
		if (hwmgw->od_enabwed) {
			size += spwintf(buf + size, "%s:\n", "OD_SCWK");
			fow (i = 0; i < odn_scwk_tabwe->num_of_pw; i++)
				size += spwintf(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_scwk_tabwe->entwies[i].cwock/100,
					odn_scwk_tabwe->entwies[i].vddc);
		}
		bweak;
	case OD_MCWK:
		if (hwmgw->od_enabwed) {
			size += spwintf(buf + size, "%s:\n", "OD_MCWK");
			fow (i = 0; i < odn_mcwk_tabwe->num_of_pw; i++)
				size += spwintf(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_mcwk_tabwe->entwies[i].cwock/100,
					odn_mcwk_tabwe->entwies[i].vddc);
		}
		bweak;
	case OD_WANGE:
		if (hwmgw->od_enabwed) {
			size += spwintf(buf + size, "%s:\n", "OD_WANGE");
			size += spwintf(buf + size, "SCWK: %7uMHz %10uMHz\n",
				data->gowden_dpm_tabwe.scwk_tabwe.dpm_wevews[0].vawue/100,
				hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock/100);
			size += spwintf(buf + size, "MCWK: %7uMHz %10uMHz\n",
				data->gowden_dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue/100,
				hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock/100);
			size += spwintf(buf + size, "VDDC: %7umV %11umV\n",
				data->odn_dpm_tabwe.min_vddc,
				data->odn_dpm_tabwe.max_vddc);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn size;
}

static void smu7_set_fan_contwow_mode(stwuct pp_hwmgw *hwmgw, uint32_t mode)
{
	switch (mode) {
	case AMD_FAN_CTWW_NONE:
		smu7_fan_ctww_set_fan_speed_pwm(hwmgw, 255);
		bweak;
	case AMD_FAN_CTWW_MANUAW:
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MicwocodeFanContwow))
			smu7_fan_ctww_stop_smc_fan_contwow(hwmgw);
		bweak;
	case AMD_FAN_CTWW_AUTO:
		if (!smu7_fan_ctww_set_static_mode(hwmgw, mode))
			smu7_fan_ctww_stawt_smc_fan_contwow(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
}

static uint32_t smu7_get_fan_contwow_mode(stwuct pp_hwmgw *hwmgw)
{
	wetuwn hwmgw->fan_ctww_enabwed ? AMD_FAN_CTWW_AUTO : AMD_FAN_CTWW_MANUAW;
}

static int smu7_get_scwk_od(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *scwk_tabwe = &(data->dpm_tabwe.scwk_tabwe);
	stwuct smu7_singwe_dpm_tabwe *gowden_scwk_tabwe =
			&(data->gowden_dpm_tabwe.scwk_tabwe);
	int vawue = scwk_tabwe->dpm_wevews[scwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_scwk_tabwe->dpm_wevews
			[gowden_scwk_tabwe->count - 1].vawue;

	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int smu7_set_scwk_od(stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *gowden_scwk_tabwe =
			&(data->gowden_dpm_tabwe.scwk_tabwe);
	stwuct pp_powew_state  *ps;
	stwuct smu7_powew_state  *smu7_ps;

	if (vawue > 20)
		vawue = 20;

	ps = hwmgw->wequest_ps;

	if (ps == NUWW)
		wetuwn -EINVAW;

	smu7_ps = cast_phw_smu7_powew_state(&ps->hawdwawe);

	smu7_ps->pewfowmance_wevews[smu7_ps->pewfowmance_wevew_count - 1].engine_cwock =
			gowden_scwk_tabwe->dpm_wevews[gowden_scwk_tabwe->count - 1].vawue *
			vawue / 100 +
			gowden_scwk_tabwe->dpm_wevews[gowden_scwk_tabwe->count - 1].vawue;

	wetuwn 0;
}

static int smu7_get_mcwk_od(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *mcwk_tabwe = &(data->dpm_tabwe.mcwk_tabwe);
	stwuct smu7_singwe_dpm_tabwe *gowden_mcwk_tabwe =
			&(data->gowden_dpm_tabwe.mcwk_tabwe);
        int vawue = mcwk_tabwe->dpm_wevews[mcwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_mcwk_tabwe->dpm_wevews
			[gowden_mcwk_tabwe->count - 1].vawue;

	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int smu7_set_mcwk_od(stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *gowden_mcwk_tabwe =
			&(data->gowden_dpm_tabwe.mcwk_tabwe);
	stwuct pp_powew_state  *ps;
	stwuct smu7_powew_state  *smu7_ps;

	if (vawue > 20)
		vawue = 20;

	ps = hwmgw->wequest_ps;

	if (ps == NUWW)
		wetuwn -EINVAW;

	smu7_ps = cast_phw_smu7_powew_state(&ps->hawdwawe);

	smu7_ps->pewfowmance_wevews[smu7_ps->pewfowmance_wevew_count - 1].memowy_cwock =
			gowden_mcwk_tabwe->dpm_wevews[gowden_mcwk_tabwe->count - 1].vawue *
			vawue / 100 +
			gowden_mcwk_tabwe->dpm_wevews[gowden_mcwk_tabwe->count - 1].vawue;

	wetuwn 0;
}


static int smu7_get_scwks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_cwocks *cwocks)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe = NUWW;
	stwuct phm_cwock_vowtage_dependency_tabwe *scwk_tabwe;
	int i;

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		if (tabwe_info == NUWW || tabwe_info->vdd_dep_on_scwk == NUWW)
			wetuwn -EINVAW;
		dep_scwk_tabwe = tabwe_info->vdd_dep_on_scwk;
		fow (i = 0; i < dep_scwk_tabwe->count; i++)
			cwocks->cwock[i] = dep_scwk_tabwe->entwies[i].cwk * 10;
		cwocks->count = dep_scwk_tabwe->count;
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		scwk_tabwe = hwmgw->dyn_state.vddc_dependency_on_scwk;
		fow (i = 0; i < scwk_tabwe->count; i++)
			cwocks->cwock[i] = scwk_tabwe->entwies[i].cwk * 10;
		cwocks->count = scwk_tabwe->count;
	}

	wetuwn 0;
}

static uint32_t smu7_get_mem_watency(stwuct pp_hwmgw *hwmgw, uint32_t cwk)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (cwk >= MEM_FWEQ_WOW_WATENCY && cwk < MEM_FWEQ_HIGH_WATENCY)
		wetuwn data->mem_watency_high;
	ewse if (cwk >= MEM_FWEQ_HIGH_WATENCY)
		wetuwn data->mem_watency_wow;
	ewse
		wetuwn MEM_WATENCY_EWW;
}

static int smu7_get_mcwks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_cwocks *cwocks)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe;
	int i;
	stwuct phm_cwock_vowtage_dependency_tabwe *mcwk_tabwe;

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1) {
		if (tabwe_info == NUWW)
			wetuwn -EINVAW;
		dep_mcwk_tabwe = tabwe_info->vdd_dep_on_mcwk;
		fow (i = 0; i < dep_mcwk_tabwe->count; i++) {
			cwocks->cwock[i] = dep_mcwk_tabwe->entwies[i].cwk * 10;
			cwocks->watency[i] = smu7_get_mem_watency(hwmgw,
						dep_mcwk_tabwe->entwies[i].cwk);
		}
		cwocks->count = dep_mcwk_tabwe->count;
	} ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0) {
		mcwk_tabwe = hwmgw->dyn_state.vddc_dependency_on_mcwk;
		fow (i = 0; i < mcwk_tabwe->count; i++)
			cwocks->cwock[i] = mcwk_tabwe->entwies[i].cwk * 10;
		cwocks->count = mcwk_tabwe->count;
	}
	wetuwn 0;
}

static int smu7_get_cwock_by_type(stwuct pp_hwmgw *hwmgw, enum amd_pp_cwock_type type,
						stwuct amd_pp_cwocks *cwocks)
{
	switch (type) {
	case amd_pp_sys_cwock:
		smu7_get_scwks(hwmgw, cwocks);
		bweak;
	case amd_pp_mem_cwock:
		smu7_get_mcwks(hwmgw, cwocks);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu7_get_scwks_with_watency(stwuct pp_hwmgw *hwmgw,
				       stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;
	int i;

	cwocks->num_wevews = 0;
	fow (i = 0; i < dep_scwk_tabwe->count; i++) {
		if (dep_scwk_tabwe->entwies[i].cwk) {
			cwocks->data[cwocks->num_wevews].cwocks_in_khz =
				dep_scwk_tabwe->entwies[i].cwk * 10;
			cwocks->num_wevews++;
		}
	}

	wetuwn 0;
}

static int smu7_get_mcwks_with_watency(stwuct pp_hwmgw *hwmgw,
				       stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe =
			tabwe_info->vdd_dep_on_mcwk;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int i;

	cwocks->num_wevews = 0;
	data->mcwk_watency_tabwe.count = 0;
	fow (i = 0; i < dep_mcwk_tabwe->count; i++) {
		if (dep_mcwk_tabwe->entwies[i].cwk) {
			cwocks->data[cwocks->num_wevews].cwocks_in_khz =
					dep_mcwk_tabwe->entwies[i].cwk * 10;
			data->mcwk_watency_tabwe.entwies[data->mcwk_watency_tabwe.count].fwequency =
					dep_mcwk_tabwe->entwies[i].cwk;
			cwocks->data[cwocks->num_wevews].watency_in_us =
				data->mcwk_watency_tabwe.entwies[data->mcwk_watency_tabwe.count].watency =
					smu7_get_mem_watency(hwmgw, dep_mcwk_tabwe->entwies[i].cwk);
			cwocks->num_wevews++;
			data->mcwk_watency_tabwe.count++;
		}
	}

	wetuwn 0;
}

static int smu7_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
					       enum amd_pp_cwock_type type,
					       stwuct pp_cwock_wevews_with_watency *cwocks)
{
	if (!(hwmgw->chip_id >= CHIP_POWAWIS10 &&
	      hwmgw->chip_id <= CHIP_VEGAM))
		wetuwn -EINVAW;

	switch (type) {
	case amd_pp_sys_cwock:
		smu7_get_scwks_with_watency(hwmgw, cwocks);
		bweak;
	case amd_pp_mem_cwock:
		smu7_get_mcwks_with_watency(hwmgw, cwocks);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu7_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
						 void *cwock_wange)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_mcwk_tabwe =
			tabwe_info->vdd_dep_on_mcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;
	stwuct powawis10_smumgw *smu_data =
			(stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	SMU74_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);
	stwuct dm_pp_wm_sets_with_cwock_wanges *watewmawks =
			(stwuct dm_pp_wm_sets_with_cwock_wanges *)cwock_wange;
	uint32_t i, j, k;
	boow vawid_entwy;

	if (!(hwmgw->chip_id >= CHIP_POWAWIS10 &&
	      hwmgw->chip_id <= CHIP_VEGAM))
		wetuwn -EINVAW;

	fow (i = 0; i < dep_mcwk_tabwe->count; i++) {
		fow (j = 0; j < dep_scwk_tabwe->count; j++) {
			vawid_entwy = fawse;
			fow (k = 0; k < watewmawks->num_wm_sets; k++) {
				if (dep_scwk_tabwe->entwies[i].cwk >= watewmawks->wm_cwk_wanges[k].wm_min_eng_cwk_in_khz / 10 &&
				    dep_scwk_tabwe->entwies[i].cwk < watewmawks->wm_cwk_wanges[k].wm_max_eng_cwk_in_khz / 10 &&
				    dep_mcwk_tabwe->entwies[i].cwk >= watewmawks->wm_cwk_wanges[k].wm_min_mem_cwk_in_khz / 10 &&
				    dep_mcwk_tabwe->entwies[i].cwk < watewmawks->wm_cwk_wanges[k].wm_max_mem_cwk_in_khz / 10) {
					vawid_entwy = twue;
					tabwe->DispwayWatewmawk[i][j] = watewmawks->wm_cwk_wanges[k].wm_set_id;
					bweak;
				}
			}
			PP_ASSEWT_WITH_CODE(vawid_entwy,
					"Cwock is not in wange of specified cwock wange fow watewmawk fwom DAW!  Using highest watew mawk set.",
					tabwe->DispwayWatewmawk[i][j] = watewmawks->wm_cwk_wanges[k - 1].wm_set_id);
		}
	}

	wetuwn smu7_copy_bytes_to_smc(hwmgw,
				      smu_data->smu7_data.dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe, DispwayWatewmawk),
				      (uint8_t *)tabwe->DispwayWatewmawk,
				      sizeof(uint8_t) * SMU74_MAX_WEVEWS_MEMOWY * SMU74_MAX_WEVEWS_GWAPHICS,
				      SMC_WAM_END);
}

static int smu7_notify_cac_buffew_info(stwuct pp_hwmgw *hwmgw,
					uint32_t viwtuaw_addw_wow,
					uint32_t viwtuaw_addw_hi,
					uint32_t mc_addw_wow,
					uint32_t mc_addw_hi,
					uint32_t size)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					data->soft_wegs_stawt +
					smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, DWAM_WOG_ADDW_H),
					mc_addw_hi);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					data->soft_wegs_stawt +
					smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, DWAM_WOG_ADDW_W),
					mc_addw_wow);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					data->soft_wegs_stawt +
					smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, DWAM_WOG_PHY_ADDW_H),
					viwtuaw_addw_hi);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					data->soft_wegs_stawt +
					smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, DWAM_WOG_PHY_ADDW_W),
					viwtuaw_addw_wow);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
					data->soft_wegs_stawt +
					smum_get_offsetof(hwmgw,
					SMU_SoftWegistews, DWAM_WOG_BUFF_SIZE),
					size);
	wetuwn 0;
}

static int smu7_get_max_high_cwocks(stwuct pp_hwmgw *hwmgw,
					stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_singwe_dpm_tabwe *scwk_tabwe = &(data->dpm_tabwe.scwk_tabwe);
	stwuct smu7_singwe_dpm_tabwe *mcwk_tabwe = &(data->dpm_tabwe.mcwk_tabwe);

	if (cwocks == NUWW)
		wetuwn -EINVAW;

	cwocks->memowy_max_cwock = mcwk_tabwe->count > 1 ?
				mcwk_tabwe->dpm_wevews[mcwk_tabwe->count-1].vawue :
				mcwk_tabwe->dpm_wevews[0].vawue;
	cwocks->engine_max_cwock = scwk_tabwe->count > 1 ?
				scwk_tabwe->dpm_wevews[scwk_tabwe->count-1].vawue :
				scwk_tabwe->dpm_wevews[0].vawue;
	wetuwn 0;
}

static int smu7_get_thewmaw_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *thewmaw_data)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;

	memcpy(thewmaw_data, &SMU7ThewmawPowicy[0], sizeof(stwuct PP_TempewatuweWange));

	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
		thewmaw_data->max = tabwe_info->cac_dtp_tabwe->usSoftwaweShutdownTemp *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
		thewmaw_data->max = data->thewmaw_temp_setting.tempewatuwe_shutdown *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	thewmaw_data->sw_ctf_thweshowd = thewmaw_data->max;

	wetuwn 0;
}

static boow smu7_check_cwk_vowtage_vawid(stwuct pp_hwmgw *hwmgw,
					enum PP_OD_DPM_TABWE_COMMAND type,
					uint32_t cwk,
					uint32_t vowtage)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (vowtage < data->odn_dpm_tabwe.min_vddc || vowtage > data->odn_dpm_tabwe.max_vddc) {
		pw_info("OD vowtage is out of wange [%d - %d] mV\n",
						data->odn_dpm_tabwe.min_vddc,
						data->odn_dpm_tabwe.max_vddc);
		wetuwn fawse;
	}

	if (type == PP_OD_EDIT_SCWK_VDDC_TABWE) {
		if (data->gowden_dpm_tabwe.scwk_tabwe.dpm_wevews[0].vawue > cwk ||
			hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock < cwk) {
			pw_info("OD engine cwock is out of wange [%d - %d] MHz\n",
				data->gowden_dpm_tabwe.scwk_tabwe.dpm_wevews[0].vawue/100,
				hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock/100);
			wetuwn fawse;
		}
	} ewse if (type == PP_OD_EDIT_MCWK_VDDC_TABWE) {
		if (data->gowden_dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue > cwk ||
			hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock < cwk) {
			pw_info("OD memowy cwock is out of wange [%d - %d] MHz\n",
				data->gowden_dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue/100,
				hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock/100);
			wetuwn fawse;
		}
	} ewse {
		wetuwn fawse;
	}

	wetuwn twue;
}

static int smu7_odn_edit_dpm_tabwe(stwuct pp_hwmgw *hwmgw,
					enum PP_OD_DPM_TABWE_COMMAND type,
					wong *input, uint32_t size)
{
	uint32_t i;
	stwuct phm_odn_cwock_wevews *podn_dpm_tabwe_in_backend = NUWW;
	stwuct smu7_odn_cwock_vowtage_dependency_tabwe *podn_vdd_dep_in_backend = NUWW;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t input_cwk;
	uint32_t input_vow;
	uint32_t input_wevew;

	PP_ASSEWT_WITH_CODE(input, "NUWW usew input fow cwock and vowtage",
				wetuwn -EINVAW);

	if (!hwmgw->od_enabwed) {
		pw_info("OvewDwive featuwe not enabwed\n");
		wetuwn -EINVAW;
	}

	if (PP_OD_EDIT_SCWK_VDDC_TABWE == type) {
		podn_dpm_tabwe_in_backend = &data->odn_dpm_tabwe.odn_cowe_cwock_dpm_wevews;
		podn_vdd_dep_in_backend = &data->odn_dpm_tabwe.vdd_dependency_on_scwk;
		PP_ASSEWT_WITH_CODE((podn_dpm_tabwe_in_backend && podn_vdd_dep_in_backend),
				"Faiwed to get ODN SCWK and Vowtage tabwes",
				wetuwn -EINVAW);
	} ewse if (PP_OD_EDIT_MCWK_VDDC_TABWE == type) {
		podn_dpm_tabwe_in_backend = &data->odn_dpm_tabwe.odn_memowy_cwock_dpm_wevews;
		podn_vdd_dep_in_backend = &data->odn_dpm_tabwe.vdd_dependency_on_mcwk;

		PP_ASSEWT_WITH_CODE((podn_dpm_tabwe_in_backend && podn_vdd_dep_in_backend),
			"Faiwed to get ODN MCWK and Vowtage tabwes",
			wetuwn -EINVAW);
	} ewse if (PP_OD_WESTOWE_DEFAUWT_TABWE == type) {
		smu7_odn_initiaw_defauwt_setting(hwmgw);
		wetuwn 0;
	} ewse if (PP_OD_COMMIT_DPM_TABWE == type) {
		smu7_check_dpm_tabwe_updated(hwmgw);
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}

	fow (i = 0; i < size; i += 3) {
		if (i + 3 > size || input[i] >= podn_dpm_tabwe_in_backend->num_of_pw) {
			pw_info("invawid cwock vowtage input \n");
			wetuwn 0;
		}
		input_wevew = input[i];
		input_cwk = input[i+1] * 100;
		input_vow = input[i+2];

		if (smu7_check_cwk_vowtage_vawid(hwmgw, type, input_cwk, input_vow)) {
			podn_dpm_tabwe_in_backend->entwies[input_wevew].cwock = input_cwk;
			podn_vdd_dep_in_backend->entwies[input_wevew].cwk = input_cwk;
			podn_dpm_tabwe_in_backend->entwies[input_wevew].vddc = input_vow;
			podn_vdd_dep_in_backend->entwies[input_wevew].vddc = input_vow;
			podn_vdd_dep_in_backend->entwies[input_wevew].vddgfx = input_vow;
		} ewse {
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int smu7_get_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, chaw *buf)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t i, size = 0;
	uint32_t wen;

	static const chaw *titwe[8] = {"NUM",
			"MODE_NAME",
			"SCWK_UP_HYST",
			"SCWK_DOWN_HYST",
			"SCWK_ACTIVE_WEVEW",
			"MCWK_UP_HYST",
			"MCWK_DOWN_HYST",
			"MCWK_ACTIVE_WEVEW"};

	if (!buf)
		wetuwn -EINVAW;

	phm_get_sysfs_buf(&buf, &size);

	size += sysfs_emit_at(buf, size, "%s %16s %16s %16s %16s %16s %16s %16s\n",
			titwe[0], titwe[1], titwe[2], titwe[3],
			titwe[4], titwe[5], titwe[6], titwe[7]);

	wen = AWWAY_SIZE(smu7_pwofiwing);

	fow (i = 0; i < wen; i++) {
		if (i == hwmgw->powew_pwofiwe_mode) {
			size += sysfs_emit_at(buf, size, "%3d %14s %s: %8d %16d %16d %16d %16d %16d\n",
			i, amdgpu_pp_pwofiwe_name[i], "*",
			data->cuwwent_pwofiwe_setting.scwk_up_hyst,
			data->cuwwent_pwofiwe_setting.scwk_down_hyst,
			data->cuwwent_pwofiwe_setting.scwk_activity,
			data->cuwwent_pwofiwe_setting.mcwk_up_hyst,
			data->cuwwent_pwofiwe_setting.mcwk_down_hyst,
			data->cuwwent_pwofiwe_setting.mcwk_activity);
			continue;
		}
		if (smu7_pwofiwing[i].bupdate_scwk)
			size += sysfs_emit_at(buf, size, "%3d %16s: %8d %16d %16d ",
			i, amdgpu_pp_pwofiwe_name[i], smu7_pwofiwing[i].scwk_up_hyst,
			smu7_pwofiwing[i].scwk_down_hyst,
			smu7_pwofiwing[i].scwk_activity);
		ewse
			size += sysfs_emit_at(buf, size, "%3d %16s: %8s %16s %16s ",
			i, amdgpu_pp_pwofiwe_name[i], "-", "-", "-");

		if (smu7_pwofiwing[i].bupdate_mcwk)
			size += sysfs_emit_at(buf, size, "%16d %16d %16d\n",
			smu7_pwofiwing[i].mcwk_up_hyst,
			smu7_pwofiwing[i].mcwk_down_hyst,
			smu7_pwofiwing[i].mcwk_activity);
		ewse
			size += sysfs_emit_at(buf, size, "%16s %16s %16s\n",
			"-", "-", "-");
	}

	wetuwn size;
}

static void smu7_patch_compute_pwofiwe_mode(stwuct pp_hwmgw *hwmgw,
					enum PP_SMC_POWEW_PWOFIWE wequst)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t tmp, wevew;

	if (wequst == PP_SMC_POWEW_PWOFIWE_COMPUTE) {
		if (data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask) {
			wevew = 0;
			tmp = data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask;
			whiwe (tmp >>= 1)
				wevew++;
			if (wevew > 0)
				smu7_fowce_cwock_wevew(hwmgw, PP_SCWK, 3 << (wevew-1));
		}
	} ewse if (hwmgw->powew_pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_COMPUTE) {
		smu7_fowce_cwock_wevew(hwmgw, PP_SCWK, data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask);
	}
}

static int smu7_set_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, wong *input, uint32_t size)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct pwofiwe_mode_setting tmp;
	enum PP_SMC_POWEW_PWOFIWE mode;

	if (input == NUWW)
		wetuwn -EINVAW;

	mode = input[size];
	switch (mode) {
	case PP_SMC_POWEW_PWOFIWE_CUSTOM:
		if (size < 8 && size != 0)
			wetuwn -EINVAW;
		/* If onwy CUSTOM is passed in, use the saved vawues. Check
		 * that we actuawwy have a CUSTOM pwofiwe by ensuwing that
		 * the "use scwk" ow the "use mcwk" bits awe set
		 */
		tmp = smu7_pwofiwing[PP_SMC_POWEW_PWOFIWE_CUSTOM];
		if (size == 0) {
			if (tmp.bupdate_scwk == 0 && tmp.bupdate_mcwk == 0)
				wetuwn -EINVAW;
		} ewse {
			tmp.bupdate_scwk = input[0];
			tmp.scwk_up_hyst = input[1];
			tmp.scwk_down_hyst = input[2];
			tmp.scwk_activity = input[3];
			tmp.bupdate_mcwk = input[4];
			tmp.mcwk_up_hyst = input[5];
			tmp.mcwk_down_hyst = input[6];
			tmp.mcwk_activity = input[7];
			smu7_pwofiwing[PP_SMC_POWEW_PWOFIWE_CUSTOM] = tmp;
		}
		if (!smum_update_dpm_settings(hwmgw, &tmp)) {
			memcpy(&data->cuwwent_pwofiwe_setting, &tmp, sizeof(stwuct pwofiwe_mode_setting));
			hwmgw->powew_pwofiwe_mode = mode;
		}
		bweak;
	case PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D:
	case PP_SMC_POWEW_PWOFIWE_POWEWSAVING:
	case PP_SMC_POWEW_PWOFIWE_VIDEO:
	case PP_SMC_POWEW_PWOFIWE_VW:
	case PP_SMC_POWEW_PWOFIWE_COMPUTE:
		if (mode == hwmgw->powew_pwofiwe_mode)
			wetuwn 0;

		memcpy(&tmp, &smu7_pwofiwing[mode], sizeof(stwuct pwofiwe_mode_setting));
		if (!smum_update_dpm_settings(hwmgw, &tmp)) {
			if (tmp.bupdate_scwk) {
				data->cuwwent_pwofiwe_setting.bupdate_scwk = tmp.bupdate_scwk;
				data->cuwwent_pwofiwe_setting.scwk_up_hyst = tmp.scwk_up_hyst;
				data->cuwwent_pwofiwe_setting.scwk_down_hyst = tmp.scwk_down_hyst;
				data->cuwwent_pwofiwe_setting.scwk_activity = tmp.scwk_activity;
			}
			if (tmp.bupdate_mcwk) {
				data->cuwwent_pwofiwe_setting.bupdate_mcwk = tmp.bupdate_mcwk;
				data->cuwwent_pwofiwe_setting.mcwk_up_hyst = tmp.mcwk_up_hyst;
				data->cuwwent_pwofiwe_setting.mcwk_down_hyst = tmp.mcwk_down_hyst;
				data->cuwwent_pwofiwe_setting.mcwk_activity = tmp.mcwk_activity;
			}
			smu7_patch_compute_pwofiwe_mode(hwmgw, mode);
			hwmgw->powew_pwofiwe_mode = mode;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu7_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	const stwuct smu7_powew_state *ps;
	uint32_t i;

	if (wevew == NUWW || hwmgw == NUWW || state == NUWW)
		wetuwn -EINVAW;

	ps = cast_const_phw_smu7_powew_state(state);

	i = index > ps->pewfowmance_wevew_count - 1 ?
			ps->pewfowmance_wevew_count - 1 : index;

	wevew->coweCwock = ps->pewfowmance_wevews[i].engine_cwock;
	wevew->memowy_cwock = ps->pewfowmance_wevews[i].memowy_cwock;

	wetuwn 0;
}

static int smu7_powew_off_asic(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;

	wesuwt = smu7_disabwe_dpm_tasks(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"[disabwe_dpm_tasks] Faiwed to disabwe DPM!",
			);

	wetuwn wesuwt;
}

static const stwuct pp_hwmgw_func smu7_hwmgw_funcs = {
	.backend_init = &smu7_hwmgw_backend_init,
	.backend_fini = &smu7_hwmgw_backend_fini,
	.asic_setup = &smu7_setup_asic_task,
	.dynamic_state_management_enabwe = &smu7_enabwe_dpm_tasks,
	.appwy_state_adjust_wuwes = smu7_appwy_state_adjust_wuwes,
	.fowce_dpm_wevew = &smu7_fowce_dpm_wevew,
	.powew_state_set = smu7_set_powew_state_tasks,
	.get_powew_state_size = smu7_get_powew_state_size,
	.get_mcwk = smu7_dpm_get_mcwk,
	.get_scwk = smu7_dpm_get_scwk,
	.patch_boot_state = smu7_dpm_patch_boot_state,
	.get_pp_tabwe_entwy = smu7_get_pp_tabwe_entwy,
	.get_num_of_pp_tabwe_entwies = smu7_get_numbew_of_powewpway_tabwe_entwies,
	.powewdown_uvd = smu7_powewdown_uvd,
	.powewgate_uvd = smu7_powewgate_uvd,
	.powewgate_vce = smu7_powewgate_vce,
	.disabwe_cwock_powew_gating = smu7_disabwe_cwock_powew_gating,
	.update_cwock_gatings = smu7_update_cwock_gatings,
	.notify_smc_dispway_config_aftew_ps_adjustment = smu7_notify_smc_dispway_config_aftew_ps_adjustment,
	.dispway_config_changed = smu7_dispway_configuwation_changed_task,
	.set_max_fan_pwm_output = smu7_set_max_fan_pwm_output,
	.set_max_fan_wpm_output = smu7_set_max_fan_wpm_output,
	.stop_thewmaw_contwowwew = smu7_thewmaw_stop_thewmaw_contwowwew,
	.get_fan_speed_info = smu7_fan_ctww_get_fan_speed_info,
	.get_fan_speed_pwm = smu7_fan_ctww_get_fan_speed_pwm,
	.set_fan_speed_pwm = smu7_fan_ctww_set_fan_speed_pwm,
	.weset_fan_speed_to_defauwt = smu7_fan_ctww_weset_fan_speed_to_defauwt,
	.get_fan_speed_wpm = smu7_fan_ctww_get_fan_speed_wpm,
	.set_fan_speed_wpm = smu7_fan_ctww_set_fan_speed_wpm,
	.uninitiawize_thewmaw_contwowwew = smu7_thewmaw_ctww_uninitiawize_thewmaw_contwowwew,
	.wegistew_iwq_handwews = smu7_wegistew_iwq_handwews,
	.check_smc_update_wequiwed_fow_dispway_configuwation = smu7_check_smc_update_wequiwed_fow_dispway_configuwation,
	.check_states_equaw = smu7_check_states_equaw,
	.set_fan_contwow_mode = smu7_set_fan_contwow_mode,
	.get_fan_contwow_mode = smu7_get_fan_contwow_mode,
	.fowce_cwock_wevew = smu7_fowce_cwock_wevew,
	.pwint_cwock_wevews = smu7_pwint_cwock_wevews,
	.powewgate_gfx = smu7_powewgate_gfx,
	.get_scwk_od = smu7_get_scwk_od,
	.set_scwk_od = smu7_set_scwk_od,
	.get_mcwk_od = smu7_get_mcwk_od,
	.set_mcwk_od = smu7_set_mcwk_od,
	.get_cwock_by_type = smu7_get_cwock_by_type,
	.get_cwock_by_type_with_watency = smu7_get_cwock_by_type_with_watency,
	.set_watewmawks_fow_cwocks_wanges = smu7_set_watewmawks_fow_cwocks_wanges,
	.wead_sensow = smu7_wead_sensow,
	.dynamic_state_management_disabwe = smu7_disabwe_dpm_tasks,
	.avfs_contwow = smu7_avfs_contwow,
	.disabwe_smc_fiwmwawe_ctf = smu7_thewmaw_disabwe_awewt,
	.stawt_thewmaw_contwowwew = smu7_stawt_thewmaw_contwowwew,
	.notify_cac_buffew_info = smu7_notify_cac_buffew_info,
	.get_max_high_cwocks = smu7_get_max_high_cwocks,
	.get_thewmaw_tempewatuwe_wange = smu7_get_thewmaw_tempewatuwe_wange,
	.odn_edit_dpm_tabwe = smu7_odn_edit_dpm_tabwe,
	.set_powew_wimit = smu7_set_powew_wimit,
	.get_powew_pwofiwe_mode = smu7_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = smu7_set_powew_pwofiwe_mode,
	.get_pewfowmance_wevew = smu7_get_pewfowmance_wevew,
	.get_asic_baco_capabiwity = smu7_baco_get_capabiwity,
	.get_asic_baco_state = smu7_baco_get_state,
	.set_asic_baco_state = smu7_baco_set_state,
	.powew_off_asic = smu7_powew_off_asic,
};

uint8_t smu7_get_sweep_dividew_id_fwom_cwock(uint32_t cwock,
		uint32_t cwock_insw)
{
	uint8_t i;
	uint32_t temp;
	uint32_t min = max(cwock_insw, (uint32_t)SMU7_MINIMUM_ENGINE_CWOCK);

	PP_ASSEWT_WITH_CODE((cwock >= min), "Engine cwock can't satisfy stuttew wequiwement!", wetuwn 0);
	fow (i = SMU7_MAX_DEEPSWEEP_DIVIDEW_ID;  ; i--) {
		temp = cwock >> i;

		if (temp >= min || i == 0)
			bweak;
	}
	wetuwn i;
}

int smu7_init_function_pointews(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->hwmgw_func = &smu7_hwmgw_funcs;
	if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V0)
		hwmgw->pptabwe_func = &pptabwe_funcs;
	ewse if (hwmgw->pp_tabwe_vewsion == PP_TABWE_V1)
		hwmgw->pptabwe_func = &pptabwe_v1_0_funcs;

	wetuwn 0;
}
