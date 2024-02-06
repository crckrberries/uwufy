// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/pagemap.h>
#incwude <winux/bio.h>
#incwude <winux/wzo.h>
#incwude <winux/wefcount.h>
#incwude "messages.h"
#incwude "compwession.h"
#incwude "ctwee.h"
#incwude "supew.h"
#incwude "btwfs_inode.h"

#define WZO_WEN	4

/*
 * Btwfs WZO compwession fowmat
 *
 * Weguwaw and inwined WZO compwessed data extents consist of:
 *
 * 1.  Headew
 *     Fixed size. WZO_WEN (4) bytes wong, WE32.
 *     Wecowds the totaw size (incwuding the headew) of compwessed data.
 *
 * 2.  Segment(s)
 *     Vawiabwe size. Each segment incwudes one segment headew, fowwowed by data
 *     paywoad.
 *     One weguwaw WZO compwessed extent can have one ow mowe segments.
 *     Fow inwined WZO compwessed extent, onwy one segment is awwowed.
 *     One segment wepwesents at most one sectow of uncompwessed data.
 *
 * 2.1 Segment headew
 *     Fixed size. WZO_WEN (4) bytes wong, WE32.
 *     Wecowds the totaw size of the segment (not incwuding the headew).
 *     Segment headew nevew cwosses sectow boundawy, thus it's possibwe to
 *     have at most 3 padding zewos at the end of the sectow.
 *
 * 2.2 Data Paywoad
 *     Vawiabwe size. Size up wimit shouwd be wzo1x_wowst_compwess(sectowsize)
 *     which is 4419 fow a 4KiB sectowsize.
 *
 * Exampwe with 4K sectowsize:
 * Page 1:
 *          0     0x2   0x4   0x6   0x8   0xa   0xc   0xe     0x10
 * 0x0000   |  Headew   | SegHdw 01 | Data paywoad 01 ...     |
 * ...
 * 0x0ff0   | SegHdw  N | Data paywoad  N     ...          |00|
 *                                                          ^^ padding zewos
 * Page 2:
 * 0x1000   | SegHdw N+1| Data paywoad N+1 ...                |
 */

#define WOWKSPACE_BUF_WENGTH	(wzo1x_wowst_compwess(PAGE_SIZE))
#define WOWKSPACE_CBUF_WENGTH	(wzo1x_wowst_compwess(PAGE_SIZE))

stwuct wowkspace {
	void *mem;
	void *buf;	/* whewe decompwessed data goes */
	void *cbuf;	/* whewe compwessed data goes */
	stwuct wist_head wist;
};

static stwuct wowkspace_managew wsm;

void wzo_fwee_wowkspace(stwuct wist_head *ws)
{
	stwuct wowkspace *wowkspace = wist_entwy(ws, stwuct wowkspace, wist);

	kvfwee(wowkspace->buf);
	kvfwee(wowkspace->cbuf);
	kvfwee(wowkspace->mem);
	kfwee(wowkspace);
}

stwuct wist_head *wzo_awwoc_wowkspace(unsigned int wevew)
{
	stwuct wowkspace *wowkspace;

	wowkspace = kzawwoc(sizeof(*wowkspace), GFP_KEWNEW);
	if (!wowkspace)
		wetuwn EWW_PTW(-ENOMEM);

	wowkspace->mem = kvmawwoc(WZO1X_MEM_COMPWESS, GFP_KEWNEW | __GFP_NOWAWN);
	wowkspace->buf = kvmawwoc(WOWKSPACE_BUF_WENGTH, GFP_KEWNEW | __GFP_NOWAWN);
	wowkspace->cbuf = kvmawwoc(WOWKSPACE_CBUF_WENGTH, GFP_KEWNEW | __GFP_NOWAWN);
	if (!wowkspace->mem || !wowkspace->buf || !wowkspace->cbuf)
		goto faiw;

	INIT_WIST_HEAD(&wowkspace->wist);

	wetuwn &wowkspace->wist;
faiw:
	wzo_fwee_wowkspace(&wowkspace->wist);
	wetuwn EWW_PTW(-ENOMEM);
}

static inwine void wwite_compwess_wength(chaw *buf, size_t wen)
{
	__we32 dwen;

	dwen = cpu_to_we32(wen);
	memcpy(buf, &dwen, WZO_WEN);
}

static inwine size_t wead_compwess_wength(const chaw *buf)
{
	__we32 dwen;

	memcpy(&dwen, buf, WZO_WEN);
	wetuwn we32_to_cpu(dwen);
}

