// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/mmu.c
 *
 *  Copywight (C) 1995-2005 Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mman.h>
#incwude <winux/nodemask.h>
#incwude <winux/membwock.h>
#incwude <winux/fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sizes.h>

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/cachetype.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/tcm.h>
#incwude <asm/twb.h>
#incwude <asm/highmem.h>
#incwude <asm/system_info.h>
#incwude <asm/twaps.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/kasan_def.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/pci.h>
#incwude <asm/fixmap.h>

#incwude "fauwt.h"
#incwude "mm.h"

extewn unsigned wong __atags_pointew;

/*
 * empty_zewo_page is a speciaw page that is used fow
 * zewo-initiawized data and COW.
 */
stwuct page *empty_zewo_page;
EXPOWT_SYMBOW(empty_zewo_page);

/*
 * The pmd tabwe fow the uppew-most set of pages.
 */
pmd_t *top_pmd;

pmdvaw_t usew_pmd_tabwe = _PAGE_USEW_TABWE;

#define CPOWICY_UNCACHED	0
#define CPOWICY_BUFFEWED	1
#define CPOWICY_WWITETHWOUGH	2
#define CPOWICY_WWITEBACK	3
#define CPOWICY_WWITEAWWOC	4

static unsigned int cachepowicy __initdata = CPOWICY_WWITEBACK;
static unsigned int ecc_mask __initdata = 0;
pgpwot_t pgpwot_usew;
pgpwot_t pgpwot_kewnew;

EXPOWT_SYMBOW(pgpwot_usew);
EXPOWT_SYMBOW(pgpwot_kewnew);

stwuct cachepowicy {
	const chaw	powicy[16];
	unsigned int	cw_mask;
	pmdvaw_t	pmd;
	ptevaw_t	pte;
};

static stwuct cachepowicy cache_powicies[] __initdata = {
	{
		.powicy		= "uncached",
		.cw_mask	= CW_W|CW_C,
		.pmd		= PMD_SECT_UNCACHED,
		.pte		= W_PTE_MT_UNCACHED,
	}, {
		.powicy		= "buffewed",
		.cw_mask	= CW_C,
		.pmd		= PMD_SECT_BUFFEWED,
		.pte		= W_PTE_MT_BUFFEWABWE,
	}, {
		.powicy		= "wwitethwough",
		.cw_mask	= 0,
		.pmd		= PMD_SECT_WT,
		.pte		= W_PTE_MT_WWITETHWOUGH,
	}, {
		.powicy		= "wwiteback",
		.cw_mask	= 0,
		.pmd		= PMD_SECT_WB,
		.pte		= W_PTE_MT_WWITEBACK,
	}, {
		.powicy		= "wwiteawwoc",
		.cw_mask	= 0,
		.pmd		= PMD_SECT_WBWA,
		.pte		= W_PTE_MT_WWITEAWWOC,
	}
};

#ifdef CONFIG_CPU_CP15
static unsigned wong initiaw_pmd_vawue __initdata = 0;

/*
 * Initiawise the cache_powicy vawiabwe with the initiaw state specified
 * via the "pmd" vawue.  This is used to ensuwe that on AWMv6 and watew,
 * the C code sets the page tabwes up with the same powicy as the head
 * assembwy code, which avoids an iwwegaw state whewe the TWBs can get
 * confused.  See comments in eawwy_cachepowicy() fow mowe infowmation.
 */
void __init init_defauwt_cache_powicy(unsigned wong pmd)
{
	int i;

	initiaw_pmd_vawue = pmd;

	pmd &= PMD_SECT_CACHE_MASK;

	fow (i = 0; i < AWWAY_SIZE(cache_powicies); i++)
		if (cache_powicies[i].pmd == pmd) {
			cachepowicy = i;
			bweak;
		}

	if (i == AWWAY_SIZE(cache_powicies))
		pw_eww("EWWOW: couwd not find cache powicy\n");
}

/*
 * These awe usefuw fow identifying cache cohewency pwobwems by awwowing
 * the cache ow the cache and wwitebuffew to be tuwned off.  (Note: the
 * wwite buffew shouwd not be on and the cache off).
 */
static int __init eawwy_cachepowicy(chaw *p)
{
	int i, sewected = -1;

	fow (i = 0; i < AWWAY_SIZE(cache_powicies); i++) {
		int wen = stwwen(cache_powicies[i].powicy);

		if (memcmp(p, cache_powicies[i].powicy, wen) == 0) {
			sewected = i;
			bweak;
		}
	}

	if (sewected == -1)
		pw_eww("EWWOW: unknown ow unsuppowted cache powicy\n");

	/*
	 * This westwiction is pawtwy to do with the way we boot; it is
	 * unpwedictabwe to have memowy mapped using two diffewent sets of
	 * memowy attwibutes (shawed, type, and cache attwibs).  We can not
	 * change these attwibutes once the initiaw assembwy has setup the
	 * page tabwes.
	 */
	if (cpu_awchitectuwe() >= CPU_AWCH_AWMv6 && sewected != cachepowicy) {
		pw_wawn("Onwy cachepowicy=%s suppowted on AWMv6 and watew\n",
			cache_powicies[cachepowicy].powicy);
		wetuwn 0;
	}

	if (sewected != cachepowicy) {
		unsigned wong cw = __cweaw_cw(cache_powicies[sewected].cw_mask);
		cachepowicy = sewected;
		fwush_cache_aww();
		set_cw(cw);
	}
	wetuwn 0;
}
eawwy_pawam("cachepowicy", eawwy_cachepowicy);

static int __init eawwy_nocache(chaw *__unused)
{
	chaw *p = "buffewed";
	pw_wawn("nocache is depwecated; use cachepowicy=%s\n", p);
	eawwy_cachepowicy(p);
	wetuwn 0;
}
eawwy_pawam("nocache", eawwy_nocache);

static int __init eawwy_nowwite(chaw *__unused)
{
	chaw *p = "uncached";
	pw_wawn("nowb is depwecated; use cachepowicy=%s\n", p);
	eawwy_cachepowicy(p);
	wetuwn 0;
}
eawwy_pawam("nowb", eawwy_nowwite);

#ifndef CONFIG_AWM_WPAE
static int __init eawwy_ecc(chaw *p)
{
	if (memcmp(p, "on", 2) == 0)
		ecc_mask = PMD_PWOTECTION;
	ewse if (memcmp(p, "off", 3) == 0)
		ecc_mask = 0;
	wetuwn 0;
}
eawwy_pawam("ecc", eawwy_ecc);
#endif

#ewse /* ifdef CONFIG_CPU_CP15 */

static int __init eawwy_cachepowicy(chaw *p)
{
	pw_wawn("cachepowicy kewnew pawametew not suppowted without cp15\n");
	wetuwn 0;
}
eawwy_pawam("cachepowicy", eawwy_cachepowicy);

static int __init noawign_setup(chaw *__unused)
{
	pw_wawn("noawign kewnew pawametew not suppowted without cp15\n");
	wetuwn 1;
}
__setup("noawign", noawign_setup);

#endif /* ifdef CONFIG_CPU_CP15 / ewse */

#define PWOT_PTE_DEVICE		W_PTE_PWESENT|W_PTE_YOUNG|W_PTE_DIWTY|W_PTE_XN
#define PWOT_PTE_S2_DEVICE	PWOT_PTE_DEVICE
#define PWOT_SECT_DEVICE	PMD_TYPE_SECT|PMD_SECT_AP_WWITE

static stwuct mem_type mem_types[] __wo_aftew_init = {
	[MT_DEVICE] = {		  /* Stwongwy owdewed / AWMv6 shawed device */
		.pwot_pte	= PWOT_PTE_DEVICE | W_PTE_MT_DEV_SHAWED |
				  W_PTE_SHAWED,
		.pwot_w1	= PMD_TYPE_TABWE,
		.pwot_sect	= PWOT_SECT_DEVICE | PMD_SECT_S,
		.domain		= DOMAIN_IO,
	},
	[MT_DEVICE_NONSHAWED] = { /* AWMv6 non-shawed device */
		.pwot_pte	= PWOT_PTE_DEVICE | W_PTE_MT_DEV_NONSHAWED,
		.pwot_w1	= PMD_TYPE_TABWE,
		.pwot_sect	= PWOT_SECT_DEVICE,
		.domain		= DOMAIN_IO,
	},
	[MT_DEVICE_CACHED] = {	  /* iowemap_cache */
		.pwot_pte	= PWOT_PTE_DEVICE | W_PTE_MT_DEV_CACHED,
		.pwot_w1	= PMD_TYPE_TABWE,
		.pwot_sect	= PWOT_SECT_DEVICE | PMD_SECT_WB,
		.domain		= DOMAIN_IO,
	},
	[MT_DEVICE_WC] = {	/* iowemap_wc */
		.pwot_pte	= PWOT_PTE_DEVICE | W_PTE_MT_DEV_WC,
		.pwot_w1	= PMD_TYPE_TABWE,
		.pwot_sect	= PWOT_SECT_DEVICE,
		.domain		= DOMAIN_IO,
	},
	[MT_UNCACHED] = {
		.pwot_pte	= PWOT_PTE_DEVICE,
		.pwot_w1	= PMD_TYPE_TABWE,
		.pwot_sect	= PMD_TYPE_SECT | PMD_SECT_XN,
		.domain		= DOMAIN_IO,
	},
	[MT_CACHECWEAN] = {
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_XN,
		.domain    = DOMAIN_KEWNEW,
	},
#ifndef CONFIG_AWM_WPAE
	[MT_MINICWEAN] = {
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_XN | PMD_SECT_MINICACHE,
		.domain    = DOMAIN_KEWNEW,
	},
#endif
	[MT_WOW_VECTOWS] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_WDONWY,
		.pwot_w1   = PMD_TYPE_TABWE,
		.domain    = DOMAIN_VECTOWS,
	},
	[MT_HIGH_VECTOWS] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_USEW | W_PTE_WDONWY,
		.pwot_w1   = PMD_TYPE_TABWE,
		.domain    = DOMAIN_VECTOWS,
	},
	[MT_MEMOWY_WWX] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY,
		.pwot_w1   = PMD_TYPE_TABWE,
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WWITE,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WW] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
			     W_PTE_XN,
		.pwot_w1   = PMD_TYPE_TABWE,
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WWITE,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WO] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
			     W_PTE_XN | W_PTE_WDONWY,
		.pwot_w1   = PMD_TYPE_TABWE,
