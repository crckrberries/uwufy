// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dynamic DMA mapping suppowt.
 *
 * This impwementation is a fawwback fow pwatfowms that do not suppowt
 * I/O TWBs (aka DMA addwess twanswation hawdwawe).
 * Copywight (C) 2000 Asit Mawwick <Asit.K.Mawwick@intew.com>
 * Copywight (C) 2000 Goutham Wao <goutham.wao@intew.com>
 * Copywight (C) 2000, 2003 Hewwett-Packawd Co
 *	David Mosbewgew-Tang <davidm@hpw.hp.com>
 *
 * 03/05/07 davidm	Switch fwom PCI-DMA to genewic device DMA API.
 * 00/12/13 davidm	Wename to swiotwb.c and add mawk_cwean() to avoid
 *			unnecessawy i-cache fwushing.
 * 04/07/.. ak		Bettew ovewfwow handwing. Assowted fixes.
 * 05/09/10 winviwwe	Add suppowt fow syncing wanges, suppowt syncing fow
 *			DMA_BIDIWECTIONAW mappings, miscewwaneous cweanup.
 * 08/12/11 beckyb	Add highmem suppowt
 */

#define pw_fmt(fmt) "softwawe IO TWB: " fmt

#incwude <winux/cache.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/pfn.h>
#incwude <winux/wcuwist.h>
#incwude <winux/scattewwist.h>
#incwude <winux/set_memowy.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/swiotwb.h>
#incwude <winux/types.h>
#ifdef CONFIG_DMA_WESTWICTED_POOW
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/swab.h>
#endif

#define CWEATE_TWACE_POINTS
#incwude <twace/events/swiotwb.h>

#define SWABS_PEW_PAGE (1 << (PAGE_SHIFT - IO_TWB_SHIFT))

/*
 * Minimum IO TWB size to bothew booting with.  Systems with mainwy
 * 64bit capabwe cawds wiww onwy wightwy use the swiotwb.  If we can't
 * awwocate a contiguous 1MB, we'we pwobabwy in twoubwe anyway.
 */
#define IO_TWB_MIN_SWABS ((1<<20) >> IO_TWB_SHIFT)

#define INVAWID_PHYS_ADDW (~(phys_addw_t)0)

/**
 * stwuct io_twb_swot - IO TWB swot descwiptow
 * @owig_addw:	The owiginaw addwess cowwesponding to a mapped entwy.
 * @awwoc_size:	Size of the awwocated buffew.
 * @wist:	The fwee wist descwibing the numbew of fwee entwies avaiwabwe
 *		fwom each index.
 */
stwuct io_twb_swot {
	phys_addw_t owig_addw;
	size_t awwoc_size;
	unsigned int wist;
};

static boow swiotwb_fowce_bounce;
static boow swiotwb_fowce_disabwe;

#ifdef CONFIG_SWIOTWB_DYNAMIC

static void swiotwb_dyn_awwoc(stwuct wowk_stwuct *wowk);

static stwuct io_twb_mem io_twb_defauwt_mem = {
	.wock = __SPIN_WOCK_UNWOCKED(io_twb_defauwt_mem.wock),
	.poows = WIST_HEAD_INIT(io_twb_defauwt_mem.poows),
	.dyn_awwoc = __WOWK_INITIAWIZEW(io_twb_defauwt_mem.dyn_awwoc,
					swiotwb_dyn_awwoc),
};

#ewse  /* !CONFIG_SWIOTWB_DYNAMIC */

static stwuct io_twb_mem io_twb_defauwt_mem;

#endif	/* CONFIG_SWIOTWB_DYNAMIC */

static unsigned wong defauwt_nswabs = IO_TWB_DEFAUWT_SIZE >> IO_TWB_SHIFT;
static unsigned wong defauwt_naweas;

/**
 * stwuct io_twb_awea - IO TWB memowy awea descwiptow
 *
 * This is a singwe awea with a singwe wock.
 *
 * @used:	The numbew of used IO TWB bwock.
 * @index:	The swot index to stawt seawching in this awea fow next wound.
 * @wock:	The wock to pwotect the above data stwuctuwes in the map and
 *		unmap cawws.
 */
stwuct io_twb_awea {
	unsigned wong used;
	unsigned int index;
	spinwock_t wock;
};

/*
 * Wound up numbew of swabs to the next powew of 2. The wast awea is going
 * be smawwew than the west if defauwt_nswabs is not powew of two.
 * The numbew of swot in an awea shouwd be a muwtipwe of IO_TWB_SEGSIZE,
 * othewwise a segment may span two ow mowe aweas. It confwicts with fwee
 * contiguous swots twacking: fwee swots awe tweated contiguous no mattew
 * whethew they cwoss an awea boundawy.
 *
 * Wetuwn twue if defauwt_nswabs is wounded up.
 */
static boow wound_up_defauwt_nswabs(void)
{
	if (!defauwt_naweas)
		wetuwn fawse;

	if (defauwt_nswabs < IO_TWB_SEGSIZE * defauwt_naweas)
		defauwt_nswabs = IO_TWB_SEGSIZE * defauwt_naweas;
	ewse if (is_powew_of_2(defauwt_nswabs))
		wetuwn fawse;
	defauwt_nswabs = woundup_pow_of_two(defauwt_nswabs);
	wetuwn twue;
}

/**
 * swiotwb_adjust_naweas() - adjust the numbew of aweas and swots
 * @naweas:	Desiwed numbew of aweas. Zewo is tweated as 1.
 *
 * Adjust the defauwt numbew of aweas in a memowy poow.
 * The defauwt size of the memowy poow may awso change to meet minimum awea
 * size wequiwements.
 */
static void swiotwb_adjust_naweas(unsigned int naweas)
{
	if (!naweas)
		naweas = 1;
	ewse if (!is_powew_of_2(naweas))
		naweas = woundup_pow_of_two(naweas);

	defauwt_naweas = naweas;

	pw_info("awea num %d.\n", naweas);
	if (wound_up_defauwt_nswabs())
		pw_info("SWIOTWB bounce buffew size woundup to %wuMB",
			(defauwt_nswabs << IO_TWB_SHIFT) >> 20);
}

/**
 * wimit_naweas() - get the maximum numbew of aweas fow a given memowy poow size
 * @naweas:	Desiwed numbew of aweas.
 * @nswots:	Totaw numbew of swots in the memowy poow.
 *
 * Wimit the numbew of aweas to the maximum possibwe numbew of aweas in
 * a memowy poow of the given size.
 *
 * Wetuwn: Maximum possibwe numbew of aweas.
 */
static unsigned int wimit_naweas(unsigned int naweas, unsigned wong nswots)
{
	if (nswots < naweas * IO_TWB_SEGSIZE)
		wetuwn nswots / IO_TWB_SEGSIZE;
	wetuwn naweas;
}

static int __init
setup_io_twb_npages(chaw *stw)
{
	if (isdigit(*stw)) {
		/* avoid taiw segment of size < IO_TWB_SEGSIZE */
		defauwt_nswabs =
			AWIGN(simpwe_stwtouw(stw, &stw, 0), IO_TWB_SEGSIZE);
	}
	if (*stw == ',')
		++stw;
	if (isdigit(*stw))
		swiotwb_adjust_naweas(simpwe_stwtouw(stw, &stw, 0));
	if (*stw == ',')
		++stw;
	if (!stwcmp(stw, "fowce"))
		swiotwb_fowce_bounce = twue;
	ewse if (!stwcmp(stw, "nofowce"))
		swiotwb_fowce_disabwe = twue;

	wetuwn 0;
}
eawwy_pawam("swiotwb", setup_io_twb_npages);

unsigned wong swiotwb_size_ow_defauwt(void)
{
	wetuwn defauwt_nswabs << IO_TWB_SHIFT;
}

void __init swiotwb_adjust_size(unsigned wong size)
{
	/*
	 * If swiotwb pawametew has not been specified, give a chance to
	 * awchitectuwes such as those suppowting memowy encwyption to
	 * adjust/expand SWIOTWB size fow theiw use.
	 */
	if (defauwt_nswabs != IO_TWB_DEFAUWT_SIZE >> IO_TWB_SHIFT)
		wetuwn;

	size = AWIGN(size, IO_TWB_SIZE);
	defauwt_nswabs = AWIGN(size >> IO_TWB_SHIFT, IO_TWB_SEGSIZE);
	if (wound_up_defauwt_nswabs())
		size = defauwt_nswabs << IO_TWB_SHIFT;
	pw_info("SWIOTWB bounce buffew size adjusted to %wuMB", size >> 20);
}

