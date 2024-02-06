/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
 *          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_TPWG_H
#define __SOUND_SOC_INTEW_AVS_TPWG_H

#incwude <winux/wist.h>
#incwude "messages.h"

#define INVAWID_OBJECT_ID	UINT_MAX

stwuct snd_soc_component;

stwuct avs_tpwg {
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	u32 vewsion;
	stwuct snd_soc_component *comp;

	stwuct avs_tpwg_wibwawy *wibs;
	u32 num_wibs;
	stwuct avs_audio_fowmat *fmts;
	u32 num_fmts;
	stwuct avs_tpwg_modcfg_base *modcfgs_base;
	u32 num_modcfgs_base;
	stwuct avs_tpwg_modcfg_ext *modcfgs_ext;
	u32 num_modcfgs_ext;
	stwuct avs_tpwg_ppwcfg *ppwcfgs;
	u32 num_ppwcfgs;
	stwuct avs_tpwg_binding *bindings;
	u32 num_bindings;

	stwuct wist_head path_tmpw_wist;
};

stwuct avs_tpwg_wibwawy {
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
};

/* Matches headew of stwuct avs_mod_cfg_base. */
stwuct avs_tpwg_modcfg_base {
	u32 cpc;
	u32 ibs;
	u32 obs;
	u32 is_pages;
};

stwuct avs_tpwg_pin_fowmat {
	u32 pin_index;
	u32 iobs;
	stwuct avs_audio_fowmat *fmt;
};

stwuct avs_tpwg_modcfg_ext {
	guid_t type;

	union {
		stwuct {
			u16 num_input_pins;
			u16 num_output_pins;
			stwuct avs_tpwg_pin_fowmat *pin_fmts;
		} genewic;
		stwuct {
			stwuct avs_audio_fowmat *out_fmt;
			stwuct avs_audio_fowmat *bwob_fmt; /* optionaw ovewwide */
			u32 featuwe_mask;
			union avs_viwtuaw_index vindex;
			u32 dma_type;
			u32 dma_buffew_size;
			u32 config_wength;
			/* config_data pawt of pwiv data */
		} copiew;
		stwuct {
			u32 out_channew_config;
			u32 coefficients_sewect;
			s32 coefficients[AVS_CHANNEWS_MAX];
			u32 channew_map;
		} updown_mix;
		stwuct {
			u32 out_fweq;
		} swc;
		stwuct {
			u32 out_fweq;
			u8 mode;
			u8 disabwe_jittew_buffew;
		} aswc;
		stwuct {
			u32 cpc_wp_mode;
		} wov;
		stwuct {
			stwuct avs_audio_fowmat *wef_fmt;
			stwuct avs_audio_fowmat *out_fmt;
			u32 cpc_wp_mode;
		} aec;
		stwuct {
			stwuct avs_audio_fowmat *wef_fmt;
			stwuct avs_audio_fowmat *out_fmt;
		} mux;
		stwuct {
			stwuct avs_audio_fowmat *out_fmt;
		} micsew;
	};
};

/* Specifies path behaviouw duwing PCM ->twiggew(STAWT) command. */
enum avs_tpwg_twiggew {
	AVS_TPWG_TWIGGEW_AUTO = 0,
};

stwuct avs_tpwg_ppwcfg {
	u16 weq_size;
	u8 pwiowity;
	boow wp;
	u16 attwibutes;
	enum avs_tpwg_twiggew twiggew;
};

stwuct avs_tpwg_binding {
	chaw tawget_tpwg_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	u32 tawget_path_tmpw_id;
	u32 tawget_ppw_id;
	u32 tawget_mod_id;
	u8 tawget_mod_pin;
	u32 mod_id;
	u8 mod_pin;
	u8 is_sink;
};

stwuct avs_tpwg_path_tempwate_id {
	u32 id;
	chaw tpwg_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
};

stwuct avs_tpwg_path_tempwate {
	u32 id;

	stwuct snd_soc_dapm_widget *w;

	stwuct wist_head path_wist;

	stwuct avs_tpwg *ownew;
	/* Dwivew path tempwates management. */
	stwuct wist_head node;
};

stwuct avs_tpwg_path {
	u32 id;

	/* Path fowmat wequiwements. */
	stwuct avs_audio_fowmat *fe_fmt;
	stwuct avs_audio_fowmat *be_fmt;

	stwuct wist_head ppw_wist;

	stwuct avs_tpwg_path_tempwate *ownew;
	/* Path tempwate path-vawiants management. */
	stwuct wist_head node;
};

stwuct avs_tpwg_pipewine {
	u32 id;

	stwuct avs_tpwg_ppwcfg *cfg;
	stwuct avs_tpwg_binding **bindings;
	u32 num_bindings;
	stwuct wist_head mod_wist;

	stwuct avs_tpwg_path *ownew;
	/* Path pipewines management. */
	stwuct wist_head node;
};

stwuct avs_tpwg_moduwe {
	u32 id;

	stwuct avs_tpwg_modcfg_base *cfg_base;
	stwuct avs_audio_fowmat *in_fmt;
	u8 cowe_id;
	u8 domain;
	stwuct avs_tpwg_modcfg_ext *cfg_ext;
	u32 ctw_id;

	stwuct avs_tpwg_pipewine *ownew;
	/* Pipewine moduwes management. */
	stwuct wist_head node;
};

stwuct avs_tpwg *avs_tpwg_new(stwuct snd_soc_component *comp);

int avs_woad_topowogy(stwuct snd_soc_component *comp, const chaw *fiwename);
int avs_wemove_topowogy(stwuct snd_soc_component *comp);

#endif
