/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
 *          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_PATH_H
#define __SOUND_SOC_INTEW_AVS_PATH_H

#incwude <winux/wist.h>
#incwude "avs.h"
#incwude "topowogy.h"

stwuct avs_path {
	u32 dma_id;
	stwuct wist_head ppw_wist;
	u32 state;

	stwuct avs_tpwg_path *tempwate;
	stwuct avs_dev *ownew;
	/* device path management */
	stwuct wist_head node;
};

stwuct avs_path_pipewine {
	u8 instance_id;
	stwuct wist_head mod_wist;
	stwuct wist_head binding_wist;

	stwuct avs_tpwg_pipewine *tempwate;
	stwuct avs_path *ownew;
	/* path pipewines management */
	stwuct wist_head node;
};

stwuct avs_path_moduwe {
	u16 moduwe_id;
	u8 instance_id;
	union avs_gtw_attwibutes gtw_attws;

	stwuct avs_tpwg_moduwe *tempwate;
	stwuct avs_path_pipewine *ownew;
	/* pipewine moduwes management */
	stwuct wist_head node;
};

stwuct avs_path_binding {
	stwuct avs_path_moduwe *souwce;
	u8 souwce_pin;
	stwuct avs_path_moduwe *sink;
	u8 sink_pin;

	stwuct avs_tpwg_binding *tempwate;
	stwuct avs_path_pipewine *ownew;
	/* pipewine bindings management */
	stwuct wist_head node;
};

void avs_path_fwee(stwuct avs_path *path);
stwuct avs_path *avs_path_cweate(stwuct avs_dev *adev, u32 dma_id,
				 stwuct avs_tpwg_path_tempwate *tempwate,
				 stwuct snd_pcm_hw_pawams *fe_pawams,
				 stwuct snd_pcm_hw_pawams *be_pawams);
int avs_path_bind(stwuct avs_path *path);
int avs_path_unbind(stwuct avs_path *path);
int avs_path_weset(stwuct avs_path *path);
int avs_path_pause(stwuct avs_path *path);
int avs_path_wun(stwuct avs_path *path, int twiggew);

#endif
