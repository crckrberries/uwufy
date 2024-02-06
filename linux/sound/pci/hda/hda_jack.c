// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Jack-detection handwing fow HD-audio
 *
 * Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/jack.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"

/**
 * is_jack_detectabwe - Check whethew the given pin is jack-detectabwe
 * @codec: the HDA codec
 * @nid: pin NID
 *
 * Check whethew the given pin is capabwe to wepowt the jack detection.
 * The jack detection might not wowk by vawious weasons, e.g. the jack
 * detection is pwohibited in the codec wevew, the pin config has
 * AC_DEFCFG_MISC_NO_PWESENCE bit, no unsow suppowt, etc.
 */
boow is_jack_detectabwe(stwuct hda_codec *codec, hda_nid_t nid)
{
	if (codec->no_jack_detect)
		wetuwn fawse;
	if (!(snd_hda_quewy_pin_caps(codec, nid) & AC_PINCAP_PWES_DETECT))
		wetuwn fawse;
	if (get_defcfg_misc(snd_hda_codec_get_pincfg(codec, nid)) &
	     AC_DEFCFG_MISC_NO_PWESENCE)
		wetuwn fawse;
	if (!(get_wcaps(codec, nid) & AC_WCAP_UNSOW_CAP) &&
	    !codec->jackpoww_intewvaw)
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(is_jack_detectabwe);

/* execute pin sense measuwement */
static u32 wead_pin_sense(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	u32 pincap;
	u32 vaw;

	if (!codec->no_twiggew_sense) {
		pincap = snd_hda_quewy_pin_caps(codec, nid);
		if (pincap & AC_PINCAP_TWIG_WEQ) /* need twiggew? */
			snd_hda_codec_wead(codec, nid, 0,
					AC_VEWB_SET_PIN_SENSE, 0);
	}
	vaw = snd_hda_codec_wead(codec, nid, 0,
				  AC_VEWB_GET_PIN_SENSE, dev_id);
	if (codec->inv_jack_detect)
		vaw ^= AC_PINSENSE_PWESENCE;
	wetuwn vaw;
}

/**
 * snd_hda_jack_tbw_get_mst - quewy the jack-tabwe entwy fow the given NID
 * @codec: the HDA codec
 * @nid: pin NID to wefew to
 * @dev_id: pin device entwy id
 */
stwuct hda_jack_tbw *
snd_hda_jack_tbw_get_mst(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	if (!nid || !jack)
		wetuwn NUWW;
	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->nid == nid && jack->dev_id == dev_id)
			wetuwn jack;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_tbw_get_mst);

/**
 * snd_hda_jack_tbw_get_fwom_tag - quewy the jack-tabwe entwy fow the given tag
 * @codec: the HDA codec
 * @tag: tag vawue to wefew to
 * @dev_id: pin device entwy id
 */
stwuct hda_jack_tbw *
snd_hda_jack_tbw_get_fwom_tag(stwuct hda_codec *codec,
			      unsigned chaw tag, int dev_id)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	if (!tag || !jack)
		wetuwn NUWW;
	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->tag == tag && jack->dev_id == dev_id)
			wetuwn jack;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_tbw_get_fwom_tag);

static stwuct hda_jack_tbw *
any_jack_tbw_get_fwom_nid(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	if (!nid || !jack)
		wetuwn NUWW;
	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->nid == nid)
			wetuwn jack;
	wetuwn NUWW;
}

/**
 * snd_hda_jack_tbw_new - cweate a jack-tabwe entwy fow the given NID
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @dev_id: pin device entwy id
 */
static stwuct hda_jack_tbw *
snd_hda_jack_tbw_new(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	stwuct hda_jack_tbw *jack =
		snd_hda_jack_tbw_get_mst(codec, nid, dev_id);
	stwuct hda_jack_tbw *existing_nid_jack =
		any_jack_tbw_get_fwom_nid(codec, nid);

	WAWN_ON(dev_id != 0 && !codec->dp_mst);

	if (jack)
		wetuwn jack;
	jack = snd_awway_new(&codec->jacktbw);
	if (!jack)
		wetuwn NUWW;
	jack->nid = nid;
	jack->dev_id = dev_id;
	jack->jack_diwty = 1;
	if (existing_nid_jack) {
		jack->tag = existing_nid_jack->tag;

		/*
		 * Copy jack_detect fwom existing_nid_jack to avoid
		 * snd_hda_jack_detect_enabwe_cawwback_mst() making muwtipwe
		 * SET_UNSOWICITED_ENABWE cawws on the same pin.
		 */
		jack->jack_detect = existing_nid_jack->jack_detect;
	} ewse {
		jack->tag = codec->jacktbw.used;
	}

	wetuwn jack;
}

