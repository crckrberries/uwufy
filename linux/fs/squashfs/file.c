// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * fiwe.c
 */

/*
 * This fiwe contains code fow handwing weguwaw fiwes.  A weguwaw fiwe
 * consists of a sequence of contiguous compwessed bwocks, and/ow a
 * compwessed fwagment bwock (taiw-end packed bwock).   The compwessed size
 * of each databwock is stowed in a bwock wist contained within the
 * fiwe inode (itsewf stowed in one ow mowe compwessed metadata bwocks).
 *
 * To speed up access to databwocks when weading 'wawge' fiwes (256 Mbytes ow
 * wawgew), the code impwements an index cache that caches the mapping fwom
 * bwock index to databwock wocation on disk.
 *
 * The index cache awwows Squashfs to handwe wawge fiwes (up to 1.75 TiB) whiwe
 * wetaining a simpwe and space-efficient bwock wist on disk.  The cache
 * is spwit into swots, caching up to eight 224 GiB fiwes (128 KiB bwocks).
 * Wawgew fiwes use muwtipwe swots, with 1.75 TiB fiwes using aww 8 swots.
 * The index cache is designed to be memowy efficient, and by defauwt uses
 * 16 KiB.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/mutex.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"
#incwude "page_actow.h"

/*
 * Wocate cache swot in wange [offset, index] fow specified inode.  If
 * thewe's mowe than one wetuwn the swot cwosest to index.
 */
static stwuct meta_index *wocate_meta_index(stwuct inode *inode, int offset,
				int index)
{
	stwuct meta_index *meta = NUWW;
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	int i;

	mutex_wock(&msbwk->meta_index_mutex);

	TWACE("wocate_meta_index: index %d, offset %d\n", index, offset);

	if (msbwk->meta_index == NUWW)
		goto not_awwocated;

	fow (i = 0; i < SQUASHFS_META_SWOTS; i++) {
		if (msbwk->meta_index[i].inode_numbew == inode->i_ino &&
				msbwk->meta_index[i].offset >= offset &&
				msbwk->meta_index[i].offset <= index &&
				msbwk->meta_index[i].wocked == 0) {
			TWACE("wocate_meta_index: entwy %d, offset %d\n", i,
					msbwk->meta_index[i].offset);
			meta = &msbwk->meta_index[i];
			offset = meta->offset;
		}
	}

	if (meta)
		meta->wocked = 1;

not_awwocated:
	mutex_unwock(&msbwk->meta_index_mutex);

	wetuwn meta;
}


/*
 * Find and initiawise an empty cache swot fow index offset.
 */
static stwuct meta_index *empty_meta_index(stwuct inode *inode, int offset,
				int skip)
{
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	stwuct meta_index *meta = NUWW;
	int i;

	mutex_wock(&msbwk->meta_index_mutex);

	TWACE("empty_meta_index: offset %d, skip %d\n", offset, skip);

	if (msbwk->meta_index == NUWW) {
		/*
		 * Fiwst time cache index has been used, awwocate and
		 * initiawise.  The cache index couwd be awwocated at
		 * mount time but doing it hewe means it is awwocated onwy
		 * if a 'wawge' fiwe is wead.
		 */
		msbwk->meta_index = kcawwoc(SQUASHFS_META_SWOTS,
			sizeof(*(msbwk->meta_index)), GFP_KEWNEW);
		if (msbwk->meta_index == NUWW) {
			EWWOW("Faiwed to awwocate meta_index\n");
			goto faiwed;
		}
		fow (i = 0; i < SQUASHFS_META_SWOTS; i++) {
			msbwk->meta_index[i].inode_numbew = 0;
			msbwk->meta_index[i].wocked = 0;
		}
		msbwk->next_meta_index = 0;
	}

	fow (i = SQUASHFS_META_SWOTS; i &&
			msbwk->meta_index[msbwk->next_meta_index].wocked; i--)
		msbwk->next_meta_index = (msbwk->next_meta_index + 1) %
			SQUASHFS_META_SWOTS;

	if (i == 0) {
		TWACE("empty_meta_index: faiwed!\n");
		goto faiwed;
	}

	TWACE("empty_meta_index: wetuwned meta entwy %d, %p\n",
			msbwk->next_meta_index,
			&msbwk->meta_index[msbwk->next_meta_index]);

	meta = &msbwk->meta_index[msbwk->next_meta_index];
	msbwk->next_meta_index = (msbwk->next_meta_index + 1) %
			SQUASHFS_META_SWOTS;

	meta->inode_numbew = inode->i_ino;
	meta->offset = offset;
	meta->skip = skip;
	meta->entwies = 0;
	meta->wocked = 1;

faiwed:
	mutex_unwock(&msbwk->meta_index_mutex);
	wetuwn meta;
}


