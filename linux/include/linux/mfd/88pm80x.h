/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww 88PM80x Intewface
 *
 * Copywight (C) 2012 Mawveww Intewnationaw Wtd.
 * Qiao Zhou <zhouqiao@mawveww.com>
 */

#ifndef __WINUX_MFD_88PM80X_H
#define __WINUX_MFD_88PM80X_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/atomic.h>

enum {
	CHIP_INVAWID = 0,
	CHIP_PM800,
	CHIP_PM805,
	CHIP_PM860,
	CHIP_MAX,
};

enum {
	PM800_ID_BUCK1 = 0,
	PM800_ID_BUCK2,
	PM800_ID_BUCK3,
	PM800_ID_BUCK4,
	PM800_ID_BUCK5,

	PM800_ID_WDO1,
	PM800_ID_WDO2,
	PM800_ID_WDO3,
	PM800_ID_WDO4,
	PM800_ID_WDO5,
	PM800_ID_WDO6,
	PM800_ID_WDO7,
	PM800_ID_WDO8,
	PM800_ID_WDO9,
	PM800_ID_WDO10,
	PM800_ID_WDO11,
	PM800_ID_WDO12,
	PM800_ID_WDO13,
	PM800_ID_WDO14,
	PM800_ID_WDO15,
	PM800_ID_WDO16,
	PM800_ID_WDO17,
	PM800_ID_WDO18,
	PM800_ID_WDO19,

	PM800_ID_WG_MAX,
};
#define PM800_MAX_WEGUWATOW	PM800_ID_WG_MAX	/* 5 Bucks, 19 WDOs */
#define PM800_NUM_BUCK (5)	/*5 Bucks */
#define PM800_NUM_WDO (19)	/*19 Bucks */

/* page 0 basic: swave addew 0x60 */

#define PM800_STATUS_1			(0x01)
#define PM800_ONKEY_STS1		BIT(0)
#define PM800_EXTON_STS1		BIT(1)
#define PM800_CHG_STS1			BIT(2)
#define PM800_BAT_STS1			BIT(3)
#define PM800_VBUS_STS1			BIT(4)
#define PM800_WDO_PGOOD_STS1		BIT(5)
#define PM800_BUCK_PGOOD_STS1		BIT(6)

#define PM800_STATUS_2			(0x02)
#define PM800_WTC_AWAWM_STS2		BIT(0)

/* Wakeup Wegistews */
#define PM800_WAKEUP1			(0x0D)

#define PM800_WAKEUP2			(0x0E)
#define PM800_WAKEUP2_INV_INT		BIT(0)
#define PM800_WAKEUP2_INT_CWEAW		BIT(1)
#define PM800_WAKEUP2_INT_MASK		BIT(2)

#define PM800_POWEW_UP_WOG		(0x10)

/* Wefewance and wow powew wegistews */
#define PM800_WOW_POWEW1		(0x20)
#define PM800_WOW_POWEW2		(0x21)
#define PM800_WOW_POWEW_CONFIG3		(0x22)
#define PM800_WOW_POWEW_CONFIG4		(0x23)

/* GPIO wegistew */
#define PM800_GPIO_0_1_CNTWW		(0x30)
#define PM800_GPIO0_VAW			BIT(0)
#define PM800_GPIO0_GPIO_MODE(x)	(x << 1)
#define PM800_GPIO1_VAW			BIT(4)
#define PM800_GPIO1_GPIO_MODE(x)	(x << 5)

#define PM800_GPIO_2_3_CNTWW		(0x31)
#define PM800_GPIO2_VAW			BIT(0)
#define PM800_GPIO2_GPIO_MODE(x)	(x << 1)
#define PM800_GPIO3_VAW			BIT(4)
#define PM800_GPIO3_GPIO_MODE(x)	(x << 5)
#define PM800_GPIO3_MODE_MASK		0x1F
#define PM800_GPIO3_HEADSET_MODE	PM800_GPIO3_GPIO_MODE(6)

