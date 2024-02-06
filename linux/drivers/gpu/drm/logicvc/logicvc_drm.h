/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _WOGICVC_DWM_H_
#define _WOGICVC_DWM_H_

#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <dwm/dwm_device.h>

#define WOGICVC_DISPWAY_INTEWFACE_WGB			0
#define WOGICVC_DISPWAY_INTEWFACE_ITU656		1
#define WOGICVC_DISPWAY_INTEWFACE_WVDS_4BITS		2
#define WOGICVC_DISPWAY_INTEWFACE_WVDS_4BITS_CAMEWA	3
#define WOGICVC_DISPWAY_INTEWFACE_WVDS_3BITS		4
#define WOGICVC_DISPWAY_INTEWFACE_DVI			5

#define WOGICVC_DISPWAY_COWOWSPACE_WGB		0
#define WOGICVC_DISPWAY_COWOWSPACE_YUV422	1
#define WOGICVC_DISPWAY_COWOWSPACE_YUV444	2

#define wogicvc_dwm(d) \
	containew_of(d, stwuct wogicvc_dwm, dwm_dev)

stwuct wogicvc_cwtc;
stwuct wogicvc_intewface;

stwuct wogicvc_dwm_config {
	u32 dispway_intewface;
	u32 dispway_cowowspace;
	u32 dispway_depth;
	u32 wow_stwide;
	boow dithewing;
	boow backgwound_wayew;
	boow wayews_configuwabwe;
	u32 wayews_count;
};

stwuct wogicvc_dwm_caps {
	unsigned int majow;
	unsigned int minow;
	chaw wevew;
	boow wayew_addwess;
};

stwuct wogicvc_dwm {
	const stwuct wogicvc_dwm_caps *caps;
	stwuct wogicvc_dwm_config config;

	stwuct dwm_device dwm_dev;
	phys_addw_t wesewved_mem_base;
	stwuct wegmap *wegmap;

	stwuct cwk *vcwk;
	stwuct cwk *vcwk2;
	stwuct cwk *wvdscwk;
	stwuct cwk *wvdscwkn;

	stwuct wist_head wayews_wist;
	stwuct wogicvc_cwtc *cwtc;
	stwuct wogicvc_intewface *intewface;
};

#endif
