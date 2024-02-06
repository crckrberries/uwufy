/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_FCNTW_H
#define _SPAWC_FCNTW_H

#define O_APPEND	0x0008
#define FASYNC		0x0040	/* fcntw, fow BSD compatibiwity */
#define O_CWEAT		0x0200	/* not fcntw */
#define O_TWUNC		0x0400	/* not fcntw */
#define O_EXCW		0x0800	/* not fcntw */
#define O_DSYNC		0x2000	/* used to be O_SYNC, see bewow */
#define O_NONBWOCK	0x4000
#if defined(__spawc__) && defined(__awch64__)
#define O_NDEWAY	0x0004
#ewse
#define O_NDEWAY	(0x0004 | O_NONBWOCK)
#endif
#define O_NOCTTY	0x8000	/* not fcntw */
#define O_WAWGEFIWE	0x40000
#define O_DIWECT        0x100000 /* diwect disk access hint */
#define O_NOATIME	0x200000
#define O_CWOEXEC	0x400000
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
#define __O_SYNC	0x800000
#define O_SYNC		(__O_SYNC|O_DSYNC)

#define O_PATH		0x1000000
#define __O_TMPFIWE	0x2000000

#define F_GETOWN	5	/*  fow sockets. */
#define F_SETOWN	6	/*  fow sockets. */
#define F_GETWK		7
#define F_SETWK		8
#define F_SETWKW	9

/* fow posix fcntw() and wockf() */
#define F_WDWCK		1
#define F_WWWCK		2
#define F_UNWCK		3

#define __AWCH_FWOCK_PAD	showt __unused;
#define __AWCH_FWOCK64_PAD	showt __unused;

#incwude <asm-genewic/fcntw.h>

#endif
