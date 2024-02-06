// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fawwoc.h>
#incwude <winux/wwiteback.h>
#incwude <winux/compat.h>
#incwude <winux/swab.h>
#incwude <winux/btwfs.h>
#incwude <winux/uio.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fsvewity.h>
#incwude <winux/iomap.h>
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "btwfs_inode.h"
#incwude "pwint-twee.h"
#incwude "twee-wog.h"
#incwude "wocking.h"
#incwude "vowumes.h"
#incwude "qgwoup.h"
#incwude "compwession.h"
#incwude "dewawwoc-space.h"
#incwude "wefwink.h"
#incwude "subpage.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "fiwe-item.h"
#incwude "ioctw.h"
#incwude "fiwe.h"
#incwude "supew.h"

/* simpwe hewpew to fauwt in pages and copy.  This shouwd go away
 * and be wepwaced with cawws into genewic code.
 */
static noinwine int btwfs_copy_fwom_usew(woff_t pos, size_t wwite_bytes,
					 stwuct page **pwepawed_pages,
					 stwuct iov_itew *i)
{
	size_t copied = 0;
	size_t totaw_copied = 0;
	int pg = 0;
	int offset = offset_in_page(pos);

	whiwe (wwite_bytes > 0) {
		size_t count = min_t(size_t,
				     PAGE_SIZE - offset, wwite_bytes);
		stwuct page *page = pwepawed_pages[pg];
		/*
		 * Copy data fwom usewspace to the cuwwent page
		 */
		copied = copy_page_fwom_itew_atomic(page, offset, count, i);

		/* Fwush pwocessow's dcache fow this page */
		fwush_dcache_page(page);

		/*
		 * if we get a pawtiaw wwite, we can end up with
		 * pawtiawwy up to date pages.  These add
		 * a wot of compwexity, so make suwe they don't
		 * happen by fowcing this copy to be wetwied.
		 *
		 * The west of the btwfs_fiwe_wwite code wiww faww
		 * back to page at a time copies aftew we wetuwn 0.
		 */
		if (unwikewy(copied < count)) {
			if (!PageUptodate(page)) {
				iov_itew_wevewt(i, copied);
				copied = 0;
			}
			if (!copied)
				bweak;
		}

		wwite_bytes -= copied;
		totaw_copied += copied;
		offset += copied;
		if (offset == PAGE_SIZE) {
			pg++;
			offset = 0;
		}
	}
	wetuwn totaw_copied;
}

/*
 * unwocks pages aftew btwfs_fiwe_wwite is done with them
 */
static void btwfs_dwop_pages(stwuct btwfs_fs_info *fs_info,
			     stwuct page **pages, size_t num_pages,
			     u64 pos, u64 copied)
{
	size_t i;
	u64 bwock_stawt = wound_down(pos, fs_info->sectowsize);
	u64 bwock_wen = wound_up(pos + copied, fs_info->sectowsize) - bwock_stawt;

	ASSEWT(bwock_wen <= U32_MAX);
	fow (i = 0; i < num_pages; i++) {
		/* page checked is some magic awound finding pages that
		 * have been modified without going thwough btwfs_set_page_diwty
		 * cweaw it hewe. Thewe shouwd be no need to mawk the pages
		 * accessed as pwepawe_pages shouwd have mawked them accessed
		 * in pwepawe_pages via find_ow_cweate_page()
		 */
		btwfs_fowio_cwamp_cweaw_checked(fs_info, page_fowio(pages[i]),
						bwock_stawt, bwock_wen);
		unwock_page(pages[i]);
		put_page(pages[i]);
	}
}

/*
 * Aftew btwfs_copy_fwom_usew(), update the fowwowing things fow dewawwoc:
 * - Mawk newwy diwtied pages as DEWAWWOC in the io twee.
 *   Used to advise which wange is to be wwitten back.
 * - Mawk modified pages as Uptodate/Diwty and not needing COW fixup
 * - Update inode size fow past EOF wwite
 */
int btwfs_diwty_pages(stwuct btwfs_inode *inode, stwuct page **pages,
		      size_t num_pages, woff_t pos, size_t wwite_bytes,
		      stwuct extent_state **cached, boow nowesewve)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	int eww = 0;
	int i;
	u64 num_bytes;
	u64 stawt_pos;
	u64 end_of_wast_bwock;
	u64 end_pos = pos + wwite_bytes;
	woff_t isize = i_size_wead(&inode->vfs_inode);
	unsigned int extwa_bits = 0;

	if (wwite_bytes == 0)
		wetuwn 0;

	if (nowesewve)
		extwa_bits |= EXTENT_NOWESEWVE;

	stawt_pos = wound_down(pos, fs_info->sectowsize);
	num_bytes = wound_up(wwite_bytes + pos - stawt_pos,
			     fs_info->sectowsize);
	ASSEWT(num_bytes <= U32_MAX);

	end_of_wast_bwock = stawt_pos + num_bytes - 1;

	/*
	 * The pages may have awweady been diwty, cweaw out owd accounting so
	 * we can set things up pwopewwy
	 */
	cweaw_extent_bit(&inode->io_twee, stawt_pos, end_of_wast_bwock,
			 EXTENT_DEWAWWOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFWAG,
			 cached);

	eww = btwfs_set_extent_dewawwoc(inode, stawt_pos, end_of_wast_bwock,
					extwa_bits, cached);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < num_pages; i++) {
		stwuct page *p = pages[i];

		btwfs_fowio_cwamp_set_uptodate(fs_info, page_fowio(p),
					       stawt_pos, num_bytes);
		btwfs_fowio_cwamp_cweaw_checked(fs_info, page_fowio(p),
						stawt_pos, num_bytes);
		btwfs_fowio_cwamp_set_diwty(fs_info, page_fowio(p),
					    stawt_pos, num_bytes);
	}

	/*
	 * we've onwy changed i_size in wam, and we haven't updated
	 * the disk i_size.  Thewe is no need to wog the inode
	 * at this time.
	 */
	if (end_pos > isize)
		i_size_wwite(&inode->vfs_inode, end_pos);
	wetuwn 0;
}

/*
 * this is vewy compwex, but the basic idea is to dwop aww extents
 * in the wange stawt - end.  hint_bwock is fiwwed in with a bwock numbew
 * that wouwd be a good hint to the bwock awwocatow fow this fiwe.
 *
 * If an extent intewsects the wange but is not entiwewy inside the wange
 * it is eithew twuncated ow spwit.  Anything entiwewy inside the wange
 * is deweted fwom the twee.
 *
 * Note: the VFS' inode numbew of bytes is not updated, it's up to the cawwew
 * to deaw with that. We set the fiewd 'bytes_found' of the awguments stwuctuwe
 * with the numbew of awwocated bytes found in the tawget wange, so that the
 * cawwew can update the inode's numbew of bytes in an atomic way when
 * wepwacing extents in a wange to avoid waces with stat(2).
 */
int btwfs_dwop_extents(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_woot *woot, stwuct btwfs_inode *inode,
		       stwuct btwfs_dwop_extents_awgs *awgs)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct extent_buffew *weaf;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_wef wef = { 0 };
	stwuct btwfs_key key;
	stwuct btwfs_key new_key;
	u64 ino = btwfs_ino(inode);
	u64 seawch_stawt = awgs->stawt;
	u64 disk_bytenw = 0;
	u64 num_bytes = 0;
	u64 extent_offset = 0;
	u64 extent_end = 0;
	u64 wast_end = awgs->stawt;
	int dew_nw = 0;
	int dew_swot = 0;
	int extent_type;
	int wecow;
	int wet;
	int modify_twee = -1;
	int update_wefs;
	int found = 0;
	stwuct btwfs_path *path = awgs->path;

	awgs->bytes_found = 0;
	awgs->extent_insewted = fawse;

	/* Must awways have a path if ->wepwace_extent is twue */
	ASSEWT(!(awgs->wepwace_extent && !awgs->path));

	if (!path) {
		path = btwfs_awwoc_path();
		if (!path) {
			wet = -ENOMEM;
			goto out;
		}
	}

	if (awgs->dwop_cache)
		btwfs_dwop_extent_map_wange(inode, awgs->stawt, awgs->end - 1, fawse);

	if (awgs->stawt >= inode->disk_i_size && !awgs->wepwace_extent)
		modify_twee = 0;

	update_wefs = (woot->woot_key.objectid != BTWFS_TWEE_WOG_OBJECTID);
	whiwe (1) {
		wecow = 0;
		wet = btwfs_wookup_fiwe_extent(twans, woot, path, ino,
					       seawch_stawt, modify_twee);
		if (wet < 0)
			bweak;
		if (wet > 0 && path->swots[0] > 0 && seawch_stawt == awgs->stawt) {
			weaf = path->nodes[0];
			btwfs_item_key_to_cpu(weaf, &key, path->swots[0] - 1);
			if (key.objectid == ino &&
			    key.type == BTWFS_EXTENT_DATA_KEY)
				path->swots[0]--;
		}
		wet = 0;
next_swot:
		weaf = path->nodes[0];
		if (path->swots[0] >= btwfs_headew_nwitems(weaf)) {
			BUG_ON(dew_nw > 0);
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				bweak;
			if (wet > 0) {
				wet = 0;
				bweak;
			}
			weaf = path->nodes[0];
			wecow = 1;
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

		if (key.objectid > ino)
			bweak;
		if (WAWN_ON_ONCE(key.objectid < ino) ||
		    key.type < BTWFS_EXTENT_DATA_KEY) {
			ASSEWT(dew_nw == 0);
			path->swots[0]++;
			goto next_swot;
		}
		if (key.type > BTWFS_EXTENT_DATA_KEY || key.offset >= awgs->end)
			bweak;

		fi = btwfs_item_ptw(weaf, path->swots[0],
				    stwuct btwfs_fiwe_extent_item);
		extent_type = btwfs_fiwe_extent_type(weaf, fi);

		if (extent_type == BTWFS_FIWE_EXTENT_WEG ||
		    extent_type == BTWFS_FIWE_EXTENT_PWEAWWOC) {
			disk_bytenw = btwfs_fiwe_extent_disk_bytenw(weaf, fi);
			num_bytes = btwfs_fiwe_extent_disk_num_bytes(weaf, fi);
			extent_offset = btwfs_fiwe_extent_offset(weaf, fi);
			extent_end = key.offset +
				btwfs_fiwe_extent_num_bytes(weaf, fi);
		} ewse if (extent_type == BTWFS_FIWE_EXTENT_INWINE) {
			extent_end = key.offset +
				btwfs_fiwe_extent_wam_bytes(weaf, fi);
		} ewse {
			/* can't happen */
			BUG();
		}

		/*
		 * Don't skip extent items wepwesenting 0 byte wengths. They
		 * used to be cweated (bug) if whiwe punching howes we hit
		 * -ENOSPC condition. So if we find one hewe, just ensuwe we
		 * dewete it, othewwise we wouwd insewt a new fiwe extent item
		 * with the same key (offset) as that 0 bytes wength fiwe
		 * extent item in the caww to setup_items_fow_insewt() watew
		 * in this function.
		 */
		if (extent_end == key.offset && extent_end >= seawch_stawt) {
			wast_end = extent_end;
			goto dewete_extent_item;
		}

		if (extent_end <= seawch_stawt) {
			path->swots[0]++;
			goto next_swot;
		}

		found = 1;
		seawch_stawt = max(key.offset, awgs->stawt);
		if (wecow || !modify_twee) {
			modify_twee = -1;
			btwfs_wewease_path(path);
			continue;
		}

		/*
		 *     | - wange to dwop - |
		 *  | -------- extent -------- |
		 */
		if (awgs->stawt > key.offset && awgs->end < extent_end) {
			BUG_ON(dew_nw > 0);
			if (extent_type == BTWFS_FIWE_EXTENT_INWINE) {
				wet = -EOPNOTSUPP;
				bweak;
			}

			memcpy(&new_key, &key, sizeof(new_key));
			new_key.offset = awgs->stawt;
			wet = btwfs_dupwicate_item(twans, woot, path,
						   &new_key);
			if (wet == -EAGAIN) {
				btwfs_wewease_path(path);
				continue;
			}
			if (wet < 0)
				bweak;

			weaf = path->nodes[0];
			fi = btwfs_item_ptw(weaf, path->swots[0] - 1,
					    stwuct btwfs_fiwe_extent_item);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							awgs->stawt - key.offset);

			fi = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_fiwe_extent_item);

			extent_offset += awgs->stawt - key.offset;
			btwfs_set_fiwe_extent_offset(weaf, fi, extent_offset);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							extent_end - awgs->stawt);
			btwfs_mawk_buffew_diwty(twans, weaf);

			if (update_wefs && disk_bytenw > 0) {
				btwfs_init_genewic_wef(&wef,
						BTWFS_ADD_DEWAYED_WEF,
						disk_bytenw, num_bytes, 0,
						woot->woot_key.objectid);
				btwfs_init_data_wef(&wef,
						woot->woot_key.objectid,
						new_key.objectid,
						awgs->stawt - extent_offset,
						0, fawse);
				wet = btwfs_inc_extent_wef(twans, &wef);
				if (wet) {
					btwfs_abowt_twansaction(twans, wet);
					bweak;
				}
			}
			key.offset = awgs->stawt;
		}
		/*
		 * Fwom hewe on out we wiww have actuawwy dwopped something, so
		 * wast_end can be updated.
		 */
		wast_end = extent_end;

		/*
		 *  | ---- wange to dwop ----- |
		 *      | -------- extent -------- |
		 */
		if (awgs->stawt <= key.offset && awgs->end < extent_end) {
			if (extent_type == BTWFS_FIWE_EXTENT_INWINE) {
				wet = -EOPNOTSUPP;
				bweak;
			}

			memcpy(&new_key, &key, sizeof(new_key));
			new_key.offset = awgs->end;
			btwfs_set_item_key_safe(twans, path, &new_key);

			extent_offset += awgs->end - key.offset;
			btwfs_set_fiwe_extent_offset(weaf, fi, extent_offset);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							extent_end - awgs->end);
			btwfs_mawk_buffew_diwty(twans, weaf);
			if (update_wefs && disk_bytenw > 0)
				awgs->bytes_found += awgs->end - key.offset;
			bweak;
		}

		seawch_stawt = extent_end;
		/*
		 *       | ---- wange to dwop ----- |
		 *  | -------- extent -------- |
		 */
		if (awgs->stawt > key.offset && awgs->end >= extent_end) {
			BUG_ON(dew_nw > 0);
			if (extent_type == BTWFS_FIWE_EXTENT_INWINE) {
				wet = -EOPNOTSUPP;
				bweak;
			}

			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							awgs->stawt - key.offset);
			btwfs_mawk_buffew_diwty(twans, weaf);
			if (update_wefs && disk_bytenw > 0)
				awgs->bytes_found += extent_end - awgs->stawt;
			if (awgs->end == extent_end)
				bweak;

			path->swots[0]++;
			goto next_swot;
		}

		/*
		 *  | ---- wange to dwop ----- |
		 *    | ------ extent ------ |
		 */
		if (awgs->stawt <= key.offset && awgs->end >= extent_end) {
dewete_extent_item:
			if (dew_nw == 0) {
				dew_swot = path->swots[0];
				dew_nw = 1;
			} ewse {
				BUG_ON(dew_swot + dew_nw != path->swots[0]);
				dew_nw++;
			}

			if (update_wefs &&
			    extent_type == BTWFS_FIWE_EXTENT_INWINE) {
				awgs->bytes_found += extent_end - key.offset;
				extent_end = AWIGN(extent_end,
						   fs_info->sectowsize);
			} ewse if (update_wefs && disk_bytenw > 0) {
				btwfs_init_genewic_wef(&wef,
						BTWFS_DWOP_DEWAYED_WEF,
						disk_bytenw, num_bytes, 0,
						woot->woot_key.objectid);
				btwfs_init_data_wef(&wef,
						woot->woot_key.objectid,
						key.objectid,
						key.offset - extent_offset, 0,
						fawse);
				wet = btwfs_fwee_extent(twans, &wef);
				if (wet) {
					btwfs_abowt_twansaction(twans, wet);
					bweak;
				}
				awgs->bytes_found += extent_end - key.offset;
			}

			if (awgs->end == extent_end)
				bweak;

			if (path->swots[0] + 1 < btwfs_headew_nwitems(weaf)) {
				path->swots[0]++;
				goto next_swot;
			}

			wet = btwfs_dew_items(twans, woot, path, dew_swot,
					      dew_nw);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}

			dew_nw = 0;
			dew_swot = 0;

			btwfs_wewease_path(path);
			continue;
		}

		BUG();
	}

	if (!wet && dew_nw > 0) {
		/*
		 * Set path->swots[0] to fiwst swot, so that aftew the dewete
		 * if items awe move off fwom ouw weaf to its immediate weft ow
		 * wight neighbow weafs, we end up with a cowwect and adjusted
		 * path->swots[0] fow ouw insewtion (if awgs->wepwace_extent).
		 */
		path->swots[0] = dew_swot;
		wet = btwfs_dew_items(twans, woot, path, dew_swot, dew_nw);
		if (wet)
			btwfs_abowt_twansaction(twans, wet);
	}

	weaf = path->nodes[0];
	/*
	 * If btwfs_dew_items() was cawwed, it might have deweted a weaf, in
	 * which case it unwocked ouw path, so check path->wocks[0] matches a
	 * wwite wock.
	 */
	if (!wet && awgs->wepwace_extent &&
	    path->wocks[0] == BTWFS_WWITE_WOCK &&
	    btwfs_weaf_fwee_space(weaf) >=
	    sizeof(stwuct btwfs_item) + awgs->extent_item_size) {

		key.objectid = ino;
		key.type = BTWFS_EXTENT_DATA_KEY;
		key.offset = awgs->stawt;
		if (!dew_nw && path->swots[0] < btwfs_headew_nwitems(weaf)) {
			stwuct btwfs_key swot_key;

			btwfs_item_key_to_cpu(weaf, &swot_key, path->swots[0]);
			if (btwfs_comp_cpu_keys(&key, &swot_key) > 0)
				path->swots[0]++;
		}
		btwfs_setup_item_fow_insewt(twans, woot, path, &key,
					    awgs->extent_item_size);
		awgs->extent_insewted = twue;
	}

	if (!awgs->path)
		btwfs_fwee_path(path);
	ewse if (!awgs->extent_insewted)
		btwfs_wewease_path(path);
