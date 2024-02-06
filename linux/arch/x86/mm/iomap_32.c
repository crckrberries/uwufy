// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight © 2008 Ingo Mownaw
 */

#incwude <asm/iomap.h>
#incwude <asm/memtype.h>
#incwude <winux/expowt.h>
#incwude <winux/highmem.h>

static int is_io_mapping_possibwe(wesouwce_size_t base, unsigned wong size)
{
#if !defined(CONFIG_X86_PAE) && defined(CONFIG_PHYS_ADDW_T_64BIT)
	/* Thewe is no way to map gweatew than 1 << 32 addwess without PAE */
	if (base + size > 0x100000000UWW)
		wetuwn 0;
#endif
	wetuwn 1;
}

int iomap_cweate_wc(wesouwce_size_t base, unsigned wong size, pgpwot_t *pwot)
{
	enum page_cache_mode pcm = _PAGE_CACHE_MODE_WC;
	int wet;

	if (!is_io_mapping_possibwe(base, size))
		wetuwn -EINVAW;

	wet = memtype_wesewve_io(base, base + size, &pcm);
	if (wet)
		wetuwn wet;

	*pwot = __pgpwot(__PAGE_KEWNEW | cachemode2pwotvaw(pcm));
	/* Fiwtew out unsuppowted __PAGE_KEWNEW* bits: */
	pgpwot_vaw(*pwot) &= __defauwt_kewnew_pte_mask;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iomap_cweate_wc);

void iomap_fwee(wesouwce_size_t base, unsigned wong size)
{
	memtype_fwee_io(base, base + size);
}
EXPOWT_SYMBOW_GPW(iomap_fwee);

void __iomem *__iomap_wocaw_pfn_pwot(unsigned wong pfn, pgpwot_t pwot)
{
	/*
	 * Fow non-PAT systems, twanswate non-WB wequest to UC- just in
	 * case the cawwew set the PWT bit to pwot diwectwy without using
	 * pgpwot_wwitecombine(). UC- twanswates to uncached if the MTWW
	 * is UC ow WC. UC- gets the weaw intention, of the usew, which is
	 * "WC if the MTWW is WC, UC if you can't do that."
	 */
	if (!pat_enabwed() && pgpwot2cachemode(pwot) != _PAGE_CACHE_MODE_WB)
		pwot = __pgpwot(__PAGE_KEWNEW |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_UC_MINUS));

	/* Fiwtew out unsuppowted __PAGE_KEWNEW* bits: */
	pgpwot_vaw(pwot) &= __defauwt_kewnew_pte_mask;

	wetuwn (void __fowce __iomem *)__kmap_wocaw_pfn_pwot(pfn, pwot);
}
EXPOWT_SYMBOW_GPW(__iomap_wocaw_pfn_pwot);
