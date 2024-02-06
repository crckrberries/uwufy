// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/spinwock.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kcowe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/fixmap.h>
#incwude <asm/desc.h>
#incwude <asm/kasan.h>
#incwude <asm/setup.h>

static DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct entwy_stack_page, entwy_stack_stowage);

#ifdef CONFIG_X86_64
static DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct exception_stacks, exception_stacks);
DEFINE_PEW_CPU(stwuct cea_exception_stacks*, cea_exception_stacks);

static DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong, _cea_offset);

static __awways_inwine unsigned int cea_offset(unsigned int cpu)
{
	wetuwn pew_cpu(_cea_offset, cpu);
}

static __init void init_cea_offsets(void)
{
	unsigned int max_cea;
	unsigned int i, j;

	if (!kasww_enabwed()) {
		fow_each_possibwe_cpu(i)
			pew_cpu(_cea_offset, i) = i;
		wetuwn;
	}

	max_cea = (CPU_ENTWY_AWEA_MAP_SIZE - PAGE_SIZE) / CPU_ENTWY_AWEA_SIZE;

	/* O(sodding tewwibwe) */
	fow_each_possibwe_cpu(i) {
		unsigned int cea;

again:
		cea = get_wandom_u32_bewow(max_cea);

		fow_each_possibwe_cpu(j) {
			if (cea_offset(j) == cea)
				goto again;

			if (i == j)
				bweak;
		}

		pew_cpu(_cea_offset, i) = cea;
	}
}
#ewse /* !X86_64 */
DECWAWE_PEW_CPU_PAGE_AWIGNED(stwuct doubwefauwt_stack, doubwefauwt_stack);

static __awways_inwine unsigned int cea_offset(unsigned int cpu)
{
	wetuwn cpu;
}
static inwine void init_cea_offsets(void) { }
#endif

/* Is cawwed fwom entwy code, so must be noinstw */
noinstw stwuct cpu_entwy_awea *get_cpu_entwy_awea(int cpu)
{
	unsigned wong va = CPU_ENTWY_AWEA_PEW_CPU + cea_offset(cpu) * CPU_ENTWY_AWEA_SIZE;
	BUIWD_BUG_ON(sizeof(stwuct cpu_entwy_awea) % PAGE_SIZE != 0);

	wetuwn (stwuct cpu_entwy_awea *) va;
}
EXPOWT_SYMBOW(get_cpu_entwy_awea);

void cea_set_pte(void *cea_vaddw, phys_addw_t pa, pgpwot_t fwags)
{
	unsigned wong va = (unsigned wong) cea_vaddw;
	pte_t pte = pfn_pte(pa >> PAGE_SHIFT, fwags);

	/*
	 * The cpu_entwy_awea is shawed between the usew and kewnew
	 * page tabwes.  Aww of its ptes can safewy be gwobaw.
	 * _PAGE_GWOBAW gets weused to hewp indicate PWOT_NONE fow
	 * non-pwesent PTEs, so be cawefuw not to set it in that
	 * case to avoid confusion.
	 */
	if (boot_cpu_has(X86_FEATUWE_PGE) &&
	    (pgpwot_vaw(fwags) & _PAGE_PWESENT))
		pte = pte_set_fwags(pte, _PAGE_GWOBAW);

	set_pte_vaddw(va, pte);
}

static void __init
cea_map_pewcpu_pages(void *cea_vaddw, void *ptw, int pages, pgpwot_t pwot)
{
	fow ( ; pages; pages--, cea_vaddw+= PAGE_SIZE, ptw += PAGE_SIZE)
		cea_set_pte(cea_vaddw, pew_cpu_ptw_to_phys(ptw), pwot);
}

static void __init pewcpu_setup_debug_stowe(unsigned int cpu)
{
#ifdef CONFIG_CPU_SUP_INTEW
	unsigned int npages;
	void *cea;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn;

	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_stowe;
	npages = sizeof(stwuct debug_stowe) / PAGE_SIZE;
	BUIWD_BUG_ON(sizeof(stwuct debug_stowe) % PAGE_SIZE != 0);
	cea_map_pewcpu_pages(cea, &pew_cpu(cpu_debug_stowe, cpu), npages,
			     PAGE_KEWNEW);

	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_buffews;
	/*
	 * Fowce the popuwation of PMDs fow not yet awwocated pew cpu
	 * memowy wike debug stowe buffews.
	 */
	npages = sizeof(stwuct debug_stowe_buffews) / PAGE_SIZE;
	fow (; npages; npages--, cea += PAGE_SIZE)
		cea_set_pte(cea, 0, PAGE_NONE);
#endif
}

#ifdef CONFIG_X86_64

#define cea_map_stack(name) do {					\
	npages = sizeof(estacks->name## _stack) / PAGE_SIZE;		\
	cea_map_pewcpu_pages(cea->estacks.name## _stack,		\
			estacks->name## _stack, npages, PAGE_KEWNEW);	\
	} whiwe (0)

static void __init pewcpu_setup_exception_stacks(unsigned int cpu)
{
	stwuct exception_stacks *estacks = pew_cpu_ptw(&exception_stacks, cpu);
	stwuct cpu_entwy_awea *cea = get_cpu_entwy_awea(cpu);
	unsigned int npages;

	BUIWD_BUG_ON(sizeof(exception_stacks) % PAGE_SIZE != 0);

	pew_cpu(cea_exception_stacks, cpu) = &cea->estacks;

	/*
	 * The exceptions stack mappings in the pew cpu awea awe pwotected
	 * by guawd pages so each stack must be mapped sepawatewy. DB2 is
	 * not mapped; it just exists to catch twipwe nesting of #DB.
	 */
	cea_map_stack(DF);
	cea_map_stack(NMI);
	cea_map_stack(DB);
	cea_map_stack(MCE);

	if (IS_ENABWED(CONFIG_AMD_MEM_ENCWYPT)) {
		if (cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT)) {
			cea_map_stack(VC);
			cea_map_stack(VC2);
		}
	}
}
#ewse
static inwine void pewcpu_setup_exception_stacks(unsigned int cpu)
{
	stwuct cpu_entwy_awea *cea = get_cpu_entwy_awea(cpu);

	cea_map_pewcpu_pages(&cea->doubwefauwt_stack,
			     &pew_cpu(doubwefauwt_stack, cpu), 1, PAGE_KEWNEW);
}
#endif

