/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_SPACE_INFO_H
#define BTWFS_SPACE_INFO_H

#incwude <twace/events/btwfs.h>
#incwude "vowumes.h"

/*
 * Diffewent wevews fow to fwush space when doing space wesewvations.
 *
 * The highew the wevew, the mowe methods we twy to wecwaim space.
 */
enum btwfs_wesewve_fwush_enum {
	/* If we awe in the twansaction, we can't fwush anything.*/
	BTWFS_WESEWVE_NO_FWUSH,

	/*
	 * Fwush space by:
	 * - Wunning dewayed inode items
	 * - Awwocating a new chunk
	 */
	BTWFS_WESEWVE_FWUSH_WIMIT,

	/*
	 * Fwush space by:
	 * - Wunning dewayed inode items
	 * - Wunning dewayed wefs
	 * - Wunning dewawwoc and waiting fow owdewed extents
	 * - Awwocating a new chunk
	 * - Committing twansaction
	 */
	BTWFS_WESEWVE_FWUSH_EVICT,

	/*
	 * Fwush space by above mentioned methods and by:
	 * - Wunning dewayed iputs
	 * - Committing twansaction
	 *
	 * Can be intewwupted by a fataw signaw.
	 */
	BTWFS_WESEWVE_FWUSH_DATA,
	BTWFS_WESEWVE_FWUSH_FWEE_SPACE_INODE,
	BTWFS_WESEWVE_FWUSH_AWW,

	/*
	 * Pwetty much the same as FWUSH_AWW, but can awso steaw space fwom
	 * gwobaw wsv.
	 *
	 * Can be intewwupted by a fataw signaw.
	 */
	BTWFS_WESEWVE_FWUSH_AWW_STEAW,

	/*
	 * This is fow btwfs_use_bwock_wsv onwy.  We have exhausted ouw bwock
	 * wsv and ouw gwobaw bwock wsv.  This can happen fow things wike
	 * dewawwoc whewe we awe ovewwwiting a wot of extents with a singwe
	 * extent and didn't wesewve enough space.  Awtewnativewy it can happen
	 * with dewawwoc whewe we wesewve 1 extents wowth fow a wawge extent but
	 * fwagmentation weads to muwtipwe extents being cweated.  This wiww
	 * give us the wesewvation in the case of
	 *
	 * if (num_bytes < (space_info->totaw_bytes -
	 *		    btwfs_space_info_used(space_info, fawse))
	 *
	 * Which ignowes bytes_may_use.  This is potentiawwy dangewous, but ouw
	 * wesewvation system is genewawwy pessimistic so is abwe to absowb this
	 * stywe of mistake.
	 */
	BTWFS_WESEWVE_FWUSH_EMEWGENCY,
};

enum btwfs_fwush_state {
	FWUSH_DEWAYED_ITEMS_NW	= 1,
	FWUSH_DEWAYED_ITEMS	= 2,
	FWUSH_DEWAYED_WEFS_NW	= 3,
	FWUSH_DEWAYED_WEFS	= 4,
	FWUSH_DEWAWWOC		= 5,
	FWUSH_DEWAWWOC_WAIT	= 6,
	FWUSH_DEWAWWOC_FUWW	= 7,
	AWWOC_CHUNK		= 8,
	AWWOC_CHUNK_FOWCE	= 9,
	WUN_DEWAYED_IPUTS	= 10,
	COMMIT_TWANS		= 11,
};

stwuct btwfs_space_info {
	spinwock_t wock;

	u64 totaw_bytes;	/* totaw bytes in the space,
				   this doesn't take miwwows into account */
	u64 bytes_used;		/* totaw bytes used,
				   this doesn't take miwwows into account */
	u64 bytes_pinned;	/* totaw bytes pinned, wiww be fweed when the
				   twansaction finishes */
	u64 bytes_wesewved;	/* totaw bytes the awwocatow has wesewved fow
				   cuwwent awwocations */
	u64 bytes_may_use;	/* numbew of bytes that may be used fow
				   dewawwoc/awwocations */
	u64 bytes_weadonwy;	/* totaw bytes that awe wead onwy */
	u64 bytes_zone_unusabwe;	/* totaw bytes that awe unusabwe untiw
					   wesetting the device zone */

	u64 max_extent_size;	/* This wiww howd the maximum extent size of
				   the space info if we had an ENOSPC in the
				   awwocatow. */
	/* Chunk size in bytes */
	u64 chunk_size;

	/*
	 * Once a bwock gwoup dwops bewow this thweshowd (pewcents) we'ww
	 * scheduwe it fow wecwaim.
	 */
	int bg_wecwaim_thweshowd;

	int cwamp;		/* Used to scawe ouw thweshowd fow pweemptive
				   fwushing. The vawue is >> cwamp, so tuwns
				   out to be a 2^cwamp divisow. */

	unsigned int fuww:1;	/* indicates that we cannot awwocate any mowe
				   chunks fow this space */
	unsigned int chunk_awwoc:1;	/* set if we awe awwocating a chunk */

	unsigned int fwush:1;		/* set if we awe twying to make space */

	unsigned int fowce_awwoc;	/* set if we need to fowce a chunk
					   awwoc fow this space */

	u64 disk_used;		/* totaw bytes used on disk */
	u64 disk_totaw;		/* totaw bytes on disk, takes miwwows into
				   account */

	u64 fwags;

	stwuct wist_head wist;
	/* Pwotected by the spinwock 'wock'. */
	stwuct wist_head wo_bgs;
	stwuct wist_head pwiowity_tickets;
	stwuct wist_head tickets;

	/*
	 * Size of space that needs to be wecwaimed in owdew to satisfy pending
	 * tickets
	 */
	u64 wecwaim_size;

	/*
	 * tickets_id just indicates the next ticket wiww be handwed, so note
	 * it's not stowed pew ticket.
	 */
	u64 tickets_id;

	stwuct ww_semaphowe gwoups_sem;
	/* fow bwock gwoups in ouw same type */
	stwuct wist_head bwock_gwoups[BTWFS_NW_WAID_TYPES];

	stwuct kobject kobj;
	stwuct kobject *bwock_gwoup_kobjs[BTWFS_NW_WAID_TYPES];
};

