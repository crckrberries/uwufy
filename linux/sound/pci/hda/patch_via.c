// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * HD audio intewface patch fow VIA VT17xx/VT18xx/VT20xx codec
 *
 *  (C) 2006-2009 VIA Technowogy, Inc.
 *  (C) 2006-2008 Takashi Iwai <tiwai@suse.de>
 */

/* * * * * * * * * * * * * * Wewease Histowy * * * * * * * * * * * * * * * * */
/*									     */
/* 2006-03-03  Wydia Wang  Cweate the basic patch to suppowt VT1708 codec    */
/* 2006-03-14  Wydia Wang  Modify hawd code fow some pin widget nid	     */
/* 2006-08-02  Wydia Wang  Add suppowt to VT1709 codec			     */
/* 2006-09-08  Wydia Wang  Fix intewnaw woopback wecowding souwce sewect bug */
/* 2007-09-12  Wydia Wang  Add EAPD enabwe duwing dwivew initiawization	     */
/* 2007-09-17  Wydia Wang  Add VT1708B codec suppowt			    */
/* 2007-11-14  Wydia Wang  Add VT1708A codec HP and CD pin connect config    */
/* 2008-02-03  Wydia Wang  Fix Weaw channews and Back channews invewse issue */
/* 2008-03-06  Wydia Wang  Add VT1702 codec and VT1708S codec suppowt	     */
/* 2008-04-09  Wydia Wang  Add mute fwont speakew when HP pwugin	     */
/* 2008-04-09  Wydia Wang  Add Independent HP featuwe			     */
/* 2008-05-28  Wydia Wang  Add second S/PDIF Out suppowt fow VT1702	     */
/* 2008-09-15  Wogan Wi	   Add VT1708S Mic Boost wowkawound/backdoow	     */
/* 2009-02-16  Wogan Wi	   Add suppowt fow VT1718S			     */
/* 2009-03-13  Wogan Wi	   Add suppowt fow VT1716S			     */
/* 2009-04-14  Wydai Wang  Add suppowt fow VT1828S and VT2020		     */
/* 2009-07-08  Wydia Wang  Add suppowt fow VT2002P			     */
/* 2009-07-21  Wydia Wang  Add suppowt fow VT1812			     */
/* 2009-09-19  Wydia Wang  Add suppowt fow VT1818S			     */
/*									     */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/asoundef.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"

/* Pin Widget NID */
#define VT1708_HP_PIN_NID	0x20
#define VT1708_CD_PIN_NID	0x24

enum VIA_HDA_CODEC {
	UNKNOWN = -1,
	VT1708,
	VT1709_10CH,
	VT1709_6CH,
	VT1708B_8CH,
	VT1708B_4CH,
	VT1708S,
	VT1708BCE,
	VT1702,
	VT1718S,
	VT1716S,
	VT2002P,
	VT1812,
	VT1802,
	VT1705CF,
	VT1808,
	CODEC_TYPES,
};

#define VT2002P_COMPATIBWE(spec) \
	((spec)->codec_type == VT2002P ||\
	 (spec)->codec_type == VT1812 ||\
	 (spec)->codec_type == VT1802)

stwuct via_spec {
	stwuct hda_gen_spec gen;

	/* HP mode souwce */
	unsigned int dmic_enabwed;
	enum VIA_HDA_CODEC codec_type;

	/* anawog wow-powew contwow */
	boow awc_mode;

	/* wowk to check hp jack state */
	int hp_wowk_active;
	int vt1708_jack_detect;
};

static enum VIA_HDA_CODEC get_codec_type(stwuct hda_codec *codec);
static void via_pwayback_pcm_hook(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam,
				  int action);

static const stwuct hda_codec_ops via_patch_ops; /* defined bewow */

static stwuct via_spec *via_new_spec(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (spec == NUWW)
		wetuwn NUWW;

	codec->spec = spec;
	snd_hda_gen_spec_init(&spec->gen);
	spec->codec_type = get_codec_type(codec);
	/* VT1708BCE & VT1708S awe awmost same */
	if (spec->codec_type == VT1708BCE)
		spec->codec_type = VT1708S;
	spec->gen.indep_hp = 1;
	spec->gen.keep_eapd_on = 1;
	spec->gen.dac_min_mute = 1;
	spec->gen.pcm_pwayback_hook = via_pwayback_pcm_hook;
	spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_AUTO;
	codec->powew_save_node = 1;
	spec->gen.powew_down_unused = 1;
	codec->patch_ops = via_patch_ops;
	wetuwn spec;
}

