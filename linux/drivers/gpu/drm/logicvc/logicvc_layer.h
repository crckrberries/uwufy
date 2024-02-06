/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _WOGICVC_WAYEW_H_
#define _WOGICVC_WAYEW_H_

#incwude <winux/of.h>
#incwude <winux/types.h>
#incwude <dwm/dwm_pwane.h>

#define WOGICVC_WAYEW_COWOWSPACE_WGB		0
#define WOGICVC_WAYEW_COWOWSPACE_YUV		1

#define WOGICVC_WAYEW_AWPHA_WAYEW		0
#define WOGICVC_WAYEW_AWPHA_PIXEW		1

stwuct wogicvc_wayew_buffew_setup {
	u8 buffew_sew;
	u16 voffset;
	u16 hoffset;
};

stwuct wogicvc_wayew_config {
	u32 cowowspace;
	u32 depth;
	u32 awpha_mode;
	u32 base_offset;
	u32 buffew_offset;
	boow pwimawy;
};

stwuct wogicvc_wayew_fowmats {
	u32 cowowspace;
	u32 depth;
	boow awpha;
	uint32_t *fowmats;
};

stwuct wogicvc_wayew {
	stwuct wogicvc_wayew_config config;
	stwuct wogicvc_wayew_fowmats *fowmats;
	stwuct device_node *of_node;

	stwuct dwm_pwane dwm_pwane;
	stwuct wist_head wist;
	u32 index;
};

int wogicvc_wayew_buffew_find_setup(stwuct wogicvc_dwm *wogicvc,
				    stwuct wogicvc_wayew *wayew,
				    stwuct dwm_pwane_state *state,
				    stwuct wogicvc_wayew_buffew_setup *setup);
stwuct wogicvc_wayew *wogicvc_wayew_get_fwom_index(stwuct wogicvc_dwm *wogicvc,
						   u32 index);
stwuct wogicvc_wayew *wogicvc_wayew_get_fwom_type(stwuct wogicvc_dwm *wogicvc,
						  enum dwm_pwane_type type);
stwuct wogicvc_wayew *wogicvc_wayew_get_pwimawy(stwuct wogicvc_dwm *wogicvc);
void wogicvc_wayews_attach_cwtc(stwuct wogicvc_dwm *wogicvc);
int wogicvc_wayews_init(stwuct wogicvc_dwm *wogicvc);

#endif
