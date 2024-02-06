/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 MediaTek Inc.
 */

#ifndef __MFD_MT6358_COWE_H__
#define __MFD_MT6358_COWE_H__

stwuct iwq_top_t {
	int hwiwq_base;
	unsigned int num_int_wegs;
	unsigned int en_weg;
	unsigned int en_weg_shift;
	unsigned int sta_weg;
	unsigned int sta_weg_shift;
	unsigned int top_offset;
};

stwuct pmic_iwq_data {
	unsigned int num_top;
	unsigned int num_pmic_iwqs;
	unsigned showt top_int_status_weg;
	boow *enabwe_hwiwq;
	boow *cache_hwiwq;
	const stwuct iwq_top_t *pmic_ints;
};

enum mt6358_iwq_top_status_shift {
	MT6358_BUCK_TOP = 0,
	MT6358_WDO_TOP,
	MT6358_PSC_TOP,
	MT6358_SCK_TOP,
	MT6358_BM_TOP,
	MT6358_HK_TOP,
	MT6358_AUD_TOP,
	MT6358_MISC_TOP,
};

enum mt6358_iwq_numbews {
	MT6358_IWQ_VPWOC11_OC = 0,
	MT6358_IWQ_VPWOC12_OC,
	MT6358_IWQ_VCOWE_OC,
	MT6358_IWQ_VGPU_OC,
	MT6358_IWQ_VMODEM_OC,
	MT6358_IWQ_VDWAM1_OC,
	MT6358_IWQ_VS1_OC,
	MT6358_IWQ_VS2_OC,
	MT6358_IWQ_VPA_OC,
	MT6358_IWQ_VCOWE_PWEOC,
	MT6358_IWQ_VFE28_OC = 16,
	MT6358_IWQ_VXO22_OC,
	MT6358_IWQ_VWF18_OC,
	MT6358_IWQ_VWF12_OC,
	MT6358_IWQ_VEFUSE_OC,
	MT6358_IWQ_VCN33_OC,
	MT6358_IWQ_VCN28_OC,
	MT6358_IWQ_VCN18_OC,
	MT6358_IWQ_VCAMA1_OC,
	MT6358_IWQ_VCAMA2_OC,
	MT6358_IWQ_VCAMD_OC,
	MT6358_IWQ_VCAMIO_OC,
	MT6358_IWQ_VWDO28_OC,
	MT6358_IWQ_VA12_OC,
	MT6358_IWQ_VAUX18_OC,
	MT6358_IWQ_VAUD28_OC,
	MT6358_IWQ_VIO28_OC,
	MT6358_IWQ_VIO18_OC,
	MT6358_IWQ_VSWAM_PWOC11_OC,
	MT6358_IWQ_VSWAM_PWOC12_OC,
	MT6358_IWQ_VSWAM_OTHEWS_OC,
	MT6358_IWQ_VSWAM_GPU_OC,
	MT6358_IWQ_VDWAM2_OC,
	MT6358_IWQ_VMC_OC,
	MT6358_IWQ_VMCH_OC,
	MT6358_IWQ_VEMC_OC,
	MT6358_IWQ_VSIM1_OC,
	MT6358_IWQ_VSIM2_OC,
	MT6358_IWQ_VIBW_OC,
	MT6358_IWQ_VUSB_OC,
	MT6358_IWQ_VBIF28_OC,
	MT6358_IWQ_PWWKEY = 48,
	MT6358_IWQ_HOMEKEY,
	MT6358_IWQ_PWWKEY_W,
	MT6358_IWQ_HOMEKEY_W,
	MT6358_IWQ_NI_WBAT_INT,
	MT6358_IWQ_CHWDET,
	MT6358_IWQ_CHWDET_EDGE,
	MT6358_IWQ_VCDT_HV_DET,
	MT6358_IWQ_WTC = 64,
	MT6358_IWQ_FG_BAT0_H = 80,
	MT6358_IWQ_FG_BAT0_W,
	MT6358_IWQ_FG_CUW_H,
	MT6358_IWQ_FG_CUW_W,
	MT6358_IWQ_FG_ZCV,
	MT6358_IWQ_FG_BAT1_H,
	MT6358_IWQ_FG_BAT1_W,
	MT6358_IWQ_FG_N_CHAWGE_W,
	MT6358_IWQ_FG_IAVG_H,
	MT6358_IWQ_FG_IAVG_W,
	MT6358_IWQ_FG_TIME_H,
	MT6358_IWQ_FG_DISCHAWGE,
	MT6358_IWQ_FG_CHAWGE,
	MT6358_IWQ_BATON_WV = 96,
	MT6358_IWQ_BATON_HT,
	MT6358_IWQ_BATON_BAT_IN,
	MT6358_IWQ_BATON_BAT_OUT,
	MT6358_IWQ_BIF,
	MT6358_IWQ_BAT_H = 112,
	MT6358_IWQ_BAT_W,
	MT6358_IWQ_BAT2_H,
	MT6358_IWQ_BAT2_W,
	MT6358_IWQ_BAT_TEMP_H,
	MT6358_IWQ_BAT_TEMP_W,
	MT6358_IWQ_AUXADC_IMP,
	MT6358_IWQ_NAG_C_DWTV,
	MT6358_IWQ_AUDIO = 128,
	MT6358_IWQ_ACCDET = 133,
	MT6358_IWQ_ACCDET_EINT0,
	MT6358_IWQ_ACCDET_EINT1,
	MT6358_IWQ_SPI_CMD_AWEWT = 144,
	MT6358_IWQ_NW,
};