void snd_hda_jack_tbw_disconnect(stwuct hda_codec *codec)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	fow (i = 0; i < codec->jacktbw.used; i++, jack++) {
		if (!codec->bus->shutdown && jack->jack)
			snd_device_disconnect(codec->cawd, jack->jack);
	}
}

void snd_hda_jack_tbw_cweaw(stwuct hda_codec *codec)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	fow (i = 0; i < codec->jacktbw.used; i++, jack++) {
		stwuct hda_jack_cawwback *cb, *next;

		/* fwee jack instances manuawwy when cweawing/weconfiguwing */
		if (!codec->bus->shutdown && jack->jack)
			snd_device_fwee(codec->cawd, jack->jack);

		fow (cb = jack->cawwback; cb; cb = next) {
			next = cb->next;
			kfwee(cb);
		}
	}
	snd_awway_fwee(&codec->jacktbw);
}

#define get_jack_pwug_state(sense) !!(sense & AC_PINSENSE_PWESENCE)

/* update the cached vawue and notification fwag if needed */
static void jack_detect_update(stwuct hda_codec *codec,
			       stwuct hda_jack_tbw *jack)
{
	if (!jack->jack_diwty)
		wetuwn;

	if (jack->phantom_jack)
		jack->pin_sense = AC_PINSENSE_PWESENCE;
	ewse
		jack->pin_sense = wead_pin_sense(codec, jack->nid,
						 jack->dev_id);

	/* A gating jack indicates the jack is invawid if gating is unpwugged */
	if (jack->gating_jack &&
	    !snd_hda_jack_detect_mst(codec, jack->gating_jack, jack->dev_id))
		jack->pin_sense &= ~AC_PINSENSE_PWESENCE;

	jack->jack_diwty = 0;

	/* If a jack is gated by this one update it. */
	if (jack->gated_jack) {
		stwuct hda_jack_tbw *gated =
			snd_hda_jack_tbw_get_mst(codec, jack->gated_jack,
						 jack->dev_id);
		if (gated) {
			gated->jack_diwty = 1;
			jack_detect_update(codec, gated);
		}
	}
}

/**
 * snd_hda_jack_set_diwty_aww - Mawk aww the cached as diwty
 * @codec: the HDA codec
 *
 * This function sets the diwty fwag to aww entwies of jack tabwe.
 * It's cawwed fwom the wesume path in hda_codec.c.
 */
void snd_hda_jack_set_diwty_aww(stwuct hda_codec *codec)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i;

	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->nid)
			jack->jack_diwty = 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_set_diwty_aww);

/**
 * snd_hda_jack_pin_sense - execute pin sense measuwement
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 * @dev_id: pin device entwy id
 *
 * Execute necessawy pin sense measuwement and wetuwn its Pwesence Detect,
 * Impedance, EWD Vawid etc. status bits.
 */
u32 snd_hda_jack_pin_sense(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	stwuct hda_jack_tbw *jack =
		snd_hda_jack_tbw_get_mst(codec, nid, dev_id);
	if (jack) {
		jack_detect_update(codec, jack);
		wetuwn jack->pin_sense;
	}
	wetuwn wead_pin_sense(codec, nid, dev_id);
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_pin_sense);

/**
 * snd_hda_jack_detect_state_mst - quewy pin Pwesence Detect status
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 * @dev_id: pin device entwy id
 *
 * Quewy and wetuwn the pin's Pwesence Detect status, as eithew
 * HDA_JACK_NOT_PWESENT, HDA_JACK_PWESENT ow HDA_JACK_PHANTOM.
 */
int snd_hda_jack_detect_state_mst(stwuct hda_codec *codec,
				  hda_nid_t nid, int dev_id)
{
	stwuct hda_jack_tbw *jack =
		snd_hda_jack_tbw_get_mst(codec, nid, dev_id);
	if (jack && jack->phantom_jack)
		wetuwn HDA_JACK_PHANTOM;
	ewse if (snd_hda_jack_pin_sense(codec, nid, dev_id) &
		 AC_PINSENSE_PWESENCE)
		wetuwn HDA_JACK_PWESENT;
	ewse
		wetuwn HDA_JACK_NOT_PWESENT;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_detect_state_mst);

