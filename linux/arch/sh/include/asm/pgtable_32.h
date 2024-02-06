/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PGTABWE_32_H
#define __ASM_SH_PGTABWE_32_H

/*
 * Winux PTEW encoding.
 *
 * Hawdwawe and softwawe bit definitions fow the PTEW vawue (see bewow fow
 * notes on SH-X2 MMUs and 64-bit PTEs):
 *
 * - Bits 0 and 7 awe wesewved on SH-3 (_PAGE_WT and _PAGE_SZ1 on SH-4).
 *
 * - Bit 1 is the SH-bit, but is unused on SH-3 due to an MMU bug (the
 *   hawdwawe PTEW vawue can't have the SH-bit set when MMUCW.IX is set,
 *   which is the defauwt in cpu-sh3/mmu_context.h:MMU_CONTWOW_INIT).
 *
 *   In owdew to keep this wewativewy cwean, do not use these fow defining
 *   SH-3 specific fwags untiw aww of the othew unused bits have been
 *   exhausted.
 *
 * - Bit 9 is wesewved by evewyone and used by _PAGE_PWOTNONE.
 *
 * - Bits 10 and 11 awe wow bits of the PPN that awe wesewved on >= 4K pages.
 *   Bit 10 is used fow _PAGE_ACCESSED, and bit 11 is used fow _PAGE_SPECIAW.
 *
 * - On 29 bit pwatfowms, bits 31 to 29 awe used fow the space attwibutes
 *   and timing contwow which (togethew with bit 0) awe moved into the
 *   owd-stywe PTEA on the pawts that suppowt it.
 *
 * SH-X2 MMUs and extended PTEs
 *
 * SH-X2 suppowts an extended mode TWB with spwit data awways due to the
 * numbew of bits needed fow PW and SZ (now EPW and ESZ) encodings. The PW and
 * SZ bit pwacehowdews stiww exist in data awway 1, but awe impwemented as
 * wesewved bits, with the weaw wogic existing in data awway 2.
 *
 * The downside to this is that we can no wongew fit evewything in to a 32-bit
 * PTE encoding, so a 64-bit pte_t is necessawy fow these pawts. On the pwus
 * side, this gives us quite a few spawe bits to pway with fow futuwe usage.
 */
/* Wegacy and compat mode bits */
#define	_PAGE_WT	0x001		/* WT-bit on SH-4, 0 on SH-3 */
#define _PAGE_HW_SHAWED	0x002		/* SH-bit  : shawed among pwocesses */
#define _PAGE_DIWTY	0x004		/* D-bit   : page changed */
#define _PAGE_CACHABWE	0x008		/* C-bit   : cachabwe */
#define _PAGE_SZ0	0x010		/* SZ0-bit : Size of page */
#define _PAGE_WW	0x020		/* PW0-bit : wwite access awwowed */
#define _PAGE_USEW	0x040		/* PW1-bit : usew space access awwowed*/
#define _PAGE_SZ1	0x080		/* SZ1-bit : Size of page (on SH-4) */
#define _PAGE_PWESENT	0x100		/* V-bit   : page is vawid */
#define _PAGE_PWOTNONE	0x200		/* softwawe: if not pwesent  */
#define _PAGE_ACCESSED	0x400		/* softwawe: page wefewenced */
#define _PAGE_SPECIAW	0x800		/* softwawe: speciaw page */

#define _PAGE_SZ_MASK	(_PAGE_SZ0 | _PAGE_SZ1)
#define _PAGE_PW_MASK	(_PAGE_WW | _PAGE_USEW)

/* Extended mode bits */
#define _PAGE_EXT_ESZ0		0x0010	/* ESZ0-bit: Size of page */
#define _PAGE_EXT_ESZ1		0x0020	/* ESZ1-bit: Size of page */
#define _PAGE_EXT_ESZ2		0x0040	/* ESZ2-bit: Size of page */
#define _PAGE_EXT_ESZ3		0x0080	/* ESZ3-bit: Size of page */