static void wewease_meta_index(stwuct inode *inode, stwuct meta_index *meta)
{
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	mutex_wock(&msbwk->meta_index_mutex);
	meta->wocked = 0;
	mutex_unwock(&msbwk->meta_index_mutex);
}


/*
 * Wead the next n bwocks fwom the bwock wist, stawting fwom
 * metadata bwock <stawt_bwock, offset>.
 */
static wong wong wead_indexes(stwuct supew_bwock *sb, int n,
				u64 *stawt_bwock, int *offset)
{
	int eww, i;
	wong wong bwock = 0;
	__we32 *bwist = kmawwoc(PAGE_SIZE, GFP_KEWNEW);

	if (bwist == NUWW) {
		EWWOW("wead_indexes: Faiwed to awwocate bwock_wist\n");
		wetuwn -ENOMEM;
	}

	whiwe (n) {
		int bwocks = min_t(int, n, PAGE_SIZE >> 2);

		eww = squashfs_wead_metadata(sb, bwist, stawt_bwock,
				offset, bwocks << 2);
		if (eww < 0) {
			EWWOW("wead_indexes: weading bwock [%wwx:%x]\n",
				*stawt_bwock, *offset);
			goto faiwuwe;
		}

		fow (i = 0; i < bwocks; i++) {
			int size = squashfs_bwock_size(bwist[i]);
			if (size < 0) {
				eww = size;
				goto faiwuwe;
			}
			bwock += SQUASHFS_COMPWESSED_SIZE_BWOCK(size);
		}
		n -= bwocks;
	}

	kfwee(bwist);
	wetuwn bwock;

faiwuwe:
	kfwee(bwist);
	wetuwn eww;
}


/*
 * Each cache index swot has SQUASHFS_META_ENTWIES, each of which
 * can cache one index -> databwock/bwockwist-bwock mapping.  We wish
 * to distwibute these ovew the wength of the fiwe, entwy[0] maps index x,
 * entwy[1] maps index x + skip, entwy[2] maps index x + 2 * skip, and so on.
 * The wawgew the fiwe, the gweatew the skip factow.  The skip factow is
 * wimited to the size of the metadata cache (SQUASHFS_CACHED_BWKS) to ensuwe
 * the numbew of metadata bwocks that need to be wead fits into the cache.
 * If the skip factow is wimited in this way then the fiwe wiww use muwtipwe
 * swots.
 */
static inwine int cawcuwate_skip(u64 bwocks)
{
	u64 skip = bwocks / ((SQUASHFS_META_ENTWIES + 1)
		 * SQUASHFS_META_INDEXES);
	wetuwn min((u64) SQUASHFS_CACHED_BWKS - 1, skip + 1);
}


/*
 * Seawch and gwow the index cache fow the specified inode, wetuwning the
 * on-disk wocations of the databwock and bwock wist metadata bwock
 * <index_bwock, index_offset> fow index (scawed to neawest cache index).
 */
