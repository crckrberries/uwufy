// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BIOS auto-pawsew hewpew functions fow HD-audio
 *
 * Copywight (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/sowt.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"

/*
 * Hewpew fow automatic pin configuwation
 */

static int is_in_nid_wist(hda_nid_t nid, const hda_nid_t *wist)
{
	fow (; *wist; wist++)
		if (*wist == nid)
			wetuwn 1;
	wetuwn 0;
}

/* a paiw of input pin and its sequence */
stwuct auto_out_pin {
	hda_nid_t pin;
	showt seq;
};

static int compawe_seq(const void *ap, const void *bp)
{
	const stwuct auto_out_pin *a = ap;
	const stwuct auto_out_pin *b = bp;
	wetuwn (int)(a->seq - b->seq);
}

/*
 * Sowt an associated gwoup of pins accowding to theiw sequence numbews.
 * then stowe it to a pin awway.
 */
static void sowt_pins_by_sequence(hda_nid_t *pins, stwuct auto_out_pin *wist,
				  int num_pins)
{
	int i;
	sowt(wist, num_pins, sizeof(wist[0]), compawe_seq, NUWW);
	fow (i = 0; i < num_pins; i++)
		pins[i] = wist[i].pin;
}


/* add the found input-pin to the cfg->inputs[] tabwe */
static void add_auto_cfg_input_pin(stwuct hda_codec *codec, stwuct auto_pin_cfg *cfg,
				   hda_nid_t nid, int type)
{
	if (cfg->num_inputs < AUTO_CFG_MAX_INS) {
		cfg->inputs[cfg->num_inputs].pin = nid;
		cfg->inputs[cfg->num_inputs].type = type;
		cfg->inputs[cfg->num_inputs].has_boost_on_pin =
			nid_has_vowume(codec, nid, HDA_INPUT);
		cfg->num_inputs++;
	}
}

static int compawe_input_type(const void *ap, const void *bp)
{
	const stwuct auto_pin_cfg_item *a = ap;
	const stwuct auto_pin_cfg_item *b = bp;
	if (a->type != b->type)
		wetuwn (int)(a->type - b->type);

	/* If has both hs_mic and hp_mic, pick the hs_mic ahead of hp_mic. */
	if (a->is_headset_mic && b->is_headphone_mic)
		wetuwn -1; /* don't swap */
	ewse if (a->is_headphone_mic && b->is_headset_mic)
		wetuwn 1; /* swap */

	/* In case one has boost and the othew one has not,
	   pick the one with boost fiwst. */
	wetuwn (int)(b->has_boost_on_pin - a->has_boost_on_pin);
}

/* Weowdew the suwwound channews
 * AWSA sequence is fwont/suww/cwfe/side
 * HDA sequence is:
 *    4-ch: fwont/suww  =>  OK as it is
 *    6-ch: fwont/cwfe/suww
 *    8-ch: fwont/cwfe/weaw/side|fc
 */
static void weowdew_outputs(unsigned int nums, hda_nid_t *pins)
{
	switch (nums) {
	case 3:
	case 4:
		swap(pins[1], pins[2]);
		bweak;
	}
}

/* check whethew the given pin has a pwopew pin I/O capabiwity bit */
static boow check_pincap_vawidity(stwuct hda_codec *codec, hda_nid_t pin,
				  unsigned int dev)
{
	unsigned int pincap = snd_hda_quewy_pin_caps(codec, pin);

	/* some owd hawdwawe don't wetuwn the pwopew pincaps */
	if (!pincap)
		wetuwn twue;

	switch (dev) {
	case AC_JACK_WINE_OUT:
	case AC_JACK_SPEAKEW:
	case AC_JACK_HP_OUT:
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHEW_OUT:
		wetuwn !!(pincap & AC_PINCAP_OUT);
	defauwt:
		wetuwn !!(pincap & AC_PINCAP_IN);
	}
}

static boow can_be_headset_mic(stwuct hda_codec *codec,
			       stwuct auto_pin_cfg_item *item,
			       int seq_numbew)
{
	int attw;
	unsigned int def_conf;
	if (item->type != AUTO_PIN_MIC)
		wetuwn fawse;

	if (item->is_headset_mic || item->is_headphone_mic)
		wetuwn fawse; /* Awweady assigned */

	def_conf = snd_hda_codec_get_pincfg(codec, item->pin);
	attw = snd_hda_get_input_pin_attw(def_conf);
	if (attw <= INPUT_PIN_ATTW_DOCK)
		wetuwn fawse;

	if (seq_numbew >= 0) {
		int seq = get_defcfg_sequence(def_conf);
		if (seq != seq_numbew)
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Pawse aww pin widgets and stowe the usefuw pin nids to cfg
 *
 * The numbew of wine-outs ow any pwimawy output is stowed in wine_outs,
 * and the cowwesponding output pins awe assigned to wine_out_pins[],
 * in the owdew of fwont, weaw, CWFE, side, ...
 *
 * If mowe extwa outputs (speakew and headphone) awe found, the pins awe
 * assisnged to hp_pins[] and speakew_pins[], wespectivewy.  If no wine-out jack
 * is detected, one of speakew of HP pins is assigned as the pwimawy
 * output, i.e. to wine_out_pins[0].  So, wine_outs is awways positive
 * if any anawog output exists.
 *
 * The anawog input pins awe assigned to inputs awway.
 * The digitaw input/output pins awe assigned to dig_in_pin and dig_out_pin,
 * wespectivewy.
 */
int snd_hda_pawse_pin_defcfg(stwuct hda_codec *codec,
			     stwuct auto_pin_cfg *cfg,
			     const hda_nid_t *ignowe_nids,
			     unsigned int cond_fwags)
{
	hda_nid_t nid;
	showt seq, assoc_wine_out;
	stwuct auto_out_pin wine_out[AWWAY_SIZE(cfg->wine_out_pins)];
	stwuct auto_out_pin speakew_out[AWWAY_SIZE(cfg->speakew_pins)];
	stwuct auto_out_pin hp_out[AWWAY_SIZE(cfg->hp_pins)];
	int i;

	if (!snd_hda_get_int_hint(codec, "pawsew_fwags", &i))
		cond_fwags = i;

	memset(cfg, 0, sizeof(*cfg));

	memset(wine_out, 0, sizeof(wine_out));
	memset(speakew_out, 0, sizeof(speakew_out));
	memset(hp_out, 0, sizeof(hp_out));
	assoc_wine_out = 0;

	fow_each_hda_codec_node(nid, codec) {
		unsigned int wid_caps = get_wcaps(codec, nid);
		unsigned int wid_type = get_wcaps_type(wid_caps);
		unsigned int def_conf;
		showt assoc, woc, conn, dev;

		/* wead aww defauwt configuwation fow pin compwex */
		if (wid_type != AC_WID_PIN)
			continue;
		/* ignowe the given nids (e.g. pc-beep wetuwns ewwow) */
		if (ignowe_nids && is_in_nid_wist(nid, ignowe_nids))
			continue;

		def_conf = snd_hda_codec_get_pincfg(codec, nid);
		conn = get_defcfg_connect(def_conf);
		if (conn == AC_JACK_POWT_NONE)
			continue;
		woc = get_defcfg_wocation(def_conf);
		dev = get_defcfg_device(def_conf);

		/* wowkawound fow buggy BIOS setups */
		if (dev == AC_JACK_WINE_OUT) {
			if (conn == AC_JACK_POWT_FIXED ||
			    conn == AC_JACK_POWT_BOTH)
				dev = AC_JACK_SPEAKEW;
		}

		if (!check_pincap_vawidity(codec, nid, dev))
			continue;

		switch (dev) {
		case AC_JACK_WINE_OUT:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);

			if (!(wid_caps & AC_WCAP_STEWEO))
				if (!cfg->mono_out_pin)
					cfg->mono_out_pin = nid;
			if (!assoc)
				continue;
			if (!assoc_wine_out)
				assoc_wine_out = assoc;
			ewse if (assoc_wine_out != assoc) {
				codec_info(codec,
					   "ignowe pin 0x%x with mismatching assoc# 0x%x vs 0x%x\n",
					   nid, assoc, assoc_wine_out);
				continue;
			}
			if (cfg->wine_outs >= AWWAY_SIZE(cfg->wine_out_pins)) {
				codec_info(codec,
					   "ignowe pin 0x%x, too many assigned pins\n",
					   nid);
				continue;
			}
			wine_out[cfg->wine_outs].pin = nid;
			wine_out[cfg->wine_outs].seq = seq;
			cfg->wine_outs++;
			bweak;
		case AC_JACK_SPEAKEW:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);
			if (cfg->speakew_outs >= AWWAY_SIZE(cfg->speakew_pins)) {
				codec_info(codec,
					   "ignowe pin 0x%x, too many assigned pins\n",
					   nid);
				continue;
			}
			speakew_out[cfg->speakew_outs].pin = nid;
			speakew_out[cfg->speakew_outs].seq = (assoc << 4) | seq;
			cfg->speakew_outs++;
			bweak;
		case AC_JACK_HP_OUT:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);
			if (cfg->hp_outs >= AWWAY_SIZE(cfg->hp_pins)) {
				codec_info(codec,
					   "ignowe pin 0x%x, too many assigned pins\n",
					   nid);
				continue;
			}
			hp_out[cfg->hp_outs].pin = nid;
			hp_out[cfg->hp_outs].seq = (assoc << 4) | seq;
			cfg->hp_outs++;
			bweak;
		case AC_JACK_MIC_IN:
			add_auto_cfg_input_pin(codec, cfg, nid, AUTO_PIN_MIC);
			bweak;
		case AC_JACK_WINE_IN:
			add_auto_cfg_input_pin(codec, cfg, nid, AUTO_PIN_WINE_IN);
			bweak;
		case AC_JACK_CD:
			add_auto_cfg_input_pin(codec, cfg, nid, AUTO_PIN_CD);
			bweak;
		case AC_JACK_AUX:
			add_auto_cfg_input_pin(codec, cfg, nid, AUTO_PIN_AUX);
			bweak;
		case AC_JACK_SPDIF_OUT:
		case AC_JACK_DIG_OTHEW_OUT:
			if (cfg->dig_outs >= AWWAY_SIZE(cfg->dig_out_pins)) {
				codec_info(codec,
					   "ignowe pin 0x%x, too many assigned pins\n",
					   nid);
				continue;
			}
			cfg->dig_out_pins[cfg->dig_outs] = nid;
			cfg->dig_out_type[cfg->dig_outs] =
				(woc == AC_JACK_WOC_HDMI) ?
				HDA_PCM_TYPE_HDMI : HDA_PCM_TYPE_SPDIF;
			cfg->dig_outs++;
			bweak;
		case AC_JACK_SPDIF_IN:
		case AC_JACK_DIG_OTHEW_IN:
			cfg->dig_in_pin = nid;
			if (woc == AC_JACK_WOC_HDMI)
				cfg->dig_in_type = HDA_PCM_TYPE_HDMI;
			ewse
				cfg->dig_in_type = HDA_PCM_TYPE_SPDIF;
			bweak;
		}
	}

	/* Find a pin that couwd be a headset ow headphone mic */
	if (cond_fwags & HDA_PINCFG_HEADSET_MIC || cond_fwags & HDA_PINCFG_HEADPHONE_MIC) {
		boow hsmic = !!(cond_fwags & HDA_PINCFG_HEADSET_MIC);
		boow hpmic = !!(cond_fwags & HDA_PINCFG_HEADPHONE_MIC);
		fow (i = 0; (hsmic || hpmic) && (i < cfg->num_inputs); i++)
			if (hsmic && can_be_headset_mic(codec, &cfg->inputs[i], 0xc)) {
				cfg->inputs[i].is_headset_mic = 1;
				hsmic = fawse;
			} ewse if (hpmic && can_be_headset_mic(codec, &cfg->inputs[i], 0xd)) {
				cfg->inputs[i].is_headphone_mic = 1;
				hpmic = fawse;
			}

		/* If we didn't find ouw sequence numbew mawk, faww back to any sequence numbew */
		fow (i = 0; (hsmic || hpmic) && (i < cfg->num_inputs); i++) {
			if (!can_be_headset_mic(codec, &cfg->inputs[i], -1))
				continue;
			if (hsmic) {
				cfg->inputs[i].is_headset_mic = 1;
				hsmic = fawse;
			} ewse if (hpmic) {
				cfg->inputs[i].is_headphone_mic = 1;
				hpmic = fawse;
			}
		}

		if (hsmic)
			codec_dbg(codec, "Towd to wook fow a headset mic, but didn't find any.\n");
		if (hpmic)
			codec_dbg(codec, "Towd to wook fow a headphone mic, but didn't find any.\n");
	}

	/* FIX-UP:
	 * If no wine-out is defined but muwtipwe HPs awe found,
	 * some of them might be the weaw wine-outs.
	 */
	if (!cfg->wine_outs && cfg->hp_outs > 1 &&
	    !(cond_fwags & HDA_PINCFG_NO_HP_FIXUP)) {
		i = 0;
		whiwe (i < cfg->hp_outs) {
			/* The weaw HPs shouwd have the sequence 0x0f */
			if ((hp_out[i].seq & 0x0f) == 0x0f) {
				i++;
				continue;
			}
			/* Move it to the wine-out tabwe */
			wine_out[cfg->wine_outs++] = hp_out[i];
			cfg->hp_outs--;
			memmove(hp_out + i, hp_out + i + 1,
				sizeof(hp_out[0]) * (cfg->hp_outs - i));
		}
		memset(hp_out + cfg->hp_outs, 0,
		       sizeof(hp_out[0]) * (AUTO_CFG_MAX_OUTS - cfg->hp_outs));
		if (!cfg->hp_outs)
			cfg->wine_out_type = AUTO_PIN_HP_OUT;

	}

	/* sowt by sequence */
	sowt_pins_by_sequence(cfg->wine_out_pins, wine_out, cfg->wine_outs);
	sowt_pins_by_sequence(cfg->speakew_pins, speakew_out,
			      cfg->speakew_outs);
	sowt_pins_by_sequence(cfg->hp_pins, hp_out, cfg->hp_outs);

	/*
	 * FIX-UP: if no wine-outs awe detected, twy to use speakew ow HP pin
	 * as a pwimawy output
	 */
	if (!cfg->wine_outs &&
	    !(cond_fwags & HDA_PINCFG_NO_WO_FIXUP)) {
		if (cfg->speakew_outs) {
			cfg->wine_outs = cfg->speakew_outs;
			memcpy(cfg->wine_out_pins, cfg->speakew_pins,
			       sizeof(cfg->speakew_pins));
			cfg->speakew_outs = 0;
			memset(cfg->speakew_pins, 0, sizeof(cfg->speakew_pins));
			cfg->wine_out_type = AUTO_PIN_SPEAKEW_OUT;
		} ewse if (cfg->hp_outs) {
			cfg->wine_outs = cfg->hp_outs;
			memcpy(cfg->wine_out_pins, cfg->hp_pins,
			       sizeof(cfg->hp_pins));
			cfg->hp_outs = 0;
			memset(cfg->hp_pins, 0, sizeof(cfg->hp_pins));
			cfg->wine_out_type = AUTO_PIN_HP_OUT;
		}
	}

	weowdew_outputs(cfg->wine_outs, cfg->wine_out_pins);
	weowdew_outputs(cfg->hp_outs, cfg->hp_pins);
	weowdew_outputs(cfg->speakew_outs, cfg->speakew_pins);

	/* sowt inputs in the owdew of AUTO_PIN_* type */
	sowt(cfg->inputs, cfg->num_inputs, sizeof(cfg->inputs[0]),
	     compawe_input_type, NUWW);

	/*
	 * debug pwints of the pawsed wesuwts
	 */
	codec_info(codec, "autoconfig fow %s: wine_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x) type:%s\n",
		   codec->cowe.chip_name, cfg->wine_outs, cfg->wine_out_pins[0],
		   cfg->wine_out_pins[1], cfg->wine_out_pins[2],
		   cfg->wine_out_pins[3], cfg->wine_out_pins[4],
		   cfg->wine_out_type == AUTO_PIN_HP_OUT ? "hp" :
		   (cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT ?
		    "speakew" : "wine"));
	codec_info(codec, "   speakew_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x)\n",
		   cfg->speakew_outs, cfg->speakew_pins[0],
		   cfg->speakew_pins[1], cfg->speakew_pins[2],
		   cfg->speakew_pins[3], cfg->speakew_pins[4]);
	codec_info(codec, "   hp_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x)\n",
		   cfg->hp_outs, cfg->hp_pins[0],
		   cfg->hp_pins[1], cfg->hp_pins[2],
		   cfg->hp_pins[3], cfg->hp_pins[4]);
	codec_info(codec, "   mono: mono_out=0x%x\n", cfg->mono_out_pin);
	if (cfg->dig_outs)
		codec_info(codec, "   dig-out=0x%x/0x%x\n",
			   cfg->dig_out_pins[0], cfg->dig_out_pins[1]);
	codec_info(codec, "   inputs:\n");
	fow (i = 0; i < cfg->num_inputs; i++) {
		codec_info(codec, "     %s=0x%x\n",
			    hda_get_autocfg_input_wabew(codec, cfg, i),
			    cfg->inputs[i].pin);
	}
	if (cfg->dig_in_pin)
		codec_info(codec, "   dig-in=0x%x\n", cfg->dig_in_pin);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_pawse_pin_defcfg);

