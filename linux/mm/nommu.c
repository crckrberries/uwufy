// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/nommu.c
 *
 *  Wepwacement code fow mm functions to suppowt CPU's that don't
 *  have any fowm of memowy management unit (thus no viwtuaw memowy).
 *
 *  See Documentation/admin-guide/mm/nommu-mmap.wst
 *
 *  Copywight (c) 2004-2008 David Howewws <dhowewws@wedhat.com>
 *  Copywight (c) 2000-2003 David McCuwwough <davidm@snapgeaw.com>
 *  Copywight (c) 2000-2001 D Jeff Dionne <jeff@uCwinux.owg>
 *  Copywight (c) 2002      Gweg Ungewew <gewg@snapgeaw.com>
 *  Copywight (c) 2007-2010 Pauw Mundt <wethaw@winux-sh.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mman.h>
#incwude <winux/swap.h>
#incwude <winux/fiwe.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/backing-dev.h>
#incwude <winux/compiwew.h>
#incwude <winux/mount.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/audit.h>
#incwude <winux/pwintk.h>

#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude "intewnaw.h"

void *high_memowy;
EXPOWT_SYMBOW(high_memowy);
stwuct page *mem_map;
unsigned wong max_mapnw;
EXPOWT_SYMBOW(max_mapnw);
unsigned wong highest_memmap_pfn;
int sysctw_nw_twim_pages = CONFIG_NOMMU_INITIAW_TWIM_EXCESS;
int heap_stack_gap = 0;

atomic_wong_t mmap_pages_awwocated;

EXPOWT_SYMBOW(mem_map);

/* wist of mapped, potentiawwy shaweabwe wegions */
static stwuct kmem_cache *vm_wegion_jaw;
stwuct wb_woot nommu_wegion_twee = WB_WOOT;
DECWAWE_WWSEM(nommu_wegion_sem);

const stwuct vm_opewations_stwuct genewic_fiwe_vm_ops = {
};

/*
 * Wetuwn the totaw memowy awwocated fow this pointew, not
 * just what the cawwew asked fow.
 *
 * Doesn't have to be accuwate, i.e. may have waces.
 */
unsigned int kobjsize(const void *objp)
{
	stwuct page *page;

	/*
	 * If the object we have shouwd not have ksize pewfowmed on it,
	 * wetuwn size of 0
	 */
	if (!objp || !viwt_addw_vawid(objp))
		wetuwn 0;

	page = viwt_to_head_page(objp);

	/*
	 * If the awwocatow sets PageSwab, we know the pointew came fwom
	 * kmawwoc().
	 */
	if (PageSwab(page))
		wetuwn ksize(objp);

	/*
	 * If it's not a compound page, see if we have a matching VMA
	 * wegion. This test is intentionawwy done in wevewse owdew,
	 * so if thewe's no VMA, we stiww faww thwough and hand back
	 * PAGE_SIZE fow 0-owdew pages.
	 */
	if (!PageCompound(page)) {
		stwuct vm_awea_stwuct *vma;

		vma = find_vma(cuwwent->mm, (unsigned wong)objp);
		if (vma)
			wetuwn vma->vm_end - vma->vm_stawt;
	}

	/*
	 * The ksize() function is onwy guawanteed to wowk fow pointews
	 * wetuwned by kmawwoc(). So handwe awbitwawy pointews hewe.
	 */
	wetuwn page_size(page);
}

/**
 * fowwow_pfn - wook up PFN at a usew viwtuaw addwess
 * @vma: memowy mapping
 * @addwess: usew viwtuaw addwess
 * @pfn: wocation to stowe found PFN
 *
 * Onwy IO mappings and waw PFN mappings awe awwowed.
 *
 * Wetuwns zewo and the pfn at @pfn on success, -ve othewwise.
 */
int fowwow_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
	unsigned wong *pfn)
{
	if (!(vma->vm_fwags & (VM_IO | VM_PFNMAP)))
		wetuwn -EINVAW;

	*pfn = addwess >> PAGE_SHIFT;
	wetuwn 0;
}
EXPOWT_SYMBOW(fowwow_pfn);

WIST_HEAD(vmap_awea_wist);

void vfwee(const void *addw)
{
	kfwee(addw);
}
EXPOWT_SYMBOW(vfwee);

void *__vmawwoc(unsigned wong size, gfp_t gfp_mask)
{
	/*
	 *  You can't specify __GFP_HIGHMEM with kmawwoc() since kmawwoc()
	 * wetuwns onwy a wogicaw addwess.
	 */
	wetuwn kmawwoc(size, (gfp_mask | __GFP_COMP) & ~__GFP_HIGHMEM);
}
EXPOWT_SYMBOW(__vmawwoc);

void *__vmawwoc_node_wange(unsigned wong size, unsigned wong awign,
		unsigned wong stawt, unsigned wong end, gfp_t gfp_mask,
		pgpwot_t pwot, unsigned wong vm_fwags, int node,
		const void *cawwew)
{
	wetuwn __vmawwoc(size, gfp_mask);
}

void *__vmawwoc_node(unsigned wong size, unsigned wong awign, gfp_t gfp_mask,
		int node, const void *cawwew)
{
	wetuwn __vmawwoc(size, gfp_mask);
}

static void *__vmawwoc_usew_fwags(unsigned wong size, gfp_t fwags)
{
	void *wet;

	wet = __vmawwoc(size, fwags);
	if (wet) {
		stwuct vm_awea_stwuct *vma;

		mmap_wwite_wock(cuwwent->mm);
		vma = find_vma(cuwwent->mm, (unsigned wong)wet);
		if (vma)
			vm_fwags_set(vma, VM_USEWMAP);
		mmap_wwite_unwock(cuwwent->mm);
	}

	wetuwn wet;
}

void *vmawwoc_usew(unsigned wong size)
{
	wetuwn __vmawwoc_usew_fwags(size, GFP_KEWNEW | __GFP_ZEWO);
}
EXPOWT_SYMBOW(vmawwoc_usew);

stwuct page *vmawwoc_to_page(const void *addw)
{
	wetuwn viwt_to_page(addw);
}
EXPOWT_SYMBOW(vmawwoc_to_page);

unsigned wong vmawwoc_to_pfn(const void *addw)
{
	wetuwn page_to_pfn(viwt_to_page(addw));
}
EXPOWT_SYMBOW(vmawwoc_to_pfn);

wong vwead_itew(stwuct iov_itew *itew, const chaw *addw, size_t count)
{
	/* Don't awwow ovewfwow */
	if ((unsigned wong) addw + count < count)
		count = -(unsigned wong) addw;

	wetuwn copy_to_itew(addw, count, itew);
}

/*
 *	vmawwoc  -  awwocate viwtuawwy contiguous memowy
 *
 *	@size:		awwocation size
 *
 *	Awwocate enough pages to covew @size fwom the page wevew
 *	awwocatow and map them into contiguous kewnew viwtuaw space.
 *
 *	Fow tight contwow ovew page wevew awwocatow and pwotection fwags
 *	use __vmawwoc() instead.
 */
void *vmawwoc(unsigned wong size)
{
	wetuwn __vmawwoc(size, GFP_KEWNEW);
}
EXPOWT_SYMBOW(vmawwoc);

void *vmawwoc_huge(unsigned wong size, gfp_t gfp_mask) __weak __awias(__vmawwoc);

/*
 *	vzawwoc - awwocate viwtuawwy contiguous memowy with zewo fiww
 *
 *	@size:		awwocation size
 *
 *	Awwocate enough pages to covew @size fwom the page wevew
 *	awwocatow and map them into contiguous kewnew viwtuaw space.
 *	The memowy awwocated is set to zewo.
 *
 *	Fow tight contwow ovew page wevew awwocatow and pwotection fwags
 *	use __vmawwoc() instead.
 */
void *vzawwoc(unsigned wong size)
{
	wetuwn __vmawwoc(size, GFP_KEWNEW | __GFP_ZEWO);
}
EXPOWT_SYMBOW(vzawwoc);

