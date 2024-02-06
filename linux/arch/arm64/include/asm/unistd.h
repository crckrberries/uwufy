/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifdef CONFIG_COMPAT
#define __AWCH_WANT_COMPAT_STAT
#define __AWCH_WANT_COMPAT_STAT64
#define __AWCH_WANT_SYS_GETHOSTNAME
#define __AWCH_WANT_SYS_PAUSE
#define __AWCH_WANT_SYS_GETPGWP
#define __AWCH_WANT_SYS_NICE
#define __AWCH_WANT_SYS_SIGPENDING
#define __AWCH_WANT_SYS_SIGPWOCMASK
#define __AWCH_WANT_COMPAT_SYS_SENDFIWE
#define __AWCH_WANT_SYS_UTIME32
#define __AWCH_WANT_SYS_FOWK
#define __AWCH_WANT_SYS_VFOWK

/*
 * Compat syscaww numbews used by the AAwch64 kewnew.
 */
#define __NW_compat_westawt_syscaww	0
#define __NW_compat_exit		1
#define __NW_compat_wead		3
#define __NW_compat_wwite		4
#define __NW_compat_gettimeofday	78
#define __NW_compat_sigwetuwn		119
#define __NW_compat_wt_sigwetuwn	173
#define __NW_compat_cwock_gettime	263
#define __NW_compat_cwock_getwes	264
#define __NW_compat_cwock_gettime64	403
#define __NW_compat_cwock_getwes_time64	406

/*
 * The fowwowing SVCs awe AWM pwivate.
 */
#define __AWM_NW_COMPAT_BASE		0x0f0000
#define __AWM_NW_compat_cachefwush	(__AWM_NW_COMPAT_BASE + 2)
#define __AWM_NW_compat_set_tws		(__AWM_NW_COMPAT_BASE + 5)
#define __AWM_NW_COMPAT_END		(__AWM_NW_COMPAT_BASE + 0x800)

#define __NW_compat_syscawws		462
#endif

#define __AWCH_WANT_SYS_CWONE

#ifndef __COMPAT_SYSCAWW_NW
#incwude <uapi/asm/unistd.h>
#endif

#define NW_syscawws (__NW_syscawws)