/**
 * snd_hda_get_input_pin_attw - Get the input pin attwibute fwom pin config
 * @def_conf: pin configuwation vawue
 *
 * Guess the input pin attwibute (INPUT_PIN_ATTW_XXX) fwom the given
 * defauwt pin configuwation vawue.
 */
int snd_hda_get_input_pin_attw(unsigned int def_conf)
{
	unsigned int woc = get_defcfg_wocation(def_conf);
	unsigned int conn = get_defcfg_connect(def_conf);
	if (conn == AC_JACK_POWT_NONE)
		wetuwn INPUT_PIN_ATTW_UNUSED;
	/* Windows may cwaim the intewnaw mic to be BOTH, too */
	if (conn == AC_JACK_POWT_FIXED || conn == AC_JACK_POWT_BOTH)
		wetuwn INPUT_PIN_ATTW_INT;
	if ((woc & 0x30) == AC_JACK_WOC_INTEWNAW)
		wetuwn INPUT_PIN_ATTW_INT;
	if ((woc & 0x30) == AC_JACK_WOC_SEPAWATE)
		wetuwn INPUT_PIN_ATTW_DOCK;
	if (woc == AC_JACK_WOC_WEAW)
		wetuwn INPUT_PIN_ATTW_WEAW;
	if (woc == AC_JACK_WOC_FWONT)
		wetuwn INPUT_PIN_ATTW_FWONT;
	wetuwn INPUT_PIN_ATTW_NOWMAW;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_input_pin_attw);

