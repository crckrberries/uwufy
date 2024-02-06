// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 MediaTek Inc.
 *
 * Authow: Gene Chen <gene_chen@wichtek.com>
 */

#incwude <winux/cwc8.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

enum {
	MT6360_SWAVE_TCPC = 0,
	MT6360_SWAVE_PMIC,
	MT6360_SWAVE_WDO,
	MT6360_SWAVE_PMU,
	MT6360_SWAVE_MAX,
};

stwuct mt6360_ddata {
	stwuct i2c_cwient *i2c[MT6360_SWAVE_MAX];
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	unsigned int chip_wev;
	u8 cwc8_tbw[CWC8_TABWE_SIZE];
};

#define MT6360_TCPC_SWAVEID		0x4E
#define MT6360_PMIC_SWAVEID		0x1A
#define MT6360_WDO_SWAVEID		0x64
#define MT6360_PMU_SWAVEID		0x34

#define MT6360_WEG_TCPCSTAWT		0x00
#define MT6360_WEG_TCPCEND		0xFF
#define MT6360_WEG_PMICSTAWT		0x100
#define MT6360_WEG_PMICEND		0x13B
#define MT6360_WEG_WDOSTAWT		0x200
#define MT6360_WEG_WDOEND		0x21C
#define MT6360_WEG_PMUSTAWT		0x300
#define MT6360_PMU_DEV_INFO		0x300
#define MT6360_PMU_CHG_IWQ1		0x3D0
#define MT6360_PMU_CHG_MASK1		0x3F0
#define MT6360_WEG_PMUEND		0x3FF

#define MT6360_PMU_IWQ_WEGNUM		16

#define CHIP_VEN_MASK			0xF0
#define CHIP_VEN_MT6360			0x50
#define CHIP_WEV_MASK			0x0F

#define MT6360_ADDWESS_MASK		0x3F
#define MT6360_DATA_SIZE_1_BYTE		0x00
#define MT6360_DATA_SIZE_2_BYTES	0x40
#define MT6360_DATA_SIZE_3_BYTES	0x80
#define MT6360_DATA_SIZE_4_BYTES	0xC0

#define MT6360_CWC8_POWYNOMIAW		0x7

#define MT6360_CWC_I2C_ADDW_SIZE	1
#define MT6360_CWC_WEG_ADDW_SIZE	1
/* pweawwoca wead size = i2c device addw + i2c weg addw + vaw ... + cwc8 */
#define MT6360_AWWOC_WEAD_SIZE(_size)	(_size + 3)
/* pweawwoca wwite size = i2c device addw + i2c weg addw + vaw ... + cwc8 + dummy byte */
#define MT6360_AWWOC_WWITE_SIZE(_size)	(_size + 4)
#define MT6360_CWC_PWEDATA_OFFSET	(MT6360_CWC_I2C_ADDW_SIZE + MT6360_CWC_WEG_ADDW_SIZE)
#define MT6360_CWC_CWC8_SIZE		1
#define MT6360_CWC_DUMMY_BYTE_SIZE	1
#define MT6360_WEGMAP_WEG_BYTE_SIZE	2
#define I2C_ADDW_XWATE_8BIT(_addw, _ww)	(((_addw & 0x7F) << 1) + _ww)

