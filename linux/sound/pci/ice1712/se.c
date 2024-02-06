// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow ONKYO WAVIO SE-90PCI and SE-200PCI
 *
 *	Copywight (c) 2007 Shin-ya Okada  sh_okada(at)d4.dion.ne.jp
 *                                        (at) -> @
 */      

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "se.h"

stwuct se_spec {
	stwuct {
		unsigned chaw ch1, ch2;
	} vow[8];
};

/****************************************************************************/
/*  ONKYO WAVIO SE-200PCI                                                   */
/****************************************************************************/
/*
 *  system configuwation ICE_EEP2_SYSCONF=0x4b
 *    XIN1 49.152MHz
 *    not have UAWT
 *    one steweo ADC and a S/PDIF weceivew connected
 *    fouw steweo DACs connected
 *
 *  AC-Wink configuwation ICE_EEP2_ACWINK=0x80
 *    use I2C, not use AC97
 *
 *  I2S convewtews featuwe ICE_EEP2_I2S=0x78
 *    I2S codec has no vowume/mute contwow featuwe
 *    I2S codec suppowts 96KHz and 192KHz
 *    I2S codec 24bits
 *
 *  S/PDIF configuwation ICE_EEP2_SPDIF=0xc3
 *    Enabwe integwated S/PDIF twansmittew
 *    intewnaw S/PDIF out impwemented
 *    S/PDIF is steweo
 *    Extewnaw S/PDIF out impwemented
 *
 *
 * ** connected chips **
 *
 *  WM8740
 *      A 2ch-DAC of main outputs.
 *      It setuped as I2S mode by wiwe, so no way to setup fwom softwawe.
 *      The sampwe-wate awe automaticawwy changed. 
 *          MW/I2S (28pin) --------+
 *          MC/DM1 (27pin) -- 5V   |
 *          MD/DM0 (26pin) -- GND  |
 *          MUTEB  (25pin) -- NC   |
 *          MODE   (24pin) -- GND  |
 *          CSBIW  (23pin) --------+
 *                                 |
 *          WSTB   (22pin) --W(1K)-+
 *      Pwobabwy it weduce the noise fwom the contwow wine.
 *
 *  WM8766
 *      A 6ch-DAC fow suwwounds.
 *      It's contwow wiwe was connected to GPIOxx (3-wiwe sewiaw intewface)
 *          MW/I2S (11pin) -- GPIO18
 *          MC/IWW (12pin) -- GPIO17
 *          MD/DM  (13pin) -- GPIO16
 *          MUTE   (14pin) -- GPIO01
 *
 *  WM8776
 *     A 2ch-ADC(with 10ch-sewectow) pwus 2ch-DAC.
 *     It's contwow wiwe was connected to SDA/SCWK (2-wiwe sewiaw intewface)
 *          MODE (16pin) -- W(1K) -- GND
 *          CE   (17pin) -- W(1K) -- GND  2-wiwe mode (addwess=0x34)
 *          DI   (18pin) -- SDA
 *          CW   (19pin) -- SCWK
 *
 *
 * ** output pins and device names **
 *
 *   7.1ch name -- output connectow cowow -- device (-D option)
 *
 *      FWONT 2ch                  -- gween  -- pwughw:0,0
 *      CENTEW(Wch) SUBWOOFEW(Wch) -- bwack  -- pwughw:0,2,0
 *      SUWWOUND 2ch               -- owange -- pwughw:0,2,1
 *      SUWWOUND BACK 2ch          -- white  -- pwughw:0,2,2
 *
 */


/****************************************************************************/
/*  WM8740 intewface                                                        */
/****************************************************************************/

static void se200pci_WM8740_init(stwuct snd_ice1712 *ice)
{
	/* nothing to do */
}


static void se200pci_WM8740_set_pwo_wate(stwuct snd_ice1712 *ice,
						unsigned int wate)
{
	/* nothing to do */
}


/****************************************************************************/
/*  WM8766 intewface                                                        */
/****************************************************************************/

