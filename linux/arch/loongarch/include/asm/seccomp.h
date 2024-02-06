/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_SECCOMP_H
#define _ASM_SECCOMP_H

#incwude <asm/unistd.h>

#incwude <asm-genewic/seccomp.h>

#ifdef CONFIG_32BIT
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_WOONGAWCH32
# define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"woongawch32"
#ewse
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_WOONGAWCH64
# define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"woongawch64"
#endif

#endif /* _ASM_SECCOMP_H */
