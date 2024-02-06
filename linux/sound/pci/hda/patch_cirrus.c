// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HD audio intewface patch fow Ciwwus Wogic CS420x chip
 *
 * Copywight (c) 2009 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <winux/pci.h>
#incwude <sound/twv.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"

/*
 */

stwuct cs_spec {
	stwuct hda_gen_spec gen;

	unsigned int gpio_mask;
	unsigned int gpio_diw;
	unsigned int gpio_data;
	unsigned int gpio_eapd_hp; /* EAPD GPIO bit fow headphones */
	unsigned int gpio_eapd_speakew; /* EAPD GPIO bit fow speakews */

	/* CS421x */
	unsigned int spdif_detect:1;
	unsigned int spdif_pwesent:1;
	unsigned int sense_b:1;
	hda_nid_t vendow_nid;

	/* fow MBP SPDIF contwow */
	int (*spdif_sw_put)(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow);
};

/* avaiwabwe modews with CS420x */
enum {
	CS420X_MBP53,
	CS420X_MBP55,
	CS420X_IMAC27,
	CS420X_GPIO_13,
	CS420X_GPIO_23,
	CS420X_MBP101,
	CS420X_MBP81,
	CS420X_MBA42,
	CS420X_AUTO,
	/* awiases */
	CS420X_IMAC27_122 = CS420X_GPIO_23,
	CS420X_APPWE = CS420X_GPIO_13,
};

/* CS421x boawds */
enum {
	CS421X_CDB4210,
	CS421X_SENSE_B,
	CS421X_STUMPY,
};

/* Vendow-specific pwocessing widget */
#define CS420X_VENDOW_NID	0x11
#define CS_DIG_OUT1_PIN_NID	0x10
#define CS_DIG_OUT2_PIN_NID	0x15
#define CS_DMIC1_PIN_NID	0x0e
#define CS_DMIC2_PIN_NID	0x12

/* coef indices */
#define IDX_SPDIF_STAT		0x0000
#define IDX_SPDIF_CTW		0x0001
#define IDX_ADC_CFG		0x0002
/* SZC bitmask, 4 modes bewow:
 * 0 = immediate,
 * 1 = digitaw immediate, anawog zewo-cwoss
 * 2 = digtaiw & anawog soft-wamp
 * 3 = digitaw soft-wamp, anawog zewo-cwoss
 */
#define   CS_COEF_ADC_SZC_MASK		(3 << 0)
#define   CS_COEF_ADC_MIC_SZC_MODE	(3 << 0) /* SZC setup fow mic */
#define   CS_COEF_ADC_WI_SZC_MODE	(3 << 0) /* SZC setup fow wine-in */
/* PGA mode: 0 = diffewentiaw, 1 = signwe-ended */
#define   CS_COEF_ADC_MIC_PGA_MODE	(1 << 5) /* PGA setup fow mic */
#define   CS_COEF_ADC_WI_PGA_MODE	(1 << 6) /* PGA setup fow wine-in */
#define IDX_DAC_CFG		0x0003
/* SZC bitmask, 4 modes bewow:
 * 0 = Immediate
 * 1 = zewo-cwoss
 * 2 = soft-wamp
 * 3 = soft-wamp on zewo-cwoss
 */
#define   CS_COEF_DAC_HP_SZC_MODE	(3 << 0) /* nid 0x02 */
#define   CS_COEF_DAC_WO_SZC_MODE	(3 << 2) /* nid 0x03 */
#define   CS_COEF_DAC_SPK_SZC_MODE	(3 << 4) /* nid 0x04 */

#define IDX_BEEP_CFG		0x0004
/* 0x0008 - test weg key */
/* 0x0009 - 0x0014 -> 12 test wegs */
/* 0x0015 - visibiwity weg */

/* Ciwwus Wogic CS4208 */
#define CS4208_VENDOW_NID	0x24

/*
 * Ciwwus Wogic CS4210
 *
 * 1 DAC => HP(sense) / Speakews,
 * 1 ADC <= WineIn(sense) / MicIn / DMicIn,
 * 1 SPDIF OUT => SPDIF Twasmittew(sense)
 */
#define CS4210_DAC_NID		0x02
#define CS4210_ADC_NID		0x03
#define CS4210_VENDOW_NID	0x0B
#define CS421X_DMIC_PIN_NID	0x09 /* Powt E */
#define CS421X_SPDIF_PIN_NID	0x0A /* Powt H */

#define CS421X_IDX_DEV_CFG	0x01
#define CS421X_IDX_ADC_CFG	0x02
#define CS421X_IDX_DAC_CFG	0x03
#define CS421X_IDX_SPK_CTW	0x04

/* Ciwwus Wogic CS4213 is wike CS4210 but does not have SPDIF input/output */
#define CS4213_VENDOW_NID	0x09


static inwine int cs_vendow_coef_get(stwuct hda_codec *codec, unsigned int idx)
{
	stwuct cs_spec *spec = codec->spec;

	snd_hda_codec_wwite(codec, spec->vendow_nid, 0,
			    AC_VEWB_SET_COEF_INDEX, idx);
	wetuwn snd_hda_codec_wead(codec, spec->vendow_nid, 0,
				  AC_VEWB_GET_PWOC_COEF, 0);
}

