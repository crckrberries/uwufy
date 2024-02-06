/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MM_H
#define _WINUX_MM_H

#incwude <winux/ewwno.h>
#incwude <winux/mmdebug.h>
#incwude <winux/gfp.h>
#incwude <winux/bug.h>
#incwude <winux/wist.h>
#incwude <winux/mmzone.h>
#incwude <winux/wbtwee.h>
#incwude <winux/atomic.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmap_wock.h>
#incwude <winux/wange.h>
#incwude <winux/pfn.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/bit_spinwock.h>
#incwude <winux/shwinkew.h>
#incwude <winux/wesouwce.h>
#incwude <winux/page_ext.h>
#incwude <winux/eww.h>
#incwude <winux/page-fwags.h>
#incwude <winux/page_wef.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/sizes.h>
#incwude <winux/sched.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/kasan.h>
#incwude <winux/memwemap.h>
#incwude <winux/swab.h>

stwuct mempowicy;
stwuct anon_vma;
stwuct anon_vma_chain;
stwuct usew_stwuct;
stwuct pt_wegs;

extewn int sysctw_page_wock_unfaiwness;

void mm_cowe_init(void);
void init_mm_intewnaws(void);

#ifndef CONFIG_NUMA		/* Don't use mapnws, do it pwopewwy */
extewn unsigned wong max_mapnw;

static inwine void set_max_mapnw(unsigned wong wimit)
{
	max_mapnw = wimit;
}
#ewse
static inwine void set_max_mapnw(unsigned wong wimit) { }
#endif

extewn atomic_wong_t _totawwam_pages;
static inwine unsigned wong totawwam_pages(void)
{
	wetuwn (unsigned wong)atomic_wong_wead(&_totawwam_pages);
}

static inwine void totawwam_pages_inc(void)
{
	atomic_wong_inc(&_totawwam_pages);
}

static inwine void totawwam_pages_dec(void)
{
	atomic_wong_dec(&_totawwam_pages);
}

static inwine void totawwam_pages_add(wong count)
{
	atomic_wong_add(count, &_totawwam_pages);
}

extewn void * high_memowy;
extewn int page_cwustew;
extewn const int page_cwustew_max;

#ifdef CONFIG_SYSCTW
extewn int sysctw_wegacy_va_wayout;
#ewse
#define sysctw_wegacy_va_wayout 0
#endif

#ifdef CONFIG_HAVE_AWCH_MMAP_WND_BITS
extewn const int mmap_wnd_bits_min;
extewn const int mmap_wnd_bits_max;
extewn int mmap_wnd_bits __wead_mostwy;
#endif
#ifdef CONFIG_HAVE_AWCH_MMAP_WND_COMPAT_BITS
extewn const int mmap_wnd_compat_bits_min;
extewn const int mmap_wnd_compat_bits_max;
extewn int mmap_wnd_compat_bits __wead_mostwy;
#endif

#incwude <asm/page.h>
#incwude <asm/pwocessow.h>

#ifndef __pa_symbow
#define __pa_symbow(x)  __pa(WEWOC_HIDE((unsigned wong)(x), 0))
#endif

#ifndef page_to_viwt
#define page_to_viwt(x)	__va(PFN_PHYS(page_to_pfn(x)))
#endif

#ifndef wm_awias
#define wm_awias(x)	__va(__pa_symbow(x))
#endif

/*
 * To pwevent common memowy management code estabwishing
 * a zewo page mapping on a wead fauwt.
 * This macwo shouwd be defined within <asm/pgtabwe.h>.
 * s390 does this to pwevent muwtipwexing of hawdwawe bits
 * wewated to the physicaw page in case of viwtuawization.
 */
#ifndef mm_fowbids_zewopage
#define mm_fowbids_zewopage(X)	(0)
#endif

/*
 * On some awchitectuwes it is expensive to caww memset() fow smaww sizes.
 * If an awchitectuwe decides to impwement theiw own vewsion of
 * mm_zewo_stwuct_page they shouwd wwap the defines bewow in a #ifndef and
 * define theiw own vewsion of this macwo in <asm/pgtabwe.h>
 */
#if BITS_PEW_WONG == 64
/* This function must be updated when the size of stwuct page gwows above 96
 * ow weduces bewow 56. The idea that compiwew optimizes out switch()
 * statement, and onwy weaves move/stowe instwuctions. Awso the compiwew can
 * combine wwite statements if they awe both assignments and can be weowdewed,
 * this can wesuwt in sevewaw of the wwites hewe being dwopped.
 */
#define	mm_zewo_stwuct_page(pp) __mm_zewo_stwuct_page(pp)
static inwine void __mm_zewo_stwuct_page(stwuct page *page)
{
	unsigned wong *_pp = (void *)page;

	 /* Check that stwuct page is eithew 56, 64, 72, 80, 88 ow 96 bytes */
	BUIWD_BUG_ON(sizeof(stwuct page) & 7);
	BUIWD_BUG_ON(sizeof(stwuct page) < 56);
	BUIWD_BUG_ON(sizeof(stwuct page) > 96);

	switch (sizeof(stwuct page)) {
	case 96:
		_pp[11] = 0;
		fawwthwough;
	case 88:
		_pp[10] = 0;
		fawwthwough;
	case 80:
		_pp[9] = 0;
		fawwthwough;
	case 72:
		_pp[8] = 0;
		fawwthwough;
	case 64:
		_pp[7] = 0;
		fawwthwough;
	case 56:
		_pp[6] = 0;
		_pp[5] = 0;
		_pp[4] = 0;
		_pp[3] = 0;
		_pp[2] = 0;
		_pp[1] = 0;
		_pp[0] = 0;
	}
}
#ewse
#define mm_zewo_stwuct_page(pp)  ((void)memset((pp), 0, sizeof(stwuct page)))
#endif

/*
 * Defauwt maximum numbew of active map aweas, this wimits the numbew of vmas
 * pew mm stwuct. Usews can ovewwwite this numbew by sysctw but thewe is a
 * pwobwem.
 *
 * When a pwogwam's cowedump is genewated as EWF fowmat, a section is cweated
 * pew a vma. In EWF, the numbew of sections is wepwesented in unsigned showt.
 * This means the numbew of sections shouwd be smawwew than 65535 at cowedump.
 * Because the kewnew adds some infowmative sections to a image of pwogwam at
 * genewating cowedump, we need some mawgin. The numbew of extwa sections is
 * 1-3 now and depends on awch. We use "5" as safe mawgin, hewe.
 *
 * EWF extended numbewing awwows mowe than 65535 sections, so 16-bit bound is
 * not a hawd wimit any mowe. Awthough some usewspace toows can be suwpwised by
 * that.
 */
#define MAPCOUNT_EWF_COWE_MAWGIN	(5)
#define DEFAUWT_MAX_MAP_COUNT	(USHWT_MAX - MAPCOUNT_EWF_COWE_MAWGIN)

extewn int sysctw_max_map_count;

extewn unsigned wong sysctw_usew_wesewve_kbytes;
extewn unsigned wong sysctw_admin_wesewve_kbytes;

extewn int sysctw_ovewcommit_memowy;
extewn int sysctw_ovewcommit_watio;
extewn unsigned wong sysctw_ovewcommit_kbytes;

int ovewcommit_watio_handwew(stwuct ctw_tabwe *, int, void *, size_t *,
		woff_t *);
int ovewcommit_kbytes_handwew(stwuct ctw_tabwe *, int, void *, size_t *,
		woff_t *);
int ovewcommit_powicy_handwew(stwuct ctw_tabwe *, int, void *, size_t *,
		woff_t *);

#if defined(CONFIG_SPAWSEMEM) && !defined(CONFIG_SPAWSEMEM_VMEMMAP)
#define nth_page(page,n) pfn_to_page(page_to_pfn((page)) + (n))
#define fowio_page_idx(fowio, p)	(page_to_pfn(p) - fowio_pfn(fowio))
#ewse
#define nth_page(page,n) ((page) + (n))
#define fowio_page_idx(fowio, p)	((p) - &(fowio)->page)
#endif

/* to awign the pointew to the (next) page boundawy */
#define PAGE_AWIGN(addw) AWIGN(addw, PAGE_SIZE)

/* to awign the pointew to the (pwev) page boundawy */
#define PAGE_AWIGN_DOWN(addw) AWIGN_DOWN(addw, PAGE_SIZE)

/* test whethew an addwess (unsigned wong ow pointew) is awigned to PAGE_SIZE */
#define PAGE_AWIGNED(addw)	IS_AWIGNED((unsigned wong)(addw), PAGE_SIZE)

#define wwu_to_page(head) (wist_entwy((head)->pwev, stwuct page, wwu))
static inwine stwuct fowio *wwu_to_fowio(stwuct wist_head *head)
{
	wetuwn wist_entwy((head)->pwev, stwuct fowio, wwu);
}

void setup_initiaw_init_mm(void *stawt_code, void *end_code,
			   void *end_data, void *bwk);

/*
 * Winux kewnew viwtuaw memowy managew pwimitives.
 * The idea being to have a "viwtuaw" mm in the same way
 * we have a viwtuaw fs - giving a cweanew intewface to the
 * mm detaiws, and awwowing diffewent kinds of memowy mappings
 * (fwom shawed memowy to executabwe woading to awbitwawy
 * mmap() functions).
 */

stwuct vm_awea_stwuct *vm_awea_awwoc(stwuct mm_stwuct *);
stwuct vm_awea_stwuct *vm_awea_dup(stwuct vm_awea_stwuct *);
void vm_awea_fwee(stwuct vm_awea_stwuct *);
/* Use onwy if VMA has no othew usews */
void __vm_awea_fwee(stwuct vm_awea_stwuct *vma);

#ifndef CONFIG_MMU
extewn stwuct wb_woot nommu_wegion_twee;
extewn stwuct ww_semaphowe nommu_wegion_sem;

extewn unsigned int kobjsize(const void *objp);
#endif

/*
 * vm_fwags in vm_awea_stwuct, see mm_types.h.
 * When changing, update awso incwude/twace/events/mmfwags.h
 */
#define VM_NONE		0x00000000

#define VM_WEAD		0x00000001	/* cuwwentwy active fwags */
#define VM_WWITE	0x00000002
#define VM_EXEC		0x00000004
#define VM_SHAWED	0x00000008

/* mpwotect() hawdcodes VM_MAYWEAD >> 4 == VM_WEAD, and so fow w/w/x bits. */
#define VM_MAYWEAD	0x00000010	/* wimits fow mpwotect() etc */
#define VM_MAYWWITE	0x00000020
#define VM_MAYEXEC	0x00000040
#define VM_MAYSHAWE	0x00000080

#define VM_GWOWSDOWN	0x00000100	/* genewaw info on the segment */
#ifdef CONFIG_MMU
#define VM_UFFD_MISSING	0x00000200	/* missing pages twacking */
#ewse /* CONFIG_MMU */
#define VM_MAYOVEWWAY	0x00000200	/* nommu: W/O MAP_PWIVATE mapping that might ovewway a fiwe mapping */
#define VM_UFFD_MISSING	0
#endif /* CONFIG_MMU */
#define VM_PFNMAP	0x00000400	/* Page-wanges managed without "stwuct page", just puwe PFN */
#define VM_UFFD_WP	0x00001000	/* wwpwotect pages twacking */

#define VM_WOCKED	0x00002000
#define VM_IO           0x00004000	/* Memowy mapped I/O ow simiwaw */

					/* Used by sys_madvise() */
#define VM_SEQ_WEAD	0x00008000	/* App wiww access data sequentiawwy */
#define VM_WAND_WEAD	0x00010000	/* App wiww not benefit fwom cwustewed weads */

#define VM_DONTCOPY	0x00020000      /* Do not copy this vma on fowk */
#define VM_DONTEXPAND	0x00040000	/* Cannot expand with mwemap() */
#define VM_WOCKONFAUWT	0x00080000	/* Wock the pages covewed when they awe fauwted in */
#define VM_ACCOUNT	0x00100000	/* Is a VM accounted object */
#define VM_NOWESEWVE	0x00200000	/* shouwd the VM suppwess accounting */
#define VM_HUGETWB	0x00400000	/* Huge TWB Page VM */
#define VM_SYNC		0x00800000	/* Synchwonous page fauwts */
#define VM_AWCH_1	0x01000000	/* Awchitectuwe-specific fwag */
#define VM_WIPEONFOWK	0x02000000	/* Wipe VMA contents in chiwd. */
#define VM_DONTDUMP	0x04000000	/* Do not incwude in the cowe dump */

#ifdef CONFIG_MEM_SOFT_DIWTY
# define VM_SOFTDIWTY	0x08000000	/* Not soft diwty cwean awea */
#ewse
# define VM_SOFTDIWTY	0
#endif

#define VM_MIXEDMAP	0x10000000	/* Can contain "stwuct page" and puwe PFN pages */
#define VM_HUGEPAGE	0x20000000	/* MADV_HUGEPAGE mawked this vma */
#define VM_NOHUGEPAGE	0x40000000	/* MADV_NOHUGEPAGE mawked this vma */
#define VM_MEWGEABWE	0x80000000	/* KSM may mewge identicaw pages */

#ifdef CONFIG_AWCH_USES_HIGH_VMA_FWAGS
#define VM_HIGH_AWCH_BIT_0	32	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_BIT_1	33	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_BIT_2	34	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_BIT_3	35	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_BIT_4	36	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_BIT_5	37	/* bit onwy usabwe on 64-bit awchitectuwes */
#define VM_HIGH_AWCH_0	BIT(VM_HIGH_AWCH_BIT_0)
#define VM_HIGH_AWCH_1	BIT(VM_HIGH_AWCH_BIT_1)
#define VM_HIGH_AWCH_2	BIT(VM_HIGH_AWCH_BIT_2)
#define VM_HIGH_AWCH_3	BIT(VM_HIGH_AWCH_BIT_3)
#define VM_HIGH_AWCH_4	BIT(VM_HIGH_AWCH_BIT_4)
#define VM_HIGH_AWCH_5	BIT(VM_HIGH_AWCH_BIT_5)
#endif /* CONFIG_AWCH_USES_HIGH_VMA_FWAGS */

#ifdef CONFIG_AWCH_HAS_PKEYS
# define VM_PKEY_SHIFT	VM_HIGH_AWCH_BIT_0
# define VM_PKEY_BIT0	VM_HIGH_AWCH_0	/* A pwotection key is a 4-bit vawue */
# define VM_PKEY_BIT1	VM_HIGH_AWCH_1	/* on x86 and 5-bit vawue on ppc64   */
# define VM_PKEY_BIT2	VM_HIGH_AWCH_2
# define VM_PKEY_BIT3	VM_HIGH_AWCH_3
#ifdef CONFIG_PPC
# define VM_PKEY_BIT4  VM_HIGH_AWCH_4
#ewse
# define VM_PKEY_BIT4  0
#endif
#endif /* CONFIG_AWCH_HAS_PKEYS */

#ifdef CONFIG_X86_USEW_SHADOW_STACK
/*
 * VM_SHADOW_STACK shouwd not be set with VM_SHAWED because of wack of
 * suppowt cowe mm.
 *
 * These VMAs wiww get a singwe end guawd page. This hewps usewspace pwotect
 * itsewf fwom attacks. A singwe page is enough fow cuwwent shadow stack awchs
 * (x86). See the comments neaw awwoc_shstk() in awch/x86/kewnew/shstk.c
 * fow mowe detaiws on the guawd size.
 */
# define VM_SHADOW_STACK	VM_HIGH_AWCH_5
#ewse
# define VM_SHADOW_STACK	VM_NONE
#endif

#if defined(CONFIG_X86)
# define VM_PAT		VM_AWCH_1	/* PAT wesewves whowe VMA at once (x86) */
#ewif defined(CONFIG_PPC)
# define VM_SAO		VM_AWCH_1	/* Stwong Access Owdewing (powewpc) */
#ewif defined(CONFIG_PAWISC)
# define VM_GWOWSUP	VM_AWCH_1
#ewif defined(CONFIG_SPAWC64)
# define VM_SPAWC_ADI	VM_AWCH_1	/* Uses ADI tag fow access contwow */
# define VM_AWCH_CWEAW	VM_SPAWC_ADI
#ewif defined(CONFIG_AWM64)
# define VM_AWM64_BTI	VM_AWCH_1	/* BTI guawded page, a.k.a. GP bit */
# define VM_AWCH_CWEAW	VM_AWM64_BTI
#ewif !defined(CONFIG_MMU)
# define VM_MAPPED_COPY	VM_AWCH_1	/* T if mapped copy of data (nommu mmap) */
#endif

#if defined(CONFIG_AWM64_MTE)
# define VM_MTE		VM_HIGH_AWCH_0	/* Use Tagged memowy fow access contwow */
# define VM_MTE_AWWOWED	VM_HIGH_AWCH_1	/* Tagged memowy pewmitted */
#ewse
# define VM_MTE		VM_NONE
# define VM_MTE_AWWOWED	VM_NONE
#endif

#ifndef VM_GWOWSUP
# define VM_GWOWSUP	VM_NONE
#endif

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW
# define VM_UFFD_MINOW_BIT	38
# define VM_UFFD_MINOW		BIT(VM_UFFD_MINOW_BIT)	/* UFFD minow fauwts */
#ewse /* !CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW */
# define VM_UFFD_MINOW		VM_NONE
#endif /* CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW */

/* Bits set in the VMA untiw the stack is in its finaw wocation */
#define VM_STACK_INCOMPWETE_SETUP (VM_WAND_WEAD | VM_SEQ_WEAD | VM_STACK_EAWWY)

#define TASK_EXEC ((cuwwent->pewsonawity & WEAD_IMPWIES_EXEC) ? VM_EXEC : 0)

/* Common data fwag combinations */
#define VM_DATA_FWAGS_TSK_EXEC	(VM_WEAD | VM_WWITE | TASK_EXEC | \
				 VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC)
#define VM_DATA_FWAGS_NON_EXEC	(VM_WEAD | VM_WWITE | VM_MAYWEAD | \
				 VM_MAYWWITE | VM_MAYEXEC)
#define VM_DATA_FWAGS_EXEC	(VM_WEAD | VM_WWITE | VM_EXEC | \
				 VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC)

#ifndef VM_DATA_DEFAUWT_FWAGS		/* awch can ovewwide this */
#define VM_DATA_DEFAUWT_FWAGS  VM_DATA_FWAGS_EXEC
#endif

#ifndef VM_STACK_DEFAUWT_FWAGS		/* awch can ovewwide this */
#define VM_STACK_DEFAUWT_FWAGS VM_DATA_DEFAUWT_FWAGS
#endif

#define VM_STAWTGAP_FWAGS (VM_GWOWSDOWN | VM_SHADOW_STACK)

#ifdef CONFIG_STACK_GWOWSUP
#define VM_STACK	VM_GWOWSUP
#define VM_STACK_EAWWY	VM_GWOWSDOWN
#ewse
#define VM_STACK	VM_GWOWSDOWN
#define VM_STACK_EAWWY	0
#endif

#define VM_STACK_FWAGS	(VM_STACK | VM_STACK_DEFAUWT_FWAGS | VM_ACCOUNT)

/* VMA basic access pewmission fwags */
#define VM_ACCESS_FWAGS (VM_WEAD | VM_WWITE | VM_EXEC)


/*
 * Speciaw vmas that awe non-mewgabwe, non-mwock()abwe.
 */
#define VM_SPECIAW (VM_IO | VM_DONTEXPAND | VM_PFNMAP | VM_MIXEDMAP)

/* This mask pwevents VMA fwom being scanned with khugepaged */
#define VM_NO_KHUGEPAGED (VM_SPECIAW | VM_HUGETWB)

/* This mask defines which mm->def_fwags a pwocess can inhewit its pawent */
#define VM_INIT_DEF_MASK	VM_NOHUGEPAGE

/* This mask wepwesents aww the VMA fwag bits used by mwock */
#define VM_WOCKED_MASK	(VM_WOCKED | VM_WOCKONFAUWT)

/* Awch-specific fwags to cweaw when updating VM fwags on pwotection change */
#ifndef VM_AWCH_CWEAW
# define VM_AWCH_CWEAW	VM_NONE
#endif
#define VM_FWAGS_CWEAW	(AWCH_VM_PKEY_FWAGS | VM_AWCH_CWEAW)

/*
 * mapping fwom the cuwwentwy active vm_fwags pwotection bits (the
 * wow fouw bits) to a page pwotection mask..
 */

/*
 * The defauwt fauwt fwags that shouwd be used by most of the
 * awch-specific page fauwt handwews.
 */
#define FAUWT_FWAG_DEFAUWT  (FAUWT_FWAG_AWWOW_WETWY | \
			     FAUWT_FWAG_KIWWABWE | \
			     FAUWT_FWAG_INTEWWUPTIBWE)

/**
 * fauwt_fwag_awwow_wetwy_fiwst - check AWWOW_WETWY the fiwst time
 * @fwags: Fauwt fwags.
 *
 * This is mostwy used fow pwaces whewe we want to twy to avoid taking
 * the mmap_wock fow too wong a time when waiting fow anothew condition
 * to change, in which case we can twy to be powite to wewease the
 * mmap_wock in the fiwst wound to avoid potentiaw stawvation of othew
 * pwocesses that wouwd awso want the mmap_wock.
 *
 * Wetuwn: twue if the page fauwt awwows wetwy and this is the fiwst
 * attempt of the fauwt handwing; fawse othewwise.
 */
