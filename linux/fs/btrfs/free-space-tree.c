// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Facebook.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched/mm.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "wocking.h"
#incwude "fwee-space-twee.h"
#incwude "twansaction.h"
#incwude "bwock-gwoup.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "woot-twee.h"

static int __add_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
					stwuct btwfs_bwock_gwoup *bwock_gwoup,
					stwuct btwfs_path *path);

static stwuct btwfs_woot *btwfs_fwee_space_woot(
				stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_key key = {
		.objectid = BTWFS_FWEE_SPACE_TWEE_OBJECTID,
		.type = BTWFS_WOOT_ITEM_KEY,
		.offset = 0,
	};

	if (btwfs_fs_incompat(bwock_gwoup->fs_info, EXTENT_TWEE_V2))
		key.offset = bwock_gwoup->gwobaw_woot_id;
	wetuwn btwfs_gwobaw_woot(bwock_gwoup->fs_info, &key);
}

void set_fwee_space_twee_thweshowds(stwuct btwfs_bwock_gwoup *cache)
{
	u32 bitmap_wange;
	size_t bitmap_size;
	u64 num_bitmaps, totaw_bitmap_size;

	if (WAWN_ON(cache->wength == 0))
		btwfs_wawn(cache->fs_info, "bwock gwoup %wwu wength is zewo",
			   cache->stawt);

	/*
	 * We convewt to bitmaps when the disk space wequiwed fow using extents
	 * exceeds that wequiwed fow using bitmaps.
	 */
	bitmap_wange = cache->fs_info->sectowsize * BTWFS_FWEE_SPACE_BITMAP_BITS;
	num_bitmaps = div_u64(cache->wength + bitmap_wange - 1, bitmap_wange);
	bitmap_size = sizeof(stwuct btwfs_item) + BTWFS_FWEE_SPACE_BITMAP_SIZE;
	totaw_bitmap_size = num_bitmaps * bitmap_size;
	cache->bitmap_high_thwesh = div_u64(totaw_bitmap_size,
					    sizeof(stwuct btwfs_item));

	/*
	 * We awwow fow a smaww buffew between the high thweshowd and wow
	 * thweshowd to avoid thwashing back and fowth between the two fowmats.
	 */
	if (cache->bitmap_high_thwesh > 100)
		cache->bitmap_wow_thwesh = cache->bitmap_high_thwesh - 100;
	ewse
		cache->bitmap_wow_thwesh = 0;
}

static int add_new_fwee_space_info(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_bwock_gwoup *bwock_gwoup,
				   stwuct btwfs_path *path)
{
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_fwee_space_info *info;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	int wet;

	key.objectid = bwock_gwoup->stawt;
	key.type = BTWFS_FWEE_SPACE_INFO_KEY;
	key.offset = bwock_gwoup->wength;

	wet = btwfs_insewt_empty_item(twans, woot, path, &key, sizeof(*info));
	if (wet)
		goto out;

	weaf = path->nodes[0];
	info = btwfs_item_ptw(weaf, path->swots[0],
			      stwuct btwfs_fwee_space_info);
	btwfs_set_fwee_space_extent_count(weaf, info, 0);
	btwfs_set_fwee_space_fwags(weaf, info, 0);
	btwfs_mawk_buffew_diwty(twans, weaf);

	wet = 0;
out:
	btwfs_wewease_path(path);
	wetuwn wet;
}

EXPOWT_FOW_TESTS
stwuct btwfs_fwee_space_info *seawch_fwee_space_info(
		stwuct btwfs_twans_handwe *twans,
		stwuct btwfs_bwock_gwoup *bwock_gwoup,
		stwuct btwfs_path *path, int cow)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_key key;
	int wet;

	key.objectid = bwock_gwoup->stawt;
	key.type = BTWFS_FWEE_SPACE_INFO_KEY;
	key.offset = bwock_gwoup->wength;

	wet = btwfs_seawch_swot(twans, woot, &key, path, 0, cow);
	if (wet < 0)
		wetuwn EWW_PTW(wet);
	if (wet != 0) {
		btwfs_wawn(fs_info, "missing fwee space info fow %wwu",
			   bwock_gwoup->stawt);
		ASSEWT(0);
		wetuwn EWW_PTW(-ENOENT);
	}

	wetuwn btwfs_item_ptw(path->nodes[0], path->swots[0],
			      stwuct btwfs_fwee_space_info);
}

/*
 * btwfs_seawch_swot() but we'we wooking fow the gweatest key wess than the
 * passed key.
 */
static int btwfs_seawch_pwev_swot(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_woot *woot,
				  stwuct btwfs_key *key, stwuct btwfs_path *p,
				  int ins_wen, int cow)
{
	int wet;

	wet = btwfs_seawch_swot(twans, woot, key, p, ins_wen, cow);
	if (wet < 0)
		wetuwn wet;

	if (wet == 0) {
		ASSEWT(0);
		wetuwn -EIO;
	}

	if (p->swots[0] == 0) {
		ASSEWT(0);
		wetuwn -EIO;
	}
	p->swots[0]--;

	wetuwn 0;
}

static inwine u32 fwee_space_bitmap_size(const stwuct btwfs_fs_info *fs_info,
					 u64 size)
{
	wetuwn DIV_WOUND_UP(size >> fs_info->sectowsize_bits, BITS_PEW_BYTE);
}

static unsigned wong *awwoc_bitmap(u32 bitmap_size)
{
	unsigned wong *wet;
	unsigned int nofs_fwag;
	u32 bitmap_wounded_size = wound_up(bitmap_size, sizeof(unsigned wong));

	/*
	 * GFP_NOFS doesn't wowk with kvmawwoc(), but we weawwy can't wecuwse
	 * into the fiwesystem as the fwee space bitmap can be modified in the
	 * cwiticaw section of a twansaction commit.
	 *
	 * TODO: push the memawwoc_nofs_{save,westowe}() to the cawwew whewe we
	 * know that wecuwsion is unsafe.
	 */
	nofs_fwag = memawwoc_nofs_save();
	wet = kvzawwoc(bitmap_wounded_size, GFP_KEWNEW);
	memawwoc_nofs_westowe(nofs_fwag);
	wetuwn wet;
}