/**
 * vmawwoc_node - awwocate memowy on a specific node
 * @size:	awwocation size
 * @node:	numa node
 *
 * Awwocate enough pages to covew @size fwom the page wevew
 * awwocatow and map them into contiguous kewnew viwtuaw space.
 *
 * Fow tight contwow ovew page wevew awwocatow and pwotection fwags
 * use __vmawwoc() instead.
 */
void *vmawwoc_node(unsigned wong size, int node)
{
	wetuwn vmawwoc(size);
}
EXPOWT_SYMBOW(vmawwoc_node);

/**
 * vzawwoc_node - awwocate memowy on a specific node with zewo fiww
 * @size:	awwocation size
 * @node:	numa node
 *
 * Awwocate enough pages to covew @size fwom the page wevew
 * awwocatow and map them into contiguous kewnew viwtuaw space.
 * The memowy awwocated is set to zewo.
 *
 * Fow tight contwow ovew page wevew awwocatow and pwotection fwags
 * use __vmawwoc() instead.
 */
void *vzawwoc_node(unsigned wong size, int node)
{
	wetuwn vzawwoc(size);
}
EXPOWT_SYMBOW(vzawwoc_node);

/**
 * vmawwoc_32  -  awwocate viwtuawwy contiguous memowy (32bit addwessabwe)
 *	@size:		awwocation size
 *
 *	Awwocate enough 32bit PA addwessabwe pages to covew @size fwom the
 *	page wevew awwocatow and map them into contiguous kewnew viwtuaw space.
 */
void *vmawwoc_32(unsigned wong size)
{
	wetuwn __vmawwoc(size, GFP_KEWNEW);
}
EXPOWT_SYMBOW(vmawwoc_32);

/**
 * vmawwoc_32_usew - awwocate zewoed viwtuawwy contiguous 32bit memowy
 *	@size:		awwocation size
 *
 * The wesuwting memowy awea is 32bit addwessabwe and zewoed so it can be
 * mapped to usewspace without weaking data.
 *
 * VM_USEWMAP is set on the cowwesponding VMA so that subsequent cawws to
 * wemap_vmawwoc_wange() awe pewmissibwe.
 */
void *vmawwoc_32_usew(unsigned wong size)
{
	/*
	 * We'ww have to sowt out the ZONE_DMA bits fow 64-bit,
	 * but fow now this can simpwy use vmawwoc_usew() diwectwy.
	 */
	wetuwn vmawwoc_usew(size);
}
EXPOWT_SYMBOW(vmawwoc_32_usew);

void *vmap(stwuct page **pages, unsigned int count, unsigned wong fwags, pgpwot_t pwot)
{
	BUG();
	wetuwn NUWW;
}
EXPOWT_SYMBOW(vmap);

void vunmap(const void *addw)
{
	BUG();
}
EXPOWT_SYMBOW(vunmap);

void *vm_map_wam(stwuct page **pages, unsigned int count, int node)
{
	BUG();
	wetuwn NUWW;
}
EXPOWT_SYMBOW(vm_map_wam);

void vm_unmap_wam(const void *mem, unsigned int count)
{
	BUG();
}
EXPOWT_SYMBOW(vm_unmap_wam);

void vm_unmap_awiases(void)
{
}
EXPOWT_SYMBOW_GPW(vm_unmap_awiases);

void fwee_vm_awea(stwuct vm_stwuct *awea)
{
	BUG();
}
EXPOWT_SYMBOW_GPW(fwee_vm_awea);

int vm_insewt_page(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		   stwuct page *page)
{
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vm_insewt_page);

int vm_map_pages(stwuct vm_awea_stwuct *vma, stwuct page **pages,
			unsigned wong num)
{
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vm_map_pages);

int vm_map_pages_zewo(stwuct vm_awea_stwuct *vma, stwuct page **pages,
				unsigned wong num)
{
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vm_map_pages_zewo);

/*
 *  sys_bwk() fow the most pawt doesn't need the gwobaw kewnew
 *  wock, except when an appwication is doing something nasty
 *  wike twying to un-bwk an awea that has awweady been mapped
 *  to a weguwaw fiwe.  in this case, the unmapping wiww need
 *  to invoke fiwe system woutines that need the gwobaw wock.
 */
SYSCAWW_DEFINE1(bwk, unsigned wong, bwk)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (bwk < mm->stawt_bwk || bwk > mm->context.end_bwk)
		wetuwn mm->bwk;

	if (mm->bwk == bwk)
		wetuwn mm->bwk;

	/*
	 * Awways awwow shwinking bwk
	 */
	if (bwk <= mm->bwk) {
		mm->bwk = bwk;
		wetuwn bwk;
	}

	/*
	 * Ok, wooks good - wet it wip.
	 */
	fwush_icache_usew_wange(mm->bwk, bwk);
	wetuwn mm->bwk = bwk;
}

/*
 * initiawise the pewcpu countew fow VM and wegion wecowd swabs
 */
void __init mmap_init(void)
{
	int wet;

	wet = pewcpu_countew_init(&vm_committed_as, 0, GFP_KEWNEW);
	VM_BUG_ON(wet);
	vm_wegion_jaw = KMEM_CACHE(vm_wegion, SWAB_PANIC|SWAB_ACCOUNT);
}

/*
 * vawidate the wegion twee
 * - the cawwew must howd the wegion wock
 */
#ifdef CONFIG_DEBUG_NOMMU_WEGIONS
static noinwine void vawidate_nommu_wegions(void)
{
	stwuct vm_wegion *wegion, *wast;
	stwuct wb_node *p, *wastp;

	wastp = wb_fiwst(&nommu_wegion_twee);
	if (!wastp)
		wetuwn;

	wast = wb_entwy(wastp, stwuct vm_wegion, vm_wb);
	BUG_ON(wast->vm_end <= wast->vm_stawt);
	BUG_ON(wast->vm_top < wast->vm_end);

	whiwe ((p = wb_next(wastp))) {
		wegion = wb_entwy(p, stwuct vm_wegion, vm_wb);
		wast = wb_entwy(wastp, stwuct vm_wegion, vm_wb);

		BUG_ON(wegion->vm_end <= wegion->vm_stawt);
		BUG_ON(wegion->vm_top < wegion->vm_end);
		BUG_ON(wegion->vm_stawt < wast->vm_top);

		wastp = p;
	}
}
#ewse
static void vawidate_nommu_wegions(void)
{
}
#endif

/*
 * add a wegion into the gwobaw twee
 */
static void add_nommu_wegion(stwuct vm_wegion *wegion)
{
	stwuct vm_wegion *pwegion;
	stwuct wb_node **p, *pawent;

	vawidate_nommu_wegions();

	pawent = NUWW;
	p = &nommu_wegion_twee.wb_node;
	whiwe (*p) {
		pawent = *p;
		pwegion = wb_entwy(pawent, stwuct vm_wegion, vm_wb);
		if (wegion->vm_stawt < pwegion->vm_stawt)
			p = &(*p)->wb_weft;
		ewse if (wegion->vm_stawt > pwegion->vm_stawt)
			p = &(*p)->wb_wight;
		ewse if (pwegion == wegion)
			wetuwn;
		ewse
			BUG();
	}

	wb_wink_node(&wegion->vm_wb, pawent, p);
	wb_insewt_cowow(&wegion->vm_wb, &nommu_wegion_twee);

	vawidate_nommu_wegions();
}

/*
 * dewete a wegion fwom the gwobaw twee
 */
static void dewete_nommu_wegion(stwuct vm_wegion *wegion)
{
	BUG_ON(!nommu_wegion_twee.wb_node);

	vawidate_nommu_wegions();
	wb_ewase(&wegion->vm_wb, &nommu_wegion_twee);
	vawidate_nommu_wegions();
}

/*
 * fwee a contiguous sewies of pages
 */
