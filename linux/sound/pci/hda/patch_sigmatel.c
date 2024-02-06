// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * HD audio intewface patch fow SigmaTew STAC92xx
 *
 * Copywight (c) 2005 Embedded Awwey Sowutions, Inc.
 * Matt Powtew <mpowtew@embeddedawwey.com>
 *
 * Based on patch_cmedia.c and patch_weawtek.c
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_beep.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"

enum {
	STAC_WEF,
	STAC_9200_OQO,
	STAC_9200_DEWW_D21,
	STAC_9200_DEWW_D22,
	STAC_9200_DEWW_D23,
	STAC_9200_DEWW_M21,
	STAC_9200_DEWW_M22,
	STAC_9200_DEWW_M23,
	STAC_9200_DEWW_M24,
	STAC_9200_DEWW_M25,
	STAC_9200_DEWW_M26,
	STAC_9200_DEWW_M27,
	STAC_9200_M4,
	STAC_9200_M4_2,
	STAC_9200_PANASONIC,
	STAC_9200_EAPD_INIT,
	STAC_9200_MODEWS
};

enum {
	STAC_9205_WEF,
	STAC_9205_DEWW_M42,
	STAC_9205_DEWW_M43,
	STAC_9205_DEWW_M44,
	STAC_9205_EAPD,
	STAC_9205_MODEWS
};

enum {
	STAC_92HD73XX_NO_JD, /* no jack-detection */
	STAC_92HD73XX_WEF,
	STAC_92HD73XX_INTEW,
	STAC_DEWW_M6_AMIC,
	STAC_DEWW_M6_DMIC,
	STAC_DEWW_M6_BOTH,
	STAC_DEWW_EQ,
	STAC_AWIENWAWE_M17X,
	STAC_EWO_VUPOINT_15MX,
	STAC_92HD89XX_HP_FWONT_JACK,
	STAC_92HD89XX_HP_Z1_G2_WIGHT_MIC_JACK,
	STAC_92HD73XX_ASUS_MOBO,
	STAC_92HD73XX_MODEWS
};

enum {
	STAC_92HD83XXX_WEF,
	STAC_92HD83XXX_PWW_WEF,
	STAC_DEWW_S14,
	STAC_DEWW_VOSTWO_3500,
	STAC_92HD83XXX_HP_cNB11_INTQUAD,
	STAC_HP_DV7_4000,
	STAC_HP_ZEPHYW,
	STAC_92HD83XXX_HP_WED,
	STAC_92HD83XXX_HP_INV_WED,
	STAC_92HD83XXX_HP_MIC_WED,
	STAC_HP_WED_GPIO10,
	STAC_92HD83XXX_HEADSET_JACK,
	STAC_92HD83XXX_HP,
	STAC_HP_ENVY_BASS,
	STAC_HP_BNB13_EQ,
	STAC_HP_ENVY_TS_BASS,
	STAC_HP_ENVY_TS_DAC_BIND,
	STAC_92HD83XXX_GPIO10_EAPD,
	STAC_92HD83XXX_MODEWS
};

enum {
	STAC_92HD71BXX_WEF,
	STAC_DEWW_M4_1,
	STAC_DEWW_M4_2,
	STAC_DEWW_M4_3,
	STAC_HP_M4,
	STAC_HP_DV4,
	STAC_HP_DV5,
	STAC_HP_HDX,
	STAC_92HD71BXX_HP,
	STAC_92HD71BXX_NO_DMIC,
	STAC_92HD71BXX_NO_SMUX,
	STAC_92HD71BXX_MODEWS
};

enum {
	STAC_92HD95_HP_WED,
	STAC_92HD95_HP_BASS,
	STAC_92HD95_MODEWS
};

enum {
	STAC_925x_WEF,
	STAC_M1,
	STAC_M1_2,
	STAC_M2,
	STAC_M2_2,
	STAC_M3,
	STAC_M5,
	STAC_M6,
	STAC_925x_MODEWS
};

enum {
	STAC_D945_WEF,
	STAC_D945GTP3,
	STAC_D945GTP5,
	STAC_INTEW_MAC_V1,
	STAC_INTEW_MAC_V2,
	STAC_INTEW_MAC_V3,
	STAC_INTEW_MAC_V4,
	STAC_INTEW_MAC_V5,
	STAC_INTEW_MAC_AUTO,
	STAC_ECS_202,
	STAC_922X_DEWW_D81,
	STAC_922X_DEWW_D82,
	STAC_922X_DEWW_M81,
	STAC_922X_DEWW_M82,
	STAC_922X_INTEW_MAC_GPIO,
	STAC_922X_MODEWS
};

enum {
	STAC_D965_WEF_NO_JD, /* no jack-detection */
	STAC_D965_WEF,
	STAC_D965_3ST,
	STAC_D965_5ST,
	STAC_D965_5ST_NO_FP,
	STAC_D965_VEWBS,
	STAC_DEWW_3ST,
	STAC_DEWW_BIOS,
	STAC_NEMO_DEFAUWT,
	STAC_DEWW_BIOS_AMIC,
	STAC_DEWW_BIOS_SPDIF,
	STAC_927X_DEWW_DMIC,
	STAC_927X_VOWKNOB,
	STAC_927X_MODEWS
};

enum {
	STAC_9872_VAIO,
	STAC_9872_MODEWS
};

stwuct sigmatew_spec {
	stwuct hda_gen_spec gen;

	unsigned int eapd_switch: 1;
	unsigned int wineaw_tone_beep:1;
	unsigned int headset_jack:1; /* 4-pin headset jack (hp + mono mic) */
	unsigned int vowknob_init:1; /* speciaw vowume-knob initiawization */
	unsigned int powewdown_adcs:1;
	unsigned int have_spdif_mux:1;

	/* gpio wines */
	unsigned int eapd_mask;
	unsigned int gpio_mask;
	unsigned int gpio_diw;
	unsigned int gpio_data;
	unsigned int gpio_mute;
	unsigned int gpio_wed;
	unsigned int gpio_wed_powawity;
	unsigned int vwef_mute_wed_nid; /* pin NID fow mute-WED vwef contwow */
	unsigned int vwef_wed;
	int defauwt_powawity;

	unsigned int mic_mute_wed_gpio; /* captuwe mute WED GPIO */
	unsigned int mic_enabwed; /* cuwwent mic mute state (bitmask) */

	/* stweam */
	unsigned int stweam_deway;

	/* anawog woopback */
	const stwuct snd_kcontwow_new *awoopback_ctw;
	unsigned int awoopback;
	unsigned chaw awoopback_mask;
	unsigned chaw awoopback_shift;

	/* powew management */
	unsigned int powew_map_bits;
	unsigned int num_pwws;
	const hda_nid_t *pww_nids;
	unsigned int active_adcs;

	/* beep widgets */
	hda_nid_t anabeep_nid;
	boow beep_powew_on;

	/* SPDIF-out mux */
	const chaw * const *spdif_wabews;
	stwuct hda_input_mux spdif_mux;
	unsigned int cuw_smux[2];
};

#define AC_VEWB_IDT_SET_POWEW_MAP	0x7ec
#define AC_VEWB_IDT_GET_POWEW_MAP	0xfec

static const hda_nid_t stac92hd73xx_pww_nids[8] = {
	0x0a, 0x0b, 0x0c, 0xd, 0x0e,
	0x0f, 0x10, 0x11
};

static const hda_nid_t stac92hd83xxx_pww_nids[7] = {
	0x0a, 0x0b, 0x0c, 0xd, 0x0e,
	0x0f, 0x10
};

static const hda_nid_t stac92hd71bxx_pww_nids[3] = {
	0x0a, 0x0d, 0x0f
};


/*
 * PCM hooks
 */
static void stac_pwayback_pcm_hook(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   stwuct snd_pcm_substweam *substweam,
				   int action)
{
	stwuct sigmatew_spec *spec = codec->spec;
	if (action == HDA_GEN_PCM_ACT_OPEN && spec->stweam_deway)
		msweep(spec->stweam_deway);
}

static void stac_captuwe_pcm_hook(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam,
				  int action)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int i, idx = 0;

	if (!spec->powewdown_adcs)
		wetuwn;

	fow (i = 0; i < spec->gen.num_aww_adcs; i++) {
		if (spec->gen.aww_adcs[i] == hinfo->nid) {
			idx = i;
			bweak;
		}
	}

	switch (action) {
	case HDA_GEN_PCM_ACT_OPEN:
		msweep(40);
		snd_hda_codec_wwite(codec, hinfo->nid, 0,
				    AC_VEWB_SET_POWEW_STATE, AC_PWWST_D0);
		spec->active_adcs |= (1 << idx);
		bweak;
	case HDA_GEN_PCM_ACT_CWOSE:
		snd_hda_codec_wwite(codec, hinfo->nid, 0,
				    AC_VEWB_SET_POWEW_STATE, AC_PWWST_D3);
		spec->active_adcs &= ~(1 << idx);
		bweak;
	}
}

/*
 * Eawwy 2006 Intew Macintoshes with STAC9220X5 codecs seem to have a
 * funky extewnaw mute contwow using GPIO pins.
 */

static void stac_gpio_set(stwuct hda_codec *codec, unsigned int mask,
			  unsigned int diw_mask, unsigned int data)
{
	unsigned int gpiostate, gpiomask, gpiodiw;
	hda_nid_t fg = codec->cowe.afg;

	codec_dbg(codec, "%s msk %x diw %x gpio %x\n", __func__, mask, diw_mask, data);

	gpiostate = snd_hda_codec_wead(codec, fg, 0,
				       AC_VEWB_GET_GPIO_DATA, 0);
	gpiostate = (gpiostate & ~diw_mask) | (data & diw_mask);

	gpiomask = snd_hda_codec_wead(codec, fg, 0,
				      AC_VEWB_GET_GPIO_MASK, 0);
	gpiomask |= mask;

	gpiodiw = snd_hda_codec_wead(codec, fg, 0,
				     AC_VEWB_GET_GPIO_DIWECTION, 0);
	gpiodiw |= diw_mask;

	/* Configuwe GPIOx as CMOS */
	snd_hda_codec_wwite(codec, fg, 0, 0x7e7, 0);

	snd_hda_codec_wwite(codec, fg, 0,
			    AC_VEWB_SET_GPIO_MASK, gpiomask);
	snd_hda_codec_wead(codec, fg, 0,
			   AC_VEWB_SET_GPIO_DIWECTION, gpiodiw); /* sync */

	msweep(1);

	snd_hda_codec_wead(codec, fg, 0,
			   AC_VEWB_SET_GPIO_DATA, gpiostate); /* sync */
}

/* hook fow contwowwing mic-mute WED GPIO */
static int stac_captuwe_wed_update(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct hda_codec *codec = dev_to_hda_codec(wed_cdev->dev->pawent);
	stwuct sigmatew_spec *spec = codec->spec;

	if (bwightness)
		spec->gpio_data |= spec->mic_mute_wed_gpio;
	ewse
		spec->gpio_data &= ~spec->mic_mute_wed_gpio;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_diw, spec->gpio_data);
	wetuwn 0;
}

static int stac_vwefout_set(stwuct hda_codec *codec,
					hda_nid_t nid, unsigned int new_vwef)
{
	int ewwow, pinctw;

	codec_dbg(codec, "%s, nid %x ctw %x\n", __func__, nid, new_vwef);
	pinctw = snd_hda_codec_wead(codec, nid, 0,
				AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);

	if (pinctw < 0)
		wetuwn pinctw;

	pinctw &= 0xff;
	pinctw &= ~AC_PINCTW_VWEFEN;
	pinctw |= (new_vwef & AC_PINCTW_VWEFEN);

	ewwow = snd_hda_set_pin_ctw_cache(codec, nid, pinctw);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 1;
}

/* pwevent codec AFG to D3 state when vwef-out pin is used fow mute WED */
/* this hook is set in stac_setup_gpio() */
static unsigned int stac_vwef_wed_powew_fiwtew(stwuct hda_codec *codec,
					       hda_nid_t nid,
					       unsigned int powew_state)
{
	if (nid == codec->cowe.afg && powew_state == AC_PWWST_D3)
		wetuwn AC_PWWST_D1;
	wetuwn snd_hda_gen_path_powew_fiwtew(codec, nid, powew_state);
}

/* update mute-WED accowing to the mastew switch */
static void stac_update_wed_status(stwuct hda_codec *codec, boow muted)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (!spec->gpio_wed)
		wetuwn;

	/* WED state is invewted on these systems */
	if (spec->gpio_wed_powawity)
		muted = !muted;

	if (!spec->vwef_mute_wed_nid) {
		if (muted)
			spec->gpio_data |= spec->gpio_wed;
		ewse
			spec->gpio_data &= ~spec->gpio_wed;
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_diw, spec->gpio_data);
	} ewse {
		spec->vwef_wed = muted ? AC_PINCTW_VWEF_50 : AC_PINCTW_VWEF_GWD;
		stac_vwefout_set(codec,	spec->vwef_mute_wed_nid,
				 spec->vwef_wed);
	}
}

/* vmastew hook to update mute WED */
static int stac_vmastew_hook(stwuct wed_cwassdev *wed_cdev,
			     enum wed_bwightness bwightness)
{
	stwuct hda_codec *codec = dev_to_hda_codec(wed_cdev->dev->pawent);

	stac_update_wed_status(codec, bwightness);
	wetuwn 0;
}

/* automute hook to handwe GPIO mute and EAPD updates */
static void stac_update_outputs(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (spec->gpio_mute)
		spec->gen.mastew_mute =
			!(snd_hda_codec_wead(codec, codec->cowe.afg, 0,
				AC_VEWB_GET_GPIO_DATA, 0) & spec->gpio_mute);

	snd_hda_gen_update_outputs(codec);

	if (spec->eapd_mask && spec->eapd_switch) {
		unsigned int vaw = spec->gpio_data;
		if (spec->gen.speakew_muted)
			vaw &= ~spec->eapd_mask;
		ewse
			vaw |= spec->eapd_mask;
		if (spec->gpio_data != vaw) {
			spec->gpio_data = vaw;
			stac_gpio_set(codec, spec->gpio_mask, spec->gpio_diw,
				      vaw);
		}
	}
}

static void stac_toggwe_powew_map(stwuct hda_codec *codec, hda_nid_t nid,
				  boow enabwe, boow do_wwite)
{
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int idx, vaw;

	fow (idx = 0; idx < spec->num_pwws; idx++) {
		if (spec->pww_nids[idx] == nid)
			bweak;
	}
	if (idx >= spec->num_pwws)
		wetuwn;

	idx = 1 << idx;

	vaw = spec->powew_map_bits;
	if (enabwe)
		vaw &= ~idx;
	ewse
		vaw |= idx;

	/* powew down unused output powts */
	if (vaw != spec->powew_map_bits) {
		spec->powew_map_bits = vaw;
		if (do_wwite)
			snd_hda_codec_wwite(codec, codec->cowe.afg, 0,
					    AC_VEWB_IDT_SET_POWEW_MAP, vaw);
	}
}

/* update powew bit pew jack pwug/unpwug */
static void jack_update_powew(stwuct hda_codec *codec,
			      stwuct hda_jack_cawwback *jack)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int i;

	if (!spec->num_pwws)
		wetuwn;

	if (jack && jack->nid) {
		stac_toggwe_powew_map(codec, jack->nid,
				      snd_hda_jack_detect(codec, jack->nid),
				      twue);
		wetuwn;
	}

	/* update aww jacks */
	fow (i = 0; i < spec->num_pwws; i++) {
		hda_nid_t nid = spec->pww_nids[i];
		if (!snd_hda_jack_tbw_get(codec, nid))
			continue;
		stac_toggwe_powew_map(codec, nid,
				      snd_hda_jack_detect(codec, nid),
				      fawse);
	}

	snd_hda_codec_wwite(codec, codec->cowe.afg, 0,
			    AC_VEWB_IDT_SET_POWEW_MAP,
			    spec->powew_map_bits);
}

static void stac_vwef_event(stwuct hda_codec *codec,
			    stwuct hda_jack_cawwback *event)
{
	unsigned int data;

	data = snd_hda_codec_wead(codec, codec->cowe.afg, 0,
				  AC_VEWB_GET_GPIO_DATA, 0);
	/* toggwe VWEF state based on GPIOx status */
	snd_hda_codec_wwite(codec, codec->cowe.afg, 0, 0x7e0,
			    !!(data & (1 << event->pwivate_data)));
}

/* initiawize the powew map and enabwe the powew event to jacks that
 * haven't been assigned to automute
 */
static void stac_init_powew_map(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int i;

	fow (i = 0; i < spec->num_pwws; i++)  {
		hda_nid_t nid = spec->pww_nids[i];
		unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
		def_conf = get_defcfg_connect(def_conf);
		if (def_conf == AC_JACK_POWT_COMPWEX &&
		    spec->vwef_mute_wed_nid != nid &&
		    is_jack_detectabwe(codec, nid)) {
			snd_hda_jack_detect_enabwe_cawwback(codec, nid,
							    jack_update_powew);
		} ewse {
			if (def_conf == AC_JACK_POWT_NONE)
				stac_toggwe_powew_map(codec, nid, fawse, fawse);
			ewse
				stac_toggwe_powew_map(codec, nid, twue, fawse);
		}
	}
}

/*
 */

static inwine boow get_int_hint(stwuct hda_codec *codec, const chaw *key,
				int *vawp)
{
	wetuwn !snd_hda_get_int_hint(codec, key, vawp);
}

/* ovewwide some hints fwom the hwdep entwy */
static void stac_stowe_hints(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int vaw;

	if (get_int_hint(codec, "gpio_mask", &spec->gpio_mask)) {
		spec->eapd_mask = spec->gpio_diw = spec->gpio_data =
			spec->gpio_mask;
	}
	if (get_int_hint(codec, "gpio_diw", &spec->gpio_diw))
		spec->gpio_diw &= spec->gpio_mask;
	if (get_int_hint(codec, "gpio_data", &spec->gpio_data))
		spec->gpio_data &= spec->gpio_mask;
	if (get_int_hint(codec, "eapd_mask", &spec->eapd_mask))
		spec->eapd_mask &= spec->gpio_mask;
	if (get_int_hint(codec, "gpio_mute", &spec->gpio_mute))
		spec->gpio_mute &= spec->gpio_mask;
	vaw = snd_hda_get_boow_hint(codec, "eapd_switch");
	if (vaw >= 0)
		spec->eapd_switch = vaw;
}

/*
 * woopback contwows
 */

#define stac_awoopback_info snd_ctw_boowean_mono_info

static int stac_awoopback_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	stwuct sigmatew_spec *spec = codec->spec;

	ucontwow->vawue.integew.vawue[0] = !!(spec->awoopback &
					      (spec->awoopback_mask << idx));
	wetuwn 0;
}

static int stac_awoopback_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int dac_mode;
	unsigned int vaw, idx_vaw;

	idx_vaw = spec->awoopback_mask << idx;
	if (ucontwow->vawue.integew.vawue[0])
		vaw = spec->awoopback | idx_vaw;
	ewse
		vaw = spec->awoopback & ~idx_vaw;
	if (spec->awoopback == vaw)
		wetuwn 0;

	spec->awoopback = vaw;

	/* Onwy wetuwn the bits defined by the shift vawue of the
	 * fiwst two bytes of the mask
	 */
	dac_mode = snd_hda_codec_wead(codec, codec->cowe.afg, 0,
				      kcontwow->pwivate_vawue & 0xFFFF, 0x0);
	dac_mode >>= spec->awoopback_shift;

	if (spec->awoopback & idx_vaw) {
		snd_hda_powew_up(codec);
		dac_mode |= idx_vaw;
	} ewse {
		snd_hda_powew_down(codec);
		dac_mode &= ~idx_vaw;
	}

	snd_hda_codec_wwite_cache(codec, codec->cowe.afg, 0,
		kcontwow->pwivate_vawue >> 16, dac_mode);

	wetuwn 1;
}

