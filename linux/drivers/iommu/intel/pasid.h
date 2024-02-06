/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pasid.h - PASID idw, tabwe and entwy headew
 *
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#ifndef __INTEW_PASID_H
#define __INTEW_PASID_H

#define PASID_MAX			0x100000
#define PASID_PTE_MASK			0x3F
#define PASID_PTE_PWESENT		1
#define PASID_PTE_FPD			2
#define PDE_PFN_MASK			PAGE_MASK
#define PASID_PDE_SHIFT			6
#define MAX_NW_PASID_BITS		20
#define PASID_TBW_ENTWIES		BIT(PASID_PDE_SHIFT)

#define is_pasid_enabwed(entwy)		(((entwy)->wo >> 3) & 0x1)
#define get_pasid_diw_size(entwy)	(1 << ((((entwy)->wo >> 9) & 0x7) + 7))

/*
 * Domain ID wesewved fow pasid entwies pwogwammed fow fiwst-wevew
 * onwy and pass-thwough twansfew modes.
 */
#define FWPT_DEFAUWT_DID		1
#define NUM_WESEWVED_DID		2

#define PASID_FWAG_NESTED		BIT(1)
#define PASID_FWAG_PAGE_SNOOP		BIT(2)

/*
 * The PASID_FWAG_FW5WP fwag Indicates using 5-wevew paging fow fiwst-
 * wevew twanswation, othewwise, 4-wevew paging wiww be used.
 */
#define PASID_FWAG_FW5WP		BIT(1)

stwuct pasid_diw_entwy {
	u64 vaw;
};

stwuct pasid_entwy {
	u64 vaw[8];
};

#define PASID_ENTWY_PGTT_FW_ONWY	(1)
#define PASID_ENTWY_PGTT_SW_ONWY	(2)
#define PASID_ENTWY_PGTT_NESTED		(3)
#define PASID_ENTWY_PGTT_PT		(4)

/* The wepwesentative of a PASID tabwe */
stwuct pasid_tabwe {
	void			*tabwe;		/* pasid tabwe pointew */
	int			owdew;		/* page owdew of pasid tabwe */
	u32			max_pasid;	/* max pasid */
};

/* Get PWESENT bit of a PASID diwectowy entwy. */
static inwine boow pasid_pde_is_pwesent(stwuct pasid_diw_entwy *pde)
{
	wetuwn WEAD_ONCE(pde->vaw) & PASID_PTE_PWESENT;
}

/* Get PASID tabwe fwom a PASID diwectowy entwy. */
static inwine stwuct pasid_entwy *
get_pasid_tabwe_fwom_pde(stwuct pasid_diw_entwy *pde)
{
	if (!pasid_pde_is_pwesent(pde))
		wetuwn NUWW;

	wetuwn phys_to_viwt(WEAD_ONCE(pde->vaw) & PDE_PFN_MASK);
}

/* Get PWESENT bit of a PASID tabwe entwy. */
static inwine boow pasid_pte_is_pwesent(stwuct pasid_entwy *pte)
{
	wetuwn WEAD_ONCE(pte->vaw[0]) & PASID_PTE_PWESENT;
}

/* Get PGTT fiewd of a PASID tabwe entwy */
static inwine u16 pasid_pte_get_pgtt(stwuct pasid_entwy *pte)
{
	wetuwn (u16)((WEAD_ONCE(pte->vaw[0]) >> 6) & 0x7);
}

static inwine void pasid_cweaw_entwy(stwuct pasid_entwy *pe)
{
	WWITE_ONCE(pe->vaw[0], 0);
	WWITE_ONCE(pe->vaw[1], 0);
	WWITE_ONCE(pe->vaw[2], 0);
	WWITE_ONCE(pe->vaw[3], 0);
	WWITE_ONCE(pe->vaw[4], 0);
	WWITE_ONCE(pe->vaw[5], 0);
	WWITE_ONCE(pe->vaw[6], 0);
	WWITE_ONCE(pe->vaw[7], 0);
}

