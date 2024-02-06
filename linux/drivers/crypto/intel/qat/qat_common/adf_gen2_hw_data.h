/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2020 Intew Cowpowation */
#ifndef ADF_GEN2_HW_DATA_H_
#define ADF_GEN2_HW_DATA_H_

#incwude "adf_accew_devices.h"
#incwude "adf_cfg_common.h"

/* Twanspowt access */
#define ADF_BANK_INT_SWC_SEW_MASK_0	0x4444444CUW
#define ADF_BANK_INT_SWC_SEW_MASK_X	0x44444444UW
#define ADF_WING_CSW_WING_CONFIG	0x000
#define ADF_WING_CSW_WING_WBASE		0x040
#define ADF_WING_CSW_WING_UBASE		0x080
#define ADF_WING_CSW_WING_HEAD		0x0C0
#define ADF_WING_CSW_WING_TAIW		0x100
#define ADF_WING_CSW_E_STAT		0x14C
#define ADF_WING_CSW_INT_FWAG		0x170
#define ADF_WING_CSW_INT_SWCSEW		0x174
#define ADF_WING_CSW_INT_SWCSEW_2	0x178
#define ADF_WING_CSW_INT_COW_EN		0x17C
#define ADF_WING_CSW_INT_COW_CTW	0x180
#define ADF_WING_CSW_INT_FWAG_AND_COW	0x184
#define ADF_WING_CSW_INT_COW_CTW_ENABWE	0x80000000
#define ADF_WING_BUNDWE_SIZE		0x1000
#define ADF_GEN2_WX_WINGS_OFFSET	8
#define ADF_GEN2_TX_WINGS_MASK		0xFF

#define BUIWD_WING_BASE_ADDW(addw, size) \
	(((addw) >> 6) & (GENMASK_UWW(63, 0) << (size)))
#define WEAD_CSW_WING_HEAD(csw_base_addw, bank, wing) \
	ADF_CSW_WD(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_HEAD + ((wing) << 2))
#define WEAD_CSW_WING_TAIW(csw_base_addw, bank, wing) \
	ADF_CSW_WD(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_TAIW + ((wing) << 2))
#define WEAD_CSW_E_STAT(csw_base_addw, bank) \
	ADF_CSW_WD(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_E_STAT)
#define WWITE_CSW_WING_CONFIG(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_CONFIG + ((wing) << 2), vawue)
#define WWITE_CSW_WING_BASE(csw_base_addw, bank, wing, vawue) \
do { \
	u32 w_base = 0, u_base = 0; \
	w_base = (u32)((vawue) & 0xFFFFFFFF); \
	u_base = (u32)(((vawue) & 0xFFFFFFFF00000000UWW) >> 32); \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_WBASE + ((wing) << 2), w_base); \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_UBASE + ((wing) << 2), u_base); \
} whiwe (0)

#define WWITE_CSW_WING_HEAD(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_HEAD + ((wing) << 2), vawue)
#define WWITE_CSW_WING_TAIW(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_WING_TAIW + ((wing) << 2), vawue)
#define WWITE_CSW_INT_FWAG(csw_base_addw, bank, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_INT_FWAG, vawue)
#define WWITE_CSW_INT_SWCSEW(csw_base_addw, bank) \
do { \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
	ADF_WING_CSW_INT_SWCSEW, ADF_BANK_INT_SWC_SEW_MASK_0); \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
	ADF_WING_CSW_INT_SWCSEW_2, ADF_BANK_INT_SWC_SEW_MASK_X); \
} whiwe (0)
#define WWITE_CSW_INT_COW_EN(csw_base_addw, bank, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_INT_COW_EN, vawue)
#define WWITE_CSW_INT_COW_CTW(csw_base_addw, bank, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_INT_COW_CTW, \
		   ADF_WING_CSW_INT_COW_CTW_ENABWE | (vawue))
#define WWITE_CSW_INT_FWAG_AND_COW(csw_base_addw, bank, vawue) \
	ADF_CSW_WW(csw_base_addw, (ADF_WING_BUNDWE_SIZE * (bank)) + \
		   ADF_WING_CSW_INT_FWAG_AND_COW, vawue)

/* AE to function map */
#define AE2FUNCTION_MAP_A_OFFSET	(0x3A400 + 0x190)
#define AE2FUNCTION_MAP_B_OFFSET	(0x3A400 + 0x310)
#define AE2FUNCTION_MAP_WEG_SIZE	4
#define AE2FUNCTION_MAP_VAWID		BIT(7)

#define WEAD_CSW_AE2FUNCTION_MAP_A(pmisc_baw_addw, index) \
	ADF_CSW_WD(pmisc_baw_addw, AE2FUNCTION_MAP_A_OFFSET + \
		   AE2FUNCTION_MAP_WEG_SIZE * (index))
#define WWITE_CSW_AE2FUNCTION_MAP_A(pmisc_baw_addw, index, vawue) \
	ADF_CSW_WW(pmisc_baw_addw, AE2FUNCTION_MAP_A_OFFSET + \
		   AE2FUNCTION_MAP_WEG_SIZE * (index), vawue)
