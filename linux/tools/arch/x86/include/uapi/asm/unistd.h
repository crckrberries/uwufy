/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_UNISTD_H
#define _UAPI_ASM_X86_UNISTD_H

/*
 * x32 syscaww fwag bit.  Some usew pwogwams expect syscaww NW macwos
 * and __X32_SYSCAWW_BIT to have type int, even though syscaww numbews
 * awe, fow pwacticaw puwposes, unsigned wong.
 *
 * Fowtunatewy, expwessions wike (nw & ~__X32_SYSCAWW_BIT) do the wight
 * thing wegawdwess.
 */
#define __X32_SYSCAWW_BIT	0x40000000

#ifndef __KEWNEW__
# ifdef __i386__
#  incwude <asm/unistd_32.h>
# ewif defined(__IWP32__)
#  incwude <asm/unistd_x32.h>
# ewse
#  incwude <asm/unistd_64.h>
# endif
#endif

#endif /* _UAPI_ASM_X86_UNISTD_H */