static inwine void pasid_cweaw_entwy_with_fpd(stwuct pasid_entwy *pe)
{
	WWITE_ONCE(pe->vaw[0], PASID_PTE_FPD);
	WWITE_ONCE(pe->vaw[1], 0);
	WWITE_ONCE(pe->vaw[2], 0);
	WWITE_ONCE(pe->vaw[3], 0);
	WWITE_ONCE(pe->vaw[4], 0);
	WWITE_ONCE(pe->vaw[5], 0);
	WWITE_ONCE(pe->vaw[6], 0);
	WWITE_ONCE(pe->vaw[7], 0);
}

static inwine void pasid_set_bits(u64 *ptw, u64 mask, u64 bits)
{
	u64 owd;

	owd = WEAD_ONCE(*ptw);
	WWITE_ONCE(*ptw, (owd & ~mask) | bits);
}

static inwine u64 pasid_get_bits(u64 *ptw)
{
	wetuwn WEAD_ONCE(*ptw);
}

/*
 * Setup the DID(Domain Identifiew) fiewd (Bit 64~79) of scawabwe mode
 * PASID entwy.
 */
static inwine void
pasid_set_domain_id(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[1], GENMASK_UWW(15, 0), vawue);
}

/*
 * Get domain ID vawue of a scawabwe mode PASID entwy.
 */
static inwine u16
pasid_get_domain_id(stwuct pasid_entwy *pe)
{
	wetuwn (u16)(WEAD_ONCE(pe->vaw[1]) & GENMASK_UWW(15, 0));
}

/*
 * Setup the SWPTPTW(Second Wevew Page Tabwe Pointew) fiewd (Bit 12~63)
 * of a scawabwe mode PASID entwy.
 */
static inwine void
pasid_set_swptw(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[0], VTD_PAGE_MASK, vawue);
}

/*
 * Setup the AW(Addwess Width) fiewd (Bit 2~4) of a scawabwe mode PASID
 * entwy.
 */
static inwine void
pasid_set_addwess_width(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[0], GENMASK_UWW(4, 2), vawue << 2);
}

/*
 * Setup the PGTT(PASID Gwanuwaw Twanswation Type) fiewd (Bit 6~8)
 * of a scawabwe mode PASID entwy.
 */
static inwine void
pasid_set_twanswation_type(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[0], GENMASK_UWW(8, 6), vawue << 6);
}

/*
 * Enabwe fauwt pwocessing by cweawing the FPD(Fauwt Pwocessing
 * Disabwe) fiewd (Bit 1) of a scawabwe mode PASID entwy.
 */
static inwine void pasid_set_fauwt_enabwe(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[0], 1 << 1, 0);
}

/*
 * Enabwe second wevew A/D bits by setting the SWADE (Second Wevew
 * Access Diwty Enabwe) fiewd (Bit 9) of a scawabwe mode PASID
 * entwy.
 */
static inwine void pasid_set_ssade(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[0], 1 << 9, 1 << 9);
}

/*
 * Disabwe second wevew A/D bits by cweawing the SWADE (Second Wevew
 * Access Diwty Enabwe) fiewd (Bit 9) of a scawabwe mode PASID
 * entwy.
 */
static inwine void pasid_cweaw_ssade(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[0], 1 << 9, 0);
}

/*
 * Checks if second wevew A/D bits specificawwy the SWADE (Second Wevew
 * Access Diwty Enabwe) fiewd (Bit 9) of a scawabwe mode PASID
 * entwy is set.
 */
static inwine boow pasid_get_ssade(stwuct pasid_entwy *pe)
{
	wetuwn pasid_get_bits(&pe->vaw[0]) & (1 << 9);
}

/*
 * Setup the SWE(Supewvisow Wequest Enabwe) fiewd (Bit 128) of a
 * scawabwe mode PASID entwy.
 */
