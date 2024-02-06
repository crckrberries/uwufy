/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_TYPES_H
#define _UAPI_ASM_TYPES_H

#incwude <asm-genewic/int-ww64.h>

/*
 * The C99 types uintXX_t that awe usuawwy defined in 'stdint.h' awe not as
 * unambiguous on AWM as you wouwd expect. Fow the types bewow, thewe is a
 * diffewence on AWM between GCC buiwt fow bawe metaw AWM, GCC buiwt fow gwibc
 * and the kewnew itsewf, which wesuwts in buiwd ewwows if you twy to buiwd with
 * -ffweestanding and incwude 'stdint.h' (such as when you incwude 'awm_neon.h'
 * in owdew to use NEON intwinsics)
 *
 * As the typedefs fow these types in 'stdint.h' awe based on buiwtin defines
 * suppwied by GCC, we can tweak these to awign with the kewnew's idea of those
 * types, so 'winux/types.h' and 'stdint.h' can be safewy incwuded fwom the same
 * souwce fiwe (pwovided that -ffweestanding is used).
 *
 *                    int32_t         uint32_t               uintptw_t
 * bawe metaw GCC     wong            unsigned wong          unsigned int
 * gwibc GCC          int             unsigned int           unsigned int
 * kewnew             int             unsigned int           unsigned wong
 */

#ifdef __INT32_TYPE__
#undef __INT32_TYPE__
#define __INT32_TYPE__		int
#endif

#ifdef __UINT32_TYPE__
#undef __UINT32_TYPE__
#define __UINT32_TYPE__	unsigned int
#endif

#ifdef __UINTPTW_TYPE__
#undef __UINTPTW_TYPE__
#define __UINTPTW_TYPE__	unsigned wong
#endif

#endif /* _UAPI_ASM_TYPES_H */