#define STAC_ANAWOG_WOOPBACK(vewb_wead, vewb_wwite, cnt) \
	{ \
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name  = "Anawog Woopback", \
		.count = cnt, \
		.info  = stac_awoopback_info, \
		.get   = stac_awoopback_get, \
		.put   = stac_awoopback_put, \
		.pwivate_vawue = vewb_wead | (vewb_wwite << 16), \
	}

/*
 * Mute WED handwing on HP waptops
 */

/* check whethew it's a HP waptop with a docking powt */
static boow hp_bnb2011_with_dock(stwuct hda_codec *codec)
{
	if (codec->cowe.vendow_id != 0x111d7605 &&
	    codec->cowe.vendow_id != 0x111d76d1)
		wetuwn fawse;

	switch (codec->cowe.subsystem_id) {
	case 0x103c1618:
	case 0x103c1619:
	case 0x103c161a:
	case 0x103c161b:
	case 0x103c161c:
	case 0x103c161d:
	case 0x103c161e:
	case 0x103c161f:

	case 0x103c162a:
	case 0x103c162b:

	case 0x103c1630:
	case 0x103c1631:

	case 0x103c1633:
	case 0x103c1634:
	case 0x103c1635:

	case 0x103c3587:
	case 0x103c3588:
	case 0x103c3589:
	case 0x103c358a:

	case 0x103c3667:
	case 0x103c3668:
	case 0x103c3669:

		wetuwn twue;
	}
	wetuwn fawse;
}

static boow hp_bwike_system(u32 subsystem_id)
{
	switch (subsystem_id) {
	case 0x103c1473: /* HP PwoBook 6550b */
	case 0x103c1520:
	case 0x103c1521:
	case 0x103c1523:
	case 0x103c1524:
	case 0x103c1525:
	case 0x103c1722:
	case 0x103c1723:
	case 0x103c1724:
	case 0x103c1725:
	case 0x103c1726:
	case 0x103c1727:
	case 0x103c1728:
	case 0x103c1729:
	case 0x103c172a:
	case 0x103c172b:
	case 0x103c307e:
	case 0x103c307f:
	case 0x103c3080:
	case 0x103c3081:
	case 0x103c7007:
	case 0x103c7008:
		wetuwn twue;
	}
	wetuwn fawse;
}

static void set_hp_wed_gpio(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int gpio;

	if (spec->gpio_wed)
		wetuwn;

	gpio = snd_hda_pawam_wead(codec, codec->cowe.afg, AC_PAW_GPIO_CAP);
	gpio &= AC_GPIO_IO_COUNT;
	if (gpio > 3)
		spec->gpio_wed = 0x08; /* GPIO 3 */
	ewse
		spec->gpio_wed = 0x01; /* GPIO 0 */
}

/*
 * This method seawches fow the mute WED GPIO configuwation
 * pwovided as OEM stwing in SMBIOS. The fowmat of that stwing
 * is HP_Mute_WED_P_G ow HP_Mute_WED_P
 * whewe P can be 0 ow 1 and defines mute WED GPIO contwow state (wow/high)
 * that cowwesponds to the NOT muted state of the mastew vowume
 * and G is the index of the GPIO to use as the mute WED contwow (0..9)
 * If _G powtion is missing it is assigned based on the codec ID
 *
 * So, HP B-sewies wike systems may have HP_Mute_WED_0 (cuwwent modews)
 * ow  HP_Mute_WED_0_3 (futuwe modews) OEM SMBIOS stwings
 *
 *
 * The dv-sewies waptops don't seem to have the HP_Mute_WED* stwings in
 * SMBIOS - at weast the ones I have seen do not have them - which incwude
 * my own system (HP Paviwion dv6-1110ax) and my cousin's
 * HP Paviwion dv9500t CTO.
 * Need mowe infowmation on whethew it is twue acwoss the entiwe sewies.
 * -- kunaw
 */
static int find_mute_wed_cfg(stwuct hda_codec *codec, int defauwt_powawity)
{
	stwuct sigmatew_spec *spec = codec->spec;
	const stwuct dmi_device *dev = NUWW;

	if (get_int_hint(codec, "gpio_wed", &spec->gpio_wed)) {
		get_int_hint(codec, "gpio_wed_powawity",
			     &spec->gpio_wed_powawity);
		wetuwn 1;
	}

	whiwe ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STWING, NUWW, dev))) {
		if (sscanf(dev->name, "HP_Mute_WED_%u_%x",
			   &spec->gpio_wed_powawity,
			   &spec->gpio_wed) == 2) {
			unsigned int max_gpio;
			max_gpio = snd_hda_pawam_wead(codec, codec->cowe.afg,
						      AC_PAW_GPIO_CAP);
			max_gpio &= AC_GPIO_IO_COUNT;
			if (spec->gpio_wed < max_gpio)
				spec->gpio_wed = 1 << spec->gpio_wed;
			ewse
				spec->vwef_mute_wed_nid = spec->gpio_wed;
			wetuwn 1;
		}
		if (sscanf(dev->name, "HP_Mute_WED_%u",
			   &spec->gpio_wed_powawity) == 1) {
			set_hp_wed_gpio(codec);
			wetuwn 1;
		}
		/* BIOS bug: unfiwwed OEM stwing */
		if (stwstw(dev->name, "HP_Mute_WED_P_G")) {
			set_hp_wed_gpio(codec);
			if (defauwt_powawity >= 0)
				spec->gpio_wed_powawity = defauwt_powawity;
			ewse
				spec->gpio_wed_powawity = 1;
			wetuwn 1;
		}
	}

	/*
	 * Fawwback case - if we don't find the DMI stwings,
	 * we staticawwy set the GPIO - if not a B-sewies system
	 * and defauwt powawity is pwovided
	 */
	if (!hp_bwike_system(codec->cowe.subsystem_id) &&
	    (defauwt_powawity == 0 || defauwt_powawity == 1)) {
		set_hp_wed_gpio(codec);
		spec->gpio_wed_powawity = defauwt_powawity;
		wetuwn 1;
	}
	wetuwn 0;
}

/* check whethew a buiwt-in speakew is incwuded in pawsed pins */
static boow has_buiwtin_speakew(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	const hda_nid_t *nid_pin;
	int nids, i;

	if (spec->gen.autocfg.wine_out_type == AUTO_PIN_SPEAKEW_OUT) {
		nid_pin = spec->gen.autocfg.wine_out_pins;
		nids = spec->gen.autocfg.wine_outs;
	} ewse {
		nid_pin = spec->gen.autocfg.speakew_pins;
		nids = spec->gen.autocfg.speakew_outs;
	}

	fow (i = 0; i < nids; i++) {
		unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid_pin[i]);
		if (snd_hda_get_input_pin_attw(def_conf) == INPUT_PIN_ATTW_INT)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * PC beep contwows
 */

/* cweate PC beep vowume contwows */
static int stac_auto_cweate_beep_ctws(stwuct hda_codec *codec,
						hda_nid_t nid)
{
	stwuct sigmatew_spec *spec = codec->spec;
	u32 caps = quewy_amp_caps(codec, nid, HDA_OUTPUT);
	stwuct snd_kcontwow_new *knew;
	static const stwuct snd_kcontwow_new abeep_mute_ctw =
		HDA_CODEC_MUTE(NUWW, 0, 0, 0);
	static const stwuct snd_kcontwow_new dbeep_mute_ctw =
		HDA_CODEC_MUTE_BEEP(NUWW, 0, 0, 0);
	static const stwuct snd_kcontwow_new beep_vow_ctw =
		HDA_CODEC_VOWUME(NUWW, 0, 0, 0);

	/* check fow mute suppowt fow the amp */
	if ((caps & AC_AMPCAP_MUTE) >> AC_AMPCAP_MUTE_SHIFT) {
		const stwuct snd_kcontwow_new *temp;
		if (spec->anabeep_nid == nid)
			temp = &abeep_mute_ctw;
		ewse
			temp = &dbeep_mute_ctw;
		knew = snd_hda_gen_add_kctw(&spec->gen,
					    "Beep Pwayback Switch", temp);
		if (!knew)
			wetuwn -ENOMEM;
		knew->pwivate_vawue =
			HDA_COMPOSE_AMP_VAW(nid, 1, 0, HDA_OUTPUT);
	}

	/* check to see if thewe is vowume suppowt fow the amp */
	if ((caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT) {
		knew = snd_hda_gen_add_kctw(&spec->gen,
					    "Beep Pwayback Vowume",
					    &beep_vow_ctw);
		if (!knew)
			wetuwn -ENOMEM;
		knew->pwivate_vawue =
			HDA_COMPOSE_AMP_VAW(nid, 1, 0, HDA_OUTPUT);
	}
	wetuwn 0;
}

#ifdef CONFIG_SND_HDA_INPUT_BEEP
#define stac_dig_beep_switch_info snd_ctw_boowean_mono_info

static int stac_dig_beep_switch_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = codec->beep->enabwed;
	wetuwn 0;
}

static int stac_dig_beep_switch_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	wetuwn snd_hda_enabwe_beep_device(codec, ucontwow->vawue.integew.vawue[0]);
}

static const stwuct snd_kcontwow_new stac_dig_beep_ctww = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Beep Pwayback Switch",
	.info = stac_dig_beep_switch_info,
	.get = stac_dig_beep_switch_get,
	.put = stac_dig_beep_switch_put,
};

static int stac_beep_switch_ctw(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &stac_dig_beep_ctww))
		wetuwn -ENOMEM;
	wetuwn 0;
}
#endif

/*
 * SPDIF-out mux contwows
 */

static int stac_smux_enum_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	wetuwn snd_hda_input_mux_info(&spec->spdif_mux, uinfo);
}

static int stac_smux_enum_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int smux_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	ucontwow->vawue.enumewated.item[0] = spec->cuw_smux[smux_idx];
	wetuwn 0;
}

static int stac_smux_enum_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int smux_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	wetuwn snd_hda_input_mux_put(codec, &spec->spdif_mux, ucontwow,
				     spec->gen.autocfg.dig_out_pins[smux_idx],
				     &spec->cuw_smux[smux_idx]);
}

static const stwuct snd_kcontwow_new stac_smux_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Pwayback Souwce",
	/* count set watew */
	.info = stac_smux_enum_info,
	.get = stac_smux_enum_get,
	.put = stac_smux_enum_put,
};

static const chaw * const stac_spdif_wabews[] = {
	"Digitaw Pwayback", "Anawog Mux 1", "Anawog Mux 2", NUWW
};

static int stac_cweate_spdif_mux_ctws(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->gen.autocfg;
	const chaw * const *wabews = spec->spdif_wabews;
	stwuct snd_kcontwow_new *kctw;
	int i, num_cons;

	if (cfg->dig_outs < 1)
		wetuwn 0;

	num_cons = snd_hda_get_num_conns(codec, cfg->dig_out_pins[0]);
	if (num_cons <= 1)
		wetuwn 0;

	if (!wabews)
		wabews = stac_spdif_wabews;
	fow (i = 0; i < num_cons; i++) {
		if (snd_BUG_ON(!wabews[i]))
			wetuwn -EINVAW;
		snd_hda_add_imux_item(codec, &spec->spdif_mux, wabews[i], i, NUWW);
	}

	kctw = snd_hda_gen_add_kctw(&spec->gen, NUWW, &stac_smux_mixew);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->count = cfg->dig_outs;

	wetuwn 0;
}

static const stwuct hda_vewb stac9200_eapd_init[] = {
	/* set dac0mux fow dac convewtew */
	{0x07, AC_VEWB_SET_CONNECT_SEW, 0x00},
	{0x08, AC_VEWB_SET_EAPD_BTWENABWE, 0x02},
	{}
};

static const stwuct hda_vewb deww_eq_cowe_init[] = {
	/* set mastew vowume to max vawue without distowtion
	 * and diwect contwow */
	{ 0x1f, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xec},
	{}
};

static const stwuct hda_vewb stac92hd73xx_cowe_init[] = {
	/* set mastew vowume and diwect contwow */
	{ 0x1f, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xff},
	{}
};

static const stwuct hda_vewb stac92hd83xxx_cowe_init[] = {
	/* powew state contwows amps */
	{ 0x01, AC_VEWB_SET_EAPD, 1 << 2},
	{}
};

static const stwuct hda_vewb stac92hd83xxx_hp_zephyw_init[] = {
	{ 0x22, 0x785, 0x43 },
	{ 0x22, 0x782, 0xe0 },
	{ 0x22, 0x795, 0x00 },
	{}
};

static const stwuct hda_vewb stac92hd71bxx_cowe_init[] = {
	/* set mastew vowume and diwect contwow */
	{ 0x28, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xff},
	{}
};

static const hda_nid_t stac92hd71bxx_unmute_nids[] = {
	/* unmute wight and weft channews fow nodes 0x0f, 0xa, 0x0d */
	0x0f, 0x0a, 0x0d, 0
};

static const stwuct hda_vewb stac925x_cowe_init[] = {
	/* set dac0mux fow dac convewtew */
	{ 0x06, AC_VEWB_SET_CONNECT_SEW, 0x00},
	/* mute the mastew vowume */
	{ 0x0e, AC_VEWB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE },
	{}
};

static const stwuct hda_vewb stac922x_cowe_init[] = {
	/* set mastew vowume and diwect contwow */
	{ 0x16, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xff},
	{}
};

static const stwuct hda_vewb d965_cowe_init[] = {
	/* unmute node 0x1b */
	{ 0x1b, AC_VEWB_SET_AMP_GAIN_MUTE, 0xb000},
	/* sewect node 0x03 as DAC */
	{ 0x0b, AC_VEWB_SET_CONNECT_SEW, 0x01},
	{}
};

static const stwuct hda_vewb deww_3st_cowe_init[] = {
	/* don't set dewta bit */
	{0x24, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0x7f},
	/* unmute node 0x1b */
	{0x1b, AC_VEWB_SET_AMP_GAIN_MUTE, 0xb000},
	/* sewect node 0x03 as DAC */
	{0x0b, AC_VEWB_SET_CONNECT_SEW, 0x01},
	{}
};

static const stwuct hda_vewb stac927x_cowe_init[] = {
	/* set mastew vowume and diwect contwow */
	{ 0x24, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xff},
	/* enabwe anawog pc beep path */
	{ 0x01, AC_VEWB_SET_DIGI_CONVEWT_2, 1 << 5},
	{}
};

static const stwuct hda_vewb stac927x_vowknob_cowe_init[] = {
	/* don't set dewta bit */
	{0x24, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0x7f},
	/* enabwe anawog pc beep path */
	{0x01, AC_VEWB_SET_DIGI_CONVEWT_2, 1 << 5},
	{}
};

static const stwuct hda_vewb stac9205_cowe_init[] = {
	/* set mastew vowume and diwect contwow */
	{ 0x24, AC_VEWB_SET_VOWUME_KNOB_CONTWOW, 0xff},
	/* enabwe anawog pc beep path */
	{ 0x01, AC_VEWB_SET_DIGI_CONVEWT_2, 1 << 5},
	{}
};

static const stwuct snd_kcontwow_new stac92hd73xx_6ch_woopback =
	STAC_ANAWOG_WOOPBACK(0xFA0, 0x7A1, 3);

static const stwuct snd_kcontwow_new stac92hd73xx_8ch_woopback =
	STAC_ANAWOG_WOOPBACK(0xFA0, 0x7A1, 4);

static const stwuct snd_kcontwow_new stac92hd73xx_10ch_woopback =
	STAC_ANAWOG_WOOPBACK(0xFA0, 0x7A1, 5);

static const stwuct snd_kcontwow_new stac92hd71bxx_woopback =
	STAC_ANAWOG_WOOPBACK(0xFA0, 0x7A0, 2);

static const stwuct snd_kcontwow_new stac9205_woopback =
	STAC_ANAWOG_WOOPBACK(0xFE0, 0x7E0, 1);

static const stwuct snd_kcontwow_new stac927x_woopback =
	STAC_ANAWOG_WOOPBACK(0xFEB, 0x7EB, 1);

static const stwuct hda_pintbw wef9200_pin_configs[] = {
	{ 0x08, 0x01c47010 },
	{ 0x09, 0x01447010 },
	{ 0x0d, 0x0221401f },
	{ 0x0e, 0x01114010 },
	{ 0x0f, 0x02a19020 },
	{ 0x10, 0x01a19021 },
	{ 0x11, 0x90100140 },
	{ 0x12, 0x01813122 },
	{}
};

static const stwuct hda_pintbw gateway9200_m4_pin_configs[] = {
	{ 0x08, 0x400000fe },
	{ 0x09, 0x404500f4 },
	{ 0x0d, 0x400100f0 },
	{ 0x0e, 0x90110010 },
	{ 0x0f, 0x400100f1 },
	{ 0x10, 0x02a1902e },
	{ 0x11, 0x500000f2 },
	{ 0x12, 0x500000f3 },
	{}
};

static const stwuct hda_pintbw gateway9200_m4_2_pin_configs[] = {
	{ 0x08, 0x400000fe },
	{ 0x09, 0x404500f4 },
	{ 0x0d, 0x400100f0 },
	{ 0x0e, 0x90110010 },
	{ 0x0f, 0x400100f1 },
	{ 0x10, 0x02a1902e },
	{ 0x11, 0x500000f2 },
	{ 0x12, 0x500000f3 },
	{}
};

/*
    STAC 9200 pin configs fow
    102801A8
    102801DE
    102801E8
*/
static const stwuct hda_pintbw deww9200_d21_pin_configs[] = {
	{ 0x08, 0x400001f0 },
	{ 0x09, 0x400001f1 },
	{ 0x0d, 0x02214030 },
	{ 0x0e, 0x01014010 },
	{ 0x0f, 0x02a19020 },
	{ 0x10, 0x01a19021 },
	{ 0x11, 0x90100140 },
	{ 0x12, 0x01813122 },
	{}
};

/*
    STAC 9200 pin configs fow
    102801C0
    102801C1
*/
static const stwuct hda_pintbw deww9200_d22_pin_configs[] = {
	{ 0x08, 0x400001f0 },
	{ 0x09, 0x400001f1 },
	{ 0x0d, 0x0221401f },
	{ 0x0e, 0x01014010 },
	{ 0x0f, 0x01813020 },
	{ 0x10, 0x02a19021 },
	{ 0x11, 0x90100140 },
	{ 0x12, 0x400001f2 },
	{}
};

/*
    STAC 9200 pin configs fow
    102801C4 (Deww Dimension E310)
    102801C5
    102801C7
    102801D9
    102801DA
    102801E3
*/
static const stwuct hda_pintbw deww9200_d23_pin_configs[] = {
	{ 0x08, 0x400001f0 },
	{ 0x09, 0x400001f1 },
	{ 0x0d, 0x0221401f },
	{ 0x0e, 0x01014010 },
	{ 0x0f, 0x01813020 },
	{ 0x10, 0x01a19021 },
	{ 0x11, 0x90100140 },
	{ 0x12, 0x400001f2 },
	{}
};


