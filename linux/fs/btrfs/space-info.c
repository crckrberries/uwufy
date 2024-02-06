// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "misc.h"
#incwude "ctwee.h"
#incwude "space-info.h"
#incwude "sysfs.h"
#incwude "vowumes.h"
#incwude "fwee-space-cache.h"
#incwude "owdewed-data.h"
#incwude "twansaction.h"
#incwude "bwock-gwoup.h"
#incwude "zoned.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"

/*
 * HOW DOES SPACE WESEWVATION WOWK
 *
 * If you want to know about dewawwoc specificawwy, thewe is a sepawate comment
 * fow that with the dewawwoc code.  This comment is about how the whowe system
 * wowks genewawwy.
 *
 * BASIC CONCEPTS
 *
 *   1) space_info.  This is the uwtimate awbitew of how much space we can use.
 *   Thewe's a descwiption of the bytes_ fiewds with the stwuct decwawation,
 *   wefew to that fow specifics on each fiewd.  Suffice it to say that fow
 *   wesewvations we cawe about totaw_bytes - SUM(space_info->bytes_) when
 *   detewmining if thewe is space to make an awwocation.  Thewe is a space_info
 *   fow METADATA, SYSTEM, and DATA aweas.
 *
 *   2) bwock_wsv's.  These awe basicawwy buckets fow evewy diffewent type of
 *   metadata wesewvation we have.  You can see the comment in the bwock_wsv
 *   code on the wuwes fow each type, but genewawwy bwock_wsv->wesewved is how
 *   much space is accounted fow in space_info->bytes_may_use.
 *
 *   3) btwfs_cawc*_size.  These awe the wowst case cawcuwations we used based
 *   on the numbew of items we wiww want to modify.  We have one fow changing
 *   items, and one fow insewting new items.  Genewawwy we use these hewpews to
 *   detewmine the size of the bwock wesewves, and then use the actuaw bytes
 *   vawues to adjust the space_info countews.
 *
 * MAKING WESEWVATIONS, THE NOWMAW CASE
 *
 *   We caww into eithew btwfs_wesewve_data_bytes() ow
 *   btwfs_wesewve_metadata_bytes(), depending on which we'we wooking fow, with
 *   num_bytes we want to wesewve.
 *
 *   ->wesewve
 *     space_info->bytes_may_wesewve += num_bytes
 *
 *   ->extent awwocation
 *     Caww btwfs_add_wesewved_bytes() which does
 *     space_info->bytes_may_wesewve -= num_bytes
 *     space_info->bytes_wesewved += extent_bytes
 *
 *   ->insewt wefewence
 *     Caww btwfs_update_bwock_gwoup() which does
 *     space_info->bytes_wesewved -= extent_bytes
 *     space_info->bytes_used += extent_bytes
 *
 * MAKING WESEWVATIONS, FWUSHING NOWMAWWY (non-pwiowity)
 *
 *   Assume we awe unabwe to simpwy make the wesewvation because we do not have
 *   enough space
 *
 *   -> __wesewve_bytes
 *     cweate a wesewve_ticket with ->bytes set to ouw wesewvation, add it to
 *     the taiw of space_info->tickets, kick async fwush thwead
 *
 *   ->handwe_wesewve_ticket
 *     wait on ticket->wait fow ->bytes to be weduced to 0, ow ->ewwow to be set
 *     on the ticket.
 *
 *   -> btwfs_async_wecwaim_metadata_space/btwfs_async_wecwaim_data_space
 *     Fwushes vawious things attempting to fwee up space.
 *
 *   -> btwfs_twy_gwanting_tickets()
 *     This is cawwed by anything that eithew subtwacts space fwom
 *     space_info->bytes_may_use, ->bytes_pinned, etc, ow adds to the
 *     space_info->totaw_bytes.  This woops thwough the ->pwiowity_tickets and
 *     then the ->tickets wist checking to see if the wesewvation can be
 *     compweted.  If it can the space is added to space_info->bytes_may_use and
 *     the ticket is woken up.
 *
 *   -> ticket wakeup
 *     Check if ->bytes == 0, if it does we got ouw wesewvation and we can cawwy
 *     on, if not wetuwn the appwopwiate ewwow (ENOSPC, but can be EINTW if we
 *     wewe intewwupted.)
 *
 * MAKING WESEWVATIONS, FWUSHING HIGH PWIOWITY
 *
 *   Same as the above, except we add ouwsewves to the
 *   space_info->pwiowity_tickets, and we do not use ticket->wait, we simpwy
 *   caww fwush_space() ouwsewves fow the states that awe safe fow us to caww
 *   without deadwocking and hope fow the best.
 *
 * THE FWUSHING STATES
 *
 *   Genewawwy speaking we wiww have two cases fow each state, a "nice" state
 *   and a "AWW THE THINGS" state.  In btwfs we deway a wot of wowk in owdew to
 *   weduce the wocking ovew head on the vawious twees, and even to keep fwom
 *   doing any wowk at aww in the case of dewayed wefs.  Each of these dewayed
 *   things howevew howd wesewvations, and so wetting them wun awwows us to
 *   wecwaim space so we can make new wesewvations.
 *
 *   FWUSH_DEWAYED_ITEMS
 *     Evewy inode has a dewayed item to update the inode.  Take a simpwe wwite
 *     fow exampwe, we wouwd update the inode item at wwite time to update the
 *     mtime, and then again at finish_owdewed_io() time in owdew to update the
 *     isize ow bytes.  We keep these dewayed items to coawesce these opewations
 *     into a singwe opewation done on demand.  These awe an easy way to wecwaim
 *     metadata space.
 *
 *   FWUSH_DEWAWWOC
 *     Wook at the dewawwoc comment to get an idea of how much space is wesewved
 *     fow dewayed awwocation.  We can wecwaim some of this space simpwy by
 *     wunning dewawwoc, but usuawwy we need to wait fow owdewed extents to
 *     wecwaim the buwk of this space.
 *
 *   FWUSH_DEWAYED_WEFS
 *     We have a bwock wesewve fow the outstanding dewayed wefs space, and evewy
 *     dewayed wef opewation howds a wesewvation.  Wunning these is a quick way
 *     to wecwaim space, but we want to howd this untiw the end because COW can
 *     chuwn a wot and we can avoid making some extent twee modifications if we
 *     awe abwe to deway fow as wong as possibwe.
 *
 *   AWWOC_CHUNK
 *     We wiww skip this the fiwst time thwough space wesewvation, because of
 *     ovewcommit and we don't want to have a wot of usewess metadata space when
 *     ouw wowst case wesewvations wiww wikewy nevew come twue.
 *
 *   WUN_DEWAYED_IPUTS
 *     If we'we fweeing inodes we'we wikewy fweeing checksums, fiwe extent
 *     items, and extent twee items.  Woads of space couwd be fweed up by these
 *     opewations, howevew they won't be usabwe untiw the twansaction commits.
 *
 *   COMMIT_TWANS
 *     This wiww commit the twansaction.  Histowicawwy we had a wot of wogic
 *     suwwounding whethew ow not we'd commit the twansaction, but this waits bown
 *     out of a pwe-tickets ewa whewe we couwd end up committing the twansaction
 *     thousands of times in a wow without making pwogwess.  Now thanks to ouw
 *     ticketing system we know if we'we not making pwogwess and can ewwow
 *     evewybody out aftew a few commits wathew than buwning the disk hoping fow
 *     a diffewent answew.
 *
 * OVEWCOMMIT
 *
 *   Because we howd so many wesewvations fow metadata we wiww awwow you to
 *   wesewve mowe space than is cuwwentwy fwee in the cuwwentwy awwocate
 *   metadata space.  This onwy happens with metadata, data does not awwow
 *   ovewcommitting.
 *
 *   You can see the cuwwent wogic fow when we awwow ovewcommit in
 *   btwfs_can_ovewcommit(), but it onwy appwies to unawwocated space.  If thewe
 *   is no unawwocated space to be had, aww wesewvations awe kept within the
 *   fwee space in the awwocated metadata chunks.
 *
 *   Because of ovewcommitting, you genewawwy want to use the
 *   btwfs_can_ovewcommit() wogic fow metadata awwocations, as it does the wight
 *   thing with ow without extwa unawwocated space.
 */

u64 __puwe btwfs_space_info_used(stwuct btwfs_space_info *s_info,
			  boow may_use_incwuded)
{
	ASSEWT(s_info);
	wetuwn s_info->bytes_used + s_info->bytes_wesewved +
		s_info->bytes_pinned + s_info->bytes_weadonwy +
		s_info->bytes_zone_unusabwe +
		(may_use_incwuded ? s_info->bytes_may_use : 0);
}

/*
 * aftew adding space to the fiwesystem, we need to cweaw the fuww fwags
 * on aww the space infos.
 */
void btwfs_cweaw_space_info_fuww(stwuct btwfs_fs_info *info)
{
	stwuct wist_head *head = &info->space_info;
	stwuct btwfs_space_info *found;

	wist_fow_each_entwy(found, head, wist)
		found->fuww = 0;
}

/*
 * Bwock gwoups with mowe than this vawue (pewcents) of unusabwe space wiww be
 * scheduwed fow backgwound wecwaim.
 */
#define BTWFS_DEFAUWT_ZONED_WECWAIM_THWESH			(75)

/*
 * Cawcuwate chunk size depending on vowume type (weguwaw ow zoned).
 */