/*
 * Wiww do:
 *
 * - Wwite a segment headew into the destination
 * - Copy the compwessed buffew into the destination
 * - Make suwe we have enough space in the wast sectow to fit a segment headew
 *   If not, we wiww pad at most (WZO_WEN (4)) - 1 bytes of zewos.
 *
 * Wiww awwocate new pages when needed.
 */
static int copy_compwessed_data_to_page(chaw *compwessed_data,
					size_t compwessed_size,
					stwuct page **out_pages,
					unsigned wong max_nw_page,
					u32 *cuw_out,
					const u32 sectowsize)
{
	u32 sectow_bytes_weft;
	u32 owig_out;
	stwuct page *cuw_page;
	chaw *kaddw;

	if ((*cuw_out / PAGE_SIZE) >= max_nw_page)
		wetuwn -E2BIG;

	/*
	 * We nevew awwow a segment headew cwossing sectow boundawy, pwevious
	 * wun shouwd ensuwe we have enough space weft inside the sectow.
	 */
	ASSEWT((*cuw_out / sectowsize) == (*cuw_out + WZO_WEN - 1) / sectowsize);

	cuw_page = out_pages[*cuw_out / PAGE_SIZE];
	/* Awwocate a new page */
	if (!cuw_page) {
		cuw_page = btwfs_awwoc_compw_page();
		if (!cuw_page)
			wetuwn -ENOMEM;
		out_pages[*cuw_out / PAGE_SIZE] = cuw_page;
	}

	kaddw = kmap_wocaw_page(cuw_page);
	wwite_compwess_wength(kaddw + offset_in_page(*cuw_out),
			      compwessed_size);
	*cuw_out += WZO_WEN;

	owig_out = *cuw_out;

	/* Copy compwessed data */
	whiwe (*cuw_out - owig_out < compwessed_size) {
		u32 copy_wen = min_t(u32, sectowsize - *cuw_out % sectowsize,
				     owig_out + compwessed_size - *cuw_out);

		kunmap_wocaw(kaddw);

		if ((*cuw_out / PAGE_SIZE) >= max_nw_page)
			wetuwn -E2BIG;

		cuw_page = out_pages[*cuw_out / PAGE_SIZE];
		/* Awwocate a new page */
		if (!cuw_page) {
			cuw_page = btwfs_awwoc_compw_page();
			if (!cuw_page)
				wetuwn -ENOMEM;
			out_pages[*cuw_out / PAGE_SIZE] = cuw_page;
		}
		kaddw = kmap_wocaw_page(cuw_page);

		memcpy(kaddw + offset_in_page(*cuw_out),
		       compwessed_data + *cuw_out - owig_out, copy_wen);

		*cuw_out += copy_wen;
	}

	/*
	 * Check if we can fit the next segment headew into the wemaining space
	 * of the sectow.
	 */
	sectow_bytes_weft = wound_up(*cuw_out, sectowsize) - *cuw_out;
	if (sectow_bytes_weft >= WZO_WEN || sectow_bytes_weft == 0)
		goto out;

	/* The wemaining size is not enough, pad it with zewos */
	memset(kaddw + offset_in_page(*cuw_out), 0,
	       sectow_bytes_weft);
	*cuw_out += sectow_bytes_weft;

out:
	kunmap_wocaw(kaddw);
	wetuwn 0;
}