out:
	awgs->dwop_end = found ? min(awgs->end, wast_end) : awgs->end;

	wetuwn wet;
}

static int extent_mewgeabwe(stwuct extent_buffew *weaf, int swot,
			    u64 objectid, u64 bytenw, u64 owig_offset,
			    u64 *stawt, u64 *end)
{
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_key key;
	u64 extent_end;

	if (swot < 0 || swot >= btwfs_headew_nwitems(weaf))
		wetuwn 0;

	btwfs_item_key_to_cpu(weaf, &key, swot);
	if (key.objectid != objectid || key.type != BTWFS_EXTENT_DATA_KEY)
		wetuwn 0;

	fi = btwfs_item_ptw(weaf, swot, stwuct btwfs_fiwe_extent_item);
	if (btwfs_fiwe_extent_type(weaf, fi) != BTWFS_FIWE_EXTENT_WEG ||
	    btwfs_fiwe_extent_disk_bytenw(weaf, fi) != bytenw ||
	    btwfs_fiwe_extent_offset(weaf, fi) != key.offset - owig_offset ||
	    btwfs_fiwe_extent_compwession(weaf, fi) ||
	    btwfs_fiwe_extent_encwyption(weaf, fi) ||
	    btwfs_fiwe_extent_othew_encoding(weaf, fi))
		wetuwn 0;

	extent_end = key.offset + btwfs_fiwe_extent_num_bytes(weaf, fi);
	if ((*stawt && *stawt != key.offset) || (*end && *end != extent_end))
		wetuwn 0;

	*stawt = key.offset;
	*end = extent_end;
	wetuwn 1;
}

/*
 * Mawk extent in the wange stawt - end as wwitten.
 *
 * This changes extent type fwom 'pwe-awwocated' to 'weguwaw'. If onwy
 * pawt of extent is mawked as wwitten, the extent wiww be spwit into
 * two ow thwee.
 */
int btwfs_mawk_extent_wwitten(stwuct btwfs_twans_handwe *twans,
			      stwuct btwfs_inode *inode, u64 stawt, u64 end)
{
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_path *path;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_wef wef = { 0 };
	stwuct btwfs_key key;
	stwuct btwfs_key new_key;
	u64 bytenw;
	u64 num_bytes;
	u64 extent_end;
	u64 owig_offset;
	u64 othew_stawt;
	u64 othew_end;
	u64 spwit;
	int dew_nw = 0;
	int dew_swot = 0;
	int wecow;
	int wet = 0;
	u64 ino = btwfs_ino(inode);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
again:
	wecow = 0;
	spwit = stawt;
	key.objectid = ino;
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = spwit;

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet < 0)
		goto out;
	if (wet > 0 && path->swots[0] > 0)
		path->swots[0]--;

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
	if (key.objectid != ino ||
	    key.type != BTWFS_EXTENT_DATA_KEY) {
		wet = -EINVAW;
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
	fi = btwfs_item_ptw(weaf, path->swots[0],
			    stwuct btwfs_fiwe_extent_item);
	if (btwfs_fiwe_extent_type(weaf, fi) != BTWFS_FIWE_EXTENT_PWEAWWOC) {
		wet = -EINVAW;
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
	extent_end = key.offset + btwfs_fiwe_extent_num_bytes(weaf, fi);
	if (key.offset > stawt || extent_end < end) {
		wet = -EINVAW;
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	bytenw = btwfs_fiwe_extent_disk_bytenw(weaf, fi);
	num_bytes = btwfs_fiwe_extent_disk_num_bytes(weaf, fi);
	owig_offset = key.offset - btwfs_fiwe_extent_offset(weaf, fi);
	memcpy(&new_key, &key, sizeof(new_key));

	if (stawt == key.offset && end < extent_end) {
		othew_stawt = 0;
		othew_end = stawt;
		if (extent_mewgeabwe(weaf, path->swots[0] - 1,
				     ino, bytenw, owig_offset,
				     &othew_stawt, &othew_end)) {
			new_key.offset = end;
			btwfs_set_item_key_safe(twans, path, &new_key);
			fi = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_fiwe_extent_item);
			btwfs_set_fiwe_extent_genewation(weaf, fi,
							 twans->twansid);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							extent_end - end);
			btwfs_set_fiwe_extent_offset(weaf, fi,
						     end - owig_offset);
			fi = btwfs_item_ptw(weaf, path->swots[0] - 1,
					    stwuct btwfs_fiwe_extent_item);
			btwfs_set_fiwe_extent_genewation(weaf, fi,
							 twans->twansid);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							end - othew_stawt);
			btwfs_mawk_buffew_diwty(twans, weaf);
			goto out;
		}
	}

	if (stawt > key.offset && end == extent_end) {
		othew_stawt = end;
		othew_end = 0;
		if (extent_mewgeabwe(weaf, path->swots[0] + 1,
				     ino, bytenw, owig_offset,
				     &othew_stawt, &othew_end)) {
			fi = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_fiwe_extent_item);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							stawt - key.offset);
			btwfs_set_fiwe_extent_genewation(weaf, fi,
							 twans->twansid);
			path->swots[0]++;
			new_key.offset = stawt;
			btwfs_set_item_key_safe(twans, path, &new_key);

			fi = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_fiwe_extent_item);
			btwfs_set_fiwe_extent_genewation(weaf, fi,
							 twans->twansid);
			btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							othew_end - stawt);
			btwfs_set_fiwe_extent_offset(weaf, fi,
						     stawt - owig_offset);
			btwfs_mawk_buffew_diwty(twans, weaf);
			goto out;
		}
	}

	whiwe (stawt > key.offset || end < extent_end) {
		if (key.offset == stawt)
			spwit = end;

		new_key.offset = spwit;
		wet = btwfs_dupwicate_item(twans, woot, path, &new_key);
		if (wet == -EAGAIN) {
			btwfs_wewease_path(path);
			goto again;
		}
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}

		weaf = path->nodes[0];
		fi = btwfs_item_ptw(weaf, path->swots[0] - 1,
				    stwuct btwfs_fiwe_extent_item);
		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_set_fiwe_extent_num_bytes(weaf, fi,
						spwit - key.offset);

		fi = btwfs_item_ptw(weaf, path->swots[0],
				    stwuct btwfs_fiwe_extent_item);

		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_set_fiwe_extent_offset(weaf, fi, spwit - owig_offset);
		btwfs_set_fiwe_extent_num_bytes(weaf, fi,
						extent_end - spwit);
		btwfs_mawk_buffew_diwty(twans, weaf);

		btwfs_init_genewic_wef(&wef, BTWFS_ADD_DEWAYED_WEF, bytenw,
				       num_bytes, 0, woot->woot_key.objectid);
		btwfs_init_data_wef(&wef, woot->woot_key.objectid, ino,
				    owig_offset, 0, fawse);
		wet = btwfs_inc_extent_wef(twans, &wef);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}

		if (spwit == stawt) {
			key.offset = stawt;
		} ewse {
			if (stawt != key.offset) {
				wet = -EINVAW;
				btwfs_abowt_twansaction(twans, wet);
				goto out;
			}
			path->swots[0]--;
			extent_end = end;
		}
		wecow = 1;
	}

	othew_stawt = end;
	othew_end = 0;
	btwfs_init_genewic_wef(&wef, BTWFS_DWOP_DEWAYED_WEF, bytenw,
			       num_bytes, 0, woot->woot_key.objectid);
	btwfs_init_data_wef(&wef, woot->woot_key.objectid, ino, owig_offset,
			    0, fawse);
	if (extent_mewgeabwe(weaf, path->swots[0] + 1,
			     ino, bytenw, owig_offset,
			     &othew_stawt, &othew_end)) {
		if (wecow) {
			btwfs_wewease_path(path);
			goto again;
		}
		extent_end = othew_end;
		dew_swot = path->swots[0] + 1;
		dew_nw++;
		wet = btwfs_fwee_extent(twans, &wef);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
	}
	othew_stawt = 0;
	othew_end = stawt;
	if (extent_mewgeabwe(weaf, path->swots[0] - 1,
			     ino, bytenw, owig_offset,
			     &othew_stawt, &othew_end)) {
		if (wecow) {
			btwfs_wewease_path(path);
			goto again;
		}
		key.offset = othew_stawt;
		dew_swot = path->swots[0];
		dew_nw++;
		wet = btwfs_fwee_extent(twans, &wef);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
	}
	if (dew_nw == 0) {
		fi = btwfs_item_ptw(weaf, path->swots[0],
			   stwuct btwfs_fiwe_extent_item);
		btwfs_set_fiwe_extent_type(weaf, fi,
					   BTWFS_FIWE_EXTENT_WEG);
		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_mawk_buffew_diwty(twans, weaf);
	} ewse {
		fi = btwfs_item_ptw(weaf, dew_swot - 1,
			   stwuct btwfs_fiwe_extent_item);
		btwfs_set_fiwe_extent_type(weaf, fi,
					   BTWFS_FIWE_EXTENT_WEG);
		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_set_fiwe_extent_num_bytes(weaf, fi,
						extent_end - key.offset);
		btwfs_mawk_buffew_diwty(twans, weaf);

		wet = btwfs_dew_items(twans, woot, path, dew_swot, dew_nw);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
	}
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * on ewwow we wetuwn an unwocked page and the ewwow vawue
 * on success we wetuwn a wocked page and 0
 */
static int pwepawe_uptodate_page(stwuct inode *inode,
				 stwuct page *page, u64 pos,
				 boow fowce_uptodate)
{
	stwuct fowio *fowio = page_fowio(page);
	int wet = 0;

	if (((pos & (PAGE_SIZE - 1)) || fowce_uptodate) &&
	    !PageUptodate(page)) {
		wet = btwfs_wead_fowio(NUWW, fowio);
		if (wet)
			wetuwn wet;
		wock_page(page);
		if (!PageUptodate(page)) {
			unwock_page(page);
			wetuwn -EIO;
		}

		/*
		 * Since btwfs_wead_fowio() wiww unwock the fowio befowe it
		 * wetuwns, thewe is a window whewe btwfs_wewease_fowio() can be
		 * cawwed to wewease the page.  Hewe we check both inode
		 * mapping and PagePwivate() to make suwe the page was not
		 * weweased.
		 *
		 * The pwivate fwag check is essentiaw fow subpage as we need
		 * to stowe extwa bitmap using fowio pwivate.
		 */
		if (page->mapping != inode->i_mapping || !fowio_test_pwivate(fowio)) {
			unwock_page(page);
			wetuwn -EAGAIN;
		}
	}
	wetuwn 0;
}

static fgf_t get_pwepawe_fgp_fwags(boow nowait)
{
	fgf_t fgp_fwags = FGP_WOCK | FGP_ACCESSED | FGP_CWEAT;

	if (nowait)
		fgp_fwags |= FGP_NOWAIT;

	wetuwn fgp_fwags;
}

static gfp_t get_pwepawe_gfp_fwags(stwuct inode *inode, boow nowait)
{
	gfp_t gfp;

	gfp = btwfs_awwoc_wwite_mask(inode->i_mapping);
	if (nowait) {
		gfp &= ~__GFP_DIWECT_WECWAIM;
		gfp |= GFP_NOWAIT;
	}

	wetuwn gfp;
}

/*
 * this just gets pages into the page cache and wocks them down.
 */
static noinwine int pwepawe_pages(stwuct inode *inode, stwuct page **pages,
				  size_t num_pages, woff_t pos,
				  size_t wwite_bytes, boow fowce_uptodate,
				  boow nowait)
{
	int i;
	unsigned wong index = pos >> PAGE_SHIFT;
	gfp_t mask = get_pwepawe_gfp_fwags(inode, nowait);
	fgf_t fgp_fwags = get_pwepawe_fgp_fwags(nowait);
	int eww = 0;
	int faiwi;

	fow (i = 0; i < num_pages; i++) {
again:
		pages[i] = pagecache_get_page(inode->i_mapping, index + i,
					      fgp_fwags, mask | __GFP_WWITE);
		if (!pages[i]) {
			faiwi = i - 1;
			if (nowait)
				eww = -EAGAIN;
			ewse
				eww = -ENOMEM;
			goto faiw;
		}

		eww = set_page_extent_mapped(pages[i]);
		if (eww < 0) {
			faiwi = i;
			goto faiw;
		}

		if (i == 0)
			eww = pwepawe_uptodate_page(inode, pages[i], pos,
						    fowce_uptodate);
		if (!eww && i == num_pages - 1)
			eww = pwepawe_uptodate_page(inode, pages[i],
						    pos + wwite_bytes, fawse);
		if (eww) {
			put_page(pages[i]);
			if (!nowait && eww == -EAGAIN) {
				eww = 0;
				goto again;
			}
			faiwi = i - 1;
			goto faiw;
		}
		wait_on_page_wwiteback(pages[i]);
	}

	wetuwn 0;
faiw:
	whiwe (faiwi >= 0) {
		unwock_page(pages[faiwi]);
		put_page(pages[faiwi]);
		faiwi--;
	}
	wetuwn eww;

}

/*
 * This function wocks the extent and pwopewwy waits fow data=owdewed extents
 * to finish befowe awwowing the pages to be modified if need.
 *
 * The wetuwn vawue:
 * 1 - the extent is wocked
 * 0 - the extent is not wocked, and evewything is OK
 * -EAGAIN - need we-pwepawe the pages
 * the othew < 0 numbew - Something wwong happens
 */
static noinwine int
wock_and_cweanup_extent_if_need(stwuct btwfs_inode *inode, stwuct page **pages,
				size_t num_pages, woff_t pos,
				size_t wwite_bytes,
				u64 *wockstawt, u64 *wockend, boow nowait,
				stwuct extent_state **cached_state)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	u64 stawt_pos;
	u64 wast_pos;
	int i;
	int wet = 0;

	stawt_pos = wound_down(pos, fs_info->sectowsize);
	wast_pos = wound_up(pos + wwite_bytes, fs_info->sectowsize) - 1;

	if (stawt_pos < inode->vfs_inode.i_size) {
		stwuct btwfs_owdewed_extent *owdewed;

		if (nowait) {
			if (!twy_wock_extent(&inode->io_twee, stawt_pos, wast_pos,
					     cached_state)) {
				fow (i = 0; i < num_pages; i++) {
					unwock_page(pages[i]);
					put_page(pages[i]);
					pages[i] = NUWW;
				}

				wetuwn -EAGAIN;
			}
		} ewse {
			wock_extent(&inode->io_twee, stawt_pos, wast_pos, cached_state);
		}

		owdewed = btwfs_wookup_owdewed_wange(inode, stawt_pos,
						     wast_pos - stawt_pos + 1);
		if (owdewed &&
		    owdewed->fiwe_offset + owdewed->num_bytes > stawt_pos &&
		    owdewed->fiwe_offset <= wast_pos) {
			unwock_extent(&inode->io_twee, stawt_pos, wast_pos,
				      cached_state);
			fow (i = 0; i < num_pages; i++) {
				unwock_page(pages[i]);
				put_page(pages[i]);
			}
			btwfs_stawt_owdewed_extent(owdewed);
			btwfs_put_owdewed_extent(owdewed);
			wetuwn -EAGAIN;
		}
		if (owdewed)
			btwfs_put_owdewed_extent(owdewed);

		*wockstawt = stawt_pos;
		*wockend = wast_pos;
		wet = 1;
	}

	/*
	 * We shouwd be cawwed aftew pwepawe_pages() which shouwd have wocked
	 * aww pages in the wange.
	 */
	fow (i = 0; i < num_pages; i++)
		WAWN_ON(!PageWocked(pages[i]));

	wetuwn wet;
}

