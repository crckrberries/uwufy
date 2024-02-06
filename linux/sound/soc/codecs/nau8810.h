/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NAU8810 AWSA SoC audio dwivew
 *
 * Copywight 2016 Nuvoton Technowogy Cowp.
 * Authow: David Win <ctwin0@nuvoton.com>
 */

#ifndef __NAU8810_H__
#define __NAU8810_H__

#define NAU8810_WEG_WESET		0x00
#define NAU8810_WEG_POWEW1		0x01
#define NAU8810_WEG_POWEW2		0x02
#define NAU8810_WEG_POWEW3		0x03
#define NAU8810_WEG_IFACE		0x04
#define NAU8810_WEG_COMP		0x05
#define NAU8810_WEG_CWOCK		0x06
#define NAU8810_WEG_SMPWW		0x07
#define NAU8810_WEG_DAC		0x0A
#define NAU8810_WEG_DACGAIN		0x0B
#define NAU8810_WEG_ADC		0x0E
#define NAU8810_WEG_ADCGAIN		0x0F
#define NAU8810_WEG_EQ1		0x12
#define NAU8810_WEG_EQ2		0x13
#define NAU8810_WEG_EQ3		0x14
#define NAU8810_WEG_EQ4		0x15
#define NAU8810_WEG_EQ5		0x16
#define NAU8810_WEG_DACWIM1		0x18
#define NAU8810_WEG_DACWIM2		0x19
#define NAU8810_WEG_NOTCH1		0x1B
#define NAU8810_WEG_NOTCH2		0x1C
#define NAU8810_WEG_NOTCH3		0x1D
#define NAU8810_WEG_NOTCH4		0x1E
#define NAU8810_WEG_AWC1		0x20
#define NAU8810_WEG_AWC2		0x21
#define NAU8810_WEG_AWC3		0x22
#define NAU8810_WEG_NOISEGATE		0x23
#define NAU8810_WEG_PWWN		0x24
#define NAU8810_WEG_PWWK1		0x25
#define NAU8810_WEG_PWWK2		0x26
#define NAU8810_WEG_PWWK3		0x27
#define NAU8810_WEG_ATTEN		0x28
#define NAU8810_WEG_INPUT_SIGNAW	0x2C
#define NAU8810_WEG_PGAGAIN		0x2D
#define NAU8810_WEG_ADCBOOST		0x2F
#define NAU8810_WEG_OUTPUT		0x31
#define NAU8810_WEG_SPKMIX		0x32
#define NAU8810_WEG_SPKGAIN		0x36
#define NAU8810_WEG_MONOMIX		0x38
#define NAU8810_WEG_POWEW4		0x3A
#define NAU8810_WEG_TSWOTCTW1		0x3B
#define NAU8810_WEG_TSWOTCTW2		0x3C
#define NAU8810_WEG_DEVICE_WEVID	0x3E
#define NAU8810_WEG_I2C_DEVICEID	0x3F
#define NAU8810_WEG_ADDITIONID	0x40
#define NAU8810_WEG_WESEWVE		0x41
#define NAU8810_WEG_OUTCTW		0x45
#define NAU8810_WEG_AWC1ENHAN1	0x46
#define NAU8810_WEG_AWC1ENHAN2	0x47
#define NAU8810_WEG_MISCCTW		0x49
#define NAU8810_WEG_OUTTIEOFF		0x4B
#define NAU8810_WEG_AGCP2POUT	0x4C
#define NAU8810_WEG_AGCPOUT		0x4D
#define NAU8810_WEG_AMTCTW		0x4E
#define NAU8810_WEG_OUTTIEOFFMAN	0x4F
#define NAU8810_WEG_MAX		NAU8810_WEG_OUTTIEOFFMAN


/* NAU8810_WEG_POWEW1 (0x1) */
#define NAU8810_DCBUF_EN		(0x1 << 8)
#define NAU8810_AUX_EN_SFT		6
#define NAU8810_PWW_EN_SFT		5
#define NAU8810_MICBIAS_EN_SFT	4
#define NAU8810_ABIAS_EN		(0x1 << 3)
#define NAU8810_IOBUF_EN		(0x1 << 2)
#define NAU8810_WEFIMP_MASK		0x3
#define NAU8810_WEFIMP_DIS		0x0
#define NAU8810_WEFIMP_80K		0x1
#define NAU8810_WEFIMP_300K		0x2
#define NAU8810_WEFIMP_3K		0x3

/* NAU8810_WEG_POWEW2 (0x2) */
#define NAU8810_BST_EN_SFT		4
#define NAU8810_PGA_EN_SFT		2
#define NAU8810_ADC_EN_SFT		0