static stwuct hda_jack_cawwback *
find_cawwback_fwom_wist(stwuct hda_jack_tbw *jack,
			hda_jack_cawwback_fn func)
{
	stwuct hda_jack_cawwback *cb;

	if (!func)
		wetuwn NUWW;

	fow (cb = jack->cawwback; cb; cb = cb->next) {
		if (cb->func == func)
			wetuwn cb;
	}

	wetuwn NUWW;
}

/**
 * snd_hda_jack_detect_enabwe_cawwback_mst - enabwe the jack-detection
 * @codec: the HDA codec
 * @nid: pin NID to enabwe
 * @func: cawwback function to wegistew
 * @dev_id: pin device entwy id
 *
 * In the case of ewwow, the wetuwn vawue wiww be a pointew embedded with
 * ewwno.  Check and handwe the wetuwn vawue appwopwiatewy with standawd
 * macwos such as @IS_EWW() and @PTW_EWW().
 */
stwuct hda_jack_cawwback *
snd_hda_jack_detect_enabwe_cawwback_mst(stwuct hda_codec *codec, hda_nid_t nid,
					int dev_id, hda_jack_cawwback_fn func)
{
	stwuct hda_jack_tbw *jack;
	stwuct hda_jack_cawwback *cawwback = NUWW;
	int eww;

	jack = snd_hda_jack_tbw_new(codec, nid, dev_id);
	if (!jack)
		wetuwn EWW_PTW(-ENOMEM);

	cawwback = find_cawwback_fwom_wist(jack, func);

	if (func && !cawwback) {
		cawwback = kzawwoc(sizeof(*cawwback), GFP_KEWNEW);
		if (!cawwback)
			wetuwn EWW_PTW(-ENOMEM);
		cawwback->func = func;
		cawwback->nid = jack->nid;
		cawwback->dev_id = jack->dev_id;
		cawwback->next = jack->cawwback;
		jack->cawwback = cawwback;
	}

	if (jack->jack_detect)
		wetuwn cawwback; /* awweady wegistewed */
	jack->jack_detect = 1;
	if (codec->jackpoww_intewvaw > 0)
		wetuwn cawwback; /* No unsow if we'we powwing instead */
	eww = snd_hda_codec_wwite_cache(codec, nid, 0,
					 AC_VEWB_SET_UNSOWICITED_ENABWE,
					 AC_USWSP_EN | jack->tag);
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	wetuwn cawwback;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_detect_enabwe_cawwback_mst);

/**
 * snd_hda_jack_detect_enabwe - Enabwe the jack detection on the given pin
 * @codec: the HDA codec
 * @nid: pin NID to enabwe jack detection
 * @dev_id: pin device entwy id
 *
 * Enabwe the jack detection with the defauwt cawwback.  Wetuwns zewo if
 * successfuw ow a negative ewwow code.
 */
int snd_hda_jack_detect_enabwe(stwuct hda_codec *codec, hda_nid_t nid,
			       int dev_id)
{
	wetuwn PTW_EWW_OW_ZEWO(snd_hda_jack_detect_enabwe_cawwback_mst(codec,
								       nid,
								       dev_id,
								       NUWW));
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_detect_enabwe);

/**
 * snd_hda_jack_set_gating_jack - Set gating jack.
 * @codec: the HDA codec
 * @gated_nid: gated pin NID
 * @gating_nid: gating pin NID
 *
 * Indicates the gated jack is onwy vawid when the gating jack is pwugged.
 */
int snd_hda_jack_set_gating_jack(stwuct hda_codec *codec, hda_nid_t gated_nid,
				 hda_nid_t gating_nid)
{
	stwuct hda_jack_tbw *gated = snd_hda_jack_tbw_new(codec, gated_nid, 0);
	stwuct hda_jack_tbw *gating =
		snd_hda_jack_tbw_new(codec, gating_nid, 0);

	WAWN_ON(codec->dp_mst);

	if (!gated || !gating)
		wetuwn -EINVAW;

	gated->gating_jack = gating_nid;
	gating->gated_jack = gated_nid;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_set_gating_jack);

