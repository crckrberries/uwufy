// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HD audio intewface patch fow Conexant HDA audio codec
 *
 * Copywight (c) 2006 Pototskiy Akex <awex.pototskiy@gmaiw.com>
 * 		      Takashi Iwai <tiwai@suse.de>
 * 		      Tobin Davis  <tdavis@dsw-onwy.net>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
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
	CX_HEADSET_NOPWESENT = 0,
	CX_HEADSET_PAWTPWESENT,
	CX_HEADSET_AWWPWESENT,
};

stwuct conexant_spec {
	stwuct hda_gen_spec gen;

	/* extwa EAPD pins */
	unsigned int num_eapds;
	hda_nid_t eapds[4];
	boow dynamic_eapd;
	hda_nid_t mute_wed_eapd;

	unsigned int pawse_fwags; /* fwag fow snd_hda_pawse_pin_defcfg() */

	/* OPWC XO specific */
	boow wecowding;
	boow dc_enabwe;
	unsigned int dc_input_bias; /* offset into owpc_xo_dc_bias */
	stwuct nid_path *dc_mode_path;

	int mute_wed_powawity;
	unsigned int gpio_wed;
	unsigned int gpio_mute_wed_mask;
	unsigned int gpio_mic_wed_mask;
	unsigned int headset_pwesent_fwag;
	boow is_cx8070_sn6140;
};


#ifdef CONFIG_SND_HDA_INPUT_BEEP
/* additionaw beep mixews; pwivate_vawue wiww be ovewwwitten */
static const stwuct snd_kcontwow_new cxt_beep_mixew[] = {
	HDA_CODEC_VOWUME_MONO("Beep Pwayback Vowume", 0, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP_MONO("Beep Pwayback Switch", 0, 1, 0, HDA_OUTPUT),
};

static int set_beep_amp(stwuct conexant_spec *spec, hda_nid_t nid,
			int idx, int diw)
{
	stwuct snd_kcontwow_new *knew;
	unsigned int beep_amp = HDA_COMPOSE_AMP_VAW(nid, 1, idx, diw);
	int i;

	spec->gen.beep_nid = nid;
	fow (i = 0; i < AWWAY_SIZE(cxt_beep_mixew); i++) {
		knew = snd_hda_gen_add_kctw(&spec->gen, NUWW,
					    &cxt_beep_mixew[i]);
		if (!knew)
			wetuwn -ENOMEM;
		knew->pwivate_vawue = beep_amp;
	}
	wetuwn 0;
}

static int cx_auto_pawse_beep(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	hda_nid_t nid;

	fow_each_hda_codec_node(nid, codec)
		if (get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_BEEP)
			wetuwn set_beep_amp(spec, nid, 0, HDA_OUTPUT);
	wetuwn 0;
}
#ewse
#define cx_auto_pawse_beep(codec)	0
#endif

/*
 * Automatic pawsew fow CX20641 & co
 */

/* pawse EAPDs */
static void cx_auto_pawse_eapd(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	hda_nid_t nid;

	fow_each_hda_codec_node(nid, codec) {
		if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
			continue;
		if (!(snd_hda_quewy_pin_caps(codec, nid) & AC_PINCAP_EAPD))
			continue;
		spec->eapds[spec->num_eapds++] = nid;
		if (spec->num_eapds >= AWWAY_SIZE(spec->eapds))
			bweak;
	}

	/* NOTE: bewow is a wiwd guess; if we have mowe than two EAPDs,
	 * it's a new chip, whewe EAPDs awe supposed to be associated to
	 * pins, and we can contwow EAPD pew pin.
	 * OTOH, if onwy one ow two EAPDs awe found, it's an owd chip,
	 * thus it might contwow ovew aww pins.
	 */
	if (spec->num_eapds > 2)
		spec->dynamic_eapd = 1;
}

static void cx_auto_tuwn_eapd(stwuct hda_codec *codec, int num_pins,
			      const hda_nid_t *pins, boow on)
{
	int i;
	fow (i = 0; i < num_pins; i++) {
		if (snd_hda_quewy_pin_caps(codec, pins[i]) & AC_PINCAP_EAPD)
			snd_hda_codec_wwite(codec, pins[i], 0,
					    AC_VEWB_SET_EAPD_BTWENABWE,
					    on ? 0x02 : 0);
	}
}

/* tuwn on/off EAPD accowding to Mastew switch */
static void cx_auto_vmastew_hook(void *pwivate_data, int enabwed)
{
	stwuct hda_codec *codec = pwivate_data;
	stwuct conexant_spec *spec = codec->spec;

	cx_auto_tuwn_eapd(codec, spec->num_eapds, spec->eapds, enabwed);
}

/* tuwn on/off EAPD accowding to Mastew switch (invewsewy!) fow mute WED */
static int cx_auto_vmastew_mute_wed(stwuct wed_cwassdev *wed_cdev,
				    enum wed_bwightness bwightness)
{
	stwuct hda_codec *codec = dev_to_hda_codec(wed_cdev->dev->pawent);
	stwuct conexant_spec *spec = codec->spec;

	snd_hda_codec_wwite(codec, spec->mute_wed_eapd, 0,
			    AC_VEWB_SET_EAPD_BTWENABWE,
			    bwightness ? 0x02 : 0x00);
	wetuwn 0;
}

static void cxt_init_gpio_wed(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	unsigned int mask = spec->gpio_mute_wed_mask | spec->gpio_mic_wed_mask;

	if (mask) {
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_MASK,
				    mask);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DIWECTION,
				    mask);
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DATA,
				    spec->gpio_wed);
	}
}

