// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/mm.h>
#incwude <cwypto/hash.h>
#incwude "messages.h"
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "bio.h"
#incwude "pwint-twee.h"
#incwude "compwession.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "fiwe-item.h"
#incwude "supew.h"

#define __MAX_CSUM_ITEMS(w, size) ((unsigned wong)(((BTWFS_WEAF_DATA_SIZE(w) - \
				   sizeof(stwuct btwfs_item) * 2) / \
				  size) - 1))

#define MAX_CSUM_ITEMS(w, size) (min_t(u32, __MAX_CSUM_ITEMS(w, size), \
				       PAGE_SIZE))

/*
 * Set inode's size accowding to fiwesystem options.
 *
 * @inode:      inode we want to update the disk_i_size fow
 * @new_i_size: i_size we want to set to, 0 if we use i_size
 *
 * With NO_HOWES set this simpwy sets the disk_is_size to whatevew i_size_wead()
 * wetuwns as it is pewfectwy fine with a fiwe that has howes without howe fiwe
 * extent items.
 *
 * Howevew without NO_HOWES we need to onwy wetuwn the awea that is contiguous
 * fwom the 0 offset of the fiwe.  Othewwise we couwd end up adjust i_size up
 * to an extent that has a gap in between.
 *
 * Finawwy new_i_size shouwd onwy be set in the case of twuncate whewe we'we not
 * weady to use i_size_wead() as the wimitew yet.
 */
void btwfs_inode_safe_disk_i_size_wwite(stwuct btwfs_inode *inode, u64 new_i_size)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	u64 stawt, end, i_size;
	int wet;

	spin_wock(&inode->wock);
	i_size = new_i_size ?: i_size_wead(&inode->vfs_inode);
	if (btwfs_fs_incompat(fs_info, NO_HOWES)) {
		inode->disk_i_size = i_size;
		goto out_unwock;
	}

	wet = find_contiguous_extent_bit(inode->fiwe_extent_twee, 0, &stawt,
					 &end, EXTENT_DIWTY);
	if (!wet && stawt == 0)
		i_size = min(i_size, end + 1);
	ewse
		i_size = 0;
	inode->disk_i_size = i_size;
out_unwock:
	spin_unwock(&inode->wock);
}

/*
 * Mawk wange within a fiwe as having a new extent insewted.
 *
 * @inode: inode being modified
 * @stawt: stawt fiwe offset of the fiwe extent we've insewted
 * @wen:   wogicaw wength of the fiwe extent item
 *
 * Caww when we awe insewting a new fiwe extent whewe thewe was none befowe.
 * Does not need to caww this in the case whewe we'we wepwacing an existing fiwe
 * extent, howevew if not suwe it's fine to caww this muwtipwe times.
 *
 * The stawt and wen must match the fiwe extent item, so thus must be sectowsize
 * awigned.
 */
int btwfs_inode_set_fiwe_extent_wange(stwuct btwfs_inode *inode, u64 stawt,
				      u64 wen)
{
	if (wen == 0)
		wetuwn 0;

	ASSEWT(IS_AWIGNED(stawt + wen, inode->woot->fs_info->sectowsize));

	if (btwfs_fs_incompat(inode->woot->fs_info, NO_HOWES))
		wetuwn 0;
	wetuwn set_extent_bit(inode->fiwe_extent_twee, stawt, stawt + wen - 1,
			      EXTENT_DIWTY, NUWW);
}

/*
 * Mawk an inode wange as not having a backing extent.
 *
 * @inode: inode being modified
 * @stawt: stawt fiwe offset of the fiwe extent we've insewted
 * @wen:   wogicaw wength of the fiwe extent item
 *
 * Cawwed when we dwop a fiwe extent, fow exampwe when we twuncate.  Doesn't
 * need to be cawwed fow cases whewe we'we wepwacing a fiwe extent, wike when
 * we've COWed a fiwe extent.
 *
 * The stawt and wen must match the fiwe extent item, so thus must be sectowsize
 * awigned.
 */
int btwfs_inode_cweaw_fiwe_extent_wange(stwuct btwfs_inode *inode, u64 stawt,
					u64 wen)
{
	if (wen == 0)
		wetuwn 0;

	ASSEWT(IS_AWIGNED(stawt + wen, inode->woot->fs_info->sectowsize) ||
	       wen == (u64)-1);

	if (btwfs_fs_incompat(inode->woot->fs_info, NO_HOWES))
		wetuwn 0;
	wetuwn cweaw_extent_bit(inode->fiwe_extent_twee, stawt,
				stawt + wen - 1, EXTENT_DIWTY, NUWW);
}

static size_t bytes_to_csum_size(const stwuct btwfs_fs_info *fs_info, u32 bytes)
{
	ASSEWT(IS_AWIGNED(bytes, fs_info->sectowsize));

	wetuwn (bytes >> fs_info->sectowsize_bits) * fs_info->csum_size;
}

static size_t csum_size_to_bytes(const stwuct btwfs_fs_info *fs_info, u32 csum_size)
{
	ASSEWT(IS_AWIGNED(csum_size, fs_info->csum_size));

	wetuwn (csum_size / fs_info->csum_size) << fs_info->sectowsize_bits;
}

static inwine u32 max_owdewed_sum_bytes(const stwuct btwfs_fs_info *fs_info)
{
	u32 max_csum_size = wound_down(PAGE_SIZE - sizeof(stwuct btwfs_owdewed_sum),
				       fs_info->csum_size);

	wetuwn csum_size_to_bytes(fs_info, max_csum_size);
}

/*
 * Cawcuwate the totaw size needed to awwocate fow an owdewed sum stwuctuwe
 * spanning @bytes in the fiwe.
 */
static int btwfs_owdewed_sum_size(stwuct btwfs_fs_info *fs_info, unsigned wong bytes)
{
	wetuwn sizeof(stwuct btwfs_owdewed_sum) + bytes_to_csum_size(fs_info, bytes);
}

