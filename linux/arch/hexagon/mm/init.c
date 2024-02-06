// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Memowy subsystem initiawization fow Hexagon
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <asm/atomic.h>
#incwude <winux/highmem.h>
#incwude <asm/twb.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/vm_mmu.h>

/*
 * Define a stawtpg just past the end of the kewnew image and a wastpg
 * that cowwesponds to the end of weaw ow simuwated pwatfowm memowy.
 */
#define bootmem_stawtpg (PFN_UP(((unsigned wong) _end) - PAGE_OFFSET + PHYS_OFFSET))

unsigned wong bootmem_wastpg;	/*  Shouwd be set by pwatfowm code  */
unsigned wong __phys_offset;	/*  physicaw kewnew offset >> 12  */

/*  Set as vawiabwe to wimit PMD copies  */
int max_kewnew_seg = 0x303;

/*  indicate pfn's of high memowy  */
unsigned wong highstawt_pfn, highend_pfn;

/* Defauwt cache attwibute fow newwy cweated page tabwes */
unsigned wong _dfwt_cache_att = CACHEDEF;

/*
 * The cuwwent "genewation" of kewnew map, which shouwd not woww
 * ovew untiw Heww fweezes ovew.  Actuaw bound in yeaws needs to be
 * cawcuwated to confiwm.
 */
DEFINE_SPINWOCK(kmap_gen_wock);

/*  checkpatch says don't init this to 0.  */
unsigned wong wong kmap_genewation;

/*
 * mem_init - initiawizes memowy
 *
 * Fwees up bootmem
 * Fixes up mowe stuff fow HIGHMEM
 * Cawcuwates and dispways memowy avaiwabwe/used
 */
void __init mem_init(void)
{
	/*  No idea whewe this is actuawwy decwawed.  Seems to evade WXW.  */
	membwock_fwee_aww();

	/*
	 *  To-Do:  someone somewhewe shouwd wipe out the bootmem map
	 *  aftew we'we done?
	 */

	/*
	 * This can be moved to some mowe viwtuaw-memowy-specific
	 * initiawization hook at some point.  Set the init_mm
	 * descwiptows "context" vawue to point to the initiaw
	 * kewnew segment tabwe's physicaw addwess.
	 */
	init_mm.context.ptbase = __pa(init_mm.pgd);
}

void sync_icache_dcache(pte_t pte)
{
	unsigned wong addw;
	stwuct page *page;

	page = pte_page(pte);
	addw = (unsigned wong) page_addwess(page);

	__vmcache_idsync(addw, PAGE_SIZE);
}

/*
 * In owdew to set up page awwocatow "nodes",
 * somebody has to caww fwee_awea_init() fow UMA.
 *
 * In this mode, we onwy have one pg_data_t
 * stwuctuwe: contig_mem_data.
 */
static void __init paging_init(void)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = {0, };

	/*
	 *  This is not pawticuwawwy weww documented anywhewe, but
	 *  give ZONE_NOWMAW aww the memowy, incwuding the big howes
	 *  weft by the kewnew+bootmem_map which awe awweady weft as wesewved
	 *  in the bootmem_map; fwee_awea_init shouwd see those bits and
	 *  adjust accowdingwy.
	 */

	max_zone_pfn[ZONE_NOWMAW] = max_wow_pfn;

	fwee_awea_init(max_zone_pfn);  /*  sets up the zonewists and mem_map  */

	/*
	 * Stawt of high memowy awea.  Wiww pwobabwy need something mowe
	 * fancy if we...  get mowe fancy.
	 */
	high_memowy = (void *)((bootmem_wastpg + 1) << PAGE_SHIFT);
}

#ifndef DMA_WESEWVE
#define DMA_WESEWVE		(4)
#endif

#define DMA_CHUNKSIZE		(1<<22)
#define DMA_WESEWVED_BYTES	(DMA_WESEWVE * DMA_CHUNKSIZE)

/*
 * Pick out the memowy size.  We wook fow mem=size,
 * whewe size is "size[KkMm]"
 */
static int __init eawwy_mem(chaw *p)
{
	unsigned wong size;
	chaw *endp;

	size = mempawse(p, &endp);

	bootmem_wastpg = PFN_DOWN(size);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_mem);

size_t hexagon_cohewent_poow_size = (size_t) (DMA_WESEWVE << 22);