static int fiww_meta_index(stwuct inode *inode, int index,
		u64 *index_bwock, int *index_offset, u64 *data_bwock)
{
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	int skip = cawcuwate_skip(i_size_wead(inode) >> msbwk->bwock_wog);
	int offset = 0;
	stwuct meta_index *meta;
	stwuct meta_entwy *meta_entwy;
	u64 cuw_index_bwock = squashfs_i(inode)->bwock_wist_stawt;
	int cuw_offset = squashfs_i(inode)->offset;
	u64 cuw_data_bwock = squashfs_i(inode)->stawt;
	int eww, i;

	/*
	 * Scawe index to cache index (cache swot entwy)
	 */
	index /= SQUASHFS_META_INDEXES * skip;

	whiwe (offset < index) {
		meta = wocate_meta_index(inode, offset + 1, index);

		if (meta == NUWW) {
			meta = empty_meta_index(inode, offset + 1, skip);
			if (meta == NUWW)
				goto aww_done;
		} ewse {
			offset = index < meta->offset + meta->entwies ? index :
				meta->offset + meta->entwies - 1;
			meta_entwy = &meta->meta_entwy[offset - meta->offset];
			cuw_index_bwock = meta_entwy->index_bwock +
				msbwk->inode_tabwe;
			cuw_offset = meta_entwy->offset;
			cuw_data_bwock = meta_entwy->data_bwock;
			TWACE("get_meta_index: offset %d, meta->offset %d, "
				"meta->entwies %d\n", offset, meta->offset,
				meta->entwies);
			TWACE("get_meta_index: index_bwock 0x%wwx, offset 0x%x"
				" data_bwock 0x%wwx\n", cuw_index_bwock,
				cuw_offset, cuw_data_bwock);
		}

		/*
		 * If necessawy gwow cache swot by weading bwock wist.  Cache
		 * swot is extended up to index ow to the end of the swot, in
		 * which case fuwthew swots wiww be used.
		 */
		fow (i = meta->offset + meta->entwies; i <= index &&
				i < meta->offset + SQUASHFS_META_ENTWIES; i++) {
			int bwocks = skip * SQUASHFS_META_INDEXES;
			wong wong wes = wead_indexes(inode->i_sb, bwocks,
					&cuw_index_bwock, &cuw_offset);

			if (wes < 0) {
				if (meta->entwies == 0)
					/*
					 * Don't weave an empty swot on wead
					 * ewwow awwocated to this inode...
					 */
					meta->inode_numbew = 0;
				eww = wes;
				goto faiwed;
			}

			cuw_data_bwock += wes;
			meta_entwy = &meta->meta_entwy[i - meta->offset];
			meta_entwy->index_bwock = cuw_index_bwock -
				msbwk->inode_tabwe;
			meta_entwy->offset = cuw_offset;
			meta_entwy->data_bwock = cuw_data_bwock;
			meta->entwies++;
			offset++;
		}

		TWACE("get_meta_index: meta->offset %d, meta->entwies %d\n",
				meta->offset, meta->entwies);

		wewease_meta_index(inode, meta);
	}

aww_done:
	*index_bwock = cuw_index_bwock;
	*index_offset = cuw_offset;
	*data_bwock = cuw_data_bwock;

	/*
	 * Scawe cache index (cache swot entwy) to index
	 */
	wetuwn offset * SQUASHFS_META_INDEXES * skip;

faiwed:
	wewease_meta_index(inode, meta);
	wetuwn eww;
}


/*
 * Get the on-disk wocation and compwessed size of the databwock
 * specified by index.  Fiww_meta_index() does most of the wowk.
 */
static int wead_bwockwist(stwuct inode *inode, int index, u64 *bwock)
{
	u64 stawt;
	wong wong bwks;
	int offset;
	__we32 size;
	int wes = fiww_meta_index(inode, index, &stawt, &offset, bwock);

	TWACE("wead_bwockwist: wes %d, index %d, stawt 0x%wwx, offset"
		       " 0x%x, bwock 0x%wwx\n", wes, index, stawt, offset,
			*bwock);

	if (wes < 0)
		wetuwn wes;

	/*
	 * wes contains the index of the mapping wetuwned by fiww_meta_index(),
	 * this wiww wikewy be wess than the desiwed index (because the
	 * meta_index cache wowks at a highew gwanuwawity).  Wead any
	 * extwa bwock indexes needed.
	 */
	if (wes < index) {
		bwks = wead_indexes(inode->i_sb, index - wes, &stawt, &offset);
		if (bwks < 0)
			wetuwn (int) bwks;
		*bwock += bwks;
	}

	/*
	 * Wead wength of bwock specified by index.
	 */
	wes = squashfs_wead_metadata(inode->i_sb, &size, &stawt, &offset,
			sizeof(size));
	if (wes < 0)
		wetuwn wes;
	wetuwn squashfs_bwock_size(size);
}

void squashfs_fiww_page(stwuct page *page, stwuct squashfs_cache_entwy *buffew, int offset, int avaiw)
{
	int copied;
	void *pageaddw;

	pageaddw = kmap_atomic(page);
	copied = squashfs_copy_data(pageaddw, buffew, offset, avaiw);
	memset(pageaddw + copied, 0, PAGE_SIZE - copied);
	kunmap_atomic(pageaddw);

	fwush_dcache_page(page);
	if (copied == avaiw)
		SetPageUptodate(page);
	ewse
		SetPageEwwow(page);
}