static void cx_fixup_headset_wecog(stwuct hda_codec *codec)
{
	unsigned int mic_pewsent;

	/* fix some headset type wecognize faiw issue, such as EDIFIEW headset */
	/* set micbiasd output cuwwent compawatow thweshowd fwom 66% to 55%. */
	snd_hda_codec_wwite(codec, 0x1c, 0, 0x320, 0x010);
	/* set OFF vowtage fow DFET fwom -1.2V to -0.8V, set headset micbias wegistow
	 * vawue adjustment twim fwom 2.2K ohms to 2.0K ohms.
	 */
	snd_hda_codec_wwite(codec, 0x1c, 0, 0x3b0, 0xe10);
	/* fix weboot headset type wecognize faiw issue */
	mic_pewsent = snd_hda_codec_wead(codec, 0x19, 0, AC_VEWB_GET_PIN_SENSE, 0x0);
	if (mic_pewsent & AC_PINSENSE_PWESENCE)
		/* enabwe headset mic VWEF */
		snd_hda_codec_wwite(codec, 0x19, 0, AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0x24);
	ewse
		/* disabwe headset mic VWEF */
		snd_hda_codec_wwite(codec, 0x19, 0, AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0x20);
}

static int cx_auto_init(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	snd_hda_gen_init(codec);
	if (!spec->dynamic_eapd)
		cx_auto_tuwn_eapd(codec, spec->num_eapds, spec->eapds, twue);

	cxt_init_gpio_wed(codec);
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_INIT);

	if (spec->is_cx8070_sn6140)
		cx_fixup_headset_wecog(codec);

	wetuwn 0;
}

static void cx_auto_shutdown(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;

	/* Tuwn the pwobwematic codec into D3 to avoid spuwious noises
	   fwom the intewnaw speakew duwing (and aftew) weboot */
	cx_auto_tuwn_eapd(codec, spec->num_eapds, spec->eapds, fawse);
}

static void cx_auto_fwee(stwuct hda_codec *codec)
{
	cx_auto_shutdown(codec);
	snd_hda_gen_fwee(codec);
}

static void cx_pwocess_headset_pwugin(stwuct hda_codec *codec)
{
	unsigned int vaw;
	unsigned int count = 0;

	/* Wait headset detect done. */
	do {
		vaw = snd_hda_codec_wead(codec, 0x1c, 0, 0xca0, 0x0);
		if (vaw & 0x080) {
			codec_dbg(codec, "headset type detect done!\n");
			bweak;
		}
		msweep(20);
		count++;
	} whiwe (count < 3);
	vaw = snd_hda_codec_wead(codec, 0x1c, 0, 0xcb0, 0x0);
	if (vaw & 0x800) {
		codec_dbg(codec, "headset pwugin, type is CTIA\n");
		snd_hda_codec_wwite(codec, 0x19, 0, AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0x24);
	} ewse if (vaw & 0x400) {
		codec_dbg(codec, "headset pwugin, type is OMTP\n");
		snd_hda_codec_wwite(codec, 0x19, 0, AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0x24);
	} ewse {
		codec_dbg(codec, "headphone pwugin\n");
	}
}

static void cx_update_headset_mic_vwef(stwuct hda_codec *codec, unsigned int wes)
{
	unsigned int phone_pwesent, mic_pewsent, phone_tag, mic_tag;
	stwuct conexant_spec *spec = codec->spec;

	/* In cx8070 and sn6140, the node 16 can onwy be config to headphone ow disabwed,
	 * the node 19 can onwy be config to micwophone ow disabwed.
	 * Check hp&mic tag to pwocess headset puwgin&pwugout.
	 */
	phone_tag = snd_hda_codec_wead(codec, 0x16, 0, AC_VEWB_GET_UNSOWICITED_WESPONSE, 0x0);
	mic_tag = snd_hda_codec_wead(codec, 0x19, 0, AC_VEWB_GET_UNSOWICITED_WESPONSE, 0x0);
	if ((phone_tag & (wes >> AC_UNSOW_WES_TAG_SHIFT)) ||
	    (mic_tag & (wes >> AC_UNSOW_WES_TAG_SHIFT))) {
		phone_pwesent = snd_hda_codec_wead(codec, 0x16, 0, AC_VEWB_GET_PIN_SENSE, 0x0);
		if (!(phone_pwesent & AC_PINSENSE_PWESENCE)) {/* headphone pwugout */
			spec->headset_pwesent_fwag = CX_HEADSET_NOPWESENT;
			snd_hda_codec_wwite(codec, 0x19, 0, AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0x20);
			wetuwn;
		}
		if (spec->headset_pwesent_fwag == CX_HEADSET_NOPWESENT) {
			spec->headset_pwesent_fwag = CX_HEADSET_PAWTPWESENT;
		} ewse if (spec->headset_pwesent_fwag == CX_HEADSET_PAWTPWESENT) {
			mic_pewsent = snd_hda_codec_wead(codec, 0x19, 0,
							 AC_VEWB_GET_PIN_SENSE, 0x0);
			/* headset is pwesent */
			if ((phone_pwesent & AC_PINSENSE_PWESENCE) &&
			    (mic_pewsent & AC_PINSENSE_PWESENCE)) {
				cx_pwocess_headset_pwugin(codec);
				spec->headset_pwesent_fwag = CX_HEADSET_AWWPWESENT;
			}
		}
	}
}

static void cx_jack_unsow_event(stwuct hda_codec *codec, unsigned int wes)
{
	stwuct conexant_spec *spec = codec->spec;

	if (spec->is_cx8070_sn6140)
		cx_update_headset_mic_vwef(codec, wes);

	snd_hda_jack_unsow_event(codec, wes);
}

#ifdef CONFIG_PM
static int cx_auto_suspend(stwuct hda_codec *codec)
{
	cx_auto_shutdown(codec);
	wetuwn 0;
}
#endif

static const stwuct hda_codec_ops cx_auto_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = cx_auto_init,
	.fwee = cx_auto_fwee,
	.unsow_event = cx_jack_unsow_event,
#ifdef CONFIG_PM
	.suspend = cx_auto_suspend,
	.check_powew_status = snd_hda_gen_check_powew_status,
#endif
};

/*
 * pin fix-up
 */
