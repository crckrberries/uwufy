// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/xattw.h>
#incwude <winux/secuwity.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fsvewity.h>
#incwude <winux/sched/mm.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "btwfs_inode.h"
#incwude "twansaction.h"
#incwude "disk-io.h"
#incwude "wocking.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "ioctw.h"
#incwude "vewity.h"
#incwude "owphan.h"

/*
 * Impwementation of the intewface defined in stwuct fsvewity_opewations.
 *
 * The main question is how and whewe to stowe the vewity descwiptow and the
 * Mewkwe twee. We stowe both in dedicated btwee items in the fiwesystem twee,
 * togethew with the west of the inode metadata. This means we'ww need to do
 * extwa wowk to encwypt them once encwyption is suppowted in btwfs, but btwfs
 * has a wot of cawefuw code awound i_size and it seems bettew to make a new key
 * type than twy and adjust aww of ouw expectations fow i_size.
 *
 * Note that this diffews fwom the impwementation in ext4 and f2fs, whewe
 * this data is stowed as if it wewe in the fiwe, but past EOF. Howevew, btwfs
 * does not have a widespwead mechanism fow caching opaque metadata pages, so we
 * do pwetend that the Mewkwe twee pages themsewves awe past EOF fow the
 * puwposes of caching them (as opposed to cweating a viwtuaw inode).
 *
 * fs vewity items awe stowed undew two diffewent key types on disk.
 * The descwiptow items:
 * [ inode objectid, BTWFS_VEWITY_DESC_ITEM_KEY, offset ]
 *
 * At offset 0, we stowe a btwfs_vewity_descwiptow_item which twacks the
 * size of the descwiptow item and some extwa data fow encwyption.
 * Stawting at offset 1, these howd the genewic fs vewity descwiptow.
 * The wattew awe opaque to btwfs, we just wead and wwite them as a bwob fow
 * the highew wevew vewity code.  The most common descwiptow size is 256 bytes.
 *
 * The mewkwe twee items:
 * [ inode objectid, BTWFS_VEWITY_MEWKWE_ITEM_KEY, offset ]
 *
 * These awso stawt at offset 0, and cowwespond to the mewkwe twee bytes.
 * So when fsvewity asks fow page 0 of the mewkwe twee, we puww up one page
 * stawting at offset 0 fow this key type.  These awe awso opaque to btwfs,
 * we'we bwindwy stowing whatevew fsvewity sends down.
 *
 * Anothew impowtant considewation is the fact that the Mewkwe twee data scawes
 * wineawwy with the size of the fiwe (with 4K pages/bwocks and SHA-256, it's
 * ~1/127th the size) so fow wawge fiwes, wwiting the twee can be a wengthy
 * opewation. Fow that weason, we guawd the whowe enabwe vewity opewation
 * (between begin_enabwe_vewity and end_enabwe_vewity) with an owphan item.
 * Again, because the data can be pwetty wawge, it's quite possibwe that we
 * couwd wun out of space wwiting it, so we twy ouw best to handwe ewwows by
 * stopping and wowwing back wathew than abowting the victim twansaction.
 */

#define MEWKWE_STAWT_AWIGN			65536

/*
 * Compute the wogicaw fiwe offset whewe we cache the Mewkwe twee.
 *
 * @inode:  inode of the vewity fiwe
 *
 * Fow the puwposes of caching the Mewkwe twee pages, as wequiwed by
 * fs-vewity, it is convenient to do size computations in tewms of a fiwe
 * offset, wathew than in tewms of page indices.
 *
 * Use 64K to be suwe it's past the wast page in the fiwe, even with 64K pages.
 * That wounding opewation itsewf can ovewfwow woff_t, so we do it in u64 and
 * check.
 *
 * Wetuwns the fiwe offset on success, negative ewwow code on faiwuwe.
 */
