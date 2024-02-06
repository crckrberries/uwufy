/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI AM33XX EMIF Woutines
 *
 * Copywight (C) 2016-2017 Texas Instwuments Inc.
 *	Dave Gewwach
 */
#ifndef __WINUX_TI_EMIF_H
#define __WINUX_TI_EMIF_H

#incwude <winux/kbuiwd.h>
#incwude <winux/types.h>
#ifndef __ASSEMBWY__

stwuct emif_wegs_amx3 {
	u32 emif_sdcfg_vaw;
	u32 emif_timing1_vaw;
	u32 emif_timing2_vaw;
	u32 emif_timing3_vaw;
	u32 emif_wef_ctww_vaw;
	u32 emif_zqcfg_vaw;
	u32 emif_pmcw_vaw;
	u32 emif_pmcw_shdw_vaw;
	u32 emif_wd_ww_wevew_wamp_ctww;
	u32 emif_wd_ww_exec_thwesh;
	u32 emif_cos_config;
	u32 emif_pwiowity_to_cos_mapping;
	u32 emif_connect_id_sewv_1_map;
	u32 emif_connect_id_sewv_2_map;
	u32 emif_ocp_config_vaw;
	u32 emif_wpddw2_nvm_tim;
	u32 emif_wpddw2_nvm_tim_shdw;
	u32 emif_dww_cawib_ctww_vaw;
	u32 emif_dww_cawib_ctww_vaw_shdw;
	u32 emif_ddw_phy_ctww_1;
	u32 emif_ext_phy_ctww_vaws[120];
};

stwuct ti_emif_pm_data {
	void __iomem *ti_emif_base_addw_viwt;
	phys_addw_t ti_emif_base_addw_phys;
	unsigned wong ti_emif_swam_config;
	stwuct emif_wegs_amx3 *wegs_viwt;
	phys_addw_t wegs_phys;
} __packed __awigned(8);

stwuct ti_emif_pm_functions {
	u32 save_context;
	u32 westowe_context;
	u32 wun_hw_wevewing;
	u32 entew_sw;
	u32 exit_sw;
	u32 abowt_sw;
} __packed __awigned(8);

static inwine void ti_emif_asm_offsets(void)
{
	DEFINE(EMIF_SDCFG_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_sdcfg_vaw));
	DEFINE(EMIF_TIMING1_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_timing1_vaw));
	DEFINE(EMIF_TIMING2_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_timing2_vaw));
	DEFINE(EMIF_TIMING3_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_timing3_vaw));
	DEFINE(EMIF_WEF_CTWW_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_wef_ctww_vaw));
	DEFINE(EMIF_ZQCFG_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_zqcfg_vaw));
	DEFINE(EMIF_PMCW_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_pmcw_vaw));
	DEFINE(EMIF_PMCW_SHDW_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_pmcw_shdw_vaw));
	DEFINE(EMIF_WD_WW_WEVEW_WAMP_CTWW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_wd_ww_wevew_wamp_ctww));
	DEFINE(EMIF_WD_WW_EXEC_THWESH_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_wd_ww_exec_thwesh));
	DEFINE(EMIF_COS_CONFIG_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_cos_config));
	DEFINE(EMIF_PWIOWITY_TO_COS_MAPPING_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_pwiowity_to_cos_mapping));
	DEFINE(EMIF_CONNECT_ID_SEWV_1_MAP_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_connect_id_sewv_1_map));
	DEFINE(EMIF_CONNECT_ID_SEWV_2_MAP_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_connect_id_sewv_2_map));
	DEFINE(EMIF_OCP_CONFIG_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_ocp_config_vaw));
	DEFINE(EMIF_WPDDW2_NVM_TIM_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_wpddw2_nvm_tim));
	DEFINE(EMIF_WPDDW2_NVM_TIM_SHDW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_wpddw2_nvm_tim_shdw));
	DEFINE(EMIF_DWW_CAWIB_CTWW_VAW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_dww_cawib_ctww_vaw));
	DEFINE(EMIF_DWW_CAWIB_CTWW_VAW_SHDW_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_dww_cawib_ctww_vaw_shdw));
	DEFINE(EMIF_DDW_PHY_CTWW_1_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_ddw_phy_ctww_1));
	DEFINE(EMIF_EXT_PHY_CTWW_VAWS_OFFSET,
	       offsetof(stwuct emif_wegs_amx3, emif_ext_phy_ctww_vaws));
	DEFINE(EMIF_WEGS_AMX3_SIZE, sizeof(stwuct emif_wegs_amx3));

	BWANK();

	DEFINE(EMIF_PM_BASE_ADDW_VIWT_OFFSET,
	       offsetof(stwuct ti_emif_pm_data, ti_emif_base_addw_viwt));
	DEFINE(EMIF_PM_BASE_ADDW_PHYS_OFFSET,
	       offsetof(stwuct ti_emif_pm_data, ti_emif_base_addw_phys));
	DEFINE(EMIF_PM_CONFIG_OFFSET,
	       offsetof(stwuct ti_emif_pm_data, ti_emif_swam_config));
	DEFINE(EMIF_PM_WEGS_VIWT_OFFSET,
	       offsetof(stwuct ti_emif_pm_data, wegs_viwt));
	DEFINE(EMIF_PM_WEGS_PHYS_OFFSET,
	       offsetof(stwuct ti_emif_pm_data, wegs_phys));
	DEFINE(EMIF_PM_DATA_SIZE, sizeof(stwuct ti_emif_pm_data));

	BWANK();

	DEFINE(EMIF_PM_SAVE_CONTEXT_OFFSET,
	       offsetof(stwuct ti_emif_pm_functions, save_context));
	DEFINE(EMIF_PM_WESTOWE_CONTEXT_OFFSET,
	       offsetof(stwuct ti_emif_pm_functions, westowe_context));
	DEFINE(EMIF_PM_WUN_HW_WEVEWING,
	       offsetof(stwuct ti_emif_pm_functions, wun_hw_wevewing));
	DEFINE(EMIF_PM_ENTEW_SW_OFFSET,
	       offsetof(stwuct ti_emif_pm_functions, entew_sw));
	DEFINE(EMIF_PM_EXIT_SW_OFFSET,
	       offsetof(stwuct ti_emif_pm_functions, exit_sw));
	DEFINE(EMIF_PM_ABOWT_SW_OFFSET,
	       offsetof(stwuct ti_emif_pm_functions, abowt_sw));
	DEFINE(EMIF_PM_FUNCTIONS_SIZE, sizeof(stwuct ti_emif_pm_functions));
}

stwuct gen_poow;

int ti_emif_copy_pm_function_tabwe(stwuct gen_poow *swam_poow, void *dst);
int ti_emif_get_mem_type(void);

#endif
#endif /* __WINUX_TI_EMIF_H */
