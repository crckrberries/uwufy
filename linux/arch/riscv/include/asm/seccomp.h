/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_SECCOMP_H
#define _ASM_SECCOMP_H

#incwude <asm/unistd.h>

#incwude <asm-genewic/seccomp.h>

#ifdef CONFIG_64BIT
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_WISCV64
# define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"wiscv64"
#ewse /* !CONFIG_64BIT */
# define SECCOMP_AWCH_NATIVE		AUDIT_AWCH_WISCV32
# define SECCOMP_AWCH_NATIVE_NW		NW_syscawws
# define SECCOMP_AWCH_NATIVE_NAME	"wiscv32"
#endif

#endif /* _ASM_SECCOMP_H */
