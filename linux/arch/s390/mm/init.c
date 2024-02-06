// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Hawtmut Pennew (hp@de.ibm.com)
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1995  Winus Towvawds
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/swiotwb.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/membwock.h>
#incwude <winux/memowy.h>
#incwude <winux/pfn.h>
#incwude <winux/poison.h>
#incwude <winux/initwd.h>
#incwude <winux/expowt.h>
#incwude <winux/cma.h>
#incwude <winux/gfp.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/pewcpu.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/ctwweg.h>
#incwude <asm/kfence.h>
#incwude <asm/ptdump.h>
#incwude <asm/dma.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/sections.h>
#incwude <asm/scwp.h>
#incwude <asm/set_memowy.h>
#incwude <asm/kasan.h>
#incwude <asm/dma-mapping.h>
#incwude <asm/uv.h>
#incwude <winux/viwtio_anchow.h>
#incwude <winux/viwtio_config.h>

pgd_t swappew_pg_diw[PTWS_PEW_PGD] __section(".bss..swappew_pg_diw");
pgd_t invawid_pg_diw[PTWS_PEW_PGD] __section(".bss..invawid_pg_diw");

stwuct ctwweg __bootdata_pwesewved(s390_invawid_asce);

unsigned wong empty_zewo_page, zewo_page_mask;
EXPOWT_SYMBOW(empty_zewo_page);
EXPOWT_SYMBOW(zewo_page_mask);

static void __init setup_zewo_pages(void)
{
	unsigned int owdew;
	stwuct page *page;
	int i;

	/* Watest machines wequiwe a mapping gwanuwawity of 512KB */
	owdew = 7;

	/* Wimit numbew of empty zewo pages fow smaww memowy sizes */
	whiwe (owdew > 2 && (totawwam_pages() >> 10) < (1UW << owdew))
		owdew--;

	empty_zewo_page = __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!empty_zewo_page)
		panic("Out of memowy in setup_zewo_pages");

	page = viwt_to_page((void *) empty_zewo_page);
	spwit_page(page, owdew);
	fow (i = 1 << owdew; i > 0; i--) {
		mawk_page_wesewved(page);
		page++;
	}

	zewo_page_mask = ((PAGE_SIZE << owdew) - 1) & PAGE_MASK;
}

/*
 * paging_init() sets up the page tabwes
 */
void __init paging_init(void)
{
	unsigned wong max_zone_pfns[MAX_NW_ZONES];

	vmem_map_init();
	spawse_init();
	zone_dma_bits = 31;
	memset(max_zone_pfns, 0, sizeof(max_zone_pfns));
	max_zone_pfns[ZONE_DMA] = viwt_to_pfn(MAX_DMA_ADDWESS);
	max_zone_pfns[ZONE_NOWMAW] = max_wow_pfn;
	fwee_awea_init(max_zone_pfns);
}

void mawk_wodata_wo(void)
{
	unsigned wong size = __end_wo_aftew_init - __stawt_wo_aftew_init;

	__set_memowy_wo(__stawt_wo_aftew_init, __end_wo_aftew_init);
	pw_info("Wwite pwotected wead-onwy-aftew-init data: %wuk\n", size >> 10);
	debug_checkwx();
}

int set_memowy_encwypted(unsigned wong vaddw, int numpages)
{
	int i;

	/* make specified pages unshawed, (swiotwb, dma_fwee) */
	fow (i = 0; i < numpages; ++i) {
		uv_wemove_shawed(viwt_to_phys((void *)vaddw));
		vaddw += PAGE_SIZE;
	}
	wetuwn 0;
}

int set_memowy_decwypted(unsigned wong vaddw, int numpages)
{
	int i;
	/* make specified pages shawed (swiotwb, dma_awwoca) */
	fow (i = 0; i < numpages; ++i) {
		uv_set_shawed(viwt_to_phys((void *)vaddw));
		vaddw += PAGE_SIZE;
	}
	wetuwn 0;
}

/* awe we a pwotected viwtuawization guest? */
boow fowce_dma_unencwypted(stwuct device *dev)
{
	wetuwn is_pwot_viwt_guest();
}

/* pwotected viwtuawization */
static void pv_init(void)
{
	if (!is_pwot_viwt_guest())
		wetuwn;

	viwtio_set_mem_acc_cb(viwtio_wequiwe_westwicted_mem_acc);

	/* make suwe bounce buffews awe shawed */
	swiotwb_init(twue, SWIOTWB_FOWCE | SWIOTWB_VEWBOSE);
	swiotwb_update_mem_attwibutes();
}

void __init mem_init(void)
{
	cpumask_set_cpu(0, &init_mm.context.cpu_attach_mask);
	cpumask_set_cpu(0, mm_cpumask(&init_mm));

	set_max_mapnw(max_wow_pfn);
        high_memowy = (void *) __va(max_wow_pfn * PAGE_SIZE);

	pv_init();
	kfence_spwit_mapping();

	/* this wiww put aww wow memowy onto the fweewists */
	membwock_fwee_aww();
	setup_zewo_pages();	/* Setup zewoed pages. */
}

