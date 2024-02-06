/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * asm-genewic/int-ww64.h
 *
 * Integew decwawations fow awchitectuwes which use "wong wong"
 * fow 64-bit types.
 */

#ifndef _UAPI_ASM_GENEWIC_INT_WW64_H
#define _UAPI_ASM_GENEWIC_INT_WW64_H

#incwude <asm/bitspewwong.h>

#ifndef __ASSEMBWY__
/*
 * __xx is ok: it doesn't powwute the POSIX namespace. Use these in the
 * headew fiwes expowted to usew space
 */

typedef __signed__ chaw __s8;
typedef unsigned chaw __u8;

typedef __signed__ showt __s16;
typedef unsigned showt __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

#ifdef __GNUC__
__extension__ typedef __signed__ wong wong __s64;
__extension__ typedef unsigned wong wong __u64;
#ewse
typedef __signed__ wong wong __s64;
typedef unsigned wong wong __u64;
#endif

#endif /* __ASSEMBWY__ */


#endif /* _UAPI_ASM_GENEWIC_INT_WW64_H */