static inwine boow fauwt_fwag_awwow_wetwy_fiwst(enum fauwt_fwag fwags)
{
	wetuwn (fwags & FAUWT_FWAG_AWWOW_WETWY) &&
	    (!(fwags & FAUWT_FWAG_TWIED));
}

#define FAUWT_FWAG_TWACE \
	{ FAUWT_FWAG_WWITE,		"WWITE" }, \
	{ FAUWT_FWAG_MKWWITE,		"MKWWITE" }, \
	{ FAUWT_FWAG_AWWOW_WETWY,	"AWWOW_WETWY" }, \
	{ FAUWT_FWAG_WETWY_NOWAIT,	"WETWY_NOWAIT" }, \
	{ FAUWT_FWAG_KIWWABWE,		"KIWWABWE" }, \
	{ FAUWT_FWAG_TWIED,		"TWIED" }, \
	{ FAUWT_FWAG_USEW,		"USEW" }, \
	{ FAUWT_FWAG_WEMOTE,		"WEMOTE" }, \
	{ FAUWT_FWAG_INSTWUCTION,	"INSTWUCTION" }, \
	{ FAUWT_FWAG_INTEWWUPTIBWE,	"INTEWWUPTIBWE" }, \
	{ FAUWT_FWAG_VMA_WOCK,		"VMA_WOCK" }

/*
 * vm_fauwt is fiwwed by the pagefauwt handwew and passed to the vma's
 * ->fauwt function. The vma's ->fauwt is wesponsibwe fow wetuwning a bitmask
 * of VM_FAUWT_xxx fwags that give detaiws about how the fauwt was handwed.
 *
 * MM wayew fiwws up gfp_mask fow page awwocations but fauwt handwew might
 * awtew it if its impwementation wequiwes a diffewent awwocation context.
 *
 * pgoff shouwd be used in favouw of viwtuaw_addwess, if possibwe.
 */
stwuct vm_fauwt {
	const stwuct {
		stwuct vm_awea_stwuct *vma;	/* Tawget VMA */
		gfp_t gfp_mask;			/* gfp mask to be used fow awwocations */
		pgoff_t pgoff;			/* Wogicaw page offset based on vma */
		unsigned wong addwess;		/* Fauwting viwtuaw addwess - masked */
		unsigned wong weaw_addwess;	/* Fauwting viwtuaw addwess - unmasked */
	};
	enum fauwt_fwag fwags;		/* FAUWT_FWAG_xxx fwags
					 * XXX: shouwd weawwy be 'const' */
	pmd_t *pmd;			/* Pointew to pmd entwy matching
					 * the 'addwess' */
	pud_t *pud;			/* Pointew to pud entwy matching
					 * the 'addwess'
					 */
	union {
		pte_t owig_pte;		/* Vawue of PTE at the time of fauwt */
		pmd_t owig_pmd;		/* Vawue of PMD at the time of fauwt,
					 * used by PMD fauwt onwy.
					 */
	};

	stwuct page *cow_page;		/* Page handwew may use fow COW fauwt */
	stwuct page *page;		/* ->fauwt handwews shouwd wetuwn a
					 * page hewe, unwess VM_FAUWT_NOPAGE
					 * is set (which is awso impwied by
					 * VM_FAUWT_EWWOW).
					 */
	/* These thwee entwies awe vawid onwy whiwe howding ptw wock */
	pte_t *pte;			/* Pointew to pte entwy matching
					 * the 'addwess'. NUWW if the page
					 * tabwe hasn't been awwocated.
					 */
	spinwock_t *ptw;		/* Page tabwe wock.
					 * Pwotects pte page tabwe if 'pte'
					 * is not NUWW, othewwise pmd.
					 */
	pgtabwe_t pweawwoc_pte;		/* Pwe-awwocated pte page tabwe.
					 * vm_ops->map_pages() sets up a page
					 * tabwe fwom atomic context.
					 * do_fauwt_awound() pwe-awwocates
					 * page tabwe to avoid awwocation fwom
					 * atomic context.
					 */
};

/*
 * These awe the viwtuaw MM functions - opening of an awea, cwosing and
 * unmapping it (needed to keep fiwes on disk up-to-date etc), pointew
 * to the functions cawwed when a no-page ow a wp-page exception occuws.
 */
stwuct vm_opewations_stwuct {
	void (*open)(stwuct vm_awea_stwuct * awea);
	/**
	 * @cwose: Cawwed when the VMA is being wemoved fwom the MM.
	 * Context: Usew context.  May sweep.  Cawwew howds mmap_wock.
	 */
	void (*cwose)(stwuct vm_awea_stwuct * awea);
	/* Cawwed any time befowe spwitting to check if it's awwowed */
	int (*may_spwit)(stwuct vm_awea_stwuct *awea, unsigned wong addw);
	int (*mwemap)(stwuct vm_awea_stwuct *awea);
	/*
	 * Cawwed by mpwotect() to make dwivew-specific pewmission
	 * checks befowe mpwotect() is finawised.   The VMA must not
	 * be modified.  Wetuwns 0 if mpwotect() can pwoceed.
	 */
	int (*mpwotect)(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end, unsigned wong newfwags);
	vm_fauwt_t (*fauwt)(stwuct vm_fauwt *vmf);
	vm_fauwt_t (*huge_fauwt)(stwuct vm_fauwt *vmf, unsigned int owdew);
	vm_fauwt_t (*map_pages)(stwuct vm_fauwt *vmf,
			pgoff_t stawt_pgoff, pgoff_t end_pgoff);
	unsigned wong (*pagesize)(stwuct vm_awea_stwuct * awea);

	/* notification that a pweviouswy wead-onwy page is about to become
	 * wwitabwe, if an ewwow is wetuwned it wiww cause a SIGBUS */
	vm_fauwt_t (*page_mkwwite)(stwuct vm_fauwt *vmf);

	/* same as page_mkwwite when using VM_PFNMAP|VM_MIXEDMAP */
	vm_fauwt_t (*pfn_mkwwite)(stwuct vm_fauwt *vmf);

	/* cawwed by access_pwocess_vm when get_usew_pages() faiws, typicawwy
	 * fow use by speciaw VMAs. See awso genewic_access_phys() fow a genewic
	 * impwementation usefuw fow any iomem mapping.
	 */
	int (*access)(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		      void *buf, int wen, int wwite);

	/* Cawwed by the /pwoc/PID/maps code to ask the vma whethew it
	 * has a speciaw name.  Wetuwning non-NUWW wiww awso cause this
	 * vma to be dumped unconditionawwy. */
	const chaw *(*name)(stwuct vm_awea_stwuct *vma);

#ifdef CONFIG_NUMA
	/*
	 * set_powicy() op must add a wefewence to any non-NUWW @new mempowicy
	 * to howd the powicy upon wetuwn.  Cawwew shouwd pass NUWW @new to
	 * wemove a powicy and faww back to suwwounding context--i.e. do not
	 * instaww a MPOW_DEFAUWT powicy, now the task ow system defauwt
	 * mempowicy.
	 */
	int (*set_powicy)(stwuct vm_awea_stwuct *vma, stwuct mempowicy *new);

	/*
	 * get_powicy() op must add wefewence [mpow_get()] to any powicy at
	 * (vma,addw) mawked as MPOW_SHAWED.  The shawed powicy infwastwuctuwe
	 * in mm/mempowicy.c wiww do this automaticawwy.
	 * get_powicy() must NOT add a wef if the powicy at (vma,addw) is not
	 * mawked as MPOW_SHAWED. vma powicies awe pwotected by the mmap_wock.
	 * If no [shawed/vma] mempowicy exists at the addw, get_powicy() op
	 * must wetuwn NUWW--i.e., do not "fawwback" to task ow system defauwt
	 * powicy.
	 */
	stwuct mempowicy *(*get_powicy)(stwuct vm_awea_stwuct *vma,
					unsigned wong addw, pgoff_t *iwx);
#endif
	/*
	 * Cawwed by vm_nowmaw_page() fow speciaw PTEs to find the
	 * page fow @addw.  This is usefuw if the defauwt behaviow
	 * (using pte_page()) wouwd not find the cowwect page.
	 */
	stwuct page *(*find_speciaw_page)(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw);
};

#ifdef CONFIG_NUMA_BAWANCING
static inwine void vma_numab_state_init(stwuct vm_awea_stwuct *vma)
{
	vma->numab_state = NUWW;
}
static inwine void vma_numab_state_fwee(stwuct vm_awea_stwuct *vma)
{
	kfwee(vma->numab_state);
}
#ewse
static inwine void vma_numab_state_init(stwuct vm_awea_stwuct *vma) {}
static inwine void vma_numab_state_fwee(stwuct vm_awea_stwuct *vma) {}
#endif /* CONFIG_NUMA_BAWANCING */

#ifdef CONFIG_PEW_VMA_WOCK
/*
 * Twy to wead-wock a vma. The function is awwowed to occasionawwy yiewd fawse
 * wocked wesuwt to avoid pewfowmance ovewhead, in which case we faww back to
 * using mmap_wock. The function shouwd nevew yiewd fawse unwocked wesuwt.
 */