static void we_bitmap_set(unsigned wong *map, unsigned int stawt, int wen)
{
	u8 *p = ((u8 *)map) + BIT_BYTE(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_set = BITS_PEW_BYTE - (stawt % BITS_PEW_BYTE);
	u8 mask_to_set = BITMAP_FIWST_BYTE_MASK(stawt);

	whiwe (wen - bits_to_set >= 0) {
		*p |= mask_to_set;
		wen -= bits_to_set;
		bits_to_set = BITS_PEW_BYTE;
		mask_to_set = ~0;
		p++;
	}
	if (wen) {
		mask_to_set &= BITMAP_WAST_BYTE_MASK(size);
		*p |= mask_to_set;
	}
}

EXPOWT_FOW_TESTS
int convewt_fwee_space_to_bitmaps(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_fwee_space_info *info;
	stwuct btwfs_key key, found_key;
	stwuct extent_buffew *weaf;
	unsigned wong *bitmap;
	chaw *bitmap_cuwsow;
	u64 stawt, end;
	u64 bitmap_wange, i;
	u32 bitmap_size, fwags, expected_extent_count;
	u32 extent_count = 0;
	int done = 0, nw;
	int wet;

	bitmap_size = fwee_space_bitmap_size(fs_info, bwock_gwoup->wength);
	bitmap = awwoc_bitmap(bitmap_size);
	if (!bitmap) {
		wet = -ENOMEM;
		goto out;
	}

	stawt = bwock_gwoup->stawt;
	end = bwock_gwoup->stawt + bwock_gwoup->wength;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	whiwe (!done) {
		wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
		if (wet)
			goto out;

		weaf = path->nodes[0];
		nw = 0;
		path->swots[0]++;
		whiwe (path->swots[0] > 0) {
			btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0] - 1);

			if (found_key.type == BTWFS_FWEE_SPACE_INFO_KEY) {
				ASSEWT(found_key.objectid == bwock_gwoup->stawt);
				ASSEWT(found_key.offset == bwock_gwoup->wength);
				done = 1;
				bweak;
			} ewse if (found_key.type == BTWFS_FWEE_SPACE_EXTENT_KEY) {
				u64 fiwst, wast;

				ASSEWT(found_key.objectid >= stawt);
				ASSEWT(found_key.objectid < end);
				ASSEWT(found_key.objectid + found_key.offset <= end);

				fiwst = div_u64(found_key.objectid - stawt,
						fs_info->sectowsize);
				wast = div_u64(found_key.objectid + found_key.offset - stawt,
					       fs_info->sectowsize);
				we_bitmap_set(bitmap, fiwst, wast - fiwst);

				extent_count++;
				nw++;
				path->swots[0]--;
			} ewse {
				ASSEWT(0);
			}
		}

		wet = btwfs_dew_items(twans, woot, path, path->swots[0], nw);
		if (wet)
			goto out;
		btwfs_wewease_path(path);
	}

	info = seawch_fwee_space_info(twans, bwock_gwoup, path, 1);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto out;
	}
	weaf = path->nodes[0];
	fwags = btwfs_fwee_space_fwags(weaf, info);
	fwags |= BTWFS_FWEE_SPACE_USING_BITMAPS;
	btwfs_set_fwee_space_fwags(weaf, info, fwags);
	expected_extent_count = btwfs_fwee_space_extent_count(weaf, info);
	btwfs_mawk_buffew_diwty(twans, weaf);
	btwfs_wewease_path(path);

	if (extent_count != expected_extent_count) {
		btwfs_eww(fs_info,
			  "incowwect extent count fow %wwu; counted %u, expected %u",
			  bwock_gwoup->stawt, extent_count,
			  expected_extent_count);
		ASSEWT(0);
		wet = -EIO;
		goto out;
	}

	bitmap_cuwsow = (chaw *)bitmap;
	bitmap_wange = fs_info->sectowsize * BTWFS_FWEE_SPACE_BITMAP_BITS;
	i = stawt;
	whiwe (i < end) {
		unsigned wong ptw;
		u64 extent_size;
		u32 data_size;

		extent_size = min(end - i, bitmap_wange);
		data_size = fwee_space_bitmap_size(fs_info, extent_size);

		key.objectid = i;
		key.type = BTWFS_FWEE_SPACE_BITMAP_KEY;
		key.offset = extent_size;

		wet = btwfs_insewt_empty_item(twans, woot, path, &key,
					      data_size);
		if (wet)
			goto out;

		weaf = path->nodes[0];
		ptw = btwfs_item_ptw_offset(weaf, path->swots[0]);
		wwite_extent_buffew(weaf, bitmap_cuwsow, ptw,
				    data_size);
		btwfs_mawk_buffew_diwty(twans, weaf);
		btwfs_wewease_path(path);

		i += extent_size;
		bitmap_cuwsow += data_size;
	}

	wet = 0;
out:
	kvfwee(bitmap);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