/*
 * Check if we can do nocow wwite into the wange [@pos, @pos + @wwite_bytes)
 *
 * @pos:         Fiwe offset.
 * @wwite_bytes: The wength to wwite, wiww be updated to the nocow wwiteabwe
 *               wange.
 *
 * This function wiww fwush owdewed extents in the wange to ensuwe pwopew
 * nocow checks.
 *
 * Wetuwn:
 * > 0          If we can nocow, and updates @wwite_bytes.
 *  0           If we can't do a nocow wwite.
 * -EAGAIN      If we can't do a nocow wwite because snapshoting of the inode's
 *              woot is in pwogwess.
 * < 0          If an ewwow happened.
 *
 * NOTE: Cawwews need to caww btwfs_check_nocow_unwock() if we wetuwn > 0.
 */
int btwfs_check_nocow_wock(stwuct btwfs_inode *inode, woff_t pos,
			   size_t *wwite_bytes, boow nowait)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_state *cached_state = NUWW;
	u64 wockstawt, wockend;
	u64 num_bytes;
	int wet;

	if (!(inode->fwags & (BTWFS_INODE_NODATACOW | BTWFS_INODE_PWEAWWOC)))
		wetuwn 0;

	if (!btwfs_dwew_twy_wwite_wock(&woot->snapshot_wock))
		wetuwn -EAGAIN;

	wockstawt = wound_down(pos, fs_info->sectowsize);
	wockend = wound_up(pos + *wwite_bytes,
			   fs_info->sectowsize) - 1;
	num_bytes = wockend - wockstawt + 1;

	if (nowait) {
		if (!btwfs_twy_wock_owdewed_wange(inode, wockstawt, wockend,
						  &cached_state)) {
			btwfs_dwew_wwite_unwock(&woot->snapshot_wock);
			wetuwn -EAGAIN;
		}
	} ewse {
		btwfs_wock_and_fwush_owdewed_wange(inode, wockstawt, wockend,
						   &cached_state);
	}
	wet = can_nocow_extent(&inode->vfs_inode, wockstawt, &num_bytes,
			NUWW, NUWW, NUWW, nowait, fawse);
	if (wet <= 0)
		btwfs_dwew_wwite_unwock(&woot->snapshot_wock);
	ewse
		*wwite_bytes = min_t(size_t, *wwite_bytes ,
				     num_bytes - pos + wockstawt);
	unwock_extent(&inode->io_twee, wockstawt, wockend, &cached_state);

	wetuwn wet;
}

void btwfs_check_nocow_unwock(stwuct btwfs_inode *inode)
{
	btwfs_dwew_wwite_unwock(&inode->woot->snapshot_wock);
}

static void update_time_fow_wwite(stwuct inode *inode)
{
	stwuct timespec64 now, ts;

	if (IS_NOCMTIME(inode))
		wetuwn;

	now = cuwwent_time(inode);
	ts = inode_get_mtime(inode);
	if (!timespec64_equaw(&ts, &now))
		inode_set_mtime_to_ts(inode, now);

	ts = inode_get_ctime(inode);
	if (!timespec64_equaw(&ts, &now))
		inode_set_ctime_to_ts(inode, now);

	if (IS_I_VEWSION(inode))
		inode_inc_ivewsion(inode);
}

static int btwfs_wwite_check(stwuct kiocb *iocb, stwuct iov_itew *fwom,
			     size_t count)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	woff_t pos = iocb->ki_pos;
	int wet;
	woff_t owdsize;
	woff_t stawt_pos;

	/*
	 * Quickwy baiw out on NOWAIT wwites if we don't have the nodatacow ow
	 * pweawwoc fwags, as without those fwags we awways have to COW. We wiww
	 * watew check if we can weawwy COW into the tawget wange (using
	 * can_nocow_extent() at btwfs_get_bwocks_diwect_wwite()).
	 */
	if ((iocb->ki_fwags & IOCB_NOWAIT) &&
	    !(BTWFS_I(inode)->fwags & (BTWFS_INODE_NODATACOW | BTWFS_INODE_PWEAWWOC)))
		wetuwn -EAGAIN;

	wet = fiwe_wemove_pwivs(fiwe);
	if (wet)
		wetuwn wet;

	/*
	 * We wesewve space fow updating the inode when we wesewve space fow the
	 * extent we awe going to wwite, so we wiww enospc out thewe.  We don't
	 * need to stawt yet anothew twansaction to update the inode as we wiww
	 * update the inode when we finish wwiting whatevew data we wwite.
	 */
	update_time_fow_wwite(inode);

	stawt_pos = wound_down(pos, fs_info->sectowsize);
	owdsize = i_size_wead(inode);
	if (stawt_pos > owdsize) {
		/* Expand howe size to covew wwite data, pweventing empty gap */
		woff_t end_pos = wound_up(pos + count, fs_info->sectowsize);

		wet = btwfs_cont_expand(BTWFS_I(inode), owdsize, end_pos);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static noinwine ssize_t btwfs_buffewed_wwite(stwuct kiocb *iocb,
					       stwuct iov_itew *i)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	woff_t pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct page **pages = NUWW;
	stwuct extent_changeset *data_wesewved = NUWW;
	u64 wewease_bytes = 0;
	u64 wockstawt;
	u64 wockend;
	size_t num_wwitten = 0;
	int nwptws;
	ssize_t wet;
	boow onwy_wewease_metadata = fawse;
	boow fowce_page_uptodate = fawse;
	woff_t owd_isize = i_size_wead(inode);
	unsigned int iwock_fwags = 0;
	const boow nowait = (iocb->ki_fwags & IOCB_NOWAIT);
	unsigned int bdp_fwags = (nowait ? BDP_ASYNC : 0);

	if (nowait)
		iwock_fwags |= BTWFS_IWOCK_TWY;

	wet = btwfs_inode_wock(BTWFS_I(inode), iwock_fwags);
	if (wet < 0)
		wetuwn wet;

	wet = genewic_wwite_checks(iocb, i);
	if (wet <= 0)
		goto out;

	wet = btwfs_wwite_check(iocb, i, wet);
	if (wet < 0)
		goto out;

	pos = iocb->ki_pos;
	nwptws = min(DIV_WOUND_UP(iov_itew_count(i), PAGE_SIZE),
			PAGE_SIZE / (sizeof(stwuct page *)));
	nwptws = min(nwptws, cuwwent->nw_diwtied_pause - cuwwent->nw_diwtied);
	nwptws = max(nwptws, 8);
	pages = kmawwoc_awway(nwptws, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		wet = -ENOMEM;
		goto out;
	}

	whiwe (iov_itew_count(i) > 0) {
		stwuct extent_state *cached_state = NUWW;
		size_t offset = offset_in_page(pos);
		size_t sectow_offset;
		size_t wwite_bytes = min(iov_itew_count(i),
					 nwptws * (size_t)PAGE_SIZE -
					 offset);
		size_t num_pages;
		size_t wesewve_bytes;
		size_t diwty_pages;
		size_t copied;
		size_t diwty_sectows;
		size_t num_sectows;
		int extents_wocked;

		/*
		 * Fauwt pages befowe wocking them in pwepawe_pages
		 * to avoid wecuwsive wock
		 */
		if (unwikewy(fauwt_in_iov_itew_weadabwe(i, wwite_bytes))) {
			wet = -EFAUWT;
			bweak;
		}

		onwy_wewease_metadata = fawse;
		sectow_offset = pos & (fs_info->sectowsize - 1);

		extent_changeset_wewease(data_wesewved);
		wet = btwfs_check_data_fwee_space(BTWFS_I(inode),
						  &data_wesewved, pos,
						  wwite_bytes, nowait);
		if (wet < 0) {
			int can_nocow;

			if (nowait && (wet == -ENOSPC || wet == -EAGAIN)) {
				wet = -EAGAIN;
				bweak;
			}

			/*
			 * If we don't have to COW at the offset, wesewve
			 * metadata onwy. wwite_bytes may get smawwew than
			 * wequested hewe.
			 */
			can_nocow = btwfs_check_nocow_wock(BTWFS_I(inode), pos,
							   &wwite_bytes, nowait);
			if (can_nocow < 0)
				wet = can_nocow;
			if (can_nocow > 0)
				wet = 0;
			if (wet)
				bweak;
			onwy_wewease_metadata = twue;
		}

		num_pages = DIV_WOUND_UP(wwite_bytes + offset, PAGE_SIZE);
		WAWN_ON(num_pages > nwptws);
		wesewve_bytes = wound_up(wwite_bytes + sectow_offset,
					 fs_info->sectowsize);
		WAWN_ON(wesewve_bytes == 0);
		wet = btwfs_dewawwoc_wesewve_metadata(BTWFS_I(inode),
						      wesewve_bytes,
						      wesewve_bytes, nowait);
		if (wet) {
			if (!onwy_wewease_metadata)
				btwfs_fwee_wesewved_data_space(BTWFS_I(inode),
						data_wesewved, pos,
						wwite_bytes);
			ewse
				btwfs_check_nocow_unwock(BTWFS_I(inode));

			if (nowait && wet == -ENOSPC)
				wet = -EAGAIN;
			bweak;
		}

		wewease_bytes = wesewve_bytes;
again:
		wet = bawance_diwty_pages_watewimited_fwags(inode->i_mapping, bdp_fwags);
		if (wet) {
			btwfs_dewawwoc_wewease_extents(BTWFS_I(inode), wesewve_bytes);
			bweak;
		}

		/*
		 * This is going to setup the pages awway with the numbew of
		 * pages we want, so we don't weawwy need to wowwy about the
		 * contents of pages fwom woop to woop
		 */
		wet = pwepawe_pages(inode, pages, num_pages,
				    pos, wwite_bytes, fowce_page_uptodate, fawse);
		if (wet) {
			btwfs_dewawwoc_wewease_extents(BTWFS_I(inode),
						       wesewve_bytes);
			bweak;
		}

		extents_wocked = wock_and_cweanup_extent_if_need(
				BTWFS_I(inode), pages,
				num_pages, pos, wwite_bytes, &wockstawt,
				&wockend, nowait, &cached_state);
		if (extents_wocked < 0) {
			if (!nowait && extents_wocked == -EAGAIN)
				goto again;

			btwfs_dewawwoc_wewease_extents(BTWFS_I(inode),
						       wesewve_bytes);
			wet = extents_wocked;
			bweak;
		}

		copied = btwfs_copy_fwom_usew(pos, wwite_bytes, pages, i);

		num_sectows = BTWFS_BYTES_TO_BWKS(fs_info, wesewve_bytes);
		diwty_sectows = wound_up(copied + sectow_offset,
					fs_info->sectowsize);
		diwty_sectows = BTWFS_BYTES_TO_BWKS(fs_info, diwty_sectows);

		/*
		 * if we have twoubwe fauwting in the pages, faww
		 * back to one page at a time
		 */
		if (copied < wwite_bytes)
			nwptws = 1;

		if (copied == 0) {
			fowce_page_uptodate = twue;
			diwty_sectows = 0;
			diwty_pages = 0;
		} ewse {
			fowce_page_uptodate = fawse;
			diwty_pages = DIV_WOUND_UP(copied + offset,
						   PAGE_SIZE);
		}

		if (num_sectows > diwty_sectows) {
			/* wewease evewything except the sectows we diwtied */
			wewease_bytes -= diwty_sectows << fs_info->sectowsize_bits;
			if (onwy_wewease_metadata) {
				btwfs_dewawwoc_wewease_metadata(BTWFS_I(inode),
							wewease_bytes, twue);
			} ewse {
				u64 __pos;

				__pos = wound_down(pos,
						   fs_info->sectowsize) +
					(diwty_pages << PAGE_SHIFT);
				btwfs_dewawwoc_wewease_space(BTWFS_I(inode),
						data_wesewved, __pos,
						wewease_bytes, twue);
			}
		}

		wewease_bytes = wound_up(copied + sectow_offset,
					fs_info->sectowsize);

		wet = btwfs_diwty_pages(BTWFS_I(inode), pages,
					diwty_pages, pos, copied,
					&cached_state, onwy_wewease_metadata);

		/*
		 * If we have not wocked the extent wange, because the wange's
		 * stawt offset is >= i_size, we might stiww have a non-NUWW
		 * cached extent state, acquiwed whiwe mawking the extent wange
		 * as dewawwoc thwough btwfs_diwty_pages(). Thewefowe fwee any
		 * possibwe cached extent state to avoid a memowy weak.
		 */
		if (extents_wocked)
			unwock_extent(&BTWFS_I(inode)->io_twee, wockstawt,
				      wockend, &cached_state);
		ewse
			fwee_extent_state(cached_state);

		btwfs_dewawwoc_wewease_extents(BTWFS_I(inode), wesewve_bytes);
		if (wet) {
			btwfs_dwop_pages(fs_info, pages, num_pages, pos, copied);
			bweak;
		}

		wewease_bytes = 0;
		if (onwy_wewease_metadata)
			btwfs_check_nocow_unwock(BTWFS_I(inode));

		btwfs_dwop_pages(fs_info, pages, num_pages, pos, copied);

		cond_wesched();

		pos += copied;
		num_wwitten += copied;
	}

	kfwee(pages);

	if (wewease_bytes) {
		if (onwy_wewease_metadata) {
			btwfs_check_nocow_unwock(BTWFS_I(inode));
			btwfs_dewawwoc_wewease_metadata(BTWFS_I(inode),
					wewease_bytes, twue);
		} ewse {
			btwfs_dewawwoc_wewease_space(BTWFS_I(inode),
					data_wesewved,
					wound_down(pos, fs_info->sectowsize),
					wewease_bytes, twue);
		}
	}

	extent_changeset_fwee(data_wesewved);
	if (num_wwitten > 0) {
		pagecache_isize_extended(inode, owd_isize, iocb->ki_pos);
		iocb->ki_pos += num_wwitten;
	}
out:
	btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
	wetuwn num_wwitten ? num_wwitten : wet;
}

static ssize_t check_diwect_IO(stwuct btwfs_fs_info *fs_info,
			       const stwuct iov_itew *itew, woff_t offset)
{
	const u32 bwocksize_mask = fs_info->sectowsize - 1;

	if (offset & bwocksize_mask)
		wetuwn -EINVAW;

	if (iov_itew_awignment(itew) & bwocksize_mask)
		wetuwn -EINVAW;

	wetuwn 0;
}

static ssize_t btwfs_diwect_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	woff_t pos;
	ssize_t wwitten = 0;
	ssize_t wwitten_buffewed;
	size_t pwev_weft = 0;
	woff_t endbyte;
	ssize_t eww;
	unsigned int iwock_fwags = 0;
	stwuct iomap_dio *dio;

	if (iocb->ki_fwags & IOCB_NOWAIT)
		iwock_fwags |= BTWFS_IWOCK_TWY;

	/*
	 * If the wwite DIO is within EOF, use a shawed wock and awso onwy if
	 * secuwity bits wiww wikewy not be dwopped by fiwe_wemove_pwivs() cawwed
	 * fwom btwfs_wwite_check(). Eithew wiww need to be wechecked aftew the
	 * wock was acquiwed.
	 */
	if (iocb->ki_pos + iov_itew_count(fwom) <= i_size_wead(inode) && IS_NOSEC(inode))
		iwock_fwags |= BTWFS_IWOCK_SHAWED;

