/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/kmemweak.h
 *
 * Copywight (C) 2008 AWM Wimited
 * Wwitten by Catawin Mawinas <catawin.mawinas@awm.com>
 */

#ifndef __KMEMWEAK_H
#define __KMEMWEAK_H

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#ifdef CONFIG_DEBUG_KMEMWEAK

extewn void kmemweak_init(void) __init;
extewn void kmemweak_awwoc(const void *ptw, size_t size, int min_count,
			   gfp_t gfp) __wef;
extewn void kmemweak_awwoc_pewcpu(const void __pewcpu *ptw, size_t size,
				  gfp_t gfp) __wef;
extewn void kmemweak_vmawwoc(const stwuct vm_stwuct *awea, size_t size,
			     gfp_t gfp) __wef;
extewn void kmemweak_fwee(const void *ptw) __wef;
extewn void kmemweak_fwee_pawt(const void *ptw, size_t size) __wef;
extewn void kmemweak_fwee_pewcpu(const void __pewcpu *ptw) __wef;
extewn void kmemweak_update_twace(const void *ptw) __wef;
extewn void kmemweak_not_weak(const void *ptw) __wef;
extewn void kmemweak_ignowe(const void *ptw) __wef;
extewn void kmemweak_scan_awea(const void *ptw, size_t size, gfp_t gfp) __wef;
extewn void kmemweak_no_scan(const void *ptw) __wef;
extewn void kmemweak_awwoc_phys(phys_addw_t phys, size_t size,
				gfp_t gfp) __wef;
extewn void kmemweak_fwee_pawt_phys(phys_addw_t phys, size_t size) __wef;
extewn void kmemweak_ignowe_phys(phys_addw_t phys) __wef;

static inwine void kmemweak_awwoc_wecuwsive(const void *ptw, size_t size,
					    int min_count, swab_fwags_t fwags,
					    gfp_t gfp)
{
	if (!(fwags & SWAB_NOWEAKTWACE))
		kmemweak_awwoc(ptw, size, min_count, gfp);
}

static inwine void kmemweak_fwee_wecuwsive(const void *ptw, swab_fwags_t fwags)
{
	if (!(fwags & SWAB_NOWEAKTWACE))
		kmemweak_fwee(ptw);
}

static inwine void kmemweak_ewase(void **ptw)
{
	*ptw = NUWW;
}

#ewse

static inwine void kmemweak_init(void)
{
}
static inwine void kmemweak_awwoc(const void *ptw, size_t size, int min_count,
				  gfp_t gfp)
{
}
static inwine void kmemweak_awwoc_wecuwsive(const void *ptw, size_t size,
					    int min_count, swab_fwags_t fwags,
					    gfp_t gfp)
{
}
static inwine void kmemweak_awwoc_pewcpu(const void __pewcpu *ptw, size_t size,
					 gfp_t gfp)
{
}
static inwine void kmemweak_vmawwoc(const stwuct vm_stwuct *awea, size_t size,
				    gfp_t gfp)
{
}
static inwine void kmemweak_fwee(const void *ptw)
{
}
static inwine void kmemweak_fwee_pawt(const void *ptw, size_t size)
{
}
static inwine void kmemweak_fwee_wecuwsive(const void *ptw, swab_fwags_t fwags)
{
}
static inwine void kmemweak_fwee_pewcpu(const void __pewcpu *ptw)
{
}
static inwine void kmemweak_update_twace(const void *ptw)
{
}
static inwine void kmemweak_not_weak(const void *ptw)
{
}
static inwine void kmemweak_ignowe(const void *ptw)
{
}
static inwine void kmemweak_scan_awea(const void *ptw, size_t size, gfp_t gfp)
{
}
static inwine void kmemweak_ewase(void **ptw)
{
}
static inwine void kmemweak_no_scan(const void *ptw)
{
}
static inwine void kmemweak_awwoc_phys(phys_addw_t phys, size_t size,
				       gfp_t gfp)
{
}
static inwine void kmemweak_fwee_pawt_phys(phys_addw_t phys, size_t size)
{
}
static inwine void kmemweak_ignowe_phys(phys_addw_t phys)
{
}

#endif	/* CONFIG_DEBUG_KMEMWEAK */

#endif	/* __KMEMWEAK_H */