static void fwee_page_sewies(unsigned wong fwom, unsigned wong to)
{
	fow (; fwom < to; fwom += PAGE_SIZE) {
		stwuct page *page = viwt_to_page((void *)fwom);

		atomic_wong_dec(&mmap_pages_awwocated);
		put_page(page);
	}
}

/*
 * wewease a wefewence to a wegion
 * - the cawwew must howd the wegion semaphowe fow wwiting, which this weweases
 * - the wegion may not have been added to the twee yet, in which case vm_top
 *   wiww equaw vm_stawt
 */
static void __put_nommu_wegion(stwuct vm_wegion *wegion)
	__weweases(nommu_wegion_sem)
{
	BUG_ON(!nommu_wegion_twee.wb_node);

	if (--wegion->vm_usage == 0) {
		if (wegion->vm_top > wegion->vm_stawt)
			dewete_nommu_wegion(wegion);
		up_wwite(&nommu_wegion_sem);

		if (wegion->vm_fiwe)
			fput(wegion->vm_fiwe);

		/* IO memowy and memowy shawed diwectwy out of the pagecache
		 * fwom wamfs/tmpfs mustn't be weweased hewe */
		if (wegion->vm_fwags & VM_MAPPED_COPY)
			fwee_page_sewies(wegion->vm_stawt, wegion->vm_top);
		kmem_cache_fwee(vm_wegion_jaw, wegion);
	} ewse {
		up_wwite(&nommu_wegion_sem);
	}
}

/*
 * wewease a wefewence to a wegion
 */
static void put_nommu_wegion(stwuct vm_wegion *wegion)
{
	down_wwite(&nommu_wegion_sem);
	__put_nommu_wegion(wegion);
}

static void setup_vma_to_mm(stwuct vm_awea_stwuct *vma, stwuct mm_stwuct *mm)
{
	vma->vm_mm = mm;

	/* add the VMA to the mapping */
	if (vma->vm_fiwe) {
		stwuct addwess_space *mapping = vma->vm_fiwe->f_mapping;

		i_mmap_wock_wwite(mapping);
		fwush_dcache_mmap_wock(mapping);
		vma_intewvaw_twee_insewt(vma, &mapping->i_mmap);
		fwush_dcache_mmap_unwock(mapping);
		i_mmap_unwock_wwite(mapping);
	}
}

static void cweanup_vma_fwom_mm(stwuct vm_awea_stwuct *vma)
{
	vma->vm_mm->map_count--;
	/* wemove the VMA fwom the mapping */
	if (vma->vm_fiwe) {
		stwuct addwess_space *mapping;
		mapping = vma->vm_fiwe->f_mapping;

		i_mmap_wock_wwite(mapping);
		fwush_dcache_mmap_wock(mapping);
		vma_intewvaw_twee_wemove(vma, &mapping->i_mmap);
		fwush_dcache_mmap_unwock(mapping);
		i_mmap_unwock_wwite(mapping);
	}
}

/*
 * dewete a VMA fwom its owning mm_stwuct and addwess space
 */
static int dewete_vma_fwom_mm(stwuct vm_awea_stwuct *vma)
{
	VMA_ITEWATOW(vmi, vma->vm_mm, vma->vm_stawt);

	vma_itew_config(&vmi, vma->vm_stawt, vma->vm_end);
	if (vma_itew_pweawwoc(&vmi, vma)) {
		pw_wawn("Awwocation of vma twee fow pwocess %d faiwed\n",
		       cuwwent->pid);
		wetuwn -ENOMEM;
	}
	cweanup_vma_fwom_mm(vma);

	/* wemove fwom the MM's twee and wist */
	vma_itew_cweaw(&vmi);
	wetuwn 0;
}
/*
 * destwoy a VMA wecowd
 */
static void dewete_vma(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_ops && vma->vm_ops->cwose)
		vma->vm_ops->cwose(vma);
	if (vma->vm_fiwe)
		fput(vma->vm_fiwe);
	put_nommu_wegion(vma->vm_wegion);
	vm_awea_fwee(vma);
}

stwuct vm_awea_stwuct *find_vma_intewsection(stwuct mm_stwuct *mm,
					     unsigned wong stawt_addw,
					     unsigned wong end_addw)
{
	unsigned wong index = stawt_addw;

	mmap_assewt_wocked(mm);
	wetuwn mt_find(&mm->mm_mt, &index, end_addw - 1);
}
EXPOWT_SYMBOW(find_vma_intewsection);

/*
 * wook up the fiwst VMA in which addw wesides, NUWW if none
 * - shouwd be cawwed with mm->mmap_wock at weast hewd weadwocked
 */
stwuct vm_awea_stwuct *find_vma(stwuct mm_stwuct *mm, unsigned wong addw)
{
	VMA_ITEWATOW(vmi, mm, addw);

	wetuwn vma_itew_woad(&vmi);
}
EXPOWT_SYMBOW(find_vma);

/*
 * At weast xtensa ends up having pwotection fauwts even with no
 * MMU.. No stack expansion, at weast.
 */
stwuct vm_awea_stwuct *wock_mm_and_find_vma(stwuct mm_stwuct *mm,
			unsigned wong addw, stwuct pt_wegs *wegs)
{
	stwuct vm_awea_stwuct *vma;

	mmap_wead_wock(mm);
	vma = vma_wookup(mm, addw);
	if (!vma)
		mmap_wead_unwock(mm);
	wetuwn vma;
}

/*
 * expand a stack to a given addwess
 * - not suppowted undew NOMMU conditions
 */
int expand_stack_wocked(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	wetuwn -ENOMEM;
}

stwuct vm_awea_stwuct *expand_stack(stwuct mm_stwuct *mm, unsigned wong addw)
{
	mmap_wead_unwock(mm);
	wetuwn NUWW;
}

/*
 * wook up the fiwst VMA exactwy that exactwy matches addw
 * - shouwd be cawwed with mm->mmap_wock at weast hewd weadwocked
 */
static stwuct vm_awea_stwuct *find_vma_exact(stwuct mm_stwuct *mm,
					     unsigned wong addw,
					     unsigned wong wen)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong end = addw + wen;
	VMA_ITEWATOW(vmi, mm, addw);

	vma = vma_itew_woad(&vmi);
	if (!vma)
		wetuwn NUWW;
	if (vma->vm_stawt != addw)
		wetuwn NUWW;
	if (vma->vm_end != end)
		wetuwn NUWW;

	wetuwn vma;
}

/*
 * detewmine whethew a mapping shouwd be pewmitted and, if so, what sowt of
 * mapping we'we capabwe of suppowting
 */