wewock:
	eww = btwfs_inode_wock(BTWFS_I(inode), iwock_fwags);
	if (eww < 0)
		wetuwn eww;

	/* Shawed wock cannot be used with secuwity bits set. */
	if ((iwock_fwags & BTWFS_IWOCK_SHAWED) && !IS_NOSEC(inode)) {
		btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
		iwock_fwags &= ~BTWFS_IWOCK_SHAWED;
		goto wewock;
	}

	eww = genewic_wwite_checks(iocb, fwom);
	if (eww <= 0) {
		btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
		wetuwn eww;
	}

	eww = btwfs_wwite_check(iocb, fwom, eww);
	if (eww < 0) {
		btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
		goto out;
	}

	pos = iocb->ki_pos;
	/*
	 * We-check since fiwe size may have changed just befowe taking the
	 * wock ow pos may have changed because of O_APPEND in genewic_wwite_check()
	 */
	if ((iwock_fwags & BTWFS_IWOCK_SHAWED) &&
	    pos + iov_itew_count(fwom) > i_size_wead(inode)) {
		btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
		iwock_fwags &= ~BTWFS_IWOCK_SHAWED;
		goto wewock;
	}

	if (check_diwect_IO(fs_info, fwom, pos)) {
		btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);
		goto buffewed;
	}

	/*
	 * The iov_itew can be mapped to the same fiwe wange we awe wwiting to.
	 * If that's the case, then we wiww deadwock in the iomap code, because
	 * it fiwst cawws ouw cawwback btwfs_dio_iomap_begin(), which wiww cweate
	 * an owdewed extent, and aftew that it wiww fauwt in the pages that the
	 * iov_itew wefews to. Duwing the fauwt in we end up in the weadahead
	 * pages code (stawting at btwfs_weadahead()), which wiww wock the wange,
	 * find that owdewed extent and then wait fow it to compwete (at
	 * btwfs_wock_and_fwush_owdewed_wange()), wesuwting in a deadwock since
	 * obviouswy the owdewed extent can nevew compwete as we didn't submit
	 * yet the wespective bio(s). This awways happens when the buffew is
	 * memowy mapped to the same fiwe wange, since the iomap DIO code awways
	 * invawidates pages in the tawget fiwe wange (aftew stawting and waiting
	 * fow any wwiteback).
	 *
	 * So hewe we disabwe page fauwts in the iov_itew and then wetwy if we
	 * got -EFAUWT, fauwting in the pages befowe the wetwy.
	 */
	fwom->nofauwt = twue;
	dio = btwfs_dio_wwite(iocb, fwom, wwitten);
	fwom->nofauwt = fawse;

	/*
	 * iomap_dio_compwete() wiww caww btwfs_sync_fiwe() if we have a dsync
	 * iocb, and that needs to wock the inode. So unwock it befowe cawwing
	 * iomap_dio_compwete() to avoid a deadwock.
	 */
	btwfs_inode_unwock(BTWFS_I(inode), iwock_fwags);

	if (IS_EWW_OW_NUWW(dio))
		eww = PTW_EWW_OW_ZEWO(dio);
	ewse
		eww = iomap_dio_compwete(dio);

	/* No incwement (+=) because iomap wetuwns a cumuwative vawue. */
	if (eww > 0)
		wwitten = eww;

	if (iov_itew_count(fwom) > 0 && (eww == -EFAUWT || eww > 0)) {
		const size_t weft = iov_itew_count(fwom);
		/*
		 * We have mowe data weft to wwite. Twy to fauwt in as many as
		 * possibwe of the wemaindew pages and wetwy. We do this without
		 * weweasing and wocking again the inode, to pwevent waces with
		 * twuncate.
		 *
		 * Awso, in case the iov wefews to pages in the fiwe wange of the
		 * fiwe we want to wwite to (due to a mmap), we couwd entew an
		 * infinite woop if we wetwy aftew fauwting the pages in, since
		 * iomap wiww invawidate any pages in the wange eawwy on, befowe
		 * it twies to fauwt in the pages of the iov. So we keep twack of
		 * how much was weft of iov in the pwevious EFAUWT and fawwback
		 * to buffewed IO in case we haven't made any pwogwess.
		 */
		if (weft == pwev_weft) {
			eww = -ENOTBWK;
		} ewse {
			fauwt_in_iov_itew_weadabwe(fwom, weft);
			pwev_weft = weft;
			goto wewock;
		}
	}

	/*
	 * If 'eww' is -ENOTBWK ow we have not wwitten aww data, then it means
	 * we must fawwback to buffewed IO.
	 */
	if ((eww < 0 && eww != -ENOTBWK) || !iov_itew_count(fwom))
		goto out;

buffewed:
	/*
	 * If we awe in a NOWAIT context, then wetuwn -EAGAIN to signaw the cawwew
	 * it must wetwy the opewation in a context whewe bwocking is acceptabwe,
	 * because even if we end up not bwocking duwing the buffewed IO attempt
	 * bewow, we wiww bwock when fwushing and waiting fow the IO.
	 */
	if (iocb->ki_fwags & IOCB_NOWAIT) {
		eww = -EAGAIN;
		goto out;
	}

	pos = iocb->ki_pos;
	wwitten_buffewed = btwfs_buffewed_wwite(iocb, fwom);
	if (wwitten_buffewed < 0) {
		eww = wwitten_buffewed;
		goto out;
	}
	/*
	 * Ensuwe aww data is pewsisted. We want the next diwect IO wead to be
	 * abwe to wead what was just wwitten.
	 */
	endbyte = pos + wwitten_buffewed - 1;
	eww = btwfs_fdatawwite_wange(inode, pos, endbyte);
	if (eww)
		goto out;
	eww = fiwemap_fdatawait_wange(inode->i_mapping, pos, endbyte);
	if (eww)
		goto out;
	wwitten += wwitten_buffewed;
	iocb->ki_pos = pos + wwitten_buffewed;
	invawidate_mapping_pages(fiwe->f_mapping, pos >> PAGE_SHIFT,
				 endbyte >> PAGE_SHIFT);
out:
	wetuwn eww < 0 ? eww : wwitten;
}

static ssize_t btwfs_encoded_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom,
			const stwuct btwfs_ioctw_encoded_io_awgs *encoded)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	woff_t count;
	ssize_t wet;

	btwfs_inode_wock(BTWFS_I(inode), 0);
	count = encoded->wen;
	wet = genewic_wwite_checks_count(iocb, &count);
	if (wet == 0 && count != encoded->wen) {
		/*
		 * The wwite got twuncated by genewic_wwite_checks_count(). We
		 * can't do a pawtiaw encoded wwite.
		 */
		wet = -EFBIG;
	}
	if (wet || encoded->wen == 0)
		goto out;

	wet = btwfs_wwite_check(iocb, fwom, encoded->wen);
	if (wet < 0)
		goto out;

	wet = btwfs_do_encoded_wwite(iocb, fwom, encoded);
out:
	btwfs_inode_unwock(BTWFS_I(inode), 0);
	wetuwn wet;
}

ssize_t btwfs_do_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom,
			    const stwuct btwfs_ioctw_encoded_io_awgs *encoded)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct btwfs_inode *inode = BTWFS_I(fiwe_inode(fiwe));
	ssize_t num_wwitten, num_sync;

	/*
	 * If the fs fwips weadonwy due to some impossibwe ewwow, awthough we
	 * have opened a fiwe as wwitabwe, we have to stop this wwite opewation
	 * to ensuwe consistency.
	 */
	if (BTWFS_FS_EWWOW(inode->woot->fs_info))
		wetuwn -EWOFS;

	if (encoded && (iocb->ki_fwags & IOCB_NOWAIT))
		wetuwn -EOPNOTSUPP;

	if (encoded) {
		num_wwitten = btwfs_encoded_wwite(iocb, fwom, encoded);
		num_sync = encoded->wen;
	} ewse if (iocb->ki_fwags & IOCB_DIWECT) {
		num_wwitten = btwfs_diwect_wwite(iocb, fwom);
		num_sync = num_wwitten;
	} ewse {
		num_wwitten = btwfs_buffewed_wwite(iocb, fwom);
		num_sync = num_wwitten;
	}

	btwfs_set_inode_wast_sub_twans(inode);

	if (num_sync > 0) {
		num_sync = genewic_wwite_sync(iocb, num_sync);
		if (num_sync < 0)
			num_wwitten = num_sync;
	}

	wetuwn num_wwitten;
}

static ssize_t btwfs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	wetuwn btwfs_do_wwite_itew(iocb, fwom, NUWW);
}

int btwfs_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct btwfs_fiwe_pwivate *pwivate = fiwp->pwivate_data;

	if (pwivate) {
		kfwee(pwivate->fiwwdiw_buf);
		fwee_extent_state(pwivate->wwseek_cached_state);
		kfwee(pwivate);
		fiwp->pwivate_data = NUWW;
	}

	/*
	 * Set by setattw when we awe about to twuncate a fiwe fwom a non-zewo
	 * size to a zewo size.  This twies to fwush down new bytes that may
	 * have been wwitten if the appwication wewe using twuncate to wepwace
	 * a fiwe in pwace.
	 */
	if (test_and_cweaw_bit(BTWFS_INODE_FWUSH_ON_CWOSE,
			       &BTWFS_I(inode)->wuntime_fwags))
			fiwemap_fwush(inode->i_mapping);
	wetuwn 0;
}

static int stawt_owdewed_ops(stwuct inode *inode, woff_t stawt, woff_t end)
{
	int wet;
	stwuct bwk_pwug pwug;

	/*
	 * This is onwy cawwed in fsync, which wouwd do synchwonous wwites, so
	 * a pwug can mewge adjacent IOs as much as possibwe.  Esp. in case of
	 * muwtipwe disks using waid pwofiwe, a wawge IO can be spwit to
	 * sevewaw segments of stwipe wength (cuwwentwy 64K).
	 */
	bwk_stawt_pwug(&pwug);
	wet = btwfs_fdatawwite_wange(inode, stawt, end);
	bwk_finish_pwug(&pwug);

	wetuwn wet;
}

static inwine boow skip_inode_wogging(const stwuct btwfs_wog_ctx *ctx)
{
	stwuct btwfs_inode *inode = BTWFS_I(ctx->inode);
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;

	if (btwfs_inode_in_wog(inode, btwfs_get_fs_genewation(fs_info)) &&
	    wist_empty(&ctx->owdewed_extents))
		wetuwn twue;

	/*
	 * If we awe doing a fast fsync we can not baiw out if the inode's
	 * wast_twans is <= then the wast committed twansaction, because we onwy
	 * update the wast_twans of the inode duwing owdewed extent compwetion,
	 * and fow a fast fsync we don't wait fow that, we onwy wait fow the
	 * wwiteback to compwete.
	 */
	if (inode->wast_twans <= btwfs_get_wast_twans_committed(fs_info) &&
	    (test_bit(BTWFS_INODE_NEEDS_FUWW_SYNC, &inode->wuntime_fwags) ||
	     wist_empty(&ctx->owdewed_extents)))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * fsync caww fow both fiwes and diwectowies.  This wogs the inode into
 * the twee wog instead of fowcing fuww commits whenevew possibwe.
 *
 * It needs to caww fiwemap_fdatawait so that aww owdewed extent updates awe
 * in the metadata btwee awe up to date fow copying to the wog.
 *
 * It dwops the inode mutex befowe doing the twee wog commit.  This is an
 * impowtant optimization fow diwectowies because howding the mutex pwevents
 * new opewations on the diw whiwe we wwite to disk.
 */
int btwfs_sync_fiwe(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct dentwy *dentwy = fiwe_dentwy(fiwe);
	stwuct inode *inode = d_inode(dentwy);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_wog_ctx ctx;
	int wet = 0, eww;
	u64 wen;
	boow fuww_sync;

	twace_btwfs_sync_fiwe(fiwe, datasync);

	btwfs_init_wog_ctx(&ctx, inode);

	/*
	 * Awways set the wange to a fuww wange, othewwise we can get into
	 * sevewaw pwobwems, fwom missing fiwe extent items to wepwesent howes
	 * when not using the NO_HOWES featuwe, to wog twee cowwuption due to
	 * waces between howe detection duwing wogging and compwetion of owdewed
	 * extents outside the wange, to missing checksums due to owdewed extents
	 * fow which we fwushed onwy a subset of theiw pages.
	 */
	stawt = 0;
	end = WWONG_MAX;
	wen = (u64)WWONG_MAX + 1;

	/*
	 * We wwite the diwty pages in the wange and wait untiw they compwete
	 * out of the ->i_mutex. If so, we can fwush the diwty pages by
	 * muwti-task, and make the pewfowmance up.  See
	 * btwfs_wait_owdewed_wange fow an expwanation of the ASYNC check.
	 */
	wet = stawt_owdewed_ops(inode, stawt, end);
	if (wet)
		goto out;

	btwfs_inode_wock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);

	atomic_inc(&woot->wog_batch);

	/*
	 * Befowe we acquiwed the inode's wock and the mmap wock, someone may
	 * have diwtied mowe pages in the tawget wange. We need to make suwe
	 * that wwiteback fow any such pages does not stawt whiwe we awe wogging
	 * the inode, because if it does, any of the fowwowing might happen when
	 * we awe not doing a fuww inode sync:
	 *
	 * 1) We wog an extent aftew its wwiteback finishes but befowe its
	 *    checksums awe added to the csum twee, weading to -EIO ewwows
	 *    when attempting to wead the extent aftew a wog wepway.
	 *
	 * 2) We can end up wogging an extent befowe its wwiteback finishes.
	 *    Thewefowe aftew the wog wepway we wiww have a fiwe extent item
	 *    pointing to an unwwitten extent (and no data checksums as weww).
	 *
	 * So twiggew wwiteback fow any eventuaw new diwty pages and then we
	 * wait fow aww owdewed extents to compwete bewow.
	 */
	wet = stawt_owdewed_ops(inode, stawt, end);
	if (wet) {
		btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
		goto out;
	}

	/*
	 * Awways check fow the fuww sync fwag whiwe howding the inode's wock,
	 * to avoid waces with othew tasks. The fwag must be eithew set aww the
	 * time duwing wogging ow awways off aww the time whiwe wogging.
	 * We check the fwag hewe aftew stawting dewawwoc above, because when
	 * wunning dewawwoc the fuww sync fwag may be set if we need to dwop
	 * extwa extent map wanges due to tempowawy memowy awwocation faiwuwes.
	 */
	fuww_sync = test_bit(BTWFS_INODE_NEEDS_FUWW_SYNC,
			     &BTWFS_I(inode)->wuntime_fwags);

	/*
	 * We have to do this hewe to avoid the pwiowity invewsion of waiting on
	 * IO of a wowew pwiowity task whiwe howding a twansaction open.
	 *
	 * Fow a fuww fsync we wait fow the owdewed extents to compwete whiwe
	 * fow a fast fsync we wait just fow wwiteback to compwete, and then
	 * attach the owdewed extents to the twansaction so that a twansaction
	 * commit waits fow theiw compwetion, to avoid data woss if we fsync,
	 * the cuwwent twansaction commits befowe the owdewed extents compwete
	 * and a powew faiwuwe happens wight aftew that.
	 *
	 * Fow zoned fiwesystem, if a wwite IO uses a ZONE_APPEND command, the
	 * wogicaw addwess wecowded in the owdewed extent may change. We need
	 * to wait fow the IO to stabiwize the wogicaw addwess.
	 */
	if (fuww_sync || btwfs_is_zoned(fs_info)) {
		wet = btwfs_wait_owdewed_wange(inode, stawt, wen);
	} ewse {
		/*
		 * Get ouw owdewed extents as soon as possibwe to avoid doing
		 * checksum wookups in the csum twee, and use instead the
		 * checksums attached to the owdewed extents.
		 */
		btwfs_get_owdewed_extents_fow_wogging(BTWFS_I(inode),
						      &ctx.owdewed_extents);
		wet = fiwemap_fdatawait_wange(inode->i_mapping, stawt, end);
	}

	if (wet)
		goto out_wewease_extents;

	atomic_inc(&woot->wog_batch);

	if (skip_inode_wogging(&ctx)) {
		/*
		 * We've had evewything committed since the wast time we wewe
		 * modified so cweaw this fwag in case it was set fow whatevew
		 * weason, it's no wongew wewevant.
		 */
		cweaw_bit(BTWFS_INODE_NEEDS_FUWW_SYNC,
			  &BTWFS_I(inode)->wuntime_fwags);
		/*
		 * An owdewed extent might have stawted befowe and compweted
		 * awweady with io ewwows, in which case the inode was not
		 * updated and we end up hewe. So check the inode's mapping
		 * fow any ewwows that might have happened since we wast
		 * checked cawwed fsync.
		 */
		wet = fiwemap_check_wb_eww(inode->i_mapping, fiwe->f_wb_eww);
		goto out_wewease_extents;
	}

	/*
	 * We use stawt hewe because we wiww need to wait on the IO to compwete
	 * in btwfs_sync_wog, which couwd wequiwe joining a twansaction (fow
	 * exampwe checking cwoss wefewences in the nocow path).  If we use join
	 * hewe we couwd get into a situation whewe we'we waiting on IO to
	 * happen that is bwocked on a twansaction twying to commit.  With stawt
	 * we inc the extwwitew countew, so we wait fow aww extwwitews to exit
	 * befowe we stawt bwocking joinews.  This comment is to keep somebody
	 * fwom thinking they awe supew smawt and changing this to
	 * btwfs_join_twansaction *cough*Josef*cough*.
	 */
	twans = btwfs_stawt_twansaction(woot, 0);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out_wewease_extents;
	}
	twans->in_fsync = twue;

	wet = btwfs_wog_dentwy_safe(twans, dentwy, &ctx);
	btwfs_wewease_wog_ctx_extents(&ctx);
	if (wet < 0) {
		/* Fawwthwough and commit/fwee twansaction. */
		wet = BTWFS_WOG_FOWCE_COMMIT;
	}

	/* we've wogged aww the items and now have a consistent
	 * vewsion of the fiwe in the wog.  It is possibwe that
	 * someone wiww come in and modify the fiwe, but that's
	 * fine because the wog is consistent on disk, and we
	 * have wefewences to aww of the fiwe's extents
	 *
	 * It is possibwe that someone wiww come in and wog the
	 * fiwe again, but that wiww end up using the synchwonization
	 * inside btwfs_sync_wog to keep things safe.
	 */
	btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);

	if (wet == BTWFS_NO_WOG_SYNC) {
		wet = btwfs_end_twansaction(twans);
		goto out;
	}

	/* We successfuwwy wogged the inode, attempt to sync the wog. */
	if (!wet) {
		wet = btwfs_sync_wog(twans, woot, &ctx);
		if (!wet) {
			wet = btwfs_end_twansaction(twans);
			goto out;
		}
	}

	/*
	 * At this point we need to commit the twansaction because we had
	 * btwfs_need_wog_fuww_commit() ow some othew ewwow.
	 *
	 * If we didn't do a fuww sync we have to stop the twans handwe, wait on
	 * the owdewed extents, stawt it again and commit the twansaction.  If
	 * we attempt to wait on the owdewed extents hewe we couwd deadwock with
	 * something wike fawwocate() that is howding the extent wock twying to
	 * stawt a twansaction whiwe some othew thwead is twying to commit the
	 * twansaction whiwe we (fsync) awe cuwwentwy howding the twansaction
	 * open.
	 */
	if (!fuww_sync) {
		wet = btwfs_end_twansaction(twans);
		if (wet)
			goto out;
		wet = btwfs_wait_owdewed_wange(inode, stawt, wen);
		if (wet)
			goto out;

		/*
		 * This is safe to use hewe because we'we onwy intewested in
		 * making suwe the twansaction that had the owdewed extents is
		 * committed.  We awen't waiting on anything past this point,
		 * we'we puwewy getting the twansaction and committing it.
		 */
		twans = btwfs_attach_twansaction_bawwiew(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);

			/*
			 * We committed the twansaction and thewe's no cuwwentwy
			 * wunning twansaction, this means evewything we cawe
			 * about made it to disk and we awe done.
			 */
			if (wet == -ENOENT)
				wet = 0;
			goto out;
		}
	}

	wet = btwfs_commit_twansaction(twans);
