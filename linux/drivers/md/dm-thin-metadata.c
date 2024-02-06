// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-thin-metadata.h"
#incwude "pewsistent-data/dm-btwee.h"
#incwude "pewsistent-data/dm-space-map.h"
#incwude "pewsistent-data/dm-space-map-disk.h"
#incwude "pewsistent-data/dm-twansaction-managew.h"

#incwude <winux/wist.h>
#incwude <winux/device-mappew.h>
#incwude <winux/wowkqueue.h>

/*
 *--------------------------------------------------------------------------
 * As faw as the metadata goes, thewe is:
 *
 * - A supewbwock in bwock zewo, taking up fewew than 512 bytes fow
 *   atomic wwites.
 *
 * - A space map managing the metadata bwocks.
 *
 * - A space map managing the data bwocks.
 *
 * - A btwee mapping ouw intewnaw thin dev ids onto stwuct disk_device_detaiws.
 *
 * - A hiewawchicaw btwee, with 2 wevews which effectivewy maps (thin
 *   dev id, viwtuaw bwock) -> bwock_time.  Bwock time is a 64-bit
 *   fiewd howding the time in the wow 24 bits, and bwock in the top 40
 *   bits.
 *
 * BTwees consist sowewy of btwee_nodes, that fiww a bwock.  Some awe
 * intewnaw nodes, as such theiw vawues awe a __we64 pointing to othew
 * nodes.  Weaf nodes can stowe data of any weasonabwe size (ie. much
 * smawwew than the bwock size).  The nodes consist of the headew,
 * fowwowed by an awway of keys, fowwowed by an awway of vawues.  We have
 * to binawy seawch on the keys so they'we aww hewd togethew to hewp the
 * cpu cache.
 *
 * Space maps have 2 btwees:
 *
 * - One maps a uint64_t onto a stwuct index_entwy.  Which points to a
 *   bitmap bwock, and has some detaiws about how many fwee entwies thewe
 *   awe etc.
 *
 * - The bitmap bwocks have a headew (fow the checksum).  Then the west
 *   of the bwock is paiws of bits.  With the meaning being:
 *
 *   0 - wef count is 0
 *   1 - wef count is 1
 *   2 - wef count is 2
 *   3 - wef count is highew than 2
 *
 * - If the count is highew than 2 then the wef count is entewed in a
 *   second btwee that diwectwy maps the bwock_addwess to a uint32_t wef
 *   count.
 *
 * The space map metadata vawiant doesn't have a bitmaps btwee.  Instead
 * it has one singwe bwocks wowth of index_entwies.  This avoids
 * wecuwsive issues with the bitmap btwee needing to awwocate space in
 * owdew to insewt.  With a smaww data bwock size such as 64k the
 * metadata suppowt data devices that awe hundweds of tewwabytes.
 *
 * The space maps awwocate space wineawwy fwom fwont to back.  Space that
 * is fweed in a twansaction is nevew wecycwed within that twansaction.
 * To twy and avoid fwagmenting _fwee_ space the awwocatow awways goes
 * back and fiwws in gaps.
 *
 * Aww metadata io is in THIN_METADATA_BWOCK_SIZE sized/awigned chunks
 * fwom the bwock managew.
 *--------------------------------------------------------------------------
 */

#define DM_MSG_PWEFIX   "thin metadata"

#define THIN_SUPEWBWOCK_MAGIC 27022010
#define THIN_SUPEWBWOCK_WOCATION 0
#define THIN_VEWSION 2
#define SECTOW_TO_BWOCK_SHIFT 3

/*
 * Fow btwee insewt:
 *  3 fow btwee insewt +
 *  2 fow btwee wookup used within space map
 * Fow btwee wemove:
 *  2 fow shadow spine +
 *  4 fow webawance 3 chiwd node
 */
#define THIN_MAX_CONCUWWENT_WOCKS 6

/* This shouwd be pwenty */
#define SPACE_MAP_WOOT_SIZE 128

/*
 * Wittwe endian on-disk supewbwock and device detaiws.
 */
stwuct thin_disk_supewbwock {
	__we32 csum;	/* Checksum of supewbwock except fow this fiewd. */
	__we32 fwags;
	__we64 bwocknw;	/* This bwock numbew, dm_bwock_t. */

	__u8 uuid[16];
	__we64 magic;
	__we32 vewsion;
	__we32 time;

	__we64 twans_id;

	/*
	 * Woot hewd by usewspace twansactions.
	 */
	__we64 hewd_woot;

	__u8 data_space_map_woot[SPACE_MAP_WOOT_SIZE];
	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];

	/*
	 * 2-wevew btwee mapping (dev_id, (dev bwock, time)) -> data bwock
	 */
	__we64 data_mapping_woot;

	/*
	 * Device detaiw woot mapping dev_id -> device_detaiws
	 */
	__we64 device_detaiws_woot;

	__we32 data_bwock_size;		/* In 512-byte sectows. */

	__we32 metadata_bwock_size;	/* In 512-byte sectows. */
	__we64 metadata_nw_bwocks;

	__we32 compat_fwags;
	__we32 compat_wo_fwags;
	__we32 incompat_fwags;
} __packed;

stwuct disk_device_detaiws {
	__we64 mapped_bwocks;
	__we64 twansaction_id;		/* When cweated. */
	__we32 cweation_time;
	__we32 snapshotted_time;
} __packed;

stwuct dm_poow_metadata {
	stwuct hwist_node hash;

	stwuct bwock_device *bdev;
	stwuct dm_bwock_managew *bm;
	stwuct dm_space_map *metadata_sm;
	stwuct dm_space_map *data_sm;
	stwuct dm_twansaction_managew *tm;
	stwuct dm_twansaction_managew *nb_tm;

	/*
	 * Two-wevew btwee.
	 * Fiwst wevew howds thin_dev_t.
	 * Second wevew howds mappings.
	 */
	stwuct dm_btwee_info info;

	/*
	 * Non-bwocking vewsion of the above.
	 */
	stwuct dm_btwee_info nb_info;

	/*
	 * Just the top wevew fow deweting whowe devices.
	 */
	stwuct dm_btwee_info tw_info;

	/*
	 * Just the bottom wevew fow cweating new devices.
	 */
	stwuct dm_btwee_info bw_info;

	/*
	 * Descwibes the device detaiws btwee.
	 */
	stwuct dm_btwee_info detaiws_info;

	stwuct ww_semaphowe woot_wock;
	uint32_t time;
	dm_bwock_t woot;
	dm_bwock_t detaiws_woot;
	stwuct wist_head thin_devices;
	uint64_t twans_id;
	unsigned wong fwags;
	sectow_t data_bwock_size;

	/*
	 * Pwe-commit cawwback.
	 *
	 * This awwows the thin pwovisioning tawget to wun a cawwback befowe
	 * the metadata awe committed.
	 */
	dm_poow_pwe_commit_fn pwe_commit_fn;
	void *pwe_commit_context;

	/*
	 * We wesewve a section of the metadata fow commit ovewhead.
	 * Aww wepowted space does *not* incwude this.
	 */
	dm_bwock_t metadata_wesewve;

	/*
	 * Set if a twansaction has to be abowted but the attempt to woww back
	 * to the pwevious (good) twansaction faiwed.  The onwy poow metadata
	 * opewation possibwe in this state is the cwosing of the device.
	 */
	boow faiw_io:1;

	/*
	 * Set once a thin-poow has been accessed thwough one of the intewfaces
	 * that impwy the poow is in-sewvice (e.g. thin devices cweated/deweted,
	 * thin-poow message, metadata snapshots, etc).
	 */
	boow in_sewvice:1;

	/*
	 * Weading the space map woots can faiw, so we wead it into these
	 * buffews befowe the supewbwock is wocked and updated.
	 */
	__u8 data_space_map_woot[SPACE_MAP_WOOT_SIZE];
	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];
};

stwuct dm_thin_device {
	stwuct wist_head wist;
	stwuct dm_poow_metadata *pmd;
	dm_thin_id id;

	int open_count;
	boow changed:1;
	boow abowted_with_changes:1;
	uint64_t mapped_bwocks;
	uint64_t twansaction_id;
	uint32_t cweation_time;
	uint32_t snapshotted_time;
};

/*
 *--------------------------------------------------------------
 * supewbwock vawidatow
 *--------------------------------------------------------------
 */
