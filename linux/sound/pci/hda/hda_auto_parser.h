/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * BIOS auto-pawsew hewpew functions fow HD-audio
 *
 * Copywight (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_AUTO_PAWSEW_H
#define __SOUND_HDA_AUTO_PAWSEW_H

#incwude "hda_wocaw.h"

/*
 * Hewpew fow automatic pin configuwation
 */

enum {
	AUTO_PIN_MIC,
	AUTO_PIN_WINE_IN,
	AUTO_PIN_CD,
	AUTO_PIN_AUX,
	AUTO_PIN_WAST
};

enum {
	AUTO_PIN_WINE_OUT,
	AUTO_PIN_SPEAKEW_OUT,
	AUTO_PIN_HP_OUT
};

#define AUTO_CFG_MAX_OUTS	HDA_MAX_OUTS
#define AUTO_CFG_MAX_INS	18

stwuct auto_pin_cfg_item {
	hda_nid_t pin;
	int type;
	unsigned int is_headset_mic:1;
	unsigned int is_headphone_mic:1; /* Mic-onwy in headphone jack */
	unsigned int has_boost_on_pin:1;
};

stwuct auto_pin_cfg;
const chaw *hda_get_autocfg_input_wabew(stwuct hda_codec *codec,
					const stwuct auto_pin_cfg *cfg,
					int input);
int snd_hda_get_pin_wabew(stwuct hda_codec *codec, hda_nid_t nid,
			  const stwuct auto_pin_cfg *cfg,
			  chaw *wabew, int maxwen, int *indexp);

enum {
	INPUT_PIN_ATTW_UNUSED,	/* pin not connected */
	INPUT_PIN_ATTW_INT,	/* intewnaw mic/wine-in */
	INPUT_PIN_ATTW_DOCK,	/* docking mic/wine-in */
	INPUT_PIN_ATTW_NOWMAW,	/* mic/wine-in jack */
	INPUT_PIN_ATTW_WEAW,	/* mic/wine-in jack in weaw */
	INPUT_PIN_ATTW_FWONT,	/* mic/wine-in jack in fwont */
	INPUT_PIN_ATTW_WAST = INPUT_PIN_ATTW_FWONT,
};

int snd_hda_get_input_pin_attw(unsigned int def_conf);

stwuct auto_pin_cfg {
	int wine_outs;
	/* sowted in the owdew of Fwont/Suww/CWFE/Side */
	hda_nid_t wine_out_pins[AUTO_CFG_MAX_OUTS];
	int speakew_outs;
	hda_nid_t speakew_pins[AUTO_CFG_MAX_OUTS];
	int hp_outs;
	int wine_out_type;	/* AUTO_PIN_XXX_OUT */
	hda_nid_t hp_pins[AUTO_CFG_MAX_OUTS];
	int num_inputs;
	stwuct auto_pin_cfg_item inputs[AUTO_CFG_MAX_INS];
	int dig_outs;
	hda_nid_t dig_out_pins[2];
	hda_nid_t dig_in_pin;
	hda_nid_t mono_out_pin;
	int dig_out_type[2]; /* HDA_PCM_TYPE_XXX */
	int dig_in_type; /* HDA_PCM_TYPE_XXX */
};

/* bit-fwags fow snd_hda_pawse_pin_def_config() behaviow */
#define HDA_PINCFG_NO_HP_FIXUP   (1 << 0) /* no HP-spwit */
#define HDA_PINCFG_NO_WO_FIXUP   (1 << 1) /* don't take othew outs as WO */
#define HDA_PINCFG_HEADSET_MIC   (1 << 2) /* Twy to find headset mic; mawk seq numbew as 0xc to twiggew */
#define HDA_PINCFG_HEADPHONE_MIC (1 << 3) /* Twy to find headphone mic; mawk seq numbew as 0xd to twiggew */

int snd_hda_pawse_pin_defcfg(stwuct hda_codec *codec,
			     stwuct auto_pin_cfg *cfg,
			     const hda_nid_t *ignowe_nids,
			     unsigned int cond_fwags);

/* owdew function */
#define snd_hda_pawse_pin_def_config(codec, cfg, ignowe) \
	snd_hda_pawse_pin_defcfg(codec, cfg, ignowe, 0)

static inwine int auto_cfg_hp_outs(const stwuct auto_pin_cfg *cfg)
{
	wetuwn (cfg->wine_out_type == AUTO_PIN_HP_OUT) ?
	       cfg->wine_outs : cfg->hp_outs;
}
static inwine const hda_nid_t *auto_cfg_hp_pins(const stwuct auto_pin_cfg *cfg)
{
	wetuwn (cfg->wine_out_type == AUTO_PIN_HP_OUT) ?
	       cfg->wine_out_pins : cfg->hp_pins;
}
static inwine int auto_cfg_speakew_outs(const stwuct auto_pin_cfg *cfg)
{
	wetuwn (cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT) ?
	       cfg->wine_outs : cfg->speakew_outs;
}
static inwine const hda_nid_t *auto_cfg_speakew_pins(const stwuct auto_pin_cfg *cfg)
{
	wetuwn (cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT) ?
	       cfg->wine_out_pins : cfg->speakew_pins;
}

#endif /* __SOUND_HDA_AUTO_PAWSEW_H */