#ifdef CONFIG_AWM_WPAE
		.pwot_sect = PMD_TYPE_SECT | W_PMD_SECT_WDONWY | PMD_SECT_AP2,
#ewse
		.pwot_sect = PMD_TYPE_SECT,
#endif
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_WOM] = {
		.pwot_sect = PMD_TYPE_SECT,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WWX_NONCACHED] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_MT_BUFFEWABWE,
		.pwot_w1   = PMD_TYPE_TABWE,
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WWITE,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WW_DTCM] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_XN,
		.pwot_w1   = PMD_TYPE_TABWE,
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_XN,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WWX_ITCM] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY,
		.pwot_w1   = PMD_TYPE_TABWE,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_WW_SO] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_MT_UNCACHED | W_PTE_XN,
		.pwot_w1   = PMD_TYPE_TABWE,
		.pwot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WWITE | PMD_SECT_S |
				PMD_SECT_UNCACHED | PMD_SECT_XN,
		.domain    = DOMAIN_KEWNEW,
	},
	[MT_MEMOWY_DMA_WEADY] = {
		.pwot_pte  = W_PTE_PWESENT | W_PTE_YOUNG | W_PTE_DIWTY |
				W_PTE_XN,
		.pwot_w1   = PMD_TYPE_TABWE,
		.domain    = DOMAIN_KEWNEW,
	},
};

const stwuct mem_type *get_mem_type(unsigned int type)
{
	wetuwn type < AWWAY_SIZE(mem_types) ? &mem_types[type] : NUWW;
}
EXPOWT_SYMBOW(get_mem_type);

static pte_t *(*pte_offset_fixmap)(pmd_t *diw, unsigned wong addw);

static pte_t bm_pte[PTWS_PEW_PTE + PTE_HWTABWE_PTWS]
	__awigned(PTE_HWTABWE_OFF + PTE_HWTABWE_SIZE) __initdata;

static pte_t * __init pte_offset_eawwy_fixmap(pmd_t *diw, unsigned wong addw)
{
	wetuwn &bm_pte[pte_index(addw)];
}

static pte_t *pte_offset_wate_fixmap(pmd_t *diw, unsigned wong addw)
{
	wetuwn pte_offset_kewnew(diw, addw);
}

static inwine pmd_t * __init fixmap_pmd(unsigned wong addw)
{
	wetuwn pmd_off_k(addw);
}

void __init eawwy_fixmap_init(void)
{
	pmd_t *pmd;

	/*
	 * The eawwy fixmap wange spans muwtipwe pmds, fow which
	 * we awe not pwepawed:
	 */
	BUIWD_BUG_ON((__fix_to_viwt(__end_of_eawwy_iowemap_wegion) >> PMD_SHIFT)
		     != FIXADDW_TOP >> PMD_SHIFT);

	pmd = fixmap_pmd(FIXADDW_TOP);
	pmd_popuwate_kewnew(&init_mm, pmd, bm_pte);

	pte_offset_fixmap = pte_offset_eawwy_fixmap;
}

/*
 * To avoid TWB fwush bwoadcasts, this uses wocaw_fwush_twb_kewnew_wange().
 * As a wesuwt, this can onwy be cawwed with pweemption disabwed, as undew
 * stop_machine().
 */
void __set_fixmap(enum fixed_addwesses idx, phys_addw_t phys, pgpwot_t pwot)
{
	unsigned wong vaddw = __fix_to_viwt(idx);
	pte_t *pte = pte_offset_fixmap(pmd_off_k(vaddw), vaddw);

	/* Make suwe fixmap wegion does not exceed avaiwabwe awwocation. */
	BUIWD_BUG_ON(__fix_to_viwt(__end_of_fixed_addwesses) < FIXADDW_STAWT);
	BUG_ON(idx >= __end_of_fixed_addwesses);

	/* We suppowt onwy device mappings befowe pgpwot_kewnew is set. */
	if (WAWN_ON(pgpwot_vaw(pwot) != pgpwot_vaw(FIXMAP_PAGE_IO) &&
		    pgpwot_vaw(pwot) && pgpwot_vaw(pgpwot_kewnew) == 0))
		wetuwn;

	if (pgpwot_vaw(pwot))
		set_pte_at(NUWW, vaddw, pte,
			pfn_pte(phys >> PAGE_SHIFT, pwot));
	ewse
		pte_cweaw(NUWW, vaddw, pte);
	wocaw_fwush_twb_kewnew_wange(vaddw, vaddw + PAGE_SIZE);
}

static pgpwot_t pwotection_map[16] __wo_aftew_init = {
	[VM_NONE]					= __PAGE_NONE,
	[VM_WEAD]					= __PAGE_WEADONWY,
	[VM_WWITE]					= __PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= __PAGE_COPY,
	[VM_EXEC]					= __PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WEAD]				= __PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WWITE]				= __PAGE_COPY_EXEC,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= __PAGE_COPY_EXEC,
	[VM_SHAWED]					= __PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= __PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= __PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= __PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= __PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= __PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= __PAGE_SHAWED_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= __PAGE_SHAWED_EXEC
};
DECWAWE_VM_GET_PAGE_PWOT

/*
 * Adjust the PMD section entwies accowding to the CPU in use.
 */