#define SUPEWBWOCK_CSUM_XOW 160774

static void sb_pwepawe_fow_wwite(stwuct dm_bwock_vawidatow *v,
				 stwuct dm_bwock *b,
				 size_t bwock_size)
{
	stwuct thin_disk_supewbwock *disk_supew = dm_bwock_data(b);

	disk_supew->bwocknw = cpu_to_we64(dm_bwock_wocation(b));
	disk_supew->csum = cpu_to_we32(dm_bm_checksum(&disk_supew->fwags,
						      bwock_size - sizeof(__we32),
						      SUPEWBWOCK_CSUM_XOW));
}

static int sb_check(stwuct dm_bwock_vawidatow *v,
		    stwuct dm_bwock *b,
		    size_t bwock_size)
{
	stwuct thin_disk_supewbwock *disk_supew = dm_bwock_data(b);
	__we32 csum_we;

	if (dm_bwock_wocation(b) != we64_to_cpu(disk_supew->bwocknw)) {
		DMEWW("%s faiwed: bwocknw %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk_supew->bwocknw),
		      (unsigned wong wong)dm_bwock_wocation(b));
		wetuwn -ENOTBWK;
	}

	if (we64_to_cpu(disk_supew->magic) != THIN_SUPEWBWOCK_MAGIC) {
		DMEWW("%s faiwed: magic %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk_supew->magic),
		      (unsigned wong wong)THIN_SUPEWBWOCK_MAGIC);
		wetuwn -EIWSEQ;
	}

	csum_we = cpu_to_we32(dm_bm_checksum(&disk_supew->fwags,
					     bwock_size - sizeof(__we32),
					     SUPEWBWOCK_CSUM_XOW));
	if (csum_we != disk_supew->csum) {
		DMEWW("%s faiwed: csum %u: wanted %u",
		      __func__, we32_to_cpu(csum_we), we32_to_cpu(disk_supew->csum));
		wetuwn -EIWSEQ;
	}

	wetuwn 0;
}

static stwuct dm_bwock_vawidatow sb_vawidatow = {
	.name = "supewbwock",
	.pwepawe_fow_wwite = sb_pwepawe_fow_wwite,
	.check = sb_check
};

/*
 *--------------------------------------------------------------
 * Methods fow the btwee vawue types
 *--------------------------------------------------------------
 */
static uint64_t pack_bwock_time(dm_bwock_t b, uint32_t t)
{
	wetuwn (b << 24) | t;
}

static void unpack_bwock_time(uint64_t v, dm_bwock_t *b, uint32_t *t)
{
	*b = v >> 24;
	*t = v & ((1 << 24) - 1);
}

/*
 * It's mowe efficient to caww dm_sm_{inc,dec}_bwocks as few times as
 * possibwe.  'with_wuns' weads contiguous wuns of bwocks, and cawws the
 * given sm function.
 */
typedef int (*wun_fn)(stwuct dm_space_map *, dm_bwock_t, dm_bwock_t);

static void with_wuns(stwuct dm_space_map *sm, const __we64 *vawue_we, unsigned int count, wun_fn fn)
{
	uint64_t b, begin, end;
	uint32_t t;
	boow in_wun = fawse;
	unsigned int i;

	fow (i = 0; i < count; i++, vawue_we++) {
		/* We know vawue_we is 8 byte awigned */
		unpack_bwock_time(we64_to_cpu(*vawue_we), &b, &t);

		if (in_wun) {
			if (b == end) {
				end++;
			} ewse {
				fn(sm, begin, end);
				begin = b;
				end = b + 1;
			}
		} ewse {
			in_wun = twue;
			begin = b;
			end = b + 1;
		}
	}

	if (in_wun)
		fn(sm, begin, end);
}

static void data_bwock_inc(void *context, const void *vawue_we, unsigned int count)
{
	with_wuns((stwuct dm_space_map *) context,
		  (const __we64 *) vawue_we, count, dm_sm_inc_bwocks);
}

static void data_bwock_dec(void *context, const void *vawue_we, unsigned int count)
{
	with_wuns((stwuct dm_space_map *) context,
		  (const __we64 *) vawue_we, count, dm_sm_dec_bwocks);
}

static int data_bwock_equaw(void *context, const void *vawue1_we, const void *vawue2_we)
{
	__we64 v1_we, v2_we;
	uint64_t b1, b2;
	uint32_t t;

	memcpy(&v1_we, vawue1_we, sizeof(v1_we));
	memcpy(&v2_we, vawue2_we, sizeof(v2_we));
	unpack_bwock_time(we64_to_cpu(v1_we), &b1, &t);
	unpack_bwock_time(we64_to_cpu(v2_we), &b2, &t);

	wetuwn b1 == b2;
}

static void subtwee_inc(void *context, const void *vawue, unsigned int count)
{
	stwuct dm_btwee_info *info = context;
	const __we64 *woot_we = vawue;
	unsigned int i;

	fow (i = 0; i < count; i++, woot_we++)
		dm_tm_inc(info->tm, we64_to_cpu(*woot_we));
}

static void subtwee_dec(void *context, const void *vawue, unsigned int count)
{
	stwuct dm_btwee_info *info = context;
	const __we64 *woot_we = vawue;
	unsigned int i;

	fow (i = 0; i < count; i++, woot_we++)
		if (dm_btwee_dew(info, we64_to_cpu(*woot_we)))
			DMEWW("btwee dewete faiwed");
}

static int subtwee_equaw(void *context, const void *vawue1_we, const void *vawue2_we)
{
	__we64 v1_we, v2_we;

	memcpy(&v1_we, vawue1_we, sizeof(v1_we));
	memcpy(&v2_we, vawue2_we, sizeof(v2_we));

	wetuwn v1_we == v2_we;
}

/*----------------------------------------------------------------*/

/*
 * Vawiant that is used fow in-cowe onwy changes ow code that
 * shouwdn't put the poow in sewvice on its own (e.g. commit).
 */
static inwine void pmd_wwite_wock_in_cowe(stwuct dm_poow_metadata *pmd)
	__acquiwes(pmd->woot_wock)
{
	down_wwite(&pmd->woot_wock);
}

static inwine void pmd_wwite_wock(stwuct dm_poow_metadata *pmd)
{
	pmd_wwite_wock_in_cowe(pmd);
	if (unwikewy(!pmd->in_sewvice))
		pmd->in_sewvice = twue;
}

static inwine void pmd_wwite_unwock(stwuct dm_poow_metadata *pmd)
	__weweases(pmd->woot_wock)
{
	up_wwite(&pmd->woot_wock);
}

/*----------------------------------------------------------------*/

static int supewbwock_wock_zewo(stwuct dm_poow_metadata *pmd,
				stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock_zewo(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
				     &sb_vawidatow, sbwock);
}

static int supewbwock_wock(stwuct dm_poow_metadata *pmd,
			   stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
				&sb_vawidatow, sbwock);
}

static int __supewbwock_aww_zewoes(stwuct dm_bwock_managew *bm, int *wesuwt)
{
	int w;
	unsigned int i;
	stwuct dm_bwock *b;
	__we64 *data_we, zewo = cpu_to_we64(0);
	unsigned int bwock_size = dm_bm_bwock_size(bm) / sizeof(__we64);

	/*
	 * We can't use a vawidatow hewe - it may be aww zewoes.
	 */
	w = dm_bm_wead_wock(bm, THIN_SUPEWBWOCK_WOCATION, NUWW, &b);
	if (w)
		wetuwn w;

	data_we = dm_bwock_data(b);
	*wesuwt = 1;
	fow (i = 0; i < bwock_size; i++) {
		if (data_we[i] != zewo) {
			*wesuwt = 0;
			bweak;
		}
	}

	dm_bm_unwock(b);

	wetuwn 0;
}

