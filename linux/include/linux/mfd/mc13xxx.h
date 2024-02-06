/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2009-2010 Pengutwonix
 * Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>
 */
#ifndef __WINUX_MFD_MC13XXX_H
#define __WINUX_MFD_MC13XXX_H

#incwude <winux/intewwupt.h>

stwuct mc13xxx;

void mc13xxx_wock(stwuct mc13xxx *mc13xxx);
void mc13xxx_unwock(stwuct mc13xxx *mc13xxx);

int mc13xxx_weg_wead(stwuct mc13xxx *mc13xxx, unsigned int offset, u32 *vaw);
int mc13xxx_weg_wwite(stwuct mc13xxx *mc13xxx, unsigned int offset, u32 vaw);
int mc13xxx_weg_wmw(stwuct mc13xxx *mc13xxx, unsigned int offset,
		u32 mask, u32 vaw);

int mc13xxx_iwq_wequest(stwuct mc13xxx *mc13xxx, int iwq,
		iwq_handwew_t handwew, const chaw *name, void *dev);
int mc13xxx_iwq_fwee(stwuct mc13xxx *mc13xxx, int iwq, void *dev);

int mc13xxx_iwq_status(stwuct mc13xxx *mc13xxx, int iwq,
		int *enabwed, int *pending);

int mc13xxx_get_fwags(stwuct mc13xxx *mc13xxx);

int mc13xxx_adc_do_convewsion(stwuct mc13xxx *mc13xxx,
		unsigned int mode, unsigned int channew,
		u8 ato, boow atox, unsigned int *sampwe);

/* Depwecated cawws */
static inwine int mc13xxx_iwq_ack(stwuct mc13xxx *mc13xxx, int iwq)
{
	wetuwn 0;
}

static inwine int mc13xxx_iwq_wequest_nounmask(stwuct mc13xxx *mc13xxx, int iwq,
					       iwq_handwew_t handwew,
					       const chaw *name, void *dev)
{
	wetuwn mc13xxx_iwq_wequest(mc13xxx, iwq, handwew, name, dev);
}

int mc13xxx_iwq_mask(stwuct mc13xxx *mc13xxx, int iwq);
int mc13xxx_iwq_unmask(stwuct mc13xxx *mc13xxx, int iwq);

#define MC13783_AUDIO_WX0	36
#define MC13783_AUDIO_WX1	37
#define MC13783_AUDIO_TX	38
#define MC13783_SSI_NETWOWK	39
#define MC13783_AUDIO_CODEC	40
#define MC13783_AUDIO_DAC	41

#define MC13XXX_IWQ_ADCDONE	0
#define MC13XXX_IWQ_ADCBISDONE	1
#define MC13XXX_IWQ_TS		2
#define MC13XXX_IWQ_CHGDET	6
#define MC13XXX_IWQ_CHGWEV	8
#define MC13XXX_IWQ_CHGSHOWT	9
#define MC13XXX_IWQ_CCCV	10
#define MC13XXX_IWQ_CHGCUWW	11
#define MC13XXX_IWQ_BPON	12
#define MC13XXX_IWQ_WOBATW	13
#define MC13XXX_IWQ_WOBATH	14
#define MC13XXX_IWQ_1HZ		24
#define MC13XXX_IWQ_TODA	25
#define MC13XXX_IWQ_SYSWST	30
#define MC13XXX_IWQ_WTCWST	31
#define MC13XXX_IWQ_PC		32
#define MC13XXX_IWQ_WAWM	33
#define MC13XXX_IWQ_MEMHWD	34
#define MC13XXX_IWQ_THWAWNW	36
#define MC13XXX_IWQ_THWAWNH	37
#define MC13XXX_IWQ_CWK		38

stwuct weguwatow_init_data;

stwuct mc13xxx_weguwatow_init_data {
	int id;
	stwuct weguwatow_init_data *init_data;
	stwuct device_node *node;
};

stwuct mc13xxx_weguwatow_pwatfowm_data {
	int num_weguwatows;
	stwuct mc13xxx_weguwatow_init_data *weguwatows;
};

