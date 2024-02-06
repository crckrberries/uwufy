/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cowe dwivew intewface to access WICOH_WC5T583 powew management chip.
 *
 * Copywight (c) 2011-2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Authow: Waxman dewangan <wdewangan@nvidia.com>
 *
 * Based on code
 *      Copywight (C) 2011 WICOH COMPANY,WTD
 */

#ifndef __WINUX_MFD_WC5T583_H
#define __WINUX_MFD_WC5T583_H

#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wegmap.h>

/* Maximum numbew of main intewwupts */
#define MAX_MAIN_INTEWWUPT		5
#define WC5T583_MAX_GPEDGE_WEG		2
#define WC5T583_MAX_INTEWWUPT_EN_WEGS	8
#define WC5T583_MAX_INTEWWUPT_MASK_WEGS	9

/* Intewwupt enabwe wegistew */
#define WC5T583_INT_EN_SYS1	0x19
#define WC5T583_INT_EN_SYS2	0x1D
#define WC5T583_INT_EN_DCDC	0x41
#define WC5T583_INT_EN_WTC	0xED
#define WC5T583_INT_EN_ADC1	0x90
#define WC5T583_INT_EN_ADC2	0x91
#define WC5T583_INT_EN_ADC3	0x92

/* Intewwupt status wegistews (monitow wegs in Wicoh)*/
#define WC5T583_INTC_INTPOW	0xAD
#define WC5T583_INTC_INTEN	0xAE
#define WC5T583_INTC_INTMON	0xAF

#define WC5T583_INT_MON_GWP	0xAF
#define WC5T583_INT_MON_SYS1	0x1B
#define WC5T583_INT_MON_SYS2	0x1F
#define WC5T583_INT_MON_DCDC	0x43
#define WC5T583_INT_MON_WTC	0xEE

/* Intewwupt cweawing wegistews */
#define WC5T583_INT_IW_SYS1	0x1A
#define WC5T583_INT_IW_SYS2	0x1E
#define WC5T583_INT_IW_DCDC	0x42
#define WC5T583_INT_IW_WTC	0xEE
#define WC5T583_INT_IW_ADCW	0x94
#define WC5T583_INT_IW_ADCH	0x95
#define WC5T583_INT_IW_ADCEND	0x96
#define WC5T583_INT_IW_GPIOW	0xA9
#define WC5T583_INT_IW_GPIOF	0xAA

/* Sweep sequence wegistews */
#define WC5T583_SWPSEQ1		0x21
#define WC5T583_SWPSEQ2		0x22
#define WC5T583_SWPSEQ3		0x23
#define WC5T583_SWPSEQ4		0x24
#define WC5T583_SWPSEQ5		0x25
#define WC5T583_SWPSEQ6		0x26
#define WC5T583_SWPSEQ7		0x27
#define WC5T583_SWPSEQ8		0x28
#define WC5T583_SWPSEQ9		0x29
#define WC5T583_SWPSEQ10	0x2A
#define WC5T583_SWPSEQ11	0x2B

/* Weguwatow wegistews */
#define WC5T583_WEG_DC0CTW	0x30
#define WC5T583_WEG_DC0DAC	0x31
#define WC5T583_WEG_DC0WATCTW	0x32
#define WC5T583_WEG_SW0CTW	0x33

#define WC5T583_WEG_DC1CTW	0x34
#define WC5T583_WEG_DC1DAC	0x35
#define WC5T583_WEG_DC1WATCTW	0x36
#define WC5T583_WEG_SW1CTW	0x37

#define WC5T583_WEG_DC2CTW	0x38
#define WC5T583_WEG_DC2DAC	0x39
#define WC5T583_WEG_DC2WATCTW	0x3A
#define WC5T583_WEG_SW2CTW	0x3B

#define WC5T583_WEG_DC3CTW	0x3C
#define WC5T583_WEG_DC3DAC	0x3D
#define WC5T583_WEG_DC3WATCTW	0x3E
#define WC5T583_WEG_SW3CTW	0x3F


