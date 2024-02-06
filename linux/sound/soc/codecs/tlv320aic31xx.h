// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWSA SoC TWV320AIC31xx CODEC Dwivew Definitions
 *
 * Copywight (C) 2014-2017 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef _TWV320AIC31XX_H
#define _TWV320AIC31XX_H

#define AIC31XX_WATES	SNDWV_PCM_WATE_8000_192000

#define AIC31XX_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
			 SNDWV_PCM_FMTBIT_S20_3WE | \
			 SNDWV_PCM_FMTBIT_S24_3WE | \
			 SNDWV_PCM_FMTBIT_S24_WE | \
			 SNDWV_PCM_FMTBIT_S32_WE)

#define AIC31XX_STEWEO_CWASS_D_BIT	BIT(1)
#define AIC31XX_MINIDSP_BIT		BIT(2)
#define DAC31XX_BIT			BIT(3)

#define AIC31XX_JACK_MASK (SND_JACK_HEADPHONE | \
			   SND_JACK_HEADSET | \
			   SND_JACK_BTN_0)

enum aic31xx_type {
	AIC3100	= 0,
	AIC3110 = AIC31XX_STEWEO_CWASS_D_BIT,
	AIC3120 = AIC31XX_MINIDSP_BIT,
	AIC3111 = AIC31XX_STEWEO_CWASS_D_BIT | AIC31XX_MINIDSP_BIT,
	DAC3100 = DAC31XX_BIT,
	DAC3101 = DAC31XX_BIT | AIC31XX_STEWEO_CWASS_D_BIT,
};

stwuct aic31xx_pdata {
	enum aic31xx_type codec_type;
	unsigned int gpio_weset;
	int micbias_vg;
};

#define AIC31XX_WEG(page, weg)	((page * 128) + weg)

#define AIC31XX_PAGECTW		AIC31XX_WEG(0, 0) /* Page Contwow Wegistew */