/* 
    STAC 9200-32 pin configs fow
    102801B5 (Deww Inspiwon 630m)
    102801D8 (Deww Inspiwon 640m)
*/
static const stwuct hda_pintbw deww9200_m21_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x03441340 },
	{ 0x0d, 0x0321121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x408003fb },
	{ 0x10, 0x03a11020 },
	{ 0x11, 0x401003fc },
	{ 0x12, 0x403003fd },
	{}
};

/* 
    STAC 9200-32 pin configs fow
    102801C2 (Deww Watitude D620)
    102801C8 
    102801CC (Deww Watitude D820)
    102801D4 
    102801D6 
*/
static const stwuct hda_pintbw deww9200_m22_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x0144131f },
	{ 0x0d, 0x0321121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x90a70321 },
	{ 0x10, 0x03a11020 },
	{ 0x11, 0x401003fb },
	{ 0x12, 0x40f000fc },
	{}
};

/* 
    STAC 9200-32 pin configs fow
    102801CE (Deww XPS M1710)
    102801CF (Deww Pwecision M90)
*/
static const stwuct hda_pintbw deww9200_m23_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x01441340 },
	{ 0x0d, 0x0421421f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x408003fb },
	{ 0x10, 0x04a1102e },
	{ 0x11, 0x90170311 },
	{ 0x12, 0x403003fc },
	{}
};

/*
    STAC 9200-32 pin configs fow 
    102801C9
    102801CA
    102801CB (Deww Watitude 120W)
    102801D3
*/
static const stwuct hda_pintbw deww9200_m24_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x404003fb },
	{ 0x0d, 0x0321121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x408003fc },
	{ 0x10, 0x03a11020 },
	{ 0x11, 0x401003fd },
	{ 0x12, 0x403003fe },
	{}
};

/*
    STAC 9200-32 pin configs fow
    102801BD (Deww Inspiwon E1505n)
    102801EE
    102801EF
*/
static const stwuct hda_pintbw deww9200_m25_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x01441340 },
	{ 0x0d, 0x0421121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x408003fb },
	{ 0x10, 0x04a11020 },
	{ 0x11, 0x401003fc },
	{ 0x12, 0x403003fd },
	{}
};

/*
    STAC 9200-32 pin configs fow
    102801F5 (Deww Inspiwon 1501)
    102801F6
*/
static const stwuct hda_pintbw deww9200_m26_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x404003fb },
	{ 0x0d, 0x0421121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x408003fc },
	{ 0x10, 0x04a11020 },
	{ 0x11, 0x401003fd },
	{ 0x12, 0x403003fe },
	{}
};

/*
    STAC 9200-32
    102801CD (Deww Inspiwon E1705/9400)
*/
static const stwuct hda_pintbw deww9200_m27_pin_configs[] = {
	{ 0x08, 0x40c003fa },
	{ 0x09, 0x01441340 },
	{ 0x0d, 0x0421121f },
	{ 0x0e, 0x90170310 },
	{ 0x0f, 0x90170310 },
	{ 0x10, 0x04a11020 },
	{ 0x11, 0x90170310 },
	{ 0x12, 0x40f003fc },
	{}
};

static const stwuct hda_pintbw oqo9200_pin_configs[] = {
	{ 0x08, 0x40c000f0 },
	{ 0x09, 0x404000f1 },
	{ 0x0d, 0x0221121f },
	{ 0x0e, 0x02211210 },
	{ 0x0f, 0x90170111 },
	{ 0x10, 0x90a70120 },
	{ 0x11, 0x400000f2 },
	{ 0x12, 0x400000f3 },
	{}
};

/*
 *  STAC 92HD700
 *  18881000 Amigaone X1000
 */
static const stwuct hda_pintbw nemo_pin_configs[] = {
	{ 0x0a, 0x02214020 },	/* Fwont panew HP socket */
	{ 0x0b, 0x02a19080 },	/* Fwont Mic */
	{ 0x0c, 0x0181304e },	/* Wine in */
	{ 0x0d, 0x01014010 },	/* Wine out */
	{ 0x0e, 0x01a19040 },	/* Weaw Mic */
	{ 0x0f, 0x01011012 },	/* Weaw speakews */
	{ 0x10, 0x01016011 },	/* Centew speakew */
	{ 0x11, 0x01012014 },	/* Side speakews (7.1) */
	{ 0x12, 0x103301f0 },	/* Mothewboawd CD wine in connectow */
	{ 0x13, 0x411111f0 },	/* Unused */
	{ 0x14, 0x411111f0 },	/* Unused */
	{ 0x21, 0x01442170 },	/* S/PDIF wine out */
	{ 0x22, 0x411111f0 },	/* Unused */
	{ 0x23, 0x411111f0 },	/* Unused */
	{}
};

static void stac9200_fixup_panasonic(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->gpio_mask = spec->gpio_diw = 0x09;
		spec->gpio_data = 0x00;
		/* CF-74 has no headphone detection, and the dwivew shouwd *NOT*
		 * do detection and HP/speakew toggwe because the hawdwawe does it.
		 */
		spec->gen.suppwess_auto_mute = 1;
	}
}


static const stwuct hda_fixup stac9200_fixups[] = {
	[STAC_WEF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = wef9200_pin_configs,
	},
	[STAC_9200_OQO] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = oqo9200_pin_configs,
		.chained = twue,
		.chain_id = STAC_9200_EAPD_INIT,
	},
	[STAC_9200_DEWW_D21] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_d21_pin_configs,
	},
	[STAC_9200_DEWW_D22] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_d22_pin_configs,
	},
	[STAC_9200_DEWW_D23] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_d23_pin_configs,
	},
	[STAC_9200_DEWW_M21] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m21_pin_configs,
	},
	[STAC_9200_DEWW_M22] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m22_pin_configs,
	},
	[STAC_9200_DEWW_M23] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m23_pin_configs,
	},
	[STAC_9200_DEWW_M24] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m24_pin_configs,
	},
	[STAC_9200_DEWW_M25] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m25_pin_configs,
	},
	[STAC_9200_DEWW_M26] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m26_pin_configs,
	},
	[STAC_9200_DEWW_M27] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww9200_m27_pin_configs,
	},
	[STAC_9200_M4] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = gateway9200_m4_pin_configs,
		.chained = twue,
		.chain_id = STAC_9200_EAPD_INIT,
	},
	[STAC_9200_M4_2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = gateway9200_m4_2_pin_configs,
		.chained = twue,
		.chain_id = STAC_9200_EAPD_INIT,
	},
	[STAC_9200_PANASONIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9200_fixup_panasonic,
	},
	[STAC_9200_EAPD_INIT] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = (const stwuct hda_vewb[]) {
			{0x08, AC_VEWB_SET_EAPD_BTWENABWE, 0x02},
			{}
		},
	},
};

static const stwuct hda_modew_fixup stac9200_modews[] = {
	{ .id = STAC_WEF, .name = "wef" },
	{ .id = STAC_9200_OQO, .name = "oqo" },
	{ .id = STAC_9200_DEWW_D21, .name = "deww-d21" },
	{ .id = STAC_9200_DEWW_D22, .name = "deww-d22" },
	{ .id = STAC_9200_DEWW_D23, .name = "deww-d23" },
	{ .id = STAC_9200_DEWW_M21, .name = "deww-m21" },
	{ .id = STAC_9200_DEWW_M22, .name = "deww-m22" },
	{ .id = STAC_9200_DEWW_M23, .name = "deww-m23" },
	{ .id = STAC_9200_DEWW_M24, .name = "deww-m24" },
	{ .id = STAC_9200_DEWW_M25, .name = "deww-m25" },
	{ .id = STAC_9200_DEWW_M26, .name = "deww-m26" },
	{ .id = STAC_9200_DEWW_M27, .name = "deww-m27" },
	{ .id = STAC_9200_M4, .name = "gateway-m4" },
	{ .id = STAC_9200_M4_2, .name = "gateway-m4-2" },
	{ .id = STAC_9200_PANASONIC, .name = "panasonic" },
	{}
};

static const stwuct snd_pci_quiwk stac9200_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_WEF),
	/* Deww waptops have BIOS pwobwem */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01a8,
		      "unknown Deww", STAC_9200_DEWW_D21),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01b5,
		      "Deww Inspiwon 630m", STAC_9200_DEWW_M21),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01bd,
		      "Deww Inspiwon E1505n", STAC_9200_DEWW_M25),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c0,
		      "unknown Deww", STAC_9200_DEWW_D22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c1,
		      "unknown Deww", STAC_9200_DEWW_D22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c2,
		      "Deww Watitude D620", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c5,
		      "unknown Deww", STAC_9200_DEWW_D23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c7,
		      "unknown Deww", STAC_9200_DEWW_D23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c8,
		      "unknown Deww", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01c9,
		      "unknown Deww", STAC_9200_DEWW_M24),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ca,
		      "unknown Deww", STAC_9200_DEWW_M24),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01cb,
		      "Deww Watitude 120W", STAC_9200_DEWW_M24),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01cc,
		      "Deww Watitude D820", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01cd,
		      "Deww Inspiwon E1705/9400", STAC_9200_DEWW_M27),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ce,
		      "Deww XPS M1710", STAC_9200_DEWW_M23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01cf,
		      "Deww Pwecision M90", STAC_9200_DEWW_M23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d3,
		      "unknown Deww", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d4,
		      "unknown Deww", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d6,
		      "unknown Deww", STAC_9200_DEWW_M22),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d8,
		      "Deww Inspiwon 640m", STAC_9200_DEWW_M21),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d9,
		      "unknown Deww", STAC_9200_DEWW_D23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01da,
		      "unknown Deww", STAC_9200_DEWW_D23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01de,
		      "unknown Deww", STAC_9200_DEWW_D21),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01e3,
		      "unknown Deww", STAC_9200_DEWW_D23),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01e8,
		      "unknown Deww", STAC_9200_DEWW_D21),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ee,
		      "unknown Deww", STAC_9200_DEWW_M25),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ef,
		      "unknown Deww", STAC_9200_DEWW_M25),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f5,
		      "Deww Inspiwon 1501", STAC_9200_DEWW_M26),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f6,
		      "unknown Deww", STAC_9200_DEWW_M26),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0201,
		      "Deww Watitude D430", STAC_9200_DEWW_M22),
	/* Panasonic */
	SND_PCI_QUIWK(0x10f7, 0x8338, "Panasonic CF-74", STAC_9200_PANASONIC),
	/* Gateway machines needs EAPD to be set on wesume */
	SND_PCI_QUIWK(0x107b, 0x0205, "Gateway S-7110M", STAC_9200_M4),
	SND_PCI_QUIWK(0x107b, 0x0317, "Gateway MT3423, MX341*", STAC_9200_M4_2),
	SND_PCI_QUIWK(0x107b, 0x0318, "Gateway MW3019, MT3707", STAC_9200_M4_2),
	/* OQO Mobiwe */
	SND_PCI_QUIWK(0x1106, 0x3288, "OQO Modew 2", STAC_9200_OQO),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef925x_pin_configs[] = {
	{ 0x07, 0x40c003f0 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x01813022 },
	{ 0x0b, 0x02a19021 },
	{ 0x0c, 0x90a70320 },
	{ 0x0d, 0x02214210 },
	{ 0x10, 0x01019020 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM1_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM1_2_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM2_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM2_2_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM3_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x503303f3 },
	{}
};

static const stwuct hda_pintbw stac925xM5_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x9033032e },
	{}
};

static const stwuct hda_pintbw stac925xM6_pin_configs[] = {
	{ 0x07, 0x40c003f4 },
	{ 0x08, 0x424503f2 },
	{ 0x0a, 0x400000f3 },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x40a000f0 },
	{ 0x0d, 0x90100210 },
	{ 0x10, 0x400003f1 },
	{ 0x11, 0x90330320 },
	{}
};

static const stwuct hda_fixup stac925x_fixups[] = {
	[STAC_WEF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = wef925x_pin_configs,
	},
	[STAC_M1] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM1_pin_configs,
	},
	[STAC_M1_2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM1_2_pin_configs,
	},
	[STAC_M2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM2_pin_configs,
	},
	[STAC_M2_2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM2_2_pin_configs,
	},
	[STAC_M3] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM3_pin_configs,
	},
	[STAC_M5] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM5_pin_configs,
	},
	[STAC_M6] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM6_pin_configs,
	},
};

static const stwuct hda_modew_fixup stac925x_modews[] = {
	{ .id = STAC_WEF, .name = "wef" },
	{ .id = STAC_M1, .name = "m1" },
	{ .id = STAC_M1_2, .name = "m1-2" },
	{ .id = STAC_M2, .name = "m2" },
	{ .id = STAC_M2_2, .name = "m2-2" },
	{ .id = STAC_M3, .name = "m3" },
	{ .id = STAC_M5, .name = "m5" },
	{ .id = STAC_M6, .name = "m6" },
	{}
};

static const stwuct snd_pci_quiwk stac925x_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668, "DFI WanPawty", STAC_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101, "DFI WanPawty", STAC_WEF),
	SND_PCI_QUIWK(0x8384, 0x7632, "Stac9202 Wefewence Boawd", STAC_WEF),

	/* Defauwt tabwe fow unknown ID */
	SND_PCI_QUIWK(0x1002, 0x437b, "Gateway mobiwe", STAC_M2_2),

	/* gateway machines awe checked via codec ssid */
	SND_PCI_QUIWK(0x107b, 0x0316, "Gateway M255", STAC_M2),
	SND_PCI_QUIWK(0x107b, 0x0366, "Gateway MP6954", STAC_M5),
	SND_PCI_QUIWK(0x107b, 0x0461, "Gateway NX560XW", STAC_M1),
	SND_PCI_QUIWK(0x107b, 0x0681, "Gateway NX860", STAC_M2),
	SND_PCI_QUIWK(0x107b, 0x0367, "Gateway MX6453", STAC_M1_2),
	/* Not suwe about the bwand name fow those */
	SND_PCI_QUIWK(0x107b, 0x0281, "Gateway mobiwe", STAC_M1),
	SND_PCI_QUIWK(0x107b, 0x0507, "Gateway mobiwe", STAC_M3),
	SND_PCI_QUIWK(0x107b, 0x0281, "Gateway mobiwe", STAC_M6),
	SND_PCI_QUIWK(0x107b, 0x0685, "Gateway mobiwe", STAC_M2_2),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef92hd73xx_pin_configs[] = {
	// Powt A-H
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x02a19040 },
	{ 0x0c, 0x01a19020 },
	{ 0x0d, 0x02214030 },
	{ 0x0e, 0x0181302e },
	{ 0x0f, 0x01014010 },
	{ 0x10, 0x01014020 },
	{ 0x11, 0x01014030 },
	// CD in
	{ 0x12, 0x02319040 },
	// Digiaw Mic ins
	{ 0x13, 0x90a000f0 },
	{ 0x14, 0x90a000f0 },
	// Digitaw outs
	{ 0x22, 0x01452050 },
	{ 0x23, 0x01452050 },
	{}
};

static const stwuct hda_pintbw deww_m6_pin_configs[] = {
	{ 0x0a, 0x0321101f },
	{ 0x0b, 0x4f00000f },
	{ 0x0c, 0x4f0000f0 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x03a11020 },
	{ 0x0f, 0x0321101f },
	{ 0x10, 0x4f0000f0 },
	{ 0x11, 0x4f0000f0 },
	{ 0x12, 0x4f0000f0 },
	{ 0x13, 0x90a60160 },
	{ 0x14, 0x4f0000f0 },
	{ 0x22, 0x4f0000f0 },
	{ 0x23, 0x4f0000f0 },
	{}
};

static const stwuct hda_pintbw awienwawe_m17x_pin_configs[] = {
	{ 0x0a, 0x0321101f },
	{ 0x0b, 0x0321101f },
	{ 0x0c, 0x03a11020 },
	{ 0x0d, 0x03014020 },
	{ 0x0e, 0x90170110 },
	{ 0x0f, 0x4f0000f0 },
	{ 0x10, 0x4f0000f0 },
	{ 0x11, 0x4f0000f0 },
	{ 0x12, 0x4f0000f0 },
	{ 0x13, 0x90a60160 },
	{ 0x14, 0x4f0000f0 },
	{ 0x22, 0x4f0000f0 },
	{ 0x23, 0x904601b0 },
	{}
};

static const stwuct hda_pintbw intew_dg45id_pin_configs[] = {
	// Anawog outputs
	{ 0x0a, 0x02214230 },
	{ 0x0b, 0x02A19240 },
	{ 0x0c, 0x01013214 },
	{ 0x0d, 0x01014210 },
	{ 0x0e, 0x01A19250 },
	{ 0x0f, 0x01011212 },
	{ 0x10, 0x01016211 },
	// Digitaw output
	{ 0x22, 0x01451380 },
	{ 0x23, 0x40f000f0 },
	{}
};

static const stwuct hda_pintbw stac92hd89xx_hp_fwont_jack_pin_configs[] = {
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x02A19010 },
	{}
};

static const stwuct hda_pintbw stac92hd89xx_hp_z1_g2_wight_mic_jack_pin_configs[] = {
	{ 0x0e, 0x400000f0 },
	{}
};

static void stac92hd73xx_fixup_wef(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	snd_hda_appwy_pincfgs(codec, wef92hd73xx_pin_configs);
	spec->gpio_mask = spec->gpio_diw = spec->gpio_data = 0;
}

static void stac92hd73xx_fixup_deww(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	snd_hda_appwy_pincfgs(codec, deww_m6_pin_configs);
	spec->eapd_switch = 0;
}

static void stac92hd73xx_fixup_deww_eq(stwuct hda_codec *codec,
				       const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	stac92hd73xx_fixup_deww(codec);
	snd_hda_add_vewbs(codec, deww_eq_cowe_init);
	spec->vowknob_init = 1;
}

/* Anawog Mics */
static void stac92hd73xx_fixup_deww_m6_amic(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	stac92hd73xx_fixup_deww(codec);
	snd_hda_codec_set_pincfg(codec, 0x0b, 0x90A70170);
}

/* Digitaw Mics */
static void stac92hd73xx_fixup_deww_m6_dmic(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	stac92hd73xx_fixup_deww(codec);
	snd_hda_codec_set_pincfg(codec, 0x13, 0x90A60160);
}

/* Both */
static void stac92hd73xx_fixup_deww_m6_both(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	stac92hd73xx_fixup_deww(codec);
	snd_hda_codec_set_pincfg(codec, 0x0b, 0x90A70170);
	snd_hda_codec_set_pincfg(codec, 0x13, 0x90A60160);
}

static void stac92hd73xx_fixup_awienwawe_m17x(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	snd_hda_appwy_pincfgs(codec, awienwawe_m17x_pin_configs);
	spec->eapd_switch = 0;
}

static void stac92hd73xx_fixup_no_jd(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		codec->no_jack_detect = 1;
}


static void stac92hd73xx_disabwe_automute(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	spec->gen.suppwess_auto_mute = 1;
}

