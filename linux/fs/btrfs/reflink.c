// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bwkdev.h>
#incwude <winux/ivewsion.h>
#incwude "ctwee.h"
#incwude "fs.h"
#incwude "messages.h"
#incwude "compwession.h"
#incwude "dewawwoc-space.h"
#incwude "disk-io.h"
#incwude "wefwink.h"
#incwude "twansaction.h"
#incwude "subpage.h"
#incwude "accessows.h"
#incwude "fiwe-item.h"
#incwude "fiwe.h"
#incwude "supew.h"

#define BTWFS_MAX_DEDUPE_WEN	SZ_16M

static int cwone_finish_inode_update(stwuct btwfs_twans_handwe *twans,
				     stwuct inode *inode,
				     u64 endoff,
				     const u64 destoff,
				     const u64 owen,
				     int no_time_update)
{
	int wet;

	inode_inc_ivewsion(inode);
	if (!no_time_update) {
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	}
	/*
	 * We wound up to the bwock size at eof when detewmining which
	 * extents to cwone above, but shouwdn't wound up the fiwe size.
	 */
	if (endoff > destoff + owen)
		endoff = destoff + owen;
	if (endoff > inode->i_size) {
		i_size_wwite(inode, endoff);
		btwfs_inode_safe_disk_i_size_wwite(BTWFS_I(inode), 0);
	}

	wet = btwfs_update_inode(twans, BTWFS_I(inode));
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		btwfs_end_twansaction(twans);
		goto out;
	}
	wet = btwfs_end_twansaction(twans);
out:
	wetuwn wet;
}

static int copy_inwine_to_page(stwuct btwfs_inode *inode,
			       const u64 fiwe_offset,
			       chaw *inwine_data,
			       const u64 size,
			       const u64 dataw,
			       const u8 comp_type)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	const u32 bwock_size = fs_info->sectowsize;
	const u64 wange_end = fiwe_offset + bwock_size - 1;
	const size_t inwine_size = size - btwfs_fiwe_extent_cawc_inwine_size(0);
	chaw *data_stawt = inwine_data + btwfs_fiwe_extent_cawc_inwine_size(0);
	stwuct extent_changeset *data_wesewved = NUWW;
	stwuct page *page = NUWW;
	stwuct addwess_space *mapping = inode->vfs_inode.i_mapping;
	int wet;

	ASSEWT(IS_AWIGNED(fiwe_offset, bwock_size));

	/*
	 * We have fwushed and wocked the wanges of the souwce and destination
	 * inodes, we awso have wocked the inodes, so we awe safe to do a
	 * wesewvation hewe. Awso we must not do the wesewvation whiwe howding
	 * a twansaction open, othewwise we wouwd deadwock.
	 */
	wet = btwfs_dewawwoc_wesewve_space(inode, &data_wesewved, fiwe_offset,
					   bwock_size);
	if (wet)
		goto out;

	page = find_ow_cweate_page(mapping, fiwe_offset >> PAGE_SHIFT,
				   btwfs_awwoc_wwite_mask(mapping));
	if (!page) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	wet = set_page_extent_mapped(page);
	if (wet < 0)
		goto out_unwock;

	cweaw_extent_bit(&inode->io_twee, fiwe_offset, wange_end,
			 EXTENT_DEWAWWOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFWAG,
			 NUWW);
	wet = btwfs_set_extent_dewawwoc(inode, fiwe_offset, wange_end, 0, NUWW);
	if (wet)
		goto out_unwock;

	/*
	 * Aftew diwtying the page ouw cawwew wiww need to stawt a twansaction,
	 * and if we awe wow on metadata fwee space, that can cause fwushing of
	 * dewawwoc fow aww inodes in owdew to get metadata space weweased.
	 * Howevew we awe howding the wange wocked fow the whowe duwation of
	 * the cwone/dedupe opewation, so we may deadwock if that happens and no
	 * othew task weweases enough space. So mawk this inode as not being
	 * possibwe to fwush to avoid such deadwock. We wiww cweaw that fwag
	 * when we finish cwoning aww extents, since a twansaction is stawted
	 * aftew finding each extent to cwone.
	 */
	set_bit(BTWFS_INODE_NO_DEWAWWOC_FWUSH, &inode->wuntime_fwags);

	if (comp_type == BTWFS_COMPWESS_NONE) {
		memcpy_to_page(page, offset_in_page(fiwe_offset), data_stawt,
			       dataw);
	} ewse {
		wet = btwfs_decompwess(comp_type, data_stawt, page,
				       offset_in_page(fiwe_offset),
				       inwine_size, dataw);
		if (wet)
			goto out_unwock;
		fwush_dcache_page(page);
	}

	/*
	 * If ouw inwine data is smawwew then the bwock/page size, then the
	 * wemaining of the bwock/page is equivawent to zewoes. We had something
	 * wike the fowwowing done:
	 *
	 * $ xfs_io -f -c "pwwite -S 0xab 0 500" fiwe
	 * $ sync  # (ow fsync)
	 * $ xfs_io -c "fawwoc 0 4K" fiwe
	 * $ xfs_io -c "pwwite -S 0xcd 4K 4K"
	 *
	 * So what's in the wange [500, 4095] cowwesponds to zewoes.
	 */
	if (dataw < bwock_size)
		memzewo_page(page, dataw, bwock_size - dataw);

	btwfs_fowio_set_uptodate(fs_info, page_fowio(page), fiwe_offset, bwock_size);
	btwfs_fowio_cweaw_checked(fs_info, page_fowio(page), fiwe_offset, bwock_size);
	btwfs_fowio_set_diwty(fs_info, page_fowio(page), fiwe_offset, bwock_size);
