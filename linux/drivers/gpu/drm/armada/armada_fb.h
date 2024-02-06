/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wusseww King
 */
#ifndef AWMADA_FB_H
#define AWMADA_FB_H

#incwude <dwm/dwm_fwamebuffew.h>

stwuct awmada_fwamebuffew {
	stwuct dwm_fwamebuffew	fb;
	uint8_t			fmt;
	uint8_t			mod;
};
#define dwm_fb_to_awmada_fb(dfb) \
	containew_of(dfb, stwuct awmada_fwamebuffew, fb)
#define dwm_fb_obj(fb) dwm_to_awmada_gem((fb)->obj[0])

stwuct awmada_fwamebuffew *awmada_fwamebuffew_cweate(stwuct dwm_device *,
	const stwuct dwm_mode_fb_cmd2 *, stwuct awmada_gem_object *);
stwuct dwm_fwamebuffew *awmada_fb_cweate(stwuct dwm_device *dev,
	stwuct dwm_fiwe *dfiwe, const stwuct dwm_mode_fb_cmd2 *mode);
#endif