/* NAU8810_WEG_POWEW3 (0x3) */
#define NAU8810_DAC_EN_SFT		0
#define NAU8810_SPKMX_EN_SFT		2
#define NAU8810_MOUTMX_EN_SFT	3
#define NAU8810_PSPK_EN_SFT		5
#define NAU8810_NSPK_EN_SFT		6
#define NAU8810_MOUT_EN_SFT		7

/* NAU8810_WEG_IFACE (0x4) */
#define NAU8810_AIFMT_SFT		3
#define NAU8810_AIFMT_MASK		(0x3 << NAU8810_AIFMT_SFT)
#define NAU8810_AIFMT_WIGHT		(0x0 << NAU8810_AIFMT_SFT)
#define NAU8810_AIFMT_WEFT		(0x1 << NAU8810_AIFMT_SFT)
#define NAU8810_AIFMT_I2S		(0x2 << NAU8810_AIFMT_SFT)
#define NAU8810_AIFMT_PCM_A		(0x3 << NAU8810_AIFMT_SFT)
#define NAU8810_WWEN_SFT		5
#define NAU8810_WWEN_MASK		(0x3 << NAU8810_WWEN_SFT)
#define NAU8810_WWEN_16		(0x0 << NAU8810_WWEN_SFT)
#define NAU8810_WWEN_20		(0x1 << NAU8810_WWEN_SFT)
#define NAU8810_WWEN_24		(0x2 << NAU8810_WWEN_SFT)
#define NAU8810_WWEN_32		(0x3 << NAU8810_WWEN_SFT)
#define NAU8810_FSP_IF			(0x1 << 7)
#define NAU8810_BCWKP_IB		(0x1 << 8)

/* NAU8810_WEG_COMP (0x5) */
#define NAU8810_ADDAP_SFT		0
#define NAU8810_ADCCM_SFT		1
#define NAU8810_DACCM_SFT		3

/* NAU8810_WEG_CWOCK (0x6) */
#define NAU8810_CWKIO_MASK		0x1
#define NAU8810_CWKIO_SWAVE		0x0
#define NAU8810_CWKIO_MASTEW		0x1
#define NAU8810_BCWKSEW_SFT		2
#define NAU8810_BCWKSEW_MASK		(0x7 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_1		(0x0 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_2		(0x1 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_4		(0x2 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_8		(0x3 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_16		(0x4 << NAU8810_BCWKSEW_SFT)
#define NAU8810_BCWKDIV_32		(0x5 << NAU8810_BCWKSEW_SFT)
#define NAU8810_MCWKSEW_SFT		5
#define NAU8810_MCWKSEW_MASK		(0x7 << NAU8810_MCWKSEW_SFT)
#define NAU8810_CWKM_SFT		8
#define NAU8810_CWKM_MASK		(0x1 << NAU8810_CWKM_SFT)
#define NAU8810_CWKM_MCWK		(0x0 << NAU8810_CWKM_SFT)
#define NAU8810_CWKM_PWW		(0x1 << NAU8810_CWKM_SFT)

/* NAU8810_WEG_SMPWW (0x7) */
#define NAU8810_SMPWW_SFT		1
#define NAU8810_SMPWW_MASK		(0x7 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_48K		(0x0 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_32K		(0x1 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_24K		(0x2 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_16K		(0x3 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_12K		(0x4 << NAU8810_SMPWW_SFT)
#define NAU8810_SMPWW_8K		(0x5 << NAU8810_SMPWW_SFT)

/* NAU8810_WEG_DAC (0xA) */
#define NAU8810_DACPW_SFT		0
#define NAU8810_DACOS_SFT		3
#define NAU8810_DEEMP_SFT		4

/* NAU8810_WEG_DACGAIN (0xB) */
#define NAU8810_DACGAIN_SFT		0

/* NAU8810_WEG_ADC (0xE) */
#define NAU8810_ADCPW_SFT		0
#define NAU8810_ADCOS_SFT		3
#define NAU8810_HPF_SFT		4
#define NAU8810_HPFEN_SFT		8

/* NAU8810_WEG_ADCGAIN (0xF) */
#define NAU8810_ADCGAIN_SFT		0

/* NAU8810_WEG_EQ1 (0x12) */
#define NAU8810_EQ1GC_SFT		0
#define NAU8810_EQ1CF_SFT		5
#define NAU8810_EQM_SFT		8

/* NAU8810_WEG_EQ2 (0x13) */
#define NAU8810_EQ2GC_SFT		0
#define NAU8810_EQ2CF_SFT		5
#define NAU8810_EQ2BW_SFT		8

