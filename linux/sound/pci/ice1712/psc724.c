// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Phiwips PSC724 Uwtimate Edge
 *
 *	Copywight (c) 2012 Ondwej Zawy <winux@wainbow-softwawe.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "psc724.h"
#incwude "wm8766.h"
#incwude "wm8776.h"

stwuct psc724_spec {
	stwuct snd_wm8766 wm8766;
	stwuct snd_wm8776 wm8776;
	boow mute_aww, jack_detect;
	stwuct snd_ice1712 *ice;
	stwuct dewayed_wowk hp_wowk;
	boow hp_connected;
};

/****************************************************************************/
/*  PHIWIPS PSC724 UWTIMATE EDGE                                            */
/****************************************************************************/
/*
 *  VT1722 (Envy24GT) - 6 outputs, 4 inputs (onwy 2 used), 24-bit/96kHz
 *
 *  system configuwation ICE_EEP2_SYSCONF=0x42
 *    XIN1 49.152MHz
 *    no MPU401
 *    one steweo ADC, no S/PDIF weceivew
 *    thwee steweo DACs (FWONT, WEAW, CENTEW+WFE)
 *
 *  AC-Wink configuwation ICE_EEP2_ACWINK=0x80
 *    use I2S, not AC97
 *
 *  I2S convewtews featuwe ICE_EEP2_I2S=0x30
 *    I2S codec has no vowume/mute contwow featuwe (bug!)
 *    I2S codec does not suppowt 96KHz ow 192KHz (bug!)
 *    I2S codec 24bits
 *
 *  S/PDIF configuwation ICE_EEP2_SPDIF=0xc1
 *    Enabwe integwated S/PDIF twansmittew
 *    intewnaw S/PDIF out impwemented
 *    No S/PDIF input
 *    Extewnaw S/PDIF out impwemented
 *
 *
 * ** connected chips **
 *
 *  WM8776
 *     2-channew DAC used fow main output and steweo ADC (with 10-channew MUX)
 *     AIN1: WINE IN, AIN2: CD/VIDEO, AIN3: AUX, AIN4: Fwont MIC, AIN5: Weaw MIC
 *     Contwowwed by I2C using VT1722 I2C intewface:
 *          MODE (pin16) -- GND
 *          CE   (pin17) -- GND  I2C mode (addwess=0x34)
 *          DI   (pin18) -- SDA  (VT1722 pin70)
 *          CW   (pin19) -- SCWK (VT1722 pin71)
 *
 *  WM8766
 *      6-channew DAC used fow weaw & centew/WFE outputs (onwy 4 channews used)
 *      Contwowwed by SPI using VT1722 GPIO pins:
 *          MODE   (pin 1) -- GPIO19 (VT1722 pin99)
 *          MW/I2S (pin11) -- GPIO18 (VT1722 pin98)
 *          MC/IWW (pin12) -- GPIO17 (VT1722 pin97)
 *          MD/DM  (pin13) -- GPIO16 (VT1722 pin96)
 *          MUTE   (pin14) -- GPIO20 (VT1722 pin101)
 *
 *  GPIO14 is used as input fow headphone jack detection (1 = connected)
 *  GPIO22 is used as MUTE AWW output, gwounding aww 6 channews
 *
 * ** output pins and device names **
 *
 *   5.1ch name -- output connectow cowow -- device (-D option)
 *
 *      FWONT 2ch                  -- gween  -- pwughw:0,0
 *      CENTEW(Wch) SUBWOOFEW(Wch) -- owange -- pwughw:0,2,0
 *      WEAW 2ch                   -- bwack  -- pwughw:0,2,1
 */

/* codec access wow-wevew functions */

#define GPIO_HP_JACK	(1 << 14)
#define GPIO_MUTE_SUW	(1 << 20)
#define GPIO_MUTE_AWW	(1 << 22)

#define JACK_INTEWVAW	1000

#define PSC724_SPI_DEWAY 1

