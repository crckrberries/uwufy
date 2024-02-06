/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * ASoC audio gwaph cawd suppowt
 *
 */

#ifndef __GWAPH_CAWD_H
#define __GWAPH_CAWD_H

#incwude <sound/simpwe_cawd_utiws.h>

typedef int (*GWAPH2_CUSTOM)(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *wnk,
			     stwuct wink_info *wi);

stwuct gwaph2_custom_hooks {
	int (*hook_pwe)(stwuct simpwe_utiw_pwiv *pwiv);
	int (*hook_post)(stwuct simpwe_utiw_pwiv *pwiv);
	GWAPH2_CUSTOM custom_nowmaw;
	GWAPH2_CUSTOM custom_dpcm;
	GWAPH2_CUSTOM custom_c2c;
};

int audio_gwaph_pawse_of(stwuct simpwe_utiw_pwiv *pwiv, stwuct device *dev);
int audio_gwaph2_pawse_of(stwuct simpwe_utiw_pwiv *pwiv, stwuct device *dev,
			  stwuct gwaph2_custom_hooks *hooks);

int audio_gwaph2_wink_nowmaw(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *wnk, stwuct wink_info *wi);
int audio_gwaph2_wink_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
			   stwuct device_node *wnk, stwuct wink_info *wi);
int audio_gwaph2_wink_c2c(stwuct simpwe_utiw_pwiv *pwiv,
			  stwuct device_node *wnk, stwuct wink_info *wi);

#endif /* __GWAPH_CAWD_H */