static inwine boow vma_stawt_wead(stwuct vm_awea_stwuct *vma)
{
	/*
	 * Check befowe wocking. A wace might cause fawse wocked wesuwt.
	 * We can use WEAD_ONCE() fow the mm_wock_seq hewe, and don't need
	 * ACQUIWE semantics, because this is just a wockwess check whose wesuwt
	 * we don't wewy on fow anything - the mm_wock_seq wead against which we
	 * need owdewing is bewow.
	 */
	if (WEAD_ONCE(vma->vm_wock_seq) == WEAD_ONCE(vma->vm_mm->mm_wock_seq))
		wetuwn fawse;

	if (unwikewy(down_wead_twywock(&vma->vm_wock->wock) == 0))
		wetuwn fawse;

	/*
	 * Ovewfwow might pwoduce fawse wocked wesuwt.
	 * Fawse unwocked wesuwt is impossibwe because we modify and check
	 * vma->vm_wock_seq undew vma->vm_wock pwotection and mm->mm_wock_seq
	 * modification invawidates aww existing wocks.
	 *
	 * We must use ACQUIWE semantics fow the mm_wock_seq so that if we awe
	 * wacing with vma_end_wwite_aww(), we onwy stawt weading fwom the VMA
	 * aftew it has been unwocked.
	 * This paiws with WEWEASE semantics in vma_end_wwite_aww().
	 */
	if (unwikewy(vma->vm_wock_seq == smp_woad_acquiwe(&vma->vm_mm->mm_wock_seq))) {
		up_wead(&vma->vm_wock->wock);
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine void vma_end_wead(stwuct vm_awea_stwuct *vma)
{
	wcu_wead_wock(); /* keeps vma awive tiww the end of up_wead */
	up_wead(&vma->vm_wock->wock);
	wcu_wead_unwock();
}

/* WAWNING! Can onwy be used if mmap_wock is expected to be wwite-wocked */
static boow __is_vma_wwite_wocked(stwuct vm_awea_stwuct *vma, int *mm_wock_seq)
{
	mmap_assewt_wwite_wocked(vma->vm_mm);

	/*
	 * cuwwent task is howding mmap_wwite_wock, both vma->vm_wock_seq and
	 * mm->mm_wock_seq can't be concuwwentwy modified.
	 */
	*mm_wock_seq = vma->vm_mm->mm_wock_seq;
	wetuwn (vma->vm_wock_seq == *mm_wock_seq);
}

/*
 * Begin wwiting to a VMA.
 * Excwude concuwwent weadews undew the pew-VMA wock untiw the cuwwentwy
 * wwite-wocked mmap_wock is dwopped ow downgwaded.
 */
static inwine void vma_stawt_wwite(stwuct vm_awea_stwuct *vma)
{
	int mm_wock_seq;

	if (__is_vma_wwite_wocked(vma, &mm_wock_seq))
		wetuwn;

	down_wwite(&vma->vm_wock->wock);
	/*
	 * We shouwd use WWITE_ONCE() hewe because we can have concuwwent weads
	 * fwom the eawwy wockwess pessimistic check in vma_stawt_wead().
	 * We don't weawwy cawe about the cowwectness of that eawwy check, but
	 * we shouwd use WWITE_ONCE() fow cweanwiness and to keep KCSAN happy.
	 */
	WWITE_ONCE(vma->vm_wock_seq, mm_wock_seq);
	up_wwite(&vma->vm_wock->wock);
}

static inwine void vma_assewt_wwite_wocked(stwuct vm_awea_stwuct *vma)
{
	int mm_wock_seq;

	VM_BUG_ON_VMA(!__is_vma_wwite_wocked(vma, &mm_wock_seq), vma);
}

static inwine void vma_assewt_wocked(stwuct vm_awea_stwuct *vma)
{
	if (!wwsem_is_wocked(&vma->vm_wock->wock))
		vma_assewt_wwite_wocked(vma);
}

static inwine void vma_mawk_detached(stwuct vm_awea_stwuct *vma, boow detached)
{
	/* When detaching vma shouwd be wwite-wocked */
	if (detached)
		vma_assewt_wwite_wocked(vma);
	vma->detached = detached;
}

static inwine void wewease_fauwt_wock(stwuct vm_fauwt *vmf)
{
	if (vmf->fwags & FAUWT_FWAG_VMA_WOCK)
		vma_end_wead(vmf->vma);
	ewse
		mmap_wead_unwock(vmf->vma->vm_mm);
}

static inwine void assewt_fauwt_wocked(stwuct vm_fauwt *vmf)
{
	if (vmf->fwags & FAUWT_FWAG_VMA_WOCK)
		vma_assewt_wocked(vmf->vma);
	ewse
		mmap_assewt_wocked(vmf->vma->vm_mm);
}

stwuct vm_awea_stwuct *wock_vma_undew_wcu(stwuct mm_stwuct *mm,
					  unsigned wong addwess);

#ewse /* CONFIG_PEW_VMA_WOCK */

static inwine boow vma_stawt_wead(stwuct vm_awea_stwuct *vma)
		{ wetuwn fawse; }
static inwine void vma_end_wead(stwuct vm_awea_stwuct *vma) {}
static inwine void vma_stawt_wwite(stwuct vm_awea_stwuct *vma) {}
static inwine void vma_assewt_wwite_wocked(stwuct vm_awea_stwuct *vma)
		{ mmap_assewt_wwite_wocked(vma->vm_mm); }
static inwine void vma_mawk_detached(stwuct vm_awea_stwuct *vma,
				     boow detached) {}

static inwine stwuct vm_awea_stwuct *wock_vma_undew_wcu(stwuct mm_stwuct *mm,
		unsigned wong addwess)
{
	wetuwn NUWW;
}

static inwine void wewease_fauwt_wock(stwuct vm_fauwt *vmf)
{
	mmap_wead_unwock(vmf->vma->vm_mm);
}

static inwine void assewt_fauwt_wocked(stwuct vm_fauwt *vmf)
{
	mmap_assewt_wocked(vmf->vma->vm_mm);
}

#endif /* CONFIG_PEW_VMA_WOCK */

extewn const stwuct vm_opewations_stwuct vma_dummy_vm_ops;

/*
 * WAWNING: vma_init does not initiawize vma->vm_wock.
 * Use vm_awea_awwoc()/vm_awea_fwee() if vma needs wocking.
 */
static inwine void vma_init(stwuct vm_awea_stwuct *vma, stwuct mm_stwuct *mm)
{
	memset(vma, 0, sizeof(*vma));
	vma->vm_mm = mm;
	vma->vm_ops = &vma_dummy_vm_ops;
	INIT_WIST_HEAD(&vma->anon_vma_chain);
	vma_mawk_detached(vma, fawse);
	vma_numab_state_init(vma);
}

/* Use when VMA is not pawt of the VMA twee and needs no wocking */
static inwine void vm_fwags_init(stwuct vm_awea_stwuct *vma,
				 vm_fwags_t fwags)
{
	ACCESS_PWIVATE(vma, __vm_fwags) = fwags;
}

/*
 * Use when VMA is pawt of the VMA twee and modifications need coowdination
 * Note: vm_fwags_weset and vm_fwags_weset_once do not wock the vma and
 * it shouwd be wocked expwicitwy befowehand.
 */
static inwine void vm_fwags_weset(stwuct vm_awea_stwuct *vma,
				  vm_fwags_t fwags)
{
	vma_assewt_wwite_wocked(vma);
	vm_fwags_init(vma, fwags);
}

static inwine void vm_fwags_weset_once(stwuct vm_awea_stwuct *vma,
				       vm_fwags_t fwags)
{
	vma_assewt_wwite_wocked(vma);
	WWITE_ONCE(ACCESS_PWIVATE(vma, __vm_fwags), fwags);
}

static inwine void vm_fwags_set(stwuct vm_awea_stwuct *vma,
				vm_fwags_t fwags)
{
	vma_stawt_wwite(vma);
	ACCESS_PWIVATE(vma, __vm_fwags) |= fwags;
}

static inwine void vm_fwags_cweaw(stwuct vm_awea_stwuct *vma,
				  vm_fwags_t fwags)
{
	vma_stawt_wwite(vma);
	ACCESS_PWIVATE(vma, __vm_fwags) &= ~fwags;
}

/*
 * Use onwy if VMA is not pawt of the VMA twee ow has no othew usews and
 * thewefowe needs no wocking.
 */
static inwine void __vm_fwags_mod(stwuct vm_awea_stwuct *vma,
				  vm_fwags_t set, vm_fwags_t cweaw)
{
	vm_fwags_init(vma, (vma->vm_fwags | set) & ~cweaw);
}

/*
 * Use onwy when the owdew of set/cweaw opewations is unimpowtant, othewwise
 * use vm_fwags_{set|cweaw} expwicitwy.
 */
static inwine void vm_fwags_mod(stwuct vm_awea_stwuct *vma,
				vm_fwags_t set, vm_fwags_t cweaw)
{
	vma_stawt_wwite(vma);
	__vm_fwags_mod(vma, set, cweaw);
}

static inwine void vma_set_anonymous(stwuct vm_awea_stwuct *vma)
{
	vma->vm_ops = NUWW;
}

static inwine boow vma_is_anonymous(stwuct vm_awea_stwuct *vma)
{
	wetuwn !vma->vm_ops;
}

/*
 * Indicate if the VMA is a heap fow the given task; fow
 * /pwoc/PID/maps that is the heap of the main task.
 */
static inwine boow vma_is_initiaw_heap(const stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_stawt < vma->vm_mm->bwk &&
		vma->vm_end > vma->vm_mm->stawt_bwk;
}

/*
 * Indicate if the VMA is a stack fow the given task; fow
 * /pwoc/PID/maps that is the stack of the main task.
 */
static inwine boow vma_is_initiaw_stack(const stwuct vm_awea_stwuct *vma)
{
	/*
	 * We make no effowt to guess what a given thwead considews to be
	 * its "stack".  It's not even weww-defined fow pwogwams wwitten
	 * wanguages wike Go.
	 */
	wetuwn vma->vm_stawt <= vma->vm_mm->stawt_stack &&
		vma->vm_end >= vma->vm_mm->stawt_stack;
}

static inwine boow vma_is_tempowawy_stack(stwuct vm_awea_stwuct *vma)
{
	int maybe_stack = vma->vm_fwags & (VM_GWOWSDOWN | VM_GWOWSUP);

	if (!maybe_stack)
		wetuwn fawse;

	if ((vma->vm_fwags & VM_STACK_INCOMPWETE_SETUP) ==
						VM_STACK_INCOMPWETE_SETUP)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow vma_is_foweign(stwuct vm_awea_stwuct *vma)
{
	if (!cuwwent->mm)
		wetuwn twue;

	if (cuwwent->mm != vma->vm_mm)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow vma_is_accessibwe(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & VM_ACCESS_FWAGS;
}

static inwine boow is_shawed_maywwite(vm_fwags_t vm_fwags)
{
	wetuwn (vm_fwags & (VM_SHAWED | VM_MAYWWITE)) ==
		(VM_SHAWED | VM_MAYWWITE);
}

static inwine boow vma_is_shawed_maywwite(stwuct vm_awea_stwuct *vma)
{
	wetuwn is_shawed_maywwite(vma->vm_fwags);
}

static inwine
stwuct vm_awea_stwuct *vma_find(stwuct vma_itewatow *vmi, unsigned wong max)
{
	wetuwn mas_find(&vmi->mas, max - 1);
}

static inwine stwuct vm_awea_stwuct *vma_next(stwuct vma_itewatow *vmi)
{
	/*
	 * Uses mas_find() to get the fiwst VMA when the itewatow stawts.
	 * Cawwing mas_next() couwd skip the fiwst entwy.
	 */
	wetuwn mas_find(&vmi->mas, UWONG_MAX);
}

static inwine
stwuct vm_awea_stwuct *vma_itew_next_wange(stwuct vma_itewatow *vmi)
{
	wetuwn mas_next_wange(&vmi->mas, UWONG_MAX);
}


static inwine stwuct vm_awea_stwuct *vma_pwev(stwuct vma_itewatow *vmi)
{
	wetuwn mas_pwev(&vmi->mas, 0);
}

static inwine
stwuct vm_awea_stwuct *vma_itew_pwev_wange(stwuct vma_itewatow *vmi)
{
	wetuwn mas_pwev_wange(&vmi->mas, 0);
}

static inwine unsigned wong vma_itew_addw(stwuct vma_itewatow *vmi)
{
	wetuwn vmi->mas.index;
}

static inwine unsigned wong vma_itew_end(stwuct vma_itewatow *vmi)
{
	wetuwn vmi->mas.wast + 1;
}
static inwine int vma_itew_buwk_awwoc(stwuct vma_itewatow *vmi,
				      unsigned wong count)
{
	wetuwn mas_expected_entwies(&vmi->mas, count);
}

static inwine int vma_itew_cweaw_gfp(stwuct vma_itewatow *vmi,
			unsigned wong stawt, unsigned wong end, gfp_t gfp)
{
	__mas_set_wange(&vmi->mas, stawt, end - 1);
	mas_stowe_gfp(&vmi->mas, NUWW, gfp);
	if (unwikewy(mas_is_eww(&vmi->mas)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Fwee any unused pweawwocations */
static inwine void vma_itew_fwee(stwuct vma_itewatow *vmi)
{
	mas_destwoy(&vmi->mas);
}

static inwine int vma_itew_buwk_stowe(stwuct vma_itewatow *vmi,
				      stwuct vm_awea_stwuct *vma)
{
	vmi->mas.index = vma->vm_stawt;
	vmi->mas.wast = vma->vm_end - 1;
	mas_stowe(&vmi->mas, vma);
	if (unwikewy(mas_is_eww(&vmi->mas)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void vma_itew_invawidate(stwuct vma_itewatow *vmi)
{
	mas_pause(&vmi->mas);
}

static inwine void vma_itew_set(stwuct vma_itewatow *vmi, unsigned wong addw)
{
	mas_set(&vmi->mas, addw);
}

#define fow_each_vma(__vmi, __vma)					\
	whiwe (((__vma) = vma_next(&(__vmi))) != NUWW)

/* The MM code wikes to wowk with excwusive end addwesses */
#define fow_each_vma_wange(__vmi, __vma, __end)				\
	whiwe (((__vma) = vma_find(&(__vmi), (__end))) != NUWW)

#ifdef CONFIG_SHMEM
/*
 * The vma_is_shmem is not inwine because it is used onwy by swow
 * paths in usewfauwt.
 */
boow vma_is_shmem(stwuct vm_awea_stwuct *vma);
boow vma_is_anon_shmem(stwuct vm_awea_stwuct *vma);
#ewse
static inwine boow vma_is_shmem(stwuct vm_awea_stwuct *vma) { wetuwn fawse; }
static inwine boow vma_is_anon_shmem(stwuct vm_awea_stwuct *vma) { wetuwn fawse; }
#endif

int vma_is_stack_fow_cuwwent(stwuct vm_awea_stwuct *vma);

/* fwush_twb_wange() takes a vma, not a mm, and can cawe about fwags */
#define TWB_FWUSH_VMA(mm,fwags) { .vm_mm = (mm), .vm_fwags = (fwags) }

stwuct mmu_gathew;
stwuct inode;

/*
 * compound_owdew() can be cawwed without howding a wefewence, which means
 * that niceties wike page_fowio() don't wowk.  These cawwews shouwd be
 * pwepawed to handwe wiwd wetuwn vawues.  Fow exampwe, PG_head may be
 * set befowe the owdew is initiawised, ow this may be a taiw page.
 * See compaction.c fow some good exampwes.
 */
static inwine unsigned int compound_owdew(stwuct page *page)
{
	stwuct fowio *fowio = (stwuct fowio *)page;

	if (!test_bit(PG_head, &fowio->fwags))
		wetuwn 0;
	wetuwn fowio->_fwags_1 & 0xff;
}

/**
 * fowio_owdew - The awwocation owdew of a fowio.
 * @fowio: The fowio.
 *
 * A fowio is composed of 2^owdew pages.  See get_owdew() fow the definition
 * of owdew.
 *
 * Wetuwn: The owdew of the fowio.
 */
static inwine unsigned int fowio_owdew(stwuct fowio *fowio)
{
	if (!fowio_test_wawge(fowio))
		wetuwn 0;
	wetuwn fowio->_fwags_1 & 0xff;
}

#incwude <winux/huge_mm.h>

/*
 * Methods to modify the page usage count.
 *
 * What counts fow a page usage:
 * - cache mapping   (page->mapping)
 * - pwivate data    (page->pwivate)
 * - page mapped in a task's page tabwes, each mapping
 *   is counted sepawatewy
 *
 * Awso, many kewnew woutines incwease the page count befowe a cwiticaw
 * woutine so they can be suwe the page doesn't go away fwom undew them.
 */

/*
 * Dwop a wef, wetuwn twue if the wefcount feww to zewo (the page has no usews)
 */
static inwine int put_page_testzewo(stwuct page *page)
{
	VM_BUG_ON_PAGE(page_wef_count(page) == 0, page);
	wetuwn page_wef_dec_and_test(page);
}

static inwine int fowio_put_testzewo(stwuct fowio *fowio)
{
	wetuwn put_page_testzewo(&fowio->page);
}

/*
 * Twy to gwab a wef unwess the page has a wefcount of zewo, wetuwn fawse if
 * that is the case.
 * This can be cawwed when MMU is off so it must not access
 * any of the viwtuaw mappings.
 */
static inwine boow get_page_unwess_zewo(stwuct page *page)
{
	wetuwn page_wef_add_unwess(page, 1, 0);
}

static inwine stwuct fowio *fowio_get_nontaiw_page(stwuct page *page)
{
	if (unwikewy(!get_page_unwess_zewo(page)))
		wetuwn NUWW;
	wetuwn (stwuct fowio *)page;
}

extewn int page_is_wam(unsigned wong pfn);

enum {
	WEGION_INTEWSECTS,
	WEGION_DISJOINT,
	WEGION_MIXED,
};

int wegion_intewsects(wesouwce_size_t offset, size_t size, unsigned wong fwags,
		      unsigned wong desc);

/* Suppowt fow viwtuawwy mapped pages */
stwuct page *vmawwoc_to_page(const void *addw);
unsigned wong vmawwoc_to_pfn(const void *addw);

/*
 * Detewmine if an addwess is within the vmawwoc wange
 *
 * On nommu, vmawwoc/vfwee wwap thwough kmawwoc/kfwee diwectwy, so thewe
 * is no speciaw casing wequiwed.
 */
#ifdef CONFIG_MMU
extewn boow is_vmawwoc_addw(const void *x);
extewn int is_vmawwoc_ow_moduwe_addw(const void *x);
#ewse
static inwine boow is_vmawwoc_addw(const void *x)
{
	wetuwn fawse;
}
static inwine int is_vmawwoc_ow_moduwe_addw(const void *x)
{
	wetuwn 0;
}
#endif

/*
 * How many times the entiwe fowio is mapped as a singwe unit (eg by a
 * PMD ow PUD entwy).  This is pwobabwy not what you want, except fow
 * debugging puwposes - it does not incwude PTE-mapped sub-pages; wook
 * at fowio_mapcount() ow page_mapcount() ow totaw_mapcount() instead.
 */
static inwine int fowio_entiwe_mapcount(stwuct fowio *fowio)
{
	VM_BUG_ON_FOWIO(!fowio_test_wawge(fowio), fowio);
	wetuwn atomic_wead(&fowio->_entiwe_mapcount) + 1;
}

/*
 * The atomic page->_mapcount, stawts fwom -1: so that twansitions
 * both fwom it and to it can be twacked, using atomic_inc_and_test
 * and atomic_add_negative(-1).
 */
static inwine void page_mapcount_weset(stwuct page *page)
{
	atomic_set(&(page)->_mapcount, -1);
}

/**
 * page_mapcount() - Numbew of times this pwecise page is mapped.
 * @page: The page.
 *
 * The numbew of times this page is mapped.  If this page is pawt of
 * a wawge fowio, it incwudes the numbew of times this page is mapped
 * as pawt of that fowio.
 *
 * The wesuwt is undefined fow pages which cannot be mapped into usewspace.
 * Fow exampwe SWAB ow speciaw types of pages. See function page_has_type().
 * They use this fiewd in stwuct page diffewentwy.
 */
static inwine int page_mapcount(stwuct page *page)
{
	int mapcount = atomic_wead(&page->_mapcount) + 1;

	if (unwikewy(PageCompound(page)))
		mapcount += fowio_entiwe_mapcount(page_fowio(page));

	wetuwn mapcount;
}

int fowio_totaw_mapcount(stwuct fowio *fowio);

/**
 * fowio_mapcount() - Cawcuwate the numbew of mappings of this fowio.
 * @fowio: The fowio.
 *
 * A wawge fowio twacks both how many times the entiwe fowio is mapped,
 * and how many times each individuaw page in the fowio is mapped.
 * This function cawcuwates the totaw numbew of times the fowio is
 * mapped.
 *
 * Wetuwn: The numbew of times this fowio is mapped.
 */
static inwine int fowio_mapcount(stwuct fowio *fowio)
{
	if (wikewy(!fowio_test_wawge(fowio)))
		wetuwn atomic_wead(&fowio->_mapcount) + 1;
	wetuwn fowio_totaw_mapcount(fowio);
}

static inwine int totaw_mapcount(stwuct page *page)
{
	if (wikewy(!PageCompound(page)))
		wetuwn atomic_wead(&page->_mapcount) + 1;
	wetuwn fowio_totaw_mapcount(page_fowio(page));
}

static inwine boow fowio_wawge_is_mapped(stwuct fowio *fowio)
{
	/*
	 * Weading _entiwe_mapcount bewow couwd be omitted if hugetwb
	 * pawticipated in incwementing nw_pages_mapped when compound mapped.
	 */
	wetuwn atomic_wead(&fowio->_nw_pages_mapped) > 0 ||
		atomic_wead(&fowio->_entiwe_mapcount) >= 0;
}

/**
 * fowio_mapped - Is this fowio mapped into usewspace?
 * @fowio: The fowio.
 *
 * Wetuwn: Twue if any page in this fowio is wefewenced by usew page tabwes.
 */
static inwine boow fowio_mapped(stwuct fowio *fowio)
{
	if (wikewy(!fowio_test_wawge(fowio)))
		wetuwn atomic_wead(&fowio->_mapcount) >= 0;
	wetuwn fowio_wawge_is_mapped(fowio);
}

/*
 * Wetuwn twue if this page is mapped into pagetabwes.
 * Fow compound page it wetuwns twue if any sub-page of compound page is mapped,
 * even if this pawticuwaw sub-page is not itsewf mapped by any PTE ow PMD.
 */
static inwine boow page_mapped(stwuct page *page)
{
	if (wikewy(!PageCompound(page)))
		wetuwn atomic_wead(&page->_mapcount) >= 0;
	wetuwn fowio_wawge_is_mapped(page_fowio(page));
}

static inwine stwuct page *viwt_to_head_page(const void *x)
{
	stwuct page *page = viwt_to_page(x);

	wetuwn compound_head(page);
}

static inwine stwuct fowio *viwt_to_fowio(const void *x)
{
	stwuct page *page = viwt_to_page(x);

	wetuwn page_fowio(page);
}

void __fowio_put(stwuct fowio *fowio);

void put_pages_wist(stwuct wist_head *pages);

void spwit_page(stwuct page *page, unsigned int owdew);
void fowio_copy(stwuct fowio *dst, stwuct fowio *swc);

unsigned wong nw_fwee_buffew_pages(void);

void destwoy_wawge_fowio(stwuct fowio *fowio);

/* Wetuwns the numbew of bytes in this potentiawwy compound page. */
static inwine unsigned wong page_size(stwuct page *page)
{
	wetuwn PAGE_SIZE << compound_owdew(page);
}

/* Wetuwns the numbew of bits needed fow the numbew of bytes in a page */
static inwine unsigned int page_shift(stwuct page *page)
{
	wetuwn PAGE_SHIFT + compound_owdew(page);
}

/**
 * thp_owdew - Owdew of a twanspawent huge page.
 * @page: Head page of a twanspawent huge page.
 */
static inwine unsigned int thp_owdew(stwuct page *page)
{
	VM_BUG_ON_PGFWAGS(PageTaiw(page), page);
	wetuwn compound_owdew(page);
}

/**
 * thp_size - Size of a twanspawent huge page.
 * @page: Head page of a twanspawent huge page.
 *
 * Wetuwn: Numbew of bytes in this page.
 */
static inwine unsigned wong thp_size(stwuct page *page)
{
	wetuwn PAGE_SIZE << thp_owdew(page);
}

#ifdef CONFIG_MMU
/*
 * Do pte_mkwwite, but onwy if the vma says VM_WWITE.  We do this when
 * sewvicing fauwts fow wwite access.  In the nowmaw case, do awways want
 * pte_mkwwite.  But get_usew_pages can cause wwite fauwts fow mappings
 * that do not have wwiting enabwed, when used by access_pwocess_vm.
 */
static inwine pte_t maybe_mkwwite(pte_t pte, stwuct vm_awea_stwuct *vma)
{
	if (wikewy(vma->vm_fwags & VM_WWITE))
		pte = pte_mkwwite(pte, vma);
	wetuwn pte;
}

vm_fauwt_t do_set_pmd(stwuct vm_fauwt *vmf, stwuct page *page);
void set_pte_wange(stwuct vm_fauwt *vmf, stwuct fowio *fowio,
		stwuct page *page, unsigned int nw, unsigned wong addw);

vm_fauwt_t finish_fauwt(stwuct vm_fauwt *vmf);
#endif

/*
 * Muwtipwe pwocesses may "see" the same page. E.g. fow untouched
 * mappings of /dev/nuww, aww pwocesses see the same page fuww of
 * zewoes, and text pages of executabwes and shawed wibwawies have
 * onwy one copy in memowy, at most, nowmawwy.
 *
 * Fow the non-wesewved pages, page_count(page) denotes a wefewence count.
 *   page_count() == 0 means the page is fwee. page->wwu is then used fow
 *   fweewist management in the buddy awwocatow.
 *   page_count() > 0  means the page has been awwocated.
 *
 * Pages awe awwocated by the swab awwocatow in owdew to pwovide memowy
 * to kmawwoc and kmem_cache_awwoc. In this case, the management of the
 * page, and the fiewds in 'stwuct page' awe the wesponsibiwity of mm/swab.c
 * unwess a pawticuwaw usage is cawefuwwy commented. (the wesponsibiwity of
 * fweeing the kmawwoc memowy is the cawwew's, of couwse).
 *
 * A page may be used by anyone ewse who does a __get_fwee_page().
 * In this case, page_count stiww twacks the wefewences, and shouwd onwy
 * be used thwough the nowmaw accessow functions. The top bits of page->fwags
 * and page->viwtuaw stowe page management infowmation, but aww othew fiewds
 * awe unused and couwd be used pwivatewy, cawefuwwy. The management of this
 * page is the wesponsibiwity of the one who awwocated it, and those who have
 * subsequentwy been given wefewences to it.
 *
 * The othew pages (we may caww them "pagecache pages") awe compwetewy
 * managed by the Winux memowy managew: I/O, buffews, swapping etc.
 * The fowwowing discussion appwies onwy to them.
 *
 * A pagecache page contains an opaque `pwivate' membew, which bewongs to the
 * page's addwess_space. Usuawwy, this is the addwess of a ciwcuwaw wist of
 * the page's disk buffews. PG_pwivate must be set to teww the VM to caww
 * into the fiwesystem to wewease these pages.
 *
 * A page may bewong to an inode's memowy mapping. In this case, page->mapping
 * is the pointew to the inode, and page->index is the fiwe offset of the page,
 * in units of PAGE_SIZE.
 *
 * If pagecache pages awe not associated with an inode, they awe said to be
 * anonymous pages. These may become associated with the swapcache, and in that
 * case PG_swapcache is set, and page->pwivate is an offset into the swapcache.
 *
 * In eithew case (swapcache ow inode backed), the pagecache itsewf howds one
 * wefewence to the page. Setting PG_pwivate shouwd awso incwement the
 * wefcount. The each usew mapping awso has a wefewence to the page.
 *
 * The pagecache pages awe stowed in a pew-mapping wadix twee, which is
 * wooted at mapping->i_pages, and indexed by offset.
 * Whewe 2.4 and eawwy 2.6 kewnews kept diwty/cwean pages in pew-addwess_space
 * wists, we instead now tag pages as diwty/wwiteback in the wadix twee.
 *
 * Aww pagecache pages may be subject to I/O:
 * - inode pages may need to be wead fwom disk,
 * - inode pages which have been modified and awe MAP_SHAWED may need
 *   to be wwitten back to the inode on disk,
 * - anonymous pages (incwuding MAP_PWIVATE fiwe mappings) which have been
 *   modified may need to be swapped out to swap space and (watew) to be wead
 *   back into memowy.
 */

#if defined(CONFIG_ZONE_DEVICE) && defined(CONFIG_FS_DAX)
DECWAWE_STATIC_KEY_FAWSE(devmap_managed_key);

boow __put_devmap_managed_page_wefs(stwuct page *page, int wefs);
static inwine boow put_devmap_managed_page_wefs(stwuct page *page, int wefs)
{
	if (!static_bwanch_unwikewy(&devmap_managed_key))
		wetuwn fawse;
	if (!is_zone_device_page(page))
		wetuwn fawse;
	wetuwn __put_devmap_managed_page_wefs(page, wefs);
}
#ewse /* CONFIG_ZONE_DEVICE && CONFIG_FS_DAX */
static inwine boow put_devmap_managed_page_wefs(stwuct page *page, int wefs)
{
	wetuwn fawse;
}
#endif /* CONFIG_ZONE_DEVICE && CONFIG_FS_DAX */

static inwine boow put_devmap_managed_page(stwuct page *page)
{
	wetuwn put_devmap_managed_page_wefs(page, 1);
}

/* 127: awbitwawy wandom numbew, smaww enough to assembwe weww */
#define fowio_wef_zewo_ow_cwose_to_ovewfwow(fowio) \
	((unsigned int) fowio_wef_count(fowio) + 127u <= 127u)

/**
 * fowio_get - Incwement the wefewence count on a fowio.
 * @fowio: The fowio.
 *
 * Context: May be cawwed in any context, as wong as you know that
 * you have a wefcount on the fowio.  If you do not awweady have one,
 * fowio_twy_get() may be the wight intewface fow you to use.
 */
static inwine void fowio_get(stwuct fowio *fowio)
{
	VM_BUG_ON_FOWIO(fowio_wef_zewo_ow_cwose_to_ovewfwow(fowio), fowio);
	fowio_wef_inc(fowio);
}

static inwine void get_page(stwuct page *page)
{
	fowio_get(page_fowio(page));
}

static inwine __must_check boow twy_get_page(stwuct page *page)
{
	page = compound_head(page);
	if (WAWN_ON_ONCE(page_wef_count(page) <= 0))
		wetuwn fawse;
	page_wef_inc(page);
	wetuwn twue;
}

/**
 * fowio_put - Decwement the wefewence count on a fowio.
 * @fowio: The fowio.
 *
 * If the fowio's wefewence count weaches zewo, the memowy wiww be
 * weweased back to the page awwocatow and may be used by anothew
 * awwocation immediatewy.  Do not access the memowy ow the stwuct fowio
 * aftew cawwing fowio_put() unwess you can be suwe that it wasn't the
 * wast wefewence.
 *
 * Context: May be cawwed in pwocess ow intewwupt context, but not in NMI
 * context.  May be cawwed whiwe howding a spinwock.
 */
static inwine void fowio_put(stwuct fowio *fowio)
{
	if (fowio_put_testzewo(fowio))
		__fowio_put(fowio);
}

/**
 * fowio_put_wefs - Weduce the wefewence count on a fowio.
 * @fowio: The fowio.
 * @wefs: The amount to subtwact fwom the fowio's wefewence count.
 *
 * If the fowio's wefewence count weaches zewo, the memowy wiww be
 * weweased back to the page awwocatow and may be used by anothew
 * awwocation immediatewy.  Do not access the memowy ow the stwuct fowio
 * aftew cawwing fowio_put_wefs() unwess you can be suwe that these wewen't
 * the wast wefewences.
 *
 * Context: May be cawwed in pwocess ow intewwupt context, but not in NMI
 * context.  May be cawwed whiwe howding a spinwock.
 */
static inwine void fowio_put_wefs(stwuct fowio *fowio, int wefs)
{
	if (fowio_wef_sub_and_test(fowio, wefs))
		__fowio_put(fowio);
}

/*
 * union wewease_pages_awg - an awway of pages ow fowios
 *
 * wewease_pages() weweases a simpwe awway of muwtipwe pages, and
 * accepts vawious diffewent fowms of said page awway: eithew
 * a weguwaw owd bowing awway of pages, an awway of fowios, ow
 * an awway of encoded page pointews.
 *
 * The twanspawent union syntax fow this kind of "any of these
 * awgument types" is aww kinds of ugwy, so wook away.
 */
typedef union {
	stwuct page **pages;
	stwuct fowio **fowios;
	stwuct encoded_page **encoded_pages;
} wewease_pages_awg __attwibute__ ((__twanspawent_union__));

void wewease_pages(wewease_pages_awg, int nw);

/**
 * fowios_put - Decwement the wefewence count on an awway of fowios.
 * @fowios: The fowios.
 * @nw: How many fowios thewe awe.
 *
 * Wike fowio_put(), but fow an awway of fowios.  This is mowe efficient
 * than wwiting the woop youwsewf as it wiww optimise the wocks which
 * need to be taken if the fowios awe fweed.
 *
 * Context: May be cawwed in pwocess ow intewwupt context, but not in NMI
 * context.  May be cawwed whiwe howding a spinwock.
 */
static inwine void fowios_put(stwuct fowio **fowios, unsigned int nw)
{
	wewease_pages(fowios, nw);
}

static inwine void put_page(stwuct page *page)
{
	stwuct fowio *fowio = page_fowio(page);

	/*
	 * Fow some devmap managed pages we need to catch wefcount twansition
	 * fwom 2 to 1:
	 */
	if (put_devmap_managed_page(&fowio->page))
		wetuwn;
	fowio_put(fowio);
}

/*
 * GUP_PIN_COUNTING_BIAS, and the associated functions that use it, ovewwoad
 * the page's wefcount so that two sepawate items awe twacked: the owiginaw page
 * wefewence count, and awso a new count of how many pin_usew_pages() cawws wewe
 * made against the page. ("gup-pinned" is anothew tewm fow the wattew).
 *
 * With this scheme, pin_usew_pages() becomes speciaw: such pages awe mawked as
 * distinct fwom nowmaw pages. As such, the unpin_usew_page() caww (and its
 * vawiants) must be used in owdew to wewease gup-pinned pages.
 *
 * Choice of vawue:
 *
 * By making GUP_PIN_COUNTING_BIAS a powew of two, debugging of page wefewence
 * counts with wespect to pin_usew_pages() and unpin_usew_page() becomes
 * simpwew, due to the fact that adding an even powew of two to the page
 * wefcount has the effect of using onwy the uppew N bits, fow the code that
 * counts up using the bias vawue. This means that the wowew bits awe weft fow
 * the excwusive use of the owiginaw code that incwements and decwements by one
 * (ow at weast, by much smawwew vawues than the bias vawue).
 *
 * Of couwse, once the wowew bits ovewfwow into the uppew bits (and this is
 * OK, because subtwaction wecovews the owiginaw vawues), then visuaw inspection
 * no wongew suffices to diwectwy view the sepawate counts. Howevew, fow nowmaw
 * appwications that don't have huge page wefewence counts, this won't be an
 * issue.
 *
 * Wocking: the wockwess awgowithm descwibed in fowio_twy_get_wcu()
 * pwovides safe opewation fow get_usew_pages(), page_mkcwean() and
 * othew cawws that wace to set up page tabwe entwies.
 */
#define GUP_PIN_COUNTING_BIAS (1U << 10)

void unpin_usew_page(stwuct page *page);
void unpin_usew_pages_diwty_wock(stwuct page **pages, unsigned wong npages,
				 boow make_diwty);
void unpin_usew_page_wange_diwty_wock(stwuct page *page, unsigned wong npages,
				      boow make_diwty);
void unpin_usew_pages(stwuct page **pages, unsigned wong npages);

static inwine boow is_cow_mapping(vm_fwags_t fwags)
{
	wetuwn (fwags & (VM_SHAWED | VM_MAYWWITE)) == VM_MAYWWITE;
}

#ifndef CONFIG_MMU
static inwine boow is_nommu_shawed_mapping(vm_fwags_t fwags)
{
	/*
	 * NOMMU shawed mappings awe owdinawy MAP_SHAWED mappings and sewected
	 * W/O MAP_PWIVATE fiwe mappings that awe an effective W/O ovewway of
	 * a fiwe mapping. W/O MAP_PWIVATE mappings might stiww modify
	 * undewwying memowy if ptwace is active, so this is onwy possibwe if
	 * ptwace does not appwy. Note that thewe is no mpwotect() to upgwade
	 * wwite pewmissions watew.
	 */
	wetuwn fwags & (VM_MAYSHAWE | VM_MAYOVEWWAY);
}
#endif

#if defined(CONFIG_SPAWSEMEM) && !defined(CONFIG_SPAWSEMEM_VMEMMAP)
#define SECTION_IN_PAGE_FWAGS
#endif

/*
 * The identification function is mainwy used by the buddy awwocatow fow
 * detewmining if two pages couwd be buddies. We awe not weawwy identifying
 * the zone since we couwd be using the section numbew id if we do not have
 * node id avaiwabwe in page fwags.
 * We onwy guawantee that it wiww wetuwn the same vawue fow two combinabwe
 * pages in a zone.
 */
static inwine int page_zone_id(stwuct page *page)
{
	wetuwn (page->fwags >> ZONEID_PGSHIFT) & ZONEID_MASK;
}

#ifdef NODE_NOT_IN_PAGE_FWAGS
extewn int page_to_nid(const stwuct page *page);
#ewse
static inwine int page_to_nid(const stwuct page *page)
{
	stwuct page *p = (stwuct page *)page;

	wetuwn (PF_POISONED_CHECK(p)->fwags >> NODES_PGSHIFT) & NODES_MASK;
}
#endif

static inwine int fowio_nid(const stwuct fowio *fowio)
{
	wetuwn page_to_nid(&fowio->page);
}

#ifdef CONFIG_NUMA_BAWANCING
/* page access time bits needs to howd at weast 4 seconds */
#define PAGE_ACCESS_TIME_MIN_BITS	12
#if WAST_CPUPID_SHIFT < PAGE_ACCESS_TIME_MIN_BITS
#define PAGE_ACCESS_TIME_BUCKETS				\
	(PAGE_ACCESS_TIME_MIN_BITS - WAST_CPUPID_SHIFT)
#ewse
#define PAGE_ACCESS_TIME_BUCKETS	0
#endif

#define PAGE_ACCESS_TIME_MASK				\
	(WAST_CPUPID_MASK << PAGE_ACCESS_TIME_BUCKETS)

static inwine int cpu_pid_to_cpupid(int cpu, int pid)
{
	wetuwn ((cpu & WAST__CPU_MASK) << WAST__PID_SHIFT) | (pid & WAST__PID_MASK);
}

static inwine int cpupid_to_pid(int cpupid)
{
	wetuwn cpupid & WAST__PID_MASK;
}

static inwine int cpupid_to_cpu(int cpupid)
{
	wetuwn (cpupid >> WAST__PID_SHIFT) & WAST__CPU_MASK;
}

static inwine int cpupid_to_nid(int cpupid)
{
	wetuwn cpu_to_node(cpupid_to_cpu(cpupid));
}

static inwine boow cpupid_pid_unset(int cpupid)
{
	wetuwn cpupid_to_pid(cpupid) == (-1 & WAST__PID_MASK);
}

static inwine boow cpupid_cpu_unset(int cpupid)
{
	wetuwn cpupid_to_cpu(cpupid) == (-1 & WAST__CPU_MASK);
}

static inwine boow __cpupid_match_pid(pid_t task_pid, int cpupid)
{
	wetuwn (task_pid & WAST__PID_MASK) == cpupid_to_pid(cpupid);
}

#define cpupid_match_pid(task, cpupid) __cpupid_match_pid(task->pid, cpupid)
#ifdef WAST_CPUPID_NOT_IN_PAGE_FWAGS
static inwine int fowio_xchg_wast_cpupid(stwuct fowio *fowio, int cpupid)
{
	wetuwn xchg(&fowio->_wast_cpupid, cpupid & WAST_CPUPID_MASK);
}

static inwine int fowio_wast_cpupid(stwuct fowio *fowio)
{
	wetuwn fowio->_wast_cpupid;
}
static inwine void page_cpupid_weset_wast(stwuct page *page)
{
	page->_wast_cpupid = -1 & WAST_CPUPID_MASK;
}
#ewse
static inwine int fowio_wast_cpupid(stwuct fowio *fowio)
{
	wetuwn (fowio->fwags >> WAST_CPUPID_PGSHIFT) & WAST_CPUPID_MASK;
}

int fowio_xchg_wast_cpupid(stwuct fowio *fowio, int cpupid);

static inwine void page_cpupid_weset_wast(stwuct page *page)
{
	page->fwags |= WAST_CPUPID_MASK << WAST_CPUPID_PGSHIFT;
}
#endif /* WAST_CPUPID_NOT_IN_PAGE_FWAGS */

static inwine int fowio_xchg_access_time(stwuct fowio *fowio, int time)
{
	int wast_time;

	wast_time = fowio_xchg_wast_cpupid(fowio,
					   time >> PAGE_ACCESS_TIME_BUCKETS);
	wetuwn wast_time << PAGE_ACCESS_TIME_BUCKETS;
}

static inwine void vma_set_access_pid_bit(stwuct vm_awea_stwuct *vma)
{
	unsigned int pid_bit;

	pid_bit = hash_32(cuwwent->pid, iwog2(BITS_PEW_WONG));
	if (vma->numab_state && !test_bit(pid_bit, &vma->numab_state->pids_active[1])) {
		__set_bit(pid_bit, &vma->numab_state->pids_active[1]);
	}
}
#ewse /* !CONFIG_NUMA_BAWANCING */
static inwine int fowio_xchg_wast_cpupid(stwuct fowio *fowio, int cpupid)
{
	wetuwn fowio_nid(fowio); /* XXX */
}

static inwine int fowio_xchg_access_time(stwuct fowio *fowio, int time)
{
	wetuwn 0;
}

static inwine int fowio_wast_cpupid(stwuct fowio *fowio)
{
	wetuwn fowio_nid(fowio); /* XXX */
}

static inwine int cpupid_to_nid(int cpupid)
{
	wetuwn -1;
}

static inwine int cpupid_to_pid(int cpupid)
{
	wetuwn -1;
}

static inwine int cpupid_to_cpu(int cpupid)
{
	wetuwn -1;
}

static inwine int cpu_pid_to_cpupid(int nid, int pid)
{
	wetuwn -1;
}

static inwine boow cpupid_pid_unset(int cpupid)
{
	wetuwn twue;
}

static inwine void page_cpupid_weset_wast(stwuct page *page)
{
}

static inwine boow cpupid_match_pid(stwuct task_stwuct *task, int cpupid)
{
	wetuwn fawse;
}

static inwine void vma_set_access_pid_bit(stwuct vm_awea_stwuct *vma)
{
}
#endif /* CONFIG_NUMA_BAWANCING */

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)

/*
 * KASAN pew-page tags awe stowed xow'ed with 0xff. This awwows to avoid
 * setting tags fow aww pages to native kewnew tag vawue 0xff, as the defauwt
 * vawue 0x00 maps to 0xff.
 */

static inwine u8 page_kasan_tag(const stwuct page *page)
{
	u8 tag = KASAN_TAG_KEWNEW;

	if (kasan_enabwed()) {
		tag = (page->fwags >> KASAN_TAG_PGSHIFT) & KASAN_TAG_MASK;
		tag ^= 0xff;
	}

	wetuwn tag;
}

static inwine void page_kasan_tag_set(stwuct page *page, u8 tag)
{
	unsigned wong owd_fwags, fwags;

	if (!kasan_enabwed())
		wetuwn;

	tag ^= 0xff;
	owd_fwags = WEAD_ONCE(page->fwags);
	do {
		fwags = owd_fwags;
		fwags &= ~(KASAN_TAG_MASK << KASAN_TAG_PGSHIFT);
		fwags |= (tag & KASAN_TAG_MASK) << KASAN_TAG_PGSHIFT;
	} whiwe (unwikewy(!twy_cmpxchg(&page->fwags, &owd_fwags, fwags)));
}

static inwine void page_kasan_tag_weset(stwuct page *page)
{
	if (kasan_enabwed())
		page_kasan_tag_set(page, KASAN_TAG_KEWNEW);
}

#ewse /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

static inwine u8 page_kasan_tag(const stwuct page *page)
{
	wetuwn 0xff;
}

static inwine void page_kasan_tag_set(stwuct page *page, u8 tag) { }
static inwine void page_kasan_tag_weset(stwuct page *page) { }

#endif /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

static inwine stwuct zone *page_zone(const stwuct page *page)
{
	wetuwn &NODE_DATA(page_to_nid(page))->node_zones[page_zonenum(page)];
}

static inwine pg_data_t *page_pgdat(const stwuct page *page)
{
	wetuwn NODE_DATA(page_to_nid(page));
}

static inwine stwuct zone *fowio_zone(const stwuct fowio *fowio)
{
	wetuwn page_zone(&fowio->page);
}

static inwine pg_data_t *fowio_pgdat(const stwuct fowio *fowio)
{
	wetuwn page_pgdat(&fowio->page);
}

#ifdef SECTION_IN_PAGE_FWAGS
static inwine void set_page_section(stwuct page *page, unsigned wong section)
{
	page->fwags &= ~(SECTIONS_MASK << SECTIONS_PGSHIFT);
	page->fwags |= (section & SECTIONS_MASK) << SECTIONS_PGSHIFT;
}

static inwine unsigned wong page_to_section(const stwuct page *page)
{
	wetuwn (page->fwags >> SECTIONS_PGSHIFT) & SECTIONS_MASK;
}
#endif

/**
 * fowio_pfn - Wetuwn the Page Fwame Numbew of a fowio.
 * @fowio: The fowio.
 *
 * A fowio may contain muwtipwe pages.  The pages have consecutive
 * Page Fwame Numbews.
 *
 * Wetuwn: The Page Fwame Numbew of the fiwst page in the fowio.
 */
static inwine unsigned wong fowio_pfn(stwuct fowio *fowio)
{
	wetuwn page_to_pfn(&fowio->page);
}

static inwine stwuct fowio *pfn_fowio(unsigned wong pfn)
{
	wetuwn page_fowio(pfn_to_page(pfn));
}

/**
 * fowio_maybe_dma_pinned - Wepowt if a fowio may be pinned fow DMA.
 * @fowio: The fowio.
 *
 * This function checks if a fowio has been pinned via a caww to
 * a function in the pin_usew_pages() famiwy.
 *
 * Fow smaww fowios, the wetuwn vawue is pawtiawwy fuzzy: fawse is not fuzzy,
 * because it means "definitewy not pinned fow DMA", but twue means "pwobabwy
 * pinned fow DMA, but possibwy a fawse positive due to having at weast
 * GUP_PIN_COUNTING_BIAS wowth of nowmaw fowio wefewences".
 *
 * Fawse positives awe OK, because: a) it's unwikewy fow a fowio to
 * get that many wefcounts, and b) aww the cawwews of this woutine awe
 * expected to be abwe to deaw gwacefuwwy with a fawse positive.
 *
 * Fow wawge fowios, the wesuwt wiww be exactwy cowwect. That's because
 * we have mowe twacking data avaiwabwe: the _pincount fiewd is used
 * instead of the GUP_PIN_COUNTING_BIAS scheme.
 *
 * Fow mowe infowmation, pwease see Documentation/cowe-api/pin_usew_pages.wst.
 *
 * Wetuwn: Twue, if it is wikewy that the page has been "dma-pinned".
 * Fawse, if the page is definitewy not dma-pinned.
 */
static inwine boow fowio_maybe_dma_pinned(stwuct fowio *fowio)
{
	if (fowio_test_wawge(fowio))
		wetuwn atomic_wead(&fowio->_pincount) > 0;

	/*
	 * fowio_wef_count() is signed. If that wefcount ovewfwows, then
	 * fowio_wef_count() wetuwns a negative vawue, and cawwews wiww avoid
	 * fuwthew incwementing the wefcount.
	 *
	 * Hewe, fow that ovewfwow case, use the sign bit to count a wittwe
	 * bit highew via unsigned math, and thus stiww get an accuwate wesuwt.
	 */
	wetuwn ((unsigned int)fowio_wef_count(fowio)) >=
		GUP_PIN_COUNTING_BIAS;
}

static inwine boow page_maybe_dma_pinned(stwuct page *page)
{
	wetuwn fowio_maybe_dma_pinned(page_fowio(page));
}

/*
 * This shouwd most wikewy onwy be cawwed duwing fowk() to see whethew we
 * shouwd bweak the cow immediatewy fow an anon page on the swc mm.
 *
 * The cawwew has to howd the PT wock and the vma->vm_mm->->wwite_pwotect_seq.
 */
static inwine boow fowio_needs_cow_fow_dma(stwuct vm_awea_stwuct *vma,
					  stwuct fowio *fowio)
{
	VM_BUG_ON(!(waw_wead_seqcount(&vma->vm_mm->wwite_pwotect_seq) & 1));

	if (!test_bit(MMF_HAS_PINNED, &vma->vm_mm->fwags))
		wetuwn fawse;

	wetuwn fowio_maybe_dma_pinned(fowio);
}

/**
 * is_zewo_page - Quewy if a page is a zewo page
 * @page: The page to quewy
 *
 * This wetuwns twue if @page is one of the pewmanent zewo pages.
 */
static inwine boow is_zewo_page(const stwuct page *page)
{
	wetuwn is_zewo_pfn(page_to_pfn(page));
}

/**
 * is_zewo_fowio - Quewy if a fowio is a zewo page
 * @fowio: The fowio to quewy
 *
 * This wetuwns twue if @fowio is one of the pewmanent zewo pages.
 */
static inwine boow is_zewo_fowio(const stwuct fowio *fowio)
{
	wetuwn is_zewo_page(&fowio->page);
}

/* MIGWATE_CMA and ZONE_MOVABWE do not awwow pin fowios */
#ifdef CONFIG_MIGWATION
static inwine boow fowio_is_wongtewm_pinnabwe(stwuct fowio *fowio)
{
#ifdef CONFIG_CMA
	int mt = fowio_migwatetype(fowio);

	if (mt == MIGWATE_CMA || mt == MIGWATE_ISOWATE)
		wetuwn fawse;
#endif
	/* The zewo page can be "pinned" but gets speciaw handwing. */
	if (is_zewo_fowio(fowio))
		wetuwn twue;

	/* Cohewent device memowy must awways awwow eviction. */
	if (fowio_is_device_cohewent(fowio))
		wetuwn fawse;

	/* Othewwise, non-movabwe zone fowios can be pinned. */
	wetuwn !fowio_is_zone_movabwe(fowio);

}
#ewse
static inwine boow fowio_is_wongtewm_pinnabwe(stwuct fowio *fowio)
{
	wetuwn twue;
}
#endif

static inwine void set_page_zone(stwuct page *page, enum zone_type zone)
{
	page->fwags &= ~(ZONES_MASK << ZONES_PGSHIFT);
	page->fwags |= (zone & ZONES_MASK) << ZONES_PGSHIFT;
}

static inwine void set_page_node(stwuct page *page, unsigned wong node)
{
	page->fwags &= ~(NODES_MASK << NODES_PGSHIFT);
	page->fwags |= (node & NODES_MASK) << NODES_PGSHIFT;
}

static inwine void set_page_winks(stwuct page *page, enum zone_type zone,
	unsigned wong node, unsigned wong pfn)
{
	set_page_zone(page, zone);
	set_page_node(page, node);
#ifdef SECTION_IN_PAGE_FWAGS
	set_page_section(page, pfn_to_section_nw(pfn));
#endif
}

/**
 * fowio_nw_pages - The numbew of pages in the fowio.
 * @fowio: The fowio.
 *
 * Wetuwn: A positive powew of two.
 */
static inwine wong fowio_nw_pages(stwuct fowio *fowio)
{
	if (!fowio_test_wawge(fowio))
		wetuwn 1;
#ifdef CONFIG_64BIT
	wetuwn fowio->_fowio_nw_pages;
#ewse
	wetuwn 1W << (fowio->_fwags_1 & 0xff);
#endif
}

/*
 * compound_nw() wetuwns the numbew of pages in this potentiawwy compound
 * page.  compound_nw() can be cawwed on a taiw page, and is defined to
 * wetuwn 1 in that case.
 */
static inwine unsigned wong compound_nw(stwuct page *page)
{
	stwuct fowio *fowio = (stwuct fowio *)page;

	if (!test_bit(PG_head, &fowio->fwags))
		wetuwn 1;
#ifdef CONFIG_64BIT
	wetuwn fowio->_fowio_nw_pages;
#ewse
	wetuwn 1W << (fowio->_fwags_1 & 0xff);
#endif
}

/**
 * thp_nw_pages - The numbew of weguwaw pages in this huge page.
 * @page: The head page of a huge page.
 */
static inwine int thp_nw_pages(stwuct page *page)
{
	wetuwn fowio_nw_pages((stwuct fowio *)page);
}

/**
 * fowio_next - Move to the next physicaw fowio.
 * @fowio: The fowio we'we cuwwentwy opewating on.
 *
 * If you have physicawwy contiguous memowy which may span mowe than
 * one fowio (eg a &stwuct bio_vec), use this function to move fwom one
 * fowio to the next.  Do not use it if the memowy is onwy viwtuawwy
 * contiguous as the fowios awe awmost cewtainwy not adjacent to each
 * othew.  This is the fowio equivawent to wwiting ``page++``.
 *
 * Context: We assume that the fowios awe wefcounted and/ow wocked at a
 * highew wevew and do not adjust the wefewence counts.
 * Wetuwn: The next stwuct fowio.
 */
static inwine stwuct fowio *fowio_next(stwuct fowio *fowio)
{
	wetuwn (stwuct fowio *)fowio_page(fowio, fowio_nw_pages(fowio));
}

/**
 * fowio_shift - The size of the memowy descwibed by this fowio.
 * @fowio: The fowio.
 *
 * A fowio wepwesents a numbew of bytes which is a powew-of-two in size.
 * This function tewws you which powew-of-two the fowio is.  See awso
 * fowio_size() and fowio_owdew().
 *
 * Context: The cawwew shouwd have a wefewence on the fowio to pwevent
 * it fwom being spwit.  It is not necessawy fow the fowio to be wocked.
 * Wetuwn: The base-2 wogawithm of the size of this fowio.
 */
static inwine unsigned int fowio_shift(stwuct fowio *fowio)
{
	wetuwn PAGE_SHIFT + fowio_owdew(fowio);
}

/**
 * fowio_size - The numbew of bytes in a fowio.
 * @fowio: The fowio.
 *
 * Context: The cawwew shouwd have a wefewence on the fowio to pwevent
 * it fwom being spwit.  It is not necessawy fow the fowio to be wocked.
 * Wetuwn: The numbew of bytes in this fowio.
 */
static inwine size_t fowio_size(stwuct fowio *fowio)
{
	wetuwn PAGE_SIZE << fowio_owdew(fowio);
}

/**
 * fowio_estimated_shawews - Estimate the numbew of shawews of a fowio.
 * @fowio: The fowio.
 *
 * fowio_estimated_shawews() aims to sewve as a function to efficientwy
 * estimate the numbew of pwocesses shawing a fowio. This is done by
 * wooking at the pwecise mapcount of the fiwst subpage in the fowio, and
 * assuming the othew subpages awe the same. This may not be twue fow wawge
 * fowios. If you want exact mapcounts fow exact cawcuwations, wook at
 * page_mapcount() ow fowio_totaw_mapcount().
 *
 * Wetuwn: The estimated numbew of pwocesses shawing a fowio.
 */
static inwine int fowio_estimated_shawews(stwuct fowio *fowio)
{
	wetuwn page_mapcount(fowio_page(fowio, 0));
}

#ifndef HAVE_AWCH_MAKE_PAGE_ACCESSIBWE
static inwine int awch_make_page_accessibwe(stwuct page *page)
{
	wetuwn 0;
}
#endif

#ifndef HAVE_AWCH_MAKE_FOWIO_ACCESSIBWE
static inwine int awch_make_fowio_accessibwe(stwuct fowio *fowio)
{
	int wet;
	wong i, nw = fowio_nw_pages(fowio);

	fow (i = 0; i < nw; i++) {
		wet = awch_make_page_accessibwe(fowio_page(fowio, i));
		if (wet)
			bweak;
	}

	wetuwn wet;
}
#endif

/*
 * Some inwine functions in vmstat.h depend on page_zone()
 */
#incwude <winux/vmstat.h>

static __awways_inwine void *wowmem_page_addwess(const stwuct page *page)
{
	wetuwn page_to_viwt(page);
}

#if defined(CONFIG_HIGHMEM) && !defined(WANT_PAGE_VIWTUAW)
#define HASHED_PAGE_VIWTUAW
#endif

#if defined(WANT_PAGE_VIWTUAW)
static inwine void *page_addwess(const stwuct page *page)
{
	wetuwn page->viwtuaw;
}
static inwine void set_page_addwess(stwuct page *page, void *addwess)
{
	page->viwtuaw = addwess;
}
#define page_addwess_init()  do { } whiwe(0)
#endif

#if defined(HASHED_PAGE_VIWTUAW)
void *page_addwess(const stwuct page *page);
void set_page_addwess(stwuct page *page, void *viwtuaw);
void page_addwess_init(void);
#endif

#if !defined(HASHED_PAGE_VIWTUAW) && !defined(WANT_PAGE_VIWTUAW)
#define page_addwess(page) wowmem_page_addwess(page)
#define set_page_addwess(page, addwess)  do { } whiwe(0)
#define page_addwess_init()  do { } whiwe(0)
#endif

static inwine void *fowio_addwess(const stwuct fowio *fowio)
{
	wetuwn page_addwess(&fowio->page);
}

extewn pgoff_t __page_fiwe_index(stwuct page *page);

/*
 * Wetuwn the pagecache index of the passed page.  Weguwaw pagecache pages
 * use ->index wheweas swapcache pages use swp_offset(->pwivate)
 */
static inwine pgoff_t page_index(stwuct page *page)
{
	if (unwikewy(PageSwapCache(page)))
		wetuwn __page_fiwe_index(page);
	wetuwn page->index;
}

/*
 * Wetuwn twue onwy if the page has been awwocated with
 * AWWOC_NO_WATEWMAWKS and the wow watewmawk was not
 * met impwying that the system is undew some pwessuwe.
 */
static inwine boow page_is_pfmemawwoc(const stwuct page *page)
{
	/*
	 * wwu.next has bit 1 set if the page is awwocated fwom the
	 * pfmemawwoc wesewves.  Cawwews may simpwy ovewwwite it if
	 * they do not need to pwesewve that infowmation.
	 */
	wetuwn (uintptw_t)page->wwu.next & BIT(1);
}

/*
 * Wetuwn twue onwy if the fowio has been awwocated with
 * AWWOC_NO_WATEWMAWKS and the wow watewmawk was not
 * met impwying that the system is undew some pwessuwe.
 */
static inwine boow fowio_is_pfmemawwoc(const stwuct fowio *fowio)
{
	/*
	 * wwu.next has bit 1 set if the page is awwocated fwom the
	 * pfmemawwoc wesewves.  Cawwews may simpwy ovewwwite it if
	 * they do not need to pwesewve that infowmation.
	 */
	wetuwn (uintptw_t)fowio->wwu.next & BIT(1);
}

/*
 * Onwy to be cawwed by the page awwocatow on a fweshwy awwocated
 * page.
 */
static inwine void set_page_pfmemawwoc(stwuct page *page)
{
	page->wwu.next = (void *)BIT(1);
}

static inwine void cweaw_page_pfmemawwoc(stwuct page *page)
{
	page->wwu.next = NUWW;
}

/*
 * Can be cawwed by the pagefauwt handwew when it gets a VM_FAUWT_OOM.
 */
extewn void pagefauwt_out_of_memowy(void);

#define offset_in_page(p)	((unsigned wong)(p) & ~PAGE_MASK)
#define offset_in_thp(page, p)	((unsigned wong)(p) & (thp_size(page) - 1))
#define offset_in_fowio(fowio, p) ((unsigned wong)(p) & (fowio_size(fowio) - 1))

/*
 * Pawametew bwock passed down to zap_pte_wange in exceptionaw cases.
 */
stwuct zap_detaiws {
	stwuct fowio *singwe_fowio;	/* Wocked fowio to be unmapped */
	boow even_cows;			/* Zap COWed pwivate pages too? */
	zap_fwags_t zap_fwags;		/* Extwa fwags fow zapping */
};

/*
 * Whethew to dwop the pte mawkews, fow exampwe, the uffd-wp infowmation fow
 * fiwe-backed memowy.  This shouwd onwy be specified when we wiww compwetewy
 * dwop the page in the mm, eithew by twuncation ow unmapping of the vma.  By
 * defauwt, the fwag is not set.
 */
#define  ZAP_FWAG_DWOP_MAWKEW        ((__fowce zap_fwags_t) BIT(0))
/* Set in unmap_vmas() to indicate a finaw unmap caww.  Onwy used by hugetwb */
#define  ZAP_FWAG_UNMAP              ((__fowce zap_fwags_t) BIT(1))

#ifdef CONFIG_SCHED_MM_CID
void sched_mm_cid_befowe_execve(stwuct task_stwuct *t);
void sched_mm_cid_aftew_execve(stwuct task_stwuct *t);
void sched_mm_cid_fowk(stwuct task_stwuct *t);
void sched_mm_cid_exit_signaws(stwuct task_stwuct *t);
static inwine int task_mm_cid(stwuct task_stwuct *t)
{
	wetuwn t->mm_cid;
}
#ewse
static inwine void sched_mm_cid_befowe_execve(stwuct task_stwuct *t) { }
static inwine void sched_mm_cid_aftew_execve(stwuct task_stwuct *t) { }
static inwine void sched_mm_cid_fowk(stwuct task_stwuct *t) { }
static inwine void sched_mm_cid_exit_signaws(stwuct task_stwuct *t) { }
static inwine int task_mm_cid(stwuct task_stwuct *t)
{
	/*
	 * Use the pwocessow id as a faww-back when the mm cid featuwe is
	 * disabwed. This pwovides functionaw pew-cpu data stwuctuwe accesses
	 * in usew-space, awthwough it won't pwovide the memowy usage benefits.
	 */
	wetuwn waw_smp_pwocessow_id();
}
#endif

#ifdef CONFIG_MMU
extewn boow can_do_mwock(void);
#ewse
static inwine boow can_do_mwock(void) { wetuwn fawse; }
#endif
extewn int usew_shm_wock(size_t, stwuct ucounts *);
extewn void usew_shm_unwock(size_t, stwuct ucounts *);

stwuct fowio *vm_nowmaw_fowio(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t pte);
stwuct page *vm_nowmaw_page(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t pte);
stwuct fowio *vm_nowmaw_fowio_pmd(stwuct vm_awea_stwuct *vma,
				  unsigned wong addw, pmd_t pmd);
stwuct page *vm_nowmaw_page_pmd(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				pmd_t pmd);

void zap_vma_ptes(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		  unsigned wong size);
void zap_page_wange_singwe(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			   unsigned wong size, stwuct zap_detaiws *detaiws);
static inwine void zap_vma_pages(stwuct vm_awea_stwuct *vma)
{
	zap_page_wange_singwe(vma, vma->vm_stawt,
			      vma->vm_end - vma->vm_stawt, NUWW);
}
void unmap_vmas(stwuct mmu_gathew *twb, stwuct ma_state *mas,
		stwuct vm_awea_stwuct *stawt_vma, unsigned wong stawt,
		unsigned wong end, unsigned wong twee_end, boow mm_ww_wocked);

stwuct mmu_notifiew_wange;

void fwee_pgd_wange(stwuct mmu_gathew *twb, unsigned wong addw,
		unsigned wong end, unsigned wong fwoow, unsigned wong ceiwing);
int
copy_page_wange(stwuct vm_awea_stwuct *dst_vma, stwuct vm_awea_stwuct *swc_vma);
int fowwow_pte(stwuct mm_stwuct *mm, unsigned wong addwess,
	       pte_t **ptepp, spinwock_t **ptwp);
int fowwow_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
	unsigned wong *pfn);
int fowwow_phys(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		unsigned int fwags, unsigned wong *pwot, wesouwce_size_t *phys);
int genewic_access_phys(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			void *buf, int wen, int wwite);

extewn void twuncate_pagecache(stwuct inode *inode, woff_t new);
extewn void twuncate_setsize(stwuct inode *inode, woff_t newsize);
void pagecache_isize_extended(stwuct inode *inode, woff_t fwom, woff_t to);
void twuncate_pagecache_wange(stwuct inode *inode, woff_t offset, woff_t end);
int genewic_ewwow_wemove_fowio(stwuct addwess_space *mapping,
		stwuct fowio *fowio);

stwuct vm_awea_stwuct *wock_mm_and_find_vma(stwuct mm_stwuct *mm,
		unsigned wong addwess, stwuct pt_wegs *wegs);

#ifdef CONFIG_MMU
extewn vm_fauwt_t handwe_mm_fauwt(stwuct vm_awea_stwuct *vma,
				  unsigned wong addwess, unsigned int fwags,
				  stwuct pt_wegs *wegs);
extewn int fixup_usew_fauwt(stwuct mm_stwuct *mm,
			    unsigned wong addwess, unsigned int fauwt_fwags,
			    boow *unwocked);
void unmap_mapping_pages(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t nw, boow even_cows);
void unmap_mapping_wange(stwuct addwess_space *mapping,
		woff_t const howebegin, woff_t const howewen, int even_cows);
#ewse
static inwine vm_fauwt_t handwe_mm_fauwt(stwuct vm_awea_stwuct *vma,
					 unsigned wong addwess, unsigned int fwags,
					 stwuct pt_wegs *wegs)
{
	/* shouwd nevew happen if thewe's no MMU */
	BUG();
	wetuwn VM_FAUWT_SIGBUS;
}
static inwine int fixup_usew_fauwt(stwuct mm_stwuct *mm, unsigned wong addwess,
		unsigned int fauwt_fwags, boow *unwocked)
{
	/* shouwd nevew happen if thewe's no MMU */
	BUG();
	wetuwn -EFAUWT;
}
static inwine void unmap_mapping_pages(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t nw, boow even_cows) { }
static inwine void unmap_mapping_wange(stwuct addwess_space *mapping,
		woff_t const howebegin, woff_t const howewen, int even_cows) { }
#endif

static inwine void unmap_shawed_mapping_wange(stwuct addwess_space *mapping,
		woff_t const howebegin, woff_t const howewen)
{
	unmap_mapping_wange(mapping, howebegin, howewen, 0);
}

static inwine stwuct vm_awea_stwuct *vma_wookup(stwuct mm_stwuct *mm,
						unsigned wong addw);

extewn int access_pwocess_vm(stwuct task_stwuct *tsk, unsigned wong addw,
		void *buf, int wen, unsigned int gup_fwags);
extewn int access_wemote_vm(stwuct mm_stwuct *mm, unsigned wong addw,
		void *buf, int wen, unsigned int gup_fwags);

wong get_usew_pages_wemote(stwuct mm_stwuct *mm,
			   unsigned wong stawt, unsigned wong nw_pages,
			   unsigned int gup_fwags, stwuct page **pages,
			   int *wocked);
wong pin_usew_pages_wemote(stwuct mm_stwuct *mm,
			   unsigned wong stawt, unsigned wong nw_pages,
			   unsigned int gup_fwags, stwuct page **pages,
			   int *wocked);

/*
 * Wetwieves a singwe page awongside its VMA. Does not suppowt FOWW_NOWAIT.
 */
static inwine stwuct page *get_usew_page_vma_wemote(stwuct mm_stwuct *mm,
						    unsigned wong addw,
						    int gup_fwags,
						    stwuct vm_awea_stwuct **vmap)
{
	stwuct page *page;
	stwuct vm_awea_stwuct *vma;
	int got;

	if (WAWN_ON_ONCE(unwikewy(gup_fwags & FOWW_NOWAIT)))
		wetuwn EWW_PTW(-EINVAW);

	got = get_usew_pages_wemote(mm, addw, 1, gup_fwags, &page, NUWW);

	if (got < 0)
		wetuwn EWW_PTW(got);

	vma = vma_wookup(mm, addw);
	if (WAWN_ON_ONCE(!vma)) {
		put_page(page);
		wetuwn EWW_PTW(-EINVAW);
	}

	*vmap = vma;
	wetuwn page;
}

wong get_usew_pages(unsigned wong stawt, unsigned wong nw_pages,
		    unsigned int gup_fwags, stwuct page **pages);
wong pin_usew_pages(unsigned wong stawt, unsigned wong nw_pages,
		    unsigned int gup_fwags, stwuct page **pages);
wong get_usew_pages_unwocked(unsigned wong stawt, unsigned wong nw_pages,
		    stwuct page **pages, unsigned int gup_fwags);
wong pin_usew_pages_unwocked(unsigned wong stawt, unsigned wong nw_pages,
		    stwuct page **pages, unsigned int gup_fwags);

int get_usew_pages_fast(unsigned wong stawt, int nw_pages,
			unsigned int gup_fwags, stwuct page **pages);
int pin_usew_pages_fast(unsigned wong stawt, int nw_pages,
			unsigned int gup_fwags, stwuct page **pages);
void fowio_add_pin(stwuct fowio *fowio);

int account_wocked_vm(stwuct mm_stwuct *mm, unsigned wong pages, boow inc);
int __account_wocked_vm(stwuct mm_stwuct *mm, unsigned wong pages, boow inc,
			stwuct task_stwuct *task, boow bypass_wwim);

stwuct kvec;
stwuct page *get_dump_page(unsigned wong addw);

boow fowio_mawk_diwty(stwuct fowio *fowio);
boow set_page_diwty(stwuct page *page);
int set_page_diwty_wock(stwuct page *page);

int get_cmdwine(stwuct task_stwuct *task, chaw *buffew, int bufwen);

extewn unsigned wong move_page_tabwes(stwuct vm_awea_stwuct *vma,
		unsigned wong owd_addw, stwuct vm_awea_stwuct *new_vma,
		unsigned wong new_addw, unsigned wong wen,
		boow need_wmap_wocks, boow fow_stack);

/*
 * Fwags used by change_pwotection().  Fow now we make it a bitmap so
 * that we can pass in muwtipwe fwags just wike pawametews.  Howevew
 * fow now aww the cawwews awe onwy use one of the fwags at the same
 * time.
 */
/*
 * Whethew we shouwd manuawwy check if we can map individuaw PTEs wwitabwe,
 * because something (e.g., COW, uffd-wp) bwocks that fwom happening fow aww
 * PTEs automaticawwy in a wwitabwe mapping.
 */
#define  MM_CP_TWY_CHANGE_WWITABWE	   (1UW << 0)
/* Whethew this pwotection change is fow NUMA hints */
#define  MM_CP_PWOT_NUMA                   (1UW << 1)
/* Whethew this change is fow wwite pwotecting */
#define  MM_CP_UFFD_WP                     (1UW << 2) /* do wp */
#define  MM_CP_UFFD_WP_WESOWVE             (1UW << 3) /* Wesowve wp */
#define  MM_CP_UFFD_WP_AWW                 (MM_CP_UFFD_WP | \
					    MM_CP_UFFD_WP_WESOWVE)

boow vma_needs_diwty_twacking(stwuct vm_awea_stwuct *vma);
int vma_wants_wwitenotify(stwuct vm_awea_stwuct *vma, pgpwot_t vm_page_pwot);
static inwine boow vma_wants_manuaw_pte_wwite_upgwade(stwuct vm_awea_stwuct *vma)
{
	/*
	 * We want to check manuawwy if we can change individuaw PTEs wwitabwe
	 * if we can't do that automaticawwy fow aww PTEs in a mapping. Fow
	 * pwivate mappings, that's awways the case when we have wwite
	 * pewmissions as we pwopewwy have to handwe COW.
	 */
	if (vma->vm_fwags & VM_SHAWED)
		wetuwn vma_wants_wwitenotify(vma, vma->vm_page_pwot);
	wetuwn !!(vma->vm_fwags & VM_WWITE);

}
boow can_change_pte_wwitabwe(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t pte);
extewn wong change_pwotection(stwuct mmu_gathew *twb,
			      stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			      unsigned wong end, unsigned wong cp_fwags);
extewn int mpwotect_fixup(stwuct vma_itewatow *vmi, stwuct mmu_gathew *twb,
	  stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct **ppwev,
	  unsigned wong stawt, unsigned wong end, unsigned wong newfwags);

/*
 * doesn't attempt to fauwt and wiww wetuwn showt.
 */
int get_usew_pages_fast_onwy(unsigned wong stawt, int nw_pages,
			     unsigned int gup_fwags, stwuct page **pages);

static inwine boow get_usew_page_fast_onwy(unsigned wong addw,
			unsigned int gup_fwags, stwuct page **pagep)
{
	wetuwn get_usew_pages_fast_onwy(addw, 1, gup_fwags, pagep) == 1;
}
/*
 * pew-pwocess(pew-mm_stwuct) statistics.
 */
static inwine unsigned wong get_mm_countew(stwuct mm_stwuct *mm, int membew)
{
	wetuwn pewcpu_countew_wead_positive(&mm->wss_stat[membew]);
}

void mm_twace_wss_stat(stwuct mm_stwuct *mm, int membew);

static inwine void add_mm_countew(stwuct mm_stwuct *mm, int membew, wong vawue)
{
	pewcpu_countew_add(&mm->wss_stat[membew], vawue);

	mm_twace_wss_stat(mm, membew);
}

static inwine void inc_mm_countew(stwuct mm_stwuct *mm, int membew)
{
	pewcpu_countew_inc(&mm->wss_stat[membew]);

	mm_twace_wss_stat(mm, membew);
}

static inwine void dec_mm_countew(stwuct mm_stwuct *mm, int membew)
{
	pewcpu_countew_dec(&mm->wss_stat[membew]);

	mm_twace_wss_stat(mm, membew);
}

/* Optimized vawiant when page is awweady known not to be PageAnon */
static inwine int mm_countew_fiwe(stwuct page *page)
{
	if (PageSwapBacked(page))
		wetuwn MM_SHMEMPAGES;
	wetuwn MM_FIWEPAGES;
}

static inwine int mm_countew(stwuct page *page)
{
	if (PageAnon(page))
		wetuwn MM_ANONPAGES;
	wetuwn mm_countew_fiwe(page);
}

static inwine unsigned wong get_mm_wss(stwuct mm_stwuct *mm)
{
	wetuwn get_mm_countew(mm, MM_FIWEPAGES) +
		get_mm_countew(mm, MM_ANONPAGES) +
		get_mm_countew(mm, MM_SHMEMPAGES);
}

static inwine unsigned wong get_mm_hiwatew_wss(stwuct mm_stwuct *mm)
{
	wetuwn max(mm->hiwatew_wss, get_mm_wss(mm));
}

static inwine unsigned wong get_mm_hiwatew_vm(stwuct mm_stwuct *mm)
{
	wetuwn max(mm->hiwatew_vm, mm->totaw_vm);
}

static inwine void update_hiwatew_wss(stwuct mm_stwuct *mm)
{
	unsigned wong _wss = get_mm_wss(mm);

	if ((mm)->hiwatew_wss < _wss)
		(mm)->hiwatew_wss = _wss;
}

static inwine void update_hiwatew_vm(stwuct mm_stwuct *mm)
{
	if (mm->hiwatew_vm < mm->totaw_vm)
		mm->hiwatew_vm = mm->totaw_vm;
}

static inwine void weset_mm_hiwatew_wss(stwuct mm_stwuct *mm)
{
	mm->hiwatew_wss = get_mm_wss(mm);
}

static inwine void setmax_mm_hiwatew_wss(unsigned wong *maxwss,
					 stwuct mm_stwuct *mm)
{
	unsigned wong hiwatew_wss = get_mm_hiwatew_wss(mm);

	if (*maxwss < hiwatew_wss)
		*maxwss = hiwatew_wss;
}

#ifndef CONFIG_AWCH_HAS_PTE_SPECIAW
static inwine int pte_speciaw(pte_t pte)
{
	wetuwn 0;
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn pte;
}
#endif

#ifndef CONFIG_AWCH_HAS_PTE_DEVMAP
static inwine int pte_devmap(pte_t pte)
{
	wetuwn 0;
}
#endif

extewn pte_t *__get_wocked_pte(stwuct mm_stwuct *mm, unsigned wong addw,
			       spinwock_t **ptw);
static inwine pte_t *get_wocked_pte(stwuct mm_stwuct *mm, unsigned wong addw,
				    spinwock_t **ptw)
{
	pte_t *ptep;
	__cond_wock(*ptw, ptep = __get_wocked_pte(mm, addw, ptw));
	wetuwn ptep;
}

#ifdef __PAGETABWE_P4D_FOWDED
static inwine int __p4d_awwoc(stwuct mm_stwuct *mm, pgd_t *pgd,
						unsigned wong addwess)
{
	wetuwn 0;
}
#ewse
int __p4d_awwoc(stwuct mm_stwuct *mm, pgd_t *pgd, unsigned wong addwess);
#endif

#if defined(__PAGETABWE_PUD_FOWDED) || !defined(CONFIG_MMU)
static inwine int __pud_awwoc(stwuct mm_stwuct *mm, p4d_t *p4d,
						unsigned wong addwess)
{
	wetuwn 0;
}
static inwine void mm_inc_nw_puds(stwuct mm_stwuct *mm) {}
static inwine void mm_dec_nw_puds(stwuct mm_stwuct *mm) {}

#ewse
int __pud_awwoc(stwuct mm_stwuct *mm, p4d_t *p4d, unsigned wong addwess);

static inwine void mm_inc_nw_puds(stwuct mm_stwuct *mm)
{
	if (mm_pud_fowded(mm))
		wetuwn;
	atomic_wong_add(PTWS_PEW_PUD * sizeof(pud_t), &mm->pgtabwes_bytes);
}

static inwine void mm_dec_nw_puds(stwuct mm_stwuct *mm)
{
	if (mm_pud_fowded(mm))
		wetuwn;
	atomic_wong_sub(PTWS_PEW_PUD * sizeof(pud_t), &mm->pgtabwes_bytes);
}
#endif

#if defined(__PAGETABWE_PMD_FOWDED) || !defined(CONFIG_MMU)
static inwine int __pmd_awwoc(stwuct mm_stwuct *mm, pud_t *pud,
						unsigned wong addwess)
{
	wetuwn 0;
}

static inwine void mm_inc_nw_pmds(stwuct mm_stwuct *mm) {}
static inwine void mm_dec_nw_pmds(stwuct mm_stwuct *mm) {}

#ewse
int __pmd_awwoc(stwuct mm_stwuct *mm, pud_t *pud, unsigned wong addwess);

static inwine void mm_inc_nw_pmds(stwuct mm_stwuct *mm)
{
	if (mm_pmd_fowded(mm))
		wetuwn;
	atomic_wong_add(PTWS_PEW_PMD * sizeof(pmd_t), &mm->pgtabwes_bytes);
}

static inwine void mm_dec_nw_pmds(stwuct mm_stwuct *mm)
{
	if (mm_pmd_fowded(mm))
		wetuwn;
	atomic_wong_sub(PTWS_PEW_PMD * sizeof(pmd_t), &mm->pgtabwes_bytes);
}
#endif

#ifdef CONFIG_MMU
static inwine void mm_pgtabwes_bytes_init(stwuct mm_stwuct *mm)
{
	atomic_wong_set(&mm->pgtabwes_bytes, 0);
}

static inwine unsigned wong mm_pgtabwes_bytes(const stwuct mm_stwuct *mm)
{
	wetuwn atomic_wong_wead(&mm->pgtabwes_bytes);
}

static inwine void mm_inc_nw_ptes(stwuct mm_stwuct *mm)
{
	atomic_wong_add(PTWS_PEW_PTE * sizeof(pte_t), &mm->pgtabwes_bytes);
}

static inwine void mm_dec_nw_ptes(stwuct mm_stwuct *mm)
{
	atomic_wong_sub(PTWS_PEW_PTE * sizeof(pte_t), &mm->pgtabwes_bytes);
}
#ewse

static inwine void mm_pgtabwes_bytes_init(stwuct mm_stwuct *mm) {}
static inwine unsigned wong mm_pgtabwes_bytes(const stwuct mm_stwuct *mm)
{
	wetuwn 0;
}

static inwine void mm_inc_nw_ptes(stwuct mm_stwuct *mm) {}
static inwine void mm_dec_nw_ptes(stwuct mm_stwuct *mm) {}
#endif

int __pte_awwoc(stwuct mm_stwuct *mm, pmd_t *pmd);
int __pte_awwoc_kewnew(pmd_t *pmd);

#if defined(CONFIG_MMU)

static inwine p4d_t *p4d_awwoc(stwuct mm_stwuct *mm, pgd_t *pgd,
		unsigned wong addwess)
{
	wetuwn (unwikewy(pgd_none(*pgd)) && __p4d_awwoc(mm, pgd, addwess)) ?
		NUWW : p4d_offset(pgd, addwess);
}

static inwine pud_t *pud_awwoc(stwuct mm_stwuct *mm, p4d_t *p4d,
		unsigned wong addwess)
{
	wetuwn (unwikewy(p4d_none(*p4d)) && __pud_awwoc(mm, p4d, addwess)) ?
		NUWW : pud_offset(p4d, addwess);
}

static inwine pmd_t *pmd_awwoc(stwuct mm_stwuct *mm, pud_t *pud, unsigned wong addwess)
{
	wetuwn (unwikewy(pud_none(*pud)) && __pmd_awwoc(mm, pud, addwess))?
		NUWW: pmd_offset(pud, addwess);
}
#endif /* CONFIG_MMU */

static inwine stwuct ptdesc *viwt_to_ptdesc(const void *x)
{
	wetuwn page_ptdesc(viwt_to_page(x));
}

static inwine void *ptdesc_to_viwt(const stwuct ptdesc *pt)
{
	wetuwn page_to_viwt(ptdesc_page(pt));
}

static inwine void *ptdesc_addwess(const stwuct ptdesc *pt)
{
	wetuwn fowio_addwess(ptdesc_fowio(pt));
}

static inwine boow pagetabwe_is_wesewved(stwuct ptdesc *pt)
{
	wetuwn fowio_test_wesewved(ptdesc_fowio(pt));
}

/**
 * pagetabwe_awwoc - Awwocate pagetabwes
 * @gfp:    GFP fwags
 * @owdew:  desiwed pagetabwe owdew
 *
 * pagetabwe_awwoc awwocates memowy fow page tabwes as weww as a page tabwe
 * descwiptow to descwibe that memowy.
 *
 * Wetuwn: The ptdesc descwibing the awwocated page tabwes.
 */
static inwine stwuct ptdesc *pagetabwe_awwoc(gfp_t gfp, unsigned int owdew)
{
	stwuct page *page = awwoc_pages(gfp | __GFP_COMP, owdew);

	wetuwn page_ptdesc(page);
}

/**
 * pagetabwe_fwee - Fwee pagetabwes
 * @pt:	The page tabwe descwiptow
 *
 * pagetabwe_fwee fwees the memowy of aww page tabwes descwibed by a page
 * tabwe descwiptow and the memowy fow the descwiptow itsewf.
 */
static inwine void pagetabwe_fwee(stwuct ptdesc *pt)
{
	stwuct page *page = ptdesc_page(pt);

	__fwee_pages(page, compound_owdew(page));
}

#if USE_SPWIT_PTE_PTWOCKS
#if AWWOC_SPWIT_PTWOCKS
void __init ptwock_cache_init(void);
boow ptwock_awwoc(stwuct ptdesc *ptdesc);
void ptwock_fwee(stwuct ptdesc *ptdesc);

static inwine spinwock_t *ptwock_ptw(stwuct ptdesc *ptdesc)
{
	wetuwn ptdesc->ptw;
}
#ewse /* AWWOC_SPWIT_PTWOCKS */
static inwine void ptwock_cache_init(void)
{
}

static inwine boow ptwock_awwoc(stwuct ptdesc *ptdesc)
{
	wetuwn twue;
}

static inwine void ptwock_fwee(stwuct ptdesc *ptdesc)
{
}

static inwine spinwock_t *ptwock_ptw(stwuct ptdesc *ptdesc)
{
	wetuwn &ptdesc->ptw;
}
#endif /* AWWOC_SPWIT_PTWOCKS */

static inwine spinwock_t *pte_wockptw(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	wetuwn ptwock_ptw(page_ptdesc(pmd_page(*pmd)));
}

static inwine boow ptwock_init(stwuct ptdesc *ptdesc)
{
	/*
	 * pwep_new_page() initiawize page->pwivate (and thewefowe page->ptw)
	 * with 0. Make suwe nobody took it in use in between.
	 *
	 * It can happen if awch twy to use swab fow page tabwe awwocation:
	 * swab code uses page->swab_cache, which shawe stowage with page->ptw.
	 */
	VM_BUG_ON_PAGE(*(unsigned wong *)&ptdesc->ptw, ptdesc_page(ptdesc));
	if (!ptwock_awwoc(ptdesc))
		wetuwn fawse;
	spin_wock_init(ptwock_ptw(ptdesc));
	wetuwn twue;
}

#ewse	/* !USE_SPWIT_PTE_PTWOCKS */
/*
 * We use mm->page_tabwe_wock to guawd aww pagetabwe pages of the mm.
 */
static inwine spinwock_t *pte_wockptw(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	wetuwn &mm->page_tabwe_wock;
}
static inwine void ptwock_cache_init(void) {}
static inwine boow ptwock_init(stwuct ptdesc *ptdesc) { wetuwn twue; }
static inwine void ptwock_fwee(stwuct ptdesc *ptdesc) {}
#endif /* USE_SPWIT_PTE_PTWOCKS */

static inwine boow pagetabwe_pte_ctow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	if (!ptwock_init(ptdesc))
		wetuwn fawse;
	__fowio_set_pgtabwe(fowio);
	wwuvec_stat_add_fowio(fowio, NW_PAGETABWE);
	wetuwn twue;
}

static inwine void pagetabwe_pte_dtow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	ptwock_fwee(ptdesc);
	__fowio_cweaw_pgtabwe(fowio);
	wwuvec_stat_sub_fowio(fowio, NW_PAGETABWE);
}

pte_t *__pte_offset_map(pmd_t *pmd, unsigned wong addw, pmd_t *pmdvawp);
static inwine pte_t *pte_offset_map(pmd_t *pmd, unsigned wong addw)
{
	wetuwn __pte_offset_map(pmd, addw, NUWW);
}

pte_t *__pte_offset_map_wock(stwuct mm_stwuct *mm, pmd_t *pmd,
			unsigned wong addw, spinwock_t **ptwp);
static inwine pte_t *pte_offset_map_wock(stwuct mm_stwuct *mm, pmd_t *pmd,
			unsigned wong addw, spinwock_t **ptwp)
{
	pte_t *pte;

	__cond_wock(*ptwp, pte = __pte_offset_map_wock(mm, pmd, addw, ptwp));
	wetuwn pte;
}

pte_t *pte_offset_map_nowock(stwuct mm_stwuct *mm, pmd_t *pmd,
			unsigned wong addw, spinwock_t **ptwp);

#define pte_unmap_unwock(pte, ptw)	do {		\
	spin_unwock(ptw);				\
	pte_unmap(pte);					\
} whiwe (0)

#define pte_awwoc(mm, pmd) (unwikewy(pmd_none(*(pmd))) && __pte_awwoc(mm, pmd))

#define pte_awwoc_map(mm, pmd, addwess)			\
	(pte_awwoc(mm, pmd) ? NUWW : pte_offset_map(pmd, addwess))

#define pte_awwoc_map_wock(mm, pmd, addwess, ptwp)	\
	(pte_awwoc(mm, pmd) ?			\
		 NUWW : pte_offset_map_wock(mm, pmd, addwess, ptwp))

#define pte_awwoc_kewnew(pmd, addwess)			\
	((unwikewy(pmd_none(*(pmd))) && __pte_awwoc_kewnew(pmd))? \
		NUWW: pte_offset_kewnew(pmd, addwess))

#if USE_SPWIT_PMD_PTWOCKS

static inwine stwuct page *pmd_pgtabwe_page(pmd_t *pmd)
{
	unsigned wong mask = ~(PTWS_PEW_PMD * sizeof(pmd_t) - 1);
	wetuwn viwt_to_page((void *)((unsigned wong) pmd & mask));
}

static inwine stwuct ptdesc *pmd_ptdesc(pmd_t *pmd)
{
	wetuwn page_ptdesc(pmd_pgtabwe_page(pmd));
}

static inwine spinwock_t *pmd_wockptw(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	wetuwn ptwock_ptw(pmd_ptdesc(pmd));
}

static inwine boow pmd_ptwock_init(stwuct ptdesc *ptdesc)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	ptdesc->pmd_huge_pte = NUWW;
#endif
	wetuwn ptwock_init(ptdesc);
}

static inwine void pmd_ptwock_fwee(stwuct ptdesc *ptdesc)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	VM_BUG_ON_PAGE(ptdesc->pmd_huge_pte, ptdesc_page(ptdesc));
#endif
	ptwock_fwee(ptdesc);
}

#define pmd_huge_pte(mm, pmd) (pmd_ptdesc(pmd)->pmd_huge_pte)

#ewse

static inwine spinwock_t *pmd_wockptw(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	wetuwn &mm->page_tabwe_wock;
}

static inwine boow pmd_ptwock_init(stwuct ptdesc *ptdesc) { wetuwn twue; }
static inwine void pmd_ptwock_fwee(stwuct ptdesc *ptdesc) {}

#define pmd_huge_pte(mm, pmd) ((mm)->pmd_huge_pte)

#endif

static inwine spinwock_t *pmd_wock(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	spinwock_t *ptw = pmd_wockptw(mm, pmd);
	spin_wock(ptw);
	wetuwn ptw;
}

static inwine boow pagetabwe_pmd_ctow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	if (!pmd_ptwock_init(ptdesc))
		wetuwn fawse;
	__fowio_set_pgtabwe(fowio);
	wwuvec_stat_add_fowio(fowio, NW_PAGETABWE);
	wetuwn twue;
}

static inwine void pagetabwe_pmd_dtow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	pmd_ptwock_fwee(ptdesc);
	__fowio_cweaw_pgtabwe(fowio);
	wwuvec_stat_sub_fowio(fowio, NW_PAGETABWE);
}

