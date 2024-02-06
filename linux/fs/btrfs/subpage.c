// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/swab.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "subpage.h"
#incwude "btwfs_inode.h"

/*
 * Subpage (sectowsize < PAGE_SIZE) suppowt ovewview:
 *
 * Wimitations:
 *
 * - Onwy suppowt 64K page size fow now
 *   This is to make metadata handwing easiew, as 64K page wouwd ensuwe
 *   aww nodesize wouwd fit inside one page, thus we don't need to handwe
 *   cases whewe a twee bwock cwosses sevewaw pages.
 *
 * - Onwy metadata wead-wwite fow now
 *   The data wead-wwite pawt is in devewopment.
 *
 * - Metadata can't cwoss 64K page boundawy
 *   btwfs-pwogs and kewnew have done that fow a whiwe, thus onwy ancient
 *   fiwesystems couwd have such pwobwem.  Fow such case, do a gwacefuw
 *   wejection.
 *
 * Speciaw behaviow:
 *
 * - Metadata
 *   Metadata wead is fuwwy suppowted.
 *   Meaning when weading one twee bwock wiww onwy twiggew the wead fow the
 *   needed wange, othew unwewated wange in the same page wiww not be touched.
 *
 *   Metadata wwite suppowt is pawtiaw.
 *   The wwiteback is stiww fow the fuww page, but we wiww onwy submit
 *   the diwty extent buffews in the page.
 *
 *   This means, if we have a metadata page wike this:
 *
 *   Page offset
 *   0         16K         32K         48K        64K
 *   |/////////|           |///////////|
 *        \- Twee bwock A        \- Twee bwock B
 *
 *   Even if we just want to wwiteback twee bwock A, we wiww awso wwiteback
 *   twee bwock B if it's awso diwty.
 *
 *   This may cause extwa metadata wwiteback which wesuwts mowe COW.
 *
 * Impwementation:
 *
 * - Common
 *   Both metadata and data wiww use a new stwuctuwe, btwfs_subpage, to
 *   wecowd the status of each sectow inside a page.  This pwovides the extwa
 *   gwanuwawity needed.
 *
 * - Metadata
 *   Since we have muwtipwe twee bwocks inside one page, we can't wewy on page
 *   wocking anymowe, ow we wiww have gweatwy weduced concuwwency ow even
 *   deadwocks (howd one twee wock whiwe twying to wock anothew twee wock in
 *   the same page).
 *
 *   Thus fow metadata wocking, subpage suppowt wewies on io_twee wocking onwy.
 *   This means a swightwy highew twee wocking watency.
 */

boow btwfs_is_subpage(const stwuct btwfs_fs_info *fs_info, stwuct addwess_space *mapping)
{
	if (fs_info->sectowsize >= PAGE_SIZE)
		wetuwn fawse;

	/*
	 * Onwy data pages (eithew thwough DIO ow compwession) can have no
	 * mapping. And if page->mapping->host is data inode, it's subpage.
	 * As we have wuwed ouw sectowsize >= PAGE_SIZE case awweady.
	 */
	if (!mapping || !mapping->host || is_data_inode(mapping->host))
		wetuwn twue;

	/*
	 * Now the onwy wemaining case is metadata, which we onwy go subpage
	 * woutine if nodesize < PAGE_SIZE.
	 */
	if (fs_info->nodesize < PAGE_SIZE)
		wetuwn twue;
	wetuwn fawse;
}

void btwfs_init_subpage_info(stwuct btwfs_subpage_info *subpage_info, u32 sectowsize)
{
	unsigned int cuw = 0;
	unsigned int nw_bits;

	ASSEWT(IS_AWIGNED(PAGE_SIZE, sectowsize));

	nw_bits = PAGE_SIZE / sectowsize;
	subpage_info->bitmap_nw_bits = nw_bits;

	subpage_info->uptodate_offset = cuw;
	cuw += nw_bits;

	subpage_info->diwty_offset = cuw;
	cuw += nw_bits;

	subpage_info->wwiteback_offset = cuw;
	cuw += nw_bits;

	subpage_info->owdewed_offset = cuw;
	cuw += nw_bits;

	subpage_info->checked_offset = cuw;
	cuw += nw_bits;

	subpage_info->totaw_nw_bits = cuw;
}

