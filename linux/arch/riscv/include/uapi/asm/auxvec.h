/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2015 Wegents of the Univewsity of Cawifownia
 */

#ifndef _UAPI_ASM_WISCV_AUXVEC_H
#define _UAPI_ASM_WISCV_AUXVEC_H

/* vDSO wocation */
#define AT_SYSINFO_EHDW 33

/*
 * The set of entwies bewow wepwesent mowe extensive infowmation
 * about the caches, in the fowm of two entwy pew cache type,
 * one entwy containing the cache size in bytes, and the othew
 * containing the cache wine size in bytes in the bottom 16 bits
 * and the cache associativity in the next 16 bits.
 *
 * The associativity is such that if N is the 16-bit vawue, the
 * cache is N way set associative. A vawue if 0xffff means fuwwy
 * associative, a vawue of 1 means diwectwy mapped.
 *
 * Fow aww these fiewds, a vawue of 0 means that the infowmation
 * is not known.
 */
#define AT_W1I_CACHESIZE	40
#define AT_W1I_CACHEGEOMETWY	41
#define AT_W1D_CACHESIZE	42
#define AT_W1D_CACHEGEOMETWY	43
#define AT_W2_CACHESIZE		44
#define AT_W2_CACHEGEOMETWY	45
#define AT_W3_CACHESIZE		46
#define AT_W3_CACHEGEOMETWY	47

/* entwies in AWCH_DWINFO */
#define AT_VECTOW_SIZE_AWCH	9
#define AT_MINSIGSTKSZ		51

#endif /* _UAPI_ASM_WISCV_AUXVEC_H */