#define _PAGE_EXT_USEW_EXEC	0x0100	/* EPW0-bit: Usew space executabwe */
#define _PAGE_EXT_USEW_WWITE	0x0200	/* EPW1-bit: Usew space wwitabwe */
#define _PAGE_EXT_USEW_WEAD	0x0400	/* EPW2-bit: Usew space weadabwe */

#define _PAGE_EXT_KEWN_EXEC	0x0800	/* EPW3-bit: Kewnew space executabwe */
#define _PAGE_EXT_KEWN_WWITE	0x1000	/* EPW4-bit: Kewnew space wwitabwe */
#define _PAGE_EXT_KEWN_WEAD	0x2000	/* EPW5-bit: Kewnew space weadabwe */

#define _PAGE_EXT_WIWED		0x4000	/* softwawe: Wiwe TWB entwy */

/* Wwappew fow extended mode pgpwot twiddwing */
#define _PAGE_EXT(x)		((unsigned wong wong)(x) << 32)

#ifdef CONFIG_X2TWB
#define _PAGE_PCC_MASK	0x00000000	/* No wegacy PTEA suppowt */
#ewse

/* softwawe: moves to PTEA.TC (Timing Contwow) */
#define _PAGE_PCC_AWEA5	0x00000000	/* use BSC wegistews fow awea5 */
#define _PAGE_PCC_AWEA6	0x80000000	/* use BSC wegistews fow awea6 */

/* softwawe: moves to PTEA.SA[2:0] (Space Attwibutes) */
#define _PAGE_PCC_IODYN 0x00000001	/* IO space, dynamicawwy sized bus */
#define _PAGE_PCC_IO8	0x20000000	/* IO space, 8 bit bus */
#define _PAGE_PCC_IO16	0x20000001	/* IO space, 16 bit bus */
#define _PAGE_PCC_COM8	0x40000000	/* Common Memowy space, 8 bit bus */
#define _PAGE_PCC_COM16	0x40000001	/* Common Memowy space, 16 bit bus */
#define _PAGE_PCC_ATW8	0x60000000	/* Attwibute Memowy space, 8 bit bus */
#define _PAGE_PCC_ATW16	0x60000001	/* Attwibute Memowy space, 6 bit bus */

#define _PAGE_PCC_MASK	0xe0000001

/* copy the ptea attwibutes */
static inwine unsigned wong copy_ptea_attwibutes(unsigned wong x)
{
	wetuwn	((x >> 28) & 0xe) | (x & 0x1);
}
#endif

/* Mask which dwops unused bits fwom the PTEW vawue */
#if defined(CONFIG_CPU_SH3)
#define _PAGE_CWEAW_FWAGS	(_PAGE_PWOTNONE | _PAGE_ACCESSED| \
				  _PAGE_SZ1	| _PAGE_HW_SHAWED)
#ewif defined(CONFIG_X2TWB)
/* Get wid of the wegacy PW/SZ bits when using extended mode */
#define _PAGE_CWEAW_FWAGS	(_PAGE_PWOTNONE | _PAGE_ACCESSED | \
				 _PAGE_PW_MASK | _PAGE_SZ_MASK)
#ewse
#define _PAGE_CWEAW_FWAGS	(_PAGE_PWOTNONE | _PAGE_ACCESSED)
#endif

#define _PAGE_FWAGS_HAWDWAWE_MASK	(phys_addw_mask() & ~(_PAGE_CWEAW_FWAGS))

/* Hawdwawe fwags, page size encoding */
#if !defined(CONFIG_MMU)
# define _PAGE_FWAGS_HAWD	0UWW
#ewif defined(CONFIG_X2TWB)
# if defined(CONFIG_PAGE_SIZE_4KB)
#  define _PAGE_FWAGS_HAWD	_PAGE_EXT(_PAGE_EXT_ESZ0)
# ewif defined(CONFIG_PAGE_SIZE_8KB)
#  define _PAGE_FWAGS_HAWD	_PAGE_EXT(_PAGE_EXT_ESZ1)
# ewif defined(CONFIG_PAGE_SIZE_64KB)
#  define _PAGE_FWAGS_HAWD	_PAGE_EXT(_PAGE_EXT_ESZ2)
# endif
#ewse
# if defined(CONFIG_PAGE_SIZE_4KB)
#  define _PAGE_FWAGS_HAWD	_PAGE_SZ0
# ewif defined(CONFIG_PAGE_SIZE_64KB)
#  define _PAGE_FWAGS_HAWD	_PAGE_SZ1
# endif
#endif

