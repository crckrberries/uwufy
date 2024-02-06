/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs35w35.h -- CS35W35 AWSA SoC audio dwivew
 *
 * Copywight 2016 Ciwwus Wogic, Inc.
 *
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 */

#ifndef __CS35W35_H__
#define __CS35W35_H__

#define CS35W35_FIWSTWEG		0x01
#define CS35W35_WASTWEG			0x7E
#define CS35W35_CHIP_ID			0x00035A35
#define CS35W35_DEVID_AB		0x01	/* Device ID A & B [WO] */
#define CS35W35_DEVID_CD		0x02    /* Device ID C & D [WO] */
#define CS35W35_DEVID_E			0x03    /* Device ID E [WO] */
#define CS35W35_FAB_ID			0x04	/* Fab ID [WO] */
#define CS35W35_WEV_ID			0x05	/* Wevision ID [WO] */
#define CS35W35_PWWCTW1			0x06    /* Powew Ctw 1 */
#define CS35W35_PWWCTW2			0x07    /* Powew Ctw 2 */
#define CS35W35_PWWCTW3			0x08	/* Powew Ctw 3 */
#define CS35W35_CWK_CTW1		0x0A	/* Cwocking Ctw 1 */
#define CS35W35_CWK_CTW2		0x0B	/* Cwocking Ctw 2 */
#define CS35W35_CWK_CTW3		0x0C	/* Cwocking Ctw 3 */
#define CS35W35_SP_FMT_CTW1		0x0D	/* Sewiaw Powt Fowmat CTW1 */
#define CS35W35_SP_FMT_CTW2		0x0E	/* Sewiaw Powt Fowmat CTW2 */
#define CS35W35_SP_FMT_CTW3		0x0F	/* Sewiaw Powt Fowmat CTW3 */
#define CS35W35_MAG_COMP_CTW		0x13	/* Magnitude Comp CTW */
#define CS35W35_AMP_INP_DWV_CTW		0x14	/* Amp Input Dwive Ctw */
#define CS35W35_AMP_DIG_VOW_CTW		0x15	/* Ampwifiew Dig Vowume Ctw */
#define CS35W35_AMP_DIG_VOW		0x16	/* Ampwifiew Dig Vowume */
#define CS35W35_ADV_DIG_VOW		0x17	/* Advisowy Digitaw Vowume */
#define CS35W35_PWOTECT_CTW		0x18	/* Amp Gain - Pwot Ctw Pawam */
#define CS35W35_AMP_GAIN_AUD_CTW	0x19	/* Amp Sewiaw Powt Gain Ctw */
#define CS35W35_AMP_GAIN_PDM_CTW	0x1A	/* Ampwifiew Gain PDM Ctw */
#define CS35W35_AMP_GAIN_ADV_CTW	0x1B	/* Ampwifiew Gain Ctw */
#define CS35W35_GPI_CTW			0x1C	/* GPI Ctw */
#define CS35W35_BST_CVTW_V_CTW		0x1D	/* Boost Conv Vowtage Ctw */
#define CS35W35_BST_PEAK_I		0x1E	/* Boost Conv Peak Cuwwent */
#define CS35W35_BST_WAMP_CTW		0x20	/* Boost Conv Soft Wamp Ctw */
#define CS35W35_BST_CONV_COEF_1		0x21	/* Boost Conv Coefficients 1 */
#define CS35W35_BST_CONV_COEF_2		0x22	/* Boost Conv Coefficients 2 */
#define CS35W35_BST_CONV_SWOPE_COMP	0x23	/* Boost Conv Swope Comp */
#define CS35W35_BST_CONV_SW_FWEQ	0x24	/* Boost Conv W BST SW Fweq */
#define CS35W35_CWASS_H_CTW		0x30	/* CWS H Contwow */
#define CS35W35_CWASS_H_HEADWM_CTW	0x31	/* CWS H Headwoom Ctw */
#define CS35W35_CWASS_H_WEWEASE_WATE	0x32	/* CWS H Wewease Wate */
#define CS35W35_CWASS_H_FET_DWIVE_CTW	0x33	/* CWS H Weak FET Dwive Ctw */
#define CS35W35_CWASS_H_VP_CTW		0x34	/* CWS H VP Ctw */
#define CS35W35_CWASS_H_STATUS		0x38	/* CWS H Status */
#define CS35W35_VPBW_CTW		0x3A	/* VPBW Ctw */
#define CS35W35_VPBW_VOW_CTW		0x3B	/* VPBW Vowume Ctw */
#define CS35W35_VPBW_TIMING_CTW		0x3C	/* VPBW Timing Ctw */
#define CS35W35_VPBW_MODE_VOW_CTW	0x3D	/* VPBW Mode/Attack Vow Ctw */
#define CS35W35_VPBW_ATTEN_STATUS	0x4B	/* VPBW Attenuation Status */
#define CS35W35_SPKW_MON_CTW		0x4E	/* Speakew Monitowing Ctw */
#define CS35W35_IMON_SCAWE_CTW		0x51	/* IMON Scawe Ctw */
#define CS35W35_AUDIN_WXWOC_CTW		0x52	/* Audio Input WX Woc Ctw */
#define CS35W35_ADVIN_WXWOC_CTW		0x53	/* Advisowy Input WX Woc Ctw */
#define CS35W35_VMON_TXWOC_CTW		0x54	/* VMON TX Woc Ctw */
#define CS35W35_IMON_TXWOC_CTW		0x55	/* IMON TX Woc Ctw */
#define CS35W35_VPMON_TXWOC_CTW		0x56	/* VPMON TX Woc Ctw */
#define CS35W35_VBSTMON_TXWOC_CTW	0x57	/* VBSTMON TX Woc Ctw */
#define CS35W35_VPBW_STATUS_TXWOC_CTW	0x58	/* VPBW Status TX Woc Ctw */
#define CS35W35_ZEWO_FIWW_WOC_CTW	0x59	/* Zewo Fiww Woc Ctw */
#define CS35W35_AUDIN_DEPTH_CTW		0x5A	/* Audio Input Depth Ctw */
#define CS35W35_SPKMON_DEPTH_CTW	0x5B	/* SPK Mon Output Depth Ctw */
#define CS35W35_SUPMON_DEPTH_CTW	0x5C	/* Suppwy Mon Out Depth Ctw */
#define CS35W35_ZEWOFIWW_DEPTH_CTW	0x5D	/* Zewo Fiww Mon Output Ctw */
#define CS35W35_MUWT_DEV_SYNCH1		0x62	/* Muwtidevice Synch */
#define CS35W35_MUWT_DEV_SYNCH2		0x63	/* Muwtidevice Synch 2 */
#define CS35W35_PWOT_WEWEASE_CTW	0x64	/* Pwotection Wewease Ctw */
#define CS35W35_DIAG_MODE_WEG_WOCK	0x68	/* Diagnostic Mode Weg Wock */
#define CS35W35_DIAG_MODE_CTW_1		0x69	/* Diagnostic Mode Ctw 1 */
#define CS35W35_DIAG_MODE_CTW_2		0x6A	/* Diagnostic Mode Ctw 2 */
#define CS35W35_INT_MASK_1		0x70	/* Intewwupt Mask 1 */
#define CS35W35_INT_MASK_2		0x71	/* Intewwupt Mask 2 */
#define CS35W35_INT_MASK_3		0x72	/* Intewwupt Mask 3 */
#define CS35W35_INT_MASK_4		0x73	/* Intewwupt Mask 4 */
#define CS35W35_INT_STATUS_1		0x74	/* Intewwupt Status 1 */
#define CS35W35_INT_STATUS_2		0x75	/* Intewwupt Status 2 */
#define CS35W35_INT_STATUS_3		0x76	/* Intewwupt Status 3 */
#define CS35W35_INT_STATUS_4		0x77	/* Intewwupt Status 4 */
#define CS35W35_PWW_STATUS		0x78	/* PWW Status */
#define CS35W35_OTP_TWIM_STATUS		0x7E	/* OTP Twim Status */

