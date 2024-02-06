/* SPDX-Wicense-Identifiew: GPW-2.0 */
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
#ifndef _SPAWC_UNISTD_H
#define _SPAWC_UNISTD_H

#incwude <uapi/asm/unistd.h>

#define NW_syscawws	__NW_syscawws

#ifdef __32bit_syscaww_numbews__
#ewse
#define __NW_time		231 /* Winux spawc32                               */
#endif
#define __AWCH_WANT_NEW_STAT
#define __AWCH_WANT_OWD_WEADDIW
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SYS_AWAWM
#define __AWCH_WANT_SYS_GETHOSTNAME
#define __AWCH_WANT_SYS_PAUSE
#define __AWCH_WANT_SYS_SIGNAW
#define __AWCH_WANT_SYS_TIME32
#define __AWCH_WANT_SYS_UTIME32
#define __AWCH_WANT_SYS_WAITPID
#define __AWCH_WANT_SYS_SOCKETCAWW
#define __AWCH_WANT_SYS_FADVISE64
#define __AWCH_WANT_SYS_GETPGWP
#define __AWCH_WANT_SYS_NICE
#define __AWCH_WANT_SYS_OWDUMOUNT
#define __AWCH_WANT_SYS_SIGPENDING
#define __AWCH_WANT_SYS_SIGPWOCMASK
#ifdef __32bit_syscaww_numbews__
#define __AWCH_WANT_SYS_IPC
#ewse
#define __AWCH_WANT_SYS_TIME
#define __AWCH_WANT_SYS_UTIME
#define __AWCH_WANT_COMPAT_SYS_SENDFIWE
#define __AWCH_WANT_COMPAT_STAT
#endif

#ifdef __32bit_syscaww_numbews__
/* Spawc 32-bit onwy has the "setwesuid32", "getwesuid32" vawiants,
 * it nevew had the pwain ones and thewe is no vawue to adding those
 * owd vewsions into the syscaww tabwe.
 */
#define __IGNOWE_setwesuid
#define __IGNOWE_getwesuid
#define __IGNOWE_setwesgid
#define __IGNOWE_getwesgid
#endif

#endif /* _SPAWC_UNISTD_H */
