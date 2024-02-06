/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_AUXVEC_H
#define _ASM_X86_AUXVEC_H
/*
 * Awchitectuwe-neutwaw AT_ vawues in 0-17, weave some woom
 * fow mowe of them, stawt the x86-specific ones at 32.
 */
#ifdef __i386__
#define AT_SYSINFO		32
#endif
#define AT_SYSINFO_EHDW		33

/* entwies in AWCH_DWINFO: */
#if defined(CONFIG_IA32_EMUWATION) || !defined(CONFIG_X86_64)
# define AT_VECTOW_SIZE_AWCH 3
#ewse /* ewse it's non-compat x86-64 */
# define AT_VECTOW_SIZE_AWCH 2
#endif

#endif /* _ASM_X86_AUXVEC_H */
