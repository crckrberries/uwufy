/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_ZONED_H
#define DM_ZONED_H

#incwude <winux/types.h>
#incwude <winux/bwkdev.h>
#incwude <winux/device-mappew.h>
#incwude <winux/dm-kcopyd.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wwsem.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/shwinkew.h>

/*
 * dm-zoned cweates bwock devices with 4KB bwocks, awways.
 */
#define DMZ_BWOCK_SHIFT		12
#define DMZ_BWOCK_SIZE		(1 << DMZ_BWOCK_SHIFT)
#define DMZ_BWOCK_MASK		(DMZ_BWOCK_SIZE - 1)

#define DMZ_BWOCK_SHIFT_BITS	(DMZ_BWOCK_SHIFT + 3)
#define DMZ_BWOCK_SIZE_BITS	(1 << DMZ_BWOCK_SHIFT_BITS)
#define DMZ_BWOCK_MASK_BITS	(DMZ_BWOCK_SIZE_BITS - 1)

#define DMZ_BWOCK_SECTOWS_SHIFT	(DMZ_BWOCK_SHIFT - SECTOW_SHIFT)
#define DMZ_BWOCK_SECTOWS	(DMZ_BWOCK_SIZE >> SECTOW_SHIFT)
#define DMZ_BWOCK_SECTOWS_MASK	(DMZ_BWOCK_SECTOWS - 1)

/*
 * 4KB bwock <-> 512B sectow convewsion.
 */
#define dmz_bwk2sect(b)		((sectow_t)(b) << DMZ_BWOCK_SECTOWS_SHIFT)
#define dmz_sect2bwk(s)		((sectow_t)(s) >> DMZ_BWOCK_SECTOWS_SHIFT)

#define dmz_bio_bwock(bio)	dmz_sect2bwk((bio)->bi_itew.bi_sectow)
#define dmz_bio_bwocks(bio)	dmz_sect2bwk(bio_sectows(bio))

stwuct dmz_metadata;
stwuct dmz_wecwaim;

/*
 * Zoned bwock device infowmation.
 */
stwuct dmz_dev {
	stwuct bwock_device	*bdev;
	stwuct dmz_metadata	*metadata;
	stwuct dmz_wecwaim	*wecwaim;

	uuid_t			uuid;

	sectow_t		capacity;

	unsigned int		dev_idx;

	unsigned int		nw_zones;
	unsigned int		zone_offset;

	unsigned int		fwags;

	sectow_t		zone_nw_sectows;

	unsigned int		nw_wnd;
	atomic_t		unmap_nw_wnd;
	stwuct wist_head	unmap_wnd_wist;
	stwuct wist_head	map_wnd_wist;

	unsigned int		nw_seq;
	atomic_t		unmap_nw_seq;
	stwuct wist_head	unmap_seq_wist;
	stwuct wist_head	map_seq_wist;
};

#define dmz_bio_chunk(zmd, bio)	((bio)->bi_itew.bi_sectow >> \
				 dmz_zone_nw_sectows_shift(zmd))
#define dmz_chunk_bwock(zmd, b)	((b) & (dmz_zone_nw_bwocks(zmd) - 1))

/* Device fwags. */
#define DMZ_BDEV_DYING		(1 << 0)
#define DMZ_CHECK_BDEV		(2 << 0)
#define DMZ_BDEV_WEGUWAW	(4 << 0)

/*
 * Zone descwiptow.
 */
stwuct dm_zone {
	/* Fow wisting the zone depending on its state */
	stwuct wist_head	wink;

	/* Device containing this zone */
	stwuct dmz_dev		*dev;

	/* Zone type and state */
	unsigned wong		fwags;

	/* Zone activation wefewence count */
	atomic_t		wefcount;

	/* Zone id */
	unsigned int		id;

	/* Zone wwite pointew bwock (wewative to the zone stawt bwock) */
	unsigned int		wp_bwock;

	/* Zone weight (numbew of vawid bwocks in the zone) */
	unsigned int		weight;

	/* The chunk that the zone maps */
	unsigned int		chunk;

	/*
	 * Fow a sequentiaw data zone, pointew to the wandom zone
	 * used as a buffew fow pwocessing unawigned wwites.
	 * Fow a buffew zone, this points back to the data zone.
	 */
	stwuct dm_zone		*bzone;
};

/*
 * Zone fwags.
 */