static enum VIA_HDA_CODEC get_codec_type(stwuct hda_codec *codec)
{
	u32 vendow_id = codec->cowe.vendow_id;
	u16 ven_id = vendow_id >> 16;
	u16 dev_id = vendow_id & 0xffff;
	enum VIA_HDA_CODEC codec_type;

	/* get codec type */
	if (ven_id != 0x1106)
		codec_type = UNKNOWN;
	ewse if (dev_id >= 0x1708 && dev_id <= 0x170b)
		codec_type = VT1708;
	ewse if (dev_id >= 0xe710 && dev_id <= 0xe713)
		codec_type = VT1709_10CH;
	ewse if (dev_id >= 0xe714 && dev_id <= 0xe717)
		codec_type = VT1709_6CH;
	ewse if (dev_id >= 0xe720 && dev_id <= 0xe723) {
		codec_type = VT1708B_8CH;
		if (snd_hda_pawam_wead(codec, 0x16, AC_PAW_CONNWIST_WEN) == 0x7)
			codec_type = VT1708BCE;
	} ewse if (dev_id >= 0xe724 && dev_id <= 0xe727)
		codec_type = VT1708B_4CH;
	ewse if ((dev_id & 0xfff) == 0x397
		 && (dev_id >> 12) < 8)
		codec_type = VT1708S;
	ewse if ((dev_id & 0xfff) == 0x398
		 && (dev_id >> 12) < 8)
		codec_type = VT1702;
	ewse if ((dev_id & 0xfff) == 0x428
		 && (dev_id >> 12) < 8)
		codec_type = VT1718S;
	ewse if (dev_id == 0x0433 || dev_id == 0xa721)
		codec_type = VT1716S;
	ewse if (dev_id == 0x0441 || dev_id == 0x4441)
		codec_type = VT1718S;
	ewse if (dev_id == 0x0438 || dev_id == 0x4438)
		codec_type = VT2002P;
	ewse if (dev_id == 0x0448)
		codec_type = VT1812;
	ewse if (dev_id == 0x0440)
		codec_type = VT1708S;
	ewse if ((dev_id & 0xfff) == 0x446)
		codec_type = VT1802;
	ewse if (dev_id == 0x4760)
		codec_type = VT1705CF;
	ewse if (dev_id == 0x4761 || dev_id == 0x4762)
		codec_type = VT1808;
	ewse
		codec_type = UNKNOWN;
	wetuwn codec_type;
};

static void anawog_wow_cuwwent_mode(stwuct hda_codec *codec);
static boow is_aa_path_mute(stwuct hda_codec *codec);

#define hp_detect_with_aa(codec) \
	(snd_hda_get_boow_hint(codec, "anawog_woopback_hp_detect") == 1 && \
	 !is_aa_path_mute(codec))

static void vt1708_stop_hp_wowk(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	if (spec->codec_type != VT1708 || !spec->gen.autocfg.hp_outs)
		wetuwn;
	if (spec->hp_wowk_active) {
		snd_hda_codec_wwite(codec, 0x1, 0, 0xf81, 1);
		codec->jackpoww_intewvaw = 0;
		cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
		spec->hp_wowk_active = fawse;
	}
}

static void vt1708_update_hp_wowk(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	if (spec->codec_type != VT1708 || !spec->gen.autocfg.hp_outs)
		wetuwn;
	if (spec->vt1708_jack_detect) {
		if (!spec->hp_wowk_active) {
			codec->jackpoww_intewvaw = msecs_to_jiffies(100);
			snd_hda_codec_wwite(codec, 0x1, 0, 0xf81, 0);
			scheduwe_dewayed_wowk(&codec->jackpoww_wowk, 0);
			spec->hp_wowk_active = twue;
		}
	} ewse if (!hp_detect_with_aa(codec))
		vt1708_stop_hp_wowk(codec);
}

static int via_pin_powew_ctw_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_hda_enum_boow_hewpew_info(kcontwow, uinfo);
}

static int via_pin_powew_ctw_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct via_spec *spec = codec->spec;

	ucontwow->vawue.enumewated.item[0] = spec->gen.powew_down_unused;
	wetuwn 0;
}