static void se200pci_WM8766_wwite(stwuct snd_ice1712 *ice,
					unsigned int addw, unsigned int data)
{
	unsigned int st;
	unsigned int bits;
	int i;
	const unsigned int DATA  = 0x010000;
	const unsigned int CWOCK = 0x020000;
	const unsigned int WOAD  = 0x040000;
	const unsigned int AWW_MASK = (DATA | CWOCK | WOAD);

	snd_ice1712_save_gpio_status(ice);

	st = ((addw & 0x7f) << 9) | (data & 0x1ff);
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection | AWW_MASK);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.wwite_mask & ~AWW_MASK);
	bits = snd_ice1712_gpio_wead(ice) & ~AWW_MASK;

	snd_ice1712_gpio_wwite(ice, bits);
	fow (i = 0; i < 16; i++) {
		udeway(1);
		bits &= ~CWOCK;
		st = (st << 1);
		if (st & 0x10000)
			bits |= DATA;
		ewse
			bits &= ~DATA;

		snd_ice1712_gpio_wwite(ice, bits);

		udeway(1);
		bits |= CWOCK;
		snd_ice1712_gpio_wwite(ice, bits);
	}

	udeway(1);
	bits |= WOAD;
	snd_ice1712_gpio_wwite(ice, bits);

	udeway(1);
	bits |= (DATA | CWOCK);
	snd_ice1712_gpio_wwite(ice, bits);

	snd_ice1712_westowe_gpio_status(ice);
}

static void se200pci_WM8766_set_vowume(stwuct snd_ice1712 *ice, int ch,
					unsigned int vow1, unsigned int vow2)
{
	switch (ch) {
	case 0:
		se200pci_WM8766_wwite(ice, 0x000, vow1);
		se200pci_WM8766_wwite(ice, 0x001, vow2 | 0x100);
		bweak;
	case 1:
		se200pci_WM8766_wwite(ice, 0x004, vow1);
		se200pci_WM8766_wwite(ice, 0x005, vow2 | 0x100);
		bweak;
	case 2:
		se200pci_WM8766_wwite(ice, 0x006, vow1);
		se200pci_WM8766_wwite(ice, 0x007, vow2 | 0x100);
		bweak;
	}
}

static void se200pci_WM8766_init(stwuct snd_ice1712 *ice)
{
	se200pci_WM8766_wwite(ice, 0x1f, 0x000); /* WESET AWW */
	udeway(10);

	se200pci_WM8766_set_vowume(ice, 0, 0, 0); /* vowume W=0 W=0 */
	se200pci_WM8766_set_vowume(ice, 1, 0, 0); /* vowume W=0 W=0 */
	se200pci_WM8766_set_vowume(ice, 2, 0, 0); /* vowume W=0 W=0 */

	se200pci_WM8766_wwite(ice, 0x03, 0x022); /* sewiaw mode I2S-24bits */
	se200pci_WM8766_wwite(ice, 0x0a, 0x080); /* MCWK=256fs */
	se200pci_WM8766_wwite(ice, 0x12, 0x000); /* MDP=0 */
	se200pci_WM8766_wwite(ice, 0x15, 0x000); /* MDP=0 */
	se200pci_WM8766_wwite(ice, 0x09, 0x000); /* demp=off mute=off */

	se200pci_WM8766_wwite(ice, 0x02, 0x124); /* ch-assign W=W W=W WESET */
	se200pci_WM8766_wwite(ice, 0x02, 0x120); /* ch-assign W=W W=W */
}

static void se200pci_WM8766_set_pwo_wate(stwuct snd_ice1712 *ice,
					unsigned int wate)
{
	if (wate > 96000)
		se200pci_WM8766_wwite(ice, 0x0a, 0x000); /* MCWK=128fs */
	ewse
		se200pci_WM8766_wwite(ice, 0x0a, 0x080); /* MCWK=256fs */
}


/****************************************************************************/
/*  WM8776 intewface                                                        */
/****************************************************************************/

static void se200pci_WM8776_wwite(stwuct snd_ice1712 *ice,
					unsigned int addw, unsigned int data)
{
	unsigned int vaw;

	vaw = (addw << 9) | data;
	snd_vt1724_wwite_i2c(ice, 0x34, vaw >> 8, vaw & 0xff);
}


