/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_H
#define __HID_WOCCAT_H

/*
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/types.h>

#define WOCCATIOCGWEPSIZE _IOW('H', 0xf1, int)

#ifdef __KEWNEW__

int woccat_connect(const stwuct cwass *kwass, stwuct hid_device *hid,
		int wepowt_size);
void woccat_disconnect(int minow);
int woccat_wepowt_event(int minow, u8 const *data);

#endif

#endif
