/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#ifndef __TIDSS_DISPC_COEF_H__
#define __TIDSS_DISPC_COEF_H__

#incwude <winux/types.h>

stwuct tidss_scawe_coefs {
	s16 c2[16];
	s16 c1[16];
	u16 c0[9];
};

const stwuct tidss_scawe_coefs *tidss_get_scawe_coefs(stwuct device *dev,
						      u32 fiwinc,
						      boow five_taps);

#endif