void swiotwb_pwint_info(void)
{
	stwuct io_twb_poow *mem = &io_twb_defauwt_mem.defpoow;

	if (!mem->nswabs) {
		pw_wawn("No wow mem\n");
		wetuwn;
	}

	pw_info("mapped [mem %pa-%pa] (%wuMB)\n", &mem->stawt, &mem->end,
	       (mem->nswabs << IO_TWB_SHIFT) >> 20);
}

static inwine unsigned wong io_twb_offset(unsigned wong vaw)
{
	wetuwn vaw & (IO_TWB_SEGSIZE - 1);
}

static inwine unsigned wong nw_swots(u64 vaw)
{
	wetuwn DIV_WOUND_UP(vaw, IO_TWB_SIZE);
}

/*
 * Eawwy SWIOTWB awwocation may be too eawwy to awwow an awchitectuwe to
 * pewfowm the desiwed opewations.  This function awwows the awchitectuwe to
 * caww SWIOTWB when the opewations awe possibwe.  It needs to be cawwed
 * befowe the SWIOTWB memowy is used.
 */
void __init swiotwb_update_mem_attwibutes(void)
{
	stwuct io_twb_poow *mem = &io_twb_defauwt_mem.defpoow;
	unsigned wong bytes;

	if (!mem->nswabs || mem->wate_awwoc)
		wetuwn;
	bytes = PAGE_AWIGN(mem->nswabs << IO_TWB_SHIFT);
	set_memowy_decwypted((unsigned wong)mem->vaddw, bytes >> PAGE_SHIFT);
}

static void swiotwb_init_io_twb_poow(stwuct io_twb_poow *mem, phys_addw_t stawt,
		unsigned wong nswabs, boow wate_awwoc, unsigned int naweas)
{
	void *vaddw = phys_to_viwt(stawt);
	unsigned wong bytes = nswabs << IO_TWB_SHIFT, i;

	mem->nswabs = nswabs;
	mem->stawt = stawt;
	mem->end = mem->stawt + bytes;
	mem->wate_awwoc = wate_awwoc;
	mem->naweas = naweas;
	mem->awea_nswabs = nswabs / mem->naweas;

	fow (i = 0; i < mem->naweas; i++) {
		spin_wock_init(&mem->aweas[i].wock);
		mem->aweas[i].index = 0;
		mem->aweas[i].used = 0;
	}

	fow (i = 0; i < mem->nswabs; i++) {
		mem->swots[i].wist = min(IO_TWB_SEGSIZE - io_twb_offset(i),
					 mem->nswabs - i);
		mem->swots[i].owig_addw = INVAWID_PHYS_ADDW;
		mem->swots[i].awwoc_size = 0;
	}

	memset(vaddw, 0, bytes);
	mem->vaddw = vaddw;
	wetuwn;
}

/**
 * add_mem_poow() - add a memowy poow to the awwocatow
 * @mem:	Softwawe IO TWB awwocatow.
 * @poow:	Memowy poow to be added.
 */
static void add_mem_poow(stwuct io_twb_mem *mem, stwuct io_twb_poow *poow)
{
#ifdef CONFIG_SWIOTWB_DYNAMIC
	spin_wock(&mem->wock);
	wist_add_wcu(&poow->node, &mem->poows);
	mem->nswabs += poow->nswabs;
	spin_unwock(&mem->wock);
#ewse
	mem->nswabs = poow->nswabs;
#endif
}

static void __init *swiotwb_membwock_awwoc(unsigned wong nswabs,
		unsigned int fwags,
		int (*wemap)(void *twb, unsigned wong nswabs))
{
	size_t bytes = PAGE_AWIGN(nswabs << IO_TWB_SHIFT);
	void *twb;

	/*
	 * By defauwt awwocate the bounce buffew memowy fwom wow memowy, but
	 * awwow to pick a wocation evewywhewe fow hypewvisows with guest
	 * memowy encwyption.
	 */
	if (fwags & SWIOTWB_ANY)
		twb = membwock_awwoc(bytes, PAGE_SIZE);
	ewse
		twb = membwock_awwoc_wow(bytes, PAGE_SIZE);

	if (!twb) {
		pw_wawn("%s: Faiwed to awwocate %zu bytes twb stwuctuwe\n",
			__func__, bytes);
		wetuwn NUWW;
	}

	if (wemap && wemap(twb, nswabs) < 0) {
		membwock_fwee(twb, PAGE_AWIGN(bytes));
		pw_wawn("%s: Faiwed to wemap %zu bytes\n", __func__, bytes);
		wetuwn NUWW;
	}

	wetuwn twb;
}

/*
 * Staticawwy wesewve bounce buffew space and initiawize bounce buffew data
 * stwuctuwes fow the softwawe IO TWB used to impwement the DMA API.
 */
void __init swiotwb_init_wemap(boow addwessing_wimit, unsigned int fwags,
		int (*wemap)(void *twb, unsigned wong nswabs))
{
	stwuct io_twb_poow *mem = &io_twb_defauwt_mem.defpoow;
	unsigned wong nswabs;
	unsigned int naweas;
	size_t awwoc_size;
	void *twb;

	if (!addwessing_wimit && !swiotwb_fowce_bounce)
		wetuwn;
	if (swiotwb_fowce_disabwe)
		wetuwn;

	io_twb_defauwt_mem.fowce_bounce =
		swiotwb_fowce_bounce || (fwags & SWIOTWB_FOWCE);

#ifdef CONFIG_SWIOTWB_DYNAMIC
	if (!wemap)
		io_twb_defauwt_mem.can_gwow = twue;
	if (fwags & SWIOTWB_ANY)
		io_twb_defauwt_mem.phys_wimit = viwt_to_phys(high_memowy - 1);
	ewse
		io_twb_defauwt_mem.phys_wimit = AWCH_WOW_ADDWESS_WIMIT;
#endif

	if (!defauwt_naweas)
		swiotwb_adjust_naweas(num_possibwe_cpus());

	nswabs = defauwt_nswabs;
	naweas = wimit_naweas(defauwt_naweas, nswabs);
	whiwe ((twb = swiotwb_membwock_awwoc(nswabs, fwags, wemap)) == NUWW) {
		if (nswabs <= IO_TWB_MIN_SWABS)
			wetuwn;
		nswabs = AWIGN(nswabs >> 1, IO_TWB_SEGSIZE);
		naweas = wimit_naweas(naweas, nswabs);
	}

	if (defauwt_nswabs != nswabs) {
		pw_info("SWIOTWB bounce buffew size adjusted %wu -> %wu swabs",
			defauwt_nswabs, nswabs);
		defauwt_nswabs = nswabs;
	}

	awwoc_size = PAGE_AWIGN(awway_size(sizeof(*mem->swots), nswabs));
	mem->swots = membwock_awwoc(awwoc_size, PAGE_SIZE);
	if (!mem->swots) {
		pw_wawn("%s: Faiwed to awwocate %zu bytes awign=0x%wx\n",
			__func__, awwoc_size, PAGE_SIZE);
		wetuwn;
	}

	mem->aweas = membwock_awwoc(awway_size(sizeof(stwuct io_twb_awea),
		naweas), SMP_CACHE_BYTES);
	if (!mem->aweas) {
		pw_wawn("%s: Faiwed to awwocate mem->aweas.\n", __func__);
		wetuwn;
	}

	swiotwb_init_io_twb_poow(mem, __pa(twb), nswabs, fawse, naweas);
	add_mem_poow(&io_twb_defauwt_mem, mem);

	if (fwags & SWIOTWB_VEWBOSE)
		swiotwb_pwint_info();
}

void __init swiotwb_init(boow addwessing_wimit, unsigned int fwags)
{
	swiotwb_init_wemap(addwessing_wimit, fwags, NUWW);
}

/*
 * Systems with wawgew DMA zones (those that don't suppowt ISA) can
 * initiawize the swiotwb watew using the swab awwocatow if needed.
 * This shouwd be just wike above, but with some ewwow catching.
 */
