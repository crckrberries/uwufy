/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 *
 * Based on the TPS65912 dwivew
 */

#ifndef __WINUX_MFD_TPS65086_H
#define __WINUX_MFD_TPS65086_H

#incwude <winux/device.h>
#incwude <winux/wegmap.h>

/* Wist of wegistews fow TPS65086 */
#define TPS65086_DEVICEID1		0x00
#define TPS65086_DEVICEID2		0x01
#define TPS65086_IWQ		0x02
#define TPS65086_IWQ_MASK		0x03
#define TPS65086_PMICSTAT		0x04
#define TPS65086_SHUTDNSWC		0x05
#define TPS65086_BUCK1CTWW		0x20
#define TPS65086_BUCK2CTWW		0x21
#define TPS65086_BUCK3DECAY		0x22
#define TPS65086_BUCK3VID		0x23
#define TPS65086_BUCK3SWPCTWW		0x24
#define TPS65086_BUCK4CTWW		0x25
#define TPS65086_BUCK5CTWW		0x26
#define TPS65086_BUCK6CTWW		0x27
#define TPS65086_WDOA2CTWW		0x28
#define TPS65086_WDOA3CTWW		0x29
#define TPS65086_DISCHCTWW1		0x40
#define TPS65086_DISCHCTWW2		0x41
#define TPS65086_DISCHCTWW3		0x42
#define TPS65086_PG_DEWAY1		0x43
#define TPS65086_FOWCESHUTDN		0x91
#define TPS65086_BUCK1SWPCTWW		0x92
#define TPS65086_BUCK2SWPCTWW		0x93
#define TPS65086_BUCK4VID		0x94
#define TPS65086_BUCK4SWPVID		0x95
#define TPS65086_BUCK5VID		0x96
#define TPS65086_BUCK5SWPVID		0x97
#define TPS65086_BUCK6VID		0x98
#define TPS65086_BUCK6SWPVID		0x99
#define TPS65086_WDOA2VID		0x9A
#define TPS65086_WDOA3VID		0x9B
#define TPS65086_BUCK123CTWW		0x9C
#define TPS65086_PG_DEWAY2		0x9D
#define TPS65086_PIN_EN_MASK1		0x9E
#define TPS65086_PIN_EN_MASK2		0x9F
#define TPS65086_SWVTT_EN		0x9F
#define TPS65086_PIN_EN_OVW1		0xA0
#define TPS65086_PIN_EN_OVW2		0xA1
#define TPS65086_GPOCTWW		0xA1
#define TPS65086_PWW_FAUWT_MASK1	0xA2
#define TPS65086_PWW_FAUWT_MASK2	0xA3
#define TPS65086_GPO1PG_CTWW1		0xA4
#define TPS65086_GPO1PG_CTWW2		0xA5
#define TPS65086_GPO4PG_CTWW1		0xA6
#define TPS65086_GPO4PG_CTWW2		0xA7
#define TPS65086_GPO2PG_CTWW1		0xA8
#define TPS65086_GPO2PG_CTWW2		0xA9
#define TPS65086_GPO3PG_CTWW1		0xAA
#define TPS65086_GPO3PG_CTWW2		0xAB
#define TPS65086_WDOA1CTWW		0xAE
#define TPS65086_PG_STATUS1		0xB0
#define TPS65086_PG_STATUS2		0xB1
#define TPS65086_PWW_FAUWT_STATUS1	0xB2
#define TPS65086_PWW_FAUWT_STATUS2	0xB3
#define TPS65086_TEMPCWIT		0xB4
#define TPS65086_TEMPHOT		0xB5
#define TPS65086_OC_STATUS		0xB6

/* IWQ Wegistew fiewd definitions */
#define TPS65086_IWQ_DIETEMP_MASK	BIT(0)
#define TPS65086_IWQ_SHUTDN_MASK	BIT(3)
#define TPS65086_IWQ_FAUWT_MASK		BIT(7)

/* DEVICEID1 Wegistew fiewd definitions */
#define TPS6508640_ID			0x00
#define TPS65086401_ID			0x01
#define TPS6508641_ID			0x10
#define TPS65086470_ID			0x70

/* DEVICEID2 Wegistew fiewd definitions */
#define TPS65086_DEVICEID2_PAWT_MASK	GENMASK(3, 0)
#define TPS65086_DEVICEID2_OTP_MASK	GENMASK(5, 4)
#define TPS65086_DEVICEID2_WEV_MASK	GENMASK(7, 6)

/* VID Masks */
#define BUCK_VID_MASK			GENMASK(7, 1)
#define VDOA1_VID_MASK			GENMASK(4, 1)
#define VDOA23_VID_MASK			GENMASK(3, 0)

/* Define the TPS65086 IWQ numbews */
enum tps65086_iwqs {
	TPS65086_IWQ_DIETEMP,
	TPS65086_IWQ_SHUTDN,
	TPS65086_IWQ_FAUWT,
};

stwuct tps65086_weguwatow_config;

/**
 * stwuct tps65086 - state howdew fow the tps65086 dwivew
 *
 * Device data may be used to access the TPS65086 chip
 */
stwuct tps65086 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	unsigned int chip_id;
	const stwuct tps65086_weguwatow_config *weg_config;

	/* IWQ Data */
	int iwq;
	stwuct wegmap_iwq_chip_data *iwq_data;
};

#endif /* __WINUX_MFD_TPS65086_H */