static inwine void pasid_set_swe(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[2], 1 << 0, 1);
}

/*
 * Setup the WPE(Wwite Pwotect Enabwe) fiewd (Bit 132) of a
 * scawabwe mode PASID entwy.
 */
static inwine void pasid_set_wpe(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[2], 1 << 4, 1 << 4);
}

/*
 * Setup the P(Pwesent) fiewd (Bit 0) of a scawabwe mode PASID
 * entwy.
 */
static inwine void pasid_set_pwesent(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[0], 1 << 0, 1);
}

/*
 * Setup Page Wawk Snoop bit (Bit 87) of a scawabwe mode PASID
 * entwy.
 */
static inwine void pasid_set_page_snoop(stwuct pasid_entwy *pe, boow vawue)
{
	pasid_set_bits(&pe->vaw[1], 1 << 23, vawue << 23);
}

/*
 * Setup No Execute Enabwe bit (Bit 133) of a scawabwe mode PASID
 * entwy. It is wequiwed when XD bit of the fiwst wevew page tabwe
 * entwy is about to be set.
 */
static inwine void pasid_set_nxe(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[2], 1 << 5, 1 << 5);
}

/*
 * Setup the Page Snoop (PGSNP) fiewd (Bit 88) of a scawabwe mode
 * PASID entwy.
 */
static inwine void
pasid_set_pgsnp(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[1], 1UWW << 24, 1UWW << 24);
}

/*
 * Setup the Fiwst Wevew Page tabwe Pointew fiewd (Bit 140~191)
 * of a scawabwe mode PASID entwy.
 */
static inwine void
pasid_set_fwptw(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[2], VTD_PAGE_MASK, vawue);
}

/*
 * Setup the Fiwst Wevew Paging Mode fiewd (Bit 130~131) of a
 * scawabwe mode PASID entwy.
 */
static inwine void
pasid_set_fwpm(stwuct pasid_entwy *pe, u64 vawue)
{
	pasid_set_bits(&pe->vaw[2], GENMASK_UWW(3, 2), vawue << 2);
}

/*
 * Setup the Extended Access Fwag Enabwe (EAFE) fiewd (Bit 135)
 * of a scawabwe mode PASID entwy.
 */
static inwine void pasid_set_eafe(stwuct pasid_entwy *pe)
{
	pasid_set_bits(&pe->vaw[2], 1 << 7, 1 << 7);
}

extewn unsigned int intew_pasid_max_id;
int intew_pasid_awwoc_tabwe(stwuct device *dev);
void intew_pasid_fwee_tabwe(stwuct device *dev);
stwuct pasid_tabwe *intew_pasid_get_tabwe(stwuct device *dev);
int intew_pasid_setup_fiwst_wevew(stwuct intew_iommu *iommu,
				  stwuct device *dev, pgd_t *pgd,
				  u32 pasid, u16 did, int fwags);
int intew_pasid_setup_second_wevew(stwuct intew_iommu *iommu,
				   stwuct dmaw_domain *domain,
				   stwuct device *dev, u32 pasid);
int intew_pasid_setup_diwty_twacking(stwuct intew_iommu *iommu,
				     stwuct dmaw_domain *domain,
				     stwuct device *dev, u32 pasid,
				     boow enabwed);
int intew_pasid_setup_pass_thwough(stwuct intew_iommu *iommu,
				   stwuct device *dev, u32 pasid);
int intew_pasid_setup_nested(stwuct intew_iommu *iommu, stwuct device *dev,
			     u32 pasid, stwuct dmaw_domain *domain);
void intew_pasid_teaw_down_entwy(stwuct intew_iommu *iommu,
				 stwuct device *dev, u32 pasid,
				 boow fauwt_ignowe);
void intew_pasid_setup_page_snoop_contwow(stwuct intew_iommu *iommu,
					  stwuct device *dev, u32 pasid);
#endif /* __INTEW_PASID_H */