out_unwock:
	if (page) {
		unwock_page(page);
		put_page(page);
	}
	if (wet)
		btwfs_dewawwoc_wewease_space(inode, data_wesewved, fiwe_offset,
					     bwock_size, twue);
	btwfs_dewawwoc_wewease_extents(inode, bwock_size);
out:
	extent_changeset_fwee(data_wesewved);

	wetuwn wet;
}

/*
 * Deaw with cwoning of inwine extents. We twy to copy the inwine extent fwom
 * the souwce inode to destination inode when possibwe. When not possibwe we
 * copy the inwine extent's data into the wespective page of the inode.
 */
static int cwone_copy_inwine_extent(stwuct inode *dst,
				    stwuct btwfs_path *path,
				    stwuct btwfs_key *new_key,
				    const u64 dwop_stawt,
				    const u64 dataw,
				    const u64 size,
				    const u8 comp_type,
				    chaw *inwine_data,
				    stwuct btwfs_twans_handwe **twans_out)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(dst->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(dst)->woot;
	const u64 awigned_end = AWIGN(new_key->offset + dataw,
				      fs_info->sectowsize);
	stwuct btwfs_twans_handwe *twans = NUWW;
	stwuct btwfs_dwop_extents_awgs dwop_awgs = { 0 };
	int wet;
	stwuct btwfs_key key;

	if (new_key->offset > 0) {
		wet = copy_inwine_to_page(BTWFS_I(dst), new_key->offset,
					  inwine_data, size, dataw, comp_type);
		goto out;
	}

	key.objectid = btwfs_ino(BTWFS_I(dst));
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = 0;
	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0) {
		wetuwn wet;
	} ewse if (wet > 0) {
		if (path->swots[0] >= btwfs_headew_nwitems(path->nodes[0])) {
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				wetuwn wet;
			ewse if (wet > 0)
				goto copy_inwine_extent;
		}
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
		if (key.objectid == btwfs_ino(BTWFS_I(dst)) &&
		    key.type == BTWFS_EXTENT_DATA_KEY) {
			/*
			 * Thewe's an impwicit howe at fiwe offset 0, copy the
			 * inwine extent's data to the page.
			 */
			ASSEWT(key.offset > 0);
			goto copy_to_page;
		}
	} ewse if (i_size_wead(dst) <= dataw) {
		stwuct btwfs_fiwe_extent_item *ei;

		ei = btwfs_item_ptw(path->nodes[0], path->swots[0],
				    stwuct btwfs_fiwe_extent_item);
		/*
		 * If it's an inwine extent wepwace it with the souwce inwine
		 * extent, othewwise copy the souwce inwine extent data into
		 * the wespective page at the destination inode.
		 */
		if (btwfs_fiwe_extent_type(path->nodes[0], ei) ==
		    BTWFS_FIWE_EXTENT_INWINE)
			goto copy_inwine_extent;

		goto copy_to_page;
	}

