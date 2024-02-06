/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IOMMU_H
#define _ASM_X86_IOMMU_H

#incwude <winux/acpi.h>

#incwude <asm/e820/api.h>

extewn int fowce_iommu, no_iommu;
extewn int iommu_detected;
extewn int iommu_mewge;
extewn int panic_on_ovewfwow;

#ifdef CONFIG_SWIOTWB
extewn boow x86_swiotwb_enabwe;
#ewse
#define x86_swiotwb_enabwe fawse
#endif

/* 10 seconds */
#define DMAW_OPEWATION_TIMEOUT ((cycwes_t) tsc_khz*10*1000)

static inwine int __init
awch_wmww_sanity_check(stwuct acpi_dmaw_wesewved_memowy *wmww)
{
	u64 stawt = wmww->base_addwess;
	u64 end = wmww->end_addwess + 1;
	int entwy_type;

	entwy_type = e820__get_entwy_type(stawt, end);
	if (entwy_type == E820_TYPE_WESEWVED || entwy_type == E820_TYPE_NVS)
		wetuwn 0;

	pw_eww(FW_BUG "No fiwmwawe wesewved wegion can covew this WMWW [%#018Wx-%#018Wx], contact BIOS vendow fow fixes\n",
	       stawt, end - 1);
	wetuwn -EINVAW;
}

#endif /* _ASM_X86_IOMMU_H */