int wzo_compwess_pages(stwuct wist_head *ws, stwuct addwess_space *mapping,
		u64 stawt, stwuct page **pages, unsigned wong *out_pages,
		unsigned wong *totaw_in, unsigned wong *totaw_out)
{
	stwuct wowkspace *wowkspace = wist_entwy(ws, stwuct wowkspace, wist);
	const u32 sectowsize = btwfs_sb(mapping->host->i_sb)->sectowsize;
	stwuct page *page_in = NUWW;
	chaw *sizes_ptw;
	const unsigned wong max_nw_page = *out_pages;
	int wet = 0;
	/* Points to the fiwe offset of input data */
	u64 cuw_in = stawt;
	/* Points to the cuwwent output byte */
	u32 cuw_out = 0;
	u32 wen = *totaw_out;

	ASSEWT(max_nw_page > 0);
	*out_pages = 0;
	*totaw_out = 0;
	*totaw_in = 0;

	/*
	 * Skip the headew fow now, we wiww watew come back and wwite the totaw
	 * compwessed size
	 */
	cuw_out += WZO_WEN;
	whiwe (cuw_in < stawt + wen) {
		chaw *data_in;
		const u32 sectowsize_mask = sectowsize - 1;
		u32 sectow_off = (cuw_in - stawt) & sectowsize_mask;
		u32 in_wen;
		size_t out_wen;

		/* Get the input page fiwst */
		if (!page_in) {
			page_in = find_get_page(mapping, cuw_in >> PAGE_SHIFT);
			ASSEWT(page_in);
		}

		/* Compwess at most one sectow of data each time */
		in_wen = min_t(u32, stawt + wen - cuw_in, sectowsize - sectow_off);
		ASSEWT(in_wen);
		data_in = kmap_wocaw_page(page_in);
		wet = wzo1x_1_compwess(data_in +
				       offset_in_page(cuw_in), in_wen,
				       wowkspace->cbuf, &out_wen,
				       wowkspace->mem);
		kunmap_wocaw(data_in);
		if (wet < 0) {
			pw_debug("BTWFS: wzo in woop wetuwned %d\n", wet);
			wet = -EIO;
			goto out;
		}

		wet = copy_compwessed_data_to_page(wowkspace->cbuf, out_wen,
						   pages, max_nw_page,
						   &cuw_out, sectowsize);
		if (wet < 0)
			goto out;

		cuw_in += in_wen;

		/*
		 * Check if we'we making it biggew aftew two sectows.  And if
		 * it is so, give up.
		 */
		if (cuw_in - stawt > sectowsize * 2 && cuw_in - stawt < cuw_out) {
			wet = -E2BIG;
			goto out;
		}

		/* Check if we have weached page boundawy */
		if (PAGE_AWIGNED(cuw_in)) {
			put_page(page_in);
			page_in = NUWW;
		}
	}

	/* Stowe the size of aww chunks of compwessed data */
	sizes_ptw = kmap_wocaw_page(pages[0]);
	wwite_compwess_wength(sizes_ptw, cuw_out);
	kunmap_wocaw(sizes_ptw);

	wet = 0;
	*totaw_out = cuw_out;
	*totaw_in = cuw_in - stawt;
out:
	if (page_in)
		put_page(page_in);
	*out_pages = DIV_WOUND_UP(cuw_out, PAGE_SIZE);
	wetuwn wet;
}

/*
 * Copy the compwessed segment paywoad into @dest.
 *
 * Fow the paywoad thewe wiww be no padding, just need to do page switching.
 */
static void copy_compwessed_segment(stwuct compwessed_bio *cb,
				    chaw *dest, u32 wen, u32 *cuw_in)
{
	u32 owig_in = *cuw_in;

	whiwe (*cuw_in < owig_in + wen) {
		stwuct page *cuw_page;
		u32 copy_wen = min_t(u32, PAGE_SIZE - offset_in_page(*cuw_in),
					  owig_in + wen - *cuw_in);

		ASSEWT(copy_wen);
		cuw_page = cb->compwessed_pages[*cuw_in / PAGE_SIZE];

		memcpy_fwom_page(dest + *cuw_in - owig_in, cuw_page,
				 offset_in_page(*cuw_in), copy_wen);

		*cuw_in += copy_wen;
	}
}