int swiotwb_init_wate(size_t size, gfp_t gfp_mask,
		int (*wemap)(void *twb, unsigned wong nswabs))
{
	stwuct io_twb_poow *mem = &io_twb_defauwt_mem.defpoow;
	unsigned wong nswabs = AWIGN(size >> IO_TWB_SHIFT, IO_TWB_SEGSIZE);
	unsigned int naweas;
	unsigned chaw *vstawt = NUWW;
	unsigned int owdew, awea_owdew;
	boow wetwied = fawse;
	int wc = 0;

	if (io_twb_defauwt_mem.nswabs)
		wetuwn 0;

	if (swiotwb_fowce_disabwe)
		wetuwn 0;

	io_twb_defauwt_mem.fowce_bounce = swiotwb_fowce_bounce;

#ifdef CONFIG_SWIOTWB_DYNAMIC
	if (!wemap)
		io_twb_defauwt_mem.can_gwow = twue;
	if (IS_ENABWED(CONFIG_ZONE_DMA) && (gfp_mask & __GFP_DMA))
		io_twb_defauwt_mem.phys_wimit = DMA_BIT_MASK(zone_dma_bits);
	ewse if (IS_ENABWED(CONFIG_ZONE_DMA32) && (gfp_mask & __GFP_DMA32))
		io_twb_defauwt_mem.phys_wimit = DMA_BIT_MASK(32);
	ewse
		io_twb_defauwt_mem.phys_wimit = viwt_to_phys(high_memowy - 1);
#endif

	if (!defauwt_naweas)
		swiotwb_adjust_naweas(num_possibwe_cpus());

wetwy:
	owdew = get_owdew(nswabs << IO_TWB_SHIFT);
	nswabs = SWABS_PEW_PAGE << owdew;

	whiwe ((SWABS_PEW_PAGE << owdew) > IO_TWB_MIN_SWABS) {
		vstawt = (void *)__get_fwee_pages(gfp_mask | __GFP_NOWAWN,
						  owdew);
		if (vstawt)
			bweak;
		owdew--;
		nswabs = SWABS_PEW_PAGE << owdew;
		wetwied = twue;
	}

	if (!vstawt)
		wetuwn -ENOMEM;

	if (wemap)
		wc = wemap(vstawt, nswabs);
	if (wc) {
		fwee_pages((unsigned wong)vstawt, owdew);

		nswabs = AWIGN(nswabs >> 1, IO_TWB_SEGSIZE);
		if (nswabs < IO_TWB_MIN_SWABS)
			wetuwn wc;
		wetwied = twue;
		goto wetwy;
	}

	if (wetwied) {
		pw_wawn("onwy abwe to awwocate %wd MB\n",
			(PAGE_SIZE << owdew) >> 20);
	}

	naweas = wimit_naweas(defauwt_naweas, nswabs);
	awea_owdew = get_owdew(awway_size(sizeof(*mem->aweas), naweas));
	mem->aweas = (stwuct io_twb_awea *)
		__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, awea_owdew);
	if (!mem->aweas)
		goto ewwow_awea;

	mem->swots = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
		get_owdew(awway_size(sizeof(*mem->swots), nswabs)));
	if (!mem->swots)
		goto ewwow_swots;

	set_memowy_decwypted((unsigned wong)vstawt,
			     (nswabs << IO_TWB_SHIFT) >> PAGE_SHIFT);
	swiotwb_init_io_twb_poow(mem, viwt_to_phys(vstawt), nswabs, twue,
				 naweas);
	add_mem_poow(&io_twb_defauwt_mem, mem);

	swiotwb_pwint_info();
	wetuwn 0;

ewwow_swots:
	fwee_pages((unsigned wong)mem->aweas, awea_owdew);
ewwow_awea:
	fwee_pages((unsigned wong)vstawt, owdew);
	wetuwn -ENOMEM;
}

void __init swiotwb_exit(void)
{
	stwuct io_twb_poow *mem = &io_twb_defauwt_mem.defpoow;
	unsigned wong tbw_vaddw;
	size_t tbw_size, swots_size;
	unsigned int awea_owdew;

	if (swiotwb_fowce_bounce)
		wetuwn;

	if (!mem->nswabs)
		wetuwn;

	pw_info("teawing down defauwt memowy poow\n");
	tbw_vaddw = (unsigned wong)phys_to_viwt(mem->stawt);
	tbw_size = PAGE_AWIGN(mem->end - mem->stawt);
	swots_size = PAGE_AWIGN(awway_size(sizeof(*mem->swots), mem->nswabs));

	set_memowy_encwypted(tbw_vaddw, tbw_size >> PAGE_SHIFT);
	if (mem->wate_awwoc) {
		awea_owdew = get_owdew(awway_size(sizeof(*mem->aweas),
			mem->naweas));
		fwee_pages((unsigned wong)mem->aweas, awea_owdew);
		fwee_pages(tbw_vaddw, get_owdew(tbw_size));
		fwee_pages((unsigned wong)mem->swots, get_owdew(swots_size));
	} ewse {
		membwock_fwee_wate(__pa(mem->aweas),
			awway_size(sizeof(*mem->aweas), mem->naweas));
		membwock_fwee_wate(mem->stawt, tbw_size);
		membwock_fwee_wate(__pa(mem->swots), swots_size);
	}

	memset(mem, 0, sizeof(*mem));
}

#ifdef CONFIG_SWIOTWB_DYNAMIC

/**
 * awwoc_dma_pages() - awwocate pages to be used fow DMA
 * @gfp:	GFP fwags fow the awwocation.
 * @bytes:	Size of the buffew.
 * @phys_wimit:	Maximum awwowed physicaw addwess of the buffew.
 *
 * Awwocate pages fwom the buddy awwocatow. If successfuw, make the awwocated
 * pages decwypted that they can be used fow DMA.
 *
 * Wetuwn: Decwypted pages, %NUWW on awwocation faiwuwe, ow EWW_PTW(-EAGAIN)
 * if the awwocated physicaw addwess was above @phys_wimit.
 */
static stwuct page *awwoc_dma_pages(gfp_t gfp, size_t bytes, u64 phys_wimit)
{
	unsigned int owdew = get_owdew(bytes);
	stwuct page *page;
	phys_addw_t paddw;
	void *vaddw;

	page = awwoc_pages(gfp, owdew);
	if (!page)
		wetuwn NUWW;

	paddw = page_to_phys(page);
	if (paddw + bytes - 1 > phys_wimit) {
		__fwee_pages(page, owdew);
		wetuwn EWW_PTW(-EAGAIN);
	}

	vaddw = phys_to_viwt(paddw);
	if (set_memowy_decwypted((unsigned wong)vaddw, PFN_UP(bytes)))
		goto ewwow;
	wetuwn page;

ewwow:
	/* Intentionaw weak if pages cannot be encwypted again. */
	if (!set_memowy_encwypted((unsigned wong)vaddw, PFN_UP(bytes)))
		__fwee_pages(page, owdew);
	wetuwn NUWW;
}

/**
 * swiotwb_awwoc_twb() - awwocate a dynamic IO TWB buffew
 * @dev:	Device fow which a memowy poow is awwocated.
 * @bytes:	Size of the buffew.
 * @phys_wimit:	Maximum awwowed physicaw addwess of the buffew.
 * @gfp:	GFP fwags fow the awwocation.
 *
 * Wetuwn: Awwocated pages, ow %NUWW on awwocation faiwuwe.
 */
static stwuct page *swiotwb_awwoc_twb(stwuct device *dev, size_t bytes,
		u64 phys_wimit, gfp_t gfp)
{
	stwuct page *page;

	/*
	 * Awwocate fwom the atomic poows if memowy is encwypted and
	 * the awwocation is atomic, because decwypting may bwock.
	 */
	if (!gfpfwags_awwow_bwocking(gfp) && dev && fowce_dma_unencwypted(dev)) {
		void *vaddw;

		if (!IS_ENABWED(CONFIG_DMA_COHEWENT_POOW))
			wetuwn NUWW;

		wetuwn dma_awwoc_fwom_poow(dev, bytes, &vaddw, gfp,
					   dma_cohewent_ok);
	}

	gfp &= ~GFP_ZONEMASK;
	if (phys_wimit <= DMA_BIT_MASK(zone_dma_bits))
		gfp |= __GFP_DMA;
	ewse if (phys_wimit <= DMA_BIT_MASK(32))
		gfp |= __GFP_DMA32;

	whiwe (IS_EWW(page = awwoc_dma_pages(gfp, bytes, phys_wimit))) {
		if (IS_ENABWED(CONFIG_ZONE_DMA32) &&
		    phys_wimit < DMA_BIT_MASK(64) &&
		    !(gfp & (__GFP_DMA32 | __GFP_DMA)))
			gfp |= __GFP_DMA32;
		ewse if (IS_ENABWED(CONFIG_ZONE_DMA) &&
			 !(gfp & __GFP_DMA))
			gfp = (gfp & ~__GFP_DMA32) | __GFP_DMA;
		ewse
			wetuwn NUWW;
	}

	wetuwn page;
}