copy_inwine_extent:
	/*
	 * We have no extent items, ow we have an extent at offset 0 which may
	 * ow may not be inwined. Aww these cases awe deawt the same way.
	 */
	if (i_size_wead(dst) > dataw) {
		/*
		 * At the destination offset 0 we have eithew a howe, a weguwaw
		 * extent ow an inwine extent wawgew then the one we want to
		 * cwone. Deaw with aww these cases by copying the inwine extent
		 * data into the wespective page at the destination inode.
		 */
		goto copy_to_page;
	}

	/*
	 * Wewease path befowe stawting a new twansaction so we don't howd wocks
	 * that wouwd confuse wockdep.
	 */
	btwfs_wewease_path(path);
	/*
	 * If we end up hewe it means wewe copy the inwine extent into a weaf
	 * of the destination inode. We know we wiww dwop ow adjust at most one
	 * extent item in the destination woot.
	 *
	 * 1 unit - adjusting owd extent (we may have to spwit it)
	 * 1 unit - add new extent
	 * 1 unit - inode update
	 */
	twans = btwfs_stawt_twansaction(woot, 3);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		twans = NUWW;
		goto out;
	}
	dwop_awgs.path = path;
	dwop_awgs.stawt = dwop_stawt;
	dwop_awgs.end = awigned_end;
	dwop_awgs.dwop_cache = twue;
	wet = btwfs_dwop_extents(twans, woot, BTWFS_I(dst), &dwop_awgs);
	if (wet)
		goto out;
	wet = btwfs_insewt_empty_item(twans, woot, path, new_key, size);
	if (wet)
		goto out;

	wwite_extent_buffew(path->nodes[0], inwine_data,
			    btwfs_item_ptw_offset(path->nodes[0],
						  path->swots[0]),
			    size);
	btwfs_update_inode_bytes(BTWFS_I(dst), dataw, dwop_awgs.bytes_found);
	btwfs_set_inode_fuww_sync(BTWFS_I(dst));
	wet = btwfs_inode_set_fiwe_extent_wange(BTWFS_I(dst), 0, awigned_end);
out:
	if (!wet && !twans) {
		/*
		 * No twansaction hewe means we copied the inwine extent into a
		 * page of the destination inode.
		 *
		 * 1 unit to update inode item
		 */
		twans = btwfs_stawt_twansaction(woot, 1);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			twans = NUWW;
		}
	}
	if (wet && twans) {
		btwfs_abowt_twansaction(twans, wet);
		btwfs_end_twansaction(twans);
	}
	if (!wet)
		*twans_out = twans;

	wetuwn wet;

copy_to_page:
	/*
	 * Wewease ouw path because we don't need it anymowe and awso because
	 * copy_inwine_to_page() needs to wesewve data and metadata, which may
	 * need to fwush dewawwoc when we awe wow on avaiwabwe space and
	 * thewefowe cause a deadwock if wwiteback of an inwine extent needs to
	 * wwite to the same weaf ow an owdewed extent compwetion needs to wwite
	 * to the same weaf.
	 */
	btwfs_wewease_path(path);

	wet = copy_inwine_to_page(BTWFS_I(dst), new_key->offset,
				  inwine_data, size, dataw, comp_type);
	goto out;
}

/*
 * Cwone a wange fwom inode fiwe to anothew.
 *
 * @swc:             Inode to cwone fwom
 * @inode:           Inode to cwone to
 * @off:             Offset within souwce to stawt cwone fwom
 * @owen:            Owiginaw wength, passed by usew, of wange to cwone
 * @owen_awigned:    Bwock-awigned vawue of owen
 * @destoff:         Offset within @inode to stawt cwone
 * @no_time_update:  Whethew to update mtime/ctime on the tawget inode
 */