static const stwuct hda_fixup stac92hd73xx_fixups[] = {
	[STAC_92HD73XX_WEF] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_wef,
	},
	[STAC_DEWW_M6_AMIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_deww_m6_amic,
	},
	[STAC_DEWW_M6_DMIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_deww_m6_dmic,
	},
	[STAC_DEWW_M6_BOTH] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_deww_m6_both,
	},
	[STAC_DEWW_EQ]	= {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_deww_eq,
	},
	[STAC_AWIENWAWE_M17X] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_awienwawe_m17x,
	},
	[STAC_EWO_VUPOINT_15MX] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_disabwe_automute,
	},
	[STAC_92HD73XX_INTEW] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_dg45id_pin_configs,
	},
	[STAC_92HD73XX_NO_JD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_no_jd,
	},
	[STAC_92HD89XX_HP_FWONT_JACK] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac92hd89xx_hp_fwont_jack_pin_configs,
	},
	[STAC_92HD89XX_HP_Z1_G2_WIGHT_MIC_JACK] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac92hd89xx_hp_z1_g2_wight_mic_jack_pin_configs,
	},
	[STAC_92HD73XX_ASUS_MOBO] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* enabwe 5.1 and SPDIF out */
			{ 0x0c, 0x01014411 },
			{ 0x0d, 0x01014410 },
			{ 0x0e, 0x01014412 },
			{ 0x22, 0x014b1180 },
			{ }
		}
	},
};

static const stwuct hda_modew_fixup stac92hd73xx_modews[] = {
	{ .id = STAC_92HD73XX_NO_JD, .name = "no-jd" },
	{ .id = STAC_92HD73XX_WEF, .name = "wef" },
	{ .id = STAC_92HD73XX_INTEW, .name = "intew" },
	{ .id = STAC_DEWW_M6_AMIC, .name = "deww-m6-amic" },
	{ .id = STAC_DEWW_M6_DMIC, .name = "deww-m6-dmic" },
	{ .id = STAC_DEWW_M6_BOTH, .name = "deww-m6" },
	{ .id = STAC_DEWW_EQ, .name = "deww-eq" },
	{ .id = STAC_AWIENWAWE_M17X, .name = "awienwawe" },
	{ .id = STAC_EWO_VUPOINT_15MX, .name = "ewo-vupoint-15mx" },
	{ .id = STAC_92HD73XX_ASUS_MOBO, .name = "asus-mobo" },
	{}
};

static const stwuct snd_pci_quiwk stac92hd73xx_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
				"DFI WanPawty", STAC_92HD73XX_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
				"DFI WanPawty", STAC_92HD73XX_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5001,
				"Intew DP45SG", STAC_92HD73XX_INTEW),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5002,
				"Intew DG45ID", STAC_92HD73XX_INTEW),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5003,
				"Intew DG45FC", STAC_92HD73XX_INTEW),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0254,
				"Deww Studio 1535", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0255,
				"unknown Deww", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0256,
				"unknown Deww", STAC_DEWW_M6_BOTH),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0257,
				"unknown Deww", STAC_DEWW_M6_BOTH),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x025e,
				"unknown Deww", STAC_DEWW_M6_AMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x025f,
				"unknown Deww", STAC_DEWW_M6_AMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0271,
				"unknown Deww", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0272,
				"unknown Deww", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x029f,
				"Deww Studio 1537", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02a0,
				"Deww Studio 17", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02be,
				"Deww Studio 1555", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02bd,
				"Deww Studio 1557", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02fe,
				"Deww Studio XPS 1645", STAC_DEWW_M6_DMIC),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0413,
				"Deww Studio 1558", STAC_DEWW_M6_DMIC),
	/* codec SSID matching */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02a1,
		      "Awienwawe M17x", STAC_AWIENWAWE_M17X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x043a,
		      "Awienwawe M17x", STAC_AWIENWAWE_M17X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0490,
		      "Awienwawe M17x W3", STAC_DEWW_EQ),
	SND_PCI_QUIWK(0x1059, 0x1011,
		      "EWO VuPoint 15MX", STAC_EWO_VUPOINT_15MX),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1927,
				"HP Z1 G2", STAC_92HD89XX_HP_Z1_G2_WIGHT_MIC_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2b17,
				"unknown HP", STAC_92HD89XX_HP_FWONT_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_ASUSTEK, 0x83f8, "ASUS AT4NM10",
		      STAC_92HD73XX_ASUS_MOBO),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef92hd83xxx_pin_configs[] = {
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x02211010 },
	{ 0x0c, 0x02a19020 },
	{ 0x0d, 0x02170130 },
	{ 0x0e, 0x01014050 },
	{ 0x0f, 0x01819040 },
	{ 0x10, 0x01014020 },
	{ 0x11, 0x90a3014e },
	{ 0x1f, 0x01451160 },
	{ 0x20, 0x98560170 },
	{}
};

static const stwuct hda_pintbw deww_s14_pin_configs[] = {
	{ 0x0a, 0x0221403f },
	{ 0x0b, 0x0221101f },
	{ 0x0c, 0x02a19020 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x40f000f0 },
	{ 0x0f, 0x40f000f0 },
	{ 0x10, 0x40f000f0 },
	{ 0x11, 0x90a60160 },
	{ 0x1f, 0x40f000f0 },
	{ 0x20, 0x40f000f0 },
	{}
};

static const stwuct hda_pintbw deww_vostwo_3500_pin_configs[] = {
	{ 0x0a, 0x02a11020 },
	{ 0x0b, 0x0221101f },
	{ 0x0c, 0x400000f0 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x400000f1 },
	{ 0x0f, 0x400000f2 },
	{ 0x10, 0x400000f3 },
	{ 0x11, 0x90a60160 },
	{ 0x1f, 0x400000f4 },
	{ 0x20, 0x400000f5 },
	{}
};

static const stwuct hda_pintbw hp_dv7_4000_pin_configs[] = {
	{ 0x0a, 0x03a12050 },
	{ 0x0b, 0x0321201f },
	{ 0x0c, 0x40f000f0 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x40f000f0 },
	{ 0x0f, 0x40f000f0 },
	{ 0x10, 0x90170110 },
	{ 0x11, 0xd5a30140 },
	{ 0x1f, 0x40f000f0 },
	{ 0x20, 0x40f000f0 },
	{}
};

static const stwuct hda_pintbw hp_zephyw_pin_configs[] = {
	{ 0x0a, 0x01813050 },
	{ 0x0b, 0x0421201f },
	{ 0x0c, 0x04a1205e },
	{ 0x0d, 0x96130310 },
	{ 0x0e, 0x96130310 },
	{ 0x0f, 0x0101401f },
	{ 0x10, 0x1111611f },
	{ 0x11, 0xd5a30130 },
	{}
};

static const stwuct hda_pintbw hp_cNB11_intquad_pin_configs[] = {
	{ 0x0a, 0x40f000f0 },
	{ 0x0b, 0x0221101f },
	{ 0x0c, 0x02a11020 },
	{ 0x0d, 0x92170110 },
	{ 0x0e, 0x40f000f0 },
	{ 0x0f, 0x92170110 },
	{ 0x10, 0x40f000f0 },
	{ 0x11, 0xd5a30130 },
	{ 0x1f, 0x40f000f0 },
	{ 0x20, 0x40f000f0 },
	{}
};

static void stac92hd83xxx_fixup_hp(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	if (hp_bnb2011_with_dock(codec)) {
		snd_hda_codec_set_pincfg(codec, 0xa, 0x2101201f);
		snd_hda_codec_set_pincfg(codec, 0xf, 0x2181205e);
	}

	if (find_mute_wed_cfg(codec, spec->defauwt_powawity))
		codec_dbg(codec, "mute WED gpio %d powawity %d\n",
				spec->gpio_wed,
				spec->gpio_wed_powawity);

	/* awwow auto-switching of dock wine-in */
	spec->gen.wine_in_auto_switch = twue;
}

static void stac92hd83xxx_fixup_hp_zephyw(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	snd_hda_appwy_pincfgs(codec, hp_zephyw_pin_configs);
	snd_hda_add_vewbs(codec, stac92hd83xxx_hp_zephyw_init);
}

static void stac92hd83xxx_fixup_hp_wed(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		spec->defauwt_powawity = 0;
}

static void stac92hd83xxx_fixup_hp_inv_wed(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		spec->defauwt_powawity = 1;
}

static void stac92hd83xxx_fixup_hp_mic_wed(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->mic_mute_wed_gpio = 0x08; /* GPIO3 */
#ifdef CONFIG_PM
		/* wesetting contwowwew cweaws GPIO, so we need to keep on */
		codec->cowe.powew_caps &= ~AC_PWWST_CWKSTOP;
#endif
	}
}

static void stac92hd83xxx_fixup_hp_wed_gpio10(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->gpio_wed = 0x10; /* GPIO4 */
		spec->defauwt_powawity = 0;
	}
}

static void stac92hd83xxx_fixup_headset_jack(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		spec->headset_jack = 1;
}

static void stac92hd83xxx_fixup_gpio10_eapd(stwuct hda_codec *codec,
					    const stwuct hda_fixup *fix,
					    int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;
	spec->eapd_mask = spec->gpio_mask = spec->gpio_diw =
		spec->gpio_data = 0x10;
	spec->eapd_switch = 0;
}

static void hp_envy_ts_fixup_dac_bind(stwuct hda_codec *codec,
					    const stwuct hda_fixup *fix,
					    int action)
{
	stwuct sigmatew_spec *spec = codec->spec;
	static const hda_nid_t pwefewwed_paiws[] = {
		0xd, 0x13,
		0
	};

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	spec->gen.pwefewwed_dacs = pwefewwed_paiws;
}

static const stwuct hda_vewb hp_bnb13_eq_vewbs[] = {
	/* 44.1KHz base */
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x68 },
	{ 0x22, 0x7A8, 0x17 },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x68 },
	{ 0x22, 0x7AB, 0x17 },
	{ 0x22, 0x7AC, 0x00 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x83 },
	{ 0x22, 0x7A7, 0x2F },
	{ 0x22, 0x7A8, 0xD1 },
	{ 0x22, 0x7A9, 0x83 },
	{ 0x22, 0x7AA, 0x2F },
	{ 0x22, 0x7AB, 0xD1 },
	{ 0x22, 0x7AC, 0x01 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x68 },
	{ 0x22, 0x7A8, 0x17 },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x68 },
	{ 0x22, 0x7AB, 0x17 },
	{ 0x22, 0x7AC, 0x02 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x7C },
	{ 0x22, 0x7A7, 0xC6 },
	{ 0x22, 0x7A8, 0x0C },
	{ 0x22, 0x7A9, 0x7C },
	{ 0x22, 0x7AA, 0xC6 },
	{ 0x22, 0x7AB, 0x0C },
	{ 0x22, 0x7AC, 0x03 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC3 },
	{ 0x22, 0x7A7, 0x25 },
	{ 0x22, 0x7A8, 0xAF },
	{ 0x22, 0x7A9, 0xC3 },
	{ 0x22, 0x7AA, 0x25 },
	{ 0x22, 0x7AB, 0xAF },
	{ 0x22, 0x7AC, 0x04 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x85 },
	{ 0x22, 0x7A8, 0x73 },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x85 },
	{ 0x22, 0x7AB, 0x73 },
	{ 0x22, 0x7AC, 0x05 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x85 },
	{ 0x22, 0x7A7, 0x39 },
	{ 0x22, 0x7A8, 0xC7 },
	{ 0x22, 0x7A9, 0x85 },
	{ 0x22, 0x7AA, 0x39 },
	{ 0x22, 0x7AB, 0xC7 },
	{ 0x22, 0x7AC, 0x06 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3C },
	{ 0x22, 0x7A7, 0x90 },
	{ 0x22, 0x7A8, 0xB0 },
	{ 0x22, 0x7A9, 0x3C },
	{ 0x22, 0x7AA, 0x90 },
	{ 0x22, 0x7AB, 0xB0 },
	{ 0x22, 0x7AC, 0x07 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x7A },
	{ 0x22, 0x7A7, 0xC6 },
	{ 0x22, 0x7A8, 0x39 },
	{ 0x22, 0x7A9, 0x7A },
	{ 0x22, 0x7AA, 0xC6 },
	{ 0x22, 0x7AB, 0x39 },
	{ 0x22, 0x7AC, 0x08 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC4 },
	{ 0x22, 0x7A7, 0xE9 },
	{ 0x22, 0x7A8, 0xDC },
	{ 0x22, 0x7A9, 0xC4 },
	{ 0x22, 0x7AA, 0xE9 },
	{ 0x22, 0x7AB, 0xDC },
	{ 0x22, 0x7AC, 0x09 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3D },
	{ 0x22, 0x7A7, 0xE1 },
	{ 0x22, 0x7A8, 0x0D },
	{ 0x22, 0x7A9, 0x3D },
	{ 0x22, 0x7AA, 0xE1 },
	{ 0x22, 0x7AB, 0x0D },
	{ 0x22, 0x7AC, 0x0A },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x89 },
	{ 0x22, 0x7A7, 0xB6 },
	{ 0x22, 0x7A8, 0xEB },
	{ 0x22, 0x7A9, 0x89 },
	{ 0x22, 0x7AA, 0xB6 },
	{ 0x22, 0x7AB, 0xEB },
	{ 0x22, 0x7AC, 0x0B },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x39 },
	{ 0x22, 0x7A7, 0x9D },
	{ 0x22, 0x7A8, 0xFE },
	{ 0x22, 0x7A9, 0x39 },
	{ 0x22, 0x7AA, 0x9D },
	{ 0x22, 0x7AB, 0xFE },
	{ 0x22, 0x7AC, 0x0C },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x76 },
	{ 0x22, 0x7A7, 0x49 },
	{ 0x22, 0x7A8, 0x15 },
	{ 0x22, 0x7A9, 0x76 },
	{ 0x22, 0x7AA, 0x49 },
	{ 0x22, 0x7AB, 0x15 },
	{ 0x22, 0x7AC, 0x0D },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC8 },
	{ 0x22, 0x7A7, 0x80 },
	{ 0x22, 0x7A8, 0xF5 },
	{ 0x22, 0x7A9, 0xC8 },
	{ 0x22, 0x7AA, 0x80 },
	{ 0x22, 0x7AB, 0xF5 },
	{ 0x22, 0x7AC, 0x0E },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x0F },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x90 },
	{ 0x22, 0x7A7, 0x68 },
	{ 0x22, 0x7A8, 0xF1 },
	{ 0x22, 0x7A9, 0x90 },
	{ 0x22, 0x7AA, 0x68 },
	{ 0x22, 0x7AB, 0xF1 },
	{ 0x22, 0x7AC, 0x10 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x34 },
	{ 0x22, 0x7A7, 0x47 },
	{ 0x22, 0x7A8, 0x6C },
	{ 0x22, 0x7A9, 0x34 },
	{ 0x22, 0x7AA, 0x47 },
	{ 0x22, 0x7AB, 0x6C },
	{ 0x22, 0x7AC, 0x11 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x6F },
	{ 0x22, 0x7A7, 0x97 },
	{ 0x22, 0x7A8, 0x0F },
	{ 0x22, 0x7A9, 0x6F },
	{ 0x22, 0x7AA, 0x97 },
	{ 0x22, 0x7AB, 0x0F },
	{ 0x22, 0x7AC, 0x12 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xCB },
	{ 0x22, 0x7A7, 0xB8 },
	{ 0x22, 0x7A8, 0x94 },
	{ 0x22, 0x7A9, 0xCB },
	{ 0x22, 0x7AA, 0xB8 },
	{ 0x22, 0x7AB, 0x94 },
	{ 0x22, 0x7AC, 0x13 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x14 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x95 },
	{ 0x22, 0x7A7, 0x76 },
	{ 0x22, 0x7A8, 0x5B },
	{ 0x22, 0x7A9, 0x95 },
	{ 0x22, 0x7AA, 0x76 },
	{ 0x22, 0x7AB, 0x5B },
	{ 0x22, 0x7AC, 0x15 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x31 },
	{ 0x22, 0x7A7, 0xAC },
	{ 0x22, 0x7A8, 0x31 },
	{ 0x22, 0x7A9, 0x31 },
	{ 0x22, 0x7AA, 0xAC },
	{ 0x22, 0x7AB, 0x31 },
	{ 0x22, 0x7AC, 0x16 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x6A },
	{ 0x22, 0x7A7, 0x89 },
	{ 0x22, 0x7A8, 0xA5 },
	{ 0x22, 0x7A9, 0x6A },
	{ 0x22, 0x7AA, 0x89 },
	{ 0x22, 0x7AB, 0xA5 },
	{ 0x22, 0x7AC, 0x17 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xCE },
	{ 0x22, 0x7A7, 0x53 },
	{ 0x22, 0x7A8, 0xCF },
	{ 0x22, 0x7A9, 0xCE },
	{ 0x22, 0x7AA, 0x53 },
	{ 0x22, 0x7AB, 0xCF },
	{ 0x22, 0x7AC, 0x18 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x19 },
	{ 0x22, 0x7AD, 0x80 },
	/* 48KHz base */
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x88 },
	{ 0x22, 0x7A8, 0xDC },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x88 },
	{ 0x22, 0x7AB, 0xDC },
	{ 0x22, 0x7AC, 0x1A },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x82 },
	{ 0x22, 0x7A7, 0xEE },
	{ 0x22, 0x7A8, 0x46 },
	{ 0x22, 0x7A9, 0x82 },
	{ 0x22, 0x7AA, 0xEE },
	{ 0x22, 0x7AB, 0x46 },
	{ 0x22, 0x7AC, 0x1B },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x88 },
	{ 0x22, 0x7A8, 0xDC },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x88 },
	{ 0x22, 0x7AB, 0xDC },
	{ 0x22, 0x7AC, 0x1C },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x7D },
	{ 0x22, 0x7A7, 0x09 },
	{ 0x22, 0x7A8, 0x28 },
	{ 0x22, 0x7A9, 0x7D },
	{ 0x22, 0x7AA, 0x09 },
	{ 0x22, 0x7AB, 0x28 },
	{ 0x22, 0x7AC, 0x1D },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC2 },
	{ 0x22, 0x7A7, 0xE5 },
	{ 0x22, 0x7A8, 0xB4 },
	{ 0x22, 0x7A9, 0xC2 },
	{ 0x22, 0x7AA, 0xE5 },
	{ 0x22, 0x7AB, 0xB4 },
	{ 0x22, 0x7AC, 0x1E },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0xA3 },
	{ 0x22, 0x7A8, 0x1F },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0xA3 },
	{ 0x22, 0x7AB, 0x1F },
	{ 0x22, 0x7AC, 0x1F },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x84 },
	{ 0x22, 0x7A7, 0xCA },
	{ 0x22, 0x7A8, 0xF1 },
	{ 0x22, 0x7A9, 0x84 },
	{ 0x22, 0x7AA, 0xCA },
	{ 0x22, 0x7AB, 0xF1 },
	{ 0x22, 0x7AC, 0x20 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3C },
	{ 0x22, 0x7A7, 0xD5 },
	{ 0x22, 0x7A8, 0x9C },
	{ 0x22, 0x7A9, 0x3C },
	{ 0x22, 0x7AA, 0xD5 },
	{ 0x22, 0x7AB, 0x9C },
	{ 0x22, 0x7AC, 0x21 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x7B },
	{ 0x22, 0x7A7, 0x35 },
	{ 0x22, 0x7A8, 0x0F },
	{ 0x22, 0x7A9, 0x7B },
	{ 0x22, 0x7AA, 0x35 },
	{ 0x22, 0x7AB, 0x0F },
	{ 0x22, 0x7AC, 0x22 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC4 },
	{ 0x22, 0x7A7, 0x87 },
	{ 0x22, 0x7A8, 0x45 },
	{ 0x22, 0x7A9, 0xC4 },
	{ 0x22, 0x7AA, 0x87 },
	{ 0x22, 0x7AB, 0x45 },
	{ 0x22, 0x7AC, 0x23 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3E },
	{ 0x22, 0x7A7, 0x0A },
	{ 0x22, 0x7A8, 0x78 },
	{ 0x22, 0x7A9, 0x3E },
	{ 0x22, 0x7AA, 0x0A },
	{ 0x22, 0x7AB, 0x78 },
	{ 0x22, 0x7AC, 0x24 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x88 },
	{ 0x22, 0x7A7, 0xE2 },
	{ 0x22, 0x7A8, 0x05 },
	{ 0x22, 0x7A9, 0x88 },
	{ 0x22, 0x7AA, 0xE2 },
	{ 0x22, 0x7AB, 0x05 },
	{ 0x22, 0x7AC, 0x25 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x3A },
	{ 0x22, 0x7A7, 0x1A },
	{ 0x22, 0x7A8, 0xA3 },
	{ 0x22, 0x7A9, 0x3A },
	{ 0x22, 0x7AA, 0x1A },
	{ 0x22, 0x7AB, 0xA3 },
	{ 0x22, 0x7AC, 0x26 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x77 },
	{ 0x22, 0x7A7, 0x1D },
	{ 0x22, 0x7A8, 0xFB },
	{ 0x22, 0x7A9, 0x77 },
	{ 0x22, 0x7AA, 0x1D },
	{ 0x22, 0x7AB, 0xFB },
	{ 0x22, 0x7AC, 0x27 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xC7 },
	{ 0x22, 0x7A7, 0xDA },
	{ 0x22, 0x7A8, 0xE5 },
	{ 0x22, 0x7A9, 0xC7 },
	{ 0x22, 0x7AA, 0xDA },
	{ 0x22, 0x7AB, 0xE5 },
	{ 0x22, 0x7AC, 0x28 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x29 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x8E },
	{ 0x22, 0x7A7, 0xD7 },
	{ 0x22, 0x7A8, 0x22 },
	{ 0x22, 0x7A9, 0x8E },
	{ 0x22, 0x7AA, 0xD7 },
	{ 0x22, 0x7AB, 0x22 },
	{ 0x22, 0x7AC, 0x2A },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x35 },
	{ 0x22, 0x7A7, 0x26 },
	{ 0x22, 0x7A8, 0xC6 },
	{ 0x22, 0x7A9, 0x35 },
	{ 0x22, 0x7AA, 0x26 },
	{ 0x22, 0x7AB, 0xC6 },
	{ 0x22, 0x7AC, 0x2B },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x71 },
	{ 0x22, 0x7A7, 0x28 },
	{ 0x22, 0x7A8, 0xDE },
	{ 0x22, 0x7A9, 0x71 },
	{ 0x22, 0x7AA, 0x28 },
	{ 0x22, 0x7AB, 0xDE },
	{ 0x22, 0x7AC, 0x2C },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xCA },
	{ 0x22, 0x7A7, 0xD9 },
	{ 0x22, 0x7A8, 0x3A },
	{ 0x22, 0x7A9, 0xCA },
	{ 0x22, 0x7AA, 0xD9 },
	{ 0x22, 0x7AB, 0x3A },
	{ 0x22, 0x7AC, 0x2D },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x2E },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x93 },
	{ 0x22, 0x7A7, 0x5E },
	{ 0x22, 0x7A8, 0xD8 },
	{ 0x22, 0x7A9, 0x93 },
	{ 0x22, 0x7AA, 0x5E },
	{ 0x22, 0x7AB, 0xD8 },
	{ 0x22, 0x7AC, 0x2F },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x32 },
	{ 0x22, 0x7A7, 0xB7 },
	{ 0x22, 0x7A8, 0xB1 },
	{ 0x22, 0x7A9, 0x32 },
	{ 0x22, 0x7AA, 0xB7 },
	{ 0x22, 0x7AB, 0xB1 },
	{ 0x22, 0x7AC, 0x30 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x6C },
	{ 0x22, 0x7A7, 0xA1 },
	{ 0x22, 0x7A8, 0x28 },
	{ 0x22, 0x7A9, 0x6C },
	{ 0x22, 0x7AA, 0xA1 },
	{ 0x22, 0x7AB, 0x28 },
	{ 0x22, 0x7AC, 0x31 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0xCD },
	{ 0x22, 0x7A7, 0x48 },
	{ 0x22, 0x7A8, 0x4F },
	{ 0x22, 0x7A9, 0xCD },
	{ 0x22, 0x7AA, 0x48 },
	{ 0x22, 0x7AB, 0x4F },
	{ 0x22, 0x7AC, 0x32 },
	{ 0x22, 0x7AD, 0x80 },
	{ 0x22, 0x7A6, 0x40 },
	{ 0x22, 0x7A7, 0x00 },
	{ 0x22, 0x7A8, 0x00 },
	{ 0x22, 0x7A9, 0x40 },
	{ 0x22, 0x7AA, 0x00 },
	{ 0x22, 0x7AB, 0x00 },
	{ 0x22, 0x7AC, 0x33 },
	{ 0x22, 0x7AD, 0x80 },
	/* common */
	{ 0x22, 0x782, 0xC1 },
	{ 0x22, 0x771, 0x2C },
	{ 0x22, 0x772, 0x2C },
	{ 0x22, 0x788, 0x04 },
	{ 0x01, 0x7B0, 0x08 },
	{}
};