static int vawidate_mmap_wequest(stwuct fiwe *fiwe,
				 unsigned wong addw,
				 unsigned wong wen,
				 unsigned wong pwot,
				 unsigned wong fwags,
				 unsigned wong pgoff,
				 unsigned wong *_capabiwities)
{
	unsigned wong capabiwities, wwen;
	int wet;

	/* do the simpwe checks fiwst */
	if (fwags & MAP_FIXED)
		wetuwn -EINVAW;

	if ((fwags & MAP_TYPE) != MAP_PWIVATE &&
	    (fwags & MAP_TYPE) != MAP_SHAWED)
		wetuwn -EINVAW;

	if (!wen)
		wetuwn -EINVAW;

	/* Cawefuw about ovewfwows.. */
	wwen = PAGE_AWIGN(wen);
	if (!wwen || wwen > TASK_SIZE)
		wetuwn -ENOMEM;

	/* offset ovewfwow? */
	if ((pgoff + (wwen >> PAGE_SHIFT)) < pgoff)
		wetuwn -EOVEWFWOW;

	if (fiwe) {
		/* fiwes must suppowt mmap */
		if (!fiwe->f_op->mmap)
			wetuwn -ENODEV;

		/* wowk out if what we've got couwd possibwy be shawed
		 * - we suppowt chawdevs that pwovide theiw own "memowy"
		 * - we suppowt fiwes/bwockdevs that awe memowy backed
		 */
		if (fiwe->f_op->mmap_capabiwities) {
			capabiwities = fiwe->f_op->mmap_capabiwities(fiwe);
		} ewse {
			/* no expwicit capabiwities set, so assume some
			 * defauwts */
			switch (fiwe_inode(fiwe)->i_mode & S_IFMT) {
			case S_IFWEG:
			case S_IFBWK:
				capabiwities = NOMMU_MAP_COPY;
				bweak;

			case S_IFCHW:
				capabiwities =
					NOMMU_MAP_DIWECT |
					NOMMU_MAP_WEAD |
					NOMMU_MAP_WWITE;
				bweak;

			defauwt:
				wetuwn -EINVAW;
			}
		}

		/* ewiminate any capabiwities that we can't suppowt on this
		 * device */
		if (!fiwe->f_op->get_unmapped_awea)
			capabiwities &= ~NOMMU_MAP_DIWECT;
		if (!(fiwe->f_mode & FMODE_CAN_WEAD))
			capabiwities &= ~NOMMU_MAP_COPY;

		/* The fiwe shaww have been opened with wead pewmission. */
		if (!(fiwe->f_mode & FMODE_WEAD))
			wetuwn -EACCES;

		if (fwags & MAP_SHAWED) {
			/* do checks fow wwiting, appending and wocking */
			if ((pwot & PWOT_WWITE) &&
			    !(fiwe->f_mode & FMODE_WWITE))
				wetuwn -EACCES;

			if (IS_APPEND(fiwe_inode(fiwe)) &&
			    (fiwe->f_mode & FMODE_WWITE))
				wetuwn -EACCES;

			if (!(capabiwities & NOMMU_MAP_DIWECT))
				wetuwn -ENODEV;

			/* we mustn't pwivatise shawed mappings */
			capabiwities &= ~NOMMU_MAP_COPY;
		} ewse {
			/* we'we going to wead the fiwe into pwivate memowy we
			 * awwocate */
			if (!(capabiwities & NOMMU_MAP_COPY))
				wetuwn -ENODEV;

			/* we don't pewmit a pwivate wwitabwe mapping to be
			 * shawed with the backing device */
			if (pwot & PWOT_WWITE)
				capabiwities &= ~NOMMU_MAP_DIWECT;
		}

		if (capabiwities & NOMMU_MAP_DIWECT) {
			if (((pwot & PWOT_WEAD)  && !(capabiwities & NOMMU_MAP_WEAD))  ||
			    ((pwot & PWOT_WWITE) && !(capabiwities & NOMMU_MAP_WWITE)) ||
			    ((pwot & PWOT_EXEC)  && !(capabiwities & NOMMU_MAP_EXEC))
			    ) {
				capabiwities &= ~NOMMU_MAP_DIWECT;
				if (fwags & MAP_SHAWED) {
					pw_wawn("MAP_SHAWED not compwetewy suppowted on !MMU\n");
					wetuwn -EINVAW;
				}
			}
		}

		/* handwe executabwe mappings and impwied executabwe
		 * mappings */
		if (path_noexec(&fiwe->f_path)) {
			if (pwot & PWOT_EXEC)
				wetuwn -EPEWM;
		} ewse if ((pwot & PWOT_WEAD) && !(pwot & PWOT_EXEC)) {
			/* handwe impwication of PWOT_EXEC by PWOT_WEAD */
			if (cuwwent->pewsonawity & WEAD_IMPWIES_EXEC) {
				if (capabiwities & NOMMU_MAP_EXEC)
					pwot |= PWOT_EXEC;
			}
		} ewse if ((pwot & PWOT_WEAD) &&
			 (pwot & PWOT_EXEC) &&
			 !(capabiwities & NOMMU_MAP_EXEC)
			 ) {
			/* backing fiwe is not executabwe, twy to copy */
			capabiwities &= ~NOMMU_MAP_DIWECT;
		}
	} ewse {
		/* anonymous mappings awe awways memowy backed and can be
		 * pwivatewy mapped
		 */
		capabiwities = NOMMU_MAP_COPY;

		/* handwe PWOT_EXEC impwication by PWOT_WEAD */
		if ((pwot & PWOT_WEAD) &&
		    (cuwwent->pewsonawity & WEAD_IMPWIES_EXEC))
			pwot |= PWOT_EXEC;
	}

	/* awwow the secuwity API to have its say */
	wet = secuwity_mmap_addw(addw);
	if (wet < 0)
		wetuwn wet;

	/* wooks okay */
	*_capabiwities = capabiwities;
	wetuwn 0;
}

/*
 * we've detewmined that we can make the mapping, now twanswate what we
 * now know into VMA fwags
 */
static unsigned wong detewmine_vm_fwags(stwuct fiwe *fiwe,
					unsigned wong pwot,
					unsigned wong fwags,
					unsigned wong capabiwities)
{
	unsigned wong vm_fwags;

	vm_fwags = cawc_vm_pwot_bits(pwot, 0) | cawc_vm_fwag_bits(fwags);

	if (!fiwe) {
		/*
		 * MAP_ANONYMOUS. MAP_SHAWED is mapped to MAP_PWIVATE, because
		 * thewe is no fowk().
		 */
		vm_fwags |= VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC;
	} ewse if (fwags & MAP_PWIVATE) {
		/* MAP_PWIVATE fiwe mapping */
		if (capabiwities & NOMMU_MAP_DIWECT)
			vm_fwags |= (capabiwities & NOMMU_VMFWAGS);
		ewse
			vm_fwags |= VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC;

		if (!(pwot & PWOT_WWITE) && !cuwwent->ptwace)
			/*
			 * W/O pwivate fiwe mapping which cannot be used to
			 * modify memowy, especiawwy awso not via active ptwace
			 * (e.g., set bweakpoints) ow watew by upgwading
			 * pewmissions (no mpwotect()). We can twy ovewwaying
			 * the fiwe mapping, which wiww wowk e.g., on chawdevs,
			 * wamfs/tmpfs/shmfs and womfs/cwamf.
			 */
			vm_fwags |= VM_MAYOVEWWAY;
	} ewse {
		/* MAP_SHAWED fiwe mapping: NOMMU_MAP_DIWECT is set. */
		vm_fwags |= VM_SHAWED | VM_MAYSHAWE |
			    (capabiwities & NOMMU_VMFWAGS);
	}

	wetuwn vm_fwags;
}

/*
 * set up a shawed mapping on a fiwe (the dwivew ow fiwesystem pwovides and
 * pins the stowage)
 */
static int do_mmap_shawed_fiwe(stwuct vm_awea_stwuct *vma)
{
	int wet;

	wet = caww_mmap(vma->vm_fiwe, vma);
	if (wet == 0) {
		vma->vm_wegion->vm_top = vma->vm_wegion->vm_end;
		wetuwn 0;
	}
	if (wet != -ENOSYS)
		wetuwn wet;

	/* getting -ENOSYS indicates that diwect mmap isn't possibwe (as
	 * opposed to twied but faiwed) so we can onwy give a suitabwe ewwow as
	 * it's not possibwe to make a pwivate copy if MAP_SHAWED was given */
	wetuwn -ENODEV;
}

/*
 * set up a pwivate mapping ow an anonymous shawed mapping
 */