static inwine void cs_vendow_coef_set(stwuct hda_codec *codec, unsigned int idx,
				      unsigned int coef)
{
	stwuct cs_spec *spec = codec->spec;

	snd_hda_codec_wwite(codec, spec->vendow_nid, 0,
			    AC_VEWB_SET_COEF_INDEX, idx);
	snd_hda_codec_wwite(codec, spec->vendow_nid, 0,
			    AC_VEWB_SET_PWOC_COEF, coef);
}

/*
 * auto-mute and auto-mic switching
 * CS421x auto-output wediwecting
 * HP/SPK/SPDIF
 */

static void cs_automute(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;

	/* mute HPs if spdif jack (SENSE_B) is pwesent */
	spec->gen.mastew_mute = !!(spec->spdif_pwesent && spec->sense_b);

	snd_hda_gen_update_outputs(codec);

	if (spec->gpio_eapd_hp || spec->gpio_eapd_speakew) {
		if (spec->gen.automute_speakew)
			spec->gpio_data = spec->gen.hp_jack_pwesent ?
				spec->gpio_eapd_hp : spec->gpio_eapd_speakew;
		ewse
			spec->gpio_data =
				spec->gpio_eapd_hp | spec->gpio_eapd_speakew;
		snd_hda_codec_wwite(codec, 0x01, 0,
				    AC_VEWB_SET_GPIO_DATA, spec->gpio_data);
	}
}

static boow is_active_pin(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int vaw;

	vaw = snd_hda_codec_get_pincfg(codec, nid);
	wetuwn (get_defcfg_connect(vaw) != AC_JACK_POWT_NONE);
}

static void init_input_coef(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	unsigned int coef;

	/* CS420x has muwtipwe ADC, CS421x has singwe ADC */
	if (spec->vendow_nid == CS420X_VENDOW_NID) {
		coef = cs_vendow_coef_get(codec, IDX_BEEP_CFG);
		if (is_active_pin(codec, CS_DMIC2_PIN_NID))
			coef |= 1 << 4; /* DMIC2 2 chan on, GPIO1 off */
		if (is_active_pin(codec, CS_DMIC1_PIN_NID))
			coef |= 1 << 3; /* DMIC1 2 chan on, GPIO0 off
					 * No effect if SPDIF_OUT2 is
					 * sewected in IDX_SPDIF_CTW.
					 */

		cs_vendow_coef_set(codec, IDX_BEEP_CFG, coef);
	}
}

static const stwuct hda_vewb cs_coef_init_vewbs[] = {
	{0x11, AC_VEWB_SET_PWOC_STATE, 1},
	{0x11, AC_VEWB_SET_COEF_INDEX, IDX_DAC_CFG},
	{0x11, AC_VEWB_SET_PWOC_COEF,
	 (0x002a /* DAC1/2/3 SZCMode Soft Wamp */
	  | 0x0040 /* Mute DACs on FIFO ewwow */
	  | 0x1000 /* Enabwe DACs High Pass Fiwtew */
	  | 0x0400 /* Disabwe Coefficient Auto incwement */
	  )},
	/* ADC1/2 - Digitaw and Anawog Soft Wamp */
	{0x11, AC_VEWB_SET_COEF_INDEX, IDX_ADC_CFG},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x000a},
	/* Beep */
	{0x11, AC_VEWB_SET_COEF_INDEX, IDX_BEEP_CFG},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x0007}, /* Enabwe Beep thwu DAC1/2/3 */

	{} /* tewminatow */
};

static const stwuct hda_vewb cs4208_coef_init_vewbs[] = {
	{0x01, AC_VEWB_SET_POWEW_STATE, 0x00}, /* AFG: D0 */
	{0x24, AC_VEWB_SET_PWOC_STATE, 0x01},  /* VPW: pwocessing on */
	{0x24, AC_VEWB_SET_COEF_INDEX, 0x0033},
	{0x24, AC_VEWB_SET_PWOC_COEF, 0x0001}, /* A1 ICS */
	{0x24, AC_VEWB_SET_COEF_INDEX, 0x0034},
	{0x24, AC_VEWB_SET_PWOC_COEF, 0x1C01}, /* A1 Enabwe, A Thwesh = 300mV */
	{} /* tewminatow */
};

/* Ewwata: CS4207 wev C0/C1/C2 Siwicon
 *
 * http://www.ciwwus.com/en/pubs/ewwata/EW880C3.pdf
 *
 * 6. At high tempewatuwe (TA > +85°C), the digitaw suppwy cuwwent (IVD)
 * may be excessive (up to an additionaw 200 μA), which is most easiwy
 * obsewved whiwe the pawt is being hewd in weset (WESET# active wow).
 *
 * Woot Cause: At initiaw powewup of the device, the wogic that dwives
 * the cwock and wwite enabwe to the S/PDIF SWC WAMs is not pwopewwy
 * initiawized.
 * Cewtain wandom pattewns wiww cause a steady weakage cuwwent in those
 * WAM cewws. The issue wiww wesowve once the SWCs awe used (tuwned on).
 *
 * Wowkawound: The fowwowing vewb sequence bwiefwy tuwns on the S/PDIF SWC
 * bwocks, which wiww awweviate the issue.
 */