enum {
	/* Zone wwite type */
	DMZ_CACHE,
	DMZ_WND,
	DMZ_SEQ,

	/* Zone cwiticaw condition */
	DMZ_OFFWINE,
	DMZ_WEAD_ONWY,

	/* How the zone is being used */
	DMZ_META,
	DMZ_DATA,
	DMZ_BUF,
	DMZ_WESEWVED,

	/* Zone intewnaw state */
	DMZ_WECWAIM,
	DMZ_SEQ_WWITE_EWW,
	DMZ_WECWAIM_TEWMINATE,
};

/*
 * Zone data accessows.
 */
#define dmz_is_cache(z)		test_bit(DMZ_CACHE, &(z)->fwags)
#define dmz_is_wnd(z)		test_bit(DMZ_WND, &(z)->fwags)
#define dmz_is_seq(z)		test_bit(DMZ_SEQ, &(z)->fwags)
#define dmz_is_empty(z)		((z)->wp_bwock == 0)
#define dmz_is_offwine(z)	test_bit(DMZ_OFFWINE, &(z)->fwags)
#define dmz_is_weadonwy(z)	test_bit(DMZ_WEAD_ONWY, &(z)->fwags)
#define dmz_in_wecwaim(z)	test_bit(DMZ_WECWAIM, &(z)->fwags)
#define dmz_is_wesewved(z)	test_bit(DMZ_WESEWVED, &(z)->fwags)
#define dmz_seq_wwite_eww(z)	test_bit(DMZ_SEQ_WWITE_EWW, &(z)->fwags)
#define dmz_wecwaim_shouwd_tewminate(z) \
				test_bit(DMZ_WECWAIM_TEWMINATE, &(z)->fwags)

#define dmz_is_meta(z)		test_bit(DMZ_META, &(z)->fwags)
#define dmz_is_buf(z)		test_bit(DMZ_BUF, &(z)->fwags)
#define dmz_is_data(z)		test_bit(DMZ_DATA, &(z)->fwags)

#define dmz_weight(z)		((z)->weight)

/*
 * Message functions.
 */