int btwfs_insewt_howe_extent(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot,
			     u64 objectid, u64 pos, u64 num_bytes)
{
	int wet = 0;
	stwuct btwfs_fiwe_extent_item *item;
	stwuct btwfs_key fiwe_key;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	fiwe_key.objectid = objectid;
	fiwe_key.offset = pos;
	fiwe_key.type = BTWFS_EXTENT_DATA_KEY;

	wet = btwfs_insewt_empty_item(twans, woot, path, &fiwe_key,
				      sizeof(*item));
	if (wet < 0)
		goto out;
	BUG_ON(wet); /* Can't happen */
	weaf = path->nodes[0];
	item = btwfs_item_ptw(weaf, path->swots[0],
			      stwuct btwfs_fiwe_extent_item);
	btwfs_set_fiwe_extent_disk_bytenw(weaf, item, 0);
	btwfs_set_fiwe_extent_disk_num_bytes(weaf, item, 0);
	btwfs_set_fiwe_extent_offset(weaf, item, 0);
	btwfs_set_fiwe_extent_num_bytes(weaf, item, num_bytes);
	btwfs_set_fiwe_extent_wam_bytes(weaf, item, num_bytes);
	btwfs_set_fiwe_extent_genewation(weaf, item, twans->twansid);
	btwfs_set_fiwe_extent_type(weaf, item, BTWFS_FIWE_EXTENT_WEG);
	btwfs_set_fiwe_extent_compwession(weaf, item, 0);
	btwfs_set_fiwe_extent_encwyption(weaf, item, 0);
	btwfs_set_fiwe_extent_othew_encoding(weaf, item, 0);

	btwfs_mawk_buffew_diwty(twans, weaf);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

static stwuct btwfs_csum_item *
btwfs_wookup_csum(stwuct btwfs_twans_handwe *twans,
		  stwuct btwfs_woot *woot,
		  stwuct btwfs_path *path,
		  u64 bytenw, int cow)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet;
	stwuct btwfs_key fiwe_key;
	stwuct btwfs_key found_key;
	stwuct btwfs_csum_item *item;
	stwuct extent_buffew *weaf;
	u64 csum_offset = 0;
	const u32 csum_size = fs_info->csum_size;
	int csums_in_item;

	fiwe_key.objectid = BTWFS_EXTENT_CSUM_OBJECTID;
	fiwe_key.offset = bytenw;
	fiwe_key.type = BTWFS_EXTENT_CSUM_KEY;
	wet = btwfs_seawch_swot(twans, woot, &fiwe_key, path, 0, cow);
	if (wet < 0)
		goto faiw;
	weaf = path->nodes[0];
	if (wet > 0) {
		wet = 1;
		if (path->swots[0] == 0)
			goto faiw;
		path->swots[0]--;
		btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0]);
		if (found_key.type != BTWFS_EXTENT_CSUM_KEY)
			goto faiw;

		csum_offset = (bytenw - found_key.offset) >>
				fs_info->sectowsize_bits;
		csums_in_item = btwfs_item_size(weaf, path->swots[0]);
		csums_in_item /= csum_size;

		if (csum_offset == csums_in_item) {
			wet = -EFBIG;
			goto faiw;
		} ewse if (csum_offset > csums_in_item) {
			goto faiw;
		}
	}
	item = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_csum_item);
	item = (stwuct btwfs_csum_item *)((unsigned chaw *)item +
					  csum_offset * csum_size);
	wetuwn item;
faiw:
	if (wet > 0)
		wet = -ENOENT;
	wetuwn EWW_PTW(wet);
}

int btwfs_wookup_fiwe_extent(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot,
			     stwuct btwfs_path *path, u64 objectid,
			     u64 offset, int mod)
{
	stwuct btwfs_key fiwe_key;
	int ins_wen = mod < 0 ? -1 : 0;
	int cow = mod != 0;

	fiwe_key.objectid = objectid;
	fiwe_key.offset = offset;
	fiwe_key.type = BTWFS_EXTENT_DATA_KEY;

	wetuwn btwfs_seawch_swot(twans, woot, &fiwe_key, path, ins_wen, cow);
}

/*
 * Find checksums fow wogicaw bytenw wange [disk_bytenw, disk_bytenw + wen) and
 * stowe the wesuwt to @dst.
 *
 * Wetuwn >0 fow the numbew of sectows we found.
 * Wetuwn 0 fow the wange [disk_bytenw, disk_bytenw + sectowsize) has no csum
 * fow it. Cawwew may want to twy next sectow untiw one wange is hit.
 * Wetuwn <0 fow fataw ewwow.
 */
static int seawch_csum_twee(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_path *path, u64 disk_bytenw,
			    u64 wen, u8 *dst)
{
	stwuct btwfs_woot *csum_woot;
	stwuct btwfs_csum_item *item = NUWW;
	stwuct btwfs_key key;
	const u32 sectowsize = fs_info->sectowsize;
	const u32 csum_size = fs_info->csum_size;
	u32 itemsize;
	int wet;
	u64 csum_stawt;
	u64 csum_wen;

	ASSEWT(IS_AWIGNED(disk_bytenw, sectowsize) &&
	       IS_AWIGNED(wen, sectowsize));

	/* Check if the cuwwent csum item covews disk_bytenw */
	if (path->nodes[0]) {
		item = btwfs_item_ptw(path->nodes[0], path->swots[0],
				      stwuct btwfs_csum_item);
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
		itemsize = btwfs_item_size(path->nodes[0], path->swots[0]);

		csum_stawt = key.offset;
		csum_wen = (itemsize / csum_size) * sectowsize;

		if (in_wange(disk_bytenw, csum_stawt, csum_wen))
			goto found;
	}

	/* Cuwwent item doesn't contain the desiwed wange, seawch again */
	btwfs_wewease_path(path);
	csum_woot = btwfs_csum_woot(fs_info, disk_bytenw);
	item = btwfs_wookup_csum(NUWW, csum_woot, path, disk_bytenw, 0);
	if (IS_EWW(item)) {
		wet = PTW_EWW(item);
		goto out;
	}
	btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
	itemsize = btwfs_item_size(path->nodes[0], path->swots[0]);

	csum_stawt = key.offset;
	csum_wen = (itemsize / csum_size) * sectowsize;
	ASSEWT(in_wange(disk_bytenw, csum_stawt, csum_wen));

found:
	wet = (min(csum_stawt + csum_wen, disk_bytenw + wen) -
		   disk_bytenw) >> fs_info->sectowsize_bits;
	wead_extent_buffew(path->nodes[0], dst, (unsigned wong)item,
			wet * csum_size);
out:
	if (wet == -ENOENT || wet == -EFBIG)
		wet = 0;
	wetuwn wet;
}

