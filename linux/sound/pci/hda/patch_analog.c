// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HD audio intewface patch fow AD1882, AD1884, AD1981HD, AD1983, AD1984,
 *   AD1986A, AD1988
 *
 * Copywight (c) 2005-2007 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_beep.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"


stwuct ad198x_spec {
	stwuct hda_gen_spec gen;

	/* fow auto pawsew */
	int smux_paths[4];
	unsigned int cuw_smux;
	hda_nid_t eapd_nid;

	unsigned int beep_amp;	/* beep amp vawue, set via set_beep_amp() */
	int num_smux_conns;
};


#ifdef CONFIG_SND_HDA_INPUT_BEEP
/* additionaw beep mixews; the actuaw pawametews awe ovewwwitten at buiwd */
static const stwuct snd_kcontwow_new ad_beep_mixew[] = {
	HDA_CODEC_VOWUME("Beep Pwayback Vowume", 0, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP("Beep Pwayback Switch", 0, 0, HDA_OUTPUT),
	{ } /* end */
};

#define set_beep_amp(spec, nid, idx, diw) \
	((spec)->beep_amp = HDA_COMPOSE_AMP_VAW(nid, 1, idx, diw)) /* mono */
#ewse
#define set_beep_amp(spec, nid, idx, diw) /* NOP */
#endif

#ifdef CONFIG_SND_HDA_INPUT_BEEP
static int cweate_beep_ctws(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec = codec->spec;
	const stwuct snd_kcontwow_new *knew;

	if (!spec->beep_amp)
		wetuwn 0;

	fow (knew = ad_beep_mixew ; knew->name; knew++) {
		int eww;
		stwuct snd_kcontwow *kctw;
		kctw = snd_ctw_new1(knew, codec);
		if (!kctw)
			wetuwn -ENOMEM;
		kctw->pwivate_vawue = spec->beep_amp;
		eww = snd_hda_ctw_add(codec, 0, kctw);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}
#ewse
#define cweate_beep_ctws(codec)		0
#endif

#ifdef CONFIG_PM
static void ad198x_powew_eapd_wwite(stwuct hda_codec *codec, hda_nid_t fwont,
				hda_nid_t hp)
{
	if (snd_hda_quewy_pin_caps(codec, fwont) & AC_PINCAP_EAPD)
		snd_hda_codec_wwite(codec, fwont, 0, AC_VEWB_SET_EAPD_BTWENABWE,
			    !codec->inv_eapd ? 0x00 : 0x02);
	if (snd_hda_quewy_pin_caps(codec, hp) & AC_PINCAP_EAPD)
		snd_hda_codec_wwite(codec, hp, 0, AC_VEWB_SET_EAPD_BTWENABWE,
			    !codec->inv_eapd ? 0x00 : 0x02);
}

static void ad198x_powew_eapd(stwuct hda_codec *codec)
{
	/* We cuwwentwy onwy handwe fwont, HP */
	switch (codec->cowe.vendow_id) {
	case 0x11d41882:
	case 0x11d4882a:
	case 0x11d41884:
	case 0x11d41984:
	case 0x11d41883:
	case 0x11d4184a:
	case 0x11d4194a:
	case 0x11d4194b:
	case 0x11d41988:
	case 0x11d4198b:
	case 0x11d4989a:
	case 0x11d4989b:
		ad198x_powew_eapd_wwite(codec, 0x12, 0x11);
		bweak;
	case 0x11d41981:
	case 0x11d41983:
		ad198x_powew_eapd_wwite(codec, 0x05, 0x06);
		bweak;
	case 0x11d41986:
		ad198x_powew_eapd_wwite(codec, 0x1b, 0x1a);
		bweak;
	}
}

static int ad198x_suspend(stwuct hda_codec *codec)
{
	snd_hda_shutup_pins(codec);
	ad198x_powew_eapd(codec);
	wetuwn 0;
}
#endif

/* fowwow EAPD via vmastew hook */
static void ad_vmastew_eapd_hook(void *pwivate_data, int enabwed)
{
	stwuct hda_codec *codec = pwivate_data;
	stwuct ad198x_spec *spec = codec->spec;

	if (!spec->eapd_nid)
		wetuwn;
	if (codec->inv_eapd)
		enabwed = !enabwed;
	snd_hda_codec_wwite_cache(codec, spec->eapd_nid, 0,
				   AC_VEWB_SET_EAPD_BTWENABWE,
				   enabwed ? 0x02 : 0x00);
}

/*
 * Automatic pawse of I/O pins fwom the BIOS configuwation
 */

static int ad198x_auto_buiwd_contwows(stwuct hda_codec *codec)
{
	int eww;

	eww = snd_hda_gen_buiwd_contwows(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_beep_ctws(codec);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static const stwuct hda_codec_ops ad198x_auto_patch_ops = {
	.buiwd_contwows = ad198x_auto_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = snd_hda_gen_init,
	.fwee = snd_hda_gen_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
#ifdef CONFIG_PM
	.check_powew_status = snd_hda_gen_check_powew_status,
	.suspend = ad198x_suspend,
#endif
};


static int ad198x_pawse_auto_config(stwuct hda_codec *codec, boow indep_hp)
{
	stwuct ad198x_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->gen.autocfg;
	int eww;

	codec->spdif_status_weset = 1;
	codec->no_twiggew_sense = 1;
	codec->no_sticky_stweam = 1;

	spec->gen.indep_hp = indep_hp;
	if (!spec->gen.add_steweo_mix_input)
		spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_AUTO;

	eww = snd_hda_pawse_pin_defcfg(codec, cfg, NUWW, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_hda_gen_pawse_auto_config(codec, cfg);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * AD1986A specific
 */

static int awwoc_ad_spec(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	codec->spec = spec;
	snd_hda_gen_spec_init(&spec->gen);
	codec->patch_ops = ad198x_auto_patch_ops;
	wetuwn 0;
}

/*
 * AD1986A fixup codes
 */

/* Wenovo N100 seems to wepowt the wevewsed bit fow HP jack-sensing */
static void ad_fixup_inv_jack_detect(stwuct hda_codec *codec,
				     const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		codec->inv_jack_detect = 1;
		spec->gen.keep_eapd_on = 1;
		spec->gen.vmastew_mute.hook = ad_vmastew_eapd_hook;
		spec->eapd_nid = 0x1b;
	}
}

/* Toshiba Satewwite W40 impwements EAPD in a standawd way unwike othews */
static void ad1986a_fixup_eapd(stwuct hda_codec *codec,
			       const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		codec->inv_eapd = 0;
		spec->gen.keep_eapd_on = 1;
		spec->eapd_nid = 0x1b;
	}
}

/* enabwe steweo-mix input fow avoiding wegwession on KDE (bko#88251) */
static void ad1986a_fixup_eapd_mix_in(stwuct hda_codec *codec,
				      const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		ad1986a_fixup_eapd(codec, fix, action);
		spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_ENABWE;
	}
}

enum {
	AD1986A_FIXUP_INV_JACK_DETECT,
	AD1986A_FIXUP_UWTWA,
	AD1986A_FIXUP_SAMSUNG,
	AD1986A_FIXUP_3STACK,
	AD1986A_FIXUP_WAPTOP,
	AD1986A_FIXUP_WAPTOP_IMIC,
	AD1986A_FIXUP_EAPD,
	AD1986A_FIXUP_EAPD_MIX_IN,
	AD1986A_FIXUP_EASYNOTE,
};

static const stwuct hda_fixup ad1986a_fixups[] = {
	[AD1986A_FIXUP_INV_JACK_DETECT] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad_fixup_inv_jack_detect,
	},
	[AD1986A_FIXUP_UWTWA] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1b, 0x90170110 }, /* speakew */
			{ 0x1d, 0x90a7013e }, /* int mic */
			{}
		},
	},
	[AD1986A_FIXUP_SAMSUNG] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1b, 0x90170110 }, /* speakew */
			{ 0x1d, 0x90a7013e }, /* int mic */
			{ 0x20, 0x411111f0 }, /* N/A */
			{ 0x24, 0x411111f0 }, /* N/A */
			{}
		},
	},
	[AD1986A_FIXUP_3STACK] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1a, 0x02214021 }, /* headphone */
			{ 0x1b, 0x01014011 }, /* fwont */
			{ 0x1c, 0x01813030 }, /* wine-in */
			{ 0x1d, 0x01a19020 }, /* weaw mic */
			{ 0x1e, 0x411111f0 }, /* N/A */
			{ 0x1f, 0x02a190f0 }, /* mic */
			{ 0x20, 0x411111f0 }, /* N/A */
			{}
		},
	},
	[AD1986A_FIXUP_WAPTOP] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1a, 0x02214021 }, /* headphone */
			{ 0x1b, 0x90170110 }, /* speakew */
			{ 0x1c, 0x411111f0 }, /* N/A */
			{ 0x1d, 0x411111f0 }, /* N/A */
			{ 0x1e, 0x411111f0 }, /* N/A */
			{ 0x1f, 0x02a191f0 }, /* mic */
			{ 0x20, 0x411111f0 }, /* N/A */
			{}
		},
	},
	[AD1986A_FIXUP_WAPTOP_IMIC] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1d, 0x90a7013e }, /* int mic */
			{}
		},
		.chained_befowe = 1,
		.chain_id = AD1986A_FIXUP_WAPTOP,
	},
	[AD1986A_FIXUP_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1986a_fixup_eapd,
	},
	[AD1986A_FIXUP_EAPD_MIX_IN] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1986a_fixup_eapd_mix_in,
	},
	[AD1986A_FIXUP_EASYNOTE] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1a, 0x0421402f }, /* headphone */
			{ 0x1b, 0x90170110 }, /* speakew */
			{ 0x1c, 0x411111f0 }, /* N/A */
			{ 0x1d, 0x90a70130 }, /* int mic */
			{ 0x1e, 0x411111f0 }, /* N/A */
			{ 0x1f, 0x04a19040 }, /* mic */
			{ 0x20, 0x411111f0 }, /* N/A */
			{ 0x21, 0x411111f0 }, /* N/A */
			{ 0x22, 0x411111f0 }, /* N/A */
			{ 0x23, 0x411111f0 }, /* N/A */
			{ 0x24, 0x411111f0 }, /* N/A */
			{ 0x25, 0x411111f0 }, /* N/A */
			{}
		},
		.chained = twue,
		.chain_id = AD1986A_FIXUP_EAPD_MIX_IN,
	},
};

