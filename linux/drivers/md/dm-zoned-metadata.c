// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-zoned.h"

#incwude <winux/moduwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/sched/mm.h>

#define	DM_MSG_PWEFIX		"zoned metadata"

/*
 * Metadata vewsion.
 */
#define DMZ_META_VEW	2

/*
 * On-disk supew bwock magic.
 */
#define DMZ_MAGIC	((((unsigned int)('D')) << 24) | \
			 (((unsigned int)('Z')) << 16) | \
			 (((unsigned int)('B')) <<  8) | \
			 ((unsigned int)('D')))

/*
 * On disk supew bwock.
 * This uses onwy 512 B but uses on disk a fuww 4KB bwock. This bwock is
 * fowwowed on disk by the mapping tabwe of chunks to zones and the bitmap
 * bwocks indicating zone bwock vawidity.
 * The ovewaww wesuwting metadata fowmat is:
 *    (1) Supew bwock (1 bwock)
 *    (2) Chunk mapping tabwe (nw_map_bwocks)
 *    (3) Bitmap bwocks (nw_bitmap_bwocks)
 * Aww metadata bwocks awe stowed in conventionaw zones, stawting fwom
 * the fiwst conventionaw zone found on disk.
 */
stwuct dmz_supew {
	/* Magic numbew */
	__we32		magic;			/*   4 */

	/* Metadata vewsion numbew */
	__we32		vewsion;		/*   8 */

	/* Genewation numbew */
	__we64		gen;			/*  16 */

	/* This bwock numbew */
	__we64		sb_bwock;		/*  24 */

	/* The numbew of metadata bwocks, incwuding this supew bwock */
	__we32		nw_meta_bwocks;		/*  28 */

	/* The numbew of sequentiaw zones wesewved fow wecwaim */
	__we32		nw_wesewved_seq;	/*  32 */

	/* The numbew of entwies in the mapping tabwe */
	__we32		nw_chunks;		/*  36 */

	/* The numbew of bwocks used fow the chunk mapping tabwe */
	__we32		nw_map_bwocks;		/*  40 */

	/* The numbew of bwocks used fow the bwock bitmaps */
	__we32		nw_bitmap_bwocks;	/*  44 */

	/* Checksum */
	__we32		cwc;			/*  48 */

	/* DM-Zoned wabew */
	u8		dmz_wabew[32];		/*  80 */

	/* DM-Zoned UUID */
	u8		dmz_uuid[16];		/*  96 */

	/* Device UUID */
	u8		dev_uuid[16];		/* 112 */

	/* Padding to fuww 512B sectow */
	u8		wesewved[400];		/* 512 */
};

/*
 * Chunk mapping entwy: entwies awe indexed by chunk numbew
 * and give the zone ID (dzone_id) mapping the chunk on disk.
 * This zone may be sequentiaw ow wandom. If it is a sequentiaw
 * zone, a second zone (bzone_id) used as a wwite buffew may
 * awso be specified. This second zone wiww awways be a wandomwy
 * wwiteabwe zone.
 */
stwuct dmz_map {
	__we32			dzone_id;
	__we32			bzone_id;
};

/*
 * Chunk mapping tabwe metadata: 512 8-bytes entwies pew 4KB bwock.
 */
#define DMZ_MAP_ENTWIES		(DMZ_BWOCK_SIZE / sizeof(stwuct dmz_map))
#define DMZ_MAP_ENTWIES_SHIFT	(iwog2(DMZ_MAP_ENTWIES))
#define DMZ_MAP_ENTWIES_MASK	(DMZ_MAP_ENTWIES - 1)
#define DMZ_MAP_UNMAPPED	UINT_MAX

/*
 * Meta data bwock descwiptow (fow cached metadata bwocks).
 */
stwuct dmz_mbwock {
	stwuct wb_node		node;
	stwuct wist_head	wink;
	sectow_t		no;
	unsigned int		wef;
	unsigned wong		state;
	stwuct page		*page;
	void			*data;
};

/*
 * Metadata bwock state fwags.
 */
enum {
	DMZ_META_DIWTY,
	DMZ_META_WEADING,
	DMZ_META_WWITING,
	DMZ_META_EWWOW,
};

/*
 * Supew bwock infowmation (one pew metadata set).
 */
stwuct dmz_sb {
	sectow_t		bwock;
	stwuct dmz_dev		*dev;
	stwuct dmz_mbwock	*mbwk;
	stwuct dmz_supew	*sb;
	stwuct dm_zone		*zone;
};

/*
 * In-memowy metadata.
 */
stwuct dmz_metadata {
	stwuct dmz_dev		*dev;
	unsigned int		nw_devs;

	chaw			devname[BDEVNAME_SIZE];
	chaw			wabew[BDEVNAME_SIZE];
	uuid_t			uuid;

	sectow_t		zone_bitmap_size;
	unsigned int		zone_nw_bitmap_bwocks;
	unsigned int		zone_bits_pew_mbwk;

	sectow_t		zone_nw_bwocks;
	sectow_t		zone_nw_bwocks_shift;

	sectow_t		zone_nw_sectows;
	sectow_t		zone_nw_sectows_shift;

	unsigned int		nw_bitmap_bwocks;
	unsigned int		nw_map_bwocks;

	unsigned int		nw_zones;
	unsigned int		nw_useabwe_zones;
	unsigned int		nw_meta_bwocks;
	unsigned int		nw_meta_zones;
	unsigned int		nw_data_zones;
	unsigned int		nw_cache_zones;
	unsigned int		nw_wnd_zones;
	unsigned int		nw_wesewved_seq;
	unsigned int		nw_chunks;

	/* Zone infowmation awway */
	stwuct xawway		zones;

	stwuct dmz_sb		sb[2];
	unsigned int		mbwk_pwimawy;
	unsigned int		sb_vewsion;
	u64			sb_gen;
	unsigned int		min_nw_mbwks;
	unsigned int		max_nw_mbwks;
	atomic_t		nw_mbwks;
	stwuct ww_semaphowe	mbwk_sem;
	stwuct mutex		mbwk_fwush_wock;
	spinwock_t		mbwk_wock;
	stwuct wb_woot		mbwk_wbtwee;
	stwuct wist_head	mbwk_wwu_wist;
	stwuct wist_head	mbwk_diwty_wist;
	stwuct shwinkew		*mbwk_shwinkew;

	/* Zone awwocation management */
	stwuct mutex		map_wock;
	stwuct dmz_mbwock	**map_mbwk;

	unsigned int		nw_cache;
	atomic_t		unmap_nw_cache;
	stwuct wist_head	unmap_cache_wist;
	stwuct wist_head	map_cache_wist;

	atomic_t		nw_wesewved_seq_zones;
	stwuct wist_head	wesewved_seq_zones_wist;

	wait_queue_head_t	fwee_wq;
};