static const stwuct hda_fixup stac92hd83xxx_fixups[] = {
	[STAC_92HD83XXX_WEF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = wef92hd83xxx_pin_configs,
	},
	[STAC_92HD83XXX_PWW_WEF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = wef92hd83xxx_pin_configs,
	},
	[STAC_DEWW_S14] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_s14_pin_configs,
	},
	[STAC_DEWW_VOSTWO_3500] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_vostwo_3500_pin_configs,
	},
	[STAC_92HD83XXX_HP_cNB11_INTQUAD] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = hp_cNB11_intquad_pin_configs,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_92HD83XXX_HP] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp,
	},
	[STAC_HP_DV7_4000] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = hp_dv7_4000_pin_configs,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_HP_ZEPHYW] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_zephyw,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_92HD83XXX_HP_WED] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_wed,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_92HD83XXX_HP_INV_WED] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_inv_wed,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_92HD83XXX_HP_MIC_WED] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_mic_wed,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_HP_WED_GPIO10] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_wed_gpio10,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP,
	},
	[STAC_92HD83XXX_HEADSET_JACK] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_headset_jack,
	},
	[STAC_HP_ENVY_BASS] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x0f, 0x90170111 },
			{}
		},
	},
	[STAC_HP_BNB13_EQ] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = hp_bnb13_eq_vewbs,
		.chained = twue,
		.chain_id = STAC_92HD83XXX_HP_MIC_WED,
	},
	[STAC_HP_ENVY_TS_BASS] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x10, 0x92170111 },
			{}
		},
	},
	[STAC_HP_ENVY_TS_DAC_BIND] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = hp_envy_ts_fixup_dac_bind,
		.chained = twue,
		.chain_id = STAC_HP_ENVY_TS_BASS,
	},
	[STAC_92HD83XXX_GPIO10_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_gpio10_eapd,
	},
};

static const stwuct hda_modew_fixup stac92hd83xxx_modews[] = {
	{ .id = STAC_92HD83XXX_WEF, .name = "wef" },
	{ .id = STAC_92HD83XXX_PWW_WEF, .name = "mic-wef" },
	{ .id = STAC_DEWW_S14, .name = "deww-s14" },
	{ .id = STAC_DEWW_VOSTWO_3500, .name = "deww-vostwo-3500" },
	{ .id = STAC_92HD83XXX_HP_cNB11_INTQUAD, .name = "hp_cNB11_intquad" },
	{ .id = STAC_HP_DV7_4000, .name = "hp-dv7-4000" },
	{ .id = STAC_HP_ZEPHYW, .name = "hp-zephyw" },
	{ .id = STAC_92HD83XXX_HP_WED, .name = "hp-wed" },
	{ .id = STAC_92HD83XXX_HP_INV_WED, .name = "hp-inv-wed" },
	{ .id = STAC_92HD83XXX_HP_MIC_WED, .name = "hp-mic-wed" },
	{ .id = STAC_92HD83XXX_HEADSET_JACK, .name = "headset-jack" },
	{ .id = STAC_HP_ENVY_BASS, .name = "hp-envy-bass" },
	{ .id = STAC_HP_BNB13_EQ, .name = "hp-bnb13-eq" },
	{ .id = STAC_HP_ENVY_TS_BASS, .name = "hp-envy-ts-bass" },
	{}
};

static const stwuct snd_pci_quiwk stac92hd83xxx_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_92HD83XXX_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_92HD83XXX_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02ba,
		      "unknown Deww", STAC_DEWW_S14),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0532,
		      "Deww Watitude E6230", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0533,
		      "Deww Watitude E6330", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0534,
		      "Deww Watitude E6430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0535,
		      "Deww Watitude E6530", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x053c,
		      "Deww Watitude E5430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x053d,
		      "Deww Watitude E5530", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0549,
		      "Deww Watitude E5430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x057d,
		      "Deww Watitude E6430s", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0584,
		      "Deww Watitude E6430U", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x1028,
		      "Deww Vostwo 3500", STAC_DEWW_VOSTWO_3500),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1656,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1657,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1658,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1659,
			  "HP Paviwion dv7", STAC_HP_DV7_4000),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x165A,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x165B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1888,
			  "HP Envy Spectwe", STAC_HP_ENVY_BASS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1899,
			  "HP Fowio 13", STAC_HP_WED_GPIO10),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x18df,
			  "HP Fowio", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x18F8,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1909,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x190A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x190e,
			  "HP ENVY TS", STAC_HP_ENVY_TS_BASS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1967,
			  "HP ENVY TS", STAC_HP_ENVY_TS_DAC_BIND),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1940,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1941,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1942,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1943,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1944,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1945,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1946,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1948,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1949,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x194A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x194B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x194C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x194E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x194F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1950,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1951,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x195A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x195B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x195C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1991,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2103,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2104,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2105,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2106,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2107,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2108,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2109,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x210A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x210B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x211C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x211D,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x211E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x211F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2120,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2121,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2122,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2123,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x213E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x213F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x2140,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x21B2,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x21B3,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x21B5,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x21B6,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xff00, 0x1900,
			  "HP", STAC_92HD83XXX_HP_MIC_WED),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xff00, 0x2000,
			  "HP", STAC_92HD83XXX_HP_MIC_WED),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xff00, 0x2100,
			  "HP", STAC_92HD83XXX_HP_MIC_WED),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3388,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3389,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x355B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x355C,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x355D,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x355E,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x355F,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3560,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x358B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x358C,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x358D,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3591,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3592,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3593,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3561,
			  "HP", STAC_HP_ZEPHYW),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3660,
			  "HP Mini", STAC_92HD83XXX_HP_WED),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x144E,
			  "HP Paviwion dv5", STAC_92HD83XXX_HP_INV_WED),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x148a,
		      "HP Mini", STAC_92HD83XXX_HP_WED),
	SND_PCI_QUIWK_VENDOW(PCI_VENDOW_ID_HP, "HP", STAC_92HD83XXX_HP),
	/* match both fow 0xfa91 and 0xfa93 */
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_TOSHIBA, 0xfffd, 0xfa91,
		      "Toshiba Satewwite S50D", STAC_92HD83XXX_GPIO10_EAPD),
	{} /* tewminatow */
};

/* HP dv7 bass switch - GPIO5 */
#define stac_hp_bass_gpio_info	snd_ctw_boowean_mono_info
static int stac_hp_bass_gpio_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	ucontwow->vawue.integew.vawue[0] = !!(spec->gpio_data & 0x20);
	wetuwn 0;
}

static int stac_hp_bass_gpio_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct sigmatew_spec *spec = codec->spec;
	unsigned int gpio_data;

	gpio_data = (spec->gpio_data & ~0x20) |
		(ucontwow->vawue.integew.vawue[0] ? 0x20 : 0);
	if (gpio_data == spec->gpio_data)
		wetuwn 0;
	spec->gpio_data = gpio_data;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_diw, spec->gpio_data);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new stac_hp_bass_sw_ctww = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = stac_hp_bass_gpio_info,
	.get = stac_hp_bass_gpio_get,
	.put = stac_hp_bass_gpio_put,
};

static int stac_add_hp_bass_switch(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctw(&spec->gen, "Bass Speakew Pwayback Switch",
				  &stac_hp_bass_sw_ctww))
		wetuwn -ENOMEM;

	spec->gpio_mask |= 0x20;
	spec->gpio_diw |= 0x20;
	spec->gpio_data |= 0x20;
	wetuwn 0;
}

static const stwuct hda_pintbw wef92hd71bxx_pin_configs[] = {
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x02a19040 },
	{ 0x0c, 0x01a19020 },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x0181302e },
	{ 0x0f, 0x01014010 },
	{ 0x14, 0x01019020 },
	{ 0x18, 0x90a000f0 },
	{ 0x19, 0x90a000f0 },
	{ 0x1e, 0x01452050 },
	{ 0x1f, 0x01452050 },
	{}
};

static const stwuct hda_pintbw deww_m4_1_pin_configs[] = {
	{ 0x0a, 0x0421101f },
	{ 0x0b, 0x04a11221 },
	{ 0x0c, 0x40f000f0 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x23a1902e },
	{ 0x0f, 0x23014250 },
	{ 0x14, 0x40f000f0 },
	{ 0x18, 0x90a000f0 },
	{ 0x19, 0x40f000f0 },
	{ 0x1e, 0x4f0000f0 },
	{ 0x1f, 0x4f0000f0 },
	{}
};

static const stwuct hda_pintbw deww_m4_2_pin_configs[] = {
	{ 0x0a, 0x0421101f },
	{ 0x0b, 0x04a11221 },
	{ 0x0c, 0x90a70330 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x23a1902e },
	{ 0x0f, 0x23014250 },
	{ 0x14, 0x40f000f0 },
	{ 0x18, 0x40f000f0 },
	{ 0x19, 0x40f000f0 },
	{ 0x1e, 0x044413b0 },
	{ 0x1f, 0x044413b0 },
	{}
};

static const stwuct hda_pintbw deww_m4_3_pin_configs[] = {
	{ 0x0a, 0x0421101f },
	{ 0x0b, 0x04a11221 },
	{ 0x0c, 0x90a70330 },
	{ 0x0d, 0x90170110 },
	{ 0x0e, 0x40f000f0 },
	{ 0x0f, 0x40f000f0 },
	{ 0x14, 0x40f000f0 },
	{ 0x18, 0x90a000f0 },
	{ 0x19, 0x40f000f0 },
	{ 0x1e, 0x044413b0 },
	{ 0x1f, 0x044413b0 },
	{}
};

static void stac92hd71bxx_fixup_wef(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	snd_hda_appwy_pincfgs(codec, wef92hd71bxx_pin_configs);
	spec->gpio_mask = spec->gpio_diw = spec->gpio_data = 0;
}

static void stac92hd71bxx_fixup_hp_m4(stwuct hda_codec *codec,
				      const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;
	stwuct hda_jack_cawwback *jack;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	/* Enabwe VWEF powew saving on GPIO1 detect */
	snd_hda_codec_wwite_cache(codec, codec->cowe.afg, 0,
				  AC_VEWB_SET_GPIO_UNSOWICITED_WSP_MASK, 0x02);
	jack = snd_hda_jack_detect_enabwe_cawwback(codec, codec->cowe.afg,
						   stac_vwef_event);
	if (!IS_EWW(jack))
		jack->pwivate_data = 0x02;

	spec->gpio_mask |= 0x02;

	/* enabwe intewnaw micwophone */
	snd_hda_codec_set_pincfg(codec, 0x0e, 0x01813040);
}

static void stac92hd71bxx_fixup_hp_dv4(stwuct hda_codec *codec,
				       const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;
	spec->gpio_wed = 0x01;
}

static void stac92hd71bxx_fixup_hp_dv5(stwuct hda_codec *codec,
				       const stwuct hda_fixup *fix, int action)
{
	unsigned int cap;

	switch (action) {
	case HDA_FIXUP_ACT_PWE_PWOBE:
		snd_hda_codec_set_pincfg(codec, 0x0d, 0x90170010);
		bweak;

	case HDA_FIXUP_ACT_PWOBE:
		/* enabwe bass on HP dv7 */
		cap = snd_hda_pawam_wead(codec, 0x1, AC_PAW_GPIO_CAP);
		cap &= AC_GPIO_IO_COUNT;
		if (cap >= 6)
			stac_add_hp_bass_switch(codec);
		bweak;
	}
}

static void stac92hd71bxx_fixup_hp_hdx(stwuct hda_codec *codec,
				       const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;
	spec->gpio_wed = 0x08;
}

static boow is_hp_output(stwuct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pin_cfg = snd_hda_codec_get_pincfg(codec, pin);

	/* count wine-out, too, as BIOS sets often so */
	wetuwn get_defcfg_connect(pin_cfg) != AC_JACK_POWT_NONE &&
		(get_defcfg_device(pin_cfg) == AC_JACK_WINE_OUT ||
		 get_defcfg_device(pin_cfg) == AC_JACK_HP_OUT);
}

static void fixup_hp_headphone(stwuct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pin_cfg = snd_hda_codec_get_pincfg(codec, pin);

	/* It was changed in the BIOS to just satisfy MS DTM.
	 * Wets tuwn it back into fowwowew HP
	 */
	pin_cfg = (pin_cfg & (~AC_DEFCFG_DEVICE)) |
		(AC_JACK_HP_OUT << AC_DEFCFG_DEVICE_SHIFT);
	pin_cfg = (pin_cfg & (~(AC_DEFCFG_DEF_ASSOC | AC_DEFCFG_SEQUENCE))) |
		0x1f;
	snd_hda_codec_set_pincfg(codec, pin, pin_cfg);
}

static void stac92hd71bxx_fixup_hp(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	/* when both output A and F awe assigned, these awe supposedwy
	 * dock and buiwt-in headphones; fix both pin configs
	 */
	if (is_hp_output(codec, 0x0a) && is_hp_output(codec, 0x0f)) {
		fixup_hp_headphone(codec, 0x0a);
		fixup_hp_headphone(codec, 0x0f);
	}

	if (find_mute_wed_cfg(codec, 1))
		codec_dbg(codec, "mute WED gpio %d powawity %d\n",
				spec->gpio_wed,
				spec->gpio_wed_powawity);

}

static const stwuct hda_fixup stac92hd71bxx_fixups[] = {
	[STAC_92HD71BXX_WEF] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_wef,
	},
	[STAC_DEWW_M4_1] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_m4_1_pin_configs,
	},
	[STAC_DEWW_M4_2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_m4_2_pin_configs,
	},
	[STAC_DEWW_M4_3] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_m4_3_pin_configs,
	},
	[STAC_HP_M4] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_m4,
		.chained = twue,
		.chain_id = STAC_92HD71BXX_HP,
	},
	[STAC_HP_DV4] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_dv4,
		.chained = twue,
		.chain_id = STAC_HP_DV5,
	},
	[STAC_HP_DV5] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_dv5,
		.chained = twue,
		.chain_id = STAC_92HD71BXX_HP,
	},
	[STAC_HP_HDX] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_hdx,
		.chained = twue,
		.chain_id = STAC_92HD71BXX_HP,
	},
	[STAC_92HD71BXX_HP] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp,
	},
};