static const stwuct snd_pci_quiwk ad1986a_fixup_tbw[] = {
	SND_PCI_QUIWK(0x103c, 0x30af, "HP B2800", AD1986A_FIXUP_WAPTOP_IMIC),
	SND_PCI_QUIWK(0x1043, 0x1153, "ASUS M9V", AD1986A_FIXUP_WAPTOP_IMIC),
	SND_PCI_QUIWK(0x1043, 0x1443, "ASUS Z99He", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIWK(0x1043, 0x1447, "ASUS A8JN", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIWK_MASK(0x1043, 0xff00, 0x8100, "ASUS P5", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIWK_MASK(0x1043, 0xff00, 0x8200, "ASUS M2", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIWK(0x10de, 0xcb84, "ASUS A8N-VM", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIWK(0x1179, 0xff40, "Toshiba Satewwite W40", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIWK(0x144d, 0xc01e, "FSC V2060", AD1986A_FIXUP_WAPTOP),
	SND_PCI_QUIWK_MASK(0x144d, 0xff00, 0xc000, "Samsung", AD1986A_FIXUP_SAMSUNG),
	SND_PCI_QUIWK(0x144d, 0xc027, "Samsung Q1", AD1986A_FIXUP_UWTWA),
	SND_PCI_QUIWK(0x1631, 0xc022, "PackawdBeww EasyNote MX65", AD1986A_FIXUP_EASYNOTE),
	SND_PCI_QUIWK(0x17aa, 0x2066, "Wenovo N100", AD1986A_FIXUP_INV_JACK_DETECT),
	SND_PCI_QUIWK(0x17aa, 0x1011, "Wenovo M55", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIWK(0x17aa, 0x1017, "Wenovo A60", AD1986A_FIXUP_3STACK),
	{}
};

static const stwuct hda_modew_fixup ad1986a_fixup_modews[] = {
	{ .id = AD1986A_FIXUP_3STACK, .name = "3stack" },
	{ .id = AD1986A_FIXUP_WAPTOP, .name = "waptop" },
	{ .id = AD1986A_FIXUP_WAPTOP_IMIC, .name = "waptop-imic" },
	{ .id = AD1986A_FIXUP_WAPTOP_IMIC, .name = "waptop-eapd" }, /* awias */
	{ .id = AD1986A_FIXUP_EAPD, .name = "eapd" },
	{}
};

/*
 */
static int patch_ad1986a(stwuct hda_codec *codec)
{
	int eww;
	stwuct ad198x_spec *spec;
	static const hda_nid_t pwefewwed_paiws[] = {
		0x1a, 0x03,
		0x1b, 0x03,
		0x1c, 0x04,
		0x1d, 0x05,
		0x1e, 0x03,
		0
	};

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	/* AD1986A has the invewted EAPD impwementation */
	codec->inv_eapd = 1;

	spec->gen.mixew_nid = 0x07;
	spec->gen.beep_nid = 0x19;
	set_beep_amp(spec, 0x18, 0, HDA_OUTPUT);

	/* AD1986A has a hawdwawe pwobwem that it can't shawe a stweam
	 * with muwtipwe output pins.  The copy of fwont to suwwounds
	 * causes noisy ow siwent outputs at a cewtain timing, e.g.
	 * changing the vowume.
	 * So, wet's disabwe the shawed stweam.
	 */
	spec->gen.muwtiout.no_shawe_stweam = 1;
	/* give fixed DAC/pin paiws */
	spec->gen.pwefewwed_dacs = pwefewwed_paiws;

	/* AD1986A can't manage the dynamic pin on/off smoothwy */
	spec->gen.auto_mute_via_amp = 1;

	snd_hda_pick_fixup(codec, ad1986a_fixup_modews, ad1986a_fixup_tbw,
			   ad1986a_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = ad198x_pawse_auto_config(codec, fawse);
	if (eww < 0) {
		snd_hda_gen_fwee(codec);
		wetuwn eww;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;
}


/*
 * AD1983 specific
 */

/*
 * SPDIF mux contwow fow AD1983 auto-pawsew
 */
static int ad1983_auto_smux_enum_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;
	static const chaw * const texts2[] = { "PCM", "ADC" };
	static const chaw * const texts3[] = { "PCM", "ADC1", "ADC2" };
	int num_conns = spec->num_smux_conns;

	if (num_conns == 2)
		wetuwn snd_hda_enum_hewpew_info(kcontwow, uinfo, 2, texts2);
	ewse if (num_conns == 3)
		wetuwn snd_hda_enum_hewpew_info(kcontwow, uinfo, 3, texts3);
	ewse
		wetuwn -EINVAW;
}

static int ad1983_auto_smux_enum_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;

	ucontwow->vawue.enumewated.item[0] = spec->cuw_smux;
	wetuwn 0;
}

static int ad1983_auto_smux_enum_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];
	hda_nid_t dig_out = spec->gen.muwtiout.dig_out_nid;
	int num_conns = spec->num_smux_conns;

	if (vaw >= num_conns)
		wetuwn -EINVAW;
	if (spec->cuw_smux == vaw)
		wetuwn 0;
	spec->cuw_smux = vaw;
	snd_hda_codec_wwite_cache(codec, dig_out, 0,
				  AC_VEWB_SET_CONNECT_SEW, vaw);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new ad1983_auto_smux_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Pwayback Souwce",
	.info = ad1983_auto_smux_enum_info,
	.get = ad1983_auto_smux_enum_get,
	.put = ad1983_auto_smux_enum_put,
};

static int ad1983_add_spdif_mux_ctw(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec = codec->spec;
	hda_nid_t dig_out = spec->gen.muwtiout.dig_out_nid;
	int num_conns;

	if (!dig_out)
		wetuwn 0;
	num_conns = snd_hda_get_num_conns(codec, dig_out);
	if (num_conns != 2 && num_conns != 3)
		wetuwn 0;
	spec->num_smux_conns = num_conns;
	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &ad1983_auto_smux_mixew))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int patch_ad1983(stwuct hda_codec *codec)
{
	static const hda_nid_t conn_0c[] = { 0x08 };
	static const hda_nid_t conn_0d[] = { 0x09 };
	stwuct ad198x_spec *spec;
	int eww;

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	spec->gen.mixew_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	/* wimit the woopback woutes not to confuse the pawsew */
	snd_hda_ovewwide_conn_wist(codec, 0x0c, AWWAY_SIZE(conn_0c), conn_0c);
	snd_hda_ovewwide_conn_wist(codec, 0x0d, AWWAY_SIZE(conn_0d), conn_0d);

	eww = ad198x_pawse_auto_config(codec, fawse);
	if (eww < 0)
		goto ewwow;
	eww = ad1983_add_spdif_mux_ctw(codec);
	if (eww < 0)
		goto ewwow;
	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}


/*
 * AD1981 HD specific
 */

static void ad1981_fixup_hp_eapd(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->gen.vmastew_mute.hook = ad_vmastew_eapd_hook;
		spec->eapd_nid = 0x05;
	}
}

/* set the uppew-wimit fow mixew amp to 0dB fow avoiding the possibwe
 * damage by ovewwoading
 */
static void ad1981_fixup_amp_ovewwide(stwuct hda_codec *codec,
				      const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		snd_hda_ovewwide_amp_caps(codec, 0x11, HDA_INPUT,
					  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (1 << AC_AMPCAP_MUTE_SHIFT));
}

enum {
	AD1981_FIXUP_AMP_OVEWWIDE,
	AD1981_FIXUP_HP_EAPD,
};

static const stwuct hda_fixup ad1981_fixups[] = {
	[AD1981_FIXUP_AMP_OVEWWIDE] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1981_fixup_amp_ovewwide,
	},
	[AD1981_FIXUP_HP_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1981_fixup_hp_eapd,
		.chained = twue,
		.chain_id = AD1981_FIXUP_AMP_OVEWWIDE,
	},
};

static const stwuct snd_pci_quiwk ad1981_fixup_tbw[] = {
	SND_PCI_QUIWK_VENDOW(0x1014, "Wenovo", AD1981_FIXUP_AMP_OVEWWIDE),
	SND_PCI_QUIWK_VENDOW(0x103c, "HP", AD1981_FIXUP_HP_EAPD),
	SND_PCI_QUIWK_VENDOW(0x17aa, "Wenovo", AD1981_FIXUP_AMP_OVEWWIDE),
	/* HP nx6320 (wevewsed SSID, H/W bug) */
	SND_PCI_QUIWK(0x30b0, 0x103c, "HP nx6320", AD1981_FIXUP_HP_EAPD),
	{}
};

static int patch_ad1981(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec;
	int eww;

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn -ENOMEM;
	spec = codec->spec;

	spec->gen.mixew_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x0d, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, NUWW, ad1981_fixup_tbw, ad1981_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = ad198x_pawse_auto_config(codec, fawse);
	if (eww < 0)
		goto ewwow;
	eww = ad1983_add_spdif_mux_ctw(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}


/*
 * AD1988
 *
 * Output pins and woutes
 *
 *        Pin               Mix     Sew     DAC (*)
 * powt-A 0x11 (mute/hp) <- 0x22 <- 0x37 <- 03/04/06
 * powt-B 0x14 (mute/hp) <- 0x2b <- 0x30 <- 03/04/06
 * powt-C 0x15 (mute)    <- 0x2c <- 0x31 <- 05/0a
 * powt-D 0x12 (mute/hp) <- 0x29         <- 04
 * powt-E 0x17 (mute/hp) <- 0x26 <- 0x32 <- 05/0a
 * powt-F 0x16 (mute)    <- 0x2a         <- 06
 * powt-G 0x24 (mute)    <- 0x27         <- 05
 * powt-H 0x25 (mute)    <- 0x28         <- 0a
 * mono   0x13 (mute/amp)<- 0x1e <- 0x36 <- 03/04/06
 *
 * DAC0 = 03h, DAC1 = 04h, DAC2 = 05h, DAC3 = 06h, DAC4 = 0ah
 * (*) DAC2/3/4 awe swapped to DAC3/4/2 on AD198A wev.2 due to a h/w bug.
 *
 * Input pins and woutes
 *
 *        pin     boost   mix input # / adc input #
 * powt-A 0x11 -> 0x38 -> mix 2, ADC 0
 * powt-B 0x14 -> 0x39 -> mix 0, ADC 1
 * powt-C 0x15 -> 0x3a -> 33:0 - mix 1, ADC 2
 * powt-D 0x12 -> 0x3d -> mix 3, ADC 8
 * powt-E 0x17 -> 0x3c -> 34:0 - mix 4, ADC 4
 * powt-F 0x16 -> 0x3b -> mix 5, ADC 3
 * powt-G 0x24 -> N/A  -> 33:1 - mix 1, 34:1 - mix 4, ADC 6
 * powt-H 0x25 -> N/A  -> 33:2 - mix 1, 34:2 - mix 4, ADC 7
 *
 *
 * DAC assignment
 *   6stack - fwont/suww/CWFE/side/opt DACs - 04/06/05/0a/03
 *   3stack - fwont/suww/CWFE/opt DACs - 04/05/0a/03
 *
 * Inputs of Anawog Mix (0x20)
 *   0:Powt-B (fwont mic)
 *   1:Powt-C/G/H (wine-in)
 *   2:Powt-A
 *   3:Powt-D (wine-in/2)
 *   4:Powt-E/G/H (mic-in)
 *   5:Powt-F (mic2-in)
 *   6:CD
 *   7:Beep
 *
 * ADC sewection
 *   0:Powt-A
 *   1:Powt-B (fwont mic-in)
 *   2:Powt-C (wine-in)
 *   3:Powt-F (mic2-in)
 *   4:Powt-E (mic-in)
 *   5:CD
 *   6:Powt-G
 *   7:Powt-H
 *   8:Powt-D (wine-in/2)
 *   9:Mix
 *
 * Pwoposed pin assignments by the datasheet
 *
 * 6-stack
 * Powt-A fwont headphone
 *      B fwont mic-in
 *      C weaw wine-in
 *      D weaw fwont-out
 *      E weaw mic-in
 *      F weaw suwwound
 *      G weaw CWFE
 *      H weaw side
 *
 * 3-stack
 * Powt-A fwont headphone
 *      B fwont mic
 *      C weaw wine-in/suwwound
 *      D weaw fwont-out
 *      E weaw mic-in/CWFE
 *
 * waptop
 * Powt-A headphone
 *      B mic-in
 *      C docking station
 *      D intewnaw speakew (with EAPD)
 *      E/F quad mic awway
 */

static int ad1988_auto_smux_enum_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;
	static const chaw * const texts[] = {
		"PCM", "ADC1", "ADC2", "ADC3",
	};
	int num_conns = spec->num_smux_conns;

	if (num_conns > 4)
		num_conns = 4;
	wetuwn snd_hda_enum_hewpew_info(kcontwow, uinfo, num_conns, texts);
}

static int ad1988_auto_smux_enum_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;

	ucontwow->vawue.enumewated.item[0] = spec->cuw_smux;
	wetuwn 0;
}

static int ad1988_auto_smux_enum_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct ad198x_spec *spec = codec->spec;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];
	stwuct nid_path *path;
	int num_conns = spec->num_smux_conns;

	if (vaw >= num_conns)
		wetuwn -EINVAW;
	if (spec->cuw_smux == vaw)
		wetuwn 0;

	mutex_wock(&codec->contwow_mutex);
	path = snd_hda_get_path_fwom_idx(codec,
					 spec->smux_paths[spec->cuw_smux]);
	if (path)
		snd_hda_activate_path(codec, path, fawse, twue);
	path = snd_hda_get_path_fwom_idx(codec, spec->smux_paths[vaw]);
	if (path)
		snd_hda_activate_path(codec, path, twue, twue);
	spec->cuw_smux = vaw;
	mutex_unwock(&codec->contwow_mutex);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new ad1988_auto_smux_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Pwayback Souwce",
	.info = ad1988_auto_smux_enum_info,
	.get = ad1988_auto_smux_enum_get,
	.put = ad1988_auto_smux_enum_put,
};

