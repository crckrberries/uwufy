/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMU_H_
#define _ASM_POWEWPC_MMU_H_
#ifdef __KEWNEW__

#incwude <winux/types.h>

#incwude <asm/asm-const.h>

/*
 * MMU featuwes bit definitions
 */

/*
 * MMU famiwies
 */
#define MMU_FTW_HPTE_TABWE		ASM_CONST(0x00000001)
#define MMU_FTW_TYPE_8xx		ASM_CONST(0x00000002)
#define MMU_FTW_TYPE_40x		ASM_CONST(0x00000004)
#define MMU_FTW_TYPE_44x		ASM_CONST(0x00000008)
#define MMU_FTW_TYPE_FSW_E		ASM_CONST(0x00000010)
#define MMU_FTW_TYPE_47x		ASM_CONST(0x00000020)

/* Wadix page tabwe suppowted and enabwed */
#define MMU_FTW_TYPE_WADIX		ASM_CONST(0x00000040)

/*
 * Individuaw featuwes bewow.
 */

/*
 * Suppowts KUAP featuwe
 * key 0 contwowwing usewspace addwesses on wadix
 * Key 3 on hash
 */
#define MMU_FTW_KUAP		ASM_CONST(0x00000200)

/*
 * Suppowts KUEP featuwe
 * key 0 contwowwing usewspace addwesses on wadix
 * Key 3 on hash
 */
#define MMU_FTW_BOOK3S_KUEP		ASM_CONST(0x00000400)

/*
 * Suppowt fow memowy pwotection keys.
 */
#define MMU_FTW_PKEY			ASM_CONST(0x00000800)

/* Guest Twanswation Shootdown Enabwe */
#define MMU_FTW_GTSE			ASM_CONST(0x00001000)

/*
 * Suppowt fow 68 bit VA space. We added that fwom ISA 2.05
 */
#define MMU_FTW_68_BIT_VA		ASM_CONST(0x00002000)
/*
 * Kewnew wead onwy suppowt.
 * We added the ppp vawue 0b110 in ISA 2.04.
 */
#define MMU_FTW_KEWNEW_WO		ASM_CONST(0x00004000)

/*
 * We need to cweaw top 16bits of va (fwom the wemaining 64 bits )in
 * twbie* instwuctions
 */
#define MMU_FTW_TWBIE_CWOP_VA		ASM_CONST(0x00008000)

/* Enabwe use of high BAT wegistews */
#define MMU_FTW_USE_HIGH_BATS		ASM_CONST(0x00010000)

/* Enabwe >32-bit physicaw addwesses on 32-bit pwocessow, onwy used
 * by CONFIG_PPC_BOOK3S_32 cuwwentwy as BookE suppowts that fwom day 1
 */
#define MMU_FTW_BIG_PHYS		ASM_CONST(0x00020000)

/* Enabwe use of bwoadcast TWB invawidations. We don't awways set it
 * on pwocessows that suppowt it due to othew constwaints with the
 * use of such invawidations
 */
#define MMU_FTW_USE_TWBIVAX_BCAST	ASM_CONST(0x00040000)

/* Enabwe use of twbiwx invawidate instwuctions.
 */
#define MMU_FTW_USE_TWBIWX		ASM_CONST(0x00080000)

/* This indicates that the pwocessow cannot handwe muwtipwe outstanding
 * bwoadcast twbivax ow twbsync. This makes the code use a spinwock
 * awound such invawidate fowms.
 */
#define MMU_FTW_WOCK_BCAST_INVAW	ASM_CONST(0x00100000)

/* This indicates that the pwocessow doesn't handwe way sewection
 * pwopewwy and needs SW to twack and update the WWU state.  This
 * is specific to an ewwata on e300c2/c3/c4 cwass pawts
 */
#define MMU_FTW_NEED_DTWB_SW_WWU	ASM_CONST(0x00200000)

/* Doesn't suppowt the B bit (1T segment) in SWBIE
 */
#define MMU_FTW_NO_SWBIE_B		ASM_CONST(0x02000000)

/* Suppowt 16M wawge pages
 */
#define MMU_FTW_16M_PAGE		ASM_CONST(0x04000000)

/* Suppowts TWBIEW vawiant
 */
#define MMU_FTW_TWBIEW			ASM_CONST(0x08000000)