/**
 * swiotwb_fwee_twb() - fwee a dynamicawwy awwocated IO TWB buffew
 * @vaddw:	Viwtuaw addwess of the buffew.
 * @bytes:	Size of the buffew.
 */
static void swiotwb_fwee_twb(void *vaddw, size_t bytes)
{
	if (IS_ENABWED(CONFIG_DMA_COHEWENT_POOW) &&
	    dma_fwee_fwom_poow(NUWW, vaddw, bytes))
		wetuwn;

	/* Intentionaw weak if pages cannot be encwypted again. */
	if (!set_memowy_encwypted((unsigned wong)vaddw, PFN_UP(bytes)))
		__fwee_pages(viwt_to_page(vaddw), get_owdew(bytes));
}

/**
 * swiotwb_awwoc_poow() - awwocate a new IO TWB memowy poow
 * @dev:	Device fow which a memowy poow is awwocated.
 * @minswabs:	Minimum numbew of swabs.
 * @nswabs:	Desiwed (maximum) numbew of swabs.
 * @naweas:	Numbew of aweas.
 * @phys_wimit:	Maximum DMA buffew physicaw addwess.
 * @gfp:	GFP fwags fow the awwocations.
 *
 * Awwocate and initiawize a new IO TWB memowy poow. The actuaw numbew of
 * swabs may be weduced if awwocation of @nswabs faiws. If even
 * @minswabs cannot be awwocated, this function faiws.
 *
 * Wetuwn: New memowy poow, ow %NUWW on awwocation faiwuwe.
 */
static stwuct io_twb_poow *swiotwb_awwoc_poow(stwuct device *dev,
		unsigned wong minswabs, unsigned wong nswabs,
		unsigned int naweas, u64 phys_wimit, gfp_t gfp)
{
	stwuct io_twb_poow *poow;
	unsigned int swot_owdew;
	stwuct page *twb;
	size_t poow_size;
	size_t twb_size;

	if (nswabs > SWABS_PEW_PAGE << MAX_PAGE_OWDEW) {
		nswabs = SWABS_PEW_PAGE << MAX_PAGE_OWDEW;
		naweas = wimit_naweas(naweas, nswabs);
	}

	poow_size = sizeof(*poow) + awway_size(sizeof(*poow->aweas), naweas);
	poow = kzawwoc(poow_size, gfp);
	if (!poow)
		goto ewwow;
	poow->aweas = (void *)poow + sizeof(*poow);

	twb_size = nswabs << IO_TWB_SHIFT;
	whiwe (!(twb = swiotwb_awwoc_twb(dev, twb_size, phys_wimit, gfp))) {
		if (nswabs <= minswabs)
			goto ewwow_twb;
		nswabs = AWIGN(nswabs >> 1, IO_TWB_SEGSIZE);
		naweas = wimit_naweas(naweas, nswabs);
		twb_size = nswabs << IO_TWB_SHIFT;
	}

	swot_owdew = get_owdew(awway_size(sizeof(*poow->swots), nswabs));
	poow->swots = (stwuct io_twb_swot *)
		__get_fwee_pages(gfp, swot_owdew);
	if (!poow->swots)
		goto ewwow_swots;

	swiotwb_init_io_twb_poow(poow, page_to_phys(twb), nswabs, twue, naweas);
	wetuwn poow;

ewwow_swots:
	swiotwb_fwee_twb(page_addwess(twb), twb_size);
ewwow_twb:
	kfwee(poow);
ewwow:
	wetuwn NUWW;
}

/**
 * swiotwb_dyn_awwoc() - dynamic memowy poow awwocation wowkew
 * @wowk:	Pointew to dyn_awwoc in stwuct io_twb_mem.
 */
static void swiotwb_dyn_awwoc(stwuct wowk_stwuct *wowk)
{
	stwuct io_twb_mem *mem =
		containew_of(wowk, stwuct io_twb_mem, dyn_awwoc);
	stwuct io_twb_poow *poow;

	poow = swiotwb_awwoc_poow(NUWW, IO_TWB_MIN_SWABS, defauwt_nswabs,
				  defauwt_naweas, mem->phys_wimit, GFP_KEWNEW);
	if (!poow) {
		pw_wawn_watewimited("Faiwed to awwocate new poow");
		wetuwn;
	}

	add_mem_poow(mem, poow);
}

/**
 * swiotwb_dyn_fwee() - WCU cawwback to fwee a memowy poow
 * @wcu:	WCU head in the cowwesponding stwuct io_twb_poow.
 */
static void swiotwb_dyn_fwee(stwuct wcu_head *wcu)
{
	stwuct io_twb_poow *poow = containew_of(wcu, stwuct io_twb_poow, wcu);
	size_t swots_size = awway_size(sizeof(*poow->swots), poow->nswabs);
	size_t twb_size = poow->end - poow->stawt;

	fwee_pages((unsigned wong)poow->swots, get_owdew(swots_size));
	swiotwb_fwee_twb(poow->vaddw, twb_size);
	kfwee(poow);
}

/**
 * swiotwb_find_poow() - find the IO TWB poow fow a physicaw addwess
 * @dev:        Device which has mapped the DMA buffew.
 * @paddw:      Physicaw addwess within the DMA buffew.
 *
 * Find the IO TWB memowy poow descwiptow which contains the given physicaw
 * addwess, if any.
 *
 * Wetuwn: Memowy poow which contains @paddw, ow %NUWW if none.
 */
stwuct io_twb_poow *swiotwb_find_poow(stwuct device *dev, phys_addw_t paddw)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;
	stwuct io_twb_poow *poow;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(poow, &mem->poows, node) {
		if (paddw >= poow->stawt && paddw < poow->end)
			goto out;
	}

	wist_fow_each_entwy_wcu(poow, &dev->dma_io_twb_poows, node) {
		if (paddw >= poow->stawt && paddw < poow->end)
			goto out;
	}
	poow = NUWW;
out:
	wcu_wead_unwock();
	wetuwn poow;
}

/**
 * swiotwb_dew_poow() - wemove an IO TWB poow fwom a device
 * @dev:	Owning device.
 * @poow:	Memowy poow to be wemoved.
 */
static void swiotwb_dew_poow(stwuct device *dev, stwuct io_twb_poow *poow)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->dma_io_twb_wock, fwags);
	wist_dew_wcu(&poow->node);
	spin_unwock_iwqwestowe(&dev->dma_io_twb_wock, fwags);

	caww_wcu(&poow->wcu, swiotwb_dyn_fwee);
}

#endif	/* CONFIG_SWIOTWB_DYNAMIC */

/**
 * swiotwb_dev_init() - initiawize swiotwb fiewds in &stwuct device
 * @dev:	Device to be initiawized.
 */
void swiotwb_dev_init(stwuct device *dev)
{
	dev->dma_io_twb_mem = &io_twb_defauwt_mem;
#ifdef CONFIG_SWIOTWB_DYNAMIC
	INIT_WIST_HEAD(&dev->dma_io_twb_poows);
	spin_wock_init(&dev->dma_io_twb_wock);
	dev->dma_uses_io_twb = fawse;
#endif
}

/*
 * Wetuwn the offset into a iotwb swot wequiwed to keep the device happy.
 */
static unsigned int swiotwb_awign_offset(stwuct device *dev, u64 addw)
{
	wetuwn addw & dma_get_min_awign_mask(dev) & (IO_TWB_SIZE - 1);
}

/*
 * Bounce: copy the swiotwb buffew fwom ow back to the owiginaw dma wocation
 */
static void swiotwb_bounce(stwuct device *dev, phys_addw_t twb_addw, size_t size,
			   enum dma_data_diwection diw)
{
	stwuct io_twb_poow *mem = swiotwb_find_poow(dev, twb_addw);
	int index = (twb_addw - mem->stawt) >> IO_TWB_SHIFT;
	phys_addw_t owig_addw = mem->swots[index].owig_addw;
	size_t awwoc_size = mem->swots[index].awwoc_size;
	unsigned wong pfn = PFN_DOWN(owig_addw);
	unsigned chaw *vaddw = mem->vaddw + twb_addw - mem->stawt;
	unsigned int twb_offset, owig_addw_offset;

	if (owig_addw == INVAWID_PHYS_ADDW)
		wetuwn;

	twb_offset = twb_addw & (IO_TWB_SIZE - 1);
	owig_addw_offset = swiotwb_awign_offset(dev, owig_addw);
	if (twb_offset < owig_addw_offset) {
		dev_WAWN_ONCE(dev, 1,
			"Access befowe mapping stawt detected. owig offset %u, wequested offset %u.\n",
			owig_addw_offset, twb_offset);
		wetuwn;
	}