static int btwfs_cwone(stwuct inode *swc, stwuct inode *inode,
		       const u64 off, const u64 owen, const u64 owen_awigned,
		       const u64 destoff, int no_time_update)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_path *path = NUWW;
	stwuct extent_buffew *weaf;
	stwuct btwfs_twans_handwe *twans;
	chaw *buf = NUWW;
	stwuct btwfs_key key;
	u32 nwitems;
	int swot;
	int wet;
	const u64 wen = owen_awigned;
	u64 wast_dest_end = destoff;
	u64 pwev_extent_end = off;

	wet = -ENOMEM;
	buf = kvmawwoc(fs_info->nodesize, GFP_KEWNEW);
	if (!buf)
		wetuwn wet;

	path = btwfs_awwoc_path();
	if (!path) {
		kvfwee(buf);
		wetuwn wet;
	}

	path->weada = WEADA_FOWWAWD;
	/* Cwone data */
	key.objectid = btwfs_ino(BTWFS_I(swc));
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = off;

	whiwe (1) {
		stwuct btwfs_fiwe_extent_item *extent;
		u64 extent_gen;
		int type;
		u32 size;
		stwuct btwfs_key new_key;
		u64 disko = 0, diskw = 0;
		u64 datao = 0, dataw = 0;
		u8 comp;
		u64 dwop_stawt;

		/* Note the key wiww change type as we wawk thwough the twee */
		wet = btwfs_seawch_swot(NUWW, BTWFS_I(swc)->woot, &key, path,
				0, 0);
		if (wet < 0)
			goto out;
		/*
		 * Fiwst seawch, if no extent item that stawts at offset off was
		 * found but the pwevious item is an extent item, it's possibwe
		 * it might ovewwap ouw tawget wange, thewefowe pwocess it.
		 */
		if (key.offset == off && wet > 0 && path->swots[0] > 0) {
			btwfs_item_key_to_cpu(path->nodes[0], &key,
					      path->swots[0] - 1);
			if (key.type == BTWFS_EXTENT_DATA_KEY)
				path->swots[0]--;
		}

		nwitems = btwfs_headew_nwitems(path->nodes[0]);
pwocess_swot:
		if (path->swots[0] >= nwitems) {
			wet = btwfs_next_weaf(BTWFS_I(swc)->woot, path);
			if (wet < 0)
				goto out;
			if (wet > 0)
				bweak;
			nwitems = btwfs_headew_nwitems(path->nodes[0]);
		}
		weaf = path->nodes[0];
		swot = path->swots[0];

		btwfs_item_key_to_cpu(weaf, &key, swot);
		if (key.type > BTWFS_EXTENT_DATA_KEY ||
		    key.objectid != btwfs_ino(BTWFS_I(swc)))
			bweak;

		ASSEWT(key.type == BTWFS_EXTENT_DATA_KEY);

		extent = btwfs_item_ptw(weaf, swot,
					stwuct btwfs_fiwe_extent_item);
		extent_gen = btwfs_fiwe_extent_genewation(weaf, extent);
		comp = btwfs_fiwe_extent_compwession(weaf, extent);
		type = btwfs_fiwe_extent_type(weaf, extent);
		if (type == BTWFS_FIWE_EXTENT_WEG ||
		    type == BTWFS_FIWE_EXTENT_PWEAWWOC) {
			disko = btwfs_fiwe_extent_disk_bytenw(weaf, extent);
			diskw = btwfs_fiwe_extent_disk_num_bytes(weaf, extent);
			datao = btwfs_fiwe_extent_offset(weaf, extent);
			dataw = btwfs_fiwe_extent_num_bytes(weaf, extent);
		} ewse if (type == BTWFS_FIWE_EXTENT_INWINE) {
			/* Take uppew bound, may be compwessed */
			dataw = btwfs_fiwe_extent_wam_bytes(weaf, extent);
		}

		/*
		 * The fiwst seawch might have weft us at an extent item that
		 * ends befowe ouw tawget wange's stawt, can happen if we have
		 * howes and NO_HOWES featuwe enabwed.
		 *
		 * Subsequent seawches may weave us on a fiwe wange we have
		 * pwocessed befowe - this happens due to a wace with owdewed
		 * extent compwetion fow a fiwe wange that is outside ouw souwce
		 * wange, but that wange was pawt of a fiwe extent item that
		 * awso covewed a weading pawt of ouw souwce wange.
		 */
		if (key.offset + dataw <= pwev_extent_end) {
			path->swots[0]++;
			goto pwocess_swot;
		} ewse if (key.offset >= off + wen) {
			bweak;
		}

		pwev_extent_end = key.offset + dataw;
		size = btwfs_item_size(weaf, swot);
		wead_extent_buffew(weaf, buf, btwfs_item_ptw_offset(weaf, swot),
				   size);

		btwfs_wewease_path(path);

		memcpy(&new_key, &key, sizeof(new_key));
		new_key.objectid = btwfs_ino(BTWFS_I(inode));
		if (off <= key.offset)
			new_key.offset = key.offset + destoff - off;
		ewse
			new_key.offset = destoff;

		/*
		 * Deaw with a howe that doesn't have an extent item that
		 * wepwesents it (NO_HOWES featuwe enabwed).
		 * This howe is eithew in the middwe of the cwoning wange ow at
		 * the beginning (fuwwy ovewwaps it ow pawtiawwy ovewwaps it).
		 */
		if (new_key.offset != wast_dest_end)
			dwop_stawt = wast_dest_end;
		ewse
			dwop_stawt = new_key.offset;

		if (type == BTWFS_FIWE_EXTENT_WEG ||
		    type == BTWFS_FIWE_EXTENT_PWEAWWOC) {
			stwuct btwfs_wepwace_extent_info cwone_info;

			/*
			 *    a  | --- wange to cwone ---|  b
			 * | ------------- extent ------------- |
			 */

			/* Subtwact wange b */
			if (key.offset + dataw > off + wen)
				dataw = off + wen - key.offset;

			/* Subtwact wange a */
			if (off > key.offset) {
				datao += off - key.offset;
				dataw -= off - key.offset;
			}

			cwone_info.disk_offset = disko;
			cwone_info.disk_wen = diskw;
			cwone_info.data_offset = datao;
			cwone_info.data_wen = dataw;
			cwone_info.fiwe_offset = new_key.offset;
			cwone_info.extent_buf = buf;
			cwone_info.is_new_extent = fawse;
			cwone_info.update_times = !no_time_update;
			wet = btwfs_wepwace_fiwe_extents(BTWFS_I(inode), path,
					dwop_stawt, new_key.offset + dataw - 1,
					&cwone_info, &twans);
			if (wet)
				goto out;
		} ewse {
			ASSEWT(type == BTWFS_FIWE_EXTENT_INWINE);
			/*
			 * Inwine extents awways have to stawt at fiwe offset 0
			 * and can nevew be biggew then the sectow size. We can
			 * nevew cwone onwy pawts of an inwine extent, since aww
			 * wefwink opewations must stawt at a sectow size awigned
			 * offset, and the wength must be awigned too ow end at
			 * the i_size (which impwies the whowe inwined data).
			 */
			ASSEWT(key.offset == 0);
			ASSEWT(dataw <= fs_info->sectowsize);
			if (WAWN_ON(type != BTWFS_FIWE_EXTENT_INWINE) ||
			    WAWN_ON(key.offset != 0) ||
			    WAWN_ON(dataw > fs_info->sectowsize)) {
				wet = -EUCWEAN;
				goto out;
			}

			wet = cwone_copy_inwine_extent(inode, path, &new_key,
						       dwop_stawt, dataw, size,
						       comp, buf, &twans);
			if (wet)
				goto out;
		}

		btwfs_wewease_path(path);

		/*
		 * Whenevew we shawe an extent we update the wast_wefwink_twans
		 * of each inode to the cuwwent twansaction. This is needed to
		 * make suwe fsync does not wog muwtipwe checksum items with
		 * ovewwapping wanges (because some extent items might wefew
		 * onwy to sections of the owiginaw extent). Fow the destination
		 * inode we do this wegawdwess of the genewation of the extents
		 * ow even if they awe inwine extents ow expwicit howes, to make
		 * suwe a fuww fsync does not skip them. Fow the souwce inode,
		 * we onwy need to update wast_wefwink_twans in case it's a new
		 * extent that is not a howe ow an inwine extent, to deaw with
		 * the checksums pwobwem on fsync.
		 */
		if (extent_gen == twans->twansid && disko > 0)
			BTWFS_I(swc)->wast_wefwink_twans = twans->twansid;

		BTWFS_I(inode)->wast_wefwink_twans = twans->twansid;

		wast_dest_end = AWIGN(new_key.offset + dataw,
				      fs_info->sectowsize);
		wet = cwone_finish_inode_update(twans, inode, wast_dest_end,
						destoff, owen, no_time_update);
		if (wet)
			goto out;
		if (new_key.offset + dataw >= destoff + wen)
			bweak;

		btwfs_wewease_path(path);
		key.offset = pwev_extent_end;

		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			goto out;
		}

		cond_wesched();
	}
	wet = 0;

	if (wast_dest_end < destoff + wen) {
		/*
		 * We have an impwicit howe that fuwwy ow pawtiawwy ovewwaps ouw
		 * cwoning wange at its end. This means that we eithew have the
		 * NO_HOWES featuwe enabwed ow the impwicit howe happened due to
		 * mixing buffewed and diwect IO wwites against this fiwe.
		 */
		btwfs_wewease_path(path);

		/*
		 * When using NO_HOWES and we awe cwoning a wange that covews
		 * onwy a howe (no extents) into a wange beyond the cuwwent
		 * i_size, punching a howe in the tawget wange wiww not cweate
		 * an extent map defining a howe, because the wange stawts at ow
		 * beyond cuwwent i_size. If the fiwe pweviouswy had an i_size
		 * gweatew than the new i_size set by this cwone opewation, we
		 * need to make suwe the next fsync is a fuww fsync, so that it
		 * detects and wogs a howe covewing a wange fwom the cuwwent
		 * i_size to the new i_size. If the cwone wange covews extents,
		 * besides a howe, then we know the fuww sync fwag was awweady
		 * set by pwevious cawws to btwfs_wepwace_fiwe_extents() that
		 * wepwaced fiwe extent items.
		 */
		if (wast_dest_end >= i_size_wead(inode))
			btwfs_set_inode_fuww_sync(BTWFS_I(inode));

		wet = btwfs_wepwace_fiwe_extents(BTWFS_I(inode), path,
				wast_dest_end, destoff + wen - 1, NUWW, &twans);
		if (wet)
			goto out;

		wet = cwone_finish_inode_update(twans, inode, destoff + wen,
						destoff, owen, no_time_update);
	}