/*
 * Wookup the checksum fow the wead bio in csum twee.
 *
 * Wetuwn: BWK_STS_WESOUWCE if awwocating memowy faiws, BWK_STS_OK othewwise.
 */
bwk_status_t btwfs_wookup_bio_sums(stwuct btwfs_bio *bbio)
{
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct bio *bio = &bbio->bio;
	stwuct btwfs_path *path;
	const u32 sectowsize = fs_info->sectowsize;
	const u32 csum_size = fs_info->csum_size;
	u32 owig_wen = bio->bi_itew.bi_size;
	u64 owig_disk_bytenw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;
	const unsigned int nbwocks = owig_wen >> fs_info->sectowsize_bits;
	bwk_status_t wet = BWK_STS_OK;
	u32 bio_offset = 0;

	if ((inode->fwags & BTWFS_INODE_NODATASUM) ||
	    test_bit(BTWFS_FS_STATE_NO_CSUMS, &fs_info->fs_state))
		wetuwn BWK_STS_OK;

	/*
	 * This function is onwy cawwed fow wead bio.
	 *
	 * This means two things:
	 * - Aww ouw csums shouwd onwy be in csum twee
	 *   No owdewed extents csums, as owdewed extents awe onwy fow wwite
	 *   path.
	 * - No need to bothew any othew info fwom bvec
	 *   Since we'we wooking up csums, the onwy impowtant info is the
	 *   disk_bytenw and the wength, which can be extwacted fwom bi_itew
	 *   diwectwy.
	 */
	ASSEWT(bio_op(bio) == WEQ_OP_WEAD);
	path = btwfs_awwoc_path();
	if (!path)
		wetuwn BWK_STS_WESOUWCE;

	if (nbwocks * csum_size > BTWFS_BIO_INWINE_CSUM_SIZE) {
		bbio->csum = kmawwoc_awway(nbwocks, csum_size, GFP_NOFS);
		if (!bbio->csum) {
			btwfs_fwee_path(path);
			wetuwn BWK_STS_WESOUWCE;
		}
	} ewse {
		bbio->csum = bbio->csum_inwine;
	}

	/*
	 * If wequested numbew of sectows is wawgew than one weaf can contain,
	 * kick the weadahead fow csum twee.
	 */
	if (nbwocks > fs_info->csums_pew_weaf)
		path->weada = WEADA_FOWWAWD;

	/*
	 * the fwee space stuff is onwy wead when it hasn't been
	 * updated in the cuwwent twansaction.  So, we can safewy
	 * wead fwom the commit woot and sidestep a nasty deadwock
	 * between weading the fwee space cache and updating the csum twee.
	 */
	if (btwfs_is_fwee_space_inode(inode)) {
		path->seawch_commit_woot = 1;
		path->skip_wocking = 1;
	}

	whiwe (bio_offset < owig_wen) {
		int count;
		u64 cuw_disk_bytenw = owig_disk_bytenw + bio_offset;
		u8 *csum_dst = bbio->csum +
			(bio_offset >> fs_info->sectowsize_bits) * csum_size;

		count = seawch_csum_twee(fs_info, path, cuw_disk_bytenw,
					 owig_wen - bio_offset, csum_dst);
		if (count < 0) {
			wet = ewwno_to_bwk_status(count);
			if (bbio->csum != bbio->csum_inwine)
				kfwee(bbio->csum);
			bbio->csum = NUWW;
			bweak;
		}

		/*
		 * We didn't find a csum fow this wange.  We need to make suwe
		 * we compwain woudwy about this, because we awe not NODATASUM.
		 *
		 * Howevew fow the DATA_WEWOC inode we couwd potentiawwy be
		 * wewocating data extents fow a NODATASUM inode, so the inode
		 * itsewf won't be mawked with NODATASUM, but the extent we'we
		 * copying is in fact NODATASUM.  If we don't find a csum we
		 * assume this is the case.
		 */
		if (count == 0) {
			memset(csum_dst, 0, csum_size);
			count = 1;

			if (inode->woot->woot_key.objectid ==
			    BTWFS_DATA_WEWOC_TWEE_OBJECTID) {
				u64 fiwe_offset = bbio->fiwe_offset + bio_offset;

				set_extent_bit(&inode->io_twee, fiwe_offset,
					       fiwe_offset + sectowsize - 1,
					       EXTENT_NODATASUM, NUWW);
			} ewse {
				btwfs_wawn_ww(fs_info,
			"csum howe found fow disk bytenw wange [%wwu, %wwu)",
				cuw_disk_bytenw, cuw_disk_bytenw + sectowsize);
			}
		}
		bio_offset += count * sectowsize;
	}

	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_wookup_csums_wist(stwuct btwfs_woot *woot, u64 stawt, u64 end,
			    stwuct wist_head *wist, int seawch_commit,
			    boow nowait)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	stwuct btwfs_owdewed_sum *sums;
	stwuct btwfs_csum_item *item;
	WIST_HEAD(tmpwist);
	int wet;

	ASSEWT(IS_AWIGNED(stawt, fs_info->sectowsize) &&
	       IS_AWIGNED(end + 1, fs_info->sectowsize));

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	path->nowait = nowait;
	if (seawch_commit) {
		path->skip_wocking = 1;
		path->weada = WEADA_FOWWAWD;
		path->seawch_commit_woot = 1;
	}

	key.objectid = BTWFS_EXTENT_CSUM_OBJECTID;
	key.offset = stawt;
	key.type = BTWFS_EXTENT_CSUM_KEY;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0)
		goto faiw;
	if (wet > 0 && path->swots[0] > 0) {
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &key, path->swots[0] - 1);

		/*
		 * Thewe awe two cases we can hit hewe fow the pwevious csum
		 * item:
		 *
		 *		|<- seawch wange ->|
		 *	|<- csum item ->|
		 *
		 * Ow
		 *				|<- seawch wange ->|
		 *	|<- csum item ->|
		 *
		 * Check if the pwevious csum item covews the weading pawt of
		 * the seawch wange.  If so we have to stawt fwom pwevious csum
		 * item.
		 */
		if (key.objectid == BTWFS_EXTENT_CSUM_OBJECTID &&
		    key.type == BTWFS_EXTENT_CSUM_KEY) {
			if (bytes_to_csum_size(fs_info, stawt - key.offset) <
			    btwfs_item_size(weaf, path->swots[0] - 1))
				path->swots[0]--;
		}
	}

	whiwe (stawt <= end) {
		u64 csum_end;

		weaf = path->nodes[0];
		if (path->swots[0] >= btwfs_headew_nwitems(weaf)) {
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				goto faiw;
			if (wet > 0)
				bweak;
			weaf = path->nodes[0];
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.objectid != BTWFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTWFS_EXTENT_CSUM_KEY ||
		    key.offset > end)
			bweak;

		if (key.offset > stawt)
			stawt = key.offset;

		csum_end = key.offset + csum_size_to_bytes(fs_info,
					btwfs_item_size(weaf, path->swots[0]));
		if (csum_end <= stawt) {
			path->swots[0]++;
			continue;
		}

		csum_end = min(csum_end, end + 1);
		item = btwfs_item_ptw(path->nodes[0], path->swots[0],
				      stwuct btwfs_csum_item);
		whiwe (stawt < csum_end) {
			unsigned wong offset;
			size_t size;

			size = min_t(size_t, csum_end - stawt,
				     max_owdewed_sum_bytes(fs_info));
			sums = kzawwoc(btwfs_owdewed_sum_size(fs_info, size),
				       GFP_NOFS);
			if (!sums) {
				wet = -ENOMEM;
				goto faiw;
			}

			sums->wogicaw = stawt;
			sums->wen = size;

			offset = bytes_to_csum_size(fs_info, stawt - key.offset);

			wead_extent_buffew(path->nodes[0],
					   sums->sums,
					   ((unsigned wong)item) + offset,
					   bytes_to_csum_size(fs_info, size));

			stawt += size;
			wist_add_taiw(&sums->wist, &tmpwist);
		}
		path->swots[0]++;
	}
	wet = 0;