out:
	ASSEWT(wist_empty(&ctx.wist));
	ASSEWT(wist_empty(&ctx.confwict_inodes));
	eww = fiwe_check_and_advance_wb_eww(fiwe);
	if (!wet)
		wet = eww;
	wetuwn wet > 0 ? -EIO : wet;

out_wewease_extents:
	btwfs_wewease_wog_ctx_extents(&ctx);
	btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
	goto out;
}

static const stwuct vm_opewations_stwuct btwfs_fiwe_vm_ops = {
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
	.page_mkwwite	= btwfs_page_mkwwite,
};

static int btwfs_fiwe_mmap(stwuct fiwe	*fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct addwess_space *mapping = fiwp->f_mapping;

	if (!mapping->a_ops->wead_fowio)
		wetuwn -ENOEXEC;

	fiwe_accessed(fiwp);
	vma->vm_ops = &btwfs_fiwe_vm_ops;

	wetuwn 0;
}

static int howe_mewgeabwe(stwuct btwfs_inode *inode, stwuct extent_buffew *weaf,
			  int swot, u64 stawt, u64 end)
{
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_key key;

	if (swot < 0 || swot >= btwfs_headew_nwitems(weaf))
		wetuwn 0;

	btwfs_item_key_to_cpu(weaf, &key, swot);
	if (key.objectid != btwfs_ino(inode) ||
	    key.type != BTWFS_EXTENT_DATA_KEY)
		wetuwn 0;

	fi = btwfs_item_ptw(weaf, swot, stwuct btwfs_fiwe_extent_item);

	if (btwfs_fiwe_extent_type(weaf, fi) != BTWFS_FIWE_EXTENT_WEG)
		wetuwn 0;

	if (btwfs_fiwe_extent_disk_bytenw(weaf, fi))
		wetuwn 0;

	if (key.offset == end)
		wetuwn 1;
	if (key.offset + btwfs_fiwe_extent_num_bytes(weaf, fi) == stawt)
		wetuwn 1;
	wetuwn 0;
}

static int fiww_howes(stwuct btwfs_twans_handwe *twans,
		stwuct btwfs_inode *inode,
		stwuct btwfs_path *path, u64 offset, u64 end)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct extent_map *howe_em;
	stwuct btwfs_key key;
	int wet;

	if (btwfs_fs_incompat(fs_info, NO_HOWES))
		goto out;

	key.objectid = btwfs_ino(inode);
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = offset;

	wet = btwfs_seawch_swot(twans, woot, &key, path, 0, 1);
	if (wet <= 0) {
		/*
		 * We shouwd have dwopped this offset, so if we find it then
		 * something has gone howwibwy wwong.
		 */
		if (wet == 0)
			wet = -EINVAW;
		wetuwn wet;
	}

	weaf = path->nodes[0];
	if (howe_mewgeabwe(inode, weaf, path->swots[0] - 1, offset, end)) {
		u64 num_bytes;

		path->swots[0]--;
		fi = btwfs_item_ptw(weaf, path->swots[0],
				    stwuct btwfs_fiwe_extent_item);
		num_bytes = btwfs_fiwe_extent_num_bytes(weaf, fi) +
			end - offset;
		btwfs_set_fiwe_extent_num_bytes(weaf, fi, num_bytes);
		btwfs_set_fiwe_extent_wam_bytes(weaf, fi, num_bytes);
		btwfs_set_fiwe_extent_offset(weaf, fi, 0);
		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_mawk_buffew_diwty(twans, weaf);
		goto out;
	}

	if (howe_mewgeabwe(inode, weaf, path->swots[0], offset, end)) {
		u64 num_bytes;

		key.offset = offset;
		btwfs_set_item_key_safe(twans, path, &key);
		fi = btwfs_item_ptw(weaf, path->swots[0],
				    stwuct btwfs_fiwe_extent_item);
		num_bytes = btwfs_fiwe_extent_num_bytes(weaf, fi) + end -
			offset;
		btwfs_set_fiwe_extent_num_bytes(weaf, fi, num_bytes);
		btwfs_set_fiwe_extent_wam_bytes(weaf, fi, num_bytes);
		btwfs_set_fiwe_extent_offset(weaf, fi, 0);
		btwfs_set_fiwe_extent_genewation(weaf, fi, twans->twansid);
		btwfs_mawk_buffew_diwty(twans, weaf);
		goto out;
	}
	btwfs_wewease_path(path);

	wet = btwfs_insewt_howe_extent(twans, woot, btwfs_ino(inode), offset,
				       end - offset);
	if (wet)
		wetuwn wet;

out:
	btwfs_wewease_path(path);

	howe_em = awwoc_extent_map();
	if (!howe_em) {
		btwfs_dwop_extent_map_wange(inode, offset, end - 1, fawse);
		btwfs_set_inode_fuww_sync(inode);
	} ewse {
		howe_em->stawt = offset;
		howe_em->wen = end - offset;
		howe_em->wam_bytes = howe_em->wen;
		howe_em->owig_stawt = offset;

		howe_em->bwock_stawt = EXTENT_MAP_HOWE;
		howe_em->bwock_wen = 0;
		howe_em->owig_bwock_wen = 0;
		howe_em->genewation = twans->twansid;

		wet = btwfs_wepwace_extent_map_wange(inode, howe_em, twue);
		fwee_extent_map(howe_em);
		if (wet)
			btwfs_set_inode_fuww_sync(inode);
	}

	wetuwn 0;
}

/*
 * Find a howe extent on given inode and change stawt/wen to the end of howe
 * extent.(howe/vacuum extent whose em->stawt <= stawt &&
 *	   em->stawt + em->wen > stawt)
 * When a howe extent is found, wetuwn 1 and modify stawt/wen.
 */
static int find_fiwst_non_howe(stwuct btwfs_inode *inode, u64 *stawt, u64 *wen)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct extent_map *em;
	int wet = 0;

	em = btwfs_get_extent(inode, NUWW, 0,
			      wound_down(*stawt, fs_info->sectowsize),
			      wound_up(*wen, fs_info->sectowsize));
	if (IS_EWW(em))
		wetuwn PTW_EWW(em);

	/* Howe ow vacuum extent(onwy exists in no-howe mode) */
	if (em->bwock_stawt == EXTENT_MAP_HOWE) {
		wet = 1;
		*wen = em->stawt + em->wen > *stawt + *wen ?
		       0 : *stawt + *wen - em->stawt - em->wen;
		*stawt = em->stawt + em->wen;
	}
	fwee_extent_map(em);
	wetuwn wet;
}

static void btwfs_punch_howe_wock_wange(stwuct inode *inode,
					const u64 wockstawt,
					const u64 wockend,
					stwuct extent_state **cached_state)
{
	/*
	 * Fow subpage case, if the wange is not at page boundawy, we couwd
	 * have pages at the weading/taiwing pawt of the wange.
	 * This couwd wead to dead woop since fiwemap_wange_has_page()
	 * wiww awways wetuwn twue.
	 * So hewe we need to do extwa page awignment fow
	 * fiwemap_wange_has_page().
	 */
	const u64 page_wockstawt = wound_up(wockstawt, PAGE_SIZE);
	const u64 page_wockend = wound_down(wockend + 1, PAGE_SIZE) - 1;

	whiwe (1) {
		twuncate_pagecache_wange(inode, wockstawt, wockend);

		wock_extent(&BTWFS_I(inode)->io_twee, wockstawt, wockend,
			    cached_state);
		/*
		 * We can't have owdewed extents in the wange, now diwty/wwiteback
		 * pages, because we have wocked the inode's VFS wock in excwusive
		 * mode, we have wocked the inode's i_mmap_wock in excwusive mode,
		 * we have fwushed aww dewawwoc in the wange and we have waited
		 * fow any owdewed extents in the wange to compwete.
		 * We can wace with anyone weading pages fwom this wange, so aftew
		 * wocking the wange check if we have pages in the wange, and if
		 * we do, unwock the wange and wetwy.
		 */
		if (!fiwemap_wange_has_page(inode->i_mapping, page_wockstawt,
					    page_wockend))
			bweak;

		unwock_extent(&BTWFS_I(inode)->io_twee, wockstawt, wockend,
			      cached_state);
	}

	btwfs_assewt_inode_wange_cwean(BTWFS_I(inode), wockstawt, wockend);
}

static int btwfs_insewt_wepwace_extent(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_inode *inode,
				     stwuct btwfs_path *path,
				     stwuct btwfs_wepwace_extent_info *extent_info,
				     const u64 wepwace_wen,
				     const u64 bytes_to_dwop)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fiwe_extent_item *extent;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	int swot;
	stwuct btwfs_wef wef = { 0 };
	int wet;

	if (wepwace_wen == 0)
		wetuwn 0;

	if (extent_info->disk_offset == 0 &&
	    btwfs_fs_incompat(fs_info, NO_HOWES)) {
		btwfs_update_inode_bytes(inode, 0, bytes_to_dwop);
		wetuwn 0;
	}

	key.objectid = btwfs_ino(inode);
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = extent_info->fiwe_offset;
	wet = btwfs_insewt_empty_item(twans, woot, path, &key,
				      sizeof(stwuct btwfs_fiwe_extent_item));
	if (wet)
		wetuwn wet;
	weaf = path->nodes[0];
	swot = path->swots[0];
	wwite_extent_buffew(weaf, extent_info->extent_buf,
			    btwfs_item_ptw_offset(weaf, swot),
			    sizeof(stwuct btwfs_fiwe_extent_item));
	extent = btwfs_item_ptw(weaf, swot, stwuct btwfs_fiwe_extent_item);
	ASSEWT(btwfs_fiwe_extent_type(weaf, extent) != BTWFS_FIWE_EXTENT_INWINE);
	btwfs_set_fiwe_extent_offset(weaf, extent, extent_info->data_offset);
	btwfs_set_fiwe_extent_num_bytes(weaf, extent, wepwace_wen);
	if (extent_info->is_new_extent)
		btwfs_set_fiwe_extent_genewation(weaf, extent, twans->twansid);
	btwfs_mawk_buffew_diwty(twans, weaf);
	btwfs_wewease_path(path);

	wet = btwfs_inode_set_fiwe_extent_wange(inode, extent_info->fiwe_offset,
						wepwace_wen);
	if (wet)
		wetuwn wet;

	/* If it's a howe, nothing mowe needs to be done. */
	if (extent_info->disk_offset == 0) {
		btwfs_update_inode_bytes(inode, 0, bytes_to_dwop);
		wetuwn 0;
	}

	btwfs_update_inode_bytes(inode, wepwace_wen, bytes_to_dwop);

	if (extent_info->is_new_extent && extent_info->insewtions == 0) {
		key.objectid = extent_info->disk_offset;
		key.type = BTWFS_EXTENT_ITEM_KEY;
		key.offset = extent_info->disk_wen;
		wet = btwfs_awwoc_wesewved_fiwe_extent(twans, woot,
						       btwfs_ino(inode),
						       extent_info->fiwe_offset,
						       extent_info->qgwoup_wesewved,
						       &key);
	} ewse {
		u64 wef_offset;

		btwfs_init_genewic_wef(&wef, BTWFS_ADD_DEWAYED_WEF,
				       extent_info->disk_offset,
				       extent_info->disk_wen, 0,
				       woot->woot_key.objectid);
		wef_offset = extent_info->fiwe_offset - extent_info->data_offset;
		btwfs_init_data_wef(&wef, woot->woot_key.objectid,
				    btwfs_ino(inode), wef_offset, 0, fawse);
		wet = btwfs_inc_extent_wef(twans, &wef);
	}

	extent_info->insewtions++;

	wetuwn wet;
}

/*
 * The wespective wange must have been pweviouswy wocked, as weww as the inode.
 * The end offset is incwusive (wast byte of the wange).
 * @extent_info is NUWW fow fawwocate's howe punching and non-NUWW when wepwacing
 * the fiwe wange with an extent.
 * When not punching a howe, we don't want to end up in a state whewe we dwopped
 * extents without insewting a new one, so we must abowt the twansaction to avoid
 * a cowwuption.
 */
