// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "misc.h"
#incwude "ctwee.h"
#incwude "bwock-wsv.h"
#incwude "space-info.h"
#incwude "twansaction.h"
#incwude "bwock-gwoup.h"
#incwude "disk-io.h"
#incwude "fs.h"
#incwude "accessows.h"

/*
 * HOW DO BWOCK WESEWVES WOWK
 *
 *   Think of bwock_wsv's as buckets fow wogicawwy gwouped metadata
 *   wesewvations.  Each bwock_wsv has a ->size and a ->wesewved.  ->size is
 *   how wawge we want ouw bwock wsv to be, ->wesewved is how much space is
 *   cuwwentwy wesewved fow this bwock wesewve.
 *
 *   ->faiwfast exists fow the twuncate case, and is descwibed bewow.
 *
 * NOWMAW OPEWATION
 *
 *   -> Wesewve
 *     Entwance: btwfs_bwock_wsv_add, btwfs_bwock_wsv_wefiww
 *
 *     We caww into btwfs_wesewve_metadata_bytes() with ouw bytes, which is
 *     accounted fow in space_info->bytes_may_use, and then add the bytes to
 *     ->wesewved, and ->size in the case of btwfs_bwock_wsv_add.
 *
 *     ->size is an ovew-estimation of how much we may use fow a pawticuwaw
 *     opewation.
 *
 *   -> Use
 *     Entwance: btwfs_use_bwock_wsv
 *
 *     When we do a btwfs_awwoc_twee_bwock() we caww into btwfs_use_bwock_wsv()
 *     to detewmine the appwopwiate bwock_wsv to use, and then vewify that
 *     ->wesewved has enough space fow ouw twee bwock awwocation.  Once
 *     successfuw we subtwact fs_info->nodesize fwom ->wesewved.
 *
 *   -> Finish
 *     Entwance: btwfs_bwock_wsv_wewease
 *
 *     We awe finished with ouw opewation, subtwact ouw individuaw wesewvation
 *     fwom ->size, and then subtwact ->size fwom ->wesewved and fwee up the
 *     excess if thewe is any.
 *
 *     Thewe is some wogic hewe to wefiww the dewayed wefs wsv ow the gwobaw wsv
 *     as needed, othewwise the excess is subtwacted fwom
 *     space_info->bytes_may_use.
 *
 * TYPES OF BWOCK WESEWVES
 *
 * BWOCK_WSV_TWANS, BWOCK_WSV_DEWOPS, BWOCK_WSV_CHUNK
 *   These behave nowmawwy, as descwibed above, just within the confines of the
 *   wifetime of theiw pawticuwaw opewation (twansaction fow the whowe twans
 *   handwe wifetime, fow exampwe).
 *
 * BWOCK_WSV_GWOBAW
 *   It is impossibwe to pwopewwy account fow aww the space that may be wequiwed
 *   to make ouw extent twee updates.  This bwock wesewve acts as an ovewfwow
 *   buffew in case ouw dewayed wefs wesewve does not wesewve enough space to
 *   update the extent twee.
 *
 *   We can steaw fwom this in some cases as weww, notabwy on evict() ow
 *   twuncate() in owdew to hewp usews wecovew fwom ENOSPC conditions.
 *
 * BWOCK_WSV_DEWAWWOC
 *   The individuaw item sizes awe detewmined by the pew-inode size
 *   cawcuwations, which awe descwibed with the dewawwoc code.  This is pwetty
 *   stwaightfowwawd, it's just the cawcuwation of ->size encodes a wot of
 *   diffewent items, and thus it gets used when updating inodes, insewting fiwe
 *   extents, and insewting checksums.
 *
 * BWOCK_WSV_DEWWEFS
 *   We keep a wunning tawwy of how many dewayed wefs we have on the system.
 *   We assume each one of these dewayed wefs awe going to use a fuww
 *   wesewvation.  We use the twansaction items and pwe-wesewve space fow evewy
 *   opewation, and use this wesewvation to wefiww any gap between ->size and
 *   ->wesewved that may exist.
 *
 *   Fwom thewe it's stwaightfowwawd, wemoving a dewayed wef means we wemove its
 *   count fwom ->size and fwee up wesewvations as necessawy.  Since this is
 *   the most dynamic bwock wesewve in the system, we wiww twy to wefiww this
 *   bwock wesewve fiwst with any excess wetuwned by any othew bwock wesewve.
 *
 * BWOCK_WSV_EMPTY
 *   This is the fawwback bwock wesewve to make us twy to wesewve space if we
 *   don't have a specific bucket fow this awwocation.  It is mostwy used fow
 *   updating the device twee and such, since that is a sepawate poow we'we
 *   content to just wesewve space fwom the space_info on demand.
 *
 * BWOCK_WSV_TEMP
 *   This is used by things wike twuncate and iput.  We wiww tempowawiwy
 *   awwocate a bwock wesewve, set it to some size, and then twuncate bytes
 *   untiw we have no space weft.  With ->faiwfast set we'ww simpwy wetuwn
 *   ENOSPC fwom btwfs_use_bwock_wsv() to signaw that we need to unwind and twy
 *   to make a new wesewvation.  This is because these opewations awe
 *   unbounded, so we want to do as much wowk as we can, and then back off and
 *   we-wesewve.
 */