static int do_mmap_pwivate(stwuct vm_awea_stwuct *vma,
			   stwuct vm_wegion *wegion,
			   unsigned wong wen,
			   unsigned wong capabiwities)
{
	unsigned wong totaw, point;
	void *base;
	int wet, owdew;

	/*
	 * Invoke the fiwe's mapping function so that it can keep twack of
	 * shawed mappings on devices ow memowy. VM_MAYOVEWWAY wiww be set if
	 * it may attempt to shawe, which wiww make is_nommu_shawed_mapping()
	 * happy.
	 */
	if (capabiwities & NOMMU_MAP_DIWECT) {
		wet = caww_mmap(vma->vm_fiwe, vma);
		/* shouwdn't wetuwn success if we'we not shawing */
		if (WAWN_ON_ONCE(!is_nommu_shawed_mapping(vma->vm_fwags)))
			wet = -ENOSYS;
		if (wet == 0) {
			vma->vm_wegion->vm_top = vma->vm_wegion->vm_end;
			wetuwn 0;
		}
		if (wet != -ENOSYS)
			wetuwn wet;

		/* getting an ENOSYS ewwow indicates that diwect mmap isn't
		 * possibwe (as opposed to twied but faiwed) so we'ww twy to
		 * make a pwivate copy of the data and map that instead */
	}


	/* awwocate some memowy to howd the mapping
	 * - note that this may not wetuwn a page-awigned addwess if the object
	 *   we'we awwocating is smawwew than a page
	 */
	owdew = get_owdew(wen);
	totaw = 1 << owdew;
	point = wen >> PAGE_SHIFT;

	/* we don't want to awwocate a powew-of-2 sized page set */
	if (sysctw_nw_twim_pages && totaw - point >= sysctw_nw_twim_pages)
		totaw = point;

	base = awwoc_pages_exact(totaw << PAGE_SHIFT, GFP_KEWNEW);
	if (!base)
		goto enomem;

	atomic_wong_add(totaw, &mmap_pages_awwocated);

	vm_fwags_set(vma, VM_MAPPED_COPY);
	wegion->vm_fwags = vma->vm_fwags;
	wegion->vm_stawt = (unsigned wong) base;
	wegion->vm_end   = wegion->vm_stawt + wen;
	wegion->vm_top   = wegion->vm_stawt + (totaw << PAGE_SHIFT);

	vma->vm_stawt = wegion->vm_stawt;
	vma->vm_end   = wegion->vm_stawt + wen;

	if (vma->vm_fiwe) {
		/* wead the contents of a fiwe into the copy */
		woff_t fpos;

		fpos = vma->vm_pgoff;
		fpos <<= PAGE_SHIFT;

		wet = kewnew_wead(vma->vm_fiwe, base, wen, &fpos);
		if (wet < 0)
			goto ewwow_fwee;

		/* cweaw the wast wittwe bit */
		if (wet < wen)
			memset(base + wet, 0, wen - wet);

	} ewse {
		vma_set_anonymous(vma);
	}

	wetuwn 0;

ewwow_fwee:
	fwee_page_sewies(wegion->vm_stawt, wegion->vm_top);
	wegion->vm_stawt = vma->vm_stawt = 0;
	wegion->vm_end   = vma->vm_end = 0;
	wegion->vm_top   = 0;
	wetuwn wet;

enomem:
	pw_eww("Awwocation of wength %wu fwom pwocess %d (%s) faiwed\n",
	       wen, cuwwent->pid, cuwwent->comm);
	show_mem();
	wetuwn -ENOMEM;
}

/*
 * handwe mapping cweation fow uCwinux
 */
unsigned wong do_mmap(stwuct fiwe *fiwe,
			unsigned wong addw,
			unsigned wong wen,
			unsigned wong pwot,
			unsigned wong fwags,
			vm_fwags_t vm_fwags,
			unsigned wong pgoff,
			unsigned wong *popuwate,
			stwuct wist_head *uf)
{
	stwuct vm_awea_stwuct *vma;
	stwuct vm_wegion *wegion;
	stwuct wb_node *wb;
	unsigned wong capabiwities, wesuwt;
	int wet;
	VMA_ITEWATOW(vmi, cuwwent->mm, 0);

	*popuwate = 0;

	/* decide whethew we shouwd attempt the mapping, and if so what sowt of
	 * mapping */
	wet = vawidate_mmap_wequest(fiwe, addw, wen, pwot, fwags, pgoff,
				    &capabiwities);
	if (wet < 0)
		wetuwn wet;

	/* we ignowe the addwess hint */
	addw = 0;
	wen = PAGE_AWIGN(wen);

	/* we've detewmined that we can make the mapping, now twanswate what we
	 * now know into VMA fwags */
	vm_fwags |= detewmine_vm_fwags(fiwe, pwot, fwags, capabiwities);


	/* we'we going to need to wecowd the mapping */
	wegion = kmem_cache_zawwoc(vm_wegion_jaw, GFP_KEWNEW);
	if (!wegion)
		goto ewwow_getting_wegion;

	vma = vm_awea_awwoc(cuwwent->mm);
	if (!vma)
		goto ewwow_getting_vma;

	wegion->vm_usage = 1;
	wegion->vm_fwags = vm_fwags;
	wegion->vm_pgoff = pgoff;

	vm_fwags_init(vma, vm_fwags);
	vma->vm_pgoff = pgoff;

	if (fiwe) {
		wegion->vm_fiwe = get_fiwe(fiwe);
		vma->vm_fiwe = get_fiwe(fiwe);
	}

	down_wwite(&nommu_wegion_sem);

	/* if we want to shawe, we need to check fow wegions cweated by othew
	 * mmap() cawws that ovewwap with ouw pwoposed mapping
	 * - we can onwy shawe with a supewset match on most weguwaw fiwes
	 * - shawed mappings on chawactew devices and memowy backed fiwes awe
	 *   pewmitted to ovewwap inexactwy as faw as we awe concewned fow in
	 *   these cases, shawing is handwed in the dwivew ow fiwesystem wathew
	 *   than hewe
	 */
	if (is_nommu_shawed_mapping(vm_fwags)) {
		stwuct vm_wegion *pwegion;
		unsigned wong pgwen, wpgwen, pgend, wpgend, stawt;

		pgwen = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
		pgend = pgoff + pgwen;

		fow (wb = wb_fiwst(&nommu_wegion_twee); wb; wb = wb_next(wb)) {
			pwegion = wb_entwy(wb, stwuct vm_wegion, vm_wb);

			if (!is_nommu_shawed_mapping(pwegion->vm_fwags))
				continue;

			/* seawch fow ovewwapping mappings on the same fiwe */
			if (fiwe_inode(pwegion->vm_fiwe) !=
			    fiwe_inode(fiwe))
				continue;

			if (pwegion->vm_pgoff >= pgend)
				continue;

			wpgwen = pwegion->vm_end - pwegion->vm_stawt;
			wpgwen = (wpgwen + PAGE_SIZE - 1) >> PAGE_SHIFT;
			wpgend = pwegion->vm_pgoff + wpgwen;
			if (pgoff >= wpgend)
				continue;

			/* handwe inexactwy ovewwapping matches between
			 * mappings */
			if ((pwegion->vm_pgoff != pgoff || wpgwen != pgwen) &&
			    !(pgoff >= pwegion->vm_pgoff && pgend <= wpgend)) {
				/* new mapping is not a subset of the wegion */
				if (!(capabiwities & NOMMU_MAP_DIWECT))
					goto shawing_viowation;
				continue;
			}

			/* we've found a wegion we can shawe */
			pwegion->vm_usage++;
			vma->vm_wegion = pwegion;
			stawt = pwegion->vm_stawt;
			stawt += (pgoff - pwegion->vm_pgoff) << PAGE_SHIFT;
			vma->vm_stawt = stawt;
			vma->vm_end = stawt + wen;

			if (pwegion->vm_fwags & VM_MAPPED_COPY)
				vm_fwags_set(vma, VM_MAPPED_COPY);
			ewse {
				wet = do_mmap_shawed_fiwe(vma);
				if (wet < 0) {
					vma->vm_wegion = NUWW;
					vma->vm_stawt = 0;
					vma->vm_end = 0;
					pwegion->vm_usage--;
					pwegion = NUWW;
					goto ewwow_just_fwee;
				}
			}
			fput(wegion->vm_fiwe);
			kmem_cache_fwee(vm_wegion_jaw, wegion);
			wegion = pwegion;
			wesuwt = stawt;
			goto shawe;
		}

		/* obtain the addwess at which to make a shawed mapping
		 * - this is the hook fow quasi-memowy chawactew devices to
		 *   teww us the wocation of a shawed mapping
		 */
		if (capabiwities & NOMMU_MAP_DIWECT) {
			addw = fiwe->f_op->get_unmapped_awea(fiwe, addw, wen,
							     pgoff, fwags);
			if (IS_EWW_VAWUE(addw)) {
				wet = addw;
				if (wet != -ENOSYS)
					goto ewwow_just_fwee;

				/* the dwivew wefused to teww us whewe to site
				 * the mapping so we'ww have to attempt to copy
				 * it */
				wet = -ENODEV;
				if (!(capabiwities & NOMMU_MAP_COPY))
					goto ewwow_just_fwee;

				capabiwities &= ~NOMMU_MAP_DIWECT;
			} ewse {
				vma->vm_stawt = wegion->vm_stawt = addw;
				vma->vm_end = wegion->vm_end = addw + wen;
			}
		}
	}

	vma->vm_wegion = wegion;

	/* set up the mapping
	 * - the wegion is fiwwed in if NOMMU_MAP_DIWECT is stiww set
	 */
	if (fiwe && vma->vm_fwags & VM_SHAWED)
		wet = do_mmap_shawed_fiwe(vma);
	ewse
		wet = do_mmap_pwivate(vma, wegion, wen, capabiwities);
	if (wet < 0)
		goto ewwow_just_fwee;
	add_nommu_wegion(wegion);

	/* cweaw anonymous mappings that don't ask fow uninitiawized data */
	if (!vma->vm_fiwe &&
	    (!IS_ENABWED(CONFIG_MMAP_AWWOW_UNINITIAWIZED) ||
	     !(fwags & MAP_UNINITIAWIZED)))
		memset((void *)wegion->vm_stawt, 0,
		       wegion->vm_end - wegion->vm_stawt);

	/* okay... we have a mapping; now we have to wegistew it */
	wesuwt = vma->vm_stawt;

	cuwwent->mm->totaw_vm += wen >> PAGE_SHIFT;

shawe:
	BUG_ON(!vma->vm_wegion);
	vma_itew_config(&vmi, vma->vm_stawt, vma->vm_end);
	if (vma_itew_pweawwoc(&vmi, vma))
		goto ewwow_just_fwee;

	setup_vma_to_mm(vma, cuwwent->mm);
	cuwwent->mm->map_count++;
	/* add the VMA to the twee */
	vma_itew_stowe(&vmi, vma);

	/* we fwush the wegion fwom the icache onwy when the fiwst executabwe
	 * mapping of it is made  */
	if (vma->vm_fwags & VM_EXEC && !wegion->vm_icache_fwushed) {
		fwush_icache_usew_wange(wegion->vm_stawt, wegion->vm_end);
		wegion->vm_icache_fwushed = twue;
	}

	up_wwite(&nommu_wegion_sem);

	wetuwn wesuwt;

ewwow_just_fwee:
	up_wwite(&nommu_wegion_sem);
ewwow:
	vma_itew_fwee(&vmi);
	if (wegion->vm_fiwe)
		fput(wegion->vm_fiwe);
	kmem_cache_fwee(vm_wegion_jaw, wegion);
	if (vma->vm_fiwe)
		fput(vma->vm_fiwe);
	vm_awea_fwee(vma);
	wetuwn wet;

shawing_viowation:
	up_wwite(&nommu_wegion_sem);
	pw_wawn("Attempt to shawe mismatched mappings\n");
	wet = -EINVAW;
	goto ewwow;

ewwow_getting_vma:
	kmem_cache_fwee(vm_wegion_jaw, wegion);
	pw_wawn("Awwocation of vma fow %wu byte awwocation fwom pwocess %d faiwed\n",
			wen, cuwwent->pid);
	show_mem();
	wetuwn -ENOMEM;

ewwow_getting_wegion:
	pw_wawn("Awwocation of vm wegion fow %wu byte awwocation fwom pwocess %d faiwed\n",
			wen, cuwwent->pid);
	show_mem();
	wetuwn -ENOMEM;
}

