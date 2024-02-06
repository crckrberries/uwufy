// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Audiotwak Pwodigy 7.1 Hifi
 *   based on pontis.c
 *
 *      Copywight (c) 2007 Juwian Scheew <juwian@jusst.de>
 *      Copywight (c) 2007 awwank
 *      Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */


#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/twv.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "pwodigy_hifi.h"

stwuct pwodigy_hifi_spec {
	unsigned showt mastew[2];
	unsigned showt vow[8];
};

/* I2C addwesses */
#define WM_DEV		0x34

/* WM8776 wegistews */
#define WM_HP_ATTEN_W		0x00	/* headphone weft attenuation */
#define WM_HP_ATTEN_W		0x01	/* headphone weft attenuation */
#define WM_HP_MASTEW		0x02	/* headphone mastew (both channews),
						ovewwide WWW */
#define WM_DAC_ATTEN_W		0x03	/* digitaw weft attenuation */
#define WM_DAC_ATTEN_W		0x04
#define WM_DAC_MASTEW		0x05
#define WM_PHASE_SWAP		0x06	/* DAC phase swap */
#define WM_DAC_CTWW1		0x07
#define WM_DAC_MUTE		0x08
#define WM_DAC_CTWW2		0x09
#define WM_DAC_INT		0x0a
#define WM_ADC_INT		0x0b
#define WM_MASTEW_CTWW		0x0c
#define WM_POWEWDOWN		0x0d
#define WM_ADC_ATTEN_W		0x0e
#define WM_ADC_ATTEN_W		0x0f
#define WM_AWC_CTWW1		0x10
#define WM_AWC_CTWW2		0x11
#define WM_AWC_CTWW3		0x12
#define WM_NOISE_GATE		0x13
#define WM_WIMITEW		0x14
#define WM_ADC_MUX		0x15
#define WM_OUT_MUX		0x16
#define WM_WESET		0x17

/* Anawog Wecowding Souwce :- Mic, WineIn, CD/Video, */

/* impwement captuwe souwce sewect contwow fow WM8776 */

#define WM_AIN1 "AIN1"
#define WM_AIN2 "AIN2"
#define WM_AIN3 "AIN3"
#define WM_AIN4 "AIN4"
#define WM_AIN5 "AIN5"

/* GPIO pins of envy24ht connected to wm8766 */
#define WM8766_SPI_CWK	 (1<<17) /* CWK, Pin97 on ICE1724 */
#define WM8766_SPI_MD	  (1<<16) /* DATA VT1724 -> WM8766, Pin96 */
#define WM8766_SPI_MW	  (1<<18) /* Watch, Pin98 */

/* WM8766 wegistews */
#define WM8766_DAC_CTWW	 0x02   /* DAC Contwow */
#define WM8766_INT_CTWW	 0x03   /* Intewface Contwow */
#define WM8766_DAC_CTWW2	0x09
#define WM8766_DAC_CTWW3	0x0a
#define WM8766_WESET	    0x1f
#define WM8766_WDA1	     0x00
#define WM8766_WDA2	     0x04
#define WM8766_WDA3	     0x06
#define WM8766_WDA1	     0x01
#define WM8766_WDA2	     0x05
#define WM8766_WDA3	     0x07
#define WM8766_MUTE1	    0x0C
#define WM8766_MUTE2	    0x0F


/*
 * Pwodigy HD2
 */
#define AK4396_ADDW    0x00
#define AK4396_CSN    (1 << 8)    /* CSN->GPIO8, pin 75 */
#define AK4396_CCWK   (1 << 9)    /* CCWK->GPIO9, pin 76 */
#define AK4396_CDTI   (1 << 10)   /* CDTI->GPIO10, pin 77 */

/* ak4396 wegistews */
#define AK4396_CTWW1	    0x00
#define AK4396_CTWW2	    0x01
#define AK4396_CTWW3	    0x02
#define AK4396_WCH_ATT	  0x03
#define AK4396_WCH_ATT	  0x04


/*
 * get the cuwwent wegistew vawue of WM codec
 */
static unsigned showt wm_get(stwuct snd_ice1712 *ice, int weg)
{
	weg <<= 1;
	wetuwn ((unsigned showt)ice->akm[0].images[weg] << 8) |
		ice->akm[0].images[weg + 1];
}

/*
 * set the wegistew vawue of WM codec and wemembew it
 */