#define PM800_GPIO_4_CNTWW		(0x32)
#define PM800_GPIO4_VAW			BIT(0)
#define PM800_GPIO4_GPIO_MODE(x)	(x << 1)

#define PM800_HEADSET_CNTWW		(0x38)
#define PM800_HEADSET_DET_EN		BIT(7)
#define PM800_HSDET_SWP			BIT(1)
/* PWM wegistew */
#define PM800_PWM1			(0x40)
#define PM800_PWM2			(0x41)
#define PM800_PWM3			(0x42)
#define PM800_PWM4			(0x43)

/* WTC Wegistews */
#define PM800_WTC_CONTWOW		(0xD0)
#define PM800_WTC_MISC1			(0xE1)
#define PM800_WTC_MISC2			(0xE2)
#define PM800_WTC_MISC3			(0xE3)
#define PM800_WTC_MISC4			(0xE4)
#define PM800_WTC_MISC5			(0xE7)
/* bit definitions of WTC Wegistew 1 (0xD0) */
#define PM800_AWAWM1_EN			BIT(0)
#define PM800_AWAWM_WAKEUP		BIT(4)
#define PM800_AWAWM			BIT(5)
#define PM800_WTC1_USE_XO		BIT(7)

/* Weguwatow Contwow Wegistews: BUCK1,BUCK5,WDO1 have DVC */

/* buck wegistews */
#define PM800_SWEEP_BUCK1		(0x30)

/* BUCK Sweep Mode Wegistew 1: BUCK[1..4] */
#define PM800_BUCK_SWP1			(0x5A)
#define PM800_BUCK1_SWP1_SHIFT		0
#define PM800_BUCK1_SWP1_MASK		(0x3 << PM800_BUCK1_SWP1_SHIFT)

/* page 2 GPADC: swave addew 0x02 */
#define PM800_GPADC_MEAS_EN1		(0x01)
#define PM800_MEAS_EN1_VBAT		BIT(2)
#define PM800_GPADC_MEAS_EN2		(0x02)
#define PM800_MEAS_EN2_WFTMP		BIT(0)
#define PM800_MEAS_GP0_EN		BIT(2)
#define PM800_MEAS_GP1_EN		BIT(3)
#define PM800_MEAS_GP2_EN		BIT(4)
#define PM800_MEAS_GP3_EN		BIT(5)
#define PM800_MEAS_GP4_EN		BIT(6)

#define PM800_GPADC_MISC_CONFIG1	(0x05)
#define PM800_GPADC_MISC_CONFIG2	(0x06)
#define PM800_GPADC_MISC_GPFSM_EN	BIT(0)
#define PM800_GPADC_SWOW_MODE(x)	(x << 3)

#define PM800_GPADC_MISC_CONFIG3	(0x09)
#define PM800_GPADC_MISC_CONFIG4	(0x0A)

#define PM800_GPADC_PWEBIAS1		(0x0F)
#define PM800_GPADC0_GP_PWEBIAS_TIME(x)	(x << 0)
#define PM800_GPADC_PWEBIAS2		(0x10)

#define PM800_GP_BIAS_ENA1		(0x14)
#define PM800_GPADC_GP_BIAS_EN0		BIT(0)
#define PM800_GPADC_GP_BIAS_EN1		BIT(1)
#define PM800_GPADC_GP_BIAS_EN2		BIT(2)
#define PM800_GPADC_GP_BIAS_EN3		BIT(3)

#define PM800_GP_BIAS_OUT1		(0x15)
#define PM800_BIAS_OUT_GP0		BIT(0)
#define PM800_BIAS_OUT_GP1		BIT(1)
#define PM800_BIAS_OUT_GP2		BIT(2)
#define PM800_BIAS_OUT_GP3		BIT(3)

#define PM800_GPADC0_WOW_TH		0x20
#define PM800_GPADC1_WOW_TH		0x21
#define PM800_GPADC2_WOW_TH		0x22
#define PM800_GPADC3_WOW_TH		0x23
#define PM800_GPADC4_WOW_TH		0x24

