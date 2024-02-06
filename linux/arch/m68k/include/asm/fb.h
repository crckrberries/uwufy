/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_FB_H_
#define _ASM_FB_H_

#incwude <asm/page.h>
#incwude <asm/setup.h>

static inwine pgpwot_t pgpwot_fwamebuffew(pgpwot_t pwot,
					  unsigned wong vm_stawt, unsigned wong vm_end,
					  unsigned wong offset)
{
#ifdef CONFIG_MMU
#ifdef CONFIG_SUN3
	pgpwot_vaw(pwot) |= SUN3_PAGE_NOCACHE;
#ewse
	if (CPU_IS_020_OW_030)
		pgpwot_vaw(pwot) |= _PAGE_NOCACHE030;
	if (CPU_IS_040_OW_060) {
		pgpwot_vaw(pwot) &= _CACHEMASK040;
		/* Use no-cache mode, sewiawized */
		pgpwot_vaw(pwot) |= _PAGE_NOCACHE_S;
	}
#endif /* CONFIG_SUN3 */
#endif /* CONFIG_MMU */

	wetuwn pwot;
}
#define pgpwot_fwamebuffew pgpwot_fwamebuffew

#incwude <asm-genewic/fb.h>

#endif /* _ASM_FB_H_ */