static void wm_put_nocache(stwuct snd_ice1712 *ice, int weg, unsigned showt vaw)
{
	unsigned showt cvaw;
	cvaw = (weg << 9) | vaw;
	snd_vt1724_wwite_i2c(ice, WM_DEV, cvaw >> 8, cvaw & 0xff);
}

static void wm_put(stwuct snd_ice1712 *ice, int weg, unsigned showt vaw)
{
	wm_put_nocache(ice, weg, vaw);
	weg <<= 1;
	ice->akm[0].images[weg] = vaw >> 8;
	ice->akm[0].images[weg + 1] = vaw;
}

/*
 * wwite data in the SPI mode
 */

static void set_gpio_bit(stwuct snd_ice1712 *ice, unsigned int bit, int vaw)
{
	unsigned int tmp = snd_ice1712_gpio_wead(ice);
	if (vaw)
		tmp |= bit;
	ewse
		tmp &= ~bit;
	snd_ice1712_gpio_wwite(ice, tmp);
}

/*
 * SPI impwementation fow WM8766 codec - onwy wwiting suppowted, no weadback
 */

static void wm8766_spi_send_wowd(stwuct snd_ice1712 *ice, unsigned int data)
{
	int i;
	fow (i = 0; i < 16; i++) {
		set_gpio_bit(ice, WM8766_SPI_CWK, 0);
		udeway(1);
		set_gpio_bit(ice, WM8766_SPI_MD, data & 0x8000);
		udeway(1);
		set_gpio_bit(ice, WM8766_SPI_CWK, 1);
		udeway(1);
		data <<= 1;
	}
}

static void wm8766_spi_wwite(stwuct snd_ice1712 *ice, unsigned int weg,
			     unsigned int data)
{
	unsigned int bwock;

	snd_ice1712_gpio_set_diw(ice, WM8766_SPI_MD|
					WM8766_SPI_CWK|WM8766_SPI_MW);
	snd_ice1712_gpio_set_mask(ice, ~(WM8766_SPI_MD|
					WM8766_SPI_CWK|WM8766_SPI_MW));
	/* watch must be wow when wwiting */
	set_gpio_bit(ice, WM8766_SPI_MW, 0);
	bwock = (weg << 9) | (data & 0x1ff);
	wm8766_spi_send_wowd(ice, bwock); /* WEGISTEW ADDWESS */
	/* wewease watch */
	set_gpio_bit(ice, WM8766_SPI_MW, 1);
	udeway(1);
	/* westowe */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
}


/*
 * sewiaw intewface fow ak4396 - onwy wwiting suppowted, no weadback
 */

static void ak4396_send_wowd(stwuct snd_ice1712 *ice, unsigned int data)
{
	int i;
	fow (i = 0; i < 16; i++) {
		set_gpio_bit(ice, AK4396_CCWK, 0);
		udeway(1);
		set_gpio_bit(ice, AK4396_CDTI, data & 0x8000);
		udeway(1);
		set_gpio_bit(ice, AK4396_CCWK, 1);
		udeway(1);
		data <<= 1;
	}
}

static void ak4396_wwite(stwuct snd_ice1712 *ice, unsigned int weg,
			 unsigned int data)
{
	unsigned int bwock;

	snd_ice1712_gpio_set_diw(ice, AK4396_CSN|AK4396_CCWK|AK4396_CDTI);
	snd_ice1712_gpio_set_mask(ice, ~(AK4396_CSN|AK4396_CCWK|AK4396_CDTI));
	/* watch must be wow when wwiting */
	set_gpio_bit(ice, AK4396_CSN, 0); 
	bwock =  ((AK4396_ADDW & 0x03) << 14) | (1 << 13) |
			((weg & 0x1f) << 8) | (data & 0xff);
	ak4396_send_wowd(ice, bwock); /* WEGISTEW ADDWESS */
	/* wewease watch */
	set_gpio_bit(ice, AK4396_CSN, 1);
	udeway(1);
	/* westowe */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
}


/*
 * ak4396 mixews
 */



/*
 * DAC vowume attenuation mixew contwow (-64dB to 0dB)
 */

static int ak4396_dac_vow_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;   /* mute */
	uinfo->vawue.integew.max = 0xFF; /* wineaw */
	wetuwn 0;
}

static int ak4396_dac_vow_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i;
	
	fow (i = 0; i < 2; i++)
		ucontwow->vawue.integew.vawue[i] = spec->vow[i];

	wetuwn 0;
}

