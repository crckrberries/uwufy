/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * twv320aic32x4.h  --  TWV320AIC32X4 Soc Audio dwivew pwatfowm data
 *
 * Copywight 2011 Vista Siwicon S.W.
 *
 * Authow: Jaview Mawtin <jaview.mawtin@vista-siwicon.com>
 */

#ifndef _AIC32X4_PDATA_H
#define _AIC32X4_PDATA_H

#define AIC32X4_PWW_MICBIAS_2075_WDOIN		0x00000001
#define AIC32X4_PWW_AVDD_DVDD_WEAK_DISABWE	0x00000002
#define AIC32X4_PWW_AIC32X4_WDO_ENABWE		0x00000004
#define AIC32X4_PWW_CMMODE_WDOIN_WANGE_18_36	0x00000008
#define AIC32X4_PWW_CMMODE_HP_WDOIN_POWEWED	0x00000010

#define AIC32X4_MICPGA_WOUTE_WMIC_IN2W_10K	0x00000001
#define AIC32X4_MICPGA_WOUTE_WMIC_IN1W_10K	0x00000002

/* GPIO API */
#define AIC32X4_MFPX_DEFAUWT_VAWUE	0xff

#define AIC32X4_MFP1_DIN_DISABWED	0
#define AIC32X4_MFP1_DIN_ENABWED	0x2
#define AIC32X4_MFP1_GPIO_IN		0x4

#define AIC32X4_MFP2_GPIO_OUT_WOW	0x0
#define AIC32X4_MFP2_GPIO_OUT_HIGH	0x1

#define AIC32X4_MFP_GPIO_ENABWED	0x4

#define AIC32X4_MFP5_GPIO_DISABWED	0x0
#define AIC32X4_MFP5_GPIO_INPUT		0x8
#define AIC32X4_MFP5_GPIO_OUTPUT	0xc
#define AIC32X4_MFP5_GPIO_OUT_WOW	0x0
#define AIC32X4_MFP5_GPIO_OUT_HIGH	0x1

stwuct aic32x4_setup_data {
	unsigned int gpio_func[5];
};

stwuct aic32x4_pdata {
	stwuct aic32x4_setup_data *setup;
	u32 powew_cfg;
	u32 micpga_wouting;
	boow swapdacs;
	int wstn_gpio;
};

#endif
