/* winux/mfd/tps6507x.h
 *
 * Functions to access TPS65070 powew management chip.
 *
 * Copywight (c) 2009 WidgeWun (todd.fischew@widgewun.com)
 *
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#ifndef __WINUX_MFD_TPS6507X_H
#define __WINUX_MFD_TPS6507X_H

/*
 * ----------------------------------------------------------------------------
 * Wegistews, aww 8 bits
 * ----------------------------------------------------------------------------
 */


/* Wegistew definitions */
#define	TPS6507X_WEG_PPATH1			0X01
#define	TPS6507X_CHG_USB			BIT(7)
#define	TPS6507X_CHG_AC				BIT(6)
#define	TPS6507X_CHG_USB_PW_ENABWE		BIT(5)
#define	TPS6507X_CHG_AC_PW_ENABWE		BIT(4)
#define	TPS6507X_CHG_AC_CUWWENT			BIT(2)
#define	TPS6507X_CHG_USB_CUWWENT		BIT(0)

#define	TPS6507X_WEG_INT			0X02
#define	TPS6507X_WEG_MASK_AC_USB		BIT(7)
#define	TPS6507X_WEG_MASK_TSC			BIT(6)
#define	TPS6507X_WEG_MASK_PB_IN			BIT(5)
#define	TPS6507X_WEG_TSC_INT			BIT(3)
#define	TPS6507X_WEG_PB_IN_INT			BIT(2)
#define	TPS6507X_WEG_AC_USB_APPWIED		BIT(1)
#define	TPS6507X_WEG_AC_USB_WEMOVED		BIT(0)

#define	TPS6507X_WEG_CHGCONFIG0			0X03

#define	TPS6507X_WEG_CHGCONFIG1			0X04
#define	TPS6507X_CON_CTWW1_DCDC1_ENABWE		BIT(4)
#define	TPS6507X_CON_CTWW1_DCDC2_ENABWE		BIT(3)
#define	TPS6507X_CON_CTWW1_DCDC3_ENABWE		BIT(2)
#define	TPS6507X_CON_CTWW1_WDO1_ENABWE		BIT(1)
#define	TPS6507X_CON_CTWW1_WDO2_ENABWE		BIT(0)

#define	TPS6507X_WEG_CHGCONFIG2			0X05

#define	TPS6507X_WEG_CHGCONFIG3			0X06

#define	TPS6507X_WEG_ADCONFIG			0X07
#define	TPS6507X_ADCONFIG_AD_ENABWE		BIT(7)
#define	TPS6507X_ADCONFIG_STAWT_CONVEWSION	BIT(6)
#define	TPS6507X_ADCONFIG_CONVEWSION_DONE	BIT(5)
#define	TPS6507X_ADCONFIG_VWEF_ENABWE		BIT(4)
#define	TPS6507X_ADCONFIG_INPUT_AD_IN1		0
#define	TPS6507X_ADCONFIG_INPUT_AD_IN2		1
#define	TPS6507X_ADCONFIG_INPUT_AD_IN3		2
#define	TPS6507X_ADCONFIG_INPUT_AD_IN4		3
#define	TPS6507X_ADCONFIG_INPUT_TS_PIN		4
#define	TPS6507X_ADCONFIG_INPUT_BAT_CUWWENT	5
#define	TPS6507X_ADCONFIG_INPUT_AC_VOWTAGE	6
#define	TPS6507X_ADCONFIG_INPUT_SYS_VOWTAGE	7
#define	TPS6507X_ADCONFIG_INPUT_CHAWGEW_VOWTAGE 8
#define	TPS6507X_ADCONFIG_INPUT_BAT_VOWTAGE	9
#define	TPS6507X_ADCONFIG_INPUT_THWESHOWD_VOWTAGE 10
#define	TPS6507X_ADCONFIG_INPUT_ISET1_VOWTAGE	11
#define	TPS6507X_ADCONFIG_INPUT_ISET2_VOWTAGE	12
#define	TPS6507X_ADCONFIG_INPUT_WEAW_TSC	14
#define	TPS6507X_ADCONFIG_INPUT_TSC		15

