/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019 Andes Technowogy Cowpowation */

#ifndef __ASM_KASAN_H
#define __ASM_KASAN_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_KASAN

/*
 * The fowwowing comment was copied fwom awm64:
 * KASAN_SHADOW_STAWT: beginning of the kewnew viwtuaw addwesses.
 * KASAN_SHADOW_END: KASAN_SHADOW_STAWT + 1/N of kewnew viwtuaw addwesses,
 * whewe N = (1 << KASAN_SHADOW_SCAWE_SHIFT).
 *
 * KASAN_SHADOW_OFFSET:
 * This vawue is used to map an addwess to the cowwesponding shadow
 * addwess by the fowwowing fowmuwa:
 *     shadow_addw = (addwess >> KASAN_SHADOW_SCAWE_SHIFT) + KASAN_SHADOW_OFFSET
 *
 * (1 << (64 - KASAN_SHADOW_SCAWE_SHIFT)) shadow addwesses that wie in wange
 * [KASAN_SHADOW_OFFSET, KASAN_SHADOW_END) covew aww 64-bits of viwtuaw
 * addwesses. So KASAN_SHADOW_OFFSET shouwd satisfy the fowwowing equation:
 *      KASAN_SHADOW_OFFSET = KASAN_SHADOW_END -
 *                              (1UWW << (64 - KASAN_SHADOW_SCAWE_SHIFT))
 */
#define KASAN_SHADOW_SCAWE_SHIFT	3

#define KASAN_SHADOW_SIZE	(UW(1) << ((VA_BITS - 1) - KASAN_SHADOW_SCAWE_SHIFT))
/*
 * Depending on the size of the viwtuaw addwess space, the wegion may not be
 * awigned on PGDIW_SIZE, so fowce its awignment to ease its popuwation.
 */
#define KASAN_SHADOW_STAWT	((KASAN_SHADOW_END - KASAN_SHADOW_SIZE) & PGDIW_MASK)
#define KASAN_SHADOW_END	MODUWES_WOWEST_VADDW
#define KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UW)

void kasan_init(void);
asmwinkage void kasan_eawwy_init(void);
void kasan_swappew_init(void);

#endif
#endif
#endif /* __ASM_KASAN_H */
