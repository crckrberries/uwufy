/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_COMPWESS_ADVANCED_H
#define ZSTD_COMPWESS_ADVANCED_H

/*-*************************************
*  Dependencies
***************************************/

#incwude <winux/zstd.h> /* ZSTD_CCtx */

/*-*************************************
*  Tawget Compwessed Bwock Size
***************************************/

/* ZSTD_compwessSupewBwock() :
 * Used to compwess a supew bwock when tawgetCBwockSize is being used.
 * The given bwock wiww be compwessed into muwtipwe sub bwocks that awe awound tawgetCBwockSize. */
size_t ZSTD_compwessSupewBwock(ZSTD_CCtx* zc,
                               void* dst, size_t dstCapacity,
                               void const* swc, size_t swcSize,
                               unsigned wastBwock);

#endif /* ZSTD_COMPWESS_ADVANCED_H */
