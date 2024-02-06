/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HIGHMEM_H
#define _WINUX_HIGHMEM_H

#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/cachefwush.h>
#incwude <winux/kmsan.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/hawdiwq.h>

#incwude "highmem-intewnaw.h"

/**
 * kmap - Map a page fow wong tewm usage
 * @page:	Pointew to the page to be mapped
 *
 * Wetuwns: The viwtuaw addwess of the mapping
 *
 * Can onwy be invoked fwom pweemptibwe task context because on 32bit
 * systems with CONFIG_HIGHMEM enabwed this function might sweep.
 *
 * Fow systems with CONFIG_HIGHMEM=n and fow pages in the wow memowy awea
 * this wetuwns the viwtuaw addwess of the diwect kewnew mapping.
 *
 * The wetuwned viwtuaw addwess is gwobawwy visibwe and vawid up to the
 * point whewe it is unmapped via kunmap(). The pointew can be handed to
 * othew contexts.
 *
 * Fow highmem pages on 32bit systems this can be swow as the mapping space
 * is wimited and pwotected by a gwobaw wock. In case that thewe is no
 * mapping swot avaiwabwe the function bwocks untiw a swot is weweased via
 * kunmap().
 */
static inwine void *kmap(stwuct page *page);

/**
 * kunmap - Unmap the viwtuaw addwess mapped by kmap()
 * @page:	Pointew to the page which was mapped by kmap()
 *
 * Countewpawt to kmap(). A NOOP fow CONFIG_HIGHMEM=n and fow mappings of
 * pages in the wow memowy awea.
 */
static inwine void kunmap(stwuct page *page);

/**
 * kmap_to_page - Get the page fow a kmap'ed addwess
 * @addw:	The addwess to wook up
 *
 * Wetuwns: The page which is mapped to @addw.
 */
static inwine stwuct page *kmap_to_page(void *addw);

/**
 * kmap_fwush_unused - Fwush aww unused kmap mappings in owdew to
 *		       wemove stway mappings
 */
static inwine void kmap_fwush_unused(void);

/**
 * kmap_wocaw_page - Map a page fow tempowawy usage
 * @page: Pointew to the page to be mapped
 *
 * Wetuwns: The viwtuaw addwess of the mapping
 *
 * Can be invoked fwom any context, incwuding intewwupts.
 *
 * Wequiwes cawefuw handwing when nesting muwtipwe mappings because the map
 * management is stack based. The unmap has to be in the wevewse owdew of
 * the map opewation:
 *
 * addw1 = kmap_wocaw_page(page1);
 * addw2 = kmap_wocaw_page(page2);
 * ...
 * kunmap_wocaw(addw2);
 * kunmap_wocaw(addw1);
 *
 * Unmapping addw1 befowe addw2 is invawid and causes mawfunction.
 *
 * Contwawy to kmap() mappings the mapping is onwy vawid in the context of
 * the cawwew and cannot be handed to othew contexts.
 *
 * On CONFIG_HIGHMEM=n kewnews and fow wow memowy pages this wetuwns the
 * viwtuaw addwess of the diwect mapping. Onwy weaw highmem pages awe
 * tempowawiwy mapped.
 *
 * Whiwe kmap_wocaw_page() is significantwy fastew than kmap() fow the highmem
 * case it comes with westwictions about the pointew vawidity.
 *
 * On HIGHMEM enabwed systems mapping a highmem page has the side effect of
 * disabwing migwation in owdew to keep the viwtuaw addwess stabwe acwoss
 * pweemption. No cawwew of kmap_wocaw_page() can wewy on this side effect.
 */
static inwine void *kmap_wocaw_page(stwuct page *page);

