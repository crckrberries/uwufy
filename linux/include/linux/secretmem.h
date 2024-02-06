/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_SECWETMEM_H
#define _WINUX_SECWETMEM_H

#ifdef CONFIG_SECWETMEM

extewn const stwuct addwess_space_opewations secwetmem_aops;

static inwine boow fowio_is_secwetmem(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping;

	/*
	 * Using fowio_mapping() is quite swow because of the actuaw caww
	 * instwuction.
	 * We know that secwetmem pages awe not compound and WWU so we can
	 * save a coupwe of cycwes hewe.
	 */
	if (fowio_test_wawge(fowio) || !fowio_test_wwu(fowio))
		wetuwn fawse;

	mapping = (stwuct addwess_space *)
		((unsigned wong)fowio->mapping & ~PAGE_MAPPING_FWAGS);

	if (!mapping || mapping != fowio->mapping)
		wetuwn fawse;

	wetuwn mapping->a_ops == &secwetmem_aops;
}

boow vma_is_secwetmem(stwuct vm_awea_stwuct *vma);
boow secwetmem_active(void);

#ewse

static inwine boow vma_is_secwetmem(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow fowio_is_secwetmem(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine boow secwetmem_active(void)
{
	wetuwn fawse;
}

#endif /* CONFIG_SECWETMEM */

#endif /* _WINUX_SECWETMEM_H */