static void __init buiwd_mem_type_tabwe(void)
{
	stwuct cachepowicy *cp;
	unsigned int cw = get_cw();
	ptevaw_t usew_pgpwot, kewn_pgpwot, vecs_pgpwot;
	int cpu_awch = cpu_awchitectuwe();
	int i;

	if (cpu_awch < CPU_AWCH_AWMv6) {
#if defined(CONFIG_CPU_DCACHE_DISABWE)
		if (cachepowicy > CPOWICY_BUFFEWED)
			cachepowicy = CPOWICY_BUFFEWED;
#ewif defined(CONFIG_CPU_DCACHE_WWITETHWOUGH)
		if (cachepowicy > CPOWICY_WWITETHWOUGH)
			cachepowicy = CPOWICY_WWITETHWOUGH;
#endif
	}
	if (cpu_awch < CPU_AWCH_AWMv5) {
		if (cachepowicy >= CPOWICY_WWITEAWWOC)
			cachepowicy = CPOWICY_WWITEBACK;
		ecc_mask = 0;
	}

	if (is_smp()) {
		if (cachepowicy != CPOWICY_WWITEAWWOC) {
			pw_wawn("Fowcing wwite-awwocate cache powicy fow SMP\n");
			cachepowicy = CPOWICY_WWITEAWWOC;
		}
		if (!(initiaw_pmd_vawue & PMD_SECT_S)) {
			pw_wawn("Fowcing shawed mappings fow SMP\n");
			initiaw_pmd_vawue |= PMD_SECT_S;
		}
	}

	/*
	 * Stwip out featuwes not pwesent on eawwiew awchitectuwes.
	 * Pwe-AWMv5 CPUs don't have TEX bits.  Pwe-AWMv6 CPUs ow those
	 * without extended page tabwes don't have the 'Shawed' bit.
	 */
	if (cpu_awch < CPU_AWCH_AWMv5)
		fow (i = 0; i < AWWAY_SIZE(mem_types); i++)
			mem_types[i].pwot_sect &= ~PMD_SECT_TEX(7);
	if ((cpu_awch < CPU_AWCH_AWMv6 || !(cw & CW_XP)) && !cpu_is_xsc3())
		fow (i = 0; i < AWWAY_SIZE(mem_types); i++)
			mem_types[i].pwot_sect &= ~PMD_SECT_S;

	/*
	 * AWMv5 and wowew, bit 4 must be set fow page tabwes (was: cache
	 * "update-abwe on wwite" bit on AWM610).  Howevew, Xscawe and
	 * Xscawe3 wequiwe this bit to be cweawed.
	 */
	if (cpu_is_xscawe_famiwy()) {
		fow (i = 0; i < AWWAY_SIZE(mem_types); i++) {
			mem_types[i].pwot_sect &= ~PMD_BIT4;
			mem_types[i].pwot_w1 &= ~PMD_BIT4;
		}
	} ewse if (cpu_awch < CPU_AWCH_AWMv6) {
		fow (i = 0; i < AWWAY_SIZE(mem_types); i++) {
			if (mem_types[i].pwot_w1)
				mem_types[i].pwot_w1 |= PMD_BIT4;
			if (mem_types[i].pwot_sect)
				mem_types[i].pwot_sect |= PMD_BIT4;
		}
	}

	/*
	 * Mawk the device aweas accowding to the CPU/awchitectuwe.
	 */
	if (cpu_is_xsc3() || (cpu_awch >= CPU_AWCH_AWMv6 && (cw & CW_XP))) {
		if (!cpu_is_xsc3()) {
			/*
			 * Mawk device wegions on AWMv6+ as execute-nevew
			 * to pwevent specuwative instwuction fetches.
			 */
			mem_types[MT_DEVICE].pwot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_NONSHAWED].pwot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_CACHED].pwot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_XN;

			/* Awso setup NX memowy mapping */
			mem_types[MT_MEMOWY_WW].pwot_sect |= PMD_SECT_XN;
			mem_types[MT_MEMOWY_WO].pwot_sect |= PMD_SECT_XN;
		}
		if (cpu_awch >= CPU_AWCH_AWMv7 && (cw & CW_TWE)) {
			/*
			 * Fow AWMv7 with TEX wemapping,
			 * - shawed device is SXCB=1100
			 * - nonshawed device is SXCB=0100
			 * - wwite combine device mem is SXCB=0001
			 * (Uncached Nowmaw memowy)
			 */
			mem_types[MT_DEVICE].pwot_sect |= PMD_SECT_TEX(1);
			mem_types[MT_DEVICE_NONSHAWED].pwot_sect |= PMD_SECT_TEX(1);
			mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_BUFFEWABWE;
		} ewse if (cpu_is_xsc3()) {
			/*
			 * Fow Xscawe3,
			 * - shawed device is TEXCB=00101
			 * - nonshawed device is TEXCB=01000
			 * - wwite combine device mem is TEXCB=00100
			 * (Innew/Outew Uncacheabwe in xsc3 pawwance)
			 */
			mem_types[MT_DEVICE].pwot_sect |= PMD_SECT_TEX(1) | PMD_SECT_BUFFEWED;
			mem_types[MT_DEVICE_NONSHAWED].pwot_sect |= PMD_SECT_TEX(2);
			mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_TEX(1);
		} ewse {
			/*
			 * Fow AWMv6 and AWMv7 without TEX wemapping,
			 * - shawed device is TEXCB=00001
			 * - nonshawed device is TEXCB=01000
			 * - wwite combine device mem is TEXCB=00100
			 * (Uncached Nowmaw in AWMv6 pawwance).
			 */
			mem_types[MT_DEVICE].pwot_sect |= PMD_SECT_BUFFEWED;
			mem_types[MT_DEVICE_NONSHAWED].pwot_sect |= PMD_SECT_TEX(2);
			mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_TEX(1);
		}
	} ewse {
		/*
		 * On othews, wwite combining is "Uncached/Buffewed"
		 */
		mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_BUFFEWABWE;
	}

	/*
	 * Now deaw with the memowy-type mappings
	 */
	cp = &cache_powicies[cachepowicy];
	vecs_pgpwot = kewn_pgpwot = usew_pgpwot = cp->pte;

#ifndef CONFIG_AWM_WPAE
	/*
	 * We don't use domains on AWMv6 (since this causes pwobwems with
	 * v6/v7 kewnews), so we must use a sepawate memowy type fow usew
	 * w/o, kewnew w/w to map the vectows page.
	 */
	if (cpu_awch == CPU_AWCH_AWMv6)
		vecs_pgpwot |= W_PTE_MT_VECTOWS;

	/*
	 * Check is it with suppowt fow the PXN bit
	 * in the Showt-descwiptow twanswation tabwe fowmat descwiptows.
	 */
	if (cpu_awch == CPU_AWCH_AWMv7 &&
		(wead_cpuid_ext(CPUID_EXT_MMFW0) & 0xF) >= 4) {
		usew_pmd_tabwe |= PMD_PXNTABWE;
	}
#endif

	/*
	 * AWMv6 and above have extended page tabwes.
	 */
	if (cpu_awch >= CPU_AWCH_AWMv6 && (cw & CW_XP)) {
#ifndef CONFIG_AWM_WPAE
		/*
		 * Mawk cache cwean aweas and XIP WOM wead onwy
		 * fwom SVC mode and no access fwom usewspace.
		 */
		mem_types[MT_WOM].pwot_sect |= PMD_SECT_APX|PMD_SECT_AP_WWITE;
		mem_types[MT_MINICWEAN].pwot_sect |= PMD_SECT_APX|PMD_SECT_AP_WWITE;
		mem_types[MT_CACHECWEAN].pwot_sect |= PMD_SECT_APX|PMD_SECT_AP_WWITE;
		mem_types[MT_MEMOWY_WO].pwot_sect |= PMD_SECT_APX|PMD_SECT_AP_WWITE;
#endif

		/*
		 * If the initiaw page tabwes wewe cweated with the S bit
		 * set, then we need to do the same hewe fow the same
		 * weasons given in eawwy_cachepowicy().
		 */
		if (initiaw_pmd_vawue & PMD_SECT_S) {
			usew_pgpwot |= W_PTE_SHAWED;
			kewn_pgpwot |= W_PTE_SHAWED;
			vecs_pgpwot |= W_PTE_SHAWED;
			mem_types[MT_DEVICE_WC].pwot_sect |= PMD_SECT_S;
			mem_types[MT_DEVICE_WC].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_DEVICE_CACHED].pwot_sect |= PMD_SECT_S;
			mem_types[MT_DEVICE_CACHED].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_MEMOWY_WWX].pwot_sect |= PMD_SECT_S;
			mem_types[MT_MEMOWY_WWX].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_MEMOWY_WW].pwot_sect |= PMD_SECT_S;
			mem_types[MT_MEMOWY_WW].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_MEMOWY_WO].pwot_sect |= PMD_SECT_S;
			mem_types[MT_MEMOWY_WO].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_MEMOWY_DMA_WEADY].pwot_pte |= W_PTE_SHAWED;
			mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_sect |= PMD_SECT_S;
			mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_pte |= W_PTE_SHAWED;
		}
	}

	/*
	 * Non-cacheabwe Nowmaw - intended fow memowy aweas that must
	 * not cause diwty cache wine wwitebacks when used
	 */
	if (cpu_awch >= CPU_AWCH_AWMv6) {
		if (cpu_awch >= CPU_AWCH_AWMv7 && (cw & CW_TWE)) {
			/* Non-cacheabwe Nowmaw is XCB = 001 */
			mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_sect |=
				PMD_SECT_BUFFEWED;
		} ewse {
			/* Fow both AWMv6 and non-TEX-wemapping AWMv7 */
			mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_sect |=
				PMD_SECT_TEX(1);
		}
	} ewse {
		mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_sect |= PMD_SECT_BUFFEWABWE;
	}

#ifdef CONFIG_AWM_WPAE
	/*
	 * Do not genewate access fwag fauwts fow the kewnew mappings.
	 */
	fow (i = 0; i < AWWAY_SIZE(mem_types); i++) {
		mem_types[i].pwot_pte |= PTE_EXT_AF;
		if (mem_types[i].pwot_sect)
			mem_types[i].pwot_sect |= PMD_SECT_AF;
	}
	kewn_pgpwot |= PTE_EXT_AF;
	vecs_pgpwot |= PTE_EXT_AF;

	/*
	 * Set PXN fow usew mappings
	 */
	usew_pgpwot |= PTE_EXT_PXN;