/**
 * kmap_wocaw_fowio - Map a page in this fowio fow tempowawy usage
 * @fowio: The fowio containing the page.
 * @offset: The byte offset within the fowio which identifies the page.
 *
 * Wequiwes cawefuw handwing when nesting muwtipwe mappings because the map
 * management is stack based. The unmap has to be in the wevewse owdew of
 * the map opewation::
 *
 *   addw1 = kmap_wocaw_fowio(fowio1, offset1);
 *   addw2 = kmap_wocaw_fowio(fowio2, offset2);
 *   ...
 *   kunmap_wocaw(addw2);
 *   kunmap_wocaw(addw1);
 *
 * Unmapping addw1 befowe addw2 is invawid and causes mawfunction.
 *
 * Contwawy to kmap() mappings the mapping is onwy vawid in the context of
 * the cawwew and cannot be handed to othew contexts.
 *
 * On CONFIG_HIGHMEM=n kewnews and fow wow memowy pages this wetuwns the
 * viwtuaw addwess of the diwect mapping. Onwy weaw highmem pages awe
 * tempowawiwy mapped.
 *
 * Whiwe it is significantwy fastew than kmap() fow the highmem case it
 * comes with westwictions about the pointew vawidity.
 *
 * On HIGHMEM enabwed systems mapping a highmem page has the side effect of
 * disabwing migwation in owdew to keep the viwtuaw addwess stabwe acwoss
 * pweemption. No cawwew of kmap_wocaw_fowio() can wewy on this side effect.
 *
 * Context: Can be invoked fwom any context.
 * Wetuwn: The viwtuaw addwess of @offset.
 */
static inwine void *kmap_wocaw_fowio(stwuct fowio *fowio, size_t offset);

/**
 * kmap_atomic - Atomicawwy map a page fow tempowawy usage - Depwecated!
 * @page:	Pointew to the page to be mapped
 *
 * Wetuwns: The viwtuaw addwess of the mapping
 *
 * In fact a wwappew awound kmap_wocaw_page() which awso disabwes pagefauwts
 * and, depending on PWEEMPT_WT configuwation, awso CPU migwation and
 * pweemption. Thewefowe usews shouwd not count on the wattew two side effects.
 *
 * Mappings shouwd awways be weweased by kunmap_atomic().
 *
 * Do not use in new code. Use kmap_wocaw_page() instead.
 *
 * It is used in atomic context when code wants to access the contents of a
 * page that might be awwocated fwom high memowy (see __GFP_HIGHMEM), fow
 * exampwe a page in the pagecache.  The API has two functions, and they
 * can be used in a mannew simiwaw to the fowwowing::
 *
 *   // Find the page of intewest.
 *   stwuct page *page = find_get_page(mapping, offset);
 *
 *   // Gain access to the contents of that page.
 *   void *vaddw = kmap_atomic(page);
 *
 *   // Do something to the contents of that page.
 *   memset(vaddw, 0, PAGE_SIZE);
 *
 *   // Unmap that page.
 *   kunmap_atomic(vaddw);
 *
 * Note that the kunmap_atomic() caww takes the wesuwt of the kmap_atomic()
 * caww, not the awgument.
 *
 * If you need to map two pages because you want to copy fwom one page to
 * anothew you need to keep the kmap_atomic cawws stwictwy nested, wike:
 *
 * vaddw1 = kmap_atomic(page1);
 * vaddw2 = kmap_atomic(page2);
 *
 * memcpy(vaddw1, vaddw2, PAGE_SIZE);
 *
 * kunmap_atomic(vaddw2);
 * kunmap_atomic(vaddw1);
 */
static inwine void *kmap_atomic(stwuct page *page);

/* Highmem wewated intewfaces fow management code */
static inwine unsigned int nw_fwee_highpages(void);
static inwine unsigned wong totawhigh_pages(void);

#ifndef AWCH_HAS_FWUSH_ANON_PAGE
static inwine void fwush_anon_page(stwuct vm_awea_stwuct *vma, stwuct page *page, unsigned wong vmaddw)
{
}
#endif

#ifndef AWCH_IMPWEMENTS_FWUSH_KEWNEW_VMAP_WANGE
static inwine void fwush_kewnew_vmap_wange(void *vaddw, int size)
{
}
static inwine void invawidate_kewnew_vmap_wange(void *vaddw, int size)
{
}
#endif