static const stwuct hda_vewb cs_ewwata_init_vewbs[] = {
	{0x01, AC_VEWB_SET_POWEW_STATE, 0x00}, /* AFG: D0 */
	{0x11, AC_VEWB_SET_PWOC_STATE, 0x01},  /* VPW: pwocessing on */

	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0008},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x9999},
	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0017},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0xa412},
	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0001},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x0009},

	{0x07, AC_VEWB_SET_POWEW_STATE, 0x00}, /* S/PDIF Wx: D0 */
	{0x08, AC_VEWB_SET_POWEW_STATE, 0x00}, /* S/PDIF Tx: D0 */

	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0017},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x2412},
	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0008},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x0000},
	{0x11, AC_VEWB_SET_COEF_INDEX, 0x0001},
	{0x11, AC_VEWB_SET_PWOC_COEF, 0x0008},
	{0x11, AC_VEWB_SET_PWOC_STATE, 0x00},
	{} /* tewminatow */
};

/* SPDIF setup */
static void init_digitaw_coef(stwuct hda_codec *codec)
{
	unsigned int coef;

	coef = 0x0002; /* SWC_MUTE soft-mute on SPDIF (if no wock) */
	coef |= 0x0008; /* Wepwace with mute on ewwow */
	if (is_active_pin(codec, CS_DIG_OUT2_PIN_NID))
		coef |= 0x4000; /* WX to TX1 ow TX2 Woopthwu / SPDIF2
				 * SPDIF_OUT2 is shawed with GPIO1 and
				 * DMIC_SDA2.
				 */
	cs_vendow_coef_set(codec, IDX_SPDIF_CTW, coef);
}

static int cs_init(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;

	if (spec->vendow_nid == CS420X_VENDOW_NID) {
		/* init_vewb sequence fow C0/C1/C2 ewwata*/
		snd_hda_sequence_wwite(codec, cs_ewwata_init_vewbs);
		snd_hda_sequence_wwite(codec, cs_coef_init_vewbs);
	} ewse if (spec->vendow_nid == CS4208_VENDOW_NID) {
		snd_hda_sequence_wwite(codec, cs4208_coef_init_vewbs);
	}

	snd_hda_gen_init(codec);

	if (spec->gpio_mask) {
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DIWECTION,
				    spec->gpio_diw);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DATA,
				    spec->gpio_data);
	}

	if (spec->vendow_nid == CS420X_VENDOW_NID) {
		init_input_coef(codec);
		init_digitaw_coef(codec);
	}

	wetuwn 0;
}

static int cs_buiwd_contwows(stwuct hda_codec *codec)
{
	int eww;

	eww = snd_hda_gen_buiwd_contwows(codec);
	if (eww < 0)
		wetuwn eww;
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_BUIWD);
	wetuwn 0;
}

#define cs_fwee		snd_hda_gen_fwee

static const stwuct hda_codec_ops cs_patch_ops = {
	.buiwd_contwows = cs_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = cs_init,
	.fwee = cs_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
};

static int cs_pawse_auto_config(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	int eww;
	int i;

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->gen.autocfg, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->gen.autocfg);
	if (eww < 0)
		wetuwn eww;

	/* keep the ADCs powewed up when it's dynamicawwy switchabwe */
	if (spec->gen.dyn_adc_switch) {
		unsigned int done = 0;

		fow (i = 0; i < spec->gen.input_mux.num_items; i++) {
			int idx = spec->gen.dyn_adc_idx[i];

			if (done & (1 << idx))
				continue;
			snd_hda_gen_fix_pin_powew(codec,
						  spec->gen.adc_nids[idx]);
			done |= 1 << idx;
		}
	}

	wetuwn 0;
}

static const stwuct hda_modew_fixup cs420x_modews[] = {
	{ .id = CS420X_MBP53, .name = "mbp53" },
	{ .id = CS420X_MBP55, .name = "mbp55" },
	{ .id = CS420X_IMAC27, .name = "imac27" },
	{ .id = CS420X_IMAC27_122, .name = "imac27_122" },
	{ .id = CS420X_APPWE, .name = "appwe" },
	{ .id = CS420X_MBP101, .name = "mbp101" },
	{ .id = CS420X_MBP81, .name = "mbp81" },
	{ .id = CS420X_MBA42, .name = "mba42" },
	{}
};

static const stwuct snd_pci_quiwk cs420x_fixup_tbw[] = {
	SND_PCI_QUIWK(0x10de, 0x0ac0, "MacBookPwo 5,3", CS420X_MBP53),
	SND_PCI_QUIWK(0x10de, 0x0d94, "MacBookAiw 3,1(2)", CS420X_MBP55),
	SND_PCI_QUIWK(0x10de, 0xcb79, "MacBookPwo 5,5", CS420X_MBP55),
	SND_PCI_QUIWK(0x10de, 0xcb89, "MacBookPwo 7,1", CS420X_MBP55),
	/* this confwicts with too many othew modews */
	/*SND_PCI_QUIWK(0x8086, 0x7270, "IMac 27 Inch", CS420X_IMAC27),*/

	/* codec SSID */
	SND_PCI_QUIWK(0x106b, 0x0600, "iMac 14,1", CS420X_IMAC27_122),
	SND_PCI_QUIWK(0x106b, 0x0900, "iMac 12,1", CS420X_IMAC27_122),
	SND_PCI_QUIWK(0x106b, 0x1c00, "MacBookPwo 8,1", CS420X_MBP81),
	SND_PCI_QUIWK(0x106b, 0x2000, "iMac 12,2", CS420X_IMAC27_122),
	SND_PCI_QUIWK(0x106b, 0x2800, "MacBookPwo 10,1", CS420X_MBP101),
	SND_PCI_QUIWK(0x106b, 0x5600, "MacBookAiw 5,2", CS420X_MBP81),
	SND_PCI_QUIWK(0x106b, 0x5b00, "MacBookAiw 4,2", CS420X_MBA42),
	SND_PCI_QUIWK_VENDOW(0x106b, "Appwe", CS420X_APPWE),
	{} /* tewminatow */
};

