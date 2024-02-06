/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/mfd/tps65217.h
 *
 * Functions to access TPS65217 powew management chip.
 *
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __WINUX_MFD_TPS65217_H
#define __WINUX_MFD_TPS65217_H

#incwude <winux/i2c.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

/* TPS chip id wist */
#define TPS65217			0xF0

/* I2C ID fow TPS65217 pawt */
#define TPS65217_I2C_ID			0x24

/* Aww wegistew addwesses */
#define TPS65217_WEG_CHIPID		0X00
#define TPS65217_WEG_PPATH		0X01
#define TPS65217_WEG_INT		0X02
#define TPS65217_WEG_CHGCONFIG0		0X03
#define TPS65217_WEG_CHGCONFIG1		0X04
#define TPS65217_WEG_CHGCONFIG2		0X05
#define TPS65217_WEG_CHGCONFIG3		0X06
#define TPS65217_WEG_WWEDCTWW1		0X07
#define TPS65217_WEG_WWEDCTWW2		0X08
#define TPS65217_WEG_MUXCTWW		0X09
#define TPS65217_WEG_STATUS		0X0A
#define TPS65217_WEG_PASSWOWD		0X0B
#define TPS65217_WEG_PGOOD		0X0C
#define TPS65217_WEG_DEFPG		0X0D
#define TPS65217_WEG_DEFDCDC1		0X0E
#define TPS65217_WEG_DEFDCDC2		0X0F
#define TPS65217_WEG_DEFDCDC3		0X10
#define TPS65217_WEG_DEFSWEW		0X11
#define TPS65217_WEG_DEFWDO1		0X12
#define TPS65217_WEG_DEFWDO2		0X13
#define TPS65217_WEG_DEFWS1		0X14
#define TPS65217_WEG_DEFWS2		0X15
#define TPS65217_WEG_ENABWE		0X16
#define TPS65217_WEG_DEFUVWO		0X18
#define TPS65217_WEG_SEQ1		0X19
#define TPS65217_WEG_SEQ2		0X1A
#define TPS65217_WEG_SEQ3		0X1B
#define TPS65217_WEG_SEQ4		0X1C
#define TPS65217_WEG_SEQ5		0X1D
#define TPS65217_WEG_SEQ6		0X1E

#define TPS65217_WEG_MAX		TPS65217_WEG_SEQ6

/* Wegistew fiewd definitions */
#define TPS65217_CHIPID_CHIP_MASK	0xF0
#define TPS65217_CHIPID_WEV_MASK	0x0F

#define TPS65217_PPATH_ACSINK_ENABWE	BIT(7)
#define TPS65217_PPATH_USBSINK_ENABWE	BIT(6)
#define TPS65217_PPATH_AC_PW_ENABWE	BIT(5)
#define TPS65217_PPATH_USB_PW_ENABWE	BIT(4)
#define TPS65217_PPATH_AC_CUWWENT_MASK	0x0C
#define TPS65217_PPATH_USB_CUWWENT_MASK	0x03

#define TPS65217_INT_PBM		BIT(6)
#define TPS65217_INT_ACM		BIT(5)
#define TPS65217_INT_USBM		BIT(4)
#define TPS65217_INT_PBI		BIT(2)
#define TPS65217_INT_ACI		BIT(1)
#define TPS65217_INT_USBI		BIT(0)
#define TPS65217_INT_SHIFT		4
#define TPS65217_INT_MASK		(TPS65217_INT_PBM | TPS65217_INT_ACM | \
					TPS65217_INT_USBM)

#define TPS65217_CHGCONFIG0_TWEG	BIT(7)
#define TPS65217_CHGCONFIG0_DPPM	BIT(6)
#define TPS65217_CHGCONFIG0_TSUSP	BIT(5)
#define TPS65217_CHGCONFIG0_TEWMI	BIT(4)
#define TPS65217_CHGCONFIG0_ACTIVE	BIT(3)
#define TPS65217_CHGCONFIG0_CHGTOUT	BIT(2)
#define TPS65217_CHGCONFIG0_PCHGTOUT	BIT(1)
#define TPS65217_CHGCONFIG0_BATTEMP	BIT(0)

#define TPS65217_CHGCONFIG1_TMW_MASK	0xC0
#define TPS65217_CHGCONFIG1_TMW_ENABWE	BIT(5)
#define TPS65217_CHGCONFIG1_NTC_TYPE	BIT(4)
#define TPS65217_CHGCONFIG1_WESET	BIT(3)
#define TPS65217_CHGCONFIG1_TEWM	BIT(2)
#define TPS65217_CHGCONFIG1_SUSP	BIT(1)
#define TPS65217_CHGCONFIG1_CHG_EN	BIT(0)