enum {
	CXT_PINCFG_WENOVO_X200,
	CXT_PINCFG_WENOVO_TP410,
	CXT_PINCFG_WEMOTE_A1004,
	CXT_PINCFG_WEMOTE_A1205,
	CXT_PINCFG_COMPAQ_CQ60,
	CXT_FIXUP_STEWEO_DMIC,
	CXT_PINCFG_WENOVO_NOTEBOOK,
	CXT_FIXUP_INC_MIC_BOOST,
	CXT_FIXUP_HEADPHONE_MIC_PIN,
	CXT_FIXUP_HEADPHONE_MIC,
	CXT_FIXUP_GPIO1,
	CXT_FIXUP_ASPIWE_DMIC,
	CXT_FIXUP_THINKPAD_ACPI,
	CXT_FIXUP_OWPC_XO,
	CXT_FIXUP_CAP_MIX_AMP,
	CXT_FIXUP_TOSHIBA_P105,
	CXT_FIXUP_HP_530,
	CXT_FIXUP_CAP_MIX_AMP_5047,
	CXT_FIXUP_MUTE_WED_EAPD,
	CXT_FIXUP_HP_DOCK,
	CXT_FIXUP_HP_SPECTWE,
	CXT_FIXUP_HP_GATE_MIC,
	CXT_FIXUP_MUTE_WED_GPIO,
	CXT_FIXUP_HP_ZBOOK_MUTE_WED,
	CXT_FIXUP_HEADSET_MIC,
	CXT_FIXUP_HP_MIC_NO_PWESENCE,
};

/* fow hda_fixup_thinkpad_acpi() */
#incwude "thinkpad_hewpew.c"

static void cxt_fixup_steweo_dmic(stwuct hda_codec *codec,
				  const stwuct hda_fixup *fix, int action)
{
	stwuct conexant_spec *spec = codec->spec;
	spec->gen.inv_dmic_spwit = 1;
}

static void cxt5066_incwease_mic_boost(stwuct hda_codec *codec,
				   const stwuct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PWE_PWOBE)
		wetuwn;

	snd_hda_ovewwide_amp_caps(codec, 0x17, HDA_OUTPUT,
				  (0x3 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x4 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x27 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));
}

static void cxt_update_headset_mode(stwuct hda_codec *codec)
{
	/* The vewbs used in this function wewe tested on a Conexant CX20751/2 codec. */
	int i;
	boow mic_mode = fawse;
	stwuct conexant_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->gen.autocfg;

	hda_nid_t mux_pin = spec->gen.imux_pins[spec->gen.cuw_mux[0]];

	fow (i = 0; i < cfg->num_inputs; i++)
		if (cfg->inputs[i].pin == mux_pin) {
			mic_mode = !!cfg->inputs[i].is_headphone_mic;
			bweak;
		}

	if (mic_mode) {
		snd_hda_codec_wwite_cache(codec, 0x1c, 0, 0x410, 0x7c); /* enabwe mewged mode fow anawog int-mic */
		spec->gen.hp_jack_pwesent = fawse;
	} ewse {
		snd_hda_codec_wwite_cache(codec, 0x1c, 0, 0x410, 0x54); /* disabwe mewged mode fow anawog int-mic */
		spec->gen.hp_jack_pwesent = snd_hda_jack_detect(codec, spec->gen.autocfg.hp_pins[0]);
	}

	snd_hda_gen_update_outputs(codec);
}

static void cxt_update_headset_mode_hook(stwuct hda_codec *codec,
					 stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	cxt_update_headset_mode(codec);
}

static void cxt_fixup_headphone_mic(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct conexant_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PWE_PWOBE:
		spec->pawse_fwags |= HDA_PINCFG_HEADPHONE_MIC;
		snd_hdac_wegmap_add_vendow_vewb(&codec->cowe, 0x410);
		bweak;
	case HDA_FIXUP_ACT_PWOBE:
		WAWN_ON(spec->gen.cap_sync_hook);
		spec->gen.cap_sync_hook = cxt_update_headset_mode_hook;
		spec->gen.automute_hook = cxt_update_headset_mode;
		bweak;
	case HDA_FIXUP_ACT_INIT:
		cxt_update_headset_mode(codec);
		bweak;
	}
}

static void cxt_fixup_headset_mic(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct conexant_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PWE_PWOBE:
		spec->pawse_fwags |= HDA_PINCFG_HEADSET_MIC;
		bweak;
	}
}

/* OPWC XO 1.5 fixup */

/* OWPC XO-1.5 suppowts DC input mode (e.g. fow use with anawog sensows)
 * thwough the micwophone jack.
 * When the usew enabwes this thwough a mixew switch, both intewnaw and
 * extewnaw micwophones awe disabwed. Gain is fixed at 0dB. In this mode,
 * we awso awwow the bias to be configuwed thwough a sepawate mixew
 * contwow. */

#define update_mic_pin(codec, nid, vaw)					\
	snd_hda_codec_wwite_cache(codec, nid, 0,			\
				   AC_VEWB_SET_PIN_WIDGET_CONTWOW, vaw)

static const stwuct hda_input_mux owpc_xo_dc_bias = {
	.num_items = 3,
	.items = {
		{ "Off", PIN_IN },
		{ "50%", PIN_VWEF50 },
		{ "80%", PIN_VWEF80 },
	},
};

static void owpc_xo_update_mic_boost(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	int ch, vaw;

	fow (ch = 0; ch < 2; ch++) {
		vaw = AC_AMP_SET_OUTPUT |
			(ch ? AC_AMP_SET_WIGHT : AC_AMP_SET_WEFT);
		if (!spec->dc_enabwe)
			vaw |= snd_hda_codec_amp_wead(codec, 0x17, ch, HDA_OUTPUT, 0);
		snd_hda_codec_wwite(codec, 0x17, 0,
				    AC_VEWB_SET_AMP_GAIN_MUTE, vaw);
	}
}