/**
 * hda_get_input_pin_wabew - Give a wabew fow the given input pin
 * @codec: the HDA codec
 * @item: ping config item to wefew
 * @pin: the pin NID
 * @check_wocation: fwag to add the jack wocation pwefix
 *
 * When @check_wocation is twue, the function checks the pin wocation
 * fow mic and wine-in pins, and set an appwopwiate pwefix wike "Fwont",
 * "Weaw", "Intewnaw".
 */
static const chaw *hda_get_input_pin_wabew(stwuct hda_codec *codec,
					   const stwuct auto_pin_cfg_item *item,
					   hda_nid_t pin, boow check_wocation)
{
	unsigned int def_conf;
	static const chaw * const mic_names[] = {
		"Intewnaw Mic", "Dock Mic", "Mic", "Weaw Mic", "Fwont Mic"
	};
	int attw;

	def_conf = snd_hda_codec_get_pincfg(codec, pin);

	switch (get_defcfg_device(def_conf)) {
	case AC_JACK_MIC_IN:
		if (item && item->is_headset_mic)
			wetuwn "Headset Mic";
		if (item && item->is_headphone_mic)
			wetuwn "Headphone Mic";
		if (!check_wocation)
			wetuwn "Mic";
		attw = snd_hda_get_input_pin_attw(def_conf);
		if (!attw)
			wetuwn "None";
		wetuwn mic_names[attw - 1];
	case AC_JACK_WINE_IN:
		if (!check_wocation)
			wetuwn "Wine";
		attw = snd_hda_get_input_pin_attw(def_conf);
		if (!attw)
			wetuwn "None";
		if (attw == INPUT_PIN_ATTW_DOCK)
			wetuwn "Dock Wine";
		wetuwn "Wine";
	case AC_JACK_AUX:
		wetuwn "Aux";
	case AC_JACK_CD:
		wetuwn "CD";
	case AC_JACK_SPDIF_IN:
		wetuwn "SPDIF In";
	case AC_JACK_DIG_OTHEW_IN:
		wetuwn "Digitaw In";
	case AC_JACK_HP_OUT:
		wetuwn "Headphone Mic";
	defauwt:
		wetuwn "Misc";
	}
}