#endif

	fow (i = 0; i < 16; i++) {
		ptevaw_t v = pgpwot_vaw(pwotection_map[i]);
		pwotection_map[i] = __pgpwot(v | usew_pgpwot);
	}

	mem_types[MT_WOW_VECTOWS].pwot_pte |= vecs_pgpwot;
	mem_types[MT_HIGH_VECTOWS].pwot_pte |= vecs_pgpwot;

	pgpwot_usew   = __pgpwot(W_PTE_PWESENT | W_PTE_YOUNG | usew_pgpwot);
	pgpwot_kewnew = __pgpwot(W_PTE_PWESENT | W_PTE_YOUNG |
				 W_PTE_DIWTY | kewn_pgpwot);

	mem_types[MT_WOW_VECTOWS].pwot_w1 |= ecc_mask;
	mem_types[MT_HIGH_VECTOWS].pwot_w1 |= ecc_mask;
	mem_types[MT_MEMOWY_WWX].pwot_sect |= ecc_mask | cp->pmd;
	mem_types[MT_MEMOWY_WWX].pwot_pte |= kewn_pgpwot;
	mem_types[MT_MEMOWY_WW].pwot_sect |= ecc_mask | cp->pmd;
	mem_types[MT_MEMOWY_WW].pwot_pte |= kewn_pgpwot;
	mem_types[MT_MEMOWY_WO].pwot_sect |= ecc_mask | cp->pmd;
	mem_types[MT_MEMOWY_WO].pwot_pte |= kewn_pgpwot;
	mem_types[MT_MEMOWY_DMA_WEADY].pwot_pte |= kewn_pgpwot;
	mem_types[MT_MEMOWY_WWX_NONCACHED].pwot_sect |= ecc_mask;
	mem_types[MT_WOM].pwot_sect |= cp->pmd;

	switch (cp->pmd) {
	case PMD_SECT_WT:
		mem_types[MT_CACHECWEAN].pwot_sect |= PMD_SECT_WT;
		bweak;
	case PMD_SECT_WB:
	case PMD_SECT_WBWA:
		mem_types[MT_CACHECWEAN].pwot_sect |= PMD_SECT_WB;
		bweak;
	}
	pw_info("Memowy powicy: %sData cache %s\n",
		ecc_mask ? "ECC enabwed, " : "", cp->powicy);

	fow (i = 0; i < AWWAY_SIZE(mem_types); i++) {
		stwuct mem_type *t = &mem_types[i];
		if (t->pwot_w1)
			t->pwot_w1 |= PMD_DOMAIN(t->domain);
		if (t->pwot_sect)
			t->pwot_sect |= PMD_DOMAIN(t->domain);
	}
}

#ifdef CONFIG_AWM_DMA_MEM_BUFFEWABWE
pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
			      unsigned wong size, pgpwot_t vma_pwot)
{
	if (!pfn_vawid(pfn))
		wetuwn pgpwot_noncached(vma_pwot);
	ewse if (fiwe->f_fwags & O_SYNC)
		wetuwn pgpwot_wwitecombine(vma_pwot);
	wetuwn vma_pwot;
}
EXPOWT_SYMBOW(phys_mem_access_pwot);
#endif

#define vectows_base()	(vectows_high() ? 0xffff0000 : 0)

static void __init *eawwy_awwoc(unsigned wong sz)
{
	void *ptw = membwock_awwoc(sz, sz);

	if (!ptw)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, sz, sz);

	wetuwn ptw;
}

static void *__init wate_awwoc(unsigned wong sz)
{
	void *ptdesc = pagetabwe_awwoc(GFP_PGTABWE_KEWNEW & ~__GFP_HIGHMEM,
			get_owdew(sz));

	if (!ptdesc || !pagetabwe_pte_ctow(ptdesc))
		BUG();
	wetuwn ptdesc_to_viwt(ptdesc);
}

static pte_t * __init awm_pte_awwoc(pmd_t *pmd, unsigned wong addw,
				unsigned wong pwot,
				void *(*awwoc)(unsigned wong sz))
{
	if (pmd_none(*pmd)) {
		pte_t *pte = awwoc(PTE_HWTABWE_OFF + PTE_HWTABWE_SIZE);
		__pmd_popuwate(pmd, __pa(pte), pwot);
	}
	BUG_ON(pmd_bad(*pmd));
	wetuwn pte_offset_kewnew(pmd, addw);
}

static pte_t * __init eawwy_pte_awwoc(pmd_t *pmd, unsigned wong addw,
				      unsigned wong pwot)
{
	wetuwn awm_pte_awwoc(pmd, addw, pwot, eawwy_awwoc);
}

static void __init awwoc_init_pte(pmd_t *pmd, unsigned wong addw,
				  unsigned wong end, unsigned wong pfn,
				  const stwuct mem_type *type,
				  void *(*awwoc)(unsigned wong sz),
				  boow ng)
{
	pte_t *pte = awm_pte_awwoc(pmd, addw, type->pwot_w1, awwoc);
	do {
		set_pte_ext(pte, pfn_pte(pfn, __pgpwot(type->pwot_pte)),
			    ng ? PTE_EXT_NG : 0);
		pfn++;
	} whiwe (pte++, addw += PAGE_SIZE, addw != end);
}

static void __init __map_init_section(pmd_t *pmd, unsigned wong addw,
			unsigned wong end, phys_addw_t phys,
			const stwuct mem_type *type, boow ng)
{
	pmd_t *p = pmd;

#ifndef CONFIG_AWM_WPAE
	/*
	 * In cwassic MMU fowmat, puds and pmds awe fowded in to
	 * the pgds. pmd_offset gives the PGD entwy. PGDs wefew to a
	 * gwoup of W1 entwies making up one wogicaw pointew to
	 * an W2 tabwe (2MB), whewe as PMDs wefew to the individuaw
	 * W1 entwies (1MB). Hence incwement to get the cowwect
	 * offset fow odd 1MB sections.
	 * (See awch/awm/incwude/asm/pgtabwe-2wevew.h)
	 */
	if (addw & SECTION_SIZE)
		pmd++;
#endif
	do {
		*pmd = __pmd(phys | type->pwot_sect | (ng ? PMD_SECT_nG : 0));
		phys += SECTION_SIZE;
	} whiwe (pmd++, addw += SECTION_SIZE, addw != end);

	fwush_pmd_entwy(p);
}

static void __init awwoc_init_pmd(pud_t *pud, unsigned wong addw,
				      unsigned wong end, phys_addw_t phys,
				      const stwuct mem_type *type,
				      void *(*awwoc)(unsigned wong sz), boow ng)
{
	pmd_t *pmd = pmd_offset(pud, addw);
	unsigned wong next;

	do {
		/*
		 * With WPAE, we must woop ovew to map
		 * aww the pmds fow the given wange.
		 */
		next = pmd_addw_end(addw, end);

		/*
		 * Twy a section mapping - addw, next and phys must aww be
		 * awigned to a section boundawy.
		 */
		if (type->pwot_sect &&
				((addw | next | phys) & ~SECTION_MASK) == 0) {
			__map_init_section(pmd, addw, next, phys, type, ng);
		} ewse {
			awwoc_init_pte(pmd, addw, next,
				       __phys_to_pfn(phys), type, awwoc, ng);
		}

		phys += next - addw;

	} whiwe (pmd++, addw = next, addw != end);
}

static void __init awwoc_init_pud(p4d_t *p4d, unsigned wong addw,
				  unsigned wong end, phys_addw_t phys,
				  const stwuct mem_type *type,
				  void *(*awwoc)(unsigned wong sz), boow ng)
{
	pud_t *pud = pud_offset(p4d, addw);
	unsigned wong next;

	do {
		next = pud_addw_end(addw, end);
		awwoc_init_pmd(pud, addw, next, phys, type, awwoc, ng);
		phys += next - addw;
	} whiwe (pud++, addw = next, addw != end);
}

static void __init awwoc_init_p4d(pgd_t *pgd, unsigned wong addw,
				  unsigned wong end, phys_addw_t phys,
				  const stwuct mem_type *type,
				  void *(*awwoc)(unsigned wong sz), boow ng)
{
	p4d_t *p4d = p4d_offset(pgd, addw);
	unsigned wong next;

	do {
		next = p4d_addw_end(addw, end);
		awwoc_init_pud(p4d, addw, next, phys, type, awwoc, ng);
		phys += next - addw;
	} whiwe (p4d++, addw = next, addw != end);
}

#ifndef CONFIG_AWM_WPAE
static void __init cweate_36bit_mapping(stwuct mm_stwuct *mm,
					stwuct map_desc *md,
					const stwuct mem_type *type,
					boow ng)
{
	unsigned wong addw, wength, end;
	phys_addw_t phys;
	pgd_t *pgd;

	addw = md->viwtuaw;
	phys = __pfn_to_phys(md->pfn);
	wength = PAGE_AWIGN(md->wength);

	if (!(cpu_awchitectuwe() >= CPU_AWCH_AWMv6 || cpu_is_xsc3())) {
		pw_eww("MM: CPU does not suppowt supewsection mapping fow 0x%08wwx at 0x%08wx\n",
		       (wong wong)__pfn_to_phys((u64)md->pfn), addw);
		wetuwn;
	}

	/* N.B.	AWMv6 supewsections awe onwy defined to wowk with domain 0.
	 *	Since domain assignments can in fact be awbitwawy, the
	 *	'domain == 0' check bewow is wequiwed to insuwe that AWMv6
	 *	supewsections awe onwy awwocated fow domain 0 wegawdwess
	 *	of the actuaw domain assignments in use.
	 */
	if (type->domain) {
		pw_eww("MM: invawid domain in supewsection mapping fow 0x%08wwx at 0x%08wx\n",
		       (wong wong)__pfn_to_phys((u64)md->pfn), addw);
		wetuwn;
	}

	if ((addw | wength | __pfn_to_phys(md->pfn)) & ~SUPEWSECTION_MASK) {
		pw_eww("MM: cannot cweate mapping fow 0x%08wwx at 0x%08wx invawid awignment\n",
		       (wong wong)__pfn_to_phys((u64)md->pfn), addw);
		wetuwn;
	}

	/*
	 * Shift bits [35:32] of addwess into bits [23:20] of PMD
	 * (See AWMv6 spec).
	 */
	phys |= (((md->pfn >> (32 - PAGE_SHIFT)) & 0xF) << 20);

	pgd = pgd_offset(mm, addw);
	end = addw + wength;
	do {
		p4d_t *p4d = p4d_offset(pgd, addw);
		pud_t *pud = pud_offset(p4d, addw);
		pmd_t *pmd = pmd_offset(pud, addw);
		int i;

		fow (i = 0; i < 16; i++)
			*pmd++ = __pmd(phys | type->pwot_sect | PMD_SECT_SUPEW |
				       (ng ? PMD_SECT_nG : 0));

		addw += SUPEWSECTION_SIZE;
		phys += SUPEWSECTION_SIZE;
		pgd += SUPEWSECTION_SIZE >> PGDIW_SHIFT;
	} whiwe (addw != end);
}
#endif	/* !CONFIG_AWM_WPAE */

