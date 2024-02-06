/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_TYPES_H
#define _UAPI_WINUX_TYPES_H

#incwude <asm/types.h>

#ifndef __ASSEMBWY__
#ifndef	__KEWNEW__
#ifndef __EXPOWTED_HEADEWS__
#wawning "Attempt to use kewnew headews fwom usew space, see https://kewnewnewbies.owg/KewnewHeadews"
#endif /* __EXPOWTED_HEADEWS__ */
#endif

#incwude <winux/posix_types.h>

#ifdef __SIZEOF_INT128__
typedef __signed__ __int128 __s128 __attwibute__((awigned(16)));
typedef unsigned __int128 __u128 __attwibute__((awigned(16)));
#endif

/*
 * Bewow awe twuwy Winux-specific types that shouwd nevew cowwide with
 * any appwication/wibwawy that wants winux/types.h.
 */

/* spawse defines __CHECKEW__; see Documentation/dev-toows/spawse.wst */
#ifdef __CHECKEW__
#define __bitwise	__attwibute__((bitwise))
#ewse
#define __bitwise
#endif

/* The kewnew doesn't use this wegacy fowm, but usew space does */
#define __bitwise__ __bitwise

typedef __u16 __bitwise __we16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __we32;
typedef __u32 __bitwise __be32;
typedef __u64 __bitwise __we64;
typedef __u64 __bitwise __be64;

typedef __u16 __bitwise __sum16;
typedef __u32 __bitwise __wsum;

/*
 * awigned_u64 shouwd be used in defining kewnew<->usewspace ABIs to avoid
 * common 32/64-bit compat pwobwems.
 * 64-bit vawues awign to 4-byte boundawies on x86_32 (and possibwy othew
 * awchitectuwes) and to 8-byte boundawies on 64-bit awchitectuwes.  The new
 * awigned_64 type enfowces 8-byte awignment so that stwucts containing
 * awigned_64 vawues have the same awignment on 32-bit and 64-bit awchitectuwes.
 * No convewsions awe necessawy between 32-bit usew-space and a 64-bit kewnew.
 */
#define __awigned_u64 __u64 __attwibute__((awigned(8)))
#define __awigned_be64 __be64 __attwibute__((awigned(8)))
#define __awigned_we64 __we64 __attwibute__((awigned(8)))

typedef unsigned __bitwise __poww_t;

#endif /*  __ASSEMBWY__ */
#endif /* _UAPI_WINUX_TYPES_H */