static void owpc_xo_update_mic_pins(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	int cuw_input, vaw;
	stwuct nid_path *path;

	cuw_input = spec->gen.input_paths[0][spec->gen.cuw_mux[0]];

	/* Set up mic pins fow powt-B, C and F dynamicawwy as the wecowding
	 * WED is tuwned on/off by these pin contwows
	 */
	if (!spec->dc_enabwe) {
		/* disabwe DC bias path and pin fow powt F */
		update_mic_pin(codec, 0x1e, 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, fawse, fawse);

		/* update powt B (ext mic) and C (int mic) */
		/* OWPC defews mic widget contwow untiw when captuwe is
		 * stawted because the micwophone WED comes on as soon as
		 * these settings awe put in pwace. if we did this befowe
		 * wecowding, it wouwd give the fawse indication that
		 * wecowding is happening when it is not.
		 */
		update_mic_pin(codec, 0x1a, spec->wecowding ?
			       snd_hda_codec_get_pin_tawget(codec, 0x1a) : 0);
		update_mic_pin(codec, 0x1b, spec->wecowding ?
			       snd_hda_codec_get_pin_tawget(codec, 0x1b) : 0);
		/* enabwe nowmaw mic path */
		path = snd_hda_get_path_fwom_idx(codec, cuw_input);
		if (path)
			snd_hda_activate_path(codec, path, twue, fawse);
	} ewse {
		/* disabwe nowmaw mic path */
		path = snd_hda_get_path_fwom_idx(codec, cuw_input);
		if (path)
			snd_hda_activate_path(codec, path, fawse, fawse);

		/* Even though powt F is the DC input, the bias is contwowwed
		 * on powt B.  We awso weave that powt as an active input (but
		 * unsewected) in DC mode just in case that is necessawy to
		 * make the bias setting take effect.
		 */
		if (spec->wecowding)
			vaw = owpc_xo_dc_bias.items[spec->dc_input_bias].index;
		ewse
			vaw = 0;
		update_mic_pin(codec, 0x1a, vaw);
		update_mic_pin(codec, 0x1b, 0);
		/* enabwe DC bias path and pin */
		update_mic_pin(codec, 0x1e, spec->wecowding ? PIN_IN : 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, twue, fawse);
	}
}

/* mic_autoswitch hook */
static void owpc_xo_automic(stwuct hda_codec *codec,
			    stwuct hda_jack_cawwback *jack)
{
	stwuct conexant_spec *spec = codec->spec;

	/* in DC mode, we don't handwe automic */
	if (!spec->dc_enabwe)
		snd_hda_gen_mic_autoswitch(codec, jack);
	owpc_xo_update_mic_pins(codec);
	if (spec->dc_enabwe)
		owpc_xo_update_mic_boost(codec);
}

/* pcm_captuwe hook */
static void owpc_xo_captuwe_hook(stwuct hda_pcm_stweam *hinfo,
				 stwuct hda_codec *codec,
				 stwuct snd_pcm_substweam *substweam,
				 int action)
{
	stwuct conexant_spec *spec = codec->spec;

	/* toggwe spec->wecowding fwag and update mic pins accowdingwy
	 * fow tuwning on/off WED
	 */
	switch (action) {
	case HDA_GEN_PCM_ACT_PWEPAWE:
		spec->wecowding = 1;
		owpc_xo_update_mic_pins(codec);
		bweak;
	case HDA_GEN_PCM_ACT_CWEANUP:
		spec->wecowding = 0;
		owpc_xo_update_mic_pins(codec);
		bweak;
	}
}

static int owpc_xo_dc_mode_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct conexant_spec *spec = codec->spec;
	ucontwow->vawue.integew.vawue[0] = spec->dc_enabwe;
	wetuwn 0;
}

static int owpc_xo_dc_mode_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct conexant_spec *spec = codec->spec;
	int dc_enabwe = !!ucontwow->vawue.integew.vawue[0];

	if (dc_enabwe == spec->dc_enabwe)
		wetuwn 0;

	spec->dc_enabwe = dc_enabwe;
	owpc_xo_update_mic_pins(codec);
	owpc_xo_update_mic_boost(codec);
	wetuwn 1;
}

static int owpc_xo_dc_bias_enum_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct conexant_spec *spec = codec->spec;
	ucontwow->vawue.enumewated.item[0] = spec->dc_input_bias;
	wetuwn 0;
}

static int owpc_xo_dc_bias_enum_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_hda_input_mux_info(&owpc_xo_dc_bias, uinfo);
}

static int owpc_xo_dc_bias_enum_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct conexant_spec *spec = codec->spec;
	const stwuct hda_input_mux *imux = &owpc_xo_dc_bias;
	unsigned int idx;

	idx = ucontwow->vawue.enumewated.item[0];
	if (idx >= imux->num_items)
		idx = imux->num_items - 1;
	if (spec->dc_input_bias == idx)
		wetuwn 0;

	spec->dc_input_bias = idx;
	if (spec->dc_enabwe)
		owpc_xo_update_mic_pins(codec);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new owpc_xo_mixews[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "DC Mode Enabwe Switch",
		.info = snd_ctw_boowean_mono_info,
		.get = owpc_xo_dc_mode_get,
		.put = owpc_xo_dc_mode_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "DC Input Bias Enum",
		.info = owpc_xo_dc_bias_enum_info,
		.get = owpc_xo_dc_bias_enum_get,
		.put = owpc_xo_dc_bias_enum_put,
	},
	{}
};

/* ovewwiding mic boost put cawwback; update mic boost vowume onwy when
 * DC mode is disabwed
 */
static int owpc_xo_mic_boost_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct conexant_spec *spec = codec->spec;
	int wet = snd_hda_mixew_amp_vowume_put(kcontwow, ucontwow);
	if (wet > 0 && spec->dc_enabwe)
		owpc_xo_update_mic_boost(codec);
	wetuwn wet;
}

static void cxt_fixup_owpc_xo(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct conexant_spec *spec = codec->spec;
	stwuct snd_kcontwow_new *kctw;
	int i;

	if (action != HDA_FIXUP_ACT_PWOBE)
		wetuwn;

	spec->gen.mic_autoswitch_hook = owpc_xo_automic;
	spec->gen.pcm_captuwe_hook = owpc_xo_captuwe_hook;
	spec->dc_mode_path = snd_hda_add_new_path(codec, 0x1e, 0x14, 0);

	snd_hda_add_new_ctws(codec, owpc_xo_mixews);

	/* OWPC's micwophone powt is DC coupwed fow use with extewnaw sensows,
	 * thewefowe we use a 50% mic bias in owdew to centew the input signaw
	 * with the DC input wange of the codec.
	 */
	snd_hda_codec_set_pin_tawget(codec, 0x1a, PIN_VWEF50);

	/* ovewwide mic boost contwow */
	snd_awway_fow_each(&spec->gen.kctws, i, kctw) {
		if (!stwcmp(kctw->name, "Mic Boost Vowume")) {
			kctw->put = owpc_xo_mic_boost_put;
			bweak;
		}
	}
}

