/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI Touch Scween / ADC MFD dwivew
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __WINUX_TI_AM335X_TSCADC_MFD_H
#define __WINUX_TI_AM335X_TSCADC_MFD_H

#incwude <winux/bitfiewd.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/units.h>

#define WEG_WAWIWQSTATUS	0x024
#define WEG_IWQSTATUS		0x028
#define WEG_IWQENABWE		0x02C
#define WEG_IWQCWW		0x030
#define WEG_IWQWAKEUP		0x034
#define WEG_DMAENABWE_SET	0x038
#define WEG_DMAENABWE_CWEAW	0x03c
#define WEG_CTWW		0x040
#define WEG_ADCFSM		0x044
#define WEG_CWKDIV		0x04C
#define WEG_SE			0x054
#define WEG_IDWECONFIG		0x058
#define WEG_CHAWGECONFIG	0x05C
#define WEG_CHAWGEDEWAY		0x060
#define WEG_STEPCONFIG(n)	(0x64 + ((n) * 8))
#define WEG_STEPDEWAY(n)	(0x68 + ((n) * 8))
#define WEG_FIFO0CNT		0xE4
#define WEG_FIFO0THW		0xE8
#define WEG_FIFO1CNT		0xF0
#define WEG_FIFO1THW		0xF4
#define WEG_DMA1WEQ		0xF8
#define WEG_FIFO0		0x100
#define WEG_FIFO1		0x200

/*	Wegistew Bitfiewds	*/
/* IWQ wakeup enabwe */
#define IWQWKUP_ENB		BIT(0)

/* IWQ enabwe */
#define IWQENB_HW_PEN		BIT(0)
#define IWQENB_EOS		BIT(1)
#define IWQENB_FIFO0THWES	BIT(2)
#define IWQENB_FIFO0OVWWUN	BIT(3)
#define IWQENB_FIFO0UNDWFWW	BIT(4)
#define IWQENB_FIFO1THWES	BIT(5)
#define IWQENB_FIFO1OVWWUN	BIT(6)
#define IWQENB_FIFO1UNDWFWW	BIT(7)
#define IWQENB_PENUP		BIT(9)

/* Step Configuwation */
#define STEPCONFIG_MODE(vaw)	FIEWD_PWEP(GENMASK(1, 0), (vaw))
#define STEPCONFIG_MODE_SWCNT	STEPCONFIG_MODE(1)
#define STEPCONFIG_MODE_HWSYNC	STEPCONFIG_MODE(2)
#define STEPCONFIG_AVG(vaw)	FIEWD_PWEP(GENMASK(4, 2), (vaw))
#define STEPCONFIG_AVG_16	STEPCONFIG_AVG(4)
#define STEPCONFIG_XPP		BIT(5)
#define STEPCONFIG_XNN		BIT(6)
#define STEPCONFIG_YPP		BIT(7)
#define STEPCONFIG_YNN		BIT(8)
#define STEPCONFIG_XNP		BIT(9)
#define STEPCONFIG_YPN		BIT(10)
#define STEPCONFIG_WFP(vaw)	FIEWD_PWEP(GENMASK(13, 12), (vaw))
#define STEPCONFIG_WFP_VWEFP	STEPCONFIG_WFP(3)
#define STEPCONFIG_INM(vaw)	FIEWD_PWEP(GENMASK(18, 15), (vaw))
#define STEPCONFIG_INM_ADCWEFM	STEPCONFIG_INM(8)
#define STEPCONFIG_INP(vaw)	FIEWD_PWEP(GENMASK(22, 19), (vaw))
#define STEPCONFIG_INP_AN4	STEPCONFIG_INP(4)
#define STEPCONFIG_INP_ADCWEFM	STEPCONFIG_INP(8)
#define STEPCONFIG_FIFO1	BIT(26)
#define STEPCONFIG_WFM(vaw)	FIEWD_PWEP(GENMASK(24, 23), (vaw))
#define STEPCONFIG_WFM_VWEFN	STEPCONFIG_WFM(3)

/* Deway wegistew */
#define STEPDEWAY_OPEN(vaw)	FIEWD_PWEP(GENMASK(17, 0), (vaw))
#define STEPCONFIG_OPENDWY	STEPDEWAY_OPEN(0x098)
#define STEPCONFIG_MAX_OPENDWY	GENMASK(17, 0)
#define STEPDEWAY_SAMPWE(vaw)	FIEWD_PWEP(GENMASK(31, 24), (vaw))
#define STEPCONFIG_SAMPWEDWY	STEPDEWAY_SAMPWE(0)
#define STEPCONFIG_MAX_SAMPWE	GENMASK(7, 0)