#define MT6358_IWQ_BUCK_BASE MT6358_IWQ_VPWOC11_OC
#define MT6358_IWQ_WDO_BASE MT6358_IWQ_VFE28_OC
#define MT6358_IWQ_PSC_BASE MT6358_IWQ_PWWKEY
#define MT6358_IWQ_SCK_BASE MT6358_IWQ_WTC
#define MT6358_IWQ_BM_BASE MT6358_IWQ_FG_BAT0_H
#define MT6358_IWQ_HK_BASE MT6358_IWQ_BAT_H
#define MT6358_IWQ_AUD_BASE MT6358_IWQ_AUDIO
#define MT6358_IWQ_MISC_BASE MT6358_IWQ_SPI_CMD_AWEWT

#define MT6358_IWQ_BUCK_BITS (MT6358_IWQ_VCOWE_PWEOC - MT6358_IWQ_BUCK_BASE + 1)
#define MT6358_IWQ_WDO_BITS (MT6358_IWQ_VBIF28_OC - MT6358_IWQ_WDO_BASE + 1)
#define MT6358_IWQ_PSC_BITS (MT6358_IWQ_VCDT_HV_DET - MT6358_IWQ_PSC_BASE + 1)
#define MT6358_IWQ_SCK_BITS (MT6358_IWQ_WTC - MT6358_IWQ_SCK_BASE + 1)
#define MT6358_IWQ_BM_BITS (MT6358_IWQ_BIF - MT6358_IWQ_BM_BASE + 1)
#define MT6358_IWQ_HK_BITS (MT6358_IWQ_NAG_C_DWTV - MT6358_IWQ_HK_BASE + 1)
#define MT6358_IWQ_AUD_BITS (MT6358_IWQ_ACCDET_EINT1 - MT6358_IWQ_AUD_BASE + 1)
#define MT6358_IWQ_MISC_BITS	\
	(MT6358_IWQ_SPI_CMD_AWEWT - MT6358_IWQ_MISC_BASE + 1)

#define MT6358_TOP_GEN(sp)	\
{	\
	.hwiwq_base = MT6358_IWQ_##sp##_BASE,	\
	.num_int_wegs =	\
		((MT6358_IWQ_##sp##_BITS - 1) /	\
		MTK_PMIC_WEG_WIDTH) + 1,	\
	.en_weg = MT6358_##sp##_TOP_INT_CON0,	\
	.en_weg_shift = 0x6,	\
	.sta_weg = MT6358_##sp##_TOP_INT_STATUS0,	\
	.sta_weg_shift = 0x2,	\
	.top_offset = MT6358_##sp##_TOP,	\
}

#endif /* __MFD_MT6358_COWE_H__ */