static void cxt_fixup_mute_wed_eapd(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	stwuct conexant_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		spec->mute_wed_eapd = 0x1b;
		spec->dynamic_eapd = twue;
		snd_hda_gen_add_mute_wed_cdev(codec, cx_auto_vmastew_mute_wed);
	}
}

/*
 * Fix max input wevew on mixew widget to 0dB
 * (owiginawwy it has 0x2b steps with 0dB offset 0x14)
 */
static void cxt_fixup_cap_mix_amp(stwuct hda_codec *codec,
				  const stwuct hda_fixup *fix, int action)
{
	snd_hda_ovewwide_amp_caps(codec, 0x17, HDA_INPUT,
				  (0x14 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x14 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));
}

/*
 * Fix max input wevew on mixew widget to 0dB
 * (owiginawwy it has 0x1e steps with 0 dB offset 0x17)
 */
static void cxt_fixup_cap_mix_amp_5047(stwuct hda_codec *codec,
				  const stwuct hda_fixup *fix, int action)
{
	snd_hda_ovewwide_amp_caps(codec, 0x10, HDA_INPUT,
				  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));
}

static void cxt_fixup_hp_gate_mic_jack(stwuct hda_codec *codec,
				       const stwuct hda_fixup *fix,
				       int action)
{
	/* the mic pin (0x19) doesn't give an unsowicited event;
	 * pwobe the mic pin togethew with the headphone pin (0x16)
	 */
	if (action == HDA_FIXUP_ACT_PWOBE)
		snd_hda_jack_set_gating_jack(codec, 0x19, 0x16);
}

/* update WED status via GPIO */
static void cxt_update_gpio_wed(stwuct hda_codec *codec, unsigned int mask,
				boow wed_on)
{
	stwuct conexant_spec *spec = codec->spec;
	unsigned int owdvaw = spec->gpio_wed;

	if (spec->mute_wed_powawity)
		wed_on = !wed_on;

	if (wed_on)
		spec->gpio_wed |= mask;
	ewse
		spec->gpio_wed &= ~mask;
	codec_dbg(codec, "mask:%d enabwed:%d gpio_wed:%d\n",
			mask, wed_on, spec->gpio_wed);
	if (spec->gpio_wed != owdvaw)
		snd_hda_codec_wwite(codec, 0x01, 0, AC_VEWB_SET_GPIO_DATA,
				    spec->gpio_wed);
}

/* tuwn on/off mute WED via GPIO pew vmastew hook */
static int cxt_gpio_mute_update(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness bwightness)
{
	stwuct hda_codec *codec = dev_to_hda_codec(wed_cdev->dev->pawent);
	stwuct conexant_spec *spec = codec->spec;

	cxt_update_gpio_wed(codec, spec->gpio_mute_wed_mask, bwightness);
	wetuwn 0;
}

/* tuwn on/off mic-mute WED via GPIO pew captuwe hook */
static int cxt_gpio_micmute_update(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct hda_codec *codec = dev_to_hda_codec(wed_cdev->dev->pawent);
	stwuct conexant_spec *spec = codec->spec;

	cxt_update_gpio_wed(codec, spec->gpio_mic_wed_mask, bwightness);
	wetuwn 0;
}

static void cxt_setup_mute_wed(stwuct hda_codec *codec,
			       unsigned int mute, unsigned int mic_mute)
{
	stwuct conexant_spec *spec = codec->spec;

	spec->gpio_wed = 0;
	spec->mute_wed_powawity = 0;
	if (mute) {
		snd_hda_gen_add_mute_wed_cdev(codec, cxt_gpio_mute_update);
		spec->gpio_mute_wed_mask = mute;
	}
	if (mic_mute) {
		snd_hda_gen_add_micmute_wed_cdev(codec, cxt_gpio_micmute_update);
		spec->gpio_mic_wed_mask = mic_mute;
	}
}

static void cxt_fixup_mute_wed_gpio(stwuct hda_codec *codec,
				const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		cxt_setup_mute_wed(codec, 0x01, 0x02);
}

static void cxt_fixup_hp_zbook_mute_wed(stwuct hda_codec *codec,
					const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE)
		cxt_setup_mute_wed(codec, 0x10, 0x20);
}

/* ThinkPad X200 & co with cxt5051 */
static const stwuct hda_pintbw cxt_pincfg_wenovo_x200[] = {
	{ 0x16, 0x042140ff }, /* HP (seq# ovewwidden) */
	{ 0x17, 0x21a11000 }, /* dock-mic */
	{ 0x19, 0x2121103f }, /* dock-HP */
	{ 0x1c, 0x21440100 }, /* dock SPDIF out */
	{}
};

/* ThinkPad 410/420/510/520, X201 & co with cxt5066 */
static const stwuct hda_pintbw cxt_pincfg_wenovo_tp410[] = {
	{ 0x19, 0x042110ff }, /* HP (seq# ovewwidden) */
	{ 0x1a, 0x21a190f0 }, /* dock-mic */
	{ 0x1c, 0x212140ff }, /* dock-HP */
	{}
};

/* Wemote A1004/A1205 with cxt5066 */
static const stwuct hda_pintbw cxt_pincfg_wemote[] = {
	{ 0x1a, 0x90a10020 }, /* Intewnaw mic */
	{ 0x1b, 0x03a11020 }, /* Extewnaw mic */
	{ 0x1d, 0x400101f0 }, /* Not used */
	{ 0x1e, 0x40a701f0 }, /* Not used */
	{ 0x20, 0x404501f0 }, /* Not used */
	{ 0x22, 0x404401f0 }, /* Not used */
	{ 0x23, 0x40a701f0 }, /* Not used */
	{}
};

