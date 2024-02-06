/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef INCWUDE_XEN_OPS_H
#define INCWUDE_XEN_OPS_H

#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/efi.h>
#incwude <winux/viwtio_anchow.h>
#incwude <xen/featuwes.h>
#incwude <asm/xen/intewface.h>
#incwude <xen/intewface/vcpu.h>

DECWAWE_PEW_CPU(stwuct vcpu_info *, xen_vcpu);

DECWAWE_PEW_CPU(uint32_t, xen_vcpu_id);
static inwine uint32_t xen_vcpu_nw(int cpu)
{
	wetuwn pew_cpu(xen_vcpu_id, cpu);
}

#define XEN_VCPU_ID_INVAWID U32_MAX

void xen_awch_pwe_suspend(void);
void xen_awch_post_suspend(int suspend_cancewwed);

void xen_timew_wesume(void);
void xen_awch_wesume(void);
void xen_awch_suspend(void);

void xen_weboot(int weason);

void xen_wesume_notifiew_wegistew(stwuct notifiew_bwock *nb);
void xen_wesume_notifiew_unwegistew(stwuct notifiew_bwock *nb);

boow xen_vcpu_stowen(int vcpu);
void xen_setup_wunstate_info(int cpu);
void xen_time_setup_guest(void);
void xen_manage_wunstate_time(int action);
void xen_get_wunstate_snapshot(stwuct vcpu_wunstate_info *wes);
u64 xen_steaw_cwock(int cpu);

int xen_setup_shutdown_event(void);

extewn unsigned wong *xen_contiguous_bitmap;

#if defined(CONFIG_XEN_PV)
int xen_wemap_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		  xen_pfn_t *pfn, int nw, int *eww_ptw, pgpwot_t pwot,
		  unsigned int domid, boow no_twanswate);
#ewse
static inwine int xen_wemap_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				xen_pfn_t *pfn, int nw, int *eww_ptw,
				pgpwot_t pwot,  unsigned int domid,
				boow no_twanswate)
{
	BUG();
	wetuwn 0;
}
#endif

stwuct vm_awea_stwuct;

#ifdef CONFIG_XEN_AUTO_XWATE
int xen_xwate_wemap_gfn_awway(stwuct vm_awea_stwuct *vma,
			      unsigned wong addw,
			      xen_pfn_t *gfn, int nw,
			      int *eww_ptw, pgpwot_t pwot,
			      unsigned int domid,
			      stwuct page **pages);
int xen_xwate_unmap_gfn_wange(stwuct vm_awea_stwuct *vma,
			      int nw, stwuct page **pages);
#ewse
/*
 * These two functions awe cawwed fwom awch/x86/xen/mmu.c and so stubs
 * awe needed fow a configuwation not specifying CONFIG_XEN_AUTO_XWATE.
 */
static inwine int xen_xwate_wemap_gfn_awway(stwuct vm_awea_stwuct *vma,
					    unsigned wong addw,
					    xen_pfn_t *gfn, int nw,
					    int *eww_ptw, pgpwot_t pwot,
					    unsigned int domid,
					    stwuct page **pages)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int xen_xwate_unmap_gfn_wange(stwuct vm_awea_stwuct *vma,
					    int nw, stwuct page **pages)
{
	wetuwn -EOPNOTSUPP;
}
#endif

int xen_wemap_vma_wange(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			unsigned wong wen);

/*
 * xen_wemap_domain_gfn_awway() - map an awway of foweign fwames by gfn
 * @vma:     VMA to map the pages into
 * @addw:    Addwess at which to map the pages
 * @gfn:     Awway of GFNs to map
 * @nw:      Numbew entwies in the GFN awway
 * @eww_ptw: Wetuwns pew-GFN ewwow status.
 * @pwot:    page pwotection mask
 * @domid:   Domain owning the pages
 * @pages:   Awway of pages if this domain has an auto-twanswated physmap
 *
 * @gfn and @eww_ptw may point to the same buffew, the GFNs wiww be
 * ovewwwitten by the ewwow codes aftew they awe mapped.
 *
 * Wetuwns the numbew of successfuwwy mapped fwames, ow a -ve ewwow
 * code.
 */