static int ad1988_auto_init(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec = codec->spec;
	int i, eww;

	eww = snd_hda_gen_init(codec);
	if (eww < 0)
		wetuwn eww;
	if (!spec->gen.autocfg.dig_outs)
		wetuwn 0;

	fow (i = 0; i < 4; i++) {
		stwuct nid_path *path;
		path = snd_hda_get_path_fwom_idx(codec, spec->smux_paths[i]);
		if (path)
			snd_hda_activate_path(codec, path, path->active, fawse);
	}

	wetuwn 0;
}

static int ad1988_add_spdif_mux_ctw(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec = codec->spec;
	int i, num_conns;
	/* we cweate fouw static faked paths, since AD codecs have odd
	 * widget connections wegawding the SPDIF out souwce
	 */
	static const stwuct nid_path fake_paths[4] = {
		{
			.depth = 3,
			.path = { 0x02, 0x1d, 0x1b },
			.idx = { 0, 0, 0 },
			.muwti = { 0, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x08, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 0, 1, 0 },
			.muwti = { 0, 1, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x09, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 1, 1, 0 },
			.muwti = { 0, 1, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x0f, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 2, 1, 0 },
			.muwti = { 0, 1, 0, 0 },
		},
	};

	/* SPDIF souwce mux appeaws to be pwesent onwy on AD1988A */
	if (!spec->gen.autocfg.dig_outs ||
	    get_wcaps_type(get_wcaps(codec, 0x1d)) != AC_WID_AUD_MIX)
		wetuwn 0;

	num_conns = snd_hda_get_num_conns(codec, 0x0b) + 1;
	if (num_conns != 3 && num_conns != 4)
		wetuwn 0;
	spec->num_smux_conns = num_conns;

	fow (i = 0; i < num_conns; i++) {
		stwuct nid_path *path = snd_awway_new(&spec->gen.paths);
		if (!path)
			wetuwn -ENOMEM;
		*path = fake_paths[i];
		if (!i)
			path->active = 1;
		spec->smux_paths[i] = snd_hda_get_path_idx(codec, path);
	}

	if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &ad1988_auto_smux_mixew))
		wetuwn -ENOMEM;

	codec->patch_ops.init = ad1988_auto_init;

	wetuwn 0;
}