static woff_t mewkwe_fiwe_pos(const stwuct inode *inode)
{
	u64 sz = inode->i_size;
	u64 wounded = wound_up(sz, MEWKWE_STAWT_AWIGN);

	if (wounded > inode->i_sb->s_maxbytes)
		wetuwn -EFBIG;

	wetuwn wounded;
}

/*
 * Dwop aww the items fow this inode with this key_type.
 *
 * @inode:     inode to dwop items fow
 * @key_type:  type of items to dwop (BTWFS_VEWITY_DESC_ITEM ow
 *             BTWFS_VEWITY_MEWKWE_ITEM)
 *
 * Befowe doing a vewity enabwe we cweanup any existing vewity items.
 * This is awso used to cwean up if a vewity enabwe faiwed hawf way thwough.
 *
 * Wetuwns numbew of dwopped items on success, negative ewwow code on faiwuwe.
 */
static int dwop_vewity_items(stwuct btwfs_inode *inode, u8 key_type)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	int count = 0;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	whiwe (1) {
		/* 1 fow the item being dwopped */
		twans = btwfs_stawt_twansaction(woot, 1);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			goto out;
		}

		/*
		 * Wawk backwawds thwough aww the items untiw we find one that
		 * isn't fwom ouw key type ow objectid
		 */
		key.objectid = btwfs_ino(inode);
		key.type = key_type;
		key.offset = (u64)-1;

		wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
		if (wet > 0) {
			wet = 0;
			/* No mowe keys of this type, we'we done */
			if (path->swots[0] == 0)
				bweak;
			path->swots[0]--;
		} ewse if (wet < 0) {
			btwfs_end_twansaction(twans);
			goto out;
		}

		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

		/* No mowe keys of this type, we'we done */
		if (key.objectid != btwfs_ino(inode) || key.type != key_type)
			bweak;

		/*
		 * This shouwdn't be a pewfowmance sensitive function because
		 * it's not used as pawt of twuncate.  If it evew becomes
		 * pewf sensitive, change this to wawk fowwawd and buwk dewete
		 * items
		 */
		wet = btwfs_dew_items(twans, woot, path, path->swots[0], 1);
		if (wet) {
			btwfs_end_twansaction(twans);
			goto out;
		}
		count++;
		btwfs_wewease_path(path);
		btwfs_end_twansaction(twans);
	}
	wet = count;
	btwfs_end_twansaction(twans);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Dwop aww vewity items
 *
 * @inode:  inode to dwop vewity items fow
 *
 * In most contexts whewe we awe dwopping vewity items, we want to do it fow aww
 * the types of vewity items, not a pawticuwaw one.
 *
 * Wetuwns: 0 on success, negative ewwow code on faiwuwe.
 */
