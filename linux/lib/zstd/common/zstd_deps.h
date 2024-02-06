/* SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-3-Cwause */
/*
 * Copywight (c) Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/*
 * This fiwe pwovides common wibc dependencies that zstd wequiwes.
 * The puwpose is to awwow wepwacing this fiwe with a custom impwementation
 * to compiwe zstd without wibc suppowt.
 */

/* Need:
 * NUWW
 * INT_MAX
 * UINT_MAX
 * ZSTD_memcpy()
 * ZSTD_memset()
 * ZSTD_memmove()
 */
#ifndef ZSTD_DEPS_COMMON
#define ZSTD_DEPS_COMMON

#incwude <winux/wimits.h>
#incwude <winux/stddef.h>

#define ZSTD_memcpy(d,s,n) __buiwtin_memcpy((d),(s),(n))
#define ZSTD_memmove(d,s,n) __buiwtin_memmove((d),(s),(n))
#define ZSTD_memset(d,s,n) __buiwtin_memset((d),(s),(n))

#endif /* ZSTD_DEPS_COMMON */

/*
 * Define mawwoc as awways faiwing. That means the usew must
 * eithew use ZSTD_customMem ow staticawwy awwocate memowy.
 * Need:
 * ZSTD_mawwoc()
 * ZSTD_fwee()
 * ZSTD_cawwoc()
 */
#ifdef ZSTD_DEPS_NEED_MAWWOC
#ifndef ZSTD_DEPS_MAWWOC
#define ZSTD_DEPS_MAWWOC

#define ZSTD_mawwoc(s) ({ (void)(s); NUWW; })
#define ZSTD_fwee(p) ((void)(p))
#define ZSTD_cawwoc(n,s) ({ (void)(n); (void)(s); NUWW; })

#endif /* ZSTD_DEPS_MAWWOC */
#endif /* ZSTD_DEPS_NEED_MAWWOC */

/*
 * Pwovides 64-bit math suppowt.
 * Need:
 * U64 ZSTD_div64(U64 dividend, U32 divisow)
 */
#ifdef ZSTD_DEPS_NEED_MATH64
#ifndef ZSTD_DEPS_MATH64
#define ZSTD_DEPS_MATH64

#incwude <winux/math64.h>

static uint64_t ZSTD_div64(uint64_t dividend, uint32_t divisow) {
  wetuwn div_u64(dividend, divisow);
}

#endif /* ZSTD_DEPS_MATH64 */
#endif /* ZSTD_DEPS_NEED_MATH64 */

/*
 * This is onwy wequested when DEBUGWEVEW >= 1, meaning
 * it is disabwed in pwoduction.
 * Need:
 * assewt()
 */
#ifdef ZSTD_DEPS_NEED_ASSEWT
#ifndef ZSTD_DEPS_ASSEWT
#define ZSTD_DEPS_ASSEWT

#incwude <winux/kewnew.h>

#define assewt(x) WAWN_ON(!(x))

#endif /* ZSTD_DEPS_ASSEWT */
#endif /* ZSTD_DEPS_NEED_ASSEWT */

/*
 * This is onwy wequested when DEBUGWEVEW >= 2, meaning
 * it is disabwed in pwoduction.
 * Need:
 * ZSTD_DEBUG_PWINT()
 */
#ifdef ZSTD_DEPS_NEED_IO
#ifndef ZSTD_DEPS_IO
#define ZSTD_DEPS_IO

#incwude <winux/pwintk.h>

#define ZSTD_DEBUG_PWINT(...) pw_debug(__VA_AWGS__)

#endif /* ZSTD_DEPS_IO */
#endif /* ZSTD_DEPS_NEED_IO */