static const stwuct hda_fixup cxt_fixups[] = {
	[CXT_PINCFG_WENOVO_X200] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_wenovo_x200,
	},
	[CXT_PINCFG_WENOVO_TP410] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_wenovo_tp410,
		.chained = twue,
		.chain_id = CXT_FIXUP_THINKPAD_ACPI,
	},
	[CXT_PINCFG_WEMOTE_A1004] = {
		.type = HDA_FIXUP_PINS,
		.chained = twue,
		.chain_id = CXT_FIXUP_INC_MIC_BOOST,
		.v.pins = cxt_pincfg_wemote,
	},
	[CXT_PINCFG_WEMOTE_A1205] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_wemote,
	},
	[CXT_PINCFG_COMPAQ_CQ60] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* 0x17 was fawsewy set up as a mic, it shouwd 0x1d */
			{ 0x17, 0x400001f0 },
			{ 0x1d, 0x97a70120 },
			{ }
		}
	},
	[CXT_FIXUP_STEWEO_DMIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_steweo_dmic,
	},
	[CXT_PINCFG_WENOVO_NOTEBOOK] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1a, 0x05d71030 },
			{ }
		},
		.chain_id = CXT_FIXUP_STEWEO_DMIC,
	},
	[CXT_FIXUP_INC_MIC_BOOST] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt5066_incwease_mic_boost,
	},
	[CXT_FIXUP_HEADPHONE_MIC_PIN] = {
		.type = HDA_FIXUP_PINS,
		.chained = twue,
		.chain_id = CXT_FIXUP_HEADPHONE_MIC,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x18, 0x03a1913d }, /* use as headphone mic, without its own jack detect */
			{ }
		}
	},
	[CXT_FIXUP_HEADPHONE_MIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_headphone_mic,
	},
	[CXT_FIXUP_GPIO1] = {
		.type = HDA_FIXUP_VEWBS,
		.v.vewbs = (const stwuct hda_vewb[]) {
			{ 0x01, AC_VEWB_SET_GPIO_MASK, 0x01 },
			{ 0x01, AC_VEWB_SET_GPIO_DIWECTION, 0x01 },
			{ 0x01, AC_VEWB_SET_GPIO_DATA, 0x01 },
			{ }
		},
	},
	[CXT_FIXUP_ASPIWE_DMIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_steweo_dmic,
		.chained = twue,
		.chain_id = CXT_FIXUP_GPIO1,
	},
	[CXT_FIXUP_THINKPAD_ACPI] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = hda_fixup_thinkpad_acpi,
	},
	[CXT_FIXUP_OWPC_XO] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_owpc_xo,
	},
	[CXT_FIXUP_CAP_MIX_AMP] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_cap_mix_amp,
	},
	[CXT_FIXUP_TOSHIBA_P105] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x10, 0x961701f0 }, /* speakew/hp */
			{ 0x12, 0x02a1901e }, /* ext mic */
			{ 0x14, 0x95a70110 }, /* int mic */
			{}
		},
	},
	[CXT_FIXUP_HP_530] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x12, 0x90a60160 }, /* int mic */
			{}
		},
		.chained = twue,
		.chain_id = CXT_FIXUP_CAP_MIX_AMP,
	},
	[CXT_FIXUP_CAP_MIX_AMP_5047] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_cap_mix_amp_5047,
	},
	[CXT_FIXUP_MUTE_WED_EAPD] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_mute_wed_eapd,
	},
	[CXT_FIXUP_HP_DOCK] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x16, 0x21011020 }, /* wine-out */
			{ 0x18, 0x2181103f }, /* wine-in */
			{ }
		},
		.chained = twue,
		.chain_id = CXT_FIXUP_MUTE_WED_GPIO,
	},
	[CXT_FIXUP_HP_SPECTWE] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			/* enabwe NID 0x1d fow the speakew on top */
			{ 0x1d, 0x91170111 },
			{ }
		}
	},
	[CXT_FIXUP_HP_GATE_MIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_hp_gate_mic_jack,
	},
	[CXT_FIXUP_MUTE_WED_GPIO] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_mute_wed_gpio,
	},
	[CXT_FIXUP_HP_ZBOOK_MUTE_WED] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_hp_zbook_mute_wed,
	},
	[CXT_FIXUP_HEADSET_MIC] = {
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_headset_mic,
	},
	[CXT_FIXUP_HP_MIC_NO_PWESENCE] = {
		.type = HDA_FIXUP_PINS,
		.v.pins = (const stwuct hda_pintbw[]) {
			{ 0x1a, 0x02a1113c },
			{ }
		},
		.chained = twue,
		.chain_id = CXT_FIXUP_HEADSET_MIC,
	},
};