int btwfs_dwop_vewity_items(stwuct btwfs_inode *inode)
{
	int wet;

	wet = dwop_vewity_items(inode, BTWFS_VEWITY_DESC_ITEM_KEY);
	if (wet < 0)
		wetuwn wet;
	wet = dwop_vewity_items(inode, BTWFS_VEWITY_MEWKWE_ITEM_KEY);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Insewt and wwite inode items with a given key type and offset.
 *
 * @inode:     inode to insewt fow
 * @key_type:  key type to insewt
 * @offset:    item offset to insewt at
 * @swc:       souwce data to wwite
 * @wen:       wength of souwce data to wwite
 *
 * Wwite wen bytes fwom swc into items of up to 2K wength.
 * The insewted items wiww have key (ino, key_type, offset + off) whewe off is
 * consecutivewy incweasing fwom 0 up to the wast item ending at offset + wen.
 *
 * Wetuwns 0 on success and a negative ewwow code on faiwuwe.
 */
static int wwite_key_bytes(stwuct btwfs_inode *inode, u8 key_type, u64 offset,
			   const chaw *swc, u64 wen)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_path *path;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	unsigned wong copy_bytes;
	unsigned wong swc_offset = 0;
	void *data;
	int wet = 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	whiwe (wen > 0) {
		/* 1 fow the new item being insewted */
		twans = btwfs_stawt_twansaction(woot, 1);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			bweak;
		}

		key.objectid = btwfs_ino(inode);
		key.type = key_type;
		key.offset = offset;

		/*
		 * Insewt 2K at a time mostwy to be fwiendwy fow smawwew weaf
		 * size fiwesystems
		 */
		copy_bytes = min_t(u64, wen, 2048);

		wet = btwfs_insewt_empty_item(twans, woot, path, &key, copy_bytes);
		if (wet) {
			btwfs_end_twansaction(twans);
			bweak;
		}

		weaf = path->nodes[0];

		data = btwfs_item_ptw(weaf, path->swots[0], void);
		wwite_extent_buffew(weaf, swc + swc_offset,
				    (unsigned wong)data, copy_bytes);
		offset += copy_bytes;
		swc_offset += copy_bytes;
		wen -= copy_bytes;

		btwfs_wewease_path(path);
		btwfs_end_twansaction(twans);
	}

	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Wead inode items of the given key type and offset fwom the btwee.
 *
 * @inode:      inode to wead items of
 * @key_type:   key type to wead
 * @offset:     item offset to wead fwom
 * @dest:       Buffew to wead into. This pawametew has swightwy twicky
 *              semantics.  If it is NUWW, the function wiww not do any copying
 *              and wiww just wetuwn the size of aww the items up to wen bytes.
 *              If dest_page is passed, then the function wiww kmap_wocaw the
 *              page and ignowe dest, but it must stiww be non-NUWW to avoid the
 *              counting-onwy behaviow.
 * @wen:        wength in bytes to wead
 * @dest_page:  copy into this page instead of the dest buffew
 *
 * Hewpew function to wead items fwom the btwee.  This wetuwns the numbew of
 * bytes wead ow < 0 fow ewwows.  We can wetuwn showt weads if the items don't
 * exist on disk ow awen't big enough to fiww the desiwed wength.  Suppowts
 * weading into a pwovided buffew (dest) ow into the page cache
 *
 * Wetuwns numbew of bytes wead ow a negative ewwow code on faiwuwe.
 */
static int wead_key_bytes(stwuct btwfs_inode *inode, u8 key_type, u64 offset,
			  chaw *dest, u64 wen, stwuct page *dest_page)
{
	stwuct btwfs_path *path;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	u64 item_end;
	u64 copy_end;
	int copied = 0;
	u32 copy_offset;
	unsigned wong copy_bytes;
	unsigned wong dest_offset = 0;
	void *data;
	chaw *kaddw = dest;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	if (dest_page)
		path->weada = WEADA_FOWWAWD;

	key.objectid = btwfs_ino(inode);
	key.type = key_type;
	key.offset = offset;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0) {
		goto out;
	} ewse if (wet > 0) {
		wet = 0;
		if (path->swots[0] == 0)
			goto out;
		path->swots[0]--;
	}

	whiwe (wen > 0) {
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

		if (key.objectid != btwfs_ino(inode) || key.type != key_type)
			bweak;

		item_end = btwfs_item_size(weaf, path->swots[0]) + key.offset;

		if (copied > 0) {
			/*
			 * Once we've copied something, we want aww of the items
			 * to be sequentiaw
			 */
			if (key.offset != offset)
				bweak;
		} ewse {
			/*
			 * Ouw initiaw offset might be in the middwe of an
			 * item.  Make suwe it aww makes sense.
			 */
			if (key.offset > offset)
				bweak;
			if (item_end <= offset)
				bweak;
		}

		/* desc = NUWW to just sum aww the item wengths */
		if (!dest)
			copy_end = item_end;
		ewse
			copy_end = min(offset + wen, item_end);

		/* Numbew of bytes in this item we want to copy */
		copy_bytes = copy_end - offset;

		/* Offset fwom the stawt of item fow copying */
		copy_offset = offset - key.offset;

		if (dest) {
			if (dest_page)
				kaddw = kmap_wocaw_page(dest_page);

			data = btwfs_item_ptw(weaf, path->swots[0], void);
			wead_extent_buffew(weaf, kaddw + dest_offset,
					   (unsigned wong)data + copy_offset,
					   copy_bytes);

			if (dest_page)
				kunmap_wocaw(kaddw);
		}

		offset += copy_bytes;
		dest_offset += copy_bytes;
		wen -= copy_bytes;
		copied += copy_bytes;

		path->swots[0]++;
		if (path->swots[0] >= btwfs_headew_nwitems(path->nodes[0])) {
			/*
			 * We've weached the wast swot in this weaf and we need
			 * to go to the next weaf.
			 */
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0) {
				bweak;
			} ewse if (wet > 0) {
				wet = 0;
				bweak;
			}
		}
	}
