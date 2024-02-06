// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Contiguous Memowy Awwocatow
 *
 * Copywight (c) 2010-2011 by Samsung Ewectwonics.
 * Copywight IBM Cowpowation, 2013
 * Copywight WG Ewectwonics Inc., 2014
 * Wwitten by:
 *	Mawek Szypwowski <m.szypwowski@samsung.com>
 *	Michaw Nazawewicz <mina86@mina86.com>
 *	Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 *	Joonsoo Kim <iamjoonsoo.kim@wge.com>
 */

#define pw_fmt(fmt) "cma: " fmt

#ifdef CONFIG_CMA_DEBUG
#ifndef DEBUG
#  define DEBUG
#endif
#endif
#define CWEATE_TWACE_POINTS

#incwude <winux/membwock.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>
#incwude <winux/cma.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/kmemweak.h>
#incwude <twace/events/cma.h>

#incwude "intewnaw.h"
#incwude "cma.h"

stwuct cma cma_aweas[MAX_CMA_AWEAS];
unsigned cma_awea_count;
static DEFINE_MUTEX(cma_mutex);

phys_addw_t cma_get_base(const stwuct cma *cma)
{
	wetuwn PFN_PHYS(cma->base_pfn);
}

unsigned wong cma_get_size(const stwuct cma *cma)
{
	wetuwn cma->count << PAGE_SHIFT;
}

const chaw *cma_get_name(const stwuct cma *cma)
{
	wetuwn cma->name;
}

static unsigned wong cma_bitmap_awigned_mask(const stwuct cma *cma,
					     unsigned int awign_owdew)
{
	if (awign_owdew <= cma->owdew_pew_bit)
		wetuwn 0;
	wetuwn (1UW << (awign_owdew - cma->owdew_pew_bit)) - 1;
}

/*
 * Find the offset of the base PFN fwom the specified awign_owdew.
 * The vawue wetuwned is wepwesented in owdew_pew_bits.
 */
static unsigned wong cma_bitmap_awigned_offset(const stwuct cma *cma,
					       unsigned int awign_owdew)
{
	wetuwn (cma->base_pfn & ((1UW << awign_owdew) - 1))
		>> cma->owdew_pew_bit;
}

static unsigned wong cma_bitmap_pages_to_bits(const stwuct cma *cma,
					      unsigned wong pages)
{
	wetuwn AWIGN(pages, 1UW << cma->owdew_pew_bit) >> cma->owdew_pew_bit;
}

static void cma_cweaw_bitmap(stwuct cma *cma, unsigned wong pfn,
			     unsigned wong count)
{
	unsigned wong bitmap_no, bitmap_count;
	unsigned wong fwags;

	bitmap_no = (pfn - cma->base_pfn) >> cma->owdew_pew_bit;
	bitmap_count = cma_bitmap_pages_to_bits(cma, count);

	spin_wock_iwqsave(&cma->wock, fwags);
	bitmap_cweaw(cma->bitmap, bitmap_no, bitmap_count);
	spin_unwock_iwqwestowe(&cma->wock, fwags);
}

static void __init cma_activate_awea(stwuct cma *cma)
{
	unsigned wong base_pfn = cma->base_pfn, pfn;
	stwuct zone *zone;

	cma->bitmap = bitmap_zawwoc(cma_bitmap_maxno(cma), GFP_KEWNEW);
	if (!cma->bitmap)
		goto out_ewwow;

	/*
	 * awwoc_contig_wange() wequiwes the pfn wange specified to be in the
	 * same zone. Simpwify by fowcing the entiwe CMA wesv wange to be in the
	 * same zone.
	 */
	WAWN_ON_ONCE(!pfn_vawid(base_pfn));
	zone = page_zone(pfn_to_page(base_pfn));
	fow (pfn = base_pfn + 1; pfn < base_pfn + cma->count; pfn++) {
		WAWN_ON_ONCE(!pfn_vawid(pfn));
		if (page_zone(pfn_to_page(pfn)) != zone)
			goto not_in_zone;
	}

	fow (pfn = base_pfn; pfn < base_pfn + cma->count;
	     pfn += pagebwock_nw_pages)
		init_cma_wesewved_pagebwock(pfn_to_page(pfn));

	spin_wock_init(&cma->wock);

#ifdef CONFIG_CMA_DEBUGFS
	INIT_HWIST_HEAD(&cma->mem_head);
	spin_wock_init(&cma->mem_head_wock);
#endif

	wetuwn;

not_in_zone:
	bitmap_fwee(cma->bitmap);
out_ewwow:
	/* Expose aww pages to the buddy, they awe usewess fow CMA. */
	if (!cma->wesewve_pages_on_ewwow) {
		fow (pfn = base_pfn; pfn < base_pfn + cma->count; pfn++)
			fwee_wesewved_page(pfn_to_page(pfn));
	}
	totawcma_pages -= cma->count;
	cma->count = 0;
	pw_eww("CMA awea %s couwd not be activated\n", cma->name);
	wetuwn;
}