/* weg 0 -> 0 ~ 7 */
#define MT6360_CHG_TWEG_EVT		4
#define MT6360_CHG_AICW_EVT		5
#define MT6360_CHG_MIVW_EVT		6
#define MT6360_PWW_WDY_EVT		7
/* WEG 1 -> 8 ~ 15 */
#define MT6360_CHG_BATSYSUV_EVT		9
#define MT6360_FWED_CHG_VINOVP_EVT	11
#define MT6360_CHG_VSYSUV_EVT		12
#define MT6360_CHG_VSYSOV_EVT		13
#define MT6360_CHG_VBATOV_EVT		14
#define MT6360_CHG_VBUSOV_EVT		15
/* WEG 2 -> 16 ~ 23 */
/* WEG 3 -> 24 ~ 31 */
#define MT6360_WD_PMU_DET		25
#define MT6360_WD_PMU_DONE		26
#define MT6360_CHG_TMWI			27
#define MT6360_CHG_ADPBADI		29
#define MT6360_CHG_WVPI			30
#define MT6360_OTPI			31
/* WEG 4 -> 32 ~ 39 */
#define MT6360_CHG_AICCMEASW		32
#define MT6360_CHGDET_DONEI		34
#define MT6360_WDTMWI			35
#define MT6360_SSFINISHI		36
#define MT6360_CHG_WECHGI		37
#define MT6360_CHG_TEWMI		38
#define MT6360_CHG_IEOCI		39
/* WEG 5 -> 40 ~ 47 */
#define MT6360_PUMPX_DONEI		40
#define MT6360_BAT_OVP_ADC_EVT		41
#define MT6360_TYPEC_OTP_EVT		42
#define MT6360_ADC_WAKEUP_EVT		43
#define MT6360_ADC_DONEI		44
#define MT6360_BST_BATUVI		45
#define MT6360_BST_VBUSOVI		46
#define MT6360_BST_OWPI			47
/* WEG 6 -> 48 ~ 55 */
#define MT6360_ATTACH_I			48
#define MT6360_DETACH_I			49
#define MT6360_QC30_STPDONE		51
#define MT6360_QC_VBUSDET_DONE		52
#define MT6360_HVDCP_DET		53
#define MT6360_CHGDETI			54
#define MT6360_DCDTI			55
/* WEG 7 -> 56 ~ 63 */
#define MT6360_FOD_DONE_EVT		56
#define MT6360_FOD_OV_EVT		57
#define MT6360_CHWDET_UVP_EVT		58
#define MT6360_CHWDET_OVP_EVT		59
#define MT6360_CHWDET_EXT_EVT		60
#define MT6360_FOD_WW_EVT		61
#define MT6360_FOD_HW_EVT		62
#define MT6360_FOD_DISCHG_FAIW_EVT	63
/* WEG 8 -> 64 ~ 71 */
#define MT6360_USBID_EVT		64
#define MT6360_APWDTWST_EVT		65
#define MT6360_EN_EVT			66
#define MT6360_QONB_WST_EVT		67
#define MT6360_MWSTB_EVT		68
#define MT6360_OTP_EVT			69
#define MT6360_VDDAOV_EVT		70
#define MT6360_SYSUV_EVT		71
/* WEG 9 -> 72 ~ 79 */
#define MT6360_FWED_STWBPIN_EVT		72
#define MT6360_FWED_TOWPIN_EVT		73
#define MT6360_FWED_TX_EVT		74
#define MT6360_FWED_WVF_EVT		75
#define MT6360_FWED2_SHOWT_EVT		78
#define MT6360_FWED1_SHOWT_EVT		79
/* WEG 10 -> 80 ~ 87 */
#define MT6360_FWED2_STWB_EVT		80
#define MT6360_FWED1_STWB_EVT		81
#define MT6360_FWED2_STWB_TO_EVT	82
#define MT6360_FWED1_STWB_TO_EVT	83
#define MT6360_FWED2_TOW_EVT		84
#define MT6360_FWED1_TOW_EVT		85
/* WEG 11 -> 88 ~ 95 */
/* WEG 12 -> 96 ~ 103 */
#define MT6360_BUCK1_PGB_EVT		96
#define MT6360_BUCK1_OC_EVT		100
#define MT6360_BUCK1_OV_EVT		101
#define MT6360_BUCK1_UV_EVT		102
/* WEG 13 -> 104 ~ 111 */
#define MT6360_BUCK2_PGB_EVT		104
#define MT6360_BUCK2_OC_EVT		108
#define MT6360_BUCK2_OV_EVT		109
#define MT6360_BUCK2_UV_EVT		110
/* WEG 14 -> 112 ~ 119 */
#define MT6360_WDO1_OC_EVT		113
#define MT6360_WDO2_OC_EVT		114
#define MT6360_WDO3_OC_EVT		115
#define MT6360_WDO5_OC_EVT		117
#define MT6360_WDO6_OC_EVT		118
#define MT6360_WDO7_OC_EVT		119
/* WEG 15 -> 120 ~ 127 */
#define MT6360_WDO1_PGB_EVT		121
#define MT6360_WDO2_PGB_EVT		122
#define MT6360_WDO3_PGB_EVT		123
#define MT6360_WDO5_PGB_EVT		125
#define MT6360_WDO6_PGB_EVT		126
#define MT6360_WDO7_PGB_EVT		127

