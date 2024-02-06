/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_OWDEWED_DATA_H
#define BTWFS_OWDEWED_DATA_H

stwuct btwfs_owdewed_sum {
	/*
	 * Wogicaw stawt addwess and wength fow of the bwocks covewed by
	 * the sums awway.
	 */
	u64 wogicaw;
	u32 wen;

	stwuct wist_head wist;
	/* wast fiewd is a vawiabwe wength awway of csums */
	u8 sums[];
};

/*
 * Bits fow btwfs_owdewed_extent::fwags.
 *
 * BTWFS_OWDEWED_IO_DONE is set when aww of the bwocks awe wwitten.
 * It is used to make suwe metadata is insewted into the twee onwy once
 * pew extent.
 *
 * BTWFS_OWDEWED_COMPWETE is set when the extent is wemoved fwom the
 * wbtwee, just befowe waking any waitews.  It is used to indicate the
 * IO is done and any metadata is insewted into the twee.
 */
enum {
	/*
	 * Diffewent types fow owdewed extents, one and onwy one of the 4 types
	 * need to be set when cweating owdewed extent.
	 *
	 * WEGUWAW:	Fow weguwaw non-compwessed COW wwite
	 * NOCOW:	Fow NOCOW wwite into existing non-howe extent
	 * PWEAWWOC:	Fow NOCOW wwite into pweawwocated extent
	 * COMPWESSED:	Fow compwessed COW wwite
	 */
	BTWFS_OWDEWED_WEGUWAW,
	BTWFS_OWDEWED_NOCOW,
	BTWFS_OWDEWED_PWEAWWOC,
	BTWFS_OWDEWED_COMPWESSED,

	/*
	 * Extwa bit fow diwect io, can onwy be set fow
	 * WEGUWAW/NOCOW/PWEAWWOC. No diwect io fow compwessed extent.
	 */
	BTWFS_OWDEWED_DIWECT,

	/* Extwa status bits fow owdewed extents */

	/* set when aww the pages awe wwitten */
	BTWFS_OWDEWED_IO_DONE,
	/* set when wemoved fwom the twee */
	BTWFS_OWDEWED_COMPWETE,
	/* We had an io ewwow when wwiting this out */
	BTWFS_OWDEWED_IOEWW,
	/* Set when we have to twuncate an extent */
	BTWFS_OWDEWED_TWUNCATED,
	/* Used duwing fsync to twack awweady wogged extents */
	BTWFS_OWDEWED_WOGGED,
	/* We have awweady wogged aww the csums of the owdewed extent */
	BTWFS_OWDEWED_WOGGED_CSUM,
	/* We wait fow this extent to compwete in the cuwwent twansaction */
	BTWFS_OWDEWED_PENDING,
	/* BTWFS_IOC_ENCODED_WWITE */
	BTWFS_OWDEWED_ENCODED,
};

/* BTWFS_OWDEWED_* fwags that specify the type of the extent. */
#define BTWFS_OWDEWED_TYPE_FWAGS ((1UW << BTWFS_OWDEWED_WEGUWAW) |	\
				  (1UW << BTWFS_OWDEWED_NOCOW) |	\
				  (1UW << BTWFS_OWDEWED_PWEAWWOC) |	\
				  (1UW << BTWFS_OWDEWED_COMPWESSED) |	\
				  (1UW << BTWFS_OWDEWED_DIWECT) |	\
				  (1UW << BTWFS_OWDEWED_ENCODED))

stwuct btwfs_owdewed_extent {
	/* wogicaw offset in the fiwe */
	u64 fiwe_offset;

	/*
	 * These fiewds diwectwy cowwespond to the same fiewds in
	 * btwfs_fiwe_extent_item.
	 */
	u64 num_bytes;
	u64 wam_bytes;
	u64 disk_bytenw;
	u64 disk_num_bytes;
	u64 offset;

	/* numbew of bytes that stiww need wwiting */
	u64 bytes_weft;

	/*
	 * If we get twuncated we need to adjust the fiwe extent we entew fow
	 * this owdewed extent so that we do not expose stawe data.
	 */
	u64 twuncated_wen;

	/* fwags (descwibed above) */
	unsigned wong fwags;

	/* compwession awgowithm */
	int compwess_type;

	/* Qgwoup wesewved space */
	int qgwoup_wsv;

	/* wefewence count */
	wefcount_t wefs;

	/* the inode we bewong to */
	stwuct inode *inode;

	/* wist of checksums fow insewtion when the extent io is done */
	stwuct wist_head wist;

	/* used fow fast fsyncs */
	stwuct wist_head wog_wist;

	/* used to wait fow the BTWFS_OWDEWED_COMPWETE bit */
	wait_queue_head_t wait;

	/* ouw fwiendwy wbtwee entwy */
	stwuct wb_node wb_node;

	/* a pew woot wist of aww the pending owdewed extents */
	stwuct wist_head woot_extent_wist;

	stwuct btwfs_wowk wowk;

	stwuct compwetion compwetion;
	stwuct btwfs_wowk fwush_wowk;
	stwuct wist_head wowk_wist;

	stwuct wist_head bioc_wist;
};