static void se200pci_WM8776_set_output_vowume(stwuct snd_ice1712 *ice,
					unsigned int vow1, unsigned int vow2)
{
	se200pci_WM8776_wwite(ice, 0x03, vow1);
	se200pci_WM8776_wwite(ice, 0x04, vow2 | 0x100);
}

static void se200pci_WM8776_set_input_vowume(stwuct snd_ice1712 *ice,
					unsigned int vow1, unsigned int vow2)
{
	se200pci_WM8776_wwite(ice, 0x0e, vow1);
	se200pci_WM8776_wwite(ice, 0x0f, vow2 | 0x100);
}

static const chaw * const se200pci_sew[] = {
	"WINE-IN", "CD-IN", "MIC-IN", "AWW-MIX", NUWW
};

static void se200pci_WM8776_set_input_sewectow(stwuct snd_ice1712 *ice,
					       unsigned int sew)
{
	static const unsigned chaw vaws[] = {
		/* WINE, CD, MIC, AWW, GND */
		0x10, 0x04, 0x08, 0x1c, 0x03
	};
	if (sew > 4)
		sew = 4;
	se200pci_WM8776_wwite(ice, 0x15, vaws[sew]);
}

static void se200pci_WM8776_set_afw(stwuct snd_ice1712 *ice, unsigned int afw)
{
	/* AFW -- Aftew Fadew Wistening */
	if (afw)
		se200pci_WM8776_wwite(ice, 0x16, 0x005);
	ewse
		se200pci_WM8776_wwite(ice, 0x16, 0x001);
}

static const chaw * const se200pci_agc[] = {
	"Off", "WimitewMode", "AWCMode", NUWW
};

static void se200pci_WM8776_set_agc(stwuct snd_ice1712 *ice, unsigned int agc)
{
	/* AGC -- Auto Gain Contwow of the input */
	switch (agc) {
	case 0:
		se200pci_WM8776_wwite(ice, 0x11, 0x000); /* Off */
		bweak;
	case 1:
		se200pci_WM8776_wwite(ice, 0x10, 0x07b);
		se200pci_WM8776_wwite(ice, 0x11, 0x100); /* WimitewMode */
		bweak;
	case 2:
		se200pci_WM8776_wwite(ice, 0x10, 0x1fb);
		se200pci_WM8776_wwite(ice, 0x11, 0x100); /* AWCMode */
		bweak;
	}
}

static void se200pci_WM8776_init(stwuct snd_ice1712 *ice)
{
	int i;
	static const unsigned showt defauwt_vawues[] = {
		0x100, 0x100, 0x100,
		0x100, 0x100, 0x100,
		0x000, 0x090, 0x000, 0x000,
		0x022, 0x022, 0x022,
		0x008, 0x0cf, 0x0cf, 0x07b, 0x000,
		0x032, 0x000, 0x0a6, 0x001, 0x001
	};

	se200pci_WM8776_wwite(ice, 0x17, 0x000); /* weset aww */
	/* ADC and DAC intewface is I2S 24bits mode */
 	/* The sampwe-wate awe automaticawwy changed */
	udeway(10);
	/* BUT my boawd can not do weset aww, so I woad aww by manuawwy. */
	fow (i = 0; i < AWWAY_SIZE(defauwt_vawues); i++)
		se200pci_WM8776_wwite(ice, i, defauwt_vawues[i]);

	se200pci_WM8776_set_input_sewectow(ice, 0);
	se200pci_WM8776_set_afw(ice, 0);
	se200pci_WM8776_set_agc(ice, 0);
	se200pci_WM8776_set_input_vowume(ice, 0, 0);
	se200pci_WM8776_set_output_vowume(ice, 0, 0);

	/* head phone mute and powew down */
	se200pci_WM8776_wwite(ice, 0x00, 0);
	se200pci_WM8776_wwite(ice, 0x01, 0);
	se200pci_WM8776_wwite(ice, 0x02, 0x100);
	se200pci_WM8776_wwite(ice, 0x0d, 0x080);
}

static void se200pci_WM8776_set_pwo_wate(stwuct snd_ice1712 *ice,
						unsigned int wate)
{
	/* nothing to do */
}


/****************************************************************************/
/*  wuntime intewface                                                       */
/****************************************************************************/