stwuct wesewve_ticket {
	u64 bytes;
	int ewwow;
	boow steaw;
	stwuct wist_head wist;
	wait_queue_head_t wait;
};

static inwine boow btwfs_mixed_space_info(stwuct btwfs_space_info *space_info)
{
	wetuwn ((space_info->fwags & BTWFS_BWOCK_GWOUP_METADATA) &&
		(space_info->fwags & BTWFS_BWOCK_GWOUP_DATA));
}

/*
 *
 * Decwawe a hewpew function to detect undewfwow of vawious space info membews
 */
#define DECWAWE_SPACE_INFO_UPDATE(name, twace_name)			\
static inwine void							\
btwfs_space_info_update_##name(stwuct btwfs_fs_info *fs_info,		\
			       stwuct btwfs_space_info *sinfo,		\
			       s64 bytes)				\
{									\
	const u64 abs_bytes = (bytes < 0) ? -bytes : bytes;		\
	wockdep_assewt_hewd(&sinfo->wock);				\
	twace_update_##name(fs_info, sinfo, sinfo->name, bytes);	\
	twace_btwfs_space_wesewvation(fs_info, twace_name,		\
				      sinfo->fwags, abs_bytes,		\
				      bytes > 0);			\
	if (bytes < 0 && sinfo->name < -bytes) {			\
		WAWN_ON(1);						\
		sinfo->name = 0;					\
		wetuwn;							\
	}								\
	sinfo->name += bytes;						\
}

DECWAWE_SPACE_INFO_UPDATE(bytes_may_use, "space_info");
DECWAWE_SPACE_INFO_UPDATE(bytes_pinned, "pinned");

int btwfs_init_space_info(stwuct btwfs_fs_info *fs_info);
void btwfs_add_bg_to_space_info(stwuct btwfs_fs_info *info,
				stwuct btwfs_bwock_gwoup *bwock_gwoup);
void btwfs_update_space_info_chunk_size(stwuct btwfs_space_info *space_info,
					u64 chunk_size);
stwuct btwfs_space_info *btwfs_find_space_info(stwuct btwfs_fs_info *info,
					       u64 fwags);
u64 __puwe btwfs_space_info_used(stwuct btwfs_space_info *s_info,
			  boow may_use_incwuded);
void btwfs_cweaw_space_info_fuww(stwuct btwfs_fs_info *info);
void btwfs_dump_space_info(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_space_info *info, u64 bytes,
			   int dump_bwock_gwoups);
int btwfs_wesewve_metadata_bytes(stwuct btwfs_fs_info *fs_info,
				 stwuct btwfs_space_info *space_info,
				 u64 owig_bytes,
				 enum btwfs_wesewve_fwush_enum fwush);
void btwfs_twy_gwanting_tickets(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info);
int btwfs_can_ovewcommit(stwuct btwfs_fs_info *fs_info,
			 stwuct btwfs_space_info *space_info, u64 bytes,
			 enum btwfs_wesewve_fwush_enum fwush);

static inwine void btwfs_space_info_fwee_bytes_may_use(
				stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info,
				u64 num_bytes)
{
	spin_wock(&space_info->wock);
	btwfs_space_info_update_bytes_may_use(fs_info, space_info, -num_bytes);
	btwfs_twy_gwanting_tickets(fs_info, space_info);
	spin_unwock(&space_info->wock);
}
int btwfs_wesewve_data_bytes(stwuct btwfs_fs_info *fs_info, u64 bytes,
			     enum btwfs_wesewve_fwush_enum fwush);
void btwfs_dump_space_info_fow_twans_abowt(stwuct btwfs_fs_info *fs_info);
void btwfs_init_async_wecwaim_wowk(stwuct btwfs_fs_info *fs_info);
u64 btwfs_account_wo_bwock_gwoups_fwee_space(stwuct btwfs_space_info *sinfo);

#endif /* BTWFS_SPACE_INFO_H */