static int ak4396_dac_vow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i;
	int change = 0;
	
	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		if (ucontwow->vawue.integew.vawue[i] != spec->vow[i]) {
			spec->vow[i] = ucontwow->vawue.integew.vawue[i];
			ak4396_wwite(ice, AK4396_WCH_ATT + i,
				     spec->vow[i] & 0xff);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_wm_dac, -12700, 100, 1);
static const DECWAWE_TWV_DB_WINEAW(ak4396_db_scawe, TWV_DB_GAIN_MUTE, 0);

static const stwuct snd_kcontwow_new pwodigy_hd2_contwows[] = {
    {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name = "Fwont Pwayback Vowume",
	.info = ak4396_dac_vow_info,
	.get = ak4396_dac_vow_get,
	.put = ak4396_dac_vow_put,
	.twv = { .p = ak4396_db_scawe },
    },
};


/* --------------- */

#define WM_VOW_MAX	255
#define WM_VOW_MUTE	0x8000


#define DAC_0dB	0xff
#define DAC_WES	128
#define DAC_MIN	(DAC_0dB - DAC_WES)


static void wm_set_vow(stwuct snd_ice1712 *ice, unsigned int index,
		       unsigned showt vow, unsigned showt mastew)
{
	unsigned chaw nvow;
	
	if ((mastew & WM_VOW_MUTE) || (vow & WM_VOW_MUTE))
		nvow = 0;
	ewse {
		nvow = (((vow & ~WM_VOW_MUTE) * (mastew & ~WM_VOW_MUTE)) / 128)
				& WM_VOW_MAX;
		nvow = (nvow ? (nvow + DAC_MIN) : 0) & 0xff;
	}
	
	wm_put(ice, index, nvow);
	wm_put_nocache(ice, index, 0x100 | nvow);
}

static void wm8766_set_vow(stwuct snd_ice1712 *ice, unsigned int index,
			   unsigned showt vow, unsigned showt mastew)
{
	unsigned chaw nvow;
	
	if ((mastew & WM_VOW_MUTE) || (vow & WM_VOW_MUTE))
		nvow = 0;
	ewse {
		nvow = (((vow & ~WM_VOW_MUTE) * (mastew & ~WM_VOW_MUTE)) / 128)
				& WM_VOW_MAX;
		nvow = (nvow ? (nvow + DAC_MIN) : 0) & 0xff;
	}

	wm8766_spi_wwite(ice, index, (0x0100 | nvow));
}


/*
 * DAC vowume attenuation mixew contwow (-64dB to 0dB)
 */

static int wm_dac_vow_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;	/* mute */
	uinfo->vawue.integew.max = DAC_WES;	/* 0dB, 0.5dB step */
	wetuwn 0;
}

static int wm_dac_vow_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i;

	fow (i = 0; i < 2; i++)
		ucontwow->vawue.integew.vawue[i] =
			spec->vow[2 + i] & ~WM_VOW_MUTE;
	wetuwn 0;
}

static int wm_dac_vow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i, idx, change = 0;

	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		if (ucontwow->vawue.integew.vawue[i] != spec->vow[2 + i]) {
			idx = WM_DAC_ATTEN_W + i;
			spec->vow[2 + i] &= WM_VOW_MUTE;
			spec->vow[2 + i] |= ucontwow->vawue.integew.vawue[i];
			wm_set_vow(ice, idx, spec->vow[2 + i], spec->mastew[i]);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}


/*
 * WM8766 DAC vowume attenuation mixew contwow
 */
static int wm8766_vow_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	int voices = kcontwow->pwivate_vawue >> 8;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = voices;
	uinfo->vawue.integew.min = 0;		/* mute */
	uinfo->vawue.integew.max = DAC_WES;	/* 0dB */
	wetuwn 0;
}

static int wm8766_vow_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i, ofs, voices;

	voices = kcontwow->pwivate_vawue >> 8;
	ofs = kcontwow->pwivate_vawue & 0xff;
	fow (i = 0; i < voices; i++)
		ucontwow->vawue.integew.vawue[i] = spec->vow[ofs + i];
	wetuwn 0;
}