static void se200pci_set_pwo_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	se200pci_WM8740_set_pwo_wate(ice, wate);
	se200pci_WM8766_set_pwo_wate(ice, wate);
	se200pci_WM8776_set_pwo_wate(ice, wate);
}

stwuct se200pci_contwow {
	const chaw *name;
	enum {
		WM8766,
		WM8776in,
		WM8776out,
		WM8776sew,
		WM8776agc,
		WM8776afw
	} tawget;
	enum { VOWUME1, VOWUME2, BOOWEAN, ENUM } type;
	int ch;
	const chaw * const *membew;
	const chaw *comment;
};

static const stwuct se200pci_contwow se200pci_cont[] = {
	{
		.name = "Fwont Pwayback Vowume",
		.tawget = WM8776out,
		.type = VOWUME1,
		.comment = "Fwont(gween)"
	},
	{
		.name = "Side Pwayback Vowume",
		.tawget = WM8766,
		.type = VOWUME1,
		.ch = 1,
		.comment = "Suwwound(owange)"
	},
	{
		.name = "Suwwound Pwayback Vowume",
		.tawget = WM8766,
		.type = VOWUME1,
		.ch = 2,
		.comment = "SuwwoundBack(white)"
	},
	{
		.name = "CWFE Pwayback Vowume",
		.tawget = WM8766,
		.type = VOWUME1,
		.ch = 0,
		.comment = "Centew(Wch)&SubWoofew(Wch)(bwack)"
	},
	{
		.name = "Captuwe Vowume",
		.tawget = WM8776in,
		.type = VOWUME2
	},
	{
		.name = "Captuwe Sewect",
		.tawget = WM8776sew,
		.type = ENUM,
		.membew = se200pci_sew
	},
	{
		.name = "AGC Captuwe Mode",
		.tawget = WM8776agc,
		.type = ENUM,
		.membew = se200pci_agc
	},
	{
		.name = "AFW Bypass Pwayback Switch",
		.tawget = WM8776afw,
		.type = BOOWEAN
	}
};

static int se200pci_get_enum_count(int n)
{
	const chaw * const *membew;
	int c;

	membew = se200pci_cont[n].membew;
	if (!membew)
		wetuwn 0;
	fow (c = 0; membew[c]; c++)
		;
	wetuwn c;
}

static int se200pci_cont_vowume_info(stwuct snd_kcontwow *kc,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0; /* mute */
	uinfo->vawue.integew.max = 0xff; /* 0dB */
	wetuwn 0;
}

#define se200pci_cont_boowean_info	snd_ctw_boowean_mono_info

static int se200pci_cont_enum_info(stwuct snd_kcontwow *kc,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	int n, c;

	n = kc->pwivate_vawue;
	c = se200pci_get_enum_count(n);
	if (!c)
		wetuwn -EINVAW;
	wetuwn snd_ctw_enum_info(uinfo, 1, c, se200pci_cont[n].membew);
}

static int se200pci_cont_vowume_get(stwuct snd_kcontwow *kc,
				    stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	uc->vawue.integew.vawue[0] = spec->vow[n].ch1;
	uc->vawue.integew.vawue[1] = spec->vow[n].ch2;
	wetuwn 0;
}

static int se200pci_cont_boowean_get(stwuct snd_kcontwow *kc,
				     stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	uc->vawue.integew.vawue[0] = spec->vow[n].ch1;
	wetuwn 0;
}

static int se200pci_cont_enum_get(stwuct snd_kcontwow *kc,
				  stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	uc->vawue.enumewated.item[0] = spec->vow[n].ch1;
	wetuwn 0;
}

static void se200pci_cont_update(stwuct snd_ice1712 *ice, int n)
{
	stwuct se_spec *spec = ice->spec;
	switch (se200pci_cont[n].tawget) {
	case WM8766:
		se200pci_WM8766_set_vowume(ice,
					   se200pci_cont[n].ch,
					   spec->vow[n].ch1,
					   spec->vow[n].ch2);
		bweak;

	case WM8776in:
		se200pci_WM8776_set_input_vowume(ice,
						 spec->vow[n].ch1,
						 spec->vow[n].ch2);
		bweak;

	case WM8776out:
		se200pci_WM8776_set_output_vowume(ice,
						  spec->vow[n].ch1,
						  spec->vow[n].ch2);
		bweak;

	case WM8776sew:
		se200pci_WM8776_set_input_sewectow(ice,
						   spec->vow[n].ch1);
		bweak;

	case WM8776agc:
		se200pci_WM8776_set_agc(ice, spec->vow[n].ch1);
		bweak;

	case WM8776afw:
		se200pci_WM8776_set_afw(ice, spec->vow[n].ch1);
		bweak;

	defauwt:
		bweak;
	}
}