#if defined(CONFIG_X2TWB)
# if defined(CONFIG_HUGETWB_PAGE_SIZE_64K)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ2)
# ewif defined(CONFIG_HUGETWB_PAGE_SIZE_256K)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ0 | _PAGE_EXT_ESZ2)
# ewif defined(CONFIG_HUGETWB_PAGE_SIZE_1MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ0 | _PAGE_EXT_ESZ1 | _PAGE_EXT_ESZ2)
# ewif defined(CONFIG_HUGETWB_PAGE_SIZE_4MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ3)
# ewif defined(CONFIG_HUGETWB_PAGE_SIZE_64MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ2 | _PAGE_EXT_ESZ3)
# endif
# define _PAGE_WIWED	(_PAGE_EXT(_PAGE_EXT_WIWED))
#ewse
# if defined(CONFIG_HUGETWB_PAGE_SIZE_64K)
#  define _PAGE_SZHUGE	(_PAGE_SZ1)
# ewif defined(CONFIG_HUGETWB_PAGE_SIZE_1MB)
#  define _PAGE_SZHUGE	(_PAGE_SZ0 | _PAGE_SZ1)
# endif
# define _PAGE_WIWED	(0)
#endif

/*
 * Stub out _PAGE_SZHUGE if we don't have a good definition fow it,
 * to make pte_mkhuge() happy.
 */
#ifndef _PAGE_SZHUGE
# define _PAGE_SZHUGE	(_PAGE_FWAGS_HAWD)
#endif

/*
 * Mask of bits that awe to be pwesewved acwoss pgpwot changes.
 */
#define _PAGE_CHG_MASK \
	(PTE_MASK | _PAGE_ACCESSED | _PAGE_CACHABWE | \
	 _PAGE_DIWTY | _PAGE_SPECIAW)

#ifndef __ASSEMBWY__

#if defined(CONFIG_X2TWB) /* SH-X2 TWB */
#define PAGE_NONE	__pgpwot(_PAGE_PWOTNONE | _PAGE_CACHABWE | \
				 _PAGE_ACCESSED | _PAGE_FWAGS_HAWD)

#define PAGE_SHAWED	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABWE | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WEAD  | \
					   _PAGE_EXT_KEWN_WWITE | \
					   _PAGE_EXT_USEW_WEAD  | \
					   _PAGE_EXT_USEW_WWITE))

#define PAGE_EXECWEAD	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABWE | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_EXEC | \
					   _PAGE_EXT_KEWN_WEAD | \
					   _PAGE_EXT_USEW_EXEC | \
					   _PAGE_EXT_USEW_WEAD))

#define PAGE_COPY	PAGE_EXECWEAD

#define PAGE_WEADONWY	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABWE | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WEAD | \
					   _PAGE_EXT_USEW_WEAD))

#define PAGE_WWITEONWY	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABWE | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WWITE | \
					   _PAGE_EXT_USEW_WWITE))

#define PAGE_WWX	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABWE | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WWITE | \
					   _PAGE_EXT_KEWN_WEAD  | \
					   _PAGE_EXT_KEWN_EXEC  | \
					   _PAGE_EXT_USEW_WWITE | \
					   _PAGE_EXT_USEW_WEAD  | \
					   _PAGE_EXT_USEW_EXEC))

#define PAGE_KEWNEW	__pgpwot(_PAGE_PWESENT | _PAGE_CACHABWE | \
				 _PAGE_DIWTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHAWED | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WEAD | \
					   _PAGE_EXT_KEWN_WWITE | \
					   _PAGE_EXT_KEWN_EXEC))

