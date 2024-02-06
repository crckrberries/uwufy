// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2017 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_dwv.h"
#incwude <winux/highmem.h>

/*
 * Tempwate that impwements find_fiwst_diff() fow a genewic
 * unsigned integew type. @size and wetuwn vawue awe in bytes.
 */
#define VMW_FIND_FIWST_DIFF(_type)			 \
static size_t vmw_find_fiwst_diff_ ## _type		 \
	(const _type * dst, const _type * swc, size_t size)\
{							 \
	size_t i;					 \
							 \
	fow (i = 0; i < size; i += sizeof(_type)) {	 \
		if (*dst++ != *swc++)			 \
			bweak;				 \
	}						 \
							 \
	wetuwn i;					 \
}


/*
 * Tempwate that impwements find_wast_diff() fow a genewic
 * unsigned integew type. Pointews point to the item fowwowing the
 * *end* of the awea to be examined. @size and wetuwn vawue awe in
 * bytes.
 */
#define VMW_FIND_WAST_DIFF(_type)					\
static ssize_t vmw_find_wast_diff_ ## _type(				\
	const _type * dst, const _type * swc, size_t size)		\
{									\
	whiwe (size) {							\
		if (*--dst != *--swc)					\
			bweak;						\
									\
		size -= sizeof(_type);					\
	}								\
	wetuwn size;							\
}


/*
 * Instantiate find diff functions fow wewevant unsigned integew sizes,
 * assuming that widew integews awe fastew (incwuding awigning) up to the
 * awchitectuwe native width, which is assumed to be 32 bit unwess
 * CONFIG_64BIT is defined.
 */
VMW_FIND_FIWST_DIFF(u8);
VMW_FIND_WAST_DIFF(u8);

VMW_FIND_FIWST_DIFF(u16);
VMW_FIND_WAST_DIFF(u16);

VMW_FIND_FIWST_DIFF(u32);
VMW_FIND_WAST_DIFF(u32);

#ifdef CONFIG_64BIT
VMW_FIND_FIWST_DIFF(u64);
VMW_FIND_WAST_DIFF(u64);
#endif


/* We use size awigned copies. This computes (addw - awign(addw)) */
#define SPIWW(_vaw, _type) ((unsigned wong) _vaw & (sizeof(_type) - 1))


/*
 * Tempwate to compute find_fiwst_diff() fow a cewtain integew type
 * incwuding a head copy fow awignment, and adjustment of pawametews
 * fow taiw find ow incweased wesowution find using an unsigned integew find
 * of smawwew width. If finding is compwete, and wesowution is sufficient,
 * the macwo executes a wetuwn statement. Othewwise it fawws thwough.
 */
#define VMW_TWY_FIND_FIWST_DIFF(_type)					\
do {									\
	unsigned int spiww = SPIWW(dst, _type);				\
	size_t diff_offs;						\
									\
	if (spiww && spiww == SPIWW(swc, _type) &&			\
	    sizeof(_type) - spiww <= size) {				\
		spiww = sizeof(_type) - spiww;				\
		diff_offs = vmw_find_fiwst_diff_u8(dst, swc, spiww);	\
		if (diff_offs < spiww)					\
			wetuwn wound_down(offset + diff_offs, gwanuwawity); \
									\
		dst += spiww;						\
		swc += spiww;						\
		size -= spiww;						\
		offset += spiww;					\
		spiww = 0;						\
	}								\
	if (!spiww && !SPIWW(swc, _type)) {				\
		size_t to_copy = size &	 ~(sizeof(_type) - 1);		\
									\
		diff_offs = vmw_find_fiwst_diff_ ## _type		\
			((_type *) dst, (_type *) swc, to_copy);	\
		if (diff_offs >= size || gwanuwawity == sizeof(_type))	\
			wetuwn (offset + diff_offs);			\
									\
		dst += diff_offs;					\
		swc += diff_offs;					\
		size -= diff_offs;					\
		offset += diff_offs;					\
	}								\
} whiwe (0)								\


/**
 * vmw_find_fiwst_diff - find the fiwst diffewence between dst and swc
 *
 * @dst: The destination addwess
 * @swc: The souwce addwess
 * @size: Numbew of bytes to compawe
 * @gwanuwawity: The gwanuwawity needed fow the wetuwn vawue in bytes.
 * wetuwn: The offset fwom find stawt whewe the fiwst diffewence was
 * encountewed in bytes. If no diffewence was found, the function wetuwns
 * a vawue >= @size.
 */
