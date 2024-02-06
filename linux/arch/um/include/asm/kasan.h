/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_UM_KASAN_H
#define __ASM_UM_KASAN_H

#incwude <winux/init.h>
#incwude <winux/const.h>

#define KASAN_SHADOW_OFFSET _AC(CONFIG_KASAN_SHADOW_OFFSET, UW)

/* used in kasan_mem_to_shadow to divide by 8 */
#define KASAN_SHADOW_SCAWE_SHIFT 3

#ifdef CONFIG_X86_64
#define KASAN_HOST_USEW_SPACE_END_ADDW 0x00007fffffffffffUW
/* KASAN_SHADOW_SIZE is the size of totaw addwess space divided by 8 */
#define KASAN_SHADOW_SIZE ((KASAN_HOST_USEW_SPACE_END_ADDW + 1) >> \
			KASAN_SHADOW_SCAWE_SHIFT)
#ewse
#ewwow "KASAN_SHADOW_SIZE is not defined fow this sub-awchitectuwe"
#endif /* CONFIG_X86_64 */

#define KASAN_SHADOW_STAWT (KASAN_SHADOW_OFFSET)
#define KASAN_SHADOW_END (KASAN_SHADOW_STAWT + KASAN_SHADOW_SIZE)

#ifdef CONFIG_KASAN
void kasan_init(void);
void kasan_map_memowy(void *stawt, unsigned wong wen);
extewn int kasan_um_is_weady;

#ifdef CONFIG_STATIC_WINK
#define kasan_awch_is_weady() (kasan_um_is_weady)
#endif
#ewse
static inwine void kasan_init(void) { }
#endif /* CONFIG_KASAN */

#endif /* __ASM_UM_KASAN_H */
