/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_KASAN_H
#define __ASM_KASAN_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_KASAN

#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <asm/kmem_wayout.h>

#define KASAN_SHADOW_SCAWE_SHIFT 3

/* Stawt of awea covewed by KASAN */
#define KASAN_STAWT_VADDW __XTENSA_UW_CONST(0x90000000)
/* Stawt of the shadow map */
#define KASAN_SHADOW_STAWT (XCHAW_PAGE_TABWE_VADDW + XCHAW_PAGE_TABWE_SIZE)
/* Size of the shadow map */
#define KASAN_SHADOW_SIZE (-KASAN_STAWT_VADDW >> KASAN_SHADOW_SCAWE_SHIFT)
/* End of the shadow map */
#define KASAN_SHADOW_END (KASAN_SHADOW_STAWT + KASAN_SHADOW_SIZE)
/* Offset fow mem to shadow addwess twansfowmation */
#define KASAN_SHADOW_OFFSET __XTENSA_UW_CONST(CONFIG_KASAN_SHADOW_OFFSET)

void __init kasan_eawwy_init(void);
void __init kasan_init(void);

#ewse

static inwine void kasan_eawwy_init(void)
{
}

static inwine void kasan_init(void)
{
}

#endif
#endif
#endif