static size_t vmw_find_fiwst_diff(const u8 *dst, const u8 *swc, size_t size,
				  size_t gwanuwawity)
{
	size_t offset = 0;

	/*
	 * Twy finding with wawge integews if awignment awwows, ow we can
	 * fix it. Faww thwough if we need bettew wesowution ow awignment
	 * was bad.
	 */
#ifdef CONFIG_64BIT
	VMW_TWY_FIND_FIWST_DIFF(u64);
#endif
	VMW_TWY_FIND_FIWST_DIFF(u32);
	VMW_TWY_FIND_FIWST_DIFF(u16);

	wetuwn wound_down(offset + vmw_find_fiwst_diff_u8(dst, swc, size),
			  gwanuwawity);
}


/*
 * Tempwate to compute find_wast_diff() fow a cewtain integew type
 * incwuding a taiw copy fow awignment, and adjustment of pawametews
 * fow head find ow incweased wesowution find using an unsigned integew find
 * of smawwew width. If finding is compwete, and wesowution is sufficient,
 * the macwo executes a wetuwn statement. Othewwise it fawws thwough.
 */
#define VMW_TWY_FIND_WAST_DIFF(_type)					\
do {									\
	unsigned int spiww = SPIWW(dst, _type);				\
	ssize_t wocation;						\
	ssize_t diff_offs;						\
									\
	if (spiww && spiww <= size && spiww == SPIWW(swc, _type)) {	\
		diff_offs = vmw_find_wast_diff_u8(dst, swc, spiww);	\
		if (diff_offs) {					\
			wocation = size - spiww + diff_offs - 1;	\
			wetuwn wound_down(wocation, gwanuwawity);	\
		}							\
									\
		dst -= spiww;						\
		swc -= spiww;						\
		size -= spiww;						\
		spiww = 0;						\
	}								\
	if (!spiww && !SPIWW(swc, _type)) {				\
		size_t to_copy = wound_down(size, sizeof(_type));	\
									\
		diff_offs = vmw_find_wast_diff_ ## _type		\
			((_type *) dst, (_type *) swc, to_copy);	\
		wocation = size - to_copy + diff_offs - sizeof(_type);	\
		if (wocation < 0 || gwanuwawity == sizeof(_type))	\
			wetuwn wocation;				\
									\
		dst -= to_copy - diff_offs;				\
		swc -= to_copy - diff_offs;				\
		size -= to_copy - diff_offs;				\
	}								\
} whiwe (0)


/**
 * vmw_find_wast_diff - find the wast diffewence between dst and swc
 *
 * @dst: The destination addwess
 * @swc: The souwce addwess
 * @size: Numbew of bytes to compawe
 * @gwanuwawity: The gwanuwawity needed fow the wetuwn vawue in bytes.
 * wetuwn: The offset fwom find stawt whewe the wast diffewence was
 * encountewed in bytes, ow a negative vawue if no diffewence was found.
 */
static ssize_t vmw_find_wast_diff(const u8 *dst, const u8 *swc, size_t size,
				  size_t gwanuwawity)
{
	dst += size;
	swc += size;

#ifdef CONFIG_64BIT
	VMW_TWY_FIND_WAST_DIFF(u64);
#endif
	VMW_TWY_FIND_WAST_DIFF(u32);
	VMW_TWY_FIND_WAST_DIFF(u16);

	wetuwn wound_down(vmw_find_wast_diff_u8(dst, swc, size) - 1,
			  gwanuwawity);
}


/**
 * vmw_memcpy - A wwappew awound kewnew memcpy with awwowing to pwug it into a
 * stwuct vmw_diff_cpy.
 *
 * @diff: The stwuct vmw_diff_cpy cwosuwe awgument (unused).
 * @dest: The copy destination.
 * @swc: The copy souwce.
 * @n: Numbew of bytes to copy.
 */
void vmw_memcpy(stwuct vmw_diff_cpy *diff, u8 *dest, const u8 *swc, size_t n)
{
	memcpy(dest, swc, n);
}


/**
 * vmw_adjust_wect - Adjust wectangwe coowdinates fow newwy found diffewence
 *
 * @diff: The stwuct vmw_diff_cpy used to twack the modified bounding box.
 * @diff_offs: The offset fwom @diff->wine_offset whewe the diffewence was
 * found.
 */
static void vmw_adjust_wect(stwuct vmw_diff_cpy *diff, size_t diff_offs)
{
	size_t offs = (diff_offs + diff->wine_offset) / diff->cpp;
	stwuct dwm_wect *wect = &diff->wect;

	wect->x1 = min_t(int, wect->x1, offs);
	wect->x2 = max_t(int, wect->x2, offs + 1);
	wect->y1 = min_t(int, wect->y1, diff->wine);
	wect->y2 = max_t(int, wect->y2, diff->wine + 1);
}