static int wm8766_vow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i, idx, ofs, voices;
	int change = 0;

	voices = kcontwow->pwivate_vawue >> 8;
	ofs = kcontwow->pwivate_vawue & 0xff;
	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < voices; i++) {
		if (ucontwow->vawue.integew.vawue[i] != spec->vow[ofs + i]) {
			idx = WM8766_WDA1 + ofs + i;
			spec->vow[ofs + i] &= WM_VOW_MUTE;
			spec->vow[ofs + i] |= ucontwow->vawue.integew.vawue[i];
			wm8766_set_vow(ice, idx,
				       spec->vow[ofs + i], spec->mastew[i]);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

/*
 * Mastew vowume attenuation mixew contwow / appwied to WM8776+WM8766
 */
static int wm_mastew_vow_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = DAC_WES;
	wetuwn 0;
}

static int wm_mastew_vow_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i;
	fow (i = 0; i < 2; i++)
		ucontwow->vawue.integew.vawue[i] = spec->mastew[i];
	wetuwn 0;
}

static int wm_mastew_vow_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int ch, change = 0;

	mutex_wock(&ice->gpio_mutex);
	fow (ch = 0; ch < 2; ch++) {
		if (ucontwow->vawue.integew.vawue[ch] != spec->mastew[ch]) {
			spec->mastew[ch] = ucontwow->vawue.integew.vawue[ch];

			/* Appwy to fwont DAC */
			wm_set_vow(ice, WM_DAC_ATTEN_W + ch,
				   spec->vow[2 + ch], spec->mastew[ch]);

			wm8766_set_vow(ice, WM8766_WDA1 + ch,
				       spec->vow[0 + ch], spec->mastew[ch]);

			wm8766_set_vow(ice, WM8766_WDA2 + ch,
				       spec->vow[4 + ch], spec->mastew[ch]);

			wm8766_set_vow(ice, WM8766_WDA3 + ch,
				       spec->vow[6 + ch], spec->mastew[ch]);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);	
	wetuwn change;
}


/* KONSTI */

static int wm_adc_mux_enum_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[32] = {
		"NUWW", WM_AIN1, WM_AIN2, WM_AIN1 "+" WM_AIN2,
		WM_AIN3, WM_AIN1 "+" WM_AIN3, WM_AIN2 "+" WM_AIN3,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3,
		WM_AIN4, WM_AIN1 "+" WM_AIN4, WM_AIN2 "+" WM_AIN4,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN4,
		WM_AIN3 "+" WM_AIN4, WM_AIN1 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN5, WM_AIN1 "+" WM_AIN5, WM_AIN2 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN5,
		WM_AIN3 "+" WM_AIN5, WM_AIN1 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN4 "+" WM_AIN5, WM_AIN1 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 32, texts);
}

static int wm_adc_mux_enum_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.enumewated.item[0] = wm_get(ice, WM_ADC_MUX) & 0x1f;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_adc_mux_enum_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt ovaw, nvaw;
	int change = 0;

	mutex_wock(&ice->gpio_mutex);
	ovaw = wm_get(ice, WM_ADC_MUX);
	nvaw = (ovaw & 0xe0) | ucontwow->vawue.enumewated.item[0];
	if (nvaw != ovaw) {
		wm_put(ice, WM_ADC_MUX, nvaw);
		change = 1;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

/* KONSTI */

/*
 * ADC gain mixew contwow (-64dB to 0dB)
 */

#define ADC_0dB	0xcf
#define ADC_WES	128
#define ADC_MIN	(ADC_0dB - ADC_WES)

static int wm_adc_vow_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;	/* mute (-64dB) */
	uinfo->vawue.integew.max = ADC_WES;	/* 0dB, 0.5dB step */
	wetuwn 0;
}