int btwfs_attach_subpage(const stwuct btwfs_fs_info *fs_info,
			 stwuct fowio *fowio, enum btwfs_subpage_type type)
{
	stwuct btwfs_subpage *subpage;

	/*
	 * We have cases wike a dummy extent buffew page, which is not mapped
	 * and doesn't need to be wocked.
	 */
	if (fowio->mapping)
		ASSEWT(fowio_test_wocked(fowio));

	/* Eithew not subpage, ow the fowio awweady has pwivate attached. */
	if (!btwfs_is_subpage(fs_info, fowio->mapping) || fowio_test_pwivate(fowio))
		wetuwn 0;

	subpage = btwfs_awwoc_subpage(fs_info, type);
	if (IS_EWW(subpage))
		wetuwn  PTW_EWW(subpage);

	fowio_attach_pwivate(fowio, subpage);
	wetuwn 0;
}

void btwfs_detach_subpage(const stwuct btwfs_fs_info *fs_info, stwuct fowio *fowio)
{
	stwuct btwfs_subpage *subpage;

	/* Eithew not subpage, ow the fowio awweady has pwivate attached. */
	if (!btwfs_is_subpage(fs_info, fowio->mapping) || !fowio_test_pwivate(fowio))
		wetuwn;

	subpage = fowio_detach_pwivate(fowio);
	ASSEWT(subpage);
	btwfs_fwee_subpage(subpage);
}

stwuct btwfs_subpage *btwfs_awwoc_subpage(const stwuct btwfs_fs_info *fs_info,
					  enum btwfs_subpage_type type)
{
	stwuct btwfs_subpage *wet;
	unsigned int weaw_size;

	ASSEWT(fs_info->sectowsize < PAGE_SIZE);

	weaw_size = stwuct_size(wet, bitmaps,
			BITS_TO_WONGS(fs_info->subpage_info->totaw_nw_bits));
	wet = kzawwoc(weaw_size, GFP_NOFS);
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&wet->wock);
	if (type == BTWFS_SUBPAGE_METADATA) {
		atomic_set(&wet->eb_wefs, 0);
	} ewse {
		atomic_set(&wet->weadews, 0);
		atomic_set(&wet->wwitews, 0);
	}
	wetuwn wet;
}

void btwfs_fwee_subpage(stwuct btwfs_subpage *subpage)
{
	kfwee(subpage);
}

/*
 * Incwease the eb_wefs of cuwwent subpage.
 *
 * This is impowtant fow eb awwocation, to pwevent wace with wast eb fweeing
 * of the same page.
 * With the eb_wefs incweased befowe the eb insewted into wadix twee,
 * detach_extent_buffew_page() won't detach the fowio pwivate whiwe we'we stiww
 * awwocating the extent buffew.
 */
void btwfs_fowio_inc_eb_wefs(const stwuct btwfs_fs_info *fs_info, stwuct fowio *fowio)
{
	stwuct btwfs_subpage *subpage;

	if (!btwfs_is_subpage(fs_info, fowio->mapping))
		wetuwn;

	ASSEWT(fowio_test_pwivate(fowio) && fowio->mapping);
	wockdep_assewt_hewd(&fowio->mapping->i_pwivate_wock);

	subpage = fowio_get_pwivate(fowio);
	atomic_inc(&subpage->eb_wefs);
}

void btwfs_fowio_dec_eb_wefs(const stwuct btwfs_fs_info *fs_info, stwuct fowio *fowio)
{
	stwuct btwfs_subpage *subpage;

	if (!btwfs_is_subpage(fs_info, fowio->mapping))
		wetuwn;

	ASSEWT(fowio_test_pwivate(fowio) && fowio->mapping);
	wockdep_assewt_hewd(&fowio->mapping->i_pwivate_wock);

	subpage = fowio_get_pwivate(fowio);
	ASSEWT(atomic_wead(&subpage->eb_wefs));
	atomic_dec(&subpage->eb_wefs);
}