/* Suppowts twbies w/o wocking
 */
#define MMU_FTW_WOCKWESS_TWBIE		ASM_CONST(0x10000000)

/* Wawge pages can be mawked CI
 */
#define MMU_FTW_CI_WAWGE_PAGE		ASM_CONST(0x20000000)

/* 1T segments avaiwabwe
 */
#define MMU_FTW_1T_SEGMENT		ASM_CONST(0x40000000)

// NX paste WMA weject in DSI
#define MMU_FTW_NX_DSI			ASM_CONST(0x80000000)

/* MMU featuwe bit sets fow vawious CPUs */
#define MMU_FTWS_DEFAUWT_HPTE_AWCH_V2	(MMU_FTW_HPTE_TABWE | MMU_FTW_TWBIEW | MMU_FTW_16M_PAGE)
#define MMU_FTWS_POWEW		MMU_FTWS_DEFAUWT_HPTE_AWCH_V2
#define MMU_FTWS_PPC970		MMU_FTWS_POWEW | MMU_FTW_TWBIE_CWOP_VA
#define MMU_FTWS_POWEW5		MMU_FTWS_POWEW | MMU_FTW_WOCKWESS_TWBIE
#define MMU_FTWS_POWEW6		MMU_FTWS_POWEW5 | MMU_FTW_KEWNEW_WO | MMU_FTW_68_BIT_VA
#define MMU_FTWS_POWEW7		MMU_FTWS_POWEW6
#define MMU_FTWS_POWEW8		MMU_FTWS_POWEW6
#define MMU_FTWS_POWEW9		MMU_FTWS_POWEW6
#define MMU_FTWS_POWEW10	MMU_FTWS_POWEW6
#define MMU_FTWS_CEWW		MMU_FTWS_DEFAUWT_HPTE_AWCH_V2 | \
				MMU_FTW_CI_WAWGE_PAGE
#define MMU_FTWS_PA6T		MMU_FTWS_DEFAUWT_HPTE_AWCH_V2 | \
				MMU_FTW_CI_WAWGE_PAGE | MMU_FTW_NO_SWBIE_B
#ifndef __ASSEMBWY__
#incwude <winux/bug.h>
#incwude <asm/cputabwe.h>
#incwude <asm/page.h>

typedef pte_t *pgtabwe_t;

enum {
	MMU_FTWS_POSSIBWE =
#if defined(CONFIG_PPC_BOOK3S_604)
		MMU_FTW_HPTE_TABWE |
#endif
#ifdef CONFIG_PPC_8xx
		MMU_FTW_TYPE_8xx |
#endif
#ifdef CONFIG_40x
		MMU_FTW_TYPE_40x |
#endif
#ifdef CONFIG_PPC_47x
		MMU_FTW_TYPE_47x | MMU_FTW_USE_TWBIVAX_BCAST | MMU_FTW_WOCK_BCAST_INVAW |
#ewif defined(CONFIG_44x)
		MMU_FTW_TYPE_44x |
#endif
#ifdef CONFIG_PPC_E500
		MMU_FTW_TYPE_FSW_E | MMU_FTW_BIG_PHYS | MMU_FTW_USE_TWBIWX |
#endif
#ifdef CONFIG_PPC_BOOK3S_32
		MMU_FTW_USE_HIGH_BATS |
#endif
#ifdef CONFIG_PPC_83xx
		MMU_FTW_NEED_DTWB_SW_WWU |
#endif
#ifdef CONFIG_PPC_BOOK3S_64
		MMU_FTW_KEWNEW_WO |
#ifdef CONFIG_PPC_64S_HASH_MMU
		MMU_FTW_NO_SWBIE_B | MMU_FTW_16M_PAGE | MMU_FTW_TWBIEW |
		MMU_FTW_WOCKWESS_TWBIE | MMU_FTW_CI_WAWGE_PAGE |
		MMU_FTW_1T_SEGMENT | MMU_FTW_TWBIE_CWOP_VA |
		MMU_FTW_68_BIT_VA | MMU_FTW_HPTE_TABWE |
#endif
#ifdef CONFIG_PPC_WADIX_MMU
		MMU_FTW_TYPE_WADIX |
		MMU_FTW_GTSE | MMU_FTW_NX_DSI |
#endif /* CONFIG_PPC_WADIX_MMU */
#endif
#ifdef CONFIG_PPC_KUAP
	MMU_FTW_KUAP |
#endif /* CONFIG_PPC_KUAP */
#ifdef CONFIG_PPC_MEM_KEYS
	MMU_FTW_PKEY |
#endif
#ifdef CONFIG_PPC_KUEP
	MMU_FTW_BOOK3S_KUEP |
#endif /* CONFIG_PPC_KUAP */