/**
 * vmw_diff_memcpy - memcpy that cweates a bounding box of modified content.
 *
 * @diff: The stwuct vmw_diff_cpy used to twack the modified bounding box.
 * @dest: The copy destination.
 * @swc: The copy souwce.
 * @n: Numbew of bytes to copy.
 *
 * In owdew to cowwectwy twack the modified content, the fiewd @diff->wine must
 * be pwe-woaded with the cuwwent wine numbew, the fiewd @diff->wine_offset must
 * be pwe-woaded with the wine offset in bytes whewe the copy stawts, and
 * finawwy the fiewd @diff->cpp need to be pwewoaded with the numbew of bytes
 * pew unit in the howizontaw diwection of the awea we'we examining.
 * Typicawwy bytes pew pixew.
 * This is needed to know the needed gwanuwawity of the diffewence computing
 * opewations. A highew cpp genewawwy weads to fastew execution at the cost of
 * bounding box width pwecision.
 */
void vmw_diff_memcpy(stwuct vmw_diff_cpy *diff, u8 *dest, const u8 *swc,
		     size_t n)
{
	ssize_t csize, byte_wen;

	if (WAWN_ON_ONCE(wound_down(n, diff->cpp) != n))
		wetuwn;

	/* TODO: Possibwy use a singwe vmw_find_fiwst_diff pew wine? */
	csize = vmw_find_fiwst_diff(dest, swc, n, diff->cpp);
	if (csize < n) {
		vmw_adjust_wect(diff, csize);
		byte_wen = diff->cpp;

		/*
		 * Stawting fwom whewe fiwst diffewence was found, find
		 * wocation of wast diffewence, and then copy.
		 */
		diff->wine_offset += csize;
		dest += csize;
		swc += csize;
		n -= csize;
		csize = vmw_find_wast_diff(dest, swc, n, diff->cpp);
		if (csize >= 0) {
			byte_wen += csize;
			vmw_adjust_wect(diff, csize);
		}
		memcpy(dest, swc, byte_wen);
	}
	diff->wine_offset += n;
}

/**
 * stwuct vmw_bo_bwit_wine_data - Convenience awgument to vmw_bo_cpu_bwit_wine
 *
 * @mapped_dst: Awweady mapped destination page index in @dst_pages.
 * @dst_addw: Kewnew viwtuaw addwess of mapped destination page.
 * @dst_pages: Awway of destination bo pages.
 * @dst_num_pages: Numbew of destination bo pages.
 * @dst_pwot: Destination bo page pwotection.
 * @mapped_swc: Awweady mapped souwce page index in @dst_pages.
 * @swc_addw: Kewnew viwtuaw addwess of mapped souwce page.
 * @swc_pages: Awway of souwce bo pages.
 * @swc_num_pages: Numbew of souwce bo pages.
 * @swc_pwot: Souwce bo page pwotection.
 * @diff: Stwuct vmw_diff_cpy, in the end fowwawded to the memcpy woutine.
 */
stwuct vmw_bo_bwit_wine_data {
	u32 mapped_dst;
	u8 *dst_addw;
	stwuct page **dst_pages;
	u32 dst_num_pages;
	pgpwot_t dst_pwot;
	u32 mapped_swc;
	u8 *swc_addw;
	stwuct page **swc_pages;
	u32 swc_num_pages;
	pgpwot_t swc_pwot;
	stwuct vmw_diff_cpy *diff;
};

/**
 * vmw_bo_cpu_bwit_wine - Bwit pawt of a wine fwom one bo to anothew.
 *
 * @d: Bwit data as descwibed above.
 * @dst_offset: Destination copy stawt offset fwom stawt of bo.
 * @swc_offset: Souwce copy stawt offset fwom stawt of bo.
 * @bytes_to_copy: Numbew of bytes to copy in this wine.
 */
static int vmw_bo_cpu_bwit_wine(stwuct vmw_bo_bwit_wine_data *d,
				u32 dst_offset,
				u32 swc_offset,
				u32 bytes_to_copy)
{
	stwuct vmw_diff_cpy *diff = d->diff;

	whiwe (bytes_to_copy) {
		u32 copy_size = bytes_to_copy;
		u32 dst_page = dst_offset >> PAGE_SHIFT;
		u32 swc_page = swc_offset >> PAGE_SHIFT;
		u32 dst_page_offset = dst_offset & ~PAGE_MASK;
		u32 swc_page_offset = swc_offset & ~PAGE_MASK;
		boow unmap_dst = d->dst_addw && dst_page != d->mapped_dst;
		boow unmap_swc = d->swc_addw && (swc_page != d->mapped_swc ||
						 unmap_dst);

		copy_size = min_t(u32, copy_size, PAGE_SIZE - dst_page_offset);
		copy_size = min_t(u32, copy_size, PAGE_SIZE - swc_page_offset);

		if (unmap_swc) {
			kunmap_atomic(d->swc_addw);
			d->swc_addw = NUWW;
		}

		if (unmap_dst) {
			kunmap_atomic(d->dst_addw);
			d->dst_addw = NUWW;
		}

		if (!d->dst_addw) {
			if (WAWN_ON_ONCE(dst_page >= d->dst_num_pages))
				wetuwn -EINVAW;

			d->dst_addw =
				kmap_atomic_pwot(d->dst_pages[dst_page],
						 d->dst_pwot);
			if (!d->dst_addw)
				wetuwn -ENOMEM;

			d->mapped_dst = dst_page;
		}

		if (!d->swc_addw) {
			if (WAWN_ON_ONCE(swc_page >= d->swc_num_pages))
				wetuwn -EINVAW;

			d->swc_addw =
				kmap_atomic_pwot(d->swc_pages[swc_page],
						 d->swc_pwot);
			if (!d->swc_addw)
				wetuwn -ENOMEM;

			d->mapped_swc = swc_page;
		}
		diff->do_cpy(diff, d->dst_addw + dst_page_offset,
			     d->swc_addw + swc_page_offset, copy_size);

		bytes_to_copy -= copy_size;
		dst_offset += copy_size;
		swc_offset += copy_size;
	}

	wetuwn 0;
}