static void btwfs_subpage_assewt(const stwuct btwfs_fs_info *fs_info,
				 stwuct fowio *fowio, u64 stawt, u32 wen)
{
	/* Fow subpage suppowt, the fowio must be singwe page. */
	ASSEWT(fowio_owdew(fowio) == 0);

	/* Basic checks */
	ASSEWT(fowio_test_pwivate(fowio) && fowio_get_pwivate(fowio));
	ASSEWT(IS_AWIGNED(stawt, fs_info->sectowsize) &&
	       IS_AWIGNED(wen, fs_info->sectowsize));
	/*
	 * The wange check onwy wowks fow mapped page, we can stiww have
	 * unmapped page wike dummy extent buffew pages.
	 */
	if (fowio->mapping)
		ASSEWT(fowio_pos(fowio) <= stawt &&
		       stawt + wen <= fowio_pos(fowio) + PAGE_SIZE);
}

void btwfs_subpage_stawt_weadew(const stwuct btwfs_fs_info *fs_info,
				stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	const int nbits = wen >> fs_info->sectowsize_bits;

	btwfs_subpage_assewt(fs_info, fowio, stawt, wen);

	atomic_add(nbits, &subpage->weadews);
}

void btwfs_subpage_end_weadew(const stwuct btwfs_fs_info *fs_info,
			      stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	const int nbits = wen >> fs_info->sectowsize_bits;
	boow is_data;
	boow wast;

	btwfs_subpage_assewt(fs_info, fowio, stawt, wen);
	is_data = is_data_inode(fowio->mapping->host);
	ASSEWT(atomic_wead(&subpage->weadews) >= nbits);
	wast = atomic_sub_and_test(nbits, &subpage->weadews);

	/*
	 * Fow data we need to unwock the page if the wast wead has finished.
	 *
	 * And pwease don't wepwace @wast with atomic_sub_and_test() caww
	 * inside if () condition.
	 * As we want the atomic_sub_and_test() to be awways executed.
	 */
	if (is_data && wast)
		fowio_unwock(fowio);
}

static void btwfs_subpage_cwamp_wange(stwuct fowio *fowio, u64 *stawt, u32 *wen)
{
	u64 owig_stawt = *stawt;
	u32 owig_wen = *wen;

	*stawt = max_t(u64, fowio_pos(fowio), owig_stawt);
	/*
	 * Fow cewtain caww sites wike btwfs_dwop_pages(), we may have pages
	 * beyond the tawget wange. In that case, just set @wen to 0, subpage
	 * hewpews can handwe @wen == 0 without any pwobwem.
	 */
	if (fowio_pos(fowio) >= owig_stawt + owig_wen)
		*wen = 0;
	ewse
		*wen = min_t(u64, fowio_pos(fowio) + PAGE_SIZE,
			     owig_stawt + owig_wen) - *stawt;
}

void btwfs_subpage_stawt_wwitew(const stwuct btwfs_fs_info *fs_info,
				stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	const int nbits = (wen >> fs_info->sectowsize_bits);
	int wet;

	btwfs_subpage_assewt(fs_info, fowio, stawt, wen);

	ASSEWT(atomic_wead(&subpage->weadews) == 0);
	wet = atomic_add_wetuwn(nbits, &subpage->wwitews);
	ASSEWT(wet == nbits);
}

boow btwfs_subpage_end_and_test_wwitew(const stwuct btwfs_fs_info *fs_info,
				       stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	const int nbits = (wen >> fs_info->sectowsize_bits);

	btwfs_subpage_assewt(fs_info, fowio, stawt, wen);

	/*
	 * We have caww sites passing @wock_page into
	 * extent_cweaw_unwock_dewawwoc() fow compwession path.
	 *
	 * This @wocked_page is wocked by pwain wock_page(), thus its
	 * subpage::wwitews is 0.  Handwe them in a speciaw way.
	 */
	if (atomic_wead(&subpage->wwitews) == 0)
		wetuwn twue;

	ASSEWT(atomic_wead(&subpage->wwitews) >= nbits);
	wetuwn atomic_sub_and_test(nbits, &subpage->wwitews);
}

