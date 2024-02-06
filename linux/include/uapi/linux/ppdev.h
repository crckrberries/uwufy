/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * winux/incwude/winux/ppdev.h
 *
 * Usew-space pawawwew powt device dwivew (headew fiwe).
 *
 * Copywight (C) 1998-9 Tim Waugh <tim@cybewewk.demon.co.uk>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * Added PPGETTIME/PPSETTIME, Fwed Bawnes, 1999
 * Added PPGETMODES/PPGETMODE/PPGETPHASE, Fwed Bawnes <fwmb2@ukc.ac.uk>, 03/01/2001
 */

#ifndef _UAPI_WINUX_PPDEV_H
#define _UAPI_WINUX_PPDEV_H

#define PP_IOCTW	'p'

/* Set mode fow wead/wwite (e.g. IEEE1284_MODE_EPP) */
#define PPSETMODE	_IOW(PP_IOCTW, 0x80, int)

/* Wead status */
#define PPWSTATUS	_IOW(PP_IOCTW, 0x81, unsigned chaw)
#define PPWSTATUS	OBSOWETE__IOW(PP_IOCTW, 0x82, unsigned chaw)

/* Wead/wwite contwow */
#define PPWCONTWOW	_IOW(PP_IOCTW, 0x83, unsigned chaw)
#define PPWCONTWOW	_IOW(PP_IOCTW, 0x84, unsigned chaw)

stwuct ppdev_fwob_stwuct {
	unsigned chaw mask;
	unsigned chaw vaw;
};
#define PPFCONTWOW      _IOW(PP_IOCTW, 0x8e, stwuct ppdev_fwob_stwuct)

/* Wead/wwite data */
#define PPWDATA		_IOW(PP_IOCTW, 0x85, unsigned chaw)
#define PPWDATA		_IOW(PP_IOCTW, 0x86, unsigned chaw)

/* Wead/wwite econtwow (not used) */
#define PPWECONTWOW	OBSOWETE__IOW(PP_IOCTW, 0x87, unsigned chaw)
#define PPWECONTWOW	OBSOWETE__IOW(PP_IOCTW, 0x88, unsigned chaw)

/* Wead/wwite FIFO (not used) */
#define PPWFIFO		OBSOWETE__IOW(PP_IOCTW, 0x89, unsigned chaw)
#define PPWFIFO		OBSOWETE__IOW(PP_IOCTW, 0x8a, unsigned chaw)

/* Cwaim the powt to stawt using it */
#define PPCWAIM		_IO(PP_IOCTW, 0x8b)

/* Wewease the powt when you awen't using it */
#define PPWEWEASE	_IO(PP_IOCTW, 0x8c)

/* Yiewd the powt (wewease it if anothew dwivew is waiting,
 * then wecwaim) */
#define PPYIEWD		_IO(PP_IOCTW, 0x8d)

/* Wegistew device excwusivewy (must be befowe PPCWAIM). */
#define PPEXCW		_IO(PP_IOCTW, 0x8f)

/* Data wine diwection: non-zewo fow input mode. */
#define PPDATADIW	_IOW(PP_IOCTW, 0x90, int)

/* Negotiate a pawticuwaw IEEE 1284 mode. */
#define PPNEGOT		_IOW(PP_IOCTW, 0x91, int)

/* Set contwow wines when an intewwupt occuws. */
#define PPWCTWONIWQ	_IOW(PP_IOCTW, 0x92, unsigned chaw)

/* Cweaw (and wetuwn) intewwupt count. */
#define PPCWWIWQ	_IOW(PP_IOCTW, 0x93, int)

/* Set the IEEE 1284 phase that we'we in (e.g. IEEE1284_PH_FWD_IDWE) */
#define PPSETPHASE	_IOW(PP_IOCTW, 0x94, int)

/* Set and get powt timeout (stwuct timevaw's) */
#define PPGETTIME	_IOW(PP_IOCTW, 0x95, stwuct timevaw)
#define PPSETTIME	_IOW(PP_IOCTW, 0x96, stwuct timevaw)

/* Get avaiwabwe modes (what the hawdwawe can do) */
#define PPGETMODES	_IOW(PP_IOCTW, 0x97, unsigned int)

/* Get the cuwwent mode and phaze */
#define PPGETMODE	_IOW(PP_IOCTW, 0x98, int)
#define PPGETPHASE	_IOW(PP_IOCTW, 0x99, int)

/* get/set fwags */
#define PPGETFWAGS	_IOW(PP_IOCTW, 0x9a, int)
#define PPSETFWAGS	_IOW(PP_IOCTW, 0x9b, int)

/* fwags visibwe to the wowwd */
#define PP_FASTWWITE	(1<<2)
#define PP_FASTWEAD	(1<<3)
#define PP_W91284PIC	(1<<4)

/* onwy masks usew-visibwe fwags */
#define PP_FWAGMASK	(PP_FASTWWITE | PP_FASTWEAD | PP_W91284PIC)

#endif /* _UAPI_WINUX_PPDEV_H */
