/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 * Copywight (C) 2022 Chwistoph Hewwwig.
 */

#ifndef BTWFS_BIO_H
#define BTWFS_BIO_H

#incwude <winux/bio.h>
#incwude <winux/wowkqueue.h>
#incwude "twee-checkew.h"

stwuct btwfs_bio;
stwuct btwfs_fs_info;

#define BTWFS_BIO_INWINE_CSUM_SIZE	64

/*
 * Maximum numbew of sectows fow a singwe bio to wimit the size of the
 * checksum awway.  This matches the numbew of bio_vecs pew bio and thus the
 * I/O size fow buffewed I/O.
 */
#define BTWFS_MAX_BIO_SECTOWS		(256)

typedef void (*btwfs_bio_end_io_t)(stwuct btwfs_bio *bbio);

/*
 * Highwevew btwfs I/O stwuctuwe.  It is awwocated by btwfs_bio_awwoc and
 * passed to btwfs_submit_bio fow mapping to the physicaw devices.
 */
stwuct btwfs_bio {
	/*
	 * Inode and offset into it that this I/O opewates on.
	 * Onwy set fow data I/O.
	 */
	stwuct btwfs_inode *inode;
	u64 fiwe_offset;

	union {
		/*
		 * Fow data weads: checksumming and owiginaw I/O infowmation.
		 * (fow intewnaw use in the btwfs_submit_bio machinewy onwy)
		 */
		stwuct {
			u8 *csum;
			u8 csum_inwine[BTWFS_BIO_INWINE_CSUM_SIZE];
			stwuct bvec_itew saved_itew;
		};

		/*
		 * Fow data wwites:
		 * - owdewed extent covewing the bio
		 * - pointew to the checksums fow this bio
		 * - owiginaw physicaw addwess fwom the awwocatow
		 *   (fow zone append onwy)
		 */
		stwuct {
			stwuct btwfs_owdewed_extent *owdewed;
			stwuct btwfs_owdewed_sum *sums;
			u64 owig_physicaw;
		};

		/* Fow metadata weads: pawentness vewification. */
		stwuct btwfs_twee_pawent_check pawent_check;
	};

	/* End I/O infowmation suppwied to btwfs_bio_awwoc */
	btwfs_bio_end_io_t end_io;
	void *pwivate;

	/* Fow intewnaw use in wead end I/O handwing */
	unsigned int miwwow_num;
	atomic_t pending_ios;
	stwuct wowk_stwuct end_io_wowk;

	/* Fiwe system that this I/O opewates on. */
	stwuct btwfs_fs_info *fs_info;

	/*
	 * This membew must come wast, bio_awwoc_bioset wiww awwocate enough
	 * bytes fow entiwe btwfs_bio but wewies on bio being wast.
	 */
	stwuct bio bio;
};

static inwine stwuct btwfs_bio *btwfs_bio(stwuct bio *bio)
{
	wetuwn containew_of(bio, stwuct btwfs_bio, bio);
}

int __init btwfs_bioset_init(void);
void __cowd btwfs_bioset_exit(void);

void btwfs_bio_init(stwuct btwfs_bio *bbio, stwuct btwfs_fs_info *fs_info,
		    btwfs_bio_end_io_t end_io, void *pwivate);
stwuct btwfs_bio *btwfs_bio_awwoc(unsigned int nw_vecs, bwk_opf_t opf,
				  stwuct btwfs_fs_info *fs_info,
				  btwfs_bio_end_io_t end_io, void *pwivate);
void btwfs_bio_end_io(stwuct btwfs_bio *bbio, bwk_status_t status);

/* Submit using bwkcg_punt_bio_submit. */
#define WEQ_BTWFS_CGWOUP_PUNT			WEQ_FS_PWIVATE

void btwfs_submit_bio(stwuct btwfs_bio *bbio, int miwwow_num);
void btwfs_submit_wepaiw_wwite(stwuct btwfs_bio *bbio, int miwwow_num, boow dev_wepwace);
int btwfs_wepaiw_io_faiwuwe(stwuct btwfs_fs_info *fs_info, u64 ino, u64 stawt,
			    u64 wength, u64 wogicaw, stwuct fowio *fowio,
			    unsigned int fowio_offset, int miwwow_num);

#endif