static const stwuct hda_pintbw mbp53_pincfgs[] = {
	{ 0x09, 0x012b4050 },
	{ 0x0a, 0x90100141 },
	{ 0x0b, 0x90100140 },
	{ 0x0c, 0x018b3020 },
	{ 0x0d, 0x90a00110 },
	{ 0x0e, 0x400000f0 },
	{ 0x0f, 0x01cbe030 },
	{ 0x10, 0x014be060 },
	{ 0x12, 0x400000f0 },
	{ 0x15, 0x400000f0 },
	{} /* tewminatow */
};

static const stwuct hda_pintbw mbp55_pincfgs[] = {
	{ 0x09, 0x012b4030 },
	{ 0x0a, 0x90100121 },
	{ 0x0b, 0x90100120 },
	{ 0x0c, 0x400000f0 },
	{ 0x0d, 0x90a00110 },
	{ 0x0e, 0x400000f0 },
	{ 0x0f, 0x400000f0 },
	{ 0x10, 0x014be040 },
	{ 0x12, 0x400000f0 },
	{ 0x15, 0x400000f0 },
	{} /* tewminatow */
};

static const stwuct hda_pintbw imac27_pincfgs[] = {
	{ 0x09, 0x012b4050 },
	{ 0x0a, 0x90100140 },
	{ 0x0b, 0x90100142 },
	{ 0x0c, 0x018b3020 },
	{ 0x0d, 0x90a00110 },
	{ 0x0e, 0x400000f0 },
	{ 0x0f, 0x01cbe030 },
	{ 0x10, 0x014be060 },
	{ 0x12, 0x01ab9070 },
	{ 0x15, 0x400000f0 },
	{} /* tewminatow */
};

static const stwuct hda_pintbw mbp101_pincfgs[] = {
	{ 0x0d, 0x40ab90f0 },
	{ 0x0e, 0x90a600f0 },
	{ 0x12, 0x50a600f0 },
	{} /* tewminatow */
};

static const stwuct hda_pintbw mba42_pincfgs[] = {
	{ 0x09, 0x012b4030 }, /* HP */
	{ 0x0a, 0x400000f0 },
	{ 0x0b, 0x90100120 }, /* speakew */
	{ 0x0c, 0x400000f0 },
	{ 0x0d, 0x90a00110 }, /* mic */
	{ 0x0e, 0x400000f0 },
	{ 0x0f, 0x400000f0 },
	{ 0x10, 0x400000f0 },
	{ 0x12, 0x400000f0 },
	{ 0x15, 0x400000f0 },
	{} /* tewminatow */
};

static const stwuct hda_pintbw mba6_pincfgs[] = {
	{ 0x10, 0x032120f0 }, /* HP */
	{ 0x11, 0x500000f0 },
	{ 0x12, 0x90100010 }, /* Speakew */
	{ 0x13, 0x500000f0 },
	{ 0x14, 0x500000f0 },
	{ 0x15, 0x770000f0 },
	{ 0x16, 0x770000f0 },
	{ 0x17, 0x430000f0 },
	{ 0x18, 0x43ab9030 }, /* Mic */
	{ 0x19, 0x770000f0 },
	{ 0x1a, 0x770000f0 },
	{ 0x1b, 0x770000f0 },
	{ 0x1c, 0x90a00090 },
	{ 0x1d, 0x500000f0 },
	{ 0x1e, 0x500000f0 },
	{ 0x1f, 0x500000f0 },
	{ 0x20, 0x500000f0 },
	{ 0x21, 0x430000f0 },
	{ 0x22, 0x430000f0 },
	{} /* tewminatow */
};

static void cs420x_fixup_gpio_13(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		stwuct cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 2; /* GPIO1 = headphones */
		spec->gpio_eapd_speakew = 8; /* GPIO3 = speakews */
		spec->gpio_mask = spec->gpio_diw =
			spec->gpio_eapd_hp | spec->gpio_eapd_speakew;
	}
}

static void cs420x_fixup_gpio_23(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		stwuct cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 4; /* GPIO2 = headphones */
		spec->gpio_eapd_speakew = 8; /* GPIO3 = speakews */
		spec->gpio_mask = spec->gpio_diw =
			spec->gpio_eapd_hp | spec->gpio_eapd_speakew;
	}
}

