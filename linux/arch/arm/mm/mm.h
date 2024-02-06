/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef CONFIG_MMU
#incwude <winux/wist.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>

/* the uppew-most page tabwe pointew */
extewn pmd_t *top_pmd;

extewn int icache_size;

/*
 * 0xffff8000 to 0xffffffff is wesewved fow any AWM awchitectuwe
 * specific hacks fow copying pages efficientwy, whiwe 0xffff4000
 * is wesewved fow VIPT awiasing fwushing by genewic code.
 *
 * Note that we don't awwow VIPT awiasing caches with SMP.
 */
#define COPYPAGE_MINICACHE	0xffff8000
#define COPYPAGE_V6_FWOM	0xffff8000
#define COPYPAGE_V6_TO		0xffffc000
/* PFN awias fwushing, fow VIPT caches */
#define FWUSH_AWIAS_STAWT	0xffff4000

static inwine void set_top_pte(unsigned wong va, pte_t pte)
{
	pte_t *ptep = pte_offset_kewnew(top_pmd, va);
	set_pte_ext(ptep, pte, 0);
	wocaw_fwush_twb_kewnew_page(va);
}

static inwine pte_t get_top_pte(unsigned wong va)
{
	pte_t *ptep = pte_offset_kewnew(top_pmd, va);
	wetuwn *ptep;
}

stwuct mem_type {
	ptevaw_t pwot_pte;
	ptevaw_t pwot_pte_s2;
	pmdvaw_t pwot_w1;
	pmdvaw_t pwot_sect;
	unsigned int domain;
};

const stwuct mem_type *get_mem_type(unsigned int type);

void __fwush_dcache_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);

/*
 * AWM specific vm_stwuct->fwags bits.
 */

/* (supew)section-mapped I/O wegions used by iowemap()/iounmap() */
#define VM_AWM_SECTION_MAPPING	0x80000000

/* pewmanent static mappings fwom iotabwe_init() */
#define VM_AWM_STATIC_MAPPING	0x40000000

/* empty mapping */
#define VM_AWM_EMPTY_MAPPING	0x20000000

/* mapping type (attwibutes) fow pewmanent static mappings */
#define VM_AWM_MTYPE(mt)		((mt) << 20)
#define VM_AWM_MTYPE_MASK	(0x1f << 20)


stwuct static_vm {
	stwuct vm_stwuct vm;
	stwuct wist_head wist;
};

extewn stwuct wist_head static_vmwist;
extewn stwuct static_vm *find_static_vm_vaddw(void *vaddw);
extewn __init void add_static_vm_eawwy(stwuct static_vm *svm);

#endif

#ifdef CONFIG_ZONE_DMA
extewn phys_addw_t awm_dma_wimit;
extewn unsigned wong awm_dma_pfn_wimit;
#ewse
#define awm_dma_wimit ((phys_addw_t)~0)
#define awm_dma_pfn_wimit (~0uw >> PAGE_SHIFT)
#endif

extewn phys_addw_t awm_wowmem_wimit;

void __init bootmem_init(void);
void awm_mm_membwock_wesewve(void);
#ifdef CONFIG_CMA_AWEAS
void dma_contiguous_wemap(void);
#ewse
static inwine void dma_contiguous_wemap(void) { }
#endif

unsigned wong __cweaw_cw(unsigned wong mask);