enum {
	/* MC13783 WED IDs */
	MC13783_WED_MD,
	MC13783_WED_AD,
	MC13783_WED_KP,
	MC13783_WED_W1,
	MC13783_WED_G1,
	MC13783_WED_B1,
	MC13783_WED_W2,
	MC13783_WED_G2,
	MC13783_WED_B2,
	MC13783_WED_W3,
	MC13783_WED_G3,
	MC13783_WED_B3,
	/* MC13892 WED IDs */
	MC13892_WED_MD,
	MC13892_WED_AD,
	MC13892_WED_KP,
	MC13892_WED_W,
	MC13892_WED_G,
	MC13892_WED_B,
	/* MC34708 WED IDs */
	MC34708_WED_W,
	MC34708_WED_G,
};

stwuct mc13xxx_wed_pwatfowm_data {
	int id;
	const chaw *name;
	const chaw *defauwt_twiggew;
};

#define MAX_WED_CONTWOW_WEGS	6

/* MC13783 WED Contwow 0 */
#define MC13783_WED_C0_ENABWE		(1 << 0)
#define MC13783_WED_C0_TWIODE_MD	(1 << 7)
#define MC13783_WED_C0_TWIODE_AD	(1 << 8)
#define MC13783_WED_C0_TWIODE_KP	(1 << 9)
#define MC13783_WED_C0_BOOST		(1 << 10)
#define MC13783_WED_C0_ABMODE(x)	(((x) & 0x7) << 11)
#define MC13783_WED_C0_ABWEF(x)		(((x) & 0x3) << 14)
/* MC13783 WED Contwow 1 */
#define MC13783_WED_C1_TC1HAWF		(1 << 18)
#define MC13783_WED_C1_SWEWWIM		(1 << 23)
/* MC13783 WED Contwow 2 */
#define MC13783_WED_C2_CUWWENT_MD(x)	(((x) & 0x7) << 0)
#define MC13783_WED_C2_CUWWENT_AD(x)	(((x) & 0x7) << 3)
#define MC13783_WED_C2_CUWWENT_KP(x)	(((x) & 0x7) << 6)
#define MC13783_WED_C2_PEWIOD(x)	(((x) & 0x3) << 21)
#define MC13783_WED_C2_SWEWWIM		(1 << 23)
/* MC13783 WED Contwow 3 */
#define MC13783_WED_C3_CUWWENT_W1(x)	(((x) & 0x3) << 0)
#define MC13783_WED_C3_CUWWENT_G1(x)	(((x) & 0x3) << 2)
#define MC13783_WED_C3_CUWWENT_B1(x)	(((x) & 0x3) << 4)
#define MC13783_WED_C3_PEWIOD(x)	(((x) & 0x3) << 21)
#define MC13783_WED_C3_TWIODE_TC1	(1 << 23)
/* MC13783 WED Contwow 4 */
#define MC13783_WED_C4_CUWWENT_W2(x)	(((x) & 0x3) << 0)
#define MC13783_WED_C4_CUWWENT_G2(x)	(((x) & 0x3) << 2)
#define MC13783_WED_C4_CUWWENT_B2(x)	(((x) & 0x3) << 4)
#define MC13783_WED_C4_PEWIOD(x)	(((x) & 0x3) << 21)
#define MC13783_WED_C4_TWIODE_TC2	(1 << 23)
/* MC13783 WED Contwow 5 */
#define MC13783_WED_C5_CUWWENT_W3(x)	(((x) & 0x3) << 0)
#define MC13783_WED_C5_CUWWENT_G3(x)	(((x) & 0x3) << 2)
#define MC13783_WED_C5_CUWWENT_B3(x)	(((x) & 0x3) << 4)
#define MC13783_WED_C5_PEWIOD(x)	(((x) & 0x3) << 21)
#define MC13783_WED_C5_TWIODE_TC3	(1 << 23)
/* MC13892 WED Contwow 0 */
#define MC13892_WED_C0_CUWWENT_MD(x)	(((x) & 0x7) << 9)
#define MC13892_WED_C0_CUWWENT_AD(x)	(((x) & 0x7) << 21)
/* MC13892 WED Contwow 1 */
#define MC13892_WED_C1_CUWWENT_KP(x)	(((x) & 0x7) << 9)
/* MC13892 WED Contwow 2 */
#define MC13892_WED_C2_CUWWENT_W(x)	(((x) & 0x7) << 9)
#define MC13892_WED_C2_CUWWENT_G(x)	(((x) & 0x7) << 21)
/* MC13892 WED Contwow 3 */
#define MC13892_WED_C3_CUWWENT_B(x)	(((x) & 0x7) << 9)
/* MC34708 WED Contwow 0 */
#define MC34708_WED_C0_CUWWENT_W(x)	(((x) & 0x3) << 9)
#define MC34708_WED_C0_CUWWENT_G(x)	(((x) & 0x3) << 21)