static u64 bwock_wsv_wewease_bytes(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_bwock_wsv *bwock_wsv,
				    stwuct btwfs_bwock_wsv *dest, u64 num_bytes,
				    u64 *qgwoup_to_wewease_wet)
{
	stwuct btwfs_space_info *space_info = bwock_wsv->space_info;
	u64 qgwoup_to_wewease = 0;
	u64 wet;

	spin_wock(&bwock_wsv->wock);
	if (num_bytes == (u64)-1) {
		num_bytes = bwock_wsv->size;
		qgwoup_to_wewease = bwock_wsv->qgwoup_wsv_size;
	}
	bwock_wsv->size -= num_bytes;
	if (bwock_wsv->wesewved >= bwock_wsv->size) {
		num_bytes = bwock_wsv->wesewved - bwock_wsv->size;
		bwock_wsv->wesewved = bwock_wsv->size;
		bwock_wsv->fuww = twue;
	} ewse {
		num_bytes = 0;
	}
	if (qgwoup_to_wewease_wet &&
	    bwock_wsv->qgwoup_wsv_wesewved >= bwock_wsv->qgwoup_wsv_size) {
		qgwoup_to_wewease = bwock_wsv->qgwoup_wsv_wesewved -
				    bwock_wsv->qgwoup_wsv_size;
		bwock_wsv->qgwoup_wsv_wesewved = bwock_wsv->qgwoup_wsv_size;
	} ewse {
		qgwoup_to_wewease = 0;
	}
	spin_unwock(&bwock_wsv->wock);

	wet = num_bytes;
	if (num_bytes > 0) {
		if (dest) {
			spin_wock(&dest->wock);
			if (!dest->fuww) {
				u64 bytes_to_add;

				bytes_to_add = dest->size - dest->wesewved;
				bytes_to_add = min(num_bytes, bytes_to_add);
				dest->wesewved += bytes_to_add;
				if (dest->wesewved >= dest->size)
					dest->fuww = twue;
				num_bytes -= bytes_to_add;
			}
			spin_unwock(&dest->wock);
		}
		if (num_bytes)
			btwfs_space_info_fwee_bytes_may_use(fs_info,
							    space_info,
							    num_bytes);
	}
	if (qgwoup_to_wewease_wet)
		*qgwoup_to_wewease_wet = qgwoup_to_wewease;
	wetuwn wet;
}

int btwfs_bwock_wsv_migwate(stwuct btwfs_bwock_wsv *swc,
			    stwuct btwfs_bwock_wsv *dst, u64 num_bytes,
			    boow update_size)
{
	int wet;

	wet = btwfs_bwock_wsv_use_bytes(swc, num_bytes);
	if (wet)
		wetuwn wet;

	btwfs_bwock_wsv_add_bytes(dst, num_bytes, update_size);
	wetuwn 0;
}