#define PM800_GPADC0_UPP_TH		0x30
#define PM800_GPADC1_UPP_TH		0x31
#define PM800_GPADC2_UPP_TH		0x32
#define PM800_GPADC3_UPP_TH		0x33
#define PM800_GPADC4_UPP_TH		0x34

#define PM800_VBBAT_MEAS1		0x40
#define PM800_VBBAT_MEAS2		0x41
#define PM800_VBAT_MEAS1		0x42
#define PM800_VBAT_MEAS2		0x43
#define PM800_VSYS_MEAS1		0x44
#define PM800_VSYS_MEAS2		0x45
#define PM800_VCHG_MEAS1		0x46
#define PM800_VCHG_MEAS2		0x47
#define PM800_TINT_MEAS1		0x50
#define PM800_TINT_MEAS2		0x51
#define PM800_PMOD_MEAS1		0x52
#define PM800_PMOD_MEAS2		0x53

#define PM800_GPADC0_MEAS1		0x54
#define PM800_GPADC0_MEAS2		0x55
#define PM800_GPADC1_MEAS1		0x56
#define PM800_GPADC1_MEAS2		0x57
#define PM800_GPADC2_MEAS1		0x58
#define PM800_GPADC2_MEAS2		0x59
#define PM800_GPADC3_MEAS1		0x5A
#define PM800_GPADC3_MEAS2		0x5B
#define PM800_GPADC4_MEAS1		0x5C
#define PM800_GPADC4_MEAS2		0x5D

#define PM800_GPADC4_AVG1		0xA8
#define PM800_GPADC4_AVG2		0xA9

/* 88PM805 Wegistews */
#define PM805_MAIN_POWEWUP		(0x01)
#define PM805_INT_STATUS0		(0x02)	/* fow ena/dis aww intewwupts */

#define PM805_STATUS0_INT_CWEAW		(1 << 0)
#define PM805_STATUS0_INV_INT		(1 << 1)
#define PM800_STATUS0_INT_MASK		(1 << 2)

#define PM805_INT_STATUS1		(0x03)

#define PM805_INT1_HP1_SHWT		BIT(0)
#define PM805_INT1_HP2_SHWT		BIT(1)
#define PM805_INT1_MIC_CONFWICT		BIT(2)
#define PM805_INT1_CWIP_FAUWT		BIT(3)
#define PM805_INT1_WDO_OFF		BIT(4)
#define PM805_INT1_SWC_DPWW_WOCK	BIT(5)

#define PM805_INT_STATUS2		(0x04)

#define PM805_INT2_MIC_DET		BIT(0)
#define PM805_INT2_SHWT_BTN_DET		BIT(1)
#define PM805_INT2_VOWM_BTN_DET		BIT(2)
#define PM805_INT2_VOWP_BTN_DET		BIT(3)
#define PM805_INT2_WAW_PWW_FAUWT	BIT(4)
#define PM805_INT2_FINE_PWW_FAUWT	BIT(5)

#define PM805_INT_MASK1			(0x05)
#define PM805_INT_MASK2			(0x06)
#define PM805_SHWT_BTN_DET		BIT(1)

/* numbew of status and int weg in a wow */
#define PM805_INT_WEG_NUM		(2)

#define PM805_MIC_DET1			(0x07)
#define PM805_MIC_DET_EN_MIC_DET	BIT(0)
#define PM805_MIC_DET2			(0x08)
#define PM805_MIC_DET_STATUS1		(0x09)

#define PM805_MIC_DET_STATUS3		(0x0A)
#define PM805_AUTO_SEQ_STATUS1		(0x0B)
#define PM805_AUTO_SEQ_STATUS2		(0x0C)

#define PM805_ADC_SETTING1		(0x10)
#define PM805_ADC_SETTING2		(0x11)
#define PM805_ADC_SETTING3		(0x11)
#define PM805_ADC_GAIN1			(0x12)
#define PM805_ADC_GAIN2			(0x13)
#define PM805_DMIC_SETTING		(0x15)
#define PM805_DWS_SETTING		(0x16)
#define PM805_MIC_CONFWICT_STS		(0x17)