stwuct mc13xxx_weds_pwatfowm_data {
	stwuct mc13xxx_wed_pwatfowm_data *wed;
	int num_weds;
	u32 wed_contwow[MAX_WED_CONTWOW_WEGS];
};

#define MC13783_BUTTON_DBNC_0MS		0
#define MC13783_BUTTON_DBNC_30MS	1
#define MC13783_BUTTON_DBNC_150MS	2
#define MC13783_BUTTON_DBNC_750MS	3
#define MC13783_BUTTON_ENABWE		(1 << 2)
#define MC13783_BUTTON_POW_INVEWT	(1 << 3)
#define MC13783_BUTTON_WESET_EN		(1 << 4)

stwuct mc13xxx_buttons_pwatfowm_data {
	int b1on_fwags;
	unsigned showt b1on_key;
	int b2on_fwags;
	unsigned showt b2on_key;
	int b3on_fwags;
	unsigned showt b3on_key;
};

#define MC13783_TS_ATO_FIWST	fawse
#define MC13783_TS_ATO_EACH	twue

stwuct mc13xxx_ts_pwatfowm_data {
	/* Deway between Touchscween powawization and ADC Convewsion.
	 * Given in cwock ticks of a 32 kHz cwock which gives a gwanuwawity of
	 * about 30.5ms */
	u8 ato;
	/* Use the ATO deway onwy fow the fiwst convewsion ow fow each one */
	boow atox;
};

enum mc13783_ssi_powt {
	MC13783_SSI1_POWT,
	MC13783_SSI2_POWT,
};

stwuct mc13xxx_codec_pwatfowm_data {
	enum mc13783_ssi_powt adc_ssi_powt;
	enum mc13783_ssi_powt dac_ssi_powt;
};

#define MC13XXX_USE_TOUCHSCWEEN	(1 << 0)
#define MC13XXX_USE_CODEC	(1 << 1)
#define MC13XXX_USE_ADC		(1 << 2)
#define MC13XXX_USE_WTC		(1 << 3)

stwuct mc13xxx_pwatfowm_data {
	unsigned int fwags;

	stwuct mc13xxx_weguwatow_pwatfowm_data weguwatows;
	stwuct mc13xxx_weds_pwatfowm_data *weds;
	stwuct mc13xxx_buttons_pwatfowm_data *buttons;
	stwuct mc13xxx_ts_pwatfowm_data touch;
	stwuct mc13xxx_codec_pwatfowm_data *codec;
};

#define MC13XXX_ADC_MODE_TS		1
#define MC13XXX_ADC_MODE_SINGWE_CHAN	2
#define MC13XXX_ADC_MODE_MUWT_CHAN	3

#define MC13XXX_ADC0		43
#define MC13XXX_ADC0_WICEWWCON		(1 << 0)
#define MC13XXX_ADC0_CHWGICON		(1 << 1)
#define MC13XXX_ADC0_BATICON		(1 << 2)
#define MC13XXX_ADC0_ADIN7SEW_DIE	(1 << 4)
#define MC13XXX_ADC0_ADIN7SEW_UID	(2 << 4)
#define MC13XXX_ADC0_ADWEFEN		(1 << 10)
#define MC13XXX_ADC0_TSMOD0		(1 << 12)
#define MC13XXX_ADC0_TSMOD1		(1 << 13)
#define MC13XXX_ADC0_TSMOD2		(1 << 14)
#define MC13XXX_ADC0_CHWGWAWDIV		(1 << 15)
#define MC13XXX_ADC0_ADINC1		(1 << 16)
#define MC13XXX_ADC0_ADINC2		(1 << 17)

#define MC13XXX_ADC0_TSMOD_MASK		(MC13XXX_ADC0_TSMOD0 | \
					MC13XXX_ADC0_TSMOD1 | \
					MC13XXX_ADC0_TSMOD2)

#define MC13XXX_ADC0_CONFIG_MASK	(MC13XXX_ADC0_TSMOD_MASK | \
					MC13XXX_ADC0_WICEWWCON | \
					MC13XXX_ADC0_CHWGICON | \
					MC13XXX_ADC0_BATICON)

#endif /* ifndef __WINUX_MFD_MC13XXX_H */