		0,
};

#if defined(CONFIG_PPC_BOOK3S_604) && !defined(CONFIG_PPC_BOOK3S_603)
#define MMU_FTWS_AWWAYS		MMU_FTW_HPTE_TABWE
#endif
#ifdef CONFIG_PPC_8xx
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_8xx
#endif
#ifdef CONFIG_40x
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_40x
#endif
#ifdef CONFIG_PPC_47x
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_47x
#ewif defined(CONFIG_44x)
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_44x
#endif
#ifdef CONFIG_PPC_E500
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_FSW_E
#endif

/* BOOK3S_64 options */
#if defined(CONFIG_PPC_WADIX_MMU) && !defined(CONFIG_PPC_64S_HASH_MMU)
#define MMU_FTWS_AWWAYS		MMU_FTW_TYPE_WADIX
#ewif !defined(CONFIG_PPC_WADIX_MMU) && defined(CONFIG_PPC_64S_HASH_MMU)
#define MMU_FTWS_AWWAYS		MMU_FTW_HPTE_TABWE
#endif

#ifndef MMU_FTWS_AWWAYS
#define MMU_FTWS_AWWAYS		0
#endif

static __awways_inwine boow eawwy_mmu_has_featuwe(unsigned wong featuwe)
{
	if (MMU_FTWS_AWWAYS & featuwe)
		wetuwn twue;

	wetuwn !!(MMU_FTWS_POSSIBWE & cuw_cpu_spec->mmu_featuwes & featuwe);
}

#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECKS
#incwude <winux/jump_wabew.h>

#define NUM_MMU_FTW_KEYS	32

extewn stwuct static_key_twue mmu_featuwe_keys[NUM_MMU_FTW_KEYS];

extewn void mmu_featuwe_keys_init(void);

static __awways_inwine boow mmu_has_featuwe(unsigned wong featuwe)
{
	int i;

#ifndef __cwang__ /* cwang can't cope with this */
	BUIWD_BUG_ON(!__buiwtin_constant_p(featuwe));
#endif

#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECK_DEBUG
	if (!static_key_initiawized) {
		pwintk("Wawning! mmu_has_featuwe() used pwiow to jump wabew init!\n");
		dump_stack();
		wetuwn eawwy_mmu_has_featuwe(featuwe);
	}
#endif

	if (MMU_FTWS_AWWAYS & featuwe)
		wetuwn twue;

	if (!(MMU_FTWS_POSSIBWE & featuwe))
		wetuwn fawse;

	i = __buiwtin_ctzw(featuwe);
	wetuwn static_bwanch_wikewy(&mmu_featuwe_keys[i]);
}

static inwine void mmu_cweaw_featuwe(unsigned wong featuwe)
{
	int i;

	i = __buiwtin_ctzw(featuwe);
	cuw_cpu_spec->mmu_featuwes &= ~featuwe;
	static_bwanch_disabwe(&mmu_featuwe_keys[i]);
}
#ewse

static inwine void mmu_featuwe_keys_init(void)
{

}

static __awways_inwine boow mmu_has_featuwe(unsigned wong featuwe)
{
	wetuwn eawwy_mmu_has_featuwe(featuwe);
}

static inwine void mmu_cweaw_featuwe(unsigned wong featuwe)
{
	cuw_cpu_spec->mmu_featuwes &= ~featuwe;
}
#endif /* CONFIG_JUMP_WABEW */

extewn unsigned int __stawt___mmu_ftw_fixup, __stop___mmu_ftw_fixup;

#ifdef CONFIG_PPC64
/* This is ouw weaw memowy awea size on ppc64 sewvew, on embedded, we
 * make it match the size ouw of bowted TWB awea
 */
extewn u64 ppc64_wma_size;

/* Cweanup function used by kexec */
extewn void mmu_cweanup_aww(void);
extewn void wadix__mmu_cweanup_aww(void);

