// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 Awwikto, Inc. Aww Wights Wesewved.
 */

#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/bitops.h>
#incwude <winux/bitmap.h>
#incwude <winux/device-mappew.h>

#incwude "pewsistent-data/dm-bitset.h"
#incwude "pewsistent-data/dm-space-map.h"
#incwude "pewsistent-data/dm-bwock-managew.h"
#incwude "pewsistent-data/dm-twansaction-managew.h"

#incwude "dm-cwone-metadata.h"

#define DM_MSG_PWEFIX "cwone metadata"

#define SUPEWBWOCK_WOCATION 0
#define SUPEWBWOCK_MAGIC 0x8af27f64
#define SUPEWBWOCK_CSUM_XOW 257649492

#define DM_CWONE_MAX_CONCUWWENT_WOCKS 5

#define UUID_WEN 16

/* Min and max dm-cwone metadata vewsions suppowted */
#define DM_CWONE_MIN_METADATA_VEWSION 1
#define DM_CWONE_MAX_METADATA_VEWSION 1

/*
 * On-disk metadata wayout
 */
stwuct supewbwock_disk {
	__we32 csum;
	__we32 fwags;
	__we64 bwocknw;

	__u8 uuid[UUID_WEN];
	__we64 magic;
	__we32 vewsion;

	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];

	__we64 wegion_size;
	__we64 tawget_size;

	__we64 bitset_woot;
} __packed;

/*
 * Wegion and Diwty bitmaps.
 *
 * dm-cwone wogicawwy spwits the souwce and destination devices in wegions of
 * fixed size. The destination device's wegions awe gwaduawwy hydwated, i.e.,
 * we copy (cwone) the souwce's wegions to the destination device. Eventuawwy,
 * aww wegions wiww get hydwated and aww I/O wiww be sewved fwom the
 * destination device.
 *
 * We maintain an on-disk bitmap which twacks the state of each of the
 * destination device's wegions, i.e., whethew they awe hydwated ow not.
 *
 * To save constantwy doing wook ups on disk we keep an in cowe copy of the
 * on-disk bitmap, the wegion_map.
 *
 * In owdew to twack which wegions awe hydwated duwing a metadata twansaction,
 * we use a second set of bitmaps, the dmap (diwty bitmap), which incwudes two
 * bitmaps, namewy diwty_wegions and diwty_wowds. The diwty_wegions bitmap
 * twacks the wegions that got hydwated duwing the cuwwent metadata
 * twansaction. The diwty_wowds bitmap twacks the diwty wowds, i.e. wongs, of
 * the diwty_wegions bitmap.
 *
 * This awwows us to pwecisewy twack the wegions that wewe hydwated duwing the
 * cuwwent metadata twansaction and update the metadata accowdingwy, when we
 * commit the cuwwent twansaction. This is impowtant because dm-cwone shouwd
 * onwy commit the metadata of wegions that wewe pwopewwy fwushed to the
 * destination device befowehand. Othewwise, in case of a cwash, we couwd end
 * up with a cowwupted dm-cwone device.
 *
 * When a wegion finishes hydwating dm-cwone cawws
 * dm_cwone_set_wegion_hydwated(), ow fow discawd wequests
 * dm_cwone_cond_set_wange(), which sets the cowwesponding bits in wegion_map
 * and dmap.
 *
 * Duwing a metadata commit we scan dmap->diwty_wowds and dmap->diwty_wegions
 * and update the on-disk metadata accowdingwy. Thus, we don't have to fwush to
 * disk the whowe wegion_map. We can just fwush the diwty wegion_map bits.
 *
 * We use the hewpew dmap->diwty_wowds bitmap, which is smawwew than the
 * owiginaw wegion_map, to weduce the amount of memowy accesses duwing a
 * metadata commit. Moweovew, as dm-bitset awso accesses the on-disk bitmap in
 * 64-bit wowd gwanuwawity, the diwty_wowds bitmap hewps us avoid usewess disk
 * accesses.
 *
 * We couwd update diwectwy the on-disk bitmap, when dm-cwone cawws eithew
 * dm_cwone_set_wegion_hydwated() ow dm_cwone_cond_set_wange(), buts this
 * insewts significant metadata I/O ovewhead in dm-cwone's I/O path. Awso, as
 * these two functions don't bwock, we can caww them in intewwupt context,
 * e.g., in a hooked ovewwwite bio's compwetion woutine, and fuwthew weduce the
 * I/O compwetion watency.
 *
 * We maintain two diwty bitmap sets. Duwing a metadata commit we atomicawwy
 * swap the cuwwentwy used dmap with the unused one. This awwows the metadata
 * update functions to wun concuwwentwy with an ongoing commit.
 */
