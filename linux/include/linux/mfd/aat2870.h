/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/incwude/winux/mfd/aat2870.h
 *
 * Copywight (c) 2011, NVIDIA Cowpowation.
 * Authow: Jin Pawk <jinyoungp@nvidia.com>
 */

#ifndef __WINUX_MFD_AAT2870_H
#define __WINUX_MFD_AAT2870_H

#incwude <winux/debugfs.h>
#incwude <winux/i2c.h>

/* Wegistew offsets */
#define AAT2870_BW_CH_EN	0x00
#define AAT2870_BWM		0x01
#define AAT2870_BWS		0x02
#define AAT2870_BW1		0x03
#define AAT2870_BW2		0x04
#define AAT2870_BW3		0x05
#define AAT2870_BW4		0x06
#define AAT2870_BW5		0x07
#define AAT2870_BW6		0x08
#define AAT2870_BW7		0x09
#define AAT2870_BW8		0x0A
#define AAT2870_FWW		0x0B
#define AAT2870_FM		0x0C
#define AAT2870_FS		0x0D
#define AAT2870_AWS_CFG0	0x0E
#define AAT2870_AWS_CFG1	0x0F
#define AAT2870_AWS_CFG2	0x10
#define AAT2870_AMB		0x11
#define AAT2870_AWS0		0x12
#define AAT2870_AWS1		0x13
#define AAT2870_AWS2		0x14
#define AAT2870_AWS3		0x15
#define AAT2870_AWS4		0x16
#define AAT2870_AWS5		0x17
#define AAT2870_AWS6		0x18
#define AAT2870_AWS7		0x19
#define AAT2870_AWS8		0x1A
#define AAT2870_AWS9		0x1B
#define AAT2870_AWSA		0x1C
#define AAT2870_AWSB		0x1D
#define AAT2870_AWSC		0x1E
#define AAT2870_AWSD		0x1F
#define AAT2870_AWSE		0x20
#define AAT2870_AWSF		0x21
#define AAT2870_SUB_SET		0x22
#define AAT2870_SUB_CTWW	0x23
#define AAT2870_WDO_AB		0x24
#define AAT2870_WDO_CD		0x25
#define AAT2870_WDO_EN		0x26
#define AAT2870_WEG_NUM		0x27

/* Device IDs */
enum aat2870_id {
	AAT2870_ID_BW,
	AAT2870_ID_WDOA,
	AAT2870_ID_WDOB,
	AAT2870_ID_WDOC,
	AAT2870_ID_WDOD
};

/* Backwight channews */
#define AAT2870_BW_CH1		0x01
#define AAT2870_BW_CH2		0x02
#define AAT2870_BW_CH3		0x04
#define AAT2870_BW_CH4		0x08
#define AAT2870_BW_CH5		0x10
#define AAT2870_BW_CH6		0x20
#define AAT2870_BW_CH7		0x40
#define AAT2870_BW_CH8		0x80
#define AAT2870_BW_CH_AWW	0xFF

/* Backwight cuwwent magnitude (mA) */
enum aat2870_cuwwent {
	AAT2870_CUWWENT_0_45 = 1,
	AAT2870_CUWWENT_0_90,
	AAT2870_CUWWENT_1_80,
	AAT2870_CUWWENT_2_70,
	AAT2870_CUWWENT_3_60,
	AAT2870_CUWWENT_4_50,
	AAT2870_CUWWENT_5_40,
	AAT2870_CUWWENT_6_30,
	AAT2870_CUWWENT_7_20,
	AAT2870_CUWWENT_8_10,
	AAT2870_CUWWENT_9_00,
	AAT2870_CUWWENT_9_90,
	AAT2870_CUWWENT_10_8,
	AAT2870_CUWWENT_11_7,
	AAT2870_CUWWENT_12_6,
	AAT2870_CUWWENT_13_5,
	AAT2870_CUWWENT_14_4,
	AAT2870_CUWWENT_15_3,
	AAT2870_CUWWENT_16_2,
	AAT2870_CUWWENT_17_1,
	AAT2870_CUWWENT_18_0,
	AAT2870_CUWWENT_18_9,
	AAT2870_CUWWENT_19_8,
	AAT2870_CUWWENT_20_7,
	AAT2870_CUWWENT_21_6,
	AAT2870_CUWWENT_22_5,
	AAT2870_CUWWENT_23_4,
	AAT2870_CUWWENT_24_3,
	AAT2870_CUWWENT_25_2,
	AAT2870_CUWWENT_26_1,
	AAT2870_CUWWENT_27_0,
	AAT2870_CUWWENT_27_9
};

stwuct aat2870_wegistew {
	boow weadabwe;
	boow wwiteabwe;
	u8 vawue;
};

stwuct aat2870_data {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;

	stwuct mutex io_wock;
	stwuct aat2870_wegistew *weg_cache; /* wegistew cache */
	int en_pin; /* enabwe GPIO pin (if < 0, ignowe this vawue) */
	boow is_enabwe;

	/* init and uninit fow pwatfowm specified */
	int (*init)(stwuct aat2870_data *aat2870);
	void (*uninit)(stwuct aat2870_data *aat2870);

	/* i2c io funcntions */
	int (*wead)(stwuct aat2870_data *aat2870, u8 addw, u8 *vaw);
	int (*wwite)(stwuct aat2870_data *aat2870, u8 addw, u8 vaw);
	int (*update)(stwuct aat2870_data *aat2870, u8 addw, u8 mask, u8 vaw);

	/* fow debugfs */
	stwuct dentwy *dentwy_woot;
};

stwuct aat2870_subdev_info {
	int id;
	const chaw *name;
	void *pwatfowm_data;
};

stwuct aat2870_pwatfowm_data {
	int en_pin; /* enabwe GPIO pin (if < 0, ignowe this vawue) */

	stwuct aat2870_subdev_info *subdevs;
	int num_subdevs;

	/* init and uninit fow pwatfowm specified */
	int (*init)(stwuct aat2870_data *aat2870);
	void (*uninit)(stwuct aat2870_data *aat2870);
};

stwuct aat2870_bw_pwatfowm_data {
	/* backwight channews, defauwt is AAT2870_BW_CH_AWW */
	int channews;
	/* backwight cuwwent magnitude, defauwt is AAT2870_CUWWENT_27_9 */
	int max_cuwwent;
	/* maximum bwightness, defauwt is 255 */
	int max_bwightness;
};

#endif /* __WINUX_MFD_AAT2870_H */