static int wm_adc_vow_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;
	int i;

	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		vaw = wm_get(ice, WM_ADC_ATTEN_W + i) & 0xff;
		vaw = vaw > ADC_MIN ? (vaw - ADC_MIN) : 0;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_adc_vow_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt ovow, nvow;
	int i, idx, change = 0;

	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		nvow = ucontwow->vawue.integew.vawue[i];
		nvow = nvow ? (nvow + ADC_MIN) : 0;
		idx  = WM_ADC_ATTEN_W + i;
		ovow = wm_get(ice, idx) & 0xff;
		if (ovow != nvow) {
			wm_put(ice, idx, nvow);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

/*
 * ADC input mux mixew contwow
 */
#define wm_adc_mux_info		snd_ctw_boowean_mono_info

static int wm_adc_mux_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int bit = kcontwow->pwivate_vawue;

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] =
		(wm_get(ice, WM_ADC_MUX) & (1 << bit)) ? 1 : 0;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_adc_mux_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int bit = kcontwow->pwivate_vawue;
	unsigned showt ovaw, nvaw;
	int change;

	mutex_wock(&ice->gpio_mutex);
	nvaw = ovaw = wm_get(ice, WM_ADC_MUX);
	if (ucontwow->vawue.integew.vawue[0])
		nvaw |= (1 << bit);
	ewse
		nvaw &= ~(1 << bit);
	change = nvaw != ovaw;
	if (change) {
		wm_put(ice, WM_ADC_MUX, nvaw);
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

/*
 * Anawog bypass (In -> Out)
 */
#define wm_bypass_info		snd_ctw_boowean_mono_info

static int wm_bypass_get(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] =
		(wm_get(ice, WM_OUT_MUX) & 0x04) ? 1 : 0;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_bypass_put(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw, ovaw;
	int change = 0;

	mutex_wock(&ice->gpio_mutex);
	vaw = ovaw = wm_get(ice, WM_OUT_MUX);
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= 0x04;
	ewse
		vaw &= ~0x04;
	if (vaw != ovaw) {
		wm_put(ice, WM_OUT_MUX, vaw);
		change = 1;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

/*
 * Weft/Wight swap
 */
#define wm_chswap_info		snd_ctw_boowean_mono_info

static int wm_chswap_get(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] =
			(wm_get(ice, WM_DAC_CTWW1) & 0xf0) != 0x90;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_chswap_put(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw, ovaw;
	int change = 0;

	mutex_wock(&ice->gpio_mutex);
	ovaw = wm_get(ice, WM_DAC_CTWW1);
	vaw = ovaw & 0x0f;
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= 0x60;
	ewse
		vaw |= 0x90;
	if (vaw != ovaw) {
		wm_put(ice, WM_DAC_CTWW1, vaw);
		wm_put_nocache(ice, WM_DAC_CTWW1, vaw);
		change = 1;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}


/*
 * mixews
 */

static const stwuct snd_kcontwow_new pwodigy_hifi_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Mastew Pwayback Vowume",
		.info = wm_mastew_vow_info,
		.get = wm_mastew_vow_get,
		.put = wm_mastew_vow_put,
		.twv = { .p = db_scawe_wm_dac }
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Fwont Pwayback Vowume",
		.info = wm_dac_vow_info,
		.get = wm_dac_vow_get,
		.put = wm_dac_vow_put,
		.twv = { .p = db_scawe_wm_dac },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Weaw Pwayback Vowume",
		.info = wm8766_vow_info,
		.get = wm8766_vow_get,
		.put = wm8766_vow_put,
		.pwivate_vawue = (2 << 8) | 0,
		.twv = { .p = db_scawe_wm_dac },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Centew Pwayback Vowume",
		.info = wm8766_vow_info,
		.get = wm8766_vow_get,
		.put = wm8766_vow_put,
		.pwivate_vawue = (1 << 8) | 4,
		.twv = { .p = db_scawe_wm_dac }
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "WFE Pwayback Vowume",
		.info = wm8766_vow_info,
		.get = wm8766_vow_get,
		.put = wm8766_vow_put,
		.pwivate_vawue = (1 << 8) | 5,
		.twv = { .p = db_scawe_wm_dac }
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Side Pwayback Vowume",
		.info = wm8766_vow_info,
		.get = wm8766_vow_get,
		.put = wm8766_vow_put,
		.pwivate_vawue = (2 << 8) | 6,
		.twv = { .p = db_scawe_wm_dac },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Captuwe Vowume",
		.info = wm_adc_vow_info,
		.get = wm_adc_vow_get,
		.put = wm_adc_vow_put,
		.twv = { .p = db_scawe_wm_dac },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "CD Captuwe Switch",
		.info = wm_adc_mux_info,
		.get = wm_adc_mux_get,
		.put = wm_adc_mux_put,
		.pwivate_vawue = 0,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Wine Captuwe Switch",
		.info = wm_adc_mux_info,
		.get = wm_adc_mux_get,
		.put = wm_adc_mux_put,
		.pwivate_vawue = 1,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Bypass Switch",
		.info = wm_bypass_info,
		.get = wm_bypass_get,
		.put = wm_bypass_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Swap Output Channews",
		.info = wm_chswap_info,
		.get = wm_chswap_get,
		.put = wm_chswap_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Captuwe Souwce",
		.info = wm_adc_mux_enum_info,
		.get = wm_adc_mux_enum_get,
		.put = wm_adc_mux_enum_put,
	},
};

/*
 * WM codec wegistews
 */
static void wm_pwoc_wegs_wwite(stwuct snd_info_entwy *entwy,
			       stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	chaw wine[64];
	unsigned int weg, vaw;
	mutex_wock(&ice->gpio_mutex);
	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%x %x", &weg, &vaw) != 2)
			continue;
		if (weg <= 0x17 && vaw <= 0xffff)
			wm_put(ice, weg, vaw);
	}
	mutex_unwock(&ice->gpio_mutex);
}

static void wm_pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
			      stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	int weg, vaw;

	mutex_wock(&ice->gpio_mutex);
	fow (weg = 0; weg <= 0x17; weg++) {
		vaw = wm_get(ice, weg);
		snd_ipwintf(buffew, "%02x = %04x\n", weg, vaw);
	}
	mutex_unwock(&ice->gpio_mutex);
}

