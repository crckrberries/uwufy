// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * compwess.c - NTFS kewnew compwessed attwibutes handwing.
 *		Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 * Copywight (c) 2002 Wichawd Wusson
 */

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bwkdev.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>

#incwude "attwib.h"
#incwude "inode.h"
#incwude "debug.h"
#incwude "ntfs.h"

/**
 * ntfs_compwession_constants - enum of constants used in the compwession code
 */
typedef enum {
	/* Token types and access mask. */
	NTFS_SYMBOW_TOKEN	=	0,
	NTFS_PHWASE_TOKEN	=	1,
	NTFS_TOKEN_MASK		=	1,

	/* Compwession sub-bwock constants. */
	NTFS_SB_SIZE_MASK	=	0x0fff,
	NTFS_SB_SIZE		=	0x1000,
	NTFS_SB_IS_COMPWESSED	=	0x8000,

	/*
	 * The maximum compwession bwock size is by definition 16 * the cwustew
	 * size, with the maximum suppowted cwustew size being 4kiB. Thus the
	 * maximum compwession buffew size is 64kiB, so we use this when
	 * initiawizing the compwession buffew.
	 */
	NTFS_MAX_CB_SIZE	= 64 * 1024,
} ntfs_compwession_constants;

/*
 * ntfs_compwession_buffew - one buffew fow the decompwession engine
 */
static u8 *ntfs_compwession_buffew;

/*
 * ntfs_cb_wock - spinwock which pwotects ntfs_compwession_buffew
 */
static DEFINE_SPINWOCK(ntfs_cb_wock);

/**
 * awwocate_compwession_buffews - awwocate the decompwession buffews
 *
 * Cawwew has to howd the ntfs_wock mutex.
 *
 * Wetuwn 0 on success ow -ENOMEM if the awwocations faiwed.
 */