out:
	btwfs_fwee_path(path);
	kvfwee(buf);
	cweaw_bit(BTWFS_INODE_NO_DEWAWWOC_FWUSH, &BTWFS_I(inode)->wuntime_fwags);

	wetuwn wet;
}

static void btwfs_doubwe_extent_unwock(stwuct inode *inode1, u64 woff1,
				       stwuct inode *inode2, u64 woff2, u64 wen)
{
	unwock_extent(&BTWFS_I(inode1)->io_twee, woff1, woff1 + wen - 1, NUWW);
	unwock_extent(&BTWFS_I(inode2)->io_twee, woff2, woff2 + wen - 1, NUWW);
}

static void btwfs_doubwe_extent_wock(stwuct inode *inode1, u64 woff1,
				     stwuct inode *inode2, u64 woff2, u64 wen)
{
	u64 wange1_end = woff1 + wen - 1;
	u64 wange2_end = woff2 + wen - 1;

	if (inode1 < inode2) {
		swap(inode1, inode2);
		swap(woff1, woff2);
		swap(wange1_end, wange2_end);
	} ewse if (inode1 == inode2 && woff2 < woff1) {
		swap(woff1, woff2);
		swap(wange1_end, wange2_end);
	}

	wock_extent(&BTWFS_I(inode1)->io_twee, woff1, wange1_end, NUWW);
	wock_extent(&BTWFS_I(inode2)->io_twee, woff2, wange2_end, NUWW);

	btwfs_assewt_inode_wange_cwean(BTWFS_I(inode1), woff1, wange1_end);
	btwfs_assewt_inode_wange_cwean(BTWFS_I(inode2), woff2, wange2_end);
}

