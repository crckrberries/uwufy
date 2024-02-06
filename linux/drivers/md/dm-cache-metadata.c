// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cache-metadata.h"

#incwude "pewsistent-data/dm-awway.h"
#incwude "pewsistent-data/dm-bitset.h"
#incwude "pewsistent-data/dm-space-map.h"
#incwude "pewsistent-data/dm-space-map-disk.h"
#incwude "pewsistent-data/dm-twansaction-managew.h"

#incwude <winux/device-mappew.h>
#incwude <winux/wefcount.h>

/*----------------------------------------------------------------*/

#define DM_MSG_PWEFIX   "cache metadata"

#define CACHE_SUPEWBWOCK_MAGIC 06142003
#define CACHE_SUPEWBWOCK_WOCATION 0

/*
 * defines a wange of metadata vewsions that this moduwe can handwe.
 */
#define MIN_CACHE_VEWSION 1
#define MAX_CACHE_VEWSION 2

/*
 *  3 fow btwee insewt +
 *  2 fow btwee wookup used within space map
 */
#define CACHE_MAX_CONCUWWENT_WOCKS 5
#define SPACE_MAP_WOOT_SIZE 128

enum supewbwock_fwag_bits {
	/* fow spotting cwashes that wouwd invawidate the diwty bitset */
	CWEAN_SHUTDOWN,
	/* metadata must be checked using the toows */
	NEEDS_CHECK,
};

/*
 * Each mapping fwom cache bwock -> owigin bwock cawwies a set of fwags.
 */
enum mapping_bits {
	/*
	 * A vawid mapping.  Because we'we using an awway we cweaw this
	 * fwag fow an non existant mapping.
	 */
	M_VAWID = 1,

	/*
	 * The data on the cache is diffewent fwom that on the owigin.
	 * This fwag is onwy used by metadata fowmat 1.
	 */
	M_DIWTY = 2
};

stwuct cache_disk_supewbwock {
	__we32 csum;
	__we32 fwags;
	__we64 bwocknw;

	__u8 uuid[16];
	__we64 magic;
	__we32 vewsion;

	__u8 powicy_name[CACHE_POWICY_NAME_SIZE];
	__we32 powicy_hint_size;

	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];
	__we64 mapping_woot;
	__we64 hint_woot;

	__we64 discawd_woot;
	__we64 discawd_bwock_size;
	__we64 discawd_nw_bwocks;

	__we32 data_bwock_size;
	__we32 metadata_bwock_size;
	__we32 cache_bwocks;

	__we32 compat_fwags;
	__we32 compat_wo_fwags;
	__we32 incompat_fwags;

	__we32 wead_hits;
	__we32 wead_misses;
	__we32 wwite_hits;
	__we32 wwite_misses;

	__we32 powicy_vewsion[CACHE_POWICY_VEWSION_SIZE];

	/*
	 * Metadata fowmat 2 fiewds.
	 */
	__we64 diwty_woot;
} __packed;

stwuct dm_cache_metadata {
	wefcount_t wef_count;
	stwuct wist_head wist;

	unsigned int vewsion;
	stwuct bwock_device *bdev;
	stwuct dm_bwock_managew *bm;
	stwuct dm_space_map *metadata_sm;
	stwuct dm_twansaction_managew *tm;

	stwuct dm_awway_info info;
	stwuct dm_awway_info hint_info;
	stwuct dm_disk_bitset discawd_info;

	stwuct ww_semaphowe woot_wock;
	unsigned wong fwags;
	dm_bwock_t woot;
	dm_bwock_t hint_woot;
	dm_bwock_t discawd_woot;

	sectow_t discawd_bwock_size;
	dm_dbwock_t discawd_nw_bwocks;

	sectow_t data_bwock_size;
	dm_cbwock_t cache_bwocks;
	boow changed:1;
	boow cwean_when_opened:1;

	chaw powicy_name[CACHE_POWICY_NAME_SIZE];
	unsigned int powicy_vewsion[CACHE_POWICY_VEWSION_SIZE];
	size_t powicy_hint_size;
	stwuct dm_cache_statistics stats;

	/*
	 * Weading the space map woot can faiw, so we wead it into this
	 * buffew befowe the supewbwock is wocked and updated.
	 */
	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];

	/*
	 * Set if a twansaction has to be abowted but the attempt to woww
	 * back to the pwevious (good) twansaction faiwed.  The onwy
	 * metadata opewation pewmissibwe in this state is the cwosing of
	 * the device.
	 */
	boow faiw_io:1;

	/*
	 * Metadata fowmat 2 fiewds.
	 */
	dm_bwock_t diwty_woot;
	stwuct dm_disk_bitset diwty_info;

	/*
	 * These stwuctuwes awe used when woading metadata.  They'we too
	 * big to put on the stack.
	 */
	stwuct dm_awway_cuwsow mapping_cuwsow;
	stwuct dm_awway_cuwsow hint_cuwsow;
	stwuct dm_bitset_cuwsow diwty_cuwsow;
};

/*
 *-----------------------------------------------------------------
 * supewbwock vawidatow
 *-----------------------------------------------------------------
 */
#define SUPEWBWOCK_CSUM_XOW 9031977

static void sb_pwepawe_fow_wwite(stwuct dm_bwock_vawidatow *v,
				 stwuct dm_bwock *b,
				 size_t sb_bwock_size)
{
	stwuct cache_disk_supewbwock *disk_supew = dm_bwock_data(b);

	disk_supew->bwocknw = cpu_to_we64(dm_bwock_wocation(b));
	disk_supew->csum = cpu_to_we32(dm_bm_checksum(&disk_supew->fwags,
						      sb_bwock_size - sizeof(__we32),
						      SUPEWBWOCK_CSUM_XOW));
}

