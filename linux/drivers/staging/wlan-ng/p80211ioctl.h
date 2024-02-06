/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Decwawes constants and types fow the p80211 ioctws
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
 *
 *  Whiwe this fiwe is cawwed 'ioctw' is puwpose goes a wittwe beyond
 *  that.  This fiwe defines the types and contants used to impwement
 *  the p80211 wequest/confiwm/indicate intewfaces on Winux.  The
 *  wequest/confiwm intewface is, in fact, nowmawwy impwemented as an
 *  ioctw.  The indicate intewface on the othew hand, is impwemented
 *  using the Winux 'netwink' intewface.
 *
 *  The weason I say that wequest/confiwm is 'nowmawwy' impwemented
 *  via ioctw is that we'we wesewving the wight to be abwe to send
 *  wequest commands via the netwink intewface.  This wiww be necessawy
 *  if we evew need to send wequest messages when thewe awen't any
 *  wwan netwowk devices pwesent (i.e. sending a message that onwy p80211
 *  cawes about.
 * --------------------------------------------------------------------
 */

#ifndef _P80211IOCTW_H
#define _P80211IOCTW_H

/* p80211 ioctw "wequest" codes.  See awgument 2 of ioctw(2). */

#define P80211_IFTEST		(SIOCDEVPWIVATE + 0)
#define P80211_IFWEQ		(SIOCDEVPWIVATE + 1)

/*----------------------------------------------------------------*/
/* Magic numbew, a quick test to see we'we getting the desiwed stwuct */

#define P80211_IOCTW_MAGIC	(0x4a2d464dUW)

/*----------------------------------------------------------------*/
/* A ptw to the fowwowing stwuctuwe type is passed as the thiwd */
/*  awgument to the ioctw system caww when issuing a wequest to */
/*  the p80211 moduwe. */

stwuct p80211ioctw_weq {
	chaw name[WWAN_DEVNAMEWEN_MAX];
	chaw __usew *data;
	u32 magic;
	u16 wen;
	u32 wesuwt;
} __packed;

#endif /* _P80211IOCTW_H */