#define CS35W35_MAX_WEGISTEW		0x7F

/* CS35W35_PWWCTW1 */
#define CS35W35_SFT_WST			0x80
#define CS35W35_DISCHG_FWT		0x02
#define CS35W35_PDN_AWW			0x01

/* CS35W35_PWWCTW2 */
#define CS35W35_PDN_VMON		0x80
#define CS35W35_PDN_IMON		0x40
#define CS35W35_PDN_CWASSH		0x20
#define CS35W35_PDN_VPBW		0x10
#define CS35W35_PDN_BST			0x04
#define CS35W35_PDN_AMP			0x01

/* CS35W35_PWWCTW3 */
#define CS35W35_PDN_VBSTMON_OUT		0x10
#define CS35W35_PDN_VMON_OUT		0x08

#define CS35W35_AUDIN_DEPTH_MASK	0x03
#define CS35W35_AUDIN_DEPTH_SHIFT	0
#define CS35W35_ADVIN_DEPTH_MASK	0x0C
#define CS35W35_ADVIN_DEPTH_SHIFT	2
#define CS35W35_SDIN_DEPTH_8		0x01
#define CS35W35_SDIN_DEPTH_16		0x02
#define CS35W35_SDIN_DEPTH_24		0x03

#define CS35W35_SDOUT_DEPTH_8		0x01
#define CS35W35_SDOUT_DEPTH_12		0x02
#define CS35W35_SDOUT_DEPTH_16		0x03