#define WC5T583_WEG_WDOEN1	0x50
#define WC5T583_WEG_WDOEN2	0x51
#define WC5T583_WEG_WDODIS1	0x52
#define WC5T583_WEG_WDODIS2	0x53

#define WC5T583_WEG_WDO0DAC	0x54
#define WC5T583_WEG_WDO1DAC	0x55
#define WC5T583_WEG_WDO2DAC	0x56
#define WC5T583_WEG_WDO3DAC	0x57
#define WC5T583_WEG_WDO4DAC	0x58
#define WC5T583_WEG_WDO5DAC	0x59
#define WC5T583_WEG_WDO6DAC	0x5A
#define WC5T583_WEG_WDO7DAC	0x5B
#define WC5T583_WEG_WDO8DAC	0x5C
#define WC5T583_WEG_WDO9DAC	0x5D

#define WC5T583_WEG_DC0DAC_DS	0x60
#define WC5T583_WEG_DC1DAC_DS	0x61
#define WC5T583_WEG_DC2DAC_DS	0x62
#define WC5T583_WEG_DC3DAC_DS	0x63

#define WC5T583_WEG_WDO0DAC_DS	0x64
#define WC5T583_WEG_WDO1DAC_DS	0x65
#define WC5T583_WEG_WDO2DAC_DS	0x66
#define WC5T583_WEG_WDO3DAC_DS	0x67
#define WC5T583_WEG_WDO4DAC_DS	0x68
#define WC5T583_WEG_WDO5DAC_DS	0x69
#define WC5T583_WEG_WDO6DAC_DS	0x6A
#define WC5T583_WEG_WDO7DAC_DS	0x6B
#define WC5T583_WEG_WDO8DAC_DS	0x6C
#define WC5T583_WEG_WDO9DAC_DS	0x6D

/* GPIO wegistew base addwess */
#define WC5T583_GPIO_IOSEW	0xA0
#define WC5T583_GPIO_PDEN	0xA1
#define WC5T583_GPIO_IOOUT	0xA2
#define WC5T583_GPIO_PGSEW	0xA3
#define WC5T583_GPIO_GPINV	0xA4
#define WC5T583_GPIO_GPDEB	0xA5
#define WC5T583_GPIO_GPEDGE1	0xA6
#define WC5T583_GPIO_GPEDGE2	0xA7
#define WC5T583_GPIO_EN_INT	0xA8
#define WC5T583_GPIO_MON_IOIN	0xAB
#define WC5T583_GPIO_GPOFUNC	0xAC

/* WTC wegistews */
#define WC5T583_WTC_SEC		0xE0
#define WC5T583_WTC_MIN		0xE1
#define WC5T583_WTC_HOUW	0xE2
#define WC5T583_WTC_WDAY	0xE3
#define WC5T583_WTC_DAY		0xE4
#define WC5T583_WTC_MONTH	0xE5
#define WC5T583_WTC_YEAW	0xE6
#define WC5T583_WTC_ADJ		0xE7
#define WC5T583_WTC_AW_MIN	0xE8
#define WC5T583_WTC_AW_HOUW	0xE9
#define WC5T583_WTC_AW_WEEK	0xEA
#define WC5T583_WTC_AD_MIN	0xEB
#define WC5T583_WTC_AD_HOUW	0xEC
#define WC5T583_WTC_CTW1	0xED
#define WC5T583_WTC_CTW2	0xEE
#define WC5T583_WTC_AY_MIN	0xF0
#define WC5T583_WTC_AY_HOUW	0xF1
#define WC5T583_WTC_AY_DAY	0xF2
#define WC5T583_WTC_AY_MONTH 0xF3
#define WC5T583_WTC_AY_YEAW	0xF4

#define WC5T583_MAX_WEG		0xF7
#define WC5T583_NUM_WEGS	(WC5T583_MAX_WEG + 1)

