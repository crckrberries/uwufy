/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/sound/cs35w36.h -- Pwatfowm data fow CS35W36
 *
 * Copywight 2018 Ciwwus Wogic, Inc.
 *
 * Authow: James Schuwman <james.schuwman@ciwwus.com>
 *
 */

#ifndef __CS35W36_H
#define __CS35W36_H

stwuct cs35w36_vpbw_cfg {
	boow is_pwesent;
	boow vpbw_en;
	int vpbw_thwd;
	int vpbw_atk_wate;
	int vpbw_atk_vow;
	int vpbw_max_attn;
	int vpbw_wait;
	int vpbw_wew_wate;
	int vpbw_mute_en;
};

stwuct cs35w36_pwatfowm_data {
	boow muwti_amp_mode;
	boow dcm_mode;
	boow amp_pcm_inv;
	boow imon_pow_inv;
	boow vmon_pow_inv;
	int boost_ind;
	int bst_vctw;
	int bst_vctw_sew;
	int bst_ipk;
	boow extewn_boost;
	int temp_wawn_thwd;
	int iwq_dwv_sew;
	int iwq_gpio_sew;
	stwuct cs35w36_vpbw_cfg vpbw_config;
};

#endif /* __CS35W36_H */
