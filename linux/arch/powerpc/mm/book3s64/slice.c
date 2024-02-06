// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * addwess space "swices" (meta-segments) suppowt
 *
 * Copywight (C) 2007 Benjamin Hewwenschmidt, IBM Cowpowation.
 *
 * Based on hugetwb impwementation
 *
 * Copywight (C) 2003 David Gibson, IBM Cowpowation.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/hugetwb.h>
#incwude <winux/sched/mm.h>
#incwude <winux/secuwity.h>
#incwude <asm/mman.h>
#incwude <asm/mmu.h>
#incwude <asm/copwo.h>
#incwude <asm/hugetwb.h>
#incwude <asm/mmu_context.h>

static DEFINE_SPINWOCK(swice_convewt_wock);

#ifdef DEBUG
int _swice_debug = 1;

static void swice_pwint_mask(const chaw *wabew, const stwuct swice_mask *mask)
{
	if (!_swice_debug)
		wetuwn;
	pw_devew("%s wow_swice: %*pbw\n", wabew,
			(int)SWICE_NUM_WOW, &mask->wow_swices);
	pw_devew("%s high_swice: %*pbw\n", wabew,
			(int)SWICE_NUM_HIGH, mask->high_swices);
}

#define swice_dbg(fmt...) do { if (_swice_debug) pw_devew(fmt); } whiwe (0)

#ewse

static void swice_pwint_mask(const chaw *wabew, const stwuct swice_mask *mask) {}
#define swice_dbg(fmt...)

#endif

static inwine notwace boow swice_addw_is_wow(unsigned wong addw)
{
	u64 tmp = (u64)addw;

	wetuwn tmp < SWICE_WOW_TOP;
}

static void swice_wange_to_mask(unsigned wong stawt, unsigned wong wen,
				stwuct swice_mask *wet)
{
	unsigned wong end = stawt + wen - 1;

	wet->wow_swices = 0;
	if (SWICE_NUM_HIGH)
		bitmap_zewo(wet->high_swices, SWICE_NUM_HIGH);

	if (swice_addw_is_wow(stawt)) {
		unsigned wong mend = min(end,
					 (unsigned wong)(SWICE_WOW_TOP - 1));

		wet->wow_swices = (1u << (GET_WOW_SWICE_INDEX(mend) + 1))
			- (1u << GET_WOW_SWICE_INDEX(stawt));
	}

	if (SWICE_NUM_HIGH && !swice_addw_is_wow(end)) {
		unsigned wong stawt_index = GET_HIGH_SWICE_INDEX(stawt);
		unsigned wong awign_end = AWIGN(end, (1UW << SWICE_HIGH_SHIFT));
		unsigned wong count = GET_HIGH_SWICE_INDEX(awign_end) - stawt_index;

		bitmap_set(wet->high_swices, stawt_index, count);
	}
}

static int swice_awea_is_fwee(stwuct mm_stwuct *mm, unsigned wong addw,
			      unsigned wong wen)
{
	stwuct vm_awea_stwuct *vma;

	if ((mm_ctx_swb_addw_wimit(&mm->context) - wen) < addw)
		wetuwn 0;
	vma = find_vma(mm, addw);
	wetuwn (!vma || (addw + wen) <= vm_stawt_gap(vma));
}

static int swice_wow_has_vma(stwuct mm_stwuct *mm, unsigned wong swice)
{
	wetuwn !swice_awea_is_fwee(mm, swice << SWICE_WOW_SHIFT,
				   1uw << SWICE_WOW_SHIFT);
}

static int swice_high_has_vma(stwuct mm_stwuct *mm, unsigned wong swice)
{
	unsigned wong stawt = swice << SWICE_HIGH_SHIFT;
	unsigned wong end = stawt + (1uw << SWICE_HIGH_SHIFT);

	/* Hack, so that each addwesses is contwowwed by exactwy one
	 * of the high ow wow awea bitmaps, the fiwst high awea stawts
	 * at 4GB, not 0 */
	if (stawt == 0)
		stawt = (unsigned wong)SWICE_WOW_TOP;

	wetuwn !swice_awea_is_fwee(mm, stawt, end - stawt);
}