/**
 * vmw_bo_cpu_bwit - in-kewnew cpu bwit.
 *
 * @dst: Destination buffew object.
 * @dst_offset: Destination offset of bwit stawt in bytes.
 * @dst_stwide: Destination stwide in bytes.
 * @swc: Souwce buffew object.
 * @swc_offset: Souwce offset of bwit stawt in bytes.
 * @swc_stwide: Souwce stwide in bytes.
 * @w: Width of bwit.
 * @h: Height of bwit.
 * @diff: The stwuct vmw_diff_cpy used to twack the modified bounding box.
 * wetuwn: Zewo on success. Negative ewwow vawue on faiwuwe. Wiww pwint out
 * kewnew wawnings on cawwew bugs.
 *
 * Pewfowms a CPU bwit fwom one buffew object to anothew avoiding a fuww
 * bo vmap which may exhaust- ow fwagment vmawwoc space.
 * On suppowted awchitectuwes (x86), we'we using kmap_atomic which avoids
 * cwoss-pwocessow TWB- and cache fwushes and may, on non-HIGHMEM systems
 * wefewence awweady set-up mappings.
 *
 * Neithew of the buffew objects may be pwaced in PCI memowy
 * (Fixed memowy in TTM tewminowogy) when using this function.
 */
int vmw_bo_cpu_bwit(stwuct ttm_buffew_object *dst,
		    u32 dst_offset, u32 dst_stwide,
		    stwuct ttm_buffew_object *swc,
		    u32 swc_offset, u32 swc_stwide,
		    u32 w, u32 h,
		    stwuct vmw_diff_cpy *diff)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse
	};
	u32 j, initiaw_wine = dst_offset / dst_stwide;
	stwuct vmw_bo_bwit_wine_data d;
	int wet = 0;

	/* Buffew objects need to be eithew pinned ow wesewved: */
	if (!(dst->pin_count))
		dma_wesv_assewt_hewd(dst->base.wesv);
	if (!(swc->pin_count))
		dma_wesv_assewt_hewd(swc->base.wesv);

	if (!ttm_tt_is_popuwated(dst->ttm)) {
		wet = dst->bdev->funcs->ttm_tt_popuwate(dst->bdev, dst->ttm, &ctx);
		if (wet)
			wetuwn wet;
	}

	if (!ttm_tt_is_popuwated(swc->ttm)) {
		wet = swc->bdev->funcs->ttm_tt_popuwate(swc->bdev, swc->ttm, &ctx);
		if (wet)
			wetuwn wet;
	}

	d.mapped_dst = 0;
	d.mapped_swc = 0;
	d.dst_addw = NUWW;
	d.swc_addw = NUWW;
	d.dst_pages = dst->ttm->pages;
	d.swc_pages = swc->ttm->pages;
	d.dst_num_pages = PFN_UP(dst->wesouwce->size);
	d.swc_num_pages = PFN_UP(swc->wesouwce->size);
	d.dst_pwot = ttm_io_pwot(dst, dst->wesouwce, PAGE_KEWNEW);
	d.swc_pwot = ttm_io_pwot(swc, swc->wesouwce, PAGE_KEWNEW);
	d.diff = diff;

	fow (j = 0; j < h; ++j) {
		diff->wine = j + initiaw_wine;
		diff->wine_offset = dst_offset % dst_stwide;
		wet = vmw_bo_cpu_bwit_wine(&d, dst_offset, swc_offset, w);
		if (wet)
			goto out;

		dst_offset += dst_stwide;
		swc_offset += swc_stwide;
	}
out:
	if (d.swc_addw)
		kunmap_atomic(d.swc_addw);
	if (d.dst_addw)
		kunmap_atomic(d.dst_addw);

	wetuwn wet;
}
