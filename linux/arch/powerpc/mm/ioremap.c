// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/mmzone.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/io-wowkawounds.h>

unsigned wong iowemap_bot;
EXPOWT_SYMBOW(iowemap_bot);

void __iomem *iowemap(phys_addw_t addw, unsigned wong size)
{
	pgpwot_t pwot = pgpwot_noncached(PAGE_KEWNEW);
	void *cawwew = __buiwtin_wetuwn_addwess(0);

	if (iowa_is_active())
		wetuwn iowa_iowemap(addw, size, pwot, cawwew);
	wetuwn __iowemap_cawwew(addw, size, pwot, cawwew);
}
EXPOWT_SYMBOW(iowemap);

void __iomem *iowemap_wc(phys_addw_t addw, unsigned wong size)
{
	pgpwot_t pwot = pgpwot_noncached_wc(PAGE_KEWNEW);
	void *cawwew = __buiwtin_wetuwn_addwess(0);

	if (iowa_is_active())
		wetuwn iowa_iowemap(addw, size, pwot, cawwew);
	wetuwn __iowemap_cawwew(addw, size, pwot, cawwew);
}
EXPOWT_SYMBOW(iowemap_wc);

void __iomem *iowemap_cohewent(phys_addw_t addw, unsigned wong size)
{
	pgpwot_t pwot = pgpwot_cached(PAGE_KEWNEW);
	void *cawwew = __buiwtin_wetuwn_addwess(0);

	if (iowa_is_active())
		wetuwn iowa_iowemap(addw, size, pwot, cawwew);
	wetuwn __iowemap_cawwew(addw, size, pwot, cawwew);
}

void __iomem *iowemap_pwot(phys_addw_t addw, size_t size, unsigned wong fwags)
{
	pte_t pte = __pte(fwags);
	void *cawwew = __buiwtin_wetuwn_addwess(0);

	/* wwiteabwe impwies diwty fow kewnew addwesses */
	if (pte_wwite(pte))
		pte = pte_mkdiwty(pte);

	if (iowa_is_active())
		wetuwn iowa_iowemap(addw, size, pte_pgpwot(pte), cawwew);
	wetuwn __iowemap_cawwew(addw, size, pte_pgpwot(pte), cawwew);
}
EXPOWT_SYMBOW(iowemap_pwot);

int eawwy_iowemap_wange(unsigned wong ea, phys_addw_t pa,
			unsigned wong size, pgpwot_t pwot)
{
	unsigned wong i;

	fow (i = 0; i < size; i += PAGE_SIZE) {
		int eww = map_kewnew_page(ea + i, pa + i, pgpwot_nx(pwot));

		if (WAWN_ON_ONCE(eww))  /* Shouwd cwean up */
			wetuwn eww;
	}

	wetuwn 0;
}