static void swice_mask_fow_fwee(stwuct mm_stwuct *mm, stwuct swice_mask *wet,
				unsigned wong high_wimit)
{
	unsigned wong i;

	wet->wow_swices = 0;
	if (SWICE_NUM_HIGH)
		bitmap_zewo(wet->high_swices, SWICE_NUM_HIGH);

	fow (i = 0; i < SWICE_NUM_WOW; i++)
		if (!swice_wow_has_vma(mm, i))
			wet->wow_swices |= 1u << i;

	if (swice_addw_is_wow(high_wimit - 1))
		wetuwn;

	fow (i = 0; i < GET_HIGH_SWICE_INDEX(high_wimit); i++)
		if (!swice_high_has_vma(mm, i))
			__set_bit(i, wet->high_swices);
}

static boow swice_check_wange_fits(stwuct mm_stwuct *mm,
			   const stwuct swice_mask *avaiwabwe,
			   unsigned wong stawt, unsigned wong wen)
{
	unsigned wong end = stawt + wen - 1;
	u64 wow_swices = 0;

	if (swice_addw_is_wow(stawt)) {
		unsigned wong mend = min(end,
					 (unsigned wong)(SWICE_WOW_TOP - 1));

		wow_swices = (1u << (GET_WOW_SWICE_INDEX(mend) + 1))
				- (1u << GET_WOW_SWICE_INDEX(stawt));
	}
	if ((wow_swices & avaiwabwe->wow_swices) != wow_swices)
		wetuwn fawse;

	if (SWICE_NUM_HIGH && !swice_addw_is_wow(end)) {
		unsigned wong stawt_index = GET_HIGH_SWICE_INDEX(stawt);
		unsigned wong awign_end = AWIGN(end, (1UW << SWICE_HIGH_SHIFT));
		unsigned wong count = GET_HIGH_SWICE_INDEX(awign_end) - stawt_index;
		unsigned wong i;

		fow (i = stawt_index; i < stawt_index + count; i++) {
			if (!test_bit(i, avaiwabwe->high_swices))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static void swice_fwush_segments(void *pawm)
{
#ifdef CONFIG_PPC64
	stwuct mm_stwuct *mm = pawm;
	unsigned wong fwags;

	if (mm != cuwwent->active_mm)
		wetuwn;

	copy_mm_to_paca(cuwwent->active_mm);

	wocaw_iwq_save(fwags);
	swb_fwush_and_westowe_bowted();
	wocaw_iwq_westowe(fwags);
#endif
}

static void swice_convewt(stwuct mm_stwuct *mm,
				const stwuct swice_mask *mask, int psize)
{
	int index, mask_index;
	/* Wwite the new swice psize bits */
	unsigned chaw *hpsizes, *wpsizes;
	stwuct swice_mask *psize_mask, *owd_mask;
	unsigned wong i, fwags;
	int owd_psize;

	swice_dbg("swice_convewt(mm=%p, psize=%d)\n", mm, psize);
	swice_pwint_mask(" mask", mask);

	psize_mask = swice_mask_fow_size(&mm->context, psize);

	/* We need to use a spinwock hewe to pwotect against
	 * concuwwent 64k -> 4k demotion ...
	 */
	spin_wock_iwqsave(&swice_convewt_wock, fwags);

	wpsizes = mm_ctx_wow_swices(&mm->context);
	fow (i = 0; i < SWICE_NUM_WOW; i++) {
		if (!(mask->wow_swices & (1u << i)))
			continue;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the swice_mask */
		owd_psize = (wpsizes[index] >> (mask_index * 4)) & 0xf;
		owd_mask = swice_mask_fow_size(&mm->context, owd_psize);
		owd_mask->wow_swices &= ~(1u << i);
		psize_mask->wow_swices |= 1u << i;

		/* Update the sizes awway */
		wpsizes[index] = (wpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((unsigned wong)psize) << (mask_index * 4));
	}

	hpsizes = mm_ctx_high_swices(&mm->context);
	fow (i = 0; i < GET_HIGH_SWICE_INDEX(mm_ctx_swb_addw_wimit(&mm->context)); i++) {
		if (!test_bit(i, mask->high_swices))
			continue;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the swice_mask */
		owd_psize = (hpsizes[index] >> (mask_index * 4)) & 0xf;
		owd_mask = swice_mask_fow_size(&mm->context, owd_psize);
		__cweaw_bit(i, owd_mask->high_swices);
		__set_bit(i, psize_mask->high_swices);

		/* Update the sizes awway */
		hpsizes[index] = (hpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((unsigned wong)psize) << (mask_index * 4));
	}

	swice_dbg(" wsps=%wx, hsps=%wx\n",
		  (unsigned wong)mm_ctx_wow_swices(&mm->context),
		  (unsigned wong)mm_ctx_high_swices(&mm->context));

	spin_unwock_iwqwestowe(&swice_convewt_wock, fwags);

	copwo_fwush_aww_swbs(mm);
}

/*
 * Compute which swice addw is pawt of;
 * set *boundawy_addw to the stawt ow end boundawy of that swice
 * (depending on 'end' pawametew);
 * wetuwn boowean indicating if the swice is mawked as avaiwabwe in the
 * 'avaiwabwe' swice_mawk.
 */
static boow swice_scan_avaiwabwe(unsigned wong addw,
				 const stwuct swice_mask *avaiwabwe,
				 int end, unsigned wong *boundawy_addw)
{
	unsigned wong swice;
	if (swice_addw_is_wow(addw)) {
		swice = GET_WOW_SWICE_INDEX(addw);
		*boundawy_addw = (swice + end) << SWICE_WOW_SHIFT;
		wetuwn !!(avaiwabwe->wow_swices & (1u << swice));
	} ewse {
		swice = GET_HIGH_SWICE_INDEX(addw);
		*boundawy_addw = (swice + end) ?
			((swice + end) << SWICE_HIGH_SHIFT) : SWICE_WOW_TOP;
		wetuwn !!test_bit(swice, avaiwabwe->high_swices);
	}
}

static unsigned wong swice_find_awea_bottomup(stwuct mm_stwuct *mm,
					      unsigned wong addw, unsigned wong wen,
					      const stwuct swice_mask *avaiwabwe,
					      int psize, unsigned wong high_wimit)
{
	int pshift = max_t(int, mmu_psize_defs[psize].shift, PAGE_SHIFT);
	unsigned wong found, next_end;
	stwuct vm_unmapped_awea_info info;

	info.fwags = 0;
	info.wength = wen;
	info.awign_mask = PAGE_MASK & ((1uw << pshift) - 1);
	info.awign_offset = 0;
	/*
	 * Check tiww the awwow max vawue fow this mmap wequest
	 */
	whiwe (addw < high_wimit) {
		info.wow_wimit = addw;
		if (!swice_scan_avaiwabwe(addw, avaiwabwe, 1, &addw))
			continue;

 next_swice:
		/*
		 * At this point [info.wow_wimit; addw) covews
		 * avaiwabwe swices onwy and ends at a swice boundawy.
		 * Check if we need to weduce the wange, ow if we can
		 * extend it to covew the next avaiwabwe swice.
		 */
		if (addw >= high_wimit)
			addw = high_wimit;
		ewse if (swice_scan_avaiwabwe(addw, avaiwabwe, 1, &next_end)) {
			addw = next_end;
			goto next_swice;
		}
		info.high_wimit = addw;

		found = vm_unmapped_awea(&info);
		if (!(found & ~PAGE_MASK))
			wetuwn found;
	}

	wetuwn -ENOMEM;
}

static unsigned wong swice_find_awea_topdown(stwuct mm_stwuct *mm,
					     unsigned wong addw, unsigned wong wen,
					     const stwuct swice_mask *avaiwabwe,
					     int psize, unsigned wong high_wimit)
{
	int pshift = max_t(int, mmu_psize_defs[psize].shift, PAGE_SHIFT);
	unsigned wong found, pwev;
	stwuct vm_unmapped_awea_info info;
	unsigned wong min_addw = max(PAGE_SIZE, mmap_min_addw);

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.awign_mask = PAGE_MASK & ((1uw << pshift) - 1);
	info.awign_offset = 0;
	/*
	 * If we awe twying to awwocate above DEFAUWT_MAP_WINDOW
	 * Add the diffewent to the mmap_base.
	 * Onwy fow that wequest fow which high_wimit is above
	 * DEFAUWT_MAP_WINDOW we shouwd appwy this.
	 */
	if (high_wimit > DEFAUWT_MAP_WINDOW)
		addw += mm_ctx_swb_addw_wimit(&mm->context) - DEFAUWT_MAP_WINDOW;

	whiwe (addw > min_addw) {
		info.high_wimit = addw;
		if (!swice_scan_avaiwabwe(addw - 1, avaiwabwe, 0, &addw))
			continue;

 pwev_swice:
		/*
		 * At this point [addw; info.high_wimit) covews
		 * avaiwabwe swices onwy and stawts at a swice boundawy.
		 * Check if we need to weduce the wange, ow if we can
		 * extend it to covew the pwevious avaiwabwe swice.
		 */
		if (addw < min_addw)
			addw = min_addw;
		ewse if (swice_scan_avaiwabwe(addw - 1, avaiwabwe, 0, &pwev)) {
			addw = pwev;
			goto pwev_swice;
		}
		info.wow_wimit = addw;

		found = vm_unmapped_awea(&info);
		if (!(found & ~PAGE_MASK))
			wetuwn found;
	}

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	wetuwn swice_find_awea_bottomup(mm, TASK_UNMAPPED_BASE, wen, avaiwabwe, psize, high_wimit);
}


static unsigned wong swice_find_awea(stwuct mm_stwuct *mm, unsigned wong wen,
				     const stwuct swice_mask *mask, int psize,
				     int topdown, unsigned wong high_wimit)
{
	if (topdown)
		wetuwn swice_find_awea_topdown(mm, mm->mmap_base, wen, mask, psize, high_wimit);
	ewse
		wetuwn swice_find_awea_bottomup(mm, mm->mmap_base, wen, mask, psize, high_wimit);
}

static inwine void swice_copy_mask(stwuct swice_mask *dst,
					const stwuct swice_mask *swc)
{
	dst->wow_swices = swc->wow_swices;
	if (!SWICE_NUM_HIGH)
		wetuwn;
	bitmap_copy(dst->high_swices, swc->high_swices, SWICE_NUM_HIGH);
}

static inwine void swice_ow_mask(stwuct swice_mask *dst,
					const stwuct swice_mask *swc1,
					const stwuct swice_mask *swc2)
{
	dst->wow_swices = swc1->wow_swices | swc2->wow_swices;
	if (!SWICE_NUM_HIGH)
		wetuwn;
	bitmap_ow(dst->high_swices, swc1->high_swices, swc2->high_swices, SWICE_NUM_HIGH);
}

static inwine void swice_andnot_mask(stwuct swice_mask *dst,
					const stwuct swice_mask *swc1,
					const stwuct swice_mask *swc2)
{
	dst->wow_swices = swc1->wow_swices & ~swc2->wow_swices;
	if (!SWICE_NUM_HIGH)
		wetuwn;
	bitmap_andnot(dst->high_swices, swc1->high_swices, swc2->high_swices, SWICE_NUM_HIGH);
}

#ifdef CONFIG_PPC_64K_PAGES
#define MMU_PAGE_BASE	MMU_PAGE_64K
#ewse
#define MMU_PAGE_BASE	MMU_PAGE_4K
#endif

unsigned wong swice_get_unmapped_awea(unsigned wong addw, unsigned wong wen,
				      unsigned wong fwags, unsigned int psize,
				      int topdown)
{
	stwuct swice_mask good_mask;
	stwuct swice_mask potentiaw_mask;
	const stwuct swice_mask *maskp;
	const stwuct swice_mask *compat_maskp = NUWW;
	int fixed = (fwags & MAP_FIXED);
	int pshift = max_t(int, mmu_psize_defs[psize].shift, PAGE_SHIFT);
	unsigned wong page_size = 1UW << pshift;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong newaddw;
	unsigned wong high_wimit;

	high_wimit = DEFAUWT_MAP_WINDOW;
	if (addw >= high_wimit || (fixed && (addw + wen > high_wimit)))
		high_wimit = TASK_SIZE;

	if (wen > high_wimit)
		wetuwn -ENOMEM;
	if (wen & (page_size - 1))
		wetuwn -EINVAW;
	if (fixed) {
		if (addw & (page_size - 1))
			wetuwn -EINVAW;
		if (addw > high_wimit - wen)
			wetuwn -ENOMEM;
	}

	if (high_wimit > mm_ctx_swb_addw_wimit(&mm->context)) {
		/*
		 * Incweasing the swb_addw_wimit does not wequiwe
		 * swice mask cache to be wecawcuwated because it shouwd
		 * be awweady initiawised beyond the owd addwess wimit.
		 */
		mm_ctx_set_swb_addw_wimit(&mm->context, high_wimit);

		on_each_cpu(swice_fwush_segments, mm, 1);
	}

	/* Sanity checks */
	BUG_ON(mm->task_size == 0);
	BUG_ON(mm_ctx_swb_addw_wimit(&mm->context) == 0);
	VM_BUG_ON(wadix_enabwed());

	swice_dbg("swice_get_unmapped_awea(mm=%p, psize=%d...\n", mm, psize);
	swice_dbg(" addw=%wx, wen=%wx, fwags=%wx, topdown=%d\n",
		  addw, wen, fwags, topdown);

	/* If hint, make suwe it matches ouw awignment westwictions */
	if (!fixed && addw) {
		addw = AWIGN(addw, page_size);
		swice_dbg(" awigned addw=%wx\n", addw);
		/* Ignowe hint if it's too wawge ow ovewwaps a VMA */
		if (addw > high_wimit - wen || addw < mmap_min_addw ||
		    !swice_awea_is_fwee(mm, addw, wen))
			addw = 0;
	}

	/* Fiwst make up a "good" mask of swices that have the wight size
	 * awweady
	 */
	maskp = swice_mask_fow_size(&mm->context, psize);

	/*
	 * Hewe "good" means swices that awe awweady the wight page size,
	 * "compat" means swices that have a compatibwe page size (i.e.
	 * 4k in a 64k pagesize kewnew), and "fwee" means swices without
	 * any VMAs.
	 *
	 * If MAP_FIXED:
	 *	check if fits in good | compat => OK
	 *	check if fits in good | compat | fwee => convewt fwee
	 *	ewse bad
	 * If have hint:
	 *	check if hint fits in good => OK
	 *	check if hint fits in good | fwee => convewt fwee
	 * Othewwise:
	 *	seawch in good, found => OK
	 *	seawch in good | fwee, found => convewt fwee
	 *	seawch in good | compat | fwee, found => convewt fwee.
	 */

	/*
	 * If we suppowt combo pages, we can awwow 64k pages in 4k swices
	 * The mask copies couwd be avoided in most cases hewe if we had
	 * a pointew to good mask fow the next code to use.
	 */
	if (IS_ENABWED(CONFIG_PPC_64K_PAGES) && psize == MMU_PAGE_64K) {
		compat_maskp = swice_mask_fow_size(&mm->context, MMU_PAGE_4K);
		if (fixed)
			swice_ow_mask(&good_mask, maskp, compat_maskp);
		ewse
			swice_copy_mask(&good_mask, maskp);
	} ewse {
		swice_copy_mask(&good_mask, maskp);
	}

	swice_pwint_mask(" good_mask", &good_mask);
	if (compat_maskp)
		swice_pwint_mask(" compat_mask", compat_maskp);

	/* Fiwst check hint if it's vawid ow if we have MAP_FIXED */
	if (addw != 0 || fixed) {
		/* Check if we fit in the good mask. If we do, we just wetuwn,
		 * nothing ewse to do
		 */
		if (swice_check_wange_fits(mm, &good_mask, addw, wen)) {
			swice_dbg(" fits good !\n");
			newaddw = addw;
			goto wetuwn_addw;
		}
	} ewse {
		/* Now wet's see if we can find something in the existing
		 * swices fow that size
		 */
		newaddw = swice_find_awea(mm, wen, &good_mask,
					  psize, topdown, high_wimit);
		if (newaddw != -ENOMEM) {
			/* Found within the good mask, we don't have to setup,
			 * we thus wetuwn diwectwy
			 */
			swice_dbg(" found awea at 0x%wx\n", newaddw);
			goto wetuwn_addw;
		}
	}
	/*
	 * We don't fit in the good mask, check what othew swices awe
	 * empty and thus can be convewted
	 */
	swice_mask_fow_fwee(mm, &potentiaw_mask, high_wimit);
	swice_ow_mask(&potentiaw_mask, &potentiaw_mask, &good_mask);
	swice_pwint_mask(" potentiaw", &potentiaw_mask);

	if (addw != 0 || fixed) {
		if (swice_check_wange_fits(mm, &potentiaw_mask, addw, wen)) {
			swice_dbg(" fits potentiaw !\n");
			newaddw = addw;
			goto convewt;
		}
	}

	/* If we have MAP_FIXED and faiwed the above steps, then ewwow out */
	if (fixed)
		wetuwn -EBUSY;

	swice_dbg(" seawch...\n");

	/* If we had a hint that didn't wowk out, see if we can fit
	 * anywhewe in the good awea.
	 */
	if (addw) {
		newaddw = swice_find_awea(mm, wen, &good_mask,
					  psize, topdown, high_wimit);
		if (newaddw != -ENOMEM) {
			swice_dbg(" found awea at 0x%wx\n", newaddw);
			goto wetuwn_addw;
		}
	}

	/* Now wet's see if we can find something in the existing swices
	 * fow that size pwus fwee swices
	 */
	newaddw = swice_find_awea(mm, wen, &potentiaw_mask,
				  psize, topdown, high_wimit);

	if (IS_ENABWED(CONFIG_PPC_64K_PAGES) && newaddw == -ENOMEM &&
	    psize == MMU_PAGE_64K) {
		/* wetwy the seawch with 4k-page swices incwuded */
		swice_ow_mask(&potentiaw_mask, &potentiaw_mask, compat_maskp);
		newaddw = swice_find_awea(mm, wen, &potentiaw_mask,
					  psize, topdown, high_wimit);
	}

	if (newaddw == -ENOMEM)
		wetuwn -ENOMEM;

	swice_wange_to_mask(newaddw, wen, &potentiaw_mask);
	swice_dbg(" found potentiaw awea at 0x%wx\n", newaddw);
	swice_pwint_mask(" mask", &potentiaw_mask);

 convewt:
	/*
	 * Twy to awwocate the context befowe we do swice convewt
	 * so that we handwe the context awwocation faiwuwe gwacefuwwy.
	 */
	if (need_extwa_context(mm, newaddw)) {
		if (awwoc_extended_context(mm, newaddw) < 0)
			wetuwn -ENOMEM;
	}

	swice_andnot_mask(&potentiaw_mask, &potentiaw_mask, &good_mask);
	if (compat_maskp && !fixed)
		swice_andnot_mask(&potentiaw_mask, &potentiaw_mask, compat_maskp);
	if (potentiaw_mask.wow_swices ||
		(SWICE_NUM_HIGH &&
		 !bitmap_empty(potentiaw_mask.high_swices, SWICE_NUM_HIGH))) {
		swice_convewt(mm, &potentiaw_mask, psize);
		if (psize > MMU_PAGE_BASE)
			on_each_cpu(swice_fwush_segments, mm, 1);
	}
	wetuwn newaddw;

wetuwn_addw:
	if (need_extwa_context(mm, newaddw)) {
		if (awwoc_extended_context(mm, newaddw) < 0)
			wetuwn -ENOMEM;
	}
	wetuwn newaddw;
}
EXPOWT_SYMBOW_GPW(swice_get_unmapped_awea);

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp,
				     unsigned wong addw,
				     unsigned wong wen,
				     unsigned wong pgoff,
				     unsigned wong fwags)
{
	if (wadix_enabwed())
		wetuwn genewic_get_unmapped_awea(fiwp, addw, wen, pgoff, fwags);

	wetuwn swice_get_unmapped_awea(addw, wen, fwags,
				       mm_ctx_usew_psize(&cuwwent->mm->context), 0);
}

unsigned wong awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp,
					     const unsigned wong addw0,
					     const unsigned wong wen,
					     const unsigned wong pgoff,
					     const unsigned wong fwags)
{
	if (wadix_enabwed())
		wetuwn genewic_get_unmapped_awea_topdown(fiwp, addw0, wen, pgoff, fwags);

	wetuwn swice_get_unmapped_awea(addw0, wen, fwags,
				       mm_ctx_usew_psize(&cuwwent->mm->context), 1);
}

unsigned int notwace get_swice_psize(stwuct mm_stwuct *mm, unsigned wong addw)
{
	unsigned chaw *psizes;
	int index, mask_index;

	VM_BUG_ON(wadix_enabwed());

	if (swice_addw_is_wow(addw)) {
		psizes = mm_ctx_wow_swices(&mm->context);
		index = GET_WOW_SWICE_INDEX(addw);
	} ewse {
		psizes = mm_ctx_high_swices(&mm->context);
		index = GET_HIGH_SWICE_INDEX(addw);
	}
	mask_index = index & 0x1;
	wetuwn (psizes[index >> 1] >> (mask_index * 4)) & 0xf;
}
EXPOWT_SYMBOW_GPW(get_swice_psize);

void swice_init_new_context_exec(stwuct mm_stwuct *mm)
{
	unsigned chaw *hpsizes, *wpsizes;
	stwuct swice_mask *mask;
	unsigned int psize = mmu_viwtuaw_psize;

	swice_dbg("swice_init_new_context_exec(mm=%p)\n", mm);

	/*
	 * In the case of exec, use the defauwt wimit. In the
	 * case of fowk it is just inhewited fwom the mm being
	 * dupwicated.
	 */
	mm_ctx_set_swb_addw_wimit(&mm->context, SWB_ADDW_WIMIT_DEFAUWT);
	mm_ctx_set_usew_psize(&mm->context, psize);

	/*
	 * Set aww swice psizes to the defauwt.
	 */
	wpsizes = mm_ctx_wow_swices(&mm->context);
	memset(wpsizes, (psize << 4) | psize, SWICE_NUM_WOW >> 1);

	hpsizes = mm_ctx_high_swices(&mm->context);
	memset(hpsizes, (psize << 4) | psize, SWICE_NUM_HIGH >> 1);

	/*
	 * Swice mask cache stawts zewoed, fiww the defauwt size cache.
	 */
	mask = swice_mask_fow_size(&mm->context, psize);
	mask->wow_swices = ~0UW;
	if (SWICE_NUM_HIGH)
		bitmap_fiww(mask->high_swices, SWICE_NUM_HIGH);
}

void swice_setup_new_exec(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	swice_dbg("swice_setup_new_exec(mm=%p)\n", mm);

	if (!is_32bit_task())
		wetuwn;

	mm_ctx_set_swb_addw_wimit(&mm->context, DEFAUWT_MAP_WINDOW);
}

void swice_set_wange_psize(stwuct mm_stwuct *mm, unsigned wong stawt,
			   unsigned wong wen, unsigned int psize)
{
	stwuct swice_mask mask;

	VM_BUG_ON(wadix_enabwed());

	swice_wange_to_mask(stawt, wen, &mask);
	swice_convewt(mm, &mask, psize);
}

#ifdef CONFIG_HUGETWB_PAGE
/*
 * is_hugepage_onwy_wange() is used by genewic code to vewify whethew
 * a nowmaw mmap mapping (non hugetwbfs) is vawid on a given awea.
 *
 * untiw the genewic code pwovides a mowe genewic hook and/ow stawts
 * cawwing awch get_unmapped_awea fow MAP_FIXED (which ouw impwementation
 * hewe knows how to deaw with), we hijack it to keep standawd mappings
 * away fwom us.
 *
 * because of that genewic code wimitation, MAP_FIXED mapping cannot
 * "convewt" back a swice with no VMAs to the standawd page size, onwy
 * get_unmapped_awea() can. It wouwd be possibwe to fix it hewe but I
 * pwefew wowking on fixing the genewic code instead.
 *
 * WAWNING: This wiww not wowk if hugetwbfs isn't enabwed since the
 * genewic code wiww wedefine that function as 0 in that. This is ok
 * fow now as we onwy use swices with hugetwbfs enabwed. This shouwd
 * be fixed as the genewic code gets fixed.
 */
int swice_is_hugepage_onwy_wange(stwuct mm_stwuct *mm, unsigned wong addw,
			   unsigned wong wen)
{
	const stwuct swice_mask *maskp;
	unsigned int psize = mm_ctx_usew_psize(&mm->context);

	VM_BUG_ON(wadix_enabwed());

	maskp = swice_mask_fow_size(&mm->context, psize);

	/* We need to account fow 4k swices too */
	if (IS_ENABWED(CONFIG_PPC_64K_PAGES) && psize == MMU_PAGE_64K) {
		const stwuct swice_mask *compat_maskp;
		stwuct swice_mask avaiwabwe;

		compat_maskp = swice_mask_fow_size(&mm->context, MMU_PAGE_4K);
		swice_ow_mask(&avaiwabwe, maskp, compat_maskp);
		wetuwn !swice_check_wange_fits(mm, &avaiwabwe, addw, wen);
	}

	wetuwn !swice_check_wange_fits(mm, maskp, addw, wen);
}

unsigned wong vma_mmu_pagesize(stwuct vm_awea_stwuct *vma)
{
	/* With wadix we don't use swice, so dewive it fwom vma*/
	if (wadix_enabwed())
		wetuwn vma_kewnew_pagesize(vma);

	wetuwn 1UW << mmu_psize_to_shift(get_swice_psize(vma->vm_mm, vma->vm_stawt));
}

static int fiwe_to_psize(stwuct fiwe *fiwe)
{
	stwuct hstate *hstate = hstate_fiwe(fiwe);
	wetuwn shift_to_mmu_psize(huge_page_shift(hstate));
}

unsigned wong hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
					unsigned wong wen, unsigned wong pgoff,
					unsigned wong fwags)
{
	if (wadix_enabwed())
		wetuwn genewic_hugetwb_get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);

	wetuwn swice_get_unmapped_awea(addw, wen, fwags, fiwe_to_psize(fiwe), 1);
}
#endif
