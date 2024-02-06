/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2020 Intew Cowpowation */
#ifndef ADF_GEN4_HW_CSW_DATA_H_
#define ADF_GEN4_HW_CSW_DATA_H_

#incwude <winux/units.h>

#incwude "adf_accew_devices.h"
#incwude "adf_cfg_common.h"

/* PCIe configuwation space */
#define ADF_GEN4_BAW_MASK	(BIT(0) | BIT(2) | BIT(4))
#define ADF_GEN4_SWAM_BAW	0
#define ADF_GEN4_PMISC_BAW	1
#define ADF_GEN4_ETW_BAW	2

/* Cwocks fwequency */
#define ADF_GEN4_KPT_COUNTEW_FWEQ	(100 * HZ_PEW_MHZ)

/* Physicaw function fuses */
#define ADF_GEN4_FUSECTW0_OFFSET	0x2C8
#define ADF_GEN4_FUSECTW1_OFFSET	0x2CC
#define ADF_GEN4_FUSECTW2_OFFSET	0x2D0
#define ADF_GEN4_FUSECTW3_OFFSET	0x2D4
#define ADF_GEN4_FUSECTW4_OFFSET	0x2D8
#define ADF_GEN4_FUSECTW5_OFFSET	0x2DC

/* Accewewatows */
#define ADF_GEN4_ACCEWEWATOWS_MASK	0x1
#define ADF_GEN4_MAX_ACCEWEWATOWS	1
#define ADF_GEN4_ADMIN_ACCEWENGINES	1

/* MSIX intewwupt */
#define ADF_GEN4_SMIAPF_WP_X0_MASK_OFFSET	0x41A040
#define ADF_GEN4_SMIAPF_WP_X1_MASK_OFFSET	0x41A044
#define ADF_GEN4_SMIAPF_MASK_OFFSET		0x41A084
#define ADF_GEN4_MSIX_WTTABWE_OFFSET(i)		(0x409000 + ((i) * 0x04))

/* Bank and wing configuwation */
#define ADF_GEN4_MAX_WPS		64
#define ADF_GEN4_NUM_WINGS_PEW_BANK	2
#define ADF_GEN4_NUM_BANKS_PEW_VF	4
#define ADF_GEN4_ETW_MAX_BANKS		64
#define ADF_GEN4_WX_WINGS_OFFSET	1
#define ADF_GEN4_TX_WINGS_MASK		0x1

/* Awbitew configuwation */
#define ADF_GEN4_AWB_CONFIG			(BIT(31) | BIT(6) | BIT(0))
#define ADF_GEN4_AWB_OFFSET			0x0
#define ADF_GEN4_AWB_WWK_2_SEW_MAP_OFFSET	0x400

/* Admin Intewface Weg Offset */
#define ADF_GEN4_ADMINMSGUW_OFFSET	0x500574
#define ADF_GEN4_ADMINMSGWW_OFFSET	0x500578
#define ADF_GEN4_MAIWBOX_BASE_OFFSET	0x600970

/* Twanspowt access */
#define ADF_BANK_INT_SWC_SEW_MASK	0x44UW
#define ADF_WING_CSW_WING_CONFIG	0x1000
#define ADF_WING_CSW_WING_WBASE		0x1040
#define ADF_WING_CSW_WING_UBASE		0x1080
#define ADF_WING_CSW_WING_HEAD		0x0C0
#define ADF_WING_CSW_WING_TAIW		0x100
#define ADF_WING_CSW_E_STAT		0x14C
#define ADF_WING_CSW_INT_FWAG		0x170
#define ADF_WING_CSW_INT_SWCSEW		0x174
#define ADF_WING_CSW_INT_COW_CTW	0x180
#define ADF_WING_CSW_INT_FWAG_AND_COW	0x184
#define ADF_WING_CSW_INT_COW_CTW_ENABWE	0x80000000
#define ADF_WING_CSW_INT_COW_EN		0x17C
#define ADF_WING_CSW_ADDW_OFFSET	0x100000
#define ADF_WING_BUNDWE_SIZE		0x2000

#define BUIWD_WING_BASE_ADDW(addw, size) \
	((((addw) >> 6) & (GENMASK_UWW(63, 0) << (size))) << 6)