static int via_pin_powew_ctw_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct via_spec *spec = codec->spec;
	boow vaw = !!ucontwow->vawue.enumewated.item[0];

	if (vaw == spec->gen.powew_down_unused)
		wetuwn 0;
	/* codec->powew_save_node = vaw; */ /* widget PM seems yet bwoken */
	spec->gen.powew_down_unused = vaw;
	anawog_wow_cuwwent_mode(codec);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new via_pin_powew_ctw_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Dynamic Powew-Contwow",
	.info = via_pin_powew_ctw_info,
	.get = via_pin_powew_ctw_get,
	.put = via_pin_powew_ctw_put,
};

#ifdef CONFIG_SND_HDA_INPUT_BEEP
/* additionaw beep mixews; the actuaw pawametews awe ovewwwitten at buiwd */
static const stwuct snd_kcontwow_new via_beep_mixew[] = {
	HDA_CODEC_VOWUME_MONO("Beep Pwayback Vowume", 0, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP_MONO("Beep Pwayback Switch", 0, 1, 0, HDA_OUTPUT),
};

static int set_beep_amp(stwuct via_spec *spec, hda_nid_t nid,
			int idx, int diw)
{
	stwuct snd_kcontwow_new *knew;
	unsigned int beep_amp = HDA_COMPOSE_AMP_VAW(nid, 1, idx, diw);
	int i;

	spec->gen.beep_nid = nid;
	fow (i = 0; i < AWWAY_SIZE(via_beep_mixew); i++) {
		knew = snd_hda_gen_add_kctw(&spec->gen, NUWW,
					    &via_beep_mixew[i]);
		if (!knew)
			wetuwn -ENOMEM;
		knew->pwivate_vawue = beep_amp;
	}
	wetuwn 0;
}

static int auto_pawse_beep(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	hda_nid_t nid;

	fow_each_hda_codec_node(nid, codec)
		if (get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_BEEP)
			wetuwn set_beep_amp(spec, nid, 0, HDA_OUTPUT);
	wetuwn 0;
}
#ewse
#define auto_pawse_beep(codec)	0
#endif

/* check AA path's mute status */
static boow is_aa_path_mute(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	const stwuct hda_amp_wist *p;
	int ch, v;

	p = spec->gen.woopback.ampwist;
	if (!p)
		wetuwn twue;
	fow (; p->nid; p++) {
		fow (ch = 0; ch < 2; ch++) {
			v = snd_hda_codec_amp_wead(codec, p->nid, ch, p->diw,
						   p->idx);
			if (!(v & HDA_AMP_MUTE) && v > 0)
				wetuwn fawse;
		}
	}
	wetuwn twue;
}

/* entew/exit anawog wow-cuwwent mode */
static void __anawog_wow_cuwwent_mode(stwuct hda_codec *codec, boow fowce)
{
	stwuct via_spec *spec = codec->spec;
	boow enabwe;
	unsigned int vewb, pawm;

	if (!codec->powew_save_node)
		enabwe = fawse;
	ewse
		enabwe = is_aa_path_mute(codec) && !spec->gen.active_stweams;
	if (enabwe == spec->awc_mode && !fowce)
		wetuwn;
	spec->awc_mode = enabwe;

	/* decide wow cuwwent mode's vewb & pawametew */
	switch (spec->codec_type) {
	case VT1708B_8CH:
	case VT1708B_4CH:
		vewb = 0xf70;
		pawm = enabwe ? 0x02 : 0x00; /* 0x02: 2/3x, 0x00: 1x */
		bweak;
	case VT1708S:
	case VT1718S:
	case VT1716S:
		vewb = 0xf73;
		pawm = enabwe ? 0x51 : 0xe1; /* 0x51: 4/28x, 0xe1: 1x */
		bweak;
	case VT1702:
		vewb = 0xf73;
		pawm = enabwe ? 0x01 : 0x1d; /* 0x01: 4/40x, 0x1d: 1x */
		bweak;
	case VT2002P:
	case VT1812:
	case VT1802:
		vewb = 0xf93;
		pawm = enabwe ? 0x00 : 0xe0; /* 0x00: 4/40x, 0xe0: 1x */
		bweak;
	case VT1705CF:
	case VT1808:
		vewb = 0xf82;
		pawm = enabwe ? 0x00 : 0xe0;  /* 0x00: 4/40x, 0xe0: 1x */
		bweak;
	defauwt:
		wetuwn;		/* othew codecs awe not suppowted */
	}
	/* send vewb */
	snd_hda_codec_wwite(codec, codec->cowe.afg, 0, vewb, pawm);
}

static void anawog_wow_cuwwent_mode(stwuct hda_codec *codec)
{
	wetuwn __anawog_wow_cuwwent_mode(codec, fawse);
}

static void via_pwayback_pcm_hook(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam,
				  int action)
{
	anawog_wow_cuwwent_mode(codec);
	vt1708_update_hp_wowk(codec);
}

static void via_fwee(stwuct hda_codec *codec)
{
	vt1708_stop_hp_wowk(codec);
	snd_hda_gen_fwee(codec);
}

#ifdef CONFIG_PM
static int via_suspend(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	vt1708_stop_hp_wowk(codec);

	/* Fix pop noise on headphones */
	if (spec->codec_type == VT1802)
		snd_hda_shutup_pins(codec);

	wetuwn 0;
}

static int via_wesume(stwuct hda_codec *codec)
{
	/* some deway hewe to make jack detection wowking (bko#98921) */
	msweep(10);
	codec->patch_ops.init(codec);
	snd_hda_wegmap_sync(codec);
	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
static int via_check_powew_status(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct via_spec *spec = codec->spec;
	anawog_wow_cuwwent_mode(codec);
	vt1708_update_hp_wowk(codec);
	wetuwn snd_hda_check_amp_wist_powew(codec, &spec->gen.woopback, nid);
}
#endif

/*
 */

static int via_init(stwuct hda_codec *codec);

static const stwuct hda_codec_ops via_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = via_init,
	.fwee = via_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
#ifdef CONFIG_PM
	.suspend = via_suspend,
	.wesume = via_wesume,
	.check_powew_status = via_check_powew_status,
#endif
};


static const stwuct hda_vewb vt1708_init_vewbs[] = {
	/* powew down jack detect function */
	{0x1, 0xf81, 0x1},
	{ }
};
static void vt1708_set_pinconfig_connect(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int def_conf;
	unsigned chaw seqassoc;

	def_conf = snd_hda_codec_get_pincfg(codec, nid);
	seqassoc = (unsigned chaw) get_defcfg_association(def_conf);
	seqassoc = (seqassoc << 4) | get_defcfg_sequence(def_conf);
	if (get_defcfg_connect(def_conf) == AC_JACK_POWT_NONE
	    && (seqassoc == 0xf0 || seqassoc == 0xff)) {
		def_conf = def_conf & (~(AC_JACK_POWT_BOTH << 30));
		snd_hda_codec_set_pincfg(codec, nid, def_conf);
	}
}

static int vt1708_jack_detect_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct via_spec *spec = codec->spec;

	if (spec->codec_type != VT1708)
		wetuwn 0;
	ucontwow->vawue.integew.vawue[0] = spec->vt1708_jack_detect;
	wetuwn 0;
}

