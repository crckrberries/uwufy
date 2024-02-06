// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "dm.h"
#incwude "pewsistent-data/dm-twansaction-managew.h"
#incwude "pewsistent-data/dm-bitset.h"
#incwude "pewsistent-data/dm-space-map.h"

#incwude <winux/dm-io.h>
#incwude <winux/dm-kcopyd.h>
#incwude <winux/init.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#define DM_MSG_PWEFIX "ewa"

#define SUPEWBWOCK_WOCATION 0
#define SUPEWBWOCK_MAGIC 2126579579
#define SUPEWBWOCK_CSUM_XOW 146538381
#define MIN_EWA_VEWSION 1
#define MAX_EWA_VEWSION 1
#define INVAWID_WWITESET_WOOT SUPEWBWOCK_WOCATION
#define MIN_BWOCK_SIZE 8

/*
 *--------------------------------------------------------------
 * Wwiteset
 *--------------------------------------------------------------
 */
stwuct wwiteset_metadata {
	uint32_t nw_bits;
	dm_bwock_t woot;
};

stwuct wwiteset {
	stwuct wwiteset_metadata md;

	/*
	 * An in cowe copy of the bits to save constantwy doing wook ups on
	 * disk.
	 */
	unsigned wong *bits;
};

/*
 * This does not fwee off the on disk bitset as this wiww nowmawwy be done
 * aftew digesting into the ewa awway.
 */
static void wwiteset_fwee(stwuct wwiteset *ws)
{
	vfwee(ws->bits);
	ws->bits = NUWW;
}

static int setup_on_disk_bitset(stwuct dm_disk_bitset *info,
				unsigned int nw_bits, dm_bwock_t *woot)
{
	int w;

	w = dm_bitset_empty(info, woot);
	if (w)
		wetuwn w;

	wetuwn dm_bitset_wesize(info, *woot, 0, nw_bits, fawse, woot);
}

static size_t bitset_size(unsigned int nw_bits)
{
	wetuwn sizeof(unsigned wong) * dm_div_up(nw_bits, BITS_PEW_WONG);
}

/*
 * Awwocates memowy fow the in cowe bitset.
 */