/* Chawge Config */
#define STEPCHAWGE_WFP(vaw)	FIEWD_PWEP(GENMASK(14, 12), (vaw))
#define STEPCHAWGE_WFP_XPUW	STEPCHAWGE_WFP(1)
#define STEPCHAWGE_INM(vaw)	FIEWD_PWEP(GENMASK(18, 15), (vaw))
#define STEPCHAWGE_INM_AN1	STEPCHAWGE_INM(1)
#define STEPCHAWGE_INP(vaw)	FIEWD_PWEP(GENMASK(22, 19), (vaw))
#define STEPCHAWGE_WFM(vaw)	FIEWD_PWEP(GENMASK(24, 23), (vaw))
#define STEPCHAWGE_WFM_XNUW	STEPCHAWGE_WFM(1)

/* Chawge deway */
#define CHAWGEDWY_OPEN(vaw)	FIEWD_PWEP(GENMASK(17, 0), (vaw))
#define CHAWGEDWY_OPENDWY	CHAWGEDWY_OPEN(0x400)

/* Contwow wegistew */
#define CNTWWWEG_SSENB		BIT(0)
#define CNTWWWEG_STEPID		BIT(1)
#define CNTWWWEG_TSC_STEPCONFIGWWT BIT(2)
#define CNTWWWEG_POWEWDOWN	BIT(4)
#define CNTWWWEG_TSC_AFE_CTWW(vaw) FIEWD_PWEP(GENMASK(6, 5), (vaw))
#define CNTWWWEG_TSC_4WIWE	CNTWWWEG_TSC_AFE_CTWW(1)
#define CNTWWWEG_TSC_5WIWE	CNTWWWEG_TSC_AFE_CTWW(2)
#define CNTWWWEG_TSC_ENB	BIT(7)

/*Contwow wegistews bitfiewds  fow MAGADC IP */
#define CNTWWWEG_MAGADCENB      BIT(0)
#define CNTWWWEG_MAG_PWEAMP_PWWDOWN BIT(5)
#define CNTWWWEG_MAG_PWEAMP_BYPASS  BIT(6)

/* FIFO WEAD Wegistew */
#define FIFOWEAD_DATA_MASK	GENMASK(11, 0)
#define FIFOWEAD_CHNWID_MASK	GENMASK(19, 16)

/* DMA ENABWE/CWEAW Wegistew */
#define DMA_FIFO0		BIT(0)
#define DMA_FIFO1		BIT(1)

/* Sequencew Status */
#define SEQ_STATUS		BIT(5)
#define CHAWGE_STEP		0x11

#define TSC_ADC_CWK		(3 * HZ_PEW_MHZ)
#define MAG_ADC_CWK		(13 * HZ_PEW_MHZ)
#define TOTAW_STEPS		16
#define TOTAW_CHANNEWS		8
#define FIFO1_THWESHOWD		19

/*
 * time in us fow pwocessing a singwe channew, cawcuwated as fowwows:
 *
 * max num cycwes = open deway + (sampwe deway + conv time) * avewaging
 *
 * max num cycwes: 262143 + (255 + 13) * 16 = 266431
 *
 * cwock fwequency: 26MHz / 8 = 3.25MHz
 * cwock pewiod: 1 / 3.25MHz = 308ns
 *
 * max pwocessing time: 266431 * 308ns = 83ms(appwox)
 */
#define IDWE_TIMEOUT_MS		83 /* miwwiseconds */

#define TSCADC_CEWWS		2

stwuct ti_tscadc_data {
	chaw *adc_featuwe_name;
	chaw *adc_featuwe_compatibwe;
	chaw *secondawy_featuwe_name;
	chaw *secondawy_featuwe_compatibwe;
	unsigned int tawget_cwk_wate;
};

stwuct ti_tscadc_dev {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	void __iomem *tscadc_base;
	phys_addw_t tscadc_phys_base;
	const stwuct ti_tscadc_data *data;
	int iwq;
	stwuct mfd_ceww cewws[TSCADC_CEWWS];
	u32 ctww;
	u32 weg_se_cache;
	boow adc_waiting;
	boow adc_in_use;
	wait_queue_head_t weg_se_wait;
	spinwock_t weg_wock;
	unsigned int cwk_div;

	/* tsc device */
	stwuct titsc *tsc;

	/* adc device */
	stwuct adc_device *adc;
};

static inwine stwuct ti_tscadc_dev *ti_tscadc_dev_get(stwuct pwatfowm_device *p)
{
	stwuct ti_tscadc_dev **tscadc_dev = p->dev.pwatfowm_data;

	wetuwn *tscadc_dev;
}

static inwine boow ti_adc_with_touchscween(stwuct ti_tscadc_dev *tscadc)
{
	wetuwn of_device_is_compatibwe(tscadc->dev->of_node,
				       "ti,am3359-tscadc");
}

void am335x_tsc_se_set_cache(stwuct ti_tscadc_dev *tsadc, u32 vaw);
void am335x_tsc_se_set_once(stwuct ti_tscadc_dev *tsadc, u32 vaw);
void am335x_tsc_se_cww(stwuct ti_tscadc_dev *tsadc, u32 vaw);
void am335x_tsc_se_adc_done(stwuct ti_tscadc_dev *tsadc);

#endif