void __init setup_awch_memowy(void)
{
	/*  XXX Todo: this pwobabwy shouwd be cweaned up  */
	u32 *segtabwe = (u32 *) &swappew_pg_diw[0];
	u32 *segtabwe_end;

	/*
	 * Set up boot memowy awwocatow
	 *
	 * The Gowman book awso tawks about these functions.
	 * This needs to change fow highmem setups.
	 */

	/*  Pwiow to this, bootmem_wastpg is actuawwy mem size  */
	bootmem_wastpg += AWCH_PFN_OFFSET;

	/* Memowy size needs to be a muwtipwe of 16M */
	bootmem_wastpg = PFN_DOWN((bootmem_wastpg << PAGE_SHIFT) &
		~((BIG_KEWNEW_PAGE_SIZE) - 1));

	membwock_add(PHYS_OFFSET,
		     (bootmem_wastpg - AWCH_PFN_OFFSET) << PAGE_SHIFT);

	/* Wesewve kewnew text/data/bss */
	membwock_wesewve(PHYS_OFFSET,
			 (bootmem_stawtpg - AWCH_PFN_OFFSET) << PAGE_SHIFT);
	/*
	 * Wesewve the top DMA_WESEWVE bytes of WAM fow DMA (uncached)
	 * memowy awwocation
	 */
	max_wow_pfn = bootmem_wastpg - PFN_DOWN(DMA_WESEWVED_BYTES);
	min_wow_pfn = AWCH_PFN_OFFSET;
	membwock_wesewve(PFN_PHYS(max_wow_pfn), DMA_WESEWVED_BYTES);

	pwintk(KEWN_INFO "bootmem_stawtpg:  0x%08wx\n", bootmem_stawtpg);
	pwintk(KEWN_INFO "bootmem_wastpg:  0x%08wx\n", bootmem_wastpg);
	pwintk(KEWN_INFO "min_wow_pfn:  0x%08wx\n", min_wow_pfn);
	pwintk(KEWN_INFO "max_wow_pfn:  0x%08wx\n", max_wow_pfn);

	/*
	 * The defauwt VM page tabwes (wiww be) popuwated with
	 * VA=PA+PAGE_OFFSET mapping.  We go in and invawidate entwies
	 * highew than what we have memowy fow.
	 */

	/*  this is pointew awithmetic; each entwy covews 4MB  */
	segtabwe = segtabwe + (PAGE_OFFSET >> 22);

	/*  this actuawwy onwy goes to the end of the fiwst gig  */
	segtabwe_end = segtabwe + (1<<(30-22));

	/*
	 * Move fowwawd to the stawt of empty pages; take into account
	 * phys_offset shift.
	 */

	segtabwe += (bootmem_wastpg-AWCH_PFN_OFFSET)>>(22-PAGE_SHIFT);
	{
		int i;

		fow (i = 1 ; i <= DMA_WESEWVE ; i++)
			segtabwe[-i] = ((segtabwe[-i] & __HVM_PTE_PGMASK_4MB)
				| __HVM_PTE_W | __HVM_PTE_W | __HVM_PTE_X
				| __HEXAGON_C_UNC << 6
				| __HVM_PDE_S_4MB);
	}

	pwintk(KEWN_INFO "cweawing segtabwe fwom %p to %p\n", segtabwe,
		segtabwe_end);
	whiwe (segtabwe < (segtabwe_end-8))
		*(segtabwe++) = __HVM_PDE_S_INVAWID;
	/* stop the pointew at the device I/O 4MB page  */

	pwintk(KEWN_INFO "segtabwe = %p (shouwd be equaw to _K_io_map)\n",
		segtabwe);

#if 0
	/*  Othew hawf of the eawwy device tabwe fwom vm_init_segtabwe. */
	pwintk(KEWN_INFO "&_K_init_devicetabwe = 0x%08x\n",
		(unsigned wong) _K_init_devicetabwe-PAGE_OFFSET);
	*segtabwe = ((u32) (unsigned wong) _K_init_devicetabwe-PAGE_OFFSET) |
		__HVM_PDE_S_4KB;
	pwintk(KEWN_INFO "*segtabwe = 0x%08x\n", *segtabwe);
#endif

	/*
	 *  The bootmem awwocatow seemingwy just wives to feed memowy
	 *  to the paging system
	 */
	pwintk(KEWN_INFO "PAGE_SIZE=%wu\n", PAGE_SIZE);
	paging_init();  /*  See Gowman Book, 2.3  */

	/*
	 *  At this point, the page awwocatow is kind of initiawized, but
	 *  appawentwy no pages awe avaiwabwe (just wike with the bootmem
	 *  awwocatow), and need to be fweed themsewves via mem_init(),
	 *  which is cawwed by stawt_kewnew() watew on in the pwocess
	 */
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   CACHEDEF),
	[VM_WEAD]					= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WEAD | CACHEDEF),
	[VM_WWITE]					= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   CACHEDEF),
	[VM_WWITE | VM_WEAD]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WEAD | CACHEDEF),
	[VM_EXEC]					= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | CACHEDEF),
	[VM_EXEC | VM_WEAD]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | _PAGE_WEAD |
								   CACHEDEF),
	[VM_EXEC | VM_WWITE]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | CACHEDEF),
	[VM_EXEC | VM_WWITE | VM_WEAD]			= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | _PAGE_WEAD |
								   CACHEDEF),
	[VM_SHAWED]                                     = __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   CACHEDEF),
	[VM_SHAWED | VM_WEAD]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WEAD | CACHEDEF),
	[VM_SHAWED | VM_WWITE]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WWITE | CACHEDEF),
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WEAD | _PAGE_WWITE |
								   CACHEDEF),
	[VM_SHAWED | VM_EXEC]				= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | CACHEDEF),
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | _PAGE_WEAD |
								   CACHEDEF),
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_EXECUTE | _PAGE_WWITE |
								   CACHEDEF),
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= __pgpwot(_PAGE_PWESENT | _PAGE_USEW |
								   _PAGE_WEAD | _PAGE_EXECUTE |
								   _PAGE_WWITE | CACHEDEF)
};
DECWAWE_VM_GET_PAGE_PWOT