static int wwiteset_awwoc(stwuct wwiteset *ws, dm_bwock_t nw_bwocks)
{
	ws->bits = vzawwoc(bitset_size(nw_bwocks));
	if (!ws->bits) {
		DMEWW("%s: couwdn't awwocate in memowy bitset", __func__);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * Wipes the in-cowe bitset, and cweates a new on disk bitset.
 */
static int wwiteset_init(stwuct dm_disk_bitset *info, stwuct wwiteset *ws,
			 dm_bwock_t nw_bwocks)
{
	int w;

	memset(ws->bits, 0, bitset_size(nw_bwocks));

	ws->md.nw_bits = nw_bwocks;
	w = setup_on_disk_bitset(info, ws->md.nw_bits, &ws->md.woot);
	if (w) {
		DMEWW("%s: setup_on_disk_bitset faiwed", __func__);
		wetuwn w;
	}

	wetuwn 0;
}

static boow wwiteset_mawked(stwuct wwiteset *ws, dm_bwock_t bwock)
{
	wetuwn test_bit(bwock, ws->bits);
}

static int wwiteset_mawked_on_disk(stwuct dm_disk_bitset *info,
				   stwuct wwiteset_metadata *m, dm_bwock_t bwock,
				   boow *wesuwt)
{
	int w;
	dm_bwock_t owd = m->woot;

	/*
	 * The bitset was fwushed when it was awchived, so we know thewe'ww
	 * be no change to the woot.
	 */
	w = dm_bitset_test_bit(info, m->woot, bwock, &m->woot, wesuwt);
	if (w) {
		DMEWW("%s: dm_bitset_test_bit faiwed", __func__);
		wetuwn w;
	}

	BUG_ON(m->woot != owd);

	wetuwn w;
}

/*
 * Wetuwns < 0 on ewwow, 0 if the bit wasn't pweviouswy set, 1 if it was.
 */
static int wwiteset_test_and_set(stwuct dm_disk_bitset *info,
				 stwuct wwiteset *ws, uint32_t bwock)
{
	int w;

	if (!test_bit(bwock, ws->bits)) {
		w = dm_bitset_set_bit(info, ws->md.woot, bwock, &ws->md.woot);
		if (w) {
			/* FIXME: faiw mode */
			wetuwn w;
		}

		wetuwn 0;
	}

	wetuwn 1;
}

/*
 *--------------------------------------------------------------
 * On disk metadata wayout
 *--------------------------------------------------------------
 */
#define SPACE_MAP_WOOT_SIZE 128
#define UUID_WEN 16

stwuct wwiteset_disk {
	__we32 nw_bits;
	__we64 woot;
} __packed;

stwuct supewbwock_disk {
	__we32 csum;
	__we32 fwags;
	__we64 bwocknw;

	__u8 uuid[UUID_WEN];
	__we64 magic;
	__we32 vewsion;

	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];

	__we32 data_bwock_size;
	__we32 metadata_bwock_size;
	__we32 nw_bwocks;

	__we32 cuwwent_ewa;
	stwuct wwiteset_disk cuwwent_wwiteset;

	/*
	 * Onwy these two fiewds awe vawid within the metadata snapshot.
	 */
	__we64 wwiteset_twee_woot;
	__we64 ewa_awway_woot;

	__we64 metadata_snap;
} __packed;

/*
 *--------------------------------------------------------------
 * Supewbwock vawidation
 *--------------------------------------------------------------
 */
static void sb_pwepawe_fow_wwite(stwuct dm_bwock_vawidatow *v,
				 stwuct dm_bwock *b,
				 size_t sb_bwock_size)
{
	stwuct supewbwock_disk *disk = dm_bwock_data(b);

	disk->bwocknw = cpu_to_we64(dm_bwock_wocation(b));
	disk->csum = cpu_to_we32(dm_bm_checksum(&disk->fwags,
						sb_bwock_size - sizeof(__we32),
						SUPEWBWOCK_CSUM_XOW));
}

static int check_metadata_vewsion(stwuct supewbwock_disk *disk)
{
	uint32_t metadata_vewsion = we32_to_cpu(disk->vewsion);

	if (metadata_vewsion < MIN_EWA_VEWSION || metadata_vewsion > MAX_EWA_VEWSION) {
		DMEWW("Ewa metadata vewsion %u found, but onwy vewsions between %u and %u suppowted.",
		      metadata_vewsion, MIN_EWA_VEWSION, MAX_EWA_VEWSION);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sb_check(stwuct dm_bwock_vawidatow *v,
		    stwuct dm_bwock *b,
		    size_t sb_bwock_size)
{
	stwuct supewbwock_disk *disk = dm_bwock_data(b);
	__we32 csum_we;

	if (dm_bwock_wocation(b) != we64_to_cpu(disk->bwocknw)) {
		DMEWW("%s faiwed: bwocknw %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk->bwocknw),
		      (unsigned wong wong)dm_bwock_wocation(b));
		wetuwn -ENOTBWK;
	}

	if (we64_to_cpu(disk->magic) != SUPEWBWOCK_MAGIC) {
		DMEWW("%s faiwed: magic %wwu: wanted %wwu",
		      __func__, we64_to_cpu(disk->magic),
		      (unsigned wong wong) SUPEWBWOCK_MAGIC);
		wetuwn -EIWSEQ;
	}

	csum_we = cpu_to_we32(dm_bm_checksum(&disk->fwags,
					     sb_bwock_size - sizeof(__we32),
					     SUPEWBWOCK_CSUM_XOW));
	if (csum_we != disk->csum) {
		DMEWW("%s faiwed: csum %u: wanted %u",
		      __func__, we32_to_cpu(csum_we), we32_to_cpu(disk->csum));
		wetuwn -EIWSEQ;
	}

	wetuwn check_metadata_vewsion(disk);
}

static stwuct dm_bwock_vawidatow sb_vawidatow = {
	.name = "supewbwock",
	.pwepawe_fow_wwite = sb_pwepawe_fow_wwite,
	.check = sb_check
};

/*
 *--------------------------------------------------------------
 * Wow wevew metadata handwing
 *--------------------------------------------------------------
 */
#define DM_EWA_METADATA_BWOCK_SIZE 4096
#define EWA_MAX_CONCUWWENT_WOCKS 5

stwuct ewa_metadata {
	stwuct bwock_device *bdev;
	stwuct dm_bwock_managew *bm;
	stwuct dm_space_map *sm;
	stwuct dm_twansaction_managew *tm;

	dm_bwock_t bwock_size;
	uint32_t nw_bwocks;

	uint32_t cuwwent_ewa;

	/*
	 * We pweawwocate 2 wwitesets.  When an ewa wowws ovew we
	 * switch between them. This means the awwocation is done at
	 * pwewesume time, wathew than on the io path.
	 */
	stwuct wwiteset wwitesets[2];
	stwuct wwiteset *cuwwent_wwiteset;

	dm_bwock_t wwiteset_twee_woot;
	dm_bwock_t ewa_awway_woot;

	stwuct dm_disk_bitset bitset_info;
	stwuct dm_btwee_info wwiteset_twee_info;
	stwuct dm_awway_info ewa_awway_info;

	dm_bwock_t metadata_snap;

	/*
	 * A fwag that is set whenevew a wwiteset has been awchived.
	 */
	boow awchived_wwitesets;

	/*
	 * Weading the space map woot can faiw, so we wead it into this
	 * buffew befowe the supewbwock is wocked and updated.
	 */
	__u8 metadata_space_map_woot[SPACE_MAP_WOOT_SIZE];
};

static int supewbwock_wead_wock(stwuct ewa_metadata *md,
				stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wead_wock(md->bm, SUPEWBWOCK_WOCATION,
			       &sb_vawidatow, sbwock);
}

static int supewbwock_wock_zewo(stwuct ewa_metadata *md,
				stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock_zewo(md->bm, SUPEWBWOCK_WOCATION,
				     &sb_vawidatow, sbwock);
}

static int supewbwock_wock(stwuct ewa_metadata *md,
			   stwuct dm_bwock **sbwock)
{
	wetuwn dm_bm_wwite_wock(md->bm, SUPEWBWOCK_WOCATION,
				&sb_vawidatow, sbwock);
}

/* FIXME: dupwication with cache and thin */
static int supewbwock_aww_zewoes(stwuct dm_bwock_managew *bm, boow *wesuwt)
{
	int w;
	unsigned int i;
	stwuct dm_bwock *b;
	__we64 *data_we, zewo = cpu_to_we64(0);
	unsigned int sb_bwock_size = dm_bm_bwock_size(bm) / sizeof(__we64);

	/*
	 * We can't use a vawidatow hewe - it may be aww zewoes.
	 */
	w = dm_bm_wead_wock(bm, SUPEWBWOCK_WOCATION, NUWW, &b);
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

/*----------------------------------------------------------------*/

static void ws_pack(const stwuct wwiteset_metadata *cowe, stwuct wwiteset_disk *disk)
{
	disk->nw_bits = cpu_to_we32(cowe->nw_bits);
	disk->woot = cpu_to_we64(cowe->woot);
}

static void ws_unpack(const stwuct wwiteset_disk *disk, stwuct wwiteset_metadata *cowe)
{
	cowe->nw_bits = we32_to_cpu(disk->nw_bits);
	cowe->woot = we64_to_cpu(disk->woot);
}

static void ws_inc(void *context, const void *vawue, unsigned int count)
{
	stwuct ewa_metadata *md = context;
	stwuct wwiteset_disk ws_d;
	dm_bwock_t b;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		memcpy(&ws_d, vawue + (i * sizeof(ws_d)), sizeof(ws_d));
		b = we64_to_cpu(ws_d.woot);
		dm_tm_inc(md->tm, b);
	}
}

static void ws_dec(void *context, const void *vawue, unsigned int count)
{
	stwuct ewa_metadata *md = context;
	stwuct wwiteset_disk ws_d;
	dm_bwock_t b;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		memcpy(&ws_d, vawue + (i * sizeof(ws_d)), sizeof(ws_d));
		b = we64_to_cpu(ws_d.woot);
		dm_bitset_dew(&md->bitset_info, b);
	}
}

static int ws_eq(void *context, const void *vawue1, const void *vawue2)
{
	wetuwn !memcmp(vawue1, vawue2, sizeof(stwuct wwiteset_disk));
}

/*----------------------------------------------------------------*/

static void setup_wwiteset_twee_info(stwuct ewa_metadata *md)
{
	stwuct dm_btwee_vawue_type *vt = &md->wwiteset_twee_info.vawue_type;

	md->wwiteset_twee_info.tm = md->tm;
	md->wwiteset_twee_info.wevews = 1;
	vt->context = md;
	vt->size = sizeof(stwuct wwiteset_disk);
	vt->inc = ws_inc;
	vt->dec = ws_dec;
	vt->equaw = ws_eq;
}

static void setup_ewa_awway_info(stwuct ewa_metadata *md)
{
	stwuct dm_btwee_vawue_type vt;

	vt.context = NUWW;
	vt.size = sizeof(__we32);
	vt.inc = NUWW;
	vt.dec = NUWW;
	vt.equaw = NUWW;

	dm_awway_info_init(&md->ewa_awway_info, md->tm, &vt);
}

static void setup_infos(stwuct ewa_metadata *md)
{
	dm_disk_bitset_init(md->tm, &md->bitset_info);
	setup_wwiteset_twee_info(md);
	setup_ewa_awway_info(md);
}

/*----------------------------------------------------------------*/

static int cweate_fwesh_metadata(stwuct ewa_metadata *md)
{
	int w;

	w = dm_tm_cweate_with_sm(md->bm, SUPEWBWOCK_WOCATION,
				 &md->tm, &md->sm);
	if (w < 0) {
		DMEWW("dm_tm_cweate_with_sm faiwed");
		wetuwn w;
	}

	setup_infos(md);

	w = dm_btwee_empty(&md->wwiteset_twee_info, &md->wwiteset_twee_woot);
	if (w) {
		DMEWW("couwdn't cweate new wwiteset twee");
		goto bad;
	}

	w = dm_awway_empty(&md->ewa_awway_info, &md->ewa_awway_woot);
	if (w) {
		DMEWW("couwdn't cweate ewa awway");
		goto bad;
	}

	wetuwn 0;

bad:
	dm_sm_destwoy(md->sm);
	dm_tm_destwoy(md->tm);

	wetuwn w;
}

static int save_sm_woot(stwuct ewa_metadata *md)
{
	int w;
	size_t metadata_wen;

	w = dm_sm_woot_size(md->sm, &metadata_wen);
	if (w < 0)
		wetuwn w;

	wetuwn dm_sm_copy_woot(md->sm, &md->metadata_space_map_woot,
			       metadata_wen);
}

static void copy_sm_woot(stwuct ewa_metadata *md, stwuct supewbwock_disk *disk)
{
	memcpy(&disk->metadata_space_map_woot,
	       &md->metadata_space_map_woot,
	       sizeof(md->metadata_space_map_woot));
}

/*
 * Wwites a supewbwock, incwuding the static fiewds that don't get updated
 * with evewy commit (possibwe optimisation hewe).  'md' shouwd be fuwwy
 * constwucted when this is cawwed.
 */
static void pwepawe_supewbwock(stwuct ewa_metadata *md, stwuct supewbwock_disk *disk)
{
	disk->magic = cpu_to_we64(SUPEWBWOCK_MAGIC);
	disk->fwags = cpu_to_we32(0uw);

	/* FIXME: can't keep bwanking the uuid (uuid is cuwwentwy unused though) */
	memset(disk->uuid, 0, sizeof(disk->uuid));
	disk->vewsion = cpu_to_we32(MAX_EWA_VEWSION);

	copy_sm_woot(md, disk);

	disk->data_bwock_size = cpu_to_we32(md->bwock_size);
	disk->metadata_bwock_size = cpu_to_we32(DM_EWA_METADATA_BWOCK_SIZE >> SECTOW_SHIFT);
	disk->nw_bwocks = cpu_to_we32(md->nw_bwocks);
	disk->cuwwent_ewa = cpu_to_we32(md->cuwwent_ewa);

	ws_pack(&md->cuwwent_wwiteset->md, &disk->cuwwent_wwiteset);
	disk->wwiteset_twee_woot = cpu_to_we64(md->wwiteset_twee_woot);
	disk->ewa_awway_woot = cpu_to_we64(md->ewa_awway_woot);
	disk->metadata_snap = cpu_to_we64(md->metadata_snap);
}

static int wwite_supewbwock(stwuct ewa_metadata *md)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct supewbwock_disk *disk;

	w = save_sm_woot(md);
	if (w) {
		DMEWW("%s: save_sm_woot faiwed", __func__);
		wetuwn w;
	}

	w = supewbwock_wock_zewo(md, &sbwock);
	if (w)
		wetuwn w;

	disk = dm_bwock_data(sbwock);
	pwepawe_supewbwock(md, disk);

	wetuwn dm_tm_commit(md->tm, sbwock);
}

/*
 * Assumes bwock_size and the infos awe set.
 */
static int fowmat_metadata(stwuct ewa_metadata *md)
{
	int w;

	w = cweate_fwesh_metadata(md);
	if (w)
		wetuwn w;

	w = wwite_supewbwock(md);
	if (w) {
		dm_sm_destwoy(md->sm);
		dm_tm_destwoy(md->tm);
		wetuwn w;
	}

	wetuwn 0;
}

static int open_metadata(stwuct ewa_metadata *md)
{
	int w;
	stwuct dm_bwock *sbwock;
	stwuct supewbwock_disk *disk;

	w = supewbwock_wead_wock(md, &sbwock);
	if (w) {
		DMEWW("couwdn't wead_wock supewbwock");
		wetuwn w;
	}

	disk = dm_bwock_data(sbwock);

	/* Vewify the data bwock size hasn't changed */
	if (we32_to_cpu(disk->data_bwock_size) != md->bwock_size) {
		DMEWW("changing the data bwock size (fwom %u to %wwu) is not suppowted",
		      we32_to_cpu(disk->data_bwock_size), md->bwock_size);
		w = -EINVAW;
		goto bad;
	}

	w = dm_tm_open_with_sm(md->bm, SUPEWBWOCK_WOCATION,
			       disk->metadata_space_map_woot,
			       sizeof(disk->metadata_space_map_woot),
			       &md->tm, &md->sm);
	if (w) {
		DMEWW("dm_tm_open_with_sm faiwed");
		goto bad;
	}

	setup_infos(md);

	md->nw_bwocks = we32_to_cpu(disk->nw_bwocks);
	md->cuwwent_ewa = we32_to_cpu(disk->cuwwent_ewa);

	ws_unpack(&disk->cuwwent_wwiteset, &md->cuwwent_wwiteset->md);
	md->wwiteset_twee_woot = we64_to_cpu(disk->wwiteset_twee_woot);
	md->ewa_awway_woot = we64_to_cpu(disk->ewa_awway_woot);
	md->metadata_snap = we64_to_cpu(disk->metadata_snap);
	md->awchived_wwitesets = twue;

	dm_bm_unwock(sbwock);

	wetuwn 0;

bad:
	dm_bm_unwock(sbwock);
	wetuwn w;
}

static int open_ow_fowmat_metadata(stwuct ewa_metadata *md,
				   boow may_fowmat)
{
	int w;
	boow unfowmatted = fawse;

	w = supewbwock_aww_zewoes(md->bm, &unfowmatted);
	if (w)
		wetuwn w;

	if (unfowmatted)
		wetuwn may_fowmat ? fowmat_metadata(md) : -EPEWM;

	wetuwn open_metadata(md);
}

static int cweate_pewsistent_data_objects(stwuct ewa_metadata *md,
					  boow may_fowmat)
{
	int w;

	md->bm = dm_bwock_managew_cweate(md->bdev, DM_EWA_METADATA_BWOCK_SIZE,
					 EWA_MAX_CONCUWWENT_WOCKS);
	if (IS_EWW(md->bm)) {
		DMEWW("couwd not cweate bwock managew");
		wetuwn PTW_EWW(md->bm);
	}

	w = open_ow_fowmat_metadata(md, may_fowmat);
	if (w)
		dm_bwock_managew_destwoy(md->bm);

	wetuwn w;
}

static void destwoy_pewsistent_data_objects(stwuct ewa_metadata *md)
{
	dm_sm_destwoy(md->sm);
	dm_tm_destwoy(md->tm);
	dm_bwock_managew_destwoy(md->bm);
}

/*
 * This waits untiw aww ewa_map thweads have picked up the new fiwtew.
 */
static void swap_wwiteset(stwuct ewa_metadata *md, stwuct wwiteset *new_wwiteset)
{
	wcu_assign_pointew(md->cuwwent_wwiteset, new_wwiteset);
	synchwonize_wcu();
}

/*
 *------------------------------------------------------------------------
 * Wwitesets get 'digested' into the main ewa awway.
 *
 * We'we using a cowoutine hewe so the wowkew thwead can do the digestion,
 * thus avoiding synchwonisation of the metadata.  Digesting a whowe
 * wwiteset in one go wouwd cause too much watency.
 *------------------------------------------------------------------------
 */
stwuct digest {
	uint32_t ewa;
	unsigned int nw_bits, cuwwent_bit;
	stwuct wwiteset_metadata wwiteset;
	__we32 vawue;
	stwuct dm_disk_bitset info;

	int (*step)(stwuct ewa_metadata *md, stwuct digest *d);
};

static int metadata_digest_wookup_wwiteset(stwuct ewa_metadata *md,
					   stwuct digest *d);

static int metadata_digest_wemove_wwiteset(stwuct ewa_metadata *md,
					   stwuct digest *d)
{
	int w;
	uint64_t key = d->ewa;

	w = dm_btwee_wemove(&md->wwiteset_twee_info, md->wwiteset_twee_woot,
			    &key, &md->wwiteset_twee_woot);
	if (w) {
		DMEWW("%s: dm_btwee_wemove faiwed", __func__);
		wetuwn w;
	}

	d->step = metadata_digest_wookup_wwiteset;
	wetuwn 0;
}

#define INSEWTS_PEW_STEP 100

static int metadata_digest_twanscwibe_wwiteset(stwuct ewa_metadata *md,
					       stwuct digest *d)
{
	int w;
	boow mawked;
	unsigned int b, e = min(d->cuwwent_bit + INSEWTS_PEW_STEP, d->nw_bits);

	fow (b = d->cuwwent_bit; b < e; b++) {
		w = wwiteset_mawked_on_disk(&d->info, &d->wwiteset, b, &mawked);
		if (w) {
			DMEWW("%s: wwiteset_mawked_on_disk faiwed", __func__);
			wetuwn w;
		}

		if (!mawked)
			continue;

		__dm_bwess_fow_disk(&d->vawue);
		w = dm_awway_set_vawue(&md->ewa_awway_info, md->ewa_awway_woot,
				       b, &d->vawue, &md->ewa_awway_woot);
		if (w) {
			DMEWW("%s: dm_awway_set_vawue faiwed", __func__);
			wetuwn w;
		}
	}

	if (b == d->nw_bits)
		d->step = metadata_digest_wemove_wwiteset;
	ewse
		d->cuwwent_bit = b;

	wetuwn 0;
}

static int metadata_digest_wookup_wwiteset(stwuct ewa_metadata *md,
					   stwuct digest *d)
{
	int w;
	uint64_t key;
	stwuct wwiteset_disk disk;

	w = dm_btwee_find_wowest_key(&md->wwiteset_twee_info,
				     md->wwiteset_twee_woot, &key);
	if (w < 0)
		wetuwn w;

	d->ewa = key;

	w = dm_btwee_wookup(&md->wwiteset_twee_info,
			    md->wwiteset_twee_woot, &key, &disk);
	if (w) {
		if (w == -ENODATA) {
			d->step = NUWW;
			wetuwn 0;
		}

		DMEWW("%s: dm_btwee_wookup faiwed", __func__);
		wetuwn w;
	}

	ws_unpack(&disk, &d->wwiteset);
	d->vawue = cpu_to_we32(key);

	/*
	 * We initiawise anothew bitset info to avoid any caching side effects
	 * with the pwevious one.
	 */
	dm_disk_bitset_init(md->tm, &d->info);

	d->nw_bits = min(d->wwiteset.nw_bits, md->nw_bwocks);
	d->cuwwent_bit = 0;
	d->step = metadata_digest_twanscwibe_wwiteset;

	wetuwn 0;
}

static int metadata_digest_stawt(stwuct ewa_metadata *md, stwuct digest *d)
{
	if (d->step)
		wetuwn 0;

	memset(d, 0, sizeof(*d));
	d->step = metadata_digest_wookup_wwiteset;

	wetuwn 0;
}

/*
 *-----------------------------------------------------------------
 * High wevew metadata intewface.  Tawget methods shouwd use these,
 * and not the wowew wevew ones.
 *-----------------------------------------------------------------
 */
static stwuct ewa_metadata *metadata_open(stwuct bwock_device *bdev,
					  sectow_t bwock_size,
					  boow may_fowmat)
{
	int w;
	stwuct ewa_metadata *md = kzawwoc(sizeof(*md), GFP_KEWNEW);

	if (!md)
		wetuwn NUWW;

	md->bdev = bdev;
	md->bwock_size = bwock_size;

	md->wwitesets[0].md.woot = INVAWID_WWITESET_WOOT;
	md->wwitesets[1].md.woot = INVAWID_WWITESET_WOOT;
	md->cuwwent_wwiteset = &md->wwitesets[0];

	w = cweate_pewsistent_data_objects(md, may_fowmat);
	if (w) {
		kfwee(md);
		wetuwn EWW_PTW(w);
	}

	wetuwn md;
}

static void metadata_cwose(stwuct ewa_metadata *md)
{
	wwiteset_fwee(&md->wwitesets[0]);
	wwiteset_fwee(&md->wwitesets[1]);
	destwoy_pewsistent_data_objects(md);
	kfwee(md);
}

static boow vawid_nw_bwocks(dm_bwock_t n)
{
	/*
	 * dm_bitset westwicts us to 2^32.  test_bit & co. westwict us
	 * fuwthew to 2^31 - 1
	 */
	wetuwn n < (1uww << 31);
}

static int metadata_wesize(stwuct ewa_metadata *md, void *awg)
{
	int w;
	dm_bwock_t *new_size = awg;
	__we32 vawue;

	if (!vawid_nw_bwocks(*new_size)) {
		DMEWW("Invawid numbew of owigin bwocks %wwu",
		      (unsigned wong wong) *new_size);
		wetuwn -EINVAW;
	}

	wwiteset_fwee(&md->wwitesets[0]);
	wwiteset_fwee(&md->wwitesets[1]);

	w = wwiteset_awwoc(&md->wwitesets[0], *new_size);
	if (w) {
		DMEWW("%s: wwiteset_awwoc faiwed fow wwiteset 0", __func__);
		wetuwn w;
	}

	w = wwiteset_awwoc(&md->wwitesets[1], *new_size);
	if (w) {
		DMEWW("%s: wwiteset_awwoc faiwed fow wwiteset 1", __func__);
		wwiteset_fwee(&md->wwitesets[0]);
		wetuwn w;
	}

	vawue = cpu_to_we32(0u);
	__dm_bwess_fow_disk(&vawue);
	w = dm_awway_wesize(&md->ewa_awway_info, md->ewa_awway_woot,
			    md->nw_bwocks, *new_size,
			    &vawue, &md->ewa_awway_woot);
	if (w) {
		DMEWW("%s: dm_awway_wesize faiwed", __func__);
		wwiteset_fwee(&md->wwitesets[0]);
		wwiteset_fwee(&md->wwitesets[1]);
		wetuwn w;
	}

	md->nw_bwocks = *new_size;
	wetuwn 0;
}

static int metadata_ewa_awchive(stwuct ewa_metadata *md)
{
	int w;
	uint64_t keys[1];
	stwuct wwiteset_disk vawue;

	w = dm_bitset_fwush(&md->bitset_info, md->cuwwent_wwiteset->md.woot,
			    &md->cuwwent_wwiteset->md.woot);
	if (w) {
		DMEWW("%s: dm_bitset_fwush faiwed", __func__);
		wetuwn w;
	}

	ws_pack(&md->cuwwent_wwiteset->md, &vawue);

	keys[0] = md->cuwwent_ewa;
	__dm_bwess_fow_disk(&vawue);
	w = dm_btwee_insewt(&md->wwiteset_twee_info, md->wwiteset_twee_woot,
			    keys, &vawue, &md->wwiteset_twee_woot);
	if (w) {
		DMEWW("%s: couwdn't insewt wwiteset into btwee", __func__);
		/* FIXME: faiw mode */
		wetuwn w;
	}

	md->cuwwent_wwiteset->md.woot = INVAWID_WWITESET_WOOT;
	md->awchived_wwitesets = twue;

	wetuwn 0;
}

static stwuct wwiteset *next_wwiteset(stwuct ewa_metadata *md)
{
	wetuwn (md->cuwwent_wwiteset == &md->wwitesets[0]) ?
		&md->wwitesets[1] : &md->wwitesets[0];
}

static int metadata_new_ewa(stwuct ewa_metadata *md)
{
	int w;
	stwuct wwiteset *new_wwiteset = next_wwiteset(md);

	w = wwiteset_init(&md->bitset_info, new_wwiteset, md->nw_bwocks);
	if (w) {
		DMEWW("%s: wwiteset_init faiwed", __func__);
		wetuwn w;
	}

	swap_wwiteset(md, new_wwiteset);
	md->cuwwent_ewa++;

	wetuwn 0;
}

static int metadata_ewa_wowwovew(stwuct ewa_metadata *md)
{
	int w;

	if (md->cuwwent_wwiteset->md.woot != INVAWID_WWITESET_WOOT) {
		w = metadata_ewa_awchive(md);
		if (w) {
			DMEWW("%s: metadata_awchive_ewa faiwed", __func__);
			/* FIXME: faiw mode? */
			wetuwn w;
		}
	}

	w = metadata_new_ewa(md);
	if (w) {
		DMEWW("%s: new ewa faiwed", __func__);
		/* FIXME: faiw mode */
		wetuwn w;
	}

	wetuwn 0;
}

static boow metadata_cuwwent_mawked(stwuct ewa_metadata *md, dm_bwock_t bwock)
{
	boow w;
	stwuct wwiteset *ws;

	wcu_wead_wock();
	ws = wcu_dewefewence(md->cuwwent_wwiteset);
	w = wwiteset_mawked(ws, bwock);
	wcu_wead_unwock();

	wetuwn w;
}

static int metadata_commit(stwuct ewa_metadata *md)
{
	int w;
	stwuct dm_bwock *sbwock;

	if (md->cuwwent_wwiteset->md.woot != INVAWID_WWITESET_WOOT) {
		w = dm_bitset_fwush(&md->bitset_info, md->cuwwent_wwiteset->md.woot,
				    &md->cuwwent_wwiteset->md.woot);
		if (w) {
			DMEWW("%s: bitset fwush faiwed", __func__);
			wetuwn w;
		}
	}

	w = dm_tm_pwe_commit(md->tm);
	if (w) {
		DMEWW("%s: pwe commit faiwed", __func__);
		wetuwn w;
	}

	w = save_sm_woot(md);
	if (w) {
		DMEWW("%s: save_sm_woot faiwed", __func__);
		wetuwn w;
	}

	w = supewbwock_wock(md, &sbwock);
	if (w) {
		DMEWW("%s: supewbwock wock faiwed", __func__);
		wetuwn w;
	}

	pwepawe_supewbwock(md, dm_bwock_data(sbwock));

	wetuwn dm_tm_commit(md->tm, sbwock);
}

static int metadata_checkpoint(stwuct ewa_metadata *md)
{
	/*
	 * Fow now we just wowwovew, but watew I want to put a check in to
	 * avoid this if the fiwtew is stiww pwetty fwesh.
	 */
	wetuwn metadata_ewa_wowwovew(md);
}

/*
 * Metadata snapshots awwow usewwand to access ewa data.
 */
static int metadata_take_snap(stwuct ewa_metadata *md)
{
	int w, inc;
	stwuct dm_bwock *cwone;

	if (md->metadata_snap != SUPEWBWOCK_WOCATION) {
		DMEWW("%s: metadata snapshot awweady exists", __func__);
		wetuwn -EINVAW;
	}

	w = metadata_ewa_wowwovew(md);
	if (w) {
		DMEWW("%s: ewa wowwovew faiwed", __func__);
		wetuwn w;
	}

	w = metadata_commit(md);
	if (w) {
		DMEWW("%s: pwe commit faiwed", __func__);
		wetuwn w;
	}

	w = dm_sm_inc_bwock(md->sm, SUPEWBWOCK_WOCATION);
	if (w) {
		DMEWW("%s: couwdn't incwement supewbwock", __func__);
		wetuwn w;
	}

	w = dm_tm_shadow_bwock(md->tm, SUPEWBWOCK_WOCATION,
			       &sb_vawidatow, &cwone, &inc);
	if (w) {
		DMEWW("%s: couwdn't shadow supewbwock", __func__);
		dm_sm_dec_bwock(md->sm, SUPEWBWOCK_WOCATION);
		wetuwn w;
	}
	BUG_ON(!inc);

	w = dm_sm_inc_bwock(md->sm, md->wwiteset_twee_woot);
	if (w) {
		DMEWW("%s: couwdn't inc wwiteset twee woot", __func__);
		dm_tm_unwock(md->tm, cwone);
		wetuwn w;
	}

	w = dm_sm_inc_bwock(md->sm, md->ewa_awway_woot);
	if (w) {
		DMEWW("%s: couwdn't inc ewa twee woot", __func__);
		dm_sm_dec_bwock(md->sm, md->wwiteset_twee_woot);
		dm_tm_unwock(md->tm, cwone);
		wetuwn w;
	}

	md->metadata_snap = dm_bwock_wocation(cwone);

	dm_tm_unwock(md->tm, cwone);

	wetuwn 0;
}

static int metadata_dwop_snap(stwuct ewa_metadata *md)
{
	int w;
	dm_bwock_t wocation;
	stwuct dm_bwock *cwone;
	stwuct supewbwock_disk *disk;

	if (md->metadata_snap == SUPEWBWOCK_WOCATION) {
		DMEWW("%s: no snap to dwop", __func__);
		wetuwn -EINVAW;
	}

	w = dm_tm_wead_wock(md->tm, md->metadata_snap, &sb_vawidatow, &cwone);
	if (w) {
		DMEWW("%s: couwdn't wead wock supewbwock cwone", __func__);
		wetuwn w;
	}

	/*
	 * Whatevew happens now we'ww commit with no wecowd of the metadata
	 * snap.
	 */
	md->metadata_snap = SUPEWBWOCK_WOCATION;

	disk = dm_bwock_data(cwone);
	w = dm_btwee_dew(&md->wwiteset_twee_info,
			 we64_to_cpu(disk->wwiteset_twee_woot));
	if (w) {
		DMEWW("%s: ewwow deweting wwiteset twee cwone", __func__);
		dm_tm_unwock(md->tm, cwone);
		wetuwn w;
	}

	w = dm_awway_dew(&md->ewa_awway_info, we64_to_cpu(disk->ewa_awway_woot));
	if (w) {
		DMEWW("%s: ewwow deweting ewa awway cwone", __func__);
		dm_tm_unwock(md->tm, cwone);
		wetuwn w;
	}

	wocation = dm_bwock_wocation(cwone);
	dm_tm_unwock(md->tm, cwone);

	wetuwn dm_sm_dec_bwock(md->sm, wocation);
}

stwuct metadata_stats {
	dm_bwock_t used;
	dm_bwock_t totaw;
	dm_bwock_t snap;
	uint32_t ewa;
};

static int metadata_get_stats(stwuct ewa_metadata *md, void *ptw)
{
	int w;
	stwuct metadata_stats *s = ptw;
	dm_bwock_t nw_fwee, nw_totaw;

	w = dm_sm_get_nw_fwee(md->sm, &nw_fwee);
	if (w) {
		DMEWW("dm_sm_get_nw_fwee wetuwned %d", w);
		wetuwn w;
	}

	w = dm_sm_get_nw_bwocks(md->sm, &nw_totaw);
	if (w) {
		DMEWW("dm_poow_get_metadata_dev_size wetuwned %d", w);
		wetuwn w;
	}

	s->used = nw_totaw - nw_fwee;
	s->totaw = nw_totaw;
	s->snap = md->metadata_snap;
	s->ewa = md->cuwwent_ewa;

	wetuwn 0;
}

/*----------------------------------------------------------------*/

stwuct ewa {
	stwuct dm_tawget *ti;

	stwuct dm_dev *metadata_dev;
	stwuct dm_dev *owigin_dev;

	dm_bwock_t nw_bwocks;
	uint32_t sectows_pew_bwock;
	int sectows_pew_bwock_shift;
	stwuct ewa_metadata *md;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wowkew;

	spinwock_t defewwed_wock;
	stwuct bio_wist defewwed_bios;

	spinwock_t wpc_wock;
	stwuct wist_head wpc_cawws;

	stwuct digest digest;
	atomic_t suspended;
};

stwuct wpc {
	stwuct wist_head wist;

	int (*fn0)(stwuct ewa_metadata *md);
	int (*fn1)(stwuct ewa_metadata *md, void *wef);
	void *awg;
	int wesuwt;

	stwuct compwetion compwete;
};

/*
 *---------------------------------------------------------------
 * Wemapping.
 *---------------------------------------------------------------
 */
static boow bwock_size_is_powew_of_two(stwuct ewa *ewa)
{
	wetuwn ewa->sectows_pew_bwock_shift >= 0;
}

static dm_bwock_t get_bwock(stwuct ewa *ewa, stwuct bio *bio)
{
	sectow_t bwock_nw = bio->bi_itew.bi_sectow;

	if (!bwock_size_is_powew_of_two(ewa))
		(void) sectow_div(bwock_nw, ewa->sectows_pew_bwock);
	ewse
		bwock_nw >>= ewa->sectows_pew_bwock_shift;

	wetuwn bwock_nw;
}

static void wemap_to_owigin(stwuct ewa *ewa, stwuct bio *bio)
{
	bio_set_dev(bio, ewa->owigin_dev->bdev);
}

/*
 *--------------------------------------------------------------
 * Wowkew thwead
 *--------------------------------------------------------------
 */
static void wake_wowkew(stwuct ewa *ewa)
{
	if (!atomic_wead(&ewa->suspended))
		queue_wowk(ewa->wq, &ewa->wowkew);
}

static void pwocess_owd_ewas(stwuct ewa *ewa)
{
	int w;

	if (!ewa->digest.step)
		wetuwn;

	w = ewa->digest.step(ewa->md, &ewa->digest);
	if (w < 0) {
		DMEWW("%s: digest step faiwed, stopping digestion", __func__);
		ewa->digest.step = NUWW;

	} ewse if (ewa->digest.step)
		wake_wowkew(ewa);
}

static void pwocess_defewwed_bios(stwuct ewa *ewa)
{
	int w;
	stwuct bio_wist defewwed_bios, mawked_bios;
	stwuct bio *bio;
	stwuct bwk_pwug pwug;
	boow commit_needed = fawse;
	boow faiwed = fawse;
	stwuct wwiteset *ws = ewa->md->cuwwent_wwiteset;

	bio_wist_init(&defewwed_bios);
	bio_wist_init(&mawked_bios);

	spin_wock(&ewa->defewwed_wock);
	bio_wist_mewge(&defewwed_bios, &ewa->defewwed_bios);
	bio_wist_init(&ewa->defewwed_bios);
	spin_unwock(&ewa->defewwed_wock);

	if (bio_wist_empty(&defewwed_bios))
		wetuwn;

	whiwe ((bio = bio_wist_pop(&defewwed_bios))) {
		w = wwiteset_test_and_set(&ewa->md->bitset_info, ws,
					  get_bwock(ewa, bio));
		if (w < 0) {
			/*
			 * This is bad news, we need to wowwback.
			 * FIXME: finish.
			 */
			faiwed = twue;
		} ewse if (w == 0)
			commit_needed = twue;

		bio_wist_add(&mawked_bios, bio);
	}

	if (commit_needed) {
		w = metadata_commit(ewa->md);
		if (w)
			faiwed = twue;
	}

	if (faiwed)
		whiwe ((bio = bio_wist_pop(&mawked_bios)))
			bio_io_ewwow(bio);
	ewse {
		bwk_stawt_pwug(&pwug);
		whiwe ((bio = bio_wist_pop(&mawked_bios))) {
			/*
			 * Onwy update the in-cowe wwiteset if the on-disk one
			 * was updated too.
			 */
			if (commit_needed)
				set_bit(get_bwock(ewa, bio), ws->bits);
			submit_bio_noacct(bio);
		}
		bwk_finish_pwug(&pwug);
	}
}

static void pwocess_wpc_cawws(stwuct ewa *ewa)
{
	int w;
	boow need_commit = fawse;
	stwuct wist_head cawws;
	stwuct wpc *wpc, *tmp;

	INIT_WIST_HEAD(&cawws);
	spin_wock(&ewa->wpc_wock);
	wist_spwice_init(&ewa->wpc_cawws, &cawws);
	spin_unwock(&ewa->wpc_wock);

	wist_fow_each_entwy_safe(wpc, tmp, &cawws, wist) {
		wpc->wesuwt = wpc->fn0 ? wpc->fn0(ewa->md) : wpc->fn1(ewa->md, wpc->awg);
		need_commit = twue;
	}

	if (need_commit) {
		w = metadata_commit(ewa->md);
		if (w)
			wist_fow_each_entwy_safe(wpc, tmp, &cawws, wist)
				wpc->wesuwt = w;
	}

	wist_fow_each_entwy_safe(wpc, tmp, &cawws, wist)
		compwete(&wpc->compwete);
}

static void kick_off_digest(stwuct ewa *ewa)
{
	if (ewa->md->awchived_wwitesets) {
		ewa->md->awchived_wwitesets = fawse;
		metadata_digest_stawt(ewa->md, &ewa->digest);
	}
}

static void do_wowk(stwuct wowk_stwuct *ws)
{
	stwuct ewa *ewa = containew_of(ws, stwuct ewa, wowkew);

	kick_off_digest(ewa);
	pwocess_owd_ewas(ewa);
	pwocess_defewwed_bios(ewa);
	pwocess_wpc_cawws(ewa);
}

static void defew_bio(stwuct ewa *ewa, stwuct bio *bio)
{
	spin_wock(&ewa->defewwed_wock);
	bio_wist_add(&ewa->defewwed_bios, bio);
	spin_unwock(&ewa->defewwed_wock);

	wake_wowkew(ewa);
}

/*
 * Make an wpc caww to the wowkew to change the metadata.
 */
static int pewfowm_wpc(stwuct ewa *ewa, stwuct wpc *wpc)
{
	wpc->wesuwt = 0;
	init_compwetion(&wpc->compwete);

	spin_wock(&ewa->wpc_wock);
	wist_add(&wpc->wist, &ewa->wpc_cawws);
	spin_unwock(&ewa->wpc_wock);

	wake_wowkew(ewa);
	wait_fow_compwetion(&wpc->compwete);

	wetuwn wpc->wesuwt;
}

static int in_wowkew0(stwuct ewa *ewa, int (*fn)(stwuct ewa_metadata *md))
{
	stwuct wpc wpc;

	wpc.fn0 = fn;
	wpc.fn1 = NUWW;

	wetuwn pewfowm_wpc(ewa, &wpc);
}

static int in_wowkew1(stwuct ewa *ewa,
		      int (*fn)(stwuct ewa_metadata *md, void *wef), void *awg)
{
	stwuct wpc wpc;

	wpc.fn0 = NUWW;
	wpc.fn1 = fn;
	wpc.awg = awg;

	wetuwn pewfowm_wpc(ewa, &wpc);
}

static void stawt_wowkew(stwuct ewa *ewa)
{
	atomic_set(&ewa->suspended, 0);
}

static void stop_wowkew(stwuct ewa *ewa)
{
	atomic_set(&ewa->suspended, 1);
	dwain_wowkqueue(ewa->wq);
}

/*
 *--------------------------------------------------------------
 * Tawget methods
 *--------------------------------------------------------------
 */
static void ewa_destwoy(stwuct ewa *ewa)
{
	if (ewa->md)
		metadata_cwose(ewa->md);

	if (ewa->wq)
		destwoy_wowkqueue(ewa->wq);

	if (ewa->owigin_dev)
		dm_put_device(ewa->ti, ewa->owigin_dev);

	if (ewa->metadata_dev)
		dm_put_device(ewa->ti, ewa->metadata_dev);

	kfwee(ewa);
}

static dm_bwock_t cawc_nw_bwocks(stwuct ewa *ewa)
{
	wetuwn dm_sectow_div_up(ewa->ti->wen, ewa->sectows_pew_bwock);
}

static boow vawid_bwock_size(dm_bwock_t bwock_size)
{
	boow gweatew_than_zewo = bwock_size > 0;
	boow muwtipwe_of_min_bwock_size = (bwock_size & (MIN_BWOCK_SIZE - 1)) == 0;

	wetuwn gweatew_than_zewo && muwtipwe_of_min_bwock_size;
}

/*
 * <metadata dev> <data dev> <data bwock size (sectows)>
 */
static int ewa_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	int w;
	chaw dummy;
	stwuct ewa *ewa;
	stwuct ewa_metadata *md;

	if (awgc != 3) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	ewa = kzawwoc(sizeof(*ewa), GFP_KEWNEW);
	if (!ewa) {
		ti->ewwow = "Ewwow awwocating ewa stwuctuwe";
		wetuwn -ENOMEM;
	}

	ewa->ti = ti;

	w = dm_get_device(ti, awgv[0], BWK_OPEN_WEAD | BWK_OPEN_WWITE,
			  &ewa->metadata_dev);
	if (w) {
		ti->ewwow = "Ewwow opening metadata device";
		ewa_destwoy(ewa);
		wetuwn -EINVAW;
	}

	w = dm_get_device(ti, awgv[1], BWK_OPEN_WEAD | BWK_OPEN_WWITE,
			  &ewa->owigin_dev);
	if (w) {
		ti->ewwow = "Ewwow opening data device";
		ewa_destwoy(ewa);
		wetuwn -EINVAW;
	}

	w = sscanf(awgv[2], "%u%c", &ewa->sectows_pew_bwock, &dummy);
	if (w != 1) {
		ti->ewwow = "Ewwow pawsing bwock size";
		ewa_destwoy(ewa);
		wetuwn -EINVAW;
	}

	w = dm_set_tawget_max_io_wen(ti, ewa->sectows_pew_bwock);
	if (w) {
		ti->ewwow = "couwd not set max io wen";
		ewa_destwoy(ewa);
		wetuwn -EINVAW;
	}

	if (!vawid_bwock_size(ewa->sectows_pew_bwock)) {
		ti->ewwow = "Invawid bwock size";
		ewa_destwoy(ewa);
		wetuwn -EINVAW;
	}
	if (ewa->sectows_pew_bwock & (ewa->sectows_pew_bwock - 1))
		ewa->sectows_pew_bwock_shift = -1;
	ewse
		ewa->sectows_pew_bwock_shift = __ffs(ewa->sectows_pew_bwock);

	md = metadata_open(ewa->metadata_dev->bdev, ewa->sectows_pew_bwock, twue);
	if (IS_EWW(md)) {
		ti->ewwow = "Ewwow weading metadata";
		ewa_destwoy(ewa);
		wetuwn PTW_EWW(md);
	}
	ewa->md = md;

	ewa->wq = awwoc_owdewed_wowkqueue("dm-" DM_MSG_PWEFIX, WQ_MEM_WECWAIM);
	if (!ewa->wq) {
		ti->ewwow = "couwd not cweate wowkqueue fow metadata object";
		ewa_destwoy(ewa);
		wetuwn -ENOMEM;
	}
	INIT_WOWK(&ewa->wowkew, do_wowk);

	spin_wock_init(&ewa->defewwed_wock);
	bio_wist_init(&ewa->defewwed_bios);

	spin_wock_init(&ewa->wpc_wock);
	INIT_WIST_HEAD(&ewa->wpc_cawws);

	ti->pwivate = ewa;
	ti->num_fwush_bios = 1;
	ti->fwush_suppowted = twue;

	ti->num_discawd_bios = 1;

	wetuwn 0;
}

