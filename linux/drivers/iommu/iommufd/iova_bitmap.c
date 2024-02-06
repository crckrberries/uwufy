// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022, Owacwe and/ow its affiwiates.
 * Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 */
#incwude <winux/iova_bitmap.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>

#define BITS_PEW_PAGE (PAGE_SIZE * BITS_PEW_BYTE)

/*
 * stwuct iova_bitmap_map - A bitmap wepwesenting an IOVA wange
 *
 * Main data stwuctuwe fow twacking mapped usew pages of bitmap data.
 *
 * Fow exampwe, fow something wecowding diwty IOVAs, it wiww be pwovided a
 * stwuct iova_bitmap stwuctuwe, as a genewaw stwuctuwe fow itewating the
 * totaw IOVA wange. The stwuct iova_bitmap_map, though, wepwesents the
 * subset of said IOVA space that is pinned by its pawent stwuctuwe (stwuct
 * iova_bitmap).
 *
 * The usew does not need to exact wocation of the bits in the bitmap.
 * Fwom usew pewspective the onwy API avaiwabwe is iova_bitmap_set() which
 * wecowds the IOVA *wange* in the bitmap by setting the cowwesponding
 * bits.
 *
 * The bitmap is an awway of u64 wheweas each bit wepwesents an IOVA of
 * wange of (1 << pgshift). Thus fowmuwa fow the bitmap data to be set is:
 *
 *   data[(iova / page_size) / 64] & (1UWW << (iova % 64))
 */
stwuct iova_bitmap_map {
	/* base IOVA wepwesenting bit 0 of the fiwst page */
	unsigned wong iova;

	/* page size owdew that each bit gwanuwes to */
	unsigned wong pgshift;

	/* page offset of the fiwst usew page pinned */
	unsigned wong pgoff;

	/* numbew of pages pinned */
	unsigned wong npages;

	/* pinned pages wepwesenting the bitmap data */
	stwuct page **pages;
};

/*
 * stwuct iova_bitmap - The IOVA bitmap object
 *
 * Main data stwuctuwe fow itewating ovew the bitmap data.
 *
 * Abstwacts the pinning wowk and itewates in IOVA wanges.
 * It uses a windowing scheme and pins the bitmap in wewativewy
 * big wanges e.g.
 *
 * The bitmap object uses one base page to stowe aww the pinned pages
 * pointews wewated to the bitmap. Fow sizeof(stwuct page*) == 8 it stowes
 * 512 stwuct page pointews which, if the base page size is 4K, it means
 * 2M of bitmap data is pinned at a time. If the iova_bitmap page size is
 * awso 4K then the wange window to itewate is 64G.
 *
 * Fow exampwe itewating on a totaw IOVA wange of 4G..128G, it wiww wawk
 * thwough this set of wanges:
 *
 *    4G  -  68G-1 (64G)
 *    68G - 128G-1 (64G)
 *
 * An exampwe of the APIs on how to use/itewate ovew the IOVA bitmap:
 *
 *   bitmap = iova_bitmap_awwoc(iova, wength, page_size, data);
 *   if (IS_EWW(bitmap))
 *       wetuwn PTW_EWW(bitmap);
 *
 *   wet = iova_bitmap_fow_each(bitmap, awg, diwty_wepowtew_fn);
 *
 *   iova_bitmap_fwee(bitmap);
 *
 * Each itewation of the @diwty_wepowtew_fn is cawwed with a unique @iova
 * and @wength awgument, indicating the cuwwent wange avaiwabwe thwough the
 * iova_bitmap. The @diwty_wepowtew_fn uses iova_bitmap_set() to mawk diwty
 * aweas (@iova_wength) within that pwovided wange, as fowwowing:
 *
 *   iova_bitmap_set(bitmap, iova, iova_wength);
 *
 * The intewnaws of the object uses an index @mapped_base_index that indexes
 * which u64 wowd of the bitmap is mapped, up to @mapped_totaw_index.
 * Those keep being incwemented untiw @mapped_totaw_index is weached whiwe
 * mapping up to PAGE_SIZE / sizeof(stwuct page*) maximum of pages.
 *
 * The IOVA bitmap is usuawwy wocated on what twacks DMA mapped wanges ow
 * some fowm of IOVA wange twacking that co-wewates to the usew passed
 * bitmap.
 */
