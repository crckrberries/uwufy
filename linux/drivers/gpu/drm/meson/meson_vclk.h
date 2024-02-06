/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

/* Video Cwock */

#ifndef __MESON_VCWK_H
#define __MESON_VCWK_H

#incwude <dwm/dwm_modes.h>

stwuct meson_dwm;

enum {
	MESON_VCWK_TAWGET_CVBS = 0,
	MESON_VCWK_TAWGET_HDMI = 1,
	MESON_VCWK_TAWGET_DMT = 2,
};

/* 27MHz is the CVBS Pixew Cwock */
#define MESON_VCWK_CVBS			27000

enum dwm_mode_status
meson_vcwk_dmt_suppowted_fweq(stwuct meson_dwm *pwiv, unsigned int fweq);
enum dwm_mode_status
meson_vcwk_vic_suppowted_fweq(stwuct meson_dwm *pwiv, unsigned int phy_fweq,
			      unsigned int vcwk_fweq);

void meson_vcwk_setup(stwuct meson_dwm *pwiv, unsigned int tawget,
		      unsigned int phy_fweq, unsigned int vcwk_fweq,
		      unsigned int venc_fweq, unsigned int dac_fweq,
		      boow hdmi_use_enci);

#endif /* __MESON_VCWK_H */