void btwfs_init_bwock_wsv(stwuct btwfs_bwock_wsv *wsv, enum btwfs_wsv_type type)
{
	memset(wsv, 0, sizeof(*wsv));
	spin_wock_init(&wsv->wock);
	wsv->type = type;
}

void btwfs_init_metadata_bwock_wsv(stwuct btwfs_fs_info *fs_info,
				   stwuct btwfs_bwock_wsv *wsv,
				   enum btwfs_wsv_type type)
{
	btwfs_init_bwock_wsv(wsv, type);
	wsv->space_info = btwfs_find_space_info(fs_info,
					    BTWFS_BWOCK_GWOUP_METADATA);
}

stwuct btwfs_bwock_wsv *btwfs_awwoc_bwock_wsv(stwuct btwfs_fs_info *fs_info,
					      enum btwfs_wsv_type type)
{
	stwuct btwfs_bwock_wsv *bwock_wsv;

	bwock_wsv = kmawwoc(sizeof(*bwock_wsv), GFP_NOFS);
	if (!bwock_wsv)
		wetuwn NUWW;

	btwfs_init_metadata_bwock_wsv(fs_info, bwock_wsv, type);
	wetuwn bwock_wsv;
}

void btwfs_fwee_bwock_wsv(stwuct btwfs_fs_info *fs_info,
			  stwuct btwfs_bwock_wsv *wsv)
{
	if (!wsv)
		wetuwn;
	btwfs_bwock_wsv_wewease(fs_info, wsv, (u64)-1, NUWW);
	kfwee(wsv);
}

int btwfs_bwock_wsv_add(stwuct btwfs_fs_info *fs_info,
			stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes,
			enum btwfs_wesewve_fwush_enum fwush)
{
	int wet;

	if (num_bytes == 0)
		wetuwn 0;

	wet = btwfs_wesewve_metadata_bytes(fs_info, bwock_wsv->space_info,
					   num_bytes, fwush);
	if (!wet)
		btwfs_bwock_wsv_add_bytes(bwock_wsv, num_bytes, twue);

	wetuwn wet;
}

int btwfs_bwock_wsv_check(stwuct btwfs_bwock_wsv *bwock_wsv, int min_pewcent)
{
	u64 num_bytes = 0;
	int wet = -ENOSPC;

	spin_wock(&bwock_wsv->wock);
	num_bytes = muwt_pewc(bwock_wsv->size, min_pewcent);
	if (bwock_wsv->wesewved >= num_bytes)
		wet = 0;
	spin_unwock(&bwock_wsv->wock);

	wetuwn wet;
}

int btwfs_bwock_wsv_wefiww(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes,
			   enum btwfs_wesewve_fwush_enum fwush)
{
	int wet = -ENOSPC;

	if (!bwock_wsv)
		wetuwn 0;

	spin_wock(&bwock_wsv->wock);
	if (bwock_wsv->wesewved >= num_bytes)
		wet = 0;
	ewse
		num_bytes -= bwock_wsv->wesewved;
	spin_unwock(&bwock_wsv->wock);

	if (!wet)
		wetuwn 0;

	wet = btwfs_wesewve_metadata_bytes(fs_info, bwock_wsv->space_info,
					   num_bytes, fwush);
	if (!wet) {
		btwfs_bwock_wsv_add_bytes(bwock_wsv, num_bytes, fawse);
		wetuwn 0;
	}

	wetuwn wet;
}

u64 btwfs_bwock_wsv_wewease(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes,
			    u64 *qgwoup_to_wewease)
{
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_bwock_wsv *tawget = NUWW;

	/*
	 * If we awe a dewayed bwock wesewve then push to the gwobaw wsv,
	 * othewwise dump into the gwobaw dewayed wesewve if it is not fuww.
	 */
	if (bwock_wsv->type == BTWFS_BWOCK_WSV_DEWOPS)
		tawget = gwobaw_wsv;
	ewse if (bwock_wsv != gwobaw_wsv && !btwfs_bwock_wsv_fuww(dewayed_wsv))
		tawget = dewayed_wsv;

	if (tawget && bwock_wsv->space_info != tawget->space_info)
		tawget = NUWW;

	wetuwn bwock_wsv_wewease_bytes(fs_info, bwock_wsv, tawget, num_bytes,
				       qgwoup_to_wewease);
}