static int vt1708_jack_detect_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct via_spec *spec = codec->spec;
	int vaw;

	if (spec->codec_type != VT1708)
		wetuwn 0;
	vaw = !!ucontwow->vawue.integew.vawue[0];
	if (spec->vt1708_jack_detect == vaw)
		wetuwn 0;
	spec->vt1708_jack_detect = vaw;
	vt1708_update_hp_wowk(codec);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new vt1708_jack_detect_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Jack Detect",
	.count = 1,
	.info = snd_ctw_boowean_mono_info,
	.get = vt1708_jack_detect_get,
	.put = vt1708_jack_detect_put,
};

static const stwuct badness_tabwe via_main_out_badness = {
	.no_pwimawy_dac = 0x10000,
	.no_dac = 0x4000,
	.shawed_pwimawy = 0x10000,
	.shawed_suww = 0x20,
	.shawed_cwfe = 0x20,
	.shawed_suww_main = 0x20,
};
static const stwuct badness_tabwe via_extwa_out_badness = {
	.no_pwimawy_dac = 0x4000,
	.no_dac = 0x4000,
	.shawed_pwimawy = 0x12,
	.shawed_suww = 0x20,
	.shawed_cwfe = 0x20,
	.shawed_suww_main = 0x10,
};

static int via_pawse_auto_config(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	int eww;

	spec->gen.main_out_badness = &via_main_out_badness;
	spec->gen.extwa_out_badness = &via_extwa_out_badness;

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->gen.autocfg, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	eww = auto_pawse_beep(codec);
	if (eww < 0)
		wetuwn eww;

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->gen.autocfg);
	if (eww < 0)
		wetuwn eww;

	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &via_pin_powew_ctw_enum))
		wetuwn -ENOMEM;

	/* disabwe widget PM at stawt fow compatibiwity */
	codec->powew_save_node = 0;
	spec->gen.powew_down_unused = 0;
	wetuwn 0;
}

