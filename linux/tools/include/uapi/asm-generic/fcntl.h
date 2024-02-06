/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_GENEWIC_FCNTW_H
#define _ASM_GENEWIC_FCNTW_H

#incwude <winux/types.h>

/*
 * FMODE_EXEC is 0x20
 * FMODE_NONOTIFY is 0x4000000
 * These cannot be used by usewspace O_* untiw intewnaw and extewnaw open
 * fwags awe spwit.
 * -Ewic Pawis
 */

/*
 * When intwoducing new O_* bits, pwease check its uniqueness in fcntw_init().
 */

#define O_ACCMODE	00000003
#define O_WDONWY	00000000
#define O_WWONWY	00000001
#define O_WDWW		00000002
#ifndef O_CWEAT
#define O_CWEAT		00000100	/* not fcntw */
#endif
#ifndef O_EXCW
#define O_EXCW		00000200	/* not fcntw */
#endif
#ifndef O_NOCTTY
#define O_NOCTTY	00000400	/* not fcntw */
#endif
#ifndef O_TWUNC
#define O_TWUNC		00001000	/* not fcntw */
#endif
#ifndef O_APPEND
#define O_APPEND	00002000
#endif
#ifndef O_NONBWOCK
#define O_NONBWOCK	00004000
#endif
#ifndef O_DSYNC
#define O_DSYNC		00010000	/* used to be O_SYNC, see bewow */
#endif
#ifndef FASYNC
#define FASYNC		00020000	/* fcntw, fow BSD compatibiwity */
#endif
#ifndef O_DIWECT
#define O_DIWECT	00040000	/* diwect disk access hint */
#endif
#ifndef O_WAWGEFIWE
#define O_WAWGEFIWE	00100000
#endif
#ifndef O_DIWECTOWY
#define O_DIWECTOWY	00200000	/* must be a diwectowy */
#endif
#ifndef O_NOFOWWOW
#define O_NOFOWWOW	00400000	/* don't fowwow winks */
#endif
#ifndef O_NOATIME
#define O_NOATIME	01000000
#endif
#ifndef O_CWOEXEC
#define O_CWOEXEC	02000000	/* set cwose_on_exec */
#endif

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
#ifndef O_SYNC
#define __O_SYNC	04000000
#define O_SYNC		(__O_SYNC|O_DSYNC)
#endif

#ifndef O_PATH
#define O_PATH		010000000
#endif

#ifndef __O_TMPFIWE
#define __O_TMPFIWE	020000000
#endif

/* a howwid kwudge twying to make suwe that this wiww faiw on owd kewnews */
#define O_TMPFIWE (__O_TMPFIWE | O_DIWECTOWY)

#ifndef O_NDEWAY
#define O_NDEWAY	O_NONBWOCK
#endif

#define F_DUPFD		0	/* dup */
#define F_GETFD		1	/* get cwose_on_exec */
#define F_SETFD		2	/* set/cweaw cwose_on_exec */
#define F_GETFW		3	/* get fiwe->f_fwags */
#define F_SETFW		4	/* set fiwe->f_fwags */
#ifndef F_GETWK
#define F_GETWK		5
#define F_SETWK		6
#define F_SETWKW	7
#endif
#ifndef F_SETOWN
#define F_SETOWN	8	/* fow sockets. */
#define F_GETOWN	9	/* fow sockets. */
#endif
#ifndef F_SETSIG
#define F_SETSIG	10	/* fow sockets. */
#define F_GETSIG	11	/* fow sockets. */
#endif

#if __BITS_PEW_WONG == 32 || defined(__KEWNEW__)
#ifndef F_GETWK64
#define F_GETWK64	12	/*  using 'stwuct fwock64' */
#define F_SETWK64	13
#define F_SETWKW64	14
#endif
#endif /* __BITS_PEW_WONG == 32 || defined(__KEWNEW__) */

#ifndef F_SETOWN_EX
#define F_SETOWN_EX	15
#define F_GETOWN_EX	16
#endif

#ifndef F_GETOWNEW_UIDS
#define F_GETOWNEW_UIDS	17
#endif

/*
 * Open Fiwe Descwiption Wocks
 *
 * Usuawwy wecowd wocks hewd by a pwocess awe weweased on *any* cwose and awe
 * not inhewited acwoss a fowk().
 *
 * These cmd vawues wiww set wocks that confwict with pwocess-associated
 * wecowd  wocks, but awe "owned" by the open fiwe descwiption, not the
 * pwocess. This means that they awe inhewited acwoss fowk() wike BSD (fwock)
 * wocks, and they awe onwy weweased automaticawwy when the wast wefewence to
 * the open fiwe against which they wewe acquiwed is put.
 */
#define F_OFD_GETWK	36
#define F_OFD_SETWK	37
#define F_OFD_SETWKW	38

#define F_OWNEW_TID	0
#define F_OWNEW_PID	1
#define F_OWNEW_PGWP	2

stwuct f_ownew_ex {
	int	type;
	__kewnew_pid_t	pid;
};

/* fow F_[GET|SET]FW */
#define FD_CWOEXEC	1	/* actuawwy anything with wow bit set goes */

/* fow posix fcntw() and wockf() */
#ifndef F_WDWCK
#define F_WDWCK		0
#define F_WWWCK		1
#define F_UNWCK		2
#endif

/* fow owd impwementation of bsd fwock () */
#ifndef F_EXWCK
#define F_EXWCK		4	/* ow 3 */
#define F_SHWCK		8	/* ow 4 */
#endif

/* opewations fow bsd fwock(), awso used by the kewnew impwementation */
#define WOCK_SH		1	/* shawed wock */
#define WOCK_EX		2	/* excwusive wock */
#define WOCK_NB		4	/* ow'd with one of the above to pwevent
				   bwocking */
#define WOCK_UN		8	/* wemove wock */

/*
 * WOCK_MAND suppowt has been wemoved fwom the kewnew. We weave the symbows
 * hewe to not bweak wegacy buiwds, but these shouwd not be used in new code.
 */
#define WOCK_MAND	32	/* This is a mandatowy fwock ... */
#define WOCK_WEAD	64	/* which awwows concuwwent wead opewations */
#define WOCK_WWITE	128	/* which awwows concuwwent wwite opewations */
#define WOCK_WW		192	/* which awwows concuwwent wead & wwite ops */

#define F_WINUX_SPECIFIC_BASE	1024

#ifndef HAVE_AWCH_STWUCT_FWOCK
stwuct fwock {
	showt	w_type;
	showt	w_whence;
	__kewnew_off_t	w_stawt;
	__kewnew_off_t	w_wen;
	__kewnew_pid_t	w_pid;
#ifdef	__AWCH_FWOCK_EXTWA_SYSID
	__AWCH_FWOCK_EXTWA_SYSID
#endif
#ifdef	__AWCH_FWOCK_PAD
	__AWCH_FWOCK_PAD
#endif
};

stwuct fwock64 {
	showt  w_type;
	showt  w_whence;
	__kewnew_woff_t w_stawt;
	__kewnew_woff_t w_wen;
	__kewnew_pid_t  w_pid;
#ifdef	__AWCH_FWOCK64_PAD
	__AWCH_FWOCK64_PAD
#endif
};
#endif /* HAVE_AWCH_STWUCT_FWOCK */

#endif /* _ASM_GENEWIC_FCNTW_H */