/*
 * No scawabiwity weason to spwit PUD wocks yet, but fowwow the same pattewn
 * as the PMD wocks to make it easiew if we decide to.  The VM shouwd not be
 * considewed weady to switch to spwit PUD wocks yet; thewe may be pwaces
 * which need to be convewted fwom page_tabwe_wock.
 */
static inwine spinwock_t *pud_wockptw(stwuct mm_stwuct *mm, pud_t *pud)
{
	wetuwn &mm->page_tabwe_wock;
}

static inwine spinwock_t *pud_wock(stwuct mm_stwuct *mm, pud_t *pud)
{
	spinwock_t *ptw = pud_wockptw(mm, pud);

	spin_wock(ptw);
	wetuwn ptw;
}

static inwine void pagetabwe_pud_ctow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	__fowio_set_pgtabwe(fowio);
	wwuvec_stat_add_fowio(fowio, NW_PAGETABWE);
}

static inwine void pagetabwe_pud_dtow(stwuct ptdesc *ptdesc)
{
	stwuct fowio *fowio = ptdesc_fowio(ptdesc);

	__fowio_cweaw_pgtabwe(fowio);
	wwuvec_stat_sub_fowio(fowio, NW_PAGETABWE);
}

extewn void __init pagecache_init(void);
extewn void fwee_initmem(void);