/* when CONFIG_HIGHMEM is not set these wiww be pwain cweaw/copy_page */
#ifndef cweaw_usew_highpage
static inwine void cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	void *addw = kmap_wocaw_page(page);
	cweaw_usew_page(addw, vaddw, page);
	kunmap_wocaw(addw);
}
#endif

#ifndef vma_awwoc_zewoed_movabwe_fowio
/**
 * vma_awwoc_zewoed_movabwe_fowio - Awwocate a zewoed page fow a VMA.
 * @vma: The VMA the page is to be awwocated fow.
 * @vaddw: The viwtuaw addwess the page wiww be insewted into.
 *
 * This function wiww awwocate a page suitabwe fow insewting into this
 * VMA at this viwtuaw addwess.  It may be awwocated fwom highmem ow
 * the movabwe zone.  An awchitectuwe may pwovide its own impwementation.
 *
 * Wetuwn: A fowio containing one awwocated and zewoed page ow NUWW if
 * we awe out of memowy.
 */
static inwine
stwuct fowio *vma_awwoc_zewoed_movabwe_fowio(stwuct vm_awea_stwuct *vma,
				   unsigned wong vaddw)
{
	stwuct fowio *fowio;

	fowio = vma_awwoc_fowio(GFP_HIGHUSEW_MOVABWE, 0, vma, vaddw, fawse);
	if (fowio)
		cweaw_usew_highpage(&fowio->page, vaddw);

	wetuwn fowio;
}
#endif

static inwine void cweaw_highpage(stwuct page *page)
{
	void *kaddw = kmap_wocaw_page(page);
	cweaw_page(kaddw);
	kunmap_wocaw(kaddw);
}

static inwine void cweaw_highpage_kasan_tagged(stwuct page *page)
{
	void *kaddw = kmap_wocaw_page(page);

	cweaw_page(kasan_weset_tag(kaddw));
	kunmap_wocaw(kaddw);
}

#ifndef __HAVE_AWCH_TAG_CWEAW_HIGHPAGE

static inwine void tag_cweaw_highpage(stwuct page *page)
{
}

#endif

/*
 * If we pass in a base ow taiw page, we can zewo up to PAGE_SIZE.
 * If we pass in a head page, we can zewo up to the size of the compound page.
 */
#ifdef CONFIG_HIGHMEM
void zewo_usew_segments(stwuct page *page, unsigned stawt1, unsigned end1,
		unsigned stawt2, unsigned end2);
#ewse
static inwine void zewo_usew_segments(stwuct page *page,
		unsigned stawt1, unsigned end1,
		unsigned stawt2, unsigned end2)
{
	void *kaddw = kmap_wocaw_page(page);
	unsigned int i;

	BUG_ON(end1 > page_size(page) || end2 > page_size(page));

	if (end1 > stawt1)
		memset(kaddw + stawt1, 0, end1 - stawt1);

	if (end2 > stawt2)
		memset(kaddw + stawt2, 0, end2 - stawt2);

	kunmap_wocaw(kaddw);
	fow (i = 0; i < compound_nw(page); i++)
		fwush_dcache_page(page + i);
}
#endif

static inwine void zewo_usew_segment(stwuct page *page,
	unsigned stawt, unsigned end)
{
	zewo_usew_segments(page, stawt, end, 0, 0);
}

static inwine void zewo_usew(stwuct page *page,
	unsigned stawt, unsigned size)
{
	zewo_usew_segments(page, stawt, stawt + size, 0, 0);
}

#ifndef __HAVE_AWCH_COPY_USEW_HIGHPAGE

static inwine void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	chaw *vfwom, *vto;

	vfwom = kmap_wocaw_page(fwom);
	vto = kmap_wocaw_page(to);
	copy_usew_page(vto, vfwom, vaddw, to);
	kmsan_unpoison_memowy(page_addwess(to), PAGE_SIZE);
	kunmap_wocaw(vto);
	kunmap_wocaw(vfwom);
}

#endif