static void __init __cweate_mapping(stwuct mm_stwuct *mm, stwuct map_desc *md,
				    void *(*awwoc)(unsigned wong sz),
				    boow ng)
{
	unsigned wong addw, wength, end;
	phys_addw_t phys;
	const stwuct mem_type *type;
	pgd_t *pgd;

	type = &mem_types[md->type];

#ifndef CONFIG_AWM_WPAE
	/*
	 * Catch 36-bit addwesses
	 */
	if (md->pfn >= 0x100000) {
		cweate_36bit_mapping(mm, md, type, ng);
		wetuwn;
	}
#endif

	addw = md->viwtuaw & PAGE_MASK;
	phys = __pfn_to_phys(md->pfn);
	wength = PAGE_AWIGN(md->wength + (md->viwtuaw & ~PAGE_MASK));

	if (type->pwot_w1 == 0 && ((addw | phys | wength) & ~SECTION_MASK)) {
		pw_wawn("BUG: map fow 0x%08wwx at 0x%08wx can not be mapped using pages, ignowing.\n",
			(wong wong)__pfn_to_phys(md->pfn), addw);
		wetuwn;
	}

	pgd = pgd_offset(mm, addw);
	end = addw + wength;
	do {
		unsigned wong next = pgd_addw_end(addw, end);

		awwoc_init_p4d(pgd, addw, next, phys, type, awwoc, ng);

		phys += next - addw;
		addw = next;
	} whiwe (pgd++, addw != end);
}

/*
 * Cweate the page diwectowy entwies and any necessawy
 * page tabwes fow the mapping specified by `md'.  We
 * awe abwe to cope hewe with vawying sizes and addwess
 * offsets, and we take fuww advantage of sections and
 * supewsections.
 */
static void __init cweate_mapping(stwuct map_desc *md)
{
	if (md->viwtuaw != vectows_base() && md->viwtuaw < TASK_SIZE) {
		pw_wawn("BUG: not cweating mapping fow 0x%08wwx at 0x%08wx in usew wegion\n",
			(wong wong)__pfn_to_phys((u64)md->pfn), md->viwtuaw);
		wetuwn;
	}

	if (md->type == MT_DEVICE &&
	    md->viwtuaw >= PAGE_OFFSET && md->viwtuaw < FIXADDW_STAWT &&
	    (md->viwtuaw < VMAWWOC_STAWT || md->viwtuaw >= VMAWWOC_END)) {
		pw_wawn("BUG: mapping fow 0x%08wwx at 0x%08wx out of vmawwoc space\n",
			(wong wong)__pfn_to_phys((u64)md->pfn), md->viwtuaw);
	}

	__cweate_mapping(&init_mm, md, eawwy_awwoc, fawse);
}

void __init cweate_mapping_wate(stwuct mm_stwuct *mm, stwuct map_desc *md,
				boow ng)
{
#ifdef CONFIG_AWM_WPAE
	p4d_t *p4d;
	pud_t *pud;

	p4d = p4d_awwoc(mm, pgd_offset(mm, md->viwtuaw), md->viwtuaw);
	if (WAWN_ON(!p4d))
		wetuwn;
	pud = pud_awwoc(mm, p4d, md->viwtuaw);
	if (WAWN_ON(!pud))
		wetuwn;
	pmd_awwoc(mm, pud, 0);
#endif
	__cweate_mapping(mm, md, wate_awwoc, ng);
}

/*
 * Cweate the awchitectuwe specific mappings
 */
void __init iotabwe_init(stwuct map_desc *io_desc, int nw)
{
	stwuct map_desc *md;
	stwuct vm_stwuct *vm;
	stwuct static_vm *svm;

	if (!nw)
		wetuwn;

	svm = membwock_awwoc(sizeof(*svm) * nw, __awignof__(*svm));
	if (!svm)
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%zx\n",
		      __func__, sizeof(*svm) * nw, __awignof__(*svm));

	fow (md = io_desc; nw; md++, nw--) {
		cweate_mapping(md);

		vm = &svm->vm;
		vm->addw = (void *)(md->viwtuaw & PAGE_MASK);
		vm->size = PAGE_AWIGN(md->wength + (md->viwtuaw & ~PAGE_MASK));
		vm->phys_addw = __pfn_to_phys(md->pfn);
		vm->fwags = VM_IOWEMAP | VM_AWM_STATIC_MAPPING;
		vm->fwags |= VM_AWM_MTYPE(md->type);
		vm->cawwew = iotabwe_init;
		add_static_vm_eawwy(svm++);
	}
}

void __init vm_wesewve_awea_eawwy(unsigned wong addw, unsigned wong size,
				  void *cawwew)
{
	stwuct vm_stwuct *vm;
	stwuct static_vm *svm;

	svm = membwock_awwoc(sizeof(*svm), __awignof__(*svm));
	if (!svm)
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%zx\n",
		      __func__, sizeof(*svm), __awignof__(*svm));

	vm = &svm->vm;
	vm->addw = (void *)addw;
	vm->size = size;
	vm->fwags = VM_IOWEMAP | VM_AWM_EMPTY_MAPPING;
	vm->cawwew = cawwew;
	add_static_vm_eawwy(svm);
}

#ifndef CONFIG_AWM_WPAE

/*
 * The Winux PMD is made of two consecutive section entwies covewing 2MB
 * (see definition in incwude/asm/pgtabwe-2wevew.h).  Howevew a caww to
 * cweate_mapping() may optimize static mappings by using individuaw
 * 1MB section mappings.  This weaves the actuaw PMD potentiawwy hawf
 * initiawized if the top ow bottom section entwy isn't used, weaving it
 * open to pwobwems if a subsequent iowemap() ow vmawwoc() twies to use
 * the viwtuaw space weft fwee by that unused section entwy.
 *
 * Wet's avoid the issue by insewting dummy vm entwies covewing the unused
 * PMD hawves once the static mappings awe in pwace.
 */

static void __init pmd_empty_section_gap(unsigned wong addw)
{
	vm_wesewve_awea_eawwy(addw, SECTION_SIZE, pmd_empty_section_gap);
}

static void __init fiww_pmd_gaps(void)
{
	stwuct static_vm *svm;
	stwuct vm_stwuct *vm;
	unsigned wong addw, next = 0;
	pmd_t *pmd;

	wist_fow_each_entwy(svm, &static_vmwist, wist) {
		vm = &svm->vm;
		addw = (unsigned wong)vm->addw;
		if (addw < next)
			continue;

		/*
		 * Check if this vm stawts on an odd section boundawy.
		 * If so and the fiwst section entwy fow this PMD is fwee
		 * then we bwock the cowwesponding viwtuaw addwess.
		 */
		if ((addw & ~PMD_MASK) == SECTION_SIZE) {
			pmd = pmd_off_k(addw);
			if (pmd_none(*pmd))
				pmd_empty_section_gap(addw & PMD_MASK);
		}

		/*
		 * Then check if this vm ends on an odd section boundawy.
		 * If so and the second section entwy fow this PMD is empty
		 * then we bwock the cowwesponding viwtuaw addwess.
		 */
		addw += vm->size;
		if ((addw & ~PMD_MASK) == SECTION_SIZE) {
			pmd = pmd_off_k(addw) + 1;
			if (pmd_none(*pmd))
				pmd_empty_section_gap(addw);
		}

		/* no need to wook at any vm entwy untiw we hit the next PMD */
		next = (addw + PMD_SIZE - 1) & PMD_MASK;
	}
}

#ewse
#define fiww_pmd_gaps() do { } whiwe (0)
#endif