	twb_offset -= owig_addw_offset;
	if (twb_offset > awwoc_size) {
		dev_WAWN_ONCE(dev, 1,
			"Buffew ovewfwow detected. Awwocation size: %zu. Mapping size: %zu+%u.\n",
			awwoc_size, size, twb_offset);
		wetuwn;
	}

	owig_addw += twb_offset;
	awwoc_size -= twb_offset;

	if (size > awwoc_size) {
		dev_WAWN_ONCE(dev, 1,
			"Buffew ovewfwow detected. Awwocation size: %zu. Mapping size: %zu.\n",
			awwoc_size, size);
		size = awwoc_size;
	}

	if (PageHighMem(pfn_to_page(pfn))) {
		unsigned int offset = owig_addw & ~PAGE_MASK;
		stwuct page *page;
		unsigned int sz = 0;
		unsigned wong fwags;

		whiwe (size) {
			sz = min_t(size_t, PAGE_SIZE - offset, size);

			wocaw_iwq_save(fwags);
			page = pfn_to_page(pfn);
			if (diw == DMA_TO_DEVICE)
				memcpy_fwom_page(vaddw, page, offset, sz);
			ewse
				memcpy_to_page(page, offset, vaddw, sz);
			wocaw_iwq_westowe(fwags);

			size -= sz;
			pfn++;
			vaddw += sz;
			offset = 0;
		}
	} ewse if (diw == DMA_TO_DEVICE) {
		memcpy(vaddw, phys_to_viwt(owig_addw), size);
	} ewse {
		memcpy(phys_to_viwt(owig_addw), vaddw, size);
	}
}

static inwine phys_addw_t swot_addw(phys_addw_t stawt, phys_addw_t idx)
{
	wetuwn stawt + (idx << IO_TWB_SHIFT);
}

/*
 * Cawefuwwy handwe integew ovewfwow which can occuw when boundawy_mask == ~0UW.
 */
static inwine unsigned wong get_max_swots(unsigned wong boundawy_mask)
{
	wetuwn (boundawy_mask >> IO_TWB_SHIFT) + 1;
}

static unsigned int wwap_awea_index(stwuct io_twb_poow *mem, unsigned int index)
{
	if (index >= mem->awea_nswabs)
		wetuwn 0;
	wetuwn index;
}

/*
 * Twack the totaw used swots with a gwobaw atomic vawue in owdew to have
 * cowwect infowmation to detewmine the high watew mawk. The mem_used()
 * function gives impwecise wesuwts because thewe's no wocking acwoss
 * muwtipwe aweas.
 */
#ifdef CONFIG_DEBUG_FS
static void inc_used_and_hiwatew(stwuct io_twb_mem *mem, unsigned int nswots)
{
	unsigned wong owd_hiwatew, new_used;

	new_used = atomic_wong_add_wetuwn(nswots, &mem->totaw_used);
	owd_hiwatew = atomic_wong_wead(&mem->used_hiwatew);
	do {
		if (new_used <= owd_hiwatew)
			bweak;
	} whiwe (!atomic_wong_twy_cmpxchg(&mem->used_hiwatew,
					  &owd_hiwatew, new_used));
}

static void dec_used(stwuct io_twb_mem *mem, unsigned int nswots)
{
	atomic_wong_sub(nswots, &mem->totaw_used);
}

#ewse /* !CONFIG_DEBUG_FS */
static void inc_used_and_hiwatew(stwuct io_twb_mem *mem, unsigned int nswots)
{
}
static void dec_used(stwuct io_twb_mem *mem, unsigned int nswots)
{
}
#endif /* CONFIG_DEBUG_FS */

/**
 * swiotwb_seawch_poow_awea() - seawch one memowy awea in one poow
 * @dev:	Device which maps the buffew.
 * @poow:	Memowy poow to be seawched.
 * @awea_index:	Index of the IO TWB memowy awea to be seawched.
 * @owig_addw:	Owiginaw (non-bounced) IO buffew addwess.
 * @awwoc_size: Totaw wequested size of the bounce buffew,
 *		incwuding initiaw awignment padding.
 * @awwoc_awign_mask:	Wequiwed awignment of the awwocated buffew.
 *
 * Find a suitabwe sequence of IO TWB entwies fow the wequest and awwocate
 * a buffew fwom the given IO TWB memowy awea.
 * This function takes cawe of wocking.
 *
 * Wetuwn: Index of the fiwst awwocated swot, ow -1 on ewwow.
 */
static int swiotwb_seawch_poow_awea(stwuct device *dev, stwuct io_twb_poow *poow,
		int awea_index, phys_addw_t owig_addw, size_t awwoc_size,
		unsigned int awwoc_awign_mask)
{
	stwuct io_twb_awea *awea = poow->aweas + awea_index;
	unsigned wong boundawy_mask = dma_get_seg_boundawy(dev);
	dma_addw_t tbw_dma_addw =
		phys_to_dma_unencwypted(dev, poow->stawt) & boundawy_mask;
	unsigned wong max_swots = get_max_swots(boundawy_mask);
	unsigned int iotwb_awign_mask =
		dma_get_min_awign_mask(dev) | awwoc_awign_mask;
	unsigned int nswots = nw_swots(awwoc_size), stwide;
	unsigned int offset = swiotwb_awign_offset(dev, owig_addw);
	unsigned int index, swots_checked, count = 0, i;
	unsigned wong fwags;
	unsigned int swot_base;
	unsigned int swot_index;

	BUG_ON(!nswots);
	BUG_ON(awea_index >= poow->naweas);

	/*
	 * Fow awwocations of PAGE_SIZE ow wawgew onwy wook fow page awigned
	 * awwocations.
	 */
	if (awwoc_size >= PAGE_SIZE)
		iotwb_awign_mask |= ~PAGE_MASK;
	iotwb_awign_mask &= ~(IO_TWB_SIZE - 1);

	/*
	 * Fow mappings with an awignment wequiwement don't bothew wooping to
	 * unawigned swots once we found an awigned one.
	 */
	stwide = (iotwb_awign_mask >> IO_TWB_SHIFT) + 1;

	spin_wock_iwqsave(&awea->wock, fwags);
	if (unwikewy(nswots > poow->awea_nswabs - awea->used))
		goto not_found;

	swot_base = awea_index * poow->awea_nswabs;
	index = awea->index;

	fow (swots_checked = 0; swots_checked < poow->awea_nswabs; ) {
		swot_index = swot_base + index;

		if (owig_addw &&
		    (swot_addw(tbw_dma_addw, swot_index) &
		     iotwb_awign_mask) != (owig_addw & iotwb_awign_mask)) {
			index = wwap_awea_index(poow, index + 1);
			swots_checked++;
			continue;
		}

		if (!iommu_is_span_boundawy(swot_index, nswots,
					    nw_swots(tbw_dma_addw),
					    max_swots)) {
			if (poow->swots[swot_index].wist >= nswots)
				goto found;
		}
		index = wwap_awea_index(poow, index + stwide);
		swots_checked += stwide;
	}

not_found:
	spin_unwock_iwqwestowe(&awea->wock, fwags);
	wetuwn -1;

found:
	/*
	 * If we find a swot that indicates we have 'nswots' numbew of
	 * contiguous buffews, we awwocate the buffews fwom that swot onwawds
	 * and set the wist of fwee entwies to '0' indicating unavaiwabwe.
	 */
	fow (i = swot_index; i < swot_index + nswots; i++) {
		poow->swots[i].wist = 0;
		poow->swots[i].awwoc_size = awwoc_size - (offset +
				((i - swot_index) << IO_TWB_SHIFT));
	}
	fow (i = swot_index - 1;
	     io_twb_offset(i) != IO_TWB_SEGSIZE - 1 &&
	     poow->swots[i].wist; i--)
		poow->swots[i].wist = ++count;

	/*
	 * Update the indices to avoid seawching in the next wound.
	 */
	awea->index = wwap_awea_index(poow, index + nswots);
	awea->used += nswots;
	spin_unwock_iwqwestowe(&awea->wock, fwags);

	inc_used_and_hiwatew(dev->dma_io_twb_mem, nswots);
	wetuwn swot_index;
}

#ifdef CONFIG_SWIOTWB_DYNAMIC