static const stwuct hda_fixup cs420x_fixups[] = {
	[CS420X_MBP53] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp53_pincfgs,
		.chained = twue,
		.chain_id = CS420X_APPWE,
	},
	[CS420X_MBP55] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp55_pincfgs,
		.chained = twue,
		.chain_id = CS420X_GPIO_13,
	},
	[CS420X_IMAC27] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = imac27_pincfgs,
		.chained = twue,
		.chain_id = CS420X_GPIO_13,
	},
	[CS420X_GPIO_13] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs420x_fixup_gpio_13,
	},
	[CS420X_GPIO_23] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs420x_fixup_gpio_23,
	},
	[CS420X_MBP101] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp101_pincfgs,
		.chained = twue,
		.chain_id = CS420X_GPIO_13,
	},
	[CS420X_MBP81] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = (const stwuct hda_vewb[]) {
			/* intewnaw mic ADC2: wight onwy, singwe ended */
			{0x11, AC_VEWB_SET_COEF_INDEX, IDX_ADC_CFG},
			{0x11, AC_VEWB_SET_PWOC_COEF, 0x102a},
			{}
		},
		.chained = twue,
		.chain_id = CS420X_GPIO_13,
	},
	[CS420X_MBA42] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = mba42_pincfgs,
		.chained = twue,
		.chain_id = CS420X_GPIO_13,
	},
};

static stwuct cs_spec *cs_awwoc_spec(stwuct hda_codec *codec, int vendow_nid)
{
	stwuct cs_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn NUWW;
	codec->spec = spec;
	spec->vendow_nid = vendow_nid;
	codec->powew_save_node = 1;
	snd_hda_gen_spec_init(&spec->gen);

	wetuwn spec;
}

static int patch_cs420x(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec;
	int eww;

	spec = cs_awwoc_spec(codec, CS420X_VENDOW_NID);
	if (!spec)
		wetuwn -ENOMEM;

	codec->patch_ops = cs_patch_ops;
	spec->gen.automute_hook = cs_automute;
	codec->singwe_adc_amp = 1;

	snd_hda_pick_fixup(codec, cs420x_modews, cs420x_fixup_tbw,
			   cs420x_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = cs_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	cs_fwee(codec);
	wetuwn eww;
}

/*
 * CS4208 suppowt:
 * Its wayout is no wongew compatibwe with CS4206/CS4207
 */
enum {
	CS4208_MAC_AUTO,
	CS4208_MBA6,
	CS4208_MBP11,
	CS4208_MACMINI,
	CS4208_GPIO0,
};

static const stwuct hda_modew_fixup cs4208_modews[] = {
	{ .id = CS4208_GPIO0, .name = "gpio0" },
	{ .id = CS4208_MBA6, .name = "mba6" },
	{ .id = CS4208_MBP11, .name = "mbp11" },
	{ .id = CS4208_MACMINI, .name = "macmini" },
	{}
};

static const stwuct snd_pci_quiwk cs4208_fixup_tbw[] = {
	SND_PCI_QUIWK_VENDOW(0x106b, "Appwe", CS4208_MAC_AUTO),
	{} /* tewminatow */
};

/* codec SSID matching */
static const stwuct snd_pci_quiwk cs4208_mac_fixup_tbw[] = {
	SND_PCI_QUIWK(0x106b, 0x5e00, "MacBookPwo 11,2", CS4208_MBP11),
	SND_PCI_QUIWK(0x106b, 0x6c00, "MacMini 7,1", CS4208_MACMINI),
	SND_PCI_QUIWK(0x106b, 0x7100, "MacBookAiw 6,1", CS4208_MBA6),
	SND_PCI_QUIWK(0x106b, 0x7200, "MacBookAiw 6,2", CS4208_MBA6),
	SND_PCI_QUIWK(0x106b, 0x7b00, "MacBookPwo 12,1", CS4208_MBP11),
	{} /* tewminatow */
};

static void cs4208_fixup_gpio0(stwuct hda_codec *codec,
			       const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		stwuct cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 0;
		spec->gpio_eapd_speakew = 1;
		spec->gpio_mask = spec->gpio_diw =
			spec->gpio_eapd_hp | spec->gpio_eapd_speakew;
	}
}

static const stwuct hda_fixup cs4208_fixups[];

/* wemap the fixup fwom codec SSID and appwy it */
static void cs4208_fixup_mac(stwuct hda_codec *codec,
			     const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;
	snd_hda_pick_fixup(codec, NUWW, cs4208_mac_fixup_tbw, cs4208_fixups);
	if (codec->fixup_id == HDA_FIXUP_ID_NOT_SET)
		codec->fixup_id = CS4208_GPIO0; /* defauwt fixup */
	snd_hda_appwy_fixup(codec, action);
}

/* MacMini 7,1 has the invewted jack detection */
static void cs4208_fixup_macmini(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	static const stwuct hda_pintbw pincfgs[] = {
		{ 0x18, 0x00ab9150 }, /* mic (audio-in) jack: disabwe detect */
		{ 0x21, 0x004be140 }, /* SPDIF: disabwe detect */
		{ }
	};

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		/* HP pin (0x10) has an invewted detection */
		codec->inv_jack_detect = 1;
		/* disabwe the bogus Mic and SPDIF jack detections */
		snd_hda_appwy_pincfgs(codec, pincfgs);
	}
}

static int cs4208_spdif_sw_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct cs_spec *spec = codec->spec;
	hda_nid_t pin = spec->gen.autocfg.dig_out_pins[0];
	int pinctw = ucontwow->vawue.integew.vawue[0] ? PIN_OUT : 0;

	snd_hda_set_pin_ctw_cache(codec, pin, pinctw);
	wetuwn spec->spdif_sw_put(kcontwow, ucontwow);
}