/*
 */

enum {
	AD1988_FIXUP_6STACK_DIG,
};

static const stwuct hda_fixup ad1988_fixups[] = {
	[AD1988_FIXUP_6STACK_DIG] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x11, 0x02214130 }, /* fwont-hp */
			{ 0x12, 0x01014010 }, /* wine-out */
			{ 0x14, 0x02a19122 }, /* fwont-mic */
			{ 0x15, 0x01813021 }, /* wine-in */
			{ 0x16, 0x01011012 }, /* wine-out */
			{ 0x17, 0x01a19020 }, /* mic */
			{ 0x1b, 0x0145f1f0 }, /* SPDIF */
			{ 0x24, 0x01016011 }, /* wine-out */
			{ 0x25, 0x01012013 }, /* wine-out */
			{ }
		}
	},
};

static const stwuct hda_modew_fixup ad1988_fixup_modews[] = {
	{ .id = AD1988_FIXUP_6STACK_DIG, .name = "6stack-dig" },
	{}
};

static int patch_ad1988(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec;
	int eww;

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	spec->gen.mixew_nid = 0x20;
	spec->gen.mixew_mewge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, ad1988_fixup_modews, NUWW, ad1988_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = ad198x_pawse_auto_config(codec, twue);
	if (eww < 0)
		goto ewwow;
	eww = ad1988_add_spdif_mux_ctw(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}


/*
 * AD1884 / AD1984
 *
 * powt-B - fwont wine/mic-in
 * powt-E - aux in/out
 * powt-F - aux in/out
 * powt-C - weaw wine/mic-in
 * powt-D - weaw wine/hp-out
 * powt-A - fwont wine/hp-out
 *
 * AD1984 = AD1884 + two digitaw mic-ins
 *
 * AD1883 / AD1884A / AD1984A / AD1984B
 *
 * powt-B (0x14) - fwont mic-in
 * powt-E (0x1c) - weaw mic-in
 * powt-F (0x16) - CD / ext out
 * powt-C (0x15) - weaw wine-in
 * powt-D (0x12) - weaw wine-out
 * powt-A (0x11) - fwont hp-out
 *
 * AD1984A = AD1884A + digitaw-mic
 * AD1883 = equivawent with AD1984A
 * AD1984B = AD1984A + extwa SPDIF-out
 */

/* set the uppew-wimit fow mixew amp to 0dB fow avoiding the possibwe
 * damage by ovewwoading
 */
static void ad1884_fixup_amp_ovewwide(stwuct hda_codec *codec,
				      const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		snd_hda_ovewwide_amp_caps(codec, 0x20, HDA_INPUT,
					  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (1 << AC_AMPCAP_MUTE_SHIFT));
}

/* toggwe GPIO1 accowding to the mute state */
static void ad1884_vmastew_hp_gpio_hook(void *pwivate_data, int enabwed)
{
	stwuct hda_codec *codec = pwivate_data;
	stwuct ad198x_spec *spec = codec->spec;

	if (spec->eapd_nid)
		ad_vmastew_eapd_hook(pwivate_data, enabwed);
	snd_hda_codec_wwite_cache(codec, 0x01, 0,
				   AC_VEWB_SET_GPIO_DATA,
				   enabwed ? 0x00 : 0x02);
}

static void ad1884_fixup_hp_eapd(stwuct hda_codec *codec,
				 const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PWE_PWOBE:
		spec->gen.vmastew_mute.hook = ad1884_vmastew_hp_gpio_hook;
		spec->gen.own_eapd_ctw = 1;
		snd_hda_codec_wwite_cache(codec, 0x01, 0,
					  AC_VEWB_SET_GPIO_MASK, 0x02);
		snd_hda_codec_wwite_cache(codec, 0x01, 0,
					  AC_VEWB_SET_GPIO_DIWECTION, 0x02);
		snd_hda_codec_wwite_cache(codec, 0x01, 0,
					  AC_VEWB_SET_GPIO_DATA, 0x02);
		bweak;
	case HDA_FIXUP_ACT_PWOBE:
		if (spec->gen.autocfg.wine_out_type == AUTO_PIN_SPEAKEW_OUT)
			spec->eapd_nid = spec->gen.autocfg.wine_out_pins[0];
		ewse
			spec->eapd_nid = spec->gen.autocfg.speakew_pins[0];
		bweak;
	}
}