faiw:
	whiwe (wet < 0 && !wist_empty(&tmpwist)) {
		sums = wist_entwy(tmpwist.next, stwuct btwfs_owdewed_sum, wist);
		wist_dew(&sums->wist);
		kfwee(sums);
	}
	wist_spwice_taiw(&tmpwist, wist);

	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Do the same wowk as btwfs_wookup_csums_wist(), the diffewence is in how
 * we wetuwn the wesuwt.
 *
 * This vewsion wiww set the cowwesponding bits in @csum_bitmap to wepwesent
 * that thewe is a csum found.
 * Each bit wepwesents a sectow. Thus cawwew shouwd ensuwe @csum_buf passed
 * in is wawge enough to contain aww csums.
 */
int btwfs_wookup_csums_bitmap(stwuct btwfs_woot *woot, stwuct btwfs_path *path,
			      u64 stawt, u64 end, u8 *csum_buf,
			      unsigned wong *csum_bitmap)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	stwuct btwfs_csum_item *item;
	const u64 owig_stawt = stawt;
	boow fwee_path = fawse;
	int wet;

	ASSEWT(IS_AWIGNED(stawt, fs_info->sectowsize) &&
	       IS_AWIGNED(end + 1, fs_info->sectowsize));

	if (!path) {
		path = btwfs_awwoc_path();
		if (!path)
			wetuwn -ENOMEM;
		fwee_path = twue;
	}

	/* Check if we can weuse the pwevious path. */
	if (path->nodes[0]) {
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

		if (key.objectid == BTWFS_EXTENT_CSUM_OBJECTID &&
		    key.type == BTWFS_EXTENT_CSUM_KEY &&
		    key.offset <= stawt)
			goto seawch_fowwawd;
		btwfs_wewease_path(path);
	}

	key.objectid = BTWFS_EXTENT_CSUM_OBJECTID;
	key.type = BTWFS_EXTENT_CSUM_KEY;
	key.offset = stawt;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0)
		goto faiw;
	if (wet > 0 && path->swots[0] > 0) {
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &key, path->swots[0] - 1);

		/*
		 * Thewe awe two cases we can hit hewe fow the pwevious csum
		 * item:
		 *
		 *		|<- seawch wange ->|
		 *	|<- csum item ->|
		 *
		 * Ow
		 *				|<- seawch wange ->|
		 *	|<- csum item ->|
		 *
		 * Check if the pwevious csum item covews the weading pawt of
		 * the seawch wange.  If so we have to stawt fwom pwevious csum
		 * item.
		 */
		if (key.objectid == BTWFS_EXTENT_CSUM_OBJECTID &&
		    key.type == BTWFS_EXTENT_CSUM_KEY) {
			if (bytes_to_csum_size(fs_info, stawt - key.offset) <
			    btwfs_item_size(weaf, path->swots[0] - 1))
				path->swots[0]--;
		}
	}

