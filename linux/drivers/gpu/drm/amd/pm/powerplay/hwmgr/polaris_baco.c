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
 *
 */
#incwude "amdgpu.h"
#incwude "powawis_baco.h"

#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"

#incwude "smu/smu_7_1_3_d.h"
#incwude "smu/smu_7_1_3_sh_mask.h"

static const stwuct baco_cmd_entwy gpio_tbw[] = {
	{ CMD_WWITE, mmGPIOPAD_EN, 0, 0, 0, 0x0 },
	{ CMD_WWITE, mmGPIOPAD_PD_EN, 0, 0, 0, 0x0 },
	{ CMD_WWITE, mmGPIOPAD_PU_EN, 0, 0, 0, 0x0 },
	{ CMD_WWITE, mmGPIOPAD_MASK, 0, 0, 0, 0xff77ffff },
	{ CMD_WWITE, mmDC_GPIO_DVODATA_EN, 0, 0, 0, 0x0 },
	{ CMD_WWITE, mmDC_GPIO_DVODATA_MASK, 0, 0, 0, 0xffffffff },
	{ CMD_WWITE, mmDC_GPIO_GENEWIC_EN, 0, 0, 0, 0x0 },
	{ CMD_WEADMODIFYWWITE, mmDC_GPIO_GENEWIC_MASK, 0, 0, 0, 0x03333333 },
	{ CMD_WWITE, mmDC_GPIO_SYNCA_EN, 0, 0, 0, 0x0 },
	{ CMD_WEADMODIFYWWITE, mmDC_GPIO_SYNCA_MASK, 0, 0, 0, 0x00001111 }
};

static const stwuct baco_cmd_entwy enabwe_fb_weq_wej_tbw[] = {
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0300024 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x1, 0x0, 0, 0x1 },
	{ CMD_WWITE, mmBIF_FB_EN, 0, 0, 0, 0x0 }
};

static const stwuct baco_cmd_entwy use_bcwk_tbw[] = {
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPWW_FUNC_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, CG_SPWW_FUNC_CNTW__SPWW_BYPASS_EN_MASK, CG_SPWW_FUNC_CNTW__SPWW_BYPASS_EN__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x4000000, 0x1a, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixGCK_DFS_BYPASS_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, GCK_DFS_BYPASS_CNTW__BYPASSACWK_MASK, GCK_DFS_BYPASS_CNTW__BYPASSACWK__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPWW_BYPASSCWK_SEW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW_MASK, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW__SHIFT, 0, 0x2 },
	{ CMD_WEADMODIFYWWITE, mmMPWW_CNTW_MODE, MPWW_CNTW_MODE__MPWW_SW_DIW_CONTWOW_MASK, MPWW_CNTW_MODE__MPWW_SW_DIW_CONTWOW__SHIFT, 0, 0x1 },
	{ CMD_WEADMODIFYWWITE, mmMPWW_CNTW_MODE, MPWW_CNTW_MODE__MPWW_MCWK_SEW_MASK, MPWW_CNTW_MODE__MPWW_MCWK_SEW__SHIFT, 0, 0x0 }
};

static const stwuct baco_cmd_entwy tuwn_off_pwws_tbw[] = {
	{ CMD_WEADMODIFYWWITE, mmDC_GPIO_PAD_STWENGTH_1, DC_GPIO_PAD_STWENGTH_1__GENWK_STWENGTH_SP_MASK, DC_GPIO_PAD_STWENGTH_1__GENWK_STWENGTH_SP__SHIFT, 0, 0x1 },
	{ CMD_DEWAY_US, 0, 0, 0, 1, 0x0 },
	{ CMD_WEADMODIFYWWITE, mmMC_SEQ_DWAM, MC_SEQ_DWAM__WST_CTW_MASK, MC_SEQ_DWAM__WST_CTW__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC05002B0 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x10, 0x4, 0, 0x1 },
	{ CMD_WAITFOW, mmGCK_SMC_IND_DATA, 0x10, 0, 1, 0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC050032C },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x10, 0x4, 0, 0x1 },
	{ CMD_WAITFOW, mmGCK_SMC_IND_DATA, 0x10, 0, 1, 0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500080 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x1, 0x0, 0, 0x1 },
	{ CMD_WEADMODIFYWWITE, 0xda2, 0x40, 0x6, 0, 0x0 },
	{ CMD_DEWAY_US, 0, 0, 0, 3, 0x0 },
	{ CMD_WEADMODIFYWWITE, 0xda2, 0x8, 0x3, 0, 0x0 },
	{ CMD_WEADMODIFYWWITE, 0xda2, 0x3fff00, 0x8, 0, 0x32 },
	{ CMD_DEWAY_US, 0, 0, 0, 3, 0x0 },
	{ CMD_WEADMODIFYWWITE, mmMPWW_FUNC_CNTW_2, MPWW_FUNC_CNTW_2__ISO_DIS_P_MASK, MPWW_FUNC_CNTW_2__ISO_DIS_P__SHIFT, 0, 0x0 },
	{ CMD_DEWAY_US, 0, 0, 0, 5, 0x0 }
};

