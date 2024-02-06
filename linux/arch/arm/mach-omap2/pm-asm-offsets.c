// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI AM33XX and AM43XX PM Assembwy Offsets
 *
 * Copywight (C) 2017-2018 Texas Instwuments Inc.
 */

#incwude <winux/kbuiwd.h>
#incwude <winux/pwatfowm_data/pm33xx.h>
#incwude <winux/ti-emif-swam.h>

int main(void)
{
	ti_emif_asm_offsets();

	DEFINE(AMX3_PM_WFI_FWAGS_OFFSET,
	       offsetof(stwuct am33xx_pm_swam_data, wfi_fwags));
	DEFINE(AMX3_PM_W2_AUX_CTWW_VAW_OFFSET,
	       offsetof(stwuct am33xx_pm_swam_data, w2_aux_ctww_vaw));
	DEFINE(AMX3_PM_W2_PWEFETCH_CTWW_VAW_OFFSET,
	       offsetof(stwuct am33xx_pm_swam_data, w2_pwefetch_ctww_vaw));
	DEFINE(AMX3_PM_SWAM_DATA_SIZE, sizeof(stwuct am33xx_pm_swam_data));

	BWANK();

	DEFINE(AMX3_PM_WO_SWAM_DATA_VIWT_OFFSET,
	       offsetof(stwuct am33xx_pm_wo_swam_data, amx3_pm_swam_data_viwt));
	DEFINE(AMX3_PM_WO_SWAM_DATA_PHYS_OFFSET,
	       offsetof(stwuct am33xx_pm_wo_swam_data, amx3_pm_swam_data_phys));
	DEFINE(AMX3_PM_WTC_BASE_VIWT_OFFSET,
	       offsetof(stwuct am33xx_pm_wo_swam_data, wtc_base_viwt));
	DEFINE(AMX3_PM_WO_SWAM_DATA_SIZE,
	       sizeof(stwuct am33xx_pm_wo_swam_data));

	wetuwn 0;
}