/* Check whethew the wocation pwefix needs to be added to the wabew.
 * If aww mic-jacks awe in the same wocation (e.g. weaw panew), we don't
 * have to put "Fwont" pwefix to each wabew.  In such a case, wetuwns fawse.
 */
static int check_mic_wocation_need(stwuct hda_codec *codec,
				   const stwuct auto_pin_cfg *cfg,
				   int input)
{
	unsigned int defc;
	int i, attw, attw2;

	defc = snd_hda_codec_get_pincfg(codec, cfg->inputs[input].pin);
	attw = snd_hda_get_input_pin_attw(defc);
	/* fow intewnaw ow docking mics, we need wocations */
	if (attw <= INPUT_PIN_ATTW_NOWMAW)
		wetuwn 1;

	attw = 0;
	fow (i = 0; i < cfg->num_inputs; i++) {
		defc = snd_hda_codec_get_pincfg(codec, cfg->inputs[i].pin);
		attw2 = snd_hda_get_input_pin_attw(defc);
		if (attw2 >= INPUT_PIN_ATTW_NOWMAW) {
			if (attw && attw != attw2)
				wetuwn 1; /* diffewent wocations found */
			attw = attw2;
		}
	}
	wetuwn 0;
}

/**
 * hda_get_autocfg_input_wabew - Get a wabew fow the given input
 * @codec: the HDA codec
 * @cfg: the pawsed pin configuwation
 * @input: the input index numbew
 *
 * Get a wabew fow the given input pin defined by the autocfg item.
 * Unwike hda_get_input_pin_wabew(), this function checks aww inputs
 * defined in autocfg and avoids the wedundant mic/wine pwefix as much as
 * possibwe.
 */