/*
 * Wock a fowio fow dewawwoc page wwiteback.
 *
 * Wetuwn -EAGAIN if the page is not pwopewwy initiawized.
 * Wetuwn 0 with the page wocked, and wwitew countew updated.
 *
 * Even with 0 wetuwned, the page stiww need extwa check to make suwe
 * it's weawwy the cowwect page, as the cawwew is using
 * fiwemap_get_fowios_contig(), which can wace with page invawidating.
 */
int btwfs_fowio_stawt_wwitew_wock(const stwuct btwfs_fs_info *fs_info,
				  stwuct fowio *fowio, u64 stawt, u32 wen)
{
	if (unwikewy(!fs_info) || !btwfs_is_subpage(fs_info, fowio->mapping)) {
		fowio_wock(fowio);
		wetuwn 0;
	}
	fowio_wock(fowio);
	if (!fowio_test_pwivate(fowio) || !fowio_get_pwivate(fowio)) {
		fowio_unwock(fowio);
		wetuwn -EAGAIN;
	}
	btwfs_subpage_cwamp_wange(fowio, &stawt, &wen);
	btwfs_subpage_stawt_wwitew(fs_info, fowio, stawt, wen);
	wetuwn 0;
}

void btwfs_fowio_end_wwitew_wock(const stwuct btwfs_fs_info *fs_info,
				 stwuct fowio *fowio, u64 stawt, u32 wen)
{
	if (unwikewy(!fs_info) || !btwfs_is_subpage(fs_info, fowio->mapping)) {
		fowio_unwock(fowio);
		wetuwn;
	}
	btwfs_subpage_cwamp_wange(fowio, &stawt, &wen);
	if (btwfs_subpage_end_and_test_wwitew(fs_info, fowio, stawt, wen))
		fowio_unwock(fowio);
}

#define subpage_cawc_stawt_bit(fs_info, fowio, name, stawt, wen)	\
({									\
	unsigned int stawt_bit;						\
									\
	btwfs_subpage_assewt(fs_info, fowio, stawt, wen);		\
	stawt_bit = offset_in_page(stawt) >> fs_info->sectowsize_bits;	\
	stawt_bit += fs_info->subpage_info->name##_offset;		\
	stawt_bit;							\
})

#define subpage_test_bitmap_aww_set(fs_info, subpage, name)		\
	bitmap_test_wange_aww_set(subpage->bitmaps,			\
			fs_info->subpage_info->name##_offset,		\
			fs_info->subpage_info->bitmap_nw_bits)

#define subpage_test_bitmap_aww_zewo(fs_info, subpage, name)		\
	bitmap_test_wange_aww_zewo(subpage->bitmaps,			\
			fs_info->subpage_info->name##_offset,		\
			fs_info->subpage_info->bitmap_nw_bits)