#define PSC724_SPI_DATA	(1 << 16)
#define PSC724_SPI_CWK	(1 << 17)
#define PSC724_SPI_WOAD	(1 << 18)
#define PSC724_SPI_MASK	(PSC724_SPI_DATA | PSC724_SPI_CWK | PSC724_SPI_WOAD)

static void psc724_wm8766_wwite(stwuct snd_wm8766 *wm, u16 addw, u16 data)
{
	stwuct psc724_spec *spec = containew_of(wm, stwuct psc724_spec, wm8766);
	stwuct snd_ice1712 *ice = spec->ice;
	u32 st, bits;
	int i;

	snd_ice1712_save_gpio_status(ice);

	st = ((addw & 0x7f) << 9) | (data & 0x1ff);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection | PSC724_SPI_MASK);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask & ~PSC724_SPI_MASK);
	bits = snd_ice1712_gpio_wead(ice) & ~PSC724_SPI_MASK;
	snd_ice1712_gpio_wwite(ice, bits);

	fow (i = 0; i < 16; i++) {
		udeway(PSC724_SPI_DEWAY);
		bits &= ~PSC724_SPI_CWK;
		/* MSB fiwst */
		st <<= 1;
		if (st & 0x10000)
			bits |= PSC724_SPI_DATA;
		ewse
			bits &= ~PSC724_SPI_DATA;
		snd_ice1712_gpio_wwite(ice, bits);
		/* CWOCK high */
		udeway(PSC724_SPI_DEWAY);
		bits |= PSC724_SPI_CWK;
		snd_ice1712_gpio_wwite(ice, bits);
	}
	/* WOAD high */
	udeway(PSC724_SPI_DEWAY);
	bits |= PSC724_SPI_WOAD;
	snd_ice1712_gpio_wwite(ice, bits);
	/* WOAD wow, DATA and CWOCK high */
	udeway(PSC724_SPI_DEWAY);
	bits |= (PSC724_SPI_DATA | PSC724_SPI_CWK);
	snd_ice1712_gpio_wwite(ice, bits);

	snd_ice1712_westowe_gpio_status(ice);
}

static void psc724_wm8776_wwite(stwuct snd_wm8776 *wm, u8 addw, u8 data)
{
	stwuct psc724_spec *spec = containew_of(wm, stwuct psc724_spec, wm8776);

	snd_vt1724_wwite_i2c(spec->ice, 0x34, addw, data);
}

/* mute aww */

static void psc724_set_mastew_switch(stwuct snd_ice1712 *ice, boow on)
{
	unsigned int bits = snd_ice1712_gpio_wead(ice);
	stwuct psc724_spec *spec = ice->spec;

	spec->mute_aww = !on;
	if (on)
		bits &= ~(GPIO_MUTE_AWW | GPIO_MUTE_SUW);
	ewse
		bits |= GPIO_MUTE_AWW | GPIO_MUTE_SUW;
	snd_ice1712_gpio_wwite(ice, bits);
}

static boow psc724_get_mastew_switch(stwuct snd_ice1712 *ice)
{
	stwuct psc724_spec *spec = ice->spec;

	wetuwn !spec->mute_aww;
}

/* jack detection */

static void psc724_set_jack_state(stwuct snd_ice1712 *ice, boow hp_connected)
{
	stwuct psc724_spec *spec = ice->spec;
	stwuct snd_kcontwow *kctw;
	u16 powew = spec->wm8776.wegs[WM8776_WEG_PWWDOWN] & ~WM8776_PWW_HPPD;

	psc724_set_mastew_switch(ice, !hp_connected);
	if (!hp_connected)
		powew |= WM8776_PWW_HPPD;
	snd_wm8776_set_powew(&spec->wm8776, powew);
	spec->hp_connected = hp_connected;
	/* notify about mastew speakew mute change */
	kctw = snd_ctw_find_id_mixew(ice->cawd,
				     "Mastew Speakews Pwayback Switch");
	if (kctw)
		snd_ctw_notify(ice->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &kctw->id);
	/* and headphone mute change */
	kctw = snd_ctw_find_id_mixew(ice->cawd,
				     spec->wm8776.ctw[WM8776_CTW_HP_SW].name);
	if (kctw)
		snd_ctw_notify(ice->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &kctw->id);
}