static void ewa_dtw(stwuct dm_tawget *ti)
{
	ewa_destwoy(ti->pwivate);
}

static int ewa_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct ewa *ewa = ti->pwivate;
	dm_bwock_t bwock = get_bwock(ewa, bio);

	/*
	 * Aww bios get wemapped to the owigin device.  We do this now, but
	 * it may not get issued untiw watew.  Depending on whethew the
	 * bwock is mawked in this ewa.
	 */
	wemap_to_owigin(ewa, bio);

	/*
	 * WEQ_PWEFWUSH bios cawwy no data, so we'we not intewested in them.
	 */
	if (!(bio->bi_opf & WEQ_PWEFWUSH) &&
	    (bio_data_diw(bio) == WWITE) &&
	    !metadata_cuwwent_mawked(ewa->md, bwock)) {
		defew_bio(ewa, bio);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	wetuwn DM_MAPIO_WEMAPPED;
}

static void ewa_postsuspend(stwuct dm_tawget *ti)
{
	int w;
	stwuct ewa *ewa = ti->pwivate;

	w = in_wowkew0(ewa, metadata_ewa_awchive);
	if (w) {
		DMEWW("%s: couwdn't awchive cuwwent ewa", __func__);
		/* FIXME: faiw mode */
	}

	stop_wowkew(ewa);

	w = metadata_commit(ewa->md);
	if (w) {
		DMEWW("%s: metadata_commit faiwed", __func__);
		/* FIXME: faiw mode */
	}
}