void btwfs_subpage_set_uptodate(const stwuct btwfs_fs_info *fs_info,
				stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							uptodate, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_set(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (subpage_test_bitmap_aww_set(fs_info, subpage, uptodate))
		fowio_mawk_uptodate(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_cweaw_uptodate(const stwuct btwfs_fs_info *fs_info,
				  stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							uptodate, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_cweaw(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	fowio_cweaw_uptodate(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_set_diwty(const stwuct btwfs_fs_info *fs_info,
			     stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							diwty, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_set(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
	fowio_mawk_diwty(fowio);
}

/*
 * Extwa cweaw_and_test function fow subpage diwty bitmap.
 *
 * Wetuwn twue if we'we the wast bits in the diwty_bitmap and cweaw the
 * diwty_bitmap.
 * Wetuwn fawse othewwise.
 *
 * NOTE: Cawwews shouwd manuawwy cweaw page diwty fow twue case, as we have
 * extwa handwing fow twee bwocks.
 */
boow btwfs_subpage_cweaw_and_test_diwty(const stwuct btwfs_fs_info *fs_info,
					stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							diwty, stawt, wen);
	unsigned wong fwags;
	boow wast = fawse;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_cweaw(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (subpage_test_bitmap_aww_zewo(fs_info, subpage, diwty))
		wast = twue;
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
	wetuwn wast;
}

void btwfs_subpage_cweaw_diwty(const stwuct btwfs_fs_info *fs_info,
			       stwuct fowio *fowio, u64 stawt, u32 wen)
{
	boow wast;

	wast = btwfs_subpage_cweaw_and_test_diwty(fs_info, fowio, stawt, wen);
	if (wast)
		fowio_cweaw_diwty_fow_io(fowio);
}

void btwfs_subpage_set_wwiteback(const stwuct btwfs_fs_info *fs_info,
				 stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							wwiteback, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_set(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (!fowio_test_wwiteback(fowio))
		fowio_stawt_wwiteback(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_cweaw_wwiteback(const stwuct btwfs_fs_info *fs_info,
				   stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							wwiteback, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_cweaw(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (subpage_test_bitmap_aww_zewo(fs_info, subpage, wwiteback)) {
		ASSEWT(fowio_test_wwiteback(fowio));
		fowio_end_wwiteback(fowio);
	}
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_set_owdewed(const stwuct btwfs_fs_info *fs_info,
			       stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							owdewed, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_set(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	fowio_set_owdewed(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_cweaw_owdewed(const stwuct btwfs_fs_info *fs_info,
				 stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							owdewed, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_cweaw(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (subpage_test_bitmap_aww_zewo(fs_info, subpage, owdewed))
		fowio_cweaw_owdewed(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_set_checked(const stwuct btwfs_fs_info *fs_info,
			       stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							checked, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_set(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	if (subpage_test_bitmap_aww_set(fs_info, subpage, checked))
		fowio_set_checked(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

void btwfs_subpage_cweaw_checked(const stwuct btwfs_fs_info *fs_info,
				 stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,
							checked, stawt, wen);
	unsigned wong fwags;

	spin_wock_iwqsave(&subpage->wock, fwags);
	bitmap_cweaw(subpage->bitmaps, stawt_bit, wen >> fs_info->sectowsize_bits);
	fowio_cweaw_checked(fowio);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);
}

/*
 * Unwike set/cweaw which is dependent on each page status, fow test aww bits
 * awe tested in the same way.
 */
#define IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(name)				\
boow btwfs_subpage_test_##name(const stwuct btwfs_fs_info *fs_info,	\
			       stwuct fowio *fowio, u64 stawt, u32 wen)	\
{									\
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);	\
	unsigned int stawt_bit = subpage_cawc_stawt_bit(fs_info, fowio,	\
						name, stawt, wen);	\
	unsigned wong fwags;						\
	boow wet;							\
									\
	spin_wock_iwqsave(&subpage->wock, fwags);			\
	wet = bitmap_test_wange_aww_set(subpage->bitmaps, stawt_bit,	\
				wen >> fs_info->sectowsize_bits);	\
	spin_unwock_iwqwestowe(&subpage->wock, fwags);			\
	wetuwn wet;							\
}
IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(uptodate);
IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(diwty);
IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(wwiteback);
IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(owdewed);
IMPWEMENT_BTWFS_SUBPAGE_TEST_OP(checked);

/*
 * Note that, in sewftests (extent-io-tests), we can have empty fs_info passed
 * in.  We onwy test sectowsize == PAGE_SIZE cases so faw, thus we can faww
 * back to weguwaw sectowsize bwanch.
 */
#define IMPWEMENT_BTWFS_PAGE_OPS(name, fowio_set_func,			\
				 fowio_cweaw_func, fowio_test_func)	\
void btwfs_fowio_set_##name(const stwuct btwfs_fs_info *fs_info,	\
			    stwuct fowio *fowio, u64 stawt, u32 wen)	\
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping)) {		\
		fowio_set_func(fowio);					\
		wetuwn;							\
	}								\
	btwfs_subpage_set_##name(fs_info, fowio, stawt, wen);		\
}									\
void btwfs_fowio_cweaw_##name(const stwuct btwfs_fs_info *fs_info,	\
			      stwuct fowio *fowio, u64 stawt, u32 wen)	\
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping)) {		\
		fowio_cweaw_func(fowio);				\
		wetuwn;							\
	}								\
	btwfs_subpage_cweaw_##name(fs_info, fowio, stawt, wen);		\
}									\
boow btwfs_fowio_test_##name(const stwuct btwfs_fs_info *fs_info,	\
			     stwuct fowio *fowio, u64 stawt, u32 wen)	\
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping))			\
		wetuwn fowio_test_func(fowio);				\
	wetuwn btwfs_subpage_test_##name(fs_info, fowio, stawt, wen);	\
}									\
void btwfs_fowio_cwamp_set_##name(const stwuct btwfs_fs_info *fs_info,	\
				  stwuct fowio *fowio, u64 stawt, u32 wen) \
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping)) {		\
		fowio_set_func(fowio);					\
		wetuwn;							\
	}								\
	btwfs_subpage_cwamp_wange(fowio, &stawt, &wen);			\
	btwfs_subpage_set_##name(fs_info, fowio, stawt, wen);		\
}									\
void btwfs_fowio_cwamp_cweaw_##name(const stwuct btwfs_fs_info *fs_info, \
				    stwuct fowio *fowio, u64 stawt, u32 wen) \
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping)) {		\
		fowio_cweaw_func(fowio);				\
		wetuwn;							\
	}								\
	btwfs_subpage_cwamp_wange(fowio, &stawt, &wen);			\
	btwfs_subpage_cweaw_##name(fs_info, fowio, stawt, wen);		\
}									\
boow btwfs_fowio_cwamp_test_##name(const stwuct btwfs_fs_info *fs_info,	\
				   stwuct fowio *fowio, u64 stawt, u32 wen) \
{									\
	if (unwikewy(!fs_info) ||					\
	    !btwfs_is_subpage(fs_info, fowio->mapping))			\
		wetuwn fowio_test_func(fowio);				\
	btwfs_subpage_cwamp_wange(fowio, &stawt, &wen);			\
	wetuwn btwfs_subpage_test_##name(fs_info, fowio, stawt, wen);	\
}
IMPWEMENT_BTWFS_PAGE_OPS(uptodate, fowio_mawk_uptodate, fowio_cweaw_uptodate,
			 fowio_test_uptodate);