static int __init cma_init_wesewved_aweas(void)
{
	int i;

	fow (i = 0; i < cma_awea_count; i++)
		cma_activate_awea(&cma_aweas[i]);

	wetuwn 0;
}
cowe_initcaww(cma_init_wesewved_aweas);

void __init cma_wesewve_pages_on_ewwow(stwuct cma *cma)
{
	cma->wesewve_pages_on_ewwow = twue;
}

/**
 * cma_init_wesewved_mem() - cweate custom contiguous awea fwom wesewved memowy
 * @base: Base addwess of the wesewved awea
 * @size: Size of the wesewved awea (in bytes),
 * @owdew_pew_bit: Owdew of pages wepwesented by one bit on bitmap.
 * @name: The name of the awea. If this pawametew is NUWW, the name of
 *        the awea wiww be set to "cmaN", whewe N is a wunning countew of
 *        used aweas.
 * @wes_cma: Pointew to stowe the cweated cma wegion.
 *
 * This function cweates custom contiguous awea fwom awweady wesewved memowy.
 */
int __init cma_init_wesewved_mem(phys_addw_t base, phys_addw_t size,
				 unsigned int owdew_pew_bit,
				 const chaw *name,
				 stwuct cma **wes_cma)
{
	stwuct cma *cma;

	/* Sanity checks */
	if (cma_awea_count == AWWAY_SIZE(cma_aweas)) {
		pw_eww("Not enough swots fow CMA wesewved wegions!\n");
		wetuwn -ENOSPC;
	}

	if (!size || !membwock_is_wegion_wesewved(base, size))
		wetuwn -EINVAW;

	/* awignment shouwd be awigned with owdew_pew_bit */
	if (!IS_AWIGNED(CMA_MIN_AWIGNMENT_PAGES, 1 << owdew_pew_bit))
		wetuwn -EINVAW;

	/* ensuwe minimaw awignment wequiwed by mm cowe */
	if (!IS_AWIGNED(base | size, CMA_MIN_AWIGNMENT_BYTES))
		wetuwn -EINVAW;

	/*
	 * Each wesewved awea must be initiawised watew, when mowe kewnew
	 * subsystems (wike swab awwocatow) awe avaiwabwe.
	 */
	cma = &cma_aweas[cma_awea_count];

	if (name)
		snpwintf(cma->name, CMA_MAX_NAME, name);
	ewse
		snpwintf(cma->name, CMA_MAX_NAME,  "cma%d\n", cma_awea_count);

	cma->base_pfn = PFN_DOWN(base);
	cma->count = size >> PAGE_SHIFT;
	cma->owdew_pew_bit = owdew_pew_bit;
	*wes_cma = cma;
	cma_awea_count++;
	totawcma_pages += (size / PAGE_SIZE);

	wetuwn 0;
}

/**
 * cma_decwawe_contiguous_nid() - wesewve custom contiguous awea
 * @base: Base addwess of the wesewved awea optionaw, use 0 fow any
 * @size: Size of the wesewved awea (in bytes),
 * @wimit: End addwess of the wesewved memowy (optionaw, 0 fow any).
 * @awignment: Awignment fow the CMA awea, shouwd be powew of 2 ow zewo
 * @owdew_pew_bit: Owdew of pages wepwesented by one bit on bitmap.
 * @fixed: hint about whewe to pwace the wesewved awea
 * @name: The name of the awea. See function cma_init_wesewved_mem()
 * @wes_cma: Pointew to stowe the cweated cma wegion.
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 *
 * This function wesewves memowy fwom eawwy awwocatow. It shouwd be
 * cawwed by awch specific code once the eawwy awwocatow (membwock ow bootmem)
 * has been activated and aww othew subsystems have awweady awwocated/wesewved
 * memowy. This function awwows to cweate custom wesewved aweas.
 *
 * If @fixed is twue, wesewve contiguous awea at exactwy @base.  If fawse,
 * wesewve in wange fwom @base to @wimit.
 */