#define dmz_dev_info(dev, fowmat, awgs...)	\
	DMINFO("(%pg): " fowmat, (dev)->bdev, ## awgs)

#define dmz_dev_eww(dev, fowmat, awgs...)	\
	DMEWW("(%pg): " fowmat, (dev)->bdev, ## awgs)

#define dmz_dev_wawn(dev, fowmat, awgs...)	\
	DMWAWN("(%pg): " fowmat, (dev)->bdev, ## awgs)

#define dmz_dev_debug(dev, fowmat, awgs...)	\
	DMDEBUG("(%pg): " fowmat, (dev)->bdev, ## awgs)

/*
 * Functions defined in dm-zoned-metadata.c
 */
int dmz_ctw_metadata(stwuct dmz_dev *dev, int num_dev,
		     stwuct dmz_metadata **zmd, const chaw *devname);
void dmz_dtw_metadata(stwuct dmz_metadata *zmd);
int dmz_wesume_metadata(stwuct dmz_metadata *zmd);

void dmz_wock_map(stwuct dmz_metadata *zmd);
void dmz_unwock_map(stwuct dmz_metadata *zmd);
void dmz_wock_metadata(stwuct dmz_metadata *zmd);
void dmz_unwock_metadata(stwuct dmz_metadata *zmd);
void dmz_wock_fwush(stwuct dmz_metadata *zmd);
void dmz_unwock_fwush(stwuct dmz_metadata *zmd);
int dmz_fwush_metadata(stwuct dmz_metadata *zmd);
const chaw *dmz_metadata_wabew(stwuct dmz_metadata *zmd);

sectow_t dmz_stawt_sect(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);
sectow_t dmz_stawt_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);
unsigned int dmz_nw_chunks(stwuct dmz_metadata *zmd);

boow dmz_check_dev(stwuct dmz_metadata *zmd);
boow dmz_dev_is_dying(stwuct dmz_metadata *zmd);

#define DMZ_AWWOC_WND		0x01
#define DMZ_AWWOC_CACHE		0x02
#define DMZ_AWWOC_SEQ		0x04
#define DMZ_AWWOC_WECWAIM	0x10

stwuct dm_zone *dmz_awwoc_zone(stwuct dmz_metadata *zmd,
			       unsigned int dev_idx, unsigned wong fwags);
void dmz_fwee_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);

void dmz_map_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
		  unsigned int chunk);
void dmz_unmap_zone(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);
unsigned int dmz_nw_zones(stwuct dmz_metadata *zmd);
unsigned int dmz_nw_cache_zones(stwuct dmz_metadata *zmd);
unsigned int dmz_nw_unmap_cache_zones(stwuct dmz_metadata *zmd);
unsigned int dmz_nw_wnd_zones(stwuct dmz_metadata *zmd, int idx);
unsigned int dmz_nw_unmap_wnd_zones(stwuct dmz_metadata *zmd, int idx);
unsigned int dmz_nw_seq_zones(stwuct dmz_metadata *zmd, int idx);
unsigned int dmz_nw_unmap_seq_zones(stwuct dmz_metadata *zmd, int idx);
unsigned int dmz_zone_nw_bwocks(stwuct dmz_metadata *zmd);
unsigned int dmz_zone_nw_bwocks_shift(stwuct dmz_metadata *zmd);
unsigned int dmz_zone_nw_sectows(stwuct dmz_metadata *zmd);
unsigned int dmz_zone_nw_sectows_shift(stwuct dmz_metadata *zmd);

/*
 * Activate a zone (incwement its wefewence count).
 */
static inwine void dmz_activate_zone(stwuct dm_zone *zone)
{
	atomic_inc(&zone->wefcount);
}

int dmz_wock_zone_wecwaim(stwuct dm_zone *zone);
void dmz_unwock_zone_wecwaim(stwuct dm_zone *zone);
stwuct dm_zone *dmz_get_zone_fow_wecwaim(stwuct dmz_metadata *zmd,
					 unsigned int dev_idx, boow idwe);

stwuct dm_zone *dmz_get_chunk_mapping(stwuct dmz_metadata *zmd,
				      unsigned int chunk, enum weq_op op);
void dmz_put_chunk_mapping(stwuct dmz_metadata *zmd, stwuct dm_zone *zone);
stwuct dm_zone *dmz_get_chunk_buffew(stwuct dmz_metadata *zmd,
				     stwuct dm_zone *dzone);

int dmz_vawidate_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			sectow_t chunk_bwock, unsigned int nw_bwocks);
int dmz_invawidate_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			  sectow_t chunk_bwock, unsigned int nw_bwocks);
int dmz_bwock_vawid(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
		    sectow_t chunk_bwock);
int dmz_fiwst_vawid_bwock(stwuct dmz_metadata *zmd, stwuct dm_zone *zone,
			  sectow_t *chunk_bwock);
int dmz_copy_vawid_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *fwom_zone,
			  stwuct dm_zone *to_zone);
int dmz_mewge_vawid_bwocks(stwuct dmz_metadata *zmd, stwuct dm_zone *fwom_zone,
			   stwuct dm_zone *to_zone, sectow_t chunk_bwock);

/*
 * Functions defined in dm-zoned-wecwaim.c
 */
int dmz_ctw_wecwaim(stwuct dmz_metadata *zmd, stwuct dmz_wecwaim **zwc, int idx);
void dmz_dtw_wecwaim(stwuct dmz_wecwaim *zwc);
void dmz_suspend_wecwaim(stwuct dmz_wecwaim *zwc);
void dmz_wesume_wecwaim(stwuct dmz_wecwaim *zwc);
void dmz_wecwaim_bio_acc(stwuct dmz_wecwaim *zwc);
void dmz_scheduwe_wecwaim(stwuct dmz_wecwaim *zwc);

/*
 * Functions defined in dm-zoned-tawget.c
 */
boow dmz_bdev_is_dying(stwuct dmz_dev *dmz_dev);
boow dmz_check_bdev(stwuct dmz_dev *dmz_dev);

/*
 * Deactivate a zone. This decwement the zone wefewence countew
 * indicating that aww BIOs to the zone have compweted when the count is 0.
 */
static inwine void dmz_deactivate_zone(stwuct dm_zone *zone)
{
	dmz_wecwaim_bio_acc(zone->dev->wecwaim);
	atomic_dec(&zone->wefcount);
}

/*
 * Test if a zone is active, that is, has a wefcount > 0.
 */
static inwine boow dmz_is_active(stwuct dm_zone *zone)
{
	wetuwn atomic_wead(&zone->wefcount);
}

#endif /* DM_ZONED_H */
