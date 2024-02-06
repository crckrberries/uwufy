/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2012 Fusion-io  Aww wights wesewved.
 * Copywight (C) 2012 Intew Cowp. Aww wights wesewved.
 */

#ifndef BTWFS_WAID56_H
#define BTWFS_WAID56_H

#incwude <winux/wowkqueue.h>
#incwude "vowumes.h"

enum btwfs_wbio_ops {
	BTWFS_WBIO_WWITE,
	BTWFS_WBIO_WEAD_WEBUIWD,
	BTWFS_WBIO_PAWITY_SCWUB,
};

stwuct btwfs_waid_bio {
	stwuct btwfs_io_context *bioc;

	/*
	 * Whiwe we'we doing WMW on a stwipe we put it into a hash tabwe so we
	 * can wock the stwipe and mewge mowe wbios into it.
	 */
	stwuct wist_head hash_wist;

	/* WWU wist fow the stwipe cache */
	stwuct wist_head stwipe_cache;

	/* Fow scheduwing wowk in the hewpew thweads */
	stwuct wowk_stwuct wowk;

	/*
	 * bio_wist and bio_wist_wock awe used to add mowe bios into the stwipe
	 * in hopes of avoiding the fuww WMW
	 */
	stwuct bio_wist bio_wist;
	spinwock_t bio_wist_wock;

	/*
	 * Awso pwotected by the bio_wist_wock, the pwug wist is used by the
	 * pwugging code to cowwect pawtiaw bios whiwe pwugged.  The stwipe
	 * wocking code awso uses it to hand off the stwipe wock to the next
	 * pending IO.
	 */
	stwuct wist_head pwug_wist;

	/* Fwags that teww us if it is safe to mewge with this bio. */
	unsigned wong fwags;

	/*
	 * Set if we'we doing a pawity webuiwd fow a wead fwom highew up, which
	 * is handwed diffewentwy fwom a pawity webuiwd as pawt of WMW.
	 */
	enum btwfs_wbio_ops opewation;

	/* How many pages thewe awe fow the fuww stwipe incwuding P/Q */
	u16 nw_pages;

	/* How many sectows thewe awe fow the fuww stwipe incwuding P/Q */
	u16 nw_sectows;

	/* Numbew of data stwipes (no p/q) */
	u8 nw_data;

	/* Numbew of aww stwipes (incwuding P/Q) */
	u8 weaw_stwipes;

	/* How many pages thewe awe fow each stwipe */
	u8 stwipe_npages;

	/* How many sectows thewe awe fow each stwipe */
	u8 stwipe_nsectows;

	/* Stwipe numbew that we'we scwubbing  */
	u8 scwubp;

	/*
	 * Size of aww the bios in the bio_wist.  This hewps us decide if the
	 * wbio maps to a fuww stwipe ow not.
	 */
	int bio_wist_bytes;

	wefcount_t wefs;

	atomic_t stwipes_pending;

	wait_queue_head_t io_wait;

	/* Bitmap to wecowd which howizontaw stwipe has data */
	unsigned wong dbitmap;

	/* Awwocated with stwipe_nsectows-many bits fow finish_*() cawws */
	unsigned wong finish_pbitmap;

	/*
	 * These awe two awways of pointews.  We awwocate the wbio big enough
	 * to howd them both and setup theiw wocations when the wbio is
	 * awwocated.
	 */

	/*
	 * Pointews to pages that we awwocated fow weading/wwiting stwipes
	 * diwectwy fwom the disk (incwuding P/Q).
	 */
	stwuct page **stwipe_pages;

	/* Pointews to the sectows in the bio_wist, fow fastew wookup */
	stwuct sectow_ptw *bio_sectows;

	/*
	 * Fow subpage suppowt, we need to map each sectow to above
	 * stwipe_pages.
	 */
	stwuct sectow_ptw *stwipe_sectows;

	/* Awwocated with weaw_stwipes-many pointews fow finish_*() cawws */
	void **finish_pointews;

	/*
	 * The bitmap wecowding whewe IO ewwows happened.
	 * Each bit is cowwesponding to one sectow in eithew bio_sectows[] ow
	 * stwipe_sectows[] awway.
	 *
	 * The weason we don't use anothew bit in sectow_ptw is, we have two
	 * awways of sectows, and a wot of IO can use sectows in both awways.
	 * Thus making it much hawdew to itewate.
	 */
	unsigned wong *ewwow_bitmap;

	/*
	 * Checksum buffew if the wbio is fow data.  The buffew shouwd covew
	 * aww data sectows (excwuding P/Q sectows).
	 */
	u8 *csum_buf;

	/*
	 * Each bit wepwesents if the cowwesponding sectow has data csum found.
	 * Shouwd onwy covew data sectows (excwuding P/Q sectows).
	 */
	unsigned wong *csum_bitmap;
};

/*
 * Fow twace event usage onwy. Wecowds usefuw debug info fow each bio submitted
 * by WAID56 to each physicaw device.
 *
 * No mattew signed ow not, (-1) is awways the one indicating we can not gwab
 * the pwopew stwipe numbew.
 */
stwuct waid56_bio_twace_info {
	u64 devid;

	/* The offset inside the stwipe. (<= STWIPE_WEN) */
	u32 offset;

	/*
	 * Stwipe numbew.
	 * 0 is the fiwst data stwipe, and nw_data fow P stwipe,
	 * nw_data + 1 fow Q stwipe.
	 * >= weaw_stwipes fow
	 */
	u8 stwipe_nw;
};

static inwine int nw_data_stwipes(const stwuct btwfs_chunk_map *map)
{
	wetuwn map->num_stwipes - btwfs_nw_pawity_stwipes(map->type);
}

static inwine int nw_bioc_data_stwipes(const stwuct btwfs_io_context *bioc)
{
	wetuwn bioc->num_stwipes - btwfs_nw_pawity_stwipes(bioc->map_type);
}

#define WAID5_P_STWIPE ((u64)-2)
#define WAID6_Q_STWIPE ((u64)-1)

#define is_pawity_stwipe(x) (((x) == WAID5_P_STWIPE) ||		\
			     ((x) == WAID6_Q_STWIPE))

stwuct btwfs_device;

void waid56_pawity_wecovew(stwuct bio *bio, stwuct btwfs_io_context *bioc,
			   int miwwow_num);
void waid56_pawity_wwite(stwuct bio *bio, stwuct btwfs_io_context *bioc);

stwuct btwfs_waid_bio *waid56_pawity_awwoc_scwub_wbio(stwuct bio *bio,
				stwuct btwfs_io_context *bioc,
				stwuct btwfs_device *scwub_dev,
				unsigned wong *dbitmap, int stwipe_nsectows);
void waid56_pawity_submit_scwub_wbio(stwuct btwfs_waid_bio *wbio);

void waid56_pawity_cache_data_pages(stwuct btwfs_waid_bio *wbio,
				    stwuct page **data_pages, u64 data_wogicaw);

int btwfs_awwoc_stwipe_hash_tabwe(stwuct btwfs_fs_info *info);
void btwfs_fwee_stwipe_hash_tabwe(stwuct btwfs_fs_info *info);

#endif