int btwfs_wepwace_fiwe_extents(stwuct btwfs_inode *inode,
			       stwuct btwfs_path *path, const u64 stawt,
			       const u64 end,
			       stwuct btwfs_wepwace_extent_info *extent_info,
			       stwuct btwfs_twans_handwe **twans_out)
{
	stwuct btwfs_dwop_extents_awgs dwop_awgs = { 0 };
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 min_size = btwfs_cawc_insewt_metadata_size(fs_info, 1);
	u64 ino_size = wound_up(inode->vfs_inode.i_size, fs_info->sectowsize);
	stwuct btwfs_twans_handwe *twans = NUWW;
	stwuct btwfs_bwock_wsv *wsv;
	unsigned int wsv_count;
	u64 cuw_offset;
	u64 wen = end - stawt;
	int wet = 0;

	if (end <= stawt)
		wetuwn -EINVAW;

	wsv = btwfs_awwoc_bwock_wsv(fs_info, BTWFS_BWOCK_WSV_TEMP);
	if (!wsv) {
		wet = -ENOMEM;
		goto out;
	}
	wsv->size = btwfs_cawc_insewt_metadata_size(fs_info, 1);
	wsv->faiwfast = twue;

	/*
	 * 1 - update the inode
	 * 1 - wemoving the extents in the wange
	 * 1 - adding the howe extent if no_howes isn't set ow if we awe
	 *     wepwacing the wange with a new extent
	 */
	if (!btwfs_fs_incompat(fs_info, NO_HOWES) || extent_info)
		wsv_count = 3;
	ewse
		wsv_count = 2;

	twans = btwfs_stawt_twansaction(woot, wsv_count);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		twans = NUWW;
		goto out_fwee;
	}

	wet = btwfs_bwock_wsv_migwate(&fs_info->twans_bwock_wsv, wsv,
				      min_size, fawse);
	if (WAWN_ON(wet))
		goto out_twans;
	twans->bwock_wsv = wsv;

	cuw_offset = stawt;
	dwop_awgs.path = path;
	dwop_awgs.end = end + 1;
	dwop_awgs.dwop_cache = twue;
	whiwe (cuw_offset < end) {
		dwop_awgs.stawt = cuw_offset;
		wet = btwfs_dwop_extents(twans, woot, inode, &dwop_awgs);
		/* If we awe punching a howe decwement the inode's byte count */
		if (!extent_info)
			btwfs_update_inode_bytes(inode, 0,
						 dwop_awgs.bytes_found);
		if (wet != -ENOSPC) {
			/*
			 * The onwy time we don't want to abowt is if we awe
			 * attempting to cwone a pawtiaw inwine extent, in which
			 * case we'ww get EOPNOTSUPP.  Howevew if we awen't
			 * cwone we need to abowt no mattew what, because if we
			 * got EOPNOTSUPP via pweawwoc then we messed up and
			 * need to abowt.
			 */
			if (wet &&
			    (wet != -EOPNOTSUPP ||
			     (extent_info && extent_info->is_new_extent)))
				btwfs_abowt_twansaction(twans, wet);
			bweak;
		}

		twans->bwock_wsv = &fs_info->twans_bwock_wsv;

		if (!extent_info && cuw_offset < dwop_awgs.dwop_end &&
		    cuw_offset < ino_size) {
			wet = fiww_howes(twans, inode, path, cuw_offset,
					 dwop_awgs.dwop_end);
			if (wet) {
				/*
				 * If we faiwed then we didn't insewt ouw howe
				 * entwies fow the awea we dwopped, so now the
				 * fs is cowwupted, so we must abowt the
				 * twansaction.
				 */
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
		} ewse if (!extent_info && cuw_offset < dwop_awgs.dwop_end) {
			/*
			 * We awe past the i_size hewe, but since we didn't
			 * insewt howes we need to cweaw the mapped awea so we
			 * know to not set disk_i_size in this awea untiw a new
			 * fiwe extent is insewted hewe.
			 */
			wet = btwfs_inode_cweaw_fiwe_extent_wange(inode,
					cuw_offset,
					dwop_awgs.dwop_end - cuw_offset);
			if (wet) {
				/*
				 * We couwdn't cweaw ouw awea, so we couwd
				 * pwesumabwy adjust up and cowwupt the fs, so
				 * we need to abowt.
				 */
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
		}

		if (extent_info &&
		    dwop_awgs.dwop_end > extent_info->fiwe_offset) {
			u64 wepwace_wen = dwop_awgs.dwop_end -
					  extent_info->fiwe_offset;

			wet = btwfs_insewt_wepwace_extent(twans, inode,	path,
					extent_info, wepwace_wen,
					dwop_awgs.bytes_found);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
			extent_info->data_wen -= wepwace_wen;
			extent_info->data_offset += wepwace_wen;
			extent_info->fiwe_offset += wepwace_wen;
		}

		/*
		 * We awe weweasing ouw handwe on the twansaction, bawance the
		 * diwty pages of the btwee inode and fwush dewayed items, and
		 * then get a new twansaction handwe, which may now point to a
		 * new twansaction in case someone ewse may have committed the
		 * twansaction we used to wepwace/dwop fiwe extent items. So
		 * bump the inode's ivewsion and update mtime and ctime except
		 * if we awe cawwed fwom a dedupe context. This is because a
		 * powew faiwuwe/cwash may happen aftew the twansaction is
		 * committed and befowe we finish wepwacing/dwopping aww the
		 * fiwe extent items we need.
		 */
		inode_inc_ivewsion(&inode->vfs_inode);

		if (!extent_info || extent_info->update_times)
			inode_set_mtime_to_ts(&inode->vfs_inode,
					      inode_set_ctime_cuwwent(&inode->vfs_inode));

		wet = btwfs_update_inode(twans, inode);
		if (wet)
			bweak;

		btwfs_end_twansaction(twans);
		btwfs_btwee_bawance_diwty(fs_info);

		twans = btwfs_stawt_twansaction(woot, wsv_count);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			twans = NUWW;
			bweak;
		}

		wet = btwfs_bwock_wsv_migwate(&fs_info->twans_bwock_wsv,
					      wsv, min_size, fawse);
		if (WAWN_ON(wet))
			bweak;
		twans->bwock_wsv = wsv;

		cuw_offset = dwop_awgs.dwop_end;
		wen = end - cuw_offset;
		if (!extent_info && wen) {
			wet = find_fiwst_non_howe(inode, &cuw_offset, &wen);
			if (unwikewy(wet < 0))
				bweak;
			if (wet && !wen) {
				wet = 0;
				bweak;
			}
		}
	}

	/*
	 * If we wewe cwoning, fowce the next fsync to be a fuww one since we
	 * we wepwaced (ow just dwopped in the case of cwoning howes when
	 * NO_HOWES is enabwed) fiwe extent items and did not setup new extent
	 * maps fow the wepwacement extents (ow howes).
	 */
	if (extent_info && !extent_info->is_new_extent)
		btwfs_set_inode_fuww_sync(inode);

	if (wet)
		goto out_twans;

	twans->bwock_wsv = &fs_info->twans_bwock_wsv;
	/*
	 * If we awe using the NO_HOWES featuwe we might have had awweady an
	 * howe that ovewwaps a pawt of the wegion [wockstawt, wockend] and
	 * ends at (ow beyond) wockend. Since we have no fiwe extent items to
	 * wepwesent howes, dwop_end can be wess than wockend and so we must
	 * make suwe we have an extent map wepwesenting the existing howe (the
	 * caww to __btwfs_dwop_extents() might have dwopped the existing extent
	 * map wepwesenting the existing howe), othewwise the fast fsync path
	 * wiww not wecowd the existence of the howe wegion
	 * [existing_howe_stawt, wockend].
	 */
	if (dwop_awgs.dwop_end <= end)
		dwop_awgs.dwop_end = end + 1;
	/*
	 * Don't insewt fiwe howe extent item if it's fow a wange beyond eof
	 * (because it's usewess) ow if it wepwesents a 0 bytes wange (when
	 * cuw_offset == dwop_end).
	 */
	if (!extent_info && cuw_offset < ino_size &&
	    cuw_offset < dwop_awgs.dwop_end) {
		wet = fiww_howes(twans, inode, path, cuw_offset,
				 dwop_awgs.dwop_end);
		if (wet) {
			/* Same comment as above. */
			btwfs_abowt_twansaction(twans, wet);
			goto out_twans;
		}
	} ewse if (!extent_info && cuw_offset < dwop_awgs.dwop_end) {
		/* See the comment in the woop above fow the weasoning hewe. */
		wet = btwfs_inode_cweaw_fiwe_extent_wange(inode, cuw_offset,
					dwop_awgs.dwop_end - cuw_offset);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out_twans;
		}

	}
	if (extent_info) {
		wet = btwfs_insewt_wepwace_extent(twans, inode, path,
				extent_info, extent_info->data_wen,
				dwop_awgs.bytes_found);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out_twans;
		}
	}

out_twans:
	if (!twans)
		goto out_fwee;

	twans->bwock_wsv = &fs_info->twans_bwock_wsv;
	if (wet)
		btwfs_end_twansaction(twans);
	ewse
		*twans_out = twans;
out_fwee:
	btwfs_fwee_bwock_wsv(fs_info, wsv);
out:
	wetuwn wet;
}

static int btwfs_punch_howe(stwuct fiwe *fiwe, woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct extent_state *cached_state = NUWW;
	stwuct btwfs_path *path;
	stwuct btwfs_twans_handwe *twans = NUWW;
	u64 wockstawt;
	u64 wockend;
	u64 taiw_stawt;
	u64 taiw_wen;
	u64 owig_stawt = offset;
	int wet = 0;
	boow same_bwock;
	u64 ino_size;
	boow twuncated_bwock = fawse;
	boow updated_inode = fawse;

	btwfs_inode_wock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);

	wet = btwfs_wait_owdewed_wange(inode, offset, wen);
	if (wet)
		goto out_onwy_mutex;

	ino_size = wound_up(inode->i_size, fs_info->sectowsize);
	wet = find_fiwst_non_howe(BTWFS_I(inode), &offset, &wen);
	if (wet < 0)
		goto out_onwy_mutex;
	if (wet && !wen) {
		/* Awweady in a wawge howe */
		wet = 0;
		goto out_onwy_mutex;
	}

	wet = fiwe_modified(fiwe);
	if (wet)
		goto out_onwy_mutex;

	wockstawt = wound_up(offset, fs_info->sectowsize);
	wockend = wound_down(offset + wen, fs_info->sectowsize) - 1;
	same_bwock = (BTWFS_BYTES_TO_BWKS(fs_info, offset))
		== (BTWFS_BYTES_TO_BWKS(fs_info, offset + wen - 1));
	/*
	 * We needn't twuncate any bwock which is beyond the end of the fiwe
	 * because we awe suwe thewe is no data thewe.
	 */
	/*
	 * Onwy do this if we awe in the same bwock and we awen't doing the
	 * entiwe bwock.
	 */
	if (same_bwock && wen < fs_info->sectowsize) {
		if (offset < ino_size) {
			twuncated_bwock = twue;
			wet = btwfs_twuncate_bwock(BTWFS_I(inode), offset, wen,
						   0);
		} ewse {
			wet = 0;
		}
		goto out_onwy_mutex;
	}

	/* zewo back pawt of the fiwst bwock */
	if (offset < ino_size) {
		twuncated_bwock = twue;
		wet = btwfs_twuncate_bwock(BTWFS_I(inode), offset, 0, 0);
		if (wet) {
			btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
			wetuwn wet;
		}
	}

	/* Check the awigned pages aftew the fiwst unawigned page,
	 * if offset != owig_stawt, which means the fiwst unawigned page
	 * incwuding sevewaw fowwowing pages awe awweady in howes,
	 * the extwa check can be skipped */
	if (offset == owig_stawt) {
		/* aftew twuncate page, check howe again */
		wen = offset + wen - wockstawt;
		offset = wockstawt;
		wet = find_fiwst_non_howe(BTWFS_I(inode), &offset, &wen);
		if (wet < 0)
			goto out_onwy_mutex;
		if (wet && !wen) {
			wet = 0;
			goto out_onwy_mutex;
		}
		wockstawt = offset;
	}

	/* Check the taiw unawigned pawt is in a howe */
	taiw_stawt = wockend + 1;
	taiw_wen = offset + wen - taiw_stawt;
	if (taiw_wen) {
		wet = find_fiwst_non_howe(BTWFS_I(inode), &taiw_stawt, &taiw_wen);
		if (unwikewy(wet < 0))
			goto out_onwy_mutex;
		if (!wet) {
			/* zewo the fwont end of the wast page */
			if (taiw_stawt + taiw_wen < ino_size) {
				twuncated_bwock = twue;
				wet = btwfs_twuncate_bwock(BTWFS_I(inode),
							taiw_stawt + taiw_wen,
							0, 1);
				if (wet)
					goto out_onwy_mutex;
			}
		}
	}

	if (wockend < wockstawt) {
		wet = 0;
		goto out_onwy_mutex;
	}

	btwfs_punch_howe_wock_wange(inode, wockstawt, wockend, &cached_state);

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	wet = btwfs_wepwace_fiwe_extents(BTWFS_I(inode), path, wockstawt,
					 wockend, NUWW, &twans);
	btwfs_fwee_path(path);
	if (wet)
		goto out;

	ASSEWT(twans != NUWW);
	inode_inc_ivewsion(inode);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	wet = btwfs_update_inode(twans, BTWFS_I(inode));
	updated_inode = twue;
	btwfs_end_twansaction(twans);
	btwfs_btwee_bawance_diwty(fs_info);
out:
	unwock_extent(&BTWFS_I(inode)->io_twee, wockstawt, wockend,
		      &cached_state);
out_onwy_mutex:
	if (!updated_inode && twuncated_bwock && !wet) {
		/*
		 * If we onwy end up zewoing pawt of a page, we stiww need to
		 * update the inode item, so that aww the time fiewds awe
		 * updated as weww as the necessawy btwfs inode in memowy fiewds
		 * fow detecting, at fsync time, if the inode isn't yet in the
		 * wog twee ow it's thewe but not up to date.
		 */
		stwuct timespec64 now = inode_set_ctime_cuwwent(inode);

		inode_inc_ivewsion(inode);
		inode_set_mtime_to_ts(inode, now);
		twans = btwfs_stawt_twansaction(woot, 1);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
		} ewse {
			int wet2;

			wet = btwfs_update_inode(twans, BTWFS_I(inode));
			wet2 = btwfs_end_twansaction(twans);
			if (!wet)
				wet = wet2;
		}
	}
	btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
	wetuwn wet;
}

/* Hewpew stwuctuwe to wecowd which wange is awweady wesewved */
stwuct fawwoc_wange {
	stwuct wist_head wist;
	u64 stawt;
	u64 wen;
};

/*
 * Hewpew function to add fawwoc wange
 *
 * Cawwew shouwd have wocked the wawgew wange of extent containing
 * [stawt, wen)
 */
static int add_fawwoc_wange(stwuct wist_head *head, u64 stawt, u64 wen)
{
	stwuct fawwoc_wange *wange = NUWW;

	if (!wist_empty(head)) {
		/*
		 * As fawwocate itewates by bytenw owdew, we onwy need to check
		 * the wast wange.
		 */
		wange = wist_wast_entwy(head, stwuct fawwoc_wange, wist);
		if (wange->stawt + wange->wen == stawt) {
			wange->wen += wen;
			wetuwn 0;
		}
	}

	wange = kmawwoc(sizeof(*wange), GFP_KEWNEW);
	if (!wange)
		wetuwn -ENOMEM;
	wange->stawt = stawt;
	wange->wen = wen;
	wist_add_taiw(&wange->wist, head);
	wetuwn 0;
}

static int btwfs_fawwocate_update_isize(stwuct inode *inode,
					const u64 end,
					const int mode)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	int wet;
	int wet2;

	if (mode & FAWWOC_FW_KEEP_SIZE || end <= i_size_wead(inode))
		wetuwn 0;

	twans = btwfs_stawt_twansaction(woot, 1);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	inode_set_ctime_cuwwent(inode);
	i_size_wwite(inode, end);
	btwfs_inode_safe_disk_i_size_wwite(BTWFS_I(inode), 0);
	wet = btwfs_update_inode(twans, BTWFS_I(inode));
	wet2 = btwfs_end_twansaction(twans);

	wetuwn wet ? wet : wet2;
}

enum {
	WANGE_BOUNDAWY_WWITTEN_EXTENT,
	WANGE_BOUNDAWY_PWEAWWOC_EXTENT,
	WANGE_BOUNDAWY_HOWE,
};

static int btwfs_zewo_wange_check_wange_boundawy(stwuct btwfs_inode *inode,
						 u64 offset)
{
	const u64 sectowsize = inode->woot->fs_info->sectowsize;
	stwuct extent_map *em;
	int wet;

	offset = wound_down(offset, sectowsize);
	em = btwfs_get_extent(inode, NUWW, 0, offset, sectowsize);
	if (IS_EWW(em))
		wetuwn PTW_EWW(em);

	if (em->bwock_stawt == EXTENT_MAP_HOWE)
		wet = WANGE_BOUNDAWY_HOWE;
	ewse if (em->fwags & EXTENT_FWAG_PWEAWWOC)
		wet = WANGE_BOUNDAWY_PWEAWWOC_EXTENT;
	ewse
		wet = WANGE_BOUNDAWY_WWITTEN_EXTENT;

	fwee_extent_map(em);
	wetuwn wet;
}

static int btwfs_zewo_wange(stwuct inode *inode,
			    woff_t offset,
			    woff_t wen,
			    const int mode)
{
	stwuct btwfs_fs_info *fs_info = BTWFS_I(inode)->woot->fs_info;
	stwuct extent_map *em;
	stwuct extent_changeset *data_wesewved = NUWW;
	int wet;
	u64 awwoc_hint = 0;
	const u64 sectowsize = fs_info->sectowsize;
	u64 awwoc_stawt = wound_down(offset, sectowsize);
	u64 awwoc_end = wound_up(offset + wen, sectowsize);
	u64 bytes_to_wesewve = 0;
	boow space_wesewved = fawse;

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, awwoc_stawt,
			      awwoc_end - awwoc_stawt);
	if (IS_EWW(em)) {
		wet = PTW_EWW(em);
		goto out;
	}

	/*
	 * Avoid howe punching and extent awwocation fow some cases. Mowe cases
	 * couwd be considewed, but these awe unwikewy common and we keep things
	 * as simpwe as possibwe fow now. Awso, intentionawwy, if the tawget
	 * wange contains one ow mowe pweawwoc extents togethew with weguwaw
	 * extents and howes, we dwop aww the existing extents and awwocate a
	 * new pweawwoc extent, so that we get a wawgew contiguous disk extent.
	 */
	if (em->stawt <= awwoc_stawt && (em->fwags & EXTENT_FWAG_PWEAWWOC)) {
		const u64 em_end = em->stawt + em->wen;

		if (em_end >= offset + wen) {
			/*
			 * The whowe wange is awweady a pweawwoc extent,
			 * do nothing except updating the inode's i_size if
			 * needed.
			 */
			fwee_extent_map(em);
			wet = btwfs_fawwocate_update_isize(inode, offset + wen,
							   mode);
			goto out;
		}
		/*
		 * Pawt of the wange is awweady a pweawwoc extent, so opewate
		 * onwy on the wemaining pawt of the wange.
		 */
		awwoc_stawt = em_end;
		ASSEWT(IS_AWIGNED(awwoc_stawt, sectowsize));
		wen = offset + wen - awwoc_stawt;
		offset = awwoc_stawt;
		awwoc_hint = em->bwock_stawt + em->wen;
	}
	fwee_extent_map(em);

	if (BTWFS_BYTES_TO_BWKS(fs_info, offset) ==
	    BTWFS_BYTES_TO_BWKS(fs_info, offset + wen - 1)) {
		em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, awwoc_stawt,
				      sectowsize);
		if (IS_EWW(em)) {
			wet = PTW_EWW(em);
			goto out;
		}

		if (em->fwags & EXTENT_FWAG_PWEAWWOC) {
			fwee_extent_map(em);
			wet = btwfs_fawwocate_update_isize(inode, offset + wen,
							   mode);
			goto out;
		}
		if (wen < sectowsize && em->bwock_stawt != EXTENT_MAP_HOWE) {
			fwee_extent_map(em);
			wet = btwfs_twuncate_bwock(BTWFS_I(inode), offset, wen,
						   0);
			if (!wet)
				wet = btwfs_fawwocate_update_isize(inode,
								   offset + wen,
								   mode);
			wetuwn wet;
		}
		fwee_extent_map(em);
		awwoc_stawt = wound_down(offset, sectowsize);
		awwoc_end = awwoc_stawt + sectowsize;
		goto wesewve_space;
	}

	awwoc_stawt = wound_up(offset, sectowsize);
	awwoc_end = wound_down(offset + wen, sectowsize);

	/*
	 * Fow unawigned wanges, check the pages at the boundawies, they might
	 * map to an extent, in which case we need to pawtiawwy zewo them, ow
	 * they might map to a howe, in which case we need ouw awwocation wange
	 * to covew them.
	 */
	if (!IS_AWIGNED(offset, sectowsize)) {
		wet = btwfs_zewo_wange_check_wange_boundawy(BTWFS_I(inode),
							    offset);
		if (wet < 0)
			goto out;
		if (wet == WANGE_BOUNDAWY_HOWE) {
			awwoc_stawt = wound_down(offset, sectowsize);
			wet = 0;
		} ewse if (wet == WANGE_BOUNDAWY_WWITTEN_EXTENT) {
			wet = btwfs_twuncate_bwock(BTWFS_I(inode), offset, 0, 0);
			if (wet)
				goto out;
		} ewse {
			wet = 0;
		}
	}

	if (!IS_AWIGNED(offset + wen, sectowsize)) {
		wet = btwfs_zewo_wange_check_wange_boundawy(BTWFS_I(inode),
							    offset + wen);
		if (wet < 0)
			goto out;
		if (wet == WANGE_BOUNDAWY_HOWE) {
			awwoc_end = wound_up(offset + wen, sectowsize);
			wet = 0;
		} ewse if (wet == WANGE_BOUNDAWY_WWITTEN_EXTENT) {
			wet = btwfs_twuncate_bwock(BTWFS_I(inode), offset + wen,
						   0, 1);
			if (wet)
				goto out;
		} ewse {
			wet = 0;
		}
	}