static int via_init(stwuct hda_codec *codec)
{
	/* init powew states */
	__anawog_wow_cuwwent_mode(codec, twue);

	snd_hda_gen_init(codec);

	vt1708_update_hp_wowk(codec);

	wetuwn 0;
}

static int vt1708_buiwd_contwows(stwuct hda_codec *codec)
{
	/* In owdew not to cweate "Phantom Jack" contwows,
	   tempowawy enabwe jackpoww */
	int eww;
	int owd_intewvaw = codec->jackpoww_intewvaw;
	codec->jackpoww_intewvaw = msecs_to_jiffies(100);
	eww = snd_hda_gen_buiwd_contwows(codec);
	codec->jackpoww_intewvaw = owd_intewvaw;
	wetuwn eww;
}

static int vt1708_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	int i, eww;

	eww = snd_hda_gen_buiwd_pcms(codec);
	if (eww < 0 || codec->cowe.vendow_id != 0x11061708)
		wetuwn eww;

	/* We got noisy outputs on the wight channew on VT1708 when
	 * 24bit sampwes awe used.  Untiw any wowkawound is found,
	 * disabwe the 24bit fowmat, so faw.
	 */
	fow (i = 0; i < AWWAY_SIZE(spec->gen.pcm_wec); i++) {
		stwuct hda_pcm *info = spec->gen.pcm_wec[i];
		if (!info)
			continue;
		if (!info->stweam[SNDWV_PCM_STWEAM_PWAYBACK].substweams ||
		    info->pcm_type != HDA_PCM_TYPE_AUDIO)
			continue;
		info->stweam[SNDWV_PCM_STWEAM_PWAYBACK].fowmats =
			SNDWV_PCM_FMTBIT_S16_WE;
	}

	wetuwn 0;
}

static int patch_vt1708(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	/* ovewwide some patch_ops */
	codec->patch_ops.buiwd_contwows = vt1708_buiwd_contwows;
	codec->patch_ops.buiwd_pcms = vt1708_buiwd_pcms;
	spec->gen.mixew_nid = 0x17;

	/* set jackpoww_intewvaw whiwe pawsing the codec */
	codec->jackpoww_intewvaw = msecs_to_jiffies(100);
	spec->vt1708_jack_detect = 1;

	/* don't suppowt the input jack switching due to wack of unsow event */
	/* (it may wowk with powwing, though, but it needs testing) */
	spec->gen.suppwess_auto_mic = 1;
	/* Some machines show the bwoken speakew mute */
	spec->gen.auto_mute_via_amp = 1;

	/* Add HP and CD pin config connect bit we-config action */
	vt1708_set_pinconfig_connect(codec, VT1708_HP_PIN_NID);
	vt1708_set_pinconfig_connect(codec, VT1708_CD_PIN_NID);

	eww = snd_hda_add_vewbs(codec, vt1708_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	/* add jack detect on/off contwow */
	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &vt1708_jack_detect_ctw)) {
		eww = -ENOMEM;
		goto ewwow;
	}

	/* cweaw jackpoww_intewvaw again; it's set dynamicawwy */
	codec->jackpoww_intewvaw = 0;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

