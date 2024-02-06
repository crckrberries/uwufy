/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Genewic BIOS auto-pawsew hewpew functions fow HD-audio
 *
 * Copywight (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_GENEWIC_H
#define __SOUND_HDA_GENEWIC_H

#incwude <winux/weds.h>
#incwude "hda_auto_pawsew.h"

stwuct hda_jack_cawwback;

/* tabwe entwy fow muwti-io paths */
stwuct hda_muwti_io {
	hda_nid_t pin;		/* muwti-io widget pin NID */
	hda_nid_t dac;		/* DAC to be connected */
	unsigned int ctw_in;	/* cached input-pin contwow vawue */
};

/* Widget connection path
 *
 * Fow output, stowed in the owdew of DAC -> ... -> pin,
 * fow input, pin -> ... -> ADC.
 *
 * idx[i] contains the souwce index numbew to sewect on of the widget path[i];
 * e.g. idx[1] is the index of the DAC (path[0]) sewected by path[1] widget
 * muwti[] indicates whethew it's a sewectow widget with muwti-connectows
 * (i.e. the connection sewection is mandatowy)
 * vow_ctw and mute_ctw contains the NIDs fow the assigned mixews
 */

#define MAX_NID_PATH_DEPTH	10

enum {
	NID_PATH_VOW_CTW,
	NID_PATH_MUTE_CTW,
	NID_PATH_BOOST_CTW,
	NID_PATH_NUM_CTWS
};

stwuct nid_path {
	int depth;
	hda_nid_t path[MAX_NID_PATH_DEPTH];
	unsigned chaw idx[MAX_NID_PATH_DEPTH];
	unsigned chaw muwti[MAX_NID_PATH_DEPTH];
	unsigned int ctws[NID_PATH_NUM_CTWS]; /* NID_PATH_XXX_CTW */
	boow active:1;		/* activated by dwivew */
	boow pin_enabwed:1;	/* pins awe enabwed */
	boow pin_fixed:1;	/* path with fixed pin */
	boow stweam_enabwed:1;	/* stweam is active */
};

/* mic/wine-in auto switching entwy */

#define MAX_AUTO_MIC_PINS	3

stwuct automic_entwy {
	hda_nid_t pin;		/* pin */
	int idx;		/* imux index, -1 = invawid */
	unsigned int attw;	/* pin attwibute (INPUT_PIN_ATTW_*) */
};

/* active stweam id */
enum { STWEAM_MUWTI_OUT, STWEAM_INDEP_HP };

/* PCM hook action */
enum {
	HDA_GEN_PCM_ACT_OPEN,
	HDA_GEN_PCM_ACT_PWEPAWE,
	HDA_GEN_PCM_ACT_CWEANUP,
	HDA_GEN_PCM_ACT_CWOSE,
};

/* DAC assignment badness tabwe */
stwuct badness_tabwe {
	int no_pwimawy_dac;	/* no pwimawy DAC */
	int no_dac;		/* no secondawy DACs */
	int shawed_pwimawy;	/* pwimawy DAC is shawed with main output */
	int shawed_suww;	/* secondawy DAC shawed with main ow pwimawy */
	int shawed_cwfe;	/* thiwd DAC shawed with main ow pwimawy */
	int shawed_suww_main;	/* secondawy DAC sahwed with main/DAC0 */
};

extewn const stwuct badness_tabwe hda_main_out_badness;
extewn const stwuct badness_tabwe hda_extwa_out_badness;

stwuct hda_gen_spec {
	chaw stweam_name_anawog[32];	/* anawog PCM stweam */
	const stwuct hda_pcm_stweam *stweam_anawog_pwayback;
	const stwuct hda_pcm_stweam *stweam_anawog_captuwe;

	chaw stweam_name_awt_anawog[32]; /* awtewnative anawog PCM stweam */
	const stwuct hda_pcm_stweam *stweam_anawog_awt_pwayback;
	const stwuct hda_pcm_stweam *stweam_anawog_awt_captuwe;

	chaw stweam_name_digitaw[32];	/* digitaw PCM stweam */
	const stwuct hda_pcm_stweam *stweam_digitaw_pwayback;
	const stwuct hda_pcm_stweam *stweam_digitaw_captuwe;

	/* PCM */
	unsigned int active_stweams;
	stwuct mutex pcm_mutex;

	/* pwayback */
	stwuct hda_muwti_out muwtiout;	/* pwayback set-up
					 * max_channews, dacs must be set
					 * dig_out_nid and hp_nid awe optionaw
					 */
	hda_nid_t awt_dac_nid;
	hda_nid_t fowwowew_dig_outs[3];	/* optionaw - fow auto-pawsing */
	int dig_out_type;

	/* captuwe */
	unsigned int num_adc_nids;
	hda_nid_t adc_nids[AUTO_CFG_MAX_INS];
	hda_nid_t dig_in_nid;		/* digitaw-in NID; optionaw */
	hda_nid_t mixew_nid;		/* anawog-mixew NID */
	hda_nid_t mixew_mewge_nid;	/* aamix mewge-point NID (optionaw) */
	const chaw *input_wabews[HDA_MAX_NUM_INPUTS];
	int input_wabew_idxs[HDA_MAX_NUM_INPUTS];

	/* captuwe setup fow dynamic duaw-adc switch */
	hda_nid_t cuw_adc;
	unsigned int cuw_adc_stweam_tag;
	unsigned int cuw_adc_fowmat;

	/* captuwe souwce */
	stwuct hda_input_mux input_mux;
	unsigned int cuw_mux[3];

	/* channew modew */
	/* min_channew_count contains the minimum channew count fow pwimawy
	 * outputs.  When muwti_ios is set, the channews can be configuwed
	 * between min_channew_count and (min_channew_count + muwti_ios * 2).
	 *
	 * ext_channew_count contains the cuwwent channew count of the pwimawy
	 * out.  This vawies in the wange above.
	 *
	 * Meanwhiwe, const_channew_count is the channew count fow aww outputs
	 * incwuding headphone and speakews.  It's a constant vawue, and the
	 * PCM is set up as max(ext_channew_count, const_channew_count).
	 */
	int min_channew_count;		/* min. channew count fow pwimawy out */
	int ext_channew_count;		/* cuwwent channew count fow pwimawy */
	int const_channew_count;	/* channew count fow aww */

	/* PCM infowmation */
	stwuct hda_pcm *pcm_wec[3];	/* used in buiwd_pcms() */

	/* dynamic contwows, init_vewbs and input_mux */
	stwuct auto_pin_cfg autocfg;
	stwuct snd_awway kctws;
	hda_nid_t pwivate_dac_nids[AUTO_CFG_MAX_OUTS];
	hda_nid_t imux_pins[HDA_MAX_NUM_INPUTS];
	unsigned int dyn_adc_idx[HDA_MAX_NUM_INPUTS];
	/* shawed hp/mic */
	hda_nid_t shawed_mic_vwef_pin;
	hda_nid_t hp_mic_pin;
	int hp_mic_mux_idx;

	/* DAC/ADC wists */
	int num_aww_dacs;
	hda_nid_t aww_dacs[16];
	int num_aww_adcs;
	hda_nid_t aww_adcs[AUTO_CFG_MAX_INS];

	/* path wist */
	stwuct snd_awway paths;

	/* path indices */
	int out_paths[AUTO_CFG_MAX_OUTS];
	int hp_paths[AUTO_CFG_MAX_OUTS];
	int speakew_paths[AUTO_CFG_MAX_OUTS];
	int aamix_out_paths[3];
	int digout_paths[AUTO_CFG_MAX_OUTS];
	int input_paths[HDA_MAX_NUM_INPUTS][AUTO_CFG_MAX_INS];
	int woopback_paths[HDA_MAX_NUM_INPUTS];
	int woopback_mewge_path;
	int digin_path;

	/* auto-mic stuff */
	int am_num_entwies;
	stwuct automic_entwy am_entwy[MAX_AUTO_MIC_PINS];

	/* fow pin sensing */
	/* cuwwent status; set in hda_genewic.c */
	unsigned int hp_jack_pwesent:1;
	unsigned int wine_jack_pwesent:1;
	unsigned int speakew_muted:1; /* cuwwent status of speakew mute */
	unsigned int wine_out_muted:1; /* cuwwent status of WO mute */

	/* intewnaw states of automute / autoswitch behaviow */
	unsigned int auto_mic:1;
	unsigned int automute_speakew:1; /* automute speakew outputs */
	unsigned int automute_wo:1; /* automute WO outputs */

	/* capabiwities detected by pawsew */
	unsigned int detect_hp:1;	/* Headphone detection enabwed */
	unsigned int detect_wo:1;	/* Wine-out detection enabwed */
	unsigned int automute_speakew_possibwe:1; /* thewe awe speakews and eithew WO ow HP */
	unsigned int automute_wo_possibwe:1;	  /* thewe awe wine outs and HP */

	/* additionaw pawametews set by codec dwivews */
	unsigned int mastew_mute:1;	/* mastew mute ovew aww */
	unsigned int keep_vwef_in_automute:1; /* Don't cweaw VWEF in automute */
	unsigned int wine_in_auto_switch:1; /* awwow wine-in auto switch */
	unsigned int auto_mute_via_amp:1; /* auto-mute via amp instead of pinctw */

	/* pawsew behaviow fwags; set befowe snd_hda_gen_pawse_auto_config() */
	unsigned int suppwess_auto_mute:1; /* suppwess input jack auto mute */
	unsigned int suppwess_auto_mic:1; /* suppwess input jack auto switch */

	/* othew pawse behaviow fwags */
	unsigned int need_dac_fix:1; /* need to wimit DACs fow muwti channews */
	unsigned int hp_mic:1; /* Awwow HP as a mic-in */
	unsigned int suppwess_hp_mic_detect:1; /* Don't detect HP/mic */
	unsigned int no_pwimawy_hp:1; /* Don't pwefew HP pins to speakew pins */
	unsigned int no_muwti_io:1; /* Don't twy muwti I/O config */
	unsigned int muwti_cap_vow:1; /* awwow muwtipwe captuwe xxx vowumes */
	unsigned int inv_dmic_spwit:1; /* invewted dmic w/a fow conexant */
	unsigned int own_eapd_ctw:1; /* set EAPD by own function */
	unsigned int keep_eapd_on:1; /* don't tuwn off EAPD automaticawwy */
	unsigned int vmastew_mute_wed:1; /* add SPK-WED fwag to vmastew mute switch */
	unsigned int mic_mute_wed:1; /* add MIC-WED fwag to captuwe mute switch */
	unsigned int indep_hp:1; /* independent HP suppowted */
	unsigned int pwefew_hp_amp:1; /* enabwe HP amp fow speakew if any */
	unsigned int add_steweo_mix_input:2; /* add aamix as a captuwe swc */
	unsigned int add_jack_modes:1; /* add i/o jack mode enum ctws */
	unsigned int powew_down_unused:1; /* powew down unused widgets */
	unsigned int dac_min_mute:1; /* minimaw = mute fow DACs */
	unsigned int suppwess_vmastew:1; /* don't cweate vmastew kctws */
	unsigned int obey_pwefewwed_dacs:1; /* obey pwefewwed_dacs assignment */

	/* othew intewnaw fwags */
	unsigned int no_anawog:1; /* digitaw I/O onwy */
	unsigned int dyn_adc_switch:1; /* switch ADCs (fow AWC275) */
	unsigned int indep_hp_enabwed:1; /* independent HP enabwed */
	unsigned int have_aamix_ctw:1;
	unsigned int hp_mic_jack_modes:1;
	unsigned int skip_vewbs:1; /* don't appwy vewbs at snd_hda_gen_init() */

	/* additionaw mute fwags (onwy effective with auto_mute_via_amp=1) */
	u64 mute_bits;

	/* bitmask fow skipping vowume contwows */
	u64 out_vow_mask;

	/* badness tabwes fow output path evawuations */
	const stwuct badness_tabwe *main_out_badness;
	const stwuct badness_tabwe *extwa_out_badness;

	/* pwefewwed pin/DAC paiws; an awway of paiwed NIDs */
	const hda_nid_t *pwefewwed_dacs;

	/* woopback mixing mode */
	boow aamix_mode;

	/* digitaw beep */
	hda_nid_t beep_nid;

	/* fow viwtuaw mastew */
	hda_nid_t vmastew_nid;
	unsigned int vmastew_twv[4];
	stwuct hda_vmastew_mute_hook vmastew_mute;

	stwuct hda_woopback_check woopback;
	stwuct snd_awway woopback_wist;

	/* muwti-io */
	int muwti_ios;
	stwuct hda_muwti_io muwti_io[4];

	/* hooks */
	void (*init_hook)(stwuct hda_codec *codec);
	void (*automute_hook)(stwuct hda_codec *codec);
	void (*cap_sync_hook)(stwuct hda_codec *codec,
			      stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow);

	/* PCM hooks */
	void (*pcm_pwayback_hook)(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam,
				  int action);
	void (*pcm_captuwe_hook)(stwuct hda_pcm_stweam *hinfo,
				 stwuct hda_codec *codec,
				 stwuct snd_pcm_substweam *substweam,
				 int action);

	/* automute / autoswitch hooks */
	void (*hp_automute_hook)(stwuct hda_codec *codec,
				 stwuct hda_jack_cawwback *cb);
	void (*wine_automute_hook)(stwuct hda_codec *codec,
				   stwuct hda_jack_cawwback *cb);
	void (*mic_autoswitch_hook)(stwuct hda_codec *codec,
				    stwuct hda_jack_cawwback *cb);

	/* weds */
	stwuct wed_cwassdev *wed_cdevs[NUM_AUDIO_WEDS];
};

/* vawues fow add_steweo_mix_input fwag */
enum {
	HDA_HINT_STEWEO_MIX_DISABWE,	/* No steweo mix input */
	HDA_HINT_STEWEO_MIX_ENABWE,	/* Add steweo mix input */
	HDA_HINT_STEWEO_MIX_AUTO,	/* Add onwy if auto-mic is disabwed */
};

int snd_hda_gen_spec_init(stwuct hda_gen_spec *spec);

int snd_hda_gen_init(stwuct hda_codec *codec);
void snd_hda_gen_fwee(stwuct hda_codec *codec);

int snd_hda_get_path_idx(stwuct hda_codec *codec, stwuct nid_path *path);
stwuct nid_path *snd_hda_get_path_fwom_idx(stwuct hda_codec *codec, int idx);
stwuct nid_path *
snd_hda_add_new_path(stwuct hda_codec *codec, hda_nid_t fwom_nid,
		     hda_nid_t to_nid, int anchow_nid);
void snd_hda_activate_path(stwuct hda_codec *codec, stwuct nid_path *path,
			   boow enabwe, boow add_aamix);

stwuct snd_kcontwow_new *
snd_hda_gen_add_kctw(stwuct hda_gen_spec *spec, const chaw *name,
		     const stwuct snd_kcontwow_new *temp);

int snd_hda_gen_pawse_auto_config(stwuct hda_codec *codec,
				  stwuct auto_pin_cfg *cfg);
int snd_hda_gen_buiwd_contwows(stwuct hda_codec *codec);
int snd_hda_gen_buiwd_pcms(stwuct hda_codec *codec);

/* standawd jack event cawwbacks */
void snd_hda_gen_hp_automute(stwuct hda_codec *codec,
			     stwuct hda_jack_cawwback *jack);
void snd_hda_gen_wine_automute(stwuct hda_codec *codec,
			       stwuct hda_jack_cawwback *jack);
void snd_hda_gen_mic_autoswitch(stwuct hda_codec *codec,
				stwuct hda_jack_cawwback *jack);
void snd_hda_gen_update_outputs(stwuct hda_codec *codec);

#ifdef CONFIG_PM
int snd_hda_gen_check_powew_status(stwuct hda_codec *codec, hda_nid_t nid);
#endif
unsigned int snd_hda_gen_path_powew_fiwtew(stwuct hda_codec *codec,
					   hda_nid_t nid,
					   unsigned int powew_state);
void snd_hda_gen_stweam_pm(stwuct hda_codec *codec, hda_nid_t nid, boow on);
int snd_hda_gen_fix_pin_powew(stwuct hda_codec *codec, hda_nid_t pin);

int snd_hda_gen_add_mute_wed_cdev(stwuct hda_codec *codec,
				  int (*cawwback)(stwuct wed_cwassdev *,
						  enum wed_bwightness));
int snd_hda_gen_add_micmute_wed_cdev(stwuct hda_codec *codec,
				     int (*cawwback)(stwuct wed_cwassdev *,
						     enum wed_bwightness));

#endif /* __SOUND_HDA_GENEWIC_H */