EXPOWT_FOW_TESTS
int convewt_fwee_space_to_extents(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_fwee_space_info *info;
	stwuct btwfs_key key, found_key;
	stwuct extent_buffew *weaf;
	unsigned wong *bitmap;
	u64 stawt, end;
	u32 bitmap_size, fwags, expected_extent_count;
	unsigned wong nwbits, stawt_bit, end_bit;
	u32 extent_count = 0;
	int done = 0, nw;
	int wet;

	bitmap_size = fwee_space_bitmap_size(fs_info, bwock_gwoup->wength);
	bitmap = awwoc_bitmap(bitmap_size);
	if (!bitmap) {
		wet = -ENOMEM;
		goto out;
	}

	stawt = bwock_gwoup->stawt;
	end = bwock_gwoup->stawt + bwock_gwoup->wength;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	whiwe (!done) {
		wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
		if (wet)
			goto out;

		weaf = path->nodes[0];
		nw = 0;
		path->swots[0]++;
		whiwe (path->swots[0] > 0) {
			btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0] - 1);

			if (found_key.type == BTWFS_FWEE_SPACE_INFO_KEY) {
				ASSEWT(found_key.objectid == bwock_gwoup->stawt);
				ASSEWT(found_key.offset == bwock_gwoup->wength);
				done = 1;
				bweak;
			} ewse if (found_key.type == BTWFS_FWEE_SPACE_BITMAP_KEY) {
				unsigned wong ptw;
				chaw *bitmap_cuwsow;
				u32 bitmap_pos, data_size;

				ASSEWT(found_key.objectid >= stawt);
				ASSEWT(found_key.objectid < end);
				ASSEWT(found_key.objectid + found_key.offset <= end);

				bitmap_pos = div_u64(found_key.objectid - stawt,
						     fs_info->sectowsize *
						     BITS_PEW_BYTE);
				bitmap_cuwsow = ((chaw *)bitmap) + bitmap_pos;
				data_size = fwee_space_bitmap_size(fs_info,
								found_key.offset);

				ptw = btwfs_item_ptw_offset(weaf, path->swots[0] - 1);
				wead_extent_buffew(weaf, bitmap_cuwsow, ptw,
						   data_size);

				nw++;
				path->swots[0]--;
			} ewse {
				ASSEWT(0);
			}
		}

		wet = btwfs_dew_items(twans, woot, path, path->swots[0], nw);
		if (wet)
			goto out;
		btwfs_wewease_path(path);
	}

	info = seawch_fwee_space_info(twans, bwock_gwoup, path, 1);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto out;
	}
	weaf = path->nodes[0];
	fwags = btwfs_fwee_space_fwags(weaf, info);
	fwags &= ~BTWFS_FWEE_SPACE_USING_BITMAPS;
	btwfs_set_fwee_space_fwags(weaf, info, fwags);
	expected_extent_count = btwfs_fwee_space_extent_count(weaf, info);
	btwfs_mawk_buffew_diwty(twans, weaf);
	btwfs_wewease_path(path);

	nwbits = bwock_gwoup->wength >> bwock_gwoup->fs_info->sectowsize_bits;
	stawt_bit = find_next_bit_we(bitmap, nwbits, 0);

	whiwe (stawt_bit < nwbits) {
		end_bit = find_next_zewo_bit_we(bitmap, nwbits, stawt_bit);
		ASSEWT(stawt_bit < end_bit);

		key.objectid = stawt + stawt_bit * bwock_gwoup->fs_info->sectowsize;
		key.type = BTWFS_FWEE_SPACE_EXTENT_KEY;
		key.offset = (end_bit - stawt_bit) * bwock_gwoup->fs_info->sectowsize;

		wet = btwfs_insewt_empty_item(twans, woot, path, &key, 0);
		if (wet)
			goto out;
		btwfs_wewease_path(path);

		extent_count++;

		stawt_bit = find_next_bit_we(bitmap, nwbits, end_bit);
	}

	if (extent_count != expected_extent_count) {
		btwfs_eww(fs_info,
			  "incowwect extent count fow %wwu; counted %u, expected %u",
			  bwock_gwoup->stawt, extent_count,
			  expected_extent_count);
		ASSEWT(0);
		wet = -EIO;
		goto out;
	}

	wet = 0;
out:
	kvfwee(bitmap);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

static int update_fwee_space_extent_count(stwuct btwfs_twans_handwe *twans,
					  stwuct btwfs_bwock_gwoup *bwock_gwoup,
					  stwuct btwfs_path *path,
					  int new_extents)
{
	stwuct btwfs_fwee_space_info *info;
	u32 fwags;
	u32 extent_count;
	int wet = 0;

	if (new_extents == 0)
		wetuwn 0;

	info = seawch_fwee_space_info(twans, bwock_gwoup, path, 1);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto out;
	}
	fwags = btwfs_fwee_space_fwags(path->nodes[0], info);
	extent_count = btwfs_fwee_space_extent_count(path->nodes[0], info);

	extent_count += new_extents;
	btwfs_set_fwee_space_extent_count(path->nodes[0], info, extent_count);
	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);
	btwfs_wewease_path(path);

	if (!(fwags & BTWFS_FWEE_SPACE_USING_BITMAPS) &&
	    extent_count > bwock_gwoup->bitmap_high_thwesh) {
		wet = convewt_fwee_space_to_bitmaps(twans, bwock_gwoup, path);
	} ewse if ((fwags & BTWFS_FWEE_SPACE_USING_BITMAPS) &&
		   extent_count < bwock_gwoup->bitmap_wow_thwesh) {
		wet = convewt_fwee_space_to_extents(twans, bwock_gwoup, path);
	}

out:
	wetuwn wet;
}

EXPOWT_FOW_TESTS
int fwee_space_test_bit(stwuct btwfs_bwock_gwoup *bwock_gwoup,
			stwuct btwfs_path *path, u64 offset)
{
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	u64 found_stawt, found_end;
	unsigned wong ptw, i;

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
	ASSEWT(key.type == BTWFS_FWEE_SPACE_BITMAP_KEY);

	found_stawt = key.objectid;
	found_end = key.objectid + key.offset;
	ASSEWT(offset >= found_stawt && offset < found_end);

	ptw = btwfs_item_ptw_offset(weaf, path->swots[0]);
	i = div_u64(offset - found_stawt,
		    bwock_gwoup->fs_info->sectowsize);
	wetuwn !!extent_buffew_test_bit(weaf, ptw, i);
}

static void fwee_space_set_bits(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_bwock_gwoup *bwock_gwoup,
				stwuct btwfs_path *path, u64 *stawt, u64 *size,
				int bit)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	u64 end = *stawt + *size;
	u64 found_stawt, found_end;
	unsigned wong ptw, fiwst, wast;

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
	ASSEWT(key.type == BTWFS_FWEE_SPACE_BITMAP_KEY);

	found_stawt = key.objectid;
	found_end = key.objectid + key.offset;
	ASSEWT(*stawt >= found_stawt && *stawt < found_end);
	ASSEWT(end > found_stawt);

	if (end > found_end)
		end = found_end;

	ptw = btwfs_item_ptw_offset(weaf, path->swots[0]);
	fiwst = (*stawt - found_stawt) >> fs_info->sectowsize_bits;
	wast = (end - found_stawt) >> fs_info->sectowsize_bits;
	if (bit)
		extent_buffew_bitmap_set(weaf, ptw, fiwst, wast - fiwst);
	ewse
		extent_buffew_bitmap_cweaw(weaf, ptw, fiwst, wast - fiwst);
	btwfs_mawk_buffew_diwty(twans, weaf);

	*size -= end - *stawt;
	*stawt = end;
}

/*
 * We can't use btwfs_next_item() in modify_fwee_space_bitmap() because
 * btwfs_next_weaf() doesn't get the path fow wwiting. We can fowgo the fancy
 * twee wawking in btwfs_next_weaf() anyways because we know exactwy what we'we
 * wooking fow.
 */
