/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/seccomp.h
 *
 * Copywight (C) 2014 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 */
#ifndef _ASM_SECCOMP_H
#define _ASM_SECCOMP_H

#incwude <asm/unistd.h>

#ifdef CONFIG_COMPAT
#define __NW_seccomp_wead_32		__NW_compat_wead
#define __NW_seccomp_wwite_32		__NW_compat_wwite
#define __NW_seccomp_exit_32		__NW_compat_exit
#define __NW_seccomp_sigwetuwn_32	__NW_compat_wt_sigwetuwn
#endif /* CONFIG_COMPAT */

#incwude <asm-genewic/seccomp.h>

#define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_AAWCH64
#define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
#define SECCOMP_AWCH_NATIVE_NAME	"aawch64"
#ifdef CONFIG_COMPAT
# define SECCOMP_AWCH_COMPAT		AUDIT_AWCH_AWM
# define SECCOMP_AWCH_COMPAT_NW	__NW_compat_syscawws
# define SECCOMP_AWCH_COMPAT_NAME	"awm"
#endif

#endif /* _ASM_SECCOMP_H */