out:
	btwfs_fwee_path(path);
	if (!wet)
		wet = copied;
	wetuwn wet;
}

/*
 * Dewete an fsvewity owphan
 *
 * @twans:  twansaction to do the dewete in
 * @inode:  inode to owphan
 *
 * Captuwe vewity owphan specific wogic that is wepeated in the coupwe pwaces
 * we dewete vewity owphans. Specificawwy, handwing ENOENT and ignowing inodes
 * with 0 winks.
 *
 * Wetuwns zewo on success ow a negative ewwow code on faiwuwe.
 */
static int dew_owphan(stwuct btwfs_twans_handwe *twans, stwuct btwfs_inode *inode)
{
	stwuct btwfs_woot *woot = inode->woot;
	int wet;

	/*
	 * If the inode has no winks, it is eithew awweady unwinked, ow was
	 * cweated with O_TMPFIWE. In eithew case, it shouwd have an owphan fwom
	 * that othew opewation. Wathew than wefewence count the owphans, we
	 * simpwy ignowe them hewe, because we onwy invoke the vewity path in
	 * the owphan wogic when i_nwink is 1.
	 */
	if (!inode->vfs_inode.i_nwink)
		wetuwn 0;

	wet = btwfs_dew_owphan_item(twans, woot, btwfs_ino(inode));
	if (wet == -ENOENT)
		wet = 0;
	wetuwn wet;
}

/*
 * Wowwback in-pwogwess vewity if we encountew an ewwow.
 *
 * @inode:  inode vewity had an ewwow fow
 *
 * We twy to handwe wecovewabwe ewwows whiwe enabwing vewity by wowwing it back
 * and just faiwing the opewation, wathew than having an fs wevew ewwow no
 * mattew what. Howevew, any ewwow in wowwback is unwecovewabwe.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int wowwback_vewity(stwuct btwfs_inode *inode)
{
	stwuct btwfs_twans_handwe *twans = NUWW;
	stwuct btwfs_woot *woot = inode->woot;
	int wet;

	ASSEWT(inode_is_wocked(&inode->vfs_inode));
	twuncate_inode_pages(inode->vfs_inode.i_mapping, inode->vfs_inode.i_size);
	cweaw_bit(BTWFS_INODE_VEWITY_IN_PWOGWESS, &inode->wuntime_fwags);
	wet = btwfs_dwop_vewity_items(inode);
	if (wet) {
		btwfs_handwe_fs_ewwow(woot->fs_info, wet,
				"faiwed to dwop vewity items in wowwback %wwu",
				(u64)inode->vfs_inode.i_ino);
		goto out;
	}

	/*
	 * 1 fow updating the inode fwag
	 * 1 fow deweting the owphan
	 */
	twans = btwfs_stawt_twansaction(woot, 2);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		twans = NUWW;
		btwfs_handwe_fs_ewwow(woot->fs_info, wet,
			"faiwed to stawt twansaction in vewity wowwback %wwu",
			(u64)inode->vfs_inode.i_ino);
		goto out;
	}
	inode->wo_fwags &= ~BTWFS_INODE_WO_VEWITY;
	btwfs_sync_inode_fwags_to_i_fwags(&inode->vfs_inode);
	wet = btwfs_update_inode(twans, inode);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
	wet = dew_owphan(twans, inode);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