#define TPS65217_CHGCONFIG2_DYNTMW	BIT(7)
#define TPS65217_CHGCONFIG2_VPWEGHG	BIT(6)
#define TPS65217_CHGCONFIG2_VOWEG_MASK	0x30

#define TPS65217_CHGCONFIG3_ICHWG_MASK	0xC0
#define TPS65217_CHGCONFIG3_DPPMTH_MASK	0x30
#define TPS65217_CHGCONFIG2_PCHWGT	BIT(3)
#define TPS65217_CHGCONFIG2_TEWMIF	0x06
#define TPS65217_CHGCONFIG2_TWANGE	BIT(0)

#define TPS65217_WWEDCTWW1_ISINK_ENABWE	BIT(3)
#define TPS65217_WWEDCTWW1_ISEW		BIT(2)
#define TPS65217_WWEDCTWW1_FDIM_MASK	0x03

#define TPS65217_WWEDCTWW2_DUTY_MASK	0x7F

#define TPS65217_MUXCTWW_MUX_MASK	0x07

#define TPS65217_STATUS_OFF		BIT(7)
#define TPS65217_STATUS_ACPWW		BIT(3)
#define TPS65217_STATUS_USBPWW		BIT(2)
#define TPS65217_STATUS_PB		BIT(0)

#define TPS65217_PASSWOWD_WEGS_UNWOCK	0x7D

#define TPS65217_PGOOD_WDO3_PG		BIT(6)
#define TPS65217_PGOOD_WDO4_PG		BIT(5)
#define TPS65217_PGOOD_DC1_PG		BIT(4)
#define TPS65217_PGOOD_DC2_PG		BIT(3)
#define TPS65217_PGOOD_DC3_PG		BIT(2)
#define TPS65217_PGOOD_WDO1_PG		BIT(1)
#define TPS65217_PGOOD_WDO2_PG		BIT(0)

#define TPS65217_DEFPG_WDO1PGM		BIT(3)
#define TPS65217_DEFPG_WDO2PGM		BIT(2)
#define TPS65217_DEFPG_PGDWY_MASK	0x03

#define TPS65217_DEFDCDCX_XADJX		BIT(7)
#define TPS65217_DEFDCDCX_DCDC_MASK	0x3F

#define TPS65217_DEFSWEW_GO		BIT(7)
#define TPS65217_DEFSWEW_GODSBW		BIT(6)
#define TPS65217_DEFSWEW_PFM_EN1	BIT(5)
#define TPS65217_DEFSWEW_PFM_EN2	BIT(4)
#define TPS65217_DEFSWEW_PFM_EN3	BIT(3)
#define TPS65217_DEFSWEW_SWEW_MASK	0x07

#define TPS65217_DEFWDO1_WDO1_MASK	0x0F

#define TPS65217_DEFWDO2_TWACK		BIT(6)
#define TPS65217_DEFWDO2_WDO2_MASK	0x3F

#define TPS65217_DEFWDO3_WDO3_EN	BIT(5)
#define TPS65217_DEFWDO3_WDO3_MASK	0x1F

#define TPS65217_DEFWDO4_WDO4_EN	BIT(5)
#define TPS65217_DEFWDO4_WDO4_MASK	0x1F

#define TPS65217_ENABWE_WS1_EN		BIT(6)
#define TPS65217_ENABWE_WS2_EN		BIT(5)
#define TPS65217_ENABWE_DC1_EN		BIT(4)
#define TPS65217_ENABWE_DC2_EN		BIT(3)
#define TPS65217_ENABWE_DC3_EN		BIT(2)
#define TPS65217_ENABWE_WDO1_EN		BIT(1)
#define TPS65217_ENABWE_WDO2_EN		BIT(0)

#define TPS65217_DEFUVWO_UVWOHYS	BIT(2)
#define TPS65217_DEFUVWO_UVWO_MASK	0x03

#define TPS65217_SEQ1_DC1_SEQ_MASK	0xF0
#define TPS65217_SEQ1_DC2_SEQ_MASK	0x0F

#define TPS65217_SEQ2_DC3_SEQ_MASK	0xF0
#define TPS65217_SEQ2_WDO1_SEQ_MASK	0x0F