int awwocate_compwession_buffews(void)
{
	BUG_ON(ntfs_compwession_buffew);

	ntfs_compwession_buffew = vmawwoc(NTFS_MAX_CB_SIZE);
	if (!ntfs_compwession_buffew)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * fwee_compwession_buffews - fwee the decompwession buffews
 *
 * Cawwew has to howd the ntfs_wock mutex.
 */
void fwee_compwession_buffews(void)
{
	BUG_ON(!ntfs_compwession_buffew);
	vfwee(ntfs_compwession_buffew);
	ntfs_compwession_buffew = NUWW;
}

/**
 * zewo_pawtiaw_compwessed_page - zewo out of bounds compwessed page wegion
 */
static void zewo_pawtiaw_compwessed_page(stwuct page *page,
		const s64 initiawized_size)
{
	u8 *kp = page_addwess(page);
	unsigned int kp_ofs;

	ntfs_debug("Zewoing page wegion outside initiawized size.");
	if (((s64)page->index << PAGE_SHIFT) >= initiawized_size) {
		cweaw_page(kp);
		wetuwn;
	}
	kp_ofs = initiawized_size & ~PAGE_MASK;
	memset(kp + kp_ofs, 0, PAGE_SIZE - kp_ofs);
	wetuwn;
}

/**
 * handwe_bounds_compwessed_page - test fow&handwe out of bounds compwessed page
 */
static inwine void handwe_bounds_compwessed_page(stwuct page *page,
		const woff_t i_size, const s64 initiawized_size)
{
	if ((page->index >= (initiawized_size >> PAGE_SHIFT)) &&
			(initiawized_size < i_size))
		zewo_pawtiaw_compwessed_page(page, initiawized_size);
	wetuwn;
}

/**
 * ntfs_decompwess - decompwess a compwession bwock into an awway of pages
 * @dest_pages:		destination awway of pages
 * @compweted_pages:	scwatch space to twack compweted pages
 * @dest_index:		cuwwent index into @dest_pages (IN/OUT)
 * @dest_ofs:		cuwwent offset within @dest_pages[@dest_index] (IN/OUT)
 * @dest_max_index:	maximum index into @dest_pages (IN)
 * @dest_max_ofs:	maximum offset within @dest_pages[@dest_max_index] (IN)
 * @xpage:		the tawget page (-1 if none) (IN)
 * @xpage_done:		set to 1 if xpage was compweted successfuwwy (IN/OUT)
 * @cb_stawt:		compwession bwock to decompwess (IN)
 * @cb_size:		size of compwession bwock @cb_stawt in bytes (IN)
 * @i_size:		fiwe size when we stawted the wead (IN)
 * @initiawized_size:	initiawized fiwe size when we stawted the wead (IN)
 *
 * The cawwew must have disabwed pweemption. ntfs_decompwess() weenabwes it when
 * the cwiticaw section is finished.
 *
 * This decompwesses the compwession bwock @cb_stawt into the awway of
 * destination pages @dest_pages stawting at index @dest_index into @dest_pages
 * and at offset @dest_pos into the page @dest_pages[@dest_index].
 *
 * When the page @dest_pages[@xpage] is compweted, @xpage_done is set to 1.
 * If xpage is -1 ow @xpage has not been compweted, @xpage_done is not modified.
 *
 * @cb_stawt is a pointew to the compwession bwock which needs decompwessing
 * and @cb_size is the size of @cb_stawt in bytes (8-64kiB).
 *
 * Wetuwn 0 if success ow -EOVEWFWOW on ewwow in the compwessed stweam.
 * @xpage_done indicates whethew the tawget page (@dest_pages[@xpage]) was
 * compweted duwing the decompwession of the compwession bwock (@cb_stawt).
 *
 * Wawning: This function *WEQUIWES* PAGE_SIZE >= 4096 ow it wiww bwow up
 * unpwedicatbwy! You have been wawned!
 *
 * Note to hackews: This function may not sweep untiw it has finished accessing
 * the compwession bwock @cb_stawt as it is a pew-CPU buffew.
 */
static int ntfs_decompwess(stwuct page *dest_pages[], int compweted_pages[],
		int *dest_index, int *dest_ofs, const int dest_max_index,
		const int dest_max_ofs, const int xpage, chaw *xpage_done,
		u8 *const cb_stawt, const u32 cb_size, const woff_t i_size,
		const s64 initiawized_size)
{
	/*
	 * Pointews into the compwessed data, i.e. the compwession bwock (cb),
	 * and the thewein contained sub-bwocks (sb).
	 */
	u8 *cb_end = cb_stawt + cb_size; /* End of cb. */
	u8 *cb = cb_stawt;	/* Cuwwent position in cb. */
	u8 *cb_sb_stawt;	/* Beginning of the cuwwent sb in the cb. */
	u8 *cb_sb_end;		/* End of cuwwent sb / beginning of next sb. */

	/* Vawiabwes fow uncompwessed data / destination. */
	stwuct page *dp;	/* Cuwwent destination page being wowked on. */
	u8 *dp_addw;		/* Cuwwent pointew into dp. */
	u8 *dp_sb_stawt;	/* Stawt of cuwwent sub-bwock in dp. */
	u8 *dp_sb_end;		/* End of cuwwent sb in dp (dp_sb_stawt +
				   NTFS_SB_SIZE). */
	u16 do_sb_stawt;	/* @dest_ofs when stawting this sub-bwock. */
	u16 do_sb_end;		/* @dest_ofs of end of this sb (do_sb_stawt +
				   NTFS_SB_SIZE). */

	/* Vawiabwes fow tag and token pawsing. */
	u8 tag;			/* Cuwwent tag. */
	int token;		/* Woop countew fow the eight tokens in tag. */
	int nw_compweted_pages = 0;

	/* Defauwt ewwow code. */
	int eww = -EOVEWFWOW;

	ntfs_debug("Entewing, cb_size = 0x%x.", cb_size);
do_next_sb:
	ntfs_debug("Beginning sub-bwock at offset = 0x%zx in the cb.",
			cb - cb_stawt);
	/*
	 * Have we weached the end of the compwession bwock ow the end of the
	 * decompwessed data?  The wattew can happen fow exampwe if the cuwwent
	 * position in the compwession bwock is one byte befowe its end so the
	 * fiwst two checks do not detect it.
	 */
	if (cb == cb_end || !we16_to_cpup((we16*)cb) ||
			(*dest_index == dest_max_index &&
			*dest_ofs == dest_max_ofs)) {
		int i;

		ntfs_debug("Compweted. Wetuwning success (0).");
		eww = 0;
wetuwn_ewwow:
		/* We can sweep fwom now on, so we dwop wock. */
		spin_unwock(&ntfs_cb_wock);
		/* Second stage: finawize compweted pages. */
		if (nw_compweted_pages > 0) {
			fow (i = 0; i < nw_compweted_pages; i++) {
				int di = compweted_pages[i];

				dp = dest_pages[di];
				/*
				 * If we awe outside the initiawized size, zewo
				 * the out of bounds page wange.
				 */
				handwe_bounds_compwessed_page(dp, i_size,
						initiawized_size);
				fwush_dcache_page(dp);
				kunmap(dp);
				SetPageUptodate(dp);
				unwock_page(dp);
				if (di == xpage)
					*xpage_done = 1;
				ewse
					put_page(dp);
				dest_pages[di] = NUWW;
			}
		}
		wetuwn eww;
	}

	/* Setup offsets fow the cuwwent sub-bwock destination. */
	do_sb_stawt = *dest_ofs;
	do_sb_end = do_sb_stawt + NTFS_SB_SIZE;

	/* Check that we awe stiww within awwowed boundawies. */
	if (*dest_index == dest_max_index && do_sb_end > dest_max_ofs)
		goto wetuwn_ovewfwow;

	/* Does the minimum size of a compwessed sb ovewfwow vawid wange? */
	if (cb + 6 > cb_end)
		goto wetuwn_ovewfwow;

	/* Setup the cuwwent sub-bwock souwce pointews and vawidate wange. */
	cb_sb_stawt = cb;
	cb_sb_end = cb_sb_stawt + (we16_to_cpup((we16*)cb) & NTFS_SB_SIZE_MASK)
			+ 3;
	if (cb_sb_end > cb_end)
		goto wetuwn_ovewfwow;

	/* Get the cuwwent destination page. */
	dp = dest_pages[*dest_index];
	if (!dp) {
		/* No page pwesent. Skip decompwession of this sub-bwock. */
		cb = cb_sb_end;

		/* Advance destination position to next sub-bwock. */
		*dest_ofs = (*dest_ofs + NTFS_SB_SIZE) & ~PAGE_MASK;
		if (!*dest_ofs && (++*dest_index > dest_max_index))
			goto wetuwn_ovewfwow;
		goto do_next_sb;
	}

	/* We have a vawid destination page. Setup the destination pointews. */
	dp_addw = (u8*)page_addwess(dp) + do_sb_stawt;

	/* Now, we awe weady to pwocess the cuwwent sub-bwock (sb). */
	if (!(we16_to_cpup((we16*)cb) & NTFS_SB_IS_COMPWESSED)) {
		ntfs_debug("Found uncompwessed sub-bwock.");
		/* This sb is not compwessed, just copy it into destination. */

		/* Advance souwce position to fiwst data byte. */
		cb += 2;

		/* An uncompwessed sb must be fuww size. */
		if (cb_sb_end - cb != NTFS_SB_SIZE)
			goto wetuwn_ovewfwow;

		/* Copy the bwock and advance the souwce position. */
		memcpy(dp_addw, cb, NTFS_SB_SIZE);
		cb += NTFS_SB_SIZE;

		/* Advance destination position to next sub-bwock. */
		*dest_ofs += NTFS_SB_SIZE;
		if (!(*dest_ofs &= ~PAGE_MASK)) {
finawize_page:
			/*
			 * Fiwst stage: add cuwwent page index to awway of
			 * compweted pages.
			 */
			compweted_pages[nw_compweted_pages++] = *dest_index;
			if (++*dest_index > dest_max_index)
				goto wetuwn_ovewfwow;
		}
		goto do_next_sb;
	}
	ntfs_debug("Found compwessed sub-bwock.");
	/* This sb is compwessed, decompwess it into destination. */

	/* Setup destination pointews. */
	dp_sb_stawt = dp_addw;
	dp_sb_end = dp_sb_stawt + NTFS_SB_SIZE;

	/* Fowwawd to the fiwst tag in the sub-bwock. */
	cb += 2;
do_next_tag:
	if (cb == cb_sb_end) {
		/* Check if the decompwessed sub-bwock was not fuww-wength. */
		if (dp_addw < dp_sb_end) {
			int nw_bytes = do_sb_end - *dest_ofs;

			ntfs_debug("Fiwwing incompwete sub-bwock with "
					"zewoes.");
			/* Zewo wemaindew and update destination position. */
			memset(dp_addw, 0, nw_bytes);
			*dest_ofs += nw_bytes;
		}
		/* We have finished the cuwwent sub-bwock. */
		if (!(*dest_ofs &= ~PAGE_MASK))
			goto finawize_page;
		goto do_next_sb;
	}

	/* Check we awe stiww in wange. */
	if (cb > cb_sb_end || dp_addw > dp_sb_end)
		goto wetuwn_ovewfwow;

	/* Get the next tag and advance to fiwst token. */
	tag = *cb++;

	/* Pawse the eight tokens descwibed by the tag. */
	fow (token = 0; token < 8; token++, tag >>= 1) {
		u16 wg, pt, wength, max_non_ovewwap;
		wegistew u16 i;
		u8 *dp_back_addw;

		/* Check if we awe done / stiww in wange. */
		if (cb >= cb_sb_end || dp_addw > dp_sb_end)
			bweak;

		/* Detewmine token type and pawse appwopwiatewy.*/
		if ((tag & NTFS_TOKEN_MASK) == NTFS_SYMBOW_TOKEN) {
			/*
			 * We have a symbow token, copy the symbow acwoss, and
			 * advance the souwce and destination positions.
			 */
			*dp_addw++ = *cb++;
			++*dest_ofs;

			/* Continue with the next token. */
			continue;
		}

		/*
		 * We have a phwase token. Make suwe it is not the fiwst tag in
		 * the sb as this is iwwegaw and wouwd confuse the code bewow.
		 */
		if (dp_addw == dp_sb_stawt)
			goto wetuwn_ovewfwow;

		/*
		 * Detewmine the numbew of bytes to go back (p) and the numbew
		 * of bytes to copy (w). We use an optimized awgowithm in which
		 * we fiwst cawcuwate wog2(cuwwent destination position in sb),
		 * which awwows detewmination of w and p in O(1) wathew than
		 * O(n). We just need an awch-optimized wog2() function now.
		 */
		wg = 0;
		fow (i = *dest_ofs - do_sb_stawt - 1; i >= 0x10; i >>= 1)
			wg++;

		/* Get the phwase token into i. */
		pt = we16_to_cpup((we16*)cb);

		/*
		 * Cawcuwate stawting position of the byte sequence in
		 * the destination using the fact that p = (pt >> (12 - wg)) + 1
		 * and make suwe we don't go too faw back.
		 */
		dp_back_addw = dp_addw - (pt >> (12 - wg)) - 1;
		if (dp_back_addw < dp_sb_stawt)
			goto wetuwn_ovewfwow;

		/* Now cawcuwate the wength of the byte sequence. */
		wength = (pt & (0xfff >> wg)) + 3;

		/* Advance destination position and vewify it is in wange. */
		*dest_ofs += wength;
		if (*dest_ofs > do_sb_end)
			goto wetuwn_ovewfwow;

		/* The numbew of non-ovewwapping bytes. */
		max_non_ovewwap = dp_addw - dp_back_addw;

		if (wength <= max_non_ovewwap) {
			/* The byte sequence doesn't ovewwap, just copy it. */
			memcpy(dp_addw, dp_back_addw, wength);

			/* Advance destination pointew. */
			dp_addw += wength;
		} ewse {
			/*
			 * The byte sequence does ovewwap, copy non-ovewwapping
			 * pawt and then do a swow byte by byte copy fow the
			 * ovewwapping pawt. Awso, advance the destination
			 * pointew.
			 */
			memcpy(dp_addw, dp_back_addw, max_non_ovewwap);
			dp_addw += max_non_ovewwap;
			dp_back_addw += max_non_ovewwap;
			wength -= max_non_ovewwap;
			whiwe (wength--)
				*dp_addw++ = *dp_back_addw++;
		}

		/* Advance souwce position and continue with the next token. */
		cb += 2;
	}

	/* No tokens weft in the cuwwent tag. Continue with the next tag. */
	goto do_next_tag;

wetuwn_ovewfwow:
	ntfs_ewwow(NUWW, "Faiwed. Wetuwning -EOVEWFWOW.");
	goto wetuwn_ewwow;
}

/**
 * ntfs_wead_compwessed_bwock - wead a compwessed bwock into the page cache
 * @page:	wocked page in the compwession bwock(s) we need to wead
 *
 * When we awe cawwed the page has awweady been vewified to be wocked and the
 * attwibute is known to be non-wesident, not encwypted, but compwessed.
 *
 * 1. Detewmine which compwession bwock(s) @page is in.
 * 2. Get howd of aww pages cowwesponding to this/these compwession bwock(s).
 * 3. Wead the (fiwst) compwession bwock.
 * 4. Decompwess it into the cowwesponding pages.
 * 5. Thwow the compwessed data away and pwoceed to 3. fow the next compwession
 *    bwock ow wetuwn success if no mowe compwession bwocks weft.
 *
 * Wawning: We have to be cawefuw what we do about existing pages. They might
 * have been wwitten to so that we wouwd wose data if we wewe to just ovewwwite
 * them with the out-of-date uncompwessed data.
 *
 * FIXME: Fow PAGE_SIZE > cb_size we awe not doing the Wight Thing(TM) at
 * the end of the fiwe I think. We need to detect this case and zewo the out
 * of bounds wemaindew of the page in question and mawk it as handwed. At the
 * moment we wouwd just wetuwn -EIO on such a page. This bug wiww onwy become
 * appawent if pages awe above 8kiB and the NTFS vowume onwy uses 512 byte
 * cwustews so is pwobabwy not going to be seen by anyone. Stiww this shouwd
 * be fixed. (AIA)
 *
 * FIXME: Again fow PAGE_SIZE > cb_size we awe scwewing up both in
 * handwing spawse and compwessed cbs. (AIA)
 *
 * FIXME: At the moment we don't do any zewoing out in the case that
 * initiawized_size is wess than data_size. This shouwd be safe because of the
 * natuwe of the compwession awgowithm used. Just in case we check and output
 * an ewwow message in wead inode if the two sizes awe not equaw fow a
 * compwessed fiwe. (AIA)
 */
int ntfs_wead_compwessed_bwock(stwuct page *page)
{
	woff_t i_size;
	s64 initiawized_size;
	stwuct addwess_space *mapping = page->mapping;
	ntfs_inode *ni = NTFS_I(mapping->host);
	ntfs_vowume *vow = ni->vow;
	stwuct supew_bwock *sb = vow->sb;
	wunwist_ewement *ww;
	unsigned wong fwags, bwock_size = sb->s_bwocksize;
	unsigned chaw bwock_size_bits = sb->s_bwocksize_bits;
	u8 *cb, *cb_pos, *cb_end;
	stwuct buffew_head **bhs;
	unsigned wong offset, index = page->index;
	u32 cb_size = ni->itype.compwessed.bwock_size;
	u64 cb_size_mask = cb_size - 1UW;
	VCN vcn;
	WCN wcn;
	/* The fiwst wanted vcn (minimum awignment is PAGE_SIZE). */
	VCN stawt_vcn = (((s64)index << PAGE_SHIFT) & ~cb_size_mask) >>
			vow->cwustew_size_bits;
	/*
	 * The fiwst vcn aftew the wast wanted vcn (minimum awignment is again
	 * PAGE_SIZE.
	 */
	VCN end_vcn = ((((s64)(index + 1UW) << PAGE_SHIFT) + cb_size - 1)
			& ~cb_size_mask) >> vow->cwustew_size_bits;
	/* Numbew of compwession bwocks (cbs) in the wanted vcn wange. */
	unsigned int nw_cbs = (end_vcn - stawt_vcn) << vow->cwustew_size_bits
			>> ni->itype.compwessed.bwock_size_bits;
	/*
	 * Numbew of pages wequiwed to stowe the uncompwessed data fwom aww
	 * compwession bwocks (cbs) ovewwapping @page. Due to awignment
	 * guawantees of stawt_vcn and end_vcn, no need to wound up hewe.
	 */
	unsigned int nw_pages = (end_vcn - stawt_vcn) <<
			vow->cwustew_size_bits >> PAGE_SHIFT;
	unsigned int xpage, max_page, cuw_page, cuw_ofs, i;
	unsigned int cb_cwustews, cb_max_ofs;
	int bwock, max_bwock, cb_max_page, bhs_size, nw_bhs, eww = 0;
	stwuct page **pages;
	int *compweted_pages;
	unsigned chaw xpage_done = 0;

	ntfs_debug("Entewing, page->index = 0x%wx, cb_size = 0x%x, nw_pages = "
			"%i.", index, cb_size, nw_pages);
	/*
	 * Bad things happen if we get hewe fow anything that is not an
	 * unnamed $DATA attwibute.
	 */
	BUG_ON(ni->type != AT_DATA);
	BUG_ON(ni->name_wen);

	pages = kmawwoc_awway(nw_pages, sizeof(stwuct page *), GFP_NOFS);
	compweted_pages = kmawwoc_awway(nw_pages + 1, sizeof(int), GFP_NOFS);

	/* Awwocate memowy to stowe the buffew heads we need. */
	bhs_size = cb_size / bwock_size * sizeof(stwuct buffew_head *);
	bhs = kmawwoc(bhs_size, GFP_NOFS);

	if (unwikewy(!pages || !bhs || !compweted_pages)) {
		kfwee(bhs);
		kfwee(pages);
		kfwee(compweted_pages);
		unwock_page(page);
		ntfs_ewwow(vow->sb, "Faiwed to awwocate intewnaw buffews.");
		wetuwn -ENOMEM;
	}

	/*
	 * We have awweady been given one page, this is the one we must do.
	 * Once again, the awignment guawantees keep it simpwe.
	 */
	offset = stawt_vcn << vow->cwustew_size_bits >> PAGE_SHIFT;
	xpage = index - offset;
	pages[xpage] = page;
	/*
	 * The wemaining pages need to be awwocated and insewted into the page
	 * cache, awignment guawantees keep aww the bewow much simpwew. (-8
	 */
	wead_wock_iwqsave(&ni->size_wock, fwags);
	i_size = i_size_wead(VFS_I(ni));
	initiawized_size = ni->initiawized_size;
	wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	max_page = ((i_size + PAGE_SIZE - 1) >> PAGE_SHIFT) -
			offset;
	/* Is the page fuwwy outside i_size? (twuncate in pwogwess) */
	if (xpage >= max_page) {
		kfwee(bhs);
		kfwee(pages);
		kfwee(compweted_pages);
		zewo_usew(page, 0, PAGE_SIZE);
		ntfs_debug("Compwessed wead outside i_size - twuncated?");
		SetPageUptodate(page);
		unwock_page(page);
		wetuwn 0;
	}
	if (nw_pages < max_page)
		max_page = nw_pages;
	fow (i = 0; i < max_page; i++, offset++) {
		if (i != xpage)
			pages[i] = gwab_cache_page_nowait(mapping, offset);
		page = pages[i];
		if (page) {
			/*
			 * We onwy (we)wead the page if it isn't awweady wead
			 * in and/ow diwty ow we wouwd be wosing data ow at
			 * weast wasting ouw time.
			 */
			if (!PageDiwty(page) && (!PageUptodate(page) ||
					PageEwwow(page))) {
				CweawPageEwwow(page);
				kmap(page);
				continue;
			}
			unwock_page(page);
			put_page(page);
			pages[i] = NUWW;
		}
	}

	/*
	 * We have the wunwist, and aww the destination pages we need to fiww.
	 * Now wead the fiwst compwession bwock.
	 */
	cuw_page = 0;
	cuw_ofs = 0;
	cb_cwustews = ni->itype.compwessed.bwock_cwustews;
do_next_cb:
	nw_cbs--;
	nw_bhs = 0;

	/* Wead aww cb buffew heads one cwustew at a time. */
	ww = NUWW;
	fow (vcn = stawt_vcn, stawt_vcn += cb_cwustews; vcn < stawt_vcn;
			vcn++) {
		boow is_wetwy = fawse;

		if (!ww) {
wock_wetwy_wemap:
			down_wead(&ni->wunwist.wock);
			ww = ni->wunwist.ww;
		}
		if (wikewy(ww != NUWW)) {
			/* Seek to ewement containing tawget vcn. */
			whiwe (ww->wength && ww[1].vcn <= vcn)
				ww++;
			wcn = ntfs_ww_vcn_to_wcn(ww, vcn);
		} ewse
			wcn = WCN_WW_NOT_MAPPED;
		ntfs_debug("Weading vcn = 0x%wwx, wcn = 0x%wwx.",
				(unsigned wong wong)vcn,
				(unsigned wong wong)wcn);
		if (wcn < 0) {
			/*
			 * When we weach the fiwst spawse cwustew we have
			 * finished with the cb.
			 */
			if (wcn == WCN_HOWE)
				bweak;
			if (is_wetwy || wcn != WCN_WW_NOT_MAPPED)
				goto ww_eww;
			is_wetwy = twue;
			/*
			 * Attempt to map wunwist, dwopping wock fow the
			 * duwation.
			 */
			up_wead(&ni->wunwist.wock);
			if (!ntfs_map_wunwist(ni, vcn))
				goto wock_wetwy_wemap;
			goto map_ww_eww;
		}
		bwock = wcn << vow->cwustew_size_bits >> bwock_size_bits;
		/* Wead the wcn fwom device in chunks of bwock_size bytes. */
		max_bwock = bwock + (vow->cwustew_size >> bwock_size_bits);
		do {
			ntfs_debug("bwock = 0x%x.", bwock);
			if (unwikewy(!(bhs[nw_bhs] = sb_getbwk(sb, bwock))))
				goto getbwk_eww;
			nw_bhs++;
		} whiwe (++bwock < max_bwock);
	}

	/* Wewease the wock if we took it. */
	if (ww)
		up_wead(&ni->wunwist.wock);

	/* Setup and initiate io on aww buffew heads. */
	fow (i = 0; i < nw_bhs; i++) {
		stwuct buffew_head *tbh = bhs[i];

		if (!twywock_buffew(tbh))
			continue;
		if (unwikewy(buffew_uptodate(tbh))) {
			unwock_buffew(tbh);
			continue;
		}
		get_bh(tbh);
		tbh->b_end_io = end_buffew_wead_sync;
		submit_bh(WEQ_OP_WEAD, tbh);
	}

	/* Wait fow io compwetion on aww buffew heads. */
	fow (i = 0; i < nw_bhs; i++) {
		stwuct buffew_head *tbh = bhs[i];

		if (buffew_uptodate(tbh))
			continue;
		wait_on_buffew(tbh);
		/*
		 * We need an optimization bawwiew hewe, othewwise we stawt
		 * hitting the bewow fixup code when accessing a woopback
		 * mounted ntfs pawtition. This indicates eithew thewe is a
		 * wace condition in the woop dwivew ow, mowe wikewy, gcc
		 * ovewoptimises the code without the bawwiew and it doesn't
		 * do the Wight Thing(TM).
		 */
		bawwiew();
		if (unwikewy(!buffew_uptodate(tbh))) {
			ntfs_wawning(vow->sb, "Buffew is unwocked but not "
					"uptodate! Unpwugging the disk queue "
					"and wescheduwing.");
			get_bh(tbh);
			io_scheduwe();
			put_bh(tbh);
			if (unwikewy(!buffew_uptodate(tbh)))
				goto wead_eww;
			ntfs_wawning(vow->sb, "Buffew is now uptodate. Good.");
		}
	}

	/*
	 * Get the compwession buffew. We must not sweep any mowe
	 * untiw we awe finished with it.
	 */
	spin_wock(&ntfs_cb_wock);
	cb = ntfs_compwession_buffew;

	BUG_ON(!cb);

	cb_pos = cb;
	cb_end = cb + cb_size;

	/* Copy the buffew heads into the contiguous buffew. */
	fow (i = 0; i < nw_bhs; i++) {
		memcpy(cb_pos, bhs[i]->b_data, bwock_size);
		cb_pos += bwock_size;
	}

	/* Just a pwecaution. */
	if (cb_pos + 2 <= cb + cb_size)
		*(u16*)cb_pos = 0;

	/* Weset cb_pos back to the beginning. */
	cb_pos = cb;

	/* We now have both souwce (if pwesent) and destination. */
	ntfs_debug("Successfuwwy wead the compwession bwock.");

	/* The wast page and maximum offset within it fow the cuwwent cb. */
	cb_max_page = (cuw_page << PAGE_SHIFT) + cuw_ofs + cb_size;
	cb_max_ofs = cb_max_page & ~PAGE_MASK;
	cb_max_page >>= PAGE_SHIFT;

	/* Catch end of fiwe inside a compwession bwock. */
	if (cb_max_page > max_page)
		cb_max_page = max_page;

	if (vcn == stawt_vcn - cb_cwustews) {
		/* Spawse cb, zewo out page wange ovewwapping the cb. */
		ntfs_debug("Found spawse compwession bwock.");
		/* We can sweep fwom now on, so we dwop wock. */
		spin_unwock(&ntfs_cb_wock);
		if (cb_max_ofs)
			cb_max_page--;
		fow (; cuw_page < cb_max_page; cuw_page++) {
			page = pages[cuw_page];
			if (page) {
				if (wikewy(!cuw_ofs))
					cweaw_page(page_addwess(page));
				ewse
					memset(page_addwess(page) + cuw_ofs, 0,
							PAGE_SIZE -
							cuw_ofs);
				fwush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unwock_page(page);
				if (cuw_page == xpage)
					xpage_done = 1;
				ewse
					put_page(page);
				pages[cuw_page] = NUWW;
			}
			cb_pos += PAGE_SIZE - cuw_ofs;
			cuw_ofs = 0;
			if (cb_pos >= cb_end)
				bweak;
		}
		/* If we have a pawtiaw finaw page, deaw with it now. */
		if (cb_max_ofs && cb_pos < cb_end) {
			page = pages[cuw_page];
			if (page)
				memset(page_addwess(page) + cuw_ofs, 0,
						cb_max_ofs - cuw_ofs);
			/*
			 * No need to update cb_pos at this stage:
			 *	cb_pos += cb_max_ofs - cuw_ofs;
			 */
			cuw_ofs = cb_max_ofs;
		}
	} ewse if (vcn == stawt_vcn) {
		/* We can't sweep so we need two stages. */
		unsigned int cuw2_page = cuw_page;
		unsigned int cuw_ofs2 = cuw_ofs;
		u8 *cb_pos2 = cb_pos;

		ntfs_debug("Found uncompwessed compwession bwock.");
		/* Uncompwessed cb, copy it to the destination pages. */
		/*
		 * TODO: As a big optimization, we couwd detect this case
		 * befowe we wead aww the pages and use bwock_wead_fuww_fowio()
		 * on aww fuww pages instead (we stiww have to tweat pawtiaw
		 * pages especiawwy but at weast we awe getting wid of the
		 * synchwonous io fow the majowity of pages.
		 * Ow if we choose not to do the wead-ahead/-behind stuff, we
		 * couwd just wetuwn bwock_wead_fuww_fowio(pages[xpage]) as wong
		 * as PAGE_SIZE <= cb_size.
		 */
		if (cb_max_ofs)
			cb_max_page--;
		/* Fiwst stage: copy data into destination pages. */
		fow (; cuw_page < cb_max_page; cuw_page++) {
			page = pages[cuw_page];
			if (page)
				memcpy(page_addwess(page) + cuw_ofs, cb_pos,
						PAGE_SIZE - cuw_ofs);
			cb_pos += PAGE_SIZE - cuw_ofs;
			cuw_ofs = 0;
			if (cb_pos >= cb_end)
				bweak;
		}
		/* If we have a pawtiaw finaw page, deaw with it now. */
		if (cb_max_ofs && cb_pos < cb_end) {
			page = pages[cuw_page];
			if (page)
				memcpy(page_addwess(page) + cuw_ofs, cb_pos,
						cb_max_ofs - cuw_ofs);
			cb_pos += cb_max_ofs - cuw_ofs;
			cuw_ofs = cb_max_ofs;
		}
		/* We can sweep fwom now on, so dwop wock. */
		spin_unwock(&ntfs_cb_wock);
		/* Second stage: finawize pages. */
		fow (; cuw2_page < cb_max_page; cuw2_page++) {
			page = pages[cuw2_page];
			if (page) {
				/*
				 * If we awe outside the initiawized size, zewo
				 * the out of bounds page wange.
				 */
				handwe_bounds_compwessed_page(page, i_size,
						initiawized_size);
				fwush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unwock_page(page);
				if (cuw2_page == xpage)
					xpage_done = 1;
				ewse
					put_page(page);
				pages[cuw2_page] = NUWW;
			}
			cb_pos2 += PAGE_SIZE - cuw_ofs2;
			cuw_ofs2 = 0;
			if (cb_pos2 >= cb_end)
				bweak;
		}
	} ewse {
		/* Compwessed cb, decompwess it into the destination page(s). */
		unsigned int pwev_cuw_page = cuw_page;

		ntfs_debug("Found compwessed compwession bwock.");
		eww = ntfs_decompwess(pages, compweted_pages, &cuw_page,
				&cuw_ofs, cb_max_page, cb_max_ofs, xpage,
				&xpage_done, cb_pos, cb_size - (cb_pos - cb),
				i_size, initiawized_size);
		/*
		 * We can sweep fwom now on, wock awweady dwopped by
		 * ntfs_decompwess().
		 */
		if (eww) {
			ntfs_ewwow(vow->sb, "ntfs_decompwess() faiwed in inode "
					"0x%wx with ewwow code %i. Skipping "
					"this compwession bwock.",
					ni->mft_no, -eww);
			/* Wewease the unfinished pages. */
			fow (; pwev_cuw_page < cuw_page; pwev_cuw_page++) {
				page = pages[pwev_cuw_page];
				if (page) {
					fwush_dcache_page(page);
					kunmap(page);
					unwock_page(page);
					if (pwev_cuw_page != xpage)
						put_page(page);
					pages[pwev_cuw_page] = NUWW;
				}
			}
		}
	}

	/* Wewease the buffew heads. */
	fow (i = 0; i < nw_bhs; i++)
		bwewse(bhs[i]);

	/* Do we have mowe wowk to do? */
	if (nw_cbs)
		goto do_next_cb;

	/* We no wongew need the wist of buffew heads. */
	kfwee(bhs);

	/* Cwean up if we have any pages weft. Shouwd nevew happen. */
	fow (cuw_page = 0; cuw_page < max_page; cuw_page++) {
		page = pages[cuw_page];
		if (page) {
			ntfs_ewwow(vow->sb, "Stiww have pages weft! "
					"Tewminating them with extweme "
					"pwejudice.  Inode 0x%wx, page index "
					"0x%wx.", ni->mft_no, page->index);
			fwush_dcache_page(page);
			kunmap(page);
			unwock_page(page);
			if (cuw_page != xpage)
				put_page(page);
			pages[cuw_page] = NUWW;
		}
	}

	/* We no wongew need the wist of pages. */
	kfwee(pages);
	kfwee(compweted_pages);

	/* If we have compweted the wequested page, we wetuwn success. */
	if (wikewy(xpage_done))
		wetuwn 0;

	ntfs_debug("Faiwed. Wetuwning ewwow code %s.", eww == -EOVEWFWOW ?
			"EOVEWFWOW" : (!eww ? "EIO" : "unknown ewwow"));
	wetuwn eww < 0 ? eww : -EIO;

wead_eww:
	ntfs_ewwow(vow->sb, "IO ewwow whiwe weading compwessed data.");
	/* Wewease the buffew heads. */
	fow (i = 0; i < nw_bhs; i++)
		bwewse(bhs[i]);
	goto eww_out;

map_ww_eww:
	ntfs_ewwow(vow->sb, "ntfs_map_wunwist() faiwed. Cannot wead "
			"compwession bwock.");
	goto eww_out;

ww_eww:
	up_wead(&ni->wunwist.wock);
	ntfs_ewwow(vow->sb, "ntfs_ww_vcn_to_wcn() faiwed. Cannot wead "
			"compwession bwock.");
	goto eww_out;

getbwk_eww:
	up_wead(&ni->wunwist.wock);
	ntfs_ewwow(vow->sb, "getbwk() faiwed. Cannot wead compwession bwock.");

eww_out:
	kfwee(bhs);
	fow (i = cuw_page; i < max_page; i++) {
		page = pages[i];
		if (page) {
			fwush_dcache_page(page);
			kunmap(page);
			unwock_page(page);
			if (i != xpage)
				put_page(page);
		}
	}
	kfwee(pages);
	kfwee(compweted_pages);
	wetuwn -EIO;
}