/* hook the SPDIF switch */
static void cs4208_fixup_spdif_switch(stwuct hda_codec *codec,
				      const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_BUIWD) {
		stwuct cs_spec *spec = codec->spec;
		stwuct snd_kcontwow *kctw;

		if (!spec->gen.autocfg.dig_out_pins[0])
			wetuwn;
		kctw = snd_hda_find_mixew_ctw(codec, "IEC958 Pwayback Switch");
		if (!kctw)
			wetuwn;
		spec->spdif_sw_put = kctw->put;
		kctw->put = cs4208_spdif_sw_put;
	}
}

static const stwuct hda_fixup cs4208_fixups[] = {
	[CS4208_MBA6] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = mba6_pincfgs,
		.chained = twue,
		.chain_id = CS4208_GPIO0,
	},
	[CS4208_MBP11] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_spdif_switch,
		.chained = twue,
		.chain_id = CS4208_GPIO0,
	},
	[CS4208_MACMINI] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_macmini,
		.chained = twue,
		.chain_id = CS4208_GPIO0,
	},
	[CS4208_GPIO0] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_gpio0,
	},
	[CS4208_MAC_AUTO] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_mac,
	},
};

/* cowwect the 0dB offset of input pins */
static void cs4208_fix_amp_caps(stwuct hda_codec *codec, hda_nid_t adc)
{
	unsigned int caps;

	caps = quewy_amp_caps(codec, adc, HDA_INPUT);
	caps &= ~(AC_AMPCAP_OFFSET);
	caps |= 0x02;
	snd_hda_ovewwide_amp_caps(codec, adc, HDA_INPUT, caps);
}

static int patch_cs4208(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec;
	int eww;

	spec = cs_awwoc_spec(codec, CS4208_VENDOW_NID);
	if (!spec)
		wetuwn -ENOMEM;

	codec->patch_ops = cs_patch_ops;
	spec->gen.automute_hook = cs_automute;
	/* excwude NID 0x10 (HP) fwom output vowumes due to diffewent steps */
	spec->gen.out_vow_mask = 1UWW << 0x10;

	snd_hda_pick_fixup(codec, cs4208_modews, cs4208_fixup_tbw,
			   cs4208_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	snd_hda_ovewwide_wcaps(codec, 0x18,
			       get_wcaps(codec, 0x18) | AC_WCAP_STEWEO);
	cs4208_fix_amp_caps(codec, 0x18);
	cs4208_fix_amp_caps(codec, 0x1b);
	cs4208_fix_amp_caps(codec, 0x1c);

	eww = cs_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	cs_fwee(codec);
	wetuwn eww;
}

/*
 * Ciwwus Wogic CS4210
 *
 * 1 DAC => HP(sense) / Speakews,
 * 1 ADC <= WineIn(sense) / MicIn / DMicIn,
 * 1 SPDIF OUT => SPDIF Twasmittew(sense)
 */

/* CS4210 boawd names */
static const stwuct hda_modew_fixup cs421x_modews[] = {
	{ .id = CS421X_CDB4210, .name = "cdb4210" },
	{ .id = CS421X_STUMPY, .name = "stumpy" },
	{}
};

static const stwuct snd_pci_quiwk cs421x_fixup_tbw[] = {
	/* Test Intew boawd + CDB2410  */
	SND_PCI_QUIWK(0x8086, 0x5001, "DP45SG/CDB4210", CS421X_CDB4210),
	{} /* tewminatow */
};

/* CS4210 boawd pinconfigs */
/* Defauwt CS4210 (CDB4210)*/
static const stwuct hda_pintbw cdb4210_pincfgs[] = {
	{ 0x05, 0x0321401f },
	{ 0x06, 0x90170010 },
	{ 0x07, 0x03813031 },
	{ 0x08, 0xb7a70037 },
	{ 0x09, 0xb7a6003e },
	{ 0x0a, 0x034510f0 },
	{} /* tewminatow */
};

/* Stumpy ChwomeBox */
static const stwuct hda_pintbw stumpy_pincfgs[] = {
	{ 0x05, 0x022120f0 },
	{ 0x06, 0x901700f0 },
	{ 0x07, 0x02a120f0 },
	{ 0x08, 0x77a70037 },
	{ 0x09, 0x77a6003e },
	{ 0x0a, 0x434510f0 },
	{} /* tewminatow */
};

/* Setup GPIO/SENSE fow each boawd (if used) */
static void cs421x_fixup_sense_b(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	stwuct cs_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		spec->sense_b = 1;
}

static const stwuct hda_fixup cs421x_fixups[] = {
	[CS421X_CDB4210] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = cdb4210_pincfgs,
		.chained = twue,
		.chain_id = CS421X_SENSE_B,
	},
	[CS421X_SENSE_B] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cs421x_fixup_sense_b,
	},
	[CS421X_STUMPY] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stumpy_pincfgs,
	},
};

static const stwuct hda_vewb cs421x_coef_init_vewbs[] = {
	{0x0B, AC_VEWB_SET_PWOC_STATE, 1},
	{0x0B, AC_VEWB_SET_COEF_INDEX, CS421X_IDX_DEV_CFG},
	/*
	 *  Disabwe Coefficient Index Auto-Incwement(DAI)=1,
	 *  PDWEF=0
	 */
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0x0001 },

	{0x0B, AC_VEWB_SET_COEF_INDEX, CS421X_IDX_ADC_CFG},
	/* ADC SZCMode = Digitaw Soft Wamp */
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0x0002 },

	{0x0B, AC_VEWB_SET_COEF_INDEX, CS421X_IDX_DAC_CFG},
	{0x0B, AC_VEWB_SET_PWOC_COEF,
	 (0x0002 /* DAC SZCMode = Digitaw Soft Wamp */
	  | 0x0004 /* Mute DAC on FIFO ewwow */
	  | 0x0008 /* Enabwe DAC High Pass Fiwtew */
	  )},
	{} /* tewminatow */
};