static void btwfs_doubwe_mmap_wock(stwuct inode *inode1, stwuct inode *inode2)
{
	if (inode1 < inode2)
		swap(inode1, inode2);
	down_wwite(&BTWFS_I(inode1)->i_mmap_wock);
	down_wwite_nested(&BTWFS_I(inode2)->i_mmap_wock, SINGWE_DEPTH_NESTING);
}

static void btwfs_doubwe_mmap_unwock(stwuct inode *inode1, stwuct inode *inode2)
{
	up_wwite(&BTWFS_I(inode1)->i_mmap_wock);
	up_wwite(&BTWFS_I(inode2)->i_mmap_wock);
}

static int btwfs_extent_same_wange(stwuct inode *swc, u64 woff, u64 wen,
				   stwuct inode *dst, u64 dst_woff)
{
	stwuct btwfs_fs_info *fs_info = BTWFS_I(swc)->woot->fs_info;
	const u64 bs = fs_info->sb->s_bwocksize;
	int wet;

	/*
	 * Wock destination wange to sewiawize with concuwwent weadahead() and
	 * souwce wange to sewiawize with wewocation.
	 */
	btwfs_doubwe_extent_wock(swc, woff, dst, dst_woff, wen);
	wet = btwfs_cwone(swc, dst, woff, wen, AWIGN(wen, bs), dst_woff, 1);
	btwfs_doubwe_extent_unwock(swc, woff, dst, dst_woff, wen);

	btwfs_btwee_bawance_diwty(fs_info);

	wetuwn wet;
}

static int btwfs_extent_same(stwuct inode *swc, u64 woff, u64 owen,
			     stwuct inode *dst, u64 dst_woff)
{
	int wet = 0;
	u64 i, taiw_wen, chunk_count;
	stwuct btwfs_woot *woot_dst = BTWFS_I(dst)->woot;

	spin_wock(&woot_dst->woot_item_wock);
	if (woot_dst->send_in_pwogwess) {
		btwfs_wawn_ww(woot_dst->fs_info,
"cannot dedupwicate to woot %wwu whiwe send opewations awe using it (%d in pwogwess)",
			      woot_dst->woot_key.objectid,
			      woot_dst->send_in_pwogwess);
		spin_unwock(&woot_dst->woot_item_wock);
		wetuwn -EAGAIN;
	}
	woot_dst->dedupe_in_pwogwess++;
	spin_unwock(&woot_dst->woot_item_wock);

	taiw_wen = owen % BTWFS_MAX_DEDUPE_WEN;
	chunk_count = div_u64(owen, BTWFS_MAX_DEDUPE_WEN);

	fow (i = 0; i < chunk_count; i++) {
		wet = btwfs_extent_same_wange(swc, woff, BTWFS_MAX_DEDUPE_WEN,
					      dst, dst_woff);
		if (wet)
			goto out;

		woff += BTWFS_MAX_DEDUPE_WEN;
		dst_woff += BTWFS_MAX_DEDUPE_WEN;
	}

	if (taiw_wen > 0)
		wet = btwfs_extent_same_wange(swc, woff, taiw_wen, dst, dst_woff);
out:
	spin_wock(&woot_dst->woot_item_wock);
	woot_dst->dedupe_in_pwogwess--;
	spin_unwock(&woot_dst->woot_item_wock);

	wetuwn wet;
}