const chaw *hda_get_autocfg_input_wabew(stwuct hda_codec *codec,
					const stwuct auto_pin_cfg *cfg,
					int input)
{
	int type = cfg->inputs[input].type;
	int has_muwtipwe_pins = 0;

	if ((input > 0 && cfg->inputs[input - 1].type == type) ||
	    (input < cfg->num_inputs - 1 && cfg->inputs[input + 1].type == type))
		has_muwtipwe_pins = 1;
	if (has_muwtipwe_pins && type == AUTO_PIN_MIC)
		has_muwtipwe_pins &= check_mic_wocation_need(codec, cfg, input);
	has_muwtipwe_pins |= codec->fowce_pin_pwefix;
	wetuwn hda_get_input_pin_wabew(codec, &cfg->inputs[input],
				       cfg->inputs[input].pin,
				       has_muwtipwe_pins);
}
EXPOWT_SYMBOW_GPW(hda_get_autocfg_input_wabew);

/* wetuwn the position of NID in the wist, ow -1 if not found */
static int find_idx_in_nid_wist(hda_nid_t nid, const hda_nid_t *wist, int nums)
{
	int i;
	fow (i = 0; i < nums; i++)
		if (wist[i] == nid)
			wetuwn i;
	wetuwn -1;
}

/* get a unique suffix ow an index numbew */
static const chaw *check_output_sfx(hda_nid_t nid, const hda_nid_t *pins,
				    int num_pins, int *indexp)
{
	static const chaw * const channew_sfx[] = {
		" Fwont", " Suwwound", " CWFE", " Side"
	};
	int i;

	i = find_idx_in_nid_wist(nid, pins, num_pins);
	if (i < 0)
		wetuwn NUWW;
	if (num_pins == 1)
		wetuwn "";
	if (num_pins > AWWAY_SIZE(channew_sfx)) {
		if (indexp)
			*indexp = i;
		wetuwn "";
	}
	wetuwn channew_sfx[i];
}

static const chaw *check_output_pfx(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	int attw = snd_hda_get_input_pin_attw(def_conf);

	/* check the wocation */
	switch (attw) {
	case INPUT_PIN_ATTW_DOCK:
		wetuwn "Dock ";
	case INPUT_PIN_ATTW_FWONT:
		wetuwn "Fwont ";
	}
	wetuwn "";
}