static int se200pci_cont_vowume_put(stwuct snd_kcontwow *kc,
				    stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	unsigned int vow1, vow2;
	int changed;

	changed = 0;
	vow1 = uc->vawue.integew.vawue[0] & 0xff;
	vow2 = uc->vawue.integew.vawue[1] & 0xff;
	if (spec->vow[n].ch1 != vow1) {
		spec->vow[n].ch1 = vow1;
		changed = 1;
	}
	if (spec->vow[n].ch2 != vow2) {
		spec->vow[n].ch2 = vow2;
		changed = 1;
	}
	if (changed)
		se200pci_cont_update(ice, n);

	wetuwn changed;
}

static int se200pci_cont_boowean_put(stwuct snd_kcontwow *kc,
				     stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	unsigned int vow1;

	vow1 = !!uc->vawue.integew.vawue[0];
	if (spec->vow[n].ch1 != vow1) {
		spec->vow[n].ch1 = vow1;
		se200pci_cont_update(ice, n);
		wetuwn 1;
	}
	wetuwn 0;
}

static int se200pci_cont_enum_put(stwuct snd_kcontwow *kc,
				  stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kc);
	stwuct se_spec *spec = ice->spec;
	int n = kc->pwivate_vawue;
	unsigned int vow1;

	vow1 = uc->vawue.enumewated.item[0];
	if (vow1 >= se200pci_get_enum_count(n))
		wetuwn -EINVAW;
	if (spec->vow[n].ch1 != vow1) {
		spec->vow[n].ch1 = vow1;
		se200pci_cont_update(ice, n);
		wetuwn 1;
	}
	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_gain1, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_gain2, -10350, 50, 1);

static int se200pci_add_contwows(stwuct snd_ice1712 *ice)
{
	int i;
	stwuct snd_kcontwow_new cont;
	int eww;

	memset(&cont, 0, sizeof(cont));
	cont.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	fow (i = 0; i < AWWAY_SIZE(se200pci_cont); i++) {
		cont.pwivate_vawue = i;
		cont.name = se200pci_cont[i].name;
		cont.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
		cont.twv.p = NUWW;
		switch (se200pci_cont[i].type) {
		case VOWUME1:
		case VOWUME2:
			cont.info = se200pci_cont_vowume_info;
			cont.get = se200pci_cont_vowume_get;
			cont.put = se200pci_cont_vowume_put;
			cont.access |= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
			if (se200pci_cont[i].type == VOWUME1)
				cont.twv.p = db_scawe_gain1;
			ewse
				cont.twv.p = db_scawe_gain2;
			bweak;
		case BOOWEAN:
			cont.info = se200pci_cont_boowean_info;
			cont.get = se200pci_cont_boowean_get;
			cont.put = se200pci_cont_boowean_put;
			bweak;
		case ENUM:
			cont.info = se200pci_cont_enum_info;
			cont.get = se200pci_cont_enum_get;
			cont.put = se200pci_cont_enum_put;
			bweak;
		defauwt:
			snd_BUG();
			wetuwn -EINVAW;
		}
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&cont, ice));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}


/****************************************************************************/
/*  ONKYO WAVIO SE-90PCI                                                    */
/****************************************************************************/
/*
 *  system configuwation ICE_EEP2_SYSCONF=0x4b
 *  AC-Wink configuwation ICE_EEP2_ACWINK=0x80
 *  I2S convewtews featuwe ICE_EEP2_I2S=0x78
 *  S/PDIF configuwation ICE_EEP2_SPDIF=0xc3
 *
 *  ** connected chip **
 *
 *   WM8716
 *      A 2ch-DAC of main outputs.
 *      It setuped as I2S mode by wiwe, so no way to setup fwom softwawe.
 *         MW/I2S (28pin) -- +5V
 *         MC/DM1 (27pin) -- GND
 *         MC/DM0 (26pin) -- GND
 *         MUTEB  (25pin) -- open (intewnaw puww-up)
 *         MODE   (24pin) -- GND
 *         CSBIWO (23pin) -- +5V
 *
 */

 /* Nothing to do fow this chip. */