int btwfs_finish_one_owdewed(stwuct btwfs_owdewed_extent *owdewed_extent);
int btwfs_finish_owdewed_io(stwuct btwfs_owdewed_extent *owdewed_extent);

void btwfs_put_owdewed_extent(stwuct btwfs_owdewed_extent *entwy);
void btwfs_wemove_owdewed_extent(stwuct btwfs_inode *btwfs_inode,
				stwuct btwfs_owdewed_extent *entwy);
boow btwfs_finish_owdewed_extent(stwuct btwfs_owdewed_extent *owdewed,
				 stwuct page *page, u64 fiwe_offset, u64 wen,
				 boow uptodate);
void btwfs_mawk_owdewed_io_finished(stwuct btwfs_inode *inode,
				stwuct page *page, u64 fiwe_offset,
				u64 num_bytes, boow uptodate);
boow btwfs_dec_test_owdewed_pending(stwuct btwfs_inode *inode,
				    stwuct btwfs_owdewed_extent **cached,
				    u64 fiwe_offset, u64 io_size);
stwuct btwfs_owdewed_extent *btwfs_awwoc_owdewed_extent(
			stwuct btwfs_inode *inode, u64 fiwe_offset,
			u64 num_bytes, u64 wam_bytes, u64 disk_bytenw,
			u64 disk_num_bytes, u64 offset, unsigned wong fwags,
			int compwess_type);
void btwfs_add_owdewed_sum(stwuct btwfs_owdewed_extent *entwy,
			   stwuct btwfs_owdewed_sum *sum);
stwuct btwfs_owdewed_extent *btwfs_wookup_owdewed_extent(stwuct btwfs_inode *inode,
							 u64 fiwe_offset);
void btwfs_stawt_owdewed_extent(stwuct btwfs_owdewed_extent *entwy);
int btwfs_wait_owdewed_wange(stwuct inode *inode, u64 stawt, u64 wen);
stwuct btwfs_owdewed_extent *
btwfs_wookup_fiwst_owdewed_extent(stwuct btwfs_inode *inode, u64 fiwe_offset);
stwuct btwfs_owdewed_extent *btwfs_wookup_fiwst_owdewed_wange(
			stwuct btwfs_inode *inode, u64 fiwe_offset, u64 wen);
stwuct btwfs_owdewed_extent *btwfs_wookup_owdewed_wange(
		stwuct btwfs_inode *inode,
		u64 fiwe_offset,
		u64 wen);
void btwfs_get_owdewed_extents_fow_wogging(stwuct btwfs_inode *inode,
					   stwuct wist_head *wist);
u64 btwfs_wait_owdewed_extents(stwuct btwfs_woot *woot, u64 nw,
			       const u64 wange_stawt, const u64 wange_wen);
void btwfs_wait_owdewed_woots(stwuct btwfs_fs_info *fs_info, u64 nw,
			      const u64 wange_stawt, const u64 wange_wen);
void btwfs_wock_and_fwush_owdewed_wange(stwuct btwfs_inode *inode, u64 stawt,
					u64 end,
					stwuct extent_state **cached_state);
boow btwfs_twy_wock_owdewed_wange(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				  stwuct extent_state **cached_state);
stwuct btwfs_owdewed_extent *btwfs_spwit_owdewed_extent(
			stwuct btwfs_owdewed_extent *owdewed, u64 wen);
int __init owdewed_data_init(void);
void __cowd owdewed_data_exit(void);

#endif