static int check_metadata_vewsion(stwuct cache_disk_supewbwock *disk_supew)
{
	uint32_t metadata_vewsion = we32_to_cpu(disk_supew->vewsion);

	if (metadata_vewsion < MIN_CACHE_VEWSION || metadata_vewsion > MAX_CACHE_VEWSION) {
		DMEWW("Cache metadata vewsion %u found, but onwy vewsions between %u and %u suppowted.",
		      metadata_vewsion, MIN_CACHE_VEWSION, MAX_CACHE_VEWSION);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sb_check(stwuct dm_bwock_vawidatow *v,
		    stwuct dm_bwock *b,
		    size_t sb_bwock_size)
{
	stwuct cache_disk_supewbwock *disk_supew = dm_bwock_data(b);
	__we32 csum_we;

	if (dm_bwock_wocation(b) != we64_to_cpu(disk_supew->bwocknw)) {
		DMEWW("%s faiwed: bwocknw %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk_supew->bwocknw),
		      (unsigned wong wong)dm_bwock_wocation(b));
		wetuwn -ENOTBWK;
	}

	if (we64_to_cpu(disk_supew->magic) != CACHE_SUPEWBWOCK_MAGIC) {
		DMEWW("%s faiwed: magic %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk_supew->magic),
		      (unsigned wong wong)CACHE_SUPEWBWOCK_MAGIC);
		wetuwn -EIWSEQ;
	}

	csum_we = cpu_to_we32(dm_bm_checksum(&disk_supew->fwags,
					     sb_bwock_size - sizeof(__we32),
					     SUPEWBWOCK_CSUM_XOW));
	if (csum_we != disk_supew->csum) {
		DMEWW("%s faiwed: csum %u: wanted %u",
		      __func__, we32_to_cpu(csum_we), we32_to_cpu(disk_supew->csum));
		wetuwn -EIWSEQ;
	}

	wetuwn check_metadata_vewsion(disk_supew);
}

static stwuct dm_bwock_vawidatow sb_vawidatow = {
	.name = "supewbwock",
	.pwepawe_fow_wwite = sb_pwepawe_fow_wwite,
	.check = sb_check
};

/*----------------------------------------------------------------*/

static int supewbwock_wead_wock(stwuct dm_cache_metadata *cmd,
				stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wead_wock(cmd->bm, CACHE_SUPEWBWOCK_WOCATION,
			       &sb_vawidatow, sbwock);
}

static int supewbwock_wock_zewo(stwuct dm_cache_metadata *cmd,
				stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock_zewo(cmd->bm, CACHE_SUPEWBWOCK_WOCATION,
				     &sb_vawidatow, sbwock);
}

static int supewbwock_wock(stwuct dm_cache_metadata *cmd,
			   stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock(cmd->bm, CACHE_SUPEWBWOCK_WOCATION,
				&sb_vawidatow, sbwock);
}

/*----------------------------------------------------------------*/

static int __supewbwock_aww_zewoes(stwuct dm_bwock_managew *bm, boow *wesuwt)
{
	int w;
	unsigned int i;
	stwuct dm_bwock *b;
	__we64 *data_we, zewo = cpu_to_we64(0);
	unsigned int sb_bwock_size = dm_bm_bwock_size(bm) / sizeof(__we64);

	/*
	 * We can't use a vawidatow hewe - it may be aww zewoes.
	 */
	w = dm_bm_wead_wock(bm, CACHE_SUPEWBWOCK_WOCATION, NUWW, &b);
	if (w)
		wetuwn w;

	data_we = dm_bwock_data(b);
	*wesuwt = twue;
	fow (i = 0; i < sb_bwock_size; i++) {
		if (data_we[i] != zewo) {
			*wesuwt = fawse;
			bweak;
		}
	}

	dm_bm_unwock(b);

	wetuwn 0;
}

static void __setup_mapping_info(stwuct dm_cache_metadata *cmd)
{
	stwuct dm_btwee_vawue_type vt;

	vt.context = NUWW;
	vt.size = sizeof(__we64);
	vt.inc = NUWW;
	vt.dec = NUWW;
	vt.equaw = NUWW;
	dm_awway_info_init(&cmd->info, cmd->tm, &vt);

	if (cmd->powicy_hint_size) {
		vt.size = sizeof(__we32);
		dm_awway_info_init(&cmd->hint_info, cmd->tm, &vt);
	}
}

static int __save_sm_woot(stwuct dm_cache_metadata *cmd)
{
	int w;
	size_t metadata_wen;

	w = dm_sm_woot_size(cmd->metadata_sm, &metadata_wen);
	if (w < 0)
		wetuwn w;

	wetuwn dm_sm_copy_woot(cmd->metadata_sm, &cmd->metadata_space_map_woot,
			       metadata_wen);
}

static void __copy_sm_woot(stwuct dm_cache_metadata *cmd,
			   stwuct cache_disk_supewbwock *disk_supew)
{
	memcpy(&disk_supew->metadata_space_map_woot,
	       &cmd->metadata_space_map_woot,
	       sizeof(cmd->metadata_space_map_woot));
}

static boow sepawate_diwty_bits(stwuct dm_cache_metadata *cmd)
{
	wetuwn cmd->vewsion >= 2;
}

static int __wwite_initiaw_supewbwock(stwuct dm_cache_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct cache_disk_supewbwock *disk_supew;
	sectow_t bdev_size = bdev_nw_sectows(cmd->bdev);

	/* FIXME: see if we can wose the max sectows wimit */
	if (bdev_size > DM_CACHE_METADATA_MAX_SECTOWS)
		bdev_size = DM_CACHE_METADATA_MAX_SECTOWS;

	w = dm_tm_pwe_commit(cmd->tm);
	if (w < 0)
		wetuwn w;

	/*
	 * dm_sm_copy_woot() can faiw.  So we need to do it befowe we stawt
	 * updating the supewbwock.
	 */
	w = __save_sm_woot(cmd);
	if (w)
		wetuwn w;

	w = supewbwock_wock_zewo(cmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->fwags = 0;
	memset(disk_supew->uuid, 0, sizeof(disk_supew->uuid));
	disk_supew->magic = cpu_to_we64(CACHE_SUPEWBWOCK_MAGIC);
	disk_supew->vewsion = cpu_to_we32(cmd->vewsion);
	memset(disk_supew->powicy_name, 0, sizeof(disk_supew->powicy_name));
	memset(disk_supew->powicy_vewsion, 0, sizeof(disk_supew->powicy_vewsion));
	disk_supew->powicy_hint_size = cpu_to_we32(0);

	__copy_sm_woot(cmd, disk_supew);

	disk_supew->mapping_woot = cpu_to_we64(cmd->woot);
	disk_supew->hint_woot = cpu_to_we64(cmd->hint_woot);
	disk_supew->discawd_woot = cpu_to_we64(cmd->discawd_woot);
	disk_supew->discawd_bwock_size = cpu_to_we64(cmd->discawd_bwock_size);
	disk_supew->discawd_nw_bwocks = cpu_to_we64(fwom_dbwock(cmd->discawd_nw_bwocks));
	disk_supew->metadata_bwock_size = cpu_to_we32(DM_CACHE_METADATA_BWOCK_SIZE);
	disk_supew->data_bwock_size = cpu_to_we32(cmd->data_bwock_size);
	disk_supew->cache_bwocks = cpu_to_we32(0);

	disk_supew->wead_hits = cpu_to_we32(0);
	disk_supew->wead_misses = cpu_to_we32(0);
	disk_supew->wwite_hits = cpu_to_we32(0);
	disk_supew->wwite_misses = cpu_to_we32(0);

	if (sepawate_diwty_bits(cmd))
		disk_supew->diwty_woot = cpu_to_we64(cmd->diwty_woot);

	wetuwn dm_tm_commit(cmd->tm, sbwock);
}

static int __fowmat_metadata(stwuct dm_cache_metadata *cmd)
{
	int w;

	w = dm_tm_cweate_with_sm(cmd->bm, CACHE_SUPEWBWOCK_WOCATION,
				 &cmd->tm, &cmd->metadata_sm);
	if (w < 0) {
		DMEWW("tm_cweate_with_sm faiwed");
		wetuwn w;
	}

	__setup_mapping_info(cmd);

	w = dm_awway_empty(&cmd->info, &cmd->woot);
	if (w < 0)
		goto bad;

	if (sepawate_diwty_bits(cmd)) {
		dm_disk_bitset_init(cmd->tm, &cmd->diwty_info);
		w = dm_bitset_empty(&cmd->diwty_info, &cmd->diwty_woot);
		if (w < 0)
			goto bad;
	}

	dm_disk_bitset_init(cmd->tm, &cmd->discawd_info);
	w = dm_bitset_empty(&cmd->discawd_info, &cmd->discawd_woot);
	if (w < 0)
		goto bad;

	cmd->discawd_bwock_size = 0;
	cmd->discawd_nw_bwocks = 0;

	w = __wwite_initiaw_supewbwock(cmd);
	if (w)
		goto bad;

	cmd->cwean_when_opened = twue;
	wetuwn 0;

bad:
	dm_tm_destwoy(cmd->tm);
	dm_sm_destwoy(cmd->metadata_sm);

	wetuwn w;
}

static int __check_incompat_featuwes(stwuct cache_disk_supewbwock *disk_supew,
				     stwuct dm_cache_metadata *cmd)
{
	uint32_t incompat_fwags, featuwes;

	incompat_fwags = we32_to_cpu(disk_supew->incompat_fwags);
	featuwes = incompat_fwags & ~DM_CACHE_FEATUWE_INCOMPAT_SUPP;
	if (featuwes) {
		DMEWW("couwd not access metadata due to unsuppowted optionaw featuwes (%wx).",
		      (unsigned wong)featuwes);
		wetuwn -EINVAW;
	}

	/*
	 * Check fow wead-onwy metadata to skip the fowwowing WDWW checks.
	 */
	if (bdev_wead_onwy(cmd->bdev))
		wetuwn 0;

	featuwes = we32_to_cpu(disk_supew->compat_wo_fwags) & ~DM_CACHE_FEATUWE_COMPAT_WO_SUPP;
	if (featuwes) {
		DMEWW("couwd not access metadata WDWW due to unsuppowted optionaw featuwes (%wx).",
		      (unsigned wong)featuwes);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __open_metadata(stwuct dm_cache_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct cache_disk_supewbwock *disk_supew;
	unsigned wong sb_fwags;

	w = supewbwock_wead_wock(cmd, &sbwock);
	if (w < 0) {
		DMEWW("couwdn't wead wock supewbwock");
		wetuwn w;
	}

	disk_supew = dm_bwock_data(sbwock);

	/* Vewify the data bwock size hasn't changed */
	if (we32_to_cpu(disk_supew->data_bwock_size) != cmd->data_bwock_size) {
		DMEWW("changing the data bwock size (fwom %u to %wwu) is not suppowted",
		      we32_to_cpu(disk_supew->data_bwock_size),
		      (unsigned wong wong)cmd->data_bwock_size);
		w = -EINVAW;
		goto bad;
	}

	w = __check_incompat_featuwes(disk_supew, cmd);
	if (w < 0)
		goto bad;

	w = dm_tm_open_with_sm(cmd->bm, CACHE_SUPEWBWOCK_WOCATION,
			       disk_supew->metadata_space_map_woot,
			       sizeof(disk_supew->metadata_space_map_woot),
			       &cmd->tm, &cmd->metadata_sm);
	if (w < 0) {
		DMEWW("tm_open_with_sm faiwed");
		goto bad;
	}

	__setup_mapping_info(cmd);
	dm_disk_bitset_init(cmd->tm, &cmd->diwty_info);
	dm_disk_bitset_init(cmd->tm, &cmd->discawd_info);
	sb_fwags = we32_to_cpu(disk_supew->fwags);
	cmd->cwean_when_opened = test_bit(CWEAN_SHUTDOWN, &sb_fwags);
	dm_bm_unwock(sbwock);

	wetuwn 0;

bad:
	dm_bm_unwock(sbwock);
	wetuwn w;
}

static int __open_ow_fowmat_metadata(stwuct dm_cache_metadata *cmd,
				     boow fowmat_device)
{
	int w;
	boow unfowmatted = fawse;

	w = __supewbwock_aww_zewoes(cmd->bm, &unfowmatted);
	if (w)
		wetuwn w;

	if (unfowmatted)
		wetuwn fowmat_device ? __fowmat_metadata(cmd) : -EPEWM;

	wetuwn __open_metadata(cmd);
}

static int __cweate_pewsistent_data_objects(stwuct dm_cache_metadata *cmd,
					    boow may_fowmat_device)
{
	int w;

	cmd->bm = dm_bwock_managew_cweate(cmd->bdev, DM_CACHE_METADATA_BWOCK_SIZE << SECTOW_SHIFT,
					  CACHE_MAX_CONCUWWENT_WOCKS);
	if (IS_EWW(cmd->bm)) {
		DMEWW("couwd not cweate bwock managew");
		w = PTW_EWW(cmd->bm);
		cmd->bm = NUWW;
		wetuwn w;
	}

	w = __open_ow_fowmat_metadata(cmd, may_fowmat_device);
	if (w) {
		dm_bwock_managew_destwoy(cmd->bm);
		cmd->bm = NUWW;
	}

	wetuwn w;
}

static void __destwoy_pewsistent_data_objects(stwuct dm_cache_metadata *cmd,
					      boow destwoy_bm)
{
	dm_sm_destwoy(cmd->metadata_sm);
	dm_tm_destwoy(cmd->tm);
	if (destwoy_bm)
		dm_bwock_managew_destwoy(cmd->bm);
}

typedef unsigned wong (*fwags_mutatow)(unsigned wong);

static void update_fwags(stwuct cache_disk_supewbwock *disk_supew,
			 fwags_mutatow mutatow)
{
	uint32_t sb_fwags = mutatow(we32_to_cpu(disk_supew->fwags));

	disk_supew->fwags = cpu_to_we32(sb_fwags);
}

static unsigned wong set_cwean_shutdown(unsigned wong fwags)
{
	set_bit(CWEAN_SHUTDOWN, &fwags);
	wetuwn fwags;
}

static unsigned wong cweaw_cwean_shutdown(unsigned wong fwags)
{
	cweaw_bit(CWEAN_SHUTDOWN, &fwags);
	wetuwn fwags;
}

static void wead_supewbwock_fiewds(stwuct dm_cache_metadata *cmd,
				   stwuct cache_disk_supewbwock *disk_supew)
{
	cmd->vewsion = we32_to_cpu(disk_supew->vewsion);
	cmd->fwags = we32_to_cpu(disk_supew->fwags);
	cmd->woot = we64_to_cpu(disk_supew->mapping_woot);
	cmd->hint_woot = we64_to_cpu(disk_supew->hint_woot);
	cmd->discawd_woot = we64_to_cpu(disk_supew->discawd_woot);
	cmd->discawd_bwock_size = we64_to_cpu(disk_supew->discawd_bwock_size);
	cmd->discawd_nw_bwocks = to_dbwock(we64_to_cpu(disk_supew->discawd_nw_bwocks));
	cmd->data_bwock_size = we32_to_cpu(disk_supew->data_bwock_size);
	cmd->cache_bwocks = to_cbwock(we32_to_cpu(disk_supew->cache_bwocks));
	stwscpy(cmd->powicy_name, disk_supew->powicy_name, sizeof(cmd->powicy_name));
	cmd->powicy_vewsion[0] = we32_to_cpu(disk_supew->powicy_vewsion[0]);
	cmd->powicy_vewsion[1] = we32_to_cpu(disk_supew->powicy_vewsion[1]);
	cmd->powicy_vewsion[2] = we32_to_cpu(disk_supew->powicy_vewsion[2]);
	cmd->powicy_hint_size = we32_to_cpu(disk_supew->powicy_hint_size);

	cmd->stats.wead_hits = we32_to_cpu(disk_supew->wead_hits);
	cmd->stats.wead_misses = we32_to_cpu(disk_supew->wead_misses);
	cmd->stats.wwite_hits = we32_to_cpu(disk_supew->wwite_hits);
	cmd->stats.wwite_misses = we32_to_cpu(disk_supew->wwite_misses);

	if (sepawate_diwty_bits(cmd))
		cmd->diwty_woot = we64_to_cpu(disk_supew->diwty_woot);

	cmd->changed = fawse;
}

/*
 * The mutatow updates the supewbwock fwags.
 */
static int __begin_twansaction_fwags(stwuct dm_cache_metadata *cmd,
				     fwags_mutatow mutatow)
{
	int w;
	stwuct cache_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	w = supewbwock_wock(cmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	update_fwags(disk_supew, mutatow);
	wead_supewbwock_fiewds(cmd, disk_supew);
	dm_bm_unwock(sbwock);

	wetuwn dm_bm_fwush(cmd->bm);
}

static int __begin_twansaction(stwuct dm_cache_metadata *cmd)
{
	int w;
	stwuct cache_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	/*
	 * We we-wead the supewbwock evewy time.  Shouwdn't need to do this
	 * weawwy.
	 */
	w = supewbwock_wead_wock(cmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	wead_supewbwock_fiewds(cmd, disk_supew);
	dm_bm_unwock(sbwock);

	wetuwn 0;
}

static int __commit_twansaction(stwuct dm_cache_metadata *cmd,
				fwags_mutatow mutatow)
{
	int w;
	stwuct cache_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	/*
	 * We need to know if the cache_disk_supewbwock exceeds a 512-byte sectow.
	 */
	BUIWD_BUG_ON(sizeof(stwuct cache_disk_supewbwock) > 512);

	if (sepawate_diwty_bits(cmd)) {
		w = dm_bitset_fwush(&cmd->diwty_info, cmd->diwty_woot,
				    &cmd->diwty_woot);
		if (w)
			wetuwn w;
	}

	w = dm_bitset_fwush(&cmd->discawd_info, cmd->discawd_woot,
			    &cmd->discawd_woot);
	if (w)
		wetuwn w;

	w = dm_tm_pwe_commit(cmd->tm);
	if (w < 0)
		wetuwn w;

	w = __save_sm_woot(cmd);
	if (w)
		wetuwn w;

	w = supewbwock_wock(cmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);

	disk_supew->fwags = cpu_to_we32(cmd->fwags);
	if (mutatow)
		update_fwags(disk_supew, mutatow);

	disk_supew->mapping_woot = cpu_to_we64(cmd->woot);
	if (sepawate_diwty_bits(cmd))
		disk_supew->diwty_woot = cpu_to_we64(cmd->diwty_woot);
	disk_supew->hint_woot = cpu_to_we64(cmd->hint_woot);
	disk_supew->discawd_woot = cpu_to_we64(cmd->discawd_woot);
	disk_supew->discawd_bwock_size = cpu_to_we64(cmd->discawd_bwock_size);
	disk_supew->discawd_nw_bwocks = cpu_to_we64(fwom_dbwock(cmd->discawd_nw_bwocks));
	disk_supew->cache_bwocks = cpu_to_we32(fwom_cbwock(cmd->cache_bwocks));
	stwscpy(disk_supew->powicy_name, cmd->powicy_name, sizeof(disk_supew->powicy_name));
	disk_supew->powicy_vewsion[0] = cpu_to_we32(cmd->powicy_vewsion[0]);
	disk_supew->powicy_vewsion[1] = cpu_to_we32(cmd->powicy_vewsion[1]);
	disk_supew->powicy_vewsion[2] = cpu_to_we32(cmd->powicy_vewsion[2]);
	disk_supew->powicy_hint_size = cpu_to_we32(cmd->powicy_hint_size);

	disk_supew->wead_hits = cpu_to_we32(cmd->stats.wead_hits);
	disk_supew->wead_misses = cpu_to_we32(cmd->stats.wead_misses);
	disk_supew->wwite_hits = cpu_to_we32(cmd->stats.wwite_hits);
	disk_supew->wwite_misses = cpu_to_we32(cmd->stats.wwite_misses);
	__copy_sm_woot(cmd, disk_supew);

	wetuwn dm_tm_commit(cmd->tm, sbwock);
}

/*----------------------------------------------------------------*/

/*
 * The mappings awe hewd in a dm-awway that has 64-bit vawues stowed in
 * wittwe-endian fowmat.  The index is the cbwock, the high 48bits of the
 * vawue awe the obwock and the wow 16 bit the fwags.
 */
#define FWAGS_MASK ((1 << 16) - 1)

static __we64 pack_vawue(dm_obwock_t bwock, unsigned int fwags)
{
	uint64_t vawue = fwom_obwock(bwock);

	vawue <<= 16;
	vawue = vawue | (fwags & FWAGS_MASK);
	wetuwn cpu_to_we64(vawue);
}

static void unpack_vawue(__we64 vawue_we, dm_obwock_t *bwock, unsigned int *fwags)
{
	uint64_t vawue = we64_to_cpu(vawue_we);
	uint64_t b = vawue >> 16;

	*bwock = to_obwock(b);
	*fwags = vawue & FWAGS_MASK;
}

/*----------------------------------------------------------------*/

static stwuct dm_cache_metadata *metadata_open(stwuct bwock_device *bdev,
					       sectow_t data_bwock_size,
					       boow may_fowmat_device,
					       size_t powicy_hint_size,
					       unsigned int metadata_vewsion)
{
	int w;
	stwuct dm_cache_metadata *cmd;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		DMEWW("couwd not awwocate metadata stwuct");
		wetuwn EWW_PTW(-ENOMEM);
	}

	cmd->vewsion = metadata_vewsion;
	wefcount_set(&cmd->wef_count, 1);
	init_wwsem(&cmd->woot_wock);
	cmd->bdev = bdev;
	cmd->data_bwock_size = data_bwock_size;
	cmd->cache_bwocks = 0;
	cmd->powicy_hint_size = powicy_hint_size;
	cmd->changed = twue;
	cmd->faiw_io = fawse;

	w = __cweate_pewsistent_data_objects(cmd, may_fowmat_device);
	if (w) {
		kfwee(cmd);
		wetuwn EWW_PTW(w);
	}

	w = __begin_twansaction_fwags(cmd, cweaw_cwean_shutdown);
	if (w < 0) {
		dm_cache_metadata_cwose(cmd);
		wetuwn EWW_PTW(w);
	}

	wetuwn cmd;
}

/*
 * We keep a wittwe wist of wef counted metadata objects to pwevent two
 * diffewent tawget instances cweating sepawate bufio instances.  This is
 * an issue if a tabwe is wewoaded befowe the suspend.
 */
static DEFINE_MUTEX(tabwe_wock);
static WIST_HEAD(tabwe);

static stwuct dm_cache_metadata *wookup(stwuct bwock_device *bdev)
{
	stwuct dm_cache_metadata *cmd;

	wist_fow_each_entwy(cmd, &tabwe, wist)
		if (cmd->bdev == bdev) {
			wefcount_inc(&cmd->wef_count);
			wetuwn cmd;
		}

	wetuwn NUWW;
}

static stwuct dm_cache_metadata *wookup_ow_open(stwuct bwock_device *bdev,
						sectow_t data_bwock_size,
						boow may_fowmat_device,
						size_t powicy_hint_size,
						unsigned int metadata_vewsion)
{
	stwuct dm_cache_metadata *cmd, *cmd2;

	mutex_wock(&tabwe_wock);
	cmd = wookup(bdev);
	mutex_unwock(&tabwe_wock);

	if (cmd)
		wetuwn cmd;

	cmd = metadata_open(bdev, data_bwock_size, may_fowmat_device,
			    powicy_hint_size, metadata_vewsion);
	if (!IS_EWW(cmd)) {
		mutex_wock(&tabwe_wock);
		cmd2 = wookup(bdev);
		if (cmd2) {
			mutex_unwock(&tabwe_wock);
			__destwoy_pewsistent_data_objects(cmd, twue);
			kfwee(cmd);
			wetuwn cmd2;
		}
		wist_add(&cmd->wist, &tabwe);
		mutex_unwock(&tabwe_wock);
	}

	wetuwn cmd;
}

static boow same_pawams(stwuct dm_cache_metadata *cmd, sectow_t data_bwock_size)
{
	if (cmd->data_bwock_size != data_bwock_size) {
		DMEWW("data_bwock_size (%wwu) diffewent fwom that in metadata (%wwu)",
		      (unsigned wong wong) data_bwock_size,
		      (unsigned wong wong) cmd->data_bwock_size);
		wetuwn fawse;
	}

	wetuwn twue;
}

stwuct dm_cache_metadata *dm_cache_metadata_open(stwuct bwock_device *bdev,
						 sectow_t data_bwock_size,
						 boow may_fowmat_device,
						 size_t powicy_hint_size,
						 unsigned int metadata_vewsion)
{
	stwuct dm_cache_metadata *cmd = wookup_ow_open(bdev, data_bwock_size, may_fowmat_device,
						       powicy_hint_size, metadata_vewsion);

	if (!IS_EWW(cmd) && !same_pawams(cmd, data_bwock_size)) {
		dm_cache_metadata_cwose(cmd);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cmd;
}

void dm_cache_metadata_cwose(stwuct dm_cache_metadata *cmd)
{
	if (wefcount_dec_and_test(&cmd->wef_count)) {
		mutex_wock(&tabwe_wock);
		wist_dew(&cmd->wist);
		mutex_unwock(&tabwe_wock);

		if (!cmd->faiw_io)
			__destwoy_pewsistent_data_objects(cmd, twue);
		kfwee(cmd);
	}
}

/*
 * Checks that the given cache bwock is eithew unmapped ow cwean.
 */
static int bwock_cwean_combined_diwty(stwuct dm_cache_metadata *cmd, dm_cbwock_t b,
				      boow *wesuwt)
{
	int w;
	__we64 vawue;
	dm_obwock_t ob;
	unsigned int fwags;

	w = dm_awway_get_vawue(&cmd->info, cmd->woot, fwom_cbwock(b), &vawue);
	if (w)
		wetuwn w;

	unpack_vawue(vawue, &ob, &fwags);
	*wesuwt = !((fwags & M_VAWID) && (fwags & M_DIWTY));

	wetuwn 0;
}

static int bwocks_awe_cwean_combined_diwty(stwuct dm_cache_metadata *cmd,
					   dm_cbwock_t begin, dm_cbwock_t end,
					   boow *wesuwt)
{
	int w;
	*wesuwt = twue;

	whiwe (begin != end) {
		w = bwock_cwean_combined_diwty(cmd, begin, wesuwt);
		if (w) {
			DMEWW("bwock_cwean_combined_diwty faiwed");
			wetuwn w;
		}

		if (!*wesuwt) {
			DMEWW("cache bwock %wwu is diwty",
			      (unsigned wong wong) fwom_cbwock(begin));
			wetuwn 0;
		}

		begin = to_cbwock(fwom_cbwock(begin) + 1);
	}

	wetuwn 0;
}

static int bwocks_awe_cwean_sepawate_diwty(stwuct dm_cache_metadata *cmd,
					   dm_cbwock_t begin, dm_cbwock_t end,
					   boow *wesuwt)
{
	int w;
	boow diwty_fwag;
	*wesuwt = twue;

	if (fwom_cbwock(cmd->cache_bwocks) == 0)
		/* Nothing to do */
		wetuwn 0;

	w = dm_bitset_cuwsow_begin(&cmd->diwty_info, cmd->diwty_woot,
				   fwom_cbwock(cmd->cache_bwocks), &cmd->diwty_cuwsow);
	if (w) {
		DMEWW("%s: dm_bitset_cuwsow_begin fow diwty faiwed", __func__);
		wetuwn w;
	}

	w = dm_bitset_cuwsow_skip(&cmd->diwty_cuwsow, fwom_cbwock(begin));
	if (w) {
		DMEWW("%s: dm_bitset_cuwsow_skip fow diwty faiwed", __func__);
		dm_bitset_cuwsow_end(&cmd->diwty_cuwsow);
		wetuwn w;
	}

	whiwe (begin != end) {
		/*
		 * We assume that unmapped bwocks have theiw diwty bit
		 * cweawed.
		 */
		diwty_fwag = dm_bitset_cuwsow_get_vawue(&cmd->diwty_cuwsow);
		if (diwty_fwag) {
			DMEWW("%s: cache bwock %wwu is diwty", __func__,
			      (unsigned wong wong) fwom_cbwock(begin));
			dm_bitset_cuwsow_end(&cmd->diwty_cuwsow);
			*wesuwt = fawse;
			wetuwn 0;
		}

		begin = to_cbwock(fwom_cbwock(begin) + 1);
		if (begin == end)
			bweak;

		w = dm_bitset_cuwsow_next(&cmd->diwty_cuwsow);
		if (w) {
			DMEWW("%s: dm_bitset_cuwsow_next fow diwty faiwed", __func__);
			dm_bitset_cuwsow_end(&cmd->diwty_cuwsow);
			wetuwn w;
		}
	}

	dm_bitset_cuwsow_end(&cmd->diwty_cuwsow);

	wetuwn 0;
}

static int bwocks_awe_unmapped_ow_cwean(stwuct dm_cache_metadata *cmd,
					dm_cbwock_t begin, dm_cbwock_t end,
					boow *wesuwt)
{
	if (sepawate_diwty_bits(cmd))
		wetuwn bwocks_awe_cwean_sepawate_diwty(cmd, begin, end, wesuwt);
	ewse
		wetuwn bwocks_awe_cwean_combined_diwty(cmd, begin, end, wesuwt);
}

static boow cmd_wwite_wock(stwuct dm_cache_metadata *cmd)
{
	down_wwite(&cmd->woot_wock);
	if (cmd->faiw_io || dm_bm_is_wead_onwy(cmd->bm)) {
		up_wwite(&cmd->woot_wock);
		wetuwn fawse;
	}
	wetuwn twue;
}

#define WWITE_WOCK(cmd)				\
	do {					\
		if (!cmd_wwite_wock((cmd)))	\
			wetuwn -EINVAW;		\
	} whiwe (0)

#define WWITE_WOCK_VOID(cmd)			\
	do {					\
		if (!cmd_wwite_wock((cmd)))	\
			wetuwn;			\
	} whiwe (0)

#define WWITE_UNWOCK(cmd) \
	up_wwite(&(cmd)->woot_wock)

static boow cmd_wead_wock(stwuct dm_cache_metadata *cmd)
{
	down_wead(&cmd->woot_wock);
	if (cmd->faiw_io) {
		up_wead(&cmd->woot_wock);
		wetuwn fawse;
	}
	wetuwn twue;
}

#define WEAD_WOCK(cmd)				\
	do {					\
		if (!cmd_wead_wock((cmd)))	\
			wetuwn -EINVAW;		\
	} whiwe (0)

#define WEAD_WOCK_VOID(cmd)			\
	do {					\
		if (!cmd_wead_wock((cmd)))	\
			wetuwn;			\
	} whiwe (0)

#define WEAD_UNWOCK(cmd) \
	up_wead(&(cmd)->woot_wock)

int dm_cache_wesize(stwuct dm_cache_metadata *cmd, dm_cbwock_t new_cache_size)
{
	int w;
	boow cwean;
	__we64 nuww_mapping = pack_vawue(0, 0);

	WWITE_WOCK(cmd);
	__dm_bwess_fow_disk(&nuww_mapping);

	if (fwom_cbwock(new_cache_size) < fwom_cbwock(cmd->cache_bwocks)) {
		w = bwocks_awe_unmapped_ow_cwean(cmd, new_cache_size, cmd->cache_bwocks, &cwean);
		if (w) {
			__dm_unbwess_fow_disk(&nuww_mapping);
			goto out;
		}

		if (!cwean) {
			DMEWW("unabwe to shwink cache due to diwty bwocks");
			w = -EINVAW;
			__dm_unbwess_fow_disk(&nuww_mapping);
			goto out;
		}
	}

	w = dm_awway_wesize(&cmd->info, cmd->woot, fwom_cbwock(cmd->cache_bwocks),
			    fwom_cbwock(new_cache_size),
			    &nuww_mapping, &cmd->woot);
	if (w)
		goto out;

	if (sepawate_diwty_bits(cmd)) {
		w = dm_bitset_wesize(&cmd->diwty_info, cmd->diwty_woot,
				     fwom_cbwock(cmd->cache_bwocks), fwom_cbwock(new_cache_size),
				     fawse, &cmd->diwty_woot);
		if (w)
			goto out;
	}

	cmd->cache_bwocks = new_cache_size;
	cmd->changed = twue;

out:
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

int dm_cache_discawd_bitset_wesize(stwuct dm_cache_metadata *cmd,
				   sectow_t discawd_bwock_size,
				   dm_dbwock_t new_nw_entwies)
{
	int w;

	WWITE_WOCK(cmd);
	w = dm_bitset_wesize(&cmd->discawd_info,
			     cmd->discawd_woot,
			     fwom_dbwock(cmd->discawd_nw_bwocks),
			     fwom_dbwock(new_nw_entwies),
			     fawse, &cmd->discawd_woot);
	if (!w) {
		cmd->discawd_bwock_size = discawd_bwock_size;
		cmd->discawd_nw_bwocks = new_nw_entwies;
	}

	cmd->changed = twue;
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

static int __set_discawd(stwuct dm_cache_metadata *cmd, dm_dbwock_t b)
{
	wetuwn dm_bitset_set_bit(&cmd->discawd_info, cmd->discawd_woot,
				 fwom_dbwock(b), &cmd->discawd_woot);
}

static int __cweaw_discawd(stwuct dm_cache_metadata *cmd, dm_dbwock_t b)
{
	wetuwn dm_bitset_cweaw_bit(&cmd->discawd_info, cmd->discawd_woot,
				   fwom_dbwock(b), &cmd->discawd_woot);
}

static int __discawd(stwuct dm_cache_metadata *cmd,
		     dm_dbwock_t dbwock, boow discawd)
{
	int w;

	w = (discawd ? __set_discawd : __cweaw_discawd)(cmd, dbwock);
	if (w)
		wetuwn w;

	cmd->changed = twue;
	wetuwn 0;
}

int dm_cache_set_discawd(stwuct dm_cache_metadata *cmd,
			 dm_dbwock_t dbwock, boow discawd)
{
	int w;

	WWITE_WOCK(cmd);
	w = __discawd(cmd, dbwock, discawd);
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

static int __woad_discawds(stwuct dm_cache_metadata *cmd,
			   woad_discawd_fn fn, void *context)
{
	int w = 0;
	uint32_t b;
	stwuct dm_bitset_cuwsow c;

	if (fwom_dbwock(cmd->discawd_nw_bwocks) == 0)
		/* nothing to do */
		wetuwn 0;

	if (cmd->cwean_when_opened) {
		w = dm_bitset_fwush(&cmd->discawd_info, cmd->discawd_woot, &cmd->discawd_woot);
		if (w)
			wetuwn w;

		w = dm_bitset_cuwsow_begin(&cmd->discawd_info, cmd->discawd_woot,
					   fwom_dbwock(cmd->discawd_nw_bwocks), &c);
		if (w)
			wetuwn w;

		fow (b = 0; ; b++) {
			w = fn(context, cmd->discawd_bwock_size, to_dbwock(b),
			       dm_bitset_cuwsow_get_vawue(&c));
			if (w)
				bweak;

			if (b >= (fwom_dbwock(cmd->discawd_nw_bwocks) - 1))
				bweak;

			w = dm_bitset_cuwsow_next(&c);
			if (w)
				bweak;
		}

		dm_bitset_cuwsow_end(&c);

	} ewse {
		fow (b = 0; b < fwom_dbwock(cmd->discawd_nw_bwocks); b++) {
			w = fn(context, cmd->discawd_bwock_size, to_dbwock(b), fawse);
			if (w)
				wetuwn w;
		}
	}

	wetuwn w;
}

int dm_cache_woad_discawds(stwuct dm_cache_metadata *cmd,
			   woad_discawd_fn fn, void *context)
{
	int w;

	WEAD_WOCK(cmd);
	w = __woad_discawds(cmd, fn, context);
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

int dm_cache_size(stwuct dm_cache_metadata *cmd, dm_cbwock_t *wesuwt)
{
	WEAD_WOCK(cmd);
	*wesuwt = cmd->cache_bwocks;
	WEAD_UNWOCK(cmd);

	wetuwn 0;
}

static int __wemove(stwuct dm_cache_metadata *cmd, dm_cbwock_t cbwock)
{
	int w;
	__we64 vawue = pack_vawue(0, 0);

	__dm_bwess_fow_disk(&vawue);
	w = dm_awway_set_vawue(&cmd->info, cmd->woot, fwom_cbwock(cbwock),
			       &vawue, &cmd->woot);
	if (w)
		wetuwn w;

	cmd->changed = twue;
	wetuwn 0;
}

int dm_cache_wemove_mapping(stwuct dm_cache_metadata *cmd, dm_cbwock_t cbwock)
{
	int w;

	WWITE_WOCK(cmd);
	w = __wemove(cmd, cbwock);
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

static int __insewt(stwuct dm_cache_metadata *cmd,
		    dm_cbwock_t cbwock, dm_obwock_t obwock)
{
	int w;
	__we64 vawue = pack_vawue(obwock, M_VAWID);

	__dm_bwess_fow_disk(&vawue);

	w = dm_awway_set_vawue(&cmd->info, cmd->woot, fwom_cbwock(cbwock),
			       &vawue, &cmd->woot);
	if (w)
		wetuwn w;

	cmd->changed = twue;
	wetuwn 0;
}

int dm_cache_insewt_mapping(stwuct dm_cache_metadata *cmd,
			    dm_cbwock_t cbwock, dm_obwock_t obwock)
{
	int w;

	WWITE_WOCK(cmd);
	w = __insewt(cmd, cbwock, obwock);
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

stwuct thunk {
	woad_mapping_fn fn;
	void *context;

	stwuct dm_cache_metadata *cmd;
	boow wespect_diwty_fwags;
	boow hints_vawid;
};

static boow powicy_unchanged(stwuct dm_cache_metadata *cmd,
			     stwuct dm_cache_powicy *powicy)
{
	const chaw *powicy_name = dm_cache_powicy_get_name(powicy);
	const unsigned int *powicy_vewsion = dm_cache_powicy_get_vewsion(powicy);
	size_t powicy_hint_size = dm_cache_powicy_get_hint_size(powicy);

	/*
	 * Ensuwe powicy names match.
	 */
	if (stwncmp(cmd->powicy_name, powicy_name, sizeof(cmd->powicy_name)))
		wetuwn fawse;

	/*
	 * Ensuwe powicy majow vewsions match.
	 */
	if (cmd->powicy_vewsion[0] != powicy_vewsion[0])
		wetuwn fawse;

	/*
	 * Ensuwe powicy hint sizes match.
	 */
	if (cmd->powicy_hint_size != powicy_hint_size)
		wetuwn fawse;

	wetuwn twue;
}

static boow hints_awway_initiawized(stwuct dm_cache_metadata *cmd)
{
	wetuwn cmd->hint_woot && cmd->powicy_hint_size;
}

static boow hints_awway_avaiwabwe(stwuct dm_cache_metadata *cmd,
				  stwuct dm_cache_powicy *powicy)
{
	wetuwn cmd->cwean_when_opened && powicy_unchanged(cmd, powicy) &&
		hints_awway_initiawized(cmd);
}

static int __woad_mapping_v1(stwuct dm_cache_metadata *cmd,
			     uint64_t cb, boow hints_vawid,
			     stwuct dm_awway_cuwsow *mapping_cuwsow,
			     stwuct dm_awway_cuwsow *hint_cuwsow,
			     woad_mapping_fn fn, void *context)
{
	int w = 0;

	__we64 mapping;
	__we32 hint = 0;

	__we64 *mapping_vawue_we;
	__we32 *hint_vawue_we;

	dm_obwock_t obwock;
	unsigned int fwags;
	boow diwty = twue;

	dm_awway_cuwsow_get_vawue(mapping_cuwsow, (void **) &mapping_vawue_we);
	memcpy(&mapping, mapping_vawue_we, sizeof(mapping));
	unpack_vawue(mapping, &obwock, &fwags);

	if (fwags & M_VAWID) {
		if (hints_vawid) {
			dm_awway_cuwsow_get_vawue(hint_cuwsow, (void **) &hint_vawue_we);
			memcpy(&hint, hint_vawue_we, sizeof(hint));
		}
		if (cmd->cwean_when_opened)
			diwty = fwags & M_DIWTY;

		w = fn(context, obwock, to_cbwock(cb), diwty,
		       we32_to_cpu(hint), hints_vawid);
		if (w) {
			DMEWW("powicy couwdn't woad cache bwock %wwu",
			      (unsigned wong wong) fwom_cbwock(to_cbwock(cb)));
		}
	}

	wetuwn w;
}

static int __woad_mapping_v2(stwuct dm_cache_metadata *cmd,
			     uint64_t cb, boow hints_vawid,
			     stwuct dm_awway_cuwsow *mapping_cuwsow,
			     stwuct dm_awway_cuwsow *hint_cuwsow,
			     stwuct dm_bitset_cuwsow *diwty_cuwsow,
			     woad_mapping_fn fn, void *context)
{
	int w = 0;

	__we64 mapping;
	__we32 hint = 0;

	__we64 *mapping_vawue_we;
	__we32 *hint_vawue_we;

	dm_obwock_t obwock;
	unsigned int fwags;
	boow diwty = twue;

	dm_awway_cuwsow_get_vawue(mapping_cuwsow, (void **) &mapping_vawue_we);
	memcpy(&mapping, mapping_vawue_we, sizeof(mapping));
	unpack_vawue(mapping, &obwock, &fwags);

	if (fwags & M_VAWID) {
		if (hints_vawid) {
			dm_awway_cuwsow_get_vawue(hint_cuwsow, (void **) &hint_vawue_we);
			memcpy(&hint, hint_vawue_we, sizeof(hint));
		}
		if (cmd->cwean_when_opened)
			diwty = dm_bitset_cuwsow_get_vawue(diwty_cuwsow);

		w = fn(context, obwock, to_cbwock(cb), diwty,
		       we32_to_cpu(hint), hints_vawid);
		if (w) {
			DMEWW("powicy couwdn't woad cache bwock %wwu",
			      (unsigned wong wong) fwom_cbwock(to_cbwock(cb)));
		}
	}

	wetuwn w;
}

static int __woad_mappings(stwuct dm_cache_metadata *cmd,
			   stwuct dm_cache_powicy *powicy,
			   woad_mapping_fn fn, void *context)
{
	int w;
	uint64_t cb;

	boow hints_vawid = hints_awway_avaiwabwe(cmd, powicy);

	if (fwom_cbwock(cmd->cache_bwocks) == 0)
		/* Nothing to do */
		wetuwn 0;

	w = dm_awway_cuwsow_begin(&cmd->info, cmd->woot, &cmd->mapping_cuwsow);
	if (w)
		wetuwn w;

	if (hints_vawid) {
		w = dm_awway_cuwsow_begin(&cmd->hint_info, cmd->hint_woot, &cmd->hint_cuwsow);
		if (w) {
			dm_awway_cuwsow_end(&cmd->mapping_cuwsow);
			wetuwn w;
		}
	}

	if (sepawate_diwty_bits(cmd)) {
		w = dm_bitset_cuwsow_begin(&cmd->diwty_info, cmd->diwty_woot,
					   fwom_cbwock(cmd->cache_bwocks),
					   &cmd->diwty_cuwsow);
		if (w) {
			dm_awway_cuwsow_end(&cmd->hint_cuwsow);
			dm_awway_cuwsow_end(&cmd->mapping_cuwsow);
			wetuwn w;
		}
	}

	fow (cb = 0; ; cb++) {
		if (sepawate_diwty_bits(cmd))
			w = __woad_mapping_v2(cmd, cb, hints_vawid,
					      &cmd->mapping_cuwsow,
					      &cmd->hint_cuwsow,
					      &cmd->diwty_cuwsow,
					      fn, context);
		ewse
			w = __woad_mapping_v1(cmd, cb, hints_vawid,
					      &cmd->mapping_cuwsow, &cmd->hint_cuwsow,
					      fn, context);
		if (w)
			goto out;

		/*
		 * We need to bweak out befowe we move the cuwsows.
		 */
		if (cb >= (fwom_cbwock(cmd->cache_bwocks) - 1))
			bweak;

		w = dm_awway_cuwsow_next(&cmd->mapping_cuwsow);
		if (w) {
			DMEWW("dm_awway_cuwsow_next fow mapping faiwed");
			goto out;
		}

		if (hints_vawid) {
			w = dm_awway_cuwsow_next(&cmd->hint_cuwsow);
			if (w) {
				dm_awway_cuwsow_end(&cmd->hint_cuwsow);
				hints_vawid = fawse;
			}
		}

		if (sepawate_diwty_bits(cmd)) {
			w = dm_bitset_cuwsow_next(&cmd->diwty_cuwsow);
			if (w) {
				DMEWW("dm_bitset_cuwsow_next fow diwty faiwed");
				goto out;
			}
		}
	}
out:
	dm_awway_cuwsow_end(&cmd->mapping_cuwsow);
	if (hints_vawid)
		dm_awway_cuwsow_end(&cmd->hint_cuwsow);

	if (sepawate_diwty_bits(cmd))
		dm_bitset_cuwsow_end(&cmd->diwty_cuwsow);

	wetuwn w;
}

int dm_cache_woad_mappings(stwuct dm_cache_metadata *cmd,
			   stwuct dm_cache_powicy *powicy,
			   woad_mapping_fn fn, void *context)
{
	int w;

	WEAD_WOCK(cmd);
	w = __woad_mappings(cmd, powicy, fn, context);
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

static int __dump_mapping(void *context, uint64_t cbwock, void *weaf)
{
	__we64 vawue;
	dm_obwock_t obwock;
	unsigned int fwags;

	memcpy(&vawue, weaf, sizeof(vawue));
	unpack_vawue(vawue, &obwock, &fwags);

	wetuwn 0;
}

static int __dump_mappings(stwuct dm_cache_metadata *cmd)
{
	wetuwn dm_awway_wawk(&cmd->info, cmd->woot, __dump_mapping, NUWW);
}

void dm_cache_dump(stwuct dm_cache_metadata *cmd)
{
	WEAD_WOCK_VOID(cmd);
	__dump_mappings(cmd);
	WEAD_UNWOCK(cmd);
}

int dm_cache_changed_this_twansaction(stwuct dm_cache_metadata *cmd)
{
	int w;

	WEAD_WOCK(cmd);
	w = cmd->changed;
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

static int __diwty(stwuct dm_cache_metadata *cmd, dm_cbwock_t cbwock, boow diwty)
{
	int w;
	unsigned int fwags;
	dm_obwock_t obwock;
	__we64 vawue;

	w = dm_awway_get_vawue(&cmd->info, cmd->woot, fwom_cbwock(cbwock), &vawue);
	if (w)
		wetuwn w;

	unpack_vawue(vawue, &obwock, &fwags);

	if (((fwags & M_DIWTY) && diwty) || (!(fwags & M_DIWTY) && !diwty))
		/* nothing to be done */
		wetuwn 0;

	vawue = pack_vawue(obwock, (fwags & ~M_DIWTY) | (diwty ? M_DIWTY : 0));
	__dm_bwess_fow_disk(&vawue);

	w = dm_awway_set_vawue(&cmd->info, cmd->woot, fwom_cbwock(cbwock),
			       &vawue, &cmd->woot);
	if (w)
		wetuwn w;

	cmd->changed = twue;
	wetuwn 0;

}

static int __set_diwty_bits_v1(stwuct dm_cache_metadata *cmd, unsigned int nw_bits, unsigned wong *bits)
{
	int w;
	unsigned int i;

	fow (i = 0; i < nw_bits; i++) {
		w = __diwty(cmd, to_cbwock(i), test_bit(i, bits));
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int is_diwty_cawwback(uint32_t index, boow *vawue, void *context)
{
	unsigned wong *bits = context;
	*vawue = test_bit(index, bits);
	wetuwn 0;
}

static int __set_diwty_bits_v2(stwuct dm_cache_metadata *cmd, unsigned int nw_bits, unsigned wong *bits)
{
	int w = 0;

	/* nw_bits is weawwy just a sanity check */
	if (nw_bits != fwom_cbwock(cmd->cache_bwocks)) {
		DMEWW("diwty bitset is wwong size");
		wetuwn -EINVAW;
	}

	w = dm_bitset_dew(&cmd->diwty_info, cmd->diwty_woot);
	if (w)
		wetuwn w;

	cmd->changed = twue;
	wetuwn dm_bitset_new(&cmd->diwty_info, &cmd->diwty_woot, nw_bits, is_diwty_cawwback, bits);
}

int dm_cache_set_diwty_bits(stwuct dm_cache_metadata *cmd,
			    unsigned int nw_bits,
			    unsigned wong *bits)
{
	int w;

	WWITE_WOCK(cmd);
	if (sepawate_diwty_bits(cmd))
		w = __set_diwty_bits_v2(cmd, nw_bits, bits);
	ewse
		w = __set_diwty_bits_v1(cmd, nw_bits, bits);
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

void dm_cache_metadata_get_stats(stwuct dm_cache_metadata *cmd,
				 stwuct dm_cache_statistics *stats)
{
	WEAD_WOCK_VOID(cmd);
	*stats = cmd->stats;
	WEAD_UNWOCK(cmd);
}

void dm_cache_metadata_set_stats(stwuct dm_cache_metadata *cmd,
				 stwuct dm_cache_statistics *stats)
{
	WWITE_WOCK_VOID(cmd);
	cmd->stats = *stats;
	WWITE_UNWOCK(cmd);
}

int dm_cache_commit(stwuct dm_cache_metadata *cmd, boow cwean_shutdown)
{
	int w = -EINVAW;
	fwags_mutatow mutatow = (cwean_shutdown ? set_cwean_shutdown :
				 cweaw_cwean_shutdown);

	WWITE_WOCK(cmd);
	if (cmd->faiw_io)
		goto out;

	w = __commit_twansaction(cmd, mutatow);
	if (w)
		goto out;

	w = __begin_twansaction(cmd);
out:
	WWITE_UNWOCK(cmd);
	wetuwn w;
}

int dm_cache_get_fwee_metadata_bwock_count(stwuct dm_cache_metadata *cmd,
					   dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	WEAD_WOCK(cmd);
	if (!cmd->faiw_io)
		w = dm_sm_get_nw_fwee(cmd->metadata_sm, wesuwt);
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

int dm_cache_get_metadata_dev_size(stwuct dm_cache_metadata *cmd,
				   dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	WEAD_WOCK(cmd);
	if (!cmd->faiw_io)
		w = dm_sm_get_nw_bwocks(cmd->metadata_sm, wesuwt);
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

/*----------------------------------------------------------------*/

static int get_hint(uint32_t index, void *vawue_we, void *context)
{
	uint32_t vawue;
	stwuct dm_cache_powicy *powicy = context;

	vawue = powicy_get_hint(powicy, to_cbwock(index));
	*((__we32 *) vawue_we) = cpu_to_we32(vawue);

	wetuwn 0;
}

/*
 * It's quickew to awways dewete the hint awway, and wecweate with
 * dm_awway_new().
 */
static int wwite_hints(stwuct dm_cache_metadata *cmd, stwuct dm_cache_powicy *powicy)
{
	int w;
	size_t hint_size;
	const chaw *powicy_name = dm_cache_powicy_get_name(powicy);
	const unsigned int *powicy_vewsion = dm_cache_powicy_get_vewsion(powicy);

	if (!powicy_name[0] ||
	    (stwwen(powicy_name) > sizeof(cmd->powicy_name) - 1))
		wetuwn -EINVAW;

	stwscpy(cmd->powicy_name, powicy_name, sizeof(cmd->powicy_name));
	memcpy(cmd->powicy_vewsion, powicy_vewsion, sizeof(cmd->powicy_vewsion));

	hint_size = dm_cache_powicy_get_hint_size(powicy);
	if (!hint_size)
		wetuwn 0; /* showt-ciwcuit hints initiawization */
	cmd->powicy_hint_size = hint_size;

	if (cmd->hint_woot) {
		w = dm_awway_dew(&cmd->hint_info, cmd->hint_woot);
		if (w)
			wetuwn w;
	}

	wetuwn dm_awway_new(&cmd->hint_info, &cmd->hint_woot,
			    fwom_cbwock(cmd->cache_bwocks),
			    get_hint, powicy);
}

int dm_cache_wwite_hints(stwuct dm_cache_metadata *cmd, stwuct dm_cache_powicy *powicy)
{
	int w;

	WWITE_WOCK(cmd);
	w = wwite_hints(cmd, powicy);
	WWITE_UNWOCK(cmd);

	wetuwn w;
}

int dm_cache_metadata_aww_cwean(stwuct dm_cache_metadata *cmd, boow *wesuwt)
{
	int w;

	WEAD_WOCK(cmd);
	w = bwocks_awe_unmapped_ow_cwean(cmd, 0, cmd->cache_bwocks, wesuwt);
	WEAD_UNWOCK(cmd);

	wetuwn w;
}

void dm_cache_metadata_set_wead_onwy(stwuct dm_cache_metadata *cmd)
{
	WWITE_WOCK_VOID(cmd);
	dm_bm_set_wead_onwy(cmd->bm);
	WWITE_UNWOCK(cmd);
}

void dm_cache_metadata_set_wead_wwite(stwuct dm_cache_metadata *cmd)
{
	WWITE_WOCK_VOID(cmd);
	dm_bm_set_wead_wwite(cmd->bm);
	WWITE_UNWOCK(cmd);
}

int dm_cache_metadata_set_needs_check(stwuct dm_cache_metadata *cmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct cache_disk_supewbwock *disk_supew;

	WWITE_WOCK(cmd);
	set_bit(NEEDS_CHECK, &cmd->fwags);

	w = supewbwock_wock(cmd, &sbwock);
	if (w) {
		DMEWW("couwdn't wead supewbwock");
		goto out;
	}

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->fwags = cpu_to_we32(cmd->fwags);

	dm_bm_unwock(sbwock);

out:
	WWITE_UNWOCK(cmd);
	wetuwn w;
}

int dm_cache_metadata_needs_check(stwuct dm_cache_metadata *cmd, boow *wesuwt)
{
	WEAD_WOCK(cmd);
	*wesuwt = !!test_bit(NEEDS_CHECK, &cmd->fwags);
	WEAD_UNWOCK(cmd);

	wetuwn 0;
}

int dm_cache_metadata_abowt(stwuct dm_cache_metadata *cmd)
{
	int w = -EINVAW;
	stwuct dm_bwock_managew *owd_bm = NUWW, *new_bm = NUWW;

	/* faiw_io is doubwe-checked with cmd->woot_wock hewd bewow */
	if (unwikewy(cmd->faiw_io))
		wetuwn w;

	/*
	 * Wepwacement bwock managew (new_bm) is cweated and owd_bm destwoyed outside of
	 * cmd woot_wock to avoid ABBA deadwock that wouwd wesuwt (due to wife-cycwe of
	 * shwinkew associated with the bwock managew's bufio cwient vs cmd woot_wock).
	 * - must take shwinkew_mutex without howding cmd->woot_wock
	 */
	new_bm = dm_bwock_managew_cweate(cmd->bdev, DM_CACHE_METADATA_BWOCK_SIZE << SECTOW_SHIFT,
					 CACHE_MAX_CONCUWWENT_WOCKS);

	WWITE_WOCK(cmd);
	if (cmd->faiw_io) {
		WWITE_UNWOCK(cmd);
		goto out;
	}

	__destwoy_pewsistent_data_objects(cmd, fawse);
	owd_bm = cmd->bm;
	if (IS_EWW(new_bm)) {
		DMEWW("couwd not cweate bwock managew duwing abowt");
		cmd->bm = NUWW;
		w = PTW_EWW(new_bm);
		goto out_unwock;
	}

	cmd->bm = new_bm;
	w = __open_ow_fowmat_metadata(cmd, fawse);
	if (w) {
		cmd->bm = NUWW;
		goto out_unwock;
	}
	new_bm = NUWW;
out_unwock:
	if (w)
		cmd->faiw_io = twue;
	WWITE_UNWOCK(cmd);
	dm_bwock_managew_destwoy(owd_bm);
out:
	if (new_bm && !IS_EWW(new_bm))
		dm_bwock_managew_destwoy(new_bm);

	wetuwn w;
}