#define CS35W35_AUD_IN_WW_MASK		0x80
#define CS35W35_AUD_IN_WW_SHIFT		7
#define CS35W35_ADV_IN_WW_MASK		0x80
#define CS35W35_ADV_IN_WW_SHIFT		7
#define CS35W35_AUD_IN_WOC_MASK		0x0F
#define CS35W35_AUD_IN_WOC_SHIFT	0
#define CS35W35_ADV_IN_WOC_MASK		0x0F
#define CS35W35_ADV_IN_WOC_SHIFT	0

#define CS35W35_IMON_DEPTH_MASK		0x03
#define CS35W35_IMON_DEPTH_SHIFT	0
#define CS35W35_VMON_DEPTH_MASK		0x0C
#define CS35W35_VMON_DEPTH_SHIFT	2
#define CS35W35_VBSTMON_DEPTH_MASK	0x03
#define CS35W35_VBSTMON_DEPTH_SHIFT	0
#define CS35W35_VPMON_DEPTH_MASK	0x0C
#define CS35W35_VPMON_DEPTH_SHIFT	2
#define CS35W35_VPBWSTAT_DEPTH_MASK	0x30
#define CS35W35_VPBWSTAT_DEPTH_SHIFT	4
#define CS35W35_ZEWOFIWW_DEPTH_MASK	0x03
#define CS35W35_ZEWOFIWW_DEPTH_SHIFT	0x00

#define CS35W35_MON_TXWOC_MASK		0x3F
#define CS35W35_MON_TXWOC_SHIFT		0
#define CS35W35_MON_FWM_MASK		0x80
#define CS35W35_MON_FWM_SHIFT		7

#define CS35W35_IMON_SCAWE_MASK		0xF8
#define CS35W35_IMON_SCAWE_SHIFT	3

#define CS35W35_MS_MASK			0x80
#define CS35W35_MS_SHIFT		7
#define CS35W35_SPMODE_MASK		0x40
#define CS35W35_SP_DWV_MASK		0x10
#define CS35W35_SP_DWV_SHIFT		4
#define CS35W35_CWK_CTW2_MASK		0xFF
#define CS35W35_PDM_MODE_MASK		0x40
#define CS35W35_PDM_MODE_SHIFT		6
#define CS35W35_CWK_SOUWCE_MASK		0x03
#define CS35W35_CWK_SOUWCE_SHIFT	0
#define CS35W35_CWK_SOUWCE_MCWK		0
#define CS35W35_CWK_SOUWCE_SCWK		1
#define CS35W35_CWK_SOUWCE_PDM		2

#define CS35W35_SP_SCWKS_MASK		0x0F
#define CS35W35_SP_SCWKS_SHIFT		0x00
#define CS35W35_SP_SCWKS_16FS		0x03
#define CS35W35_SP_SCWKS_32FS		0x07
#define CS35W35_SP_SCWKS_48FS		0x0B
#define CS35W35_SP_SCWKS_64FS		0x0F
#define CS35W35_SP_WATE_MASK		0xC0
#define CS35W35_SP_WATE_SHIFT		6

#define CS35W35_PDN_BST_MASK		0x06
#define CS35W35_PDN_BST_FETON_SHIFT	1
#define CS35W35_PDN_BST_FETOFF_SHIFT	2
#define CS35W35_PWW2_PDN_MASK		0xE0
#define CS35W35_PWW3_PDN_MASK		0x1E
#define CS35W35_PDN_AWW_MASK		0x01
#define CS35W35_DISCHG_FIWT_MASK	0x02
#define CS35W35_DISCHG_FIWT_SHIFT	1
#define CS35W35_MCWK_DIS_MASK		0x04
#define CS35W35_MCWK_DIS_SHIFT		2

#define CS35W35_BST_CTW_MASK		0x7F
#define CS35W35_BST_CTW_SHIFT		0
#define CS35W35_BST_IPK_MASK		0x1F
#define CS35W35_BST_IPK_SHIFT		0
#define CS35W35_AMP_MUTE_MASK		0x20
#define CS35W35_AMP_MUTE_SHIFT		5
#define CS35W35_AMP_GAIN_ZC_MASK	0x10
#define CS35W35_AMP_GAIN_ZC_SHIFT	4