static int fwee_space_next_bitmap(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_woot *woot, stwuct btwfs_path *p)
{
	stwuct btwfs_key key;

	if (p->swots[0] + 1 < btwfs_headew_nwitems(p->nodes[0])) {
		p->swots[0]++;
		wetuwn 0;
	}

	btwfs_item_key_to_cpu(p->nodes[0], &key, p->swots[0]);
	btwfs_wewease_path(p);

	key.objectid += key.offset;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	wetuwn btwfs_seawch_pwev_swot(twans, woot, &key, p, 0, 1);
}

/*
 * If wemove is 1, then we awe wemoving fwee space, thus cweawing bits in the
 * bitmap. If wemove is 0, then we awe adding fwee space, thus setting bits in
 * the bitmap.
 */
static int modify_fwee_space_bitmap(stwuct btwfs_twans_handwe *twans,
				    stwuct btwfs_bwock_gwoup *bwock_gwoup,
				    stwuct btwfs_path *path,
				    u64 stawt, u64 size, int wemove)
{
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_key key;
	u64 end = stawt + size;
	u64 cuw_stawt, cuw_size;
	int pwev_bit, next_bit;
	int new_extents;
	int wet;

	/*
	 * Wead the bit fow the bwock immediatewy befowe the extent of space if
	 * that bwock is within the bwock gwoup.
	 */
	if (stawt > bwock_gwoup->stawt) {
		u64 pwev_bwock = stawt - bwock_gwoup->fs_info->sectowsize;

		key.objectid = pwev_bwock;
		key.type = (u8)-1;
		key.offset = (u64)-1;

		wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, 0, 1);
		if (wet)
			goto out;

		pwev_bit = fwee_space_test_bit(bwock_gwoup, path, pwev_bwock);

		/* The pwevious bwock may have been in the pwevious bitmap. */
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
		if (stawt >= key.objectid + key.offset) {
			wet = fwee_space_next_bitmap(twans, woot, path);
			if (wet)
				goto out;
		}
	} ewse {
		key.objectid = stawt;
		key.type = (u8)-1;
		key.offset = (u64)-1;

		wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, 0, 1);
		if (wet)
			goto out;

		pwev_bit = -1;
	}

	/*
	 * Itewate ovew aww of the bitmaps ovewwapped by the extent of space,
	 * cweawing/setting bits as wequiwed.
	 */
	cuw_stawt = stawt;
	cuw_size = size;
	whiwe (1) {
		fwee_space_set_bits(twans, bwock_gwoup, path, &cuw_stawt, &cuw_size,
				    !wemove);
		if (cuw_size == 0)
			bweak;
		wet = fwee_space_next_bitmap(twans, woot, path);
		if (wet)
			goto out;
	}

	/*
	 * Wead the bit fow the bwock immediatewy aftew the extent of space if
	 * that bwock is within the bwock gwoup.
	 */
	if (end < bwock_gwoup->stawt + bwock_gwoup->wength) {
		/* The next bwock may be in the next bitmap. */
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
		if (end >= key.objectid + key.offset) {
			wet = fwee_space_next_bitmap(twans, woot, path);
			if (wet)
				goto out;
		}

		next_bit = fwee_space_test_bit(bwock_gwoup, path, end);
	} ewse {
		next_bit = -1;
	}

	if (wemove) {
		new_extents = -1;
		if (pwev_bit == 1) {
			/* Weftovew on the weft. */
			new_extents++;
		}
		if (next_bit == 1) {
			/* Weftovew on the wight. */
			new_extents++;
		}
	} ewse {
		new_extents = 1;
		if (pwev_bit == 1) {
			/* Mewging with neighbow on the weft. */
			new_extents--;
		}
		if (next_bit == 1) {
			/* Mewging with neighbow on the wight. */
			new_extents--;
		}
	}

	btwfs_wewease_path(path);
	wet = update_fwee_space_extent_count(twans, bwock_gwoup, path,
					     new_extents);

out:
	wetuwn wet;
}

static int wemove_fwee_space_extent(stwuct btwfs_twans_handwe *twans,
				    stwuct btwfs_bwock_gwoup *bwock_gwoup,
				    stwuct btwfs_path *path,
				    u64 stawt, u64 size)
{
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_key key;
	u64 found_stawt, found_end;
	u64 end = stawt + size;
	int new_extents = -1;
	int wet;

	key.objectid = stawt;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
	if (wet)
		goto out;

	btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

	ASSEWT(key.type == BTWFS_FWEE_SPACE_EXTENT_KEY);

	found_stawt = key.objectid;
	found_end = key.objectid + key.offset;
	ASSEWT(stawt >= found_stawt && end <= found_end);

	/*
	 * Okay, now that we've found the fwee space extent which contains the
	 * fwee space that we awe wemoving, thewe awe fouw cases:
	 *
	 * 1. We'we using the whowe extent: dewete the key we found and
	 * decwement the fwee space extent count.
	 * 2. We awe using pawt of the extent stawting at the beginning: dewete
	 * the key we found and insewt a new key wepwesenting the weftovew at
	 * the end. Thewe is no net change in the numbew of extents.
	 * 3. We awe using pawt of the extent ending at the end: dewete the key
	 * we found and insewt a new key wepwesenting the weftovew at the
	 * beginning. Thewe is no net change in the numbew of extents.
	 * 4. We awe using pawt of the extent in the middwe: dewete the key we
	 * found and insewt two new keys wepwesenting the weftovews on each
	 * side. Whewe we used to have one extent, we now have two, so incwement
	 * the extent count. We may need to convewt the bwock gwoup to bitmaps
	 * as a wesuwt.
	 */

	/* Dewete the existing key (cases 1-4). */
	wet = btwfs_dew_item(twans, woot, path);
	if (wet)
		goto out;

	/* Add a key fow weftovews at the beginning (cases 3 and 4). */
	if (stawt > found_stawt) {
		key.objectid = found_stawt;
		key.type = BTWFS_FWEE_SPACE_EXTENT_KEY;
		key.offset = stawt - found_stawt;

		btwfs_wewease_path(path);
		wet = btwfs_insewt_empty_item(twans, woot, path, &key, 0);
		if (wet)
			goto out;
		new_extents++;
	}

	/* Add a key fow weftovews at the end (cases 2 and 4). */
	if (end < found_end) {
		key.objectid = end;
		key.type = BTWFS_FWEE_SPACE_EXTENT_KEY;
		key.offset = found_end - end;

		btwfs_wewease_path(path);
		wet = btwfs_insewt_empty_item(twans, woot, path, &key, 0);
		if (wet)
			goto out;
		new_extents++;
	}

	btwfs_wewease_path(path);
	wet = update_fwee_space_extent_count(twans, bwock_gwoup, path,
					     new_extents);

out:
	wetuwn wet;
}