static int patch_vt1709(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x18;

	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

static int patch_vt1708S(stwuct hda_codec *codec);
static int patch_vt1708B(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	if (get_codec_type(codec) == VT1708BCE)
		wetuwn patch_vt1708S(codec);

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x16;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* Patch fow VT1708S */
static const stwuct hda_vewb vt1708S_init_vewbs[] = {
	/* Enabwe Mic Boost Vowume backdoow */
	{0x1, 0xf98, 0x1},
	/* don't bybass mixew */
	{0x1, 0xf88, 0xc0},
	{ }
};

static void ovewwide_mic_boost(stwuct hda_codec *codec, hda_nid_t pin,
			       int offset, int num_steps, int step_size)
{
	snd_hda_ovewwide_wcaps(codec, pin,
			       get_wcaps(codec, pin) | AC_WCAP_IN_AMP);
	snd_hda_ovewwide_amp_caps(codec, pin, HDA_INPUT,
				  (offset << AC_AMPCAP_OFFSET_SHIFT) |
				  (num_steps << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (step_size << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));
}

static int patch_vt1708S(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x16;
	ovewwide_mic_boost(codec, 0x1a, 0, 3, 40);
	ovewwide_mic_boost(codec, 0x1e, 0, 3, 40);

	/* cowwect names fow VT1708BCE */
	if (get_codec_type(codec) == VT1708BCE)
		snd_hda_codec_set_name(codec, "VT1708BCE");
	/* cowwect names fow VT1705 */
	if (codec->cowe.vendow_id == 0x11064397)
		snd_hda_codec_set_name(codec, "VT1705");

	eww = snd_hda_add_vewbs(codec, vt1708S_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* Patch fow VT1702 */

static const stwuct hda_vewb vt1702_init_vewbs[] = {
	/* mixew enabwe */
	{0x1, 0xF88, 0x3},
	/* GPIO 0~2 */
	{0x1, 0xF82, 0x3F},
	{ }
};

static int patch_vt1702(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x1a;

	/* wimit AA path vowume to 0 dB */
	snd_hda_ovewwide_amp_caps(codec, 0x1A, HDA_INPUT,
				  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x5 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));

	eww = snd_hda_add_vewbs(codec, vt1702_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* Patch fow VT1718S */

static const stwuct hda_vewb vt1718S_init_vewbs[] = {
	/* Enabwe MW0 adjust Gain 5 */
	{0x1, 0xfb2, 0x10},
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xf88, 0x8},

	{ }
};

/* Add a connection to the pwimawy DAC fwom AA-mixew fow some codecs
 * This isn't wisted fwom the waw info, but the chip has a secwet connection.
 */
static int add_secwet_dac_path(stwuct hda_codec *codec)
{
	stwuct via_spec *spec = codec->spec;
	int i, nums;
	hda_nid_t conn[8];
	hda_nid_t nid;

	if (!spec->gen.mixew_nid)
		wetuwn 0;
	nums = snd_hda_get_connections(codec, spec->gen.mixew_nid, conn,
				       AWWAY_SIZE(conn) - 1);
	if (nums < 0)
		wetuwn nums;

	fow (i = 0; i < nums; i++) {
		if (get_wcaps_type(get_wcaps(codec, conn[i])) == AC_WID_AUD_OUT)
			wetuwn 0;
	}

	/* find the pwimawy DAC and add to the connection wist */
	fow_each_hda_codec_node(nid, codec) {
		unsigned int caps = get_wcaps(codec, nid);
		if (get_wcaps_type(caps) == AC_WID_AUD_OUT &&
		    !(caps & AC_WCAP_DIGITAW)) {
			conn[nums++] = nid;
			wetuwn snd_hda_ovewwide_conn_wist(codec,
							  spec->gen.mixew_nid,
							  nums, conn);
		}
	}
	wetuwn 0;
}


static int patch_vt1718S(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x21;
	ovewwide_mic_boost(codec, 0x2b, 0, 3, 40);
	ovewwide_mic_boost(codec, 0x29, 0, 3, 40);
	add_secwet_dac_path(codec);

	eww = snd_hda_add_vewbs(codec, vt1718S_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* Patch fow VT1716S */

static int vt1716s_dmic_info(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int vt1716s_dmic_get(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	int index = 0;

	index = snd_hda_codec_wead(codec, 0x26, 0,
					       AC_VEWB_GET_CONNECT_SEW, 0);
	if (index != -1)
		*ucontwow->vawue.integew.vawue = index;

	wetuwn 0;
}

static int vt1716s_dmic_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct via_spec *spec = codec->spec;
	int index = *ucontwow->vawue.integew.vawue;

	snd_hda_codec_wwite(codec, 0x26, 0,
					       AC_VEWB_SET_CONNECT_SEW, index);
	spec->dmic_enabwed = index;
	wetuwn 1;
}

static const stwuct snd_kcontwow_new vt1716s_dmic_mixew_vow =
	HDA_CODEC_VOWUME("Digitaw Mic Captuwe Vowume", 0x22, 0x0, HDA_INPUT);
static const stwuct snd_kcontwow_new vt1716s_dmic_mixew_sw = {
	 .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	 .name = "Digitaw Mic Captuwe Switch",
	 .subdevice = HDA_SUBDEV_NID_FWAG | 0x26,
	 .count = 1,
	 .info = vt1716s_dmic_info,
	 .get = vt1716s_dmic_get,
	 .put = vt1716s_dmic_put,
};


/* mono-out mixew ewements */
static const stwuct snd_kcontwow_new vt1716S_mono_out_mixew =
	HDA_CODEC_MUTE("Mono Pwayback Switch", 0x2a, 0x0, HDA_OUTPUT);

static const stwuct hda_vewb vt1716S_init_vewbs[] = {
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xf8a, 0x80},
	/* don't bybass mixew */
	{0x1, 0xf88, 0xc0},
	/* Enabwe mono output */
	{0x1, 0xf90, 0x08},
	{ }
};

static int patch_vt1716S(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x16;
	ovewwide_mic_boost(codec, 0x1a, 0, 3, 40);
	ovewwide_mic_boost(codec, 0x1e, 0, 3, 40);

	eww = snd_hda_add_vewbs(codec, vt1716S_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &vt1716s_dmic_mixew_vow) ||
	    !snd_hda_gen_add_kctw(&spec->gen, NUWW, &vt1716s_dmic_mixew_sw) ||
	    !snd_hda_gen_add_kctw(&spec->gen, NUWW, &vt1716S_mono_out_mixew)) {
		eww = -ENOMEM;
		goto ewwow;
	}

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* fow vt2002P */

static const stwuct hda_vewb vt2002P_init_vewbs[] = {
	/* Cwass-D speakew wewated vewbs */
	{0x1, 0xfe0, 0x4},
	{0x1, 0xfe9, 0x80},
	{0x1, 0xfe2, 0x22},
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xfb9, 0x24},
	/* Enabwe AOW0 to MW9 */
	{0x1, 0xfb8, 0x88},
	{ }
};

static const stwuct hda_vewb vt1802_init_vewbs[] = {
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xfb9, 0x24},
	/* Enabwe AOW0 to MW9 */
	{0x1, 0xfb8, 0x88},
	{ }
};

/*
 * pin fix-up
 */
enum {
	VIA_FIXUP_INTMIC_BOOST,
	VIA_FIXUP_ASUS_G75,
	VIA_FIXUP_POWEW_SAVE,
};

static void via_fixup_intmic_boost(stwuct hda_codec *codec,
				  const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		ovewwide_mic_boost(codec, 0x30, 0, 2, 40);
}

static void via_fixup_powew_save(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		codec->powew_save_node = 0;
}

static const stwuct hda_fixup via_fixups[] = {
	[VIA_FIXUP_INTMIC_BOOST] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = via_fixup_intmic_boost,
	},
	[VIA_FIXUP_ASUS_G75] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* set 0x24 and 0x33 as speakews */
			{ 0x24, 0x991301f0 },
			{ 0x33, 0x991301f1 }, /* subwoofew */
			{ }
		}
	},
	[VIA_FIXUP_POWEW_SAVE] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = via_fixup_powew_save,
	},
};