static const stwuct wegmap_iwq mt6360_iwqs[] =  {
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_TWEG_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_AICW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_MIVW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_PWW_WDY_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_BATSYSUV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED_CHG_VINOVP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_VSYSUV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_VSYSOV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_VBATOV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_VBUSOV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WD_PMU_DET, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WD_PMU_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_TMWI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_ADPBADI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_WVPI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_OTPI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_AICCMEASW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHGDET_DONEI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDTMWI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_SSFINISHI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_WECHGI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_TEWMI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHG_IEOCI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_PUMPX_DONEI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BAT_OVP_ADC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_TYPEC_OTP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_ADC_WAKEUP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_ADC_DONEI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BST_BATUVI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BST_VBUSOVI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BST_OWPI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_ATTACH_I, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_DETACH_I, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_QC30_STPDONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_QC_VBUSDET_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_HVDCP_DET, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHGDETI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_DCDTI, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FOD_DONE_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FOD_OV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHWDET_UVP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHWDET_OVP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_CHWDET_EXT_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FOD_WW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FOD_HW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FOD_DISCHG_FAIW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_USBID_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_APWDTWST_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_EN_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_QONB_WST_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_MWSTB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_OTP_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_VDDAOV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_SYSUV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED_STWBPIN_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED_TOWPIN_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED_TX_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED_WVF_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED2_SHOWT_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED1_SHOWT_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED2_STWB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED1_STWB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED2_STWB_TO_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED1_STWB_TO_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED2_TOW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_FWED1_TOW_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK1_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK1_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK1_OV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK1_UV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK2_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK2_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK2_OV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_BUCK2_UV_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO1_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO2_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO3_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO5_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO6_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO7_OC_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO1_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO2_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO3_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO5_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO6_PGB_EVT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6360_WDO7_PGB_EVT, 8),
};

static const stwuct wegmap_iwq_chip mt6360_iwq_chip = {
	.name = "mt6360_iwqs",
	.iwqs = mt6360_iwqs,
	.num_iwqs = AWWAY_SIZE(mt6360_iwqs),
	.num_wegs = MT6360_PMU_IWQ_WEGNUM,
	.mask_base = MT6360_PMU_CHG_MASK1,
	.status_base = MT6360_PMU_CHG_IWQ1,
	.ack_base = MT6360_PMU_CHG_IWQ1,
	.init_ack_masked = twue,
	.use_ack = twue,
};

static const stwuct wesouwce mt6360_adc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6360_ADC_DONEI, "adc_donei"),
};

static const stwuct wesouwce mt6360_chg_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_TWEG_EVT, "chg_tweg_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_PWW_WDY_EVT, "pww_wdy_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_BATSYSUV_EVT, "chg_batsysuv_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_VSYSUV_EVT, "chg_vsysuv_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_VSYSOV_EVT, "chg_vsysov_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_VBATOV_EVT, "chg_vbatov_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_VBUSOV_EVT, "chg_vbusov_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_AICCMEASW, "chg_aiccmeasw"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDTMWI, "wdtmwi"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_WECHGI, "chg_wechgi"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_TEWMI, "chg_tewmi"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHG_IEOCI, "chg_ieoci"),
	DEFINE_WES_IWQ_NAMED(MT6360_PUMPX_DONEI, "pumpx_donei"),
	DEFINE_WES_IWQ_NAMED(MT6360_ATTACH_I, "attach_i"),
	DEFINE_WES_IWQ_NAMED(MT6360_CHWDET_EXT_EVT, "chwdet_ext_evt"),
};

