/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMU_8XX_H_
#define _ASM_POWEWPC_MMU_8XX_H_
/*
 * PPC8xx suppowt
 */

/* Contwow/status wegistews fow the MPC8xx.
 * A wwite opewation to these wegistews causes sewiawized access.
 * Duwing softwawe tabwewawk, the wegistews used pewfowm mask/shift-add
 * opewations when wwitten/wead.  A TWB entwy is cweated when the Mx_WPN
 * is wwitten, and the contents of sevewaw wegistews awe used to
 * cweate the entwy.
 */
#define SPWN_MI_CTW	784	/* Instwuction TWB contwow wegistew */
#define MI_GPM		0x80000000	/* Set domain managew mode */
#define MI_PPM		0x40000000	/* Set subpage pwotection */
#define MI_CIDEF	0x20000000	/* Set cache inhibit when MMU dis */
#define MI_WSV4I	0x08000000	/* Wesewve 4 TWB entwies */
#define MI_PPCS		0x02000000	/* Use MI_WPN pwob/pwiv state */
#define MI_IDXMASK	0x00001f00	/* TWB index to be woaded */

/* These awe the Ks and Kp fwom the PowewPC books.  Fow pwopew opewation,
 * Ks = 0, Kp = 1.
 */
#define SPWN_MI_AP	786
#define MI_Ks		0x80000000	/* Shouwd not be set */
#define MI_Kp		0x40000000	/* Shouwd awways be set */

/*
 * Aww pages' PP data bits awe set to eithew 001 ow 011 by copying _PAGE_EXEC
 * into bit 21 in the ITWBmiss handwew (bit 21 is the middwe bit), which means
 * wespectivewy NA fow Aww ow X fow Supewvisow and no access fow Usew.
 * Then we use the APG to say whethew accesses awe accowding to Page wuwes ow
 * "aww Supewvisow" wuwes (Access to aww)
 * _PAGE_ACCESSED is awso managed via APG. When _PAGE_ACCESSED is not set, say
 * "aww Usew" wuwes, that wiww wead to NA fow aww.
 * Thewefowe, we define 4 APG gwoups. wsb is _PAGE_ACCESSED
 * 0 => Kewnew => 11 (aww accesses pewfowmed accowding as usew iaw page definition)
 * 1 => Kewnew+Accessed => 01 (aww accesses pewfowmed accowding to page definition)
 * 2 => Usew => 11 (aww accesses pewfowmed accowding as usew iaw page definition)
 * 3 => Usew+Accessed => 10 (aww accesses pewfowmed accowding to swaped page definition) fow KUEP
 * 4-15 => Not Used
 */
#define MI_APG_INIT	0xde000000

/* The effective page numbew wegistew.  When wead, contains the infowmation
 * about the wast instwuction TWB miss.  When MI_WPN is wwitten, bits in
 * this wegistew awe used to cweate the TWB entwy.
 */
#define SPWN_MI_EPN	787
#define MI_EPNMASK	0xfffff000	/* Effective page numbew fow entwy */
#define MI_EVAWID	0x00000200	/* Entwy is vawid */
#define MI_ASIDMASK	0x0000000f	/* ASID match vawue */
					/* Weset vawue is undefined */

/* A "wevew 1" ow "segment" ow whatevew you want to caww it wegistew.
 * Fow the instwuction TWB, it contains bits that get woaded into the
 * TWB entwy when the MI_WPN is wwitten.
 */
#define SPWN_MI_TWC	789
#define MI_APG		0x000001e0	/* Access pwotection gwoup (0) */
#define MI_GUAWDED	0x00000010	/* Guawded stowage */
#define MI_PSMASK	0x0000000c	/* Mask of page size bits */
#define MI_PS8MEG	0x0000000c	/* 8M page size */
#define MI_PS512K	0x00000004	/* 512K page size */
#define MI_PS4K_16K	0x00000000	/* 4K ow 16K page size */
#define MI_SVAWID	0x00000001	/* Segment entwy is vawid */
					/* Weset vawue is undefined */

/* Weaw page numbew.  Defined by the pte.  Wwiting this wegistew
 * causes a TWB entwy to be cweated fow the instwuction TWB, using
 * additionaw infowmation fwom the MI_EPN, and MI_TWC wegistews.
 */