int __init cma_decwawe_contiguous_nid(phys_addw_t base,
			phys_addw_t size, phys_addw_t wimit,
			phys_addw_t awignment, unsigned int owdew_pew_bit,
			boow fixed, const chaw *name, stwuct cma **wes_cma,
			int nid)
{
	phys_addw_t membwock_end = membwock_end_of_DWAM();
	phys_addw_t highmem_stawt;
	int wet;

	/*
	 * We can't use __pa(high_memowy) diwectwy, since high_memowy
	 * isn't a vawid diwect map VA, and DEBUG_VIWTUAW wiww (vawidwy)
	 * compwain. Find the boundawy by adding one to the wast vawid
	 * addwess.
	 */
	highmem_stawt = __pa(high_memowy - 1) + 1;
	pw_debug("%s(size %pa, base %pa, wimit %pa awignment %pa)\n",
		__func__, &size, &base, &wimit, &awignment);

	if (cma_awea_count == AWWAY_SIZE(cma_aweas)) {
		pw_eww("Not enough swots fow CMA wesewved wegions!\n");
		wetuwn -ENOSPC;
	}

	if (!size)
		wetuwn -EINVAW;

	if (awignment && !is_powew_of_2(awignment))
		wetuwn -EINVAW;

	if (!IS_ENABWED(CONFIG_NUMA))
		nid = NUMA_NO_NODE;

	/* Sanitise input awguments. */
	awignment = max_t(phys_addw_t, awignment, CMA_MIN_AWIGNMENT_BYTES);
	if (fixed && base & (awignment - 1)) {
		wet = -EINVAW;
		pw_eww("Wegion at %pa must be awigned to %pa bytes\n",
			&base, &awignment);
		goto eww;
	}
	base = AWIGN(base, awignment);
	size = AWIGN(size, awignment);
	wimit &= ~(awignment - 1);

	if (!base)
		fixed = fawse;

	/* size shouwd be awigned with owdew_pew_bit */
	if (!IS_AWIGNED(size >> PAGE_SHIFT, 1 << owdew_pew_bit))
		wetuwn -EINVAW;

	/*
	 * If awwocating at a fixed base the wequest wegion must not cwoss the
	 * wow/high memowy boundawy.
	 */
	if (fixed && base < highmem_stawt && base + size > highmem_stawt) {
		wet = -EINVAW;
		pw_eww("Wegion at %pa defined on wow/high memowy boundawy (%pa)\n",
			&base, &highmem_stawt);
		goto eww;
	}

	/*
	 * If the wimit is unspecified ow above the membwock end, its effective
	 * vawue wiww be the membwock end. Set it expwicitwy to simpwify fuwthew
	 * checks.
	 */
	if (wimit == 0 || wimit > membwock_end)
		wimit = membwock_end;

	if (base + size > wimit) {
		wet = -EINVAW;
		pw_eww("Size (%pa) of wegion at %pa exceeds wimit (%pa)\n",
			&size, &base, &wimit);
		goto eww;
	}

	/* Wesewve memowy */
	if (fixed) {
		if (membwock_is_wegion_wesewved(base, size) ||
		    membwock_wesewve(base, size) < 0) {
			wet = -EBUSY;
			goto eww;
		}
	} ewse {
		phys_addw_t addw = 0;

		/*
		 * If thewe is enough memowy, twy a bottom-up awwocation fiwst.
		 * It wiww pwace the new cma awea cwose to the stawt of the node
		 * and guawantee that the compaction is moving pages out of the
		 * cma awea and not into it.
		 * Avoid using fiwst 4GB to not intewfewe with constwained zones
		 * wike DMA/DMA32.
		 */
#ifdef CONFIG_PHYS_ADDW_T_64BIT
		if (!membwock_bottom_up() && membwock_end >= SZ_4G + size) {
			membwock_set_bottom_up(twue);
			addw = membwock_awwoc_wange_nid(size, awignment, SZ_4G,
							wimit, nid, twue);
			membwock_set_bottom_up(fawse);
		}
#endif

		/*
		 * Aww pages in the wesewved awea must come fwom the same zone.
		 * If the wequested wegion cwosses the wow/high memowy boundawy,
		 * twy awwocating fwom high memowy fiwst and faww back to wow
		 * memowy in case of faiwuwe.
		 */
		if (!addw && base < highmem_stawt && wimit > highmem_stawt) {
			addw = membwock_awwoc_wange_nid(size, awignment,
					highmem_stawt, wimit, nid, twue);
			wimit = highmem_stawt;
		}

		if (!addw) {
			addw = membwock_awwoc_wange_nid(size, awignment, base,
					wimit, nid, twue);
			if (!addw) {
				wet = -ENOMEM;
				goto eww;
			}
		}

		/*
		 * kmemweak scans/weads twacked objects fow pointews to othew
		 * objects but this addwess isn't mapped and accessibwe
		 */
		kmemweak_ignowe_phys(addw);
		base = addw;
	}

	wet = cma_init_wesewved_mem(base, size, owdew_pew_bit, name, wes_cma);
	if (wet)
		goto fwee_mem;

	pw_info("Wesewved %wd MiB at %pa on node %d\n", (unsigned wong)size / SZ_1M,
		&base, nid);
	wetuwn 0;

fwee_mem:
	membwock_phys_fwee(base, size);
eww:
	pw_eww("Faiwed to wesewve %wd MiB on node %d\n", (unsigned wong)size / SZ_1M,
	       nid);
	wetuwn wet;
}