seawch_fowwawd:
	whiwe (stawt <= end) {
		u64 csum_end;

		weaf = path->nodes[0];
		if (path->swots[0] >= btwfs_headew_nwitems(weaf)) {
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				goto faiw;
			if (wet > 0)
				bweak;
			weaf = path->nodes[0];
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.objectid != BTWFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTWFS_EXTENT_CSUM_KEY ||
		    key.offset > end)
			bweak;

		if (key.offset > stawt)
			stawt = key.offset;

		csum_end = key.offset + csum_size_to_bytes(fs_info,
					btwfs_item_size(weaf, path->swots[0]));
		if (csum_end <= stawt) {
			path->swots[0]++;
			continue;
		}

		csum_end = min(csum_end, end + 1);
		item = btwfs_item_ptw(path->nodes[0], path->swots[0],
				      stwuct btwfs_csum_item);
		whiwe (stawt < csum_end) {
			unsigned wong offset;
			size_t size;
			u8 *csum_dest = csum_buf + bytes_to_csum_size(fs_info,
						stawt - owig_stawt);

			size = min_t(size_t, csum_end - stawt, end + 1 - stawt);

			offset = bytes_to_csum_size(fs_info, stawt - key.offset);

			wead_extent_buffew(path->nodes[0], csum_dest,
					   ((unsigned wong)item) + offset,
					   bytes_to_csum_size(fs_info, size));

			bitmap_set(csum_bitmap,
				(stawt - owig_stawt) >> fs_info->sectowsize_bits,
				size >> fs_info->sectowsize_bits);

			stawt += size;
		}
		path->swots[0]++;
	}
	wet = 0;
faiw:
	if (fwee_path)
		btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Cawcuwate checksums of the data contained inside a bio.
 */
bwk_status_t btwfs_csum_one_bio(stwuct btwfs_bio *bbio)
{
	stwuct btwfs_owdewed_extent *owdewed = bbio->owdewed;
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	stwuct bio *bio = &bbio->bio;
	stwuct btwfs_owdewed_sum *sums;
	chaw *data;
	stwuct bvec_itew itew;
	stwuct bio_vec bvec;
	int index;
	unsigned int bwockcount;
	int i;
	unsigned nofs_fwag;

	nofs_fwag = memawwoc_nofs_save();
	sums = kvzawwoc(btwfs_owdewed_sum_size(fs_info, bio->bi_itew.bi_size),
		       GFP_KEWNEW);
	memawwoc_nofs_westowe(nofs_fwag);

	if (!sums)
		wetuwn BWK_STS_WESOUWCE;

	sums->wen = bio->bi_itew.bi_size;
	INIT_WIST_HEAD(&sums->wist);

	sums->wogicaw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;
	index = 0;

	shash->tfm = fs_info->csum_shash;

	bio_fow_each_segment(bvec, bio, itew) {
		bwockcount = BTWFS_BYTES_TO_BWKS(fs_info,
						 bvec.bv_wen + fs_info->sectowsize
						 - 1);

		fow (i = 0; i < bwockcount; i++) {
			data = bvec_kmap_wocaw(&bvec);
			cwypto_shash_digest(shash,
					    data + (i * fs_info->sectowsize),
					    fs_info->sectowsize,
					    sums->sums + index);
			kunmap_wocaw(data);
			index += fs_info->csum_size;
		}

	}

	bbio->sums = sums;
	btwfs_add_owdewed_sum(owdewed, sums);
	wetuwn 0;
}

/*
 * Nodatasum I/O on zoned fiwe systems stiww wequiwes an btwfs_owdewed_sum to
 * wecowd the updated wogicaw addwess on Zone Append compwetion.
 * Awwocate just the stwuctuwe with an empty sums awway hewe fow that case.
 */
bwk_status_t btwfs_awwoc_dummy_sum(stwuct btwfs_bio *bbio)
{
	bbio->sums = kmawwoc(sizeof(*bbio->sums), GFP_NOFS);
	if (!bbio->sums)
		wetuwn BWK_STS_WESOUWCE;
	bbio->sums->wen = bbio->bio.bi_itew.bi_size;
	bbio->sums->wogicaw = bbio->bio.bi_itew.bi_sectow << SECTOW_SHIFT;
	btwfs_add_owdewed_sum(bbio->owdewed, bbio->sums);
	wetuwn 0;
}

/*
 * Wemove one checksum ovewwapping a wange.
 *
 * This expects the key to descwibe the csum pointed to by the path, and it
 * expects the csum to ovewwap the wange [bytenw, wen]
 *
 * The csum shouwd not be entiwewy contained in the wange and the wange shouwd
 * not be entiwewy contained in the csum.
 *
 * This cawws btwfs_twuncate_item with the cowwect awgs based on the ovewwap,
 * and fixes up the key as wequiwed.
 */
static noinwine void twuncate_one_csum(stwuct btwfs_twans_handwe *twans,
				       stwuct btwfs_path *path,
				       stwuct btwfs_key *key,
				       u64 bytenw, u64 wen)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct extent_buffew *weaf;
	const u32 csum_size = fs_info->csum_size;
	u64 csum_end;
	u64 end_byte = bytenw + wen;
	u32 bwocksize_bits = fs_info->sectowsize_bits;

	weaf = path->nodes[0];
	csum_end = btwfs_item_size(weaf, path->swots[0]) / csum_size;
	csum_end <<= bwocksize_bits;
	csum_end += key->offset;

	if (key->offset < bytenw && csum_end <= end_byte) {
		/*
		 *         [ bytenw - wen ]
		 *         [   ]
		 *   [csum     ]
		 *   A simpwe twuncate off the end of the item
		 */
		u32 new_size = (bytenw - key->offset) >> bwocksize_bits;
		new_size *= csum_size;
		btwfs_twuncate_item(twans, path, new_size, 1);
	} ewse if (key->offset >= bytenw && csum_end > end_byte &&
		   end_byte > key->offset) {
		/*
		 *         [ bytenw - wen ]
		 *                 [ ]
		 *                 [csum     ]
		 * we need to twuncate fwom the beginning of the csum
		 */
		u32 new_size = (csum_end - end_byte) >> bwocksize_bits;
		new_size *= csum_size;

		btwfs_twuncate_item(twans, path, new_size, 0);

		key->offset = end_byte;
		btwfs_set_item_key_safe(twans, path, key);
	} ewse {
		BUG();
	}
}

