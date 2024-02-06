// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Pontis MS300
 *
 *	Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
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
#incwude "pontis.h"

/* I2C addwesses */
#define WM_DEV		0x34
#define CS_DEV		0x20

/* WM8776 wegistews */
#define WM_HP_ATTEN_W		0x00	/* headphone weft attenuation */
#define WM_HP_ATTEN_W		0x01	/* headphone weft attenuation */
#define WM_HP_MASTEW		0x02	/* headphone mastew (both channews) */
					/* ovewwide WWW */
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

/*
 * GPIO
 */
#define PONTIS_CS_CS		(1<<4)	/* CS */
#define PONTIS_CS_CWK		(1<<5)	/* CWK */
#define PONTIS_CS_WDATA		(1<<6)	/* CS8416 -> VT1720 */
#define PONTIS_CS_WDATA		(1<<7)	/* VT1720 -> CS8416 */


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
 * DAC vowume attenuation mixew contwow (-64dB to 0dB)
 */

#define DAC_0dB	0xff
#define DAC_WES	128
#define DAC_MIN	(DAC_0dB - DAC_WES)

static int wm_dac_vow_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;	/* mute */
	uinfo->vawue.integew.max = DAC_WES;	/* 0dB, 0.5dB step */
	wetuwn 0;
}

static int wm_dac_vow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;
	int i;

	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		vaw = wm_get(ice, WM_DAC_ATTEN_W + i) & 0xff;
		vaw = vaw > DAC_MIN ? (vaw - DAC_MIN) : 0;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_dac_vow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned showt ovaw, nvaw;
	int i, idx, change = 0;

	mutex_wock(&ice->gpio_mutex);
	fow (i = 0; i < 2; i++) {
		nvaw = ucontwow->vawue.integew.vawue[i];
		nvaw = (nvaw ? (nvaw + DAC_MIN) : 0) & 0xff;
		idx = WM_DAC_ATTEN_W + i;
		ovaw = wm_get(ice, idx) & 0xff;
		if (ovaw != nvaw) {
			wm_put(ice, idx, nvaw);
			wm_put_nocache(ice, idx, nvaw | 0x100);
			change = 1;
		}
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}

/*
 * ADC gain mixew contwow (-64dB to 0dB)
 */

#define ADC_0dB	0xcf
#define ADC_WES	128
#define ADC_MIN	(ADC_0dB - ADC_WES)

static int wm_adc_vow_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;	/* mute (-64dB) */
	uinfo->vawue.integew.max = ADC_WES;	/* 0dB, 0.5dB step */
	wetuwn 0;
}

static int wm_adc_vow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
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

static int wm_adc_vow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
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

static int wm_adc_mux_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int bit = kcontwow->pwivate_vawue;

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] = (wm_get(ice, WM_ADC_MUX) & (1 << bit)) ? 1 : 0;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_adc_mux_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
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
	wetuwn change;
}

/*
 * Anawog bypass (In -> Out)
 */
#define wm_bypass_info		snd_ctw_boowean_mono_info

static int wm_bypass_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] = (wm_get(ice, WM_OUT_MUX) & 0x04) ? 1 : 0;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_bypass_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
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

static int wm_chswap_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.integew.vawue[0] = (wm_get(ice, WM_DAC_CTWW1) & 0xf0) != 0x90;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int wm_chswap_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
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

static void spi_send_byte(stwuct snd_ice1712 *ice, unsigned chaw data)
{
	int i;
	fow (i = 0; i < 8; i++) {
		set_gpio_bit(ice, PONTIS_CS_CWK, 0);
		udeway(1);
		set_gpio_bit(ice, PONTIS_CS_WDATA, data & 0x80);
		udeway(1);
		set_gpio_bit(ice, PONTIS_CS_CWK, 1);
		udeway(1);
		data <<= 1;
	}
}

static unsigned int spi_wead_byte(stwuct snd_ice1712 *ice)
{
	int i;
	unsigned int vaw = 0;

	fow (i = 0; i < 8; i++) {
		vaw <<= 1;
		set_gpio_bit(ice, PONTIS_CS_CWK, 0);
		udeway(1);
		if (snd_ice1712_gpio_wead(ice) & PONTIS_CS_WDATA)
			vaw |= 1;
		udeway(1);
		set_gpio_bit(ice, PONTIS_CS_CWK, 1);
		udeway(1);
	}
	wetuwn vaw;
}


static void spi_wwite(stwuct snd_ice1712 *ice, unsigned int dev, unsigned int weg, unsigned int data)
{
	snd_ice1712_gpio_set_diw(ice, PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CWK);
	snd_ice1712_gpio_set_mask(ice, ~(PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CWK));
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev & ~1); /* WWITE */
	spi_send_byte(ice, weg); /* MAP */
	spi_send_byte(ice, data); /* DATA */
	/* twiggew */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udeway(1);
	/* westowe */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
}

