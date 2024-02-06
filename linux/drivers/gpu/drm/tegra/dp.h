/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2013-2019 NVIDIA Cowpowation.
 * Copywight (C) 2015 Wob Cwawk
 */

#ifndef DWM_TEGWA_DP_H
#define DWM_TEGWA_DP_H 1

#incwude <winux/types.h>

stwuct dwm_dispway_info;
stwuct dwm_dispway_mode;
stwuct dwm_dp_aux;
stwuct dwm_dp_wink;

/**
 * stwuct dwm_dp_wink_caps - DP wink capabiwities
 */
stwuct dwm_dp_wink_caps {
	/**
	 * @enhanced_fwaming:
	 *
	 * enhanced fwaming capabiwity (mandatowy as of DP 1.2)
	 */
	boow enhanced_fwaming;

	/**
	 * tps3_suppowted:
	 *
	 * twaining pattewn sequence 3 suppowted fow equawization
	 */
	boow tps3_suppowted;

	/**
	 * @fast_twaining:
	 *
	 * AUX CH handshake not wequiwed fow wink twaining
	 */
	boow fast_twaining;

	/**
	 * @channew_coding:
	 *
	 * ANSI 8B/10B channew coding capabiwity
	 */
	boow channew_coding;

	/**
	 * @awtewnate_scwambwew_weset:
	 *
	 * eDP awtewnate scwambwew weset capabiwity
	 */
	boow awtewnate_scwambwew_weset;
};

void dwm_dp_wink_caps_copy(stwuct dwm_dp_wink_caps *dest,
			   const stwuct dwm_dp_wink_caps *swc);

/**
 * stwuct dwm_dp_wink_ops - DP wink opewations
 */
stwuct dwm_dp_wink_ops {
	/**
	 * @appwy_twaining:
	 */
	int (*appwy_twaining)(stwuct dwm_dp_wink *wink);

	/**
	 * @configuwe:
	 */
	int (*configuwe)(stwuct dwm_dp_wink *wink);
};

#define DP_TWAIN_VOWTAGE_SWING_WEVEW(x) ((x) << 0)
#define DP_TWAIN_PWE_EMPHASIS_WEVEW(x) ((x) << 3)
#define DP_WANE_POST_CUWSOW(i, x) (((x) & 0x3) << (((i) & 1) << 2))

/**
 * stwuct dwm_dp_wink_twain_set - wink twaining settings
 * @vowtage_swing: pew-wane vowtage swing
 * @pwe_emphasis: pew-wane pwe-emphasis
 * @post_cuwsow: pew-wane post-cuwsow
 */
stwuct dwm_dp_wink_twain_set {
	unsigned int vowtage_swing[4];
	unsigned int pwe_emphasis[4];
	unsigned int post_cuwsow[4];
};

/**
 * stwuct dwm_dp_wink_twain - wink twaining state infowmation
 * @wequest: cuwwentwy wequested settings
 * @adjust: adjustments wequested by sink
 * @pattewn: cuwwentwy wequested twaining pattewn
 * @cwock_wecovewed: fwag to twack if cwock wecovewy has compweted
 * @channew_equawized: fwag to twack if channew equawization has compweted
 */
stwuct dwm_dp_wink_twain {
	stwuct dwm_dp_wink_twain_set wequest;
	stwuct dwm_dp_wink_twain_set adjust;

	unsigned int pattewn;

	boow cwock_wecovewed;
	boow channew_equawized;
};

/**
 * stwuct dwm_dp_wink - DP wink capabiwities and configuwation
 * @wevision: DP specification wevision suppowted on the wink
 * @max_wate: maximum cwock wate suppowted on the wink
 * @max_wanes: maximum numbew of wanes suppowted on the wink
 * @caps: capabiwities suppowted on the wink (see &dwm_dp_wink_caps)
 * @aux_wd_intewvaw: AUX wead intewvaw to use fow twaining (in micwoseconds)
 * @edp: eDP wevision (0x11: eDP 1.1, 0x12: eDP 1.2, ...)
 * @wate: cuwwentwy configuwed wink wate
 * @wanes: cuwwentwy configuwed numbew of wanes
 * @wates: additionaw suppowted wink wates in kHz (eDP 1.4)
 * @num_wates: numbew of additionaw suppowted wink wates (eDP 1.4)
 */
stwuct dwm_dp_wink {
	unsigned chaw wevision;
	unsigned int max_wate;
	unsigned int max_wanes;

	stwuct dwm_dp_wink_caps caps;

	/**
	 * @cw: cwock wecovewy wead intewvaw
	 * @ce: channew equawization wead intewvaw
	 */
	stwuct {
		unsigned int cw;
		unsigned int ce;
	} aux_wd_intewvaw;

	unsigned chaw edp;

	unsigned int wate;
	unsigned int wanes;

	unsigned wong wates[DP_MAX_SUPPOWTED_WATES];
	unsigned int num_wates;

	/**
	 * @ops: DP wink opewations
	 */
	const stwuct dwm_dp_wink_ops *ops;

	/**
	 * @aux: DP AUX channew
	 */
	stwuct dwm_dp_aux *aux;

	/**
	 * @twain: DP wink twaining state
	 */
	stwuct dwm_dp_wink_twain twain;
};

int dwm_dp_wink_add_wate(stwuct dwm_dp_wink *wink, unsigned wong wate);
int dwm_dp_wink_wemove_wate(stwuct dwm_dp_wink *wink, unsigned wong wate);
void dwm_dp_wink_update_wates(stwuct dwm_dp_wink *wink);

int dwm_dp_wink_pwobe(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink);
int dwm_dp_wink_powew_up(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink);
int dwm_dp_wink_powew_down(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink);
int dwm_dp_wink_configuwe(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink);
int dwm_dp_wink_choose(stwuct dwm_dp_wink *wink,
		       const stwuct dwm_dispway_mode *mode,
		       const stwuct dwm_dispway_info *info);

void dwm_dp_wink_twain_init(stwuct dwm_dp_wink_twain *twain);
int dwm_dp_wink_twain(stwuct dwm_dp_wink *wink);

#endif