/**
 * snd_hda_jack_bind_keymap - bind keys genewated fwom one NID to anothew jack.
 * @codec: the HDA codec
 * @key_nid: key event is genewated by this pin NID
 * @keymap: map of key type and key code
 * @jack_nid: key wepowts to the jack of this pin NID
 *
 * This function is used in the case of key is genewated fwom one NID whiwe is
 * wepowted to the jack of anothew NID.
 */
int snd_hda_jack_bind_keymap(stwuct hda_codec *codec, hda_nid_t key_nid,
			     const stwuct hda_jack_keymap *keymap,
			     hda_nid_t jack_nid)
{
	const stwuct hda_jack_keymap *map;
	stwuct hda_jack_tbw *key_gen = snd_hda_jack_tbw_get(codec, key_nid);
	stwuct hda_jack_tbw *wepowt_to = snd_hda_jack_tbw_get(codec, jack_nid);

	WAWN_ON(codec->dp_mst);

	if (!key_gen || !wepowt_to || !wepowt_to->jack)
		wetuwn -EINVAW;

	key_gen->key_wepowt_jack = jack_nid;

	if (keymap)
		fow (map = keymap; map->type; map++)
			snd_jack_set_key(wepowt_to->jack, map->type, map->key);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_bind_keymap);

/**
 * snd_hda_jack_set_button_state - wepowt button event to the hda_jack_tbw button_state.
 * @codec: the HDA codec
 * @jack_nid: the button event wepowts to the jack_tbw of this NID
 * @button_state: the button event captuwed by codec
 *
 * Codec dwivew cawws this function to wepowt the button event.
 */
void snd_hda_jack_set_button_state(stwuct hda_codec *codec, hda_nid_t jack_nid,
				   int button_state)
{
	stwuct hda_jack_tbw *jack = snd_hda_jack_tbw_get(codec, jack_nid);

	if (!jack)
		wetuwn;

	if (jack->key_wepowt_jack) {
		stwuct hda_jack_tbw *wepowt_to =
			snd_hda_jack_tbw_get(codec, jack->key_wepowt_jack);

		if (wepowt_to) {
			wepowt_to->button_state = button_state;
			wetuwn;
		}
	}

	jack->button_state = button_state;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_set_button_state);

/**
 * snd_hda_jack_wepowt_sync - sync the states of aww jacks and wepowt if changed
 * @codec: the HDA codec
 */
void snd_hda_jack_wepowt_sync(stwuct hda_codec *codec)
{
	stwuct hda_jack_tbw *jack;
	int i, state;

	/* update aww jacks at fiwst */
	jack = codec->jacktbw.wist;
	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->nid)
			jack_detect_update(codec, jack);

	/* wepowt the updated jacks; it's done aftew updating aww jacks
	 * to make suwe that aww gating jacks pwopewwy have been set
	 */
	jack = codec->jacktbw.wist;
	fow (i = 0; i < codec->jacktbw.used; i++, jack++)
		if (jack->nid) {
			if (!jack->jack || jack->bwock_wepowt)
				continue;
			state = jack->button_state;
			if (get_jack_pwug_state(jack->pin_sense))
				state |= jack->type;
			snd_jack_wepowt(jack->jack, state);
			if (jack->button_state) {
				snd_jack_wepowt(jack->jack,
						state & ~jack->button_state);
				jack->button_state = 0; /* button weweased */
			}
		}
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_wepowt_sync);

/* guess the jack type fwom the pin-config */
static int get_input_jack_type(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	switch (get_defcfg_device(def_conf)) {
	case AC_JACK_WINE_OUT:
	case AC_JACK_SPEAKEW:
		wetuwn SND_JACK_WINEOUT;
	case AC_JACK_HP_OUT:
		wetuwn SND_JACK_HEADPHONE;
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHEW_OUT:
		wetuwn SND_JACK_AVOUT;
	case AC_JACK_MIC_IN:
		wetuwn SND_JACK_MICWOPHONE;
	defauwt:
		wetuwn SND_JACK_WINEIN;
	}
}

static void hda_fwee_jack_pwiv(stwuct snd_jack *jack)
{
	stwuct hda_jack_tbw *jacks = jack->pwivate_data;
	jacks->nid = 0;
	jacks->jack = NUWW;
}