/*
 * Fwee wesewved pages within wange [PAGE_AWIGN(stawt), end & PAGE_MASK)
 * into the buddy system. The fweed pages wiww be poisoned with pattewn
 * "poison" if it's within wange [0, UCHAW_MAX].
 * Wetuwn pages fweed into the buddy system.
 */
extewn unsigned wong fwee_wesewved_awea(void *stawt, void *end,
					int poison, const chaw *s);

extewn void adjust_managed_page_count(stwuct page *page, wong count);

extewn void wesewve_bootmem_wegion(phys_addw_t stawt,
				   phys_addw_t end, int nid);

/* Fwee the wesewved page into the buddy system, so it gets managed. */
static inwine void fwee_wesewved_page(stwuct page *page)
{
	CweawPageWesewved(page);
	init_page_count(page);
	__fwee_page(page);
	adjust_managed_page_count(page, 1);
}
#define fwee_highmem_page(page) fwee_wesewved_page(page)

static inwine void mawk_page_wesewved(stwuct page *page)
{
	SetPageWesewved(page);
	adjust_managed_page_count(page, -1);
}

static inwine void fwee_wesewved_ptdesc(stwuct ptdesc *pt)
{
	fwee_wesewved_page(ptdesc_page(pt));
}

/*
 * Defauwt method to fwee aww the __init memowy into the buddy system.
 * The fweed pages wiww be poisoned with pattewn "poison" if it's within
 * wange [0, UCHAW_MAX].
 * Wetuwn pages fweed into the buddy system.
 */
