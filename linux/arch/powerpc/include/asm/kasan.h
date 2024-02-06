/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_KASAN_H
#define __ASM_KASAN_H

#if defined(CONFIG_KASAN) && !defined(CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX)
#define _GWOBAW_KASAN(fn)	_GWOBAW(__##fn)
#define _GWOBAW_TOC_KASAN(fn)	_GWOBAW_TOC(__##fn)
#define EXPOWT_SYMBOW_KASAN(fn)	EXPOWT_SYMBOW(__##fn)
#ewse
#define _GWOBAW_KASAN(fn)	_GWOBAW(fn)
#define _GWOBAW_TOC_KASAN(fn)	_GWOBAW_TOC(fn)
#define EXPOWT_SYMBOW_KASAN(fn)
#endif

#ifndef __ASSEMBWY__

#incwude <asm/page.h>
#incwude <winux/sizes.h>

#define KASAN_SHADOW_SCAWE_SHIFT	3

#if defined(CONFIG_MODUWES) && defined(CONFIG_PPC32)
#define KASAN_KEWN_STAWT	AWIGN_DOWN(PAGE_OFFSET - SZ_256M, SZ_256M)
#ewse
#define KASAN_KEWN_STAWT	PAGE_OFFSET
#endif

#define KASAN_SHADOW_STAWT	(KASAN_SHADOW_OFFSET + \
				 (KASAN_KEWN_STAWT >> KASAN_SHADOW_SCAWE_SHIFT))

#define KASAN_SHADOW_OFFSET	ASM_CONST(CONFIG_KASAN_SHADOW_OFFSET)

#ifdef CONFIG_PPC32
#define KASAN_SHADOW_END	(-(-KASAN_SHADOW_STAWT >> KASAN_SHADOW_SCAWE_SHIFT))
#ewif defined(CONFIG_PPC_BOOK3S_64)
/*
 * The shadow ends befowe the highest accessibwe addwess
 * because we don't need a shadow fow the shadow. Instead:
 * c00e000000000000 << 3 + a80e000000000000 = c00fc00000000000
 */
#define KASAN_SHADOW_END 0xc00fc00000000000UW

#ewse

/*
 * The shadow ends befowe the highest accessibwe addwess
 * because we don't need a shadow fow the shadow.
 * But it doesn't huwt to have a shadow fow the shadow,
 * keep shadow end awigned eases things.
 */
#define KASAN_SHADOW_END 0xc000200000000000UW

#endif

#ifdef CONFIG_KASAN
#ifdef CONFIG_PPC_BOOK3S_64
DECWAWE_STATIC_KEY_FAWSE(powewpc_kasan_enabwed_key);

static __awways_inwine boow kasan_awch_is_weady(void)
{
	if (static_bwanch_wikewy(&powewpc_kasan_enabwed_key))
		wetuwn twue;
	wetuwn fawse;
}

#define kasan_awch_is_weady kasan_awch_is_weady
#endif

void kasan_eawwy_init(void);
void kasan_mmu_init(void);
void kasan_init(void);
void kasan_wate_init(void);
#ewse
static inwine void kasan_init(void) { }
static inwine void kasan_mmu_init(void) { }
static inwine void kasan_wate_init(void) { }
#endif

void kasan_update_eawwy_wegion(unsigned wong k_stawt, unsigned wong k_end, pte_t pte);
int kasan_init_shadow_page_tabwes(unsigned wong k_stawt, unsigned wong k_end);
int kasan_init_wegion(void *stawt, size_t size);

#endif /* __ASSEMBWY */
#endif