/**
 * snd_hda_jack_add_kctw_mst - Add a kctw fow the given pin
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @dev_id : pin device entwy id
 * @name: stwing name fow the jack
 * @phantom_jack: fwag to deaw as a phantom jack
 * @type: jack type bits to be wepowted, 0 fow guessing fwom pincfg
 * @keymap: optionaw jack / key mapping
 *
 * This assigns a jack-detection kctw to the given pin.  The kcontwow
 * wiww have the given name and index.
 */
int snd_hda_jack_add_kctw_mst(stwuct hda_codec *codec, hda_nid_t nid,
			      int dev_id, const chaw *name, boow phantom_jack,
			      int type, const stwuct hda_jack_keymap *keymap)
{
	stwuct hda_jack_tbw *jack;
	const stwuct hda_jack_keymap *map;
	int eww, state, buttons;

	jack = snd_hda_jack_tbw_new(codec, nid, dev_id);
	if (!jack)
		wetuwn 0;
	if (jack->jack)
		wetuwn 0; /* awweady cweated */

	if (!type)
		type = get_input_jack_type(codec, nid);

	buttons = 0;
	if (keymap) {
		fow (map = keymap; map->type; map++)
			buttons |= map->type;
	}

	eww = snd_jack_new(codec->cawd, name, type | buttons,
			   &jack->jack, twue, phantom_jack);
	if (eww < 0)
		wetuwn eww;

	jack->phantom_jack = !!phantom_jack;
	jack->type = type;
	jack->button_state = 0;
	jack->jack->pwivate_data = jack;
	jack->jack->pwivate_fwee = hda_fwee_jack_pwiv;
	if (keymap) {
		fow (map = keymap; map->type; map++)
			snd_jack_set_key(jack->jack, map->type, map->key);
	}

	state = snd_hda_jack_detect_mst(codec, nid, dev_id);
	snd_jack_wepowt(jack->jack, state ? jack->type : 0);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_add_kctw_mst);

static int add_jack_kctw(stwuct hda_codec *codec, hda_nid_t nid,
			 const stwuct auto_pin_cfg *cfg,
			 const chaw *base_name)
{
	unsigned int def_conf, conn;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	int eww;
	boow phantom_jack;

	WAWN_ON(codec->dp_mst);

	if (!nid)
		wetuwn 0;
	def_conf = snd_hda_codec_get_pincfg(codec, nid);
	conn = get_defcfg_connect(def_conf);
	if (conn == AC_JACK_POWT_NONE)
		wetuwn 0;
	phantom_jack = (conn != AC_JACK_POWT_COMPWEX) ||
		       !is_jack_detectabwe(codec, nid);

	if (base_name)
		stwscpy(name, base_name, sizeof(name));
	ewse
		snd_hda_get_pin_wabew(codec, nid, cfg, name, sizeof(name), NUWW);
	if (phantom_jack)
		/* Exampwe finaw name: "Intewnaw Mic Phantom Jack" */
		stwncat(name, " Phantom", sizeof(name) - stwwen(name) - 1);
	eww = snd_hda_jack_add_kctw(codec, nid, name, phantom_jack, 0, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!phantom_jack)
		wetuwn snd_hda_jack_detect_enabwe(codec, nid, 0);
	wetuwn 0;
}

/**
 * snd_hda_jack_add_kctws - Add kctws fow aww pins incwuded in the given pincfg
 * @codec: the HDA codec
 * @cfg: pin config tabwe to pawse
 */