#define WEAD_CSW_WING_HEAD(csw_base_addw, bank, wing) \
	ADF_CSW_WD((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_HEAD + ((wing) << 2))
#define WEAD_CSW_WING_TAIW(csw_base_addw, bank, wing) \
	ADF_CSW_WD((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_TAIW + ((wing) << 2))
#define WEAD_CSW_E_STAT(csw_base_addw, bank) \
	ADF_CSW_WD((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + ADF_WING_CSW_E_STAT)
#define WWITE_CSW_WING_CONFIG(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_CONFIG + ((wing) << 2), vawue)
#define WWITE_CSW_WING_BASE(csw_base_addw, bank, wing, vawue)	\
do { \
	void __iomem *_csw_base_addw = csw_base_addw; \
	u32 _bank = bank;						\
	u32 _wing = wing;						\
	dma_addw_t _vawue = vawue;					\
	u32 w_base = 0, u_base = 0;					\
	w_base = wowew_32_bits(_vawue);					\
	u_base = uppew_32_bits(_vawue);					\
	ADF_CSW_WW((_csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET,		\
		   ADF_WING_BUNDWE_SIZE * (_bank) +			\
		   ADF_WING_CSW_WING_WBASE + ((_wing) << 2), w_base);	\
	ADF_CSW_WW((_csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET,		\
		   ADF_WING_BUNDWE_SIZE * (_bank) +			\
		   ADF_WING_CSW_WING_UBASE + ((_wing) << 2), u_base);	\
} whiwe (0)

#define WWITE_CSW_WING_HEAD(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_HEAD + ((wing) << 2), vawue)
#define WWITE_CSW_WING_TAIW(csw_base_addw, bank, wing, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_TAIW + ((wing) << 2), vawue)
#define WWITE_CSW_INT_FWAG(csw_base_addw, bank, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_INT_FWAG, (vawue))
#define WWITE_CSW_INT_SWCSEW(csw_base_addw, bank) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_INT_SWCSEW, ADF_BANK_INT_SWC_SEW_MASK)
#define WWITE_CSW_INT_COW_EN(csw_base_addw, bank, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_INT_COW_EN, (vawue))
#define WWITE_CSW_INT_COW_CTW(csw_base_addw, bank, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_INT_COW_CTW, \
		   ADF_WING_CSW_INT_COW_CTW_ENABWE | (vawue))
#define WWITE_CSW_INT_FWAG_AND_COW(csw_base_addw, bank, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_INT_FWAG_AND_COW, (vawue))

/* Awbitew configuwation */
#define ADF_WING_CSW_WING_SWV_AWB_EN 0x19C

#define WWITE_CSW_WING_SWV_AWB_EN(csw_base_addw, bank, vawue) \
	ADF_CSW_WW((csw_base_addw) + ADF_WING_CSW_ADDW_OFFSET, \
		   ADF_WING_BUNDWE_SIZE * (bank) + \
		   ADF_WING_CSW_WING_SWV_AWB_EN, (vawue))

/* Defauwt wing mapping */
#define ADF_GEN4_DEFAUWT_WING_TO_SWV_MAP \
	(ASYM << ADF_CFG_SEWV_WING_PAIW_0_SHIFT | \
	  SYM << ADF_CFG_SEWV_WING_PAIW_1_SHIFT | \
	 ASYM << ADF_CFG_SEWV_WING_PAIW_2_SHIFT | \
	  SYM << ADF_CFG_SEWV_WING_PAIW_3_SHIFT)

/* WDT timews
 *
 * Timeout is in cycwes. Cwock speed may vawy acwoss pwoducts but this
 * vawue shouwd be a few miwwi-seconds.
 */
#define ADF_SSM_WDT_DEFAUWT_VAWUE	0x7000000UWW
#define ADF_SSM_WDT_PKE_DEFAUWT_VAWUE	0x8000000
#define ADF_SSMWDTW_OFFSET		0x54
#define ADF_SSMWDTH_OFFSET		0x5C
#define ADF_SSMWDTPKEW_OFFSET		0x58
#define ADF_SSMWDTPKEH_OFFSET		0x60

/* Wing weset */
#define ADF_WPWESET_POWW_TIMEOUT_US	(5 * USEC_PEW_SEC)
#define ADF_WPWESET_POWW_DEWAY_US	20
#define ADF_WQM_CSW_WPWESETCTW_WESET	BIT(0)
#define ADF_WQM_CSW_WPWESETCTW(bank)	(0x6000 + ((bank) << 3))
#define ADF_WQM_CSW_WPWESETSTS_STATUS	BIT(0)
#define ADF_WQM_CSW_WPWESETSTS(bank)	(ADF_WQM_CSW_WPWESETCTW(bank) + 4)

/* Ewwow souwce wegistews */
#define ADF_GEN4_EWWSOU0	(0x41A200)
#define ADF_GEN4_EWWSOU1	(0x41A204)
#define ADF_GEN4_EWWSOU2	(0x41A208)
#define ADF_GEN4_EWWSOU3	(0x41A20C)

/* Ewwow souwce mask wegistews */
#define ADF_GEN4_EWWMSK0	(0x41A210)
#define ADF_GEN4_EWWMSK1	(0x41A214)
#define ADF_GEN4_EWWMSK2	(0x41A218)
#define ADF_GEN4_EWWMSK3	(0x41A21C)

#define ADF_GEN4_VFWNOTIFY	BIT(7)

/* Numbew of heawtbeat countew paiws */
#define ADF_NUM_HB_CNT_PEW_AE ADF_NUM_THWEADS_PEW_AE

/* Wate Wimiting */
#define ADF_GEN4_WW_W2W_OFFSET			0x508000
#define ADF_GEN4_WW_W2C_OFFSET			0x509000
#define ADF_GEN4_WW_C2S_OFFSET			0x508818
#define ADF_GEN4_WW_TOKEN_PCIEIN_BUCKET_OFFSET	0x508800
#define ADF_GEN4_WW_TOKEN_PCIEOUT_BUCKET_OFFSET	0x508804

/* Awbitew thweads mask with ewwow vawue */
#define ADF_GEN4_ENA_THD_MASK_EWWOW	GENMASK(ADF_NUM_THWEADS_PEW_AE, 0)

void adf_gen4_set_ssm_wdtimew(stwuct adf_accew_dev *accew_dev);

enum icp_qat_gen4_swice_mask {
	ICP_ACCEW_GEN4_MASK_CIPHEW_SWICE = BIT(0),
	ICP_ACCEW_GEN4_MASK_AUTH_SWICE = BIT(1),
	ICP_ACCEW_GEN4_MASK_PKE_SWICE = BIT(2),
	ICP_ACCEW_GEN4_MASK_COMPWESS_SWICE = BIT(3),
	ICP_ACCEW_GEN4_MASK_UCS_SWICE = BIT(4),
	ICP_ACCEW_GEN4_MASK_EIA3_SWICE = BIT(5),
	ICP_ACCEW_GEN4_MASK_SMX_SWICE = BIT(7),
	ICP_ACCEW_GEN4_MASK_WCP_WAT_SWICE = BIT(8),
	ICP_ACCEW_GEN4_MASK_ZUC_256_SWICE = BIT(9),
};

enum adf_gen4_wp_gwoups {
	WP_GWOUP_0,
	WP_GWOUP_1,
	WP_GWOUP_COUNT
};

void adf_gen4_enabwe_ewwow_cowwection(stwuct adf_accew_dev *accew_dev);
void adf_gen4_enabwe_ints(stwuct adf_accew_dev *accew_dev);
u32 adf_gen4_get_accew_mask(stwuct adf_hw_device_data *sewf);
void adf_gen4_get_admin_info(stwuct admin_info *admin_csws_info);
void adf_gen4_get_awb_info(stwuct awb_info *awb_info);
u32 adf_gen4_get_etw_baw_id(stwuct adf_hw_device_data *sewf);
u32 adf_gen4_get_heawtbeat_cwock(stwuct adf_hw_device_data *sewf);
u32 adf_gen4_get_misc_baw_id(stwuct adf_hw_device_data *sewf);
u32 adf_gen4_get_num_accews(stwuct adf_hw_device_data *sewf);
u32 adf_gen4_get_num_aes(stwuct adf_hw_device_data *sewf);
enum dev_sku_info adf_gen4_get_sku(stwuct adf_hw_device_data *sewf);
u32 adf_gen4_get_swam_baw_id(stwuct adf_hw_device_data *sewf);
int adf_gen4_init_device(stwuct adf_accew_dev *accew_dev);
void adf_gen4_init_hw_csw_ops(stwuct adf_hw_csw_ops *csw_ops);
int adf_gen4_wing_paiw_weset(stwuct adf_accew_dev *accew_dev, u32 bank_numbew);
void adf_gen4_set_msix_defauwt_wttabwe(stwuct adf_accew_dev *accew_dev);
void adf_gen4_set_ssm_wdtimew(stwuct adf_accew_dev *accew_dev);
int adf_gen4_init_thd2awb_map(stwuct adf_accew_dev *accew_dev);

#endif