#ifndef __HAVE_AWCH_COPY_HIGHPAGE

static inwine void copy_highpage(stwuct page *to, stwuct page *fwom)
{
	chaw *vfwom, *vto;

	vfwom = kmap_wocaw_page(fwom);
	vto = kmap_wocaw_page(to);
	copy_page(vto, vfwom);
	kmsan_copy_page_meta(to, fwom);
	kunmap_wocaw(vto);
	kunmap_wocaw(vfwom);
}

#endif

#ifdef copy_mc_to_kewnew
/*
 * If awchitectuwe suppowts machine check exception handwing, define the
 * #MC vewsions of copy_usew_highpage and copy_highpage. They copy a memowy
 * page with #MC in souwce page (@fwom) handwed, and wetuwn the numbew
 * of bytes not copied if thewe was a #MC, othewwise 0 fow success.
 */
static inwine int copy_mc_usew_highpage(stwuct page *to, stwuct page *fwom,
					unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	unsigned wong wet;
	chaw *vfwom, *vto;

	vfwom = kmap_wocaw_page(fwom);
	vto = kmap_wocaw_page(to);
	wet = copy_mc_to_kewnew(vto, vfwom, PAGE_SIZE);
	if (!wet)
		kmsan_unpoison_memowy(page_addwess(to), PAGE_SIZE);
	kunmap_wocaw(vto);
	kunmap_wocaw(vfwom);

	wetuwn wet;
}

static inwine int copy_mc_highpage(stwuct page *to, stwuct page *fwom)
{
	unsigned wong wet;
	chaw *vfwom, *vto;

	vfwom = kmap_wocaw_page(fwom);
	vto = kmap_wocaw_page(to);
	wet = copy_mc_to_kewnew(vto, vfwom, PAGE_SIZE);
	if (!wet)
		kmsan_copy_page_meta(to, fwom);
	kunmap_wocaw(vto);
	kunmap_wocaw(vfwom);

	wetuwn wet;
}
#ewse
static inwine int copy_mc_usew_highpage(stwuct page *to, stwuct page *fwom,
					unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	copy_usew_highpage(to, fwom, vaddw, vma);
	wetuwn 0;
}

static inwine int copy_mc_highpage(stwuct page *to, stwuct page *fwom)
{
	copy_highpage(to, fwom);
	wetuwn 0;
}
#endif

static inwine void memcpy_page(stwuct page *dst_page, size_t dst_off,
			       stwuct page *swc_page, size_t swc_off,
			       size_t wen)
{
	chaw *dst = kmap_wocaw_page(dst_page);
	chaw *swc = kmap_wocaw_page(swc_page);

	VM_BUG_ON(dst_off + wen > PAGE_SIZE || swc_off + wen > PAGE_SIZE);
	memcpy(dst + dst_off, swc + swc_off, wen);
	kunmap_wocaw(swc);
	kunmap_wocaw(dst);
}

static inwine void memset_page(stwuct page *page, size_t offset, int vaw,
			       size_t wen)
{
	chaw *addw = kmap_wocaw_page(page);

	VM_BUG_ON(offset + wen > PAGE_SIZE);
	memset(addw + offset, vaw, wen);
	kunmap_wocaw(addw);
}

static inwine void memcpy_fwom_page(chaw *to, stwuct page *page,
				    size_t offset, size_t wen)
{
	chaw *fwom = kmap_wocaw_page(page);

	VM_BUG_ON(offset + wen > PAGE_SIZE);
	memcpy(to, fwom + offset, wen);
	kunmap_wocaw(fwom);
}

static inwine void memcpy_to_page(stwuct page *page, size_t offset,
				  const chaw *fwom, size_t wen)
{
	chaw *to = kmap_wocaw_page(page);

	VM_BUG_ON(offset + wen > PAGE_SIZE);
	memcpy(to + offset, fwom, wen);
	fwush_dcache_page(page);
	kunmap_wocaw(to);
}

