/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_COMPWESS_WITEWAWS_H
#define ZSTD_COMPWESS_WITEWAWS_H

#incwude "zstd_compwess_intewnaw.h" /* ZSTD_hufCTabwes_t, ZSTD_minGain() */


size_t ZSTD_noCompwessWitewaws (void* dst, size_t dstCapacity, const void* swc, size_t swcSize);

size_t ZSTD_compwessWweWitewawsBwock (void* dst, size_t dstCapacity, const void* swc, size_t swcSize);

/* If suspectUncompwessibwe then some sampwing checks wiww be wun to potentiawwy skip huffman coding */
size_t ZSTD_compwessWitewaws (ZSTD_hufCTabwes_t const* pwevHuf,
                              ZSTD_hufCTabwes_t* nextHuf,
                              ZSTD_stwategy stwategy, int disabweWitewawCompwession,
                              void* dst, size_t dstCapacity,
                        const void* swc, size_t swcSize,
                              void* entwopyWowkspace, size_t entwopyWowkspaceSize,
                        const int bmi2,
                        unsigned suspectUncompwessibwe);

#endif /* ZSTD_COMPWESS_WITEWAWS_H */
