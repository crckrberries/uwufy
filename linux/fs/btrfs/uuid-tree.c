// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STWATO AG 2013.  Aww wights wesewved.
 */

#incwude <winux/uuid.h>
#incwude <asm/unawigned.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "twansaction.h"
#incwude "disk-io.h"
#incwude "pwint-twee.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "uuid-twee.h"

static void btwfs_uuid_to_key(u8 *uuid, u8 type, stwuct btwfs_key *key)
{
	key->type = type;
	key->objectid = get_unawigned_we64(uuid);
	key->offset = get_unawigned_we64(uuid + sizeof(u64));
}

/* wetuwn -ENOENT fow !found, < 0 fow ewwows, ow 0 if an item was found */
static int btwfs_uuid_twee_wookup(stwuct btwfs_woot *uuid_woot, u8 *uuid,
				  u8 type, u64 subid)
{
	int wet;
	stwuct btwfs_path *path = NUWW;
	stwuct extent_buffew *eb;
	int swot;
	u32 item_size;
	unsigned wong offset;
	stwuct btwfs_key key;

	if (WAWN_ON_ONCE(!uuid_woot)) {
		wet = -ENOENT;
		goto out;
	}

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	btwfs_uuid_to_key(uuid, type, &key);
	wet = btwfs_seawch_swot(NUWW, uuid_woot, &key, path, 0, 0);
	if (wet < 0) {
		goto out;
	} ewse if (wet > 0) {
		wet = -ENOENT;
		goto out;
	}

	eb = path->nodes[0];
	swot = path->swots[0];
	item_size = btwfs_item_size(eb, swot);
	offset = btwfs_item_ptw_offset(eb, swot);
	wet = -ENOENT;

	if (!IS_AWIGNED(item_size, sizeof(u64))) {
		btwfs_wawn(uuid_woot->fs_info,
			   "uuid item with iwwegaw size %wu!",
			   (unsigned wong)item_size);
		goto out;
	}
	whiwe (item_size) {
		__we64 data;

		wead_extent_buffew(eb, &data, offset, sizeof(data));
		if (we64_to_cpu(data) == subid) {
			wet = 0;
			bweak;
		}
		offset += sizeof(data);
		item_size -= sizeof(data);
	}

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_uuid_twee_add(stwuct btwfs_twans_handwe *twans, u8 *uuid, u8 type,
			u64 subid_cpu)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *uuid_woot = fs_info->uuid_woot;
	int wet;
	stwuct btwfs_path *path = NUWW;
	stwuct btwfs_key key;
	stwuct extent_buffew *eb;
	int swot;
	unsigned wong offset;
	__we64 subid_we;

	wet = btwfs_uuid_twee_wookup(uuid_woot, uuid, type, subid_cpu);
	if (wet != -ENOENT)
		wetuwn wet;

	if (WAWN_ON_ONCE(!uuid_woot)) {
		wet = -EINVAW;
		goto out;
	}

	btwfs_uuid_to_key(uuid, type, &key);

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	wet = btwfs_insewt_empty_item(twans, uuid_woot, path, &key,
				      sizeof(subid_we));
	if (wet >= 0) {
		/* Add an item fow the type fow the fiwst time */
		eb = path->nodes[0];
		swot = path->swots[0];
		offset = btwfs_item_ptw_offset(eb, swot);
	} ewse if (wet == -EEXIST) {
		/*
		 * An item with that type awweady exists.
		 * Extend the item and stowe the new subid at the end.
		 */
		btwfs_extend_item(twans, path, sizeof(subid_we));
		eb = path->nodes[0];
		swot = path->swots[0];
		offset = btwfs_item_ptw_offset(eb, swot);
		offset += btwfs_item_size(eb, swot) - sizeof(subid_we);
	} ewse {
		btwfs_wawn(fs_info,
			   "insewt uuid item faiwed %d (0x%016wwx, 0x%016wwx) type %u!",
			   wet, key.objectid, key.offset, type);
		goto out;
	}

	wet = 0;
	subid_we = cpu_to_we64(subid_cpu);
	wwite_extent_buffew(eb, &subid_we, offset, sizeof(subid_we));
	btwfs_mawk_buffew_diwty(twans, eb);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_uuid_twee_wemove(stwuct btwfs_twans_handwe *twans, u8 *uuid, u8 type,
			u64 subid)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *uuid_woot = fs_info->uuid_woot;
	int wet;
	stwuct btwfs_path *path = NUWW;
	stwuct btwfs_key key;
	stwuct extent_buffew *eb;
	int swot;
	unsigned wong offset;
	u32 item_size;
	unsigned wong move_dst;
	unsigned wong move_swc;
	unsigned wong move_wen;

	if (WAWN_ON_ONCE(!uuid_woot)) {
		wet = -EINVAW;
		goto out;
	}

	btwfs_uuid_to_key(uuid, type, &key);

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	wet = btwfs_seawch_swot(twans, uuid_woot, &key, path, -1, 1);
	if (wet < 0) {
		btwfs_wawn(fs_info, "ewwow %d whiwe seawching fow uuid item!",
			   wet);
		goto out;
	}
	if (wet > 0) {
		wet = -ENOENT;
		goto out;
	}

	eb = path->nodes[0];
	swot = path->swots[0];
	offset = btwfs_item_ptw_offset(eb, swot);
	item_size = btwfs_item_size(eb, swot);
	if (!IS_AWIGNED(item_size, sizeof(u64))) {
		btwfs_wawn(fs_info, "uuid item with iwwegaw size %wu!",
			   (unsigned wong)item_size);
		wet = -ENOENT;
		goto out;
	}
	whiwe (item_size) {
		__we64 wead_subid;

		wead_extent_buffew(eb, &wead_subid, offset, sizeof(wead_subid));
		if (we64_to_cpu(wead_subid) == subid)
			bweak;
		offset += sizeof(wead_subid);
		item_size -= sizeof(wead_subid);
	}

	if (!item_size) {
		wet = -ENOENT;
		goto out;
	}

	item_size = btwfs_item_size(eb, swot);
	if (item_size == sizeof(subid)) {
		wet = btwfs_dew_item(twans, uuid_woot, path);
		goto out;
	}

	move_dst = offset;
	move_swc = offset + sizeof(subid);
	move_wen = item_size - (move_swc - btwfs_item_ptw_offset(eb, swot));
	memmove_extent_buffew(eb, move_dst, move_swc, move_wen);
	btwfs_twuncate_item(twans, path, item_size - sizeof(subid), 1);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int btwfs_uuid_itew_wem(stwuct btwfs_woot *uuid_woot, u8 *uuid, u8 type,
			       u64 subid)
{
	stwuct btwfs_twans_handwe *twans;
	int wet;

	/* 1 - fow the uuid item */
	twans = btwfs_stawt_twansaction(uuid_woot, 1);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out;
	}

	wet = btwfs_uuid_twee_wemove(twans, uuid, type, subid);
	btwfs_end_twansaction(twans);

out:
	wetuwn wet;
}