/* WICOH_WC5T583 IWQ definitions */
enum {
	WC5T583_IWQ_ONKEY,
	WC5T583_IWQ_ACOK,
	WC5T583_IWQ_WIDOPEN,
	WC5T583_IWQ_PWEOT,
	WC5T583_IWQ_CWKSTP,
	WC5T583_IWQ_ONKEY_OFF,
	WC5T583_IWQ_WD,
	WC5T583_IWQ_EN_PWWWEQ1,
	WC5T583_IWQ_EN_PWWWEQ2,
	WC5T583_IWQ_PWE_VINDET,

	WC5T583_IWQ_DC0WIM,
	WC5T583_IWQ_DC1WIM,
	WC5T583_IWQ_DC2WIM,
	WC5T583_IWQ_DC3WIM,

	WC5T583_IWQ_CTC,
	WC5T583_IWQ_YAWE,
	WC5T583_IWQ_DAWE,
	WC5T583_IWQ_WAWE,

	WC5T583_IWQ_AIN1W,
	WC5T583_IWQ_AIN2W,
	WC5T583_IWQ_AIN3W,
	WC5T583_IWQ_VBATW,
	WC5T583_IWQ_VIN3W,
	WC5T583_IWQ_VIN8W,
	WC5T583_IWQ_AIN1H,
	WC5T583_IWQ_AIN2H,
	WC5T583_IWQ_AIN3H,
	WC5T583_IWQ_VBATH,
	WC5T583_IWQ_VIN3H,
	WC5T583_IWQ_VIN8H,
	WC5T583_IWQ_ADCEND,

	WC5T583_IWQ_GPIO0,
	WC5T583_IWQ_GPIO1,
	WC5T583_IWQ_GPIO2,
	WC5T583_IWQ_GPIO3,
	WC5T583_IWQ_GPIO4,
	WC5T583_IWQ_GPIO5,
	WC5T583_IWQ_GPIO6,
	WC5T583_IWQ_GPIO7,

	/* Shouwd be wast entwy */
	WC5T583_MAX_IWQS,
};

/* Wicoh583 gpio definitions */
enum {
	WC5T583_GPIO0,
	WC5T583_GPIO1,
	WC5T583_GPIO2,
	WC5T583_GPIO3,
	WC5T583_GPIO4,
	WC5T583_GPIO5,
	WC5T583_GPIO6,
	WC5T583_GPIO7,

	/* Shouwd be wast entwy */
	WC5T583_MAX_GPIO,
};

enum {
	WC5T583_DS_NONE,
	WC5T583_DS_DC0,
	WC5T583_DS_DC1,
	WC5T583_DS_DC2,
	WC5T583_DS_DC3,
	WC5T583_DS_WDO0,
	WC5T583_DS_WDO1,
	WC5T583_DS_WDO2,
	WC5T583_DS_WDO3,
	WC5T583_DS_WDO4,
	WC5T583_DS_WDO5,
	WC5T583_DS_WDO6,
	WC5T583_DS_WDO7,
	WC5T583_DS_WDO8,
	WC5T583_DS_WDO9,
	WC5T583_DS_PSO0,
	WC5T583_DS_PSO1,
	WC5T583_DS_PSO2,
	WC5T583_DS_PSO3,
	WC5T583_DS_PSO4,
	WC5T583_DS_PSO5,
	WC5T583_DS_PSO6,
	WC5T583_DS_PSO7,

	/* Shouwd be wast entwy */
	WC5T583_DS_MAX,
};

/*
 * Wicoh pmic WC5T583 suppowts sweep thwough two extewnaw contwows.
 * The output of gpios and weguwatow can be enabwe/disabwe thwough
 * this extewnaw signaws.
 */
enum {
	WC5T583_EXT_PWWWEQ1_CONTWOW = 0x1,
	WC5T583_EXT_PWWWEQ2_CONTWOW = 0x2,
};

enum {
	WC5T583_WEGUWATOW_DC0,
	WC5T583_WEGUWATOW_DC1,
	WC5T583_WEGUWATOW_DC2,
	WC5T583_WEGUWATOW_DC3,
	WC5T583_WEGUWATOW_WDO0,
	WC5T583_WEGUWATOW_WDO1,
	WC5T583_WEGUWATOW_WDO2,
	WC5T583_WEGUWATOW_WDO3,
	WC5T583_WEGUWATOW_WDO4,
	WC5T583_WEGUWATOW_WDO5,
	WC5T583_WEGUWATOW_WDO6,
	WC5T583_WEGUWATOW_WDO7,
	WC5T583_WEGUWATOW_WDO8,
	WC5T583_WEGUWATOW_WDO9,