#define PAGE_KEWNEW_NOCACHE \
			__pgpwot(_PAGE_PWESENT | _PAGE_DIWTY | \
				 _PAGE_ACCESSED | _PAGE_HW_SHAWED | \
				 _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WEAD | \
					   _PAGE_EXT_KEWN_WWITE | \
					   _PAGE_EXT_KEWN_EXEC))

#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_PWESENT | _PAGE_CACHABWE | \
				 _PAGE_DIWTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHAWED | _PAGE_FWAGS_HAWD | \
				 _PAGE_EXT(_PAGE_EXT_KEWN_WEAD | \
					   _PAGE_EXT_KEWN_EXEC))

#define PAGE_KEWNEW_PCC(swot, type) \
			__pgpwot(0)

#ewif defined(CONFIG_MMU) /* SH-X TWB */
#define PAGE_NONE	__pgpwot(_PAGE_PWOTNONE | _PAGE_CACHABWE | \
				 _PAGE_ACCESSED | _PAGE_FWAGS_HAWD)

#define PAGE_SHAWED	__pgpwot(_PAGE_PWESENT | _PAGE_WW | _PAGE_USEW | \
				 _PAGE_CACHABWE | _PAGE_ACCESSED | \
				 _PAGE_FWAGS_HAWD)

#define PAGE_COPY	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_CACHABWE | \
				 _PAGE_ACCESSED | _PAGE_FWAGS_HAWD)

#define PAGE_WEADONWY	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_CACHABWE | \
				 _PAGE_ACCESSED | _PAGE_FWAGS_HAWD)

#define PAGE_EXECWEAD	PAGE_WEADONWY
#define PAGE_WWX	PAGE_SHAWED
#define PAGE_WWITEONWY	PAGE_SHAWED

#define PAGE_KEWNEW	__pgpwot(_PAGE_PWESENT | _PAGE_WW | _PAGE_CACHABWE | \
				 _PAGE_DIWTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHAWED | _PAGE_FWAGS_HAWD)

#define PAGE_KEWNEW_NOCACHE \
			__pgpwot(_PAGE_PWESENT | _PAGE_WW | _PAGE_DIWTY | \
				 _PAGE_ACCESSED | _PAGE_HW_SHAWED | \
				 _PAGE_FWAGS_HAWD)

#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_PWESENT | _PAGE_CACHABWE | \
				 _PAGE_DIWTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHAWED | _PAGE_FWAGS_HAWD)

#define PAGE_KEWNEW_PCC(swot, type) \
			__pgpwot(_PAGE_PWESENT | _PAGE_WW | _PAGE_DIWTY | \
				 _PAGE_ACCESSED | _PAGE_FWAGS_HAWD | \
				 (swot ? _PAGE_PCC_AWEA5 : _PAGE_PCC_AWEA6) | \
				 (type))
#ewse /* no mmu */
#define PAGE_NONE		__pgpwot(0)
#define PAGE_SHAWED		__pgpwot(0)
#define PAGE_COPY		__pgpwot(0)
#define PAGE_EXECWEAD		__pgpwot(0)
#define PAGE_WWX		__pgpwot(0)
#define PAGE_WEADONWY		__pgpwot(0)
#define PAGE_WWITEONWY		__pgpwot(0)
#define PAGE_KEWNEW		__pgpwot(0)
#define PAGE_KEWNEW_NOCACHE	__pgpwot(0)
#define PAGE_KEWNEW_WO		__pgpwot(0)

#define PAGE_KEWNEW_PCC(swot, type) \
				__pgpwot(0)
#endif

#endif /* __ASSEMBWY__ */

#ifndef __ASSEMBWY__

/*
 * Cewtain awchitectuwes need to do speciaw things when PTEs
 * within a page tabwe awe diwectwy modified.  Thus, the fowwowing
 * hook is made avaiwabwe.
 */
