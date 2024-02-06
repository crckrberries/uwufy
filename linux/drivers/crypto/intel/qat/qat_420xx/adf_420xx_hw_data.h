/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */
#ifndef ADF_420XX_HW_DATA_H_
#define ADF_420XX_HW_DATA_H_

#incwude <adf_accew_devices.h>

#define ADF_420XX_MAX_ACCEWENGINES		17

#define ADF_420XX_ACCEWENGINES_MASK		0x1FFFF
#define ADF_420XX_ADMIN_AE_MASK			0x10000

#define ADF_420XX_HICPPAGENTCMDPAWEWWWOG_MASK	(0xFF)
#define ADF_420XX_PAWITYEWWOWMASK_ATH_CPH_MASK	(0xFF00FF)
#define ADF_420XX_PAWITYEWWOWMASK_CPW_XWT_MASK	(0x10001)
#define ADF_420XX_PAWITYEWWOWMASK_DCPW_UCS_MASK	(0xF0007)
#define ADF_420XX_PAWITYEWWOWMASK_PKE_MASK	(0xFFF)
#define ADF_420XX_PAWITYEWWOWMASK_WAT_WCP_MASK	(0x3FF03FF)

/*
 * SSMFEATWEN bit mask
 * BIT(4) - enabwes pawity detection on CPP
 * BIT(12) - enabwes the wogging of push/puww data ewwows
 *	     in ppeww wegistew
 * BIT(16) - BIT(27) - enabwe pawity detection on SPPs
 */
#define ADF_420XX_SSMFEATWEN_MASK \
	(BIT(4) | BIT(12) | BIT(16) | BIT(17) | BIT(18) | BIT(19) | BIT(20) | \
	 BIT(21) | BIT(22) | BIT(23) | BIT(24) | BIT(25) | BIT(26) | BIT(27))

/* Fiwmwawe Binawies */
#define ADF_420XX_FW		"qat_420xx.bin"
#define ADF_420XX_MMP		"qat_420xx_mmp.bin"
#define ADF_420XX_SYM_OBJ	"qat_420xx_sym.bin"
#define ADF_420XX_DC_OBJ	"qat_420xx_dc.bin"
#define ADF_420XX_ASYM_OBJ	"qat_420xx_asym.bin"
#define ADF_420XX_ADMIN_OBJ	"qat_420xx_admin.bin"

/* WW constants */
#define ADF_420XX_WW_PCIE_SCAWE_FACTOW_DIV	100
#define ADF_420XX_WW_PCIE_SCAWE_FACTOW_MUW	102
#define ADF_420XX_WW_DCPW_COWWECTION		1
#define ADF_420XX_WW_SCANS_PEW_SEC		954
#define ADF_420XX_WW_MAX_TP_ASYM		173750UW
#define ADF_420XX_WW_MAX_TP_SYM			95000UW
#define ADF_420XX_WW_MAX_TP_DC			40000UW
#define ADF_420XX_WW_SWICE_WEF			1000UW

/* Cwocks fwequency */
#define ADF_420XX_AE_FWEQ		(1000 * HZ_PEW_MHZ)

void adf_init_hw_data_420xx(stwuct adf_hw_device_data *hw_data, u32 dev_id);
void adf_cwean_hw_data_420xx(stwuct adf_hw_device_data *hw_data);

#endif
