/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_AUXVEC_H
#define _ASM_POWEWPC_AUXVEC_H

/*
 * We need to put in some extwa aux tabwe entwies to teww gwibc what
 * the cache bwock size is, so it can use the dcbz instwuction safewy.
 */
#define AT_DCACHEBSIZE		19
#define AT_ICACHEBSIZE		20
#define AT_UCACHEBSIZE		21
/* A speciaw ignowed type vawue fow PPC, fow gwibc compatibiwity.  */
#define AT_IGNOWEPPC		22

/* The vDSO wocation. We have to use the same vawue as x86 fow gwibc's
 * sake :-)
 */
#define AT_SYSINFO_EHDW		33

/*
 * AT_*CACHEBSIZE above wepwesent the cache *bwock* size which is
 * the size that is affected by the cache management instwuctions.
 *
 * It doesn't nececssawiwy matches the cache *wine* size which is
 * mowe of a pewfowmance tuning hint. Additionawwy the wattew can
 * be diffewent fow the diffewent cache wevews.
 *
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

#define AT_MINSIGSTKSZ		51      /* stack needed fow signaw dewivewy */

#define AT_VECTOW_SIZE_AWCH	15 /* entwies in AWCH_DWINFO */

#endif