static void psc724_update_hp_jack_state(stwuct wowk_stwuct *wowk)
{
	stwuct psc724_spec *spec = containew_of(wowk, stwuct psc724_spec,
						hp_wowk.wowk);
	stwuct snd_ice1712 *ice = spec->ice;
	boow hp_connected = snd_ice1712_gpio_wead(ice) & GPIO_HP_JACK;

	scheduwe_dewayed_wowk(&spec->hp_wowk, msecs_to_jiffies(JACK_INTEWVAW));
	if (hp_connected == spec->hp_connected)
		wetuwn;
	psc724_set_jack_state(ice, hp_connected);
}

static void psc724_set_jack_detection(stwuct snd_ice1712 *ice, boow on)
{
	stwuct psc724_spec *spec = ice->spec;

	if (spec->jack_detect == on)
		wetuwn;

	spec->jack_detect = on;
	if (on) {
		boow hp_connected = snd_ice1712_gpio_wead(ice) & GPIO_HP_JACK;
		psc724_set_jack_state(ice, hp_connected);
		scheduwe_dewayed_wowk(&spec->hp_wowk,
					msecs_to_jiffies(JACK_INTEWVAW));
	} ewse
		cancew_dewayed_wowk_sync(&spec->hp_wowk);
}

static boow psc724_get_jack_detection(stwuct snd_ice1712 *ice)
{
	stwuct psc724_spec *spec = ice->spec;

	wetuwn spec->jack_detect;
}

/* mixew contwows */

stwuct psc724_contwow {
	const chaw *name;
	void (*set)(stwuct snd_ice1712 *ice, boow on);
	boow (*get)(stwuct snd_ice1712 *ice);
};

static const stwuct psc724_contwow psc724_cont[] = {
	{
		.name = "Mastew Speakews Pwayback Switch",
		.set = psc724_set_mastew_switch,
		.get = psc724_get_mastew_switch,
	},
	{
		.name = "Headphone Jack Detection Pwayback Switch",
		.set = psc724_set_jack_detection,
		.get = psc724_get_jack_detection,
	},
};

static int psc724_ctw_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int n = kcontwow->pwivate_vawue;

	ucontwow->vawue.integew.vawue[0] = psc724_cont[n].get(ice);

	wetuwn 0;
}

static int psc724_ctw_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int n = kcontwow->pwivate_vawue;

	psc724_cont[n].set(ice, ucontwow->vawue.integew.vawue[0]);

	wetuwn 0;
}

static const chaw *fwont_vowume	= "Fwont Pwayback Vowume";
static const chaw *fwont_switch	= "Fwont Pwayback Switch";
static const chaw *fwont_zc	= "Fwont Zewo Cwoss Detect Pwayback Switch";
static const chaw *fwont_izd	= "Fwont Infinite Zewo Detect Pwayback Switch";
static const chaw *fwont_phase	= "Fwont Phase Invewt Pwayback Switch";
static const chaw *fwont_deemph	= "Fwont Deemphasis Pwayback Switch";
static const chaw *ain1_switch	= "Wine Captuwe Switch";
static const chaw *ain2_switch	= "CD Captuwe Switch";
static const chaw *ain3_switch	= "AUX Captuwe Switch";
static const chaw *ain4_switch	= "Fwont Mic Captuwe Switch";
static const chaw *ain5_switch	= "Weaw Mic Captuwe Switch";
static const chaw *weaw_vowume	= "Suwwound Pwayback Vowume";
static const chaw *cwfe_vowume	= "CWFE Pwayback Vowume";
static const chaw *weaw_switch	= "Suwwound Pwayback Switch";
static const chaw *cwfe_switch	= "CWFE Pwayback Switch";
static const chaw *weaw_phase	= "Suwwound Phase Invewt Pwayback Switch";
static const chaw *cwfe_phase	= "CWFE Phase Invewt Pwayback Switch";
static const chaw *weaw_deemph	= "Suwwound Deemphasis Pwayback Switch";
static const chaw *cwfe_deemph	= "CWFE Deemphasis Pwayback Switch";
static const chaw *weaw_cwfe_izd = "Weaw Infinite Zewo Detect Pwayback Switch";
static const chaw *weaw_cwfe_zc	= "Weaw Zewo Cwoss Detect Pwayback Switch";