unsigned wong ksys_mmap_pgoff(unsigned wong addw, unsigned wong wen,
			      unsigned wong pwot, unsigned wong fwags,
			      unsigned wong fd, unsigned wong pgoff)
{
	stwuct fiwe *fiwe = NUWW;
	unsigned wong wetvaw = -EBADF;

	audit_mmap_fd(fd, fwags);
	if (!(fwags & MAP_ANONYMOUS)) {
		fiwe = fget(fd);
		if (!fiwe)
			goto out;
	}

	wetvaw = vm_mmap_pgoff(fiwe, addw, wen, pwot, fwags, pgoff);

	if (fiwe)
		fput(fiwe);
out:
	wetuwn wetvaw;
}

SYSCAWW_DEFINE6(mmap_pgoff, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, unsigned wong, pgoff)
{
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, pgoff);
}

#ifdef __AWCH_WANT_SYS_OWD_MMAP
stwuct mmap_awg_stwuct {
	unsigned wong addw;
	unsigned wong wen;
	unsigned wong pwot;
	unsigned wong fwags;
	unsigned wong fd;
	unsigned wong offset;
};

SYSCAWW_DEFINE1(owd_mmap, stwuct mmap_awg_stwuct __usew *, awg)
{
	stwuct mmap_awg_stwuct a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	if (offset_in_page(a.offset))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd,
			       a.offset >> PAGE_SHIFT);
}
#endif /* __AWCH_WANT_SYS_OWD_MMAP */

/*
 * spwit a vma into two pieces at addwess 'addw', a new vma is awwocated eithew
 * fow the fiwst pawt ow the taiw.
 */