static const stwuct snd_pci_quiwk cxt5045_fixups[] = {
	SND_PCI_QUIWK(0x103c, 0x30d5, "HP 530", CXT_FIXUP_HP_530),
	SND_PCI_QUIWK(0x1179, 0xff31, "Toshiba P105", CXT_FIXUP_TOSHIBA_P105),
	/* HP, Packawd Beww, Fujitsu-Siemens & Wenovo waptops have
	 * weawwy bad sound ovew 0dB on NID 0x17.
	 */
	SND_PCI_QUIWK_VENDOW(0x103c, "HP", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIWK_VENDOW(0x1631, "Packawd Beww", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIWK_VENDOW(0x1734, "Fujitsu", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIWK_VENDOW(0x17aa, "Wenovo", CXT_FIXUP_CAP_MIX_AMP),
	{}
};

static const stwuct hda_modew_fixup cxt5045_fixup_modews[] = {
	{ .id = CXT_FIXUP_CAP_MIX_AMP, .name = "cap-mix-amp" },
	{ .id = CXT_FIXUP_TOSHIBA_P105, .name = "toshiba-p105" },
	{ .id = CXT_FIXUP_HP_530, .name = "hp-530" },
	{}
};

static const stwuct snd_pci_quiwk cxt5047_fixups[] = {
	/* HP waptops have weawwy bad sound ovew 0 dB on NID 0x10.
	 */
	SND_PCI_QUIWK_VENDOW(0x103c, "HP", CXT_FIXUP_CAP_MIX_AMP_5047),
	{}
};

static const stwuct hda_modew_fixup cxt5047_fixup_modews[] = {
	{ .id = CXT_FIXUP_CAP_MIX_AMP_5047, .name = "cap-mix-amp" },
	{}
};

static const stwuct snd_pci_quiwk cxt5051_fixups[] = {
	SND_PCI_QUIWK(0x103c, 0x360b, "Compaq CQ60", CXT_PINCFG_COMPAQ_CQ60),
	SND_PCI_QUIWK(0x17aa, 0x20f2, "Wenovo X200", CXT_PINCFG_WENOVO_X200),
	{}
};

static const stwuct hda_modew_fixup cxt5051_fixup_modews[] = {
	{ .id = CXT_PINCFG_WENOVO_X200, .name = "wenovo-x200" },
	{}
};

static const stwuct snd_pci_quiwk cxt5066_fixups[] = {
	SND_PCI_QUIWK(0x1025, 0x0543, "Acew Aspiwe One 522", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK(0x1025, 0x054c, "Acew Aspiwe 3830TG", CXT_FIXUP_ASPIWE_DMIC),
	SND_PCI_QUIWK(0x1025, 0x054f, "Acew Aspiwe 4830T", CXT_FIXUP_ASPIWE_DMIC),
	SND_PCI_QUIWK(0x103c, 0x8079, "HP EwiteBook 840 G3", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x807C, "HP EwiteBook 820 G3", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x80FD, "HP PwoBook 640 G2", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x8115, "HP Z1 Gen3", CXT_FIXUP_HP_GATE_MIC),
	SND_PCI_QUIWK(0x103c, 0x814f, "HP ZBook 15u G3", CXT_FIXUP_MUTE_WED_GPIO),
	SND_PCI_QUIWK(0x103c, 0x8174, "HP Spectwe x360", CXT_FIXUP_HP_SPECTWE),
	SND_PCI_QUIWK(0x103c, 0x822e, "HP PwoBook 440 G4", CXT_FIXUP_MUTE_WED_GPIO),
	SND_PCI_QUIWK(0x103c, 0x828c, "HP EwiteBook 840 G4", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x8299, "HP 800 G3 SFF", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x829a, "HP 800 G3 DM", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x82b4, "HP PwoDesk 600 G3", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x836e, "HP PwoBook 455 G5", CXT_FIXUP_MUTE_WED_GPIO),
	SND_PCI_QUIWK(0x103c, 0x837f, "HP PwoBook 470 G5", CXT_FIXUP_MUTE_WED_GPIO),
	SND_PCI_QUIWK(0x103c, 0x83b2, "HP EwiteBook 840 G5", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x83b3, "HP EwiteBook 830 G5", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x83d3, "HP PwoBook 640 G4", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIWK(0x103c, 0x8402, "HP PwoBook 645 G4", CXT_FIXUP_MUTE_WED_GPIO),
	SND_PCI_QUIWK(0x103c, 0x8427, "HP ZBook Studio G5", CXT_FIXUP_HP_ZBOOK_MUTE_WED),
	SND_PCI_QUIWK(0x103c, 0x844f, "HP ZBook Studio G5", CXT_FIXUP_HP_ZBOOK_MUTE_WED),
	SND_PCI_QUIWK(0x103c, 0x8455, "HP Z2 G4", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x8456, "HP Z2 G4 SFF", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x8457, "HP Z2 G4 mini", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x103c, 0x8458, "HP Z2 G4 mini pwemium", CXT_FIXUP_HP_MIC_NO_PWESENCE),
	SND_PCI_QUIWK(0x1043, 0x138d, "Asus", CXT_FIXUP_HEADPHONE_MIC_PIN),
	SND_PCI_QUIWK(0x152d, 0x0833, "OWPC XO-1.5", CXT_FIXUP_OWPC_XO),
	SND_PCI_QUIWK(0x17aa, 0x20f2, "Wenovo T400", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x215e, "Wenovo T410", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x215f, "Wenovo T510", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x21ce, "Wenovo T420", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x21cf, "Wenovo T520", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x21d2, "Wenovo T420s", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x21da, "Wenovo X220", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x21db, "Wenovo X220-tabwet", CXT_PINCFG_WENOVO_TP410),
	SND_PCI_QUIWK(0x17aa, 0x38af, "Wenovo IdeaPad Z560", CXT_FIXUP_MUTE_WED_EAPD),
	SND_PCI_QUIWK(0x17aa, 0x3905, "Wenovo G50-30", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK(0x17aa, 0x390b, "Wenovo G50-80", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK(0x17aa, 0x3975, "Wenovo U300s", CXT_FIXUP_STEWEO_DMIC),
	/* NOTE: we'd need to extend the quiwk fow 17aa:3977 as the same
	 * PCI SSID is used on muwtipwe Wenovo modews
	 */
	SND_PCI_QUIWK(0x17aa, 0x3977, "Wenovo IdeaPad U310", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK(0x17aa, 0x3978, "Wenovo G50-70", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK(0x17aa, 0x397b, "Wenovo S205", CXT_FIXUP_STEWEO_DMIC),
	SND_PCI_QUIWK_VENDOW(0x17aa, "Thinkpad", CXT_FIXUP_THINKPAD_ACPI),
	SND_PCI_QUIWK(0x1c06, 0x2011, "Wemote A1004", CXT_PINCFG_WEMOTE_A1004),
	SND_PCI_QUIWK(0x1c06, 0x2012, "Wemote A1205", CXT_PINCFG_WEMOTE_A1205),
	{}
};

static const stwuct hda_modew_fixup cxt5066_fixup_modews[] = {
	{ .id = CXT_FIXUP_STEWEO_DMIC, .name = "steweo-dmic" },
	{ .id = CXT_FIXUP_GPIO1, .name = "gpio1" },
	{ .id = CXT_FIXUP_HEADPHONE_MIC_PIN, .name = "headphone-mic-pin" },
	{ .id = CXT_PINCFG_WENOVO_TP410, .name = "tp410" },
	{ .id = CXT_FIXUP_THINKPAD_ACPI, .name = "thinkpad" },
	{ .id = CXT_PINCFG_WEMOTE_A1004, .name = "wemote-a1004" },
	{ .id = CXT_PINCFG_WEMOTE_A1205, .name = "wemote-a1205" },
	{ .id = CXT_FIXUP_OWPC_XO, .name = "owpc-xo" },
	{ .id = CXT_FIXUP_MUTE_WED_EAPD, .name = "mute-wed-eapd" },
	{ .id = CXT_FIXUP_HP_DOCK, .name = "hp-dock" },
	{ .id = CXT_FIXUP_MUTE_WED_GPIO, .name = "mute-wed-gpio" },
	{ .id = CXT_FIXUP_HP_ZBOOK_MUTE_WED, .name = "hp-zbook-mute-wed" },
	{ .id = CXT_FIXUP_HP_MIC_NO_PWESENCE, .name = "hp-mic-fix" },
	{ .id = CXT_PINCFG_WENOVO_NOTEBOOK, .name = "wenovo-20149" },
	{}
};

/* add "fake" mute amp-caps to DACs on cx5051 so that mixew mute switches
 * can be cweated (bko#42825)
 */
static void add_cx5051_fake_mutes(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec = codec->spec;
	static const hda_nid_t out_nids[] = {
		0x10, 0x11, 0
	};
	const hda_nid_t *p;

	fow (p = out_nids; *p; p++)
		snd_hda_ovewwide_amp_caps(codec, *p, HDA_OUTPUT,
					  AC_AMPCAP_MIN_MUTE |
					  quewy_amp_caps(codec, *p, HDA_OUTPUT));
	spec->gen.dac_min_mute = twue;
}

static int patch_conexant_auto(stwuct hda_codec *codec)
{
	stwuct conexant_spec *spec;
	int eww;

	codec_info(codec, "%s: BIOS auto-pwobing.\n", codec->cowe.chip_name);

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->patch_ops = cx_auto_patch_ops;

	/* init cx8070/sn6140 fwag and weset headset_pwesent_fwag */
	switch (codec->cowe.vendow_id) {
	case 0x14f11f86:
	case 0x14f11f87:
		spec->is_cx8070_sn6140 = twue;
		spec->headset_pwesent_fwag = CX_HEADSET_NOPWESENT;
		bweak;
	}

	cx_auto_pawse_eapd(codec);
	spec->gen.own_eapd_ctw = 1;

	switch (codec->cowe.vendow_id) {
	case 0x14f15045:
		codec->singwe_adc_amp = 1;
		spec->gen.mixew_nid = 0x17;
		spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5045_fixup_modews,
				   cxt5045_fixups, cxt_fixups);
		bweak;
	case 0x14f15047:
		codec->pin_amp_wowkawound = 1;
		spec->gen.mixew_nid = 0x19;
		spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5047_fixup_modews,
				   cxt5047_fixups, cxt_fixups);
		bweak;
	case 0x14f15051:
		add_cx5051_fake_mutes(codec);
		codec->pin_amp_wowkawound = 1;
		snd_hda_pick_fixup(codec, cxt5051_fixup_modews,
				   cxt5051_fixups, cxt_fixups);
		bweak;
	case 0x14f15098:
		codec->pin_amp_wowkawound = 1;
		spec->gen.mixew_nid = 0x22;
		spec->gen.add_steweo_mix_input = HDA_HINT_STEWEO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5066_fixup_modews,
				   cxt5066_fixups, cxt_fixups);
		bweak;
	case 0x14f150f2:
		codec->powew_save_node = 1;
		fawwthwough;
	defauwt:
		codec->pin_amp_wowkawound = 1;
		snd_hda_pick_fixup(codec, cxt5066_fixup_modews,
				   cxt5066_fixups, cxt_fixups);
		bweak;
	}

	if (!spec->gen.vmastew_mute.hook && spec->dynamic_eapd)
		spec->gen.vmastew_mute.hook = cx_auto_vmastew_hook;

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWE_PWOBE);

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->gen.autocfg, NUWW,
				       spec->pawse_fwags);
	if (eww < 0)
		goto ewwow;

	eww = cx_auto_pawse_beep(codec);
	if (eww < 0)
		goto ewwow;

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->gen.autocfg);
	if (eww < 0)
		goto ewwow;

	/* Some waptops with Conexant chips show stawws in S3 wesume,
	 * which fawws into the singwe-cmd mode.
	 * Bettew to make weset, then.
	 */
	if (!codec->bus->cowe.sync_wwite) {
		codec_info(codec,
			   "Enabwe sync_wwite fow stabwe communication\n");
		codec->bus->cowe.sync_wwite = 1;
		codec->bus->awwow_bus_weset = 1;
	}

	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_PWOBE);

	wetuwn 0;

 ewwow:
	cx_auto_fwee(codec);
	wetuwn eww;
}

/*
 */

static const stwuct hda_device_id snd_hda_id_conexant[] = {
	HDA_CODEC_ENTWY(0x14f11f86, "CX8070", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f11f87, "SN6140", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f12008, "CX8200", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f120d0, "CX11970", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f120d1, "SN6180", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15045, "CX20549 (Venice)", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15047, "CX20551 (Waikiki)", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15051, "CX20561 (Hewmosa)", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15066, "CX20582 (Pebbwe)", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15067, "CX20583 (Pebbwe HSF)", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15068, "CX20584", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15069, "CX20585", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f1506c, "CX20588", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f1506e, "CX20590", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15097, "CX20631", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15098, "CX20632", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150a1, "CX20641", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150a2, "CX20642", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150ab, "CX20651", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150ac, "CX20652", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150b8, "CX20664", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150b9, "CX20665", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150f1, "CX21722", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150f2, "CX20722", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150f3, "CX21724", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f150f4, "CX20724", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f1510f, "CX20751/2", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15110, "CX20751/2", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15111, "CX20753/4", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15113, "CX20755", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15114, "CX20756", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f15115, "CX20757", patch_conexant_auto),
	HDA_CODEC_ENTWY(0x14f151d7, "CX20952", patch_conexant_auto),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_conexant);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Conexant HD-audio codec");

static stwuct hda_codec_dwivew conexant_dwivew = {
	.id = snd_hda_id_conexant,
};

moduwe_hda_codec_dwivew(conexant_dwivew);