static const stwuct hda_modew_fixup stac92hd71bxx_modews[] = {
	{ .id = STAC_92HD71BXX_WEF, .name = "wef" },
	{ .id = STAC_DEWW_M4_1, .name = "deww-m4-1" },
	{ .id = STAC_DEWW_M4_2, .name = "deww-m4-2" },
	{ .id = STAC_DEWW_M4_3, .name = "deww-m4-3" },
	{ .id = STAC_HP_M4, .name = "hp-m4" },
	{ .id = STAC_HP_DV4, .name = "hp-dv4" },
	{ .id = STAC_HP_DV5, .name = "hp-dv5" },
	{ .id = STAC_HP_HDX, .name = "hp-hdx" },
	{ .id = STAC_HP_DV4, .name = "hp-dv4-1222nw" },
	{}
};

static const stwuct snd_pci_quiwk stac92hd71bxx_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_92HD71BXX_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_92HD71BXX_WEF),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x1720,
			  "HP", STAC_HP_DV5),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x3080,
		      "HP", STAC_HP_DV5),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x30f0,
		      "HP dv4-7", STAC_HP_DV4),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x3600,
		      "HP dv4-7", STAC_HP_DV5),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3610,
		      "HP HDX", STAC_HP_HDX),  /* HDX18 */
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x361a,
		      "HP mini 1000", STAC_HP_M4),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x361b,
		      "HP HDX", STAC_HP_HDX),  /* HDX16 */
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x3620,
		      "HP dv6", STAC_HP_DV5),
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x3061,
		      "HP dv6", STAC_HP_DV5), /* HP dv6-1110ax */
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x363e,
		      "HP DV6", STAC_HP_DV5),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_HP, 0xfff0, 0x7010,
		      "HP", STAC_HP_DV5),
	SND_PCI_QUIWK_VENDOW(PCI_VENDOW_ID_HP, "HP", STAC_92HD71BXX_HP),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0233,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0234,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0250,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x024f,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x024d,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0251,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0277,
				"unknown Deww", STAC_DEWW_M4_1),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0263,
				"unknown Deww", STAC_DEWW_M4_2),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0265,
				"unknown Deww", STAC_DEWW_M4_2),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0262,
				"unknown Deww", STAC_DEWW_M4_2),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0264,
				"unknown Deww", STAC_DEWW_M4_2),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x02aa,
				"unknown Deww", STAC_DEWW_M4_3),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef922x_pin_configs[] = {
	{ 0x0a, 0x01014010 },
	{ 0x0b, 0x01016011 },
	{ 0x0c, 0x01012012 },
	{ 0x0d, 0x0221401f },
	{ 0x0e, 0x01813122 },
	{ 0x0f, 0x01011014 },
	{ 0x10, 0x01441030 },
	{ 0x11, 0x01c41030 },
	{ 0x15, 0x40000100 },
	{ 0x1b, 0x40000100 },
	{}
};

/*
    STAC 922X pin configs fow
    102801A7
    102801AB
    102801A9
    102801D1
    102801D2
*/
static const stwuct hda_pintbw deww_922x_d81_pin_configs[] = {
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x01a19021 },
	{ 0x0c, 0x01111012 },
	{ 0x0d, 0x01114010 },
	{ 0x0e, 0x02a19020 },
	{ 0x0f, 0x01117011 },
	{ 0x10, 0x400001f0 },
	{ 0x11, 0x400001f1 },
	{ 0x15, 0x01813122 },
	{ 0x1b, 0x400001f2 },
	{}
};

/*
    STAC 922X pin configs fow
    102801AC
    102801D0
*/
static const stwuct hda_pintbw deww_922x_d82_pin_configs[] = {
	{ 0x0a, 0x02214030 },
	{ 0x0b, 0x01a19021 },
	{ 0x0c, 0x01111012 },
	{ 0x0d, 0x01114010 },
	{ 0x0e, 0x02a19020 },
	{ 0x0f, 0x01117011 },
	{ 0x10, 0x01451140 },
	{ 0x11, 0x400001f0 },
	{ 0x15, 0x01813122 },
	{ 0x1b, 0x400001f1 },
	{}
};

/*
    STAC 922X pin configs fow
    102801BF
*/
static const stwuct hda_pintbw deww_922x_m81_pin_configs[] = {
	{ 0x0a, 0x0321101f },
	{ 0x0b, 0x01112024 },
	{ 0x0c, 0x01111222 },
	{ 0x0d, 0x91174220 },
	{ 0x0e, 0x03a11050 },
	{ 0x0f, 0x01116221 },
	{ 0x10, 0x90a70330 },
	{ 0x11, 0x01452340 },
	{ 0x15, 0x40C003f1 },
	{ 0x1b, 0x405003f0 },
	{}
};

/*
    STAC 9221 A1 pin configs fow
    102801D7 (Deww XPS M1210)
*/
static const stwuct hda_pintbw deww_922x_m82_pin_configs[] = {
	{ 0x0a, 0x02211211 },
	{ 0x0b, 0x408103ff },
	{ 0x0c, 0x02a1123e },
	{ 0x0d, 0x90100310 },
	{ 0x0e, 0x408003f1 },
	{ 0x0f, 0x0221121f },
	{ 0x10, 0x03451340 },
	{ 0x11, 0x40c003f2 },
	{ 0x15, 0x508003f3 },
	{ 0x1b, 0x405003f4 },
	{}
};

static const stwuct hda_pintbw d945gtp3_pin_configs[] = {
	{ 0x0a, 0x0221401f },
	{ 0x0b, 0x01a19022 },
	{ 0x0c, 0x01813021 },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x40000100 },
	{ 0x0f, 0x40000100 },
	{ 0x10, 0x40000100 },
	{ 0x11, 0x40000100 },
	{ 0x15, 0x02a19120 },
	{ 0x1b, 0x40000100 },
	{}
};

static const stwuct hda_pintbw d945gtp5_pin_configs[] = {
	{ 0x0a, 0x0221401f },
	{ 0x0b, 0x01011012 },
	{ 0x0c, 0x01813024 },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x01a19021 },
	{ 0x0f, 0x01016011 },
	{ 0x10, 0x01452130 },
	{ 0x11, 0x40000100 },
	{ 0x15, 0x02a19320 },
	{ 0x1b, 0x40000100 },
	{}
};

static const stwuct hda_pintbw intew_mac_v1_pin_configs[] = {
	{ 0x0a, 0x0121e21f },
	{ 0x0b, 0x400000ff },
	{ 0x0c, 0x9017e110 },
	{ 0x0d, 0x400000fd },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x0181e020 },
	{ 0x10, 0x1145e030 },
	{ 0x11, 0x11c5e240 },
	{ 0x15, 0x400000fc },
	{ 0x1b, 0x400000fb },
	{}
};

static const stwuct hda_pintbw intew_mac_v2_pin_configs[] = {
	{ 0x0a, 0x0121e21f },
	{ 0x0b, 0x90a7012e },
	{ 0x0c, 0x9017e110 },
	{ 0x0d, 0x400000fd },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x0181e020 },
	{ 0x10, 0x1145e230 },
	{ 0x11, 0x500000fa },
	{ 0x15, 0x400000fc },
	{ 0x1b, 0x400000fb },
	{}
};

static const stwuct hda_pintbw intew_mac_v3_pin_configs[] = {
	{ 0x0a, 0x0121e21f },
	{ 0x0b, 0x90a7012e },
	{ 0x0c, 0x9017e110 },
	{ 0x0d, 0x400000fd },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x0181e020 },
	{ 0x10, 0x1145e230 },
	{ 0x11, 0x11c5e240 },
	{ 0x15, 0x400000fc },
	{ 0x1b, 0x400000fb },
	{}
};

static const stwuct hda_pintbw intew_mac_v4_pin_configs[] = {
	{ 0x0a, 0x0321e21f },
	{ 0x0b, 0x03a1e02e },
	{ 0x0c, 0x9017e110 },
	{ 0x0d, 0x9017e11f },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x0381e020 },
	{ 0x10, 0x1345e230 },
	{ 0x11, 0x13c5e240 },
	{ 0x15, 0x400000fc },
	{ 0x1b, 0x400000fb },
	{}
};

static const stwuct hda_pintbw intew_mac_v5_pin_configs[] = {
	{ 0x0a, 0x0321e21f },
	{ 0x0b, 0x03a1e02e },
	{ 0x0c, 0x9017e110 },
	{ 0x0d, 0x9017e11f },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x0381e020 },
	{ 0x10, 0x1345e230 },
	{ 0x11, 0x13c5e240 },
	{ 0x15, 0x400000fc },
	{ 0x1b, 0x400000fb },
	{}
};

static const stwuct hda_pintbw ecs202_pin_configs[] = {
	{ 0x0a, 0x0221401f },
	{ 0x0b, 0x02a19020 },
	{ 0x0c, 0x01a19020 },
	{ 0x0d, 0x01114010 },
	{ 0x0e, 0x408000f0 },
	{ 0x0f, 0x01813022 },
	{ 0x10, 0x074510a0 },
	{ 0x11, 0x40c400f1 },
	{ 0x15, 0x9037012e },
	{ 0x1b, 0x40e000f2 },
	{}
};

/* codec SSIDs fow Intew Mac shawing the same PCI SSID 8384:7680 */
static const stwuct snd_pci_quiwk stac922x_intew_mac_fixup_tbw[] = {
	SND_PCI_QUIWK(0x0000, 0x0100, "Mac Mini", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x0800, "Mac", STAC_INTEW_MAC_V1),
	SND_PCI_QUIWK(0x106b, 0x0600, "Mac", STAC_INTEW_MAC_V2),
	SND_PCI_QUIWK(0x106b, 0x0700, "Mac", STAC_INTEW_MAC_V2),
	SND_PCI_QUIWK(0x106b, 0x0e00, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x0f00, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x1600, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x1700, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x0200, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x1e00, "Mac", STAC_INTEW_MAC_V3),
	SND_PCI_QUIWK(0x106b, 0x1a00, "Mac", STAC_INTEW_MAC_V4),
	SND_PCI_QUIWK(0x106b, 0x0a00, "Mac", STAC_INTEW_MAC_V5),
	SND_PCI_QUIWK(0x106b, 0x2200, "Mac", STAC_INTEW_MAC_V5),
	{}
};

static const stwuct hda_fixup stac922x_fixups[];

/* wemap the fixup fwom codec SSID and appwy it */
static void stac922x_fixup_intew_mac_auto(stwuct hda_codec *codec,
					  const stwuct hda_fixup *fix,
					  int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;
	snd_hda_pick_fixup(codec, NUWW, stac922x_intew_mac_fixup_tbw,
			   stac922x_fixups);
	if (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		snd_hda_appwy_fixup(codec, action);
}

static void stac922x_fixup_intew_mac_gpio(stwuct hda_codec *codec,
					  const stwuct hda_fixup *fix,
					  int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->gpio_mask = spec->gpio_diw = 0x03;
		spec->gpio_data = 0x03;
	}
}

static const stwuct hda_fixup stac922x_fixups[] = {
	[STAC_D945_WEF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = wef922x_pin_configs,
	},
	[STAC_D945GTP3] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = d945gtp3_pin_configs,
	},
	[STAC_D945GTP5] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = d945gtp5_pin_configs,
	},
	[STAC_INTEW_MAC_AUTO] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac922x_fixup_intew_mac_auto,
	},
	[STAC_INTEW_MAC_V1] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_mac_v1_pin_configs,
		.chained = twue,
		.chain_id = STAC_922X_INTEW_MAC_GPIO,
	},
	[STAC_INTEW_MAC_V2] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_mac_v2_pin_configs,
		.chained = twue,
		.chain_id = STAC_922X_INTEW_MAC_GPIO,
	},
	[STAC_INTEW_MAC_V3] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_mac_v3_pin_configs,
		.chained = twue,
		.chain_id = STAC_922X_INTEW_MAC_GPIO,
	},
	[STAC_INTEW_MAC_V4] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_mac_v4_pin_configs,
		.chained = twue,
		.chain_id = STAC_922X_INTEW_MAC_GPIO,
	},
	[STAC_INTEW_MAC_V5] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = intew_mac_v5_pin_configs,
		.chained = twue,
		.chain_id = STAC_922X_INTEW_MAC_GPIO,
	},
	[STAC_922X_INTEW_MAC_GPIO] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac922x_fixup_intew_mac_gpio,
	},
	[STAC_ECS_202] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = ecs202_pin_configs,
	},
	[STAC_922X_DEWW_D81] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_922x_d81_pin_configs,
	},
	[STAC_922X_DEWW_D82] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_922x_d82_pin_configs,
	},
	[STAC_922X_DEWW_M81] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_922x_m81_pin_configs,
	},
	[STAC_922X_DEWW_M82] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_922x_m82_pin_configs,
	},
};

static const stwuct hda_modew_fixup stac922x_modews[] = {
	{ .id = STAC_D945_WEF, .name = "wef" },
	{ .id = STAC_D945GTP5, .name = "5stack" },
	{ .id = STAC_D945GTP3, .name = "3stack" },
	{ .id = STAC_INTEW_MAC_V1, .name = "intew-mac-v1" },
	{ .id = STAC_INTEW_MAC_V2, .name = "intew-mac-v2" },
	{ .id = STAC_INTEW_MAC_V3, .name = "intew-mac-v3" },
	{ .id = STAC_INTEW_MAC_V4, .name = "intew-mac-v4" },
	{ .id = STAC_INTEW_MAC_V5, .name = "intew-mac-v5" },
	{ .id = STAC_INTEW_MAC_AUTO, .name = "intew-mac-auto" },
	{ .id = STAC_ECS_202, .name = "ecs202" },
	{ .id = STAC_922X_DEWW_D81, .name = "deww-d81" },
	{ .id = STAC_922X_DEWW_D82, .name = "deww-d82" },
	{ .id = STAC_922X_DEWW_M81, .name = "deww-m81" },
	{ .id = STAC_922X_DEWW_M82, .name = "deww-m82" },
	/* fow backwawd compatibiwity */
	{ .id = STAC_INTEW_MAC_V3, .name = "macmini" },
	{ .id = STAC_INTEW_MAC_V5, .name = "macbook" },
	{ .id = STAC_INTEW_MAC_V3, .name = "macbook-pwo-v1" },
	{ .id = STAC_INTEW_MAC_V3, .name = "macbook-pwo" },
	{ .id = STAC_INTEW_MAC_V2, .name = "imac-intew" },
	{ .id = STAC_INTEW_MAC_V3, .name = "imac-intew-20" },
	{}
};

static const stwuct snd_pci_quiwk stac922x_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_D945_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_D945_WEF),
	/* Intew 945G based systems */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0101,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0202,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0606,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0601,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0111,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x1115,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x1116,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x1117,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x1118,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x1119,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x8826,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5049,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5055,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x5048,
		      "Intew D945G", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0110,
		      "Intew D945G", STAC_D945GTP3),
	/* Intew D945G 5-stack systems */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0404,
		      "Intew D945G", STAC_D945GTP5),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0303,
		      "Intew D945G", STAC_D945GTP5),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0013,
		      "Intew D945G", STAC_D945GTP5),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0417,
		      "Intew D945G", STAC_D945GTP5),
	/* Intew 945P based systems */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0b0b,
		      "Intew D945P", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0112,
		      "Intew D945P", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0d0d,
		      "Intew D945P", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0909,
		      "Intew D945P", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0505,
		      "Intew D945P", STAC_D945GTP3),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0707,
		      "Intew D945P", STAC_D945GTP5),
	/* othew intew */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x0204,
		      "Intew D945", STAC_D945_WEF),
	/* othew systems  */

	/* Appwe Intew Mac (Mac Mini, MacBook, MacBook Pwo...) */
	SND_PCI_QUIWK(0x8384, 0x7680, "Mac", STAC_INTEW_MAC_AUTO),

	/* Deww systems  */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01a7,
		      "unknown Deww", STAC_922X_DEWW_D81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01a9,
		      "unknown Deww", STAC_922X_DEWW_D81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ab,
		      "unknown Deww", STAC_922X_DEWW_D81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ac,
		      "unknown Deww", STAC_922X_DEWW_D82),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01bf,
		      "unknown Deww", STAC_922X_DEWW_M81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d0,
		      "unknown Deww", STAC_922X_DEWW_D82),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d1,
		      "unknown Deww", STAC_922X_DEWW_D81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d2,
		      "unknown Deww", STAC_922X_DEWW_D81),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01d7,
		      "Deww XPS M1210", STAC_922X_DEWW_M82),
	/* ECS/PC Chips boawds */
	SND_PCI_QUIWK_MASK(0x1019, 0xf000, 0x2000,
		      "ECS/PC chips", STAC_ECS_202),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef927x_pin_configs[] = {
	{ 0x0a, 0x02214020 },
	{ 0x0b, 0x02a19080 },
	{ 0x0c, 0x0181304e },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x01a19040 },
	{ 0x0f, 0x01011012 },
	{ 0x10, 0x01016011 },
	{ 0x11, 0x0101201f },
	{ 0x12, 0x183301f0 },
	{ 0x13, 0x18a001f0 },
	{ 0x14, 0x18a001f0 },
	{ 0x21, 0x01442070 },
	{ 0x22, 0x01c42190 },
	{ 0x23, 0x40000100 },
	{}
};

static const stwuct hda_pintbw d965_3st_pin_configs[] = {
	{ 0x0a, 0x0221401f },
	{ 0x0b, 0x02a19120 },
	{ 0x0c, 0x40000100 },
	{ 0x0d, 0x01014011 },
	{ 0x0e, 0x01a19021 },
	{ 0x0f, 0x01813024 },
	{ 0x10, 0x40000100 },
	{ 0x11, 0x40000100 },
	{ 0x12, 0x40000100 },
	{ 0x13, 0x40000100 },
	{ 0x14, 0x40000100 },
	{ 0x21, 0x40000100 },
	{ 0x22, 0x40000100 },
	{ 0x23, 0x40000100 },
	{}
};

static const stwuct hda_pintbw d965_5st_pin_configs[] = {
	{ 0x0a, 0x02214020 },
	{ 0x0b, 0x02a19080 },
	{ 0x0c, 0x0181304e },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x01a19040 },
	{ 0x0f, 0x01011012 },
	{ 0x10, 0x01016011 },
	{ 0x11, 0x40000100 },
	{ 0x12, 0x40000100 },
	{ 0x13, 0x40000100 },
	{ 0x14, 0x40000100 },
	{ 0x21, 0x01442070 },
	{ 0x22, 0x40000100 },
	{ 0x23, 0x40000100 },
	{}
};

static const stwuct hda_pintbw d965_5st_no_fp_pin_configs[] = {
	{ 0x0a, 0x40000100 },
	{ 0x0b, 0x40000100 },
	{ 0x0c, 0x0181304e },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x01a19040 },
	{ 0x0f, 0x01011012 },
	{ 0x10, 0x01016011 },
	{ 0x11, 0x40000100 },
	{ 0x12, 0x40000100 },
	{ 0x13, 0x40000100 },
	{ 0x14, 0x40000100 },
	{ 0x21, 0x01442070 },
	{ 0x22, 0x40000100 },
	{ 0x23, 0x40000100 },
	{}
};

static const stwuct hda_pintbw deww_3st_pin_configs[] = {
	{ 0x0a, 0x02211230 },
	{ 0x0b, 0x02a11220 },
	{ 0x0c, 0x01a19040 },
	{ 0x0d, 0x01114210 },
	{ 0x0e, 0x01111212 },
	{ 0x0f, 0x01116211 },
	{ 0x10, 0x01813050 },
	{ 0x11, 0x01112214 },
	{ 0x12, 0x403003fa },
	{ 0x13, 0x90a60040 },
	{ 0x14, 0x90a60040 },
	{ 0x21, 0x404003fb },
	{ 0x22, 0x40c003fc },
	{ 0x23, 0x40000100 },
	{}
};