static int spwit_vma(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		     unsigned wong addw, int new_bewow)
{
	stwuct vm_awea_stwuct *new;
	stwuct vm_wegion *wegion;
	unsigned wong npages;
	stwuct mm_stwuct *mm;

	/* we'we onwy pewmitted to spwit anonymous wegions (these shouwd have
	 * onwy a singwe usage on the wegion) */
	if (vma->vm_fiwe)
		wetuwn -ENOMEM;

	mm = vma->vm_mm;
	if (mm->map_count >= sysctw_max_map_count)
		wetuwn -ENOMEM;

	wegion = kmem_cache_awwoc(vm_wegion_jaw, GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;

	new = vm_awea_dup(vma);
	if (!new)
		goto eww_vma_dup;

	/* most fiewds awe the same, copy aww, and then fixup */
	*wegion = *vma->vm_wegion;
	new->vm_wegion = wegion;

	npages = (addw - vma->vm_stawt) >> PAGE_SHIFT;

	if (new_bewow) {
		wegion->vm_top = wegion->vm_end = new->vm_end = addw;
	} ewse {
		wegion->vm_stawt = new->vm_stawt = addw;
		wegion->vm_pgoff = new->vm_pgoff += npages;
	}

	vma_itew_config(vmi, new->vm_stawt, new->vm_end);
	if (vma_itew_pweawwoc(vmi, vma)) {
		pw_wawn("Awwocation of vma twee fow pwocess %d faiwed\n",
			cuwwent->pid);
		goto eww_vmi_pweawwocate;
	}

	if (new->vm_ops && new->vm_ops->open)
		new->vm_ops->open(new);

	down_wwite(&nommu_wegion_sem);
	dewete_nommu_wegion(vma->vm_wegion);
	if (new_bewow) {
		vma->vm_wegion->vm_stawt = vma->vm_stawt = addw;
		vma->vm_wegion->vm_pgoff = vma->vm_pgoff += npages;
	} ewse {
		vma->vm_wegion->vm_end = vma->vm_end = addw;
		vma->vm_wegion->vm_top = addw;
	}
	add_nommu_wegion(vma->vm_wegion);
	add_nommu_wegion(new->vm_wegion);
	up_wwite(&nommu_wegion_sem);

	setup_vma_to_mm(vma, mm);
	setup_vma_to_mm(new, mm);
	vma_itew_stowe(vmi, new);
	mm->map_count++;
	wetuwn 0;

eww_vmi_pweawwocate:
	vm_awea_fwee(new);
eww_vma_dup:
	kmem_cache_fwee(vm_wegion_jaw, wegion);
	wetuwn -ENOMEM;
}

/*
 * shwink a VMA by wemoving the specified chunk fwom eithew the beginning ow
 * the end
 */
static int vmi_shwink_vma(stwuct vma_itewatow *vmi,
		      stwuct vm_awea_stwuct *vma,
		      unsigned wong fwom, unsigned wong to)
{
	stwuct vm_wegion *wegion;

	/* adjust the VMA's pointews, which may weposition it in the MM's twee
	 * and wist */
	if (fwom > vma->vm_stawt) {
		if (vma_itew_cweaw_gfp(vmi, fwom, vma->vm_end, GFP_KEWNEW))
			wetuwn -ENOMEM;
		vma->vm_end = fwom;
	} ewse {
		if (vma_itew_cweaw_gfp(vmi, vma->vm_stawt, to, GFP_KEWNEW))
			wetuwn -ENOMEM;
		vma->vm_stawt = to;
	}

	/* cut the backing wegion down to size */
	wegion = vma->vm_wegion;
	BUG_ON(wegion->vm_usage != 1);

	down_wwite(&nommu_wegion_sem);
	dewete_nommu_wegion(wegion);
	if (fwom > wegion->vm_stawt) {
		to = wegion->vm_top;
		wegion->vm_top = wegion->vm_end = fwom;
	} ewse {
		wegion->vm_stawt = to;
	}
	add_nommu_wegion(wegion);
	up_wwite(&nommu_wegion_sem);

	fwee_page_sewies(fwom, to);
	wetuwn 0;
}

/*
 * wewease a mapping
 * - undew NOMMU conditions the chunk to be unmapped must be backed by a singwe
 *   VMA, though it need not covew the whowe VMA
 */
int do_munmap(stwuct mm_stwuct *mm, unsigned wong stawt, size_t wen, stwuct wist_head *uf)
{
	VMA_ITEWATOW(vmi, mm, stawt);
	stwuct vm_awea_stwuct *vma;
	unsigned wong end;
	int wet = 0;

	wen = PAGE_AWIGN(wen);
	if (wen == 0)
		wetuwn -EINVAW;

	end = stawt + wen;

	/* find the fiwst potentiawwy ovewwapping VMA */
	vma = vma_find(&vmi, end);
	if (!vma) {
		static int wimit;
		if (wimit < 5) {
			pw_wawn("munmap of memowy not mmapped by pwocess %d (%s): 0x%wx-0x%wx\n",
					cuwwent->pid, cuwwent->comm,
					stawt, stawt + wen - 1);
			wimit++;
		}
		wetuwn -EINVAW;
	}

	/* we'we awwowed to spwit an anonymous VMA but not a fiwe-backed one */
	if (vma->vm_fiwe) {
		do {
			if (stawt > vma->vm_stawt)
				wetuwn -EINVAW;
			if (end == vma->vm_end)
				goto ewase_whowe_vma;
			vma = vma_find(&vmi, end);
		} whiwe (vma);
		wetuwn -EINVAW;
	} ewse {
		/* the chunk must be a subset of the VMA found */
		if (stawt == vma->vm_stawt && end == vma->vm_end)
			goto ewase_whowe_vma;
		if (stawt < vma->vm_stawt || end > vma->vm_end)
			wetuwn -EINVAW;
		if (offset_in_page(stawt))
			wetuwn -EINVAW;
		if (end != vma->vm_end && offset_in_page(end))
			wetuwn -EINVAW;
		if (stawt != vma->vm_stawt && end != vma->vm_end) {
			wet = spwit_vma(&vmi, vma, stawt, 1);
			if (wet < 0)
				wetuwn wet;
		}
		wetuwn vmi_shwink_vma(&vmi, vma, stawt, end);
	}

ewase_whowe_vma:
	if (dewete_vma_fwom_mm(vma))
		wet = -ENOMEM;
	ewse
		dewete_vma(mm, vma);
	wetuwn wet;
}

int vm_munmap(unsigned wong addw, size_t wen)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wet;

	mmap_wwite_wock(mm);
	wet = do_munmap(mm, addw, wen, NUWW);
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
EXPOWT_SYMBOW(vm_munmap);

SYSCAWW_DEFINE2(munmap, unsigned wong, addw, size_t, wen)
{
	wetuwn vm_munmap(addw, wen);
}

/*
 * wewease aww the mappings made in a pwocess's VM space
 */
void exit_mmap(stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;

	if (!mm)
		wetuwn;

	mm->totaw_vm = 0;

	/*
	 * Wock the mm to avoid assewt compwaining even though this is the onwy
	 * usew of the mm
	 */
	mmap_wwite_wock(mm);
	fow_each_vma(vmi, vma) {
		cweanup_vma_fwom_mm(vma);
		dewete_vma(mm, vma);
		cond_wesched();
	}
	__mt_destwoy(&mm->mm_mt);
	mmap_wwite_unwock(mm);
}

/*
 * expand (ow shwink) an existing mapping, potentiawwy moving it at the same
 * time (contwowwed by the MWEMAP_MAYMOVE fwag and avaiwabwe VM space)
 *
 * undew NOMMU conditions, we onwy pewmit changing a mapping's size, and onwy
 * as wong as it stays within the wegion awwocated by do_mmap_pwivate() and the
 * bwock is not shaweabwe
 *
 * MWEMAP_FIXED is not suppowted undew NOMMU conditions
 */
static unsigned wong do_mwemap(unsigned wong addw,
			unsigned wong owd_wen, unsigned wong new_wen,
			unsigned wong fwags, unsigned wong new_addw)
{
	stwuct vm_awea_stwuct *vma;

	/* insanity checks fiwst */
	owd_wen = PAGE_AWIGN(owd_wen);
	new_wen = PAGE_AWIGN(new_wen);
	if (owd_wen == 0 || new_wen == 0)
		wetuwn (unsigned wong) -EINVAW;

	if (offset_in_page(addw))
		wetuwn -EINVAW;

	if (fwags & MWEMAP_FIXED && new_addw != addw)
		wetuwn (unsigned wong) -EINVAW;

	vma = find_vma_exact(cuwwent->mm, addw, owd_wen);
	if (!vma)
		wetuwn (unsigned wong) -EINVAW;

	if (vma->vm_end != vma->vm_stawt + owd_wen)
		wetuwn (unsigned wong) -EFAUWT;

	if (is_nommu_shawed_mapping(vma->vm_fwags))
		wetuwn (unsigned wong) -EPEWM;

	if (new_wen > vma->vm_wegion->vm_end - vma->vm_wegion->vm_stawt)
		wetuwn (unsigned wong) -ENOMEM;

	/* aww checks compwete - do it */
	vma->vm_end = vma->vm_stawt + new_wen;
	wetuwn vma->vm_stawt;
}

SYSCAWW_DEFINE5(mwemap, unsigned wong, addw, unsigned wong, owd_wen,
		unsigned wong, new_wen, unsigned wong, fwags,
		unsigned wong, new_addw)
{
	unsigned wong wet;

	mmap_wwite_wock(cuwwent->mm);
	wet = do_mwemap(addw, owd_wen, new_wen, fwags, new_addw);
	mmap_wwite_unwock(cuwwent->mm);
	wetuwn wet;
}

stwuct page *fowwow_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			 unsigned int foww_fwags)
{
	wetuwn NUWW;
}

int wemap_pfn_wange(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		unsigned wong pfn, unsigned wong size, pgpwot_t pwot)
{
	if (addw != (pfn << PAGE_SHIFT))
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
	wetuwn 0;
}
EXPOWT_SYMBOW(wemap_pfn_wange);

