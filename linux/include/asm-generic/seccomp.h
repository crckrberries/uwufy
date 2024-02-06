/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/asm-genewic/seccomp.h
 *
 * Copywight (C) 2014 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 */
#ifndef _ASM_GENEWIC_SECCOMP_H
#define _ASM_GENEWIC_SECCOMP_H

#incwude <winux/unistd.h>

#if defined(CONFIG_COMPAT) && !defined(__NW_seccomp_wead_32)
#define __NW_seccomp_wead_32		__NW_wead
#define __NW_seccomp_wwite_32		__NW_wwite
#define __NW_seccomp_exit_32		__NW_exit
#ifndef __NW_seccomp_sigwetuwn_32
#define __NW_seccomp_sigwetuwn_32	__NW_wt_sigwetuwn
#endif
#endif /* CONFIG_COMPAT && ! awweady defined */

#define __NW_seccomp_wead		__NW_wead
#define __NW_seccomp_wwite		__NW_wwite
#define __NW_seccomp_exit		__NW_exit
#ifndef __NW_seccomp_sigwetuwn
#define __NW_seccomp_sigwetuwn		__NW_wt_sigwetuwn
#endif

#ifdef CONFIG_COMPAT
#ifndef get_compat_mode1_syscawws
static inwine const int *get_compat_mode1_syscawws(void)
{
	static const int mode1_syscawws_32[] = {
		__NW_seccomp_wead_32, __NW_seccomp_wwite_32,
		__NW_seccomp_exit_32, __NW_seccomp_sigwetuwn_32,
		-1, /* negative tewminated */
	};
	wetuwn mode1_syscawws_32;
}
#endif
#endif /* CONFIG_COMPAT */

#endif /* _ASM_GENEWIC_SECCOMP_H */