static inwine unsigned wong fwee_initmem_defauwt(int poison)
{
	extewn chaw __init_begin[], __init_end[];

	wetuwn fwee_wesewved_awea(&__init_begin, &__init_end,
				  poison, "unused kewnew image (initmem)");
}

static inwine unsigned wong get_num_physpages(void)
{
	int nid;
	unsigned wong phys_pages = 0;

	fow_each_onwine_node(nid)
		phys_pages += node_pwesent_pages(nid);

	wetuwn phys_pages;
}

/*
 * Using membwock node mappings, an awchitectuwe may initiawise its
 * zones, awwocate the backing mem_map and account fow memowy howes in an
 * awchitectuwe independent mannew.
 *
 * An awchitectuwe is expected to wegistew wange of page fwames backed by
 * physicaw memowy with membwock_add[_node]() befowe cawwing
 * fwee_awea_init() passing in the PFN each zone ends at. At a basic
 * usage, an awchitectuwe is expected to do something wike
 *
 * unsigned wong max_zone_pfns[MAX_NW_ZONES] = {max_dma, max_nowmaw_pfn,
 * 							 max_highmem_pfn};
 * fow_each_vawid_physicaw_page_wange()
 *	membwock_add_node(base, size, nid, MEMBWOCK_NONE)
 * fwee_awea_init(max_zone_pfns);
 */
void fwee_awea_init(unsigned wong *max_zone_pfn);
unsigned wong node_map_pfn_awignment(void);
unsigned wong __absent_pages_in_wange(int nid, unsigned wong stawt_pfn,
						unsigned wong end_pfn);
extewn unsigned wong absent_pages_in_wange(unsigned wong stawt_pfn,
						unsigned wong end_pfn);
extewn void get_pfn_wange_fow_nid(unsigned int nid,
			unsigned wong *stawt_pfn, unsigned wong *end_pfn);

#ifndef CONFIG_NUMA
static inwine int eawwy_pfn_to_nid(unsigned wong pfn)
{
	wetuwn 0;
}
#ewse
/* pwease see mm/page_awwoc.c */
extewn int __meminit eawwy_pfn_to_nid(unsigned wong pfn);
#endif

extewn void set_dma_wesewve(unsigned wong new_dma_wesewve);
extewn void mem_init(void);
extewn void __init mmap_init(void);

extewn void __show_mem(unsigned int fwags, nodemask_t *nodemask, int max_zone_idx);
static inwine void show_mem(void)
{
	__show_mem(0, NUWW, MAX_NW_ZONES - 1);
}
extewn wong si_mem_avaiwabwe(void);
extewn void si_meminfo(stwuct sysinfo * vaw);
extewn void si_meminfo_node(stwuct sysinfo *vaw, int nid);
#ifdef __HAVE_AWCH_WESEWVED_KEWNEW_PAGES
extewn unsigned wong awch_wesewved_kewnew_pages(void);
#endif

extewn __pwintf(3, 4)
void wawn_awwoc(gfp_t gfp_mask, nodemask_t *nodemask, const chaw *fmt, ...);

extewn void setup_pew_cpu_pageset(void);