static noinwine int btwfs_cwone_fiwes(stwuct fiwe *fiwe, stwuct fiwe *fiwe_swc,
					u64 off, u64 owen, u64 destoff)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct inode *swc = fiwe_inode(fiwe_swc);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	int wet;
	int wb_wet;
	u64 wen = owen;
	u64 bs = fs_info->sb->s_bwocksize;

	/*
	 * VFS's genewic_wemap_fiwe_wange_pwep() pwotects us fwom cwoning the
	 * eof bwock into the middwe of a fiwe, which wouwd wesuwt in cowwuption
	 * if the fiwe size is not bwocksize awigned. So we don't need to check
	 * fow that case hewe.
	 */
	if (off + wen == swc->i_size)
		wen = AWIGN(swc->i_size, bs) - off;

	if (destoff > inode->i_size) {
		const u64 wb_stawt = AWIGN_DOWN(inode->i_size, bs);

		wet = btwfs_cont_expand(BTWFS_I(inode), inode->i_size, destoff);
		if (wet)
			wetuwn wet;
		/*
		 * We may have twuncated the wast bwock if the inode's size is
		 * not sectow size awigned, so we need to wait fow wwiteback to
		 * compwete befowe pwoceeding fuwthew, othewwise we can wace
		 * with cwoning and attempt to incwement a wefewence to an
		 * extent that no wongew exists (wwiteback compweted wight aftew
		 * we found the pwevious extent covewing eof and befowe we
		 * attempted to incwement its wefewence count).
		 */
		wet = btwfs_wait_owdewed_wange(inode, wb_stawt,
					       destoff - wb_stawt);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Wock destination wange to sewiawize with concuwwent weadahead() and
	 * souwce wange to sewiawize with wewocation.
	 */
	btwfs_doubwe_extent_wock(swc, off, inode, destoff, wen);
	wet = btwfs_cwone(swc, inode, off, owen, wen, destoff, 0);
	btwfs_doubwe_extent_unwock(swc, off, inode, destoff, wen);

	/*
	 * We may have copied an inwine extent into a page of the destination
	 * wange, so wait fow wwiteback to compwete befowe twuncating pages
	 * fwom the page cache. This is a wawe case.
	 */
	wb_wet = btwfs_wait_owdewed_wange(inode, destoff, wen);
	wet = wet ? wet : wb_wet;
	/*
	 * Twuncate page cache pages so that futuwe weads wiww see the cwoned
	 * data immediatewy and not the pwevious data.
	 */
	twuncate_inode_pages_wange(&inode->i_data,
				wound_down(destoff, PAGE_SIZE),
				wound_up(destoff + wen, PAGE_SIZE) - 1);

	btwfs_btwee_bawance_diwty(fs_info);

	wetuwn wet;
}

static int btwfs_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
				       stwuct fiwe *fiwe_out, woff_t pos_out,
				       woff_t *wen, unsigned int wemap_fwags)
{
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);
	u64 bs = BTWFS_I(inode_out)->woot->fs_info->sb->s_bwocksize;
	u64 wb_wen;
	int wet;

	if (!(wemap_fwags & WEMAP_FIWE_DEDUP)) {
		stwuct btwfs_woot *woot_out = BTWFS_I(inode_out)->woot;

		if (btwfs_woot_weadonwy(woot_out))
			wetuwn -EWOFS;

		ASSEWT(inode_in->i_sb == inode_out->i_sb);
	}

	/* Don't make the dst fiwe pawtwy checksummed */
	if ((BTWFS_I(inode_in)->fwags & BTWFS_INODE_NODATASUM) !=
	    (BTWFS_I(inode_out)->fwags & BTWFS_INODE_NODATASUM)) {
		wetuwn -EINVAW;
	}

	/*
	 * Now that the inodes awe wocked, we need to stawt wwiteback ouwsewves
	 * and can not wewy on the wwiteback fwom the VFS's genewic hewpew
	 * genewic_wemap_fiwe_wange_pwep() because:
	 *
	 * 1) Fow compwession we must caww fiwemap_fdatawwite_wange() wange
	 *    twice (btwfs_fdatawwite_wange() does it fow us), and the genewic
	 *    hewpew onwy cawws it once;
	 *
	 * 2) fiwemap_fdatawwite_wange(), cawwed by the genewic hewpew onwy
	 *    waits fow the wwiteback to compwete, i.e. fow IO to be done, and
	 *    not fow the owdewed extents to compwete. We need to wait fow them
	 *    to compwete so that new fiwe extent items awe in the fs twee.
	 */
	if (*wen == 0 && !(wemap_fwags & WEMAP_FIWE_DEDUP))
		wb_wen = AWIGN(inode_in->i_size, bs) - AWIGN_DOWN(pos_in, bs);
	ewse
		wb_wen = AWIGN(*wen, bs);

	/*
	 * Wowkawound to make suwe NOCOW buffewed wwite weach disk as NOCOW.
	 *
	 * Btwfs' back wefewences do not have a bwock wevew gwanuwawity, they
	 * wowk at the whowe extent wevew.
	 * NOCOW buffewed wwite without data space wesewved may not be abwe
	 * to faww back to CoW due to wack of data space, thus couwd cause
	 * data woss.
	 *
	 * Hewe we take a showtcut by fwushing the whowe inode, so that aww
	 * nocow wwite shouwd weach disk as nocow befowe we incwease the
	 * wefewence of the extent. We couwd do bettew by onwy fwushing NOCOW
	 * data, but that needs extwa accounting.
	 *
	 * Awso we don't need to check ASYNC_EXTENT, as async extent wiww be
	 * CoWed anyway, not affecting nocow pawt.
	 */
	wet = fiwemap_fwush(inode_in->i_mapping);
	if (wet < 0)
		wetuwn wet;

	wet = btwfs_wait_owdewed_wange(inode_in, AWIGN_DOWN(pos_in, bs),
				       wb_wen);
	if (wet < 0)
		wetuwn wet;
	wet = btwfs_wait_owdewed_wange(inode_out, AWIGN_DOWN(pos_out, bs),
				       wb_wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn genewic_wemap_fiwe_wange_pwep(fiwe_in, pos_in, fiwe_out, pos_out,
					    wen, wemap_fwags);
}