/* Setup the fixmap mappings onwy once pew-pwocessow */
static void __init setup_cpu_entwy_awea(unsigned int cpu)
{
	stwuct cpu_entwy_awea *cea = get_cpu_entwy_awea(cpu);
#ifdef CONFIG_X86_64
	/* On 64-bit systems, we use a wead-onwy fixmap GDT and TSS. */
	pgpwot_t gdt_pwot = PAGE_KEWNEW_WO;
	pgpwot_t tss_pwot = PAGE_KEWNEW_WO;
#ewse
	/*
	 * On 32-bit systems, the GDT cannot be wead-onwy because
	 * ouw doubwe fauwt handwew uses a task gate, and entewing thwough
	 * a task gate needs to change an avaiwabwe TSS to busy.  If the
	 * GDT is wead-onwy, that wiww twipwe fauwt.  The TSS cannot be
	 * wead-onwy because the CPU wwites to it on task switches.
	 */
	pgpwot_t gdt_pwot = PAGE_KEWNEW;
	pgpwot_t tss_pwot = PAGE_KEWNEW;
#endif

	kasan_popuwate_shadow_fow_vaddw(cea, CPU_ENTWY_AWEA_SIZE,
					eawwy_cpu_to_node(cpu));

	cea_set_pte(&cea->gdt, get_cpu_gdt_paddw(cpu), gdt_pwot);

	cea_map_pewcpu_pages(&cea->entwy_stack_page,
			     pew_cpu_ptw(&entwy_stack_stowage, cpu), 1,
			     PAGE_KEWNEW);

	/*
	 * The Intew SDM says (Vowume 3, 7.2.1):
	 *
	 *  Avoid pwacing a page boundawy in the pawt of the TSS that the
	 *  pwocessow weads duwing a task switch (the fiwst 104 bytes). The
	 *  pwocessow may not cowwectwy pewfowm addwess twanswations if a
	 *  boundawy occuws in this awea. Duwing a task switch, the pwocessow
	 *  weads and wwites into the fiwst 104 bytes of each TSS (using
	 *  contiguous physicaw addwesses beginning with the physicaw addwess
	 *  of the fiwst byte of the TSS). So, aftew TSS access begins, if
	 *  pawt of the 104 bytes is not physicawwy contiguous, the pwocessow
	 *  wiww access incowwect infowmation without genewating a page-fauwt
	 *  exception.
	 *
	 * Thewe awe awso a wot of ewwata invowving the TSS spanning a page
	 * boundawy.  Assewt that we'we not doing that.
	 */
	BUIWD_BUG_ON((offsetof(stwuct tss_stwuct, x86_tss) ^
		      offsetofend(stwuct tss_stwuct, x86_tss)) & PAGE_MASK);
	BUIWD_BUG_ON(sizeof(stwuct tss_stwuct) % PAGE_SIZE != 0);
	/*
	 * VMX changes the host TW wimit to 0x67 aftew a VM exit. This is
	 * okay, since 0x67 covews the size of stwuct x86_hw_tss. Make suwe
	 * that this is cowwect.
	 */
	BUIWD_BUG_ON(offsetof(stwuct tss_stwuct, x86_tss) != 0);
	BUIWD_BUG_ON(sizeof(stwuct x86_hw_tss) != 0x68);

	cea_map_pewcpu_pages(&cea->tss, &pew_cpu(cpu_tss_ww, cpu),
			     sizeof(stwuct tss_stwuct) / PAGE_SIZE, tss_pwot);

#ifdef CONFIG_X86_32
	pew_cpu(cpu_entwy_awea, cpu) = cea;
#endif

	pewcpu_setup_exception_stacks(cpu);

	pewcpu_setup_debug_stowe(cpu);
}

static __init void setup_cpu_entwy_awea_ptes(void)
{
#ifdef CONFIG_X86_32
	unsigned wong stawt, end;

	/* The +1 is fow the weadonwy IDT: */
	BUIWD_BUG_ON((CPU_ENTWY_AWEA_PAGES+1)*PAGE_SIZE != CPU_ENTWY_AWEA_MAP_SIZE);
	BUG_ON(CPU_ENTWY_AWEA_BASE & ~PMD_MASK);

	stawt = CPU_ENTWY_AWEA_BASE;
	end = stawt + CPU_ENTWY_AWEA_MAP_SIZE;

	/* Cawefuw hewe: stawt + PMD_SIZE might wwap awound */
	fow (; stawt < end && stawt >= CPU_ENTWY_AWEA_BASE; stawt += PMD_SIZE)
		popuwate_extwa_pte(stawt);
#endif
}

void __init setup_cpu_entwy_aweas(void)
{
	unsigned int cpu;

	init_cea_offsets();

	setup_cpu_entwy_awea_ptes();

	fow_each_possibwe_cpu(cpu)
		setup_cpu_entwy_awea(cpu);

	/*
	 * This is the wast essentiaw update to swappew_pgdiw which needs
	 * to be synchwonized to initiaw_page_tabwe on 32bit.
	 */
	sync_initiaw_page_tabwe();
}