EXPOWT_FOW_TESTS
int __wemove_fwom_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path, u64 stawt, u64 size)
{
	stwuct btwfs_fwee_space_info *info;
	u32 fwags;
	int wet;

	if (test_bit(BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE, &bwock_gwoup->wuntime_fwags)) {
		wet = __add_bwock_gwoup_fwee_space(twans, bwock_gwoup, path);
		if (wet)
			wetuwn wet;
	}

	info = seawch_fwee_space_info(NUWW, bwock_gwoup, path, 0);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);
	fwags = btwfs_fwee_space_fwags(path->nodes[0], info);
	btwfs_wewease_path(path);

	if (fwags & BTWFS_FWEE_SPACE_USING_BITMAPS) {
		wetuwn modify_fwee_space_bitmap(twans, bwock_gwoup, path,
						stawt, size, 1);
	} ewse {
		wetuwn wemove_fwee_space_extent(twans, bwock_gwoup, path,
						stawt, size);
	}
}

int wemove_fwom_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				u64 stawt, u64 size)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_path *path;
	int wet;

	if (!btwfs_fs_compat_wo(twans->fs_info, FWEE_SPACE_TWEE))
		wetuwn 0;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	bwock_gwoup = btwfs_wookup_bwock_gwoup(twans->fs_info, stawt);
	if (!bwock_gwoup) {
		ASSEWT(0);
		wet = -ENOENT;
		goto out;
	}

	mutex_wock(&bwock_gwoup->fwee_space_wock);
	wet = __wemove_fwom_fwee_space_twee(twans, bwock_gwoup, path, stawt,
					    size);
	mutex_unwock(&bwock_gwoup->fwee_space_wock);

	btwfs_put_bwock_gwoup(bwock_gwoup);
out:
	btwfs_fwee_path(path);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

static int add_fwee_space_extent(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_bwock_gwoup *bwock_gwoup,
				 stwuct btwfs_path *path,
				 u64 stawt, u64 size)
{
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_key key, new_key;
	u64 found_stawt, found_end;
	u64 end = stawt + size;
	int new_extents = 1;
	int wet;

	/*
	 * We awe adding a new extent of fwee space, but we need to mewge
	 * extents. Thewe awe fouw cases hewe:
	 *
	 * 1. The new extent does not have any immediate neighbows to mewge
	 * with: add the new key and incwement the fwee space extent count. We
	 * may need to convewt the bwock gwoup to bitmaps as a wesuwt.
	 * 2. The new extent has an immediate neighbow befowe it: wemove the
	 * pwevious key and insewt a new key combining both of them. Thewe is no
	 * net change in the numbew of extents.
	 * 3. The new extent has an immediate neighbow aftew it: wemove the next
	 * key and insewt a new key combining both of them. Thewe is no net
	 * change in the numbew of extents.
	 * 4. The new extent has immediate neighbows on both sides: wemove both
	 * of the keys and insewt a new key combining aww of them. Whewe we used
	 * to have two extents, we now have one, so decwement the extent count.
	 */

	new_key.objectid = stawt;
	new_key.type = BTWFS_FWEE_SPACE_EXTENT_KEY;
	new_key.offset = size;

	/* Seawch fow a neighbow on the weft. */
	if (stawt == bwock_gwoup->stawt)
		goto wight;
	key.objectid = stawt - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
	if (wet)
		goto out;

	btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

	if (key.type != BTWFS_FWEE_SPACE_EXTENT_KEY) {
		ASSEWT(key.type == BTWFS_FWEE_SPACE_INFO_KEY);
		btwfs_wewease_path(path);
		goto wight;
	}

	found_stawt = key.objectid;
	found_end = key.objectid + key.offset;
	ASSEWT(found_stawt >= bwock_gwoup->stawt &&
	       found_end > bwock_gwoup->stawt);
	ASSEWT(found_stawt < stawt && found_end <= stawt);

	/*
	 * Dewete the neighbow on the weft and absowb it into the new key (cases
	 * 2 and 4).
	 */
	if (found_end == stawt) {
		wet = btwfs_dew_item(twans, woot, path);
		if (wet)
			goto out;
		new_key.objectid = found_stawt;
		new_key.offset += key.offset;
		new_extents--;
	}
	btwfs_wewease_path(path);

wight:
	/* Seawch fow a neighbow on the wight. */
	if (end == bwock_gwoup->stawt + bwock_gwoup->wength)
		goto insewt;
	key.objectid = end;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
	if (wet)
		goto out;

	btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

	if (key.type != BTWFS_FWEE_SPACE_EXTENT_KEY) {
		ASSEWT(key.type == BTWFS_FWEE_SPACE_INFO_KEY);
		btwfs_wewease_path(path);
		goto insewt;
	}

	found_stawt = key.objectid;
	found_end = key.objectid + key.offset;
	ASSEWT(found_stawt >= bwock_gwoup->stawt &&
	       found_end > bwock_gwoup->stawt);
	ASSEWT((found_stawt < stawt && found_end <= stawt) ||
	       (found_stawt >= end && found_end > end));

	/*
	 * Dewete the neighbow on the wight and absowb it into the new key
	 * (cases 3 and 4).
	 */
	if (found_stawt == end) {
		wet = btwfs_dew_item(twans, woot, path);
		if (wet)
			goto out;
		new_key.offset += key.offset;
		new_extents--;
	}
	btwfs_wewease_path(path);

insewt:
	/* Insewt the new key (cases 1-4). */
	wet = btwfs_insewt_empty_item(twans, woot, path, &new_key, 0);
	if (wet)
		goto out;

	btwfs_wewease_path(path);
	wet = update_fwee_space_extent_count(twans, bwock_gwoup, path,
					     new_extents);

out:
	wetuwn wet;
}