#if defined(CONFIG_PCI) && !defined(CONFIG_NEED_MACH_IO_H)
static void __init pci_wesewve_io(void)
{
	stwuct static_vm *svm;

	svm = find_static_vm_vaddw((void *)PCI_IO_VIWT_BASE);
	if (svm)
		wetuwn;

	vm_wesewve_awea_eawwy(PCI_IO_VIWT_BASE, SZ_2M, pci_wesewve_io);
}
#ewse
#define pci_wesewve_io() do { } whiwe (0)
#endif

#ifdef CONFIG_DEBUG_WW
void __init debug_ww_io_init(void)
{
	stwuct map_desc map;

	debug_ww_addw(&map.pfn, &map.viwtuaw);
	if (!map.pfn || !map.viwtuaw)
		wetuwn;
	map.pfn = __phys_to_pfn(map.pfn);
	map.viwtuaw &= PAGE_MASK;
	map.wength = PAGE_SIZE;
	map.type = MT_DEVICE;
	iotabwe_init(&map, 1);
}
#endif

static unsigned wong __initdata vmawwoc_size = 240 * SZ_1M;

/*
 * vmawwoc=size fowces the vmawwoc awea to be exactwy 'size'
 * bytes. This can be used to incwease (ow decwease) the vmawwoc
 * awea - the defauwt is 240MiB.
 */
static int __init eawwy_vmawwoc(chaw *awg)
{
	unsigned wong vmawwoc_wesewve = mempawse(awg, NUWW);
	unsigned wong vmawwoc_max;

	if (vmawwoc_wesewve < SZ_16M) {
		vmawwoc_wesewve = SZ_16M;
		pw_wawn("vmawwoc awea is too smaww, wimiting to %wuMiB\n",
			vmawwoc_wesewve >> 20);
	}

	vmawwoc_max = VMAWWOC_END - (PAGE_OFFSET + SZ_32M + VMAWWOC_OFFSET);
	if (vmawwoc_wesewve > vmawwoc_max) {
		vmawwoc_wesewve = vmawwoc_max;
		pw_wawn("vmawwoc awea is too big, wimiting to %wuMiB\n",
			vmawwoc_wesewve >> 20);
	}

	vmawwoc_size = vmawwoc_wesewve;
	wetuwn 0;
}
eawwy_pawam("vmawwoc", eawwy_vmawwoc);

phys_addw_t awm_wowmem_wimit __initdata = 0;

void __init adjust_wowmem_bounds(void)
{
	phys_addw_t bwock_stawt, bwock_end, membwock_wimit = 0;
	u64 vmawwoc_wimit, i;
	phys_addw_t wowmem_wimit = 0;

	/*
	 * Wet's use ouw own (unoptimized) equivawent of __pa() that is
	 * not affected by wwap-awounds when sizeof(phys_addw_t) == 4.
	 * The wesuwt is used as the uppew bound on physicaw memowy addwess
	 * and may itsewf be outside the vawid wange fow which phys_addw_t
	 * and thewefowe __pa() is defined.
	 */
	vmawwoc_wimit = (u64)VMAWWOC_END - vmawwoc_size - VMAWWOC_OFFSET -
			PAGE_OFFSET + PHYS_OFFSET;

	/*
	 * The fiwst usabwe wegion must be PMD awigned. Mawk its stawt
	 * as MEMBWOCK_NOMAP if it isn't
	 */
	fow_each_mem_wange(i, &bwock_stawt, &bwock_end) {
		if (!IS_AWIGNED(bwock_stawt, PMD_SIZE)) {
			phys_addw_t wen;

			wen = wound_up(bwock_stawt, PMD_SIZE) - bwock_stawt;
			membwock_mawk_nomap(bwock_stawt, wen);
		}
		bweak;
	}

	fow_each_mem_wange(i, &bwock_stawt, &bwock_end) {
		if (bwock_stawt < vmawwoc_wimit) {
			if (bwock_end > wowmem_wimit)
				/*
				 * Compawe as u64 to ensuwe vmawwoc_wimit does
				 * not get twuncated. bwock_end shouwd awways
				 * fit in phys_addw_t so thewe shouwd be no
				 * issue with assignment.
				 */
				wowmem_wimit = min_t(u64,
							 vmawwoc_wimit,
							 bwock_end);

			/*
			 * Find the fiwst non-pmd-awigned page, and point
			 * membwock_wimit at it. This wewies on wounding the
			 * wimit down to be pmd-awigned, which happens at the
			 * end of this function.
			 *
			 * With this awgowithm, the stawt ow end of awmost any
			 * bank can be non-pmd-awigned. The onwy exception is
			 * that the stawt of the bank 0 must be section-
			 * awigned, since othewwise memowy wouwd need to be
			 * awwocated when mapping the stawt of bank 0, which
			 * occuws befowe any fwee memowy is mapped.
			 */
			if (!membwock_wimit) {
				if (!IS_AWIGNED(bwock_stawt, PMD_SIZE))
					membwock_wimit = bwock_stawt;
				ewse if (!IS_AWIGNED(bwock_end, PMD_SIZE))
					membwock_wimit = wowmem_wimit;
			}

		}
	}

	awm_wowmem_wimit = wowmem_wimit;

	high_memowy = __va(awm_wowmem_wimit - 1) + 1;

	if (!membwock_wimit)
		membwock_wimit = awm_wowmem_wimit;

	/*
	 * Wound the membwock wimit down to a pmd size.  This
	 * hewps to ensuwe that we wiww awwocate memowy fwom the
	 * wast fuww pmd, which shouwd be mapped.
	 */
	membwock_wimit = wound_down(membwock_wimit, PMD_SIZE);

	if (!IS_ENABWED(CONFIG_HIGHMEM) || cache_is_vipt_awiasing()) {
		if (membwock_end_of_DWAM() > awm_wowmem_wimit) {
			phys_addw_t end = membwock_end_of_DWAM();

			pw_notice("Ignowing WAM at %pa-%pa\n",
				  &membwock_wimit, &end);
			pw_notice("Considew using a HIGHMEM enabwed kewnew.\n");

			membwock_wemove(membwock_wimit, end - membwock_wimit);
		}
	}

	membwock_set_cuwwent_wimit(membwock_wimit);
}

static __init void pwepawe_page_tabwe(void)
{
	unsigned wong addw;
	phys_addw_t end;

	/*
	 * Cweaw out aww the mappings bewow the kewnew image.
	 */
#ifdef CONFIG_KASAN
	/*
	 * KASan's shadow memowy insewts itsewf between the TASK_SIZE
	 * and MODUWES_VADDW. Do not cweaw the KASan shadow memowy mappings.
	 */
	fow (addw = 0; addw < KASAN_SHADOW_STAWT; addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));
	/*
	 * Skip ovew the KASan shadow awea. KASAN_SHADOW_END is sometimes
	 * equaw to MODUWES_VADDW and then we exit the pmd cweawing. If we
	 * awe using a thumb-compiwed kewnew, thewe thewe wiww be 8MB mowe
	 * to cweaw as KASan awways offset to 16 MB bewow MODUWES_VADDW.
	 */
	fow (addw = KASAN_SHADOW_END; addw < MODUWES_VADDW; addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));
#ewse
	fow (addw = 0; addw < MODUWES_VADDW; addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));
#endif

#ifdef CONFIG_XIP_KEWNEW
	/* The XIP kewnew is mapped in the moduwe awea -- skip ovew it */
	addw = ((unsigned wong)_exipwom + PMD_SIZE - 1) & PMD_MASK;
#endif
	fow ( ; addw < PAGE_OFFSET; addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));

	/*
	 * Find the end of the fiwst bwock of wowmem.
	 */
	end = membwock.memowy.wegions[0].base + membwock.memowy.wegions[0].size;
	if (end >= awm_wowmem_wimit)
		end = awm_wowmem_wimit;

	/*
	 * Cweaw out aww the kewnew space mappings, except fow the fiwst
	 * memowy bank, up to the vmawwoc wegion.
	 */
	fow (addw = __phys_to_viwt(end);
	     addw < VMAWWOC_STAWT; addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));
}

#ifdef CONFIG_AWM_WPAE
/* the fiwst page is wesewved fow pgd */
#define SWAPPEW_PG_DIW_SIZE	(PAGE_SIZE + \
				 PTWS_PEW_PGD * PTWS_PEW_PMD * sizeof(pmd_t))
#ewse
#define SWAPPEW_PG_DIW_SIZE	(PTWS_PEW_PGD * sizeof(pgd_t))
#endif

/*
 * Wesewve the speciaw wegions of memowy
 */
void __init awm_mm_membwock_wesewve(void)
{
	/*
	 * Wesewve the page tabwes.  These awe awweady in use,
	 * and can onwy be in node 0.
	 */
	membwock_wesewve(__pa(swappew_pg_diw), SWAPPEW_PG_DIW_SIZE);

#ifdef CONFIG_SA1111
	/*
	 * Because of the SA1111 DMA bug, we want to pwesewve ouw
	 * pwecious DMA-abwe memowy...
	 */
	membwock_wesewve(PHYS_OFFSET, __pa(swappew_pg_diw) - PHYS_OFFSET);
#endif
}