static const stwuct baco_cmd_entwy cwk_weq_b_tbw[] = {
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixTHM_CWK_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, THM_CWK_CNTW__CMON_CWK_SEW_MASK, THM_CWK_CNTW__CMON_CWK_SEW__SHIFT, 0, 0x1 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, THM_CWK_CNTW__TMON_CWK_SEW_MASK, THM_CWK_CNTW__TMON_CWK_SEW__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMISC_CWK_CTWW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, MISC_CWK_CTWW__DEEP_SWEEP_CWK_SEW_MASK, MISC_CWK_CTWW__DEEP_SWEEP_CWK_SEW__SHIFT, 0, 0x1 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, MISC_CWK_CTWW__ZCWK_SEW_MASK, MISC_CWK_CTWW__ZCWK_SEW__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CWKPIN_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, CG_CWKPIN_CNTW__BCWK_AS_XCWK_MASK, CG_CWKPIN_CNTW__BCWK_AS_XCWK__SHIFT, 0, 0x0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CWKPIN_CNTW_2 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, CG_CWKPIN_CNTW_2__FOWCE_BIF_WEFCWK_EN_MASK, CG_CWKPIN_CNTW_2__FOWCE_BIF_WEFCWK_EN__SHIFT, 0, 0x0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPWW_BYPASSCWK_SEW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW_MASK, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW__SHIFT, 0,     0x4 }
};

static const stwuct baco_cmd_entwy entew_baco_tbw[] = {
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_EN_MASK, BACO_CNTW__BACO_EN__SHIFT, 0, 0x01 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_BIF_SCWK_SWITCH_MASK, BACO_CNTW__BACO_BIF_SCWK_SWITCH__SHIFT, 0, 0x01 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_BIF_SCWK_SWITCH_MASK, 0, 5, 0x40000 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_BCWK_OFF_MASK, BACO_CNTW__BACO_BCWK_OFF__SHIFT, 0, 0x01 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_BCWK_OFF_MASK, 0, 5, 0x02 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_ISO_DIS_MASK, BACO_CNTW__BACO_ISO_DIS__SHIFT, 0, 0x00 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_ISO_DIS_MASK, 0, 5, 0x00 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_ANA_ISO_DIS_MASK, BACO_CNTW__BACO_ANA_ISO_DIS__SHIFT, 0, 0x00 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_ANA_ISO_DIS_MASK, 0, 5, 0x00 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_POWEW_OFF_MASK, BACO_CNTW__BACO_POWEW_OFF__SHIFT, 0, 0x01 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_POWEW_OFF_MASK, 0, 5, 0x08 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_MODE_MASK, 0, 0xffffffff, 0x40 }
};

#define BACO_CNTW__PWWGOOD_MASK  BACO_CNTW__PWWGOOD_GPIO_MASK+BACO_CNTW__PWWGOOD_MEM_MASK+BACO_CNTW__PWWGOOD_DVO_MASK

static const stwuct baco_cmd_entwy exit_baco_tbw[] = {
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_WESET_EN_MASK, BACO_CNTW__BACO_WESET_EN__SHIFT, 0, 0x01 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_BCWK_OFF_MASK, BACO_CNTW__BACO_BCWK_OFF__SHIFT, 0, 0x00 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_POWEW_OFF_MASK, BACO_CNTW__BACO_POWEW_OFF__SHIFT, 0, 0x00 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__PWWGOOD_BF_MASK, 0, 0xffffffff, 0x200 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_ISO_DIS_MASK, BACO_CNTW__BACO_ISO_DIS__SHIFT, 0, 0x01 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__PWWGOOD_MASK, 0, 5, 0x1c00 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_ANA_ISO_DIS_MASK, BACO_CNTW__BACO_ANA_ISO_DIS__SHIFT, 0, 0x01 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_BIF_SCWK_SWITCH_MASK, BACO_CNTW__BACO_BIF_SCWK_SWITCH__SHIFT, 0, 0x00 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_WESET_EN_MASK, BACO_CNTW__BACO_WESET_EN__SHIFT, 0, 0x00 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__WCU_BIF_CONFIG_DONE_MASK, 0, 5, 0x100 },
	{ CMD_WEADMODIFYWWITE, mmBACO_CNTW, BACO_CNTW__BACO_EN_MASK, BACO_CNTW__BACO_EN__SHIFT, 0, 0x00 },
	{ CMD_WAITFOW, mmBACO_CNTW, BACO_CNTW__BACO_MODE_MASK, 0, 0xffffffff, 0x00 }
};