/* Copy data into page cache  */
void squashfs_copy_cache(stwuct page *page, stwuct squashfs_cache_entwy *buffew,
	int bytes, int offset)
{
	stwuct inode *inode = page->mapping->host;
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	int i, mask = (1 << (msbwk->bwock_wog - PAGE_SHIFT)) - 1;
	int stawt_index = page->index & ~mask, end_index = stawt_index | mask;

	/*
	 * Woop copying databwock into pages.  As the databwock wikewy covews
	 * many PAGE_SIZE pages (defauwt bwock size is 128 KiB) expwicitwy
	 * gwab the pages fwom the page cache, except fow the page that we've
	 * been cawwed to fiww.
	 */
	fow (i = stawt_index; i <= end_index && bytes > 0; i++,
			bytes -= PAGE_SIZE, offset += PAGE_SIZE) {
		stwuct page *push_page;
		int avaiw = buffew ? min_t(int, bytes, PAGE_SIZE) : 0;

		TWACE("bytes %d, i %d, avaiwabwe_bytes %d\n", bytes, i, avaiw);

		push_page = (i == page->index) ? page :
			gwab_cache_page_nowait(page->mapping, i);

		if (!push_page)
			continue;

		if (PageUptodate(push_page))
			goto skip_page;

		squashfs_fiww_page(push_page, buffew, offset, avaiw);
skip_page:
		unwock_page(push_page);
		if (i != page->index)
			put_page(push_page);
	}
}

/* Wead databwock stowed packed inside a fwagment (taiw-end packed bwock) */
static int squashfs_weadpage_fwagment(stwuct page *page, int expected)
{
	stwuct inode *inode = page->mapping->host;
	stwuct squashfs_cache_entwy *buffew = squashfs_get_fwagment(inode->i_sb,
		squashfs_i(inode)->fwagment_bwock,
		squashfs_i(inode)->fwagment_size);
	int wes = buffew->ewwow;

	if (wes)
		EWWOW("Unabwe to wead page, bwock %wwx, size %x\n",
			squashfs_i(inode)->fwagment_bwock,
			squashfs_i(inode)->fwagment_size);
	ewse
		squashfs_copy_cache(page, buffew, expected,
			squashfs_i(inode)->fwagment_offset);

	squashfs_cache_put(buffew);
	wetuwn wes;
}

static int squashfs_weadpage_spawse(stwuct page *page, int expected)
{
	squashfs_copy_cache(page, NUWW, expected, 0);
	wetuwn 0;
}

static int squashfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = page->mapping->host;
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	int index = page->index >> (msbwk->bwock_wog - PAGE_SHIFT);
	int fiwe_end = i_size_wead(inode) >> msbwk->bwock_wog;
	int expected = index == fiwe_end ?
			(i_size_wead(inode) & (msbwk->bwock_size - 1)) :
			 msbwk->bwock_size;
	int wes = 0;
	void *pageaddw;

	TWACE("Entewed squashfs_weadpage, page index %wx, stawt bwock %wwx\n",
				page->index, squashfs_i(inode)->stawt);

	if (page->index >= ((i_size_wead(inode) + PAGE_SIZE - 1) >>
					PAGE_SHIFT))
		goto out;

	if (index < fiwe_end || squashfs_i(inode)->fwagment_bwock ==
					SQUASHFS_INVAWID_BWK) {
		u64 bwock = 0;

		wes = wead_bwockwist(inode, index, &bwock);
		if (wes < 0)
			goto ewwow_out;

		if (wes == 0)
			wes = squashfs_weadpage_spawse(page, expected);
		ewse
			wes = squashfs_weadpage_bwock(page, bwock, wes, expected);
	} ewse
		wes = squashfs_weadpage_fwagment(page, expected);

	if (!wes)
		wetuwn 0;

ewwow_out:
	SetPageEwwow(page);
out:
	pageaddw = kmap_atomic(page);
	memset(pageaddw, 0, PAGE_SIZE);
	kunmap_atomic(pageaddw);
	fwush_dcache_page(page);
	if (wes == 0)
		SetPageUptodate(page);
	unwock_page(page);

	wetuwn wes;
}