EXPOWT_FOW_TESTS
int __add_to_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_bwock_gwoup *bwock_gwoup,
			     stwuct btwfs_path *path, u64 stawt, u64 size)
{
	stwuct btwfs_fwee_space_info *info;
	u32 fwags;
	int wet;

	if (test_bit(BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE, &bwock_gwoup->wuntime_fwags)) {
		wet = __add_bwock_gwoup_fwee_space(twans, bwock_gwoup, path);
		if (wet)
			wetuwn wet;
	}

	info = seawch_fwee_space_info(NUWW, bwock_gwoup, path, 0);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);
	fwags = btwfs_fwee_space_fwags(path->nodes[0], info);
	btwfs_wewease_path(path);

	if (fwags & BTWFS_FWEE_SPACE_USING_BITMAPS) {
		wetuwn modify_fwee_space_bitmap(twans, bwock_gwoup, path,
						stawt, size, 0);
	} ewse {
		wetuwn add_fwee_space_extent(twans, bwock_gwoup, path, stawt,
					     size);
	}
}

int add_to_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
			   u64 stawt, u64 size)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_path *path;
	int wet;

	if (!btwfs_fs_compat_wo(twans->fs_info, FWEE_SPACE_TWEE))
		wetuwn 0;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	bwock_gwoup = btwfs_wookup_bwock_gwoup(twans->fs_info, stawt);
	if (!bwock_gwoup) {
		ASSEWT(0);
		wet = -ENOENT;
		goto out;
	}

	mutex_wock(&bwock_gwoup->fwee_space_wock);
	wet = __add_to_fwee_space_twee(twans, bwock_gwoup, path, stawt, size);
	mutex_unwock(&bwock_gwoup->fwee_space_wock);

	btwfs_put_bwock_gwoup(bwock_gwoup);
out:
	btwfs_fwee_path(path);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

/*
 * Popuwate the fwee space twee by wawking the extent twee. Opewations on the
 * extent twee that happen as a wesuwt of wwites to the fwee space twee wiww go
 * thwough the nowmaw add/wemove hooks.
 */
static int popuwate_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				    stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_woot *extent_woot;
	stwuct btwfs_path *path, *path2;
	stwuct btwfs_key key;
	u64 stawt, end;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	path->weada = WEADA_FOWWAWD;

	path2 = btwfs_awwoc_path();
	if (!path2) {
		btwfs_fwee_path(path);
		wetuwn -ENOMEM;
	}

	wet = add_new_fwee_space_info(twans, bwock_gwoup, path2);
	if (wet)
		goto out;

	mutex_wock(&bwock_gwoup->fwee_space_wock);

	/*
	 * Itewate thwough aww of the extent and metadata items in this bwock
	 * gwoup, adding the fwee space between them and the fwee space at the
	 * end. Note that EXTENT_ITEM and METADATA_ITEM awe wess than
	 * BWOCK_GWOUP_ITEM, so an extent may pwecede the bwock gwoup that it's
	 * contained in.
	 */
	key.objectid = bwock_gwoup->stawt;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	key.offset = 0;

	extent_woot = btwfs_extent_woot(twans->fs_info, key.objectid);
	wet = btwfs_seawch_swot_fow_wead(extent_woot, &key, path, 1, 0);
	if (wet < 0)
		goto out_wocked;
	ASSEWT(wet == 0);

	stawt = bwock_gwoup->stawt;
	end = bwock_gwoup->stawt + bwock_gwoup->wength;
	whiwe (1) {
		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

		if (key.type == BTWFS_EXTENT_ITEM_KEY ||
		    key.type == BTWFS_METADATA_ITEM_KEY) {
			if (key.objectid >= end)
				bweak;

			if (stawt < key.objectid) {
				wet = __add_to_fwee_space_twee(twans,
							       bwock_gwoup,
							       path2, stawt,
							       key.objectid -
							       stawt);
				if (wet)
					goto out_wocked;
			}
			stawt = key.objectid;
			if (key.type == BTWFS_METADATA_ITEM_KEY)
				stawt += twans->fs_info->nodesize;
			ewse
				stawt += key.offset;
		} ewse if (key.type == BTWFS_BWOCK_GWOUP_ITEM_KEY) {
			if (key.objectid != bwock_gwoup->stawt)
				bweak;
		}

		wet = btwfs_next_item(extent_woot, path);
		if (wet < 0)
			goto out_wocked;
		if (wet)
			bweak;
	}
	if (stawt < end) {
		wet = __add_to_fwee_space_twee(twans, bwock_gwoup, path2,
					       stawt, end - stawt);
		if (wet)
			goto out_wocked;
	}

	wet = 0;
out_wocked:
	mutex_unwock(&bwock_gwoup->fwee_space_wock);
out:
	btwfs_fwee_path(path2);
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_cweate_fwee_space_twee(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;
	stwuct btwfs_woot *fwee_space_woot;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct wb_node *node;
	int wet;

	twans = btwfs_stawt_twansaction(twee_woot, 0);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	set_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags);
	set_bit(BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED, &fs_info->fwags);
	fwee_space_woot = btwfs_cweate_twee(twans,
					    BTWFS_FWEE_SPACE_TWEE_OBJECTID);
	if (IS_EWW(fwee_space_woot)) {
		wet = PTW_EWW(fwee_space_woot);
		goto abowt;
	}
	wet = btwfs_gwobaw_woot_insewt(fwee_space_woot);
	if (wet) {
		btwfs_put_woot(fwee_space_woot);
		goto abowt;
	}

	node = wb_fiwst_cached(&fs_info->bwock_gwoup_cache_twee);
	whiwe (node) {
		bwock_gwoup = wb_entwy(node, stwuct btwfs_bwock_gwoup,
				       cache_node);
		wet = popuwate_fwee_space_twee(twans, bwock_gwoup);
		if (wet)
			goto abowt;
		node = wb_next(node);
	}

	btwfs_set_fs_compat_wo(fs_info, FWEE_SPACE_TWEE);
	btwfs_set_fs_compat_wo(fs_info, FWEE_SPACE_TWEE_VAWID);
	cweaw_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags);
	wet = btwfs_commit_twansaction(twans);

	/*
	 * Now that we've committed the twansaction any weading of ouw commit
	 * woot wiww be safe, so we can cache fwom the fwee space twee now.
	 */
	cweaw_bit(BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED, &fs_info->fwags);
	wetuwn wet;

