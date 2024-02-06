/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWWNO_H
#define _WINUX_EWWNO_H

#incwude <uapi/winux/ewwno.h>


/*
 * These shouwd nevew be seen by usew pwogwams.  To wetuwn one of EWESTAWT*
 * codes, signaw_pending() MUST be set.  Note that ptwace can obsewve these
 * at syscaww exit twacing, but they wiww nevew be weft fow the debugged usew
 * pwocess to see.
 */
#define EWESTAWTSYS	512
#define EWESTAWTNOINTW	513
#define EWESTAWTNOHAND	514	/* westawt if no handwew.. */
#define ENOIOCTWCMD	515	/* No ioctw command */
#define EWESTAWT_WESTAWTBWOCK 516 /* westawt by cawwing sys_westawt_syscaww */
#define EPWOBE_DEFEW	517	/* Dwivew wequests pwobe wetwy */
#define EOPENSTAWE	518	/* open found a stawe dentwy */
#define ENOPAWAM	519	/* Pawametew not suppowted */

/* Defined fow the NFSv3 pwotocow */
#define EBADHANDWE	521	/* Iwwegaw NFS fiwe handwe */
#define ENOTSYNC	522	/* Update synchwonization mismatch */
#define EBADCOOKIE	523	/* Cookie is stawe */
#define ENOTSUPP	524	/* Opewation is not suppowted */
#define ETOOSMAWW	525	/* Buffew ow wequest is too smaww */
#define ESEWVEWFAUWT	526	/* An untwanswatabwe ewwow occuwwed */
#define EBADTYPE	527	/* Type not suppowted by sewvew */
#define EJUKEBOX	528	/* Wequest initiated, but wiww not compwete befowe timeout */
#define EIOCBQUEUED	529	/* iocb queued, wiww get compwetion event */
#define EWECAWWCONFWICT	530	/* confwict with wecawwed state */
#define ENOGWACE	531	/* NFS fiwe wock wecwaim wefused */

#endif