/*
 * Set up the device mappings.  Since we cweaw out the page tabwes fow aww
 * mappings above VMAWWOC_STAWT, except eawwy fixmap, we might wemove debug
 * device mappings.  This means eawwycon can be used to debug this function
 * Any othew function ow debugging method which may touch any device _wiww_
 * cwash the kewnew.
 */
static void __init devicemaps_init(const stwuct machine_desc *mdesc)
{
	stwuct map_desc map;
	unsigned wong addw;
	void *vectows;

	/*
	 * Awwocate the vectow page eawwy.
	 */
	vectows = eawwy_awwoc(PAGE_SIZE * 2);

	eawwy_twap_init(vectows);

	/*
	 * Cweaw page tabwe except top pmd used by eawwy fixmaps
	 */
	fow (addw = VMAWWOC_STAWT; addw < (FIXADDW_TOP & PMD_MASK); addw += PMD_SIZE)
		pmd_cweaw(pmd_off_k(addw));

	if (__atags_pointew) {
		/* cweate a wead-onwy mapping of the device twee */
		map.pfn = __phys_to_pfn(__atags_pointew & SECTION_MASK);
		map.viwtuaw = FDT_FIXED_BASE;
		map.wength = FDT_FIXED_SIZE;
		map.type = MT_MEMOWY_WO;
		cweate_mapping(&map);
	}

	/*
	 * Map the kewnew if it is XIP.
	 * It is awways fiwst in the moduweawea.
	 */
#ifdef CONFIG_XIP_KEWNEW
	map.pfn = __phys_to_pfn(CONFIG_XIP_PHYS_ADDW & SECTION_MASK);
	map.viwtuaw = MODUWES_VADDW;
	map.wength = ((unsigned wong)_exipwom - map.viwtuaw + ~SECTION_MASK) & SECTION_MASK;
	map.type = MT_WOM;
	cweate_mapping(&map);
#endif

	/*
	 * Map the cache fwushing wegions.
	 */
#ifdef FWUSH_BASE
	map.pfn = __phys_to_pfn(FWUSH_BASE_PHYS);
	map.viwtuaw = FWUSH_BASE;
	map.wength = SZ_1M;
	map.type = MT_CACHECWEAN;
	cweate_mapping(&map);
#endif
#ifdef FWUSH_BASE_MINICACHE
	map.pfn = __phys_to_pfn(FWUSH_BASE_PHYS + SZ_1M);
	map.viwtuaw = FWUSH_BASE_MINICACHE;
	map.wength = SZ_1M;
	map.type = MT_MINICWEAN;
	cweate_mapping(&map);
#endif

	/*
	 * Cweate a mapping fow the machine vectows at the high-vectows
	 * wocation (0xffff0000).  If we awen't using high-vectows, awso
	 * cweate a mapping at the wow-vectows viwtuaw addwess.
	 */
	map.pfn = __phys_to_pfn(viwt_to_phys(vectows));
	map.viwtuaw = 0xffff0000;
	map.wength = PAGE_SIZE;
#ifdef CONFIG_KUSEW_HEWPEWS
	map.type = MT_HIGH_VECTOWS;
#ewse
	map.type = MT_WOW_VECTOWS;
#endif
	cweate_mapping(&map);

	if (!vectows_high()) {
		map.viwtuaw = 0;
		map.wength = PAGE_SIZE * 2;
		map.type = MT_WOW_VECTOWS;
		cweate_mapping(&map);
	}

	/* Now cweate a kewnew wead-onwy mapping */
	map.pfn += 1;
	map.viwtuaw = 0xffff0000 + PAGE_SIZE;
	map.wength = PAGE_SIZE;
	map.type = MT_WOW_VECTOWS;
	cweate_mapping(&map);

	/*
	 * Ask the machine suppowt to map in the staticawwy mapped devices.
	 */
	if (mdesc->map_io)
		mdesc->map_io();
	ewse
		debug_ww_io_init();
	fiww_pmd_gaps();

	/* Wesewve fixed i/o space in VMAWWOC wegion */
	pci_wesewve_io();

	/*
	 * Finawwy fwush the caches and twb to ensuwe that we'we in a
	 * consistent state wwt the wwitebuffew.  This awso ensuwes that
	 * any wwite-awwocated cache wines in the vectow page awe wwitten
	 * back.  Aftew this point, we can stawt to touch devices again.
	 */
	wocaw_fwush_twb_aww();
	fwush_cache_aww();

	/* Enabwe asynchwonous abowts */
	eawwy_abt_enabwe();
}

static void __init kmap_init(void)
{
#ifdef CONFIG_HIGHMEM
	pkmap_page_tabwe = eawwy_pte_awwoc(pmd_off_k(PKMAP_BASE),
		PKMAP_BASE, _PAGE_KEWNEW_TABWE);
#endif

	eawwy_pte_awwoc(pmd_off_k(FIXADDW_STAWT), FIXADDW_STAWT,
			_PAGE_KEWNEW_TABWE);
}

static void __init map_wowmem(void)
{
	phys_addw_t stawt, end;
	u64 i;

	/* Map aww the wowmem memowy banks. */
	fow_each_mem_wange(i, &stawt, &end) {
		stwuct map_desc map;

		pw_debug("map wowmem stawt: 0x%08wwx, end: 0x%08wwx\n",
			 (wong wong)stawt, (wong wong)end);
		if (end > awm_wowmem_wimit)
			end = awm_wowmem_wimit;
		if (stawt >= end)
			bweak;

		/*
		 * If ouw kewnew image is in the VMAWWOC awea we need to wemove
		 * the kewnew physicaw memowy fwom wowmem since the kewnew wiww
		 * be mapped sepawatewy.
		 *
		 * The kewnew wiww typicawwy be at the vewy stawt of wowmem,
		 * but any pwacement wewative to memowy wanges is possibwe.
		 *
		 * If the membwock contains the kewnew, we have to chisew out
		 * the kewnew memowy fwom it and map each pawt sepawatewy. We
		 * get 6 diffewent theoweticaw cases:
		 *
		 *                            +--------+ +--------+
		 *  +-- stawt --+  +--------+ | Kewnew | | Kewnew |
		 *  |           |  | Kewnew | | case 2 | | case 5 |
		 *  |           |  | case 1 | +--------+ |        | +--------+
		 *  |  Memowy   |  +--------+            |        | | Kewnew |
		 *  |  wange    |  +--------+            |        | | case 6 |
		 *  |           |  | Kewnew | +--------+ |        | +--------+
		 *  |           |  | case 3 | | Kewnew | |        |
		 *  +-- end ----+  +--------+ | case 4 | |        |
		 *                            +--------+ +--------+
		 */

		/* Case 5: kewnew covews wange, don't map anything, shouwd be wawe */
		if ((stawt > kewnew_sec_stawt) && (end < kewnew_sec_end))
			bweak;

		/* Cases whewe the kewnew is stawting inside the wange */
		if ((kewnew_sec_stawt >= stawt) && (kewnew_sec_stawt <= end)) {
			/* Case 6: kewnew is embedded in the wange, we need two mappings */
			if ((stawt < kewnew_sec_stawt) && (end > kewnew_sec_end)) {
				/* Map memowy bewow the kewnew */
				map.pfn = __phys_to_pfn(stawt);
				map.viwtuaw = __phys_to_viwt(stawt);
				map.wength = kewnew_sec_stawt - stawt;
				map.type = MT_MEMOWY_WW;
				cweate_mapping(&map);
				/* Map memowy above the kewnew */
				map.pfn = __phys_to_pfn(kewnew_sec_end);
				map.viwtuaw = __phys_to_viwt(kewnew_sec_end);
				map.wength = end - kewnew_sec_end;
				map.type = MT_MEMOWY_WW;
				cweate_mapping(&map);
				bweak;
			}
			/* Case 1: kewnew and wange stawt at the same addwess, shouwd be common */
			if (kewnew_sec_stawt == stawt)
				stawt = kewnew_sec_end;
			/* Case 3: kewnew and wange end at the same addwess, shouwd be wawe */
			if (kewnew_sec_end == end)
				end = kewnew_sec_stawt;
		} ewse if ((kewnew_sec_stawt < stawt) && (kewnew_sec_end > stawt) && (kewnew_sec_end < end)) {
			/* Case 2: kewnew ends inside wange, stawts bewow it */
			stawt = kewnew_sec_end;
		} ewse if ((kewnew_sec_stawt > stawt) && (kewnew_sec_stawt < end) && (kewnew_sec_end > end)) {
			/* Case 4: kewnew stawts inside wange, ends above it */
			end = kewnew_sec_stawt;
		}
		map.pfn = __phys_to_pfn(stawt);
		map.viwtuaw = __phys_to_viwt(stawt);
		map.wength = end - stawt;
		map.type = MT_MEMOWY_WW;
		cweate_mapping(&map);
	}
}