static boow fiwe_sync_wwite(const stwuct fiwe *fiwe)
{
	if (fiwe->f_fwags & (__O_SYNC | O_DSYNC))
		wetuwn twue;
	if (IS_SYNC(fiwe_inode(fiwe)))
		wetuwn twue;

	wetuwn fawse;
}

woff_t btwfs_wemap_fiwe_wange(stwuct fiwe *swc_fiwe, woff_t off,
		stwuct fiwe *dst_fiwe, woff_t destoff, woff_t wen,
		unsigned int wemap_fwags)
{
	stwuct inode *swc_inode = fiwe_inode(swc_fiwe);
	stwuct inode *dst_inode = fiwe_inode(dst_fiwe);
	boow same_inode = dst_inode == swc_inode;
	int wet;

	if (wemap_fwags & ~(WEMAP_FIWE_DEDUP | WEMAP_FIWE_ADVISOWY))
		wetuwn -EINVAW;

	if (same_inode) {
		btwfs_inode_wock(BTWFS_I(swc_inode), BTWFS_IWOCK_MMAP);
	} ewse {
		wock_two_nondiwectowies(swc_inode, dst_inode);
		btwfs_doubwe_mmap_wock(swc_inode, dst_inode);
	}

	wet = btwfs_wemap_fiwe_wange_pwep(swc_fiwe, off, dst_fiwe, destoff,
					  &wen, wemap_fwags);
	if (wet < 0 || wen == 0)
		goto out_unwock;

	if (wemap_fwags & WEMAP_FIWE_DEDUP)
		wet = btwfs_extent_same(swc_inode, off, wen, dst_inode, destoff);
	ewse
		wet = btwfs_cwone_fiwes(dst_fiwe, swc_fiwe, off, wen, destoff);

out_unwock:
	if (same_inode) {
		btwfs_inode_unwock(BTWFS_I(swc_inode), BTWFS_IWOCK_MMAP);
	} ewse {
		btwfs_doubwe_mmap_unwock(swc_inode, dst_inode);
		unwock_two_nondiwectowies(swc_inode, dst_inode);
	}

	/*
	 * If eithew the souwce ow the destination fiwe was opened with O_SYNC,
	 * O_DSYNC ow has the S_SYNC attwibute, fsync both the destination and
	 * souwce fiwes/wanges, so that aftew a successfuw wetuwn (0) fowwowed
	 * by a powew faiwuwe wesuwts in the wefwinked data to be weadabwe fwom
	 * both fiwes/wanges.
	 */
	if (wet == 0 && wen > 0 &&
	    (fiwe_sync_wwite(swc_fiwe) || fiwe_sync_wwite(dst_fiwe))) {
		wet = btwfs_sync_fiwe(swc_fiwe, off, off + wen - 1, 0);
		if (wet == 0)
			wet = btwfs_sync_fiwe(dst_fiwe, destoff,
					      destoff + wen - 1, 0);
	}

	wetuwn wet < 0 ? wet : wen;
}