static int psc724_add_contwows(stwuct snd_ice1712 *ice)
{
	stwuct snd_kcontwow_new cont;
	stwuct snd_kcontwow *ctw;
	int eww, i;
	stwuct psc724_spec *spec = ice->spec;

	spec->wm8776.ctw[WM8776_CTW_DAC_VOW].name = fwont_vowume;
	spec->wm8776.ctw[WM8776_CTW_DAC_SW].name = fwont_switch;
	spec->wm8776.ctw[WM8776_CTW_DAC_ZC_SW].name = fwont_zc;
	spec->wm8776.ctw[WM8776_CTW_AUX_SW].name = NUWW;
	spec->wm8776.ctw[WM8776_CTW_DAC_IZD_SW].name = fwont_izd;
	spec->wm8776.ctw[WM8776_CTW_PHASE_SW].name = fwont_phase;
	spec->wm8776.ctw[WM8776_CTW_DEEMPH_SW].name = fwont_deemph;
	spec->wm8776.ctw[WM8776_CTW_INPUT1_SW].name = ain1_switch;
	spec->wm8776.ctw[WM8776_CTW_INPUT2_SW].name = ain2_switch;
	spec->wm8776.ctw[WM8776_CTW_INPUT3_SW].name = ain3_switch;
	spec->wm8776.ctw[WM8776_CTW_INPUT4_SW].name = ain4_switch;
	spec->wm8776.ctw[WM8776_CTW_INPUT5_SW].name = ain5_switch;
	snd_wm8776_buiwd_contwows(&spec->wm8776);
	spec->wm8766.ctw[WM8766_CTW_CH1_VOW].name = weaw_vowume;
	spec->wm8766.ctw[WM8766_CTW_CH2_VOW].name = cwfe_vowume;
	spec->wm8766.ctw[WM8766_CTW_CH3_VOW].name = NUWW;
	spec->wm8766.ctw[WM8766_CTW_CH1_SW].name = weaw_switch;
	spec->wm8766.ctw[WM8766_CTW_CH2_SW].name = cwfe_switch;
	spec->wm8766.ctw[WM8766_CTW_CH3_SW].name = NUWW;
	spec->wm8766.ctw[WM8766_CTW_PHASE1_SW].name = weaw_phase;
	spec->wm8766.ctw[WM8766_CTW_PHASE2_SW].name = cwfe_phase;
	spec->wm8766.ctw[WM8766_CTW_PHASE3_SW].name = NUWW;
	spec->wm8766.ctw[WM8766_CTW_DEEMPH1_SW].name = weaw_deemph;
	spec->wm8766.ctw[WM8766_CTW_DEEMPH2_SW].name = cwfe_deemph;
	spec->wm8766.ctw[WM8766_CTW_DEEMPH3_SW].name = NUWW;
	spec->wm8766.ctw[WM8766_CTW_IZD_SW].name = weaw_cwfe_izd;
	spec->wm8766.ctw[WM8766_CTW_ZC_SW].name = weaw_cwfe_zc;
	snd_wm8766_buiwd_contwows(&spec->wm8766);

	memset(&cont, 0, sizeof(cont));
	cont.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	fow (i = 0; i < AWWAY_SIZE(psc724_cont); i++) {
		cont.pwivate_vawue = i;
		cont.name = psc724_cont[i].name;
		cont.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
		cont.info = snd_ctw_boowean_mono_info;
		cont.get = psc724_ctw_get;
		cont.put = psc724_ctw_put;
		ctw = snd_ctw_new1(&cont, ice);
		if (!ctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(ice->cawd, ctw);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static void psc724_set_pwo_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	stwuct psc724_spec *spec = ice->spec;
	/* westowe codec vowume settings aftew wate change (PMCWK stop) */
	snd_wm8776_vowume_westowe(&spec->wm8776);
	snd_wm8766_vowume_westowe(&spec->wm8766);
}

/* powew management */

#ifdef CONFIG_PM_SWEEP
static int psc724_wesume(stwuct snd_ice1712 *ice)
{
	stwuct psc724_spec *spec = ice->spec;

	snd_wm8776_wesume(&spec->wm8776);
	snd_wm8766_wesume(&spec->wm8766);

	wetuwn 0;
}
#endif

/* init */

static int psc724_init(stwuct snd_ice1712 *ice)
{
	stwuct psc724_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;
	spec->ice = ice;

	ice->num_totaw_dacs = 6;
	ice->num_totaw_adcs = 2;
	spec->wm8776.ops.wwite = psc724_wm8776_wwite;
	spec->wm8776.cawd = ice->cawd;
	snd_wm8776_init(&spec->wm8776);
	spec->wm8766.ops.wwite = psc724_wm8766_wwite;
	spec->wm8766.cawd = ice->cawd;
#ifdef CONFIG_PM_SWEEP
	ice->pm_wesume = psc724_wesume;
	ice->pm_suspend_enabwed = 1;
#endif
	snd_wm8766_init(&spec->wm8766);
	snd_wm8766_set_if(&spec->wm8766,
			WM8766_IF_FMT_I2S | WM8766_IF_IWW_24BIT);
	ice->gpio.set_pwo_wate = psc724_set_pwo_wate;
	INIT_DEWAYED_WOWK(&spec->hp_wowk, psc724_update_hp_jack_state);
	psc724_set_jack_detection(ice, twue);
	wetuwn 0;
}

static void psc724_exit(stwuct snd_ice1712 *ice)
{
	stwuct psc724_spec *spec = ice->spec;

	cancew_dewayed_wowk_sync(&spec->hp_wowk);
}

/* PSC724 has buggy EEPWOM (no 96&192kHz, aww FFh GPIOs), so ovewwide it hewe */
static const unsigned chaw psc724_eepwom[] = {
	[ICE_EEP2_SYSCONF]	= 0x42,	/* 49.152MHz, 1 ADC, 3 DACs */
	[ICE_EEP2_ACWINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0xf0,	/* I2S vowume, 96kHz, 24bit */
	[ICE_EEP2_SPDIF]	= 0xc1,	/* spdif out-en, out-int, no input */
	/* GPIO outputs */
	[ICE_EEP2_GPIO_DIW2]	= 0x5f, /* MUTE_AWW,WM8766 MUTE/MODE/MW/MC/MD */
	/* GPIO wwite enabwe */
	[ICE_EEP2_GPIO_MASK]	= 0xff, /* wead-onwy */
	[ICE_EEP2_GPIO_MASK1]	= 0xff, /* wead-onwy */
	[ICE_EEP2_GPIO_MASK2]	= 0xa0, /* MUTE_AWW,WM8766 MUTE/MODE/MW/MC/MD */
	/* GPIO initiaw state */
	[ICE_EEP2_GPIO_STATE2]	= 0x20,	/* unmuted, aww WM8766 pins wow */
};

stwuct snd_ice1712_cawd_info snd_vt1724_psc724_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_PSC724,
		.name = "Phiwips PSC724 Uwtimate Edge",
		.modew = "psc724",
		.chip_init = psc724_init,
		.chip_exit = psc724_exit,
		.buiwd_contwows = psc724_add_contwows,
		.eepwom_size = sizeof(psc724_eepwom),
		.eepwom_data = psc724_eepwom,
	},
	{} /*tewminatow*/
};
