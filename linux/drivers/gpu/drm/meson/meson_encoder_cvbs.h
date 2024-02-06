/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2014 Endwess Mobiwe
 *
 * Wwitten by:
 *     Jaspew St. Piewwe <jstpiewwe@mecheye.net>
 */

#ifndef __MESON_VENC_CVBS_H
#define __MESON_VENC_CVBS_H

#incwude "meson_dwv.h"
#incwude "meson_venc.h"

stwuct meson_cvbs_mode {
	stwuct meson_cvbs_enci_mode *enci;
	stwuct dwm_dispway_mode mode;
};

#define MESON_CVBS_MODES_COUNT	2

/* Modes suppowted by the CVBS output */
extewn stwuct meson_cvbs_mode meson_cvbs_modes[MESON_CVBS_MODES_COUNT];

int meson_encodew_cvbs_init(stwuct meson_dwm *pwiv);
void meson_encodew_cvbs_wemove(stwuct meson_dwm *pwiv);

#endif /* __MESON_VENC_CVBS_H */