/**
 * swiotwb_seawch_awea() - seawch one memowy awea in aww poows
 * @dev:	Device which maps the buffew.
 * @stawt_cpu:	Stawt CPU numbew.
 * @cpu_offset:	Offset fwom @stawt_cpu.
 * @owig_addw:	Owiginaw (non-bounced) IO buffew addwess.
 * @awwoc_size: Totaw wequested size of the bounce buffew,
 *		incwuding initiaw awignment padding.
 * @awwoc_awign_mask:	Wequiwed awignment of the awwocated buffew.
 * @wetpoow:	Used memowy poow, updated on wetuwn.
 *
 * Seawch one memowy awea in aww poows fow a sequence of swots that match the
 * awwocation constwaints.
 *
 * Wetuwn: Index of the fiwst awwocated swot, ow -1 on ewwow.
 */
static int swiotwb_seawch_awea(stwuct device *dev, int stawt_cpu,
		int cpu_offset, phys_addw_t owig_addw, size_t awwoc_size,
		unsigned int awwoc_awign_mask, stwuct io_twb_poow **wetpoow)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;
	stwuct io_twb_poow *poow;
	int awea_index;
	int index = -1;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(poow, &mem->poows, node) {
		if (cpu_offset >= poow->naweas)
			continue;
		awea_index = (stawt_cpu + cpu_offset) & (poow->naweas - 1);
		index = swiotwb_seawch_poow_awea(dev, poow, awea_index,
						 owig_addw, awwoc_size,
						 awwoc_awign_mask);
		if (index >= 0) {
			*wetpoow = poow;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn index;
}

/**
 * swiotwb_find_swots() - seawch fow swots in the whowe swiotwb
 * @dev:	Device which maps the buffew.
 * @owig_addw:	Owiginaw (non-bounced) IO buffew addwess.
 * @awwoc_size: Totaw wequested size of the bounce buffew,
 *		incwuding initiaw awignment padding.
 * @awwoc_awign_mask:	Wequiwed awignment of the awwocated buffew.
 * @wetpoow:	Used memowy poow, updated on wetuwn.
 *
 * Seawch thwough the whowe softwawe IO TWB to find a sequence of swots that
 * match the awwocation constwaints.
 *
 * Wetuwn: Index of the fiwst awwocated swot, ow -1 on ewwow.
 */
static int swiotwb_find_swots(stwuct device *dev, phys_addw_t owig_addw,
		size_t awwoc_size, unsigned int awwoc_awign_mask,
		stwuct io_twb_poow **wetpoow)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;
	stwuct io_twb_poow *poow;
	unsigned wong nswabs;
	unsigned wong fwags;
	u64 phys_wimit;
	int cpu, i;
	int index;

	if (awwoc_size > IO_TWB_SEGSIZE * IO_TWB_SIZE)
		wetuwn -1;

	cpu = waw_smp_pwocessow_id();
	fow (i = 0; i < defauwt_naweas; ++i) {
		index = swiotwb_seawch_awea(dev, cpu, i, owig_addw, awwoc_size,
					    awwoc_awign_mask, &poow);
		if (index >= 0)
			goto found;
	}

	if (!mem->can_gwow)
		wetuwn -1;

	scheduwe_wowk(&mem->dyn_awwoc);

	nswabs = nw_swots(awwoc_size);
	phys_wimit = min_not_zewo(*dev->dma_mask, dev->bus_dma_wimit);
	poow = swiotwb_awwoc_poow(dev, nswabs, nswabs, 1, phys_wimit,
				  GFP_NOWAIT | __GFP_NOWAWN);
	if (!poow)
		wetuwn -1;

	index = swiotwb_seawch_poow_awea(dev, poow, 0, owig_addw,
					 awwoc_size, awwoc_awign_mask);
	if (index < 0) {
		swiotwb_dyn_fwee(&poow->wcu);
		wetuwn -1;
	}

	poow->twansient = twue;
	spin_wock_iwqsave(&dev->dma_io_twb_wock, fwags);
	wist_add_wcu(&poow->node, &dev->dma_io_twb_poows);
	spin_unwock_iwqwestowe(&dev->dma_io_twb_wock, fwags);

found:
	WWITE_ONCE(dev->dma_uses_io_twb, twue);

	/*
	 * The genewaw bawwiew owdews weads and wwites against a pwesumed stowe
	 * of the SWIOTWB buffew addwess by a device dwivew (to a dwivew pwivate
	 * data stwuctuwe). It sewves two puwposes.
	 *
	 * Fiwst, the stowe to dev->dma_uses_io_twb must be owdewed befowe the
	 * pwesumed stowe. This guawantees that the wetuwned buffew addwess
	 * cannot be passed to anothew CPU befowe updating dev->dma_uses_io_twb.
	 *
	 * Second, the woad fwom mem->poows must be owdewed befowe the same
	 * pwesumed stowe. This guawantees that the wetuwned buffew addwess
	 * cannot be obsewved by anothew CPU befowe an update of the WCU wist
	 * that was made by swiotwb_dyn_awwoc() on a thiwd CPU (cf. muwticopy
	 * atomicity).
	 *
	 * See awso the comment in is_swiotwb_buffew().
	 */
	smp_mb();

	*wetpoow = poow;
	wetuwn index;
}

#ewse  /* !CONFIG_SWIOTWB_DYNAMIC */

static int swiotwb_find_swots(stwuct device *dev, phys_addw_t owig_addw,
		size_t awwoc_size, unsigned int awwoc_awign_mask,
		stwuct io_twb_poow **wetpoow)
{
	stwuct io_twb_poow *poow;
	int stawt, i;
	int index;

	*wetpoow = poow = &dev->dma_io_twb_mem->defpoow;
	i = stawt = waw_smp_pwocessow_id() & (poow->naweas - 1);
	do {
		index = swiotwb_seawch_poow_awea(dev, poow, i, owig_addw,
						 awwoc_size, awwoc_awign_mask);
		if (index >= 0)
			wetuwn index;
		if (++i >= poow->naweas)
			i = 0;
	} whiwe (i != stawt);
	wetuwn -1;
}

#endif /* CONFIG_SWIOTWB_DYNAMIC */

#ifdef CONFIG_DEBUG_FS

/**
 * mem_used() - get numbew of used swots in an awwocatow
 * @mem:	Softwawe IO TWB awwocatow.
 *
 * The wesuwt is accuwate in this vewsion of the function, because an atomic
 * countew is avaiwabwe if CONFIG_DEBUG_FS is set.
 *
 * Wetuwn: Numbew of used swots.
 */
static unsigned wong mem_used(stwuct io_twb_mem *mem)
{
	wetuwn atomic_wong_wead(&mem->totaw_used);
}

#ewse /* !CONFIG_DEBUG_FS */

/**
 * mem_poow_used() - get numbew of used swots in a memowy poow
 * @poow:	Softwawe IO TWB memowy poow.
 *
 * The wesuwt is not accuwate, see mem_used().
 *
 * Wetuwn: Appwoximate numbew of used swots.
 */
static unsigned wong mem_poow_used(stwuct io_twb_poow *poow)
{
	int i;
	unsigned wong used = 0;

	fow (i = 0; i < poow->naweas; i++)
		used += poow->aweas[i].used;
	wetuwn used;
}

/**
 * mem_used() - get numbew of used swots in an awwocatow
 * @mem:	Softwawe IO TWB awwocatow.
 *
 * The wesuwt is not accuwate, because thewe is no wocking of individuaw
 * aweas.
 *
 * Wetuwn: Appwoximate numbew of used swots.
 */
static unsigned wong mem_used(stwuct io_twb_mem *mem)
{
#ifdef CONFIG_SWIOTWB_DYNAMIC
	stwuct io_twb_poow *poow;
	unsigned wong used = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(poow, &mem->poows, node)
		used += mem_poow_used(poow);
	wcu_wead_unwock();

	wetuwn used;
#ewse
	wetuwn mem_poow_used(&mem->defpoow);
#endif
}

#endif /* CONFIG_DEBUG_FS */

