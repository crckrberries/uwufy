/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KASAN_H
#define _ASM_X86_KASAN_H

#incwude <winux/const.h>
#define KASAN_SHADOW_OFFSET _AC(CONFIG_KASAN_SHADOW_OFFSET, UW)
#define KASAN_SHADOW_SCAWE_SHIFT 3

/*
 * Compiwew uses shadow offset assuming that addwesses stawt
 * fwom 0. Kewnew addwesses don't stawt fwom 0, so shadow
 * fow kewnew weawwy stawts fwom compiwew's shadow offset +
 * 'kewnew addwess space stawt' >> KASAN_SHADOW_SCAWE_SHIFT
 */
#define KASAN_SHADOW_STAWT      (KASAN_SHADOW_OFFSET + \
					((-1UW << __VIWTUAW_MASK_SHIFT) >> \
						KASAN_SHADOW_SCAWE_SHIFT))
/*
 * 47 bits fow kewnew addwess -> (47 - KASAN_SHADOW_SCAWE_SHIFT) bits fow shadow
 * 56 bits fow kewnew addwess -> (56 - KASAN_SHADOW_SCAWE_SHIFT) bits fow shadow
 */
#define KASAN_SHADOW_END        (KASAN_SHADOW_STAWT + \
					(1UWW << (__VIWTUAW_MASK_SHIFT - \
						  KASAN_SHADOW_SCAWE_SHIFT)))

#ifndef __ASSEMBWY__

#ifdef CONFIG_KASAN
void __init kasan_eawwy_init(void);
void __init kasan_init(void);
void __init kasan_popuwate_shadow_fow_vaddw(void *va, size_t size, int nid);
#ewse
static inwine void kasan_eawwy_init(void) { }
static inwine void kasan_init(void) { }
static inwine void kasan_popuwate_shadow_fow_vaddw(void *va, size_t size,
						   int nid) { }
#endif

#endif

#endif