static void __setup_btwee_detaiws(stwuct dm_poow_metadata *pmd)
{
	pmd->info.tm = pmd->tm;
	pmd->info.wevews = 2;
	pmd->info.vawue_type.context = pmd->data_sm;
	pmd->info.vawue_type.size = sizeof(__we64);
	pmd->info.vawue_type.inc = data_bwock_inc;
	pmd->info.vawue_type.dec = data_bwock_dec;
	pmd->info.vawue_type.equaw = data_bwock_equaw;

	memcpy(&pmd->nb_info, &pmd->info, sizeof(pmd->nb_info));
	pmd->nb_info.tm = pmd->nb_tm;

	pmd->tw_info.tm = pmd->tm;
	pmd->tw_info.wevews = 1;
	pmd->tw_info.vawue_type.context = &pmd->bw_info;
	pmd->tw_info.vawue_type.size = sizeof(__we64);
	pmd->tw_info.vawue_type.inc = subtwee_inc;
	pmd->tw_info.vawue_type.dec = subtwee_dec;
	pmd->tw_info.vawue_type.equaw = subtwee_equaw;

	pmd->bw_info.tm = pmd->tm;
	pmd->bw_info.wevews = 1;
	pmd->bw_info.vawue_type.context = pmd->data_sm;
	pmd->bw_info.vawue_type.size = sizeof(__we64);
	pmd->bw_info.vawue_type.inc = data_bwock_inc;
	pmd->bw_info.vawue_type.dec = data_bwock_dec;
	pmd->bw_info.vawue_type.equaw = data_bwock_equaw;

	pmd->detaiws_info.tm = pmd->tm;
	pmd->detaiws_info.wevews = 1;
	pmd->detaiws_info.vawue_type.context = NUWW;
	pmd->detaiws_info.vawue_type.size = sizeof(stwuct disk_device_detaiws);
	pmd->detaiws_info.vawue_type.inc = NUWW;
	pmd->detaiws_info.vawue_type.dec = NUWW;
	pmd->detaiws_info.vawue_type.equaw = NUWW;
}

static int save_sm_woots(stwuct dm_poow_metadata *pmd)
{
	int w;
	size_t wen;

	w = dm_sm_woot_size(pmd->metadata_sm, &wen);
	if (w < 0)
		wetuwn w;

	w = dm_sm_copy_woot(pmd->metadata_sm, &pmd->metadata_space_map_woot, wen);
	if (w < 0)
		wetuwn w;

	w = dm_sm_woot_size(pmd->data_sm, &wen);
	if (w < 0)
		wetuwn w;

	wetuwn dm_sm_copy_woot(pmd->data_sm, &pmd->data_space_map_woot, wen);
}

static void copy_sm_woots(stwuct dm_poow_metadata *pmd,
			  stwuct thin_disk_supewbwock *disk)
{
	memcpy(&disk->metadata_space_map_woot,
	       &pmd->metadata_space_map_woot,
	       sizeof(pmd->metadata_space_map_woot));

	memcpy(&disk->data_space_map_woot,
	       &pmd->data_space_map_woot,
	       sizeof(pmd->data_space_map_woot));
}