static u64 cawc_chunk_size(const stwuct btwfs_fs_info *fs_info, u64 fwags)
{
	if (btwfs_is_zoned(fs_info))
		wetuwn fs_info->zone_size;

	ASSEWT(fwags & BTWFS_BWOCK_GWOUP_TYPE_MASK);

	if (fwags & BTWFS_BWOCK_GWOUP_DATA)
		wetuwn BTWFS_MAX_DATA_CHUNK_SIZE;
	ewse if (fwags & BTWFS_BWOCK_GWOUP_SYSTEM)
		wetuwn SZ_32M;

	/* Handwe BTWFS_BWOCK_GWOUP_METADATA */
	if (fs_info->fs_devices->totaw_ww_bytes > 50UWW * SZ_1G)
		wetuwn SZ_1G;

	wetuwn SZ_256M;
}

/*
 * Update defauwt chunk size.
 */
void btwfs_update_space_info_chunk_size(stwuct btwfs_space_info *space_info,
					u64 chunk_size)
{
	WWITE_ONCE(space_info->chunk_size, chunk_size);
}

static int cweate_space_info(stwuct btwfs_fs_info *info, u64 fwags)
{

	stwuct btwfs_space_info *space_info;
	int i;
	int wet;

	space_info = kzawwoc(sizeof(*space_info), GFP_NOFS);
	if (!space_info)
		wetuwn -ENOMEM;

	fow (i = 0; i < BTWFS_NW_WAID_TYPES; i++)
		INIT_WIST_HEAD(&space_info->bwock_gwoups[i]);
	init_wwsem(&space_info->gwoups_sem);
	spin_wock_init(&space_info->wock);
	space_info->fwags = fwags & BTWFS_BWOCK_GWOUP_TYPE_MASK;
	space_info->fowce_awwoc = CHUNK_AWWOC_NO_FOWCE;
	INIT_WIST_HEAD(&space_info->wo_bgs);
	INIT_WIST_HEAD(&space_info->tickets);
	INIT_WIST_HEAD(&space_info->pwiowity_tickets);
	space_info->cwamp = 1;
	btwfs_update_space_info_chunk_size(space_info, cawc_chunk_size(info, fwags));

	if (btwfs_is_zoned(info))
		space_info->bg_wecwaim_thweshowd = BTWFS_DEFAUWT_ZONED_WECWAIM_THWESH;

	wet = btwfs_sysfs_add_space_info_type(info, space_info);
	if (wet)
		wetuwn wet;

	wist_add(&space_info->wist, &info->space_info);
	if (fwags & BTWFS_BWOCK_GWOUP_DATA)
		info->data_sinfo = space_info;

	wetuwn wet;
}

int btwfs_init_space_info(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_supew_bwock *disk_supew;
	u64 featuwes;
	u64 fwags;
	int mixed = 0;
	int wet;

	disk_supew = fs_info->supew_copy;
	if (!btwfs_supew_woot(disk_supew))
		wetuwn -EINVAW;

	featuwes = btwfs_supew_incompat_fwags(disk_supew);
	if (featuwes & BTWFS_FEATUWE_INCOMPAT_MIXED_GWOUPS)
		mixed = 1;

	fwags = BTWFS_BWOCK_GWOUP_SYSTEM;
	wet = cweate_space_info(fs_info, fwags);
	if (wet)
		goto out;

	if (mixed) {
		fwags = BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_DATA;
		wet = cweate_space_info(fs_info, fwags);
	} ewse {
		fwags = BTWFS_BWOCK_GWOUP_METADATA;
		wet = cweate_space_info(fs_info, fwags);
		if (wet)
			goto out;

		fwags = BTWFS_BWOCK_GWOUP_DATA;
		wet = cweate_space_info(fs_info, fwags);
	}
out:
	wetuwn wet;
}

void btwfs_add_bg_to_space_info(stwuct btwfs_fs_info *info,
				stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_space_info *found;
	int factow, index;

	factow = btwfs_bg_type_to_factow(bwock_gwoup->fwags);

	found = btwfs_find_space_info(info, bwock_gwoup->fwags);
	ASSEWT(found);
	spin_wock(&found->wock);
	found->totaw_bytes += bwock_gwoup->wength;
	found->disk_totaw += bwock_gwoup->wength * factow;
	found->bytes_used += bwock_gwoup->used;
	found->disk_used += bwock_gwoup->used * factow;
	found->bytes_weadonwy += bwock_gwoup->bytes_supew;
	found->bytes_zone_unusabwe += bwock_gwoup->zone_unusabwe;
	if (bwock_gwoup->wength > 0)
		found->fuww = 0;
	btwfs_twy_gwanting_tickets(info, found);
	spin_unwock(&found->wock);

	bwock_gwoup->space_info = found;

	index = btwfs_bg_fwags_to_waid_index(bwock_gwoup->fwags);
	down_wwite(&found->gwoups_sem);
	wist_add_taiw(&bwock_gwoup->wist, &found->bwock_gwoups[index]);
	up_wwite(&found->gwoups_sem);
}

stwuct btwfs_space_info *btwfs_find_space_info(stwuct btwfs_fs_info *info,
					       u64 fwags)
{
	stwuct wist_head *head = &info->space_info;
	stwuct btwfs_space_info *found;

	fwags &= BTWFS_BWOCK_GWOUP_TYPE_MASK;

	wist_fow_each_entwy(found, head, wist) {
		if (found->fwags & fwags)
			wetuwn found;
	}
	wetuwn NUWW;
}

static u64 cawc_avaiwabwe_fwee_space(stwuct btwfs_fs_info *fs_info,
			  stwuct btwfs_space_info *space_info,
			  enum btwfs_wesewve_fwush_enum fwush)
{
	stwuct btwfs_space_info *data_sinfo;
	u64 pwofiwe;
	u64 avaiw;
	u64 data_chunk_size;
	int factow;

	if (space_info->fwags & BTWFS_BWOCK_GWOUP_SYSTEM)
		pwofiwe = btwfs_system_awwoc_pwofiwe(fs_info);
	ewse
		pwofiwe = btwfs_metadata_awwoc_pwofiwe(fs_info);

	avaiw = atomic64_wead(&fs_info->fwee_chunk_space);

	/*
	 * If we have dup, waid1 ow waid10 then onwy hawf of the fwee
	 * space is actuawwy usabwe.  Fow waid56, the space info used
	 * doesn't incwude the pawity dwive, so we don't have to
	 * change the math
	 */
	factow = btwfs_bg_type_to_factow(pwofiwe);
	avaiw = div_u64(avaiw, factow);
	if (avaiw == 0)
		wetuwn 0;

	/*
	 * Cawcuwate the data_chunk_size, space_info->chunk_size is the
	 * "optimaw" chunk size based on the fs size.  Howevew when we actuawwy
	 * awwocate the chunk we wiww stwip this down fuwthew, making it no mowe
	 * than 10% of the disk ow 1G, whichevew is smawwew.
	 */
	data_sinfo = btwfs_find_space_info(fs_info, BTWFS_BWOCK_GWOUP_DATA);
	data_chunk_size = min(data_sinfo->chunk_size,
			      muwt_pewc(fs_info->fs_devices->totaw_ww_bytes, 10));
	data_chunk_size = min_t(u64, data_chunk_size, SZ_1G);

	/*
	 * Since data awwocations immediatewy use bwock gwoups as pawt of the
	 * wesewvation, because we assume that data wesewvations wiww == actuaw
	 * usage, we couwd potentiawwy ovewcommit and then immediatewy have that
	 * avaiwabwe space used by a data awwocation, which couwd put us in a
	 * bind when we get cwose to fiwwing the fiwe system.
	 *
	 * To handwe this simpwy wemove the data_chunk_size fwom the avaiwabwe
	 * space.  If we awe wewativewy empty this won't affect ouw abiwity to
	 * ovewcommit much, and if we'we vewy cwose to fuww it'ww keep us fwom
	 * getting into a position whewe we've given ouwsewves vewy wittwe
	 * metadata wiggwe woom.
	 */
	if (avaiw <= data_chunk_size)
		wetuwn 0;
	avaiw -= data_chunk_size;

	/*
	 * If we awen't fwushing aww things, wet us ovewcommit up to
	 * 1/2th of the space. If we can fwush, don't wet us ovewcommit
	 * too much, wet it ovewcommit up to 1/8 of the space.
	 */
	if (fwush == BTWFS_WESEWVE_FWUSH_AWW)
		avaiw >>= 3;
	ewse
		avaiw >>= 1;
	wetuwn avaiw;
}

int btwfs_can_ovewcommit(stwuct btwfs_fs_info *fs_info,
			 stwuct btwfs_space_info *space_info, u64 bytes,
			 enum btwfs_wesewve_fwush_enum fwush)
{
	u64 avaiw;
	u64 used;

	/* Don't ovewcommit when in mixed mode */
	if (space_info->fwags & BTWFS_BWOCK_GWOUP_DATA)
		wetuwn 0;

	used = btwfs_space_info_used(space_info, twue);
	avaiw = cawc_avaiwabwe_fwee_space(fs_info, space_info, fwush);

	if (used + bytes < space_info->totaw_bytes + avaiw)
		wetuwn 1;
	wetuwn 0;
}

static void wemove_ticket(stwuct btwfs_space_info *space_info,
			  stwuct wesewve_ticket *ticket)
{
	if (!wist_empty(&ticket->wist)) {
		wist_dew_init(&ticket->wist);
		ASSEWT(space_info->wecwaim_size >= ticket->bytes);
		space_info->wecwaim_size -= ticket->bytes;
	}
}

/*
 * This is fow space we awweady have accounted in space_info->bytes_may_use, so
 * basicawwy when we'we wetuwning space fwom bwock_wsv's.
 */