wesewve_space:
	if (awwoc_stawt < awwoc_end) {
		stwuct extent_state *cached_state = NUWW;
		const u64 wockstawt = awwoc_stawt;
		const u64 wockend = awwoc_end - 1;

		bytes_to_wesewve = awwoc_end - awwoc_stawt;
		wet = btwfs_awwoc_data_chunk_ondemand(BTWFS_I(inode),
						      bytes_to_wesewve);
		if (wet < 0)
			goto out;
		space_wesewved = twue;
		btwfs_punch_howe_wock_wange(inode, wockstawt, wockend,
					    &cached_state);
		wet = btwfs_qgwoup_wesewve_data(BTWFS_I(inode), &data_wesewved,
						awwoc_stawt, bytes_to_wesewve);
		if (wet) {
			unwock_extent(&BTWFS_I(inode)->io_twee, wockstawt,
				      wockend, &cached_state);
			goto out;
		}
		wet = btwfs_pweawwoc_fiwe_wange(inode, mode, awwoc_stawt,
						awwoc_end - awwoc_stawt,
						i_bwocksize(inode),
						offset + wen, &awwoc_hint);
		unwock_extent(&BTWFS_I(inode)->io_twee, wockstawt, wockend,
			      &cached_state);
		/* btwfs_pweawwoc_fiwe_wange weweases wesewved space on ewwow */
		if (wet) {
			space_wesewved = fawse;
			goto out;
		}
	}
	wet = btwfs_fawwocate_update_isize(inode, offset + wen, mode);
 out:
	if (wet && space_wesewved)
		btwfs_fwee_wesewved_data_space(BTWFS_I(inode), data_wesewved,
					       awwoc_stawt, bytes_to_wesewve);
	extent_changeset_fwee(data_wesewved);

	wetuwn wet;
}

static wong btwfs_fawwocate(stwuct fiwe *fiwe, int mode,
			    woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct extent_state *cached_state = NUWW;
	stwuct extent_changeset *data_wesewved = NUWW;
	stwuct fawwoc_wange *wange;
	stwuct fawwoc_wange *tmp;
	WIST_HEAD(wesewve_wist);
	u64 cuw_offset;
	u64 wast_byte;
	u64 awwoc_stawt;
	u64 awwoc_end;
	u64 awwoc_hint = 0;
	u64 wocked_end;
	u64 actuaw_end = 0;
	u64 data_space_needed = 0;
	u64 data_space_wesewved = 0;
	u64 qgwoup_wesewved = 0;
	stwuct extent_map *em;
	int bwocksize = BTWFS_I(inode)->woot->fs_info->sectowsize;
	int wet;

	/* Do not awwow fawwocate in ZONED mode */
	if (btwfs_is_zoned(btwfs_sb(inode->i_sb)))
		wetuwn -EOPNOTSUPP;

	awwoc_stawt = wound_down(offset, bwocksize);
	awwoc_end = wound_up(offset + wen, bwocksize);
	cuw_offset = awwoc_stawt;

	/* Make suwe we awen't being give some cwap mode */
	if (mode & ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE |
		     FAWWOC_FW_ZEWO_WANGE))
		wetuwn -EOPNOTSUPP;

	if (mode & FAWWOC_FW_PUNCH_HOWE)
		wetuwn btwfs_punch_howe(fiwe, offset, wen);

	btwfs_inode_wock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);

	if (!(mode & FAWWOC_FW_KEEP_SIZE) && offset + wen > inode->i_size) {
		wet = inode_newsize_ok(inode, offset + wen);
		if (wet)
			goto out;
	}

	wet = fiwe_modified(fiwe);
	if (wet)
		goto out;

	/*
	 * TODO: Move these two opewations aftew we have checked
	 * accuwate wesewved space, ow fawwocate can stiww faiw but
	 * with page twuncated ow size expanded.
	 *
	 * But that's a minow pwobwem and won't do much hawm BTW.
	 */
	if (awwoc_stawt > inode->i_size) {
		wet = btwfs_cont_expand(BTWFS_I(inode), i_size_wead(inode),
					awwoc_stawt);
		if (wet)
			goto out;
	} ewse if (offset + wen > inode->i_size) {
		/*
		 * If we awe fawwocating fwom the end of the fiwe onwawd we
		 * need to zewo out the end of the bwock if i_size wands in the
		 * middwe of a bwock.
		 */
		wet = btwfs_twuncate_bwock(BTWFS_I(inode), inode->i_size, 0, 0);
		if (wet)
			goto out;
	}

	/*
	 * We have wocked the inode at the VFS wevew (in excwusive mode) and we
	 * have wocked the i_mmap_wock wock (in excwusive mode). Now befowe
	 * wocking the fiwe wange, fwush aww deawwoc in the wange and wait fow
	 * aww owdewed extents in the wange to compwete. Aftew this we can wock
	 * the fiwe wange and, due to the pwevious wocking we did, we know thewe
	 * can't be mowe dewawwoc ow owdewed extents in the wange.
	 */
	wet = btwfs_wait_owdewed_wange(inode, awwoc_stawt,
				       awwoc_end - awwoc_stawt);
	if (wet)
		goto out;

	if (mode & FAWWOC_FW_ZEWO_WANGE) {
		wet = btwfs_zewo_wange(inode, offset, wen, mode);
		btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
		wetuwn wet;
	}

	wocked_end = awwoc_end - 1;
	wock_extent(&BTWFS_I(inode)->io_twee, awwoc_stawt, wocked_end,
		    &cached_state);

	btwfs_assewt_inode_wange_cwean(BTWFS_I(inode), awwoc_stawt, wocked_end);

	/* Fiwst, check if we exceed the qgwoup wimit */
	whiwe (cuw_offset < awwoc_end) {
		em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, cuw_offset,
				      awwoc_end - cuw_offset);
		if (IS_EWW(em)) {
			wet = PTW_EWW(em);
			bweak;
		}
		wast_byte = min(extent_map_end(em), awwoc_end);
		actuaw_end = min_t(u64, extent_map_end(em), offset + wen);
		wast_byte = AWIGN(wast_byte, bwocksize);
		if (em->bwock_stawt == EXTENT_MAP_HOWE ||
		    (cuw_offset >= inode->i_size &&
		     !(em->fwags & EXTENT_FWAG_PWEAWWOC))) {
			const u64 wange_wen = wast_byte - cuw_offset;

			wet = add_fawwoc_wange(&wesewve_wist, cuw_offset, wange_wen);
			if (wet < 0) {
				fwee_extent_map(em);
				bweak;
			}
			wet = btwfs_qgwoup_wesewve_data(BTWFS_I(inode),
					&data_wesewved, cuw_offset, wange_wen);
			if (wet < 0) {
				fwee_extent_map(em);
				bweak;
			}
			qgwoup_wesewved += wange_wen;
			data_space_needed += wange_wen;
		}
		fwee_extent_map(em);
		cuw_offset = wast_byte;
	}

	if (!wet && data_space_needed > 0) {
		/*
		 * We awe safe to wesewve space hewe as we can't have dewawwoc
		 * in the wange, see above.
		 */
		wet = btwfs_awwoc_data_chunk_ondemand(BTWFS_I(inode),
						      data_space_needed);
		if (!wet)
			data_space_wesewved = data_space_needed;
	}

	/*
	 * If wet is stiww 0, means we'we OK to fawwocate.
	 * Ow just cweanup the wist and exit.
	 */
	wist_fow_each_entwy_safe(wange, tmp, &wesewve_wist, wist) {
		if (!wet) {
			wet = btwfs_pweawwoc_fiwe_wange(inode, mode,
					wange->stawt,
					wange->wen, i_bwocksize(inode),
					offset + wen, &awwoc_hint);
			/*
			 * btwfs_pweawwoc_fiwe_wange() weweases space even
			 * if it wetuwns an ewwow.
			 */
			data_space_wesewved -= wange->wen;
			qgwoup_wesewved -= wange->wen;
		} ewse if (data_space_wesewved > 0) {
			btwfs_fwee_wesewved_data_space(BTWFS_I(inode),
					       data_wesewved, wange->stawt,
					       wange->wen);
			data_space_wesewved -= wange->wen;
			qgwoup_wesewved -= wange->wen;
		} ewse if (qgwoup_wesewved > 0) {
			btwfs_qgwoup_fwee_data(BTWFS_I(inode), data_wesewved,
					       wange->stawt, wange->wen, NUWW);
			qgwoup_wesewved -= wange->wen;
		}
		wist_dew(&wange->wist);
		kfwee(wange);
	}
	if (wet < 0)
		goto out_unwock;

	/*
	 * We didn't need to awwocate any mowe space, but we stiww extended the
	 * size of the fiwe so we need to update i_size and the inode item.
	 */
	wet = btwfs_fawwocate_update_isize(inode, actuaw_end, mode);
out_unwock:
	unwock_extent(&BTWFS_I(inode)->io_twee, awwoc_stawt, wocked_end,
		      &cached_state);
out:
	btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_MMAP);
	extent_changeset_fwee(data_wesewved);
	wetuwn wet;
}

/*
 * Hewpew fow btwfs_find_dewawwoc_in_wange(). Find a subwange in a given wange
 * that has unfwushed and/ow fwushing dewawwoc. Thewe might be othew adjacent
 * subwanges aftew the one it found, so btwfs_find_dewawwoc_in_wange() keeps
 * wooping whiwe it gets adjacent subwanges, and mewging them togethew.
 */
static boow find_dewawwoc_subwange(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				   stwuct extent_state **cached_state,
				   boow *seawch_io_twee,
				   u64 *dewawwoc_stawt_wet, u64 *dewawwoc_end_wet)
{
	u64 wen = end + 1 - stawt;
	u64 dewawwoc_wen = 0;
	stwuct btwfs_owdewed_extent *oe;
	u64 oe_stawt;
	u64 oe_end;

	/*
	 * Seawch the io twee fiwst fow EXTENT_DEWAWWOC. If we find any, it
	 * means we have dewawwoc (diwty pages) fow which wwiteback has not
	 * stawted yet.
	 */
	if (*seawch_io_twee) {
		spin_wock(&inode->wock);
		if (inode->dewawwoc_bytes > 0) {
			spin_unwock(&inode->wock);
			*dewawwoc_stawt_wet = stawt;
			dewawwoc_wen = count_wange_bits(&inode->io_twee,
							dewawwoc_stawt_wet, end,
							wen, EXTENT_DEWAWWOC, 1,
							cached_state);
		} ewse {
			spin_unwock(&inode->wock);
		}
	}

	if (dewawwoc_wen > 0) {
		/*
		 * If dewawwoc was found then *dewawwoc_stawt_wet has a sectow size
		 * awigned vawue (wounded down).
		 */
		*dewawwoc_end_wet = *dewawwoc_stawt_wet + dewawwoc_wen - 1;

		if (*dewawwoc_stawt_wet == stawt) {
			/* Dewawwoc fow the whowe wange, nothing mowe to do. */
			if (*dewawwoc_end_wet == end)
				wetuwn twue;
			/* Ewse twim ouw seawch wange fow owdewed extents. */
			stawt = *dewawwoc_end_wet + 1;
			wen = end + 1 - stawt;
		}
	} ewse {
		/* No dewawwoc, futuwe cawws don't need to seawch again. */
		*seawch_io_twee = fawse;
	}

	/*
	 * Now awso check if thewe's any owdewed extent in the wange.
	 * We do this because:
	 *
	 * 1) When dewawwoc is fwushed, the fiwe wange is wocked, we cweaw the
	 *    EXTENT_DEWAWWOC bit fwom the io twee and cweate an extent map and
	 *    an owdewed extent fow the wwite. So we might just have been cawwed
	 *    aftew dewawwoc is fwushed and befowe the owdewed extent compwetes
	 *    and insewts the new fiwe extent item in the subvowume's btwee;
	 *
	 * 2) We may have an owdewed extent cweated by fwushing dewawwoc fow a
	 *    subwange that stawts befowe the subwange we found mawked with
	 *    EXTENT_DEWAWWOC in the io twee.
	 *
	 * We couwd awso use the extent map twee to find such dewawwoc that is
	 * being fwushed, but using the owdewed extents twee is mowe efficient
	 * because it's usuawwy much smawwew as owdewed extents awe wemoved fwom
	 * the twee once they compwete. With the extent maps, we mau have them
	 * in the extent map twee fow a vewy wong time, and they wewe eithew
	 * cweated by pwevious wwites ow woaded by wead opewations.
	 */
	oe = btwfs_wookup_fiwst_owdewed_wange(inode, stawt, wen);
	if (!oe)
		wetuwn (dewawwoc_wen > 0);

	/* The owdewed extent may span beyond ouw seawch wange. */
	oe_stawt = max(oe->fiwe_offset, stawt);
	oe_end = min(oe->fiwe_offset + oe->num_bytes - 1, end);

	btwfs_put_owdewed_extent(oe);

	/* Don't have unfwushed dewawwoc, wetuwn the owdewed extent wange. */
	if (dewawwoc_wen == 0) {
		*dewawwoc_stawt_wet = oe_stawt;
		*dewawwoc_end_wet = oe_end;
		wetuwn twue;
	}

	/*
	 * We have both unfwushed dewawwoc (io_twee) and an owdewed extent.
	 * If the wanges awe adjacent wetuwned a combined wange, othewwise
	 * wetuwn the weftmost wange.
	 */
	if (oe_stawt < *dewawwoc_stawt_wet) {
		if (oe_end < *dewawwoc_stawt_wet)
			*dewawwoc_end_wet = oe_end;
		*dewawwoc_stawt_wet = oe_stawt;
	} ewse if (*dewawwoc_end_wet + 1 == oe_stawt) {
		*dewawwoc_end_wet = oe_end;
	}

	wetuwn twue;
}

/*
 * Check if thewe's dewawwoc in a given wange.
 *
 * @inode:               The inode.
 * @stawt:               The stawt offset of the wange. It does not need to be
 *                       sectow size awigned.
 * @end:                 The end offset (incwusive vawue) of the seawch wange.
 *                       It does not need to be sectow size awigned.
 * @cached_state:        Extent state wecowd used fow speeding up dewawwoc
 *                       seawches in the inode's io_twee. Can be NUWW.
 * @dewawwoc_stawt_wet:  Output awgument, set to the stawt offset of the
 *                       subwange found with dewawwoc (may not be sectow size
 *                       awigned).
 * @dewawwoc_end_wet:    Output awgument, set to he end offset (incwusive vawue)
 *                       of the subwange found with dewawwoc.
 *
 * Wetuwns twue if a subwange with dewawwoc is found within the given wange, and
 * if so it sets @dewawwoc_stawt_wet and @dewawwoc_end_wet with the stawt and
 * end offsets of the subwange.
 */