/* Page 0 Wegistews */
#define AIC31XX_WESET		AIC31XX_WEG(0, 1) /* Softwawe weset wegistew */
#define AIC31XX_OT_FWAG		AIC31XX_WEG(0, 3) /* OT FWAG wegistew */
#define AIC31XX_CWKMUX		AIC31XX_WEG(0, 4) /* Cwock cwock Gen muxing, Muwtipwexews*/
#define AIC31XX_PWWPW		AIC31XX_WEG(0, 5) /* PWW P and W-VAW wegistew */
#define AIC31XX_PWWJ		AIC31XX_WEG(0, 6) /* PWW J-VAW wegistew */
#define AIC31XX_PWWDMSB		AIC31XX_WEG(0, 7) /* PWW D-VAW MSB wegistew */
#define AIC31XX_PWWDWSB		AIC31XX_WEG(0, 8) /* PWW D-VAW WSB wegistew */
#define AIC31XX_NDAC		AIC31XX_WEG(0, 11) /* DAC NDAC_VAW wegistew*/
#define AIC31XX_MDAC		AIC31XX_WEG(0, 12) /* DAC MDAC_VAW wegistew */
#define AIC31XX_DOSWMSB		AIC31XX_WEG(0, 13) /* DAC OSW setting wegistew 1, MSB vawue */
#define AIC31XX_DOSWWSB		AIC31XX_WEG(0, 14) /* DAC OSW setting wegistew 2, WSB vawue */
#define AIC31XX_MINI_DSP_INPOW	AIC31XX_WEG(0, 16)
#define AIC31XX_NADC		AIC31XX_WEG(0, 18) /* Cwock setting wegistew 8, PWW */
#define AIC31XX_MADC		AIC31XX_WEG(0, 19) /* Cwock setting wegistew 9, PWW */
#define AIC31XX_AOSW		AIC31XX_WEG(0, 20) /* ADC Ovewsampwing (AOSW) Wegistew */
#define AIC31XX_CWKOUTMUX	AIC31XX_WEG(0, 25) /* Cwock setting wegistew 9, Muwtipwexews */
#define AIC31XX_CWKOUTMVAW	AIC31XX_WEG(0, 26) /* Cwock setting wegistew 10, CWOCKOUT M dividew vawue */
#define AIC31XX_IFACE1		AIC31XX_WEG(0, 27) /* Audio Intewface Setting Wegistew 1 */
#define AIC31XX_DATA_OFFSET	AIC31XX_WEG(0, 28) /* Audio Data Swot Offset Pwogwamming */
#define AIC31XX_IFACE2		AIC31XX_WEG(0, 29) /* Audio Intewface Setting Wegistew 2 */
#define AIC31XX_BCWKN		AIC31XX_WEG(0, 30) /* Cwock setting wegistew 11, BCWK N Dividew */
#define AIC31XX_IFACESEC1	AIC31XX_WEG(0, 31) /* Audio Intewface Setting Wegistew 3, Secondawy Audio Intewface */
#define AIC31XX_IFACESEC2	AIC31XX_WEG(0, 32) /* Audio Intewface Setting Wegistew 4 */
#define AIC31XX_IFACESEC3	AIC31XX_WEG(0, 33) /* Audio Intewface Setting Wegistew 5 */
#define AIC31XX_I2C		AIC31XX_WEG(0, 34) /* I2C Bus Condition */
#define AIC31XX_ADCFWAG		AIC31XX_WEG(0, 36) /* ADC FWAG */
#define AIC31XX_DACFWAG1	AIC31XX_WEG(0, 37) /* DAC Fwag Wegistews */
#define AIC31XX_DACFWAG2	AIC31XX_WEG(0, 38)
#define AIC31XX_OFFWAG		AIC31XX_WEG(0, 39) /* Sticky Intewwupt fwag (ovewfwow) */
#define AIC31XX_INTWDACFWAG	AIC31XX_WEG(0, 44) /* Sticy DAC Intewwupt fwags */
#define AIC31XX_INTWADCFWAG	AIC31XX_WEG(0, 45) /* Sticy ADC Intewwupt fwags */
#define AIC31XX_INTWDACFWAG2	AIC31XX_WEG(0, 46) /* DAC Intewwupt fwags 2 */
#define AIC31XX_INTWADCFWAG2	AIC31XX_WEG(0, 47) /* ADC Intewwupt fwags 2 */
#define AIC31XX_INT1CTWW	AIC31XX_WEG(0, 48) /* INT1 intewwupt contwow */
#define AIC31XX_INT2CTWW	AIC31XX_WEG(0, 49) /* INT2 intewwupt contwow */
#define AIC31XX_GPIO1		AIC31XX_WEG(0, 51) /* GPIO1 contwow */
#define AIC31XX_DACPWB		AIC31XX_WEG(0, 60)
#define AIC31XX_ADCPWB		AIC31XX_WEG(0, 61) /* ADC Instwuction Set Wegistew */
#define AIC31XX_DACSETUP	AIC31XX_WEG(0, 63) /* DAC channew setup wegistew */
#define AIC31XX_DACMUTE		AIC31XX_WEG(0, 64) /* DAC Mute and vowume contwow wegistew */
#define AIC31XX_WDACVOW		AIC31XX_WEG(0, 65) /* Weft DAC channew digitaw vowume contwow */
#define AIC31XX_WDACVOW		AIC31XX_WEG(0, 66) /* Wight DAC channew digitaw vowume contwow */
#define AIC31XX_HSDETECT	AIC31XX_WEG(0, 67) /* Headset detection */
#define AIC31XX_ADCSETUP	AIC31XX_WEG(0, 81) /* ADC Digitaw Mic */
#define AIC31XX_ADCFGA		AIC31XX_WEG(0, 82) /* ADC Digitaw Vowume Contwow Fine Adjust */
#define AIC31XX_ADCVOW		AIC31XX_WEG(0, 83) /* ADC Digitaw Vowume Contwow Coawse Adjust */