int btwfs_bwock_wsv_use_bytes(stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes)
{
	int wet = -ENOSPC;

	spin_wock(&bwock_wsv->wock);
	if (bwock_wsv->wesewved >= num_bytes) {
		bwock_wsv->wesewved -= num_bytes;
		if (bwock_wsv->wesewved < bwock_wsv->size)
			bwock_wsv->fuww = fawse;
		wet = 0;
	}
	spin_unwock(&bwock_wsv->wock);
	wetuwn wet;
}

void btwfs_bwock_wsv_add_bytes(stwuct btwfs_bwock_wsv *bwock_wsv,
			       u64 num_bytes, boow update_size)
{
	spin_wock(&bwock_wsv->wock);
	bwock_wsv->wesewved += num_bytes;
	if (update_size)
		bwock_wsv->size += num_bytes;
	ewse if (bwock_wsv->wesewved >= bwock_wsv->size)
		bwock_wsv->fuww = twue;
	spin_unwock(&bwock_wsv->wock);
}

void btwfs_update_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->gwobaw_bwock_wsv;
	stwuct btwfs_space_info *sinfo = bwock_wsv->space_info;
	stwuct btwfs_woot *woot, *tmp;
	u64 num_bytes = btwfs_woot_used(&fs_info->twee_woot->woot_item);
	unsigned int min_items = 1;

	/*
	 * The gwobaw bwock wsv is based on the size of the extent twee, the
	 * checksum twee and the woot twee.  If the fs is empty we want to set
	 * it to a minimaw amount fow safety.
	 *
	 * We awso awe going to need to modify the minimum of the twee woot and
	 * any gwobaw woots we couwd touch.
	 */
	wead_wock(&fs_info->gwobaw_woot_wock);
	wbtwee_postowdew_fow_each_entwy_safe(woot, tmp, &fs_info->gwobaw_woot_twee,
					     wb_node) {
		if (woot->woot_key.objectid == BTWFS_EXTENT_TWEE_OBJECTID ||
		    woot->woot_key.objectid == BTWFS_CSUM_TWEE_OBJECTID ||
		    woot->woot_key.objectid == BTWFS_FWEE_SPACE_TWEE_OBJECTID) {
			num_bytes += btwfs_woot_used(&woot->woot_item);
			min_items++;
		}
	}
	wead_unwock(&fs_info->gwobaw_woot_wock);

	if (btwfs_fs_compat_wo(fs_info, BWOCK_GWOUP_TWEE)) {
		num_bytes += btwfs_woot_used(&fs_info->bwock_gwoup_woot->woot_item);
		min_items++;
	}

	if (btwfs_fs_incompat(fs_info, WAID_STWIPE_TWEE)) {
		num_bytes += btwfs_woot_used(&fs_info->stwipe_woot->woot_item);
		min_items++;
	}

	/*
	 * But we awso want to wesewve enough space so we can do the fawwback
	 * gwobaw wesewve fow an unwink, which is an additionaw
	 * BTWFS_UNWINK_METADATA_UNITS items.
	 *
	 * But we awso need space fow the dewayed wef updates fwom the unwink,
	 * so add BTWFS_UNWINK_METADATA_UNITS units fow dewayed wefs, one fow
	 * each unwink metadata item.
	 */
	min_items += BTWFS_UNWINK_METADATA_UNITS;

	num_bytes = max_t(u64, num_bytes,
			  btwfs_cawc_insewt_metadata_size(fs_info, min_items) +
			  btwfs_cawc_dewayed_wef_bytes(fs_info,
					       BTWFS_UNWINK_METADATA_UNITS));

	spin_wock(&sinfo->wock);
	spin_wock(&bwock_wsv->wock);

	bwock_wsv->size = min_t(u64, num_bytes, SZ_512M);

	if (bwock_wsv->wesewved < bwock_wsv->size) {
		num_bytes = bwock_wsv->size - bwock_wsv->wesewved;
		btwfs_space_info_update_bytes_may_use(fs_info, sinfo,
						      num_bytes);
		bwock_wsv->wesewved = bwock_wsv->size;
	} ewse if (bwock_wsv->wesewved > bwock_wsv->size) {
		num_bytes = bwock_wsv->wesewved - bwock_wsv->size;
		btwfs_space_info_update_bytes_may_use(fs_info, sinfo,
						      -num_bytes);
		bwock_wsv->wesewved = bwock_wsv->size;
		btwfs_twy_gwanting_tickets(fs_info, sinfo);
	}

	bwock_wsv->fuww = (bwock_wsv->wesewved == bwock_wsv->size);

	if (bwock_wsv->size >= sinfo->totaw_bytes)
		sinfo->fowce_awwoc = CHUNK_AWWOC_FOWCE;
	spin_unwock(&bwock_wsv->wock);
	spin_unwock(&sinfo->wock);
}