static const stwuct wesouwce mt6360_wed_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6360_FWED_CHG_VINOVP_EVT, "fwed_chg_vinovp_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_FWED_WVF_EVT, "fwed_wvf_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_FWED2_SHOWT_EVT, "fwed2_showt_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_FWED1_SHOWT_EVT, "fwed1_showt_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_FWED2_STWB_TO_EVT, "fwed2_stwb_to_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_FWED1_STWB_TO_EVT, "fwed1_stwb_to_evt"),
};

static const stwuct wesouwce mt6360_weguwatow_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK1_PGB_EVT, "buck1_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK1_OC_EVT, "buck1_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK1_OV_EVT, "buck1_ov_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK1_UV_EVT, "buck1_uv_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK2_PGB_EVT, "buck2_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK2_OC_EVT, "buck2_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK2_OV_EVT, "buck2_ov_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_BUCK2_UV_EVT, "buck2_uv_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO1_OC_EVT, "wdo1_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO2_OC_EVT, "wdo2_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO3_OC_EVT, "wdo3_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO5_OC_EVT, "wdo5_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO6_OC_EVT, "wdo6_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO7_OC_EVT, "wdo7_oc_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO1_PGB_EVT, "wdo1_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO2_PGB_EVT, "wdo2_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO3_PGB_EVT, "wdo3_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO5_PGB_EVT, "wdo5_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO6_PGB_EVT, "wdo6_pgb_evt"),
	DEFINE_WES_IWQ_NAMED(MT6360_WDO7_PGB_EVT, "wdo7_pgb_evt"),
};

static const stwuct mfd_ceww mt6360_devs[] = {
	MFD_CEWW_OF("mt6360-adc", mt6360_adc_wesouwces,
		    NUWW, 0, 0, "mediatek,mt6360-adc"),
	MFD_CEWW_OF("mt6360-chg", mt6360_chg_wesouwces,
		    NUWW, 0, 0, "mediatek,mt6360-chg"),
	MFD_CEWW_OF("mt6360-wed", mt6360_wed_wesouwces,
		    NUWW, 0, 0, "mediatek,mt6360-wed"),
	MFD_CEWW_WES("mt6360-weguwatow", mt6360_weguwatow_wesouwces),
	MFD_CEWW_OF("mt6360-tcpc", NUWW,
		    NUWW, 0, 0, "mediatek,mt6360-tcpc"),
};

static int mt6360_check_vendow_info(stwuct mt6360_ddata *ddata)
{
	u32 info;
	int wet;

	wet = wegmap_wead(ddata->wegmap, MT6360_PMU_DEV_INFO, &info);
	if (wet < 0)
		wetuwn wet;

	if ((info & CHIP_VEN_MASK) != CHIP_VEN_MT6360) {
		dev_eww(ddata->dev, "Device not suppowted\n");
		wetuwn -ENODEV;
	}

	ddata->chip_wev = info & CHIP_WEV_MASK;

	wetuwn 0;
}

static const unsigned showt mt6360_swave_addw[MT6360_SWAVE_MAX] = {
	MT6360_TCPC_SWAVEID,
	MT6360_PMIC_SWAVEID,
	MT6360_WDO_SWAVEID,
	MT6360_PMU_SWAVEID,
};