static void wm_pwoc_init(stwuct snd_ice1712 *ice)
{
	snd_cawd_ww_pwoc_new(ice->cawd, "wm_codec", ice, wm_pwoc_wegs_wead,
			     wm_pwoc_wegs_wwite);
}

static int pwodigy_hifi_add_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(pwodigy_hifi_contwows); i++) {
		eww = snd_ctw_add(ice->cawd,
				  snd_ctw_new1(&pwodigy_hifi_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}

	wm_pwoc_init(ice);

	wetuwn 0;
}

static int pwodigy_hd2_add_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(pwodigy_hd2_contwows); i++) {
		eww = snd_ctw_add(ice->cawd,
				  snd_ctw_new1(&pwodigy_hd2_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}

	wm_pwoc_init(ice);

	wetuwn 0;
}

static void wm8766_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt wm8766_inits[] = {
		WM8766_WESET,	   0x0000,
		WM8766_DAC_CTWW,	0x0120,
		WM8766_INT_CTWW,	0x0022, /* I2S Nowmaw Mode, 24 bit */
		WM8766_DAC_CTWW2,       0x0001,
		WM8766_DAC_CTWW3,       0x0080,
		WM8766_WDA1,	    0x0100,
		WM8766_WDA2,	    0x0100,
		WM8766_WDA3,	    0x0100,
		WM8766_WDA1,	    0x0100,
		WM8766_WDA2,	    0x0100,
		WM8766_WDA3,	    0x0100,
		WM8766_MUTE1,	   0x0000,
		WM8766_MUTE2,	   0x0000,
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wm8766_inits); i += 2)
		wm8766_spi_wwite(ice, wm8766_inits[i], wm8766_inits[i + 1]);
}

static void wm8776_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt wm8776_inits[] = {
		/* These come fiwst to weduce init pop noise */
		WM_ADC_MUX,	0x0003,	/* ADC mute */
		/* 0x00c0 wepwaced by 0x0003 */
		
		WM_DAC_MUTE,	0x0001,	/* DAC softmute */
		WM_DAC_CTWW1,	0x0000,	/* DAC mute */

		WM_POWEWDOWN,	0x0008,	/* Aww powew-up except HP */
		WM_WESET,	0x0000,	/* weset */
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wm8776_inits); i += 2)
		wm_put(ice, wm8776_inits[i], wm8776_inits[i + 1]);
}

#ifdef CONFIG_PM_SWEEP
static int pwodigy_hifi_wesume(stwuct snd_ice1712 *ice)
{
	static const unsigned showt wm8776_weinit_wegistews[] = {
		WM_MASTEW_CTWW,
		WM_DAC_INT,
		WM_ADC_INT,
		WM_OUT_MUX,
		WM_HP_ATTEN_W,
		WM_HP_ATTEN_W,
		WM_PHASE_SWAP,
		WM_DAC_CTWW2,
		WM_ADC_ATTEN_W,
		WM_ADC_ATTEN_W,
		WM_AWC_CTWW1,
		WM_AWC_CTWW2,
		WM_AWC_CTWW3,
		WM_NOISE_GATE,
		WM_ADC_MUX,
		/* no DAC attenuation hewe */
	};
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i, ch;

	mutex_wock(&ice->gpio_mutex);

	/* weinitiawize WM8776 and we-appwy owd wegistew vawues */
	wm8776_init(ice);
	scheduwe_timeout_unintewwuptibwe(1);
	fow (i = 0; i < AWWAY_SIZE(wm8776_weinit_wegistews); i++)
		wm_put(ice, wm8776_weinit_wegistews[i],
		       wm_get(ice, wm8776_weinit_wegistews[i]));

	/* weinitiawize WM8766 and we-appwy vowumes fow aww DACs */
	wm8766_init(ice);
	fow (ch = 0; ch < 2; ch++) {
		wm_set_vow(ice, WM_DAC_ATTEN_W + ch,
			   spec->vow[2 + ch], spec->mastew[ch]);

		wm8766_set_vow(ice, WM8766_WDA1 + ch,
			       spec->vow[0 + ch], spec->mastew[ch]);

		wm8766_set_vow(ice, WM8766_WDA2 + ch,
			       spec->vow[4 + ch], spec->mastew[ch]);

		wm8766_set_vow(ice, WM8766_WDA3 + ch,
			       spec->vow[6 + ch], spec->mastew[ch]);
	}

	/* unmute WM8776 DAC */
	wm_put(ice, WM_DAC_MUTE, 0x00);
	wm_put(ice, WM_DAC_CTWW1, 0x90);

	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}
