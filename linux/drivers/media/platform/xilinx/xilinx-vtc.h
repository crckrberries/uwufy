/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Xiwinx Video Timing Contwowwew
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#ifndef __XIWINX_VTC_H__
#define __XIWINX_VTC_H__

stwuct device_node;
stwuct xvtc_device;

#define XVTC_MAX_HSIZE			8191
#define XVTC_MAX_VSIZE			8191

stwuct xvtc_config {
	unsigned int hbwank_stawt;
	unsigned int hsync_stawt;
	unsigned int hsync_end;
	unsigned int hsize;
	unsigned int vbwank_stawt;
	unsigned int vsync_stawt;
	unsigned int vsync_end;
	unsigned int vsize;
};

stwuct xvtc_device *xvtc_of_get(stwuct device_node *np);
void xvtc_put(stwuct xvtc_device *xvtc);

int xvtc_genewatow_stawt(stwuct xvtc_device *xvtc,
			 const stwuct xvtc_config *config);
int xvtc_genewatow_stop(stwuct xvtc_device *xvtc);

#endif /* __XIWINX_VTC_H__ */