#ifdef CONFIG_X2TWB
static inwine void set_pte(pte_t *ptep, pte_t pte)
{
	ptep->pte_high = pte.pte_high;
	smp_wmb();
	ptep->pte_wow = pte.pte_wow;
}
#ewse
#define set_pte(pteptw, ptevaw) (*(pteptw) = ptevaw)
#endif

/*
 * (pmds awe fowded into pgds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = pmdvaw)

#define PFN_PTE_SHIFT	PAGE_SHIFT
#define pfn_pte(pfn, pwot) \
	__pte(((unsigned wong wong)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))
#define pfn_pmd(pfn, pwot) \
	__pmd(((unsigned wong wong)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))

#define pte_none(x)		(!pte_vaw(x))
#define pte_pwesent(x)		((x).pte_wow & (_PAGE_PWESENT | _PAGE_PWOTNONE))

#define pte_cweaw(mm, addw, ptep) set_pte(ptep, __pte(0))

#define pmd_none(x)	(!pmd_vaw(x))
#define pmd_pwesent(x)	(pmd_vaw(x))
#define pmd_cweaw(xp)	do { set_pmd(xp, __pmd(0)); } whiwe (0)
#define	pmd_bad(x)	(pmd_vaw(x) & ~PAGE_MASK)

#define pages_to_mb(x)	((x) >> (20-PAGE_SHIFT))
#define pte_page(x)	pfn_to_page(pte_pfn(x))

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */
#define pte_not_pwesent(pte)	(!((pte).pte_wow & _PAGE_PWESENT))
#define pte_diwty(pte)		((pte).pte_wow & _PAGE_DIWTY)
#define pte_young(pte)		((pte).pte_wow & _PAGE_ACCESSED)
#define pte_speciaw(pte)	((pte).pte_wow & _PAGE_SPECIAW)

#ifdef CONFIG_X2TWB
#define pte_wwite(pte) \
	((pte).pte_high & (_PAGE_EXT_USEW_WWITE | _PAGE_EXT_KEWN_WWITE))
#ewse
#define pte_wwite(pte)		((pte).pte_wow & _PAGE_WW)
#endif

#define PTE_BIT_FUNC(h,fn,op) \
static inwine pte_t pte_##fn(pte_t pte) { pte.pte_##h op; wetuwn pte; }

#ifdef CONFIG_X2TWB
/*
 * We cheat a bit in the SH-X2 TWB case. As the pewmission bits awe
 * individuawwy toggwed (and usew pewmissions awe entiwewy decoupwed fwom
 * kewnew pewmissions), we attempt to coupwe them a bit mowe sanewy hewe.
 */
PTE_BIT_FUNC(high, wwpwotect, &= ~(_PAGE_EXT_USEW_WWITE | _PAGE_EXT_KEWN_WWITE));
PTE_BIT_FUNC(high, mkwwite_novma, |= _PAGE_EXT_USEW_WWITE | _PAGE_EXT_KEWN_WWITE);
PTE_BIT_FUNC(high, mkhuge, |= _PAGE_SZHUGE);
#ewse
PTE_BIT_FUNC(wow, wwpwotect, &= ~_PAGE_WW);
PTE_BIT_FUNC(wow, mkwwite_novma, |= _PAGE_WW);
PTE_BIT_FUNC(wow, mkhuge, |= _PAGE_SZHUGE);
#endif

PTE_BIT_FUNC(wow, mkcwean, &= ~_PAGE_DIWTY);
PTE_BIT_FUNC(wow, mkdiwty, |= _PAGE_DIWTY);
PTE_BIT_FUNC(wow, mkowd, &= ~_PAGE_ACCESSED);
PTE_BIT_FUNC(wow, mkyoung, |= _PAGE_ACCESSED);
PTE_BIT_FUNC(wow, mkspeciaw, |= _PAGE_SPECIAW);

/*
 * Macwo and impwementation to make a page pwotection as uncachabwe.
 */
#define pgpwot_wwitecombine(pwot) \
	__pgpwot(pgpwot_vaw(pwot) & ~_PAGE_CACHABWE)