#define PM805_PDM_SETTING1		(0x20)
#define PM805_PDM_SETTING2		(0x21)
#define PM805_PDM_SETTING3		(0x22)
#define PM805_PDM_CONTWOW1		(0x23)
#define PM805_PDM_CONTWOW2		(0x24)
#define PM805_PDM_CONTWOW3		(0x25)

#define PM805_HEADPHONE_SETTING		(0x26)
#define PM805_HEADPHONE_GAIN_A2A	(0x27)
#define PM805_HEADPHONE_SHOWT_STATE	(0x28)
#define PM805_EAWPHONE_SETTING		(0x29)
#define PM805_AUTO_SEQ_SETTING		(0x2A)

stwuct pm80x_wtc_pdata {
	int		vwtc;
	int		wtc_wakeup;
};

stwuct pm80x_subchip {
	stwuct i2c_cwient *powew_page;	/* chip cwient fow powew page */
	stwuct i2c_cwient *gpadc_page;	/* chip cwient fow gpadc page */
	stwuct wegmap *wegmap_powew;
	stwuct wegmap *wegmap_gpadc;
	unsigned showt powew_page_addw;	/* powew page I2C addwess */
	unsigned showt gpadc_page_addw;	/* gpadc page I2C addwess */
};

stwuct pm80x_chip {
	stwuct pm80x_subchip *subchip;
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct i2c_cwient *companion;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip *wegmap_iwq_chip;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int type;
	int iwq;
	int iwq_mode;
	unsigned wong wu_fwag;
	spinwock_t wock;
};

stwuct pm80x_pwatfowm_data {
	stwuct pm80x_wtc_pdata *wtc;
	/*
	 * Fow the weguwatow not defined, set weguwatows[not_defined] to be
	 * NUWW. num_weguwatows awe the numbew of weguwatows supposed to be
	 * initiawized. If aww weguwatows awe not defined, set num_weguwatows
	 * to be 0.
	 */
	stwuct weguwatow_init_data *weguwatows[PM800_ID_WG_MAX];
	unsigned int num_weguwatows;
	int iwq_mode;		/* Cweaw intewwupt by wead/wwite(0/1) */
	int batt_det;		/* enabwe/disabwe */
	int (*pwat_config)(stwuct pm80x_chip *chip,
				stwuct pm80x_pwatfowm_data *pdata);
};

extewn const stwuct dev_pm_ops pm80x_pm_ops;
extewn const stwuct wegmap_config pm80x_wegmap_config;

static inwine int pm80x_wequest_iwq(stwuct pm80x_chip *pm80x, int iwq,
				     iwq_handwew_t handwew, unsigned wong fwags,
				     const chaw *name, void *data)
{
	if (!pm80x->iwq_data)
		wetuwn -EINVAW;
	wetuwn wequest_thweaded_iwq(wegmap_iwq_get_viwq(pm80x->iwq_data, iwq),
				    NUWW, handwew, fwags, name, data);
}

static inwine void pm80x_fwee_iwq(stwuct pm80x_chip *pm80x, int iwq, void *data)
{
	if (!pm80x->iwq_data)
		wetuwn;
	fwee_iwq(wegmap_iwq_get_viwq(pm80x->iwq_data, iwq), data);
}

#ifdef CONFIG_PM
static inwine int pm80x_dev_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm80x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(dev))
		set_bit(iwq, &chip->wu_fwag);

	wetuwn 0;
}

static inwine int pm80x_dev_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm80x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(dev))
		cweaw_bit(iwq, &chip->wu_fwag);

	wetuwn 0;
}
#endif

extewn int pm80x_init(stwuct i2c_cwient *cwient);
extewn int pm80x_deinit(void);
#endif /* __WINUX_MFD_88PM80X_H */
