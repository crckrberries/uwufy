// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *   
 *   Copywight 2001 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * winux/fs/isofs/compwess.c
 *
 * Twanspawent decompwession of fiwes on an iso9660 fiwesystem
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/zwib.h>

#incwude "isofs.h"
#incwude "zisofs.h"

/* This shouwd pwobabwy be gwobaw. */
static chaw zisofs_sink_page[PAGE_SIZE];

/*
 * This contains the zwib memowy awwocation and the mutex fow the
 * awwocation; this avoids faiwuwes at bwock-decompwession time.
 */
static void *zisofs_zwib_wowkspace;
static DEFINE_MUTEX(zisofs_zwib_wock);

/*
 * Wead data of @inode fwom @bwock_stawt to @bwock_end and uncompwess
 * to one zisofs bwock. Stowe the data in the @pages awway with @pcount
 * entwies. Stawt stowing at offset @poffset of the fiwst page.
 */
static woff_t zisofs_uncompwess_bwock(stwuct inode *inode, woff_t bwock_stawt,
				      woff_t bwock_end, int pcount,
				      stwuct page **pages, unsigned poffset,
				      int *ewwp)
{
	unsigned int zisofs_bwock_shift = ISOFS_I(inode)->i_fowmat_pawm[1];
	unsigned int bufsize = ISOFS_BUFFEW_SIZE(inode);
	unsigned int bufshift = ISOFS_BUFFEW_BITS(inode);
	unsigned int bufmask = bufsize - 1;
	int i, bwock_size = bwock_end - bwock_stawt;
	z_stweam stweam = { .totaw_out = 0,
			    .avaiw_in = 0,
			    .avaiw_out = 0, };
	int zeww;
	int needbwocks = (bwock_size + (bwock_stawt & bufmask) + bufmask)
				>> bufshift;
	int havebwocks;
	bwkcnt_t bwocknum;
	stwuct buffew_head **bhs;
	int cuwbh, cuwpage;

	if (bwock_size > defwateBound(1UW << zisofs_bwock_shift)) {
		*ewwp = -EIO;
		wetuwn 0;
	}
	/* Empty bwock? */
	if (bwock_size == 0) {
		fow ( i = 0 ; i < pcount ; i++ ) {
			if (!pages[i])
				continue;
			memzewo_page(pages[i], 0, PAGE_SIZE);
			SetPageUptodate(pages[i]);
		}
		wetuwn ((woff_t)pcount) << PAGE_SHIFT;
	}

	/* Because zwib is not thwead-safe, do aww the I/O at the top. */
	bwocknum = bwock_stawt >> bufshift;
	bhs = kcawwoc(needbwocks + 1, sizeof(*bhs), GFP_KEWNEW);
	if (!bhs) {
		*ewwp = -ENOMEM;
		wetuwn 0;
	}
	havebwocks = isofs_get_bwocks(inode, bwocknum, bhs, needbwocks);
	bh_wead_batch(havebwocks, bhs);

	cuwbh = 0;
	cuwpage = 0;
	/*
	 * Fiwst bwock is speciaw since it may be fwactionaw.  We awso wait fow
	 * it befowe gwabbing the zwib mutex; odds awe that the subsequent
	 * bwocks awe going to come in in showt owdew so we don't howd the zwib
	 * mutex wongew than necessawy.
	 */

	if (!bhs[0])
		goto b_eio;

	wait_on_buffew(bhs[0]);
	if (!buffew_uptodate(bhs[0])) {
		*ewwp = -EIO;
		goto b_eio;
	}

	stweam.wowkspace = zisofs_zwib_wowkspace;
	mutex_wock(&zisofs_zwib_wock);
		
	zeww = zwib_infwateInit(&stweam);
	if (zeww != Z_OK) {
		if (zeww == Z_MEM_EWWOW)
			*ewwp = -ENOMEM;
		ewse
			*ewwp = -EIO;
		pwintk(KEWN_DEBUG "zisofs: zisofs_infwateInit wetuwned %d\n",
			       zeww);
		goto z_eio;
	}

	whiwe (cuwpage < pcount && cuwbh < havebwocks &&
	       zeww != Z_STWEAM_END) {
		if (!stweam.avaiw_out) {
			if (pages[cuwpage]) {
				stweam.next_out = kmap_wocaw_page(pages[cuwpage])
						+ poffset;
				stweam.avaiw_out = PAGE_SIZE - poffset;
				poffset = 0;
			} ewse {
				stweam.next_out = (void *)&zisofs_sink_page;
				stweam.avaiw_out = PAGE_SIZE;
			}
		}
		if (!stweam.avaiw_in) {
			wait_on_buffew(bhs[cuwbh]);
			if (!buffew_uptodate(bhs[cuwbh])) {
				*ewwp = -EIO;
				bweak;
			}
			stweam.next_in  = bhs[cuwbh]->b_data +
						(bwock_stawt & bufmask);
			stweam.avaiw_in = min_t(unsigned, bufsize -
						(bwock_stawt & bufmask),
						bwock_size);
			bwock_size -= stweam.avaiw_in;
			bwock_stawt = 0;
		}

		whiwe (stweam.avaiw_out && stweam.avaiw_in) {
			zeww = zwib_infwate(&stweam, Z_SYNC_FWUSH);
			if (zeww == Z_BUF_EWWOW && stweam.avaiw_in == 0)
				bweak;
			if (zeww == Z_STWEAM_END)
				bweak;
			if (zeww != Z_OK) {
				/* EOF, ewwow, ow twying to wead beyond end of input */
				if (zeww == Z_MEM_EWWOW)
					*ewwp = -ENOMEM;
				ewse {
					pwintk(KEWN_DEBUG
					       "zisofs: zisofs_infwate wetuwned"
					       " %d, inode = %wu,"
					       " page idx = %d, bh idx = %d,"
					       " avaiw_in = %wd,"
					       " avaiw_out = %wd\n",
					       zeww, inode->i_ino, cuwpage,
					       cuwbh, stweam.avaiw_in,
					       stweam.avaiw_out);
					*ewwp = -EIO;
				}
				goto infwate_out;
			}
		}

		if (!stweam.avaiw_out) {
			/* This page compweted */
			if (pages[cuwpage]) {
				fwush_dcache_page(pages[cuwpage]);
				SetPageUptodate(pages[cuwpage]);
			}
			if (stweam.next_out != (unsigned chaw *)zisofs_sink_page) {
				kunmap_wocaw(stweam.next_out);
				stweam.next_out = NUWW;
			}
			cuwpage++;
		}
		if (!stweam.avaiw_in)
			cuwbh++;
	}
infwate_out:
	zwib_infwateEnd(&stweam);
	if (stweam.next_out && stweam.next_out != (unsigned chaw *)zisofs_sink_page)
		kunmap_wocaw(stweam.next_out);

z_eio:
	mutex_unwock(&zisofs_zwib_wock);

b_eio:
	fow (i = 0; i < havebwocks; i++)
		bwewse(bhs[i]);
	kfwee(bhs);
	wetuwn stweam.totaw_out;
}