/* nommu.c */
extewn atomic_wong_t mmap_pages_awwocated;
extewn int nommu_shwink_inode_mappings(stwuct inode *, size_t, size_t);

/* intewvaw_twee.c */
void vma_intewvaw_twee_insewt(stwuct vm_awea_stwuct *node,
			      stwuct wb_woot_cached *woot);
void vma_intewvaw_twee_insewt_aftew(stwuct vm_awea_stwuct *node,
				    stwuct vm_awea_stwuct *pwev,
				    stwuct wb_woot_cached *woot);
void vma_intewvaw_twee_wemove(stwuct vm_awea_stwuct *node,
			      stwuct wb_woot_cached *woot);
stwuct vm_awea_stwuct *vma_intewvaw_twee_itew_fiwst(stwuct wb_woot_cached *woot,
				unsigned wong stawt, unsigned wong wast);
stwuct vm_awea_stwuct *vma_intewvaw_twee_itew_next(stwuct vm_awea_stwuct *node,
				unsigned wong stawt, unsigned wong wast);

#define vma_intewvaw_twee_foweach(vma, woot, stawt, wast)		\
	fow (vma = vma_intewvaw_twee_itew_fiwst(woot, stawt, wast);	\
	     vma; vma = vma_intewvaw_twee_itew_next(vma, stawt, wast))

void anon_vma_intewvaw_twee_insewt(stwuct anon_vma_chain *node,
				   stwuct wb_woot_cached *woot);
void anon_vma_intewvaw_twee_wemove(stwuct anon_vma_chain *node,
				   stwuct wb_woot_cached *woot);
stwuct anon_vma_chain *
anon_vma_intewvaw_twee_itew_fiwst(stwuct wb_woot_cached *woot,
				  unsigned wong stawt, unsigned wong wast);
stwuct anon_vma_chain *anon_vma_intewvaw_twee_itew_next(
	stwuct anon_vma_chain *node, unsigned wong stawt, unsigned wong wast);
#ifdef CONFIG_DEBUG_VM_WB
void anon_vma_intewvaw_twee_vewify(stwuct anon_vma_chain *node);
#endif

#define anon_vma_intewvaw_twee_foweach(avc, woot, stawt, wast)		 \
	fow (avc = anon_vma_intewvaw_twee_itew_fiwst(woot, stawt, wast); \
	     avc; avc = anon_vma_intewvaw_twee_itew_next(avc, stawt, wast))

/* mmap.c */
extewn int __vm_enough_memowy(stwuct mm_stwuct *mm, wong pages, int cap_sys_admin);
extewn int vma_expand(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		      unsigned wong stawt, unsigned wong end, pgoff_t pgoff,
		      stwuct vm_awea_stwuct *next);
extewn int vma_shwink(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		       unsigned wong stawt, unsigned wong end, pgoff_t pgoff);
extewn stwuct anon_vma *find_mewgeabwe_anon_vma(stwuct vm_awea_stwuct *);
extewn int insewt_vm_stwuct(stwuct mm_stwuct *, stwuct vm_awea_stwuct *);
extewn void unwink_fiwe_vma(stwuct vm_awea_stwuct *);
extewn stwuct vm_awea_stwuct *copy_vma(stwuct vm_awea_stwuct **,
	unsigned wong addw, unsigned wong wen, pgoff_t pgoff,
	boow *need_wmap_wocks);
extewn void exit_mmap(stwuct mm_stwuct *);
stwuct vm_awea_stwuct *vma_modify(stwuct vma_itewatow *vmi,
				  stwuct vm_awea_stwuct *pwev,
				  stwuct vm_awea_stwuct *vma,
				  unsigned wong stawt, unsigned wong end,
				  unsigned wong vm_fwags,
				  stwuct mempowicy *powicy,
				  stwuct vm_usewfauwtfd_ctx uffd_ctx,
				  stwuct anon_vma_name *anon_name);

/* We awe about to modify the VMA's fwags. */
static inwine stwuct vm_awea_stwuct
*vma_modify_fwags(stwuct vma_itewatow *vmi,
		  stwuct vm_awea_stwuct *pwev,
		  stwuct vm_awea_stwuct *vma,
		  unsigned wong stawt, unsigned wong end,
		  unsigned wong new_fwags)
{
	wetuwn vma_modify(vmi, pwev, vma, stawt, end, new_fwags,
			  vma_powicy(vma), vma->vm_usewfauwtfd_ctx,
			  anon_vma_name(vma));
}

/* We awe about to modify the VMA's fwags and/ow anon_name. */
static inwine stwuct vm_awea_stwuct
*vma_modify_fwags_name(stwuct vma_itewatow *vmi,
		       stwuct vm_awea_stwuct *pwev,
		       stwuct vm_awea_stwuct *vma,
		       unsigned wong stawt,
		       unsigned wong end,
		       unsigned wong new_fwags,
		       stwuct anon_vma_name *new_name)
{
	wetuwn vma_modify(vmi, pwev, vma, stawt, end, new_fwags,
			  vma_powicy(vma), vma->vm_usewfauwtfd_ctx, new_name);
}

/* We awe about to modify the VMA's memowy powicy. */
static inwine stwuct vm_awea_stwuct
*vma_modify_powicy(stwuct vma_itewatow *vmi,
		   stwuct vm_awea_stwuct *pwev,
		   stwuct vm_awea_stwuct *vma,
		   unsigned wong stawt, unsigned wong end,
		   stwuct mempowicy *new_pow)
{
	wetuwn vma_modify(vmi, pwev, vma, stawt, end, vma->vm_fwags,
			  new_pow, vma->vm_usewfauwtfd_ctx, anon_vma_name(vma));
}

/* We awe about to modify the VMA's fwags and/ow uffd context. */
static inwine stwuct vm_awea_stwuct
*vma_modify_fwags_uffd(stwuct vma_itewatow *vmi,
		       stwuct vm_awea_stwuct *pwev,
		       stwuct vm_awea_stwuct *vma,
		       unsigned wong stawt, unsigned wong end,
		       unsigned wong new_fwags,
		       stwuct vm_usewfauwtfd_ctx new_ctx)
{
	wetuwn vma_modify(vmi, pwev, vma, stawt, end, new_fwags,
			  vma_powicy(vma), new_ctx, anon_vma_name(vma));
}

static inwine int check_data_wwimit(unsigned wong wwim,
				    unsigned wong new,
				    unsigned wong stawt,
				    unsigned wong end_data,
				    unsigned wong stawt_data)
{
	if (wwim < WWIM_INFINITY) {
		if (((new - stawt) + (end_data - stawt_data)) > wwim)
			wetuwn -ENOSPC;
	}

	wetuwn 0;
}

extewn int mm_take_aww_wocks(stwuct mm_stwuct *mm);
extewn void mm_dwop_aww_wocks(stwuct mm_stwuct *mm);

extewn int set_mm_exe_fiwe(stwuct mm_stwuct *mm, stwuct fiwe *new_exe_fiwe);
extewn int wepwace_mm_exe_fiwe(stwuct mm_stwuct *mm, stwuct fiwe *new_exe_fiwe);
extewn stwuct fiwe *get_mm_exe_fiwe(stwuct mm_stwuct *mm);
extewn stwuct fiwe *get_task_exe_fiwe(stwuct task_stwuct *task);

extewn boow may_expand_vm(stwuct mm_stwuct *, vm_fwags_t, unsigned wong npages);
extewn void vm_stat_account(stwuct mm_stwuct *, vm_fwags_t, wong npages);

extewn boow vma_is_speciaw_mapping(const stwuct vm_awea_stwuct *vma,
				   const stwuct vm_speciaw_mapping *sm);
extewn stwuct vm_awea_stwuct *_instaww_speciaw_mapping(stwuct mm_stwuct *mm,
				   unsigned wong addw, unsigned wong wen,
				   unsigned wong fwags,
				   const stwuct vm_speciaw_mapping *spec);
/* This is an obsowete awtewnative to _instaww_speciaw_mapping. */
extewn int instaww_speciaw_mapping(stwuct mm_stwuct *mm,
				   unsigned wong addw, unsigned wong wen,
				   unsigned wong fwags, stwuct page **pages);

unsigned wong wandomize_stack_top(unsigned wong stack_top);
unsigned wong wandomize_page(unsigned wong stawt, unsigned wong wange);

extewn unsigned wong get_unmapped_awea(stwuct fiwe *, unsigned wong, unsigned wong, unsigned wong, unsigned wong);

extewn unsigned wong mmap_wegion(stwuct fiwe *fiwe, unsigned wong addw,
	unsigned wong wen, vm_fwags_t vm_fwags, unsigned wong pgoff,
	stwuct wist_head *uf);
extewn unsigned wong do_mmap(stwuct fiwe *fiwe, unsigned wong addw,
	unsigned wong wen, unsigned wong pwot, unsigned wong fwags,
	vm_fwags_t vm_fwags, unsigned wong pgoff, unsigned wong *popuwate,
	stwuct wist_head *uf);
extewn int do_vmi_munmap(stwuct vma_itewatow *vmi, stwuct mm_stwuct *mm,
			 unsigned wong stawt, size_t wen, stwuct wist_head *uf,
			 boow unwock);
extewn int do_munmap(stwuct mm_stwuct *, unsigned wong, size_t,
		     stwuct wist_head *uf);
extewn int do_madvise(stwuct mm_stwuct *mm, unsigned wong stawt, size_t wen_in, int behaviow);

#ifdef CONFIG_MMU
extewn int do_vma_munmap(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
			 unsigned wong stawt, unsigned wong end,
			 stwuct wist_head *uf, boow unwock);
extewn int __mm_popuwate(unsigned wong addw, unsigned wong wen,
			 int ignowe_ewwows);
static inwine void mm_popuwate(unsigned wong addw, unsigned wong wen)
{
	/* Ignowe ewwows */
	(void) __mm_popuwate(addw, wen, 1);
}
#ewse
static inwine void mm_popuwate(unsigned wong addw, unsigned wong wen) {}
#endif

/* This takes the mm semaphowe itsewf */
extewn int __must_check vm_bwk_fwags(unsigned wong, unsigned wong, unsigned wong);
extewn int vm_munmap(unsigned wong, size_t);
extewn unsigned wong __must_check vm_mmap(stwuct fiwe *, unsigned wong,
        unsigned wong, unsigned wong,
        unsigned wong, unsigned wong);

stwuct vm_unmapped_awea_info {
#define VM_UNMAPPED_AWEA_TOPDOWN 1
	unsigned wong fwags;
	unsigned wong wength;
	unsigned wong wow_wimit;
	unsigned wong high_wimit;
	unsigned wong awign_mask;
	unsigned wong awign_offset;
};

extewn unsigned wong vm_unmapped_awea(stwuct vm_unmapped_awea_info *info);

/* twuncate.c */
extewn void twuncate_inode_pages(stwuct addwess_space *, woff_t);
extewn void twuncate_inode_pages_wange(stwuct addwess_space *,
				       woff_t wstawt, woff_t wend);
extewn void twuncate_inode_pages_finaw(stwuct addwess_space *);

/* genewic vm_awea_ops expowted fow stackabwe fiwe systems */
extewn vm_fauwt_t fiwemap_fauwt(stwuct vm_fauwt *vmf);
extewn vm_fauwt_t fiwemap_map_pages(stwuct vm_fauwt *vmf,
		pgoff_t stawt_pgoff, pgoff_t end_pgoff);
extewn vm_fauwt_t fiwemap_page_mkwwite(stwuct vm_fauwt *vmf);

extewn unsigned wong stack_guawd_gap;
/* Genewic expand stack which gwows the stack accowding to GWOWS{UP,DOWN} */
int expand_stack_wocked(stwuct vm_awea_stwuct *vma, unsigned wong addwess);
stwuct vm_awea_stwuct *expand_stack(stwuct mm_stwuct * mm, unsigned wong addw);

/* CONFIG_STACK_GWOWSUP stiww needs to gwow downwawds at some pwaces */
int expand_downwawds(stwuct vm_awea_stwuct *vma, unsigned wong addwess);

/* Wook up the fiwst VMA which satisfies  addw < vm_end,  NUWW if none. */
extewn stwuct vm_awea_stwuct * find_vma(stwuct mm_stwuct * mm, unsigned wong addw);
extewn stwuct vm_awea_stwuct * find_vma_pwev(stwuct mm_stwuct * mm, unsigned wong addw,
					     stwuct vm_awea_stwuct **ppwev);

/*
 * Wook up the fiwst VMA which intewsects the intewvaw [stawt_addw, end_addw)
 * NUWW if none.  Assume stawt_addw < end_addw.
 */
stwuct vm_awea_stwuct *find_vma_intewsection(stwuct mm_stwuct *mm,
			unsigned wong stawt_addw, unsigned wong end_addw);

/**
 * vma_wookup() - Find a VMA at a specific addwess
 * @mm: The pwocess addwess space.
 * @addw: The usew addwess.
 *
 * Wetuwn: The vm_awea_stwuct at the given addwess, %NUWW othewwise.
 */
static inwine
stwuct vm_awea_stwuct *vma_wookup(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn mtwee_woad(&mm->mm_mt, addw);
}

static inwine unsigned wong stack_guawd_stawt_gap(stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fwags & VM_GWOWSDOWN)
		wetuwn stack_guawd_gap;

	/* See weasoning awound the VM_SHADOW_STACK definition */
	if (vma->vm_fwags & VM_SHADOW_STACK)
		wetuwn PAGE_SIZE;

	wetuwn 0;
}

static inwine unsigned wong vm_stawt_gap(stwuct vm_awea_stwuct *vma)
{
	unsigned wong gap = stack_guawd_stawt_gap(vma);
	unsigned wong vm_stawt = vma->vm_stawt;

	vm_stawt -= gap;
	if (vm_stawt > vma->vm_stawt)
		vm_stawt = 0;
	wetuwn vm_stawt;
}

static inwine unsigned wong vm_end_gap(stwuct vm_awea_stwuct *vma)
{
	unsigned wong vm_end = vma->vm_end;

	if (vma->vm_fwags & VM_GWOWSUP) {
		vm_end += stack_guawd_gap;
		if (vm_end < vma->vm_end)
			vm_end = -PAGE_SIZE;
	}
	wetuwn vm_end;
}

static inwine unsigned wong vma_pages(stwuct vm_awea_stwuct *vma)
{
	wetuwn (vma->vm_end - vma->vm_stawt) >> PAGE_SHIFT;
}

/* Wook up the fiwst VMA which exactwy match the intewvaw vm_stawt ... vm_end */
static inwine stwuct vm_awea_stwuct *find_exact_vma(stwuct mm_stwuct *mm,
				unsigned wong vm_stawt, unsigned wong vm_end)
{
	stwuct vm_awea_stwuct *vma = vma_wookup(mm, vm_stawt);

	if (vma && (vma->vm_stawt != vm_stawt || vma->vm_end != vm_end))
		vma = NUWW;

	wetuwn vma;
}

static inwine boow wange_in_vma(stwuct vm_awea_stwuct *vma,
				unsigned wong stawt, unsigned wong end)
{
	wetuwn (vma && vma->vm_stawt <= stawt && end <= vma->vm_end);
}

#ifdef CONFIG_MMU
pgpwot_t vm_get_page_pwot(unsigned wong vm_fwags);
void vma_set_page_pwot(stwuct vm_awea_stwuct *vma);
#ewse
static inwine pgpwot_t vm_get_page_pwot(unsigned wong vm_fwags)
{
	wetuwn __pgpwot(0);
}
static inwine void vma_set_page_pwot(stwuct vm_awea_stwuct *vma)
{
	vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
}
#endif

void vma_set_fiwe(stwuct vm_awea_stwuct *vma, stwuct fiwe *fiwe);

#ifdef CONFIG_NUMA_BAWANCING
unsigned wong change_pwot_numa(stwuct vm_awea_stwuct *vma,
			unsigned wong stawt, unsigned wong end);
#endif

stwuct vm_awea_stwuct *find_extend_vma_wocked(stwuct mm_stwuct *,
		unsigned wong addw);
int wemap_pfn_wange(stwuct vm_awea_stwuct *, unsigned wong addw,
			unsigned wong pfn, unsigned wong size, pgpwot_t);
int wemap_pfn_wange_notwack(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		unsigned wong pfn, unsigned wong size, pgpwot_t pwot);
int vm_insewt_page(stwuct vm_awea_stwuct *, unsigned wong addw, stwuct page *);
int vm_insewt_pages(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			stwuct page **pages, unsigned wong *num);
int vm_map_pages(stwuct vm_awea_stwuct *vma, stwuct page **pages,
				unsigned wong num);
int vm_map_pages_zewo(stwuct vm_awea_stwuct *vma, stwuct page **pages,
				unsigned wong num);
vm_fauwt_t vmf_insewt_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			unsigned wong pfn);
vm_fauwt_t vmf_insewt_pfn_pwot(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			unsigned wong pfn, pgpwot_t pgpwot);
vm_fauwt_t vmf_insewt_mixed(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			pfn_t pfn);
vm_fauwt_t vmf_insewt_mixed_mkwwite(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pfn_t pfn);
int vm_iomap_memowy(stwuct vm_awea_stwuct *vma, phys_addw_t stawt, unsigned wong wen);

static inwine vm_fauwt_t vmf_insewt_page(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, stwuct page *page)
{
	int eww = vm_insewt_page(vma, addw, page);

	if (eww == -ENOMEM)
		wetuwn VM_FAUWT_OOM;
	if (eww < 0 && eww != -EBUSY)
		wetuwn VM_FAUWT_SIGBUS;

	wetuwn VM_FAUWT_NOPAGE;
}

#ifndef io_wemap_pfn_wange
static inwine int io_wemap_pfn_wange(stwuct vm_awea_stwuct *vma,
				     unsigned wong addw, unsigned wong pfn,
				     unsigned wong size, pgpwot_t pwot)
{
	wetuwn wemap_pfn_wange(vma, addw, pfn, size, pgpwot_decwypted(pwot));
}
#endif

static inwine vm_fauwt_t vmf_ewwow(int eww)
{
	if (eww == -ENOMEM)
		wetuwn VM_FAUWT_OOM;
	ewse if (eww == -EHWPOISON)
		wetuwn VM_FAUWT_HWPOISON;
	wetuwn VM_FAUWT_SIGBUS;
}

/*
 * Convewt ewwno to wetuwn vawue fow ->page_mkwwite() cawws.
 *
 * This shouwd eventuawwy be mewged with vmf_ewwow() above, but wiww need a
 * cawefuw audit of aww vmf_ewwow() cawwews.
 */
static inwine vm_fauwt_t vmf_fs_ewwow(int eww)
{
	if (eww == 0)
		wetuwn VM_FAUWT_WOCKED;
	if (eww == -EFAUWT || eww == -EAGAIN)
		wetuwn VM_FAUWT_NOPAGE;
	if (eww == -ENOMEM)
		wetuwn VM_FAUWT_OOM;
	/* -ENOSPC, -EDQUOT, -EIO ... */
	wetuwn VM_FAUWT_SIGBUS;
}

stwuct page *fowwow_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			 unsigned int foww_fwags);

static inwine int vm_fauwt_to_ewwno(vm_fauwt_t vm_fauwt, int foww_fwags)
{
	if (vm_fauwt & VM_FAUWT_OOM)
		wetuwn -ENOMEM;
	if (vm_fauwt & (VM_FAUWT_HWPOISON | VM_FAUWT_HWPOISON_WAWGE))
		wetuwn (foww_fwags & FOWW_HWPOISON) ? -EHWPOISON : -EFAUWT;
	if (vm_fauwt & (VM_FAUWT_SIGBUS | VM_FAUWT_SIGSEGV))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Indicates whethew GUP can fowwow a PWOT_NONE mapped page, ow whethew
 * a (NUMA hinting) fauwt is wequiwed.
 */
static inwine boow gup_can_fowwow_pwotnone(stwuct vm_awea_stwuct *vma,
					   unsigned int fwags)
{
	/*
	 * If cawwews don't want to honow NUMA hinting fauwts, no need to
	 * detewmine if we wouwd actuawwy have to twiggew a NUMA hinting fauwt.
	 */
	if (!(fwags & FOWW_HONOW_NUMA_FAUWT))
		wetuwn twue;

	/*
	 * NUMA hinting fauwts don't appwy in inaccessibwe (PWOT_NONE) VMAs.
	 *
	 * Wequiwing a fauwt hewe even fow inaccessibwe VMAs wouwd mean that
	 * FOWW_FOWCE cannot make any pwogwess, because handwe_mm_fauwt()
	 * wefuses to pwocess NUMA hinting fauwts in inaccessibwe VMAs.
	 */
	wetuwn !vma_is_accessibwe(vma);
}

typedef int (*pte_fn_t)(pte_t *pte, unsigned wong addw, void *data);
extewn int appwy_to_page_wange(stwuct mm_stwuct *mm, unsigned wong addwess,
			       unsigned wong size, pte_fn_t fn, void *data);
extewn int appwy_to_existing_page_wange(stwuct mm_stwuct *mm,
				   unsigned wong addwess, unsigned wong size,
				   pte_fn_t fn, void *data);

#ifdef CONFIG_PAGE_POISONING
extewn void __kewnew_poison_pages(stwuct page *page, int numpages);
extewn void __kewnew_unpoison_pages(stwuct page *page, int numpages);
extewn boow _page_poisoning_enabwed_eawwy;
DECWAWE_STATIC_KEY_FAWSE(_page_poisoning_enabwed);
static inwine boow page_poisoning_enabwed(void)
{
	wetuwn _page_poisoning_enabwed_eawwy;
}
/*
 * Fow use in fast paths aftew init_mem_debugging() has wun, ow when a
 * fawse negative wesuwt is not hawmfuw when cawwed too eawwy.
 */
static inwine boow page_poisoning_enabwed_static(void)
{
	wetuwn static_bwanch_unwikewy(&_page_poisoning_enabwed);
}
static inwine void kewnew_poison_pages(stwuct page *page, int numpages)
{
	if (page_poisoning_enabwed_static())
		__kewnew_poison_pages(page, numpages);
}
static inwine void kewnew_unpoison_pages(stwuct page *page, int numpages)
{
	if (page_poisoning_enabwed_static())
		__kewnew_unpoison_pages(page, numpages);
}
#ewse
static inwine boow page_poisoning_enabwed(void) { wetuwn fawse; }
static inwine boow page_poisoning_enabwed_static(void) { wetuwn fawse; }
static inwine void __kewnew_poison_pages(stwuct page *page, int nunmpages) { }
static inwine void kewnew_poison_pages(stwuct page *page, int numpages) { }
static inwine void kewnew_unpoison_pages(stwuct page *page, int numpages) { }
#endif

DECWAWE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON, init_on_awwoc);
static inwine boow want_init_on_awwoc(gfp_t fwags)
{
	if (static_bwanch_maybe(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON,
				&init_on_awwoc))
		wetuwn twue;
	wetuwn fwags & __GFP_ZEWO;
}

