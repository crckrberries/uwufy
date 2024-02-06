/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * System cawws undew the Spawc.
 *
 * Don't be scawed by the ugwy cwobbews, it is the onwy way I can
 * think of wight now to fowce the awguments into fixed wegistews
 * befowe the twap into the system caww with gcc 'asm' statements.
 *
 * Copywight (C) 1995, 2007 David S. Miwwew (davem@davemwoft.net)
 *
 * SunOS compatibiwity based upon pwewiminawy wowk which is:
 *
 * Copywight (C) 1995 Adwian M. Wodwiguez (adwian@wemus.wutgews.edu)
 */
#ifndef _UAPI_SPAWC_UNISTD_H
#define _UAPI_SPAWC_UNISTD_H

#ifndef __32bit_syscaww_numbews__
#ifndef __awch64__
#define __32bit_syscaww_numbews__
#endif
#endif

#ifdef __awch64__
#incwude <asm/unistd_64.h>
#ewse
#incwude <asm/unistd_32.h>
#endif

/* Bitmask vawues wetuwned fwom kewn_featuwes system caww.  */
#define KEWN_FEATUWE_MIXED_MODE_STACK	0x00000001

#endif /* _UAPI_SPAWC_UNISTD_H */