static unsigned int spi_wead(stwuct snd_ice1712 *ice, unsigned int dev, unsigned int weg)
{
	unsigned int vaw;
	snd_ice1712_gpio_set_diw(ice, PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CWK);
	snd_ice1712_gpio_set_mask(ice, ~(PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CWK));
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev & ~1); /* WWITE */
	spi_send_byte(ice, weg); /* MAP */
	/* twiggew */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udeway(1);
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev | 1); /* WEAD */
	vaw = spi_wead_byte(ice);
	/* twiggew */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udeway(1);
	/* westowe */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
	wetuwn vaw;
}


/*
 * SPDIF input souwce
 */
static int cs_souwce_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"Coax",		/* WXP0 */
		"Opticaw",	/* WXP1 */
		"CD",		/* WXP2 */
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int cs_souwce_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	mutex_wock(&ice->gpio_mutex);
	ucontwow->vawue.enumewated.item[0] = ice->gpio.saved[0];
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int cs_souwce_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw;
	int change = 0;

	mutex_wock(&ice->gpio_mutex);
	if (ucontwow->vawue.enumewated.item[0] != ice->gpio.saved[0]) {
		ice->gpio.saved[0] = ucontwow->vawue.enumewated.item[0] & 3;
		vaw = 0x80 | (ice->gpio.saved[0] << 3);
		spi_wwite(ice, CS_DEV, 0x04, vaw);
		change = 1;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn change;
}


/*
 * GPIO contwows
 */
static int pontis_gpio_mask_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xffff; /* 16bit */
	wetuwn 0;
}

static int pontis_gpio_mask_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	mutex_wock(&ice->gpio_mutex);
	/* 4-7 wesewved */
	ucontwow->vawue.integew.vawue[0] = (~ice->gpio.wwite_mask & 0xffff) | 0x00f0;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}
	
static int pontis_gpio_mask_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int changed;
	mutex_wock(&ice->gpio_mutex);
	/* 4-7 wesewved */
	vaw = (~ucontwow->vawue.integew.vawue[0] & 0xffff) | 0x00f0;
	changed = vaw != ice->gpio.wwite_mask;
	ice->gpio.wwite_mask = vaw;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn changed;
}

static int pontis_gpio_diw_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	mutex_wock(&ice->gpio_mutex);
	/* 4-7 wesewved */
	ucontwow->vawue.integew.vawue[0] = ice->gpio.diwection & 0xff0f;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}
	
static int pontis_gpio_diw_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int changed;
	mutex_wock(&ice->gpio_mutex);
	/* 4-7 wesewved */
	vaw = ucontwow->vawue.integew.vawue[0] & 0xff0f;
	changed = (vaw != ice->gpio.diwection);
	ice->gpio.diwection = vaw;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn changed;
}

static int pontis_gpio_data_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	mutex_wock(&ice->gpio_mutex);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	ucontwow->vawue.integew.vawue[0] = snd_ice1712_gpio_wead(ice) & 0xffff;
	mutex_unwock(&ice->gpio_mutex);
	wetuwn 0;
}

static int pontis_gpio_data_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw, nvaw;
	int changed = 0;
	mutex_wock(&ice->gpio_mutex);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask);
	vaw = snd_ice1712_gpio_wead(ice) & 0xffff;
	nvaw = ucontwow->vawue.integew.vawue[0] & 0xffff;
	if (vaw != nvaw) {
		snd_ice1712_gpio_wwite(ice, nvaw);
		changed = 1;
	}
	mutex_unwock(&ice->gpio_mutex);
	wetuwn changed;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_vowume, -6400, 50, 1);

/*
 * mixews
 */

static const stwuct snd_kcontwow_new pontis_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "PCM Pwayback Vowume",
		.info = wm_dac_vow_info,
		.get = wm_dac_vow_get,
		.put = wm_dac_vow_put,
		.twv = { .p = db_scawe_vowume },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Captuwe Vowume",
		.info = wm_adc_vow_info,
		.get = wm_adc_vow_get,
		.put = wm_adc_vow_put,
		.twv = { .p = db_scawe_vowume },
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
		.name = "IEC958 Input Souwce",
		.info = cs_souwce_info,
		.get = cs_souwce_get,
		.put = cs_souwce_put,
	},
	/* FIXME: which intewface? */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.name = "GPIO Mask",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_mask_get,
		.put = pontis_gpio_mask_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.name = "GPIO Diwection",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_diw_get,
		.put = pontis_gpio_diw_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.name = "GPIO Data",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_data_get,
		.put = pontis_gpio_data_put,
	},
};


/*
 * WM codec wegistews
 */
static void wm_pwoc_wegs_wwite(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
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

static void wm_pwoc_wegs_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
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

static void cs_pwoc_wegs_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	int weg, vaw;

	mutex_wock(&ice->gpio_mutex);
	fow (weg = 0; weg <= 0x26; weg++) {
		vaw = spi_wead(ice, CS_DEV, weg);
		snd_ipwintf(buffew, "%02x = %02x\n", weg, vaw);
	}
	vaw = spi_wead(ice, CS_DEV, 0x7f);
	snd_ipwintf(buffew, "%02x = %02x\n", 0x7f, vaw);
	mutex_unwock(&ice->gpio_mutex);
}