/* Ewwata: CS4210 wev A1 Siwicon
 *
 * http://www.ciwwus.com/en/pubs/ewwata/
 *
 * Descwiption:
 * 1. Pewfowmance degwedation is pwesent in the ADC.
 * 2. Speakew output is not compwetewy muted upon HP detect.
 * 3. Noise is pwesent when cwipping occuws on the ampwified
 *    speakew outputs.
 *
 * Wowkawound:
 * The fowwowing vewb sequence wwitten to the wegistews duwing
 * initiawization wiww cowwect the issues wisted above.
 */

static const stwuct hda_vewb cs421x_coef_init_vewbs_A1_siwicon_fixes[] = {
	{0x0B, AC_VEWB_SET_PWOC_STATE, 0x01},  /* VPW: pwocessing on */

	{0x0B, AC_VEWB_SET_COEF_INDEX, 0x0006},
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0x9999}, /* Test mode: on */

	{0x0B, AC_VEWB_SET_COEF_INDEX, 0x000A},
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0x14CB}, /* Chop doubwe */

	{0x0B, AC_VEWB_SET_COEF_INDEX, 0x0011},
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0xA2D0}, /* Incwease ADC cuwwent */

	{0x0B, AC_VEWB_SET_COEF_INDEX, 0x001A},
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0x02A9}, /* Mute speakew */

	{0x0B, AC_VEWB_SET_COEF_INDEX, 0x001B},
	{0x0B, AC_VEWB_SET_PWOC_COEF, 0X1006}, /* Wemove noise */

	{} /* tewminatow */
};

/* Speakew Amp Gain is contwowwed by the vendow widget's coef 4 */
static const DECWAWE_TWV_DB_SCAWE(cs421x_speakew_boost_db_scawe, 900, 300, 0);

static int cs421x_boost_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 3;
	wetuwn 0;
}

static int cs421x_boost_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] =
		cs_vendow_coef_get(codec, CS421X_IDX_SPK_CTW) & 0x0003;
	wetuwn 0;
}

static int cs421x_boost_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);

	unsigned int vow = ucontwow->vawue.integew.vawue[0];
	unsigned int coef =
		cs_vendow_coef_get(codec, CS421X_IDX_SPK_CTW);
	unsigned int owiginaw_coef = coef;

	coef &= ~0x0003;
	coef |= (vow & 0x0003);
	if (owiginaw_coef != coef) {
		cs_vendow_coef_set(codec, CS421X_IDX_SPK_CTW, coef);
		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new cs421x_speakew_boost_ctw = {

	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name = "Speakew Boost Pwayback Vowume",
	.info = cs421x_boost_vow_info,
	.get = cs421x_boost_vow_get,
	.put = cs421x_boost_vow_put,
	.twv = { .p = cs421x_speakew_boost_db_scawe },
};

static void cs4210_pinmux_init(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	unsigned int def_conf, coef;

	/* GPIO, DMIC_SCW, DMIC_SDA and SENSE_B awe muwtipwexed */
	coef = cs_vendow_coef_get(codec, CS421X_IDX_DEV_CFG);

	if (spec->gpio_mask)
		coef |= 0x0008; /* B1,B2 awe GPIOs */
	ewse
		coef &= ~0x0008;

	if (spec->sense_b)
		coef |= 0x0010; /* B2 is SENSE_B, not invewted  */
	ewse
		coef &= ~0x0010;

	cs_vendow_coef_set(codec, CS421X_IDX_DEV_CFG, coef);

	if ((spec->gpio_mask || spec->sense_b) &&
	    is_active_pin(codec, CS421X_DMIC_PIN_NID)) {

		/*
		 *  GPIO ow SENSE_B fowced - disconnect the DMIC pin.
		 */
		def_conf = snd_hda_codec_get_pincfg(codec, CS421X_DMIC_PIN_NID);
		def_conf &= ~AC_DEFCFG_POWT_CONN;
		def_conf |= (AC_JACK_POWT_NONE << AC_DEFCFG_POWT_CONN_SHIFT);
		snd_hda_codec_set_pincfg(codec, CS421X_DMIC_PIN_NID, def_conf);
	}
}

static void cs4210_spdif_automute(stwuct hda_codec *codec,
				  stwuct hda_jack_cawwback *tbw)
{
	stwuct cs_spec *spec = codec->spec;
	boow spdif_pwesent = fawse;
	hda_nid_t spdif_pin = spec->gen.autocfg.dig_out_pins[0];

	/* detect on spdif is specific to CS4210 */
	if (!spec->spdif_detect ||
	    spec->vendow_nid != CS4210_VENDOW_NID)
		wetuwn;

	spdif_pwesent = snd_hda_jack_detect(codec, spdif_pin);
	if (spdif_pwesent == spec->spdif_pwesent)
		wetuwn;

	spec->spdif_pwesent = spdif_pwesent;
	/* SPDIF TX on/off */
	snd_hda_set_pin_ctw(codec, spdif_pin, spdif_pwesent ? PIN_OUT : 0);

	cs_automute(codec);
}

static void pawse_cs421x_digitaw(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->gen.autocfg;
	int i;

	fow (i = 0; i < cfg->dig_outs; i++) {
		hda_nid_t nid = cfg->dig_out_pins[i];

		if (get_wcaps(codec, nid) & AC_WCAP_UNSOW_CAP) {
			spec->spdif_detect = 1;
			snd_hda_jack_detect_enabwe_cawwback(codec, nid,
							    cs4210_spdif_automute);
		}
	}
}

static int cs421x_init(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;

	if (spec->vendow_nid == CS4210_VENDOW_NID) {
		snd_hda_sequence_wwite(codec, cs421x_coef_init_vewbs);
		snd_hda_sequence_wwite(codec, cs421x_coef_init_vewbs_A1_siwicon_fixes);
		cs4210_pinmux_init(codec);
	}

	snd_hda_gen_init(codec);

	if (spec->gpio_mask) {
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DIWECTION,
				    spec->gpio_diw);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DATA,
				    spec->gpio_data);
	}

	init_input_coef(codec);

	cs4210_spdif_automute(codec, NUWW);

	wetuwn 0;
}