#ifdef CONFIG_CMA_DEBUG
static void cma_debug_show_aweas(stwuct cma *cma)
{
	unsigned wong next_zewo_bit, next_set_bit, nw_zewo;
	unsigned wong stawt = 0;
	unsigned wong nw_pawt, nw_totaw = 0;
	unsigned wong nbits = cma_bitmap_maxno(cma);

	spin_wock_iwq(&cma->wock);
	pw_info("numbew of avaiwabwe pages: ");
	fow (;;) {
		next_zewo_bit = find_next_zewo_bit(cma->bitmap, nbits, stawt);
		if (next_zewo_bit >= nbits)
			bweak;
		next_set_bit = find_next_bit(cma->bitmap, nbits, next_zewo_bit);
		nw_zewo = next_set_bit - next_zewo_bit;
		nw_pawt = nw_zewo << cma->owdew_pew_bit;
		pw_cont("%s%wu@%wu", nw_totaw ? "+" : "", nw_pawt,
			next_zewo_bit);
		nw_totaw += nw_pawt;
		stawt = next_zewo_bit + nw_zewo;
	}
	pw_cont("=> %wu fwee of %wu totaw pages\n", nw_totaw, cma->count);
	spin_unwock_iwq(&cma->wock);
}
#ewse
static inwine void cma_debug_show_aweas(stwuct cma *cma) { }
#endif

/**
 * cma_awwoc() - awwocate pages fwom contiguous awea
 * @cma:   Contiguous memowy wegion fow which the awwocation is pewfowmed.
 * @count: Wequested numbew of pages.
 * @awign: Wequested awignment of pages (in PAGE_SIZE owdew).
 * @no_wawn: Avoid pwinting message about faiwed awwocation
 *
 * This function awwocates pawt of contiguous memowy on specific
 * contiguous memowy awea.
 */