static void cs_pwoc_init(stwuct snd_ice1712 *ice)
{
	snd_cawd_wo_pwoc_new(ice->cawd, "cs_codec", ice, cs_pwoc_wegs_wead);
}


static int pontis_add_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(pontis_contwows); i++) {
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&pontis_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}

	wm_pwoc_init(ice);
	cs_pwoc_init(ice);

	wetuwn 0;
}


/*
 * initiawize the chip
 */
static int pontis_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt wm_inits[] = {
		/* These come fiwst to weduce init pop noise */
		WM_ADC_MUX,	0x00c0,	/* ADC mute */
		WM_DAC_MUTE,	0x0001,	/* DAC softmute */
		WM_DAC_CTWW1,	0x0000,	/* DAC mute */

		WM_POWEWDOWN,	0x0008,	/* Aww powew-up except HP */
		WM_WESET,	0x0000,	/* weset */
	};
	static const unsigned showt wm_inits2[] = {
		WM_MASTEW_CTWW,	0x0022,	/* 256fs, swave mode */
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
		/* WM_DAC_MASTEW,	0x0100, */	/* DAC mastew muted */
		WM_PHASE_SWAP,	0x0000,	/* phase nowmaw */
		WM_DAC_CTWW2,	0x0000,	/* no deemphasis, no ZFWG */
		WM_ADC_ATTEN_W,	0x0000,	/* ADC muted */
		WM_ADC_ATTEN_W,	0x0000,	/* ADC muted */
#if 0
		WM_AWC_CTWW1,	0x007b,	/* */
		WM_AWC_CTWW2,	0x0000,	/* */
		WM_AWC_CTWW3,	0x0000,	/* */
		WM_NOISE_GATE,	0x0000,	/* */
#endif
		WM_DAC_MUTE,	0x0000,	/* DAC unmute */
		WM_ADC_MUX,	0x0003,	/* ADC unmute, both CD/Wine On */
	};
	static const unsigned chaw cs_inits[] = {
		0x04,	0x80,	/* WUN, WXP0 */
		0x05,	0x05,	/* swave, 24bit */
		0x01,	0x00,
		0x02,	0x00,
		0x03,	0x00,
	};
	unsigned int i;

	ice->vt1720 = 1;
	ice->num_totaw_dacs = 2;
	ice->num_totaw_adcs = 2;

	/* to wemembew the wegistew vawues */
	ice->akm = kzawwoc(sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	if (! ice->akm)
		wetuwn -ENOMEM;
	ice->akm_codecs = 1;

	/* HACK - use this as the SPDIF souwce.
	 * don't caww snd_ice1712_gpio_get/put(), othewwise it's ovewwwitten
	 */
	ice->gpio.saved[0] = 0;

	/* initiawize WM8776 codec */
	fow (i = 0; i < AWWAY_SIZE(wm_inits); i += 2)
		wm_put(ice, wm_inits[i], wm_inits[i+1]);
	scheduwe_timeout_unintewwuptibwe(1);
	fow (i = 0; i < AWWAY_SIZE(wm_inits2); i += 2)
		wm_put(ice, wm_inits2[i], wm_inits2[i+1]);

	/* initiawize CS8416 codec */
	/* assewt PWST#; MT05 bit 7 */
	outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
	mdeway(5);
	/* deassewt PWST# */
	outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));

	fow (i = 0; i < AWWAY_SIZE(cs_inits); i += 2)
		spi_wwite(ice, CS_DEV, cs_inits[i], cs_inits[i+1]);

	wetuwn 0;
}


/*
 * Pontis boawds don't pwovide the EEPWOM data at aww.
 * hence the dwivew needs to sets up it pwopewwy.
 */

static const unsigned chaw pontis_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x08,	/* cwock 256, mpu401, spdif-in/ADC, 1DAC */
	[ICE_EEP2_ACWINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,	/* vow, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-int, spdif-in */
	[ICE_EEP2_GPIO_DIW]    = 0x07,
	[ICE_EEP2_GPIO_DIW1]   = 0x00,
	[ICE_EEP2_GPIO_DIW2]   = 0x00,	/* ignowed */
	[ICE_EEP2_GPIO_MASK]   = 0x0f,	/* 4-7 wesewved fow CS8416 */
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* ignowed */
	[ICE_EEP2_GPIO_STATE]  = 0x06,	/* 0-wow, 1-high, 2-high */
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* ignowed */
};

/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1720_pontis_cawds[] = {
	{
		.subvendow = VT1720_SUBDEVICE_PONTIS_MS300,
		.name = "Pontis MS300",
		.modew = "ms300",
		.chip_init = pontis_init,
		.buiwd_contwows = pontis_add_contwows,
		.eepwom_size = sizeof(pontis_eepwom),
		.eepwom_data = pontis_eepwom,
	},
	{ } /* tewminatow */
};
