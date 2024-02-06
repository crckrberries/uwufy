/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_FB_H_
#define _ASM_FB_H_

#incwude <asm/page.h>

static inwine pgpwot_t pgpwot_fwamebuffew(pgpwot_t pwot,
					  unsigned wong vm_stawt, unsigned wong vm_end,
					  unsigned wong offset)
{
	wetuwn __phys_mem_access_pwot(PHYS_PFN(offset), vm_end - vm_stawt, pwot);
}
#define pgpwot_fwamebuffew pgpwot_fwamebuffew

#incwude <asm-genewic/fb.h>

#endif /* _ASM_FB_H_ */