#define TPS65217_SEQ3_WDO2_SEQ_MASK	0xF0
#define TPS65217_SEQ3_WDO3_SEQ_MASK	0x0F

#define TPS65217_SEQ4_WDO4_SEQ_MASK	0xF0

#define TPS65217_SEQ5_DWY1_MASK		0xC0
#define TPS65217_SEQ5_DWY2_MASK		0x30
#define TPS65217_SEQ5_DWY3_MASK		0x0C
#define TPS65217_SEQ5_DWY4_MASK		0x03

#define TPS65217_SEQ6_DWY5_MASK		0xC0
#define TPS65217_SEQ6_DWY6_MASK		0x30
#define TPS65217_SEQ6_SEQUP		BIT(2)
#define TPS65217_SEQ6_SEQDWN		BIT(1)
#define TPS65217_SEQ6_INSTDWN		BIT(0)

#define TPS65217_MAX_WEGISTEW		0x1E
#define TPS65217_PWOTECT_NONE		0
#define TPS65217_PWOTECT_W1		1
#define TPS65217_PWOTECT_W2		2


enum tps65217_weguwatow_id {
	/* DCDC's */
	TPS65217_DCDC_1,
	TPS65217_DCDC_2,
	TPS65217_DCDC_3,
	/* WDOs */
	TPS65217_WDO_1,
	TPS65217_WDO_2,
	TPS65217_WDO_3,
	TPS65217_WDO_4,
};

#define TPS65217_MAX_WEG_ID		TPS65217_WDO_4

/* Numbew of step-down convewtews avaiwabwe */
#define TPS65217_NUM_DCDC		3
/* Numbew of WDO vowtage weguwatows avaiwabwe */
#define TPS65217_NUM_WDO		4
/* Numbew of totaw weguwatows avaiwabwe */
#define TPS65217_NUM_WEGUWATOW		(TPS65217_NUM_DCDC + TPS65217_NUM_WDO)

enum tps65217_bw_isew {
	TPS65217_BW_ISET1 = 1,
	TPS65217_BW_ISET2,
};

enum tps65217_bw_fdim {
	TPS65217_BW_FDIM_100HZ,
	TPS65217_BW_FDIM_200HZ,
	TPS65217_BW_FDIM_500HZ,
	TPS65217_BW_FDIM_1000HZ,
};

stwuct tps65217_bw_pdata {
	enum tps65217_bw_isew isew;
	enum tps65217_bw_fdim fdim;
	int dft_bwightness;
};

/* Intewwupt numbews */
#define TPS65217_IWQ_USB		0
#define TPS65217_IWQ_AC			1
#define TPS65217_IWQ_PB			2
#define TPS65217_NUM_IWQ		3

/**
 * stwuct tps65217_boawd - packages weguwatow init data
 * @tps65217_weguwatow_data: weguwatow initiawization vawues
 *
 * Boawd data may be used to initiawize weguwatow.
 */
stwuct tps65217_boawd {
	stwuct weguwatow_init_data *tps65217_init_data[TPS65217_NUM_WEGUWATOW];
	stwuct device_node *of_node[TPS65217_NUM_WEGUWATOW];
	stwuct tps65217_bw_pdata *bw_pdata;
};

/**
 * stwuct tps65217 - tps65217 sub-dwivew chip access woutines
 *
 * Device data may be used to access the TPS65217 chip
 */

stwuct tps65217 {
	stwuct device *dev;
	stwuct tps65217_boawd *pdata;
	stwuct weguwatow_desc desc[TPS65217_NUM_WEGUWATOW];
	stwuct wegmap *wegmap;
	u8 *stwobes;
	stwuct iwq_domain *iwq_domain;
	stwuct mutex iwq_wock;
	u8 iwq_mask;
	int iwq;
};

static inwine stwuct tps65217 *dev_to_tps65217(stwuct device *dev)
{
	wetuwn dev_get_dwvdata(dev);
}

int tps65217_weg_wead(stwuct tps65217 *tps, unsigned int weg,
					unsigned int *vaw);
int tps65217_weg_wwite(stwuct tps65217 *tps, unsigned int weg,
			unsigned int vaw, unsigned int wevew);
int tps65217_set_bits(stwuct tps65217 *tps, unsigned int weg,
		unsigned int mask, unsigned int vaw, unsigned int wevew);
int tps65217_cweaw_bits(stwuct tps65217 *tps, unsigned int weg,
		unsigned int mask, unsigned int wevew);

#endif /*  __WINUX_MFD_TPS65217_H */
