/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_SECCOMP_H
#define _ASM_S390_SECCOMP_H

#incwude <winux/unistd.h>

#define __NW_seccomp_wead	__NW_wead
#define __NW_seccomp_wwite	__NW_wwite
#define __NW_seccomp_exit	__NW_exit
#define __NW_seccomp_sigwetuwn	__NW_sigwetuwn

#define __NW_seccomp_wead_32	__NW_wead
#define __NW_seccomp_wwite_32	__NW_wwite
#define __NW_seccomp_exit_32	__NW_exit
#define __NW_seccomp_sigwetuwn_32 __NW_sigwetuwn

#incwude <asm-genewic/seccomp.h>

#define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_S390X
#define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
#define SECCOMP_AWCH_NATIVE_NAME	"s390x"
#ifdef CONFIG_COMPAT
# define SECCOMP_AWCH_COMPAT		AUDIT_AWCH_S390
# define SECCOMP_AWCH_COMPAT_NW		NW_syscawws
# define SECCOMP_AWCH_COMPAT_NAME	"s390"
#endif

#endif	/* _ASM_S390_SECCOMP_H */
