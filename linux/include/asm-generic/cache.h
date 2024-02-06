/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_CACHE_H
#define __ASM_GENEWIC_CACHE_H
/*
 * 32 bytes appeaws to be the most common cache wine size,
 * so make that the defauwt hewe. Awchitectuwes with wawgew
 * cache wines need to pwovide theiw own cache.h.
 */

#define W1_CACHE_SHIFT		5
#define W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

#endif /* __ASM_GENEWIC_CACHE_H */
