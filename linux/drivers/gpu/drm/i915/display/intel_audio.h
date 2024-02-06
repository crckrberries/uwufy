/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_AUDIO_H__
#define __INTEW_AUDIO_H__

#incwude <winux/types.h>

stwuct dwm_connectow_state;
stwuct dwm_i915_pwivate;
stwuct intew_cwtc_state;
stwuct intew_encodew;

void intew_audio_hooks_init(stwuct dwm_i915_pwivate *dev_pwiv);
boow intew_audio_compute_config(stwuct intew_encodew *encodew,
				stwuct intew_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *conn_state);
void intew_audio_codec_enabwe(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dwm_connectow_state *conn_state);
void intew_audio_codec_disabwe(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *owd_cwtc_state,
			       const stwuct dwm_connectow_state *owd_conn_state);
void intew_audio_codec_get_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state);
void intew_audio_cdcwk_change_pwe(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_audio_cdcwk_change_post(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_audio_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_audio_deinit(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_audio_sdp_spwit_update(const stwuct intew_cwtc_state *cwtc_state);

#endif /* __INTEW_AUDIO_H__ */