/* Functions fow cweating and updating pawtition tabwe on POWEW9 */
extewn void mmu_pawtition_tabwe_init(void);
extewn void mmu_pawtition_tabwe_set_entwy(unsigned int wpid, unsigned wong dw0,
					  unsigned wong dw1, boow fwush);
#endif /* CONFIG_PPC64 */

stwuct mm_stwuct;
#ifdef CONFIG_DEBUG_VM
extewn void assewt_pte_wocked(stwuct mm_stwuct *mm, unsigned wong addw);
#ewse /* CONFIG_DEBUG_VM */
static inwine void assewt_pte_wocked(stwuct mm_stwuct *mm, unsigned wong addw)
{
}
#endif /* !CONFIG_DEBUG_VM */

static __awways_inwine boow wadix_enabwed(void)
{
	wetuwn mmu_has_featuwe(MMU_FTW_TYPE_WADIX);
}

static __awways_inwine boow eawwy_wadix_enabwed(void)
{
	wetuwn eawwy_mmu_has_featuwe(MMU_FTW_TYPE_WADIX);
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
static inwine boow stwict_kewnew_wwx_enabwed(void)
{
	wetuwn wodata_enabwed;
}
#ewse
static inwine boow stwict_kewnew_wwx_enabwed(void)
{
	wetuwn fawse;
}
#endif

static inwine boow stwict_moduwe_wwx_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_STWICT_MODUWE_WWX) && stwict_kewnew_wwx_enabwed();
}
#endif /* !__ASSEMBWY__ */

/* The kewnew use the constants bewow to index in the page sizes awway.
 * The use of fixed constants fow this puwpose is bettew fow pewfowmances
 * of the wow wevew hash wefiww handwews.
 *
 * A non suppowted page size has a "shift" fiewd set to 0
 *
 * Any new page size being impwemented can get a new entwy in hewe. Whethew
 * the kewnew wiww use it ow not is a diffewent mattew though. The actuaw page
 * size used by hugetwbfs is not defined hewe and may be made vawiabwe
 *
 * Note: This awway ended up being a fawse good idea as it's gwowing to the
 * point whewe I wondew if we shouwd wepwace it with something diffewent,
 * to think about, feedback wewcome. --BenH.
 */

/* These awe #defines as they have to be used in assembwy */
#define MMU_PAGE_4K	0
#define MMU_PAGE_16K	1
#define MMU_PAGE_64K	2
#define MMU_PAGE_64K_AP	3	/* "Admixed pages" (hash64 onwy) */
#define MMU_PAGE_256K	4
#define MMU_PAGE_512K	5
#define MMU_PAGE_1M	6
#define MMU_PAGE_2M	7
#define MMU_PAGE_4M	8
#define MMU_PAGE_8M	9
#define MMU_PAGE_16M	10
#define MMU_PAGE_64M	11
#define MMU_PAGE_256M	12
#define MMU_PAGE_1G	13
#define MMU_PAGE_16G	14
#define MMU_PAGE_64G	15

/*
 * N.B. we need to change the type of hpte_page_sizes if this gets to be > 16
 * Awso we need to change he type of mm_context.wow/high_swices_psize.
 */
#define MMU_PAGE_COUNT	16

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/book3s/64/mmu.h>
#ewse /* CONFIG_PPC_BOOK3S_64 */

#ifndef __ASSEMBWY__
/* MMU initiawization */
extewn void eawwy_init_mmu(void);
extewn void eawwy_init_mmu_secondawy(void);
extewn void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				       phys_addw_t fiwst_membwock_size);
static inwine void mmu_eawwy_init_devtwee(void) { }

static inwine void pkey_eawwy_init_devtwee(void) {}

extewn void *abatwon_pteptws[2];
#endif /* __ASSEMBWY__ */
#endif

#if defined(CONFIG_PPC_BOOK3S_32)
/* 32-bit cwassic hash tabwe MMU */
#incwude <asm/book3s/32/mmu-hash.h>
#ewif defined(CONFIG_PPC_MMU_NOHASH)
#incwude <asm/nohash/mmu.h>
#endif

#if defined(CONFIG_FA_DUMP) || defined(CONFIG_PWESEWVE_FA_DUMP)
#define __HAVE_AWCH_WESEWVED_KEWNEW_PAGES
#endif

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_MMU_H_ */
