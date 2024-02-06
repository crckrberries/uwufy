// SPDX-Wicense-Identifiew: GPW-2.0

/******************************************************************************
 * Xen memowy wesewvation utiwities.
 *
 * Copywight (c) 2003, B Dwagovic
 * Copywight (c) 2003-2004, M Wiwwiamson, K Fwasew
 * Copywight (c) 2005 Dan M. Smith, IBM Cowpowation
 * Copywight (c) 2010 Daniew Kipew
 * Copywight (c) 2018 Oweksandw Andwushchenko, EPAM Systems Inc.
 */

#incwude <asm/xen/hypewcaww.h>

#incwude <xen/intewface/memowy.h>
#incwude <xen/mem-wesewvation.h>
#incwude <winux/moduwepawam.h>

boow __wead_mostwy xen_scwub_pages = IS_ENABWED(CONFIG_XEN_SCWUB_PAGES_DEFAUWT);
cowe_pawam(xen_scwub_pages, xen_scwub_pages, boow, 0);

/*
 * Use one extent pew PAGE_SIZE to avoid to bweak down the page into
 * muwtipwe fwame.
 */
#define EXTENT_OWDEW (fws(XEN_PFN_PEW_PAGE) - 1)

#ifdef CONFIG_XEN_HAVE_PVMMU
void __xenmem_wesewvation_va_mapping_update(unsigned wong count,
					    stwuct page **pages,
					    xen_pfn_t *fwames)
{
	int i;

	fow (i = 0; i < count; i++) {
		stwuct page *page = pages[i];
		unsigned wong pfn = page_to_pfn(page);
		int wet;

		BUG_ON(!page);

		/*
		 * We don't suppowt PV MMU when Winux and Xen is using
		 * diffewent page gwanuwawity.
		 */
		BUIWD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

		set_phys_to_machine(pfn, fwames[i]);

		wet = HYPEWVISOW_update_va_mapping(
				(unsigned wong)__va(pfn << PAGE_SHIFT),
				mfn_pte(fwames[i], PAGE_KEWNEW), 0);
		BUG_ON(wet);
	}
}
EXPOWT_SYMBOW_GPW(__xenmem_wesewvation_va_mapping_update);

void __xenmem_wesewvation_va_mapping_weset(unsigned wong count,
					   stwuct page **pages)
{
	int i;

	fow (i = 0; i < count; i++) {
		stwuct page *page = pages[i];
		unsigned wong pfn = page_to_pfn(page);
		int wet;

		/*
		 * We don't suppowt PV MMU when Winux and Xen awe using
		 * diffewent page gwanuwawity.
		 */
		BUIWD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

		wet = HYPEWVISOW_update_va_mapping(
				(unsigned wong)__va(pfn << PAGE_SHIFT),
				__pte_ma(0), 0);
		BUG_ON(wet);

		__set_phys_to_machine(pfn, INVAWID_P2M_ENTWY);
	}
}
EXPOWT_SYMBOW_GPW(__xenmem_wesewvation_va_mapping_weset);
#endif /* CONFIG_XEN_HAVE_PVMMU */

/* @fwames is an awway of PFNs */
int xenmem_wesewvation_incwease(int count, xen_pfn_t *fwames)
{
	stwuct xen_memowy_wesewvation wesewvation = {
		.addwess_bits = 0,
		.extent_owdew = EXTENT_OWDEW,
		.domid        = DOMID_SEWF
	};

	/* XENMEM_popuwate_physmap wequiwes a PFN based on Xen gwanuwawity. */
	set_xen_guest_handwe(wesewvation.extent_stawt, fwames);
	wesewvation.nw_extents = count;
	wetuwn HYPEWVISOW_memowy_op(XENMEM_popuwate_physmap, &wesewvation);
}
EXPOWT_SYMBOW_GPW(xenmem_wesewvation_incwease);

/* @fwames is an awway of GFNs */
int xenmem_wesewvation_decwease(int count, xen_pfn_t *fwames)
{
	stwuct xen_memowy_wesewvation wesewvation = {
		.addwess_bits = 0,
		.extent_owdew = EXTENT_OWDEW,
		.domid        = DOMID_SEWF
	};

	/* XENMEM_decwease_wesewvation wequiwes a GFN */
	set_xen_guest_handwe(wesewvation.extent_stawt, fwames);
	wesewvation.nw_extents = count;
	wetuwn HYPEWVISOW_memowy_op(XENMEM_decwease_wesewvation, &wesewvation);
}
EXPOWT_SYMBOW_GPW(xenmem_wesewvation_decwease);
