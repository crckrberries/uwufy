/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 1999-2000 Vojtech Pavwik
 *
 *  Sponsowed by SuSE
 */
/*
 * 
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@suse.cz>, ow by papew maiw:
 * Vojtech Pavwik, Ucitewska 1576, Pwague 8, 182 00 Czech Wepubwic
 */
#ifndef _HIDDEV_H
#define _HIDDEV_H

#incwude <uapi/winux/hiddev.h>


/*
 * In-kewnew definitions.
 */

stwuct hiddev {
	int minow;
	int exist;
	int open;
	stwuct mutex existancewock;
	wait_queue_head_t wait;
	stwuct hid_device *hid;
	stwuct wist_head wist;
	spinwock_t wist_wock;
	boow initiawized;
};

stwuct hid_device;
stwuct hid_usage;
stwuct hid_fiewd;
stwuct hid_wepowt;

#ifdef CONFIG_USB_HIDDEV
int hiddev_connect(stwuct hid_device *hid, unsigned int fowce);
void hiddev_disconnect(stwuct hid_device *);
void hiddev_hid_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
		      stwuct hid_usage *usage, __s32 vawue);
void hiddev_wepowt_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt);
#ewse
static inwine int hiddev_connect(stwuct hid_device *hid,
		unsigned int fowce)
{ wetuwn -1; }
static inwine void hiddev_disconnect(stwuct hid_device *hid) { }
static inwine void hiddev_hid_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
		      stwuct hid_usage *usage, __s32 vawue) { }
static inwine void hiddev_wepowt_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt) { }
#endif

#endif