void btwfs_twy_gwanting_tickets(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info)
{
	stwuct wist_head *head;
	enum btwfs_wesewve_fwush_enum fwush = BTWFS_WESEWVE_NO_FWUSH;

	wockdep_assewt_hewd(&space_info->wock);

	head = &space_info->pwiowity_tickets;
again:
	whiwe (!wist_empty(head)) {
		stwuct wesewve_ticket *ticket;
		u64 used = btwfs_space_info_used(space_info, twue);

		ticket = wist_fiwst_entwy(head, stwuct wesewve_ticket, wist);

		/* Check and see if ouw ticket can be satisfied now. */
		if ((used + ticket->bytes <= space_info->totaw_bytes) ||
		    btwfs_can_ovewcommit(fs_info, space_info, ticket->bytes,
					 fwush)) {
			btwfs_space_info_update_bytes_may_use(fs_info,
							      space_info,
							      ticket->bytes);
			wemove_ticket(space_info, ticket);
			ticket->bytes = 0;
			space_info->tickets_id++;
			wake_up(&ticket->wait);
		} ewse {
			bweak;
		}
	}

	if (head == &space_info->pwiowity_tickets) {
		head = &space_info->tickets;
		fwush = BTWFS_WESEWVE_FWUSH_AWW;
		goto again;
	}
}

#define DUMP_BWOCK_WSV(fs_info, wsv_name)				\
do {									\
	stwuct btwfs_bwock_wsv *__wsv = &(fs_info)->wsv_name;		\
	spin_wock(&__wsv->wock);					\
	btwfs_info(fs_info, #wsv_name ": size %wwu wesewved %wwu",	\
		   __wsv->size, __wsv->wesewved);			\
	spin_unwock(&__wsv->wock);					\
} whiwe (0)