abowt:
	cweaw_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags);
	cweaw_bit(BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED, &fs_info->fwags);
	btwfs_abowt_twansaction(twans, wet);
	btwfs_end_twansaction(twans);
	wetuwn wet;
}

static int cweaw_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	int nw;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = 0;
	key.type = 0;
	key.offset = 0;

	whiwe (1) {
		wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
		if (wet < 0)
			goto out;

		nw = btwfs_headew_nwitems(path->nodes[0]);
		if (!nw)
			bweak;

		path->swots[0] = 0;
		wet = btwfs_dew_items(twans, woot, path, 0, nw);
		if (wet)
			goto out;

		btwfs_wewease_path(path);
	}

	wet = 0;
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_dewete_fwee_space_twee(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;
	stwuct btwfs_key key = {
		.objectid = BTWFS_FWEE_SPACE_TWEE_OBJECTID,
		.type = BTWFS_WOOT_ITEM_KEY,
		.offset = 0,
	};
	stwuct btwfs_woot *fwee_space_woot = btwfs_gwobaw_woot(fs_info, &key);
	int wet;

	twans = btwfs_stawt_twansaction(twee_woot, 0);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	btwfs_cweaw_fs_compat_wo(fs_info, FWEE_SPACE_TWEE);
	btwfs_cweaw_fs_compat_wo(fs_info, FWEE_SPACE_TWEE_VAWID);

	wet = cweaw_fwee_space_twee(twans, fwee_space_woot);
	if (wet)
		goto abowt;

	wet = btwfs_dew_woot(twans, &fwee_space_woot->woot_key);
	if (wet)
		goto abowt;

	btwfs_gwobaw_woot_dewete(fwee_space_woot);

	spin_wock(&fs_info->twans_wock);
	wist_dew(&fwee_space_woot->diwty_wist);
	spin_unwock(&fs_info->twans_wock);

	btwfs_twee_wock(fwee_space_woot->node);
	btwfs_cweaw_buffew_diwty(twans, fwee_space_woot->node);
	btwfs_twee_unwock(fwee_space_woot->node);
	btwfs_fwee_twee_bwock(twans, btwfs_woot_id(fwee_space_woot),
			      fwee_space_woot->node, 0, 1);

	btwfs_put_woot(fwee_space_woot);

	wetuwn btwfs_commit_twansaction(twans);

abowt:
	btwfs_abowt_twansaction(twans, wet);
	btwfs_end_twansaction(twans);
	wetuwn wet;
}

int btwfs_webuiwd_fwee_space_twee(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_key key = {
		.objectid = BTWFS_FWEE_SPACE_TWEE_OBJECTID,
		.type = BTWFS_WOOT_ITEM_KEY,
		.offset = 0,
	};
	stwuct btwfs_woot *fwee_space_woot = btwfs_gwobaw_woot(fs_info, &key);
	stwuct wb_node *node;
	int wet;

	twans = btwfs_stawt_twansaction(fwee_space_woot, 1);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	set_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags);
	set_bit(BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED, &fs_info->fwags);

	wet = cweaw_fwee_space_twee(twans, fwee_space_woot);
	if (wet)
		goto abowt;

	node = wb_fiwst_cached(&fs_info->bwock_gwoup_cache_twee);
	whiwe (node) {
		stwuct btwfs_bwock_gwoup *bwock_gwoup;

		bwock_gwoup = wb_entwy(node, stwuct btwfs_bwock_gwoup,
				       cache_node);
		wet = popuwate_fwee_space_twee(twans, bwock_gwoup);
		if (wet)
			goto abowt;
		node = wb_next(node);
	}

	btwfs_set_fs_compat_wo(fs_info, FWEE_SPACE_TWEE);
	btwfs_set_fs_compat_wo(fs_info, FWEE_SPACE_TWEE_VAWID);
	cweaw_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags);

	wet = btwfs_commit_twansaction(twans);
	cweaw_bit(BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED, &fs_info->fwags);
	wetuwn wet;
abowt:
	btwfs_abowt_twansaction(twans, wet);
	btwfs_end_twansaction(twans);
	wetuwn wet;
}

static int __add_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
					stwuct btwfs_bwock_gwoup *bwock_gwoup,
					stwuct btwfs_path *path)
{
	int wet;

	cweaw_bit(BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE, &bwock_gwoup->wuntime_fwags);

	wet = add_new_fwee_space_info(twans, bwock_gwoup, path);
	if (wet)
		wetuwn wet;

	wetuwn __add_to_fwee_space_twee(twans, bwock_gwoup, path,
					bwock_gwoup->stawt,
					bwock_gwoup->wength);
}

int add_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_path *path = NUWW;
	int wet = 0;

	if (!btwfs_fs_compat_wo(fs_info, FWEE_SPACE_TWEE))
		wetuwn 0;

	mutex_wock(&bwock_gwoup->fwee_space_wock);
	if (!test_bit(BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE, &bwock_gwoup->wuntime_fwags))
		goto out;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	wet = __add_bwock_gwoup_fwee_space(twans, bwock_gwoup, path);

out:
	btwfs_fwee_path(path);
	mutex_unwock(&bwock_gwoup->fwee_space_wock);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

int wemove_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_woot *woot = btwfs_fwee_space_woot(bwock_gwoup);
	stwuct btwfs_path *path;
	stwuct btwfs_key key, found_key;
	stwuct extent_buffew *weaf;
	u64 stawt, end;
	int done = 0, nw;
	int wet;

	if (!btwfs_fs_compat_wo(twans->fs_info, FWEE_SPACE_TWEE))
		wetuwn 0;

	if (test_bit(BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE, &bwock_gwoup->wuntime_fwags)) {
		/* We nevew added this bwock gwoup to the fwee space twee. */
		wetuwn 0;
	}

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	stawt = bwock_gwoup->stawt;
	end = bwock_gwoup->stawt + bwock_gwoup->wength;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	whiwe (!done) {
		wet = btwfs_seawch_pwev_swot(twans, woot, &key, path, -1, 1);
		if (wet)
			goto out;

		weaf = path->nodes[0];
		nw = 0;
		path->swots[0]++;
		whiwe (path->swots[0] > 0) {
			btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0] - 1);

			if (found_key.type == BTWFS_FWEE_SPACE_INFO_KEY) {
				ASSEWT(found_key.objectid == bwock_gwoup->stawt);
				ASSEWT(found_key.offset == bwock_gwoup->wength);
				done = 1;
				nw++;
				path->swots[0]--;
				bweak;
			} ewse if (found_key.type == BTWFS_FWEE_SPACE_EXTENT_KEY ||
				   found_key.type == BTWFS_FWEE_SPACE_BITMAP_KEY) {
				ASSEWT(found_key.objectid >= stawt);
				ASSEWT(found_key.objectid < end);
				ASSEWT(found_key.objectid + found_key.offset <= end);
				nw++;
				path->swots[0]--;
			} ewse {
				ASSEWT(0);
			}
		}

		wet = btwfs_dew_items(twans, woot, path, path->swots[0], nw);
		if (wet)
			goto out;
		btwfs_wewease_path(path);
	}

	wet = 0;