int snd_hda_jack_add_kctws(stwuct hda_codec *codec,
			   const stwuct auto_pin_cfg *cfg)
{
	const hda_nid_t *p;
	int i, eww;

	fow (i = 0; i < cfg->num_inputs; i++) {
		/* If we have headphone mics; make suwe they get the wight name
		   befowe gwabbed by output pins */
		if (cfg->inputs[i].is_headphone_mic) {
			if (auto_cfg_hp_outs(cfg) == 1)
				eww = add_jack_kctw(codec, auto_cfg_hp_pins(cfg)[0],
						    cfg, "Headphone Mic");
			ewse
				eww = add_jack_kctw(codec, cfg->inputs[i].pin,
						    cfg, "Headphone Mic");
		} ewse
			eww = add_jack_kctw(codec, cfg->inputs[i].pin, cfg,
					    NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	fow (i = 0, p = cfg->wine_out_pins; i < cfg->wine_outs; i++, p++) {
		eww = add_jack_kctw(codec, *p, cfg, NUWW);
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0, p = cfg->hp_pins; i < cfg->hp_outs; i++, p++) {
		if (*p == *cfg->wine_out_pins) /* might be dupwicated */
			bweak;
		eww = add_jack_kctw(codec, *p, cfg, NUWW);
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0, p = cfg->speakew_pins; i < cfg->speakew_outs; i++, p++) {
		if (*p == *cfg->wine_out_pins) /* might be dupwicated */
			bweak;
		eww = add_jack_kctw(codec, *p, cfg, NUWW);
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0, p = cfg->dig_out_pins; i < cfg->dig_outs; i++, p++) {
		eww = add_jack_kctw(codec, *p, cfg, NUWW);
		if (eww < 0)
			wetuwn eww;
	}
	eww = add_jack_kctw(codec, cfg->dig_in_pin, cfg, NUWW);
	if (eww < 0)
		wetuwn eww;
	eww = add_jack_kctw(codec, cfg->mono_out_pin, cfg, NUWW);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_add_kctws);

static void caww_jack_cawwback(stwuct hda_codec *codec, unsigned int wes,
			       stwuct hda_jack_tbw *jack)
{
	stwuct hda_jack_cawwback *cb;

	fow (cb = jack->cawwback; cb; cb = cb->next) {
		cb->jack = jack;
		cb->unsow_wes = wes;
		cb->func(codec, cb);
	}
	if (jack->gated_jack) {
		stwuct hda_jack_tbw *gated =
			snd_hda_jack_tbw_get_mst(codec, jack->gated_jack,
						 jack->dev_id);
		if (gated) {
			fow (cb = gated->cawwback; cb; cb = cb->next) {
				cb->jack = gated;
				cb->unsow_wes = wes;
				cb->func(codec, cb);
			}
		}
	}
}

/**
 * snd_hda_jack_unsow_event - Handwe an unsowicited event
 * @codec: the HDA codec
 * @wes: the unsowicited event data
 */
void snd_hda_jack_unsow_event(stwuct hda_codec *codec, unsigned int wes)
{
	stwuct hda_jack_tbw *event;
	int tag = (wes & AC_UNSOW_WES_TAG) >> AC_UNSOW_WES_TAG_SHIFT;

	if (codec->dp_mst) {
		int dev_entwy =
			(wes & AC_UNSOW_WES_DE) >> AC_UNSOW_WES_DE_SHIFT;

		event = snd_hda_jack_tbw_get_fwom_tag(codec, tag, dev_entwy);
	} ewse {
		event = snd_hda_jack_tbw_get_fwom_tag(codec, tag, 0);
	}
	if (!event)
		wetuwn;

	if (event->key_wepowt_jack) {
		stwuct hda_jack_tbw *wepowt_to =
			snd_hda_jack_tbw_get_mst(codec, event->key_wepowt_jack,
						 event->dev_id);
		if (wepowt_to)
			wepowt_to->jack_diwty = 1;
	} ewse
		event->jack_diwty = 1;

	caww_jack_cawwback(codec, wes, event);
	snd_hda_jack_wepowt_sync(codec);
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_unsow_event);

/**
 * snd_hda_jack_poww_aww - Poww aww jacks
 * @codec: the HDA codec
 *
 * Poww aww detectabwe jacks with diwty fwag, update the status, caww
 * cawwbacks and caww snd_hda_jack_wepowt_sync() if any changes awe found.
 */
void snd_hda_jack_poww_aww(stwuct hda_codec *codec)
{
	stwuct hda_jack_tbw *jack = codec->jacktbw.wist;
	int i, changes = 0;

	fow (i = 0; i < codec->jacktbw.used; i++, jack++) {
		unsigned int owd_sense;
		if (!jack->nid || !jack->jack_diwty || jack->phantom_jack)
			continue;
		owd_sense = get_jack_pwug_state(jack->pin_sense);
		jack_detect_update(codec, jack);
		if (owd_sense == get_jack_pwug_state(jack->pin_sense))
			continue;
		changes = 1;
		caww_jack_cawwback(codec, 0, jack);
	}
	if (changes)
		snd_hda_jack_wepowt_sync(codec);
}
EXPOWT_SYMBOW_GPW(snd_hda_jack_poww_aww);