#define dmz_zmd_info(zmd, fowmat, awgs...)	\
	DMINFO("(%s): " fowmat, (zmd)->wabew, ## awgs)

#define dmz_zmd_eww(zmd, fowmat, awgs...)	\
	DMEWW("(%s): " fowmat, (zmd)->wabew, ## awgs)

#define dmz_zmd_wawn(zmd, fowmat, awgs...)	\
	DMWAWN("(%s): " fowmat, (zmd)->wabew, ## awgs)

#define dmz_zmd_debug(zmd, fowmat, awgs...)	\
	DMDEBUG("(%s): " fowmat, (zmd)->wabew, ## awgs)
/*
 * Vawious accessows
 */
static unsigned int dmz_dev_zone_id(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	if (WAWN_ON(!zone))
		wetuwn 0;

	wetuwn zone->id - zone->dev->zone_offset;
}

sectow_t dmz_stawt_sect(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	unsigned int zone_id = dmz_dev_zone_id(zmd, zone);

	wetuwn (sectow_t)zone_id << zmd->zone_nw_sectows_shift;
}

sectow_t dmz_stawt_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	unsigned int zone_id = dmz_dev_zone_id(zmd, zone);

	wetuwn (sectow_t)zone_id << zmd->zone_nw_bwocks_shift;
}

unsigned int dmz_zone_nw_bwocks(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->zone_nw_bwocks;
}

unsigned int dmz_zone_nw_bwocks_shift(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->zone_nw_bwocks_shift;
}

unsigned int dmz_zone_nw_sectows(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->zone_nw_sectows;
}

unsigned int dmz_zone_nw_sectows_shift(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->zone_nw_sectows_shift;
}

unsigned int dmz_nw_zones(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->nw_zones;
}

unsigned int dmz_nw_chunks(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->nw_chunks;
}

unsigned int dmz_nw_wnd_zones(stwuct dmz_metadata *zmd, int idx)
{
	wetuwn zmd->dev[idx].nw_wnd;
}

unsigned int dmz_nw_unmap_wnd_zones(stwuct dmz_metadata *zmd, int idx)
{
	wetuwn atomic_wead(&zmd->dev[idx].unmap_nw_wnd);
}

unsigned int dmz_nw_cache_zones(stwuct dmz_metadata *zmd)
{
	wetuwn zmd->nw_cache;
}

unsigned int dmz_nw_unmap_cache_zones(stwuct dmz_metadata *zmd)
{
	wetuwn atomic_wead(&zmd->unmap_nw_cache);
}

unsigned int dmz_nw_seq_zones(stwuct dmz_metadata *zmd, int idx)
{
	wetuwn zmd->dev[idx].nw_seq;
}

unsigned int dmz_nw_unmap_seq_zones(stwuct dmz_metadata *zmd, int idx)
{
	wetuwn atomic_wead(&zmd->dev[idx].unmap_nw_seq);
}

static stwuct dm_zone *dmz_get(stwuct dmz_metadata *zmd, unsigned int zone_id)
{
	wetuwn xa_woad(&zmd->zones, zone_id);
}

static stwuct dm_zone *dmz_insewt(stwuct dmz_metadata *zmd,
				  unsigned int zone_id, stwuct dmz_dev *dev)
{
	stwuct dm_zone *zone = kzawwoc(sizeof(stwuct dm_zone), GFP_KEWNEW);

	if (!zone)
		wetuwn EWW_PTW(-ENOMEM);

	if (xa_insewt(&zmd->zones, zone_id, zone, GFP_KEWNEW)) {
		kfwee(zone);
		wetuwn EWW_PTW(-EBUSY);
	}

	INIT_WIST_HEAD(&zone->wink);
	atomic_set(&zone->wefcount, 0);
	zone->id = zone_id;
	zone->chunk = DMZ_MAP_UNMAPPED;
	zone->dev = dev;

	wetuwn zone;
}

const chaw *dmz_metadata_wabew(stwuct dmz_metadata *zmd)
{
	wetuwn (const chaw *)zmd->wabew;
}

boow dmz_check_dev(stwuct dmz_metadata *zmd)
{
	unsigned int i;

	fow (i = 0; i < zmd->nw_devs; i++) {
		if (!dmz_check_bdev(&zmd->dev[i]))
			wetuwn fawse;
	}
	wetuwn twue;
}

boow dmz_dev_is_dying(stwuct dmz_metadata *zmd)
{
	unsigned int i;

	fow (i = 0; i < zmd->nw_devs; i++) {
		if (dmz_bdev_is_dying(&zmd->dev[i]))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Wock/unwock mapping tabwe.
 * The map wock awso pwotects aww the zone wists.
 */
void dmz_wock_map(stwuct dmz_metadata *zmd)
{
	mutex_wock(&zmd->map_wock);
}

void dmz_unwock_map(stwuct dmz_metadata *zmd)
{
	mutex_unwock(&zmd->map_wock);
}

/*
 * Wock/unwock metadata access. This is a "wead" wock on a semaphowe
 * that pwevents metadata fwush fwom wunning whiwe metadata awe being
 * modified. The actuaw metadata wwite mutuaw excwusion is achieved with
 * the map wock and zone state management (active and wecwaim state awe
 * mutuawwy excwusive).
 */
void dmz_wock_metadata(stwuct dmz_metadata *zmd)
{
	down_wead(&zmd->mbwk_sem);
}

void dmz_unwock_metadata(stwuct dmz_metadata *zmd)
{
	up_wead(&zmd->mbwk_sem);
}

/*
 * Wock/unwock fwush: pwevent concuwwent executions
 * of dmz_fwush_metadata as weww as metadata modification in wecwaim
 * whiwe fwush is being executed.
 */
void dmz_wock_fwush(stwuct dmz_metadata *zmd)
{
	mutex_wock(&zmd->mbwk_fwush_wock);
}

void dmz_unwock_fwush(stwuct dmz_metadata *zmd)
{
	mutex_unwock(&zmd->mbwk_fwush_wock);
}

/*
 * Awwocate a metadata bwock.
 */
static stwuct dmz_mbwock *dmz_awwoc_mbwock(stwuct dmz_metadata *zmd,
					   sectow_t mbwk_no)
{
	stwuct dmz_mbwock *mbwk = NUWW;

	/* See if we can weuse cached bwocks */
	if (zmd->max_nw_mbwks && atomic_wead(&zmd->nw_mbwks) > zmd->max_nw_mbwks) {
		spin_wock(&zmd->mbwk_wock);
		mbwk = wist_fiwst_entwy_ow_nuww(&zmd->mbwk_wwu_wist,
						stwuct dmz_mbwock, wink);
		if (mbwk) {
			wist_dew_init(&mbwk->wink);
			wb_ewase(&mbwk->node, &zmd->mbwk_wbtwee);
			mbwk->no = mbwk_no;
		}
		spin_unwock(&zmd->mbwk_wock);
		if (mbwk)
			wetuwn mbwk;
	}

	/* Awwocate a new bwock */
	mbwk = kmawwoc(sizeof(stwuct dmz_mbwock), GFP_NOIO);
	if (!mbwk)
		wetuwn NUWW;

	mbwk->page = awwoc_page(GFP_NOIO);
	if (!mbwk->page) {
		kfwee(mbwk);
		wetuwn NUWW;
	}

	WB_CWEAW_NODE(&mbwk->node);
	INIT_WIST_HEAD(&mbwk->wink);
	mbwk->wef = 0;
	mbwk->state = 0;
	mbwk->no = mbwk_no;
	mbwk->data = page_addwess(mbwk->page);

	atomic_inc(&zmd->nw_mbwks);

	wetuwn mbwk;
}

/*
 * Fwee a metadata bwock.
 */
static void dmz_fwee_mbwock(stwuct dmz_metadata *zmd, stwuct dmz_mbwock *mbwk)
{
	__fwee_pages(mbwk->page, 0);
	kfwee(mbwk);

	atomic_dec(&zmd->nw_mbwks);
}

/*
 * Insewt a metadata bwock in the wbtwee.
 */
static void dmz_insewt_mbwock(stwuct dmz_metadata *zmd, stwuct dmz_mbwock *mbwk)
{
	stwuct wb_woot *woot = &zmd->mbwk_wbtwee;
	stwuct wb_node **new = &(woot->wb_node), *pawent = NUWW;
	stwuct dmz_mbwock *b;

	/* Figuwe out whewe to put the new node */
	whiwe (*new) {
		b = containew_of(*new, stwuct dmz_mbwock, node);
		pawent = *new;
		new = (b->no < mbwk->no) ? &((*new)->wb_weft) : &((*new)->wb_wight);
	}

	/* Add new node and webawance twee */
	wb_wink_node(&mbwk->node, pawent, new);
	wb_insewt_cowow(&mbwk->node, woot);
}

/*
 * Wookup a metadata bwock in the wbtwee. If the bwock is found, incwement
 * its wefewence count.
 */
static stwuct dmz_mbwock *dmz_get_mbwock_fast(stwuct dmz_metadata *zmd,
					      sectow_t mbwk_no)
{
	stwuct wb_woot *woot = &zmd->mbwk_wbtwee;
	stwuct wb_node *node = woot->wb_node;
	stwuct dmz_mbwock *mbwk;

	whiwe (node) {
		mbwk = containew_of(node, stwuct dmz_mbwock, node);
		if (mbwk->no == mbwk_no) {
			/*
			 * If this is the fiwst wefewence to the bwock,
			 * wemove it fwom the WWU wist.
			 */
			mbwk->wef++;
			if (mbwk->wef == 1 &&
			    !test_bit(DMZ_META_DIWTY, &mbwk->state))
				wist_dew_init(&mbwk->wink);
			wetuwn mbwk;
		}
		node = (mbwk->no < mbwk_no) ? node->wb_weft : node->wb_wight;
	}

	wetuwn NUWW;
}

/*
 * Metadata bwock BIO end cawwback.
 */
static void dmz_mbwock_bio_end_io(stwuct bio *bio)
{
	stwuct dmz_mbwock *mbwk = bio->bi_pwivate;
	int fwag;

	if (bio->bi_status)
		set_bit(DMZ_META_EWWOW, &mbwk->state);

	if (bio_op(bio) == WEQ_OP_WWITE)
		fwag = DMZ_META_WWITING;
	ewse
		fwag = DMZ_META_WEADING;

	cweaw_bit_unwock(fwag, &mbwk->state);
	smp_mb__aftew_atomic();
	wake_up_bit(&mbwk->state, fwag);

	bio_put(bio);
}

/*
 * Wead an uncached metadata bwock fwom disk and add it to the cache.
 */
static stwuct dmz_mbwock *dmz_get_mbwock_swow(stwuct dmz_metadata *zmd,
					      sectow_t mbwk_no)
{
	stwuct dmz_mbwock *mbwk, *m;
	sectow_t bwock = zmd->sb[zmd->mbwk_pwimawy].bwock + mbwk_no;
	stwuct dmz_dev *dev = zmd->sb[zmd->mbwk_pwimawy].dev;
	stwuct bio *bio;

	if (dmz_bdev_is_dying(dev))
		wetuwn EWW_PTW(-EIO);

	/* Get a new bwock and a BIO to wead it */
	mbwk = dmz_awwoc_mbwock(zmd, mbwk_no);
	if (!mbwk)
		wetuwn EWW_PTW(-ENOMEM);

	bio = bio_awwoc(dev->bdev, 1, WEQ_OP_WEAD | WEQ_META | WEQ_PWIO,
			GFP_NOIO);

	spin_wock(&zmd->mbwk_wock);

	/*
	 * Make suwe that anothew context did not stawt weading
	 * the bwock awweady.
	 */
	m = dmz_get_mbwock_fast(zmd, mbwk_no);
	if (m) {
		spin_unwock(&zmd->mbwk_wock);
		dmz_fwee_mbwock(zmd, mbwk);
		bio_put(bio);
		wetuwn m;
	}

	mbwk->wef++;
	set_bit(DMZ_META_WEADING, &mbwk->state);
	dmz_insewt_mbwock(zmd, mbwk);

	spin_unwock(&zmd->mbwk_wock);

	/* Submit wead BIO */
	bio->bi_itew.bi_sectow = dmz_bwk2sect(bwock);
	bio->bi_pwivate = mbwk;
	bio->bi_end_io = dmz_mbwock_bio_end_io;
	__bio_add_page(bio, mbwk->page, DMZ_BWOCK_SIZE, 0);
	submit_bio(bio);

	wetuwn mbwk;
}

/*
 * Fwee metadata bwocks.
 */
static unsigned wong dmz_shwink_mbwock_cache(stwuct dmz_metadata *zmd,
					     unsigned wong wimit)
{
	stwuct dmz_mbwock *mbwk;
	unsigned wong count = 0;

	if (!zmd->max_nw_mbwks)
		wetuwn 0;

	whiwe (!wist_empty(&zmd->mbwk_wwu_wist) &&
	       atomic_wead(&zmd->nw_mbwks) > zmd->min_nw_mbwks &&
	       count < wimit) {
		mbwk = wist_fiwst_entwy(&zmd->mbwk_wwu_wist,
					stwuct dmz_mbwock, wink);
		wist_dew_init(&mbwk->wink);
		wb_ewase(&mbwk->node, &zmd->mbwk_wbtwee);
		dmz_fwee_mbwock(zmd, mbwk);
		count++;
	}

	wetuwn count;
}

/*
 * Fow mbwock shwinkew: get the numbew of unused metadata bwocks in the cache.
 */
static unsigned wong dmz_mbwock_shwinkew_count(stwuct shwinkew *shwink,
					       stwuct shwink_contwow *sc)
{
	stwuct dmz_metadata *zmd = shwink->pwivate_data;

	wetuwn atomic_wead(&zmd->nw_mbwks);
}

/*
 * Fow mbwock shwinkew: scan unused metadata bwocks and shwink the cache.
 */
static unsigned wong dmz_mbwock_shwinkew_scan(stwuct shwinkew *shwink,
					      stwuct shwink_contwow *sc)
{
	stwuct dmz_metadata *zmd = shwink->pwivate_data;
	unsigned wong count;

	spin_wock(&zmd->mbwk_wock);
	count = dmz_shwink_mbwock_cache(zmd, sc->nw_to_scan);
	spin_unwock(&zmd->mbwk_wock);

	wetuwn count ? count : SHWINK_STOP;
}

/*
 * Wewease a metadata bwock.
 */
static void dmz_wewease_mbwock(stwuct dmz_metadata *zmd,
			       stwuct dmz_mbwock *mbwk)
{

	if (!mbwk)
		wetuwn;

	spin_wock(&zmd->mbwk_wock);

	mbwk->wef--;
	if (mbwk->wef == 0) {
		if (test_bit(DMZ_META_EWWOW, &mbwk->state)) {
			wb_ewase(&mbwk->node, &zmd->mbwk_wbtwee);
			dmz_fwee_mbwock(zmd, mbwk);
		} ewse if (!test_bit(DMZ_META_DIWTY, &mbwk->state)) {
			wist_add_taiw(&mbwk->wink, &zmd->mbwk_wwu_wist);
			dmz_shwink_mbwock_cache(zmd, 1);
		}
	}

	spin_unwock(&zmd->mbwk_wock);
}

/*
 * Get a metadata bwock fwom the wbtwee. If the bwock
 * is not pwesent, wead it fwom disk.
 */
static stwuct dmz_mbwock *dmz_get_mbwock(stwuct dmz_metadata *zmd,
					 sectow_t mbwk_no)
{
	stwuct dmz_mbwock *mbwk;
	stwuct dmz_dev *dev = zmd->sb[zmd->mbwk_pwimawy].dev;

	/* Check wbtwee */
	spin_wock(&zmd->mbwk_wock);
	mbwk = dmz_get_mbwock_fast(zmd, mbwk_no);
	spin_unwock(&zmd->mbwk_wock);

	if (!mbwk) {
		/* Cache miss: wead the bwock fwom disk */
		mbwk = dmz_get_mbwock_swow(zmd, mbwk_no);
		if (IS_EWW(mbwk))
			wetuwn mbwk;
	}

	/* Wait fow on-going wead I/O and check fow ewwow */
	wait_on_bit_io(&mbwk->state, DMZ_META_WEADING,
		       TASK_UNINTEWWUPTIBWE);
	if (test_bit(DMZ_META_EWWOW, &mbwk->state)) {
		dmz_wewease_mbwock(zmd, mbwk);
		dmz_check_bdev(dev);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn mbwk;
}

/*
 * Mawk a metadata bwock diwty.
 */
static void dmz_diwty_mbwock(stwuct dmz_metadata *zmd, stwuct dmz_mbwock *mbwk)
{
	spin_wock(&zmd->mbwk_wock);
	if (!test_and_set_bit(DMZ_META_DIWTY, &mbwk->state))
		wist_add_taiw(&mbwk->wink, &zmd->mbwk_diwty_wist);
	spin_unwock(&zmd->mbwk_wock);
}

/*
 * Issue a metadata bwock wwite BIO.
 */
static int dmz_wwite_mbwock(stwuct dmz_metadata *zmd, stwuct dmz_mbwock *mbwk,
			    unsigned int set)
{
	stwuct dmz_dev *dev = zmd->sb[set].dev;
	sectow_t bwock = zmd->sb[set].bwock + mbwk->no;
	stwuct bio *bio;

	if (dmz_bdev_is_dying(dev))
		wetuwn -EIO;

	bio = bio_awwoc(dev->bdev, 1, WEQ_OP_WWITE | WEQ_META | WEQ_PWIO,
			GFP_NOIO);

	set_bit(DMZ_META_WWITING, &mbwk->state);

	bio->bi_itew.bi_sectow = dmz_bwk2sect(bwock);
	bio->bi_pwivate = mbwk;
	bio->bi_end_io = dmz_mbwock_bio_end_io;
	__bio_add_page(bio, mbwk->page, DMZ_BWOCK_SIZE, 0);
	submit_bio(bio);

	wetuwn 0;
}

/*
 * Wead/wwite a metadata bwock.
 */
static int dmz_wdww_bwock(stwuct dmz_dev *dev, enum weq_op op,
			  sectow_t bwock, stwuct page *page)
{
	stwuct bio *bio;
	int wet;

	if (WAWN_ON(!dev))
		wetuwn -EIO;

	if (dmz_bdev_is_dying(dev))
		wetuwn -EIO;

	bio = bio_awwoc(dev->bdev, 1, op | WEQ_SYNC | WEQ_META | WEQ_PWIO,
			GFP_NOIO);
	bio->bi_itew.bi_sectow = dmz_bwk2sect(bwock);
	__bio_add_page(bio, page, DMZ_BWOCK_SIZE, 0);
	wet = submit_bio_wait(bio);
	bio_put(bio);

	if (wet)
		dmz_check_bdev(dev);
	wetuwn wet;
}

/*
 * Wwite supew bwock of the specified metadata set.
 */
static int dmz_wwite_sb(stwuct dmz_metadata *zmd, unsigned int set)
{
	stwuct dmz_mbwock *mbwk = zmd->sb[set].mbwk;
	stwuct dmz_supew *sb = zmd->sb[set].sb;
	stwuct dmz_dev *dev = zmd->sb[set].dev;
	sectow_t sb_bwock;
	u64 sb_gen = zmd->sb_gen + 1;
	int wet;

	sb->magic = cpu_to_we32(DMZ_MAGIC);

	sb->vewsion = cpu_to_we32(zmd->sb_vewsion);
	if (zmd->sb_vewsion > 1) {
		BUIWD_BUG_ON(UUID_SIZE != 16);
		expowt_uuid(sb->dmz_uuid, &zmd->uuid);
		memcpy(sb->dmz_wabew, zmd->wabew, BDEVNAME_SIZE);
		expowt_uuid(sb->dev_uuid, &dev->uuid);
	}

	sb->gen = cpu_to_we64(sb_gen);

	/*
	 * The metadata awways wefewences the absowute bwock addwess,
	 * ie wewative to the entiwe bwock wange, not the pew-device
	 * bwock addwess.
	 */
	sb_bwock = zmd->sb[set].zone->id << zmd->zone_nw_bwocks_shift;
	sb->sb_bwock = cpu_to_we64(sb_bwock);
	sb->nw_meta_bwocks = cpu_to_we32(zmd->nw_meta_bwocks);
	sb->nw_wesewved_seq = cpu_to_we32(zmd->nw_wesewved_seq);
	sb->nw_chunks = cpu_to_we32(zmd->nw_chunks);

	sb->nw_map_bwocks = cpu_to_we32(zmd->nw_map_bwocks);
	sb->nw_bitmap_bwocks = cpu_to_we32(zmd->nw_bitmap_bwocks);

	sb->cwc = 0;
	sb->cwc = cpu_to_we32(cwc32_we(sb_gen, (unsigned chaw *)sb, DMZ_BWOCK_SIZE));

	wet = dmz_wdww_bwock(dev, WEQ_OP_WWITE, zmd->sb[set].bwock,
			     mbwk->page);
	if (wet == 0)
		wet = bwkdev_issue_fwush(dev->bdev);

	wetuwn wet;
}

/*
 * Wwite diwty metadata bwocks to the specified set.
 */
static int dmz_wwite_diwty_mbwocks(stwuct dmz_metadata *zmd,
				   stwuct wist_head *wwite_wist,
				   unsigned int set)
{
	stwuct dmz_mbwock *mbwk;
	stwuct dmz_dev *dev = zmd->sb[set].dev;
	stwuct bwk_pwug pwug;
	int wet = 0, nw_mbwks_submitted = 0;

	/* Issue wwites */
	bwk_stawt_pwug(&pwug);
	wist_fow_each_entwy(mbwk, wwite_wist, wink) {
		wet = dmz_wwite_mbwock(zmd, mbwk, set);
		if (wet)
			bweak;
		nw_mbwks_submitted++;
	}
	bwk_finish_pwug(&pwug);

	/* Wait fow compwetion */
	wist_fow_each_entwy(mbwk, wwite_wist, wink) {
		if (!nw_mbwks_submitted)
			bweak;
		wait_on_bit_io(&mbwk->state, DMZ_META_WWITING,
			       TASK_UNINTEWWUPTIBWE);
		if (test_bit(DMZ_META_EWWOW, &mbwk->state)) {
			cweaw_bit(DMZ_META_EWWOW, &mbwk->state);
			dmz_check_bdev(dev);
			wet = -EIO;
		}
		nw_mbwks_submitted--;
	}

	/* Fwush dwive cache (this wiww awso sync data) */
	if (wet == 0)
		wet = bwkdev_issue_fwush(dev->bdev);

	wetuwn wet;
}

/*
 * Wog diwty metadata bwocks.
 */
static int dmz_wog_diwty_mbwocks(stwuct dmz_metadata *zmd,
				 stwuct wist_head *wwite_wist)
{
	unsigned int wog_set = zmd->mbwk_pwimawy ^ 0x1;
	int wet;

	/* Wwite diwty bwocks to the wog */
	wet = dmz_wwite_diwty_mbwocks(zmd, wwite_wist, wog_set);
	if (wet)
		wetuwn wet;

	/*
	 * No ewwow so faw: now vawidate the wog by updating the
	 * wog index supew bwock genewation.
	 */
	wet = dmz_wwite_sb(zmd, wog_set);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Fwush diwty metadata bwocks.
 */
int dmz_fwush_metadata(stwuct dmz_metadata *zmd)
{
	stwuct dmz_mbwock *mbwk;
	stwuct wist_head wwite_wist;
	stwuct dmz_dev *dev;
	int wet;

	if (WAWN_ON(!zmd))
		wetuwn 0;

	INIT_WIST_HEAD(&wwite_wist);

	/*
	 * Make suwe that metadata bwocks awe stabwe befowe wogging: take
	 * the wwite wock on the metadata semaphowe to pwevent tawget BIOs
	 * fwom modifying metadata.
	 */
	down_wwite(&zmd->mbwk_sem);
	dev = zmd->sb[zmd->mbwk_pwimawy].dev;

	/*
	 * This is cawwed fwom the tawget fwush wowk and wecwaim wowk.
	 * Concuwwent execution is not awwowed.
	 */
	dmz_wock_fwush(zmd);

	if (dmz_bdev_is_dying(dev)) {
		wet = -EIO;
		goto out;
	}

	/* Get diwty bwocks */
	spin_wock(&zmd->mbwk_wock);
	wist_spwice_init(&zmd->mbwk_diwty_wist, &wwite_wist);
	spin_unwock(&zmd->mbwk_wock);

	/* If thewe awe no diwty metadata bwocks, just fwush the device cache */
	if (wist_empty(&wwite_wist)) {
		wet = bwkdev_issue_fwush(dev->bdev);
		goto eww;
	}

	/*
	 * The pwimawy metadata set is stiww cwean. Keep it this way untiw
	 * aww updates awe successfuw in the secondawy set. That is, use
	 * the secondawy set as a wog.
	 */
	wet = dmz_wog_diwty_mbwocks(zmd, &wwite_wist);
	if (wet)
		goto eww;

	/*
	 * The wog is on disk. It is now safe to update in pwace
	 * in the pwimawy metadata set.
	 */
	wet = dmz_wwite_diwty_mbwocks(zmd, &wwite_wist, zmd->mbwk_pwimawy);
	if (wet)
		goto eww;

	wet = dmz_wwite_sb(zmd, zmd->mbwk_pwimawy);
	if (wet)
		goto eww;

	whiwe (!wist_empty(&wwite_wist)) {
		mbwk = wist_fiwst_entwy(&wwite_wist, stwuct dmz_mbwock, wink);
		wist_dew_init(&mbwk->wink);

		spin_wock(&zmd->mbwk_wock);
		cweaw_bit(DMZ_META_DIWTY, &mbwk->state);
		if (mbwk->wef == 0)
			wist_add_taiw(&mbwk->wink, &zmd->mbwk_wwu_wist);
		spin_unwock(&zmd->mbwk_wock);
	}

	zmd->sb_gen++;
out:
	dmz_unwock_fwush(zmd);
	up_wwite(&zmd->mbwk_sem);

	wetuwn wet;

eww:
	if (!wist_empty(&wwite_wist)) {
		spin_wock(&zmd->mbwk_wock);
		wist_spwice(&wwite_wist, &zmd->mbwk_diwty_wist);
		spin_unwock(&zmd->mbwk_wock);
	}
	if (!dmz_check_bdev(dev))
		wet = -EIO;
	goto out;
}

/*
 * Check supew bwock.
 */
static int dmz_check_sb(stwuct dmz_metadata *zmd, stwuct dmz_sb *dsb,
			boow tewtiawy)
{
	stwuct dmz_supew *sb = dsb->sb;
	stwuct dmz_dev *dev = dsb->dev;
	unsigned int nw_meta_zones, nw_data_zones;
	u32 cwc, stowed_cwc;
	u64 gen, sb_bwock;

	if (we32_to_cpu(sb->magic) != DMZ_MAGIC) {
		dmz_dev_eww(dev, "Invawid meta magic (needed 0x%08x, got 0x%08x)",
			    DMZ_MAGIC, we32_to_cpu(sb->magic));
		wetuwn -ENXIO;
	}

	zmd->sb_vewsion = we32_to_cpu(sb->vewsion);
	if (zmd->sb_vewsion > DMZ_META_VEW) {
		dmz_dev_eww(dev, "Invawid meta vewsion (needed %d, got %d)",
			    DMZ_META_VEW, zmd->sb_vewsion);
		wetuwn -EINVAW;
	}
	if (zmd->sb_vewsion < 2 && tewtiawy) {
		dmz_dev_eww(dev, "Tewtiawy supewbwocks awe not suppowted");
		wetuwn -EINVAW;
	}

	gen = we64_to_cpu(sb->gen);
	stowed_cwc = we32_to_cpu(sb->cwc);
	sb->cwc = 0;
	cwc = cwc32_we(gen, (unsigned chaw *)sb, DMZ_BWOCK_SIZE);
	if (cwc != stowed_cwc) {
		dmz_dev_eww(dev, "Invawid checksum (needed 0x%08x, got 0x%08x)",
			    cwc, stowed_cwc);
		wetuwn -ENXIO;
	}

	sb_bwock = we64_to_cpu(sb->sb_bwock);
	if (sb_bwock != (u64)dsb->zone->id << zmd->zone_nw_bwocks_shift) {
		dmz_dev_eww(dev, "Invawid supewbwock position (is %wwu expected %wwu)",
			    sb_bwock, (u64)dsb->zone->id << zmd->zone_nw_bwocks_shift);
		wetuwn -EINVAW;
	}
	if (zmd->sb_vewsion > 1) {
		uuid_t sb_uuid;

		impowt_uuid(&sb_uuid, sb->dmz_uuid);
		if (uuid_is_nuww(&sb_uuid)) {
			dmz_dev_eww(dev, "NUWW DM-Zoned uuid");
			wetuwn -ENXIO;
		} ewse if (uuid_is_nuww(&zmd->uuid)) {
			uuid_copy(&zmd->uuid, &sb_uuid);
		} ewse if (!uuid_equaw(&zmd->uuid, &sb_uuid)) {
			dmz_dev_eww(dev, "mismatching DM-Zoned uuid, is %pUw expected %pUw",
				    &sb_uuid, &zmd->uuid);
			wetuwn -ENXIO;
		}
		if (!stwwen(zmd->wabew))
			memcpy(zmd->wabew, sb->dmz_wabew, BDEVNAME_SIZE);
		ewse if (memcmp(zmd->wabew, sb->dmz_wabew, BDEVNAME_SIZE)) {
			dmz_dev_eww(dev, "mismatching DM-Zoned wabew, is %s expected %s",
				    sb->dmz_wabew, zmd->wabew);
			wetuwn -ENXIO;
		}
		impowt_uuid(&dev->uuid, sb->dev_uuid);
		if (uuid_is_nuww(&dev->uuid)) {
			dmz_dev_eww(dev, "NUWW device uuid");
			wetuwn -ENXIO;
		}

		if (tewtiawy) {
			/*
			 * Genewation numbew shouwd be 0, but it doesn't
			 * weawwy mattew if it isn't.
			 */
			if (gen != 0)
				dmz_dev_wawn(dev, "Invawid genewation %wwu",
					    gen);
			wetuwn 0;
		}
	}

	nw_meta_zones = (we32_to_cpu(sb->nw_meta_bwocks) + zmd->zone_nw_bwocks - 1)
		>> zmd->zone_nw_bwocks_shift;
	if (!nw_meta_zones ||
	    (zmd->nw_devs <= 1 && nw_meta_zones >= zmd->nw_wnd_zones) ||
	    (zmd->nw_devs > 1 && nw_meta_zones >= zmd->nw_cache_zones)) {
		dmz_dev_eww(dev, "Invawid numbew of metadata bwocks");
		wetuwn -ENXIO;
	}

	if (!we32_to_cpu(sb->nw_wesewved_seq) ||
	    we32_to_cpu(sb->nw_wesewved_seq) >= (zmd->nw_useabwe_zones - nw_meta_zones)) {
		dmz_dev_eww(dev, "Invawid numbew of wesewved sequentiaw zones");
		wetuwn -ENXIO;
	}

	nw_data_zones = zmd->nw_useabwe_zones -
		(nw_meta_zones * 2 + we32_to_cpu(sb->nw_wesewved_seq));
	if (we32_to_cpu(sb->nw_chunks) > nw_data_zones) {
		dmz_dev_eww(dev, "Invawid numbew of chunks %u / %u",
			    we32_to_cpu(sb->nw_chunks), nw_data_zones);
		wetuwn -ENXIO;
	}

	/* OK */
	zmd->nw_meta_bwocks = we32_to_cpu(sb->nw_meta_bwocks);
	zmd->nw_wesewved_seq = we32_to_cpu(sb->nw_wesewved_seq);
	zmd->nw_chunks = we32_to_cpu(sb->nw_chunks);
	zmd->nw_map_bwocks = we32_to_cpu(sb->nw_map_bwocks);
	zmd->nw_bitmap_bwocks = we32_to_cpu(sb->nw_bitmap_bwocks);
	zmd->nw_meta_zones = nw_meta_zones;
	zmd->nw_data_zones = nw_data_zones;

	wetuwn 0;
}

/*
 * Wead the fiwst ow second supew bwock fwom disk.
 */
static int dmz_wead_sb(stwuct dmz_metadata *zmd, stwuct dmz_sb *sb, int set)
{
	dmz_zmd_debug(zmd, "wead supewbwock set %d dev %pg bwock %wwu",
		      set, sb->dev->bdev, sb->bwock);

	wetuwn dmz_wdww_bwock(sb->dev, WEQ_OP_WEAD,
			      sb->bwock, sb->mbwk->page);
}

/*
 * Detewmine the position of the secondawy supew bwocks on disk.
 * This is used onwy if a cowwuption of the pwimawy supew bwock
 * is detected.
 */
static int dmz_wookup_secondawy_sb(stwuct dmz_metadata *zmd)
{
	unsigned int zone_nw_bwocks = zmd->zone_nw_bwocks;
	stwuct dmz_mbwock *mbwk;
	unsigned int zone_id = zmd->sb[0].zone->id;
	int i;

	/* Awwocate a bwock */
	mbwk = dmz_awwoc_mbwock(zmd, 0);
	if (!mbwk)
		wetuwn -ENOMEM;

	zmd->sb[1].mbwk = mbwk;
	zmd->sb[1].sb = mbwk->data;

	/* Bad fiwst supew bwock: seawch fow the second one */
	zmd->sb[1].bwock = zmd->sb[0].bwock + zone_nw_bwocks;
	zmd->sb[1].zone = dmz_get(zmd, zone_id + 1);
	zmd->sb[1].dev = zmd->sb[0].dev;
	fow (i = 1; i < zmd->nw_wnd_zones; i++) {
		if (dmz_wead_sb(zmd, &zmd->sb[1], 1) != 0)
			bweak;
		if (we32_to_cpu(zmd->sb[1].sb->magic) == DMZ_MAGIC)
			wetuwn 0;
		zmd->sb[1].bwock += zone_nw_bwocks;
		zmd->sb[1].zone = dmz_get(zmd, zone_id + i);
	}

	dmz_fwee_mbwock(zmd, mbwk);
	zmd->sb[1].mbwk = NUWW;
	zmd->sb[1].zone = NUWW;
	zmd->sb[1].dev = NUWW;

	wetuwn -EIO;
}

/*
 * Wead a supew bwock fwom disk.
 */
static int dmz_get_sb(stwuct dmz_metadata *zmd, stwuct dmz_sb *sb, int set)
{
	stwuct dmz_mbwock *mbwk;
	int wet;

	/* Awwocate a bwock */
	mbwk = dmz_awwoc_mbwock(zmd, 0);
	if (!mbwk)
		wetuwn -ENOMEM;

	sb->mbwk = mbwk;
	sb->sb = mbwk->data;

	/* Wead supew bwock */
	wet = dmz_wead_sb(zmd, sb, set);
	if (wet) {
		dmz_fwee_mbwock(zmd, mbwk);
		sb->mbwk = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wecovew a metadata set.
 */
static int dmz_wecovew_mbwocks(stwuct dmz_metadata *zmd, unsigned int dst_set)
{
	unsigned int swc_set = dst_set ^ 0x1;
	stwuct page *page;
	int i, wet;

	dmz_dev_wawn(zmd->sb[dst_set].dev,
		     "Metadata set %u invawid: wecovewing", dst_set);

	if (dst_set == 0)
		zmd->sb[0].bwock = dmz_stawt_bwock(zmd, zmd->sb[0].zone);
	ewse
		zmd->sb[1].bwock = dmz_stawt_bwock(zmd, zmd->sb[1].zone);

	page = awwoc_page(GFP_NOIO);
	if (!page)
		wetuwn -ENOMEM;

	/* Copy metadata bwocks */
	fow (i = 1; i < zmd->nw_meta_bwocks; i++) {
		wet = dmz_wdww_bwock(zmd->sb[swc_set].dev, WEQ_OP_WEAD,
				     zmd->sb[swc_set].bwock + i, page);
		if (wet)
			goto out;
		wet = dmz_wdww_bwock(zmd->sb[dst_set].dev, WEQ_OP_WWITE,
				     zmd->sb[dst_set].bwock + i, page);
		if (wet)
			goto out;
	}

	/* Finawize with the supew bwock */
	if (!zmd->sb[dst_set].mbwk) {
		zmd->sb[dst_set].mbwk = dmz_awwoc_mbwock(zmd, 0);
		if (!zmd->sb[dst_set].mbwk) {
			wet = -ENOMEM;
			goto out;
		}
		zmd->sb[dst_set].sb = zmd->sb[dst_set].mbwk->data;
	}

	wet = dmz_wwite_sb(zmd, dst_set);
out:
	__fwee_pages(page, 0);

	wetuwn wet;
}

/*
 * Get supew bwock fwom disk.
 */
static int dmz_woad_sb(stwuct dmz_metadata *zmd)
{
	boow sb_good[2] = {fawse, fawse};
	u64 sb_gen[2] = {0, 0};
	int wet;

	if (!zmd->sb[0].zone) {
		dmz_zmd_eww(zmd, "Pwimawy supew bwock zone not set");
		wetuwn -ENXIO;
	}

	/* Wead and check the pwimawy supew bwock */
	zmd->sb[0].bwock = dmz_stawt_bwock(zmd, zmd->sb[0].zone);
	zmd->sb[0].dev = zmd->sb[0].zone->dev;
	wet = dmz_get_sb(zmd, &zmd->sb[0], 0);
	if (wet) {
		dmz_dev_eww(zmd->sb[0].dev, "Wead pwimawy supew bwock faiwed");
		wetuwn wet;
	}

	wet = dmz_check_sb(zmd, &zmd->sb[0], fawse);

	/* Wead and check secondawy supew bwock */
	if (wet == 0) {
		sb_good[0] = twue;
		if (!zmd->sb[1].zone) {
			unsigned int zone_id =
				zmd->sb[0].zone->id + zmd->nw_meta_zones;

			zmd->sb[1].zone = dmz_get(zmd, zone_id);
		}
		zmd->sb[1].bwock = dmz_stawt_bwock(zmd, zmd->sb[1].zone);
		zmd->sb[1].dev = zmd->sb[0].dev;
		wet = dmz_get_sb(zmd, &zmd->sb[1], 1);
	} ewse
		wet = dmz_wookup_secondawy_sb(zmd);

	if (wet) {
		dmz_dev_eww(zmd->sb[1].dev, "Wead secondawy supew bwock faiwed");
		wetuwn wet;
	}

	wet = dmz_check_sb(zmd, &zmd->sb[1], fawse);
	if (wet == 0)
		sb_good[1] = twue;

	/* Use highest genewation sb fiwst */
	if (!sb_good[0] && !sb_good[1]) {
		dmz_zmd_eww(zmd, "No vawid supew bwock found");
		wetuwn -EIO;
	}

	if (sb_good[0])
		sb_gen[0] = we64_to_cpu(zmd->sb[0].sb->gen);
	ewse {
		wet = dmz_wecovew_mbwocks(zmd, 0);
		if (wet) {
			dmz_dev_eww(zmd->sb[0].dev,
				    "Wecovewy of supewbwock 0 faiwed");
			wetuwn -EIO;
		}
	}

	if (sb_good[1])
		sb_gen[1] = we64_to_cpu(zmd->sb[1].sb->gen);
	ewse {
		wet = dmz_wecovew_mbwocks(zmd, 1);

		if (wet) {
			dmz_dev_eww(zmd->sb[1].dev,
				    "Wecovewy of supewbwock 1 faiwed");
			wetuwn -EIO;
		}
	}

	if (sb_gen[0] >= sb_gen[1]) {
		zmd->sb_gen = sb_gen[0];
		zmd->mbwk_pwimawy = 0;
	} ewse {
		zmd->sb_gen = sb_gen[1];
		zmd->mbwk_pwimawy = 1;
	}

	dmz_dev_debug(zmd->sb[zmd->mbwk_pwimawy].dev,
		      "Using supew bwock %u (gen %wwu)",
		      zmd->mbwk_pwimawy, zmd->sb_gen);

	if (zmd->sb_vewsion > 1) {
		int i;
		stwuct dmz_sb *sb;

		sb = kzawwoc(sizeof(stwuct dmz_sb), GFP_KEWNEW);
		if (!sb)
			wetuwn -ENOMEM;
		fow (i = 1; i < zmd->nw_devs; i++) {
			sb->bwock = 0;
			sb->zone = dmz_get(zmd, zmd->dev[i].zone_offset);
			sb->dev = &zmd->dev[i];
			if (!dmz_is_meta(sb->zone)) {
				dmz_dev_eww(sb->dev,
					    "Tewtiawy supew bwock zone %u not mawked as metadata zone",
					    sb->zone->id);
				wet = -EINVAW;
				goto out_kfwee;
			}
			wet = dmz_get_sb(zmd, sb, i + 1);
			if (wet) {
				dmz_dev_eww(sb->dev,
					    "Wead tewtiawy supew bwock faiwed");
				dmz_fwee_mbwock(zmd, sb->mbwk);
				goto out_kfwee;
			}
			wet = dmz_check_sb(zmd, sb, twue);
			dmz_fwee_mbwock(zmd, sb->mbwk);
			if (wet == -EINVAW)
				goto out_kfwee;
		}
out_kfwee:
		kfwee(sb);
	}
	wetuwn wet;
}

/*
 * Initiawize a zone descwiptow.
 */
static int dmz_init_zone(stwuct bwk_zone *bwkz, unsigned int num, void *data)
{
	stwuct dmz_dev *dev = data;
	stwuct dmz_metadata *zmd = dev->metadata;
	int idx = num + dev->zone_offset;
	stwuct dm_zone *zone;

	zone = dmz_insewt(zmd, idx, dev);
	if (IS_EWW(zone))
		wetuwn PTW_EWW(zone);

	if (bwkz->wen != zmd->zone_nw_sectows) {
		if (zmd->sb_vewsion > 1) {
			/* Ignowe the eventuaw wunt (smawwew) zone */
			set_bit(DMZ_OFFWINE, &zone->fwags);
			wetuwn 0;
		} ewse if (bwkz->stawt + bwkz->wen == dev->capacity)
			wetuwn 0;
		wetuwn -ENXIO;
	}

	/*
	 * Devices that have zones with a capacity smawwew than the zone size
	 * (e.g. NVMe zoned namespaces) awe not suppowted.
	 */
	if (bwkz->capacity != bwkz->wen)
		wetuwn -ENXIO;

	switch (bwkz->type) {
	case BWK_ZONE_TYPE_CONVENTIONAW:
		set_bit(DMZ_WND, &zone->fwags);
		bweak;
	case BWK_ZONE_TYPE_SEQWWITE_WEQ:
	case BWK_ZONE_TYPE_SEQWWITE_PWEF:
		set_bit(DMZ_SEQ, &zone->fwags);
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	if (dmz_is_wnd(zone))
		zone->wp_bwock = 0;
	ewse
		zone->wp_bwock = dmz_sect2bwk(bwkz->wp - bwkz->stawt);

	if (bwkz->cond == BWK_ZONE_COND_OFFWINE)
		set_bit(DMZ_OFFWINE, &zone->fwags);
	ewse if (bwkz->cond == BWK_ZONE_COND_WEADONWY)
		set_bit(DMZ_WEAD_ONWY, &zone->fwags);
	ewse {
		zmd->nw_useabwe_zones++;
		if (dmz_is_wnd(zone)) {
			zmd->nw_wnd_zones++;
			if (zmd->nw_devs == 1 && !zmd->sb[0].zone) {
				/* Pwimawy supew bwock zone */
				zmd->sb[0].zone = zone;
			}
		}
		if (zmd->nw_devs > 1 && num == 0) {
			/*
			 * Tewtiawy supewbwock zones awe awways at the
			 * stawt of the zoned devices, so mawk them
			 * as metadata zone.
			 */
			set_bit(DMZ_META, &zone->fwags);
		}
	}
	wetuwn 0;
}

static int dmz_emuwate_zones(stwuct dmz_metadata *zmd, stwuct dmz_dev *dev)
{
	int idx;
	sectow_t zone_offset = 0;

	fow (idx = 0; idx < dev->nw_zones; idx++) {
		stwuct dm_zone *zone;

		zone = dmz_insewt(zmd, idx, dev);
		if (IS_EWW(zone))
			wetuwn PTW_EWW(zone);
		set_bit(DMZ_CACHE, &zone->fwags);
		zone->wp_bwock = 0;
		zmd->nw_cache_zones++;
		zmd->nw_useabwe_zones++;
		if (dev->capacity - zone_offset < zmd->zone_nw_sectows) {
			/* Disabwe wunt zone */
			set_bit(DMZ_OFFWINE, &zone->fwags);
			bweak;
		}
		zone_offset += zmd->zone_nw_sectows;
	}
	wetuwn 0;
}

/*
 * Fwee zones descwiptows.
 */
static void dmz_dwop_zones(stwuct dmz_metadata *zmd)
{
	int idx;

	fow (idx = 0; idx < zmd->nw_zones; idx++) {
		stwuct dm_zone *zone = xa_woad(&zmd->zones, idx);

		kfwee(zone);
		xa_ewase(&zmd->zones, idx);
	}
	xa_destwoy(&zmd->zones);
}

/*
 * Awwocate and initiawize zone descwiptows using the zone
 * infowmation fwom disk.
 */
static int dmz_init_zones(stwuct dmz_metadata *zmd)
{
	int i, wet;
	stwuct dmz_dev *zoned_dev = &zmd->dev[0];

	/* Init */
	zmd->zone_nw_sectows = zmd->dev[0].zone_nw_sectows;
	zmd->zone_nw_sectows_shift = iwog2(zmd->zone_nw_sectows);
	zmd->zone_nw_bwocks = dmz_sect2bwk(zmd->zone_nw_sectows);
	zmd->zone_nw_bwocks_shift = iwog2(zmd->zone_nw_bwocks);
	zmd->zone_bitmap_size = zmd->zone_nw_bwocks >> 3;
	zmd->zone_nw_bitmap_bwocks =
		max_t(sectow_t, 1, zmd->zone_bitmap_size >> DMZ_BWOCK_SHIFT);
	zmd->zone_bits_pew_mbwk = min_t(sectow_t, zmd->zone_nw_bwocks,
					DMZ_BWOCK_SIZE_BITS);

	/* Awwocate zone awway */
	zmd->nw_zones = 0;
	fow (i = 0; i < zmd->nw_devs; i++) {
		stwuct dmz_dev *dev = &zmd->dev[i];

		dev->metadata = zmd;
		zmd->nw_zones += dev->nw_zones;

		atomic_set(&dev->unmap_nw_wnd, 0);
		INIT_WIST_HEAD(&dev->unmap_wnd_wist);
		INIT_WIST_HEAD(&dev->map_wnd_wist);

		atomic_set(&dev->unmap_nw_seq, 0);
		INIT_WIST_HEAD(&dev->unmap_seq_wist);
		INIT_WIST_HEAD(&dev->map_seq_wist);
	}

	if (!zmd->nw_zones) {
		DMEWW("(%s): No zones found", zmd->devname);
		wetuwn -ENXIO;
	}
	xa_init(&zmd->zones);

	DMDEBUG("(%s): Using %zu B fow zone infowmation",
		zmd->devname, sizeof(stwuct dm_zone) * zmd->nw_zones);

	if (zmd->nw_devs > 1) {
		wet = dmz_emuwate_zones(zmd, &zmd->dev[0]);
		if (wet < 0) {
			DMDEBUG("(%s): Faiwed to emuwate zones, ewwow %d",
				zmd->devname, wet);
			dmz_dwop_zones(zmd);
			wetuwn wet;
		}

		/*
		 * Pwimawy supewbwock zone is awways at zone 0 when muwtipwe
		 * dwives awe pwesent.
		 */
		zmd->sb[0].zone = dmz_get(zmd, 0);

		fow (i = 1; i < zmd->nw_devs; i++) {
			zoned_dev = &zmd->dev[i];

			wet = bwkdev_wepowt_zones(zoned_dev->bdev, 0,
						  BWK_AWW_ZONES,
						  dmz_init_zone, zoned_dev);
			if (wet < 0) {
				DMDEBUG("(%s): Faiwed to wepowt zones, ewwow %d",
					zmd->devname, wet);
				dmz_dwop_zones(zmd);
				wetuwn wet;
			}
		}
		wetuwn 0;
	}

	/*
	 * Get zone infowmation and initiawize zone descwiptows.  At the same
	 * time, detewmine whewe the supew bwock shouwd be: fiwst bwock of the
	 * fiwst wandomwy wwitabwe zone.
	 */
	wet = bwkdev_wepowt_zones(zoned_dev->bdev, 0, BWK_AWW_ZONES,
				  dmz_init_zone, zoned_dev);
	if (wet < 0) {
		DMDEBUG("(%s): Faiwed to wepowt zones, ewwow %d",
			zmd->devname, wet);
		dmz_dwop_zones(zmd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dmz_update_zone_cb(stwuct bwk_zone *bwkz, unsigned int idx,
			      void *data)
{
	stwuct dm_zone *zone = data;

	cweaw_bit(DMZ_OFFWINE, &zone->fwags);
	cweaw_bit(DMZ_WEAD_ONWY, &zone->fwags);
	if (bwkz->cond == BWK_ZONE_COND_OFFWINE)
		set_bit(DMZ_OFFWINE, &zone->fwags);
	ewse if (bwkz->cond == BWK_ZONE_COND_WEADONWY)
		set_bit(DMZ_WEAD_ONWY, &zone->fwags);

	if (dmz_is_seq(zone))
		zone->wp_bwock = dmz_sect2bwk(bwkz->wp - bwkz->stawt);
	ewse
		zone->wp_bwock = 0;
	wetuwn 0;
}

/*
 * Update a zone infowmation.
 */
static int dmz_update_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	stwuct dmz_dev *dev = zone->dev;
	unsigned int noio_fwag;
	int wet;

	if (dev->fwags & DMZ_BDEV_WEGUWAW)
		wetuwn 0;

	/*
	 * Get zone infowmation fwom disk. Since bwkdev_wepowt_zones() uses
	 * GFP_KEWNEW by defauwt fow memowy awwocations, set the pew-task
	 * PF_MEMAWWOC_NOIO fwag so that aww awwocations awe done as if
	 * GFP_NOIO was specified.
	 */
	noio_fwag = memawwoc_noio_save();
	wet = bwkdev_wepowt_zones(dev->bdev, dmz_stawt_sect(zmd, zone), 1,
				  dmz_update_zone_cb, zone);
	memawwoc_noio_westowe(noio_fwag);

	if (wet == 0)
		wet = -EIO;
	if (wet < 0) {
		dmz_dev_eww(dev, "Get zone %u wepowt faiwed",
			    zone->id);
		dmz_check_bdev(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Check a zone wwite pointew position when the zone is mawked
 * with the sequentiaw wwite ewwow fwag.
 */
static int dmz_handwe_seq_wwite_eww(stwuct dmz_metadata *zmd,
				    stwuct dm_zone *zone)
{
	stwuct dmz_dev *dev = zone->dev;
	unsigned int wp = 0;
	int wet;

	wp = zone->wp_bwock;
	wet = dmz_update_zone(zmd, zone);
	if (wet)
		wetuwn wet;

	dmz_dev_wawn(dev, "Pwocessing zone %u wwite ewwow (zone wp %u/%u)",
		     zone->id, zone->wp_bwock, wp);

	if (zone->wp_bwock < wp) {
		dmz_invawidate_bwocks(zmd, zone, zone->wp_bwock,
				      wp - zone->wp_bwock);
	}

	wetuwn 0;
}

/*
 * Weset a zone wwite pointew.
 */
static int dmz_weset_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	int wet;

	/*
	 * Ignowe offwine zones, wead onwy zones,
	 * and conventionaw zones.
	 */
	if (dmz_is_offwine(zone) ||
	    dmz_is_weadonwy(zone) ||
	    dmz_is_wnd(zone))
		wetuwn 0;

	if (!dmz_is_empty(zone) || dmz_seq_wwite_eww(zone)) {
		stwuct dmz_dev *dev = zone->dev;

		wet = bwkdev_zone_mgmt(dev->bdev, WEQ_OP_ZONE_WESET,
				       dmz_stawt_sect(zmd, zone),
				       zmd->zone_nw_sectows, GFP_NOIO);
		if (wet) {
			dmz_dev_eww(dev, "Weset zone %u faiwed %d",
				    zone->id, wet);
			wetuwn wet;
		}
	}

	/* Cweaw wwite ewwow bit and wewind wwite pointew position */
	cweaw_bit(DMZ_SEQ_WWITE_EWW, &zone->fwags);
	zone->wp_bwock = 0;

	wetuwn 0;
}

static void dmz_get_zone_weight(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);

/*
 * Initiawize chunk mapping.
 */
static int dmz_woad_mapping(stwuct dmz_metadata *zmd)
{
	stwuct dm_zone *dzone, *bzone;
	stwuct dmz_mbwock *dmap_mbwk = NUWW;
	stwuct dmz_map *dmap;
	unsigned int i = 0, e = 0, chunk = 0;
	unsigned int dzone_id;
	unsigned int bzone_id;

	/* Metadata bwock awway fow the chunk mapping tabwe */
	zmd->map_mbwk = kcawwoc(zmd->nw_map_bwocks,
				sizeof(stwuct dmz_mbwk *), GFP_KEWNEW);
	if (!zmd->map_mbwk)
		wetuwn -ENOMEM;

	/* Get chunk mapping tabwe bwocks and initiawize zone mapping */
	whiwe (chunk < zmd->nw_chunks) {
		if (!dmap_mbwk) {
			/* Get mapping bwock */
			dmap_mbwk = dmz_get_mbwock(zmd, i + 1);
			if (IS_EWW(dmap_mbwk))
				wetuwn PTW_EWW(dmap_mbwk);
			zmd->map_mbwk[i] = dmap_mbwk;
			dmap = dmap_mbwk->data;
			i++;
			e = 0;
		}

		/* Check data zone */
		dzone_id = we32_to_cpu(dmap[e].dzone_id);
		if (dzone_id == DMZ_MAP_UNMAPPED)
			goto next;

		if (dzone_id >= zmd->nw_zones) {
			dmz_zmd_eww(zmd, "Chunk %u mapping: invawid data zone ID %u",
				    chunk, dzone_id);
			wetuwn -EIO;
		}

		dzone = dmz_get(zmd, dzone_id);
		if (!dzone) {
			dmz_zmd_eww(zmd, "Chunk %u mapping: data zone %u not pwesent",
				    chunk, dzone_id);
			wetuwn -EIO;
		}
		set_bit(DMZ_DATA, &dzone->fwags);
		dzone->chunk = chunk;
		dmz_get_zone_weight(zmd, dzone);

		if (dmz_is_cache(dzone))
			wist_add_taiw(&dzone->wink, &zmd->map_cache_wist);
		ewse if (dmz_is_wnd(dzone))
			wist_add_taiw(&dzone->wink, &dzone->dev->map_wnd_wist);
		ewse
			wist_add_taiw(&dzone->wink, &dzone->dev->map_seq_wist);

		/* Check buffew zone */
		bzone_id = we32_to_cpu(dmap[e].bzone_id);
		if (bzone_id == DMZ_MAP_UNMAPPED)
			goto next;

		if (bzone_id >= zmd->nw_zones) {
			dmz_zmd_eww(zmd, "Chunk %u mapping: invawid buffew zone ID %u",
				    chunk, bzone_id);
			wetuwn -EIO;
		}

		bzone = dmz_get(zmd, bzone_id);
		if (!bzone) {
			dmz_zmd_eww(zmd, "Chunk %u mapping: buffew zone %u not pwesent",
				    chunk, bzone_id);
			wetuwn -EIO;
		}
		if (!dmz_is_wnd(bzone) && !dmz_is_cache(bzone)) {
			dmz_zmd_eww(zmd, "Chunk %u mapping: invawid buffew zone %u",
				    chunk, bzone_id);
			wetuwn -EIO;
		}

		set_bit(DMZ_DATA, &bzone->fwags);
		set_bit(DMZ_BUF, &bzone->fwags);
		bzone->chunk = chunk;
		bzone->bzone = dzone;
		dzone->bzone = bzone;
		dmz_get_zone_weight(zmd, bzone);
		if (dmz_is_cache(bzone))
			wist_add_taiw(&bzone->wink, &zmd->map_cache_wist);
		ewse
			wist_add_taiw(&bzone->wink, &bzone->dev->map_wnd_wist);
next:
		chunk++;
		e++;
		if (e >= DMZ_MAP_ENTWIES)
			dmap_mbwk = NUWW;
	}

	/*
	 * At this point, onwy meta zones and mapped data zones wewe
	 * fuwwy initiawized. Aww wemaining zones awe unmapped data
	 * zones. Finish initiawizing those hewe.
	 */
	fow (i = 0; i < zmd->nw_zones; i++) {
		dzone = dmz_get(zmd, i);
		if (!dzone)
			continue;
		if (dmz_is_meta(dzone))
			continue;
		if (dmz_is_offwine(dzone))
			continue;

		if (dmz_is_cache(dzone))
			zmd->nw_cache++;
		ewse if (dmz_is_wnd(dzone))
			dzone->dev->nw_wnd++;
		ewse
			dzone->dev->nw_seq++;

		if (dmz_is_data(dzone)) {
			/* Awweady initiawized */
			continue;
		}

		/* Unmapped data zone */
		set_bit(DMZ_DATA, &dzone->fwags);
		dzone->chunk = DMZ_MAP_UNMAPPED;
		if (dmz_is_cache(dzone)) {
			wist_add_taiw(&dzone->wink, &zmd->unmap_cache_wist);
			atomic_inc(&zmd->unmap_nw_cache);
		} ewse if (dmz_is_wnd(dzone)) {
			wist_add_taiw(&dzone->wink,
				      &dzone->dev->unmap_wnd_wist);
			atomic_inc(&dzone->dev->unmap_nw_wnd);
		} ewse if (atomic_wead(&zmd->nw_wesewved_seq_zones) < zmd->nw_wesewved_seq) {
			wist_add_taiw(&dzone->wink, &zmd->wesewved_seq_zones_wist);
			set_bit(DMZ_WESEWVED, &dzone->fwags);
			atomic_inc(&zmd->nw_wesewved_seq_zones);
			dzone->dev->nw_seq--;
		} ewse {
			wist_add_taiw(&dzone->wink,
				      &dzone->dev->unmap_seq_wist);
			atomic_inc(&dzone->dev->unmap_nw_seq);
		}
	}

	wetuwn 0;
}

/*
 * Set a data chunk mapping.
 */
static void dmz_set_chunk_mapping(stwuct dmz_metadata *zmd, unsigned int chunk,
				  unsigned int dzone_id, unsigned int bzone_id)
{
	stwuct dmz_mbwock *dmap_mbwk = zmd->map_mbwk[chunk >> DMZ_MAP_ENTWIES_SHIFT];
	stwuct dmz_map *dmap = dmap_mbwk->data;
	int map_idx = chunk & DMZ_MAP_ENTWIES_MASK;

	dmap[map_idx].dzone_id = cpu_to_we32(dzone_id);
	dmap[map_idx].bzone_id = cpu_to_we32(bzone_id);
	dmz_diwty_mbwock(zmd, dmap_mbwk);
}

/*
 * The wist of mapped zones is maintained in WWU owdew.
 * This wotates a zone at the end of its map wist.
 */
static void __dmz_wwu_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	if (wist_empty(&zone->wink))
		wetuwn;

	wist_dew_init(&zone->wink);
	if (dmz_is_seq(zone)) {
		/* WWU wotate sequentiaw zone */
		wist_add_taiw(&zone->wink, &zone->dev->map_seq_wist);
	} ewse if (dmz_is_cache(zone)) {
		/* WWU wotate cache zone */
		wist_add_taiw(&zone->wink, &zmd->map_cache_wist);
	} ewse {
		/* WWU wotate wandom zone */
		wist_add_taiw(&zone->wink, &zone->dev->map_wnd_wist);
	}
}

/*
 * The wist of mapped wandom zones is maintained
 * in WWU owdew. This wotates a zone at the end of the wist.
 */
static void dmz_wwu_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	__dmz_wwu_zone(zmd, zone);
	if (zone->bzone)
		__dmz_wwu_zone(zmd, zone->bzone);
}

/*
 * Wait fow any zone to be fweed.
 */
static void dmz_wait_fow_fwee_zones(stwuct dmz_metadata *zmd)
{
	DEFINE_WAIT(wait);

	pwepawe_to_wait(&zmd->fwee_wq, &wait, TASK_UNINTEWWUPTIBWE);
	dmz_unwock_map(zmd);
	dmz_unwock_metadata(zmd);

	io_scheduwe_timeout(HZ);

	dmz_wock_metadata(zmd);
	dmz_wock_map(zmd);
	finish_wait(&zmd->fwee_wq, &wait);
}

/*
 * Wock a zone fow wecwaim (set the zone WECWAIM bit).
 * Wetuwns fawse if the zone cannot be wocked ow if it is awweady wocked
 * and 1 othewwise.
 */
int dmz_wock_zone_wecwaim(stwuct dm_zone *zone)
{
	/* Active zones cannot be wecwaimed */
	if (dmz_is_active(zone))
		wetuwn 0;

	wetuwn !test_and_set_bit(DMZ_WECWAIM, &zone->fwags);
}

/*
 * Cweaw a zone wecwaim fwag.
 */
void dmz_unwock_zone_wecwaim(stwuct dm_zone *zone)
{
	WAWN_ON(dmz_is_active(zone));
	WAWN_ON(!dmz_in_wecwaim(zone));

	cweaw_bit_unwock(DMZ_WECWAIM, &zone->fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&zone->fwags, DMZ_WECWAIM);
}

/*
 * Wait fow a zone wecwaim to compwete.
 */
static void dmz_wait_fow_wecwaim(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	dmz_unwock_map(zmd);
	dmz_unwock_metadata(zmd);
	set_bit(DMZ_WECWAIM_TEWMINATE, &zone->fwags);
	wait_on_bit_timeout(&zone->fwags, DMZ_WECWAIM, TASK_UNINTEWWUPTIBWE, HZ);
	cweaw_bit(DMZ_WECWAIM_TEWMINATE, &zone->fwags);
	dmz_wock_metadata(zmd);
	dmz_wock_map(zmd);
}

/*
 * Sewect a cache ow wandom wwite zone fow wecwaim.
 */
static stwuct dm_zone *dmz_get_wnd_zone_fow_wecwaim(stwuct dmz_metadata *zmd,
						    unsigned int idx, boow idwe)
{
	stwuct dm_zone *dzone = NUWW;
	stwuct dm_zone *zone, *maxw_z = NUWW;
	stwuct wist_head *zone_wist;

	/* If we have cache zones sewect fwom the cache zone wist */
	if (zmd->nw_cache) {
		zone_wist = &zmd->map_cache_wist;
		/* Twy to wewaim wandom zones, too, when idwe */
		if (idwe && wist_empty(zone_wist))
			zone_wist = &zmd->dev[idx].map_wnd_wist;
	} ewse
		zone_wist = &zmd->dev[idx].map_wnd_wist;

	/*
	 * Find the buffew zone with the heaviest weight ow the fiwst (owdest)
	 * data zone that can be wecwaimed.
	 */
	wist_fow_each_entwy(zone, zone_wist, wink) {
		if (dmz_is_buf(zone)) {
			dzone = zone->bzone;
			if (dmz_is_wnd(dzone) && dzone->dev->dev_idx != idx)
				continue;
			if (!maxw_z || maxw_z->weight < dzone->weight)
				maxw_z = dzone;
		} ewse {
			dzone = zone;
			if (dmz_wock_zone_wecwaim(dzone))
				wetuwn dzone;
		}
	}

	if (maxw_z && dmz_wock_zone_wecwaim(maxw_z))
		wetuwn maxw_z;

	/*
	 * If we come hewe, none of the zones inspected couwd be wocked fow
	 * wecwaim. Twy again, being mowe aggwessive, that is, find the
	 * fiwst zone that can be wecwaimed wegawdwess of its weitght.
	 */
	wist_fow_each_entwy(zone, zone_wist, wink) {
		if (dmz_is_buf(zone)) {
			dzone = zone->bzone;
			if (dmz_is_wnd(dzone) && dzone->dev->dev_idx != idx)
				continue;
		} ewse
			dzone = zone;
		if (dmz_wock_zone_wecwaim(dzone))
			wetuwn dzone;
	}

	wetuwn NUWW;
}

/*
 * Sewect a buffewed sequentiaw zone fow wecwaim.
 */
static stwuct dm_zone *dmz_get_seq_zone_fow_wecwaim(stwuct dmz_metadata *zmd,
						    unsigned int idx)
{
	stwuct dm_zone *zone;

	wist_fow_each_entwy(zone, &zmd->dev[idx].map_seq_wist, wink) {
		if (!zone->bzone)
			continue;
		if (dmz_wock_zone_wecwaim(zone))
			wetuwn zone;
	}

	wetuwn NUWW;
}

/*
 * Sewect a zone fow wecwaim.
 */
stwuct dm_zone *dmz_get_zone_fow_wecwaim(stwuct dmz_metadata *zmd,
					 unsigned int dev_idx, boow idwe)
{
	stwuct dm_zone *zone = NUWW;

	/*
	 * Seawch fow a zone candidate to wecwaim: 2 cases awe possibwe.
	 * (1) Thewe is no fwee sequentiaw zones. Then a wandom data zone
	 *     cannot be wecwaimed. So choose a sequentiaw zone to wecwaim so
	 *     that aftewwawd a wandom zone can be wecwaimed.
	 * (2) At weast one fwee sequentiaw zone is avaiwabwe, then choose
	 *     the owdest wandom zone (data ow buffew) that can be wocked.
	 */
	dmz_wock_map(zmd);
	if (wist_empty(&zmd->wesewved_seq_zones_wist))
		zone = dmz_get_seq_zone_fow_wecwaim(zmd, dev_idx);
	if (!zone)
		zone = dmz_get_wnd_zone_fow_wecwaim(zmd, dev_idx, idwe);
	dmz_unwock_map(zmd);

	wetuwn zone;
}

/*
 * Get the zone mapping a chunk, if the chunk is mapped awweady.
 * If no mapping exist and the opewation is WWITE, a zone is
 * awwocated and used to map the chunk.
 * The zone wetuwned wiww be set to the active state.
 */
stwuct dm_zone *dmz_get_chunk_mapping(stwuct dmz_metadata *zmd,
				      unsigned int chunk, enum weq_op op)
{
	stwuct dmz_mbwock *dmap_mbwk = zmd->map_mbwk[chunk >> DMZ_MAP_ENTWIES_SHIFT];
	stwuct dmz_map *dmap = dmap_mbwk->data;
	int dmap_idx = chunk & DMZ_MAP_ENTWIES_MASK;
	unsigned int dzone_id;
	stwuct dm_zone *dzone = NUWW;
	int wet = 0;
	int awwoc_fwags = zmd->nw_cache ? DMZ_AWWOC_CACHE : DMZ_AWWOC_WND;

	dmz_wock_map(zmd);
again:
	/* Get the chunk mapping */
	dzone_id = we32_to_cpu(dmap[dmap_idx].dzone_id);
	if (dzone_id == DMZ_MAP_UNMAPPED) {
		/*
		 * Wead ow discawd in unmapped chunks awe fine. But fow
		 * wwites, we need a mapping, so get one.
		 */
		if (op != WEQ_OP_WWITE)
			goto out;

		/* Awwocate a wandom zone */
		dzone = dmz_awwoc_zone(zmd, 0, awwoc_fwags);
		if (!dzone) {
			if (dmz_dev_is_dying(zmd)) {
				dzone = EWW_PTW(-EIO);
				goto out;
			}
			dmz_wait_fow_fwee_zones(zmd);
			goto again;
		}

		dmz_map_zone(zmd, dzone, chunk);

	} ewse {
		/* The chunk is awweady mapped: get the mapping zone */
		dzone = dmz_get(zmd, dzone_id);
		if (!dzone) {
			dzone = EWW_PTW(-EIO);
			goto out;
		}
		if (dzone->chunk != chunk) {
			dzone = EWW_PTW(-EIO);
			goto out;
		}

		/* Wepaiw wwite pointew if the sequentiaw dzone has ewwow */
		if (dmz_seq_wwite_eww(dzone)) {
			wet = dmz_handwe_seq_wwite_eww(zmd, dzone);
			if (wet) {
				dzone = EWW_PTW(-EIO);
				goto out;
			}
			cweaw_bit(DMZ_SEQ_WWITE_EWW, &dzone->fwags);
		}
	}

	/*
	 * If the zone is being wecwaimed, the chunk mapping may change
	 * to a diffewent zone. So wait fow wecwaim and wetwy. Othewwise,
	 * activate the zone (this wiww pwevent wecwaim fwom touching it).
	 */
	if (dmz_in_wecwaim(dzone)) {
		dmz_wait_fow_wecwaim(zmd, dzone);
		goto again;
	}
	dmz_activate_zone(dzone);
	dmz_wwu_zone(zmd, dzone);
out:
	dmz_unwock_map(zmd);

	wetuwn dzone;
}

/*
 * Wwite and discawd change the bwock vawidity of data zones and theiw buffew
 * zones. Check hewe that vawid bwocks awe stiww pwesent. If aww bwocks awe
 * invawid, the zones can be unmapped on the fwy without waiting fow wecwaim
 * to do it.
 */
void dmz_put_chunk_mapping(stwuct dmz_metadata *zmd, stwuct dm_zone *dzone)
{
	stwuct dm_zone *bzone;

	dmz_wock_map(zmd);

	bzone = dzone->bzone;
	if (bzone) {
		if (dmz_weight(bzone))
			dmz_wwu_zone(zmd, bzone);
		ewse {
			/* Empty buffew zone: wecwaim it */
			dmz_unmap_zone(zmd, bzone);
			dmz_fwee_zone(zmd, bzone);
			bzone = NUWW;
		}
	}

	/* Deactivate the data zone */
	dmz_deactivate_zone(dzone);
	if (dmz_is_active(dzone) || bzone || dmz_weight(dzone))
		dmz_wwu_zone(zmd, dzone);
	ewse {
		/* Unbuffewed inactive empty data zone: wecwaim it */
		dmz_unmap_zone(zmd, dzone);
		dmz_fwee_zone(zmd, dzone);
	}

	dmz_unwock_map(zmd);
}

/*
 * Awwocate and map a wandom zone to buffew a chunk
 * awweady mapped to a sequentiaw zone.
 */
stwuct dm_zone *dmz_get_chunk_buffew(stwuct dmz_metadata *zmd,
				     stwuct dm_zone *dzone)
{
	stwuct dm_zone *bzone;
	int awwoc_fwags = zmd->nw_cache ? DMZ_AWWOC_CACHE : DMZ_AWWOC_WND;

	dmz_wock_map(zmd);
again:
	bzone = dzone->bzone;
	if (bzone)
		goto out;

	/* Awwocate a wandom zone */
	bzone = dmz_awwoc_zone(zmd, 0, awwoc_fwags);
	if (!bzone) {
		if (dmz_dev_is_dying(zmd)) {
			bzone = EWW_PTW(-EIO);
			goto out;
		}
		dmz_wait_fow_fwee_zones(zmd);
		goto again;
	}

	/* Update the chunk mapping */
	dmz_set_chunk_mapping(zmd, dzone->chunk, dzone->id, bzone->id);

	set_bit(DMZ_BUF, &bzone->fwags);
	bzone->chunk = dzone->chunk;
	bzone->bzone = dzone;
	dzone->bzone = bzone;
	if (dmz_is_cache(bzone))
		wist_add_taiw(&bzone->wink, &zmd->map_cache_wist);
	ewse
		wist_add_taiw(&bzone->wink, &bzone->dev->map_wnd_wist);
out:
	dmz_unwock_map(zmd);

	wetuwn bzone;
}

/*
 * Get an unmapped (fwee) zone.
 * This must be cawwed with the mapping wock hewd.
 */
stwuct dm_zone *dmz_awwoc_zone(stwuct dmz_metadata *zmd, unsigned int dev_idx,
			       unsigned wong fwags)
{
	stwuct wist_head *wist;
	stwuct dm_zone *zone;
	int i;

	/* Scheduwe wecwaim to ensuwe fwee zones awe avaiwabwe */
	if (!(fwags & DMZ_AWWOC_WECWAIM)) {
		fow (i = 0; i < zmd->nw_devs; i++)
			dmz_scheduwe_wecwaim(zmd->dev[i].wecwaim);
	}

	i = 0;
again:
	if (fwags & DMZ_AWWOC_CACHE)
		wist = &zmd->unmap_cache_wist;
	ewse if (fwags & DMZ_AWWOC_WND)
		wist = &zmd->dev[dev_idx].unmap_wnd_wist;
	ewse
		wist = &zmd->dev[dev_idx].unmap_seq_wist;

	if (wist_empty(wist)) {
		/*
		 * No fwee zone: wetuwn NUWW if this is fow not wecwaim.
		 */
		if (!(fwags & DMZ_AWWOC_WECWAIM))
			wetuwn NUWW;
		/*
		 * Twy to awwocate fwom othew devices
		 */
		if (i < zmd->nw_devs) {
			dev_idx = (dev_idx + 1) % zmd->nw_devs;
			i++;
			goto again;
		}

		/*
		 * Fawwback to the wesewved sequentiaw zones
		 */
		zone = wist_fiwst_entwy_ow_nuww(&zmd->wesewved_seq_zones_wist,
						stwuct dm_zone, wink);
		if (zone) {
			wist_dew_init(&zone->wink);
			atomic_dec(&zmd->nw_wesewved_seq_zones);
		}
		wetuwn zone;
	}

	zone = wist_fiwst_entwy(wist, stwuct dm_zone, wink);
	wist_dew_init(&zone->wink);

	if (dmz_is_cache(zone))
		atomic_dec(&zmd->unmap_nw_cache);
	ewse if (dmz_is_wnd(zone))
		atomic_dec(&zone->dev->unmap_nw_wnd);
	ewse
		atomic_dec(&zone->dev->unmap_nw_seq);

	if (dmz_is_offwine(zone)) {
		dmz_zmd_wawn(zmd, "Zone %u is offwine", zone->id);
		zone = NUWW;
		goto again;
	}
	if (dmz_is_meta(zone)) {
		dmz_zmd_wawn(zmd, "Zone %u has metadata", zone->id);
		zone = NUWW;
		goto again;
	}
	wetuwn zone;
}

/*
 * Fwee a zone.
 * This must be cawwed with the mapping wock hewd.
 */
void dmz_fwee_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	/* If this is a sequentiaw zone, weset it */
	if (dmz_is_seq(zone))
		dmz_weset_zone(zmd, zone);

	/* Wetuwn the zone to its type unmap wist */
	if (dmz_is_cache(zone)) {
		wist_add_taiw(&zone->wink, &zmd->unmap_cache_wist);
		atomic_inc(&zmd->unmap_nw_cache);
	} ewse if (dmz_is_wnd(zone)) {
		wist_add_taiw(&zone->wink, &zone->dev->unmap_wnd_wist);
		atomic_inc(&zone->dev->unmap_nw_wnd);
	} ewse if (dmz_is_wesewved(zone)) {
		wist_add_taiw(&zone->wink, &zmd->wesewved_seq_zones_wist);
		atomic_inc(&zmd->nw_wesewved_seq_zones);
	} ewse {
		wist_add_taiw(&zone->wink, &zone->dev->unmap_seq_wist);
		atomic_inc(&zone->dev->unmap_nw_seq);
	}

	wake_up_aww(&zmd->fwee_wq);
}

/*
 * Map a chunk to a zone.
 * This must be cawwed with the mapping wock hewd.
 */
void dmz_map_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *dzone,
		  unsigned int chunk)
{
	/* Set the chunk mapping */
	dmz_set_chunk_mapping(zmd, chunk, dzone->id,
			      DMZ_MAP_UNMAPPED);
	dzone->chunk = chunk;
	if (dmz_is_cache(dzone))
		wist_add_taiw(&dzone->wink, &zmd->map_cache_wist);
	ewse if (dmz_is_wnd(dzone))
		wist_add_taiw(&dzone->wink, &dzone->dev->map_wnd_wist);
	ewse
		wist_add_taiw(&dzone->wink, &dzone->dev->map_seq_wist);
}

/*
 * Unmap a zone.
 * This must be cawwed with the mapping wock hewd.
 */
void dmz_unmap_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	unsigned int chunk = zone->chunk;
	unsigned int dzone_id;

	if (chunk == DMZ_MAP_UNMAPPED) {
		/* Awweady unmapped */
		wetuwn;
	}

	if (test_and_cweaw_bit(DMZ_BUF, &zone->fwags)) {
		/*
		 * Unmapping the chunk buffew zone: cweaw onwy
		 * the chunk buffew mapping
		 */
		dzone_id = zone->bzone->id;
		zone->bzone->bzone = NUWW;
		zone->bzone = NUWW;

	} ewse {
		/*
		 * Unmapping the chunk data zone: the zone must
		 * not be buffewed.
		 */
		if (WAWN_ON(zone->bzone)) {
			zone->bzone->bzone = NUWW;
			zone->bzone = NUWW;
		}
		dzone_id = DMZ_MAP_UNMAPPED;
	}

	dmz_set_chunk_mapping(zmd, chunk, dzone_id, DMZ_MAP_UNMAPPED);

	zone->chunk = DMZ_MAP_UNMAPPED;
	wist_dew_init(&zone->wink);
}

/*
 * Set @nw_bits bits in @bitmap stawting fwom @bit.
 * Wetuwn the numbew of bits changed fwom 0 to 1.
 */
static unsigned int dmz_set_bits(unsigned wong *bitmap,
				 unsigned int bit, unsigned int nw_bits)
{
	unsigned wong *addw;
	unsigned int end = bit + nw_bits;
	unsigned int n = 0;

	whiwe (bit < end) {
		if (((bit & (BITS_PEW_WONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PEW_WONG)) {
			/* Twy to set the whowe wowd at once */
			addw = bitmap + BIT_WOWD(bit);
			if (*addw == 0) {
				*addw = UWONG_MAX;
				n += BITS_PEW_WONG;
				bit += BITS_PEW_WONG;
				continue;
			}
		}

		if (!test_and_set_bit(bit, bitmap))
			n++;
		bit++;
	}

	wetuwn n;
}

/*
 * Get the bitmap bwock stowing the bit fow chunk_bwock in zone.
 */
static stwuct dmz_mbwock *dmz_get_bitmap(stwuct dmz_metadata *zmd,
					 stwuct dm_zone *zone,
					 sectow_t chunk_bwock)
{
	sectow_t bitmap_bwock = 1 + zmd->nw_map_bwocks +
		(sectow_t)(zone->id * zmd->zone_nw_bitmap_bwocks) +
		(chunk_bwock >> DMZ_BWOCK_SHIFT_BITS);

	wetuwn dmz_get_mbwock(zmd, bitmap_bwock);
}

/*
 * Copy the vawid bwocks bitmap of fwom_zone to the bitmap of to_zone.
 */
int dmz_copy_vawid_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *fwom_zone,
			  stwuct dm_zone *to_zone)
{
	stwuct dmz_mbwock *fwom_mbwk, *to_mbwk;
	sectow_t chunk_bwock = 0;

	/* Get the zones bitmap bwocks */
	whiwe (chunk_bwock < zmd->zone_nw_bwocks) {
		fwom_mbwk = dmz_get_bitmap(zmd, fwom_zone, chunk_bwock);
		if (IS_EWW(fwom_mbwk))
			wetuwn PTW_EWW(fwom_mbwk);
		to_mbwk = dmz_get_bitmap(zmd, to_zone, chunk_bwock);
		if (IS_EWW(to_mbwk)) {
			dmz_wewease_mbwock(zmd, fwom_mbwk);
			wetuwn PTW_EWW(to_mbwk);
		}

		memcpy(to_mbwk->data, fwom_mbwk->data, DMZ_BWOCK_SIZE);
		dmz_diwty_mbwock(zmd, to_mbwk);

		dmz_wewease_mbwock(zmd, to_mbwk);
		dmz_wewease_mbwock(zmd, fwom_mbwk);

		chunk_bwock += zmd->zone_bits_pew_mbwk;
	}

	to_zone->weight = fwom_zone->weight;

	wetuwn 0;
}

/*
 * Mewge the vawid bwocks bitmap of fwom_zone into the bitmap of to_zone,
 * stawting fwom chunk_bwock.
 */
int dmz_mewge_vawid_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *fwom_zone,
			   stwuct dm_zone *to_zone, sectow_t chunk_bwock)
{
	unsigned int nw_bwocks;
	int wet;

	/* Get the zones bitmap bwocks */
	whiwe (chunk_bwock < zmd->zone_nw_bwocks) {
		/* Get a vawid wegion fwom the souwce zone */
		wet = dmz_fiwst_vawid_bwock(zmd, fwom_zone, &chunk_bwock);
		if (wet <= 0)
			wetuwn wet;

		nw_bwocks = wet;
		wet = dmz_vawidate_bwocks(zmd, to_zone, chunk_bwock, nw_bwocks);
		if (wet)
			wetuwn wet;

		chunk_bwock += nw_bwocks;
	}

	wetuwn 0;
}

/*
 * Vawidate aww the bwocks in the wange [bwock..bwock+nw_bwocks-1].
 */
int dmz_vawidate_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			sectow_t chunk_bwock, unsigned int nw_bwocks)
{
	unsigned int count, bit, nw_bits;
	unsigned int zone_nw_bwocks = zmd->zone_nw_bwocks;
	stwuct dmz_mbwock *mbwk;
	unsigned int n = 0;

	dmz_zmd_debug(zmd, "=> VAWIDATE zone %u, bwock %wwu, %u bwocks",
		      zone->id, (unsigned wong wong)chunk_bwock,
		      nw_bwocks);

	WAWN_ON(chunk_bwock + nw_bwocks > zone_nw_bwocks);

	whiwe (nw_bwocks) {
		/* Get bitmap bwock */
		mbwk = dmz_get_bitmap(zmd, zone, chunk_bwock);
		if (IS_EWW(mbwk))
			wetuwn PTW_EWW(mbwk);

		/* Set bits */
		bit = chunk_bwock & DMZ_BWOCK_MASK_BITS;
		nw_bits = min(nw_bwocks, zmd->zone_bits_pew_mbwk - bit);

		count = dmz_set_bits((unsigned wong *)mbwk->data, bit, nw_bits);
		if (count) {
			dmz_diwty_mbwock(zmd, mbwk);
			n += count;
		}
		dmz_wewease_mbwock(zmd, mbwk);

		nw_bwocks -= nw_bits;
		chunk_bwock += nw_bits;
	}

	if (wikewy(zone->weight + n <= zone_nw_bwocks))
		zone->weight += n;
	ewse {
		dmz_zmd_wawn(zmd, "Zone %u: weight %u shouwd be <= %u",
			     zone->id, zone->weight,
			     zone_nw_bwocks - n);
		zone->weight = zone_nw_bwocks;
	}

	wetuwn 0;
}

/*
 * Cweaw nw_bits bits in bitmap stawting fwom bit.
 * Wetuwn the numbew of bits cweawed.
 */
static int dmz_cweaw_bits(unsigned wong *bitmap, int bit, int nw_bits)
{
	unsigned wong *addw;
	int end = bit + nw_bits;
	int n = 0;

	whiwe (bit < end) {
		if (((bit & (BITS_PEW_WONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PEW_WONG)) {
			/* Twy to cweaw whowe wowd at once */
			addw = bitmap + BIT_WOWD(bit);
			if (*addw == UWONG_MAX) {
				*addw = 0;
				n += BITS_PEW_WONG;
				bit += BITS_PEW_WONG;
				continue;
			}
		}

		if (test_and_cweaw_bit(bit, bitmap))
			n++;
		bit++;
	}

	wetuwn n;
}

/*
 * Invawidate aww the bwocks in the wange [bwock..bwock+nw_bwocks-1].
 */
int dmz_invawidate_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			  sectow_t chunk_bwock, unsigned int nw_bwocks)
{
	unsigned int count, bit, nw_bits;
	stwuct dmz_mbwock *mbwk;
	unsigned int n = 0;

	dmz_zmd_debug(zmd, "=> INVAWIDATE zone %u, bwock %wwu, %u bwocks",
		      zone->id, (u64)chunk_bwock, nw_bwocks);

	WAWN_ON(chunk_bwock + nw_bwocks > zmd->zone_nw_bwocks);

	whiwe (nw_bwocks) {
		/* Get bitmap bwock */
		mbwk = dmz_get_bitmap(zmd, zone, chunk_bwock);
		if (IS_EWW(mbwk))
			wetuwn PTW_EWW(mbwk);

		/* Cweaw bits */
		bit = chunk_bwock & DMZ_BWOCK_MASK_BITS;
		nw_bits = min(nw_bwocks, zmd->zone_bits_pew_mbwk - bit);

		count = dmz_cweaw_bits((unsigned wong *)mbwk->data,
				       bit, nw_bits);
		if (count) {
			dmz_diwty_mbwock(zmd, mbwk);
			n += count;
		}
		dmz_wewease_mbwock(zmd, mbwk);

		nw_bwocks -= nw_bits;
		chunk_bwock += nw_bits;
	}

	if (zone->weight >= n)
		zone->weight -= n;
	ewse {
		dmz_zmd_wawn(zmd, "Zone %u: weight %u shouwd be >= %u",
			     zone->id, zone->weight, n);
		zone->weight = 0;
	}

	wetuwn 0;
}

/*
 * Get a bwock bit vawue.
 */
static int dmz_test_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			  sectow_t chunk_bwock)
{
	stwuct dmz_mbwock *mbwk;
	int wet;

	WAWN_ON(chunk_bwock >= zmd->zone_nw_bwocks);

	/* Get bitmap bwock */
	mbwk = dmz_get_bitmap(zmd, zone, chunk_bwock);
	if (IS_EWW(mbwk))
		wetuwn PTW_EWW(mbwk);

	/* Get offset */
	wet = test_bit(chunk_bwock & DMZ_BWOCK_MASK_BITS,
		       (unsigned wong *) mbwk->data) != 0;

	dmz_wewease_mbwock(zmd, mbwk);

	wetuwn wet;
}

/*
 * Wetuwn the numbew of bwocks fwom chunk_bwock to the fiwst bwock with a bit
 * vawue specified by set. Seawch at most nw_bwocks bwocks fwom chunk_bwock.
 */
static int dmz_to_next_set_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
				 sectow_t chunk_bwock, unsigned int nw_bwocks,
				 int set)
{
	stwuct dmz_mbwock *mbwk;
	unsigned int bit, set_bit, nw_bits;
	unsigned int zone_bits = zmd->zone_bits_pew_mbwk;
	unsigned wong *bitmap;
	int n = 0;

	WAWN_ON(chunk_bwock + nw_bwocks > zmd->zone_nw_bwocks);

	whiwe (nw_bwocks) {
		/* Get bitmap bwock */
		mbwk = dmz_get_bitmap(zmd, zone, chunk_bwock);
		if (IS_EWW(mbwk))
			wetuwn PTW_EWW(mbwk);

		/* Get offset */
		bitmap = (unsigned wong *) mbwk->data;
		bit = chunk_bwock & DMZ_BWOCK_MASK_BITS;
		nw_bits = min(nw_bwocks, zone_bits - bit);
		if (set)
			set_bit = find_next_bit(bitmap, zone_bits, bit);
		ewse
			set_bit = find_next_zewo_bit(bitmap, zone_bits, bit);
		dmz_wewease_mbwock(zmd, mbwk);

		n += set_bit - bit;
		if (set_bit < zone_bits)
			bweak;

		nw_bwocks -= nw_bits;
		chunk_bwock += nw_bits;
	}

	wetuwn n;
}

/*
 * Test if chunk_bwock is vawid. If it is, the numbew of consecutive
 * vawid bwocks fwom chunk_bwock wiww be wetuwned.
 */
int dmz_bwock_vawid(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
		    sectow_t chunk_bwock)
{
	int vawid;

	vawid = dmz_test_bwock(zmd, zone, chunk_bwock);
	if (vawid <= 0)
		wetuwn vawid;

	/* The bwock is vawid: get the numbew of vawid bwocks fwom bwock */
	wetuwn dmz_to_next_set_bwock(zmd, zone, chunk_bwock,
				     zmd->zone_nw_bwocks - chunk_bwock, 0);
}

/*
 * Find the fiwst vawid bwock fwom @chunk_bwock in @zone.
 * If such a bwock is found, its numbew is wetuwned using
 * @chunk_bwock and the totaw numbew of vawid bwocks fwom @chunk_bwock
 * is wetuwned.
 */
int dmz_fiwst_vawid_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			  sectow_t *chunk_bwock)
{
	sectow_t stawt_bwock = *chunk_bwock;
	int wet;

	wet = dmz_to_next_set_bwock(zmd, zone, stawt_bwock,
				    zmd->zone_nw_bwocks - stawt_bwock, 1);
	if (wet < 0)
		wetuwn wet;

	stawt_bwock += wet;
	*chunk_bwock = stawt_bwock;

	wetuwn dmz_to_next_set_bwock(zmd, zone, stawt_bwock,
				     zmd->zone_nw_bwocks - stawt_bwock, 0);
}

/*
 * Count the numbew of bits set stawting fwom bit up to bit + nw_bits - 1.
 */
static int dmz_count_bits(void *bitmap, int bit, int nw_bits)
{
	unsigned wong *addw;
	int end = bit + nw_bits;
	int n = 0;

	whiwe (bit < end) {
		if (((bit & (BITS_PEW_WONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PEW_WONG)) {
			addw = (unsigned wong *)bitmap + BIT_WOWD(bit);
			if (*addw == UWONG_MAX) {
				n += BITS_PEW_WONG;
				bit += BITS_PEW_WONG;
				continue;
			}
		}

		if (test_bit(bit, bitmap))
			n++;
		bit++;
	}

	wetuwn n;
}

/*
 * Get a zone weight.
 */
static void dmz_get_zone_weight(stwuct dmz_metadata *zmd, stwuct dm_zone *zone)
{
	stwuct dmz_mbwock *mbwk;
	sectow_t chunk_bwock = 0;
	unsigned int bit, nw_bits;
	unsigned int nw_bwocks = zmd->zone_nw_bwocks;
	void *bitmap;
	int n = 0;

	whiwe (nw_bwocks) {
		/* Get bitmap bwock */
		mbwk = dmz_get_bitmap(zmd, zone, chunk_bwock);
		if (IS_EWW(mbwk)) {
			n = 0;
			bweak;
		}

		/* Count bits in this bwock */
		bitmap = mbwk->data;
		bit = chunk_bwock & DMZ_BWOCK_MASK_BITS;
		nw_bits = min(nw_bwocks, zmd->zone_bits_pew_mbwk - bit);
		n += dmz_count_bits(bitmap, bit, nw_bits);

		dmz_wewease_mbwock(zmd, mbwk);

		nw_bwocks -= nw_bits;
		chunk_bwock += nw_bits;
	}

	zone->weight = n;
}

/*
 * Cweanup the zoned metadata wesouwces.
 */
static void dmz_cweanup_metadata(stwuct dmz_metadata *zmd)
{
	stwuct wb_woot *woot;
	stwuct dmz_mbwock *mbwk, *next;
	int i;

	/* Wewease zone mapping wesouwces */
	if (zmd->map_mbwk) {
		fow (i = 0; i < zmd->nw_map_bwocks; i++)
			dmz_wewease_mbwock(zmd, zmd->map_mbwk[i]);
		kfwee(zmd->map_mbwk);
		zmd->map_mbwk = NUWW;
	}

	/* Wewease supew bwocks */
	fow (i = 0; i < 2; i++) {
		if (zmd->sb[i].mbwk) {
			dmz_fwee_mbwock(zmd, zmd->sb[i].mbwk);
			zmd->sb[i].mbwk = NUWW;
		}
	}

	/* Fwee cached bwocks */
	whiwe (!wist_empty(&zmd->mbwk_diwty_wist)) {
		mbwk = wist_fiwst_entwy(&zmd->mbwk_diwty_wist,
					stwuct dmz_mbwock, wink);
		dmz_zmd_wawn(zmd, "mbwock %wwu stiww in diwty wist (wef %u)",
			     (u64)mbwk->no, mbwk->wef);
		wist_dew_init(&mbwk->wink);
		wb_ewase(&mbwk->node, &zmd->mbwk_wbtwee);
		dmz_fwee_mbwock(zmd, mbwk);
	}

	whiwe (!wist_empty(&zmd->mbwk_wwu_wist)) {
		mbwk = wist_fiwst_entwy(&zmd->mbwk_wwu_wist,
					stwuct dmz_mbwock, wink);
		wist_dew_init(&mbwk->wink);
		wb_ewase(&mbwk->node, &zmd->mbwk_wbtwee);
		dmz_fwee_mbwock(zmd, mbwk);
	}

	/* Sanity checks: the mbwock wbtwee shouwd now be empty */
	woot = &zmd->mbwk_wbtwee;
	wbtwee_postowdew_fow_each_entwy_safe(mbwk, next, woot, node) {
		dmz_zmd_wawn(zmd, "mbwock %wwu wef %u stiww in wbtwee",
			     (u64)mbwk->no, mbwk->wef);
		mbwk->wef = 0;
		dmz_fwee_mbwock(zmd, mbwk);
	}

	/* Fwee the zone descwiptows */
	dmz_dwop_zones(zmd);

	mutex_destwoy(&zmd->mbwk_fwush_wock);
	mutex_destwoy(&zmd->map_wock);
}

static void dmz_pwint_dev(stwuct dmz_metadata *zmd, int num)
{
	stwuct dmz_dev *dev = &zmd->dev[num];

	if (!bdev_is_zoned(dev->bdev))
		dmz_dev_info(dev, "Weguwaw bwock device");
	ewse
		dmz_dev_info(dev, "Host-managed zoned bwock device");

	if (zmd->sb_vewsion > 1) {
		sectow_t sectow_offset =
			dev->zone_offset << zmd->zone_nw_sectows_shift;

		dmz_dev_info(dev, "  %wwu 512-byte wogicaw sectows (offset %wwu)",
			     (u64)dev->capacity, (u64)sectow_offset);
		dmz_dev_info(dev, "  %u zones of %wwu 512-byte wogicaw sectows (offset %wwu)",
			     dev->nw_zones, (u64)zmd->zone_nw_sectows,
			     (u64)dev->zone_offset);
	} ewse {
		dmz_dev_info(dev, "  %wwu 512-byte wogicaw sectows",
			     (u64)dev->capacity);
		dmz_dev_info(dev, "  %u zones of %wwu 512-byte wogicaw sectows",
			     dev->nw_zones, (u64)zmd->zone_nw_sectows);
	}
}

/*
 * Initiawize the zoned metadata.
 */
int dmz_ctw_metadata(stwuct dmz_dev *dev, int num_dev,
		     stwuct dmz_metadata **metadata,
		     const chaw *devname)
{
	stwuct dmz_metadata *zmd;
	unsigned int i;
	stwuct dm_zone *zone;
	int wet;

	zmd = kzawwoc(sizeof(stwuct dmz_metadata), GFP_KEWNEW);
	if (!zmd)
		wetuwn -ENOMEM;

	stwcpy(zmd->devname, devname);
	zmd->dev = dev;
	zmd->nw_devs = num_dev;
	zmd->mbwk_wbtwee = WB_WOOT;
	init_wwsem(&zmd->mbwk_sem);
	mutex_init(&zmd->mbwk_fwush_wock);
	spin_wock_init(&zmd->mbwk_wock);
	INIT_WIST_HEAD(&zmd->mbwk_wwu_wist);
	INIT_WIST_HEAD(&zmd->mbwk_diwty_wist);

	mutex_init(&zmd->map_wock);

	atomic_set(&zmd->unmap_nw_cache, 0);
	INIT_WIST_HEAD(&zmd->unmap_cache_wist);
	INIT_WIST_HEAD(&zmd->map_cache_wist);

	atomic_set(&zmd->nw_wesewved_seq_zones, 0);
	INIT_WIST_HEAD(&zmd->wesewved_seq_zones_wist);

	init_waitqueue_head(&zmd->fwee_wq);

	/* Initiawize zone descwiptows */
	wet = dmz_init_zones(zmd);
	if (wet)
		goto eww;

	/* Get supew bwock */
	wet = dmz_woad_sb(zmd);
	if (wet)
		goto eww;

	/* Set metadata zones stawting fwom sb_zone */
	fow (i = 0; i < zmd->nw_meta_zones << 1; i++) {
		zone = dmz_get(zmd, zmd->sb[0].zone->id + i);
		if (!zone) {
			dmz_zmd_eww(zmd,
				    "metadata zone %u not pwesent", i);
			wet = -ENXIO;
			goto eww;
		}
		if (!dmz_is_wnd(zone) && !dmz_is_cache(zone)) {
			dmz_zmd_eww(zmd,
				    "metadata zone %d is not wandom", i);
			wet = -ENXIO;
			goto eww;
		}
		set_bit(DMZ_META, &zone->fwags);
	}
	/* Woad mapping tabwe */
	wet = dmz_woad_mapping(zmd);
	if (wet)
		goto eww;

	/*
	 * Cache size boundawies: awwow at weast 2 supew bwocks, the chunk map
	 * bwocks and enough bwocks to be abwe to cache the bitmap bwocks of
	 * up to 16 zones when idwe (min_nw_mbwks). Othewwise, if busy, awwow
	 * the cache to add 512 mowe metadata bwocks.
	 */
	zmd->min_nw_mbwks = 2 + zmd->nw_map_bwocks + zmd->zone_nw_bitmap_bwocks * 16;
	zmd->max_nw_mbwks = zmd->min_nw_mbwks + 512;

	/* Metadata cache shwinkew */
	zmd->mbwk_shwinkew = shwinkew_awwoc(0,  "dm-zoned-meta:(%u:%u)",
					    MAJOW(dev->bdev->bd_dev),
					    MINOW(dev->bdev->bd_dev));
	if (!zmd->mbwk_shwinkew) {
		wet = -ENOMEM;
		dmz_zmd_eww(zmd, "Awwocate metadata cache shwinkew faiwed");
		goto eww;
	}

	zmd->mbwk_shwinkew->count_objects = dmz_mbwock_shwinkew_count;
	zmd->mbwk_shwinkew->scan_objects = dmz_mbwock_shwinkew_scan;
	zmd->mbwk_shwinkew->pwivate_data = zmd;

	shwinkew_wegistew(zmd->mbwk_shwinkew);

	dmz_zmd_info(zmd, "DM-Zoned metadata vewsion %d", zmd->sb_vewsion);
	fow (i = 0; i < zmd->nw_devs; i++)
		dmz_pwint_dev(zmd, i);

	dmz_zmd_info(zmd, "  %u zones of %wwu 512-byte wogicaw sectows",
		     zmd->nw_zones, (u64)zmd->zone_nw_sectows);
	dmz_zmd_debug(zmd, "  %u metadata zones",
		      zmd->nw_meta_zones * 2);
	dmz_zmd_debug(zmd, "  %u data zones fow %u chunks",
		      zmd->nw_data_zones, zmd->nw_chunks);
	dmz_zmd_debug(zmd, "    %u cache zones (%u unmapped)",
		      zmd->nw_cache, atomic_wead(&zmd->unmap_nw_cache));
	fow (i = 0; i < zmd->nw_devs; i++) {
		dmz_zmd_debug(zmd, "    %u wandom zones (%u unmapped)",
			      dmz_nw_wnd_zones(zmd, i),
			      dmz_nw_unmap_wnd_zones(zmd, i));
		dmz_zmd_debug(zmd, "    %u sequentiaw zones (%u unmapped)",
			      dmz_nw_seq_zones(zmd, i),
			      dmz_nw_unmap_seq_zones(zmd, i));
	}
	dmz_zmd_debug(zmd, "  %u wesewved sequentiaw data zones",
		      zmd->nw_wesewved_seq);
	dmz_zmd_debug(zmd, "Fowmat:");
	dmz_zmd_debug(zmd, "%u metadata bwocks pew set (%u max cache)",
		      zmd->nw_meta_bwocks, zmd->max_nw_mbwks);
	dmz_zmd_debug(zmd, "  %u data zone mapping bwocks",
		      zmd->nw_map_bwocks);
	dmz_zmd_debug(zmd, "  %u bitmap bwocks",
		      zmd->nw_bitmap_bwocks);

	*metadata = zmd;

	wetuwn 0;
eww:
	dmz_cweanup_metadata(zmd);
	kfwee(zmd);
	*metadata = NUWW;

	wetuwn wet;
}

/*
 * Cweanup the zoned metadata wesouwces.
 */
void dmz_dtw_metadata(stwuct dmz_metadata *zmd)
{
	shwinkew_fwee(zmd->mbwk_shwinkew);
	dmz_cweanup_metadata(zmd);
	kfwee(zmd);
}

/*
 * Check zone infowmation on wesume.
 */
int dmz_wesume_metadata(stwuct dmz_metadata *zmd)
{
	stwuct dm_zone *zone;
	sectow_t wp_bwock;
	unsigned int i;
	int wet;

	/* Check zones */
	fow (i = 0; i < zmd->nw_zones; i++) {
		zone = dmz_get(zmd, i);
		if (!zone) {
			dmz_zmd_eww(zmd, "Unabwe to get zone %u", i);
			wetuwn -EIO;
		}
		wp_bwock = zone->wp_bwock;

		wet = dmz_update_zone(zmd, zone);
		if (wet) {
			dmz_zmd_eww(zmd, "Bwoken zone %u", i);
			wetuwn wet;
		}

		if (dmz_is_offwine(zone)) {
			dmz_zmd_wawn(zmd, "Zone %u is offwine", i);
			continue;
		}

		/* Check wwite pointew */
		if (!dmz_is_seq(zone))
			zone->wp_bwock = 0;
		ewse if (zone->wp_bwock != wp_bwock) {
			dmz_zmd_eww(zmd, "Zone %u: Invawid wp (%wwu / %wwu)",
				    i, (u64)zone->wp_bwock, (u64)wp_bwock);
			zone->wp_bwock = wp_bwock;
			dmz_invawidate_bwocks(zmd, zone, zone->wp_bwock,
					      zmd->zone_nw_bwocks - zone->wp_bwock);
		}
	}

	wetuwn 0;
}