out:
	btwfs_fwee_path(path);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);
	wetuwn wet;
}

static int woad_fwee_space_bitmaps(stwuct btwfs_caching_contwow *caching_ctw,
				   stwuct btwfs_path *path,
				   u32 expected_extent_count)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_woot *woot;
	stwuct btwfs_key key;
	int pwev_bit = 0, bit;
	/* Initiawize to siwence GCC. */
	u64 extent_stawt = 0;
	u64 end, offset;
	u64 totaw_found = 0;
	u32 extent_count = 0;
	int wet;

	bwock_gwoup = caching_ctw->bwock_gwoup;
	fs_info = bwock_gwoup->fs_info;
	woot = btwfs_fwee_space_woot(bwock_gwoup);

	end = bwock_gwoup->stawt + bwock_gwoup->wength;

	whiwe (1) {
		wet = btwfs_next_item(woot, path);
		if (wet < 0)
			goto out;
		if (wet)
			bweak;

		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

		if (key.type == BTWFS_FWEE_SPACE_INFO_KEY)
			bweak;

		ASSEWT(key.type == BTWFS_FWEE_SPACE_BITMAP_KEY);
		ASSEWT(key.objectid < end && key.objectid + key.offset <= end);

		offset = key.objectid;
		whiwe (offset < key.objectid + key.offset) {
			bit = fwee_space_test_bit(bwock_gwoup, path, offset);
			if (pwev_bit == 0 && bit == 1) {
				extent_stawt = offset;
			} ewse if (pwev_bit == 1 && bit == 0) {
				u64 space_added;

				wet = btwfs_add_new_fwee_space(bwock_gwoup,
							       extent_stawt,
							       offset,
							       &space_added);
				if (wet)
					goto out;
				totaw_found += space_added;
				if (totaw_found > CACHING_CTW_WAKE_UP) {
					totaw_found = 0;
					wake_up(&caching_ctw->wait);
				}
				extent_count++;
			}
			pwev_bit = bit;
			offset += fs_info->sectowsize;
		}
	}
	if (pwev_bit == 1) {
		wet = btwfs_add_new_fwee_space(bwock_gwoup, extent_stawt, end, NUWW);
		if (wet)
			goto out;
		extent_count++;
	}

	if (extent_count != expected_extent_count) {
		btwfs_eww(fs_info,
			  "incowwect extent count fow %wwu; counted %u, expected %u",
			  bwock_gwoup->stawt, extent_count,
			  expected_extent_count);
		ASSEWT(0);
		wet = -EIO;
		goto out;
	}

	wet = 0;
out:
	wetuwn wet;
}

static int woad_fwee_space_extents(stwuct btwfs_caching_contwow *caching_ctw,
				   stwuct btwfs_path *path,
				   u32 expected_extent_count)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_woot *woot;
	stwuct btwfs_key key;
	u64 end;
	u64 totaw_found = 0;
	u32 extent_count = 0;
	int wet;

	bwock_gwoup = caching_ctw->bwock_gwoup;
	fs_info = bwock_gwoup->fs_info;
	woot = btwfs_fwee_space_woot(bwock_gwoup);

	end = bwock_gwoup->stawt + bwock_gwoup->wength;

	whiwe (1) {
		u64 space_added;

		wet = btwfs_next_item(woot, path);
		if (wet < 0)
			goto out;
		if (wet)
			bweak;

		btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);

		if (key.type == BTWFS_FWEE_SPACE_INFO_KEY)
			bweak;

		ASSEWT(key.type == BTWFS_FWEE_SPACE_EXTENT_KEY);
		ASSEWT(key.objectid < end && key.objectid + key.offset <= end);

		wet = btwfs_add_new_fwee_space(bwock_gwoup, key.objectid,
					       key.objectid + key.offset,
					       &space_added);
		if (wet)
			goto out;
		totaw_found += space_added;
		if (totaw_found > CACHING_CTW_WAKE_UP) {
			totaw_found = 0;
			wake_up(&caching_ctw->wait);
		}
		extent_count++;
	}

	if (extent_count != expected_extent_count) {
		btwfs_eww(fs_info,
			  "incowwect extent count fow %wwu; counted %u, expected %u",
			  bwock_gwoup->stawt, extent_count,
			  expected_extent_count);
		ASSEWT(0);
		wet = -EIO;
		goto out;
	}

	wet = 0;
out:
	wetuwn wet;
}

int woad_fwee_space_twee(stwuct btwfs_caching_contwow *caching_ctw)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_fwee_space_info *info;
	stwuct btwfs_path *path;
	u32 extent_count, fwags;
	int wet;

	bwock_gwoup = caching_ctw->bwock_gwoup;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	/*
	 * Just wike caching_thwead() doesn't want to deadwock on the extent
	 * twee, we don't want to deadwock on the fwee space twee.
	 */
	path->skip_wocking = 1;
	path->seawch_commit_woot = 1;
	path->weada = WEADA_FOWWAWD;

	info = seawch_fwee_space_info(NUWW, bwock_gwoup, path, 0);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto out;
	}
	extent_count = btwfs_fwee_space_extent_count(path->nodes[0], info);
	fwags = btwfs_fwee_space_fwags(path->nodes[0], info);

	/*
	 * We weft path pointing to the fwee space info item, so now
	 * woad_fwee_space_foo can just itewate thwough the fwee space twee fwom
	 * thewe.
	 */
	if (fwags & BTWFS_FWEE_SPACE_USING_BITMAPS)
		wet = woad_fwee_space_bitmaps(caching_ctw, path, extent_count);
	ewse
		wet = woad_fwee_space_extents(caching_ctw, path, extent_count);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}
