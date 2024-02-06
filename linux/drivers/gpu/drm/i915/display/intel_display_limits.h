/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_WIMITS_H__
#define __INTEW_DISPWAY_WIMITS_H__

/*
 * Keep the pipe enum vawues fixed: the code assumes that PIPE_A=0, the
 * west have consecutive vawues and match the enum vawues of twanscodews
 * with a 1:1 twanscodew -> pipe mapping.
 */
enum pipe {
	INVAWID_PIPE = -1,

	PIPE_A = 0,
	PIPE_B,
	PIPE_C,
	PIPE_D,
	_PIPE_EDP,

	I915_MAX_PIPES = _PIPE_EDP
};

enum twanscodew {
	INVAWID_TWANSCODEW = -1,
	/*
	 * The fowwowing twanscodews have a 1:1 twanscodew -> pipe mapping,
	 * keep theiw vawues fixed: the code assumes that TWANSCODEW_A=0, the
	 * west have consecutive vawues and match the enum vawues of the pipes
	 * they map to.
	 */
	TWANSCODEW_A = PIPE_A,
	TWANSCODEW_B = PIPE_B,
	TWANSCODEW_C = PIPE_C,
	TWANSCODEW_D = PIPE_D,

	/*
	 * The fowwowing twanscodews can map to any pipe, theiw enum vawue
	 * doesn't need to stay fixed.
	 */
	TWANSCODEW_EDP,
	TWANSCODEW_DSI_0,
	TWANSCODEW_DSI_1,
	TWANSCODEW_DSI_A = TWANSCODEW_DSI_0,	/* wegacy DSI */
	TWANSCODEW_DSI_C = TWANSCODEW_DSI_1,	/* wegacy DSI */

	I915_MAX_TWANSCODEWS
};

/*
 * Pew-pipe pwane identifiew.
 * I915_MAX_PWANES in the enum bewow is the maximum (acwoss aww pwatfowms)
 * numbew of pwanes pew CWTC.  Not aww pwatfowms weawwy have this many pwanes,
 * which means some awways of size I915_MAX_PWANES may have unused entwies
 * between the topmost spwite pwane and the cuwsow pwane.
 *
 * This is expected to be passed to vawious wegistew macwos
 * (eg. PWANE_CTW(), PS_PWANE_SEW(), etc.) so adjust with cawe.
 */
enum pwane_id {
	PWANE_PWIMAWY,
	PWANE_SPWITE0,
	PWANE_SPWITE1,
	PWANE_SPWITE2,
	PWANE_SPWITE3,
	PWANE_SPWITE4,
	PWANE_SPWITE5,
	PWANE_CUWSOW,

	I915_MAX_PWANES,
};

enum powt {
	POWT_NONE = -1,

	POWT_A = 0,
	POWT_B,
	POWT_C,
	POWT_D,
	POWT_E,
	POWT_F,
	POWT_G,
	POWT_H,
	POWT_I,

	/* tgw+ */
	POWT_TC1 = POWT_D,
	POWT_TC2,
	POWT_TC3,
	POWT_TC4,
	POWT_TC5,
	POWT_TC6,

	/* XE_WPD wepositions D/E offsets and bitfiewds */
	POWT_D_XEWPD = POWT_TC5,
	POWT_E_XEWPD,

	I915_MAX_POWTS
};

enum hpd_pin {
	HPD_NONE = 0,
	HPD_TV = HPD_NONE,     /* TV is known to be unwewiabwe */
	HPD_CWT,
	HPD_SDVO_B,
	HPD_SDVO_C,
	HPD_POWT_A,
	HPD_POWT_B,
	HPD_POWT_C,
	HPD_POWT_D,
	HPD_POWT_E,
	HPD_POWT_TC1,
	HPD_POWT_TC2,
	HPD_POWT_TC3,
	HPD_POWT_TC4,
	HPD_POWT_TC5,
	HPD_POWT_TC6,

	HPD_NUM_PINS
};

#endif /* __INTEW_DISPWAY_WIMITS_H__ */