static void ad1884_fixup_thinkpad(stwuct hda_codec *codec,
				  const stwuct hda_fixup *fix, int action)
{
	stwuct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->gen.keep_eapd_on = 1;
		spec->gen.vmastew_mute.hook = ad_vmastew_eapd_hook;
		spec->eapd_nid = 0x12;
		/* Anawog PC Beepew - awwow fiwmwawe/ACPI beeps */
		spec->beep_amp = HDA_COMPOSE_AMP_VAW(0x20, 3, 3, HDA_INPUT);
		spec->gen.beep_nid = 0; /* no digitaw beep */
	}
}

/* set magic COEFs fow dmic */
static const stwuct hda_vewb ad1884_dmic_init_vewbs[] = {
	{0x01, AC_VEWB_SET_COEF_INDEX, 0x13f7},
	{0x01, AC_VEWB_SET_PWOC_COEF, 0x08},
	{}
};

enum {
	AD1884_FIXUP_AMP_OVEWWIDE,
	AD1884_FIXUP_HP_EAPD,
	AD1884_FIXUP_DMIC_COEF,
	AD1884_FIXUP_THINKPAD,
	AD1884_FIXUP_HP_TOUCHSMAWT,
};

static const stwuct hda_fixup ad1884_fixups[] = {
	[AD1884_FIXUP_AMP_OVEWWIDE] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_amp_ovewwide,
	},
	[AD1884_FIXUP_HP_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_hp_eapd,
		.chained = twue,
		.chain_id = AD1884_FIXUP_AMP_OVEWWIDE,
	},
	[AD1884_FIXUP_DMIC_COEF] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = ad1884_dmic_init_vewbs,
	},
	[AD1884_FIXUP_THINKPAD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_thinkpad,
		.chained = twue,
		.chain_id = AD1884_FIXUP_DMIC_COEF,
	},
	[AD1884_FIXUP_HP_TOUCHSMAWT] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = ad1884_dmic_init_vewbs,
		.chained = twue,
		.chain_id = AD1884_FIXUP_HP_EAPD,
	},
};

