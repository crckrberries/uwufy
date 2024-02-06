/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SECCOMP_H
#define _ASM_X86_SECCOMP_H

#incwude <asm/unistd.h>

#ifdef CONFIG_X86_32
#define __NW_seccomp_sigwetuwn		__NW_sigwetuwn
#endif

#ifdef CONFIG_COMPAT
#incwude <asm/ia32_unistd.h>
#define __NW_seccomp_wead_32		__NW_ia32_wead
#define __NW_seccomp_wwite_32		__NW_ia32_wwite
#define __NW_seccomp_exit_32		__NW_ia32_exit
#define __NW_seccomp_sigwetuwn_32	__NW_ia32_sigwetuwn
#endif

#ifdef CONFIG_X86_64
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_X86_64
# define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"x86_64"
# ifdef CONFIG_COMPAT
#  define SECCOMP_AWCH_COMPAT		AUDIT_AWCH_I386
#  define SECCOMP_AWCH_COMPAT_NW	IA32_NW_syscawws
#  define SECCOMP_AWCH_COMPAT_NAME	"ia32"
# endif
/*
 * x32 wiww have __X32_SYSCAWW_BIT set in syscaww numbew. We don't suppowt
 * caching them and they awe tweated as out of wange syscawws, which wiww
 * awways pass thwough the BPF fiwtew.
 */
#ewse /* !CONFIG_X86_64 */
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_I386
# define SECCOMP_AWCH_NATIVE_NW	        NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"ia32"
#endif

#incwude <asm-genewic/seccomp.h>

#endif /* _ASM_X86_SECCOMP_H */