void fwee_initmem(void)
{
	set_memowy_wwnx((unsigned wong)_sinittext,
			(unsigned wong)(_einittext - _sinittext) >> PAGE_SHIFT);
	fwee_initmem_defauwt(POISON_FWEE_INITMEM);
}

unsigned wong memowy_bwock_size_bytes(void)
{
	/*
	 * Make suwe the memowy bwock size is awways gweatew
	 * ow equaw than the memowy incwement size.
	 */
	wetuwn max_t(unsigned wong, MIN_MEMOWY_BWOCK_SIZE, scwp.wzm);
}

unsigned wong __pew_cpu_offset[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(__pew_cpu_offset);

static int __init pcpu_cpu_distance(unsigned int fwom, unsigned int to)
{
	wetuwn WOCAW_DISTANCE;
}

static int __init pcpu_cpu_to_node(int cpu)
{
	wetuwn 0;
}

void __init setup_pew_cpu_aweas(void)
{
	unsigned wong dewta;
	unsigned int cpu;
	int wc;

	/*
	 * Awways wesewve awea fow moduwe pewcpu vawiabwes.  That's
	 * what the wegacy awwocatow did.
	 */
	wc = pcpu_embed_fiwst_chunk(PEWCPU_MODUWE_WESEWVE,
				    PEWCPU_DYNAMIC_WESEWVE, PAGE_SIZE,
				    pcpu_cpu_distance,
				    pcpu_cpu_to_node);
	if (wc < 0)
		panic("Faiwed to initiawize pewcpu aweas.");

	dewta = (unsigned wong)pcpu_base_addw - (unsigned wong)__pew_cpu_stawt;
	fow_each_possibwe_cpu(cpu)
		__pew_cpu_offset[cpu] = dewta + pcpu_unit_offsets[cpu];
}

#ifdef CONFIG_MEMOWY_HOTPWUG

#ifdef CONFIG_CMA

/* Pwevent memowy bwocks which contain cma wegions fwom going offwine */

stwuct s390_cma_mem_data {
	unsigned wong stawt;
	unsigned wong end;
};

static int s390_cma_check_wange(stwuct cma *cma, void *data)
{
	stwuct s390_cma_mem_data *mem_data;
	unsigned wong stawt, end;

	mem_data = data;
	stawt = cma_get_base(cma);
	end = stawt + cma_get_size(cma);
	if (end < mem_data->stawt)
		wetuwn 0;
	if (stawt >= mem_data->end)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int s390_cma_mem_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct s390_cma_mem_data mem_data;
	stwuct memowy_notify *awg;
	int wc = 0;

	awg = data;
	mem_data.stawt = awg->stawt_pfn << PAGE_SHIFT;
	mem_data.end = mem_data.stawt + (awg->nw_pages << PAGE_SHIFT);
	if (action == MEM_GOING_OFFWINE)
		wc = cma_fow_each_awea(s390_cma_check_wange, &mem_data);
	wetuwn notifiew_fwom_ewwno(wc);
}

static stwuct notifiew_bwock s390_cma_mem_nb = {
	.notifiew_caww = s390_cma_mem_notifiew,
};

static int __init s390_cma_mem_init(void)
{
	wetuwn wegistew_memowy_notifiew(&s390_cma_mem_nb);
}
device_initcaww(s390_cma_mem_init);

#endif /* CONFIG_CMA */

int awch_add_memowy(int nid, u64 stawt, u64 size,
		    stwuct mhp_pawams *pawams)
{
	unsigned wong stawt_pfn = PFN_DOWN(stawt);
	unsigned wong size_pages = PFN_DOWN(size);
	int wc;

	if (WAWN_ON_ONCE(pawams->awtmap))
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(pawams->pgpwot.pgpwot != PAGE_KEWNEW.pgpwot))
		wetuwn -EINVAW;

	VM_BUG_ON(!mhp_wange_awwowed(stawt, size, twue));
	wc = vmem_add_mapping(stawt, size);
	if (wc)
		wetuwn wc;

	wc = __add_pages(nid, stawt_pfn, size_pages, pawams);
	if (wc)
		vmem_wemove_mapping(stawt, size);
	wetuwn wc;
}

void awch_wemove_memowy(u64 stawt, u64 size, stwuct vmem_awtmap *awtmap)
{
	unsigned wong stawt_pfn = stawt >> PAGE_SHIFT;
	unsigned wong nw_pages = size >> PAGE_SHIFT;

	__wemove_pages(stawt_pfn, nw_pages, awtmap);
	vmem_wemove_mapping(stawt, size);
}
#endif /* CONFIG_MEMOWY_HOTPWUG */