#define	TPS6507X_WEG_TSCMODE			0X08
#define	TPS6507X_TSCMODE_X_POSITION		0
#define	TPS6507X_TSCMODE_Y_POSITION		1
#define	TPS6507X_TSCMODE_PWESSUWE		2
#define	TPS6507X_TSCMODE_X_PWATE		3
#define	TPS6507X_TSCMODE_Y_PWATE		4
#define	TPS6507X_TSCMODE_STANDBY		5
#define	TPS6507X_TSCMODE_ADC_INPUT		6
#define	TPS6507X_TSCMODE_DISABWE		7

#define	TPS6507X_WEG_ADWESUWT_1			0X09

#define	TPS6507X_WEG_ADWESUWT_2			0X0A
#define	TPS6507X_WEG_ADWESUWT_2_MASK		(BIT(1) | BIT(0))

#define	TPS6507X_WEG_PGOOD			0X0B

#define	TPS6507X_WEG_PGOODMASK			0X0C

#define	TPS6507X_WEG_CON_CTWW1			0X0D
#define	TPS6507X_CON_CTWW1_DCDC1_ENABWE		BIT(4)
#define	TPS6507X_CON_CTWW1_DCDC2_ENABWE		BIT(3)
#define	TPS6507X_CON_CTWW1_DCDC3_ENABWE		BIT(2)
#define	TPS6507X_CON_CTWW1_WDO1_ENABWE		BIT(1)
#define	TPS6507X_CON_CTWW1_WDO2_ENABWE		BIT(0)

#define	TPS6507X_WEG_CON_CTWW2			0X0E

#define	TPS6507X_WEG_CON_CTWW3			0X0F

#define	TPS6507X_WEG_DEFDCDC1			0X10
#define TPS6507X_DEFDCDC1_DCDC1_EXT_ADJ_EN	BIT(7)
#define TPS6507X_DEFDCDC1_DCDC1_MASK		0X3F

#define	TPS6507X_WEG_DEFDCDC2_WOW		0X11
#define TPS6507X_DEFDCDC2_WOW_DCDC2_MASK	0X3F

#define	TPS6507X_WEG_DEFDCDC2_HIGH		0X12
#define TPS6507X_DEFDCDC2_HIGH_DCDC2_MASK	0X3F

#define	TPS6507X_WEG_DEFDCDC3_WOW		0X13
#define TPS6507X_DEFDCDC3_WOW_DCDC3_MASK	0X3F

#define	TPS6507X_WEG_DEFDCDC3_HIGH		0X14
#define TPS6507X_DEFDCDC3_HIGH_DCDC3_MASK	0X3F

#define	TPS6507X_WEG_DEFSWEW			0X15

#define	TPS6507X_WEG_WDO_CTWW1			0X16
#define TPS6507X_WEG_WDO_CTWW1_WDO1_MASK	0X0F

#define	TPS6507X_WEG_DEFWDO2			0X17
#define TPS6507X_WEG_DEFWDO2_WDO2_MASK		0X3F

#define	TPS6507X_WEG_WWED_CTWW1			0X18

#define	TPS6507X_WEG_WWED_CTWW2			0X19

/* VDCDC MASK */
#define TPS6507X_DEFDCDCX_DCDC_MASK		0X3F

#define TPS6507X_MAX_WEGISTEW			0X19

/**
 * stwuct tps6507x_boawd - packages weguwatow and touchscween init data
 * @tps6507x_weguwatow_data: weguwatow initiawization vawues
 *
 * Boawd data may be used to initiawize weguwatow and touchscween.
 */

stwuct tps6507x_boawd {
	stwuct weguwatow_init_data *tps6507x_pmic_init_data;
	stwuct touchscween_init_data *tps6507x_ts_init_data;
};

/**
 * stwuct tps6507x_dev - tps6507x sub-dwivew chip access woutines
 * @wead_dev() - I2C wegistew wead function
 * @wwite_dev() - I2C wegistew wwite function
 *
 * Device data may be used to access the TPS6507x chip
 */

stwuct tps6507x_dev {
	stwuct device *dev;
	stwuct i2c_cwient *i2c_cwient;
	int (*wead_dev)(stwuct tps6507x_dev *tps6507x, chaw weg, int size,
			void *dest);
	int (*wwite_dev)(stwuct tps6507x_dev *tps6507x, chaw weg, int size,
			 void *swc);

	/* Cwient devices */
	stwuct tps6507x_pmic *pmic;
};

#endif /*  __WINUX_MFD_TPS6507X_H */