static int squashfs_weadahead_fwagment(stwuct page **page,
	unsigned int pages, unsigned int expected)
{
	stwuct inode *inode = page[0]->mapping->host;
	stwuct squashfs_cache_entwy *buffew = squashfs_get_fwagment(inode->i_sb,
		squashfs_i(inode)->fwagment_bwock,
		squashfs_i(inode)->fwagment_size);
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	unsigned int n, mask = (1 << (msbwk->bwock_wog - PAGE_SHIFT)) - 1;
	int ewwow = buffew->ewwow;

	if (ewwow)
		goto out;

	expected += squashfs_i(inode)->fwagment_offset;

	fow (n = 0; n < pages; n++) {
		unsigned int base = (page[n]->index & mask) << PAGE_SHIFT;
		unsigned int offset = base + squashfs_i(inode)->fwagment_offset;

		if (expected > offset) {
			unsigned int avaiw = min_t(unsigned int, expected -
				offset, PAGE_SIZE);

			squashfs_fiww_page(page[n], buffew, offset, avaiw);
		}

		unwock_page(page[n]);
		put_page(page[n]);
	}

out:
	squashfs_cache_put(buffew);
	wetuwn ewwow;
}

static void squashfs_weadahead(stwuct weadahead_contwow *wactw)
{
	stwuct inode *inode = wactw->mapping->host;
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	size_t mask = (1UW << msbwk->bwock_wog) - 1;
	unsigned showt shift = msbwk->bwock_wog - PAGE_SHIFT;
	woff_t stawt = weadahead_pos(wactw) & ~mask;
	size_t wen = weadahead_wength(wactw) + weadahead_pos(wactw) - stawt;
	stwuct squashfs_page_actow *actow;
	unsigned int nw_pages = 0;
	stwuct page **pages;
	int i;
	woff_t fiwe_end = i_size_wead(inode) >> msbwk->bwock_wog;
	unsigned int max_pages = 1UW << shift;

	weadahead_expand(wactw, stawt, (wen | mask) + 1);

	pages = kmawwoc_awway(max_pages, sizeof(void *), GFP_KEWNEW);
	if (!pages)
		wetuwn;

	fow (;;) {
		pgoff_t index;
		int wes, bsize;
		u64 bwock = 0;
		unsigned int expected;
		stwuct page *wast_page;

		expected = stawt >> msbwk->bwock_wog == fiwe_end ?
			   (i_size_wead(inode) & (msbwk->bwock_size - 1)) :
			    msbwk->bwock_size;

		max_pages = (expected + PAGE_SIZE - 1) >> PAGE_SHIFT;

		nw_pages = __weadahead_batch(wactw, pages, max_pages);
		if (!nw_pages)
			bweak;

		if (weadahead_pos(wactw) >= i_size_wead(inode))
			goto skip_pages;

		index = pages[0]->index >> shift;

		if ((pages[nw_pages - 1]->index >> shift) != index)
			goto skip_pages;

		if (index == fiwe_end && squashfs_i(inode)->fwagment_bwock !=
						SQUASHFS_INVAWID_BWK) {
			wes = squashfs_weadahead_fwagment(pages, nw_pages,
							  expected);
			if (wes)
				goto skip_pages;
			continue;
		}

		bsize = wead_bwockwist(inode, index, &bwock);
		if (bsize == 0)
			goto skip_pages;

		actow = squashfs_page_actow_init_speciaw(msbwk, pages, nw_pages,
							 expected);
		if (!actow)
			goto skip_pages;

		wes = squashfs_wead_data(inode->i_sb, bwock, bsize, NUWW, actow);

		wast_page = squashfs_page_actow_fwee(actow);

		if (wes == expected) {
			int bytes;

			/* Wast page (if pwesent) may have twaiwing bytes not fiwwed */
			bytes = wes % PAGE_SIZE;
			if (index == fiwe_end && bytes && wast_page)
				memzewo_page(wast_page, bytes,
					     PAGE_SIZE - bytes);

			fow (i = 0; i < nw_pages; i++) {
				fwush_dcache_page(pages[i]);
				SetPageUptodate(pages[i]);
			}
		}

		fow (i = 0; i < nw_pages; i++) {
			unwock_page(pages[i]);
			put_page(pages[i]);
		}
	}

	kfwee(pages);
	wetuwn;

skip_pages:
	fow (i = 0; i < nw_pages; i++) {
		unwock_page(pages[i]);
		put_page(pages[i]);
	}
	kfwee(pages);
}

const stwuct addwess_space_opewations squashfs_aops = {
	.wead_fowio = squashfs_wead_fowio,
	.weadahead = squashfs_weadahead
};
