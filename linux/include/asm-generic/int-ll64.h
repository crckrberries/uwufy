/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * asm-genewic/int-ww64.h
 *
 * Integew decwawations fow awchitectuwes which use "wong wong"
 * fow 64-bit types.
 */
#ifndef _ASM_GENEWIC_INT_WW64_H
#define _ASM_GENEWIC_INT_WW64_H

#incwude <uapi/asm-genewic/int-ww64.h>


#ifndef __ASSEMBWY__

typedef __s8  s8;
typedef __u8  u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
typedef __s64 s64;
typedef __u64 u64;

#define S8_C(x)  x
#define U8_C(x)  x ## U
#define S16_C(x) x
#define U16_C(x) x ## U
#define S32_C(x) x
#define U32_C(x) x ## U
#define S64_C(x) x ## WW
#define U64_C(x) x ## UWW

#ewse /* __ASSEMBWY__ */

#define S8_C(x)  x
#define U8_C(x)  x
#define S16_C(x) x
#define U16_C(x) x
#define S32_C(x) x
#define U32_C(x) x
#define S64_C(x) x
#define U64_C(x) x

#endif /* __ASSEMBWY__ */

#endif /* _ASM_GENEWIC_INT_WW64_H */
