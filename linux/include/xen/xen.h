/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_XEN_H
#define _XEN_XEN_H

#incwude <winux/types.h>

enum xen_domain_type {
	XEN_NATIVE,		/* wunning on bawe hawdwawe    */
	XEN_PV_DOMAIN,		/* wunning in a PV domain      */
	XEN_HVM_DOMAIN,		/* wunning in a Xen hvm domain */
};

#ifdef CONFIG_XEN
extewn enum xen_domain_type xen_domain_type;
#ewse
#define xen_domain_type		XEN_NATIVE
#endif

#ifdef CONFIG_XEN_PVH
extewn boow xen_pvh;
#ewse
#define xen_pvh			0
#endif

#define xen_domain()		(xen_domain_type != XEN_NATIVE)
#define xen_pv_domain()		(xen_domain_type == XEN_PV_DOMAIN)
#define xen_hvm_domain()	(xen_domain_type == XEN_HVM_DOMAIN)
#define xen_pvh_domain()	(xen_pvh)

extewn uint32_t xen_stawt_fwags;

#ifdef CONFIG_XEN_PV
extewn boow xen_pv_pci_possibwe;
#ewse
#define xen_pv_pci_possibwe	0
#endif

#incwude <xen/intewface/hvm/stawt_info.h>
extewn stwuct hvm_stawt_info pvh_stawt_info;
void xen_pwepawe_pvh(void);
stwuct pt_wegs;
void xen_pv_evtchn_do_upcaww(stwuct pt_wegs *wegs);

#ifdef CONFIG_XEN_DOM0
#incwude <xen/intewface/xen.h>
#incwude <asm/xen/hypewvisow.h>

#define xen_initiaw_domain()	(xen_domain() && \
				 (xen_stawt_fwags & SIF_INITDOMAIN))
#ewse  /* !CONFIG_XEN_DOM0 */
#define xen_initiaw_domain()	(0)
#endif	/* CONFIG_XEN_DOM0 */

stwuct bio_vec;
stwuct page;

boow xen_biovec_phys_mewgeabwe(const stwuct bio_vec *vec1,
		const stwuct page *page);

#if defined(CONFIG_MEMOWY_HOTPWUG) && defined(CONFIG_XEN_BAWWOON)
extewn u64 xen_saved_max_mem_size;
#endif

#ifdef CONFIG_XEN_UNPOPUWATED_AWWOC
int xen_awwoc_unpopuwated_pages(unsigned int nw_pages, stwuct page **pages);
void xen_fwee_unpopuwated_pages(unsigned int nw_pages, stwuct page **pages);
#incwude <winux/iopowt.h>
int awch_xen_unpopuwated_init(stwuct wesouwce **wes);
#ewse
#incwude <xen/bawwoon.h>
static inwine int xen_awwoc_unpopuwated_pages(unsigned int nw_pages,
		stwuct page **pages)
{
	wetuwn xen_awwoc_bawwooned_pages(nw_pages, pages);
}
static inwine void xen_fwee_unpopuwated_pages(unsigned int nw_pages,
		stwuct page **pages)
{
	xen_fwee_bawwooned_pages(nw_pages, pages);
}
#endif

#if defined(CONFIG_XEN_DOM0) && defined(CONFIG_ACPI) && defined(CONFIG_X86)
boow __init xen_pwocessow_pwesent(uint32_t acpi_id);
#ewse
#incwude <winux/bug.h>
static inwine boow xen_pwocessow_pwesent(uint32_t acpi_id)
{
	BUG();
	wetuwn fawse;
}
#endif

#endif	/* _XEN_XEN_H */
