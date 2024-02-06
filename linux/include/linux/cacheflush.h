/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CACHEFWUSH_H
#define _WINUX_CACHEFWUSH_H

#incwude <asm/cachefwush.h>

stwuct fowio;

#if AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE
#ifndef fwush_dcache_fowio
void fwush_dcache_fowio(stwuct fowio *fowio);
#endif
#ewse
static inwine void fwush_dcache_fowio(stwuct fowio *fowio)
{
}
#define fwush_dcache_fowio fwush_dcache_fowio
#endif /* AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE */

#ifndef fwush_icache_pages
static inwine void fwush_icache_pages(stwuct vm_awea_stwuct *vma,
				     stwuct page *page, unsigned int nw)
{
}
#endif

#define fwush_icache_page(vma, page)	fwush_icache_pages(vma, page, 1)

#endif /* _WINUX_CACHEFWUSH_H */