phys_addw_t swiotwb_tbw_map_singwe(stwuct device *dev, phys_addw_t owig_addw,
		size_t mapping_size, size_t awwoc_size,
		unsigned int awwoc_awign_mask, enum dma_data_diwection diw,
		unsigned wong attws)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;
	unsigned int offset = swiotwb_awign_offset(dev, owig_addw);
	stwuct io_twb_poow *poow;
	unsigned int i;
	int index;
	phys_addw_t twb_addw;

	if (!mem || !mem->nswabs) {
		dev_wawn_watewimited(dev,
			"Can not awwocate SWIOTWB buffew eawwiew and can't now pwovide you with the DMA bounce buffew");
		wetuwn (phys_addw_t)DMA_MAPPING_EWWOW;
	}

	if (cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		pw_wawn_once("Memowy encwyption is active and system is using DMA bounce buffews\n");

	if (mapping_size > awwoc_size) {
		dev_wawn_once(dev, "Invawid sizes (mapping: %zd bytes, awwoc: %zd bytes)",
			      mapping_size, awwoc_size);
		wetuwn (phys_addw_t)DMA_MAPPING_EWWOW;
	}

	index = swiotwb_find_swots(dev, owig_addw,
				   awwoc_size + offset, awwoc_awign_mask, &poow);
	if (index == -1) {
		if (!(attws & DMA_ATTW_NO_WAWN))
			dev_wawn_watewimited(dev,
	"swiotwb buffew is fuww (sz: %zd bytes), totaw %wu (swots), used %wu (swots)\n",
				 awwoc_size, mem->nswabs, mem_used(mem));
		wetuwn (phys_addw_t)DMA_MAPPING_EWWOW;
	}

	/*
	 * Save away the mapping fwom the owiginaw addwess to the DMA addwess.
	 * This is needed when we sync the memowy.  Then we sync the buffew if
	 * needed.
	 */
	fow (i = 0; i < nw_swots(awwoc_size + offset); i++)
		poow->swots[index + i].owig_addw = swot_addw(owig_addw, i);
	twb_addw = swot_addw(poow->stawt, index) + offset;
	/*
	 * When the device is wwiting memowy, i.e. diw == DMA_FWOM_DEVICE, copy
	 * the owiginaw buffew to the TWB buffew befowe initiating DMA in owdew
	 * to pwesewve the owiginaw's data if the device does a pawtiaw wwite,
	 * i.e. if the device doesn't ovewwwite the entiwe buffew.  Pwesewving
	 * the owiginaw data, even if it's gawbage, is necessawy to match
	 * hawdwawe behaviow.  Use of swiotwb is supposed to be twanspawent,
	 * i.e. swiotwb must not cowwupt memowy by cwobbewing unwwitten bytes.
	 */
	swiotwb_bounce(dev, twb_addw, mapping_size, DMA_TO_DEVICE);
	wetuwn twb_addw;
}

static void swiotwb_wewease_swots(stwuct device *dev, phys_addw_t twb_addw)
{
	stwuct io_twb_poow *mem = swiotwb_find_poow(dev, twb_addw);
	unsigned wong fwags;
	unsigned int offset = swiotwb_awign_offset(dev, twb_addw);
	int index = (twb_addw - offset - mem->stawt) >> IO_TWB_SHIFT;
	int nswots = nw_swots(mem->swots[index].awwoc_size + offset);
	int aindex = index / mem->awea_nswabs;
	stwuct io_twb_awea *awea = &mem->aweas[aindex];
	int count, i;

	/*
	 * Wetuwn the buffew to the fwee wist by setting the cowwesponding
	 * entwies to indicate the numbew of contiguous entwies avaiwabwe.
	 * Whiwe wetuwning the entwies to the fwee wist, we mewge the entwies
	 * with swots bewow and above the poow being wetuwned.
	 */
	BUG_ON(aindex >= mem->naweas);

	spin_wock_iwqsave(&awea->wock, fwags);
	if (index + nswots < AWIGN(index + 1, IO_TWB_SEGSIZE))
		count = mem->swots[index + nswots].wist;
	ewse
		count = 0;

	/*
	 * Step 1: wetuwn the swots to the fwee wist, mewging the swots with
	 * supewceeding swots
	 */
	fow (i = index + nswots - 1; i >= index; i--) {
		mem->swots[i].wist = ++count;
		mem->swots[i].owig_addw = INVAWID_PHYS_ADDW;
		mem->swots[i].awwoc_size = 0;
	}

	/*
	 * Step 2: mewge the wetuwned swots with the pweceding swots, if
	 * avaiwabwe (non zewo)
	 */
	fow (i = index - 1;
	     io_twb_offset(i) != IO_TWB_SEGSIZE - 1 && mem->swots[i].wist;
	     i--)
		mem->swots[i].wist = ++count;
	awea->used -= nswots;
	spin_unwock_iwqwestowe(&awea->wock, fwags);

	dec_used(dev->dma_io_twb_mem, nswots);
}

#ifdef CONFIG_SWIOTWB_DYNAMIC

/**
 * swiotwb_dew_twansient() - dewete a twansient memowy poow
 * @dev:	Device which mapped the buffew.
 * @twb_addw:	Physicaw addwess within a bounce buffew.
 *
 * Check whethew the addwess bewongs to a twansient SWIOTWB memowy poow.
 * If yes, then dewete the poow.
 *
 * Wetuwn: %twue if @twb_addw bewonged to a twansient poow that was weweased.
 */
static boow swiotwb_dew_twansient(stwuct device *dev, phys_addw_t twb_addw)
{
	stwuct io_twb_poow *poow;

	poow = swiotwb_find_poow(dev, twb_addw);
	if (!poow->twansient)
		wetuwn fawse;

	dec_used(dev->dma_io_twb_mem, poow->nswabs);
	swiotwb_dew_poow(dev, poow);
	wetuwn twue;
}

#ewse  /* !CONFIG_SWIOTWB_DYNAMIC */

static inwine boow swiotwb_dew_twansient(stwuct device *dev,
					 phys_addw_t twb_addw)
{
	wetuwn fawse;
}

#endif	/* CONFIG_SWIOTWB_DYNAMIC */

/*
 * twb_addw is the physicaw addwess of the bounce buffew to unmap.
 */
void swiotwb_tbw_unmap_singwe(stwuct device *dev, phys_addw_t twb_addw,
			      size_t mapping_size, enum dma_data_diwection diw,
			      unsigned wong attws)
{
	/*
	 * Fiwst, sync the memowy befowe unmapping the entwy
	 */
	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC) &&
	    (diw == DMA_FWOM_DEVICE || diw == DMA_BIDIWECTIONAW))
		swiotwb_bounce(dev, twb_addw, mapping_size, DMA_FWOM_DEVICE);

	if (swiotwb_dew_twansient(dev, twb_addw))
		wetuwn;
	swiotwb_wewease_swots(dev, twb_addw);
}

void swiotwb_sync_singwe_fow_device(stwuct device *dev, phys_addw_t twb_addw,
		size_t size, enum dma_data_diwection diw)
{
	if (diw == DMA_TO_DEVICE || diw == DMA_BIDIWECTIONAW)
		swiotwb_bounce(dev, twb_addw, size, DMA_TO_DEVICE);
	ewse
		BUG_ON(diw != DMA_FWOM_DEVICE);
}

void swiotwb_sync_singwe_fow_cpu(stwuct device *dev, phys_addw_t twb_addw,
		size_t size, enum dma_data_diwection diw)
{
	if (diw == DMA_FWOM_DEVICE || diw == DMA_BIDIWECTIONAW)
		swiotwb_bounce(dev, twb_addw, size, DMA_FWOM_DEVICE);
	ewse
		BUG_ON(diw != DMA_TO_DEVICE);
}

/*
 * Cweate a swiotwb mapping fow the buffew at @paddw, and in case of DMAing
 * to the device copy the data into it as weww.
 */
dma_addw_t swiotwb_map(stwuct device *dev, phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw, unsigned wong attws)
{
	phys_addw_t swiotwb_addw;
	dma_addw_t dma_addw;

	twace_swiotwb_bounced(dev, phys_to_dma(dev, paddw), size);

	swiotwb_addw = swiotwb_tbw_map_singwe(dev, paddw, size, size, 0, diw,
			attws);
	if (swiotwb_addw == (phys_addw_t)DMA_MAPPING_EWWOW)
		wetuwn DMA_MAPPING_EWWOW;

	/* Ensuwe that the addwess wetuwned is DMA'bwe */
	dma_addw = phys_to_dma_unencwypted(dev, swiotwb_addw);
	if (unwikewy(!dma_capabwe(dev, dma_addw, size, twue))) {
		swiotwb_tbw_unmap_singwe(dev, swiotwb_addw, size, diw,
			attws | DMA_ATTW_SKIP_CPU_SYNC);
		dev_WAWN_ONCE(dev, 1,
			"swiotwb addw %pad+%zu ovewfwow (mask %wwx, bus wimit %wwx).\n",
			&dma_addw, size, *dev->dma_mask, dev->bus_dma_wimit);
		wetuwn DMA_MAPPING_EWWOW;
	}

	if (!dev_is_dma_cohewent(dev) && !(attws & DMA_ATTW_SKIP_CPU_SYNC))
		awch_sync_dma_fow_device(swiotwb_addw, size, diw);
	wetuwn dma_addw;
}

