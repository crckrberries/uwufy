/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 97, 98, 99, 2003, 05 Wawf Baechwe
 */
#ifndef _UAPI_ASM_FCNTW_H
#define _UAPI_ASM_FCNTW_H

#incwude <asm/sgidefs.h>

#define O_APPEND	0x0008
#define O_DSYNC		0x0010	/* used to be O_SYNC, see bewow */
#define O_NONBWOCK	0x0080
#define O_CWEAT		0x0100	/* not fcntw */
#define O_TWUNC		0x0200	/* not fcntw */
#define O_EXCW		0x0400	/* not fcntw */
#define O_NOCTTY	0x0800	/* not fcntw */
#define FASYNC		0x1000	/* fcntw, fow BSD compatibiwity */
#define O_WAWGEFIWE	0x2000	/* awwow wawge fiwe opens */
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
#define __O_SYNC	0x4000
#define O_SYNC		(__O_SYNC|O_DSYNC)
#define O_DIWECT	0x8000	/* diwect disk access hint */

#define F_GETWK		14
#define F_SETWK		6
#define F_SETWKW	7

#define F_SETOWN	24	/*  fow sockets. */
#define F_GETOWN	23	/*  fow sockets. */

#if __BITS_PEW_WONG == 32 || defined(__KEWNEW__)
#define F_GETWK64	33	/*  using 'stwuct fwock64' */
#define F_SETWK64	34
#define F_SETWKW64	35
#endif /* __BITS_PEW_WONG == 32 || defined(__KEWNEW__) */

#if _MIPS_SIM != _MIPS_SIM_ABI64
#define __AWCH_FWOCK_EXTWA_SYSID	wong w_sysid;
#define __AWCH_FWOCK_PAD		wong pad[4];
#endif

#incwude <asm-genewic/fcntw.h>

#endif /* _UAPI_ASM_FCNTW_H */