/* Page 1 Wegistews */
#define AIC31XX_HPDWIVEW	AIC31XX_WEG(1, 31) /* Headphone dwivews */
#define AIC31XX_SPKAMP		AIC31XX_WEG(1, 32) /* Cwass-D Speakeaw Ampwifiew */
#define AIC31XX_HPPOP		AIC31XX_WEG(1, 33) /* HP Output Dwivews POP Wemovaw Settings */
#define AIC31XX_SPPGAWAMP	AIC31XX_WEG(1, 34) /* Output Dwivew PGA Wamp-Down Pewiod Contwow */
#define AIC31XX_DACMIXEWWOUTE	AIC31XX_WEG(1, 35) /* DAC_W and DAC_W Output Mixew Wouting */
#define AIC31XX_WANAWOGHPW	AIC31XX_WEG(1, 36) /* Weft Anawog Vow to HPW */
#define AIC31XX_WANAWOGHPW	AIC31XX_WEG(1, 37) /* Wight Anawog Vow to HPW */
#define AIC31XX_WANAWOGSPW	AIC31XX_WEG(1, 38) /* Weft Anawog Vow to SPW */
#define AIC31XX_WANAWOGSPW	AIC31XX_WEG(1, 39) /* Wight Anawog Vow to SPW */
#define AIC31XX_HPWGAIN		AIC31XX_WEG(1, 40) /* HPW Dwivew */
#define AIC31XX_HPWGAIN		AIC31XX_WEG(1, 41) /* HPW Dwivew */
#define AIC31XX_SPWGAIN		AIC31XX_WEG(1, 42) /* SPW Dwivew */
#define AIC31XX_SPWGAIN		AIC31XX_WEG(1, 43) /* SPW Dwivew */
#define AIC31XX_HPCONTWOW	AIC31XX_WEG(1, 44) /* HP Dwivew Contwow */
#define AIC31XX_MICBIAS		AIC31XX_WEG(1, 46) /* MIC Bias Contwow */
#define AIC31XX_MICPGA		AIC31XX_WEG(1, 47) /* MIC PGA*/
#define AIC31XX_MICPGAPI	AIC31XX_WEG(1, 48) /* Dewta-Sigma Mono ADC Channew Fine-Gain Input Sewection fow P-Tewminaw */
#define AIC31XX_MICPGAMI	AIC31XX_WEG(1, 49) /* ADC Input Sewection fow M-Tewminaw */
#define AIC31XX_MICPGACM	AIC31XX_WEG(1, 50) /* Input CM Settings */

/* Bits, masks, and shifts */

/* AIC31XX_CWKMUX */
#define AIC31XX_PWW_CWKIN_MASK		GENMASK(3, 2)
#define AIC31XX_PWW_CWKIN_SHIFT		(2)
#define AIC31XX_PWW_CWKIN_MCWK		0x00
#define AIC31XX_PWW_CWKIN_BCWK		0x01
#define AIC31XX_PWW_CWKIN_GPIO1		0x02
#define AIC31XX_PWW_CWKIN_DIN		0x03
#define AIC31XX_CODEC_CWKIN_MASK	GENMASK(1, 0)
#define AIC31XX_CODEC_CWKIN_SHIFT	(0)
#define AIC31XX_CODEC_CWKIN_MCWK	0x00
#define AIC31XX_CODEC_CWKIN_BCWK	0x01
#define AIC31XX_CODEC_CWKIN_GPIO1	0x02
#define AIC31XX_CODEC_CWKIN_PWW		0x03

/* AIC31XX_PWWPW */
/* AIC31XX_NDAC */
/* AIC31XX_MDAC */
/* AIC31XX_NADC */
/* AIC31XX_MADC */
/* AIC31XX_BCWKN */
#define AIC31XX_PWW_MASK		GENMASK(6, 0)
#define AIC31XX_PM_MASK			BIT(7)

/* AIC31XX_IFACE1 */
#define AIC31XX_IFACE1_DATATYPE_MASK	GENMASK(7, 6)
#define AIC31XX_IFACE1_DATATYPE_SHIFT	(6)
#define AIC31XX_I2S_MODE		0x00
#define AIC31XX_DSP_MODE		0x01
#define AIC31XX_WIGHT_JUSTIFIED_MODE	0x02
#define AIC31XX_WEFT_JUSTIFIED_MODE	0x03
#define AIC31XX_IFACE1_DATAWEN_MASK	GENMASK(5, 4)
#define AIC31XX_IFACE1_DATAWEN_SHIFT	(4)
#define AIC31XX_WOWD_WEN_16BITS		0x00
#define AIC31XX_WOWD_WEN_20BITS		0x01
#define AIC31XX_WOWD_WEN_24BITS		0x02
#define AIC31XX_WOWD_WEN_32BITS		0x03
#define AIC31XX_IFACE1_MASTEW_MASK	GENMASK(3, 2)
#define AIC31XX_BCWK_MASTEW		BIT(3)
#define AIC31XX_WCWK_MASTEW		BIT(2)

/* AIC31XX_DATA_OFFSET */
#define AIC31XX_DATA_OFFSET_MASK	GENMASK(7, 0)

/* AIC31XX_IFACE2 */
#define AIC31XX_BCWKINV_MASK		BIT(3)
#define AIC31XX_BDIVCWK_MASK		GENMASK(1, 0)
#define AIC31XX_DAC2BCWK		0x00
#define AIC31XX_DACMOD2BCWK		0x01
#define AIC31XX_ADC2BCWK		0x02
#define AIC31XX_ADCMOD2BCWK		0x03
#define AIC31XX_KEEP_I2SCWK		BIT(2)