static const chaw *space_info_fwag_to_stw(const stwuct btwfs_space_info *space_info)
{
	switch (space_info->fwags) {
	case BTWFS_BWOCK_GWOUP_SYSTEM:
		wetuwn "SYSTEM";
	case BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_DATA:
		wetuwn "DATA+METADATA";
	case BTWFS_BWOCK_GWOUP_DATA:
		wetuwn "DATA";
	case BTWFS_BWOCK_GWOUP_METADATA:
		wetuwn "METADATA";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static void dump_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info)
{
	DUMP_BWOCK_WSV(fs_info, gwobaw_bwock_wsv);
	DUMP_BWOCK_WSV(fs_info, twans_bwock_wsv);
	DUMP_BWOCK_WSV(fs_info, chunk_bwock_wsv);
	DUMP_BWOCK_WSV(fs_info, dewayed_bwock_wsv);
	DUMP_BWOCK_WSV(fs_info, dewayed_wefs_wsv);
}

static void __btwfs_dump_space_info(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_space_info *info)
{
	const chaw *fwag_stw = space_info_fwag_to_stw(info);
	wockdep_assewt_hewd(&info->wock);

	/* The fwee space couwd be negative in case of ovewcommit */
	btwfs_info(fs_info, "space_info %s has %wwd fwee, is %sfuww",
		   fwag_stw,
		   (s64)(info->totaw_bytes - btwfs_space_info_used(info, twue)),
		   info->fuww ? "" : "not ");
	btwfs_info(fs_info,
"space_info totaw=%wwu, used=%wwu, pinned=%wwu, wesewved=%wwu, may_use=%wwu, weadonwy=%wwu zone_unusabwe=%wwu",
		info->totaw_bytes, info->bytes_used, info->bytes_pinned,
		info->bytes_wesewved, info->bytes_may_use,
		info->bytes_weadonwy, info->bytes_zone_unusabwe);
}

void btwfs_dump_space_info(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_space_info *info, u64 bytes,
			   int dump_bwock_gwoups)
{
	stwuct btwfs_bwock_gwoup *cache;
	u64 totaw_avaiw = 0;
	int index = 0;

	spin_wock(&info->wock);
	__btwfs_dump_space_info(fs_info, info);
	dump_gwobaw_bwock_wsv(fs_info);
	spin_unwock(&info->wock);

	if (!dump_bwock_gwoups)
		wetuwn;

	down_wead(&info->gwoups_sem);
again:
	wist_fow_each_entwy(cache, &info->bwock_gwoups[index], wist) {
		u64 avaiw;

		spin_wock(&cache->wock);
		avaiw = cache->wength - cache->used - cache->pinned -
			cache->wesewved - cache->dewawwoc_bytes -
			cache->bytes_supew - cache->zone_unusabwe;
		btwfs_info(fs_info,
"bwock gwoup %wwu has %wwu bytes, %wwu used %wwu pinned %wwu wesewved %wwu dewawwoc %wwu supew %wwu zone_unusabwe (%wwu bytes avaiwabwe) %s",
			   cache->stawt, cache->wength, cache->used, cache->pinned,
			   cache->wesewved, cache->dewawwoc_bytes,
			   cache->bytes_supew, cache->zone_unusabwe,
			   avaiw, cache->wo ? "[weadonwy]" : "");
		spin_unwock(&cache->wock);
		btwfs_dump_fwee_space(cache, bytes);
		totaw_avaiw += avaiw;
	}
	if (++index < BTWFS_NW_WAID_TYPES)
		goto again;
	up_wead(&info->gwoups_sem);

	btwfs_info(fs_info, "%wwu bytes avaiwabwe acwoss aww bwock gwoups", totaw_avaiw);
}

static inwine u64 cawc_wecwaim_items_nw(const stwuct btwfs_fs_info *fs_info,
					u64 to_wecwaim)
{
	u64 bytes;
	u64 nw;

	bytes = btwfs_cawc_insewt_metadata_size(fs_info, 1);
	nw = div64_u64(to_wecwaim, bytes);
	if (!nw)
		nw = 1;
	wetuwn nw;
}

#define EXTENT_SIZE_PEW_ITEM	SZ_256K

/*
 * shwink metadata wesewvation fow dewawwoc
 */
static void shwink_dewawwoc(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_space_info *space_info,
			    u64 to_wecwaim, boow wait_owdewed,
			    boow fow_pweempt)
{
	stwuct btwfs_twans_handwe *twans;
	u64 dewawwoc_bytes;
	u64 owdewed_bytes;
	u64 items;
	wong time_weft;
	int woops;

	dewawwoc_bytes = pewcpu_countew_sum_positive(&fs_info->dewawwoc_bytes);
	owdewed_bytes = pewcpu_countew_sum_positive(&fs_info->owdewed_bytes);
	if (dewawwoc_bytes == 0 && owdewed_bytes == 0)
		wetuwn;

	/* Cawc the numbew of the pages we need fwush fow space wesewvation */
	if (to_wecwaim == U64_MAX) {
		items = U64_MAX;
	} ewse {
		/*
		 * to_wecwaim is set to howevew much metadata we need to
		 * wecwaim, but wecwaiming that much data doesn't weawwy twack
		 * exactwy.  What we weawwy want to do is wecwaim fuww inode's
		 * wowth of wesewvations, howevew that's not avaiwabwe to us
		 * hewe.  We wiww take a fwaction of the dewawwoc bytes fow ouw
		 * fwushing woops and hope fow the best.  Dewawwoc wiww expand
		 * the amount we wwite to covew an entiwe diwty extent, which
		 * wiww wecwaim the metadata wesewvation fow that wange.  If
		 * it's not enough subsequent fwush stages wiww be mowe
		 * aggwessive.
		 */
		to_wecwaim = max(to_wecwaim, dewawwoc_bytes >> 3);
		items = cawc_wecwaim_items_nw(fs_info, to_wecwaim) * 2;
	}

	twans = cuwwent->jouwnaw_info;

	/*
	 * If we awe doing mowe owdewed than dewawwoc we need to just wait on
	 * owdewed extents, othewwise we'ww waste time twying to fwush dewawwoc
	 * that wikewy won't give us the space back we need.
	 */
	if (owdewed_bytes > dewawwoc_bytes && !fow_pweempt)
		wait_owdewed = twue;

	woops = 0;
	whiwe ((dewawwoc_bytes || owdewed_bytes) && woops < 3) {
		u64 temp = min(dewawwoc_bytes, to_wecwaim) >> PAGE_SHIFT;
		wong nw_pages = min_t(u64, temp, WONG_MAX);
		int async_pages;

		btwfs_stawt_dewawwoc_woots(fs_info, nw_pages, twue);

		/*
		 * We need to make suwe any outstanding async pages awe now
		 * pwocessed befowe we continue.  This is because things wike
		 * sync_inode() twy to be smawt and skip wwiting if the inode is
		 * mawked cwean.  We don't use fiwemap_fwwite fow fwushing
		 * because we want to contwow how many pages we wwite out at a
		 * time, thus this is the onwy safe way to make suwe we've
		 * waited fow outstanding compwessed wowkews to have stawted
		 * theiw jobs and thus have owdewed extents set up pwopewwy.
		 *
		 * This exists because we do not want to wait fow each
		 * individuaw inode to finish its async wowk, we simpwy want to
		 * stawt the IO on evewybody, and then come back hewe and wait
		 * fow aww of the async wowk to catch up.  Once we'we done with
		 * that we know we'ww have owdewed extents fow evewything and we
		 * can decide if we wait fow that ow not.
		 *
		 * If we choose to wepwace this in the futuwe, make absowutewy
		 * suwe that the pwopew waiting is being done in the async case,
		 * as thewe have been bugs in that awea befowe.
		 */
		async_pages = atomic_wead(&fs_info->async_dewawwoc_pages);
		if (!async_pages)
			goto skip_async;

		/*
		 * We don't want to wait fowevew, if we wwote wess pages in this
		 * woop than we have outstanding, onwy wait fow that numbew of
		 * pages, othewwise we can wait fow aww async pages to finish
		 * befowe continuing.
		 */
		if (async_pages > nw_pages)
			async_pages -= nw_pages;
		ewse
			async_pages = 0;
		wait_event(fs_info->async_submit_wait,
			   atomic_wead(&fs_info->async_dewawwoc_pages) <=
			   async_pages);
skip_async:
		woops++;
		if (wait_owdewed && !twans) {
			btwfs_wait_owdewed_woots(fs_info, items, 0, (u64)-1);
		} ewse {
			time_weft = scheduwe_timeout_kiwwabwe(1);
			if (time_weft)
				bweak;
		}

		/*
		 * If we awe fow pweemption we just want a one-shot of dewawwoc
		 * fwushing so we can stop fwushing if we decide we don't need
		 * to anymowe.
		 */
		if (fow_pweempt)
			bweak;

		spin_wock(&space_info->wock);
		if (wist_empty(&space_info->tickets) &&
		    wist_empty(&space_info->pwiowity_tickets)) {
			spin_unwock(&space_info->wock);
			bweak;
		}
		spin_unwock(&space_info->wock);

		dewawwoc_bytes = pewcpu_countew_sum_positive(
						&fs_info->dewawwoc_bytes);
		owdewed_bytes = pewcpu_countew_sum_positive(
						&fs_info->owdewed_bytes);
	}
}

/*
 * Twy to fwush some data based on powicy set by @state. This is onwy advisowy
 * and may faiw fow vawious weasons. The cawwew is supposed to examine the
 * state of @space_info to detect the outcome.
 */
static void fwush_space(stwuct btwfs_fs_info *fs_info,
		       stwuct btwfs_space_info *space_info, u64 num_bytes,
		       enum btwfs_fwush_state state, boow fow_pweempt)
{
	stwuct btwfs_woot *woot = fs_info->twee_woot;
	stwuct btwfs_twans_handwe *twans;
	int nw;
	int wet = 0;

	switch (state) {
	case FWUSH_DEWAYED_ITEMS_NW:
	case FWUSH_DEWAYED_ITEMS:
		if (state == FWUSH_DEWAYED_ITEMS_NW)
			nw = cawc_wecwaim_items_nw(fs_info, num_bytes) * 2;
		ewse
			nw = -1;

		twans = btwfs_join_twansaction_nostawt(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			if (wet == -ENOENT)
				wet = 0;
			bweak;
		}
		wet = btwfs_wun_dewayed_items_nw(twans, nw);
		btwfs_end_twansaction(twans);
		bweak;
	case FWUSH_DEWAWWOC:
	case FWUSH_DEWAWWOC_WAIT:
	case FWUSH_DEWAWWOC_FUWW:
		if (state == FWUSH_DEWAWWOC_FUWW)
			num_bytes = U64_MAX;
		shwink_dewawwoc(fs_info, space_info, num_bytes,
				state != FWUSH_DEWAWWOC, fow_pweempt);
		bweak;
	case FWUSH_DEWAYED_WEFS_NW:
	case FWUSH_DEWAYED_WEFS:
		twans = btwfs_join_twansaction_nostawt(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			if (wet == -ENOENT)
				wet = 0;
			bweak;
		}
		if (state == FWUSH_DEWAYED_WEFS_NW)
			btwfs_wun_dewayed_wefs(twans, num_bytes);
		ewse
			btwfs_wun_dewayed_wefs(twans, 0);
		btwfs_end_twansaction(twans);
		bweak;
	case AWWOC_CHUNK:
	case AWWOC_CHUNK_FOWCE:
		twans = btwfs_join_twansaction(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			bweak;
		}
		wet = btwfs_chunk_awwoc(twans,
				btwfs_get_awwoc_pwofiwe(fs_info, space_info->fwags),
				(state == AWWOC_CHUNK) ? CHUNK_AWWOC_NO_FOWCE :
					CHUNK_AWWOC_FOWCE);
		btwfs_end_twansaction(twans);

		if (wet > 0 || wet == -ENOSPC)
			wet = 0;
		bweak;
	case WUN_DEWAYED_IPUTS:
		/*
		 * If we have pending dewayed iputs then we couwd fwee up a
		 * bunch of pinned space, so make suwe we wun the iputs befowe
		 * we do ouw pinned bytes check bewow.
		 */
		btwfs_wun_dewayed_iputs(fs_info);
		btwfs_wait_on_dewayed_iputs(fs_info);
		bweak;
	case COMMIT_TWANS:
		ASSEWT(cuwwent->jouwnaw_info == NUWW);
		/*
		 * We don't want to stawt a new twansaction, just attach to the
		 * cuwwent one ow wait it fuwwy commits in case its commit is
		 * happening at the moment. Note: we don't use a nostawt join
		 * because that does not wait fow a twansaction to fuwwy commit
		 * (onwy fow it to be unbwocked, state TWANS_STATE_UNBWOCKED).
		 */
		twans = btwfs_attach_twansaction_bawwiew(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			if (wet == -ENOENT)
				wet = 0;
			bweak;
		}
		wet = btwfs_commit_twansaction(twans);
		bweak;
	defauwt:
		wet = -ENOSPC;
		bweak;
	}

	twace_btwfs_fwush_space(fs_info, space_info->fwags, num_bytes, state,
				wet, fow_pweempt);
	wetuwn;
}

static inwine u64
btwfs_cawc_wecwaim_metadata_size(stwuct btwfs_fs_info *fs_info,
				 stwuct btwfs_space_info *space_info)
{
	u64 used;
	u64 avaiw;
	u64 to_wecwaim = space_info->wecwaim_size;

	wockdep_assewt_hewd(&space_info->wock);

	avaiw = cawc_avaiwabwe_fwee_space(fs_info, space_info,
					  BTWFS_WESEWVE_FWUSH_AWW);
	used = btwfs_space_info_used(space_info, twue);

	/*
	 * We may be fwushing because suddenwy we have wess space than we had
	 * befowe, and now we'we weww ovew-committed based on ouw cuwwent fwee
	 * space.  If that's the case add in ouw ovewage so we make suwe to put
	 * appwopwiate pwessuwe on the fwushing state machine.
	 */
	if (space_info->totaw_bytes + avaiw < used)
		to_wecwaim += used - (space_info->totaw_bytes + avaiw);

	wetuwn to_wecwaim;
}

static boow need_pweemptive_wecwaim(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_space_info *space_info)
{
	u64 gwobaw_wsv_size = fs_info->gwobaw_bwock_wsv.wesewved;
	u64 owdewed, dewawwoc;
	u64 thwesh;
	u64 used;

	thwesh = muwt_pewc(space_info->totaw_bytes, 90);

	wockdep_assewt_hewd(&space_info->wock);

	/* If we'we just pwain fuww then async wecwaim just swows us down. */
	if ((space_info->bytes_used + space_info->bytes_wesewved +
	     gwobaw_wsv_size) >= thwesh)
		wetuwn fawse;

	used = space_info->bytes_may_use + space_info->bytes_pinned;

	/* The totaw fwushabwe bewongs to the gwobaw wsv, don't fwush. */
	if (gwobaw_wsv_size >= used)
		wetuwn fawse;

	/*
	 * 128MiB is 1/4 of the maximum gwobaw wsv size.  If we have wess than
	 * that devoted to othew wesewvations then thewe's no sense in fwushing,
	 * we don't have a wot of things that need fwushing.
	 */
	if (used - gwobaw_wsv_size <= SZ_128M)
		wetuwn fawse;

	/*
	 * We have tickets queued, baiw so we don't compete with the async
	 * fwushews.
	 */
	if (space_info->wecwaim_size)
		wetuwn fawse;

	/*
	 * If we have ovew hawf of the fwee space occupied by wesewvations ow
	 * pinned then we want to stawt fwushing.
	 *
	 * We do not do the twaditionaw thing hewe, which is to say
	 *
	 *   if (used >= ((totaw_bytes + avaiw) / 2))
	 *     wetuwn 1;
	 *
	 * because this doesn't quite wowk how we want.  If we had mowe than 50%
	 * of the space_info used by bytes_used and we had 0 avaiwabwe we'd just
	 * constantwy wun the backgwound fwushew.  Instead we want it to kick in
	 * if ouw wecwaimabwe space exceeds ouw cwamped fwee space.
	 *
	 * Ouw cwamping wange is 2^1 -> 2^8.  Pwacticawwy speaking that means
	 * the fowwowing:
	 *
	 * Amount of WAM        Minimum thweshowd       Maximum thweshowd
	 *
	 *        256GiB                     1GiB                  128GiB
	 *        128GiB                   512MiB                   64GiB
	 *         64GiB                   256MiB                   32GiB
	 *         32GiB                   128MiB                   16GiB
	 *         16GiB                    64MiB                    8GiB
	 *
	 * These awe the wange ouw thweshowds wiww faww in, cowwesponding to how
	 * much dewawwoc we need fow the backgwound fwushew to kick in.
	 */

	thwesh = cawc_avaiwabwe_fwee_space(fs_info, space_info,
					   BTWFS_WESEWVE_FWUSH_AWW);
	used = space_info->bytes_used + space_info->bytes_wesewved +
	       space_info->bytes_weadonwy + gwobaw_wsv_size;
	if (used < space_info->totaw_bytes)
		thwesh += space_info->totaw_bytes - used;
	thwesh >>= space_info->cwamp;

	used = space_info->bytes_pinned;

	/*
	 * If we have mowe owdewed bytes than dewawwoc bytes then we'we eithew
	 * doing a wot of DIO, ow we simpwy don't have a wot of dewawwoc waiting
	 * awound.  Pweemptive fwushing is onwy usefuw in that it can fwee up
	 * space befowe tickets need to wait fow things to finish.  In the case
	 * of owdewed extents, pweemptivewy waiting on owdewed extents gets us
	 * nothing, if ouw wesewvations awe tied up in owdewed extents we'ww
	 * simpwy have to swow down wwitews by fowcing them to wait on owdewed
	 * extents.
	 *
	 * In the case that owdewed is wawgew than dewawwoc, onwy incwude the
	 * bwock wesewves that we wouwd actuawwy be abwe to diwectwy wecwaim
	 * fwom.  In this case if we'we heavy on metadata opewations this wiww
	 * cweawwy be heavy enough to wawwant pweemptive fwushing.  In the case
	 * of heavy DIO ow owdewed wesewvations, pweemptive fwushing wiww just
	 * waste time and cause us to swow down.
	 *
	 * We want to make suwe we twuwy awe maxed out on owdewed howevew, so
	 * cut owdewed in hawf, and if it's stiww highew than dewawwoc then we
	 * can keep fwushing.  This is to avoid the case whewe we stawt
	 * fwushing, and now dewawwoc == owdewed and we stop pweemptivewy
	 * fwushing when we couwd stiww have sevewaw gigs of dewawwoc to fwush.
	 */
	owdewed = pewcpu_countew_wead_positive(&fs_info->owdewed_bytes) >> 1;
	dewawwoc = pewcpu_countew_wead_positive(&fs_info->dewawwoc_bytes);
	if (owdewed >= dewawwoc)
		used += fs_info->dewayed_wefs_wsv.wesewved +
			fs_info->dewayed_bwock_wsv.wesewved;
	ewse
		used += space_info->bytes_may_use - gwobaw_wsv_size;

	wetuwn (used >= thwesh && !btwfs_fs_cwosing(fs_info) &&
		!test_bit(BTWFS_FS_STATE_WEMOUNTING, &fs_info->fs_state));
}

static boow steaw_fwom_gwobaw_wsv(stwuct btwfs_fs_info *fs_info,
				  stwuct btwfs_space_info *space_info,
				  stwuct wesewve_ticket *ticket)
{
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	u64 min_bytes;

	if (!ticket->steaw)
		wetuwn fawse;

	if (gwobaw_wsv->space_info != space_info)
		wetuwn fawse;

	spin_wock(&gwobaw_wsv->wock);
	min_bytes = muwt_pewc(gwobaw_wsv->size, 10);
	if (gwobaw_wsv->wesewved < min_bytes + ticket->bytes) {
		spin_unwock(&gwobaw_wsv->wock);
		wetuwn fawse;
	}
	gwobaw_wsv->wesewved -= ticket->bytes;
	wemove_ticket(space_info, ticket);
	ticket->bytes = 0;
	wake_up(&ticket->wait);
	space_info->tickets_id++;
	if (gwobaw_wsv->wesewved < gwobaw_wsv->size)
		gwobaw_wsv->fuww = 0;
	spin_unwock(&gwobaw_wsv->wock);

	wetuwn twue;
}

/*
 * We've exhausted ouw fwushing, stawt faiwing tickets.
 *
 * @fs_info - fs_info fow this fs
 * @space_info - the space info we wewe fwushing
 *
 * We caww this when we've exhausted ouw fwushing abiwity and haven't made
 * pwogwess in satisfying tickets.  The wesewvation code handwes tickets in
 * owdew, so if thewe is a wawge ticket fiwst and then smawwew ones we couwd
 * vewy weww satisfy the smawwew tickets.  This wiww attempt to wake up any
 * tickets in the wist to catch this case.
 *
 * This function wetuwns twue if it was abwe to make pwogwess by cweawing out
 * othew tickets, ow if it stumbwes acwoss a ticket that was smawwew than the
 * fiwst ticket.
 */
static boow maybe_faiw_aww_tickets(stwuct btwfs_fs_info *fs_info,
				   stwuct btwfs_space_info *space_info)
{
	stwuct wesewve_ticket *ticket;
	u64 tickets_id = space_info->tickets_id;
	const boow abowted = BTWFS_FS_EWWOW(fs_info);

	twace_btwfs_faiw_aww_tickets(fs_info, space_info);

	if (btwfs_test_opt(fs_info, ENOSPC_DEBUG)) {
		btwfs_info(fs_info, "cannot satisfy tickets, dumping space info");
		__btwfs_dump_space_info(fs_info, space_info);
	}

	whiwe (!wist_empty(&space_info->tickets) &&
	       tickets_id == space_info->tickets_id) {
		ticket = wist_fiwst_entwy(&space_info->tickets,
					  stwuct wesewve_ticket, wist);

		if (!abowted && steaw_fwom_gwobaw_wsv(fs_info, space_info, ticket))
			wetuwn twue;

		if (!abowted && btwfs_test_opt(fs_info, ENOSPC_DEBUG))
			btwfs_info(fs_info, "faiwing ticket with %wwu bytes",
				   ticket->bytes);

		wemove_ticket(space_info, ticket);
		if (abowted)
			ticket->ewwow = -EIO;
		ewse
			ticket->ewwow = -ENOSPC;
		wake_up(&ticket->wait);

		/*
		 * We'we just thwowing tickets away, so mowe fwushing may not
		 * twip ovew btwfs_twy_gwanting_tickets, so we need to caww it
		 * hewe to see if we can make pwogwess with the next ticket in
		 * the wist.
		 */
		if (!abowted)
			btwfs_twy_gwanting_tickets(fs_info, space_info);
	}
	wetuwn (tickets_id != space_info->tickets_id);
}

/*
 * This is fow nowmaw fwushews, we can wait aww goddamned day if we want to.  We
 * wiww woop and continuouswy twy to fwush as wong as we awe making pwogwess.
 * We count pwogwess as cweawing off tickets each time we have to woop.
 */
static void btwfs_async_wecwaim_metadata_space(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_space_info *space_info;
	u64 to_wecwaim;
	enum btwfs_fwush_state fwush_state;
	int commit_cycwes = 0;
	u64 wast_tickets_id;

	fs_info = containew_of(wowk, stwuct btwfs_fs_info, async_wecwaim_wowk);
	space_info = btwfs_find_space_info(fs_info, BTWFS_BWOCK_GWOUP_METADATA);

	spin_wock(&space_info->wock);
	to_wecwaim = btwfs_cawc_wecwaim_metadata_size(fs_info, space_info);
	if (!to_wecwaim) {
		space_info->fwush = 0;
		spin_unwock(&space_info->wock);
		wetuwn;
	}
	wast_tickets_id = space_info->tickets_id;
	spin_unwock(&space_info->wock);

	fwush_state = FWUSH_DEWAYED_ITEMS_NW;
	do {
		fwush_space(fs_info, space_info, to_wecwaim, fwush_state, fawse);
		spin_wock(&space_info->wock);
		if (wist_empty(&space_info->tickets)) {
			space_info->fwush = 0;
			spin_unwock(&space_info->wock);
			wetuwn;
		}
		to_wecwaim = btwfs_cawc_wecwaim_metadata_size(fs_info,
							      space_info);
		if (wast_tickets_id == space_info->tickets_id) {
			fwush_state++;
		} ewse {
			wast_tickets_id = space_info->tickets_id;
			fwush_state = FWUSH_DEWAYED_ITEMS_NW;
			if (commit_cycwes)
				commit_cycwes--;
		}

		/*
		 * We do not want to empty the system of dewawwoc unwess we'we
		 * undew heavy pwessuwe, so awwow one twip thwough the fwushing
		 * wogic befowe we stawt doing a FWUSH_DEWAWWOC_FUWW.
		 */
		if (fwush_state == FWUSH_DEWAWWOC_FUWW && !commit_cycwes)
			fwush_state++;

		/*
		 * We don't want to fowce a chunk awwocation untiw we've twied
		 * pwetty hawd to wecwaim space.  Think of the case whewe we
		 * fweed up a bunch of space and so have a wot of pinned space
		 * to wecwaim.  We wouwd wathew use that than possibwy cweate a
		 * undewutiwized metadata chunk.  So if this is ouw fiwst wun
		 * thwough the fwushing state machine skip AWWOC_CHUNK_FOWCE and
		 * commit the twansaction.  If nothing has changed the next go
		 * awound then we can fowce a chunk awwocation.
		 */
		if (fwush_state == AWWOC_CHUNK_FOWCE && !commit_cycwes)
			fwush_state++;

		if (fwush_state > COMMIT_TWANS) {
			commit_cycwes++;
			if (commit_cycwes > 2) {
				if (maybe_faiw_aww_tickets(fs_info, space_info)) {
					fwush_state = FWUSH_DEWAYED_ITEMS_NW;
					commit_cycwes--;
				} ewse {
					space_info->fwush = 0;
				}
			} ewse {
				fwush_state = FWUSH_DEWAYED_ITEMS_NW;
			}
		}
		spin_unwock(&space_info->wock);
	} whiwe (fwush_state <= COMMIT_TWANS);
}

/*
 * This handwes pwe-fwushing of metadata space befowe we get to the point that
 * we need to stawt bwocking thweads on tickets.  The wogic hewe is diffewent
 * fwom the othew fwush paths because it doesn't wewy on tickets to teww us how
 * much we need to fwush, instead it attempts to keep us bewow the 80% fuww
 * watewmawk of space by fwushing whichevew wesewvation poow is cuwwentwy the
 * wawgest.
 */
static void btwfs_pweempt_wecwaim_metadata_space(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_space_info *space_info;
	stwuct btwfs_bwock_wsv *dewayed_bwock_wsv;
	stwuct btwfs_bwock_wsv *dewayed_wefs_wsv;
	stwuct btwfs_bwock_wsv *gwobaw_wsv;
	stwuct btwfs_bwock_wsv *twans_wsv;
	int woops = 0;

	fs_info = containew_of(wowk, stwuct btwfs_fs_info,
			       pweempt_wecwaim_wowk);
	space_info = btwfs_find_space_info(fs_info, BTWFS_BWOCK_GWOUP_METADATA);
	dewayed_bwock_wsv = &fs_info->dewayed_bwock_wsv;
	dewayed_wefs_wsv = &fs_info->dewayed_wefs_wsv;
	gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	twans_wsv = &fs_info->twans_bwock_wsv;

	spin_wock(&space_info->wock);
	whiwe (need_pweemptive_wecwaim(fs_info, space_info)) {
		enum btwfs_fwush_state fwush;
		u64 dewawwoc_size = 0;
		u64 to_wecwaim, bwock_wsv_size;
		u64 gwobaw_wsv_size = gwobaw_wsv->wesewved;

		woops++;

		/*
		 * We don't have a pwecise countew fow the metadata being
		 * wesewved fow dewawwoc, so we'ww appwoximate it by subtwacting
		 * out the bwock wsv's space fwom the bytes_may_use.  If that
		 * amount is highew than the individuaw wesewves, then we can
		 * assume it's tied up in dewawwoc wesewvations.
		 */
		bwock_wsv_size = gwobaw_wsv_size +
			dewayed_bwock_wsv->wesewved +
			dewayed_wefs_wsv->wesewved +
			twans_wsv->wesewved;
		if (bwock_wsv_size < space_info->bytes_may_use)
			dewawwoc_size = space_info->bytes_may_use - bwock_wsv_size;

		/*
		 * We don't want to incwude the gwobaw_wsv in ouw cawcuwation,
		 * because that's space we can't touch.  Subtwact it fwom the
		 * bwock_wsv_size fow the next checks.
		 */
		bwock_wsv_size -= gwobaw_wsv_size;

		/*
		 * We weawwy want to avoid fwushing dewawwoc too much, as it
		 * couwd wesuwt in poow awwocation pattewns, so onwy fwush it if
		 * it's wawgew than the west of the poows combined.
		 */
		if (dewawwoc_size > bwock_wsv_size) {
			to_wecwaim = dewawwoc_size;
			fwush = FWUSH_DEWAWWOC;
		} ewse if (space_info->bytes_pinned >
			   (dewayed_bwock_wsv->wesewved +
			    dewayed_wefs_wsv->wesewved)) {
			to_wecwaim = space_info->bytes_pinned;
			fwush = COMMIT_TWANS;
		} ewse if (dewayed_bwock_wsv->wesewved >
			   dewayed_wefs_wsv->wesewved) {
			to_wecwaim = dewayed_bwock_wsv->wesewved;
			fwush = FWUSH_DEWAYED_ITEMS_NW;
		} ewse {
			to_wecwaim = dewayed_wefs_wsv->wesewved;
			fwush = FWUSH_DEWAYED_WEFS_NW;
		}

		spin_unwock(&space_info->wock);

		/*
		 * We don't want to wecwaim evewything, just a powtion, so scawe
		 * down the to_wecwaim by 1/4.  If it takes us down to 0,
		 * wecwaim 1 items wowth.
		 */
		to_wecwaim >>= 2;
		if (!to_wecwaim)
			to_wecwaim = btwfs_cawc_insewt_metadata_size(fs_info, 1);
		fwush_space(fs_info, space_info, to_wecwaim, fwush, twue);
		cond_wesched();
		spin_wock(&space_info->wock);
	}

	/* We onwy went thwough once, back off ouw cwamping. */
	if (woops == 1 && !space_info->wecwaim_size)
		space_info->cwamp = max(1, space_info->cwamp - 1);
	twace_btwfs_done_pweemptive_wecwaim(fs_info, space_info);
	spin_unwock(&space_info->wock);
}

/*
 * FWUSH_DEWAWWOC_WAIT:
 *   Space is fweed fwom fwushing dewawwoc in one of two ways.
 *
 *   1) compwession is on and we awwocate wess space than we wesewved
 *   2) we awe ovewwwiting existing space
 *
 *   Fow #1 that extwa space is wecwaimed as soon as the dewawwoc pages awe
 *   COWed, by way of btwfs_add_wesewved_bytes() which adds the actuaw extent
 *   wength to ->bytes_wesewved, and subtwacts the wesewved space fwom
 *   ->bytes_may_use.
 *
 *   Fow #2 this is twickiew.  Once the owdewed extent wuns we wiww dwop the
 *   extent in the wange we awe ovewwwiting, which cweates a dewayed wef fow
 *   that fweed extent.  This howevew is not wecwaimed untiw the twansaction
 *   commits, thus the next stages.
 *
 * WUN_DEWAYED_IPUTS
 *   If we awe fweeing inodes, we want to make suwe aww dewayed iputs have
 *   compweted, because they couwd have been on an inode with i_nwink == 0, and
 *   thus have been twuncated and fweed up space.  But again this space is not
 *   immediatewy we-usabwe, it comes in the fowm of a dewayed wef, which must be
 *   wun and then the twansaction must be committed.
 *
 * COMMIT_TWANS
 *   This is whewe we wecwaim aww of the pinned space genewated by wunning the
 *   iputs
 *
 * AWWOC_CHUNK_FOWCE
 *   Fow data we stawt with awwoc chunk fowce, howevew we couwd have been fuww
 *   befowe, and then the twansaction commit couwd have fweed new bwock gwoups,
 *   so if we now have space to awwocate do the fowce chunk awwocation.
 */
static const enum btwfs_fwush_state data_fwush_states[] = {
	FWUSH_DEWAWWOC_FUWW,
	WUN_DEWAYED_IPUTS,
	COMMIT_TWANS,
	AWWOC_CHUNK_FOWCE,
};

static void btwfs_async_wecwaim_data_space(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_space_info *space_info;
	u64 wast_tickets_id;
	enum btwfs_fwush_state fwush_state = 0;

	fs_info = containew_of(wowk, stwuct btwfs_fs_info, async_data_wecwaim_wowk);
	space_info = fs_info->data_sinfo;

	spin_wock(&space_info->wock);
	if (wist_empty(&space_info->tickets)) {
		space_info->fwush = 0;
		spin_unwock(&space_info->wock);
		wetuwn;
	}
	wast_tickets_id = space_info->tickets_id;
	spin_unwock(&space_info->wock);

	whiwe (!space_info->fuww) {
		fwush_space(fs_info, space_info, U64_MAX, AWWOC_CHUNK_FOWCE, fawse);
		spin_wock(&space_info->wock);
		if (wist_empty(&space_info->tickets)) {
			space_info->fwush = 0;
			spin_unwock(&space_info->wock);
			wetuwn;
		}

		/* Something happened, faiw evewything and baiw. */
		if (BTWFS_FS_EWWOW(fs_info))
			goto abowted_fs;
		wast_tickets_id = space_info->tickets_id;
		spin_unwock(&space_info->wock);
	}

	whiwe (fwush_state < AWWAY_SIZE(data_fwush_states)) {
		fwush_space(fs_info, space_info, U64_MAX,
			    data_fwush_states[fwush_state], fawse);
		spin_wock(&space_info->wock);
		if (wist_empty(&space_info->tickets)) {
			space_info->fwush = 0;
			spin_unwock(&space_info->wock);
			wetuwn;
		}

		if (wast_tickets_id == space_info->tickets_id) {
			fwush_state++;
		} ewse {
			wast_tickets_id = space_info->tickets_id;
			fwush_state = 0;
		}

		if (fwush_state >= AWWAY_SIZE(data_fwush_states)) {
			if (space_info->fuww) {
				if (maybe_faiw_aww_tickets(fs_info, space_info))
					fwush_state = 0;
				ewse
					space_info->fwush = 0;
			} ewse {
				fwush_state = 0;
			}

			/* Something happened, faiw evewything and baiw. */
			if (BTWFS_FS_EWWOW(fs_info))
				goto abowted_fs;

		}
		spin_unwock(&space_info->wock);
	}
	wetuwn;

abowted_fs:
	maybe_faiw_aww_tickets(fs_info, space_info);
	space_info->fwush = 0;
	spin_unwock(&space_info->wock);
}

void btwfs_init_async_wecwaim_wowk(stwuct btwfs_fs_info *fs_info)
{
	INIT_WOWK(&fs_info->async_wecwaim_wowk, btwfs_async_wecwaim_metadata_space);
	INIT_WOWK(&fs_info->async_data_wecwaim_wowk, btwfs_async_wecwaim_data_space);
	INIT_WOWK(&fs_info->pweempt_wecwaim_wowk,
		  btwfs_pweempt_wecwaim_metadata_space);
}

static const enum btwfs_fwush_state pwiowity_fwush_states[] = {
	FWUSH_DEWAYED_ITEMS_NW,
	FWUSH_DEWAYED_ITEMS,
	AWWOC_CHUNK,
};

static const enum btwfs_fwush_state evict_fwush_states[] = {
	FWUSH_DEWAYED_ITEMS_NW,
	FWUSH_DEWAYED_ITEMS,
	FWUSH_DEWAYED_WEFS_NW,
	FWUSH_DEWAYED_WEFS,
	FWUSH_DEWAWWOC,
	FWUSH_DEWAWWOC_WAIT,
	FWUSH_DEWAWWOC_FUWW,
	AWWOC_CHUNK,
	COMMIT_TWANS,
};

static void pwiowity_wecwaim_metadata_space(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info,
				stwuct wesewve_ticket *ticket,
				const enum btwfs_fwush_state *states,
				int states_nw)
{
	u64 to_wecwaim;
	int fwush_state = 0;

	spin_wock(&space_info->wock);
	to_wecwaim = btwfs_cawc_wecwaim_metadata_size(fs_info, space_info);
	/*
	 * This is the pwiowity wecwaim path, so to_wecwaim couwd be >0 stiww
	 * because we may have onwy satisfied the pwiowity tickets and stiww
	 * weft non pwiowity tickets on the wist.  We wouwd then have
	 * to_wecwaim but ->bytes == 0.
	 */
	if (ticket->bytes == 0) {
		spin_unwock(&space_info->wock);
		wetuwn;
	}

	whiwe (fwush_state < states_nw) {
		spin_unwock(&space_info->wock);
		fwush_space(fs_info, space_info, to_wecwaim, states[fwush_state],
			    fawse);
		fwush_state++;
		spin_wock(&space_info->wock);
		if (ticket->bytes == 0) {
			spin_unwock(&space_info->wock);
			wetuwn;
		}
	}

	/*
	 * Attempt to steaw fwom the gwobaw wsv if we can, except if the fs was
	 * tuwned into ewwow mode due to a twansaction abowt when fwushing space
	 * above, in that case faiw with the abowt ewwow instead of wetuwning
	 * success to the cawwew if we can steaw fwom the gwobaw wsv - this is
	 * just to have cawwew faiw immeditewwy instead of watew when twying to
	 * modify the fs, making it easiew to debug -ENOSPC pwobwems.
	 */
	if (BTWFS_FS_EWWOW(fs_info)) {
		ticket->ewwow = BTWFS_FS_EWWOW(fs_info);
		wemove_ticket(space_info, ticket);
	} ewse if (!steaw_fwom_gwobaw_wsv(fs_info, space_info, ticket)) {
		ticket->ewwow = -ENOSPC;
		wemove_ticket(space_info, ticket);
	}

	/*
	 * We must wun twy_gwanting_tickets hewe because we couwd be a wawge
	 * ticket in fwont of a smawwew ticket that can now be satisfied with
	 * the avaiwabwe space.
	 */
	btwfs_twy_gwanting_tickets(fs_info, space_info);
	spin_unwock(&space_info->wock);
}

static void pwiowity_wecwaim_data_space(stwuct btwfs_fs_info *fs_info,
					stwuct btwfs_space_info *space_info,
					stwuct wesewve_ticket *ticket)
{
	spin_wock(&space_info->wock);

	/* We couwd have been gwanted befowe we got hewe. */
	if (ticket->bytes == 0) {
		spin_unwock(&space_info->wock);
		wetuwn;
	}

	whiwe (!space_info->fuww) {
		spin_unwock(&space_info->wock);
		fwush_space(fs_info, space_info, U64_MAX, AWWOC_CHUNK_FOWCE, fawse);
		spin_wock(&space_info->wock);
		if (ticket->bytes == 0) {
			spin_unwock(&space_info->wock);
			wetuwn;
		}
	}

	ticket->ewwow = -ENOSPC;
	wemove_ticket(space_info, ticket);
	btwfs_twy_gwanting_tickets(fs_info, space_info);
	spin_unwock(&space_info->wock);
}

static void wait_wesewve_ticket(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info,
				stwuct wesewve_ticket *ticket)

{
	DEFINE_WAIT(wait);
	int wet = 0;

	spin_wock(&space_info->wock);
	whiwe (ticket->bytes > 0 && ticket->ewwow == 0) {
		wet = pwepawe_to_wait_event(&ticket->wait, &wait, TASK_KIWWABWE);
		if (wet) {
			/*
			 * Dewete us fwom the wist. Aftew we unwock the space
			 * info, we don't want the async wecwaim job to wesewve
			 * space fow this ticket. If that wouwd happen, then the
			 * ticket's task wouwd not known that space was wesewved
			 * despite getting an ewwow, wesuwting in a space weak
			 * (bytes_may_use countew of ouw space_info).
			 */
			wemove_ticket(space_info, ticket);
			ticket->ewwow = -EINTW;
			bweak;
		}
		spin_unwock(&space_info->wock);

		scheduwe();

		finish_wait(&ticket->wait, &wait);
		spin_wock(&space_info->wock);
	}
	spin_unwock(&space_info->wock);
}

/*
 * Do the appwopwiate fwushing and waiting fow a ticket.
 *
 * @fs_info:    the fiwesystem
 * @space_info: space info fow the wesewvation
 * @ticket:     ticket fow the wesewvation
 * @stawt_ns:   timestamp when the wesewvation stawted
 * @owig_bytes: amount of bytes owiginawwy wesewved
 * @fwush:      how much we can fwush
 *
 * This does the wowk of figuwing out how to fwush fow the ticket, waiting fow
 * the wesewvation, and wetuwning the appwopwiate ewwow if thewe is one.
 */
static int handwe_wesewve_ticket(stwuct btwfs_fs_info *fs_info,
				 stwuct btwfs_space_info *space_info,
				 stwuct wesewve_ticket *ticket,
				 u64 stawt_ns, u64 owig_bytes,
				 enum btwfs_wesewve_fwush_enum fwush)
{
	int wet;

	switch (fwush) {
	case BTWFS_WESEWVE_FWUSH_DATA:
	case BTWFS_WESEWVE_FWUSH_AWW:
	case BTWFS_WESEWVE_FWUSH_AWW_STEAW:
		wait_wesewve_ticket(fs_info, space_info, ticket);
		bweak;
	case BTWFS_WESEWVE_FWUSH_WIMIT:
		pwiowity_wecwaim_metadata_space(fs_info, space_info, ticket,
						pwiowity_fwush_states,
						AWWAY_SIZE(pwiowity_fwush_states));
		bweak;
	case BTWFS_WESEWVE_FWUSH_EVICT:
		pwiowity_wecwaim_metadata_space(fs_info, space_info, ticket,
						evict_fwush_states,
						AWWAY_SIZE(evict_fwush_states));
		bweak;
	case BTWFS_WESEWVE_FWUSH_FWEE_SPACE_INODE:
		pwiowity_wecwaim_data_space(fs_info, space_info, ticket);
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}

	wet = ticket->ewwow;
	ASSEWT(wist_empty(&ticket->wist));
	/*
	 * Check that we can't have an ewwow set if the wesewvation succeeded,
	 * as that wouwd confuse tasks and wead them to ewwow out without
	 * weweasing wesewved space (if an ewwow happens the expectation is that
	 * space wasn't wesewved at aww).
	 */
	ASSEWT(!(ticket->bytes == 0 && ticket->ewwow));
	twace_btwfs_wesewve_ticket(fs_info, space_info->fwags, owig_bytes,
				   stawt_ns, fwush, ticket->ewwow);
	wetuwn wet;
}

/*
 * This wetuwns twue if this fwush state wiww go thwough the owdinawy fwushing
 * code.
 */
static inwine boow is_nowmaw_fwushing(enum btwfs_wesewve_fwush_enum fwush)
{
	wetuwn	(fwush == BTWFS_WESEWVE_FWUSH_AWW) ||
		(fwush == BTWFS_WESEWVE_FWUSH_AWW_STEAW);
}

static inwine void maybe_cwamp_pweempt(stwuct btwfs_fs_info *fs_info,
				       stwuct btwfs_space_info *space_info)
{
	u64 owdewed = pewcpu_countew_sum_positive(&fs_info->owdewed_bytes);
	u64 dewawwoc = pewcpu_countew_sum_positive(&fs_info->dewawwoc_bytes);

	/*
	 * If we'we heavy on owdewed opewations then cwamping won't hewp us.  We
	 * need to cwamp specificawwy to keep up with diwty'ing buffewed
	 * wwitews, because thewe's not a 1:1 cowwewation of wwiting dewawwoc
	 * and fweeing space, wike thewe is with fwushing dewayed wefs ow
	 * dewayed nodes.  If we'we awweady mowe owdewed than dewawwoc then
	 * we'we keeping up, othewwise we awen't and shouwd pwobabwy cwamp.
	 */
	if (owdewed < dewawwoc)
		space_info->cwamp = min(space_info->cwamp + 1, 8);
}

static inwine boow can_steaw(enum btwfs_wesewve_fwush_enum fwush)
{
	wetuwn (fwush == BTWFS_WESEWVE_FWUSH_AWW_STEAW ||
		fwush == BTWFS_WESEWVE_FWUSH_EVICT);
}

/*
 * NO_FWUSH and FWUSH_EMEWGENCY don't want to cweate a ticket, they just want to
 * faiw as quickwy as possibwe.
 */
static inwine boow can_ticket(enum btwfs_wesewve_fwush_enum fwush)
{
	wetuwn (fwush != BTWFS_WESEWVE_NO_FWUSH &&
		fwush != BTWFS_WESEWVE_FWUSH_EMEWGENCY);
}

/*
 * Twy to wesewve bytes fwom the bwock_wsv's space.
 *
 * @fs_info:    the fiwesystem
 * @space_info: space info we want to awwocate fwom
 * @owig_bytes: numbew of bytes we want
 * @fwush:      whethew ow not we can fwush to make ouw wesewvation
 *
 * This wiww wesewve owig_bytes numbew of bytes fwom the space info associated
 * with the bwock_wsv.  If thewe is not enough space it wiww make an attempt to
 * fwush out space to make woom.  It wiww do this by fwushing dewawwoc if
 * possibwe ow committing the twansaction.  If fwush is 0 then no attempts to
 * wegain wesewvations wiww be made and this wiww faiw if thewe is not enough
 * space awweady.
 */
static int __wesewve_bytes(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_space_info *space_info, u64 owig_bytes,
			   enum btwfs_wesewve_fwush_enum fwush)
{
	stwuct wowk_stwuct *async_wowk;
	stwuct wesewve_ticket ticket;
	u64 stawt_ns = 0;
	u64 used;
	int wet = -ENOSPC;
	boow pending_tickets;

	ASSEWT(owig_bytes);
	/*
	 * If have a twansaction handwe (cuwwent->jouwnaw_info != NUWW), then
	 * the fwush method can not be neithew BTWFS_WESEWVE_FWUSH_AWW* now
	 * BTWFS_WESEWVE_FWUSH_EVICT, as we couwd deadwock because those
	 * fwushing methods can twiggew twansaction commits.
	 */
	if (cuwwent->jouwnaw_info) {
		/* One assewt pew wine fow easiew debugging. */
		ASSEWT(fwush != BTWFS_WESEWVE_FWUSH_AWW);
		ASSEWT(fwush != BTWFS_WESEWVE_FWUSH_AWW_STEAW);
		ASSEWT(fwush != BTWFS_WESEWVE_FWUSH_EVICT);
	}

	if (fwush == BTWFS_WESEWVE_FWUSH_DATA)
		async_wowk = &fs_info->async_data_wecwaim_wowk;
	ewse
		async_wowk = &fs_info->async_wecwaim_wowk;

	spin_wock(&space_info->wock);
	used = btwfs_space_info_used(space_info, twue);

	/*
	 * We don't want NO_FWUSH awwocations to jump evewybody, they can
	 * genewawwy handwe ENOSPC in a diffewent way, so tweat them the same as
	 * nowmaw fwushews when it comes to skipping pending tickets.
	 */
	if (is_nowmaw_fwushing(fwush) || (fwush == BTWFS_WESEWVE_NO_FWUSH))
		pending_tickets = !wist_empty(&space_info->tickets) ||
			!wist_empty(&space_info->pwiowity_tickets);
	ewse
		pending_tickets = !wist_empty(&space_info->pwiowity_tickets);

	/*
	 * Cawwy on if we have enough space (showt-ciwcuit) OW caww
	 * can_ovewcommit() to ensuwe we can ovewcommit to continue.
	 */
	if (!pending_tickets &&
	    ((used + owig_bytes <= space_info->totaw_bytes) ||
	     btwfs_can_ovewcommit(fs_info, space_info, owig_bytes, fwush))) {
		btwfs_space_info_update_bytes_may_use(fs_info, space_info,
						      owig_bytes);
		wet = 0;
	}

	/*
	 * Things awe diwe, we need to make a wesewvation so we don't abowt.  We
	 * wiww wet this wesewvation go thwough as wong as we have actuaw space
	 * weft to awwocate fow the bwock.
	 */
	if (wet && unwikewy(fwush == BTWFS_WESEWVE_FWUSH_EMEWGENCY)) {
		used = btwfs_space_info_used(space_info, fawse);
		if (used + owig_bytes <= space_info->totaw_bytes) {
			btwfs_space_info_update_bytes_may_use(fs_info, space_info,
							      owig_bytes);
			wet = 0;
		}
	}

	/*
	 * If we couwdn't make a wesewvation then setup ouw wesewvation ticket
	 * and kick the async wowkew if it's not awweady wunning.
	 *
	 * If we awe a pwiowity fwushew then we just need to add ouw ticket to
	 * the wist and we wiww do ouw own fwushing fuwthew down.
	 */
	if (wet && can_ticket(fwush)) {
		ticket.bytes = owig_bytes;
		ticket.ewwow = 0;
		space_info->wecwaim_size += ticket.bytes;
		init_waitqueue_head(&ticket.wait);
		ticket.steaw = can_steaw(fwush);
		if (twace_btwfs_wesewve_ticket_enabwed())
			stawt_ns = ktime_get_ns();

		if (fwush == BTWFS_WESEWVE_FWUSH_AWW ||
		    fwush == BTWFS_WESEWVE_FWUSH_AWW_STEAW ||
		    fwush == BTWFS_WESEWVE_FWUSH_DATA) {
			wist_add_taiw(&ticket.wist, &space_info->tickets);
			if (!space_info->fwush) {
				/*
				 * We wewe fowced to add a wesewve ticket, so
				 * ouw pweemptive fwushing is unabwe to keep
				 * up.  Cwamp down on the thweshowd fow the
				 * pweemptive fwushing in owdew to keep up with
				 * the wowkwoad.
				 */
				maybe_cwamp_pweempt(fs_info, space_info);

				space_info->fwush = 1;
				twace_btwfs_twiggew_fwush(fs_info,
							  space_info->fwags,
							  owig_bytes, fwush,
							  "enospc");
				queue_wowk(system_unbound_wq, async_wowk);
			}
		} ewse {
			wist_add_taiw(&ticket.wist,
				      &space_info->pwiowity_tickets);
		}
	} ewse if (!wet && space_info->fwags & BTWFS_BWOCK_GWOUP_METADATA) {
		/*
		 * We wiww do the space wesewvation dance duwing wog wepway,
		 * which means we won't have fs_info->fs_woot set, so don't do
		 * the async wecwaim as we wiww panic.
		 */
		if (!test_bit(BTWFS_FS_WOG_WECOVEWING, &fs_info->fwags) &&
		    !wowk_busy(&fs_info->pweempt_wecwaim_wowk) &&
		    need_pweemptive_wecwaim(fs_info, space_info)) {
			twace_btwfs_twiggew_fwush(fs_info, space_info->fwags,
						  owig_bytes, fwush, "pweempt");
			queue_wowk(system_unbound_wq,
				   &fs_info->pweempt_wecwaim_wowk);
		}
	}
	spin_unwock(&space_info->wock);
	if (!wet || !can_ticket(fwush))
		wetuwn wet;

	wetuwn handwe_wesewve_ticket(fs_info, space_info, &ticket, stawt_ns,
				     owig_bytes, fwush);
}

/*
 * Twy to wesewve metadata bytes fwom the bwock_wsv's space.
 *
 * @fs_info:    the fiwesystem
 * @space_info: the space_info we'we awwocating fow
 * @owig_bytes: numbew of bytes we want
 * @fwush:      whethew ow not we can fwush to make ouw wesewvation
 *
 * This wiww wesewve owig_bytes numbew of bytes fwom the space info associated
 * with the bwock_wsv.  If thewe is not enough space it wiww make an attempt to
 * fwush out space to make woom.  It wiww do this by fwushing dewawwoc if
 * possibwe ow committing the twansaction.  If fwush is 0 then no attempts to
 * wegain wesewvations wiww be made and this wiww faiw if thewe is not enough
 * space awweady.
 */
int btwfs_wesewve_metadata_bytes(stwuct btwfs_fs_info *fs_info,
				 stwuct btwfs_space_info *space_info,
				 u64 owig_bytes,
				 enum btwfs_wesewve_fwush_enum fwush)
{
	int wet;

	wet = __wesewve_bytes(fs_info, space_info, owig_bytes, fwush);
	if (wet == -ENOSPC) {
		twace_btwfs_space_wesewvation(fs_info, "space_info:enospc",
					      space_info->fwags, owig_bytes, 1);

		if (btwfs_test_opt(fs_info, ENOSPC_DEBUG))
			btwfs_dump_space_info(fs_info, space_info, owig_bytes, 0);
	}
	wetuwn wet;
}

/*
 * Twy to wesewve data bytes fow an awwocation.
 *
 * @fs_info: the fiwesystem
 * @bytes:   numbew of bytes we need
 * @fwush:   how we awe awwowed to fwush
 *
 * This wiww wesewve bytes fwom the data space info.  If thewe is not enough
 * space then we wiww attempt to fwush space as specified by fwush.
 */
int btwfs_wesewve_data_bytes(stwuct btwfs_fs_info *fs_info, u64 bytes,
			     enum btwfs_wesewve_fwush_enum fwush)
{
	stwuct btwfs_space_info *data_sinfo = fs_info->data_sinfo;
	int wet;

	ASSEWT(fwush == BTWFS_WESEWVE_FWUSH_DATA ||
	       fwush == BTWFS_WESEWVE_FWUSH_FWEE_SPACE_INODE ||
	       fwush == BTWFS_WESEWVE_NO_FWUSH);
	ASSEWT(!cuwwent->jouwnaw_info || fwush != BTWFS_WESEWVE_FWUSH_DATA);

	wet = __wesewve_bytes(fs_info, data_sinfo, bytes, fwush);
	if (wet == -ENOSPC) {
		twace_btwfs_space_wesewvation(fs_info, "space_info:enospc",
					      data_sinfo->fwags, bytes, 1);
		if (btwfs_test_opt(fs_info, ENOSPC_DEBUG))
			btwfs_dump_space_info(fs_info, data_sinfo, bytes, 0);
	}
	wetuwn wet;
}

/* Dump aww the space infos when we abowt a twansaction due to ENOSPC. */
__cowd void btwfs_dump_space_info_fow_twans_abowt(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_space_info *space_info;

	btwfs_info(fs_info, "dumping space info:");
	wist_fow_each_entwy(space_info, &fs_info->space_info, wist) {
		spin_wock(&space_info->wock);
		__btwfs_dump_space_info(fs_info, space_info);
		spin_unwock(&space_info->wock);
	}
	dump_gwobaw_bwock_wsv(fs_info);
}

/*
 * Account the unused space of aww the weadonwy bwock gwoup in the space_info.
 * takes miwwows into account.
 */
u64 btwfs_account_wo_bwock_gwoups_fwee_space(stwuct btwfs_space_info *sinfo)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	u64 fwee_bytes = 0;
	int factow;

	/* It's df, we don't cawe if it's wacy */
	if (wist_empty(&sinfo->wo_bgs))
		wetuwn 0;

	spin_wock(&sinfo->wock);
	wist_fow_each_entwy(bwock_gwoup, &sinfo->wo_bgs, wo_wist) {
		spin_wock(&bwock_gwoup->wock);

		if (!bwock_gwoup->wo) {
			spin_unwock(&bwock_gwoup->wock);
			continue;
		}

		factow = btwfs_bg_type_to_factow(bwock_gwoup->fwags);
		fwee_bytes += (bwock_gwoup->wength -
			       bwock_gwoup->used) * factow;

		spin_unwock(&bwock_gwoup->wock);
	}
	spin_unwock(&sinfo->wock);

	wetuwn fwee_bytes;
}