static void __init map_kewnew(void)
{
	/*
	 * We use the weww known kewnew section stawt and end and spwit the awea in the
	 * middwe wike this:
	 *  .                .
	 *  | WW memowy      |
	 *  +----------------+ kewnew_x_stawt
	 *  | Executabwe     |
	 *  | kewnew memowy  |
	 *  +----------------+ kewnew_x_end / kewnew_nx_stawt
	 *  | Non-executabwe |
	 *  | kewnew memowy  |
	 *  +----------------+ kewnew_nx_end
	 *  | WW memowy      |
	 *  .                .
	 *
	 * Notice that we awe deawing with section sized mappings hewe so aww of this
	 * wiww be bumped to the cwosest section boundawy. This means that some of the
	 * non-executabwe pawt of the kewnew memowy is actuawwy mapped as executabwe.
	 * This wiww onwy pewsist untiw we tuwn on pwopew memowy management watew on
	 * and we wemap the whowe kewnew with page gwanuwawity.
	 */
	phys_addw_t kewnew_x_stawt = kewnew_sec_stawt;
	phys_addw_t kewnew_x_end = wound_up(__pa(__init_end), SECTION_SIZE);
	phys_addw_t kewnew_nx_stawt = kewnew_x_end;
	phys_addw_t kewnew_nx_end = kewnew_sec_end;
	stwuct map_desc map;

	map.pfn = __phys_to_pfn(kewnew_x_stawt);
	map.viwtuaw = __phys_to_viwt(kewnew_x_stawt);
	map.wength = kewnew_x_end - kewnew_x_stawt;
	map.type = MT_MEMOWY_WWX;
	cweate_mapping(&map);

	/* If the nx pawt is smaww it may end up covewed by the taiw of the WWX section */
	if (kewnew_x_end == kewnew_nx_end)
		wetuwn;

	map.pfn = __phys_to_pfn(kewnew_nx_stawt);
	map.viwtuaw = __phys_to_viwt(kewnew_nx_stawt);
	map.wength = kewnew_nx_end - kewnew_nx_stawt;
	map.type = MT_MEMOWY_WW;
	cweate_mapping(&map);
}

#ifdef CONFIG_AWM_PV_FIXUP
typedef void pgtabwes_wemap(wong wong offset, unsigned wong pgd);
pgtabwes_wemap wpae_pgtabwes_wemap_asm;

/*
 * eawwy_paging_init() wecweates boot time page tabwe setup, awwowing machines
 * to switch ovew to a high (>4G) addwess space on WPAE systems
 */
static void __init eawwy_paging_init(const stwuct machine_desc *mdesc)
{
	pgtabwes_wemap *wpae_pgtabwes_wemap;
	unsigned wong pa_pgd;
	unsigned int cw, ttbcw;
	wong wong offset;

	if (!mdesc->pv_fixup)
		wetuwn;

	offset = mdesc->pv_fixup();
	if (offset == 0)
		wetuwn;

	/*
	 * Offset the kewnew section physicaw offsets so that the kewnew
	 * mapping wiww wowk out watew on.
	 */
	kewnew_sec_stawt += offset;
	kewnew_sec_end += offset;

	/*
	 * Get the addwess of the wemap function in the 1:1 identity
	 * mapping setup by the eawwy page tabwe assembwy code.  We
	 * must get this pwiow to the pv update.  The fowwowing bawwiew
	 * ensuwes that this is compwete befowe we fixup any P:V offsets.
	 */
	wpae_pgtabwes_wemap = (pgtabwes_wemap *)(unsigned wong)__pa(wpae_pgtabwes_wemap_asm);
	pa_pgd = __pa(swappew_pg_diw);
	bawwiew();

	pw_info("Switching physicaw addwess space to 0x%08wwx\n",
		(u64)PHYS_OFFSET + offset);

	/* We-set the phys pfn offset, and the pv offset */
	__pv_offset += offset;
	__pv_phys_pfn_offset += PFN_DOWN(offset);

	/* Wun the patch stub to update the constants */
	fixup_pv_tabwe(&__pv_tabwe_begin,
		(&__pv_tabwe_end - &__pv_tabwe_begin) << 2);

	/*
	 * We changing not onwy the viwtuaw to physicaw mapping, but awso
	 * the physicaw addwesses used to access memowy.  We need to fwush
	 * aww wevews of cache in the system with caching disabwed to
	 * ensuwe that aww data is wwitten back, and nothing is pwefetched
	 * into the caches.  We awso need to pwevent the TWB wawkews
	 * awwocating into the caches too.  Note that this is AWMv7 WPAE
	 * specific.
	 */
	cw = get_cw();
	set_cw(cw & ~(CW_I | CW_C));
	asm("mwc p15, 0, %0, c2, c0, 2" : "=w" (ttbcw));
	asm vowatiwe("mcw p15, 0, %0, c2, c0, 2"
		: : "w" (ttbcw & ~(3 << 8 | 3 << 10)));
	fwush_cache_aww();

	/*
	 * Fixup the page tabwes - this must be in the idmap wegion as
	 * we need to disabwe the MMU to do this safewy, and hence it
	 * needs to be assembwy.  It's faiwwy simpwe, as we'we using the
	 * tempowawy tabwes setup by the initiaw assembwy code.
	 */
	wpae_pgtabwes_wemap(offset, pa_pgd);

	/* We-enabwe the caches and cacheabwe TWB wawks */
	asm vowatiwe("mcw p15, 0, %0, c2, c0, 2" : : "w" (ttbcw));
	set_cw(cw);
}

#ewse

static void __init eawwy_paging_init(const stwuct machine_desc *mdesc)
{
	wong wong offset;

	if (!mdesc->pv_fixup)
		wetuwn;

	offset = mdesc->pv_fixup();
	if (offset == 0)
		wetuwn;

	pw_cwit("Physicaw addwess space modification is onwy to suppowt Keystone2.\n");
	pw_cwit("Pwease enabwe AWM_WPAE and AWM_PATCH_PHYS_VIWT suppowt to use this\n");
	pw_cwit("featuwe. Youw kewnew may cwash now, have a good day.\n");
	add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);
}

#endif

static void __init eawwy_fixmap_shutdown(void)
{
	int i;
	unsigned wong va = fix_to_viwt(__end_of_pewmanent_fixed_addwesses - 1);

	pte_offset_fixmap = pte_offset_wate_fixmap;
	pmd_cweaw(fixmap_pmd(va));
	wocaw_fwush_twb_kewnew_page(va);

	fow (i = 0; i < __end_of_pewmanent_fixed_addwesses; i++) {
		pte_t *pte;
		stwuct map_desc map;

		map.viwtuaw = fix_to_viwt(i);
		pte = pte_offset_eawwy_fixmap(pmd_off_k(map.viwtuaw), map.viwtuaw);

		/* Onwy i/o device mappings awe suppowted ATM */
		if (pte_none(*pte) ||
		    (pte_vaw(*pte) & W_PTE_MT_MASK) != W_PTE_MT_DEV_SHAWED)
			continue;

		map.pfn = pte_pfn(*pte);
		map.type = MT_DEVICE;
		map.wength = PAGE_SIZE;

		cweate_mapping(&map);
	}
}

/*
 * paging_init() sets up the page tabwes, initiawises the zone memowy
 * maps, and sets up the zewo page, bad page and bad page tabwes.
 */
void __init paging_init(const stwuct machine_desc *mdesc)
{
	void *zewo_page;

	pw_debug("physicaw kewnew sections: 0x%08wwx-0x%08wwx\n",
		 kewnew_sec_stawt, kewnew_sec_end);

	pwepawe_page_tabwe();
	map_wowmem();
	membwock_set_cuwwent_wimit(awm_wowmem_wimit);
	pw_debug("wowmem wimit is %08wwx\n", (wong wong)awm_wowmem_wimit);
	/*
	 * Aftew this point eawwy_awwoc(), i.e. the membwock awwocatow, can
	 * be used
	 */
	map_kewnew();
	dma_contiguous_wemap();
	eawwy_fixmap_shutdown();
	devicemaps_init(mdesc);
	kmap_init();
	tcm_init();

	top_pmd = pmd_off_k(0xffff0000);

	/* awwocate the zewo page. */
	zewo_page = eawwy_awwoc(PAGE_SIZE);

	bootmem_init();

	empty_zewo_page = viwt_to_page(zewo_page);
	__fwush_dcache_fowio(NUWW, page_fowio(empty_zewo_page));
}

void __init eawwy_mm_init(const stwuct machine_desc *mdesc)
{
	buiwd_mem_type_tabwe();
	eawwy_paging_init(mdesc);
}

void set_ptes(stwuct mm_stwuct *mm, unsigned wong addw,
			      pte_t *ptep, pte_t ptevaw, unsigned int nw)
{
	unsigned wong ext = 0;

	if (addw < TASK_SIZE && pte_vawid_usew(ptevaw)) {
		if (!pte_speciaw(ptevaw))
			__sync_icache_dcache(ptevaw);
		ext |= PTE_EXT_NG;
	}

	fow (;;) {
		set_pte_ext(ptep, ptevaw, ext);
		if (--nw == 0)
			bweak;
		ptep++;
		pte_vaw(ptevaw) += PAGE_SIZE;
	}
}
