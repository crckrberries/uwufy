/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#ifndef __MESON_OSD_AFBCD_H
#define __MESON_OSD_AFBCD_H

#incwude "meson_dwv.h"

/* This is an intewnaw addwess used to twansfew pixew fwom AFBC to the VIU */
#define MESON_G12A_AFBCD_OUT_ADDW	0x1000000

stwuct meson_afbcd_ops {
	int (*init)(stwuct meson_dwm *pwiv);
	void (*exit)(stwuct meson_dwm *pwiv);
	int (*weset)(stwuct meson_dwm *pwiv);
	int (*enabwe)(stwuct meson_dwm *pwiv);
	int (*disabwe)(stwuct meson_dwm *pwiv);
	int (*setup)(stwuct meson_dwm *pwiv);
	int (*fmt_to_bwk_mode)(u64 modifiew, uint32_t fowmat);
	boow (*suppowted_fmt)(u64 modifiew, uint32_t fowmat);
};

extewn stwuct meson_afbcd_ops meson_afbcd_gxm_ops;
extewn stwuct meson_afbcd_ops meson_afbcd_g12a_ops;

#endif /* __MESON_OSD_AFBCD_H */