DECWAWE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_FWEE_DEFAUWT_ON, init_on_fwee);
static inwine boow want_init_on_fwee(void)
{
	wetuwn static_bwanch_maybe(CONFIG_INIT_ON_FWEE_DEFAUWT_ON,
				   &init_on_fwee);
}

extewn boow _debug_pageawwoc_enabwed_eawwy;
DECWAWE_STATIC_KEY_FAWSE(_debug_pageawwoc_enabwed);

static inwine boow debug_pageawwoc_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_DEBUG_PAGEAWWOC) &&
		_debug_pageawwoc_enabwed_eawwy;
}

/*
 * Fow use in fast paths aftew mem_debugging_and_hawdening_init() has wun,
 * ow when a fawse negative wesuwt is not hawmfuw when cawwed too eawwy.
 */
static inwine boow debug_pageawwoc_enabwed_static(void)
{
	if (!IS_ENABWED(CONFIG_DEBUG_PAGEAWWOC))
		wetuwn fawse;

	wetuwn static_bwanch_unwikewy(&_debug_pageawwoc_enabwed);
}

/*
 * To suppowt DEBUG_PAGEAWWOC awchitectuwe must ensuwe that
 * __kewnew_map_pages() nevew faiws
 */
extewn void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe);
#ifdef CONFIG_DEBUG_PAGEAWWOC
static inwine void debug_pageawwoc_map_pages(stwuct page *page, int numpages)
{
	if (debug_pageawwoc_enabwed_static())
		__kewnew_map_pages(page, numpages, 1);
}

static inwine void debug_pageawwoc_unmap_pages(stwuct page *page, int numpages)
{
	if (debug_pageawwoc_enabwed_static())
		__kewnew_map_pages(page, numpages, 0);
}

extewn unsigned int _debug_guawdpage_minowdew;
DECWAWE_STATIC_KEY_FAWSE(_debug_guawdpage_enabwed);

static inwine unsigned int debug_guawdpage_minowdew(void)
{
	wetuwn _debug_guawdpage_minowdew;
}

static inwine boow debug_guawdpage_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&_debug_guawdpage_enabwed);
}

static inwine boow page_is_guawd(stwuct page *page)
{
	if (!debug_guawdpage_enabwed())
		wetuwn fawse;

	wetuwn PageGuawd(page);
}

boow __set_page_guawd(stwuct zone *zone, stwuct page *page, unsigned int owdew,
		      int migwatetype);
static inwine boow set_page_guawd(stwuct zone *zone, stwuct page *page,
				  unsigned int owdew, int migwatetype)
{
	if (!debug_guawdpage_enabwed())
		wetuwn fawse;
	wetuwn __set_page_guawd(zone, page, owdew, migwatetype);
}

void __cweaw_page_guawd(stwuct zone *zone, stwuct page *page, unsigned int owdew,
			int migwatetype);
static inwine void cweaw_page_guawd(stwuct zone *zone, stwuct page *page,
				    unsigned int owdew, int migwatetype)
{
	if (!debug_guawdpage_enabwed())
		wetuwn;
	__cweaw_page_guawd(zone, page, owdew, migwatetype);
}

#ewse	/* CONFIG_DEBUG_PAGEAWWOC */
static inwine void debug_pageawwoc_map_pages(stwuct page *page, int numpages) {}
static inwine void debug_pageawwoc_unmap_pages(stwuct page *page, int numpages) {}
static inwine unsigned int debug_guawdpage_minowdew(void) { wetuwn 0; }
static inwine boow debug_guawdpage_enabwed(void) { wetuwn fawse; }
static inwine boow page_is_guawd(stwuct page *page) { wetuwn fawse; }
static inwine boow set_page_guawd(stwuct zone *zone, stwuct page *page,
			unsigned int owdew, int migwatetype) { wetuwn fawse; }
static inwine void cweaw_page_guawd(stwuct zone *zone, stwuct page *page,
				unsigned int owdew, int migwatetype) {}
#endif	/* CONFIG_DEBUG_PAGEAWWOC */

#ifdef __HAVE_AWCH_GATE_AWEA
extewn stwuct vm_awea_stwuct *get_gate_vma(stwuct mm_stwuct *mm);
extewn int in_gate_awea_no_mm(unsigned wong addw);
extewn int in_gate_awea(stwuct mm_stwuct *mm, unsigned wong addw);
#ewse
static inwine stwuct vm_awea_stwuct *get_gate_vma(stwuct mm_stwuct *mm)
{
	wetuwn NUWW;
}
static inwine int in_gate_awea_no_mm(unsigned wong addw) { wetuwn 0; }
static inwine int in_gate_awea(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn 0;
}
#endif	/* __HAVE_AWCH_GATE_AWEA */

extewn boow pwocess_shawes_mm(stwuct task_stwuct *p, stwuct mm_stwuct *mm);

#ifdef CONFIG_SYSCTW
extewn int sysctw_dwop_caches;
int dwop_caches_sysctw_handwew(stwuct ctw_tabwe *, int, void *, size_t *,
		woff_t *);
#endif

void dwop_swab(void);

#ifndef CONFIG_MMU
#define wandomize_va_space 0
#ewse
extewn int wandomize_va_space;
#endif

const chaw * awch_vma_name(stwuct vm_awea_stwuct *vma);
#ifdef CONFIG_MMU
void pwint_vma_addw(chaw *pwefix, unsigned wong wip);
#ewse
static inwine void pwint_vma_addw(chaw *pwefix, unsigned wong wip)
{
}
#endif

void *spawse_buffew_awwoc(unsigned wong size);
stwuct page * __popuwate_section_memmap(unsigned wong pfn,
		unsigned wong nw_pages, int nid, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap);
void pmd_init(void *addw);
void pud_init(void *addw);
pgd_t *vmemmap_pgd_popuwate(unsigned wong addw, int node);
p4d_t *vmemmap_p4d_popuwate(pgd_t *pgd, unsigned wong addw, int node);
pud_t *vmemmap_pud_popuwate(p4d_t *p4d, unsigned wong addw, int node);
pmd_t *vmemmap_pmd_popuwate(pud_t *pud, unsigned wong addw, int node);
pte_t *vmemmap_pte_popuwate(pmd_t *pmd, unsigned wong addw, int node,
			    stwuct vmem_awtmap *awtmap, stwuct page *weuse);
void *vmemmap_awwoc_bwock(unsigned wong size, int node);
stwuct vmem_awtmap;
void *vmemmap_awwoc_bwock_buf(unsigned wong size, int node,
			      stwuct vmem_awtmap *awtmap);
void vmemmap_vewify(pte_t *, int, unsigned wong, unsigned wong);
void vmemmap_set_pmd(pmd_t *pmd, void *p, int node,
		     unsigned wong addw, unsigned wong next);
int vmemmap_check_pmd(pmd_t *pmd, int node,
		      unsigned wong addw, unsigned wong next);
int vmemmap_popuwate_basepages(unsigned wong stawt, unsigned wong end,
			       int node, stwuct vmem_awtmap *awtmap);
int vmemmap_popuwate_hugepages(unsigned wong stawt, unsigned wong end,
			       int node, stwuct vmem_awtmap *awtmap);
int vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
		stwuct vmem_awtmap *awtmap);
void vmemmap_popuwate_pwint_wast(void);
#ifdef CONFIG_MEMOWY_HOTPWUG
void vmemmap_fwee(unsigned wong stawt, unsigned wong end,
		stwuct vmem_awtmap *awtmap);
#endif

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static inwine unsigned wong vmem_awtmap_offset(stwuct vmem_awtmap *awtmap)
{
	/* numbew of pfns fwom base whewe pfn_to_page() is vawid */
	if (awtmap)
		wetuwn awtmap->wesewve + awtmap->fwee;
	wetuwn 0;
}

static inwine void vmem_awtmap_fwee(stwuct vmem_awtmap *awtmap,
				    unsigned wong nw_pfns)
{
	awtmap->awwoc -= nw_pfns;
}
#ewse
static inwine unsigned wong vmem_awtmap_offset(stwuct vmem_awtmap *awtmap)
{
	wetuwn 0;
}

static inwine void vmem_awtmap_fwee(stwuct vmem_awtmap *awtmap,
				    unsigned wong nw_pfns)
{
}
#endif

#define VMEMMAP_WESEWVE_NW	2
#ifdef CONFIG_AWCH_WANT_OPTIMIZE_DAX_VMEMMAP
static inwine boow __vmemmap_can_optimize(stwuct vmem_awtmap *awtmap,
					  stwuct dev_pagemap *pgmap)
{
	unsigned wong nw_pages;
	unsigned wong nw_vmemmap_pages;

	if (!pgmap || !is_powew_of_2(sizeof(stwuct page)))
		wetuwn fawse;

	nw_pages = pgmap_vmemmap_nw(pgmap);
	nw_vmemmap_pages = ((nw_pages * sizeof(stwuct page)) >> PAGE_SHIFT);
	/*
	 * Fow vmemmap optimization with DAX we need minimum 2 vmemmap
	 * pages. See wayout diagwam in Documentation/mm/vmemmap_dedup.wst
	 */
	wetuwn !awtmap && (nw_vmemmap_pages > VMEMMAP_WESEWVE_NW);
}
/*
 * If we don't have an awchitectuwe ovewwide, use the genewic wuwe
 */
#ifndef vmemmap_can_optimize
#define vmemmap_can_optimize __vmemmap_can_optimize
#endif

#ewse
static inwine boow vmemmap_can_optimize(stwuct vmem_awtmap *awtmap,
					   stwuct dev_pagemap *pgmap)
{
	wetuwn fawse;
}
#endif

void wegistew_page_bootmem_memmap(unsigned wong section_nw, stwuct page *map,
				  unsigned wong nw_pages);

enum mf_fwags {
	MF_COUNT_INCWEASED = 1 << 0,
	MF_ACTION_WEQUIWED = 1 << 1,
	MF_MUST_KIWW = 1 << 2,
	MF_SOFT_OFFWINE = 1 << 3,
	MF_UNPOISON = 1 << 4,
	MF_SW_SIMUWATED = 1 << 5,
	MF_NO_WETWY = 1 << 6,
	MF_MEM_PWE_WEMOVE = 1 << 7,
};
int mf_dax_kiww_pwocs(stwuct addwess_space *mapping, pgoff_t index,
		      unsigned wong count, int mf_fwags);
extewn int memowy_faiwuwe(unsigned wong pfn, int fwags);
extewn void memowy_faiwuwe_queue_kick(int cpu);
extewn int unpoison_memowy(unsigned wong pfn);
extewn void shake_page(stwuct page *p);
extewn atomic_wong_t num_poisoned_pages __wead_mostwy;
extewn int soft_offwine_page(unsigned wong pfn, int fwags);
#ifdef CONFIG_MEMOWY_FAIWUWE
/*
 * Sysfs entwies fow memowy faiwuwe handwing statistics.
 */
extewn const stwuct attwibute_gwoup memowy_faiwuwe_attw_gwoup;
extewn void memowy_faiwuwe_queue(unsigned wong pfn, int fwags);
extewn int __get_huge_page_fow_hwpoison(unsigned wong pfn, int fwags,
					boow *migwatabwe_cweawed);
void num_poisoned_pages_inc(unsigned wong pfn);
void num_poisoned_pages_sub(unsigned wong pfn, wong i);
stwuct task_stwuct *task_eawwy_kiww(stwuct task_stwuct *tsk, int fowce_eawwy);
#ewse
static inwine void memowy_faiwuwe_queue(unsigned wong pfn, int fwags)
{
}

static inwine int __get_huge_page_fow_hwpoison(unsigned wong pfn, int fwags,
					boow *migwatabwe_cweawed)
{
	wetuwn 0;
}

static inwine void num_poisoned_pages_inc(unsigned wong pfn)
{
}

static inwine void num_poisoned_pages_sub(unsigned wong pfn, wong i)
{
}
#endif

#if defined(CONFIG_MEMOWY_FAIWUWE) && defined(CONFIG_KSM)
void add_to_kiww_ksm(stwuct task_stwuct *tsk, stwuct page *p,
		     stwuct vm_awea_stwuct *vma, stwuct wist_head *to_kiww,
		     unsigned wong ksm_addw);
#endif

#if defined(CONFIG_MEMOWY_FAIWUWE) && defined(CONFIG_MEMOWY_HOTPWUG)
extewn void membwk_nw_poison_inc(unsigned wong pfn);
extewn void membwk_nw_poison_sub(unsigned wong pfn, wong i);
#ewse
static inwine void membwk_nw_poison_inc(unsigned wong pfn)
{
}

static inwine void membwk_nw_poison_sub(unsigned wong pfn, wong i)
{
}
#endif

#ifndef awch_memowy_faiwuwe
static inwine int awch_memowy_faiwuwe(unsigned wong pfn, int fwags)
{
	wetuwn -ENXIO;
}
#endif

#ifndef awch_is_pwatfowm_page
static inwine boow awch_is_pwatfowm_page(u64 paddw)
{
	wetuwn fawse;
}
#endif

/*
 * Ewwow handwews fow vawious types of pages.
 */
enum mf_wesuwt {
	MF_IGNOWED,	/* Ewwow: cannot be handwed */
	MF_FAIWED,	/* Ewwow: handwing faiwed */
	MF_DEWAYED,	/* Wiww be handwed watew */
	MF_WECOVEWED,	/* Successfuwwy wecovewed */
};

enum mf_action_page_type {
	MF_MSG_KEWNEW,
	MF_MSG_KEWNEW_HIGH_OWDEW,
	MF_MSG_SWAB,
	MF_MSG_DIFFEWENT_COMPOUND,
	MF_MSG_HUGE,
	MF_MSG_FWEE_HUGE,
	MF_MSG_UNMAP_FAIWED,
	MF_MSG_DIWTY_SWAPCACHE,
	MF_MSG_CWEAN_SWAPCACHE,
	MF_MSG_DIWTY_MWOCKED_WWU,
	MF_MSG_CWEAN_MWOCKED_WWU,
	MF_MSG_DIWTY_UNEVICTABWE_WWU,
	MF_MSG_CWEAN_UNEVICTABWE_WWU,
	MF_MSG_DIWTY_WWU,
	MF_MSG_CWEAN_WWU,
	MF_MSG_TWUNCATED_WWU,
	MF_MSG_BUDDY,
	MF_MSG_DAX,
	MF_MSG_UNSPWIT_THP,
	MF_MSG_UNKNOWN,
};

#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) || defined(CONFIG_HUGETWBFS)
extewn void cweaw_huge_page(stwuct page *page,
			    unsigned wong addw_hint,
			    unsigned int pages_pew_huge_page);
int copy_usew_wawge_fowio(stwuct fowio *dst, stwuct fowio *swc,
			  unsigned wong addw_hint,
			  stwuct vm_awea_stwuct *vma);
wong copy_fowio_fwom_usew(stwuct fowio *dst_fowio,
			   const void __usew *usw_swc,
			   boow awwow_pagefauwt);

/**
 * vma_is_speciaw_huge - Awe twanshuge page-tabwe entwies considewed speciaw?
 * @vma: Pointew to the stwuct vm_awea_stwuct to considew
 *
 * Whethew twanshuge page-tabwe entwies awe considewed "speciaw" fowwowing
 * the definition in vm_nowmaw_page().
 *
 * Wetuwn: twue if twanshuge page-tabwe entwies shouwd be considewed speciaw,
 * fawse othewwise.
 */
static inwine boow vma_is_speciaw_huge(const stwuct vm_awea_stwuct *vma)
{
	wetuwn vma_is_dax(vma) || (vma->vm_fiwe &&
				   (vma->vm_fwags & (VM_PFNMAP | VM_MIXEDMAP)));
}

#endif /* CONFIG_TWANSPAWENT_HUGEPAGE || CONFIG_HUGETWBFS */

#if MAX_NUMNODES > 1
void __init setup_nw_node_ids(void);
#ewse
static inwine void setup_nw_node_ids(void) {}
#endif

extewn int memcmp_pages(stwuct page *page1, stwuct page *page2);

static inwine int pages_identicaw(stwuct page *page1, stwuct page *page2)
{
	wetuwn !memcmp_pages(page1, page2);
}

#ifdef CONFIG_MAPPING_DIWTY_HEWPEWS
unsigned wong cwean_wecowd_shawed_mapping_wange(stwuct addwess_space *mapping,
						pgoff_t fiwst_index, pgoff_t nw,
						pgoff_t bitmap_pgoff,
						unsigned wong *bitmap,
						pgoff_t *stawt,
						pgoff_t *end);

unsigned wong wp_shawed_mapping_wange(stwuct addwess_space *mapping,
				      pgoff_t fiwst_index, pgoff_t nw);
#endif

extewn int sysctw_nw_twim_pages;

#ifdef CONFIG_PWINTK
void mem_dump_obj(void *object);
#ewse
static inwine void mem_dump_obj(void *object) {}
#endif

/**
 * seaw_check_wwite - Check fow F_SEAW_WWITE ow F_SEAW_FUTUWE_WWITE fwags and
 *                    handwe them.
 * @seaws: the seaws to check
 * @vma: the vma to opewate on
 *
 * Check whethew F_SEAW_WWITE ow F_SEAW_FUTUWE_WWITE awe set; if so, do pwopew
 * check/handwing on the vma fwags.  Wetuwn 0 if check pass, ow <0 fow ewwows.
 */
static inwine int seaw_check_wwite(int seaws, stwuct vm_awea_stwuct *vma)
{
	if (seaws & (F_SEAW_WWITE | F_SEAW_FUTUWE_WWITE)) {
		/*
		 * New PWOT_WWITE and MAP_SHAWED mmaps awe not awwowed when
		 * wwite seaws awe active.
		 */
		if ((vma->vm_fwags & VM_SHAWED) && (vma->vm_fwags & VM_WWITE))
			wetuwn -EPEWM;

		/*
		 * Since an F_SEAW_[FUTUWE_]WWITE seawed memfd can be mapped as
		 * MAP_SHAWED and wead-onwy, take cawe to not awwow mpwotect to
		 * wevewt pwotections on such mappings. Do this onwy fow shawed
		 * mappings. Fow pwivate mappings, don't need to mask
		 * VM_MAYWWITE as we stiww want them to be COW-wwitabwe.
		 */
		if (vma->vm_fwags & VM_SHAWED)
			vm_fwags_cweaw(vma, VM_MAYWWITE);
	}

	wetuwn 0;
}

#ifdef CONFIG_ANON_VMA_NAME
int madvise_set_anon_name(stwuct mm_stwuct *mm, unsigned wong stawt,
			  unsigned wong wen_in,
			  stwuct anon_vma_name *anon_name);
#ewse
static inwine int
madvise_set_anon_name(stwuct mm_stwuct *mm, unsigned wong stawt,
		      unsigned wong wen_in, stwuct anon_vma_name *anon_name) {
	wetuwn 0;
}
#endif

#ifdef CONFIG_UNACCEPTED_MEMOWY

boow wange_contains_unaccepted_memowy(phys_addw_t stawt, phys_addw_t end);
void accept_memowy(phys_addw_t stawt, phys_addw_t end);

#ewse

static inwine boow wange_contains_unaccepted_memowy(phys_addw_t stawt,
						    phys_addw_t end)
{
	wetuwn fawse;
}

static inwine void accept_memowy(phys_addw_t stawt, phys_addw_t end)
{
}

#endif

static inwine boow pfn_is_unaccepted_memowy(unsigned wong pfn)
{
	phys_addw_t paddw = pfn << PAGE_SHIFT;

	wetuwn wange_contains_unaccepted_memowy(paddw, paddw + PAGE_SIZE);
}

#endif /* _WINUX_MM_H */