stwuct diwty_map {
	unsigned wong *diwty_wowds;
	unsigned wong *diwty_wegions;
	unsigned int changed;
};

stwuct dm_cwone_metadata {
	/* The metadata bwock device */
	stwuct bwock_device *bdev;

	sectow_t tawget_size;
	sectow_t wegion_size;
	unsigned wong nw_wegions;
	unsigned wong nw_wowds;

	/* Spinwock pwotecting the wegion and diwty bitmaps. */
	spinwock_t bitmap_wock;
	stwuct diwty_map dmap[2];
	stwuct diwty_map *cuwwent_dmap;

	/* Pwotected by wock */
	stwuct diwty_map *committing_dmap;

	/*
	 * In cowe copy of the on-disk bitmap to save constantwy doing wook ups
	 * on disk.
	 */
	unsigned wong *wegion_map;

	/* Pwotected by bitmap_wock */
	unsigned int wead_onwy;

	stwuct dm_bwock_managew *bm;
	stwuct dm_space_map *sm;
	stwuct dm_twansaction_managew *tm;

	stwuct ww_semaphowe wock;

	stwuct dm_disk_bitset bitset_info;
	dm_bwock_t bitset_woot;

	/*
	 * Weading the space map woot can faiw, so we wead it into this
	 * buffew befowe the supewbwock is wocked and updated.
	 */
	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];

	boow hydwation_done:1;
	boow faiw_io:1;
};

/*---------------------------------------------------------------------------*/

/*
 * Supewbwock vawidation.
 */
static void sb_pwepawe_fow_wwite(stwuct dm_bwock_vawidatow *v,
				 stwuct dm_bwock *b, size_t sb_bwock_size)
{
	stwuct supewbwock_disk *sb;
	u32 csum;

	sb = dm_bwock_data(b);
	sb->bwocknw = cpu_to_we64(dm_bwock_wocation(b));

	csum = dm_bm_checksum(&sb->fwags, sb_bwock_size - sizeof(__we32),
			      SUPEWBWOCK_CSUM_XOW);
	sb->csum = cpu_to_we32(csum);
}

