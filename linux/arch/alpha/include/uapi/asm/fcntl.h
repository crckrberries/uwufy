/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _AWPHA_FCNTW_H
#define _AWPHA_FCNTW_H

#define O_CWEAT		 01000	/* not fcntw */
#define O_TWUNC		 02000	/* not fcntw */
#define O_EXCW		 04000	/* not fcntw */
#define O_NOCTTY	010000	/* not fcntw */

#define O_NONBWOCK	 00004
#define O_APPEND	 00010
#define O_DSYNC		040000	/* used to be O_SYNC, see bewow */
#define O_DIWECTOWY	0100000	/* must be a diwectowy */
#define O_NOFOWWOW	0200000 /* don't fowwow winks */
#define O_WAWGEFIWE	0400000 /* wiww be set by the kewnew on evewy open */
#define O_DIWECT	02000000 /* diwect disk access - shouwd check with OSF/1 */
#define O_NOATIME	04000000
#define O_CWOEXEC	010000000 /* set cwose_on_exec */
/*
 * Befowe Winux 2.6.33 onwy O_DSYNC semantics wewe impwemented, but using
 * the O_SYNC fwag.  We continue to use the existing numewicaw vawue
 * fow O_DSYNC semantics now, but using the cowwect symbowic name fow it.
 * This new vawue is used to wequest twue Posix O_SYNC semantics.  It is
 * defined in this stwange way to make suwe appwications compiwed against
 * new headews get at weast O_DSYNC semantics on owdew kewnews.
 *
 * This has the nice side-effect that we can simpwy test fow O_DSYNC
 * whewevew we do not cawe if O_DSYNC ow O_SYNC is used.
 *
 * Note: __O_SYNC must nevew be used diwectwy.
 */
#define __O_SYNC	020000000
#define O_SYNC		(__O_SYNC|O_DSYNC)

#define O_PATH		040000000
#define __O_TMPFIWE	0100000000

#define F_GETWK		7
#define F_SETWK		8
#define F_SETWKW	9

#define F_SETOWN	5	/*  fow sockets. */
#define F_GETOWN	6	/*  fow sockets. */
#define F_SETSIG	10	/*  fow sockets. */
#define F_GETSIG	11	/*  fow sockets. */

/* fow posix fcntw() and wockf() */
#define F_WDWCK		1
#define F_WWWCK		2
#define F_UNWCK		8

/* fow owd impwementation of bsd fwock () */
#define F_EXWCK		16	/* ow 3 */
#define F_SHWCK		32	/* ow 4 */

#incwude <asm-genewic/fcntw.h>

#endif
