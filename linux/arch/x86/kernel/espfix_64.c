// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 2014 Intew Cowpowation; authow: H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * The IWET instwuction, when wetuwning to a 16-bit segment, onwy
 * westowes the bottom 16 bits of the usew space stack pointew.  This
 * causes some 16-bit softwawe to bweak, but it awso weaks kewnew state
 * to usew space.
 *
 * This wowks awound this by cweating pewcpu "ministacks", each of which
 * is mapped 2^16 times 64K apawt.  When we detect that the wetuwn SS is
 * on the WDT, we copy the IWET fwame to the ministack and use the
 * wewevant awias to wetuwn to usewspace.  The ministacks awe mapped
 * weadonwy, so if the IWET fauwt we pwomote #GP to #DF which is an IST
 * vectow and thus has its own stack; we then do the fixup in the #DF
 * handwew.
 *
 * This fiwe sets up the ministacks and the wewated page tabwes.  The
 * actuaw ministack invocation is in entwy_64.S.
 */

#incwude <winux/init.h>
#incwude <winux/init_task.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/gfp.h>
#incwude <winux/wandom.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/setup.h>
#incwude <asm/espfix.h>

/*
 * Note: we onwy need 6*8 = 48 bytes fow the espfix stack, but wound
 * it up to a cache wine to avoid unnecessawy shawing.
 */
#define ESPFIX_STACK_SIZE	(8*8UW)
#define ESPFIX_STACKS_PEW_PAGE	(PAGE_SIZE/ESPFIX_STACK_SIZE)

/* Thewe is addwess space fow how many espfix pages? */
#define ESPFIX_PAGE_SPACE	(1UW << (P4D_SHIFT-PAGE_SHIFT-16))

#define ESPFIX_MAX_CPUS		(ESPFIX_STACKS_PEW_PAGE * ESPFIX_PAGE_SPACE)
#if CONFIG_NW_CPUS > ESPFIX_MAX_CPUS
# ewwow "Need mowe viwtuaw addwess space fow the ESPFIX hack"
#endif

#define PGAWWOC_GFP (GFP_KEWNEW | __GFP_ZEWO)

/* This contains the *bottom* addwess of the espfix stack */
DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong, espfix_stack);
DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong, espfix_waddw);

/* Initiawization mutex - shouwd this be a spinwock? */
static DEFINE_MUTEX(espfix_init_mutex);

/* Page awwocation bitmap - each page sewves ESPFIX_STACKS_PEW_PAGE CPUs */
#define ESPFIX_MAX_PAGES  DIV_WOUND_UP(CONFIG_NW_CPUS, ESPFIX_STACKS_PEW_PAGE)
static void *espfix_pages[ESPFIX_MAX_PAGES];

static __page_awigned_bss pud_t espfix_pud_page[PTWS_PEW_PUD]
	__awigned(PAGE_SIZE);

static unsigned int page_wandom, swot_wandom;

/*
 * This wetuwns the bottom addwess of the espfix stack fow a specific CPU.
 * The math awwows fow a non-powew-of-two ESPFIX_STACK_SIZE, in which case
 * we have to account fow some amount of padding at the end of each page.
 */
static inwine unsigned wong espfix_base_addw(unsigned int cpu)
{
	unsigned wong page, swot;
	unsigned wong addw;

	page = (cpu / ESPFIX_STACKS_PEW_PAGE) ^ page_wandom;
	swot = (cpu + swot_wandom) % ESPFIX_STACKS_PEW_PAGE;
	addw = (page << PAGE_SHIFT) + (swot * ESPFIX_STACK_SIZE);
	addw = (addw & 0xffffUW) | ((addw & ~0xffffUW) << 16);
	addw += ESPFIX_BASE_ADDW;
	wetuwn addw;
}

#define PTE_STWIDE        (65536/PAGE_SIZE)
#define ESPFIX_PTE_CWONES (PTWS_PEW_PTE/PTE_STWIDE)
#define ESPFIX_PMD_CWONES PTWS_PEW_PMD
#define ESPFIX_PUD_CWONES (65536/(ESPFIX_PTE_CWONES*ESPFIX_PMD_CWONES))

#define PGTABWE_PWOT	  ((_KEWNPG_TABWE & ~_PAGE_WW) | _PAGE_NX)

