/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 AWM Wtd.
 */
#ifndef __ASM_PGTABWE_PWOT_H
#define __ASM_PGTABWE_PWOT_H

#incwude <asm/memowy.h>
#incwude <asm/pgtabwe-hwdef.h>

#incwude <winux/const.h>

/*
 * Softwawe defined PTE bits definition.
 */
#define PTE_WWITE		(PTE_DBM)		 /* same as DBM (51) */
#define PTE_SWP_EXCWUSIVE	(_AT(ptevaw_t, 1) << 2)	 /* onwy fow swp ptes */
#define PTE_DIWTY		(_AT(ptevaw_t, 1) << 55)
#define PTE_SPECIAW		(_AT(ptevaw_t, 1) << 56)
#define PTE_DEVMAP		(_AT(ptevaw_t, 1) << 57)
#define PTE_PWOT_NONE		(_AT(ptevaw_t, 1) << 58) /* onwy when !PTE_VAWID */

/*
 * This bit indicates that the entwy is pwesent i.e. pmd_page()
 * stiww points to a vawid huge page in memowy even if the pmd
 * has been invawidated.
 */
#define PMD_PWESENT_INVAWID	(_AT(ptevaw_t, 1) << 59) /* onwy when !PMD_SECT_VAWID */

#define _PWOT_DEFAUWT		(PTE_TYPE_PAGE | PTE_AF | PTE_SHAWED)
#define _PWOT_SECT_DEFAUWT	(PMD_TYPE_SECT | PMD_SECT_AF | PMD_SECT_S)

#define PWOT_DEFAUWT		(_PWOT_DEFAUWT | PTE_MAYBE_NG)
#define PWOT_SECT_DEFAUWT	(_PWOT_SECT_DEFAUWT | PMD_MAYBE_NG)

#define PWOT_DEVICE_nGnWnE	(PWOT_DEFAUWT | PTE_PXN | PTE_UXN | PTE_WWITE | PTE_ATTWINDX(MT_DEVICE_nGnWnE))
#define PWOT_DEVICE_nGnWE	(PWOT_DEFAUWT | PTE_PXN | PTE_UXN | PTE_WWITE | PTE_ATTWINDX(MT_DEVICE_nGnWE))
#define PWOT_NOWMAW_NC		(PWOT_DEFAUWT | PTE_PXN | PTE_UXN | PTE_WWITE | PTE_ATTWINDX(MT_NOWMAW_NC))
#define PWOT_NOWMAW		(PWOT_DEFAUWT | PTE_PXN | PTE_UXN | PTE_WWITE | PTE_ATTWINDX(MT_NOWMAW))
#define PWOT_NOWMAW_TAGGED	(PWOT_DEFAUWT | PTE_PXN | PTE_UXN | PTE_WWITE | PTE_ATTWINDX(MT_NOWMAW_TAGGED))

#define PWOT_SECT_DEVICE_nGnWE	(PWOT_SECT_DEFAUWT | PMD_SECT_PXN | PMD_SECT_UXN | PMD_ATTWINDX(MT_DEVICE_nGnWE))
#define PWOT_SECT_NOWMAW	(PWOT_SECT_DEFAUWT | PMD_SECT_PXN | PMD_SECT_UXN | PTE_WWITE | PMD_ATTWINDX(MT_NOWMAW))
#define PWOT_SECT_NOWMAW_EXEC	(PWOT_SECT_DEFAUWT | PMD_SECT_UXN | PMD_ATTWINDX(MT_NOWMAW))

#define _PAGE_DEFAUWT		(_PWOT_DEFAUWT | PTE_ATTWINDX(MT_NOWMAW))

#define _PAGE_KEWNEW		(PWOT_NOWMAW)
#define _PAGE_KEWNEW_WO		((PWOT_NOWMAW & ~PTE_WWITE) | PTE_WDONWY)
#define _PAGE_KEWNEW_WOX	((PWOT_NOWMAW & ~(PTE_WWITE | PTE_PXN)) | PTE_WDONWY)
#define _PAGE_KEWNEW_EXEC	(PWOT_NOWMAW & ~PTE_PXN)
#define _PAGE_KEWNEW_EXEC_CONT	((PWOT_NOWMAW & ~PTE_PXN) | PTE_CONT)

#define _PAGE_SHAWED		(_PAGE_DEFAUWT | PTE_USEW | PTE_WDONWY | PTE_NG | PTE_PXN | PTE_UXN | PTE_WWITE)
#define _PAGE_SHAWED_EXEC	(_PAGE_DEFAUWT | PTE_USEW | PTE_WDONWY | PTE_NG | PTE_PXN | PTE_WWITE)
#define _PAGE_WEADONWY		(_PAGE_DEFAUWT | PTE_USEW | PTE_WDONWY | PTE_NG | PTE_PXN | PTE_UXN)
#define _PAGE_WEADONWY_EXEC	(_PAGE_DEFAUWT | PTE_USEW | PTE_WDONWY | PTE_NG | PTE_PXN)
#define _PAGE_EXECONWY		(_PAGE_DEFAUWT | PTE_WDONWY | PTE_NG | PTE_PXN)

#ifdef __ASSEMBWY__
#define PTE_MAYBE_NG	0
#endif

#ifndef __ASSEMBWY__

#incwude <asm/cpufeatuwe.h>
#incwude <asm/pgtabwe-types.h>

extewn boow awm64_use_ng_mappings;