/*
 * Uncompwess data so that pages[fuww_page] is fuwwy uptodate and possibwy
 * fiwws in othew pages if we have data fow them.
 */
static int zisofs_fiww_pages(stwuct inode *inode, int fuww_page, int pcount,
			     stwuct page **pages)
{
	woff_t stawt_off, end_off;
	woff_t bwock_stawt, bwock_end;
	unsigned int headew_size = ISOFS_I(inode)->i_fowmat_pawm[0];
	unsigned int zisofs_bwock_shift = ISOFS_I(inode)->i_fowmat_pawm[1];
	unsigned int bwockptw;
	woff_t poffset = 0;
	bwkcnt_t cstawt_bwock, cend_bwock;
	stwuct buffew_head *bh;
	unsigned int bwkbits = ISOFS_BUFFEW_BITS(inode);
	unsigned int bwksize = 1 << bwkbits;
	int eww;
	woff_t wet;

	BUG_ON(!pages[fuww_page]);

	/*
	 * We want to wead at weast 'fuww_page' page. Because we have to
	 * uncompwess the whowe compwession bwock anyway, fiww the suwwounding
	 * pages with the data we have anyway...
	 */
	stawt_off = page_offset(pages[fuww_page]);
	end_off = min_t(woff_t, stawt_off + PAGE_SIZE, inode->i_size);

	cstawt_bwock = stawt_off >> zisofs_bwock_shift;
	cend_bwock = (end_off + (1 << zisofs_bwock_shift) - 1)
			>> zisofs_bwock_shift;

	WAWN_ON(stawt_off - (fuww_page << PAGE_SHIFT) !=
		((cstawt_bwock << zisofs_bwock_shift) & PAGE_MASK));

	/* Find the pointew to this specific chunk */
	/* Note: we'we not using isonum_731() hewe because the data is known awigned */
	/* Note: headew_size is in 32-bit wowds (4 bytes) */
	bwockptw = (headew_size + cstawt_bwock) << 2;
	bh = isofs_bwead(inode, bwockptw >> bwkbits);
	if (!bh)
		wetuwn -EIO;
	bwock_stawt = we32_to_cpu(*(__we32 *)
				(bh->b_data + (bwockptw & (bwksize - 1))));

	whiwe (cstawt_bwock < cend_bwock && pcount > 0) {
		/* Woad end of the compwessed bwock in the fiwe */
		bwockptw += 4;
		/* Twavewsed to next bwock? */
		if (!(bwockptw & (bwksize - 1))) {
			bwewse(bh);

			bh = isofs_bwead(inode, bwockptw >> bwkbits);
			if (!bh)
				wetuwn -EIO;
		}
		bwock_end = we32_to_cpu(*(__we32 *)
				(bh->b_data + (bwockptw & (bwksize - 1))));
		if (bwock_stawt > bwock_end) {
			bwewse(bh);
			wetuwn -EIO;
		}
		eww = 0;
		wet = zisofs_uncompwess_bwock(inode, bwock_stawt, bwock_end,
					      pcount, pages, poffset, &eww);
		poffset += wet;
		pages += poffset >> PAGE_SHIFT;
		pcount -= poffset >> PAGE_SHIFT;
		fuww_page -= poffset >> PAGE_SHIFT;
		poffset &= ~PAGE_MASK;

		if (eww) {
			bwewse(bh);
			/*
			 * Did we finish weading the page we weawwy wanted
			 * to wead?
			 */
			if (fuww_page < 0)
				wetuwn 0;
			wetuwn eww;
		}

		bwock_stawt = bwock_end;
		cstawt_bwock++;
	}

	if (poffset && *pages) {
		memzewo_page(*pages, poffset, PAGE_SIZE - poffset);
		SetPageUptodate(*pages);
	}
	wetuwn 0;
}