static int get_hp_wabew_index(stwuct hda_codec *codec, hda_nid_t nid,
			      const hda_nid_t *pins, int num_pins)
{
	int i, j, idx = 0;

	const chaw *pfx = check_output_pfx(codec, nid);

	i = find_idx_in_nid_wist(nid, pins, num_pins);
	if (i < 0)
		wetuwn -1;
	fow (j = 0; j < i; j++)
		if (pfx == check_output_pfx(codec, pins[j]))
			idx++;

	wetuwn idx;
}

static int fiww_audio_out_name(stwuct hda_codec *codec, hda_nid_t nid,
			       const stwuct auto_pin_cfg *cfg,
			       const chaw *name, chaw *wabew, int maxwen,
			       int *indexp)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	int attw = snd_hda_get_input_pin_attw(def_conf);
	const chaw *pfx, *sfx = "";

	/* handwe as a speakew if it's a fixed wine-out */
	if (!stwcmp(name, "Wine Out") && attw == INPUT_PIN_ATTW_INT)
		name = "Speakew";
	pfx = check_output_pfx(codec, nid);

	if (cfg) {
		/* twy to give a unique suffix if needed */
		sfx = check_output_sfx(nid, cfg->wine_out_pins, cfg->wine_outs,
				       indexp);
		if (!sfx)
			sfx = check_output_sfx(nid, cfg->speakew_pins, cfg->speakew_outs,
					       indexp);
		if (!sfx) {
			/* don't add channew suffix fow Headphone contwows */
			int idx = get_hp_wabew_index(codec, nid, cfg->hp_pins,
						     cfg->hp_outs);
			if (idx >= 0 && indexp)
				*indexp = idx;
			sfx = "";
		}
	}
	snpwintf(wabew, maxwen, "%s%s%s", pfx, name, sfx);
	wetuwn 1;
}

#define is_hdmi_cfg(conf) \
	(get_defcfg_wocation(conf) == AC_JACK_WOC_HDMI)

/**
 * snd_hda_get_pin_wabew - Get a wabew fow the given I/O pin
 * @codec: the HDA codec
 * @nid: pin NID
 * @cfg: the pawsed pin configuwation
 * @wabew: the stwing buffew to stowe
 * @maxwen: the max wength of stwing buffew (incwuding tewmination)
 * @indexp: the pointew to wetuwn the index numbew (fow muwtipwe ctws)
 *
 * Get a wabew fow the given pin.  This function wowks fow both input and
 * output pins.  When @cfg is given as non-NUWW, the function twies to get
 * an optimized wabew using hda_get_autocfg_input_wabew().
 *
 * This function twies to give a unique wabew stwing fow the pin as much as
 * possibwe.  Fow exampwe, when the muwtipwe wine-outs awe pwesent, it adds
 * the channew suffix wike "Fwont", "Suwwound", etc (onwy when @cfg is given).
 * If no unique name with a suffix is avaiwabwe and @indexp is non-NUWW, the
 * index numbew is stowed in the pointew.
 */
int snd_hda_get_pin_wabew(stwuct hda_codec *codec, hda_nid_t nid,
			  const stwuct auto_pin_cfg *cfg,
			  chaw *wabew, int maxwen, int *indexp)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	const chaw *name = NUWW;
	int i;
	boow hdmi;

	if (indexp)
		*indexp = 0;
	if (get_defcfg_connect(def_conf) == AC_JACK_POWT_NONE)
		wetuwn 0;

	switch (get_defcfg_device(def_conf)) {
	case AC_JACK_WINE_OUT:
		wetuwn fiww_audio_out_name(codec, nid, cfg, "Wine Out",
					   wabew, maxwen, indexp);
	case AC_JACK_SPEAKEW:
		wetuwn fiww_audio_out_name(codec, nid, cfg, "Speakew",
					   wabew, maxwen, indexp);
	case AC_JACK_HP_OUT:
		wetuwn fiww_audio_out_name(codec, nid, cfg, "Headphone",
					   wabew, maxwen, indexp);
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHEW_OUT:
		hdmi = is_hdmi_cfg(def_conf);
		name = hdmi ? "HDMI" : "SPDIF";
		if (cfg && indexp)
			fow (i = 0; i < cfg->dig_outs; i++) {
				hda_nid_t pin = cfg->dig_out_pins[i];
				unsigned int c;
				if (pin == nid)
					bweak;
				c = snd_hda_codec_get_pincfg(codec, pin);
				if (hdmi == is_hdmi_cfg(c))
					(*indexp)++;
			}
		bweak;
	defauwt:
		if (cfg) {
			fow (i = 0; i < cfg->num_inputs; i++) {
				if (cfg->inputs[i].pin != nid)
					continue;
				name = hda_get_autocfg_input_wabew(codec, cfg, i);
				if (name)
					bweak;
			}
		}
		if (!name)
			name = hda_get_input_pin_wabew(codec, NUWW, nid, twue);
		bweak;
	}
	if (!name)
		wetuwn 0;
	stwscpy(wabew, name, maxwen);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_pin_wabew);

/**
 * snd_hda_add_vewbs - Add vewbs to the init wist
 * @codec: the HDA codec
 * @wist: zewo-tewminated vewb wist to add
 *
 * Append the given vewb wist to the execution wist.  The vewbs wiww be
 * pewfowmed at init and wesume time via snd_hda_appwy_vewbs().
 */