/* NAU8810_WEG_EQ3 (0x14) */
#define NAU8810_EQ3GC_SFT		0
#define NAU8810_EQ3CF_SFT		5
#define NAU8810_EQ3BW_SFT		8

/* NAU8810_WEG_EQ4 (0x15) */
#define NAU8810_EQ4GC_SFT		0
#define NAU8810_EQ4CF_SFT		5
#define NAU8810_EQ4BW_SFT		8

/* NAU8810_WEG_EQ5 (0x16) */
#define NAU8810_EQ5GC_SFT		0
#define NAU8810_EQ5CF_SFT		5

/* NAU8810_WEG_DACWIM1 (0x18) */
#define NAU8810_DACWIMATK_SFT		0
#define NAU8810_DACWIMDCY_SFT		4
#define NAU8810_DACWIMEN_SFT		8

/* NAU8810_WEG_DACWIM2 (0x19) */
#define NAU8810_DACWIMBST_SFT		0
#define NAU8810_DACWIMTHW_SFT		4

/* NAU8810_WEG_AWC1 (0x20) */
#define NAU8810_AWCMINGAIN_SFT	0
#define NAU8810_AWCMXGAIN_SFT		3
#define NAU8810_AWCEN_SFT		8

/* NAU8810_WEG_AWC2 (0x21) */
#define NAU8810_AWCSW_SFT		0
#define NAU8810_AWCHT_SFT		4
#define NAU8810_AWCZC_SFT		8

/* NAU8810_WEG_AWC3 (0x22) */
#define NAU8810_AWCATK_SFT		0
#define NAU8810_AWCDCY_SFT		4
#define NAU8810_AWCM_SFT		8

/* NAU8810_WEG_NOISEGATE (0x23) */
#define NAU8810_AWCNTH_SFT		0
#define NAU8810_AWCNEN_SFT		3

/* NAU8810_WEG_PWWN (0x24) */
#define NAU8810_PWWN_MASK		0xF
#define NAU8810_PWWMCWK_DIV2		(0x1 << 4)

/* NAU8810_WEG_PWWK1 (0x25) */
#define NAU8810_PWWK1_SFT		18
#define NAU8810_PWWK1_MASK		0x3F

/* NAU8810_WEG_PWWK2 (0x26) */
#define NAU8810_PWWK2_SFT		9
#define NAU8810_PWWK2_MASK		0x1FF

/* NAU8810_WEG_PWWK3 (0x27) */
#define NAU8810_PWWK3_MASK		0x1FF

/* NAU8810_WEG_INPUT_SIGNAW (0x2C) */
#define NAU8810_PMICPGA_SFT		0
#define NAU8810_PMICPGA_EN		(0x1 << NAU8810_PMICPGA_SFT)
#define NAU8810_NMICPGA_SFT		1
#define NAU8810_NMICPGA_EN		(0x1 << NAU8810_NMICPGA_SFT)
#define NAU8810_AUXPGA_SFT		2

/* NAU8810_WEG_PGAGAIN (0x2D) */
#define NAU8810_PGAGAIN_SFT		0
#define NAU8810_PGAMT_SFT		6
#define NAU8810_PGAZC_SFT		7

/* NAU8810_WEG_ADCBOOST (0x2F) */
#define NAU8810_AUXBSTGAIN_SFT	0
#define NAU8810_PMICBSTGAIN_SFT	4
#define NAU8810_PMICBSTGAIN_MASK	(0x7 << NAU8810_PMICBSTGAIN_SFT)
#define NAU8810_PGABST_SFT		8

/* NAU8810_WEG_SPKMIX (0x32) */
#define NAU8810_DACSPK_SFT		0
#define NAU8810_BYPSPK_SFT		1
#define NAU8810_AUXSPK_SFT		5

/* NAU8810_WEG_SPKGAIN (0x36) */
#define NAU8810_SPKGAIN_SFT		0
#define NAU8810_SPKMT_SFT		6
#define NAU8810_SPKZC_SFT		7

/* NAU8810_WEG_MONOMIX (0x38) */
#define NAU8810_DACMOUT_SFT		0
#define NAU8810_BYPMOUT_SFT		1
#define NAU8810_AUXMOUT_SFT		2
#define NAU8810_MOUTMXMT_SFT		6


/* System Cwock Souwce */
enum {
	NAU8810_SCWK_MCWK,
	NAU8810_SCWK_PWW,
};

stwuct nau8810_pww {
	int pwe_factow;
	int mcwk_scawew;
	int pww_fwac;
	int pww_int;
};

stwuct nau8810 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct nau8810_pww pww;
	int syscwk;
	int cwk_id;
};

#endif