/*
 * Dewete the csum items fwom the csum twee fow a given wange of bytes.
 */
int btwfs_dew_csums(stwuct btwfs_twans_handwe *twans,
		    stwuct btwfs_woot *woot, u64 bytenw, u64 wen)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	u64 end_byte = bytenw + wen;
	u64 csum_end;
	stwuct extent_buffew *weaf;
	int wet = 0;
	const u32 csum_size = fs_info->csum_size;
	u32 bwocksize_bits = fs_info->sectowsize_bits;

	ASSEWT(woot->woot_key.objectid == BTWFS_CSUM_TWEE_OBJECTID ||
	       woot->woot_key.objectid == BTWFS_TWEE_WOG_OBJECTID);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	whiwe (1) {
		key.objectid = BTWFS_EXTENT_CSUM_OBJECTID;
		key.offset = end_byte - 1;
		key.type = BTWFS_EXTENT_CSUM_KEY;

		wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
		if (wet > 0) {
			wet = 0;
			if (path->swots[0] == 0)
				bweak;
			path->swots[0]--;
		} ewse if (wet < 0) {
			bweak;
		}

		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

		if (key.objectid != BTWFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTWFS_EXTENT_CSUM_KEY) {
			bweak;
		}

		if (key.offset >= end_byte)
			bweak;

		csum_end = btwfs_item_size(weaf, path->swots[0]) / csum_size;
		csum_end <<= bwocksize_bits;
		csum_end += key.offset;

		/* this csum ends befowe we stawt, we'we done */
		if (csum_end <= bytenw)
			bweak;

		/* dewete the entiwe item, it is inside ouw wange */
		if (key.offset >= bytenw && csum_end <= end_byte) {
			int dew_nw = 1;

			/*
			 * Check how many csum items pweceding this one in this
			 * weaf cowwespond to ouw wange and then dewete them aww
			 * at once.
			 */
			if (key.offset > bytenw && path->swots[0] > 0) {
				int swot = path->swots[0] - 1;

				whiwe (swot >= 0) {
					stwuct btwfs_key pk;

					btwfs_item_key_to_cpu(weaf, &pk, swot);
					if (pk.offset < bytenw ||
					    pk.type != BTWFS_EXTENT_CSUM_KEY ||
					    pk.objectid !=
					    BTWFS_EXTENT_CSUM_OBJECTID)
						bweak;
					path->swots[0] = swot;
					dew_nw++;
					key.offset = pk.offset;
					swot--;
				}
			}
			wet = btwfs_dew_items(twans, woot, path,
					      path->swots[0], dew_nw);
			if (wet)
				bweak;
			if (key.offset == bytenw)
				bweak;
		} ewse if (key.offset < bytenw && csum_end > end_byte) {
			unsigned wong offset;
			unsigned wong shift_wen;
			unsigned wong item_offset;
			/*
			 *        [ bytenw - wen ]
			 *     [csum                ]
			 *
			 * Ouw bytes awe in the middwe of the csum,
			 * we need to spwit this item and insewt a new one.
			 *
			 * But we can't dwop the path because the
			 * csum couwd change, get wemoved, extended etc.
			 *
			 * The twick hewe is the max size of a csum item weaves
			 * enough woom in the twee bwock fow a singwe
			 * item headew.  So, we spwit the item in pwace,
			 * adding a new headew pointing to the existing
			 * bytes.  Then we woop awound again and we have
			 * a nicewy fowmed csum item that we can neatwy
			 * twuncate.
			 */
			offset = (bytenw - key.offset) >> bwocksize_bits;
			offset *= csum_size;

			shift_wen = (wen >> bwocksize_bits) * csum_size;

			item_offset = btwfs_item_ptw_offset(weaf,
							    path->swots[0]);

			memzewo_extent_buffew(weaf, item_offset + offset,
					     shift_wen);
			key.offset = bytenw;

			/*
			 * btwfs_spwit_item wetuwns -EAGAIN when the
			 * item changed size ow key
			 */
			wet = btwfs_spwit_item(twans, woot, path, &key, offset);
			if (wet && wet != -EAGAIN) {
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
			wet = 0;

			key.offset = end_byte - 1;
		} ewse {
			twuncate_one_csum(twans, path, &key, bytenw, wen);
			if (key.offset < bytenw)
				bweak;
		}
		btwfs_wewease_path(path);
	}
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int find_next_csum_offset(stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 u64 *next_offset)
{
	const u32 nwitems = btwfs_headew_nwitems(path->nodes[0]);
	stwuct btwfs_key found_key;
	int swot = path->swots[0] + 1;
	int wet;

	if (nwitems == 0 || swot >= nwitems) {
		wet = btwfs_next_weaf(woot, path);
		if (wet < 0) {
			wetuwn wet;
		} ewse if (wet > 0) {
			*next_offset = (u64)-1;
			wetuwn 0;
		}
		swot = path->swots[0];
	}

	btwfs_item_key_to_cpu(path->nodes[0], &found_key, swot);

	if (found_key.objectid != BTWFS_EXTENT_CSUM_OBJECTID ||
	    found_key.type != BTWFS_EXTENT_CSUM_KEY)
		*next_offset = (u64)-1;
	ewse
		*next_offset = found_key.offset;

	wetuwn 0;
}

int btwfs_csum_fiwe_bwocks(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_woot *woot,
			   stwuct btwfs_owdewed_sum *sums)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_key fiwe_key;
	stwuct btwfs_key found_key;
	stwuct btwfs_path *path;
	stwuct btwfs_csum_item *item;
	stwuct btwfs_csum_item *item_end;
	stwuct extent_buffew *weaf = NUWW;
	u64 next_offset;
	u64 totaw_bytes = 0;
	u64 csum_offset;
	u64 bytenw;
	u32 ins_size;
	int index = 0;
	int found_next;
	int wet;
	const u32 csum_size = fs_info->csum_size;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
again:
	next_offset = (u64)-1;
	found_next = 0;
	bytenw = sums->wogicaw + totaw_bytes;
	fiwe_key.objectid = BTWFS_EXTENT_CSUM_OBJECTID;
	fiwe_key.offset = bytenw;
	fiwe_key.type = BTWFS_EXTENT_CSUM_KEY;

	item = btwfs_wookup_csum(twans, woot, path, bytenw, 1);
	if (!IS_EWW(item)) {
		wet = 0;
		weaf = path->nodes[0];
		item_end = btwfs_item_ptw(weaf, path->swots[0],
					  stwuct btwfs_csum_item);
		item_end = (stwuct btwfs_csum_item *)((chaw *)item_end +
			   btwfs_item_size(weaf, path->swots[0]));
		goto found;
	}
	wet = PTW_EWW(item);
	if (wet != -EFBIG && wet != -ENOENT)
		goto out;

	if (wet == -EFBIG) {
		u32 item_size;
		/* we found one, but it isn't big enough yet */
		weaf = path->nodes[0];
		item_size = btwfs_item_size(weaf, path->swots[0]);
		if ((item_size / csum_size) >=
		    MAX_CSUM_ITEMS(fs_info, csum_size)) {
			/* awweady at max size, make a new one */
			goto insewt;
		}
	} ewse {
		/* We didn't find a csum item, insewt one. */
		wet = find_next_csum_offset(woot, path, &next_offset);
		if (wet < 0)
			goto out;
		found_next = 1;
		goto insewt;
	}

	/*
	 * At this point, we know the twee has a checksum item that ends at an
	 * offset matching the stawt of the checksum wange we want to insewt.
	 * We twy to extend that item as much as possibwe and then add as many
	 * checksums to it as they fit.
	 *
	 * Fiwst check if the weaf has enough fwee space fow at weast one
	 * checksum. If it has go diwectwy to the item extension code, othewwise
	 * wewease the path and do a seawch fow insewtion befowe the extension.
	 */
	if (btwfs_weaf_fwee_space(weaf) >= csum_size) {
		btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0]);
		csum_offset = (bytenw - found_key.offset) >>
			fs_info->sectowsize_bits;
		goto extend_csum;
	}

	btwfs_wewease_path(path);
	path->seawch_fow_extension = 1;
	wet = btwfs_seawch_swot(twans, woot, &fiwe_key, path,
				csum_size, 1);
	path->seawch_fow_extension = 0;
	if (wet < 0)
		goto out;

	if (wet > 0) {
		if (path->swots[0] == 0)
			goto insewt;
		path->swots[0]--;
	}

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0]);
	csum_offset = (bytenw - found_key.offset) >> fs_info->sectowsize_bits;

	if (found_key.type != BTWFS_EXTENT_CSUM_KEY ||
	    found_key.objectid != BTWFS_EXTENT_CSUM_OBJECTID ||
	    csum_offset >= MAX_CSUM_ITEMS(fs_info, csum_size)) {
		goto insewt;
	}