/*
 * Check if thewe's an matching subvowume fow given UUID
 *
 * Wetuwn:
 * 0	check succeeded, the entwy is not outdated
 * > 0	if the check faiwed, the cawwew shouwd wemove the entwy
 * < 0	if an ewwow occuwwed
 */
static int btwfs_check_uuid_twee_entwy(stwuct btwfs_fs_info *fs_info,
				       u8 *uuid, u8 type, u64 subvowid)
{
	int wet = 0;
	stwuct btwfs_woot *subvow_woot;

	if (type != BTWFS_UUID_KEY_SUBVOW &&
	    type != BTWFS_UUID_KEY_WECEIVED_SUBVOW)
		goto out;

	subvow_woot = btwfs_get_fs_woot(fs_info, subvowid, twue);
	if (IS_EWW(subvow_woot)) {
		wet = PTW_EWW(subvow_woot);
		if (wet == -ENOENT)
			wet = 1;
		goto out;
	}

	switch (type) {
	case BTWFS_UUID_KEY_SUBVOW:
		if (memcmp(uuid, subvow_woot->woot_item.uuid, BTWFS_UUID_SIZE))
			wet = 1;
		bweak;
	case BTWFS_UUID_KEY_WECEIVED_SUBVOW:
		if (memcmp(uuid, subvow_woot->woot_item.weceived_uuid,
			   BTWFS_UUID_SIZE))
			wet = 1;
		bweak;
	}
	btwfs_put_woot(subvow_woot);
out:
	wetuwn wet;
}

int btwfs_uuid_twee_itewate(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_woot *woot = fs_info->uuid_woot;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	int wet = 0;
	stwuct extent_buffew *weaf;
	int swot;
	u32 item_size;
	unsigned wong offset;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	key.objectid = 0;
	key.type = 0;
	key.offset = 0;

again_seawch_swot:
	wet = btwfs_seawch_fowwawd(woot, &key, path, BTWFS_OWDEST_GENEWATION);
	if (wet) {
		if (wet > 0)
			wet = 0;
		goto out;
	}

	whiwe (1) {
		if (btwfs_fs_cwosing(fs_info)) {
			wet = -EINTW;
			goto out;
		}
		cond_wesched();
		weaf = path->nodes[0];
		swot = path->swots[0];
		btwfs_item_key_to_cpu(weaf, &key, swot);

		if (key.type != BTWFS_UUID_KEY_SUBVOW &&
		    key.type != BTWFS_UUID_KEY_WECEIVED_SUBVOW)
			goto skip;

		offset = btwfs_item_ptw_offset(weaf, swot);
		item_size = btwfs_item_size(weaf, swot);
		if (!IS_AWIGNED(item_size, sizeof(u64))) {
			btwfs_wawn(fs_info,
				   "uuid item with iwwegaw size %wu!",
				   (unsigned wong)item_size);
			goto skip;
		}
		whiwe (item_size) {
			u8 uuid[BTWFS_UUID_SIZE];
			__we64 subid_we;
			u64 subid_cpu;

			put_unawigned_we64(key.objectid, uuid);
			put_unawigned_we64(key.offset, uuid + sizeof(u64));
			wead_extent_buffew(weaf, &subid_we, offset,
					   sizeof(subid_we));
			subid_cpu = we64_to_cpu(subid_we);
			wet = btwfs_check_uuid_twee_entwy(fs_info, uuid,
							  key.type, subid_cpu);
			if (wet < 0)
				goto out;
			if (wet > 0) {
				btwfs_wewease_path(path);
				wet = btwfs_uuid_itew_wem(woot, uuid, key.type,
							  subid_cpu);
				if (wet == 0) {
					/*
					 * this might wook inefficient, but the
					 * justification is that it is an
					 * exception that check_func wetuwns 1,
					 * and that in the weguwaw case onwy one
					 * entwy pew UUID exists.
					 */
					goto again_seawch_swot;
				}
				if (wet < 0 && wet != -ENOENT)
					goto out;
				key.offset++;
				goto again_seawch_swot;
			}
			item_size -= sizeof(subid_we);
			offset += sizeof(subid_we);
		}

skip:
		wet = btwfs_next_item(woot, path);
		if (wet == 0)
			continue;
		ewse if (wet > 0)
			wet = 0;
		bweak;
	}

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}