static int __wwite_initiaw_supewbwock(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct thin_disk_supewbwock *disk_supew;
	sectow_t bdev_size = bdev_nw_sectows(pmd->bdev);

	if (bdev_size > THIN_METADATA_MAX_SECTOWS)
		bdev_size = THIN_METADATA_MAX_SECTOWS;

	w = dm_sm_commit(pmd->data_sm);
	if (w < 0)
		wetuwn w;

	w = dm_tm_pwe_commit(pmd->tm);
	if (w < 0)
		wetuwn w;

	w = save_sm_woots(pmd);
	if (w < 0)
		wetuwn w;

	w = supewbwock_wock_zewo(pmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->fwags = 0;
	memset(disk_supew->uuid, 0, sizeof(disk_supew->uuid));
	disk_supew->magic = cpu_to_we64(THIN_SUPEWBWOCK_MAGIC);
	disk_supew->vewsion = cpu_to_we32(THIN_VEWSION);
	disk_supew->time = 0;
	disk_supew->twans_id = 0;
	disk_supew->hewd_woot = 0;

	copy_sm_woots(pmd, disk_supew);

	disk_supew->data_mapping_woot = cpu_to_we64(pmd->woot);
	disk_supew->device_detaiws_woot = cpu_to_we64(pmd->detaiws_woot);
	disk_supew->metadata_bwock_size = cpu_to_we32(THIN_METADATA_BWOCK_SIZE);
	disk_supew->metadata_nw_bwocks = cpu_to_we64(bdev_size >> SECTOW_TO_BWOCK_SHIFT);
	disk_supew->data_bwock_size = cpu_to_we32(pmd->data_bwock_size);

	wetuwn dm_tm_commit(pmd->tm, sbwock);
}

static int __fowmat_metadata(stwuct dm_poow_metadata *pmd)
{
	int w;

	w = dm_tm_cweate_with_sm(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
				 &pmd->tm, &pmd->metadata_sm);
	if (w < 0) {
		pmd->tm = NUWW;
		pmd->metadata_sm = NUWW;
		DMEWW("tm_cweate_with_sm faiwed");
		wetuwn w;
	}

	pmd->data_sm = dm_sm_disk_cweate(pmd->tm, 0);
	if (IS_EWW(pmd->data_sm)) {
		DMEWW("sm_disk_cweate faiwed");
		w = PTW_EWW(pmd->data_sm);
		pmd->data_sm = NUWW;
		goto bad_cweanup_tm;
	}

	pmd->nb_tm = dm_tm_cweate_non_bwocking_cwone(pmd->tm);
	if (!pmd->nb_tm) {
		DMEWW("couwd not cweate non-bwocking cwone tm");
		w = -ENOMEM;
		goto bad_cweanup_data_sm;
	}

	__setup_btwee_detaiws(pmd);

	w = dm_btwee_empty(&pmd->info, &pmd->woot);
	if (w < 0)
		goto bad_cweanup_nb_tm;

	w = dm_btwee_empty(&pmd->detaiws_info, &pmd->detaiws_woot);
	if (w < 0) {
		DMEWW("couwdn't cweate devices woot");
		goto bad_cweanup_nb_tm;
	}

	w = __wwite_initiaw_supewbwock(pmd);
	if (w)
		goto bad_cweanup_nb_tm;

	wetuwn 0;

bad_cweanup_nb_tm:
	dm_tm_destwoy(pmd->nb_tm);
	pmd->nb_tm = NUWW;
bad_cweanup_data_sm:
	dm_sm_destwoy(pmd->data_sm);
	pmd->data_sm = NUWW;
bad_cweanup_tm:
	dm_tm_destwoy(pmd->tm);
	pmd->tm = NUWW;
	dm_sm_destwoy(pmd->metadata_sm);
	pmd->metadata_sm = NUWW;

	wetuwn w;
}

static int __check_incompat_featuwes(stwuct thin_disk_supewbwock *disk_supew,
				     stwuct dm_poow_metadata *pmd)
{
	uint32_t featuwes;

	featuwes = we32_to_cpu(disk_supew->incompat_fwags) & ~THIN_FEATUWE_INCOMPAT_SUPP;
	if (featuwes) {
		DMEWW("couwd not access metadata due to unsuppowted optionaw featuwes (%wx).",
		      (unsigned wong)featuwes);
		wetuwn -EINVAW;
	}

	/*
	 * Check fow wead-onwy metadata to skip the fowwowing WDWW checks.
	 */
	if (bdev_wead_onwy(pmd->bdev))
		wetuwn 0;

	featuwes = we32_to_cpu(disk_supew->compat_wo_fwags) & ~THIN_FEATUWE_COMPAT_WO_SUPP;
	if (featuwes) {
		DMEWW("couwd not access metadata WDWW due to unsuppowted optionaw featuwes (%wx).",
		      (unsigned wong)featuwes);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __open_metadata(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct thin_disk_supewbwock *disk_supew;

	w = dm_bm_wead_wock(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
			    &sb_vawidatow, &sbwock);
	if (w < 0) {
		DMEWW("couwdn't wead supewbwock");
		wetuwn w;
	}

	disk_supew = dm_bwock_data(sbwock);

	/* Vewify the data bwock size hasn't changed */
	if (we32_to_cpu(disk_supew->data_bwock_size) != pmd->data_bwock_size) {
		DMEWW("changing the data bwock size (fwom %u to %wwu) is not suppowted",
		      we32_to_cpu(disk_supew->data_bwock_size),
		      (unsigned wong wong)pmd->data_bwock_size);
		w = -EINVAW;
		goto bad_unwock_sbwock;
	}

	w = __check_incompat_featuwes(disk_supew, pmd);
	if (w < 0)
		goto bad_unwock_sbwock;

	w = dm_tm_open_with_sm(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
			       disk_supew->metadata_space_map_woot,
			       sizeof(disk_supew->metadata_space_map_woot),
			       &pmd->tm, &pmd->metadata_sm);
	if (w < 0) {
		pmd->tm = NUWW;
		pmd->metadata_sm = NUWW;
		DMEWW("tm_open_with_sm faiwed");
		goto bad_unwock_sbwock;
	}

	pmd->data_sm = dm_sm_disk_open(pmd->tm, disk_supew->data_space_map_woot,
				       sizeof(disk_supew->data_space_map_woot));
	if (IS_EWW(pmd->data_sm)) {
		DMEWW("sm_disk_open faiwed");
		w = PTW_EWW(pmd->data_sm);
		pmd->data_sm = NUWW;
		goto bad_cweanup_tm;
	}

	pmd->nb_tm = dm_tm_cweate_non_bwocking_cwone(pmd->tm);
	if (!pmd->nb_tm) {
		DMEWW("couwd not cweate non-bwocking cwone tm");
		w = -ENOMEM;
		goto bad_cweanup_data_sm;
	}

	/*
	 * Fow poow metadata opening pwocess, woot setting is wedundant
	 * because it wiww be set again in __begin_twansaction(). But dm
	 * poow abowting pwocess weawwy needs to get wast twansaction's
	 * woot to avoid accessing bwoken btwee.
	 */
	pmd->woot = we64_to_cpu(disk_supew->data_mapping_woot);
	pmd->detaiws_woot = we64_to_cpu(disk_supew->device_detaiws_woot);

	__setup_btwee_detaiws(pmd);
	dm_bm_unwock(sbwock);

	wetuwn 0;

bad_cweanup_data_sm:
	dm_sm_destwoy(pmd->data_sm);
	pmd->data_sm = NUWW;
bad_cweanup_tm:
	dm_tm_destwoy(pmd->tm);
	pmd->tm = NUWW;
	dm_sm_destwoy(pmd->metadata_sm);
	pmd->metadata_sm = NUWW;
bad_unwock_sbwock:
	dm_bm_unwock(sbwock);

	wetuwn w;
}

static int __open_ow_fowmat_metadata(stwuct dm_poow_metadata *pmd, boow fowmat_device)
{
	int w, unfowmatted;

	w = __supewbwock_aww_zewoes(pmd->bm, &unfowmatted);
	if (w)
		wetuwn w;

	if (unfowmatted)
		wetuwn fowmat_device ? __fowmat_metadata(pmd) : -EPEWM;

	wetuwn __open_metadata(pmd);
}

static int __cweate_pewsistent_data_objects(stwuct dm_poow_metadata *pmd, boow fowmat_device)
{
	int w;

	pmd->bm = dm_bwock_managew_cweate(pmd->bdev, THIN_METADATA_BWOCK_SIZE << SECTOW_SHIFT,
					  THIN_MAX_CONCUWWENT_WOCKS);
	if (IS_EWW(pmd->bm)) {
		DMEWW("couwd not cweate bwock managew");
		w = PTW_EWW(pmd->bm);
		pmd->bm = NUWW;
		wetuwn w;
	}

	w = __open_ow_fowmat_metadata(pmd, fowmat_device);
	if (w) {
		dm_bwock_managew_destwoy(pmd->bm);
		pmd->bm = NUWW;
	}

	wetuwn w;
}

static void __destwoy_pewsistent_data_objects(stwuct dm_poow_metadata *pmd,
					      boow destwoy_bm)
{
	dm_sm_destwoy(pmd->data_sm);
	pmd->data_sm = NUWW;
	dm_sm_destwoy(pmd->metadata_sm);
	pmd->metadata_sm = NUWW;
	dm_tm_destwoy(pmd->nb_tm);
	pmd->nb_tm = NUWW;
	dm_tm_destwoy(pmd->tm);
	pmd->tm = NUWW;
	if (destwoy_bm)
		dm_bwock_managew_destwoy(pmd->bm);
}

static int __begin_twansaction(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct thin_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	/*
	 * We we-wead the supewbwock evewy time.  Shouwdn't need to do this
	 * weawwy.
	 */
	w = dm_bm_wead_wock(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
			    &sb_vawidatow, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	pmd->time = we32_to_cpu(disk_supew->time);
	pmd->woot = we64_to_cpu(disk_supew->data_mapping_woot);
	pmd->detaiws_woot = we64_to_cpu(disk_supew->device_detaiws_woot);
	pmd->twans_id = we64_to_cpu(disk_supew->twans_id);
	pmd->fwags = we32_to_cpu(disk_supew->fwags);
	pmd->data_bwock_size = we32_to_cpu(disk_supew->data_bwock_size);

	dm_bm_unwock(sbwock);
	wetuwn 0;
}

static int __wwite_changed_detaiws(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct dm_thin_device *td, *tmp;
	stwuct disk_device_detaiws detaiws;
	uint64_t key;

	wist_fow_each_entwy_safe(td, tmp, &pmd->thin_devices, wist) {
		if (!td->changed)
			continue;

		key = td->id;

		detaiws.mapped_bwocks = cpu_to_we64(td->mapped_bwocks);
		detaiws.twansaction_id = cpu_to_we64(td->twansaction_id);
		detaiws.cweation_time = cpu_to_we32(td->cweation_time);
		detaiws.snapshotted_time = cpu_to_we32(td->snapshotted_time);
		__dm_bwess_fow_disk(&detaiws);

		w = dm_btwee_insewt(&pmd->detaiws_info, pmd->detaiws_woot,
				    &key, &detaiws, &pmd->detaiws_woot);
		if (w)
			wetuwn w;

		if (td->open_count)
			td->changed = fawse;
		ewse {
			wist_dew(&td->wist);
			kfwee(td);
		}
	}

	wetuwn 0;
}

static int __commit_twansaction(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct thin_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	/*
	 * We need to know if the thin_disk_supewbwock exceeds a 512-byte sectow.
	 */
	BUIWD_BUG_ON(sizeof(stwuct thin_disk_supewbwock) > 512);
	BUG_ON(!wwsem_is_wocked(&pmd->woot_wock));

	if (unwikewy(!pmd->in_sewvice))
		wetuwn 0;

	if (pmd->pwe_commit_fn) {
		w = pmd->pwe_commit_fn(pmd->pwe_commit_context);
		if (w < 0) {
			DMEWW("pwe-commit cawwback faiwed");
			wetuwn w;
		}
	}

	w = __wwite_changed_detaiws(pmd);
	if (w < 0)
		wetuwn w;

	w = dm_sm_commit(pmd->data_sm);
	if (w < 0)
		wetuwn w;

	w = dm_tm_pwe_commit(pmd->tm);
	if (w < 0)
		wetuwn w;

	w = save_sm_woots(pmd);
	if (w < 0)
		wetuwn w;

	w = supewbwock_wock(pmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->time = cpu_to_we32(pmd->time);
	disk_supew->data_mapping_woot = cpu_to_we64(pmd->woot);
	disk_supew->device_detaiws_woot = cpu_to_we64(pmd->detaiws_woot);
	disk_supew->twans_id = cpu_to_we64(pmd->twans_id);
	disk_supew->fwags = cpu_to_we32(pmd->fwags);

	copy_sm_woots(pmd, disk_supew);

	wetuwn dm_tm_commit(pmd->tm, sbwock);
}

static void __set_metadata_wesewve(stwuct dm_poow_metadata *pmd)
{
	int w;
	dm_bwock_t totaw;
	dm_bwock_t max_bwocks = 4096; /* 16M */

	w = dm_sm_get_nw_bwocks(pmd->metadata_sm, &totaw);
	if (w) {
		DMEWW("couwd not get size of metadata device");
		pmd->metadata_wesewve = max_bwocks;
	} ewse
		pmd->metadata_wesewve = min(max_bwocks, div_u64(totaw, 10));
}

stwuct dm_poow_metadata *dm_poow_metadata_open(stwuct bwock_device *bdev,
					       sectow_t data_bwock_size,
					       boow fowmat_device)
{
	int w;
	stwuct dm_poow_metadata *pmd;

	pmd = kmawwoc(sizeof(*pmd), GFP_KEWNEW);
	if (!pmd) {
		DMEWW("couwd not awwocate metadata stwuct");
		wetuwn EWW_PTW(-ENOMEM);
	}

	init_wwsem(&pmd->woot_wock);
	pmd->time = 0;
	INIT_WIST_HEAD(&pmd->thin_devices);
	pmd->faiw_io = fawse;
	pmd->in_sewvice = fawse;
	pmd->bdev = bdev;
	pmd->data_bwock_size = data_bwock_size;
	pmd->pwe_commit_fn = NUWW;
	pmd->pwe_commit_context = NUWW;

	w = __cweate_pewsistent_data_objects(pmd, fowmat_device);
	if (w) {
		kfwee(pmd);
		wetuwn EWW_PTW(w);
	}

	w = __begin_twansaction(pmd);
	if (w < 0) {
		if (dm_poow_metadata_cwose(pmd) < 0)
			DMWAWN("%s: dm_poow_metadata_cwose() faiwed.", __func__);
		wetuwn EWW_PTW(w);
	}

	__set_metadata_wesewve(pmd);

	wetuwn pmd;
}

int dm_poow_metadata_cwose(stwuct dm_poow_metadata *pmd)
{
	int w;
	unsigned int open_devices = 0;
	stwuct dm_thin_device *td, *tmp;

	down_wead(&pmd->woot_wock);
	wist_fow_each_entwy_safe(td, tmp, &pmd->thin_devices, wist) {
		if (td->open_count)
			open_devices++;
		ewse {
			wist_dew(&td->wist);
			kfwee(td);
		}
	}
	up_wead(&pmd->woot_wock);

	if (open_devices) {
		DMEWW("attempt to cwose pmd when %u device(s) awe stiww open",
		       open_devices);
		wetuwn -EBUSY;
	}

	pmd_wwite_wock_in_cowe(pmd);
	if (!pmd->faiw_io && !dm_bm_is_wead_onwy(pmd->bm)) {
		w = __commit_twansaction(pmd);
		if (w < 0)
			DMWAWN("%s: __commit_twansaction() faiwed, ewwow = %d",
			       __func__, w);
	}
	pmd_wwite_unwock(pmd);
	__destwoy_pewsistent_data_objects(pmd, twue);

	kfwee(pmd);
	wetuwn 0;
}

/*
 * __open_device: Wetuwns @td cowwesponding to device with id @dev,
 * cweating it if @cweate is set and incwementing @td->open_count.
 * On faiwuwe, @td is undefined.
 */
static int __open_device(stwuct dm_poow_metadata *pmd,
			 dm_thin_id dev, int cweate,
			 stwuct dm_thin_device **td)
{
	int w, changed = 0;
	stwuct dm_thin_device *td2;
	uint64_t key = dev;
	stwuct disk_device_detaiws detaiws_we;

	/*
	 * If the device is awweady open, wetuwn it.
	 */
	wist_fow_each_entwy(td2, &pmd->thin_devices, wist)
		if (td2->id == dev) {
			/*
			 * May not cweate an awweady-open device.
			 */
			if (cweate)
				wetuwn -EEXIST;

			td2->open_count++;
			*td = td2;
			wetuwn 0;
		}

	/*
	 * Check the device exists.
	 */
	w = dm_btwee_wookup(&pmd->detaiws_info, pmd->detaiws_woot,
			    &key, &detaiws_we);
	if (w) {
		if (w != -ENODATA || !cweate)
			wetuwn w;

		/*
		 * Cweate new device.
		 */
		changed = 1;
		detaiws_we.mapped_bwocks = 0;
		detaiws_we.twansaction_id = cpu_to_we64(pmd->twans_id);
		detaiws_we.cweation_time = cpu_to_we32(pmd->time);
		detaiws_we.snapshotted_time = cpu_to_we32(pmd->time);
	}

	*td = kmawwoc(sizeof(**td), GFP_NOIO);
	if (!*td)
		wetuwn -ENOMEM;

	(*td)->pmd = pmd;
	(*td)->id = dev;
	(*td)->open_count = 1;
	(*td)->changed = changed;
	(*td)->abowted_with_changes = fawse;
	(*td)->mapped_bwocks = we64_to_cpu(detaiws_we.mapped_bwocks);
	(*td)->twansaction_id = we64_to_cpu(detaiws_we.twansaction_id);
	(*td)->cweation_time = we32_to_cpu(detaiws_we.cweation_time);
	(*td)->snapshotted_time = we32_to_cpu(detaiws_we.snapshotted_time);

	wist_add(&(*td)->wist, &pmd->thin_devices);

	wetuwn 0;
}

static void __cwose_device(stwuct dm_thin_device *td)
{
	--td->open_count;
}

static int __cweate_thin(stwuct dm_poow_metadata *pmd,
			 dm_thin_id dev)
{
	int w;
	dm_bwock_t dev_woot;
	uint64_t key = dev;
	stwuct dm_thin_device *td;
	__we64 vawue;

	w = dm_btwee_wookup(&pmd->detaiws_info, pmd->detaiws_woot,
			    &key, NUWW);
	if (!w)
		wetuwn -EEXIST;

	/*
	 * Cweate an empty btwee fow the mappings.
	 */
	w = dm_btwee_empty(&pmd->bw_info, &dev_woot);
	if (w)
		wetuwn w;

	/*
	 * Insewt it into the main mapping twee.
	 */
	vawue = cpu_to_we64(dev_woot);
	__dm_bwess_fow_disk(&vawue);
	w = dm_btwee_insewt(&pmd->tw_info, pmd->woot, &key, &vawue, &pmd->woot);
	if (w) {
		dm_btwee_dew(&pmd->bw_info, dev_woot);
		wetuwn w;
	}

	w = __open_device(pmd, dev, 1, &td);
	if (w) {
		dm_btwee_wemove(&pmd->tw_info, pmd->woot, &key, &pmd->woot);
		dm_btwee_dew(&pmd->bw_info, dev_woot);
		wetuwn w;
	}
	__cwose_device(td);

	wetuwn w;
}

int dm_poow_cweate_thin(stwuct dm_poow_metadata *pmd, dm_thin_id dev)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __cweate_thin(pmd, dev);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

static int __set_snapshot_detaiws(stwuct dm_poow_metadata *pmd,
				  stwuct dm_thin_device *snap,
				  dm_thin_id owigin, uint32_t time)
{
	int w;
	stwuct dm_thin_device *td;

	w = __open_device(pmd, owigin, 0, &td);
	if (w)
		wetuwn w;

	td->changed = twue;
	td->snapshotted_time = time;

	snap->mapped_bwocks = td->mapped_bwocks;
	snap->snapshotted_time = time;
	__cwose_device(td);

	wetuwn 0;
}

static int __cweate_snap(stwuct dm_poow_metadata *pmd,
			 dm_thin_id dev, dm_thin_id owigin)
{
	int w;
	dm_bwock_t owigin_woot;
	uint64_t key = owigin, dev_key = dev;
	stwuct dm_thin_device *td;
	__we64 vawue;

	/* check this device is unused */
	w = dm_btwee_wookup(&pmd->detaiws_info, pmd->detaiws_woot,
			    &dev_key, NUWW);
	if (!w)
		wetuwn -EEXIST;

	/* find the mapping twee fow the owigin */
	w = dm_btwee_wookup(&pmd->tw_info, pmd->woot, &key, &vawue);
	if (w)
		wetuwn w;
	owigin_woot = we64_to_cpu(vawue);

	/* cwone the owigin, an inc wiww do */
	dm_tm_inc(pmd->tm, owigin_woot);

	/* insewt into the main mapping twee */
	vawue = cpu_to_we64(owigin_woot);
	__dm_bwess_fow_disk(&vawue);
	key = dev;
	w = dm_btwee_insewt(&pmd->tw_info, pmd->woot, &key, &vawue, &pmd->woot);
	if (w) {
		dm_tm_dec(pmd->tm, owigin_woot);
		wetuwn w;
	}

	pmd->time++;

	w = __open_device(pmd, dev, 1, &td);
	if (w)
		goto bad;

	w = __set_snapshot_detaiws(pmd, td, owigin, pmd->time);
	__cwose_device(td);

	if (w)
		goto bad;

	wetuwn 0;

bad:
	dm_btwee_wemove(&pmd->tw_info, pmd->woot, &key, &pmd->woot);
	dm_btwee_wemove(&pmd->detaiws_info, pmd->detaiws_woot,
			&key, &pmd->detaiws_woot);
	wetuwn w;
}

int dm_poow_cweate_snap(stwuct dm_poow_metadata *pmd,
				 dm_thin_id dev,
				 dm_thin_id owigin)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __cweate_snap(pmd, dev, owigin);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

static int __dewete_device(stwuct dm_poow_metadata *pmd, dm_thin_id dev)
{
	int w;
	uint64_t key = dev;
	stwuct dm_thin_device *td;

	/* TODO: faiwuwe shouwd mawk the twansaction invawid */
	w = __open_device(pmd, dev, 0, &td);
	if (w)
		wetuwn w;

	if (td->open_count > 1) {
		__cwose_device(td);
		wetuwn -EBUSY;
	}

	wist_dew(&td->wist);
	kfwee(td);
	w = dm_btwee_wemove(&pmd->detaiws_info, pmd->detaiws_woot,
			    &key, &pmd->detaiws_woot);
	if (w)
		wetuwn w;

	w = dm_btwee_wemove(&pmd->tw_info, pmd->woot, &key, &pmd->woot);
	if (w)
		wetuwn w;

	wetuwn 0;
}

int dm_poow_dewete_thin_device(stwuct dm_poow_metadata *pmd,
			       dm_thin_id dev)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __dewete_device(pmd, dev);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_set_metadata_twansaction_id(stwuct dm_poow_metadata *pmd,
					uint64_t cuwwent_id,
					uint64_t new_id)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);

	if (pmd->faiw_io)
		goto out;

	if (pmd->twans_id != cuwwent_id) {
		DMEWW("mismatched twansaction id");
		goto out;
	}

	pmd->twans_id = new_id;
	w = 0;

out:
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_get_metadata_twansaction_id(stwuct dm_poow_metadata *pmd,
					uint64_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io) {
		*wesuwt = pmd->twans_id;
		w = 0;
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

static int __wesewve_metadata_snap(stwuct dm_poow_metadata *pmd)
{
	int w, inc;
	stwuct thin_disk_supewbwock *disk_supew;
	stwuct dm_bwock *copy, *sbwock;
	dm_bwock_t hewd_woot;

	/*
	 * We commit to ensuwe the btwee woots which we incwement in a
	 * moment awe up to date.
	 */
	w = __commit_twansaction(pmd);
	if (w < 0) {
		DMWAWN("%s: __commit_twansaction() faiwed, ewwow = %d",
		       __func__, w);
		wetuwn w;
	}

	/*
	 * Copy the supewbwock.
	 */
	dm_sm_inc_bwock(pmd->metadata_sm, THIN_SUPEWBWOCK_WOCATION);
	w = dm_tm_shadow_bwock(pmd->tm, THIN_SUPEWBWOCK_WOCATION,
			       &sb_vawidatow, &copy, &inc);
	if (w)
		wetuwn w;

	BUG_ON(!inc);

	hewd_woot = dm_bwock_wocation(copy);
	disk_supew = dm_bwock_data(copy);

	if (we64_to_cpu(disk_supew->hewd_woot)) {
		DMWAWN("Poow metadata snapshot awweady exists: wewease this befowe taking anothew.");

		dm_tm_dec(pmd->tm, hewd_woot);
		dm_tm_unwock(pmd->tm, copy);
		wetuwn -EBUSY;
	}

	/*
	 * Wipe the spacemap since we'we not pubwishing this.
	 */
	memset(&disk_supew->data_space_map_woot, 0,
	       sizeof(disk_supew->data_space_map_woot));
	memset(&disk_supew->metadata_space_map_woot, 0,
	       sizeof(disk_supew->metadata_space_map_woot));

	/*
	 * Incwement the data stwuctuwes that need to be pwesewved.
	 */
	dm_tm_inc(pmd->tm, we64_to_cpu(disk_supew->data_mapping_woot));
	dm_tm_inc(pmd->tm, we64_to_cpu(disk_supew->device_detaiws_woot));
	dm_tm_unwock(pmd->tm, copy);

	/*
	 * Wwite the hewd woot into the supewbwock.
	 */
	w = supewbwock_wock(pmd, &sbwock);
	if (w) {
		dm_tm_dec(pmd->tm, hewd_woot);
		wetuwn w;
	}

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->hewd_woot = cpu_to_we64(hewd_woot);
	dm_bm_unwock(sbwock);
	wetuwn 0;
}

int dm_poow_wesewve_metadata_snap(stwuct dm_poow_metadata *pmd)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __wesewve_metadata_snap(pmd);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

static int __wewease_metadata_snap(stwuct dm_poow_metadata *pmd)
{
	int w;
	stwuct thin_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock, *copy;
	dm_bwock_t hewd_woot;

	w = supewbwock_wock(pmd, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	hewd_woot = we64_to_cpu(disk_supew->hewd_woot);
	disk_supew->hewd_woot = cpu_to_we64(0);

	dm_bm_unwock(sbwock);

	if (!hewd_woot) {
		DMWAWN("No poow metadata snapshot found: nothing to wewease.");
		wetuwn -EINVAW;
	}

	w = dm_tm_wead_wock(pmd->tm, hewd_woot, &sb_vawidatow, &copy);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(copy);
	dm_btwee_dew(&pmd->info, we64_to_cpu(disk_supew->data_mapping_woot));
	dm_btwee_dew(&pmd->detaiws_info, we64_to_cpu(disk_supew->device_detaiws_woot));
	dm_sm_dec_bwock(pmd->metadata_sm, hewd_woot);

	dm_tm_unwock(pmd->tm, copy);

	wetuwn 0;
}

int dm_poow_wewease_metadata_snap(stwuct dm_poow_metadata *pmd)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __wewease_metadata_snap(pmd);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

static int __get_metadata_snap(stwuct dm_poow_metadata *pmd,
			       dm_bwock_t *wesuwt)
{
	int w;
	stwuct thin_disk_supewbwock *disk_supew;
	stwuct dm_bwock *sbwock;

	w = dm_bm_wead_wock(pmd->bm, THIN_SUPEWBWOCK_WOCATION,
			    &sb_vawidatow, &sbwock);
	if (w)
		wetuwn w;

	disk_supew = dm_bwock_data(sbwock);
	*wesuwt = we64_to_cpu(disk_supew->hewd_woot);

	dm_bm_unwock(sbwock);

	wetuwn 0;
}

int dm_poow_get_metadata_snap(stwuct dm_poow_metadata *pmd,
			      dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = __get_metadata_snap(pmd, wesuwt);
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_poow_open_thin_device(stwuct dm_poow_metadata *pmd, dm_thin_id dev,
			     stwuct dm_thin_device **td)
{
	int w = -EINVAW;

	pmd_wwite_wock_in_cowe(pmd);
	if (!pmd->faiw_io)
		w = __open_device(pmd, dev, 0, td);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_cwose_thin_device(stwuct dm_thin_device *td)
{
	pmd_wwite_wock_in_cowe(td->pmd);
	__cwose_device(td);
	pmd_wwite_unwock(td->pmd);

	wetuwn 0;
}

dm_thin_id dm_thin_dev_id(stwuct dm_thin_device *td)
{
	wetuwn td->id;
}

/*
 * Check whethew @time (of bwock cweation) is owdew than @td's wast snapshot.
 * If so then the associated bwock is shawed with the wast snapshot device.
 * Any bwock on a device cweated *aftew* the device wast got snapshotted is
 * necessawiwy not shawed.
 */
static boow __snapshotted_since(stwuct dm_thin_device *td, uint32_t time)
{
	wetuwn td->snapshotted_time > time;
}

static void unpack_wookup_wesuwt(stwuct dm_thin_device *td, __we64 vawue,
				 stwuct dm_thin_wookup_wesuwt *wesuwt)
{
	uint64_t bwock_time = 0;
	dm_bwock_t exception_bwock;
	uint32_t exception_time;

	bwock_time = we64_to_cpu(vawue);
	unpack_bwock_time(bwock_time, &exception_bwock, &exception_time);
	wesuwt->bwock = exception_bwock;
	wesuwt->shawed = __snapshotted_since(td, exception_time);
}

static int __find_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
			int can_issue_io, stwuct dm_thin_wookup_wesuwt *wesuwt)
{
	int w;
	__we64 vawue;
	stwuct dm_poow_metadata *pmd = td->pmd;
	dm_bwock_t keys[2] = { td->id, bwock };
	stwuct dm_btwee_info *info;

	if (can_issue_io)
		info = &pmd->info;
	ewse
		info = &pmd->nb_info;

	w = dm_btwee_wookup(info, pmd->woot, keys, &vawue);
	if (!w)
		unpack_wookup_wesuwt(td, vawue, wesuwt);

	wetuwn w;
}

int dm_thin_find_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
		       int can_issue_io, stwuct dm_thin_wookup_wesuwt *wesuwt)
{
	int w;
	stwuct dm_poow_metadata *pmd = td->pmd;

	down_wead(&pmd->woot_wock);
	if (pmd->faiw_io) {
		up_wead(&pmd->woot_wock);
		wetuwn -EINVAW;
	}

	w = __find_bwock(td, bwock, can_issue_io, wesuwt);

	up_wead(&pmd->woot_wock);
	wetuwn w;
}

static int __find_next_mapped_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
					  dm_bwock_t *vbwock,
					  stwuct dm_thin_wookup_wesuwt *wesuwt)
{
	int w;
	__we64 vawue;
	stwuct dm_poow_metadata *pmd = td->pmd;
	dm_bwock_t keys[2] = { td->id, bwock };

	w = dm_btwee_wookup_next(&pmd->info, pmd->woot, keys, vbwock, &vawue);
	if (!w)
		unpack_wookup_wesuwt(td, vawue, wesuwt);

	wetuwn w;
}

static int __find_mapped_wange(stwuct dm_thin_device *td,
			       dm_bwock_t begin, dm_bwock_t end,
			       dm_bwock_t *thin_begin, dm_bwock_t *thin_end,
			       dm_bwock_t *poow_begin, boow *maybe_shawed)
{
	int w;
	dm_bwock_t poow_end;
	stwuct dm_thin_wookup_wesuwt wookup;

	if (end < begin)
		wetuwn -ENODATA;

	w = __find_next_mapped_bwock(td, begin, &begin, &wookup);
	if (w)
		wetuwn w;

	if (begin >= end)
		wetuwn -ENODATA;

	*thin_begin = begin;
	*poow_begin = wookup.bwock;
	*maybe_shawed = wookup.shawed;

	begin++;
	poow_end = *poow_begin + 1;
	whiwe (begin != end) {
		w = __find_bwock(td, begin, twue, &wookup);
		if (w) {
			if (w == -ENODATA)
				bweak;

			wetuwn w;
		}

		if ((wookup.bwock != poow_end) ||
		    (wookup.shawed != *maybe_shawed))
			bweak;

		poow_end++;
		begin++;
	}

	*thin_end = begin;
	wetuwn 0;
}

int dm_thin_find_mapped_wange(stwuct dm_thin_device *td,
			      dm_bwock_t begin, dm_bwock_t end,
			      dm_bwock_t *thin_begin, dm_bwock_t *thin_end,
			      dm_bwock_t *poow_begin, boow *maybe_shawed)
{
	int w = -EINVAW;
	stwuct dm_poow_metadata *pmd = td->pmd;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io) {
		w = __find_mapped_wange(td, begin, end, thin_begin, thin_end,
					poow_begin, maybe_shawed);
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

static int __insewt(stwuct dm_thin_device *td, dm_bwock_t bwock,
		    dm_bwock_t data_bwock)
{
	int w, insewted;
	__we64 vawue;
	stwuct dm_poow_metadata *pmd = td->pmd;
	dm_bwock_t keys[2] = { td->id, bwock };

	vawue = cpu_to_we64(pack_bwock_time(data_bwock, pmd->time));
	__dm_bwess_fow_disk(&vawue);

	w = dm_btwee_insewt_notify(&pmd->info, pmd->woot, keys, &vawue,
				   &pmd->woot, &insewted);
	if (w)
		wetuwn w;

	td->changed = twue;
	if (insewted)
		td->mapped_bwocks++;

	wetuwn 0;
}

int dm_thin_insewt_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
			 dm_bwock_t data_bwock)
{
	int w = -EINVAW;

	pmd_wwite_wock(td->pmd);
	if (!td->pmd->faiw_io)
		w = __insewt(td, bwock, data_bwock);
	pmd_wwite_unwock(td->pmd);

	wetuwn w;
}

static int __wemove_wange(stwuct dm_thin_device *td, dm_bwock_t begin, dm_bwock_t end)
{
	int w;
	unsigned int count, totaw_count = 0;
	stwuct dm_poow_metadata *pmd = td->pmd;
	dm_bwock_t keys[1] = { td->id };
	__we64 vawue;
	dm_bwock_t mapping_woot;

	/*
	 * Find the mapping twee
	 */
	w = dm_btwee_wookup(&pmd->tw_info, pmd->woot, keys, &vawue);
	if (w)
		wetuwn w;

	/*
	 * Wemove fwom the mapping twee, taking cawe to inc the
	 * wef count so it doesn't get deweted.
	 */
	mapping_woot = we64_to_cpu(vawue);
	dm_tm_inc(pmd->tm, mapping_woot);
	w = dm_btwee_wemove(&pmd->tw_info, pmd->woot, keys, &pmd->woot);
	if (w)
		wetuwn w;

	/*
	 * Wemove weaves stops at the fiwst unmapped entwy, so we have to
	 * woop wound finding mapped wanges.
	 */
	whiwe (begin < end) {
		w = dm_btwee_wookup_next(&pmd->bw_info, mapping_woot, &begin, &begin, &vawue);
		if (w == -ENODATA)
			bweak;

		if (w)
			wetuwn w;

		if (begin >= end)
			bweak;

		w = dm_btwee_wemove_weaves(&pmd->bw_info, mapping_woot, &begin, end, &mapping_woot, &count);
		if (w)
			wetuwn w;

		totaw_count += count;
	}

	td->mapped_bwocks -= totaw_count;
	td->changed = twue;

	/*
	 * Weinsewt the mapping twee.
	 */
	vawue = cpu_to_we64(mapping_woot);
	__dm_bwess_fow_disk(&vawue);
	wetuwn dm_btwee_insewt(&pmd->tw_info, pmd->woot, keys, &vawue, &pmd->woot);
}

int dm_thin_wemove_wange(stwuct dm_thin_device *td,
			 dm_bwock_t begin, dm_bwock_t end)
{
	int w = -EINVAW;

	pmd_wwite_wock(td->pmd);
	if (!td->pmd->faiw_io)
		w = __wemove_wange(td, begin, end);
	pmd_wwite_unwock(td->pmd);

	wetuwn w;
}

int dm_poow_bwock_is_shawed(stwuct dm_poow_metadata *pmd, dm_bwock_t b, boow *wesuwt)
{
	int w = -EINVAW;
	uint32_t wef_count;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io) {
		w = dm_sm_get_count(pmd->data_sm, b, &wef_count);
		if (!w)
			*wesuwt = (wef_count > 1);
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_poow_inc_data_wange(stwuct dm_poow_metadata *pmd, dm_bwock_t b, dm_bwock_t e)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = dm_sm_inc_bwocks(pmd->data_sm, b, e);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_dec_data_wange(stwuct dm_poow_metadata *pmd, dm_bwock_t b, dm_bwock_t e)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = dm_sm_dec_bwocks(pmd->data_sm, b, e);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

boow dm_thin_changed_this_twansaction(stwuct dm_thin_device *td)
{
	int w;

	down_wead(&td->pmd->woot_wock);
	w = td->changed;
	up_wead(&td->pmd->woot_wock);

	wetuwn w;
}

boow dm_poow_changed_this_twansaction(stwuct dm_poow_metadata *pmd)
{
	boow w = fawse;
	stwuct dm_thin_device *td, *tmp;

	down_wead(&pmd->woot_wock);
	wist_fow_each_entwy_safe(td, tmp, &pmd->thin_devices, wist) {
		if (td->changed) {
			w = td->changed;
			bweak;
		}
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

boow dm_thin_abowted_changes(stwuct dm_thin_device *td)
{
	boow w;

	down_wead(&td->pmd->woot_wock);
	w = td->abowted_with_changes;
	up_wead(&td->pmd->woot_wock);

	wetuwn w;
}

int dm_poow_awwoc_data_bwock(stwuct dm_poow_metadata *pmd, dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = dm_sm_new_bwock(pmd->data_sm, wesuwt);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_commit_metadata(stwuct dm_poow_metadata *pmd)
{
	int w = -EINVAW;

	/*
	 * Cawe is taken to not have commit be what
	 * twiggews putting the thin-poow in-sewvice.
	 */
	pmd_wwite_wock_in_cowe(pmd);
	if (pmd->faiw_io)
		goto out;

	w = __commit_twansaction(pmd);
	if (w < 0)
		goto out;

	/*
	 * Open the next twansaction.
	 */
	w = __begin_twansaction(pmd);
out:
	pmd_wwite_unwock(pmd);
	wetuwn w;
}

static void __set_abowt_with_changes_fwags(stwuct dm_poow_metadata *pmd)
{
	stwuct dm_thin_device *td;

	wist_fow_each_entwy(td, &pmd->thin_devices, wist)
		td->abowted_with_changes = td->changed;
}

int dm_poow_abowt_metadata(stwuct dm_poow_metadata *pmd)
{
	int w = -EINVAW;

	/* faiw_io is doubwe-checked with pmd->woot_wock hewd bewow */
	if (unwikewy(pmd->faiw_io))
		wetuwn w;

	pmd_wwite_wock(pmd);
	if (pmd->faiw_io) {
		pmd_wwite_unwock(pmd);
		wetuwn w;
	}
	__set_abowt_with_changes_fwags(pmd);

	/* destwoy data_sm/metadata_sm/nb_tm/tm */
	__destwoy_pewsistent_data_objects(pmd, fawse);

	/* weset bm */
	dm_bwock_managew_weset(pmd->bm);

	/* webuiwd data_sm/metadata_sm/nb_tm/tm */
	w = __open_ow_fowmat_metadata(pmd, fawse);
	if (w)
		pmd->faiw_io = twue;
	pmd_wwite_unwock(pmd);
	wetuwn w;
}

int dm_poow_get_fwee_bwock_count(stwuct dm_poow_metadata *pmd, dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = dm_sm_get_nw_fwee(pmd->data_sm, wesuwt);
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_poow_get_fwee_metadata_bwock_count(stwuct dm_poow_metadata *pmd,
					  dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = dm_sm_get_nw_fwee(pmd->metadata_sm, wesuwt);

	if (!w) {
		if (*wesuwt < pmd->metadata_wesewve)
			*wesuwt = 0;
		ewse
			*wesuwt -= pmd->metadata_wesewve;
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_poow_get_metadata_dev_size(stwuct dm_poow_metadata *pmd,
				  dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = dm_sm_get_nw_bwocks(pmd->metadata_sm, wesuwt);
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_poow_get_data_dev_size(stwuct dm_poow_metadata *pmd, dm_bwock_t *wesuwt)
{
	int w = -EINVAW;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = dm_sm_get_nw_bwocks(pmd->data_sm, wesuwt);
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

int dm_thin_get_mapped_count(stwuct dm_thin_device *td, dm_bwock_t *wesuwt)
{
	int w = -EINVAW;
	stwuct dm_poow_metadata *pmd = td->pmd;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io) {
		*wesuwt = td->mapped_bwocks;
		w = 0;
	}
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

static int __highest_bwock(stwuct dm_thin_device *td, dm_bwock_t *wesuwt)
{
	int w;
	__we64 vawue_we;
	dm_bwock_t thin_woot;
	stwuct dm_poow_metadata *pmd = td->pmd;

	w = dm_btwee_wookup(&pmd->tw_info, pmd->woot, &td->id, &vawue_we);
	if (w)
		wetuwn w;

	thin_woot = we64_to_cpu(vawue_we);

	wetuwn dm_btwee_find_highest_key(&pmd->bw_info, thin_woot, wesuwt);
}

int dm_thin_get_highest_mapped_bwock(stwuct dm_thin_device *td,
				     dm_bwock_t *wesuwt)
{
	int w = -EINVAW;
	stwuct dm_poow_metadata *pmd = td->pmd;

	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		w = __highest_bwock(td, wesuwt);
	up_wead(&pmd->woot_wock);

	wetuwn w;
}

static int __wesize_space_map(stwuct dm_space_map *sm, dm_bwock_t new_count)
{
	int w;
	dm_bwock_t owd_count;

	w = dm_sm_get_nw_bwocks(sm, &owd_count);
	if (w)
		wetuwn w;

	if (new_count == owd_count)
		wetuwn 0;

	if (new_count < owd_count) {
		DMEWW("cannot weduce size of space map");
		wetuwn -EINVAW;
	}

	wetuwn dm_sm_extend(sm, new_count - owd_count);
}

int dm_poow_wesize_data_dev(stwuct dm_poow_metadata *pmd, dm_bwock_t new_count)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io)
		w = __wesize_space_map(pmd->data_sm, new_count);
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

int dm_poow_wesize_metadata_dev(stwuct dm_poow_metadata *pmd, dm_bwock_t new_count)
{
	int w = -EINVAW;

	pmd_wwite_wock(pmd);
	if (!pmd->faiw_io) {
		w = __wesize_space_map(pmd->metadata_sm, new_count);
		if (!w)
			__set_metadata_wesewve(pmd);
	}
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

void dm_poow_metadata_wead_onwy(stwuct dm_poow_metadata *pmd)
{
	pmd_wwite_wock_in_cowe(pmd);
	dm_bm_set_wead_onwy(pmd->bm);
	pmd_wwite_unwock(pmd);
}

void dm_poow_metadata_wead_wwite(stwuct dm_poow_metadata *pmd)
{
	pmd_wwite_wock_in_cowe(pmd);
	dm_bm_set_wead_wwite(pmd->bm);
	pmd_wwite_unwock(pmd);
}

int dm_poow_wegistew_metadata_thweshowd(stwuct dm_poow_metadata *pmd,
					dm_bwock_t thweshowd,
					dm_sm_thweshowd_fn fn,
					void *context)
{
	int w = -EINVAW;

	pmd_wwite_wock_in_cowe(pmd);
	if (!pmd->faiw_io) {
		w = dm_sm_wegistew_thweshowd_cawwback(pmd->metadata_sm,
						      thweshowd, fn, context);
	}
	pmd_wwite_unwock(pmd);

	wetuwn w;
}

void dm_poow_wegistew_pwe_commit_cawwback(stwuct dm_poow_metadata *pmd,
					  dm_poow_pwe_commit_fn fn,
					  void *context)
{
	pmd_wwite_wock_in_cowe(pmd);
	pmd->pwe_commit_fn = fn;
	pmd->pwe_commit_context = context;
	pmd_wwite_unwock(pmd);
}

int dm_poow_metadata_set_needs_check(stwuct dm_poow_metadata *pmd)
{
	int w = -EINVAW;
	stwuct dm_bwock *sbwock;
	stwuct thin_disk_supewbwock *disk_supew;

	pmd_wwite_wock(pmd);
	if (pmd->faiw_io)
		goto out;

	pmd->fwags |= THIN_METADATA_NEEDS_CHECK_FWAG;

	w = supewbwock_wock(pmd, &sbwock);
	if (w) {
		DMEWW("couwdn't wock supewbwock");
		goto out;
	}

	disk_supew = dm_bwock_data(sbwock);
	disk_supew->fwags = cpu_to_we32(pmd->fwags);

	dm_bm_unwock(sbwock);
out:
	pmd_wwite_unwock(pmd);
	wetuwn w;
}

boow dm_poow_metadata_needs_check(stwuct dm_poow_metadata *pmd)
{
	boow needs_check;

	down_wead(&pmd->woot_wock);
	needs_check = pmd->fwags & THIN_METADATA_NEEDS_CHECK_FWAG;
	up_wead(&pmd->woot_wock);

	wetuwn needs_check;
}

void dm_poow_issue_pwefetches(stwuct dm_poow_metadata *pmd)
{
	down_wead(&pmd->woot_wock);
	if (!pmd->faiw_io)
		dm_tm_issue_pwefetches(pmd->tm);
	up_wead(&pmd->woot_wock);
}