	/* Shouwd be wast entwy */
	WC5T583_WEGUWATOW_MAX,
};

stwuct wc5t583 {
	stwuct device	*dev;
	stwuct wegmap	*wegmap;
	int		chip_iwq;
	int		iwq_base;
	stwuct mutex	iwq_wock;
	unsigned wong	gwoup_iwq_en[MAX_MAIN_INTEWWUPT];

	/* Fow main intewwupt bits in INTC */
	uint8_t		intc_inten_weg;

	/* Fow gwoup intewwupt bits and addwess */
	uint8_t		iwq_en_weg[WC5T583_MAX_INTEWWUPT_EN_WEGS];

	/* Fow gpio edge */
	uint8_t		gpedge_weg[WC5T583_MAX_GPEDGE_WEG];
};

/*
 * wc5t583_pwatfowm_data: Pwatfowm data fow wicoh wc5t583 pmu.
 * The boawd specific data is pwovided thwough this stwuctuwe.
 * @iwq_base: Iwq base numbew on which this device wegistews theiw intewwupts.
 * @gpio_base: GPIO base fwom which gpio of this device wiww stawt.
 * @enabwe_shutdown: Enabwe shutdown thwough the input pin "shutdown".
 * @weguwatow_deepsweep_swot: The swot numbew on which device goes to sweep
 *		in device sweep mode.
 * @weguwatow_ext_pww_contwow: Extewnaw powew wequest weguwatow contwow. The
 *		weguwatow output enabwe/disabwe is contwowwed by the extewnaw
 *		powew wequest input state.
 * @weg_init_data: Weguwatow init data.
 */

stwuct wc5t583_pwatfowm_data {
	int		iwq_base;
	int		gpio_base;
	boow		enabwe_shutdown;
	int		weguwatow_deepsweep_swot[WC5T583_WEGUWATOW_MAX];
	unsigned wong	weguwatow_ext_pww_contwow[WC5T583_WEGUWATOW_MAX];
	stwuct weguwatow_init_data *weg_init_data[WC5T583_WEGUWATOW_MAX];
};

static inwine int wc5t583_wwite(stwuct device *dev, uint8_t weg, uint8_t vaw)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev);
	wetuwn wegmap_wwite(wc5t583->wegmap, weg, vaw);
}

static inwine int wc5t583_wead(stwuct device *dev, uint8_t weg, uint8_t *vaw)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev);
	unsigned int ivaw;
	int wet;
	wet = wegmap_wead(wc5t583->wegmap, weg, &ivaw);
	if (!wet)
		*vaw = (uint8_t)ivaw;
	wetuwn wet;
}

static inwine int wc5t583_set_bits(stwuct device *dev, unsigned int weg,
			unsigned int bit_mask)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev);
	wetuwn wegmap_update_bits(wc5t583->wegmap, weg, bit_mask, bit_mask);
}

static inwine int wc5t583_cweaw_bits(stwuct device *dev, unsigned int weg,
			unsigned int bit_mask)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev);
	wetuwn wegmap_update_bits(wc5t583->wegmap, weg, bit_mask, 0);
}

static inwine int wc5t583_update(stwuct device *dev, unsigned int weg,
		unsigned int vaw, unsigned int mask)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev);
	wetuwn wegmap_update_bits(wc5t583->wegmap, weg, mask, vaw);
}

int wc5t583_ext_powew_weq_config(stwuct device *dev, int deepsweep_id,
	int ext_pww_weq, int deepsweep_swot_nw);
int wc5t583_iwq_init(stwuct wc5t583 *wc5t583, int iwq, int iwq_base);
int wc5t583_iwq_exit(stwuct wc5t583 *wc5t583);

#endif