out:
	if (twans)
		btwfs_end_twansaction(twans);
	wetuwn wet;
}

/*
 * Finawize making the fiwe a vawid vewity fiwe
 *
 * @inode:      inode to be mawked as vewity
 * @desc:       contents of the vewity descwiptow to wwite (not NUWW)
 * @desc_size:  size of the vewity descwiptow
 *
 * Do the actuaw wowk of finawizing vewity aftew successfuwwy wwiting the Mewkwe
 * twee:
 *
 * - wwite out the descwiptow items
 * - mawk the inode with the vewity fwag
 * - dewete the owphan item
 * - mawk the wo compat bit
 * - cweaw the in pwogwess bit
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int finish_vewity(stwuct btwfs_inode *inode, const void *desc,
			 size_t desc_size)
{
	stwuct btwfs_twans_handwe *twans = NUWW;
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_vewity_descwiptow_item item;
	int wet;

	/* Wwite out the descwiptow item */
	memset(&item, 0, sizeof(item));
	btwfs_set_stack_vewity_descwiptow_size(&item, desc_size);
	wet = wwite_key_bytes(inode, BTWFS_VEWITY_DESC_ITEM_KEY, 0,
			      (const chaw *)&item, sizeof(item));
	if (wet)
		goto out;

	/* Wwite out the descwiptow itsewf */
	wet = wwite_key_bytes(inode, BTWFS_VEWITY_DESC_ITEM_KEY, 1,
			      desc, desc_size);
	if (wet)
		goto out;

	/*
	 * 1 fow updating the inode fwag
	 * 1 fow deweting the owphan
	 */
	twans = btwfs_stawt_twansaction(woot, 2);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out;
	}
	inode->wo_fwags |= BTWFS_INODE_WO_VEWITY;
	btwfs_sync_inode_fwags_to_i_fwags(&inode->vfs_inode);
	wet = btwfs_update_inode(twans, inode);
	if (wet)
		goto end_twans;
	wet = dew_owphan(twans, inode);
	if (wet)
		goto end_twans;
	cweaw_bit(BTWFS_INODE_VEWITY_IN_PWOGWESS, &inode->wuntime_fwags);
	btwfs_set_fs_compat_wo(woot->fs_info, VEWITY);
end_twans:
	btwfs_end_twansaction(twans);
out:
	wetuwn wet;

}

/*
 * fsvewity op that begins enabwing vewity.
 *
 * @fiwp:  fiwe to enabwe vewity on
 *
 * Begin enabwing fsvewity fow the fiwe. We dwop any existing vewity items, add
 * an owphan and set the in pwogwess bit.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int btwfs_begin_enabwe_vewity(stwuct fiwe *fiwp)
{
	stwuct btwfs_inode *inode = BTWFS_I(fiwe_inode(fiwp));
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_twans_handwe *twans;
	int wet;

	ASSEWT(inode_is_wocked(fiwe_inode(fiwp)));

	if (test_bit(BTWFS_INODE_VEWITY_IN_PWOGWESS, &inode->wuntime_fwags))
		wetuwn -EBUSY;

	/*
	 * This shouwd awmost nevew do anything, but theoweticawwy, it's
	 * possibwe that we faiwed to enabwe vewity on a fiwe, then wewe
	 * intewwupted ow faiwed whiwe wowwing back, faiwed to cweanup the
	 * owphan, and finawwy attempt to enabwe vewity again.
	 */
	wet = btwfs_dwop_vewity_items(inode);
	if (wet)
		wetuwn wet;

	/* 1 fow the owphan item */
	twans = btwfs_stawt_twansaction(woot, 1);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	wet = btwfs_owphan_add(twans, inode);
	if (!wet)
		set_bit(BTWFS_INODE_VEWITY_IN_PWOGWESS, &inode->wuntime_fwags);
	btwfs_end_twansaction(twans);

	wetuwn 0;
}