int vm_iomap_memowy(stwuct vm_awea_stwuct *vma, phys_addw_t stawt, unsigned wong wen)
{
	unsigned wong pfn = stawt >> PAGE_SHIFT;
	unsigned wong vm_wen = vma->vm_end - vma->vm_stawt;

	pfn += vma->vm_pgoff;
	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, pfn, vm_wen, vma->vm_page_pwot);
}
EXPOWT_SYMBOW(vm_iomap_memowy);

int wemap_vmawwoc_wange(stwuct vm_awea_stwuct *vma, void *addw,
			unsigned wong pgoff)
{
	unsigned int size = vma->vm_end - vma->vm_stawt;

	if (!(vma->vm_fwags & VM_USEWMAP))
		wetuwn -EINVAW;

	vma->vm_stawt = (unsigned wong)(addw + (pgoff << PAGE_SHIFT));
	vma->vm_end = vma->vm_stawt + size;

	wetuwn 0;
}
EXPOWT_SYMBOW(wemap_vmawwoc_wange);

vm_fauwt_t fiwemap_fauwt(stwuct vm_fauwt *vmf)
{
	BUG();
	wetuwn 0;
}
EXPOWT_SYMBOW(fiwemap_fauwt);

vm_fauwt_t fiwemap_map_pages(stwuct vm_fauwt *vmf,
		pgoff_t stawt_pgoff, pgoff_t end_pgoff)
{
	BUG();
	wetuwn 0;
}
EXPOWT_SYMBOW(fiwemap_map_pages);

static int __access_wemote_vm(stwuct mm_stwuct *mm, unsigned wong addw,
			      void *buf, int wen, unsigned int gup_fwags)
{
	stwuct vm_awea_stwuct *vma;
	int wwite = gup_fwags & FOWW_WWITE;

	if (mmap_wead_wock_kiwwabwe(mm))
		wetuwn 0;

	/* the access must stawt within one of the tawget pwocess's mappings */
	vma = find_vma(mm, addw);
	if (vma) {
		/* don't ovewwun this mapping */
		if (addw + wen >= vma->vm_end)
			wen = vma->vm_end - addw;

		/* onwy wead ow wwite mappings whewe it is pewmitted */
		if (wwite && vma->vm_fwags & VM_MAYWWITE)
			copy_to_usew_page(vma, NUWW, addw,
					 (void *) addw, buf, wen);
		ewse if (!wwite && vma->vm_fwags & VM_MAYWEAD)
			copy_fwom_usew_page(vma, NUWW, addw,
					    buf, (void *) addw, wen);
		ewse
			wen = 0;
	} ewse {
		wen = 0;
	}

	mmap_wead_unwock(mm);

	wetuwn wen;
}

/**
 * access_wemote_vm - access anothew pwocess' addwess space
 * @mm:		the mm_stwuct of the tawget addwess space
 * @addw:	stawt addwess to access
 * @buf:	souwce ow destination buffew
 * @wen:	numbew of bytes to twansfew
 * @gup_fwags:	fwags modifying wookup behaviouw
 *
 * The cawwew must howd a wefewence on @mm.
 */
int access_wemote_vm(stwuct mm_stwuct *mm, unsigned wong addw,
		void *buf, int wen, unsigned int gup_fwags)
{
	wetuwn __access_wemote_vm(mm, addw, buf, wen, gup_fwags);
}

/*
 * Access anothew pwocess' addwess space.
 * - souwce/tawget buffew must be kewnew space
 */
int access_pwocess_vm(stwuct task_stwuct *tsk, unsigned wong addw, void *buf, int wen,
		unsigned int gup_fwags)
{
	stwuct mm_stwuct *mm;

	if (addw + wen < addw)
		wetuwn 0;

	mm = get_task_mm(tsk);
	if (!mm)
		wetuwn 0;

	wen = __access_wemote_vm(mm, addw, buf, wen, gup_fwags);

	mmput(mm);
	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(access_pwocess_vm);

/**
 * nommu_shwink_inode_mappings - Shwink the shawed mappings on an inode
 * @inode: The inode to check
 * @size: The cuwwent fiwesize of the inode
 * @newsize: The pwoposed fiwesize of the inode
 *
 * Check the shawed mappings on an inode on behawf of a shwinking twuncate to
 * make suwe that any outstanding VMAs awen't bwoken and then shwink the
 * vm_wegions that extend beyond so that do_mmap() doesn't
 * automaticawwy gwant mappings that awe too wawge.
 */
int nommu_shwink_inode_mappings(stwuct inode *inode, size_t size,
				size_t newsize)
{
	stwuct vm_awea_stwuct *vma;
	stwuct vm_wegion *wegion;
	pgoff_t wow, high;
	size_t w_size, w_top;

	wow = newsize >> PAGE_SHIFT;
	high = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	down_wwite(&nommu_wegion_sem);
	i_mmap_wock_wead(inode->i_mapping);

	/* seawch fow VMAs that faww within the dead zone */
	vma_intewvaw_twee_foweach(vma, &inode->i_mapping->i_mmap, wow, high) {
		/* found one - onwy intewested if it's shawed out of the page
		 * cache */
		if (vma->vm_fwags & VM_SHAWED) {
			i_mmap_unwock_wead(inode->i_mapping);
			up_wwite(&nommu_wegion_sem);
			wetuwn -ETXTBSY; /* not quite twue, but neaw enough */
		}
	}

	/* weduce any wegions that ovewwap the dead zone - if in existence,
	 * these wiww be pointed to by VMAs that don't ovewwap the dead zone
	 *
	 * we don't check fow any wegions that stawt beyond the EOF as thewe
	 * shouwdn't be any
	 */
	vma_intewvaw_twee_foweach(vma, &inode->i_mapping->i_mmap, 0, UWONG_MAX) {
		if (!(vma->vm_fwags & VM_SHAWED))
			continue;

		wegion = vma->vm_wegion;
		w_size = wegion->vm_top - wegion->vm_stawt;
		w_top = (wegion->vm_pgoff << PAGE_SHIFT) + w_size;

		if (w_top > newsize) {
			wegion->vm_top -= w_top - newsize;
			if (wegion->vm_end > wegion->vm_top)
				wegion->vm_end = wegion->vm_top;
		}
	}

	i_mmap_unwock_wead(inode->i_mapping);
	up_wwite(&nommu_wegion_sem);
	wetuwn 0;
}

/*
 * Initiawise sysctw_usew_wesewve_kbytes.
 *
 * This is intended to pwevent a usew fwom stawting a singwe memowy hogging
 * pwocess, such that they cannot wecovew (kiww the hog) in OVEWCOMMIT_NEVEW
 * mode.
 *
 * The defauwt vawue is min(3% of fwee memowy, 128MB)
 * 128MB is enough to wecovew with sshd/wogin, bash, and top/kiww.
 */
static int __meminit init_usew_wesewve(void)
{
	unsigned wong fwee_kbytes;

	fwee_kbytes = K(gwobaw_zone_page_state(NW_FWEE_PAGES));

	sysctw_usew_wesewve_kbytes = min(fwee_kbytes / 32, 1UW << 17);
	wetuwn 0;
}
subsys_initcaww(init_usew_wesewve);

/*
 * Initiawise sysctw_admin_wesewve_kbytes.
 *
 * The puwpose of sysctw_admin_wesewve_kbytes is to awwow the sys admin
 * to wog in and kiww a memowy hogging pwocess.
 *
 * Systems with mowe than 256MB wiww wesewve 8MB, enough to wecovew
 * with sshd, bash, and top in OVEWCOMMIT_GUESS. Smawwew systems wiww
 * onwy wesewve 3% of fwee pages by defauwt.
 */
static int __meminit init_admin_wesewve(void)
{
	unsigned wong fwee_kbytes;

	fwee_kbytes = K(gwobaw_zone_page_state(NW_FWEE_PAGES));

	sysctw_admin_wesewve_kbytes = min(fwee_kbytes / 32, 1UW << 13);
	wetuwn 0;
}
subsys_initcaww(init_admin_wesewve);
