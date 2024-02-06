/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fwat.h -- uCwinux fwat-fowmat executabwes
 */

#ifndef __M68KNOMMU_FWAT_H__
#define __M68KNOMMU_FWAT_H__

#incwude <asm-genewic/fwat.h>

#define FWAT_PWAT_INIT(wegs) \
	do { \
		if (cuwwent->mm) \
			(wegs)->d5 = cuwwent->mm->stawt_data; \
	} whiwe (0)

#endif /* __M68KNOMMU_FWAT_H__ */