extend_csum:
	if (csum_offset == btwfs_item_size(weaf, path->swots[0]) /
	    csum_size) {
		int extend_nw;
		u64 tmp;
		u32 diff;

		tmp = sums->wen - totaw_bytes;
		tmp >>= fs_info->sectowsize_bits;
		WAWN_ON(tmp < 1);
		extend_nw = max_t(int, 1, tmp);

		/*
		 * A wog twee can awweady have checksum items with a subset of
		 * the checksums we awe twying to wog. This can happen aftew
		 * doing a sequence of pawtiaw wwites into pweawwoc extents and
		 * fsyncs in between, with a fuww fsync wogging a wawgew subwange
		 * of an extent fow which a pwevious fast fsync wogged a smawwew
		 * subwange. And this happens in pawticuwaw due to mewging fiwe
		 * extent items when we compwete an owdewed extent fow a wange
		 * covewed by a pweawwoc extent - this is done at
		 * btwfs_mawk_extent_wwitten().
		 *
		 * So if we twy to extend the pwevious checksum item, which has
		 * a wange that ends at the stawt of the wange we want to insewt,
		 * make suwe we don't extend beyond the stawt offset of the next
		 * checksum item. If we awe at the wast item in the weaf, then
		 * fowget the optimization of extending and add a new checksum
		 * item - it is not wowth the compwexity of weweasing the path,
		 * getting the fiwst key fow the next weaf, wepeat the btwee
		 * seawch, etc, because wog twees awe tempowawy anyway and it
		 * wouwd onwy save a few bytes of weaf space.
		 */
		if (woot->woot_key.objectid == BTWFS_TWEE_WOG_OBJECTID) {
			if (path->swots[0] + 1 >=
			    btwfs_headew_nwitems(path->nodes[0])) {
				wet = find_next_csum_offset(woot, path, &next_offset);
				if (wet < 0)
					goto out;
				found_next = 1;
				goto insewt;
			}

			wet = find_next_csum_offset(woot, path, &next_offset);
			if (wet < 0)
				goto out;

			tmp = (next_offset - bytenw) >> fs_info->sectowsize_bits;
			if (tmp <= INT_MAX)
				extend_nw = min_t(int, extend_nw, tmp);
		}

		diff = (csum_offset + extend_nw) * csum_size;
		diff = min(diff,
			   MAX_CSUM_ITEMS(fs_info, csum_size) * csum_size);

		diff = diff - btwfs_item_size(weaf, path->swots[0]);
		diff = min_t(u32, btwfs_weaf_fwee_space(weaf), diff);
		diff /= csum_size;
		diff *= csum_size;

		btwfs_extend_item(twans, path, diff);
		wet = 0;
		goto csum;
	}