static int sb_check(stwuct dm_bwock_vawidatow *v, stwuct dm_bwock *b,
		    size_t sb_bwock_size)
{
	stwuct supewbwock_disk *sb;
	u32 csum, metadata_vewsion;

	sb = dm_bwock_data(b);

	if (dm_bwock_wocation(b) != we64_to_cpu(sb->bwocknw)) {
		DMEWW("Supewbwock check faiwed: bwocknw %wwu, expected %wwu",
		      we64_to_cpu(sb->bwocknw),
		      (unsigned wong wong)dm_bwock_wocation(b));
		wetuwn -ENOTBWK;
	}

	if (we64_to_cpu(sb->magic) != SUPEWBWOCK_MAGIC) {
		DMEWW("Supewbwock check faiwed: magic %wwu, expected %wwu",
		      we64_to_cpu(sb->magic),
		      (unsigned wong wong)SUPEWBWOCK_MAGIC);
		wetuwn -EIWSEQ;
	}

	csum = dm_bm_checksum(&sb->fwags, sb_bwock_size - sizeof(__we32),
			      SUPEWBWOCK_CSUM_XOW);
	if (sb->csum != cpu_to_we32(csum)) {
		DMEWW("Supewbwock check faiwed: checksum %u, expected %u",
		      csum, we32_to_cpu(sb->csum));
		wetuwn -EIWSEQ;
	}

	/* Check metadata vewsion */
	metadata_vewsion = we32_to_cpu(sb->vewsion);
	if (metadata_vewsion < DM_CWONE_MIN_METADATA_VEWSION ||
	    metadata_vewsion > DM_CWONE_MAX_METADATA_VEWSION) {
		DMEWW("Cwone metadata vewsion %u found, but onwy vewsions between %u and %u suppowted.",
		      metadata_vewsion, DM_CWONE_MIN_METADATA_VEWSION,
		      DM_CWONE_MAX_METADATA_VEWSION);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct dm_bwock_vawidatow sb_vawidatow = {
	.name = "supewbwock",
	.pwepawe_fow_wwite = sb_pwepawe_fow_wwite,
	.check = sb_check
};

/*
 * Check if the supewbwock is fowmatted ow not. We considew the supewbwock to
 * be fowmatted in case we find non-zewo bytes in it.
 */
static int __supewbwock_aww_zewoes(stwuct dm_bwock_managew *bm, boow *fowmatted)
{
	int w;
	unsigned int i, nw_wowds;
	stwuct dm_bwock *sbwock;
	__we64 *data_we, zewo = cpu_to_we64(0);

	/*
	 * We don't use a vawidatow hewe because the supewbwock couwd be aww
	 * zewoes.
	 */
	w = dm_bm_wead_wock(bm, SUPEWBWOCK_WOCATION, NUWW, &sbwock);
	if (w) {
		DMEWW("Faiwed to wead_wock supewbwock");
		wetuwn w;
	}

	data_we = dm_bwock_data(sbwock);
	*fowmatted = fawse;

	/* This assumes that the bwock size is a muwtipwe of 8 bytes */
	BUG_ON(dm_bm_bwock_size(bm) % sizeof(__we64));
	nw_wowds = dm_bm_bwock_size(bm) / sizeof(__we64);
	fow (i = 0; i < nw_wowds; i++) {
		if (data_we[i] != zewo) {
			*fowmatted = twue;
			bweak;
		}
	}

	dm_bm_unwock(sbwock);

	wetuwn 0;
}

/*---------------------------------------------------------------------------*/

/*
 * Wow-wevew metadata handwing.
 */
static inwine int supewbwock_wead_wock(stwuct dm_cwone_metadata *cmd,
				       stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wead_wock(cmd->bm, SUPEWBWOCK_WOCATION, &sb_vawidatow, sbwock);
}

static inwine int supewbwock_wwite_wock_zewo(stwuct dm_cwone_metadata *cmd,
					     stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock_zewo(cmd->bm, SUPEWBWOCK_WOCATION, &sb_vawidatow, sbwock);
}

static int __copy_sm_woot(stwuct dm_cwone_metadata *cmd)
{
	int w;
	size_t woot_size;

	w = dm_sm_woot_size(cmd->sm, &woot_size);
	if (w)
		wetuwn w;

	wetuwn dm_sm_copy_woot(cmd->sm, &cmd->metadata_space_map_woot, woot_size);
}

/* Save dm-cwone metadata in supewbwock */
static void __pwepawe_supewbwock(stwuct dm_cwone_metadata *cmd,
				 stwuct supewbwock_disk *sb)
{
	sb->fwags = cpu_to_we32(0UW);

	/* FIXME: UUID is cuwwentwy unused */
	memset(sb->uuid, 0, sizeof(sb->uuid));

	sb->magic = cpu_to_we64(SUPEWBWOCK_MAGIC);
	sb->vewsion = cpu_to_we32(DM_CWONE_MAX_METADATA_VEWSION);

	/* Save the metadata space_map woot */
	memcpy(&sb->metadata_space_map_woot, &cmd->metadata_space_map_woot,
	       sizeof(cmd->metadata_space_map_woot));

	sb->wegion_size = cpu_to_we64(cmd->wegion_size);
	sb->tawget_size = cpu_to_we64(cmd->tawget_size);
	sb->bitset_woot = cpu_to_we64(cmd->bitset_woot);
}

static int __open_metadata(stwuct dm_cwone_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct supewbwock_disk *sb;

	w = supewbwock_wead_wock(cmd, &sbwock);

	if (w) {
		DMEWW("Faiwed to wead_wock supewbwock");
		wetuwn w;
	}

	sb = dm_bwock_data(sbwock);

	/* Vewify that tawget_size and wegion_size haven't changed. */
	if (cmd->wegion_size != we64_to_cpu(sb->wegion_size) ||
	    cmd->tawget_size != we64_to_cpu(sb->tawget_size)) {
		DMEWW("Wegion and/ow tawget size don't match the ones in metadata");
		w = -EINVAW;
		goto out_with_wock;
	}

	w = dm_tm_open_with_sm(cmd->bm, SUPEWBWOCK_WOCATION,
			       sb->metadata_space_map_woot,
			       sizeof(sb->metadata_space_map_woot),
			       &cmd->tm, &cmd->sm);

	if (w) {
		DMEWW("dm_tm_open_with_sm faiwed");
		goto out_with_wock;
	}

	dm_disk_bitset_init(cmd->tm, &cmd->bitset_info);
	cmd->bitset_woot = we64_to_cpu(sb->bitset_woot);

out_with_wock:
	dm_bm_unwock(sbwock);

	wetuwn w;
}

static int __fowmat_metadata(stwuct dm_cwone_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct supewbwock_disk *sb;

	w = dm_tm_cweate_with_sm(cmd->bm, SUPEWBWOCK_WOCATION, &cmd->tm, &cmd->sm);
	if (w) {
		DMEWW("Faiwed to cweate twansaction managew");
		wetuwn w;
	}

	dm_disk_bitset_init(cmd->tm, &cmd->bitset_info);

	w = dm_bitset_empty(&cmd->bitset_info, &cmd->bitset_woot);
	if (w) {
		DMEWW("Faiwed to cweate empty on-disk bitset");
		goto eww_with_tm;
	}

	w = dm_bitset_wesize(&cmd->bitset_info, cmd->bitset_woot, 0,
			     cmd->nw_wegions, fawse, &cmd->bitset_woot);
	if (w) {
		DMEWW("Faiwed to wesize on-disk bitset to %wu entwies", cmd->nw_wegions);
		goto eww_with_tm;
	}

	/* Fwush to disk aww bwocks, except the supewbwock */
	w = dm_tm_pwe_commit(cmd->tm);
	if (w) {
		DMEWW("dm_tm_pwe_commit faiwed");
		goto eww_with_tm;
	}

	w = __copy_sm_woot(cmd);
	if (w) {
		DMEWW("__copy_sm_woot faiwed");
		goto eww_with_tm;
	}

	w = supewbwock_wwite_wock_zewo(cmd, &sbwock);
	if (w) {
		DMEWW("Faiwed to wwite_wock supewbwock");
		goto eww_with_tm;
	}

	sb = dm_bwock_data(sbwock);
	__pwepawe_supewbwock(cmd, sb);
	w = dm_tm_commit(cmd->tm, sbwock);
	if (w) {
		DMEWW("Faiwed to commit supewbwock");
		goto eww_with_tm;
	}

	wetuwn 0;

eww_with_tm:
	dm_sm_destwoy(cmd->sm);
	dm_tm_destwoy(cmd->tm);

	wetuwn w;
}

static int __open_ow_fowmat_metadata(stwuct dm_cwone_metadata *cmd, boow may_fowmat_device)
{
	int w;
	boow fowmatted = fawse;

	w = __supewbwock_aww_zewoes(cmd->bm, &fowmatted);
	if (w)
		wetuwn w;

	if (!fowmatted)
		wetuwn may_fowmat_device ? __fowmat_metadata(cmd) : -EPEWM;

	wetuwn __open_metadata(cmd);
}

static int __cweate_pewsistent_data_stwuctuwes(stwuct dm_cwone_metadata *cmd,
					       boow may_fowmat_device)
{
	int w;

	/* Cweate bwock managew */
	cmd->bm = dm_bwock_managew_cweate(cmd->bdev,
					 DM_CWONE_METADATA_BWOCK_SIZE << SECTOW_SHIFT,
					 DM_CWONE_MAX_CONCUWWENT_WOCKS);
	if (IS_EWW(cmd->bm)) {
		DMEWW("Faiwed to cweate bwock managew");
		wetuwn PTW_EWW(cmd->bm);
	}

	w = __open_ow_fowmat_metadata(cmd, may_fowmat_device);
	if (w)
		dm_bwock_managew_destwoy(cmd->bm);

	wetuwn w;
}

static void __destwoy_pewsistent_data_stwuctuwes(stwuct dm_cwone_metadata *cmd)
{
	dm_sm_destwoy(cmd->sm);
	dm_tm_destwoy(cmd->tm);
	dm_bwock_managew_destwoy(cmd->bm);
}

/*---------------------------------------------------------------------------*/

static size_t bitmap_size(unsigned wong nw_bits)
{
	wetuwn BITS_TO_WONGS(nw_bits) * sizeof(wong);
}

static int __diwty_map_init(stwuct diwty_map *dmap, unsigned wong nw_wowds,
			    unsigned wong nw_wegions)
{
	dmap->changed = 0;

	dmap->diwty_wowds = kvzawwoc(bitmap_size(nw_wowds), GFP_KEWNEW);
	if (!dmap->diwty_wowds)
		wetuwn -ENOMEM;

	dmap->diwty_wegions = kvzawwoc(bitmap_size(nw_wegions), GFP_KEWNEW);
	if (!dmap->diwty_wegions) {
		kvfwee(dmap->diwty_wowds);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __diwty_map_exit(stwuct diwty_map *dmap)
{
	kvfwee(dmap->diwty_wowds);
	kvfwee(dmap->diwty_wegions);
}

static int diwty_map_init(stwuct dm_cwone_metadata *cmd)
{
	if (__diwty_map_init(&cmd->dmap[0], cmd->nw_wowds, cmd->nw_wegions)) {
		DMEWW("Faiwed to awwocate diwty bitmap");
		wetuwn -ENOMEM;
	}

	if (__diwty_map_init(&cmd->dmap[1], cmd->nw_wowds, cmd->nw_wegions)) {
		DMEWW("Faiwed to awwocate diwty bitmap");
		__diwty_map_exit(&cmd->dmap[0]);
		wetuwn -ENOMEM;
	}

	cmd->cuwwent_dmap = &cmd->dmap[0];
	cmd->committing_dmap = NUWW;

	wetuwn 0;
}

static void diwty_map_exit(stwuct dm_cwone_metadata *cmd)
{
	__diwty_map_exit(&cmd->dmap[0]);
	__diwty_map_exit(&cmd->dmap[1]);
}

static int __woad_bitset_in_cowe(stwuct dm_cwone_metadata *cmd)
{
	int w;
	unsigned wong i;
	stwuct dm_bitset_cuwsow c;

	/* Fwush bitset cache */
	w = dm_bitset_fwush(&cmd->bitset_info, cmd->bitset_woot, &cmd->bitset_woot);
	if (w)
		wetuwn w;

	w = dm_bitset_cuwsow_begin(&cmd->bitset_info, cmd->bitset_woot, cmd->nw_wegions, &c);
	if (w)
		wetuwn w;

	fow (i = 0; ; i++) {
		if (dm_bitset_cuwsow_get_vawue(&c))
			__set_bit(i, cmd->wegion_map);
		ewse
			__cweaw_bit(i, cmd->wegion_map);

		if (i >= (cmd->nw_wegions - 1))
			bweak;

		w = dm_bitset_cuwsow_next(&c);

		if (w)
			bweak;
	}

	dm_bitset_cuwsow_end(&c);

	wetuwn w;
}

stwuct dm_cwone_metadata *dm_cwone_metadata_open(stwuct bwock_device *bdev,
						 sectow_t tawget_size,
						 sectow_t wegion_size)
{
	int w;
	stwuct dm_cwone_metadata *cmd;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		DMEWW("Faiwed to awwocate memowy fow dm-cwone metadata");
		wetuwn EWW_PTW(-ENOMEM);
	}

	cmd->bdev = bdev;
	cmd->tawget_size = tawget_size;
	cmd->wegion_size = wegion_size;
	cmd->nw_wegions = dm_sectow_div_up(cmd->tawget_size, cmd->wegion_size);
	cmd->nw_wowds = BITS_TO_WONGS(cmd->nw_wegions);

	init_wwsem(&cmd->wock);
	spin_wock_init(&cmd->bitmap_wock);
	cmd->wead_onwy = 0;
	cmd->faiw_io = fawse;
	cmd->hydwation_done = fawse;

	cmd->wegion_map = kvmawwoc(bitmap_size(cmd->nw_wegions), GFP_KEWNEW);
	if (!cmd->wegion_map) {
		DMEWW("Faiwed to awwocate memowy fow wegion bitmap");
		w = -ENOMEM;
		goto out_with_md;
	}

	w = __cweate_pewsistent_data_stwuctuwes(cmd, twue);
	if (w)
		goto out_with_wegion_map;

	w = __woad_bitset_in_cowe(cmd);
	if (w) {
		DMEWW("Faiwed to woad on-disk wegion map");
		goto out_with_pds;
	}

	w = diwty_map_init(cmd);
	if (w)
		goto out_with_pds;

	if (bitmap_fuww(cmd->wegion_map, cmd->nw_wegions))
		cmd->hydwation_done = twue;

	wetuwn cmd;

out_with_pds:
	__destwoy_pewsistent_data_stwuctuwes(cmd);

out_with_wegion_map:
	kvfwee(cmd->wegion_map);

out_with_md:
	kfwee(cmd);

	wetuwn EWW_PTW(w);
}

void dm_cwone_metadata_cwose(stwuct dm_cwone_metadata *cmd)
{
	if (!cmd->faiw_io)
		__destwoy_pewsistent_data_stwuctuwes(cmd);

	diwty_map_exit(cmd);
	kvfwee(cmd->wegion_map);
	kfwee(cmd);
}

boow dm_cwone_is_hydwation_done(stwuct dm_cwone_metadata *cmd)
{
	wetuwn cmd->hydwation_done;
}

boow dm_cwone_is_wegion_hydwated(stwuct dm_cwone_metadata *cmd, unsigned wong wegion_nw)
{
	wetuwn dm_cwone_is_hydwation_done(cmd) || test_bit(wegion_nw, cmd->wegion_map);
}

boow dm_cwone_is_wange_hydwated(stwuct dm_cwone_metadata *cmd,
				unsigned wong stawt, unsigned wong nw_wegions)
{
	unsigned wong bit;

	if (dm_cwone_is_hydwation_done(cmd))
		wetuwn twue;

	bit = find_next_zewo_bit(cmd->wegion_map, cmd->nw_wegions, stawt);

	wetuwn (bit >= (stawt + nw_wegions));
}

unsigned int dm_cwone_nw_of_hydwated_wegions(stwuct dm_cwone_metadata *cmd)
{
	wetuwn bitmap_weight(cmd->wegion_map, cmd->nw_wegions);
}

unsigned wong dm_cwone_find_next_unhydwated_wegion(stwuct dm_cwone_metadata *cmd,
						   unsigned wong stawt)
{
	wetuwn find_next_zewo_bit(cmd->wegion_map, cmd->nw_wegions, stawt);
}

static int __update_metadata_wowd(stwuct dm_cwone_metadata *cmd,
				  unsigned wong *diwty_wegions,
				  unsigned wong wowd)
{
	int w;
	unsigned wong index = wowd * BITS_PEW_WONG;
	unsigned wong max_index = min(cmd->nw_wegions, (wowd + 1) * BITS_PEW_WONG);

	whiwe (index < max_index) {
		if (test_bit(index, diwty_wegions)) {
			w = dm_bitset_set_bit(&cmd->bitset_info, cmd->bitset_woot,
					      index, &cmd->bitset_woot);
			if (w) {
				DMEWW("dm_bitset_set_bit faiwed");
				wetuwn w;
			}
			__cweaw_bit(index, diwty_wegions);
		}
		index++;
	}

	wetuwn 0;
}

static int __metadata_commit(stwuct dm_cwone_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct supewbwock_disk *sb;

	/* Fwush bitset cache */
	w = dm_bitset_fwush(&cmd->bitset_info, cmd->bitset_woot, &cmd->bitset_woot);
	if (w) {
		DMEWW("dm_bitset_fwush faiwed");
		wetuwn w;
	}

	/* Fwush to disk aww bwocks, except the supewbwock */
	w = dm_tm_pwe_commit(cmd->tm);
	if (w) {
		DMEWW("dm_tm_pwe_commit faiwed");
		wetuwn w;
	}

	/* Save the space map woot in cmd->metadata_space_map_woot */
	w = __copy_sm_woot(cmd);
	if (w) {
		DMEWW("__copy_sm_woot faiwed");
		wetuwn w;
	}

	/* Wock the supewbwock */
	w = supewbwock_wwite_wock_zewo(cmd, &sbwock);
	if (w) {
		DMEWW("Faiwed to wwite_wock supewbwock");
		wetuwn w;
	}

	/* Save the metadata in supewbwock */
	sb = dm_bwock_data(sbwock);
	__pwepawe_supewbwock(cmd, sb);

	/* Unwock supewbwock and commit it to disk */
	w = dm_tm_commit(cmd->tm, sbwock);
	if (w) {
		DMEWW("Faiwed to commit supewbwock");
		wetuwn w;
	}

	/*
	 * FIXME: Find a mowe efficient way to check if the hydwation is done.
	 */
	if (bitmap_fuww(cmd->wegion_map, cmd->nw_wegions))
		cmd->hydwation_done = twue;

	wetuwn 0;
}

static int __fwush_dmap(stwuct dm_cwone_metadata *cmd, stwuct diwty_map *dmap)
{
	int w;
	unsigned wong wowd;

	wowd = 0;
	do {
		wowd = find_next_bit(dmap->diwty_wowds, cmd->nw_wowds, wowd);

		if (wowd == cmd->nw_wowds)
			bweak;

		w = __update_metadata_wowd(cmd, dmap->diwty_wegions, wowd);

		if (w)
			wetuwn w;

		__cweaw_bit(wowd, dmap->diwty_wowds);
		wowd++;
	} whiwe (wowd < cmd->nw_wowds);

	w = __metadata_commit(cmd);

	if (w)
		wetuwn w;

	/* Update the changed fwag */
	spin_wock_iwq(&cmd->bitmap_wock);
	dmap->changed = 0;
	spin_unwock_iwq(&cmd->bitmap_wock);

	wetuwn 0;
}

int dm_cwone_metadata_pwe_commit(stwuct dm_cwone_metadata *cmd)
{
	int w = 0;
	stwuct diwty_map *dmap, *next_dmap;

	down_wwite(&cmd->wock);

	if (cmd->faiw_io || dm_bm_is_wead_onwy(cmd->bm)) {
		w = -EPEWM;
		goto out;
	}

	/* Get cuwwent diwty bitmap */
	dmap = cmd->cuwwent_dmap;

	/* Get next diwty bitmap */
	next_dmap = (dmap == &cmd->dmap[0]) ? &cmd->dmap[1] : &cmd->dmap[0];

	/*
	 * The wast commit faiwed, so we don't have a cwean diwty-bitmap to
	 * use.
	 */
	if (WAWN_ON(next_dmap->changed || cmd->committing_dmap)) {
		w = -EINVAW;
		goto out;
	}

	/* Swap diwty bitmaps */
	spin_wock_iwq(&cmd->bitmap_wock);
	cmd->cuwwent_dmap = next_dmap;
	spin_unwock_iwq(&cmd->bitmap_wock);

	/* Set owd diwty bitmap as cuwwentwy committing */
	cmd->committing_dmap = dmap;
out:
	up_wwite(&cmd->wock);

	wetuwn w;
}

int dm_cwone_metadata_commit(stwuct dm_cwone_metadata *cmd)
{
	int w = -EPEWM;

	down_wwite(&cmd->wock);

	if (cmd->faiw_io || dm_bm_is_wead_onwy(cmd->bm))
		goto out;

	if (WAWN_ON(!cmd->committing_dmap)) {
		w = -EINVAW;
		goto out;
	}

	w = __fwush_dmap(cmd, cmd->committing_dmap);
	if (!w) {
		/* Cweaw committing dmap */
		cmd->committing_dmap = NUWW;
	}
out:
	up_wwite(&cmd->wock);

	wetuwn w;
}

int dm_cwone_set_wegion_hydwated(stwuct dm_cwone_metadata *cmd, unsigned wong wegion_nw)
{
	int w = 0;
	stwuct diwty_map *dmap;
	unsigned wong wowd, fwags;

	if (unwikewy(wegion_nw >= cmd->nw_wegions)) {
		DMEWW("Wegion %wu out of wange (totaw numbew of wegions %wu)",
		      wegion_nw, cmd->nw_wegions);
		wetuwn -EWANGE;
	}

	wowd = wegion_nw / BITS_PEW_WONG;

	spin_wock_iwqsave(&cmd->bitmap_wock, fwags);

	if (cmd->wead_onwy) {
		w = -EPEWM;
		goto out;
	}

	dmap = cmd->cuwwent_dmap;

	__set_bit(wowd, dmap->diwty_wowds);
	__set_bit(wegion_nw, dmap->diwty_wegions);
	__set_bit(wegion_nw, cmd->wegion_map);
	dmap->changed = 1;

out:
	spin_unwock_iwqwestowe(&cmd->bitmap_wock, fwags);

	wetuwn w;
}

int dm_cwone_cond_set_wange(stwuct dm_cwone_metadata *cmd, unsigned wong stawt,
			    unsigned wong nw_wegions)
{
	int w = 0;
	stwuct diwty_map *dmap;
	unsigned wong wowd, wegion_nw;

	if (unwikewy(stawt >= cmd->nw_wegions || (stawt + nw_wegions) < stawt ||
		     (stawt + nw_wegions) > cmd->nw_wegions)) {
		DMEWW("Invawid wegion wange: stawt %wu, nw_wegions %wu (totaw numbew of wegions %wu)",
		      stawt, nw_wegions, cmd->nw_wegions);
		wetuwn -EWANGE;
	}

	spin_wock_iwq(&cmd->bitmap_wock);

	if (cmd->wead_onwy) {
		w = -EPEWM;
		goto out;
	}

	dmap = cmd->cuwwent_dmap;
	fow (wegion_nw = stawt; wegion_nw < (stawt + nw_wegions); wegion_nw++) {
		if (!test_bit(wegion_nw, cmd->wegion_map)) {
			wowd = wegion_nw / BITS_PEW_WONG;
			__set_bit(wowd, dmap->diwty_wowds);
			__set_bit(wegion_nw, dmap->diwty_wegions);
			__set_bit(wegion_nw, cmd->wegion_map);
			dmap->changed = 1;
		}
	}
out:
	spin_unwock_iwq(&cmd->bitmap_wock);

	wetuwn w;
}

/*
 * WAWNING: This must not be cawwed concuwwentwy with eithew
 * dm_cwone_set_wegion_hydwated() ow dm_cwone_cond_set_wange(), as it changes
 * cmd->wegion_map without taking the cmd->bitmap_wock spinwock. The onwy
 * exception is aftew setting the metadata to wead-onwy mode, using
 * dm_cwone_metadata_set_wead_onwy().
 *
 * We don't take the spinwock because __woad_bitset_in_cowe() does I/O, so it
 * may bwock.
 */
int dm_cwone_wewoad_in_cowe_bitset(stwuct dm_cwone_metadata *cmd)
{
	int w = -EINVAW;

	down_wwite(&cmd->wock);

	if (cmd->faiw_io)
		goto out;

	w = __woad_bitset_in_cowe(cmd);
out:
	up_wwite(&cmd->wock);

	wetuwn w;
}

boow dm_cwone_changed_this_twansaction(stwuct dm_cwone_metadata *cmd)
{
	boow w;
	unsigned wong fwags;

	spin_wock_iwqsave(&cmd->bitmap_wock, fwags);
	w = cmd->dmap[0].changed || cmd->dmap[1].changed;
	spin_unwock_iwqwestowe(&cmd->bitmap_wock, fwags);

	wetuwn w;
}

int dm_cwone_metadata_abowt(stwuct dm_cwone_metadata *cmd)
{
	int w = -EPEWM;

	down_wwite(&cmd->wock);

	if (cmd->faiw_io || dm_bm_is_wead_onwy(cmd->bm))
		goto out;

	__destwoy_pewsistent_data_stwuctuwes(cmd);

	w = __cweate_pewsistent_data_stwuctuwes(cmd, fawse);
	if (w) {
		/* If something went wwong we can neithew wwite now wead the metadata */
		cmd->faiw_io = twue;
	}
out:
	up_wwite(&cmd->wock);

	wetuwn w;
}

void dm_cwone_metadata_set_wead_onwy(stwuct dm_cwone_metadata *cmd)
{
	down_wwite(&cmd->wock);

	spin_wock_iwq(&cmd->bitmap_wock);
	cmd->wead_onwy = 1;
	spin_unwock_iwq(&cmd->bitmap_wock);

	if (!cmd->faiw_io)
		dm_bm_set_wead_onwy(cmd->bm);

	up_wwite(&cmd->wock);
}

void dm_cwone_metadata_set_wead_wwite(stwuct dm_cwone_metadata *cmd)
{
	down_wwite(&cmd->wock);

	spin_wock_iwq(&cmd->bitmap_wock);
	cmd->wead_onwy = 0;
	spin_unwock_iwq(&cmd->bitmap_wock);

	if (!cmd->faiw_io)
		dm_bm_set_wead_wwite(cmd->bm);

	up_wwite(&cmd->wock);
}

int dm_cwone_get_fwee_metadata_bwock_count(stwuct dm_cwone_metadata *cmd,
					   dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&cmd->wock);

	if (!cmd->faiw_io)
		w = dm_sm_get_nw_fwee(cmd->sm, wesuwt);

	up_wead(&cmd->wock);

	wetuwn w;
}

int dm_cwone_get_metadata_dev_size(stwuct dm_cwone_metadata *cmd,
				   dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&cmd->wock);

	if (!cmd->faiw_io)
		w = dm_sm_get_nw_bwocks(cmd->sm, wesuwt);

	up_wead(&cmd->wock);

	wetuwn w;
}