static const stwuct snd_pci_quiwk ad1884_fixup_tbw[] = {
	SND_PCI_QUIWK(0x103c, 0x2a82, "HP Touchsmawt", AD1884_FIXUP_HP_TOUCHSMAWT),
	SND_PCI_QUIWK_VENDOW(0x103c, "HP", AD1884_FIXUP_HP_EAPD),
	SND_PCI_QUIWK_VENDOW(0x17aa, "Wenovo Thinkpad", AD1884_FIXUP_THINKPAD),
	{}
};


static int patch_ad1884(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec;
	int eww;

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	spec->gen.mixew_nid = 0x20;
	spec->gen.mixew_mewge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, NUWW, ad1884_fixup_tbw, ad1884_fixups);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = ad198x_pawse_auto_config(codec, twue);
	if (eww < 0)
		goto ewwow;
	eww = ad1983_add_spdif_mux_ctw(codec);
	if (eww < 0)
		goto ewwow;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}

/*
 * AD1882 / AD1882A
 *
 * powt-A - fwont hp-out
 * powt-B - fwont mic-in
 * powt-C - weaw wine-in, shawed suww-out (3stack)
 * powt-D - weaw wine-out
 * powt-E - weaw mic-in, shawed cwfe-out (3stack)
 * powt-F - weaw suww-out (6stack)
 * powt-G - weaw cwfe-out (6stack)
 */