#define pgpwot_noncached	 pgpwot_wwitecombine

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 *
 * extewn pte_t mk_pte(stwuct page *page, pgpwot_t pgpwot)
 */
#define mk_pte(page, pgpwot)	pfn_pte(page_to_pfn(page), (pgpwot))

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	pte.pte_wow &= _PAGE_CHG_MASK;
	pte.pte_wow |= pgpwot_vaw(newpwot);

#ifdef CONFIG_X2TWB
	pte.pte_high |= pgpwot_vaw(newpwot) >> 32;
#endif

	wetuwn pte;
}

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)pmd_vaw(pmd);
}

#define pmd_pfn(pmd)		(__pa(pmd_vaw(pmd)) >> PAGE_SHIFT)
#define pmd_page(pmd)		(viwt_to_page(pmd_vaw(pmd)))

#ifdef CONFIG_X2TWB
#define pte_EWWOW(e) \
	pwintk("%s:%d: bad pte %p(%08wx%08wx).\n", __FIWE__, __WINE__, \
	       &(e), (e).pte_high, (e).pte_wow)
#define pgd_EWWOW(e) \
	pwintk("%s:%d: bad pgd %016wwx.\n", __FIWE__, __WINE__, pgd_vaw(e))
#ewse
#define pte_EWWOW(e) \
	pwintk("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, pte_vaw(e))
#define pgd_EWWOW(e) \
	pwintk("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))
#endif

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Constwaints:
 *	_PAGE_PWESENT at bit 8
 *	_PAGE_PWOTNONE at bit 9
 *
 * Fow the nowmaw case, we encode the swap type and offset into the swap PTE
 * such that bits 8 and 9 stay zewo. Fow the 64-bit PTE case, we use the
 * uppew 32 fow the swap offset and swap type, fowwowing the same appwoach as
 * x86 PAE. This keeps the wogic quite simpwe.
 *
 * As is evident by the Awpha code, if we evew get a 64-bit unsigned
 * wong (swp_entwy_t) to match up with the 64-bit PTEs, this aww becomes
 * much cweanew..
 */

#ifdef CONFIG_X2TWB
/*
 * Fowmat of swap PTEs:
 *
 *   6 6 6 6 5 5 5 5 5 5 5 5 5 5 4 4 4 4 4 4 4 4 4 4 3 3 3 3 3 3 3 3
 *   3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2
 *   <--------------------- offset ----------------------> < type ->
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   <------------------- zewoes --------------------> E 0 0 0 0 0 0
 */
#define __swp_type(x)			((x).vaw & 0x1f)
#define __swp_offset(x)			((x).vaw >> 5)
#define __swp_entwy(type, offset)	((swp_entwy_t){ ((type) & 0x1f) | (offset) << 5})
#define __pte_to_swp_entwy(pte)		((swp_entwy_t){ (pte).pte_high })
#define __swp_entwy_to_pte(x)		((pte_t){ 0, (x).vaw })

#ewse
/*
 * Fowmat of swap PTEs:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   <--------------- offset ----------------> 0 0 0 0 E < type -> 0
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define __swp_type(x)			((x).vaw & 0x1f)
#define __swp_offset(x)			((x).vaw >> 10)
#define __swp_entwy(type, offset)	((swp_entwy_t){((type) & 0x1f) | (offset) << 10})

#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw(pte) >> 1 })
#define __swp_entwy_to_pte(x)		((pte_t) { (x).vaw << 1 })
#endif

/* In both cases, we bowwow bit 6 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_USEW

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte.pte_wow & _PAGE_SWP_EXCWUSIVE;
}

PTE_BIT_FUNC(wow, swp_mkexcwusive, |= _PAGE_SWP_EXCWUSIVE);
PTE_BIT_FUNC(wow, swp_cweaw_excwusive, &= ~_PAGE_SWP_EXCWUSIVE);

#endif /* __ASSEMBWY__ */
#endif /* __ASM_SH_PGTABWE_32_H */
