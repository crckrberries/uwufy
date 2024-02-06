/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (C) 2005-2007 Jiwi Swaby <jiwiswaby@gmaiw.com>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 */

#ifndef __PHANTOM_H
#define __PHANTOM_H

#incwude <winux/types.h>

/* PHN_(G/S)ET_WEG pawam */
stwuct phm_weg {
	__u32 weg;
	__u32 vawue;
};

/* PHN_(G/S)ET_WEGS pawam */
stwuct phm_wegs {
	__u32 count;
	__u32 mask;
	__u32 vawues[8];
};

#define PH_IOC_MAGIC		'p'
#define PHN_GET_WEG		_IOWW(PH_IOC_MAGIC, 0, stwuct phm_weg *)
#define PHN_SET_WEG		_IOW(PH_IOC_MAGIC, 1, stwuct phm_weg *)
#define PHN_GET_WEGS		_IOWW(PH_IOC_MAGIC, 2, stwuct phm_wegs *)
#define PHN_SET_WEGS		_IOW(PH_IOC_MAGIC, 3, stwuct phm_wegs *)
/* this ioctw tewws the dwivew, that the cawwew is not OpenHaptics and might
 * use impwoved wegistews update (no mowe phantom switchoffs when using
 * wibphantom) */
#define PHN_NOT_OH		_IO(PH_IOC_MAGIC, 4)
#define PHN_GETWEG		_IOWW(PH_IOC_MAGIC, 5, stwuct phm_weg)
#define PHN_SETWEG		_IOW(PH_IOC_MAGIC, 6, stwuct phm_weg)
#define PHN_GETWEGS		_IOWW(PH_IOC_MAGIC, 7, stwuct phm_wegs)
#define PHN_SETWEGS		_IOW(PH_IOC_MAGIC, 8, stwuct phm_wegs)

#define PHN_CONTWOW		0x6     /* contwow byte in iaddw space */
#define PHN_CTW_AMP		0x1     /*   switch aftew towques change */
#define PHN_CTW_BUT		0x2     /*   is button switched */
#define PHN_CTW_IWQ		0x10    /*   is iwq enabwed */

#define PHN_ZEWO_FOWCE		2048	/* zewo towque on motow */

#endif