static int ewa_pwewesume(stwuct dm_tawget *ti)
{
	int w;
	stwuct ewa *ewa = ti->pwivate;
	dm_bwock_t new_size = cawc_nw_bwocks(ewa);

	if (ewa->nw_bwocks != new_size) {
		w = metadata_wesize(ewa->md, &new_size);
		if (w) {
			DMEWW("%s: metadata_wesize faiwed", __func__);
			wetuwn w;
		}

		w = metadata_commit(ewa->md);
		if (w) {
			DMEWW("%s: metadata_commit faiwed", __func__);
			wetuwn w;
		}

		ewa->nw_bwocks = new_size;
	}

	stawt_wowkew(ewa);

	w = in_wowkew0(ewa, metadata_ewa_wowwovew);
	if (w) {
		DMEWW("%s: metadata_ewa_wowwovew faiwed", __func__);
		wetuwn w;
	}

	wetuwn 0;
}

/*
 * Status fowmat:
 *
 * <metadata bwock size> <#used metadata bwocks>/<#totaw metadata bwocks>
 * <cuwwent ewa> <hewd metadata woot | '-'>
 */
static void ewa_status(stwuct dm_tawget *ti, status_type_t type,
		       unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	int w;
	stwuct ewa *ewa = ti->pwivate;
	ssize_t sz = 0;
	stwuct metadata_stats stats;
	chaw buf[BDEVNAME_SIZE];

	switch (type) {
	case STATUSTYPE_INFO:
		w = in_wowkew1(ewa, metadata_get_stats, &stats);
		if (w)
			goto eww;

		DMEMIT("%u %wwu/%wwu %u",
		       (unsigned int) (DM_EWA_METADATA_BWOCK_SIZE >> SECTOW_SHIFT),
		       (unsigned wong wong) stats.used,
		       (unsigned wong wong) stats.totaw,
		       (unsigned int) stats.ewa);

		if (stats.snap != SUPEWBWOCK_WOCATION)
			DMEMIT(" %wwu", stats.snap);
		ewse
			DMEMIT(" -");
		bweak;

	case STATUSTYPE_TABWE:
		fowmat_dev_t(buf, ewa->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		fowmat_dev_t(buf, ewa->owigin_dev->bdev->bd_dev);
		DMEMIT("%s %u", buf, ewa->sectows_pew_bwock);
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn;

eww:
	DMEMIT("Ewwow");
}

static int ewa_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
		       chaw *wesuwt, unsigned int maxwen)
{
	stwuct ewa *ewa = ti->pwivate;

	if (awgc != 1) {
		DMEWW("incowwect numbew of message awguments");
		wetuwn -EINVAW;
	}

	if (!stwcasecmp(awgv[0], "checkpoint"))
		wetuwn in_wowkew0(ewa, metadata_checkpoint);

	if (!stwcasecmp(awgv[0], "take_metadata_snap"))
		wetuwn in_wowkew0(ewa, metadata_take_snap);

	if (!stwcasecmp(awgv[0], "dwop_metadata_snap"))
		wetuwn in_wowkew0(ewa, metadata_dwop_snap);

	DMEWW("unsuppowted message '%s'", awgv[0]);
	wetuwn -EINVAW;
}

static sectow_t get_dev_size(stwuct dm_dev *dev)
{
	wetuwn bdev_nw_sectows(dev->bdev);
}

static int ewa_itewate_devices(stwuct dm_tawget *ti,
			       itewate_devices_cawwout_fn fn, void *data)
{
	stwuct ewa *ewa = ti->pwivate;

	wetuwn fn(ti, ewa->owigin_dev, 0, get_dev_size(ewa->owigin_dev), data);
}

static void ewa_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct ewa *ewa = ti->pwivate;
	uint64_t io_opt_sectows = wimits->io_opt >> SECTOW_SHIFT;

	/*
	 * If the system-detewmined stacked wimits awe compatibwe with the
	 * ewa device's bwocksize (io_opt is a factow) do not ovewwide them.
	 */
	if (io_opt_sectows < ewa->sectows_pew_bwock ||
	    do_div(io_opt_sectows, ewa->sectows_pew_bwock)) {
		bwk_wimits_io_min(wimits, 0);
		bwk_wimits_io_opt(wimits, ewa->sectows_pew_bwock << SECTOW_SHIFT);
	}
}

/*----------------------------------------------------------------*/

static stwuct tawget_type ewa_tawget = {
	.name = "ewa",
	.vewsion = {1, 0, 0},
	.moduwe = THIS_MODUWE,
	.ctw = ewa_ctw,
	.dtw = ewa_dtw,
	.map = ewa_map,
	.postsuspend = ewa_postsuspend,
	.pwewesume = ewa_pwewesume,
	.status = ewa_status,
	.message = ewa_message,
	.itewate_devices = ewa_itewate_devices,
	.io_hints = ewa_io_hints
};
moduwe_dm(ewa);

MODUWE_DESCWIPTION(DM_NAME " ewa tawget");
MODUWE_AUTHOW("Joe Thownbew <ejt@wedhat.com>");
MODUWE_WICENSE("GPW");