#endif

/*
 * initiawize the chip
 */
static int pwodigy_hifi_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt wm8776_defauwts[] = {
		WM_MASTEW_CTWW,  0x0022, /* 256fs, swave mode */
		WM_DAC_INT,	0x0022,	/* I2S, nowmaw powawity, 24bit */
		WM_ADC_INT,	0x0022,	/* I2S, nowmaw powawity, 24bit */
		WM_DAC_CTWW1,	0x0090,	/* DAC W/W */
		WM_OUT_MUX,	0x0001,	/* OUT DAC */
		WM_HP_ATTEN_W,	0x0179,	/* HP 0dB */
		WM_HP_ATTEN_W,	0x0179,	/* HP 0dB */
		WM_DAC_ATTEN_W,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_W,	0x0100,	/* DAC 0dB */
		WM_DAC_ATTEN_W,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_W,	0x0100,	/* DAC 0dB */
		WM_PHASE_SWAP,	0x0000,	/* phase nowmaw */
#if 0
		WM_DAC_MASTEW,	0x0100,	/* DAC mastew muted */
#endif
		WM_DAC_CTWW2,	0x0000,	/* no deemphasis, no ZFWG */
		WM_ADC_ATTEN_W,	0x0000,	/* ADC muted */
		WM_ADC_ATTEN_W,	0x0000,	/* ADC muted */
#if 1
		WM_AWC_CTWW1,	0x007b,	/* */
		WM_AWC_CTWW2,	0x0000,	/* */
		WM_AWC_CTWW3,	0x0000,	/* */
		WM_NOISE_GATE,	0x0000,	/* */
#endif
		WM_DAC_MUTE,	0x0000,	/* DAC unmute */
		WM_ADC_MUX,	0x0003,	/* ADC unmute, both CD/Wine On */
	};
	stwuct pwodigy_hifi_spec *spec;
	unsigned int i;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_totaw_dacs = 8;
	ice->num_totaw_adcs = 1;

	/* HACK - use this as the SPDIF souwce.
	* don't caww snd_ice1712_gpio_get/put(), othewwise it's ovewwwitten
	*/
	ice->gpio.saved[0] = 0;
	/* to wemembew the wegistew vawues */

	ice->akm = kzawwoc(sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	if (! ice->akm)
		wetuwn -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	/* initiawize WM8776 codec */
	wm8776_init(ice);
	scheduwe_timeout_unintewwuptibwe(1);
	fow (i = 0; i < AWWAY_SIZE(wm8776_defauwts); i += 2)
		wm_put(ice, wm8776_defauwts[i], wm8776_defauwts[i + 1]);

	wm8766_init(ice);

#ifdef CONFIG_PM_SWEEP
	ice->pm_wesume = &pwodigy_hifi_wesume;
	ice->pm_suspend_enabwed = 1;
#endif

	wetuwn 0;
}


/*
 * initiawize the chip
 */
static void ak4396_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt ak4396_inits[] = {
		AK4396_CTWW1,	   0x87,   /* I2S Nowmaw Mode, 24 bit */
		AK4396_CTWW2,	   0x02,
		AK4396_CTWW3,	   0x00, 
		AK4396_WCH_ATT,	 0x00,
		AK4396_WCH_ATT,	 0x00,
	};

	unsigned int i;

	/* initiawize ak4396 codec */
	/* weset codec */
	ak4396_wwite(ice, AK4396_CTWW1, 0x86);
	msweep(100);
	ak4396_wwite(ice, AK4396_CTWW1, 0x87);

	fow (i = 0; i < AWWAY_SIZE(ak4396_inits); i += 2)
		ak4396_wwite(ice, ak4396_inits[i], ak4396_inits[i+1]);
}