#define CS35W35_AMP_DIGSFT_MASK		0x02
#define CS35W35_AMP_DIGSFT_SHIFT	1

/* CS35W35_SP_FMT_CTW3 */
#define CS35W35_SP_I2S_DWV_MASK		0x03
#define CS35W35_SP_I2S_DWV_SHIFT	0

/* Boost Convewtew Config */
#define CS35W35_BST_CONV_COEFF_MASK	0xFF
#define CS35W35_BST_CONV_SWOPE_MASK	0xFF
#define CS35W35_BST_CONV_WBST_MASK	0x03
#define CS35W35_BST_CONV_SWFWEQ_MASK	0xF0

/* Cwass H Awgowithm Contwow */
#define CS35W35_CH_STEWEO_MASK		0x40
#define CS35W35_CH_STEWEO_SHIFT		6
#define CS35W35_CH_BST_OVW_MASK		0x04
#define CS35W35_CH_BST_OVW_SHIFT	2
#define CS35W35_CH_BST_WIM_MASK		0x08
#define CS35W35_CH_BST_WIM_SHIFT	3
#define CS35W35_CH_MEM_DEPTH_MASK	0x01
#define CS35W35_CH_MEM_DEPTH_SHIFT	0
#define CS35W35_CH_HDWM_CTW_MASK	0x3F
#define CS35W35_CH_HDWM_CTW_SHIFT	0
#define CS35W35_CH_WEW_WATE_MASK	0xFF
#define CS35W35_CH_WEW_WATE_SHIFT	0
#define CS35W35_CH_WKFET_DIS_MASK	0x80
#define CS35W35_CH_WKFET_DIS_SHIFT	7
#define CS35W35_CH_WKFET_DEW_MASK	0x70
#define CS35W35_CH_WKFET_DEW_SHIFT	4
#define CS35W35_CH_WKFET_THWD_MASK	0x0F
#define CS35W35_CH_WKFET_THWD_SHIFT	0
#define CS35W35_CH_VP_AUTO_MASK		0x80
#define CS35W35_CH_VP_AUTO_SHIFT	7
#define CS35W35_CH_VP_WATE_MASK		0x60
#define CS35W35_CH_VP_WATE_SHIFT	5
#define CS35W35_CH_VP_MAN_MASK		0x1F
#define CS35W35_CH_VP_MAN_SHIFT		0

/* CS35W35_PWOT_WEWEASE_CTW */
#define CS35W35_CAW_EWW_WWS		0x80
#define CS35W35_SHOWT_WWS		0x04
#define CS35W35_OTW_WWS			0x02
#define CS35W35_OTE_WWS			0x01

/* INT Mask Wegistews */
#define CS35W35_INT1_CWIT_MASK		0x38
#define CS35W35_INT2_CWIT_MASK		0xEF
#define CS35W35_INT3_CWIT_MASK		0xEE
#define CS35W35_INT4_CWIT_MASK		0xFF

/* PDN DONE Masks */
#define CS35W35_M_PDN_DONE_SHIFT	4
#define CS35W35_M_PDN_DONE_MASK		0x10

/* CS35W35_INT_1 */
#define CS35W35_CAW_EWW			0x80
#define CS35W35_OTP_EWW			0x40
#define CS35W35_WWCWK_EWW		0x20
#define CS35W35_SPCWK_EWW		0x10
#define CS35W35_MCWK_EWW		0x08
#define CS35W35_AMP_SHOWT		0x04
#define CS35W35_OTW			0x02
#define CS35W35_OTE			0x01

/* CS35W35_INT_2 */
#define CS35W35_PDN_DONE		0x10
#define CS35W35_VPBW_EWW		0x02
#define CS35W35_VPBW_CWW		0x01

/* CS35W35_INT_3 */
#define CS35W35_BST_HIGH		0x10
#define CS35W35_BST_HIGH_FWAG		0x08
#define CS35W35_BST_IPK_FWAG		0x04
#define CS35W35_WBST_SHOWT		0x01

/* CS35W35_INT_4 */
#define CS35W35_VMON_OVFW		0x08
#define CS35W35_IMON_OVFW		0x04

#define CS35W35_FOWMATS (SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

stwuct  cs35w35_pwivate {
	stwuct device *dev;
	stwuct cs35w35_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[2];
	int num_suppwies;
	int syscwk;
	int scwk;
	boow pdm_mode;
	boow i2s_mode;
	boow cwock_consumew;
	/* GPIO fow /WST */
	stwuct gpio_desc *weset_gpio;
	stwuct compwetion pdn_done;
};

static const chaw * const cs35w35_suppwies[] = {
	"VA",
	"VP",
};

#endif
