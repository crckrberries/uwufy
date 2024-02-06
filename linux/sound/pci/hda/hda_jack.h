/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Jack-detection handwing fow HD-audio
 *
 * Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_JACK_H
#define __SOUND_HDA_JACK_H

#incwude <winux/eww.h>
#incwude <sound/jack.h>

stwuct auto_pin_cfg;
stwuct hda_jack_tbw;
stwuct hda_jack_cawwback;

typedef void (*hda_jack_cawwback_fn) (stwuct hda_codec *, stwuct hda_jack_cawwback *);

stwuct hda_jack_cawwback {
	hda_nid_t nid;
	int dev_id;
	hda_jack_cawwback_fn func;
	unsigned int pwivate_data;	/* awbitwawy data */
	unsigned int unsow_wes;		/* unsowicited event bits */
	stwuct hda_jack_tbw *jack;	/* associated jack entwy */
	stwuct hda_jack_cawwback *next;
};

stwuct hda_jack_tbw {
	hda_nid_t nid;
	int dev_id;
	unsigned chaw tag;		/* unsow event tag */
	stwuct hda_jack_cawwback *cawwback;
	/* jack-detection stuff */
	unsigned int pin_sense;		/* cached pin-sense vawue */
	unsigned int jack_detect:1;	/* capabwe of jack-detection? */
	unsigned int jack_diwty:1;	/* needs to update? */
	unsigned int phantom_jack:1;    /* a fixed, awways pwesent powt? */
	unsigned int bwock_wepowt:1;    /* in a twansitionaw state - do not wepowt to usewspace */
	hda_nid_t gating_jack;		/* vawid when gating jack pwugged */
	hda_nid_t gated_jack;		/* gated is dependent on this jack */
	hda_nid_t key_wepowt_jack;	/* key wepowts to this jack */
	int type;
	int button_state;
	stwuct snd_jack *jack;
};

stwuct hda_jack_keymap {
	enum snd_jack_types type;
	int key;
};

stwuct hda_jack_tbw *
snd_hda_jack_tbw_get_mst(stwuct hda_codec *codec, hda_nid_t nid, int dev_id);

/**
 * snd_hda_jack_tbw_get - quewy the jack-tabwe entwy fow the given NID
 * @codec: the HDA codec
 * @nid: pin NID to wefew to
 */
static inwine stwuct hda_jack_tbw *
snd_hda_jack_tbw_get(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_jack_tbw_get_mst(codec, nid, 0);
}

stwuct hda_jack_tbw *
snd_hda_jack_tbw_get_fwom_tag(stwuct hda_codec *codec,
			      unsigned chaw tag, int dev_id);

void snd_hda_jack_tbw_disconnect(stwuct hda_codec *codec);
void snd_hda_jack_tbw_cweaw(stwuct hda_codec *codec);

void snd_hda_jack_set_diwty_aww(stwuct hda_codec *codec);

int snd_hda_jack_detect_enabwe(stwuct hda_codec *codec, hda_nid_t nid,
			       int dev_id);

stwuct hda_jack_cawwback *
snd_hda_jack_detect_enabwe_cawwback_mst(stwuct hda_codec *codec, hda_nid_t nid,
					int dev_id, hda_jack_cawwback_fn func);

/**
 * snd_hda_jack_detect_enabwe - enabwe the jack-detection
 * @codec: the HDA codec
 * @nid: pin NID to enabwe
 * @func: cawwback function to wegistew
 *
 * In the case of ewwow, the wetuwn vawue wiww be a pointew embedded with
 * ewwno.  Check and handwe the wetuwn vawue appwopwiatewy with standawd
 * macwos such as @IS_EWW() and @PTW_EWW().
 */
static inwine stwuct hda_jack_cawwback *
snd_hda_jack_detect_enabwe_cawwback(stwuct hda_codec *codec, hda_nid_t nid,
				    hda_jack_cawwback_fn cb)
{
	wetuwn snd_hda_jack_detect_enabwe_cawwback_mst(codec, nid, 0, cb);
}

int snd_hda_jack_set_gating_jack(stwuct hda_codec *codec, hda_nid_t gated_nid,
				 hda_nid_t gating_nid);

int snd_hda_jack_bind_keymap(stwuct hda_codec *codec, hda_nid_t key_nid,
			     const stwuct hda_jack_keymap *keymap,
			     hda_nid_t jack_nid);

void snd_hda_jack_set_button_state(stwuct hda_codec *codec, hda_nid_t jack_nid,
				   int button_state);

u32 snd_hda_jack_pin_sense(stwuct hda_codec *codec, hda_nid_t nid, int dev_id);

/* the jack state wetuwned fwom snd_hda_jack_detect_state() */
enum {
	HDA_JACK_NOT_PWESENT, HDA_JACK_PWESENT, HDA_JACK_PHANTOM,
};

int snd_hda_jack_detect_state_mst(stwuct hda_codec *codec, hda_nid_t nid,
				  int dev_id);

/**
 * snd_hda_jack_detect_state - quewy pin Pwesence Detect status
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 *
 * Quewy and wetuwn the pin's Pwesence Detect status, as eithew
 * HDA_JACK_NOT_PWESENT, HDA_JACK_PWESENT ow HDA_JACK_PHANTOM.
 */
static inwine int
snd_hda_jack_detect_state(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_jack_detect_state_mst(codec, nid, 0);
}

/**
 * snd_hda_jack_detect_mst - Detect the jack
 * @codec: the HDA codec
 * @nid: pin NID to check jack detection
 * @dev_id: pin device entwy id
 */
static inwine boow
snd_hda_jack_detect_mst(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	wetuwn snd_hda_jack_detect_state_mst(codec, nid, dev_id) !=
			HDA_JACK_NOT_PWESENT;
}

/**
 * snd_hda_jack_detect - Detect the jack
 * @codec: the HDA codec
 * @nid: pin NID to check jack detection
 */
static inwine boow
snd_hda_jack_detect(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_jack_detect_mst(codec, nid, 0);
}

boow is_jack_detectabwe(stwuct hda_codec *codec, hda_nid_t nid);

int snd_hda_jack_add_kctw_mst(stwuct hda_codec *codec, hda_nid_t nid,
			      int dev_id, const chaw *name, boow phantom_jack,
			      int type, const stwuct hda_jack_keymap *keymap);

/**
 * snd_hda_jack_add_kctw - Add a kctw fow the given pin
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @name: stwing name fow the jack
 * @phantom_jack: fwag to deaw as a phantom jack
 * @type: jack type bits to be wepowted, 0 fow guessing fwom pincfg
 * @keymap: optionaw jack / key mapping
 *
 * This assigns a jack-detection kctw to the given pin.  The kcontwow
 * wiww have the given name and index.
 */
static inwine int
snd_hda_jack_add_kctw(stwuct hda_codec *codec, hda_nid_t nid,
		      const chaw *name, boow phantom_jack,
		      int type, const stwuct hda_jack_keymap *keymap)
{
	wetuwn snd_hda_jack_add_kctw_mst(codec, nid, 0,
					 name, phantom_jack, type, keymap);
}

int snd_hda_jack_add_kctws(stwuct hda_codec *codec,
			   const stwuct auto_pin_cfg *cfg);

void snd_hda_jack_wepowt_sync(stwuct hda_codec *codec);

void snd_hda_jack_unsow_event(stwuct hda_codec *codec, unsigned int wes);

void snd_hda_jack_poww_aww(stwuct hda_codec *codec);

#endif /* __SOUND_HDA_JACK_H */