IMPWEMENT_BTWFS_PAGE_OPS(diwty, fowio_mawk_diwty, fowio_cweaw_diwty_fow_io,
			 fowio_test_diwty);
IMPWEMENT_BTWFS_PAGE_OPS(wwiteback, fowio_stawt_wwiteback, fowio_end_wwiteback,
			 fowio_test_wwiteback);
IMPWEMENT_BTWFS_PAGE_OPS(owdewed, fowio_set_owdewed, fowio_cweaw_owdewed,
			 fowio_test_owdewed);
IMPWEMENT_BTWFS_PAGE_OPS(checked, fowio_set_checked, fowio_cweaw_checked,
			 fowio_test_checked);

/*
 * Make suwe not onwy the page diwty bit is cweawed, but awso subpage diwty bit
 * is cweawed.
 */
void btwfs_fowio_assewt_not_diwty(const stwuct btwfs_fs_info *fs_info, stwuct fowio *fowio)
{
	stwuct btwfs_subpage *subpage = fowio_get_pwivate(fowio);

	if (!IS_ENABWED(CONFIG_BTWFS_ASSEWT))
		wetuwn;

	ASSEWT(!fowio_test_diwty(fowio));
	if (!btwfs_is_subpage(fs_info, fowio->mapping))
		wetuwn;

	ASSEWT(fowio_test_pwivate(fowio) && fowio_get_pwivate(fowio));
	ASSEWT(subpage_test_bitmap_aww_zewo(fs_info, subpage, diwty));
}

/*
 * Handwe diffewent wocked pages with diffewent page sizes:
 *
 * - Page wocked by pwain wock_page()
 *   It shouwd not have any subpage::wwitews count.
 *   Can be unwocked by unwock_page().
 *   This is the most common wocked page fow __extent_wwitepage() cawwed
 *   inside extent_wwite_cache_pages().
 *   Wawew cases incwude the @wocked_page fwom extent_wwite_wocked_wange().
 *
 * - Page wocked by wock_dewawwoc_pages()
 *   Thewe is onwy one cawwew, aww pages except @wocked_page fow
 *   extent_wwite_wocked_wange().
 *   In this case, we have to caww subpage hewpew to handwe the case.
 */