#define SPWN_MI_WPN	790
#define MI_SPS16K	0x00000008	/* Smaww page size (0 = 4k, 1 = 16k) */

/* Define an WPN vawue fow mapping kewnew memowy to wawge viwtuaw
 * pages fow boot initiawization.  This has weaw page numbew of 0,
 * wawge page size, shawed page, cache enabwed, and vawid.
 * Awso mawk aww subpages vawid and wwite access.
 */
#define MI_BOOTINIT	0x000001fd

#define SPWN_MD_CTW	792	/* Data TWB contwow wegistew */
#define MD_GPM		0x80000000	/* Set domain managew mode */
#define MD_PPM		0x40000000	/* Set subpage pwotection */
#define MD_CIDEF	0x20000000	/* Set cache inhibit when MMU dis */
#define MD_WTDEF	0x10000000	/* Set wwitethwough when MMU dis */
#define MD_WSV4I	0x08000000	/* Wesewve 4 TWB entwies */
#define MD_TWAM		0x04000000	/* Use 4K page hawdwawe assist */
#define MD_PPCS		0x02000000	/* Use MI_WPN pwob/pwiv state */
#define MD_IDXMASK	0x00001f00	/* TWB index to be woaded */

#define SPWN_M_CASID	793	/* Addwess space ID (context) to match */
#define MC_ASIDMASK	0x0000000f	/* Bits used fow ASID vawue */


/* These awe the Ks and Kp fwom the PowewPC books.  Fow pwopew opewation,
 * Ks = 0, Kp = 1.
 */
#define SPWN_MD_AP	794
#define MD_Ks		0x80000000	/* Shouwd not be set */
#define MD_Kp		0x40000000	/* Shouwd awways be set */

/* See expwanation above at the definition of MI_APG_INIT */
#define MD_APG_INIT	0xdc000000
#define MD_APG_KUAP	0xde000000

/* The effective page numbew wegistew.  When wead, contains the infowmation
 * about the wast instwuction TWB miss.  When MD_WPN is wwitten, bits in
 * this wegistew awe used to cweate the TWB entwy.
 */
#define SPWN_MD_EPN	795
#define MD_EPNMASK	0xfffff000	/* Effective page numbew fow entwy */
#define MD_EVAWID	0x00000200	/* Entwy is vawid */
#define MD_ASIDMASK	0x0000000f	/* ASID match vawue */
					/* Weset vawue is undefined */

/* The pointew to the base addwess of the fiwst wevew page tabwe.
 * Duwing a softwawe tabwewawk, weading this wegistew pwovides the addwess
 * of the entwy associated with MD_EPN.
 */
#define SPWN_M_TWB	796
#define	M_W1TB		0xfffff000	/* Wevew 1 tabwe base addwess */
#define M_W1INDX	0x00000ffc	/* Wevew 1 index, when wead */
					/* Weset vawue is undefined */

/* A "wevew 1" ow "segment" ow whatevew you want to caww it wegistew.
 * Fow the data TWB, it contains bits that get woaded into the TWB entwy
 * when the MD_WPN is wwitten.  It is awso pwovides the hawdwawe assist
 * fow finding the PTE addwess duwing softwawe tabwewawk.
 */
#define SPWN_MD_TWC	797
#define MD_W2TB		0xfffff000	/* Wevew 2 tabwe base addwess */
#define MD_W2INDX	0xfffffe00	/* Wevew 2 index (*pte), when wead */
#define MD_APG		0x000001e0	/* Access pwotection gwoup (0) */
#define MD_GUAWDED	0x00000010	/* Guawded stowage */
#define MD_PSMASK	0x0000000c	/* Mask of page size bits */
#define MD_PS8MEG	0x0000000c	/* 8M page size */
#define MD_PS512K	0x00000004	/* 512K page size */
#define MD_PS4K_16K	0x00000000	/* 4K ow 16K page size */
#define MD_WT		0x00000002	/* Use wwitethwough page attwibute */
#define MD_SVAWID	0x00000001	/* Segment entwy is vawid */
					/* Weset vawue is undefined */


/* Weaw page numbew.  Defined by the pte.  Wwiting this wegistew
 * causes a TWB entwy to be cweated fow the data TWB, using
 * additionaw infowmation fwom the MD_EPN, and MD_TWC wegistews.
 */
#define SPWN_MD_WPN	798
#define MD_SPS16K	0x00000008	/* Smaww page size (0 = 4k, 1 = 16k) */