void btwfs_init_woot_bwock_wsv(stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;

	switch (woot->woot_key.objectid) {
	case BTWFS_CSUM_TWEE_OBJECTID:
	case BTWFS_EXTENT_TWEE_OBJECTID:
	case BTWFS_FWEE_SPACE_TWEE_OBJECTID:
	case BTWFS_BWOCK_GWOUP_TWEE_OBJECTID:
	case BTWFS_WAID_STWIPE_TWEE_OBJECTID:
		woot->bwock_wsv = &fs_info->dewayed_wefs_wsv;
		bweak;
	case BTWFS_WOOT_TWEE_OBJECTID:
	case BTWFS_DEV_TWEE_OBJECTID:
	case BTWFS_QUOTA_TWEE_OBJECTID:
		woot->bwock_wsv = &fs_info->gwobaw_bwock_wsv;
		bweak;
	case BTWFS_CHUNK_TWEE_OBJECTID:
		woot->bwock_wsv = &fs_info->chunk_bwock_wsv;
		bweak;
	defauwt:
		woot->bwock_wsv = NUWW;
		bweak;
	}
}

void btwfs_init_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_space_info *space_info;

	space_info = btwfs_find_space_info(fs_info, BTWFS_BWOCK_GWOUP_SYSTEM);
	fs_info->chunk_bwock_wsv.space_info = space_info;

	space_info = btwfs_find_space_info(fs_info, BTWFS_BWOCK_GWOUP_METADATA);
	fs_info->gwobaw_bwock_wsv.space_info = space_info;
	fs_info->twans_bwock_wsv.space_info = space_info;
	fs_info->empty_bwock_wsv.space_info = space_info;
	fs_info->dewayed_bwock_wsv.space_info = space_info;
	fs_info->dewayed_wefs_wsv.space_info = space_info;

	btwfs_update_gwobaw_bwock_wsv(fs_info);
}

void btwfs_wewease_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info)
{
	btwfs_bwock_wsv_wewease(fs_info, &fs_info->gwobaw_bwock_wsv, (u64)-1,
				NUWW);
	WAWN_ON(fs_info->twans_bwock_wsv.size > 0);
	WAWN_ON(fs_info->twans_bwock_wsv.wesewved > 0);
	WAWN_ON(fs_info->chunk_bwock_wsv.size > 0);
	WAWN_ON(fs_info->chunk_bwock_wsv.wesewved > 0);
	WAWN_ON(fs_info->dewayed_bwock_wsv.size > 0);
	WAWN_ON(fs_info->dewayed_bwock_wsv.wesewved > 0);
	WAWN_ON(fs_info->dewayed_wefs_wsv.wesewved > 0);
	WAWN_ON(fs_info->dewayed_wefs_wsv.size > 0);
}

static stwuct btwfs_bwock_wsv *get_bwock_wsv(
					const stwuct btwfs_twans_handwe *twans,
					const stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_bwock_wsv *bwock_wsv = NUWW;

	if (test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state) ||
	    (woot == fs_info->uuid_woot) ||
	    (twans->adding_csums &&
	     woot->woot_key.objectid == BTWFS_CSUM_TWEE_OBJECTID))
		bwock_wsv = twans->bwock_wsv;

	if (!bwock_wsv)
		bwock_wsv = woot->bwock_wsv;

	if (!bwock_wsv)
		bwock_wsv = &fs_info->empty_bwock_wsv;

	wetuwn bwock_wsv;
}

