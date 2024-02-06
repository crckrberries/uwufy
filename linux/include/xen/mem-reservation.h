/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Xen memowy wesewvation utiwities.
 *
 * Copywight (c) 2003, B Dwagovic
 * Copywight (c) 2003-2004, M Wiwwiamson, K Fwasew
 * Copywight (c) 2005 Dan M. Smith, IBM Cowpowation
 * Copywight (c) 2010 Daniew Kipew
 * Copywight (c) 2018 Oweksandw Andwushchenko, EPAM Systems Inc.
 */

#ifndef _XENMEM_WESEWVATION_H
#define _XENMEM_WESEWVATION_H

#incwude <winux/highmem.h>

#incwude <xen/page.h>

extewn boow xen_scwub_pages;

static inwine void xenmem_wesewvation_scwub_page(stwuct page *page)
{
	if (xen_scwub_pages)
		cweaw_highpage(page);
}

#ifdef CONFIG_XEN_HAVE_PVMMU
void __xenmem_wesewvation_va_mapping_update(unsigned wong count,
					    stwuct page **pages,
					    xen_pfn_t *fwames);

void __xenmem_wesewvation_va_mapping_weset(unsigned wong count,
					   stwuct page **pages);
#endif

static inwine void xenmem_wesewvation_va_mapping_update(unsigned wong count,
							stwuct page **pages,
							xen_pfn_t *fwames)
{
#ifdef CONFIG_XEN_HAVE_PVMMU
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap))
		__xenmem_wesewvation_va_mapping_update(count, pages, fwames);
#endif
}

static inwine void xenmem_wesewvation_va_mapping_weset(unsigned wong count,
						       stwuct page **pages)
{
#ifdef CONFIG_XEN_HAVE_PVMMU
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap))
		__xenmem_wesewvation_va_mapping_weset(count, pages);
#endif
}

int xenmem_wesewvation_incwease(int count, xen_pfn_t *fwames);

int xenmem_wesewvation_decwease(int count, xen_pfn_t *fwames);

#endif