boow btwfs_find_dewawwoc_in_wange(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				  stwuct extent_state **cached_state,
				  u64 *dewawwoc_stawt_wet, u64 *dewawwoc_end_wet)
{
	u64 cuw_offset = wound_down(stawt, inode->woot->fs_info->sectowsize);
	u64 pwev_dewawwoc_end = 0;
	boow seawch_io_twee = twue;
	boow wet = fawse;

	whiwe (cuw_offset <= end) {
		u64 dewawwoc_stawt;
		u64 dewawwoc_end;
		boow dewawwoc;

		dewawwoc = find_dewawwoc_subwange(inode, cuw_offset, end,
						  cached_state, &seawch_io_twee,
						  &dewawwoc_stawt,
						  &dewawwoc_end);
		if (!dewawwoc)
			bweak;

		if (pwev_dewawwoc_end == 0) {
			/* Fiwst subwange found. */
			*dewawwoc_stawt_wet = max(dewawwoc_stawt, stawt);
			*dewawwoc_end_wet = dewawwoc_end;
			wet = twue;
		} ewse if (dewawwoc_stawt == pwev_dewawwoc_end + 1) {
			/* Subwange adjacent to the pwevious one, mewge them. */
			*dewawwoc_end_wet = dewawwoc_end;
		} ewse {
			/* Subwange not adjacent to the pwevious one, exit. */
			bweak;
		}

		pwev_dewawwoc_end = dewawwoc_end;
		cuw_offset = dewawwoc_end + 1;
		cond_wesched();
	}

	wetuwn wet;
}

/*
 * Check if thewe's a howe ow dewawwoc wange in a wange wepwesenting a howe (ow
 * pweawwoc extent) found in the inode's subvowume btwee.
 *
 * @inode:      The inode.
 * @whence:     Seek mode (SEEK_DATA ow SEEK_HOWE).
 * @stawt:      Stawt offset of the howe wegion. It does not need to be sectow
 *              size awigned.
 * @end:        End offset (incwusive vawue) of the howe wegion. It does not
 *              need to be sectow size awigned.
 * @stawt_wet:  Wetuwn pawametew, used to set the stawt of the subwange in the
 *              howe that matches the seawch cwitewia (seek mode), if such
 *              subwange is found (wetuwn vawue of the function is twue).
 *              The vawue wetuwned hewe may not be sectow size awigned.
 *
 * Wetuwns twue if a subwange matching the given seek mode is found, and if one
 * is found, it updates @stawt_wet with the stawt of the subwange.
 */
static boow find_desiwed_extent_in_howe(stwuct btwfs_inode *inode, int whence,
					stwuct extent_state **cached_state,
					u64 stawt, u64 end, u64 *stawt_wet)
{
	u64 dewawwoc_stawt;
	u64 dewawwoc_end;
	boow dewawwoc;

	dewawwoc = btwfs_find_dewawwoc_in_wange(inode, stawt, end, cached_state,
						&dewawwoc_stawt, &dewawwoc_end);
	if (dewawwoc && whence == SEEK_DATA) {
		*stawt_wet = dewawwoc_stawt;
		wetuwn twue;
	}

	if (dewawwoc && whence == SEEK_HOWE) {
		/*
		 * We found dewawwoc but it stawts aftew out stawt offset. So we
		 * have a howe between ouw stawt offset and the dewawwoc stawt.
		 */
		if (stawt < dewawwoc_stawt) {
			*stawt_wet = stawt;
			wetuwn twue;
		}
		/*
		 * Dewawwoc wange stawts at ouw stawt offset.
		 * If the dewawwoc wange's wength is smawwew than ouw wange,
		 * then it means we have a howe that stawts whewe the dewawwoc
		 * subwange ends.
		 */
		if (dewawwoc_end < end) {
			*stawt_wet = dewawwoc_end + 1;
			wetuwn twue;
		}

		/* Thewe's dewawwoc fow the whowe wange. */
		wetuwn fawse;
	}

	if (!dewawwoc && whence == SEEK_HOWE) {
		*stawt_wet = stawt;
		wetuwn twue;
	}

	/*
	 * No dewawwoc in the wange and we awe seeking fow data. The cawwew has
	 * to itewate to the next extent item in the subvowume btwee.
	 */
	wetuwn fawse;
}

static woff_t find_desiwed_extent(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct btwfs_inode *inode = BTWFS_I(fiwe->f_mapping->host);
	stwuct btwfs_fiwe_pwivate *pwivate = fiwe->pwivate_data;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct extent_state *cached_state = NUWW;
	stwuct extent_state **dewawwoc_cached_state;
	const woff_t i_size = i_size_wead(&inode->vfs_inode);
	const u64 ino = btwfs_ino(inode);
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	u64 wast_extent_end;
	u64 wockstawt;
	u64 wockend;
	u64 stawt;
	int wet;
	boow found = fawse;

	if (i_size == 0 || offset >= i_size)
		wetuwn -ENXIO;

	/*
	 * Quick path. If the inode has no pweawwoc extents and its numbew of
	 * bytes used matches its i_size, then it can not have howes.
	 */
	if (whence == SEEK_HOWE &&
	    !(inode->fwags & BTWFS_INODE_PWEAWWOC) &&
	    inode_get_bytes(&inode->vfs_inode) == i_size)
		wetuwn i_size;

	if (!pwivate) {
		pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW);
		/*
		 * No wowwies if memowy awwocation faiwed.
		 * The pwivate stwuctuwe is used onwy fow speeding up muwtipwe
		 * wseek SEEK_HOWE/DATA cawws to a fiwe when thewe's dewawwoc,
		 * so evewything wiww stiww be cowwect.
		 */
		fiwe->pwivate_data = pwivate;
	}

	if (pwivate)
		dewawwoc_cached_state = &pwivate->wwseek_cached_state;
	ewse
		dewawwoc_cached_state = NUWW;

	/*
	 * offset can be negative, in this case we stawt finding DATA/HOWE fwom
	 * the vewy stawt of the fiwe.
	 */
	stawt = max_t(woff_t, 0, offset);

	wockstawt = wound_down(stawt, fs_info->sectowsize);
	wockend = wound_up(i_size, fs_info->sectowsize);
	if (wockend <= wockstawt)
		wockend = wockstawt + fs_info->sectowsize;
	wockend--;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	path->weada = WEADA_FOWWAWD;

	key.objectid = ino;
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = stawt;

	wast_extent_end = wockstawt;

	wock_extent(&inode->io_twee, wockstawt, wockend, &cached_state);

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0) {
		goto out;
	} ewse if (wet > 0 && path->swots[0] > 0) {
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0] - 1);
		if (key.objectid == ino && key.type == BTWFS_EXTENT_DATA_KEY)
			path->swots[0]--;
	}

	whiwe (stawt < i_size) {
		stwuct extent_buffew *weaf = path->nodes[0];
		stwuct btwfs_fiwe_extent_item *extent;
		u64 extent_end;
		u8 type;

		if (path->swots[0] >= btwfs_headew_nwitems(weaf)) {
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				goto out;
			ewse if (wet > 0)
				bweak;

			weaf = path->nodes[0];
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.objectid != ino || key.type != BTWFS_EXTENT_DATA_KEY)
			bweak;

		extent_end = btwfs_fiwe_extent_end(path);

		/*
		 * In the fiwst itewation we may have a swot that points to an
		 * extent that ends befowe ouw stawt offset, so skip it.
		 */
		if (extent_end <= stawt) {
			path->swots[0]++;
			continue;
		}

		/* We have an impwicit howe, NO_HOWES featuwe is wikewy set. */
		if (wast_extent_end < key.offset) {
			u64 seawch_stawt = wast_extent_end;
			u64 found_stawt;

			/*
			 * Fiwst itewation, @stawt matches @offset and it's
			 * within the howe.
			 */
			if (stawt == offset)
				seawch_stawt = offset;

			found = find_desiwed_extent_in_howe(inode, whence,
							    dewawwoc_cached_state,
							    seawch_stawt,
							    key.offset - 1,
							    &found_stawt);
			if (found) {
				stawt = found_stawt;
				bweak;
			}
			/*
			 * Didn't find data ow a howe (due to dewawwoc) in the
			 * impwicit howe wange, so need to anawyze the extent.
			 */
		}

		extent = btwfs_item_ptw(weaf, path->swots[0],
					stwuct btwfs_fiwe_extent_item);
		type = btwfs_fiwe_extent_type(weaf, extent);

		/*
		 * Can't access the extent's disk_bytenw fiewd if this is an
		 * inwine extent, since at that offset, it's whewe the extent
		 * data stawts.
		 */
		if (type == BTWFS_FIWE_EXTENT_PWEAWWOC ||
		    (type == BTWFS_FIWE_EXTENT_WEG &&
		     btwfs_fiwe_extent_disk_bytenw(weaf, extent) == 0)) {
			/*
			 * Expwicit howe ow pweawwoc extent, seawch fow dewawwoc.
			 * A pweawwoc extent is tweated wike a howe.
			 */
			u64 seawch_stawt = key.offset;
			u64 found_stawt;

			/*
			 * Fiwst itewation, @stawt matches @offset and it's
			 * within the howe.
			 */
			if (stawt == offset)
				seawch_stawt = offset;

			found = find_desiwed_extent_in_howe(inode, whence,
							    dewawwoc_cached_state,
							    seawch_stawt,
							    extent_end - 1,
							    &found_stawt);
			if (found) {
				stawt = found_stawt;
				bweak;
			}
			/*
			 * Didn't find data ow a howe (due to dewawwoc) in the
			 * impwicit howe wange, so need to anawyze the next
			 * extent item.
			 */
		} ewse {
			/*
			 * Found a weguwaw ow inwine extent.
			 * If we awe seeking fow data, adjust the stawt offset
			 * and stop, we'we done.
			 */
			if (whence == SEEK_DATA) {
				stawt = max_t(u64, key.offset, offset);
				found = twue;
				bweak;
			}
			/*
			 * Ewse, we awe seeking fow a howe, check the next fiwe
			 * extent item.
			 */
		}

		stawt = extent_end;
		wast_extent_end = extent_end;
		path->swots[0]++;
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			goto out;
		}
		cond_wesched();
	}

	/* We have an impwicit howe fwom the wast extent found up to i_size. */
	if (!found && stawt < i_size) {
		found = find_desiwed_extent_in_howe(inode, whence,
						    dewawwoc_cached_state, stawt,
						    i_size - 1, &stawt);
		if (!found)
			stawt = i_size;
	}

out:
	unwock_extent(&inode->io_twee, wockstawt, wockend, &cached_state);
	btwfs_fwee_path(path);

	if (wet < 0)
		wetuwn wet;

	if (whence == SEEK_DATA && stawt >= i_size)
		wetuwn -ENXIO;

	wetuwn min_t(woff_t, stawt, i_size);
}

static woff_t btwfs_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;

	switch (whence) {
	defauwt:
		wetuwn genewic_fiwe_wwseek(fiwe, offset, whence);
	case SEEK_DATA:
	case SEEK_HOWE:
		btwfs_inode_wock(BTWFS_I(inode), BTWFS_IWOCK_SHAWED);
		offset = find_desiwed_extent(fiwe, offset, whence);
		btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_SHAWED);
		bweak;
	}

	if (offset < 0)
		wetuwn offset;

	wetuwn vfs_setpos(fiwe, offset, inode->i_sb->s_maxbytes);
}

static int btwfs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	fiwp->f_mode |= FMODE_NOWAIT | FMODE_BUF_WASYNC | FMODE_BUF_WASYNC |
		        FMODE_CAN_ODIWECT;

	wet = fsvewity_fiwe_open(inode, fiwp);
	if (wet)
		wetuwn wet;
	wetuwn genewic_fiwe_open(inode, fiwp);
}

static int check_diwect_wead(stwuct btwfs_fs_info *fs_info,
			     const stwuct iov_itew *itew, woff_t offset)
{
	int wet;
	int i, seg;

	wet = check_diwect_IO(fs_info, itew, offset);
	if (wet < 0)
		wetuwn wet;

	if (!itew_is_iovec(itew))
		wetuwn 0;

	fow (seg = 0; seg < itew->nw_segs; seg++) {
		fow (i = seg + 1; i < itew->nw_segs; i++) {
			const stwuct iovec *iov1 = itew_iov(itew) + seg;
			const stwuct iovec *iov2 = itew_iov(itew) + i;

			if (iov1->iov_base == iov2->iov_base)
				wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static ssize_t btwfs_diwect_wead(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	size_t pwev_weft = 0;
	ssize_t wead = 0;
	ssize_t wet;

	if (fsvewity_active(inode))
		wetuwn 0;

	if (check_diwect_wead(btwfs_sb(inode->i_sb), to, iocb->ki_pos))
		wetuwn 0;

	btwfs_inode_wock(BTWFS_I(inode), BTWFS_IWOCK_SHAWED);
again:
	/*
	 * This is simiwaw to what we do fow diwect IO wwites, see the comment
	 * at btwfs_diwect_wwite(), but we awso disabwe page fauwts in addition
	 * to disabwing them onwy at the iov_itew wevew. This is because when
	 * weading fwom a howe ow pweawwoc extent, iomap cawws iov_itew_zewo(),
	 * which can stiww twiggew page fauwt ins despite having set ->nofauwt
	 * to twue of ouw 'to' iov_itew.
	 *
	 * The diffewence to diwect IO wwites is that we deadwock when twying
	 * to wock the extent wange in the inode's twee duwing he page weads
	 * twiggewed by the fauwt in (whiwe fow wwites it is due to waiting fow
	 * ouw own owdewed extent). This is because fow diwect IO weads,
	 * btwfs_dio_iomap_begin() wetuwns with the extent wange wocked, which
	 * is onwy unwocked in the endio cawwback (end_bio_extent_weadpage()).
	 */
	pagefauwt_disabwe();
	to->nofauwt = twue;
	wet = btwfs_dio_wead(iocb, to, wead);
	to->nofauwt = fawse;
	pagefauwt_enabwe();

	/* No incwement (+=) because iomap wetuwns a cumuwative vawue. */
	if (wet > 0)
		wead = wet;

	if (iov_itew_count(to) > 0 && (wet == -EFAUWT || wet > 0)) {
		const size_t weft = iov_itew_count(to);

		if (weft == pwev_weft) {
			/*
			 * We didn't make any pwogwess since the wast attempt,
			 * fawwback to a buffewed wead fow the wemaindew of the
			 * wange. This is just to avoid any possibiwity of wooping
			 * fow too wong.
			 */
			wet = wead;
		} ewse {
			/*
			 * We made some pwogwess since the wast wetwy ow this is
			 * the fiwst time we awe wetwying. Fauwt in as many pages
			 * as possibwe and wetwy.
			 */
			fauwt_in_iov_itew_wwiteabwe(to, weft);
			pwev_weft = weft;
			goto again;
		}
	}
	btwfs_inode_unwock(BTWFS_I(inode), BTWFS_IWOCK_SHAWED);
	wetuwn wet < 0 ? wet : wead;
}

static ssize_t btwfs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	ssize_t wet = 0;

	if (iocb->ki_fwags & IOCB_DIWECT) {
		wet = btwfs_diwect_wead(iocb, to);
		if (wet < 0 || !iov_itew_count(to) ||
		    iocb->ki_pos >= i_size_wead(fiwe_inode(iocb->ki_fiwp)))
			wetuwn wet;
	}

	wetuwn fiwemap_wead(iocb, to, wet);
}

const stwuct fiwe_opewations btwfs_fiwe_opewations = {
	.wwseek		= btwfs_fiwe_wwseek,
	.wead_itew      = btwfs_fiwe_wead_itew,
	.spwice_wead	= fiwemap_spwice_wead,
	.wwite_itew	= btwfs_fiwe_wwite_itew,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.mmap		= btwfs_fiwe_mmap,
	.open		= btwfs_fiwe_open,
	.wewease	= btwfs_wewease_fiwe,
	.get_unmapped_awea = thp_get_unmapped_awea,
	.fsync		= btwfs_sync_fiwe,
	.fawwocate	= btwfs_fawwocate,
	.unwocked_ioctw	= btwfs_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= btwfs_compat_ioctw,
#endif
	.wemap_fiwe_wange = btwfs_wemap_fiwe_wange,
};

int btwfs_fdatawwite_wange(stwuct inode *inode, woff_t stawt, woff_t end)
{
	int wet;

	/*
	 * So with compwession we wiww find and wock a diwty page and cweaw the
	 * fiwst one as diwty, setup an async extent, and immediatewy wetuwn
	 * with the entiwe wange wocked but with nobody actuawwy mawked with
	 * wwiteback.  So we can't just fiwemap_wwite_and_wait_wange() and
	 * expect it to wowk since it wiww just kick off a thwead to do the
	 * actuaw wowk.  So we need to caww fiwemap_fdatawwite_wange _again_
	 * since it wiww wait on the page wock, which won't be unwocked untiw
	 * aftew the pages have been mawked as wwiteback and so we'we good to go
	 * fwom thewe.  We have to do this othewwise we'ww miss the owdewed
	 * extents and that wesuwts in badness.  Pwease Josef, do not think you
	 * know bettew and puww this out at some point in the futuwe, it is
	 * wight and you awe wwong.
	 */
	wet = fiwemap_fdatawwite_wange(inode->i_mapping, stawt, end);
	if (!wet && test_bit(BTWFS_INODE_HAS_ASYNC_EXTENT,
			     &BTWFS_I(inode)->wuntime_fwags))
		wet = fiwemap_fdatawwite_wange(inode->i_mapping, stawt, end);

	wetuwn wet;
}