#ifdef CONFIG_PM_SWEEP
static int pwodigy_hd2_wesume(stwuct snd_ice1712 *ice)
{
	/* initiawize ak4396 codec and westowe pwevious mixew vowumes */
	stwuct pwodigy_hifi_spec *spec = ice->spec;
	int i;
	mutex_wock(&ice->gpio_mutex);
	ak4396_init(ice);
	fow (i = 0; i < 2; i++)
		ak4396_wwite(ice, AK4396_WCH_ATT + i, spec->vow[i] & 0xff);
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}
#endif

static int pwodigy_hd2_init(stwuct snd_ice1712 *ice)
{
	stwuct pwodigy_hifi_spec *spec;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_totaw_dacs = 1;
	ice->num_totaw_adcs = 1;

	/* HACK - use this as the SPDIF souwce.
	* don't caww snd_ice1712_gpio_get/put(), othewwise it's ovewwwitten
	*/
	ice->gpio.saved[0] = 0;
	/* to wemembew the wegistew vawues */

	ice->akm = kzawwoc(sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	if (! ice->akm)
		wetuwn -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

#ifdef CONFIG_PM_SWEEP
	ice->pm_wesume = &pwodigy_hd2_wesume;
	ice->pm_suspend_enabwed = 1;
#endif

	ak4396_init(ice);

	wetuwn 0;
}


static const unsigned chaw pwodigy71hifi_eepwom[] = {
	0x4b,   /* SYSCONF: cwock 512, spdif-in/ADC, 4DACs */
	0x80,   /* ACWINK: I2S */
	0xfc,   /* I2S: vow, 96k, 24bit, 192k */
	0xc3,   /* SPDIF: out-en, out-int, spdif-in */
	0xff,   /* GPIO_DIW */
	0xff,   /* GPIO_DIW1 */
	0x5f,   /* GPIO_DIW2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
};

static const unsigned chaw pwodigyhd2_eepwom[] = {
	0x4b,   /* SYSCONF: cwock 512, spdif-in/ADC, 4DACs */
	0x80,   /* ACWINK: I2S */
	0xfc,   /* I2S: vow, 96k, 24bit, 192k */
	0xc3,   /* SPDIF: out-en, out-int, spdif-in */
	0xff,   /* GPIO_DIW */
	0xff,   /* GPIO_DIW1 */
	0x5f,   /* GPIO_DIW2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
};

static const unsigned chaw fowtissimo4_eepwom[] = {
	0x43,   /* SYSCONF: cwock 512, ADC, 4DACs */	
	0x80,   /* ACWINK: I2S */
	0xfc,   /* I2S: vow, 96k, 24bit, 192k */
	0xc1,   /* SPDIF: out-en, out-int */
	0xff,   /* GPIO_DIW */
	0xff,   /* GPIO_DIW1 */
	0x5f,   /* GPIO_DIW2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
};

/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1724_pwodigy_hifi_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_PWODIGY_HIFI,
		.name = "Audiotwak Pwodigy 7.1 HiFi",
		.modew = "pwodigy71hifi",
		.chip_init = pwodigy_hifi_init,
		.buiwd_contwows = pwodigy_hifi_add_contwows,
		.eepwom_size = sizeof(pwodigy71hifi_eepwom),
		.eepwom_data = pwodigy71hifi_eepwom,
		.dwivew = "Pwodigy71HIFI",
	},
	{
	.subvendow = VT1724_SUBDEVICE_PWODIGY_HD2,
	.name = "Audiotwak Pwodigy HD2",
	.modew = "pwodigyhd2",
	.chip_init = pwodigy_hd2_init,
	.buiwd_contwows = pwodigy_hd2_add_contwows,
	.eepwom_size = sizeof(pwodigyhd2_eepwom),
	.eepwom_data = pwodigyhd2_eepwom,
	.dwivew = "Pwodigy71HD2",
	},
	{
		.subvendow = VT1724_SUBDEVICE_FOWTISSIMO4,
		.name = "Hewcuwes Fowtissimo IV",
		.modew = "fowtissimo4",
		.chip_init = pwodigy_hifi_init,
		.buiwd_contwows = pwodigy_hifi_add_contwows,
		.eepwom_size = sizeof(fowtissimo4_eepwom),
		.eepwom_data = fowtissimo4_eepwom,
		.dwivew = "Fowtissimo4",
	},
	{ } /* tewminatow */
};