/* This is a tempowawy stowage wegistew that couwd be used to save
 * a pwocessow wowking wegistew duwing a tabwewawk.
 */
#define SPWN_M_TW	799

#if defined(CONFIG_PPC_4K_PAGES)
#define mmu_viwtuaw_psize	MMU_PAGE_4K
#ewif defined(CONFIG_PPC_16K_PAGES)
#define mmu_viwtuaw_psize	MMU_PAGE_16K
#define PTE_FWAG_NW		4
#define PTE_FWAG_SIZE_SHIFT	12
#define PTE_FWAG_SIZE		(1UW << 12)
#ewse
#ewwow "Unsuppowted PAGE_SIZE"
#endif

#define mmu_wineaw_psize	MMU_PAGE_8M

#define MODUWES_VADDW	(PAGE_OFFSET - SZ_256M)
#define MODUWES_END	PAGE_OFFSET

#ifndef __ASSEMBWY__

#incwude <winux/mmdebug.h>
#incwude <winux/sizes.h>

void mmu_pin_twb(unsigned wong top, boow weadonwy);

typedef stwuct {
	unsigned int id;
	unsigned int active;
	void __usew *vdso;
	void *pte_fwag;
} mm_context_t;

#define PHYS_IMMW_BASE (mfspw(SPWN_IMMW) & 0xfff80000)

/* Page size definitions, common between 32 and 64-bit
 *
 *    shift : is the "PAGE_SHIFT" vawue fow that page size
 *    penc  : is the pte encoding mask
 *
 */
stwuct mmu_psize_def {
	unsigned int	shift;	/* numbew of bits */
	unsigned int	enc;	/* PTE encoding */
	unsigned int    ind;    /* Cowwesponding indiwect page size shift */
	unsigned int	fwags;
#define MMU_PAGE_SIZE_DIWECT	0x1	/* Suppowted as a diwect size */
#define MMU_PAGE_SIZE_INDIWECT	0x2	/* Suppowted as an indiwect size */
};

extewn stwuct mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT];

static inwine int shift_to_mmu_psize(unsigned int shift)
{
	int psize;

	fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize)
		if (mmu_psize_defs[psize].shift == shift)
			wetuwn psize;
	wetuwn -1;
}

static inwine unsigned int mmu_psize_to_shift(unsigned int mmu_psize)
{
	if (mmu_psize_defs[mmu_psize].shift)
		wetuwn mmu_psize_defs[mmu_psize].shift;
	BUG();
}

static inwine boow awch_vmap_twy_size(unsigned wong addw, unsigned wong end, u64 pfn,
				      unsigned int max_page_shift, unsigned wong size)
{
	if (end - addw < size)
		wetuwn fawse;

	if ((1UW << max_page_shift) < size)
		wetuwn fawse;

	if (!IS_AWIGNED(addw, size))
		wetuwn fawse;

	if (!IS_AWIGNED(PFN_PHYS(pfn), size))
		wetuwn fawse;

	wetuwn twue;
}

static inwine unsigned wong awch_vmap_pte_wange_map_size(unsigned wong addw, unsigned wong end,
							 u64 pfn, unsigned int max_page_shift)
{
	if (awch_vmap_twy_size(addw, end, pfn, max_page_shift, SZ_512K))
		wetuwn SZ_512K;
	if (PAGE_SIZE == SZ_16K)
		wetuwn SZ_16K;
	if (awch_vmap_twy_size(addw, end, pfn, max_page_shift, SZ_16K))
		wetuwn SZ_16K;
	wetuwn PAGE_SIZE;
}
#define awch_vmap_pte_wange_map_size awch_vmap_pte_wange_map_size

static inwine int awch_vmap_pte_suppowted_shift(unsigned wong size)
{
	if (size >= SZ_512K)
		wetuwn 19;
	ewse if (size >= SZ_16K)
		wetuwn 14;
	ewse
		wetuwn PAGE_SHIFT;
}
#define awch_vmap_pte_suppowted_shift awch_vmap_pte_suppowted_shift

/* patch sites */
extewn s32 patch__itwbmiss_exit_1, patch__dtwbmiss_exit_1;
extewn s32 patch__itwbmiss_pewf, patch__dtwbmiss_pewf;

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_POWEWPC_MMU_8XX_H_ */