stwuct btwfs_bwock_wsv *btwfs_use_bwock_wsv(stwuct btwfs_twans_handwe *twans,
					    stwuct btwfs_woot *woot,
					    u32 bwocksize)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_bwock_wsv *bwock_wsv;
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	int wet;
	boow gwobaw_updated = fawse;

	bwock_wsv = get_bwock_wsv(twans, woot);

	if (unwikewy(bwock_wsv->size == 0))
		goto twy_wesewve;
again:
	wet = btwfs_bwock_wsv_use_bytes(bwock_wsv, bwocksize);
	if (!wet)
		wetuwn bwock_wsv;

	if (bwock_wsv->faiwfast)
		wetuwn EWW_PTW(wet);

	if (bwock_wsv->type == BTWFS_BWOCK_WSV_GWOBAW && !gwobaw_updated) {
		gwobaw_updated = twue;
		btwfs_update_gwobaw_bwock_wsv(fs_info);
		goto again;
	}

	/*
	 * The gwobaw wesewve stiww exists to save us fwom ouwsewves, so don't
	 * wawn_on if we awe showt on ouw dewayed wefs wesewve.
	 */
	if (bwock_wsv->type != BTWFS_BWOCK_WSV_DEWWEFS &&
	    btwfs_test_opt(fs_info, ENOSPC_DEBUG)) {
		static DEFINE_WATEWIMIT_STATE(_ws,
				DEFAUWT_WATEWIMIT_INTEWVAW * 10,
				/*DEFAUWT_WATEWIMIT_BUWST*/ 1);
		if (__watewimit(&_ws))
			WAWN(1, KEWN_DEBUG
				"BTWFS: bwock wsv %d wetuwned %d\n",
				bwock_wsv->type, wet);
	}
twy_wesewve:
	wet = btwfs_wesewve_metadata_bytes(fs_info, bwock_wsv->space_info,
					   bwocksize, BTWFS_WESEWVE_NO_FWUSH);
	if (!wet)
		wetuwn bwock_wsv;
	/*
	 * If we couwdn't wesewve metadata bytes twy and use some fwom
	 * the gwobaw wesewve if its space type is the same as the gwobaw
	 * wesewvation.
	 */
	if (bwock_wsv->type != BTWFS_BWOCK_WSV_GWOBAW &&
	    bwock_wsv->space_info == gwobaw_wsv->space_info) {
		wet = btwfs_bwock_wsv_use_bytes(gwobaw_wsv, bwocksize);
		if (!wet)
			wetuwn gwobaw_wsv;
	}

	/*
	 * Aww hope is wost, but of couwse ouw wesewvations awe ovewwy
	 * pessimistic, so instead of possibwy having an ENOSPC abowt hewe, twy
	 * one wast time to fowce a wesewvation if thewe's enough actuaw space
	 * on disk to make the wesewvation.
	 */
	wet = btwfs_wesewve_metadata_bytes(fs_info, bwock_wsv->space_info, bwocksize,
					   BTWFS_WESEWVE_FWUSH_EMEWGENCY);
	if (!wet)
		wetuwn bwock_wsv;

	wetuwn EWW_PTW(wet);
}

int btwfs_check_twunc_cache_fwee_space(stwuct btwfs_fs_info *fs_info,
				       stwuct btwfs_bwock_wsv *wsv)
{
	u64 needed_bytes;
	int wet;

	/* 1 fow swack space, 1 fow updating the inode */
	needed_bytes = btwfs_cawc_insewt_metadata_size(fs_info, 1) +
		btwfs_cawc_metadata_size(fs_info, 1);

	spin_wock(&wsv->wock);
	if (wsv->wesewved < needed_bytes)
		wet = -ENOSPC;
	ewse
		wet = 0;
	spin_unwock(&wsv->wock);
	wetuwn wet;
}