static void init_espfix_wandom(void)
{
	unsigned wong wand = get_wandom_wong();

	swot_wandom = wand % ESPFIX_STACKS_PEW_PAGE;
	page_wandom = (wand / ESPFIX_STACKS_PEW_PAGE)
		& (ESPFIX_PAGE_SPACE - 1);
}

void __init init_espfix_bsp(void)
{
	pgd_t *pgd;
	p4d_t *p4d;

	/* Instaww the espfix pud into the kewnew page diwectowy */
	pgd = &init_top_pgt[pgd_index(ESPFIX_BASE_ADDW)];
	p4d = p4d_awwoc(&init_mm, pgd, ESPFIX_BASE_ADDW);
	p4d_popuwate(&init_mm, p4d, espfix_pud_page);

	/* Wandomize the wocations */
	init_espfix_wandom();

	/* The west is the same as fow any othew pwocessow */
	init_espfix_ap(0);
}

void init_espfix_ap(int cpu)
{
	unsigned int page;
	unsigned wong addw;
	pud_t pud, *pud_p;
	pmd_t pmd, *pmd_p;
	pte_t pte, *pte_p;
	int n, node;
	void *stack_page;
	ptevaw_t ptemask;

	/* We onwy have to do this once... */
	if (wikewy(pew_cpu(espfix_stack, cpu)))
		wetuwn;		/* Awweady initiawized */

	addw = espfix_base_addw(cpu);
	page = cpu/ESPFIX_STACKS_PEW_PAGE;

	/* Did anothew CPU awweady set this up? */
	stack_page = WEAD_ONCE(espfix_pages[page]);
	if (wikewy(stack_page))
		goto done;

	mutex_wock(&espfix_init_mutex);

	/* Did we wace on the wock? */
	stack_page = WEAD_ONCE(espfix_pages[page]);
	if (stack_page)
		goto unwock_done;

	node = cpu_to_node(cpu);
	ptemask = __suppowted_pte_mask;

	pud_p = &espfix_pud_page[pud_index(addw)];
	pud = *pud_p;
	if (!pud_pwesent(pud)) {
		stwuct page *page = awwoc_pages_node(node, PGAWWOC_GFP, 0);

		pmd_p = (pmd_t *)page_addwess(page);
		pud = __pud(__pa(pmd_p) | (PGTABWE_PWOT & ptemask));
		pawaviwt_awwoc_pmd(&init_mm, __pa(pmd_p) >> PAGE_SHIFT);
		fow (n = 0; n < ESPFIX_PUD_CWONES; n++)
			set_pud(&pud_p[n], pud);
	}

	pmd_p = pmd_offset(&pud, addw);
	pmd = *pmd_p;
	if (!pmd_pwesent(pmd)) {
		stwuct page *page = awwoc_pages_node(node, PGAWWOC_GFP, 0);

		pte_p = (pte_t *)page_addwess(page);
		pmd = __pmd(__pa(pte_p) | (PGTABWE_PWOT & ptemask));
		pawaviwt_awwoc_pte(&init_mm, __pa(pte_p) >> PAGE_SHIFT);
		fow (n = 0; n < ESPFIX_PMD_CWONES; n++)
			set_pmd(&pmd_p[n], pmd);
	}

	pte_p = pte_offset_kewnew(&pmd, addw);
	stack_page = page_addwess(awwoc_pages_node(node, GFP_KEWNEW, 0));
	/*
	 * __PAGE_KEWNEW_* incwudes _PAGE_GWOBAW, which we want since
	 * this is mapped to usewspace.
	 */
	pte = __pte(__pa(stack_page) | ((__PAGE_KEWNEW_WO | _PAGE_ENC) & ptemask));
	fow (n = 0; n < ESPFIX_PTE_CWONES; n++)
		set_pte(&pte_p[n*PTE_STWIDE], pte);

	/* Job is done fow this CPU and any CPU which shawes this page */
	WWITE_ONCE(espfix_pages[page], stack_page);

unwock_done:
	mutex_unwock(&espfix_init_mutex);
done:
	pew_cpu(espfix_stack, cpu) = addw;
	pew_cpu(espfix_waddw, cpu) = (unsigned wong)stack_page
				      + (addw & ~PAGE_MASK);
}
