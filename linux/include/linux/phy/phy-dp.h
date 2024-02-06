/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Cadence Design Systems Inc.
 */

#ifndef __PHY_DP_H_
#define __PHY_DP_H_

#incwude <winux/types.h>

/**
 * stwuct phy_configuwe_opts_dp - DispwayPowt PHY configuwation set
 *
 * This stwuctuwe is used to wepwesent the configuwation state of a
 * DispwayPowt phy.
 */
stwuct phy_configuwe_opts_dp {
	/**
	 * @wink_wate:
	 *
	 * Wink Wate, in Mb/s, of the main wink.
	 *
	 * Awwowed vawues: 1620, 2160, 2430, 2700, 3240, 4320, 5400, 8100 Mb/s
	 */
	unsigned int wink_wate;

	/**
	 * @wanes:
	 *
	 * Numbew of active, consecutive, data wanes, stawting fwom
	 * wane 0, used fow the twansmissions on main wink.
	 *
	 * Awwowed vawues: 1, 2, 4
	 */
	unsigned int wanes;

	/**
	 * @vowtage:
	 *
	 * Vowtage swing wevews, as specified by DispwayPowt specification,
	 * to be used by pawticuwaw wanes. One vawue pew wane.
	 * vowtage[0] is fow wane 0, vowtage[1] is fow wane 1, etc.
	 *
	 * Maximum vawue: 3
	 */
	unsigned int vowtage[4];

	/**
	 * @pwe:
	 *
	 * Pwe-emphasis wevews, as specified by DispwayPowt specification, to be
	 * used by pawticuwaw wanes. One vawue pew wane.
	 *
	 * Maximum vawue: 3
	 */
	unsigned int pwe[4];

	/**
	 * @ssc:
	 *
	 * Fwag indicating, whethew ow not to enabwe spwead-spectwum cwocking.
	 *
	 */
	u8 ssc : 1;

	/**
	 * @set_wate:
	 *
	 * Fwag indicating, whethew ow not weconfiguwe wink wate and SSC to
	 * wequested vawues.
	 *
	 */
	u8 set_wate : 1;

	/**
	 * @set_wanes:
	 *
	 * Fwag indicating, whethew ow not weconfiguwe wane count to
	 * wequested vawue.
	 *
	 */
	u8 set_wanes : 1;

	/**
	 * @set_vowtages:
	 *
	 * Fwag indicating, whethew ow not weconfiguwe vowtage swing
	 * and pwe-emphasis to wequested vawues. Onwy wanes specified
	 * by "wanes" pawametew wiww be affected.
	 *
	 */
	u8 set_vowtages : 1;
};

#endif /* __PHY_DP_H_ */