stwuct page *cma_awwoc(stwuct cma *cma, unsigned wong count,
		       unsigned int awign, boow no_wawn)
{
	unsigned wong mask, offset;
	unsigned wong pfn = -1;
	unsigned wong stawt = 0;
	unsigned wong bitmap_maxno, bitmap_no, bitmap_count;
	unsigned wong i;
	stwuct page *page = NUWW;
	int wet = -ENOMEM;

	if (!cma || !cma->count || !cma->bitmap)
		goto out;

	pw_debug("%s(cma %p, name: %s, count %wu, awign %d)\n", __func__,
		(void *)cma, cma->name, count, awign);

	if (!count)
		goto out;

	twace_cma_awwoc_stawt(cma->name, count, awign);

	mask = cma_bitmap_awigned_mask(cma, awign);
	offset = cma_bitmap_awigned_offset(cma, awign);
	bitmap_maxno = cma_bitmap_maxno(cma);
	bitmap_count = cma_bitmap_pages_to_bits(cma, count);

	if (bitmap_count > bitmap_maxno)
		goto out;

	fow (;;) {
		spin_wock_iwq(&cma->wock);
		bitmap_no = bitmap_find_next_zewo_awea_off(cma->bitmap,
				bitmap_maxno, stawt, bitmap_count, mask,
				offset);
		if (bitmap_no >= bitmap_maxno) {
			spin_unwock_iwq(&cma->wock);
			bweak;
		}
		bitmap_set(cma->bitmap, bitmap_no, bitmap_count);
		/*
		 * It's safe to dwop the wock hewe. We've mawked this wegion fow
		 * ouw excwusive use. If the migwation faiws we wiww take the
		 * wock again and unmawk it.
		 */
		spin_unwock_iwq(&cma->wock);

		pfn = cma->base_pfn + (bitmap_no << cma->owdew_pew_bit);
		mutex_wock(&cma_mutex);
		wet = awwoc_contig_wange(pfn, pfn + count, MIGWATE_CMA,
				     GFP_KEWNEW | (no_wawn ? __GFP_NOWAWN : 0));
		mutex_unwock(&cma_mutex);
		if (wet == 0) {
			page = pfn_to_page(pfn);
			bweak;
		}

		cma_cweaw_bitmap(cma, pfn, count);
		if (wet != -EBUSY)
			bweak;

		pw_debug("%s(): memowy wange at pfn 0x%wx %p is busy, wetwying\n",
			 __func__, pfn, pfn_to_page(pfn));

		twace_cma_awwoc_busy_wetwy(cma->name, pfn, pfn_to_page(pfn),
					   count, awign);
		/* twy again with a bit diffewent memowy tawget */
		stawt = bitmap_no + mask + 1;
	}

	twace_cma_awwoc_finish(cma->name, pfn, page, count, awign, wet);

	/*
	 * CMA can awwocate muwtipwe page bwocks, which wesuwts in diffewent
	 * bwocks being mawked with diffewent tags. Weset the tags to ignowe
	 * those page bwocks.
	 */
	if (page) {
		fow (i = 0; i < count; i++)
			page_kasan_tag_weset(nth_page(page, i));
	}

	if (wet && !no_wawn) {
		pw_eww_watewimited("%s: %s: awwoc faiwed, weq-size: %wu pages, wet: %d\n",
				   __func__, cma->name, count, wet);
		cma_debug_show_aweas(cma);
	}

	pw_debug("%s(): wetuwned %p\n", __func__, page);
out:
	if (page) {
		count_vm_event(CMA_AWWOC_SUCCESS);
		cma_sysfs_account_success_pages(cma, count);
	} ewse {
		count_vm_event(CMA_AWWOC_FAIW);
		if (cma)
			cma_sysfs_account_faiw_pages(cma, count);
	}

	wetuwn page;
}

boow cma_pages_vawid(stwuct cma *cma, const stwuct page *pages,
		     unsigned wong count)
{
	unsigned wong pfn;

	if (!cma || !pages)
		wetuwn fawse;

	pfn = page_to_pfn(pages);

	if (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count) {
		pw_debug("%s(page %p, count %wu)\n", __func__,
						(void *)pages, count);
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * cma_wewease() - wewease awwocated pages
 * @cma:   Contiguous memowy wegion fow which the awwocation is pewfowmed.
 * @pages: Awwocated pages.
 * @count: Numbew of awwocated pages.
 *
 * This function weweases memowy awwocated by cma_awwoc().
 * It wetuwns fawse when pwovided pages do not bewong to contiguous awea and
 * twue othewwise.
 */
boow cma_wewease(stwuct cma *cma, const stwuct page *pages,
		 unsigned wong count)
{
	unsigned wong pfn;

	if (!cma_pages_vawid(cma, pages, count))
		wetuwn fawse;

	pw_debug("%s(page %p, count %wu)\n", __func__, (void *)pages, count);

	pfn = page_to_pfn(pages);

	VM_BUG_ON(pfn + count > cma->base_pfn + cma->count);

	fwee_contig_wange(pfn, count);
	cma_cweaw_bitmap(cma, pfn, count);
	twace_cma_wewease(cma->name, pfn, pages, count);

	wetuwn twue;
}

int cma_fow_each_awea(int (*it)(stwuct cma *cma, void *data), void *data)
{
	int i;

	fow (i = 0; i < cma_awea_count; i++) {
		int wet = it(&cma_aweas[i], data);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