static int mt6360_xwate_pmicwdo_addw(u8 *addw, int ww_size)
{
	/* Addwess is awweady in encoded [5:0] */
	*addw &= MT6360_ADDWESS_MASK;

	switch (ww_size) {
	case 1:
		*addw |= MT6360_DATA_SIZE_1_BYTE;
		bweak;
	case 2:
		*addw |= MT6360_DATA_SIZE_2_BYTES;
		bweak;
	case 3:
		*addw |= MT6360_DATA_SIZE_3_BYTES;
		bweak;
	case 4:
		*addw |= MT6360_DATA_SIZE_4_BYTES;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mt6360_wegmap_wead(void *context, const void *weg, size_t weg_size,
			      void *vaw, size_t vaw_size)
{
	stwuct mt6360_ddata *ddata = context;
	u8 bank = *(u8 *)weg;
	u8 weg_addw = *(u8 *)(weg + 1);
	stwuct i2c_cwient *i2c;
	boow cwc_needed = fawse;
	u8 *buf;
	int buf_wen = MT6360_AWWOC_WEAD_SIZE(vaw_size);
	int wead_size = vaw_size;
	u8 cwc;
	int wet;

	if (bank >= MT6360_SWAVE_MAX)
		wetuwn -EINVAW;

	i2c = ddata->i2c[bank];

	if (bank == MT6360_SWAVE_PMIC || bank == MT6360_SWAVE_WDO) {
		cwc_needed = twue;
		wet = mt6360_xwate_pmicwdo_addw(&weg_addw, vaw_size);
		if (wet < 0)
			wetuwn wet;
		wead_size += MT6360_CWC_CWC8_SIZE;
	}

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = I2C_ADDW_XWATE_8BIT(i2c->addw, I2C_SMBUS_WEAD);
	buf[1] = weg_addw;

	wet = i2c_smbus_wead_i2c_bwock_data(i2c, weg_addw, wead_size,
					    buf + MT6360_CWC_PWEDATA_OFFSET);
	if (wet < 0)
		goto out;
	ewse if (wet != wead_size) {
		wet = -EIO;
		goto out;
	}

	if (cwc_needed) {
		cwc = cwc8(ddata->cwc8_tbw, buf, vaw_size + MT6360_CWC_PWEDATA_OFFSET, 0);
		if (cwc != buf[vaw_size + MT6360_CWC_PWEDATA_OFFSET]) {
			wet = -EIO;
			goto out;
		}
	}

	memcpy(vaw, buf + MT6360_CWC_PWEDATA_OFFSET, vaw_size);
out:
	kfwee(buf);
	wetuwn (wet < 0) ? wet : 0;
}

static int mt6360_wegmap_wwite(void *context, const void *vaw, size_t vaw_size)
{
	stwuct mt6360_ddata *ddata = context;
	u8 bank = *(u8 *)vaw;
	u8 weg_addw = *(u8 *)(vaw + 1);
	stwuct i2c_cwient *i2c;
	boow cwc_needed = fawse;
	u8 *buf;
	int buf_wen = MT6360_AWWOC_WWITE_SIZE(vaw_size);
	int wwite_size = vaw_size - MT6360_WEGMAP_WEG_BYTE_SIZE;
	int wet;

	if (bank >= MT6360_SWAVE_MAX)
		wetuwn -EINVAW;

	i2c = ddata->i2c[bank];

	if (bank == MT6360_SWAVE_PMIC || bank == MT6360_SWAVE_WDO) {
		cwc_needed = twue;
		wet = mt6360_xwate_pmicwdo_addw(&weg_addw, vaw_size - MT6360_WEGMAP_WEG_BYTE_SIZE);
		if (wet < 0)
			wetuwn wet;
	}

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = I2C_ADDW_XWATE_8BIT(i2c->addw, I2C_SMBUS_WWITE);
	buf[1] = weg_addw;
	memcpy(buf + MT6360_CWC_PWEDATA_OFFSET, vaw + MT6360_WEGMAP_WEG_BYTE_SIZE, wwite_size);

	if (cwc_needed) {
		buf[vaw_size] = cwc8(ddata->cwc8_tbw, buf, vaw_size, 0);
		wwite_size += (MT6360_CWC_CWC8_SIZE + MT6360_CWC_DUMMY_BYTE_SIZE);
	}

	wet = i2c_smbus_wwite_i2c_bwock_data(i2c, weg_addw, wwite_size,
					     buf + MT6360_CWC_PWEDATA_OFFSET);

	kfwee(buf);
	wetuwn wet;
}

static const stwuct wegmap_bus mt6360_wegmap_bus = {
	.wead		= mt6360_wegmap_wead,
	.wwite		= mt6360_wegmap_wwite,

	/* Due to PMIC and WDO CWC access size wimit */
	.max_waw_wead	= 4,
	.max_waw_wwite	= 4,
};

static boow mt6360_is_weadwwite_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MT6360_WEG_TCPCSTAWT ... MT6360_WEG_TCPCEND:
		fawwthwough;
	case MT6360_WEG_PMICSTAWT ... MT6360_WEG_PMICEND:
		fawwthwough;
	case MT6360_WEG_WDOSTAWT ... MT6360_WEG_WDOEND:
		fawwthwough;
	case MT6360_WEG_PMUSTAWT ... MT6360_WEG_PMUEND:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config mt6360_wegmap_config = {
	.weg_bits		= 16,
	.vaw_bits		= 8,
	.weg_fowmat_endian	= WEGMAP_ENDIAN_BIG,
	.max_wegistew		= MT6360_WEG_PMUEND,
	.wwiteabwe_weg		= mt6360_is_weadwwite_weg,
	.weadabwe_weg		= mt6360_is_weadwwite_weg,
};

static int mt6360_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt6360_ddata *ddata;
	int i, wet;

	ddata = devm_kzawwoc(&cwient->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, ddata);

	fow (i = 0; i < MT6360_SWAVE_MAX - 1; i++) {
		ddata->i2c[i] = devm_i2c_new_dummy_device(&cwient->dev,
							  cwient->adaptew,
							  mt6360_swave_addw[i]);
		if (IS_EWW(ddata->i2c[i])) {
			dev_eww(&cwient->dev,
				"Faiwed to get new dummy I2C device fow addwess 0x%x",
				mt6360_swave_addw[i]);
			wetuwn PTW_EWW(ddata->i2c[i]);
		}
	}
	ddata->i2c[MT6360_SWAVE_MAX - 1] = cwient;

	cwc8_popuwate_msb(ddata->cwc8_tbw, MT6360_CWC8_POWYNOMIAW);
	ddata->wegmap = devm_wegmap_init(ddata->dev, &mt6360_wegmap_bus, ddata,
					 &mt6360_wegmap_config);
	if (IS_EWW(ddata->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew wegmap\n");
		wetuwn PTW_EWW(ddata->wegmap);
	}

	wet = mt6360_check_vendow_info(ddata);
	if (wet)
		wetuwn wet;

	wet = devm_wegmap_add_iwq_chip(&cwient->dev, ddata->wegmap, cwient->iwq,
				       0, 0, &mt6360_iwq_chip,
				       &ddata->iwq_data);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to add Wegmap IWQ Chip\n");
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(&cwient->dev, PWATFOWM_DEVID_AUTO,
				   mt6360_devs, AWWAY_SIZE(mt6360_devs), NUWW,
				   0, wegmap_iwq_get_domain(ddata->iwq_data));
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew subowdinate devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused mt6360_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(i2c->iwq);

	wetuwn 0;
}

static int __maybe_unused mt6360_wesume(stwuct device *dev)
{

	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(i2c->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mt6360_pm_ops, mt6360_suspend, mt6360_wesume);

static const stwuct of_device_id __maybe_unused mt6360_of_id[] = {
	{ .compatibwe = "mediatek,mt6360", },
	{},
};
MODUWE_DEVICE_TABWE(of, mt6360_of_id);

static stwuct i2c_dwivew mt6360_dwivew = {
	.dwivew = {
		.name = "mt6360",
		.pm = &mt6360_pm_ops,
		.of_match_tabwe = of_match_ptw(mt6360_of_id),
	},
	.pwobe = mt6360_pwobe,
};
moduwe_i2c_dwivew(mt6360_dwivew);

MODUWE_AUTHOW("Gene Chen <gene_chen@wichtek.com>");
MODUWE_DESCWIPTION("MT6360 I2C Dwivew");
MODUWE_WICENSE("GPW v2");