static void stac927x_fixup_wef_no_jd(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	/* no jack detecion fow wef-no-jd modew */
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		codec->no_jack_detect = 1;
}

static void stac927x_fixup_wef(stwuct hda_codec *codec,
			       const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		snd_hda_appwy_pincfgs(codec, wef927x_pin_configs);
		spec->eapd_mask = spec->gpio_mask = 0;
		spec->gpio_diw = spec->gpio_data = 0;
	}
}

static void stac927x_fixup_deww_dmic(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	if (codec->cowe.subsystem_id != 0x1028022f) {
		/* GPIO2 High = Enabwe EAPD */
		spec->eapd_mask = spec->gpio_mask = 0x04;
		spec->gpio_diw = spec->gpio_data = 0x04;
	}

	snd_hda_add_vewbs(codec, deww_3st_cowe_init);
	spec->vowknob_init = 1;
}

static void stac927x_fixup_vowknob(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		snd_hda_add_vewbs(codec, stac927x_vowknob_cowe_init);
		spec->vowknob_init = 1;
	}
}

static const stwuct hda_fixup stac927x_fixups[] = {
	[STAC_D965_WEF_NO_JD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_wef_no_jd,
		.chained = twue,
		.chain_id = STAC_D965_WEF,
	},
	[STAC_D965_WEF] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_wef,
	},
	[STAC_D965_3ST] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_3st_pin_configs,
		.chained = twue,
		.chain_id = STAC_D965_VEWBS,
	},
	[STAC_D965_5ST] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_5st_pin_configs,
		.chained = twue,
		.chain_id = STAC_D965_VEWBS,
	},
	[STAC_D965_VEWBS] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = d965_cowe_init,
	},
	[STAC_D965_5ST_NO_FP] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_5st_no_fp_pin_configs,
	},
	[STAC_NEMO_DEFAUWT] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = nemo_pin_configs,
	},
	[STAC_DEWW_3ST] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_3st_pin_configs,
		.chained = twue,
		.chain_id = STAC_927X_DEWW_DMIC,
	},
	[STAC_DEWW_BIOS] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* cowwect the fwont output jack as a hp out */
			{ 0x0f, 0x0221101f },
			/* cowwect the fwont input jack as a mic */
			{ 0x0e, 0x02a79130 },
			{}
		},
		.chained = twue,
		.chain_id = STAC_927X_DEWW_DMIC,
	},
	[STAC_DEWW_BIOS_AMIC] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* configuwe the anawog micwophone on some waptops */
			{ 0x0c, 0x90a79130 },
			{}
		},
		.chained = twue,
		.chain_id = STAC_DEWW_BIOS,
	},
	[STAC_DEWW_BIOS_SPDIF] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* cowwect the device fiewd to SPDIF out */
			{ 0x21, 0x01442070 },
			{}
		},
		.chained = twue,
		.chain_id = STAC_DEWW_BIOS,
	},
	[STAC_927X_DEWW_DMIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_deww_dmic,
	},
	[STAC_927X_VOWKNOB] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_vowknob,
	},
};

static const stwuct hda_modew_fixup stac927x_modews[] = {
	{ .id = STAC_D965_WEF_NO_JD, .name = "wef-no-jd" },
	{ .id = STAC_D965_WEF, .name = "wef" },
	{ .id = STAC_D965_3ST, .name = "3stack" },
	{ .id = STAC_D965_5ST, .name = "5stack" },
	{ .id = STAC_D965_5ST_NO_FP, .name = "5stack-no-fp" },
	{ .id = STAC_DEWW_3ST, .name = "deww-3stack" },
	{ .id = STAC_DEWW_BIOS, .name = "deww-bios" },
	{ .id = STAC_NEMO_DEFAUWT, .name = "nemo-defauwt" },
	{ .id = STAC_DEWW_BIOS_AMIC, .name = "deww-bios-amic" },
	{ .id = STAC_927X_VOWKNOB, .name = "vowknob" },
	{}
};

static const stwuct snd_pci_quiwk stac927x_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_D965_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_D965_WEF),
	 /* Intew 946 based systems */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x3d01, "Intew D946", STAC_D965_3ST),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0xa301, "Intew D946", STAC_D965_3ST),
	/* 965 based 3 stack systems */
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_INTEW, 0xff00, 0x2100,
			   "Intew D965", STAC_D965_3ST),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_INTEW, 0xff00, 0x2000,
			   "Intew D965", STAC_D965_3ST),
	/* Deww 3 stack systems */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x01dd, "Deww Dimension E520", STAC_DEWW_3ST),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x01ed, "Deww     ", STAC_DEWW_3ST),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x01f4, "Deww     ", STAC_DEWW_3ST),
	/* Deww 3 stack systems with vewb tabwe in BIOS */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x01f3, "Deww Inspiwon 1420", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x01f7, "Deww XPS M1730", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x0227, "Deww Vostwo 1400  ", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x022e, "Deww     ", STAC_DEWW_BIOS_SPDIF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x022f, "Deww Inspiwon 1525", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x0242, "Deww     ", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x0243, "Deww     ", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x02ff, "Deww     ", STAC_DEWW_BIOS),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW,  0x0209, "Deww XPS 1330", STAC_DEWW_BIOS_SPDIF),
	/* 965 based 5 stack systems */
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_INTEW, 0xff00, 0x2300,
			   "Intew D965", STAC_D965_5ST),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_INTEW, 0xff00, 0x2500,
			   "Intew D965", STAC_D965_5ST),
	/* Nemo */
	SND_PCI_QUIWK(0x1888, 0x1000, "AmigaOne X1000", STAC_NEMO_DEFAUWT),
	/* vowume-knob fixes */
	SND_PCI_QUIWK_VENDOW(0x10cf, "FSC", STAC_927X_VOWKNOB),
	{} /* tewminatow */
};

static const stwuct hda_pintbw wef9205_pin_configs[] = {
	{ 0x0a, 0x40000100 },
	{ 0x0b, 0x40000100 },
	{ 0x0c, 0x01016011 },
	{ 0x0d, 0x01014010 },
	{ 0x0e, 0x01813122 },
	{ 0x0f, 0x01a19021 },
	{ 0x14, 0x01019020 },
	{ 0x16, 0x40000100 },
	{ 0x17, 0x90a000f0 },
	{ 0x18, 0x90a000f0 },
	{ 0x21, 0x01441030 },
	{ 0x22, 0x01c41030 },
	{}
};

/*
    STAC 9205 pin configs fow
    102801F1
    102801F2
    102801FC
    102801FD
    10280204
    1028021F
    10280228 (Deww Vostwo 1500)
    10280229 (Deww Vostwo 1700)
*/
static const stwuct hda_pintbw deww_9205_m42_pin_configs[] = {
	{ 0x0a, 0x0321101F },
	{ 0x0b, 0x03A11020 },
	{ 0x0c, 0x400003FA },
	{ 0x0d, 0x90170310 },
	{ 0x0e, 0x400003FB },
	{ 0x0f, 0x400003FC },
	{ 0x14, 0x400003FD },
	{ 0x16, 0x40F000F9 },
	{ 0x17, 0x90A60330 },
	{ 0x18, 0x400003FF },
	{ 0x21, 0x0144131F },
	{ 0x22, 0x40C003FE },
	{}
};

/*
    STAC 9205 pin configs fow
    102801F9
    102801FA
    102801FE
    102801FF (Deww Pwecision M4300)
    10280206
    10280200
    10280201
*/
static const stwuct hda_pintbw deww_9205_m43_pin_configs[] = {
	{ 0x0a, 0x0321101f },
	{ 0x0b, 0x03a11020 },
	{ 0x0c, 0x90a70330 },
	{ 0x0d, 0x90170310 },
	{ 0x0e, 0x400000fe },
	{ 0x0f, 0x400000ff },
	{ 0x14, 0x400000fd },
	{ 0x16, 0x40f000f9 },
	{ 0x17, 0x400000fa },
	{ 0x18, 0x400000fc },
	{ 0x21, 0x0144131f },
	{ 0x22, 0x40c003f8 },
	/* Enabwe SPDIF in/out */
	{ 0x1f, 0x01441030 },
	{ 0x20, 0x1c410030 },
	{}
};

static const stwuct hda_pintbw deww_9205_m44_pin_configs[] = {
	{ 0x0a, 0x0421101f },
	{ 0x0b, 0x04a11020 },
	{ 0x0c, 0x400003fa },
	{ 0x0d, 0x90170310 },
	{ 0x0e, 0x400003fb },
	{ 0x0f, 0x400003fc },
	{ 0x14, 0x400003fd },
	{ 0x16, 0x400003f9 },
	{ 0x17, 0x90a60330 },
	{ 0x18, 0x400003ff },
	{ 0x21, 0x01441340 },
	{ 0x22, 0x40c003fe },
	{}
};

static void stac9205_fixup_wef(stwuct hda_codec *codec,
			       const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		snd_hda_appwy_pincfgs(codec, wef9205_pin_configs);
		/* SPDIF-In enabwed */
		spec->eapd_mask = spec->gpio_mask = spec->gpio_diw = 0;
	}
}

static void stac9205_fixup_deww_m43(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;
	stwuct hda_jack_cawwback *jack;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		snd_hda_appwy_pincfgs(codec, deww_9205_m43_pin_configs);

		/* Enabwe unsow wesponse fow GPIO4/Dock HP connection */
		snd_hda_codec_wwite_cache(codec, codec->cowe.afg, 0,
			AC_VEWB_SET_GPIO_UNSOWICITED_WSP_MASK, 0x10);
		jack = snd_hda_jack_detect_enabwe_cawwback(codec, codec->cowe.afg,
							   stac_vwef_event);
		if (!IS_EWW(jack))
			jack->pwivate_data = 0x01;

		spec->gpio_diw = 0x0b;
		spec->eapd_mask = 0x01;
		spec->gpio_mask = 0x1b;
		spec->gpio_mute = 0x10;
		/* GPIO0 High = EAPD, GPIO1 Wow = Headphone Mute,
		 * GPIO3 Wow = DWM
		 */
		spec->gpio_data = 0x01;
	}
}

static void stac9205_fixup_eapd(stwuct hda_codec *codec,
				const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		spec->eapd_switch = 0;
}

static const stwuct hda_fixup stac9205_fixups[] = {
	[STAC_9205_WEF] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_wef,
	},
	[STAC_9205_DEWW_M42] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_9205_m42_pin_configs,
	},
	[STAC_9205_DEWW_M43] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_deww_m43,
	},
	[STAC_9205_DEWW_M44] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = deww_9205_m44_pin_configs,
	},
	[STAC_9205_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_eapd,
	},
	{}
};

static const stwuct hda_modew_fixup stac9205_modews[] = {
	{ .id = STAC_9205_WEF, .name = "wef" },
	{ .id = STAC_9205_DEWW_M42, .name = "deww-m42" },
	{ .id = STAC_9205_DEWW_M43, .name = "deww-m43" },
	{ .id = STAC_9205_DEWW_M44, .name = "deww-m44" },
	{ .id = STAC_9205_EAPD, .name = "eapd" },
	{}
};

static const stwuct snd_pci_quiwk stac9205_fixup_tbw[] = {
	/* SigmaTew wefewence boawd */
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0x2668,
		      "DFI WanPawty", STAC_9205_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_INTEW, 0xfb30,
		      "SigmaTew", STAC_9205_WEF),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DFI, 0x3101,
		      "DFI WanPawty", STAC_9205_WEF),
	/* Deww */
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f1,
		      "unknown Deww", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f2,
		      "unknown Deww", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f8,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01f9,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01fa,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01fc,
		      "unknown Deww", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01fd,
		      "unknown Deww", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01fe,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x01ff,
		      "Deww Pwecision M4300", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0204,
		      "unknown Deww", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0206,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x021b,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x021c,
		      "Deww Pwecision", STAC_9205_DEWW_M43),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x021f,
		      "Deww Inspiwon", STAC_9205_DEWW_M44),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0228,
		      "Deww Vostwo 1500", STAC_9205_DEWW_M42),
	SND_PCI_QUIWK(PCI_VENDOW_ID_DEWW, 0x0229,
		      "Deww Vostwo 1700", STAC_9205_DEWW_M42),
	/* Gateway */
	SND_PCI_QUIWK(0x107b, 0x0560, "Gateway T6834c", STAC_9205_EAPD),
	SND_PCI_QUIWK(0x107b, 0x0565, "Gateway T1616", STAC_9205_EAPD),
	{} /* tewminatow */
};

static void stac92hd95_fixup_hp_wed(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct sigmatew_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	if (find_mute_wed_cfg(codec, spec->defauwt_powawity))
		codec_dbg(codec, "mute WED gpio %d powawity %d\n",
				spec->gpio_wed,
				spec->gpio_wed_powawity);
}

static const stwuct hda_fixup stac92hd95_fixups[] = {
	[STAC_92HD95_HP_WED] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd95_fixup_hp_wed,
	},
	[STAC_92HD95_HP_BASS] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = (const stwuct hda_vewb[]) {
			{0x1a, 0x795, 0x00}, /* HPF to 100Hz */
			{}
		},
		.chained = twue,
		.chain_id = STAC_92HD95_HP_WED,
	},
};

static const stwuct snd_pci_quiwk stac92hd95_fixup_tbw[] = {
	SND_PCI_QUIWK(PCI_VENDOW_ID_HP, 0x1911, "HP Spectwe 13", STAC_92HD95_HP_BASS),
	{} /* tewminatow */
};

static const stwuct hda_modew_fixup stac92hd95_modews[] = {
	{ .id = STAC_92HD95_HP_WED, .name = "hp-wed" },
	{ .id = STAC_92HD95_HP_BASS, .name = "hp-bass" },
	{}
};


static int stac_pawse_auto_config(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int eww;
	int fwags = 0;

	if (spec->headset_jack)
		fwags |= HDA_PINCFG_HEADSET_MIC;

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->gen.autocfg, NUWW, fwags);
	if (eww < 0)
		wetuwn eww;

	/* add hooks */
	spec->gen.pcm_pwayback_hook = stac_pwayback_pcm_hook;
	spec->gen.pcm_captuwe_hook = stac_captuwe_pcm_hook;

	spec->gen.automute_hook = stac_update_outputs;

	if (spec->gpio_wed)
		snd_hda_gen_add_mute_wed_cdev(codec, stac_vmastew_hook);

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->gen.autocfg);
	if (eww < 0)
		wetuwn eww;

	if (spec->vwef_mute_wed_nid) {
		eww = snd_hda_gen_fix_pin_powew(codec, spec->vwef_mute_wed_nid);
		if (eww < 0)
			wetuwn eww;
	}

	/* setup anawog beep contwows */
	if (spec->anabeep_nid > 0) {
		eww = stac_auto_cweate_beep_ctws(codec,
						 spec->anabeep_nid);
		if (eww < 0)
			wetuwn eww;
	}

	/* setup digitaw beep contwows and input device */
#ifdef CONFIG_SND_HDA_INPUT_BEEP
	if (spec->gen.beep_nid) {
		hda_nid_t nid = spec->gen.beep_nid;
		unsigned int caps;

		eww = stac_auto_cweate_beep_ctws(codec, nid);
		if (eww < 0)
			wetuwn eww;
		if (codec->beep) {
			/* IDT/STAC codecs have wineaw beep tone pawametew */
			codec->beep->wineaw_tone = spec->wineaw_tone_beep;
			/* keep powew up whiwe beep is enabwed */
			codec->beep->keep_powew_at_enabwe = 1;
			/* if no beep switch is avaiwabwe, make its own one */
			caps = quewy_amp_caps(codec, nid, HDA_OUTPUT);
			if (!(caps & AC_AMPCAP_MUTE)) {
				eww = stac_beep_switch_ctw(codec);
				if (eww < 0)
					wetuwn eww;
			}
		}
	}
#endif

	if (spec->awoopback_ctw &&
	    snd_hda_get_boow_hint(codec, "woopback") == 1) {
		unsigned int ww_vewb =
			spec->awoopback_ctw->pwivate_vawue >> 16;
		if (snd_hdac_wegmap_add_vendow_vewb(&codec->cowe, ww_vewb))
			wetuwn -ENOMEM;
		if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, spec->awoopback_ctw))
			wetuwn -ENOMEM;
	}

	if (spec->have_spdif_mux) {
		eww = stac_cweate_spdif_mux_ctws(codec);
		if (eww < 0)
			wetuwn eww;
	}

	stac_init_powew_map(codec);

	wetuwn 0;
}

static int stac_init(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;
	int i;

	/* ovewwide some hints */
	stac_stowe_hints(codec);

	/* set up GPIO */
	/* tuwn on EAPD staticawwy when spec->eapd_switch isn't set.
	 * othewwise, unsow event wiww tuwn it on/off dynamicawwy
	 */
	if (!spec->eapd_switch)
		spec->gpio_data |= spec->eapd_mask;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_diw, spec->gpio_data);

	snd_hda_gen_init(codec);

	/* sync the powew-map */
	if (spec->num_pwws)
		snd_hda_codec_wwite(codec, codec->cowe.afg, 0,
				    AC_VEWB_IDT_SET_POWEW_MAP,
				    spec->powew_map_bits);

	/* powew down inactive ADCs */
	if (spec->powewdown_adcs) {
		fow (i = 0; i < spec->gen.num_aww_adcs; i++) {
			if (spec->active_adcs & (1 << i))
				continue;
			snd_hda_codec_wwite(codec, spec->gen.aww_adcs[i], 0,
					    AC_VEWB_SET_POWEW_STATE,
					    AC_PWWST_D3);
		}
	}

	wetuwn 0;
}

#define stac_fwee	snd_hda_gen_fwee

#ifdef CONFIG_SND_PWOC_FS
static void stac92hd_pwoc_hook(stwuct snd_info_buffew *buffew,
			       stwuct hda_codec *codec, hda_nid_t nid)
{
	if (nid == codec->cowe.afg)
		snd_ipwintf(buffew, "Powew-Map: 0x%02x\n", 
			    snd_hda_codec_wead(codec, nid, 0,
					       AC_VEWB_IDT_GET_POWEW_MAP, 0));
}

static void anawog_woop_pwoc_hook(stwuct snd_info_buffew *buffew,
				  stwuct hda_codec *codec,
				  unsigned int vewb)
{
	snd_ipwintf(buffew, "Anawog Woopback: 0x%02x\n",
		    snd_hda_codec_wead(codec, codec->cowe.afg, 0, vewb, 0));
}

/* stac92hd71bxx, stac92hd73xx */
static void stac92hd7x_pwoc_hook(stwuct snd_info_buffew *buffew,
				 stwuct hda_codec *codec, hda_nid_t nid)
{
	stac92hd_pwoc_hook(buffew, codec, nid);
	if (nid == codec->cowe.afg)
		anawog_woop_pwoc_hook(buffew, codec, 0xfa0);
}

static void stac9205_pwoc_hook(stwuct snd_info_buffew *buffew,
			       stwuct hda_codec *codec, hda_nid_t nid)
{
	if (nid == codec->cowe.afg)
		anawog_woop_pwoc_hook(buffew, codec, 0xfe0);
}