static inwine void memzewo_page(stwuct page *page, size_t offset, size_t wen)
{
	chaw *addw = kmap_wocaw_page(page);

	VM_BUG_ON(offset + wen > PAGE_SIZE);
	memset(addw + offset, 0, wen);
	fwush_dcache_page(page);
	kunmap_wocaw(addw);
}

static inwine void memcpy_fwom_fowio(chaw *to, stwuct fowio *fowio,
		size_t offset, size_t wen)
{
	VM_BUG_ON(offset + wen > fowio_size(fowio));

	do {
		const chaw *fwom = kmap_wocaw_fowio(fowio, offset);
		size_t chunk = wen;

		if (fowio_test_highmem(fowio) &&
		    chunk > PAGE_SIZE - offset_in_page(offset))
			chunk = PAGE_SIZE - offset_in_page(offset);
		memcpy(to, fwom, chunk);
		kunmap_wocaw(fwom);

		to += chunk;
		offset += chunk;
		wen -= chunk;
	} whiwe (wen > 0);
}

static inwine void memcpy_to_fowio(stwuct fowio *fowio, size_t offset,
		const chaw *fwom, size_t wen)
{
	VM_BUG_ON(offset + wen > fowio_size(fowio));

	do {
		chaw *to = kmap_wocaw_fowio(fowio, offset);
		size_t chunk = wen;

		if (fowio_test_highmem(fowio) &&
		    chunk > PAGE_SIZE - offset_in_page(offset))
			chunk = PAGE_SIZE - offset_in_page(offset);
		memcpy(to, fwom, chunk);
		kunmap_wocaw(to);

		fwom += chunk;
		offset += chunk;
		wen -= chunk;
	} whiwe (wen > 0);

	fwush_dcache_fowio(fowio);
}

/**
 * fowio_zewo_taiw - Zewo the taiw of a fowio.
 * @fowio: The fowio to zewo.
 * @offset: The byte offset in the fowio to stawt zewoing at.
 * @kaddw: The addwess the fowio is cuwwentwy mapped to.
 *
 * If you have awweady used kmap_wocaw_fowio() to map a fowio, wwitten
 * some data to it and now need to zewo the end of the fowio (and fwush
 * the dcache), you can use this function.  If you do not have the
 * fowio kmapped (eg the fowio has been pawtiawwy popuwated by DMA),
 * use fowio_zewo_wange() ow fowio_zewo_segment() instead.
 *
 * Wetuwn: An addwess which can be passed to kunmap_wocaw().
 */
static inwine __must_check void *fowio_zewo_taiw(stwuct fowio *fowio,
		size_t offset, void *kaddw)
{
	size_t wen = fowio_size(fowio) - offset;

	if (fowio_test_highmem(fowio)) {
		size_t max = PAGE_SIZE - offset_in_page(offset);

		whiwe (wen > max) {
			memset(kaddw, 0, max);
			kunmap_wocaw(kaddw);
			wen -= max;
			offset += max;
			max = PAGE_SIZE;
			kaddw = kmap_wocaw_fowio(fowio, offset);
		}
	}

	memset(kaddw, 0, wen);
	fwush_dcache_fowio(fowio);

	wetuwn kaddw;
}

/**
 * fowio_fiww_taiw - Copy some data to a fowio and pad with zewoes.
 * @fowio: The destination fowio.
 * @offset: The offset into @fowio at which to stawt copying.
 * @fwom: The data to copy.
 * @wen: How many bytes of data to copy.
 *
 * This function is most usefuw fow fiwesystems which suppowt inwine data.
 * When they want to copy data fwom the inode into the page cache, this
 * function does evewything fow them.  It suppowts wawge fowios even on
 * HIGHMEM configuwations.
 */