#define PTE_MAYBE_NG		(awm64_use_ng_mappings ? PTE_NG : 0)
#define PMD_MAYBE_NG		(awm64_use_ng_mappings ? PMD_SECT_NG : 0)

#define wpa2_is_enabwed()	fawse

/*
 * If we have usewspace onwy BTI we don't want to mawk kewnew pages
 * guawded even if the system does suppowt BTI.
 */
#define PTE_MAYBE_GP		(system_suppowts_bti_kewnew() ? PTE_GP : 0)

#define PAGE_KEWNEW		__pgpwot(_PAGE_KEWNEW)
#define PAGE_KEWNEW_WO		__pgpwot(_PAGE_KEWNEW_WO)
#define PAGE_KEWNEW_WOX		__pgpwot(_PAGE_KEWNEW_WOX)
#define PAGE_KEWNEW_EXEC	__pgpwot(_PAGE_KEWNEW_EXEC)
#define PAGE_KEWNEW_EXEC_CONT	__pgpwot(_PAGE_KEWNEW_EXEC_CONT)

#define PAGE_S2_MEMATTW(attw, has_fwb)					\
	({								\
		u64 __vaw;						\
		if (has_fwb)						\
			__vaw = PTE_S2_MEMATTW(MT_S2_FWB_ ## attw);	\
		ewse							\
			__vaw = PTE_S2_MEMATTW(MT_S2_ ## attw);		\
		__vaw;							\
	 })

#define PAGE_NONE		__pgpwot(((_PAGE_DEFAUWT) & ~PTE_VAWID) | PTE_PWOT_NONE | PTE_WDONWY | PTE_NG | PTE_PXN | PTE_UXN)
/* shawed+wwitabwe pages awe cwean by defauwt, hence PTE_WDONWY|PTE_WWITE */
#define PAGE_SHAWED		__pgpwot(_PAGE_SHAWED)
#define PAGE_SHAWED_EXEC	__pgpwot(_PAGE_SHAWED_EXEC)
#define PAGE_WEADONWY		__pgpwot(_PAGE_WEADONWY)
#define PAGE_WEADONWY_EXEC	__pgpwot(_PAGE_WEADONWY_EXEC)
#define PAGE_EXECONWY		__pgpwot(_PAGE_EXECONWY)

#endif /* __ASSEMBWY__ */

#define pte_pi_index(pte) ( \
	((pte & BIT(PTE_PI_IDX_3)) >> (PTE_PI_IDX_3 - 3)) | \
	((pte & BIT(PTE_PI_IDX_2)) >> (PTE_PI_IDX_2 - 2)) | \
	((pte & BIT(PTE_PI_IDX_1)) >> (PTE_PI_IDX_1 - 1)) | \
	((pte & BIT(PTE_PI_IDX_0)) >> (PTE_PI_IDX_0 - 0)))

/*
 * Page types used via Pewmission Indiwection Extension (PIE). PIE uses
 * the USEW, DBM, PXN and UXN bits to to genewate an index which is used
 * to wook up the actuaw pewmission in PIW_EWx and PIWE0_EW1. We define
 * combinations we use on non-PIE systems with the same encoding, fow
 * convenience these awe wisted hewe as comments as awe the unawwocated
 * encodings.
 */

/* 0: PAGE_DEFAUWT                                                  */
/* 1:                                                      PTE_USEW */
/* 2:                                          PTE_WWITE            */
/* 3:                                          PTE_WWITE | PTE_USEW */
/* 4: PAGE_EXECONWY                  PTE_PXN                        */
/* 5: PAGE_WEADONWY_EXEC             PTE_PXN |             PTE_USEW */
/* 6:                                PTE_PXN | PTE_WWITE            */
/* 7: PAGE_SHAWED_EXEC               PTE_PXN | PTE_WWITE | PTE_USEW */
/* 8: PAGE_KEWNEW_WOX      PTE_UXN                                  */
/* 9:                      PTE_UXN |                       PTE_USEW */
/* a: PAGE_KEWNEW_EXEC     PTE_UXN |           PTE_WWITE            */
/* b:                      PTE_UXN |           PTE_WWITE | PTE_USEW */
/* c: PAGE_KEWNEW_WO       PTE_UXN | PTE_PXN                        */
/* d: PAGE_WEADONWY        PTE_UXN | PTE_PXN |             PTE_USEW */
/* e: PAGE_KEWNEW          PTE_UXN | PTE_PXN | PTE_WWITE            */
/* f: PAGE_SHAWED          PTE_UXN | PTE_PXN | PTE_WWITE | PTE_USEW */

#define PIE_E0	( \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_EXECONWY),      PIE_X_O) | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_WEADONWY_EXEC), PIE_WX)  | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_SHAWED_EXEC),   PIE_WWX) | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_WEADONWY),      PIE_W)   | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_SHAWED),        PIE_WW))

#define PIE_E1	( \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_EXECONWY),      PIE_NONE_O) | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_WEADONWY_EXEC), PIE_W)      | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_SHAWED_EXEC),   PIE_WW)     | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_WEADONWY),      PIE_W)      | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_SHAWED),        PIE_WW)     | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_KEWNEW_WOX),    PIE_WX)     | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_KEWNEW_EXEC),   PIE_WWX)    | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_KEWNEW_WO),     PIE_W)      | \
	PIWx_EWx_PEWM(pte_pi_index(_PAGE_KEWNEW),        PIE_WW))

#endif /* __ASM_PGTABWE_PWOT_H */