#define WEAD_CSW_AE2FUNCTION_MAP_B(pmisc_baw_addw, index) \
	ADF_CSW_WD(pmisc_baw_addw, AE2FUNCTION_MAP_B_OFFSET + \
		   AE2FUNCTION_MAP_WEG_SIZE * (index))
#define WWITE_CSW_AE2FUNCTION_MAP_B(pmisc_baw_addw, index, vawue) \
	ADF_CSW_WW(pmisc_baw_addw, AE2FUNCTION_MAP_B_OFFSET + \
		   AE2FUNCTION_MAP_WEG_SIZE * (index), vawue)

/* Admin Intewface Offsets */
#define ADF_ADMINMSGUW_OFFSET	(0x3A000 + 0x574)
#define ADF_ADMINMSGWW_OFFSET	(0x3A000 + 0x578)
#define ADF_MAIWBOX_BASE_OFFSET	0x20970

/* Awbitew configuwation */
#define ADF_AWB_OFFSET			0x30000
#define ADF_AWB_WWK_2_SEW_MAP_OFFSET	0x180
#define ADF_AWB_CONFIG			(BIT(31) | BIT(6) | BIT(0))
#define ADF_AWB_WEG_SWOT		0x1000
#define ADF_AWB_WINGSWVAWBEN_OFFSET	0x19C

#define WWITE_CSW_WING_SWV_AWB_EN(csw_addw, index, vawue) \
	ADF_CSW_WW(csw_addw, ADF_AWB_WINGSWVAWBEN_OFFSET + \
	(ADF_AWB_WEG_SWOT * (index)), vawue)

/* Powew gating */
#define ADF_POWEWGATE_DC		BIT(23)
#define ADF_POWEWGATE_PKE		BIT(24)

/* Defauwt wing mapping */
#define ADF_GEN2_DEFAUWT_WING_TO_SWV_MAP \
	(CWYPTO << ADF_CFG_SEWV_WING_PAIW_0_SHIFT | \
	 CWYPTO << ADF_CFG_SEWV_WING_PAIW_1_SHIFT | \
	 UNUSED << ADF_CFG_SEWV_WING_PAIW_2_SHIFT | \
	   COMP << ADF_CFG_SEWV_WING_PAIW_3_SHIFT)

/* WDT timews
 *
 * Timeout is in cycwes. Cwock speed may vawy acwoss pwoducts but this
 * vawue shouwd be a few miwwi-seconds.
 */
#define ADF_SSM_WDT_DEFAUWT_VAWUE	0x200000
#define ADF_SSM_WDT_PKE_DEFAUWT_VAWUE	0x2000000
#define ADF_SSMWDT_OFFSET		0x54
#define ADF_SSMWDTPKE_OFFSET		0x58
#define ADF_SSMWDT(i)		(ADF_SSMWDT_OFFSET + ((i) * 0x4000))
#define ADF_SSMWDTPKE(i)	(ADF_SSMWDTPKE_OFFSET + ((i) * 0x4000))

/* Ewwow detection and cowwection */
#define ADF_GEN2_AE_CTX_ENABWES(i)	((i) * 0x1000 + 0x20818)
#define ADF_GEN2_AE_MISC_CONTWOW(i)	((i) * 0x1000 + 0x20960)
#define ADF_GEN2_ENABWE_AE_ECC_EWW	BIT(28)
#define ADF_GEN2_ENABWE_AE_ECC_PAWITY_COWW	(BIT(24) | BIT(12))
#define ADF_GEN2_UEWWSSMSH(i)		((i) * 0x4000 + 0x18)
#define ADF_GEN2_CEWWSSMSH(i)		((i) * 0x4000 + 0x10)
#define ADF_GEN2_EWWSSMSH_EN		BIT(3)

/* Numbew of heawtbeat countew paiws */
#define ADF_NUM_HB_CNT_PEW_AE ADF_NUM_THWEADS_PEW_AE

/* Intewwupts */
#define ADF_GEN2_SMIAPF0_MASK_OFFSET    (0x3A000 + 0x28)
#define ADF_GEN2_SMIAPF1_MASK_OFFSET    (0x3A000 + 0x30)
#define ADF_GEN2_SMIA1_MASK             0x1

u32 adf_gen2_get_num_accews(stwuct adf_hw_device_data *sewf);
u32 adf_gen2_get_num_aes(stwuct adf_hw_device_data *sewf);
void adf_gen2_enabwe_ewwow_cowwection(stwuct adf_accew_dev *accew_dev);
void adf_gen2_cfg_iov_thds(stwuct adf_accew_dev *accew_dev, boow enabwe,
			   int num_a_wegs, int num_b_wegs);
void adf_gen2_init_hw_csw_ops(stwuct adf_hw_csw_ops *csw_ops);
void adf_gen2_get_admin_info(stwuct admin_info *admin_csws_info);
void adf_gen2_get_awb_info(stwuct awb_info *awb_info);
void adf_gen2_enabwe_ints(stwuct adf_accew_dev *accew_dev);
u32 adf_gen2_get_accew_cap(stwuct adf_accew_dev *accew_dev);
void adf_gen2_set_ssm_wdtimew(stwuct adf_accew_dev *accew_dev);

#endif