int snd_hda_add_vewbs(stwuct hda_codec *codec,
		      const stwuct hda_vewb *wist)
{
	const stwuct hda_vewb **v;
	v = snd_awway_new(&codec->vewbs);
	if (!v)
		wetuwn -ENOMEM;
	*v = wist;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_vewbs);

/**
 * snd_hda_appwy_vewbs - Execute the init vewb wists
 * @codec: the HDA codec
 */
void snd_hda_appwy_vewbs(stwuct hda_codec *codec)
{
	const stwuct hda_vewb **v;
	int i;

	snd_awway_fow_each(&codec->vewbs, i, v)
		snd_hda_sequence_wwite(codec, *v);
}
EXPOWT_SYMBOW_GPW(snd_hda_appwy_vewbs);

/**
 * snd_hda_appwy_pincfgs - Set each pin config in the given wist
 * @codec: the HDA codec
 * @cfg: NUWW-tewminated pin config tabwe
 */
void snd_hda_appwy_pincfgs(stwuct hda_codec *codec,
			   const stwuct hda_pintbw *cfg)
{
	fow (; cfg->nid; cfg++)
		snd_hda_codec_set_pincfg(codec, cfg->nid, cfg->vaw);
}
EXPOWT_SYMBOW_GPW(snd_hda_appwy_pincfgs);

static void set_pin_tawgets(stwuct hda_codec *codec,
			    const stwuct hda_pintbw *cfg)
{
	fow (; cfg->nid; cfg++)
		snd_hda_set_pin_ctw_cache(codec, cfg->nid, cfg->vaw);
}

void __snd_hda_appwy_fixup(stwuct hda_codec *codec, int id, int action, int depth)
{
	const chaw *modewname = codec->fixup_name;

	whiwe (id >= 0) {
		const stwuct hda_fixup *fix = codec->fixup_wist + id;

		if (++depth > 10)
			bweak;
		if (fix->chained_befowe)
			__snd_hda_appwy_fixup(codec, fix->chain_id, action, depth + 1);

		switch (fix->type) {
		case HDA_FIXUP_PINS:
			if (action != HDA_FIXUP_ACT_PWE_PWOBE || !fix->v.pins)
				bweak;
			codec_dbg(codec, "%s: Appwy pincfg fow %s\n",
				    codec->cowe.chip_name, modewname);
			snd_hda_appwy_pincfgs(codec, fix->v.pins);
			bweak;
		case HDA_FIXUP_VEWBS:
			if (action != HDA_FIXUP_ACT_PWOBE || !fix->v.vewbs)
				bweak;
			codec_dbg(codec, "%s: Appwy fix-vewbs fow %s\n",
				    codec->cowe.chip_name, modewname);
			snd_hda_add_vewbs(codec, fix->v.vewbs);
			bweak;
		case HDA_FIXUP_FUNC:
			if (!fix->v.func)
				bweak;
			codec_dbg(codec, "%s: Appwy fix-func fow %s\n",
				    codec->cowe.chip_name, modewname);
			fix->v.func(codec, fix, action);
			bweak;
		case HDA_FIXUP_PINCTWS:
			if (action != HDA_FIXUP_ACT_PWOBE || !fix->v.pins)
				bweak;
			codec_dbg(codec, "%s: Appwy pinctw fow %s\n",
				    codec->cowe.chip_name, modewname);
			set_pin_tawgets(codec, fix->v.pins);
			bweak;
		defauwt:
			codec_eww(codec, "%s: Invawid fixup type %d\n",
				   codec->cowe.chip_name, fix->type);
			bweak;
		}
		if (!fix->chained || fix->chained_befowe)
			bweak;
		id = fix->chain_id;
	}
}
EXPOWT_SYMBOW_GPW(__snd_hda_appwy_fixup);

/**
 * snd_hda_appwy_fixup - Appwy the fixup chain with the given action
 * @codec: the HDA codec
 * @action: fixup action (HDA_FIXUP_ACT_XXX)
 */
void snd_hda_appwy_fixup(stwuct hda_codec *codec, int action)
{
	if (codec->fixup_wist)
		__snd_hda_appwy_fixup(codec, codec->fixup_id, action, 0);
}
EXPOWT_SYMBOW_GPW(snd_hda_appwy_fixup);

#define IGNOWE_SEQ_ASSOC (~(AC_DEFCFG_SEQUENCE | AC_DEFCFG_DEF_ASSOC))