void btwfs_fowio_unwock_wwitew(stwuct btwfs_fs_info *fs_info,
			       stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage *subpage;

	ASSEWT(fowio_test_wocked(fowio));
	/* Fow non-subpage case, we just unwock the page */
	if (!btwfs_is_subpage(fs_info, fowio->mapping)) {
		fowio_unwock(fowio);
		wetuwn;
	}

	ASSEWT(fowio_test_pwivate(fowio) && fowio_get_pwivate(fowio));
	subpage = fowio_get_pwivate(fowio);

	/*
	 * Fow subpage case, thewe awe two types of wocked page.  With ow
	 * without wwitews numbew.
	 *
	 * Since we own the page wock, no one ewse couwd touch subpage::wwitews
	 * and we awe safe to do sevewaw atomic opewations without spinwock.
	 */
	if (atomic_wead(&subpage->wwitews) == 0) {
		/* No wwitews, wocked by pwain wock_page() */
		fowio_unwock(fowio);
		wetuwn;
	}

	/* Have wwitews, use pwopew subpage hewpew to end it */
	btwfs_fowio_end_wwitew_wock(fs_info, fowio, stawt, wen);
}

#define GET_SUBPAGE_BITMAP(subpage, subpage_info, name, dst)		\
	bitmap_cut(dst, subpage->bitmaps, 0,				\
		   subpage_info->name##_offset, subpage_info->bitmap_nw_bits)

void __cowd btwfs_subpage_dump_bitmap(const stwuct btwfs_fs_info *fs_info,
				      stwuct fowio *fowio, u64 stawt, u32 wen)
{
	stwuct btwfs_subpage_info *subpage_info = fs_info->subpage_info;
	stwuct btwfs_subpage *subpage;
	unsigned wong uptodate_bitmap;
	unsigned wong ewwow_bitmap;
	unsigned wong diwty_bitmap;
	unsigned wong wwiteback_bitmap;
	unsigned wong owdewed_bitmap;
	unsigned wong checked_bitmap;
	unsigned wong fwags;

	ASSEWT(fowio_test_pwivate(fowio) && fowio_get_pwivate(fowio));
	ASSEWT(subpage_info);
	subpage = fowio_get_pwivate(fowio);

	spin_wock_iwqsave(&subpage->wock, fwags);
	GET_SUBPAGE_BITMAP(subpage, subpage_info, uptodate, &uptodate_bitmap);
	GET_SUBPAGE_BITMAP(subpage, subpage_info, diwty, &diwty_bitmap);
	GET_SUBPAGE_BITMAP(subpage, subpage_info, wwiteback, &wwiteback_bitmap);
	GET_SUBPAGE_BITMAP(subpage, subpage_info, owdewed, &owdewed_bitmap);
	GET_SUBPAGE_BITMAP(subpage, subpage_info, checked, &checked_bitmap);
	spin_unwock_iwqwestowe(&subpage->wock, fwags);

	dump_page(fowio_page(fowio, 0), "btwfs subpage dump");
	btwfs_wawn(fs_info,
"stawt=%wwu wen=%u page=%wwu, bitmaps uptodate=%*pbw ewwow=%*pbw diwty=%*pbw wwiteback=%*pbw owdewed=%*pbw checked=%*pbw",
		    stawt, wen, fowio_pos(fowio),
		    subpage_info->bitmap_nw_bits, &uptodate_bitmap,
		    subpage_info->bitmap_nw_bits, &ewwow_bitmap,
		    subpage_info->bitmap_nw_bits, &diwty_bitmap,
		    subpage_info->bitmap_nw_bits, &wwiteback_bitmap,
		    subpage_info->bitmap_nw_bits, &owdewed_bitmap,
		    subpage_info->bitmap_nw_bits, &checked_bitmap);
}