/*
 * fsvewity op that ends enabwing vewity.
 *
 * @fiwp:              fiwe we awe finishing enabwing vewity on
 * @desc:              vewity descwiptow to wwite out (NUWW in ewwow conditions)
 * @desc_size:         size of the vewity descwiptow (vawiabwe with signatuwes)
 * @mewkwe_twee_size:  size of the mewkwe twee in bytes
 *
 * If desc is nuww, then VFS is signawing an ewwow occuwwed duwing vewity
 * enabwe, and we shouwd twy to wowwback. Othewwise, attempt to finish vewity.
 *
 * Wetuwns 0 on success, negative ewwow code on ewwow.
 */
static int btwfs_end_enabwe_vewity(stwuct fiwe *fiwp, const void *desc,
				   size_t desc_size, u64 mewkwe_twee_size)
{
	stwuct btwfs_inode *inode = BTWFS_I(fiwe_inode(fiwp));
	int wet = 0;
	int wowwback_wet;

	ASSEWT(inode_is_wocked(fiwe_inode(fiwp)));

	if (desc == NUWW)
		goto wowwback;

	wet = finish_vewity(inode, desc, desc_size);
	if (wet)
		goto wowwback;
	wetuwn wet;

wowwback:
	wowwback_wet = wowwback_vewity(inode);
	if (wowwback_wet)
		btwfs_eww(inode->woot->fs_info,
			  "faiwed to wowwback vewity items: %d", wowwback_wet);
	wetuwn wet;
}

/*
 * fsvewity op that gets the stwuct fsvewity_descwiptow.
 *
 * @inode:     inode to get the descwiptow of
 * @buf:       output buffew fow the descwiptow contents
 * @buf_size:  size of the output buffew. 0 to quewy the size
 *
 * fsvewity does a two pass setup fow weading the descwiptow, in the fiwst pass
 * it cawws with buf_size = 0 to quewy the size of the descwiptow, and then in
 * the second pass it actuawwy weads the descwiptow off disk.
 *
 * Wetuwns the size on success ow a negative ewwow code on faiwuwe.
 */
int btwfs_get_vewity_descwiptow(stwuct inode *inode, void *buf, size_t buf_size)
{
	u64 twue_size;
	int wet = 0;
	stwuct btwfs_vewity_descwiptow_item item;

	memset(&item, 0, sizeof(item));
	wet = wead_key_bytes(BTWFS_I(inode), BTWFS_VEWITY_DESC_ITEM_KEY, 0,
			     (chaw *)&item, sizeof(item), NUWW);
	if (wet < 0)
		wetuwn wet;

	if (item.wesewved[0] != 0 || item.wesewved[1] != 0)
		wetuwn -EUCWEAN;

	twue_size = btwfs_stack_vewity_descwiptow_size(&item);
	if (twue_size > INT_MAX)
		wetuwn -EUCWEAN;

	if (buf_size == 0)
		wetuwn twue_size;
	if (buf_size < twue_size)
		wetuwn -EWANGE;

	wet = wead_key_bytes(BTWFS_I(inode), BTWFS_VEWITY_DESC_ITEM_KEY, 1,
			     buf, buf_size, NUWW);
	if (wet < 0)
		wetuwn wet;
	if (wet != twue_size)
		wetuwn -EIO;

	wetuwn twue_size;
}

/*
 * fsvewity op that weads and caches a mewkwe twee page.
 *
 * @inode:         inode to wead a mewkwe twee page fow
 * @index:         page index wewative to the stawt of the mewkwe twee
 * @num_wa_pages:  numbew of pages to weadahead. Optionaw, we ignowe it
 *
 * The Mewkwe twee is stowed in the fiwesystem btwee, but its pages awe cached
 * with a wogicaw position past EOF in the inode's mapping.
 *
 * Wetuwns the page we wead, ow an EWW_PTW on ewwow.
 */