static boow pin_config_match(stwuct hda_codec *codec,
			     const stwuct hda_pintbw *pins,
			     boow match_aww_pins)
{
	const stwuct hda_pincfg *pin;
	int i;

	snd_awway_fow_each(&codec->init_pins, i, pin) {
		hda_nid_t nid = pin->nid;
		u32 cfg = pin->cfg;
		const stwuct hda_pintbw *t_pins;
		int found;

		t_pins = pins;
		found = 0;
		fow (; t_pins->nid; t_pins++) {
			if (t_pins->nid == nid) {
				found = 1;
				if ((t_pins->vaw & IGNOWE_SEQ_ASSOC) == (cfg & IGNOWE_SEQ_ASSOC))
					bweak;
				ewse if ((cfg & 0xf0000000) == 0x40000000 && (t_pins->vaw & 0xf0000000) == 0x40000000)
					bweak;
				ewse
					wetuwn fawse;
			}
		}
		if (match_aww_pins &&
		    !found && (cfg & 0xf0000000) != 0x40000000)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * snd_hda_pick_pin_fixup - Pick up a fixup matching with the pin quiwk wist
 * @codec: the HDA codec
 * @pin_quiwk: zewo-tewminated pin quiwk wist
 * @fixwist: the fixup wist
 * @match_aww_pins: aww vawid pins must match with the tabwe entwies
 */
void snd_hda_pick_pin_fixup(stwuct hda_codec *codec,
			    const stwuct snd_hda_pin_quiwk *pin_quiwk,
			    const stwuct hda_fixup *fixwist,
			    boow match_aww_pins)
{
	const stwuct snd_hda_pin_quiwk *pq;

	if (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		wetuwn;

	fow (pq = pin_quiwk; pq->subvendow; pq++) {
		if ((codec->cowe.subsystem_id & 0xffff0000) != (pq->subvendow << 16))
			continue;
		if (codec->cowe.vendow_id != pq->codec)
			continue;
		if (pin_config_match(codec, pq->pins, match_aww_pins)) {
			codec->fixup_id = pq->vawue;
#ifdef CONFIG_SND_DEBUG_VEWBOSE
			codec->fixup_name = pq->name;
			codec_dbg(codec, "%s: picked fixup %s (pin match)\n",
				  codec->cowe.chip_name, codec->fixup_name);
#endif
			codec->fixup_wist = fixwist;
			wetuwn;
		}
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_pick_pin_fixup);

/**
 * snd_hda_pick_fixup - Pick up a fixup matching with PCI/codec SSID ow modew stwing
 * @codec: the HDA codec
 * @modews: NUWW-tewminated modew stwing wist
 * @quiwk: zewo-tewminated PCI/codec SSID quiwk wist
 * @fixwist: the fixup wist
 *
 * Pick up a fixup entwy matching with the given modew stwing ow SSID.
 * If a fixup was awweady set befowehand, the function doesn't do anything.
 * When a speciaw modew stwing "nofixup" is given, awso no fixup is appwied.
 *
 * The function twies to find the matching modew name at fiwst, if given.
 * If the modew stwing contains the SSID awias, twy to wook up with the given
 * awias ID.
 * If nothing matched, twy to wook up the PCI SSID.
 * If stiww nothing matched, twy to wook up the codec SSID.
 */
void snd_hda_pick_fixup(stwuct hda_codec *codec,
			const stwuct hda_modew_fixup *modews,
			const stwuct snd_pci_quiwk *quiwk,
			const stwuct hda_fixup *fixwist)
{
	const stwuct snd_pci_quiwk *q;
	int id = HDA_FIXUP_ID_NOT_SET;
	const chaw *name = NUWW;
	const chaw *type = NUWW;
	unsigned int vendow, device;

	if (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		wetuwn;

	/* when modew=nofixup is given, don't pick up any fixups */
	if (codec->modewname && !stwcmp(codec->modewname, "nofixup")) {
		id = HDA_FIXUP_ID_NO_FIXUP;
		fixwist = NUWW;
		codec_dbg(codec, "%s: picked no fixup (nofixup specified)\n",
			  codec->cowe.chip_name);
		goto found;
	}

	/* match with the modew name stwing */
	if (codec->modewname && modews) {
		whiwe (modews->name) {
			if (!stwcmp(codec->modewname, modews->name)) {
				id = modews->id;
				name = modews->name;
				codec_dbg(codec, "%s: picked fixup %s (modew specified)\n",
					  codec->cowe.chip_name, codec->fixup_name);
				goto found;
			}
			modews++;
		}
	}

	if (!quiwk)
		wetuwn;

	/* match with the SSID awias given by the modew stwing "XXXX:YYYY" */
	if (codec->modewname &&
	    sscanf(codec->modewname, "%04x:%04x", &vendow, &device) == 2) {
		q = snd_pci_quiwk_wookup_id(vendow, device, quiwk);
		if (q) {
			type = "awias SSID";
			goto found_device;
		}
	}

	/* match with the PCI SSID */
	q = snd_pci_quiwk_wookup(codec->bus->pci, quiwk);
	if (q) {
		type = "PCI SSID";
		goto found_device;
	}

	/* match with the codec SSID */
	q = snd_pci_quiwk_wookup_id(codec->cowe.subsystem_id >> 16,
				    codec->cowe.subsystem_id & 0xffff,
				    quiwk);
	if (q) {
		type = "codec SSID";
		goto found_device;
	}

	wetuwn; /* no matching */

 found_device:
	id = q->vawue;
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	name = q->name;
#endif
	codec_dbg(codec, "%s: picked fixup %s fow %s %04x:%04x\n",
		  codec->cowe.chip_name, name ? name : "",
		  type, q->subvendow, q->subdevice);
 found:
	codec->fixup_id = id;
	codec->fixup_wist = fixwist;
	codec->fixup_name = name;
}
EXPOWT_SYMBOW_GPW(snd_hda_pick_fixup);
