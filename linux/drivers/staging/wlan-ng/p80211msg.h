/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Macwos, constants, types, and funcs fow weq and ind messages
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 */

#ifndef _P80211MSG_H
#define _P80211MSG_H

#define WWAN_DEVNAMEWEN_MAX	16

stwuct p80211msg {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
} __packed;

#endif /* _P80211MSG_H */