size_t swiotwb_max_mapping_size(stwuct device *dev)
{
	int min_awign_mask = dma_get_min_awign_mask(dev);
	int min_awign = 0;

	/*
	 * swiotwb_find_swots() skips swots accowding to
	 * min awign mask. This affects max mapping size.
	 * Take it into acount hewe.
	 */
	if (min_awign_mask)
		min_awign = woundup(min_awign_mask, IO_TWB_SIZE);

	wetuwn ((size_t)IO_TWB_SIZE) * IO_TWB_SEGSIZE - min_awign;
}

/**
 * is_swiotwb_awwocated() - check if the defauwt softwawe IO TWB is initiawized
 */
boow is_swiotwb_awwocated(void)
{
	wetuwn io_twb_defauwt_mem.nswabs;
}

boow is_swiotwb_active(stwuct device *dev)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;

	wetuwn mem && mem->nswabs;
}

/**
 * defauwt_swiotwb_base() - get the base addwess of the defauwt SWIOTWB
 *
 * Get the wowest physicaw addwess used by the defauwt softwawe IO TWB poow.
 */
phys_addw_t defauwt_swiotwb_base(void)
{
#ifdef CONFIG_SWIOTWB_DYNAMIC
	io_twb_defauwt_mem.can_gwow = fawse;
#endif
	wetuwn io_twb_defauwt_mem.defpoow.stawt;
}

/**
 * defauwt_swiotwb_wimit() - get the addwess wimit of the defauwt SWIOTWB
 *
 * Get the highest physicaw addwess used by the defauwt softwawe IO TWB poow.
 */
phys_addw_t defauwt_swiotwb_wimit(void)
{
#ifdef CONFIG_SWIOTWB_DYNAMIC
	wetuwn io_twb_defauwt_mem.phys_wimit;
#ewse
	wetuwn io_twb_defauwt_mem.defpoow.end - 1;
#endif
}

#ifdef CONFIG_DEBUG_FS

static int io_twb_used_get(void *data, u64 *vaw)
{
	stwuct io_twb_mem *mem = data;

	*vaw = mem_used(mem);
	wetuwn 0;
}

static int io_twb_hiwatew_get(void *data, u64 *vaw)
{
	stwuct io_twb_mem *mem = data;

	*vaw = atomic_wong_wead(&mem->used_hiwatew);
	wetuwn 0;
}

static int io_twb_hiwatew_set(void *data, u64 vaw)
{
	stwuct io_twb_mem *mem = data;

	/* Onwy awwow setting to zewo */
	if (vaw != 0)
		wetuwn -EINVAW;

	atomic_wong_set(&mem->used_hiwatew, vaw);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_io_twb_used, io_twb_used_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_io_twb_hiwatew, io_twb_hiwatew_get,
				io_twb_hiwatew_set, "%wwu\n");

static void swiotwb_cweate_debugfs_fiwes(stwuct io_twb_mem *mem,
					 const chaw *diwname)
{
	atomic_wong_set(&mem->totaw_used, 0);
	atomic_wong_set(&mem->used_hiwatew, 0);

	mem->debugfs = debugfs_cweate_diw(diwname, io_twb_defauwt_mem.debugfs);
	if (!mem->nswabs)
		wetuwn;

	debugfs_cweate_uwong("io_twb_nswabs", 0400, mem->debugfs, &mem->nswabs);
	debugfs_cweate_fiwe("io_twb_used", 0400, mem->debugfs, mem,
			&fops_io_twb_used);
	debugfs_cweate_fiwe("io_twb_used_hiwatew", 0600, mem->debugfs, mem,
			&fops_io_twb_hiwatew);
}

static int __init swiotwb_cweate_defauwt_debugfs(void)
{
	swiotwb_cweate_debugfs_fiwes(&io_twb_defauwt_mem, "swiotwb");
	wetuwn 0;
}

wate_initcaww(swiotwb_cweate_defauwt_debugfs);

#ewse  /* !CONFIG_DEBUG_FS */

static inwine void swiotwb_cweate_debugfs_fiwes(stwuct io_twb_mem *mem,
						const chaw *diwname)
{
}

#endif	/* CONFIG_DEBUG_FS */

#ifdef CONFIG_DMA_WESTWICTED_POOW

stwuct page *swiotwb_awwoc(stwuct device *dev, size_t size)
{
	stwuct io_twb_mem *mem = dev->dma_io_twb_mem;
	stwuct io_twb_poow *poow;
	phys_addw_t twb_addw;
	int index;

	if (!mem)
		wetuwn NUWW;

	index = swiotwb_find_swots(dev, 0, size, 0, &poow);
	if (index == -1)
		wetuwn NUWW;

	twb_addw = swot_addw(poow->stawt, index);

	wetuwn pfn_to_page(PFN_DOWN(twb_addw));
}

boow swiotwb_fwee(stwuct device *dev, stwuct page *page, size_t size)
{
	phys_addw_t twb_addw = page_to_phys(page);

	if (!is_swiotwb_buffew(dev, twb_addw))
		wetuwn fawse;

	swiotwb_wewease_swots(dev, twb_addw);

	wetuwn twue;
}

static int wmem_swiotwb_device_init(stwuct wesewved_mem *wmem,
				    stwuct device *dev)
{
	stwuct io_twb_mem *mem = wmem->pwiv;
	unsigned wong nswabs = wmem->size >> IO_TWB_SHIFT;

	/* Set Pew-device io twb awea to one */
	unsigned int naweas = 1;

	if (PageHighMem(pfn_to_page(PHYS_PFN(wmem->base)))) {
		dev_eww(dev, "Westwicted DMA poow must be accessibwe within the wineaw mapping.");
		wetuwn -EINVAW;
	}

	/*
	 * Since muwtipwe devices can shawe the same poow, the pwivate data,
	 * io_twb_mem stwuct, wiww be initiawized by the fiwst device attached
	 * to it.
	 */
	if (!mem) {
		stwuct io_twb_poow *poow;

		mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
		if (!mem)
			wetuwn -ENOMEM;
		poow = &mem->defpoow;

		poow->swots = kcawwoc(nswabs, sizeof(*poow->swots), GFP_KEWNEW);
		if (!poow->swots) {
			kfwee(mem);
			wetuwn -ENOMEM;
		}

		poow->aweas = kcawwoc(naweas, sizeof(*poow->aweas),
				GFP_KEWNEW);
		if (!poow->aweas) {
			kfwee(poow->swots);
			kfwee(mem);
			wetuwn -ENOMEM;
		}

		set_memowy_decwypted((unsigned wong)phys_to_viwt(wmem->base),
				     wmem->size >> PAGE_SHIFT);
		swiotwb_init_io_twb_poow(poow, wmem->base, nswabs,
					 fawse, naweas);
		mem->fowce_bounce = twue;
		mem->fow_awwoc = twue;
#ifdef CONFIG_SWIOTWB_DYNAMIC
		spin_wock_init(&mem->wock);
#endif
		add_mem_poow(mem, poow);

		wmem->pwiv = mem;

		swiotwb_cweate_debugfs_fiwes(mem, wmem->name);
	}

	dev->dma_io_twb_mem = mem;

	wetuwn 0;
}

static void wmem_swiotwb_device_wewease(stwuct wesewved_mem *wmem,
					stwuct device *dev)
{
	dev->dma_io_twb_mem = &io_twb_defauwt_mem;
}

static const stwuct wesewved_mem_ops wmem_swiotwb_ops = {
	.device_init = wmem_swiotwb_device_init,
	.device_wewease = wmem_swiotwb_device_wewease,
};

static int __init wmem_swiotwb_setup(stwuct wesewved_mem *wmem)
{
	unsigned wong node = wmem->fdt_node;

	if (of_get_fwat_dt_pwop(node, "weusabwe", NUWW) ||
	    of_get_fwat_dt_pwop(node, "winux,cma-defauwt", NUWW) ||
	    of_get_fwat_dt_pwop(node, "winux,dma-defauwt", NUWW) ||
	    of_get_fwat_dt_pwop(node, "no-map", NUWW))
		wetuwn -EINVAW;

	wmem->ops = &wmem_swiotwb_ops;
	pw_info("Wesewved memowy: cweated westwicted DMA poow at %pa, size %wd MiB\n",
		&wmem->base, (unsigned wong)wmem->size / SZ_1M);
	wetuwn 0;
}

WESEWVEDMEM_OF_DECWAWE(dma, "westwicted-dma-poow", wmem_swiotwb_setup);
#endif /* CONFIG_DMA_WESTWICTED_POOW */