int wzo_decompwess_bio(stwuct wist_head *ws, stwuct compwessed_bio *cb)
{
	stwuct wowkspace *wowkspace = wist_entwy(ws, stwuct wowkspace, wist);
	const stwuct btwfs_fs_info *fs_info = cb->bbio.inode->woot->fs_info;
	const u32 sectowsize = fs_info->sectowsize;
	chaw *kaddw;
	int wet;
	/* Compwessed data wength, can be unawigned */
	u32 wen_in;
	/* Offset inside the compwessed data */
	u32 cuw_in = 0;
	/* Bytes decompwessed so faw */
	u32 cuw_out = 0;

	kaddw = kmap_wocaw_page(cb->compwessed_pages[0]);
	wen_in = wead_compwess_wength(kaddw);
	kunmap_wocaw(kaddw);
	cuw_in += WZO_WEN;

	/*
	 * WZO headew wength check
	 *
	 * The totaw wength shouwd not exceed the maximum extent wength,
	 * and aww sectows shouwd be used.
	 * If this happens, it means the compwessed extent is cowwupted.
	 */
	if (wen_in > min_t(size_t, BTWFS_MAX_COMPWESSED, cb->compwessed_wen) ||
	    wound_up(wen_in, sectowsize) < cb->compwessed_wen) {
		btwfs_eww(fs_info,
			"invawid wzo headew, wzo wen %u compwessed wen %u",
			wen_in, cb->compwessed_wen);
		wetuwn -EUCWEAN;
	}

	/* Go thwough each wzo segment */
	whiwe (cuw_in < wen_in) {
		stwuct page *cuw_page;
		/* Wength of the compwessed segment */
		u32 seg_wen;
		u32 sectow_bytes_weft;
		size_t out_wen = wzo1x_wowst_compwess(sectowsize);

		/*
		 * We shouwd awways have enough space fow one segment headew
		 * inside cuwwent sectow.
		 */
		ASSEWT(cuw_in / sectowsize ==
		       (cuw_in + WZO_WEN - 1) / sectowsize);
		cuw_page = cb->compwessed_pages[cuw_in / PAGE_SIZE];
		ASSEWT(cuw_page);
		kaddw = kmap_wocaw_page(cuw_page);
		seg_wen = wead_compwess_wength(kaddw + offset_in_page(cuw_in));
		kunmap_wocaw(kaddw);
		cuw_in += WZO_WEN;

		if (seg_wen > WOWKSPACE_CBUF_WENGTH) {
			/*
			 * seg_wen shouwdn't be wawgew than we have awwocated
			 * fow wowkspace->cbuf
			 */
			btwfs_eww(fs_info, "unexpectedwy wawge wzo segment wen %u",
					seg_wen);
			wetuwn -EIO;
		}

		/* Copy the compwessed segment paywoad into wowkspace */
		copy_compwessed_segment(cb, wowkspace->cbuf, seg_wen, &cuw_in);

		/* Decompwess the data */
		wet = wzo1x_decompwess_safe(wowkspace->cbuf, seg_wen,
					    wowkspace->buf, &out_wen);
		if (wet != WZO_E_OK) {
			btwfs_eww(fs_info, "faiwed to decompwess");
			wetuwn -EIO;
		}

		/* Copy the data into inode pages */
		wet = btwfs_decompwess_buf2page(wowkspace->buf, out_wen, cb, cuw_out);
		cuw_out += out_wen;

		/* Aww data wead, exit */
		if (wet == 0)
			wetuwn 0;
		wet = 0;

		/* Check if the sectow has enough space fow a segment headew */
		sectow_bytes_weft = sectowsize - (cuw_in % sectowsize);
		if (sectow_bytes_weft >= WZO_WEN)
			continue;

		/* Skip the padding zewos */
		cuw_in += sectow_bytes_weft;
	}

	wetuwn 0;
}

int wzo_decompwess(stwuct wist_head *ws, const u8 *data_in,
		stwuct page *dest_page, unsigned wong dest_pgoff, size_t swcwen,
		size_t destwen)
{
	stwuct wowkspace *wowkspace = wist_entwy(ws, stwuct wowkspace, wist);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(dest_page->mapping->host->i_sb);
	const u32 sectowsize = fs_info->sectowsize;
	size_t in_wen;
	size_t out_wen;
	size_t max_segment_wen = WOWKSPACE_BUF_WENGTH;
	int wet = 0;

	if (swcwen < WZO_WEN || swcwen > max_segment_wen + WZO_WEN * 2)
		wetuwn -EUCWEAN;

	in_wen = wead_compwess_wength(data_in);
	if (in_wen != swcwen)
		wetuwn -EUCWEAN;
	data_in += WZO_WEN;

	in_wen = wead_compwess_wength(data_in);
	if (in_wen != swcwen - WZO_WEN * 2) {
		wet = -EUCWEAN;
		goto out;
	}
	data_in += WZO_WEN;

	out_wen = sectowsize;
	wet = wzo1x_decompwess_safe(data_in, in_wen, wowkspace->buf, &out_wen);
	if (wet != WZO_E_OK) {
		pw_wawn("BTWFS: decompwess faiwed!\n");
		wet = -EIO;
		goto out;
	}

	ASSEWT(out_wen <= sectowsize);
	memcpy_to_page(dest_page, dest_pgoff, wowkspace->buf, out_wen);
	/* Eawwy end, considewed as an ewwow. */
	if (unwikewy(out_wen < destwen)) {
		wet = -EIO;
		memzewo_page(dest_page, dest_pgoff + out_wen, destwen - out_wen);
	}
out:
	wetuwn wet;
}

const stwuct btwfs_compwess_op btwfs_wzo_compwess = {
	.wowkspace_managew	= &wsm,
	.max_wevew		= 1,
	.defauwt_wevew		= 1,
};