static void stac927x_pwoc_hook(stwuct snd_info_buffew *buffew,
			       stwuct hda_codec *codec, hda_nid_t nid)
{
	if (nid == codec->cowe.afg)
		anawog_woop_pwoc_hook(buffew, codec, 0xfeb);
}
#ewse
#define stac92hd_pwoc_hook	NUWW
#define stac92hd7x_pwoc_hook	NUWW
#define stac9205_pwoc_hook	NUWW
#define stac927x_pwoc_hook	NUWW
#endif

#ifdef CONFIG_PM
static int stac_suspend(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	snd_hda_shutup_pins(codec);

	if (spec->eapd_mask)
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_diw, spec->gpio_data &
				~spec->eapd_mask);

	wetuwn 0;
}
#ewse
#define stac_suspend		NUWW
#endif /* CONFIG_PM */

static const stwuct hda_codec_ops stac_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = stac_init,
	.fwee = stac_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
#ifdef CONFIG_PM
	.suspend = stac_suspend,
#endif
};

static int awwoc_stac_spec(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->no_twiggew_sense = 1; /* seems common with STAC/IDT codecs */
	spec->gen.dac_min_mute = twue;
	codec->patch_ops = stac_patch_ops;
	wetuwn 0;
}

static int patch_stac9200(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;

	codec->powew_fiwtew = snd_hda_codec_eapd_powew_fiwtew;

	snd_hda_add_vewbs(codec, stac9200_eapd_init);

	snd_hda_pick_fixup(codec, stac9200_modews, stac9200_fixup_tbw,
			   stac9200_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static int patch_stac925x(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;

	snd_hda_add_vewbs(codec, stac925x_cowe_init);

	snd_hda_pick_fixup(codec, stac925x_modews, stac925x_fixup_tbw,
			   stac925x_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static int patch_stac92hd73xx(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;
	int num_dacs;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	/* enabwe powew_save_node onwy fow new 92HD89xx chips, as it causes
	 * cwick noises on owd 92HD73xx chips.
	 */
	if ((codec->cowe.vendow_id & 0xfffffff0) != 0x111d7670)
		codec->powew_save_node = 1;
	spec->wineaw_tone_beep = 0;
	spec->gen.mixew_nid = 0x1d;
	spec->have_spdif_mux = 1;

	num_dacs = snd_hda_get_num_conns(codec, 0x0a) - 1;
	if (num_dacs < 3 || num_dacs > 5) {
		codec_wawn(codec,
			   "Couwd not detewmine numbew of channews defauwting to DAC count\n");
		num_dacs = 5;
	}

	switch (num_dacs) {
	case 0x3: /* 6 Channew */
		spec->awoopback_ctw = &stac92hd73xx_6ch_woopback;
		bweak;
	case 0x4: /* 8 Channew */
		spec->awoopback_ctw = &stac92hd73xx_8ch_woopback;
		bweak;
	case 0x5: /* 10 Channew */
		spec->awoopback_ctw = &stac92hd73xx_10ch_woopback;
		bweak;
	}

	spec->awoopback_mask = 0x01;
	spec->awoopback_shift = 8;

	spec->gen.beep_nid = 0x1c; /* digitaw beep */

	/* GPIO0 High = Enabwe EAPD */
	spec->eapd_mask = spec->gpio_mask = spec->gpio_diw = 0x1;
	spec->gpio_data = 0x01;

	spec->eapd_switch = 1;

	spec->num_pwws = AWWAY_SIZE(stac92hd73xx_pww_nids);
	spec->pww_nids = stac92hd73xx_pww_nids;

	spec->gen.own_eapd_ctw = 1;
	spec->gen.powew_down_unused = 1;

	snd_hda_pick_fixup(codec, stac92hd73xx_modews, stac92hd73xx_fixup_tbw,
			   stac92hd73xx_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	if (!spec->vowknob_init)
		snd_hda_add_vewbs(codec, stac92hd73xx_cowe_init);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	/* Don't GPIO-mute speakews if thewe awe no intewnaw speakews, because
	 * the GPIO might be necessawy fow Headphone
	 */
	if (spec->eapd_switch && !has_buiwtin_speakew(codec))
		spec->eapd_switch = 0;

	codec->pwoc_widget_hook = stac92hd7x_pwoc_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static void stac_setup_gpio(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec = codec->spec;

	spec->gpio_mask |= spec->eapd_mask;
	if (spec->gpio_wed) {
		if (!spec->vwef_mute_wed_nid) {
			spec->gpio_mask |= spec->gpio_wed;
			spec->gpio_diw |= spec->gpio_wed;
			spec->gpio_data |= spec->gpio_wed;
		} ewse {
			codec->powew_fiwtew = stac_vwef_wed_powew_fiwtew;
		}
	}

	if (spec->mic_mute_wed_gpio) {
		spec->gpio_mask |= spec->mic_mute_wed_gpio;
		spec->gpio_diw |= spec->mic_mute_wed_gpio;
		spec->mic_enabwed = 0;
		spec->gpio_data |= spec->mic_mute_wed_gpio;
		snd_hda_gen_add_micmute_wed_cdev(codec, stac_captuwe_wed_update);
	}
}

static int patch_stac92hd83xxx(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	/* wongew deway needed fow D3 */
	codec->cowe.powew_caps &= ~AC_PWWST_EPSS;

	spec = codec->spec;
	codec->powew_save_node = 1;
	spec->wineaw_tone_beep = 0;
	spec->gen.own_eapd_ctw = 1;
	spec->gen.powew_down_unused = 1;
	spec->gen.mixew_nid = 0x1b;

	spec->gen.beep_nid = 0x21; /* digitaw beep */
	spec->pww_nids = stac92hd83xxx_pww_nids;
	spec->num_pwws = AWWAY_SIZE(stac92hd83xxx_pww_nids);
	spec->defauwt_powawity = -1; /* no defauwt cfg */

	snd_hda_add_vewbs(codec, stac92hd83xxx_cowe_init);

	snd_hda_pick_fixup(codec, stac92hd83xxx_modews, stac92hd83xxx_fixup_tbw,
			   stac92hd83xxx_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	stac_setup_gpio(codec);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	codec->pwoc_widget_hook = stac92hd_pwoc_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static const hda_nid_t stac92hd95_pww_nids[] = {
	0x0a, 0x0b, 0x0c, 0x0d
};

static int patch_stac92hd95(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	/* wongew deway needed fow D3 */
	codec->cowe.powew_caps &= ~AC_PWWST_EPSS;

	spec = codec->spec;
	codec->powew_save_node = 1;
	spec->wineaw_tone_beep = 0;
	spec->gen.own_eapd_ctw = 1;
	spec->gen.powew_down_unused = 1;

	spec->gen.beep_nid = 0x19; /* digitaw beep */
	spec->pww_nids = stac92hd95_pww_nids;
	spec->num_pwws = AWWAY_SIZE(stac92hd95_pww_nids);
	spec->defauwt_powawity = 0;

	snd_hda_pick_fixup(codec, stac92hd95_modews, stac92hd95_fixup_tbw,
			   stac92hd95_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	stac_setup_gpio(codec);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	codec->pwoc_widget_hook = stac92hd_pwoc_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static int patch_stac92hd71bxx(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	const hda_nid_t *unmute_nids = stac92hd71bxx_unmute_nids;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	/* disabwed powew_save_node since it causes noises on a Deww machine */
	/* codec->powew_save_node = 1; */
	spec->wineaw_tone_beep = 0;
	spec->gen.own_eapd_ctw = 1;
	spec->gen.powew_down_unused = 1;
	spec->gen.mixew_nid = 0x17;
	spec->have_spdif_mux = 1;

	/* GPIO0 = EAPD */
	spec->gpio_mask = 0x01;
	spec->gpio_diw = 0x01;
	spec->gpio_data = 0x01;

	switch (codec->cowe.vendow_id) {
	case 0x111d76b6: /* 4 Powt without Anawog Mixew */
	case 0x111d76b7:
		unmute_nids++;
		bweak;
	case 0x111d7608: /* 5 Powt with Anawog Mixew */
		if ((codec->cowe.wevision_id & 0xf) == 0 ||
		    (codec->cowe.wevision_id & 0xf) == 1)
			spec->stweam_deway = 40; /* 40 miwwiseconds */

		/* disabwe VSW */
		unmute_nids++;
		snd_hda_codec_set_pincfg(codec, 0x0f, 0x40f000f0);
		snd_hda_codec_set_pincfg(codec, 0x19, 0x40f000f3);
		bweak;
	case 0x111d7603: /* 6 Powt with Anawog Mixew */
		if ((codec->cowe.wevision_id & 0xf) == 1)
			spec->stweam_deway = 40; /* 40 miwwiseconds */

		bweak;
	}

	if (get_wcaps_type(get_wcaps(codec, 0x28)) == AC_WID_VOW_KNB)
		snd_hda_add_vewbs(codec, stac92hd71bxx_cowe_init);

	if (get_wcaps(codec, 0xa) & AC_WCAP_IN_AMP) {
		const hda_nid_t *p;
		fow (p = unmute_nids; *p; p++)
			snd_hda_codec_amp_init_steweo(codec, *p, HDA_INPUT, 0,
						      0xff, 0x00);
	}

	spec->awoopback_ctw = &stac92hd71bxx_woopback;
	spec->awoopback_mask = 0x50;
	spec->awoopback_shift = 0;

	spec->powewdown_adcs = 1;
	spec->gen.beep_nid = 0x26; /* digitaw beep */
	spec->num_pwws = AWWAY_SIZE(stac92hd71bxx_pww_nids);
	spec->pww_nids = stac92hd71bxx_pww_nids;

	snd_hda_pick_fixup(codec, stac92hd71bxx_modews, stac92hd71bxx_fixup_tbw,
			   stac92hd71bxx_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	stac_setup_gpio(codec);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	codec->pwoc_widget_hook = stac92hd7x_pwoc_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static int patch_stac922x(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;

	snd_hda_add_vewbs(codec, stac922x_cowe_init);

	/* Fix Mux captuwe wevew; max to 2 */
	snd_hda_ovewwide_amp_caps(codec, 0x12, HDA_OUTPUT,
				  (0 << AC_AMPCAP_OFFSET_SHIFT) |
				  (2 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x27 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));

	snd_hda_pick_fixup(codec, stac922x_modews, stac922x_fixup_tbw,
			   stac922x_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static const chaw * const stac927x_spdif_wabews[] = {
	"Digitaw Pwayback", "ADAT", "Anawog Mux 1",
	"Anawog Mux 2", "Anawog Mux 3", NUWW
};

static int patch_stac927x(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;
	spec->have_spdif_mux = 1;
	spec->spdif_wabews = stac927x_spdif_wabews;

	spec->gen.beep_nid = 0x23; /* digitaw beep */

	/* GPIO0 High = Enabwe EAPD */
	spec->eapd_mask = spec->gpio_mask = 0x01;
	spec->gpio_diw = spec->gpio_data = 0x01;

	spec->awoopback_ctw = &stac927x_woopback;
	spec->awoopback_mask = 0x40;
	spec->awoopback_shift = 0;
	spec->eapd_switch = 1;

	snd_hda_pick_fixup(codec, stac927x_modews, stac927x_fixup_tbw,
			   stac927x_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	if (!spec->vowknob_init)
		snd_hda_add_vewbs(codec, stac927x_cowe_init);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	codec->pwoc_widget_hook = stac927x_pwoc_hook;

	/*
	 * !!FIXME!!
	 * The STAC927x seem to wequiwe faiwwy wong deways fow cewtain
	 * command sequences.  With too showt deways (even if the answew
	 * is set to WIWB pwopewwy), it wesuwts in the siwence output
	 * on some hawdwawes wike Deww.
	 *
	 * The bewow fwag enabwes the wongew deway (see get_wesponse
	 * in hda_intew.c).
	 */
	codec->bus->cowe.needs_damn_wong_deway = 1;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

static int patch_stac9205(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;
	spec->have_spdif_mux = 1;

	spec->gen.beep_nid = 0x23; /* digitaw beep */

	snd_hda_add_vewbs(codec, stac9205_cowe_init);
	spec->awoopback_ctw = &stac9205_woopback;

	spec->awoopback_mask = 0x40;
	spec->awoopback_shift = 0;
	
	/* GPIO0 High = EAPD */
	spec->eapd_mask = spec->gpio_mask = spec->gpio_diw = 0x1;
	spec->gpio_data = 0x01;

	/* Tuwn on/off EAPD pew HP pwugging */
	spec->eapd_switch = 1;

	snd_hda_pick_fixup(codec, stac9205_modews, stac9205_fixup_tbw,
			   stac9205_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn eww;
	}

	codec->pwoc_widget_hook = stac9205_pwoc_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}

/*
 * STAC9872 hack
 */

static const stwuct hda_vewb stac9872_cowe_init[] = {
	{0x15, AC_VEWB_SET_CONNECT_SEW, 0x1}, /* mic-sew: 0a,0d,14,02 */
	{0x15, AC_VEWB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE}, /* Mic-in -> 0x9 */
	{}
};

static const stwuct hda_pintbw stac9872_vaio_pin_configs[] = {
	{ 0x0a, 0x03211020 },
	{ 0x0b, 0x411111f0 },
	{ 0x0c, 0x411111f0 },
	{ 0x0d, 0x03a15030 },
	{ 0x0e, 0x411111f0 },
	{ 0x0f, 0x90170110 },
	{ 0x11, 0x411111f0 },
	{ 0x13, 0x411111f0 },
	{ 0x14, 0x90a7013e },
	{}
};

static const stwuct hda_modew_fixup stac9872_modews[] = {
	{ .id = STAC_9872_VAIO, .name = "vaio" },
	{}
};

static const stwuct hda_fixup stac9872_fixups[] = {
	[STAC_9872_VAIO] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = stac9872_vaio_pin_configs,
	},
};

static const stwuct snd_pci_quiwk stac9872_fixup_tbw[] = {
	SND_PCI_QUIWK_MASK(0x104d, 0xfff0, 0x81e0,
			   "Sony VAIO F/S", STAC_9872_VAIO),
	{} /* tewminatow */
};

static int patch_stac9872(stwuct hda_codec *codec)
{
	stwuct sigmatew_spec *spec;
	int eww;

	eww = awwoc_stac_spec(codec);
	if (eww < 0)
		wetuwn eww;

	spec = codec->spec;
	spec->wineaw_tone_beep = 1;
	spec->gen.own_eapd_ctw = 1;

	snd_hda_add_vewbs(codec, stac9872_cowe_init);

	snd_hda_pick_fixup(codec, stac9872_modews, stac9872_fixup_tbw,
			   stac9872_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = stac_pawse_auto_config(codec);
	if (eww < 0) {
		stac_fwee(codec);
		wetuwn -EINVAW;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}


/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_sigmatew[] = {
	HDA_CODEC_ENTWY(0x83847690, "STAC9200", patch_stac9200),
	HDA_CODEC_ENTWY(0x83847882, "STAC9220 A1", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847680, "STAC9221 A1", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847880, "STAC9220 A2", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847681, "STAC9220D/9223D A2", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847682, "STAC9221 A2", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847683, "STAC9221D A2", patch_stac922x),
	HDA_CODEC_ENTWY(0x83847618, "STAC9227", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847619, "STAC9227", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847638, "STAC92HD700", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847616, "STAC9228", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847617, "STAC9228", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847614, "STAC9229", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847615, "STAC9229", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847620, "STAC9274", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847621, "STAC9274D", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847622, "STAC9273X", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847623, "STAC9273D", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847624, "STAC9272X", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847625, "STAC9272D", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847626, "STAC9271X", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847627, "STAC9271D", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847628, "STAC9274X5NH", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847629, "STAC9274D5NH", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847632, "STAC9202",  patch_stac925x),
	HDA_CODEC_ENTWY(0x83847633, "STAC9202D", patch_stac925x),
	HDA_CODEC_ENTWY(0x83847634, "STAC9250", patch_stac925x),
	HDA_CODEC_ENTWY(0x83847635, "STAC9250D", patch_stac925x),
	HDA_CODEC_ENTWY(0x83847636, "STAC9251", patch_stac925x),
	HDA_CODEC_ENTWY(0x83847637, "STAC9250D", patch_stac925x),
	HDA_CODEC_ENTWY(0x83847645, "92HD206X", patch_stac927x),
	HDA_CODEC_ENTWY(0x83847646, "92HD206D", patch_stac927x),
	/* The fowwowing does not take into account .id=0x83847661 when subsys =
	 * 104D0C00 which is STAC9225s. Because of this, some SZ Notebooks awe
	 * cuwwentwy not fuwwy suppowted.
	 */
	HDA_CODEC_ENTWY(0x83847661, "CXD9872WD/K", patch_stac9872),
	HDA_CODEC_ENTWY(0x83847662, "STAC9872AK", patch_stac9872),
	HDA_CODEC_ENTWY(0x83847664, "CXD9872AKD", patch_stac9872),
	HDA_CODEC_ENTWY(0x83847698, "STAC9205", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a0, "STAC9205", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a1, "STAC9205D", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a2, "STAC9204", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a3, "STAC9204D", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a4, "STAC9255", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a5, "STAC9255D", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a6, "STAC9254", patch_stac9205),
	HDA_CODEC_ENTWY(0x838476a7, "STAC9254D", patch_stac9205),
	HDA_CODEC_ENTWY(0x111d7603, "92HD75B3X5", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d7604, "92HD83C1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76d4, "92HD83C1C5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7605, "92HD81B1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76d5, "92HD81B1C5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76d1, "92HD87B1/3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76d9, "92HD87B2/4", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7666, "92HD88B3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7667, "92HD88B1", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7668, "92HD88B2", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7669, "92HD88B4", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d7608, "92HD75B2X5", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d7674, "92HD73D1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d7675, "92HD73C1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d7676, "92HD73E1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d7695, "92HD95", patch_stac92hd95),
	HDA_CODEC_ENTWY(0x111d76b0, "92HD71B8X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b1, "92HD71B8X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b2, "92HD71B7X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b3, "92HD71B7X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b4, "92HD71B6X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b5, "92HD71B6X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b6, "92HD71B5X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76b7, "92HD71B5X", patch_stac92hd71bxx),
	HDA_CODEC_ENTWY(0x111d76c0, "92HD89C3", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c1, "92HD89C2", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c2, "92HD89C1", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c3, "92HD89B3", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c4, "92HD89B2", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c5, "92HD89B1", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c6, "92HD89E3", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c7, "92HD89E2", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c8, "92HD89E1", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76c9, "92HD89D3", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76ca, "92HD89D2", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76cb, "92HD89D1", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76cc, "92HD89F3", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76cd, "92HD89F2", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76ce, "92HD89F1", patch_stac92hd73xx),
	HDA_CODEC_ENTWY(0x111d76df, "92HD93BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e0, "92HD91BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e3, "92HD98BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e5, "92HD99BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e7, "92HD90BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e8, "92HD66B1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76e9, "92HD66B2X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76ea, "92HD66B3X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76eb, "92HD66C1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76ec, "92HD66C2X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76ed, "92HD66C3X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76ee, "92HD66B1X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76ef, "92HD66B2X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76f0, "92HD66B3X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76f1, "92HD66C1X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76f2, "92HD66C2X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTWY(0x111d76f3, "92HD66C3/65", patch_stac92hd83xxx),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_sigmatew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IDT/Sigmatew HD-audio codec");

static stwuct hda_codec_dwivew sigmatew_dwivew = {
	.id = snd_hda_id_sigmatew,
};

moduwe_hda_codec_dwivew(sigmatew_dwivew);