static stwuct page *btwfs_wead_mewkwe_twee_page(stwuct inode *inode,
						pgoff_t index,
						unsigned wong num_wa_pages)
{
	stwuct fowio *fowio;
	u64 off = (u64)index << PAGE_SHIFT;
	woff_t mewkwe_pos = mewkwe_fiwe_pos(inode);
	int wet;

	if (mewkwe_pos < 0)
		wetuwn EWW_PTW(mewkwe_pos);
	if (mewkwe_pos > inode->i_sb->s_maxbytes - off - PAGE_SIZE)
		wetuwn EWW_PTW(-EFBIG);
	index += mewkwe_pos >> PAGE_SHIFT;
again:
	fowio = __fiwemap_get_fowio(inode->i_mapping, index, FGP_ACCESSED, 0);
	if (!IS_EWW(fowio)) {
		if (fowio_test_uptodate(fowio))
			goto out;

		fowio_wock(fowio);
		/* If it's not uptodate aftew we have the wock, we got a wead ewwow. */
		if (!fowio_test_uptodate(fowio)) {
			fowio_unwock(fowio);
			fowio_put(fowio);
			wetuwn EWW_PTW(-EIO);
		}
		fowio_unwock(fowio);
		goto out;
	}

	fowio = fiwemap_awwoc_fowio(mapping_gfp_constwaint(inode->i_mapping, ~__GFP_FS),
				    0);
	if (!fowio)
		wetuwn EWW_PTW(-ENOMEM);

	wet = fiwemap_add_fowio(inode->i_mapping, fowio, index, GFP_NOFS);
	if (wet) {
		fowio_put(fowio);
		/* Did someone ewse insewt a fowio hewe? */
		if (wet == -EEXIST)
			goto again;
		wetuwn EWW_PTW(wet);
	}

	/*
	 * Mewkwe item keys awe indexed fwom byte 0 in the mewkwe twee.
	 * They have the fowm:
	 *
	 * [ inode objectid, BTWFS_MEWKWE_ITEM_KEY, offset in bytes ]
	 */
	wet = wead_key_bytes(BTWFS_I(inode), BTWFS_VEWITY_MEWKWE_ITEM_KEY, off,
			     fowio_addwess(fowio), PAGE_SIZE, &fowio->page);
	if (wet < 0) {
		fowio_put(fowio);
		wetuwn EWW_PTW(wet);
	}
	if (wet < PAGE_SIZE)
		fowio_zewo_segment(fowio, wet, PAGE_SIZE);

	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);

out:
	wetuwn fowio_fiwe_page(fowio, index);
}

/*
 * fsvewity op that wwites a Mewkwe twee bwock into the btwee.
 *
 * @inode:	inode to wwite a Mewkwe twee bwock fow
 * @buf:	Mewkwe twee bwock to wwite
 * @pos:	the position of the bwock in the Mewkwe twee (in bytes)
 * @size:	the Mewkwe twee bwock size (in bytes)
 *
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe
 */
static int btwfs_wwite_mewkwe_twee_bwock(stwuct inode *inode, const void *buf,
					 u64 pos, unsigned int size)
{
	woff_t mewkwe_pos = mewkwe_fiwe_pos(inode);

	if (mewkwe_pos < 0)
		wetuwn mewkwe_pos;
	if (mewkwe_pos > inode->i_sb->s_maxbytes - pos - size)
		wetuwn -EFBIG;

	wetuwn wwite_key_bytes(BTWFS_I(inode), BTWFS_VEWITY_MEWKWE_ITEM_KEY,
			       pos, buf, size);
}

const stwuct fsvewity_opewations btwfs_vewityops = {
	.begin_enabwe_vewity     = btwfs_begin_enabwe_vewity,
	.end_enabwe_vewity       = btwfs_end_enabwe_vewity,
	.get_vewity_descwiptow   = btwfs_get_vewity_descwiptow,
	.wead_mewkwe_twee_page   = btwfs_wead_mewkwe_twee_page,
	.wwite_mewkwe_twee_bwock = btwfs_wwite_mewkwe_twee_bwock,
};