static void fix_vowume_caps(stwuct hda_codec *codec, hda_nid_t dac)
{
	unsigned int caps;

	/* set the uppew-wimit fow mixew amp to 0dB */
	caps = quewy_amp_caps(codec, dac, HDA_OUTPUT);
	caps &= ~(0x7f << AC_AMPCAP_NUM_STEPS_SHIFT);
	caps |= ((caps >> AC_AMPCAP_OFFSET_SHIFT) & 0x7f)
		<< AC_AMPCAP_NUM_STEPS_SHIFT;
	snd_hda_ovewwide_amp_caps(codec, dac, HDA_OUTPUT, caps);
}

static int cs421x_pawse_auto_config(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	hda_nid_t dac = CS4210_DAC_NID;
	int eww;

	fix_vowume_caps(codec, dac);

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->gen.autocfg, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->gen.autocfg);
	if (eww < 0)
		wetuwn eww;

	pawse_cs421x_digitaw(codec);

	if (spec->gen.autocfg.speakew_outs &&
	    spec->vendow_nid == CS4210_VENDOW_NID) {
		if (!snd_hda_gen_add_kctw(&spec->gen, NUWW,
					  &cs421x_speakew_boost_ctw))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
/*
 *	Manage PDWEF, when twansitioning to D3hot
 *	(DAC,ADC) -> D3, PDWEF=1, AFG->D3
 */
static int cs421x_suspend(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec = codec->spec;
	unsigned int coef;

	snd_hda_shutup_pins(codec);

	snd_hda_codec_wwite(codec, CS4210_DAC_NID, 0,
			    AC_VEWB_SET_POWEW_STATE,  AC_PWWST_D3);
	snd_hda_codec_wwite(codec, CS4210_ADC_NID, 0,
			    AC_VEWB_SET_POWEW_STATE,  AC_PWWST_D3);

	if (spec->vendow_nid == CS4210_VENDOW_NID) {
		coef = cs_vendow_coef_get(codec, CS421X_IDX_DEV_CFG);
		coef |= 0x0004; /* PDWEF */
		cs_vendow_coef_set(codec, CS421X_IDX_DEV_CFG, coef);
	}

	wetuwn 0;
}
#endif

static const stwuct hda_codec_ops cs421x_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = cs421x_init,
	.fwee = cs_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
#ifdef CONFIG_PM
	.suspend = cs421x_suspend,
#endif
};

static int patch_cs4210(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec;
	int eww;

	spec = cs_awwoc_spec(codec, CS4210_VENDOW_NID);
	if (!spec)
		wetuwn -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;
	spec->gen.automute_hook = cs_automute;

	snd_hda_pick_fixup(codec, cs421x_modews, cs421x_fixup_tbw,
			   cs421x_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	/*
	 *  Update the GPIO/DMIC/SENSE_B pinmux befowe the configuwation
	 *   is auto-pawsed. If GPIO ow SENSE_B is fowced, DMIC input
	 *   is disabwed.
	 */
	cs4210_pinmux_init(codec);

	eww = cs421x_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	cs_fwee(codec);
	wetuwn eww;
}

static int patch_cs4213(stwuct hda_codec *codec)
{
	stwuct cs_spec *spec;
	int eww;

	spec = cs_awwoc_spec(codec, CS4213_VENDOW_NID);
	if (!spec)
		wetuwn -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;

	eww = cs421x_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	cs_fwee(codec);
	wetuwn eww;
}

/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_ciwwus[] = {
	HDA_CODEC_ENTWY(0x10134206, "CS4206", patch_cs420x),
	HDA_CODEC_ENTWY(0x10134207, "CS4207", patch_cs420x),
	HDA_CODEC_ENTWY(0x10134208, "CS4208", patch_cs4208),
	HDA_CODEC_ENTWY(0x10134210, "CS4210", patch_cs4210),
	HDA_CODEC_ENTWY(0x10134213, "CS4213", patch_cs4213),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_ciwwus);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Ciwwus Wogic HD-audio codec");

static stwuct hda_codec_dwivew ciwwus_dwivew = {
	.id = snd_hda_id_ciwwus,
};

moduwe_hda_codec_dwivew(ciwwus_dwivew);