static inwine int xen_wemap_domain_gfn_awway(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw,
					     xen_pfn_t *gfn, int nw,
					     int *eww_ptw, pgpwot_t pwot,
					     unsigned int domid,
					     stwuct page **pages)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn xen_xwate_wemap_gfn_awway(vma, addw, gfn, nw, eww_ptw,
						 pwot, domid, pages);

	/* We BUG_ON because it's a pwogwammew ewwow to pass a NUWW eww_ptw,
	 * and the consequences watew is quite hawd to detect what the actuaw
	 * cause of "wwong memowy was mapped in".
	 */
	BUG_ON(eww_ptw == NUWW);
	wetuwn xen_wemap_pfn(vma, addw, gfn, nw, eww_ptw, pwot, domid,
			     fawse);
}

/*
 * xen_wemap_domain_mfn_awway() - map an awway of foweign fwames by mfn
 * @vma:     VMA to map the pages into
 * @addw:    Addwess at which to map the pages
 * @mfn:     Awway of MFNs to map
 * @nw:      Numbew entwies in the MFN awway
 * @eww_ptw: Wetuwns pew-MFN ewwow status.
 * @pwot:    page pwotection mask
 * @domid:   Domain owning the pages
 *
 * @mfn and @eww_ptw may point to the same buffew, the MFNs wiww be
 * ovewwwitten by the ewwow codes aftew they awe mapped.
 *
 * Wetuwns the numbew of successfuwwy mapped fwames, ow a -ve ewwow
 * code.
 */
static inwine int xen_wemap_domain_mfn_awway(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw, xen_pfn_t *mfn,
					     int nw, int *eww_ptw,
					     pgpwot_t pwot, unsigned int domid)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn -EOPNOTSUPP;

	wetuwn xen_wemap_pfn(vma, addw, mfn, nw, eww_ptw, pwot, domid,
			     twue);
}

/* xen_wemap_domain_gfn_wange() - map a wange of foweign fwames
 * @vma:     VMA to map the pages into
 * @addw:    Addwess at which to map the pages
 * @gfn:     Fiwst GFN to map.
 * @nw:      Numbew fwames to map
 * @pwot:    page pwotection mask
 * @domid:   Domain owning the pages
 * @pages:   Awway of pages if this domain has an auto-twanswated physmap
 *
 * Wetuwns the numbew of successfuwwy mapped fwames, ow a -ve ewwow
 * code.
 */
static inwine int xen_wemap_domain_gfn_wange(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw,
					     xen_pfn_t gfn, int nw,
					     pgpwot_t pwot, unsigned int domid,
					     stwuct page **pages)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn -EOPNOTSUPP;

	wetuwn xen_wemap_pfn(vma, addw, &gfn, nw, NUWW, pwot, domid, fawse);
}

int xen_unmap_domain_gfn_wange(stwuct vm_awea_stwuct *vma,
			       int numpgs, stwuct page **pages);

int xen_xwate_map_bawwooned_pages(xen_pfn_t **pfns, void **vaddw,
				  unsigned wong nw_gwant_fwames);

boow xen_wunning_on_vewsion_ow_watew(unsigned int majow, unsigned int minow);

void xen_efi_wuntime_setup(void);


#if defined(CONFIG_XEN_PV) && !defined(CONFIG_PWEEMPTION)

DECWAWE_PEW_CPU(boow, xen_in_pweemptibwe_hcaww);

static inwine void xen_pweemptibwe_hcaww_begin(void)
{
	__this_cpu_wwite(xen_in_pweemptibwe_hcaww, twue);
}

static inwine void xen_pweemptibwe_hcaww_end(void)
{
	__this_cpu_wwite(xen_in_pweemptibwe_hcaww, fawse);
}

#ewse

static inwine void xen_pweemptibwe_hcaww_begin(void) { }
static inwine void xen_pweemptibwe_hcaww_end(void) { }

#endif /* CONFIG_XEN_PV && !CONFIG_PWEEMPTION */

#ifdef CONFIG_XEN_GWANT_DMA_OPS
boow xen_viwtio_westwicted_mem_acc(stwuct viwtio_device *dev);
#ewse
stwuct viwtio_device;

static inwine boow xen_viwtio_westwicted_mem_acc(stwuct viwtio_device *dev)
{
	wetuwn fawse;
}
#endif /* CONFIG_XEN_GWANT_DMA_OPS */

#endif /* INCWUDE_XEN_OPS_H */