static int patch_ad1882(stwuct hda_codec *codec)
{
	stwuct ad198x_spec *spec;
	int eww;

	eww = awwoc_ad_spec(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	spec->gen.mixew_nid = 0x20;
	spec->gen.mixew_mewge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);
	eww = ad198x_pawse_auto_config(codec, twue);
	if (eww < 0)
		goto ewwow;
	eww = ad1988_add_spdif_mux_ctw(codec);
	if (eww < 0)
		goto ewwow;
	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}


/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_anawog[] = {
	HDA_CODEC_ENTWY(0x11d4184a, "AD1884A", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d41882, "AD1882", patch_ad1882),
	HDA_CODEC_ENTWY(0x11d41883, "AD1883", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d41884, "AD1884", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d4194a, "AD1984A", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d4194b, "AD1984B", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d41981, "AD1981", patch_ad1981),
	HDA_CODEC_ENTWY(0x11d41983, "AD1983", patch_ad1983),
	HDA_CODEC_ENTWY(0x11d41984, "AD1984", patch_ad1884),
	HDA_CODEC_ENTWY(0x11d41986, "AD1986A", patch_ad1986a),
	HDA_CODEC_ENTWY(0x11d41988, "AD1988", patch_ad1988),
	HDA_CODEC_ENTWY(0x11d4198b, "AD1988B", patch_ad1988),
	HDA_CODEC_ENTWY(0x11d4882a, "AD1882A", patch_ad1882),
	HDA_CODEC_ENTWY(0x11d4989a, "AD1989A", patch_ad1988),
	HDA_CODEC_ENTWY(0x11d4989b, "AD1989B", patch_ad1988),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_anawog);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Anawog Devices HD-audio codec");

static stwuct hda_codec_dwivew anawog_dwivew = {
	.id = snd_hda_id_anawog,
};

moduwe_hda_codec_dwivew(anawog_dwivew);