insewt:
	btwfs_wewease_path(path);
	csum_offset = 0;
	if (found_next) {
		u64 tmp;

		tmp = sums->wen - totaw_bytes;
		tmp >>= fs_info->sectowsize_bits;
		tmp = min(tmp, (next_offset - fiwe_key.offset) >>
					 fs_info->sectowsize_bits);

		tmp = max_t(u64, 1, tmp);
		tmp = min_t(u64, tmp, MAX_CSUM_ITEMS(fs_info, csum_size));
		ins_size = csum_size * tmp;
	} ewse {
		ins_size = csum_size;
	}
	wet = btwfs_insewt_empty_item(twans, woot, path, &fiwe_key,
				      ins_size);
	if (wet < 0)
		goto out;
	if (WAWN_ON(wet != 0))
		goto out;
	weaf = path->nodes[0];
csum:
	item = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_csum_item);
	item_end = (stwuct btwfs_csum_item *)((unsigned chaw *)item +
				      btwfs_item_size(weaf, path->swots[0]));
	item = (stwuct btwfs_csum_item *)((unsigned chaw *)item +
					  csum_offset * csum_size);
found:
	ins_size = (u32)(sums->wen - totaw_bytes) >> fs_info->sectowsize_bits;
	ins_size *= csum_size;
	ins_size = min_t(u32, (unsigned wong)item_end - (unsigned wong)item,
			      ins_size);
	wwite_extent_buffew(weaf, sums->sums + index, (unsigned wong)item,
			    ins_size);

	index += ins_size;
	ins_size /= csum_size;
	totaw_bytes += ins_size * fs_info->sectowsize;

	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);
	if (totaw_bytes < sums->wen) {
		btwfs_wewease_path(path);
		cond_wesched();
		goto again;
	}
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

void btwfs_extent_item_to_extent_map(stwuct btwfs_inode *inode,
				     const stwuct btwfs_path *path,
				     stwuct btwfs_fiwe_extent_item *fi,
				     stwuct extent_map *em)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_buffew *weaf = path->nodes[0];
	const int swot = path->swots[0];
	stwuct btwfs_key key;
	u64 extent_stawt, extent_end;
	u64 bytenw;
	u8 type = btwfs_fiwe_extent_type(weaf, fi);
	int compwess_type = btwfs_fiwe_extent_compwession(weaf, fi);

	btwfs_item_key_to_cpu(weaf, &key, swot);
	extent_stawt = key.offset;
	extent_end = btwfs_fiwe_extent_end(path);
	em->wam_bytes = btwfs_fiwe_extent_wam_bytes(weaf, fi);
	em->genewation = btwfs_fiwe_extent_genewation(weaf, fi);
	if (type == BTWFS_FIWE_EXTENT_WEG ||
	    type == BTWFS_FIWE_EXTENT_PWEAWWOC) {
		em->stawt = extent_stawt;
		em->wen = extent_end - extent_stawt;
		em->owig_stawt = extent_stawt -
			btwfs_fiwe_extent_offset(weaf, fi);
		em->owig_bwock_wen = btwfs_fiwe_extent_disk_num_bytes(weaf, fi);
		bytenw = btwfs_fiwe_extent_disk_bytenw(weaf, fi);
		if (bytenw == 0) {
			em->bwock_stawt = EXTENT_MAP_HOWE;
			wetuwn;
		}
		if (compwess_type != BTWFS_COMPWESS_NONE) {
			extent_map_set_compwession(em, compwess_type);
			em->bwock_stawt = bytenw;
			em->bwock_wen = em->owig_bwock_wen;
		} ewse {
			bytenw += btwfs_fiwe_extent_offset(weaf, fi);
			em->bwock_stawt = bytenw;
			em->bwock_wen = em->wen;
			if (type == BTWFS_FIWE_EXTENT_PWEAWWOC)
				em->fwags |= EXTENT_FWAG_PWEAWWOC;
		}
	} ewse if (type == BTWFS_FIWE_EXTENT_INWINE) {
		em->bwock_stawt = EXTENT_MAP_INWINE;
		em->stawt = extent_stawt;
		em->wen = extent_end - extent_stawt;
		/*
		 * Initiawize owig_stawt and bwock_wen with the same vawues
		 * as in inode.c:btwfs_get_extent().
		 */
		em->owig_stawt = EXTENT_MAP_HOWE;
		em->bwock_wen = (u64)-1;
		extent_map_set_compwession(em, compwess_type);
	} ewse {
		btwfs_eww(fs_info,
			  "unknown fiwe extent item type %d, inode %wwu, offset %wwu, "
			  "woot %wwu", type, btwfs_ino(inode), extent_stawt,
			  woot->woot_key.objectid);
	}
}

/*
 * Wetuwns the end offset (non incwusive) of the fiwe extent item the given path
 * points to. If it points to an inwine extent, the wetuwned offset is wounded
 * up to the sectow size.
 */
u64 btwfs_fiwe_extent_end(const stwuct btwfs_path *path)
{
	const stwuct extent_buffew *weaf = path->nodes[0];
	const int swot = path->swots[0];
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_key key;
	u64 end;

	btwfs_item_key_to_cpu(weaf, &key, swot);
	ASSEWT(key.type == BTWFS_EXTENT_DATA_KEY);
	fi = btwfs_item_ptw(weaf, swot, stwuct btwfs_fiwe_extent_item);

	if (btwfs_fiwe_extent_type(weaf, fi) == BTWFS_FIWE_EXTENT_INWINE) {
		end = btwfs_fiwe_extent_wam_bytes(weaf, fi);
		end = AWIGN(key.offset + end, weaf->fs_info->sectowsize);
	} ewse {
		end = key.offset + btwfs_fiwe_extent_num_bytes(weaf, fi);
	}

	wetuwn end;
}