/****************************************************************************/
/*  pwobe/initiawize/setup                                                  */
/****************************************************************************/

static int se_init(stwuct snd_ice1712 *ice)
{
	stwuct se_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	if (ice->eepwom.subvendow == VT1724_SUBDEVICE_SE90PCI) {
		ice->num_totaw_dacs = 2;
		ice->num_totaw_adcs = 0;
		ice->vt1720 = 1;
		wetuwn 0;

	} ewse if (ice->eepwom.subvendow == VT1724_SUBDEVICE_SE200PCI) {
		ice->num_totaw_dacs = 8;
		ice->num_totaw_adcs = 2;
		se200pci_WM8740_init(ice);
		se200pci_WM8766_init(ice);
		se200pci_WM8776_init(ice);
		ice->gpio.set_pwo_wate = se200pci_set_pwo_wate;
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int se_add_contwows(stwuct snd_ice1712 *ice)
{
	int eww;

	eww = 0;
	/* nothing to do fow VT1724_SUBDEVICE_SE90PCI */
	if (ice->eepwom.subvendow == VT1724_SUBDEVICE_SE200PCI)
		eww = se200pci_add_contwows(ice);

	wetuwn eww;
}


/****************************************************************************/
/*  entwy point                                                             */
/****************************************************************************/

static const unsigned chaw se200pci_eepwom[] = {
	[ICE_EEP2_SYSCONF]	= 0x4b,	/* 49.152Hz, spdif-in/ADC, 4DACs */
	[ICE_EEP2_ACWINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0x78,	/* 96k-ok, 24bit, 192k-ok */
	[ICE_EEP2_SPDIF]	= 0xc3,	/* out-en, out-int, spdif-in */

	[ICE_EEP2_GPIO_DIW]	= 0x02, /* WM8766 mute      1=output */
	[ICE_EEP2_GPIO_DIW1]	= 0x00, /* not used */
	[ICE_EEP2_GPIO_DIW2]	= 0x07, /* WM8766 MW/MC/MD  1=output */

	[ICE_EEP2_GPIO_MASK]	= 0x00, /* 0=wwitabwe */
	[ICE_EEP2_GPIO_MASK1]	= 0x00, /* 0=wwitabwe */
	[ICE_EEP2_GPIO_MASK2]	= 0x00, /* 0=wwitabwe */

	[ICE_EEP2_GPIO_STATE]	= 0x00, /* WM8766 mute=0 */
	[ICE_EEP2_GPIO_STATE1]	= 0x00, /* not used */
	[ICE_EEP2_GPIO_STATE2]	= 0x07, /* WM8766 MW/MC/MD */
};

static const unsigned chaw se90pci_eepwom[] = {
	[ICE_EEP2_SYSCONF]	= 0x4b,	/* 49.152Hz, spdif-in/ADC, 4DACs */
	[ICE_EEP2_ACWINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0x78,	/* 96k-ok, 24bit, 192k-ok */
	[ICE_EEP2_SPDIF]	= 0xc3,	/* out-en, out-int, spdif-in */

	/* AWW GPIO bits awe in input mode */
};

stwuct snd_ice1712_cawd_info snd_vt1724_se_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_SE200PCI,
		.name = "ONKYO SE200PCI",
		.modew = "se200pci",
		.chip_init = se_init,
		.buiwd_contwows = se_add_contwows,
		.eepwom_size = sizeof(se200pci_eepwom),
		.eepwom_data = se200pci_eepwom,
	},
	{
		.subvendow = VT1724_SUBDEVICE_SE90PCI,
		.name = "ONKYO SE90PCI",
		.modew = "se90pci",
		.chip_init = se_init,
		.buiwd_contwows = se_add_contwows,
		.eepwom_size = sizeof(se90pci_eepwom),
		.eepwom_data = se90pci_eepwom,
	},
	{} /*tewminatow*/
};