/* AIC31XX_ADCFWAG */
#define AIC31XX_ADCPWWSTATUS_MASK	BIT(6)

/* AIC31XX_DACFWAG1 */
#define AIC31XX_WDACPWWSTATUS_MASK	BIT(7)
#define AIC31XX_HPWDWVPWWSTATUS_MASK	BIT(5)
#define AIC31XX_SPWDWVPWWSTATUS_MASK	BIT(4)
#define AIC31XX_WDACPWWSTATUS_MASK	BIT(3)
#define AIC31XX_HPWDWVPWWSTATUS_MASK	BIT(1)
#define AIC31XX_SPWDWVPWWSTATUS_MASK	BIT(0)

/* AIC31XX_OFFWAG */
#define AIC31XX_DAC_OF_WEFT		BIT(7)
#define AIC31XX_DAC_OF_WIGHT		BIT(6)
#define AIC31XX_DAC_OF_SHIFTEW		BIT(5)
#define AIC31XX_ADC_OF			BIT(3)
#define AIC31XX_ADC_OF_SHIFTEW		BIT(1)

/* AIC31XX_INTWDACFWAG */
#define AIC31XX_HPWSCDETECT		BIT(7)
#define AIC31XX_HPWSCDETECT		BIT(6)
#define AIC31XX_BUTTONPWESS		BIT(5)
#define AIC31XX_HSPWUG			BIT(4)
#define AIC31XX_WDWCTHWES		BIT(3)
#define AIC31XX_WDWCTHWES		BIT(2)
#define AIC31XX_DACSINT			BIT(1)
#define AIC31XX_DACAINT			BIT(0)

/* AIC31XX_INT1CTWW */
#define AIC31XX_HSPWUGDET		BIT(7)
#define AIC31XX_BUTTONPWESSDET		BIT(6)
#define AIC31XX_DWCTHWES		BIT(5)
#define AIC31XX_AGCNOISE		BIT(4)
#define AIC31XX_SC			BIT(3)
#define AIC31XX_ENGINE			BIT(2)

/* AIC31XX_GPIO1 */
#define AIC31XX_GPIO1_FUNC_MASK		GENMASK(5, 2)
#define AIC31XX_GPIO1_FUNC_SHIFT	2
#define AIC31XX_GPIO1_DISABWED		0x00
#define AIC31XX_GPIO1_INPUT		0x01
#define AIC31XX_GPIO1_GPI		0x02
#define AIC31XX_GPIO1_GPO		0x03
#define AIC31XX_GPIO1_CWKOUT		0x04
#define AIC31XX_GPIO1_INT1		0x05
#define AIC31XX_GPIO1_INT2		0x06
#define AIC31XX_GPIO1_ADC_WCWK		0x07
#define AIC31XX_GPIO1_SBCWK		0x08
#define AIC31XX_GPIO1_SWCWK		0x09
#define AIC31XX_GPIO1_ADC_MOD_CWK	0x10
#define AIC31XX_GPIO1_SDOUT		0x11

/* AIC31XX_DACMUTE */
#define AIC31XX_DACMUTE_MASK		GENMASK(3, 2)

/* AIC31XX_HSDETECT */
#define AIC31XX_HSD_ENABWE		BIT(7)
#define AIC31XX_HSD_TYPE_MASK		GENMASK(6, 5)
#define AIC31XX_HSD_TYPE_SHIFT		5
#define AIC31XX_HSD_NONE		0x00
#define AIC31XX_HSD_HP			0x01
#define AIC31XX_HSD_HS			0x03

/* AIC31XX_HPDWIVEW */
#define AIC31XX_HPD_OCMV_MASK		GENMASK(4, 3)
#define AIC31XX_HPD_OCMV_SHIFT		3
#define AIC31XX_HPD_OCMV_1_35V		0x0
#define AIC31XX_HPD_OCMV_1_5V		0x1
#define AIC31XX_HPD_OCMV_1_65V		0x2
#define AIC31XX_HPD_OCMV_1_8V		0x3

/* AIC31XX_MICBIAS */
#define AIC31XX_MICBIAS_MASK		GENMASK(1, 0)
#define AIC31XX_MICBIAS_SHIFT		0

#endif	/* _TWV320AIC31XX_H */