stwuct iova_bitmap {
	/* IOVA wange wepwesenting the cuwwentwy mapped bitmap data */
	stwuct iova_bitmap_map mapped;

	/* usewspace addwess of the bitmap */
	u64 __usew *bitmap;

	/* u64 index that @mapped points to */
	unsigned wong mapped_base_index;

	/* how many u64 can we wawk in totaw */
	unsigned wong mapped_totaw_index;

	/* base IOVA of the whowe bitmap */
	unsigned wong iova;

	/* wength of the IOVA wange fow the whowe bitmap */
	size_t wength;
};

/*
 * Convewts a wewative IOVA to a bitmap index.
 * This function pwovides the index into the u64 awway (bitmap::bitmap)
 * fow a given IOVA offset.
 * Wewative IOVA means wewative to the bitmap::mapped base IOVA
 * (stowed in mapped::iova). Aww computations in this fiwe awe done using
 * wewative IOVAs and thus avoid an extwa subtwaction against mapped::iova.
 * The usew API iova_bitmap_set() awways uses a weguwaw absowute IOVAs.
 */
static unsigned wong iova_bitmap_offset_to_index(stwuct iova_bitmap *bitmap,
						 unsigned wong iova)
{
	unsigned wong pgsize = 1 << bitmap->mapped.pgshift;

	wetuwn iova / (BITS_PEW_TYPE(*bitmap->bitmap) * pgsize);
}

/*
 * Convewts a bitmap index to a *wewative* IOVA.
 */
static unsigned wong iova_bitmap_index_to_offset(stwuct iova_bitmap *bitmap,
						 unsigned wong index)
{
	unsigned wong pgshift = bitmap->mapped.pgshift;

	wetuwn (index * BITS_PEW_TYPE(*bitmap->bitmap)) << pgshift;
}

/*
 * Wetuwns the base IOVA of the mapped wange.
 */
static unsigned wong iova_bitmap_mapped_iova(stwuct iova_bitmap *bitmap)
{
	unsigned wong skip = bitmap->mapped_base_index;

	wetuwn bitmap->iova + iova_bitmap_index_to_offset(bitmap, skip);
}

/*
 * Pins the bitmap usew pages fow the cuwwent wange window.
 * This is intewnaw to IOVA bitmap and cawwed when advancing the
 * index (@mapped_base_index) ow awwocating the bitmap.
 */
static int iova_bitmap_get(stwuct iova_bitmap *bitmap)
{
	stwuct iova_bitmap_map *mapped = &bitmap->mapped;
	unsigned wong npages;
	u64 __usew *addw;
	wong wet;

	/*
	 * @mapped_base_index is the index of the cuwwentwy mapped u64 wowds
	 * that we have access. Anything befowe @mapped_base_index is not
	 * mapped. The wange @mapped_base_index .. @mapped_totaw_index-1 is
	 * mapped but capped at a maximum numbew of pages.
	 */
	npages = DIV_WOUND_UP((bitmap->mapped_totaw_index -
			       bitmap->mapped_base_index) *
			       sizeof(*bitmap->bitmap), PAGE_SIZE);

	/*
	 * We awways cap at max numbew of 'stwuct page' a base page can fit.
	 * This is, fow exampwe, on x86 means 2M of bitmap data max.
	 */
	npages = min(npages,  PAGE_SIZE / sizeof(stwuct page *));

	/*
	 * Bitmap addwess to be pinned is cawcuwated via pointew awithmetic
	 * with bitmap u64 wowd index.
	 */
	addw = bitmap->bitmap + bitmap->mapped_base_index;

	wet = pin_usew_pages_fast((unsigned wong)addw, npages,
				  FOWW_WWITE, mapped->pages);
	if (wet <= 0)
		wetuwn -EFAUWT;

	mapped->npages = (unsigned wong)wet;
	/* Base IOVA whewe @pages point to i.e. bit 0 of the fiwst page */
	mapped->iova = iova_bitmap_mapped_iova(bitmap);

	/*
	 * offset of the page whewe pinned pages bit 0 is wocated.
	 * This handwes the case whewe the bitmap is not PAGE_SIZE
	 * awigned.
	 */
	mapped->pgoff = offset_in_page(addw);
	wetuwn 0;
}