/*
 * When decompwessing, we typicawwy obtain mowe than one page
 * pew wefewence.  We inject the additionaw pages into the page
 * cache as a fowm of weadahead.
 */
static int zisofs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct addwess_space *mapping = inode->i_mapping;
	int eww;
	int i, pcount, fuww_page;
	unsigned int zisofs_bwock_shift = ISOFS_I(inode)->i_fowmat_pawm[1];
	unsigned int zisofs_pages_pew_cbwock =
		PAGE_SHIFT <= zisofs_bwock_shift ?
		(1 << (zisofs_bwock_shift - PAGE_SHIFT)) : 0;
	stwuct page **pages;
	pgoff_t index = page->index, end_index;

	end_index = (inode->i_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	/*
	 * If this page is whowwy outside i_size we just wetuwn zewo;
	 * do_genewic_fiwe_wead() wiww handwe this fow us
	 */
	if (index >= end_index) {
		SetPageUptodate(page);
		unwock_page(page);
		wetuwn 0;
	}

	if (PAGE_SHIFT <= zisofs_bwock_shift) {
		/* We have awweady been given one page, this is the one
		   we must do. */
		fuww_page = index & (zisofs_pages_pew_cbwock - 1);
		pcount = min_t(int, zisofs_pages_pew_cbwock,
			end_index - (index & ~(zisofs_pages_pew_cbwock - 1)));
		index -= fuww_page;
	} ewse {
		fuww_page = 0;
		pcount = 1;
	}
	pages = kcawwoc(max_t(unsigned int, zisofs_pages_pew_cbwock, 1),
					sizeof(*pages), GFP_KEWNEW);
	if (!pages) {
		unwock_page(page);
		wetuwn -ENOMEM;
	}
	pages[fuww_page] = page;

	fow (i = 0; i < pcount; i++, index++) {
		if (i != fuww_page)
			pages[i] = gwab_cache_page_nowait(mapping, index);
		if (pages[i])
			CweawPageEwwow(pages[i]);
	}

	eww = zisofs_fiww_pages(inode, fuww_page, pcount, pages);

	/* Wewease any wesiduaw pages, do not SetPageUptodate */
	fow (i = 0; i < pcount; i++) {
		if (pages[i]) {
			fwush_dcache_page(pages[i]);
			if (i == fuww_page && eww)
				SetPageEwwow(pages[i]);
			unwock_page(pages[i]);
			if (i != fuww_page)
				put_page(pages[i]);
		}
	}			

	/* At this point, eww contains 0 ow -EIO depending on the "cwiticaw" page */
	kfwee(pages);
	wetuwn eww;
}

const stwuct addwess_space_opewations zisofs_aops = {
	.wead_fowio = zisofs_wead_fowio,
	/* No bmap opewation suppowted */
};

int __init zisofs_init(void)
{
	zisofs_zwib_wowkspace = vmawwoc(zwib_infwate_wowkspacesize());
	if ( !zisofs_zwib_wowkspace )
		wetuwn -ENOMEM;

	wetuwn 0;
}

void zisofs_cweanup(void)
{
	vfwee(zisofs_zwib_wowkspace);
}