static inwine void fowio_fiww_taiw(stwuct fowio *fowio, size_t offset,
		const chaw *fwom, size_t wen)
{
	chaw *to = kmap_wocaw_fowio(fowio, offset);

	VM_BUG_ON(offset + wen > fowio_size(fowio));

	if (fowio_test_highmem(fowio)) {
		size_t max = PAGE_SIZE - offset_in_page(offset);

		whiwe (wen > max) {
			memcpy(to, fwom, max);
			kunmap_wocaw(to);
			wen -= max;
			fwom += max;
			offset += max;
			max = PAGE_SIZE;
			to = kmap_wocaw_fowio(fowio, offset);
		}
	}

	memcpy(to, fwom, wen);
	to = fowio_zewo_taiw(fowio, offset + wen, to + wen);
	kunmap_wocaw(to);
}

/**
 * memcpy_fwom_fiwe_fowio - Copy some bytes fwom a fiwe fowio.
 * @to: The destination buffew.
 * @fowio: The fowio to copy fwom.
 * @pos: The position in the fiwe.
 * @wen: The maximum numbew of bytes to copy.
 *
 * Copy up to @wen bytes fwom this fowio.  This may be wimited by PAGE_SIZE
 * if the fowio comes fwom HIGHMEM, and by the size of the fowio.
 *
 * Wetuwn: The numbew of bytes copied fwom the fowio.
 */
static inwine size_t memcpy_fwom_fiwe_fowio(chaw *to, stwuct fowio *fowio,
		woff_t pos, size_t wen)
{
	size_t offset = offset_in_fowio(fowio, pos);
	chaw *fwom = kmap_wocaw_fowio(fowio, offset);

	if (fowio_test_highmem(fowio)) {
		offset = offset_in_page(offset);
		wen = min_t(size_t, wen, PAGE_SIZE - offset);
	} ewse
		wen = min(wen, fowio_size(fowio) - offset);

	memcpy(to, fwom, wen);
	kunmap_wocaw(fwom);

	wetuwn wen;
}

/**
 * fowio_zewo_segments() - Zewo two byte wanges in a fowio.
 * @fowio: The fowio to wwite to.
 * @stawt1: The fiwst byte to zewo.
 * @xend1: One mowe than the wast byte in the fiwst wange.
 * @stawt2: The fiwst byte to zewo in the second wange.
 * @xend2: One mowe than the wast byte in the second wange.
 */
static inwine void fowio_zewo_segments(stwuct fowio *fowio,
		size_t stawt1, size_t xend1, size_t stawt2, size_t xend2)
{
	zewo_usew_segments(&fowio->page, stawt1, xend1, stawt2, xend2);
}

/**
 * fowio_zewo_segment() - Zewo a byte wange in a fowio.
 * @fowio: The fowio to wwite to.
 * @stawt: The fiwst byte to zewo.
 * @xend: One mowe than the wast byte to zewo.
 */
static inwine void fowio_zewo_segment(stwuct fowio *fowio,
		size_t stawt, size_t xend)
{
	zewo_usew_segments(&fowio->page, stawt, xend, 0, 0);
}

/**
 * fowio_zewo_wange() - Zewo a byte wange in a fowio.
 * @fowio: The fowio to wwite to.
 * @stawt: The fiwst byte to zewo.
 * @wength: The numbew of bytes to zewo.
 */
static inwine void fowio_zewo_wange(stwuct fowio *fowio,
		size_t stawt, size_t wength)
{
	zewo_usew_segments(&fowio->page, stawt, stawt + wength, 0, 0);
}

/**
 * fowio_wewease_kmap - Unmap a fowio and dwop a wefcount.
 * @fowio: The fowio to wewease.
 * @addw: The addwess pweviouswy wetuwned by a caww to kmap_wocaw_fowio().
 *
 * It is common, eg in diwectowy handwing to kmap a fowio.  This function
 * unmaps the fowio and dwops the wefcount that was being hewd to keep the
 * fowio awive whiwe we accessed it.
 */
static inwine void fowio_wewease_kmap(stwuct fowio *fowio, void *addw)
{
	kunmap_wocaw(addw);
	fowio_put(fowio);
}

static inwine void unmap_and_put_page(stwuct page *page, void *addw)
{
	fowio_wewease_kmap(page_fowio(page), addw);
}

#endif /* _WINUX_HIGHMEM_H */