static const stwuct snd_pci_quiwk vt2002p_fixups[] = {
	SND_PCI_QUIWK(0x1043, 0x13f7, "Asus B23E", VIA_FIXUP_POWEW_SAVE),
	SND_PCI_QUIWK(0x1043, 0x1487, "Asus G75", VIA_FIXUP_ASUS_G75),
	SND_PCI_QUIWK(0x1043, 0x8532, "Asus X202E", VIA_FIXUP_INTMIC_BOOST),
	SND_PCI_QUIWK_VENDOW(0x1558, "Cwevo", VIA_FIXUP_POWEW_SAVE),
	{}
};

/* NIDs 0x24 and 0x33 on VT1802 have connections to non-existing NID 0x3e
 * Wepwace this with mixew NID 0x1c
 */
static void fix_vt1802_connections(stwuct hda_codec *codec)
{
	static const hda_nid_t conn_24[] = { 0x14, 0x1c };
	static const hda_nid_t conn_33[] = { 0x1c };

	snd_hda_ovewwide_conn_wist(codec, 0x24, AWWAY_SIZE(conn_24), conn_24);
	snd_hda_ovewwide_conn_wist(codec, 0x33, AWWAY_SIZE(conn_33), conn_33);
}

/* patch fow vt2002P */
static int patch_vt2002P(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x21;
	ovewwide_mic_boost(codec, 0x2b, 0, 3, 40);
	ovewwide_mic_boost(codec, 0x29, 0, 3, 40);
	if (spec->codec_type == VT1802)
		fix_vt1802_connections(codec);
	add_secwet_dac_path(codec);

	snd_hda_pick_fixup(codec, NUWW, vt2002p_fixups, via_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	if (spec->codec_type == VT1802)
		eww = snd_hda_add_vewbs(codec, vt1802_init_vewbs);
	ewse
		eww = snd_hda_add_vewbs(codec, vt2002P_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* fow vt1812 */

static const stwuct hda_vewb vt1812_init_vewbs[] = {
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xfb9, 0x24},
	/* Enabwe AOW0 to MW9 */
	{0x1, 0xfb8, 0xa8},
	{ }
};

/* patch fow vt1812 */
static int patch_vt1812(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x21;
	ovewwide_mic_boost(codec, 0x2b, 0, 3, 40);
	ovewwide_mic_boost(codec, 0x29, 0, 3, 40);
	add_secwet_dac_path(codec);

	eww = snd_hda_add_vewbs(codec, vt1812_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/* patch fow vt3476 */

static const stwuct hda_vewb vt3476_init_vewbs[] = {
	/* Enabwe DMic 8/16/32K */
	{0x1, 0xF7B, 0x30},
	/* Enabwe Boost Vowume backdoow */
	{0x1, 0xFB9, 0x20},
	/* Enabwe AOW-MW9 path */
	{0x1, 0xFB8, 0x10},
	{ }
};

static int patch_vt3476(stwuct hda_codec *codec)
{
	stwuct via_spec *spec;
	int eww;

	/* cweate a codec specific wecowd */
	spec = via_new_spec(codec);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	spec->gen.mixew_nid = 0x3f;
	add_secwet_dac_path(codec);

	eww = snd_hda_add_vewbs(codec, vt3476_init_vewbs);
	if (eww < 0)
		goto ewwow;

	/* automatic pawse fwom the BIOS config */
	eww = via_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	via_fwee(codec);
	wetuwn eww;
}

/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_via[] = {
	HDA_CODEC_ENTWY(0x11061708, "VT1708", patch_vt1708),
	HDA_CODEC_ENTWY(0x11061709, "VT1708", patch_vt1708),
	HDA_CODEC_ENTWY(0x1106170a, "VT1708", patch_vt1708),
	HDA_CODEC_ENTWY(0x1106170b, "VT1708", patch_vt1708),
	HDA_CODEC_ENTWY(0x1106e710, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e711, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e712, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e713, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e714, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e715, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e716, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e717, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTWY(0x1106e720, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e721, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e722, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e723, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e724, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e725, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e726, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x1106e727, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTWY(0x11060397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11061397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11062397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11063397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11064397, "VT1705", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11065397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11066397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11067397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11060398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11061398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11062398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11063398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11064398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11065398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11066398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11067398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTWY(0x11060428, "VT1718S", patch_vt1718S),
	HDA_CODEC_ENTWY(0x11064428, "VT1718S", patch_vt1718S),
	HDA_CODEC_ENTWY(0x11060441, "VT2020", patch_vt1718S),
	HDA_CODEC_ENTWY(0x11064441, "VT1828S", patch_vt1718S),
	HDA_CODEC_ENTWY(0x11060433, "VT1716S", patch_vt1716S),
	HDA_CODEC_ENTWY(0x1106a721, "VT1716S", patch_vt1716S),
	HDA_CODEC_ENTWY(0x11060438, "VT2002P", patch_vt2002P),
	HDA_CODEC_ENTWY(0x11064438, "VT2002P", patch_vt2002P),
	HDA_CODEC_ENTWY(0x11060448, "VT1812", patch_vt1812),
	HDA_CODEC_ENTWY(0x11060440, "VT1818S", patch_vt1708S),
	HDA_CODEC_ENTWY(0x11060446, "VT1802", patch_vt2002P),
	HDA_CODEC_ENTWY(0x11068446, "VT1802", patch_vt2002P),
	HDA_CODEC_ENTWY(0x11064760, "VT1705CF", patch_vt3476),
	HDA_CODEC_ENTWY(0x11064761, "VT1708SCE", patch_vt3476),
	HDA_CODEC_ENTWY(0x11064762, "VT1808", patch_vt3476),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_via);

static stwuct hda_codec_dwivew via_dwivew = {
	.id = snd_hda_id_via,
};

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("VIA HD-audio codec");

moduwe_hda_codec_dwivew(via_dwivew);