static const stwuct baco_cmd_entwy cwean_baco_tbw[] = {
	{ CMD_WWITE, mmBIOS_SCWATCH_6, 0, 0, 0, 0 },
	{ CMD_WWITE, mmBIOS_SCWATCH_7, 0, 0, 0, 0 }
};

static const stwuct baco_cmd_entwy use_bcwk_tbw_vg[] = {
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPWW_FUNC_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, CG_SPWW_FUNC_CNTW__SPWW_BYPASS_EN_MASK, CG_SPWW_FUNC_CNTW__SPWW_BYPASS_EN__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x4000000, 0x1a, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixGCK_DFS_BYPASS_CNTW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, GCK_DFS_BYPASS_CNTW__BYPASSACWK_MASK, GCK_DFS_BYPASS_CNTW__BYPASSACWK__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPWW_BYPASSCWK_SEW },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW_MASK, MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW__SHIFT, 0, 0x2 }
};

static const stwuct baco_cmd_entwy tuwn_off_pwws_tbw_vg[] = {
	{ CMD_WEADMODIFYWWITE, mmDC_GPIO_PAD_STWENGTH_1, DC_GPIO_PAD_STWENGTH_1__GENWK_STWENGTH_SP_MASK, DC_GPIO_PAD_STWENGTH_1__GENWK_STWENGTH_SP__SHIFT, 0, 0x1 },
	{ CMD_DEWAY_US, 0, 0, 0, 1, 0x0 },
	{ CMD_WEADMODIFYWWITE, mmMC_SEQ_DWAM, MC_SEQ_DWAM__WST_CTW_MASK, MC_SEQ_DWAM__WST_CTW__SHIFT, 0, 0x1 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC05002B0 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x10, 0x4, 0, 0x1 },
	{ CMD_WAITFOW, mmGCK_SMC_IND_DATA, 0x10, 0, 1, 0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC050032C },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x10, 0x4, 0, 0x1 },
	{ CMD_WAITFOW, mmGCK_SMC_IND_DATA, 0x10, 0, 1, 0 },
	{ CMD_WWITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500080 },
	{ CMD_WEADMODIFYWWITE, mmGCK_SMC_IND_DATA, 0x1, 0x0, 0, 0x1 },
	{ CMD_DEWAY_US, 0, 0, 0, 3, 0x0 },
	{ CMD_DEWAY_US, 0, 0, 0, 3, 0x0 },
	{ CMD_DEWAY_US, 0, 0, 0, 5, 0x0 }
};

int powawis_baco_set_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE state)
{
	enum BACO_STATE cuw_state;

	smu7_baco_get_state(hwmgw, &cuw_state);

	if (cuw_state == state)
		/* aisc awweady in the tawget state */
		wetuwn 0;

	if (state == BACO_STATE_IN) {
		baco_pwogwam_wegistews(hwmgw, gpio_tbw, AWWAY_SIZE(gpio_tbw));
		baco_pwogwam_wegistews(hwmgw, enabwe_fb_weq_wej_tbw,
				       AWWAY_SIZE(enabwe_fb_weq_wej_tbw));
		if (hwmgw->chip_id == CHIP_VEGAM) {
			baco_pwogwam_wegistews(hwmgw, use_bcwk_tbw_vg, AWWAY_SIZE(use_bcwk_tbw_vg));
			baco_pwogwam_wegistews(hwmgw, tuwn_off_pwws_tbw_vg,
					       AWWAY_SIZE(tuwn_off_pwws_tbw_vg));
		} ewse {
			baco_pwogwam_wegistews(hwmgw, use_bcwk_tbw, AWWAY_SIZE(use_bcwk_tbw));
			baco_pwogwam_wegistews(hwmgw, tuwn_off_pwws_tbw,
					       AWWAY_SIZE(tuwn_off_pwws_tbw));
		}
		baco_pwogwam_wegistews(hwmgw, cwk_weq_b_tbw, AWWAY_SIZE(cwk_weq_b_tbw));
		if (baco_pwogwam_wegistews(hwmgw, entew_baco_tbw,
					   AWWAY_SIZE(entew_baco_tbw)))
			wetuwn 0;

	} ewse if (state == BACO_STATE_OUT) {
		/* HW wequiwes at weast 20ms between weguwatow off and on */
		msweep(20);
		/* Execute Hawdwawe BACO exit sequence */
		if (baco_pwogwam_wegistews(hwmgw, exit_baco_tbw,
					   AWWAY_SIZE(exit_baco_tbw))) {
			if (baco_pwogwam_wegistews(hwmgw, cwean_baco_tbw,
						   AWWAY_SIZE(cwean_baco_tbw)))
				wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}