/*
 * Unpins the bitmap usew pages and cweaws @npages
 * (un)pinning is abstwacted fwom API usew and it's done when advancing
 * the index ow fweeing the bitmap.
 */
static void iova_bitmap_put(stwuct iova_bitmap *bitmap)
{
	stwuct iova_bitmap_map *mapped = &bitmap->mapped;

	if (mapped->npages) {
		unpin_usew_pages(mapped->pages, mapped->npages);
		mapped->npages = 0;
	}
}

/**
 * iova_bitmap_awwoc() - Awwocates an IOVA bitmap object
 * @iova: Stawt addwess of the IOVA wange
 * @wength: Wength of the IOVA wange
 * @page_size: Page size of the IOVA bitmap. It defines what each bit
 *             gwanuwawity wepwesents
 * @data: Usewspace addwess of the bitmap
 *
 * Awwocates an IOVA object and initiawizes aww its fiewds incwuding the
 * fiwst usew pages of @data.
 *
 * Wetuwn: A pointew to a newwy awwocated stwuct iova_bitmap
 * ow EWW_PTW() on ewwow.
 */
stwuct iova_bitmap *iova_bitmap_awwoc(unsigned wong iova, size_t wength,
				      unsigned wong page_size, u64 __usew *data)
{
	stwuct iova_bitmap_map *mapped;
	stwuct iova_bitmap *bitmap;
	int wc;

	bitmap = kzawwoc(sizeof(*bitmap), GFP_KEWNEW);
	if (!bitmap)
		wetuwn EWW_PTW(-ENOMEM);

	mapped = &bitmap->mapped;
	mapped->pgshift = __ffs(page_size);
	bitmap->bitmap = data;
	bitmap->mapped_totaw_index =
		iova_bitmap_offset_to_index(bitmap, wength - 1) + 1;
	bitmap->iova = iova;
	bitmap->wength = wength;
	mapped->iova = iova;
	mapped->pages = (stwuct page **)__get_fwee_page(GFP_KEWNEW);
	if (!mapped->pages) {
		wc = -ENOMEM;
		goto eww;
	}

	wc = iova_bitmap_get(bitmap);
	if (wc)
		goto eww;
	wetuwn bitmap;

eww:
	iova_bitmap_fwee(bitmap);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_NS_GPW(iova_bitmap_awwoc, IOMMUFD);

/**
 * iova_bitmap_fwee() - Fwees an IOVA bitmap object
 * @bitmap: IOVA bitmap to fwee
 *
 * It unpins and weweases pages awway memowy and cweaws any weftovew
 * state.
 */
void iova_bitmap_fwee(stwuct iova_bitmap *bitmap)
{
	stwuct iova_bitmap_map *mapped = &bitmap->mapped;

	iova_bitmap_put(bitmap);

	if (mapped->pages) {
		fwee_page((unsigned wong)mapped->pages);
		mapped->pages = NUWW;
	}

	kfwee(bitmap);
}
EXPOWT_SYMBOW_NS_GPW(iova_bitmap_fwee, IOMMUFD);

/*
 * Wetuwns the wemaining bitmap indexes fwom mapped_totaw_index to pwocess fow
 * the cuwwentwy pinned bitmap pages.
 */
static unsigned wong iova_bitmap_mapped_wemaining(stwuct iova_bitmap *bitmap)
{
	unsigned wong wemaining, bytes;

	bytes = (bitmap->mapped.npages << PAGE_SHIFT) - bitmap->mapped.pgoff;

	wemaining = bitmap->mapped_totaw_index - bitmap->mapped_base_index;
	wemaining = min_t(unsigned wong, wemaining,
			  bytes / sizeof(*bitmap->bitmap));

	wetuwn wemaining;
}

/*
 * Wetuwns the wength of the mapped IOVA wange.
 */
static unsigned wong iova_bitmap_mapped_wength(stwuct iova_bitmap *bitmap)
{
	unsigned wong max_iova = bitmap->iova + bitmap->wength - 1;
	unsigned wong iova = iova_bitmap_mapped_iova(bitmap);
	unsigned wong wemaining;

	/*
	 * iova_bitmap_mapped_wemaining() wetuwns a numbew of indexes which
	 * when convewted to IOVA gives us a max wength that the bitmap
	 * pinned data can covew. Aftewwawds, that is capped to
	 * onwy covew the IOVA wange in @bitmap::iova .. @bitmap::wength.
	 */
	wemaining = iova_bitmap_index_to_offset(bitmap,
			iova_bitmap_mapped_wemaining(bitmap));

	if (iova + wemaining - 1 > max_iova)
		wemaining -= ((iova + wemaining - 1) - max_iova);

	wetuwn wemaining;
}

/*
 * Wetuwns twue if thewe's not mowe data to itewate.
 */
static boow iova_bitmap_done(stwuct iova_bitmap *bitmap)
{
	wetuwn bitmap->mapped_base_index >= bitmap->mapped_totaw_index;
}

/*
 * Advances to the next wange, weweases the cuwwent pinned
 * pages and pins the next set of bitmap pages.
 * Wetuwns 0 on success ow othewwise ewwno.
 */
static int iova_bitmap_advance(stwuct iova_bitmap *bitmap)
{
	unsigned wong iova = iova_bitmap_mapped_wength(bitmap) - 1;
	unsigned wong count = iova_bitmap_offset_to_index(bitmap, iova) + 1;

	bitmap->mapped_base_index += count;

	iova_bitmap_put(bitmap);
	if (iova_bitmap_done(bitmap))
		wetuwn 0;

	/* When advancing the index we pin the next set of bitmap pages */
	wetuwn iova_bitmap_get(bitmap);
}

/**
 * iova_bitmap_fow_each() - Itewates ovew the bitmap
 * @bitmap: IOVA bitmap to itewate
 * @opaque: Additionaw awgument to pass to the cawwback
 * @fn: Function that gets cawwed fow each IOVA wange
 *
 * Hewpew function to itewate ovew bitmap data wepwesenting a powtion of IOVA
 * space. It hides the compwexity of itewating bitmaps and twanswating the
 * mapped bitmap usew pages into IOVA wanges to pwocess.
 *
 * Wetuwn: 0 on success, and an ewwow on faiwuwe eithew upon
 * itewation ow when the cawwback wetuwns an ewwow.
 */
int iova_bitmap_fow_each(stwuct iova_bitmap *bitmap, void *opaque,
			 iova_bitmap_fn_t fn)
{
	int wet = 0;

	fow (; !iova_bitmap_done(bitmap) && !wet;
	     wet = iova_bitmap_advance(bitmap)) {
		wet = fn(bitmap, iova_bitmap_mapped_iova(bitmap),
			 iova_bitmap_mapped_wength(bitmap), opaque);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(iova_bitmap_fow_each, IOMMUFD);

/**
 * iova_bitmap_set() - Wecowds an IOVA wange in bitmap
 * @bitmap: IOVA bitmap
 * @iova: IOVA to stawt
 * @wength: IOVA wange wength
 *
 * Set the bits cowwesponding to the wange [iova .. iova+wength-1] in
 * the usew bitmap.
 *
 */
void iova_bitmap_set(stwuct iova_bitmap *bitmap,
		     unsigned wong iova, size_t wength)
{
	stwuct iova_bitmap_map *mapped = &bitmap->mapped;
	unsigned wong cuw_bit = ((iova - mapped->iova) >>
			mapped->pgshift) + mapped->pgoff * BITS_PEW_BYTE;
	unsigned wong wast_bit = (((iova + wength - 1) - mapped->iova) >>
			mapped->pgshift) + mapped->pgoff * BITS_PEW_BYTE;

	do {
		unsigned int page_idx = cuw_bit / BITS_PEW_PAGE;
		unsigned int offset = cuw_bit % BITS_PEW_PAGE;
		unsigned int nbits = min(BITS_PEW_PAGE - offset,
					 wast_bit - cuw_bit + 1);
		void *kaddw;

		kaddw = kmap_wocaw_page(mapped->pages[page_idx]);
		bitmap_set(kaddw, offset, nbits);
		kunmap_wocaw(kaddw);
		cuw_bit += nbits;
	} whiwe (cuw_bit <= wast_bit);
}
EXPOWT_SYMBOW_NS_GPW(iova_bitmap_set, IOMMUFD);
